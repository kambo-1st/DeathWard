#include "combat/Simulation.hpp"

namespace dw {
namespace {
constexpr std::array<Vector3,4> GutsAxes{{{0,0,1},{1,0,0},{0,0,-1},{-1,0,0}}};
}
void Simulation::updateGuts(Enemy &e,float dt) {
    const auto &p=*content->guts(e.monster);
    if(!e.guts)e.guts=GutsRuntime{};
    auto &r=*e.guts;
    r.gaze=unit(horizontal(sub(player.position,e.position)));
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};r.windup=-1;r.charging=false;r.hasDestination=false;
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    const float grid=p.grid*p.scale;
    const auto &bounds=arena.rooms[size_t(room)].bounds;
    const auto clear=[&](Vector3 a,Vector3 b) {
        return b.x>=bounds.min.x+e.radius&&b.x<=bounds.max.x-e.radius&&
            b.z>=bounds.min.z+e.radius&&b.z<=bounds.max.z-e.radius&&arena.clear(a,b,e.radius);
    };
    const auto gridCell=[&](Vector3 point) {
        const auto origin=arena.rooms[size_t(room)].center;
        return std::pair<int,int>{int(std::round((point.x-origin.x)/grid)),int(std::round((point.z-origin.z)/grid))};
    };
    const auto emitCreep=[&] {
        if(!r.pendingCreep)return true;
        if(hazards.size()>=limits.hazards)return false;
        Hazard h;h.kind=p.tar?HazardKind::Tar:HazardKind::Creep;h.position=h.origin=*r.pendingCreep;
        h.position.y=.85f;h.delay=0;h.radius=p.creepRadius;h.damage=p.creepDamage;
        h.duration=float(p.creepFrames)/30;h.fadeDuration=float(p.fadeFrames)/30;h.fadeScale=p.fadeScale;
        h.fadeOnRoomClear=true;h.context.sourceEntity=e.id;h.tint=p.tar?Color{36,32,43,210}:Color{144,43,50,200};
        addHazard(h);r.pendingCreep.reset();++r.creepPatches;return true;
    };
    const bool wasPending=r.pendingCreep.has_value();
    if(!emitCreep()){e.velocity={};return;}
    if(wasPending)e.velocity=mul(r.momentum,p.scale*30);
    const auto stopCharge=[&] {
        r.charging=false;r.windup=-1;r.recovery=p.recoveryFrames;r.hitFrame=0;r.multiplier=.1f;
        r.hasDestination=false;r.momentum={};++r.stops;e.state=EnemyState::Ready;
    };
    const auto chooseDestination=[&] {
        const auto forward=GutsAxes[size_t(r.direction)];
        const auto side=GutsAxes[size_t((r.direction+3)%4)];
        // Source corner rule: occupied rear-side cell, empty side cell, and no
        // previous corner turn. Continuous clearance also catches narrow props
        // that would fall between a coarse native grid's sample points.
        if(!r.turned&&!clear(e.position,add(e.position,mul(sub(side,forward),grid)))&&
            clear(e.position,add(e.position,mul(side,grid)))) {
            r.direction=(r.direction+3)%4;r.turned=true;++r.turns;
        }
        for(int attempt=0;attempt<4;++attempt) {
            const auto axis=GutsAxes[size_t(r.direction)];
            const auto target=add(e.position,mul(axis,grid));
            if(clear(e.position,target)) {
                r.destination=target;r.arrival=p.arrival*p.scale;r.hasDestination=true;r.turned=false;return;
            }
            // Canyon walls are not aligned with Isaac's grid. Approach their
            // real footprint, then turn; never snap through terrain to a cell.
            float lo=0,hi=grid;
            for(int n=0;n<12;++n) {
                const float middle=(lo+hi)*.5f;
                if(clear(e.position,add(e.position,mul(axis,middle))))lo=middle;else hi=middle;
            }
            if(lo>.15f) {
                r.destination=add(e.position,mul(axis,std::max(0.f,lo-.025f)));
                r.arrival=.04f;r.hasDestination=true;return;
            }
            r.direction=(r.direction+1)%4;r.turned=true;++r.turns;
        }
    };
    // Source decisions are 30 Hz; integrate between them so fast rolls cannot
    // skip thin obstacles or depend on the application's render frequency.
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;
            ++r.ticks;
            if(!r.initialized) {
                r.initialized=true;r.momentum={};
            } else {
                r.rollFrame=(r.rollFrame+1)%p.rollFrames;
                r.rollPhase=float(r.rollFrame)/float(p.rollFrames);
                if(r.hitFrame>=0&&++r.hitFrame>=p.hitFrames)r.hitFrame=-1;
                if(r.direction<0) {
                    for(int d=0;d<4;++d)if(!clear(e.position,add(e.position,mul(GutsAxes[size_t(d)],grid)))){r.direction=d;break;}
                    if(r.direction<0)r.direction=int(combatRng.bounded(4));
                }
                if(r.windup>=0) {
                    r.multiplier=std::max(p.brake,r.multiplier-p.brake);
                    if(++r.windup>=p.windupFrames){r.windup=-1;r.charging=true;r.multiplier=p.chargeMultiplier;e.state=EnemyState::Charging;}
                } else if(!r.charging) {
                    if(r.recovery>0)--r.recovery;
                    r.multiplier=std::min(1.f,r.multiplier+p.recoveryAcceleration);
                }
                if(!r.charging) {
                    if(r.hasDestination&&dot(horizontal(sub(r.destination,e.position)),GutsAxes[size_t(r.direction)])<=r.arrival)r.hasDestination=false;
                    if(!r.hasDestination)chooseDestination();
                }
                auto force=Vector3{};
                if(r.charging)force=mul(r.chargeDirection,p.force*r.multiplier);
                else if(r.hasDestination)force=mul(unit(horizontal(sub(r.destination,e.position))),p.force*r.multiplier);
                r.momentum=add(mul(r.momentum,p.retention),force);
                if(r.hasDestination&&!r.charging) {
                    const auto delta=mul(horizontal(sub(r.destination,e.position)),1/p.scale);
                    // Source perpendicular correction precedes the common
                    // friction pass, so that new pull is damped as well.
                    if(std::abs(delta.x)>std::abs(delta.z))r.momentum.z=(r.momentum.z+delta.z*p.crossPull)*p.retention;
                    else r.momentum.x=(r.momentum.x+delta.x*p.crossPull)*p.retention;
                }
                if(p.charge&&!r.charging&&r.windup<0&&r.recovery==0) {
                    const auto predicted=add(player.position,mul(player.velocity,p.prediction/30));
                    r.predictedTarget=predicted;
                    const auto a=gridCell(e.position),b=gridCell(predicted);
                    if(a!=b&&(a.first==b.first||a.second==b.second)&&arena.sight(e.position,predicted)&&
                        arena.clear(e.position,predicted,.12f)) {
                        const auto delta=sub(predicted,e.position);
                        r.chargeDirection=a.first==b.first?Vector3{0,0,delta.z<0?-1.f:1.f}:Vector3{delta.x<0?-1.f:1.f,0,0};
                        r.windup=0;r.multiplier=1;++r.charges;e.state=EnemyState::Windup;
                    }
                }
                if(p.shooting) {
                    if(r.shotFrame>=0&&++r.shotFrame>=p.shotFrames)r.shotFrame=-1;
                    if(r.shotTimer>=p.shotInterval) {
                        if(shootCyst(e)){r.shotTimer=0;r.shotFrame=0;}
                    } else ++r.shotTimer;
                }
                if(p.creepInterval) {
                    const int interval=r.charging?p.chargingCreepInterval:p.creepInterval;
                    const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(remaining))*30+1e-4)));
                    if((globalTick+e.id)%uint64_t(interval)==0) {
                        r.pendingCreep=e.position;
                        if(!emitCreep()){e.velocity={};return;}
                    }
                }
            }
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto previous=e.position,velocity=mul(r.momentum,p.scale*30);
        moveMonster(e,velocity,step);
        const auto actual=horizontal(sub(e.position,previous));
        if(length(sub(actual,mul(velocity,step)))>.001f) {
            r.momentum=mul(e.velocity,1/(p.scale*30));
            if(r.charging)stopCharge();else r.hasDestination=false;
        }
        if(length(r.momentum)>.01f)e.facing=unit(r.momentum);
        if(segmentSphere(sub(previous,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
            arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
        }
        e.target=r.charging||r.windup>=0?add(e.position,mul(r.chargeDirection,grid)):r.destination;
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
}
} // namespace dw
