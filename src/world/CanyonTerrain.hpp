#pragma once
#include "core/Types.hpp"

namespace dw {
struct Arena;
enum class CanyonRiverKind { None, Boundary, Interior };
struct RiverPoint {
    Vector3 position{};
    float width = 0, along = 0;
};
struct RiverSample {
    float distance = 10000, width = 0, along = 0, side = 0;
};
struct RoadPoint {
    Vector3 position{};
    float width = 0, along = 0; // Half-width of the worn track, excluding the soft shoulder.
};
struct RoadSample {
    float distance = 10000, width = 0, along = 0, side = 0;
};
// One triangulated height field supplies both the visible rock and its collision.
// Heights are world-space meters; cells split along their NW-to-SE diagonal.
struct CanyonTerrain {
    static constexpr float WalkableHeight = .12f;
    static constexpr float WaterLevel = -.045f;
    static constexpr float WadeDepth = .075f;
    float x = 0, z = 0, step = 1.25f;
    int width = 0, depth = 0;
    std::vector<float> heights;
    std::vector<std::vector<Vector3>> trails;
    CanyonRiverKind riverKind = CanyonRiverKind::None;
    std::vector<RiverPoint> river;
    std::vector<int> riverRooms;
    Vector3 riverOutward{}; // From playable basins toward the low, distant bank.
    std::vector<RoadPoint> road;
    std::vector<int> roadRooms, roadPassages;
    RoadSample roadSample(Vector3 p) const;
    RiverSample riverSample(Vector3 p) const;
    float height(float px, float pz) const;
    Vector3 vertex(int ix, int iz) const;
    bool blocked(Vector3 p, float radius) const;
    bool waterBlocked(Vector3 p) const;
    bool waterClear(Vector3 from, Vector3 to, float radius) const;
    SegmentHit trace(Vector3 from, Vector3 to, float radius = 0) const;
};
void planCanyonRiver(const Arena &arena, CanyonTerrain &field);
void connectInteriorRiver(Arena &arena, const std::vector<float> &dryHeights);
void planCanyonRoad(Arena &arena);
void buildCanyon(Arena &arena, bool river = true);
} // namespace dw
