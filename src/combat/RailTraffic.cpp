#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateRailTraffic(float dt) {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot||!arena.rails)return;
    auto &h=*slot;auto &t=h.traffic;const auto *p=content->railTraffic(monsterId(906));
    if(!p||!p->enabled||t.stopped)return;
    const auto &rail=*arena.rails;
    auto reset=[&](bool initial) {
        int counts=p->initialMin+int(combatRng.bounded(uint32_t(p->initialMax-p->initialMin+1)));
        const auto &layout=*arena.profile.bossRails;
        if(!initial&&(layout.width+2)*(layout.height+2)>p->largeArea)counts/=p->largeDivisor;
        t.timeout=t.lifespan=counts;t.expired=false;
    };
    t.clock+=dt;
    while(t.clock+.000001f>=1/p->tickRate) {
        t.clock-=1/p->tickRate;++t.ticks;
        if(!t.initialized){t.initialized=true;reset(true);}
        else if(t.expired&&std::any_of(enemies.begin(),enemies.end(),[&](const auto &e){
            return e.alive&&content->monsterBoss(e.monster);
        })) {
            ++t.attempts;
            const int route=selectHornfelRoute(true);
            if(route<0)++t.blocked;
            else {
                const auto &choice=p->passengers[combatRng.bounded(uint32_t(p->passengers.size()))];
                // Pending native identities retain their slots. Never replace an
                // unported creature with another payload or ordinary generic AI.
                if(!choice.available)++t.unavailable;
                else if(t.passengers.size()>=limits.enemies||livingEnemies()+pendingMonsters_.size()>=limits.enemies)++t.capacityRejected;
                else {
                    const auto pose=rail.paths[size_t(route)].sample(0);
                    const auto actor=spawnMonster(choice.actor,pose.position);
                    if(actor) {
                        RailPassengerRuntime rider;rider.actor=actor;rider.opening=p->doorTime;
                        rider.cart.id=nextEntity_++;rider.cart.rider=actor;rider.cart.route=route;
                        rider.cart.position=pose.position;rider.cart.direction=pose.direction;
                        auto *e=findEnemy(actor);e->railCarrier=rider.cart.id;e->generation=1;
                        e->position=add(pose.position,{0,e->radius+.25f,0});e->facing=pose.direction;
                        e->state=EnemyState::Teleporting;
                        // Source SpawnerType906 is attribution, not a death-linked
                        // Parent. Current room's traffic owns only the carrier.
                        e->summoner=h.owner;
                        e->spawnerType=906;
                        t.passengers.push_back(std::move(rider));++t.spawned;
                    } else ++t.capacityRejected;
                }
            }
            reset(false); // Failed admission consumes the complete interval too.
        }
        // Native controller runs before the common effect timeout epilogue.
        if(t.timeout>0&&--t.timeout==0)t.expired=true;
    }
    for(auto &r:t.passengers) {
        if(r.finished)continue;
        auto *e=findEnemy(r.actor);
        if(!e||!e->alive) {
            r.emptyTime+=dt;r.cart.rider=0;
            // Source ordinary empty cart breaks after more than two updates.
            if(r.emptyTime+.000001f>=3/p->tickRate) {
                r.finished=true;r.cart.visible=r.cart.intact=false;++t.destroyed;
                particleEffect(ParticleEffect::Wood,r.cart.position,{0,1,0},.6f);
            }
            continue;
        }
        r.opening-=dt;if(r.opening>.00001f)continue;
        r.cart.visible=true;if(e->state==EnemyState::Teleporting)e->state=EnemyState::Ready;
        const auto &route=rail.paths[size_t(r.cart.route)];
        const auto travel=route.advance(r.cart.distance,p->speed*dt);
        r.cart.distance=travel.distance;r.cart.position=travel.pose.position;r.cart.direction=travel.pose.direction;
        e->position=add(r.cart.position,{0,e->radius+.25f,0});e->velocity=mul(r.cart.direction,p->speed);
        if(const auto *rule=content->environmentActor(e->monster)) {
            e->facing=r.cart.direction;
            if(rule->kind==EnvironmentActorKind::Fireplace&&e->environment&&!e->environment->spent) {
                for(auto segment:travel.swept) {
                    segment[0].y=segment[1].y=player.position.y;
                    if(segmentSphere(segment[0],segment[1],player.position,e->radius+.48f)<=1)
                        hurtPlayer(rule->contact,{0,0,e->id,-1});
                    Hazard fire;fire.kind=HazardKind::FireWave;fire.origin=segment[0];fire.position=segment[1];
                    fire.radius=e->radius;fire.duration=1;fire.damage=rule->contact;
                    fire.harmsMonsters=true;fire.monsterDamageInterval=rule->contactInterval;fire.context={nextChain_++,0,e->id,-1};
                    exposeMonstersToFire(fire);
                }
            }
        }
        if(travel.pose.finished&&!(e->environment&&(e->environment->hits||e->environment->destructionPending))) {
            // Leaving the room uses Remove, not Kill: no death recipe, loot or
            // hazard detonation. Pending mandatory destruction gets first claim.
            e->alive=false;e->railCarrier=0;e->velocity={};
            r.finished=true;r.cart.visible=r.cart.intact=false;++t.removed;
        }
    }
    std::erase_if(t.passengers,[](const auto &r){return r.finished;});
}

void Simulation::clearRailTraffic() {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot)return;
    auto &h=*slot;auto &t=h.traffic;t.stopped=true;
    for(auto &r:t.passengers)if(auto *e=findEnemy(r.actor)) {
        e->alive=false;e->railCarrier=0;e->velocity={};
    }
    t.passengers.clear();
    for(auto &d:h.decoys)if(!d.deathPending) {
        if(auto *e=findEnemy(d.actor)){e->alive=false;e->velocity={};}
        d.finished=true;d.cart.visible=d.cart.intact=false;
    }
    // Source room clear removes the doors and attached riders. Freely moving
    // escorts/offspring are separate threats and prevent reaching this point.
    h.doors.clear();h.mainReserved=false;h.cart.visible=false;
}
} // namespace dw
