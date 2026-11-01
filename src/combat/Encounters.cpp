#include "combat/Simulation.hpp"
#include <stdexcept>

namespace dw {
const EnemyDefinition &enemyDefinition(EnemyKind kind) {
    static constexpr std::array<EnemyDefinition, size_t(EnemyKind::Count)> definitions{{
        {"Ash Rusher", 36, 0.6f, 2.6f, 0.45f, 0.8f},
        {"Dust Gunman", 48, 0.6f, 1.8f, 0.5f, 1.9f},
        {"Shotgun Outlaw", 80, 0.65f, 2.1f, 0.75f, 2.5f},
        {"Grave Sharpshooter", 58, 0.6f, 1.5f, 1.15f, 2.8f},
        {"Dynamite Prospector", 64, 0.6f, 1.7f, 0.65f, 3.1f},
        {"Ironhide Brute", 144, 0.8f, 1.4f, 0.85f, 1.5f},
        {"Railbreaker", 110, 0.8f, 1.8f, 0.9f, 2.6f},
        {"Hex Preacher", 72, 0.6f, 1.5f, 1.0f, 5.5f},
        {"Bell Ringer", 96, 0.7f, 1.4f, 1.1f, 3.8f},
        {"Hangman", 80, 0.65f, 1.8f, 0.85f, 3.0f},
        {"Cinder Spitter", 76, 0.7f, 1.5f, 0.75f, 3.8f},
        {"Ricochet Marshal", 72, 0.6f, 1.7f, 0.65f, 2.2f},
        {"Lantern Wraith", 64, 0.6f, 1.6f, 0.75f, 2.0f},
        {"Powder Husk", 48, 0.7f, 1.9f, 0.65f, 1.3f},
        {"Chainbound Outlaw", 68, 0.6f, 1.7f, 0.65f, 2.2f},
        {"Hollow Sheriff", 1100, 1.2f, 1, 0, 1.5f},
        {"Monster", 72, 0.6f, 2, .6f, 2.5f},
    }};
    return definitions.at(size_t(kind));
}

EntityId Simulation::spawn(EnemyKind kind, Vector3 position) {
    if (livingEnemies() >= limits.enemies) {
        suppress({}, "enemy capacity");
        return 0;
    }
    const auto &definition = enemyDefinition(kind);
    Enemy enemy;
    enemy.id = nextEntity_++;
    enemy.kind = kind;
    if(kind==EnemyKind::Boss)enemy.bossKind=BossKind::Sheriff;
    enemy.position = position;
    enemy.position.y = 0.85f;
    enemy.hp = enemy.maxHp = definition.hp;
    enemy.radius = definition.radius;
    enemy.facing = unit(sub(player.position, enemy.position));
    enemy.cooldown = encounterRng.real(0.6f, 1.8f);
    enemies.push_back(enemy);
    return enemy.id;
}

bool Simulation::placeEnemy(EnemyKind kind, Random &rng, bool spaced, MonsterId monster) {
    const auto &layout = arena.rooms[size_t(room)];
    const auto &bounds = layout.bounds;
    const float radius = monster ? content->monster(monster)->radius : enemyDefinition(kind).radius;
    auto valid = [&](Vector3 point) {
        // Terrain collision samples the perimeter: a larger clearance ring can
        // miss a narrow water/terrain feature touched by the actual body.
        if (arena.blocked(point, radius) || (radius < .8f && arena.blocked(point, .8f)) || arena.reservedSupplyCache(point,radius) ||
            distance(point, player.position) < 6)
            return false;
        if (spaced && !roomSpawnClear(point, radius))
            return false;
        if (spaced)
            for (const auto &other : enemies)
                if (other.alive && distance(point, other.position) < radius + other.radius + 0.35f)
                    return false;
        if(content->statue(monster)) {
            // Classic rooms and debug spawns also create solid statue bodies.
            // Test the eventual footprint before accepting it, just as the
            // progression-specific statue spawner does. Open floor at the
            // candidate alone does not prove that room routes stay open.
            const float half=radius*.85f;
            arena.movementBodies.push_back({{point.x-half,-1,point.z-half},{point.x+half,8,point.z+half}});
            bool connected=!arena.blocked(layout.center,.8f)&&!arena.blocked(layout.entry,.8f)&&
                !arena.path(layout.entry,layout.center,.8f).empty()&&!arena.path(layout.center,layout.objective,.8f).empty();
            for(int link:layout.passages)if(connected) {
                const int side=arena.passages[size_t(link)].rooms[0]==room?0:1;
                connected=!arena.path(layout.center,arena.doorApproach(link,side),.8f).empty();
            }
            arena.movementBodies.pop_back();
            if(!connected)return false;
        }
        return true;
    };
    auto create = [&](Vector3 point) {
        if (!(monster ? spawnMonster(monster, point) : spawn(kind, point)))
            return false;
        // Normal rooms use their own stream, independent of prior room visits.
        enemies.back().cooldown = rng.real(0.6f, 1.8f);
        if(const auto *lob=content->lobWalker(monster);lob&&!lob->attackFrames)
            enemies.back().cooldown=float(lob->initialMin+int(rng.bounded(unsigned(lob->initialMax-lob->initialMin+1))))/30;
        return true;
    };
    for (int attempt = 0; attempt < 240; ++attempt) {
        Vector3 point{rng.real(bounds.min.x + 1, bounds.max.x - 1), 0.85f,
                      rng.real(bounds.min.z + 1, bounds.max.z - 1)};
        if (valid(point))
            return create(point);
    }
    // Deterministic fallback for heavily clipped rooms or crowded cheat spawns.
    for (float x = bounds.min.x + 1; x < bounds.max.x - 1; x += 1)
        for (float z = bounds.min.z + 1; z < bounds.max.z - 1; z += 1)
            if (valid({x, 0.85f, z}))
                return create({x, 0.85f, z});
    return false;
}

void Simulation::spawnEnemies(int count) {
    // Random testing spawns use the same roster as the current mission.
    std::vector<MonsterId> monsters;
    for (const auto &d : content->monsters())
        if (d.natural)
            monsters.push_back(d.id);
    EntityId unpaired = 0;
    for (int i = 0; i < count && livingEnemies() < limits.enemies; ++i) {
        if (arena.theme == MissionTheme::Canyon) {
            const auto monster = monsters[encounterRng.bounded(uint32_t(monsters.size()))];
            if (!placeEnemy(EnemyKind::Monster, encounterRng, false, monster))
                break;
            continue;
        }
        EnemyKind kind =
            unpaired ? EnemyKind::Chainbound : EnemyKind(encounterRng.bounded(OrdinaryEnemyCount));
        if (kind == EnemyKind::Chainbound && !unpaired && i + 1 == count)
            kind = EnemyKind::Gunman;
        if (!placeEnemy(kind, encounterRng, false))
            break;
        if (kind == EnemyKind::Chainbound) {
            if (unpaired) {
                enemies.back().partner = unpaired;
                findEnemy(unpaired)->partner = enemies.back().id;
                unpaired = 0;
            } else
                unpaired = enemies.back().id;
        }
    }
}

int Simulation::roomEnemyCount(int index) const {
    const auto &layout = arena.rooms.at(size_t(index));
    if (layout.kind == RoomKind::Empty || layout.kind == RoomKind::Power || layout.kind == RoomKind::Shop || layout.kind==RoomKind::Service)
        return 0;
    if(surveyTutorial)return index==1?2:3;
    if(arena.profile.active())return layout.kind==RoomKind::Boss?1:int(floorEncounter(index).monsters.size());
    if (layout.kind == RoomKind::Boss && arena.theme == MissionTheme::Mine && !followup)
        return 1;
    return std::clamp(int(std::ceil(layout.usableArea() / 70.0f)), 4, 24);
}

const std::vector<Enemy> &Simulation::roomEnemies(int index) const {
    return index == room ? enemies : rooms.at(size_t(index)).residents;
}

bool Simulation::roomSpawnClear(Vector3 point, float radius) const {
    if (arena.roomAt(point) != room)
        return false;
    if (arena.reservedSupplyCache(point,radius))
        return false;
    // Any doorway can become the player's first entrance. Keep its landing clear
    // without moving an already-visible enemy when that doorway is crossed.
    for (int passage : arena.rooms[size_t(room)].passages) {
        const int side = arena.passages[size_t(passage)].rooms[0] == room ? 0 : 1;
        // Gates are open while residents are prepared. Reserve their complete
        // future collider, including corners outside the circular landing zone.
        if (sphereBox(point,radius,arena.passages[size_t(passage)].gates[size_t(side)]))
            return false;
        if (distance(point, arena.doorApproach(passage, side)) < radius + 2.5f)
            return false;
    }
    return true;
}

void Simulation::prepareRoomEnemies(int index) {
    std::erase_if(suppliedBombs,[&](const auto &bomb){return bomb.room==index&&bomb.state!=SuppliedBombState::Carried;});
    const int previousRoom = room;
    const auto previousPosition = player.position;
    const auto previousRng = encounterRng;
    auto active = std::move(enemies);
    auto pending = std::move(pendingMonsters_);
    pendingMonsters_ = {};
    enemies = {};
    enemies.reserve(limits.enemies);
    room = index;
    rooms[size_t(index)].formations.clear();
    rooms[size_t(index)].segmented.clear();
    rooms[size_t(index)].hornfel.reset();
    rooms[size_t(index)].plates.clear();
    rooms[size_t(index)].residents.clear();
    player.position = arena.rooms[size_t(index)].entry;
    spawnRoomEnemies();
    // Required components must exist in resident rooms before the player enters.
    // Retain births that cannot yet fit instead of discarding this room's queue.
    flushMonsterSpawns();
    if(arena.theme==MissionTheme::Canyon&&arena.profile.active()&&!surveyTutorial) {
        Random champions(seed_^uint64_t(index+1)*0x9e3779b97f4a7c15ULL);
        for(auto &body:enemies)if(championEligible(body.monster)&&champions.bounded(10000)<unsigned(content->championChance())) {
            std::vector<int> pool;for(int k=0;k<26;++k)if(const auto *p=content->champion(k);p&&arena.profile.sourceStage>=p->firstStage&&championTypeEligible(body.monster,k))pool.push_back(k);
            if(!pool.empty())makeChampion(body.id,pool[champions.bounded(unsigned(pool.size()))]);
        }
    }
    rooms[size_t(index)].pendingSpawns=std::move(pendingMonsters_);
    rooms[size_t(index)].residents = std::move(enemies);
    enemies = std::move(active);
    room = previousRoom;
    player.position = previousPosition;
    encounterRng = previousRng;
    pendingMonsters_ = std::move(pending);
    syncStatueBodies();
}

void Simulation::spawnRoomEnemies() {
    const auto &layout = arena.rooms[size_t(room)];
    if (layout.kind == RoomKind::Empty || layout.kind == RoomKind::Power || layout.kind == RoomKind::Shop || layout.kind==RoomKind::Service)
        return;
    if(surveyTutorial) {
        Random placement(seed_ ^ 0x5455544f5249414cULL ^ uint64_t(room));
        // Existing canyon creatures, limited to readable basic behaviors.
        for(int n=0;n<roomEnemyCount(room);++n) {
            if(!placeEnemy(EnemyKind::Monster,placement,true,monsterId(room==1?10:14,room==1?1:0)))break;
            enemies.back().hp=enemies.back().maxHp=24;
            enemies.back().cooldown=1.8f;
        }
        return;
    }
    if(arena.profile.active()) {
        if(layout.kind==RoomKind::Boss)spawnCanyonBoss();
        else spawnFloorEnemies();
        return;
    }
    if (room == finalRoom() && arena.theme == MissionTheme::Mine && !followup) {
        spawn(EnemyKind::Boss, layout.bossSpawn);
        return;
    }
    Random composition(seed_ ^ 0x524f4f4d47524f55ULL ^ (uint64_t(room + 1) * 0x9e3779b97f4a7c15ULL));
    if (arena.theme == MissionTheme::Canyon) {
        std::vector<MonsterId> pool;
        for (const auto &d : content->monsters())
            if (d.natural && !content->formation(d.id) && d.depth <= std::max(1, layout.depth))
                pool.push_back(d.id);
        const std::array<MonsterId, 6> basics{monsterId(10, 1), monsterId(14), monsterId(18),
                                        monsterId(21),    monsterId(11), monsterId(85)};
        const auto basic = basics[composition.bounded(uint32_t(basics.size()))];
        const auto special = pool[composition.bounded(uint32_t(pool.size()))];
        const auto &definition = *content->monster(special);
        const int count = roomEnemyCount(room);
        const int specialCount = definition.roomHazard ? 1 : std::max(1, count / 3);
        Random placement(seed_ ^ 0x535041574e524f4fULL ^ (uint64_t(room + 1) * 0xbf58476d1ce4e5b9ULL));
        EntityId leader = 0;
        for (int n = 0; n < count;) {
            auto id = n < specialCount ? special : basic;
            const bool companion = id == monsterId(26, 2) || id == monsterId(55, 2) || id == monsterId(35) ||
                                   id == monsterId(35, 2);
            if (companion && n + 2 > count)
                id = basic;
            const auto before = livingEnemies();
            if (!placeEnemy(EnemyKind::Monster, placement, true, id))
                break;
            if (id == monsterId(89)) {
                if (const auto *head = findEnemy(leader)) {
                    for (int direction = 0; direction < 16; ++direction) {
                        const auto point =
                            add(head->position, rotateY({1.45f, 0, 0}, float(direction) * Pi / 8));
                        if (!roomSpawnClear(point, .6f) || arena.blocked(point, .6f) ||
                            distance(point, player.position) < 6 || !arena.sight(point, head->position))
                            continue;
                        bool occupied = false;
                        for (const auto &other : enemies)
                            if (other.id != enemies.back().id &&
                                distance(point, other.position) < other.radius + .7f)
                                occupied = true;
                        if (!occupied) {
                            enemies.back().position = point;
                            enemies.back().partner = leader;
                            break;
                        }
                    }
                }
                leader = enemies.back().id;
            }
            flushMonsterSpawns(&placement, 6);
            n += int(livingEnemies() - before);
        }
        return;
    }
    const EnemyKind basic = composition.bounded(2) ? EnemyKind::Rusher : EnemyKind::Gunman;
    std::vector<EnemyKind> pool;
    for (int i = 0; i < OrdinaryEnemyCount; ++i) {
        const auto kind = EnemyKind(i);
        if (kind != basic && (layout.depth > 1 || i <= int(EnemyKind::Ironhide)))
            pool.push_back(kind);
    }
    for (size_t i = 0; i < pool.size(); ++i)
        std::swap(pool[i], pool[i + composition.bounded(uint32_t(pool.size() - i))]);
    const int count = roomEnemyCount(room);
    // Half the group uses a basic role. Each special occupies at most a quarter,
    // rounded up, so a large room never becomes twenty simultaneous hook/sniper casts.
    std::vector<EnemyKind> roster;
    for (int special = 0; special < 2; ++special) {
        const auto kind = pool[size_t(special)];
        int amount = std::max(1, count / 4);
        if (kind == EnemyKind::Chainbound)
            amount = std::max(2, amount - amount % 2);
        for (int i = 0; i < amount; ++i)
            roster.push_back(kind);
    }
    while (int(roster.size()) < count)
        roster.push_back(basic);

    Random placement(seed_ ^ 0x535041574e524f4fULL ^ (uint64_t(room + 1) * 0xbf58476d1ce4e5b9ULL));
    EntityId unpaired = 0;
    for (auto kind : roster) {
        if (!placeEnemy(kind, placement, true))
            break;
        auto &enemy = enemies.back();
        if (kind != EnemyKind::Chainbound)
            continue;
        if (!unpaired) {
            unpaired = enemy.id;
            continue;
        }
        enemy.partner = unpaired;
        auto *partner = findEnemy(unpaired);
        partner->partner = enemy.id;
        // Start the pair close enough to see the tether; never move through cover.
        for (int i = 0; i < 16; ++i) {
            Vector3 point = add(partner->position, rotateY({3, 0, 0}, float(i) * Pi / 8));
            if (!roomSpawnClear(point, enemy.radius) || arena.blocked(point, 0.8f) ||
                !arena.sight(point, partner->position) || distance(point, player.position) < 6)
                continue;
            bool occupied = false;
            for (const auto &other : enemies)
                occupied = occupied || (other.id != enemy.id && distance(point, other.position) < 1.6f);
            if (!occupied) {
                enemy.position = point;
                break;
            }
        }
        unpaired = 0;
    }
}
void Simulation::startPractice(int batch) {
    if(batch!=2&&batch!=3&&batch!=4)throw std::runtime_error("Unknown practice batch");
    int target=-1;
    for(int n=1;n<finalRoom();++n)if(arena.rooms[size_t(n)].kind==RoomKind::Combat&&arena.rooms[size_t(n)].story==StoryRoom::None){target=n;break;}
    if(target<0)throw std::runtime_error("No combat room available for practice");
    jumpDebug(target);clearRoomDebug();arena.sealRoom(room);
    const auto center=arena.rooms[size_t(room)].center;
    const std::vector<MonsterId> cohort=batch==2?std::vector<MonsterId>{monsterId(13),monsterId(14),monsterId(18),monsterId(85),monsterId(16)}:
        batch==3?std::vector<MonsterId>{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)}:
        std::vector<MonsterId>{monsterId(822),monsterId(823),monsterId(874),monsterId(889),monsterId(889)};
    for(auto id:cohort) {
        bool placed=false;const auto *d=content->monster(id);
        for(int ring=0;ring<32&&!placed;++ring)for(int n=0;n<24&&!placed;++n) {
            const auto at=add(center,rotateY({float(ring)*.75f,0,0},float(n)*2*Pi/24));
            if(arena.roomAt(at)!=room||distance(at,player.position)<4||
               (d->flying?arena.flightBlocked(at,d->radius,room):arena.blocked(at,d->radius))||
               std::any_of(enemies.begin(),enemies.end(),[&](const Enemy &e){return distance(e.position,at)<e.radius+d->radius+1;}))continue;
            if(!d->flying&&arena.path(player.position,at,d->radius).empty())continue;
            placed=spawnMonster(id,at)!=0;
        }
        if(!placed)throw std::runtime_error("Cannot place practice enemy safely");
    }
    moneyPickups.clear();
    items.clear();player.baseHealth=player.maxHp=player.hp=StartingHealth;player.shotDamage=RevolverDamage;
    player.hurt=player.fireCooldown=player.dodge=player.dodgeCooldown=0;
    stats={};roomClear=false;rooms[size_t(room)].cleared=false;rooms[size_t(room)].rewardTaken=true;
    rewardOpen=shopOpen=finished=dead=godMode=debugScenario=false;messageTime=0;
    arena.sealRoom(room);checkpointNeeded=true;
}
} // namespace dw
