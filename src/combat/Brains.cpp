#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateBrain(Enemy &e,float dt) {
    const auto &p=*content->brain(e.monster);
    if(!e.brain)e.brain=BrainRuntime{};
    auto &r=*e.brain;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const auto stop=[&] {
        if(r.charging)++r.stops;
        r.charging=false;r.blocked=false;r.hasDestination=false;r.chargeDirection={};e.state=EnemyState::Ready;
    };
    if(e.state==EnemyState::Stunned) {
        if(r.charging)++r.stops;
        r.charging=false;r.blocked=false;r.hasDestination=false;r.chargeDirection={};
        r.clock=0;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    const auto emitCreep=[&] {
        if(!r.pendingCreep)return true;
        if(hazards.size()>=limits.hazards)return false;
        Hazard h;h.kind=HazardKind::Creep;h.position=h.origin=*r.pendingCreep;
        h.position.y=.85f;h.radius=p.creepRadius;h.damage=p.creepDamage;h.delay=0;
        h.duration=float(p.creepFrames)/30;h.fadeDuration=float(p.fadeFrames)/30;h.fadeScale=p.fadeScale;
        h.fadeOnRoomClear=true;h.tint={142,47,52,195};h.context.sourceEntity=e.id;
        addHazard(h);r.pendingCreep.reset();++r.creepPatches;return true;
    };
    // Retain one due emission under local capacity pressure. Pause subsequent
    // source decisions rather than silently discarding trail or growing a queue.
    const bool wasPending=r.pendingCreep.has_value();
    if(!emitCreep()){e.velocity={};return;}
    if(wasPending)e.velocity=mul(r.momentum,p.scale*30);
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    const auto cellCenter=[&] {
        const float grid=p.grid*p.scale;
        const auto origin=arena.rooms[size_t(room)].center;
        auto center=e.position;
        center.x=origin.x+std::round((e.position.x-origin.x)/grid)*grid;
        center.z=origin.z+std::round((e.position.z-origin.z)/grid)*grid;
        // Arbitrary canyon geometry has no guaranteed empty native grid cell.
        return arena.blocked(center,e.radius)?e.position:center;
    };
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        if(!r.initialized){r.initialized=true;continue;}
        r.walkFrame=(r.walkFrame+1)%p.walkFrames;
        r.walkPhase=float(r.walkFrame)/float(p.walkFrames);
        if(p.pursuit) {
            stepGroundPursuit(e,*p.pursuit,r.momentum,r.destination,p.pursuit->force);
            r.hasDestination=true;
        } else if(r.charging) {
            if(r.blocked)stop();
            else {
                r.momentum=add(mul(r.momentum,p.chargeRetention),r.chargeDirection);
                const auto grid=cellCenter();auto correction=Vector3{};
                if(std::abs(r.momentum.x)>std::abs(r.momentum.z))correction.z=(grid.z-e.position.z)*p.gridPull;
                else correction.x=(grid.x-e.position.x)*p.gridPull;
                const auto goal=add(e.position,correction);
                if(arena.clear(e.position,goal,e.radius))e.position=goal;
                else stop();
            }
        } else {
            stepAxisWander(e,p,r);
            r.momentum.x*=p.retention;r.momentum.z*=p.verticalRetention;
            const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+1e-4)));
            // Stable entity IDs provide the native per-entity stagger; the
            // source's global interval remains separate from actor trail time.
            if((globalTick+e.id)%uint64_t(p.chargeInterval)==0) {
                auto target=add(player.position,mul(player.velocity,combatRng.real(0,p.prediction)/30));
                const float margin=p.alignment*p.scale;
                if(bounds.max.x-bounds.min.x>2*margin&&bounds.max.z-bounds.min.z>2*margin) {
                    target.x=std::clamp(target.x,bounds.min.x+margin,bounds.max.x-margin);
                    target.z=std::clamp(target.z,bounds.min.z+margin,bounds.max.z-margin);
                }
                r.predictedTarget=target;
                const auto grid=cellCenter(),delta=horizontal(sub(target,grid));
                if(std::min(std::abs(delta.x),std::abs(delta.z))<p.alignment*p.scale&&
                    length(delta)<p.range*p.scale&&arena.sight(grid,target)) {
                    r.chargeDirection=std::abs(delta.x)>std::abs(delta.z)?
                        Vector3{delta.x<0?-1.f:1.f,0,0}:Vector3{0,0,delta.z<0?-1.f:1.f};
                    r.charging=true;r.blocked=false;++r.charges;e.state=EnemyState::Charging;
                }
            }
        }
        if(p.pursuit&&length(r.momentum)>.01f)e.facing=unit(r.momentum);
        else if(r.charging)e.facing=r.chargeDirection;
        else if(length(r.momentum)>.01f)e.facing=std::abs(r.momentum.x)>std::abs(r.momentum.z)?
            Vector3{r.momentum.x<0?-1.f:1.f,0,0}:Vector3{0,0,r.momentum.z<0?-1.f:1.f};
        const int count=int(std::count_if(enemies.begin(),enemies.end(),[&](const auto &body) {
            const auto *d=content->monster(body.monster);
            return body.alive&&!body.dyingEggy()&&body.friendly==e.friendly&&(!d||!d->roomHazard);
        }));
        const auto interval=uint64_t(count<p.crowdThreshold?p.denseInterval:p.sparseInterval);
        const auto phase=(r.ticks+e.id%interval)%interval;
        if(phase==0||(phase==interval/2&&length(r.momentum)>p.extraCreepSpeed)) {
            r.pendingCreep=e.position;
            if(!emitCreep()){r.clock=0;e.velocity={};return;}
        }
    }
    const auto velocity=mul(r.momentum,p.scale*30);
    if(r.charging&&!arena.clear(e.position,add(e.position,mul(velocity,dt)),e.radius))r.blocked=true;
    moveMonster(e,p.pursuit?steerMonsterBodies(e,velocity):velocity,dt);e.target=r.charging?r.predictedTarget:r.hasDestination?r.destination:e.position;
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
