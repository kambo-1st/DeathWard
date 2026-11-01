#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 flatAim(Vector3 from,Vector3 to){return unit(horizontal(sub(to,from)));}
}
bool Simulation::flushCreatureShots(Enemy &e) {
    if(!e.creature)return true;
    auto &pending=e.creature->pending;
    while(!pending.empty()) {
        const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const Event &v){return v.type==EventType::Shot;});
        if(queue_.size()>=limits.queuedEvents||(pending.front().type==EventType::Shot&&projectiles.size()+size_t(queued)>=limits.projectiles))return false;
        if(!queueRoot(pending.front()))return false;
        pending.pop_front();
    }
    e.creature->deathPending=false;return true;
}
void Simulation::igniteGas(Vector3 position,float radius) {
    for(auto &h:hazards)if(h.alive&&h.explosiveGas&&h.kind==HazardKind::Gas&&
        distance(h.position,position)<radius+h.radius&&arena.sight(position,h.position))h.gasIgnited=true;
}
bool Simulation::collapseClack(Enemy &e) {
    const auto *cycle=content->creatureCycle(e.monster);
    if(!cycle||!cycle->clack||e.state==EnemyState::Collapsed)return false;
    if(!e.creature)e.creature.emplace();
    e.state=EnemyState::Collapsed;e.stateTime=cycle->clack->regrow;e.hp=e.maxHp;
    e.velocity={};e.lift=0;return true;
}
bool Simulation::reflectBouncer(Enemy &e,Projectile &p) {
    if(!e.creature||!e.creature->inflated||p.hostile||p.kind==ProjectileKind::Ipecac||p.blastRadius>0)return false;
    const auto normal=flatAim(e.position,p.position);
    if(dot(p.velocity,normal)>=0)return false;
    // Native pair-seeded lottery. Entity IDs supply stable local init seeds;
    // this reproduces the branch and rate, not original game's RNG stream.
    uint32_t rng=uint32_t(p.id+e.id);rng^=rng>>5;rng^=rng<<9;rng^=rng>>7;
    if(rng%5)return false;
    p.velocity=sub(p.velocity,mul(normal,2*dot(p.velocity,normal)));
    p.position=add(p.position,mul(normal,.02f));return true;
}
void Simulation::creatureDeath(Enemy &e) {
    const auto *cycle=content->creatureCycle(e.monster);if(!cycle)return;
    if(!e.creature)e.creature.emplace();
    auto &r=*e.creature;
    auto shot=[&](Vector3 at,Vector3 velocity,float gravity=0,float retention=0,float radius=.22f) -> Event& {
        Event v;v.type=EventType::Shot;v.position=v.origin=at;v.direction=unit(velocity);v.speed=length(velocity);
        v.hostile=true;v.damage=10;v.projectileGravity=gravity;v.projectileFlightRetention=retention;
        v.projectileRadius=radius;v.projectileLife=12;v.context.sourceEntity=e.id;setEnemyShotAffiliation(e,v);
        r.pending.push_back(v);return r.pending.back();
    };
    if(cycle->bouncer) {
        if(!r.inflated)for(int n=0;n<4;++n)shot(e.position,mul(rotateY({1,0,0},Pi/4+float(n)*Pi/2),30));
        else {
            for(int n=0;n<12;++n) {
                auto velocity=mul(rotateY({1,0,0},combatRng.real(0,2*Pi)),21);
                velocity.y=-(5-combatRng.real(0,24))*1.5f;
                shot(e.position,velocity,28.8f,.9f,.22f*(.9f+.4f*float(combatRng.bounded(2))+combatRng.real(0,.05f)));
            }
            for(int n=0;n<22;++n) {
                auto at=add(e.position,rotateY({.5f,0,0},combatRng.real(0,2*Pi)));at.y=2.2f+combatRng.real(0,.8f);
                auto &v=shot(at,mul(rotateY({1,0,0},combatRng.real(0,2*Pi)),combatRng.real(0,45)),
                    90*(.04f-combatRng.real(0,.03f)),.9f,.22f*(.6f+combatRng.real(0,1.2f)));
                v.projectilePlanarMotion=SourcePlanarMotionDefinition{};
                v.projectilePlanarMotion->acceleration=.9f;v.projectilePlanarMotion->accelerationRampFrames=20;
            }
            // Native shockwave pushes; it is not an unconditional damaging bomb.
            if(!e.friendly&&planarDistance(e.position,player.position)<12)
                player.position=arena.move(player.position,mul(flatAim(e.position,player.position),2),.48f);
            effectVisual(e.position,12,0,.4f);
        }
    } else if(cycle->gasDwarf) {
        const auto &p=*cycle->gasDwarf;
        if(e.selfDetonated) {
            Event v;v.type=EventType::Explosion;v.position=v.origin=e.position;
            v.radius=p.blastRadius;v.damage=p.blastDamage;v.playerDamage=e.friendly?0:p.playerDamage;
            v.context.sourceEntity=e.id;r.pending.push_back(v);
        } else {
            auto velocity=mul(flatAim(e.position,player.position),p.shotSpeed);velocity.y=5;
            auto &v=shot(e.position,velocity,12,0,.28f);v.projectileKind=ProjectileKind::Ipecac;
            v.projectileBlastRadius=p.blastRadius;v.projectileBlastDamage=p.blastDamage;
            v.projectileBlastPlayerDamage=e.friendly?0:p.playerDamage;
        }
    }
    r.deathPending=!r.pending.empty();flushCreatureShots(e);
}
void Simulation::updateCreatureCycle(Enemy &e,float dt) {
    const auto &cycle=*content->creatureCycle(e.monster);const auto &d=*content->monster(e.monster);
    if(!e.creature)e.creature.emplace();
    auto &r=*e.creature;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    flushCreatureShots(e);
    if(e.state==EnemyState::Stunned){e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;}
    if(!r.initialized) {
        r.initialized=true;r.timer=cycle.bouncer?combatRng.real(cycle.bouncer->timerMin,cycle.bouncer->timerMin+cycle.bouncer->timerRange):cycle.quakey?cycle.quakey->interval:0;
        e.facing=flatAim(e.position,player.position);return;
    }
    r.clock+=dt*enemyTimeScale(e);
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);const float step=1.f/30;
        const auto target=confusedTarget(e);auto toward=flatAim(e.position,target);
        auto walk=[&](Vector3 heading,float speed) {
            e.facing=length(heading)>.001f?heading:e.facing;
            if(e.railCarrier)return;
            if(e.affectedBy(EnemyStatus::Fear)||e.affectedBy(EnemyStatus::Shrink)) {
                stepFearMotion(e,r.momentum);moveMonster(e,mul(r.momentum,3),step);return;
            }
            const float tuned=speed*e.championSpeed*(e.friendly?1.f:EnemyMovementMultiplier);
            if(dot(heading,toward)>.9f&&!arena.clear(e.position,target,e.radius)) {
                e.pathTime-=step;
                if(e.pathTime<=0){e.path=arena.path(e.position,target,e.radius);e.pathTime=.3f;}
                while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.6f)e.path.erase(e.path.begin());
                if(!e.path.empty())heading=flatAim(e.position,e.path.front());
            }
            moveMonster(e,steerMonsterBodies(e,mul(heading,tuned)),step);
        };
        auto contact=[&](float damage) {
            if(!e.friendly&&segmentSphere(sub(e.position,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
                hurtPlayer(e.champion<0?damage:std::max(damage,10*e.championDamage),{0,0,e.id,-1});
        };
        if(cycle.bouncer) {
            const auto &p=*cycle.bouncer;r.near|=planarDistance(e.position,player.position)<p.proximity;
            if(r.phase==0) {
                r.timer=std::max(0.f,r.timer-step);walk(mul(toward,-1),p.fleeSpeed);
                if(e.age>1&&r.near&&r.timer<=0&&combatRng.bounded(20)==0){r.phase=1;r.frame=0;e.state=EnemyState::Windup;}
            } else if(r.phase==1) {
                ++r.frame;e.velocity=mul(e.velocity,.6f);
                if(r.frame==p.inflateEvent){r.inflated=true;r.phaseTime=e.radius*1.5f;}
                if(r.frame>=p.inflateFrames){r.phase=2;e.state=EnemyState::Ready;}
            } else walk(toward,p.chaseSpeed);
                if(r.inflated&&r.phaseTime>0&&(r.phase==1||++r.frame%15==0)) {
                    const float desired=r.phaseTime;Vector3 at=e.position;bool legal=!arena.blocked(at,desired);
                    // A native size increase can overlap a 3D canyon wall.
                    // Sweep a short correction using the old legal footprint;
                    // never teleport through cover or leave an enlarged body wedged.
                    for(int ring=1;!legal&&ring<=8;++ring)for(int n=0;!legal&&n<16;++n) {
                        auto candidate=add(e.position,rotateY({float(ring)*.15f,0,0},float(n)*Pi/8));
                        if(!arena.blocked(candidate,desired)&&arena.clear(e.position,candidate,e.radius)){at=candidate;legal=true;}
                    }
                    if(legal){if(e.statuses&&e.statuses->unshrunkRadius>0)e.statuses->unshrunkRadius*=desired/e.radius;e.position=at;e.radius=desired;r.phaseTime=0;}
                }
            contact(p.contact);
            if(r.inflated&&!e.friendly&&distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
                Event kill;kill.type=EventType::Damage;kill.target=e.id;kill.damage=1e6f;queueRoot(kill);return;
            }
        } else if(cycle.quakey) {
            const auto &p=*cycle.quakey;
            if(r.phase==0) {
                walk(toward,d.speed);r.timer-=step;contact(10);
                if(r.timer<=0&&planarDistance(e.position,player.position)<=p.range) {
                    r.phase=1;r.phaseTime=0;r.origin=e.position;
                    const auto delta=horizontal(sub(target,e.position));const float range=length(delta);
                    r.target=arena.move(e.position,mul(unit(delta),std::min(range,p.range)),e.radius);
                    e.state=EnemyState::Windup;e.velocity={};
                }
            } else if(r.phase==1) {
                r.phaseTime+=step;
                if(r.phaseTime>=p.windup){r.phase=2;r.phaseTime=0;e.state=EnemyState::Jumping;}
            } else if(r.phase==2) {
                r.phaseTime+=step;const float t=std::min(1.f,r.phaseTime/p.flight);
                if(!e.railCarrier)e.position=add(r.origin,mul(sub(r.target,r.origin),t));
                e.lift=std::sin(Pi*t)*p.height;
                if(t>=1) {
                    e.lift=0;e.state=EnemyState::Ready;r.phase=0;r.timer=p.interval;
                    auto projectile=[&](Vector3 at,Vector3 velocity,float gravity) {
                        Event v;v.type=EventType::Shot;v.hostile=true;v.position=v.origin=at;v.direction=unit(velocity);v.speed=length(velocity);
                        v.damage=p.damage;v.projectileKind=ProjectileKind::Rock;v.projectileGravity=gravity;v.projectileLife=4;
                        v.context.sourceEntity=e.id;setEnemyShotAffiliation(e,v);r.pending.push_back(v);
                    };
                    for(int n=0;n<8;++n)projectile(e.position,mul(rotateY({1,0,0},float(n)*Pi/4),p.shotSpeed),0);
                    for(int n=0;n<p.rocks;++n) {
                        auto at=add(player.position,rotateY({1.5f*float(n),0,0},combatRng.real(0,2*Pi)));
                        at.x=std::clamp(at.x,arena.rooms[size_t(room)].bounds.min.x+1,arena.rooms[size_t(room)].bounds.max.x-1);
                        at.z=std::clamp(at.z,arena.rooms[size_t(room)].bounds.min.z+1,arena.rooms[size_t(room)].bounds.max.z-1);
                        effectVisual({at.x,.1f,at.z},.65f,0,.7f);at.y=6;projectile(at,{0,-.1f,0},12);
                    }
                    if(!e.friendly&&planarDistance(e.position,player.position)<3)
                        player.position=arena.move(player.position,mul(flatAim(e.position,player.position),2.5f),.48f);
                    audioCues.push(AudioCueKind::StoneHit,e.position);flushCreatureShots(e);
                }
            }
        } else if(cycle.gasDwarf) {
            const auto &p=*cycle.gasDwarf;walk(toward,d.speed);r.timer-=step;
            if(r.timer<=0) {
                Hazard gas;gas.kind=HazardKind::Gas;gas.position=gas.origin=e.position;gas.delay=0;gas.duration=p.duration;
                gas.radius=p.radius;gas.damage=0;gas.harmsPlayer=false;gas.context.sourceEntity=e.id;gas.tint={126,144,73,110};
                gas.explosiveGas=true;gas.gasBlastRadius=p.blastRadius;gas.gasBlastDamage=p.blastDamage;gas.gasPlayerDamage=e.friendly?0:p.playerDamage;
                addHazard(gas);r.timer=p.interval;
            }
            if(!e.friendly&&distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
                Event kill;kill.type=EventType::Damage;kill.target=e.id;kill.damage=1e6f;
                if(queueRoot(kill))e.selfDetonated=true;
                return;
            }
        } else if(cycle.clack) {
            const auto &p=*cycle.clack;
            if(e.state==EnemyState::Collapsed) {
                const bool active=std::any_of(enemies.begin(),enemies.end(),[&](const Enemy &other){return other.id!=e.id&&other.alive&&other.monster==e.monster&&other.state!=EnemyState::Collapsed&&other.friendly==e.friendly;});
                if(!active) {
                    Event finish;finish.type=EventType::Damage;finish.target=e.id;finish.damage=1e6f;finish.execution=true;queueRoot(finish);return;
                }
                e.stateTime-=step;if(e.stateTime<=0){e.state=EnemyState::Ready;e.hp=e.maxHp;r.timer=p.chase;r.phase=0;}
            } else {
                r.timer-=step;if(r.timer<=0){r.phase=1-r.phase;r.timer=r.phase?p.wander:p.chase;e.facing=rotateY({1,0,0},combatRng.real(0,2*Pi));}
                walk(r.phase?e.facing:toward,d.speed);contact(p.contact);
            }
        }
    }
}
} // namespace dw
