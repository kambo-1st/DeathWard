#include "combat/Simulation.hpp"
#include "combat/LobFlight.hpp"
#include "combat/SourceTime.hpp"
#include <limits>

namespace dw {
namespace {
int *statusCounter(EnemyStatusRuntime &r,EnemyStatus status) {
    switch(status) {
    case EnemyStatus::Fear:return &r.fear;
    case EnemyStatus::Confusion:return &r.confusion;
    case EnemyStatus::Freeze:return &r.freeze;
    case EnemyStatus::Slow:return &r.slow;
    case EnemyStatus::Poison:return &r.poison.frames;
    case EnemyStatus::Burn:return &r.burn.frames;
    case EnemyStatus::Shrink:return &r.shrink;
    case EnemyStatus::Charm:return &r.charm;
    }
    return nullptr;
}
}
void Simulation::invalidateStatusPath(Enemy &e,EnemyStatus status) {
    // Freeze holds the controller's existing route, animation and attack.
    if(status!=EnemyStatus::Fear&&status!=EnemyStatus::Confusion&&status!=EnemyStatus::Shrink&&status!=EnemyStatus::Charm)return;
    e.path.clear();e.pathTime=0;
    if(!e.statuses)return;
    if(status==EnemyStatus::Charm){e.statuses->charmTarget=0;e.statuses->charmLastPoll=~uint64_t(0);}
    // Native status toggles invalidate the pathfinder cache, not the separate
    // confusion point. Reapplication may reuse that point until its next poll.
    if(status==EnemyStatus::Fear||status==EnemyStatus::Shrink) {
        e.statuses->flee.targetReady=false;
        if(e.headless)e.headless->targetReady=false;
    }
}

bool Simulation::applyEnemyStatus(EntityId id,EnemyStatus status,int frames,float damage,Context source) {
    if(!frames||frames < -18000||frames>18000||!std::isfinite(damage)||std::abs(damage)>1000000)return false;
    auto *e=findEnemy(id);
    const auto *p=e?content->enemyStatuses(e->monster):nullptr;
    if(!e||!e->alive||!p||(status==EnemyStatus::Freeze&&!p->freeze)||(status==EnemyStatus::Slow&&!p->slow)||
       (status==EnemyStatus::Poison&&!p->poison)||(status==EnemyStatus::Burn&&!p->burn)||
       (status==EnemyStatus::Shrink&&!p->shrink)||(status==EnemyStatus::Charm&&(!p->charm||frames<0||e->friendly)))return false;
    // Negative Charm is permanent conversion, not an extended temporary timer.
    // Reject it until follower lifetime/transfer support is implemented.
    EnemyStatusRuntime probe;
    if(!statusCounter(probe,status))return false;
    if(!e->statuses) {
        auto &r=e->statuses.emplace();
        // Retain the source phase while the resident's room is inactive.
        const double time=std::max(0.,double(e->age)*30);
        r.ticks=uint64_t(std::floor(time+.00001));
        r.clock=float(std::max(0.,time-double(r.ticks))/30);
    }
    auto &remaining=*statusCounter(*e->statuses,status);
    const bool already=remaining>0;
    const bool fleeing=e->affectedBy(EnemyStatus::Fear)||e->affectedBy(EnemyStatus::Shrink);
    if(!already&&status==EnemyStatus::Shrink) {
        auto &r=*e->statuses;
        if(r.unshrunkRadius==0)r.unshrunkRadius=e->radius;
        // Installed AddShrink uses the current interpolated visual scale once,
        // not its new target scale. Ordinary first application keeps full size.
        e->radius=r.unshrunkRadius*r.visualScale;
    }
    if(!already&&status==EnemyStatus::Freeze) {
        e->statuses->frozenPoseTime=e->animationTime();
        e->statuses->frozenSpeed=e->animationSpeed();
    }
    if(!already&&(status==EnemyStatus::Freeze||status==EnemyStatus::Slow)) {
        if(content->headShooter(e->monster)&&(!e->headShooter||!e->headShooter->initialized)) {
            // Capture the real poll phase before freezing, even before its
            // first AI call. A long thawing step must not initialize it from
            // the end of that step and silently skip source frames.
            if(!e->headShooter)e->headShooter.emplace();
            e->headShooter->tick=uint64_t(std::max(0.,std::floor(stats.duration*30+.00001)));
            e->headShooter->initialized=true;
        }
    }
    if(status==EnemyStatus::Charm) {
        remaining=std::max(remaining,frames);
        if(!already)e->statuses->charmFrame=uint64_t(std::max(0.,std::floor(stats.duration*30+.00001)));
    } else if(status==EnemyStatus::Slow) {
        // Native slowing is additive without the120-frame cap. Negative
        // duration assigns2, even if a longer application is already active.
        remaining=frames<0?p->slow->refreshFrames:int(std::min<int64_t>(std::numeric_limits<int>::max(),int64_t(remaining)+frames));
    } else if(frames<0)remaining=std::max(remaining,-frames);
    else {
        const int cap=status==EnemyStatus::Freeze?p->freeze->capFrames:status==EnemyStatus::Poison?p->poison->capFrames:
            status==EnemyStatus::Burn?p->burn->capFrames:status==EnemyStatus::Shrink?p->shrink->capFrames:p->capFrames;
        const int added=std::min(cap,remaining+frames);
        // Native confusion never shortens an existing extended application;
        // fear's positive-duration branch assigns the capped sum directly.
        remaining=status==EnemyStatus::Confusion?std::max(remaining,added):added;
    }
    if(status==EnemyStatus::Poison||status==EnemyStatus::Burn) {
        auto &r=status==EnemyStatus::Poison?e->statuses->poison:e->statuses->burn;
        const auto &profile=*(status==EnemyStatus::Poison?p->poison:p->burn);
        // The source keeps the stronger damage and does not restart the tick
        // phase when reapplying. Values are already converted to DeathWard HP.
        Event producer;producer.context=source;identifyDamageSource(producer);
        if(damage<=0)damage=producer.context.damageSource==DamageSource::Player||producer.context.damageSource==DamageSource::Ally?
            content->resolve(items,player.shotDamage,26,false)[BuildStat::Damage]:profile.minimumDamage;
        if(!already){r.elapsed=0;r.damage=profile.minimumDamage;}
        if(damage>r.damage||!already)r.source=producer.context;
        r.damage=std::max({r.damage,profile.minimumDamage,damage});
        // Tick roots retain attribution, but never retain an expired event chain.
        r.source.chainId=0;r.source.generation=0;
    }
    if(status==EnemyStatus::Charm) {
        // Reapplication invalidates navigation, but native target31c survives.
        e->path.clear();e->pathTime=0;
        if(!already)invalidateStatusPath(*e,status);
    } else if(!already&&!((status==EnemyStatus::Fear||status==EnemyStatus::Shrink)&&fleeing))invalidateStatusPath(*e,status);
    return true;
}

void Simulation::removeEnemyStatus(EntityId id,EnemyStatus status) {
    auto *e=findEnemy(id);if(!e||!e->statuses)return;
    auto *counter=statusCounter(*e->statuses,status);if(!counter)return;
    auto &remaining=*counter;
    if(remaining>0){
        remaining=0;
        if(status==EnemyStatus::Shrink&&e->statuses->unshrunkRadius>0)e->radius=e->statuses->unshrunkRadius;
        invalidateStatusPath(*e,status);
    }
}

void Simulation::updateMonsterStatuses(Enemy &e,float dt) {
    if(!e.statuses){updateMonster(e,dt);return;}
    auto &r=*e.statuses;
    if(r.squashed){flushSquashedEnemy(e);return;}
    // Contact still works while ordinary AI is frozen, stunned or waiting for
    // projectile capacity. A swept player path cannot skip a small body.
    if(r.shrink>0&&segmentSphere(sub(e.position,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
       arena.sight(e.position,player.position)) {
        contactMonsterPlayer(e,0);return;
    }
    if(content->headShooter(e.monster)&&(!e.headShooter||!e.headShooter->initialized)) {
        // Initialize from the whole physics step before subdividing it. Using
        // a short status slice with the end-of-step global time shifts Horf's
        // acquisition phase when an effect is applied before its first update.
        if(!e.headShooter)e.headShooter.emplace();
        e.headShooter->tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));
        e.headShooter->initialized=true;
    }
    flushStatusDamage(e,r.poison);flushStatusDamage(e,r.burn);
    // Consume time even during stun or a capacity-delayed shot, but not while
    // the room/simulation is paused. Splitting prevents long steps extending
    // effects or changing the frame on which the ordinary AI resumes.
    float remaining=dt;
    while(remaining>1e-7f) {
        const float step=std::min(remaining,1.f/30-r.clock);
        const bool frozen=r.freeze>0;
        if(frozen)updateFrozenMonster(e,step);
        else {
            r.animationDelay+=step*(1-enemyTimeScale(e));
            updateMonster(e,step);
        }
        remaining-=step;r.clock+=step;
        if(r.squashed)break;
        if(r.clock>=1.f/30-1e-6f) {
            r.clock=0;++r.ticks;++r.charmFrame;
            if(frozen) {
                // Native FrameCount still advances while the sprite/AI are
                // held. Retain polling phase without executing attacks/trails.
                if(e.gaper)++e.gaper->ticks;
                if(e.headless){++e.headless->ticks;advanceSourceFrames(e.headless->timerFraction,enemyTimeScale(e));}
                if(e.headShooter&&e.headShooter->initialized){++e.headShooter->tick;advanceSourceFrames(e.headShooter->timerFraction,enemyTimeScale(e));}
            }
            const auto *profile=content->enemyStatuses(e.monster);
            if(profile&&profile->shrink) {
                const float target=r.shrink>0?profile->shrink->scale:1;
                r.visualScale+=(target-r.visualScale)*profile->shrink->approach;
                if(std::abs(r.visualScale-target)<1e-6f)r.visualScale=target;
                if(r.shrink>0&&!--r.shrink){e.radius=r.unshrunkRadius;invalidateStatusPath(e,EnemyStatus::Shrink);}
            }
            if(profile&&profile->poison)tickDamageStatus(e,r.poison,*profile->poison);
            if(profile&&profile->burn)tickDamageStatus(e,r.burn,*profile->burn);
            if(r.freeze>0)--r.freeze;
            if(r.slow>0)--r.slow;
            if(r.fear>0&&!--r.fear)invalidateStatusPath(e,EnemyStatus::Fear);
            if(r.confusion>0&&!--r.confusion)invalidateStatusPath(e,EnemyStatus::Confusion);
            if(r.charm>0&&!--r.charm)invalidateStatusPath(e,EnemyStatus::Charm);
        }
    }
}

void Simulation::flushSquashedEnemy(Enemy &e) {
    auto &r=*e.statuses;
    if(r.squashQueued||queue_.size()>=limits.queuedEvents)return;
    // Native collision calls Die directly. Use the existing execution path to
    // suppress a Gaper's damage-triggered headless morph and pay one death only.
    Event hit;hit.type=EventType::Damage;hit.target=e.id;hit.position=e.position;
    hit.damage=std::max(1.f,e.hp);hit.damageKind=DamageKind::Crush;hit.execution=true;
    hit.context.damageSource=DamageSource::Player;
    r.squashQueued=queueRoot(hit);
}

void Simulation::contactMonsterPlayer(Enemy &e,float damage) {
    if(e.affectedBy(EnemyStatus::Shrink)||(e.statuses&&e.statuses->squashed)) {
        e.statuses->squashed=true;flushSquashedEnemy(e);
    } else hurtPlayer(damage,{0,0,e.id,-1});
}

bool Simulation::flushStatusDamage(Enemy &e,DamageStatusRuntime &r) {
    if(!r.pending)return true;
    // Normal event admission is bounded. Retain one selected tick and pause
    // only this effect's clock under backpressure; never grow an unbounded list.
    if(queue_.size()>=limits.queuedEvents)return false;
    Event hit;hit.type=EventType::Damage;hit.target=e.id;hit.position=r.pending->position;
    hit.damage=r.pending->damage;hit.damageKind=DamageKind::Burning;hit.areaDamage=true;
    hit.context=r.pending->source;hit.context.chainId=nextChain_++;hit.context.generation=0;
    if(!accept(hit))return false;
    r.pending.reset();return true;
}

void Simulation::tickDamageStatus(Enemy &e,DamageStatusRuntime &r,const DamageStatusDefinition &p) {
    if(!flushStatusDamage(e,r)||r.frames<=0)return;
    // Native duration expires before the periodic damage branch: duration2
    // cannot damage; duration3 hits on update2, then every20 real updates.
    if(!--r.frames){r.damage=p.minimumDamage;r.elapsed=0;return;}
    const bool due=r.elapsed==p.firstTick-1;
    r.elapsed=(r.elapsed+1)%p.periodFrames;
    if(due) {
        r.pending=StatusDamageTick{r.damage,e.position,r.source};
        flushStatusDamage(e,r);
    }
}

void Simulation::updateFrozenMonster(Enemy &e,float dt) {
    const auto &p=*content->enemyStatuses(e.monster)->freeze;
    const float timeScale=enemyTimeScale(e),retention=sourceTimeRetention(p.retention,timeScale);
    e.age+=dt;e.statuses->animationDelay+=dt;
    e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const auto before=e.position;
    if(!e.railCarrier) {
        // Freeze skips ordinary AI friction, then multiplies native friction
        // by .01. Fractional recurrence preserves that30Hz endpoint and keeps
        // knockback/collision impulses without making the actor immovable.
        auto velocity=horizontal(e.velocity);
        const Vector3 travel{advanceLobHeight(velocity.x,0,retention,dt)*timeScale,0,
                             advanceLobHeight(velocity.z,0,retention,dt)*timeScale};
        moveMonster(e,mul(travel,1/dt),dt);
        const auto moved=sub(e.position,before);
        e.velocity={std::abs(moved.x-travel.x)<.0001f?velocity.x:0,0,
                    std::abs(moved.z-travel.z)<.0001f?velocity.z:0};
        // A capacity-delayed Gusher shot restores this momentum on retry.
        // Keep the selected projectile, but do not resurrect pre-freeze speed.
        if(e.headless)e.headless->momentum=mul(horizontal(e.velocity),1/(content->headless(e.monster)->scale*30));
    }
    // Ordinary frozen NPCs retain their collision damage and vulnerabilities.
    if(content->monster(e.monster)->contact&&
       segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
       arena.sight(e.position,player.position)) {
        const auto *g=content->gaper(e.monster);const auto *h=content->headless(e.monster);
        contactMonsterPlayer(e,g?g->contact:h?h->contact:10);
    }
}

float Simulation::enemyTimeScale(const Enemy &e) const {
    return e.affectedBy(EnemyStatus::Slow)?content->enemyStatuses(e.monster)->slow->timeScale:1;
}
float Simulation::enemyShotTimeScale(const Enemy &e) const {
    return e.affectedBy(EnemyStatus::Slow)?content->enemyStatuses(e.monster)->slow->projectileTimeScale:1;
}
Vector3 Simulation::slowEnemyMotion(const Enemy &e,Vector3 before,Vector3 after,float retention) const {
    const float t=enemyTimeScale(e);
    if(t==1)return after;
    const auto carried=mul(before,retention),impulse=sub(after,carried);
    // AddVelocity scales its impulse by t before the base update's rational
    // friction. Keep stored velocity unscaled; displacement separately uses t.
    return mul(add(carried,mul(impulse,t)),1/(retention+t-retention*t));
}

void Simulation::stepFearMotion(Enemy &e,Vector3 &momentum) {
    const auto *profile=content->enemyStatuses(e.monster);
    if(!profile||!profile->fear||!e.statuses||e.railCarrier)return;
    const auto &p=*profile->fear;auto &r=e.statuses->flee;
    // Headless .75 friction precedes EvadeTarget, but AddVelocity divides by
    // accumulated friction; the impulse cancels that factor. Gaper applies
    // .8 after EvadeTarget, damping both old momentum and the new impulse.
    const bool headless=content->headless(e.monster)!=nullptr;
    r.tick=e.statuses->ticks+1;r.momentum=headless?mul(momentum,p.retention):momentum;
    const auto before=momentum;
    const auto target=resolvedEnemyTarget(e);
    float retention=stepEvaderMotion(e,p,r,&target)*p.retention;
    if(!headless)r.momentum=mul(r.momentum,p.retention);
    if(r.evadeChecks>0){r.momentum=mul(r.momentum,profile->fearAlertRetention);retention*=profile->fearAlertRetention;}
    momentum=slowEnemyMotion(e,before,r.momentum,retention);
}

Vector3 Simulation::confusedTarget(Enemy &e) {
    if(!e.affectedBy(EnemyStatus::Confusion))return resolvedEnemyTarget(e);
    const auto &p=*content->enemyStatuses(e.monster);auto &r=*e.statuses;
    if(!r.confusedTarget||(r.ticks+1)%unsigned(p.confusionRefreshFrames)==0) {
        const float radius=combatRng.real(0,1)*combatRng.real(0,1)*p.confusionRadius;
        auto target=add(e.position,rotateY({radius,0,0},combatRng.real(0,2*Pi)));
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        target.x=std::clamp(target.x,bounds.min.x+e.radius,bounds.max.x-e.radius);
        target.z=std::clamp(target.z,bounds.min.z+e.radius,bounds.max.z-e.radius);
        // Native rectangular-room clamping becomes legal physical canyon
        // floor. Preserve the draw count; shorten the same ray around cover.
        for(int n=0;n<12&&(arena.roomAt(target)!=room||arena.blocked(target,e.radius));++n)
            target=mul(add(target,e.position),.5f);
        if(arena.roomAt(target)!=room||arena.blocked(target,e.radius))target=e.position;
        r.confusedTarget=target;
    }
    return *r.confusedTarget;
}
} // namespace dw
