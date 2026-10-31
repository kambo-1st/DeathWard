#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){Simulation s(0,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,5);int room=1;EntityId id=0;Vector3 start{};for(const auto&e:s.roomEnemies(room))if(e.monster==monsterId(853)){id=e.id;start=e.position;break;}
s.jumpDebug(room);s.godMode=true;s.debugScenario=true;
for(int n=0;n<24;++n){auto p=add(start,rotateY({0,0,7},float(n)*Pi/12));p.y=.85f;if(s.arena.roomAt(p)!=room||s.arena.blocked(p,.48f)||!s.arena.sight(p,start))continue;if(std::any_of(s.enemies.begin(),s.enemies.end(),[&](const auto&e){return distance(p,e.position)<3;}))continue;s.player.position=p;break;}
std::cout<<"target="<<id<<" player="<<s.player.position.x<<","<<s.player.position.z<<"\n";for(int frame=0;frame<300;++frame){s.step({});if(!s.findEnemy(id)){std::cout<<"gone frame="<<frame<<"\n";break;}}}
