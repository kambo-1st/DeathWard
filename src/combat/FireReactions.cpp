#include "combat/Simulation.hpp"

namespace dw {
void Simulation::addFire(Vector3 position,float radius,float duration,float damage,bool harmsMonsters,
                         bool harmsPlayer,Context context) {
    if(!std::isfinite(radius)||!std::isfinite(duration)||!std::isfinite(damage)||
       !std::isfinite(position.x)||!std::isfinite(position.y)||!std::isfinite(position.z)||
       radius<=0||radius>100||duration<=0||duration>120||damage<0||damage>1000000)return;
    Hazard fire;fire.kind=HazardKind::Fire;fire.position=fire.origin=position;
    fire.radius=radius;fire.duration=duration;fire.delay=0;fire.damage=damage;
    fire.harmsMonsters=harmsMonsters;fire.harmsPlayer=harmsPlayer;fire.context=context;
    if(!context.sourceEntity&&context.damageSource==DamageSource::Unspecified)
        fire.context.damageSource=DamageSource::Environment;
    addHazard(fire);
}

bool Simulation::transformMonster(Enemy &enemy,MonsterId target,TransformHealth policy) {
    const auto *definition=content->monster(target);
    if(!definition||enemy.kind!=EnemyKind::Monster||!enemy.alive||enemy.hp<=0||
       (enemy.partner&&!enemy.friendly)||enemy.formation)return false;
    const float ratio=std::clamp(enemy.hp/std::max(.001f,enemy.maxHp),0.f,1.f);
    // Preserve scaled offspring/champion health relative to its original definition.
    const auto *before=content->monster(enemy.monster);
    const bool targetFlight=enemy.targetHop&&enemy.targetHop->airborne;
    const bool rockMorph=content->rockSpider(enemy.monster)&&content->rockSpider(target);
    const auto rockVelocity=enemy.velocity;
    const float rockLift=enemy.lift;
    if(targetFlight&&!enemy.targetHop->transformedFlight)
        enemy.targetHop->transformedFlight=*content->targetHop(enemy.monster);
    const float scale=enemy.maxHp/before->hp;
    enemy.monster=target;enemy.maxHp=definition->hp*scale;
    enemy.hp=policy==TransformHealth::Fraction?enemy.maxHp*ratio:std::min(enemy.hp,enemy.maxHp);
    // Compatible body radii/navigation modes were validated by the content loader.
    // A temporary size/status change on the live body remains intact.
    const bool stunned=enemy.state==EnemyState::Stunned;const float stun=enemy.stateTime;
    enemy.state=stunned?EnemyState::Stunned:enemy.hop.active||targetFlight?EnemyState::Jumping:EnemyState::Ready;
    enemy.stateTime=stunned?stun:0;
    enemy.behavior={};enemy.phase=0;enemy.auxiliary=0;enemy.trailTime=0;enemy.lift=0;
    enemy.lob=content->lobWalker(target)?std::optional<LobWalkerRuntime>{LobWalkerRuntime{}}:std::nullopt;
    enemy.headShooter.reset();
    enemy.buzz.reset();
    enemy.path.clear();enemy.pathTime=0;if(!targetFlight)enemy.velocity={};
    enemy.cooldown=definition->cooldown;enemy.flash=.12f;
    // Fire changes the rock's material/force; it does not restart its reveal,
    // skitter counter or committed heading, including a thrown rock's bounce.
    if(rockMorph){enemy.velocity=rockVelocity;enemy.lift=rockLift;}
    // Entity ID, summoner, team, position, animation clock and existing shots are
    // not recreated. This is neither a kill nor an offspring/reward event.
    return true;
}

float Simulation::reactToFire(Enemy &enemy,const Event &event) {
    if(event.execution||(event.damageKind!=DamageKind::Flame&&event.damageKind!=DamageKind::Burning)||enemy.kind!=EnemyKind::Monster)return 1;
    const auto *rule=content->fireReaction(enemy.monster);
    if(!rule)return 1;
    const bool flooded=room>=0&&room<arena.roomCount()&&arena.rooms[size_t(room)].flooded;
    if(rule->dryOnly&&flooded)return 1;
    const bool flame=event.damageKind==DamageKind::Flame;
    const float scale=flame?rule->flameScale:rule->burningScale;
    const bool trigger=rule->trigger==FireTrigger::Both||
        (flame?rule->trigger==FireTrigger::Flame:rule->trigger==FireTrigger::Burning);
    if(trigger&&rule->transform)transformMonster(enemy,*rule->transform,rule->health);
    return scale; // The triggering hit uses the original body's reaction once.
}

void Simulation::exposeMonstersToFire(const Hazard &fire) {
    if(!fire.alive||fire.age<fire.delay||fire.age>=fire.delay+fire.duration)return;
    for(auto &enemy:enemies) {
        if(!enemy.alive||enemy.id==fire.context.sourceEntity||enemy.kind!=EnemyKind::Monster||enemy.fireContactCooldown>0||
           (enemy.environment&&enemy.environment->spent)||
           enemy.state==EnemyState::Buried||enemy.state==EnemyState::Teleporting)continue;
        // Hostile patches preserve existing native-enemy friendly-fire policy.
        // They still expose explicitly reactive bodies to flame contact.
        const bool harmsAlly=enemy.friendly&&(fire.harmsPlayer||fire.harmsMonsters);
        if(const auto *swarm=content->swarmSpider(enemy.monster);swarm&&swarm->playerObjectsOnly) {
            const auto *source=findEnemy(fire.context.sourceEntity);
            const auto *sourceProfile=source?content->environmentActor(source->monster):nullptr;
            if(sourceProfile&&sourceProfile->kind==EnvironmentActorKind::Fireplace)continue;
        }
        const auto *environment=content->environmentActor(enemy.monster);
        const bool ignitable=environment&&environment->kind==EnvironmentActorKind::Tnt;
        if(!fire.harmsMonsters&&!content->fireReaction(enemy.monster)&&!harmsAlly&&!ignitable)continue;
        const auto *c=content->charge(enemy.monster);const bool tail=c&&c->tailRadius>0;
        const auto body=tail?chargeTailPosition(enemy):add(enemy.position,{0,enemy.lift,0});
        const float radius=tail?c->tailRadius*enemy.radius:enemy.radius;
        auto contact=fire.position;
        if(fire.kind==HazardKind::FireWave) {
            const auto axis=unit(horizontal(sub(fire.position,fire.origin)));
            contact=add(fire.origin,mul(axis,std::clamp(dot(sub(body,fire.origin),axis),0.f,planarDistance(fire.origin,fire.position))));
        }
        if(planarDistance(body,contact)>=fire.radius+radius||
           std::abs(body.y-contact.y)>radius+.6f||!arena.sight(contact,body))continue;
        Event hit;hit.type=EventType::Damage;hit.damageKind=DamageKind::Flame;
        hit.target=enemy.id;hit.position=tail?contact:body;hit.origin=contact;hit.radius=fire.radius;
        hit.direction=unit(sub(body,contact));hit.areaDamage=true;
        hit.hostile=!fire.harmsMonsters;hit.damage=(fire.harmsMonsters||harmsAlly)?fire.damage:0;
        emit(hit,fire.context);
        // Shared target cooldown bounds overlapping patches; .5s is local fire
        // contact tuning, not a measured Isaac interval. Direct burn hits do not use it.
        enemy.fireContactCooldown=std::clamp(fire.monsterDamageInterval,Tick,120.f);
    }
}
} // namespace dw
