#include "world/SourceFullFlyRoom.hpp"
#include "world/SourcePropRooms.hpp"
#include "world/Dungeon.hpp"
#include "world/DungGeometry.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include "world/SourceRoomSelection.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceHeartRockRoomData.hpp"
#include "world/SourceCombatRockRooms.hpp"
#include "world/SourceChestRockRoomData.hpp"
#include "world/SourceCoinRockRoomData.hpp"
#include "world/SourceKeyRockRoomData.hpp"
#include "world/SourceBombRockRoomData.hpp"
#include "combat/SourceRoomRewards.hpp"
#include <span>
#include <stdexcept>
namespace dw {
namespace {
Vector3 heartCell(const RoomLayout &layout,int x,int y) {
    return sourceHeartCell(layout,x,y);
}
}
void Arena::prepareRoomHeartLayouts(uint64_t seed,int mode,int propLayouts) {
    if(mode<0||mode>2)throw std::invalid_argument("Invalid room-heart layout mode");
    if((!mode&&propLayouts!=2)||profile.floor!=0||!profile.active()||theme!=MissionTheme::Canyon)return;
    std::vector<int> eligible;
    for(int i=1;i<roomCount()-1;++i) {
        const auto &layout=rooms[size_t(i)];
        if(!layout.vacantServiceSite&&(layout.kind==RoomKind::Combat||layout.kind==RoomKind::Empty)&&layout.story==StoryRoom::None&&
           layout.sourceCombatTemplate<0)eligible.push_back(i);
    }
    std::stable_sort(eligible.begin(),eligible.end(),[&](int a,int b){return rooms[size_t(a)].depth<rooms[size_t(b)].depth;});
    std::vector<float> weights;weights.reserve(BasementHeartLayouts.size());
    for(const auto &source:BasementHeartLayouts)weights.push_back(source.weight);
    for(int index:eligible) {
        if(!mode)break;
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
            const bool completeChest=selected.variant==SourceChestRockRoom&&index!=2&&index!=3&&
                std::none_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;});
            const bool completeCoins=selected.variant==SourceCoinRockRoom&&index!=2&&index!=3&&
                std::none_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;});
            const bool completeKeys=selected.variant==SourceKeyRockRoom&&index!=2&&index!=3&&
                std::none_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;});
            const bool completeBombs=selected.variant==SourceBombRockRoom&&index!=2&&index!=3&&
                std::none_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;});
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
                if(completeChest&&ordinal==Basement31ChestOrdinal) {
                    const auto cell=Basement31ChestCell;
                    layout.chestSpawns.push_back({heartCell(layout,cell[0],cell[1]),spawnState,cell[0],cell[1],ordinal});
                }
                if(completeCoins)for(const auto &slot:Basement30Coins)if(slot.ordinal==ordinal) {
                    const int subtype=slot.subtype==0?sourceOrdinaryPickup(spawnState,20,{}).subtype:slot.subtype;
                    layout.coinSpawns.push_back({heartCell(layout,slot.x,slot.y),spawnState,slot.x,slot.y,ordinal,slot.subtype,subtype});
                }
                if(completeKeys)for(const auto &slot:Basement214Keys)if(slot.ordinal==ordinal) {
                    const int subtype=slot.subtype==0?sourceOrdinaryPickup(spawnState,30,{}).subtype:slot.subtype;
                    layout.keySpawns.push_back({heartCell(layout,slot.x,slot.y),spawnState,slot.x,slot.y,ordinal,slot.subtype,subtype});
                }
                if(completeBombs)for(const auto &slot:Basement32Bombs)if(slot.ordinal==ordinal) {
                    const int subtype=slot.subtype==0?sourceOrdinaryPickup(spawnState,40,{}).subtype:slot.subtype;
                    layout.bombSpawns.push_back({heartCell(layout,slot.x,slot.y),spawnState,slot.x,slot.y,ordinal,slot.subtype,subtype});
                }
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
            if(completeChest) {
                layout.sourceObstacleTemplate=SourceChestRockRoom;
                layout.kind=RoomKind::Empty;
            }
            if(completeKeys) {
                layout.sourceObstacleTemplate=SourceKeyRockRoom;
                layout.kind=RoomKind::Empty;
            }
            if(completeBombs) {
                layout.sourceObstacleTemplate=SourceBombRockRoom;
                layout.kind=RoomKind::Empty;
            }
            if(completeCoins) {
                layout.sourceObstacleTemplate=SourceCoinRockRoom;
                layout.kind=RoomKind::Empty;
            }
        }
        if(mode==1&&layout.sourceHeartTemplate==91) {
            layout.sourceObstacleTemplate=91;
            // The source record contains only rocks and pickups, no enemies.
            layout.kind=RoomKind::Empty;
        }
        if(mode==1&&sourceCombatRockRoom(layout.sourceHeartTemplate)&&index!=2&&index!=3&&
           std::none_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;})) {
            // Complete selected Gaper/rock record. Legacy miners/altar
            // rooms and mandatory key sites retain their existing composition;
            // their selected metadata and RNG sequence are never rerolled.
            layout.sourceCombatTemplate=layout.sourceObstacleTemplate=layout.sourceHeartTemplate;
            layout.kind=RoomKind::Combat;
        }
        if(mode==1&&propLayouts&&sourcePropRoom(layout.sourceHeartTemplate)&&index!=2&&index!=3&&
           std::none_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;})) {
            layout.sourceCombatTemplate=layout.sourceObstacleTemplate=layout.sourceHeartTemplate;
            layout.kind=layout.sourceHeartTemplate==26?RoomKind::Empty:RoomKind::Combat;
        }
        if(mode==2)break;
    }
    // D14a.2 bounded recorded encounter allocation. Source704 is shape5,
    // outside the13x7 native-selection pool. Do not falsify its shape or add
    // a second source selection roll. Preserve all already complete rooms.
    if(mode==1&&propLayouts!=2)for(auto it=eligible.rbegin();it!=eligible.rend();++it) {
        const int index=*it;auto &layout=rooms[size_t(index)];
        if(index==2||index==3||layout.sourceCombatTemplate>=0||layout.sourceObstacleTemplate>=0||
           !layout.heartSpawns.empty()||std::any_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;}))continue;
        layout.sourceHeartTemplate=layout.sourceCombatTemplate=layout.sourceObstacleTemplate=FullFlyRoomTemplate;
        layout.kind=RoomKind::Combat;
        // The fixed content layer uses its own reproducible DW descriptor seed.
        Random allocation(seed^0x46554c4c464c5900ULL^uint64_t(index));
        layout.sourceRoomSelectionSeed=uint32_t(allocation.next());
        if(!layout.sourceRoomSelectionSeed)layout.sourceRoomSelectionSeed=1;
        layout.sourceRoomSpawnSeed=sourceRoomDescriptorSeeds(layout.sourceRoomSelectionSeed).spawn;
        break;
    }
    if(propLayouts==2)for(int index:eligible) {
        if(index==2||index==3||std::any_of(keys.begin(),keys.end(),[&](const auto &key){return key.room==index;}))continue;
        auto &layout=rooms[size_t(index)];
        layout.sourceHeartTemplate=layout.sourceCombatTemplate=layout.sourceObstacleTemplate=PropReviewRoom;
        layout.kind=RoomKind::Empty;
        layout.heartSpawns.clear();layout.chestSpawns.clear();layout.coinSpawns.clear();layout.keySpawns.clear();layout.bombSpawns.clear();
        if(!layout.sourceRoomSpawnSeed)layout.sourceRoomSpawnSeed=uint32_t(seed)^uint32_t(index+1)*2654435761u;
        if(!layout.sourceRoomSpawnSeed)layout.sourceRoomSpawnSeed=1;
        break;
    }
}
void Arena::prepareSourceHeartRocks() {
    for(int index=0;index<roomCount();++index) {
        const auto &layout=rooms[size_t(index)];
        if(const auto *source=sourcePropRoom(layout.sourceObstacleTemplate)) {
            const float half=sourceHeartCellSize(layout)*.5f;
            for(const auto &slot:source->entries)if(slot.type==1000||slot.type==1500) {
                const auto at=sourceHeartCell(layout,slot.x,slot.y);
                Breakable prop;prop.room=index;prop.kind=slot.type==1500?BreakableKind::Dung:BreakableKind::CrackedRock;
                prop.sourceGridIndex=(slot.y+1)*15+slot.x+1;
                prop.id=0x535243000000ULL+uint64_t(index)*256+uint64_t(prop.sourceGridIndex);
                prop.bounds={{at.x-half,0,at.z-half},{at.x+half,slot.type==1500?1.1f:1.35f,at.z+half}};
                if(prop.kind==BreakableKind::Dung)prop.bounds=dungBounds(prop.bounds);
                prop.rewardPosition=at;prop.paid=slot.type!=1500;
                prop.health=prop.initialHealth=slot.type==1500?4:1;
                prop.lootSeed=propSlotSeed(layout.sourceRoomSpawnSeed,slot.ordinal);
                breakables.push_back(prop);
            }
            rebuildWalls();continue;
        }
        std::span<const std::array<int,2>> rocks;
        if(layout.sourceObstacleTemplate==91)rocks=Basement91Rocks;
        else if(layout.sourceObstacleTemplate==SourceChestRockRoom)rocks=Basement31Rocks;
        else if(layout.sourceObstacleTemplate==SourceKeyRockRoom)rocks=Basement214Rocks;
        else if(layout.sourceObstacleTemplate==SourceBombRockRoom)rocks=Basement32Rocks;
        else if(layout.sourceObstacleTemplate==SourceCoinRockRoom)rocks=Basement30Rocks;
        else if(const auto *source=sourceCombatRockRoom(layout.sourceObstacleTemplate))rocks=source->rocks;
        else continue;
        const float half=sourceHeartCellSize(layout)*.5f;
        for(const auto &cell:rocks) {
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
