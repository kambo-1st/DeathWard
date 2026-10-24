#include "combat/Simulation.hpp"

namespace dw {
const char *bossName(BossKind kind) {
    switch(kind) {
    case BossKind::Ridgeback:return "RIDGEBACK";
    case BossKind::PowderForeman:return "POWDER FOREMAN";
    case BossKind::StormMarshal:return "STORM MARSHAL";
    case BossKind::Sheriff:return "THE HOLLOW SHERIFF";
    default:return "CANYON GUARDIAN";
    }
}
const char *bossHint(const Enemy &e) {
    if(e.bossKind==BossKind::Ridgeback)return e.phase?"TWO CHARGES / BREAK COVER TO STUN":"DODGE THE LANE / PUNISH RECOVERY";
    if(e.bossKind==BossKind::PowderForeman)return "STEP INTO CHARGES TO KICK / WATCH THE FUSE";
    return e.phase?"SWEEP THEN VOLLEY / EACH ATTACK IS WARNED":"MOVE THROUGH THE OPEN GAP / PUNISH RECOVERY";
}
void Simulation::spawnCanyonBoss() {
    const auto id=spawn(EnemyKind::Boss,arena.rooms[size_t(room)].bossSpawn);
    auto *e=findEnemy(id);if(!e)return;
    e->bossKind=arena.profile.boss;e->radius=e->bossKind==BossKind::Ridgeback?1.2f:1.f;
    const float health=e->bossKind==BossKind::Ridgeback?620:e->bossKind==BossKind::PowderForeman?500:540;
    e->hp=e->maxHp=health+float(e->bossKind==BossKind::Ridgeback?100:80)*arena.profile.band;
    e->cooldown=1.2f;e->state=EnemyState::Ready;e->home=e->position;
}
void Simulation::updateCanyonBoss(Enemy &e,float dt) {
    if(e.bossKind!=BossKind::Ridgeback){updateFrontierBoss(e,dt);return;}
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};
    e.phase=e.hp<=e.maxHp*.5f?1:0;
    e.stateTime-=dt;e.cooldown-=dt;
    auto recover=[&](bool collided) {
        e.state=EnemyState::Stunned;e.stateTime=collided?2.f:1.35f;
        if(collided)e.bossCombo=0;
    };
    auto aim=[&] {
        e.state=EnemyState::Windup;e.stateTime=e.phase?.85f:1.15f;
        e.facing=unit(sub(player.position,e.position));
        e.target=add(e.position,mul(e.facing,std::min(16.f,distance(e.position,player.position)+4)));
        audioCues.push(AudioCueKind::Warning,e.position);
    };
    if(e.state==EnemyState::Stunned) {
        if(e.stateTime<=0) {
            if(e.bossCombo>0) {--e.bossCombo;aim();}
            else {e.state=EnemyState::Ready;e.cooldown=.6f;}
        }
        return;
    }
    if(e.state==EnemyState::Ready) {
        e.facing=unit(sub(player.position,e.position));
        if(e.cooldown>0)return;
        // Burrow toward a safe, visible landing. Never teleport onto the player or
        // into evidence, water, gates, cover or outside this room.
        const auto &layout=arena.rooms[size_t(room)];
        const float start=float((e.bossCycles*5+int(seed_%16))%16)*Pi/8;
        e.target=e.position;
        for(int n=0;n<16;++n) {
            const auto p=add(layout.center,{std::cos(start+n*Pi/8)*7.5f,0,std::sin(start+n*Pi/8)*7.5f});
            if(distance(p,player.position)<6||arena.blocked(p,e.radius+.4f)||!roomSpawnClear(p,e.radius))continue;
            e.target=p;break;
        }
        e.state=EnemyState::Buried;e.stateTime=.75f;++e.bossCycles;
        audioCues.push(AudioCueKind::Warning,e.target);
        return;
    }
    if(e.state==EnemyState::Buried) {
        if(e.stateTime>0)return;
        // A player can walk onto the marker; wait rather than emerge through them.
        if(distance(e.target,player.position)<2.7f){e.stateTime=.1f;return;}
        e.position=e.target;e.state=EnemyState::Exposed;e.stateTime=.7f;
        particleEffect(ParticleEffect::Dirt,e.position,{0,1,0},.7f);
        return;
    }
    if(e.state==EnemyState::Exposed) {
        if(e.stateTime<=0){e.bossCombo=e.phase?1:0;aim();}
        return;
    }
    if(e.state==EnemyState::Windup) {
        // Aim is committed for the entire warning and charge, including phase two.
        if(e.stateTime<=0){e.state=EnemyState::Charging;e.stateTime=1.25f;}
        return;
    }
    if(e.state==EnemyState::Charging) {
        const auto from=e.position;
        const float travel=std::min(15.f*dt,distance(e.position,e.target));
        const auto to=add(from,mul(e.facing,travel));
        SegmentHit hit;
        for(const auto &wall:arena.walls) {
            const auto candidate=segmentBox(from,to,wall,e.radius);
            if(candidate.hit&&(!hit.hit||candidate.t<hit.t))hit=candidate;
        }
        // Movement traces use a footprint, not a projectile sphere that would
        // intersect flat ground whenever the boss radius exceeds its center height.
        const bool terrain=!arena.clear(from,to,e.radius)||arena.blocked(to,e.radius);
        if(hit.hit||terrain) {
            // A charge can crush only fragile rocks. It cannot open caches, seams,
            // story routes or infinite resource sources.
            for(auto &prop:arena.breakables)if(prop.room==room&&prop.solid()&&prop.kind==BreakableKind::CrackedRock&&
                segmentBox(from,to,prop.bounds,e.radius+.04f).hit) {
                hitBreakable(prop,1,true);payBreakables();
            }
            arena.rebuildWalls();
            if(hit.hit)e.position=add(from,mul(sub(to,from),std::max(0.f,hit.t-.02f)));
            recover(true);audioCues.push(AudioCueKind::StoneHit,e.position);
        } else {
            e.position=to;e.velocity=mul(e.facing,15);
            if(segmentSphere(from,to,player.position,e.radius+.48f)<=1&&arena.sight(from,player.position))hurtPlayer(16);
            if(distance(e.position,e.target)<.05f||e.stateTime<=0)recover(false);
        }
    }
}
void Simulation::rewardCanyonBoss(const Enemy &enemy) {
    auto &progress=rooms[size_t(room)];
    for(auto &p:projectiles)if(p.hostile&&p.context.sourceEntity==enemy.id){p.alive=false;p.cancelled=true;}
    // Cancel queued attacks too. The death transition can occur before another
    // attack emitted in the same tick reaches the front of the event queue.
    std::erase_if(queue_,[&](const Event &e) {
        if(e.context.sourceEntity!=enemy.id||(!e.hostile&&!e.playerDamageHostile))return false;
        auto it=chains.find(e.context.chainId);if(it!=chains.end()&&it->second.queued)--it->second.queued;
        return true;
    });
    clearHazards(true);
    for(auto &prop:arena.breakables)if(prop.room==room&&prop.kind==BreakableKind::PowderBarrel)prop.fuse=-1;
    if(progress.bossPaid)return;
    progress.bossPaid=true;
    const auto at=arena.rooms[size_t(room)].center;
    moneyPickups.push_back({at,6+2*std::max(0,arena.profile.band),0,true});
    // Supply, never a required key or a healing-on-kill loop.
    dynamite=std::min(MaxDynamite,dynamite+1);
    checkpointNeeded=true;
}
} // namespace dw
