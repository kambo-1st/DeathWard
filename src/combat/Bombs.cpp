#include "combat/Simulation.hpp"
namespace dw {
bool Simulation::spawnOrdinaryBomb(Vector3 at,int subtype,uint32_t seed,bool preplaced) {
    if(dead||finished||!sourceOrdinaryBombValue(subtype)||!seed||bombPickups.size()>=1024||
       !std::isfinite(at.x)||!std::isfinite(at.y)||!std::isfinite(at.z)||arena.blocked(at,.35f))return false;
    const int owner=arena.roomAt(at);if(owner<0)return false;
    // Native pickup resolver: BOGO changes ordinary subtype1 into subtype2 at
    // actor birth. Never double a collected amount or mutate existing actors.
    if(subtype==1&&itemStacks({"isaac",ItemKind::Collectible,250})>0)subtype=2;
    OrdinaryBombPickup pickup;pickup.position=at;pickup.room=owner;pickup.sourceSubtype=subtype;
    pickup.seed=seed;pickup.placedInLayout=preplaced;
    pickup.timing.collectFrames=subtype==2?BombTiming::DoubleCollectFrames:BombTiming::SingleCollectFrames;
    if(!preplaced)pickup.timing.appear(1);
    bombPickups.push_back(pickup);checkpointNeeded=true;return true;
}
void Simulation::deliverRoomBombs(int index) {
    const auto &spawns=arena.rooms[size_t(index)].bombSpawns;
    auto &delivered=rooms[size_t(index)].roomBombsDelivered;delivered.resize(spawns.size(),false);
    for(size_t i=0;i<spawns.size();++i) {
        const auto &s=spawns[i];
        if(!delivered[i]&&arena.roomAt(s.preferred)==index&&spawnOrdinaryBomb(s.preferred,s.subtype,s.pickupSeed,true))delivered[i]=true;
    }
}
void Simulation::updateOrdinaryBombs(float dt) {
    std::erase_if(bombPickups,[&](auto &p) {
        if(p.room!=room)return false;
        p.timing.advance(dt);
        if(p.timing.phase==BombTiming::Phase::Gone)return true;
        if(!p.timing.collectible()||dead||player.totalHealth()<=0||dynamite>=MaxDynamite||
           planarDistance(player.position,p.position)>=1||!arena.clear(player.position,p.position,.1f))return false;
        if(p.shopStock&&(!hasSourceShop(room)||!shopBombOffered()||shopBombSold||!roomClear||roomThreats()||
           shopBombPrice<0||shopBombPrice>15||money()<uint64_t(shopPrice(shopBombPrice,shopBombSlot))))return false;
        if(p.shopStock) {
            const int price=shopPrice(shopBombPrice,shopBombSlot);
            moneySpent+=uint64_t(price);shopBombSold=true;
            announce("DYNAMITE / "+std::to_string(price)+" COINS",2);
        }
        dynamite=std::min(MaxDynamite,dynamite+sourceOrdinaryBombValue(p.sourceSubtype));
        p.timing.collect();audioCues.push(AudioCueKind::Pickup,p.position);
        checkpointNeeded=true;return false;
    });
    deliverShopBomb();
    deliverRoomBombs(room); // Deferred births never consume elapsed time retroactively.
}
} // namespace dw
