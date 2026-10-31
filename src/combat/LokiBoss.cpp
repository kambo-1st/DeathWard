#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::lokiPositionClear(const Enemy &e,Vector3 p,float playerClearance) const {
    const auto &b=arena.rooms[size_t(room)].bounds;
    if(p.x-e.radius<b.min.x||p.x+e.radius>b.max.x||p.z-e.radius<b.min.z||p.z+e.radius>b.max.z||
       planarDistance(p,player.position)<playerClearance||arena.blocked(p,e.radius)||
       !roomSpawnClear(p,e.radius)||arena.reservedSupplyCache(p,e.radius)||
       (arena.canyon&&arena.canyon->waterBlocked(p)))return false;
    for(const auto &other:enemies)if(other.alive&&other.id!=e.id&&
        planarDistance(p,other.position)<e.radius+other.radius+.15f)return false;
    return true;
}

EntityId Simulation::spawnLoki(MonsterId id,Vector3 center) {
    const auto &p=*content->loki(id);const auto &d=*content->monster(id);
    if(livingEnemies()+pendingMonsters_.size()+size_t(p.bodies)>limits.enemies) {
        suppress({},"Loki encounter capacity");return 0;
    }
    // Fit every body before mutating the encounter: never produce half a Lokii.
    std::array<Vector3,2> positions{};Enemy candidate;candidate.radius=d.radius;
    for(int body=0;body<p.bodies;++body) {
        bool found=false;
        const auto anchor=add(center,{p.bodies==2?(body?1.f:-1.f)*(d.radius+.3f):0,0,0});
        for(int attempt=0;attempt<81;++attempt) {
            auto at=anchor;
            if(attempt)at=add(at,rotateY({1.f+float(attempt/8)*.6f,0,0},float(attempt%8)*Pi/4));
            at.y=d.radius+.05f;
            if(!lokiPositionClear(candidate,at,d.radius+.65f)||
                (body&&planarDistance(at,positions[0])<d.radius*2+.2f))continue;
            positions[size_t(body)]=at;found=true;break;
        }
        if(!found){suppress({},"Loki encounter placement");return 0;}
    }
    EntityId group=0;
    for(int body=0;body<p.bodies;++body) {
        const auto entity=spawn(EnemyKind::Boss,positions[size_t(body)]);
        auto &e=enemies.back();if(!group)group=entity;
        e.monster=id;e.bossKind=BossKind::Isaac;e.bossGroup=group;e.bossHalf=body;
        e.hp=e.maxHp=d.hp;e.radius=d.radius;e.position=positions[size_t(body)];e.home=e.position;
        e.facing={0,0,1};e.cooldown=p.initialDelay+float(body)*p.volleyInterval;
    }
    return group;
}

void Simulation::updateLoki(Enemy &e,float dt) {
    const auto &p=*content->loki(e.monster);const auto &d=*content->monster(e.monster);
    const float pace=dt/(EnemyCooldownMultiplier*arena.profile.cooldownScale);
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};e.cooldown-=pace;
    auto finish=[&]{e.state=EnemyState::Ready;e.cooldown=d.cooldown;++e.bossCycles;e.bossStep=0;};
    auto volley=[&](int count,float angle) {
        for(int n=0;n<count;++n)shootEnemy(e,rotateY({1,0,0},angle+float(n)*2*Pi/count),p.shotDamage,p.shotSpeed);
    };
    auto summon=[&] {
        // Shared encounter cap for Lokii is an explicit local interpretation.
        const auto count=std::count_if(enemies.begin(),enemies.end(),[&](const auto &child){return child.alive&&child.summoner==e.bossGroup;})+
            std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &child){return child.summoner==e.bossGroup;});
        if(count<p.childLimit)queueMonster(p.child,e.position,0,e.generation+1,false,1,0,e.bossGroup);
    };
    auto destination=[&] {
        const auto &b=arena.rooms[size_t(room)].bounds;
        for(int n=0;n<64;++n) {
            Vector3 at{combatRng.real(b.min.x+e.radius,b.max.x-e.radius),e.radius+.05f,
                       combatRng.real(b.min.z+e.radius,b.max.z-e.radius)};
            if(lokiPositionClear(e,at,p.teleportClearance)){e.target=at;return true;}
        }
        return false;
    };
    if(e.state==EnemyState::Stunned) {
        e.stateTime-=dt;
        if(e.stateTime<=0)finish();
    } else if(e.state==EnemyState::Teleporting) {
        e.stateTime-=pace;
        if(e.stateTime<=0) {
            // Recheck occupancy at arrival; a moving player/second half can
            // invalidate the planned destination while the body is absent.
            if(!lokiPositionClear(e,e.target,p.teleportClearance)&&!destination()) {
                e.target=e.position;
                if(!lokiPositionClear(e,e.target,e.radius+.65f)){e.stateTime=.1f;return;}
            }
            e.position=e.target;e.state=EnemyState::Exposed;e.stateTime=p.reappear;
        }
        return; // No contact while absent, including the arrival tick.
    } else if(e.state==EnemyState::Exposed) {
        e.stateTime-=pace;if(e.stateTime<=0)finish();
    } else if(e.state==EnemyState::Windup) {
        e.stateTime-=pace;
        if(e.stateTime<=0) {
            if(e.bossAttack==0) {
                volley(4,e.bossStep==1?Pi/4:0);
                if(++e.bossStep==3)finish();else e.stateTime=p.volleyInterval;
            } else {if(e.bossAttack==1)volley(8,0);else summon();finish();}
        }
    } else if(e.cooldown<=0) {
        int total=0;for(int w:p.weights)total+=w;
        int roll=int(combatRng.bounded(uint32_t(total)));e.bossAttack=0;
        for(int n=0;n<4;++n)if((roll-=p.weights[size_t(n)])<0){e.bossAttack=n;break;}
        e.bossStep=0;
        if(e.bossAttack==3) {
            if(destination()){e.state=EnemyState::Teleporting;e.stateTime=p.vanish;}
            else e.cooldown=.25f;
        } else {e.state=EnemyState::Windup;e.stateTime=d.windup;}
    }
    if(e.state!=EnemyState::Teleporting&&planarDistance(e.position,player.position)<e.radius+.48f&&
        arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
    }
}
} // namespace dw
