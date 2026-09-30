#pragma once
#include <array>

namespace dw {
enum class HubKind { BlackCreek, Frontier, Redstone };
inline constexpr std::array Hubs{HubKind::BlackCreek, HubKind::Frontier, HubKind::Redstone};
inline constexpr const char *hubName(HubKind hub) {
    return hub == HubKind::Redstone ? "REDSTONE CANYON" :
           hub == HubKind::Frontier ? "WESTERN FRONTIER" : "BLACK CREEK";
}
inline constexpr const char *hubShortName(HubKind hub) {
    return hub == HubKind::Frontier ? "FRONTIER" : hubName(hub);
}
inline constexpr const char *hubFolder(HubKind hub) {
    return hub == HubKind::Redstone ? "redstone" : hub == HubKind::Frontier ? "frontier" : "town";
}
inline constexpr HubKind primaryTravelHub(HubKind hub) {
    return hub == HubKind::BlackCreek ? HubKind::Frontier : HubKind::BlackCreek;
}
inline constexpr HubKind secondaryTravelHub(HubKind hub) {
    return hub == HubKind::Redstone ? HubKind::Frontier : HubKind::Redstone;
}
} // namespace dw
