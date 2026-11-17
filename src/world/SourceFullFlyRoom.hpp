#pragma once
#include "world/Dungeon.hpp"
namespace dw {
inline constexpr int FullFlyRoomTemplate=704;
// Recorded source1.704.0 is a13x14 interior, cells(6,5)/(6,8).
// Fit those relative centres into the retained canyon without changing its
// outline or imposing source doors/connection geometry.
inline Vector3 fullFlyRoomPosition(const RoomLayout &room,int index) {
    const auto size=sub(room.bounds.max,room.bounds.min);
    const float cell=std::min(size.x*.86f/13,size.z*.86f/14);
    return add(room.center,{0,0,(index==0?-1.5f:1.5f)*cell});
}
}
