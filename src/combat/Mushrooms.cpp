#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateMushroom(Enemy &e,float dt) {
    const auto &p=*content->mushroom(e.monster);
    if(!e.mushroom)e.mushroom=MushroomRuntime{};
    auto &r=*e.mushroom;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    e.velocity={};
    if(!r.initialized){r.initialized=true;r.anchor=e.position;r.timer=p.timerQuantum*(1+int(combatRng.bounded(unsigned(p.blockingChoices))));}
    // Native velocity restores the original location every update. Keep the
    // stationary body anchored; no hidden pursuit or target-facing rotation.
    e.position=r.anchor;
    if(e.state==EnemyState::Stunned) {
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;
        return; // Local stun pauses the cycle; native petrification is separate.
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        switch(r.phase) {
        case MushroomPhase::InitialHide:
            if(++r.frame>=p.hideFrames){r.phase=MushroomPhase::Blocking;r.frame=0;}
            break;
        case MushroomPhase::Blocking:
            if(--r.timer<=0) {
                r.phase=MushroomPhase::Reveal;r.frame=0;r.fired=false;
                r.diagonal=combatRng.bounded(2)!=0;
                audioCues.push(AudioCueKind::Warning,e.position);
            }
            break;
        case MushroomPhase::Reveal:
            if(r.frame<p.shootFrame||r.fired)++r.frame;
            r.opening=std::min(1.f,float(r.frame)/float(p.revealFrames));
            if(r.frame==p.shootFrame&&!r.fired) {
                const auto pending=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
                // One native event creates all four. Retain its orientation
                // and frame under pressure instead of firing a partial cross.
                if(limits.eventsPerChain&&queue_.size()+4<=limits.queuedEvents&&projectiles.size()+size_t(pending)+4<=limits.projectiles) {
                    const std::array<Vector3,4> directions=r.diagonal?
                        std::array<Vector3,4>{{{p.diagonal,0,p.diagonal},{-p.diagonal,0,p.diagonal},{p.diagonal,0,-p.diagonal},{-p.diagonal,0,-p.diagonal}}}:
                        std::array<Vector3,4>{{{1,0,0},{-1,0,0},{0,0,1},{0,0,-1}}};
                    for(auto direction:directions) {
                        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;shot.position=shot.origin=e.position;
                        const auto velocity=mul(direction,p.speed);shot.direction=unit(velocity);shot.speed=length(velocity);
                        shot.damage=p.damage;shot.projectileLife=p.life;queueRoot(shot);
                    }
                    r.fired=true;audioCues.push(AudioCueKind::MonsterAttack,e.position);
                }
            }
            if(r.frame>=p.revealFrames) {
                r.phase=MushroomPhase::Revealed;r.frame=0;r.opening=1;
                r.timer=p.timerQuantum*(1+int(combatRng.bounded(unsigned(p.revealedChoices))));
            }
            break;
        case MushroomPhase::Revealed:
            if(--r.timer<=0){r.phase=MushroomPhase::Hide;r.frame=0;audioCues.push(AudioCueKind::MonsterAttack,e.position);}
            break;
        case MushroomPhase::Hide:
            r.opening=std::max(0.f,1-float(++r.frame)/float(p.hideFrames));
            // Source remains in state16 (full damage) until Hide finishes.
            if(r.frame>=p.hideFrames) {
                r.phase=MushroomPhase::Blocking;r.frame=0;
                r.timer=p.timerQuantum*(1+int(combatRng.bounded(unsigned(p.blockingChoices))));
            }
            break;
        }
    }
    e.state=r.blocking()?EnemyState::Ready:r.phase==MushroomPhase::Reveal?EnemyState::Windup:EnemyState::Exposed;
    e.stateTime=r.phase==MushroomPhase::Reveal?float(p.revealFrames-r.frame)/30:0;e.cooldown=float(r.timer)/30;
    if(p.contact>0&&segmentSphere(sub(e.position,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
        arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
