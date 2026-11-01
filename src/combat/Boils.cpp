#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootBoil(Enemy &e,const BoilDefinition &p,bool aimed) {
    auto &r=*e.sack;
    if(!r.shots)r.shots=p.shotMinimum+int(combatRng.bounded(unsigned(p.shotMaximum-p.shotMinimum+1)));
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(queue_.size()+size_t(r.shots)>limits.queuedEvents||projectiles.size()+size_t(queued+r.shots)>limits.projectiles)return false;
    for(int n=0;n<r.shots;++n) {
        Vector3 velocity;
        if(aimed) {
            velocity=mul(unit(horizontal(sub(player.position,e.position))),p.shotSpeed);
            velocity=add(velocity,rotateY({combatRng.real(0,p.shotScatter),0,0},combatRng.real(0,2*Pi)));
            velocity=mul(velocity,combatRng.real(p.aimedMultiplierMin,p.aimedMultiplierMax));
        } else velocity=rotateY({p.shotSpeed,0,0},combatRng.real(0,2*Pi));
        velocity.y=combatRng.real(p.upMin,p.upMax);
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin={e.position.x,p.shotHeight,e.position.z};
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=10;shot.projectileLife=8;
        shot.projectileGravity=p.gravity;shot.projectileFlightRetention=.9f;
        shot.projectileRadius=p.shotRadius;
        if(p.payload==BoilPayload::Ipecac) {
            shot.projectileKind=ProjectileKind::Ipecac;shot.projectileBlastRadius=p.blastRadius;
            shot.projectileBlastDamage=p.blastDamage;shot.projectileBlastPlayerDamage=p.playerDamage;
        } else shot.projectileRadius*=.9f+.4f*float(combatRng.bounded(2))+combatRng.real(0,.05f);
        queueRoot(shot);
    }
    return true;
}

void Simulation::updateSack(Enemy &e,float dt) {
    // Stationary Sack and the Boil family share the source attack/growth cycle.
    // Walkers start full-sized and never enter regenerative growth.
    const auto *profile=content->boil(e.monster);
    const auto &p=profile?profile->cycle:*content->sack(e.monster);
    const bool walking=profile&&profile->walking;
    const bool spider=!profile||profile->payload==BoilPayload::Spider;
    if(!e.sack)e.sack=SackRuntime{};
    auto &r=*e.sack;e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=walking?mul(horizontal(e.velocity),1/(profile->scale*30)):Vector3{};
    if(!r.initialized){r.initialized=true;r.previousHp=e.hp;}
    if(!walking&&e.hp<r.previousHp-.0001f){r.growth=0;r.frame=-1;r.fired=false;r.shots=0;}
    r.previousHp=e.hp;
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frame=-1;r.fired=false;r.shots=0;r.targetReady=false;e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(walking) {
            const auto &w=*profile;
            if(r.frame<0) {
                if(r.targetReady&&(planarDistance(e.position,r.destination)<w.arrival*w.scale||
                    (length(r.momentum)<std::sqrt(.1f)&&combatRng.bounded(10)==0)))r.targetReady=false;
                if(!r.targetReady) {
                    // Native WalkRandom samples a40-unit radial point. Require
                    // legal local terrain and a clear approach for our3D rooms.
                    for(int attempt=0;attempt<12;++attempt) {
                        auto target=add(e.position,rotateY({w.wanderDistance*w.scale,0,0},combatRng.real(0,2*Pi)));
                        if(arena.roomAt(target)!=room||arena.blocked(target,e.radius)||!arena.clear(e.position,target,e.radius))continue;
                        r.destination=target;r.targetReady=true;break;
                    }
                }
                if(r.targetReady)r.momentum=add(r.momentum,mul(unit(horizontal(sub(r.destination,e.position))),w.force/w.retention));
            }
            r.momentum=mul(r.momentum,w.retention);
        }
        if(!walking&&e.hp<e.maxHp-.0001f) {
            e.hp=std::min(e.maxHp,e.hp+r.growth*p.healing*p.healthScale*content->regularHealthAdjustment(e.monster));
            r.growth=(r.growth+p.growth)*p.growthRetention;r.frame=-1;r.fired=false;r.shots=0;e.state=EnemyState::Ready;
            continue;
        }
        if(r.frame>=0) {
            if(r.shake||r.frame<p.eventFrame||r.fired)++r.frame;
            if(!r.shake&&r.frame==p.eventFrame&&!r.fired) {
                if(spider) {
                    if(e.generation>=4)r.fired=true;
                    else if(livingEnemies()+pendingMonsters_.size()<limits.enemies) {
                        const bool near=planarDistance(e.position,player.position)<p.aimRange-combatRng.real(0,p.aimJitter);
                        auto target=near?mul(add(e.position,player.position),.5f):e.position;
                        target=add(target,rotateY({combatRng.real(0,near?p.nearScatter:p.farScatter),0,0},combatRng.real(0,2*Pi)));
                        ThrownOffspringRuntime thrown;thrown.origin=e.position;
                        if(profile)thrown.profile.initialHeight=profile->throwHeight;
                        queueMonster(p.child,target,0,e.generation+1,false,1,0,e.id,0,-1,{},true,thrown);
                        r.fired=true;
                    }
                } else {
                    const bool aimed=planarDistance(e.position,player.position)<p.aimRange-combatRng.real(0,p.aimJitter);
                    r.fired=shootBoil(e,*profile,aimed);
                }
                if(r.fired){++r.attacks;audioCues.push(AudioCueKind::MonsterAttack,e.position);}
            }
            if(r.frame>=(r.shake?p.shakeFrames:p.attackFrames)) {
                r.frame=-1;r.fired=false;r.shots=0;e.state=EnemyState::Ready;e.stateTime=0;
            } else {e.state=EnemyState::Windup;e.stateTime=float((r.shake?p.shakeFrames:p.attackFrames)-r.frame)/30;}
        } else if(combatRng.bounded(unsigned(p.chance))==0&&
            (planarDistance(e.position,player.position)<p.nearRange||combatRng.bounded(unsigned(p.farChance))==0)) {
            const auto count=roomThreats()+pendingMonsters_.size();
            r.shake=spider&&(count>=size_t(p.populationLimit)||(count>0&&combatRng.bounded(unsigned(count))!=0));
            // Walking Sack keeps walking when its population roll rejects a
            // birth. Only the stationary family has the Shake animation.
            if(walking&&r.shake){r.shake=false;continue;}
            r.frame=0;r.fired=false;r.shots=0;e.state=EnemyState::Windup;e.stateTime=float(r.shake?p.shakeFrames:p.attackFrames)/30;
            if(!r.shake)audioCues.push(AudioCueKind::Warning,e.position);
        }
    }
    if(walking) {
        const auto before=e.position;
        moveMonster(e,steerMonsterBodies(e,mul(r.momentum,profile->scale*30)),dt);
        if(length(r.momentum)>.1f&&planarDistance(before,e.position)<.001f)r.targetReady=false;
        if(length(e.velocity)>.001f)e.facing=unit(horizontal(e.velocity));
        if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(profile->contactDamage,source);
        }
    } else e.velocity={};
    r.previousHp=e.hp;
}
} // namespace dw
