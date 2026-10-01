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
void verifyBoundary(const Arena &arena, const Arena &dry) {
    const auto &field = *arena.canyon;
    // Exact field-edge vertices have no enclosing triangle for height queries.
    for (size_t i = 1; i + 1 < field.river.size(); ++i)
        check(field.waterBlocked(field.river[i].position),
              "the river boundary has no walkable gaps or fords");
    const auto outward = field.riverOutward;
    const Vector3 tangent{-outward.z, 0, outward.x};
    for (int index : field.riverRooms) {
        const auto &room = arena.rooms[size_t(index)];
        for (const auto &other : arena.rooms)
            check(dot(other.center, outward) <= dot(room.center, outward) + .1f,
                  "only exterior-facing walls are replaced");
        const auto size = sub(room.bounds.max, room.bounds.min);
        const float reach = std::abs(dot(size, outward)) * .5f;
        auto bank = add(room.center, mul(outward, reach - 2.5f));
        check(!arena.blocked(bank, .48f), "the replacement bank is walkable");
        const auto route = arena.path(room.center, bank, .48f);
        check(!route.empty() && distance(route.back(), bank) < .1f,
              "each opened riverbank connects to its room");
        int roomRemoved = 0;
        const float span = std::abs(dot(size, tangent));
        for (float s = -span * .18f; s <= span * .18f; s += .5f)
            for (float q = reach - 4; q <= reach; q += .5f) {
                const auto p = add(add(room.center, mul(outward, q)), mul(tangent, s));
                if (dry.canyon->height(p.x, p.z) > 1 && !field.blocked(p, 0))
                    ++roomRemoved;
            }
        check(roomRemoved > 5, "a meaningful span of enclosing cliff becomes accessible near bank");
        const auto sample = field.riverSample(bank);
        auto water = add(bank, mul(outward, sample.width + 3));
        check(field.waterBlocked(water) && arena.sight(bank, water) && !arena.trace(bank, water, .08f).hit &&
                  !arena.clear(bank, water, .48f),
              "water forms the visible movement boundary while allowing sight and bullets");
        check(distance(arena.move(bank, sub(water, bank), .48f), water) > .5f,
              "a large movement step cannot tunnel across the river boundary");
        const auto far = add(bank, mul(outward, 2 * sample.width + 11));
        check(field.height(far.x, far.z) > .12f && field.height(far.x, far.z) < 1.5f &&
                  dry.canyon->height(far.x, far.z) > 4,
              "low landscape replaces the tall plateau across the river");
    }
}
void verifyInterior(const Arena &arena) {
    const auto &field = *arena.canyon;
    check(field.riverRooms.size() == 3 && length(field.riverOutward) == 0,
          "interior rivers cross three basins without opening an exterior side");
    int fords = 0, crossings = 0;
    for (int z = 0; z < field.depth; ++z)
        for (int x = 0; x < field.width; ++x) {
            const auto p = field.vertex(x, z);
            if (p.y < CanyonTerrain::WaterLevel && !field.blocked(p, .48f))
                ++fords;
        }
    check(fords > 10, "interior rivers provide meaningful shallow crossings");
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
}
CanyonRiverKind verify(uint64_t seed) {
    Arena arena(seed, MissionTheme::Canyon), dry(seed, MissionTheme::Canyon, false);
    const auto &field = *arena.canyon;
    check(!field.riverRooms.empty() && field.riverRooms.size() <= 3 && field.river.size() > 30,
          "one seeded river type is generated across one to three rooms");
    check(dry.canyon->riverKind == CanyonRiverKind::None && dry.canyon->river.empty() &&
              *std::min_element(dry.canyon->heights.begin(), dry.canyon->heights.end()) >= 0,
          "comparison mode restores the dry terrain");
    Arena repeat(seed, MissionTheme::Canyon);
    check(field.heights == repeat.canyon->heights && arena.floorCells == repeat.floorCells &&
              field.riverRooms == repeat.canyon->riverRooms && field.riverKind == repeat.canyon->riverKind,
          "river terrain and navigation reproduce for a seed");
    int deep = 0;
    for (int z = 0; z < field.depth; ++z)
        for (int x = 0; x < field.width; ++x) {
            const auto p = field.vertex(x, z);
            if (p.y < -.5f) {
                ++deep;
                check(!arena.contains(p) && arena.blocked(p, .48f), "deep water is never walkable");
            }
        }
    check(deep > 30, "each river type contains a meaningful deep channel");
    if (field.riverKind == CanyonRiverKind::Boundary)
        verifyBoundary(arena, dry);
    else {
        check(field.riverKind == CanyonRiverKind::Interior, "River On selects a known river type");
        verifyInterior(arena);
    }
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
            (dry.blocked(position(cell), .6f) || !dry.path(dry.entrance, position(cell), .6f).empty())) {
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
    for (int index : field.riverRooms) {
        const auto &room = arena.rooms[size_t(index)];
        for (int link : room.passages) {
            auto &passage = arena.passages[size_t(link)];
            passage.sealed[passage.rooms[0] == index ? 0 : 1] = true;
        }
        arena.rebuildWalls();
        for (int link : room.passages) {
            const auto &passage = arena.passages[size_t(link)];
            const int other = passage.rooms[0] == index ? passage.rooms[1] : passage.rooms[0];
            check(arena.path(room.center, arena.rooms[size_t(other)].center, .48f).empty(),
                  "neither river type can bypass sealed room exits");
        }
        for (int link : room.passages)
            arena.passages[size_t(link)].sealed = {false, false};
        arena.rebuildWalls();
    }
    std::cout << "PASS river seed " << seed << ": "
              << (field.riverKind == CanyonRiverKind::Boundary ? "boundary" : "interior") << ", " << deep
              << " deep samples\n";
    return field.riverKind;
}
} // namespace
int main() {
    try {
        int boundary = 0, interior = 0;
        for (uint64_t seed : {0ULL, 1ULL, 2ULL, 3ULL, 4ULL, 5ULL, 6ULL, 7ULL, 42ULL, 1866ULL, 69175541ULL}) {
            const auto kind = verify(seed);
            boundary += kind == CanyonRiverKind::Boundary;
            interior += kind == CanyonRiverKind::Interior;
            if (seed == 1866)
                check(kind == CanyonRiverKind::Boundary, "documented boundary seed remains reproducible");
            if (seed == 42)
                check(kind == CanyonRiverKind::Interior, "documented interior seed remains reproducible");
        }
        check(boundary >= 3 && interior >= 3, "the seed selection exercises both river types");
    } catch (const std::exception &error) {
        std::cerr << "FAIL " << error.what() << '\n';
        return 1;
    }
}
