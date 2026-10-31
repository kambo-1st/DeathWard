#include "combat/Simulation.hpp"

namespace dw {
void Simulation::selectHornfelEscorts() {
    auto &h=*rooms[size_t(room)].hornfel;const auto &p=*content->hornfel(monsterId(906));
    h.escortPending=false;
    if(h.state!=HornfelState::Riding||!p.escortChance||combatRng.bounded(uint32_t(p.escortChance)))return;
    int population=0;
    for(const auto &e:enemies)population+=e.alive&&e.monster.type==819;
    for(const auto &e:pendingMonsters_)population+=e.id.type==819;
    for(const auto &b:enemyBombs)population+=b.charge.alive&&b.ordnance==monsterId(4,14);
    for(const auto &b:pendingEnemyBombs)population+=b.charge.alive&&b.ordnance==monsterId(4,14);
    if(population>=p.escortLimit)return;
    const auto entry=arena.rails->paths[size_t(h.cart.route)].sample(0);
    if(planarDistance(entry.position,player.position)<=p.escortClearance)return;
    h.escortEntry=entry.position;h.escortDirection=entry.direction;h.escortPending=true;
}

void Simulation::spawnHornfelEscorts() {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot||!slot->escortPending)return;
    auto &h=*slot;h.escortPending=false;
    if(h.completed||!h.cart.intact||h.state!=HornfelState::Riding)return;
    const auto &p=*content->hornfel(monsterId(906));const auto &fly=*content->monster(p.escort);
    const auto &follow=*content->flyBomb(p.escort);
    // Optional pair: bounded, all-or-none admission on this entry. Do not retry
    // a new pair halfway across the room or reroll its position under pressure.
    if(livingEnemies()+pendingMonsters_.size()+size_t(p.escortCount)>limits.enemies){++h.escortGroupsSkipped;return;}
    std::vector<Vector3> positions,velocities;
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    for(int n=0;n<p.escortCount;++n) {
        const auto velocity=rotateY(h.escortDirection,combatRng.real(-p.escortSpread,p.escortSpread)*Pi/180);
        auto at=add(h.escortEntry,rotateY({p.escortRadius,0,0},combatRng.real(0,2*Pi)));
        // Native rail entrances extend beyond the room. Flight bodies use our
        // interior collision footprint; an outward random offset cannot strand them.
        at.x=std::clamp(at.x,bounds.min.x+fly.radius+.02f,bounds.max.x-fly.radius-.02f);
        at.z=std::clamp(at.z,bounds.min.z+fly.radius+.02f,bounds.max.z-fly.radius-.02f);
        if(arena.flightBlocked(at,fly.radius,room)){++h.escortGroupsSkipped;return;}
        positions.push_back(at);velocities.push_back(velocity);
    }
    const auto count=enemies.size();
    for(int n=0;n<p.escortCount;++n) {
        const auto id=spawnMonster(p.escort,positions[size_t(n)]);
        if(!id){enemies.resize(count);++h.escortGroupsSkipped;return;}
        auto &e=enemies.back();e.summoner=h.owner;e.generation=findEnemy(h.owner)->generation+1;e.facing=velocities[size_t(n)];
        e.flyFollow=FlyBombFollowRuntime{h.owner,0,uint64_t(h.activeAge*30),velocities[size_t(n)],{},player.position};
        e.velocity=mul(velocities[size_t(n)],follow.followScale*30);
    }
    ++h.escortGroups;h.escortsSpawned+=p.escortCount;
}

void Simulation::releaseHornfelEscorts(EntityId owner) {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot||slot->owner!=owner)return;
    const auto &p=*content->hornfel(monsterId(906));
    for(auto &e:enemies)if(e.alive&&e.flyFollow&&e.flyFollow->parent==owner) {
        e.hp=std::min(e.hp,p.escortReleaseHp);e.flyFollow.reset();e.path.clear();e.pathTime=0;
        ++slot->escortsReleased;
    }
}
} // namespace dw
