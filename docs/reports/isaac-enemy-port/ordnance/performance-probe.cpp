#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
using namespace dw;
int main() {
    for(int count:{1,16,64}) {
        Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
        s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,12,25}};
        for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;}
        for(auto &r:s.rooms){r.residents.clear();r.segmented.clear();r.cleared=false;r.plates.clear();}
        s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.pendingEnemyBombs.clear();s.stats={};
        s.debugScenario=s.godMode=true;s.roomClear=s.bossKilled=false;s.player.position={20,.85f,20};
        const auto owner=s.spawnMonster(monsterId(69),{-20,.85f,-20});if(!owner)return 2;s.findEnemy(owner)->cooldown=10000;
        const std::array<std::string_view,4> profiles{"normal","hot","sad","brimstone"};
        std::vector<double> times;size_t peakBombs=0,peakPending=0,peakShots=0;int rejected=0;
        for(int tick=0;tick<1860;++tick) {
            const auto start=std::chrono::steady_clock::now();
            if(tick%120==0)for(int n=0;n<count;++n) {
                Vector3 p{float(n%8)*4-14,1,float(n/8)*4-14};
                if(!s.throwEnemyBomb(profiles[size_t(n+tick/120)%4],owner,p,add(p,{2,0,2})))++rejected;
            }
            s.step({});const auto stop=std::chrono::steady_clock::now();
            if(tick>=60)times.push_back(std::chrono::duration<double,std::micro>(stop-start).count());
            peakBombs=std::max(peakBombs,s.enemyBombs.size());peakPending=std::max(peakPending,s.pendingEnemyBombs.size());peakShots=std::max(peakShots,s.projectiles.size());
            if(peakBombs>s.limits.enemyBombs||peakPending>s.limits.pendingEnemyBombs||peakShots>s.limits.projectiles)return 3;
        }
        std::sort(times.begin(),times.end());double sum=0;for(auto t:times)sum+=t;
        std::cout<<"ORDNANCE_CPU burst="<<count<<" every_ticks=120 samples="<<times.size()<<" mean_us="<<sum/times.size()
            <<" p50_us="<<times[times.size()/2]<<" p95_us="<<times[times.size()*95/100]<<" max_us="<<times.back()
            <<" peak_bombs="<<peakBombs<<" peak_pending="<<peakPending<<" peak_projectiles="<<peakShots<<" rejected="<<rejected
            <<" explosions="<<s.stats.explosions<<" render=0 baseline_comparison=0\n";
    }
}
