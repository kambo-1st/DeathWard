#include "combat/Simulation.hpp"

namespace dw {
EntityId Simulation::spawnBombFlyHost(MonsterId child,Vector3 position,EntityId producer) {
    const auto *rule=content->flyBomb(child);
    if(!rule||!rule->orbitOwner)return 0;
    if(producer) {const auto *parent=findEnemy(producer);if(!parent||!parent->alive)return 0;}
    const auto *host=content->monster(rule->orbitOwner),*orbiter=content->monster(child);
    if(livingEnemies()+pendingMonsters_.size()+size_t(rule->orbitCount)+1>limits.enemies)return 0;
    std::vector<Vector3> positions{position};
    for(int slot=0;slot<rule->orbitCount;++slot)
        positions.push_back(add(position,rotateY({rule->orbitRadius,0,0},float(slot)*2*Pi/float(rule->orbitCount))));
    for(size_t i=0;i<positions.size();++i) {
        const float radius=i?orbiter->radius:host->radius;
        auto &at=positions[i];
        if(arena.flightBlocked(at,radius,room))return 0;
        at.y=arena.flightHeight(at,radius);
        for(const auto &other:enemies)if(other.alive&&distance(at,other.position)<radius+other.radius+.05f)return 0;
        for(size_t j=0;j<i;++j)if(distance(at,positions[j])<radius+(j?orbiter->radius:host->radius)+.05f)return 0;
    }
    const auto count=enemies.size();
    const auto owner=spawnMonster(rule->orbitOwner,positions[0]);
    if(!owner)return 0;
    findEnemy(owner)->summoner=producer;
    for(int slot=0;slot<rule->orbitCount;++slot) {
        if(!spawnMonster(child,positions[size_t(slot)+1],owner,slot)) {
            enemies.resize(count);return 0; // No partial mandatory group on capacity failure.
        }
    }
    return owner;
}

void Simulation::updateFlyBomb(Enemy &enemy,float dt) {
    const auto &rule=*content->flyBomb(enemy.monster);
    const auto &definition=*content->monster(enemy.monster);
    enemy.age+=dt;enemy.pathTime-=dt;
    enemy.flash=std::max(0.f,enemy.flash-dt);
    enemy.fireContactCooldown=std::max(0.f,enemy.fireContactCooldown-dt);
    enemy.velocity={};
    auto requestContactDeath=[&] {
        if(std::any_of(queue_.begin(),queue_.end(),[&](const auto &event){return event.type==EventType::Damage&&event.target==enemy.id&&event.execution;}))return;
        Event death;death.type=EventType::Damage;death.target=enemy.id;death.position=enemy.position;
        death.damage=enemy.hp+1;death.execution=true;death.context.sourceEntity=enemy.id;
        queueRoot(death);
    };
    if(enemy.selfDetonated){requestContactDeath();return;}
    const auto previous=enemy.position;
    if(rule.orbitOwner) {
        const auto *owner=findEnemy(enemy.componentOwner);
        if(!owner||!owner->alive||owner->monster!=rule.orbitOwner) {
            enemy.alive=false;flyBombDeath(enemy);return;
        }
        const float angle=enemy.age*rule.orbitSpeed+float(enemy.componentSlot)*2*Pi/float(rule.orbitCount);
        const auto target=add(owner->position,rotateY({rule.orbitRadius,0,0},angle));
        // Ownership preserves phase; physical borders may compress the orbit.
        // Never teleport an attached fly through a sealed gate or a cliff.
        moveMonster(enemy,mul(horizontal(sub(target,enemy.position)),1/dt),dt);
        if(length(horizontal(enemy.velocity))>.001f)enemy.facing=unit(horizontal(enemy.velocity));
    } else if(!updateFlyBombFollow(enemy,dt)) {
        auto toward=unit(horizontal(sub(player.position,enemy.position)));
        bool routed=false;
        if(!arena.flightClear(enemy.position,player.position,enemy.radius,room)) {
            if(enemy.pathTime<=0) {
                enemy.path=arena.flightPath(enemy.position,player.position,enemy.radius,room);
                enemy.pathTime=1.1f;
            }
            while(!enemy.path.empty()&&planarDistance(enemy.position,enemy.path.front())<.12f)enemy.path.erase(enemy.path.begin());
            if(!enemy.path.empty()){toward=unit(horizontal(sub(enemy.path.front(),enemy.position)));routed=true;}
        } else enemy.path.clear();
        const float curve=routed?0:rule.circleStrength*std::clamp(1-planarDistance(enemy.position,player.position)/rule.circleRange,0.f,1.f);
        const Vector3 tangent{-toward.z,0,toward.x};
        const auto desired=unit(add(toward,mul(tangent,(enemy.id%2?1.f:-1.f)*curve)));
        const float current=std::atan2(enemy.facing.z,enemy.facing.x),target=std::atan2(desired.z,desired.x);
        const float angle=current+std::clamp(std::remainder(target-current,2*Pi),-rule.turnRate*dt,rule.turnRate*dt);
        enemy.facing={std::cos(angle),0,std::sin(angle)};
        moveMonster(enemy,mul(enemy.facing,definition.speed*EnemyMovementMultiplier),dt);
    }
    // Test relative motion: a fast dodge can cross the fly between fixed ticks.
    // Vertical separation is retained so flying above cover is not ground contact.
    if(segmentSphere(sub(previous,playerStepStart_),sub(enemy.position,player.position),{},enemy.radius+.48f)<=1&&
       arena.sight(enemy.position,player.position)) {
        enemy.selfDetonated=true;
        requestContactDeath();
    }
}

bool Simulation::updateFlyBombFollow(Enemy &e,float dt) {
    if(!e.flyFollow)return false;
    const auto *parent=findEnemy(e.flyFollow->parent);
    if(!parent||!parent->alive) {
        // Parent removal differs from Hornfel's ordinary exit: native references
        // disappear, but the explicit exit HP clamp is not invoked.
        e.flyFollow.reset();e.path.clear();e.pathTime=0;return false;
    }
    auto &f=*e.flyFollow;const auto &p=*content->flyBomb(e.monster);
    f.clock+=dt;
    while(f.clock+.000001f>=1.f/30) {
        f.clock-=1.f/30;++f.tick;
        if(f.tick%3==0) {
            auto delta=mul(horizontal(sub(parent->position,e.position)),1/p.followScale);
            const float distance=length(delta);
            if(distance<p.followRange) {
                // Shared native fly AI: soft radial constraint plus a tangent.
                // Coincident source spawns need a finite local fallback direction.
                const auto radial=distance>.001f?mul(delta,1/distance):e.facing;
                const float desired=p.followRadius+std::sin(float(f.tick)*p.followFrequency)*p.followWobble;
                const float error=std::clamp(distance-desired,-p.followClamp,p.followClamp);
                f.momentum=add(f.momentum,mul(radial,error*p.followRadial));
                f.momentum=add(f.momentum,mul(Vector3{-delta.z,0,delta.x},p.followTangent/(std::abs(error)+2)));
            }
            f.target=player.position;
        }
        if(f.tick%2==0) {
            const auto delta=mul(horizontal(sub(f.target,e.position)),1/p.followScale);
            // The source applies a skewed player attraction, attenuated by .2
            // when Parent exists; this is not a rigid orbit or pure player chase.
            const auto toward=mul(Vector3{delta.x-delta.z,0,(delta.z+delta.x)*.5f},p.followPursuit);
            const float distance=length(toward);
            if(distance>p.followDeadzone)
                f.momentum=add(f.momentum,mul(unit(toward),2*std::min((distance-p.followDeadzone)*p.followGain,p.followForce)));
        }
        if(f.tick%4==1)f.wander=mul(add(f.wander,rotateY({p.followJitter,0,0},combatRng.real(0,2*Pi))),p.followJitterRetention);
        if(f.tick%3==2)f.momentum=mul(add(f.momentum,mul(f.wander,2)),p.followRetention);
    }
    auto velocity=mul(f.momentum,p.followScale*30);
    if(length(velocity)>p.followSpeedCap)velocity=mul(unit(velocity),p.followSpeedCap);
    moveMonster(e,velocity,dt);
    // Physical flight collision wins over the steering force. Retaining only
    // realized momentum prevents acceleration accumulating against a cliff.
    f.momentum=mul(horizontal(e.velocity),1/(p.followScale*30));
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    return true;
}

void Simulation::flyBombDeath(const Enemy &enemy) {
    const auto &rule=*content->flyBomb(enemy.monster);
    EnemyBomb bomb;bomb.id=nextEntity_++;bomb.source=enemy.id;bomb.sourceMonster=enemy.monster;
    bomb.ordnance=rule.ordnance;bomb.room=room;
    auto &charge=bomb.charge;charge.kind=HazardKind::MonsterBomb;
    charge.position=charge.origin=enemy.position;charge.radius=rule.radius;charge.delay=rule.fuse;
    charge.blastDamage=enemy.selfDetonated?rule.contactDamage:rule.deathDamage;
    charge.damage=enemy.selfDetonated?rule.contactPlayerDamage:rule.deathPlayerDamage;
    if(enemy.selfDetonated)charge.delay=0;
    // Source death becomes real ordnance. Local 3D adaptation: drop vertically
    // from the body's altitude using terrain-aware bomb physics, without item modifiers.
    queueEnemyBomb(bomb);
}

} // namespace dw
