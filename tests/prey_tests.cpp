#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
struct Pack {
 std::filesystem::path dir=std::filesystem::temp_directory_path()/("dw-prey-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 std::string original;
 Pack(){std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());std::ifstream in(dir/"prey.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
 ~Pack(){std::filesystem::remove_all(dir);}
 auto load(const std::string &s){std::ofstream(dir/"prey.mechanics")<<s;return MechanicsLibrary::load(dir);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){auto n=s.find(a);check(n!=s.npos,"fixture directive exists");s.replace(n,a.size(),b);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
 Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
 s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
 for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
 s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
 s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
 s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,25};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
void motion() {
 auto s=fixture();s.arena.rooms[0].flooded=true;auto id=s.spawnMonster(monsterId(810),{0,.85f,0});
 check(near(s.findEnemy(id)->hp,16),"source5HPx3.2");tick(s,2);
 check(near(s.findEnemy(id)->swimmer->acceleration,.016f)&&near(s.findEnemy(id)->velocity.z,.016f*.96f*3),"first source swimming impulse and friction");
 float expected=.016f*.96f;
 for(int frame=2;frame<=22;++frame)expected=(expected+std::min(.35f,.016f*frame))*.96f;
 tick(s,42);check(near(s.findEnemy(id)->swimmer->acceleration,.35f)&&near(s.findEnemy(id)->velocity.z,expected*3),"swimming acceleration and accumulated speed match22sourceupdates");
 auto bounce=fixture();bounce.arena.rooms[0].flooded=true;auto edge=bounce.spawnMonster(monsterId(810),{29.2f,.85f,0});
 bounce.player.position={40,.85f,0};bounce.findEnemy(edge)->velocity={3,0,0};tick(bounce,2);
 check(bounce.findEnemy(edge)->velocity.x<0,"wet boundary reverses outward momentum before wall");
 Pack p;auto lib=p.load(replace(p.original,".7 2 2 4 10 6", ".7 1 2 4 10 6"));auto dry=fixture(lib);id=dry.spawnMonster(monsterId(810),{0,.85f,0});
 tick(dry,2);check(dry.findEnemy(id)->swimmer->hopFrame==0,"dry hop begins on configured random check");
 const float speed=length(dry.findEnemy(id)->velocity);check(speed>=6&&speed<=12,"source2..4hop impulse converted to local velocity");
 tick(dry,10);check(dry.findEnemy(id)->swimmer->hopFrame==5&&dry.findEnemy(id)->lift>0&&near(length(dry.findEnemy(id)->velocity),speed),"hop coasts before Land6");
 tick(dry,2);check(dry.findEnemy(id)->swimmer->hopFrame==6&&near(dry.findEnemy(id)->lift,0)&&near(length(dry.findEnemy(id)->velocity),speed*.7f),"Land6 restores source ground damping");
 tick(dry,8);check(dry.findEnemy(id)->swimmer->hopFrame==-1,"hop animation ends at10sourceframes");
 auto *e=dry.findEnemy(id);e->state=EnemyState::Stunned;e->stateTime=.2f;tick(dry,10);check(e->state==EnemyState::Stunned&&near(length(e->velocity),0),"stun stops movement");
 std::cout<<"PASS swimming acceleration and source Hop10/Land6 timing\n";
}
void terrain() {
 auto s=fixture();auto &a=s.arena;a.canyon=std::make_shared<CanyonTerrain>();auto &f=*a.canyon;
 f.x=f.z=-31;f.step=1;f.width=f.depth=63;f.heights.resize(63*63);
 for(int z=0;z<63;++z)for(int x=0;x<63;++x)f.heights[size_t(z*63+x)]=std::abs(z-31)<=2?-1.f:0.f;
 f.boundaryHeights=f.heights;f.riverKind=CanyonRiverKind::Interior;f.river={{{-30,0,0},2,0},{{30,0,0},2,60}};f.riverRooms={0};
 check(a.blocked({0,.85f,0},.45f)&&!a.swimBlocked({0,.85f,0},.45f,0),"deep water blocks ground but permits swimming");
 check(!a.clear({0,.85f,-6},{0,.85f,6},.45f)&&a.swimClear({0,.85f,-6},{0,.85f,6},.45f,0),"water crossing uses distinct swept collision");
 s.player.position={0,.85f,12};auto id=s.spawnMonster(monsterId(810),{0,.85f,-6});tick(s,100);
 check(s.findEnemy(id)->position.z>3,"actual small leech crosses the river");
 a.boundaryWalls.push_back({{-3,0,1},{3,2,2}});a.rebuildWalls();
 check(a.swimBlocked({0,.85f,1.5f},.45f,0)&&!a.swimClear({0,.85f,-4},{0,.85f,4},.45f,0),"swimming cannot cross solid cover");
 check(a.swimBlocked({30,.85f,0},.45f,0),"swimming cannot escape room through boundary water");
 auto blocked=fixture();blocked.arena.rooms[0].flooded=true;blocked.arena.boundaryWalls.push_back({{-4,0,0},{4,3,1}});blocked.arena.rebuildWalls();
 id=blocked.spawnMonster(monsterId(810),{0,.85f,-3});blocked.player.position={0,.85f,10};tick(blocked,150);
 check(blocked.findEnemy(id)->position.z<-.4f,"wet pursuit still respects rock geometry");
 std::cout<<"PASS real river crossing, solid obstacles and room boundaries\n";
}
void spawning() {
 Pack p;auto lib=p.load(replace(p.original,".8 .5 .9 1.079 30", ".8 0 .9 0 30"));auto s=fixture(lib);s.player.position={0,.85f,10};
 auto id=s.spawnMonster(monsterId(817),{0,.85f,0});check(near(s.findEnemy(id)->hp,44.8f),"Prey source14HPx3.2");
 for(int n=0;n<100&&(!s.findEnemy(id)->evader||s.findEnemy(id)->evader->attackFrame<0);++n)tick(s);
 tick(s,7);check(s.livingEnemies()==1,"live child waits for Shoot4");tick(s);
 auto child=std::find_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.summoner==id;});
 check(child!=s.enemies.end()&&child->monster==monsterId(810)&&near(child->hp,16)&&!child->buzz,"Prey emits persistent full-health Small Leech");
 for(int others:{0,2,5}) {
  auto q=fixture();id=q.spawnMonster(monsterId(817),{0,.85f,0});
  for(int i=0;i<others;++i)q.spawnMonster(monsterId(12),{float(i*3-9),.85f,-18});
  damage(q,id,45);tick(q);
  const int children=int(std::count_if(q.enemies.begin(),q.enemies.end(),[](const auto &e){return e.alive&&e.monster==monsterId(810);}));
  check(children==(others==0?3:others==2?2:1),"Prey uses population-adjusted death count with minimum1");
  for(const auto &e:q.enemies)if(e.alive&&e.monster==monsterId(810))check(e.thrownOffspring&&near(e.position.x,0)&&near(e.position.z,0)&&near(e.position.y,1.85f),"death children begin thrown at parent with source initial height");
  tick(q,20);
  for(const auto &e:q.enemies)if(e.alive&&e.monster==monsterId(810))check(e.thrownOffspring&&e.position.y>5,"thrown birth follows source gravity arc");
  tick(q,24);
  for(const auto &e:q.enemies)if(e.alive&&e.monster==monsterId(810))check(bool(e.thrownOffspring),"thrown state remains through22sourceframes");
  tick(q,2);
  for(const auto &e:q.enemies)if(e.alive&&e.monster==monsterId(810))check(!e.thrownOffspring&&near(e.position.y,.85f)&&!q.arena.blocked(e.position,e.radius),"source23frame landing restores legal ground body");
 }
 auto pending=fixture();pending.debugScenario=false;id=pending.spawnMonster(monsterId(817),{0,.85f,0});pending.limits.enemies=0;
 damage(pending,id,45);tick(pending,5);check(!pending.roomClear&&pending.livingEnemies()==0,"retained death children keep room sealed");
 pending.limits.enemies=3;tick(pending);check(pending.livingEnemies()==3&&!pending.roomClear,"all retained children resume");
 auto overkill=fixture();id=overkill.spawnMonster(monsterId(817),{0,.85f,0});damage(overkill,id,109);tick(overkill);check(overkill.livingEnemies()==0,"source-20scaled overkill suppresses children");
 auto contact=fixture();contact.player.position={0,.85f,0};contact.spawnMonster(monsterId(810),{0,.85f,0});tick(contact);
 check(near(contact.player.hp,StartingHealth-10*EnemyDamageMultiplier),"Small Leech contact uses half-heart conversion");
 auto harmless=fixture();harmless.spawnMonster(monsterId(817),harmless.player.position);tick(harmless);check(near(harmless.player.hp,StartingHealth),"Prey body is harmless");
 std::cout<<"PASS Prey health, live/death offspring, population, retained births, overkill and contacts\n";
}
void airborneCollision() {
 auto s=fixture();auto parent=s.spawnMonster(monsterId(817),{0,.85f,0});damage(s,parent,45);tick(s,13);
 auto child=std::find_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.alive&&e.monster==monsterId(810);});
 check(child!=s.enemies.end()&&bool(child->thrownOffspring),"fixture has thrown child");
 const auto id=child->id;const auto position=child->position;
 Event shot;shot.type=EventType::Shot;shot.position=add(position,{1,0,0});shot.direction={-1,0,0};shot.damage=8;shot.speed=100;
 s.queueRoot(shot);s.drainEvents();tick(s,2);check(near(s.findEnemy(id)->hp,16),"airborne birth ignores projectile entity collision");
 Event blast;blast.type=EventType::Damage;blast.areaDamage=true;blast.target=id;blast.damage=3;s.queueRoot(blast);s.drainEvents();
 check(near(s.findEnemy(id)->hp,13),"entity collision zero does not grant bomb immunity");
 s.player.position=s.findEnemy(id)->position;s.player.position.y=.85f;const auto hp=s.player.hp;tick(s);
 check(near(s.player.hp,hp),"airborne child has no contact damage");
 s.player.position={20,.85f,20};tick(s,40);check(!s.findEnemy(id)->thrownOffspring,"collision policy restores after landing");
 const auto landed=s.findEnemy(id)->position;shot.position=add(landed,{.7f,0,0});s.queueRoot(shot);s.drainEvents();tick(s,2);
 check(s.findEnemy(id)->hp<13,"landed body can be hit by a projectile again");
 auto crowded=fixture();crowded.arena.obstacles.push_back({{-3,0,-3},{-1,5,3}});crowded.arena.rebuildWalls();
 parent=crowded.spawnMonster(monsterId(817),{0,.85f,0});damage(crowded,parent,45);
 for(int frame=0;frame<70;++frame) {
  tick(crowded);
  for(const auto &e:crowded.enemies)if(e.alive&&e.monster==monsterId(810))check(!sphereBox(e.position,e.radius,crowded.arena.obstacles[0]),"birth arc never intersects physical cover");
 }
 check(crowded.livingEnemies()==3,"cover search admits all three children");
 std::cout<<"PASS airborne projectile/contact policy, blast vulnerability, landing and obstacle arcs\n";
}
void data() {
 Pack p;auto before=p.load(p.original);auto after=p.load(replace(p.original,".016 .35 .96", ".02 .35 .96"));
 check(before->fingerprint()!=after->fingerprint()&&near(before->swimmer(monsterId(810))->acceleration,.016f),"immutable external snapshots");
 for(auto bad:{replace(p.original,".016 .35", ".4 .35"),replace(p.original,"10 6 .35", "10 10 .35"),replace(p.original,"population_adjustment -1 1", "population_adjustment -1 99"),replace(p.original,"-10 -8 .7 .04", "-10 -8 0 .04")}) {
  bool rejected=false;try{p.load(bad);}catch(...){rejected=true;}check(rejected,"invalid swimmer/death configuration rejected");
 }
 std::set<MonsterId> found;
 for(uint64_t seed=0;seed<1024&&found.size()<2;++seed) {
  ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
  for(int floor=0;floor<plan.floorCount&&found.size()<2;++floor) {
  // Added specialists change weighted choices. Search the actual approved
  // habitat across both possible Quarry floors, not just one old seed window.
  const auto profile=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
  if(profile.band!=1||profile.variant!=FloorVariant::Flooded)continue;
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if((e.monster==monsterId(810)||e.monster==monsterId(817))&&found.insert(e.monster).second) {
   check(s.arena.profile.variant==FloorVariant::Flooded,"approved wet Quarry context");
   std::cout<<"NATURAL_PREY_FAMILY id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
  }
  }
 }
 check(found.size()==2,"both regular identities have actual natural floor residents");
 std::cout<<"PASS validated snapshots and natural Prey/Small Leech placement\n";
}
}
int main(){try{motion();terrain();spawning();airborneCollision();data();std::cout<<"PASS Prey and Small Leech\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
