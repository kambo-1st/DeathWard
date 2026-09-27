#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <iostream>
#include <numeric>

namespace dw {
Simulation::Simulation(uint64_t seed, uint64_t runId, const WorldState &world)
    : arena(seed), encounterRng(seed ^ 0x454e434f554e5445ULL), rewardRng(seed ^ 0x5245574152445354ULL),
      combatRng(seed ^ 0x434f4d424154524eULL), seed_(seed), runId_(runId), startingWorld_(world) {
    rescued = world.minersRescued;
    altarDestroyed = world.altarDestroyed;
    bossKilled = world.bossDefeated;
    followup = world.bossDefeated;
    player.position = arena.entrance;
    player.aim = arena.rooms[0].center;
    enemies.reserve(256);
    projectiles.reserve(4096);
    for (int index = 0; index < RoomCount; ++index) {
        if (arena.rooms[size_t(index)].kind != RoomKind::Power)
            continue;
        std::array<ItemId, ItemCount> pool{ItemId::Ricochet, ItemId::Split, ItemId::Judas, ItemId::Powder,
                                           ItemId::Ghost};
        for (int i = 0; i < 2; ++i) {
            const int other = i + int(rewardRng.bounded(uint32_t(ItemCount - i)));
            std::swap(pool[size_t(i)], pool[size_t(other)]);
            rooms[size_t(index)].offers[size_t(i)] = pool[size_t(i)];
        }
    }
    enterRoom(0);
    announce(followup ? "RED HOLLOW / return to unfinished business"
                      : "RED HOLLOW / find the six missing miners",
             5);
}
void Simulation::announce(std::string text, float seconds) {
    message = std::move(text);
    messageTime = seconds;
}
size_t Simulation::livingEnemies() const {
    return size_t(std::count_if(enemies.begin(), enemies.end(), [](const Enemy &e) { return e.alive; }));
}
size_t Simulation::itemStacks(ItemId item) const {
    return size_t(std::count(items.begin(), items.end(), item));
}
Enemy *Simulation::findEnemy(EntityId id) {
    auto it = std::find_if(enemies.begin(), enemies.end(), [id](const Enemy &e) { return e.id == id; });
    return it == enemies.end() ? nullptr : &*it;
}
const Enemy *Simulation::boss() const {
    for (const auto &e : enemies)
        if (e.alive && e.kind == EnemyKind::Boss)
            return &e;
    return nullptr;
}
std::string Simulation::roomName() const {
    return roomName(room);
}
std::string Simulation::roomName(int index) {
    static constexpr const char *names[] = {
        "The Old Claim",   "Timberfall",       "The Cageworks",    "Ash Chapel",    "Dead Man's Cut",
        "The Deep Vein",   "The Switchyard",   "Old Powder Store", "The Dry Well",  "Iron Junction",
        "The Broken Lift", "The Bone Gallery", "Smuggler's Cache", "The Reliquary", "The Hollow Court"};
    return names[std::clamp(index, 0, FinalRoom)];
}
EntityId Simulation::spawn(EnemyKind kind, Vector3 position) {
    if (livingEnemies() >= limits.enemies) {
        suppress({}, "enemy capacity");
        return 0;
    }
    Enemy e;
    e.id = nextEntity_++;
    e.kind = kind;
    e.position = position;
    e.position.y = 0.85f;
    e.maxHp = kind == EnemyKind::Boss ? 1100.0f : kind == EnemyKind::Gunman ? 48.0f : 36.0f;
    e.hp = e.maxHp;
    e.radius = kind == EnemyKind::Boss ? 1.2f : 0.6f;
    e.cooldown = encounterRng.real(0.5f, 1.8f);
    enemies.push_back(e);
    return e.id;
}
void Simulation::spawnWave(int count) {
    const auto &area = arena.rooms[size_t(room)].bounds;
    for (int i = 0; i < count; ++i) {
        Vector3 p{};
        bool found = false;
        for (int attempt = 0; attempt < 80; ++attempt) {
            p = {encounterRng.real(area.min.x + 1.5f, area.max.x - 1.5f), 0.85f,
                 encounterRng.real(area.min.z + 1.5f, area.max.z - 1.5f)};
            if (!arena.blocked(p, 0.8f) && distance(p, player.position) > 6) {
                found = true;
                break;
            }
        }
        if (found)
            spawn(encounterRng.bounded(3) == 0 ? EnemyKind::Gunman : EnemyKind::Rusher, p);
    }
}
void Simulation::grant(ItemId item) {
    if (int(item) < 0 || int(item) >= ItemCount || items.size() >= 256)
        return;
    items.push_back(item);
    if (item == ItemId::Judas) {
        player.maxHp = std::max(10.0f, player.maxHp * 0.8f);
        player.hp = std::min(player.hp, player.maxHp);
    }
    Event e;
    e.type = EventType::Pickup;
    queueRoot(e);
    announce(std::string(itemDefinition(item).name) + " / the rules have changed");
    checkpointNeeded = true;
}
void Simulation::offerReward() {
    const auto &progress = rooms[size_t(room)];
    if (arena.rooms[size_t(room)].kind != RoomKind::Power || progress.rewardTaken)
        return;
    offers = progress.offers;
    rewardOpen = true;
}
void Simulation::chooseReward(int index) {
    auto &progress = rooms[size_t(room)];
    if (!rewardOpen || index < 0 || index >= int(offers.size()) || progress.rewardTaken ||
        arena.rooms[size_t(room)].kind != RoomKind::Power)
        return;
    progress.rewardTaken = true;
    ++powerUpsTaken;
    grant(offers[size_t(index)]);
    rewardOpen = false;
    announce("Power claimed. This cache is empty; explore another passage.", 4);
}
void Simulation::enterRoom(int index) {
    room = std::clamp(index, 0, FinalRoom);
    auto &progress = rooms[size_t(room)];
    const bool firstVisit = !progress.visited;
    progress.visited = true;
    roomClear = progress.cleared;
    rewardOpen = false;
    wave = 0;
    waveDelay = 1.2f;
    projectiles.clear();
    queue_.clear();
    chains.clear();
    enemies.clear();
    visuals.clear();
    if (firstVisit && room != 0)
        player.hp = std::min(player.maxHp, player.hp + 15);
    if (arena.rooms[size_t(room)].kind == RoomKind::Power) {
        if (!progress.cleared) {
            progress.cleared = true;
            ++stats.rooms;
        }
        roomClear = true;
        arena.sealRoom(-1);
        announce(progress.rewardTaken ? "An empty power cache."
                                      : "POWER CACHE / approach the pedestal and choose one item.",
                 5);
    } else if (!roomClear) {
        cancelMove();
        arena.sealRoom(room);
        announce(room == FinalRoom ? "THE HOLLOW COURT / all exits sealed"
                                   : roomName() + " / doors sealed until the fight is over",
                 4);
    } else {
        arena.sealRoom(-1);
        announce(roomName() + " / already cleared", 3);
    }
    checkpointNeeded = true;
}
void Simulation::clearRoom() {
    auto &progress = rooms[size_t(room)];
    if (progress.cleared)
        return;
    progress.cleared = roomClear = true;
    arena.sealRoom(-1);
    ++stats.rooms;
    player.hp = std::min(player.maxHp, player.hp + 20);
    checkpointNeeded = true;
    Event event;
    event.type = EventType::RoomCleared;
    queueRoot(event);
    announce(room == FinalRoom
                 ? "The Court is silent. Use the return lantern to reach Black Creek."
                 : "Room cleared. Doors reopened. Choose a passage; look for keys and power caches.",
             5);
}
void Simulation::collectKeys() {
    for (auto &key : arena.keys) {
        if (!key.collected && rooms[size_t(key.room)].cleared &&
            distance(player.position, key.position) < 1.6f && arena.sight(player.position, key.position)) {
            key.collected = true;
            ++keys;
            announce("KEY FOUND / unlock a golden door. Keys carried: " + std::to_string(keys), 4);
        }
    }
}
bool Simulation::useDoor(int passage, int side) {
    if (passage < 0 || passage >= int(arena.passages.size()) || side < 0 || side > 1)
        return false;
    auto &door = arena.passages[size_t(passage)];
    if (distance(player.position, arena.doorApproach(passage, side)) > 3 || !roomClear || door.sealed[0] ||
        door.sealed[1]) {
        announce("Clear the room before leaving.", 2);
        return false;
    }
    if (door.locked) {
        if (keys == 0) {
            announce("A key is needed. Search the open passages.", 3);
            return false;
        }
        --keys;
        door.locked = false;
        arena.rebuildWalls();
        announce("Door unlocked. Keys carried: " + std::to_string(keys), 3);
    }
    requestMove(arena.doorApproach(passage, 1 - side));
    return true;
}
void Simulation::requestDoor(int passage, int side) {
    if (passage < 0 || passage >= int(arena.passages.size()) || side < 0 || side > 1)
        return;
    const auto &door = arena.passages[size_t(passage)];
    if (!roomClear || door.sealed[0] || door.sealed[1]) {
        announce("Clear the room before leaving.", 2);
        return;
    }
    if (!door.locked) {
        requestMove(arena.doorApproach(passage, 1 - side));
        return;
    }
    requestMove(arena.doorApproach(passage, side));
    doorOnArrival_ = std::pair{passage, side};
}
void Simulation::startBoss() {
    cancelMove();
    debugScenario = false;
    enterRoom(FinalRoom);
    rewardOpen = false;
    player.position = arena.rooms.back().entry;
    beginBossEncounter();
}
void Simulation::beginBossEncounter() {
    wave = 1;
    spawn(followup ? EnemyKind::Gunman : EnemyKind::Boss, arena.rooms.back().bossSpawn);
    if (followup)
        spawnWave(12);
    announce(followup ? "Finish what remains" : "THE HOLLOW SHERIFF", 4);
}
void Simulation::killAll() {
    for (const auto &enemy : enemies)
        if (enemy.alive) {
            Event e;
            e.type = EventType::Damage;
            e.target = enemy.id;
            e.position = enemy.position;
            e.origin = player.position;
            e.direction = unit(sub(enemy.position, player.position));
            e.damage = 10000;
            queueRoot(e);
        }
    drainEvents();
}
void Simulation::startStress() {
    cancelMove();
    debugScenario = true;
    godMode = true;
    rewardOpen = false;
    roomClear = false;
    enemies.clear();
    projectiles.clear();
    queue_.clear();
    chains.clear();
    for (int i = 0; i < ItemCount; ++i)
        if (!itemStacks(ItemId(i)))
            grant(ItemId(i));
    spawnWave(100);
    for (int i = 0; i < 600; ++i) {
        float angle = float(i) * 2 * Pi / 600;
        Event e;
        e.position = player.position;
        e.origin = e.position;
        e.direction = {std::cos(angle), 0, std::sin(angle)};
        e.lastRound = true;
        queueRoot(e);
    }
    drainEvents();
    announce("STRESS / 100 enemies, 600 shots, all five effects", 6);
}
void Simulation::interact() {
    cancelMove();
    collectKeys();
    if (arena.rooms[size_t(room)].kind == RoomKind::Power && !rooms[size_t(room)].rewardTaken &&
        distance(player.position, arena.rooms[size_t(room)].objective) < 2.6f) {
        offerReward();
        return;
    }
    if (!rescued && distance(player.position, arena.miners) < 2.6f) {
        rescued = true;
        checkpointNeeded = true;
        announce("Six miners escape through the old shaft. Mary will remember.", 5);
        return;
    }
    if (!altarDestroyed && distance(player.position, arena.altar) < 2.6f) {
        altarDestroyed = true;
        checkpointNeeded = true;
        effectVisual(arena.altar, 3, 0, 0.8f);
        announce("The altar breaks. Something loses your scent.", 5);
        return;
    }
    if (room == FinalRoom && roomClear && distance(player.position, arena.exit) < 2.8f) {
        finished = true;
        return;
    }
    for (size_t i = 0; i < arena.passages.size(); ++i)
        for (int side = 0; side < 2; ++side)
            if (distance(player.position, arena.doorApproach(int(i), side)) < 2.8f) {
                useDoor(int(i), side);
                return;
            }
}
void Simulation::finishDebug(bool victory) {
    if (victory) {
        bossKilled = true;
        finished = true;
    } else {
        player.hp = 0;
        dead = true;
    }
}
RunSummary Simulation::summary() const {
    RunSummary s;
    s.id = runId_;
    s.seed = seed_;
    s.startingContext = CampaignStore::worldContext(startingWorld_);
    s.rescued = rescued;
    s.altarDestroyed = altarDestroyed;
    s.bossKilled = bossKilled;
    s.stats = stats;
    s.items = items;
    return s;
}
void Simulation::suppress(const Context &ctx, const std::string &reason) {
    ++stats.suppressed;
    if (!logs.empty() && logs.back().id == ctx.chainId && logs.back().reason == reason) {
        ++logs.back().suppressed;
        return;
    }
    logs.push_back({ctx.chainId, ctx.generation, ctx.sourceEffect, reason, 1});
    if (logs.size() > 40)
        logs.pop_front();
    // Bounded diagnostics avoid turning a pathological chain into unbounded I/O.
    if (stats.suppressed <= 8)
        std::clog << "chain " << ctx.chainId << " depth " << ctx.generation << " effect " << ctx.sourceEffect
                  << ": " << reason << '\n';
}
void Simulation::queueRoot(Event event) {
    event.context = {nextChain_++, 0, event.context.sourceEntity, -1};
    accept(event);
}
void Simulation::emit(Event event, const Context &parent, int effect) {
    event.context = parent;
    ++event.context.generation;
    if (effect >= 0)
        event.context.sourceEffect = effect;
    accept(event);
}
bool Simulation::accept(Event event) {
    if (event.context.generation > limits.maxDepth) {
        suppress(event.context, "generation limit");
        return false;
    }
    if (queue_.size() >= limits.queuedEvents) {
        suppress(event.context, "queue capacity");
        return false;
    }
    auto &chain = chains[event.context.chainId];
    if (chain.stopped || chain.accepted >= limits.eventsPerChain) {
        chain.stopped = true;
        suppress(event.context, "chain event limit");
        return false;
    }
    ++chain.accepted;
    ++chain.queued;
    stats.maxDepth = std::max(stats.maxDepth, uint64_t(event.context.generation));
    queue_.push_back(event);
    return true;
}
void Simulation::createProjectile(const Event &event) {
    if (projectiles.size() >= limits.projectiles) {
        suppress(event.context, "projectile capacity");
        return;
    }
    Projectile p;
    p.id = nextEntity_++;
    p.position = p.previous = event.position;
    p.origin = event.origin;
    p.velocity = mul(unit(event.direction), event.speed);
    p.damage = event.damage;
    p.hostile = event.hostile;
    p.lastRound = event.lastRound;
    p.ghost = event.ghost;
    p.context = event.context;
    if (event.target)
        p.hitEntities.push_back(event.target);
    if (p.hostile) {
        p.radius = 0.22f;
        p.life = 5;
    } else
        applyProjectileItems(*this, p);
    ++chains[p.context.chainId].active;
    projectiles.push_back(std::move(p));
    ++stats.projectiles;
    stats.maxProjectiles = std::max(stats.maxProjectiles, uint64_t(projectiles.size()));
}
void Simulation::effectVisual(Vector3 p, float radius, int kind, float duration) {
    if (visuals.size() < 512)
        visuals.push_back({p, radius, duration, duration, kind});
}
void Simulation::process(const Event &e) {
    switch (e.type) {
    case EventType::Shot:
        createProjectile(e);
        break;
    case EventType::ProjectileHit: {
        Event damage = e;
        damage.type = EventType::Damage;
        emit(damage, e.context);
        break;
    }
    case EventType::Damage: {
        Enemy *target = findEnemy(e.target);
        if (!target || !target->alive)
            break;
        stats.damageDealt += std::min(target->hp, e.damage);
        target->hp -= e.damage;
        target->flash = 0.12f;
        Event hit = e;
        hit.position = target->position;
        hit.type = EventType::EnemyDamaged;
        emit(hit, e.context);
        if (target->hp <= 0) {
            target->alive = false;
            ++stats.kills;
            auto &chain = chains[e.context.chainId];
            ++chain.kills;
            stats.largestKillChain = std::max(stats.largestKillChain, chain.kills);
            effectVisual(target->position, 0.8f, 1);
            if (target->kind == EnemyKind::Boss) {
                bossKilled = true;
                checkpointNeeded = true;
            }
            hit.type = EventType::EnemyKilled;
            emit(hit, e.context);
        }
        break;
    }
    case EventType::Explosion: {
        ++stats.explosions;
        effectVisual(e.position, e.radius, 0, 0.5f);
        for (const auto &enemy : enemies)
            if (enemy.alive && distance(enemy.position, e.position) < e.radius + enemy.radius &&
                arena.sight(e.position, enemy.position)) {
                Event damage = e;
                damage.type = EventType::Damage;
                damage.target = enemy.id;
                emit(damage, e.context);
            }
        break;
    }
    default:
        break;
    }
    dispatchItemEffects(*this, e);
}
void Simulation::drainEvents() {
    size_t processed = 0;
    while (!queue_.empty() && processed++ < limits.eventsPerTick) {
        Event e = queue_.front();
        queue_.pop_front();
        auto it = chains.find(e.context.chainId);
        if (it != chains.end() && it->second.queued)
            --it->second.queued;
        process(e);
    }
}
void Simulation::collectChains() {
    for (auto it = chains.begin(); it != chains.end();) {
        if (it->second.queued == 0 && it->second.active == 0)
            it = chains.erase(it);
        else
            ++it;
    }
}
void Simulation::updatePlayer(const Input &input, float dt) {
    player.aim = input.aim;
    player.aim.y = player.position.y;
    player.fireCooldown = std::max(0.0f, player.fireCooldown - dt);
    player.dodgeCooldown = std::max(0.0f, player.dodgeCooldown - dt);
    player.hurt = std::max(0.0f, player.hurt - dt);
    Vector3 movement = input.movement;
    if (input.fire || input.standStill)
        cancelMove(); // Attacking never continues an old click-to-move order.
    if (input.standStill) {
        movement = {};
    } else if (length(movement) > 0.01f) {
        cancelMove(); // Keyboard movement immediately takes over from click-to-move.
    } else if (!input.fire) {
        if (input.doorTarget)
            requestDoor(input.doorTarget->first, input.doorTarget->second);
        else if (input.moveTarget)
            requestMove(*input.moveTarget);
        if (doorOnArrival_ && distance(player.position, arena.doorApproach(doorOnArrival_->first,
                                                                           doorOnArrival_->second)) < 1.0f) {
            const auto target = *doorOnArrival_;
            cancelMove();
            useDoor(target.first, target.second);
        }
        if (!movePath_.empty() && interactOnArrival_ && distance(player.position, movePath_.back()) < 2.0f &&
            arena.sight(player.position, movePath_.back())) {
            interact();
        }
        while (!movePath_.empty() && distance(player.position, movePath_[waypoint_]) < 0.04f) {
            if (++waypoint_ == movePath_.size())
                cancelMove();
        }
        if (!movePath_.empty()) {
            Vector3 offset = sub(movePath_[waypoint_], player.position);
            movement = mul(unit(offset), std::min(1.0f, length(offset) / (6 * dt)));
        }
    }
    if (input.dodge && player.dodgeCooldown <= 0) {
        player.dodge = 0.22f;
        player.dodgeCooldown = 1.1f;
        player.dodgeDirection =
            length(movement) > 0.1f ? unit(movement) : unit(sub(player.aim, player.position));
    }
    if (length(movement) > 1)
        movement = unit(movement);
    if (player.dodge > 0) {
        movement = mul(player.dodgeDirection, 3.4f);
        player.dodge -= dt;
    }
    player.position = arena.move(player.position, mul(movement, 6 * dt), 0.48f);
    if (input.fire && player.fireCooldown <= 0) {
        player.fireCooldown = 0.29f;
        ++stats.shots;
        Event e;
        e.direction = unit(sub(player.aim, player.position));
        e.position = add(player.position, mul(e.direction, 0.7f));
        e.origin = e.position;
        e.lastRound = player.nextRound == 6;
        player.nextRound = player.nextRound % 6 + 1;
        queueRoot(e);
        effectVisual(e.position, 0.35f, 3, 0.09f);
    }
    if (input.interact)
        interact();
}
void Simulation::updateEnemies(float dt) {
    auto hurtPlayer = [&](float damage, const Context &parent) {
        if (godMode || player.dodge > 0 || player.hurt > 0)
            return;
        player.hp -= damage;
        stats.damageTaken += damage;
        player.hurt = 0.45f;
        Event hit;
        hit.type = EventType::PlayerDamaged;
        hit.damage = damage;
        hit.position = player.position;
        if (parent.chainId)
            emit(hit, parent);
        else
            queueRoot(hit);
    };
    for (auto &e : enemies) {
        if (!e.alive)
            continue;
        e.cooldown -= dt;
        e.flash = std::max(0.0f, e.flash - dt);
        e.age += dt;
        Vector3 toward = sub(player.position, e.position);
        float dist = length(toward);
        Vector3 direction = unit(toward);
        Vector3 movement{};
        if (e.kind == EnemyKind::Rusher) {
            movement = mul(direction, 2.0f + 0.12f * float(room));
            if (dist < 1.3f && e.cooldown <= 0) {
                hurtPlayer(10, {});
                e.cooldown = 0.8f;
            }
        } else if (e.kind == EnemyKind::Gunman) {
            if (dist > 9 || !arena.sight(e.position, player.position))
                movement = mul(direction, 1.7f);
            else if (dist < 5)
                movement = mul(direction, -1.4f);
            if (e.cooldown <= 0 && arena.sight(e.position, player.position)) {
                Event shot;
                shot.position = add(e.position, mul(direction, 0.8f));
                shot.origin = shot.position;
                shot.direction = direction;
                shot.hostile = true;
                shot.speed = 10;
                shot.damage = 12;
                shot.context.sourceEntity = e.id;
                queueRoot(shot);
                e.cooldown = 1.9f;
            }
        } else {
            e.phase = e.hp > e.maxHp * 0.66f ? 0 : e.hp > e.maxHp * 0.33f ? 1 : 2;
            movement = mul(direction, e.phase == 2 ? 2.7f : 1.0f);
            if (dist < 1.9f)
                hurtPlayer(18, {});
            if (e.cooldown <= 0) {
                int count = e.phase == 0 ? 5 : e.phase == 1 ? 12 : 18;
                for (int i = 0; i < count; ++i) {
                    float angle = e.phase == 0 ? (float(i) - 2) * 0.14f
                                               : 2 * Pi * float(i) / float(count) + e.age * 0.18f;
                    Vector3 aim = e.phase == 0 ? rotateY(direction, angle)
                                               : Vector3{std::cos(angle), 0, std::sin(angle)};
                    Event shot;
                    shot.position = add(e.position, mul(aim, 1.3f));
                    shot.origin = shot.position;
                    shot.direction = aim;
                    shot.hostile = true;
                    shot.speed = e.phase == 2 ? 12 : 8;
                    shot.damage = 14;
                    shot.context.sourceEntity = e.id;
                    queueRoot(shot);
                }
                e.cooldown = e.phase == 0 ? 1.5f : e.phase == 1 ? 1.7f : 1.0f;
                effectVisual(e.position, 2.0f + float(e.phase), 4, 0.45f);
            }
        }
        // Nearby separation and obstacle steering keep primitive crowds moving around cover.
        Vector3 separation{};
        for (size_t index : candidates(e.position, e.position, 1.6f)) {
            const auto &other = enemies[index];
            if (other.id == e.id || !other.alive)
                continue;
            Vector3 delta = sub(e.position, other.position);
            float d = length(delta);
            if (d > 0.01f && d < e.radius + other.radius + 0.15f)
                separation = add(separation, mul(delta, (1.4f - d) / d));
        }
        movement = add(movement, mul(separation, 2));
        Vector3 next = arena.move(e.position, mul(movement, dt), e.radius);
        if (distance(next, e.position) < 0.015f && length(movement) > 0.2f) {
            Vector3 side = rotateY(direction, Pi / 2);
            if (e.id % 2)
                side = mul(side, -1);
            next = arena.move(e.position, mul(side, 2.4f * dt), e.radius);
        }
        e.velocity = mul(sub(next, e.position), 1 / dt);
        e.position = next;
    }
}
void Simulation::rebuildGrid() {
    const auto origin = arena.rooms[size_t(room)].center;
    for (auto &cell : grid_)
        cell.clear();
    for (size_t i = 0; i < enemies.size(); ++i)
        if (enemies[i].alive) {
            const auto p = enemies[i].position;
            int x = std::clamp(int(std::floor((p.x - origin.x + 20) / 4)), 0, 9),
                z = std::clamp(int(std::floor((p.z - origin.z + 20) / 4)), 0, 9);
            grid_[size_t(z * 10 + x)].push_back(i);
        }
}
std::vector<size_t> Simulation::candidates(Vector3 a, Vector3 b, float radius) const {
    const auto origin = arena.rooms[size_t(room)].center;
    a = sub(a, origin);
    b = sub(b, origin);
    int minX = std::clamp(int(std::floor((std::min(a.x, b.x) - radius + 20) / 4)), 0, 9),
        maxX = std::clamp(int(std::floor((std::max(a.x, b.x) + radius + 20) / 4)), 0, 9);
    int minZ = std::clamp(int(std::floor((std::min(a.z, b.z) - radius + 20) / 4)), 0, 9),
        maxZ = std::clamp(int(std::floor((std::max(a.z, b.z) + radius + 20) / 4)), 0, 9);
    std::vector<size_t> result;
    for (int z = minZ; z <= maxZ; ++z)
        for (int x = minX; x <= maxX; ++x) {
            const auto &cell = grid_[size_t(z * 10 + x)];
            result.insert(result.end(), cell.begin(), cell.end());
        }
    return result;
}
void Simulation::updateProjectiles(float dt) {
    for (auto &p : projectiles) {
        if (!p.alive)
            continue;
        p.previous = p.position;
        p.life -= dt;
        if (p.life <= 0) {
            p.alive = false;
            continue;
        }
        float remaining = dt;
        for (int step = 0; step < 8 && remaining > 0.00001f && p.alive; ++step) {
            Vector3 end = add(p.position, mul(p.velocity, remaining));
            float best = 2;
            Vector3 normal{};
            EntityId target = 0;
            bool wall = false, playerHit = false;
            for (const auto &box : arena.walls) {
                auto hit = segmentBox(p.position, end, box, p.radius);
                if (hit.hit && hit.t < best) {
                    best = hit.t;
                    normal = hit.normal;
                    wall = true;
                }
            }
            if (p.hostile) {
                float hit = segmentSphere(p.position, end, player.position, 0.48f + p.radius);
                if (hit < best) {
                    best = hit;
                    wall = false;
                    playerHit = true;
                }
            } else
                for (size_t index : candidates(p.position, end, 1.5f)) {
                    const Enemy &enemy = enemies[index];
                    if (!enemy.alive || std::find(p.hitEntities.begin(), p.hitEntities.end(), enemy.id) !=
                                            p.hitEntities.end())
                        continue;
                    float hit = segmentSphere(p.position, end, enemy.position, enemy.radius + p.radius);
                    if (hit < best) {
                        best = hit;
                        target = enemy.id;
                        wall = false;
                    }
                }
            if (best > 1) {
                p.position = end;
                break;
            }
            p.position = add(p.position, mul(sub(end, p.position), best));
            remaining *= 1 - best;
            Event event;
            event.position = p.position;
            event.origin = p.origin;
            event.direction = unit(p.velocity);
            event.damage = p.damage;
            event.target = target;
            event.lastRound = p.lastRound;
            event.ghost = p.ghost;
            event.hostile = p.hostile;
            if (wall) {
                if (p.bounces > 0 && length(normal) > 0.5f) {
                    --p.bounces;
                    ++stats.bounces;
                    p.velocity = sub(p.velocity, mul(normal, 2 * dot(p.velocity, normal)));
                    p.position = add(p.position, mul(normal, 0.02f));
                    event.type = EventType::ProjectileBounce;
                    emit(event, p.context);
                    effectVisual(p.position, 0.25f, 3, 0.12f);
                } else
                    p.alive = false;
            } else if (playerHit) {
                if (!godMode && player.dodge <= 0 && player.hurt <= 0) {
                    player.hp -= p.damage;
                    stats.damageTaken += p.damage;
                    player.hurt = 0.35f;
                    event.type = EventType::PlayerDamaged;
                    emit(event, p.context);
                }
                p.alive = false;
            } else {
                event.type = EventType::ProjectileHit;
                emit(event, p.context);
                p.hitEntities.push_back(target);
                if (p.pierce > 0) {
                    --p.pierce;
                    p.position = add(p.position, mul(unit(p.velocity), 0.02f));
                } else
                    p.alive = false;
            }
        }
    }
    for (const auto &p : projectiles)
        if (!p.alive) {
            auto it = chains.find(p.context.chainId);
            if (it != chains.end() && it->second.active)
                --it->second.active;
        }
    std::erase_if(projectiles, [](const Projectile &p) { return !p.alive; });
}
void Simulation::step(const Input &input, float dt) {
    if (rewardOpen || finished || dead)
        return;
    stats.duration += dt;
    if (boss())
        stats.bossDuration += dt;
    messageTime = std::max(0.0f, messageTime - dt);
    updatePlayer(input, dt);
    const int location = arena.roomAt(player.position);
    if (roomClear && location >= 0 && location != room) {
        const auto &bounds = arena.rooms[size_t(location)].bounds;
        const auto p = player.position;
        // Close doors only once the entire player is safely beyond the threshold.
        if (p.x > bounds.min.x + 1.1f && p.x < bounds.max.x - 1.1f && p.z > bounds.min.z + 1.1f &&
            p.z < bounds.max.z - 1.1f)
            enterRoom(location);
    }
    collectKeys();
    rebuildGrid();
    updateEnemies(dt);
    rebuildGrid();
    updateProjectiles(dt);
    drainEvents();
    for (auto &v : visuals)
        v.life -= dt;
    std::erase_if(visuals, [](const VisualEffect &v) { return v.life <= 0; });
    std::erase_if(enemies, [](const Enemy &e) { return !e.alive; });
    collectChains();
    if (player.hp <= 0) {
        dead = true;
        return;
    }
    if (debugScenario)
        return;
    if (!roomClear && livingEnemies() == 0 && queue_.empty()) {
        waveDelay -= dt;
        if (waveDelay <= 0) {
            if (room == FinalRoom) {
                if (wave == 0) {
                    beginBossEncounter();
                } else {
                    clearRoom();
                }
            } else if (wave < WavesPerRoom) {
                spawnWave(std::min(18, 6 + arena.rooms[size_t(room)].depth * 2 + wave * 2));
                ++wave;
                waveDelay = 1.8f;
            } else {
                clearRoom();
            }
        }
    }
}
} // namespace dw
