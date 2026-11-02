#pragma once
#include "core/Types.hpp"
namespace dw {
struct CanyonAppearance;
struct CanyonBoundaryFace {
    Vector3 bottomA, bottomB, topA, topB;
};
void rebuildCanyonWallFacets(CanyonAppearance &look, const std::vector<CanyonBoundaryFace> &faces);
} // namespace dw
