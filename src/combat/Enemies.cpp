#include "combat/Simulation.hpp"

namespace dw {
const Enemy *Simulation::findEnemy(EntityId id) const {
    for (const auto &enemy : enemies)
        if (enemy.id == id)
            return &enemy;
    return nullptr;
}

bool Simulation::chainActive(const Enemy &enemy) const {
    const auto *partner = findEnemy(enemy.partner);
    return enemy.alive && enemy.kind == EnemyKind::Chainbound && partner && partner->alive &&
           partner->partner == enemy.id && distance(enemy.position, partner->position) <= 8 &&
           arena.sight(enemy.position, partner->position);
}

bool Simulation::hurtPlayer(float damage, const Context &context) {
    if (godMode || player.dodge > 0 || player.hurt > 0)
        return false;
    // Apply once at impact for enemy contact, shots and hazards, including split shots.
    damage *= EnemyDamageMultiplier;
    player.hp -= damage;
    audioCues.push(AudioCueKind::Hurt, player.position);
    stats.damageTaken += damage;
    player.hurt = 0.45f;
    Event hit;
    hit.type = EventType::PlayerDamaged;
    hit.damage = damage;
    hit.position = player.position;
    if (context.chainId)
        emit(hit, context);
    else
        queueRoot(hit);
    return true;
}

float Simulation::enemyDamage(const Enemy &enemy, const Event &event) const {
    if (event.execution)
        return event.damage;
    if (enemy.kind == EnemyKind::Monster) {
        const auto *d = monsterDefinition(enemy.monster);
        const int type = enemy.monster / 10000, variant = enemy.monster / 100 % 100;
        if (d->roomHazard || enemy.friendly || enemy.state == EnemyState::Buried ||
            enemy.state == EnemyState::Teleporting)
            return 0;
        if (type == 27 && variant != 1 && enemy.state != EnemyState::Windup &&
            enemy.state != EnemyState::Exposed)
            return 0;
        if (((type == 41 && variant != 2 && variant != 3) || (type == 23 && variant == 3)) &&
            !event.areaDamage && !event.armorPiercing && dot(unit(event.direction), enemy.facing) < .35f)
            return 0;
        if (type == 41 && variant == 3 && enemy.partner && findEnemy(enemy.partner))
            return 0;
    }
    float amount = event.damage;
    if (enemy.kind == EnemyKind::Ironhide && enemy.state != EnemyState::Stunned && !event.armorPiercing &&
        !event.areaDamage && dot(unit(event.direction), enemy.facing) < -0.25f)
        amount *= 0.35f;
    for (const auto &other : enemies)
        if (other.alive && other.kind == EnemyKind::Preacher && other.aura > 0 && other.id != enemy.id &&
            distance(other.position, enemy.position) < 6 && arena.sight(other.position, enemy.position)) {
            amount *= 0.65f; // Auras never stack into immunity.
            break;
        }
    return std::max(0.0f, amount);
}

void Simulation::shootEnemy(const Enemy &enemy, Vector3 direction, float damage, float speed, int bounces,
                            ProjectileKind kind) {
    audioCues.push(enemy.kind == EnemyKind::Monster ? AudioCueKind::MonsterAttack : AudioCueKind::EnemyShot,
                   enemy.position);
    Event shot;
    shot.position = add(enemy.position, mul(direction, enemy.radius + 0.15f));
    // A muzzle must not create a bullet through an adjacent wall.
    if (!arena.clear(enemy.position, shot.position, 0.22f))
        shot.position = enemy.position;
    shot.origin = shot.position;
    shot.direction = direction;
    shot.hostile = true;
    shot.damage = damage;
    shot.speed = speed;
    shot.bounces = bounces;
    shot.projectileKind = kind;
    shot.context.sourceEntity = enemy.id;
    queueRoot(shot);
}

void Simulation::addHazard(Hazard hazard) {
    if (hazards.size() >= limits.hazards) {
        suppress(hazard.context, "hazard capacity");
        return;
    }
    if (!hazard.context.chainId)
        hazard.context = {nextChain_++, 0, hazard.context.sourceEntity, -1};
    ++chains[hazard.context.chainId].active;
    hazards.push_back(hazard);
}

void Simulation::clearHazards() {
    for (const auto &hazard : hazards) {
        auto it = chains.find(hazard.context.chainId);
        if (it != chains.end() && it->second.active)
            --it->second.active;
    }
    hazards.clear();
}

void Simulation::updateHazards(float dt) {
    for (auto &hazard : hazards) {
        const float previousAge = hazard.age;
        hazard.age += dt;
        if (hazard.age < hazard.delay)
            continue;
        const float dist = distance(player.position, hazard.position);
        const bool visible = arena.sight(hazard.position, player.position);
        if (hazard.kind == HazardKind::Beam) {
            if (segmentSphere(hazard.origin, hazard.position, player.position, hazard.radius + .48f) <= 1 &&
                arena.sight(hazard.origin, player.position))
                hurtPlayer(hazard.damage, hazard.context);
        } else if (hazard.kind == HazardKind::Tar) {
            if (dist < hazard.radius + .3f && visible)
                player.slowTime = .3f;
        } else if (hazard.kind == HazardKind::Ring) {
            const float before =
                hazard.radius * std::clamp((previousAge - hazard.delay) / hazard.duration, 0.0f, 1.0f);
            const float after =
                hazard.radius * std::clamp((hazard.age - hazard.delay) / hazard.duration, 0.0f, 1.0f);
            if (!hazard.hitPlayer && dist + 0.5f >= before && dist - 0.5f <= after && visible)
                hazard.hitPlayer = hurtPlayer(hazard.damage, hazard.context);
        } else if (hazard.kind == HazardKind::Fire || hazard.kind == HazardKind::Creep ||
                   hazard.kind == HazardKind::Gas || hazard.kind == HazardKind::HolyLight) {
            if (dist < hazard.radius + 0.3f && visible)
                hurtPlayer(hazard.damage, hazard.context);
        } else {
            if (dist < hazard.radius + 0.48f && visible)
                hurtPlayer(hazard.damage, hazard.context);
            effectVisual(hazard.position, hazard.radius, 0, 0.5f);
            if (hazard.kind == HazardKind::Powder || hazard.kind == HazardKind::MonsterBomb) {
                Event blast;
                blast.type = EventType::Explosion;
                blast.position = hazard.position;
                blast.origin = hazard.origin;
                blast.damage = 80;
                blast.radius = hazard.radius;
                blast.areaDamage = true;
                blast.hostile = hazard.kind == HazardKind::MonsterBomb;
                emit(blast, hazard.context);
            }
            hazard.alive = false;
        }
        if (hazard.age >= hazard.delay + hazard.duration)
            hazard.alive = false;
        if (!hazard.alive) {
            auto it = chains.find(hazard.context.chainId);
            if (it != chains.end() && it->second.active)
                --it->second.active;
        }
    }
    std::erase_if(hazards, [](const Hazard &hazard) { return !hazard.alive; });
}

void Simulation::performEnemyAttack(Enemy &enemy) {
    const Vector3 aim = unit(sub(enemy.target, enemy.position));
    const float dist = distance(enemy.position, player.position);
    switch (enemy.kind) {
    case EnemyKind::Rusher:
    case EnemyKind::Ironhide:
    case EnemyKind::PowderHusk: {
        const float reach = enemy.kind == EnemyKind::Ironhide ? 2.6f : 2.1f;
        if (dist < reach && dot(aim, unit(sub(player.position, enemy.position))) > 0.35f &&
            arena.sight(enemy.position, player.position))
            hurtPlayer(enemy.kind == EnemyKind::Ironhide ? 22 : 10);
        effectVisual(add(enemy.position, mul(aim, 0.8f)), reach * 0.5f, 4, 0.2f);
        break;
    }
    case EnemyKind::Shotgun:
        for (int i = -2; i <= 2; ++i)
            shootEnemy(enemy, rotateY(aim, float(i) * 0.17f), 10, 13);
        break;
    case EnemyKind::Sharpshooter:
        shootEnemy(enemy, aim, 28, 32);
        break;
    case EnemyKind::Prospector:
    case EnemyKind::Spitter: {
        Hazard hazard;
        const bool fire = enemy.kind == EnemyKind::Spitter;
        hazard.kind = fire ? HazardKind::Fire : HazardKind::Dynamite;
        hazard.position = enemy.target;
        hazard.origin = enemy.position;
        hazard.delay = fire ? 0.85f : 1.05f;
        hazard.duration = fire ? 3.5f : 0;
        hazard.radius = fire ? 2.3f : 2.8f;
        hazard.damage = fire ? 7 : 22;
        hazard.context.sourceEntity = enemy.id;
        addHazard(hazard);
        break;
    }
    case EnemyKind::Railbreaker:
        enemy.state = EnemyState::Charging;
        enemy.stateTime = 1.1f;
        enemy.facing = aim;
        break;
    case EnemyKind::Preacher:
        enemy.aura = 4;
        shootEnemy(enemy, aim, 8, 8);
        break;
    case EnemyKind::BellRinger: {
        Hazard hazard;
        hazard.kind = HazardKind::Ring;
        hazard.position = hazard.origin = enemy.position;
        hazard.delay = 0;
        hazard.duration = 1.6f;
        hazard.radius = 11;
        hazard.damage = 16;
        hazard.context.sourceEntity = enemy.id;
        addHazard(hazard);
        break;
    }
    case EnemyKind::Hangman:
        shootEnemy(enemy, aim, 8, 16, 0, ProjectileKind::Hook);
        break;
    case EnemyKind::Marshal:
        shootEnemy(enemy, aim, 12, 9, 1);
        break;
    case EnemyKind::Wraith:
        for (int i = -1; i <= 1; ++i)
            shootEnemy(enemy, rotateY(aim, float(i) * 0.2f), 10, 10);
        break;
    default:
        shootEnemy(enemy, aim, 12, 10);
        break;
    }
}

void Simulation::updateEnemies(float dt) {
    // Offspring are queued and flushed after this loop; no vector references are invalidated.
    for (auto &enemy : enemies) {
        if (!enemy.alive)
            continue;
        if (enemy.kind == EnemyKind::Monster) {
            updateMonster(enemy, dt);
            continue;
        }
        if (enemy.kind == EnemyKind::Chainbound) {
            const auto *partner = findEnemy(enemy.partner);
            if (!partner || !partner->alive) {
                enemy.partner = 0;
                enemy.kind = EnemyKind::Gunman;
            } else if (enemy.id < partner->id && chainActive(enemy) &&
                       segmentSphere(enemy.position, partner->position, player.position, 0.62f) <= 1)
                hurtPlayer(12);
        }
        const auto &definition = enemyDefinition(enemy.kind);
        enemy.cooldown -= dt / EnemyCooldownMultiplier;
        enemy.flash = std::max(0.0f, enemy.flash - dt);
        enemy.aura = std::max(0.0f, enemy.aura - dt);
        enemy.pathTime -= dt;
        enemy.age += dt;
        enemy.velocity = {};
        const Vector3 direction = unit(sub(player.position, enemy.position));
        const float dist = distance(player.position, enemy.position);
        const bool sight = arena.sight(enemy.position, player.position);
        Vector3 movement{};

        if (enemy.state == EnemyState::Stunned) {
            enemy.stateTime -= dt;
            if (enemy.stateTime <= 0)
                enemy.state = EnemyState::Ready;
            continue;
        }
        if (enemy.state == EnemyState::Teleporting) {
            enemy.stateTime -= dt;
            if (enemy.stateTime <= 0) {
                bool occupied = distance(enemy.target, player.position) < 3;
                for (const auto &other : enemies)
                    occupied = occupied ||
                               (other.alive && other.id != enemy.id &&
                                distance(other.position, enemy.target) < other.radius + enemy.radius + 0.2f);
                if (!occupied && !arena.blocked(enemy.target, enemy.radius)) {
                    effectVisual(enemy.position, 1.1f, 2, 0.5f);
                    enemy.position = enemy.target;
                }
                enemy.state = EnemyState::Windup;
                audioCues.push(AudioCueKind::Warning, enemy.position);
                enemy.stateTime = definition.windup; // Always warn again after arrival.
                enemy.target = player.position;
                enemy.facing = unit(sub(enemy.target, enemy.position));
            }
            continue;
        }
        if (enemy.state == EnemyState::Windup) {
            enemy.stateTime -= dt;
            if (enemy.stateTime <= 0) {
                enemy.state = EnemyState::Ready;
                enemy.cooldown = definition.cooldown;
                performEnemyAttack(enemy);
            }
            continue;
        }
        if (enemy.state == EnemyState::Charging) {
            enemy.stateTime -= dt;
            const Vector3 before = enemy.position;
            const Vector3 delta = mul(enemy.facing, 14 * dt);
            // A charge stops on any wall, instead of sliding around its corner.
            const bool impact = !arena.clear(before, add(before, delta), enemy.radius) ||
                                arena.blocked(add(before, delta), enemy.radius);
            if (impact) {
                enemy.state = EnemyState::Stunned;
                enemy.stateTime = 1.3f;
                effectVisual(enemy.position, 1.2f, 3, 0.4f);
            } else {
                enemy.position = add(before, delta);
                enemy.velocity = mul(enemy.facing, 14);
                if (segmentSphere(before, enemy.position, player.position, enemy.radius + 0.48f) <= 1 &&
                    sight)
                    hurtPlayer(24);
                if (enemy.stateTime <= 0) {
                    enemy.state = EnemyState::Stunned;
                    enemy.stateTime = 0.5f;
                }
            }
            continue;
        }

        // Ironhide turns at a bounded angular speed; its back can be flanked.
        if (enemy.kind == EnemyKind::Ironhide) {
            const float current = std::atan2(enemy.facing.z, enemy.facing.x);
            const float wanted = std::atan2(direction.z, direction.x);
            const float delta = std::remainder(wanted - current, 2 * Pi);
            const float angle = current + std::clamp(delta, -1.1f * dt, 1.1f * dt);
            enemy.facing = {std::cos(angle), 0, std::sin(angle)};
        } else
            enemy.facing = direction;

        if (enemy.kind == EnemyKind::Boss) {
            enemy.phase = enemy.hp > enemy.maxHp * 0.66f ? 0 : enemy.hp > enemy.maxHp * 0.33f ? 1 : 2;
            movement = mul(direction, enemy.phase == 2 ? 2.7f : 1.0f);
            if (dist < 1.9f && sight)
                hurtPlayer(18);
            if (enemy.cooldown <= 0) {
                const int count = enemy.phase == 0 ? 5 : enemy.phase == 1 ? 12 : 18;
                for (int i = 0; i < count; ++i) {
                    float angle = enemy.phase == 0 ? (float(i) - 2) * 0.14f
                                                   : 2 * Pi * float(i) / float(count) + enemy.age * 0.18f;
                    Vector3 aim = enemy.phase == 0 ? rotateY(direction, angle)
                                                   : Vector3{std::cos(angle), 0, std::sin(angle)};
                    shootEnemy(enemy, aim, 14, enemy.phase == 2 ? 12 : 8);
                }
                enemy.cooldown = enemy.phase == 0 ? 1.5f : enemy.phase == 1 ? 1.7f : 1.0f;
                effectVisual(enemy.position, 2.0f + float(enemy.phase), 4, 0.45f);
            }
        } else {
            const bool melee = enemy.kind == EnemyKind::Rusher || enemy.kind == EnemyKind::Ironhide ||
                               enemy.kind == EnemyKind::PowderHusk;
            float desired = melee                                   ? 1.5f
                            : enemy.kind == EnemyKind::Shotgun      ? 5.0f
                            : enemy.kind == EnemyKind::Sharpshooter ? 15.0f
                                                                    : 8.0f;
            const float reach = melee ? (enemy.kind == EnemyKind::Ironhide ? 2.1f : 1.7f)
                                : enemy.kind == EnemyKind::Shotgun      ? 9.0f
                                : enemy.kind == EnemyKind::BellRinger   ? 10.0f
                                : enemy.kind == EnemyKind::Hangman      ? 14.0f
                                : enemy.kind == EnemyKind::Sharpshooter ? 32.0f
                                                                        : 20.0f;
            if (dist > desired || !sight)
                movement =
                    mul(enemy.kind == EnemyKind::Ironhide ? enemy.facing : direction, definition.speed);
            else if (!melee && dist < desired - 2)
                movement = mul(direction, -definition.speed * 0.8f);
            if (enemy.kind == EnemyKind::Chainbound) {
                const auto *partner = findEnemy(enemy.partner);
                if (partner && distance(partner->position, enemy.position) > 7)
                    movement = mul(unit(sub(partner->position, enemy.position)), definition.speed);
                else if (sight && dist > 4 && dist < 12)
                    movement = add(movement,
                                   mul(rotateY(direction, Pi / 2), enemy.id < enemy.partner ? 0.8f : -0.8f));
            }
            if (enemy.cooldown <= 0 && sight && dist <= reach &&
                (enemy.kind != EnemyKind::Ironhide || dot(enemy.facing, direction) > 0.8f)) {
                enemy.target = enemy.kind == EnemyKind::Ironhide
                                   ? add(enemy.position, mul(enemy.facing, dist))
                                   : player.position;
                enemy.state = EnemyState::Windup;
                audioCues.push(AudioCueKind::Warning, enemy.position);
                enemy.stateTime = definition.windup;
                enemy.path.clear();
                if (enemy.kind == EnemyKind::Wraith) {
                    const auto &bounds = arena.rooms[size_t(room)].bounds;
                    for (int i = 0; i < 48; ++i) {
                        Vector3 destination{combatRng.real(bounds.min.x + 1, bounds.max.x - 1), 0.85f,
                                            combatRng.real(bounds.min.z + 1, bounds.max.z - 1)};
                        const float range = distance(destination, player.position);
                        if (range >= 5 && range <= 12 && !arena.blocked(destination, enemy.radius) &&
                            arena.sight(destination, player.position)) {
                            enemy.target = destination;
                            enemy.state = EnemyState::Teleporting;
                            enemy.stateTime = 0.9f;
                            break;
                        }
                    }
                }
                continue;
            }
        }

        // Reuse short paths until cover or a moving target requires another route.
        if (!sight && length(movement) > 0.1f) {
            if (enemy.pathTime <= 0) {
                enemy.path = arena.path(enemy.position, player.position, enemy.radius);
                enemy.pathTime = 0.9f + float(enemy.id % 7) * 0.07f;
            }
            while (!enemy.path.empty() && distance(enemy.path.front(), enemy.position) < 0.35f)
                enemy.path.erase(enemy.path.begin());
            if (!enemy.path.empty())
                movement = mul(unit(sub(enemy.path.front(), enemy.position)), definition.speed);
        } else
            enemy.path.clear();
        movement = mul(movement, EnemyMovementMultiplier);
        Vector3 separation{};
        for (size_t index : candidates(enemy.position, enemy.position, 2.2f)) {
            const auto &other = enemies[index];
            if (other.id == enemy.id || !other.alive)
                continue;
            const Vector3 delta = sub(enemy.position, other.position);
            const float d = length(delta), gap = enemy.radius + other.radius + 0.15f;
            if (d > 0.01f && d < gap)
                separation = add(separation, mul(delta, (gap - d) / d));
        }
        movement = add(movement, mul(separation, 2));
        Vector3 next = arena.move(enemy.position, mul(movement, dt), enemy.radius);
        if (distance(next, enemy.position) < 0.01f && length(movement) > 0.2f) {
            const Vector3 side = rotateY(direction, enemy.id % 2 ? Pi / 2 : -Pi / 2);
            next = arena.move(enemy.position, mul(side, definition.speed * EnemyMovementMultiplier * dt),
                              enemy.radius);
        }
        enemy.velocity = mul(sub(next, enemy.position), 1 / dt);
        enemy.position = next;
    }
}
} // namespace dw
