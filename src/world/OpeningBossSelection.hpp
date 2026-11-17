#pragma once
#include "core/Types.hpp"

namespace dw {
struct OpeningBossEntry {int poolId,type;uint32_t weight;};
// Installed Repentance1.7.9b Basement XML, in source order, restricted to the
// two selected ordinary actors. These are not full native pool probabilities.
inline constexpr std::array<OpeningBossEntry,2> SupportedOpeningBosses{{{1,20,1},{13,67,1}}};
inline int seededOpeningBossType(uint64_t floorSeed) {
    // Dedicated DW stream: independent of map dimensions, encounters, runtime
    // draws and run ID. Native unlock/history/global RNG gates remain open.
    Random rng(floorSeed^0x44313343424f5353ULL);
    uint32_t total=0;for(const auto &entry:SupportedOpeningBosses)total+=entry.weight;
    auto draw=rng.bounded(total);
    for(const auto &entry:SupportedOpeningBosses){if(draw<entry.weight)return entry.type;draw-=entry.weight;}
    return SupportedOpeningBosses.back().type;
}
inline int openingBossType(uint64_t floorSeed,bool seeded,bool monstro,bool duke) {
    return seeded?seededOpeningBossType(floorSeed):duke?67:monstro?20:0;
}
} // namespace dw
