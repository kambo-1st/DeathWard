#pragma once
#include "world/CliffWallTopology.hpp"
#include <string>
#include <vector>
namespace dw::cliffOptions {
using Triangle = std::array<Vector3, 3>;
struct Mesh {
    std::vector<Triangle> faces;
    std::vector<std::array<Vector3, 2>> polygonEdges;
    size_t masses = 0, quads = 0, ngons = 0, chips = 0;
    double area = 0;
    float maxDepth = 0;
};
Mesh build(const std::vector<cliffDetail::Quad> &, const std::string &, uint64_t);
} // namespace dw::cliffOptions
