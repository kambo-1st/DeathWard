#include "items/Items.hpp"
#include "combat/BlueFly.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
using namespace dw;
namespace {
const ItemKey Halo{"isaac",ItemKind::Collectible,10};
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>std::max(.00005f,std::abs(b)*.000005f))throw std::runtime_error(m);}
Simulation make(uint64_t seed=9,int pool=1,float scale=1.1f,int lo=7,int hi=9) {return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,pool);}
int treasure(const Simulation &s){for(int i=0;i<s.arena.roomCount();++i)if(s.hasSourceTreasure(i))return i;throw std::runtime_error("treasure missing");}
void native() {
 const auto folder=Root/"docs/reports/isaac-first-floor-parity/pw-f02-halo-of-flies/source";
 std::ifstream counts(folder/"native-count.csv");std::string line;std::getline(counts,line);int n=0;
 while(std::getline(counts,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);unsigned copies,count;row>>copies>>count;check(sourceHaloCount(copies)==count,"native capped ordinary count");++n;}check(n==9,"all count cases");
 std::ifstream angles(folder/"native-orbit.csv");std::getline(angles,line);n=0;
 while(std::getline(angles,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float phase,value;uint32_t frame;int parity;row>>phase>>frame>>parity>>value;near(sourceHaloAngle(phase,frame,parity),value,"native orbit angle");++n;}check(n==36,"all angle cases");
 std::ifstream contacts(folder/"native-npc-contact.csv");std::getline(contacts,line);n=0;
 while(std::getline(contacts,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int kind,variant,killed;row>>kind>>variant>>killed;check(sourceBlueFlyInstakill({kind,variant,0})==bool(killed),"shared native contact kill identities");++n;}check(n==22,"all NPC cases");
 std::cout<<"PASS 9 native copy counts,36 orbit angles,22 NPC decisions\n";
}
void lifecycle() {
 int seed=0,owner=-1;
 for(int candidate=1;candidate<=100;++candidate){auto s=make(candidate);const int at=treasure(s);if(s.treasureUpgradeItem(at)==10){seed=candidate;owner=at;break;}}
 check(seed,"natural Halo witness");auto s=make(seed);s.jumpDebug(owner);
 std::cout<<"HALO_WITNESS seed="<<seed<<" room="<<owner+1<<'\n';
 check(s.content->item(Halo)->category==CollectibleCategory::Familiar,"familiar category");
 const auto attack=primaryPlayerAttack(s,s.player.shotDamage,false);const float pace=s.player.walkingSpeed();
 s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);check(s.collectTreasureUpgrade()&&!s.collectTreasureUpgrade(),"ordinary once-only pedestal");s.step({});
 check(s.haloFlies.size()==2&&s.livingEnemies()==0,"two persistent friendly orbiters");near(s.player.walkingSpeed(),pace,"walking retained");near(primaryPlayerAttack(s,s.player.shotDamage,false).damage,attack.damage,"weapon damage retained");
 const auto id=s.haloFlies[0].id;s.jumpDebug(0);s.step({});check(s.haloFlies.size()==2&&s.haloFlies[0].id==id&&s.haloFlies[0].room==0,"room transfer stable identity");check(distance(s.haloFlies[0].position,s.haloFlies[0].previous)<.2f,"no cross-room collision chord");s.jumpDebug(owner);s.step({});check(!s.rewardAvailable(owner),"revisit spent");
 for(int i=0;i<6;++i)s.grant(Halo);s.step({});check(s.haloFlies.size()==10,"source ten-fly cap");
 s.items.resize(1);s.step({});check(s.haloFlies.size()==2&&s.haloFlies[0].id==id,"copy removal stable");
 s.grant({"isaac",ItemKind::Collectible,8});s.grant({"isaac",ItemKind::Collectible,45});s.heldTrinket=WhipWormKey;s.haloOfFlies={.8f,1.2f,.9f};
 s.resizeRooms(1.11f,7,9,.26f,true,1,true,true,true,true,true,1,5);s.step({});check(s.haloFlies.size()==2&&s.haloOfFlies.orbitSpeed==.8f&&s.brotherBobbies.size()==1&&s.heldTrinket==WhipWormKey,"Apply preserves build and settings");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor(),"next floor");s.step({});check(s.haloFlies.size()==2&&s.haloOfFlies.orbitRadius==1.2f,"floor reconstruction");s.items.clear();s.step({});check(s.haloFlies.empty(),"last copy removal");
 for(auto [scale,lo,hi]:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}}){auto test=make(seed,5,scale,lo,hi);test.jumpDebug(treasure(test));test.player.position=pedestalGeometry::approach(test.rewardPosition(test.room),{1,0,0},.85f);check(!test.arena.blocked(test.player.position,.48f)&&test.collectTreasureUpgrade(),"three sizes reachable pedestal");test.step({});check(test.haloFlies.size()==2,"three sizes ownership");}
 std::cout<<"PASS acquisition/copies/room/revisit/Apply/floor/removal and three canyon sizes\n";
}
Simulation fixture(){auto s=make(9,5);s.jumpDebug(treasure(s));s.player.position=add(s.rewardPosition(s.room),{0,.85f,4});s.grant(Halo);s.step({});return s;}
Vector3 nextOffset(const Simulation &s,float dt) {
 const auto d=mul(sub(s.haloFlies[0].position,s.player.position),1/(HaloSpace*s.haloOfFlies.orbitRadius));
 const float angle=std::atan2(d.z/HaloSourceRadiusZ,d.x/HaloSourceRadiusX)-HaloSourceOffset;
 return mul(sourceHaloOffset(angle-dt*30*HaloSourceSpeed*Pi*.5f*s.haloOfFlies.orbitSpeed),HaloSpace*s.haloOfFlies.orbitRadius);
}
void collision() {
 for(int hz:{30,60,120}) {
  const float dt=1.f/hz;auto s=fixture();const auto d=nextOffset(s,dt);Projectile p;p.id=900000;p.position=add(s.player.position,mul(unit(d),3));p.velocity=mul(unit(d),-400);p.life=10;p.radius=.08f;p.hostile=true;p.damage=10;s.projectiles.push_back(p);const auto hp=s.player.hp;s.step({},dt);
  check(s.projectiles.empty()&&s.player.hp==hp&&s.haloFlies.size()==2&&s.haloFlies[0].blockedShots==1,"swept fast shot intercepted before player, familiar survives");
  s=fixture();const auto radial=unit(nextOffset(s,dt));const Vector3 gap{-radial.z,0,radial.x};p.position=add(s.player.position,mul(gap,3));p.velocity=mul(gap,-400);s.projectiles.push_back(p);s.step({},dt);check(s.player.hp<6&&s.haloFlies[0].blockedShots==0&&s.haloFlies[1].blockedShots==0,"gap is vulnerable, no global shield");
  s=fixture();p.hostile=false;p.position=add(s.player.position,mul(unit(nextOffset(s,dt)),2));p.velocity=mul(unit(nextOffset(s,dt)),-100);p.attack.canonicalFlight=false;s.projectiles.push_back(p);s.step({},dt);check(s.haloFlies[0].blockedShots==0&&s.haloFlies[1].blockedShots==0,"friendly bullets pass");
  s=fixture();p.hostile=true;p.ignoresPlayer=true;p.position=add(s.player.position,mul(unit(nextOffset(s,dt)),3));p.velocity=mul(unit(nextOffset(s,dt)),-400);s.projectiles.push_back(p);s.step({},dt);check(s.haloFlies[0].blockedShots==0&&s.player.hp==6,"player-ignoring shot bypass");
 }
 auto s=fixture();const auto d=nextOffset(s,Tick);const auto block=add(s.player.position,mul(unit(d),2));s.arena.obstacles.push_back({sub(block,{.2f,.8f,.2f}),add(block,{.2f,.8f,.2f})});s.arena.rebuildWalls();Projectile p;p.position=add(s.player.position,mul(unit(d),3));p.velocity=mul(unit(d),-400);p.life=10;p.radius=.08f;p.hostile=true;p.damage=10;s.projectiles.push_back(p);s.step({});check(s.haloFlies[0].blockedShots==0&&s.player.hp==6,"earlier wall wins over orbital");
 for(MonsterId type: {MonsterId{13,0,0},MonsterId{14,0,0},MonsterId{14,2,0},MonsterId{10,1,0}}) {
  s=fixture();const auto id=s.spawnMonster(type,add(s.player.position,nextOffset(s,Tick)));auto *e=s.findEnemy(id);check(e,"NPC fixture spawn");e->state=EnemyState::Stunned;e->stateTime=1000;const auto hp=e->hp;s.step({});e=s.findEnemy(id);
  if(sourceBlueFlyInstakill(type))check(!e||!e->alive,"native fly identity killed through actual damage lifecycle");else check(e&&e->alive&&e->hp==hp,"ordinary contact deals no damage");check(s.haloFlies.size()==2,"fly contact never consumes Halo");
 }
 std::cout<<"PASS swept interception/gaps/friendly/ignore at30/60/120Hz, earlier wall, real NPC kill/no-damage\n";
}
void orbit() {
 Vector3 end{};
 for(int hz:{30,60,120}) {auto s=fixture();const auto start=s.haloFlies[0].position;
  for(int i=0;i<hz;++i)s.step({},1.f/hz);
  if(hz==30)end=sub(s.haloFlies[0].position,s.player.position);else {const auto d=sub(s.haloFlies[0].position,s.player.position);near(d.x,end.x,"partition orbit x");near(d.z,end.z,"partition orbit z");}
  check(distance(start,s.haloFlies[0].position)>.5f,"visible orbit advances");const auto before=s.haloFlies[0].position;s.rewardOpen=true;for(int i=0;i<hz;++i)s.step({},1.f/hz);check(distance(before,s.haloFlies[0].position)==0,"modal freezes orbital");s.rewardOpen=false;
  s.haloOfFlies.orbitSpeed=.25f;const auto expected=add(s.player.position,nextOffset(s,1.f/hz));s.step({},1.f/hz);near(s.haloFlies[0].position.x,expected.x,"speed edit preserves phase");near(s.haloFlies[0].position.z,expected.z,"speed edit preserves phase z");
 }
 std::cout<<"PASS orbit partitions/pause/live phase continuity\n";
}
void presets() {
 const auto dir=std::filesystem::temp_directory_path()/("deathward-halo-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);const auto path=dir/"preset.json";
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&!p.haloOfFlies.custom()&&p.playerSpeed==1,"schema5 preserves accepted settings");
 for(int pool=0;pool<=5;++pool){p.treasureCollectiblePool=pool;p.haloOfFlies={.8f,1.2f,.9f};p.brotherBobby.damage=1.2f;p.trinkets.whipStrength=.5f;p.save(path);check(BalancePreset::load(path,p.mechanicsFingerprint).json()==p.json(),"schema41 full roundtrip all modes and categories");}
 auto bad=p.json();const auto at=bad.find("\"orbit_speed\": 0.8");check(at!=std::string::npos,"bad-field fixture");bad.replace(at,18,"\"orbit_speed\": 9.0");std::ofstream(path)<<bad;bool rejected=false;try{BalancePreset::load(path,p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"reject invalid orbital override");
 auto s=fixture();s.grant(Halo);{CampaignStore store(dir/"campaign.save");const auto id=store.begin(9);auto record=s.summary();record.id=id;store.checkpoint(record);}
 {CampaignStore store(dir/"campaign.save");check(std::count(store.data().pending->items.begin(),store.data().pending->items.end(),Halo)==2,"Halo copies serialized in real campaign record");store.recover();check(std::count(store.data().history.back().items.begin(),store.data().history.back().items.end(),Halo)==2,"interrupted history preserves Halo copies, not live resume");}
 std::filesystem::remove_all(dir);
 std::cout<<"PASS accepted preset migration, full roundtrip, invalid rejection and campaign interruption history\n";
}
}
int main(){try{native();lifecycle();collision();orbit();presets();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
