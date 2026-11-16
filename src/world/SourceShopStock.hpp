#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
namespace dw {
// Ordinary normal-mode/config-variant0 initializer from installed 1.7.9b.
// Caller supplies descriptor stock seed and shop level; floor/profile/item-pool
// selection are separate. Category8 is a collectible, not a particular item.
struct SourceShopStock {
    std::array<int,8> categories{};
    int discountSlot=-1;
    uint32_t rngAfter=0;
};
inline SourceShopStock sourceShopStock(uint32_t seed,int level=0) {
    uint32_t state=seed?seed:1;
    const auto next=[&]{state^=state>>5;state^=state<<9;state^=state>>7;return state;};
    std::array<int,9> pool{0,1,2,3,4,5,6,7,8};
    const int count=level>=4?9:8;
    for(int i=count-1;i>0;--i)std::swap(pool[size_t(i)],pool[size_t(next()%uint32_t(i+1))]);
    SourceShopStock result;std::copy_n(pool.begin(),8,result.categories.begin());
    result.categories[next()%2]=8;
    if(next()%3)result.discountSlot=int(next()%6);
    result.rngAfter=state;return result;
}
inline int sourceShopDiscountPrice(int base,int discountCount) {
    if(base<=0||discountCount<=0)return base;
    if(base>5&&discountCount==1)return base/2;
    return int(std::ceil(float(base)/float(discountCount+1)));
}
// Explicit DW seed adapter, separate from native descriptor generation.
inline uint32_t canyonShopStockSeed(uint64_t floorSeed) {
    const auto seed=uint32_t(floorSeed)^0x53544f43U;
    return seed?seed:1;
}
} // namespace dw
