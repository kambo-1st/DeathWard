#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::lumpDestinationClear(const Enemy &e,Vector3 point,bool occupancy) const {
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    if(point.x-e.radius<bounds.min.x||point.x+e.radius>bounds.max.x||
        point.z-e.radius<bounds.min.z||point.z+e.radius>bounds.max.z||arena.blocked(point,e.radius))return false;
    if(!occupancy)return true;
    const float cell=content->lump(e.monster)->grid*content->lump(e.monster)->scale;
    auto sameCell=[&](Vector3 other) {
        return int(std::floor((point.x-bounds.min.x)/cell))==int(std::floor((other.x-bounds.min.x)/cell))&&
            int(std::floor((point.z-bounds.min.z)/cell))==int(std::floor((other.z-bounds.min.z)/cell));
    };
    if(planarDistance(point,player.position)<e.radius+.5f)return false;
    for(const auto &other:enemies)if(other.alive&&other.id!=e.id&&
        (sameCell(other.position)||planarDistance(point,other.position)<e.radius+other.radius||
            (other.lump&&sameCell(other.lump->anchor))))return false;
    return true;
}

void Simulation::chooseLumpDestination(Enemy &e) {
    const auto &p=*content->lump(e.monster);auto &r=*e.lump;
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    const float margin=std::max(e.radius,p.margin*p.scale),cell=p.grid*p.scale;
    if(bounds.max.x-bounds.min.x<=2*margin||bounds.max.z-bounds.min.z<=2*margin)return;
    // One candidate per hidden source frame, before the independent emergence
    // roll. Failure keeps the old anchor, including in rooms too small for200.
    Vector3 point{combatRng.real(bounds.min.x+margin,bounds.max.x-margin),.85f,
        combatRng.real(bounds.min.z+margin,bounds.max.z-margin)};
    const auto delta=mul(horizontal(sub(point,player.position)),1/p.scale);
    const float range=length(delta);
    if(range<p.targetMin||((std::abs(delta.x)<p.alignment||std::abs(delta.z)<p.alignment)&&range<p.axisRange))return;
    point.x=bounds.min.x+(std::floor((point.x-bounds.min.x)/cell)+.5f)*cell;
    point.z=bounds.min.z+(std::floor((point.z-bounds.min.z)/cell)+.5f)*cell;
    if(lumpDestinationClear(e,point,true)) {
        if(planarDistance(point,r.anchor)>.001f)++r.relocations;
        r.anchor=point;
    }
}

bool Simulation::shootLump(Enemy &e) {
    const auto &p=*content->lump(e.monster);auto &r=*e.lump;
    if(r.pendingShots.empty()) {
        r.pendingShots.resize(3);auto aim=unit(horizontal(sub(player.position,e.position)));
        if(length(aim)<.001f)aim=e.facing;
        const Vector3 side{-aim.z,0,aim.x};
        for(int n=0;n<3;++n) {
            auto velocity=mul(aim,p.shot.speed);
            if(n)velocity=mul(add(mul(velocity,.961f),mul(side,p.shot.speed*.276f*(n==1?1.f:-1.f))),.9f);
            velocity=add(mul(velocity,1.2f),mul(horizontal(e.velocity),.4f));velocity.y=p.shotUp;
            auto &shot=r.pendingShots[size_t(n)];shot.hostile=true;shot.context.sourceEntity=e.id;
            shot.position=add(e.position,{0,p.shotHeight-.85f,0});shot.origin=e.position;
            shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shot.damage;
            shot.projectileLife=p.shot.life;shot.projectileRadius=p.shotRadius;
            shot.projectileGravity=p.shotGravity;shot.projectileFlightRetention=p.shotRetention;
        }
    }
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+3>limits.queuedEvents||
        projectiles.size()+size_t(queued)+3>limits.projectiles)return false;
    for(const auto &shot:r.pendingShots)queueRoot(shot);
    r.pendingShots.clear();++r.volleys;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

void Simulation::updateLump(Enemy &e,float dt) {
    const auto &p=*content->lump(e.monster);if(!e.lump){e.lump=LumpRuntime{};e.lump->anchor=e.position;}auto &r=*e.lump;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=r.intangible?EnemyState::Buried:EnemyState::Ready;
        return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        if(!r.initialized){r.initialized=true;r.anchor=e.position;e.velocity={};continue;}
        auto begin=[&](LumpPhase phase){r.phase=phase;r.frame=0;};
        if(r.phase==LumpPhase::Ready&&r.cooldown<=0&&combatRng.bounded(unsigned(p.hideChance))==0)begin(LumpPhase::Hiding);
        if(r.cooldown>0)--r.cooldown;
        const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+.00001)));
        bool acquired=false;
        // The native acquisition is independent of phase: it can interrupt
        // Hide/Appear or hidden relocation after63 frames, with no extra delay.
        if(r.pendingShots.empty()&&r.cooldown<=0&&(globalTick+e.id)%unsigned(p.shot.checkFrames)==0&&
            planarDistance(e.position,player.position)<p.shot.range&&arena.sight(e.position,player.position)&&
            lumpDestinationClear(e,e.position,false)) {
            begin(LumpPhase::Spitting);r.fired=false;r.intangible=false;r.cooldown=p.shot.cooldownFrames;acquired=true;
        }
        if(r.phase==LumpPhase::Hiding) {
            if(++r.frame==1)audioCues.push(AudioCueKind::Warning,e.position);
            if(r.frame>=p.hideFrames){begin(LumpPhase::Hidden);r.intangible=true;++r.burrows;}
        }
        if(r.phase==LumpPhase::Hidden) {
            r.intangible=true;chooseLumpDestination(e);
            if(combatRng.bounded(unsigned(p.appearChance))==0&&lumpDestinationClear(e,e.position,false)) {
                begin(LumpPhase::Appearing); // This update still has collision class0.
            }
        } else if(r.phase==LumpPhase::Spitting) {
            r.intangible=false;
            if(!acquired) {
                if(r.frame<p.shot.shootFrame||r.fired)++r.frame;
                if(r.frame==p.shot.shootFrame&&!r.fired)r.fired=shootLump(e);
                if(r.frame>=p.shot.attackFrames)begin(LumpPhase::Hiding);
            }
        } else if(r.phase==LumpPhase::Appearing) {
            r.intangible=false;
            if(++r.frame==6)audioCues.push(AudioCueKind::Warning,e.position);
            if(r.frame>=p.appearFrames)begin(LumpPhase::Ready);
        } else if(r.phase==LumpPhase::Ready)r.intangible=false;
        // Native velocity is replaced by anchor-position each update, then
        // damped. Fixed source steps prevent a60Hz half-step overshoot/change.
        const auto displacement=mul(horizontal(sub(r.anchor,e.position)),p.retention);
        if(r.phase==LumpPhase::Hidden) {
            e.position=add(e.position,displacement);e.velocity=mul(displacement,30);
        } else moveMonster(e,mul(displacement,30),1.f/30);
    }
    r.visibility=r.phase==LumpPhase::Hidden?0:r.phase==LumpPhase::Hiding?
        std::max(.08f,1-float(r.frame)/float(p.hideFrames)):r.phase==LumpPhase::Appearing?
        std::max(.08f,float(r.frame)/float(p.appearFrames)):1;
    e.state=r.intangible?EnemyState::Buried:r.phase==LumpPhase::Ready?EnemyState::Ready:EnemyState::Windup;
    e.cooldown=float(r.cooldown)/30;e.facing=unit(horizontal(sub(player.position,e.position)));e.target=player.position;
    if(!r.intangible&&planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
