#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 trailPoint(const std::deque<Vector3> &trail,float distance) {
    if(trail.empty())return {};
    for(size_t i=1;i<trail.size();++i) {
        const float span=planarDistance(trail[i-1],trail[i]);
        if(span>0&&distance<=span)return add(trail[i-1],mul(sub(trail[i],trail[i-1]),distance/span));
        distance-=span;
    }
    return trail.back();
}
}
bool Simulation::settleShellSegment(Enemy &e,float dt) {
    if(!e.segmentSettling)return true;
    const auto &p=*content->shell(e.monster);
    auto ground=e.position;ground.y=.85f;
    if(!arena.blocked(ground,e.radius)) {
        e.position.y=std::max(.85f,e.position.y-p.settleSpeed*dt);
        if(e.position.y<=.85f){e.segmentSettling=false;e.path.clear();e.pathTime=0;return true;}
        return false;
    }
    // Losing flight over cover/water has no direct 2D equivalent. Slide to the
    // nearest connected floor before descending; never teleport or erase flesh.
    e.pathTime-=dt;
    if(e.pathTime<=0) {
        e.path.clear();e.pathTime=1;
        bool found=false;
        for(int radius=1;radius<=24&&!found;++radius)for(int spoke=0;spoke<16&&!found;++spoke) {
            auto at=add(ground,rotateY({float(radius),0,0},float(spoke)*2*Pi/16));
            if(arena.roomAt(at)!=room||arena.blocked(at,e.radius)||arena.flightBlocked(at,e.radius,room))continue;
            if(arena.path(e.home,at,e.radius).empty())continue;
            auto path=arena.flightPath(e.position,at,e.radius,room);
            if(!path.empty()){e.path=std::move(path);found=true;}
        }
        if(!found&&!arena.blocked(e.home,e.radius))e.path=arena.flightPath(e.position,e.home,e.radius,room);
    }
    while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.15f)e.path.erase(e.path.begin());
    if(!e.path.empty()) {
        const auto delta=horizontal(sub(e.path.front(),e.position));
        e.position=arena.fly(e.position,mul(unit(delta),std::min(length(delta),p.settleSpeed*dt)),e.radius,room);
    }
    return false;
}
void Simulation::updateShell(SegmentedEncounterRuntime &group,float dt) {
    const auto &p=*content->segmentedBoss(group.monster);const auto &s=*content->shell(group.monster);
    for(auto &chain:group.chains) {
        if(chain.members.empty())continue;
        auto *leader=findEnemy(chain.members.front());if(!leader||!leader->alive)continue;
        const bool headed=leader->segmentHead;
        int exposed=0;
        for(auto id:chain.members)if(const auto *e=findEnemy(id);e&&e->alive&&!e->segmentHead&&e->segmentArmor<=0)++exposed;
        const float speed=headed?p.speed*(1-s.exposedSlowdown*float(exposed)/float(std::max(size_t(1),chain.members.size()-1))):s.fleshSpeed;
        for(size_t i=0;i<chain.members.size();++i) {
            auto *e=findEnemy(chain.members[i]);if(!e||!e->alive)continue;
            const auto old=e->position;
            e->age+=dt;e->flash=std::max(0.f,e->flash-dt);e->cooldown-=dt;e->auxiliary-=dt;e->state=EnemyState::Ready;
            const bool grounded=settleShellSegment(*e,dt);
            if(grounded) {
                if(i==0&&headed) {
                    auto direction=unit(horizontal(e->facing));
                    const auto toward=horizontal(sub(player.position,e->position));
                    if(length(toward)<s.steerRange) {
                        const float angle=std::atan2(direction.z,direction.x);
                        const float target=std::atan2(toward.z,toward.x);
                        const float change=std::remainder(target-angle,2*Pi);
                        const float diagonal=std::atan2(direction.z>=0?1.f:-1.f,direction.x>=0?1.f:-1.f);
                        const float next=std::clamp(angle+std::clamp(change,-s.turnRate*dt,s.turnRate*dt),diagonal-.3f,diagonal+.3f);
                        direction={std::cos(next),0,std::sin(next)};
                    }
                    const auto delta=mul(direction,speed*dt);
                    e->position=arena.fly(e->position,delta,e->radius,room);
                    if(std::abs(e->position.x-old.x)<std::abs(delta.x)*.5f)direction.x=-direction.x;
                    if(std::abs(e->position.z-old.z)<std::abs(delta.z)*.5f)direction.z=-direction.z;
                    e->facing=direction;
                } else if(i||chain.members.size()>1) {
                    auto target=i?trailPoint(chain.trail,float(i)*p.spacing):player.position;target.y=.85f;
                    const bool flying=e->segmentArmor>0;
                    e->pathTime-=dt;
                    const bool clear=flying?arena.flightClear(e->position,target,e->radius,room):arena.clear(e->position,target,e->radius);
                    if(clear)e->path={target};
                    else if(e->pathTime<=0) {
                        e->path=flying?arena.flightPath(e->position,target,e->radius,room):arena.path(e->position,target,e->radius);
                        e->pathTime=.6f;
                    }
                    while(!e->path.empty()&&planarDistance(e->position,e->path.front())<.1f)e->path.erase(e->path.begin());
                    if(!e->path.empty()) {
                        const auto delta=horizontal(sub(e->path.front(),e->position));
                        const auto motion=mul(unit(delta),std::min(length(delta),speed*dt*(i?1.5f:1.f)));
                        if(arena.roomAt(add(e->position,motion))==room)
                            e->position=flying?arena.fly(e->position,motion,e->radius,room):arena.move(e->position,motion,e->radius);
                        if(length(motion)>.001f)e->facing=unit(motion);
                    }
                }
            }
            if(i==0) {
                if(chain.trail.size()<2||planarDistance(chain.trail[1],e->position)>.1f)chain.trail.push_front(e->position);
                else chain.trail.front()=e->position;
                while(chain.trail.size()>1024)chain.trail.pop_back();
            }
            e->velocity=mul(sub(e->position,old),1/dt);
            if(segmentSphere(old,e->position,player.position,e->radius+.48f)<=1&&arena.sight(e->position,player.position))hurtPlayer(p.contactDamage);
            if(e->segmentHead||e->segmentArmor>0||!grounded)continue;
            if(i+1==chain.members.size()) {
                if(e->cooldown<=0) {
                    const auto child=p.exposedChild;
                    const int count=int(std::count_if(enemies.begin(),enemies.end(),[&](const auto &v){return v.alive&&v.monster==child;})+
                        std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &v){return v.id==child;}));
                    if(count<p.childLimit)queueMonster(child,add(e->position,mul(e->facing,e->radius+1)),0,e->generation+1,false,1,0,e->id);
                    e->cooldown=p.headInterval;
                }
            } else if(e->auxiliary<=0) {
                const auto aim=unit(sub(player.position,e->position));
                for(int n=-1;n<=1;++n)shootEnemy(*e,rotateY(aim,float(n)*s.shotSpread),p.shotDamage,p.shotSpeed);
                e->auxiliary=p.bodyInterval;
            }
        }
    }
}
void Simulation::reconcileShell(SegmentedEncounterRuntime &group) {
    const auto &p=*content->segmentedBoss(group.monster);std::vector<BossChainRuntime> next;
    auto retire=[&](EntityId id){if(auto *e=findEnemy(id)){e->alive=false;e->hp=0;e->segmentHead=false;}};
    auto append=[&](std::vector<EntityId> members,bool headed,EntityId chainId) {
        if(members.empty())return;
        BossChainRuntime chain;chain.id=chainId?chainId:nextEntity_++;chain.members=std::move(members);
        for(size_t i=0;i<chain.members.size();++i)if(auto *e=findEnemy(chain.members[i])) {
            const bool promote=headed&&i==0&&!e->segmentHead;
            e->segmentHead=headed&&i==0;
            if(promote)e->facing=unit(Vector3{e->facing.x>=0?1.f:-1.f,0,e->facing.z>=0?1.f:-1.f});
            e->path.clear();e->pathTime=0;chain.trail.push_back(e->position);
        }
        next.push_back(std::move(chain));
    };
    for(auto &chain:group.chains) {
        const bool changed=std::any_of(chain.members.begin(),chain.members.end(),[&](auto id){const auto *e=findEnemy(id);return !e||!e->alive;});
        if(!changed){next.push_back(std::move(chain));continue;}
        std::vector<std::vector<EntityId>> pieces;std::vector<EntityId> piece;
        for(auto id:chain.members) {
            if(const auto *e=findEnemy(id);e&&e->alive)piece.push_back(id);
            else if(!piece.empty()){pieces.push_back(std::move(piece));piece={};}
        }
        if(!piece.empty())pieces.push_back(std::move(piece));
        for(auto &part:pieces) {
            const bool originalHead=findEnemy(part.front())->segmentHead;
            if(originalHead) {
                if(part.size()==1)retire(part.front());
                else append(std::move(part),true,chain.id);
            } else if(int(part.size())>=p.splitMinimum&&(findEnemy(part.front())->segmentArmor>0||findEnemy(part.back())->segmentArmor>0)) {
                if(findEnemy(part.front())->segmentArmor<=0)std::reverse(part.begin(),part.end());
                append(std::move(part),true,0);
            } else {
                // Do not bridge over retired armored pieces. Detached contiguous
                // flesh stays a group; a lone flesh part is a stationary spawner.
                std::vector<EntityId> flesh;
                for(auto id:part) {
                    if(findEnemy(id)->segmentArmor<=0)flesh.push_back(id);
                    else {retire(id);append(std::move(flesh),false,0);flesh={};}
                }
                append(std::move(flesh),false,0);
            }
        }
    }
    group.chains=std::move(next);
}
} // namespace dw
