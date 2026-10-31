#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootMawDeath(Enemy &e) {
    if(!e.maw||!e.maw->deathPending)return true;
    const auto &p=*content->maw(e.monster);
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||queue_.size()+size_t(p.deathShots)>limits.queuedEvents||
        projectiles.size()+size_t(queued+p.deathShots)>limits.projectiles)return false;
    for(int i=0;i<p.deathShots;++i) {
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin=e.position;shot.direction=rotateY({1,0,0},float(i)*2*Pi/float(p.deathShots));
        shot.speed=p.deathSpeed;shot.damage=p.deathDamage;shot.projectileLife=p.shot.life;
        queueRoot(shot);
    }
    e.maw->deathPending=false;return true;
}

void Simulation::updateMaw(Enemy &e,float dt) {
    const auto &p=*content->maw(e.monster);
    if(!e.maw)e.maw=MawRuntime{};
    auto &r=*e.maw;auto &cast=r.cast;
    if(!cast.initialized) {
        cast.initialized=true;cast.tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));
    }
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    e.cooldown=std::max(0.f,e.cooldown-dt);if(e.cooldown<.00001f)e.cooldown=0;
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        cast.clock=0;cast.attackFrame=-1;cast.fired=false;r.momentum={};e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    cast.clock+=dt;
    while(cast.clock+1e-6f>=1.f/30) {
        cast.clock=std::max(0.f,cast.clock-1.f/30);++cast.tick;
        if(cast.attackFrame>=0) {
            if(cast.attackFrame<p.shot.shootFrame||cast.fired)++cast.attackFrame;
            if(cast.attackFrame==p.shot.shootFrame&&!cast.fired) {
                const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
                if(limits.eventsPerChain&&queue_.size()<limits.queuedEvents&&projectiles.size()+size_t(queued)<limits.projectiles) {
                    Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
                    shot.position=shot.origin=e.position;shot.direction=unit(horizontal(sub(player.position,e.position)));
                    if(length(shot.direction)<.001f)shot.direction=e.facing;
                    shot.speed=p.shot.speed;shot.damage=p.shot.damage;shot.projectileLife=p.shot.life;shot.projectileRadius=p.shotRadius;
                    if(p.homing){shot.projectileKind=ProjectileKind::Homing;shot.projectileHoming=p.homing;}
                    cast.fired=queueRoot(shot);if(cast.fired)audioCues.push(AudioCueKind::MonsterAttack,e.position);
                }
            }
            if(cast.attackFrame>=p.shot.attackFrames) {cast.attackFrame=-1;cast.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
            else {e.state=EnemyState::Windup;e.stateTime=float(p.shot.attackFrames-cast.attackFrame)/30;}
        } else {
            r.momentum=add(r.momentum,mul(unit(horizontal(sub(player.position,e.position))),p.force/p.retention));
            if(p.shoots&&e.cooldown==0&&(cast.tick+e.id)%unsigned(p.shot.checkFrames)==0&&
                planarDistance(e.position,player.position)<p.shot.range&&arena.sight(e.position,player.position)) {
                cast.attackFrame=0;cast.fired=false;e.state=EnemyState::Windup;e.stateTime=float(p.shot.attackFrames)/30;
                e.cooldown=float(p.shot.cooldownFrames)/30;audioCues.push(AudioCueKind::Warning,e.position);
            }
        }
        r.momentum=mul(r.momentum,p.retention);
    }
    moveMonster(e,mul(r.momentum,p.scale*30),dt);
    e.facing=unit(horizontal(sub(player.position,e.position)));e.target=player.position;
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}

void Simulation::releaseEternalFly(Enemy &e) {
    const auto *p=content->eternalFly(e.monster);if(!p)return;
    // Holy Leech's death blast removes its companion; it never releases an
    // Attack Fly. Resolve ownership before the dead parent is erased.
    const auto *parent=findEnemy(e.partner);
    const auto *leech=parent?content->leech(parent->monster):nullptr;
    if(leech&&leech->child==e.monster){e.alive=false;return;}
    const int ticks=e.eternalFly?e.eternalFly->orbitTicks:0;
    if(ticks==0){e.alive=false;return;}
    e.monster=p->released;e.partner=0;e.maxHp=content->monsterHealth(e.monster,arena.profile.sourceStage);
    e.hp=std::min(e.hp,e.maxHp);e.radius=content->monster(e.monster)->radius;
    e.buzz=BuzzFlyRuntime{};e.buzz->healingTicks=ticks;e.buzz->healingDivisor=p->healingFrames;
    e.velocity={}; // Source orbit changes position directly; it adds no pursuit momentum.
    e.eternalFly.reset();e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;e.path.clear();e.behavior={};
}

void Simulation::updateEternalFly(Enemy &e,float dt) {
    const auto &p=*content->eternalFly(e.monster);
    if(!e.eternalFly)e.eternalFly=EternalFlyRuntime{};
    const auto *parent=findEnemy(e.partner);
    if(!parent||!parent->alive){releaseEternalFly(e);return;}
    auto &r=*e.eternalFly;
    if(!r.initialized) {
        r.initialized=true;r.phase=int(combatRng.bounded(10));
        r.tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));
    }
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    e.state=EnemyState::Ready;e.stateTime=0;r.clock+=dt;
    const auto before=e.position;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.tick;
        const bool hanger=parent->monster.type==90;
        const float ramp=std::min(1.f,float(r.orbitTicks)/float(hanger?30:p.growthFrames));
        float angle=float(r.tick)*p.phase*(hanger?.5f:1)+float(r.phase)*Pi/10;
        if(r.phase%2==0)angle=-angle;
        const auto destination=add(parent->position,{std::cos(angle)*(hanger?6:p.radiusX)*ramp,0,std::sin(angle)*(hanger?5:p.radiusZ)*ramp});
        e.position=add(e.position,mul(sub(destination,e.position),parent->monster.type==102?1:p.follow));
        // Invulnerable source orbit ignores scenery; retain visible flight height.
        e.position.y=arena.flightHeight(e.position,e.radius);++r.orbitTicks;
    }
    e.velocity=mul(sub(e.position,before),1/dt);
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
