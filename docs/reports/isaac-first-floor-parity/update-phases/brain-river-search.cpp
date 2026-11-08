#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
bool possible(uint64_t floorSeed,int count,const FloorProfile &p,const MechanicsLibrary &content){
 const auto &pool=content.encounterPool(p.band,EncounterPattern::Pursuit).specialists;
 for(int room=1;room<=count+2;++room){
  Random rng(floorSeed^0x464c4f4f52475250ULL^(uint64_t(room+1)*0x9e3779b97f4a7c15ULL));
  int total=0;for(int w:p.patterns)total+=w;
  if(int(rng.bounded(uint32_t(total)))>=p.patterns[0])continue;
  for(int budget=4;budget<=p.maxThreat;++budget)for(int slots=2;slots<=12;++slots){
   auto eligible=[&](const auto &e){return e.weight>0&&e.cost+content.replacementCost(e.monster,p)<=budget-2&&e.members<=slots&&(!e.variant||*e.variant==p.variant)&&(!e.maximum||e.members<=e.maximum);};
   int weight=0;for(const auto &e:pool)if(eligible(e))weight+=e.weight;
   if(!weight)continue;
   auto draw=rng;int choice=int(draw.bounded(uint32_t(weight)));
   for(const auto &e:pool)if(eligible(e)){choice-=e.weight;if(choice<0){if(e.monster==monsterId(32))return true;break;}}
  }
 }
 return false;
}
int main(){std::cout<<std::unitbuf;auto content=defaultMechanics();int candidates=0;
 for(uint64_t seed=526;seed<20000;++seed){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
  for(int floor=0;floor<plan.floorCount;++floor){
   auto p=plan.profileOnFloor(floor);if(p.band!=3)continue;
   auto floorSeed=plan.floorSeed(floor);Random river(floorSeed^0x5249564552545950ULL);if(river.bounded(2))continue;
   p=content->configureFloor(p,floorSeed);
   if(!possible(floorSeed,plan.roomsOnFloor(floor),p,*content))continue;
   Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++candidates;
   if(!s.arena.canyon||s.arena.canyon->riverKind!=CanyonRiverKind::Interior)continue;
   for(int room=1;room<s.finalRoom();++room){bool brain=false;for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(32))brain=true;if(!brain)continue;
    bool water=std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;});
    std::cout<<"NATURAL_BRAIN seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<" river="<<water<<'\n';
    if(water){std::cout<<"COMPLETE candidates="<<candidates<<'\n';return 0;}
   }
  }
  if(seed%100==0)std::cout<<"PROGRESS seed="<<seed<<" candidates="<<candidates<<'\n';
 }
 return 1;}
