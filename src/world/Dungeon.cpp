#include "world/Dungeon.hpp"
#include <map>
#include <queue>

namespace dw {
namespace {
bool inside(Vector3 p, Box box, float inset = 0) {
    return p.x >= box.min.x + inset && p.x <= box.max.x - inset && p.z >= box.min.z + inset &&
           p.z <= box.max.z - inset;
}
Vector3 cellCenter(FloorCell c) {
    return {(float(c.first) + 0.5f) * FloorTile, 0.85f, (float(c.second) + 0.5f) * FloorTile};
}
// Compress adjacent tiles into strips for rendering; all collision walls come from the same tiles.
std::vector<Box> strips(const std::set<FloorCell> &cells) {
    std::map<int, std::vector<int>> rows;
    for (auto [x, z] : cells)
        rows[z].push_back(x);
    std::vector<Box> result;
    for (const auto &[z, xs] : rows) {
        int first = xs.front(), last = first;
        auto emit = [&] {
            result.push_back({{float(first) * FloorTile, -0.4f, float(z) * FloorTile},
                              {float(last + 1) * FloorTile, 0, float(z + 1) * FloorTile}});
        };
        for (size_t i = 1; i < xs.size(); ++i) {
            if (xs[i] != last + 1) {
                emit();
                first = xs[i];
            }
            last = xs[i];
        }
        emit();
    }
    return result;
}
bool connectedFloor(const Arena &arena, Box bounds, float radius) {
    std::set<FloorCell> walkable;
    std::vector<Box> localWalls;
    for (auto wall : arena.walls)
        if (wall.max.x >= bounds.min.x - 2 && wall.min.x <= bounds.max.x + 2 &&
            wall.max.z >= bounds.min.z - 2 && wall.min.z <= bounds.max.z + 2)
            localWalls.push_back(wall);
    auto clear = [&](Vector3 a, Vector3 b) {
        for (auto wall : localWalls)
            if (segmentBox(a, b, wall, radius).hit)
                return false;
        return true;
    };
    for (int x = int(bounds.min.x / FloorTile); x < int(bounds.max.x / FloorTile); ++x)
        for (int z = int(bounds.min.z / FloorTile); z < int(bounds.max.z / FloorTile); ++z) {
            FloorCell cell{x, z};
            if (!arena.floorCells.contains(cell))
                continue;
            auto p = cellCenter(cell);
            bool blocked = false;
            for (auto wall : localWalls)
                blocked = blocked || sphereBox(p, radius, wall);
            if (!blocked)
                walkable.insert(cell);
        }
    if (walkable.empty())
        return false;
    std::set<FloorCell> reached{*walkable.begin()};
    std::queue<FloorCell> frontier;
    frontier.push(*walkable.begin());
    while (!frontier.empty()) {
        auto cell = frontier.front();
        frontier.pop();
        for (auto [dx, dz] : {FloorCell{0, -1}, FloorCell{1, 0}, FloorCell{0, 1}, FloorCell{-1, 0}}) {
            FloorCell next{cell.first + dx, cell.second + dz};
            if (walkable.contains(next) && !reached.contains(next) &&
                clear(cellCenter(cell), cellCenter(next))) {
                reached.insert(next);
                frontier.push(next);
            }
        }
    }
    return reached.size() == walkable.size();
}
} // namespace

Arena::Arena(uint64_t seed) : visualSeed(seed) {
    Random layout(seed ^ 0x4c41594f55544d31ULL);
    std::set<std::pair<int, int>> usedSizes;
    const auto graph = generateRoomGraph(seed);
    const int powerRooms = graph.powerRooms;
    rooms.back().kind = RoomKind::Boss;
    for (int i = 0; i < powerRooms; ++i)
        rooms[size_t(RoomCount - 2 - i)].kind = RoomKind::Power;
    auto shuffle = [&](auto &values) {
        for (size_t i = values.size(); i > 1; --i)
            std::swap(values[i - 1], values[layout.bounded(uint32_t(i))]);
    };
    for (auto edge : graph.links) {
        Passage passage;
        passage.rooms = edge;
        passage.locked = rooms[size_t(edge[0])].kind != RoomKind::Combat ||
                         rooms[size_t(edge[1])].kind != RoomKind::Combat;
        const int index = int(passages.size());
        passages.push_back(passage);
        rooms[size_t(edge[0])].passages.push_back(index);
        rooms[size_t(edge[1])].passages.push_back(index);
    }
    // Unequal row/column spacing changes corridor lengths while keeping crossings
    // impossible: a corridor only joins neighboring occupied cells of the graph.
    auto axis = [&](bool xAxis) {
        int low = 0, high = 0;
        for (auto cell : graph.cells) {
            const int value = xAxis ? cell.first : cell.second;
            low = std::min(low, value);
            high = std::max(high, value);
        }
        std::map<int, int> positions{{0, 0}};
        for (int i = 1; i <= high; ++i)
            positions[i] = positions[i - 1] + 24 + 2 * int(layout.bounded(5));
        for (int i = -1; i >= low; --i)
            positions[i] = positions[i + 1] - 24 - 2 * int(layout.bounded(5));
        return positions;
    };
    const auto xs = axis(true), zs = axis(false);
    for (int i = 0; i < RoomCount; ++i) {
        auto &room = rooms[size_t(i)];
        const auto cell = graph.cells[size_t(i)];
        const int cx = xs.at(cell.first), cz = zs.at(cell.second);
        room.center = {float(cx) * FloorTile, 0.85f, float(cz) * FloorTile};
        int halfX, halfZ;
        do {
            halfX = 6 + int(layout.bounded(5));
            halfZ = 6 + int(layout.bounded(5));
        } while (!usedSizes.insert({halfX, halfZ}).second);
        room.bounds = {
            {room.center.x - float(halfX) * FloorTile, 0, room.center.z - float(halfZ) * FloorTile},
            {room.center.x + float(halfX) * FloorTile, 3, room.center.z + float(halfZ) * FloorTile}};
        // Cycle a seeded sequence of footprints so every expedition has visible shape variety.
        room.shape = (int(seed % 4) + i) % 4;
        const bool mirrorX = layout.bounded(2), mirrorZ = layout.bounded(2);
        std::set<FloorCell> local;
        for (int x = -halfX; x < halfX; ++x)
            for (int z = -halfZ; z < halfZ; ++z) {
                const int ax = std::min(x + halfX, halfX - 1 - x);
                const int az = std::min(z + halfZ, halfZ - 1 - z);
                const float px = (float(x) + 0.5f) * (mirrorX ? -1 : 1);
                const float pz = (float(z) + 0.5f) * (mirrorZ ? -1 : 1);
                bool cut = room.shape == 1   ? ax < 2 && az < 2
                           : room.shape == 2 ? px > 1.5f && pz > 1.5f
                           : room.shape == 3 ? std::abs(px) > 3.5f && std::abs(pz) > 3.5f
                                             : false;
                if (!cut)
                    local.insert({cx + x, cz + z});
            }
        room.floors = strips(local);
        floorCells.insert(local.begin(), local.end());
        room.objective = room.center;
        // Objectives sit off the main axis in a seeded, walkable part of the room.
        std::vector<Vector3> sites;
        for (const auto &cell : local) {
            Vector3 p = cellCenter(cell);
            if (!inside(p, room.bounds, 3) || distance(p, room.center) < 5)
                continue;
            bool safe = true;
            for (int dx = -1; dx <= 1; ++dx)
                for (int dz = -1; dz <= 1; ++dz)
                    safe = safe && local.contains({cell.first + dx, cell.second + dz});
            if (safe)
                sites.push_back(p);
        }
        if (!sites.empty())
            room.objective = sites[layout.bounded(uint32_t(sites.size()))];
        room.bossSpawn = room.center;
    }
    std::array<bool, RoomCount> hasEntry{};
    for (auto &passage : passages) {
        auto &a = rooms[size_t(passage.rooms[0])];
        auto &b = rooms[size_t(passage.rooms[1])];
        Vector3 direction = unit(sub(b.center, a.center));
        const bool eastWest = std::abs(direction.x) > 0.5f;
        const float extentA =
            eastWest ? (a.bounds.max.x - a.bounds.min.x) / 2 : (a.bounds.max.z - a.bounds.min.z) / 2;
        const float extentB =
            eastWest ? (b.bounds.max.x - b.bounds.min.x) / 2 : (b.bounds.max.z - b.bounds.min.z) / 2;
        passage.from = add(a.center, mul(direction, extentA));
        passage.to = sub(b.center, mul(direction, extentB));
        if (!hasEntry[size_t(passage.rooms[0])]) {
            a.entry = a.exit = sub(passage.from, mul(direction, 2));
            hasEntry[size_t(passage.rooms[0])] = true;
        }
        if (!hasEntry[size_t(passage.rooms[1])]) {
            b.entry = b.exit = add(passage.to, mul(direction, 2));
            hasEntry[size_t(passage.rooms[1])] = true;
        }
        // Four floor cells across (8 units), with no discontinuity at either doorway.
        passage.floor = {{std::min(passage.from.x, passage.to.x) - (eastWest ? 0 : 4), -0.4f,
                          std::min(passage.from.z, passage.to.z) - (eastWest ? 4 : 0)},
                         {std::max(passage.from.x, passage.to.x) + (eastWest ? 0 : 4), 0,
                          std::max(passage.from.z, passage.to.z) + (eastWest ? 4 : 0)}};
        for (int side = 0; side < 2; ++side) {
            const auto at = side == 0 ? passage.from : passage.to;
            passage.gates[size_t(side)] = {
                sub(at, eastWest ? Vector3{0.25f, 0.85f, 4} : Vector3{4, 0.85f, 0.25f}),
                add(at, eastWest ? Vector3{0.25f, 2.15f, 4} : Vector3{4, 2.15f, 0.25f})};
        }
        for (int x = int(passage.floor.min.x / FloorTile); x < int(passage.floor.max.x / FloorTile); ++x)
            for (int z = int(passage.floor.min.z / FloorTile); z < int(passage.floor.max.z / FloorTile); ++z)
                floorCells.insert({x, z});
    }
    entrance = rooms[0].entry = {0, 0.85f, rooms[0].bounds.max.z - 3};
    exit = rooms.back().exit = add(rooms.back().center, {0, 0, -4});
    miners = rooms[2].objective;
    altar = rooms[3].objective;
    floors = strips(floorCells);
    bounds = {{std::numeric_limits<float>::infinity(), -1, std::numeric_limits<float>::infinity()},
              {-std::numeric_limits<float>::infinity(), 4, -std::numeric_limits<float>::infinity()}};
    // Merge exposed tile edges into continuous walls, including all concave corners.
    std::map<std::pair<int, int>, std::set<int>> edges;
    for (auto [x, z] : floorCells) {
        bounds.min.x = std::min(bounds.min.x, float(x) * FloorTile);
        bounds.min.z = std::min(bounds.min.z, float(z) * FloorTile);
        bounds.max.x = std::max(bounds.max.x, float(x + 1) * FloorTile);
        bounds.max.z = std::max(bounds.max.z, float(z + 1) * FloorTile);
        if (!floorCells.contains({x - 1, z}))
            edges[{0, x}].insert(z);
        if (!floorCells.contains({x + 1, z}))
            edges[{0, x + 1}].insert(z);
        if (!floorCells.contains({x, z - 1}))
            edges[{1, z}].insert(x);
        if (!floorCells.contains({x, z + 1}))
            edges[{1, z + 1}].insert(x);
    }
    for (const auto &[key, offsets] : edges) {
        const auto [axis, line] = key;
        int first = *offsets.begin(), last = first;
        auto emit = [&] {
            float lo = float(first) * FloorTile, hi = float(last + 1) * FloorTile;
            float at = float(line) * FloorTile;
            boundaryWalls.push_back(
                axis == 0 ? Box{{at - 0.18f, -0.2f, lo - 0.18f}, {at + 0.18f, 2.2f, hi + 0.18f}}
                          : Box{{lo - 0.18f, -0.2f, at - 0.18f}, {hi + 0.18f, 2.2f, at + 0.18f}});
        };
        for (auto it = std::next(offsets.begin()); it != offsets.end(); ++it) {
            if (*it != last + 1) {
                emit();
                first = *it;
            }
            last = *it;
        }
        emit();
    }
    walls = boundaryWalls;
    for (auto &room : rooms) {
        const int desired = 4 + int(layout.bounded(6));
        for (int attempt = 0; attempt < 404 && int(room.obstacles.size()) < desired; ++attempt) {
            Vector3 p{layout.real(room.bounds.min.x + 2, room.bounds.max.x - 2), 0,
                      layout.real(room.bounds.min.z + 2, room.bounds.max.z - 2)};
            const float maxSize = attempt < 160 ? 4.5f : 2.2f;
            const bool fallback = attempt >= 400;
            if (fallback)
                p = add(room.center, {(attempt % 2 ? -4.0f : 4.0f), 0, (attempt % 4 < 2 ? -4.0f : 4.0f)});
            const float w = fallback ? 1.4f : layout.real(1.4f, maxSize);
            const float d = fallback ? 1.4f : layout.real(1.4f, maxSize);
            Box box{{p.x - w / 2, 0, p.z - d / 2}, {p.x + w / 2, layout.real(1.2f, 2.8f), p.z + d / 2}};
            // Keep a broad cross through the room and a direct route to its objective clear.
            if ((box.min.x < room.center.x + 2.7f && box.max.x > room.center.x - 2.7f) ||
                (box.min.z < room.center.z + 2.7f && box.max.z > room.center.z - 2.7f) ||
                segmentBox(room.center, room.objective, box, 2.5f).hit)
                continue;
            bool safe = true;
            for (float x : {box.min.x - 1.4f, box.max.x + 1.4f})
                for (float z : {box.min.z - 1.4f, box.max.z + 1.4f})
                    safe = safe && inside({x, 0.85f, z}, room.bounds, 0.8f) && !blocked({x, 0.85f, z}, 0.6f);
            for (const auto &other : room.obstacles)
                if (box.min.x < other.max.x + 2.8f && box.max.x > other.min.x - 2.8f &&
                    box.min.z < other.max.z + 2.8f && box.max.z > other.min.z - 2.8f)
                    safe = false;
            if (safe) {
                walls.push_back(box);
                // Reject cover that creates pockets too narrow for navigation or enemy spawns.
                for (float radius : {0.48f, 0.6f, 0.8f})
                    safe = safe && connectedFloor(*this, room.bounds, radius);
                if (!safe) {
                    walls.pop_back();
                    continue;
                }
                room.obstacles.push_back(box);
                obstacles.push_back(box);
            }
        }
    }
    // Every key starts in the unlocked combat network, never behind the lock it opens.
    std::vector<int> keyRooms;
    for (int i = 0; i < RoomCount; ++i)
        if (rooms[size_t(i)].kind == RoomKind::Combat && i != 2 && i != 3)
            keyRooms.push_back(i);
    shuffle(keyRooms);
    for (int i = 0; i < powerRooms + 1; ++i)
        keys.push_back({keyRooms[size_t(i)], rooms[size_t(keyRooms[size_t(i)])].objective, false});
    std::queue<int> breadth;
    std::array<bool, RoomCount> seen{};
    seen[0] = true;
    breadth.push(0);
    while (!breadth.empty()) {
        const int at = breadth.front();
        breadth.pop();
        for (int index : rooms[size_t(at)].passages) {
            const auto &p = passages[size_t(index)];
            const int next = p.rooms[0] == at ? p.rooms[1] : p.rooms[0];
            if (!seen[size_t(next)]) {
                seen[size_t(next)] = true;
                rooms[size_t(next)].depth = rooms[size_t(at)].depth + 1;
                breadth.push(next);
            }
        }
    }
    // Keep objective rooms combat-ready. Quiet rooms belong to
    // the unlocked network and can still contain a key, but never a power pedestal.
    std::vector<int> quietRooms;
    for (int i = 1; i < RoomCount; ++i)
        if (rooms[size_t(i)].kind == RoomKind::Combat && rooms[size_t(i)].depth > 1 && i != 2 && i != 3)
            quietRooms.push_back(i);
    shuffle(quietRooms);
    const int quietCount = 1 + int(layout.bounded(2));
    // The entrance is always quiet and counts toward the one-to-two-room limit.
    rooms.front().kind = RoomKind::Empty;
    for (int i = 1; i < quietCount; ++i)
        rooms[size_t(quietRooms[size_t(i - 1)])].kind = RoomKind::Empty;
    rebuildWalls();
}
void Arena::rebuildWalls() {
    walls = boundaryWalls;
    walls.insert(walls.end(), obstacles.begin(), obstacles.end());
    for (const auto &passage : passages)
        for (int side = 0; side < 2; ++side)
            if (passage.closed(side))
                walls.push_back(passage.gates[size_t(side)]);
}
void Arena::sealRoom(int index) {
    for (auto &passage : passages)
        for (int side = 0; side < 2; ++side)
            passage.sealed[size_t(side)] = passage.rooms[size_t(side)] == index;
    rebuildWalls();
}
Vector3 Arena::doorPosition(int passage, int side) const {
    const auto &p = passages[size_t(passage)];
    return side == 0 ? p.from : p.to;
}
Vector3 Arena::doorApproach(int passage, int side) const {
    const auto &p = passages[size_t(passage)];
    const auto at = doorPosition(passage, side);
    return add(at, mul(unit(sub(rooms[size_t(p.rooms[size_t(side)])].center, at)), 2));
}
float RoomLayout::usableArea() const {
    // Generated floor strips and cover boxes do not overlap each other. Intersect
    // cover with each strip so clipped corners and missing floor never count.
    float area = 0;
    for (const auto &floor : floors) {
        area += (floor.max.x - floor.min.x) * (floor.max.z - floor.min.z);
        for (const auto &cover : obstacles)
            area -= std::max(0.0f, std::min(floor.max.x, cover.max.x) - std::max(floor.min.x, cover.min.x)) *
                    std::max(0.0f, std::min(floor.max.z, cover.max.z) - std::max(floor.min.z, cover.min.z));
    }
    return std::max(0.0f, area);
}
int Arena::roomAt(Vector3 p) const {
    for (int i = 0; i < RoomCount; ++i)
        if (inside(p, rooms[size_t(i)].bounds) && contains(p))
            return i;
    return -1;
}
bool Arena::contains(Vector3 p) const {
    if (floorCells.empty())
        return inside(p, bounds);
    return floorCells.contains({int(std::floor(p.x / FloorTile)), int(std::floor(p.z / FloorTile))});
}
bool Arena::blocked(Vector3 p, float radius) const {
    if (!contains(p))
        return true;
    for (const auto &wall : walls)
        if (sphereBox(p, radius, wall))
            return true;
    return false;
}
bool Arena::clear(Vector3 from, Vector3 to, float radius) const {
    for (const auto &wall : walls)
        if (segmentBox(from, to, wall, radius).hit)
            return false;
    return true;
}
bool Arena::sight(Vector3 from, Vector3 to) const {
    return clear(from, to, 0);
}
Vector3 Arena::move(Vector3 from, Vector3 delta, float radius) const {
    Vector3 x = add(from, {delta.x, 0, 0});
    if (!blocked(x, radius) && clear(from, x, radius))
        from = x;
    Vector3 z = add(from, {0, 0, delta.z});
    if (!blocked(z, radius) && clear(from, z, radius))
        from = z;
    return from;
}
} // namespace dw
