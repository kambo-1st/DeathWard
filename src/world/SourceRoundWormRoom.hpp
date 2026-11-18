#pragma once
#include <array>
namespace dw {
// Installed Basement1.505.0, difficulty5/weight1. Full recorded content;
// source door metadata never changes the retained canyon connections.
inline constexpr std::array<std::array<int,2>,36> Basement505Rocks{{
    {0,0},{1,0},{12,0},{0,1},{0,2},{2,2},{0,3},{0,4},{1,4},{3,4},
    {0,5},{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},{8,5},{9,5},{10,5},{11,5},{12,5},
    {0,6},{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6},{8,6},{9,6},{10,6},{11,6},{12,6}
}};
inline constexpr std::array<std::array<int,2>,2> Basement505Worms{{{1,1},{2,4}}};
} // namespace dw
