#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
using namespace dw;
int main(){std::set<MonsterId> found;
 for(uint64_t seed=0;seed<1024 && (!found.contains(monsterId(16)) || !found.contains(monsterId(16,1)));++seed){
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
  for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==16&&found.insert(e.monster).second)
   std::cout<<"WITNESS id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor=0 room="<<room<<std::endl;
 }
 return found.contains(monsterId(16))&&found.contains(monsterId(16,1))?0:1;
}
