#pragma once
#include "world/Dungeon.hpp"

namespace dw {
// Repentance 1.7.9b resources-dlc3/rooms/01.basement.stb: normal 1.47.0.
// Recorded 13x7, difficulty 1, positive weight; two 10.1.0 spawns at (5,3)/(7,3).
// See d08-source-room/source-template.json for the pinned binary and extraction.
inline constexpr int BasementGaperTemplate = 47;
inline Vector3 sourceCombatSpawn(const RoomLayout &room, int slot) {
    // Embed the source formation uniformly in the retained canyon basin.
    // This is a dynamic spatial adapter, not native room geometry/pressure parity.
    const auto size=sub(room.bounds.max,room.bounds.min);
    const float cell=std::min(size.x*.86f/13.f,size.z*.86f/7.f);
    return add(room.center,{(slot==0?-1.f:1.f)*cell,0,0});
}
} // namespace dw
