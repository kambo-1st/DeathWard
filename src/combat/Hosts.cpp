#include "combat/Simulation.hpp"

namespace dw {
void Simulation::hostBlockedHit(Enemy &e,const Event &event) {
    const auto *p=content->host(e.monster);
    if(!p||!p->armored||event.execution||event.damageKind==DamageKind::Burning)return;
    if(!e.host)e.host=HostRuntime{};
    // Damage is accumulated before the next source update, not rounded once
    // per pellet. Hits during the attack do not add idle opening delay.
    if(e.host->frame<0&&event.damage>0)e.host->blockedDamage+=event.damage/p->healthScale;
}

void Simulation::updateHost(Enemy &e,float dt) {
    const auto &p=*content->host(e.monster);
    if(!e.host)e.host=HostRuntime{};
    auto &r=*e.host;
    if(!r.initialized){r.initialized=true;r.tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));}
    e.age+=dt;e.pathTime-=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.frame=-1;r.fired=false;r.exposed=false;r.clock=0;r.momentum={};r.blockedDamage=0;e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    const bool walk=p.motion==HostMotion::Walk, floating=p.motion==HostMotion::Float;
    if(!floating)r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.tick;++r.lifeTicks;
        if(r.blockedDamage>0) {
            r.delay=std::min(p.delayLimit,r.delay+int(std::min(r.blockedDamage,10000.f)+.5f)/2);
            if(r.blockedDamage>20)r.shake=true;
            r.blockedDamage=0;
        }
        const bool attacking=r.frame>=0;
        r.momentum=mul(r.momentum,attacking?p.attackRetention:p.retention);
        if(floating) {
            r.momentum.x+=r.momentum.x<0?-p.force:p.force;
            r.momentum.z+=r.momentum.z<0?-p.force:p.force;
        } else if(walk&&!attacking) {
            auto destination=player.position;
            if(!arena.clear(e.position,destination,e.radius)) {
                if(e.pathTime<=0){e.path=arena.path(e.position,destination,e.radius);e.pathTime=.6f;}
                while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.15f)e.path.erase(e.path.begin());
                destination=e.path.empty()?e.position:e.path.front();
            }
            const auto delta=horizontal(sub(destination,e.position));
            const auto force=steerMonsterBodies(e,mul(unit(delta),p.force*std::min(1.f,length(delta)/(20*p.scale))));
            r.momentum=add(r.momentum,force);
        }
        if(attacking) {
            if(walk&&r.cooldown>0)--r.cooldown;
            if(r.frame<p.shootFrame||r.fired)++r.frame;
            if(r.frame==p.shootFrame&&!r.fired) {
                if(p.slam) {
                    if(hazards.size()<limits.hazards) {
                        const auto &slam=*p.slam;
                        auto aim=unit(horizontal(sub(player.position,e.position)));if(length(aim)<.001f)aim=e.facing;
                        Hazard wave;wave.kind=HazardKind::RockWave;wave.context.sourceEntity=e.id;
                        wave.origin=wave.position=wave.previous=add(e.position,mul(aim,slam.offset));
                        wave.position.y=wave.origin.y=wave.previous.y=.85f;
                        wave.delay=0;wave.duration=float(slam.wave.lifeFrames)/30;wave.radius=slam.wave.radius;
                        wave.damage=slam.wave.playerDamage;wave.velocity=mul(aim,slam.wave.spacing*30/float(slam.wave.stepFrames));
                        wave.rockWave=RockWaveRuntime{slam.wave,0,0,aim,Random(combatRng.next()),{wave.position}};
                        addHazard(wave);launchPlayer(e.position,slam);r.fired=true;
                        particleEffect(ParticleEffect::Stone,e.position,{0,1,0},.8f);
                        audioCues.push(AudioCueKind::StoneHit,e.position);
                    }
                } else {
                const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
                if(limits.eventsPerChain&&queue_.size()+p.volley.size()<=limits.queuedEvents&&
                   projectiles.size()+size_t(queued)+p.volley.size()<=limits.projectiles) {
                    auto aim=unit(horizontal(sub(player.position,e.position)));if(length(aim)<.001f)aim=e.facing;
                    const Vector3 side{-aim.z,0,aim.x};
                    for(auto coefficient:p.volley) {
                        auto velocity=mul(add(mul(aim,coefficient.x),mul(side,coefficient.y)),p.speed);
                        velocity=add(velocity,mul(horizontal(e.velocity),p.inheritVelocity));
                        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;shot.position=shot.origin=e.position;
                        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.damage;shot.projectileLife=p.life;
                        queueRoot(shot);
                    }
                    r.fired=true;audioCues.push(AudioCueKind::MonsterAttack,e.position);
                }
                }
            }
            if(r.frame>=p.frames){r.frame=-1;r.fired=false;r.delay=0;r.shake=false;}
        } else {
            const bool cadence=(r.tick+e.id)%unsigned(p.checkFrames)==0;
            if(r.delay==0) {
                r.shake=false;
                bool ready=false;
                if(walk) {
                    if(combatRng.bounded(unsigned(p.chance))==0) {
                        if(r.cooldown>0)--r.cooldown;
                        ready=r.cooldown==0&&cadence;
                    }
                } else if(cadence) {
                    if(r.cooldown>0)--r.cooldown;else ready=true;
                }
                if(ready&&planarDistance(e.position,player.position)<p.range&&arena.sight(e.position,player.position)) {
                    r.frame=0;r.fired=false;r.cooldown=p.cooldown;r.shake=false;
                    audioCues.push(AudioCueKind::Warning,e.position);
                }
            }
            // Source stationary delay uses global/entity cadence, mobile uses age.
            if(r.frame<0&&r.delay>0&&(walk?r.lifeTicks%unsigned(p.checkFrames)==0:cadence))--r.delay;
        }
        r.exposed=r.frame>=p.openFrame&&r.frame<p.closeFrame;
    }
    e.state=r.frame<0?EnemyState::Ready:r.exposed?EnemyState::Exposed:EnemyState::Windup;
    e.stateTime=r.frame<0?0:float(p.frames-r.frame)/30;e.cooldown=float(r.cooldown)/30;
    e.target=player.position;e.facing=unit(horizontal(sub(player.position,e.position)));
    const auto before=e.position,wanted=mul(r.momentum,p.scale*30);
    moveMonster(e,wanted,dt);
    if(floating) {
        const auto actual=sub(e.position,before),travel=mul(wanted,dt);
        if(std::abs(actual.x-travel.x)>.0005f)r.momentum.x=-r.momentum.x;
        if(std::abs(actual.z-travel.z)>.0005f)r.momentum.z=-r.momentum.z;
    }
    if(p.contact>0&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
        arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
void Simulation::launchPlayer(Vector3 origin,const HostSlamDefinition &rules) {
    // Native slam launches a grounded player, even through nearby scenery.
    // Horizontal collision remains grounded: the visual/physical hop grants no
    // new route across canyon walls or pits.
    if(player.launch||planarDistance(origin,player.position)>=rules.range)return;
    PlayerLaunch hop;hop.baseY=player.position.y;hop.up=rules.hop;hop.gravity=rules.gravity;hop.retention=rules.retention;
    hop.impulse=mul(unit(horizontal(sub(player.position,origin))),rules.push);player.launch=hop;
}
void Simulation::resetPlayerLaunch() {
    if(player.launch)player.position.y=player.launch->baseY;
    player.launch.reset();
}
} // namespace dw
