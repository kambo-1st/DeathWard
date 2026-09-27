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
    }
    for (const auto &box : arena.floors) {
        point(box.min);
        point(box.max);
    }
    for (const auto &box : arena.walls) {
        point(box.min);
        point(box.max);
    }
    return result;
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
            check(arena.path(arena.entrance, arena.rooms[1].center, 0.48f).empty(),
                  "closed encounter gate prevents skipping rooms");
            for (int i = 0; i < dw::RoomCount - 1; ++i) {
                const auto &passage = arena.passages[size_t(i)];
                const auto start = arena.rooms[size_t(i)].exit;
                const auto before = arena.move(start, dw::sub(passage.to, start), 0.48f);
                check(dw::distance(before, start) < 0.001f, "closed gates also block swept movement");
                arena.openPassage(i);
                verifyRoute(arena, start, arena.rooms[size_t(i + 1)].entry, 0.48f, "connected passage");
            }
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
            a.enterRoom(i);
            a.player.position = a.arena.rooms[size_t(i)].entry;
            a.spawnWave(40);
            check(a.livingEnemies() == 40, "generated chambers support full enemy waves");
            for (const auto &enemy : a.enemies) {
                check(a.arena.roomAt(enemy.position) == i && !a.arena.blocked(enemy.position, enemy.radius),
                      "enemy spawns remain inside their chamber and clear of generated cover");
            }
        }
        dw::Simulation travel(1866, 1, {});
        travel.godMode = travel.debugScenario = true;
        travel.player.hp = 100;
        travel.roomClear = true;
        travel.arena.openPassage(0);
        auto walk = [&](Vector3 target) {
            dw::Input input;
            input.moveTarget = target;
            travel.step(input);
            check(travel.moveDestination().has_value(), "connected destination has a mouse route");
            for (int i = 0; i < 1200 && travel.moveDestination(); ++i) {
                const auto previous = travel.player.position;
                travel.step({});
                check(dw::distance(previous, travel.player.position) < 0.101f,
                      "room traversal never teleports");
            }
            check(!travel.moveDestination() && dw::distance(travel.player.position, target) < 0.05f,
                  "corridor movement reaches its destination");
        };
        walk(travel.arena.rooms[1].center);
        check(travel.room == 1, "crossing the doorway starts the next room");
        const float afterEntry = travel.player.hp;
        walk(travel.arena.rooms[0].center);
        check(travel.room == 1 && travel.player.hp == afterEntry && travel.wave == 0,
              "backtracking does not reset encounters, grant rewards or heal again");
        walk(travel.arena.rooms[1].center);
        check(travel.player.hp == afterEntry, "reentering a visited chamber cannot farm healing");
        std::cout << "PASS 64 seeds: deterministic varied geometry, connected floor, doors, objectives and "
                     "boss clearance\n"
                  << "PASS campaign-independent layouts, valid spawns and continuous backtracking\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        return 1;
    }
}
