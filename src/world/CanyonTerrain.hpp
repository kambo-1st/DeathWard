#pragma once
#include "core/Types.hpp"

namespace dw {
struct Arena;
// One triangulated height field supplies both the visible rock and its collision.
// Heights are world-space meters; cells split along their NW-to-SE diagonal.
struct CanyonTerrain {
    static constexpr float WalkableHeight = .12f;
    float x = 0, z = 0, step = 1.25f;
    int width = 0, depth = 0;
    std::vector<float> heights;
    std::vector<std::vector<Vector3>> trails;
    float height(float px, float pz) const;
    Vector3 vertex(int ix, int iz) const;
    bool blocked(Vector3 p, float radius) const;
    SegmentHit trace(Vector3 from, Vector3 to, float radius = 0) const;
};
void buildCanyon(Arena &arena);
} // namespace dw
