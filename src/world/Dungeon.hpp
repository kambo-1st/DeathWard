#pragma once
#include "core/Types.hpp"
#include <optional>
#include <set>

namespace dw {
inline constexpr int RoomCount = 7;
inline constexpr float FloorTile = 2;
using FloorCell = std::pair<int, int>;
struct RoomLayout {
    Box bounds;
    Vector3 center{}, entry{}, exit{}, objective{}, bossSpawn{};
    int shape = 0;
    std::vector<Box> floors, obstacles;
};
struct Passage {
    Vector3 from{}, to{};
    Box floor, gate;
    bool open = false;
};
struct Arena {
    // Default construction provides an empty test arena; expeditions always supply a seed.
    Box bounds{{-15, -1, -15}, {15, 4, 15}};
    std::array<RoomLayout, RoomCount> rooms{};
    std::array<Passage, RoomCount - 1> passages{};
    std::vector<Box> floors, boundaryWalls, obstacles, walls;
    std::set<FloorCell> floorCells;
    Vector3 entrance{0, 0.85f, 10}, exit{0, 0.85f, -13}, miners{-10, 0.85f, -8}, altar{10, 0.85f, -8};
    Arena() = default;
    explicit Arena(uint64_t seed);
    void openPassage(int index);
    void rebuildWalls();
    int roomAt(Vector3 p) const;
    bool contains(Vector3 p) const;
    bool blocked(Vector3 p, float radius) const;
    bool sight(Vector3 from, Vector3 to) const;
    bool clear(Vector3 from, Vector3 to, float radius) const;
    Vector3 move(Vector3 from, Vector3 delta, float radius) const;
    std::vector<Vector3> path(Vector3 from, Vector3 target, float radius) const;
};
} // namespace dw
