#include "combat/Simulation.hpp"
#include "combat/SourceRoomRewards.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,int floor=0){
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true,1,true);
    r.coinClearRewards=true;r.redHeartClearRewards=true;r.godMode=true;return r;
}
uint64_t witness(int subtype) {
    for(uint64_t seed=0;seed<100000;++seed){
        ExpeditionPlan e(seed,false,WitnessAccount::None,ExpeditionPacing::Compact);
        Random adapter(e.floorSeed(0)^0x4845415254415744ULL^(2*0x9e3779b97f4a7c15ULL));auto state=uint32_t(adapter.next());if(!state)state=1;
        SourceAwardRng rng{state};if(sourceOrdinaryRoomAward(rng)!=20)continue;
        if(sourceOrdinaryPickup(rng.next(),20).subtype!=subtype)continue;
        auto r=create(seed);const auto &l=r.arena.rooms[1];if(l.kind==RoomKind::Combat&&l.story==StoryRoom::None)return seed;
    }throw std::runtime_error("no natural coin witness");
}
void clear(Simulation &r){r.jumpDebug(1);r.moneyPickups.clear();r.clearRoomDebug();}
void ordinary(int subtype,uint64_t seed) {
    auto r=create(seed);clear(r);const auto &a=r.rooms[1].redHeartAward;
    check(a&&a->variant==20&&a->subtype==subtype&&a->delivered&&!a->pending,"natural ordinary coin award");
    check(r.moneyPickups.size()==1&&r.moneyPickups[0].sourceSubtype==subtype&&r.moneyPickups[0].value==sourceOrdinaryCoinValue(subtype),"native source value and identity");
    auto at=r.moneyPickups[0].position;check(r.arena.roomAt(at)==1&&!r.arena.blocked(at,.35f)&&!r.arena.path(r.player.position,at,.48f).empty(),"coin reachable in owner room");
    r.player.position=at;for(int n=0;n<90;++n)r.step({});check(r.money()==uint64_t(sourceOrdinaryCoinValue(subtype))&&r.moneyPickups.empty(),"exact once-only collection");
    auto wallet=r.money();r.jumpDebug(0);r.jumpDebug(1);r.step({});check(r.money()==wallet&&r.moneyPickups.empty(),"no duplicate on revisit");
    std::cout<<"COIN seed="<<seed<<" room=2 subtype="<<subtype<<" value="<<wallet<<'\n';
}
void boundaries(uint64_t seed) {
    for(int fps:{30,60,120}){
        auto r=create(seed);clear(r);r.player.position=r.moneyPickups[0].position;
        for(int n=1;n<23*fps/30;++n){r.step({},1.f/fps);check(r.money()==0,"coin cannot collect before Drop23");}
        r.step({},1.f/fps);check(r.money()==1&&r.moneyPickups.size()==1&&r.moneyPickups[0].timing.phase==CoinTiming::Phase::Collect,"Drop23 admits exactly once");
        for(int n=1;n<14*fps/30;++n){r.step({},1.f/fps);check(r.money()==1&&r.moneyPickups.size()==1,"Collect14 presentation pays once");}
        r.step({},1.f/fps);check(r.moneyPickups.empty(),"Collect14 cleanup");
    }
    auto r=create(seed);r.jumpDebug(1);r.moneyPickups.assign(1024,MoneyPickup{r.arena.rooms[0].center,1,1,false});r.clearRoomDebug();
    auto &a=r.rooms[1].redHeartAward;check(a&&a->pending&&!a->delivered,"coin capacity backpressure");auto init=a->pickupSeed;
    r.coinClearRewards=false;r.player.attributes.luck=10;r.jumpDebug(0);r.moneyPickups.clear();r.step({});check(a->pending,"inactive award remains pending");
    r.jumpDebug(1);r.step({});check(a->delivered&&a->pickupSeed==init&&a->luck==0&&r.moneyPickups.size()==1&&r.moneyPickups[0].timing.frame==0,"deferred birth retains result, starts at admission");
    r.step({},.1f);auto age=r.moneyPickups[0].timing.frame;r.jumpDebug(0);r.step({},1);check(r.moneyPickups[0].timing.frame==age,"inactive coin clock frozen");
    r.jumpDebug(1);r.rewardOpen=true;r.step({},1);check(r.moneyPickups[0].timing.frame==age,"paused coin clock frozen");r.rewardOpen=false;
    r.resizeRooms(1.2f,7,9,.26f);check(!r.coinClearRewards&&r.player.attributes.luck==10,"Apply retains live coin setting");
    auto off=create(seed);off.coinClearRewards=false;clear(off);off.coinClearRewards=true;off.jumpDebug(0);off.jumpDebug(1);off.step({});check(std::none_of(off.moneyPickups.begin(),off.moneyPickups.end(),[](auto &c){return c.sourceSubtype!=0;})&&off.rooms[1].redHeartAward&&!off.rooms[1].redHeartAward->pending,"no retroactive award after enabling");
    auto later=create(seed,1);later.jumpDebug(1);later.moneyPickups.clear();later.clearRoomDebug();check(!later.rooms[1].redHeartAward,"later floors keep separate policy");
    std::cout<<"PASS source timing at30/60/120Hz, capacity, inactive/pause, live edits, no reroll/retroactive reward, floor boundary\n";
}
void wallet(uint64_t seed){for(uint64_t money:{0,98,99,120}){
    auto r=create(seed);clear(r);r.moneyCollected=money;r.player.position=r.moneyPickups[0].position;for(int n=0;n<90;++n)r.step({});
    check(r.money()==(money<99?std::min(uint64_t(99),money+5):money),"source coin clips at99 without deleting retained currency");
    check(r.moneyPickups.empty()==(money<99),"whole coin consumed below cap; refused coin retained at/above cap");
}}
int main(){try{
    auto penny=witness(1),nickel=witness(2),dime=witness(3);ordinary(1,penny);ordinary(2,nickel);ordinary(3,dime);boundaries(penny);wallet(nickel);
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
