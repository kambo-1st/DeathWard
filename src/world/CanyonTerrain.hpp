#pragma once
#include "core/Types.hpp"

namespace dw {
struct Arena;
// One triangulated height field supplies both the visible rock and its collision.
// Heights are world-space meters; cells split along their NW-to-SE diagonal.
struct CanyonTerrain {
    float x = 0, z = 0, step = 1.25f;
    int width = 0, depth = 0;
    std::vector<float> heights;
    std::vector<unsigned char> cliffs;
    std::vector<std::vector<Vector3>> trails;
    float height(float px, float pz) const;
    Vector3 vertex(int ix, int iz) const;
    bool blocked(Vector3 p, float radius) const;
    SegmentHit trace(Vector3 from, Vector3 to, float radius = 0, const Vector3 *focus = nullptr,
                     const Vector3 *camera = nullptr) const;
    static float displayedHeight(Vector3 point, bool cliff, Vector3 focus, Vector3 camera);
};
void buildCanyon(Arena &arena);
} // namespace dw
