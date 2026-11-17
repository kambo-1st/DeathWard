#include "items/Items.hpp"
#include "items/CricketHead.hpp"
#include "items/SadOnion.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include "world/SourceTreasureStock.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
const ItemKey Cricket{"isaac",ItemKind::Collectible,4},Onion{"isaac",ItemKind::Collectible,1};
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>std::max(.00003f,std::abs(b)*.000003f))throw std::runtime_error(m);}
Simulation make(uint64_t seed=69,int pool=1,float scale=1.1f,int low=7,int high=9) {
 return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,low,high,.26f,true,1,true,true,true,true,true,true,1,pool);
}
int treasure(const Simulation &s){for(int i=0;i<s.arena.roomCount();++i)if(s.hasSourceTreasure(i))return i;throw std::runtime_error("no treasure");}
void native() {
 auto file=std::ifstream(Root/"docs/reports/isaac-first-floor-parity/d11b-treasure-variety/source/native-damage.csv");std::string line;std::getline(file,line);int n=0;
 while(std::getline(file,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float raw,contribution,before,damage;size_t copies;
  check(bool(row>>raw>>copies>>contribution>>before>>damage),"damage evidence row");near(sourceOrdinaryDamage(raw+contribution),before,"native raw curve");near(cricketHeadDamage(sourceOrdinaryDamage(raw),copies),damage,"native damage through inverse adapter");++n;}
 check(n==32,"all native damage evidence");
 file=std::ifstream(Root/"docs/reports/isaac-first-floor-parity/d11b-treasure-variety/source/native-tears.csv");std::getline(file,line);n=0;
 while(std::getline(file,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float raw,damage,scale,height,velocity,knockback,falling;int copies;
  check(bool(row>>raw>>copies>>damage>>scale>>height>>velocity>>knockback>>falling),"tear evidence row");near(sourceOrdinaryTearScale(damage),scale,"whole native tear-size result");near(velocity,1,"source velocity unchanged");near(knockback,1.7f,"source knockback parameter unchanged");++n;}
 check(n==32,"all whole tear results");
 file=std::ifstream(Root/"docs/reports/isaac-first-floor-parity/d12f-shop-collectibles/source/native-choice.csv");std::getline(file,line);n=0;
 while(std::getline(file,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);uint32_t seed,after;int id;check(bool(row>>seed>>after>>id),"choice evidence");check(sourceTreasureChoice(seed)==(id==64?1:id==250?4:0),"same native weighted index in treasure XML order");++n;}check(n==524,"native choice boundary cases");
 for(float base:{.1f,3.5f,8.f,50.f}) {check(cricketHeadDamage(base,0)==base&&cricketHeadDamage(base,5,0)==base,"unowned and zero strength exact");check(cricketHeadDamage(base,1)>=base,"positive upgrade");}
 near(cricketHeadDamage(3.5f,1),6.640783f,"source starting Cricket damage");
 std::cout<<"PASS 32 damage / 32 full tear outputs / 524 native weighted-index cases\n";
}
void ownership() {
 auto s=make(69,2);s.applyCombatBalance(3.5f,1);s.canonicalShooting=true;
 const int owner=treasure(s);s.jumpDebug(owner);const auto at=s.rewardPosition(owner);
 check(planarDistance(at,s.arena.rooms[size_t(owner)].center)<.00001f&&s.arena.blocked(at,.48f),"centered solid pedestal");
 s.player.position=pedestalGeometry::approach(at,{1,0,0},.85f);const auto before=primaryPlayerAttack(s,s.player.shotDamage,false);const auto cadence=primaryCadence(s);s.player.fireCooldown=.31f;
 check(s.collectTreasureUpgrade()&&s.itemStacks(Cricket)==1&&!s.collectTreasureUpgrade(),"one Cricket, once");const auto after=primaryPlayerAttack(s,s.player.shotDamage,false);
 near(after.damage,cricketHeadDamage(3.5f,1)*3.2f,"primary attack internal conversion");check(after.radius>before.radius&&after.speed==before.speed&&after.life==before.life&&after.maxDistance==before.maxDistance&&primaryCadence(s)==cadence,"only damage and derived size change");check(s.player.fireCooldown==.31f&&s.player.shotDamage==11.2f,"wait and accepted base stay intact");
 Event shot;shot.type=EventType::Shot;shot.position=s.player.position;shot.direction={1,0,0};shot.damage=after.damage;shot.attack=after;s.queueRoot(shot);s.drainEvents();check(!s.projectiles.empty(),"real emitted attack");const auto born=s.projectiles.back();
 s.cricketHeadStrength=0;near(primaryPlayerAttack(s,s.player.shotDamage,false).damage,before.damage,"live disabled effect for new attacks");check(s.projectiles.back().damage==born.damage&&s.projectiles.back().radius==born.radius,"flying projectile retains birth");
 s.cricketHeadStrength=1;s.grant(Cricket);near(primaryPlayerAttack(s,s.player.shotDamage,false).damage,cricketHeadDamage(3.5f,2)*3.2f,"duplicate flat contributions, one multiplier");
 const float damage=primaryPlayerAttack(s,s.player.shotDamage,false).damage;s.grant(Onion);check(primaryCadence(s)<cadence,"Onion independent cadence");near(primaryPlayerAttack(s,s.player.shotDamage,false).damage,damage,"Onion does not double damage");
 s.jumpDebug(0);s.jumpDebug(owner);check(!s.rewardAvailable(owner),"revisit never repays");
 s.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,true,true,1,0);check(s.treasureUpgradeItem(owner)==1&&s.itemStacks(Cricket)==2&&s.cricketHeadStrength==1&&s.rewardAvailable(owner),"explicit Apply replaces offering, keeps build");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor()&&s.itemStacks(Cricket)==2&&s.treasureCollectiblePool==0,"next-floor owned effect retained");near(primaryPlayerAttack(s,s.player.shotDamage,false).damage,damage,"next-floor damage retained");
 auto gated=make(69,2);gated.jumpDebug(treasure(gated));gated.player.position=pedestalGeometry::approach(gated.rewardPosition(gated.room),{1,0,0},.85f);gated.items.assign(256,Onion);check(!gated.collectTreasureUpgrade()&&!gated.rooms[size_t(gated.room)].rewardTaken,"capacity gate atomic");
 std::cout<<"PASS actual attack / size / birth / duplicate / Onion / revisit / Apply / floor / capacity\n";
}
void coverage() {
 bool onion=false,cricket=false;int n=0;
 for(uint64_t seed:{1ULL,4ULL,7ULL,32ULL,69ULL})for(auto dim:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}}){auto [scale,low,high]=dim;auto s=make(seed,1,scale,low,high);int room=treasure(s);s.jumpDebug(room);int item=s.treasureUpgradeItem(room);check(item==1||item==4||item==8||item==10||item==45,"eligible pool");onion|=item==1;cricket|=item==4;const auto at=pedestalGeometry::approach(s.rewardPosition(room),{1,0,0},.85f);check(!s.arena.blocked(at,.48f)&&!s.arena.path(s.player.position,at,.48f).empty(),"reachable pedestal");if(scale==1.1f)std::cout<<"WITNESS seed="<<seed<<" room="<<room+1<<" item="<<item<<'\n';++n;}
 check(onion&&cricket,"both natural options");std::cout<<"PASS "<<n<<" natural size/placement cases\n";
}
void presets() {
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&p.treasureCollectiblePool==1&&p.cricketHeadStrength==1,"accepted old preset preserved and migrated");
 auto path=std::filesystem::temp_directory_path()/("deathward-cricket-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json");
 for(int mode:{0,1,2})for(float strength:{0.f,.95f,1.f,2.f}){p.treasureCollectiblePool=mode;p.cricketHeadStrength=strength;p.save(path);check(BalancePreset::load(path,p.mechanicsFingerprint).json()==p.json(),"exact selection/strength roundtrip");}
 for(auto invalid:{std::pair{"\"treasure_collectible_pool\": 2","\"treasure_collectible_pool\": 2.5"},std::pair{"\"cricket_head_strength\": 2","\"cricket_head_strength\": 2.1"}}){auto bad=p.json();auto at=bad.find(invalid.first);check(at!=std::string::npos,"bad value located");bad.replace(at,std::string(invalid.first).size(),invalid.second);std::ofstream(path)<<bad;bool rejected=false;try{BalancePreset::load(path,p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"invalid preset refused");}
 std::filesystem::remove(path);std::cout<<"PASS old preset / 12 combinations / invalid refusal\n";
}
}
int main(){try{native();ownership();coverage();presets();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
