#pragma once
#include "core/Types.hpp"
#include <vector>
namespace dw::cliffDetail {
struct Quad {
    Vector3 ab, bb, bt, at;
};
struct Point {
    double x, y;
};
struct Tri {
    int a, b, c;
};
struct Study {
    std::vector<Point> points;
    std::vector<Vector3> vertices;
    std::vector<Tri> triangles;
    std::vector<std::vector<int>> polygons;
    size_t boundary = 0, broad = 0, quads = 0, ngons = 0, chips = 0;
    float maxTilt = 0;
    float width = 0, height = 0;
};
Study buildSelectedA(const std::vector<Quad> &, uint64_t seed = 1866, float reliefScale = 1);
void refineFacets(Study &, uint64_t seed);
Vector3 normal(Quad q);
bool near(Vector3 a, Vector3 b);
// Boundary-constrained irregular network. Rejects invalid/degenerate patches.
Study build(const std::vector<Quad> &patch, uint64_t seed = 1866, float reliefScale = 1);
} // namespace dw::cliffDetail
