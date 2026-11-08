#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
using namespace dw;
int main(){
 std::cout<<std::unitbuf;
 std::vector<MonsterId> targets={monsterId(854),monsterId(217,1),monsterId(217,2),monsterId(217,3),monsterId(220,1),monsterId(870),monsterId(871),monsterId(57),monsterId(57,1),monsterId(57,2),monsterId(862)};
 std::set<MonsterId> found;bool brain=false;
 std::vector<uint64_t> seeds={9,326,5,2,0,11,1,4,16,22,101};
 for(uint64_t seed=0;seed<256;++seed)if(std::find(seeds.begin(),seeds.end(),seed)==seeds.end())seeds.push_back(seed);
 for(auto seed:seeds){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
  for(int floor=0;floor<plan.floorCount;++floor){
   Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
   for(int room=1;room<s.arena.roomCount();++room){
    const bool river=s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;});
    for(const auto &e:s.roomEnemies(room)){
     if(!brain&&e.monster==monsterId(32)&&river&&s.arena.profile.band==3){std::cout<<"BRAIN_RIVER seed="<<seed<<" floor="<<floor<<" room="<<room<<" band=3 river=1\n";brain=true;}
     if(std::find(targets.begin(),targets.end(),e.monster)!=targets.end()&&!found.count(e.monster)&&!(e.monster==monsterId(854)&&s.arena.profile.band!=3)){
      found.insert(e.monster);std::cout<<"FOUND id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<" river="<<river<<'\n';
     }
    }
   }
   if(found.size()==targets.size()&&brain){std::cout<<"COMPLETE targets="<<found.size()<<" plusBrainRiver\n";return 0;}
  }
 }
 return 1;
}
