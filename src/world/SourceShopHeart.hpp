#pragma once
#include "world/SourceHeartRockRoom.hpp"
#include "world/ShopCartGeometry.hpp"
namespace dw {
// Installed special-room2.0.0 has generic shop slots at (5,4)/(7,4).
// Retain source slot order and X spacing; leave standing room beside the centered cart.
inline constexpr int SourceShopHeartPrice=3, SourceShopKeyPrice=5;
inline Vector3 sourceShopKeyPosition(const RoomLayout &layout) {
    return shopCartGeometry::stockPosition(sourceHeartCell(layout,5,4),layout.center);
}
inline Vector3 sourceShopHeartPosition(const RoomLayout &layout) {
    return shopCartGeometry::stockPosition(sourceHeartCell(layout,7,4),layout.center);
}
} // namespace dw
