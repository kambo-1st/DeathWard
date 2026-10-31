#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *s){if(!b)throw std::runtime_error(s);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
struct Pack {
 std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-spider-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 std::string original;
 Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());std::ifstream in(path/"spiders.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
 ~Pack(){std::filesystem::remove_all(path);}
 auto load(std::string s){std::ofstream(path/"spiders.mechanics")<<s;return MechanicsLibrary::load(path);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){auto n=s.find(a);check(n!=s.npos,"fixture directive");s.replace(n,a.size(),b);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
 Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
 s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
 for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
 s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
 s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
 s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,8};s.godMode=true;return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
void movement() {
 auto s=fixture();auto id=s.spawnMonster(monsterId(85),{0,.85f,0});tick(s,30);
 auto *e=s.findEnemy(id);check(near(e->maxHp,20.8f)&&e->spider->counter==14&&!e->spider->targetReady,"source HP and initial idle threshold");
 check(length(e->velocity)<.001f&&near(e->position.z,0),"stationary before burst acquisition");
 tick(s,2);e=s.findEnemy(id);check(e->spider->targetReady&&e->spider->pursuing&&e->spider->counter==15,"selection on15th ready update after init");
 check(near(e->spider->destination.z,8)&&near(e->position.z,0),"acquisition does not immediately move body");
 tick(s,2);check(near(s.findEnemy(id)->velocity.z,10.8f),"source force6 times retention.6 mapped to10.8local initial speed");
 tick(s,2);check(near(s.findEnemy(id)->velocity.z,17.28f),"second source update accumulates and damps momentum");
 const auto destination=s.findEnemy(id)->spider->destination;s.player.position={-8,.85f,3};tick(s,8);
 check(distance(s.findEnemy(id)->spider->destination,destination)<.001f,"burst target is committed, not continuously homing");
 bool stopped=false,restarted=false;for(int n=0;n<180;++n){tick(s);if(!s.findEnemy(id)->spider->targetReady)stopped=true;else if(stopped)restarted=true;}
 check(stopped&&restarted&&s.stats.projectiles==0,"repeated stop/burst cycle without projectiles");
 auto lead=fixture();id=lead.spawnMonster(monsterId(85),{0,.85f,0});tick(lead,31);Input moving;moving.movement={1,0,0};lead.step(moving);
 check(near(lead.findEnemy(id)->spider->destination.x,lead.player.position.x+lead.player.velocity.x/3),"source ten-update target-velocity lead");
 auto far=fixture();far.player.position={25,.85f,25};id=far.spawnMonster(monsterId(85),{0,.85f,0});tick(far,32);e=far.findEnemy(id);
 const auto distance=planarDistance(e->position,e->spider->destination);check(e->spider->targetReady&&!e->spider->pursuing&&distance>=7&&distance<=11,"far target causes70..110source wandering");
 auto small=fixture();auto big=small;const auto a=small.spawnMonster(monsterId(85),{0,.85f,0}),b=big.spawnMonster(monsterId(94),{0,.85f,0});
 for(int n=0;n<300;++n){tick(small);tick(big);check(planarDistance(small.findEnemy(a)->position,big.findEnemy(b)->position)<.001f,"Big Spider shares exact ordinary movement");}
 check(near(big.findEnemy(b)->maxHp,64),"Big Spider source20HPx3.2");
 std::cout<<"PASS source idle/acquisition, acceleration, committed bursts, wandering and shared movement\n";
}
void collision() {
 auto s=fixture();s.arena.obstacles.push_back({{-29,0,3},{29,4,4}});s.arena.rebuildWalls();auto id=s.spawnMonster(monsterId(85),{0,.85f,0});
 for(int n=0;n<140;++n){tick(s);const auto &e=*s.findEnemy(id);check(!e.spider->pursuing,"blocked sight does not acquire player chase");check(!s.arena.blocked(e.position,e.radius),"wander never enters solid cover");}
 auto stuck=fixture();id=stuck.spawnMonster(monsterId(85),{0,.85f,0});tick(stuck,32);stuck.arena.obstacles.push_back({{-29,0,1},{29,4,2}});stuck.arena.rebuildWalls();bool cancelled=false;
 for(int n=0;n<45;++n){tick(stuck);check(stuck.findEnemy(id)->position.z<.601f,"burst cannot penetrate newly blocked route");cancelled|=!stuck.findEnemy(id)->spider->targetReady;}
 check(cancelled,"low speed after countdown cancels a blocked burst");
 auto river=fixture();river.arena.canyon=std::make_shared<CanyonTerrain>();auto &f=*river.arena.canyon;
 f.x=f.z=-31;f.step=1;f.width=f.depth=63;f.heights.resize(63*63);
 for(int z=0;z<63;++z)for(int x=0;x<63;++x)f.heights[size_t(z*63+x)]=std::abs(z-31)<=2?-1.f:0.f;
 f.boundaryHeights=f.heights;f.riverKind=CanyonRiverKind::Interior;f.river={{{-30,0,0},2,0},{{30,0,0},2,60}};
 id=river.spawnMonster(monsterId(85),{0,.85f,-6});river.player.position={0,.85f,6};
 for(int n=0;n<240;++n){tick(river);const auto &body=*river.findEnemy(id);check(!f.waterBlocked(body.position)&&!river.arena.blocked(body.position,body.radius),"ordinary Spider never swims across a river");}
 auto contact=fixture();contact.godMode=false;id=contact.spawnMonster(monsterId(85),contact.player.position);tick(contact);
 check(near(contact.player.hp,StartingHealth-10*EnemyDamageMultiplier),"contact maps source half-heart through existing multiplier");
 auto fire=fixture();id=fire.spawnMonster(monsterId(85),{0,.85f,0});fire.addFire({0,.85f,0},2,2,30,true,false);tick(fire,2);check(!fire.findEnemy(id)||!fire.findEnemy(id)->alive,"ordinary Spider remains vulnerable to fire");
 auto stun=fixture();id=stun.spawnMonster(monsterId(85),{0,.85f,0});tick(stun,40);auto *e=stun.findEnemy(id);e->state=EnemyState::Stunned;e->stateTime=.3f;tick(stun,2);
 check(!stun.findEnemy(id)->spider->targetReady&&length(stun.findEnemy(id)->velocity)<.001f,"stun cancels committed movement");
 std::cout<<"PASS sight/solid collision, blocked-target recovery, contact, fire and interruption\n";
}
void children() {
 auto s=fixture();s.player.position={0,.85f,12};auto id=s.spawnMonster(monsterId(94),{0,.85f,0});damage(s,id,65);tick(s);
 check(s.livingEnemies()==2&&s.stats.kills==1,"exactly two regular children after normal death");
 std::vector<const Enemy*> kids;for(const auto &e:s.enemies)if(e.alive)kids.push_back(&e);
 for(const auto *e:kids)check(e->monster==monsterId(85)&&near(e->hp,20.8f)&&near(std::abs(e->position.x),1)&&near(e->position.z,0)&&near(std::abs(e->velocity.x),30)&&near(e->velocity.z,0),"perpendicular offsets, full health and outward source10velocity");
 check(dot(kids[0]->velocity,kids[1]->velocity)<-899,"opposite child impulses");
 auto over=fixture();id=over.spawnMonster(monsterId(94),{0,.85f,0});damage(over,id,128);tick(over);check(over.livingEnemies()==0,"post-hitHP<=-64 suppresses split");
 auto retained=fixture();retained.player.position={0,.85f,12};retained.debugScenario=false;id=retained.spawnMonster(monsterId(94),{0,.85f,0});retained.limits.enemies=0;damage(retained,id,65);tick(retained,3);
 check(!retained.roomClear&&retained.livingEnemies()==0,"capacity retains both deaths and seals room");
 retained.limits.enemies=1;tick(retained);check(retained.livingEnemies()==1&&!retained.roomClear,"one birth can be admitted while other remains pending");
 retained.limits.enemies=2;tick(retained);check(retained.livingEnemies()==2&&!retained.roomClear,"remaining independent child survives parent removal");
 retained.killAll();tick(retained);check(retained.roomClear,"all children must be defeated before completion");
 std::cout<<"PASS two outward death children, extreme-overkill suppression and retained completion\n";
}
void data() {
 Pack p;auto old=p.load(p.original);auto next=p.load(replace(p.original,".1 .6 6 14",".1 .6 5 14"));check(old->fingerprint()!=next->fingerprint()&&old->spider(monsterId(85))->force==6,"immutable external profile snapshots");
 for(auto invalid:{replace(p.original,".1 .6 6 14",".1 1 6 14"),replace(p.original,"100 200 10","200 100 10"),replace(p.original,"offspring_impulse 30","offspring_impulse -1"),p.original+"spider 85.0.0 .1 .6 6 14 15 100 200 10 70 110 14 3 20 10 60 70 40 60\n"}) {
  bool rejected=false;try{p.load(invalid);}catch(...){rejected=true;}check(rejected,"invalid or duplicate profiles rejected");
 }
 std::set<MonsterId> found;
 for(uint64_t seed=0;seed<128&&found.size()<2;++seed) {
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if((e.monster==monsterId(85)||e.monster==monsterId(94))&&found.insert(e.monster).second)
   std::cout<<"NATURAL_SPIDER id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor=0 room="<<room<<'\n';
 }
 check(found.size()==2,"both source identities have actual early-floor residents");
 std::cout<<"PASS validated configuration and actual seeded stage placement\n";
}
}
int main(){try{movement();collision();children();data();std::cout<<"PASS Spider and Big Spider\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
