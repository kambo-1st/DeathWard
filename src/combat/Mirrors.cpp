#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateMirror(Enemy &e,float dt) {
    const auto &p=*content->mirror(e.monster);
    if(!e.mirror)e.mirror=MirrorRuntime{};
    auto &r=*e.mirror;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    // Native target assignment offers each player to only one type53 actor,
    // across both variants. DeathWard currently has one playable character.
    for(const auto &other:enemies)if(other.alive&&other.id<e.id&&content->mirror(other.monster)) {
        e.alive=false;e.velocity={};return; // Removal, not a paid combat kill.
    }
    if(e.state==EnemyState::Stunned) {
        e.velocity={};r.clock=0;r.observedDelay=int(player.fireCooldown*30);
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    const auto &layout=arena.rooms[size_t(room)];
    const auto &bounds=layout.bounds;const auto *d=content->monster(e.monster);
    const auto legal=[&](Vector3 point) {
        return point.x>=bounds.min.x+e.radius&&point.x<=bounds.max.x-e.radius&&
            point.z>=bounds.min.z+e.radius&&point.z<=bounds.max.z-e.radius&&
            !(d->flying?arena.flightBlocked(point,e.radius,room):arena.blocked(point,e.radius));
    };
    if(r.initialized) {
        r.desired={2*layout.center.x-player.position.x,.85f,2*layout.center.z-player.position.z};
        auto at=r.desired;
        at.x=std::clamp(at.x,bounds.min.x+e.radius,bounds.max.x-e.radius);
        at.z=std::clamp(at.z,bounds.min.z+e.radius,bounds.max.z-e.radius);
        // The native controller assigns the reflected position directly, then
        // the grid resolves collisions. Canyon terrain is not symmetric: use
        // the nearest sampled legal footprint instead of embedding the actor.
        if(!legal(at)) {
            bool found=false;
            for(int ring=1;ring<=16&&!found;++ring)for(int n=0;n<16;++n) {
                const auto candidate=add(at,rotateY({float(ring)*.5f,0,0},float(n)*Pi/8));
                if(legal(candidate)){at=candidate;found=true;break;}
            }
            if(!found)at=e.position;
            ++r.terrainCorrections;
        }
        if(legal(at))e.position=at;
        if(d->flying)e.position.y=arena.flightHeight(e.position,e.radius);
        e.velocity=mul(horizontal(player.velocity),-p.movementMultiplier);
        auto aim=horizontal(sub(player.aim,player.position));
        // Isaac's cardinal shooting is retained when mouse aim is continuous.
        e.facing=std::abs(aim.x)>std::abs(aim.z)?Vector3{aim.x>0?-1.f:1.f,0,0}:Vector3{0,0,aim.z>0?-1.f:1.f};
        e.target=add(e.position,mul(e.facing,10));
    }
    const auto emit=[&] {
        if(!r.pending)return true;
        const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
        if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+size_t(p.shots)>limits.queuedEvents||
            projectiles.size()+size_t(queued+p.shots)>limits.projectiles)return false;
        for(int n=0;n<p.shots;++n) {
            auto velocity=r.shotVelocity;
            if(n)velocity=mul(add(mul(velocity,p.sideForward),
                mul(Vector3{-velocity.z,0,velocity.x},p.sideCross*(n==1?1.f:-1.f))),p.sideMultiplier);
            if(p.shots==3)velocity=add(mul(velocity,p.spreadVelocity),mul(r.inheritedVelocity,p.spreadInheritance));
            velocity.y=p.up;
            Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
            shot.position=shot.origin=r.shotOrigin;shot.direction=unit(velocity);shot.speed=length(velocity);
            shot.damage=p.damage;shot.projectileLife=p.life;shot.projectileRadius=p.radius;
            shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.retention;queueRoot(shot);
        }
        r.pending=false;++r.volleys;r.shootFrame=3;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
    };
    emit();r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        if(!r.initialized){r.initialized=true;e.velocity={};continue;}
        if(r.cooldown>0)--r.cooldown;
        if(r.shootFrame>0)--r.shootFrame;
        // Source watches integer weapon delay increase, not the number of
        // pellets or child shots. This also preserves its high-rate aliasing.
        const int delay=int(std::max(0.f,player.fireCooldown)*30);
        if(delay>r.observedDelay&&r.cooldown==0&&!r.pending) {
            auto inherited=mul(e.velocity,p.inheritance);
            const float along=dot(inherited,e.facing);
            if(along<0)inherited=sub(inherited,mul(e.facing,along));
            r.shotVelocity=add(mul(e.facing,p.speed),inherited);
            r.inheritedVelocity=e.velocity;r.shotOrigin=e.position;
            if(p.eyeMin+p.eyeExtra>0) {
                const float offset=(p.eyeMin+combatRng.real(0,p.eyeExtra))*float(r.eye)/30;
                const auto candidate=sub(e.position,{r.shotVelocity.z*offset,0,r.shotVelocity.x*offset});
                if(arena.clear(e.position,candidate,p.radius))r.shotOrigin=candidate;
                r.eye=-r.eye;
            }
            r.shotOrigin.y+=p.height-.85f;r.pending=true;r.cooldown=p.cooldownFrames;emit();
        }
        r.observedDelay=delay;
    }
    e.cooldown=float(r.cooldown)/30;
}
} // namespace dw
