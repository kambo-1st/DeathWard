#include "combat/Simulation.hpp"
#include "combat/LobFlight.hpp"
#include "combat/SourceTime.hpp"

namespace dw {
void Simulation::updateHeadShooter(Enemy &e,float dt) {
    const auto &p=*content->headShooter(e.monster);
    if(!e.headShooter)e.headShooter=HeadShooterRuntime{};
    auto &r=*e.headShooter;
    const float timeScale=enemyTimeScale(e);
    if(!r.initialized) {
        // Source acquisition uses the global frame plus entity index. Room
        // re-entry retains this actor's phase; inactive actors do not catch up.
        r.tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));
        r.initialized=true;
    }
    e.age+=dt;e.lift=0;
    e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        e.cooldown=std::max(0.f,e.cooldown-dt*timeScale);
        e.velocity={};
        r.attackFrame=-1;r.fired=false;r.clock=0;e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    if(p.bodyRetention>0&&!e.railCarrier) {
        // Stationary AI still retains externally supplied momentum. Use the
        // same fractional source-frame interpolation as projectile damping.
        auto velocity=horizontal(e.velocity);
        const float retention=sourceTimeRetention(p.bodyRetention,timeScale);
        const Vector3 travel{advanceLobHeight(velocity.x,0,retention,dt)*timeScale,0,
                             advanceLobHeight(velocity.z,0,retention,dt)*timeScale};
        const auto before=e.position;moveMonster(e,mul(travel,1/dt),dt);
        const auto moved=sub(e.position,before);
        e.velocity={std::abs(moved.x-travel.x)<.0001f?velocity.x:0,0,
                    std::abs(moved.z-travel.z)<.0001f?velocity.z:0};
    } else if(!e.railCarrier)e.velocity={};
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.tick;
        const int elapsedFrames=advanceSourceFrames(r.timerFraction,timeScale);
        const int animationFrames=advanceSourceFrames(r.animationFraction,timeScale);
        e.cooldown=std::max(0.f,e.cooldown-float(elapsedFrames)/30);
        if(r.attackFrame>=0) {
            if(r.attackFrame<p.shootFrame||r.fired)r.attackFrame+=animationFrames;
            if(r.attackFrame==p.shootFrame&&!r.fired) {
                const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
                if(queue_.size()>=limits.queuedEvents||projectiles.size()+size_t(queued)>=limits.projectiles)continue;
                // Aim on Shoot; leaving acquisition range does not cancel it.
                Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
                shot.position=shot.origin=e.position;shot.direction=unit(horizontal(sub(resolvedEnemyTarget(e),e.position)));
                if(length(shot.direction)<.001f)shot.direction=e.facing;
                shot.speed=p.speed;shot.damage=p.damage;shot.projectileLife=p.life;
                shot.projectileTimeScale=enemyShotTimeScale(e);
                setEnemyShotAffiliation(e,shot);
                if(p.shotRetention>0) {
                    const auto velocity=add(mul(shot.direction,p.speed),{0,p.shotUp,0});
                    shot.position=shot.origin=add(e.position,{0,p.shotHeight-.85f,0});
                    shot.direction=unit(velocity);shot.speed=length(velocity);
                    shot.projectileGravity=p.shotGravity;shot.projectileFlightRetention=p.shotRetention;
                    shot.projectileRadius=p.shotRadius;
                }
                if(!queueRoot(shot))continue;
                audioCues.push(AudioCueKind::MonsterAttack,e.position);r.fired=true;
            }
            if(r.attackFrame>=p.attackFrames) {r.attackFrame=-1;r.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
            else {e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames-r.attackFrame)/30;}
        }
        const auto target=resolvedEnemyTarget(e);
        if(!(e.affectedBy(EnemyStatus::Fear)||e.affectedBy(EnemyStatus::Shrink))&&!e.affectedBy(EnemyStatus::Confusion)&&
           r.attackFrame<0&&e.cooldown<=1e-6f&&(r.tick+e.id)%unsigned(p.checkFrames)==0&&
           planarDistance(e.position,target)<p.range&&arena.sight(e.position,target)) {
            r.attackFrame=0;r.animationFraction=0;r.fired=false;e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames)/30;
            e.target=target;e.cooldown=float(p.cooldownFrames)/30;
            audioCues.push(AudioCueKind::Warning,e.position);
        }
    }
    if(r.attackFrame>=0&&!r.fired)e.target=resolvedEnemyTarget(e);
    if(content->monster(e.monster)->contact&&planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        contactMonsterPlayer(e,10);
    }
}
} // namespace dw
