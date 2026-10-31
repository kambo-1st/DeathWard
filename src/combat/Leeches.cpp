#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateLeech(Enemy &e,float dt) {
    const auto &p=*content->leech(e.monster);
    if(!e.leech)e.leech=LeechRuntime{};
    auto &r=*e.leech;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const auto stop=[&] {
        if(r.charging)++r.stops;
        r.charging=false;r.blocked=false;r.hasDestination=false;r.chargeStuckTicks=0;
        r.chargeDirection={};r.walkFrame=0;e.state=EnemyState::Ready;
    };
    if(e.state==EnemyState::Stunned) {
        stop();e.state=EnemyState::Stunned;r.clock=0;r.momentum={};e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    const auto cellCenter=[&] {
        const auto origin=arena.rooms[size_t(room)].center;const float grid=p.grid*p.scale;
        auto center=e.position;center.x=origin.x+std::round((center.x-origin.x)/grid)*grid;
        center.z=origin.z+std::round((center.z-origin.z)/grid)*grid;
        return arena.flightBlocked(center,e.radius,room)?e.position:center;
    };
    // Repentance Leeches ignore knockback. Only this controller and actual
    // flight collisions change their momentum, not an external velocity kick.
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        if(!r.initialized){r.initialized=true;r.lastPosition=e.position;continue;}
        faceAxisWander(e,r);
        if(r.charging) {
            if(planarDistance(e.position,r.lastPosition)<p.chargeStuckDistance*p.scale)++r.chargeStuckTicks;
            else r.chargeStuckTicks=0;
            r.lastPosition=e.position;
            if(r.blocked||r.chargeStuckTicks>p.chargeStuckFrames)stop();
            else {
                // Native AddVelocity divides by friction; the base movement
                // applies that friction after the cross-axis grid correction.
                r.momentum=add(r.momentum,mul(r.chargeDirection,1/p.chargeRetention));
                const auto grid=cellCenter();
                if(std::abs(r.chargeDirection.z)>std::abs(r.chargeDirection.x))
                    r.momentum.x+=((grid.x-e.position.x)/p.scale-r.momentum.x)*p.gridPull;
                else r.momentum.z+=((grid.z-e.position.z)/p.scale-r.momentum.z)*p.gridPull;
                r.momentum=mul(r.momentum,p.chargeRetention);
                r.walkFrame=(r.walkFrame+1)%p.dashFrames;
            }
        } else {
            stepAxisWander(e,p,r);
            r.momentum.z*=p.zRetention;r.momentum=mul(r.momentum,p.retention);
            r.walkFrame=(r.walkFrame+1)%p.walkFrames;
            const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+1e-4)));
            if((globalTick+e.id)%uint64_t(p.checkFrames)==0) {
                auto target=add(player.position,mul(player.velocity,combatRng.real(0,p.prediction)/30));
                const auto &bounds=arena.rooms[size_t(room)].bounds;const float margin=p.alignment*p.scale;
                if(bounds.max.x-bounds.min.x>2*margin&&bounds.max.z-bounds.min.z>2*margin) {
                    target.x=std::clamp(target.x,bounds.min.x+margin,bounds.max.x-margin);
                    target.z=std::clamp(target.z,bounds.min.z+margin,bounds.max.z-margin);
                }
                r.predictedTarget=target;const auto grid=cellCenter(),delta=horizontal(sub(target,grid));
                // Walls-only sight, no maximum charge range and no turn after
                // acquisition. Native alignment is cardinal but the committed
                // direction retains a small angle toward the predicted target.
                if(length(delta)>.0001f&&std::min(std::abs(delta.x),std::abs(delta.z))<margin&&
                    arena.flightClear(grid,target,0,room)) {
                    r.chargeDirection=mul(unit(delta),p.chargeForce);r.charging=true;r.blocked=false;
                    r.lastPosition=e.position;r.chargeStuckTicks=0;r.walkFrame=0;
                    ++r.charges;e.state=EnemyState::Charging;
                }
            }
        }
    }
    const auto wanted=mul(r.momentum,p.scale*30),before=e.position;
    moveMonster(e,wanted,dt);
    if(length(sub(horizontal(e.velocity),wanted))>.05f&&
        !arena.flightClear(before,add(before,mul(wanted,dt)),e.radius,room)) {
        r.blocked=true;r.hasDestination=false;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    e.target=r.charging?r.predictedTarget:r.hasDestination?r.destination:e.position;
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
