#include "combat/Simulation.hpp"
#include "world/CanyonTerrain.hpp"
#include <iostream>
using namespace dw;
int main(){std::cout<<std::unitbuf;for(uint64_t seed=51;seed<250;++seed){ExpeditionPlan p(seed,false,WitnessAccount::Rourke);for(int floor=0;floor<p.floorCount;++floor){if(p.profileOnFloor(floor).band!=3)continue;Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);if(!s.arena.canyon||s.arena.canyon->riverKind!=CanyonRiverKind::Interior)continue;for(int room=1;room<s.finalRoom();++room){bool brain=false;for(const auto&e:s.roomEnemies(room))brain|=e.monster==monsterId(32);if(!brain)continue;bool river=std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto&v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;});if(river){std::cout<<"FOUND seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';return 0;}}}}return 1;}
