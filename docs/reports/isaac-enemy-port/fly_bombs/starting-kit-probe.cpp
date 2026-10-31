#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){for(const auto [seed,room]:std::array<std::pair<uint64_t,int>,3>{{{0,2},{4,1},{10,8}}}) {
 Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,2);s.jumpDebug(room);s.godMode=false;s.debugScenario=false;
 int flies=0;for(const auto&e:s.enemies)flies+=e.monster==monsterId(819);const auto initial=s.livingEnemies();
 for(int tick=0;tick<7200&&!s.dead&&!s.roomClear;++tick) {
  Input in;const Enemy *target=nullptr;
  for(const auto&e:s.enemies)if(e.alive&&!s.content->monster(e.monster)->roomHazard&&s.arena.sight(s.player.position,e.position))
   if(!target||distance(s.player.position,e.position)<distance(s.player.position,target->position))target=&e;
  if(!target)for(const auto&e:s.enemies)if(e.alive&&!s.content->monster(e.monster)->roomHazard){target=&e;break;}
  Vector3 move{};
  if(target){const auto toward=unit(horizontal(sub(target->position,s.player.position)));const float range=planarDistance(target->position,s.player.position);
   in.fire=true;in.aim=add(target->position,mul(target->velocity,.15f));
   move=add(Vector3{-toward.z,0,toward.x},mul(toward,std::clamp((range-8)*.4f,-1.f,1.f)));
  }
  for(const auto&e:s.enemies)if(e.alive){const auto away=horizontal(sub(s.player.position,e.position));const float range=length(away);
   if(range<3)move=add(move,mul(unit(away),(3-range)*1.3f));if(range<1.6f)in.dodge=true;}
  for(const auto &b:s.enemyBombs)if(b.room==s.room){const auto away=horizontal(sub(s.player.position,b.charge.position));
   if(length(away)<4)move=add(move,mul(unit(away),2));}
  for(const auto&p:s.projectiles)if(p.hostile&&distance(p.position,s.player.position)<1.8f)in.dodge=true;
  in.movement=unit(move);s.step(in);
 }
 std::cout<<"FLY_BOMB_STARTING_KIT seed="<<seed<<" floor=2 room="<<room<<" initial_actors="<<initial<<" initial_fly_bombs="<<flies
  <<" seconds="<<s.stats.duration<<" hp="<<s.player.hp<<" dead="<<s.dead<<" clear="<<s.roomClear<<" threats="<<s.roomThreats()
  <<" kills="<<s.stats.kills<<" explosions="<<s.stats.explosions<<" player_damage="<<s.player.shotDamage<<" max_hp="<<s.player.maxHp
  <<" god=0 teleports_during_fight=0 inventory_used=0 items="<<s.items.size()<<'\n';
 } }
