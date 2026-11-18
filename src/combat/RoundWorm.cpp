#include "combat/Simulation.hpp"
#include "world/SourceHeartRockRoom.hpp"

namespace dw {
bool Simulation::roundWormDestinationClear(const Enemy &e,Vector3 point) const {
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    if(point.x-e.radius<bounds.min.x||point.x+e.radius>bounds.max.x||
       point.z-e.radius<bounds.min.z||point.z+e.radius>bounds.max.z||
       arena.roomAt(point)!=room||arena.blocked(point,e.radius))return false;
    if(planarDistance(point,player.position)<e.radius+.48f)return false;
    for(const auto &other:enemies)if(other.alive&&other.id!=e.id&&
        other.state!=EnemyState::Buried&&planarDistance(point,other.position)<e.radius+other.radius)return false;
    return true;
}

bool Simulation::shootRoundWorm(Enemy &e) {
    auto &r=*e.roundWorm;
    if(!r.pending) {
        // Native lead is ten player steps, not ten seconds. Canyon collision
        // clips the lead, using the retained physical geometry rather than a
        // source rectangular wall/grid query.
        auto target=player.position;
        auto lead=roundWormLead(mul(horizontal(player.velocity),1.f/60));
        if(length(lead)>10*GaperMovementScale) {
            const float desired=length(lead),margin=8*GaperMovementScale;
            const auto direction=unit(lead);float available=desired;
            for(float d=0;d<=desired+margin;d+=.025f) {
                if(arena.blocked(add(target,mul(direction,d)),.02f)){available=std::max(0.f,d-margin);break;}
            }
            lead=mul(direction,std::min(desired,available));
        }
        target=add(target,lead);
        const auto &b=arena.rooms[size_t(room)].bounds;const float margin=20*GaperMovementScale;
        target.x=std::clamp(target.x,b.min.x+margin,b.max.x-margin);
        target.z=std::clamp(target.z,b.min.z+margin,b.max.z-margin);
        if(!arena.sight(e.position,target))return true; // Native blocked shot is skipped, not deferred.
        r.shotOrigin=e.position;
        r.shotVelocity=mul(roundWormShot(sub(target,e.position)),GaperMovementScale*30*r.shotSpeed);
        if(length(r.shotVelocity)<.001f)return true;
        r.pending=true;
    }
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const Event &v){return v.type==EventType::Shot;});
    if(queue_.size()>=limits.queuedEvents||projectiles.size()+size_t(queued)>=limits.projectiles)return false;
    Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;shot.position=shot.origin=r.shotOrigin;
    shot.direction=unit(r.shotVelocity);shot.speed=length(r.shotVelocity);shot.damage=10;
    shot.pooterFlight=true;
    if(!queueRoot(shot))return false;
    r.pending=false;++r.shots;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

void Simulation::updateRoundWorm(Enemy &e,float dt) {
    auto &r=*e.roundWorm;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    e.velocity={};
    if(e.state==EnemyState::Stunned) {
        r.clock=0;e.stateTime-=dt;
        if(e.stateTime<=0)e.state=r.phase==RoundWormPhase::Hidden?EnemyState::Buried:EnemyState::Ready;
        return;
    }
    if(!r.initialized){r.initialized=true;r.cycleSpeed=roundWormTuning.cycleSpeed;r.shotSpeed=roundWormTuning.shotSpeed;}
    auto begin=[&](RoundWormPhase phase) {
        r.phase=phase;r.frame=0;r.cycleSpeed=roundWormTuning.cycleSpeed;
        if(phase==RoundWormPhase::DigOut){r.shotSpeed=roundWormTuning.shotSpeed;r.fired=false;}
    };
    // Explicit 30Hz adapter, with phase settings snapshotted at admission.
    // Native RNG, factory Appear and the complete animation wrapper are not
    // claimed identical to this production scheduler.
    r.clock+=dt;
    while(r.clock+1e-7>=1./30) {
        r.clock=std::max(0.,r.clock-1./30);
        if(r.phase==RoundWormPhase::Hidden) {
            const auto &layout=arena.rooms[size_t(room)];
            // Placement follows the room's source-cell adapter. Reusing the
            // fixed movement scale here can make the native1000-unit upper
            // gate unreachable from the entrance of a resized canyon room.
            const float placementScale=sourceHeartCellSize(layout)/40;
            const float angle=combatRng.real(0,2*Pi),radius=(60+combatRng.real(0,250))*placementScale;
            auto point=add(layout.center,{std::cos(angle)*radius,0,std::sin(angle)*radius});point.y=.85f;
            const auto &b=layout.bounds;const float margin=std::max(e.radius,20*placementScale);
            point.x=std::clamp(point.x,b.min.x+margin,b.max.x-margin);
            point.z=std::clamp(point.z,b.min.z+margin,b.max.z-margin);
            const auto delta=mul(horizontal(sub(point,player.position)),1/placementScale);
            const auto parity=combatRng.bounded(2);
            if(roundWormRelocation(dot(delta,delta),parity)&&roundWormDestinationClear(e,point)) {
                e.position=point;++r.relocations;begin(RoundWormPhase::DigOut);
                audioCues.push(AudioCueKind::Warning,point);
            }
        } else if(r.phase==RoundWormPhase::DigIn) {
            r.frame+=r.cycleSpeed;
            if(r.frame>=17){begin(RoundWormPhase::Hidden);++r.burrows;}
        } else {
            // A capacity-delayed attack retains its origin/velocity and holds
            // the Shoot event until admission. No duplicate or lost attack.
            if(!r.pending)r.frame+=r.cycleSpeed;
            if(r.frame>=38&&!r.fired)r.fired=shootRoundWorm(e);
            if(r.frame>=61&&r.fired)begin(RoundWormPhase::DigIn);
        }
        e.state=r.phase==RoundWormPhase::Hidden?EnemyState::Buried:EnemyState::Ready;
    }
    e.facing=unit(horizontal(sub(player.position,e.position)));e.target=player.position;
    if(r.phase!=RoundWormPhase::Hidden&&planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(10,source);
    }
}
} // namespace dw
