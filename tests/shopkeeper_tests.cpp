#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceRecordedShop.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace dw;
namespace {
void check(bool v,const char *message){if(!v)throw std::runtime_error(message);}
Simulation generated(float scale=1,int lo=7,int hi=9,uint64_t seed=6){auto result=Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{1});result.inventoryBombTuning=InventoryBombTuning{};return result;}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void blast(Simulation &s){const auto &r=s.arena.rooms[size_t(s.room)];s.player.position=add(r.center,{0,.85f,shopCartGeometry::HalfDepth+.65f});check(!s.arena.blocked(s.player.position,.48f)&&s.placeDynamite(),"place real dynamite by keeper");s.player.position=r.entry;ticks(s,100);}
void native(){
 std::ifstream file(std::filesystem::path(DEATHWARD_TEST_ROOT)/"docs/reports/isaac-first-floor-parity/d14a11-shopkeeper/source/native-drops.csv");check(bool(file),"native reference exists");std::string line;std::getline(file,line);int count=0;while(std::getline(file,line)){
  std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);uint32_t seed,mask,after;int n;std::array<KeeperDrop,2> expected;row>>seed>>mask>>n;for(auto &v:expected)row>>v.type>>v.variant>>v.subtype>>v.seed;row>>after;check(bool(row),"native row parsed");auto s=seed;const auto actual=sourceKeeperDrops(s,mask);check(s==after&&actual.count==n,"native count and RNG match");for(int i=0;i<2;++i){const auto &a=actual.entries[size_t(i)],&e=expected[size_t(i)];check(a.type==e.type&&a.variant==e.variant&&a.subtype==e.subtype&&a.seed==e.seed,"native output identity and seed");}++count;
 }check(count==4120,"all native outcomes consumed");std::cout<<"PASS 4120 native keeper outcome and RNG comparisons\n";
}
void life(float scale,int lo,int hi,int mode){
 auto s=generated(scale,lo,hi);check(s.enterSourceRoomReview(RecordedShopReview),"generated recorded shop");const int shop=s.room;const auto center=s.arena.rooms[size_t(shop)].center;s.keeperTuning.outcome=mode;
 s.player.position=add(center,{0,.85f,4});for(int i=0;i<100;++i){Input in;in.fire=true;in.aim=center;s.step(in);}check(!s.arena.rooms[size_t(shop)].keeper.destroyed,"ordinary shots do not destroy keeper");
 blast(s);auto &k=s.arena.rooms[size_t(shop)].keeper;check(k.destroyed&&k.sourceHealth==0&&!s.arena.blocked(add(center,{0,.85f,0}),.48f),"blast removes wagon/collider");check(!s.shopUpgradeSold&&!s.shopCardSold,"blast does not sell/free shop stock");
 ticks(s,80);const auto paid=k.delivered;check(paid==k.drops.count,"all chosen drops admitted");check(mode!=1||paid==0,"no-drop override");check(mode!=2||std::count_if(s.moneyPickups.begin(),s.moneyPickups.end(),[&](const auto&p){return p.room==s.room;})==2,"two ordinary coin actors");check(mode!=3||std::count_if(s.enemies.begin(),s.enemies.end(),[](const auto&e){return e.alive&&e.keeperSpawn&&e.monster==monsterId(85);})==2,"two ordinary spiders");check(mode!=4||s.machineCollectibles.size()==1&&s.machineCollectibles[0].item==64,"Steam Sale collectible");
 s.enterRoom(0);s.enterRoom(shop);ticks(s,2);check(s.arena.rooms[size_t(shop)].keeper.destroyed&&s.arena.rooms[size_t(shop)].keeper.delivered==paid,"destroyed/sold state survives revisit");if(mode==3)check(s.enemies.size()==2,"living shop spiders persist on revisit");
 if(mode==1){Input walk;walk.moveTarget=center;s.step(walk);ticks(s,500);check(planarDistance(s.player.position,center)<.8f,"click path crosses former wagon footprint");}
 if(mode==4){auto at=s.machineCollectibles.front().position;s.player.position=at;ticks(s,2);check(s.itemStacks({"isaac",ItemKind::Collectible,64})==1&&s.shopPrice(15,0)==7,"free Steam Sale pickup grants working discount");}
 s.keeperTuning.outcome=(mode+1)%5;ticks(s,3);check(s.arena.rooms[size_t(shop)].keeper.delivered==paid,"live edit never rerolls old reward");s.resizeRooms(scale,lo,hi,.27f);check(!s.arena.rooms[size_t(shop)].keeper.destroyed&&s.keeperTuning.outcome==(mode+1)%5,"Apply resets keeper and retains override");check(!s.arena.blocked(s.player.position,.48f),"Apply relocates player safely around restored wagon");
 std::cout<<"PASS size="<<scale<<" outcome="<<mode<<" shots/blast/drops/revisit/Apply\n";
}
void gates(){
 auto s=generated();check(s.enterSourceRoomReview(RecordedShopReview),"keeper gate fixture");auto &k=s.arena.rooms[size_t(s.room)].keeper;s.keeperTuning.destructible=false;blast(s);check(!k.destroyed&&k.sourceHealth==5,"live disable prevents blast damage");s.keeperTuning.destructible=true;s.keeperTuning.rewards=false;blast(s);check(k.destroyed&&k.drops.count==0,"disabled drops consume destruction once");
 auto small=generated();small.enterSourceRoomReview(RecordedShopReview);small.inventoryBombTuning=InventoryBombTuning{};small.inventoryBombTuning->damage=1;small.dynamite=6;small.keeperTuning.outcome=1;for(int i=0;i<5;++i){blast(small);const auto &state=small.arena.rooms[size_t(small.room)].keeper;check(state.destroyed==(i==4),"source five HP stays separate from bomb internal units");}
 auto capacity=generated();capacity.enterSourceRoomReview(RecordedShopReview);capacity.keeperTuning.outcome=3;capacity.limits.enemies=0;blast(capacity);check(capacity.arena.rooms[size_t(capacity.room)].keeper.delivered==0,"capacity defers chosen births");capacity.enterRoom(0);capacity.enterRoom(capacity.arena.shopRoom);capacity.keeperTuning.outcome=1;capacity.limits.enemies=2;ticks(capacity,3);check(capacity.enemies.size()==2,"pending births survive revisit/edits");
}
void naturalAndFloor(){
 auto s=generated(1,7,9,68);check(s.enterSourceRoomReview(RecordedShopReview),"natural coin review room");blast(s);ticks(s,80);
 const auto &k=s.arena.rooms[size_t(s.room)].keeper;check(k.drops.count==2&&k.drops.entries[0].type==5&&k.drops.entries[0].variant==20&&std::count_if(s.moneyPickups.begin(),s.moneyPickups.end(),[&](const auto &p){return p.room==s.room;})==2,"natural seed68 yields two coin actors without override");
 s.keeperTuning={false,false,3};s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.keeperTuning==KeeperTuning{false,false,3},"floor advance retains keeper configuration");for(const auto &r:s.arena.rooms)check(!r.keeper.destroyed&&r.keeper.delivered==0,"next floor resets keeper state");
 std::cout<<"PASS natural seed68 coins and next-floor configuration/state boundaries\n";
}
void presets(){
 const auto root=std::filesystem::path(DEATHWARD_TEST_ROOT);auto p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d14a10-recorded-shop/review-preset.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&!p.keeper.custom(),"schema55 migration retains settings");
 const auto file=std::filesystem::temp_directory_path()/"deathward-keeper-preset-test.json";for(int mode=0;mode<5;++mode)for(bool enabled:{false,true}){p.keeper={enabled,!enabled,mode};p.save(file);check(BalancePreset::load(file,p.mechanicsFingerprint).revision()==p.revision(),"keeper exact export/load");}std::filesystem::remove(file);
}
}
int main(int argc,char**){try{std::cout<<std::unitbuf;if(argc>1){for(uint64_t seed=0;seed<4096;++seed)if(matchesRecordedShop(seed,1)){auto s=generated(1,7,9,seed);if(!s.enterSourceRoomReview(RecordedShopReview))continue;auto rng=recordedShopSlotSeed(s.arena.rooms[size_t(s.room)],3);const auto d=sourceKeeperDrops(rng);if(d.count==2&&d.entries[0].type==5){std::cout<<"NATURAL coin review seed="<<seed<<" room="<<s.room+1<<" keeper_seed="<<recordedShopSlotSeed(s.arena.rooms[size_t(s.room)],3)<<"\n";return 0;}}return 1;}native();for(auto size:{std::tuple{.75f,5,5},std::tuple{1.f,7,9},std::tuple{1.5f,10,10}})for(int mode=0;mode<5;++mode){auto [scale,lo,hi]=size;life(scale,lo,hi,mode);}gates();naturalAndFloor();presets();std::cout<<"PASS keeper damage/availability/capacity and schema56 boundaries\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
