#pragma once
#include "core/Types.hpp"
namespace dw::shopCartGeometry {
// Grounded, XZ-centered baked Fort Mercy merchant wagon; see asset manifest.
inline constexpr float HalfWidth=2.2f, HalfDepth=1.189709f, Height=2.641257f;
inline Box bounds(Vector3 center) {
    return {{center.x-HalfWidth,0,center.z-HalfDepth},{center.x+HalfWidth,Height,center.z+HalfDepth}};
}
inline Vector3 reviewStart(Vector3 center) { return {center.x,.85f,center.z+3.9f}; }
inline Vector3 stockPosition(Vector3 sourceCell,Vector3 center) {
    // Small dynamic rooms still need a full character footprint at the counter.
    sourceCell.z=std::max(sourceCell.z,center.z+HalfDepth+.9f);return sourceCell;
}
} // namespace dw::shopCartGeometry
