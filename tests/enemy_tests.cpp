#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

namespace {
using namespace dw;
void check(bool condition, const std::string &message) {
    if (!condition)
        throw std::runtime_error(message);
}
void tick(Simulation &run, int frames) {
    for (int i = 0; i < frames; ++i)
        run.step({});
}
Simulation fixture() {
    Simulation run(1866, 1, {});
    run.arena = Arena{};
    run.arena.bounds = {{-25, -1, -25}, {25, 4, 25}};
    run.arena.walls = {{{-26, -1, -26}, {-25, 4, 26}},
                       {{25, -1, -26}, {26, 4, 26}},
                       {{-26, -1, -26}, {26, 4, -25}},
                       {{-26, -1, 25}, {26, 4, 26}}};
    for (auto &room : run.arena.rooms) {
        room.bounds = run.arena.bounds;
        room.floors = {{{-25, -0.4f, -25}, {25, 0, 25}}};
    }
    run.player.position = {0, 0.85f, 8};
    run.debugScenario = true;
    run.roomClear = false;
    return run;
}
EntityId prepare(Simulation &run, EnemyKind kind, Vector3 at = {0, 0.85f, 0}) {
    const auto id = run.spawn(kind, at);
    run.findEnemy(id)->cooldown = 0;
    run.step({});
    return id;
}
void resolveWindup(Simulation &run, EnemyKind kind) {
    tick(run, int(std::ceil(enemyDefinition(kind).windup / Tick)) + 1);
}
void damage(Simulation &run, EntityId id, float amount, Vector3 direction = {0, 0, -1}, bool piercing = false,
            bool area = false) {
    Event hit;
    hit.type = EventType::Damage;
    hit.target = id;
    hit.damage = amount;
    hit.direction = direction;
    hit.armorPiercing = piercing;
    hit.areaDamage = area;
    run.queueRoot(hit);
    run.drainEvents();
}

void testMeleeAndGuns() {
    for (auto kind : {EnemyKind::Rusher, EnemyKind::Ironhide, EnemyKind::PowderHusk}) {
        auto run = fixture();
        run.player.position.z = 1.5f;
        auto id = prepare(run, kind);
        check(run.findEnemy(id)->state == EnemyState::Windup && run.player.hp == StartingHealth,
              "melee attacks give warning before damage");
        resolveWindup(run, kind);
        check(run.player.hp < StartingHealth, "a completed melee swing damages a player in reach");
        auto miss = fixture();
        miss.player.position.z = 1.5f;
        prepare(miss, kind);
        miss.player.position.x = 5;
        resolveWindup(miss, kind);
        check(miss.player.hp == StartingHealth, "moving out of a committed melee attack avoids damage");
    }
    for (auto kind : {EnemyKind::Gunman, EnemyKind::Shotgun, EnemyKind::Sharpshooter, EnemyKind::Marshal}) {
        auto run = fixture();
        auto id = prepare(run, kind);
        check(run.findEnemy(id)->state == EnemyState::Windup && run.projectiles.empty(),
              "ranged attacks have a visible windup");
        resolveWindup(run, kind);
        check(run.projectiles.size() == (kind == EnemyKind::Shotgun ? 5 : 1),
              "weapon-specific projectile pattern");
        if (kind == EnemyKind::Shotgun)
            check(run.projectiles.front().velocity.x * run.projectiles.back().velocity.x < 0,
                  "shotgun spreads to both sides of its aim");
        if (kind == EnemyKind::Sharpshooter)
            check(std::abs(length(run.projectiles.front().velocity) - 32) < 0.01f,
                  "sharpshooter fires its faster high-damage round");
        if (kind == EnemyKind::Marshal) {
            check(run.projectiles.front().bounces == 1, "marshal has exactly one bounce");
            run.player.position.x = 8;
            tick(run, 180);
            check(run.stats.bounces > 0, "marshal bullet actually reflects from a wall");
        }
    }
}

void testArmorAndSupport() {
    auto run = fixture();
    auto id = run.spawn(EnemyKind::Ironhide, {0, 0.85f, 0});
    damage(run, id, 20);
    check(std::abs(run.findEnemy(id)->hp - 137) < 0.01f, "frontal plate reduces rather than negates damage");
    damage(run, id, 20, {0, 0, 1});
    check(std::abs(run.findEnemy(id)->hp - 117) < 0.01f, "rear shots bypass armor");
    damage(run, id, 20, {0, 0, -1}, true);
    damage(run, id, 20, {0, 0, -1}, false, true);
    check(std::abs(run.findEnemy(id)->hp - 77) < 0.01f, "piercing and area damage bypass the plate");
    run.player.position = {0, 0.85f, -8};
    tick(run, 1);
    check(run.findEnemy(id)->facing.z > 0.99f, "brute cannot turn instantly when flanked");

    auto support = fixture();
    auto preacher = prepare(support, EnemyKind::Preacher);
    resolveWindup(support, EnemyKind::Preacher);
    check(support.findEnemy(preacher)->aura > 0, "preacher completes a protective chant");
    auto ally = support.spawn(EnemyKind::Gunman, {2, 0.85f, 0});
    damage(support, ally, 20);
    check(std::abs(support.findEnemy(ally)->hp - 35) < 0.01f, "nearby allies receive limited protection");
    damage(support, preacher, 1);
    check(support.findEnemy(preacher)->aura == 0, "shooting preacher interrupts its protection");
    damage(support, ally, 20);
    check(std::abs(support.findEnemy(ally)->hp - 15) < 0.01f, "interrupted aura no longer reduces damage");
    support.findEnemy(preacher)->aura = 4;
    support.arena.walls.push_back({{0.7f, 0, -2}, {1.2f, 3, 2}});
    damage(support, ally, 10);
    check(std::abs(support.findEnemy(ally)->hp - 5) < 0.01f, "protection does not pass through cover");
}

void testHazards() {
    for (auto kind : {EnemyKind::Prospector, EnemyKind::Spitter}) {
        auto run = fixture();
        auto source = prepare(run, kind);
        resolveWindup(run, kind);
        check(run.hazards.size() == 1 && run.player.hp == StartingHealth,
              "thrown attacks mark the landing area before damage");
        run.findEnemy(source)->state = EnemyState::Stunned;
        run.findEnemy(source)->stateTime = 100;
        tick(run, 35);
        check(run.player.hp == StartingHealth, "bomb/oil travel time is safe");
        tick(run, 40);
        check(run.player.hp < StartingHealth, "standing in the warned landing zone causes damage");
        if (kind == EnemyKind::Spitter) {
            const float hp = run.player.hp;
            tick(run, 40);
            check(run.player.hp < hp && !run.hazards.empty(), "fire persists and damages over time");
        }
        run.godMode = true;
        tick(run, 300);
        check(run.hazards.empty() && run.chains.empty(), "expired hazards release their chain accounting");
    }
    auto powder = fixture();
    const auto husk = powder.spawn(EnemyKind::PowderHusk, {0, 0.85f, 0});
    const auto victim = powder.spawn(EnemyKind::Rusher, {1, 0.85f, 0});
    powder.findEnemy(victim)->state = EnemyState::Stunned;
    powder.findEnemy(victim)->stateTime = 100;
    damage(powder, husk, 1000);
    damage(powder, husk, 1000);
    check(powder.hazards.size() == 1 && powder.stats.kills == 1, "one delayed fuse per powder death");
    tick(powder, 40);
    check(powder.findEnemy(victim)->alive, "powder blast does not damage allies before fuse expires");
    tick(powder, 40);
    check(powder.livingEnemies() == 0 && powder.stats.kills == 2 && powder.stats.largestKillChain == 2,
          "powder blast kills allies and retains the original kill-chain provenance");
    tick(powder, 40);
    check(powder.chains.empty(), "powder death chain is reclaimed");

    auto limited = fixture();
    limited.limits.hazards = 1;
    for (int i = 0; i < 3; ++i)
        limited.spawn(EnemyKind::PowderHusk, {float(i) * 3, 0.85f, 0});
    limited.killAll();
    check(limited.hazards.size() == 1 && limited.stats.suppressed == 2,
          "simultaneous death fuses respect and report the hazard budget");
    limited.player.pullTime = 1;
    limited.clearRoomDebug();
    check(limited.hazards.empty() && limited.chains.empty() && limited.player.pullTime == 0,
          "clear-room cheat cancels a live fuse, pull and held chain accounting");
}

void testChargeAndRing() {
    auto charge = fixture();
    charge.godMode = true;
    charge.player.position.z = 3;
    charge.arena.walls.push_back({{-3, 0, 5}, {3, 3, 6}});
    const auto id = prepare(charge, EnemyKind::Railbreaker);
    resolveWindup(charge, EnemyKind::Railbreaker);
    tick(charge, 25);
    check(charge.findEnemy(id)->state == EnemyState::Stunned && charge.findEnemy(id)->position.z < 4.3f,
          "railbreaker collides with cover and enters a punishable stun");
    for (int mode = 0; mode < 3; ++mode) {
        auto ring = fixture();
        ring.player.position.z = 5;
        auto bell = prepare(ring, EnemyKind::BellRinger);
        if (mode == 1)
            ring.arena.walls.push_back({{-4, 0, 2}, {4, 3, 3}});
        resolveWindup(ring, EnemyKind::BellRinger);
        ring.findEnemy(bell)->state = EnemyState::Stunned;
        ring.findEnemy(bell)->stateTime = 100;
        if (mode == 2) {
            ring.player.dodge = 1.6f;
            ring.player.dodgeDirection = {};
        }
        tick(ring, 95);
        check(ring.player.hp == (mode == 0 ? StartingHealth - 16 : StartingHealth),
              "bell ring hits once, respects cover and can be dodged");
    }
}

void testHookWraithAndChain() {
    for (int mode = 0; mode < 3; ++mode) {
        auto hook = fixture();
        prepare(hook, EnemyKind::Hangman);
        resolveWindup(hook, EnemyKind::Hangman);
        check(hook.projectiles.size() == 1 && hook.projectiles.front().kind == ProjectileKind::Hook,
              "hangman launches a real colliding hook");
        if (mode == 1)
            hook.arena.walls.push_back({{-3, 0, 4}, {3, 3, 5}});
        if (mode == 2) {
            hook.player.dodge = 1;
            hook.player.dodgeDirection = {};
        }
        tick(hook, 48);
        if (mode == 0)
            check(hook.player.hp < StartingHealth && hook.player.position.z < 6,
                  "a connected hook pulls the player toward its caster");
        else
            check(hook.player.hp == StartingHealth && hook.player.pullTime == 0 &&
                      hook.player.position.z == 8,
                  "cover and dodge prevent both hook damage and pull");
    }
    auto wraith = fixture();
    const auto ghost = prepare(wraith, EnemyKind::Wraith);
    check(wraith.findEnemy(ghost)->state == EnemyState::Teleporting, "wraith marks a destination first");
    const auto before = wraith.findEnemy(ghost)->position;
    tick(wraith, 35);
    check(distance(wraith.findEnemy(ghost)->position, before) == 0 && wraith.projectiles.empty(),
          "wraith remains visible and cannot attack during teleport warning");
    tick(wraith, 22);
    check(distance(wraith.findEnemy(ghost)->position, before) > 1 && wraith.projectiles.empty() &&
              !wraith.arena.blocked(wraith.findEnemy(ghost)->position, 0.6f),
          "wraith arrives on clear floor and gives another warning before attacking");
    tick(wraith, 48);
    check(wraith.stats.projectiles == 3, "wraith attacks only after its arrival windup");

    auto chain = fixture();
    auto first = chain.spawn(EnemyKind::Chainbound, {-2, 0.85f, 8});
    auto second = chain.spawn(EnemyKind::Chainbound, {2, 0.85f, 8});
    chain.findEnemy(first)->partner = second;
    chain.findEnemy(second)->partner = first;
    check(chain.chainActive(*chain.findEnemy(first)), "a visible pair has an active tether");
    chain.step({});
    check(chain.player.hp == StartingHealth - 12, "crossing the chain damages the player");
    chain.arena.walls.push_back({{-0.5f, 0, 7}, {0.5f, 3, 9}});
    check(!chain.chainActive(*chain.findEnemy(first)), "cover breaks the damaging chain");
    damage(chain, second, 1000);
    chain.step({});
    check(chain.findEnemy(first)->kind == EnemyKind::Gunman && chain.findEnemy(first)->partner == 0,
          "killing one outlaw breaks the pair without spawning a replacement");
}

void testAreaAndEncounters() {
    auto run = fixture();
    auto &room = run.arena.rooms[0];
    room.kind = RoomKind::Combat;
    room.floors = {{{0, -0.4f, 0}, {28, 0, 20}}};
    check(room.usableArea() == 560 && run.roomEnemyCount(0) == 8,
          "560 usable square units support eight enemies");
    room.floors = {{{0, -0.4f, 0}, {28, 0, 10}}, {{0, -0.4f, 10}, {14, 0, 20}}};
    check(room.usableArea() == 420 && run.roomEnemyCount(0) == 6,
          "an L-shaped room uses its real floor, not its unchanged bounding box");
    room.obstacles = {{{0, 0, 0}, {7, 2, 10}}};
    check(room.usableArea() == 350 && run.roomEnemyCount(0) == 5, "cover reduces the population budget");
    room.floors = {{{0, -0.4f, 0}, {100, 0, 100}}};
    check(run.roomEnemyCount(0) == 24, "large rooms have a bounded population");
    for (auto kind : {RoomKind::Empty, RoomKind::Power}) {
        room.kind = kind;
        check(run.roomEnemyCount(0) == 0, "quiet rooms and power caches never receive a combat population");
    }
    room.kind = RoomKind::Boss;
    check(run.roomEnemyCount(0) == 1, "boss remains a single encounter");

    std::set<EnemyKind> seen;
    std::set<int> populations;
    float minArea = 100000, maxArea = 0;
    for (uint64_t seed = 0; seed < 32; ++seed) {
        Simulation generated(seed, 1, {});
        for (int index = 0; index < RoomCount; ++index) {
            const auto &layout = generated.arena.rooms[size_t(index)];
            generated.player.position = layout.entry;
            generated.enterRoom(index);
            check(int(generated.livingEnemies()) == generated.roomEnemyCount(index),
                  "actual initial population matches the generated room's area budget");
            if (layout.kind != RoomKind::Combat)
                continue;
            populations.insert(int(generated.livingEnemies()));
            minArea = std::min(minArea, layout.usableArea());
            maxArea = std::max(maxArea, layout.usableArea());
            std::set<int> kinds;
            for (const auto &enemy : generated.enemies) {
                check(enemy.kind != EnemyKind::Monster,
                      "mine encounters keep the Western roster exclusively");
                seen.insert(enemy.kind);
                kinds.insert(enemy.kind == EnemyKind::Monster ? enemy.monster : -int(enemy.kind) - 1);
                check(generated.arena.roomAt(enemy.position) == index &&
                          !generated.arena.blocked(enemy.position, enemy.radius) &&
                          distance(enemy.position, generated.player.position) >= 6,
                      "every type spawns on safe room floor away from the entrance");
                for (const auto &other : generated.enemies)
                    if (enemy.id != other.id)
                        check(distance(enemy.position, other.position) >= enemy.radius + other.radius,
                              "normal encounter bodies never overlap at spawn");
                if (enemy.kind == EnemyKind::Chainbound) {
                    const auto *partner = generated.findEnemy(enemy.partner);
                    check(partner && partner->kind == EnemyKind::Chainbound && partner->partner == enemy.id,
                          "chainbound enemies occupy two existing slots and always have a partner");
                }
            }
            check(kinds.size() >= 1 && kinds.size() <= 3,
                  "rooms use a readable mixture of two or three roles");
        }
    }
    check(seen.size() == OrdinaryEnemyCount && populations.size() >= 8,
          "seeded mines include all original enemy types and varied population sizes");
    std::cout << "POPULATION seeds=32 area=" << minArea << ".." << maxArea
              << " enemies=" << *populations.begin() << ".." << *populations.rbegin()
              << " types=" << seen.size() << '\n';
    Simulation a(1866, 1, {}), b(1866, 2, {});
    b.jumpDebug(4);
    b.spawnEnemies(20);
    for (int i = 0; i < 1000; ++i)
        b.combatRng.next();
    a.jumpDebug(2);
    b.jumpDebug(2);
    check(a.enemies.size() == b.enemies.size(), "visit order never changes room population");
    for (size_t i = 0; i < a.enemies.size(); ++i)
        check(a.enemies[i].kind == b.enemies[i].kind && a.enemies[i].monster == b.enemies[i].monster &&
                  distance(a.enemies[i].position, b.enemies[i].position) == 0 &&
                  a.enemies[i].cooldown == b.enemies[i].cooldown,
              "room composition, placements and initial timers reproduce independently of prior fights");
    a.clearRoomDebug();
    check(a.hazards.empty() && a.chains.empty(), "clear-room cheat removes delayed attacks and accounting");
}
} // namespace

int main() {
    try {
        testMeleeAndGuns();
        testArmorAndSupport();
        testHazards();
        testChargeAndRing();
        testHookWraithAndChain();
        testAreaAndEncounters();
        std::cout << "PASS fifteen enemy behaviors, tells, counters, hazards and seeded area-based groups\n";
    } catch (const std::exception &error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
