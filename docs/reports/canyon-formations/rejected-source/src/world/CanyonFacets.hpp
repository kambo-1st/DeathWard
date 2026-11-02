#pragma once
#include "core/Types.hpp"
namespace dw {
struct CanyonAppearance;
struct CanyonWallSpan {
    Vector3 bottomA, bottomB, topA, topB;
    int tier = 0;
};
// Retain exact contact/cap edges; triangulate scattered interior points into broad facets.
void appendCanyonFacets(CanyonAppearance &look, const std::vector<CanyonWallSpan> &spans);
} // namespace dw
