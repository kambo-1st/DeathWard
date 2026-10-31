#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateRockSpider(Enemy &e,float dt) {
    const auto &p=*content->rockSpider(e.monster);
    if(!e.rockSpider)e.rockSpider=RockSpiderRuntime{};
    auto &r=*e.rockSpider;
    const bool coal=e.environment.has_value();
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned&&!coal) {
        e.stateTime-=dt;r.clock=0;r.heading=r.momentum={};e.velocity={};
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    float remaining=dt;
    while(remaining>1e-7f) {
      if(r.clock==0) {
        ++r.ticks;
        if(!r.initialized)r.initialized=true;
        else if(r.phase==RockSpiderPhase::Rock) {
            r.height+=r.vertical;
            if(r.height>0) {
                r.height=0;
                if(arena.blocked(e.position,0)) {
                    // Native landing in a solid grid cell destroys the rock.
                    // Retrying a saturated event queue cannot lose this death.
                    Event hit;hit.type=EventType::Damage;hit.target=e.id;hit.damage=e.hp+1;
                    hit.execution=true;hit.context.sourceEntity=e.id;queueRoot(hit);
                    break;
                }
                r.momentum=mul(r.momentum,p.landingRetention);
                r.vertical=std::abs(r.vertical)>1?r.vertical*p.bounce:0;
            }
            r.vertical+=p.gravity;
            if(r.height>=p.gridHeight&&std::abs(r.vertical)<p.wakeVertical) {
                if(coal)r.momentum=mul(r.momentum,.9f);
                else if(length(r.momentum)<p.wakeSpeed&&combatRng.bounded(unsigned(p.wakeChance))==0) {
                    r.phase=RockSpiderPhase::Appearing;r.frame=0;
                }
            }
        } else if(r.phase==RockSpiderPhase::Appearing) {
            r.momentum=mul(r.momentum,p.retention);
            if(++r.frame>=p.appearFrames){r.phase=RockSpiderPhase::Skitter;r.frame=0;}
        } else {
            r.counter+=p.counterStep;
            if(r.counter<p.cycle&&r.counter%p.selectionStep==0) {
                ++r.selections;
                r.pursuing=combatRng.bounded(unsigned(p.chaseChance))!=0;
                if(r.pursuing) {
                    r.heading=horizontal(sub(player.position,e.position));
                    if(!arena.clear(e.position,player.position,e.radius)) {
                        const auto route=arena.path(e.position,player.position,e.radius);
                        r.heading=route.empty()?r.momentum:horizontal(sub(route.front(),e.position));
                    }
                    r.heading=rotateY(unit(r.heading),combatRng.real(-p.spread*.5f,p.spread*.5f)*Pi/180);
                } else {
                    // The final failed candidate is still committed natively;
                    // physical movement subsequently clips against the wall.
                    for(int attempt=0;attempt<p.wanderAttempts;++attempt) {
                        r.heading=rotateY({1,0,0},combatRng.real(0,2*Pi));
                        if(arena.clear(e.position,add(e.position,mul(r.heading,p.wanderDistance*p.scale)),e.radius))break;
                    }
                }
            }
            const bool extra=combatRng.bounded(2)==0;
            if(extra&&(r.counter&1))++r.counter;
            r.momentum=mul(add(r.momentum,mul(r.heading,p.force)),p.retention);
            // The final impulse happens before the counter/heading reset.
            if(r.counter>=p.cycle){r.counter=0;r.heading={};r.pursuing=false;++r.cycles;}
        }
        if(coal) {
            if(roomThreats()==0){e.alive=false;e.environment->spent=true;break;}
            auto wear=[&] {
                Event hit;hit.damage=content->environmentActor(e.monster)->damageScale;
                damageEnvironmentActor(e,hit); // Same per-hit1-or2 wear as a small shot.
            };
            if(r.ticks%uint64_t(p.decayFrames)==0&&combatRng.bounded(unsigned(p.decayChance))!=0)wear();
            // The Fireplace dispatch applies additional five-frame water wear
            // before delegating Coal to this controller.
            if(arena.rooms[size_t(room)].flooded&&(r.ticks+e.id)%uint64_t(p.wetDecayFrames)==0)wear();
        }
      }
    if(!e.alive)return;
    const float step=std::min(remaining,1.f/30-r.clock);
    e.lift=-r.height*p.scale;
    auto velocity=mul(r.momentum,p.scale*30);
    if(r.height<p.gridHeight) {
        const auto before=e.position;
        auto airborne=add(before,{0,e.lift,0});
        const auto moved=arena.fly(airborne,mul(velocity,step),e.radius,room);
        e.position.x=moved.x;e.position.z=moved.z;
        e.velocity=mul(sub(e.position,before),1/step);
    } else moveMonster(e,coal?velocity:steerMonsterBodies(e,velocity),step);
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    if(r.height>=p.entityHeight&&distance(add(e.position,{0,e.lift,0}),player.position)<e.radius+.48f&&arena.sight(e.position,player.position))
        hurtPlayer(p.contactDamage,{0,0,e.id,-1});
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    remaining-=step;r.clock+=step;
    if(r.clock>=1.f/30-1e-6f)r.clock=0;
    }
}

bool Simulation::rockSpiderDeath(Enemy &e,const Event &event) {
    const auto *p=content->rockSpider(e.monster);
    if(!p||e.environment||event.debugExecution||arena.blocked(e.position,0))return false;
    if(p->deathMorph) {
        const float healthScale=e.maxHp/content->monsterHealth(e.monster,arena.profile.sourceStage);
        const float radiusScale=e.radius/content->monster(e.monster)->radius;
        e.monster=p->deathMorph;
        const auto &next=*content->monster(e.monster);
        e.hp=e.maxHp=content->monsterHealth(e.monster,arena.profile.sourceStage)*healthScale;
        e.radius=next.radius*radiusScale;e.rockSpider.reset();e.spider=SpiderRuntime{};
        e.state=EnemyState::Ready;e.stateTime=0;e.lift=0;e.phase=0;e.behavior={};e.hop={};
        e.path.clear();e.pathTime=0;e.cooldown=next.cooldown;
        checkpointNeeded=true;
        return true; // Same entity, no kill/loot/new capacity slot or clear window.
    }
    if(p->deathChild) {
        queueMonster(p->deathChild,e.position,0,0,false,1,0,e.id,0,-1,{},true,{},mul(e.velocity,.5f));
        auto &child=pendingMonsters_.back();child.rockSpider=RockSpiderRuntime{};
        child.rockSpider->initialized=true;child.rockSpider->height=-1;
        child.rockSpider->vertical=-1-combatRng.real(0,1);
    }
    return false;
}
} // namespace dw
