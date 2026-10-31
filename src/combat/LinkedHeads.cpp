#include "combat/Simulation.hpp"

namespace dw {
void Simulation::releaseLinkedPart(Enemy &e,MonsterId replacement) {
    const auto &d=*content->monster(replacement);
    e.monster=replacement;e.partner=0;e.linkedHead.reset();e.lift=0;
    e.hp=e.maxHp=content->monsterHealth(replacement,arena.profile.sourceStage);
    e.radius=d.radius;e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;
    e.path.clear();e.pathTime=0;e.behavior={};e.maw.reset();
    if(content->maw(replacement))e.maw=MawRuntime{};
    if(d.flying)e.position.y=arena.flightHeight(e.position,e.radius);
}

bool Simulation::shootLinkedHeadDeath(Enemy &e) {
    if(!e.linkedHead||!e.linkedHead->deathPending)return true;
    const auto &p=*content->linkedHead(e.monster);
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||queue_.size()+size_t(p.deathShots)>limits.queuedEvents||
        projectiles.size()+size_t(queued+p.deathShots)>limits.projectiles)return false;
    for(int n=0;n<p.deathShots;++n) {
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin=e.position;shot.direction=rotateY({1,0,0},float(n)*2*Pi/float(p.deathShots));
        shot.speed=p.deathSpeed;shot.damage=p.deathDamage;shot.projectileLife=5;
        queueRoot(shot);
    }
    e.linkedHead->deathPending=false;return true;
}

void Simulation::linkedHeadDeath(Enemy &e) {
    const auto &p=*content->linkedHead(e.monster);
    if(auto *other=findEnemy(e.partner);other&&other->alive) {
        if(e.monster==p.body&&other->monster==p.head)releaseLinkedPart(*other,p.headRelease);
        else if(e.monster==p.head&&other->monster==p.body)releaseLinkedPart(*other,p.bodyRelease);
    }
    if(!e.linkedHead)e.linkedHead=LinkedHeadRuntime{};
    e.linkedHead->neckCount=0;
    if(e.monster==p.head&&p.deathShots) {
        e.linkedHead->deathPending=true;shootLinkedHeadDeath(e);
    }
}

void Simulation::updateLinkedHead(Enemy &e,float dt) {
    const auto &p=*content->linkedHead(e.monster);
    if(!e.linkedHead)e.linkedHead=LinkedHeadRuntime{};
    auto &r=*e.linkedHead;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    e.pathTime-=dt;
    auto *partner=findEnemy(e.partner);
    const bool head=e.monster==p.head;
    if(head&&(!partner||!partner->alive||partner->monster!=p.body)) {
        releaseLinkedPart(e,p.headRelease);return;
    }
    if(!head&&e.partner&&(!partner||!partner->alive||partner->monster!=p.head)) {
        releaseLinkedPart(e,p.bodyRelease);return;
    }
    // A reserved head waits for capacity. The body cannot begin an incomplete
    // attack or disappear while the required offspring has not been admitted.
    if(!partner){e.velocity={};return;}
    if(!partner->linkedHead)partner->linkedHead=LinkedHeadRuntime{};
    auto &body=head?*partner:e;
    auto &bodyState=*body.linkedHead;
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=bodyState.extended?EnemyState::Returning:EnemyState::Ready;
        return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
        if(!r.initialized){r.initialized=true;continue;}
        if(!head) {
            if(bodyState.extended)r.momentum=mul(r.momentum,p.throwRetention);
            else {
                auto destination=player.position;
                if(!arena.clear(e.position,destination,e.radius)) {
                    if(e.pathTime<=0){e.path=arena.path(e.position,destination,e.radius);e.pathTime=.4f;}
                    while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.15f)e.path.erase(e.path.begin());
                    destination=e.path.empty()?e.position:e.path.front();
                }
                auto delta=horizontal(sub(destination,e.position));const float distance=length(delta)/p.scale;
                // Native FindGridPath: .7 friction, force scaled by min(d/10,2).
                // The 3D navigation supplies safe waypoints instead of native grid cells.
                r.momentum=mul(r.momentum,distance<=1?.5f:p.walkRetention);
                if(distance>1)r.momentum=add(r.momentum,mul(unit(delta),p.force*std::min(distance*.1f,2.f)));
            }
            r.walkPhase=float(r.ticks%uint64_t(p.walkFrames))/float(p.walkFrames);
        } else {
            // Source uses a separate random check on every head update. It does
            // not roll once per attack and has no health threshold.
            if(combatRng.bounded(unsigned(p.splitChance))==0) {
                releaseLinkedPart(body,p.bodyRelease);releaseLinkedPart(e,p.headRelease);return;
            }
            bodyState.timer=std::max(p.timerMinimum,bodyState.timer-1);
            if(!bodyState.extended) {
                const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+1e-4)));
                if(body.state!=EnemyState::Stunned&&(globalTick+e.id)%uint64_t(p.checkFrames)==0) {
                    const auto target=add(player.position,mul(player.velocity,p.prediction/30));
                    const auto delta=horizontal(sub(target,e.position));r.predictedTarget=target;
                    if(length(delta)>1e-5f&&length(delta)<p.range*p.scale&&arena.sight(e.position,player.position)) {
                        r.momentum=mul(unit(delta),p.launchSpeed);bodyState.timer=p.timerStart;
                        bodyState.extended=r.extended=true;++r.throws;++bodyState.throws;
                        e.facing=unit(delta);e.state=EnemyState::Charging;body.state=EnemyState::Returning;
                        audioCues.push(AudioCueKind::MonsterAttack,e.position);
                    }
                }
            } else {
                const auto delta=horizontal(sub(body.position,e.position));const float distance=length(delta);
                if(distance<p.returnDistance*p.scale&&bodyState.timer<p.attachTimer) {
                    bodyState.extended=r.extended=false;++r.returns;++bodyState.returns;
                    body.state=e.state=EnemyState::Ready;r.momentum={};
                } else if(distance>1e-5f) {
                    const float spring=p.springBase-p.springSubtract*std::clamp(
                        float(bodyState.timer-p.timerMinimum)/p.springDivisor,0.f,1.f);
                    const float retention=p.headRetention+float(bodyState.timer)*p.timerRetention;
                    // Here native code adds the spring before modifying the
                    // actor friction, unlike the body's pathfinder force.
                    r.momentum=mul(add(r.momentum,mul(unit(delta),spring)),retention);
                    e.state=EnemyState::Returning;
                }
            }
        }
    }
    if(head&&!bodyState.extended) {
        e.position=body.position;e.velocity=body.velocity;e.facing=body.facing;e.state=EnemyState::Ready;
    } else {
        auto velocity=mul(r.momentum,p.scale*30);
        if(!head)velocity=steerMonsterBodies(e,velocity);
        const auto before=e.position;moveMonster(e,velocity,dt);
        if(!head&&planarDistance(before,e.position)>.001f)e.facing=unit(horizontal(sub(e.position,before)));
    }
    if(head) {
        e.lift=p.headLift;r.neckRadius=p.neckRadius;
        r.neckCount=bodyState.extended?p.neckCount:0;
        const auto start=add(body.position,{0,p.headLift*.25f,0}),end=add(e.position,{0,p.headLift,0});
        const float slack=std::max(0.f,1-planarDistance(start,end)/(100*p.scale));
        for(int n=0;n<r.neckCount;++n) {
            const float t=float(n+1)/float(r.neckCount+1);
            r.neckPoints[size_t(n)]=add(start,mul(sub(end,start),t));
            r.neckPoints[size_t(n)].y-=std::sin(t*Pi)*p.neckSag*slack;
        }
    }
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
