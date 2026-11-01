#pragma once
namespace dw {
struct CanyonAppearance;
struct CanyonTerrain;
// Replace boundary rock only; retain the canonical ground and detached outcrops.
void rebuildCanyonCliffs(CanyonAppearance &appearance, const CanyonTerrain &source);
} // namespace dw
