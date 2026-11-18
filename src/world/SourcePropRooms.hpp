#pragma once
#include <array>
#include <span>
#include "world/SourceRoomSelection.hpp"
#include "world/Dungeon.hpp"
namespace dw {
struct SourcePropEntry {int x,y,type,variant,ordinal;};
struct SourcePropRoom {int variant;std::span<const SourcePropEntry> entries;int width=13,height=7,type=1,subtype=0;};
inline constexpr int RecordedDukeRoom=2012;
inline constexpr std::array<SourcePropEntry,8> PropRoom2012{{{0,0,1500,0,0},{5,1,1000,0,1},{11,1,1000,0,2},{6,3,67,0,3},{7,3,18,0,4},{1,5,1000,0,5},{8,5,1000,0,6},{12,6,1500,0,7}}};
inline constexpr int PropReviewRoom=1000000;
inline constexpr std::array<SourcePropEntry,8> PropRoom51{{{0,0,1000,0,0},{11,0,1500,0,1},{12,0,1500,0,2},{6,2,10,0,3},{6,4,10,0,4},{0,6,1500,0,5},{1,6,1500,0,6},{12,6,1000,0,7}}};
inline constexpr std::array<SourcePropEntry,2> PropRoom26{{{4,3,1500,0,0},{8,3,1500,0,1}}};
inline constexpr std::array<SourcePropEntry,3> PropRoom52{{{12,0,1500,0,0},{6,3,14,0,1},{0,6,1500,0,2}}};
inline constexpr std::array<SourcePropEntry,17> PropRoom633{{{11,0,1000,0,0},{12,0,1000,0,1},{1,1,1000,0,2},{11,1,1400,0,3},{12,1,1000,0,4},{4,2,1400,0,5},{8,2,1400,0,6},{5,3,10,1,7},{6,3,1400,0,8},{7,3,10,1,9},{4,4,1400,0,10},{8,4,1400,0,11},{0,5,1000,0,12},{1,5,1400,0,13},{11,5,1000,0,14},{0,6,1000,0,15},{1,6,1000,0,16}}};
inline constexpr std::array<SourcePropEntry,5> PropReviewEntries{{{3,2,1400,0,0},{9,2,1400,0,1},{4,4,1500,0,2},{6,4,1500,0,3},{8,4,1500,0,4}}};
inline constexpr std::array<SourcePropEntry,40> PropRoom414{{{0,0,1500,0,0},{1,0,1500,0,1},{24,0,1500,0,2},{25,0,1500,0,3},{0,1,1500,0,4},{1,1,14,0,5},{24,1,14,0,6},{25,1,1500,0,7},{13,2,18,0,8},{12,3,18,0,9},{4,4,1500,0,10},{21,4,1500,0,11},{11,5,18,0,12},{12,5,14,0,13},{14,5,18,0,14},{9,6,18,0,15},{12,6,1500,0,16},{13,6,1500,0,17},{14,6,14,0,18},{16,6,18,0,19},{8,7,18,0,20},{11,7,14,0,21},{12,7,1500,0,22},{13,7,1500,0,23},{17,7,18,0,24},{11,8,18,0,25},{13,8,14,0,26},{14,8,18,0,27},{4,9,1500,0,28},{21,9,1500,0,29},{13,10,18,0,30},{12,11,18,0,31},{0,12,1500,0,32},{1,12,14,0,33},{24,12,14,0,34},{25,12,1500,0,35},{0,13,1500,0,36},{1,13,1500,0,37},{24,13,1500,0,38},{25,13,1500,0,39}}};
inline constexpr std::array<SourcePropRoom,7> SourcePropRooms{{{RecordedDukeRoom,PropRoom2012,13,7,5,13},{414,PropRoom414,26,14},{51,PropRoom51},{26,PropRoom26},{52,PropRoom52},{633,PropRoom633},{PropReviewRoom,PropReviewEntries}}};
inline const SourcePropRoom *sourcePropRoom(int variant){for(const auto &r:SourcePropRooms)if(r.variant==variant)return &r;return nullptr;}
inline float sourcePropCellSize(const RoomLayout &layout,const SourcePropRoom &source) {
    if(layout.sourcePropCellOverride>0)return layout.sourcePropCellOverride;
    const auto size=sub(layout.bounds.max,layout.bounds.min);
    return std::min(size.x*.86f/source.width,size.z*.86f/source.height);
}
inline Vector3 sourcePropCell(const RoomLayout &layout,const SourcePropRoom &source,int x,int y) {
    const float cell=sourcePropCellSize(layout,source);
    return add(layout.center,{(x-(source.width-1)*.5f)*cell,0,(y-(source.height-1)*.5f)*cell});
}
inline uint32_t propSlotSeed(uint32_t seed,int ordinal){if(!seed)seed=1;for(int i=0;i<=ordinal;++i)sourceRoomSpawnRandom(seed);return seed;}
}
