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
        check(run.player.maxHp == 160, "Judas applies its health cost to the increased starting health");
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
void testContinuousFire() {
    auto run = fixture();
    check(run.player.hp == 200 && run.player.maxHp == 200, "new expeditions start at 200 HP");
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
        check(projectile.damage == 48, "the player's revolver deals 48 base damage");
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
    run.spawnWave(100);
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
    a.spawnWave(40);
    b.spawnWave(40);
    check(a.enemies.size() == b.enemies.size(), "same encounter size");
    for (size_t i = 0; i < a.enemies.size(); ++i)
        check(dw::distance(a.enemies[i].position, b.enemies[i].position) == 0 &&
                  a.enemies[i].kind == b.enemies[i].kind,
              "combat draws do not change encounter setup");
    a.debugScenario = b.debugScenario = false;
    a.enemies.clear();
    b.enemies.clear();
    a.wave = b.wave = 3;
    a.waveDelay = b.waveDelay = 0;
    a.step({});
    b.step({});
    check(a.rewardOpen && b.rewardOpen && a.offers == b.offers, "combat draws do not change reward offers");
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
    check(next.items.empty() && next.player.maxHp == 200, "temporary items and health costs reset");
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
void testLoop() {
    dw::Simulation run(1866, 1, {});
    run.godMode = true;
    for (int room = 0; room < dw::Simulation::FinalRoom; ++room) {
        for (int wave = 0; wave < 3; ++wave) {
            tick(run, 120);
            check(run.livingEnemies() > 0, "encounter wave spawns");
            run.killAll();
        }
        tick(run, 120);
        check(run.rewardOpen, "room clear offers reward");
        run.chooseReward(0);
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
        run.nextRoom();
        for (int frame = 0; frame < 1000 && run.room == room; ++frame) {
            const auto previous = run.player.position;
            run.step({});
            check(dw::distance(previous, run.player.position) <= 0.101f,
                  "walking between rooms never teleports the player");
            check(!run.arena.blocked(run.player.position, 0.48f), "passages have collision-free traversal");
        }
        check(run.room == room + 1, "walking through a corridor starts the connected encounter");
        // Finish the walk before testing the next wave's timing.
        while (run.moveDestination())
            run.step({});
    }
    tick(run, 120);
    check(run.boss() != nullptr, "final room contains boss");
    run.killAll();
    tick(run, 180);
    run.player.position = run.arena.exit;
    run.interact();
    check(run.finished && run.bossKilled && run.stats.rooms == 7,
          "debug shortcut completes all seven chambers");
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
        std::filesystem::remove_all(directory);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << "\nTest files: " << directory << '\n';
        return 1;
    }
}
