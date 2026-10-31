#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootSpitty(Enemy &e,bool burst,bool death) {
    const auto &p=*content->spitty(e.monster);auto &r=*e.spitty;
    if(burst&&!r.pendingBurst)r.pendingBurst=p.burstMin+int(combatRng.bounded(unsigned(p.burstMax-p.burstMin+1)));
    const int count=death?p.ringCount*2:burst?r.pendingBurst:p.kind==SpittyKind::Conjoined?2:p.streamCount;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+size_t(count)>limits.queuedEvents||
        projectiles.size()+size_t(queued+count)>limits.projectiles)return false;
    const auto &flight=death?p.death:burst?p.burst:p.shot;
    for(int n=0;n<count;++n) {
        Vector3 direction=r.attackDirection;
        float size=1,gravity=flight.gravity;
        std::optional<SourcePlanarMotionDefinition> motion;
        if(death) {
            const int ring=n/p.ringCount;
            const float angle=float(n%p.ringCount+1)*2*Pi/float(p.ringCount)+(ring?p.deathOffset:0);
            direction={std::cos(angle),0,std::sin(angle)};
            size=p.deathSize;motion=SourcePlanarMotionDefinition{1,0,ring?-1:1,e.position};
        } else if(burst) {
            direction=rotateY({1,0,0},combatRng.real(0,2*Pi));
            size=p.burstSize+p.burstSizeToggle*float(combatRng.bounded(2))+combatRng.real(0,p.burstSizeJitter);
        } else if(p.kind==SpittyKind::Conjoined)direction=mul(direction,n?-1.f:1.f);
        else if(p.kind==SpittyKind::Tainted) {
            direction=rotateY(direction,combatRng.real(-.5f,.5f)*float(n)*p.streamJitter);
            size=p.streamSize-p.streamSizeStep*float(n);gravity+=p.streamGravityStep*float(n);
            motion=SourcePlanarMotionDefinition{1-p.streamAccelerationStep*float(n),0,0,{}};
        }
        auto velocity=mul(direction,flight.speed);velocity.y=combatRng.real(flight.upMin,flight.upMax);
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=add(e.position,{0,flight.height-.85f,0});shot.origin=e.position;
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=flight.damage;
        shot.projectileLife=flight.life;shot.projectileRadius=flight.radius*size;
        shot.projectileGravity=gravity;shot.projectileFlightRetention=flight.retention;
        shot.projectilePlanarMotion=motion;queueRoot(shot);
    }
    if(death)r.deathPending=false;
    else if(burst){r.pendingBurst=0;++r.bursts;}
    else ++r.volleys;
    audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

void Simulation::updateSpitty(Enemy &e,float dt) {
    const auto &p=*content->spitty(e.monster);
    if(!e.spitty)e.spitty=SpittyRuntime{};
    auto &r=*e.spitty;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.attackFrame=-1;r.fired=false;r.pendingBurst=0;r.walkFrame=0;r.walkAxis=-1;
        r.momentum={};e.velocity={};e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        const bool attacking=r.attackFrame>=0;
        if(attacking) {
            if(r.attackFrame<p.shootFrame||r.fired)++r.attackFrame;
            if(r.attackFrame==p.shootFrame&&!r.fired)r.fired=shootSpitty(e);
            if(r.attackFrame>=p.attackFrames) {
                r.attackFrame=-1;r.fired=false;r.walkFrame=0;r.walkAxis=-1;e.state=EnemyState::Ready;
            }
        } else {
            // Facing is derived from the previous velocity, not from the player.
            const int axis=faceAxisWander(e,r);
            stepAxisWander(e,p,r);
            if(!r.pendingBurst)r.walkFrame=(r.walkFrame+1)%(axis==0?p.horizontalFrames:p.verticalFrames);
            if(p.walkShootFrame&&(r.pendingBurst||r.walkFrame==p.walkShootFrame))shootSpitty(e,true);
            if(!r.pendingBurst&&combatRng.bounded(unsigned(p.chance))==0) {
                r.attackFrame=0;r.fired=false;r.attackDirection=e.facing;
                e.state=EnemyState::Windup;audioCues.push(AudioCueKind::Warning,e.position);
            }
            r.momentum.z*=p.zRetention;
        }
        r.momentum=mul(r.momentum,p.retention);
    }
    e.stateTime=r.attackFrame>=0?float(p.attackFrames-r.attackFrame)/30:0;
    moveAxisWander(e,p,r,dt);
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
