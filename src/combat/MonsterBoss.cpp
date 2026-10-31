#include "combat/Simulation.hpp"
#include <bit>

namespace dw {
void Simulation::initializeMonsterBoss(Enemy &e,BossForm form) {
    e.kind=EnemyKind::Boss;e.bossKind=BossKind::Isaac;e.bossForm=form;
    if(const auto *p=content->peep(e.monster);p&&form==BossForm::Yellow)e.radius*=p->yellowScale;
    if(content->bloat(e.monster))e.facing={0,0,1}; // Source down is fixed in world space, not toward the camera/player.
    e.position.y=e.radius+.05f;e.home=e.position;e.cooldown=1.2f;
    requestBossComponents(e);
}
void Simulation::bossCreep(const Enemy &e,float radius,float duration,Color tint,float damage) {
    auto at=e.position;at.y=.85f;
    if(arena.canyon&&(std::abs(arena.canyon->height(at.x,at.z))>.02f||arena.canyon->waterBlocked(at)))return;
    // Constant trails refresh nearby deposits rather than exhausting the hazard cap
    // while the boss is stationary. Each patch still expires after its owner leaves.
    for(auto &h:hazards)if(h.alive&&h.kind==HazardKind::Creep&&h.context.sourceEntity==e.id&&
        std::abs(h.radius-radius)<.01f&&planarDistance(h.position,at)<radius*.5f) {h.age=0;h.duration=duration;return;}
    Hazard h;h.kind=HazardKind::Creep;h.position=at;h.radius=radius;h.delay=0;h.duration=duration;
    h.damage=damage;h.context.sourceEntity=e.id;h.tint=tint;addHazard(h);
}
void Simulation::updateMonsterBoss(Enemy &e,float dt) {
    if(content->hornfel(e.monster)){updateHornfel(e,dt);return;}
    if(content->loki(e.monster)){updateLoki(e,dt);return;}
    if(content->bloat(e.monster)){updateBloat(e,dt);return;}
    const auto *p=content->peep(e.monster);if(!p)return;
    const auto &d=*content->monster(e.monster);
    const float pace=e.bossForm==BossForm::Yellow?p->yellowSpeed:1;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};e.auxiliary-=dt;
    e.trailTime-=dt;e.cooldown-=dt*pace/(EnemyCooldownMultiplier*arena.profile.cooldownScale);
    requestBossComponents(e);e.phase=std::popcount(e.bossParts);
    auto volley=[&](int count) {
        const float angle=combatRng.real(0,2*Pi);
        for(int n=0;n<count;++n)shootEnemy(e,rotateY({1,0,0},angle+float(n)*2*Pi/count),
            p->shotDamage,p->shotSpeed,0,ProjectileKind::Yellow);
    };
    if(e.bossForm==BossForm::Yellow&&e.trailTime<=0) {bossCreep(e,p->trailRadius,p->creepDuration);e.trailTime=p->trailInterval;}
    const bool stunned=e.state==EnemyState::Stunned;
    if(stunned)e.stateTime-=dt;
    if(e.hop.active) {
        if(advanceHopArc(e,dt)) {
            volley(12);++e.bossCycles;e.cooldown=d.cooldown;
            e.state=stunned&&e.stateTime>0?EnemyState::Stunned:EnemyState::Ready;
            particleEffect(ParticleEffect::Dirt,{e.position.x,0,e.position.z},{0,1,0},1);
        } else if(!stunned||e.stateTime<=0)e.state=EnemyState::Jumping;
    } else if(stunned) {
        if(e.stateTime<=0){e.state=EnemyState::Ready;e.cooldown=.4f;}
    } else if(e.state==EnemyState::Windup) {
        e.stateTime-=dt*pace;
        if(e.stateTime<=0) {
            if(e.bossAttack==2&&revalidateHopArc(e)) {e.hop.active=true;e.hop.elapsed=0;e.state=EnemyState::Jumping;}
            else {
                if(e.bossAttack==0)bossCreep(e,p->creepRadius,p->creepDuration);
                if(e.bossAttack==1)volley(8);
                ++e.bossCycles;e.state=EnemyState::Ready;e.cooldown=d.cooldown;
            }
        }
    } else if(e.cooldown<=0) {
        int total=0;for(int weight:p->weights)total+=weight;
        int roll=int(combatRng.bounded(uint32_t(total)));e.bossAttack=0;
        for(int n=0;n<3;++n)if((roll-=p->weights[size_t(n)])<0){e.bossAttack=n;break;}
        e.facing=unit(horizontal(sub(player.position,e.position)));
        if(e.bossAttack==2) {
            const float reach=std::min(p->distance,planarDistance(player.position,e.position));
            if(!planHopArc(e,e.facing,reach,p->height,p->maximumHeight,p->flight/(pace*EnemyMovementMultiplier))&&
               !planHopArc(e,e.facing,0,p->height,p->maximumHeight,p->flight/(pace*EnemyMovementMultiplier))) {e.cooldown=.4f;return;}
            e.target=e.hop.end;
        } else e.target=e.position;
        e.state=EnemyState::Windup;e.stateTime=d.windup;audioCues.push(AudioCueKind::Warning,e.position);
    }
    if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(p->contactDamage);
}
} // namespace dw
