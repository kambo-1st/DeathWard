#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main() {
 bool goon=false,boom=false;
 for(uint64_t seed=0;seed<1024&&!goon;++seed) {
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))
   if(e.monster==monsterId(16,1)) {
    std::cout<<"WITNESS id=16.1.0 seed="<<seed<<" floor=0 room="<<room<<std::endl;goon=true;
   }
 }
 for(uint64_t seed=128;seed<4096&&!boom;++seed) {
  ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
  int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
  const auto profile=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
  if(profile.variant!=FloorVariant::Standard)continue;
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))
   if(e.monster==monsterId(16,2)) {
    std::cout<<"WITNESS id=16.2.0 seed="<<seed<<" floor="<<floor<<" room="<<room<<std::endl;boom=true;
   }
 }
 return goon&&boom?0:1;
}
