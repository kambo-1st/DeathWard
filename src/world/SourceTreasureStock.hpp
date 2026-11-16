#pragma once
#include "world/SourceShopStock.hpp"
namespace dw {
// Restricted eligible XML order: Sad Onion1, Cricket's Head4, equal weight.
// Canyon seed mixing and this two-item pool are explicit adaptations.
inline int sourceTreasureChoice(uint32_t seed,bool includeBobby=false) {
    if(!includeBobby)return sourceTwoCollectibleChoice(seed,1,4);
    // Same original numeric draw/strict weighted scan, restricted XML order 1/4/8.
    if(!seed)seed=1;
    seed^=seed>>1;seed^=seed<<11;seed^=seed>>6;
    const float draw=float(seed)*0x1.fffffcp-33f*3.f;
    return draw<1?1:draw<2?4:draw<3?8:0;
}
inline uint32_t canyonTreasureSeed(uint64_t floorSeed,int room) {
    uint64_t mixed=floorSeed^0x5452454153555245ULL^(uint64_t(room+1)*0x9e3779b97f4a7c15ULL);
    mixed=(mixed^(mixed>>30))*0xbf58476d1ce4e5b9ULL;
    mixed=(mixed^(mixed>>27))*0x94d049bb133111ebULL;
    const auto seed=uint32_t(mixed^(mixed>>31));return seed?seed:1;
}
}
