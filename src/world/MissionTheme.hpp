#pragma once
#include "core/Types.hpp"

namespace dw {
enum class MissionTheme { Mine, Canyon };
enum class ThemeChoice { Seeded, Mine, Canyon };
struct MissionThemeDefinition {
    const char *name;
    const char *title;
    const char *region;
    const char *passage;
    Color sky, backdrop, floor, stone, edge, gate;
};
inline const MissionThemeDefinition &missionTheme(MissionTheme theme) {
    static constexpr MissionThemeDefinition mine{"Mine",
                                                 "Red Hollow Mine",
                                                 "RED HOLLOW",
                                                 "Mine Passage",
                                                 {26, 29, 28, 255},
                                                 {117, 94, 65, 255},
                                                 {83, 71, 56, 255},
                                                 {94, 77, 55, 255},
                                                 {133, 106, 72, 255},
                                                 {76, 58, 38, 255}};
    static constexpr MissionThemeDefinition canyon{"Canyon",
                                                   "Redstone Canyon",
                                                   "REDSTONE",
                                                   "Canyon Trail",
                                                   {157, 183, 190, 255},
                                                   {157, 102, 67, 255},
                                                   {184, 133, 88, 255},
                                                   {155, 83, 51, 255},
                                                   {211, 153, 97, 255},
                                                   {124, 68, 43, 255}};
    return theme == MissionTheme::Canyon ? canyon : mine;
}
inline MissionTheme resolveTheme(ThemeChoice choice, uint64_t seed) {
    if (choice == ThemeChoice::Mine)
        return MissionTheme::Mine;
    if (choice == ThemeChoice::Canyon)
        return MissionTheme::Canyon;
    Random random(seed ^ 0x5448454d45534d31ULL);
    return random.bounded(2) ? MissionTheme::Canyon : MissionTheme::Mine;
}
} // namespace dw
