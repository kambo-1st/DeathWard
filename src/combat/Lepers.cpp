#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::delaysLeperDamage(const Event &event) const {
    if(event.type!=EventType::Damage||event.leperResolved||event.execution||event.damage<=0)return false;
    const auto *e=findEnemy(event.target);
    return e&&e->alive&&e->leper&&content->leper(e->monster)&&!sourceImmune(*e,event);
}
bool Simulation::leperDamageFull(const Event &event) const {
    return delaysLeperDamage(event)&&findEnemy(event.target)->leper->pendingDamage.size()>=std::max(size_t(1),limits.queuedEvents);
}
void Simulation::cancelLeperDamage(Enemy &e) {
    if(!e.leper)return;
    auto release=[&](auto &hits){for(const auto &hit:hits) {
        const auto it=chains.find(hit.context.chainId);
        if(it!=chains.end()&&it->second.active)--it->second.active;
    }hits.clear();};
    release(e.leper->pendingDamage);release(e.leper->applyingDamage);
}
void Simulation::emitLeperFlesh(Enemy &e,bool final) {
    const auto &p=*content->leper(e.monster);
    const auto delta=horizontal(sub(e.position,player.position));
    const auto away=length(delta)>0?mul(delta,1/length(delta)):Vector3{};
    const auto direction=final?rotateY({1,0,0},combatRng.real(0,2*Pi)):away;
    const auto velocity=final?mul(direction,combatRng.real(p.deathMin,p.deathMax)):
        mul(rotateY(direction,combatRng.real(-p.childSpread,p.childSpread)*Pi/180),combatRng.real(p.childMin,p.childMax));
    // Capture source-frame choices now, but admit births only after translation.
    // Otherwise two 60Hz half-updates spawn/move children earlier than one30Hz
    // update and even change collision-aware spawn placement around the parent.
    e.leper->frameFlesh.push_back({add(e.position,mul(direction,p.childOffset)),velocity});
    ++e.leper->births;
}
void Simulation::flushLeperBirths(Enemy &e) {
    for(const auto &birth:e.leper->frameFlesh)
        queueMonster(content->leper(e.monster)->flesh,birth.position,0,std::min(4,e.generation+1),false,1,0,e.id,0,-1,{},true,{},birth.velocity);
    e.leper->frameFlesh.clear();
}
void Simulation::resolveLeperDamage(Enemy &e) {
    auto &r=*e.leper;if(r.pendingDamage.empty()||!r.applyingDamage.empty())return;
    const auto &p=*content->leper(e.monster);
    r.applyingDamage=std::move(r.pendingDamage);r.pendingDamage.clear();++r.batches;
    float damage=0;for(const auto &hit:r.applyingDamage)damage+=enemyDamage(e,hit);
    if(r.chase>0)r.chase=std::max(1,r.chase-int(std::ceil(p.damageTimerGain*damage/(p.damageScale*content->regularHealthAdjustment(e.monster)))));
    // Native AI predicts the entire queued batch before Entity::Update applies
    // individual hits. MaxHP remains fixed inside this loop; Morph runs once.
    const float predicted=e.hp-damage,oldMax=e.maxHp;
    const auto original=e.monster;
    const float hpScale=e.maxHp/content->monsterHealth(original,arena.profile.sourceStage);
    while(e.monster.subtype<3&&damage>0&&predicted<=float(3-e.monster.subtype)*oldMax/float(4-e.monster.subtype)) {
        ++e.monster.subtype;emitLeperFlesh(e,false);
        const auto delta=horizontal(sub(e.position,player.position));
        if(length(delta)>0)r.evade.momentum=add(r.evade.momentum,mul(delta,p.knockback*r.friction/length(delta)));
    }
    if(e.monster!=original) {
        e.maxHp=content->monsterHealth(e.monster,arena.profile.sourceStage)*hpScale;
        e.hp=std::min(e.hp,e.maxHp); // Native Morph clamps BEFORE queued subtraction.
        r.transition=p.transitionFrames;
        if(e.state!=EnemyState::Stunned){e.state=EnemyState::Windup;e.stateTime=float(r.transition)/30;}
        e.path.clear();r.evade.targetReady=false;
    }
    e.velocity=mul(r.evade.momentum,p.scale*30);
}
void Simulation::applyLeperDamage(Enemy &e) {
    // The common native update applies friction/translation before subtracting
    // queued HP. Finish the source frame's movement before death/morph spawns.
    auto hits=std::move(e.leper->applyingDamage);e.leper->applyingDamage.clear();
    bool consume=true;
    for(auto hit:hits) {
        if(consume) {
            hit.leperResolved=true;process(hit);
            // Native queued subtraction stops at a lethal hit. The resulting
            // Gusher must not receive the remainder of the parent's batch.
            consume=e.alive&&content->leper(e.monster);
        }
        const auto it=chains.find(hit.context.chainId);
        if(it!=chains.end()&&it->second.active)--it->second.active;
    }
}
bool Simulation::leperDeath(Enemy &e,const Event &event) {
    if(event.debugExecution) {
        if(e.leper){e.leper->pendingCreep.reset();e.leper->frameFlesh.clear();}
        return false;
    }
    const auto &p=*content->leper(e.monster);
    auto &r=*e.leper;if(r.deathReleased)return false;r.deathReleased=true;
    emitLeperFlesh(e,true);
    flushLeperBirths(e);
    if(e.hp<=-p.overkill*content->regularHealthAdjustment(e.monster)||combatRng.bounded(unsigned(p.morphChance))!=0)return false;
    const float scale=e.maxHp/content->monsterHealth(e.monster,arena.profile.sourceStage);
    e.monster=p.gusher;e.hp=e.maxHp=content->monsterHealth(p.gusher,arena.profile.sourceStage)*scale;
    e.state=EnemyState::Ready;e.stateTime=0;e.phase=0;e.behavior={};e.hop={};
    e.auxiliary=e.trailTime=e.lift=0;e.path.clear();e.pathTime=0;
    auto &h=e.headless.emplace();h.initialized=true;h.scarred=true;h.ticks=r.ticks;
    h.cooldown=p.gusherDelayMin+int(combatRng.bounded(unsigned(p.gusherDelayMax-p.gusherDelayMin+1)));
    h.momentum=mul(horizontal(e.velocity),1/(content->headless(p.gusher)->scale*30));
    e.cooldown=float(h.cooldown)/30;checkpointNeeded=true;
    cancelLeperDamage(e);
    // The native headless controller only special-cases State0; inherited
    // State16 does not suppress wandering/shooting. No transition stun carries.
    return true;
}
bool Simulation::flushLeperCreep(Enemy &e) {
    if(!e.leper||!e.leper->pendingCreep)return true;
    auto &r=*e.leper;if(hazards.size()>=limits.hazards)return false;
    Hazard h;h.kind=HazardKind::Creep;h.position=h.origin=*r.pendingCreep;h.position.y=.85f;
    h.radius=r.creepRadius;h.damage=r.creepDamage;h.delay=0;h.duration=r.creepDuration;
    h.fadeDuration=r.creepFadeDuration;h.fadeScale=r.creepFadeScale;h.fadeOnRoomClear=true;
    h.tint={142,47,52,195};h.context.sourceEntity=e.id;addHazard(h);
    r.pendingCreep.reset();++r.creepPatches;return true;
}
void Simulation::updateLeper(Enemy &e,float dt) {
    auto &r=*e.leper;auto &motion=r.evade;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    motion.momentum=mul(horizontal(e.velocity),1/(content->leper(e.monster)->scale*30));
    const bool stunned=e.state==EnemyState::Stunned;
    if(stunned){motion.momentum={};e.velocity={};e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;}
    float remaining=dt;
    while(remaining>1e-7f) {
        const auto &p=*content->leper(e.monster);
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            motion.tick=uint64_t(std::max(0.,std::floor((stats.duration-remaining)*30+1e-4)));
            r.friction=1;
            const bool capacity=flushLeperCreep(e);
            if(!r.initialized){r.initialized=true;r.chase=0;}
            else if(!capacity||stunned)motion.momentum={};
            else if(r.transition>0) {
                --r.transition;r.friction=p.transitionRetention;motion.momentum=mul(motion.momentum,r.friction);
            } else if(r.chase<=0&&e.monster.subtype<3) {
                r.friction=stepEvaderMotion(e,p.evade,motion)*p.evade.retention;
                motion.momentum=mul(motion.momentum,p.evade.retention);
                if(r.chase<0)++r.chase;
                if(!r.chase&&motion.evadeChecks<=0&&combatRng.bounded(unsigned(p.chaseChance))==0)r.chase=p.chaseFrames;
            } else {
                stepGroundPursuit(e,p,motion.momentum,motion.destination,p.force,&r.friction);
                r.friction*=p.chaseRetention;motion.momentum=mul(motion.momentum,p.chaseRetention);
                r.chase=std::max(0,r.chase-1);
                if(!r.chase)r.chase=-p.restMin-int(combatRng.bounded(unsigned(p.restMax-p.restMin+1)));
            }
            if(!stunned) {
                r.walkFrame=length(motion.momentum)>=p.stopSpeed?(r.walkFrame+1)%p.walkFrames:0;
                r.walkPhase=float(r.walkFrame)/p.walkFrames;
                e.state=r.transition>0?EnemyState::Windup:EnemyState::Ready;e.stateTime=float(r.transition)/30;
            }
            if(capacity&&(motion.tick+e.id)%unsigned(p.trailPeriod)==0) {
                if(e.monster.subtype==3) {
                    r.pendingCreep=e.position;r.creepRadius=combatRng.real(p.creepMin,p.creepMax);
                    r.creepDamage=p.creepDamage;r.creepDuration=float(p.creepFrames)/30;
                    r.creepFadeDuration=float(p.fadeFrames)/30;r.creepFadeScale=p.fadeScale;flushLeperCreep(e);
                }
                if(e.monster.subtype>0)effectVisual({e.position.x,.025f,e.position.z},combatRng.real(.1f,.2f),7,8);
            }
            resolveLeperDamage(e);
            if(!e.alive||!content->leper(e.monster))return;
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position;
        if(!stunned)moveMonster(e,steerMonsterBodies(e,mul(motion.momentum,p.scale*30)),step);
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(e.monster.subtype>0&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(content->leper(e.monster)->contact,{0,0,e.id,-1});
        motion.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f) {
            r.clock=0;r.frameReady=false;flushLeperBirths(e);applyLeperDamage(e);
            if(!e.alive||!content->leper(e.monster))return;
        }
    }
    e.target=player.position;e.cooldown=std::max(0,r.chase)/30.f;
}
} // namespace dw
