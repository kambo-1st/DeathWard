#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::eggyLanded(Enemy &e) {
    const auto &p=*content->eggy(e.monster);
    if(!e.eggy)e.eggy=EggyRuntime{};
    auto at=e.position;at.y=.85f;
    // A2D creep patch cannot float above a local canyon river or solid cover.
    if(!arena.blocked(at,.1f)&&hazards.size()<limits.hazards) {
        Hazard h;h.kind=HazardKind::Tar;h.position=at;h.origin=at;h.delay=0;
        h.radius=p.creepRadius;h.duration=p.creepDuration;h.damage=0;
        h.tint={222,218,195,210};h.context.sourceEntity=e.id;
        h.harmsPlayer=!e.friendly;addHazard(h);++e.eggy->creepPatches;
    }
    return combatRng.bounded(unsigned(p.restartChance))==0;
}

bool Simulation::beginEggyDeath(Enemy &e,const Event &event) {
    if(!content->eggy(e.monster)||event.execution||e.friendly||e.hp>0)return false;
    if(!e.eggy)e.eggy=EggyRuntime{};
    auto &r=*e.eggy;if(r.dying)return true;
    r.dying=true;r.frame=0;r.clock=0;r.deathContext=event.context;
    r.anchor=e.position;r.anchor.y=.85f;
    // Do not strand its mandatory children in a river after an airborne kill.
    if(arena.blocked(r.anchor,e.radius)&&e.targetHop)r.anchor=e.targetHop->lastGround;
    e.position=r.anchor;e.hp=.1f;e.velocity={};e.lift=0;
    if(e.targetHop){e.targetHop->airborne=false;e.targetHop->targetReady=false;e.targetHop->frame=-1;}
    e.state=EnemyState::Exposed;e.stateTime=0;
    checkpointNeeded=true;return true;
}

void Simulation::updateEggyDeath(Enemy &e,float dt) {
    const auto &p=*content->eggy(e.monster);auto &r=*e.eggy;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.position=r.anchor;e.velocity={};e.lift=0;
    // A dead husk does not become a living or contacting enemy when stunned.
    e.state=EnemyState::Exposed;e.stateTime=0;
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30&&r.frame<p.deathFrames) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.frame;
        const int counter=r.frame-p.releaseFrame+1;
        if(!std::binary_search(p.releaseCounters.begin(),p.releaseCounters.end(),counter))continue;
        const auto &child=*content->swarmSpider(p.child);
        const auto at=add(r.anchor,rotateY({p.scatter,0,0},combatRng.real(0,2*Pi)));
        const auto direction=rotateY({1,0,0},combatRng.real(0,2*Pi));
        int roll=int(combatRng.bounded(unsigned(p.weights[0]+p.weights[1]+p.weights[2])));
        int kind=0;for(int i=0;i<3;++i)if((roll-=p.weights[size_t(i)])<0){kind=i;break;}
        const auto &hop=child.hops[size_t(kind)];SwarmSpiderRuntime born;
        born.initialized=true;born.kind=kind;born.frame=hop.jump+p.childAdvance;
        born.airborne=true;born.hops=1;
        born.launch=born.momentum=mul(direction,combatRng.real(hop.minimum,hop.maximum));
        const auto before=pendingMonsters_.size();
        queueMonster(p.child,at,0,e.generation+1,false,1,0,e.id,0,-1,{},true);
        if(pendingMonsters_.size()>before) {
            pendingMonsters_.back().swarmHop=born;++r.released;
        }
    }
    if(r.frame>=p.deathFrames&&!r.finishing) {
        Event finish;finish.type=EventType::Damage;finish.target=e.id;
        finish.damage=e.hp+1;finish.execution=true;finish.context=r.deathContext;
        finish.origin=finish.position=e.position;
        r.finishing=queueRoot(finish);
    }
}
} // namespace dw
