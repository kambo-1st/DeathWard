#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootLobWalker(Enemy &e,Vector3 aim) {
    const auto &p=*content->lobWalker(e.monster);
    aim=horizontal(aim);
    if(length(aim)<.001f)return false;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
    if(queue_.size()>=limits.queuedEvents||projectiles.size()+size_t(queued)>=limits.projectiles)return false;
    auto velocity=mul(unit(aim),p.speed);
    if(p.jitter>0)velocity=add(velocity,rotateY({combatRng.real(0,p.jitter),0,0},combatRng.real(-Pi,Pi)));
    velocity.y=combatRng.real(p.upMin,p.upMax);
    Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
    shot.position=shot.origin=add(e.position,{0,p.height-.85f,0});
    shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=10;
    shot.projectileKind=p.fireWave.jetStepFrames?ProjectileKind::Ember:ProjectileKind::Ipecac;shot.projectileLife=8;
    shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.flightRetention;shot.projectileRadius=p.radius;
    if(p.fireWave.jetStepFrames)shot.fireWave=p.fireWave;
    else {shot.projectileBlastRadius=p.blastRadius;shot.projectileBlastDamage=p.blastDamage;shot.projectileBlastPlayerDamage=p.playerDamage;}
    return queueRoot(shot);
}

void Simulation::updateLobWalker(Enemy &e,float dt) {
    const auto &p=*content->lobWalker(e.monster);const auto &d=*content->monster(e.monster);
    if(!e.lob)e.lob=LobWalkerRuntime{};
    auto &r=*e.lob;
    e.age+=dt;e.pathTime-=dt;e.auxiliary-=dt;
    e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r={};e.stateTime-=dt;e.velocity={};
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    // No generic cooldown/floor multiplier: these delays are source30Hz ticks.
    e.cooldown=std::max(0.f,e.cooldown-dt);
    const bool wander=d.motion==MonsterMotion::Wander;
    Vector3 wanted{};
    if(r.attackFrame<0) {
        Vector3 direction=unit(horizontal(sub(player.position,e.position)));
        if(wander) {
            if(e.auxiliary<=0) {
                e.facing=rotateY({1,0,0},combatRng.real(-Pi,Pi));
                e.auxiliary=combatRng.real(p.wanderMin,p.wanderMax);
            }
            direction=e.facing;
        } else if(!arena.clear(e.position,player.position,e.radius)) {
            if(e.pathTime<=0){e.path=arena.path(e.position,player.position,e.radius);e.pathTime=.6f;}
            while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.15f)e.path.erase(e.path.begin());
            direction=e.path.empty()?Vector3{}:unit(horizontal(sub(e.path.front(),e.position)));
        }
        wanted=mul(direction,d.speed*EnemyMovementMultiplier);
        if(!wander)wanted=steerMonsterBodies(e,wanted);
    }
    const float retention=std::pow(p.movementRetention,dt*30);
    const auto velocity=add(mul(horizontal(e.velocity),retention),mul(wanted,1-retention));
    const auto before=e.position;
    moveMonster(e,velocity,dt);
    if(wander&&length(wanted)>.1f&&distance(before,e.position)<length(velocity)*dt*.5f)e.auxiliary=0;
    if(!wander&&length(e.velocity)>.05f)e.facing=unit(e.velocity);
    if(d.contact&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
       arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(10,source);
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(r.attackFrame>=0) {
            if(r.attackFrame<p.shootFrame||r.fired)++r.attackFrame;
            if(r.attackFrame==p.shootFrame&&!r.fired) {
                // Aim at the current target at Shoot, never the acquisition position.
                if(!shootLobWalker(e,sub(player.position,e.position)))continue;
                r.fired=true;
            }
            if(r.attackFrame>=p.attackFrames){r.attackFrame=-1;r.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
            else {e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames-r.attackFrame)/30;}
        } else if(e.cooldown<=1e-6f) {
            if(wander) {
                // Blocked/stationary bodies neither aim at the player nor reset delay.
                if(shootLobWalker(e,e.velocity))
                    e.cooldown=float(p.repeatMin+int(combatRng.bounded(unsigned(p.repeatMax-p.repeatMin+1))))/30;
            } else if(combatRng.bounded(unsigned(p.chance))==0&&planarDistance(e.position,player.position)<p.range) {
                // Source acquisition has no sight requirement; the physical lob
                // still collides with the actual wall/terrain in its trajectory.
                r.attackFrame=0;r.fired=false;e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames)/30;
                e.target=player.position;
            }
        }
    }
}
} // namespace dw
