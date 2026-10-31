#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main() {
    std::array<int,4> cases{};int clears=0,total=0;
    for(uint64_t seed=0;seed<32&&total<6;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&total<6;++floor) {
            const int band=plan.profileOnFloor(floor).band;if(band==0||cases[band]>=2)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            int room=-1;
            for(int r=1;r<s.finalRoom()&&room<0;++r)for(const auto &e:s.roomEnemies(r))if(e.monster==monsterId(227))room=r;
            if(room<0)continue;
            ++cases[band];++total;s.jumpDebug(room);s.godMode=false;s.debugScenario=false;
            const auto threats=s.roomThreats();
            for(int step=0;step<10800&&!s.dead&&!s.roomClear;++step) {
                const Enemy *target=nullptr;
                for(const auto &e:s.enemies)if(e.alive&&!s.content->statue(e.monster)&&
                    (!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
                if(!target)break;
                Input in;in.fire=true;in.aim=add(target->position,mul(target->velocity,.15f));
                const auto delta=horizontal(sub(target->position,s.player.position)),toward=unit(delta);
                auto move=add(Vector3{-toward.z,0,toward.x},mul(toward,std::clamp((length(delta)-9)*.5f,-1.f,1.f)));
                for(const auto &e:s.enemies)if(e.alive) {
                    const auto away=horizontal(sub(s.player.position,e.position));
                    if(length(away)<4)move=add(move,mul(unit(away),(4-length(away))*1.5f));
                    if(length(away)<1.8f)in.dodge=true;
                }
                for(const auto &p:s.projectiles)if(p.hostile&&distance(p.position,s.player.position)<2)in.dodge=true;
                in.movement=unit(move);s.step(in);
            }
            clears+=s.roomClear;
            std::cout<<"BONY_STARTING_KIT seed="<<seed<<" floor="<<floor<<" band="<<band<<" room="<<room
                <<" initial_threats="<<threats<<" seconds="<<s.stats.duration<<" hp="<<s.player.hp
                <<" dead="<<s.dead<<" clear="<<s.roomClear<<" remaining="<<s.roomThreats()
                <<" max_hp="<<s.player.maxHp<<" shot_damage="<<s.player.shotDamage<<" items="<<s.items.size()
                <<" god=0 teleports_during_combat=0\n";
            if(!s.roomClear)for(const auto &e:s.enemies)if(e.alive) {
                std::cout<<"REMAINING type="<<monsterIdText(e.monster)<<" hp="<<e.hp
                    <<" distance="<<distance(s.player.position,e.position)
                    <<" sight="<<s.arena.sight(s.player.position,e.position)
                    <<" path_points="<<s.arena.path(s.player.position,e.position,.48f).size()
                    <<" player_x="<<s.player.position.x<<" player_z="<<s.player.position.z
                    <<" enemy_x="<<e.position.x<<" enemy_z="<<e.position.z<<'\n';
            }
        }
    }
    std::cout<<"BONY_SAMPLE clears="<<clears<<" cases="<<total<<" scope=automated_mixed_room_sample_not_final_balance\n";
    return total==6?0:1;
}
