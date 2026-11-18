#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
Simulation generated(uint64_t seed,float scale=1.1f,int lo=7,int hi=9,bool seeded=true,uint64_t runId=1,int floor=0,MissionTheme theme=MissionTheme::Canyon,bool tutorial=false,ExpeditionPacing pacing=ExpeditionPacing::Compact) {
 return Simulation(seed,runId,{},theme,true,tutorial,WitnessAccount::None,floor,pacing,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{},seeded);
}
void damage(Simulation &s,EntityId id,float value){Event e;e.type=EventType::Damage;e.target=id;e.damage=value;s.queueRoot(e);s.drainEvents();}
void frames(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void layouts(const Simulation &a,const Simulation &b) {
 check(a.arena.roomCount()==b.arena.roomCount()&&a.arena.passages.size()==b.arena.passages.size(),"boss choice preserves room graph");
 for(int i=0;i<a.finalRoom();++i) {
  const auto &x=a.arena.rooms[size_t(i)],&y=b.arena.rooms[size_t(i)];
  check(x.kind==y.kind&&x.service==y.service&&x.vacantServiceSite==y.vacantServiceSite&&planarDistance(x.center,y.center)<.001f,"ordinary room roles and positions do not reroll");
  check(x.sourceCombatTemplate==y.sourceCombatTemplate&&x.sourceHeartTemplate==y.sourceHeartTemplate&&x.sourceObstacleTemplate==y.sourceObstacleTemplate&&x.heartSpawns.size()==y.heartSpawns.size(),"source room contents do not reroll");
  check(a.roomEnemyCount(i)==b.roomEnemyCount(i),"ordinary encounter population stays unchanged");
 }
}
void stableChoices() {
 check(seededOpeningBossType(0)==20&&seededOpeningBossType(1)==67&&seededOpeningBossType(69)==67,"recorded v1 seed witnesses");
 check(SupportedOpeningBosses[0].poolId==1&&SupportedOpeningBosses[1].poolId==13&&SupportedOpeningBosses[0].weight==1&&SupportedOpeningBosses[1].weight==1,"recorded supported XML subset and source order");
 for(uint64_t seed:{0,1,69}) {
  auto s=generated(seed);const auto selected=s.arena.profile.bossMonster;
  check(selected==monsterId(seed==0?20:67)&&s.hasSourceBoss(s.finalRoom()),"actual generated opening boss uses dedicated seeded choice");
  auto retry=generated(seed,1.1f,7,9,true,987654321);check(retry.arena.profile.bossMonster==selected,"new expedition ID does not reroll boss");layouts(s,retry);
  auto fixed=generated(seed,1.1f,7,9,false);check(fixed.arena.profile.bossMonster==monsterId(20),"fixed Monstro remains available");layouts(s,fixed);
  for(int n=0;n<128;++n){s.combatRng.next();s.rewardRng.next();s.encounterRng.next();}
  s.resizeRooms(.75f,5,5,.3f);check(s.seededBosses&&s.arena.profile.bossMonster==selected,"small-room Apply and unrelated random draws retain boss");
  s.resizeRooms(1.5f,10,10,.26f);check(s.arena.profile.bossMonster==selected,"large-room Apply retains boss");
  s.jumpDebug(s.finalRoom());int bosses=0;
  for(const auto &e:s.enemies)if(e.alive&&e.kind==EnemyKind::Boss){++bosses;check(e.monster==selected&&((selected.type==20&&e.monstro)||(selected.type==67&&e.duke)),"selected actual controller is spawned");}
  check(bosses==1,"one opening-floor boss");
 }
 for(auto pacing:{ExpeditionPacing::Compact,ExpeditionPacing::Classic}) {
  auto a=generated(1,1.1f,7,9,true,1,1,MissionTheme::Canyon,false,pacing),b=generated(1,1.1f,7,9,false,1,1,MissionTheme::Canyon,false,pacing);
  check(a.arena.profile.bossMonster==b.arena.profile.bossMonster&&!a.hasSourceBoss(a.finalRoom()),"later floors retain existing boss policy");
 }
 auto tutorial=generated(1,1.1f,7,9,true,1,0,MissionTheme::Canyon,true);
 auto mine=generated(1,1.1f,7,9,true,1,0,MissionTheme::Mine);
 auto classic=generated(1,1.1f,7,9,true,1,0,MissionTheme::Canyon,false,ExpeditionPacing::Classic);
 check(!tutorial.hasSourceBoss(tutorial.finalRoom())&&!mine.hasSourceBoss(mine.finalRoom())&&!classic.hasSourceBoss(classic.finalRoom()),"tutorial/Mine/Classic remain outside seeded opening policy");
}
void fullLoop() {
 for(uint64_t seed:{0,1}) {
  auto s=generated(seed);s.jumpDebug(s.finalRoom());s.godMode=true;s.player.position=add(s.arena.rooms.back().center,{4,0,0});s.player.position.y=.85f;
  EntityId boss=0;for(const auto &e:s.enemies)if(e.alive&&e.kind==EnemyKind::Boss)boss=e.id;
  check(boss!=0&&!s.rewardAvailable(s.room)&&!s.canUseFloorExit(),"seeded fight initially seals reward/exit");
  damage(s,boss,10000);frames(s,2);
  if(seed==1) {
   check(!s.rewardAvailable(s.room)&&!s.canUseFloorExit(),"seeded Duke death keeps remaining flies as a gate");
   std::vector<EntityId> children;for(const auto&e:s.enemies)if(e.alive&&e.dukeChild)children.push_back(e.id);
   check(children.size()==6,"seeded Duke retains six ordinary death flies");for(auto id:children)damage(s,id,10000);
   // Recorded initial flies also participate in the ordinary room-clear gate.
   for(const auto &e:s.enemies)if(e.alive&&e.monster==monsterId(18)&&!e.dukeChild)damage(s,e.id,10000);frames(s,3);
  }
  check(s.rewardAvailable(s.room)&&s.canUseFloorExit()&&s.arena.bossRewardPedestal,"selected boss death/offspring clear unlocks single reward and exit");
  s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);
  check(s.collectTreasureUpgrade()&&s.itemStacks({"isaac",ItemKind::Collectible,25})==1&&!s.collectTreasureUpgrade(),"Breakfast is collected exactly once");
  s.player.position=s.arena.exit;s.interact();check(s.floorExitRequested&&s.advanceFloor()&&s.floor==1&&s.seededBosses&&s.player.maxHp==8,"descent preserves item and seeded setting without replacing later boss");
 }
}
void presets() {
 const auto fp=defaultMechanics()->fingerprint();const auto dir=std::filesystem::temp_directory_path()/"deathward-d13c-presets";std::filesystem::create_directories(dir);
 BalancePreset p{1,fp};p.defaultZoomPercent=165;p.duke.health=.75f;p.monstro.movement=.8f;
 for(bool enabled:{true,false}){p.seededBosses=enabled;p.save(dir/"roundtrip.json");const auto q=BalancePreset::load(dir/"roundtrip.json",fp);check(q.seededBosses==enabled&&q.duke==p.duke&&q.monstro==p.monstro&&q.defaultZoomPercent==165,"schema45 policy and both tunings round-trip");}
 for(const auto *name:{"d03-shooting/user-preset-2026-11-11.json","d13a-monstro-loop/migrated-preset-v43.json","d13b-duke-loop/duke-preset.json"}) {
  auto old=BalancePreset::load(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/"+name,fp);
  check(!old.seededBosses&&old.defaultZoomPercent==165&&old.playerSpeed==1,"old presets keep fixed choices and accepted settings");
  if(std::string(name).find("d13b")!=std::string::npos)check(old.duke.enabled,"old Duke remains fixed Duke");
 }
 p.seededBosses=true;auto text=p.json();const auto at=text.find("\"seeded_bosses\": true",text.find("\"resolved\""));check(at!=text.npos,"resolved selector present");text.replace(at,std::string("\"seeded_bosses\": true").size(),"\"seeded_bosses\": 1");std::ofstream(dir/"invalid.json")<<text;
 bool rejected=false;try{(void)BalancePreset::load(dir/"invalid.json",fp);}catch(const std::exception&){rejected=true;}check(rejected,"nonboolean selector rejected");std::filesystem::remove_all(dir);
}
}
int main(){try{stableChoices();fullLoop();presets();std::cout<<"PASS seeded opening bosses: stable encounters/resize/streams, scoped eligibility, reward/descent and preset migration\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
