#include "combat/Simulation.hpp"

namespace dw {
namespace {
bool jetPathClear(const Arena &arena,int room,Vector3 from,Vector3 to) {
    const auto &bounds=arena.rooms.at(size_t(room)).bounds;
    if(to.x<bounds.min.x||to.x>bounds.max.x||to.z<bounds.min.z||to.z>bounds.max.z)return false;
    // Native generators accept grid class0/1 (including pits). Use a swept
    // solid test in3D: no tunnelling through narrow cover between jet centres.
    if(arena.trace(from,to,.05f).hit)return false;
    for(const auto &body:arena.movementBodies)if(segmentBox(from,to,body,.05f).hit)return false;
    return true;
}
}
bool FireWaveBurst::segment(int n,Vector3 &from,Vector3 &to) const {
    if(n<0||n>=rayCount||rules.jetStepFrames)return false;
    const float tail=std::max(0.f,(age-rules.trailDuration)*rules.speed);
    if(tail>=rays[size_t(n)].length)return false;
    from=add(origin,mul(directions[size_t(n)],tail));to=add(origin,mul(directions[size_t(n)],rays[size_t(n)].length));
    return true;
}
bool Simulation::createFireWave(const Projectile &projectile) {
    if(fireWaves.size()>=limits.fireWaves)return false;
    FireWaveBurst burst;burst.id=nextEntity_++;burst.source=projectile.context.sourceEntity;
    burst.room=room;burst.origin=projectile.position;burst.origin.y=.85f;burst.rules=projectile.fireWave;
    burst.context=projectile.context;
    // Landing on a wall/pit creates no fire on its far side. Move back just
    // outside a hit surface along the incoming projectile direction if possible.
    auto clear=[&](Vector3 p){return burst.rules.jetStepFrames?jetPathClear(arena,room,p,p):
        arena.roomAt(p)==room&&!arena.blocked(p,burst.rules.radius);};
    if(!clear(burst.origin)) {
        bool found=false;const auto back=unit(horizontal(projectile.velocity));
        for(int n=1;n<=8;++n) {
            auto at=sub(burst.origin,mul(back,float(n)*.125f));
            if(clear(at)) {burst.origin=at;found=true;break;}
        }
        if(!found)return true; // Impact absorbed by solid terrain; no remote fire.
    }
    fireWaves.push_back(burst);checkpointNeeded=true;return true;
}
bool Simulation::pulseFireJet(const FireWaveBurst &burst,const FireWaveJet &jet) {
    const bool allied=burst.context.damageSource==DamageSource::Player||burst.context.damageSource==DamageSource::Ally;
    std::vector<Event> hits;
    for(const auto &enemy:enemies) {
        if(!enemy.alive||enemy.fireContactCooldown>0||(allied&&enemy.friendly)||
           enemy.state==EnemyState::Buried||enemy.state==EnemyState::Teleporting)continue;
        // Installed50154b..50157b cancels pending damage whose EntityRef is
        // effect1000.147 with SpawnerType!=1. EntityRef+8 is SpawnerType, not
        // subtype: a player's fire jets remain effective. This does not grant
        // blanket Flame/Burning immunity or exclude friendly NPC producers.
        if(const auto *knight=content->knight(enemy.monster);knight&&knight->ignoreFireJets&&
            burst.context.damageSource!=DamageSource::Player)continue;
        const auto at=add(enemy.position,{0,enemy.lift,0});
        if(distance(jet.position,at)>burst.rules.radius+enemy.radius||!arena.sight(jet.position,at))continue;
        Event hit;hit.type=EventType::Damage;hit.context=burst.context;hit.target=enemy.id;
        hit.damage=burst.rules.jetMonsterDamage;hit.damageKind=DamageKind::Flame;hit.areaDamage=true;hit.harmsCompanions=!allied;
        hit.origin=jet.position;hit.position=at;hit.direction=unit(sub(at,jet.position));
        if(!sourceImmune(enemy,hit))hits.push_back(hit);
    }
    // Retain the whole pulse if its targets cannot be admitted. The player hit
    // is committed only together with the NPC hits, never repeatedly on retries.
    if(queue_.size()+hits.size()>limits.queuedEvents)return false;
    for(auto &hit:hits) {
        if(!queueRoot(hit))return false;
        if(auto *e=findEnemy(hit.target))e->fireContactCooldown=1;
    }
    if(!allied&&distance(jet.position,player.position)<=burst.rules.radius+.48f&&arena.sight(jet.position,player.position))
        hurtPlayer(burst.rules.damage,burst.context);
    return true;
}
void Simulation::updateFireJets(FireWaveBurst &burst,float dt) {
    const auto &p=burst.rules;burst.age+=dt;
    const float interval=float(p.jetStepFrames)/30;
    while(burst.jetStep<p.jetCount&&burst.age+1e-6f>=float(burst.jetStep+1)*interval) {
        ++burst.jetStep;
        for(int n=0;n<burst.rayCount;++n) {
            auto &ray=burst.rays[size_t(n)];if(ray.stopped)continue;
            const auto from=add(burst.origin,mul(burst.directions[size_t(n)],ray.length));
            const auto to=add(from,mul(burst.directions[size_t(n)],p.jetSpacing));
            if(!jetPathClear(arena,burst.room,from,to)){ray.stopped=true;continue;}
            ray.length+=p.jetSpacing;
            burst.jets.push_back({to,float(burst.jetStep)*interval,1-float(burst.jetStep)*p.jetScaleLoss,0});
            if(burst.jetStep==p.jetCount)ray.stopped=true;
        }
    }
    for(auto &jet:burst.jets) {
        const float age=burst.age-jet.born;
        for(const auto &[frame,bit]:{std::pair{p.jetPulseA,1u},std::pair{p.jetPulseB,2u}}) {
            if(age+1e-6f<float(frame)/30||jet.pulses&bit)continue;
            if(!pulseFireJet(burst,jet))break;
            jet.pulses|=bit;
        }
    }
    std::erase_if(burst.jets,[&](const auto &jet){return jet.pulses==3&&burst.age-jet.born>=float(p.jetLifeFrames)/30;});
}
void Simulation::updateFireWaves(float dt) {
    for(auto &burst:fireWaves) {
        if(burst.room!=room)continue;
        if(burst.rules.jetStepFrames){updateFireJets(burst,dt);continue;}
        const float previous=burst.age;burst.age+=dt;
        for(int n=0;n<burst.rayCount;++n) {
            auto &ray=burst.rays[size_t(n)];const auto axis=burst.directions[size_t(n)];
            const float goal=std::min(burst.rules.range,burst.age*burst.rules.speed);
            // Short spatial steps catch pits/room edges; swept trace catches thin
            // cover. A stopped ray leaves its existing trail to burn out.
            while(!ray.stopped&&ray.length<goal) {
                const float next=std::min(goal,ray.length+.2f);
                const auto from=add(burst.origin,mul(axis,ray.length)),to=add(burst.origin,mul(axis,next));
                const auto hit=arena.trace(from,to,burst.rules.radius);
                if(hit.hit) {
                    ray.length+=(next-ray.length)*std::max(0.f,hit.t-.001f);ray.stopped=true;break;
                }
                if(arena.roomAt(to)!=room||arena.blocked(to,burst.rules.radius)) {ray.stopped=true;break;}
                ray.length=next;
            }
            if(ray.length>=burst.rules.range)ray.stopped=true;
            // Include the trail that expired during this step in swept contact.
            // This prevents a large dt from jumping completely over the player.
            const float tail=std::max(0.f,(previous-burst.rules.trailDuration)*burst.rules.speed);
            if(tail>=ray.length)continue;
            const auto from=add(burst.origin,mul(axis,tail)),to=add(burst.origin,mul(axis,ray.length));
            const auto closest=add(from,mul(axis,std::clamp(dot(sub(player.position,from),axis),0.f,ray.length-tail)));
            Context source=burst.context;source.chainId=nextChain_++;source.generation=0;source.sourceEffect=-1;
            if(segmentSphere(from,to,player.position,burst.rules.radius+.48f)<=1&&arena.sight(closest,player.position))
                hurtPlayer(burst.rules.damage,source);
            Hazard field;field.kind=HazardKind::FireWave;field.origin=from;field.position=to;
            field.radius=burst.rules.radius;field.damage=burst.rules.damage;field.delay=0;field.duration=1;
            field.context=source;exposeMonstersToFire(field);
        }
    }
    std::erase_if(fireWaves,[](const auto &burst) {
        if(burst.rules.jetStepFrames)return burst.jets.empty()&&
            std::all_of(burst.rays.begin(),burst.rays.begin()+burst.rayCount,[](const auto &ray){return ray.stopped;});
        return std::all_of(burst.rays.begin(),burst.rays.begin()+burst.rayCount,[&](const auto &ray) {
            return ray.stopped&&burst.age>=ray.length/burst.rules.speed+burst.rules.trailDuration;
        });
    });
}
} // namespace dw
