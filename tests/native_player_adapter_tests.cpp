#include "combat/Simulation.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
void near(float a,float b,float tolerance,const char *why){if(std::abs(a-b)>tolerance){std::cerr<<a<<" != "<<b<<'\n';check(false,why);}}
std::vector<std::string> columns(std::string line){std::istringstream s(line);std::vector<std::string> r;for(std::string f;std::getline(s,f,',');)r.push_back(f);return r;}
std::unique_ptr<Simulation> fixture(float scale){
 auto s=std::make_unique<Simulation>(42,1,WorldState{},MissionTheme::Mine);auto &run=*s;
 run.arena=Arena{};auto &a=run.arena;a.bounds={{-10000,-1,-10000},{10000,5,10000}};a.rooms.resize(1);a.floors={{{-10000,-.4f,-10000},{10000,0,10000}}};a.boundaryWalls={};
 a.rooms[0].bounds=a.bounds;a.rooms[0].center={0,.85f,0};a.rooms[0].floors=a.floors;a.rebuildWalls();
 run.rooms.assign(1,{});run.room=0;run.debugScenario=true;run.godMode=true;run.enemies.clear();run.hazards.clear();run.projectiles.clear();run.items.clear();run.heartPickups.clear();run.moneyPickups.clear();run.player.position={0,.85f,0};
 run.nativePlayerMovement.emplace(scale);return s;
}
}
int main(){try{
 int rows=0,cases=0;
 // Two explicit coordinate transforms verify that no accepted walking-speed
 // value is hidden inside the native recurrence. Neither is geometry acceptance.
 for(float scale:{.018123172f,.05f}){
  std::ifstream in(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/native-motion-reference/native-traces.csv");check(bool(in),"independent native trace available");
  std::string name,line;std::getline(in,line);std::unique_ptr<Simulation> run;
  while(std::getline(in,line)){
   const auto c=columns(line);if(c[1]!="player")continue;
   if(name!=c[0]){name=c[0];run=fixture(scale);++cases;}
   Input input;input.movement={std::stof(c[4]),0,std::stof(c[5])};run->player.attributes.speed=std::stof(c[3]);run->step(input);
   near(run->player.position.x,std::stof(c[7])*scale,.002,"actual Simulation native position x");near(run->player.position.z,std::stof(c[8])*scale,.002,"actual Simulation native position y");
   near(run->player.velocity.x,std::stof(c[12])*scale*60,.002,"actual realized world velocity x");near(run->player.velocity.z,std::stof(c[13])*scale*60,.002,"actual realized world velocity y");
   near(run->nativePlayerMovement->body.velocity.x,std::stof(c[9]),.002,"actual next-invocation native velocity x");near(run->nativePlayerMovement->body.velocity.z,std::stof(c[10]),.002,"actual next-invocation native velocity y");++rows;
  }
 }
 check(rows==2760&&cases==14,"all seven native player cases at both spatial transforms");
 auto run=fixture(.02f);run->godMode=false;Input input;input.movement={1,0,0};input.dodge=true;run->step(input);
 near(run->player.velocity.x,20.4f,.002,"native review retains absolute dodge boost");check(run->player.dodge>0&&run->player.hp==6,"native review keeps real health/dodge");
 input.dodge=false;while(run->player.dodge>0)run->step(input);
 const auto end=run->player.position;input.movement={};run->step(input);near(planarDistance(end,run->player.position),0,.0001,"no native residual momentum banked during dodge");
 Simulation normal(42,1,{},MissionTheme::Mine);check(!normal.nativePlayerMovement,"normal expedition does not enable reference movement");
 std::cout<<"PASS "<<rows<<" actual Simulation states at two explicit spatial transforms, "<<cases<<" sequences; ordinary default unchanged and dodge retained\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
