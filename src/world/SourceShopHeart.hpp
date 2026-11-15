#pragma once
#include "world/SourceHeartRockRoom.hpp"
namespace dw {
// Installed special-room2.0.0 has generic shop slots at (5,4)/(7,4).
// D12a pins a full red heart in the second slot; full stock selection is open.
inline constexpr int SourceShopHeartPrice=3, SourceShopKeyPrice=5;
inline Vector3 sourceShopKeyPosition(const RoomLayout &layout) {
    return sourceHeartCell(layout,5,4);
}
inline Vector3 sourceShopHeartPosition(const RoomLayout &layout) {
    return sourceHeartCell(layout,7,4);
}
} // namespace dw
