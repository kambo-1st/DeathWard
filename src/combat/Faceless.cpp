#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::flushFacelessShots(Enemy &e) {
    if(!e.faceless||e.faceless->pendingShots.empty())return true;
    const auto &shots=e.faceless->pendingShots;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &x){return x.alive;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+shots.size()>limits.queuedEvents||size_t(live+queued)+shots.size()>limits.projectiles)return false;
    for(const auto &shot:shots)queueRoot(shot);
    e.faceless->pendingShots.clear();return true;
}

void Simulation::shootFaceless(Enemy &e) {
    auto &r=*e.faceless;const auto &p=*content->faceless(e.monster);
    // FireProjectiles mode9 increments before emission: 60,120,...,360 degrees.
    // Its angle parameter is explicitly zero, independent of the target/facing.
    for(int n=1;n<=p.shots;++n) {
        const float angle=float(n)*2*Pi/float(p.shots);
        const Vector3 velocity{std::cos(angle)*p.shotSpeed,p.shotUp,std::sin(angle)*p.shotSpeed};
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin=add(e.position,{0,p.shotHeight-.85f,0});
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.shotDamage;
        shot.projectileRadius=p.shotRadius;shot.projectileLife=p.shotLife;
        shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.shotRetention;
        r.pendingShots.push_back(shot);
    }
    r.recentDamage=std::max(0.f,r.recentDamage-p.shotCost);
    ++r.attacks;r.fired=true;audioCues.push(AudioCueKind::MonsterAttack,e.position);
    flushFacelessShots(e);
}

void Simulation::updateFaceless(Enemy &e,float dt) {
    const auto &p=*content->faceless(e.monster);
    if(!e.faceless)e.faceless=FacelessRuntime{};
    auto &r=*e.faceless;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const bool pending=!r.pendingShots.empty();
    if(!flushFacelessShots(e)){e.velocity={};return;}
    if(pending)e.velocity=mul(r.momentum,p.scale*30);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;
            if(!r.initialized)r.initialized=true;
            else {
                if(r.frame>=0) {
                    ++r.frame;
                    if(r.frame==p.shootFrame&&!r.fired)shootFaceless(e);
                    if(r.frame>=p.attackFrames){r.frame=-1;r.fired=false;}
                }
                if(!r.aggressive) {
                    const float range=p.alertRange*p.scale;
                    bool alert=e.hp<e.maxHp||planarDistance(e.position,player.position)<range;
                    if(!alert)for(const auto &other:enemies)
                        if(other.alive&&other.monster.type==827&&other.faceless&&other.faceless->aggressive&&
                           planarDistance(e.position,other.position)<range){alert=true;break;}
                    if(alert){r.aggressive=true;r.targetReady=false;e.path.clear();}
                }
                if(combatRng.bounded(unsigned(p.trailChance))==0)
                    effectVisual({e.position.x,.025f,e.position.z},combatRng.real(p.trailMin,p.trailMax),7,p.trailLife);
                if(!e.railCarrier) {
                    if(r.aggressive) {
                        if(e.path.empty()||planarDistance(r.destination,player.position)>.5f) {
                            r.destination=player.position;e.path=arena.path(e.position,r.destination,e.radius);
                        }
                        while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.3f)e.path.erase(e.path.begin());
                        const auto delta=horizontal(sub(e.path.empty()?e.position:e.path.front(),e.position));
                        const float sourceDistance=length(delta)/p.scale;
                        r.momentum=mul(r.momentum,p.pathRetention);
                        if(sourceDistance>1)r.momentum=add(r.momentum,mul(unit(delta),std::min(sourceDistance*.1f,2.f)*p.pathForce));
                    } else {
                        if(!r.targetReady) {
                            const auto at=add(e.position,mul(rotateY({1,0,0},combatRng.real(0,2*Pi)),p.wanderDistance*p.scale));
                            if(!arena.blocked(at,e.radius)){r.destination=at;r.targetReady=true;}
                        }
                        if(r.targetReady) {
                            const auto delta=horizontal(sub(r.destination,e.position));
                            if(length(delta)<p.arrival*p.scale||r.blocked||
                               (dot(r.momentum,r.momentum)<p.stuckSpeedSquared&&combatRng.bounded(unsigned(p.stuckChance))==0))r.targetReady=false;
                            else r.momentum=add(r.momentum,mul(unit(delta),p.wanderForce));
                        }
                        r.momentum=mul(r.momentum,p.wanderRetention);
                    }
                }
                r.blocked=false;
                if(r.frame<0&&e.spawnerType!=906) {
                    const float chance=p.tainted&&r.aggressive?1:p.baseChance+p.damageChance*std::sqrt(r.recentDamage);
                    if(combatRng.real(0,1)<=chance) {
                        r.frame=0;r.fired=false;audioCues.push(AudioCueKind::Warning,e.position);
                    }
                }
            }
            r.recentDamage=std::max(0.f,r.recentDamage+r.incomingDamage-p.hurtDecay);r.incomingDamage=0;
            e.state=r.frame>=0&&r.frame<p.shootFrame?EnemyState::Windup:EnemyState::Ready;
            e.stateTime=e.state==EnemyState::Windup?float(p.shootFrame-r.frame)/30:0;
            if(!r.pendingShots.empty()){e.velocity={};return;}
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position,velocity=steerMonsterBodies(e,mul(r.momentum,p.scale*30));
        if(!e.railCarrier)moveMonster(e,velocity,step);
        if(length(velocity)>.001f&&planarDistance(before,e.position)<length(velocity)*step*.5f)r.blocked=true;
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(p.contact,{0,0,e.id,-1});
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=player.position;
}

bool Simulation::tryFacelessMorph(Enemy &e,const Event &event) {
    const auto *p=content->faceless(e.monster);
    if(!p||p->tainted||event.execution||e.hp>0||e.hp<=-p->overkill*p->damageScale||
       combatRng.bounded(unsigned(p->morphChance))!=0)return false;
    const float hpScale=e.maxHp/content->monsterHealth(e.monster,arena.profile.sourceStage);
    const float radiusScale=e.radius/content->monster(e.monster)->radius;
    e.monster=combatRng.bounded(unsigned(p->pacerChance))==0?p->pacer:p->gusher;
    const auto &next=*content->monster(e.monster);
    e.hp=e.maxHp=content->monsterHealth(e.monster,arena.profile.sourceStage)*hpScale;
    e.radius=next.radius*radiusScale;
    e.state=EnemyState::Ready;e.stateTime=0;e.phase=0;e.behavior={};e.hop={};
    e.headless=content->headless(e.monster)?std::optional<HeadlessRuntime>{HeadlessRuntime{}}:std::nullopt;
    e.auxiliary=e.trailTime=e.lift=0;e.path.clear();e.pathTime=0;e.cooldown=next.cooldown;
    // A selected volley can outlive its controller. Keep only its pending
    // payload until admission; the new headless body updates independently.
    if(e.faceless&&e.faceless->pendingShots.empty())e.faceless.reset();
    checkpointNeeded=true;
    return true; // Same entity and ownership: no kill, loot, slot or clear window.
}
} // namespace dw
