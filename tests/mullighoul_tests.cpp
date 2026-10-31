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
 std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-willo-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 std::string original;
 Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());std::ifstream in(path/"mullighoul.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
 ~Pack(){std::filesystem::remove_all(path);}
 auto load(std::string s){std::ofstream(path/"mullighoul.mechanics")<<s;return MechanicsLibrary::load(path);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){const auto n=s.find(a);check(n!=s.npos,"fixture directive");s.replace(n,a.size(),b);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
 Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
 s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
 for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
 s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
 s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
 s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,0};s.godMode=true;return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
void orbit() {
 auto s=fixture();std::vector<EntityId> ids;
 for(int n=0;n<4;++n)ids.push_back(s.spawnMonster(monsterId(808),{float(n*2),.85f,0}));
 tick(s,180);for(size_t n=0;n<ids.size();++n) {
  const auto &e=*s.findEnemy(ids[n]);check(near(e.maxHp,19.2f),"Willo6sourceHPx3.2");
  check(near(e.willo->slot,float(n)*Pi/2),"cohort receives evenly spaced native offsets");
  const auto delta=sub(e.position,s.player.position);const float ellipse=std::sqrt(delta.x*delta.x/144+delta.z*delta.z/(10.08f*10.08f));
  check(std::abs(ellipse-1)<.08f,"Willo settles into source120x100.8 ellipse");
 }
 const auto committed=s.findEnemy(ids[1])->willo->attackSlot;
 damage(s,ids[0],20);tick(s);check(s.livingEnemies()==3,"one orbit member can die");
 check(near(s.findEnemy(ids[1])->willo->slot,Pi/2)&&near(s.findEnemy(ids[2])->willo->slot,Pi/2+2*Pi/3),"death redistributes surviving offsets from their minimum");
 if(s.findEnemy(ids[1])->willo->attackFrame>=0)check(near(s.findEnemy(ids[1])->willo->attackSlot,committed),"active shooter retains attack slot during regrouping");
 s.player.position={5,.85f,-4};tick(s,90);
 for(const auto &e:s.enemies)if(e.alive){const auto d=sub(e.position,s.player.position);check(std::abs(std::sqrt(d.x*d.x/144+d.z*d.z/101.6064f)-1)<.1f,"orbit recentres on player movement");}
 for(int n=0;n<600;++n){tick(s);int firing=0;for(const auto &e:s.enemies)if(e.alive&&e.willo&&e.willo->attackFrame>=0)++firing;check(firing<=1,"cohort permits only one active attack");}
 std::cout<<"PASS elliptical player orbit, redistribution and attack serialization\n";
}
void attacks() {
 Pack pack;auto lib=pack.load(replace(pack.original,"20 9 36","20 1 36"));auto s=fixture(lib);
 const auto id=s.spawnMonster(monsterId(808),{12,.85f,0});
 for(int n=0;n<100&&(!s.findEnemy(id)->willo||s.findEnemy(id)->willo->attackFrame<0);++n)tick(s);
 check(s.findEnemy(id)->willo->attackFrame==0,"settled Willo starts source Attack");
 tick(s,10);check(s.findEnemy(id)->willo->attackFrame==5&&!s.findEnemy(id)->willo->warning,"warning does not start before6");
 tick(s,2);check(s.findEnemy(id)->willo->warning&&s.stats.projectiles==0,"Warn6 precedes the shot");
 tick(s,34);check(s.findEnemy(id)->willo->attackFrame==23&&s.stats.projectiles==0,"no shot before24");
 tick(s,2);check(s.stats.projectiles==1&&!s.findEnemy(id)->willo->warning,"Shoot24 emits one shot and stops warning");
 const auto &p=s.projectiles.front();check(p.noWallCollision&&near(length(horizontal(p.velocity)),30),"source10velocity and NO_WALL_COLLIDE preserved");
 check(p.gravity==9&&near(p.flightRetention,.9f)&&p.velocity.y<0,"source downward damped shot is configured");
 tick(s,24);check(s.findEnemy(id)->willo->attackFrame==-1,"Attack36 returns ready");
 auto held=fixture(lib);const auto a=held.spawnMonster(monsterId(808),{12,.85f,0});
 for(int n=0;n<100&&(!held.findEnemy(a)->willo||held.findEnemy(a)->willo->attackFrame<0);++n)tick(held);
 held.limits.projectiles=0;tick(held,80);check(held.findEnemy(a)->willo->attackFrame==24&&held.stats.projectiles==0,"capacity holds Shoot event without losing attack");
 held.limits.projectiles=10;tick(held,2);check(held.stats.projectiles==1,"retained Shoot resumes exactly once");
 held.findEnemy(a)->state=EnemyState::Stunned;held.findEnemy(a)->stateTime=.3f;tick(held,6);
 check(held.findEnemy(a)->willo->attackFrame==-1&&!held.findEnemy(a)->willo->warning&&near(length(held.findEnemy(a)->velocity),0),"stun interrupts attack and releases cohort lock");
 std::cout<<"PASS Warn6/Shoot24/Attack36, damped shot, capacity and stun\n";
}
void collision() {
 auto s=fixture();s.godMode=false;auto id=s.spawnMonster(monsterId(808),s.player.position);tick(s);check(near(s.player.hp,StartingHealth),"Willo body is harmless");
 damage(s,id,20);check(!s.findEnemy(id)->alive,"Willo is normally vulnerable");
 auto wall=fixture();wall.godMode=false;wall.arena.obstacles.push_back({{-2,0,3},{2,4,4}});wall.arena.rebuildWalls();
 Event shot;shot.hostile=true;shot.position=shot.origin={0,1.15f,8};shot.direction=unit(Vector3{0,-1.5f,-30});shot.speed=length(Vector3{0,-1.5f,-30});
 shot.damage=10;shot.projectileGravity=9;shot.projectileFlightRetention=.9f;shot.projectileRadius=.25f;shot.noWallCollision=true;
 wall.queueRoot(shot);wall.drainEvents();tick(wall,20);check(near(wall.player.hp,StartingHealth-10*EnemyDamageMultiplier),"Willo projectile passes cover and still hits player");
 auto ordinary=fixture();ordinary.godMode=false;ordinary.arena=wall.arena;shot.noWallCollision=false;ordinary.queueRoot(shot);ordinary.drainEvents();tick(ordinary,20);
 check(near(ordinary.player.hp,StartingHealth),"ordinary projectiles retain wall collision");
 auto fly=fixture();fly.arena.obstacles.push_back({{-20,0,-2},{20,4,2}});fly.arena.rebuildWalls();id=fly.spawnMonster(monsterId(808),{0,.85f,-10});bool crossed=false;
 for(int n=0;n<160;++n){tick(fly);crossed|=fly.findEnemy(id)->position.z>2;}check(crossed,"source Willo body orbit ignores grid cover");
 auto fire=fixture();id=fire.spawnMonster(monsterId(808),{12,.85f,0});fire.addFire({0,.85f,0},20,2,30,true,false);tick(fire,2);
 check(!fire.findEnemy(id)||!fire.findEnemy(id)->alive,"Willo can be killed by environmental fire");
 std::cout<<"PASS body/contact/fire vulnerability and separate wall-passing projectile policy\n";
}
void parent() {
 auto s=fixture();s.player.position={0,.85f,10};auto id=s.spawnMonster(monsterId(817,1),{0,.85f,0});tick(s,100);
 check(near(s.findEnemy(id)->maxHp,44.8f)&&near(s.findEnemy(id)->position.y,1.45f),"Mullighoul installed14HP and hover height");
 check(std::any_of(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.monster==monsterId(808)&&e.summoner==id&&near(e.maxHp,19.2f);}),"live Shoot emits full Willo");
 for(int others:{0,2,5}) {
  auto q=fixture();q.player.position={20,.85f,20};id=q.spawnMonster(monsterId(817,1),{0,.85f,0});
  for(int n=0;n<others;++n)q.spawnMonster(monsterId(12),{float(n*3-9),.85f,-18});damage(q,id,45);tick(q);
  const auto count=std::count_if(q.enemies.begin(),q.enemies.end(),[](const auto &e){return e.alive&&e.monster==monsterId(808);});
  check(count==(others==0?3:others==2?2:1),"native817death population formula applies to Mullighoul");
 }
 auto over=fixture();id=over.spawnMonster(monsterId(817,1),{0,.85f,0});damage(over,id,109);tick(over);check(over.livingEnemies()==0,"scaled overkill suppresses Willos");
 auto pending=fixture();pending.player.position={20,.85f,20};pending.debugScenario=false;id=pending.spawnMonster(monsterId(817,1),{0,.85f,0});pending.limits.enemies=0;
 damage(pending,id,45);tick(pending,3);check(!pending.roomClear&&pending.livingEnemies()==0,"retained death Willos seal room");
 pending.limits.enemies=3;tick(pending);check(pending.livingEnemies()==3&&!pending.roomClear,"all reserved Willos admitted before completion");
 pending.killAll();tick(pending);check(pending.roomClear,"killing all child threats completes room");
 auto nav=fixture();auto &a=nav.arena;a.canyon=std::make_shared<CanyonTerrain>();auto &f=*a.canyon;f.x=f.z=-31;f.step=1;f.width=f.depth=63;f.heights.resize(63*63);
 for(int z=0;z<63;++z)for(int x=0;x<63;++x)f.heights[size_t(z*63+x)]=std::abs(z-31)<=2?-1.f:0.f;
 f.boundaryHeights=f.heights;f.riverKind=CanyonRiverKind::Interior;f.river={{{-30,0,0},2,0},{{30,0,0},2,60}};
 check(!a.clear({0,.85f,-6},{0,.85f,6},.7f)&&!a.swimPath({0,.85f,-6},{0,.85f,6},.7f,0).empty(),"hover path crosses pits even without flooded room tag");
 a.obstacles.push_back({{-2,0,-1},{2,3,1}});a.rebuildWalls();auto path=a.swimPath({0,.85f,-6},{0,.85f,6},.7f,0);check(!path.empty(),"hover path can route around solid rocks over water");
 Vector3 at{0,.85f,-6};for(auto p:path){check(a.swimClear(at,p,.7f,0),"hover path sweeps every segment against solids");at=p;}
 id=nav.spawnMonster(monsterId(817,1),{5,.85f,-6});nav.player.position={5,.85f,-15};bool wet=false;
 for(int n=0;n<500;++n){tick(nav);const auto &e=*nav.findEnemy(id);wet|=a.canyon->waterBlocked(e.position);check(!a.swimBlocked(e.position,e.radius,0),"actual hover movement never enters rock or boundary");}
 check(wet,"actual fleeing Mullighoul crosses water");
 std::cout<<"PASS Mullighoul live/death children,overkill,completion and hover navigation\n";
}
void data() {
 Pack p;auto before=p.load(p.original);auto after=p.load(replace(p.original,"120 .84","100 .84"));check(before->fingerprint()!=after->fingerprint()&&before->willo(monsterId(808))->radius==120,"immutable profile snapshots");
 for(auto bad:{replace(p.original,"36 6 24","36 6 40"),replace(p.original,"1.15 -1.5 9 .9","1.15 -1.5 9 1"),replace(p.original,"evader_hover 817.1.0 .6","evader_hover 817.1.0 -1")}) {bool no=false;try{p.load(bad);}catch(...){no=true;}check(no,"invalid profiles rejected");}
 std::set<MonsterId> found;
 for(uint64_t seed=0;seed<256&&found.size()<2;++seed) {
  ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if((e.monster==monsterId(808)||e.monster==monsterId(817,1))&&found.insert(e.monster).second){check(s.arena.profile.variant==FloorVariant::Flooded,"approved wet band1 habitat");std::cout<<"NATURAL_WILLO_FAMILY id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';}
 }
 check(found.size()==2,"both regular identities have actual seeded floor residents");
 std::cout<<"PASS validated content and seeded Willo/Mullighoul residents\n";
}
}
int main(){try{orbit();attacks();collision();parent();data();std::cout<<"PASS Willo and Mullighoul\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
