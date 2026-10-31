#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *s){if(!ok)throw std::runtime_error(s);}
bool near(float a,float b,float eps=.003f){return std::abs(a-b)<eps;}
Simulation fixture(){
 Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0);
 s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,10,80}};
 for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-80,-.4f,-80},{80,0,80}}};}
 s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.stats={};s.rooms.assign(s.arena.roomCount(),{});
 s.room=0;s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,20};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void frame(Simulation &s,EntityId id,int f){for(int i=0;i<800&&s.findEnemy(id)->host->frame!=f;++i)tick(s);check(s.findEnemy(id)->host->frame==f,"source frame reached");}
void hit(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;s.queueRoot(e);s.drainEvents();}
EntityId slam(Simulation &s){auto id=s.spawnMonster(monsterId(27,3),{0,.85f,0});frame(s,id,53);check(s.hazards.empty()&&s.stats.projectiles==0,"no early wave/bullet");frame(s,id,54);check(s.hazards.size()==1&&s.hazards[0].rockWave,"Close54 emits configured rock generator");return id;}
void cycle(){
 auto s=fixture();auto id=s.spawnMonster(monsterId(27,3),{0,.85f,0});check(near(s.findEnemy(id)->hp,48),"15sourceHP converted once");
 hit(s,id,4);check(near(s.findEnemy(id)->hp,48),"closed armor");frame(s,id,10);hit(s,id,4);check(near(s.findEnemy(id)->hp,44),"Open10 vulnerable");
 frame(s,id,53);s.player.position={20,.85f,0};frame(s,id,54);check(!s.findEnemy(id)->host->exposed&&s.hazards.size()==1,"close and slam share event");
 check(s.hazards[0].rockWave->heading.x>.999f&&near(s.hazards[0].origin.x,2),"live slam aim and20source-unit launch offset");
 hit(s,id,4,DamageKind::Crush);check(near(s.findEnemy(id)->hp,44),"closed armor rejects crush");hit(s,id,4,DamageKind::Burning);check(near(s.findEnemy(id)->hp,40),"burning bypass");
 frame(s,id,70);tick(s,2);check(s.findEnemy(id)->host->frame==-1&&s.findEnemy(id)->host->cooldown==7,"71frame cycle and retained idle cooldown");
 check(s.stats.projectiles==0&&s.stats.explosions==0,"rock pulse never masquerades as bullet or bomb");
 auto c=fixture();c.godMode=false;c.player.position={0,.85f,0};c.spawnMonster(monsterId(27,3),c.player.position);tick(c,2);check(c.player.hp<100,"Hard Host has source contact damage");
}
void stepping(){
 auto s=fixture();slam(s);auto &w=s.hazards[0];const auto start=w.position;
 while(s.hazards[0].rockWave->frame<6)tick(s);
 check(near(s.hazards[0].position.z-start.z,9)&&near(s.hazards[0].position.x,0),"first three bursts straight3world-unit steps");
 auto a=fixture(),b=fixture();slam(a);slam(b);a.player.position=b.player.position={60,.85f,-60};
 tick(a,36);tick(b,36);check(!a.hazards.empty()&&distance(a.hazards[0].position,b.hazards[0].position)<.001f,"seeded wave RNG repeatable");
 check(std::abs(a.hazards[0].position.x)>.01f,"subtype2 increasingly wanders after frame6");
 auto capped=fixture();auto id=capped.spawnMonster(monsterId(27,3),{0,.85f,0});capped.limits.hazards=0;tick(capped,160);
 check(capped.findEnemy(id)->host->frame==54&&!capped.findEnemy(id)->host->fired,"hazard pressure retains slam");
 capped.limits.hazards=1;tick(capped,2);check(capped.hazards.size()==1&&capped.findEnemy(id)->host->fired,"capacity recovery emits once");
}
Breakable prop(int id,BreakableKind kind,Box box){Breakable p;p.id=id;p.kind=kind;p.room=0;p.bounds=box;p.health=2;p.lootSeed=17;p.rewardPosition=mul(add(box.min,box.max),.5f);return p;}
void damageAndTerrain(){
 for(bool reversed:{false,true}) {
  auto s=fixture();auto owner=slam(s);s.player.position={0,.85f,5};s.godMode=false;
  // Configure after launch so acquisition sees the player; this also ensures
  // the first pulse's destruction is tested independently of body pathfinding.
  s.arena.breakables={prop(1,BreakableKind::CrackedRock,{{-.2f,0,4.7f},{.2f,2,4.8f}}),prop(2,BreakableKind::CrackedRock,{{-1,0,10},{1,2,10.5f}})};
  if(reversed)std::reverse(s.arena.breakables.begin(),s.arena.breakables.end());s.arena.rebuildWalls();
  const auto bombs=s.dynamite;tick(s,4);
  check(s.arena.breakables[reversed?1:0].destroyed&&!s.arena.breakables[reversed?0:1].destroyed,"thin first obstacle consumed, later rock retained independent of vector order");
  check(s.hazards.empty()&&s.dynamite==bombs&&s.stats.explosions==0,"destructive wave stops without spending bomb inventory");
  check(s.player.hp==100-10*EnemyDamageMultiplier,"crush pulse uses native no-entity-line-check through nearby impacted cover");
  check(s.findEnemy(owner)->alive,"owner excluded from crush pulse");
 }
 auto s=fixture();slam(s);auto victim=s.spawnMonster(monsterId(13),{0,.85f,5});s.findEnemy(victim)->hp=s.findEnemy(victim)->maxHp=100;s.findEnemy(victim)->state=EnemyState::Stunned;s.findEnemy(victim)->stateTime=10;
 tick(s,4);check(near(s.findEnemy(victim)->hp,68),"crush damages NPC by10sourceHP not player half-heart conversion");
 auto pressure=fixture();slam(pressure);victim=pressure.spawnMonster(monsterId(13),{0,.85f,5});pressure.findEnemy(victim)->state=EnemyState::Stunned;pressure.findEnemy(victim)->stateTime=10;
 pressure.limits.queuedEvents=0;tick(pressure,8);check(pressure.hazards[0].rockWave->frame==0,"queued-event pressure retains pulse point and source frame");pressure.limits.queuedEvents=512;tick(pressure,1);check(pressure.hazards[0].rockWave->frame>0,"pending pulse recovers");
 auto pit=fixture();slam(pit);for(int x=-80;x<80;++x)for(int z=-80;z<4;++z)pit.arena.floorCells.insert({int(std::floor(float(x)/FloorTile)),int(std::floor(float(z)/FloorTile))});
 tick(pit,4);check(pit.hazards.empty(),"ground wave consumed by pit");
 auto ore=fixture();slam(ore);ore.arena.breakables={prop(1,BreakableKind::OreSeam,{{-1,0,5},{1,2,5.1f}})};ore.arena.rebuildWalls();tick(ore,8);check(!ore.arena.breakables[0].destroyed,"declared local ore gate protection");
}
void launchAndLifecycle(){
 auto s=fixture();s.player.position={0,.85f,8};auto id=slam(s);check(bool(s.player.launch),"nearby slam launches grounded player");
 const float ground=.85f;tick(s,2);check(near(s.player.position.y,ground+.9f),"first source hop frame uses9native units");
 tick(s,2);check(near(s.player.position.y,ground+1.69f),"source1.1gravity recurrence");tick(s,44);check(!s.player.launch&&near(s.player.position.y,ground),"finite hop lands exactly");
 auto wall=fixture();wall.player.position={0,.85f,8};slam(wall);wall.arena.boundaryWalls={{{-80,-1,8.8f},{80,20,9}}};wall.arena.rebuildWalls();tick(wall,30);check(wall.player.position.z<8.33f,"horizontal shove cannot vault walls while airborne");
 auto distant=fixture();distant.player.position.z=12;slam(distant);check(!distant.player.launch,"strict120native-unit slam range");
 auto leave=fixture();leave.player.position.z=8;slam(leave);tick(leave,8);leave.enterRoom(1);check(!leave.player.launch&&near(leave.player.position.y,.85f)&&leave.hazards.empty(),"room transition clears hop and generator");
 auto dying=fixture();id=slam(dying);dying.killAll();tick(dying,2);check(dying.livingEnemies()==0&&!dying.hazards.empty(),"emitted wave survives owner death and room clear");
 auto early=fixture();id=early.spawnMonster(monsterId(27,3),{0,.85f,0});frame(early,id,10);hit(early,id,1000);tick(early,150);check(early.hazards.empty(),"death before slam cancels pending wave");
}
void configuration(){
 auto root=std::filesystem::temp_directory_path()/("dw-hard-host-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(root);
 for(const auto &p:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(p.path().extension()==".mechanics")std::filesystem::copy_file(p.path(),root/p.path().filename());
 const auto file=root/"hosts.mechanics";std::ifstream in(file);const std::string original((std::istreambuf_iterator<char>(in)),{});
 for(auto pair:{std::pair{"71 10 54 54","71 10 53 54"},std::pair{"2 240 6 20 3 2","0 240 6 20 3 2"},std::pair{"75 .5 2 12 9 27 99 .8","75 .5 2 12 9 27 0 .8"}}){auto text=original;auto at=text.find(pair.first);check(at!=text.npos,"configuration mutation exists");text.replace(at,std::string(pair.first).size(),pair.second);std::ofstream(file)<<text;bool bad=false;try{MechanicsLibrary::load(root);}catch(...){bad=true;}check(bad,"invalid slam rejected");}
 std::ofstream(file)<<original;auto before=MechanicsLibrary::load(root);auto text=original;auto at=text.find("2 240 6 20 3 2");text.replace(at,14,"2 240 6 20 4 2");std::ofstream(file)<<text;auto after=MechanicsLibrary::load(root);
 check(near(before->host(monsterId(27,3))->slam->wave.spacing,3)&&near(after->host(monsterId(27,3))->slam->wave.spacing,4)&&before->fingerprint()!=after->fingerprint(),"immutable external wave reload");std::filesystem::remove_all(root);
}
void placement(){
 bool found=false;for(uint64_t seed=0;seed<128&&!found;++seed){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(27,3)){
   check(s.arena.profile.band==1&&near(e.hp,48),"Mines/Ashpit band and source HP");std::cout<<"NATURAL_HARD_HOST seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';found=true;break;}
 }
 check(found,"seeded hard host witness");
}
}
int main(){try{cycle();stepping();damageAndTerrain();launchAndLifecycle();configuration();placement();std::cout<<"PASS Hard Host source slam, crush generator, terrain, hop, lifecycle, limits and config\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
