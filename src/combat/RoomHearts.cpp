#include "combat/Simulation.hpp"
#include "combat/SourceRoomRewards.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include <stdexcept>

namespace dw {
namespace {
// A separate DW seed stream selects a source heart layer. This does not claim
// native floor-template selection, descriptor RNG or complete encounter parity.
template<class Rows> const auto &weighted(const Rows &rows,int begin,int count,Random &rng) {
    float total=0;for(int i=0;i<count;++i)total+=rows[size_t(begin+i)].weight;
    float roll=rng.real(0,total);
    for(int i=0;i<count-1;++i) {roll-=rows[size_t(begin+i)].weight;if(roll<0)return rows[size_t(begin+i)];}
    return rows[size_t(begin+count-1)];
}
Vector3 heartCell(const RoomLayout &layout,int x,int y) {
    const auto size=sub(layout.bounds.max,layout.bounds.min);
    const float cell=std::min(size.x*.86f/13,size.z*.86f/7);
    return add(layout.center,{(x-6)*cell,0,(y-3)*cell});
}
}
void Simulation::prepareRoomHearts() {
    if(roomHeartLayouts<0||roomHeartLayouts>2)throw std::invalid_argument("Invalid room-heart layout mode");
    if(!roomHeartLayouts||floor!=0||surveyTutorial||!arena.profile.active()||arena.theme!=MissionTheme::Canyon)return;
    std::vector<int> eligible;
    for(int i=1;i<finalRoom();++i) {
        const auto &layout=arena.rooms[size_t(i)];const auto &progress=rooms[size_t(i)];
        if((layout.kind==RoomKind::Combat||layout.kind==RoomKind::Empty)&&layout.story==StoryRoom::None&&
           layout.sourceCombatTemplate<0&&!progress.plateObjective&&!progress.trapOnly)eligible.push_back(i);
    }
    std::stable_sort(eligible.begin(),eligible.end(),[&](int a,int b){return arena.rooms[size_t(a)].depth<arena.rooms[size_t(b)].depth;});
    for(int index:eligible) {
        auto &layout=arena.rooms[size_t(index)];
        Random rng(seed_^0x524f4f4d48454152ULL^(uint64_t(index+1)*0x9e3779b97f4a7c15ULL));
        auto append=[&](int x,int y,int sourceSubtype,int subtype,uint32_t seed) {
            layout.heartSpawns.push_back({heartCell(layout,x,y),seed,x,y,sourceSubtype,subtype});
        };
        if(roomHeartLayouts==2) {
            // Explicit testing override: pair coordinates from 1.215.0, fixed
            // full/half instead of source subtype0 resolution. No frequency claim.
            layout.sourceHeartTemplate=215;append(5,3,0,1,0);append(7,3,0,2,0);
        } else {
            const auto &selected=weighted(BasementHeartLayouts,0,int(BasementHeartLayouts.size()),rng);
            layout.sourceHeartTemplate=selected.variant;
            for(int n=0;n<selected.slotCount;++n) {
                const auto &slot=BasementHeartSlots[size_t(selected.firstSlot+n)];
                const auto &choice=weighted(BasementHeartChoices,slot.firstChoice,slot.choiceCount,rng);
                if(choice.type!=5||choice.variant!=10)continue;
                uint32_t seed=uint32_t(rng.next());if(!seed)seed=1;
                const int subtype=choice.subtype==0?sourceOrdinaryPickup(seed,10,{}).subtype:choice.subtype;
                // Retain unsupported outcomes in the layout for inspection;
                // only selected full/half red actors are admitted below.
                append(slot.x,slot.y,choice.subtype,subtype,seed);
            }
        }
        rooms[size_t(index)].roomHeartsDelivered.resize(layout.heartSpawns.size(),false);
        deliverRoomHearts(index); // Already present before the first room entry.
        if(roomHeartLayouts==2)break;
    }
}
void Simulation::deliverRoomHearts(int index) {
    const auto &layout=arena.rooms[size_t(index)];auto &delivered=rooms[size_t(index)].roomHeartsDelivered;
    if(layout.heartSpawns.empty()||dead||finished||heartPickups.size()>=1024)return;
    bool pending=false;
    for(size_t i=0;i<layout.heartSpawns.size();++i)if(!delivered[i]&&(layout.heartSpawns[i].subtype==1||layout.heartSpawns[i].subtype==2)){pending=true;break;}
    if(!pending)return;
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
