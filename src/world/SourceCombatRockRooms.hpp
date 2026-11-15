#pragma once
#include "world/SourceCombatRockRoomData.hpp"
#include <span>

namespace dw {
// Complete, selected records with only ordinary Gapers and plain rocks.
// This registry does not enable other templates or native factory behavior.
struct SourceCombatRockRoom {
    int variant;
    std::span<const std::array<int,2>> rocks, gapers;
};
inline constexpr std::array<SourceCombatRockRoom,2> SourceCombatRockRooms{{
    {4,Basement4Rocks,Basement4Gapers},
    {108,Basement108Rocks,Basement108Gapers},
}};
inline const SourceCombatRockRoom *sourceCombatRockRoom(int variant) {
    for(const auto &source:SourceCombatRockRooms)if(source.variant==variant)return &source;
    return nullptr;
}
} // namespace dw
