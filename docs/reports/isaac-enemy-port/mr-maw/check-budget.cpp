#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){for(int seed=0;seed<8;++seed){ExpeditionPlan p(seed,false,WitnessAccount::Rourke);
 for(int floor=0;floor<p.floorCount;++floor){if(p.profileOnFloor(floor).band!=1)continue;
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);int max=0,pursuit=0;
  for(int room=1;room<s.finalRoom();++room){const auto e=s.floorEncounter(room);max=std::max(max,e.budget);if(e.pattern==EncounterPattern::Pursuit)pursuit=std::max(pursuit,e.budget);}
  std::cout<<"seed="<<seed<<" floor="<<floor<<" max_budget="<<max<<" pursuit_budget="<<pursuit<<'\n';
 }}}
