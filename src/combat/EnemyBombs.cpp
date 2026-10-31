#include "combat/Simulation.hpp"

namespace dw {
void Simulation::queueDeathBlast(Enemy &enemy) {
    if(!enemy.deathBlastPending)return;
    const auto &p=*content->deathBlast(enemy.monster);
    const bool explode=!p.onlySelf||enemy.selfDetonated;
    const int shots=enemy.selfDetonated?p.selfShots:p.shots;
    const auto queuedShots=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
    // Admit the whole death payload, retaining the dead body as its carrier
    // until every required channel is available. No partial ring or lost bomb.
    const auto events=size_t(shots)+size_t(explode);
    if(events&&(limits.eventsPerChain==0||limits.maxDepth<0||queue_.size()+events>limits.queuedEvents||
        (shots&&projectiles.size()+size_t(queuedShots+shots)>limits.projectiles)))return;
    if(!p.bomb.empty()&&enemyBombs.size()>=limits.enemyBombs&&pendingEnemyBombs.size()>=limits.pendingEnemyBombs)return;
    if(explode) {
        Event blast;blast.type=EventType::Explosion;blast.position=blast.origin=enemy.position;
        blast.damage=p.damage;blast.radius=p.radius;blast.playerDamage=p.playerDamage;
        blast.areaDamage=blast.harmsCompanions=blast.playerDamageHostile=true;
        blast.demolition=Demolition::EnemyBomb;blast.context.sourceEntity=enemy.id;
        queueRoot(blast);
    }
    for(int i=0;i<shots;++i) {
        Event shot;shot.position=shot.origin=enemy.position;shot.direction=rotateY({1,0,0},p.angle+float(i)*2*Pi/float(shots));
        shot.hostile=true;shot.speed=p.shotSpeed;shot.damage=p.shotDamage;shot.projectileLife=5;
        shot.context.sourceEntity=enemy.id;queueRoot(shot);
    }
    if(!p.bomb.empty()) {
        const auto &rules=*content->enemyBomb(p.bomb);
        EnemyBomb bomb;bomb.id=nextEntity_++;bomb.source=enemy.id;bomb.sourceMonster=enemy.monster;
        bomb.ordnance=rules.ordnance;bomb.room=room;bomb.rules=rules;bomb.configured=true;
        auto &c=bomb.charge;c.kind=HazardKind::MonsterBomb;c.position=c.origin=enemy.position;
        c.delay=rules.fuse+(rules.fuseJitterFrames?float(combatRng.bounded(unsigned(rules.fuseJitterFrames+1)))/30:0);
        c.radius=rules.radius;c.blastDamage=rules.damage;c.damage=rules.playerDamage;
        c.position.y=(arena.canyon?arena.canyon->height(c.position.x,c.position.z):0)+.18f;c.settled=true;
        queueEnemyBomb(bomb);
    }
    enemy.deathBlastPending=false;
}
void Simulation::reconcileDeathBlasts() {
    for(auto &enemy:enemies)queueDeathBlast(enemy);
}
EntityId Simulation::throwEnemyBomb(std::string_view profile,EntityId source,Vector3 start,Vector3 target,bool place) {
    const auto *rules=content->enemyBomb(profile);const auto *owner=findEnemy(source);
    const auto finite=[](Vector3 p){return std::isfinite(p.x)&&std::isfinite(p.y)&&std::isfinite(p.z);};
    const auto &bounds=arena.rooms.at(size_t(room)).bounds;
    const bool railProducer=owner&&content->hornfel(owner->monster)&&start.x>=bounds.min.x&&start.x<=bounds.max.x&&start.z>=bounds.min.z&&start.z<=bounds.max.z;
    if(!rules||!owner||!owner->alive||owner->friendly||!finite(start)||!finite(target)||(!railProducer&&arena.roomAt(start)!=room))return 0;
    EnemyBomb bomb;bomb.id=nextEntity_++;bomb.source=source;bomb.sourceMonster=owner->monster;
    bomb.ordnance=rules->ordnance;bomb.room=room;bomb.rules=*rules;bomb.configured=true;
    auto &c=bomb.charge;c.kind=HazardKind::MonsterBomb;c.position=c.origin=start;
    c.delay=rules->fuse+(rules->fuseJitterFrames?float(combatRng.bounded(unsigned(rules->fuseJitterFrames+1)))/30:0);
    c.radius=rules->radius;c.blastDamage=rules->damage;c.damage=rules->playerDamage;
    if(!place) {
        auto delta=horizontal(sub(target,start));if(length(delta)>rules->range)delta=mul(unit(delta),rules->range);
        target=add(start,delta);target.y=(arena.canyon?arena.canyon->height(target.x,target.z):0)+.18f;
        c.velocity=mul(sub(target,start),1/rules->flight);c.velocity.y+=.5f*DynamiteGravity*rules->flight;
    } else {
        const float ground=(arena.canyon?arena.canyon->height(start.x,start.z):0)+.18f;
        if(start.y<=ground+.02f){c.position.y=ground;c.settled=true;}
    }
    return queueEnemyBomb(bomb)?bomb.id:0;
}

bool Simulation::queueEnemyBomb(EnemyBomb bomb) {
    if(bomb.charge.delay<=0&&detonateEnemyBomb(bomb)&&!bomb.charge.alive)return true;
    if(enemyBombs.size()<limits.enemyBombs)enemyBombs.push_back(bomb);
    else if(pendingEnemyBombs.size()<limits.pendingEnemyBombs)pendingEnemyBombs.push_back(bomb);
    else {suppress({},"enemy bomb capacity");return false;}
    checkpointNeeded=true;return true;
}

bool Simulation::detonateEnemyBomb(EnemyBomb &bomb) {
    if(bomb.detonated)return true;
    const auto &p=bomb.rules;
    const int shots=bomb.configured&&p.payload==EnemyBombPayload::Sad?p.shots:0;
    // Reserve the complete blast/ring before acceptance. Capacity pressure keeps
    // the armed bomb pending, not a half-emitted ring or a vanished explosion.
    const auto queuedShots=std::count_if(queue_.begin(),queue_.end(),[](const auto &e){return e.type==EventType::Shot;});
    if(limits.eventsPerChain==0||limits.maxDepth<0||queue_.size()+size_t(1+shots)>limits.queuedEvents||
       (shots&&projectiles.size()+size_t(queuedShots+shots)>limits.projectiles))return false;
    Event blast;blast.type=EventType::Explosion;blast.position=bomb.charge.position;blast.origin=bomb.charge.origin;
    blast.damage=bomb.charge.blastDamage;blast.radius=bomb.charge.radius;blast.playerDamage=bomb.charge.damage;
    blast.hostile=blast.areaDamage=blast.harmsCompanions=blast.playerDamageHostile=true;
    blast.demolition=Demolition::EnemyBomb;blast.context.sourceEntity=bomb.id;
    // Physical source Bomb bodies carry IGNORE_ARMOR. Delayed NPC explosion
    // markers share this scheduler but are not source Bomb entities.
    blast.ignoreAdaptiveArmor=!bomb.blastMarker;
    if(bomb.configured&&!p.harmsSource)blast.explosionIgnore=bomb.source;
    if(bomb.blastIgnore)blast.explosionIgnore=bomb.blastIgnore;
    queueRoot(blast);
    const auto muzzle=add(bomb.charge.position,{0,.67f,0});
    for(int i=0;i<shots;++i) {
        Event shot;shot.position=shot.origin=muzzle;shot.direction=rotateY({1,0,0},float(i)*2*Pi/float(shots));
        shot.hostile=true;shot.speed=p.shotSpeed;shot.damage=p.shotDamage;shot.projectileLife=p.shotLife;
        shot.context.sourceEntity=bomb.id;queueRoot(shot);
    }
    bomb.detonated=true;bomb.effectAge=0;checkpointNeeded=true;
    if(bomb.configured&&p.payload==EnemyBombPayload::Brimstone) {
        for(size_t i=0;i<bomb.beamEnds.size();++i) {
            auto end=add(muzzle,mul(rotateY({1,0,0},float(i)*Pi/2),p.beamRange));
            const auto hit=arena.trace(muzzle,end,p.beamRadius);
            if(hit.hit)end=add(muzzle,mul(sub(end,muzzle),std::max(0.f,hit.t-.001f)));
            bomb.beamEnds[i]=end;
        }
    } else if(!bomb.configured||p.payload!=EnemyBombPayload::Hot)bomb.charge.alive=false;
    return true;
}

void Simulation::updateEnemyBombEffect(EnemyBomb &bomb,float dt) {
    const auto &p=bomb.rules;const float before=bomb.effectAge;bomb.effectAge+=dt;
    const float duration=p.payload==EnemyBombPayload::Hot?p.fieldDuration:p.beamDuration;
    if(before>=duration){bomb.charge.alive=false;return;}
    // These are ordnance-owned fields. They survive producer death and room
    // clear, and pause with the bomb in inactive rooms. No player item scaling.
    Hazard field;field.delay=0;field.age=before;field.duration=duration;
    field.context={nextChain_++,0,bomb.id,-1};field.position=field.origin=add(bomb.charge.position,{0,.67f,0});
    if(p.payload==EnemyBombPayload::Hot) {
        field.kind=HazardKind::Fire;field.radius=p.fieldRadius;field.damage=p.fieldDamage;
        if(planarDistance(player.position,field.position)<field.radius+.3f&&
           std::abs(player.position.y-field.position.y)<1&&arena.sight(field.position,player.position))hurtPlayer(field.damage,field.context);
        exposeMonstersToFire(field);
    } else if(p.payload==EnemyBombPayload::Brimstone) {
        field.kind=HazardKind::Beam;field.radius=p.beamRadius;field.damage=p.beamDamage;
        for(auto end:bomb.beamEnds) {
            field.position=end;
            if(segmentSphere(field.origin,end,player.position,field.radius+.48f)<=1&&arena.sight(field.origin,player.position))
                hurtPlayer(field.damage,field.context);
            exposeCompanionsToHazard(field,before);
        }
    }
    if(bomb.effectAge>=duration)bomb.charge.alive=false;
}

void Simulation::updateEnemyBombs(float dt) {
    for(auto it=pendingEnemyBombs.begin();it!=pendingEnemyBombs.end()&&enemyBombs.size()<limits.enemyBombs;) {
        if(it->room!=room){++it;continue;}
        enemyBombs.push_back(*it);it=pendingEnemyBombs.erase(it);
    }
    for(auto &bomb:enemyBombs) {
        if(bomb.room!=room)continue;
        if(bomb.detonated){updateEnemyBombEffect(bomb,dt);continue;}
        auto &c=bomb.charge;const auto previous=c.position;
        if(!bomb.blastMarker)advanceDynamite(c,arena,std::min(dt,std::max(0.f,c.delay-c.age)));
        if(bomb.configured&&bomb.rules.payload==EnemyBombPayload::Hot&&
           segmentSphere(sub(previous,playerStepStart_),sub(c.position,player.position),{},.7f)<=1&&arena.sight(c.position,player.position))
            hurtPlayer(bomb.rules.contactDamage,{0,0,bomb.id,-1});
        c.age+=dt;if(c.age>=c.delay)detonateEnemyBomb(bomb);
    }
    std::erase_if(enemyBombs,[](const auto &bomb){return !bomb.charge.alive;});
}
} // namespace dw
