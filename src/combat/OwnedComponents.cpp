#include "combat/Simulation.hpp"

namespace dw {
void Simulation::requestBossComponents(Enemy &e) {
    const auto *peep=content->peep(e.monster);const auto *bloat=content->bloat(e.monster);
    if((!peep&&!bloat)||e.auxiliary>0)return;
    const auto eyeId=peep?peep->eye:bloat->eye;
    const auto side=Vector3{-e.facing.z,0,e.facing.x};
    for(int slot=0;slot<2;++slot) {
        if(e.bossParts&(1u<<slot))continue;
        if(!bloat&&e.bossForm!=BossForm::Cyan&&e.hp>e.maxHp*(slot==0?2.f/3:1.f/3))continue;
        if(std::any_of(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &p){return p.componentOwner==e.id&&p.componentSlot==slot;}))continue;
        const auto *eye=content->monster(eyeId);
        queueMonster(eyeId,add(e.position,mul(side,(slot?1.f:-1.f)*(e.radius+eye->radius+.3f))),
            0,e.generation+1,false,1,0,0,e.id,slot);
        // Capacity/placement failures retry without pretending that the eye exists.
        e.auxiliary=.25f;
    }
}
void Simulation::removeOwnedComponents(EntityId owner,bool deathEffects) {
    for(auto &e:enemies)if(e.alive&&e.componentOwner==owner) {
        e.alive=false;
        if(deathEffects&&content->flyBomb(e.monster))flyBombDeath(e);
    }
    std::erase_if(pendingMonsters_,[&](const auto &request){return request.componentOwner==owner;});
}
void Simulation::updateOwnedComponent(Enemy &e,float dt) {
    const auto *rule=content->component(e.monster);const auto *owner=findEnemy(e.componentOwner);
    if(!rule||!owner||!owner->alive||owner->monster!=rule->owner){e.alive=false;return;}
    const auto &d=*content->monster(e.monster);
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    const float speed=d.speed*EnemyMovementMultiplier;
    auto velocity=mul(unit(horizontal(e.facing)),speed);
    auto before=e.position;auto next=arena.fly(before,mul(velocity,dt),e.radius,room);
    // Reflect each blocked axis, including corners; interior cover is overflown.
    if(std::abs(next.x-before.x)<std::abs(velocity.x*dt)*.5f)e.facing.x=-e.facing.x;
    if(std::abs(next.z-before.z)<std::abs(velocity.z*dt)*.5f)e.facing.z=-e.facing.z;
    for(const auto &other:enemies)if(other.alive&&other.id!=e.id&&
        segmentSphere(before,next,other.position,e.radius+other.radius)<=1) {
        auto normal=unit(horizontal(sub(before,other.position)));
        if(dot(velocity,normal)>=0)continue;
        e.facing=unit(sub(unit(velocity),mul(normal,2*dot(unit(velocity),normal))));
        next=before;break;
    }
    e.position=next;e.velocity=mul(sub(next,before),1/dt);
    if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(rule->contactDamage);
}
} // namespace dw
