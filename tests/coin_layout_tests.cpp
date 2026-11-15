#include "combat/Simulation.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceCoinRockRoomData.hpp"
#include "world/SourceRoomSelection.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,float size=1.1f,int lo=7,int hi=9,int mode=1,int floor=0) {
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,
                 defaultMechanics(),size,lo,hi,.26f,true,mode,true);
    r.coinClearRewards=false;return r;
}
int owner(const Simulation &r) {
    for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==30)return i;
    return -1;
}
void advance(Simulation &r,int frames){for(int n=0;n<frames;++n)r.step({});}
void verify(uint64_t seed,float size,int lo,int hi,bool lifecycle) {
    auto r=create(seed,size,lo,hi);const int index=owner(r);const std::string tag=" seed="+std::to_string(seed)+" scale="+std::to_string(size)+" range="+std::to_string(lo)+","+std::to_string(hi);
    check(index>=0,"natural source30 room"+tag);const auto layout=r.arena.rooms[size_t(index)];
    check(index!=2&&index!=3&&layout.kind==RoomKind::Empty&&layout.story==StoryRoom::None&&r.roomEnemies(index).empty(),"compatible complete room without enemies"+tag);
    check(layout.coinSpawns.size()==4&&layout.heartSpawns.empty()&&layout.chestSpawns.empty(),"exact four coin slots"+tag);
    int rocks=0;for(const auto &b:r.arena.breakables)if(b.room==index){++rocks;check(b.sourceGridIndex==67&&b.paid&&!b.destroyed,"source central rock only"+tag);}
    check(rocks==1&&r.arena.blocked(layout.center,.48f)&&layout.obstacles.empty()&&r.arena.supplyCache.room!=index,"central rock and no unrelated props/cache"+tag);
    for(const auto &coin:r.moneyPickups)check(r.arena.roomAt(coin.position)!=index,"no extra random piles"+tag);
    uint32_t state=sourceRoomDescriptorSeeds(layout.sourceRoomSelectionSeed).spawn;size_t slot=0;int total=0;
    for(int ordinal=0;ordinal<5;++ordinal) {
        sourceRoomSpawnRandom(state);if(ordinal==2)continue;
        const auto &spawn=layout.coinSpawns[slot];const auto &record=Basement30Coins[slot++];
        check(spawn.ordinal==ordinal&&spawn.x==record.x&&spawn.y==record.y&&spawn.sourceSubtype==0&&spawn.pickupSeed==state,"original slot order includes rock RNG step"+tag);
        check(spawn.subtype==sourceOrdinaryPickup(state,20,{}).subtype,"shared native ordinary resolver"+tag);
        check(planarDistance(spawn.preferred,sourceHeartCell(layout,record.x,record.y))<.001f,"exact source cell adaptation"+tag);
        total+=sourceOrdinaryCoinValue(spawn.subtype);
    }
    check(r.enterSourceRoomReview(30)&&r.room==index&&r.roomClear&&!r.rooms[size_t(index)].redHeartAward,"direct empty room has no fake combat-clear reward"+tag);
    auto count=[&]{return std::count_if(r.moneyPickups.begin(),r.moneyPickups.end(),[&](const auto &c){return c.room==index&&c.placedInLayout;});};
    check(count()==4,"four ready actors independent of clear-coin switch"+tag);
    for(const auto &coin:r.moneyPickups)if(coin.room==index)check(coin.placedInLayout&&coin.timing.phase==CoinTiming::Phase::Idle&&coin.timing.collectible(),"idle on first entry, no birth wait"+tag);
    for(int p:layout.passages) {
        const auto at=r.arena.doorApproach(p,r.arena.passages[size_t(p)].rooms[0]==index?0:1);
        check(!r.arena.path(layout.entry,at,.48f).empty(),"normal doors remain reachable"+tag);
    }
    for(const auto &spawn:layout.coinSpawns) {
        auto route=r.arena.path(r.player.position,spawn.preferred,.48f);check(!route.empty(),"coin reachable around central rock"+tag);
        auto from=r.player.position;for(auto at:route){check(!r.arena.blocked(at,.48f)&&r.arena.clear(from,at,.48f),"physical path clearance"+tag);from=at;}
        Input click;click.moveTarget=spawn.preferred;r.step(click);
        for(int n=0;n<300;++n){r.step({});check(!r.arena.blocked(r.player.position,.48f),"actual movement never enters central rock"+tag);}
        check(planarDistance(r.player.position,spawn.preferred)<.15f,"actual click reaches coin"+tag);
    }
    check(r.money()==uint64_t(total)&&count()==0&&r.dynamite==StartingDynamite,"exact once-only value collected without spending dynamite"+tag);
    const auto clears=r.stats.rooms;r.jumpDebug(0);r.jumpDebug(index);advance(r,60);
    check(r.money()==uint64_t(total)&&count()==0&&r.stats.rooms==clears,"revisit cannot repay coins or clear reward"+tag);
    if(lifecycle) {
        const auto id=r.summary().id;r.player.hp=4;r.player.attributes.speed=.8f;
        r.resizeRooms(size,lo,hi,.26f,std::nullopt,0);
        check(r.arena.rooms[size_t(index)].coinSpawns.empty()&&count()==0,"OFF Apply removes source coin arrangement"+tag);
        r.player.position=layout.center;r.resizeRooms(size,lo,hi,.26f,std::nullopt,1);
        check(count()==4&&r.arena.rooms[size_t(index)].coinSpawns.size()==4,"SOURCE Apply restores layout actors"+tag);
        check(!r.arena.blocked(r.player.position,.48f)&&!r.arena.path(r.arena.rooms[size_t(index)].entry,r.player.position,.48f).empty(),"Apply cannot trap player in restored rock"+tag);
        check(r.summary().id==id&&r.player.hp==4&&r.player.attributes.speed==.8f&&r.money()==uint64_t(total)&&!r.coinClearRewards,"regeneration retains player/build/wallet/expedition and reward switch"+tag);
    }
    std::cout<<"PASS exact source slots/seeds/rock, idle coins, physical click collection, values, revisit/Apply"<<tag<<" total="<<total<<'\n';
}
void boundaries(uint64_t seed) {
    auto r=create(seed);const int index=owner(r);check(index>=0,"capacity fixture has source30");
    const auto slots=r.arena.rooms[size_t(index)].coinSpawns;
    r.moneyPickups.assign(1024,MoneyPickup{r.arena.rooms[0].center,1});
    check(r.enterSourceRoomReview(30)&&std::none_of(r.rooms[size_t(index)].roomCoinsDelivered.begin(),r.rooms[size_t(index)].roomCoinsDelivered.end(),[](bool x){return x;}),"capacity retains undelivered source identities");
    r.moneyPickups.clear();r.player.attributes.luck=10;r.step({});
    check(r.moneyPickups.size()==4&&r.money()==0,"capacity release admits idle actors without retroactive collection");
    for(size_t i=0;i<slots.size();++i)check(r.moneyPickups[i].sourceSubtype==slots[i].subtype&&planarDistance(r.moneyPickups[i].position,slots[i].preferred)<.001f,"capacity does not reroll or relocate");
    r.player.position=slots[0].preferred;r.step({});const auto paid=r.money();
    check(paid==uint64_t(sourceOrdinaryCoinValue(slots[0].subtype))&&r.moneyPickups[0].timing.phase==CoinTiming::Phase::Collect,"immediate admission starts once-only collection");
    r.jumpDebug(0);advance(r,60);check(r.moneyPickups[0].timing.frame==0,"inactive collection phase frozen");
    r.jumpDebug(index);advance(r,60);check(r.money()==paid&&r.moneyPickups.size()==3,"partial revisit keeps remaining coins, no replacement");
    auto blocked=create(seed);auto &layout=blocked.arena.rooms[size_t(index)];const auto at=layout.coinSpawns[0].preferred;
    Breakable barrier;barrier.room=index;barrier.paid=true;barrier.bounds={add(at,{-.4f,-.85f,-.4f}),add(at,{.4f,.5f,.4f})};
    blocked.arena.breakables.push_back(barrier);blocked.arena.rebuildWalls();check(blocked.enterSourceRoomReview(30),"blocked slot fixture enters");
    check(!blocked.rooms[size_t(index)].roomCoinsDelivered[0]&&std::count(blocked.rooms[size_t(index)].roomCoinsDelivered.begin(),blocked.rooms[size_t(index)].roomCoinsDelivered.end(),true)==3,"blocked slot waits without moving");
    blocked.arena.breakables.pop_back();blocked.arena.rebuildWalls();blocked.step({});
    check(blocked.rooms[size_t(index)].roomCoinsDelivered[0]&&std::any_of(blocked.moneyPickups.begin(),blocked.moneyPickups.end(),[&](const auto &p){return p.placedInLayout&&planarDistance(p.position,at)<.001f&&p.sourceSubtype==slots[0].subtype;}),"cleared obstruction admits exact same coin");
    for(int subtype:{1,2,3})for(uint64_t money:{0,98,99,120}) {
        auto cap=create(seed);auto &spawns=cap.arena.rooms[size_t(index)].coinSpawns;
        spawns.resize(1);spawns[0].subtype=subtype; // Explicit actor-consumer fixture, not a claimed natural outcome.
        check(cap.enterSourceRoomReview(30),"wallet fixture entry");cap.moneyCollected=money;cap.player.position=spawns[0].preferred;advance(cap,60);
        const auto expected=money<99?std::min(uint64_t(99),money+uint64_t(sourceOrdinaryCoinValue(subtype))):money;
        check(cap.money()==expected,"penny/nickel/dime use existing99 cap without deleting retained currency");
        const auto remaining=std::count_if(cap.moneyPickups.begin(),cap.moneyPickups.end(),[&](const auto &p){return p.placedInLayout&&p.room==index;});
        check(remaining==(money<99?0:1),"whole coin clips below99; refused coin remains at cap");
    }
    for(int mode:{0,2}){auto off=create(seed,1.1f,7,9,mode);check(owner(off)<0&&!off.enterSourceRoomReview(30),"OFF/test mode cannot masquerade as source30");}
    auto later=create(seed,1.1f,7,9,1,1);check(owner(later)<0,"opening-floor scope retained");
    std::cout<<"PASS capacity/blocked identity, partial revisit/inactive clock, all three coin values/caps and scope exclusions\n";
}
int main(){try{
    verify(1322,.75f,5,5,false);
    verify(1063,1.1f,7,9,true);
    verify(1063,1.5f,10,10,false);
    boundaries(1063);
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
