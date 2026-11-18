#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation make(uint64_t seed=1,int pool=6){return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true,1,true,true,true,true,true,true,1,pool);}
int treasure(const Simulation &s){for(int i=0;i<s.arena.roomCount();++i)if(s.hasSourceTreasure(i))return i;throw std::runtime_error("No treasure");}
void away(Simulation &s){s.player.position=add(s.rewardPosition(s.room),{0,.85f,4});s.collectTreasureUpgrade();}
void touch(Simulation &s){s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);}
void lifecycle(){
 auto s=make();s.jumpDebug(treasure(s));away(s);
 for(int item:{1,4,8,10})s.grant({"isaac",ItemKind::Collectible,uint32_t(item)});
 s.grant(YumHeartKey);s.activeItem->charge=2;const auto stats=s.effectivePlayerStats();s.step({});
 touch(s);check(s.collectTreasureUpgrade(),"Collect second active");
 check(s.activeItem==ActiveItemState{BookOfShadowsKey,3}&&s.itemStacks(YumHeartKey)==0&&s.itemStacks(BookOfShadowsKey)==1,"Exactly one active inventory member");
 check(s.rooms[size_t(s.room)].droppedActive==ActiveItemState{YumHeartKey,2},"Old item/charge stays on pedestal");
 check(!s.collectTreasureUpgrade(),"No automatic contact swap-back");
 check(s.effectivePlayerStats().damage==stats.damage&&s.effectivePlayerStats().tearsPerSecond==stats.tearsPerSecond&&s.brotherBobbies.size()==1&&s.haloFlies.size()==2,"Permanent passive and familiar ownership retained");
 check(s.useActiveItem()&&s.activeItem->charge==0&&s.bookProtectionRemaining==10,"Book use / discharge");
 away(s);touch(s);check(s.collectTreasureUpgrade()&&s.activeItem==ActiveItemState{YumHeartKey,2}&&s.rooms[size_t(s.room)].droppedActive==ActiveItemState{BookOfShadowsKey,0},"Swap back retains both charges");
 check(s.bookProtectionRemaining==10&&!s.takeHeartDamage(1),"Protection survives item swap independently");
 const auto owner=s.room;s.jumpDebug(0);s.jumpDebug(owner);check(s.rooms[size_t(owner)].droppedActive->charge==0&&s.bookProtectionRemaining==10,"Room transition retains dropped charge and remaining protection");
 away(s);touch(s);check(s.collectTreasureUpgrade()&&s.activeItem->item==BookOfShadowsKey,"Reclaim spent Book");away(s);
 s.bookOfShadows={8.5f,2};s.resizeRooms(1.11f,7,9,.26f);check(s.activeItem->charge==0&&s.bookProtectionRemaining==10&&s.bookOfShadows==BookOfShadowsTuning{8.5f,2},"Apply retains build/timer/config, no refill");
 int first=-1;for(int i=1;i<s.finalRoom();++i){s.jumpDebug(i);if(s.roomClear||!s.roomThreats())continue;first=i;s.clearRoomDebug();break;}
 check(first>=0&&s.activeItem->charge==2,"Future hostile clear uses Book recharge");s.clearRoom();check(s.activeItem->charge==2,"No repeated clear charge");
 s.jumpDebug(first,true);s.clearRoomDebug();check(s.activeItem->charge==2,"Replay cannot award charge");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();check(s.activeItem->charge==3,"Charge caps at three");
 s.floorExitRequested=true;check(s.advanceFloor()&&s.activeItem==ActiveItemState{BookOfShadowsKey,3}&&s.bookOfShadows==BookOfShadowsTuning{8.5f,2}&&s.itemStacks({"isaac",ItemKind::Collectible,8})==1,"Floor retains slot/config/passives");
 std::cout<<"PASS different active swaps, charge retention, passives/familiars, clears/revisit/Apply/floor\n";
}
void timerAndDamage(){
 for(int hz:{30,60,120}) {
  auto s=make();s.jumpDebug(treasure(s));away(s);s.grant(BookOfShadowsKey);s.activeItem->charge=2;
  check(!s.useActiveItem()&&s.bookProtectionRemaining==0,"Partial charge rejected");s.activeItem->charge=3;
  check(s.useActiveItem(),"Use Book");const auto hp=s.player.hp;const auto damage=s.stats.damageTaken;
  check(!s.takeHeartDamage(1)&&!s.takeHeartDamage(2,true)&&s.player.hp==hp&&s.stats.damageTaken==damage&&s.player.hurt==0,"Protected damage rejected before health/events/cooldown");
  s.rewardOpen=true;for(int i=0;i<hz;++i)s.step({},1.f/hz);check(s.bookProtectionRemaining==10,"Modal freezes effect");s.rewardOpen=false;
  s.bookOfShadows.duration=2;check(s.bookProtectionRemaining==10,"Live edits do not resize running effect");
  for(int i=0;i<hz*10-1;++i)s.step({},1.f/hz);
  check(s.bookProtectionRemaining>0&&!s.takeHeartDamage(1),"Protection lasts through final interval");
  s.step({},1.f/hz);check(s.bookProtectionRemaining<1e-6&&s.takeHeartDamage(1)&&s.player.hp==hp-1,"Expiry restores ordinary damage at 30/60/120 Hz");
  s.player.hurt=0;s.player.dodge=.2f;check(!s.takeHeartDamage(1),"Dodge protects independently after expiry");s.player.dodge=0;
  s.activeItem->charge=3;check(s.useActiveItem()&&s.bookProtectionRemaining==2,"Next activation consumes live duration");
  for(int i=0;i<hz;++i)s.step({},1.f/hz);s.activeItem->charge=3;s.useActiveItem();check(std::abs(s.bookProtectionRemaining-3)<.00001,"Repeated effect adds remaining duration");
 }
 auto s=make();s.jumpDebug(treasure(s));away(s);s.grant(BookOfShadowsKey);Input input;input.useActive=true;s.step(input);s.activeItem->charge=3;for(int n=0;n<60;++n)s.step(input);check(s.activeItem->charge==3&&s.bookProtectionRemaining<10,"Held key does not repeatedly activate");s.step({});s.step(input);check(s.activeItem->charge==0&&s.bookProtectionRemaining>18,"Release/repress re-arms");
 // Actual hostile projectile collision and a placed dynamite explosion use the same gate.
 Projectile p;p.id=900001;p.position=add(s.player.position,{2,0,0});p.velocity={-200,0,0};p.life=2;p.radius=.1f;p.hostile=true;p.damage=10;s.projectiles.push_back(p);const auto hp=s.player.hp;s.step({});check(s.player.hp==hp&&s.projectiles.empty(),"Hostile projectile consumed without damage");
 check(s.placeDynamite(),"Place ordinary dynamite");for(int n=0;n<180;++n)s.step({});check(s.player.hp==hp&&s.bookProtectionRemaining>0,"Placed explosion respects protection");
 std::cout<<"PASS activation/input/pause/expiry/partitions, additive duration, projectile/blast damage and dodge independence\n";
}
void nativeCharge(){
 std::ifstream input(Root/"docs/reports/isaac-first-floor-parity/pw-a02-book-of-shadows/source/native-charge.csv");std::string line;std::getline(input,line);int count=0;
 while(std::getline(input,line)) {
  std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int before,award,after;check(bool(row>>before>>award>>after),"Native charge row");
  auto s=make();s.grant(BookOfShadowsKey);s.activeItem->charge=before;s.bookOfShadows.recharge=award;
  for(int i=1;i<s.finalRoom();++i){s.jumpDebug(i);if(!s.roomClear&&s.roomThreats()){s.clearRoomDebug();break;}}
  check(s.activeItem->charge==after,"Actual clear matches original three-charge arithmetic");++count;
 }check(count==12,"Native case coverage");
}
void persistenceAndReview(){
 const auto dir=std::filesystem::temp_directory_path()/("deathward-book-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&p.playerSpeed==1&&!p.bookOfShadows.custom(),"Accepted preset migration");
 p.bookOfShadows={7.5f,2};p.yumHeart.binding=2;p.treasureCollectiblePool=6;p.save(dir/"preset.json");check(BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).json()==p.json(),"Full preset roundtrip");
 for(const auto replacement:{std::string("0"),std::string("31"),std::string("null")}) {auto bad=p.json();const auto at=bad.find("\"duration\": 7.5");check(at!=bad.npos,"Duration fixture");bad.replace(at+12,3,replacement);std::ofstream(dir/"bad.json")<<bad;bool rejected=false;try{BalancePreset::load(dir/"bad.json",p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"Invalid duration rejected");}
 auto s=make();check(s.beginActiveReview()&&s.items.empty()&&s.treasureUpgradeItem(s.room)==45,"Review starts empty with staged Yum");touch(s);s.collectTreasureUpgrade();check(s.activeItem->item==YumHeartKey&&!s.collectTreasureUpgrade(),"First review offering gated");s.useActiveItem();away(s);touch(s);check(s.collectTreasureUpgrade()&&s.activeItem->item==BookOfShadowsKey&&s.rooms[size_t(s.room)].droppedActive==ActiveItemState{YumHeartKey,0}&&s.powerUpsTaken==1,"Second review offering performs ordinary swap");
 s.useActiveItem();{CampaignStore c(dir/"campaign.save");auto id=c.begin(1);auto record=s.summary();record.id=id;c.checkpoint(record);}
 {CampaignStore c(dir/"campaign.save");check(c.data().pending->activeItem==s.activeItem,"Book slot/charge checkpoint");c.recover();check(c.data().history.back().activeItem==s.activeItem,"Interrupted history retains Book slot, not live resume");}
 std::filesystem::remove_all(dir);std::cout<<"PASS preset migration/roundtrip/invalid rejection, labelled empty-build review, campaign history\n";
}
}
int main(int argc,char **){try{
 if(argc>1){std::set<int> seen;for(int seed=1;seed<100;++seed){auto s=make(seed,1);const int room=treasure(s),item=s.treasureUpgradeItem(room);if(seen.insert(item).second||seed==38||seed==11)std::cout<<"WITNESS seed="<<seed<<" room="<<room+1<<" item="<<item<<'\n';}return seen.size()==7?0:1;}
 lifecycle();timerAndDamage();nativeCharge();persistenceAndReview();return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
