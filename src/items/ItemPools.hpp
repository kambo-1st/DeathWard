#pragma once
#include "core/Types.hpp"

namespace dw {
enum class ItemPool { Armory, Shop, Boss, Bargain };
const std::array<int,ItemCount> &itemPoolWeights(ItemPool pool);
std::array<ItemId,2> drawItemOffers(ItemPool pool,uint64_t seed);
} // namespace dw
