#include "combat/Simulation.hpp"

namespace dw {
void Simulation::advanceRockWave(Hazard &wave,float dt) {
    if(wave.rockWave){advanceSteppedRockWave(wave,dt);return;}
    wave.previous=wave.position;
    auto end=add(wave.position,mul(wave.velocity,std::min(dt,std::max(0.f,wave.duration-(wave.age-dt)))));
    const bool leavesRoom=arena.roomAt(end)!=room;
    if(leavesRoom) {
        float low=0,high=1;
        for(int i=0;i<16;++i) {
            const float middle=(low+high)*.5f;
            if(arena.roomAt(add(wave.previous,mul(sub(end,wave.previous),middle)))==room)low=middle;
            else high=middle;
        }
        end=add(wave.previous,mul(sub(end,wave.previous),low));
    }
    const auto hit=arena.trace(wave.position,end,wave.radius);
    wave.position=hit.hit?add(wave.previous,mul(sub(end,wave.previous),std::max(0.f,hit.t-.001f))):end;
    // Keep cover intact while resolving swept contacts. A wall opened by this
    // crest cannot retroactively expose actors behind it to that same crest.
    if(arena.roomAt(player.position)==room&&!wave.hitPlayer&&segmentSphere(wave.previous,wave.position,player.position,wave.radius+.48f)<=1&&
        arena.sight(wave.previous,player.position))wave.hitPlayer=hurtPlayer(wave.damage,wave.context);
    exposeCompanionsToHazard(wave,wave.age-dt);
    if(hit.hit) {
        bool changed=false;
        for(auto &prop:arena.breakables) {
            if(!prop.solid()||prop.room!=room||prop.kind==BreakableKind::CacheSide)continue;
            const auto contact=segmentBox(wave.previous,end,prop.bounds,wave.radius);
            if(!contact.hit||std::abs(contact.t-hit.t)>.0001f)continue;
            // The current optional cache wall is the declared DeathWard secret-
            // entrance analogue. Ordinary cracks also break; ore/resource gates
            // and structural walls remain protected. No bomb inventory is spent.
            if(prop.kind==BreakableKind::CacheGate||prop.kind==BreakableKind::CrackedRock) {
                prop.destroyed=true;changed=true;
            }
        }
        if(changed) {
            arena.rebuildWalls();for(auto &enemy:enemies)enemy.pathTime=0;payBreakables();
        }
        wave.alive=false; // One obstacle per wave, including a wall it opens.
    }
    if(leavesRoom)wave.alive=false;
}
bool Simulation::pulseRockWave(const Hazard &wave,Vector3 at) {
    const auto &p=wave.rockWave->rules;
    std::vector<Event> hits;
    for(const auto &e:enemies) {
        if(!e.alive||e.id==wave.context.sourceEntity||e.state==EnemyState::Buried||e.state==EnemyState::Teleporting||
            arena.roomAt(e.position)!=room||distance(at,add(e.position,{0,e.lift,0}))>=p.radius+e.radius)continue;
        Event hit;hit.type=EventType::Damage;hit.context=wave.context;hit.target=e.id;hit.damage=p.monsterDamage;
        hit.damageKind=DamageKind::Crush;hit.demolition=Demolition::RockWave;hit.areaDamage=true;hit.hostile=true;
        hit.radius=p.radius;hit.harmsCompanions=true;hit.position=e.position;hit.origin=at;hit.direction=unit(sub(e.position,at));hits.push_back(hit);
    }
    const bool playerHit=!player.launch&&arena.roomAt(player.position)==room&&distance(at,player.position)<p.radius+.48f;
    const bool playerEvent=playerHit&&!godMode&&player.hurt<=0&&player.dodge<=0;
    if(((!hits.empty()||playerEvent)&&!limits.eventsPerChain)||queue_.size()+hits.size()+size_t(playerEvent)>limits.queuedEvents)return false;
    for(auto &hit:hits)if(!queueRoot(hit))return false;
    // The native crush pulse disables its entity line check. Its terrain scan
    // still checks cover. A raised player is outside the ground pulse.
    if(playerHit)
        hurtPlayer(p.playerDamage,wave.context);
    std::vector<size_t> props;
    for(size_t i=0;i<arena.breakables.size();++i) {
        const auto &b=arena.breakables[i];
        if(!b.solid()||b.room!=room||b.kind==BreakableKind::CacheSide||b.kind==BreakableKind::OreSeam)continue;
        Vector3 surface{std::clamp(at.x,b.bounds.min.x,b.bounds.max.x),at.y,std::clamp(at.z,b.bounds.min.z,b.bounds.max.z)};
        const auto delta=sub(surface,at);const float dist=length(delta);
        if(dist<p.radius&&(dist<.001f||arena.sight(at,sub(surface,mul(unit(delta),.025f)))))props.push_back(i);
    }
    bool changed=false;
    for(size_t i:props) {
        auto &b=arena.breakables[i];
        if(b.kind==BreakableKind::PowderBarrel){hitBreakable(b,p.monsterDamage,true);continue;}
        b.destroyed=true;changed=true;
    }
    if(changed){arena.rebuildWalls();for(auto &e:enemies)e.pathTime=0;payBreakables();}
    particleEffect(ParticleEffect::Stone,at,{0,1,0},.4f);return true;
}
void Simulation::advanceSteppedRockWave(Hazard &wave,float dt) {
    auto &r=*wave.rockWave;const auto &p=r.rules;r.clock+=dt;
    const float interval=float(p.stepFrames)/30;
    while(wave.alive&&r.clock+1e-6f>=interval) {
        const int frame=r.frame+p.stepFrames;
        auto rng=r.rng;float angle=0;
        if(frame>p.jitterStart)angle=rng.real(-p.jitterDegrees,p.jitterDegrees)*
            std::min(1.f,float(frame-p.jitterStart)/float(p.jitterRamp))*Pi/180;
        const auto direction=rotateY(r.heading,angle),from=wave.position;
        auto to=add(from,mul(direction,p.spacing));
        // Swept terrain collision is the 3D adaptation of native grid stepping.
        // It prevents tunnelling through thin props; pits/room edges consume it.
        if(arena.roomAt(to)!=room){wave.alive=false;break;}
        const auto hit=arena.trace(from,to,.01f);
        if(!hit.hit&&arena.blocked(to,0)){wave.alive=false;break;}
        if(hit.hit)to=add(from,mul(sub(to,from),std::max(0.f,hit.t-.001f)));
        if(!pulseRockWave(wave,to))break; // Same point/RNG/frame retries atomically.
        r.clock=std::max(0.f,r.clock-interval);r.frame=frame;r.rng=rng;
        wave.previous=from;wave.position=to;wave.velocity=mul(direction,p.spacing/interval);
        r.trail.push_back(to);if(r.trail.size()>8)r.trail.erase(r.trail.begin());
        if(hit.hit||frame>=p.lifeFrames)wave.alive=false;
    }
}
void Simulation::hitBreakable(Breakable &prop,float damage,bool hard) {
    if (!prop.solid() || prop.kind==BreakableKind::CacheSide || damage<=0) return;
    if(prop.kind==BreakableKind::Dung) {
        const auto &profile=*content->dung();
        const int loss=hard?profile.hits:1+int(combatRng.bounded(unsigned(profile.bonusChance))==0)+int(combatRng.bounded(unsigned(profile.bonusChance))==0);
        prop.health=std::max(0,prop.health-loss);prop.destroyed=prop.health==0;
        particleEffect(ParticleEffect::Dirt,mul(add(prop.bounds.min,prop.bounds.max),.5f),{0,1,0},.4f);
        if(prop.destroyed){arena.rebuildWalls();for(auto &enemy:enemies)enemy.pathTime=0;payBreakables();}
        return;
    }
    if (prop.kind==BreakableKind::PowderBarrel) {
        if(prop.fuse>=0)return;
        prop.health-=int(std::ceil(damage));
        if(prop.health<=0)prop.fuse=.65f;
        return;
    }
    if(!hard)return;
    if(--prop.health>0) {
        particleEffect(ParticleEffect::Stone, mul(add(prop.bounds.min,prop.bounds.max),.5f),{0,1,0},.55f);
        return;
    }
    prop.destroyed=true;
}
void Simulation::resolveExplosion(const Event &e) {
    igniteGas(e.position,e.radius);
    // Snapshot ALL recipients before any collision changes. Never let vector order
    // turn a single blast into a shot through the cover it has just destroyed.
    std::vector<EntityId> victims;
    for(const auto &enemy:enemies) {
        const auto *c=content->charge(enemy.monster);const bool tail=c&&c->tailRadius>0;
        const auto target=tail?chargeTailPosition(enemy):enemy.position;
        const float radius=tail?c->tailRadius*enemy.radius:enemy.radius;
        if(enemy.alive&&enemy.id!=e.explosionIgnore&&!(e.hostile&&enemy.id==e.context.sourceEntity)&&
           distance(target,e.position)<e.radius+radius&&(!e.explosionLineCheck||arena.sight(e.position,target)))
            victims.push_back(enemy.id);
    }
    const bool playerHit=e.playerDamage>0&&distance(player.position,e.position)<e.radius+.48f&&
                         (!e.explosionLineCheck||arena.sight(e.position,player.position));
    std::vector<size_t> props;
    for(size_t i=0;i<arena.breakables.size();++i) {
        const auto &p=arena.breakables[i];
        if(!p.solid()||p.kind==BreakableKind::CacheSide)continue;
        const Vector3 surface{std::clamp(e.position.x,p.bounds.min.x,p.bounds.max.x),
                              std::clamp(e.position.y,p.bounds.min.y,p.bounds.max.y),
                              std::clamp(e.position.z,p.bounds.min.z,p.bounds.max.z)};
        const float dist=distance(surface,e.position);
        // Stop just outside the nearest surface, so the target cannot block its own ray.
        const auto endpoint=dist>.025f?sub(surface,mul(unit(sub(surface,e.position)),.025f)):e.position;
        if(dist<e.radius && (!e.explosionLineCheck||dist<.001f||arena.sight(e.position,endpoint)))props.push_back(i);
    }
    for(auto id:victims) {
        if(auto *eye=findEnemy(id))if(const auto *rule=content->component(eye->monster)) {
            const auto away=unit(horizontal(sub(eye->position,e.position)));
            eye->facing=unit(add(eye->facing,mul(away,rule->bombDeflection)));
        }
        Event damage=e;damage.type=EventType::Damage;damage.target=id;damage.areaDamage=true;damage.explosionDamage=true;
        emit(damage,e.context);
    }
    if(playerHit)hurtPlayer(e.playerDamage,e.context,e.playerDamageHostile);
    for(auto i:props)hitBreakable(arena.breakables[i],e.damage,
        e.demolition==Demolition::SpentDynamite||e.demolition==Demolition::SuppliedBomb||e.demolition==Demolition::EnemyBomb);
    if(!props.empty()) {
        arena.rebuildWalls();
        // Planned paths cannot retain a former collision boundary after demolition.
        for(auto &enemy:enemies)enemy.pathTime=0;
        payBreakables();
    }
}
void Simulation::payBreakables() {
    for(auto &p:arena.breakables) {
        if(!p.destroyed||p.paid)continue;
        p.paid=true; // Includes no-loot rolls: re-entry and duplicate hits never reroll.
        Random rng(p.lootSeed);
        int coins=0;
        if(p.kind==BreakableKind::CrackedRock)coins=rng.bounded(5)==0?1+int(rng.bounded(2)):0;
        if(p.kind==BreakableKind::OreSeam)coins=3+int(rng.bounded(4));
        if(p.kind==BreakableKind::CacheGate) {
            coins=8+int(rng.bounded(5));
            arena.keys.push_back({p.room,add(p.rewardPosition,{.6f,0,0}),false});
        }
        if(coins>0)moneyPickups.push_back({p.rewardPosition,coins,0,true});
        particleEffect(p.kind==BreakableKind::Dung?ParticleEffect::Dirt:ParticleEffect::Stone,mul(add(p.bounds.min,p.bounds.max),.5f),{0,1,0},.65f);
        checkpointNeeded=true;
    }
}
void Simulation::updateBreakables(float dt) {
    for(auto &p:arena.breakables) {
        // Offscreen room simulation remains dormant like its enemies. Returning resumes
        // the telegraphed fuse; no remote detonation can hit the player through a corridor.
        if(p.destroyed||p.fuse<0||p.room!=room)continue;
        p.fuse-=dt;
        if(p.fuse>0)continue;
        p.destroyed=true;p.paid=true;
        arena.rebuildWalls();
        Event blast;blast.type=EventType::Explosion;
        blast.position=mul(add(p.bounds.min,p.bounds.max),.5f);blast.origin=blast.position;
        blast.damage=80;blast.radius=3.6f;blast.playerDamage=20;
        blast.harmsCompanions=true; // Neutral scenery explosion, not a player's own bomb.
        blast.context.damageSource=DamageSource::Tnt; // The powder barrel is DeathWard's scenery-TNT analogue.
        // Each finite barrel is an independent delayed source. Root acceptance and all
        // descendants use the normal event limits. Barrels NEVER inherit hard demolition.
        queueRoot(blast);
    }
}
} // namespace dw
