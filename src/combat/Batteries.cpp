#include "combat/Simulation.hpp"
namespace dw {
bool Simulation::spawnShopBattery(Vector3 at,int slot) {
    if(slot<0||size_t(slot)>=upgradedShop.size()||upgradedShop[size_t(slot)].category!=5||batteryPickups.size()>=1024||dead||finished||arena.blocked(at,.48f))return false;
    const int roomIndex=arena.roomAt(at);if(!hasSourceShop(roomIndex))return false;
    batteryPickups.push_back({at,roomIndex,slot,{}});checkpointNeeded=true;return true;
}
bool Simulation::spawnBattery(Vector3 at) {
    if(dead||finished||batteryPickups.size()>=1024||!std::isfinite(at.x)||!std::isfinite(at.y)||!std::isfinite(at.z)||arena.blocked(at,.48f))return false;
    const int owner=arena.roomAt(at);if(owner<0)return false;
    BatteryPickup p{at,owner,-1,{}};p.timing.appear();batteryPickups.push_back(p);checkpointNeeded=true;return true;
}
void Simulation::updateBatteries(float dt) {
    std::erase_if(batteryPickups,[&](BatteryPickup &p){
        if(p.room!=room)return false;
        p.timing.advance(dt);if(p.timing.phase==BatteryTiming::Phase::Gone)return true;
        if(!p.timing.collectible()||!batteryTuning.enabled||!activeItem||(p.shopSlot>=0&&!canBuyUpgradedShop(p.shopSlot))||
           planarDistance(player.position,p.position)>=1||!arena.clear(player.position,p.position,.1f))return false;
        activeItem->validate();batteryTuning.validate();
        const int gain=batteryChargeGain(activeItem->charge,activeCapacity(activeItem->item),batteryTuning.charges);
        if(gain<=0||(p.shopSlot>=0&&!payUpgradedShop(p.shopSlot)))return false;
        activeItem->charge+=gain;p.timing.collect();checkpointNeeded=true;
        audioCues.push(AudioCueKind::Pickup,p.position);announce("BATTERY / +"+std::to_string(gain)+" ACTIVE CHARGES",3);
        return false;
    });
}
}
