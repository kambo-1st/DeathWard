#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 arc(const HopRuntime &hop,float t) {
    auto p=add(hop.start,mul(sub(hop.end,hop.start),t));
    p.y+=4*t*(1-t)*hop.height;
    return p;
}
bool landing(const Arena &arena,Vector3 p,float radius,int room) {
    p.y=.85f;
    return !arena.flightBlocked(p,radius,room)&&!arena.blocked(p,radius)&&
        !arena.reservedSupplyCache(p,radius);
}
bool clearArc(const Arena &arena,const HopRuntime &hop,float radius,int room) {
    if(!landing(arena,hop.end,radius,room)||!arena.flightClear(hop.start,hop.end,radius,room))return false;
    // Swept volume at fixed arc intervals; no ground-navigation test over water.
    // Bounded authored distance/height keeps the sampling below .5 world units.
    constexpr int samples=64;
    auto previous=hop.start;
    for(int i=1;i<=samples;++i) {
        const auto next=arc(hop,float(i)/samples);
        if(arena.trace(previous,next,radius).hit)return false;
        previous=next;
    }
    return true;
}
}

bool Simulation::planHopArc(Enemy &e,Vector3 direction,float reach,float height,float maximumHeight,float duration) {
    auto &hop=e.hop;
    constexpr std::array<float,7> angles{0,Pi/6,-Pi/6,Pi/3,-Pi/3,Pi/2,-Pi/2};
    for(float fraction:{1.f,.65f,.35f})for(float angle:angles) {
        hop.start=e.position;
        hop.end=add(hop.start,mul(rotateY(direction,angle),reach*fraction));
        if(!landing(arena,hop.end,e.radius,room)||!arena.flightClear(hop.start,hop.end,e.radius,room))continue;
        for(int elevation=0;elevation<=8;++elevation) {
            hop.height=height+(maximumHeight-height)*float(elevation)/8;
            if(clearArc(arena,hop,e.radius,room)){hop.duration=duration;return true;}
        }
    }
    return false;
}
bool Simulation::revalidateHopArc(Enemy &e) {
    e.hop.start=e.position;return clearArc(arena,e.hop,e.radius,room);
}
bool Simulation::advanceHopArc(Enemy &e,float dt) {
    auto &hop=e.hop;const auto before=e.position;
    hop.elapsed=std::min(hop.duration,hop.elapsed+dt);
    e.position=arc(hop,hop.elapsed/hop.duration);e.velocity=mul(sub(e.position,before),1/dt);
    if(hop.elapsed>=hop.duration){e.position=hop.end;hop.active=false;return true;}
    return false;
}

void Simulation::updateHop(Enemy &e,const MonsterDefinition &d,const HopDefinition &h,float dt) {
    auto &hop=e.hop;
    auto target=player.position;bool hasTarget=!e.friendly;
    if(e.friendly) {
        float best=100000;
        e.partner=0;
        for(const auto &other:enemies)if(other.alive&&!other.friendly&&other.id!=e.id) {
            const float dist=planarDistance(e.position,other.position);
            if(dist<best){best=dist;target=other.position;e.partner=other.id;hasTarget=true;}
        }
    }
    const bool stunned=e.state==EnemyState::Stunned;
    if(stunned)e.stateTime-=dt;
    if(hop.active) {
        // A committed jump keeps its trajectory through stun or a compatible
        // fire transformation. It cannot drop an actor into a pit/rock mid-flight.
        if(advanceHopArc(e,dt)) {
            e.cooldown=d.cooldown;
            e.state=stunned&&e.stateTime>0?EnemyState::Stunned:EnemyState::Ready;
        } else if(!stunned||e.stateTime<=0)e.state=EnemyState::Jumping;
    } else if(stunned) {
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    } else if(e.state==EnemyState::Windup) {
        e.stateTime-=dt;
        if(e.stateTime<=0) {
            // Ground crowd separation may have moved the body during windup;
            // recheck the committed destination and arc from its actual takeoff.
            if(revalidateHopArc(e)) {
                hop.active=true;hop.elapsed=0;e.state=EnemyState::Jumping;
            } else {e.state=EnemyState::Ready;e.cooldown=h.retry;}
        }
    } else if(e.cooldown<=0) {
        const float dist=planarDistance(e.position,target);
        hop.pursuing=hasTarget&&dist<=h.range;
        const auto direction=hop.pursuing?unit(horizontal(sub(target,e.position))):
            rotateY({1,0,0},combatRng.real(-Pi,Pi));
        const float reach=hop.pursuing?std::min(h.chaseDistance,std::max(.1f,dist)):h.wanderDistance;
        const bool planned=planHopArc(e,direction,reach,h.height,h.maximumHeight,h.duration/(e.friendly?1.f:EnemyMovementMultiplier));
        if(planned) {
            e.facing=unit(horizontal(sub(hop.end,hop.start)));e.target=hop.end;
            e.state=EnemyState::Windup;e.stateTime=d.windup;
            if(!e.friendly)audioCues.push(AudioCueKind::Warning,e.position);
        } else e.cooldown=h.retry;
    }
    // Actual 3D body positions drive projectiles, aiming, flame exposure and
    // contact. The old visual-only lift is deliberately zero for these actors.
    if(!d.contact)return;
    if(e.friendly) {
        const auto *target=findEnemy(e.partner);
        if(target&&target->alive&&!target->friendly&&e.auxiliary<=0&&
           distance(e.position,target->position)<e.radius+target->radius&&arena.sight(e.position,target->position)) {
            Event hit;hit.type=EventType::Damage;hit.target=target->id;hit.damage=28;
            queueRoot(hit);e.auxiliary=.7f;
        }
    } else if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(10);
}
} // namespace dw
