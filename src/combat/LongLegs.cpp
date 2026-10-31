#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateLongLegs(Enemy &e,float dt) {
    const auto &p=*content->longLegs(e.monster);
    if(!e.longLegs)e.longLegs=LongLegsRuntime{};
    auto &r=*e.longLegs;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.frame=-1;r.fired=false;r.targetReady=false;r.clock=0;e.path.clear();e.velocity={};r.momentum={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    auto destination=[&](bool flee) {
        r.targetReady=false;e.path.clear();
        const auto away=unit(horizontal(sub(e.position,player.position)));
        for(int attempt=0;attempt<16;++attempt) {
            const float angle=combatRng.real(0,2*Pi),reach=(flee?combatRng.real(30,480):40)*p.scale;
            auto offset=Vector3{std::cos(angle)*reach,0,std::sin(angle)*reach*(flee?.5f:1)};
            if(flee)offset=add(offset,mul(away,30*p.scale));
            auto at=add(e.position,offset);
            if(arena.roomAt(at)!=room||arena.blocked(at,e.radius))continue;
            if(flee&&planarDistance(at,player.position)<planarDistance(e.position,player.position)+p.scale*10)continue;
            auto path=arena.path(e.position,at,e.radius);if(path.empty())continue;
            r.destination=at;e.path=std::move(path);r.targetReady=true;return;
        }
    };
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.tick;
        if(!r.initialized){r.initialized=true;continue;}
        if(r.frame>=0) {
            r.momentum=mul(r.momentum,p.attackRetention);
            if(r.frame<p.eventFrame||r.fired)++r.frame;
            if(r.frame==p.eventFrame&&!r.fired) {
                if(p.child) {
                    if(e.generation>=4)r.fired=true;
                    else if(livingEnemies()+pendingMonsters_.size()<limits.enemies) {
                        if(content->sack(p.child)) {
                            // Source overlapping Sacks replace one another without a kill reward.
                            for(auto &old:enemies)if(old.alive&&old.monster==p.child&&
                                planarDistance(old.position,e.position)<old.radius+e.radius)old.alive=false;
                            queueMonster(p.child,e.position,0,e.generation+1,false,1,0,e.id,0,-1,{},true);
                            Hazard creep;creep.kind=HazardKind::Tar;creep.position=e.position;creep.delay=0;
                            creep.duration=p.creepDuration;creep.radius=p.creepRadius;creep.damage=0;
                            creep.context.sourceEntity=e.id;creep.tint={226,226,211,180};hazards.push_back(creep);
                        } else {
                            const auto impulse=rotateY({p.scale*30,0,0},combatRng.real(0,2*Pi));
                            queueMonster(p.child,e.position,0,e.generation+1,false,1,0,e.id,0,-1,{},true,{},impulse);
                            if(p.twinChance&&combatRng.bounded(unsigned(p.twinChance))==0)
                                queueMonster(p.child,e.position,0,e.generation+1,false,1,0,e.id,0,-1,{},true,{},mul(impulse,-1));
                        }
                        r.fired=true;
                    }
                } else {
                    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
                    if(queue_.size()+size_t(p.shots)>limits.queuedEvents||projectiles.size()+size_t(queued+p.shots)>limits.projectiles)continue;
                    const float speed=combatRng.real(p.shotMinimum,p.shotMaximum)*p.scale*30;
                    for(int i=0;i<p.shots;++i) {
                        auto velocity=rotateY({speed,0,0},2*Pi*float(i)/float(p.shots)+(p.shots==4?Pi/4:0));
                        velocity.y=p.shotUp+combatRng.real(-p.shotJitter,p.shotJitter);
                        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;shot.position=shot.origin={e.position.x,p.shotHeight,e.position.z};
                        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=10;shot.projectileLife=4;
                        shot.projectileGravity=p.shotGravity;shot.projectileFlightRetention=.9f;shot.projectileRadius=.25f;
                        queueRoot(shot);
                    }
                    r.fired=true;
                }
                if(r.fired){++r.attacks;audioCues.push(AudioCueKind::MonsterAttack,e.position);}
            }
            if(r.frame>=p.attackFrames){r.frame=-1;r.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
            else {e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames-r.frame)/30;}
            continue;
        }
        if(p.flee) {
            // Same source EvadeTarget primitive as Hive: staggered proximity
            // checks plus a sticky flee period, followed by physical path search.
            if((r.tick+e.id)%14==0) {
                const bool near=planarDistance(e.position,player.position)<(arena.sight(e.position,player.position)?250:170)*p.scale;
                if(near){if(!r.evadeChecks)r.targetReady=false;r.evadeChecks=3;}
                else r.evadeChecks=std::max(0,r.evadeChecks-1);
            }
            if(r.targetReady&&(planarDistance(e.position,r.destination)<3*p.scale||e.path.empty()))r.targetReady=false;
            if(!r.targetReady)destination(r.evadeChecks>0);
        } else {
            if(!r.targetReady||planarDistance(r.destination,player.position)>.5f||e.path.empty()) {
                r.destination=player.position;e.path=arena.path(e.position,r.destination,e.radius);r.targetReady=!e.path.empty();
            }
        }
        if(r.targetReady) {
            while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.3f)e.path.erase(e.path.begin());
            const auto delta=horizontal(sub(e.path.empty()?r.destination:e.path.front(),e.position));
            const bool path=!p.flee||r.evadeChecks>0;
            const float force=path?std::min(length(delta)/p.scale*.1f,2.f)*p.pathForce:.5f;
            // FindGridPath adds force divided by its .7 friction. This
            // controller then ASSIGNS .8, unlike Hive's multiplying modifier.
            r.momentum=add(r.momentum,mul(unit(delta),force/(path?.7f:.9f)));
        }
        r.momentum=mul(r.momentum,p.retention);
        bool attack=false;
        if(p.flee) {
            if(roomThreats()+pendingMonsters_.size()<size_t(p.populationLimit))
                attack=(!r.evadeChecks&&combatRng.bounded(unsigned(p.quietChance))==0)||combatRng.bounded(unsigned(p.chance))==0;
        } else attack=r.targetReady&&arena.clear(e.position,player.position,e.radius)&&combatRng.bounded(unsigned(p.chance))==0;
        if(attack){r.frame=0;r.fired=false;e.state=EnemyState::Windup;e.stateTime=float(p.attackFrames)/30;audioCues.push(AudioCueKind::Warning,e.position);}
    }
    moveMonster(e,steerMonsterBodies(e,mul(r.momentum,p.scale*30)),dt);
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
    }
}

} // namespace dw
