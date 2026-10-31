#include "combat/Simulation.hpp"

namespace dw {
void Simulation::damageEnvironmentActor(Enemy &e,const Event &hit) {
    if(!e.environment)return;
    auto &state=*e.environment;const auto &p=*content->environmentActor(e.monster);
    if(hit.debugExecution){e.alive=false;e.railCarrier=0;state={};return;}
    if(e.rockSpider&&e.rockSpider->height<content->rockSpider(e.monster)->entityHeight&&hit.areaDamage&&!hit.execution)return;
    if(state.spent||state.destructionPending||e.state==EnemyState::Teleporting)return;
    if(p.kind==EnvironmentActorKind::Fireplace&&hit.damageKind!=DamageKind::Physical)return;
    const bool ignition=p.kind==EnvironmentActorKind::Tnt&&hit.damageKind==DamageKind::Flame;
    if(!ignition&&(!std::isfinite(hit.damage)||hit.damage<=0))return;
    ++state.hits;state.baseLoss+=hit.damage/p.damageScale>10?2:1;
    state.accumulatedDamage+=std::max(0.f,hit.damage/p.damageScale);
    state.explosiveHit|=hit.explosionDamage||hit.execution||ignition;
    e.flash=.12f;audioCues.push(AudioCueKind::StoneHit,e.position);
    if(p.kind==EnvironmentActorKind::Tnt&&!e.railCarrier&&!hit.areaDamage)
        e.velocity=add(e.velocity,mul(unit(horizontal(hit.direction)),std::min(p.pushSpeed,2.f)));
}

void Simulation::reconcileEnvironmentActors() {
    for(auto &e:enemies) {
        if(!e.alive||!e.environment)continue;
        auto &state=*e.environment;const auto &p=*content->environmentActor(e.monster);
        if(state.hits&&!state.spent&&!state.destructionPending) {
            if(p.kind==EnvironmentActorKind::Fireplace||p.kind==EnvironmentActorKind::HotCoal) {
                const bool force=state.explosiveHit||(p.kind==EnvironmentActorKind::Fireplace&&state.accumulatedDamage>=1000);
                float loss=float(state.baseLoss);
                // Source processes the queued normal-fire hits individually.
                for(uint64_t i=0;i<state.hits;++i)if(combatRng.bounded(3)==0)loss+=1;
                e.hp=std::max(1.f,e.hp-loss);
                if(force||e.hp<1.5f){state.spent=true;e.hp=1;e.phase=1;
                    if(p.kind==EnvironmentActorKind::HotCoal)e.alive=false;
                }
            } else {
                // TNT batches damage, regardless of ordinary shot strength.
                const float loss=state.explosiveHit?4.f:1.f+float(combatRng.bounded(3)==0);
                e.hp=std::max(1.f,e.hp-loss);
                if(e.hp<=1)state.destructionPending=true;
            }
            state.hits=state.baseLoss=0;state.explosiveHit=false;state.accumulatedDamage=0;
            if(state.spent){particleEffect(ParticleEffect::Dirt,e.position,{0,1,0},.5f);checkpointNeeded=true;}
        }
        if(!state.destructionPending)continue;
        Event blast;blast.type=EventType::Explosion;blast.position=blast.origin=e.position;
        blast.damage=p.blastDamage;blast.radius=p.blastRadius;blast.playerDamage=p.blastPlayerDamage;
        blast.playerDamageHostile=blast.harmsCompanions=true;blast.explosionLineCheck=false;
        blast.context.sourceEntity=e.id;blast.demolition=Demolition::EnemyBomb;
        if(!queueRoot(blast))continue; // One retained mandatory blast; no lost or repeated detonation.
        state.destructionPending=false;state.spent=true;e.phase=1;e.hp=.5f;
        if(e.railCarrier){e.alive=false;e.railCarrier=0;}
        Event destroyed;destroyed.type=EventType::RoomHazardDestroyed;destroyed.target=e.id;destroyed.position=e.position;
        destroyed.context.sourceEntity=e.id;queueRoot(destroyed);
        checkpointNeeded=true;
    }
}

bool Simulation::environmentActionsPending() const {
    return std::any_of(enemies.begin(),enemies.end(),[](const auto &e){
        return e.alive&&e.environment&&(e.environment->hits||e.environment->destructionPending);
    });
}

void Simulation::updateEnvironmentActor(Enemy &e,float dt) {
    auto &state=*e.environment;const auto &p=*content->environmentActor(e.monster);
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Teleporting||state.spent||state.destructionPending)return;
    if(p.kind==EnvironmentActorKind::Fireplace) {
        // A mounted fireplace is above flooded ground; a floor fireplace goes out.
        if(!e.railCarrier&&arena.rooms[size_t(room)].flooded){state.spent=true;e.hp=1;e.phase=1;return;}
        if(!e.railCarrier&&segmentSphere(playerStepStart_,player.position,e.position,e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(p.contact,{0,0,e.id,-1});
        Hazard fire;fire.kind=HazardKind::Fire;fire.position=fire.origin=e.position;fire.radius=e.radius;
        fire.delay=0;fire.duration=1;fire.damage=p.contact;fire.harmsMonsters=true;fire.monsterDamageInterval=p.contactInterval;
        fire.context={nextChain_++,0,e.id,-1};exposeMonstersToFire(fire);
        return;
    }
    if(e.railCarrier)return;
    // Ground TNT uses physical pushing rather than AI locomotion. World mass,
    // speed and overlap resolution are local3D adaptations, bounded by walls/pits.
    e.velocity=mul(e.velocity,std::pow(p.pushRetention,dt*30));
    auto displace=[&](Vector3 from,float radius,Vector3 direction) {
        auto away=horizontal(sub(e.position,from));const float separation=length(away),reach=radius+e.radius;
        if(separation>=reach||std::abs(e.position.y-from.y)>e.radius+radius)return;
        const auto normal=separation>.0001f?mul(away,1/separation):unit(horizontal(direction));
        e.position=arena.move(e.position,mul(normal,std::min(reach-separation+.01f,p.pushSpeed*dt)),e.radius);
        e.velocity=mul(normal,p.pushSpeed);
    };
    e.position=arena.move(e.position,mul(e.velocity,dt),e.radius);
    displace(player.position,.48f,player.velocity);
    const auto away=horizontal(sub(player.position,e.position));const float separation=length(away),reach=.48f+e.radius;
    if(separation<reach&&separation>.0001f&&std::abs(e.position.y-player.position.y)<reach)
        player.position=arena.move(player.position,mul(away,(reach-separation)/separation),.48f);
    for(const auto &other:enemies)if(other.id!=e.id&&other.alive&&!other.railCarrier&&!other.environment&&
        other.state!=EnemyState::Teleporting&&other.state!=EnemyState::Buried)displace(other.position,other.radius,other.velocity);
}
} // namespace dw
