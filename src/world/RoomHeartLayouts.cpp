#include "world/Dungeon.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include "world/SourceRoomSelection.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceHeartRockRoomData.hpp"
#include "combat/SourceRoomRewards.hpp"
#include <stdexcept>
namespace dw {
namespace {
Vector3 heartCell(const RoomLayout &layout,int x,int y) {
    return sourceHeartCell(layout,x,y);
}
}
void Arena::prepareRoomHeartLayouts(uint64_t seed,int mode) {
    if(mode<0||mode>2)throw std::invalid_argument("Invalid room-heart layout mode");
    if(!mode||profile.floor!=0||!profile.active()||theme!=MissionTheme::Canyon)return;
    std::vector<int> eligible;
    for(int i=1;i<roomCount()-1;++i) {
        const auto &layout=rooms[size_t(i)];
        if((layout.kind==RoomKind::Combat||layout.kind==RoomKind::Empty)&&layout.story==StoryRoom::None&&
           layout.sourceCombatTemplate<0)eligible.push_back(i);
    }
    std::stable_sort(eligible.begin(),eligible.end(),[&](int a,int b){return rooms[size_t(a)].depth<rooms[size_t(b)].depth;});
    std::vector<float> weights;weights.reserve(BasementHeartLayouts.size());
    for(const auto &source:BasementHeartLayouts)weights.push_back(source.weight);
    for(int index:eligible) {
        auto &layout=rooms[size_t(index)];
        Random rng(seed^0x524f4f4d48454152ULL^(uint64_t(index+1)*0x9e3779b97f4a7c15ULL));
        auto append=[&](int x,int y,int sourceSubtype,int subtype,uint32_t seed) {
            layout.heartSpawns.push_back({heartCell(layout,x,y),seed,x,y,sourceSubtype,subtype});
        };
        if(mode==2) {
            // Explicit testing override: pair coordinates from 1.215.0, fixed
            // full/half instead of source subtype0 resolution. No frequency claim.
            layout.sourceHeartTemplate=215;append(5,3,0,1,0);append(7,3,0,2,0);
        } else {
            auto query=sourceBasementFirstFloorQuery(0);
            for(int p:layout.passages) {
                const auto &passage=passages[size_t(p)];
                const int other=passage.rooms[passage.rooms[0]==index?1:0];
                const auto direction=sub(rooms[size_t(other)].center,layout.center);
                // Explicit canyon-to-source axis adapter; geometry is retained.
                const int door=std::abs(direction.x)>std::abs(direction.z)?(direction.x<0?0:2):(direction.z<0?1:3);
                query.doors|=1<<door;
            }
            uint32_t selectionSeed=uint32_t(rng.next());if(!selectionSeed)selectionSeed=1;
            const int selectedIndex=sourceRoomSelect(BasementHeartLayouts,weights,query,selectionSeed);
            if(selectedIndex<0)continue; // No compatible template: never reroll into hearts.
            const auto &selected=BasementHeartLayouts[size_t(selectedIndex)];
            layout.sourceHeartTemplate=selected.variant;
            layout.sourceRoomSelectionSeed=selectionSeed;
            layout.sourceRoomSpawnSeed=sourceRoomDescriptorSeeds(selectionSeed).spawn;
            // Native Room::Init advances once for EVERY source spawn stack,
            // including omitted obstacles/enemies. Native InitSeeds derives the
            // spawn seed from the SAME seed passed to room selection, not the
            // selector's local RNG endpoint or a second independent DW draw.
            // The initial selection seed and floor order remain DW adapters.
            uint32_t spawnState=layout.sourceRoomSpawnSeed;
            int nextSlot=0;
            for(int ordinal=0;ordinal<selected.spawnCount;++ordinal) {
                const float unit=sourceRoomSpawnRandom(spawnState);
                if(nextSlot>=selected.slotCount)continue;
                const auto &slot=BasementHeartSlots[size_t(selected.firstSlot+nextSlot)];
                if(slot.ordinal!=ordinal)continue;
                ++nextSlot;
                const int choiceIndex=sourceRoomSpawnChoice(BasementHeartChoices,slot.firstChoice,slot.choiceCount,unit);
                if(choiceIndex<0)continue;
                const auto &choice=BasementHeartChoices[size_t(choiceIndex)];
                if(choice.type!=5||choice.variant!=10)continue;
                const uint32_t seed=spawnState;
                const int subtype=choice.subtype==0?sourceOrdinaryPickup(seed,10,{}).subtype:choice.subtype;
                // Retain unsupported outcomes in the layout for inspection;
                // only selected full/half red actors are admitted below.
                append(slot.x,slot.y,choice.subtype,subtype,seed);
            }
        }
        if(mode==1&&layout.sourceHeartTemplate==91) {
            layout.sourceObstacleTemplate=91;
            // The source record contains only rocks and pickups, no enemies.
            layout.kind=RoomKind::Empty;
        }
        if(mode==2)break;
    }
}
void Arena::prepareSourceHeartRocks() {
    for(int index=0;index<roomCount();++index) {
        const auto &layout=rooms[size_t(index)];if(layout.sourceObstacleTemplate!=91)continue;
        const float half=sourceHeartCellSize(layout)*.5f;
        for(const auto &cell:Basement91Rocks) {
            const auto at=sourceHeartCell(layout,cell[0],cell[1]);
            Breakable rock;rock.room=index;rock.kind=BreakableKind::CrackedRock;
            rock.sourceGridIndex=(cell[1]+1)*15+cell[0]+1;
            rock.id=0x535243000000ULL+uint64_t(index)*256+uint64_t(rock.sourceGridIndex);
            rock.bounds={{at.x-half,0,at.z-half},{at.x+half,1.35f,at.z+half}};
            rock.rewardPosition=at;rock.paid=true; // No unrelated custom rock-coin producer.
            breakables.push_back(rock);
        }
        rebuildWalls();
        // Mandatory DW keys are not part of this source record. Keep them on
        // an accessible floor tile outside its enclosed optional pickups.
        for(auto &key:keys)if(key.room==index&&(blocked(key.position,.48f)||path(layout.entry,key.position,.48f).empty())) {
            float best=std::numeric_limits<float>::infinity();Vector3 selected=layout.entry;
            for(const auto &tile:floorCells) {
                const Vector3 at{(tile.first+.5f)*FloorTile,.85f,(tile.second+.5f)*FloorTile};
                const float score=planarDistance(at,layout.entry);
                if(score<best&&roomAt(at)==index&&!blocked(at,.6f)&&!path(layout.entry,at,.48f).empty()) {best=score;selected=at;}
            }
            key.position=selected;
        }
    }
}
} // namespace dw
