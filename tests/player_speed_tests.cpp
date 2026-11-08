#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace dw;
constexpr Vector3 Spawn{0,.85f,0};
void check(bool ok,const char *message) { if(!ok)throw std::runtime_error(message); }
void near(float value,float expected,const char *message) {check(std::abs(value-expected)<.002f,message);}
Simulation fixture() {
    Simulation run(42,1,{},MissionTheme::Mine);
    run.arena=Arena{};auto &a=run.arena;
    a.bounds={{-40,-1,-40},{40,5,40}};a.rooms.resize(1);
    a.floors={{{-40,-.4f,-40},{40,0,40}}};a.boundaryWalls={};
    auto &room=a.rooms[0];room.bounds=a.bounds;room.center=room.entry=Spawn;room.floors=a.floors;
    room.exit=room.objective={1000,0,1000};a.rebuildWalls();
    run.rooms.assign(1,{});run.room=0;run.debugScenario=true;run.roomClear=false;
    run.enemies.clear();run.projectiles.clear();run.hazards.clear();run.items.clear();
    run.player=Player{};run.player.position=Spawn;run.stats={};
    return run;
}
}

int main() {
    try {
        for(float speed:{0.f,.5f,1.f,1.5f,2.f})for(bool diagonal:{false,true}) {
            auto run=fixture();run.player.attributes.speed=speed;
            Input in;in.movement=diagonal?Vector3{1,0,1}:Vector3{1,0,0};
            for(int n=0;n<120;++n)run.step(in);
            near(distance(horizontal(run.player.position),horizontal(Spawn)),9.6f*speed,
                 "canonical Speed controls straight/diagonal walking without a diagonal boost");
            const auto stop=run.player.position;run.step({});
            near(distance(stop,run.player.position),0,"release stopping remains immediate");
            in.movement=mul(in.movement,-1);run.step(in);
            near(distance(stop,run.player.position),4.8f*speed*Tick,"reversal is immediate at selected Speed");

            auto slowed=fixture();slowed.player.attributes.speed=speed;slowed.player.slowTime=10;
            Input slowWalk;slowWalk.movement={1,0,0};for(int n=0;n<60;++n)slowed.step(slowWalk);
            near(distance(slowed.player.position,Spawn),3.2f*speed,
                 "slowed walking follows Speed without speeding up or reviving zero-Speed movement");

            // The universal dodge exception has its own absolute boost.
            auto dodge=fixture();dodge.player.attributes.speed=speed;
            Hazard hazard;hazard.kind=HazardKind::Creep;hazard.position=Spawn;
            hazard.delay=0;hazard.duration=1;hazard.radius=50;hazard.damage=10;
            dodge.hazards.push_back(hazard);Input dash;dash.movement={1,0,0};dash.dodge=true;
            dodge.step(dash);check(dodge.player.hp==6,"dodge immunity survives every walking Speed");
            near(distance(dodge.player.position,Spawn)/Tick,20.4f,"walking Speed does not alter dodge boost");
            dodge.hazards.clear();dash.dodge=false;int boosted=1;
            while(dodge.player.dodge>0&&boosted<60){dodge.step(dash);++boosted;}
            check(boosted==14,"dodge duration remains fourteen boosted ticks");
            near(distance(dodge.player.position,Spawn),4.76f,"dodge distance remains unchanged");
        }

        auto run=fixture();run.player.attributes.speed=1.5f;
        Input click;click.moveTarget=Vector3{8,.85f,0};run.step(click);
        for(int n=0;n<179;++n)run.step({});
        near(distance(run.player.position,Vector3{8,.85f,0}),0,"click-to-walk reaches and stops at destination without overshoot");
        auto zero=fixture();zero.player.attributes.speed=0;zero.step(click);
        near(distance(zero.player.position,Spawn),0,"zero Speed click route does not divide by zero or move");
        zero.player.attributes.speed=1;for(int n=0;n<180;++n)zero.step({});
        near(distance(zero.player.position,Vector3{8,.85f,0}),0,"paused click route resumes when Speed becomes positive");

        // Shot Speed and other unwired attributes cannot alter walking.
        auto independent=fixture();independent.player.attributes.shotSpeed=2;
        independent.player.attributes.tearsPerSecond=6;independent.player.attributes.rangeTiles=13;
        independent.player.attributes.damage=7;independent.player.attributes.luck=-2;
        Input walk;walk.movement={1,0,0};for(int n=0;n<60;++n)independent.step(walk);
        near(distance(independent.player.position,Spawn),4.8f,"only Speed drives the movement consumer");
        for(float speed:{.5f,1.f,2.f}) {
            auto shot=fixture();shot.player.attributes.speed=speed;
            Input fire;fire.fire=true;fire.aimDirection=Vector3{0,0,-1};shot.step(fire);
            check(shot.projectiles.size()==1,"one existing primary projectile emitted");
            near(shot.projectiles.front().attack.speed,8,"Speed does not rewrite base projectile speed");
            near(shot.projectiles.front().damage,24,"Speed does not rewrite existing attack damage");
            near(shot.player.fireCooldown,11.f/30.f,"Speed does not rewrite existing firing interval");
        }
        Player player;player.hp=5;player.soulHearts=2;player.attributes.speed=1.5f;
        auto snapshot=player.sourceAttributes();
        check(snapshot.health.red==5&&snapshot.health.soul==2,"attribute snapshot reads authoritative live typed health");
        snapshot.health.addRed(1);snapshot.speed=2;
        check(player.hp==5&&player.attributes.speed==1.5f,"snapshot is not a second mutable runtime authority");

        auto floors=fixture();floors.player.attributes.speed=1.5f;
        floors.jumpDebug(floors.finalRoom());floors.clearRoomDebug();floors.floorExitRequested=true;
        check(floors.advanceFloor()&&floors.player.attributes.speed==1.5f,"canonical Speed survives floor transfer");
        std::cout<<"PASS canonical Speed movement, click route/arrival, zero/reversal, independent stats, retained dodge, health snapshot and floor transfer\n";
        return 0;
    } catch(const std::exception &e) {std::cerr<<e.what()<<'\n';return 1;}
}
