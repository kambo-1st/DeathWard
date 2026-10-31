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
 std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-long-legs-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 std::string original;
 Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());std::ifstream in(path/"long_legs.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
 ~Pack(){std::filesystem::remove_all(path);}
 auto load(const std::string &s){std::ofstream(path/"long_legs.mechanics")<<s;return MechanicsLibrary::load(path);}
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
void hit(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;s.queueRoot(e);s.drainEvents();}
std::string forced(std::string text) {
 text=replace(text,".5 100 50 6 45 26",".5 1 1 6 45 26");
 text=replace(text,".5 200 100 6 45 26",".5 1 1 6 45 26");
 for(int n=0;n<2;++n)text=replace(text,".5 50 50 6 45 22",".5 1 1 6 45 22");
 return replace(text,"1.2 50 4 8 24","1.2 1 1 8 24");
}
void shots() {
 Pack pack;const auto lib=pack.load(forced(pack.original));
 for(int variant:{0,1}) {
  auto s=fixture(lib);const auto id=s.spawnMonster(monsterId(207,variant),{0,.85f,0});tick(s,4);
  check(s.findEnemy(id)->longLegs->frame==0,"Crazy enters45frame Attack");
  check(near(s.findEnemy(id)->hp,variant?51.2f:64.f),"source16/12 plus4stageHP conversion");
  tick(s,42);check(s.stats.projectiles==0&&s.findEnemy(id)->longLegs->frame==21,"no emission before Shoot22");
  s.player.position={-18,.85f,2};tick(s,2);const int count=variant?4:8;
  check(s.stats.projectiles==uint64_t(count)&&s.projectiles.size()==size_t(count),"Shoot22 emits exact diagonal/eightway count");
  std::set<std::pair<int,int>> directions;
  for(const auto &p:s.projectiles) {
   const auto v=horizontal(p.velocity);const float speed=length(v);
   check(speed>=24-.01f&&speed<=30+.01f,"shared native8..10speed scaledx3");
   check(near(p.gravity,27)&&near(p.flightRetention,.9f),"source falling acceleration and friction");
   const int x=v.x>.1f?1:v.x<-.1f?-1:0,z=v.z>.1f?1:v.z<-.1f?-1:0;
   directions.insert({x,z});if(variant)check(x&&z&&near(std::abs(v.x),std::abs(v.z)),"small variant uses fixed diagonals independent of aim");
  }
  check(directions.size()==size_t(count),"all directions distinct");tick(s,46);
  check(s.findEnemy(id)->longLegs->frame==-1&&s.findEnemy(id)->longLegs->attacks==1,"attack finishes at45without repeat emission");
 }
 auto s=fixture(lib);s.limits.projectiles=3;const auto id=s.spawnMonster(monsterId(207,1),{0,.85f,0});tick(s,70);
 check(s.findEnemy(id)->longLegs->frame==22&&!s.findEnemy(id)->longLegs->fired&&s.stats.projectiles==0,"capacity retains whole volley without partial discharge");
 s.limits.projectiles=20;tick(s,2);check(s.stats.projectiles==4,"retained volley emits once capacity becomes available");
 std::cout<<"PASS Crazy45/Shoot22,8way and4diagonal shots, stageHP, arc fields and atomic capacity\n";
}
void offspring() {
 Pack pack;auto text=replace(forced(pack.original),"85.0.0 20 0","85.0.0 1 0");const auto lib=pack.load(text);
 for(bool wet:{false,true}) {
  auto s=fixture(lib);if(wet){s.arena.profile.band=1;s.arena.profile.variant=FloorVariant::Flooded;}
  const auto id=s.spawnMonster(monsterId(206),{0,.85f,0});tick(s,4);tick(s,50);
  check(s.livingEnemies()==1&&s.findEnemy(id)->longLegs->frame==25,"no child before Lay26");tick(s,2);
  std::vector<const Enemy*> children;for(const auto &e:s.enemies)if(e.id!=id)children.push_back(&e);
  check(children.size()==2,"forced1in20twin choice lays two independent children");
  for(auto *e:children)check(e->monster==monsterId(wet?814:85)&&near(e->hp,20.8f)&&e->summoner==id,"wet allbirth substitution and full childHP/ownership");
  check(length(add(children[0]->velocity,children[1]->velocity))<.01f&&near(length(children[0]->velocity),3),"opposite randomunit source birth velocities");
  hit(s,id,1000);tick(s,2);check(s.livingEnemies()==2&&!s.roomClear,"children survive parent and retain room completion");
 }
 auto crowded=fixture(lib);auto id=crowded.spawnMonster(monsterId(206),{0,.85f,0});
 for(int n=0;n<5;++n)crowded.spawnMonster(monsterId(13),{float(n*2+12),.85f,15});tick(crowded,220);
 check(crowded.findEnemy(id)->longLegs->attacks==0,"six total room enemies suppress Baby laying");
 auto small=fixture(lib);id=small.spawnMonster(monsterId(206,1),{0,.85f,0});tick(small,56);
 const auto child=std::find_if(small.enemies.begin(),small.enemies.end(),[](const auto &e){return e.monster==monsterId(30,2);});
 check(child!=small.enemies.end()&&near(child->hp,22.4f)&&near(child->maxHp,64),"Small Baby lays partly grown7of20HP Sack without lowering maxHP");
 check(std::any_of(small.hazards.begin(),small.hazards.end(),[](const auto &h){return h.kind==HazardKind::Tar&&h.damage==0&&h.tint.r>200;}),"Small Baby lays slowing white creep");
 small.player.position=small.hazards.back().position;tick(small);check(small.player.slowTime>0,"white creep actually slows player");
 std::cout<<"PASS Baby45/Lay26, twins, population cap, independent wet children and Small Baby Sack/white creep\n";
}
void sacks() {
 Pack pack;const auto lib=pack.load(forced(pack.original));auto s=fixture(lib);const auto id=s.spawnMonster(monsterId(30,2),{0,.85f,0});
 check(near(s.findEnemy(id)->hp,22.4f)&&near(s.findEnemy(id)->maxHp,64),"Sack normal-mode initialHP7/20");
 tick(s,2);check(near(s.findEnemy(id)->hp,22.4f)&&near(s.findEnemy(id)->sack->growth,.0128f),"first growth update adds acceleration before subsequent healing");
 tick(s,2);check(near(s.findEnemy(id)->hp,22.449152f),"native prior growth times1.2 timesHPscale healing");
 hit(s,id,3);const float damaged=s.findEnemy(id)->hp;tick(s,2);
 check(near(s.findEnemy(id)->hp,damaged)&&near(s.findEnemy(id)->sack->growth,.0128f),"damage resets regenerative acceleration");
 tick(s,800);check(s.findEnemy(id)->hp>=63.99f,"Sack recovers to full health");
 bool thrown=false,landed=false;EntityId child=0;
 for(int n=0;n<600;++n) {
  tick(s);for(const auto &e:s.enemies)if(e.monster==monsterId(85)){child=e.id;thrown|=bool(e.thrownOffspring);if(thrown&&!e.thrownOffspring)landed=true;}
  if(landed)break;
 }
 check(thrown&&landed&&child,"Sack throws Spider through state6and lands into normal controller");
 check(s.findEnemy(child)->spider&&!s.findEnemy(child)->swimmer,"Spider landing initializes own controller");
 auto contact=fixture(lib);contact.godMode=false;const auto sack=contact.spawnMonster(monsterId(30,2),contact.player.position);tick(contact,10);
 check(near(contact.player.hp,100),"Sack deals no contact damage");hit(contact,sack,1000);tick(contact);check(contact.livingEnemies()==0,"lethal damage prevents regeneration");
 std::cout<<"PASS Sack growth/reset, swell, thrown Spider landing, noncontact and lethal damage\n";
}
void movementAndConfig() {
 Pack pack;auto text=pack.original;
 text=replace(text,".5 100 50 6", ".5 10000 10000 6");
 text=replace(text,".5 50 50 6", ".5 10000 10000 6");const auto lib=pack.load(text);
 auto chase=fixture(lib);chase.arena.obstacles.push_back({{-2,0,3},{2,3,5}});chase.arena.rebuildWalls();
 const auto id=chase.spawnMonster(monsterId(207),{0,.85f,0});bool passed=false;
 for(int n=0;n<500;++n){tick(chase);const auto &e=*chase.findEnemy(id);check(!chase.arena.blocked(e.position,e.radius),"Crazy path movement respects cover");passed|=e.position.z>6;}
 check(passed,"Crazy navigates around obstruction");
 auto flee=fixture(lib);flee.player.position={0,.85f,4};const auto baby=flee.spawnMonster(monsterId(206),{0,.85f,0});float farthest=0;
 for(int n=0;n<300;++n){tick(flee);farthest=std::max(farthest,planarDistance(flee.findEnemy(baby)->position,flee.player.position));}
 check(farthest>8,"Baby selects retreat paths");
 auto invalid=[&](const std::string &bad){try{pack.load(bad);}catch(const std::exception&){return;}throw std::runtime_error("invalid configuration accepted");};
 invalid(replace(pack.original,"45 26 85.0.0","26 26 85.0.0"));
 invalid(replace(pack.original,"0 8 8 10","0 5 8 10"));
 invalid(replace(pack.original,"3.2 7 .02 .64","3.2 21 .02 .64"));
 invalid(replace(pack.original,".5 100 50 6 45 26 85.0.0",".5 100 50 6 45 26 999.0.0"));
 check(lib->longLegs(monsterId(206))->chance==10000,"old content snapshot survives reload errors");
 std::cout<<"PASS ground pursuit/retreat and strict immutable config\n";
}
void natural() {
 std::set<MonsterId> wanted{monsterId(206),monsterId(206,1),monsterId(207),monsterId(207,1)};
 for(uint64_t seed=0;seed<160&&!wanted.empty();++seed) {
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
  for(int room=0;room<s.arena.roomCount();++room)for(const auto &e:s.roomEnemies(room))if(wanted.erase(e.monster))
   std::cout<<"NATURAL_LONG_LEGS id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor=0 room="<<room<<'\n';
 }
 check(wanted.empty(),"all four Long Legs identities occur in real seeded rooms");
}
}
int main(){try{shots();offspring();sacks();movementAndConfig();natural();std::cout<<"PASS Long Legs and Sack\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
