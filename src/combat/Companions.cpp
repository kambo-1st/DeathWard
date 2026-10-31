#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::companionTarget(const Enemy &e) const {
    const auto *d=content->monster(e.monster);
    return e.alive&&!e.dyingEggy()&&!e.friendly&&(!d||!d->roomHazard)&&
        e.state!=EnemyState::Buried&&e.state!=EnemyState::Teleporting;
}
float Simulation::contactDamage(const Enemy &e) const {
    if(e.dyingEggy())return 0;
    if(const auto *d=content->monster(e.monster);d&&!d->contact)return 0;
    if(const auto *c=content->charge(e.monster))return c->contactDamage;
    if(const auto *p=content->peep(e.monster))return p->contactDamage;
    if(const auto *b=content->bloat(e.monster))return b->contactDamage;
    if(const auto *c=content->component(e.monster))return c->contactDamage;
    return e.monster.type==24?20.f:10.f;
}
void Simulation::updateContactFamiliars(float dt) {
    // One producer per owned definition, independent of duplicate item copies.
    std::erase_if(familiars,[&](const auto &f){return itemStacks(f.item)==0;});
    for(const auto &definition:content->contactFamiliars()) {
        if(!itemStacks(definition.item))continue;
        auto found=std::find_if(familiars.begin(),familiars.end(),[&](const auto &f){return f.item==definition.item;});
        if(found==familiars.end()) {
            ContactFamiliarRuntime f;f.item=definition.item;f.id=nextEntity_++;
            f.position=player.position;f.facing=player.facing;f.radius=definition.radius;
            f.trail.push_back({stats.duration-definition.lag,player.position,player.facing});
            familiars.push_back(std::move(f));found=std::prev(familiars.end());
        }
        auto &f=*found;
        // The path is a timed history, not a spring that cuts across corners.
        // Sampling at at most 120 Hz bounds the two-second configured history.
        if(f.trail.empty()||stats.duration-f.trail.back().time>=Tick*.5f)
            f.trail.push_back({stats.duration,player.position,player.facing});
        const double delayed=stats.duration-definition.lag;
        while(f.trail.size()>2&&f.trail[1].time<=delayed)f.trail.pop_front();
        while(f.trail.size()>256)f.trail.pop_front();
        const auto &a=f.trail.front();const auto &b=f.trail.size()>1?f.trail[1]:a;
        const float fraction=b.time>a.time?float(std::clamp((delayed-a.time)/(b.time-a.time),0.,1.)):0.f;
        f.position=add(a.position,mul(sub(b.position,a.position),fraction));
        f.facing=unit(add(mul(a.facing,1-fraction),mul(b.facing,fraction)));
        for(auto &contact:f.contacts)contact.second-=dt;
        std::erase_if(f.contacts,[&](const auto &contact){const auto *e=findEnemy(contact.first);return contact.second<=0||!e||!e->alive;});
        int population=int(std::count_if(enemies.begin(),enemies.end(),[&](const auto &e){return e.alive&&e.friendly&&e.monster==definition.child;}))+
            int(std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &e){return e.id==definition.child;}));
        for(const auto &enemy:enemies) {
            if(population>=definition.limit)break;
            if(!companionTarget(enemy)||distance(enemy.position,f.position)>enemy.radius+f.radius||
                !arena.sight(f.position,enemy.position)||
                std::any_of(f.contacts.begin(),f.contacts.end(),[&](const auto &c){return c.first==enemy.id;}))continue;
            const auto before=pendingMonsters_.size();
            queueMonster(definition.child,f.position,0,1,false,1,0,f.id,0,-1,definition.item);
            if(pendingMonsters_.size()>before) {
                ++population;f.contacts.emplace_back(enemy.id,definition.contactInterval);
            }
        }
    }
}
void Simulation::updateCompanionContacts(float dt) {
    for(auto &ally:enemies) {
        if(!ally.alive||!ally.friendly)continue;
        const auto *definition=content->companion(ally.monster);if(!definition)continue;
        ally.companionAttackCooldown=std::max(0.f,ally.companionAttackCooldown-dt);
        ally.companionHurtCooldown=std::max(0.f,ally.companionHurtCooldown-dt);
        for(const auto &enemy:enemies) {
            if(!companionTarget(enemy)||distance(ally.position,enemy.position)>ally.radius+enemy.radius+.06f||
                !arena.sight(ally.position,enemy.position))continue;
            if(ally.state!=EnemyState::Stunned&&ally.companionAttackCooldown<=0) {
                bool weak=false;enemyProjectileHit(enemy,ally.position,enemy.position,ally.radius,weak);
                Event hit;hit.type=EventType::Damage;hit.target=enemy.id;hit.position=ally.position;
                hit.origin=ally.position;hit.direction=unit(sub(enemy.position,ally.position));
                hit.damage=definition->contactDamage;hit.weakPointHit=weak;
                hit.context.sourceEntity=ally.id;hit.context.sourceItem=ally.companionItem;queueRoot(hit);
                ally.companionAttackCooldown=definition->attackInterval;
            }
            if(ally.companionHurtCooldown<=0&&contactDamage(enemy)>0) {
                Event hit;hit.type=EventType::Damage;hit.target=ally.id;hit.position=ally.position;
                hit.origin=enemy.position;hit.direction=unit(sub(ally.position,enemy.position));
                hit.damage=contactDamage(enemy);hit.hostile=true;hit.context.sourceEntity=enemy.id;queueRoot(hit);
            }
        }
    }
}
void Simulation::exposeCompanionsToHazard(const Hazard &hazard,float previousAge) {
    if(!hazard.alive||hazard.age<hazard.delay||(!hazard.harmsPlayer&&!hazard.harmsMonsters))return;
    // Fire has its own shared exposure cooldown. Explosive event producers carry
    // their faction separately; player dynamite remains harmless to these allies.
    if(hazard.kind==HazardKind::Fire||hazard.kind==HazardKind::Tar||hazard.kind==HazardKind::PlayerDynamite||
        hazard.kind==HazardKind::BossCharge||hazard.kind==HazardKind::Powder||hazard.kind==HazardKind::MonsterBomb)return;
    if(hazard.duration>0&&hazard.age>=hazard.delay+hazard.duration)return;
    for(const auto &ally:enemies) {
        if(!ally.alive||!ally.friendly||!content->companion(ally.monster)||ally.companionHurtCooldown>0)continue;
        bool touched=false;
        if(hazard.kind==HazardKind::RockWave)
            touched=arena.roomAt(ally.position)==room&&segmentSphere(hazard.previous,hazard.position,ally.position,hazard.radius+ally.radius)<=1&&
                arena.sight(hazard.previous,ally.position);
        else if(hazard.kind==HazardKind::Beam)
            touched=segmentSphere(hazard.origin,hazard.position,ally.position,hazard.radius+ally.radius)<=1&&
                arena.sight(hazard.origin,ally.position);
        else {
            const float range=distance(ally.position,hazard.position);
            if(hazard.kind==HazardKind::Ring) {
                const float duration=std::max(Tick,hazard.duration);
                const float before=hazard.radius*std::clamp((previousAge-hazard.delay)/duration,0.f,1.f);
                const float after=hazard.radius*std::clamp((hazard.age-hazard.delay)/duration,0.f,1.f);
                touched=range+ally.radius>=before&&range-ally.radius<=after;
            } else touched=range<hazard.radius+ally.radius;
            touched=touched&&arena.sight(hazard.position,ally.position);
        }
        if(!touched)continue;
        Event hit;hit.type=EventType::Damage;hit.target=ally.id;hit.position=hazard.position;
        hit.origin=hazard.origin;hit.damage=hazard.damage;hit.areaDamage=true;
        hit.hostile=true;
        if(hazard.kind==HazardKind::RockWave)hit.demolition=Demolition::RockWave;
        emit(hit,hazard.context);
    }
}
} // namespace dw
