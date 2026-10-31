#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateSmallMaggot(Enemy &e,float dt) {
    const auto &p=*content->smallMaggot(e.monster);
    if(!e.smallMaggot)e.smallMaggot=SmallMaggotRuntime{};
    auto &r=*e.smallMaggot;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    const auto randomDirection=[&]{return rotateY({1,0,0},combatRng.real(0,2*Pi));};
    const auto interval=[&](int minimum,int maximum){return minimum+int(combatRng.bounded(unsigned(maximum-minimum+1)));};
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized) {
                r.initialized=true;r.heading=randomDirection();r.cooldown=interval(p.initialMin,p.initialMax);
                // The source initializes state3, not a fixed emergence animation.
                // Force is initially zero; the first timer expiry chooses it.
            } else {
                if(r.blocked)r.cooldown=0;
                --r.cooldown;r.blocked=false;
                if(!r.alert) {
                    if(e.hp<e.maxHp)r.alert=true;
                    else {
                        const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(remaining))*30+1e-4)));
                        if(globalTick%unsigned(p.alertInterval)==0&&combatRng.bounded(unsigned(p.alertChance))==0) {
                            // Awareness has no sight gate. The later pursuit
                            // decision checks terrain separately. Native player
                            // camouflage/charm branches remain outside this profile.
                            r.alert=planarDistance(e.position,player.position)<p.alertRange*p.scale;
                            if(!r.alert)for(const auto &other:enemies)
                                if(other.id!=e.id&&other.alive&&other.smallMaggot&&other.smallMaggot->alert&&
                                   planarDistance(e.position,other.position)<p.alertRange*p.scale){r.alert=true;break;}
                        }
                    }
                    if(r.alert)++r.alerts;
                } else if(combatRng.bounded(unsigned(p.forgetChance))==0)r.alert=false;
                if(r.cooldown<=0) {
                    const bool pursue=r.alert&&arena.sight(e.position,player.position);
                    if(pursue)r.heading=unit(horizontal(sub(player.position,e.position)));
                    if(length(r.heading)<.0001f)r.heading=randomDirection();
                    // Native lookahead checks the grid six pixels ahead. This
                    // world's irregular terrain requires the actual body footprint.
                    for(int attempt=0;attempt<p.obstacleAttempts;++attempt) {
                        if(arena.clear(e.position,add(e.position,mul(r.heading,p.lookahead*p.scale)),e.radius))break;
                        r.heading=rotateY(r.heading,combatRng.real(-p.obstacleTurnDegrees,p.obstacleTurnDegrees)*Pi/180);
                    }
                    r.curve=combatRng.real(-p.curveDegrees,p.curveDegrees)*Pi/180;
                    r.force=combatRng.real(p.forceMin,p.forceMax)*(pursue?p.targetMultiplier:1);
                    r.cooldown=interval(p.turnMin,p.turnMax);++r.turns;
                }
                r.momentum=mul(add(r.momentum,mul(r.heading,r.force)),p.retention);
                r.heading=rotateY(r.heading,r.curve);
            }
            const int axis=std::clamp(int(std::floor((std::atan2(r.momentum.z,std::abs(r.momentum.x))*180/Pi+22.5f)/45))+2,0,4);
            if(axis!=r.walkAxis){r.walkAxis=axis;r.walkFrame=0;}
            else r.walkFrame=(r.walkFrame+1)%p.walkFrames;
            e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position,velocity=mul(r.momentum,p.scale*30);
        if(!e.railCarrier) {
            if(!arena.clear(before,add(before,mul(velocity,step)),e.radius))r.blocked=true;
            moveMonster(e,velocity,step);
        }
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(!e.friendly&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(p.contact,{0,0,e.id,-1});
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=add(e.position,mul(r.heading,p.lookahead*p.scale));
}
} // namespace dw
