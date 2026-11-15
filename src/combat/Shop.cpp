#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include "items/ItemPools.hpp"
#include "world/SourceShopHeart.hpp"

namespace dw {
bool Simulation::hasSourceShop(int index) const {
    return sourceShopHeart&&floor==0&&!surveyTutorial&&arena.theme==MissionTheme::Canyon&&
        arena.profile.active()&&index==arena.shopRoom&&index>=0&&index<arena.roomCount()&&
        arena.rooms[size_t(index)].kind==RoomKind::Shop;
}
Vector3 Simulation::shopHeartPosition() const {
    return sourceShopHeartPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
Vector3 Simulation::shopKeyPosition() const {
    return sourceShopKeyPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
void Simulation::deliverShopKey() {
    if(!hasSourceShop(room)||!sourceShopKey||shopKeyDelivered||shopKeySold||dead||finished)return;
    const auto at=shopKeyPosition();
    // Stable DW actor seed; native shop stock/factory RNG is a separate open scope.
    const uint32_t pickupSeed=uint32_t(seed_^0x53484f504b4559ULL)|1U;
    if(arena.blocked(at,.48f)||!spawnOrdinaryKey(at,1,pickupSeed,true))return;
    keyPickups.back().shopStock=true;shopKeyDelivered=true;checkpointNeeded=true;
}
void Simulation::deliverShopHeart() {
    if(!hasSourceShop(room)||shopHeartDelivered||shopHeartSold||dead||finished)return;
    const auto at=shopHeartPosition();
    if(arena.blocked(at,.48f)||!spawnHeartPickup(HeartKind::Red,at,2))return;
    auto &heart=heartPickups.back();heart.sourceSubtype=1;heart.shopStock=true;
    shopHeartDelivered=true;checkpointNeeded=true; // Idle on entry, no clear-reward birth.
}
void Simulation::prepareShop() {
    Random rng(seed_ ^ 0x53484f5053544f43ULL);
    std::array<ItemId, ItemCount> pool{};
    const int available=surveyTutorial||expedition.pacing==ExpeditionPacing::Classic?LegacyItemCount:ItemCount;
    for(int i=0;i<available;++i)pool[size_t(i)]=ItemId(i);
    shopOffers[0] = {ItemId::Ricochet, 10, ShopOfferKind::Medicine, false};
    for (int i = 0; i < 2; ++i) {
        const int other = i + int(rng.bounded(available - i));
        std::swap(pool[size_t(i)], pool[size_t(other)]);
        shopOffers[size_t(i + 1)] = {pool[size_t(i)], 25, ShopOfferKind::Power, false};
    }
    shopOffers[3] = {ItemId::Ricochet, 15, ShopOfferKind::Dynamite, false};
    if(arena.profile.active()) {
        const auto offers=drawItemOffers(ItemPool::Shop,seed_,*content);
        for(int i=0;i<2;++i)shopOffers[size_t(i+1)].item=offers[size_t(i)];
    }
}
void Simulation::openShop() {
    if(hasSourceShop(room))return; // Priced floor pickups use ordinary touch collection.
    if ((room != arena.shopRoom && arena.rooms[size_t(room)].kind!=RoomKind::Service) || dead || finished || rewardOpen || !roomClear ||
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
    shopOpen = rewardOpen = false;
    cancelMove();
}
std::string Simulation::shopUnavailable(int index) const {
    if(hasSourceShop(room))return "SHOP PICKUPS / WALK UP TO BUY";
    if(arena.rooms[size_t(room)].kind==RoomKind::Service)return serviceUnavailable(index);
    if (index < 0 || index >= int(shopOffers.size()) || !shopOpen || room != arena.shopRoom || !roomClear ||
        roomThreats() || dead || finished ||
        distance(player.position, arena.rooms[size_t(room)].objective) > 2.6f ||
        !arena.sight(player.position, arena.rooms[size_t(room)].objective))
        return "SHOP CLOSED";
    const auto &offer = shopOffers[size_t(index)];
    if (offer.sold)
        return "SOLD OUT";
    if (offer.kind == ShopOfferKind::Medicine && player.hp >= player.redHealthCapacity())
        return "HEALTH FULL";
    if (offer.kind == ShopOfferKind::Power && items.size() >= 256)
        return "INVENTORY FULL";
    if (offer.kind == ShopOfferKind::Dynamite && dynamite > MaxDynamite - 3)
        return "DYNAMITE FULL";
    if (money() < uint64_t(offer.price))
        return "NEED " + std::to_string(uint64_t(offer.price) - money()) + " MORE COINS";
    return {};
}
bool Simulation::buyShop(int index) {
    if(arena.rooms[size_t(room)].kind==RoomKind::Service)return buyService(index);
    if (!shopUnavailable(index).empty())
        return false;
    auto &offer = shopOffers[size_t(index)];
    moneySpent += uint64_t(offer.price);
    offer.sold = true;
    if (offer.kind == ShopOfferKind::Dynamite) {
        dynamite += 3;
        audioCues.push(AudioCueKind::Pickup, player.position);
        announce("Three sticks of dynamite. Mind the fuse.");
    } else if (offer.kind == ShopOfferKind::Medicine) {
        collectHeart(HeartKind::Red,2);
        audioCues.push(AudioCueKind::Pickup, player.position);
        announce("Field medicine / restored up to one red heart.");
    } else
        grant(offer.item);
    checkpointNeeded = true;
    return true;
}
} // namespace dw
