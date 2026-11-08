#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){
 std::cout<<"id,time,enemy_speed,player_base_speed,x,z\n";
 for(auto id:{monsterId(10),monsterId(10,1),monsterId(12),monsterId(14),monsterId(85)}){
  Simulation s(42,1,{},MissionTheme::Mine);s.arena=Arena{};auto &a=s.arena;
  a.bounds={{-80,-1,-80},{80,5,80}};a.rooms.resize(1);a.floors={{{-80,-.4f,-80},{80,0,80}}};a.boundaryWalls={};
  a.rooms[0].bounds=a.bounds;a.rooms[0].center={0,.85f,0};a.rooms[0].floors=a.floors;a.rebuildWalls();
  s.rooms.assign(1,{});s.room=0;s.debugScenario=true;s.godMode=true;s.enemies.clear();s.hazards.clear();s.projectiles.clear();
  s.player.position={30,.85f,0};auto entity=s.spawnMonster(id,{-30,.85f,0});
  for(int n=0;n<120;++n){s.step({});const auto *e=s.findEnemy(entity);if(!e)return 1;
   std::cout<<monsterIdText(id)<<','<<(n+1)*Tick<<','<<length(horizontal(e->velocity))<<','<<s.player.walkingSpeed()<<','<<e->position.x<<','<<e->position.z<<'\n';}
 }
}
