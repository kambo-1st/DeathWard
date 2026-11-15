#include "RoomReviewSeeds.hpp"
#include "combat/Simulation.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceKeyRockRoomData.hpp"
#include "world/SourceRoomSelection.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,float size=1.1f,int lo=7,int hi=9,int mode=1) {
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
                 defaultMechanics(),size,lo,hi,.26f,true,mode,true);
    r.keyClearRewards=false;return r;
}
int owner(const Simulation &r){for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==214)return i;return -1;}
void advance(Simulation &r,int frames){for(int n=0;n<frames;++n)r.step({});}
void verify(uint64_t seed,float size,int lo,int hi,bool lifecycle) {
    auto r=create(seed,size,lo,hi);const int index=owner(r);const auto tag=" seed="+std::to_string(seed)+" scale="+std::to_string(size);
    check(index>=0,"natural source214 exists"+tag);const auto layout=r.arena.rooms[size_t(index)];
    check(index!=2&&index!=3&&layout.kind==RoomKind::Empty&&layout.story==StoryRoom::None&&r.roomEnemies(index).empty(),"compatible complete empty room"+tag);
    check(layout.keySpawns.size()==2&&layout.heartSpawns.empty()&&layout.coinSpawns.empty()&&layout.chestSpawns.empty(),"exact key-only contents"+tag);
    int rocks=0;for(const auto &b:r.arena.breakables)if(b.room==index){++rocks;check(b.sourceGridIndex>=0&&b.paid&&!b.destroyed,"source rock without custom drop"+tag);}
    check(rocks==18&&layout.obstacles.empty()&&r.arena.supplyCache.room!=index,"eighteen rocks, no unrelated props"+tag);
    uint32_t state=sourceRoomDescriptorSeeds(layout.sourceRoomSelectionSeed).spawn;size_t slot=0;
    for(int ordinal=0;ordinal<20;++ordinal) {
        sourceRoomSpawnRandom(state);if(ordinal!=4&&ordinal!=15)continue;
        const auto &spawn=layout.keySpawns[slot];const auto &record=Basement214Keys[slot++];
        check(spawn.ordinal==ordinal&&spawn.x==record.x&&spawn.y==record.y&&spawn.pickupSeed==state,"original source ordinal and seed"+tag);
        check(spawn.subtype==sourceOrdinaryPickup(state,30).subtype&&planarDistance(spawn.preferred,sourceHeartCell(layout,record.x,record.y))<.001f,"native subtype and exact canyon cell"+tag);
    }
    check(r.enterSourceRoomReview(214)&&r.roomClear&&!r.rooms[size_t(index)].redHeartAward,"direct empty room review without fake clear"+tag);
    check(r.keyPickups.size()==2&&r.keys==0,"two ordinary keys before combat independent of clear toggle"+tag);
    for(const auto &p:r.keyPickups)check(p.placedInLayout&&p.timing.phase==KeyTiming::Phase::Idle&&p.timing.collectible(),"preplaced idle actor"+tag);
    for(const auto &s:layout.keySpawns)check(r.arena.path(layout.entry,s.preferred,.48f).empty(),"intact rock encloses original cell"+tag);
    for(int passage:layout.passages) {
        const auto approach=r.arena.doorApproach(passage,r.arena.passages[size_t(passage)].rooms[0]==index?0:1);
        check(!r.arena.path(layout.entry,approach,.48f).empty(),"normal doors remain accessible"+tag);
    }
    r.godMode=true; // Blast mechanics fixture only; main-game handoff uses normal health.
    for(size_t i=0;i<2;++i) {
        const auto target=layout.keySpawns[i].preferred;
        Input click;click.moveTarget=target;r.step(click);advance(r,90);check(r.keys==int(i),"cannot collect through intact enclosure"+tag);
        const auto approach=sourceHeartCell(layout,i==0?1:11,i==0?2:4);
        check(!r.arena.blocked(approach,.48f)&&!r.arena.path(r.player.position,approach,.48f).empty(),"accessible demolition approach"+tag);
        r.player.position=approach;r.player.velocity={};Input stop;stop.moveTarget=approach;r.step(stop);
        check(r.placeDynamite(),"ordinary dynamite admission"+tag);advance(r,240);
        check(!r.arena.path(r.player.position,target,.48f).empty(),"real blast opens key access"+tag);
        r.step(click);for(int n=0;n<360;++n){r.step({});check(!r.arena.blocked(r.player.position,.48f),"actual click navigation physical clearance"+tag);}
        check(r.keys==int(i)+1,"collect exactly one key after breach"+tag);
    }
    check(r.keyPickups.empty()&&r.dynamite==StartingDynamite-2,"two keys and two ordinary dynamite spent"+tag);
    const auto clears=r.stats.rooms;r.jumpDebug(0);r.jumpDebug(index);advance(r,60);
    check(r.keys==2&&r.keyPickups.empty()&&r.stats.rooms==clears,"revisit never duplicates keys or clears"+tag);
    if(lifecycle) {
        r.player.hp=4;const auto id=r.summary().id;r.resizeRooms(size,lo,hi,.26f,std::nullopt,0);
        check(owner(r)<0&&r.keyPickups.empty(),"OFF Apply removes source arrangement"+tag);
        r.player.position=layout.keySpawns[0].preferred;r.resizeRooms(size,lo,hi,.26f,std::nullopt,1);
        check(r.keyPickups.size()==2&&!r.arena.blocked(r.player.position,.48f)&&!r.arena.path(r.arena.rooms[size_t(index)].entry,r.player.position,.48f).empty(),"Apply restores keys and rescues player from reclosed pocket"+tag);
        check(r.keys==2&&r.player.hp==4&&r.summary().id==id&&!r.keyClearRewards,"Apply retains inventory/build/expedition/policy"+tag);
    }
    std::cout<<"PASS full source214 exact identities/access/dynamite/clicks/revisit"<<tag<<'\n';
}
void boundaries(uint64_t seed) {
    auto r=create(seed);const int index=owner(r);check(index>=0,"deferred layout fixture");const auto slots=r.arena.rooms[size_t(index)].keySpawns;
    r.keyPickups.assign(1024,OrdinaryKeyPickup{r.arena.rooms[0].center,0});check(r.enterSourceRoomReview(214),"deferred direct entry");
    check(std::none_of(r.rooms[size_t(index)].roomKeysDelivered.begin(),r.rooms[size_t(index)].roomKeysDelivered.end(),[](bool b){return b;}),"capacity retains slot identities");
    r.keyPickups.clear();r.player.attributes.luck=10;r.step({});check(r.keyPickups.size()==2,"released capacity admits same keys");
    for(size_t i=0;i<2;++i)check(r.keyPickups[i].seed==slots[i].pickupSeed&&r.keyPickups[i].sourceSubtype==slots[i].subtype&&planarDistance(r.keyPickups[i].position,slots[i].preferred)<.001f,"no deferred reroll or relocation");
    for(int mode:{0,2}){auto off=create(seed,1.1f,7,9,mode);check(owner(off)<0&&!off.enterSourceRoomReview(214),"OFF/test mode cannot pretend complete source214");}
    std::cout<<"PASS source214 deferred identities and scope\n";
}
int main(int argc,char **argv){try{
    if(argc>1){verify(std::stoull(argv[1]),.75f,5,5,false);return 0;}
    verify(review::seed(214,.75f,5,5),.75f,5,5,false);verify(review::seed(214,1.1f,7,9),1.1f,7,9,true);verify(review::seed(214,1.5f,10,10),1.5f,10,10,false);boundaries(review::seed(214));
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
