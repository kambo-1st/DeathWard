#include "items/ItemPools.hpp"

namespace dw {
const std::vector<WeightedItem> &itemPoolWeights(ItemPool pool,const MechanicsLibrary &content) {
    static constexpr std::array<const char *,4> names{"armory","shop","boss","bargain"};
    return content.pool(names.at(size_t(pool)));
}
int itemPoolWeight(ItemPool pool,const ItemKey &item,const MechanicsLibrary &content) {
    for(const auto &entry:itemPoolWeights(pool,content))if(entry.item==item)return entry.weight;
    return 0;
}
std::array<ItemKey,2> drawItemOffers(ItemPool pool,uint64_t seed,const MechanicsLibrary &content) {
    Random rng(seed^(0x4954454d504f4f4cULL+uint64_t(pool)*0x9e3779b97f4a7c15ULL));
    auto weights=itemPoolWeights(pool,content);std::array<ItemKey,2> result{};
    for(auto &item:result) {
        int total=0;for(const auto &entry:weights)total+=entry.weight;
        int roll=int(rng.bounded(uint32_t(total)));
        for(auto &entry:weights) {
            roll-=entry.weight;
            if(roll<0){item=entry.item;entry.weight=0;break;}
        }
    }
    return result;
}
} // namespace dw
