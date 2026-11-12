#include "combat/Simulation.hpp"

namespace dw {
void Simulation::prepareRoomHearts() {
    for(int index=0;index<arena.roomCount();++index) {
        rooms[size_t(index)].roomHeartsDelivered.resize(arena.rooms[size_t(index)].heartSpawns.size(),false);
        deliverRoomHearts(index);
    }
}
void Simulation::deliverRoomHearts(int index) {
    const auto &layout=arena.rooms[size_t(index)];auto &delivered=rooms[size_t(index)].roomHeartsDelivered;
    if(layout.heartSpawns.empty()||dead||finished||heartPickups.size()>=1024)return;
    bool pending=false;
    for(size_t i=0;i<layout.heartSpawns.size();++i)if(!delivered[i]&&(layout.heartSpawns[i].subtype==1||layout.heartSpawns[i].subtype==2)){pending=true;break;}
    if(!pending)return;
    if(layout.sourceObstacleTemplate==91) {
        for(size_t i=0;i<layout.heartSpawns.size()&&heartPickups.size()<1024;++i) {
            const auto &spawn=layout.heartSpawns[i];
            if(delivered[i]||(spawn.subtype!=1&&spawn.subtype!=2))continue;
            // Deliberately unreachable until its surrounding rocks are opened.
            // Capacity/collision delays retain this exact position and identity.
            if(!spawnHeartPickup(HeartKind::Red,spawn.preferred,spawn.subtype==1?2:1))continue;
            auto &pickup=heartPickups.back();pickup.sourceSubtype=spawn.subtype;pickup.placedInLayout=true;
            delivered[i]=true;checkpointNeeded=true;
        }
        return;
    }
    const auto basicSafe=[&](Vector3 at) {
        if(arena.roomAt(at)!=index||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.6f))return false;
        for(int p:layout.passages)for(const auto &gate:arena.passages[size_t(p)].gates)
            if(sphereBox(at,.7f,gate))return false;
        return true;
    };
    std::vector<Vector3> candidates;
    for(const auto &cell:arena.floorCells) {
        const Vector3 at{(cell.first+.5f)*FloorTile,layout.center.y,(cell.second+.5f)*FloorTile};
        if(basicSafe(at))candidates.push_back(at);
    }
    if(candidates.empty())return;
    const auto anchor=*std::min_element(candidates.begin(),candidates.end(),[&](Vector3 a,Vector3 b){
        return planarDistance(a,layout.entry)<planarDistance(b,layout.entry);
    });
    for(size_t i=0;i<layout.heartSpawns.size()&&heartPickups.size()<1024;++i) {
        const auto &spawn=layout.heartSpawns[i];
        if(delivered[i]||(spawn.subtype!=1&&spawn.subtype!=2))continue;
        auto safe=[&](Vector3 at) {
            if(!basicSafe(at))return false;
            for(const auto &pickup:heartPickups)if(pickup.room==index&&planarDistance(at,pickup.position)<1.25f)return false;
            for(const auto &key:arena.keys)if(key.room==index&&planarDistance(at,key.position)<1.25f)return false;
            return !arena.path(anchor,at,.48f).empty();
        };
        auto position=spawn.preferred;bool found=safe(position);
        if(!found) {
            std::stable_sort(candidates.begin(),candidates.end(),[&](Vector3 a,Vector3 b){
                return planarDistance(a,spawn.preferred)<planarDistance(b,spawn.preferred);
            });
            for(auto at:candidates)if(safe(at)){position=at;found=true;break;}
        }
        if(!found||!spawnHeartPickup(HeartKind::Red,position,spawn.subtype==1?2:1))continue;
        auto &pickup=heartPickups.back();pickup.sourceSubtype=spawn.subtype;pickup.placedInLayout=true;
        // Placed pickups are already idle/collectible on entry, independent of
        // the appearance-speed setting for newly emitted clear rewards.
        delivered[i]=true;checkpointNeeded=true;
    }
}
} // namespace dw
