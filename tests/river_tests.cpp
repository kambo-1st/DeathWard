#include "combat/Simulation.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
void verify(uint64_t seed) {
    Arena arena(seed, MissionTheme::Canyon), dry(seed, MissionTheme::Canyon, false);
    const auto &field = *arena.canyon;
    check(field.riverRooms.size() == 3 && field.river.size() > 30,
          "a continuous three-room river region is generated");
    check(dry.canyon->river.empty() &&
              *std::min_element(dry.canyon->heights.begin(), dry.canyon->heights.end()) >= 0,
          "comparison mode restores the dry terrain");
    Arena repeat(seed, MissionTheme::Canyon);
    check(field.heights == repeat.canyon->heights && arena.floorCells == repeat.floorCells &&
              field.riverRooms == repeat.canyon->riverRooms,
          "river terrain and navigation reproduce for a seed");
    int deep = 0, fords = 0, crossings = 0;
    for (int z = 0; z < field.depth; ++z)
        for (int x = 0; x < field.width; ++x) {
            const auto p = field.vertex(x, z);
            if (p.y < -.5f) {
                ++deep;
                check(!arena.contains(p) && arena.blocked(p, .48f), "deep water is never walkable");
            }
            if (p.y < CanyonTerrain::WaterLevel && !field.blocked(p, .48f))
                ++fords;
        }
    check(deep > 30 && fords > 10, "river contains both deep channels and shallow fords");
    for (size_t i = 1; i + 1 < field.river.size(); ++i) {
        const auto &at = field.river[i];
        if (field.height(at.position.x, at.position.z) > -.4f)
            continue;
        const auto direction = unit(sub(field.river[i + 1].position, field.river[i - 1].position));
        const Vector3 side{-direction.z, 0, direction.x};
        auto a = add(at.position, mul(side, at.width + 2.5f)),
             b = sub(at.position, mul(side, at.width + 2.5f));
        a.y = b.y = .85f;
        if (arena.blocked(a, .6f) || arena.blocked(b, .6f) || !arena.sight(a, b))
            continue;
        ++crossings;
        check(!arena.clear(a, b, .48f) && !arena.trace(a, b, .08f).hit,
              "water blocks movement while bullets and sight pass across it");
        check(distance(arena.move(a, sub(b, a), .48f), b) > .5f,
              "a large movement step cannot tunnel across a river");
        const auto path = arena.path(a, b, .48f);
        check(!path.empty(), "opposite riverbanks connect through a ford");
        for (auto next : path) {
            const int count = std::max(1, int(distance(a, next) / .05f));
            for (int n = 0; n <= count; ++n)
                check(!arena.blocked(add(a, mul(sub(next, a), float(n) / count)), .48f),
                      "smoothed ford routes never cut through deep water");
            a = next;
        }
        if (crossings >= 3)
            break;
    }
    check(crossings > 0, "river offers a real movement barrier between two visible banks");
    // Flood the actual navigation graph with gates open. Every generated cell
    // suitable for an actor must connect to the entrance, including sand bars.
    for (auto &p : arena.passages) {
        p.locked = false;
        p.sealed = {false, false};
    }
    arena.rebuildWalls();
    for (auto &p : dry.passages) {
        p.locked = false;
        p.sealed = {false, false};
    }
    dry.rebuildWalls();
    auto position = [](FloorCell c) {
        return Vector3{(c.first + .5f) * FloorTile, .85f, (c.second + .5f) * FloorTile};
    };
    const auto origin =
        *std::min_element(arena.floorCells.begin(), arena.floorCells.end(), [&](auto a, auto b) {
            const float da = arena.blocked(position(a), .6f) ? 1e9f : distance(position(a), arena.entrance);
            const float db = arena.blocked(position(b), .6f) ? 1e9f : distance(position(b), arena.entrance);
            return da < db;
        });
    std::set<FloorCell> reached{origin};
    std::queue<FloorCell> queue;
    queue.push(origin);
    while (!queue.empty()) {
        const auto at = queue.front();
        queue.pop();
        for (auto [dx, dz] : {FloorCell{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
            const FloorCell next{at.first + dx, at.second + dz};
            if (!arena.floorCells.contains(next) || reached.contains(next) ||
                arena.blocked(position(next), .6f) || !arena.clear(position(at), position(next), .6f))
                continue;
            reached.insert(next);
            queue.push(next);
        }
    }
    int stranded = 0;
    for (auto cell : arena.floorCells)
        if (!arena.blocked(position(cell), .6f) && !reached.contains(cell) &&
            !dry.blocked(position(cell), .6f) && !dry.path(dry.entrance, position(cell), .6f).empty()) {
            if (stranded < 8) {
                const auto p = position(cell);
                const auto sample = field.riverSample(p);
                std::cerr << "Pocket " << p.x << "," << p.z << " room " << arena.roomAt(p) << " river edge "
                          << sample.distance - sample.width << " dry height " << dry.canyon->height(p.x, p.z)
                          << '\n';
            }
            ++stranded;
        }
    if (stranded)
        std::cerr << "Seed " << seed << " stranded cells: " << stranded << '\n';
    check(stranded == 0, "river generation does not isolate previously reachable banks");
    std::cout << "PASS river seed " << seed << ": " << deep << " deep samples, " << fords
              << " ford samples\n";
}
} // namespace
int main() {
    try {
        for (uint64_t seed : {0ULL, 1ULL, 2ULL, 3ULL, 4ULL, 5ULL, 6ULL, 7ULL, 42ULL, 1866ULL, 69175541ULL})
            verify(seed);
    } catch (const std::exception &error) {
        std::cerr << "FAIL " << error.what() << '\n';
        return 1;
    }
}
