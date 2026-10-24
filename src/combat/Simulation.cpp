#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include "items/ItemPools.hpp"
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace dw {
Simulation::Simulation(uint64_t seed, uint64_t runId, const WorldState &world, MissionTheme theme,
                       bool canyonRiver, bool tutorial, WitnessAccount account, int level, ExpeditionPacing pacing)
    : expedition(seed,tutorial,account,pacing),floor(level),
      arena(expedition.floorSeed(level), theme, canyonRiver, tutorial, expedition.storyAt(level),
            expedition.roomsOnFloor(level),expedition.dimensionsOnFloor(level),
            theme==MissionTheme::Canyon?expedition.profileOnFloor(level):FloorProfile{}),
      encounterRng(expedition.floorSeed(level) ^ 0x454e434f554e5445ULL),
      rewardRng(expedition.floorSeed(level) ^ 0x5245574152445354ULL),
      combatRng(expedition.floorSeed(level) ^ 0x434f4d424154524eULL), seed_(expedition.floorSeed(level)),
      runId_(runId), canyonRiver_(canyonRiver), startingWorld_(world) {
    if(account!=WitnessAccount::None&&account!=WitnessAccount::Rourke)
        throw std::invalid_argument("This testimony has not been authored yet.");
    surveyTutorial=tutorial;
    rooms.resize(arena.rooms.size());
    rescued = world.minersRescued;
    altarDestroyed = world.altarDestroyed;
    bossKilled = theme == MissionTheme::Canyon ? world.flags.contains("canyon_cleared") : world.bossDefeated;
    followup = bossKilled;
    if(surveyTutorial||testimony())rescued=altarDestroyed=bossKilled=followup=false;
    if(arena.profile.active())bossKilled=followup=false;
    player.position = arena.entrance;
    player.aim = arena.rooms[0].center;
    player.facing = unit(sub(player.aim, player.position));
    enemies.reserve(256);
    projectiles.reserve(4096);
    if (!tutorial && pacing != ExpeditionPacing::Classic)
        arena.prepareBreakables(seed_);
    for (int index = 0; index < arena.roomCount(); ++index) {
        if(arena.profile.active()) {
            rooms[size_t(index)].offers=drawItemOffers(arena.rooms[size_t(index)].kind==RoomKind::Boss?
                ItemPool::Boss:arena.rooms[size_t(index)].service==RoomService::Smuggler?ItemPool::Bargain:ItemPool::Armory,seed_^uint64_t(index+1)*0x9e3779b97f4a7c15ULL);
            continue;
        }
        if (arena.rooms[size_t(index)].kind != RoomKind::Power)
            continue;
        std::array<ItemId, ItemCount> pool{};
        const int available=tutorial||pacing==ExpeditionPacing::Classic?LegacyItemCount:ItemCount;
        for(int i=0;i<available;++i)pool[size_t(i)]=ItemId(i);
        for (int i = 0; i < 2; ++i) {
            const int other = i + int(rewardRng.bounded(uint32_t(available - i)));
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
    else if(testimony())announce(std::string(accountName(expedition.account))+" / Follow his route; examine what remains.",6);

}
int Simulation::storyRoomIndex() const {
    for(size_t i=0;i<arena.rooms.size();++i)if(arena.rooms[i].story!=StoryRoom::None)return int(i);
    return -1;
}
bool Simulation::storySeen() const {
    const auto expected=expedition.storyAt(floor);
    return expected==StoryRoom::None||std::any_of(evidence.begin(),evidence.end(),[&](const auto &e) {
        return e.floor==floor&&e.floorSeed==seed_&&e.account==expedition.account&&e.room==expected;
    });
}
bool Simulation::canUseFloorExit() const {
    return room==finalRoom()&&roomClear&&(!surveyTutorial||surveyRecovered)&&storySeen();
}
bool Simulation::advanceFloor() {
    if(!floorExitRequested||lastFloor()||dead||!canUseFloorExit())return false;
    // Construct first: a load failure leaves the previous floor and player intact.
    Simulation next(expedition.seed,runId_,startingWorld_,arena.theme,canyonRiver_,false,expedition.account,floor+1,
                    expedition.pacing);
    const auto spawn=next.player;
    next.player=player;next.player.position=spawn.position;next.player.aim=spawn.aim;next.player.facing=spawn.facing;
    next.player.velocity={};next.player.shootPose=next.player.dodge=next.player.pullTime=next.player.hurt=0;
    next.player.dodgeMoving=false;
    const auto entranceRooms=next.stats.rooms;next.stats=stats;next.stats.rooms+=entranceRooms;
    next.roomEnteredAt=next.stats.duration;
    for(auto &progress:next.rooms)for(auto &enemy:progress.residents)enemy.observedShots=next.stats.shots;
    next.items=items;next.keys=keys;next.dynamite=dynamite;next.dynamiteCooldown=dynamiteCooldown;
    next.moneyCollected=moneyCollected;next.moneySpent=moneySpent;
    next.rescued=rescued;next.altarDestroyed=altarDestroyed;next.evidence=evidence;
    next.godMode=godMode;next.limits=limits;next.audioEpoch=audioEpoch+1;
    next.checkpointNeeded=true;
    *this=std::move(next);
    return true;
}
void Simulation::announce(std::string text, float seconds, MessageKind kind) {
    messageKind=kind;
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
    if(arena.rooms[size_t(room)].service!=RoomService::None)return roomServiceName(arena.rooms[size_t(room)].service);
    if(arena.rooms[size_t(room)].story!=StoryRoom::None)return storyRoomName(arena.rooms[size_t(room)].story);
    if(surveyTutorial) {
        static constexpr const char *names[]={"Beyond the Gate","Dust Hollow","The Sheltered Bend","Last Approach","Survey Camp"};
        return names[size_t(room)];
    }
    if (arena.rooms[size_t(room)].kind == RoomKind::Shop)
        return "Trader's Rest";
    if (arena.rooms[size_t(room)].kind == RoomKind::Boss)
        return arena.profile.active()?(arena.profile.boss==BossKind::PowderForeman?"Foreman's Yard":
            arena.profile.boss==BossKind::StormMarshal?"Stormwatch Ring":"Ridgeback Hollow"):roomName(FinalRoom, arena.theme);
    if (arena.rooms[size_t(room)].kind == RoomKind::Power)
        return roomName(RoomCount - 2 - (finalRoom() - 1 - room), arena.theme);
    return roomName(room, arena.theme);
}
std::string Simulation::tutorialHint() const {
    if(surveyRecovered)return "The letter and records are safe. Follow the return lantern to Fort Mercy.";
    switch(room) {
    case 0:return "Click clear ground to walk, or use WASD. Follow the open passage into the badlands.";
    case 1:return roomClear?"The passage is open. Keep following the trail.":"Click an enemy or hold arrow keys to fire. Move with WASD; hold Shift to stand still.";
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
    announce(itemDefinition(item).name,2);
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
bool Simulation::rewardAvailable(int index) const {
    const auto &site=arena.rooms.at(size_t(index));const auto &progress=rooms.at(size_t(index));
    return !progress.rewardTaken&&(site.kind==RoomKind::Power||
        (arena.profile.active()&&site.kind==RoomKind::Boss&&progress.bossPaid&&progress.cleared));
}
Vector3 Simulation::rewardPosition(int index) const {
    const auto &site=arena.rooms.at(size_t(index));
    return site.kind==RoomKind::Boss?site.reward:site.objective;
}
void Simulation::offerReward() {
    const auto &progress = rooms[size_t(room)];
    if (!rewardAvailable(room))
        return;
    offers = progress.offers;
    rewardOpen = true;
}
void Simulation::chooseReward(int index) {
    auto &progress = rooms[size_t(room)];
    if (!rewardOpen || index < 0 || index >= int(offers.size()) || progress.rewardTaken ||
        !rewardAvailable(room)||items.size()>=256||!roomClear||
        distance(player.position,rewardPosition(room))>=2.6f||!arena.sight(player.position,rewardPosition(room)))
        return;
    progress.rewardTaken = true;
    if(arena.rooms[size_t(room)].kind==RoomKind::Power)++powerUpsTaken;
    grant(offers[size_t(index)]);
    rewardOpen = shopOpen = false;
}
void Simulation::enterRoom(int index) {
    roomEnteredAt=stats.duration;roomClearedAt=-10;messageTime=0;
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
    if (kind == RoomKind::Power || kind == RoomKind::Empty || kind == RoomKind::Shop || kind==RoomKind::Service) {
        if (!progress.cleared) {
            progress.cleared = true;
            ++stats.rooms;
        }
        roomClear = true;
        arena.sealRoom(-1);
    } else if (!roomClear) {
        cancelMove();
        arena.sealRoom(room);
        if (room == finalRoom() && !surveyTutorial)
            beginBossEncounter();
    } else {
        arena.sealRoom(-1);
    }
    checkpointNeeded = true;
}
void Simulation::clearRoom() {
    auto &progress = rooms[size_t(room)];
    if (progress.cleared)
        return;
    progress.cleared = roomClear = true;
    roomClearedAt=stats.duration;
    audioCues.push(AudioCueKind::RoomClear, player.position);
    if (room == finalRoom() && !surveyTutorial && arena.theme == MissionTheme::Canyon)
        bossKilled = true;
    for (auto &enemy : enemies)
        if (const auto *d = monsterDefinition(enemy.monster); d && d->roomHazard)
            enemy.alive = false;
    clearHazards(true);
    arena.sealRoom(-1);
    ++stats.rooms;
    checkpointNeeded = true;
    Event event;
    event.type = EventType::RoomCleared;
    queueRoot(event);

}
void Simulation::collectKeys() {
    for (auto &key : arena.keys) {
        if (!key.collected && rooms[size_t(key.room)].cleared &&
            distance(player.position, key.position) < 1.6f && arena.sight(player.position, key.position)) {
            key.collected = true;
            ++keys;
            audioCues.push(AudioCueKind::Pickup, key.position);
            announce("Key found",1.8f);
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
    }
    requestMove(arena.doorApproach(passage, 1 - side),false);
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
        requestMove(arena.doorApproach(passage, 1 - side),false);
        return;
    }
    requestMove(arena.doorApproach(passage, side),false);
    doorOnArrival_ = std::pair{passage, side};
}
void Simulation::startBoss(BossKind kind) {
    if(arena.profile.active()&&canyonBoss(kind)) {
        arena.profile.boss=kind;
        std::erase_if(arena.breakables,[&](const auto &prop){return prop.room==finalRoom();});
        arena.rebuildWalls();arena.prepareBossArena();
    }
    jumpDebug(finalRoom(), true);
}
void Simulation::beginBossEncounter() {
    if(const auto *e=boss();e&&canyonBoss(e->bossKind)) {
        announce(std::string(testimony()?accountName(expedition.account):arena.profile.name)+
                 " / "+bossName(e->bossKind)+". "+bossHint(*e),6);return;
    }
    if(testimony()) {announce(std::string(accountName(expedition.account))+
        (lastFloor()?" / THE DRY CREEK. Clear the room, then examine the evidence.":" / Clear the final room to continue deeper."),6);return;}
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
    debugNotice("CHEAT / full health and cooldowns reset");
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
    debugNotice("CHEAT / room cleared. All combat seals open.");
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
    debugNotice(std::string("CHEAT / ") + (restart ? "restarted " : "jumped to ") + roomName());
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
    debugNotice("STRESS / 100 enemies, 600 shots, all five effects", 6);
}
void Simulation::interact() {
    cancelMove();
    const auto &site=arena.rooms[size_t(room)];
    if(site.story!=StoryRoom::None&&roomClear&&distance(player.position,site.objective)<2.6f&&arena.sight(player.position,site.objective)) {
        if(!storySeen()) {
            evidence.push_back({site.story,expedition.account,floor,seed_});
            audioCues.push(AudioCueKind::Pickup,site.objective);checkpointNeeded=true;
        }
        storyOpen=site.story;return;
    }
    if(surveyTutorial && room==finalRoom() && roomClear &&
       distance(player.position,surveyPosition())<2.6f && arena.sight(player.position,surveyPosition())) {
        if(!surveyRecovered)audioCues.push(AudioCueKind::Pickup,surveyPosition());
        surveyRecovered=true;letterOpen=true;checkpointNeeded=true;
        announce("Bell's survey records and Eleanor's letter recovered. Return to the commander.",6);
        return;
    }
    if (room == arena.shopRoom || arena.rooms[size_t(room)].kind==RoomKind::Service) {
        openShop();
        if (shopOpen)
            return;
    }
    collectKeys();
    if (rewardAvailable(room) && distance(player.position,rewardPosition(room))<2.6f &&
        arena.sight(player.position,rewardPosition(room))) {
        offerReward();
        return;
    }
    if (legacyObjectives() && !rescued && distance(player.position, arena.miners) < 2.6f) {
        audioCues.push(AudioCueKind::Pickup, arena.miners);
        rescued = true;
        checkpointNeeded = true;
        announce("Six miners escape through the old shaft. Mary will remember.", 5);
        return;
    }
    if (legacyObjectives() && !altarDestroyed && distance(player.position, arena.altar) < 2.6f) {
        audioCues.push(AudioCueKind::Explosion, arena.altar);
        altarDestroyed = true;
        checkpointNeeded = true;
        effectVisual(arena.altar, 3, 0, 0.8f);
        announce("The altar breaks. Something loses your scent.", 5);
        return;
    }
    if (canUseFloorExit() && distance(player.position, arena.exit) < 2.8f) {
        if(lastFloor())finished=true;
        else floorExitRequested=true;
        return;
    }
    if(room==finalRoom()&&roomClear&&!storySeen()&&distance(player.position,arena.exit)<2.8f) {
        return; // The persistent exit marker explains the missing evidence.
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
        debugVictory_=true;
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
    s.seed = expedition.seed;
    s.floor=floor;s.floorCount=expedition.floorCount;s.pacing=expedition.pacing;s.account=expedition.account;s.evidence=evidence;
    s.expedition = surveyTutorial?SurveyExpeditionTitle:testimony()?RourkeExpeditionTitle:missionTheme(arena.theme).title;
    s.startingContext = CampaignStore::worldContext(startingWorld_);
    s.rescued = legacyObjectives()&&rescued;
    s.altarDestroyed = legacyObjectives()&&altarDestroyed;
    s.bossKilled = legacyObjectives()&&bossKilled&&(lastFloor()||debugVictory_);
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
    } else {
        p.attack=event.attack?*event.attack:playerAttack(*this,event.damage,event.lastRound,event.speed);
        p.attack.heading=unit(event.direction);
        if(!event.attack)p.attack.bounces+=event.bounces;
        p.damage=p.attack.damage;p.radius=p.attack.radius;p.life=p.attack.life;
        p.velocity=mul(unit(event.direction),p.attack.speed);
        p.bounces=p.attack.bounces;p.pierce=p.attack.pierce;
        p.returning=event.returning&&p.attack.returnRange>0;
        if(p.returning)p.bounces=0;
    }
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
                if(canyonBoss(target->bossKind))rewardCanyonBoss(*target);
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
        if(!e.compactBlast)particleEffect(ParticleEffect::Explosion,e.position,{0,1,0},e.radius/3.3f);
        effectVisual(e.position,e.radius,0,e.compactBlast?.18f:.5f);
        resolveExplosion(e);
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
    player.aim = input.aimDirection ? add(player.position, mul(*input.aimDirection, 10)) : input.aim;
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
    // Keep directional aim attached to the player through movement, dodges and pulls.
    if (input.aimDirection)
        player.aim = add(player.aim, sub(player.position, previousPosition));
    kickDynamiteOnContact(previousPosition);
    if (input.placeDynamite)
        placeDynamite();
    else if (input.dynamiteTarget)
        throwDynamite(*input.dynamiteTarget);
    if (input.fire && player.fireCooldown <= 0 && !input.dynamiteTarget && !input.placeDynamite) {
        player.shootPose = 0.32f;
        player.fireCooldown = primaryCadence(*this);
        ++stats.shots;
        audioCues.push(AudioCueKind::Shot, player.position);
        Event e;
        e.direction = unit(sub(player.aim, player.position));
        e.damage = player.shotDamage;
        e.lastRound = player.nextRound == 6;
        e.attack=playerAttack(*this,e.damage,e.lastRound);
        player.nextRound = player.nextRound % 6 + 1;
        // One root per trigger pull: pellet count must not multiply chain budgets
        // or advance the cylinder. Descendants carry the resolved specification.
        e.context={nextChain_++,0,0,-1};
        const int pellets=primaryPellets(*this);
        const auto aim=e.direction;
        for(int i=0;i<pellets;++i) {
            e.direction=rotateY(aim,(float(i)-float(pellets-1)*.5f)*(e.attack->rail?.16f:.14f));
            e.position=add(player.position,mul(e.direction,.7f));
            if(!arena.clear(player.position,e.position,e.attack->radius))e.position=player.position;
            e.origin=e.position;
            accept(e);
        }
        e.direction=aim;e.position=add(player.position,mul(aim,.7f));
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
        if(!p.hostile)updateGuidance(p,dt);
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
            if(!p.hostile&&!p.returning&&p.attack.returnRange>0&&p.traveled>=p.attack.returnRange-.001f)
                beginReturn(p);
            float slice=remaining;
            if(!p.hostile&&!p.returning&&p.attack.returnRange>0)
                slice=std::min(slice,(p.attack.returnRange-p.traveled)/std::max(.01f,length(p.velocity)));
            Vector3 end = add(p.position, mul(p.velocity, slice));
            float best = 2;
            Vector3 normal{};
            EntityId target = 0;
            bool wall = false, playerHit = false, caught = false;
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
            } else if(!p.phaseSpent)
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
            if(p.returning) {
                const auto hit=segmentSphere(p.position,end,player.position,.5f);
                if(hit<best){best=hit;wall=false;caught=true;}
            }
            if (best > 1) {
                p.traveled+=distance(p.position,end);
                p.position = end;
                remaining-=slice;
                continue;
            }
            p.traveled+=distance(p.position,end)*best;
            p.position = add(p.position, mul(sub(end, p.position), best));
            remaining-=slice*best;
            if(caught){p.alive=false;break;}
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
            if(!p.hostile) {
                event.attack=p.attack;event.projectile=p.id;event.remainingLife=p.life;
                event.remainingBounces=p.bounces;event.remainingPierce=std::max(0,p.pierce-1);
                event.returning=p.returning;
            }
            if (wall) {
                for (auto &prop : arena.breakables) {
                    if (!prop.solid() || prop.kind != BreakableKind::PowderBarrel) continue;
                    if (sphereBox(p.position, p.radius + .025f, prop.bounds))
                        hitBreakable(prop, p.damage, false);
                }
                audioCues.push(AudioCueKind::StoneHit, p.position);
                particleEffect(impactMaterial(p.position, normal), p.position, normal);
                if (p.bounces > 0 && length(normal) > 0.5f) {
                    --p.bounces;
                    ++stats.bounces;
                    p.velocity = sub(p.velocity, mul(normal, 2 * dot(p.velocity, normal)));
                    p.position = add(p.position, mul(normal, 0.02f));
                    p.guidedTarget=0;p.guidanceTime=0;
                    event.type = EventType::ProjectileBounce;
                    emit(event, p.context);
                    effectVisual(p.position, 0.25f, 3, 0.12f);
                } else if(!p.hostile&&!p.returning&&p.attack.returnRange>0) {
                    p.position=add(p.position,mul(normal,.025f));beginReturn(p);
                } else p.alive=false;
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
                event.explosiveHit=p.attack.capDamage>0&&!p.capSpent;
                p.capSpent=p.capSpent||event.explosiveHit;
                event.type = EventType::ProjectileHit;
                emit(event, p.context);
                p.hitEntities.push_back(target);
                p.guidedTarget=0;p.guidanceTime=0;
                if (p.pierce > 0) {
                    --p.pierce;
                    p.position = add(p.position, mul(unit(p.velocity), 0.02f));
                } else if(p.attack.returnRange>0) {
                    // A plain returning shot damages one body per leg. It keeps
                    // traveling until its turn; Rail/Judas add bodies to each leg.
                    p.phaseSpent=true;
                    p.position=add(p.position,mul(unit(p.velocity),.02f));
                } else p.alive=false;
            }
        }
    }
    for (const auto &p : projectiles)
        if (!p.alive) {
            if (!p.cancelled && p.hostile && (p.kind == ProjectileKind::SplitShot || p.kind == ProjectileKind::BurstShot)) {
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
            if (!p.cancelled && p.hostile && (p.kind == ProjectileKind::Tar || p.kind == ProjectileKind::Flame)) {
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
    if (rewardOpen || shopOpen || letterOpen || storyOpen!=StoryRoom::None || floorExitRequested || finished || dead)
        return;
    stats.duration += dt;
    for (auto &burst : particleBursts) burst.age += dt;
    std::erase_if(particleBursts, [](const auto &burst) { return burst.age >= 3; });
    if (boss() || (arena.theme == MissionTheme::Canyon && room == finalRoom() && !roomClear))
        stats.bossDuration += dt;
    messageTime = std::max(0.0f, messageTime - dt);
    updatePlayer(input, dt);
    if (shopOpen || rewardOpen || letterOpen || storyOpen!=StoryRoom::None || floorExitRequested || finished)
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
    updateBreakables(dt);
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
