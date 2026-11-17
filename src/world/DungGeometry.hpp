#pragma once
#include "core/Types.hpp"

namespace dw {
// Requested canyon presentation: size the pile and its collider together,
// retaining the source cell/placement centre and the floor contact height.
inline Box dungBounds(Box bounds) {
    constexpr float footprintScale = .70f;
    constexpr float heightScale = footprintScale * 1.50f;
    const float x = (bounds.min.x + bounds.max.x) * .5f;
    const float z = (bounds.min.z + bounds.max.z) * .5f;
    const float halfX = (bounds.max.x - bounds.min.x) * .5f * footprintScale;
    const float halfZ = (bounds.max.z - bounds.min.z) * .5f * footprintScale;
    return {{x - halfX, bounds.min.y, z - halfZ},
            {x + halfX, bounds.min.y + (bounds.max.y - bounds.min.y) * heightScale, z + halfZ}};
}
} // namespace dw
