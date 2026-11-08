#include "../tools/enemy_movement_calibration.hpp"
#include <chrono>
#include <iostream>
using namespace dw;
namespace {
void check(bool ok,const char *why){movement_review::require(ok,why);}
void near(double a,double b,double tolerance,const char *why){if(std::abs(a-b)>tolerance){std::cerr<<a<<" != "<<b<<'\n';check(false,why);}}
std::string read(const std::filesystem::path &p){std::ifstream f(p);return {(std::istreambuf_iterator<char>(f)),{}};}
struct Temporary {
 std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-motion-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 ~Temporary(){std::error_code ec;std::filesystem::remove_all(path,ec);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib,float geometry=1){
 Simulation s(42,1,{},MissionTheme::Mine,false,false,WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(lib));
 s.arena=Arena{};auto &a=s.arena;const float extent=400*geometry;
 a.bounds={{-extent,-1,-extent},{extent,5,extent}};a.rooms.resize(1);a.floors={{{-extent,-.4f,-extent},{extent,0,extent}}};a.boundaryWalls={};
 a.rooms[0].bounds=a.bounds;a.rooms[0].center={0,.85f,0};a.rooms[0].floors=a.floors;a.rebuildWalls();
 s.rooms.assign(1,{});s.room=0;s.debugScenario=true;s.godMode=true;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};
 s.player.position={300*geometry,.85f,0};return s;
}
}
int main(){try{
 Temporary tmp;auto original=defaultMechanics();std::map<std::filesystem::path,std::string> before;
 for(const auto &f:std::filesystem::directory_iterator(original->directory()))if(f.path().extension()==".mechanics")before.emplace(f.path(),read(f.path()));
 auto candidate=movement_review::makePack(*original,tmp.path);
 near(movement_review::WorldScale*movement_review::NativePlayerSteadyStep*60,Player::AcceptedWalkingPace,1e-6,"native held player pace anchors conversion");
 for(const auto &[file,text]:before)check(read(file)==text,"production files unchanged");
 // Only the six controller scale tokens can differ; HP, attacks and every other
 // source force/counter are held byte-for-byte. No hidden HP compensation.
 for(const auto &[file,text]:before){
  const auto changed=read(tmp.path/file.filename());std::istringstream a(text),b(changed);std::string x,y;
  while(std::getline(a,x)){check(bool(std::getline(b,y)),"all source lines retained");if(x==y)continue;
   std::istringstream ax(x),by(y);std::vector<std::string> at,bt;for(std::string t;ax>>t;)at.push_back(t);for(std::string t;by>>t;)bt.push_back(t);
   check(at.size()==bt.size()&&at.size()>4,"only numeric conversion changes");const auto id=parseMonsterId(at[1]);check(movement_review::selected(id),"only selected movement controllers differ");
   const size_t column=(at[0]=="gaper"||at[0]=="headless")?3:2;
   for(size_t n=0;n<at.size();++n)if(n!=column)check(at[n]==bt[n],"source profile fields preserved");
   near(std::stod(bt[column]),movement_review::WorldScale,1e-10,"one common relative movement conversion");
  }check(!std::getline(b,y),"no extra mechanics directives");
 }
 std::cout<<"id,previous_peak,corrected_peak,corrected_final,player_pace\n";
 for(auto id:{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1),monsterId(12),monsterId(14),monsterId(85)}){
  // Keep both players outside authored shooting ranges, so attack friction
  // cannot confound this isolated locomotion similarity witness.
  auto old=fixture(original),now=fixture(candidate,float(movement_review::ConversionRatio));
  auto a=old.spawnMonster(id,{-30,.85f,0});auto b=now.spawnMonster(id,{-30*float(movement_review::ConversionRatio),.85f,0});check(a&&b,"spawn movement actors");
  float previousPeak=0,correctedPeak=0;
  for(int tick=0;tick<120;++tick){old.step({});now.step({});auto *x=old.findEnemy(a),*y=now.findEnemy(b);check(x&&y,"actors survive motion-only fixture");
   previousPeak=std::max(previousPeak,length(horizontal(x->velocity)));correctedPeak=std::max(correctedPeak,length(horizontal(y->velocity)));
   // Similarity check for recurrence, timing, burst/idle transitions and random
   // destinations in open space. This is NOT independent native AI acceptance.
   near(y->position.x,x->position.x*movement_review::ConversionRatio,.003,"scaled trajectory x");
   near(y->position.z,x->position.z*movement_review::ConversionRatio,.003,"scaled trajectory z");
   near(length(horizontal(y->velocity)),length(horizontal(x->velocity))*movement_review::ConversionRatio,.005,"scaled velocity per fixed step");
  }
  auto *e=now.findEnemy(b);const auto speed=length(horizontal(e->velocity));
  if(id==monsterId(10)||id==monsterId(10,1)){
   const double force=id==monsterId(10)?.7200000286102295:.49799999594688416;
   const double expected=force*2/(1-.7)*30*movement_review::WorldScale;
   near(speed,expected,.002,"open Gaper chase rate from pinned native recurrence");check(speed<now.player.walkingSpeed(),"Gaper chase slower than accepted player");
  }
  if(id==monsterId(12))near(correctedPeak,0,0,"Horf stationary");
  std::cout<<monsterIdText(id)<<','<<previousPeak<<','<<correctedPeak<<','<<speed<<','<<now.player.walkingSpeed()<<'\n';
  // Actual controller suppression and restart, with no momentum left over.
  e->state=EnemyState::Stunned;e->stateTime=1;const auto position=e->position;now.step({});
  near(length(horizontal(e->velocity)),0,1e-6,"stun clears motion");near(planarDistance(position,e->position),0,1e-6,"stun holds position");
 }
 std::cout<<"PASS movement-only scope, HP/attack preservation, 840 paired fixed steps, source-derived Gaper ratios and stun stopping\n";
 return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
