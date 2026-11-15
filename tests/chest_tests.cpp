#include "combat/Simulation.hpp"
#include "combat/ChestGeometry.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,int floor=0) {
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,
                 defaultMechanics(),1.1f,7,9,.26f,true,1,true);
    r.chestClearRewards=r.coinClearRewards=r.redHeartClearRewards=true;r.godMode=true;return r;
}
uint64_t witness() {
    for(uint64_t seed=0;seed<100000;++seed) {
        ExpeditionPlan e(seed,false,WitnessAccount::None,ExpeditionPacing::Compact);
        Random adapter(e.floorSeed(0)^0x4845415254415744ULL^(2*0x9e3779b97f4a7c15ULL));
        auto state=uint32_t(adapter.next());if(!state)state=1;
        SourceAwardRng rng{state};if(sourceOrdinaryRoomAward(rng)!=50)continue;
        auto drops=chestPickupBatches(rng.next());
        if(!std::any_of(drops.begin(),drops.end(),[](auto &d){return d.variant==20;})||
           !std::any_of(drops.begin(),drops.end(),[](auto &d){return d.variant==10;}))continue;
        auto r=create(seed);const auto &l=r.arena.rooms[1];
        if(l.kind==RoomKind::Combat&&l.story==StoryRoom::None)return seed;
    }
    throw std::runtime_error("no natural chest witness");
}
void clear(Simulation &r) {r.jumpDebug(1);r.clearRoomDebug();r.moneyPickups.clear();r.heartPickups.clear();}
void advance(Simulation &r,float seconds){for(int n=0;n<int(seconds*60);++n)r.step({});}
void natural(uint64_t seed) {
    auto r=create(seed);clear(r);
    auto &award=r.rooms[1].redHeartAward;
    check(award&&award->variant==50&&award->delivered&&r.chests.size()==1,"ordinary native selector emits one chest");
    auto &c=r.chests[0];const auto seedSnapshot=c.seed;const auto drops=c.contents;
    check(!c.opened&&c.age==0&&r.arena.roomAt(c.position)==1,"closed chest born in owning room");
    r.player.position=add(c.position,{1.5f,0,0});advance(r,1);
    check(!c.opened,"smaller chest does not open at the old oversized touch distance");
    c.age=0; // Exercise the separate birth gate below.
    const int keys=r.keys;r.player.position=add(c.position,{0,0,chestGeometry::StopZ+.04f});advance(r,.3f);check(!c.opened,"birth gate prevents immediate opening");
    auto age=c.age;r.jumpDebug(0);advance(r,2);check(c.age==age&&!c.opened,"inactive room chest frozen");
    r.jumpDebug(1);r.player.position=add(c.position,{0,0,chestGeometry::StopZ+.04f});r.chestClearRewards=false;r.player.attributes.luck=10;
    advance(r,1.5f);check(c.opened&&r.keys==keys&&c.seed==seedSnapshot,"free touch opening, independent of later policy/Luck");
    check(c.contents.size()==drops.size()&&std::all_of(c.contents.begin(),c.contents.end(),[](auto &d){return d.delivered;}),"all snapshotted contents scatter once");
    auto verify=[&](const auto &p){check(r.arena.roomAt(p.position)==1&&!r.arena.blocked(p.position,.48f)&&!r.arena.path(r.player.position,p.position,.48f).empty(),"loot stays reachable and in owner room");};
    for(auto &p:r.moneyPickups)verify(p);for(auto &p:r.heartPickups)verify(p);for(auto &p:r.chestSupplies)verify(p);for(auto &p:r.keyPickups)verify(p);
    check(planarDistance(r.player.position,c.position)>=chestGeometry::StopZ-.001f,"solid chest keeps player outside the smaller box");
    r.moneyPickups.clear();r.heartPickups.clear();r.chestSupplies.clear();r.keyPickups.clear();
    r.jumpDebug(0);r.jumpDebug(1);r.player.position=add(c.position,{0,0,chestGeometry::StopZ+.04f});advance(r,2);
    check(c.opened&&r.moneyPickups.empty()&&r.heartPickups.empty()&&r.chestSupplies.empty()&&r.keyPickups.empty(),"opened chest cannot repay after revisit");
    r.resizeRooms(1.2f,7,9,.26f);check(!r.chestClearRewards&&r.chests.empty()&&r.chestSupplies.empty()&&r.keyPickups.empty(),"Apply retains option and explicitly resets floor actors");
    std::cout<<"CHEST seed="<<seed<<" room=2 init="<<seedSnapshot<<" drops=";
    for(auto &d:drops)std::cout<<d.variant<<'.'<<d.subtype<<' ';std::cout<<'\n';
}
void capacity(uint64_t seed) {
    auto r=create(seed);r.jumpDebug(1);r.chests.resize(128);r.clearRoomDebug();
    auto &award=r.rooms[1].redHeartAward;check(award&&award->pending&&!award->delivered,"chest capacity retains pending award");
    auto init=award->pickupSeed;r.chests.clear();r.chestClearRewards=false;r.step({});
    check(award->delivered&&r.chests.size()==1&&r.chests[0].seed==init,"capacity recovery delivers same chest despite toggle");
    auto &c=r.chests[0];r.player.position=add(c.position,{0,0,chestGeometry::StopZ+.04f});
    const auto elsewhere=r.arena.rooms[0].center;
    r.moneyPickups.assign(1024,MoneyPickup{elsewhere,1,0,false});
    r.heartPickups.assign(1024,HeartPickup{elsewhere,HeartKind::Red,2,0});
    r.chestSupplies.assign(1024,ChestSupply{elsewhere,0});r.keyPickups.assign(1024,OrdinaryKeyPickup{elsewhere,0});
    advance(r,2);check(c.opened&&std::none_of(c.contents.begin(),c.contents.end(),[](auto &d){return d.delivered;}),"full pickup stores retain chest loot");
    r.moneyPickups.clear();r.heartPickups.clear();r.chestSupplies.clear();r.keyPickups.clear();r.step({});
    check(std::all_of(c.contents.begin(),c.contents.end(),[](auto &d){return d.delivered;}),"pending contents recover without reroll");
    for(auto &p:r.moneyPickups)check(p.timing.frame==0,"actual deferred loot birth starts at zero");
    const auto age=c.openAge;r.rewardOpen=true;advance(r,1);check(c.openAge==age,"paused chest frozen");r.rewardOpen=false;
    std::cout<<"PASS capacity/backpressure, actual birth, snapshot, pause and regeneration\n";
}
void supplies(uint64_t seed) {
    {
        uint32_t lootSeed=1;
        for(;lootSeed<10000;++lootSeed) {
            const auto drops=chestPickupBatches(lootSeed);
            if(std::any_of(drops.begin(),drops.end(),[](auto &d){return d.variant==30;})&&
               std::any_of(drops.begin(),drops.end(),[](auto &d){return d.variant==40;}))break;
        }
        check(lootSeed<10000,"key/bomb contents witness");
        for(float scale:{.75f,1.5f}) {
        auto r=create(seed);r.resizeRooms(scale,scale<1?5:10,scale<1?5:10,.26f);clear(r);
        check(r.chests.size()==1,"chest spawn at dynamic room-size extremes");
        const auto at=r.chests[0].position;r.chests[0].opened=true;
        r.player.position=add(at,{3,0,0});Input input;input.moveTarget=add(at,{-3,0,0});r.step(input);advance(r,6);
        check(planarDistance(r.player.position,*input.moveTarget)<.1f,"dynamic-size floor still routes around chest");
    }
    auto r=create(seed);clear(r);const auto at=r.chests[0].position;r.chests.clear();r.step({});
        check(r.spawnChest(at,lootSeed),"resource-bearing chest admission");
        auto &c=r.chests[0];c.opened=true;r.player.position=add(at,{4,0,0});advance(r,.5f);
        const auto expected=std::count_if(c.contents.begin(),c.contents.end(),[](auto &d){return d.variant==30||d.variant==40;});
        check(r.chestSupplies.size()+r.keyPickups.size()==size_t(expected)&&std::any_of(r.chestSupplies.begin(),r.chestSupplies.end(),[](auto &p){return p.bomb;})&&
              !r.keyPickups.empty(),"chest emits both ordinary key and dynamite actors");
    }
    for(bool bomb:{false,true})for(bool full:{false,true}) {
        auto r=create(seed);clear(r);r.chests.clear();
        ChestSupply p;p.position=r.player.position;p.room=r.room;p.bomb=bomb;p.timing.appear(1);
        r.chestSupplies.push_back(p);int &amount=bomb?r.dynamite:r.keys;amount=full?(bomb?MaxDynamite:99):0;
        advance(r,2);check(amount==(full?(bomb?MaxDynamite:99):1),"supply increments retained resource once");
        check(r.chestSupplies.empty()!=full,"full inventory leaves supply on floor");
        if(full){--amount;advance(r,2);check(r.chestSupplies.empty()&&amount==(bomb?MaxDynamite:99),"refused supply collectible after spending");}
    }
    auto off=create(seed);off.chestClearRewards=false;clear(off);off.chestClearRewards=true;advance(off,1);
    check(off.chests.empty()&&off.rooms[1].redHeartAward&&!off.rooms[1].redHeartAward->pending,"no retroactive clear chest after enabling");
    auto later=create(seed,1);later.jumpDebug(1);later.clearRoomDebug();check(later.chests.empty(),"later floors retain their policy");
    std::cout<<"PASS key/dynamite caps, refusal/recovery, once-only collection, live toggle and floor scope\n";
}
void collision(uint64_t seed) {
    const std::array<Vector3,4> directions{{{1,0,0},{-1,0,0},{0,0,1},{0,0,-1}}};
    for(bool opened:{false,true})for(int fps:{30,60,120})for(auto direction:directions) {
        auto r=create(seed);clear(r);auto &c=r.chests[0];c.opened=opened;c.age=2;
        const auto at=c.position;const auto body=chestGeometry::body(at);
        r.player.position=sub(at,mul(direction,3));check(!r.arena.blocked(r.player.position,.48f),"clear approach fixture");
        Input input;input.movement=direction;
        for(int n=0;n<fps;++n) {
            r.step(input,1.f/fps);
            check(!sphereBox(r.player.position,.48f,body),"walking cannot penetrate closed/open chest");
        }
        check(dot(sub(r.player.position,at),direction)<-.7f,"walking stops on approach side");
        auto dodge=create(seed);clear(dodge);auto &dc=dodge.chests[0];dc.opened=opened;
        const auto center=dc.position;dodge.player.position=sub(center,mul(direction,3));
        input.dodge=true;dodge.step(input,1.f/fps);input.dodge=false;
        for(int n=0;n<fps/2;++n){dodge.step(input,1.f/fps);check(!sphereBox(dodge.player.position,.48f,chestGeometry::body(center)),"dodge cannot tunnel through chest");}
        check(dc.opened==opened,"dodge fixture covers closed and opened bodies independently");
        check(dot(sub(dodge.player.position,center),direction)<-.7f,"dodge remains on approach side");
    }
    for(bool opened:{false,true})for(auto direction:directions) {
        auto r=create(seed);clear(r);auto &c=r.chests[0];c.opened=opened;c.age=2;
        const auto at=c.position;const auto body=chestGeometry::body(at);
        r.player.position=sub(at,mul(direction,3));const auto goal=add(at,mul(direction,3));
        Input input;input.moveTarget=goal;r.step(input);
        for(int n=0;n<360;++n) {
            r.step({});check(!sphereBox(r.player.position,.48f,body),"click route never crosses chest footprint");
        }
        check(planarDistance(r.player.position,goal)<.1f,"click beyond chest arrives around either state");
    }
    for(float scale:{.75f,1.5f}) {
        auto r=create(seed);r.resizeRooms(scale,scale<1?5:10,scale<1?5:10,.26f);clear(r);
        check(r.chests.size()==1,"chest spawn at dynamic room-size extremes");
        const auto at=r.chests[0].position;r.chests[0].opened=true;
        r.player.position=add(at,{3,0,0});Input input;input.moveTarget=add(at,{-3,0,0});r.step(input);advance(r,6);
        check(planarDistance(r.player.position,*input.moveTarget)<.1f,"dynamic-size floor still routes around chest");
    }
    auto r=create(seed);clear(r);const auto at=r.chests[0].position;
    check(!r.arena.blocked(r.player.position,.48f),"clear reward does not trap its player");
    check(!r.spawnChest(r.player.position,17),"solid chest refuses occupied player position");
    r.player.position=add(at,{3,0,0});Input click;click.moveTarget=at;r.step(click);advance(r,2);
    check(r.chests[0].opened&&!r.arena.blocked(r.player.position,.48f),"click on chest approaches edge and opens it");
    r.jumpDebug(0);r.jumpDebug(1);
    check(!r.arena.blocked(r.player.position,.48f)&&r.arena.blocked(at,.48f),"debug revisit avoids chest and retains solid body");
    r.chests.clear();r.step({});r.player.position=sub(at,{3,0,0});
    Input prior;prior.moveTarget=add(at,{3,0,0});r.step(prior);
    check(r.spawnChest(at,17),"new chest can occupy a future route segment");advance(r,5);
    check(planarDistance(r.player.position,*prior.moveTarget)<.1f,"already selected path reroutes when chest is born");
    std::cout<<"PASS closed/open walking+dodge from four sides at30/60/120Hz; click routes, edge opening, occupied birth and revisit\n";
}
int main(){try{const auto seed=witness();natural(seed);capacity(seed);supplies(seed);collision(seed);}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
