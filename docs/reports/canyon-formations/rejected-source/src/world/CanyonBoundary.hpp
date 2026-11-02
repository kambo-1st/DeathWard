#pragma once
namespace dw {
struct Arena;
enum class CanyonBoundaryStyle { Classic, Organic };
// Classic remains available for deterministic regression comparisons.
void buildCanyonBoundary(Arena &arena, bool river, CanyonBoundaryStyle style);
} // namespace dw
