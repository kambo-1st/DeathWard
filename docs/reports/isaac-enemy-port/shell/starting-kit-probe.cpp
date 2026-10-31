#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void startingKitProbe() {
    for(const auto [seed,floor]:std::array<std::pair<uint64_t,int>,3>{{{7,2},{23,2},{28,3}}}) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);
        if(s.arena.profile.bossMonster!=monsterId(19,3))throw std::runtime_error("Wrong natural Shell fixture");
        s.jumpDebug(s.finalRoom());s.godMode=false;s.dynamite=0;s.debugScenario=false;
        for(int tick=0;tick<14400&&!s.dead&&!s.roomClear;++tick) {
            Input in;const Enemy *armored=nullptr,*target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&!e.segmentHead&&!s.content->statue(e.monster)) {
                if(e.segmentArmor>0) {if(!armored||planarDistance(s.player.position,e.position)<planarDistance(s.player.position,armored->position))armored=&e;}
                else if(!target||planarDistance(s.player.position,e.position)<planarDistance(s.player.position,target->position))target=&e;
            }
            auto move=Vector3{};
            if(const auto *bomb=s.carriedBomb()) {
                if(armored) {
                    const auto delta=horizontal(sub(armored->position,s.player.position));const float range=length(delta);
                    move=mul(unit(delta),std::clamp((range-7)*.5f,-1.f,1.f));
                    if(bomb->charge.age>2.1f){in.fire=true;in.aim=add(armored->position,mul(armored->velocity,.7f));}
                } else {in.fire=true;in.aim=target?target->position:add(s.player.position,{10,0,0});}
            } else {
                const SuppliedBomb *pickup=nullptr;
                if(armored)for(const auto &b:s.suppliedBombs)if(b.state==SuppliedBombState::Pickup&&
                    (!pickup||planarDistance(s.player.position,b.charge.position)<planarDistance(s.player.position,pickup->charge.position)))pickup=&b;
                if(pickup)move=unit(horizontal(sub(pickup->charge.position,s.player.position)));
                else if(target) {
                    const auto toward=unit(horizontal(sub(target->position,s.player.position)));
                    move=add(Vector3{-toward.z,0,toward.x},mul(toward,std::clamp((planarDistance(target->position,s.player.position)-9)*.5f,-1.f,1.f)));
                }
                if(target){in.fire=true;in.aim=add(target->position,mul(target->velocity,.2f));}
            }
            for(const auto &e:s.enemies)if(e.alive&&!s.content->statue(e.monster)) {
                const auto away=horizontal(sub(s.player.position,e.position));const float range=length(away);
                if(range<3)move=add(move,mul(unit(away),(3-range)*1.2f));
                if(range<1.8f)in.dodge=true;
            }
            for(const auto &b:s.suppliedBombs)if(b.state==SuppliedBombState::Thrown&&b.charge.age>2) {
                const auto away=horizontal(sub(s.player.position,b.charge.position));if(length(away)<5)move=add(move,mul(unit(away),3));
            }
            for(const auto &shot:s.projectiles)if(shot.hostile&&distance(shot.position,s.player.position)<2)in.dodge=true;
            in.movement=unit(move);s.step(in);
        }
        float hp=0,armor=0;int alive=0;
        for(const auto &e:s.enemies)if(e.alive&&e.segmentedEncounter&&!e.segmentHead){++alive;hp+=e.hp;armor+=e.segmentArmor;}
        std::cout<<"SHELL_STARTING_KIT_PROBE seed="<<seed<<" floor="<<floor<<" seconds="<<s.stats.duration<<" player_hp="<<s.player.hp<<" dead="<<s.dead
            <<" boss_killed="<<s.bossKilled<<" room_clear="<<s.roomClear<<" remaining_threats="<<s.roomThreats()<<" remaining_parts="<<alive<<" remaining_hp="<<hp<<" remaining_armor="<<armor
            <<" explosions="<<s.stats.explosions<<" inventory="<<s.dynamite<<" god=0 teleports=0 max_hp="<<s.player.maxHp<<" shot_damage="<<s.player.shotDamage<<" items="<<s.items.size()<<"\n";
    }
}
int main(){startingKitProbe();}
