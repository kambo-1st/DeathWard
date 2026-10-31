#include "combat/Simulation.hpp"

namespace dw {
Vector3 Simulation::chargeTailPosition(const Enemy &e) const {
    const auto *c=content->charge(e.monster);
    return c?add(e.position,mul(unit(horizontal(e.facing)),-c->tailOffset*e.radius)):e.position;
}
float Simulation::enemyProjectileHit(const Enemy &e,Vector3 from,Vector3 to,float radius,bool &weak) const {
    weak=false;const auto *c=content->charge(e.monster);
    if(e.adultLeech&&e.adultLeech->intangible)return 2.f;
    if(e.rockSpider) {
        if(e.rockSpider->height<content->rockSpider(e.monster)->entityHeight)return 2.f;
        return segmentSphere(from,to,add(e.position,{0,e.lift,0}),e.radius+radius);
    }
    if(e.thrownOffspring||e.dyingEggy())return 2.f; // These source states have no entity collision.
    if(content->statue(e.monster)&&content->monster(e.monster)->shape==MonsterShape::Stone) {
        const float half=e.radius*.85f;
        const Box body{{e.position.x-half,0,e.position.z-half},{e.position.x+half,e.radius*2,e.position.z+half}};
        const auto hit=segmentBox(from,to,body,radius);return hit.hit?hit.t:2.f;
    }
    if(!c||c->tailRadius<=0)return segmentSphere(from,to,e.position,e.radius+radius);
    const auto facing=unit(horizontal(e.facing));
    // Compact armored head/midsection and exposed tail share the navigation hull.
    // Test nearest geometry first: a rearward direction alone is insufficient.
    float best=segmentSphere(from,to,add(e.position,mul(facing,e.radius*.25f)),e.radius*.7f+radius);
    best=std::min(best,segmentSphere(from,to,add(e.position,mul(facing,-e.radius*.15f)),e.radius*.55f+radius));
    const float tail=segmentSphere(from,to,chargeTailPosition(e),c->tailRadius*e.radius+radius);
    if(tail<best){best=tail;weak=true;}
    return best;
}
void Simulation::updateCharge(Enemy &e,float dt) {
    const auto &c=*content->charge(e.monster);const auto &d=*content->monster(e.monster);
    const float multiplier=e.friendly?1.f:EnemyMovementMultiplier;
    const float speed=c.speed*multiplier,walk=d.speed*multiplier;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};e.cooldown-=dt;e.auxiliary-=dt;e.trailTime-=dt;
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    auto finish=[&]{e.state=EnemyState::Ready;e.cooldown=c.recovery;e.chargeRecovery=c.pause;e.auxiliary=0;};
    auto dash=[&] {
        const auto start=e.position;float remaining=dt;bool blocked=false;
        // Swept reflections retain the remaining distance and reflect the actual
        // wall normal. Four impacts per tick bound pathological tight corners.
        for(int bounce=0;bounce<4&&remaining>Tick*.001f;++bounce) {
            const auto delta=mul(e.facing,speed*remaining),end=add(e.position,delta);
            if(!arena.blocked(end,e.radius)&&arena.clear(e.position,end,e.radius)) {
                e.position=end;remaining=0;break;
            }
            const auto hit=arena.trace(e.position,end,e.radius);
            if(hit.hit&&hit.t>0)e.position=add(e.position,mul(delta,std::max(0.f,hit.t-.001f)));
            blocked=true;
            if(!c.reflect)break;
            auto normal=unit(horizontal(hit.normal));
            if(!hit.hit||length(normal)<.5f) {
                // Water/navigation edges have no rendered wall normal.
                const bool x=arena.blocked(add(e.position,{delta.x,0,0}),e.radius);
                const bool z=arena.blocked(add(e.position,{0,0,delta.z}),e.radius);
                normal=x&&!z?Vector3{e.facing.x>0?-1.f:1.f,0,0}:z&&!x?Vector3{0,0,e.facing.z>0?-1.f:1.f}:mul(e.facing,-1);
            }
            e.facing=unit(sub(e.facing,mul(normal,2*dot(e.facing,normal))));
            remaining*=hit.hit?1-std::clamp(hit.t,0.f,1.f):.5f;
            blocked=false;
        }
        e.velocity=mul(sub(e.position,start),1/dt);
        if(c.trailInterval>0&&e.trailTime<=0&&planarDistance(start,e.position)>.001f) {
            // A trail is deposited only during actual dash movement, never while resting.
            if(!arena.canyon||(!arena.canyon->waterBlocked(e.position)&&std::abs(arena.canyon->height(e.position.x,e.position.z))<.02f))
                monsterPatch(e,HazardKind::Tar,e.position,c.trailRadius,0,c.trailDuration);
            e.trailTime=c.trailInterval;
        }
        if(blocked||e.stateTime<=0)finish();
    };
    if(e.state==EnemyState::Stunned) {
        e.stateTime-=dt;if(e.stateTime<=0)finish();
    } else if(e.state==EnemyState::Charging) {
        e.stateTime-=dt;
        if(c.turnRate>0) {
            const auto *other=e.friendly?findEnemy(e.partner):nullptr;
            const auto target=unit(horizontal(sub(e.friendly?(other&&other->alive?other->position:add(e.position,e.facing)):player.position,e.position)));
            const float angle=std::atan2(target.x,target.z)-std::atan2(e.facing.x,e.facing.z);
            const float turn=std::atan2(std::sin(angle),std::cos(angle));
            e.facing=rotateY(e.facing,std::clamp(turn,-c.turnRate*dt,c.turnRate*dt));
        }
        dash();
    } else if(e.chargeRecovery>0) {
        e.chargeRecovery=std::max(0.f,e.chargeRecovery-dt);
    } else {
        auto target=player.position;bool hasTarget=!e.friendly;
        if(e.friendly) {
            float nearest=std::numeric_limits<float>::max();e.partner=0;
            for(const auto &other:enemies)if(companionTarget(other)) {
                const auto delta=sub(other.position,e.position);
                if(std::abs(delta.x)>c.alignment&&std::abs(delta.z)>c.alignment)continue;
                const auto range=distance(e.position,other.position);
                if(range<nearest&&arena.sight(e.position,other.position)) {
                    nearest=range;target=other.position;e.partner=other.id;hasTarget=true;
                }
            }
        }
        const auto delta=sub(target,e.position);
        const bool vertical=std::abs(delta.x)<=c.alignment,horizontal=std::abs(delta.z)<=c.alignment;
        const bool aligned=c.diagonal?std::abs(std::abs(delta.x)-std::abs(delta.z))*.70710678f<=c.alignment:vertical||horizontal;
        if(e.cooldown<=0&&hasTarget&&aligned&&arena.sight(e.position,target)) {
            e.facing=c.diagonal?unit(Vector3{delta.x<0?-1.f:1.f,0,delta.z<0?-1.f:1.f}):
                vertical?Vector3{0,0,delta.z<0?-1.f:1.f}:Vector3{delta.x<0?-1.f:1.f,0,0};
            e.state=EnemyState::Charging;e.stateTime=c.duration;
            dash(); // No anticipation delay. Turning variants start on the acquired axis.
        } else {
            if(e.auxiliary<=0){e.facing=rotateY({1,0,0},combatRng.real(-Pi,Pi));e.auxiliary=combatRng.real(c.wanderMin,c.wanderMax);}
            const auto before=e.position;moveMonster(e,mul(e.facing,walk),dt);
            if(planarDistance(before,e.position)<walk*dt*.5f)e.auxiliary=0;
        }
    }
    if(!e.friendly&&d.contact&&distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(c.contactDamage);
}
} // namespace dw
