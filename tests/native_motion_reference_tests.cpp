#include "combat/reference/NativeMotion.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
void near(float actual,float expected,const char *why){if(std::abs(actual-expected)>.003f){std::cerr<<actual<<" != "<<expected<<'\n';check(false,why);}}
std::vector<std::string> columns(std::string line){std::istringstream s(line);std::vector<std::string> result;for(std::string field;std::getline(s,field,',');)result.push_back(field);return result;}
}
int main(){try{
 std::ifstream in(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/native-motion-reference/native-traces.csv");check(bool(in),"independently executed native traces exist");
 std::string line,name;std::getline(in,line);native_motion::Body body;int count=0,cases=0;
 float sourceGaperNormal=0,sourceGaperAwake=0,sourcePlayer=0;
 while(std::getline(in,line)){
  auto c=columns(line);check(c.size()==14,"native trace schema");if(c[0]!=name){name=c[0];body={};++cases;}
  const auto input=Vector3{std::stof(c[4]),0,std::stof(c[5])};const float parameter=std::stof(c[3]);
  body.integrate();near(body.velocity.x,std::stof(c[12]),"native realized vx");near(body.velocity.z,std::stof(c[13]),"native realized vy");
  if(c[1]=="player")body.velocity=native_motion::playerSteering(body.velocity,input,parameter);
  else if(c[1]=="gaper")native_motion::gaperSteering(body,input,parameter,c[6]=="blocked"?native_motion::Path::Blocked:native_motion::Path::Moving);
  else if(c[1]=="spider")native_motion::spiderSteering(body,input,c[6]=="target");else check(false,"known actor");
  near(body.position.x,std::stof(c[7]),"native integrated position x");near(body.position.z,std::stof(c[8]),"native integrated position y");
  near(body.velocity.x,std::stof(c[9]),"native outgoing vx");near(body.velocity.z,std::stof(c[10]),"native outgoing vy");near(body.friction,std::stof(c[11]),"native current friction");
  if(c[2]=="119") {if(name=="gaper-normal")sourceGaperNormal=std::stof(c[12]);if(name=="gaper-awake")sourceGaperAwake=std::stof(c[12]);}
  if(name=="player-press-release"&&c[2]=="179")sourcePlayer=std::stof(c[12]);
  ++count;
 }
 check(count==1840&&cases==10,"all independent native reference cases covered");
 check(sourcePlayer>0&&sourceGaperNormal>0&&sourceGaperAwake>0,"measured steady reference velocities");
 std::cout<<"PASS "<<count<<" bounded native position/realized-velocity/outgoing-velocity/friction states across "<<cases<<" sequences\n";
 std::cout<<"native-player-step="<<sourcePlayer<<" native-gaper-normal-realized-step="<<sourceGaperNormal<<" native-gaper-awake-realized-step="<<sourceGaperAwake<<'\n';
 std::cout<<"Full actor reachability, live scheduling, navigation/collision and Spider target timing remain unverified\n";
 return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
