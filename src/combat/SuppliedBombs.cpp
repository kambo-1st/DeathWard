#include "combat/Simulation.hpp"

namespace dw {
const SuppliedBomb *Simulation::carriedBomb() const {
    const auto it=std::find_if(suppliedBombs.begin(),suppliedBombs.end(),[](const auto &b){return b.state==SuppliedBombState::Carried;});
    return it==suppliedBombs.end()?nullptr:&*it;
}
bool Simulation::createSuppliedBomb(Enemy &supplier,bool deathDrop) {
    const auto &rules=content->statue(supplier.monster)->supply;
    if(suppliedBombs.size()>=limits.suppliedBombs) {
        suppress({},"supplied bomb capacity");return false;
    }
    for(int attempt=0;attempt<160;++attempt) {
        const float radius=2+float(attempt/16)*.5f;
        auto at=add(supplier.position,rotateY(mul(supplier.statueFacing,radius),float(attempt%16)*2*Pi/16));
        at.y=.85f;
        if(arena.roomAt(at)!=room||arena.blocked(at,.55f)||!roomSpawnClear(at,.55f)||
            arena.path(player.position,at,.48f).empty())continue;
        if(std::any_of(suppliedBombs.begin(),suppliedBombs.end(),[&](const auto &b){return b.room==room&&
            b.state==SuppliedBombState::Pickup&&planarDistance(at,b.charge.position)<.65f;}))continue;
        SuppliedBomb bomb;bomb.id=nextEntity_++;bomb.supplier=supplier.id;bomb.room=room;
        bomb.rules=rules;bomb.deathDrop=deathDrop;
        bomb.charge.position=bomb.charge.origin=at;
        bomb.charge.position.y=(arena.canyon?arena.canyon->height(at.x,at.z):0)+.18f;
        bomb.charge.delay=rules.fuse;bomb.charge.radius=rules.radius;
        bomb.charge.blastDamage=rules.damage;bomb.charge.damage=rules.selfDamage;
        bomb.charge.settled=true;suppliedBombs.push_back(bomb);++supplier.supplyProduced;
        checkpointNeeded=true;return true;
    }
    return false; // Retry; never put mandatory supply inside cover or across a closed gate.
}
bool Simulation::takeNearbySuppliedBomb() {
    if(carriedBomb()||dead||finished||shopOpen||rewardOpen||player.hp<=0)return false;
    for(auto &bomb:suppliedBombs) {
        if(bomb.room!=room||bomb.state!=SuppliedBombState::Pickup||
            planarDistance(player.position,bomb.charge.position)>bomb.rules.pickupRadius||
            std::abs(player.position.y-(bomb.charge.position.y+.67f))>.5f||
            !arena.sight(player.position,add(bomb.charge.position,{0,.35f,0})))continue;
        bomb.state=SuppliedBombState::Carried;bomb.charge.age=0;
        bomb.charge.position=bomb.charge.origin=add(player.position,{0,.8f,0});
        if(!bomb.deathDrop)if(auto *supplier=findEnemy(bomb.supplier))supplier->supplyCooldown=bomb.rules.replenish;
        audioCues.push(AudioCueKind::Pickup,player.position);checkpointNeeded=true;
        return true;
    }
    return false;
}
bool Simulation::useSuppliedBomb(Vector3 target,bool place) {
    if(!std::isfinite(target.x)||!std::isfinite(target.z))return false;
    for(auto &bomb:suppliedBombs)if(bomb.state==SuppliedBombState::Carried) {
        auto &charge=bomb.charge;bomb.state=SuppliedBombState::Thrown;bomb.room=room;
        charge.position=add(player.position,{0,.4f,0});
        if(arena.trace(player.position,charge.position,.18f).hit)charge.position=player.position;
        charge.origin=charge.position;
        auto offset=horizontal(sub(target,player.position));
        if(length(offset)<.01f)offset=mul(player.facing,bomb.rules.range);
        if(length(offset)>bomb.rules.range)offset=mul(unit(offset),bomb.rules.range);
        charge.velocity=mul(offset,1/bomb.rules.flight);
        charge.velocity.y=(.18f-charge.position.y)/bomb.rules.flight+.5f*DynamiteGravity*bomb.rules.flight;
        charge.settled=false;
        if(place) {
            charge.position=player.position;
            charge.position.y=(arena.canyon?arena.canyon->height(player.position.x,player.position.z):0)+.18f;
            charge.velocity={};charge.settled=true;
        }
        // Taking starts the fuse. Neither throwing nor placing resets that clock.
        player.shootPose=.32f;audioCues.push(AudioCueKind::Warning,player.position);
        checkpointNeeded=true;return true;
    }
    return false;
}
void Simulation::updateSuppliedBombs(float dt) {
    for(auto &supplier:enemies)if(const auto *s=content->statue(supplier.monster);s&&s->attack==StatueAttack::Supply) {
        supplier.supplyCooldown=std::max(0.f,supplier.supplyCooldown-dt);
        if(supplier.supplyCooldown>0)continue;
        // Death drops are retained as bounded pending work if space/capacity is
        // temporarily unavailable. They are not silently lost or converted to inventory.
        while(supplier.supplyDeathPending>0) {
            if(!createSuppliedBomb(supplier,true))break;
            --supplier.supplyDeathPending;
        }
        if(supplier.supplyDeathPending>0){supplier.supplyCooldown=.25f;continue;}
        if(!supplier.alive||supplier.statueDisabled)continue;
        const bool stocked=std::any_of(suppliedBombs.begin(),suppliedBombs.end(),[&](const auto &bomb){
            return bomb.supplier==supplier.id&&!bomb.deathDrop&&bomb.state==SuppliedBombState::Pickup;
        });
        if(!stocked&&!createSuppliedBomb(supplier,false))supplier.supplyCooldown=.25f;
    }
    for(auto &bomb:suppliedBombs) {
        if(bomb.state==SuppliedBombState::Pickup)continue; // Unlit stock has no fuse.
        auto &charge=bomb.charge;
        if(bomb.state==SuppliedBombState::Carried) {
            bomb.room=room;charge.position=add(player.position,{0,.8f,0});
        } else if(bomb.room==room)advanceDynamite(charge,arena,std::min(dt,std::max(0.f,charge.delay-charge.age)));
        else continue; // Thrown ordnance pauses with its inactive room, like its actors.
        charge.age+=dt;
        if(charge.age<charge.delay)continue;
        Event blast;blast.type=EventType::Explosion;blast.position=charge.position;blast.origin=charge.origin;
        blast.damage=charge.blastDamage;blast.radius=charge.radius;blast.areaDamage=true;
        blast.playerDamage=charge.damage;blast.playerDamageHostile=false;
        blast.demolition=Demolition::SuppliedBomb;blast.armorPiercing=true;
        blast.ignoreAdaptiveArmor=true;
        blast.context.sourceEntity=bomb.id;queueRoot(blast);
        charge.alive=false;checkpointNeeded=true;
    }
    std::erase_if(suppliedBombs,[](const auto &bomb){return !bomb.charge.alive;});
}
} // namespace dw
