#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){Simulation s(24,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);auto &a=s.arena;
for(auto &p:a.passages){p.locked=false;p.sealed={false,false};}a.rebuildWalls();auto pos=a.supplyCache.approach;
std::cout<<"approach "<<pos.x<<","<<pos.z<<" room "<<a.supplyCache.room<<"\n";
for(auto &p:a.breakables)if(p.room==a.supplyCache.room)std::cout<<int(p.kind)<<" "<<p.bounds.min.x<<","<<p.bounds.min.z<<" -> "<<p.bounds.max.x<<","<<p.bounds.max.z<<" health "<<p.health<<"\n";
s.player.position=pos;Event blast;blast.type=EventType::Explosion;blast.position=pos;blast.radius=4.5f;blast.damage=100;blast.demolition=Demolition::SpentDynamite;blast.playerDamage=25;s.queueRoot(blast);s.drainEvents();
for(auto &p:a.breakables)if(p.kind==BreakableKind::CacheGate)std::cout<<"gate after "<<p.health<<" destroyed "<<p.destroyed<<"\n";
}
