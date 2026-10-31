#pragma once
#include "content/Mechanics.hpp"

namespace dw {
enum class ItemPool { Armory, Shop, Boss, Bargain };
const std::vector<WeightedItem> &itemPoolWeights(ItemPool pool,const MechanicsLibrary &content=*defaultMechanics());
int itemPoolWeight(ItemPool pool,const ItemKey &item,const MechanicsLibrary &content=*defaultMechanics());
std::array<ItemKey,2> drawItemOffers(ItemPool pool,uint64_t seed,const MechanicsLibrary &content=*defaultMechanics());
} // namespace dw
