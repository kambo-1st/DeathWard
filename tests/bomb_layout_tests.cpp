#include "combat/Simulation.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceBombRockRoomData.hpp"
#include "world/SourceRoomSelection.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,float size=1.1f,int lo=7,int hi=9,int mode=1) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
                      defaultMechanics(),size,lo,hi,.26f,true,mode,true);
}
int owner(const Simulation &r){for(int i=1;i<r.finalRoom();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==32)return i;return -1;}
void advance(Simulation &r,int frames){for(int n=0;n<frames;++n)r.step({});}
bool ordinary(const RoomLayout &r){return r.bombSpawns.size()==3&&std::all_of(r.bombSpawns.begin(),r.bombSpawns.end(),[](const auto &p){return sourceOrdinaryBombValue(p.subtype)>0;});}
// Candidate prefilter only: every reported witness is checked in full generation.
bool candidate(uint64_t seed) {
    ExpeditionPlan e(seed,false,WitnessAccount::None,ExpeditionPacing::Compact);
    std::vector<float> initial;for(const auto &r:BasementHeartLayouts)initial.push_back(r.weight);
    for(int i=1;i<9;++i) {
        Random rng(e.floorSeed(0)^0x524f4f4d48454152ULL^(uint64_t(i+1)*0x9e3779b97f4a7c15ULL));
        auto state=uint32_t(rng.next());if(!state)state=1;
        for(int doors=1;doors<16;++doors) {
            auto weights=initial;auto q=sourceBasementFirstFloorQuery(doors);
            const int selected=sourceRoomSelect(BasementHeartLayouts,weights,q,state);
            if(selected>=0&&BasementHeartLayouts[size_t(selected)].variant==32)return true;
        }
    }return false;
}
void verify(uint64_t seed,float size,int lo,int hi) {
    auto r=create(seed,size,lo,hi);const int index=owner(r);const std::string tag=" seed="+std::to_string(seed)+" size="+std::to_string(size);
    check(index>=0,"natural source32"+tag);const auto layout=r.arena.rooms[size_t(index)];
    check(ordinary(layout)&&index!=2&&index!=3&&layout.kind==RoomKind::Empty&&r.roomEnemies(index).empty(),"complete compatible ordinary bomb room"+tag);
    check(layout.heartSpawns.empty()&&layout.coinSpawns.empty()&&layout.keySpawns.empty()&&layout.chestSpawns.empty(),"no unrelated pickup layer"+tag);
    int rocks=0;for(const auto &b:r.arena.breakables)if(b.room==index){++rocks;check(b.paid&&b.sourceGridIndex>=0,"source rocks without custom payout"+tag);}
    check(rocks==34&&layout.obstacles.empty()&&r.arena.supplyCache.room<0,"exact34 rocks and no cache"+tag);
    uint32_t state=sourceRoomDescriptorSeeds(layout.sourceRoomSelectionSeed).spawn;size_t slot=0;
    for(int ordinal=0;ordinal<37;++ordinal) {
        sourceRoomSpawnRandom(state);if(ordinal<17||ordinal>19)continue;
        const auto &p=layout.bombSpawns[slot];const auto &record=Basement32Bombs[slot++];
        check(p.ordinal==ordinal&&p.pickupSeed==state&&p.x==record.x&&p.y==record.y&&p.subtype==sourceOrdinaryPickup(state,40).subtype,"original source slot/seed/subtype"+tag);
        check(planarDistance(p.preferred,sourceHeartCell(layout,p.x,p.y))<.001f,"exact original canyon-adapted cell"+tag);
    }
    check(r.enterSourceRoomReview(32)&&r.roomClear&&r.bombPickups.size()==3&&!r.rooms[size_t(index)].redHeartAward,"direct normal empty-room admission"+tag);
    for(const auto &p:r.bombPickups)check(p.placedInLayout&&p.timing.collectible()&&r.arena.path(layout.entry,p.position,.48f).empty(),"idle preplaced bomb remains enclosed"+tag);
    for(int link:layout.passages)check(!r.arena.path(layout.entry,r.arena.doorApproach(link,r.arena.passages[size_t(link)].rooms[0]==index?0:1),.48f).empty(),"door routes remain free"+tag);
    // Access using real ordinary dynamite; invulnerability only isolates blast
    // geometry here. The actual Game input check must retreat at normal health.
    r.godMode=true;int spent=0;
    for(int row=0;row<=2;++row) {
        if(!r.arena.path(r.player.position,layout.bombSpawns[1].preferred,.48f).empty())break;
        const auto at=sourceHeartCell(layout,6,row);
        check(!r.arena.blocked(at,.48f)&&!r.arena.path(r.player.position,at,.48f).empty(),"demolition approach"+tag);
        r.player.position=at;r.player.velocity={};Input stop;stop.moveTarget=at;r.step(stop);
        check(r.placeDynamite(),"starting supply admits access blast"+tag);++spent;advance(r,240);
    }
    check(!r.arena.path(r.player.position,layout.bombSpawns[1].preferred,.48f).empty(),"starting supply opens bomb pocket"+tag);
    int expected=StartingDynamite-spent;
    for(const auto &p:layout.bombSpawns)expected+=sourceOrdinaryBombValue(p.subtype);
    for(const auto &p:layout.bombSpawns) {
        Input click;click.moveTarget=p.preferred;r.step(click);
        for(int n=0;n<600;++n){r.step({});check(!r.arena.blocked(r.player.position,.48f),"physical click path clearance"+tag);}
    }
    check(r.dynamite==expected&&r.bombPickups.empty(),"collect every ordinary slot once"+tag);
    r.jumpDebug(0);r.jumpDebug(index);advance(r,60);check(r.dynamite==expected&&r.bombPickups.empty(),"revisit cannot repay"+tag);
    const auto identity=r.summary().id;r.player.hp=4;r.resizeRooms(size,lo,hi,.26f,std::nullopt,0);
    check(owner(r)<0&&r.bombPickups.empty(),"OFF Apply removes arrangement"+tag);
    r.player.position=layout.bombSpawns[1].preferred;r.resizeRooms(size,lo,hi,.26f,std::nullopt,1);
    check(r.bombPickups.size()==3&&!r.arena.blocked(r.player.position,.48f)&&!r.arena.path(r.arena.rooms[size_t(index)].entry,r.player.position,.48f).empty(),"Apply restores and rescues from reclosed pocket"+tag);
    check(r.dynamite==expected&&r.player.hp==4&&r.summary().id==identity&&!r.bombClearRewards,"Apply retains inventory/player/expedition/policy"+tag);
    std::cout<<"PASS source32 slots/rocks/real demolition/clicks/revisit/Apply"<<tag<<" spent="<<spent<<'\n';
}
void boundaries() {
    auto r=create(129);const int index=owner(r);check(index>=0,"deferred bomb layout fixture");
    const auto slots=r.arena.rooms[size_t(index)].bombSpawns;
    r.bombPickups.assign(1024,OrdinaryBombPickup{r.arena.rooms[0].center,0});
    check(r.enterSourceRoomReview(32),"deferred direct room entry");
    check(std::none_of(r.rooms[size_t(index)].roomBombsDelivered.begin(),r.rooms[size_t(index)].roomBombsDelivered.end(),[](bool b){return b;}),"capacity preserves undelivered slots");
    r.bombPickups.clear();r.bombClearRewards=false;r.player.attributes.luck=10;r.step({});
    check(r.bombPickups.size()==3,"capacity recovery delivers all original slots");
    for(size_t i=0;i<3;++i)check(r.bombPickups[i].seed==slots[i].pickupSeed&&r.bombPickups[i].sourceSubtype==slots[i].subtype&&planarDistance(r.bombPickups[i].position,slots[i].preferred)<.001f,"deferred slot identity and location stay fixed");
    for(int mode:{0,2}){auto off=create(129,1.1f,7,9,mode);check(owner(off)<0&&!off.enterSourceRoomReview(32),"OFF/test cannot masquerade as complete bomb room");}
}
int main(int argc,char **argv){try{
    if(argc>1&&std::string(argv[1])=="--scan") {
        for(const auto dims:{std::array<float,3>{.75f,5,5},{1.1f,7,9},{1.5f,10,10}}) {
            bool found=false;
            for(uint64_t seed=0;seed<10000&&!found;++seed)if(candidate(seed)) {
                auto r=create(seed,dims[0],int(dims[1]),int(dims[2]));const int index=owner(r);
                if(index>=0&&ordinary(r.arena.rooms[size_t(index)])){std::cout<<"WITNESS "<<seed<<' '<<dims[0]<<' '<<dims[1]<<' '<<dims[2]<<" room="<<index+1<<std::endl;found=true;}
            }
            check(found,"natural source32 witness search");
        }return 0;
    }
    if(argc==5){verify(std::stoull(argv[1]),std::stof(argv[2]),std::stoi(argv[3]),std::stoi(argv[4]));return 0;}
    verify(1027,.75f,5,5);verify(129,1.1f,7,9);verify(1027,1.5f,10,10);boundaries();
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
