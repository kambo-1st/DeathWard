#include "items/ItemPools.hpp"

namespace dw {
const std::array<int,ItemCount> &itemPoolWeights(ItemPool pool) {
    // Deliberately overlapping contexts, not one uniform bag. Indexed by ItemId:
    // Ricochet, Split, Judas, Powder, Ghost, Scatter, Rail, Lodestone, Return, Cap, Braid.
    static constexpr std::array<std::array<int,ItemCount>,4> weights{{
        {4,4,0,0,0,5,5,3,3,1,1}, // Armory: firing forms and trajectories.
        {4,0,0,0,0,2,1,5,4,1,5}, // Shop: utility, guidance and explosive support.
        {1,3,0,3,3,0,4,3,2,0,2}, // Boss: pierce and kill-chain payoffs.
        {0,1,4,4,4,0,1,0,0,4,0}  // Bargain: unusual/risky effects for maximum HP.
    }};
    return weights.at(size_t(pool));
}
std::array<ItemId,2> drawItemOffers(ItemPool pool,uint64_t seed) {
    Random rng(seed^(0x4954454d504f4f4cULL+uint64_t(pool)*0x9e3779b97f4a7c15ULL));
    auto weights=itemPoolWeights(pool);std::array<ItemId,2> result{};
    for(auto &item:result) {
        int total=0;for(int weight:weights)total+=weight;
        int roll=int(rng.bounded(uint32_t(total)));
        for(int i=0;i<ItemCount;++i) {
            roll-=weights[size_t(i)];
            if(roll<0){item=ItemId(i);weights[size_t(i)]=0;break;}
        }
    }
    return result;
}
} // namespace dw
