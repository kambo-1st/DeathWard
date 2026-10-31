#include "combat/Simulation.hpp"

namespace dw {
void Simulation::tryLeaperJump(Enemy &e,Vector3 target) {
    const auto &p=*content->leaper(e.monster);auto &r=*e.leaper;auto &hop=*e.targetHop;
    if(r.phase||r.pending||hop.targetReady||hop.airborne||combatRng.bounded(unsigned(p.chance))!=0)return;
    target.y=.85f;
    auto legal=[&](Vector3 at) {
        return !arena.blocked(at,e.radius)&&!arena.reservedSupplyCache(at,e.radius)&&
            arena.flightClear(e.position,at,e.radius,room);
    };
    if(!legal(target)) {
        // Source asks for a nearby legal grid point within120 units. Generated
        // 3D rooms use a bounded half-metre search and retain their solid walls.
        bool found=false;const auto wanted=target;
        for(float radius=.5f;radius<=p.searchRadius&&!found;radius+=.5f)
            for(int i=0;i<32;++i) {
                const auto at=add(wanted,rotateY({radius,0,0},2*Pi*float(i)/32));
                if(legal(at)){target=at;found=true;break;}
            }
        if(!found)return;
    }
    r.phase=1;r.frame=0;r.progress=0;r.target=target;r.start=e.position;++r.leaps;
    hop.frame=-1;hop.counter=0;hop.targetReady=false;hop.momentum={};hop.arc=0;
    e.velocity={};e.target=target;
    audioCues.push(AudioCueKind::Warning,e.position);
}
void Simulation::leaperLanded(Enemy &e,bool big) {
    const auto &p=*content->leaper(e.monster);auto &r=*e.leaper;
    if(!big&&!p.sticky)return;
    auto at=e.position;at.y=.85f;
    // Only one committed landing can wait for capacity. Further takeoffs wait
    // until it is emitted, so the packet cannot grow without bound.
    r.pending=LeaperLanding{at,big};
}
void Simulation::advanceLeaper(Enemy &e) {
    const auto &p=*content->leaper(e.monster);auto &r=*e.leaper;auto &hop=*e.targetHop;
    ++r.frame;
    if(r.phase==1&&r.frame>=p.upFrames){r.phase=2;r.frame=0;}
    if(r.phase==2&&r.frame>=p.downFrames) {
        r.phase=0;r.frame=0;hop.airborne=false;hop.counter=0;hop.frame=-1;hop.momentum={};e.velocity={};return;
    }
    hop.airborne=r.phase==1?r.frame>=p.jumpFrame:r.frame<p.landFrame;
    if(hop.airborne) {
        r.progress=std::min(1.f,r.progress+p.progressStep);
        e.position=arena.fly(e.position,mul(horizontal(sub(r.target,e.position)),r.progress),e.radius,room);
    } else e.position.y=.85f;
    if(r.phase==2&&r.frame==p.landFrame) {
        auto ground=e.position;ground.y=.85f;
        if(arena.blocked(ground,e.radius)||arena.reservedSupplyCache(ground,e.radius)) {
            // A closing gate or newly occupied landing cannot embed the body.
            ground=hop.lastGround;
        }
        e.position=ground;hop.lastGround=ground;++r.bigLandings;
        leaperLanded(e,true);
        particleEffect(ParticleEffect::Dirt,ground,{0,1,0},1);
    }
}
void Simulation::flushLeaperLanding(Enemy &e) {
    const auto &p=*content->leaper(e.monster);auto &r=*e.leaper;if(!r.pending)return;
    const auto landing=*r.pending;
    const int count=landing.big?p.shots:0;
    const float creep=landing.big?p.bigCreep:p.smallCreep;
    const bool patch=creep>0&&!arena.blocked(landing.position,.1f);
    const auto live=std::count_if(projectiles.begin(),projectiles.end(),[](const auto &shot){return shot.alive;});
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
    if((count&&(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+size_t(count)>limits.queuedEvents||
            size_t(live+queued+count)>limits.projectiles))||(patch&&hazards.size()>=limits.hazards))return;
    for(int i=0;i<count;++i) {
        const float angle=p.sticky?combatRng.real(0,2*Pi):2*Pi*float(i)/float(count);
        const Vector3 velocity{std::cos(angle)*p.speed,combatRng.real(p.upMin,p.upMax),std::sin(angle)*p.speed};
        Event shot;shot.hostile=!e.friendly;shot.context.sourceEntity=e.id;
        shot.position=shot.origin=landing.position;shot.position.y=shot.origin.y=p.shotHeight;
        shot.direction=unit(velocity);shot.speed=length(velocity);shot.damage=p.damage;shot.projectileLife=p.life;
        shot.projectileGravity=p.gravity;shot.projectileFlightRetention=p.retention;
        const float scale=p.sizeLow+(p.sizeStep>0?float(combatRng.bounded(2))*p.sizeStep:0)+
            (p.sizeJitter>0?combatRng.real(0,p.sizeJitter):0);
        shot.projectileRadius=p.radius*scale;
        // A color override must not grant Tar's impact-creep behavior.
        if(p.sticky)shot.projectileTint={67,57,63,255};
        if(e.friendly) {
            AttackSpec spec;spec.damage=p.damage;spec.speed=shot.speed;spec.life=p.life;spec.radius=shot.projectileRadius;
            shot.attack=spec;
        }
        queueRoot(shot);
    }
    if(patch) {
        Hazard h;h.kind=HazardKind::Tar;h.position=h.origin=landing.position;h.delay=0;
        h.radius=creep;h.duration=p.creepDuration;h.damage=0;h.tint={48,42,48,210};
        h.context.sourceEntity=e.id;h.harmsPlayer=!e.friendly;addHazard(h);++r.creepPatches;
    }
    if(count){++r.volleys;audioCues.push(AudioCueKind::MonsterAttack,landing.position);}
    r.pending.reset();
}
} // namespace dw
