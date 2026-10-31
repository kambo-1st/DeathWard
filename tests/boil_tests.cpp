#include "combat/Simulation.hpp"
#include "combat/LobFlight.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *what){if(!value)throw std::runtime_error(what);}
bool near(float a,float b){return std::abs(a-b)<.008f;}
struct Pack {
 std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-boils-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 std::string original;
 Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());std::ifstream f(path/"boils.mechanics");original.assign(std::istreambuf_iterator<char>(f),{});}
 ~Pack(){std::filesystem::remove_all(path);}
 auto load(const std::string &s){std::ofstream(path/"boils.mechanics")<<s;return MechanicsLibrary::load(path);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){auto i=s.find(a);check(i!=s.npos,"fixture directive exists");s.replace(i,a.size(),b);return s;}
std::string force(std::string text){for(int n=0;n<5;++n)text=replace(text,"1.2 50 4 8 24","1.2 1 1 8 24");return text;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
 Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
 s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,8,50}};
 for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-50,-.4f,-50},{50,0,50}}};}
 s.arena.boundaryWalls={{{-51,-1,-51},{-50,8,51}},{{50,-1,-51},{51,8,51}},{{-51,-1,-51},{51,8,-50}},{{-51,-1,50},{51,8,51}}};
 s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
 s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,12};s.godMode=true;return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount,DamageSource source=DamageSource::Player,bool explosive=false,DamageKind kind=DamageKind::Physical) {
 Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.context.damageSource=source;e.explosionDamage=explosive;e.damageKind=kind;s.queueRoot(e);s.drainEvents();
}
void growth() {
 for(int variant:{0,1}) {
  auto s=fixture();const auto id=s.spawnMonster(monsterId(30,variant),{0,.85f,0});
  check(near(s.findEnemy(id)->hp,22.4f)&&near(s.findEnemy(id)->maxHp,64),"stationary initial7/max20sourceHP");
  tick(s,2);check(near(s.findEnemy(id)->hp,22.4f)&&near(s.findEnemy(id)->sack->growth,.016f),"Boil first acceleration is.02*.8");
  tick(s,2);check(near(s.findEnemy(id)->hp,22.46144f),"Boil heals from prior acceleration*1.2*3.2");
  damage(s,id,3);const float hp=s.findEnemy(id)->hp;tick(s,2);
  check(near(s.findEnemy(id)->hp,hp)&&near(s.findEnemy(id)->sack->growth,.016f),"damage resets regenerative acceleration");
  tick(s,360);check(s.findEnemy(id)->hp>63.9f,"Boil grows fully in source-rate cycle");
  damage(s,id,1000);tick(s);check(s.livingEnemies()==0,"lethal damage never regenerates");
 }
 for(int variant:{0,1,2}) {
  auto s=fixture();const auto id=s.spawnMonster(monsterId(88,variant),{0,.85f,0});
  check(near(s.findEnemy(id)->hp,64),"walkers start fully swollen");damage(s,id,20);tick(s,300);
  check(near(s.findEnemy(id)->hp,44)&&near(s.findEnemy(id)->sack->growth,0),"walkers do not heal or shrink after damage");
 }
 auto boil=fixture(),sack=fixture();const auto a=boil.spawnMonster(monsterId(30),{0,.85f,0}),b=sack.spawnMonster(monsterId(30,2),{0,.85f,0});
 tick(boil,100);tick(sack,100);check(boil.findEnemy(a)->hp>sack.findEnemy(b)->hp+5,"Sack grows slower than Boil");
 std::cout<<"PASS stationary growth/damage/reset versus nonregenerating walkers\n";
}
void attacks() {
 Pack pack;auto lib=pack.load(force(pack.original));
 for(int type:{30,88})for(int variant:{0,1}) {
  auto s=fixture(lib);const auto id=s.spawnMonster(monsterId(type,variant),{0,.85f,0});s.findEnemy(id)->hp=64;
  tick(s,2);check(s.findEnemy(id)->sack->frame==0,"full body starts Shoot24");tick(s,22);
  check(s.findEnemy(id)->sack->frame==11&&s.stats.projectiles==0,"no early shot before Shoot12");tick(s,2);
  const auto count=s.stats.projectiles;check(variant?count==1:count>=3&&count<=4,"singleGut versus3/4blood volley");
  check(s.projectiles.size()==count,"whole volley admitted");
  for(const auto &p:s.projectiles) {
   check(near(p.gravity,variant?50.4f:63.9f)&&near(p.flightRetention,.9f),"source-derived damped fall");
   check(p.velocity.y>=(variant?24.75f:7.5f)-.01f&&p.velocity.y<=(variant?49.95f:43.5f)+.01f,"upward velocity range");
   const float speed=length(horizontal(p.velocity));
   check(variant?speed>=3.465f&&speed<=27.721f:speed>=10.49f&&speed<=31.51f,"targeted planar speed/scatter range");
   check(p.kind==(variant?ProjectileKind::Ipecac:ProjectileKind::Bullet),"distinct blood/Ipecac projectile kind");
  }
  tick(s,24);check(s.findEnemy(id)->sack->frame==-1&&s.findEnemy(id)->sack->attacks==1,"one emission and recovery at24");
 }
 auto held=fixture(lib);held.limits.projectiles=2;auto id=held.spawnMonster(monsterId(30),{0,.85f,0});held.findEnemy(id)->hp=64;tick(held,90);
 check(held.stats.projectiles==0&&held.findEnemy(id)->sack->frame==12,"whole blood volley retained at capacity");
 const auto selected=held.findEnemy(id)->sack->shots;held.limits.projectiles=16;tick(held,2);
 check(held.stats.projectiles==uint64_t(selected),"retained selected count emitted once");
 for(int type:{30,88}) {
  auto s=fixture(lib);id=s.spawnMonster(monsterId(type),{0,.85f,0});s.findEnemy(id)->hp=64;tick(s,12);damage(s,id,10);tick(s,14);
  check(type==30?s.stats.projectiles==0:s.stats.projectiles>=3,"damage interrupts only growing stationary attack");
 }
 std::cout<<"PASS Shoot24/event12, blood and Ipecac trajectories, atomic volley retention and damage interruption\n";
}
void throwAndMotion() {
 Pack pack;auto lib=pack.load(force(pack.original));
 for(bool wet:{false,true}) {
  auto s=fixture(lib);if(wet){s.arena.profile.band=1;s.arena.profile.variant=FloorVariant::Flooded;}
  auto id=s.spawnMonster(monsterId(88,2),{0,.85f,0});tick(s,26);check(s.livingEnemies()==2,"walking Sack produces child at12");
  auto it=std::find_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.id!=id;});
  check(it!=s.enemies.end()&&it->monster==monsterId(wet?814:85)&&it->thrownOffspring,"walking birth supports wet substitution");
  const auto child=it->id;check(near(it->thrownOffspring->profile.initialHeight,-30),"walker throws from sourceheight30rather than10");
  it->state=EnemyState::Stunned;it->stateTime=.1f;tick(s,8);check(s.findEnemy(child)->state!=EnemyState::Stunned,"Spider/Strider stun expires during shared thrown flight");
  tick(s,90);check(!s.findEnemy(child)->thrownOffspring&&s.findEnemy(child)->alive,"thrown child lands in normal controller");
  damage(s,id,1000);tick(s,2);check(s.findEnemy(child)->alive&&!s.roomClear,"independent child survives parent and keeps room sealed");
 }
 auto crowded=fixture(lib);auto id=crowded.spawnMonster(monsterId(88,2),{0,.85f,0});
 for(int n=0;n<7;++n)crowded.spawnMonster(monsterId(13),{float(n*2+14),.85f,-12});tick(crowded,120);
 check(crowded.findEnemy(id)->sack->attacks==0&&crowded.findEnemy(id)->sack->frame==-1,"crowded walking Sack keeps walking without stationary Shake");
 auto move=fixture();move.arena.obstacles.push_back({{1,0,-2},{4,3,2}});move.arena.rebuildWalls();id=move.spawnMonster(monsterId(88),{0,.85f,0});float travel=0;
 for(int n=0;n<300;++n){auto before=move.findEnemy(id)->position;tick(move);const auto &e=*move.findEnemy(id);travel+=planarDistance(before,e.position);check(!move.arena.blocked(e.position,e.radius),"wandering footprint stays clear of solid cover");}
 check(travel>2,"walker wanders in actual simulation");
 auto impulse=fixture();id=impulse.spawnMonster(monsterId(88),{0,.85f,0});
 impulse.findEnemy(id)->sack=SackRuntime{};auto &r=*impulse.findEnemy(id)->sack;
 r.initialized=true;r.previousHp=64;r.targetReady=true;r.destination={4,.85f,0};tick(impulse,2);
 check(near(impulse.findEnemy(id)->velocity.x,1.5f),"native.5force survives division and.75friction");
 r.frame=0;r.fired=true;impulse.findEnemy(id)->velocity={6,0,0};tick(impulse,2);
 check(near(impulse.findEnemy(id)->velocity.x,4.5f),"walking attack coasts with.75retention and no new force");
 for(int type:{30,88}) {
  auto s=fixture();s.godMode=false;id=s.spawnMonster(monsterId(type),s.player.position);tick(s,2);
  check(type==30?near(s.player.hp,100):s.player.hp<100,"only walking family has contact damage");
 }
 std::cout<<"PASS walking movement/collision/contact, population gating, high throws and independent wet children\n";
}
void immunityAndConfig() {
 for(int type:{30,88})for(int variant:{0,1,2}) {
  auto s=fixture();const auto id=s.spawnMonster(monsterId(type,variant),{0,.85f,0});s.findEnemy(id)->hp=64;
  for(auto source:{DamageSource::Enemy,DamageSource::Environment})damage(s,id,10,source,true);
  check(near(s.findEnemy(id)->hp,64),"family blocks hostile/environment explosions");
  for(auto source:{DamageSource::Player,DamageSource::Ally,DamageSource::Tnt})damage(s,id,3,source,true);
  check(near(s.findEnemy(id)->hp,55),"player, ally and TNT explosions remain effective");
  damage(s,id,3,DamageSource::Enemy,false,DamageKind::Flame);check(near(s.findEnemy(id)->hp,52),"not blanket fire immunity");
 }
 Pack pack;auto old=pack.load(pack.original);
 auto reject=[&](const std::string &text){try{pack.load(text);}catch(const std::exception &){return;}throw std::runtime_error("invalid Boil config accepted");};
 reject(replace(pack.original,"24 12 26","12 12 26"));
 reject(replace(pack.original,"3.2 7 .02 .8","3.2 21 .02 .8"));
 reject(replace(pack.original,"30.1.0 1 1 11.55","30.1.0 2 2 11.55"));
 reject(replace(pack.original,"88.2.0 1 spider","88.2.0 1 blood"));
 reject(pack.original+"boil_projectiles 30.0.0 3 4 21 10.5 1.15 7.5 43.5 63.9 1 1 .15 0 0 10\n");
 check(old->boil(monsterId(30))->cycle.eventFrame==12,"previous immutable snapshot survives rejected reloads");
 std::cout<<"PASS source-aware explosion immunity and strict immutable external configuration\n";
}
void flightAndBlast() {
 for(auto [speed,accel]:{std::pair{-5.f,1.32f},std::pair{-29.f,1.32f},std::pair{-16.5f,1.02f},std::pair{-33.3f,1.02f}}) {
  float height=-23,world=1.15f,velocity=-speed*1.5f;
  for(int n=0;n<70;++n) {
   speed=.9f*speed+.1f+accel;height+=speed;
   world+=advanceLobHeight(velocity,(.1f+accel)*45,.9f,Tick);
   world+=advanceLobHeight(velocity,(.1f+accel)*45,.9f,Tick);
   check(near(world,-height*.05f)&&near(velocity,-speed*1.5f),"blood/Gut flight matches independent native30Hz endpoints");
  }
 }
 Pack pack;auto lib=pack.load(force(pack.original));
 auto s=fixture(lib);auto id=s.spawnMonster(monsterId(30,1),{0,.85f,0});s.findEnemy(id)->hp=64;tick(s,26);
 s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;
 auto other=s.spawnMonster(monsterId(10),{2,.85f,0});s.findEnemy(other)->hp=s.findEnemy(other)->maxHp=500;
 s.findEnemy(other)->state=EnemyState::Stunned;s.findEnemy(other)->stateTime=10;
 s.projectiles.front().position={0,.25f,0};s.projectiles.front().velocity={0,-1,0};
 s.godMode=false;s.player.position={0,.85f,3};tick(s,2);
 check(s.stats.explosions==1&&near(s.findEnemy(id)->hp,64)&&near(s.findEnemy(other)->hp,340)&&near(s.player.hp,75),
       "real Gut blast preserves owner, harms neighbor/player once, with existing hostile scaling");
 auto pending=fixture(lib);id=pending.spawnMonster(monsterId(30,1),{0,.85f,0});pending.findEnemy(id)->hp=64;tick(pending,26);
 pending.enemies.clear();pending.projectiles.front().position={0,.25f,0};pending.projectiles.front().velocity={0,-1,0};
 pending.limits.queuedEvents=0;pending.debugScenario=false;tick(pending,2);
 check(!pending.roomClear&&pending.projectiles.size()==1&&pending.projectiles.front().impactPending,"pending Gut impact keeps room sealed after producer death");
 pending.limits.queuedEvents=256;tick(pending,3);
 check(pending.roomClear&&pending.projectiles.empty()&&pending.stats.explosions==1,"retained Gut blast resolves once then permits room completion");
 std::cout<<"PASS independent fall recurrence and real Gut blast/producer immunity/completion under pressure\n";
}
void natural() {
 std::set<MonsterId> wanted{monsterId(30),monsterId(30,1),monsterId(30,2),monsterId(88),monsterId(88,1),monsterId(88,2)};
 for(uint64_t seed=0;seed<160&&!wanted.empty();++seed) {
  ExpeditionPlan p(seed,false,WitnessAccount::Rourke);
  for(int floor=0;floor<p.floorCount&&!wanted.empty();++floor) {
   Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
   for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(wanted.erase(e.monster))
    std::cout<<"NATURAL_BOIL id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
  }
 }
 check(wanted.empty(),"all six family members occur in actual seeded stage pools");
}
}
int main(){try{growth();attacks();throwAndMotion();immunityAndConfig();flightAndBlast();natural();std::cout<<"PASS Boil family\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
