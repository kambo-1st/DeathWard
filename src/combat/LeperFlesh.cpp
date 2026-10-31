#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::flushLeperFleshShot(Enemy &e) {
    if(!e.leperFlesh||e.leperFlesh->pendingShots.empty())return true;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &x){return x.alive;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()>=limits.queuedEvents||size_t(live+queued)>=limits.projectiles)return false;
    queueRoot(e.leperFlesh->pendingShots.front());e.leperFlesh->pendingShots.clear();return true;
}

void Simulation::leperFleshDeath(Enemy &e) {
    const auto &p=*content->leperFlesh(e.monster);
    if(!e.leperFlesh)e.leperFlesh=LeperFleshRuntime{};
    auto &r=*e.leperFlesh;if(r.deathReleased)return;r.deathReleased=true;
    // Source lead is .1 * native distance * target velocity per source frame.
    // Convert each quantity explicitly; this is not a fixed-time aim offset.
    const float nativeDistance=planarDistance(e.position,player.position)/p.scale;
    const auto nativeVelocity=mul(horizontal(player.velocity),1/(p.scale*30));
    const auto target=add(player.position,mul(nativeVelocity,p.prediction*nativeDistance*p.scale));
    const auto delta=horizontal(sub(target,e.position));
    const auto direction=length(delta)>0?mul(delta,1/length(delta)):Vector3{};
    const auto velocity=add(mul(direction,p.shotSpeed),{0,p.shotUp,0});
    Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
    shot.position=shot.origin=add(e.position,{0,p.shotHeight-.85f,0});
    shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shotDamage;
    shot.projectileRadius=p.shotRadius;shot.projectileLife=p.shotLife;
    shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.shotRetention;
    shot.projectileTint={179,138,152,255};
    r.pendingShots.push_back(shot);audioCues.push(AudioCueKind::MonsterAttack,e.position);
    flushLeperFleshShot(e);
}

void Simulation::updateLeperFlesh(Enemy &e,float dt) {
    const auto &p=*content->leperFlesh(e.monster);
    if(!e.leperFlesh)e.leperFlesh=LeperFleshRuntime{};
    auto &r=*e.leperFlesh;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    auto contactDeath=[&] {
        Event death;death.type=EventType::Damage;death.target=e.id;death.position=e.position;
        death.damage=e.hp+1;death.execution=true;death.context.sourceEntity=e.id;
        e.selfDetonated=true;r.momentum={};e.velocity={};queueRoot(death);
    };
    // Retain contact consumption if the bounded event queue was full.
    if(e.selfDetonated){contactDeath();return;}
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    const bool stunned=e.state==EnemyState::Stunned;
    if(stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady&&!stunned) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized)r.initialized=true;
            else {
                const auto delta=horizontal(sub(player.position,e.position));
                const auto direction=length(delta)>0?mul(delta,1/length(delta)):Vector3{};
                const auto random=rotateY({1,0,0},combatRng.real(0,2*Pi));
                // Native direct velocity addition precedes shared friction.
                r.momentum=mul(add(r.momentum,mul(add(direction,mul(random,p.randomWeight)),p.force)),p.retention);
                r.animation=float((r.ticks-1)%p.idleFrames)/p.idleFrames;
            }
            // Blood and droplets are cosmetic. They never create damaging creep
            // or a live shooting attack that the source flesh does not have.
            if(r.ticks%p.trailPeriod==0)
                effectVisual({e.position.x,.025f,e.position.z},combatRng.real(p.trailMin,p.trailMax),7,p.trailLife);
            if(r.ticks%p.particlePeriod==0)effectVisual(e.position,.12f,7,.3f);
            e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position;
        if(!e.railCarrier&&!stunned)moveMonster(e,mul(r.momentum,p.scale*30),step);
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        // Walls-only floating actors may pass over cover. Actual height still
        // matters for contact: a flesh chunk on top of a rock cannot hit below.
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
           arena.sight(e.position,player.position)) {
            hurtPlayer(p.contact,{0,0,e.id,-1});contactDeath();return;
        }
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=player.position;
}
} // namespace dw
