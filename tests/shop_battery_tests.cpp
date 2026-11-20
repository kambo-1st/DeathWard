#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void equip(Simulation &s,const ItemKey &item){if(s.activeItem)std::erase(s.items,s.activeItem->item);s.activeItem.reset();s.grant(item);}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
Simulation canyon(float scale=1,int lo=7,int hi=9,uint64_t seed=15){return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{1});}
void native(){
 const auto dir=Root/"docs/reports/isaac-first-floor-parity/d14a16-shop-batteries/source";std::string line;int rows=0;std::ifstream f(dir/"native-charge.csv");check(bool(f),"native collection fixture");std::getline(f,line);
 while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int item,cap,before,after,accepted;in>>item>>cap>>before>>after>>accepted;check(bool(in)&&batteryChargeGain(before,cap)==after-before&&accepted==(before<cap),"native charge and admission");++rows;}check(rows==11,"11 ordinary collection cases");
 f.close();f.open(dir/"native-capacity.csv");std::getline(f,line);rows=0;while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int cap,before,amount,after,changed;in>>cap>>before>>amount>>after>>changed;check(bool(in)&&batteryChargeGain(before,cap,amount)==changed&&before+changed==after,"source capacity clamp");++rows;}check(rows==136,"136 source capacity cases");
 f.close();f.open(dir/"native-prices.csv");std::getline(f,line);rows=0;while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);uint32_t seed;int slot,price;in>>seed>>slot>>price;check(bool(in)&&BatteryTuning{}.price==price,"source battery price");++rows;}check(rows==30,"30 source prices");
 f.close();f.open(dir/"native-stock.csv");std::getline(f,line);rows=0;while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int slot,category,variant,subtype;in>>slot>>category>>variant>>subtype;check(bool(in)&&category==5&&variant==90&&subtype==1,"ordinary battery identity");++rows;}check(rows==6,"six source slots");
 for(int hz:{30,60,120}){BatteryTiming t;t.appear();for(int i=0;i<hz*25/30;++i)t.advance(1.f/hz);check(!t.collectible(),"no collection before Drop26");for(int i=0;i<hz/30;++i)t.advance(1.f/hz);check(t.collectible(),"Drop26 admission");t.collect();for(int i=0;i<hz/2-1;++i)t.advance(1.f/hz);check(t.phase==BatteryTiming::Phase::Collect,"collect lasts15 source frames");t.advance(1.f/hz);check(t.phase==BatteryTiming::Phase::Gone,"collect cleanup");}
 std::cout<<"PASS183 native numeric/stock cases and30/60/120Hz animation gates\n";
}
void gameplay(float scale,int lo,int hi){
 auto s=canyon(scale,lo,hi);const int shop=s.arena.shopRoom;check(s.hasSourceShop(shop)&&s.upgradedShop.size()==2,"naturally selected base-level battery pair");s.jumpDebug(shop);s.step({});check(s.batteryPickups.size()==1,"battery actor delivered");const auto at=s.batteryPickups[0].position;const int slot=s.batteryPickups[0].shopSlot;check(!s.arena.blocked(at,.48f)&&!s.arena.path(s.player.position,at,.48f).empty(),"battery reachable");s.moneyCollected=30;s.player.position=at;ticks(s,3);check(!s.upgradedShop[size_t(slot)].sold&&s.moneySpent==0,"no active means no purchase");
 equip(s,IvBagKey);ticks(s,3);check(s.moneySpent==0,"IV Bag cannot take battery");equip(s,YumHeartKey);ticks(s,3);check(s.moneySpent==0&&s.activeItem->charge==4,"full active cannot buy battery");check(s.useActiveItem()&&s.activeItem->charge==0,"real active use discharges");
 s.moneyCollected=0;ticks(s,3);check(s.activeItem->charge==0&&!s.upgradedShop[size_t(slot)].sold,"insufficient money preserves battery");s.moneyCollected=30;s.batteryTuning.enabled=false;ticks(s,3);check(s.moneySpent==0,"live disable preserves stock");s.batteryTuning.enabled=true;s.batteryTuning.charges=2;s.batteryTuning.price=7;const auto cost=s.upgradedShopPrice(slot);ticks(s,3);check(s.activeItem->charge==2&&s.moneySpent==uint64_t(cost)&&s.upgradedShop[size_t(slot)].sold,"touch purchase applies live amount and price");ticks(s,60);check(s.batteryPickups.empty()&&s.moneySpent==uint64_t(cost),"cleanup and once-only payment");
 s.enterRoom(0);s.enterRoom(shop);ticks(s,3);check(s.batteryPickups.empty(),"revisit does not respawn sold battery");s.resizeRooms(scale,lo,hi,.27f);check(s.activeItem->charge==2&&s.batteryTuning.charges==2&&s.batteryTuning.price==7,"Apply preserves active charge and custom controls");s.jumpDebug(s.arena.shopRoom);ticks(s,3);check(s.batteryPickups.size()==1,"explicit floor reset replenishes shop");
 s.batteryTuning={};equip(s,BookOfShadowsKey);check(s.useActiveItem(),"Book use");s.player.position=s.batteryPickups[0].position;s.moneyCollected=60;const auto start=s.moneySpent;ticks(s,3);check(s.activeItem->charge==3&&s.moneySpent>start,"ordinary six-charge battery caps Book at3");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.activeItem->charge==3&&s.batteryTuning==BatteryTuning{},"floor transition preserves charged active and settings");
 std::cout<<"PASS natural purchase, capacity/funds/IV Bag, live tuning, revisit, Apply and floor size "<<scale<<'\n';
}
void upgraded(){auto s=canyon(1,7,9,68);s.configureShopLevel(4);s.jumpDebug(s.arena.shopRoom);s.step({});check(s.batteryPickups.size()==1&&s.upgradedShop.size()==6,"level4 now supports selected battery slot");equip(s,YumHeartKey);s.useActiveItem();s.grant({"isaac",ItemKind::Collectible,64});s.moneyCollected=30;s.player.position=s.batteryPickups[0].position;const int slot=s.batteryPickups[0].shopSlot;check(s.upgradedShopPrice(slot)==3,"Steam Sale battery costs3");ticks(s,2);check(s.moneySpent==3&&s.activeItem->charge==4,"discount and capped recharge consumed together");std::cout<<"PASS upgraded stock and Steam Sale\n";}
void persistence(){
 auto dir=std::filesystem::temp_directory_path()/("deathward-battery-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a15-donation-milestones/review-preset.json",defaultMechanics()->fingerprint());check(p.batteries==BatteryTuning{}&&p.defaultZoomPercent==165,"schema59 migration preserves settings");
 for(bool enabled:{false,true})for(int charge:{1,6,12})for(int price:{0,5,30}){p.batteries={enabled,charge,price};p.save(dir/"preset.json");const auto q=BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint);check(q.batteries==p.batteries&&q.revision()==p.revision(),"schema60 roundtrip");}
 auto bad=p;bad.batteries.charges=13;bool rejected=false;try{bad.save(dir/"preset.json");}catch(...){rejected=true;}check(rejected&&BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).batteries==p.batteries,"invalid export atomic");std::filesystem::remove_all(dir);std::cout<<"PASS59 migration,18 schema60 combinations and atomic rejection\n";
}
}
int main(){try{std::cout<<std::unitbuf;native();for(auto [scale,lo,hi]:{std::tuple{.75f,5,5},std::tuple{1.f,7,9},std::tuple{1.5f,10,10}})gameplay(scale,lo,hi);upgraded();persistence();std::cout<<"PASS shop battery delivery\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
