#pragma once
#include "core/Types.hpp"
#include "world/CanyonTerrain.hpp"
#include "world/MissionTheme.hpp"
#include <memory>
#include <optional>
#include <set>

namespace dw {
inline constexpr int RoomCount = 15;
inline constexpr float FloorTile = 2;
using FloorCell = std::pair<int, int>;
enum class RoomKind { Combat, Power, Boss, Empty, Shop };
struct RoomGraph {
    std::array<FloorCell, RoomCount> cells{};
    std::vector<std::array<int, 2>> links;
    int powerRooms = 1;
};
RoomGraph generateRoomGraph(uint64_t seed);
struct RoomLayout {
    Box bounds;
    Vector3 center{}, entry{}, exit{}, objective{}, bossSpawn{};
    int shape = 0, depth = 0;
    float floorArea = -1;
    RoomKind kind = RoomKind::Combat;
    std::vector<int> passages;
    std::vector<Box> floors, obstacles;
    float usableArea() const;
};
struct Passage {
    std::array<int, 2> rooms{};
    Vector3 from{}, to{};
    Box floor;
    std::array<Box, 2> gates;
    std::array<bool, 2> sealed{};
    bool locked = false;
    bool closed(int side) const {
        return locked || sealed[size_t(side)];
    }
    bool open() const {
        return !closed(0) && !closed(1);
    }
};
struct KeyPickup {
    int room = 0;
    Vector3 position{};
    bool collected = false;
};
struct Arena {
    uint64_t visualSeed = 0;
    MissionTheme theme = MissionTheme::Mine;
    std::shared_ptr<CanyonTerrain> canyon;
    // Default construction provides an empty test arena; expeditions always supply a seed.
    Box bounds{{-15, -1, -15}, {15, 4, 15}};
    std::array<RoomLayout, RoomCount> rooms{};
    std::vector<Passage> passages;
    std::vector<KeyPickup> keys;
    int shopRoom = -1;
    std::vector<Box> floors, boundaryWalls, obstacles, walls;
    std::set<FloorCell> floorCells;
    Vector3 entrance{0, 0.85f, 10}, exit{0, 0.85f, -13}, miners{-10, 0.85f, -8}, altar{10, 0.85f, -8};
    Arena() = default;
    explicit Arena(uint64_t seed, MissionTheme missionTheme = MissionTheme::Mine);
    void sealRoom(int index);
    Vector3 doorPosition(int passage, int side) const;
    Vector3 doorApproach(int passage, int side) const;
    void rebuildWalls();
    int roomAt(Vector3 p) const;
    bool contains(Vector3 p) const;
    bool blocked(Vector3 p, float radius) const;
    bool sight(Vector3 from, Vector3 to) const;
    bool clear(Vector3 from, Vector3 to, float radius) const;
    SegmentHit trace(Vector3 from, Vector3 to, float radius = 0) const;
    Vector3 move(Vector3 from, Vector3 delta, float radius) const;
    std::vector<Vector3> path(Vector3 from, Vector3 target, float radius) const;
};
} // namespace dw
