#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <iostream>
#include <numeric>

namespace dw {
Simulation::Simulation(uint64_t seed, uint64_t runId, const WorldState &world, MissionTheme theme,
                       bool canyonRiver, bool tutorial)
    : arena(seed, theme, canyonRiver, tutorial), encounterRng(seed ^ 0x454e434f554e5445ULL),
      rewardRng(seed ^ 0x5245574152445354ULL), combatRng(seed ^ 0x434f4d424154524eULL), seed_(seed),
      runId_(runId), startingWorld_(world) {
    surveyTutorial=tutorial;
    rooms.resize(arena.rooms.size());
    rescued = world.minersRescued;
    altarDestroyed = world.altarDestroyed;
    bossKilled = theme == MissionTheme::Canyon ? world.flags.contains("canyon_cleared") : world.bossDefeated;
    followup = bossKilled;
    if(surveyTutorial)rescued=altarDestroyed=bossKilled=followup=false;
    player.position = arena.entrance;
    player.aim = arena.rooms[0].center;
    player.facing = unit(sub(player.aim, player.position));
    enemies.reserve(256);
    projectiles.reserve(4096);
    for (int index = 0; index < arena.roomCount(); ++index) {
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
    for (int index = 0; index < arena.roomCount(); ++index)
        prepareRoomEnemies(index);
    enemies = std::move(rooms[0].residents);
    prepareMoney();
    prepareShop();
    enterRoom(0);
    if(surveyTutorial)announce("THE LOST SURVEY / One floor. Recover Bell's records and return to Fort Mercy.",6);
    else announce(std::string(missionTheme(theme).region) +
                 (followup ? " / return to unfinished business" : " / find the six missing miners"),
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
    if(surveyTutorial) {
        static constexpr const char *names[]={"Beyond the Gate","Dust Hollow","The Sheltered Bend","Last Approach","Survey Camp"};
        return names[size_t(room)];
    }
    if (arena.rooms[size_t(room)].kind == RoomKind::Shop)
        return "Trader's Rest";
    return roomName(room, arena.theme);
}
std::string Simulation::tutorialHint() const {
    if(surveyRecovered)return "The letter and records are safe. Follow the return lantern to Fort Mercy.";
    switch(room) {
    case 0:return "Click clear ground to walk, or use WASD. Follow the open passage into the badlands.";
    case 1:return roomClear?"The passage is open. Keep following the trail.":"Click an enemy to fire. Keep moving; hold Shift to shoot from one spot.";
    case 2:return "A quiet stretch. Recover your bearings and follow the trail toward the survey camp.";
    case 3:return roomClear?"The survey camp is just ahead.":"Use Dodge or Space to evade an attack. Cover stops bullets.";
    default:return "Look for the leather document case. Click it, or approach and choose Recover records.";
    }
}
std::string Simulation::roomName(int index, MissionTheme theme) {
    static constexpr std::array<const char *, RoomCount> names{
        "The Old Claim",   "Timberfall",       "The Cageworks",    "Ash Chapel",    "Dead Man's Cut",
        "The Deep Vein",   "The Switchyard",   "Old Powder Store", "The Dry Well",  "Iron Junction",
        "The Broken Lift", "The Bone Gallery", "Smuggler's Cache", "The Reliquary", "The Hollow Court"};
    static constexpr std::array<const char *, RoomCount> canyonNames{
        "Dustwind Approach",  "The Red Narrows",   "Captives' Gulch",  "Sunbleached Shrine",
        "Dead Man's Bend",    "Splitrock Basin",   "The Dry Wash",     "Powder Bluff",
        "Coyote Hollow",      "Twin Mesas",        "Fallen Spire",     "Bone Dry Ravine",
        "Prospector's Cache", "The Sun Reliquary", "The Infested Mesa"};
    const auto &selected = theme == MissionTheme::Canyon ? canyonNames : names;
    return selected[size_t(std::clamp(index, 0, FinalRoom))];
}
void Simulation::grant(ItemId item) {
    if (int(item) < 0 || int(item) >= ItemCount || items.size() >= 256)
        return;
    items.push_back(item);
    audioCues.push(AudioCueKind::Pickup, player.position);
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
void Simulation::tunePlayer(float baseHealth, float shotDamage) {
    if (dead || finished || !std::isfinite(baseHealth) || !std::isfinite(shotDamage))
        return;
    baseHealth = std::clamp(baseHealth, 25.0f, 2000.0f);
    shotDamage = std::clamp(shotDamage, 1.0f, 500.0f);
    if (baseHealth != player.baseHealth) {
        const float healthFraction = std::clamp(player.hp / player.maxHp, 0.0f, 1.0f);
        player.baseHealth = baseHealth;
        player.maxHp = baseHealth;
        for (size_t i = 0; i < itemStacks(ItemId::Judas); ++i)
            player.maxHp = std::max(10.0f, player.maxHp * 0.8f);
        player.hp = player.maxHp * healthFraction;
    }
    player.shotDamage = shotDamage;
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
    rewardOpen = shopOpen = false;
    announce("Power claimed. This cache is empty; explore another passage.", 4);
}
void Simulation::enterRoom(int index) {
    audioCues.clear();
    ++audioEpoch;
    audioCues.push(AudioCueKind::Door, player.position);
    if (rooms[size_t(room)].cleared)
        enemies.clear();
    rooms[size_t(room)].residents = std::move(enemies);
    room = std::clamp(index, 0, finalRoom());
    enemies = std::move(rooms[size_t(room)].residents);
    auto &progress = rooms[size_t(room)];
    progress.visited = true;
    roomClear = progress.cleared;
    rewardOpen = shopOpen = false;
    projectiles.clear();
    clearHazards();
    player.pullTime = 0;
    player.velocity = {};
    player.shootPose = 0;
    queue_.clear();
    chains.clear();
    pendingMonsters_.clear();
    visuals.clear();
    particleBursts.clear();
    const auto kind = arena.rooms[size_t(room)].kind;
    if (kind == RoomKind::Power || kind == RoomKind::Empty || kind == RoomKind::Shop) {
        if (!progress.cleared) {
            progress.cleared = true;
            ++stats.rooms;
        }
        roomClear = true;
        arena.sealRoom(-1);
        announce(kind == RoomKind::Shop    ? "TRADER'S REST / approach the shopkeeper to trade."
                 : kind == RoomKind::Empty ? "QUIET ROOM / no enemies. Explore the open passages."
                 : progress.rewardTaken    ? "An empty power cache."
                                           : "POWER CACHE / approach the pedestal and choose one item.",
                 5);
    } else if (!roomClear) {
        cancelMove();
        arena.sealRoom(room);
        announce(roomName() + " / doors sealed until the fight is over", 4);
        if (room == finalRoom() && !surveyTutorial)
            beginBossEncounter();
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
    audioCues.push(AudioCueKind::RoomClear, player.position);
    if (room == finalRoom() && !surveyTutorial && arena.theme == MissionTheme::Canyon)
        bossKilled = true;
    for (auto &enemy : enemies)
        if (const auto *d = monsterDefinition(enemy.monster); d && d->roomHazard)
            enemy.alive = false;
    clearHazards();
    arena.sealRoom(-1);
    ++stats.rooms;
    checkpointNeeded = true;
    Event event;
    event.type = EventType::RoomCleared;
    queueRoot(event);
    announce(surveyTutorial?"The trail is clear. Continue toward Bell's survey camp.":room == finalRoom()
                 ? "The final chamber is clear. Use the return lantern to reach town."
                 : "Room cleared. Doors reopened. Choose a passage; look for keys and power caches.",
             5);
}
void Simulation::collectKeys() {
    for (auto &key : arena.keys) {
        if (!key.collected && rooms[size_t(key.room)].cleared &&
            distance(player.position, key.position) < 1.6f && arena.sight(player.position, key.position)) {
            key.collected = true;
            ++keys;
            audioCues.push(AudioCueKind::Pickup, key.position);
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
        audioCues.push(AudioCueKind::Door, player.position);
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
    jumpDebug(finalRoom(), true);
}
void Simulation::beginBossEncounter() {
    announce(arena.theme == MissionTheme::Canyon ? "THE INFESTED MESA / clear the final monster group"
             : followup                          ? "Finish what remains"
                                                 : "THE HOLLOW SHERIFF",
             4);
}
void Simulation::killAll() {
    pendingMonsters_.clear();
    for (const auto &enemy : enemies)
        if (enemy.alive) {
            Event e;
            e.type = EventType::Damage;
            e.target = enemy.id;
            e.position = enemy.position;
            e.origin = player.position;
            e.direction = unit(sub(enemy.position, player.position));
            e.damage = 10000;
            e.execution = true;
            queueRoot(e);
        }
    drainEvents();
}
void Simulation::healDebug() {
    player.hp = player.maxHp;
    player.hurt = player.dodge = player.dodgeCooldown = player.fireCooldown = 0;
    player.pullTime = 0;
    player.velocity = {};
    player.shootPose = 0;
    dynamiteCooldown = 0;
    announce("CHEAT / full health and cooldowns reset");
}
void Simulation::clearRoomDebug() {
    killAll();
    // End all pending damage and secondary effects, including bounded work left
    // over from a stress scene.
    cancelMove();
    enemies.clear();
    pendingMonsters_.clear();
    projectiles.clear();
    clearHazards();
    player.pullTime = 0;
    queue_.clear();
    chains.clear();
    visuals.clear();
    particleBursts.clear();
    rewardOpen = shopOpen = debugScenario = false;
    if (room == finalRoom() && !surveyTutorial)
        bossKilled = true;
    clearRoom();
    // A stress scenario may have started in an already-cleared room.
    roomClear = true;
    arena.sealRoom(-1);
    drainEvents();
    collectChains();
    checkpointNeeded = true;
    announce("CHEAT / room cleared. All combat seals open.");
}
void Simulation::jumpDebug(int index, bool restart) {
    index = std::clamp(index, 0, finalRoom());
    cancelMove();
    debugScenario = finished = dead = false;
    auto &progress = rooms[size_t(index)];
    if (restart && progress.cleared) {
        progress.cleared = false;
        --stats.rooms;
    }
    if (restart && index == finalRoom())
        bossKilled = false;
    if (restart) {
        prepareRoomEnemies(index);
        if (index == room)
            enemies = std::move(rooms[size_t(index)].residents);
    }
    healDebug();
    // Debug travel must not land inside a group that already occupies the room.
    player.position =
        index == finalRoom() ? arena.rooms[size_t(index)].entry : arena.rooms[size_t(index)].center;
    for (const auto &enemy : roomEnemies(index))
        if (enemy.alive && distance(player.position, enemy.position) < 6) {
            player.position = arena.rooms[size_t(index)].entry;
            break;
        }
    enterRoom(index);
    player.aim = arena.rooms[size_t(index)].exit;
    // Keep the build, keys, unlocked doors and claimed rewards when replaying.
    announce(std::string("CHEAT / ") + (restart ? "restarted " : "jumped to ") + roomName());
}
void Simulation::startStress() {
    audioCues.clear();
    ++audioEpoch;
    cancelMove();
    debugScenario = true;
    godMode = true;
    rewardOpen = shopOpen = false;
    roomClear = false;
    enemies.clear();
    projectiles.clear();
    clearHazards();
    player.pullTime = 0;
    queue_.clear();
    chains.clear();
    for (int i = 0; i < ItemCount; ++i)
        if (!itemStacks(ItemId(i)))
            grant(ItemId(i));
    spawnEnemies(100);
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
    if(surveyTutorial && room==finalRoom() && roomClear &&
       distance(player.position,surveyPosition())<2.6f && arena.sight(player.position,surveyPosition())) {
        if(!surveyRecovered)audioCues.push(AudioCueKind::Pickup,surveyPosition());
        surveyRecovered=true;letterOpen=true;checkpointNeeded=true;
        announce("Bell's survey records and Eleanor's letter recovered. Return to the commander.",6);
        return;
    }
    if (room == arena.shopRoom) {
        openShop();
        if (shopOpen)
            return;
    }
    collectKeys();
    if (arena.rooms[size_t(room)].kind == RoomKind::Power && !rooms[size_t(room)].rewardTaken &&
        distance(player.position, arena.rooms[size_t(room)].objective) < 2.6f) {
        offerReward();
        return;
    }
    if (!surveyTutorial && !rescued && distance(player.position, arena.miners) < 2.6f) {
        audioCues.push(AudioCueKind::Pickup, arena.miners);
        rescued = true;
        checkpointNeeded = true;
        announce("Six miners escape through the old shaft. Mary will remember.", 5);
        return;
    }
    if (!surveyTutorial && !altarDestroyed && distance(player.position, arena.altar) < 2.6f) {
        audioCues.push(AudioCueKind::Explosion, arena.altar);
        altarDestroyed = true;
        checkpointNeeded = true;
        effectVisual(arena.altar, 3, 0, 0.8f);
        announce("The altar breaks. Something loses your scent.", 5);
        return;
    }
    if (canReturn() && distance(player.position, arena.exit) < 2.8f) {
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
        if (!dead)
            audioCues.push(AudioCueKind::PlayerDeath, player.position);
        dead = true;
    }
}
RunSummary Simulation::summary() const {
    RunSummary s;
    s.id = runId_;
    s.seed = seed_;
    s.expedition = surveyTutorial?SurveyExpeditionTitle:missionTheme(arena.theme).title;
    s.startingContext = CampaignStore::worldContext(startingWorld_);
    s.rescued = !surveyTutorial&&rescued;
    s.altarDestroyed = !surveyTutorial&&altarDestroyed;
    s.bossKilled = !surveyTutorial&&bossKilled;
    s.surveyRecovered = surveyTutorial&&surveyRecovered;
    s.stats = stats;
    s.items = items;
    s.moneyCollected = moneyCollected;
    s.moneySpent = moneySpent;
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
    p.kind = event.projectileKind;
    p.bounces = event.bounces;
    if (event.target)
        p.hitEntities.push_back(event.target);
    if (p.hostile) {
        p.radius = 0.22f;
        p.life = 5;
        if (p.kind == ProjectileKind::BurstShot)
            p.life = 1.2f;
        if (p.kind == ProjectileKind::ReturningHead) {
            p.life = 2;
            p.radius = .4f;
        }
        if (p.kind == ProjectileKind::Rock) {
            p.life = 2;
            p.radius = .35f;
        }
        if (const auto *source = findEnemy(p.context.sourceEntity)) {
            const int type = source->monster / 10000;
            if ((type == 11 || type == 30 || type == 88) && p.kind == ProjectileKind::Bullet)
                p.life = .8f;
        }
    } else
        applyProjectileItems(*this, p);
    ++chains[p.context.chainId].active;
    projectiles.push_back(std::move(p));
    ++stats.projectiles;
    stats.maxProjectiles = std::max(stats.maxProjectiles, uint64_t(projectiles.size()));
}
void Simulation::particleEffect(ParticleEffect kind, Vector3 position, Vector3 direction, float scale) {
    if (particleBursts.size() >= 128) particleBursts.erase(particleBursts.begin());
    particleBursts.push_back({kind, position, direction, 0, std::clamp(scale,.3f,2.f),
                             uint32_t(seed_) ^ (nextParticle_++ * 0x9e3779b9u)});
}
ParticleEffect Simulation::impactMaterial(Vector3 position, Vector3 normal) const {
    for (const auto &passage : arena.passages)
        for (int side = 0; side < 2; ++side) {
            const auto &b = passage.gates[size_t(side)];
            if (passage.closed(side) && position.x >= b.min.x-.3f && position.x <= b.max.x+.3f &&
                position.z >= b.min.z-.3f && position.z <= b.max.z+.3f)
                return ParticleEffect::Metal;
        }
    if (normal.y > .6f) return ParticleEffect::Dirt;
    return arena.theme == MissionTheme::Canyon ? ParticleEffect::Stone : ParticleEffect::Wood;
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
        const float damage = enemyDamage(*target, e);
        if (damage <= 0) {
            audioCues.push(AudioCueKind::StoneHit, target->position);
            if (!e.areaDamage) particleEffect(ParticleEffect::Metal, e.position, mul(e.direction,-1));
            if (target->monster == monsterId(41, 4) && !e.hostile && !e.areaDamage)
                shootEnemy(*target, mul(unit(e.direction), -1), 10, 12);
            break;
        }
        if (!e.areaDamage)
            particleEffect(target->kind == EnemyKind::Ironhide ? ParticleEffect::Metal : ParticleEffect::Flesh,
                           e.position, mul(e.direction,-1));
        stats.damageDealt += std::min(target->hp, damage);
        target->hp -= damage;
        audioCues.push(AudioCueKind::FleshHit, target->position);
        if (target->kind == EnemyKind::Preacher && damage > 0) {
            target->aura = 0;
            target->state = EnemyState::Ready;
            target->cooldown = 1.5f;
        }
        target->flash = 0.12f;
        Event hit = e;
        hit.position = target->position;
        hit.type = EventType::EnemyDamaged;
        emit(hit, e.context);
        if (target->hp <= 0) {
            if (!e.execution && target->kind == EnemyKind::Monster && collapseMonster(*target))
                break;
            target->alive = false;
            dropMoney(*target);
            audioCues.push(AudioCueKind::EnemyDeath, target->position);
            if (target->kind == EnemyKind::Monster && !e.execution)
                monsterDeath(*target, e);
            if (target->kind == EnemyKind::PowderHusk) {
                Hazard hazard;
                hazard.kind = HazardKind::Powder;
                hazard.position = target->position;
                hazard.origin = e.origin;
                hazard.delay = 1.1f;
                hazard.radius = 3.4f;
                hazard.damage = 24;
                hazard.context = e.context;
                addHazard(hazard);
            }
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
        audioCues.push(AudioCueKind::Explosion, e.position);
        ++stats.explosions;
        particleEffect(ParticleEffect::Explosion, e.position, {0,1,0}, e.radius / 3.3f);
        effectVisual(e.position, e.radius, 0, 0.5f);
        for (const auto &enemy : enemies)
            if (enemy.alive && !(e.hostile && enemy.id == e.context.sourceEntity) &&
                distance(enemy.position, e.position) < e.radius + enemy.radius &&
                arena.sight(e.position, enemy.position)) {
                Event damage = e;
                damage.type = EventType::Damage;
                damage.target = enemy.id;
                damage.areaDamage = true;
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
    const Vector3 previousPosition = player.position;
    player.aim = input.aim;
    player.aim.y = player.position.y;
    player.fireCooldown = std::max(0.0f, player.fireCooldown - dt);
    dynamiteCooldown = std::max(0.0f, dynamiteCooldown - dt);
    player.dodgeCooldown = std::max(0.0f, player.dodgeCooldown - dt);
    player.hurt = std::max(0.0f, player.hurt - dt);
    player.shootPose = std::max(0.0f, player.shootPose - dt);
    player.slowTime = std::max(0.0f, player.slowTime - dt);
    Vector3 movement = input.movement;
    if (input.fire || input.standStill || input.dynamiteTarget)
        cancelMove(); // Attacking never continues an old click-to-move order.
    if (input.standStill) {
        movement = {};
    } else if (length(movement) > 0.01f) {
        cancelMove(); // Keyboard movement immediately takes over from click-to-move.
    } else if (!input.fire && !input.dynamiteTarget) {
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
        audioCues.push(AudioCueKind::Dodge, player.position);
        player.dodgeMoving = length(movement) > 0.1f;
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
    player.position = arena.move(
        player.position, mul(movement, (player.slowTime > 0 && player.dodge <= 0 ? 3.2f : 6) * dt), 0.48f);
    if (player.pullTime > 0) {
        if (player.dodge > 0 || !arena.sight(player.position, player.pullTarget))
            player.pullTime = 0;
        else {
            const Vector3 toward = sub(player.pullTarget, player.position);
            player.position =
                arena.move(player.position, mul(unit(toward), std::min(length(toward), 12 * dt)), 0.48f);
            player.pullTime = std::max(0.0f, player.pullTime - dt);
        }
    }
    kickDynamiteOnContact(previousPosition);
    if (input.placeDynamite)
        placeDynamite();
    else if (input.dynamiteTarget)
        throwDynamite(*input.dynamiteTarget);
    if (input.fire && player.fireCooldown <= 0 && !input.dynamiteTarget && !input.placeDynamite) {
        player.shootPose = 0.32f;
        player.fireCooldown = 0.29f;
        ++stats.shots;
        audioCues.push(AudioCueKind::Shot, player.position);
        Event e;
        e.direction = unit(sub(player.aim, player.position));
        e.damage = player.shotDamage;
        e.position = add(player.position, mul(e.direction, 0.7f));
        e.origin = e.position;
        e.lastRound = player.nextRound == 6;
        player.nextRound = player.nextRound % 6 + 1;
        queueRoot(e);
        particleEffect(ParticleEffect::PlayerMuzzle, e.position, e.direction);
        effectVisual(e.position, 0.35f, 6, 0.09f);
    }
    player.velocity = mul(sub(player.position, previousPosition), 1 / dt);
    if (player.dodge > 0)
        player.facing = player.dodgeDirection;
    else if (input.fire || player.shootPose > 0)
        player.facing = unit(sub(player.aim, player.position));
    else if (length(player.velocity) > 0.1f)
        player.facing = unit(player.velocity);
    if (input.interact)
        interact();
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
        if (p.kind == ProjectileKind::Homing) {
            auto wanted = sub(player.position, p.position);
            wanted.y = 0;
            p.velocity = mul(unit(add(unit(p.velocity), mul(unit(wanted), dt * 1.4f))), length(p.velocity));
        }
        if (p.kind == ProjectileKind::ReturningHead && p.life < 1.3f) {
            const auto *source = findEnemy(p.context.sourceEntity);
            if (!source || !source->alive || distance(p.position, source->position) < .8f)
                p.alive = false;
            else
                p.velocity = mul(unit(sub(source->position, p.position)), 14);
        }
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
            const auto terrainHit = arena.trace(p.position, end, p.radius);
            if (terrainHit.hit) {
                best = terrainHit.t;
                normal = terrainHit.normal;
                wall = true;
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
                    if (!enemy.alive || enemy.friendly || enemy.state == EnemyState::Buried ||
                        std::find(p.hitEntities.begin(), p.hitEntities.end(), enemy.id) !=
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
            event.armorPiercing = p.pierce > 0;
            if (wall) {
                audioCues.push(AudioCueKind::StoneHit, p.position);
                particleEffect(impactMaterial(p.position, normal), p.position, normal);
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
                const bool hurt = hurtPlayer(p.damage, p.context);
                if (hurt) particleEffect(ParticleEffect::Flesh, p.position, mul(event.direction,-1));
                if (hurt && p.kind == ProjectileKind::Hook) {
                    const auto *source = findEnemy(p.context.sourceEntity);
                    if (source && source->alive && arena.sight(player.position, source->position)) {
                        cancelMove();
                        player.pullTarget = source->position;
                        player.pullTime = 0.35f;
                    }
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
            if (p.hostile && (p.kind == ProjectileKind::SplitShot || p.kind == ProjectileKind::BurstShot)) {
                const int count = p.kind == ProjectileKind::SplitShot ? 2 : 6;
                for (int n = 0; n < count; ++n) {
                    Event child;
                    child.position = sub(p.position, mul(unit(p.velocity), .3f));
                    child.origin = p.origin;
                    child.direction = p.kind == ProjectileKind::SplitShot
                                          ? rotateY(unit(p.velocity), n ? .8f : -.8f)
                                          : rotateY({1, 0, 0}, float(n) * 2 * Pi / float(count));
                    child.damage = p.damage;
                    child.speed = 8;
                    child.hostile = true;
                    emit(child, p.context);
                }
            }
            if (p.hostile && (p.kind == ProjectileKind::Tar || p.kind == ProjectileKind::Flame)) {
                Enemy source;
                source.id = p.context.sourceEntity;
                source.position = p.position;
                monsterPatch(source, p.kind == ProjectileKind::Tar ? HazardKind::Tar : HazardKind::Fire,
                             p.position, .7f, .2f, 2.5f);
            }
            auto it = chains.find(p.context.chainId);
            if (it != chains.end() && it->second.active)
                --it->second.active;
        }
    std::erase_if(projectiles, [](const Projectile &p) { return !p.alive; });
}
void Simulation::step(const Input &input, float dt) {
    if (rewardOpen || shopOpen || letterOpen || finished || dead)
        return;
    stats.duration += dt;
    for (auto &burst : particleBursts) burst.age += dt;
    std::erase_if(particleBursts, [](const auto &burst) { return burst.age >= 3; });
    if (boss() || (arena.theme == MissionTheme::Canyon && room == finalRoom() && !roomClear))
        stats.bossDuration += dt;
    messageTime = std::max(0.0f, messageTime - dt);
    updatePlayer(input, dt);
    if (shopOpen || letterOpen)
        return;
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
    updateMoney(dt);
    // After the room transition, each actor advances either its idle or combat
    // clock exactly once. Ambient animation never runs attacks or summons.
    for (auto &progress : rooms)
        for (auto &enemy : progress.residents)
            if (enemy.alive)
                enemy.idleTime += dt;
    rebuildGrid();
    updateEnemies(dt);
    flushMonsterSpawns();
    rebuildGrid();
    updateProjectiles(dt);
    updateHazards(dt);
    drainEvents();
    flushMonsterSpawns();
    for (auto &v : visuals)
        v.life -= dt;
    std::erase_if(visuals, [](const VisualEffect &v) { return v.life <= 0; });
    std::erase_if(enemies, [](const Enemy &e) { return !e.alive; });
    collectChains();
    if (player.hp <= 0) {
        audioCues.push(AudioCueKind::PlayerDeath, player.position);
        dead = true;
        return;
    }
    if (debugScenario)
        return;
    if (!roomClear && roomThreats() == 0 && queue_.empty() && pendingMonsters_.empty())
        clearRoom();
}
} // namespace dw
