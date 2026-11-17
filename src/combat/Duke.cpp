#include "combat/Simulation.hpp"
namespace dw {
bool Simulation::flushDukeBirths(Enemy &e) {
    auto &r=*e.duke;
    if(r.pending.empty())return true;
    if(e.generation>=4||livingEnemies()+pendingMonsters_.size()+r.pending.size()>limits.enemies||
       std::any_of(r.pending.begin(),r.pending.end(),[](const auto &birth){return !birth.seed;}))return false;
    for(const auto &birth:r.pending) {
        auto at=mul(birth.position,GaperMovementScale);at.y=.85f;
        queueMonster(monsterId(birth.type),at,0,e.generation+1,false,birth.healthScale,0,birth.live?e.id:0,0,-1,{},true);
        auto &request=pendingMonsters_.back();request.producer=e.id;
        request.spawnerType=birth.live?67:0;request.contactRetention=birth.live?.9f:0;
        request.dukeChild=DukeChildRuntime{birth.seed,birth.cohort?e.id:0,birth.cohort,birth.visualScale};
    }
    r.pending.clear();return true;
}
void Simulation::releaseDukeCohort(Enemy &e,bool impulse) {
    const float velocityScale=GaperMovementScale*30*dukeTuning.flySpeed;
    const auto origin=e.duke?mul(e.duke->position,GaperMovementScale):e.position;
    if(!impulse&&e.duke)for(auto &birth:e.duke->pending)birth.cohort=false;
    for(auto &birth:pendingMonsters_)if(birth.dukeChild&&birth.dukeChild->cohort&&birth.dukeChild->parent==e.id) {
        if(impulse)birth.impulse=mul(sourceDukeRelease(mul(horizontal(sub(birth.position,origin)),1/GaperMovementScale),
            mul(horizontal(birth.impulse),1/velocityScale)),velocityScale);
        birth.dukeChild->cohort=false;birth.dukeChild->parent=0;
    }
    for(auto &child:enemies)if(child.dukeChild&&child.dukeChild->cohort&&child.dukeChild->parent==e.id) {
        if(impulse&&child.alive) {
            const auto velocity=sourceDukeRelease(mul(horizontal(sub(child.position,origin)),1/GaperMovementScale),
                mul(horizontal(child.velocity),1/velocityScale));
            const float vertical=child.velocity.y;child.velocity=mul(velocity,velocityScale);child.velocity.y=vertical;
            if(child.buzz)child.buzz->momentum=velocity;
        }
        child.dukeChild->cohort=false;child.dukeChild->parent=0;
    }
}
void Simulation::updateDuke(Enemy &e,float dt) {
    auto &r=*e.duke;e.age+=dt;e.flash=std::max(0.f,e.flash-dt);const auto before=e.position;
    auto contact=[&] {
        auto from=sub(before,playerStepStart_),to=sub(e.position,player.position);
        from=horizontal(from);to=horizontal(to);
        if(segmentSphere(from,to,{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(10,{0,0,e.id,-1});
    };
    if(!r.initialized){r.initialized=true;r.initSeed=uint32_t(combatRng.next());if(!r.initSeed)r.initSeed=1;r.position=mul(horizontal(e.position),1/GaperMovementScale);r.momentum=mul(horizontal(e.velocity),(1.f/30)/GaperMovementScale);}
    const bool recovering=r.paused;
    if(!flushDukeBirths(e)){r.paused=true;e.velocity={};contact();return;}
    r.paused=false;
    if(!recovering) {
        r.position=mul(horizontal(e.position),1/GaperMovementScale);r.clock+=dt;
    }
    auto physics=[&] {
        sourceDukePhysics(r);
        const auto destination=mul(r.position,GaperMovementScale),delta=horizontal(sub(destination,e.position));
        const auto before=e.position;auto after=arena.fly(before,mul(delta,dukeTuning.movement),e.radius,room);
        if(arena.roomAt(after)!=room)after=before;
        // Retained canyon outline: reflect blocked axes rather than wedging in an irregular corner.
        if(std::abs(after.x-before.x-delta.x*dukeTuning.movement)>.0001f)r.momentum.x=-r.momentum.x;
        if(std::abs(after.z-before.z-delta.z*dukeTuning.movement)>.0001f)r.momentum.z=-r.momentum.z;
        e.position=after;e.position.y=arena.flightHeight(e.position,e.radius);
        r.position=mul(horizontal(e.position),1/GaperMovementScale);e.velocity=mul(r.momentum,GaperMovementScale*30*dukeTuning.movement);r.pendingPhysics=false;
    };
    if(r.pendingPhysics)physics();
    while(r.clock+1e-6f>=(1.f/30)) {
        r.clock=std::max(0.f,r.clock-(1.f/30));
        const int owned=int(std::count_if(enemies.begin(),enemies.end(),[&](const auto &child){return child.dukeChild&&child.dukeChild->cohort&&child.dukeChild->parent==e.id;})+
            std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &child){return child.dukeChild&&child.dukeChild->cohort&&child.dukeChild->parent==e.id;}));
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        const auto minimum=mul(Vector3{bounds.min.x+e.radius,0,bounds.min.z+e.radius},1/GaperMovementScale);
        const auto maximum=mul(Vector3{bounds.max.x-e.radius,0,bounds.max.z-e.radius},1/GaperMovementScale);
        const auto tick=sourceDukeTick(r,int(roomThreats()+pendingMonsters_.size()),owned,[&]{return uint32_t(combatRng.next());},false,minimum,maximum,35.f);
        if(tick.release)releaseDukeCohort(e,true);
        if(tick.sound)audioCues.push(AudioCueKind::MonsterAttack,e.position);
        e.bossAttack=r.state;e.state=r.state==4?EnemyState::Ready:EnemyState::Windup;e.stateTime=std::max(0.f,float(40-r.frame)*(1.f/30));
        r.pendingPhysics=true;
        if(!flushDukeBirths(e)){r.paused=true;e.velocity={};break;}
        physics();
    }
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    contact();
}
void Simulation::dukeDeath(Enemy &e,bool debugExecution) {
    auto &r=*e.duke;
    if(debugExecution){releaseDukeCohort(e,false);r.pending.clear();r.deathPrepared=true;r.deathPending=false;return;}
    if(!r.initialized){r.initialized=true;r.initSeed=uint32_t(combatRng.next());if(!r.initSeed)r.initSeed=1;}
    r.deathPending=true;
    if(!r.deathPrepared&&r.initSeed) {
        r.position=mul(horizontal(e.position),1/GaperMovementScale);r.momentum=mul(horizontal(e.velocity),(1.f/30)/GaperMovementScale);r.friction=1;
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        const auto minimum=mul(Vector3{bounds.min.x+e.radius,0,bounds.min.z+e.radius},1/GaperMovementScale);
        const auto maximum=mul(Vector3{bounds.max.x-e.radius,0,bounds.max.z-e.radius},1/GaperMovementScale);
        const int owned=int(std::count_if(enemies.begin(),enemies.end(),[&](const auto &child){return child.dukeChild&&child.dukeChild->cohort&&child.dukeChild->parent==e.id;})+
            std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &child){return child.dukeChild&&child.dukeChild->cohort&&child.dukeChild->parent==e.id;}));
        const auto tick=sourceDukeTick(r,int(roomThreats()+pendingMonsters_.size()),owned,[&]{return uint32_t(combatRng.next());},true,minimum,maximum,35.f);
        if(tick.release)releaseDukeCohort(e,true);
        releaseDukeCohort(e,false);
    }
    if(r.deathPrepared&&flushDukeBirths(e))r.deathPending=false;
}
void Simulation::reconcileDukeDeaths() {
    for(auto &enemy:enemies)if(enemy.duke&&enemy.duke->deathPending) {
        if(!enemy.duke->deathPrepared){if(enemy.duke->initSeed)dukeDeath(enemy);}
        else if(flushDukeBirths(enemy))enemy.duke->deathPending=false;
    }
}
} // namespace dw
