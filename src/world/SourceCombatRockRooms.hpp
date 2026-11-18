#pragma once
#include "world/SourceCombatRockRoomData.hpp"
#include <span>
#include "world/SourceRoundWormRoom.hpp"

namespace dw {
// Complete selected enemy/plain-rock records; no unrelated pool expansion.
// This registry does not enable other templates or native factory behavior.
struct SourceCombatRockRoom {
    int variant;
    std::span<const std::array<int,2>> rocks, enemies;
    int enemyType=10,enemyVariant=1;
};
inline constexpr std::array<SourceCombatRockRoom,7> SourceCombatRockRooms{{
    {4,Basement4Rocks,Basement4Gapers},
    {108,Basement108Rocks,Basement108Gapers},
    {109,Basement109Rocks,Basement109Gapers},
    {547,Basement547Rocks,Basement547Gapers},
    {548,Basement548Rocks,Basement548Gapers},
    {550,Basement550Rocks,Basement550Gapers},
    {505,Basement505Rocks,Basement505Worms,244,0},
}};
inline const SourceCombatRockRoom *sourceCombatRockRoom(int variant) {
    for(const auto &source:SourceCombatRockRooms)if(source.variant==variant)return &source;
    return nullptr;
}
} // namespace dw
