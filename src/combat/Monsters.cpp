#include "combat/Simulation.hpp"
#include <stdexcept>

namespace dw {
namespace {
using M = MonsterMotion;
using A = MonsterAttack;
using S = MonsterShape;
// HP and timing are tuned for DeathWard's 48-damage revolver and 200-health player.
constexpr MonsterDefinition Catalog[]{
    {monsterId(10), "Frowning Gaper", M::Chase, A::None, S::Walker, 72},
    {monsterId(10, 1), "Gaper", M::Chase, A::None, S::Walker, 64},
    {monsterId(10, 2), "Flaming Gaper", M::Chase, A::None, S::Walker, 80, 2.8f},
    {monsterId(10, 3), "Rotten Gaper", M::Chase, A::Shot, S::Walker, 88, 2.1f},
    {monsterId(11), "Gusher", M::Wander, A::Shot, S::Headless, 40, 1.6f},
    {monsterId(11, 1), "Pacer", M::Wander, A::None, S::Headless, 32, 1.6f},
    {monsterId(12), "Horf", M::Still, A::Shot, S::Skull, 64, 0},
    {monsterId(13), "Fly", M::Still, A::None, S::Fly, 24, 0, .35f, 3, .5f, 1, true, false},
    {monsterId(14), "Pooter", M::Chase, A::Shot, S::Fly, 48, 1, .45f, 2.4f, .55f, 1, true, false},
    {monsterId(14, 1), "Super Pooter", M::Chase, A::Spread, S::Fly, 72, 1, .5f, 2.6f, .65f, 2, true, false},
    {monsterId(14, 2), "Tainted Pooter", M::Chase, A::Spread, S::Fly, 120, 1, .6f, 3, .8f, 4, true, false},
    {monsterId(15), "Clotty", M::Wander, A::Cross, S::Blob, 80, 1.8f},
    {monsterId(15, 1), "Clot", M::Wander, A::Diagonal, S::Blob, 80, 1.8f},
    {monsterId(15, 2), "I.Blob", M::Wander, A::Ring, S::Blob, 96, 1.7f, .65f, 2.8f, .7f, 2},
    {monsterId(15, 3), "Grilled Clotty", M::Wander, A::Cross, S::Blob, 96, 3, .65f, 2.4f, .65f, 3},
    {monsterId(16), "Mulligan", M::Flee, A::None, S::Walker, 72, 2},
    {monsterId(16, 1), "Mulligoon", M::Flee, A::None, S::Walker, 88, 2, .65f, 2.4f, .7f, 2},
    {monsterId(16, 2), "Mulliboom", M::Chase, A::None, S::Walker, 48, 3.2f, .6f, 2.4f, .7f, 2},
    {monsterId(18), "Attack Fly", M::Chase, A::None, S::Fly, 32, 3.2f, .38f, 2, .5f, 1, true},
    {monsterId(21), "Maggot", M::Wander, A::None, S::Worm, 40, 1.5f},
    {monsterId(22), "Hive", M::Flee, A::Spawn, S::Walker, 112, 1.5f, .7f, 4, .85f, 2},
    {monsterId(22, 1), "Drowned Hive", M::Flee, A::Spawn, S::Walker, 112, 1.5f, .7f, 4, .85f, 3},
    {monsterId(22, 2), "Holy Mulligan", M::Flee, A::Spawn, S::Walker, 120, 1.6f, .7f, 4, .85f, 3},
    {monsterId(22, 3), "Tainted Mulligan", M::Flee, A::Spawn, S::Walker, 192, 1.5f, .8f, 5, 1, 4},
    {monsterId(23), "Charger", M::Charge, A::None, S::Worm, 64, 1.5f},
    {monsterId(23, 0, 1), "My Shadow", M::Charge, A::None, S::Worm, 64, 2, .5f, 2, .5f, 1, false, true, false,
     false},
    {monsterId(23, 1), "Drowned Charger", M::Charge, A::None, S::Worm, 72, 1.5f},
    {monsterId(23, 2), "Dank Charger", M::Charge, A::None, S::Worm, 96, 1.5f, .65f, 2.5f, .7f, 3},
    {monsterId(23, 3), "Carrion Princess", M::Charge, A::None, S::Worm, 112, 1.8f, .7f, 2.5f, .7f, 3},
    {monsterId(24), "Globin", M::Chase, A::None, S::Walker, 96, 2.4f},
    {monsterId(24, 1), "Gazing Globin", M::Chase, A::None, S::Walker, 96, 3.3f, .6f, 2, .5f, 2},
    {monsterId(24, 2), "Dank Globin", M::Chase, A::None, S::Walker, 112, 2.2f, .65f, 2, .5f, 3},
    {monsterId(24, 3), "Cursed Globin", M::Chase, A::None, S::Walker, 112, 2.5f, .65f, 2, .5f, 4},
    {monsterId(25), "Boom Fly", M::Bounce, A::None, S::Fly, 48, 2.6f, .55f, 2, .5f, 2, true},
    {monsterId(25, 1), "Red Boom Fly", M::Bounce, A::None, S::Fly, 48, 2.6f, .55f, 2, .5f, 2, true},
    {monsterId(25, 2), "Drowned Boom Fly", M::Bounce, A::None, S::Fly, 56, 2.6f, .55f, 2, .5f, 3, true},
    {monsterId(25, 3), "Dragon Fly", M::Bounce, A::None, S::Fly, 64, 2.6f, .55f, 2, .5f, 3, true},
    {monsterId(25, 3, 1), "Dragon Fly X", M::Bounce, A::None, S::Fly, 64, 2.6f, .55f, 2, .5f, 3, true},
    {monsterId(25, 4), "Bone Fly", M::Bounce, A::Shot, S::Fly, 64, 2.6f, .55f, 2, .6f, 3, true},
    {monsterId(25, 5), "Sick Boom Fly", M::Bounce, A::None, S::Fly, 64, 2.6f, .55f, 2, .5f, 3, true},
    {monsterId(25, 6), "Tainted Boom Fly", M::Bounce, A::None, S::Fly, 96, 2.6f, .65f, 2, .5f, 4, true},
    {monsterId(26), "Maw", M::Chase, A::Shot, S::Skull, 64, 1.7f, .55f, 2.4f, .55f, 1, true},
    {monsterId(26, 1), "Red Maw", M::Chase, A::None, S::Skull, 64, 3.3f, .55f, 2.4f, .55f, 2, true},
    {monsterId(26, 2), "Psychic Maw", M::Chase, A::Shot, S::Skull, 88, 1.7f, .6f, 3, .8f, 3, true},
    {monsterId(27), "Host", M::Still, A::Spread, S::Skull, 88, 0, .7f, 2.8f, .8f, 2},
    {monsterId(27, 1), "Red Host", M::Still, A::Spread, S::Skull, 112, 0, .7f, 2.8f, .8f, 2},
    {monsterId(27, 3), "Hard Host", M::Still, A::Shot, S::Skull, 112, 0, .7f, 3, .85f, 3},
    {monsterId(29), "Hopper", M::Hop, A::None, S::Headless, 48, 3.5f},
    {monsterId(29, 1), "Trite", M::Hop, A::None, S::Spider, 48, 6, .5f, 2.1f, .55f, 2},
    {monsterId(29, 2), "Eggy", M::Hop, A::None, S::Spider, 96, 3.8f, .65f, 2.5f, .6f, 3},
    {monsterId(29, 3), "Tainted Hopper", M::Hop, A::Ring, S::Headless, 192, 4, .8f, 3, .8f, 4},
    {monsterId(30), "Boil", M::Still, A::Burst, S::Blob, 88, 0},
    {monsterId(30, 1), "Gut", M::Still, A::Lob, S::Blob, 88, 0, .6f, 3, .8f, 2},
    {monsterId(30, 2), "Sack", M::Still, A::Spawn, S::Blob, 88, 0, .65f, 4, .8f, 2},
    {monsterId(31), "Spitty", M::Wander, A::Spitty, S::Worm, 48, 1.2f},
    {monsterId(31, 1), "Tainted Spitty", M::Wander, A::Spitty, S::Worm, 160, 1.8f, .8f, 2, .6f, 4},
    {monsterId(32), "Brain", M::Wander, A::None, S::Blob, 56, 1.5f},
    {monsterId(34), "Leaper", M::Hop, A::Cross, S::Headless, 80, 5, .6f, 2.8f, .8f, 2},
    {monsterId(34, 1), "Sticky Leaper", M::Hop, A::Burst, S::Headless, 96, 5, .65f, 2.8f, .8f, 3},
    {monsterId(35), "Mr. Maw", M::Chase, A::Head, S::Walker, 104, 1.8f, .65f, 3, .7f, 2},
    {monsterId(35, 1), "Mr. Maw Head", M::Orbit, A::None, S::Skull, 48, 8, .45f, 3, .7f, 2, true, true, false,
     false},
    {monsterId(35, 2), "Mr. Red Maw", M::Chase, A::Head, S::Walker, 112, 2.8f, .65f, 2.6f, .7f, 3},
    {monsterId(35, 3), "Mr. Red Maw Head", M::Orbit, A::None, S::Skull, 48, 9, .45f, 3, .7f, 3, true, true,
     false, false},
    {monsterId(38), "Baby", M::Teleport, A::Shot, S::Walker, 80, 1.4f, .55f, 2.8f, .6f, 2, true},
    {monsterId(38, 1), "Angelic Baby", M::Teleport, A::Spread, S::Walker, 96, 1.6f, .55f, 2.8f, .7f, 3, true},
    {monsterId(38, 1, 1), "Angelic Baby (small)", M::Teleport, A::Shot, S::Walker, 40, 1.6f, .35f, 3, .7f, 2,
     true, true, false, false},
    {monsterId(38, 3), "Wrinkly Baby", M::Charge, A::Spread, S::Walker, 96, 2, .6f, 3, .7f, 3, true},
    {monsterId(39), "Vis", M::Wander, A::Beam, S::Headless, 104, 1.3f, .7f, 3.5f, 1, 3},
    {monsterId(39, 1), "Double Vis", M::Wander, A::DoubleBeam, S::Headless, 120, 1.3f, .7f, 3.5f, 1, 3},
    {monsterId(39, 2), "Chubber", M::Wander, A::Head, S::Headless, 112, 1.3f, .7f, 3.5f, .9f, 3},
    {monsterId(39, 3), "Scarred Double Vis", M::Wander, A::QuadBeam, S::Headless, 144, 1.3f, .75f, 4, 1.1f,
     4},
    {monsterId(40), "Guts", M::Wall, A::None, S::Blob, 64, 2.8f},
    {monsterId(40, 1), "Scarred Guts", M::Wall, A::None, S::Blob, 72, 2.8f, .6f, 2, .6f, 2},
    {monsterId(40, 2), "Slog", M::Wall, A::None, S::Blob, 88, 3, .6f, 2.5f, .65f, 3},
    {monsterId(41), "Knight", M::Charge, A::None, S::Skull, 104, 1.8f, .7f, 2.6f, .65f, 2},
    {monsterId(41, 1), "Selfless Knight", M::Charge, A::None, S::Skull, 112, 2, .7f, 2.5f, .65f, 3},
    {monsterId(41, 2), "Loose Knight", M::Charge, A::None, S::Skull, 112, 1.8f, .7f, 2.6f, .7f, 3},
    {monsterId(41, 3), "Brainless Knight", M::Charge, A::None, S::Headless, 96, 1.8f, .7f, 2.6f, .65f, 3,
     false, true, false, false},
    {monsterId(41, 4), "Black Knight", M::Charge, A::None, S::Skull, 144, 1.8f, .75f, 3, .8f, 4},
    {monsterId(42), "Stone Grimace", M::Still, A::Shot, S::Stone, 1, 0, .7f, 2.8f, .8f, 2, false, false,
     true},
    {monsterId(42, 1), "Vomit Grimace", M::Still, A::Lob, S::Stone, 1, 0, .7f, 3.5f, .9f, 3, false, false,
     true},
    {monsterId(42, 2), "Triple Grimace", M::Still, A::Spread, S::Stone, 1, 0, .7f, 3, .9f, 3, false, false,
     true},
    {monsterId(44), "Poky", M::Bounce, A::None, S::Stone, 1, 2.5f, .65f, 2, .6f, 2, false, true, true},
    {monsterId(44, 1), "Slide", M::Charge, A::None, S::Stone, 1, 0, .65f, 3, .8f, 3, false, true, true},
    {monsterId(53), "Dople", M::Mirror, A::Shot, S::Walker, 80, 2, .6f, 1, .25f, 2},
    {monsterId(53, 1), "Evil Twin", M::Mirror, A::Spread, S::Walker, 112, 2, .6f, 1, .25f, 3, true},
    {monsterId(54), "Flaming Hopper", M::Hop, A::None, S::Headless, 64, 6, .6f, 1.6f, .45f, 2},
    {monsterId(55), "Leech", M::Charge, A::None, S::Worm, 64, 2, .55f, 2, .5f, 2},
    {monsterId(55, 1), "Kamikaze Leech", M::Charge, A::None, S::Worm, 64, 2, .55f, 2, .6f, 3},
    {monsterId(55, 2), "Holy Leech", M::Charge, A::None, S::Worm, 80, 2, .55f, 2, .6f, 3},
    {monsterId(56), "Lump", M::Burrow, A::Spread, S::Blob, 88, 0, .6f, 2.5f, .65f, 2},
    {monsterId(57), "MemBrain", M::Hop, A::Ring, S::Blob, 144, 1.8f, .85f, 3, .8f, 3},
    {monsterId(57, 1), "Mama Guts", M::Hop, A::Ring, S::Blob, 144, 1.8f, .85f, 3, .8f, 3},
    {monsterId(57, 2), "Dead Meat", M::Hop, A::Ring, S::Blob, 160, 1.8f, .85f, 3, .9f, 4},
    {monsterId(58), "Para-Bite", M::Burrow, A::None, S::Worm, 80, 2.4f, .6f, 3, .7f, 2},
    {monsterId(58, 1), "Scarred Para-Bite", M::Burrow, A::Shot, S::Worm, 88, 2.4f, .6f, 3, .7f, 3},
    {monsterId(59), "Fred", M::Burrow, A::Cross, S::Worm, 104, 0, .65f, 3, .8f, 3},
    {monsterId(60), "Eye", M::Still, A::Beam, S::Eye, 88, 0, .65f, 3, 1, 3},
    {monsterId(60, 1), "Bloodshot Eye", M::Still, A::Beam, S::Eye, 112, 0, .75f, 3.5f, 1.2f, 3},
    {monsterId(60, 2), "Holy Eye", M::Still, A::Light, S::Eye, 112, 0, .75f, 3.5f, 1, 4},
    {monsterId(61), "Sucker", M::Chase, A::None, S::Fly, 48, 1.8f, .5f, 2, .6f, 2, true},
    {monsterId(61, 1), "Spit", M::Chase, A::None, S::Fly, 48, 1.8f, .5f, 2, .6f, 2, true},
    {monsterId(61, 2), "Soul Sucker", M::Chase, A::None, S::Fly, 64, 1.8f, .5f, 2, .6f, 3, true},
    {monsterId(61, 3), "Ink", M::Chase, A::None, S::Fly, 56, 1.8f, .5f, 2, .6f, 3, true},
    {monsterId(61, 4), "Mama Fly", M::Flee, A::Spawn, S::Fly, 112, 2, .65f, 4, .85f, 3, true},
    {monsterId(61, 5), "Bulb", M::Wander, A::None, S::Fly, 48, 2.5f, .45f, 2, .6f, 3, true, false},
    {monsterId(61, 6), "Bloodfly", M::Chase, A::None, S::Fly, 48, 2.8f, .5f, 2, .6f, 3, true},
    {monsterId(61, 7), "Tainted Sucker", M::Chase, A::None, S::Fly, 96, 1.8f, .6f, 2, .6f, 4, true, false},
    {monsterId(68, 1), "Peep Eye", M::Bounce, A::None, S::Eye, 1, 2.8f, .6f, 2, .6f, 3, true, true, true},
    {monsterId(68, 11), "Bloat Eye", M::Bounce, A::None, S::Eye, 1, 2.8f, .6f, 2, .6f, 3, true, true, true},
    {monsterId(77), "Embryo", M::Hop, A::None, S::Blob, 40, 3, .45f},
    {monsterId(80), "Moter", M::Chase, A::None, S::Fly, 72, 3, .5f, 2, .6f, 2, true},
    {monsterId(85), "Spider", M::Wander, A::None, S::Spider, 32, 3.5f, .4f},
    {monsterId(86), "Keeper", M::Hop, A::Spread, S::Skull, 96, 2, .6f, 2.7f, .7f, 2},
    {monsterId(87), "Gurgle", M::Chase, A::Lob, S::Walker, 104, 1.8f, .65f, 3, .8f, 3},
    {monsterId(87, 1), "Crackle", M::Chase, A::Lob, S::Walker, 112, 1.8f, .65f, 3.5f, .9f, 3},
    {monsterId(88), "Walking Boil", M::Wander, A::Burst, S::Blob, 88, 1.7f},
    {monsterId(88, 1), "Walking Gut", M::Wander, A::Lob, S::Blob, 88, 1.7f, .65f, 3, .8f, 2},
    {monsterId(88, 2), "Walking Sack", M::Wander, A::Spawn, S::Blob, 104, 1.7f, .65f, 4, .8f, 2},
    {monsterId(89), "Buttlicker", M::Chain, A::None, S::Worm, 64, 2.5f},
    // Required offspring outside the requested range; never drawn into the natural room pool.
    {monsterId(96), "Eternal Fly", M::Orbit, A::None, S::Fly, 32, 3, .35f, 2, .5f, 2, true, true, true,
     false},
    {monsterId(222), "Ring Fly", M::Orbit, A::None, S::Fly, 32, 2.6f, .35f, 2, .5f, 3, true, true, false,
     false},
    {monsterId(238), "Splasher", M::Wander, A::Lob, S::Headless, 40, 1.6f, .5f, 3, .7f, 3, false, true, false,
     false},
    {monsterId(840), "Pon", M::Hop, A::None, S::Blob, 64, 3, .5f, 2, .5f, 3, false, true, false, false},
    {monsterId(853), "Small Maggot", M::Wander, A::None, S::Worm, 24, 1.6f, .3f, 2, .5f, 3, false, true,
     false, false},
    {monsterId(861), "Pustule", M::Still, A::None, S::Blob, 56, 0, .5f, 5, .8f, 3, false, false, false,
     false},
    {monsterId(862), "Cyst", M::Wall, A::Shot, S::Blob, 56, 2.6f, .5f, 3, .6f, 3, false, true, false, false},
    {monsterId(884), "Swarm Spider", M::Hop, A::None, S::Spider, 20, 4.5f, .25f, .6f, .15f, 3, false, true,
     false, false},
};
int type(const Enemy &e) {
    return e.monster / 10000;
}
int variant(const Enemy &e) {
    return e.monster / 100 % 100;
}
Vector3 flatDirection(Vector3 a, Vector3 b) {
    auto d = sub(b, a);
    d.y = 0;
    return unit(d);
}
} // namespace
std::span<const MonsterDefinition> monsterCatalog() {
    return Catalog;
}
const MonsterDefinition *monsterDefinition(int id) {
    for (const auto &d : Catalog)
        if (d.id == id)
            return &d;
    return nullptr;
}
std::string monsterIdText(int id) {
    auto result = std::to_string(id / 10000) + "." + std::to_string(id / 100 % 100);
    if (id % 100)
        result += "." + std::to_string(id % 100);
    return result;
}

EntityId Simulation::spawnMonster(int id, Vector3 position) {
    const auto *d = monsterDefinition(id);
    if (!d)
        return 0;
    const auto entity = spawn(EnemyKind::Monster, position);
    if (!entity)
        return 0;
    auto &e = enemies.back();
    e.monster = id;
    e.hp = e.maxHp = d->hp;
    e.radius = d->radius;
    e.home = e.position;
    e.facing = rotateY({1, 0, 0}, float(entity % 8) * Pi / 4 + Pi / 4);
    e.observedShots = stats.shots;
    e.friendly = id == monsterId(23, 0, 1);
    if (id == monsterId(26, 2) || id == monsterId(55, 2))
        queueMonster(monsterId(96), add(position, {1.2f, 0, 0}), entity);
    if (type(e) == 35 && (variant(e) == 0 || variant(e) == 2))
        queueMonster(monsterId(35, variant(e) + 1), add(position, {1, 0, 0}), entity);
    if (id == monsterId(41, 3))
        queueMonster(monsterId(840), add(position, {1.5f, 0, 0}), entity);
    return entity;
}
void Simulation::queueMonster(int id, Vector3 at, EntityId partner, int generation, bool collapsed) {
    if (pendingMonsters_.size() + livingEnemies() >= limits.enemies || generation > 4) {
        suppress({}, "monster offspring capacity");
        return;
    }
    pendingMonsters_.push_back({id, at, partner, generation, collapsed});
}
void Simulation::flushMonsterSpawns(Random *placement, float playerClearance) {
    // Copy a request before spawning: spawn can append a paired child to this queue.
    size_t cursor = 0;
    while (cursor < pendingMonsters_.size() && cursor < limits.enemies) {
        const auto request = pendingMonsters_[cursor++];
        const auto *d = monsterDefinition(request.id);
        if (!d)
            continue;
        Vector3 at = request.position;
        at.y = .85f;
        bool placed = false;
        for (int attempt = 0; attempt < 65; ++attempt) {
            if (attempt)
                at = add(request.position,
                         rotateY({.8f + float(attempt / 8) * .45f, 0, 0}, float(attempt % 8) * Pi / 4));
            at.y = .85f;
            if ((placement && arena.roomAt(at) != room) || arena.blocked(at, d->radius) ||
                distance(at, player.position) < std::max(playerClearance, d->radius + .65f))
                continue;
            bool occupied = false;
            for (const auto &other : enemies)
                if (other.alive && distance(at, other.position) < d->radius + other.radius + .05f) {
                    occupied = true;
                    break;
                }
            if (!occupied) {
                placed = true;
                break;
            }
        }
        if (!placed) {
            suppress({}, "monster offspring placement");
            continue;
        }
        auto entity = spawnMonster(request.id, at);
        if (!entity)
            continue;
        auto &e = *findEnemy(entity);
        if (placement)
            e.cooldown = placement->real(.6f, 1.8f);
        e.partner = request.partner;
        e.generation = request.generation;
        if (e.monster == monsterId(24, 3))
            e.maxHp *= std::pow(.7f, float(e.generation));
        if (request.collapsed) {
            e.state = EnemyState::Collapsed;
            e.stateTime = 2.5f;
            e.hp = e.maxHp * .25f;
        }
        if (request.id == monsterId(840)) {
            if (auto *parent = findEnemy(request.partner))
                parent->partner = entity;
        }
    }
    pendingMonsters_.clear();
}
size_t Simulation::roomThreats() const {
    return size_t(std::count_if(enemies.begin(), enemies.end(), [](const Enemy &e) {
        const auto *d = monsterDefinition(e.monster);
        return e.alive && !e.friendly && (!d || !d->roomHazard);
    }));
}
void Simulation::spawnMonsterDebug(int id) {
    const auto *d = monsterDefinition(id);
    if (!d)
        return;
    const auto &bounds = arena.rooms[size_t(room)].bounds;
    for (int attempt = 0; attempt < 240; ++attempt) {
        Vector3 p{encounterRng.real(bounds.min.x + 1, bounds.max.x - 1), .85f,
                  encounterRng.real(bounds.min.z + 1, bounds.max.z - 1)};
        if (arena.blocked(p, d->radius) || distance(p, player.position) < 6)
            continue;
        bool occupied = false;
        for (const auto &other : enemies)
            if (other.alive && distance(p, other.position) < d->radius + other.radius + .2f)
                occupied = true;
        if (occupied)
            continue;
        if (spawnMonster(id, p)) {
            debugScenario = true;
            flushMonsterSpawns();
            announce(monsterIdText(id) + " / " + d->name);
        }
        return;
    }
    announce("No safe space for this enemy in the current room.");
}
void Simulation::monsterPattern(const Enemy &e, int count, float angle, float speed, ProjectileKind kind) {
    for (int n = 0; n < count; ++n)
        shootEnemy(e, rotateY({1, 0, 0}, angle + float(n) * 2 * Pi / float(count)), 10, speed,
                   kind == ProjectileKind::BurstShot ? 1 : 0, kind);
}
void Simulation::monsterPatch(const Enemy &e, HazardKind kind, Vector3 at, float radius, float delay,
                              float duration) {
    Hazard h;
    h.kind = kind;
    h.position = at;
    h.origin = e.position;
    h.radius = radius;
    h.delay = delay;
    h.duration = duration;
    h.damage = kind == HazardKind::Tar ? 0 : kind == HazardKind::MonsterBomb ? 20 : 8;
    h.context.sourceEntity = e.id;
    addHazard(h);
}
void Simulation::monsterBeam(const Enemy &e, Vector3 dir, float delay) {
    auto end = add(e.position, mul(dir, 32));
    const auto hit = arena.trace(e.position, end, .1f);
    if (hit.hit)
        end = add(e.position, mul(sub(end, e.position), std::max(0.0f, hit.t - .005f)));
    Hazard h;
    h.kind = HazardKind::Beam;
    h.origin = e.position;
    h.position = end;
    h.radius = type(e) == 60 && variant(e) == 0 ? .16f : .35f;
    h.delay = delay;
    h.duration = .65f;
    h.damage = 16;
    h.context.sourceEntity = e.id;
    addHazard(h);
}
void Simulation::monsterLines(const Enemy &e, HazardKind kind, bool diagonal) {
    for (int n = 0; n < 4; ++n) {
        const auto dir = rotateY({1, 0, 0}, float(n) * Pi / 2 + (diagonal ? Pi / 4 : 0));
        for (int step = 1; step <= 10; ++step) {
            const auto at = add(e.position, mul(dir, float(step) * 1.5f));
            if (!arena.contains(at) || !arena.sight(e.position, at))
                break;
            monsterPatch(e, kind, at, .8f, .45f + float(step) * .065f,
                         kind == HazardKind::MonsterBomb ? 0 : 2.5f);
        }
    }
}
void Simulation::attackMonster(Enemy &e) {
    const auto &d = *monsterDefinition(e.monster);
    const int t = type(e), v = variant(e);
    auto aim = flatDirection(e.position, e.target);
    const auto projectile = (t == 26 && v == 2)   ? ProjectileKind::Homing
                            : (t == 14 && v == 2) ? ProjectileKind::SplitShot
                            : (t == 15 && v == 1) ? ProjectileKind::Tar
                            : (t == 15 && v == 3) ? ProjectileKind::Flame
                                                  : ProjectileKind::Bullet;
    switch (d.attack) {
    case A::Shot:
        if (t == 27 && v == 3) {
            for (int n = 0; n < 4; ++n)
                shootEnemy(e, aim, 14, 7 + float(n) * 2, 0, ProjectileKind::Rock);
        } else
            shootEnemy(e, aim, 10, 9, 0, projectile);
        break;
    case A::Spread: {
        const int count = (t == 14 || t == 86) ? (v == 2 ? 4 : 2) : (t == 27 && v == 1) ? 5 : 3;
        for (int n = 0; n < count; ++n)
            shootEnemy(e, rotateY(aim, (float(n) - float(count - 1) / 2) * .22f), 10, 9, 0, projectile);
        break;
    }
    case A::Cross:
        monsterPattern(e, 4, (t == 15 && v == 3) ? .12f : 0, 9, projectile);
        if (t == 59 && ++e.phase % 3 == 0)
            monsterPatch(e, HazardKind::MonsterBomb, e.target, 2.2f, 1, 0);
        break;
    case A::Diagonal:
        monsterPattern(e, 4, Pi / 4, 9, projectile);
        break;
    case A::Ring:
        if (t == 57 && v == 2)
            for (int n = 0; n < 8; ++n)
                shootEnemy(e, rotateY({1, 0, 0}, float(n) * Pi / 4), 10, 8, 1);
        else if (t == 29) {
            constexpr std::array<int, 4> rings{4, 6, 8, 12};
            monsterPattern(e, rings[size_t(e.phase++ % 4)], e.age * .15f, 8);
            e.auxiliary = .18f;
        } else
            monsterPattern(e, 8, e.age * .15f, 8);
        break;
    case A::Burst:
        for (int n = 0; n < 7; ++n)
            shootEnemy(e, rotateY(aim, combatRng.real(-Pi, Pi)), 8, combatRng.real(4, 8), 0,
                       t == 34 ? ProjectileKind::Tar : projectile);
        break;
    case A::Lob:
        monsterPatch(e, HazardKind::MonsterBomb, e.target, 2.2f, .95f, 0);
        if (t == 87 && v == 1) {
            Enemy at = e;
            at.position = e.target;
            monsterLines(at, HazardKind::Fire);
        }
        break;
    case A::Spawn: {
        int child = monsterId(85), count = 1;
        if (t == 22) {
            child = v == 0   ? monsterId(18)
                    : v == 1 ? monsterId(23, 1)
                    : v == 2 ? monsterId(38, 1, 1)
                             : monsterId(222);
            count = v == 3 ? 6 : 1;
        }
        if (t == 61)
            child = monsterId(861);
        // Limit each summoner's live children as well as the global population.
        const auto children = std::count_if(enemies.begin(), enemies.end(), [&](const Enemy &other) {
            return other.alive && other.partner == e.id;
        });
        if (children < 6)
            for (int n = 0; n < std::min(count, 6 - int(children)); ++n)
                queueMonster(child, add(e.position, rotateY({1.6f, 0, 0}, float(n) * 2 * Pi / float(count))),
                             e.id, e.generation + 1);
        break;
    }
    case A::Beam:
        monsterBeam(e, aim);
        break;
    case A::DoubleBeam:
        monsterBeam(e, aim);
        monsterBeam(e, mul(aim, -1));
        break;
    case A::QuadBeam:
        for (int n = 0; n < 4; ++n)
            monsterBeam(e, rotateY(aim, float(n) * Pi / 2));
        break;
    case A::Head:
        if (t == 39)
            shootEnemy(e, aim, 16, 12, 0, ProjectileKind::ReturningHead);
        else
            for (auto &child : enemies)
                if (child.alive && child.partner == e.id && type(child) == 35) {
                    child.state = EnemyState::Charging;
                    child.stateTime = .7f;
                    child.facing = aim;
                }
        break;
    case A::Light:
        for (int n = 0; n < 4; ++n)
            monsterPatch(e, HazardKind::HolyLight,
                         add(e.target, rotateY({float(n) * .7f, 0, 0}, float(n) * Pi / 2)), .85f,
                         .65f + float(n) * .18f, .3f);
        break;
    case A::Spitty:
        shootEnemy(e, e.facing, 10, 8);
        if (v == 1) {
            monsterPattern(e, 7, e.age, 6);
            for (int n = 0; n < 4; ++n)
                shootEnemy(e, e.facing, 10, 9 + float(n) * 2);
        }
        break;
    default:
        break;
    }
}

void Simulation::moveMonster(Enemy &e, Vector3 velocity, float dt) {
    const auto before = e.position;
    // Keep movement, projectile collision and the rendered body on the same navigable surface.
    e.position = arena.move(before, mul(velocity, dt), e.radius);
    e.velocity = mul(sub(e.position, before), 1 / dt);
}

void Simulation::updateMonster(Enemy &e, float dt) {
    const auto &d = *monsterDefinition(e.monster);
    const int t = type(e), v = variant(e);
    e.cooldown -= dt;
    e.auxiliary -= dt;
    e.trailTime -= dt;
    e.age += dt;
    e.pathTime -= dt;
    e.flash = std::max(0.0f, e.flash - dt);
    e.velocity = {};
    e.lift = 0;
    if (t == 29 && v == 3 && e.phase > 0 && e.phase < 4 && e.auxiliary <= 0)
        attackMonster(e);
    if (e.monster == monsterId(29))
        for (const auto &hazard : hazards)
            if (hazard.kind == HazardKind::Fire && hazard.age >= hazard.delay &&
                distance(hazard.position, e.position) < hazard.radius) {
                e.monster = monsterId(54);
                break;
            }
    auto target = player.position;
    if (e.friendly) {
        float best = 100000;
        for (const auto &other : enemies)
            if (other.alive && !other.friendly && other.id != e.id) {
                const float range = distance(e.position, other.position);
                if (range < best) {
                    best = range;
                    target = other.position;
                    e.partner = other.id;
                }
            }
        if (best == 100000)
            return;
    }
    const auto direction = flatDirection(e.position, target);
    const float dist = distance(e.position, target);
    const bool sight = arena.sight(e.position, target);
    if (t == 96) {
        const auto *parent = findEnemy(e.partner);
        if (!parent || !parent->alive) {
            if (parent && parent->monster == monsterId(55, 2)) {
                e.alive = false;
                return;
            }
            e.monster = monsterId(18);
            e.partner = 0;
            e.hp = e.maxHp = 32;
            return;
        }
    }
    if (t == 35 && (v == 1 || v == 3)) {
        const auto *parent = findEnemy(e.partner);
        if (!parent || !parent->alive) {
            e.monster = monsterId(26, v == 3 ? 1 : 0);
            e.partner = 0;
            return;
        }
    }
    if (t == 41 && v == 3 && e.partner) {
        const auto *partner = findEnemy(e.partner);
        if (!partner || !partner->alive) {
            e.alive = false;
            return;
        }
    }
    if (e.state == EnemyState::Stunned) {
        e.stateTime -= dt;
        if (e.stateTime <= 0)
            e.state = EnemyState::Ready;
        return;
    }
    if (e.state == EnemyState::Collapsed) {
        e.stateTime -= dt;
        if (v == 1)
            moveMonster(e, mul(direction, -1.3f), dt);
        if (e.stateTime <= 0) {
            e.state = EnemyState::Ready;
            e.hp = e.maxHp;
            e.cooldown = .7f;
        }
        return;
    }
    if (e.state == EnemyState::Buried || e.state == EnemyState::Teleporting) {
        e.stateTime -= dt;
        if (e.stateTime <= 0) {
            if (!arena.blocked(e.target, e.radius) && distance(e.target, player.position) > 2)
                e.position = e.target;
            e.state = EnemyState::Exposed;
            e.stateTime = .6f;
            e.cooldown = .8f;
            e.target = target;
        }
        return;
    }
    if (e.state == EnemyState::Returning) {
        const auto *parent = findEnemy(e.partner);
        const auto destination = t == 35 && parent ? parent->position : e.home;
        moveMonster(e, mul(flatDirection(e.position, destination), 3), dt);
        if (distance(e.position, destination) < 1.3f) {
            e.state = EnemyState::Ready;
            e.cooldown = 1;
        }
        return;
    }
    if (e.state == EnemyState::Exposed) {
        e.stateTime -= dt;
        if (e.stateTime <= 0)
            e.state = EnemyState::Ready;
        return;
    }
    if (e.state == EnemyState::Jumping) {
        e.stateTime -= dt;
        const float progress = 1 - std::clamp(e.stateTime / .65f, 0.0f, 1.0f);
        e.lift = std::sin(progress * Pi) * (t == 34 ? 3 : 1.2f);
        moveMonster(e,
                    mul(flatDirection(e.position, e.target),
                        std::min(t == 34 ? 20.0f : d.speed,
                                 distance(e.position, e.target) / std::max(dt, e.stateTime))),
                    dt);
        if (e.stateTime <= 0) {
            e.state = EnemyState::Ready;
            e.cooldown = d.cooldown;
            e.lift = 0;
            if (d.attack != A::None) {
                e.target = target;
                if (t == 29 && v == 3)
                    e.phase = 0;
                attackMonster(e);
            }
            if ((t == 34 && v == 1) || (t == 29 && v == 2))
                monsterPatch(e, HazardKind::Tar, e.position, 1.6f, 0, 3);
            if (t == 840)
                monsterPatch(e, HazardKind::Creep, e.position, 1, 0, 3);
        }
    } else if (e.state == EnemyState::Charging) {
        e.stateTime -= dt;
        const auto before = e.position;
        const float speed = t == 41 && v == 1 ? 16 : t == 35 ? 12 : 11;
        moveMonster(e, mul(e.facing, speed), dt);
        const bool impact = distance(before, e.position) < speed * dt * .65f;
        if (t == 23 && v == 2 && e.trailTime <= 0) {
            monsterPatch(e, HazardKind::Tar, e.position, .7f, 0, 2.5f);
            e.trailTime = .22f;
        }
        if (impact && t == 23 && v == 2 && e.stateTime > 0)
            e.facing = mul(e.facing, -1);
        else if (impact || e.stateTime <= 0) {
            if (t == 41 && v == 4)
                monsterLines(e, HazardKind::Fire);
            if (t == 38) {
                e.target = target;
                attackMonster(e);
            }
            e.state = (t == 44 || t == 35) ? EnemyState::Returning : EnemyState::Stunned;
            e.stateTime = .7f;
            e.cooldown = d.cooldown;
        }
    } else if (e.state == EnemyState::Windup) {
        e.stateTime -= dt;
        if (e.stateTime <= 0) {
            e.cooldown = d.cooldown;
            e.state = EnemyState::Ready;
            if (d.motion == M::Charge || (t == 40 && v == 2)) {
                e.state = EnemyState::Charging;
                e.stateTime = 1.2f;
                e.facing = flatDirection(e.position, e.target);
            } else if (d.motion == M::Hop) {
                e.state = EnemyState::Jumping;
                e.stateTime = .65f;
            } else {
                attackMonster(e);
                if (t == 27) {
                    e.state = EnemyState::Exposed;
                    e.stateTime = .8f;
                }
                if (d.motion == M::Burrow)
                    e.auxiliary = .75f;
            }
        }
    } else {
        if (t == 10 && v == 0 && sight)
            e.awakened = true;
        if (t == 30)
            e.hp = std::min(e.maxHp, e.hp + dt * 12);
        if (t == 861) {
            e.hp = std::min(e.maxHp, e.hp + dt * 3);
            if (e.age > 7) {
                e.monster = monsterId(61, 6);
                e.hp = e.maxHp = 48;
                e.radius = .5f;
            }
        }
        if ((t == 32 || (t == 40 && v == 1) || (t == 25 && v == 5) || (t == 10 && v == 2)) &&
            e.trailTime <= 0) {
            monsterPatch(e,
                         t == 25   ? HazardKind::Gas
                         : t == 10 ? HazardKind::Fire
                                   : HazardKind::Creep,
                         e.position, .7f, 0, 2.6f);
            e.trailTime = .5f;
        }
        if ((t == 16 && v == 2 && dist < 1.4f) || (t == 16 && v < 2 && e.age > 12 && dist < 4)) {
            Event death;
            death.type = EventType::Damage;
            death.target = e.id;
            death.damage = 10000;
            queueRoot(death);
        }
        Vector3 movement{};
        switch (d.motion) {
        case M::Still:
            break;
        case M::Chase:
        case M::Teleport:
        case M::Burrow:
            if (d.speed > 0)
                movement = mul(direction, d.speed * (t == 10 && v == 0 && e.awakened ? 1.5f : 1));
            if (d.attack != A::None && dist < 5 && t != 10 && t != 87)
                movement = {};
            break;
        case M::Flee:
            movement = mul(direction, dist < 10 ? -d.speed : d.speed * .3f);
            break;
        case M::Mirror:
            movement = {-player.velocity.x, 0, -player.velocity.z};
            if (stats.shots != e.observedShots) {
                e.target = add(e.position, mul(unit(sub(player.aim, player.position)), -10));
                attackMonster(e);
            }
            e.observedShots = stats.shots;
            break;
        case M::Orbit: {
            const auto *parent = findEnemy(e.partner);
            auto center = parent && parent->alive ? parent->position : target;
            const auto goal = add(center, rotateY({t == 35 ? 1.1f : 1.6f, 0, 0}, e.age * 2 + float(e.id)));
            movement = mul(flatDirection(e.position, goal), std::min(6.0f, distance(goal, e.position) / dt));
            break;
        }
        case M::Wall: {
            float best = 1e9f;
            Vector3 anchor = e.home;
            for (const auto &wall : arena.walls) {
                const Vector3 p{std::clamp(e.position.x, wall.min.x, wall.max.x), .85f,
                                std::clamp(e.position.z, wall.min.z, wall.max.z)};
                if (distance(p, e.position) < best) {
                    best = distance(p, e.position);
                    anchor = p;
                }
            }
            auto away = flatDirection(anchor, e.position);
            movement = add(mul(rotateY(away, Pi / 2), d.speed), mul(away, (e.radius + .3f - best) * 2));
            break;
        }
        case M::Chain: {
            const auto *leader = findEnemy(e.partner);
            if (leader && leader->alive) {
                movement =
                    mul(flatDirection(e.position, leader->position),
                        d.speed * std::clamp(distance(e.position, leader->position) - .8f, 0.0f, 1.4f));
                break;
            }
            [[fallthrough]];
        }
        case M::Wander:
        case M::Charge:
        case M::Hop:
        case M::Bounce:
            if (d.motion != M::Bounce && e.auxiliary <= 0) {
                // With no active-item charges in DeathWard, Bulbs remain harmless wanderers.
                e.facing = rotateY({1, 0, 0}, t == 61 && v == 5 ? float(combatRng.bounded(4)) * Pi / 2
                                                                : combatRng.real(-Pi, Pi));
                e.auxiliary = combatRng.real(.7f, 1.8f);
            }
            movement = mul(e.facing, d.speed);
            if (d.motion == M::Hop)
                movement = {};
            if (t == 85 && dist < 7 && sight)
                movement = mul(direction, d.speed);
            break;
        }
        if (t == 10 && v == 3) {
            // Stable facial temperament: chase, hesitate, or back away while spitting.
            const int temperament = int(e.id % 3);
            if (temperament == 1 && std::fmod(e.age, 2.0f) < .7f)
                movement = {};
            if (temperament == 2 && dist < 5)
                movement = mul(direction, -d.speed);
        }
        if (!sight && length(movement) > .1f && (d.motion == M::Chase || d.motion == M::Charge)) {
            if (e.pathTime <= 0) {
                e.path = arena.path(e.position, target, e.radius);
                e.pathTime = 1.1f;
            }
            while (!e.path.empty() && distance(e.position, e.path.front()) < .4f)
                e.path.erase(e.path.begin());
            if (!e.path.empty())
                movement = mul(flatDirection(e.position, e.path.front()), d.speed);
        }
        const auto before = e.position;
        moveMonster(e, movement, dt);
        if (length(movement) > .1f && distance(before, e.position) < length(movement) * dt * .5f) {
            if (d.motion == M::Bounce) {
                // Reflect only the blocked component; never drift through a boundary.
                const auto probe = arena.move(before, {movement.x * dt, 0, 0}, e.radius);
                if (std::abs(probe.x - before.x) < std::abs(movement.x * dt) * .5f)
                    e.facing.x = -e.facing.x;
                else
                    e.facing.z = -e.facing.z;
            } else {
                e.facing = rotateY(e.facing, Pi / 2);
                e.auxiliary = .4f;
            }
        }
        if (t == 60) {
            const float angle = std::atan2(e.facing.z, e.facing.x);
            const float delta = std::remainder(std::atan2(direction.z, direction.x) - angle, 2 * Pi);
            const float next = angle + std::clamp(delta, -dt * .9f, dt * .9f);
            e.facing = {std::cos(next), 0, std::sin(next)};
        } else if (length(movement) > .1f && d.motion != M::Bounce)
            e.facing = unit(movement);
        const bool aligned = (t == 23 && v == 3)
                                 ? std::abs(std::abs(direction.x) - std::abs(direction.z)) < .16f
                                 : std::abs(direction.x) < .18f || std::abs(direction.z) < .18f;
        bool attack = d.attack != A::None && d.motion != M::Mirror && sight && dist < 24;
        if (t == 30 && e.hp < e.maxHp - .1f)
            attack = false;
        if (t == 60 && v < 2)
            attack = attack && dot(e.facing, direction) > .97f;
        if (d.motion == M::Charge || (t == 40 && v == 2))
            attack = sight && aligned && dist < 22;
        if (d.motion == M::Hop)
            attack = true;
        if (e.cooldown <= 0 && attack) {
            e.state = EnemyState::Windup;
            e.stateTime = d.windup;
            e.target = target;
            if (d.motion == M::Hop && t != 34) {
                const auto hop = ((t == 29 && v == 1) || t == 54 || t == 884 || dist < 6)
                                     ? direction
                                     : rotateY({1, 0, 0}, combatRng.real(-Pi, Pi));
                e.target = add(e.position, mul(hop, d.speed * .65f));
            }
            if (t == 34 && distance(e.position, e.target) > 12)
                e.target = add(e.position, mul(direction, 12));
        }
        if ((d.motion == M::Burrow || d.motion == M::Teleport) && e.auxiliary <= 0 &&
            e.state == EnemyState::Ready) {
            const auto &bounds = arena.rooms[size_t(room)].bounds;
            for (int n = 0; n < 48; ++n) {
                Vector3 p{combatRng.real(bounds.min.x + 1, bounds.max.x - 1), .85f,
                          combatRng.real(bounds.min.z + 1, bounds.max.z - 1)};
                if (arena.blocked(p, e.radius) || distance(p, target) < 3 || distance(p, target) > 14)
                    continue;
                e.target = p;
                e.state = d.motion == M::Burrow ? EnemyState::Buried : EnemyState::Teleporting;
                e.stateTime = 1;
                e.auxiliary = 5;
                break;
            }
        }
    }
    if (d.contact && e.lift < .8f && distance(e.position, target) < e.radius + .48f && sight) {
        if (e.friendly) {
            if (e.cooldown <= 0) {
                Event hit;
                hit.type = EventType::Damage;
                hit.target = e.partner;
                hit.damage = 28;
                queueRoot(hit);
                e.cooldown = .7f;
            }
        } else
            hurtPlayer(t == 24 ? 20 : 10);
    }
}

bool Simulation::collapseMonster(Enemy &e) {
    if (type(e) != 24 || e.state == EnemyState::Collapsed)
        return false;
    e.state = EnemyState::Collapsed;
    e.stateTime = 2.5f;
    e.hp = std::max(12.0f, e.maxHp * .25f);
    e.lift = 0;
    if (variant(e) == 2) {
        queueMonster(monsterId(85), e.position, 0, e.generation + 1);
        monsterPatch(e, HazardKind::Tar, e.position, 1.3f, 0, 4);
    }
    if (variant(e) == 3 && e.generation < 3) {
        ++e.generation;
        e.maxHp *= .7f;
        e.hp = e.maxHp * .3f;
        queueMonster(e.monster, e.position, 0, e.generation, true);
    }
    return true;
}
void Simulation::monsterDeath(const Enemy &e, const Event &event) {
    const int t = type(e), v = variant(e);
    // Resolve orbiters before room completion can remove a defeated parent's last threat.
    for (auto &child : enemies) {
        if (!child.alive || child.partner != e.id || child.monster != monsterId(96))
            continue;
        if (t == 55 && v == 2)
            child.alive = false;
        else {
            child.monster = monsterId(18);
            child.partner = 0;
            child.hp = child.maxHp = 32;
        }
    }
    auto offspring = [&](int id, int count) {
        for (int n = 0; n < count; ++n)
            queueMonster(id, add(e.position, rotateY({1, 0, 0}, float(n) * 2 * Pi / float(count))), 0,
                         e.generation + 1);
    };
    auto bomb = [&] { monsterPatch(e, HazardKind::MonsterBomb, e.position, 2.8f, .7f, 0); };
    if (t == 10 && v < 3)
        offspring(monsterId(11, combatRng.bounded(4) ? 1 : 0), 1);
    if (t == 16) {
        if (v == 0) {
            offspring(monsterId(18), 2);
            offspring(monsterId(13), 1);
            if (e.age > 12)
                monsterPattern(e, 4);
        }
        if (v == 1) {
            bomb();
            monsterPattern(e, e.age > 12 ? 8 : 4, Pi / 4);
        }
        if (v == 2)
            bomb();
    }
    if (t == 22) {
        if (v == 0) {
            offspring(monsterId(18), 3);
            offspring(monsterId(14), 1);
        }
        if (v == 1)
            offspring(monsterId(23, 1), 2);
        if (v == 2)
            offspring(monsterId(77), 2);
        if (v == 3) {
            offspring(monsterId(18), 3);
            offspring(monsterId(61), 2);
            offspring(monsterId(25), 1);
        }
    }
    if (t == 23 && v == 1)
        monsterPattern(e, 4, Pi / 4);
    if (t == 24 && v == 2)
        monsterPatch(e, HazardKind::Tar, e.position, 1.6f, 0, 4);
    if (t == 25) {
        if (v == 0 || v == 2)
            bomb();
        if (v == 1)
            monsterPattern(e, 6);
        if (v == 2) {
            monsterPattern(e, 4);
            if (combatRng.bounded(2))
                offspring(monsterId(23, 1), 1);
        }
        if (v == 3)
            monsterLines(e, HazardKind::Fire, e.monster % 100 == 1);
        if (v == 4)
            monsterPattern(e, 3);
        if (v == 5) {
            monsterPattern(e, 6);
            monsterPatch(e, HazardKind::Gas, e.position, 3, .4f, 4);
        }
        if (v == 6) {
            bomb();
            monsterLines(e, HazardKind::MonsterBomb);
        }
    }
    if (t == 26 && v == 1)
        monsterPattern(e, 4);
    if (t == 29 && v == 2)
        offspring(monsterId(884), 5);
    if (t == 31 && v == 1) {
        monsterPattern(e, 8);
        monsterPattern(e, 8, Pi / 8, 6);
    }
    if (t == 35) {
        if (v == 0 || v == 2)
            offspring(monsterId(11), 1);
        else if (auto *parent = findEnemy(e.partner); parent && parent->alive) {
            parent->monster = monsterId(11);
            parent->hp = parent->maxHp = 40;
        }
    }
    if (t == 41 && v == 2)
        offspring(monsterId(41, 3), 1);
    if (t == 55 && v > 0)
        bomb();
    if (t == 57)
        offspring(v == 0 ? monsterId(32) : v == 1 ? monsterId(40) : monsterId(862), 2);
    if (t == 61) {
        if (v == 0 || v == 6)
            monsterPattern(e, 4);
        if (v == 1)
            monsterPatch(e, HazardKind::MonsterBomb, player.position, 2.2f, 1, 0);
        if (v == 2)
            for (int n = 0; n < 4; ++n)
                monsterBeam(e, rotateY({1, 0, 0}, float(n) * Pi / 2), .9f);
        if (v == 3) {
            monsterPattern(e, 4, Pi / 4, 9, ProjectileKind::Tar);
            monsterPatch(e, HazardKind::Tar, e.position, 2, 0, 4);
        }
        if (v == 4)
            offspring(monsterId(853), 4);
        if (v == 7)
            monsterPattern(e, 6, 0, 7, ProjectileKind::BurstShot);
    }
    if (t == 80)
        offspring(monsterId(18), 2);
    if (t == 87 && v == 0 && combatRng.bounded(2))
        offspring(monsterId(238), 1);
    if (t == 861) {
        offspring(monsterId(853), 2);
        monsterPatch(e, HazardKind::Creep, e.position, 1.6f, 0, 4);
    }
    (void)event;
}
} // namespace dw
