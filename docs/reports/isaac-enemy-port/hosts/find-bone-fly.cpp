#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){for(uint64_t seed=80;seed<1000;++seed){ExpeditionPlan plan(seed);for(int floor=0;floor<plan.floorCount;++floor){auto p=plan.profileOnFloor(floor);if(p.band!=1||p.variant!=FloorVariant::Standard)continue;Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);for(int room=0;room<s.arena.roomCount();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(25,4)){std::cout<<"BONE_WITNESS seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';return 0;}}}return 1;}
