#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
using namespace dw;
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,12,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;}
    for(auto &r:s.rooms){r.residents.clear();r.segmented.clear();r.cleared=false;r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.suppliedBombs.clear();s.moneyPickups.clear();s.stats={};
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={20,.85f,20};return s;
}
int main(){for(bool chain:{false,true}) {
    auto s=fixture();
    if(chain)for(int i=0;i<8;++i) {
        const auto id=s.spawnMonster(monsterId(25,6),{0,.85f,0});Event death;death.type=EventType::Damage;death.target=id;death.damage=1000;s.queueRoot(death);s.drainEvents();
    } else for(int i=0;i<24;++i) {
        const int v=i%6;const auto id=s.spawnMonster(monsterId(25,v),{float(i%6)*5-15,.85f,float(i/6)*5-10});
        if(auto *e=s.findEnemy(id))e->cooldown=0;
    }
    std::vector<double> samples;size_t actors=0,bullets=0,fields=0,armed=0,pending=0;
    for(int n=0;n<1860;++n) {
        const auto start=std::chrono::steady_clock::now();s.step({});const auto stop=std::chrono::steady_clock::now();
        // Include initial chain work; it is the relevant worst-case interval.
        if(chain||n>=60)samples.push_back(std::chrono::duration<double,std::micro>(stop-start).count());
        actors=std::max(actors,s.livingEnemies());bullets=std::max(bullets,s.projectiles.size());fields=std::max(fields,s.hazards.size());
        armed=std::max(armed,s.enemyBombs.size());pending=std::max(pending,s.pendingEnemyBombs.size());
    }
    std::sort(samples.begin(),samples.end());double sum=0;for(auto x:samples)sum+=x;
    std::cout<<"BOOM_CPU_STEP chain="<<chain<<" samples="<<samples.size()<<" mean_us="<<sum/samples.size()<<" p95_us="<<samples[samples.size()*95/100]
        <<" max_us="<<samples.back()<<" peak_actors="<<actors<<" peak_bullets="<<bullets<<" peak_fields="<<fields<<" peak_armed="<<armed<<" peak_pending="<<pending
        <<" suppressed="<<s.stats.suppressed<<" explosions="<<s.stats.explosions<<" render=0 baseline_comparison=0\n";
}}
