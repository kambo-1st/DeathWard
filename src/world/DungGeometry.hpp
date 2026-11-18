#pragma once
#include "core/Types.hpp"

namespace dw {
inline constexpr float DungFootprintScale = 1.3125f;
inline constexpr float DungHeightScale = 1.05f;
inline constexpr float DungRemnantFootprintScale = .70f;
// Half-diagonal of the rendered/solid square footprint for placement checks.
inline float dungClearanceRadius(float cellWidth) {
    return cellWidth * DungFootprintScale * .7071067812f;
}
// Requested canyon presentation: size the pile and its collider together,
// retaining the source cell/placement centre and the floor contact height.
inline Box dungBounds(Box bounds) {
    const float x = (bounds.min.x + bounds.max.x) * .5f;
    const float z = (bounds.min.z + bounds.max.z) * .5f;
    const float halfX = (bounds.max.x - bounds.min.x) * .5f * DungFootprintScale;
    const float halfZ = (bounds.max.z - bounds.min.z) * .5f * DungFootprintScale;
    return {{x - halfX, bounds.min.y, z - halfZ},
            {x + halfX, bounds.min.y + (bounds.max.y - bounds.min.y) * DungHeightScale, z + halfZ}};
}
} // namespace dw
