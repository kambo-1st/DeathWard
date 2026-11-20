#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceShopStock.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
Simulation canyon(float scale=1,int lo=7,int hi=9,uint64_t seed=5){return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{1});}
void native(){
 std::ifstream f(Root/"docs/reports/isaac-first-floor-parity/troll-bombs/native-updates.csv");check(bool(f),"preserved whole-Update capture");std::string line;std::getline(f,line);BagBombMotion m;int last=-1,rows=0,cases=0;float worst=0;
 while(std::getline(f,line)){
  std::vector<std::string> c;std::stringstream ss(line);std::string v;while(std::getline(ss,v,','))c.push_back(v);check(c.size()==26,"native row fields");
  int variant=std::stoi(c[1]),id=std::stoi(c[0]);if((variant!=3&&variant!=4)||std::stoi(c[24])>0)continue;
  auto n=[&](int i){return std::stof(c[size_t(i)]);};
  if(id!=last){m={};m.variant=variant;m.countdown=m.fuse(uint32_t(std::stoul(c[2])));m.velocity={n(3),0,n(4)};last=id;++cases;}
  m.move();--m.countdown;m.steer({n(5),0,n(6)},{n(7),0,n(8)});
  const float error=std::max({std::abs(m.position.x-n(10)),std::abs(m.position.z-n(11)),std::abs(m.velocity.x-n(12)),std::abs(m.velocity.z-n(13)),std::abs(m.friction-n(14))});
  worst=std::max(worst,error);check(error==0&&m.countdown==std::stoi(c[15]),"exact captured fuse/motion/friction state");++rows;
 }
 check(rows==2568&&cases==48,"all48 ordinary/super preblast cases");std::cout<<"PASS "<<rows<<" native states / "<<cases<<" cases / maximum numeric error "<<worst<<'\n';
}
uint32_t bagSeed(int subtype){for(uint32_t seed=1;seed<1000000;++seed)for(auto d:sourceGrabBagContents(seed))if(d.variant==40&&sourceOrdinaryPickup(d.seed,40).subtype==subtype)return seed;throw std::runtime_error("missing rare seed");}
void delivery(float scale,int lo,int hi,int subtype){
 auto s=canyon(scale,lo,hi);s.jumpDebug(s.arena.shopRoom);s.step({});check(s.grabBags.size()==1,"natural shop bag placement");const auto pos=s.grabBags[0].position;const int slot=s.grabBags[0].shopSlot;
 // Supplied deterministic contents seed; geometry/stock/payment use actual game.
 const uint32_t seed=bagSeed(subtype);s.grabBags.clear();s.upgradedShop[size_t(slot)].seed=seed;check(s.spawnShopGrabBag(pos,slot),"rare-content bag admission");
 s.limits.enemyBombs=0;s.limits.pendingEnemyBombs=0;s.player.position=pos;s.moneyCollected=20;const int ammo=s.dynamite;ticks(s,2);check(s.grabBags[0].opened&&s.moneySpent==7,"paid once while hazard capacity full");
 uint32_t expected=0;for(auto d:s.grabBags[0].contents)if(d.variant==40&&d.subtype==subtype){check(!d.delivered,"rare content retained pending");expected=d.seed;}check(expected!=0,"rare identity retained");
 s.grabBagTuning.bombFuse=2;s.grabBagTuning.bombMovement=.5f;s.limits.enemyBombs=100;s.player.position=s.arena.rooms[size_t(s.room)].entry;ticks(s,1);
 check(!s.enemyBombs.empty()&&s.enemyBombs[0].bagBomb,"pending hazard admitted");const auto id=s.enemyBombs[0].id;check(s.enemyBombs[0].bagBomb->seed==expected,"seed preserved across capacity retry");check(s.enemyBombs[0].bagBomb->motion.variant==(subtype==3?3:4),"source pickup-to-actor mapping");
 check(s.enemyBombs[0].bagBomb->movement==.5f&&std::abs(s.enemyBombs[0].charge.delay-float(BagBombMotion::fuse(expected)+1)*2/30)<.00001f,"birth snapshots independent controls");
 s.grabBagTuning.bombFuse=.25f;s.grabBagTuning.bombMovement=2;const auto old=s.enemyBombs[0].charge.delay;
 const int shop=s.room;const int oldTicks=s.enemyBombs[0].bagBomb->motion.ticks;s.enterRoom(0);s.player.position=s.arena.rooms[0].entry;ticks(s,30);check(s.enemyBombs[0].charge.delay==old&&s.enemyBombs[0].bagBomb->motion.ticks==oldTicks,"inactive room pauses existing hazard");s.enterRoom(shop);s.player.position=s.arena.rooms[size_t(shop)].entry;ticks(s,4);check(s.enemyBombs[0].id==id&&s.enemyBombs[0].bagBomb->movement==.5f&&s.moneySpent==7&&s.dynamite==ammo,"revisit no duplicate/payment/ammo and lit snapshot retained");
 for(auto d:s.grabBags[0].contents)if(d.variant==40&&d.subtype==subtype)check(d.delivered,"rare outcome marked delivered once");
 s.resizeRooms(scale,lo,hi,.27f);check(s.enemyBombs.empty()&&s.grabBagTuning.bombFuse==.25f&&s.grabBagTuning.bombMovement==2,"Apply clears floor hazards and retains tuning");
 std::cout<<"PASS rare bag subtype "<<subtype<<" at room scale "<<scale<<" seed "<<seed<<'\n';
}
void explosion(){
 for(int subtype:{3,5})for(bool dodge:{false,true}){
  auto s=canyon();s.jumpDebug(s.arena.shopRoom);s.step({});const auto at=s.player.position;const auto hp=s.player.totalHealth();const auto ammo=s.dynamite;check(s.spawnBagBomb(at,subtype,42),"direct source actor admission");s.enemyBombs[0].bagBomb->motion.countdown=0;s.limits.eventsPerChain=0;
  ticks(s,5);check(s.enemyBombs.size()==1&&s.enemyBombs[0].bagBomb->blastPending&&s.player.totalHealth()==hp,"blast capacity pauses pending hazard");
  if(dodge)s.player.dodge=.2f;s.limits.eventsPerChain=256;ticks(s,1);check(s.enemyBombs.empty(),"one accepted explosion removes hazard");check(s.dynamite==ammo&&s.player.totalHealth()==hp-(dodge?0:2),"two half-heart blast / dodge immunity / no ammo");ticks(s,10);check(s.player.totalHealth()==hp-(dodge?0:2),"no repeated explosion");
 }
 std::cout<<"PASS deferred explosion, once-only damage and universal dodge\n";
}
void motionPartitions(){
 for(int hz:{30,60,120})for(int subtype:{3,5}) {
  auto s=canyon();s.jumpDebug(s.arena.shopRoom);s.step({});auto at=s.grabBags[0].position;
  bool found=false;for(int i=0;i<24;++i){auto target=add(at,mul(rotateY({1,0,0},float(i)*2*Pi/24),3));if(s.arena.roomAt(target)==s.room&&!s.arena.blocked(target,.48f)&&s.arena.clear(at,target,.48f)){s.player.position=target;found=true;break;}}
  check(found&&s.spawnBagBomb(at,subtype,1),"motion fixture clear source/target");const auto origin=s.enemyBombs[0].charge.origin;auto model=s.enemyBombs[0].bagBomb->motion;
  Input moving;if(subtype==5)moving.movement=unit(horizontal(sub(s.player.position,at)));for(int tick=0;tick<12;++tick){for(int part=0;part<hz/30;++part)s.step(moving,1.f/hz);model.move();--model.countdown;model.steer(mul(horizontal(sub(s.player.position,origin)),1/BagBombRuntime::MotionScale),mul(horizontal(s.player.velocity),1/(60*BagBombRuntime::MotionScale)));check(s.enemyBombs.size()==1,"preblast actor retained");const auto &actual=s.enemyBombs[0];check(planarDistance(actual.charge.position,add(origin,mul(model.position,BagBombRuntime::MotionScale)))<.0001f&&actual.bagBomb->motion.countdown==model.countdown&&distance(actual.bagBomb->motion.velocity,model.velocity)<.0001f,"actual Simulation uses native model across partitions");}
 }
 std::cout<<"PASS actual Simulation 30/60/120 Hz fuse and pursuit partitions\n";
}
void persistence(){
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a17-shop-grab-bags/review-preset.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&p.grabBags.bombFuse==1&&p.grabBags.bombMovement==1,"schema61 migration preserves165% user settings");
 const auto file=std::filesystem::temp_directory_path()/"dw-bag-bomb-contract-test.json";
 for(float fuse:{.25f,1.f,4.f})for(float move:{.1f,1.f,2.f}){p.grabBags.bombFuse=fuse;p.grabBags.bombMovement=move;p.save(file);auto q=BalancePreset::load(file,p.mechanicsFingerprint);check(p.revision()==q.revision()&&q.grabBags==p.grabBags,"schema62 exact roundtrip");}
 auto bad=p;bad.grabBags.bombFuse=0;bool rejected=false;try{bad.save(file);}catch(...){rejected=true;}check(rejected&&BalancePreset::load(file,p.mechanicsFingerprint).revision()==p.revision(),"invalid tuning rejects atomically");std::filesystem::remove(file);std::cout<<"PASS migrated and custom preset contracts\n";
}
}
int main(int argc,char **argv){try{std::cout<<std::unitbuf;if(argc>1&&std::string(argv[1])=="--find"){
 int found3=0,found5=0;for(uint64_t seed=1;seed<=10000&&(!found3||!found5);++seed){const auto stock=sourceShopStock(canyonShopStockSeed(ExpeditionPlan(seed).floorSeed(0)),1);if(stock.categories[0]!=7&&stock.categories[1]!=7)continue;auto s=canyon(1,7,9,seed);s.jumpDebug(s.arena.shopRoom);s.step({});for(const auto &b:s.grabBags)for(auto d:b.contents)if(d.variant==40&&(d.subtype==3||d.subtype==5)){if(d.subtype==3)found3=1;else found5=1;std::cout<<"NATURAL expedition="<<seed<<" room="<<s.room+1<<" subtype="<<d.subtype<<" bag="<<b.seed<<" actor="<<d.seed<<'\n';}}return 0;}
 native();for(auto [scale,lo,hi]:{std::tuple{.75f,5,5},std::tuple{1.f,7,9},std::tuple{1.5f,10,10}})for(int sub:{3,5})delivery(scale,lo,hi,sub);explosion();motionPartitions();persistence();std::cout<<"PASS D14a18 bag bombs\n";
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
