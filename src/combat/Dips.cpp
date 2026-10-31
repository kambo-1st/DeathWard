#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::flushSlideDeath(Enemy &e) {
    if(!e.slide||e.slide->deathShot.empty())return true;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+1>limits.queuedEvents||projectiles.size()+size_t(queued)+1>limits.projectiles)return false;
    if(!queueRoot(e.slide->deathShot.front()))return false;
    e.slide->deathShot.clear();return true;
}
void Simulation::slideDeath(Enemy &e) {
    const auto &p=*content->slide(e.monster);
    if(p.deathShot) {
        const auto &d=*p.deathShot;const float dist=distance(e.position,player.position);
        const auto target=add(player.position,mul(player.velocity,d.prediction*dist/(p.scale*30)));
        auto direction=unit(horizontal(sub(target,e.position)));if(length(direction)<.001f)direction=e.facing;
        auto velocity=mul(direction,d.speed);velocity.y=d.up;
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin=add(e.position,{0,d.height-.85f,0});
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=d.damage;
        shot.projectileLife=d.life;shot.projectileRadius=d.radius;shot.projectileGravity=d.gravity;
        shot.projectileFlightRetention=d.retention;shot.projectileKind=ProjectileKind::Yellow;
        if(!e.slide)e.slide=SlideRuntime{};
        e.slide->deathShot.clear();e.slide->deathShot.push_back(shot);flushSlideDeath(e);
    }
    if(!p.child)return;
    // Squirts use a fixed horizontal pair; Splurt samples two independent axes.
    for(float sign:{-1.f,1.f}) {
        const auto direction=p.secondAttackFrames?rotateY({1,0,0},combatRng.real(0,2*Pi)):Vector3{sign,0,0};
        Vector3 impulse{};
        if(p.secondAttackFrames)impulse=mul(direction,combatRng.real(p.childImpulseMin,p.childImpulseMax)*p.scale*30);
        const auto before=pendingMonsters_.size();
        queueMonster(p.child,add(e.position,mul(direction,p.childOffset)),0,e.generation+1,false,1,0,0,0,-1,{},true,{},impulse);
        if(p.secondAttackFrames&&pendingMonsters_.size()>before) {
            // Native children enter Move and receive one immediate update.
            SlideRuntime born;born.initialized=true;born.phase=2;born.frame=1;born.ticks=1;
            born.momentum=mul(impulse,content->slide(p.child)->moveRetention/(p.scale*30));
            pendingMonsters_.back().slide=born;
            pendingMonsters_.back().impulse=mul(born.momentum,p.scale*30);
        }
    }
}

void Simulation::updateSlide(Enemy &e,float dt) {
    const auto &p=*content->slide(e.monster);if(!e.slide)e.slide=SlideRuntime{};auto &r=*e.slide;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=r.phase==1?EnemyState::Windup:EnemyState::Ready;
        return;
    }
    const bool swims=p.floodedPits&&arena.swimmingRoom(room);
    const auto emitCreep=[&] {
        if(!r.pendingCreep)return true;
        if(hazards.size()>=limits.hazards)return false;
        const auto &c=*p.creep;
        Hazard h;h.kind=HazardKind::Tar;h.position=h.origin=*r.pendingCreep;h.position.y=.85f;
        h.delay=0;h.radius=c.radius;h.damage=0;h.duration=float(c.frames)/30;
        h.fadeDuration=float(c.fadeFrames)/30;h.fadeScale=c.fadeScale;h.fadeOnRoomClear=true;
        h.tint={37,32,41,210};h.context.sourceEntity=e.id;addHazard(h);
        r.pendingCreep.reset();++r.creepPatches;return true;
    };
    const bool pending=r.pendingCreep.has_value();
    if(!emitCreep()){e.velocity={};return;}
    if(pending)e.velocity=mul(r.momentum,p.scale*30);
    // External knockback and Dinga's radial push feed the next source decision.
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized)r.initialized=true;
            else if(!p.targeted) {
                if(r.phase==0||r.phase==3) {
                    if(r.phase==3||combatRng.bounded(unsigned(p.chance))==0) {
                        const bool aimed=p.chainFrame&&combatRng.bounded(unsigned(p.aimChance))==0;
                        const auto direction=aimed?unit(horizontal(sub(player.position,e.position))):rotateY({1,0,0},combatRng.real(0,2*Pi));
                        const float impulse=combatRng.real(p.impulseMin,p.impulseMax);
                        r.momentum=add(r.momentum,mul(direction,impulse));
                        r.phase=2;r.frame=0;++r.dashes;
                    }
                    r.momentum=mul(r.momentum,p.idleRetention);
                } else {
                    if(p.chainFrame) {
                        ++r.frame;
                        if(r.frame==p.chainFrame&&combatRng.bounded(unsigned(p.chainChance))==0){r.phase=3;++r.chains;}
                        else if(r.frame>=p.moveFrames){r.phase=0;r.frame=0;}
                    } else if(length(r.momentum)<p.stopSpeed){r.phase=0;r.frame=0;}
                    r.momentum=mul(r.momentum,p.moveRetention);
                }
            } else {
                float retention=p.moveRetention;
                if(r.phase==0) {
                    // Native IsFrame(5, InitSeed) additionally gates its 1/5 draw.
                    // Actor source ticks/ID provide a deterministic local offset.
                    if(combatRng.bounded(unsigned(p.chance))==0&&(r.ticks+e.id)%unsigned(p.checkFrames)==0) {
                        r.phase=1;r.frame=0;r.collisions=0;r.secondDash=false;++r.dashes;
                    }
                    retention*=p.idleRetention;
                } else if(r.phase==1) {
                    ++r.frame;
                    const int launch=r.secondDash?p.secondLaunchFrame:p.launchFrame;
                    const int frames=r.secondDash?p.secondAttackFrames:p.attackFrames;
                    if(r.frame==launch) {
                        const auto delta=unit(horizontal(sub(player.position,e.position)));
                        r.momentum=add(r.momentum,mul(delta,p.impulseMin/retention));
                        e.facing=delta;++r.launches;audioCues.push(AudioCueKind::MonsterAttack,e.position);
                    }
                    if(r.frame>=frames){r.phase=2;r.frame=0;r.slideFrames=0;}
                } else {
                    ++r.slideFrames;
                    if(r.slideFrames<p.sustainFrames)r.momentum=add(r.momentum,mul(unit(r.momentum),p.sustainForce/retention));
                    else if(p.secondAttackFrames) {
                        if(length(r.momentum)<p.slowSpeed) {
                            r.phase=r.secondDash?0:1;r.frame=0;
                            if(!r.secondDash){r.secondDash=true;++r.dashes;}
                        }
                    } else if(length(r.momentum)<p.stopSpeed){r.phase=0;r.frame=0;}
                    else if(length(r.momentum)<p.slowSpeed)retention*=p.slowRetention;
                    if(p.secondAttackFrames) {
                        // Source switches state before selecting the brake threshold.
                        const bool firstSlide=!r.secondDash&&r.phase==2;
                        if(r.slideFrames>(firstSlide?p.firstBrake:p.secondBrake))retention*=p.collisionRetention;
                    } else {
                        if(r.blocked)++r.collisions;
                        if(r.collisions>p.collisionFrames)retention*=p.collisionRetention;
                    }
                }
                r.momentum=mul(r.momentum,retention);
            }
            r.blocked=false;
            if(p.creep&&(r.phase==2||(r.phase==1&&r.frame>=p.launchFrame))) {
                const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(remaining))*30+1e-4)));
                if(globalTick%uint64_t(p.creep->interval)==0) {
                    r.pendingCreep=e.position;
                    if(!emitCreep()){e.velocity={};return;}
                }
            }
            r.animation=std::fmod(r.animation+1.f/float(r.phase==0?p.idleFrames:p.moveFrames),1.f);
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto wanted=mul(r.momentum,p.scale*30),before=e.position;
        if(!e.railCarrier) {
            // Reach the actual contact point instead of rejecting a complete
            // render-step displacement. Fast slides must stop at the same wall
            // position at 30 and 120 Hz.
            for(int axis=0;axis<2;++axis) {
                const auto start=e.position;const auto delta=axis==0?Vector3{wanted.x*step,0,0}:Vector3{0,0,wanted.z*step};
                if(length(delta)<1e-7f)continue;
                auto legal=[&](float f){const auto at=add(start,mul(delta,f));return swims?(!arena.swimBlocked(at,e.radius,room)&&arena.swimClear(start,at,e.radius,room)):(!arena.blocked(at,e.radius)&&arena.clear(start,at,e.radius));};
                if(legal(1)){e.position=add(start,delta);continue;}
                float lo=0,hi=1;
                for(int n=0;n<16;++n){const float mid=(lo+hi)/2;if(legal(mid))lo=mid;else hi=mid;}
                e.position=add(start,mul(delta,lo));r.blocked=true;
                if(axis==0)r.momentum.x=0;else r.momentum.z=0;
            }
            e.velocity=mul(r.momentum,p.scale*30);
        }
        if(length(e.velocity)>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
        }
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.state=r.phase==1?EnemyState::Windup:EnemyState::Ready;
    e.stateTime=r.phase==1?float((r.secondDash?p.secondAttackFrames:p.attackFrames)-r.frame)/30:0;
    e.target=player.position;
}
} // namespace dw
