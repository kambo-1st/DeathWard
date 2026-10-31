#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
using namespace dw;
// Automated input sampling, not human balance acceptance. No combat teleports,
// items, god mode or scripted damage. Entry uses the actual generated boss room.
int main() {
    for(const auto [seed,floor]:std::array<std::pair<uint64_t,int>,4>{{{10,2},{58,3},{953,2},{1254,3}}}) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        s.jumpDebug(s.finalRoom());s.godMode=false;s.debugScenario=false;
        if(!s.boss()||s.boss()->monster!=monsterId(906))return 1;
        std::vector<double> samples;size_t peakBombs=0,peakShots=0;
        for(int frame=0;frame<10800&&!s.dead&&!s.roomClear;++frame) {
            Input in;const auto *target=s.boss();
            if(target) {
                in.fire=target->state!=EnemyState::Teleporting;
                in.aim=add(target->position,mul(target->velocity,.15f));
                const auto delta=horizontal(sub(target->position,s.player.position)),toward=unit(delta);
                auto move=add(Vector3{-toward.z,0,toward.x},mul(toward,std::clamp((length(delta)-9)*.5f,-1.f,1.f)));
                if(length(delta)<2)in.dodge=true;
                for(const auto &bomb:s.enemyBombs) {
                    const auto away=horizontal(sub(s.player.position,bomb.charge.position));
                    if(length(away)<bomb.charge.radius+2)move=add(move,mul(unit(away),3));
                }
                for(const auto &hazard:s.hazards) {
                    const auto away=horizontal(sub(s.player.position,hazard.position));
                    if(length(away)<hazard.radius+1.5f)move=add(move,mul(unit(away),2));
                }
                for(const auto &shot:s.projectiles)if(shot.hostile&&distance(shot.position,s.player.position)<2)in.dodge=true;
                in.movement=unit(move);
            }
            const auto begin=std::chrono::steady_clock::now();s.step(in);
            if(frame>=60)samples.push_back(std::chrono::duration<double,std::micro>(std::chrono::steady_clock::now()-begin).count());
            peakBombs=std::max(peakBombs,s.enemyBombs.size());peakShots=std::max(peakShots,s.projectiles.size());
        }
        const auto &h=*s.rooms[size_t(s.room)].hornfel;
        std::cout<<"HORNFEL_STARTING_KIT seed="<<seed<<" floor="<<floor<<" layout="<<s.arena.rails->layout<<" pits="<<s.arena.rails->pits.size()
            <<" seconds="<<s.stats.duration<<" hp="<<s.player.hp<<" dead="<<s.dead<<" clear="<<s.roomClear<<" escaped="<<h.escaped
            <<" completed="<<h.completed<<" state="<<int(h.state)<<" kills="<<s.stats.kills<<" inventory="<<s.dynamite
            <<" max_hp="<<s.player.maxHp<<" shot_damage="<<s.player.shotDamage<<" items="<<s.items.size()<<" god=0 combat_teleports=0\n";
        if(!samples.empty()) {
            std::sort(samples.begin(),samples.end());double sum=0;for(auto n:samples)sum+=n;
            std::cout<<"HORNFEL_NATIVE_STEP seed="<<seed<<" samples="<<samples.size()<<" mean_us="<<sum/samples.size()
                <<" p50_us="<<samples[samples.size()/2]<<" p95_us="<<samples[samples.size()*95/100]<<" max_us="<<samples.back()
                <<" peak_bombs="<<peakBombs<<" peak_projectiles="<<peakShots<<" suppressed="<<s.stats.suppressed
                <<" render=0 baseline_comparison=0 human_acceptance=0\n";
        }
    }
}
