#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
using namespace dw;
Simulation fixture(std::shared_ptr<const MechanicsLibrary> rules=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(rules));s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,12,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;}
    for(auto &r:s.rooms){r.residents.clear();r.segmented.clear();r.cleared=false;r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.suppliedBombs.clear();s.enemyBombs.clear();s.moneyPickups.clear();s.stats={};
    s.debugScenario=true;s.godMode=true;s.roomClear=s.bossKilled=false;s.player.position={20,.85f,20};return s;
}
int main(){for(int variant:{0,1,2}) {
 auto s=fixture();const int groups=variant==2?12:1;
 for(int n=0;n<groups;++n)s.spawnMonster(monsterId(69,variant?1:0),{float(n%4)*8-12,.85f,float(n/4)*8-8});
 std::vector<double> samples;size_t peakActors=0,peakProjectiles=0;
 for(int n=0;n<1860;++n) {
  const auto start=std::chrono::steady_clock::now();s.step({});const auto stop=std::chrono::steady_clock::now();
  if(n>=60)samples.push_back(std::chrono::duration<double,std::micro>(stop-start).count());
  peakActors=std::max(peakActors,s.livingEnemies());peakProjectiles=std::max(peakProjectiles,s.projectiles.size());
 }
 std::sort(samples.begin(),samples.end());double sum=0;for(auto n:samples)sum+=n;
 std::cout<<"LOKI_NATIVE_STEP variant="<<variant<<" groups="<<groups<<" samples="<<samples.size()<<" mean_us="<<sum/samples.size()<<" p50_us="<<samples[samples.size()/2]<<" p95_us="<<samples[samples.size()*95/100]<<" max_us="<<samples.back()<<" peak_actors="<<peakActors<<" peak_projectiles="<<peakProjectiles<<" shots="<<s.stats.projectiles<<" suppressed="<<s.stats.suppressed<<" render=0 baseline_comparison=0\n";
}}
