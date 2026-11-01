#include "combat/Simulation.hpp"
#include "combat/SourceTime.hpp"

namespace dw {
bool Simulation::flushHeadlessShot(Enemy &e) {
    if(!e.headless||e.headless->pendingShots.empty())return true;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &x){return x.alive;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()>=limits.queuedEvents||size_t(live+queued)>=limits.projectiles)return false;
    queueRoot(e.headless->pendingShots.front());e.headless->pendingShots.clear();return true;
}

void Simulation::updateHeadless(Enemy &e,float dt) {
    const auto &p=*content->headless(e.monster);
    if(!e.headless)e.headless=HeadlessRuntime{}; // Includes actual decapitation offspring.
    auto &r=*e.headless;
    const float timeScale=enemyTimeScale(e);
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const bool pending=!r.pendingShots.empty();
    if(!flushHeadlessShot(e)){e.velocity={};return;}
    if(pending)e.velocity=mul(r.momentum,p.scale*30);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;r.animationTicks+=advanceSourceFrames(r.animationFraction,timeScale);
            const int elapsedFrames=advanceSourceFrames(r.timerFraction,timeScale);
            if(!r.initialized) {
                r.initialized=true;
                r.cooldown=p.initialMin+int(combatRng.bounded(unsigned(p.initialMax-p.initialMin+1)));
            } else {
                // The source fires before movement/friction. No target, range,
                // line-of-sight gate, windup, or artificial aim at zero velocity.
                if(p.shooter) {
                    const float speed=length(r.momentum);
                    if(r.cooldown>0||(e.affectedBy(EnemyStatus::Fear)||e.affectedBy(EnemyStatus::Shrink))||e.affectedBy(EnemyStatus::Confusion))
                        r.cooldown=std::max(-18000,r.cooldown-elapsedFrames);
                    else if(speed>0) {
                        const auto velocity=add(mul(r.momentum,p.shotSpeed/speed),{0,p.shotUp,0});
                        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
                        shot.position=shot.origin=add(e.position,{0,p.shotHeight-.85f,0});
                        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shotDamage;
                        shot.projectileRadius=p.shotRadius;shot.projectileLife=p.shotLife;
                        shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.shotRetention;
                        shot.projectileTimeScale=enemyShotTimeScale(e);
                        setEnemyShotAffiliation(e,shot);
                        r.pendingShots.push_back(shot);++r.shots;
                        r.cooldown=p.reloadMin+int(combatRng.bounded(unsigned(p.reloadMax-p.reloadMin+1)));
                        audioCues.push(AudioCueKind::MonsterAttack,e.position);flushHeadlessShot(e);
                    }
                }
                const float priorSpeedSquared=dot(r.momentum,r.momentum);
                const auto before=r.momentum;
                // Source reduces friction before MoveRandomly; the helper's
                // force/friction division cancels friction on the new impulse.
                const bool afraid=(e.affectedBy(EnemyStatus::Fear)||e.affectedBy(EnemyStatus::Shrink));
                if(afraid)stepFearMotion(e,r.momentum);
                else r.momentum=mul(r.momentum,p.retention);
                if(!afraid&&!e.railCarrier) {
                    if(!r.targetReady) {
                        const auto at=add(e.position,mul(rotateY({1,0,0},combatRng.real(0,2*Pi)),p.wanderDistance*p.scale));
                        if(!arena.blocked(at,e.radius)){r.destination=at;r.targetReady=true;}
                    }
                    if(r.targetReady) {
                        const auto delta=horizontal(sub(r.destination,e.position));
                        if(length(delta)<p.arrival*p.scale||r.blocked||
                           (priorSpeedSquared<p.stuckSpeedSquared&&combatRng.bounded(unsigned(p.stuckChance))==0))r.targetReady=false;
                        else r.momentum=add(r.momentum,mul(unit(delta),p.force*e.championSpeed));
                    }
                }
                if(!afraid)r.momentum=slowEnemyMotion(e,before,r.momentum,p.retention);
                r.blocked=false;
                if(r.ticks%p.trailPeriod==0)
                    effectVisual({e.position.x,.025f,e.position.z},combatRng.real(p.trailMin,p.trailMax),7,p.trailLife);
                if(p.broodChild) {
                    if(r.cooldown>0)--r.cooldown;
                    else {
                        const auto count=std::count_if(enemies.begin(),enemies.end(),[&](const auto &body) {
                            const auto *d=content->monster(body.monster);
                            return body.alive&&!body.dyingEggy()&&body.friendly==e.friendly&&(!d||!d->roomHazard);
                        });
                        // Reserved births count locally, preventing parallel producers
                        // from evading the source population gate during backpressure.
                        if(size_t(count)+pendingMonsters_.size()<size_t(p.broodLimit)) {
                            const auto target=add(e.position,rotateY({combatRng.real(0,p.broodRadius),0,0},combatRng.real(0,2*Pi)));
                            if(queueThrownSpider(e,p.broodChild,target,p.broodHeight)) {
                                r.cooldown=combatRng.bounded(2)?p.broodLong:p.broodShort;++r.births;
                            }
                        }
                    }
                }
            }
            e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=float(r.cooldown)/30;
            if(!r.pendingShots.empty()){e.velocity={};return;}
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position,velocity=steerMonsterBodies(e,mul(r.momentum,p.scale*30));
        if(!e.railCarrier)moveMonster(e,velocity,step*timeScale);
        if(length(velocity)>.001f&&planarDistance(before,e.position)<length(velocity)*step*timeScale*.5f)r.blocked=true;
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            contactMonsterPlayer(e,p.contact);
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=add(e.position,e.facing);
}
} // namespace dw
