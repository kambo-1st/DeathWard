#include "combat/Simulation.hpp"
namespace dw {
namespace {
bool admitKey(Simulation &run,Vector3 at,int subtype,uint32_t seed,bool preplaced) {
    if(run.dead||run.finished||!seed||run.keyPickups.size()>=1024||
       !std::isfinite(at.x)||!std::isfinite(at.y)||!std::isfinite(at.z)||run.arena.blocked(at,.35f))return false;
    const int owner=run.arena.roomAt(at);if(owner<0)return false;
    OrdinaryKeyPickup pickup;pickup.position=at;pickup.room=owner;pickup.sourceSubtype=subtype;
    pickup.seed=seed;pickup.placedInLayout=preplaced;
    if(!preplaced)pickup.timing.appear(1);
    run.keyPickups.push_back(pickup);run.checkpointNeeded=true;return true;
}
}
bool Simulation::spawnOrdinaryKey(Vector3 at,int subtype,uint32_t seed,bool preplaced) {
    return sourceOrdinaryKeyValue(subtype)&&admitKey(*this,at,subtype,seed,preplaced);
}
bool Simulation::spawnGoldenKey(Vector3 at,uint32_t seed) {
    // Selected bag producer only. Other unresolved key producers retain their scope.
    return grabBagTuning.goldenKeys&&admitKey(*this,at,2,seed,false);
}
void Simulation::deliverRoomKeys(int index) {
    const auto &spawns=arena.rooms[size_t(index)].keySpawns;
    auto &delivered=rooms[size_t(index)].roomKeysDelivered;delivered.resize(spawns.size(),false);
    for(size_t i=0;i<spawns.size();++i) {
        const auto &s=spawns[i];
        if(!delivered[i]&&arena.roomAt(s.preferred)==index&&spawnOrdinaryKey(s.preferred,s.subtype,s.pickupSeed,true))delivered[i]=true;
    }
}
void Simulation::updateOrdinaryKeys(float dt) {
    std::erase_if(keyPickups,[&](auto &p) {
        if(p.room!=room)return false;
        p.timing.advance(dt);
        if(p.timing.phase==KeyTiming::Phase::Gone)return true;
        const bool golden=p.sourceSubtype==2;
        if(!p.timing.collectible()||dead||player.totalHealth()<=0||(!golden&&keys>=99)||
           planarDistance(player.position,p.position)>=1||!arena.clear(player.position,p.position,.1f))return false;
        if(p.upgradedShopSlot>=0&&!canBuyUpgradedShop(p.upgradedShopSlot))return false;
        if(p.shopStock&&(!hasSourceShop(room)||!shopKeyOffered()||!sourceShopKey||shopKeySold||!roomClear||roomThreats()||
           shopKeyPrice<0||shopKeyPrice>15||money()<uint64_t(shopPrice(shopKeyPrice,shopKeySlot))))return false;
        if(p.upgradedShopSlot>=0&&!payUpgradedShop(p.upgradedShopSlot))return false;
        if(p.shopStock) {
            moneySpent+=uint64_t(shopPrice(shopKeyPrice,shopKeySlot));shopKeySold=true;
            announce("KEY / "+std::to_string(shopPrice(shopKeyPrice,shopKeySlot))+" COINS",2);
        }
        if(golden){goldenKey=true;announce("GOLDEN KEY / FREE LOCKS THIS FLOOR",3);}
        else keys=std::min(99,keys+sourceOrdinaryKeyValue(p.sourceSubtype));
        p.timing.collect();audioCues.push(AudioCueKind::Pickup,p.position);
        checkpointNeeded=true;return false;
    });
    deliverRoomKeys(room); // Deferred births never consume elapsed time retroactively.
    deliverShopKey();
}
} // namespace dw
