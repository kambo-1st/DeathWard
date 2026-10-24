#include "combat/Simulation.hpp"

namespace dw {
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
        const auto *def=monsterDefinition(e.monster);
        return e.alive&&!e.friendly&&!(def&&def->roomHazard)&&
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
    const auto wanted=sub(target->position,p.position);
    const float current=std::atan2(p.velocity.z,p.velocity.x),angle=std::atan2(wanted.z,wanted.x);
    const float turn=std::clamp(std::remainder(angle-current,2*Pi),-p.attack.homingTurn*dt,p.attack.homingTurn*dt);
    p.velocity={std::cos(current+turn)*p.attack.speed,0,std::sin(current+turn)*p.attack.speed};
}
} // namespace dw
