#include "combat/Simulation.hpp"
#include "combat/SourceTime.hpp"

namespace dw {
void Simulation::updateGaper(Enemy &e,float dt) {
    const auto &p=*content->gaper(e.monster);
    if(!e.gaper)e.gaper=GaperRuntime{};
    auto &r=*e.gaper;
    const float timeScale=enemyTimeScale(e);
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            const int animationFrames=advanceSourceFrames(r.animationFraction,timeScale);
            if(r.initialized) {
                if(p.frowning&&r.wakeStarted)r.headFrame=std::min(p.headFrames-1,r.headFrame+advanceSourceFrames(r.headFraction,timeScale));
                else if(!p.frowning)r.headFrame=(r.headFrame+advanceSourceFrames(r.headFraction,timeScale))%p.headFrames;
            } else r.initialized=true;
            // Walk selection precedes this tick's steering. The native .1
            // parameter is a stop threshold; it does not scale animation speed.
            r.walkFrame=length(r.momentum)>=p.stopSpeed?(r.walkFrame+animationFrames)%p.walkFrames:0;
            r.walkPhase=float(r.walkFrame)/p.walkFrames;
            r.force=(p.frowning&&r.headFrame>0?p.awakeForce:p.force)*e.championSpeed;
            if((e.affectedBy(EnemyStatus::Fear)||e.affectedBy(EnemyStatus::Shrink))) {
                stepFearMotion(e,r.momentum);
                // Native EvadeTarget can itself call FindGridPath. Its direct
                // escape route can wake the frowning overlay just like pursuit.
                const auto &flee=e.statuses->flee;
                if(flee.evadeChecks>0&&flee.targetReady)
                    r.directPath=arena.clear(e.position,flee.destination,e.radius);
            } else {
                const auto target=confusedTarget(e);
                const auto before=r.momentum;float retention=1;
                r.directPath=stepGroundPursuit(e,p,r.momentum,r.destination,r.force,&retention,&target);
                r.momentum=slowEnemyMotion(e,before,r.momentum,retention);
            }
            if(p.frowning&&r.directPath&&!r.wakeStarted)r.wakeStarted=true;
            r.eyeOpenness=p.frowning?float(r.headFrame)/float(p.headFrames-1):1;
            e.awakened=p.frowning&&r.headFrame>0;
            e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position;
        if(!e.railCarrier)moveMonster(e,steerMonsterBodies(e,mul(r.momentum,p.scale*30)),step*timeScale);
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            contactMonsterPlayer(e,p.contact);
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=(e.affectedBy(EnemyStatus::Fear)||e.affectedBy(EnemyStatus::Shrink))?e.statuses->flee.destination:
        e.affectedBy(EnemyStatus::Confusion)&&e.statuses->confusedTarget?*e.statuses->confusedTarget:resolvedEnemyTarget(e);
}
} // namespace dw
