// Pool expansion changes seeded selection. Discover replacement witnesses;
// never inject an enemy into a test that claims natural reachability.
#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
using namespace dw;
int main(){std::cout<<std::unitbuf;std::set<int> seen;bool wet=false;
 for(int seed=0;seed<256;++seed){std::cerr<<"SEARCH seed="<<seed<<'\n';ExpeditionPlan p(seed,false,WitnessAccount::Rourke);
  for(int floor=0;floor<p.floorCount;++floor){int band=p.profileOnFloor(floor).band;if(band<2)continue;
   Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
   for(int room=1;room<s.finalRoom();++room){
    if(!std::any_of(s.roomEnemies(room).begin(),s.roomEnemies(room).end(),[](const auto &e){return e.monster==monsterId(32);}))continue;
    bool river=s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&
      std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;});
    if(!seen.contains(band)||(river&&!wet))std::cout<<"{\"seed\":"<<seed<<",\"floor\":"<<floor<<",\"room\":"<<room<<",\"band\":"<<band<<",\"river\":"<<(river?"true":"false")<<"}\n";
    seen.insert(band);wet=wet||river;if(seen.size()==2&&wet)return 0;
   }
  }
 }return 1;
}
