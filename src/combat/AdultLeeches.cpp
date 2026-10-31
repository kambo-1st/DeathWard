#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootAdultLeech(Enemy &e,int ring) {
    auto &r=*e.adultLeech;const auto &p=content->adultLeech(e.monster)->shots[size_t(ring)];
    if(r.pendingShots.empty()) {
        r.pendingRing=ring;
        const auto origin=add(e.position,{r.chargeSign*p.offset,0,0});
        for(int n=1;n<=p.count;++n) {
            const float angle=float(n)*2*Pi/float(p.count);
            Vector3 velocity{std::cos(angle)*p.speed,combatRng.real(p.upMin,p.upMax),std::sin(angle)*p.speed};
            Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
            shot.position=add(origin,{0,p.height-.85f,0});shot.origin=origin;
            shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.damage;
            shot.projectileLife=p.life;shot.projectileRadius=p.radius;shot.projectileGravity=p.gravity;
            shot.projectileFlightRetention=p.retention;r.pendingShots.push_back(shot);
        }
    }
    const auto count=r.pendingShots.size();
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+count>limits.queuedEvents||
       projectiles.size()+size_t(queued)+count>limits.projectiles)return false;
    for(const auto &shot:r.pendingShots)queueRoot(shot);
    r.pendingShots.clear();r.pendingRing=-1;
    if(ring==0)++r.wallRings;else ++r.landingRings;
    audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

void Simulation::updateAdultLeech(Enemy &e,float dt) {
    const auto &p=*content->adultLeech(e.monster);auto &r=*e.adultLeech;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    // Own momentum deliberately ignores external knockback, as for Repentance Leeches.
    const auto heading=[&] {
        const float angle=combatRng.real(-Pi/4,Pi/4);
        r.heading={std::cos(angle),0,std::sin(angle)};
        if(combatRng.bounded(2)==0)r.heading.x=-r.heading.x;
        if(combatRng.bounded(2)==0&&r.heading.z*(player.position.z-e.position.z)<0)r.heading.z=-r.heading.z;
    };
    const auto legalGround=[&](Vector3 point) {
        const auto &b=arena.rooms[size_t(room)].bounds;
        return point.x>=b.min.x+e.radius&&point.x<=b.max.x-e.radius&&
               point.z>=b.min.z+e.radius&&point.z<=b.max.z-e.radius&&!arena.blocked(point,e.radius);
    };
    const auto cue=[&](AudioCueKind kind){audioCues.push(kind,e.position);};
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized)r.initialized=true;
            else if(r.pendingRing>=0)shootAdultLeech(e,r.pendingRing);
            else switch(r.phase) {
            case AdultLeechPhase::Wander: {
                if(r.recovery>0){--r.recovery;r.momentum=mul(r.momentum,p.recoveryRetention);break;}
                if(length(r.heading)<.001f)heading();
                r.momentum=add(mul(r.momentum,p.walkRetention),mul(r.heading,p.walkForce));
                if(!arena.blocked(e.position,.05f)) {
                    if(combatRng.bounded(unsigned(p.headingChance))==0)heading();
                    if(r.blocked)r.heading=mul(r.heading,-1);
                } else if(combatRng.bounded(unsigned(p.headingChance))==0) {
                    // Source grid helper chooses free floor. Use nearby real canyon
                    // floor rather than introducing Isaac's rectangular tile grid.
                    for(int i=0;i<16;++i) {
                        auto point=add(e.position,rotateY({p.grid*p.scale,0,0},float(i)*Pi/8));
                        if(legalGround(point)){r.heading=unit(horizontal(sub(point,e.position)));break;}
                    }
                }
                r.blocked=false;r.walkPhase=std::fmod(r.walkPhase+1.f/float(p.walkFrames),1.f);
                const auto delta=mul(horizontal(sub(player.position,e.position)),1/p.scale);
                if(!r.burrowUsed&&e.hp/e.maxHp<p.healthThreshold&&
                   (std::abs(delta.z)>std::abs(delta.x)||std::abs(delta.z)>p.burrowDistance)&&
                   combatRng.bounded(unsigned(p.burrowChance))==0&&!arena.blocked(e.position,.05f)) {
                    r.phase=AdultLeechPhase::Burrow;r.frame=0;r.burrowUsed=true;++r.burrows;
                    const auto center=arena.rooms[size_t(room)].center;const float grid=p.grid*p.scale;
                    r.anchor={center.x+std::round((e.position.x-center.x)/grid)*grid,e.position.y,
                              center.z+std::round((e.position.z-center.z)/grid)*grid};
                    if(arena.flightBlocked(r.anchor,e.radius,room))r.anchor=e.position;
                } else if(combatRng.bounded(unsigned(p.chargeChance))==0&&std::abs(delta.z)<p.alignment) {
                    r.phase=AdultLeechPhase::Charge;r.chargeSign=delta.x<0?-1.f:1.f;r.gain=p.initialGain;
                    ++r.charges;cue(AudioCueKind::Warning);
                }
                break;
            }
            case AdultLeechPhase::Charge: {
                if(r.blocked) {
                    if(length(r.impactVelocity)>p.impactSpeed&&dot(unit(r.impactVelocity),r.impactNormal)>p.impactDot) {
                        r.momentum=sub(r.momentum,mul(r.impactNormal,p.recoil));r.recovery=p.recoveryFrames;
                        ++r.impacts;cue(AudioCueKind::StoneHit);shootAdultLeech(e,0);
                    }
                    r.phase=AdultLeechPhase::Wander;r.blocked=false;++r.stops;
                    r.momentum=mul(r.momentum,p.chargeRetention);break;
                }
                const auto delta=mul(horizontal(sub(player.position,e.position)),1/p.scale);
                const float steer=delta.z>p.steerDeadzone?p.steer:delta.z<-p.steerDeadzone?-p.steer:0;
                r.momentum=add(mul(r.momentum,p.chargeRetention),{r.gain*r.chargeSign,0,std::clamp(r.gain*steer,-p.steerCap,p.steerCap)});
                if(r.gain<1||std::abs(delta.x)<p.gainRange)r.gain=std::min(p.maxGain,r.gain+p.gainStep);
                r.walkPhase=std::fmod(r.walkPhase+1.f/float(p.walkFrames),1.f);break;
            }
            case AdultLeechPhase::Burrow:
                ++r.frame;r.momentum=add(mul(r.momentum,p.burrowRetention),mul(horizontal(sub(r.anchor,e.position)),p.burrowPull/p.scale));
                if(r.frame==p.burrowSound)cue(AudioCueKind::StoneHit);
                if(r.frame==p.burrowHit){r.intangible=true;cue(AudioCueKind::MonsterAttack);}
                if(r.frame>=p.burrowFrames){r.phase=AdultLeechPhase::Hidden;r.hidden=1;r.momentum={};}
                break;
            case AdultLeechPhase::Hidden:
                ++r.hidden;r.momentum={};
                if(r.hidden>p.hiddenFrames&&combatRng.bounded(unsigned(p.emergeChance))==0) {
                    auto point=player.position;
                    // A larger 3D hull may not fit where the player stands. Keep
                    // the closest legal landing; never teleport into a canyon wall.
                    if(!legalGround(point)) {
                        bool found=false;
                        for(int radius=1;radius<=16&&!found;++radius)for(int i=0;i<16;++i) {
                            auto trial=add(player.position,rotateY({float(radius)*.25f,0,0},float(i)*Pi/8));
                            if(legalGround(trial)){point=trial;found=true;break;}
                        }
                        if(!found)point=e.position;
                    }
                    e.position=point;e.position.y=.85f;r.phase=AdultLeechPhase::Fall;r.frame=0;r.anchored=false;
                    cue(AudioCueKind::Warning);
                }
                break;
            case AdultLeechPhase::Fall: {
                ++r.frame;
                if(r.frame<=p.fallHit) {
                    auto target=player.position;
                    if(!arena.clear(e.position,target,e.radius)) {
                        const auto path=arena.path(e.position,target,e.radius);
                        target=path.empty()?e.position:path.front();
                    }
                    const auto delta=mul(horizontal(sub(target,e.position)),1/p.scale);const float range=length(delta);
                    if(range>1)r.momentum=add(mul(r.momentum,p.followRetention),mul(unit(delta),std::min(range*.1f,2.f)*p.followForce));
                    else r.momentum=mul(r.momentum,.5f);
                } else if(r.anchored)r.momentum=add(mul(r.momentum,p.settleRetention),mul(horizontal(sub(r.anchor,e.position)),1/p.scale));
                else r.momentum=mul(r.momentum,p.freeRetention);
                if(r.frame==p.fallHit) {
                    r.intangible=false;r.momentum={};r.anchor=e.position;r.anchored=true;++r.landings;
                    cue(AudioCueKind::StoneHit);shootAdultLeech(e,1);
                }
                if(r.frame==p.fallSound){r.anchored=false;cue(AudioCueKind::StoneHit);}
                if(r.frame>=p.fallFrames){r.phase=AdultLeechPhase::Wander;r.anchored=false;}
                break;
            }
            }
        }
        const float step=std::min(remaining,1.f/30-r.clock);const auto before=e.position;
        const auto wanted=r.pendingRing>=0?Vector3{}:mul(r.momentum,p.scale*30);
        const bool grounded=r.phase==AdultLeechPhase::Fall&&r.intangible;
        if(grounded){e.position=arena.move(before,mul(wanted,step),e.radius);e.velocity=mul(sub(e.position,before),1/step);}
        else {
            // Sweep each sliding axis up to the real wall, rather than discarding
            // the whole render-frame displacement. Retain first-impact velocity
            // and zero the blocked momentum component across partial updates.
            Vector3 normal{};
            for(int axis=0;axis<2;++axis) {
                const auto delta=axis==0?Vector3{wanted.x*step,0,0}:Vector3{0,0,wanted.z*step};
                if(length(delta)<1e-8f)continue;
                if(arena.flightClear(e.position,add(e.position,delta),e.radius,room))e.position=add(e.position,delta);
                else {
                    float lo=0,hi=1;
                    for(int attempt=0;attempt<16;++attempt) {
                        const float mid=(lo+hi)*.5f;
                        if(arena.flightClear(e.position,add(e.position,mul(delta,mid)),e.radius,room))lo=mid;else hi=mid;
                    }
                    e.position=add(e.position,mul(delta,lo));
                    if(axis==0)normal.x=wanted.x>0?1.f:-1.f;else normal.z=wanted.z>0?1.f:-1.f;
                }
            }
            if(length(normal)>0) {
                if(!r.blocked){r.impactVelocity=r.momentum;r.impactNormal=unit(normal);}
                r.blocked=true;
                if(normal.x)r.momentum.x=0;
                if(normal.z)r.momentum.z=0;
            }
            e.position.y=arena.flightHeight(e.position,e.radius);e.velocity=mul(sub(e.position,before),1/step);
        }
        if(grounded&&length(horizontal(sub(wanted,e.velocity)))>.05f)
            r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        if(r.phase==AdultLeechPhase::Charge)e.facing={r.chargeSign,0,0};
        else if(std::abs(e.velocity.x)>.001f)e.facing={e.velocity.x>0?1.f:-1.f,0,0};
        if(!r.intangible&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
           arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
        }
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    r.visibility=r.phase==AdultLeechPhase::Hidden?0:r.phase==AdultLeechPhase::Burrow?
        std::clamp(1-float(r.frame)/float(p.burrowHit),0.f,1.f):1;
    e.lift=r.phase==AdultLeechPhase::Fall&&r.frame<p.fallHit?6.f*(1-float(r.frame)/float(p.fallHit)):0;
    // Intangibility is explicit; scripted damage must not inherit generic buried immunity.
    e.state=r.phase==AdultLeechPhase::Charge?EnemyState::Charging:r.phase==AdultLeechPhase::Wander?EnemyState::Ready:EnemyState::Windup;
    e.target=player.position;
}
} // namespace dw
