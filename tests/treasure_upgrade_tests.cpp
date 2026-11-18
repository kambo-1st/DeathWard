#include "items/Items.hpp"
#include "items/SadOnion.hpp"
#include "world/PedestalGeometry.hpp"
#include "core/BalancePreset.hpp"
#include <fstream>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
const ItemKey Onion{"isaac",ItemKind::Collectible,1};
void check(bool ok,const char *m){if(!ok)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>.00002f){std::cerr<<a<<" != "<<b<<'\n';throw std::runtime_error(m);}}
Simulation generated(uint64_t seed=69,float scale=1.1f,int min=7,int max=9,float routes=.26f) {
 return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,min,max,routes,true,1,true,true,true);
}
int treasure(const Simulation &r){for(int i=0;i<r.arena.roomCount();++i)if(r.hasSourceTreasure(i))return i;throw std::runtime_error("no treasure");}
Vector3 contact(const Simulation &r,int room) {
 return pedestalGeometry::approach(r.rewardPosition(room),{1,0,0},.85f);
}
void nativeMath(){
 std::ifstream file(std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d11a-treasure-upgrade/source/native-tears.csv");
 check(bool(file),"native cases exist");std::string line;std::getline(file,line);int cases=0;
 while(std::getline(file,line)){
  std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float raw,contribution,total,delay,rate;size_t copies;
  check(bool(row>>raw>>copies>>contribution>>total>>delay>>rate),"valid native row");
  near(sourceOrdinaryTears(total),rate,"original code rate agreement");
  const float base=sourceOrdinaryTears(raw);
  if(base<5)near(sadOnionTears(base,copies),rate,"inverse accepted-baseline adapter matches uncapped source cases");
  ++cases;
 }
 check(cases==60,"all native cases consumed");
 for(float base:{0.f,.1f,.5f,1.9272734f,30.f/11,4.9f,5.f,10.f}){
  check(sadOnionTears(base,0)==base&&sadOnionTears(base,1,0)==base,"no phantom modifier");
  check(sadOnionTears(base,1)>=base,"upgrade never reduces custom base");
 }
 near(sadOnionTears(30.f/11,1),3.4451733f,"one onion source base");
}
void centeredPedestals(const Simulation &r) {
 for(int i=0;i<r.arena.roomCount();++i) {
  const auto &room=r.arena.rooms[size_t(i)];if(room.kind!=RoomKind::Power)continue;
  const auto at=r.rewardPosition(i);check(planarDistance(at,room.center)<.00001f,"pedestal exactly centered");
  for(float x:{-2.f,-1.f,0.f,1.f,2.f})for(float z:{-2.f,-1.f,0.f,1.f,2.f}) {
   const Vector3 p{at.x+x,.85f,at.z+z};
   const bool inBody=std::abs(x)<=1&&std::abs(z)<=1;
   if(r.arena.blocked(p,.48f)!=inBody) {
    std::cerr<<"CLEARANCE seed="<<r.expedition.seed<<" floor="<<r.floor<<" room="<<i<<" scale="<<r.roomSizeScale<<" routes="<<r.routeLengthScale<<" offset="<<x<<","<<z<<" height="<<(r.arena.canyon?r.arena.canyon->height(p.x,p.z):0)<<" contains="<<r.arena.contains(p)<<" at="<<at.x<<","<<at.z<<"\n";
    for(auto b:r.arena.walls)if(sphereBox(p,.48f,b))std::cerr<<"WALL "<<b.min.x<<","<<b.min.z<<" -> "<<b.max.x<<","<<b.max.z<<"\n";
   }
   check(r.arena.blocked(p,.48f)==inBody,"solid pedestal with clear surrounding approaches");
   if(r.arena.canyon)check(std::abs(r.arena.canyon->height(p.x,p.z))<.08f,"pedestal clearance has flat floor");
  }
  for(const auto &coin:r.moneyPickups)check(planarDistance(at,coin.position)>2.4f,"pickup does not overlap pedestal");
  for(const auto &key:r.arena.keys)check(planarDistance(at,key.position)>2.4f,"mandatory key does not overlap pedestal");
 }
}
void laterPedestals() {
 for(uint64_t seed:{1ULL,69ULL,129ULL})for(int floor:{1,2,ExpeditionPlan(seed,false,WitnessAccount::None,ExpeditionPacing::Compact).floorCount-1}) {
  Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true,1,true,true,true);
  centeredPedestals(r);
 }
}
void collection(){
 int cases=0;
 for(uint64_t seed:{1ULL,69ULL,129ULL})for(auto dim:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}})for(float routes:{.25f,1.f,2.f}){
  auto [scale,min,max]=dim;auto r=generated(seed,scale,min,max,routes);centeredPedestals(r);const int room=treasure(r);r.jumpDebug(room);
  const auto p=contact(r,room);check(!r.arena.path(r.player.position,p,.48f).empty(),"pedestal edge reachable from room entry");
  check(!r.collectTreasureUpgrade(),"cannot collect remotely");r.player.position=p;r.player.position.y=.85f;
  const float base=r.player.attributes.tearsPerSecond;const auto attack=primaryPlayerAttack(r,r.player.shotDamage,false);const auto health=r.player.hp;
  r.player.fireCooldown=.31f;check(r.collectTreasureUpgrade(),"touch pays upgrade");
  check(r.itemStacks(Onion)==1&&r.powerUpsTaken==1&&r.rooms[size_t(room)].rewardTaken&&!r.rewardOpen,"single owned item without choice menu");
  check(r.player.attributes.tearsPerSecond==base&&r.player.fireCooldown==.31f&&r.player.hp==health,"base stat, wait and health retained");
  const auto after=primaryPlayerAttack(r,r.player.shotDamage,false);
  check(after.speed==attack.speed&&after.maxDistance==attack.maxDistance&&after.damage==attack.damage,"only Tears affected");
  near(1/primaryCadence(r),3.4451733f,"actual item consumer");
  check(!r.collectTreasureUpgrade(),"cannot repay");r.jumpDebug(0);r.jumpDebug(room);r.player.position=p;
  check(!r.collectTreasureUpgrade()&&r.itemStacks(Onion)==1,"revisit persistent");++cases;
 }
 std::cout<<"PASS "<<cases<<" generated geometry/route collection cases\n";
 auto r=generated();int room=treasure(r);r.jumpDebug(room);r.player.position=contact(r,room);
 r.roomClear=false;check(!r.collectTreasureUpgrade(),"combat gate");r.roomClear=true;
 r.rewardOpen=true;check(!r.collectTreasureUpgrade(),"modal gate");r.rewardOpen=false;
 r.dead=true;check(!r.collectTreasureUpgrade(),"death gate");r.dead=false;
 check(r.collectTreasureUpgrade(),"rejected checks did not consume");r.sadOnionStrength=.5f;
 r.resizeRooms(1.2f,7,9,.26f,true,1,true,false);
 check(!r.sourceTreasureUpgrade&&r.sadOnionStrength==.5f&&r.itemStacks(Onion)==1,"Apply keeps owned build and strength while changing offer");
 r.resizeRooms(1.1f,7,9,.26f,true,1,true,true);
 check(r.sourceTreasureUpgrade&&r.itemStacks(Onion)==1,"regeneration explicitly resets offering, not build");
 r.jumpDebug(r.finalRoom());r.clearRoomDebug();r.floorExitRequested=true;check(r.advanceFloor(),"floor advances");
 check(r.sourceTreasureUpgrade&&r.sadOnionStrength==.5f&&r.itemStacks(Onion)==1,"floor carries item and tuning");
 for(int i=0;i<r.arena.roomCount();++i)check(!r.hasSourceTreasure(i),"bounded offering only opening floor");
}
void firing(){
 auto r=generated();r.jumpDebug(treasure(r));r.player.position=contact(r,r.room);
 r.sourceTreasureUpgrade=false;Input input;input.fire=true;input.aimDirection=Vector3{1,0,0};r.step(input);
 check(r.stats.shots==1&&!r.projectiles.empty(),"actual baseline shot");const auto birth=r.projectiles.front().attack;const float wait=r.player.fireCooldown;
 r.sourceTreasureUpgrade=true;check(r.collectTreasureUpgrade(),"collect while firing wait active");
 check(r.player.fireCooldown==wait&&r.projectiles.front().attack.speed==birth.speed&&r.projectiles.front().attack.maxDistance==birth.maxDistance,"pickup retains emitted attack and wait");
 int ticks=0;while(r.stats.shots==1&&ticks<100){r.step(input);++ticks;}
 check(ticks>=21&&ticks<=23,"next shot respects pre-pickup wait");
 check(r.player.fireCooldown<.30f&&r.player.fireCooldown>.27f,"new wait uses source Tears");
 r.projectiles.clear();r.stats.shots=0;r.player.fireCooldown=0;
 for(int n=0;n<600;++n)r.step(input);
 check(r.stats.shots==35,"ten seconds upgraded emission cadence");
 r.grant(Onion);near(r.effectivePlayerStats().tearsPerSecond,4.3325763f,"owned copies compose once");
 for(int n=0;n<100;++n)near(r.effectivePlayerStats().tearsPerSecond,4.3325763f,"snapshot does not compound");
 r.sadOnionStrength=0;near(1/primaryCadence(r),30.f/11,"live disabled strength preserves ownership");
}
void solidPedestal(){
 auto r=generated();const int owner=treasure(r);r.jumpDebug(owner);
 const auto at=r.rewardPosition(owner);
 for(int n=0;n<16;++n) {
  const float angle=n*Pi/8;const Vector3 direction{std::cos(angle),0,std::sin(angle)};
  auto from=add(at,mul(direction,3)),to=sub(at,mul(direction,3));from.y=to.y=.85f;
  check(!r.arena.blocked(from,.48f)&&!r.arena.blocked(to,.48f),"approaches outside body");
  check(!r.arena.clear(from,to,.48f)&&r.arena.sight(from,to),"solid swept movement with clear projectile/sight path");
  auto route=r.arena.path(from,to,.48f);check(!route.empty(),"route around solid pedestal");
  auto previous=from;for(auto point:route){check(r.arena.clear(previous,point,.48f),"every route leg clears pedestal");previous=point;}
  r.player.position=from;r.player.dodge=0;r.player.dodgeCooldown=0;
  for(int tick=0;tick<90;++tick) {
   Input input;input.movement=unit(horizontal(sub(at,r.player.position)));r.step(input);
   check(!r.arena.blocked(r.player.position,.48f),"keyboard movement never enters pedestal");
  }
  check(planarDistance(r.player.position,at)>1.4f&&planarDistance(r.player.position,at)<1.65f,"walking reaches solid edge");
  for(int tick=0;tick<30;++tick) {
   Input input;input.movement=unit(horizontal(sub(at,r.player.position)));input.dodge=tick==0;r.step(input);
   check(!r.arena.blocked(r.player.position,.48f),"universal dodge cannot enter pedestal");
  }
  r.player.position=from;r.player.dodge=0;
  for(int tick=0;tick<360&&planarDistance(r.player.position,to)>.06f;++tick) {
   Input input;if(tick==0)input.moveTarget=to;r.step(input);
   check(!r.arena.blocked(r.player.position,.48f),"click route stays outside body");
  }
  check(planarDistance(r.player.position,to)<.06f,"actual click movement routes around base");
 }
 check(r.itemStacks(Onion)==1,"contact from multiple sides still pays once");
 r.jumpDebug(0);r.jumpDebug(owner);
 check(r.arena.blocked(at,.48f)&&!r.rewardAvailable(owner),"collected pedestal stays solid on revisit");
 r.resizeRooms(1.2f,7,9,.26f,true,1,true,true);r.jumpDebug(treasure(r));
 check(r.arena.blocked(r.rewardPosition(r.room),.48f)&&!r.arena.blocked(r.player.position,.48f),"Apply recreates solid base with safe entry");
 r.sourceTreasureUpgrade=false;
 for(int tick=0;tick<240&&!r.rewardOpen;++tick){Input input;if(tick==0)input.moveTarget=r.rewardPosition(r.room);r.step(input);}
 check(r.rewardOpen&&!r.arena.blocked(r.player.position,.48f),"legacy offering still opens outside solid base");
 std::cout<<"PASS 16-direction keyboard/dodge/click routing, persistent collision, safe Apply and legacy offering\n";
}
void presets(){
 auto dir=std::filesystem::temp_directory_path()/("deathward-d11a-preset-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
 const auto hash=defaultMechanics()->fingerprint();check(hash=="ff9ac597a5f92395","audited additive catalog hash including Mom's Eye");
 for(bool enabled:{false,true})for(float strength:{0.f,.55f,1.f,2.f}){
  BalancePreset p{1,hash};p.sourceTreasureUpgrade=enabled;p.sadOnionStrength=strength;p.save(dir/"test.json");
  auto q=BalancePreset::load(dir/"test.json",hash);check(p.revision()==q.revision(),"treasure preset roundtrip");
 }
 const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
 const auto old=BalancePreset::load(source,hash);check(old.sourceTreasureUpgrade&&old.sadOnionStrength==1&&old.defaultZoomPercent==165&&old.tearsPerSecond==1.9272734f,"old accepted preset migrates without retuning");
 bool rejected=false;try{BalancePreset::load(source,"arbitrary-new-content");}catch(...){rejected=true;}check(rejected,"arbitrary hash rejected");
 std::filesystem::remove_all(dir);
}
}
int main(){try{nativeMath();collection();laterPedestals();firing();solidPedestal();presets();std::cout<<"PASS native curve/inverse, generated collection, ownership/floor/Apply, emitted shots/wait/cadence and preset migration\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
