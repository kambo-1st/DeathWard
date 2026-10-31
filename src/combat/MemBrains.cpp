#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootMemBrain(Enemy &e) {
    const auto &p=*content->memBrain(e.monster);auto &r=*e.memBrain;
    if(r.pendingShots.empty())for(int n=0;n<8;++n) {
        const float angle=p.shotAngle+float(n)*Pi/4;
        Vector3 velocity{std::cos(angle)*p.shotSpeed,combatRng.real(p.shotUpMin,p.shotUpMax),std::sin(angle)*p.shotSpeed};
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=add(e.position,{0,p.shotHeight-.85f,0});shot.origin=e.position;
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shotDamage;
        shot.projectileLife=p.shotLife;shot.projectileRadius=p.shotRadius;
        shot.projectileGravity=p.shotGravity;shot.projectileFlightRetention=p.shotRetention;
        shot.repeatWallBounce=p.wallBounce;r.pendingShots.push_back(shot);
        if(p.dinga)r.pendingShots.back().projectileKind=ProjectileKind::Brown;
    }
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+8>limits.queuedEvents||projectiles.size()+size_t(queued)+8>limits.projectiles)return false;
    for(const auto &shot:r.pendingShots)queueRoot(shot);
    r.pendingShots.clear();++r.volleys;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

bool Simulation::dingaAttack(Enemy &e) {
    const auto &parent=*content->memBrain(e.monster);const auto &p=*parent.dinga;auto &r=*e.memBrain;
    if(r.birthChoice<0)r.birthChoice=roomThreats()+pendingMonsters_.size()<size_t(p.populationLimit)&&
        combatRng.bounded(unsigned(p.shotChance))!=0?1:0;
    if(r.birthChoice==0) {if(!shootMemBrain(e))return false;}
    else {
        const auto axis=rotateY({1,0,0},combatRng.real(0,2*Pi));
        const float force=std::max(0.f,p.pushRange-p.childOffset/parent.scale)*p.pushForce*parent.scale*30;
        for(float sign:{-1.f,1.f})queueMonster(p.child,add(e.position,mul(axis,sign*p.childOffset)),
            0,e.generation+1,false,1,0,e.id,0,-1,{},true,{},mul(axis,sign*force));
        r.births+=2;audioCues.push(AudioCueKind::MonsterAttack,e.position);
    }
    // The source finds every type-217 actor, not only this parent's children.
    for(auto &dip:enemies)if(dip.alive&&dip.monster.type==p.child.type) {
        const auto delta=horizontal(sub(dip.position,e.position));const float d=length(delta)/parent.scale;
        if(d<=0||d>=p.pushRange)continue;
        dip.velocity=add(dip.velocity,mul(unit(delta),(p.pushRange-d)*p.pushForce*parent.scale*30));++r.pushes;
    }
    return true;
}

bool Simulation::shootCyst(Enemy &e) {
    const auto &p=*content->guts(e.monster);auto &r=*e.guts;
    if(r.pendingShots.empty()) {
        auto direction=unit(horizontal(sub(player.position,e.position)));if(length(direction)<.001f)direction=e.facing;
        auto velocity=mul(direction,p.shotSpeed);velocity.y=p.shotUp;
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;shot.position=add(e.position,{0,p.shotHeight-.85f,0});shot.origin=e.position;
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shotDamage;
        shot.projectileLife=p.shotLife;shot.projectileRadius=p.shotRadius;shot.projectileGravity=p.shotGravity;
        shot.projectileFlightRetention=p.shotRetention;r.pendingShots.push_back(shot);
    }
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+1>limits.queuedEvents||projectiles.size()+size_t(queued)+1>limits.projectiles)return false;
    queueRoot(r.pendingShots.front());r.pendingShots.clear();++r.shots;
    audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

void Simulation::memBrainDeath(const Enemy &e) {
    const auto &p=*content->memBrain(e.monster);
    const auto offset=rotateY({p.childOffset,0,0},combatRng.real(0,2*Pi));
    // Native children have zero initial velocity and opposite random offsets.
    // Retained births remain room threats even if one slot is temporarily full.
    for(float sign:{1.f,-1.f})queueMonster(p.child,add(e.position,mul(offset,sign)),0,e.generation+1,false,1,0,0,0,-1,{},true);
}

void Simulation::updateMemBrain(Enemy &e,float dt) {
    const auto &p=*content->memBrain(e.monster);if(!e.memBrain)e.memBrain=MemBrainRuntime{};auto &r=*e.memBrain;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=r.attackFrame>=0?EnemyState::Windup:EnemyState::Ready;
        return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized)r.initialized=true;
            else {
                if(r.attackFrame>=0) {
                    if(r.attackFrame<p.shootFrame||r.fired)r.attackFrame+=p.dinga?p.dinga->animationFps/30:1;
                    if(r.attackFrame>=p.shootFrame&&!r.fired) {
                        r.fired=p.dinga?dingaAttack(e):shootMemBrain(e);
                        if(!r.fired)r.attackFrame=float(p.shootFrame);
                    }
                    if(r.attackFrame>=p.attackFrames){r.attackFrame=-1;r.fired=false;}
                } else {
                    // The native helper samples once before its arrival/collision/
                    // stuck check. Clearing a target cannot reroll it this frame.
                    if(!r.targetReady) {
                        const auto point=add(e.position,rotateY({p.wanderDistance*p.scale,0,0},combatRng.real(0,2*Pi)));
                        const auto &bounds=arena.rooms[size_t(room)].bounds;
                        if(point.x>=bounds.min.x+e.radius&&point.x<=bounds.max.x-e.radius&&
                            point.z>=bounds.min.z+e.radius&&point.z<=bounds.max.z-e.radius&&
                            !arena.blocked(point,e.radius)&&arena.clear(e.position,point,e.radius)) {
                            r.destination=point;r.targetReady=true;
                        }
                    }
                    if(r.targetReady&&(r.blocked||planarDistance(e.position,r.destination)<p.arrival*p.scale||
                        (length(r.momentum)<p.stuckSpeed&&combatRng.bounded(unsigned(p.stuckChance))==0)))r.targetReady=false;
                    r.blocked=false;
                    if(r.targetReady)r.momentum=add(r.momentum,mul(unit(horizontal(sub(r.destination,e.position))),p.force/p.retention));
                    r.walkPhase=std::fmod(r.walkPhase+(p.dinga?p.dinga->animationFps/30:1)/float(p.walkFrames),1.f);
                    if(combatRng.bounded(unsigned(p.chance))==0&&roomThreats()+pendingMonsters_.size()<size_t(p.populationLimit)) {
                        r.attackFrame=0;r.fired=false;r.birthChoice=-1;++r.attacks;
                    }
                }
                r.momentum=mul(r.momentum,p.retention);
            }
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto wanted=mul(r.momentum,p.scale*30),before=e.position;
        moveMonster(e,wanted,step);
        if(length(sub(horizontal(sub(e.position,before)),mul(wanted,step)))>.001f) {
            r.blocked=true;r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        }
        if(length(e.velocity)>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
            arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
        }
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=r.targetReady?r.destination:e.position;
    e.state=r.attackFrame>=0?EnemyState::Windup:EnemyState::Ready;
    e.stateTime=r.attackFrame>=0?float(p.attackFrames-r.attackFrame)/(p.dinga?p.dinga->animationFps:30):0;
    // Source hop is sprite deformation, not an invulnerable pathfinding jump.
    const float arc=float(r.attackFrame-(p.shootFrame-13))/13;
    e.lift=arc>0&&arc<1?std::sin(arc*Pi)*1.1f:0;
}
} // namespace dw
