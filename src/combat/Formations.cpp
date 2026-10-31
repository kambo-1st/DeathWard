#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 groupTarget(const Simulation &s,Vector3 center,bool friendly) {
    if(!friendly)return s.player.position;
    Vector3 target=center;float best=std::numeric_limits<float>::infinity();
    for(const auto &e:s.enemies)if(e.alive&&!e.friendly) {
        const auto range=planarDistance(center,e.position);
        if(range<best){target=e.position;best=range;}
    }
    return target;
}
// New arrivals fill a dead slot first, otherwise bisect the largest angular gap.
// Existing angles never change, including when a founding member dies.
void admit(FormationRuntime &group,Enemy &enemy) {
    for(auto &slot:group.slots)if(!slot.member) {
        slot.member=enemy.id;enemy.formation=group.id;return;
    }
    std::vector<float> angles;for(const auto &slot:group.slots)angles.push_back(slot.angle);
    std::sort(angles.begin(),angles.end());
    float largest=-1,angle=0;
    for(size_t i=0;i<angles.size();++i) {
        const auto next=i+1<angles.size()?angles[i+1]:angles.front()+2*Pi;
        if(next-angles[i]>largest){largest=next-angles[i];angle=std::fmod((next+angles[i])*.5f,2*Pi);}
    }
    group.slots.push_back({enemy.id,angle});enemy.formation=group.id;
}
}
void Simulation::updateFormations(float dt) {
    auto &groups=rooms[size_t(room)].formations;
    // Transformation/team changes detach membership without changing population ownership.
    for(auto &group:groups)for(auto &slot:group.slots) {
        const auto *e=findEnemy(slot.member);
        if(!e||!e->alive||e->formation!=group.id||e->monster!=group.monster||e->friendly!=group.friendly)
            slot.member=0;
    }
    std::erase_if(groups,[](const auto &g){return std::none_of(g.slots.begin(),g.slots.end(),[](const auto &s){return s.member;});});
    std::vector<Enemy*> pending;
    for(auto &e:enemies)if(e.alive) {
        const auto found=std::find_if(groups.begin(),groups.end(),[&](const auto &g){return g.id==e.formation&&g.monster==e.monster&&g.friendly==e.friendly;});
        if(found==groups.end())e.formation=0;
        if(!e.formation&&content->formation(e.monster))pending.push_back(&e);
    }
    std::sort(pending.begin(),pending.end(),[](auto a,auto b){return a->id<b->id;});
    for(auto *enemy:pending) {
        if(enemy->formation)continue;
        const auto &rule=*content->formation(enemy->monster);
        FormationRuntime *available=nullptr;float best=std::numeric_limits<float>::infinity();
        for(auto &g:groups)if(g.monster==enemy->monster&&g.friendly==enemy->friendly&&
            (int(g.slots.size())<rule.capacity||std::any_of(g.slots.begin(),g.slots.end(),[](const auto &s){return !s.member;}))) {
            const float gap=planarDistance(g.center,enemy->position);
            if(gap<best){available=&g;best=gap;}
        }
        if(available){admit(*available,*enemy);continue;}
        std::vector<Enemy*> members;
        Vector3 mean{};
        for(auto *candidate:pending)if(!candidate->formation&&candidate->monster==enemy->monster&&candidate->friendly==enemy->friendly&&int(members.size())<rule.capacity) {
            members.push_back(candidate);mean=add(mean,candidate->position);
        }
        mean=mul(mean,1.f/float(members.size()));mean.y=.85f;
        const float envelope=rule.radius+enemy->radius+.05f;
        std::optional<Vector3> center;
        if(!arena.flightBlocked(mean,envelope,room))center=mean;
        else {
            const auto &area=arena.rooms[size_t(room)].bounds;float nearest=std::numeric_limits<float>::infinity();
            for(float z=area.min.z+envelope;z<=area.max.z-envelope;z+=1)
                for(float x=area.min.x+envelope;x<=area.max.x-envelope;x+=1) {
                    const Vector3 p{x,.85f,z};const float gap=planarDistance(p,mean);
                    if(gap<nearest&&!arena.flightBlocked(p,envelope,room)){center=p;nearest=gap;}
                }
        }
        // A room too narrow for a circle falls back to ordinary flight pursuit;
        // never teleport members through solid terrain to force a formation.
        if(!center)continue;
        FormationRuntime g;g.id=enemy->id;g.monster=enemy->monster;g.friendly=enemy->friendly;g.center=*center;
        for(size_t i=0;i<members.size();++i){g.slots.push_back({members[i]->id,2*Pi*float(i)/float(members.size())});members[i]->formation=g.id;}
        groups.push_back(std::move(g));
    }
    for(auto &g:groups) {
        const auto &rule=*content->formation(g.monster);
        const float envelope=rule.radius+content->monster(g.monster)->radius+.05f;
        g.angle=std::fmod(g.angle+rule.angularSpeed*dt,2*Pi);g.pathTime-=dt;
        auto target=groupTarget(*this,g.center,g.friendly);target.y=g.center.y;
        if(!arena.flightClear(g.center,target,envelope,room)) {
            if(g.pathTime<=0){g.path=arena.flightPath(g.center,target,envelope,room);g.pathTime=1.1f;}
            while(!g.path.empty()&&planarDistance(g.center,g.path.front())<.08f)g.path.erase(g.path.begin());
            target=g.path.empty()?g.center:g.path.front();
        } else g.path.clear();
        const auto delta=horizontal(sub(target,g.center));const auto range=length(delta);
        const float step=rule.speed*(g.friendly?1:EnemyMovementMultiplier)*dt;
        g.center=arena.fly(g.center,mul(unit(delta),std::min(step,range)),envelope,room);
        g.center.y=.85f; // The formation is an XZ controller, each body has its own clearance height.
    }
}
void Simulation::updateFormationMember(Enemy &e,const FormationDefinition &rule,float dt) {
    auto target=groupTarget(*this,e.position,e.friendly);
    const auto &groups=rooms[size_t(room)].formations;
    const auto group=std::find_if(groups.begin(),groups.end(),[&](const auto &g){return g.id==e.formation;});
    bool assigned=false;
    if(group!=groups.end())for(const auto &slot:group->slots)if(slot.member==e.id) {
        target=add(group->center,rotateY({rule.radius,0,0},group->angle+slot.angle));assigned=true;break;
    }
    if(!arena.flightClear(e.position,target,e.radius,room)) {
        if(e.pathTime<=0){e.path=arena.flightPath(e.position,target,e.radius,room);e.pathTime=.25f;}
        while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.08f)e.path.erase(e.path.begin());
        if(!e.path.empty())target=e.path.front();
    } else e.path.clear();
    const auto delta=horizontal(sub(target,e.position));
    const float speed=assigned?rule.gatherSpeed:rule.speed*(e.friendly?1:EnemyMovementMultiplier);
    moveMonster(e,mul(unit(delta),std::min(speed,length(delta)/dt)),dt);
    if(planarDistance(e.velocity,{})>.001f)e.facing=unit(horizontal(e.velocity));
    const auto *definition=content->monster(e.monster);
    if(!definition->contact)return;
    if(!e.friendly) {
        if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(10);
    } else if(e.cooldown<=0) {
        for(const auto &other:enemies)if(other.alive&&!other.friendly&&distance(e.position,other.position)<e.radius+other.radius&&arena.sight(e.position,other.position)) {
            Event hit;hit.type=EventType::Damage;hit.target=other.id;hit.damage=28;queueRoot(hit);e.cooldown=.7f;break;
        }
    }
}
} // namespace dw
