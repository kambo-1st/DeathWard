#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateRottenGaper(Enemy &e,float dt) {
    const auto &p=*content->rottenGaper(e.monster);
    if(!e.rottenGaper)e.rottenGaper=RottenGaperRuntime{};
    auto &r=*e.rottenGaper;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.frameReady=false;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    const auto normalize=[](Vector3 v){const auto n=length(v);return n>0?mul(v,1/n):v;};
    auto pathForce=[&](Vector3 destination,float force) {
        if(e.path.empty()||e.pathTime<=0||planarDistance(r.destination,destination)>.5f||
           !arena.clear(e.position,e.path.front(),e.radius)) {
            r.destination=destination;e.path=arena.path(e.position,destination,e.radius);e.pathTime=1.1f;
        }
        while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.3f&&
              arena.clear(e.position,e.path[1],e.radius))e.path.erase(e.path.begin());
        const auto delta=horizontal(sub(e.path.empty()?e.position:e.path.front(),e.position));
        const float distance=length(delta)/p.scale;
        if(distance==0)r.momentum=mul(r.momentum,p.blockedRetention);
        else if(distance<=p.arrival)r.momentum=mul(r.momentum,p.arrivalRetention);
        else r.momentum=add(mul(r.momentum,p.retention),mul(normalize(delta),force*std::min(distance*p.distanceGain,p.maxGain)));
    };
    auto evade=[&](Vector3 threat,uint64_t globalTick) {
        // Shared native EvadeTarget: staggered proximity checks, three sticky
        // checks, then wander. Native tile candidate/cache operations are adapted
        // to this world's irregular walkable footprint, as for Hive/Long Legs.
        if((globalTick+e.id)%14==0) {
            if(planarDistance(e.position,threat)<(arena.sight(e.position,threat)?250:170)*p.scale) {
                if(!r.evadeChecks)r.targetReady=false;
                r.evadeChecks=3;
            } else r.evadeChecks=std::max(0,r.evadeChecks-1);
        }
        const bool fleeing=r.evadeChecks>0;
        if(r.targetReady&&(planarDistance(e.position,r.destination)<3*p.scale||e.path.empty()||
            !arena.clear(e.position,e.path.front(),e.radius)))r.targetReady=false;
        if(!r.targetReady) {
            e.path.clear();
            auto away=normalize(horizontal(sub(e.position,threat)));
            if(fleeing) {
                if(std::abs(std::abs(away.x)-std::abs(away.z))<.25f) {
                    if(combatRng.bounded(2))away.x*=.5f;else away.z*=.5f;
                }
                r.momentum=add(r.momentum,mul(away,1.5f));
            }
            for(int attempt=0;attempt<7;++attempt) {
                const float angle=combatRng.real(0,2*Pi),reach=fleeing?combatRng.real(30,480):40;
                auto offset=Vector3{std::cos(angle)*reach*p.scale,0,std::sin(angle)*reach*p.scale*(fleeing?.5f:1)};
                if(fleeing)offset=add(offset,mul(away,30*p.scale));
                const auto at=add(e.position,offset);
                if(arena.roomAt(at)!=room||arena.blocked(at,e.radius)||!arena.clear(e.position,at,e.radius))continue;
                if(fleeing&&planarDistance(at,threat)<=planarDistance(e.position,threat)+(100+reach/3-attempt*10)*p.scale)continue;
                auto path=arena.path(e.position,at,e.radius);if(path.empty())continue;
                r.destination=at;e.path=std::move(path);e.pathTime=1.1f;r.targetReady=true;break;
            }
        }
        if(r.targetReady) {
            if(fleeing)pathForce(r.destination,p.evadeForce);
            else {
                const auto delta=horizontal(sub(r.destination,e.position));
                r.momentum=add(mul(r.momentum,.9f),mul(normalize(delta),.5f));
                // EvadeTarget's non-flee branch adds another .9 multiplier.
                r.momentum=mul(r.momentum,.9f);
            }
        }
        r.momentum=mul(r.momentum,p.evadeRetention);
    };
    float remaining=dt;
    while(remaining>1e-7f) {
        if(!r.frameReady) {
            r.frameReady=true;++r.ticks;
            if(!r.initialized) {
                // Source State0 initializes Head/Walk then enters State4.
                // It does not also execute pursuit or summoning on this update.
                r.initialized=true;r.force=p.force;
            } else {
                r.walkFrame=length(r.momentum)>=p.stopSpeed?(r.walkFrame+1)%p.walkFrames:0;
                r.walkPhase=float(r.walkFrame)/p.walkFrames;r.force=p.force;
                e.pathTime-=1.f/30;
                if(p.brood) {
                    if(r.remember>0)--r.remember;
                    const auto *previous=findEnemy(r.avoid);
                    if(r.remember<=0||!previous||!previous->alive)r.avoid=0;
                    if(!r.avoid&&planarDistance(e.position,player.position)>p.playerRange*p.scale) {
                        for(const auto &peer:enemies)if(peer.alive&&peer.id!=e.id&&peer.friendly==e.friendly&&
                            peer.monster.type==e.monster.type&&peer.monster.variant==e.monster.variant&&peer.monster.subtype!=e.monster.subtype&&
                            planarDistance(peer.position,e.position)<p.peerRange*p.scale) {
                            r.avoid=peer.id;r.remember=p.rememberMin+int(combatRng.bounded(unsigned(p.rememberMax-p.rememberMin+1)));break;
                        }
                    }
                    ++r.spawnCounter;
                    if(r.spawnCounter>p.spawnDelay) {
                        ++r.spawnRolls;
                        if(combatRng.bounded(unsigned(p.spawnChance))==0) {
                            // Reset happens even when all six owned slots are full.
                            r.spawnCounter=0;
                            const auto live=std::count_if(enemies.begin(),enemies.end(),[&](const auto &child){return child.alive&&child.summoner==e.id;});
                            const auto pending=std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &child){return child.summoner==e.id;});
                            if(live+pending<p.childLimit&&e.generation<4) {
                                queueMonster(p.child,e.position,0,e.generation+1,false,1,0,e.id,0,-1,{},true);++r.births;
                            }
                        }
                    }
                }
                const auto *avoid=findEnemy(r.avoid);
                const bool evading=avoid&&avoid->alive;
                if(r.evading!=evading){r.evading=evading;r.targetReady=false;e.path.clear();}
                r.orbitDirect=false;
                if(!e.railCarrier) {
                    if(evading) {
                        const auto globalTick=uint64_t(std::max(0.,std::floor((stats.duration-double(remaining))*30+1e-4)));
                        evade(avoid->position,globalTick);
                    } else if(p.orbit) {
                        const float distance=planarDistance(e.position,player.position);
                        r.force*=p.orbitMinimum+p.orbitGain*std::clamp((distance/p.scale-p.orbitNear)/p.orbitSpan,0.f,1.f);
                        r.orbitDirect=arena.clear(e.position,player.position,e.radius);
                        if(r.orbitDirect) {
                            const auto projected=add(e.position,mul(normalize(rotateY(r.momentum,combatRng.real(-p.orbitTurn,p.orbitTurn)*Pi/180)),distance));
                            r.destination=add(player.position,mul(normalize(horizontal(sub(projected,player.position))),p.orbitRadius*p.scale));
                            r.momentum=mul(add(r.momentum,mul(normalize(horizontal(sub(r.destination,e.position))),r.force)),p.orbitRetention);
                            e.path.clear();
                        } else pathForce(player.position,r.force);
                    } else pathForce(player.position,r.force);
                }
            }
            e.state=EnemyState::Ready;e.stateTime=0;e.cooldown=0;
        }
        const float step=std::min(remaining,1.f/30-r.clock);
        const auto before=e.position;
        if(!e.railCarrier) {
            const auto velocity=mul(r.momentum,p.scale*30);
            // At a tight route corner, lateral crowd steering can repeatedly
            // pull a body away from the alignment needed to enter the opening.
            // Follow the last short approach exactly; physical body resolution
            // still separates actors, and normal crowd steering resumes beyond it.
            const bool aligning=e.path.size()>1&&planarDistance(e.position,e.path.front())<e.radius+.2f&&
                !arena.clear(e.position,e.path[1],e.radius);
            auto steered=steerMonsterBodies(e,velocity,aligning);
            // Keep the newly acquired straight route through the opening too.
            // Otherwise a neighbor beside the jamb can immediately steer this
            // body back into the wall after its corner waypoint is consumed.
            const float lookahead=std::max(e.radius,length(velocity)/30);
            if(!e.path.empty()&&length(velocity)>.001f&&
               arena.clear(before,add(before,mul(normalize(velocity),lookahead)),e.radius)&&
               !arena.clear(before,add(before,mul(normalize(steered),lookahead)),e.radius))steered=velocity;
            moveMonster(e,steered,step);
        }
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if(!e.friendly&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&arena.sight(e.position,player.position))
            hurtPlayer(p.contact,{0,0,e.id,-1});
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
        remaining-=step;r.clock+=step;
        if(r.clock>=1.f/30-1e-6f){r.clock=0;r.frameReady=false;}
    }
    e.target=r.destination;
}
} // namespace dw
