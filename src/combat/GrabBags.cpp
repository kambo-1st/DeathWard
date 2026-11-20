#include "combat/Simulation.hpp"
namespace dw {
bool Simulation::spawnShopGrabBag(Vector3 at,int slot) {
    if(slot<0||size_t(slot)>=upgradedShop.size()||upgradedShop[size_t(slot)].category!=7||grabBags.size()>=128||dead||finished||arena.blocked(at,.48f))return false;
    const int owner=arena.roomAt(at);if(!hasSourceShop(owner))return false;
    GrabBagPickup p;p.position=at;p.room=owner;p.shopSlot=slot;p.seed=upgradedShop[size_t(slot)].seed;
    p.contents=sourceGrabBagContents(p.seed);
    // Resolve once; unsupported rare subtypes retain identity without reroll.
    // Cards use the existing bounded Temperance producer, not the full source pool.
    for(auto &d:p.contents) {
        if(d.variant==300)d.subtype=TemperanceCard;
        else if(d.variant==90)d.subtype=1;
        else d.subtype=sourceOrdinaryPickup(d.seed,d.variant).subtype;
    }
    grabBags.push_back(std::move(p));checkpointNeeded=true;return true;
}
void Simulation::updateGrabBags(float dt) {
    for(auto &bag:grabBags)if(bag.room==room) {
        if(!bag.opened){
            if(!grabBagTuning.enabled||!canBuyUpgradedShop(bag.shopSlot)||planarDistance(player.position,bag.position)>=1||!arena.clear(player.position,bag.position,.1f))continue;
            if(!payUpgradedShop(bag.shopSlot))continue;
            bag.opened=true;bag.timing.collect();checkpointNeeded=true;
            audioCues.push(AudioCueKind::Pickup,bag.position);announce("GRAB BAG / SUPPLIES UNPACKED",3);
        } else bag.timing.advance(dt);
        for(size_t i=0;i<bag.contents.size();++i){
            auto &d=bag.contents[i];if(d.delivered)continue;
            // Existing ordinary pickup coverage; special key/bomb identities stay
            // recorded and unspawned. Do not silently convert them to basic loot.
            if((d.variant==30&&!sourceOrdinaryKeyValue(d.subtype))||(d.variant==40&&!sourceOrdinaryBombValue(d.subtype)))continue;
            for(int attempt=0;attempt<144;++attempt){
                const float angle=float(i)*2.399963f+float(attempt%24)*2*Pi/24;
                const float radius=1.6f+float(attempt/24)*.6f;
                Vector3 at{bag.position.x+std::cos(angle)*radius,.85f,bag.position.z+std::sin(angle)*radius};
                if(arena.roomAt(at)!=room||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.5f)||!arena.clear(bag.position,at,.25f)||arena.path(player.position,at,.48f).empty())continue;
                bool conflict=false;
                for(const auto &o:upgradedShop)if(!o.sold&&planarDistance(o.position,at)<1.3f)conflict=true;
                for(int p:arena.rooms[size_t(room)].passages)for(const auto &gate:arena.passages[size_t(p)].gates)if(sphereBox(at,.5f,gate))conflict=true;
                const auto near=[&](const auto &p){return p.room==room&&planarDistance(p.position,at)<.8f;};
                if(conflict||std::any_of(moneyPickups.begin(),moneyPickups.end(),near)||std::any_of(keyPickups.begin(),keyPickups.end(),near)||std::any_of(bombPickups.begin(),bombPickups.end(),near)||std::any_of(batteryPickups.begin(),batteryPickups.end(),near)||std::any_of(pillPickups.begin(),pillPickups.end(),near))continue;
                bool born=false;
                if(d.variant==20&&moneyPickups.size()<1024){MoneyPickup coin{at,sourceOrdinaryCoinValue(d.subtype),0,true};coin.sourceSubtype=d.subtype;coin.room=room;coin.timing.appear(1);moneyPickups.push_back(coin);born=true;}
                else if(d.variant==30)born=spawnOrdinaryKey(at,d.subtype,d.seed);
                else if(d.variant==40)born=spawnOrdinaryBomb(at,d.subtype,d.seed);
                else if(d.variant==90)born=spawnBattery(at);
                else if(d.variant==300)born=spawnPill(at,d.subtype,d.seed);
                if(born){d.delivered=true;checkpointNeeded=true;}break;
            }
        }
    }
}
}
