#include "combat/Simulation.hpp"
#include "world/CanyonTerrain.hpp"

namespace dw {
bool Simulation::flushHardyShots(Enemy &e) {
    if(!e.hardy||e.hardy->pendingShots.empty())return true;
    const auto &shots=e.hardy->pendingShots;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &x){return x.type==EventType::Shot;});
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &x){return x.alive;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+shots.size()>limits.queuedEvents||size_t(live+queued)+shots.size()>limits.projectiles)return false;
    for(const auto &shot:shots)queueRoot(shot);
    e.hardy->pendingShots.clear();return true;
}
void Simulation::hardyDeath(Enemy &e) {
    const auto &p=*content->hardy(e.monster);
    queueMonster(p.child,e.position,0,0,false,p.childHealth,0,0,0,-1,{},true);
}
void Simulation::hardyImpact(Enemy &e,Vector3 normal) {
    auto &r=*e.hardy;const auto &p=*content->hardy(e.monster);
    ++r.impacts;r.phase=3;r.frame=0;
    auto shot=[&](Vector3 planar,float up,float size,float gravity,bool burst) {
        Event event;event.hostile=true;event.context.sourceEntity=e.id;
        event.position=event.origin=add(e.position,{0,p.shotHeight-.85f,0});
        const auto velocity=add(planar,{0,up,0});event.direction=unit(velocity);event.speed=length(velocity);
        event.damage=p.shotDamage;event.projectileKind=ProjectileKind::Rock;
        event.projectileRadius=p.shotRadius*size;event.projectileLife=p.shotLife;
        event.projectileGravity=gravity;event.projectileFlightRetention=p.shotRetention;
        if(burst)event.projectileBurst=ProjectileBurstDefinition{};
        r.pendingShots.push_back(event);
    };
    if(r.impacts<3) {
        // Native mode8: cardinals followed by .70710677 diagonals.
        for(const auto dir:std::array<Vector3,8>{{{1,0,0},{-1,0,0},{0,0,1},{0,0,-1},{.70710677f,0,.70710677f},{-.70710677f,0,.70710677f},{.70710677f,0,-.70710677f},{-.70710677f,0,-.70710677f}}})
            shot(mul(dir,p.ringSpeed*p.shotScale*30),combatRng.real(-.15f,.15f),1,4.5f,false);
    }
    if(r.impacts>=2) {
        // FireBossProjectiles receives a COUNT, not a ring mode. Target sampled
        // at impact; each projectile adds independently scattered planar speed.
        const auto aimed=unit(horizontal(sub(player.position,e.position)));
        for(int n=0;n<(r.impacts==2?6:8);++n) {
            const auto jitter=mul(rotateY({1,0,0},combatRng.real(0,2*Pi)),combatRng.real(0,p.clusterScatter));
            const auto velocity=mul(add(mul(aimed,p.clusterSpeed),jitter),p.shotScale*30);
            const float size=(.9f+.4f*float(combatRng.bounded(2))+combatRng.real(0,.05f))*(r.impacts==3?1.2f:1);
            shot(velocity,-combatRng.real(p.clusterFallMin,p.clusterFallMax)*1.5f,size,p.clusterGravity,r.impacts==3);
        }
    }
    if(r.impacts==3) {
        r.lethalImpact=true;
        const int count=2+int(combatRng.bounded(2));
        for(int n=0;n<count;++n) {
            const auto direction=rotateY(normal,combatRng.real(-p.childSpread*.5f,p.childSpread*.5f)*Pi/180);
            const auto position=add(e.position,mul(direction,p.childOffset*p.scale));
            const auto before=pendingMonsters_.size();
            queueMonster(p.rock,position,0,0,false,1,0,e.id,0,-1,{},true,{},mul(direction,combatRng.real(p.childSpeedMin,p.childSpeedMax)*p.scale*30));
            if(pendingMonsters_.size()==before)continue;
            auto &child=pendingMonsters_.back();child.rockSpider=RockSpiderRuntime{};
            child.rockSpider->initialized=true;child.rockSpider->height=p.childHeight;
            child.rockSpider->vertical=combatRng.real(p.childUpMin,p.childUpMax);
        }
    }
    particleEffect(ParticleEffect::Stone,e.position,normal,.85f);
    audioCues.push(AudioCueKind::MonsterAttack,e.position);
    flushHardyShots(e);
}
void Simulation::updateHardy(Enemy &e,float dt) {
    const auto &p=*content->hardy(e.monster);if(!e.hardy)e.hardy=HardyRuntime{};auto &r=*e.hardy;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(!flushHardyShots(e)){e.velocity={};return;}
    if(r.lethalImpact) {
        Event hit;hit.type=EventType::Damage;hit.target=e.id;hit.damage=e.hp+1;hit.execution=true;hit.context.sourceEntity=e.id;
        queueRoot(hit);e.velocity={};return;
    }
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    float remaining=dt;
    while(remaining>1e-7f) {
        if(r.clock==0) {
            ++r.ticks;float retention=p.retention;
            if(!r.initialized)r.initialized=true;
            else if(r.phase==0) {
                r.cooldown=std::max(0,r.cooldown-1);
                if(combatRng.bounded(unsigned(p.chance))==0&&(r.ticks+e.id)%uint64_t(p.checkFrames)==0&&r.cooldown==0){r.phase=1;r.frame=0;r.collisions=0;}
                retention*=p.idleRetention;
            } else if(r.phase==1) {
                if(++r.frame==p.launchFrame) {
                    const auto dir=unit(horizontal(sub(player.position,e.position)));
                    r.momentum=add(r.momentum,mul(dir,p.launch/retention));e.facing=dir;
                    r.phase=2;r.slideFrames=0;++r.launches;audioCues.push(AudioCueKind::MonsterAttack,e.position);
                }
            } else if(r.phase==2) {
                if(r.blocked)++r.collisions;r.blocked=false;
                ++r.slideFrames;
                if(r.collisions>0&&r.slideFrames>=p.slowAfter) {
                    const float speed=length(r.momentum);
                    if(speed<p.stopSpeed){r.phase=0;r.frame=0;}
                    else if(speed<p.slowSpeed)retention*=p.brake;
                } else r.momentum=add(r.momentum,mul(unit(r.momentum),p.force/retention));
                if(r.collisions>4)retention*=p.collisionBrake;
            } else {
                retention*=p.collisionBrake;
                if(++r.frame>=p.hitFrames){r.phase=0;r.frame=0;r.cooldown=p.cooldown;}
            }
            r.momentum=mul(r.momentum,retention);
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto from=e.position,velocity=mul(r.momentum,p.scale*30),to=add(from,mul(velocity,step));
        auto contact=arena.trace(from,to,e.radius);
        if(arena.canyon) {
            // Ground locomotion clips the footprint at WalkableHeight, below
            // the body's projectile hull. Trace that same footprint so sloped
            // canyon walls register an impact before the movement query stops us.
            auto a=from,b=to;a.y=b.y=CanyonTerrain::WalkableHeight;
            for(int n=-1;n<8;++n) {
                const auto offset=n<0?Vector3{}:Vector3{e.radius*std::cos(float(n)*Pi/4),0,e.radius*std::sin(float(n)*Pi/4)};
                auto hit=arena.canyon->trace(add(a,offset),add(b,offset));
                if(hit.hit&&length(horizontal(hit.normal))>.001f&&(!contact.hit||hit.t<contact.t)) {
                    hit.normal=unit(horizontal(hit.normal));contact=hit;
                }
            }
        }
        if(contact.hit&&length(horizontal(contact.normal))>.5f) {
            e.position=add(from,mul(sub(to,from),std::max(0.f,contact.t-.0001f)));
            if(r.phase==2) {
                r.blocked=true;
                if(dot(unit(velocity),mul(contact.normal,-1))>p.impactDot) {
                    // Destroy only the contacted breakable. Structural wall
                    // meshes remain intact; cache gates reveal their passage.
                    for(auto &b:arena.breakables) {
                        if(!b.solid()||b.room!=room||b.kind==BreakableKind::CacheSide)continue;
                        const auto hit=segmentBox(from,to,b.bounds,e.radius);
                        if(!hit.hit||std::abs(hit.t-contact.t)>.0001f)continue;
                        if(b.kind==BreakableKind::PowderBarrel)hitBreakable(b,10000,true);
                        else {b.destroyed=true;arena.rebuildWalls();for(auto &other:enemies)other.pathTime=0;payBreakables();}
                        break;
                    }
                    hardyImpact(e,contact.normal);
                }
            }
            // Native collision feeds a reflected/sliding velocity back to AI.
            // Keep tangent momentum, allowing glancing contacts to scrape.
            r.momentum=sub(r.momentum,mul(contact.normal,std::min(0.f,dot(r.momentum,contact.normal))));
            if(r.phase==3)r.momentum={};
        } else if(!arena.blocked(to,e.radius)&&arena.clear(from,to,e.radius))e.position=to;
        else {r.momentum={};if(r.phase==2){r.blocked=true;if(r.slideFrames>=p.slowAfter)r.phase=0;}}
        e.velocity=mul(r.momentum,p.scale*30);
        if(length(e.velocity)>.001f)e.facing=unit(e.velocity);
        if(segmentSphere(sub(from,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))hurtPlayer(p.contact,{0,0,e.id,-1});
        remaining-=step;r.clock+=step;if(r.clock>=1.f/30-1e-6f)r.clock=0;
        if(!r.pendingShots.empty()||r.lethalImpact)break;
    }
    e.state=r.phase==1?EnemyState::Windup:EnemyState::Ready;
    e.stateTime=r.phase==1?float(p.launchFrame-r.frame)/30:0;
}
} // namespace dw
