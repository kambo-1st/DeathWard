#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
void tick(Simulation &run, int n) {
    for (int i = 0; i < n; ++i)
        run.step({});
}
Simulation fixture() {
    Simulation run(1866, 1, {});
    run.arena = Arena{};
    run.arena.bounds = {{-25, -1, -25}, {25, 8, 25}};
    for (auto &room : run.arena.rooms)
        room.bounds = run.arena.bounds;
    run.player.position = {0, .85f, 8};
    run.roomClear = false;
    run.debugScenario = true;
    run.moneyPickups.clear();
    return run;
}
EntityId target(Simulation &run, Vector3 at, float hp = 150) {
    const auto id = run.spawn(EnemyKind::Gunman, at);
    auto &enemy = *run.findEnemy(id);
    enemy.hp = enemy.maxHp = hp;
    enemy.state = EnemyState::Stunned;
    enemy.stateTime = 30;
    return id;
}
void fuseAndDamage() {
    auto run = fixture();
    const Vector3 aim{0, .85f, 0};
    const auto preview = run.dynamiteTrajectory(aim);
    check(preview.size() > 20 && preview.back().y < .3f, "preview predicts an arc and ground landing");
    auto landing = preview.back();
    landing.y = .85f;
    const auto near = target(run, add(landing, {1, 0, 0}));
    const auto far = target(run, add(landing, {7, 0, 0}));
    const auto combat = run.combatRng.state, rewards = run.rewardRng.state;
    check(run.dynamite == 3 && run.throwDynamite(aim), "missions start with three throwable charges");
    check(run.dynamite == 2 && !run.throwDynamite(aim),
          "cooldown rejects a duplicate throw without spending");
    check(run.chains.size() == 1 && run.chains.begin()->second.active == 1,
          "an armed charge retains its event chain until detonation");
    tick(run, 118);
    check(run.stats.explosions == 0 && run.findEnemy(near)->hp == 150, "a lit fuse never deals early damage");
    check(run.hazards.size() == 1 && distance(run.hazards.front().position, preview.back()) < .03f,
          "the actual bouncing charge matches the preview");
    tick(run, 4);
    check(run.stats.explosions == 1 && run.findEnemy(near)->hp == 50 && run.findEnemy(far)->hp == 150,
          "one detonation deals 100 damage only inside its blast radius");
    check(run.player.hp == 100 && run.hazards.empty() && run.chains.empty() && run.stats.shots == 0,
          "throwing keeps the revolver independent and reclaims the hazard chain");
    check(run.combatRng.state == combat && run.rewardRng.state == rewards,
          "throwing, bouncing and damage do not consume gameplay RNG");
    bool heard = false;
    for (const auto &cue : run.audioCues.cues())
        heard |= cue.kind == AudioCueKind::Explosion;
    check(heard, "detonation produces positional explosion audio");
}
void collisionAndCover() {
    auto run = fixture();
    run.arena.walls.push_back({{-8, 0, 3}, {8, 9, 3.6f}});
    const auto behind = target(run, {0, .85f, 2});
    const auto path = run.dynamiteTrajectory({0, .85f, -2});
    for (const auto p : path)
        check(p.z > 3.6f, "the charge bounces off a tall wall without tunneling through it");
    check(run.throwDynamite({0, .85f, -2}), "throw toward solid cover");
    tick(run, 123);
    check(run.findEnemy(behind)->hp == 150, "solid cover blocks explosion damage");
    auto low = fixture();
    low.arena.walls.push_back({{-8, 0, 3}, {8, .6f, 3.6f}});
    const auto over = low.dynamiteTrajectory({0, .85f, -2});
    check(over.back().z < 3, "the lob can clear low cover using actual height");
    for (auto theme : {MissionTheme::Mine, MissionTheme::Canyon}) {
        Simulation mission(1866, 1, {}, theme);
        const auto route = mission.dynamiteTrajectory(add(mission.player.position, {30, 0, 30}));
        for (size_t i = 1; i < route.size(); ++i) {
            check(!mission.arena.trace(route[i - 1], route[i], .16f).hit,
                  "predicted movement respects generated cover and canyon surfaces");
        }
    }
}
void groundPlacement() {
    for (auto theme : {MissionTheme::Mine, MissionTheme::Canyon}) {
        Simulation run(1866, 1, {}, theme);
        const auto player = run.player.position;
        check(run.placeDynamite() && run.dynamite == 2, "ground placement consumes one charge");
        const auto placed = run.hazards.front().position;
        const float floor = run.arena.canyon ? run.arena.canyon->height(player.x, player.z) : 0;
        check(placed.x == player.x && placed.z == player.z && std::abs(placed.y - floor - .18f) < .001f &&
                  run.hazards.front().settled && length(run.hazards.front().velocity) == 0,
              "placed dynamite sits on the actual floor at the player's feet without a throw");
        check(!run.placeDynamite() && run.dynamite == 2, "placement respects the shared cooldown");
        tick(run, 118);
        check(run.stats.explosions == 0 && distance(run.hazards.front().position, placed) == 0,
              "a placed charge stays exactly still throughout its fuse");
        tick(run, 4);
        check(run.stats.explosions == 1 && run.player.hp == 75 && run.hazards.empty(),
              "ground dynamite explodes after two seconds and can hurt a player who stays nearby");
    }
    auto run = fixture();
    Input walking;
    walking.movement = {1, 0, 0};
    walking.aim = {100, .85f, -100};
    walking.placeDynamite = true;
    run.step(walking);
    const auto placed = run.hazards.front().position;
    check(placed.x == run.player.position.x && placed.z == run.player.position.z,
          "placement ignores cursor aim and uses the player position during its simulation tick");
    walking.placeDynamite = false;
    for (int i = 0; i < 122; ++i)
        run.step(walking);
    check(run.player.hp == 100 && run.stats.explosions == 1 && run.dynamite == 2,
          "the player can keep moving away from a placed charge and escape the explosion");
}
void selfDamageAndGuards() {
    for (int protection = 0; protection < 3; ++protection) {
        auto run = fixture();
        run.godMode = protection == 1;
        check(run.throwDynamite(run.player.position), "a short throw can be placed at the player's feet");
        tick(run, 118);
        if (protection == 2)
            run.player.dodge = .3f;
        tick(run, 5);
        check(run.player.hp == (protection == 0 ? 75 : 100),
              "own blast deals 25 damage, respecting dodge and invulnerability");
    }
    auto run = fixture();
    run.hazards.resize(run.limits.hazards);
    check(!run.throwDynamite({}) && !run.placeDynamite() && run.dynamite == 3,
          "hazard capacity never consumes ammunition");
    run.hazards.clear();
    run.shopOpen = true;
    check(!run.throwDynamite({}) && !run.placeDynamite(), "shop blocks dynamite");
    run.shopOpen = false;
    run.rewardOpen = true;
    check(!run.throwDynamite({}) && !run.placeDynamite(), "power choice blocks dynamite");
    run.rewardOpen = false;
    run.dead = true;
    check(!run.throwDynamite({}) && !run.placeDynamite(), "dead players cannot deploy dynamite");
    run.dead = false;
    run.finished = true;
    check(!run.throwDynamite({}) && !run.placeDynamite(), "completed missions cannot deploy dynamite");
    run.finished = false;
    run.dynamite = 0;
    check(!run.throwDynamite({}) && !run.placeDynamite() && run.hazards.empty(),
          "empty ammo cannot create a charge");
    run.dynamite = 3;
    run.throwDynamite({});
    run.enterRoom(1);
    check(run.hazards.empty() && run.dynamite == 2 && run.chains.empty(),
          "room travel clears live ordnance without refilling ammo or leaking chains");
    tick(run, 30);
    check(run.throwDynamite({}), "a new charge can be thrown after travel");
    run.clearRoomDebug();
    check(run.hazards.empty() && run.chains.empty(), "debug clear removes pending ordnance");
}
void effectsAndRestock() {
    auto run = fixture();
    run.grant(ItemId::Powder);
    auto landing = run.dynamiteTrajectory({0, .85f, 0}).back();
    landing.y = .85f;
    target(run, landing, 50);
    target(run, add(landing, {2, 0, 0}), 50);
    run.throwDynamite(landing);
    tick(run, 124);
    check(run.stats.kills == 2 && run.stats.explosions >= 3 && run.chains.empty(),
          "dynamite kills trigger existing kill effects with bounded chain cleanup");
    WorldState wallet;
    wallet.money = 50;
    Simulation shop(1866, 1, wallet);
    shop.enterRoom(shop.arena.shopRoom);
    shop.player.position = shop.arena.rooms[size_t(shop.room)].objective;
    shop.interact();
    shop.dynamite = MaxDynamite - 2;
    check(!shop.buyShop(3) && shop.money() == 50 && !shop.shopOffers[3].sold,
          "packs cannot overfill the nine-charge inventory");
    shop.dynamite = 2;
    check(shop.buyShop(3) && shop.dynamite == 5 && shop.money() == 35 && shop.moneySpent == 15 &&
              shop.items.empty() && shop.checkpointNeeded,
          "the shop sells three charges for 15 coins and checkpoints spending");
    check(!shop.buyShop(3) && shop.dynamite == 5, "refill stock is sold only once per mission");
}
} // namespace
int main() {
    try {
        fuseAndDamage();
        collisionAndCover();
        groundPlacement();
        selfDamageAndGuards();
        effectsAndRestock();
        std::cout
            << "PASS dynamite fuse, trajectory, collisions, damage, cover, guards, chains and shop refill\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
