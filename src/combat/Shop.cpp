#include "combat/Simulation.hpp"
#include "items/Items.hpp"

namespace dw {
void Simulation::prepareShop() {
    Random rng(seed_ ^ 0x53484f5053544f43ULL);
    std::array<ItemId, ItemCount> pool{ItemId::Ricochet, ItemId::Split, ItemId::Judas, ItemId::Powder,
                                       ItemId::Ghost};
    shopOffers[0] = {ItemId::Ricochet, 10, true, false};
    for (int i = 0; i < 2; ++i) {
        const int other = i + int(rng.bounded(ItemCount - i));
        std::swap(pool[size_t(i)], pool[size_t(other)]);
        shopOffers[size_t(i + 1)] = {pool[size_t(i)], 25, false, false};
    }
}
void Simulation::openShop() {
    if (arena.shopRoom < 0 || room != arena.shopRoom || dead || finished || rewardOpen || !roomClear ||
        roomThreats() != 0 || distance(player.position, arena.rooms[size_t(room)].objective) > 2.6f ||
        !arena.sight(player.position, arena.rooms[size_t(room)].objective))
        return;
    cancelMove();
    player.velocity = {};
    player.shootPose = 0;
    shopOpen = true;
    audioCues.push(AudioCueKind::UI, player.position);
}
void Simulation::closeShop() {
    shopOpen = false;
    cancelMove();
}
std::string Simulation::shopUnavailable(int index) const {
    if (index < 0 || index >= int(shopOffers.size()) || !shopOpen || room != arena.shopRoom || !roomClear ||
        roomThreats() || dead || finished ||
        distance(player.position, arena.rooms[size_t(room)].objective) > 2.6f ||
        !arena.sight(player.position, arena.rooms[size_t(room)].objective))
        return "SHOP CLOSED";
    const auto &offer = shopOffers[size_t(index)];
    if (offer.sold)
        return "SOLD OUT";
    if (offer.medicine && player.hp >= player.maxHp)
        return "HEALTH FULL";
    if (!offer.medicine && items.size() >= 256)
        return "INVENTORY FULL";
    if (money() < uint64_t(offer.price))
        return "NEED " + std::to_string(uint64_t(offer.price) - money()) + " MORE COINS";
    return {};
}
bool Simulation::buyShop(int index) {
    if (!shopUnavailable(index).empty())
        return false;
    auto &offer = shopOffers[size_t(index)];
    moneySpent += uint64_t(offer.price);
    offer.sold = true;
    if (offer.medicine) {
        player.hp = std::min(player.maxHp, player.hp + 40);
        audioCues.push(AudioCueKind::Pickup, player.position);
        announce("Field medicine / restored up to 40 health.");
    } else
        grant(offer.item);
    checkpointNeeded = true;
    return true;
}
} // namespace dw
