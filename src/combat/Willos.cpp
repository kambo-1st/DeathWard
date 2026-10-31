#include "combat/Simulation.hpp"

namespace dw {
void Simulation::syncWilloOrbits() {
    std::map<MonsterId,std::vector<Enemy*>> groups;
    for(auto &e:enemies)if(e.alive&&content->willo(e.monster))groups[e.monster].push_back(&e);
    for(auto &[id,members]:groups) {
        std::sort(members.begin(),members.end(),[](auto a,auto b){return a->id<b->id;});
        uint64_t signature=1469598103934665603ULL;float first=360;bool changed=false;
        for(auto *e:members) {
            if(!e->willo)e->willo=WilloRuntime{};
            signature=(signature^e->id)*1099511628211ULL;
            first=std::min(first,e->willo->slot);
        }
        for(auto *e:members)changed|=e->willo->members!=signature;
        if(!changed)continue;
        // Native regrouping uses the smallest surviving offset and redistributes
        // the whole cohort. A shooting actor retains its committed attack slot.
        for(size_t n=0;n<members.size();++n) {
            auto &r=*members[n]->willo;r.members=signature;
            if(members.size()>1)r.slot=first+2*Pi*float(n)/float(members.size());
        }
    }
}
void Simulation::updateWillo(Enemy &e,float dt) {
    const auto &p=*content->willo(e.monster);if(!e.willo)e.willo=WilloRuntime{};
    auto &r=*e.willo;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);e.lift=0;
    if(e.state==EnemyState::Stunned) {
        r.attackFrame=-1;r.fired=false;r.warning=false;r.clock=0;e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    // Source uses a common game-frame angle, including its half-frame phase.
    r.angle=-float(stats.duration*30)*p.angularStep;
    const float slot=r.attackFrame>=0?r.attackSlot:r.slot;
    auto target=add(player.position,{std::cos(r.angle+slot)*p.radius*p.scale,0,std::sin(r.angle+slot)*p.radius*p.scale*p.ellipse});
    target.y=e.position.y;
    const auto carry=mul(horizontal(player.velocity),p.carry/30);
    auto correction=mul(horizontal(sub(target,add(e.position,carry))),p.tracking);
    if(length(correction)>p.trackingCap*p.scale)correction=mul(unit(correction),p.trackingCap*p.scale);
    e.velocity=mul(add(carry,correction),30);
    // Source grid collision NONE: an orbit may cross scenery or leave the room.
    // Shooting is gated below while outside. Clamping to a flight path would
    // break the player-centred circle and strand members against canyon edges.
    e.position=add(e.position,mul(e.velocity,dt));e.position.y=.85f;
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(r.attackFrame>=0) {
            if(r.attackFrame<p.shootFrame||r.fired)++r.attackFrame;
            if(r.attackFrame==p.warnFrame)audioCues.push(AudioCueKind::Warning,e.position);
            if(r.attackFrame==p.shootFrame&&!r.fired) {
                const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
                if(queue_.size()>=limits.queuedEvents||projectiles.size()+size_t(queued)>=limits.projectiles)continue;
                const auto aim=sub(add(player.position,mul(player.velocity,p.prediction/30)),e.position);
                auto velocity=mul(unit(horizontal(aim)),p.speed);velocity.y=p.up;
                Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;shot.position=shot.origin={e.position.x,p.height,e.position.z};
                shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.damage;shot.projectileLife=p.life;
                shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.retention;shot.projectileRadius=p.projectileRadius;
                shot.noWallCollision=p.noWallCollision;
                if(!queueRoot(shot))continue;
                audioCues.push(AudioCueKind::MonsterAttack,e.position);r.fired=true;
            }
            if(r.attackFrame>=p.attackFrames){r.attackFrame=-1;r.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
            else {e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames-r.attackFrame)/30;}
            continue;
        }
        if(combatRng.bounded(unsigned(p.chance))!=0)continue;
        if(planarDistance(e.position,target)>p.settleRange*p.scale)continue;
        const auto &area=arena.rooms.at(size_t(room)).bounds;
        if(e.position.x<area.min.x||e.position.x>area.max.x||e.position.z<area.min.z||e.position.z>area.max.z)continue;
        bool busy=false;
        for(const auto &other:enemies)if(other.alive&&other.willo&&content->willo(other.monster)&&other.willo->attackFrame>=0){busy=true;break;}
        if(!busy){r.attackFrame=0;r.fired=false;r.attackSlot=r.slot;e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames)/30;}
    }
    r.warning=r.attackFrame>=p.warnFrame&&r.attackFrame<p.shootFrame;
}
} // namespace dw
