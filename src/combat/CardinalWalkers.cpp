#include "combat/Simulation.hpp"

namespace dw {
int Simulation::faceAxisWander(Enemy &e,AxisWanderRuntime &r) {
    const int axis=std::abs(r.momentum.x)>std::abs(r.momentum.z)?0:r.momentum.z<0?1:2;
    if(axis!=r.walkAxis){r.walkAxis=axis;r.walkFrame=0;}
    e.facing=axis==0?Vector3{r.momentum.x<0?-1.f:1.f,0,0}:Vector3{0,0,axis==1?-1.f:1.f};
    return axis;
}
void Simulation::stepAxisWander(Enemy &e,const AxisWanderDefinition &p,AxisWanderRuntime &r) {
    const auto chooseDestination=[&] {
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        const float margin=e.radius+.1f;
        const std::array<Vector3,4> axes{{{-1,0,0},{0,0,-1},{1,0,0},{0,0,1}}};
        // Source cardinal random grid paths become radius-aware rays through the
        // actual canyon. Bound retries; clip before cliffs, water, gates and props.
        for(int attempt=0;attempt<p.attempts;++attempt) {
            const int first=int(combatRng.bounded(4));
            for(int axis=0;axis<4;++axis) {
                const int cells=int(combatRng.bounded(unsigned(p.maxCells+1)));if(!cells)continue;
                auto target=add(e.position,mul(axes[size_t((first+axis)%4)],float(cells)*p.grid*p.scale));
                target.x=std::clamp(target.x,bounds.min.x+margin,bounds.max.x-margin);
                target.z=std::clamp(target.z,bounds.min.z+margin,bounds.max.z-margin);
                const auto delta=horizontal(sub(target,e.position));const float range=length(delta);
                if(range<p.arrival*p.scale)continue;
                auto safe=e.position;const int steps=std::max(1,int(std::ceil(range/(p.grid*p.scale*.25f))));
                for(int n=1;n<=steps;++n) {
                    const auto point=add(e.position,mul(delta,float(n)/float(steps)));
                    const auto *definition=content->monster(e.monster);
                    if(definition&&definition->flying?!arena.flightClear(safe,point,e.radius,room):!arena.clear(safe,point,e.radius))break;
                    safe=point;
                }
                if(planarDistance(safe,e.position)<p.arrival*p.scale)continue;
                r.destination=safe;r.hasDestination=true;r.stuckTicks=0;return;
            }
        }
    };
    if(!r.hasDestination)chooseDestination();
    if(r.hasDestination) {
        const auto delta=horizontal(sub(r.destination,add(e.position,mul(r.momentum,p.scale))));
        if(length(delta)<p.arrival*p.scale)r.hasDestination=false;
        else if(length(r.momentum)<p.stuckSpeed&&++r.stuckTicks>p.stuckFrames)r.hasDestination=false;
        r.momentum=add(r.momentum,mul(unit(delta),p.force));
    }
}
void Simulation::moveAxisWander(Enemy &e,const AxisWanderDefinition &p,AxisWanderRuntime &r,float dt) {
    const auto wanted=mul(r.momentum,p.scale*30);const auto before=e.position;
    moveMonster(e,wanted,dt);e.target=r.hasDestination?r.destination:e.position;
    if(length(wanted)>.1f&&distance(before,e.position)<length(wanted)*dt*.25f)r.hasDestination=false;
}
void Simulation::updateCardinalWalker(Enemy &e,float dt) {
    const auto &p=*content->cardinalWalker(e.monster);
    if(!e.cardinalWalker)e.cardinalWalker=AxisWanderRuntime{};
    auto &r=*e.cardinalWalker;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.walkFrame=0;r.walkAxis=-1;r.momentum={};e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        const int axis=faceAxisWander(e,r);
        stepAxisWander(e,p,r);
        r.walkFrame=(r.walkFrame+1)%(axis==0?p.horizontalFrames:p.verticalFrames);
        r.momentum.z*=p.zRetention;r.momentum=mul(r.momentum,p.retention);
    }
    moveAxisWander(e,p,r,dt);
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
