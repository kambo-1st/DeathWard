#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
int main(int argc,char **argv){std::cout<<std::unitbuf;try{
 struct Witness{int seed,floor,room,band,variant;bool river;};
 for(const auto w:std::array<Witness,5>{{{5,3,4,2,0,false},{5,4,2,3,0,true},
   {8,6,5,3,1,false},{18,5,7,3,1,true},{28,7,9,3,3,false}}}) {
  if(argc>1&&w.variant!=std::stoi(argv[1]))continue;
  Simulation s(w.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,w.floor);s.godMode=true;
  check(s.arena.profile.band==w.band,"correct habitat band");
  if(w.river)check(s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&
   std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==w.room;}),"actual interior river");
  EntityId id=0;for(const auto &e:s.roomEnemies(w.room))if(e.monster==monsterId(38,w.variant))id=e.id;
  check(id,"actual resident present before entry");s.enterRoom(w.room);s.player.position=s.arena.rooms[size_t(w.room)].entry;
  uint64_t ticks=0,shots=0,teleports=0,dashes=0;
  for(int frame=0;frame<360;++frame) {
   s.step({});const auto *e=s.findEnemy(id);check(e&&e->alive&&e->baby,"resident remains active");
   check(std::abs(e->maxHp-80)<.001f,"source HP");
   if(e->baby->phase!=BabyPhase::Vanishing)
    check(!s.arena.flightBlocked(e->position,e->radius,w.room),"physical flight legality");
   ticks=e->baby->ticks;shots=e->baby->volleys;teleports=e->baby->teleports;dashes=e->baby->dashes;
  }
  check(ticks>170,"dedicated controller advances at30Hz");
  std::cout<<"PASS seed="<<w.seed<<" floor="<<w.floor<<" room="<<w.room<<" band="<<w.band<<" variant="<<w.variant
    <<" river="<<w.river<<" frames=360 ticks="<<ticks<<" volleys="<<shots<<" teleports="<<teleports<<" dashes="<<dashes<<'\n';
 }
 return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
