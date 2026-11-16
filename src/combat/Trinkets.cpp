#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::spawnTrinket(Vector3 at,const ItemKey &item,uint32_t seed,bool preplaced) {
    if(item!=CancerKey||!content->item(item)||dead||finished||!seed||trinketPickups.size()>=1024||
       !std::isfinite(at.x)||!std::isfinite(at.y)||!std::isfinite(at.z)||arena.blocked(at,.35f))return false;
    const int owner=arena.roomAt(at);if(owner<0)return false;
    TrinketPickup pickup;pickup.position=at;pickup.room=owner;pickup.item=item;pickup.seed=seed;
    if(!preplaced)pickup.timing.appear();
    trinketPickups.push_back(pickup);checkpointNeeded=true;return true;
}
bool Simulation::dropTrinket() {
    if(!heldTrinket||dead||finished||player.totalHealth()<=0||rewardOpen||shopOpen||letterOpen||
       storyOpen!=StoryRoom::None||floorExitRequested||trinketPickups.size()>=1024)return false;
    const auto &layout=arena.rooms[size_t(room)];
    const auto safe=[&](Vector3 at) {
        if(arena.roomAt(at)!=room||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.5f))return false;
        for(int index:layout.passages)for(const auto &gate:arena.passages[size_t(index)].gates)
            if(sphereBox(at,.5f,gate))return false;
        for(const auto &p:trinketPickups)if(p.room==room&&p.timing.collectible()&&planarDistance(p.position,at)<.7f)return false;
        return !arena.path(player.position,at,.48f).empty();
    };
    Vector3 point=player.position;float best=safe(point)?0:std::numeric_limits<float>::infinity();
    if(best!=0)for(const auto &cell:arena.floorCells) {
        const Vector3 at{(cell.first+.5f)*FloorTile,.85f,(cell.second+.5f)*FloorTile};
        const float score=planarDistance(at,player.position);
        if(score<best&&safe(at)){point=at;best=score;}
    }
    if(!std::isfinite(best)||!spawnTrinket(point,*heldTrinket,1))return false;
    trinketPickups.back().contactBlocked=true;heldTrinket.reset();
    announce("TRINKET DROPPED / walk away to collect again",2);checkpointNeeded=true;return true;
}
void Simulation::updateTrinkets(float dt) {
    bool admitted=false; // At most one slot change per simulation step.
    std::erase_if(trinketPickups,[&](TrinketPickup &p) {
        if(p.room!=room)return false;
        p.timing.advance(dt);
        if(p.timing.phase==TrinketTiming::Phase::Gone)return true;
        const bool touching=planarDistance(player.position,p.position)<1;
        if(!touching){p.contactBlocked=false;return false;}
        if(p.contactBlocked||admitted||!p.timing.collectible()||dead||player.totalHealth()<=0||
           !arena.clear(player.position,p.position,.1f))return false;
        const auto outgoing=heldTrinket;heldTrinket=p.item;admitted=true;
        if(outgoing) {
            p.item=*outgoing;p.contactBlocked=true;p.timing.appear();
        } else p.timing.collect();
        audioCues.push(AudioCueKind::Pickup,p.position);announce("CANCER / TEARS UP / TRINKET",3);
        checkpointNeeded=true;return false;
    });
    // Block all overlapping actors until the player leaves their contact area.
    if(admitted)for(auto &p:trinketPickups)if(p.room==room&&planarDistance(player.position,p.position)<1)p.contactBlocked=true;
}
} // namespace dw
