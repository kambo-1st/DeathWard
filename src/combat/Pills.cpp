#include "combat/Simulation.hpp"
namespace dw {
void Simulation::queuePursePills() {
    // Dedicated DW item seed stream. Birth identity/count are fixed now and
    // placement retries never reroll or charge the player again.
    for(int i=0;i<pillTuning.purseCount;++i){
        purseRng_=purseRng_?purseRng_:1;purseRng_^=purseRng_>>1;purseRng_^=purseRng_<<11;purseRng_^=purseRng_>>6;
        pendingPursePills.push_back({player.position,room,sourceOrdinaryPillColor(purseRng_),i,purseRng_});
    }
    checkpointNeeded=true;
}
bool Simulation::spawnPill(Vector3 at,int color,uint32_t seed,bool idle) {
    if(((color<1||color>13)&&color!=TemperanceCard)||!seed||pillPickups.size()>=1024||dead||finished||!std::isfinite(at.x)||!std::isfinite(at.y)||!std::isfinite(at.z)||arena.blocked(at,.35f))return false;
    const int owner=arena.roomAt(at);if(owner<0)return false;
    PillPickup p;p.position=at;p.room=owner;p.color=color;p.seed=seed;p.timing.card=color==TemperanceCard;if(!idle)p.timing.appear(color==TemperanceCard);pillPickups.push_back(p);checkpointNeeded=true;return true;
}
void Simulation::deliverPursePills() {
    std::erase_if(pendingPursePills,[&](const PendingPursePill &p){
        if(p.room!=room||pillPickups.size()>=1024)return false;
        const auto safe=[&](Vector3 at){
            if(arena.roomAt(at)!=room||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.5f)||arena.path(player.position,at,.48f).empty())return false;
            for(int id:arena.rooms[size_t(room)].passages)for(const auto &gate:arena.passages[size_t(id)].gates)if(sphereBox(at,.5f,gate))return false;
            for(const auto &other:pillPickups)if(other.room==room&&other.timing.phase!=PillTiming::Phase::Gone&&planarDistance(other.position,at)<1.2f)return false;
            return true;
        };
        for(int ring=0;ring<5;++ring)for(int step=0;step<16;++step){
            const float a=p.ordinal*Pi/2+step*Pi/8;auto at=add(p.origin,{std::cos(a)*(1.8f+ring*.7f),0,std::sin(a)*(1.8f+ring*.7f)});at.y=.85f;
            if(safe(at)&&spawnPill(at,p.color,p.seed))return true;
        }
        return false;
    });
}
int Simulation::resolvedPillEffect(int color) const {
    const int effect=pills.effect(color);
    return effect==6&&player.maxHp<=2?7:effect; // Original ordinary red-health character safety gate.
}
std::string Simulation::heldPillName() const {
    if(!pills.held)return "EMPTY CONSUMABLE SLOT";
    if(pills.held==TemperanceCard)return "XIV / TEMPERANCE";
    return pills.known(pills.held)?pillEffectName(resolvedPillEffect(pills.held)):"UNKNOWN PILL";
}
bool Simulation::usePill() {
    if(!pills.held||dead||finished||player.totalHealth()<=0||rewardOpen||shopOpen||letterOpen||storyOpen!=StoryRoom::None||floorExitRequested)return false;
    if(pills.held==TemperanceCard)return useTemperance();
    const int effect=resolvedPillEffect(pills.held);if(effect<0)return false;
    auto health=player.sourceHealth();
    switch(effect){case 2:health.addSoul(4);break;case 5:health.addRed(health.redCapacity());break;case 6:health.addMaxRed(-2);break;case 7:health.addMaxRed(2);break;default:break;}
    applyPlayerHealth(std::move(health));pills.identified[size_t(pills.held-1)]=true;
    ++pills.consumed[size_t(effect)];pills.held=0;
    audioCues.push(AudioCueKind::Pickup,player.position);announce(std::string(pillEffectName(effect))+" / PILL USED",3);checkpointNeeded=true;return true;
}
bool Simulation::dropPill() {
    if(!pills.held||dead||finished||player.totalHealth()<=0||rewardOpen||shopOpen||letterOpen||storyOpen!=StoryRoom::None||floorExitRequested)return false;
    if(!spawnPill(player.position,pills.held,1))return false;
    pillPickups.back().contactBlocked=true;pills.held=0;checkpointNeeded=true;announce("CONSUMABLE DROPPED / WALK AWAY TO PICK IT UP AGAIN",2);return true;
}
void Simulation::updatePills(float dt) {
    deliverPursePills();bool admitted=false;
    std::erase_if(pillPickups,[&](PillPickup &p){
        if(p.room!=room)return false;
        p.timing.advance(dt);
        if(p.timing.phase==PillTiming::Phase::Gone)return true;
        const bool touching=planarDistance(player.position,p.position)<1;
        if(!touching){p.contactBlocked=false;return false;}
        if(p.contactBlocked||admitted||!p.timing.collectible()||dead||player.totalHealth()<=0||!arena.clear(player.position,p.position,.1f))return false;
        if(p.shopStock){
            const int price=shopPrice(bloodMachineTuning.cardPrice,shopCardSlot);
            if(shopCardSold||money()<uint64_t(price)||!roomClear||roomThreats())return false;
            moneySpent+=uint64_t(price);shopCardSold=true;p.shopStock=false;
        }
        const int previous=pills.held;pills.held=p.color;admitted=true;
        if(previous){p.color=previous;p.contactBlocked=true;p.timing.appear(previous==TemperanceCard);}else p.timing.collect();
        audioCues.push(AudioCueKind::Pickup,p.position);announce(heldPillName()+" / "+pillTuning.useKey()+" USE / "+pillTuning.dropKey()+" DROP",3);checkpointNeeded=true;return false;
    });
    if(admitted)for(auto &p:pillPickups)if(p.room==room&&planarDistance(player.position,p.position)<1)p.contactBlocked=true;
}
}
