#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceRecordedShop.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void blast(Simulation &s,Vector3 at){Event e;e.type=EventType::Explosion;e.position=at;e.radius=2;e.damage=100;check(s.queueRoot(e),"blast queue");s.drainEvents();}
void native(){
 auto dir=Root/"docs/reports/isaac-first-floor-parity/d14a14-coin-donation/source";std::string line;int rows=0;
 std::ifstream f(dir/"native-deposits.csv");check(bool(f),"native deposits file");std::getline(f,line);
 while(std::getline(f,line)){
  std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);uint32_t seed,bank,bankAfter,flags,after;int run,held,runAfter,luck,state,cooldown;
  in>>seed>>bank>>run>>held>>bankAfter>>runAfter>>luck>>state>>cooldown>>flags>>after;check(bool(in),"deposit row");auto result=sourceDonation(seed,bank,run,held);
  check(bankAfter==bank+1&&runAfter==run+1&&int(result.luck)==luck&&cooldown==result.cooldown,"native counters/luck/cooldown");
  check(state==(result.jammed||result.overflow?3:1)&&flags==(result.overflow?1u<<17:result.jammed?1u<<18:0)&&seed==after,"native jam/overflow/RNG");++rows;
 }
 check(rows==1280,"1280 deposits");f.close();f.open(dir/"native-withdrawals.csv");std::getline(f,line);rows=0;
 while(std::getline(f,line)){
  std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);uint32_t seed,bank,afterBank,after;int withdrawn,coins;in>>seed>>bank>>withdrawn>>coins>>afterBank>>after;
  check(bool(in)&&sourceDonationWithdrawal(seed,bank)==withdrawn&&coins==std::max(0,withdrawn-1)&&afterBank==bank-withdrawn&&after==seed,"native withdrawal arithmetic/RNG");++rows;
 }check(rows==2048,"2048 withdrawals");std::cout<<"PASS 3328 native numeric comparisons\n";
}
Simulation fixture(uint32_t bank=0){
 WorldState world;world.donationBank=bank;Simulation s(69,1,world,MissionTheme::Mine,false);s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
 auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
 s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=false;s.player.position={0,.85f,0};s.roomClear=true;s.moneyCollected=20;
 s.coinDonationMachines.push_back({{4,.85f,0},0,42});s.coinDonationTuning.outcome=1;ticks(s,1);return s;
}
void donate(Simulation &s){s.player.position=add(s.coinDonationMachines[0].position,{1.06f,0,0});ticks(s,2);s.player.position={0,.85f,0};ticks(s,20);}
void lifecycle(){
 auto s=fixture();const auto health=s.player.hp;donate(s);check(s.donation.bank==1&&s.money()==19&&s.player.hp==health,"one coin, no blood, once-only credit");ticks(s,100);check(s.donation.bank==1,"no extra credit away");
 s.coinDonationTuning.outcome=2;donate(s);check(s.donation.jammed&&s.donation.bank==2&&s.money()==18,"forced next jam pays coin before jamming");auto at=s.coinDonationMachines[0].position;blast(s,at);check(!s.donation.excluded&&s.donation.bank==2&&s.arena.blocked(at,.48f),"native jam immunity keeps collider/bank");
 s.coinDonationTuning.outcome=1;donate(s);check(s.money()==18,"tuning cannot unjam");
 auto d=fixture(100);auto seed=d.coinDonationMachines[0].rng;const int amount=sourceDonationWithdrawal(seed,100);blast(d,d.coinDonationMachines[0].position);check(d.donation.bank==100-amount&&d.pendingBloodRewards.size()==size_t(amount-1)&&d.donation.excluded,"withdrawal with one lost coin");
 const auto after=d.donation.bank;blast(d,d.coinDonationMachines[0].position);check(d.donation.bank==after&&!d.arena.blocked(d.coinDonationMachines[0].position,.48f),"repeated blast cannot withdraw twice, collider removed");
 auto pending=fixture(30);pending.player.position=add(pending.coinDonationMachines[0].position,{1.06f,0,0});ticks(pending,2);check(pending.money()==19&&pending.donation.bank==30,"coin admission precedes credit");blast(pending,pending.coinDonationMachines[0].position);auto bank=pending.donation.bank;pending.player.position={0,.85f,0};ticks(pending,40);check(pending.donation.bank==bank,"blast cancels pending unpaid credit");
 auto paused=fixture();paused.player.position=add(paused.coinDonationMachines[0].position,{1.06f,0,0});ticks(paused,2);paused.rewardOpen=true;ticks(paused,100);check(paused.donation.bank==0,"paused phase cannot credit");paused.rewardOpen=false;paused.player.position={0,.85f,0};ticks(paused,20);check(paused.donation.bank==1,"committed phase completes away from contact");
 auto overflow=fixture(999);donate(overflow);check(overflow.donation.bank==1000&&overflow.donation.excluded&&overflow.moneyPickups.size()==15,"1000th donation yields 15 dimes");for(const auto &p:overflow.moneyPickups)check(p.sourceSubtype==3&&p.value==10,"overflow dime value");
 auto rollover=fixture(1000);donate(rollover);check(rollover.donation.bank==1001,"next expedition displays modulo bank, retains raw counter");
 std::cout<<"PASS admission, timing, jam, explosion, overflow and once-only accounting\n";
}
Simulation canyon(float scale,int lo,int hi,WorldState w={}) {return Simulation(68,1,w,MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{1});}
void rooms(float scale,int lo,int hi){
 auto s=canyon(scale,lo,hi);check(s.enterSourceRoomReview(RecordedShopReview),"direct shop");s.step({});check(s.coinDonationMachines.size()==1,"ordinary recorded shop machine");auto at=s.coinDonationMachines[0].position;check(s.arena.blocked(at,.48f),"register has collision");s.coinDonationTuning.outcome=2;s.moneyCollected=20;
 Input move;move.moveTarget=at;s.step(move);check(s.moveDestination().has_value(),"mouse approach route");for(int i=0;i<2000&&!s.donation.jammed;++i)s.step({});check(s.donation.jammed&&s.donation.bank==1,"walk to register and donate");
 s.enterRoom(0);s.enterRoom(s.arena.shopRoom);s.step({});check(s.coinDonationMachines[0].phase==CoinDonationMachine::Phase::Jammed,"revisit jam retained");
 s.resizeRooms(scale,lo,hi,.27f);check(s.donation.bank==1&&s.donation.jammed&&s.coinDonationTuning.outcome==2&&s.coinDonationMachines.size()==1&&s.coinDonationMachines[0].phase==CoinDonationMachine::Phase::Jammed,"Apply keeps campaign/expedition accounting and tuning");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.donation.bank==1&&s.donation.jammed&&s.coinDonationTuning.outcome==2,"floor transition keeps bank/jam/settings");
 std::cout<<"PASS natural shop / access / revisit / Apply / floor size "<<scale<<'\n';
}
void persistence(){
 const auto dir=std::filesystem::temp_directory_path()/("deathward-donation-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
 {CampaignStore store(dir/"campaign.save");auto id=store.begin(68);WorldState world=store.data().world;Simulation s(68,id,world);s.donation.bank=37;auto summary=s.summary();store.checkpoint(summary);store.checkpoint(summary);check(store.data().world.donationBank==37,"idempotent checkpoint");}
 {CampaignStore store(dir/"campaign.save");check(store.data().world.donationBank==37&&store.recover(),"interrupted bank recovered");auto id=store.begin(69);Simulation s(69,id,store.data().world);check(s.donation.bank==37&&!s.donation.jammed,"new expedition bank, fresh jam");s.donation.bank=29;store.resolve(s.summary(),EndReason::Death);check(store.data().world.donationBank==29,"withdrawal/death persisted");store.resolve(s.summary(),EndReason::Death);check(store.data().world.donationBank==29,"resolve idempotence");}
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a12-blood-machine-explosions/review-preset.json",defaultMechanics()->fingerprint());check(!p.coinDonation.custom()&&p.defaultZoomPercent==165,"schema57 migration");
 for(int mode=0;mode<3;++mode){p.coinDonation={false,true,1.2f,.75f,mode};p.save(dir/"preset.json");auto load=BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint);check(load.revision()==p.revision()&&load.defaultZoomPercent==165,"schema58 roundtrip");}
 auto bad=p;bad.coinDonation.jamScale=-1;bool rejected=false;try{bad.save(dir/"preset.json");}catch(...){rejected=true;}check(rejected&&BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).revision()==p.revision(),"invalid export atomic");
 std::filesystem::remove_all(dir);std::cout<<"PASS persistence, recovery, death, preset migration and atomic validation\n";
}
}
int main(){try{std::cout<<std::unitbuf;native();lifecycle();for(auto dims:{std::tuple{.75f,5,5},std::tuple{1.f,7,9},std::tuple{1.5f,10,10}}){auto [scale,lo,hi]=dims;rooms(scale,lo,hi);}persistence();std::cout<<"PASS coin donation delivery\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
