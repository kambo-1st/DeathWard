#include "combat/Simulation.hpp"

namespace dw {
void Simulation::hitBreakable(Breakable &prop,float damage,bool hard) {
    if (!prop.solid() || prop.kind==BreakableKind::CacheSide || damage<=0) return;
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
    // Snapshot ALL recipients before any collision changes. Never let vector order
    // turn a single blast into a shot through the cover it has just destroyed.
    std::vector<EntityId> victims;
    for(const auto &enemy:enemies)
        if(enemy.alive&&!(e.hostile&&enemy.id==e.context.sourceEntity)&&
           distance(enemy.position,e.position)<e.radius+enemy.radius&&arena.sight(e.position,enemy.position))
            victims.push_back(enemy.id);
    const bool playerHit=e.playerDamage>0&&distance(player.position,e.position)<e.radius+.48f&&
                         arena.sight(e.position,player.position);
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
        if(dist<e.radius && (dist<.001f||arena.sight(e.position,endpoint)))props.push_back(i);
    }
    for(auto id:victims) {
        Event damage=e;damage.type=EventType::Damage;damage.target=id;damage.areaDamage=true;
        emit(damage,e.context);
    }
    if(playerHit)hurtPlayer(e.playerDamage,e.context,e.playerDamageHostile);
    for(auto i:props)hitBreakable(arena.breakables[i],e.damage,e.demolition==Demolition::SpentDynamite);
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
        particleEffect(ParticleEffect::Stone,mul(add(p.bounds.min,p.bounds.max),.5f),{0,1,0},.65f);
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
        // Each finite barrel is an independent delayed source. Root acceptance and all
        // descendants use the normal event limits. Barrels NEVER inherit hard demolition.
        queueRoot(blast);
    }
}
} // namespace dw
