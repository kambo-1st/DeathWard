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
int main(){for(bool exposed:{false,true}) {
 auto s=fixture();s.spawnMonster(monsterId(19,3),{0,.85f,0});
 const auto original=s.rooms[0].segmented[0].chains;
 if(exposed)for(const auto &chain:original)for(int i:{1,2,3}) {
  Event e;e.type=EventType::Explosion;e.position=e.origin=s.findEnemy(chain.members[size_t(i)])->position;e.radius=.1f;e.damage=15;e.demolition=Demolition::SuppliedBomb;s.queueRoot(e);s.drainEvents();
 }
 std::vector<double> samples;size_t peakActors=0,peakProjectiles=0,peakTrail=0;
 for(int n=0;n<1860;++n) {
  const auto start=std::chrono::steady_clock::now();s.step({});const auto stop=std::chrono::steady_clock::now();
  if(n>=60)samples.push_back(std::chrono::duration<double,std::micro>(stop-start).count());
  peakActors=std::max(peakActors,s.livingEnemies());peakProjectiles=std::max(peakProjectiles,s.projectiles.size());
  for(const auto &c:s.rooms[0].segmented[0].chains)peakTrail=std::max(peakTrail,c.trail.size());
 }
 std::sort(samples.begin(),samples.end());double sum=0;for(auto n:samples)sum+=n;
 std::cout<<"SHELL_NATIVE_STEP exposed="<<exposed<<" samples="<<samples.size()<<" mean_us="<<sum/samples.size()<<" p50_us="<<samples[samples.size()/2]<<" p95_us="<<samples[samples.size()*95/100]<<" max_us="<<samples.back()<<" peak_actors="<<peakActors<<" peak_projectiles="<<peakProjectiles<<" peak_trail="<<peakTrail<<" shots="<<s.stats.projectiles<<" render=0\n";
}}
