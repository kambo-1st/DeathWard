#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateStrider(Enemy &e,float dt) {
    const auto &p=*content->strider(e.monster);if(!e.strider)e.strider=StriderRuntime{};
    auto &r=*e.strider;e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);e.lift=p.hover;
    if(e.thrownOffspring){e.lift=0;updateThrownOffspring(e,dt);return;}
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.frame=-1;r.clock=0;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized)r.initialized=true;
        else if(r.frame>=0) {
            ++r.frame;
            auto direction=r.chasing?horizontal(sub(player.position,e.position)):r.direction;
            if(length(direction)>.0001f) {
                direction=unit(direction);
                const float angle=std::atan2(direction.z,direction.x);
                r.angle+=std::remainder(angle-r.angle,2*Pi)*p.turn;
                if(r.frame==p.rowFrame) {
                    r.momentum=add(r.momentum,mul(direction,combatRng.real(p.forceMinimum,p.forceMaximum)));
                    ++r.strokes;
                }
            }
            if(r.frame>=p.strokeFrames)r.frame=-1;
        } else if(combatRng.bounded(unsigned(p.checkChance))==0) {
            r.chasing=combatRng.bounded(unsigned(p.chaseChance))==0&&arena.sight(e.position,player.position);
            if(r.chasing){r.direction={};r.frame=0;}
            else if(combatRng.bounded(unsigned(p.wanderChance))==0) {
                r.direction=rotateY({1,0,0},combatRng.real(0,2*Pi));r.frame=0;
            }
        }
        r.momentum=mul(r.momentum,p.retention);
    }
    moveMonster(e,steerMonsterBodies(e,mul(r.momentum,p.scale*30)),dt);
    e.facing={std::cos(r.angle),0,std::sin(r.angle)};
    if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
    }
}

void Simulation::updateSwarmSpider(Enemy &e,float dt) {
    const auto &p=*content->swarmSpider(e.monster);if(!e.swarmSpider)e.swarmSpider=SwarmSpiderRuntime{};
    auto &r=*e.swarmSpider;e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(e.state==EnemyState::Stunned) {
        r.frame=-1;r.airborne=false;r.clock=0;r.momentum={};e.velocity={};e.lift=0;e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized){r.initialized=true;continue;}
        if(!r.airborne)r.momentum=mul(r.momentum,p.retention);
        if(r.frame>=0) {
            ++r.frame;const auto &hop=p.hops[size_t(r.kind)];
            if(r.frame==hop.jump){r.momentum=r.launch;r.airborne=true;++r.hops;}
            if(r.frame==hop.land)r.airborne=false;
            if(r.frame>=hop.frames||(r.frame>=hop.land&&combatRng.bounded(unsigned(p.earlyChance))==0))r.frame=-1;
        } else {
            auto delta=horizontal(sub(player.position,e.position));const float dist=length(delta)/p.scale;
            if(dist<=.0001f)continue;
            auto direction=unit(delta);
            const bool turn=combatRng.bounded(unsigned(dist>p.farRange?p.farTurnChance:p.turnChance))==0||dist<p.nearRange;
            if(turn) {
                if(combatRng.bounded(2)==0)direction=rotateY(direction,combatRng.bounded(2)?Pi/2:-Pi/2);
                else direction=mul(direction,-1);
            }
            const auto &weights=p.weights[size_t(dist<p.nearRange?0:dist>p.farRange?2:1)];
            int roll=int(combatRng.bounded(unsigned(weights[0]+weights[1]+weights[2])));
            r.kind=0;for(int i=0;i<3;++i)if((roll-=weights[size_t(i)])<0){r.kind=i;break;}
            const auto &hop=p.hops[size_t(r.kind)];
            const float speed=combatRng.real(hop.minimum,hop.maximum);
            r.launch=mul(rotateY(direction,combatRng.real(-hop.spread,hop.spread)*Pi/180),speed);
            r.frame=0;
        }
    }
    e.state=r.airborne?EnemyState::Jumping:EnemyState::Ready;
    const auto &hop=p.hops[size_t(r.kind)];
    // Source Jump/Land changes sprite pose and physics-knockback flag, not grid
    // collision or world height. Keep the ground collider throughout the hop.
    e.lift=r.airborne?p.height*std::sin(Pi*float(r.frame-hop.jump)/float(hop.land-hop.jump)):0;
    moveMonster(e,mul(r.momentum,p.scale*30),dt);
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    if(distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contactDamage,source);
    }
}
} // namespace dw
