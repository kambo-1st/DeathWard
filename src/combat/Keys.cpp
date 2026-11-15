#include "combat/Simulation.hpp"
namespace dw {
bool Simulation::spawnOrdinaryKey(Vector3 at,int subtype,uint32_t seed,bool preplaced) {
    if(dead||finished||!sourceOrdinaryKeyValue(subtype)||!seed||keyPickups.size()>=1024||
       !std::isfinite(at.x)||!std::isfinite(at.y)||!std::isfinite(at.z)||arena.blocked(at,.35f))return false;
    const int owner=arena.roomAt(at);if(owner<0)return false;
    OrdinaryKeyPickup pickup;pickup.position=at;pickup.room=owner;pickup.sourceSubtype=subtype;
    pickup.seed=seed;pickup.placedInLayout=preplaced;
    if(!preplaced)pickup.timing.appear(1);
    keyPickups.push_back(pickup);checkpointNeeded=true;return true;
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
        if(!p.timing.collectible()||dead||player.totalHealth()<=0||keys>=99||
           planarDistance(player.position,p.position)>=1||!arena.clear(player.position,p.position,.1f))return false;
        keys=std::min(99,keys+sourceOrdinaryKeyValue(p.sourceSubtype));
        p.timing.collect();audioCues.push(AudioCueKind::Pickup,p.position);
        checkpointNeeded=true;return false;
    });
    deliverRoomKeys(room); // Deferred births never consume elapsed time retroactively.
}
} // namespace dw
