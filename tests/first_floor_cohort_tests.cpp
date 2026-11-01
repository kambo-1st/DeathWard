#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
const std::array<MonsterId,5> Cohort{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1),monsterId(12)};
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation fixture(unsigned seed,std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-24,-1,-24},{24,12,24}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-24,-.4f,-24},{24,0,24}}};}
    s.arena.boundaryWalls={{{-25,-1,-25},{-24,12,25}},{{24,-1,-25},{25,12,25}},{{-25,-1,-25},{25,12,-24}},{{-25,-1,24},{25,12,25}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.stats={};
    s.room=0;s.rooms.assign(s.arena.roomCount(),{});s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,18};
    return s;
}
void startingKit() {
    for(unsigned seed=0;seed<8;++seed) {
        auto s=fixture(seed);s.debugScenario=false;s.godMode=false;s.dynamite=0;
        check(s.player.hp==100&&s.player.shotDamage==24,"preserve starting health100/damage24");
        for(size_t n=0;n<Cohort.size();++n)check(s.spawnMonster(Cohort[n],{float(n)*4-8,.85f,-4}),"cohort spawn admitted");
        int frames=0;
        for(;frames<3600&&!s.dead&&!s.roomClear;++frames) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            Input input;
            if(target) {
                const auto delta=horizontal(sub(target->position,s.player.position));
                input.fire=true;input.aim=add(target->position,mul(horizontal(target->velocity),length(delta)/26));
                input.movement=length(delta)<7?mul(unit(delta),-1):length(delta)>12?unit(delta):Vector3{};
                input.dodge=length(delta)<2.5f;
            }
            s.step(input);
        }
        std::cout<<"COHORT_STARTING_KIT seed="<<seed<<" seconds="<<frames*Tick<<" hp="<<s.player.hp
                 <<" kills="<<s.stats.kills<<" clear="<<s.roomClear<<" suppressed="<<s.stats.suppressed<<'\n';
        check(s.roomClear&&!s.dead&&s.stats.kills==5&&s.stats.suppressed==0,
              "starting revolver/dodge clears mixed cohort and any morphs with exactly five root rewards");
    }
}
void natural() {
    std::set<MonsterId> found;std::set<int> lengths;int checked=0;
    for(unsigned seed=0;seed<32;++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        lengths.insert(s.expedition.floorCount);
        check(s.arena.roomCount()==9,"standard opening floor retains nine rooms");
        struct Snapshot{int room;EntityId id;Vector3 at;float age;};std::vector<Snapshot> residents;
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))
            if(std::find(Cohort.begin(),Cohort.end(),e.monster)!=Cohort.end()) {
                check(!s.arena.blocked(e.position,e.radius),"natural cohort body has a legal physical footprint");
                check(e.hp==32*(e.champion<0?1:s.content->champion(e.champion)->hp)&&(e.gaper||e.headless||s.content->headShooter(e.monster)),"seeded cohort has correct health and dedicated behavior");
                if(found.insert(e.monster).second)std::cout<<"COHORT_NATURAL id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor=0 room="<<room<<'\n';
                residents.push_back({room,e.id,e.position,e.age});++checked;
            }
        for(int n=0;n<30;++n)s.step({});
        for(const auto &old:residents) {
            const auto &group=s.roomEnemies(old.room);
            const auto it=std::find_if(group.begin(),group.end(),[&](const auto &e){return e.id==old.id;});
            check(it!=group.end()&&distance(it->position,old.at)<.0001f&&it->age==old.age,"unentered cohort residents remain idle");
        }
    }
    check(found.size()==5&&lengths==std::set<int>({4,5,6,7,8}),"all five ordinary identities reachable on first floors across every supported run length");
    std::cout<<"COHORT_PLACEMENT seeds=32 floors=32 lengths=4,5,6,7,8 residents="<<checked<<" identities="<<found.size()<<'\n';
}
void performance(const std::shared_ptr<const MechanicsLibrary> &content) {
    for(unsigned trial=0;trial<3;++trial) {
        auto s=fixture(1866,content);
        for(int n=0;n<20;++n)s.spawnMonster(Cohort[size_t(n)%Cohort.size()],{float(n%5)*4-8,.85f,float(n/5)*4-10});
        std::vector<double> times;size_t bullets=0;
        for(int n=0;n<1860;++n) {
            const auto start=std::chrono::steady_clock::now();s.step({});const auto end=std::chrono::steady_clock::now();
            if(n>=60)times.push_back(std::chrono::duration<double,std::micro>(end-start).count());
            bullets=std::max(bullets,s.projectiles.size());
        }
        std::sort(times.begin(),times.end());double total=0;for(double t:times)total+=t;
        std::cout<<"COHORT_PERF trial="<<trial<<" samples="<<times.size()<<" mean_us="<<total/times.size()
                 <<" p95_us="<<times[times.size()*95/100]<<" max_us="<<times.back()<<" actors="<<s.livingEnemies()
                 <<" peak_bullets="<<bullets<<" suppressed="<<s.stats.suppressed<<" render=0\n";
        check(s.livingEnemies()==20&&s.stats.suppressed==0,"stress fixture retains all actors without suppressed events");
    }
}
}
int main(int argc,char **argv) {
    std::cout<<std::unitbuf;
    try {
        if(argc>1&&std::string(argv[1])=="--performance")performance(argc>2?MechanicsLibrary::load(argv[2]):defaultMechanics());
        else {startingKit();natural();std::cout<<"PASS first-floor cohort\n";}
    }catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
