#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
void check(bool condition, const std::string &message) {
    if (!condition)
        throw std::runtime_error(message);
}
void tick(dw::Simulation &run, int frames) {
    for (int i = 0; i < frames; ++i)
        run.step({});
}
dw::Simulation fixture() {
    dw::Simulation run(1866, 1, {});
    // Item/collision contracts use a fixed arena, independent of procedural content.
    run.arena = dw::Arena{};
    run.arena.walls = {{{-16, -1, -16}, {16, 2, -15}}, {{-16, -1, 15}, {16, 2, 16}},
                       {{-16, -1, -15}, {-15, 2, 15}}, {{15, -1, -15}, {16, 2, 15}},
                       {{-7, 0, -4}, {-5, 2.5f, 0}},   {{5, 0, 1}, {7, 2.5f, 5}},
                       {{-11, 0, 5}, {-8, 1.8f, 7}},   {{8, 0, -6}, {11, 1.8f, -4}}};
    for (auto &room : run.arena.rooms) {
        room.bounds = {{-15, 0, -15}, {15, 3, 15}};
        room.exit = run.arena.exit;
    }
    run.debugScenario = true;
    run.godMode = true;
    run.player.position = {0, 0.85f, 12};
    return run;
}
void fire(dw::Simulation &run, Vector3 position, Vector3 direction, float damage = 24, bool last = false) {
    dw::Event shot;
    shot.position = shot.origin = position;
    shot.direction = direction;
    shot.damage = damage;
    shot.lastRound = last;
    run.queueRoot(shot);
    run.drainEvents();
}
void testCollision() {
    auto hit = dw::segmentBox({0, 1, 5}, {0, 1, -5}, {{-1, 0, -1}, {1, 2, 1}});
    check(hit.hit && std::abs(hit.t - 0.4f) < 0.001f && hit.normal.z == 1, "swept box hit and normal");
    check(!dw::segmentBox({0, 3, 5}, {0, 3, -5}, {{-1, 0, -1}, {1, 2, 1}}).hit, "collision respects height");
    check(dw::segmentSphere({0, 1, 5}, {0, 1, -5}, {0, 1, 0}, 0.5f) < 1,
          "fast projectile cannot tunnel through sphere");
    check(dw::segmentSphere({0, 3, 5}, {0, 3, -5}, {0, 1, 0}, 0.5f) > 1, "sphere collision respects height");
}
void testItems() {
    {
        auto run = fixture();
        run.grant(dw::ItemId::Ricochet);
        fire(run, {13, 0.85f, 10}, {1, 0, 0});
        tick(run, 12);
        check(run.stats.bounces > 0, "ricochet reflects a wall impact");
        check(!run.projectiles.empty() && run.projectiles.front().velocity.x < 0,
              "ricochet reverses direction");
    }
    {
        auto run = fixture();
        run.grant(dw::ItemId::Split);
        run.spawn(dw::EnemyKind::Rusher, {0, 0.85f, 0});
        fire(run, {0, 0.85f, 4}, {0, 0, -1});
        tick(run, 15);
        check(run.stats.splits > 0 && run.stats.projectiles >= 3, "hit emits split projectiles");
    }
    {
        auto run = fixture();
        run.grant(dw::ItemId::Judas);
        run.spawn(dw::EnemyKind::Rusher, {0, 0.85f, 0});
        run.spawn(dw::EnemyKind::Rusher, {0, 0.85f, -2});
        fire(run, {0, 0.85f, 4}, {0, 0, -1}, 100, true);
        tick(run, 22);
        check(run.stats.kills == 2, "last round penetrates two enemies");
        check(run.player.maxHp == 80, "Judas applies its health cost to the 100 starting health");
    }
    {
        auto run = fixture();
        run.grant(dw::ItemId::Powder);
        auto first = run.spawn(dw::EnemyKind::Rusher, {0, 0.85f, 0});
        auto second = run.spawn(dw::EnemyKind::Rusher, {1, 0.85f, 0});
        run.findEnemy(first)->hp = 10;
        run.findEnemy(second)->hp = 10;
        fire(run, {0, 0.85f, 3}, {0, 0, -1}, 100);
        tick(run, 20);
        check(run.stats.kills == 2 && run.stats.explosions >= 2, "explosion kills trigger another explosion");
        check(run.stats.largestKillChain == 2, "kill chain includes explosion descendants");
    }
    {
        auto run = fixture();
        run.grant(dw::ItemId::Ghost);
        run.grant(dw::ItemId::Ricochet);
        run.spawn(dw::EnemyKind::Rusher, {0, 0.85f, 0});
        fire(run, {0, 0.85f, 3}, {0, 0, -1}, 100);
        tick(run, 12);
        check(run.stats.ghosts > 0, "kill emits ghost shot");
        bool inherited = false;
        for (const auto &p : run.projectiles)
            if (p.ghost && p.bounces > 0)
                inherited = true;
        check(inherited, "ghost inherits ricochet modifier");
    }
    {
        auto run = fixture();
        run.grant(dw::ItemId::Ricochet);
        run.grant(dw::ItemId::Split);
        run.spawn(dw::EnemyKind::Rusher, {11, 0.85f, 10});
        fire(run, {13, 0.85f, 10}, {1, 0, 0});
        tick(run, 20);
        check(run.stats.bounces > 0 && run.stats.splits > 0, "bounced hit triggers split");
    }
    {
        auto run = fixture();
        auto id = run.spawn(dw::EnemyKind::Rusher, {0, 0.85f, 0});
        for (int i = 0; i < 3; ++i) {
            dw::Event e;
            e.type = dw::EventType::Damage;
            e.target = id;
            e.damage = 100;
            run.queueRoot(e);
        }
        run.drainEvents();
        check(run.stats.kills == 1, "queued duplicate hits kill once");
    }
}
void testPlayerTuning() {
    auto run = fixture();
    run.tunePlayer(200, 48);
    run.player.hp = 100;
    run.grant(dw::ItemId::Judas);
    run.tunePlayer(400, 20);
    check(run.player.maxHp == 320 && run.player.hp == 200 && run.player.shotDamage == 20,
          "health tuning preserves the injured fraction and applies existing item penalties");
    run.grant(dw::ItemId::Judas);
    run.tunePlayer(500, 20);
    check(run.player.maxHp == 320 && run.player.hp == 250,
          "item penalties still stack after tuning without accumulating additional tuning penalties");
    run.tunePlayer(200, 20);
    run.healDebug();
    check(run.player.hp == 128, "the heal shortcut fills the adjusted effective maximum");

    run.arena.walls.clear();
    dw::Input input;
    input.fire = true;
    input.aim = {0, 0.85f, -10};
    run.step(input);
    check(run.projectiles.size() == 1 && run.projectiles.front().damage == 20,
          "real player fire uses the chosen damage");
    run.tunePlayer(200, 100);
    check(run.projectiles.front().damage == 20, "tuning does not rewrite bullets already in flight");
    run.player.fireCooldown = 0;
    run.step(input);
    check(run.projectiles.back().damage == 100, "the next shot immediately uses adjusted damage");
    run.grant(dw::ItemId::Split);
    run.grant(dw::ItemId::Ghost);
    run.tunePlayer(200, 20);
    dw::Event hit;
    hit.type = dw::EventType::ProjectileHit;
    hit.damage = 20;
    dw::dispatchItemEffects(run, hit);
    run.drainEvents();
    check(run.projectiles.back().damage == 16, "split bullets inherit adjusted damage once");
    hit.type = dw::EventType::EnemyKilled;
    hit.damage = 16;
    dw::dispatchItemEffects(run, hit);
    run.drainEvents();
    check(run.projectiles.back().ghost && run.projectiles.back().damage == 20,
          "ghost bullets honor damage below the original 48-point floor");
    run.tunePlayer(-100, 9000);
    check(run.player.baseHealth == 25 && run.player.shotDamage == 500 && run.player.hp > 0,
          "tuning clamps health and damage to playable bounds");
    run.tunePlayer(9000, -100);
    check(run.player.baseHealth == 2000 && run.player.shotDamage == 1,
          "the opposite tuning bounds are enforced");
    run.tunePlayer(std::numeric_limits<float>::quiet_NaN(), 48);
    check(run.player.baseHealth == 2000 && run.player.shotDamage == 1,
          "invalid tuning cannot poison player stats");
    run.finishDebug(false);
    run.tunePlayer(200, 48);
    check(run.dead && run.player.hp == 0 && run.player.shotDamage == 1, "tuning cannot revive a dead player");
}
void testContinuousFire() {
    auto run = fixture();
    check(run.player.hp == 100 && run.player.maxHp == 100, "new expeditions start at 100 HP");
    run.arena.walls.clear();
    run.grant(dw::ItemId::Judas);
    dw::Input input;
    input.fire = true;
    input.aim = {0, 0.85f, -10};
    int lastFrame = -1, interval = 0;
    uint64_t shots = 0;
    for (int frame = 0; frame < 720; ++frame) {
        run.step(input);
        if (run.stats.shots == shots)
            continue;
        ++shots;
        const auto &projectile = run.projectiles.back();
        check(projectile.damage == 24, "the player's revolver deals 24 base damage");
        check(projectile.lastRound == (shots % 6 == 0), "every sixth shot retains last-round effects");
        check(projectile.pierce == (shots % 6 == 0 ? 6 : 0), "Judas pierces on each cylinder cycle");
        if (lastFrame >= 0) {
            if (interval == 0)
                interval = frame - lastFrame;
            check(frame - lastFrame == interval, "fire cadence never pauses at a cylinder boundary");
        }
        lastFrame = frame;
    }
    check(shots >= 36, "holding fire continues across multiple cylinders without reload input");
}
void testMouseMovement() {
    auto run = fixture();
    run.player.position = {-10, 0.85f, -2};
    const Vector3 target{-2, 0.85f, -2};
    dw::Input click;
    click.moveTarget = target;
    run.step(click);
    for (int i = 0; i < 300; ++i) {
        run.step({});
        check(!run.arena.blocked(run.player.position, 0.48f), "click-to-move never passes through cover");
    }
    check(dw::distance(run.player.position, target) < 0.1f && !run.moveDestination(),
          "mouse movement routes around cover and stops at destination");
    click.moveTarget = Vector3{-6, 0.85f, -2}; // Inside a solid obstacle.
    run.step(click);
    tick(run, 240);
    check(!run.moveDestination() && !run.arena.blocked(run.player.position, 0.48f),
          "clicking solid cover ends at a walkable edge");
    click.moveTarget = Vector3{12, 0.85f, 12};
    run.step(click);
    dw::Input keyboard;
    keyboard.movement = {0, 0, 1};
    run.step(keyboard);
    const auto stopped = run.player.position;
    tick(run, 60);
    check(!run.moveDestination() && dw::distance(stopped, run.player.position) < 0.001f,
          "WASD overrides and cancels a mouse route");
    run.step(click);
    auto beforeAttack = run.player.position;
    dw::Input attack;
    attack.fire = true;
    run.step(attack);
    tick(run, 30);
    check(!run.moveDestination() && dw::distance(beforeAttack, run.player.position) < 0.001f,
          "attacking cancels the previous route, including after fire is released");
    run.step(click);
    beforeAttack = run.player.position;
    keyboard.standStill = true;
    keyboard.moveTarget = target;
    run.step(keyboard);
    tick(run, 30);
    check(!run.moveDestination() && dw::distance(beforeAttack, run.player.position) < 0.001f,
          "stand-still overrides keyboard movement and cancels click-to-move");
    click.moveTarget = Vector3{100, 0.85f, 100};
    run.step(click);
    tick(run, 600);
    check(!run.moveDestination() && run.player.position.x <= 14.3f && run.player.position.z <= 14.3f,
          "out-of-arena clicks stop inside arena bounds");
    run.room = 2;
    click.moveTarget = run.arena.miners;
    run.step(click);
    tick(run, 600);
    check(run.rescued && !run.moveDestination(), "mouse destination rescues miners on arrival");
    run.room = 3;
    click.moveTarget = run.arena.altar;
    run.step(click);
    tick(run, 600);
    check(run.altarDestroyed && !run.moveDestination(), "mouse destination destroys altar on arrival");
}
void testSafety() {
    auto run = fixture();
    run.limits.eventsPerChain = 24;
    run.limits.eventsPerTick = 8;
    run.limits.queuedEvents = 128;
    run.limits.projectiles = 128;
    for (int i = 0; i < 10; ++i)
        run.grant(dw::ItemId::Split);
    run.grant(dw::ItemId::Powder);
    run.spawnEnemies(100);
    fire(run, {0, 0.85f, 8}, {0, 0, -1}, 1000);
    tick(run, 420);
    check(run.queuedEvents() <= run.limits.queuedEvents && run.projectiles.size() <= run.limits.projectiles,
          "event and projectile capacities are bounded");
    check(run.stats.suppressed > 0 && !run.logs.empty(), "branching chain hits a logged safety limit");
    run.enemies.clear(); // Stop gunmen creating new root chains while old descendants expire.
    tick(run, 420);
    check(run.chains.empty(), "completed chain accounting is reclaimed");
    auto depth = fixture();
    depth.limits.maxDepth = 0;
    depth.grant(dw::ItemId::Split);
    depth.spawn(dw::EnemyKind::Rusher, {0, 0.85f, 0});
    fire(depth, {0, 0.85f, 3}, {0, 0, -1});
    tick(depth, 20);
    check(depth.stats.suppressed > 0, "generation depth is enforced");
}
void testDeterminism() {
    auto a = fixture(), b = fixture();
    for (int i = 0; i < 20000; ++i)
        b.combatRng.next();
    a.spawnEnemies(40);
    b.spawnEnemies(40);
    check(a.enemies.size() == b.enemies.size(), "same encounter size");
    for (size_t i = 0; i < a.enemies.size(); ++i)
        check(dw::distance(a.enemies[i].position, b.enemies[i].position) == 0 &&
                  a.enemies[i].kind == b.enemies[i].kind,
              "combat draws do not change encounter setup");
    a.debugScenario = b.debugScenario = false;
    a.enemies.clear();
    b.enemies.clear();
    a.roomClear = b.roomClear = false;
    a.rooms[0].cleared = b.rooms[0].cleared = false;
    a.step({});
    b.step({});
    check(a.roomClear && b.roomClear && !a.rewardOpen && !b.rewardOpen,
          "combat rooms clear without giving power-ups");
    check(a.rooms[dw::RoomCount - 2].offers == b.rooms[dw::RoomCount - 2].offers,
          "combat draws do not change seeded power-room offers");
}
void testCampaign(const std::filesystem::path &path) {
    dw::CampaignStore store(path);
    uint64_t id = store.begin(123);
    auto run = dw::Simulation(123, id, store.data().world);
    run.grant(dw::ItemId::Judas);
    run.rescued = true;
    store.checkpoint(run.summary());
    {
        dw::CampaignStore restart(path);
        check(restart.recover(), "pending run recovers as retreat");
        check(restart.data().world.population == 48 && restart.data().world.prosperity == 42,
              "rescue survives interrupted retreat");
        check(restart.data().history.size() == 1 && restart.data().history.back().interrupted,
              "partial history marked interrupted");
    }
    dw::CampaignStore restart(path);
    check(!restart.recover() && restart.data().history.size() == 1,
          "second restart does not repeat consequences");
    auto previous = restart.data().history.back();
    restart.resolve(previous, dw::EndReason::Retreat);
    check(restart.data().history.size() == 1, "resolve is idempotent");
    id = restart.begin(456);
    dw::Simulation next(456, id, restart.data().world);
    check(next.items.empty() && next.player.maxHp == 100, "temporary items and health costs reset");
    next.bossKilled = true;
    next.altarDestroyed = true;
    auto won = restart.resolve(next.summary(), dw::EndReason::Victory);
    check(restart.data().world.mineOpen && restart.data().world.prosperity == 62,
          "later victory restores setback and reopens mine");
    check(!restart.data().world.flags.contains("something_followed"), "altar clears persistent haunting");
    id = restart.begin(456);
    dw::Simulation revisit(456, id, restart.data().world);
    check(revisit.rescued && revisit.followup, "revisit remembers rescue and boss");
    restart.resolve(revisit.summary(), dw::EndReason::Victory);
    check(restart.data().world.population == 48 && restart.data().world.prosperity == 62,
          "revisit cannot duplicate rescue or prosperity rewards");
    dw::CampaignStore reloaded(path);
    check(reloaded.data().history.size() == 3 && reloaded.data().world.mineOpen,
          "consequences and history survive reload together");
    reloaded.reset();
    check(reloaded.data().history.empty() && std::filesystem::exists(path.string() + ".bak"),
          "debug reset keeps backup");
    id = reloaded.begin(789);
    dw::Simulation hollow(789, id, reloaded.data().world);
    hollow.bossKilled = true;
    reloaded.resolve(hollow.summary(), dw::EndReason::Victory);
    check(!reloaded.data().world.mineOpen && reloaded.data().world.flags.contains("miners_stranded"),
          "victory without rescue is a distinct outcome");
    std::ofstream corrupt(path, std::ios::app);
    corrupt << "damage";
    corrupt.close();
    bool rejected = false;
    try {
        dw::CampaignStore invalid(path);
    } catch (...) {
        rejected = true;
    }
    check(rejected, "damaged save is rejected instead of overwritten");
}
void testCheats() {
    dw::Simulation run(1866, 1, {});
    run.godMode = true;
    run.jumpDebug(2);
    const auto before = run.stats.rooms;
    run.spawnEnemies(20);
    run.queueRoot({});
    run.clearRoomDebug();
    check(run.roomClear && run.livingEnemies() == 0 && run.projectiles.empty() && run.queuedEvents() == 0 &&
              run.chains.empty(),
          "clear-room cheat removes enemies and all pending combat effects");
    tick(run, 600);
    check(run.livingEnemies() == 0 && run.stats.rooms == before + 1,
          "clear-room cheat keeps the room empty and counts completion once");
    run.startStress();
    check(run.debugScenario && run.livingEnemies() > 0, "stress scenario starts in a cleared room");
    run.clearRoomDebug();
    check(run.roomClear && !run.debugScenario && run.stats.rooms == before + 1,
          "clearing a stress scene restores room state without counting another clear");
    const auto items = run.items.size();
    run.keys = 3;
    run.player.hp = 1;
    run.player.dodgeCooldown = 2;
    run.jumpDebug(2, true);
    check(!run.roomClear && run.livingEnemies() > 0 && run.stats.rooms == before &&
              run.player.hp == run.player.maxHp && run.player.dodgeCooldown == 0 &&
              run.items.size() == items && run.keys == 3 && !run.moveDestination(),
          "room restart heals, resets progression and keeps the testing build and keys");
    for (const auto &enemy : run.enemies)
        check(dw::distance(enemy.position, run.player.position) > 6,
              "room restart spawns its enemy group safely away from the new player position");
    const int power = dw::RoomCount - 2;
    run.jumpDebug(power);
    run.player.position = run.arena.rooms[size_t(power)].objective;
    run.interact();
    run.chooseReward(0);
    run.jumpDebug(power, true);
    run.player.position = run.arena.rooms[size_t(power)].objective;
    run.interact();
    check(!run.rewardOpen && run.powerUpsTaken == 1 && run.items.size() == items + 1,
          "room replay preserves claimed powers and cannot grant a second normal reward");
    run.startBoss();
    run.clearRoomDebug();
    const auto clears = run.stats.rooms;
    check(run.bossKilled && run.roomClear, "boss skip marks the objective complete");
    run.startBoss();
    check(!run.bossKilled && !run.roomClear && run.livingEnemies() == 1 && run.stats.rooms == clears - 1,
          "boss replay resets cleared state and starts exactly one encounter");
    for (int index : run.arena.rooms.back().passages) {
        const auto &door = run.arena.passages[size_t(index)];
        check(door.sealed[0] || door.sealed[1], "boss replay seals the entrance again");
    }
    run.clearRoomDebug();
    run.clearRoomDebug();
    check(run.stats.rooms == clears, "replayed and repeated clears keep room counts consistent");
}
void testLoop() {
    dw::Simulation run(1866, 1, {});
    run.godMode = true;
    int powers = 0;
    for (int room = 0; room < dw::RoomCount; ++room) {
        run.player.hp = 30;
        run.player.position = run.arena.rooms[size_t(room)].center;
        run.enterRoom(room);
        check(run.player.hp == 30, "entering any room preserves the player's wounded health");
        const auto before = run.items.size();
        if (run.arena.rooms[size_t(room)].kind == dw::RoomKind::Power) {
            check(run.roomClear && !run.rewardOpen,
                  "power rooms are peaceful and require approaching the pedestal");
            run.player.position = run.arena.rooms[size_t(room)].objective;
            run.interact();
            check(run.rewardOpen && run.offers[0] != run.offers[1],
                  "power pedestal offers two distinct choices");
            run.chooseReward(0);
            ++powers;
            run.interact();
            run.chooseReward(1);
            check(!run.rewardOpen && run.items.size() == before + 1,
                  "one power per cache; repeat interactions give nothing");
        } else if (run.arena.rooms[size_t(room)].kind == dw::RoomKind::Empty) {
            const auto cleared = run.stats.rooms;
            tick(run, 600);
            check(run.roomClear && run.livingEnemies() == 0 && !run.rewardOpen && run.items.size() == before,
                  "empty rooms stay peaceful without enemies or power rewards");
            run.enterRoom(room);
            check(run.player.hp == 30 && run.stats.rooms == cleared,
                  "revisiting an empty room preserves health and room completion");
        } else {
            check(run.livingEnemies() > 0, "one enemy group is present immediately on room entry");
            run.killAll();
            tick(run, 1);
            check(run.roomClear && !run.rewardOpen && run.items.size() == before,
                  "defeating the single group immediately opens doors without granting an item");
            check(run.player.hp == 30, "killing the last enemy and clearing the room never heals");
            const auto cleared = run.stats.rooms;
            tick(run, 600);
            check(run.livingEnemies() == 0 && run.stats.rooms == cleared,
                  "cleared rooms never spawn a second group after waiting");
            run.enterRoom(room);
            check(run.livingEnemies() == 0 && run.roomClear && run.stats.rooms == cleared,
                  "revisiting a cleared combat room never spawns another group");
        }
        if (room == 2) {
            run.player.position = run.arena.miners;
            run.interact();
            check(run.rescued, "in-world rescue interaction");
        }
        if (room == 3) {
            run.player.position = run.arena.altar;
            run.interact();
            check(run.altarDestroyed, "in-world altar interaction");
        }
        for (int passage : run.arena.rooms[size_t(room)].passages) {
            const auto &door = run.arena.passages[size_t(passage)];
            check(!door.sealed[0] && !door.sealed[1], "combat seals reopen after clearing the room");
        }
    }
    check(powers >= 1 && powers <= 2 && run.powerUpsTaken == powers, "at most two powers per expedition");
    run.player.position = run.arena.exit;
    run.interact();
    check(run.finished && run.bossKilled && run.stats.rooms == dw::RoomCount,
          "debug shortcut completes all fifteen rooms and the boss");
}
} // namespace
int main() {
    auto directory =
        std::filesystem::temp_directory_path() /
        ("deathward-tests-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        std::filesystem::create_directories(directory);
        testCollision();
        std::cout << "PASS 3D swept collisions\n";
        testItems();
        std::cout << "PASS five items and composed effects\n";
        testContinuousFire();
        std::cout << "PASS continuous fire and sixth-shot effects\n";
        testPlayerTuning();
        std::cout << "PASS player health, damage and item tuning\n";
        testMouseMovement();
        std::cout << "PASS mouse routes, interactions and keyboard override\n";
        testSafety();
        std::cout << "PASS bounded chains and cleanup\n";
        testDeterminism();
        std::cout << "PASS independent seeded RNG streams\n";
        testCampaign(directory / "campaign.save");
        std::cout << "PASS persistence, recovery, consequences and revisits\n";
        testLoop();
        std::cout << "PASS full expedition progression\n";
        testCheats();
        std::cout << "PASS cheat clears, stress cleanup, room restart and repeatable boss\n";
        std::filesystem::remove_all(directory);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << "\nTest files: " << directory << '\n';
        return 1;
    }
}
