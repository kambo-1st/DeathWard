#pragma once
#include "core/Types.hpp"

namespace dw::chestGeometry {
// Art-size correction requested after the first chest review: half the
// original 1.8 model scale. Keep its visible body and contact footprint together.
inline constexpr float ModelScale=.9f;
inline constexpr float HalfWidth=.588310852f*ModelScale;
inline constexpr float HalfDepth=.305809326f*ModelScale;
inline constexpr float PlayerRadius=.48f;
inline constexpr float StopX=HalfWidth+PlayerRadius;
inline constexpr float StopZ=HalfDepth+PlayerRadius;
inline constexpr float ContactMargin=.08f;
inline constexpr float PlacementRadius=.70f;
inline constexpr float ShadowRadius=.65f;
inline Box body(Vector3 at) {
    return {{at.x-HalfWidth,.04f,at.z-HalfDepth},
            {at.x+HalfWidth,.04f+.6943710446f*ModelScale,at.z+HalfDepth}};
}
} // namespace dw::chestGeometry
