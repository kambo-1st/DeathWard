#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootBaby(Enemy &e) {
    const auto &p=*content->baby(e.monster);auto &r=*e.baby;
    const bool spread=p.kind==BabyKind::Angelic||p.kind==BabyKind::Wrinkly;
    const int count=spread?3:1;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+size_t(count)>limits.queuedEvents||
        projectiles.size()+size_t(queued+count)>limits.projectiles)return false;
    auto aim=unit(horizontal(sub(player.position,e.position)));
    if(length(aim)<.001f)aim=e.facing;
    const Vector3 side{-aim.z,0,aim.x};
    for(int n=0;n<count;++n) {
        auto velocity=mul(aim,p.shot.speed);
        if(n)velocity=mul(add(mul(velocity,.961f),mul(side,p.shot.speed*.276f*p.spread*(n==1?1.f:-1.f))),.9f);
        // Native mode2 changes both speed and falling motion; do not normalize
        // the side vectors or discard the body's velocity at the Shoot event.
        if(spread)velocity=add(mul(velocity,1.2f),mul(r.momentum,p.scale*30*.4f));
        velocity=mul(velocity,p.velocityMultiplier);velocity.y=p.shotUp;
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=add(add(e.position,mul(aim,p.originOffset)),{0,p.shotHeight-.85f,0});
        shot.origin=e.position;shot.direction=unit(velocity);shot.speed=length(velocity);
        shot.damage=p.shot.damage;shot.projectileLife=p.shot.life;shot.projectileRadius=p.shotRadius;
        shot.projectileGravity=p.shotGravity;shot.projectileFlightRetention=p.shotRetention;
        queueRoot(shot);
    }
    ++r.volleys;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

bool Simulation::babyDestinationClear(const Enemy &e,Vector3 point) const {
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    if(point.x-e.radius<bounds.min.x||point.x+e.radius>bounds.max.x||
        point.z-e.radius<bounds.min.z||point.z+e.radius>bounds.max.z||arena.blocked(point,e.radius))return false;
    if(planarDistance(point,player.position)<e.radius+.5f)return false;
    const auto &p=*content->baby(e.monster);const float cell=p.grid*p.scale;
    const auto gridX=[&](float x){return int(std::floor((x-bounds.min.x)/cell));};
    const auto gridZ=[&](float z){return int(std::floor((z-bounds.min.z)/cell));};
    // This vector contains the active room; inactive actors live in residents.
    for(const auto &other:enemies)if(other.alive&&other.id!=e.id) {
        if(planarDistance(point,other.position)<e.radius+other.radius||
            (gridX(point.x)==gridX(other.position.x)&&gridZ(point.z)==gridZ(other.position.z)))return false;
        if(other.baby&&other.baby->destination&&planarDistance(point,*other.baby->destination)<cell*.5f)return false;
    }
    return true;
}

void Simulation::chooseBabyDestination(Enemy &e) {
    const auto &p=*content->baby(e.monster);auto &r=*e.baby;
    const auto &bounds=arena.rooms[size_t(room)].bounds;const float cell=p.grid*p.scale;
    for(int attempt=0;attempt<p.attempts&&!r.destination;++attempt) {
        const float radius=p.radiusMin+combatRng.real(0,p.radiusExtra);
        auto point=add(e.position,rotateY({radius*p.scale,0,0},combatRng.real(0,2*Pi)));
        auto delta=horizontal(sub(point,player.position));const float range=length(delta)/p.scale;
        if(range<=p.targetMin||(p.targetMax>0&&range>=p.targetMax))continue;
        if(p.kind==BabyKind::Normal&&(std::abs(delta.x)<=p.alignment*p.scale||std::abs(delta.z)<=p.alignment*p.scale))continue;
        // Native 40-unit cell centers become room-relative cells in the canyon.
        point.x=bounds.min.x+(std::floor((point.x-bounds.min.x)/cell)+.5f)*cell;
        point.z=bounds.min.z+(std::floor((point.z-bounds.min.z)/cell)+.5f)*cell;
        point.y=.85f;
        if(babyDestinationClear(e,point))r.destination=point;
    }
}

void Simulation::updateBaby(Enemy &e,float dt) {
    const auto &p=*content->baby(e.monster);if(!e.baby)e.baby=BabyRuntime{};auto &r=*e.baby;
    const bool wrinkly=p.kind==BabyKind::Wrinkly;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.phase=BabyPhase::Ready;r.frame=0;r.attackFrame=-1;r.fired=false;r.intangible=false;r.visibility=1;
        r.clock=0;r.momentum={};e.velocity={};e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized) {
            r.initialized=true;r.ticks=uint64_t(std::max(0.,std::floor(stats.duration*30+.00001)));
            if(wrinkly)r.cooldown=p.initialMin+int(combatRng.bounded(unsigned(p.initialMax-p.initialMin+1)));
            continue;
        }
        ++r.ticks;
        const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+.00001)));
        const auto delta=horizontal(sub(player.position,e.position));const float range=length(delta)/p.scale;
        float retention=p.retention;
        auto beginAttack=[&](int frame) {
            r.phase=BabyPhase::Ready;r.attackFrame=frame;r.fired=false;r.frame=0;
            audioCues.push(AudioCueKind::Warning,e.position);
        };
        auto advanceAttack=[&] {
            if(r.attackFrame<p.shot.shootFrame||r.fired)++r.attackFrame;
            if(r.attackFrame==p.shot.shootFrame&&!r.fired)r.fired=shootBaby(e);
            if(r.attackFrame>=p.shot.attackFrames) {
                r.attackFrame=-1;r.fired=false;
                if(wrinkly) {
                    r.dashDirection={};r.dashTarget={};
                    r.cooldown=p.recoveryMin+int(combatRng.bounded(unsigned(p.recoveryMax-p.recoveryMin+1)));
                }
            }
        };
        if(r.phase==BabyPhase::Vanishing||r.phase==BabyPhase::Appearing) {
            r.intangible=true;++r.frame;
            if(r.phase==BabyPhase::Vanishing&&r.frame>=p.vanishFrames) {
                if(r.destination&&!babyDestinationClear(e,*r.destination))r.destination.reset();
                if(!r.destination)chooseBabyDestination(e);
                // Dynamic scenery may occupy a stored cell. Retain the teleport
                // until a legal destination exists, rather than embed the actor.
                if(r.destination) {
                    e.position=*r.destination;e.position.y=arena.flightHeight(e.position,e.radius);
                    r.destination.reset();r.teleportCharge=0;r.phase=BabyPhase::Appearing;r.frame=0;++r.teleports;
                }
            } else if(r.phase==BabyPhase::Appearing&&r.frame>=p.appearFrames) {
                r.phase=BabyPhase::Ready;r.frame=0; // Collision returns on the following ready update.
            }
            if(r.cooldown<=0)r.momentum=add(r.momentum,mul(unit(delta),p.force/p.retention));
        } else if(wrinkly&&r.phase==BabyPhase::DashStart) {
            if(++r.frame>=p.dashFrames) {
                r.phase=BabyPhase::Dashing;r.frame=0;r.dashTarget=player.position;r.dashDirection=unit(delta);r.blocked=false;++r.dashes;
            }
        } else if(wrinkly&&r.phase==BabyPhase::Dashing) {
            retention=p.dashRetention;
            r.momentum=add(r.momentum,mul(r.dashDirection,p.dashForce));
            r.momentum=mul(r.dashDirection,dot(r.momentum,r.dashDirection));
            const auto offset=mul(horizontal(sub(e.position,r.dashTarget)),1/p.scale);
            r.momentum=sub(r.momentum,sub(offset,mul(r.dashDirection,dot(offset,r.dashDirection))));
            if(r.blocked||dot(horizontal(sub(r.dashTarget,e.position)),r.dashDirection)<p.dashStop*p.scale)beginAttack(0);
        } else if(wrinkly) {
            r.intangible=false;
            if(r.attackFrame>=0)advanceAttack();
            else {
                const auto target=range<p.keepDistance?add(player.position,mul(unit(mul(delta,-1)),p.keepDistance*p.scale)):player.position;
                r.momentum=add(r.momentum,mul(unit(horizontal(sub(target,e.position))),p.force/p.retention));
                // Hostile Wrinkly uses native target-team eligibility (6aeb40),
                // not the normal Baby's range/line-of-sight helper (6a15a0).
                if(r.cooldown<=0&&combatRng.bounded(unsigned(p.chance))==0) {
                    if(range<p.keepDistance)beginAttack(p.closeAttackFrame);
                    else if(range<p.dashRange){r.phase=BabyPhase::DashStart;r.frame=0;audioCues.push(AudioCueKind::Warning,e.position);}
                }
            }
        } else {
            r.intangible=false;
            if(r.attackFrame<0&&r.cooldown<=0&&(globalTick+e.id)%unsigned(p.shot.checkFrames)==0&&
                range*p.scale<p.shot.range&&arena.sight(e.position,player.position)) {
                beginAttack(0);r.cooldown=p.shot.cooldownFrames;
            } else if(r.attackFrame>=0)advanceAttack();
            if(r.cooldown>0)--r.cooldown;
            if(r.recentDamageFrames>0)r.teleportCharge=p.searchCharge;
            if(std::min(std::abs(delta.x),std::abs(delta.z))<p.alignment*p.scale&&range<p.alignmentRange)r.teleportCharge+=1;
            r.teleportCharge+=combatRng.real(0,p.randomCharge);
            if(r.teleportCharge>p.searchCharge&&!r.destination)chooseBabyDestination(e);
            if(r.teleportCharge>p.startCharge&&r.destination) {
                r.phase=BabyPhase::Vanishing;r.frame=0;r.attackFrame=-1;r.fired=false;
                audioCues.push(AudioCueKind::Warning,e.position);
            }
            if(r.cooldown<=0)r.momentum=add(r.momentum,mul(unit(delta),p.force/p.retention));
        }
        if(wrinkly&&r.cooldown>0)--r.cooldown;
        if(r.recentDamageFrames>0)--r.recentDamageFrames;
        r.momentum=mul(r.momentum,retention);
        r.walkPhase=std::fmod(r.walkPhase+1.f/float(p.walkFrames),1.f);
    }
    if(r.phase==BabyPhase::Vanishing) {
        // Vanish disables grid collision. Keep this transient drift in its room.
        const auto before=e.position;const auto &b=arena.rooms[size_t(room)].bounds;
        e.position=add(e.position,mul(r.momentum,p.scale*30*dt));
        e.position.x=std::clamp(e.position.x,b.min.x+e.radius,b.max.x-e.radius);
        e.position.z=std::clamp(e.position.z,b.min.z+e.radius,b.max.z-e.radius);
        e.velocity=mul(sub(e.position,before),1/dt);
    } else {
        const auto wanted=mul(r.momentum,p.scale*30);moveMonster(e,wanted,dt);
        // Canyon wall stop is the physical 3D adaptation of the common collision
        // response; the native controller itself only tests the committed target.
        if(r.phase==BabyPhase::Dashing&&length(wanted)>1&&dot(horizontal(e.velocity),r.dashDirection)<dot(wanted,r.dashDirection)*.25f)r.blocked=true;
    }
    r.visibility=r.phase==BabyPhase::Vanishing?std::clamp(1-float(r.frame)/float(p.jumpFrame),0.f,1.f):
        r.phase==BabyPhase::Appearing?std::clamp(float(r.frame)/float(p.landFrame),0.f,1.f):1;
    e.state=r.intangible?EnemyState::Teleporting:r.phase==BabyPhase::Dashing?EnemyState::Charging:
        r.phase!=BabyPhase::Ready||r.attackFrame>=0?EnemyState::Windup:EnemyState::Ready;
    e.cooldown=float(r.cooldown)/30;e.stateTime=float(r.attackFrame>=0?p.shot.attackFrames-r.attackFrame:0)/30;
    e.facing=r.phase==BabyPhase::Dashing?r.dashDirection:unit(horizontal(sub(player.position,e.position)));
    e.target=player.position;
    if(!r.intangible&&planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
        if(r.phase==BabyPhase::Dashing)r.blocked=true;
    }
}
} // namespace dw
