#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main() {
 for(auto [seed,floor]:std::vector<std::pair<int,int>>{{10,2},{953,2},{57,2},{58,3},{924,2},{749,2}}) {
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  const auto center=s.roomEnemies(s.finalRoom()).front().position;
  s.jumpDebug(s.finalRoom());s.godMode=true;s.debugScenario=true;
  for(int n=0;n<24;++n) {
   auto point=add(center,rotateY({0,0,7},float(n)*Pi/12));point.y=.85f;
   if(s.arena.roomAt(point)!=s.room||s.arena.blocked(point,.48f)||!s.arena.sight(point,center))continue;
   if(std::any_of(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return distance(point,e.position)<3;}))continue;
   s.player.position=point;break;
  }
  auto &h=*s.rooms.back().hornfel;int state=-1,spawned=0,removed=0,shots=0,bursts=0,destroyed=0,escorts=0,released=0;
  for(int f=1;f<=6000;++f) {
   s.step({});
   if(int(h.state)!=state||h.decoysSpawned!=spawned||h.decoysRemoved!=removed||h.recoveryShots!=shots||int(s.fireWaves.size())!=bursts||h.decoysDestroyed!=destroyed||h.escortsSpawned!=escorts||h.escortsReleased!=released) {
    state=int(h.state);spawned=h.decoysSpawned;removed=h.decoysRemoved;shots=h.recoveryShots;bursts=int(s.fireWaves.size());destroyed=h.decoysDestroyed;escorts=h.escortsSpawned;released=h.escortsReleased;
    std::cout<<"seed="<<seed<<" floor="<<floor<<" frame="<<f<<" state="<<state<<" charge="<<h.charges<<" passes="<<h.chargePasses<<" repeats="<<h.repeatsChosen<<" shots="<<shots<<" fire="<<bursts<<" decoys="<<spawned<<" destroyed="<<destroyed<<" removed="<<removed<<" escorts="<<escorts<<" released="<<released<<'\n';
    for(const auto &e:s.enemies)if(e.monster.type==819)std::cout<<" FLY id="<<e.id<<" hp="<<e.hp<<" parent="<<(e.flyFollow?e.flyFollow->parent:0)<<" x="<<e.position.x<<" z="<<e.position.z<<'\n';
   }
  }
 }
}
