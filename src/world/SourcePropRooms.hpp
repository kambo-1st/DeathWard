#pragma once
#include <array>
#include <span>
#include "world/SourceRoomSelection.hpp"
namespace dw {
struct SourcePropEntry {int x,y,type,variant,ordinal;};
struct SourcePropRoom {int variant;std::span<const SourcePropEntry> entries;};
inline constexpr int PropReviewRoom=1000000;
inline constexpr std::array<SourcePropEntry,2> PropRoom26{{{4,3,1500,0,0},{8,3,1500,0,1}}};
inline constexpr std::array<SourcePropEntry,3> PropRoom52{{{12,0,1500,0,0},{6,3,14,0,1},{0,6,1500,0,2}}};
inline constexpr std::array<SourcePropEntry,17> PropRoom633{{{11,0,1000,0,0},{12,0,1000,0,1},{1,1,1000,0,2},{11,1,1400,0,3},{12,1,1000,0,4},{4,2,1400,0,5},{8,2,1400,0,6},{5,3,10,1,7},{6,3,1400,0,8},{7,3,10,1,9},{4,4,1400,0,10},{8,4,1400,0,11},{0,5,1000,0,12},{1,5,1400,0,13},{11,5,1000,0,14},{0,6,1000,0,15},{1,6,1000,0,16}}};
inline constexpr std::array<SourcePropEntry,5> PropReviewEntries{{{3,2,1400,0,0},{9,2,1400,0,1},{4,4,1500,0,2},{6,4,1500,0,3},{8,4,1500,0,4}}};
inline constexpr std::array<SourcePropRoom,4> SourcePropRooms{{{26,PropRoom26},{52,PropRoom52},{633,PropRoom633},{PropReviewRoom,PropReviewEntries}}};
inline const SourcePropRoom *sourcePropRoom(int variant){for(const auto &r:SourcePropRooms)if(r.variant==variant)return &r;return nullptr;}
inline uint32_t propSlotSeed(uint32_t seed,int ordinal){if(!seed)seed=1;for(int i=0;i<=ordinal;++i)sourceRoomSpawnRandom(seed);return seed;}
}
