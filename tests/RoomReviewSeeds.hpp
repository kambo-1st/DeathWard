#pragma once
#include <cstdint>
#include <cmath>
#include <stdexcept>
// Natural Simulation witnesses after optional-shop generation. See the recorded
// scanner/grid CSVs; templates and outcomes are never forced by these fixtures.
namespace review {
struct RoomCase {int variant;float scale;int minimum,maximum;uint64_t seed;int room;};
inline constexpr RoomCase Rooms[] = {
    {4,0.75f,5,5,22,4},
    {4,0.75f,7,9,22,4},
    {4,0.75f,10,10,22,4},
    {4,1.1f,5,5,22,4},
    {4,1.1f,7,9,443,1},
    {4,1.1f,10,10,586,1},
    {4,1.5f,5,5,22,4},
    {4,1.5f,7,9,443,1},
    {4,1.5f,10,10,268,4},
    {30,0.75f,5,5,84,4},
    {30,1.1f,7,9,84,4},
    {30,1.5f,10,10,84,4},
    {31,0.75f,5,5,1290,5},
    {31,1.1f,7,9,1290,5},
    {31,1.5f,10,10,1213,5},
    {32,0.75f,5,5,1860,5},
    {32,1.1f,7,9,1860,5},
    {32,1.5f,10,10,1860,5},
    {91,0.75f,5,5,195,2},
    {91,0.75f,7,9,195,2},
    {91,0.75f,10,10,195,2},
    {91,1.1f,5,5,195,2},
    {91,1.1f,7,9,195,2},
    {91,1.1f,10,10,195,2},
    {91,1.5f,5,5,195,2},
    {91,1.5f,7,9,195,2},
    {91,1.5f,10,10,195,2},
    {108,0.75f,5,5,680,4},
    {108,0.75f,7,9,2046,5},
    {108,0.75f,10,10,2046,5},
    {108,1.1f,5,5,680,4},
    {108,1.1f,7,9,853,4},
    {108,1.1f,10,10,680,4},
    {108,1.5f,5,5,2046,5},
    {108,1.5f,7,9,680,4},
    {108,1.5f,10,10,853,4},
    {109,0.75f,5,5,436,5},
    {109,1.1f,7,9,649,4},
    {109,1.5f,10,10,649,4},
    {214,0.75f,5,5,890,5},
    {214,1.1f,7,9,1525,4},
    {214,1.5f,10,10,890,5},
    {547,0.75f,5,5,922,1},
    {547,1.1f,7,9,899,5},
    {547,1.5f,10,10,922,1},
    {548,0.75f,5,5,487,4},
    {548,1.1f,7,9,487,4},
    {548,1.5f,10,10,254,5},
    {550,0.75f,5,5,10,4},
    {550,1.1f,7,9,378,5},
    {550,1.5f,10,10,10,4},

};
inline RoomCase roomCase(int variant,float scale=1.1f,int minimum=7,int maximum=9) {
    for(const auto &r:Rooms)if(r.variant==variant&&std::abs(r.scale-scale)<.001f&&r.minimum==minimum&&r.maximum==maximum)return r;
    throw std::runtime_error("Missing recorded room review fixture");
}
inline uint64_t seed(int variant,float scale=1.1f,int minimum=7,int maximum=9){return roomCase(variant,scale,minimum,maximum).seed;}
inline int room(int variant,float scale=1.1f,int minimum=7,int maximum=9){return roomCase(variant,scale,minimum,maximum).room;}
inline constexpr uint64_t FullHeartClearSeed=3;
}
