#include "items/Items.hpp"
#include "combat/BrotherBobby.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include "world/SourceTreasureStock.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
using namespace dw;
namespace {
const ItemKey Bobby{"isaac",ItemKind::Collectible,8};
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>std::max(.00005f,std::abs(b)*.000005f))throw std::runtime_error(m);}
Simulation make(uint64_t seed=9,int pool=1) {return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true,1,true,true,true,true,true,true,1,pool);}
int treasure(const Simulation &s){for(int i=0;i<s.arena.roomCount();++i)if(s.hasSourceTreasure(i))return i;throw std::runtime_error("treasure missing");}
void native() {
 auto file=std::ifstream(Root/"docs/reports/isaac-first-floor-parity/pw-f01-brother-bobby/source/native-follow.csv");std::string line;std::getline(file,line);int n=0;
 while(std::getline(file,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);std::string name;int step;float x,z,vx,vz,px,pz,nx,nz,nvx,nvz;
  check(bool(row>>name>>step>>x>>z>>vx>>vz>>px>>pz>>nx>>nz>>nvx>>nvz),"native follow row");const auto v=sourceBobbyFollow({vx,0,vz},{x-px,0,z-pz});near(v.x,nvx,"native follow vx");near(v.z,nvz,"native follow vz");near(x+v.x,nx,"native physics x");near(z+v.z,nz,"native physics z");++n;}
 check(n==315,"all native following states");
 file=std::ifstream(Root/"docs/reports/isaac-first-floor-parity/pw-f01-brother-bobby/source/native-birth.csv");std::getline(file,line);n=0;
 while(std::getline(file,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float pd,vx,vz,dx,dz,damage,scale,fall,base,tx,tz;check(bool(row>>pd>>vx>>vz>>dx>>dz>>damage>>scale>>fall>>base>>tx>>tz),"birth row");auto v=add(Vector3{dx*10,0,dz*10},Vector3{vx*1.2f,0,vz*1.2f});if(length(v)<10)v=mul(unit(v),10);near(v.x,tx,"native inheritance x");near(v.z,tz,"native inheritance z");near(damage,BobbySourceDamage,"independent native damage");near(scale,.8f,"native tear scale");near(fall,0,"fall acceleration");near(base,0,"falling base");++n;}
 check(n==48,"all native birth states");std::cout<<"PASS 315 source follow/free-physics and 48 independent tear births\n";
}
void lifecycle() {
 auto s=make();s.jumpDebug(treasure(s));check(s.treasureUpgradeItem(s.room)==8,"natural Bobby witness seed9");
 check(s.content->item(Bobby)->category==CollectibleCategory::Familiar,"real category metadata");
 const auto attack=primaryPlayerAttack(s,s.player.shotDamage,false);const auto pace=s.player.walkingSpeed();
 s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);check(s.collectTreasureUpgrade()&&!s.collectTreasureUpgrade(),"ordinary once-only acquisition");s.step({},Tick);
 check(s.brotherBobbies.size()==1&&s.livingEnemies()==0,"one friendly companion, no room seal");auto id=s.brotherBobbies[0].id;
 check(primaryPlayerAttack(s,s.player.shotDamage,false).damage==attack.damage&&s.player.walkingSpeed()==pace,"owner unchanged");
 const int owner=s.room;s.jumpDebug(0);s.step({},Tick);check(s.brotherBobbies.size()==1&&s.brotherBobbies[0].id==id&&s.brotherBobbies[0].room==0,"room transfer retains identity");s.jumpDebug(owner);s.step({},Tick);check(!s.rewardAvailable(owner),"revisit never repays");
 s.grant(Bobby);s.step({},Tick);check(s.brotherBobbies.size()==2&&s.brotherBobbies[0].id==id&&s.brotherBobbies[1].id!=id,"one actor per copy");s.items.pop_back();s.step({},Tick);check(s.brotherBobbies.size()==1&&s.brotherBobbies[0].id==id,"removal stable");
 s.brotherBobby={.8f,1.2f,.9f,1.1f};s.resizeRooms(1.11f,7,9,.26f,true,1,true,true,true,true,true,1,3);s.step({},Tick);check(s.brotherBobbies.size()==1&&s.brotherBobby.movement==.8f&&s.treasureUpgradeItem(s.room)==8,"Apply reconstructs ownership and preserves tuning");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor(),"advance floor");s.step({},Tick);check(s.brotherBobbies.size()==1&&s.brotherBobby.shotSpeed==1.1f,"floor continuity");
 s.items.clear();s.step({},Tick);check(s.brotherBobbies.empty(),"last copy removal");std::cout<<"PASS natural acquisition, copies/removal, room/revisit/Apply/floor ownership\n";
}
void cadenceAndShots() {
 for(int hz:{30,60,120}) {
  auto s=make(7,3);s.jumpDebug(treasure(s));s.grant(Bobby);s.player.fireCooldown=1000;s.godMode=true;
  Input input;input.fire=true;input.aimDirection=Vector3{1,0,0};
  auto file=std::ifstream(Root/"docs/reports/isaac-first-floor-parity/pw-f01-brother-bobby/source/native-cadence.csv");std::string line;std::getline(file,line);uint64_t shots=0;
  while(std::getline(file,line)) {std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int tick,held,fired,remaining,interval;row>>tick>>held>>fired>>remaining>>interval;input.fire=held;for(int sub=0;sub<hz/30;++sub)s.step(input,1.f/hz);shots+=fired;check(s.brotherBobbies[0].shots==shots,"source held/released cadence through actual step");near(s.brotherBobbies[0].cooldown,remaining/30.f,"retained native counter");}
  s.player.velocity={};s.brotherBobbies[0].position=add(s.player.position,{60*BobbySpace,0,0});s.brotherBobbies[0].nativeVelocity={};
  Vector3 expected{60,0,0},velocity{};
  for(int frame=0;frame<30;++frame) {
   velocity=sourceBobbyFollow(velocity,expected);expected=add(expected,velocity);
   for(int sub=0;sub<hz/30;++sub)s.step({},1.f/hz);
   const auto actual=mul(sub(s.brotherBobbies[0].position,s.player.position),1/BobbySpace);
   near(actual.x,expected.x,"actual fixed-clock follow position");
  }
  auto before=s.brotherBobbies[0];s.rewardOpen=true;for(int i=0;i<60;++i)s.step(input,1.f/hz);check(s.brotherBobbies[0].shots==before.shots&&s.brotherBobbies[0].cooldown==before.cooldown,"modal pauses familiar");s.rewardOpen=false;
  s.brotherBobby.interval=.25f;const auto wait=s.brotherBobbies[0].cooldown;check(wait==before.cooldown,"edit does not reset current wait");
  std::cout<<"PASS source cadence/release/pause at "<<hz<<"Hz\n";
 }
 auto s=make(7,3);s.jumpDebug(treasure(s));s.grant(Bobby);s.player.fireCooldown=1000;s.player.position=add(s.rewardPosition(s.room),{0,.85f,4});s.godMode=true;
 // A supplied stationary ordinary enemy isolates the familiar's real hit path.
 const auto enemy=s.spawnMonster({10,1,0},add(s.player.position,{4,0,0}));auto *e=s.findEnemy(enemy);check(e,"enemy");e->state=EnemyState::Stunned;e->stateTime=1000;const float hp=e->hp;
 Input fire;fire.fire=true;fire.aimDirection=Vector3{1,0,0};s.step(fire,Tick);s.step(fire,Tick);s.drainEvents();
 auto p=std::find_if(s.projectiles.begin(),s.projectiles.end(),[](const auto &p){return p.context.familiarAttack;});check(p!=s.projectiles.end(),"familiar projectile emitted");near(p->damage,11.2f,"source damage conversion");check(!p->hostile&&p->context.damageSource==DamageSource::Ally&&p->context.sourceItem==Bobby&&p->playerFlight&&p->playerFlight->reviewClockScale==1,"friendly birth provenance and independent native flight clock");
 const auto pid=p->id;const auto damage=p->damage;const auto speed=p->attack.speed;
 s.grant({"isaac",ItemKind::Collectible,4});s.grant({"isaac",ItemKind::Collectible,1});s.brotherBobby.damage=2;s.brotherBobby.shotSpeed=.5f;
 p=std::find_if(s.projectiles.begin(),s.projectiles.end(),[&](const auto &p){return p.id==pid;});check(p->damage==damage&&p->attack.speed==speed,"born shot frozen across player items/live familiar edits");
 for(int i=0;i<120&&s.findEnemy(enemy)->hp==hp;++i)s.step({},Tick);check(s.findEnemy(enemy)->hp<hp,"actual friendly shot hits NPC");near(hp-s.findEnemy(enemy)->hp,damage,"only familiar damage paid");check(s.player.hp==6&&s.stats.shots==0,"no owner damage or player cadence use");
 // The explicit lineage must bypass player projectile hooks even when owned.
 s.grant(ItemId::Split);Event hit;hit.type=EventType::ProjectileHit;hit.context.familiarAttack=true;hit.remainingLife=2;const auto split=s.stats.splits;dispatchItemEffects(s,hit);check(s.stats.splits==split,"no player split inheritance");
 // A friendly tear must expire on a real wall, and cannot hurt its owner.
 auto wallRun=make(7,3);wallRun.jumpDebug(treasure(wallRun));wallRun.grant(Bobby);wallRun.player.fireCooldown=1000;
 const auto cover=wallRun.rewardPosition(wallRun.room);wallRun.arena.obstacles.push_back({{cover.x-1,0,cover.z-1},{cover.x+1,2,cover.z+1}});wallRun.arena.rebuildWalls();
 wallRun.player.position=pedestalGeometry::approach(wallRun.rewardPosition(wallRun.room),{1,0,0},.85f);
 Input intoWall;intoWall.fire=true;intoWall.aimDirection=Vector3{-1,0,0};wallRun.step(intoWall,1.f/30);wallRun.drainEvents();
 check(!wallRun.projectiles.empty(),"wall shot emitted");for(int i=0;i<20;++i)wallRun.step({},Tick);
 check(std::none_of(wallRun.projectiles.begin(),wallRun.projectiles.end(),[](const auto &p){return p.context.familiarAttack&&p.alive;}),"familiar tears collide with tall solid cover");
 std::cout<<"PASS actual friendly damage/wall collision, independent/frozen birth and player-item isolation\n";
}
void presets() {
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&!p.brotherBobby.custom(),"historical accepted preset migration");
 const auto dir=std::filesystem::temp_directory_path()/("deathward-bobby-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);const auto path=dir/"preset.json";
 for(int mode=0;mode<4;++mode){p.treasureCollectiblePool=mode;p.brotherBobby={.25f,2,.9f,1.25f};p.inventoryBombs.damage=40;p.save(path);check(BalancePreset::load(path,p.mechanicsFingerprint).json()==p.json(),"full roundtrip including multiple object overrides");}
 auto bad=p.json();auto at=bad.find("\"movement\": 0.25");bad.replace(at,16,"\"movement\": 0.24");std::ofstream(path)<<bad;bool rejected=false;try{BalancePreset::load(path,p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"invalid tuning rejected");
 auto s=make();s.grant(Bobby);{CampaignStore c(dir/"campaign.save");const auto id=c.begin(7);auto summary=s.summary();summary.id=id;c.checkpoint(summary);}CampaignStore loaded(dir/"campaign.save");check(loaded.data().pending&&loaded.data().pending->items==s.items,"owned familiar key serialized in real campaign checkpoint");loaded.recover();check(!loaded.data().history.empty()&&loaded.data().history.back().items==s.items,"interruption history keeps ownership (not live resume)");std::filesystem::remove_all(dir);std::cout<<"PASS preset boundaries/migration and campaign owned-key serialization\n";
}
}
int main(){try{native();lifecycle();cadenceAndShots();presets();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
