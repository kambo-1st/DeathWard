#include "items/Items.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
void near(float actual,float expected,const char *message){check(std::abs(actual-expected)<.002f,message);}
Simulation fixture() {
    Simulation run(42,1,{},MissionTheme::Mine);
    run.arena=Arena{};auto &a=run.arena;a.bounds={{-45,-1,-45},{45,5,45}};a.rooms.resize(1);
    a.floors={{{-45,-.4f,-45},{45,0,45}}};a.boundaryWalls={};
    auto &room=a.rooms[0];room.bounds=a.bounds;room.center=room.entry={0,.85f,0};room.floors=a.floors;
    room.exit=room.objective={1000,0,1000};a.rebuildWalls();run.rooms.assign(1,{});
    run.room=0;run.debugScenario=true;run.roomClear=false;run.godMode=true;
    run.enemies.clear();run.projectiles.clear();run.hazards.clear();run.items.clear();run.stats={};
    run.player=Player{};run.player.position={0,.85f,0};return run;
}
void primary(Simulation &run){Input in;in.fire=true;in.aimDirection=Vector3{1,0,0};run.step(in);}
void ticks(Simulation &run,int count){for(int n=0;n<count;++n)run.step({});}
void witness(Simulation &run,float x){
    Enemy e;e.id=100000;e.kind=EnemyKind::Monster;e.monster={12,0,0};e.position={x,.85f,0};
    e.hp=e.maxHp=1000;e.radius=.65f;run.enemies.push_back(e);
    check(run.applyEnemyStatus(e.id,EnemyStatus::Freeze,-18000),"stationary integration witness freezes");
}
}
int main(){
    try {
        for(auto theme:{MissionTheme::Mine,MissionTheme::Canyon})for(bool tutorial:{false,true}){
            Simulation run(42,1,{},theme,false,tutorial);
            check(run.canonicalShooting,"ordinary and tutorial expeditions use canonical shooting by default");
            near(run.player.shotDamage,24,"attack damage remains outside this integration");
            near(run.player.hp,6,"starting health remains six half-heart units");
        }
        auto base=fixture();primary(base);check(base.projectiles.size()==1,"default primary emits one projectile");
        const auto &p=base.projectiles.front();check(p.attack.canonicalFlight&&p.playerFlight,"default primary uses accepted flight");
        near(p.attack.speed,8,"default launch matches accepted review");near(p.attack.maxDistance,11,"default reach matches accepted review");
        near(p.damage,24,"canonical shooting does not change attack damage");near(base.player.fireCooldown,11.f/30,"default rate matches accepted review");
        for(int mode=0;mode<4;++mode){
            auto run=fixture();if(mode==1)run.player.attributes.tearsPerSecond*=2;
            if(mode==2)run.player.attributes.shotSpeed*=1.5f;if(mode==3)run.player.attributes.rangeTiles*=2;
            Input fire;fire.fire=true;fire.aimDirection=Vector3{1,0,0};
            for(int n=0;n<480;++n){run.step(fire);for(const auto &q:run.projectiles){
                near(q.attack.speed,mode==2?12:8,"only Shot Speed changes default launch");
                near(q.attack.maxDistance,mode==3?22:11,"only Range changes default reach");
            }}
            check(run.stats.shots==uint64_t(mode==1?44:22),"only Tears changes normal-expedition emission count");
        }
        auto split=fixture();split.grant(ItemId::Split);witness(split,9);primary(split);
        for(int n=0;n<180&&!split.stats.splits;++n)split.step({});
        check(split.stats.splits==1&&split.projectiles.size()==2,"canonical primary creates split descendants");
        for(const auto &q:split.projectiles){check(q.attack.canonicalFlight,"split preserves canonical specification");
            check(q.attack.maxDistance>0&&q.attack.maxDistance<3,"split consumes remaining range instead of restarting full range");}
        ticks(split,180);check(split.projectiles.empty(),"split range/lifetime remains bounded");

        auto returning=fixture();returning.grant(ItemId::Return);primary(returning);bool passedBaseBudget=false,turned=false;
        for(int n=0;n<240&&!returning.projectiles.empty();++n){
            const auto &q=returning.projectiles.front();turned|=q.returning;
            passedBaseBudget|=q.returning&&q.traveled>q.attack.maxDistance;returning.step({});
        }
        check(turned&&passedBaseBudget&&returning.projectiles.empty(),"outward range does not cut off return leg or prevent catch");
        auto scatter=fixture();scatter.grant(ItemId::Scatter);primary(scatter);
        check(scatter.projectiles.size()==5,"authored scatter count remains");
        for(const auto &q:scatter.projectiles){near(q.damage,9.12f,"scatter damage unchanged");near(q.attack.maxDistance,14,"authored scatter range exception retained");}
        auto scatterFast=fixture();scatterFast.grant(ItemId::Scatter);scatterFast.player.attributes.shotSpeed=2;primary(scatterFast);
        near(scatterFast.projectiles.front().attack.maxDistance,14,"Shot Speed does not rewrite scatter range");
        auto scatterRange=fixture();scatterRange.grant(ItemId::Scatter);scatterRange.player.attributes.rangeTiles*=2;primary(scatterRange);
        near(scatterRange.projectiles.front().attack.maxDistance,28,"Range scales authored scatter distance");

        // Birth/lifecycle compatibility for authored pairs; not native item acceptance.
        int pairs=0;for(int a=0;a<ItemCount;++a)for(int b=a;b<ItemCount;++b){
            auto run=fixture();run.grant(ItemId(a));run.grant(ItemId(b));witness(run,3);primary(run);
            check(run.stats.shots==1,"authored pairs retain one primary trigger");
            for(int n=0;n<300;++n){
                for(const auto &q:run.projectiles)check(q.attack.canonicalFlight&&std::isfinite(q.life)&&std::isfinite(q.velocity.x)&&q.attack.maxDistance>=0,"authored pair preserves valid canonical projectile state");
                run.step({});
            }
            check(run.projectiles.empty()&&run.queuedEvents()==0,"authored pair lifecycle terminates");++pairs;
        }
        auto floor=fixture();floor.player.attributes.shotSpeed=1.5f;floor.player.attributes.rangeTiles=13;
        floor.jumpDebug(floor.finalRoom());floor.clearRoomDebug();floor.floorExitRequested=true;
        check(floor.advanceFloor()&&floor.canonicalShooting&&floor.player.attributes.shotSpeed==1.5f&&floor.player.attributes.rangeTiles==13,"production mode and stat state survive floor transfer");
        auto historical=fixture();historical.canonicalShooting=false;
        historical.jumpDebug(historical.finalRoom());historical.clearRoomDebug();historical.floorExitRequested=true;
        check(historical.advanceFloor()&&!historical.canonicalShooting,"explicit historical comparison mode also survives floor transfer");
        auto ghost=fixture();ghost.grant(ItemId::Ghost);Event kill;kill.type=EventType::EnemyKilled;kill.direction={1,0,0};kill.position=kill.origin={0,.85f,0};
        ghost.queueRoot(kill);ghost.drainEvents();check(!ghost.projectiles.empty()&&ghost.projectiles.back().attack.canonicalFlight,"shotless ghost repeats canonical weapon specification");
        std::cout<<"PASS normal-expedition defaults, independent stats, split budgets, return catch, scatter exception, "<<pairs<<" authored pair lifecycles, floor carry and shotless ghost\n";
        return 0;
    }catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}
}
