#include "../tools/source_room_reference.hpp"
#include "combat/reference/NativeGridPath.hpp"
#include "../tools/enemy_movement_calibration.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::vector<std::string> columns(std::string row){std::istringstream in(row);std::vector<std::string> r;for(std::string f;std::getline(in,f,',');)r.push_back(f);return r;}
struct Temporary{std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-gaper-trajectory-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));~Temporary(){std::error_code ec;std::filesystem::remove_all(path,ec);}};
std::unique_ptr<Simulation> fixture(std::shared_ptr<const MechanicsLibrary> library,bool blocked,bool legacy) {
 auto s=std::make_unique<Simulation>(42,1,WorldState{},MissionTheme::Mine,false,false,WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(library));s->arena=Arena{};source_room_review::configure(s->arena,true);
 if(blocked){s->arena.obstacles={{{18,0,-100},{19,3,100}}};s->arena.rebuildWalls();}
 s->enemies.clear();s->projectiles.clear();s->hazards.clear();s->items.clear();s->moneyPickups.clear();s->heartPickups.clear();s->rooms.assign(1,{});s->room=0;s->debugScenario=true;s->godMode=true;s->stats={};s->nativeGaperPursuit=!legacy;return s;
}

void frowningPhases(std::shared_ptr<const MechanicsLibrary> library) {
 std::ifstream input(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/frowning-phase-review/native-phases.csv");
 check(bool(input),"native Frowning phase evidence exists");std::string row,name;std::getline(input,row);std::unique_ptr<Simulation> run;EntityId actor=0;int cases=0,states=0;
 while(std::getline(input,row)) {
  const auto c=columns(row);check(c.size()==9,"native Frowning phase schema");
  if(name!=c[0]) {
   name=c[0];++cases;run=fixture(library,false,false);run->player.position=source_room_review::worldFromNative({560,280});
   actor=run->spawnMonster(monsterId(10,0),source_room_review::worldFromNative({320,280}));check(actor!=0,"phase actor spawns");run->findEnemy(actor)->friendly=true;
   if(std::stof(c[3])==.5f)check(run->applyEnemyStatus(actor,EnemyStatus::Slow,10000),"fixture supplies existing.5 entity timeScale through Slow adapter");
  }
  auto *e=run->findEnemy(actor);check(std::abs(e->gaper->headFrame+e->gaper->headFraction-std::stof(c[4]))<1e-6f,"head state before AI matches native");
  if(std::stoi(c[2]))run->arena.obstacles.clear();else run->arena.obstacles={{{18,0,-100},{19,3,100}}};run->arena.rebuildWalls();
  run->step({},1.f/30);e=run->findEnemy(actor);check(e&&e->alive,"phase actor remains alive");
  const float frame=e->gaper->headFrame+e->gaper->headFraction;
  check(e->gaper->directPath==(std::stoi(c[2])!=0),"physical fixture provides requested native direct flag");
  if(std::abs(frame-std::stof(c[7]))>=1e-6f||std::abs(e->gaper->force-std::stof(c[5]))>=1e-6f||e->gaper->headPlaying!=(std::stoi(c[8])!=0))throw std::runtime_error("native post-base activation mismatch: "+row);
  check(e->awakened==(e->gaper->headFrame>0)&&std::abs(e->gaper->eyeOpenness-float(e->gaper->headFrame)/19)<1e-6f,"private presentation consumes post-base integer frame");++states;
 }
 check(cases==6&&states==288,"all six native activation cases compared");
 std::cout<<"private_frowning_phases cases="<<cases<<" post_base_states="<<states<<" force_frame_fraction_playing_match=1 native_Slow_acceptance=0\n";
}

void referenceGridLines() {
 const std::string root=std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/gaper-grid-lines/";
 std::ifstream masks(root+"native-masks.csv"),lines(root+"native-lines.csv");check(bool(masks)&&bool(lines),"native mask and line evidence exists");
 std::string row;int maskCount=0,lineCount=0;std::getline(masks,row);
 while(std::getline(masks,row)){const auto c=columns(row);check(c.size()==3,"mask schema");check(native_grid::collisionClass(std::stoi(c[0]),std::stoi(c[1]))==std::stoi(c[2]),"native collision classification matches");++maskCount;}
 std::getline(lines,row);
 while(std::getline(lines,row)) {
  const auto c=columns(row);check(c.size()==7,"line schema");std::vector<int> costs(135,1000);
  for(int z=1;z<=7;++z)for(int x=1;x<=13;++x)costs[z*15+x]=0;
  for(int z=1;z<=7;++z)if(c[0]=="sealed"||(c[0]=="central-cover"&&z>=2&&z<=6)||(c[0]=="upper-gap"&&z>=2)||(c[0]=="lower-gap"&&z<=6))costs[z*15+7]=1000;
  if(c[0].starts_with("cost"))costs[4*15+7]=std::stoi(c[0].substr(4));
  const bool result=native_grid::clearLine(costs,15,9,std::stof(c[2]),std::stof(c[3]),std::stof(c[4]),std::stof(c[5]),std::stoi(c[1]));
  if(result!=(std::stoi(c[6])!=0))throw std::runtime_error("native line mismatch: "+row);++lineCount;
 }
 check(maskCount==55&&lineCount==288,"all native mask/line cases compared");
 std::cout<<"native_grid_lines masks="<<maskCount<<" lines="<<lineCount<<" exact_result_match=1\n";
}

void referenceGridRouting() {
 std::ifstream input(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/gaper-scheduler-routing/native-routes.csv");
 check(bool(input),"original native obstructed grid fixture exists");std::string row;std::getline(input,row);int decisions=0;
 while(std::getline(input,row)) {
  const auto c=columns(row);check(c.size()==9,"native grid decision schema");
  std::vector<int> costs(135,1000);
  for(int z=1;z<=7;++z)for(int x=1;x<=13;++x)costs[z*15+x]=0;
  for(int z=1;z<=7;++z) {
   const bool blocked=c[0]=="sealed"||(c[0]=="central-cover"&&z>=2&&z<=6)||
                      (c[0]=="upper-gap"&&z>=2)||(c[0]=="lower-gap"&&z<=6);
   if(blocked)costs[z*15+7]=1000;
  }
  const auto actual=native_grid::gaperWaypoint(costs,15,9,std::stoi(c[2]),std::stoi(c[3]));
  check(actual.found==(std::stoi(c[4])!=0)&&actual.index==std::stoi(c[5]),"reference port matches original native found flag and exact waypoint");++decisions;
 }
 check(decisions==64,"all native grid decisions compared");
 std::cout<<"native_grid_reference decisions="<<decisions<<" exact_waypoint_match=1 production_enabled=0\n";
}

void reviewGridIntegration(std::shared_ptr<const MechanicsLibrary> library) {
 std::ifstream input(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/gaper-scheduler-routing/native-routes.csv");
 check(bool(input),"native route integration evidence exists");std::string row;std::getline(input,row);int decisions=0,direct=0,grid=0;
 while(std::getline(input,row)) {
  const auto c=columns(row);auto run=fixture(library,false,false);source_room_review::configure(run->arena);
  if(c[0]=="central-cover")run->arena.obstacles={{{12,0,2},{14,3,12}}};
  else if(c[0]=="sealed")run->arena.obstacles={{{12,0,0},{14,3,14}}};
  else if(c[0]=="upper-gap")run->arena.obstacles={{{12,0,2},{14,3,14}}};
  else if(c[0]=="lower-gap")run->arena.obstacles={{{12,0,0},{14,3,12}}};
  run->arena.rebuildWalls();
  auto worldCell=[](int i){return Vector3{float(2*(i%15)-1),.85f,float(2*(i/15)-1)};};
  run->player.position=worldCell(std::stoi(c[3]));const auto actor=run->spawnMonster(monsterId(10,0),worldCell(std::stoi(c[2])));
  check(actor!=0,"review grid actor spawns");run->findEnemy(actor)->friendly=true;run->step({},1.f/60);
  const auto *e=run->findEnemy(actor);
  if(std::stoi(c[4])==0)check(e->path.empty()&&!e->gaper->directPath,"native sealed route remains absent in private runtime");
  else {
   check(e->path.size()==1,"private review consumes one native grid or direct waypoint");
   if(e->gaper->directPath){check(planarDistance(e->path.front(),run->player.position)<.001f,"clear native/physical route uses live target");++direct;}
   else {check(planarDistance(e->path.front(),worldCell(std::stoi(c[5])))<.001f,"blocked private route matches original native adjacent waypoint");++grid;}
  }
  ++decisions;
 }
 check(decisions==64&&grid>0&&direct>0,"private runtime integration covers all64 decisions and both route branches");
 std::cout<<"private_grid_integration decisions="<<decisions<<" direct="<<direct<<" adjacent_grid="<<grid<<" production_enabled=0\n";
}

void physicalRouting(std::shared_ptr<const MechanicsLibrary> library) {
 // DeathWard navigation acceptance only: these are not native path traces.
 for(int variant:{0,1})for(int scenario=0;scenario<3;++scenario) {
  auto run=fixture(library,false,false);source_room_review::configure(run->arena);
  run->player.position={22,.85f,7};
  const Box cover=scenario==0?Box{{12,0,3},{14,3,11}}:
                                         Box{{12,0,-10},{14,3,24}};
  run->arena.obstacles={cover};run->arena.rebuildWalls();
  const auto actor=run->spawnMonster(monsterId(10,variant),{4,.85f,7});
  check(actor!=0,"physical routing actor spawns");run->findEnemy(actor)->friendly=true;
  for(int k=0;k<900;++k) {
   if(scenario==2&&k==120){run->arena.obstacles.clear();run->arena.rebuildWalls();}
   run->step({},1.f/60);const auto *e=run->findEnemy(actor);
   check(e&&e->alive,"physical routing actor survives");
   check(!run->arena.blocked(e->position,e->radius),"grounded footprint never enters cover or leaves floor");
   if(scenario==1) {
    check(e->position.x<12-e->radius+.001f,"sealed barrier is never crossed");
    if(variant==0)check(!e->awakened,"sealed cover never creates a direct wake path");
   }
   if(scenario==2&&k==122)check(e->gaper->directPath,"removing cover refreshes direct route promptly");
  }
  const auto *e=run->findEnemy(actor);
  if(scenario!=1) {
   check(planarDistance(e->position,run->player.position)<1.2f,"finite cover is rounded or removed and target reached");
   if(variant==0)check(e->awakened&&e->gaper->headFrame==19,"physical clear route eventually completes awakening");
  }
  std::cout<<"physical_navigation variant="<<variant<<" scenario="<<scenario
           <<" target_distance="<<planarDistance(e->position,run->player.position)<<'\n';
 }
}
}
int main(int argc,char **argv){try{
 bool legacy=false;int substeps=1;for(int n=1;n<argc;++n){const std::string arg=argv[n];if(arg=="--legacy")legacy=true;else if(arg=="--substeps"&&n+1<argc)substeps=std::stoi(argv[++n]);else check(false,"unknown trajectory option");}check(substeps>=1&&substeps<=4,"supported trajectory substeps");
 Temporary temporary;auto original=defaultMechanics();auto library=movement_review::makePack(*original,temporary.path,source_room_review::Scale);
 std::ifstream input(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/gaper-trajectories/native-trajectories.csv");check(bool(input),"original native trajectory fixture exists");std::string row,name;std::getline(input,row);
 std::unique_ptr<Simulation> run;EntityId actor=0;int cases=0,samples=0;float maxPosition=0,maxVelocity=0;bool matched=true;
 // The game uses the strict60Hz comparison. Smaller physics partitions are
 // a numerical stress check: changing world-space float accumulation can flip
 // the branch at exactly one native coordinate of arrival. Bound that stress
 // drift to a quarter native pixel; do not call it strict native equivalence.
 const float positionBound=substeps==1?.002f:source_room_review::Scale*.25f;
 const float velocityBound=substeps==1?.005f:source_room_review::Scale*.25f*30;
 auto finish=[&]{if(name.empty())return;std::cout<<name<<",max_position_error="<<maxPosition<<",max_interval_velocity_error="<<maxVelocity<<'\n';matched&=maxPosition<positionBound&&maxVelocity<velocityBound;};
 while(std::getline(input,row)){
  auto c=columns(row);check(c.size()==18,"native trajectory schema");const auto target=source_room_review::worldFromNative({std::stof(c[5]),std::stof(c[6])});const auto expected=source_room_review::worldFromNative({std::stof(c[9]),std::stof(c[10])});
  if(name!=c[0]){
   finish();name=c[0];++cases;maxPosition=maxVelocity=0;run=fixture(library,c[7]=="blocked",legacy);run->player.position=target;actor=run->spawnMonster(monsterId(10,std::stoi(c[1])),expected);check(actor!=0,"Gaper trajectory actor spawns");auto *e=run->findEnemy(actor);
   // Isolate supplied-waypoint motion from player-contact separation. Friendly
   // without Charm keeps the ordinary player target but skips body displacement.
   e->friendly=true;e->velocity={std::stof(c[16])*30*source_room_review::Scale,0,std::stof(c[17])*30*source_room_review::Scale};
   if(name=="frowning-awake-turn"){e->gaper->initialized=true;e->gaper->wakeStarted=true;e->gaper->headPlaying=true;e->gaper->headFrame=1;e->awakened=true;}
   check(c[2]=="0","first main phase is initial condition at time0");continue;
  }
  run->player.position=target;for(int n=0;n<substeps;++n)run->step({},1.f/(60*substeps));const auto *e=run->findEnemy(actor);check(e&&e->alive,"trajectory actor remains alive");check(planarDistance(e->target,target)<.001f,"friendly diagnostic retains ordinary supplied target without Charm");maxPosition=std::max(maxPosition,planarDistance(e->position,expected));
  const Vector3 expectedVelocity{std::stof(c[14])*30*source_room_review::Scale,0,std::stof(c[15])*30*source_room_review::Scale};maxVelocity=std::max(maxVelocity,length(horizontal(sub(e->velocity,expectedVelocity))));++samples;
 }
 finish();check(cases==10&&samples==1620,"all ten cases and1620 half-step transitions covered");check(matched,"actual Gaper trajectories must match original main/interpolation reference");
 std::cout<<"substeps="<<substeps<<" position_bound="<<positionBound<<" interval_velocity_bound="<<velocityBound<<" comparison="<<(substeps==1?"strict native60Hz":"quarter-native-pixel numerical stress")<<'\n';
 if(!legacy){frowningPhases(library);referenceGridLines();referenceGridRouting();reviewGridIntegration(library);physicalRouting(library);}
 std::cout<<"PASS actual Gaper open-route trajectories: ten cases,1620 half steps; native navigation, collisions and full overlay/status behavior remain unaccepted\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
