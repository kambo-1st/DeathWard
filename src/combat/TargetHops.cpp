#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 momentum(Vector3 velocity,Vector3 delta,bool jumping,const TargetHopDefinition &p) {
    const float distance=length(delta);
    // delta is expressed in native units. Near the destination the native
    // controller normalizes even its grounded, downscaled direction.
    const auto force=distance<p.nearRange?unit(delta):mul(delta,p.farForce*(jumping?1.f:p.groundFactor));
    return mul(add(velocity,force),p.retention);
}
bool airFrame(int frame,const TargetHopDefinition &p) {return frame>=p.jumpFrame&&frame<p.hopFrames;}
}

bool Simulation::hopRingLanded(Enemy &e) {
    const auto &p=*content->hopRings(e.monster);auto &r=*e.hopRings;
    auto at=e.position;at.y=.85f;
    r.pending.push_back({at,r.stage});
    r.stage=(r.stage+1)%int(p.stages.size());
    if(r.stage==0)++r.cycles;
    r.chainPending=r.stage!=0;
    return r.chainPending;
}
void Simulation::flushHopRings(Enemy &e) {
    const auto &p=*content->hopRings(e.monster);auto &r=*e.hopRings;
    while(!r.pending.empty()) {
        const auto volley=r.pending.front();const auto stage=p.stages.at(size_t(volley.stage));
        const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
        const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &shot){return shot.alive;});
        // A capacity limit delays a complete ring, never silently drops half of
        // one. At most one full sequence is retained; the next cycle waits.
        if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+size_t(stage.count)>limits.queuedEvents||
            size_t(live+queued+stage.count)>limits.projectiles)return;
        for(int i=0;i<stage.count;++i) {
            const float angle=2*Pi*float(i+1)/float(stage.count);
            const Vector3 velocity{std::cos(angle)*stage.speed,combatRng.real(p.upMin,p.upMax),std::sin(angle)*stage.speed};
            Event shot;shot.hostile=!e.friendly;shot.context.sourceEntity=e.id;
            shot.position=shot.origin=add(volley.position,{0,p.height-.85f,0});shot.direction=unit(velocity);
            shot.speed=length(velocity);shot.damage=p.damage;shot.projectileLife=p.life;shot.projectileRadius=p.radius;
            shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.flightRetention;
            queueRoot(shot);
        }
        ++r.volleys;r.pending.erase(r.pending.begin());
        audioCues.push(AudioCueKind::MonsterAttack,volley.position);
        particleEffect(ParticleEffect::Dirt,volley.position,{0,1,0},.65f);
    }
}

void Simulation::updateTargetHop(Enemy &e,float dt) {
    const auto p=e.targetHop&&e.targetHop->transformedFlight?*e.targetHop->transformedFlight:*content->targetHop(e.monster);
    if(!e.targetHop)e.targetHop=TargetHopRuntime{};
    auto &r=*e.targetHop;
    const bool pending=e.landingCreep&&!e.landingCreep->pending.empty();
    if(!flushLandingCreep(e)){e.velocity={};return;}
    if(pending)e.velocity=mul(r.momentum,p.scale*30);
    const auto *creep=content->landingCreep(e.monster);
    bool highHandled=e.leaper&&e.leaper->phase;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.auxiliary-=dt;
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);e.lift=0;
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    const bool stunned=e.state==EnemyState::Stunned;
    if(stunned) {
        e.stateTime-=dt;
        if(!r.airborne) {
            if(e.leaper)e.leaper->phase=0;
            r.targetReady=false;r.restartAtJump=false;r.frame=-1;r.counter=0;r.clock=0;r.arc=0;r.momentum={};e.velocity={};
            if(e.stateTime<=0)e.state=EnemyState::Ready;
            return;
        }
        // A local stun never drops an airborne actor into a river or rock.
        // Its committed destination continues only until the animation ends.
    }
    auto target=player.position;auto targetVelocity=player.velocity;bool hasTarget=!e.friendly;
    if(e.friendly) {
        float best=100000;e.partner=0;
        for(const auto &other:enemies)if(other.alive&&!other.friendly&&other.id!=e.id) {
            const float d=planarDistance(e.position,other.position);
            if(d<best){best=d;target=other.position;targetVelocity=other.velocity;e.partner=other.id;hasTarget=true;}
        }
    }
    const auto &bounds=arena.rooms.at(size_t(room)).bounds;
    auto snapped=[&](Vector3 at) {
        const float margin=std::max(e.radius,p.margin*p.scale),grid=p.grid*p.scale;
        auto axis=[&](float value,float low,float high) {
            if(low+margin>high-margin)return (low+high)*.5f;
            value=std::clamp(value,low+margin,high-margin);
            return std::clamp(low+grid*.5f+std::round((value-low-grid*.5f)/grid)*grid,low+margin,high-margin);
        };
        return Vector3{axis(at.x,bounds.min.x,bounds.max.x),.85f,axis(at.z,bounds.min.z,bounds.max.z)};
    };
    // Source rooms have a fixed grid and flat collision. Check our actual
    // stepped steering trajectory, not a straight teleport/endpoint arc. This
    // local geometry adaptation only rejects a route without a ground landing.
    auto safeLanding=[&](Vector3 at,Vector3 speed,Vector3 destination,int firstFrame) {
        for(int frame=firstFrame;frame<p.hopFrames;++frame) {
            const bool air=airFrame(frame,p);
            speed=momentum(speed,mul(horizontal(sub(destination,at)),1/p.scale),air,p);
            const auto delta=mul(speed,p.scale);
            at=air?arena.fly(at,delta,e.radius,room):arena.move(at,delta,e.radius);
        }
        at.y=.85f;
        return !arena.blocked(at,e.radius)&&!arena.reservedSupplyCache(at,e.radius);
    };
    const bool wasAir=r.airborne;
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized){r.initialized=true;r.lastGround=e.position;continue;}
        if(e.leaper&&e.leaper->phase) {advanceLeaper(e);highHandled=true;continue;}
        // The native controller draws both uniforms on every normal update,
        // including updates with a destination already committed.
        r.bonus=(p.bonusA>0?combatRng.real(0,p.bonusA):0)+(p.bonusB>0?combatRng.real(0,p.bonusB):0);
        if(r.targetReady) {
            if(r.frame>=0&&++r.frame>=p.hopFrames)r.frame=-1;
            r.airborne=airFrame(r.frame,p);
            if(r.frame==p.jumpFrame) {
                if(!safeLanding(e.position,r.momentum,r.destination,r.frame)) {
                    r.targetReady=false;r.airborne=false;r.frame=-1;r.counter=0;r.momentum={};
                    continue;
                }
                ++r.hops;
            }
            const bool landed=r.frame==p.landFrame;
            if(landed) {
                ++r.landings;
                if(creep)e.landingCreep->pending.push_back(e.position);
            }
            if(landed&&e.leaper)leaperLanded(e,false);
            const auto delta=mul(horizontal(sub(r.destination,e.position)),1/p.scale);
            const bool movementAir=r.airborne;
            const bool mayRelease=r.frame<0||(creep&&r.frame>=p.landFrame&&
                combatRng.bounded(unsigned(creep->releaseChance))!=0);
            const bool release=mayRelease&&(length(delta)<p.arrival||
                ((length(r.momentum)<p.stuckSpeed||r.counter>p.stuckFrames)&&
                 combatRng.bounded(unsigned(p.releaseChance))==0));
            if(release) {
                auto ground=e.position;ground.y=.85f;
                if(!r.airborne||!arena.blocked(ground,e.radius)) {
                    r.targetReady=false;r.counter=0;
                    if(creep&&r.airborne){r.airborne=false;r.frame=-1;++e.landingCreep->releases;}
                }
            }
            if(r.frame<0&&e.hopRings&&e.hopRings->chainPending) {
                // A chain deferred over unsafe3D ground resumes once the
                // committed flight has finished its safe landing.
                r.targetReady=false;r.counter=p.idleFrames;r.restartAtJump=true;
                e.hopRings->chainPending=false;
            }
            // Native state4 still applies its final impulse on the release tick.
            r.momentum=momentum(r.momentum,delta,movementAir,p);
            const bool restart=landed&&((content->eggy(e.monster)&&eggyLanded(e))||
                (e.hopRings&&hopRingLanded(e)));
            if(restart) {
                auto ground=e.position;ground.y=.85f;
                // Native2D can restart immediately. Our actual-height body
                // must have legal ground here before ending this flight early.
                if(!arena.blocked(ground,e.radius)) {
                    r.targetReady=false;r.airborne=false;r.frame=-1;r.counter=p.idleFrames;
                    r.restartAtJump=true;
                    if(e.eggy)++e.eggy->restarts;
                    if(e.hopRings)e.hopRings->chainPending=false;
                }
            }
        } else {
            r.momentum=mul(r.momentum,p.retention);
            const bool cycleWaiting=(e.hopRings&&e.hopRings->stage==0&&!e.hopRings->pending.empty())||
                (e.leaper&&e.leaper->pending.has_value());
            if(!stunned&&!cycleWaiting&&r.counter>=p.idleFrames) {
                const auto delta=horizontal(sub(target,e.position));
                const float range=(p.rangeBase+p.rangeBonus*r.bonus)*p.scale;
                r.pursuing=hasTarget&&length(delta)<range;
                auto candidate=r.pursuing?add(add(target,mul(delta,r.bonus/p.overshoot)),
                    mul(horizontal(targetVelocity),float(p.leadFrames)/30)):
                    add(e.position,rotateY({(p.wander+r.bonus)*p.scale,0,0},combatRng.real(0,2*Pi)));
                const auto blockedTarget=[&](Vector3 at) {
                    if(arena.blocked(at,e.radius)||arena.reservedSupplyCache(at,e.radius))return true;
                    if(creep)for(const auto &other:enemies)if(other.alive&&other.id!=e.id&&
                        !(other.targetHop&&other.targetHop->airborne)&&(!content->monster(other.monster)||!content->monster(other.monster)->flying)&&
                        planarDistance(at,other.position)<e.radius+other.radius)return true;
                    return false;
                };
                for(int attempt=0;attempt<= (creep?creep->searchAttempts:0);++attempt) {
                if(attempt){candidate=add(e.position,rotateY({(p.wander+r.bonus)*p.scale,0,0},combatRng.real(0,2*Pi)));r.pursuing=false;}
                auto destination=snapped(candidate);
                // Source grid cells coincide with the collision map. Our
                // generated rocks need not align with the four-unit target
                // grid: snapping a legal target into one can freeze a hopper
                // with zero overshoot forever. Retain its legal unsnapped
                // candidate in that case; the landing sweep still applies.
                if(arena.blocked(destination,e.radius)) {
                    const float margin=std::max(e.radius,p.margin*p.scale);
                    auto axis=[&](float value,float low,float high) {
                        return low+margin>high-margin?(low+high)*.5f:std::clamp(value,low+margin,high-margin);
                    };
                    destination={axis(candidate.x,bounds.min.x,bounds.max.x),.85f,
                                 axis(candidate.z,bounds.min.z,bounds.max.z)};
                }
                if(!blockedTarget(destination)&&
                    safeLanding(e.position,r.momentum,destination,r.restartAtJump?p.jumpFrame:1)) {
                    r.destination=destination;r.targetReady=true;r.frame=r.restartAtJump?p.jumpFrame:0;r.counter=0;
                    if(e.hopRings)e.hopRings->animationStage=e.hopRings->stage;
                    if(r.restartAtJump){r.airborne=true;++r.hops;r.restartAtJump=false;}
                    break;
                }
                }
            }
        }
        ++r.counter;
        if(e.leaper&&!stunned&&hasTarget) {
            tryLeaperJump(e,target);
            highHandled|=e.leaper->phase!=0;
        }
    }
    flushLandingCreep(e);
    if(e.hopRings&&!stunned)flushHopRings(e);
    if(e.leaper&&!stunned)flushLeaperLanding(e);
    if(highHandled) {
        const auto &high=*content->leaper(e.monster);const auto &leap=*e.leaper;
        if(r.airborne) {
            const float frame=float((leap.phase==1?0:high.upFrames)+leap.frame)+r.clock*30;
            r.arc=std::clamp((frame-high.jumpFrame)/float(high.upFrames+high.landFrame-high.jumpFrame),0.f,1.f);
            e.position.y=arena.flightHeight(e.position,e.radius)+high.height*std::sin(Pi*r.arc);
        } else {e.position.y=.85f;r.arc=0;}
        e.velocity={};e.target=leap.target;e.facing=unit(horizontal(sub(leap.target,leap.start)));
        if(stunned&&e.stateTime>0)e.state=EnemyState::Stunned;
        else e.state=r.airborne?EnemyState::Jumping:leap.phase==1?EnemyState::Windup:EnemyState::Ready;
        if(!r.airborne&&!e.friendly&&distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
        }
        return;
    }
    auto before=e.position;
    if(wasAir&&!r.airborne) {
        auto grounded=e.position;grounded.y=.85f;
        // Moving/closing geometry can invalidate the takeoff prediction. Retain
        // the last legal point rather than embedding the actor in new geometry.
        if(arena.blocked(grounded,e.radius)) {
            e.position=r.lastGround;r.momentum={};r.targetReady=false;r.frame=-1;r.counter=0;
            before=e.position; // A corrective landing is not a damaging swept attack.
        } else e.position=grounded;
    }
    const auto delta=mul(r.momentum,p.scale*30*dt);
    e.position=r.airborne?arena.fly(e.position,delta,e.radius,room):arena.move(e.position,delta,e.radius);
    if(r.airborne) {
        r.arc=std::clamp((float(r.frame-p.jumpFrame)+r.clock*30)/float(p.landFrame-p.jumpFrame),0.f,1.f);
        e.position.y+=p.height*std::sin(Pi*r.arc);
    } else {e.position.y=.85f;r.arc=0;}
    auto ground=e.position;ground.y=.85f;
    if(!arena.blocked(ground,e.radius))r.lastGround=ground;
    e.velocity=mul(sub(e.position,before),1/dt);
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    e.target=r.destination;
    if(stunned&&e.stateTime>0)e.state=EnemyState::Stunned;
    else e.state=r.airborne?EnemyState::Jumping:r.targetReady&&r.frame>=0&&r.frame<p.jumpFrame?EnemyState::Windup:EnemyState::Ready;
    if(!r.airborne)r.transformedFlight.reset();
    if(e.friendly) {
        const auto *other=findEnemy(e.partner);
        if(other&&other->alive&&e.auxiliary<=0&&distance(e.position,other->position)<e.radius+other->radius&&arena.sight(e.position,other->position)) {
            Event hit;hit.type=EventType::Damage;hit.target=other->id;hit.damage=28;queueRoot(hit);e.auxiliary=.7f;
        }
    } else if(segmentSphere(before,e.position,player.position,e.radius+.48f)<=1&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
    }
}
} // namespace dw
