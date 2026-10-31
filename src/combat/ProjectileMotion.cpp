#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateSourcePlanarMotion(Projectile &p,float elapsed) {
    if(!p.sourcePlanarMotion||!p.alive)return;
    p.planarClock+=elapsed;
    if(p.planarClock+1e-6f<1.f/30)return;
    p.planarClock=std::max(0.f,p.planarClock-1.f/30);
    const auto &m=*p.sourcePlanarMotion;
    auto velocity=horizontal(p.velocity);
    if(m.orbitDirection) {
        const auto delta=horizontal(sub(p.position,m.orbitCenter));
        const float radial=m.orbitRadius>0?
            .5f*std::clamp(1-length(delta)/m.orbitRadius,-1.f,1.f):.5f;
        const auto tangent=mul(Vector3{-delta.z,0,delta.x},float(m.orbitDirection));
        velocity=mul(unit(add(tangent,mul(delta,radial))),length(velocity));
    }
    ++p.planarTicks;
    // Native common movement increments elapsed source age before the extended
    // multiplier runs. The first completed frame therefore uses1/rampFrames.
    const float factor=m.accelerationRampFrames>0?
        1+(m.acceleration-1)*std::min(1.f,float(p.planarTicks)/m.accelerationRampFrames):m.acceleration;
    velocity=mul(velocity,factor);
    p.velocity.x=velocity.x;p.velocity.z=velocity.z;
    // Height/falling velocity, source attribution and the orbit center are
    // independent of planar motion and of the shooter's continued existence.
}
bool Simulation::burstOnDeath(const Projectile &p) {
    const auto pending=std::count_if(queue_.begin(),queue_.end(),[](const auto &e){return e.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &x){return x.alive;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+4>limits.queuedEvents||size_t(live+pending)+4>limits.projectiles)return false;
    const auto &b=*p.sourceBurst;const float angle=combatRng.real(0,2*Pi),speed=length(horizontal(p.velocity));
    auto birth=sub(p.position,mul(horizontal(p.velocity),1.f/30));
    const auto obstruction=arena.trace(p.position,birth,p.radius*b.childScale);
    if(obstruction.hit)birth=add(p.position,mul(sub(birth,p.position),std::max(0.f,obstruction.t-.001f)));
    birth.y=b.height;
    for(int n:std::array<int,4>{0,2,3,1}) {
        auto velocity=mul(rotateY({1,0,0},angle+float(n)*Pi/2),speed);
        velocity.y=combatRng.real(b.upMin,b.upMax);
        Event child;child.hostile=true;child.context=p.context;child.position=birth;child.origin=p.origin;
        child.direction=unit(velocity);child.speed=length(velocity);child.damage=p.damage;
        child.projectileKind=p.kind;child.projectileRadius=p.radius*b.childScale;
        child.projectileGravity=p.gravity;child.projectileFlightRetention=p.flightRetention;child.projectileLife=5;
        queueRoot(child); // BURST flag cleared; source owner and rock appearance retained.
    }
    return true;
}
bool Simulation::splitOnImpact(const Projectile &p) {
    const auto &s=*p.impactSplit;
    const auto pending=std::count_if(queue_.begin(),queue_.end(),[](const auto &e){return e.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &p){return p.alive;});
    // The dead parent is released before queued children are materialized. Both
    // children must fit together; retain one stopped carrier while saturated.
    if(queue_.size()+2>limits.queuedEvents||size_t(live+pending)+2>limits.projectiles||limits.eventsPerChain==0||limits.maxDepth<0)return false;
    auto backwards=mul(unit(horizontal(p.velocity)),-1);
    if(length(backwards)<.001f)backwards={0,0,-1};
    for(float sign:{-1.f,1.f}) {
        Event child;child.hostile=true;child.context=p.context;
        child.direction=rotateY(backwards,sign*s.angle);
        child.position=add(p.position,mul(child.direction,s.offset));
        // Keep the source backward offset, but clip it against intervening 3D
        // scenery so spawning cannot teleport a child through a thin wall.
        const auto hit=arena.trace(p.position,child.position,s.radius);
        if(hit.hit)child.position=add(add(p.position,mul(sub(child.position,p.position),hit.t)),mul(hit.normal,.01f));
        child.origin=p.origin;child.speed=s.speed;child.damage=s.damage;
        child.projectileRadius=s.radius;child.projectileLife=s.life;
        queueRoot(child); // Source attribution survives its owner; children do not recurse.
    }
    return true;
}
void Simulation::beginReturn(Projectile &p) {
    if(p.returning||p.attack.returnRange<=0)return;
    p.returning=true;p.phaseSpent=false;p.bounces=0;p.pierce=p.attack.pierce;
    p.hitEntities.clear();p.guidedTarget=0;
    p.velocity=mul(unit(sub(player.position,p.position)),p.attack.speed);
    // Life and capSpent deliberately survive the turn.
}
void Simulation::updateGuidance(Projectile &p,float dt) {
    if(p.returning) {
        p.velocity=mul(unit(sub(player.position,p.position)),p.attack.speed);
        return;
    }
    if(p.attack.homingTurn<=0||p.phaseSpent)return;
    p.guidanceTime-=dt;
    const Enemy *target=findEnemy(p.guidedTarget);
    auto eligible=[&](const Enemy &e) {
        const auto *def=content->monster(e.monster);
        return e.alive&&!e.friendly&&!e.thrownOffspring&&!(def&&def->roomHazard)&&
            !(e.leaper&&e.leaper->phase&&e.targetHop->airborne)&&
            e.state!=EnemyState::Buried&&e.state!=EnemyState::Teleporting&&
            distance(e.position,p.position)<=12&&
            std::find(p.hitEntities.begin(),p.hitEntities.end(),e.id)==p.hitEntities.end();
    };
    if(p.guidanceTime<=0||!target||!eligible(*target)) {
        p.guidanceTime=.12f;p.guidedTarget=0;target=nullptr;
        std::vector<const Enemy*> choices;
        for(const auto &e:enemies)
            if(eligible(e)&&dot(unit(p.velocity),unit(sub(e.position,p.position)))>-.25f)choices.push_back(&e);
        std::sort(choices.begin(),choices.end(),[&](const Enemy *a,const Enemy *b) {
            const auto da=distance(a->position,p.position),db=distance(b->position,p.position);
            return da==db?a->id<b->id:da<db;
        });
        for(const auto *e:choices)if(arena.sight(p.position,e->position)){target=e;p.guidedTarget=e->id;break;}
    }
    if(!target||!arena.sight(p.position,target->position))return;
    const auto current=unit(p.velocity),wanted=unit(sub(target->position,p.position));
    const float cosine=std::clamp(dot(current,wanted),-1.f,1.f),angle=std::acos(cosine);
    if(angle<.00001f)return;
    const float turn=std::min(angle,p.attack.homingTurn*dt);
    auto tangent=sub(wanted,mul(current,cosine));
    if(length(tangent)<.00001f)tangent=std::abs(current.y)<.9f?Vector3{-current.z,0,current.x}:Vector3{1,0,0};
    p.velocity=mul(add(mul(current,std::cos(turn)),mul(unit(tangent),std::sin(turn))),p.attack.speed);
}
} // namespace dw
