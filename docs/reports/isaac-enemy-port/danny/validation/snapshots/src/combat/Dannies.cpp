#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::flushDannyShots(Enemy &e) {
    if(!e.danny||e.danny->pendingShots.empty())return true;
    const auto &shots=e.danny->pendingShots;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &x){return x.alive;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+shots.size()>limits.queuedEvents||size_t(live+queued)+shots.size()>limits.projectiles)return false;
    for(const auto &shot:shots)queueRoot(shot);
    e.danny->pendingShots.clear();return true;
}

void Simulation::dannyAttack(Enemy &e) {
    auto &r=*e.danny;const auto &p=*content->danny(e.monster);
    // Source FindSpawnedEntities counts the owner's persistent seed marker,
    // including a normal Rock Spider after it morphs into an ordinary Spider.
    int owned=0;
    for(const auto &child:enemies)if(child.alive&&child.summoner==e.id)++owned;
    for(const auto &child:pendingMonsters_)if(child.summoner==e.id)++owned;
    const int children=std::max(0,p.ownedLimit-owned);
    const auto aim=unit(horizontal(sub(player.position,e.position)));
    if(!p.coal)for(int n=0;n<p.total-children;++n) {
        const auto jitter=mul(rotateY({1,0,0},combatRng.real(0,2*Pi)),combatRng.real(0,p.scatter));
        auto velocity=mul(add(mul(aim,p.shotSpeed),jitter),p.scale*30);
        velocity.y=-combatRng.real(p.fallMin,p.fallMax)*1.5f;
        const float size=.9f+.4f*float(combatRng.bounded(2))+combatRng.real(0,.05f);
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin={e.position.x,p.shotHeight,e.position.z};
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shotDamage;
        shot.projectileKind=ProjectileKind::Rock;shot.projectileRadius=p.shotRadius*size;
        shot.projectileLife=p.shotLife;shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.shotRetention;
        r.pendingShots.push_back(shot);
    }
    for(int n=0;n<(p.coal?p.total:children);++n) {
        const bool living=n<children;
        const auto direction=rotateY(aim,combatRng.real(-p.childSpread*.5f,p.childSpread*.5f)*Pi/180);
        const auto at=add(e.position,mul(direction,p.childOffset*p.scale));
        const auto impulse=mul(direction,combatRng.real(p.childMin,p.childMax)*p.scale*30);
        const auto before=pendingMonsters_.size();
        // This acyclic spawn path must not inherit the generic generation cap.
        // Only actual spiders receive the source ownership marker; hot coals do not.
        queueMonster(living?p.child:p.coalBody,at,0,0,false,1,0,living?e.id:0,0,-1,{},true,{},impulse);
        if(pendingMonsters_.size()==before)continue;
        auto &born=pendingMonsters_.back();born.rockSpider=RockSpiderRuntime{};
        born.producer=e.id;
        born.rockSpider->initialized=true;born.rockSpider->height=p.childHeight;
        born.rockSpider->vertical=combatRng.real(p.childUpMin,p.childUpMax);
        if(living)++r.children;
    }
    ++r.attacks;r.fired=true;
    particleEffect(ParticleEffect::Stone,e.position,aim,.6f);
    audioCues.push(AudioCueKind::MonsterAttack,e.position);
    flushDannyShots(e);
}

void Simulation::updateDanny(Enemy &e,float dt) {
    const auto &p=*content->danny(e.monster);if(!e.danny)e.danny=DannyRuntime{};auto &r=*e.danny;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const bool pending=!r.pendingShots.empty();
    if(!flushDannyShots(e)){e.velocity={};return;}
    const bool wasWaiting=r.waitingBirths;
    r.waitingBirths=std::any_of(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &birth){return birth.producer==e.id;});
    // A bounded-capacity queue must not accumulate unbounded four-coal volleys.
    // Freeze this producer until its already-selected births can be admitted;
    // neither drop a payload nor invent an extra source population cap.
    if(r.waitingBirths){e.velocity={};return;}
    if(pending||wasWaiting)e.velocity=mul(r.momentum,p.scale*30);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;
            if(!r.initialized) {
                r.initialized=true;r.cooldown=p.initialMin+int(combatRng.bounded(unsigned(p.initialMax-p.initialMin+1)));
            } else if(r.frame>=0) {
                r.momentum=mul(r.momentum,p.attackRetention);
                ++r.frame;
                if(r.frame==p.shootFrame&&!r.fired)dannyAttack(e);
                if(r.frame>=p.attackFrames){r.frame=-1;r.fired=false;}
            } else {
                if(!e.railCarrier) {
                    if(e.path.empty()||planarDistance(r.destination,player.position)>.5f) {
                        r.destination=player.position;e.path=arena.path(e.position,r.destination,e.radius);
                    }
                    while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.3f)e.path.erase(e.path.begin());
                    const auto delta=horizontal(sub(e.path.empty()?e.position:e.path.front(),e.position));
                    const float sourceDistance=length(delta)/p.scale;
                    if(sourceDistance>1) {
                        const float force=std::min(sourceDistance*.1f,2.f)*p.pathForce;
                        r.momentum=add(mul(r.momentum,p.retention),mul(unit(delta),force));
                    } else r.momentum=mul(r.momentum,.5f);
                }
                const bool hurt=r.recentDamage>p.hurtThreshold;
                r.cooldown=std::max(0,r.cooldown-(hurt?2:1));
                bool attack=r.cooldown==0&&(combatRng.bounded(unsigned(p.chance))==0||
                    (hurt&&combatRng.bounded(unsigned(p.hurtChance))==0));
                // Installed SpawnerType906 blocks ordinary attacks for Hornfel
                // passengers; their carrier controls locomotion independently.
                const auto *parent=findEnemy(e.summoner);
                if(e.railCarrier||(parent&&parent->monster.type==906))attack=false;
                if(attack) {
                    const float range=planarDistance(e.position,player.position)/p.scale;
                    attack=range<p.nearRange||(range<p.farRange&&combatRng.bounded(unsigned(p.farChance))==0);
                }
                if(attack) {
                    auto counts=[&](MonsterId id){return p.coal?id==monsterId(33,2):(id==monsterId(85)||id.type==818);};
                    int population=0;
                    for(const auto &actor:enemies)if(actor.alive&&counts(actor.monster))++population;
                    for(const auto &birth:pendingMonsters_)if(counts(birth.id))++population;
                    if(population<p.roomLimit) {
                        r.frame=0;r.fired=false;r.cooldown=p.cooldown;
                        e.facing=unit(horizontal(sub(player.position,e.position)));
                        audioCues.push(AudioCueKind::Warning,e.position);
                    }
                }
            }
            // The native damage accumulator updates at the controller epilogue;
            // the faster cooldown/chance applies on the following source tick.
            r.recentDamage=std::max(0.f,r.recentDamage+r.incomingDamage-p.hurtDecay);r.incomingDamage=0;
            if(!r.pendingShots.empty()){e.velocity={};return;}
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position;
        if(!e.railCarrier)moveMonster(e,steerMonsterBodies(e,mul(r.momentum,p.scale*30)),step);
        if(r.frame<0&&length(e.velocity)>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(p.contact,{0,0,e.id,-1});
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.state=r.frame>=0&&r.frame<p.shootFrame?EnemyState::Windup:EnemyState::Ready;
    e.stateTime=e.state==EnemyState::Windup?float(p.shootFrame-r.frame)/30:0;
    e.target=player.position;
}
} // namespace dw
