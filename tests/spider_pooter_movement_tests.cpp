#include "../tools/source_room_reference.hpp"
#include "../tools/enemy_movement_calibration.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::vector<std::string> columns(const std::string &row){std::istringstream in(row);std::vector<std::string> result;for(std::string value;std::getline(in,value,',');)result.push_back(value);return result;}
struct Temporary {std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-burst-wander-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));~Temporary(){std::error_code ec;std::filesystem::remove_all(path,ec);}};
std::unique_ptr<Simulation> fixture(std::shared_ptr<const MechanicsLibrary> library,bool candidate) {
 auto s=std::make_unique<Simulation>(42,1,WorldState{},MissionTheme::Mine,false,false,WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(library));s->arena=Arena{};source_room_review::configure(s->arena,true);
 s->enemies.clear();s->projectiles.clear();s->hazards.clear();s->items.clear();s->moneyPickups.clear();s->heartPickups.clear();s->rooms.assign(1,{});s->room=0;s->debugScenario=true;s->godMode=true;s->nativeBurstWanderReview=candidate;s->combatRng=Random(123456);return s;
}
Vector3 point(float x,float y){return source_room_review::worldFromNative({x,y});}
}
int main(int argc,char **argv){try {
 bool candidate=true;int substeps=2;for(int i=1;i<argc;++i){const std::string arg=argv[i];if(arg=="--legacy")candidate=false;else if(arg=="--substeps"&&i+1<argc)substeps=std::stoi(argv[++i]);else check(false,"unknown motion comparison option");}check(substeps>=1&&substeps<=4,"supported motion substeps");Temporary temporary;auto library=movement_review::makePack(*defaultMechanics(),temporary.path,source_room_review::Scale);
 const auto root=std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/spider-pooter-movement/";
 std::ifstream gates(root+"spider-gates.csv");check(bool(gates),"native Spider gates exist");std::string row;std::getline(gates,row);int gateCount=0;
 while(std::getline(gates,row)) {
  const auto c=columns(row);auto s=fixture(library,candidate);s->player.position=point(380,280);auto actor=s->spawnMonster(monsterId(85),point(320,280));check(actor!=0,"Spider gate actor spawns");auto *e=s->findEnemy(actor);e->friendly=true;e->spider.emplace();e->spider->initialized=true;e->spider->counter=std::stoi(c[0]);s->step({},1.f/30);e=s->findEnemy(actor);
  if(e->spider->targetReady!=(std::stoi(c[2])!=0)||e->spider->counter!=std::stoi(c[1]))throw std::runtime_error("Spider gate old="+c[0]+" expected="+c[1]+","+c[2]+" actual="+std::to_string(e->spider->counter)+","+std::to_string(e->spider->targetReady)+" initialized="+std::to_string(e->spider->initialized)+" clock="+std::to_string(e->spider->clock)+" state="+std::to_string(int(e->state))+" age="+std::to_string(e->age)+" duration="+std::to_string(s->stats.duration)+" finished="+std::to_string(s->finished));++gateCount;
 }
 std::ifstream spiders(root+"spider-native.csv");check(bool(spiders),"native Spider states exist");std::getline(spiders,row);std::unique_ptr<Simulation> run;std::string name;EntityId actor=0;int spiderCount=0;float spiderError=0,pooterError=0,pooterWanderError=0;bool matched=true;
 while(std::getline(spiders,row)) {
  const auto c=columns(row);
  if(name!=c[0]){name=c[0];run=fixture(library,candidate);run->player.position=point(1000,280);actor=run->spawnMonster(monsterId(85),point(320,280));check(actor!=0,"Spider motion actor spawns");auto *e=run->findEnemy(actor);e->friendly=true;e->spider.emplace();e->spider->initialized=true;e->spider->counter=std::stoi(c[3]);e->velocity={std::stof(c[2])*1.5f,0,0};if(name!="idle"){e->spider->targetReady=e->spider->pursuing=true;e->spider->destination=point(name=="burst-arrival"?330:500,280);}}
  for(int n=0;n<substeps;++n)run->step({},1.f/(30*substeps));const auto *e=run->findEnemy(actor);const float error=planarDistance(e->position,point(std::stof(c[6]),std::stof(c[7])));spiderError=std::max(spiderError,error);
  matched&=error<.002f&&length(sub(e->velocity,{std::stof(c[8])*1.5f,0,std::stof(c[9])*1.5f}))<.005f&&e->spider->targetReady==(std::stoi(c[4])!=0)&&e->spider->counter==std::stoi(c[5]);++spiderCount;
 }
 std::ifstream pooters(root+"pooter-native.csv");check(bool(pooters),"native Pooter states exist");std::getline(pooters,row);name.clear();int pooterCount=0;
 while(std::getline(pooters,row)) {
  const auto c=columns(row);
  if(name!=c[0]){name=c[0];run=fixture(library,candidate);run->player.position=point(1000,280);actor=run->spawnMonster(monsterId(14),point(std::stof(c[2]),std::stof(c[3])));check(actor!=0,"Pooter actor spawns");auto *e=run->findEnemy(actor);e->friendly=true;e->buzz.emplace();e->buzz->initialized=true;e->buzz->tick=0;e->buzz->wander={.2f,0,.1f};e->velocity={name=="right"?-6.f:3.f,0,name=="bottom"?-3.f:1.5f};e->cooldown=std::stof(c[4])/30;run->combatRng=Random(123456);}
  for(int n=0;n<substeps;++n)run->step({},1.f/(30*substeps));const auto *e=run->findEnemy(actor);const float error=planarDistance(e->position,point(std::stof(c[7]),std::stof(c[8])));const float wanderError=length(sub(e->buzz->wander,{std::stof(c[11]),0,std::stof(c[12])}));pooterError=std::max(pooterError,error);pooterWanderError=std::max(pooterWanderError,wanderError);
  check(run->combatRng.state==std::stoull(c[6]),"supplied DW random stream stays isolated and consumes identical draws");check(run->projectiles.empty(),"wandering fixture excludes attacks");
  matched&=error<.002f&&wanderError<.0001f&&length(sub(e->velocity,{std::stof(c[9])*1.5f,0,std::stof(c[10])*1.5f}))<.005f;++pooterCount;
 }
 std::cout<<"physics_hz="<<30*substeps<<'\n';
 std::cout<<"spider gates="<<gateCount<<" states="<<spiderCount<<" max_position_error="<<spiderError<<'\n';
 std::cout<<"pooter states="<<pooterCount<<" max_position_error="<<pooterError<<" max_wander_error="<<pooterWanderError<<'\n';
 check(gateCount==16&&spiderCount==48&&pooterCount==144,"all native bounded cases compared");check(matched,"native Spider/Pooter bounded motion comparison");
 std::cout<<"PASS bounded Spider burst/idle and Pooter wandering; source RNG/acquisition/collision/live scheduling remain open\n";
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
