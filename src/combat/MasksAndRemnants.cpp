#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 maskFacing(Vector3 direction) {
    if(std::abs(direction.x)>std::abs(direction.z))return {direction.x<0?-1.f:1.f,0,0};
    return {0,0,direction.z<0?-1.f:1.f};
}
}
bool Simulation::flushKnightImpact(Enemy &e) {
    if(!e.knight||!e.knight->pendingImpact)return true;
    const auto *p=content->knight(e.monster);if(!p)return true;
    if(fireWaves.size()>=limits.fireWaves)return false;
    auto &r=*e.knight;FireWaveBurst burst;
    burst.id=nextEntity_++;burst.source=e.id;burst.room=room;burst.origin=r.pendingOrigin;
    burst.origin.y=.85f;burst.rules=p->impactWave;burst.context.sourceEntity=e.id;
    burst.context.damageSource=e.friendly?DamageSource::Ally:DamageSource::Enemy;
    burst.rayCount=3;
    // Native heading+180+90*i, i=-1..1: both sides and back, never into the wall.
    for(int i=0;i<3;++i)burst.directions[size_t(i)]=rotateY(r.pendingDirection,Pi/2+float(i)*Pi/2);
    fireWaves.push_back(std::move(burst));r.pendingImpact=false;++r.impactBursts;return true;
}
void Simulation::updateKnight(Enemy &e,float dt) {
    const auto &p=*content->knight(e.monster);
    if(!e.knight)e.knight=KnightRuntime{};
    auto &r=*e.knight;e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const auto stop=[&] {
        if(r.charging)++r.stops;
        r.charging=false;r.blocked=false;r.hasDestination=false;r.chargeDirection={};e.state=EnemyState::Ready;
    };
    const bool pending=r.pendingImpact;
    if(!flushKnightImpact(e)){e.velocity={};return;}
    if(pending)e.velocity=mul(r.momentum,p.scale*30);
    if(e.state==EnemyState::Stunned) {
        // External stun interrupts the committed direction; impact recovery is
        // its own source timer and is not the old generic stun/windup cycle.
        stop();e.state=EnemyState::Stunned;r.clock=0;r.momentum={};e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    const auto cellCenter=[&] {
        const auto origin=arena.rooms[size_t(room)].center;const float grid=p.grid*p.scale;
        auto center=e.position;center.x=origin.x+std::round((center.x-origin.x)/grid)*grid;
        center.z=origin.z+std::round((center.z-origin.z)/grid)*grid;
        return arena.blocked(center,e.radius)?e.position:center;
    };
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        if(!r.initialized){r.initialized=true;continue;}
        if(e.lift>0||r.liftVelocity>0) {
            e.lift+=r.liftVelocity*p.scale;r.liftVelocity-=p.impactGravity;
            if(e.lift<0){e.lift=0;r.liftVelocity=0;}
        }
        bool recovering=e.lift>0||r.liftVelocity>0||r.recovery>0;
        if(r.recovery>0&&e.lift<=0&&r.liftVelocity<=0)--r.recovery;
        if(r.charging) {
            if(r.blocked) {
                const auto incoming=r.impactVelocity,normal=r.impactNormal;
                const bool strong=p.recoveryFrames&&length(incoming)>p.impactSpeed&&
                    dot(unit(incoming),normal)>p.impactAlignment;
                if(strong) {
                    r.pendingOrigin=cellCenter();r.pendingDirection=unit(r.chargeDirection);
                    r.pendingImpact=true;++r.impacts;r.recovery=p.recoveryFrames;r.liftVelocity=p.impactLift;recovering=true;
                    // Native collision response subtracts5 times the incoming
                    // normal component, then applies the collision brake.
                    r.momentum=mul(sub(r.momentum,mul(normal,dot(incoming,normal)*p.impactRebound)),p.impactBrake);
                } else r.momentum=mul(r.momentum,p.impactBrake);
                stop();
                if(!flushKnightImpact(e)){r.clock=0;e.velocity={};return;}
            } else {
                r.momentum=add(mul(r.momentum,p.retention),r.chargeDirection);
                const float force=length(r.chargeDirection);
                // Source tests the old magnitude, then adds.07; it may overshoot4
                // by one increment, rather than clamping before the last step.
                if(force<p.chargeMaximum)r.chargeDirection=mul(unit(r.chargeDirection),force+p.chargeAcceleration);
                const auto grid=cellCenter();Vector3 correction{};
                if(std::abs(r.momentum.x)>std::abs(r.momentum.z))correction.z=(grid.z-e.position.z)*p.gridPull;
                else correction.x=(grid.x-e.position.x)*p.gridPull;
                if(arena.clear(e.position,add(e.position,correction),e.radius))e.position=add(e.position,correction);
            }
        } else if(recovering) {
            r.momentum=mul(r.momentum,p.recoveryRetention);
        } else {
            // Brainless calls MoveRandomly(true) before the shared grid helper.
            // Its radial destination is reused by both impulses, never an orbit
            // around Pon or a direct chase of the player.
            if(p.randomWalk) {
                if(r.hasDestination&&(planarDistance(e.position,r.destination)<p.randomArrival*p.scale||r.blocked||
                    (dot(r.momentum,r.momentum)<.1f&&combatRng.bounded(10)==0)))r.hasDestination=false;
                if(!r.hasDestination) {
                    const auto target=add(e.position,rotateY({p.randomDistance*p.scale,0,0},combatRng.real(0,2*Pi)));
                    if(arena.clear(e.position,target,e.radius)){r.destination=target;r.hasDestination=true;}
                }
                if(r.hasDestination)r.momentum=add(r.momentum,mul(unit(horizontal(sub(r.destination,e.position))),p.randomForce));
            }
            r.blocked=false;stepAxisWander(e,p,r);r.momentum=mul(r.momentum,p.retention);
            const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+1e-4)));
            if((globalTick+e.id)%uint64_t(p.checkFrames)==0) {
                auto target=add(player.position,mul(player.velocity,combatRng.real(0,p.prediction)/30));
                const auto &bounds=arena.rooms[size_t(room)].bounds;const float margin=p.alignment*p.scale;
                if(bounds.max.x-bounds.min.x>2*margin&&bounds.max.z-bounds.min.z>2*margin) {
                    target.x=std::clamp(target.x,bounds.min.x+margin,bounds.max.x-margin);
                    target.z=std::clamp(target.z,bounds.min.z+margin,bounds.max.z-margin);
                }
                r.predictedTarget=target;const auto grid=cellCenter(),delta=horizontal(sub(target,grid));
                if(std::min(std::abs(delta.x),std::abs(delta.z))<margin&&length(delta)<p.range*p.scale&&arena.sight(grid,target)) {
                    r.chargeDirection=mul(maskFacing(delta),p.chargeForce);r.charging=true;++r.charges;e.state=EnemyState::Charging;
                }
            }
        }
        if(r.charging)e.facing=unit(r.chargeDirection);
        else if(length(r.momentum)>.01f&&!recovering)e.facing=maskFacing(r.momentum);
        if(!recovering)r.walkFrame=(r.walkFrame+1)%p.walkFrames;
    }
    const auto wanted=mul(r.momentum,p.scale*30),before=e.position;
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    const auto goal=add(before,mul(wanted,dt));auto bounded=goal;
    bounded.x=std::clamp(bounded.x,bounds.min.x+e.radius,bounds.max.x-e.radius);
    bounded.z=std::clamp(bounded.z,bounds.min.z+e.radius,bounds.max.z-e.radius);
    const bool boundaryHit=planarDistance(bounded,goal)>.00001f;
    // Source combat is confined to one room. Open passages in debug/previews
    // must not let an indefinitely committed charge run into other rooms.
    moveMonster(e,boundaryHit?mul(sub(bounded,before),1/dt):wanted,dt);
    const auto lost=sub(wanted,e.velocity);
    if(length(lost)>.05f&&(boundaryHit||!arena.clear(before,goal,e.radius))) {
        r.blocked=true;r.impactVelocity=r.momentum;r.impactNormal=unit(horizontal(lost));r.hasDestination=false;
    }
    e.target=r.charging?r.predictedTarget:r.hasDestination?r.destination:e.position;
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
void Simulation::updateMaskArmor(Enemy &e,float dt) {
    const auto *p=content->maskArmor(e.monster);if(!p)return;
    if(!e.maskArmor)e.maskArmor=MaskArmorRuntime{};
    auto &r=*e.maskArmor;
    r.turnGrace=std::max(0.f,r.turnGrace-dt);
    const auto face=maskFacing(e.facing);
    if(r.initialized&&dot(face,r.facing)<.5f)r.turnGrace=float(p->turnGraceFrames)/30;
    r.facing=face;r.initialized=true;
    // The mask artwork and its protection must always show the same direction.
    e.facing=face;
}
bool Simulation::maskBlocks(const Enemy &e,const Event &event) const {
    if(!content->maskArmor(e.monster)||event.execution||event.areaDamage||event.armorPiercing||
       event.damageKind!=DamageKind::Physical)return false;
    // Installed6aa830 rejects a negative component on the facing axis. Side
    // hits (zero component) and rear hits pass; there is no angular cone.
    return dot(horizontal(event.direction),maskFacing(e.facing))<0;
}
void Simulation::reflectMaskHit(Enemy &e,const Event &event) {
    const auto *p=content->maskArmor(e.monster);
    if(!p||!p->reflect||event.hostile||!maskBlocks(e,event)||
       (e.maskArmor&&e.maskArmor->turnGrace>0))return;
    const auto incoming=unit(horizontal(event.direction));
    auto normal=maskFacing(e.facing);
    if(std::abs(dot(incoming,normal))<p->grazingThreshold) {
        const auto radial=unit(horizontal(sub(event.position,e.position)));
        if(length(radial)>.5f)normal=radial;
    }
    const auto outgoing=sub(incoming,mul(normal,2*dot(incoming,normal)));
    shootEnemy(e,outgoing,p->reflectionDamage,event.speed);
    if(!e.maskArmor)e.maskArmor=MaskArmorRuntime{};
    ++e.maskArmor->reflections;
}
bool Simulation::tryLinkedRemnant(Enemy &e,const Event &event) {
    const auto *p=content->linkedRemnant(e.monster);
    if(!p||e.monster!=p->source||e.hp>0||event.execution)return false;
    const float scale=e.maxHp/content->monsterHealth(e.monster,arena.profile.sourceStage);
    const auto spawn=add(e.position,rotateY({p->offset,0,0},combatRng.real(0,2*Pi)));
    e.monster=p->body;e.hp=e.maxHp=content->monsterHealth(p->body,arena.profile.sourceStage)*scale;
    e.maskArmor.reset();e.partner=0;e.linkedRemnant=LinkedRemnantRuntime{true,true};
    e.behavior={};e.state=EnemyState::Ready;e.stateTime=0;e.phase=0;e.cooldown=0;
    e.path.clear();e.pathTime=0;e.lift=0;e.knight=KnightRuntime{};
    // The original ID remains alive. A retained request prevents a full enemy
    // pool from swallowing the vulnerable child or clearing the room early.
    queueMonster(p->child,spawn,e.id,0,false,scale,0,0,0,-1,{},true);
    checkpointNeeded=true;return true;
}
bool Simulation::updateLinkedRemnant(Enemy &e) {
    const auto *p=content->linkedRemnant(e.monster);
    if(!p||e.monster!=p->body)return true;
    if(!e.linkedRemnant)e.linkedRemnant=LinkedRemnantRuntime{};
    auto &r=*e.linkedRemnant;
    if(r.waiting){e.velocity={};return false;}
    if(!r.initialized) {
        Enemy *nearest=nullptr;float best=1e30f;
        for(auto &other:enemies)if(other.alive&&other.monster==p->child&&!other.partner) {
            const float distance=planarDistance(e.position,other.position);
            if(distance<best){nearest=&other;best=distance;}
        }
        if(nearest){e.partner=nearest->id;nearest->partner=e.id;}
        r.initialized=true;
    }
    const auto *child=findEnemy(e.partner);
    if(!child||!child->alive||child->monster!=p->child||child->partner!=e.id) {
        e.alive=false;e.velocity={};effectVisual(e.position,.5f,1);return false;
    }
    return true;
}
void Simulation::finishLinkedRemnant(Enemy &e) {
    const auto *p=content->linkedRemnant(e.monster);if(!p)return;
    if(auto *other=findEnemy(e.partner);other&&other->partner==e.id) {
        if(e.monster==p->child&&other->monster==p->body) {
            other->alive=false;other->velocity={};effectVisual(other->position,.5f,1);
        }
        other->partner=0;
    }
    e.partner=0;
}
bool Simulation::flushLandingCreep(Enemy &e) {
    const auto *p=content->landingCreep(e.monster);if(!p)return true;
    if(!e.landingCreep)e.landingCreep=LandingCreepRuntime{};
    auto &r=*e.landingCreep;
    while(!r.pending.empty()) {
        if(hazards.size()>=limits.hazards)return false;
        Hazard h;h.kind=HazardKind::Creep;h.position=h.origin=r.pending.front();h.position.y=.85f;
        h.radius=p->radius;h.damage=p->damage;h.duration=float(p->frames)/30;h.delay=0;
        h.fadeDuration=float(p->fadeFrames)/30;h.fadeScale=p->fadeScale;h.fadeOnRoomClear=true;
        h.context.sourceEntity=e.id;h.tint={144,43,50,200};addHazard(h);
        r.pending.erase(r.pending.begin());++r.patches;
    }
    return true;
}
} // namespace dw
