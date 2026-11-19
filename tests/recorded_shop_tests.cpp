#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceRecordedShop.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation generated(uint64_t seed=6,float scale=1,int lo=7,int hi=9,int layouts=1,int props=1,int pool=1,bool variation=true,bool shop=true,int floor=0) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,layouts,true,true,true,shop,true,variation,pool,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{props});
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void walk(Simulation &s,Vector3 at){Input in;in.moveTarget=at;s.step(in);for(int i=0;i<1800&&planarDistance(s.player.position,at)>.1f;++i)s.step({});check(planarDistance(s.player.position,at)<.1f,"real click path reaches stock");}
void source(){
    std::ifstream f(std::filesystem::path(DEATHWARD_TEST_ROOT)/"docs/reports/isaac-first-floor-parity/d14a10-recorded-shop/source-slots.csv");check(bool(f),"pinned STB slots");std::string line;std::getline(f,line);int count=0;while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int n,x,y,t,v,st,choices;float weight;row>>n>>x>>y>>t>>v>>st>>weight>>choices;const auto &entry=RecordedShopSlots.at(size_t(n));check(entry.ordinal==n&&entry.x==x&&entry.y==y&&entry.type==t&&entry.variant==v&&entry.subtype==st,"exact STB stack identities/order");check(choices==(n==3?2:1)&&weight==(n==3?.5f:1.f),"weighted keeper vs singleton slots");++count;}check(count==8,"all eight slots");std::cout<<"PASS exact eight source stacks and weighted keeper metadata\n";
}
void arrangement(Simulation &s) {
    const int index=s.arena.shopRoom;const auto &r=s.arena.rooms.at(size_t(index));check(r.sourceShopTemplate==0&&r.kind==RoomKind::Shop&&r.passages.size()==1,"recorded contents in retained optional shop");check(s.shopUpgradeItem==195&&s.shopUpgradeSlot==0&&s.shopCardSlot==1&&s.shopPrice(15,0)==15&&s.shopPrice(5,1)==5,"recorded observed stock/order/prices");check(!s.shopHeartOffered()&&!s.shopBombOffered()&&!s.shopKeyOffered()&&s.roomEnemyCount(index)==0,"no unrecorded stock or combat");
    std::set<uint64_t> ids;int rocks=0;for(const auto &p:s.arena.breakables){check(ids.insert(p.id).second,"unique prop IDs");if(p.room!=index)continue;++rocks;check(p.kind==BreakableKind::CrackedRock&&p.paid,"plain rocks with no custom coin reward");}
    check(rocks==4&&r.obstacles.empty(),"four source rocks, no generated outcrops");
    for(const auto &slot:RecordedShopSlots)if(slot.type==1000){auto p=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.room==index&&p.sourceGridIndex==(slot.y+1)*15+slot.x+1;});check(p!=s.arena.breakables.end()&&planarDistance(p->rewardPosition,recordedShopCell(r,slot.x,slot.y))<.001f&&p->lootSeed==recordedShopSlotSeed(r,slot.ordinal),"recorded rock cell, ID and native ordinal seed");check(s.arena.blocked(p->rewardPosition,.48f),"rock collider");}
    check(s.arena.blocked(r.center,.48f),"retained merchant wagon collider");
    for(int x:{5,7}){const auto at=recordedShopCell(r,x,4);check(!s.arena.blocked(at,.55f)&&!s.arena.path(r.entry,at,.48f).empty(),"both stock positions reachable with rocks intact");}
}
void loop(float scale,int lo,int hi) {
    auto s=generated(6,scale,lo,hi);arrangement(s);check(s.enterSourceRoomReview(RecordedShopReview)&&s.player.hp==6&&!s.godMode,"normal-health direct review requires generated record");const int shop=s.room;s.moneyCollected=20;const auto cart=s.arena.rooms[size_t(shop)].center;
    s.step({});check(s.pillPickups.size()==1&&s.pillPickups[0].seed==recordedShopSlotSeed(s.arena.rooms[size_t(shop)],7),"card actor uses all-eight-slot descriptor sequence");walk(s,s.shopUpgradePosition());check(s.shopUpgradeSold&&s.money()==5&&s.itemStacks({"isaac",ItemKind::Collectible,195})==1&&s.pillPickups.size()>=4,"real movement buys Purse and admits pills once");
    ticks(s,80);walk(s,s.shopCardPosition());check(s.shopCardSold&&s.money()==0&&s.pills.held==TemperanceCard,"real movement buys card without overlapping another slot");check(s.usePill()&&s.bloodMachines.size()==1,"card works around shop rocks/wagon");const auto machine=s.bloodMachines[0].position;s.player.position=recordedShopCell(s.arena.rooms[size_t(shop)],6,4);ticks(s,5);
    auto rock=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.room==shop;});const auto id=rock->id;const auto at=rock->rewardPosition;const auto half=(rock->bounds.max.x-rock->bounds.min.x)*.5f;bool placed=false;
    s.inventoryBombTuning=InventoryBombTuning{};for(auto d:std::array<Vector3,4>{{{0,0,1},{0,0,-1},{1,0,0},{-1,0,0}}}){auto p=add(at,mul(d,half+.6f));if(s.arena.blocked(p,.48f)||s.arena.roomAt(p)!=shop)continue;s.player.position=p;placed=s.placeDynamite();if(placed)break;}check(placed,"dynamite admitted beside recorded rock");s.player.position=s.arena.rooms[size_t(shop)].entry;ticks(s,100);rock=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.id==id;});check(rock->destroyed&&!s.arena.blocked(at,.48f),"ordinary dynamite removes rock/collider");
    s.enterRoom(0);s.enterRoom(shop);ticks(s,90);check(s.shopUpgradeSold&&s.shopCardSold&&s.money()==0&&s.itemStacks({"isaac",ItemKind::Collectible,195})==1&&rock->destroyed&&s.bloodMachines.size()==1&&planarDistance(machine,s.bloodMachines[0].position)<.001f,"revisit retains purchases, demolition and machine");
    s.shopUpgradePrice=13;s.bloodMachineTuning.cardPrice=4;s.resizeRooms(scale,lo,hi,.27f);arrangement(s);check(s.itemStacks({"isaac",ItemKind::Collectible,195})==1&&s.shopUpgradePrice==13&&s.bloodMachineTuning.cardPrice==4&&!s.shopUpgradeSold&&!s.shopCardSold&&s.bloodMachines.empty(),"Apply retains owned item/custom prices and resets floor stock/actors");check(!s.arena.blocked(s.player.position,.48f),"safe player after Apply");s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.itemStacks({"isaac",ItemKind::Collectible,195})==1,"descent retains owned item");for(const auto &r:s.arena.rooms)check(r.sourceShopTemplate<0,"opening-floor-only record");
    std::cout<<"PASS recorded shop seed6 scale="<<scale<<" range="<<lo<<'-'<<hi<<" purchase/consumption/demolition/revisit/Apply/descent\n";
}
void boundaries(){
    for(int mode:{0,2}){auto s=generated(6,1,7,9,mode);check(s.arena.rooms[size_t(s.arena.shopRoom)].sourceShopTemplate<0&&!s.enterSourceRoomReview(RecordedShopReview),"OFF/test does not masquerade as recorded shop");}
    for(int props:{0,2}){auto s=generated(6,1,7,9,1,props);check(!s.enterSourceRoomReview(RecordedShopReview),"props toggle stages arrangement");}
    for(int pool:{0,2}){auto s=generated(6,1,7,9,1,1,pool);check(!s.enterSourceRoomReview(RecordedShopReview),"different forced collectible cannot masquerade");}
    for(auto flags:{std::pair{false,true},std::pair{true,false}}){auto s=generated(6,1,7,9,1,1,1,flags.first,flags.second);check(!s.enterSourceRoomReview(RecordedShopReview),"shop switches retain their scope");}
    auto natural=generated(2);check(!natural.enterSourceRoomReview(RecordedShopReview)&&natural.shopUpgradeItem==195,"Purse without matching card remains old ordinary stock");
    auto s=generated();check(s.enterSourceRoomReview(RecordedShopReview),"Apply fixture");s.player.hp=4;s.resizeRooms(1,7,9,.26f,std::nullopt,0);check(s.player.hp==4&&s.arena.rooms[size_t(s.room)].sourceShopTemplate<0,"Apply OFF no heal");s.resizeRooms(1,7,9,.26f,std::nullopt,1);arrangement(s);check(s.player.hp==4&&!s.arena.blocked(s.player.position,.48f),"Apply SOURCE restores whole layout safely");
    const auto p=BalancePreset::load(std::filesystem::path(DEATHWARD_TEST_ROOT)/"docs/reports/isaac-first-floor-parity/d14a9-temperance/review-preset.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&p.roomHeartLayouts==1&&p.temperance==BloodMachineTuning{},"schema54 migration preserves all values");
    std::cout<<"PASS SOURCE/props/stock/pool/review/Apply boundaries and schema54 migration\n";
}
}
int main(int argc,char **argv){try{std::cout<<std::unitbuf;source();loop(.75f,5,5);loop(1,7,9);loop(1.5f,10,10);boundaries();if(argc>1&&std::string(argv[1])=="--coverage"){int admitted=0,rejected=0;for(uint64_t seed=0;seed<1024;++seed)if(matchesRecordedShop(seed,1)){auto s=generated(seed,.75f,5,5);if(s.arena.rooms[size_t(s.arena.shopRoom)].sourceShopTemplate==0){arrangement(s);++admitted;}else ++rejected;}std::cout<<"COVERAGE minimum size admitted="<<admitted<<" safely rejected="<<rejected<<'\n';}return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
