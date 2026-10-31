#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){std::cout<<std::unitbuf;std::set<MonsterId> wanted{monsterId(217,1),monsterId(217,2),monsterId(217,3),monsterId(220,1),monsterId(870),monsterId(871),monsterId(217),monsterId(220),monsterId(223),monsterId(57),monsterId(57,1),monsterId(57,2),monsterId(862),monsterId(854)};
for(uint64_t seed=0;seed<100&&!wanted.empty();++seed){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
 for(int floor=0;floor<plan.floorCount&&!wanted.empty();++floor){
 Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
 for(int room=1;room<int(s.arena.roomCount());++room)for(const auto &e:s.roomEnemies(room))if(wanted.contains(e.monster)){
 std::cout<<e.monster.type<<'.'<<e.monster.variant<<".0 seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';wanted.erase(e.monster);}
 }}return wanted.empty()?0:1;}
