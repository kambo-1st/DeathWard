#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){for(uint64_t seed=0;seed<512;++seed){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
 Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
 for(int room=0;room<run.arena.roomCount();++room)for(const auto&e:run.roomEnemies(room))if(e.monster==monsterId(15,2)){
  std::cout<<"IBLOB seed="<<seed<<" floor="<<floor<<" room="<<room<<" variant="<<int(run.arena.profile.variant)<<'\n';return 0;}
 }return 1;}
