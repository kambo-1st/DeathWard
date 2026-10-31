#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateSpider(Enemy &e,float dt) {
    const auto &p=*content->spider(e.monster);if(!e.spider)e.spider=SpiderRuntime{};
    auto &r=*e.spider;e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    auto requestContactDeath=[&] {
        if(std::any_of(queue_.begin(),queue_.end(),[&](const auto &event){return event.type==EventType::Damage&&event.target==e.id&&event.execution;}))return;
        Event death;death.type=EventType::Damage;death.target=e.id;death.position=e.position;
        death.damage=e.hp+1;death.execution=true;death.context.sourceEntity=e.id;queueRoot(death);
    };
    // Preserve a spent child's death request when the event queue is full.
    if(e.selfDetonated){requestContactDeath();return;}
    const auto previous=e.position;
    auto contact=[&] {
        if(!e.friendly&&segmentSphere(sub(previous,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
           arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
            if(r.diesOnContact){e.selfDetonated=true;e.velocity={};r.momentum={};requestContactDeath();}
        }
    };
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);e.lift=0;
    if(e.thrownOffspring){updateThrownOffspring(e,dt);if(!e.thrownOffspring)contact();return;}
    // Preserve real collision/separation/knockback velocity between source ticks.
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.targetReady=false;r.pursuing=false;r.counter=0;r.clock=0;r.momentum={};e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;contact();return;
    }
    const auto &bounds=arena.rooms.at(size_t(room)).bounds;
    auto clamped=[&](Vector3 at,float left,float top,float right,float bottom) {
        // Narrow local rooms may not fit the native margins. Collapse that
        // axis to its centre instead of passing inverted bounds to clamp.
        auto axis=[](float at,float lo,float hi,float a,float b) {
            return lo+a>hi-b?(lo+hi)*.5f:std::clamp(at,lo+a,hi-b);
        };
        at.x=axis(at.x,bounds.min.x,bounds.max.x,std::max(e.radius,left),std::max(e.radius,right));
        at.z=axis(at.z,bounds.min.z,bounds.max.z,std::max(e.radius,top),std::max(e.radius,bottom));
        at.y=.85f;return at;
    };
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized){r.initialized=true;r.counter=0;continue;}
        if(r.targetReady) {
            --r.counter;
            const auto delta=horizontal(sub(r.destination,e.position));
            if(length(delta)<p.arrival*p.scale||(length(r.momentum)<p.stuckSpeed&&r.counter<0)) {
                r.targetReady=false;r.pursuing=false;r.counter=0;
            }
            // Native code still applies this last impulse when clearing a target.
            if(length(delta)>.0001f)r.momentum=add(r.momentum,mul(unit(delta),p.force));
        } else if(r.counter++>=p.idleFrames) {
            const float range=combatRng.real(p.rangeMinimum,p.rangeMaximum)*p.scale;
            if(planarDistance(e.position,player.position)<range&&arena.sight(e.position,player.position)) {
                r.destination=clamped(add(player.position,mul(horizontal(player.velocity),p.prediction/30)),
                    e.radius,e.radius,e.radius,e.radius);
                r.targetReady=true;r.pursuing=true;
            } else {
                const float reach=combatRng.real(p.wanderMinimum,p.wanderMaximum)*p.scale;
                const auto offset=rotateY({reach,0,0},combatRng.real(0,2*Pi));
                auto target=clamped(add(e.position,offset),p.leftMargin*p.scale,p.topMargin*p.scale,
                    p.rightMargin*p.scale,p.bottomMargin*p.scale);
                if(!arena.blocked(target,e.radius)) {
                    bool clear=arena.clear(e.position,target,e.radius);
                    if(!clear&&combatRng.bounded(unsigned(p.gapChance))==0) {
                        // Source mode1 trims each endpoint by10%. Use a narrow
                        // sight segment only for selection; motion still sweeps
                        // the full body, so no rock/pit penetration is permitted.
                        const auto delta=sub(target,e.position);
                        clear=arena.clear(add(e.position,mul(delta,.1f)),sub(target,mul(delta,.1f)),0);
                    }
                    if(clear){r.destination=target;r.targetReady=true;r.pursuing=false;r.counter=p.wanderFrames;}
                }
            }
        }
        r.momentum=mul(r.momentum,p.retention);
    }
    const auto velocity=mul(r.momentum,p.scale*30);
    moveMonster(e,steerMonsterBodies(e,velocity),dt);
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    contact();
}
} // namespace dw
