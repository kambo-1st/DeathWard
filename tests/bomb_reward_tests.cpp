#include "combat/Simulation.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,int floor=0){
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,
        defaultMechanics(),1.1f,7,9,.26f,true,1,true);
    r.bombClearRewards=true;r.redHeartClearRewards=true;r.godMode=true;return r;
}
uint64_t witness(int subtype) {
    for(uint64_t seed=0;seed<100000;++seed) {
        ExpeditionPlan e(seed,false,WitnessAccount::None,ExpeditionPacing::Compact);
        Random adapter(e.floorSeed(0)^0x4845415254415744ULL^(2*0x9e3779b97f4a7c15ULL));auto state=uint32_t(adapter.next());if(!state)state=1;
        SourceAwardRng rng{state};if(sourceOrdinaryRoomAward(rng)!=40||sourceOrdinaryPickup(rng.next(),40).subtype!=subtype)continue;
        auto r=create(seed);const auto &l=r.arena.rooms[1];if(l.kind==RoomKind::Combat&&l.story==StoryRoom::None)return seed;
    }throw std::runtime_error("no natural bomb witness");
}
void clear(Simulation &r){r.jumpDebug(1);r.clearRoomDebug();}
void advance(Simulation &r,int frames){for(int i=0;i<frames;++i)r.step({});}
void timing(uint64_t seed,int subtype) {
    for(int fps:{30,60,120}) {
        auto r=create(seed);clear(r);const auto award=r.rooms[1].redHeartAward;
        check(award&&award->variant==40&&award->subtype==subtype&&award->delivered&&r.bombPickups.size()==1,"native ordinary clear produces one bomb");
        check(r.bombPickups[0].seed==award->pickupSeed,"fixed source pickup seed");
        r.player.position=r.bombPickups[0].position;const int before=r.dynamite;
        for(int n=1;n<25*fps/30;++n){r.step({},1.f/fps);check(r.dynamite==before,"bomb cannot collect before Drop25");}
        r.step({},1.f/fps);check(r.dynamite==before+sourceOrdinaryBombValue(subtype)&&r.bombPickups[0].timing.phase==BombTiming::Phase::Collect,"Drop25 admits once");
        for(int n=1;n<(subtype==2?13:16)*fps/30;++n){r.step({},1.f/fps);check(r.dynamite==before+sourceOrdinaryBombValue(subtype)&&r.bombPickups.size()==1,"subtype-specific collection pays once");}
        r.step({},1.f/fps);check(r.bombPickups.empty(),"subtype-specific collection cleanup");
        r.jumpDebug(0);r.jumpDebug(1);advance(r,60);check(r.dynamite==before+sourceOrdinaryBombValue(subtype)&&r.bombPickups.empty(),"revisit cannot repay clear bomb");
    }
    std::cout<<"PASS bomb clear witness seed="<<seed<<" / source timing30,60,120Hz / one-time collection\n";
}
void boundaries(uint64_t seed,uint64_t troll) {
    auto r=create(seed);r.jumpDebug(1);r.bombPickups.assign(1024,OrdinaryBombPickup{r.arena.rooms[0].center,0});r.clearRoomDebug();
    auto &a=r.rooms[1].redHeartAward;check(a&&a->pending&&!a->delivered,"capacity retains bomb award");const auto init=a->pickupSeed;
    r.bombClearRewards=false;r.player.attributes.luck=10;r.jumpDebug(0);r.bombPickups.clear();r.step({});check(a->pending,"inactive pending award stays fixed");
    r.jumpDebug(1);r.step({});check(a->delivered&&a->pickupSeed==init&&a->luck==0&&r.bombPickups.size()==1&&r.bombPickups[0].timing.frame==0,"deferred actual birth at zero independent of live edits");
    advance(r,10);const auto frame=r.bombPickups[0].timing.frame;r.jumpDebug(0);advance(r,60);check(r.bombPickups[0].timing.frame==frame,"inactive bomb frozen");
    r.jumpDebug(1);r.rewardOpen=true;advance(r,60);check(r.bombPickups[0].timing.frame==frame,"paused bomb frozen");r.rewardOpen=false;
    const auto id=r.summary().id;r.resizeRooms(1.2f,7,9,.26f);check(!r.bombClearRewards&&r.bombPickups.empty()&&r.summary().id==id&&r.player.attributes.luck==10,"Apply resets actors but retains expedition/settings");
    r.jumpDebug(r.finalRoom());r.clearRoomDebug();r.floorExitRequested=true;
    check(r.advanceFloor()&&!r.bombClearRewards&&r.bombPickups.empty(),"floor transition retains bomb policy and removes old actors");
    auto off=create(seed);off.bombClearRewards=false;clear(off);off.bombClearRewards=true;off.jumpDebug(0);off.jumpDebug(1);advance(off,60);
    check(off.bombPickups.empty()&&off.rooms[1].redHeartAward&&!off.rooms[1].redHeartAward->pending,"no retroactive bomb reward when reenabled");
    auto rare=create(troll);clear(rare);check(rare.rooms[1].redHeartAward&&rare.rooms[1].redHeartAward->subtype==3&&!rare.rooms[1].redHeartAward->pending&&rare.bombPickups.empty(),"troll decision retained unsupported without reroll");
    auto later=create(seed,1);clear(later);check(!later.rooms[1].redHeartAward,"opening-floor reward scope");
    std::cout<<"PASS deferred/pause/inactive/policy/Apply/scope and unsupported troll witness seed="<<troll<<'\n';
}
void inventory(uint64_t seed) {
    std::ifstream file(std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/resources/native-collection.csv");
    check(bool(file),"preserved native bomb collection matrix");
    std::string line;std::getline(file,line);int cases=0;
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);
        int variant,subtype,initial,golden,keys,bombs,goldenKey,goldenBomb,collected;
        row>>variant>>subtype>>initial>>golden>>keys>>bombs>>goldenKey>>goldenBomb>>collected;
        if(variant!=40||(subtype!=1&&subtype!=2)||golden)continue;
        auto r=create(seed);r.dynamite=initial;
        check(r.spawnOrdinaryBomb(r.player.position,subtype,42,true),"native count fixture admitted");advance(r,100);
        check(r.dynamite==bombs,"actual inventory matches preserved native quantity/clamp");++cases;
    }
    check(cases==8,"all ordinary no-golden native quantity cases");
    for(int subtype:{1,2})for(int initial:{0,1,98,99}) {
        auto r=create(seed);auto at=r.player.position;r.dynamite=initial;
        check(r.spawnOrdinaryBomb(at,subtype,42),"ordinary/double bomb admission");advance(r,100);
        check(r.dynamite==(initial<99?std::min(99,initial+sourceOrdinaryBombValue(subtype)):99),"source single/double count clamps99");
        check(r.bombPickups.empty()==(initial<99),"at99 bomb remains on floor");
        if(initial==99){--r.dynamite;advance(r,60);check(r.dynamite==99&&r.bombPickups.empty(),"refused bomb becomes collectible after spending");}
    }
    auto r=create(seed);for(int subtype:{0,3,4,5,6,7,9})check(!r.spawnOrdinaryBomb(r.player.position,subtype,42),"unsupported subtype refused");
    check(!r.spawnOrdinaryBomb(r.player.position,1,0),"zero seed refused");
    check(r.spawnOrdinaryBomb(r.player.position,1,42,true),"preplaced immediate actor");r.player.hp=0;r.step({});check(r.dynamite==StartingDynamite,"dead player cannot collect");
    std::cout<<"PASS single/double caps, refusal/recovery and unsupported actor identities\n";
}
int main(){try{const auto seed=witness(1);timing(seed,1);timing(witness(2),2);boundaries(seed,witness(3));inventory(seed);}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
