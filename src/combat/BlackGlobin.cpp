#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::queueThrownSpider(Enemy &e,MonsterId child,Vector3 target,float height) {
    ThrownOffspringRuntime flight;
    flight.origin=e.position;flight.origin.y=.85f;flight.profile.initialHeight=height;
    const auto before=pendingMonsters_.size();
    // These terminal Spider births cannot recurse into their parent family.
    // Keep ancestry bounded without deleting required offspring at depth four.
    queueMonster(child,target,0,std::min(4,e.generation+1),false,1,0,e.id,0,-1,{},true,flight);
    if(pendingMonsters_.size()==before)return false;
    pendingMonsters_.back().producer=e.id;
    audioCues.push(AudioCueKind::MonsterAttack,e.position);
    return true;
}

void Simulation::blackGlobinDamageBrood(Enemy &e) {
    const auto &p=*content->blackGlobin(e.monster);
    auto &r=*e.blackGlobin;
    if(!r.initialized||r.lastEmissionHP-e.hp<=p.damageThreshold)return;
    const auto target=add(e.position,mul(horizontal(sub(player.position,e.position)),p.targetFraction));
    if(queueThrownSpider(e,p.spider,target,p.throwHeight)) {
        r.lastEmissionHP=e.hp;++r.births;
    }
}

void Simulation::blackGlobinDeath(Enemy &e) {
    const auto &p=*content->blackGlobin(e.monster);
    if(!e.blackGlobin)e.blackGlobin=BlackGlobinRuntime{};
    auto &r=*e.blackGlobin;
    if(r.deathReleased)return;
    // DeathWard resolves lethal damage immediately. Run the same polled HP
    // check before releasing parts; there is no additional unconditional spider.
    blackGlobinDamageBrood(e);r.deathReleased=true;
    queueMonster(p.body,e.position,0,std::min(4,e.generation+1),false,1,0,e.id,0,-1,{},true);
    const auto offset=rotateY({combatRng.real(0,p.headRadius),0,0},combatRng.real(0,2*Pi));
    queueMonster(p.head,add(e.position,offset),0,std::min(4,e.generation+1),false,1,0,e.id,0,-1,{},true);
}

void Simulation::updateBlackGlobin(Enemy &e,float dt) {
    const auto &p=*content->blackGlobin(e.monster);
    if(!e.blackGlobin)e.blackGlobin=BlackGlobinRuntime{};
    auto &r=*e.blackGlobin;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    // One due live birth is retained under geometry/capacity pressure. Damage
    // still accumulates; death can reserve its final HP-triggered birth too.
    if(std::any_of(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &s){return s.producer==e.id;})) {
        e.velocity={};return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized){r.initialized=true;r.lastEmissionHP=e.hp;}
            else {
                blackGlobinDamageBrood(e);
                r.walkFrame=length(r.momentum)>=p.stopSpeed?(r.walkFrame+1)%p.walkFrames:0;
                r.walkPhase=float(r.walkFrame)/p.walkFrames;
                stepGroundPursuit(e,p,r.momentum,r.destination,p.force);
            }
            e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position;
        if(!e.railCarrier)moveMonster(e,steerMonsterBodies(e,mul(r.momentum,p.scale*30)),step);
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(p.contact,{0,0,e.id,-1});
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=player.position;
}
} // namespace dw
