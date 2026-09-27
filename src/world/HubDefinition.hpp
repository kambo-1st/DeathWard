#pragma once

namespace dw {
enum class HubKind { BlackCreek, Frontier };
inline constexpr const char *hubName(HubKind hub) {
    return hub == HubKind::Frontier ? "WESTERN FRONTIER" : "BLACK CREEK";
}
inline constexpr const char *hubFolder(HubKind hub) {
    return hub == HubKind::Frontier ? "frontier" : "town";
}
} // namespace dw
