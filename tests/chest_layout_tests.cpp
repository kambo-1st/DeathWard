#include "combat/Simulation.hpp"
#include "combat/ChestGeometry.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceChestRockRoomData.hpp"
#include "world/SourceRoomSelection.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,float size=1.1f,int lo=7,int hi=9,int mode=1,int floor=0) {
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,
                 defaultMechanics(),size,lo,hi,.26f,true,mode,true);
    r.chestClearRewards=false;r.redHeartAppearanceSpeed=2;r.godMode=true;return r;
}
int owner(const Simulation &r) {
    for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==31)return i;
    return -1;
}
void advance(Simulation &r,int frames) {for(int n=0;n<frames;++n)r.step({});}
void verify(uint64_t seed,float size,int lo,int hi,bool lifecycle) {
    auto r=create(seed,size,lo,hi);const int index=owner(r);
    check(index>=0,"natural chest room selected");const auto layout=r.arena.rooms[size_t(index)];
    const std::string tag=" seed="+std::to_string(seed)+" size="+std::to_string(size)+" range="+std::to_string(lo)+","+std::to_string(hi);
    check(index!=2&&index!=3&&layout.kind==RoomKind::Empty&&layout.story==StoryRoom::None&&r.roomEnemies(index).empty(),"compatible complete empty room"+tag);
    check(layout.chestSpawns.size()==1&&layout.heartSpawns.empty(),"one source chest and no extra pickups"+tag);
    const auto slot=layout.chestSpawns[0];uint32_t state=sourceRoomDescriptorSeeds(layout.sourceRoomSelectionSeed).spawn;
    for(int i=0;i<=6;++i)sourceRoomSpawnRandom(state);
    check(slot.ordinal==6&&slot.x==6&&slot.y==3&&slot.pickupSeed==state,"exact descriptor and seventh spawn-state seed"+tag);
    check(r.arena.supplyCache.room!=index&&layout.obstacles.empty(),"no unrelated cache/outcrop"+tag);
    int rocks=0;for(const auto &b:r.arena.breakables)if(b.room==index){++rocks;check(b.sourceGridIndex>=0&&b.paid&&!b.destroyed,"only intact source plain rocks"+tag);}
    check(rocks==12,"all twelve enclosing rocks"+tag);
    for(const auto &p:r.moneyPickups)check(r.arena.roomAt(p.position)!=index,"no legacy coin piles"+tag);
    check(r.enterSourceRoomReview(31)&&r.room==index,"direct review enters complete arrangement"+tag);
    check(r.chests.size()==1&&r.chests[0].placedInLayout&&!r.chests[0].opened&&r.chests[0].age==.8f&&r.chests[0].heartAppearanceSpeed==2,"preplaced closed chest ready at entry with applied appearance setting"+tag);
    const auto at=r.chests[0].position;
    check(planarDistance(at,slot.preferred)<.001f&&r.chests[0].seed==slot.pickupSeed&&r.arena.blocked(at,.48f),"exact source placement and immediate solid body"+tag);
    check(r.roomClear&&!r.rooms[size_t(index)].redHeartAward,"empty room does not roll combat award"+tag);
    for(int p:layout.passages) {
        auto to=r.arena.doorApproach(p,r.arena.passages[size_t(p)].rooms[0]==index?0:1);
        check(!r.arena.path(layout.entry,to,.48f).empty(),"existing passage access"+tag);
    }
    Input click;click.moveTarget=at;r.step(click);advance(r,120);
    check(!r.chests[0].opened,"cannot open through intact enclosure"+tag);
    for(auto edge:{Vector3{chestGeometry::StopX+.04f,0,0},Vector3{-chestGeometry::StopX-.04f,0,0},Vector3{0,0,chestGeometry::StopZ+.04f},Vector3{0,0,-chestGeometry::StopZ-.04f}})
        check(r.arena.path(layout.entry,add(at,edge),.48f).empty(),"enclosure keeps all chest approaches inaccessible"+tag);
    r.player.position=sourceHeartCell(layout,3,3);r.player.velocity={};
    check(!r.arena.blocked(r.player.position,.48f)&&!r.arena.path(layout.entry,r.player.position,.48f).empty(),"accessible demolition approach"+tag);
    Input fire;fire.fire=true;fire.aim=at;for(int n=0;n<90;++n)r.step(fire);
    check(std::none_of(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==index&&b.destroyed;}),"ordinary shots do not remove rocks"+tag);
    check(r.placeDynamite(),"uses ordinary inventory dynamite"+tag);advance(r,240);
    check(r.dynamite==StartingDynamite-1,"demolition spends one dynamite"+tag);
    const auto destroyed=std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==index&&b.destroyed;});
    check(destroyed>0,"real blast opens source enclosure"+tag);
    r.step(click);advance(r,300);
    check(r.chests[0].opened&&!r.arena.blocked(r.player.position,.48f),"ordinary click enters breach and opens from legal edge"+tag);
    check(std::all_of(r.chests[0].contents.begin(),r.chests[0].contents.end(),[](const auto &d){return d.delivered;}),"fixed contents scatter after opening"+tag);
    check(r.arena.blocked(at,.48f),"opened chest retains collision"+tag);
    for(const auto &p:r.moneyPickups)if(p.room==index)check(!r.arena.path(r.player.position,p.position,.48f).empty(),"coins reachable after demolition"+tag);
    for(const auto &p:r.heartPickups)if(p.room==index)check(!r.arena.path(r.player.position,p.position,.48f).empty(),"hearts reachable after demolition"+tag);
    for(const auto &p:r.bombPickups)if(p.room==index)check(!r.arena.path(r.player.position,p.position,.48f).empty(),"supplies reachable after demolition"+tag);
    const auto count=r.chests.size(),coins=r.moneyPickups.size(),hearts=r.heartPickups.size(),supplies=r.bombPickups.size();
    const auto cleared=r.stats.rooms;r.jumpDebug(0);r.jumpDebug(index);advance(r,120);
    check(r.chests.size()==count&&r.chests[0].opened&&r.chests[0].seed==state,"revisit retains chest identity and open state"+tag);
    check(r.moneyPickups.size()==coins&&r.heartPickups.size()==hearts&&r.bombPickups.size()==supplies&&r.stats.rooms==cleared,"no duplicate loot or clear"+tag);
    if(lifecycle) {
        const auto id=r.summary().id;r.player.hp=4;r.player.attributes.speed=.8f;
        r.resizeRooms(size,lo,hi,.26f,std::nullopt,0);
        check(r.chests.empty()&&r.arena.rooms[size_t(index)].chestSpawns.empty(),"OFF Apply removes preplaced chest and room contents"+tag);
        r.player.position=at;r.resizeRooms(size,lo,hi,.26f,std::nullopt,1);
        check(r.chests.size()==1&&!r.chests[0].opened&&r.chests[0].placedInLayout&&r.chests[0].heartAppearanceSpeed==2,"SOURCE Apply resets chest and snapshots selected appearance"+tag);
        check(!r.arena.path(r.arena.rooms[size_t(index)].entry,r.player.position,.48f).empty(),"Apply relocates player outside reclosed enclosure"+tag);
        check(r.summary().id==id&&r.player.hp==4&&r.player.attributes.speed==.8f&&!r.chestClearRewards,"Apply retains expedition/player/settings and independent reward switch"+tag);
    }
    std::cout<<"PASS exact source chest/rocks/seed, demolition, click opening, solid body, loot and revisit"<<tag<<'\n';
}
void deferred(uint64_t seed) {
    auto r=create(seed);r.chests.resize(128);check(r.enterSourceRoomReview(31),"capacity fixture direct entry");
    const int index=r.room;const auto slot=r.arena.rooms[size_t(index)].chestSpawns[0];
    check(!r.rooms[size_t(index)].roomChestsDelivered[0],"capacity retains source slot");
    r.chests.clear();r.step({});check(r.chests.size()==1&&r.chests[0].seed==slot.pickupSeed&&r.chests[0].age==.8f,"capacity release admits same preplaced identity without retroactive age");
    r.step({});check(r.chests.size()==1,"slot cannot pay twice");
    auto off=create(seed,1.1f,7,9,0);check(!off.enterSourceRoomReview(31)&&owner(off)<0,"OFF prevents preplaced source chest");
    auto pair=create(seed,1.1f,7,9,2);check(owner(pair)<0&&pair.chests.empty(),"full/half test stays independent");
    auto later=create(seed,1.1f,7,9,1,1);check(owner(later)<0&&later.chests.empty(),"opening-floor scope retained");
    std::cout<<"PASS deferred exact admission, OFF/test/later-floor exclusions\n";
}
int main(int argc,char **argv){try{
    if(argc>1&&std::string(argv[1])=="--find") {
        for(auto [size,lo,hi]:{std::tuple{.75f,5,5},std::tuple{1.5f,10,10}}) {
            for(uint64_t seed=0;seed<10000;++seed) {
                ExpeditionPlan plan(seed,false,WitnessAccount::None,ExpeditionPacing::Compact);
                auto dims=plan.dimensionsOnFloor(0);dims.roomSizeScale=size;dims.routeLengthScale=.26f;dims.smallerRooms=true;dims.minHalfTiles=lo;dims.maxHalfTiles=hi;
                Arena arena(plan.floorSeed(0),MissionTheme::Canyon,true,false,plan.storyAt(0),plan.roomsOnFloor(0),dims,
                    defaultMechanics()->configureFloor(plan.profileOnFloor(0),plan.floorSeed(0)),true,1);
                int index=-1;for(int i=0;i<arena.roomCount();++i)if(arena.rooms[size_t(i)].sourceObstacleTemplate==31)index=i;
                if(index<0)continue;
                std::cout<<"WITNESS seed="<<seed<<" room="<<index+1<<" size="<<size<<" range="<<lo<<','<<hi<<std::endl;break;
            }
        }
        return 0;
    }
    // Natural selector witnesses at the globally smallest/largest supported
    // dimensions and the accepted user preset. Resizing can select other rooms;
    // never force source31 into a seed where the native selector omitted it.
    verify(669,.75f,5,5,false);
    verify(375,1.1f,7,9,true);
    verify(375,1.5f,10,10,false);
    deferred(375);
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
