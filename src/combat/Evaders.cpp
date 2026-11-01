#include "combat/Simulation.hpp"

namespace dw {
float Simulation::stepEvaderMotion(Enemy &e,const EvaderDefinition &p,EvaderRuntime &r,const Vector3 *resolvedTarget) {
    const auto targetPosition=resolvedTarget?*resolvedTarget:player.position;
    auto planDestination=[&](bool flee) {
        r.targetReady=false;e.path.clear();
        const auto away=unit(horizontal(sub(e.position,targetPosition)));
        // Source flee candidates are scattered around a point away from the
        // player. Resolve them using the canyon's physical navigation, instead
        // of importing Isaac's rectangular grid and its tile marker cache.
        for(int attempt=0;attempt<16;++attempt) {
            Vector3 offset;
            if(flee) {
                const float angle=combatRng.real(0,2*Pi),radius=combatRng.real(30,480)*p.scale;
                offset=add(mul(away,30*p.scale),{std::cos(angle)*radius,0,std::sin(angle)*radius*.5f});
            } else offset=rotateY({40*p.scale,0,0},combatRng.real(0,2*Pi));
            auto target=add(e.position,offset);target.y=e.position.y;
            if(p.hoverHeight>0?arena.swimBlocked(target,e.radius,room):arena.roomAt(target)!=room||arena.blocked(target,e.radius))continue;
            if(flee&&planarDistance(target,targetPosition)<planarDistance(e.position,targetPosition)+1)continue;
            auto path=p.hoverHeight>0?arena.swimPath(e.position,target,e.radius,room):arena.path(e.position,target,e.radius);
            if(path.empty())continue;
            r.destination=target;r.targetReady=true;e.path=std::move(path);return;
        }
    };
    if((r.tick+e.id)%unsigned(p.proximityFrames)==0) {
        const bool sight=arena.sight(e.position,targetPosition);
        const bool near=planarDistance(e.position,targetPosition)<(sight?p.visibleRange:p.hiddenRange);
        if(near) {
            if(!r.evadeChecks)r.targetReady=false;
            r.evadeChecks=p.evadeChecks;
        } else r.evadeChecks=std::max(0,r.evadeChecks-1);
    }
    const bool flee=r.evadeChecks>0;
    if(r.targetReady&&(planarDistance(e.position,r.destination)<.3f||e.path.empty()))r.targetReady=false;
    if(p.chase) {
        if(!r.targetReady||planarDistance(r.destination,targetPosition)>.5f) {
            r.destination=targetPosition;r.targetReady=true;e.path=arena.path(e.position,r.destination,e.radius);
        }
    } else if(!r.targetReady)planDestination(flee);
    float appliedRetention=1;
    if(r.targetReady) {
        while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.35f)e.path.erase(e.path.begin());
        const auto point=e.path.empty()?r.destination:e.path.front();
        const auto delta=horizontal(sub(point,e.position));
        // Shared native path force min(distance*.1,2)*speed, with .7
        // friction; wander is a .5 impulse and .9 friction. Friction
        // is applied after AddVelocity's division by that friction.
        const float force=(flee||p.chase)?std::min(length(delta)/p.scale*.1f,2.f)*p.pathForce:p.wanderForce;
        const float pathFriction=(flee||p.chase)?.7f:p.wanderRetention;
        appliedRetention=pathFriction;
        r.momentum=add(mul(r.momentum,pathFriction),mul(unit(delta),force*e.championSpeed));
    }
    return appliedRetention;
}

void Simulation::updateEvader(Enemy &e,float dt) {
    const auto &p=*content->evader(e.monster);
    if(!e.evader)e.evader=EvaderRuntime{};
    auto &r=*e.evader;
    if(!r.initialized) {
        r.initialized=true;r.tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);e.lift=0;
    if(p.hoverHeight>0)e.position.y=.85f+p.hoverHeight;
    auto requestDeath=[&] {
        Event death;death.type=EventType::Damage;death.target=e.id;death.position=e.position;
        death.damage=e.hp+1;death.context.sourceEntity=e.id;
        e.selfDetonated=true;r.momentum={};e.velocity={};queueRoot(death);
    };
    if(e.selfDetonated){requestDeath();return;}
    if(e.state==EnemyState::Stunned) {
        r.attackFrame=-1;r.detonationFrame=-1;r.fired=false;r.momentum={};e.velocity={};r.clock=0;e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.tick;++r.lifeTicks;
        // Native state0 only initializes state4; movement/attacks start on the
        // following source update (including Nest, Hive and Mulligan).
        if(r.lifeTicks==1)continue;
        if(r.detonationFrame>=0) {
            r.momentum=mul(r.momentum,p.retention);++r.detonationFrame;
            e.state=EnemyState::Windup;e.stateTime=float(p.detonationFrames-r.detonationFrame)/30;
            if(r.detonationFrame>=p.detonationFrames){requestDeath();return;}
            continue;
        }
        if(p.chase&&r.lifeTicks%unsigned(p.contactFrames)==0&&planarDistance(e.position,player.position)<p.contactRange) {
            requestDeath();return;
        }
        float friction=1;
        if(r.attackFrame<0) {
            stepEvaderMotion(e,p,r);
            friction=p.retention;
            if(p.detonationChance&&r.gridCollision&&combatRng.bounded(unsigned(p.detonationChance))==0) {
                r.detonationFrame=0;e.state=EnemyState::Windup;e.stateTime=float(p.detonationFrames)/30;
                audioCues.push(AudioCueKind::Warning,e.position);
            }
            r.gridCollision=false;
        } else {
            if(r.attackFrame<p.shootFrame||r.fired)++r.attackFrame;
            if(r.attackFrame==p.shootFrame&&!r.fired) {
                if(e.generation>=4)r.fired=true; // Existing global offspring-generation bound.
                else if(livingEnemies()+pendingMonsters_.size()<limits.enemies) {
                    queueMonster(p.child,e.position,0,e.generation+1,false,p.childHealth,0,e.id,0,-1,{},true);
                    pendingMonsters_.back().childContactDeath=p.childContactDeath;
                    r.fired=true;audioCues.push(AudioCueKind::MonsterAttack,e.position);
                }
            }
            if(r.attackFrame>=p.attackFrames){r.attackFrame=-1;r.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
            else {e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames-r.attackFrame)/30;}
        }
        r.momentum=mul(r.momentum,friction);
        if(!p.spawns)continue;
        // The source gates on all room enemies, not an owner-specific child cap.
        // Include reserved births so frame ordering cannot bypass local capacity.
        const auto population=roomThreats()+pendingMonsters_.size();
        if(r.cooldown<=1&&population>=size_t(p.populationMinimum+int(combatRng.bounded(unsigned(p.populationMaximum-p.populationMinimum+1)))))
            r.cooldown+=float(p.crowdDelayMinimum+int(combatRng.bounded(unsigned(p.crowdDelayMaximum-p.crowdDelayMinimum+1))));
        if(r.evadeChecks>0) {
            if(r.cooldown<=0&&r.attackFrame<0) {
                if(planarDistance(e.position,player.position)>=p.attackRange)r.cooldown=3;
                else if(!arena.sight(e.position,player.position))r.cooldown=7;
                else {
                    r.cooldown=float(p.cooldownFrames);
                    if(p.cooldownBonusMaximum)r.cooldown+=float(p.cooldownBonusMinimum+
                        int(combatRng.bounded(unsigned(p.cooldownBonusMaximum-p.cooldownBonusMinimum+1))));
                    r.attackFrame=0;r.fired=false;
                    e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames)/30;e.target=player.position;
                    audioCues.push(AudioCueKind::Warning,e.position);
                }
            } else r.cooldown=std::max(0.f,r.cooldown-1);
        }
    }
    auto velocity=mul(r.momentum,p.scale*30);if(length(velocity)>24)velocity=mul(unit(velocity),24);
    const auto previous=e.position;
    const auto steered=steerMonsterBodies(e,velocity);
    moveMonster(e,steered,dt);
    // A static terrain collision can arm a Mulligan's random explosion; other
    // bodies alone must not count as a grid hit. Latch across 60Hz half-steps.
    if(p.detonationChance&&planarDistance(add(previous,mul(steered,dt)),e.position)>.0001f)r.gridCollision=true;
    if(length(velocity)>.2f&&planarDistance(previous,e.position)<.0001f){r.targetReady=false;e.path.clear();}
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    e.cooldown=r.cooldown/30;
    // The source bodies are harmless. Offspring own their own contact policies.
}
} // namespace dw
