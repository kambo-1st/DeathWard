#pragma once
#include "world/Dungeon.hpp"
namespace dw {
inline float sourceHeartCellSize(const RoomLayout &layout) {
    const auto size=sub(layout.bounds.max,layout.bounds.min);
    return std::min(size.x*.86f/13,size.z*.86f/7);
}
inline Vector3 sourceHeartCell(const RoomLayout &layout,int x,int y) {
    return add(layout.center,{(x-6)*sourceHeartCellSize(layout),0,(y-3)*sourceHeartCellSize(layout)});
}
} // namespace dw
