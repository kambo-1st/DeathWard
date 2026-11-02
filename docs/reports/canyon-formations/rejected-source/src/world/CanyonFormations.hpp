#pragma once
#include "world/CanyonFacets.hpp"
#include <functional>
namespace dw {
struct CanyonAppearance;
struct CanyonTerrain;
// Unified polygon caps and walls. The canonical walkable floor is retained.
void rebuildCanyonFormations(CanyonAppearance &, const CanyonTerrain &, const std::vector<CanyonWallSpan> &,
                             const std::function<float(Vector3, int)> &height,
                             const std::function<float(Vector3, int)> &formation);
} // namespace dw
