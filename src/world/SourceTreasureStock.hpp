#pragma once
#include "world/SourceShopStock.hpp"
namespace dw {
inline constexpr int RecordedMomsEyeReview=4000006; // Type4/template6 review identity.
// Restricted XML order: Onion1, Cricket4, Bobby8, Halo10, Yum45, Eye55, Book58.
// Canyon seed mixing and restricted pools are explicit adaptations.
inline int sourceTreasureChoice(uint32_t seed,bool includeBobby=false,bool includeYum=false,bool includeHalo=false,bool includeBook=false,bool includeMomsEye=false) {
    if(!includeBobby&&!includeYum&&!includeHalo&&!includeBook&&!includeMomsEye)return sourceTwoCollectibleChoice(seed,1,4);
    // Same original numeric draw/strict weighted scan; legacy helper modes retained.
    if(!seed)seed=1;
    seed^=seed>>1;seed^=seed<<11;seed^=seed>>6;
    const float draw=float(seed)*0x1.fffffcp-33f*(includeMomsEye?7.f:includeBook?6.f:includeHalo?5.f:includeYum?4.f:3.f);
    if(includeMomsEye)return draw<1?1:draw<2?4:draw<3?8:draw<4?10:draw<5?45:draw<6?55:draw<7?58:0;
    if(includeBook)return draw<1?1:draw<2?4:draw<3?8:draw<4?10:draw<5?45:draw<6?58:0;
    if(includeHalo)return draw<1?1:draw<2?4:draw<3?8:draw<4?10:draw<5?45:0;
    return draw<1?1:draw<2?4:draw<3?8:includeYum&&draw<4?45:0;
}
inline int sourceTreasureItem(int mode,uint32_t seed) {
    if(mode<0||mode>7)throw std::invalid_argument("Invalid treasure pool");
    constexpr int fixed[]{1,0,4,8,45,10,58,55};
    if(mode!=1)return fixed[mode];
    const int item=sourceTreasureChoice(seed,true,true,true,true,true);
    return item?item:1;
}
inline uint32_t canyonTreasureSeed(uint64_t floorSeed,int room) {
    uint64_t mixed=floorSeed^0x5452454153555245ULL^(uint64_t(room+1)*0x9e3779b97f4a7c15ULL);
    mixed=(mixed^(mixed>>30))*0xbf58476d1ce4e5b9ULL;
    mixed=(mixed^(mixed>>27))*0x94d049bb133111ebULL;
    const auto seed=uint32_t(mixed^(mixed>>31));return seed?seed:1;
}
}
