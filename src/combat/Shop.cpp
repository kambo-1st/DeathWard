#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include "items/ItemPools.hpp"
#include "world/SourceShopHeart.hpp"
#include "world/SourceShopStock.hpp"

namespace dw {
bool Simulation::hasSourceShop(int index) const {
    return sourceShopHeart&&floor==0&&!surveyTutorial&&arena.theme==MissionTheme::Canyon&&
        arena.profile.active()&&index==arena.shopRoom&&index>=0&&index<arena.roomCount()&&
        arena.rooms[size_t(index)].kind==RoomKind::Shop;
}
Vector3 Simulation::shopHeartPosition() const {
    return shopHeartSlot==0?sourceShopKeyPosition(arena.rooms.at(size_t(arena.shopRoom))):sourceShopHeartPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
Vector3 Simulation::shopKeyPosition() const {
    return shopKeySlot==1?sourceShopHeartPosition(arena.rooms.at(size_t(arena.shopRoom))):sourceShopKeyPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
Vector3 Simulation::shopBombPosition() const {
    return shopBombSlot==0?sourceShopKeyPosition(arena.rooms.at(size_t(arena.shopRoom))):sourceShopHeartPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
void Simulation::deliverShopBomb() {
    if(!hasSourceShop(room)||!shopBombOffered()||shopBombDelivered||shopBombSold||dead||finished)return;
    const auto at=shopBombPosition();
    const uint32_t pickupSeed=uint32_t(seed_^0x53484f50424f4d42ULL)|1U; // Explicit DW actor seed.
    if(arena.blocked(at,.48f)||!spawnOrdinaryBomb(at,1,pickupSeed,true))return;
    bombPickups.back().shopStock=true;shopBombDelivered=true;checkpointNeeded=true;
}
void Simulation::deliverShopKey() {
    if(!hasSourceShop(room)||!shopKeyOffered()||shopKeyDelivered||shopKeySold||dead||finished)return;
    const auto at=shopKeyPosition();
    // Stable DW actor seed; native shop stock/factory RNG is a separate open scope.
    const uint32_t pickupSeed=uint32_t(seed_^0x53484f504b4559ULL)|1U;
    if(arena.blocked(at,.48f)||!spawnOrdinaryKey(at,1,pickupSeed,true))return;
    keyPickups.back().shopStock=true;shopKeyDelivered=true;checkpointNeeded=true;
}
void Simulation::deliverShopHeart() {
    if(!hasSourceShop(room)||!shopHeartOffered()||shopHeartDelivered||shopHeartSold||dead||finished)return;
    const auto at=shopHeartPosition();
    if(arena.blocked(at,.48f)||!spawnHeartPickup(HeartKind::Red,at,2))return;
    auto &heart=heartPickups.back();heart.sourceSubtype=1;heart.shopStock=true;
    shopHeartDelivered=true;checkpointNeeded=true; // Idle on entry, no clear-reward birth.
}
Vector3 Simulation::shopUpgradePosition() const {
    return shopUpgradeSlot==0?sourceShopKeyPosition(arena.rooms.at(size_t(arena.shopRoom))):sourceShopHeartPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
int Simulation::shopPrice(int base,int slot) const {
    const int copies=steamSaleDiscounts?itemStacks({"isaac",ItemKind::Collectible,64}):0;
    // The native random sale and Steam Sale use the same count; they do not multiply.
    const int discounts=copies>0?copies:(slot>=0&&slot==shopDiscountSlot?1:0);
    return sourceShopDiscountPrice(base,discounts);
}
bool Simulation::collectShopUpgrade() {
    if(!hasSourceShop(room)||!shopVariationActive()||shopUpgradeSold||dead||finished||
       player.totalHealth()<=0||!roomClear||roomThreats()||shopOpen||rewardOpen||letterOpen||
       storyOpen!=StoryRoom::None||items.size()>=256||shopUpgradePrice<0||shopUpgradePrice>30)return false;
    const auto at=shopUpgradePosition();
    if(planarDistance(player.position,at)>=1||!arena.clear(player.position,at,.1f))return false;
    const int price=shopPrice(shopUpgradePrice,shopUpgradeSlot);
    const ItemKey item{"isaac",ItemKind::Collectible,64};
    if(!content->item(item)||money()<uint64_t(price))return false;
    moneySpent+=uint64_t(price);shopUpgradeSold=true;grant(item);
    announce("STEAM SALE / SHOP DISCOUNT",3);checkpointNeeded=true;return true;
}
void Simulation::prepareShop() {
    shopHeartSlot=1;shopKeySlot=0;shopUpgradeSlot=shopDiscountSlot=shopBombSlot=-1;
    if(hasSourceShop(arena.shopRoom)&&sourceShopVariation) {
        const auto stock=sourceShopStock(canyonShopStockSeed(seed_)); // Supplied basic shop level0.
        const int a=stock.categories[0],b=stock.categories[1];
        if((a==8&&(b==0||b==1||b==3))||(b==8&&(a==0||a==1||a==3))) {
            shopUpgradeSlot=a==8?0:1;
            shopHeartSlot=a==0?0:b==0?1:-1;shopKeySlot=a==3?0:b==3?1:-1;
            shopBombSlot=a==1?0:b==1?1:-1;
            shopDiscountSlot=stock.discountSlot;
        }
        // No category reroll. Other pairs retain the explicit previous fixed-pair fallback.
        // Collectible pool selection is bounded to the eligible Steam Sale offering.
    }
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
