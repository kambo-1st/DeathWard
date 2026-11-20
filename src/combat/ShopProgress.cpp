#include "combat/Simulation.hpp"
#include "world/SourceShopHeart.hpp"
namespace dw {
void Simulation::configureShopLevel(int level){if(level < -1||level>4)throw std::invalid_argument("Invalid shop level");shopLevelOverride=level;prepareShop();}

void Simulation::prepareUpgradedShop() {
    upgradedShop.clear();shopLevel=shopLevelOverride<0?donationShopLevel(donation.unlocks):shopLevelOverride;
    if(!hasSourceShop(arena.shopRoom)||!sourceShopVariation)return;
    const auto &site=arena.rooms[size_t(arena.shopRoom)];const int count=shopLevel+2;
    const auto stock=sourceShopStock(canyonShopStockSeed(seed_),shopLevel+1); // Native field is1-based.
    if(shopLevel==0&&stock.categories[0]!=5&&stock.categories[1]!=5&&stock.categories[0]!=7&&stock.categories[1]!=7)return;
    std::vector<Vector3> positions;bool fits=false;
    for(int percent=100;percent>=50;--percent) {
        positions.clear();const float cell=std::max(1.1f,recordedShopCellSize(site)*percent/100);bool valid=true;
        for(int slot=0;slot<count;++slot) {
            const auto [x,y]=SourceShopCells[size_t(shopLevel)][size_t(slot)];
            auto at=add(site.center,{(x-6)*cell,0,std::max((y-1)*cell,shopCartGeometry::HalfDepth+.9f)});at.y=.85f;
            if(shopLevel==4&&y==4)at.z=std::max(at.z,site.center.z+shopCartGeometry::HalfDepth+2.65f);
            if(arena.roomAt(at)!=arena.shopRoom||arena.blocked(at,.55f)||arena.path(site.entry,at,.48f).empty()){valid=false;break;}
            for(auto previous:positions)if(planarDistance(previous,at)<2.f)valid=false;
            positions.push_back(at);
        }
        if(valid){fits=true;break;}
    }
    // An incompatible canyon keeps its existing bounded stock. Never put offers inside terrain.
    if(!fits)return;
    bool firstCollectible=true;
    for(int i=0;i<count;++i) {
        auto descriptor=site;
        if(!descriptor.sourceRoomSpawnSeed)descriptor.sourceRoomSpawnSeed=canyonShopStockSeed(seed_); // Explicit DW fallback for unrecorded canyon shops.
        const auto seed=recordedShopSlotSeed(descriptor,(shopLevel==0||shopLevel==3?6:4)+i);
        UpgradedShopOffer offer;offer.position=positions[size_t(i)];offer.category=stock.categories[size_t(i)];offer.slot=i;offer.seed=seed;
        if(offer.category==8){offer.item=firstCollectible?shopUpgradeItem:shopCollectiblePool==1?sourceShopCollectibleChoice(seed,true):shopUpgradeItem;firstCollectible=false;}
        upgradedShop.push_back(offer);
    }
    shopDiscountSlot=stock.discountSlot;
    shopHeartSlot=shopKeySlot=shopBombSlot=shopCardSlot=shopUpgradeSlot=-1;
}
int Simulation::upgradedShopPrice(int slot)const {
    const int category=upgradedShop.at(size_t(slot)).category;
    const int base=category==7?grabBagTuning.price:category==5?batteryTuning.price:category==8?shopUpgradePrice:category==0?shopHeartPrice:category==4?shopSoulHeartPrice:category==3?shopKeyPrice:category==1?shopBombPrice:category==6?bloodMachineTuning.cardPrice:5;
    return shopPrice(base,slot);
}
bool Simulation::canBuyUpgradedShop(int slot)const {
    return slot>=0&&size_t(slot)<upgradedShop.size()&&!upgradedShop[size_t(slot)].sold&&hasSourceShop(room)&&!dead&&!finished&&player.totalHealth()>0&&roomClear&&!roomThreats()&&!shopOpen&&!rewardOpen&&!letterOpen&&storyOpen==StoryRoom::None&&money()>=uint64_t(upgradedShopPrice(slot));
}
bool Simulation::payUpgradedShop(int slot) {
    if(!canBuyUpgradedShop(slot))return false;
    moneySpent+=uint64_t(upgradedShopPrice(slot));upgradedShop[size_t(slot)].sold=true;checkpointNeeded=true;return true;
}
void Simulation::deliverUpgradedShop() {
    if(!hasSourceShop(room)||dead||finished)return;
    for(auto &offer:upgradedShop) {
        if(offer.delivered||offer.sold||!offer.supported()||arena.blocked(offer.position,.48f))continue;
        bool born=false;
        switch(offer.category) {
        case 0:case 4:
            born=spawnHeartPickup(offer.category==4?HeartKind::Soul:HeartKind::Red,offer.position,2);
            if(born){heartPickups.back().upgradedShopSlot=offer.slot;heartPickups.back().sourceSubtype=offer.category==4?3:1;}break;
        case 1:born=spawnOrdinaryBomb(offer.position,1,offer.seed,true);if(born)bombPickups.back().upgradedShopSlot=offer.slot;break;
        case 2:case 6:born=spawnPill(offer.position,offer.category==6?TemperanceCard:sourceOrdinaryPillColor(offer.seed),offer.seed,true);if(born)pillPickups.back().upgradedShopSlot=offer.slot;break;
        case 3:if(sourceShopKey){born=spawnOrdinaryKey(offer.position,1,offer.seed,true);if(born)keyPickups.back().upgradedShopSlot=offer.slot;}break;
        case 7:born=spawnShopGrabBag(offer.position,offer.slot);break;
        case 5:born=spawnShopBattery(offer.position,offer.slot);break;
        case 8:born=true;break; // Existing collectible presentation; collection below.
        }
        if(born){offer.delivered=true;checkpointNeeded=true;}
    }
}
void Simulation::collectUpgradedShopItems() {
    if(!hasSourceShop(room))return;
    for(auto &offer:upgradedShop)if(offer.category==8&&!offer.sold&&planarDistance(player.position,offer.position)<1&&arena.clear(player.position,offer.position,.1f)) {
        const ItemKey item{"isaac",ItemKind::Collectible,uint32_t(offer.item)};
        if(items.size()>=256||!content->item(item)||!payUpgradedShop(offer.slot))continue;
        grant(item);announce(offer.item==195?"MOM'S COIN PURSE / PILLS SPAWNED":offer.item==250?"BOGO BOMBS / DYNAMITE PICKUPS DOUBLE":"STEAM SALE / SHOP DISCOUNT",3);
    }
}
}
