#include "combat/Simulation.hpp"

namespace dw {
int Simulation::selectHornfelRoute(bool reserveMain) {
    const auto &h=*rooms[size_t(room)].hornfel;const auto &rail=*arena.rails;
    auto candidates=[&](bool excludePrevious) {
        std::vector<int> result;
        for(size_t i=0;i<rail.paths.size();++i) {
            const auto &p=rail.paths[i];
            auto conflicts=[&](const RailCartRuntime &cart) {
                const auto &other=rail.paths[size_t(cart.route)];
                return p.entry==other.entry||p.entry==other.exit||p.exit==other.entry||p.exit==other.exit;
            };
            if((reserveMain||excludePrevious)&&h.mainReserved&&conflicts(h.cart))continue;
            if(std::any_of(h.decoys.begin(),h.decoys.end(),[&](const auto &d){return !d.finished&&conflicts(d.cart);}))continue;
            if(std::any_of(h.traffic.passengers.begin(),h.traffic.passengers.end(),[&](const auto &r){return !r.finished&&conflicts(r.cart);}))continue;
            // Native door picker avoids the arrival door within60 native units.
            // Our active-time grace uses the generated room's entry point.
            if(h.activeAge<1&&planarDistance(rail.doors[size_t(p.entry)],arena.rooms[size_t(room)].entry)<=6)continue;
            result.push_back(int(i));
        }
        return result;
    };
    auto choices=candidates(!reserveMain);
    // Single-route source templates need reuse. Never relax another rider's reservation.
    if(choices.empty()&&!reserveMain)choices=candidates(false);
    return choices.empty()?-1:choices[combatRng.bounded(uint32_t(choices.size()))];
}

void Simulation::selectHornfelDecoys() {
    auto &h=*rooms[size_t(room)].hornfel;const auto &p=*content->hornfelDecoy(monsterId(906,1));
    h.decoySelected=false;
    if(h.decoyCooldown>0||h.activeAge<p.startDelay||p.chance==0)return;
    // Native API registrations independently identify alive enemies minus alive
    // bosses <2. Our room hazards are excluded from that ordinary enemy count.
    const auto others=std::count_if(enemies.begin(),enemies.end(),[&](const auto &e){
        const auto *d=content->monster(e.monster);
        return e.alive&&!e.friendly&&e.id!=h.owner&&!content->monsterBoss(e.monster)&&(!d||!d->roomHazard);
    });
    if(others>=2||combatRng.bounded(10000)>=uint32_t(p.chance))return;
    const auto &layout=*arena.profile.bossRails;
    const int count=(layout.width+2)*(layout.height+2)>135?p.largeCount:p.smallCount;
    for(int i=0;i<count&&h.decoys.size()<limits.enemies;++i) {
        const int route=selectHornfelRoute(true);if(route<0)break;
        HornfelDecoyRuntime d;d.cart.route=route;d.opening=content->hornfel(p.owner)->doorTime;
        const auto at=arena.rails->paths[size_t(route)].sample(0);d.cart.position=at.position;d.cart.direction=at.direction;
        h.decoys.push_back(std::move(d));h.decoySelected=true;
    }
    if(h.decoySelected)h.decoyCooldown=p.cooldown;
}

void Simulation::damageHornfelDecoy(Enemy &e,const Event &event) {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot)return;
    auto it=std::find_if(slot->decoys.begin(),slot->decoys.end(),[&](const auto &d){return d.actor==e.id;});
    if(it==slot->decoys.end()||it->finished||e.state==EnemyState::Teleporting)return;
    auto &d=*it;
    if(event.debugExecution) {e.alive=false;d.finished=true;d.cart.visible=false;d.cart.intact=false;return;}
    if(event.damage<=0||!std::isfinite(event.damage))return;
    const auto &p=*content->hornfelDecoy(e.monster);
    ++d.acceptedHits;d.baseLoss+=event.damage/p.damageScale>10?2:1;d.explosiveHit|=event.explosionDamage;
    e.flash=.12f;audioCues.push(AudioCueKind::StoneHit,e.position);
    if(!event.areaDamage)particleEffect(ParticleEffect::Wood,e.position,mul(event.direction,-1));
    Event hit=event;hit.type=EventType::EnemyDamaged;hit.position=e.position;emit(hit,event.context);
}

void Simulation::reconcileHornfelDecoys() {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot)return;
    for(auto &d:slot->decoys) {
        if(d.finished||!d.acceptedHits)continue;
        auto *e=findEnemy(d.actor);if(!e||!e->alive)continue;
        float loss=float(d.baseLoss);
        if(d.explosiveHit)loss=e->hp;
        else for(uint64_t i=0;i<d.acceptedHits;++i)if(combatRng.bounded(3)==0)loss+=1;
        stats.damageDealt+=std::min(e->hp,loss);e->hp-=loss;
        d.acceptedHits=d.baseLoss=0;d.explosiveHit=false;
        if(e->hp<1.5f) {
            e->hp=std::max(1.f,e->hp);e->alive=false;e->velocity={};
            d.finished=d.deathPending=true;d.cart.position=e->position;d.cart.visible=d.cart.intact=false;
            // Death aftermath is retained independently of the erased actor.
            // No independent boss reward, enemy kill, or item-on-kill dispatch.
            checkpointNeeded=true;
        }
    }
}

void Simulation::updateHornfelDecoys(float dt) {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot||!arena.rails)return;
    auto &h=*slot;const auto &p=*content->hornfelDecoy(monsterId(906,1));
    const auto &root=*content->hornfel(p.owner);const auto &rail=*arena.rails;
    std::vector<bool> doors(h.doors.size());
    for(size_t i=0;i<doors.size();++i)doors[i]=h.doors[i].requested;
    if(const auto *traffic=content->railTraffic(p.owner))for(const auto &r:h.traffic.passengers) {
        if(r.finished||r.cart.route<0||doors.empty())continue;
        const auto &route=rail.paths[size_t(r.cart.route)];
        doors[size_t(route.entry)]=true;
        if(route.length()-r.cart.distance<traffic->speed*root.doorTime+2)doors[size_t(route.exit)]=true;
    }
    for(auto &d:h.decoys) {
        if(d.deathPending) {
            const auto &rules=*content->enemyBomb(p.bomb);
            if(d.bombVelocities.empty())for(int i=0;i<p.bombCount;++i) {
                const float speed=combatRng.real(p.bombSpeedMin,p.bombSpeedMax),angle=combatRng.real(0,2*Pi);
                d.bombVelocities.push_back(rotateY({speed,0,0},angle));
            }
            // Admission is atomic: neither a partial ring nor repeated direct blast.
            if(enemyBombs.size()+pendingEnemyBombs.size()+d.bombVelocities.size()>limits.enemyBombs+limits.pendingEnemyBombs||
                queue_.size()>=limits.queuedEvents||limits.eventsPerChain==0||limits.maxDepth<0)continue;
            Event blast;blast.type=EventType::Explosion;blast.position=blast.origin=d.cart.position;
            blast.damage=p.blastDamage;blast.radius=p.blastRadius;blast.playerDamage=p.playerDamage;
            blast.hostile=blast.areaDamage=blast.harmsCompanions=blast.playerDamageHostile=true;
            blast.explosionLineCheck=false;blast.explosionIgnore=h.owner;blast.context.sourceEntity=d.actor;blast.demolition=Demolition::EnemyBomb;
            if(!queueRoot(blast))continue;
            for(auto velocity:d.bombVelocities) {
                EnemyBomb b;b.id=nextEntity_++;b.source=d.actor;b.sourceMonster=monsterId(906,1);b.blastIgnore=h.owner;
                b.ordnance=rules.ordnance;b.room=room;b.rules=rules;b.configured=true;
                auto &c=b.charge;c.kind=HazardKind::MonsterBomb;c.position=c.origin=d.cart.position;
                c.delay=rules.fuse;c.radius=rules.radius;c.blastDamage=rules.damage;c.damage=rules.playerDamage;c.velocity=velocity;
                queueEnemyBomb(b);
            }
            particleEffect(ParticleEffect::Wood,d.cart.position,{0,1,0},1);
            d.deathPending=false;++h.decoysDestroyed;continue;
        }
        if(d.finished)continue;
        const auto &route=rail.paths[size_t(d.cart.route)];
        doors[size_t(route.entry)]=true;
        if(!d.actor) {
            if(h.completed||!h.cart.intact){d.finished=true;continue;}
            if(livingEnemies()+pendingMonsters_.size()>=limits.enemies)continue;
            d.actor=spawn(EnemyKind::Monster,add(d.cart.position,{0,.85f+.25f,0}));if(!d.actor)continue;
            auto &e=enemies.back();e.monster=monsterId(906,1);e.radius=content->monster(e.monster)->radius;
            e.hp=e.maxHp=4;e.state=EnemyState::Teleporting;e.bossAttack=-1;e.facing=d.cart.direction;
            d.cart.id=nextEntity_++;d.cart.rider=e.id;++h.decoysSpawned;continue;
        }
        auto *e=findEnemy(d.actor);
        if(!e||!e->alive){d.finished=true;d.cart.visible=false;continue;}
        e->age+=dt;e->flash=std::max(0.f,e->flash-dt);e->velocity={};
        doors[size_t(route.entry)]=true;d.opening-=dt;
        if(d.opening>.00001f)continue;
        d.cart.visible=true;e->state=EnemyState::Ready;
        auto travel=route.advance(d.cart.distance,p.speed*dt);d.cart.distance=travel.distance;
        d.cart.position=travel.pose.position;d.cart.direction=travel.pose.direction;
        e->position=add(d.cart.position,{0,e->radius+.25f,0});e->facing=d.cart.direction;e->velocity=mul(e->facing,p.speed);
        if(route.length()-d.cart.distance<p.speed*root.doorTime+2)doors[size_t(route.exit)]=true;
        for(auto segment:travel.swept) {
            segment[0].y=segment[1].y=player.position.y;
            if(segmentSphere(segment[0],segment[1],player.position,e->radius+.48f)<=1) {
                hurtPlayer(p.contact,{0,0,e->id,-1});
                // Pinned Hornfel behavior: walking into a dummy destroys it.
                // Contact consumes the dummy even when player invulnerability
                // suppresses HP loss; the queued aftermath still obeys capacity.
                ++d.acceptedHits;d.explosiveHit=true;break;
            }
        }
        if(travel.pose.finished&&!d.acceptedHits) {
            e->alive=false;e->velocity={};d.finished=true;d.cart.visible=d.cart.intact=false;++h.decoysRemoved;
        }
    }
    for(size_t i=0;i<doors.size();++i)h.doors[i].openness=std::clamp(h.doors[i].openness+(doors[i]?dt:-dt)/root.doorTime,0.f,1.f);
    std::erase_if(h.decoys,[](const auto &d){return d.finished&&!d.deathPending;});
}
} // namespace dw
