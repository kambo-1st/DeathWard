#include "combat/Simulation.hpp"

namespace dw {
void Simulation::bloatLasers(Enemy &e,const BloatDefinition &p,bool down) {
    for(int side:{-1,1}) {
        // Fixed sockets leave a real central gap in the downward pair. Side
        // beams travel away from each eye; there is deliberately no upward ray.
        const auto start=add(e.position,{float(side)*e.radius*.45f,0,e.radius*.8f});
        const Vector3 direction=down?Vector3{0,0,1}:Vector3{float(side),0,0};
        auto end=add(start,mul(direction,p.beamRange));const auto hit=arena.trace(start,end,p.beamRadius);
        if(hit.hit)end=add(start,mul(sub(end,start),std::max(0.f,hit.t-.001f)));
        Hazard h;h.kind=HazardKind::Beam;h.origin=start;h.position=end;h.radius=p.beamRadius;
        h.delay=0;h.duration=p.beamDuration;h.damage=p.beamDamage;h.context.sourceEntity=e.id;
        h.ownerBound=true;h.tint={170,37,48,255};addHazard(h);
    }
    e.bossAttack=down?3:4;e.beamCooldown=p.beamCooldown;e.cooldown=std::max(e.cooldown,p.beamDuration);
    ++e.bossCycles;audioCues.push(AudioCueKind::MonsterAttack,e.position);
}
void Simulation::bloatLobs(const Enemy &e,const BloatDefinition &p,int count) {
    const auto aim=unit(horizontal(sub(player.position,e.position)));const Vector3 side{-aim.z,0,aim.x};
    for(int n=0;n<count;++n) {
        auto target=add(player.position,mul(side,(float(n)-float(count-1)*.5f)*p.lobSpread));target.y=.22f;
        const auto start=add(e.position,{0,e.radius*.2f,0});
        auto velocity=mul(sub(target,start),1/p.lobFlight);velocity.y+=.5f*p.gravity*p.lobFlight;
        Event shot;shot.position=shot.origin=start;shot.direction=unit(velocity);shot.speed=length(velocity);
        shot.hostile=true;shot.damage=0;shot.projectileKind=ProjectileKind::Ipecac;
        shot.projectileGravity=p.gravity;shot.projectileBlastRadius=p.blastRadius;shot.projectileBlastDamage=p.blastDamage;
        shot.projectileLife=p.lobFlight+1;shot.context.sourceEntity=e.id;queueRoot(shot);
    }
    audioCues.push(AudioCueKind::MonsterAttack,e.position);
}
void Simulation::updateBloat(Enemy &e,float dt) {
    const auto &p=*content->bloat(e.monster);const auto &d=*content->monster(e.monster);
    const bool green=e.bossForm==BossForm::Green;const Color creep=green?Color{96,151,58,220}:Color{147,35,46,220};
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};e.facing={0,0,1};e.auxiliary-=dt;
    e.cooldown-=dt/(EnemyCooldownMultiplier*arena.profile.cooldownScale);e.beamCooldown-=dt;
    requestBossComponents(e);e.phase=0;
    auto landing=[&] {
        if(green)bloatLobs(e,p,e.bossAttack==1?2:3);
        else for(int n=0;n<8;++n)shootEnemy(e,rotateY({1,0,0},float(n)*Pi/4),p.shotDamage,p.shotSpeed);
        if(e.bossAttack==2)bossCreep(e,p.landingRadius,p.creepDuration,creep,p.shotDamage);
        ++e.bossCycles;e.cooldown=d.cooldown;
    };
    const bool stunned=e.state==EnemyState::Stunned;if(stunned)e.stateTime-=dt;
    if(e.hop.active) {
        if(advanceHopArc(e,dt)) {landing();e.state=stunned&&e.stateTime>0?EnemyState::Stunned:EnemyState::Ready;}
        else if(!stunned||e.stateTime<=0)e.state=EnemyState::Jumping;
    } else if(stunned) {
        if(e.stateTime<=0){e.state=EnemyState::Ready;e.cooldown=.4f;}
    } else if(e.state==EnemyState::Windup) {
        e.stateTime-=dt;
        if(e.stateTime<=0) {
            if(e.bossAttack!=0&&revalidateHopArc(e)){e.hop.active=true;e.hop.elapsed=0;e.state=EnemyState::Jumping;}
            else {
                if(e.bossAttack==0) {
                    bossCreep(e,p.creepRadius,p.creepDuration,creep,p.shotDamage);
                    if(green)summonMonsters(e,{p.charger,2,p.summonLimit,1,e.radius+1});
                    ++e.bossCycles;
                }
                e.state=EnemyState::Ready;e.cooldown=d.cooldown;
            }
        }
    } else {
        const auto delta=sub(player.position,e.position);
        const bool down=delta.z>e.radius*.8f&&std::abs(delta.x)<=e.radius*.45f+p.beamAlignment;
        const bool sides=std::abs(delta.z-e.radius*.8f)<=p.beamAlignment&&std::abs(delta.x)>e.radius*.45f;
        if(e.beamCooldown<=0&&(down||sides)&&planarDistance(player.position,e.position)<p.beamRange&&arena.sight(e.position,player.position))
            bloatLasers(e,p,down);
        else if(e.cooldown<=0) {
            int total=0;for(int weight:p.weights)total+=weight;
            int roll=int(combatRng.bounded(uint32_t(total)));e.bossAttack=0;
            for(int n=0;n<3;++n)if((roll-=p.weights[size_t(n)])<0){e.bossAttack=n;break;}
            if(e.bossAttack) {
                const bool shortHop=e.bossAttack==1;const auto direction=unit(horizontal(delta));
                const float reach=shortHop?0:std::min(p.distance,planarDistance(player.position,e.position));
                const float height=shortHop?p.shortHeight:p.height;
                const float duration=(shortHop?p.shortFlight:p.flight)/EnemyMovementMultiplier;
                if(!planHopArc(e,direction,reach,height,shortHop?height:p.maximumHeight,duration)&&
                    !planHopArc(e,direction,0,height,p.maximumHeight,duration)){e.cooldown=.4f;return;}
                e.target=e.hop.end;
            } else e.target=e.position;
            e.state=EnemyState::Windup;e.stateTime=d.windup;audioCues.push(AudioCueKind::Warning,e.position);
        }
    }
    if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(p.contactDamage);
}
} // namespace dw
