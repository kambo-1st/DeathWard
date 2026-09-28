#include "combat/Simulation.hpp"
#include <bit>
#include <iostream>
#include <queue>
#include <stdexcept>

namespace {
void check(bool value, const std::string &message) {
    if (!value)
        throw std::runtime_error(message);
}
uint64_t fingerprint(const dw::Arena &arena) {
    uint64_t result = 1469598103934665603ULL;
    auto value = [&](float f) { result = (result ^ std::bit_cast<uint32_t>(f)) * 1099511628211ULL; };
    auto point = [&](Vector3 p) {
        value(p.x);
        value(p.y);
        value(p.z);
    };
    for (const auto &room : arena.rooms) {
        point(room.bounds.min);
        point(room.bounds.max);
        point(room.center);
        point(room.entry);
        point(room.exit);
        point(room.objective);
        value(float(room.shape));
        value(float(room.kind));
        value(float(room.depth));
    }
    for (const auto &box : arena.floors) {
        point(box.min);
        point(box.max);
    }
    for (const auto &box : arena.walls) {
        point(box.min);
        point(box.max);
    }
    for (const auto &p : arena.passages) {
        value(float(p.rooms[0]));
        value(float(p.rooms[1]));
        value(float(p.locked));
        point(p.from);
        point(p.to);
    }
    for (const auto &key : arena.keys) {
        value(float(key.room));
        point(key.position);
    }
    return result;
}
std::set<int> reachable(const dw::Arena &arena) {
    std::set<int> seen{0};
    std::queue<int> queue;
    queue.push(0);
    while (!queue.empty()) {
        const int room = queue.front();
        queue.pop();
        for (int index : arena.rooms[size_t(room)].passages) {
            const auto &p = arena.passages[size_t(index)];
            const int next = p.rooms[0] == room ? p.rooms[1] : p.rooms[0];
            if (!p.locked && seen.insert(next).second)
                queue.push(next);
        }
    }
    return seen;
}
void verifyRoute(const dw::Arena &arena, Vector3 from, Vector3 goal, float radius, const std::string &label) {
    check(!arena.blocked(from, radius) && !arena.blocked(goal, radius), label + ": clear endpoints");
    const auto route = arena.path(from, goal, radius);
    check(!route.empty() && dw::distance(route.back(), goal) < 0.001f, label + ": reachable endpoint");
    for (const auto &point : route) {
        check(arena.clear(from, point, radius), label + ": route respects collision geometry");
        const int steps = int(dw::distance(from, point) / 0.3f) + 1;
        for (int i = 0; i <= steps; ++i)
            check(
                !arena.blocked(dw::add(from, dw::mul(dw::sub(point, from), float(i) / float(steps))), radius),
                label + ": route stays on the mine floor");
        from = point;
    }
}
void verifyConnectedFloor(const dw::Arena &arena) {
    auto center = [](dw::FloorCell c) -> Vector3 {
        return {(float(c.first) + 0.5f) * dw::FloorTile, 0.85f, (float(c.second) + 0.5f) * dw::FloorTile};
    };
    std::set<dw::FloorCell> walkable;
    for (auto c : arena.floorCells)
        if (!arena.blocked(center(c), 0.6f))
            walkable.insert(c);
    std::set<dw::FloorCell> reached{*walkable.begin()};
    std::queue<dw::FloorCell> queue;
    queue.push(*walkable.begin());
    while (!queue.empty()) {
        const auto c = queue.front();
        queue.pop();
        for (auto [x, z] :
             {dw::FloorCell{0, -1}, dw::FloorCell{1, 0}, dw::FloorCell{0, 1}, dw::FloorCell{-1, 0}}) {
            dw::FloorCell next{c.first + x, c.second + z};
            if (walkable.contains(next) && !reached.contains(next) &&
                arena.clear(center(c), center(next), 0.6f)) {
                reached.insert(next);
                queue.push(next);
            }
        }
    }
    check(reached.size() == walkable.size(), "obstacles never isolate walkable floor or enemy spawn areas");
}
} // namespace

int main() {
    try {
        std::set<uint64_t> maps;
        for (uint64_t seed = 0; seed < 64; ++seed) {
            dw::Arena arena(seed), repeated(seed);
            check(fingerprint(arena) == fingerprint(repeated), "same seed reproduces all geometry");
            check(maps.insert(fingerprint(arena)).second, "different seeds produce different maps");
            std::set<std::pair<float, float>> sizes;
            std::set<int> shapes;
            for (const auto &room : arena.rooms) {
                sizes.insert({room.bounds.max.x - room.bounds.min.x, room.bounds.max.z - room.bounds.min.z});
                shapes.insert(room.shape);
                check(!room.obstacles.empty(),
                      "each room contains seeded obstacles (seed " + std::to_string(seed) + ")");
                verifyRoute(arena, room.entry, room.center, 0.48f, "room entry");
                verifyRoute(arena, room.center, room.exit, 0.48f, "room exit");
                verifyRoute(arena, room.center, room.objective, 0.48f, "room objective");
            }
            check(sizes.size() == dw::RoomCount && shapes.size() == 4,
                  "every expedition varies room sizes and footprints");
            const auto initiallyReachable = reachable(arena);
            int powers = 0, empty = 0, shops = 0, locked = 0, maxDegree = 0;
            for (int i = 0; i < dw::RoomCount; ++i) {
                const auto &room = arena.rooms[size_t(i)];
                maxDegree = std::max(maxDegree, int(room.passages.size()));
                if (room.kind == dw::RoomKind::Power)
                    ++powers;
                if (room.kind == dw::RoomKind::Empty)
                    ++empty;
                if (room.kind == dw::RoomKind::Shop)
                    ++shops;
                if (room.kind == dw::RoomKind::Combat || room.kind == dw::RoomKind::Empty ||
                    room.kind == dw::RoomKind::Shop)
                    check(initiallyReachable.contains(i),
                          "combat and empty rooms are accessible without spending a key");
                else {
                    check(room.passages.size() == 1 && !initiallyReachable.contains(i),
                          "special rooms have one locked entrance");
                }
            }
            check(powers >= 1 && powers <= 2, "one or two separate power rooms");
            check(shops == 1, "exactly one unlocked shop room");
            check(empty >= 1 && empty <= 2, "one or two additional enemy-free rooms");
            check(arena.rooms[0].kind == dw::RoomKind::Empty,
                  "the starting room is enemy-free for every seed");
            check(arena.rooms[2].kind == dw::RoomKind::Combat && arena.rooms[3].kind == dw::RoomKind::Combat,
                  "objective rooms retain combat encounters");
            check(arena.rooms[0].passages.size() >= 2 && maxDegree >= 3 &&
                      arena.passages.size() >= dw::RoomCount - 1,
                  "map has branching choices, with optional alternate routes");
            for (const auto &key : arena.keys) {
                check(initiallyReachable.contains(key.room),
                      "every key is reachable before opening any lock");
                verifyRoute(arena, arena.rooms[size_t(key.room)].center, key.position, 0.48f,
                            "key placement");
            }
            for (size_t i = 0; i < arena.passages.size(); ++i) {
                auto &passage = arena.passages[i];
                const auto start = arena.doorApproach(int(i), 0);
                const auto goal = arena.doorApproach(int(i), 1);
                if (passage.locked) {
                    ++locked;
                    const auto before = arena.move(start, dw::sub(goal, start), 0.48f);
                    check(dw::distance(before, start) < 0.001f, "locked doors block swept movement");
                    check(arena.path(start, goal, 0.48f).empty(),
                          "locked special rooms cannot be bypassed through another route");
                }
                passage.locked = false;
                arena.rebuildWalls();
                verifyRoute(arena, start, goal, 0.48f, "connected passage");
                verifyRoute(arena, goal, start, 0.48f, "reverse passage");
            }
            check(int(arena.keys.size()) == locked && locked == powers + 1,
                  "there is exactly one usable key per locked door");
            check(reachable(arena).size() == dw::RoomCount,
                  "collecting available keys can unlock the entire dungeon");
            verifyRoute(arena, arena.entrance, arena.exit, 0.48f, "complete expedition route");
            verifyRoute(arena, arena.rooms.back().entry, arena.rooms.back().bossSpawn, 1.2f,
                        "boss clearance");
            verifyConnectedFloor(arena);
        }
        dw::WorldState changed;
        changed.minersRescued = changed.altarDestroyed = changed.bossDefeated = true;
        dw::Simulation a(1866, 1, {}), b(1866, 99, changed);
        check(fingerprint(a.arena) == fingerprint(b.arena),
              "campaign outcomes and run IDs do not change the seeded map");
        a.godMode = a.debugScenario = true;
        for (int i = 0; i < dw::RoomCount; ++i) {
            a.player.position = a.arena.rooms[size_t(i)].entry;
            a.enterRoom(i);
            const auto initial = a.livingEnemies();
            a.spawnEnemies(40);
            check(a.livingEnemies() == initial + 40, "generated chambers support additional test enemies");
            for (const auto &enemy : a.enemies) {
                check(a.arena.roomAt(enemy.position) == i && !a.arena.blocked(enemy.position, enemy.radius),
                      "enemy spawns remain inside their chamber and clear of generated cover");
            }
        }
        dw::Simulation travel(1866, 1, {});
        travel.godMode = travel.debugScenario = true;
        travel.player.hp = 100;
        travel.clearRoom();
        const int passageIndex = travel.arena.rooms[0].passages.front();
        const auto &passage = travel.arena.passages[size_t(passageIndex)];
        const int fromSide = passage.rooms[0] == 0 ? 0 : 1;
        const int next = passage.rooms[size_t(1 - fromSide)];
        auto cross = [&](int side, int expected) {
            travel.player.position = travel.arena.doorApproach(passageIndex, side);
            dw::Input input;
            input.doorTarget = std::pair{passageIndex, side};
            travel.step(input);
            for (int i = 0; i < 1000 && travel.room != expected; ++i) {
                const auto previous = travel.player.position;
                travel.step({});
                check(dw::distance(previous, travel.player.position) < 0.101f,
                      "room traversal never teleports");
                check(!travel.arena.blocked(travel.player.position, 0.48f),
                      "closing entrance never traps the player in a gate");
            }
            check(travel.room == expected,
                  "doorway traversal selects the connected room, regardless of index");
        };
        cross(fromSide, next);
        for (int index : travel.arena.rooms[size_t(next)].passages) {
            const auto &p = travel.arena.passages[size_t(index)];
            check(p.closed(p.rooms[0] == next ? 0 : 1),
                  "all exits, including the previous entrance, seal during combat");
        }
        const auto gate = travel.arena.doorPosition(passageIndex, 1 - fromSide);
        const auto inside = travel.arena.doorApproach(passageIndex, 1 - fromSide);
        check(dw::distance(travel.arena.move(inside, dw::mul(dw::sub(gate, inside), 3), 0.48f), inside) <
                  0.001f,
              "the previous access physically blocks retreat during combat");
        travel.clearRoom();
        const auto cleared = travel.stats.rooms;
        const auto health = travel.player.hp;
        cross(1 - fromSide, 0);
        cross(fromSide, next);
        check(travel.roomClear && travel.stats.rooms == cleared && travel.player.hp == health,
              "revisiting cleared rooms cannot repeat encounters or farm healing");
        const auto &powerRoom = travel.arena.rooms[dw::RoomCount - 2];
        const int lockIndex = powerRoom.passages.front();
        const auto &lockedDoor = travel.arena.passages[size_t(lockIndex)];
        const int outside = lockedDoor.rooms[0] == dw::RoomCount - 2 ? 1 : 0;
        travel.enterRoom(lockedDoor.rooms[size_t(outside)]);
        travel.clearRoom();
        travel.player.position = travel.arena.doorApproach(lockIndex, outside);
        check(!travel.useDoor(lockIndex, outside) && travel.keys == 0 && lockedDoor.locked,
              "doors cannot unlock without a key");
        auto &key = travel.arena.keys.front();
        travel.enterRoom(key.room);
        travel.clearRoom();
        travel.player.position = key.position;
        travel.step({});
        travel.step({});
        check(travel.keys == 1 && key.collected, "randomly placed keys are collected exactly once");
        travel.enterRoom(lockedDoor.rooms[size_t(outside)]);
        travel.player.position = travel.arena.doorApproach(lockIndex, outside);
        check(travel.useDoor(lockIndex, outside) && travel.keys == 0 && !lockedDoor.locked,
              "unlocking consumes exactly one key");
        travel.player.position = travel.arena.doorApproach(lockIndex, outside);
        check(travel.useDoor(lockIndex, outside) && travel.keys == 0,
              "unlocked doors do not charge another key");
        std::cout << "PASS 64 seeds: deterministic varied geometry, connected floor, doors, objectives and "
                     "boss clearance\n"
                  << "PASS branches, reachable keys, locks, combat seals, unique pickups and revisits\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        return 1;
    }
}
