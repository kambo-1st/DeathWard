#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float tolerance=.001f){return std::abs(a-b)<tolerance;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine);s.enemies.clear();s.arena=Arena{};
    s.arena.bounds={{-100,-1,-100},{100,30,100}};
    for(auto &room:s.arena.rooms){room.bounds=s.arena.bounds;room.center={0,0,0};room.kind=RoomKind::Combat;}
    s.arena.rebuildWalls();s.rooms.assign(s.arena.rooms.size(),{});s.room=0;
    s.player.position={70,.85f,70};s.godMode=true;s.debugScenario=true;s.roomClear=false;return s;
}
EntityId shot(Simulation &s,int direction,float acceleration=1,float radius=0,Vector3 at={0,.85f,0}) {
    Event event;event.position=event.origin=at;event.direction={1,0,0};event.speed=24;
    event.hostile=true;event.projectileLife=10;event.damage=10;
    event.projectilePlanarMotion=SourcePlanarMotionDefinition{acceleration,radius,direction,at};
    check(s.queueRoot(event),"shot event admitted");s.drainEvents();return s.projectiles.back().id;
}
void recurrence() {
    auto cw=fixture(),ccw=fixture();shot(cw,1);shot(ccw,-1);
    cw.step({},Tick);ccw.step({},Tick);
    check(near(cw.projectiles[0].position.x,.4f)&&near(cw.projectiles[0].velocity.z,0),"first half-frame travels along birth velocity");
    cw.step({},Tick);ccw.step({},Tick);
    // Independently derived first native endpoint: radial .5 plus unit tangent.
    check(near(cw.projectiles[0].position.x,.8f)&&near(cw.projectiles[0].velocity.x,24/std::sqrt(5.f))&&
        near(cw.projectiles[0].velocity.z,48/std::sqrt(5.f)),"first orbit endpoint matches native radial-plus-tangent rule");
    for(int n=0;n<58;++n){cw.step({},Tick);ccw.step({},Tick);}
    const auto &a=cw.projectiles[0],&b=ccw.projectiles[0];
    check(near(length(a.velocity),24)&&near(a.position.x,b.position.x)&&near(a.position.z,-b.position.z),"opposite rings are mirrored and retain speed");
    check(planarDistance(a.position,{0,0,0})>6,"zero orbit distance spirals outward instead of circling at fixed radius");
    auto coarse=fixture(),fine=fixture();shot(coarse,1);shot(fine,1);
    for(int n=0;n<30;++n)coarse.step({},1.f/30);
    for(int n=0;n<120;++n)fine.step({},1.f/120);
    check(distance(a.position,coarse.projectiles[0].position)<.001f&&distance(a.position,fine.projectiles[0].position)<.001f,
        "source orbit endpoints survive 30/60/120 Hz subdivision");
    auto band=fixture();shot(band,1,1,4);
    for(int n=0;n<90;++n)band.step({},Tick);
    check(planarDistance(band.projectiles[0].position,{})<7,"positive orbit radius reduces outward drift");
    std::cout<<"ORBIT source_endpoint=1 opposite_handedness=1 cadence=1 radial_drift=1\n";
}
void acceleration() {
    for(float factor:{.73f,1.f,1.03f}) {
        auto s=fixture();shot(s,0,factor);float position=0,velocity=24;
        for(int n=0;n<15;++n){position+=velocity/30;velocity*=factor;s.step({},1.f/30);}
        const auto &p=s.projectiles[0];check(near(p.position.x,position)&&near(p.velocity.x,velocity),"acceleration uses source movement-then-multiply order");
        check(near(p.velocity.y,0)&&!p.noWallCollision,"plain acceleration preserves height and scenery collision");
    }
    auto s=fixture();shot(s,1,.97f);s.projectiles[0].velocity.y=3;s.step({},1.f/30);
    check(near(s.projectiles[0].velocity.y,3)&&near(s.projectiles[0].position.y,.95f),"orbit and deceleration do not alter falling velocity");
    std::cout<<"ACCELERATION deceleration=1 growth=1 independent_height=1\n";
}
void extendedAcceleration() {
    auto coarse=fixture(),fine=fixture(),finer=fixture();
    for(auto *s:{&coarse,&fine,&finer}) {
        shot(*s,0,.9f);s->projectiles[0].sourcePlanarMotion->accelerationRampFrames=20;
        s->projectiles[0].velocity.y=1.5f;
    }
    float position=0,velocity=24;
    for(int n=1;n<=40;++n) {
        position+=velocity/30;
        // Independent native ACCELERATE_EX calculation: min(age/20,1), then
        // linear interpolation from1 to.9, after this frame's translation.
        velocity*=1-.1f*std::min(float(n)/20,1.f);
        coarse.step({},1.f/30);for(int k=0;k<2;++k)fine.step({},1.f/60);for(int k=0;k<4;++k)finer.step({},1.f/120);
        const auto &p=coarse.projectiles[0];
        check(near(p.position.x,position)&&near(p.velocity.x,velocity)&&p.planarTicks==unsigned(n),
            "extended acceleration matches native age-dependent recurrence before and after ramp saturation");
        check(distance(p.position,fine.projectiles[0].position)<.002f&&distance(p.position,finer.projectiles[0].position)<.002f&&
            near(p.velocity.x,fine.projectiles[0].velocity.x)&&near(p.velocity.x,finer.projectiles[0].velocity.x),
            "ramp age advances only at source endpoints under30/60/120Hz subdivision");
        check(near(p.velocity.y,1.5f)&&near(p.position.y,.85f+float(n)*.05f),"ramp does not alter independent vertical motion");
    }
    auto wall=fixture();wall.arena.obstacles.push_back({{.25f,0,-3},{.3f,3,3}});wall.arena.rebuildWalls();
    shot(wall,0,.9f);wall.projectiles[0].sourcePlanarMotion->accelerationRampFrames=20;wall.step({},1.f/30);
    check(wall.projectiles.empty(),"extended acceleration retains physical scenery collision");
    auto owner=fixture();const auto id=owner.spawnMonster(monsterId(10),{-20,.85f,0});shot(owner,0,.9f);
    owner.projectiles[0].sourcePlanarMotion->accelerationRampFrames=20;owner.projectiles[0].context.sourceEntity=id;
    Event death;death.type=EventType::Damage;death.target=id;death.damage=10000;owner.queueRoot(death);owner.drainEvents();
    for(int n=0;n<40;++n)owner.step({},1.f/30);
    check(owner.projectiles.size()==1&&owner.projectiles[0].context.sourceEntity==id&&near(owner.projectiles[0].velocity.x,velocity),
        "ramped death projectile retains age and attribution after source removal");
    std::cout<<"EXTENDED_ACCELERATION native_ramp20=1 first_age1=1 saturation=1 cadence=1 vertical=1 scenery=1 owner_death=1\n";
}
void physicalBehavior() {
    auto orbit=fixture(),straight=fixture();
    for(auto *s:{&orbit,&straight}) {s->arena.obstacles.push_back({{.25f,0,-3},{.3f,3,3}});s->arena.rebuildWalls();}
    shot(orbit,1);shot(straight,0,.97f);orbit.step({},Tick);straight.step({},Tick);
    check(orbit.projectiles.size()==1&&straight.projectiles.empty(),"native orbit ignores walls; decelerating stream still hits them");
    auto ground=fixture();shot(ground,1);ground.projectiles[0].gravity=30;ground.projectiles[0].velocity.y=-3;
    for(int n=0;n<30;++n)ground.step({});check(ground.projectiles.empty(),"wall-passing orbit still lands on ground");
    auto hit=fixture();hit.godMode=false;shot(hit,1);hit.player.position={.7f,.85f,0};hit.step({});
    check(hit.player.hp<StartingHealth&&hit.projectiles.empty(),"orbit hits player before turning");
    auto owner=fixture();const auto id=owner.spawnMonster(monsterId(10),{-20,.85f,0});shot(owner,1);
    owner.projectiles[0].context.sourceEntity=id;owner.projectiles[0].sourcePlanarMotion->orbitCenter={0,.85f,0};
    Event death;death.type=EventType::Damage;death.target=id;death.damage=10000;owner.queueRoot(death);owner.drainEvents();
    for(int n=0;n<12;++n)owner.step({});
    check(owner.projectiles.size()==1&&owner.projectiles[0].context.sourceEntity==id&&
        near(owner.projectiles[0].sourcePlanarMotion->orbitCenter.x,0),"death/removal retains projectile origin and attribution");
    std::cout<<"PHYSICAL walls=1 ground=1 player=1 survives_owner=1\n";
}
}
int main(){try{recurrence();acceleration();extendedAcceleration();physicalBehavior();std::cout<<"PASS source projectile motion\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
