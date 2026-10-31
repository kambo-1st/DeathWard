#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(){
    struct Fixture {uint64_t seed;int floor;};std::vector<Fixture> fixtures;std::array<int,2> counts{};
    for(uint64_t seed=0;seed<128&&(counts[0]<4||counts[1]<4);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            const auto p=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            if(p.bossMonster.type==69&&counts[size_t(p.bossMonster.variant)]<4) {fixtures.push_back({seed,floor});++counts[size_t(p.bossMonster.variant)];}
        }
    }
    for(const auto f:fixtures) {
        Simulation s(f.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,f.floor);
        s.jumpDebug(s.finalRoom());s.godMode=false;s.debugScenario=false;const auto initial=s.roomThreats();
        bool boom=s.boss()&&s.boss()->monster.type==69;
        if(!boom){std::cout<<"WRONG_FIXTURE seed="<<f.seed<<" floor="<<f.floor<<" room="<<s.finalRoom()<<'\n';return 1;}
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
        std::cout<<"LOKI_STARTING_KIT seed="<<f.seed<<" floor="<<f.floor<<" room="<<s.finalRoom()<<" variant="<<s.arena.profile.bossMonster.variant<<" initial_threats="<<initial<<" seconds="<<s.stats.duration
            <<" player_hp="<<s.player.hp<<" dead="<<s.dead<<" clear="<<s.roomClear<<" remaining="<<s.roomThreats()<<" explosions="<<s.stats.explosions
            <<" inventory="<<s.dynamite<<" god=0 teleports_during_combat=0 max_hp="<<s.player.maxHp<<" shot_damage="<<s.player.shotDamage<<" items="<<s.items.size()<<'\n';
    }
}
