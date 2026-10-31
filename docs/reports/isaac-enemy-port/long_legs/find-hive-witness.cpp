#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main() {
 for(uint64_t seed=100;seed<1000;++seed) {
  ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
  int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))
   if(e.monster==monsterId(22,1)) {
    std::cout<<"WITNESS id=22.1.0 seed="<<seed<<" floor="<<floor<<" room="<<room
             <<" flooded="<<(s.arena.profile.variant==FloorVariant::Flooded)<<std::endl;
    return 0;
   }
 }
 return 1;
}
