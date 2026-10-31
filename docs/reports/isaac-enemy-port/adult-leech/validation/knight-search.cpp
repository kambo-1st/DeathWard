#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
using namespace dw;
int main(){std::cout<<std::unitbuf;std::set<MonsterId> wanted{monsterId(41),monsterId(41,1),monsterId(41,2),monsterId(41,4),monsterId(840)};for(uint64_t seed=0;seed<100&&!wanted.empty();++seed){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);for(int floor=0;floor<plan.floorCount&&!wanted.empty();++floor){if(plan.profileOnFloor(floor).band<1)continue;Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);for(int room=1;room<s.finalRoom();++room)for(const auto&e:s.roomEnemies(room))if(wanted.contains(e.monster)){std::cout<<"FOUND "<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';wanted.erase(e.monster);}}}return !wanted.empty();}
