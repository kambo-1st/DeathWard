#include "../tools/source_room_reference.hpp"
#include "../tools/enemy_movement_calibration.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
void near(float a,float b,float tolerance,const char *why){if(std::abs(a-b)>tolerance){std::cerr<<a<<" != "<<b<<'\n';check(false,why);}}
std::vector<std::string> fields(std::string row){std::vector<std::string> v;std::istringstream in(row);for(std::string f;std::getline(in,f,',');)v.push_back(f);return v;}
struct Temporary {std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-source-room-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));~Temporary(){std::error_code ec;std::filesystem::remove_all(path,ec);}};
std::unique_ptr<Simulation> fixture(std::shared_ptr<const MechanicsLibrary> library,bool open=false){
 auto s=std::make_unique<Simulation>(42,1,WorldState{},MissionTheme::Mine,false,false,WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(library));
 s->arena=Arena{};source_room_review::configure(s->arena,open);s->enemies.clear();s->projectiles.clear();s->hazards.clear();s->items.clear();s->moneyPickups.clear();s->heartPickups.clear();s->rooms.assign(1,{});s->room=0;s->debugScenario=true;s->godMode=true;s->player.position=source_room_review::Centre;s->stats={};s->nativePlayerMovement.emplace(source_room_review::Scale);s->nativeGaperPursuit=true;return s;
}
}
int main(){try{
 Temporary temporary;auto original=defaultMechanics();auto candidate=movement_review::makePack(*original,temporary.path,source_room_review::Scale);
 near(source_room_review::Scale,FloorTile/40.f,1e-7,"spatial anchor comes from native and floor tile spacing");
 auto run=fixture(candidate);near(run->arena.bounds.max.x-run->arena.bounds.min.x,26,1e-6,"native room width");near(run->arena.bounds.max.z-run->arena.bounds.min.z,14,1e-6,"native room depth");
 std::ifstream grid(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/room-scale-timing/native-grid.csv");check(bool(grid),"independent native grid fixture exists");std::string row;std::getline(grid,row);int interior=0;
 while(std::getline(grid,row)) {auto c=fields(row);const int column=std::stoi(c[1]),z=std::stoi(c[2]);if(column<1||column>13||z<1||z>7)continue;
  Vector2 native{std::stof(c[3]),std::stof(c[4])};const auto p=source_room_review::worldFromNative(native);const auto back=source_room_review::nativeFromWorld(p);
  near(p.x,(column-.5f)*FloorTile,1e-5,"native column maps to floor tile centre");near(p.z,(z-.5f)*FloorTile,1e-5,"native row maps to floor tile centre");near(back.x,native.x,1e-4,"native x roundtrip");near(back.y,native.y,1e-4,"native y roundtrip");
  check(run->arena.contains(p)&&!run->arena.blocked(p,.48f),"all91 native interior centres have navigable floor");++interior;
 }
 check(interior==91&&run->arena.floorCells.size()==91,"all13x7 source interior cells checked");
 // Replay the independently executed native player traces in the real adapter.
 std::ifstream traces(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/native-motion-reference/native-traces.csv");check(bool(traces),"independent native movement trace exists");std::getline(traces,row);std::string name;int states=0;
 while(std::getline(traces,row)){auto c=fields(row);if(c[1]!="player")continue;if(c[0]!=name){name=c[0];run=fixture(candidate,true);}Input input;input.movement={std::stof(c[4]),0,std::stof(c[5])};run->player.attributes.speed=std::stof(c[3]);run->step(input);
  near(run->player.position.x,source_room_review::Centre.x+std::stof(c[7])*source_room_review::Scale,.002,"geometric adapter native x");near(run->player.position.z,source_room_review::Centre.z+std::stof(c[8])*source_room_review::Scale,.002,"geometric adapter native y");++states;
 }
 check(states==1380,"all seven player sequences in geometric coordinates");
 run=fixture(candidate,true);Input input;input.movement={1,0,0};for(int n=0;n<360;++n)run->step(input);const auto playerPace=length(horizontal(run->player.velocity));
 // Compare against the longest REAL live pass, not a selected feel constant.
 std::ifstream live(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/room-scale-timing/live-walking-segments.csv");check(bool(live),"live movement measurement exists");std::getline(live,row);float duration=0,livePace=0;
 while(std::getline(live,row)){auto c=fields(row);const float span=std::stof(c[2])-std::stof(c[1]);if(span>duration){duration=span;livePace=std::abs(std::stof(c[6]))*source_room_review::Scale;}}
 check(duration>1&&livePace>0,"longest live baseline segment usable");check(std::abs(playerPace/livePace-1)<.01f,"geometric baseline agrees with measured native walking within1percent");
 std::cout<<"native_scaled_live_pace="<<livePace<<" actual_steady_player="<<playerPace<<'\n';
 for(auto id:{monsterId(10),monsterId(10,1)}){run=fixture(candidate);run->player.position={23,.85f,7};const auto actor=run->spawnMonster(id,{3,.85f,7});check(actor!=0,"Gaper spawns in native reference room");for(int n=0;n<120;++n)run->step({});const auto *e=run->findEnemy(actor);check(e&&e->alive,"live Gaper remains active");const float nativeStep=id==monsterId(10)?4.80000019f:3.31999997f;near(length(horizontal(e->velocity)),nativeStep*30*source_room_review::Scale,.002,"Gaper realized chase uses same geometric conversion");
  std::cout<<monsterIdText(id)<<" chase/player="<<length(horizontal(e->velocity))/playerPace<<'\n';
 }
 run=fixture(candidate);input={};input.moveTarget=Vector3{21,.85f,7};run->step(input);input.moveTarget.reset();for(int n=0;n<360;++n)run->step(input);
 near(planarDistance(run->player.position,{21,.85f,7}),0,.05f,"native review stops at clicked destination");check(!run->moveDestination(),"completed click route is cleared");const auto stopped=run->player.position;for(int n=0;n<60;++n)run->step({});near(planarDistance(run->player.position,stopped),0,.0001f,"mouse arrival cannot bank native residual velocity");
 for(const auto &body:original->monsters()){near(candidate->monster(body.id)->hp,body.hp,1e-6,"fallbackHP unchanged");for(int stage:{1,4,13})near(candidate->monsterHealth(body.id,stage),original->monsterHealth(body.id,stage),1e-6,"source stageHP unchanged");}
 near(candidate->regularHealthMultiplier(),original->regularHealthMultiplier(),1e-6,"HP control unchanged");
 run=fixture(candidate);run->player.position={5,.85f,7};input={};input.movement={1,0,0};input.dodge=true;run->step(input);near(run->player.velocity.x,20.4f,.002,"absolute universal dodge retained");check(run->player.hp==6&&run->player.shotDamage==24,"real health and production shot damage retained");
 std::cout<<"PASS91 mapped floor cells,1380 native Simulation states, independent live pace, Gaper ratios and unchangedHP/dodge; full NPC trajectories and colliders remain unaccepted\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
