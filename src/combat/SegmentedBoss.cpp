#include "combat/Simulation.hpp"

namespace dw {
namespace {
void resetTrail(BossChainRuntime &chain,const Simulation &run) {
    chain.trail.clear();
    for(auto id:chain.members)if(const auto *e=run.findEnemy(id))chain.trail.push_back(e->position);
}
Vector3 pointAlong(const std::deque<Vector3> &trail,float distance) {
    if(trail.empty())return {};
    for(size_t i=1;i<trail.size();++i) {
        const float span=planarDistance(trail[i-1],trail[i]);
        if(span>0&&distance<=span)return add(trail[i-1],mul(sub(trail[i],trail[i-1]),distance/span));
        distance-=span;
    }
    return trail.back();
}
}
EntityId Simulation::spawnSegmentedBoss(MonsterId id,Vector3 center) {
    const auto *p=content->segmentedBoss(id);const auto *d=content->monster(id);
    if(!p||!d||livingEnemies()+size_t(p->chains*p->segments+p->suppliers)>limits.enemies)return 0;
    const bool shell=content->shell(id)!=nullptr;
    center.y=.85f;
    std::vector<std::vector<Vector3>> positions;
    for(int n=0;n<p->chains;++n) {
        std::vector<Vector3> row;const float sign=n%2?-1.f:1.f;
        for(int part=0;part<p->segments;++part) {
            const auto at=add(center,{sign*(float(p->segments-1)*.5f-float(part))*p->spacing,0,(float(n)-float(p->chains-1)*.5f)*8});
            if(arena.roomAt(at)!=room||arena.blocked(at,d->radius)||!roomSpawnClear(at,d->radius))return 0;
            row.push_back(at);
        }
        positions.push_back(std::move(row));
    }
    std::vector<Vector3> suppliers;
    const float supplierRadius=content->monster(p->supplier)->radius;
    for(int attempt=0;attempt<128&&int(suppliers.size())<p->suppliers;++attempt) {
        const int spoke=(attempt%32)/2+(attempt%2)*16;
        const float angle=float(spoke)*2*Pi/32;
        const auto at=add(center,{std::cos(angle)*(12+attempt/32),0,std::sin(angle)*(12+attempt/32)});
        if(arena.roomAt(at)!=room||arena.blocked(at,supplierRadius)||!roomSpawnClear(at,supplierRadius)||
            arena.path(center,at,.48f).empty())continue;
        if(std::any_of(suppliers.begin(),suppliers.end(),[&](Vector3 v){return planarDistance(v,at)<6;}))continue;
        suppliers.push_back(at);
    }
    if(int(suppliers.size())!=p->suppliers)return 0; // Atomic: never leave a half-built mandatory encounter.
    SegmentedEncounterRuntime group;group.id=nextEntity_++;group.monster=id;
    group.maximumHealth=d->hp*float(p->chains*(p->segments-(shell?1:0)));EntityId first=0;
    for(size_t n=0;n<positions.size();++n) {
        BossChainRuntime chain;chain.id=nextEntity_++;chain.turnTime=p->turnMin;
        for(size_t part=0;part<positions[n].size();++part) {
            const auto actor=spawn(EnemyKind::Boss,positions[n][part]);auto &e=*findEnemy(actor);
            e.monster=id;e.bossKind=BossKind::Isaac;e.hp=e.maxHp=d->hp;e.radius=d->radius;
            e.segmentedEncounter=group.id;e.segmentArmor=p->armor;e.segmentHead=part==0;
            e.facing={n%2?-1.f:1.f,0,0};e.home=e.position;e.cooldown=p->headInterval+float(n)*.6f;e.auxiliary=p->bodyInterval;
            if(shell) {e.facing=unit(Vector3{e.facing.x,0,n%2?1.f:-1.f});e.position.y=arena.flightHeight(e.position,e.radius);}
            chain.members.push_back(actor);chain.trail.push_back(e.position);group.allMembers.push_back(actor);
            if(!first)first=actor;
        }
        group.chains.push_back(std::move(chain));
    }
    rooms[size_t(room)].segmented.push_back(std::move(group));
    for(auto at:suppliers) {
        const auto actor=spawnMonster(p->supplier,at);auto &e=*findEnemy(actor);
        e.facing=e.statueFacing=unit(horizontal(sub(center,at)));
    }
    return first;
}
float Simulation::segmentDamage(Enemy &e,const Event &event) {
    const auto &p=*content->segmentedBoss(e.monster);
    if(event.execution&&event.debugExecution)return event.damage;
    const bool shell=content->shell(e.monster)!=nullptr;
    if(shell&&e.segmentHead)return 0;
    if(e.segmentArmor>0) {
        // Generic instant-death/area/piercing flags are not armor-breaking bombs.
        if(!event.explosionDamage)return 0;
        const float fraction=std::clamp(planarDistance(event.position,e.position)/std::max(.01f,event.radius),0.f,1.f);
        const float amount=event.damage*(p.blastNear+(p.blastFar-p.blastNear)*fraction);
        e.segmentArmor=std::max(0.f,e.segmentArmor-amount);e.phase=e.segmentArmor>0?0:1;e.flash=.15f;
        if(e.segmentArmor==0) {
            particleEffect(ParticleEffect::Stone,e.position,{0,1,0},.6f);
            if(shell){e.segmentSettling=true;e.path.clear();e.pathTime=0;}
        }
        return 0; // Independent armor absorbs this hit; spillover remains an explicit local policy.
    }
    if(event.execution)return event.damage;
    if(event.explosionDamage) {
        const float fraction=std::clamp(planarDistance(event.position,e.position)/std::max(.01f,event.radius),0.f,1.f);
        return event.damage*(p.blastNear+(p.blastFar-p.blastNear)*fraction);
    }
    return event.damage;
}
float Simulation::bossHealthFraction(const Enemy &e) const {
    if(e.bossGroup) {
        float hp=0,maxHp=0;
        for(const auto &body:enemies)if(body.bossGroup==e.bossGroup){maxHp+=body.maxHp;if(body.alive)hp+=std::max(0.f,body.hp);}
        return maxHp>0?std::clamp(hp/maxHp,0.f,1.f):0;
    }
    if(!e.segmentedEncounter)return std::clamp(e.hp/e.maxHp,0.f,1.f);
    for(const auto &group:rooms[size_t(room)].segmented)if(group.id==e.segmentedEncounter) {
        const bool shell=content->shell(group.monster)!=nullptr;
        float health=0;for(const auto &member:enemies)if(member.alive&&member.segmentedEncounter==group.id&&!(shell&&member.segmentHead))health+=member.hp;
        return std::clamp(health/std::max(1.f,group.maximumHealth),0.f,1.f);
    }
    return 0;
}
void Simulation::updateSegmentedBosses(float dt) {
    for(auto &group:rooms[size_t(room)].segmented) {
        if(group.completed)continue;
        if(content->shell(group.monster)){updateShell(group,dt);continue;}
        const auto &p=*content->segmentedBoss(group.monster);
        for(auto &chain:group.chains) {
            if(chain.members.empty())continue;
            auto *head=findEnemy(chain.members.front());if(!head||!head->alive)continue;
            int exposed=0;for(auto id:chain.members)if(const auto *e=findEnemy(id);e&&e->alive&&e->segmentArmor<=0)++exposed;
            const float speed=p.speed*(1+p.exposedSpeed*float(exposed)/float(chain.members.size()));
            chain.turnTime-=dt;
            auto turn=[&](bool blocked) {
                const auto previous=head->facing;
                const int offset=int(combatRng.bounded(4));
                for(int n=0;n<4;++n) {
                    const std::array<Vector3,4> directions{{{1,0,0},{0,0,1},{-1,0,0},{0,0,-1}}};
                    const auto direction=directions[size_t((offset+n)%4)];
                    if(!blocked&&dot(direction,previous)<-.5f)continue;
                    const auto goal=add(head->position,mul(direction,head->radius+1));
                    if(arena.roomAt(goal)==room&&arena.clear(head->position,goal,head->radius)&&!arena.blocked(goal,head->radius)) {
                        head->facing=direction;break;
                    }
                }
                chain.turnTime=combatRng.real(p.turnMin,p.turnMax);
            };
            if(chain.turnTime<=0)turn(false);
            const auto before=head->position;
            const auto goal=add(before,mul(head->facing,speed*dt));
            if(arena.roomAt(goal)==room)head->position=arena.move(before,sub(goal,before),head->radius);
            if(planarDistance(before,head->position)<speed*dt*.5f)turn(true);
            // Distance-spaced samples retain enough trail even for a slow, long
            // externally configured chain. Frame-count capping loses its tail.
            if(chain.trail.size()<2||planarDistance(chain.trail[1],head->position)>.1f)chain.trail.push_front(head->position);
            else chain.trail.front()=head->position;
            while(chain.trail.size()>1024)chain.trail.pop_back();
            for(size_t i=0;i<chain.members.size();++i) {
                auto *e=findEnemy(chain.members[i]);if(!e||!e->alive)continue;
                const auto old=i?e->position:before;
                if(i) {
                    auto delta=horizontal(sub(pointAlong(chain.trail,float(i)*p.spacing),e->position));
                    const float range=length(delta);delta=mul(unit(delta),std::min(range,speed*dt*1.5f));
                    e->position=arena.move(e->position,delta,e->radius);
                    if(length(delta)>.001f)e->facing=unit(delta);
                }
                e->velocity=mul(sub(e->position,old),1/dt);e->age+=dt;e->flash=std::max(0.f,e->flash-dt);
                e->cooldown-=dt;e->auxiliary-=dt;e->state=EnemyState::Ready;
                if(segmentSphere(old,e->position,player.position,e->radius+.48f)<=1&&arena.sight(e->position,player.position))hurtPlayer(p.contactDamage);
                if(e->segmentHead&&e->cooldown<=0) {
                    const auto childKind=[&](MonsterId id){return id==p.armoredChild||id==p.exposedChild;};
                    const int count=int(std::count_if(enemies.begin(),enemies.end(),[&](const auto &v){return v.alive&&childKind(v.monster);})+
                        std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &v){return childKind(v.id);}));
                    if(count<p.childLimit) {
                        // Check the room cap once per burst, as distinct from an owner cap.
                        const int burst=1+int(combatRng.bounded(uint32_t(p.burstMaximum)));
                        const auto child=e->segmentArmor>0?p.armoredChild:p.exposedChild;
                        for(int n=0;n<burst;++n)queueMonster(child,add(e->position,mul(rotateY(e->facing,(float(n)-float(burst-1)*.5f)*.6f),e->radius+1)),0,e->generation+1,false,1,0,e->id);
                    }
                    e->cooldown=p.headInterval;
                } else if(!e->segmentHead&&e->segmentArmor<=0&&e->auxiliary<=0) {
                    for(int n=0;n<p.bodyShots;++n)shootEnemy(*e,rotateY({1,0,0},combatRng.real(-Pi,Pi)),p.shotDamage,combatRng.real(p.shotSpeed*.5f,p.shotSpeed));
                    e->auxiliary=p.bodyInterval;
                }
            }
        }
    }
}
void Simulation::reconcileSegmentedBosses() {
    auto &groups=rooms[size_t(room)].segmented;
    for(auto &group:groups) {
        if(group.completed)continue;
        if(content->shell(group.monster))reconcileShell(group);
        else {
        const auto &p=*content->segmentedBoss(group.monster);std::vector<BossChainRuntime> next;
        for(auto &chain:group.chains) {
            const bool changed=std::any_of(chain.members.begin(),chain.members.end(),[&](auto id){const auto *e=findEnemy(id);return !e||!e->alive;});
            if(!changed){next.push_back(std::move(chain));continue;}
            std::vector<std::vector<EntityId>> pieces;std::vector<EntityId> piece;
            for(auto id:chain.members) {
                if(const auto *e=findEnemy(id);e&&e->alive)piece.push_back(id);
                else if(!piece.empty()){pieces.push_back(std::move(piece));piece={};}
            }
            if(!piece.empty())pieces.push_back(std::move(piece));
            if(pieces.empty())continue;
            BossChainRuntime retained;retained.id=chain.id;retained.members=std::move(pieces.front());
            const size_t retainedIndex=next.size();next.push_back(std::move(retained));
            for(size_t i=1;i<pieces.size();++i) {
                if(int(pieces[i].size())>=p.splitMinimum) {
                    BossChainRuntime split;split.id=nextEntity_++;split.members=std::move(pieces[i]);next.push_back(std::move(split));
                } else {
                    // Short fragments close the gap behind the retained head. Do not
                    // silently delete their remaining armor/HP. Native edge case unmeasured.
                    auto &keep=next[retainedIndex].members;keep.insert(keep.end(),pieces[i].begin(),pieces[i].end());
                }
            }
            for(size_t i=retainedIndex;i<next.size();++i) {
                auto &result=next[i];resetTrail(result,*this);result.turnTime=0;
                for(size_t n=0;n<result.members.size();++n)if(auto *e=findEnemy(result.members[n]))e->segmentHead=n==0;
            }
        }
        group.chains=std::move(next);
        }
        if(!group.chains.empty())continue;
        group.completed=true;checkpointNeeded=true;
        // The encounter survives its first head and every partial split. Pay once
        // only after all original segments from both worms have actually died.
        const auto owned=[&](EntityId id){return std::find(group.allMembers.begin(),group.allMembers.end(),id)!=group.allMembers.end();};
        for(auto &shot:projectiles)if(shot.hostile&&owned(shot.context.sourceEntity)){shot.alive=false;shot.cancelled=true;}
        std::erase_if(queue_,[&](const Event &event){
            if(!event.hostile||!owned(event.context.sourceEntity))return false;
            auto it=chains.find(event.context.chainId);if(it!=chains.end()&&it->second.queued)--it->second.queued;return true;
        });
        if(std::none_of(groups.begin(),groups.end(),[](const auto &g){return !g.completed;})) {
            Enemy representative;representative.id=group.id;representative.kind=EnemyKind::Boss;representative.bossKind=BossKind::Isaac;
            bossKilled=true;rewardCanyonBoss(representative);
        }
    }
}
} // namespace dw
