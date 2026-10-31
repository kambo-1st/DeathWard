#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *s){if(!ok)throw std::runtime_error(s);}
bool near(float a,float b){return std::abs(a-b)<.008f;}
struct Pack {
 std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-spider-variants-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 std::string original;
 Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());std::ifstream in(path/"spider_variants.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
 ~Pack(){std::filesystem::remove_all(path);}
 auto load(const std::string &s){std::ofstream(path/"spider_variants.mechanics")<<s;return MechanicsLibrary::load(path);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){auto i=s.find(a);check(i!=s.npos,"fixture directive exists");s.replace(i,a.size(),b);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
 Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
 s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,8,40}};
 for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-40,-.4f,-40},{40,0,40}}};}
 s.arena.boundaryWalls={{{-41,-1,-41},{-40,8,41}},{{40,-1,-41},{41,8,41}},{{-41,-1,-41},{41,8,-40}},{{-41,-1,40},{41,8,41}}};
 s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
 s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,12};s.godMode=true;return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;s.queueRoot(e);s.drainEvents();}
void river(Simulation &s) {
 s.arena.canyon=std::make_shared<CanyonTerrain>();auto &f=*s.arena.canyon;
 f.x=f.z=-41;f.step=1;f.width=f.depth=83;f.heights.resize(83*83);
 for(int z=0;z<83;++z)for(int x=0;x<83;++x)f.heights[size_t(z*83+x)]=std::abs(z-41)<=2?-1.f:0.f;
 f.boundaryHeights=f.heights;f.riverKind=CanyonRiverKind::Interior;f.river={{{-40,0,0},2,0},{{40,0,0},2,80}};
}
void strider() {
 Pack p;auto lib=p.load(replace(p.original,".1 .95 6 9 4 2 3",".1 .95 6 6 1 1 1"));
 auto s=fixture(lib);auto id=s.spawnMonster(monsterId(814),{0,.85f,0});tick(s,4);
 auto *e=s.findEnemy(id);check(e->strider&&e->strider->frame==0&&e->strider->chasing,"ready check starts twenty-frame rowing stroke");
 check(near(e->hp,20.8f)&&near(e->lift,.8f),"source HP and height conversion");tick(s,10);
 check(s.findEnemy(id)->strider->frame==5&&length(s.findEnemy(id)->velocity)<.001f,"no impulse before Row6");
 s.player.position={12,.85f,0};tick(s,2);e=s.findEnemy(id);
 check(e->strider->strokes==1&&near(e->velocity.x,17.1f)&&near(e->velocity.z,0),"Row6 retargets current player and applies force6 times retention.95");
 tick(s,2);check(near(s.findEnemy(id)->velocity.x,16.245f),"gliding decays by.95 on the next source tick");
 tick(s,26);check(s.findEnemy(id)->strider->frame==-1&&s.findEnemy(id)->strider->strokes==1,"twenty-frame stroke completes with one rowing impulse");
 auto wet=fixture(lib);river(wet);wet.player.position={0,.85f,8};id=wet.spawnMonster(monsterId(814),{0,.85f,-8});bool water=false,crossed=false;
 for(int n=0;n<300;++n){tick(wet);const auto &body=*wet.findEnemy(id);water|=wet.arena.canyon->waterBlocked(body.position);crossed|=body.position.z>3;check(!wet.arena.swimBlocked(body.position,body.radius,0),"Strider respects solid swimming collision");}
 check(water&&crossed,"Strider genuinely traverses impassable water");
 auto rock=fixture(lib);rock.arena.obstacles.push_back({{-39,0,3},{39,4,4}});rock.arena.rebuildWalls();id=rock.spawnMonster(monsterId(814),{0,.85f,0});
 for(int n=0;n<160;++n){tick(rock);check(!rock.findEnemy(id)->strider->chasing,"blocked sight prevents new chase stroke");check(!rock.arena.swimBlocked(rock.findEnemy(id)->position,.4f,0),"Strider does not penetrate rocks");}
 std::cout<<"PASS Strider Row6/20frames, current targeting, glide retention, true water traversal and rock collision\n";
}
void swarm() {
 Pack p;
 for(int kind=0;kind<3;++kind) {
  std::string weight=kind==0?"1 0 0":kind==1?"0 1 0":"0 0 1";
  auto text=replace(p.original,"5 3 0 2 3 2 2 3 9",weight+" "+weight+" "+weight);
  text=replace(text,"100 200 4 20 4","100 200 10000 10000 10000");auto lib=p.load(text);
  auto s=fixture(lib);s.player.position={0,.85f,30};auto id=s.spawnMonster(monsterId(884),{0,.85f,0});tick(s,4);
  auto *e=s.findEnemy(id);const auto hop=lib->swarmSpider(monsterId(884))->hops[size_t(kind)];
  check(e->swarmSpider->kind==kind&&e->swarmSpider->frame==0,"configured weighted choice selects correct hop");
  const auto launch=e->swarmSpider->launch;const float speed=length(launch);
  check(speed>=hop.minimum&&speed<=hop.maximum,"source hop-specific speed range");
  check(near(e->maxHp,15.04f),"Swarm source4.5+.2stageHP scaled3.2");
  s.player.position={-30,.85f,0};tick(s,2*(hop.jump-1));check(length(s.findEnemy(id)->velocity)<.001f,"hop windup stationary until Jump event");
  tick(s,2);e=s.findEnemy(id);check(e->swarmSpider->airborne&&near(length(e->velocity),speed*3)&&near(e->velocity.z,launch.z*3),"Jump uses committed vector despite moved player");
  tick(s,2*(hop.land-hop.jump));e=s.findEnemy(id);check(!e->swarmSpider->airborne&&e->swarmSpider->frame==hop.land&&near(length(e->velocity),speed*3),"constant flight velocity through Land event");
  tick(s,2);check(near(length(s.findEnemy(id)->velocity),speed*3*.7f),"ground friction resumes on update after Land");
 }
 auto base=fixture();
 for(float range:{5.f,15.f,30.f}) {
  std::array<int,3> choices{};
  for(uint64_t seed=1;seed<=192;++seed) {
   auto sample=base;sample.combatRng=Random(seed);sample.player.position={0,.85f,range};
   const auto id=sample.spawnMonster(monsterId(884),{0,.85f,0});tick(sample,4);
   const auto &r=*sample.findEnemy(id)->swarmSpider;++choices[size_t(r.kind)];
   if(range<10)check(unit(r.launch).z<.72f,"nearby swarm always turns sideways or away before jitter");
  }
  check(range>=10?choices[2]>0:choices[2]==0,"long hops excluded only from near distance tier");
  if(range>20)check(choices[2]>choices[0]+choices[1],"far tier favors long hops");
 }
 auto s=fixture();s.player.position={0,.85f,5};auto id=s.spawnMonster(monsterId(884),{0,.85f,0});std::set<int> kinds;bool sawAir=false;
 for(int n=0;n<600;++n){tick(s);const auto *e=s.findEnemy(id);kinds.insert(e->swarmSpider->kind);sawAir|=e->swarmSpider->airborne;}
 check(sawAir&&s.findEnemy(id)->swarmSpider->hops>8&&s.stats.projectiles==0,"repeated varied hops without projectile attack");
 auto water=fixture();river(water);water.player.position={0,.85f,8};id=water.spawnMonster(monsterId(884),{0,.85f,-8});
 for(int n=0;n<300;++n){tick(water);check(!water.arena.canyon->waterBlocked(water.findEnemy(id)->position),"visual swarm hops do not grant pit flight");}
 auto overlap=fixture();const auto a=overlap.spawnMonster(monsterId(884),{0,.85f,0}),b=overlap.spawnMonster(monsterId(884),{0,.85f,0});tick(overlap);
 check(planarDistance(overlap.findEnemy(a)->position,overlap.findEnemy(b)->position)<.001f,"source player-objects collision does not separate enemy peers");
 std::cout<<"PASS all three Swarm hop event schedules, launch ranges, commitment, friction, pit collision and peer overlap\n";
}
void damageAndReplacement() {
 auto fire=fixture();const auto fireplace=fire.spawnMonster(monsterId(33),{0,.85f,0});(void)fireplace;
 auto id=fire.spawnMonster(monsterId(884),{0,.85f,0});auto ordinary=fire.spawnMonster(monsterId(85),{.1f,.85f,0});tick(fire);
 std::cout<<"FIREPLACE swarm="<<fire.findEnemy(id)->hp<<" ordinary="<<fire.findEnemy(ordinary)->hp<<" fire="<<fire.findEnemy(fireplace)->hp<<" spent="<<fire.findEnemy(fireplace)->environment->spent<<"\n";
 check(near(fire.findEnemy(id)->hp,15.04f)&&fire.findEnemy(ordinary)->hp<20.8f,"real fireplace hurts ordinary Spider but not Swarm");
 damage(fire,id,3,DamageKind::Burning);check(near(fire.findEnemy(id)->hp,12.04f),"fireplace immunity is not burning immunity");
 damage(fire,id,3,DamageKind::Flame);check(near(fire.findEnemy(id)->hp,9.04f),"player flame remains damaging");damage(fire,id,20);check(!fire.findEnemy(id)->alive,"physical damage kills Swarm normally");
 for(int type:{814,884}) {
  auto contact=fixture();contact.godMode=false;id=contact.spawnMonster(monsterId(type),contact.player.position);tick(contact);
  check(near(contact.player.hp,StartingHealth-10*EnemyDamageMultiplier),"contact preserves existing damage scaling");
  auto stun=fixture();id=stun.spawnMonster(monsterId(type),{0,.85f,0});tick(stun,40);auto *e=stun.findEnemy(id);e->state=EnemyState::Stunned;e->stateTime=.2f;tick(stun,2);check(length(stun.findEnemy(id)->velocity)<.001f,"stun interrupts variant movement");
 }
 auto wet=fixture();wet.arena.profile.band=1;wet.arena.profile.variant=FloorVariant::Flooded;wet.arena.profile.sourceStage=3;
 id=wet.spawnMonster(monsterId(85),{0,.85f,0});check(wet.findEnemy(id)->monster==monsterId(814),"direct Spider spawn replaces identity on wet floor");wet.enemies.clear();
 id=wet.spawnMonster(monsterId(94),{0,.85f,0});wet.limits.enemies=0;damage(wet,id,65);tick(wet,2);check(wet.livingEnemies()==0,"wet replacement children retain capacity delay");wet.limits.enemies=2;tick(wet);
 check(wet.livingEnemies()==2,"both wet death children admitted");for(const auto &e:wet.enemies)if(e.alive)check(e.monster==monsterId(814)&&near(e.hp,20.8f)&&near(std::abs(e.velocity.x),30),"Big Spider births become full-health Striders with original impulses");
 FloorProfile dry=wet.arena.profile;dry.variant=FloorVariant::Standard;check(wet.content->spawnIdentity(monsterId(85),dry)==monsterId(85),"dry floor preserves ordinary Spider");
 std::cout<<"PASS fireplace-specific immunity, ordinary damage/contact/stun and wet direct/retained death replacements\n";
}
void configAndPlacement() {
 Pack p;auto before=p.load(p.original);auto after=p.load(replace(p.original,".1 .95 6 9",".1 .9 6 9"));check(before->fingerprint()!=after->fingerprint()&&near(before->strider(monsterId(814))->retention,.95f),"immutable reload snapshots");
 for(const auto &bad:{replace(p.original,"20 6 .2","20 20 .2"),replace(p.original,"5 3 0 2 3 2 2 3 9","0 0 0 2 3 2 2 3 9"),replace(p.original,"10 2 8 5 6 45","10 8 2 5 6 45"),p.original+"replace_spawn 814.0.0 85.0.0 1 1 flooded\n",replace(p.original,"replace_spawn 85.0.0 814.0.0 1 1 flooded","replace_monster 85.0.0 814.0.0 1 1 flooded 5000 0")}) {bool rejected=false;try{p.load(bad);}catch(...){rejected=true;}check(rejected,"bad events/weights/cyclic replacements rejected");}
 std::set<MonsterId> found;
 for(uint64_t seed=0;seed<512&&found.size()<2;++seed) {
  ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
  for(int floor=0;floor<plan.floorCount&&plan.profileOnFloor(floor).band<=1;++floor) {
   if(floor>0&&found.contains(monsterId(814)))break;
   Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
   for(int room=1;room<s.finalRoom();++room) {
    const auto encounter=s.floorEncounter(room);
    for(const auto &e:s.roomEnemies(room))if((e.monster==monsterId(814)||e.monster==monsterId(884))&&found.insert(e.monster).second)
     std::cout<<"NATURAL_VARIANT id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<std::endl;
    if(s.arena.profile.band==1&&s.arena.profile.variant==FloorVariant::Flooded)
     for(const auto &e:s.roomEnemies(room))check(e.monster!=monsterId(85),"all original Spiders replaced in actual wet residents");
   }
  }
 }
 check(found.size()==2,"both regular variants naturally reachable");std::cout<<"PASS validated config and real seeded variant placement\n";
}
}
int main(){try{strider();swarm();damageAndReplacement();configAndPlacement();std::cout<<"PASS Strider and Swarm Spider\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
