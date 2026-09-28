#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
Simulation fixture() {
    Simulation s(1866, 1, {});
    s.arena = Arena{};
    s.arena.bounds = {{-25, -1, -25}, {25, 4, 25}};
    s.arena.walls = {{{-26, -1, -26}, {-25, 5, 26}},
                     {{25, -1, -26}, {26, 5, 26}},
                     {{-26, -1, -26}, {26, 5, -25}},
                     {{-26, -1, 25}, {26, 5, 26}}};
    for (auto &r : s.arena.rooms) {
        r.bounds = s.arena.bounds;
        r.center = {0, 0, 0};
        r.floors = {{{-25, -.4f, -25}, {25, 0, 25}}};
    }
    s.player.position = {0, .85f, 8};
    s.debugScenario = true;
    s.roomClear = false;
    return s;
}
void tick(Simulation &s, int count) {
    for (int n = 0; n < count; ++n)
        s.step({});
}
void damage(Simulation &s, EntityId id, float amount, Vector3 direction = {0, 0, -1}, bool area = false) {
    Event e;
    e.type = EventType::Damage;
    e.target = id;
    e.damage = amount;
    e.direction = direction;
    e.areaDamage = area;
    s.queueRoot(e);
    s.drainEvents();
}
EntityId ready(Simulation &s, int id) {
    auto entity = s.spawnMonster(id, {0, .85f, 0});
    s.findEnemy(entity)->cooldown = 0;
    return entity;
}
void catalogAndSmoke() {
    std::set<int> ids;
    for (const auto &d : monsterCatalog()) {
        check(ids.insert(d.id).second, "monster IDs must be unique");
        auto s = fixture();
        s.godMode = true;
        ready(s, d.id);
        tick(s, 420);
        for (const auto &e : s.enemies)
            check(std::isfinite(e.position.x) && std::isfinite(e.hp),
                  "every family simulates finite positions and health");
        check(s.enemies.size() <= s.limits.enemies && s.hazards.size() <= s.limits.hazards &&
                  s.projectiles.size() <= s.limits.projectiles,
              "all families respect effect budgets");
        s.clearRoomDebug();
        check(s.livingEnemies() == 0 && s.hazards.empty() && s.chains.empty(),
              "clear-room cheat cleans every monster family");
    }
    for (int id : {monsterId(10), monsterId(10, 3), monsterId(25, 3, 1), monsterId(38, 1, 1),
                   monsterId(42, 2), monsterId(68, 11), monsterId(89)})
        check(ids.contains(id), "requested endpoints and multi-part variants are present");
    check(monsterIdText(monsterId(25, 3, 1)) == "25.3.1" && monsterIdText(monsterId(68, 11)) == "68.11",
          "variant IDs preserve decimal components");
    std::cout << "CATALOG " << ids.size() << " entries including offspring\n";
}
void gunsAndArmor() {
    auto s = fixture();
    auto id = ready(s, monsterId(12));
    s.step({});
    check(s.findEnemy(id)->state == EnemyState::Windup && s.projectiles.empty(), "Horf warns before firing");
    tick(s, 35);
    check(s.stats.projectiles == 1, "Horf fires one actual projectile");
    int frames = 0;
    while (s.stats.projectiles < 2 && frames < 180) {
        tick(s, 1);
        ++frames;
    }
    check(frames >= 150 && frames <= 159 && s.stats.projectiles == 2,
          "Horf attacks again sooner while retaining its full windup");
    check(s.player.hp == StartingHealth - 12.5f && s.stats.damageTaken == 12.5f,
          "Horf shots deal 25% more damage exactly once");
    auto c = fixture();
    ready(c, monsterId(15));
    tick(c, 36);
    check(c.stats.projectiles == 4, "Clotty fires four cardinal shots");
    auto host = fixture();
    id = host.spawnMonster(monsterId(27), {0, .85f, 0});
    damage(host, id, 20);
    check(host.findEnemy(id)->hp == 88, "closed Host shell blocks damage");
    host.findEnemy(id)->cooldown = 0;
    host.step({});
    damage(host, id, 20);
    check(host.findEnemy(id)->hp == 68, "raised Host exposes its body");
    auto knight = fixture();
    id = knight.spawnMonster(monsterId(41), {0, .85f, 0});
    knight.findEnemy(id)->facing = {0, 0, 1};
    damage(knight, id, 30, {0, 0, -1});
    check(knight.findEnemy(id)->hp == 104, "Knight blocks frontal shots");
    damage(knight, id, 30, {0, 0, 1});
    check(knight.findEnemy(id)->hp == 74, "Knight rear remains vulnerable");
    damage(knight, id, 30, {0, 0, -1}, true);
    check(knight.findEnemy(id)->hp == 44, "explosions bypass directional armor");
    auto reflect = fixture();
    id = reflect.spawnMonster(monsterId(41, 4), {0, .85f, 0});
    reflect.findEnemy(id)->facing = {0, 0, 1};
    damage(reflect, id, 20);
    check(reflect.projectiles.size() == 1 && reflect.projectiles[0].hostile,
          "Black Knight reflects a frontal shot");
}
void regenerationAndOffspring() {
    auto s = fixture();
    auto id = s.spawnMonster(monsterId(24), {0, .85f, 0});
    damage(s, id, 200);
    check(s.findEnemy(id)->alive && s.findEnemy(id)->state == EnemyState::Collapsed && s.stats.kills == 0,
          "Globin collapses before a true kill");
    tick(s, 160);
    check(s.findEnemy(id)->state != EnemyState::Collapsed && s.findEnemy(id)->hp == 96,
          "ignored goo regenerates");
    damage(s, id, 200);
    damage(s, id, 200);
    check(!s.findEnemy(id)->alive && s.stats.kills == 1, "finishing the goo prevents regeneration");
    auto moter = fixture();
    id = moter.spawnMonster(monsterId(80), {0, .85f, 0});
    damage(moter, id, 200);
    moter.step({});
    check(moter.livingEnemies() == 2, "Moter produces two living Attack Flies");
    for (const auto &e : moter.enemies)
        check(e.monster == monsterId(18), "Moter children use the correct ID");
    auto limited = fixture();
    limited.limits.enemies = 2;
    id = limited.spawnMonster(monsterId(22, 3), {0, .85f, 0});
    damage(limited, id, 1000);
    limited.step({});
    check(limited.livingEnemies() <= 2 && limited.stats.suppressed > 0,
          "death summons are bounded and report suppression");
    auto room = fixture();
    room.debugScenario = false;
    room.rooms[0].cleared = false;
    id = room.spawnMonster(monsterId(80), {0, .85f, 0});
    damage(room, id, 200);
    room.step({});
    check(!room.roomClear && room.roomThreats() == 2, "offspring are present before the room-clear check");
    room.killAll();
    room.step({});
    check(room.roomClear && room.livingEnemies() == 0,
          "kill cheat also clears offspring without new summons");
    auto linked = fixture();
    id = linked.spawnMonster(monsterId(41, 3), {0, .85f, 0});
    linked.step({});
    auto pon = linked.findEnemy(id)->partner;
    check(pon && linked.findEnemy(pon), "Brainless Knight gets a linked Pon");
    damage(linked, pon, 200);
    linked.step({});
    check(!linked.findEnemy(id), "killing Pon removes its corresponding Knight");
}
void hazardsAndCover() {
    auto s = fixture();
    s.debugScenario = false;
    s.rooms[0].cleared = false;
    const auto grimace = ready(s, monsterId(42));
    const auto victim = s.spawn(EnemyKind::Rusher, {5, .85f, 0});
    damage(s, grimace, 1000);
    check(s.findEnemy(grimace)->alive && s.roomThreats() == 1,
          "Grimace is invulnerable but not a room objective");
    damage(s, victim, 1000);
    s.step({});
    check(s.roomClear && s.roomThreats() == 0 && s.hazards.empty(),
          "room opens with only an invulnerable hazard left");
    for (bool wall : {false, true}) {
        auto beam = fixture();
        auto id = ready(beam, monsterId(39));
        beam.step({});
        if (wall)
            beam.arena.walls.push_back({{-3, 0, 4}, {3, 4, 5}});
        tick(beam, 100);
        check((beam.player.hp < StartingHealth) == !wall, "laser damage is clipped by solid cover");
        beam.findEnemy(id)->state = EnemyState::Stunned;
        beam.findEnemy(id)->stateTime = 100;
        tick(beam, 180);
        check(beam.chains.empty(), "laser effects release their chain ownership");
    }
    auto dodge = fixture();
    ready(dodge, monsterId(39));
    tick(dodge, 70);
    dodge.player.dodge = 2;
    dodge.player.dodgeDirection = {};
    tick(dodge, 40);
    check(dodge.player.hp == StartingHealth, "dodge protects against an active beam");
    auto bomb = fixture();
    auto id = ready(bomb, monsterId(87));
    bomb.step({});
    tick(bomb, 50);
    check(!bomb.hazards.empty() && bomb.player.hp == StartingHealth,
          "explosive shot marks a safe fuse period");
    const auto zone = bomb.hazards.front().position;
    bomb.findEnemy(id)->position = zone;
    bomb.findEnemy(id)->state = EnemyState::Stunned;
    bomb.findEnemy(id)->stateTime = 10;
    auto other = bomb.spawn(EnemyKind::Ironhide, add(zone, {1, 0, 0}));
    bomb.findEnemy(other)->state = EnemyState::Stunned;
    bomb.findEnemy(other)->stateTime = 10;
    tick(bomb, 65);
    check(bomb.findEnemy(id)->hp == 104 && bomb.findEnemy(other)->hp < 144,
          "Gurgle blast spares its source and damages other enemies");
}
void movementAndProjectiles() {
    auto chase = fixture();
    const auto gaper = chase.spawnMonster(monsterId(10, 1), {0, .85f, 0});
    tick(chase, 60);
    check(std::abs(chase.findEnemy(gaper)->position.z - 2.42f) < .01f,
          "Gapers pursue 10% faster across open floor");
    chase.player.position = add(chase.findEnemy(gaper)->position, {0, 0, .75f});
    tick(chase, 1);
    check(chase.player.hp == StartingHealth - 12.5f, "monster contact deals the boosted damage");
    tick(chase, 10);
    check(chase.player.hp == StartingHealth - 12.5f, "contact damage still respects hurt invulnerability");
    auto mirror = fixture();
    auto id = mirror.spawnMonster(monsterId(53), {0, .85f, 0});
    Input input;
    input.movement = {1, 0, 0};
    input.fire = true;
    input.aim = {0, .85f, -8};
    mirror.step(input);
    check(mirror.findEnemy(id)->position.x < 0 && mirror.stats.projectiles == 2,
          "Dople mirrors actual movement and fired shots");
    auto split = fixture();
    ready(split, monsterId(14, 2));
    tick(split, 55);
    check(split.projectiles.size() == 4, "Tainted Pooter starts with four splitting shots");
    for (auto &p : split.projectiles)
        p.life = 0;
    split.step({});
    check(split.stats.projectiles == 12, "each splitting shot creates exactly two children");
    for (const auto &p : split.projectiles)
        check(p.kind == ProjectileKind::Bullet, "split children cannot split recursively");
    auto terrain = fixture();
    terrain.godMode = true;
    terrain.arena.walls.push_back({{-2, 0, 3}, {2, 4, 4}});
    id = ready(terrain, monsterId(23));
    tick(terrain, 180);
    check(!terrain.arena.blocked(terrain.findEnemy(id)->position, .6f),
          "charging monsters respect obstacle collision");
    auto burrow = fixture();
    id = ready(burrow, monsterId(58));
    tick(burrow, 2);
    check(burrow.findEnemy(id)->state == EnemyState::Buried, "Para-Bite burrows");
    auto hp = burrow.findEnemy(id)->hp;
    damage(burrow, id, 1000);
    check(burrow.findEnemy(id)->hp == hp, "buried enemies cannot be shot");
    tick(burrow, 70);
    check(!burrow.arena.blocked(burrow.findEnemy(id)->position, .6f), "burrowing returns to valid terrain");
}
void referenceCorrections() {
    auto bulb = fixture();
    const auto bulbId = bulb.spawnMonster(monsterId(61, 5), bulb.player.position);
    tick(bulb, 12);
    check(bulb.player.hp == StartingHealth && bulb.player.dodgeCooldown == 0,
          "Bulb has no health or dodge-drain effect when no active item exists");
    const auto facing = bulb.findEnemy(bulbId)->facing;
    check(std::abs(facing.x) < .001f || std::abs(facing.z) < .001f,
          "harmless Bulbs wander along right-angled directions");

    auto sucker = fixture();
    const auto id = sucker.spawnMonster(monsterId(61, 7), sucker.player.position);
    tick(sucker, 12);
    check(sucker.player.hp == StartingHealth, "Tainted Sucker never deals contact damage");
    sucker.findEnemy(id)->position = {0, .85f, 0};
    damage(sucker, id, 1000);
    check(sucker.projectiles.size() == 6, "Tainted Sucker death creates six parent projectiles");
    for (const auto &p : sucker.projectiles)
        check(p.bounces == 1 && p.kind == ProjectileKind::BurstShot,
              "Tainted Sucker parents can bounce before splitting");
    sucker.projectiles.front().position = {24, .85f, 0};
    tick(sucker, 12);
    check(sucker.stats.bounces > 0 && sucker.projectiles.front().velocity.x < 0,
          "Tainted Sucker's projectile actually reflects off cover");
    for (auto &p : sucker.projectiles)
        p.life = 0;
    sucker.step({});
    check(sucker.stats.projectiles == 42, "six parent projectiles each split into six children");

    auto eggy = fixture();
    auto egg = eggy.spawnMonster(monsterId(29, 2), {0, .85f, 0});
    damage(eggy, egg, 1000);
    eggy.step({});
    check(eggy.livingEnemies() == 5, "Eggy's death creates its configured swarm");
    for (const auto &e : eggy.enemies)
        check(e.monster == monsterId(884) && e.radius < monsterDefinition(monsterId(85))->radius,
              "Eggy spawns distinct small Swarm Spiders instead of ordinary Spiders");
    bool hopped = false;
    for (int frame = 0; frame < 180; ++frame) {
        eggy.step({});
        hopped |=
            std::any_of(eggy.enemies.begin(), eggy.enemies.end(), [](const Enemy &e) { return e.lift > 0; });
    }
    check(hopped, "Swarm Spiders hop while approaching the player");

    auto spawner = fixture();
    spawner.godMode = true;
    const auto hive = spawner.spawnMonster(monsterId(22, 3), {0, .85f, 0});
    for (int n = 0; n < 5; ++n) {
        const auto child = spawner.spawnMonster(monsterId(222), {float(n) * 2 - 4, .85f, -3});
        spawner.findEnemy(child)->partner = hive;
    }
    spawner.findEnemy(hive)->state = EnemyState::Windup;
    spawner.findEnemy(hive)->stateTime = 0;
    spawner.step({});
    check(std::count_if(spawner.enemies.begin(), spawner.enemies.end(),
                        [hive](const Enemy &e) { return e.alive && e.partner == hive; }) == 6,
          "a partly occupied summon group never exceeds its six-child limit");
}
} // namespace
int main() {
    try {
        catalogAndSmoke();
        gunsAndArmor();
        regenerationAndOffspring();
        hazardsAndCover();
        movementAndProjectiles();
        referenceCorrections();
        std::cout << "PASS monster roster, armor, regeneration, summons, linked deaths, room hazards, beams, "
                     "collision and projectiles\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        return 1;
    }
}
