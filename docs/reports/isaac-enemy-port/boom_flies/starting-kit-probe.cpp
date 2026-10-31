#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){
    struct Fixture {uint64_t seed;int floor,room;};
    for(const auto f:std::array<Fixture,7>{{{0,2,2},{0,3,8},{0,4,11},{4,3,4},{4,6,8},{16,1,4},{19,2,7}}}) {
        Simulation s(f.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,f.floor);
        s.jumpDebug(f.room);s.godMode=false;s.debugScenario=false;const auto initial=s.roomThreats();
        bool boom=false;for(const auto &e:s.enemies)boom|=e.monster.type==25;
        if(!boom){std::cout<<"WRONG_FIXTURE seed="<<f.seed<<" floor="<<f.floor<<" room="<<f.room<<'\n';return 1;}
        for(int step=0;step<10800&&!s.dead&&!s.roomClear;++step) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&!s.content->statue(e.monster)&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            if(!target)break;Input in;in.fire=true;in.aim=add(target->position,mul(target->velocity,.15f));
            const auto delta=horizontal(sub(target->position,s.player.position)),toward=unit(delta);
            auto move=add(Vector3{-toward.z,0,toward.x},mul(toward,std::clamp((length(delta)-9)*.5f,-1.f,1.f)));
            for(const auto &e:s.enemies)if(e.alive) {
                const auto away=horizontal(sub(s.player.position,e.position));if(length(away)<4)move=add(move,mul(unit(away),(4-length(away))*1.5f));
                if(length(away)<1.8f)in.dodge=true;
            }
            for(const auto &h:s.hazards) {
                const auto away=horizontal(sub(s.player.position,h.position));if(length(away)<h.radius+1.5f)move=add(move,mul(unit(away),2));
            }
            for(const auto &b:s.enemyBombs) {
                const auto away=horizontal(sub(s.player.position,b.charge.position));if(length(away)<b.charge.radius+2)move=add(move,mul(unit(away),3));
            }
            for(const auto &p:s.projectiles)if(p.hostile&&distance(p.position,s.player.position)<2)in.dodge=true;
            in.movement=unit(move);s.step(in);
        }
        std::cout<<"BOOM_STARTING_KIT seed="<<f.seed<<" floor="<<f.floor<<" room="<<f.room<<" initial_threats="<<initial<<" seconds="<<s.stats.duration
            <<" player_hp="<<s.player.hp<<" dead="<<s.dead<<" clear="<<s.roomClear<<" remaining="<<s.roomThreats()<<" explosions="<<s.stats.explosions
            <<" inventory="<<s.dynamite<<" god=0 teleports_during_combat=0 max_hp="<<s.player.maxHp<<" shot_damage="<<s.player.shotDamage<<" items="<<s.items.size()<<'\n';
    }
}
