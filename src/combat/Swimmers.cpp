#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::planThrownOffspring(ThrownOffspringRuntime &r,Vector3 target,float radius,bool overPits) const {
    r.clock=0;r.frames=0;r.height=r.profile.initialHeight;r.verticalVelocity=r.profile.initialVelocity;
    r.step=mul(horizontal(sub(target,r.origin)),r.profile.planar);
    auto p=r.origin;p.y=.85f-r.height*r.profile.heightScale;
    float height=r.height,velocity=r.verticalVelocity;
    for(int frame=1;frame<=256;++frame) {
        velocity+=r.profile.gravity;height+=velocity;
        const bool landed=height>-velocity;
        auto next=add(p,r.step);next.y=landed?.85f:.85f-height*r.profile.heightScale;
        // Source walls-only airborne collision is adapted to actual 3D cover:
        // a birth may fly over a rock/pit, but may not pass through its mesh.
        if(!arena.flightClear(p,next,radius,room)||arena.trace(p,next,radius).hit)return false;
        p=next;
        if(landed) {
            if((overPits?arena.swimBlocked(p,radius,room):arena.blocked(p,radius))||arena.reservedSupplyCache(p,radius))return false;
            r.duration=frame;return true;
        }
    }
    return false;
}
void Simulation::updateThrownOffspring(Enemy &e,float dt) {
    if(e.state==EnemyState::Stunned){e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;}
    auto &r=*e.thrownOffspring;r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        r.verticalVelocity+=r.profile.gravity;r.height+=r.verticalVelocity;++r.frames;
        const bool landed=r.frames>=r.duration;
        auto next=add(e.position,r.step);next.y=landed?.85f:.85f-r.height*r.profile.heightScale;
        // The entire arc and endpoint were checked before admission. Dynamic
        // actors do not collide with this source entity-collision-zero state.
        e.velocity=mul(sub(next,e.position),30);e.position=next;
        if(length(r.step)>.0001f)e.facing=unit(r.step);
        if(landed) {
            e.thrownOffspring.reset();e.velocity={};e.lift=0;
            if(content->swimmer(e.monster))e.swimmer=SwimmerRuntime{};
            if(content->spider(e.monster))e.spider=SpiderRuntime{};
            if(content->strider(e.monster))e.strider=StriderRuntime{};
            return;
        }
    }
}
void Simulation::updateSwimmer(Enemy &e,float dt) {
    const auto &p=*content->swimmer(e.monster);
    if(!e.swimmer)e.swimmer=SwimmerRuntime{};
    auto &r=*e.swimmer;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.thrownOffspring) {
        updateThrownOffspring(e,dt);return;
    }
    r.swimming=arena.swimmingRoom(room);
    // Read actual body velocity so collision separation and knockback are not
    // overwritten by a private, stale movement accumulator.
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.hopFrame=-1;r.momentum={};e.velocity={};e.lift=0;e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(r.hopFrame>=0) {
            ++r.hopFrame;
            if(r.hopFrame>=p.landFrame)r.momentum=mul(r.momentum,p.groundRetention);
            if(r.hopFrame>=p.hopFrames)r.hopFrame=-1;
        } else if(r.swimming) {
            r.acceleration=std::min(p.maximumAcceleration,r.acceleration+p.acceleration);
            r.momentum=mul(add(r.momentum,mul(unit(horizontal(sub(player.position,e.position))),r.acceleration)),p.retention);
            const auto &bounds=arena.rooms.at(size_t(room)).bounds;
            const auto next=add(e.position,mul(r.momentum,p.scale));
            const float marginX=std::max(e.radius,p.marginX*p.scale);
            if((r.momentum.x<0&&next.x<bounds.min.x+marginX)||(r.momentum.x>0&&next.x>bounds.max.x-marginX))r.momentum.x*=p.bounce;
            if((r.momentum.z<0&&next.z<bounds.min.z+std::max(e.radius,p.marginTop*p.scale))||
               (r.momentum.z>0&&next.z>bounds.max.z-std::max(e.radius,p.marginBottom*p.scale)))r.momentum.z*=p.bounce;
        } else {
            r.momentum=mul(r.momentum,p.groundRetention);
            if(combatRng.bounded(unsigned(p.hopChance))==0) {
                r.momentum=add(r.momentum,mul(unit(horizontal(sub(player.position,e.position))),combatRng.real(p.hopMinimum,p.hopMaximum)));
                r.hopFrame=0;
            }
        }
        if(length(r.momentum)>p.speedCap)r.momentum=mul(unit(r.momentum),p.speedCap);
    }
    // The source dry hop is an animation with ground collision; retain that
    // collision policy and a small Original-style visual lift until Land.
    e.lift=r.hopFrame>=0&&r.hopFrame<p.landFrame?p.hopHeight*std::sin(Pi*float(r.hopFrame)/float(p.landFrame)):0;
    const auto velocity=mul(r.momentum,p.scale*30);
    moveMonster(e,steerMonsterBodies(e,velocity),dt);
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
    }
}
} // namespace dw
