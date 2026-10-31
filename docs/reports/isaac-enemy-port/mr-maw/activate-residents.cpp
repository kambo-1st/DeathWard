#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
int main(){std::cout<<std::unitbuf;try{
 struct Witness{int seed,floor,room,band,variant;bool river;};
 for(const auto w:std::array<Witness,7>{{{1,4,3,2,2,false},{4,5,2,2,0,false},{6,3,11,3,2,true},
   {7,4,3,3,0,false},{65,2,5,1,2,false},{75,1,2,1,0,false},{81,3,7,2,0,true}}}) {
  Simulation s(w.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,w.floor);s.godMode=true;
  check(s.arena.profile.band==w.band,"source-equivalent floor band");
  check(w.variant!=2||w.band!=1||s.arena.profile.variant==FloorVariant::Flooded,"early red body requires Flooded Quarry");
  if(w.river)check(s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&
    std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==w.room;}),"real interior river crosses resident room");
  EntityId body=0,head=0;
  for(const auto &e:s.roomEnemies(w.room))if(e.monster==monsterId(35,w.variant)){body=e.id;head=e.partner;}
  check(body&&head,"actual seeded body and required head present before entry");s.enterRoom(w.room);s.player.position=s.arena.rooms[size_t(w.room)].entry;
  bool active=false;
  for(int n=0;n<240;++n){s.step({});
   for(const auto id:{body,head})if(const auto *e=s.findEnemy(id);e&&e->alive) {
    check(e->monster.type==35||e->monster.type==26||e->monster.type==11,"only source-defined survivors");
    if(e->linkedHead)active=active||e->linkedHead->ticks>0;
    const bool flying=s.content->monster(e->monster)->flying;
    check(!(flying?s.arena.flightBlocked(e->position,e->radius,w.room):s.arena.blocked(e->position,e->radius)),"active linked actor remains physically legal");
   }
  }
  check(active,"natural resident activates dedicated controller");
  std::cout<<"PASS seed="<<w.seed<<" floor="<<w.floor<<" room="<<w.room<<" band="<<w.band<<" variant="<<w.variant<<" river="<<w.river<<" frames=240\n";
 }
 return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
