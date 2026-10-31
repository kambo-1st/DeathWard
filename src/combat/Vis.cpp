#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::shootVis(Enemy &e) {
    const auto &p=*content->vis(e.monster);auto &r=*e.vis;
    if(p.returningBody) {
        if(livingEnemies()+pendingMonsters_.size()>=limits.enemies)return false;
        const auto &child=*content->returningBody(p.returningBody);
        auto at=e.position;if(r.heading.x!=0)at.z+=child.spawnOffset*child.scale;
        const Vector3 impulse{r.heading.x*child.launch*child.horizontalMultiplier*child.scale*30,0,
            r.heading.z*child.launch*child.scale*30};
        queueMonster(p.returningBody,at,0,0,false,1,0,0,e.id,-1,{},true,{},impulse);
        ++r.volleys;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
    }
    // Admit the entire packet or retain the animation's Shoot event. A Double
    // or Scarred Vis must never silently lose one of its lanes at capacity.
    if(hazards.size()+size_t(p.beams)>limits.hazards)return false;
    const std::array<Vector3,4> directions{{r.heading,mul(r.heading,-1),
        {-r.heading.z,0,r.heading.x},{r.heading.z,0,-r.heading.x}}};
    for(int n=0;n<p.beams;++n) {
        const auto direction=directions[size_t(n)];
        Hazard beam;beam.kind=HazardKind::Beam;beam.delay=0;beam.duration=float(p.beamFrames)/30;
        beam.fadeDuration=float(p.fadeFrames)/30;beam.fadeScale=p.fadeScale;beam.fadeOnRoomClear=true;
        beam.radius=p.beamRadius;beam.damage=p.playerDamage;beam.context.sourceEntity=e.id;
        beam.harmsMonsters=true;
        OwnedBeamRuntime owned;owned.heading=direction;owned.offset={direction.x*p.originX,p.beamHeight-.85f,0};
        owned.range=p.beamRange;owned.monsterDamage=p.monsterDamage;owned.immuneType=e.monster.type;
        owned.damageFrames=p.damageFrames;beam.ownedBeam=owned;
        followOwnedBeam(beam);addHazard(beam);
    }
    ++r.volleys;audioCues.push(AudioCueKind::MonsterAttack,e.position);return true;
}

void Simulation::followOwnedBeam(Hazard &beam) {
    const auto &r=*beam.ownedBeam;const auto *owner=findEnemy(beam.context.sourceEntity);
    if(!owner||!owner->alive) {
        // Owner death disables damage immediately but lets the visible beam
        // contract. This is distinct from every existing ownerBound hazard.
        beam.fadeAge=std::max(0.f,beam.fadeAge);return;
    }
    beam.origin=add(owner->position,r.offset);
    beam.position=add(beam.origin,mul(r.heading,r.range));
    // Geometry adapter: 3D cliffs and solid cover clip the canyon beam; the
    // source is a 2D room laser. Moving the owner retraces both endpoints.
    const auto hit=arena.trace(beam.origin,beam.position,.05f);
    if(hit.hit)beam.position=add(beam.origin,mul(sub(beam.position,beam.origin),std::max(0.f,hit.t-.0001f)));
}

void Simulation::damageOwnedBeam(Hazard &beam,float dt) {
    auto &r=*beam.ownedBeam;r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.frame;
        if(r.frame%r.damageFrames)continue;
        ++r.pulses;
        if(beam.harmsPlayer&&segmentSphere(beam.origin,beam.position,player.position,beam.radius+.48f)<=1&&
            arena.sight(beam.origin,player.position))hurtPlayer(beam.damage,beam.context);
        if(!beam.harmsMonsters)continue;
        for(const auto &target:enemies) {
            if(!target.alive||target.id==beam.context.sourceEntity||target.maxHp<=0||
                (target.kind==EnemyKind::Monster&&target.monster.type==r.immuneType))continue;
            bool weak=false;
            if(enemyProjectileHit(target,beam.origin,beam.position,beam.radius,weak)>1||
                !arena.sight(beam.origin,target.position))continue;
            Event hit;hit.type=EventType::Damage;hit.target=target.id;hit.position=target.position;
            hit.origin=beam.origin;hit.direction=r.heading;hit.hostile=true;hit.weakPointHit=weak;
            hit.damage=r.monsterDamage;emit(hit,beam.context);
        }
    }
}

void Simulation::updateVis(Enemy &e,float dt) {
    const auto &p=*content->vis(e.monster);if(!e.vis)e.vis=VisRuntime{};auto &r=*e.vis;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    if(e.state==EnemyState::Stunned) {
        r.clock=0;r.momentum={};r.attackFrame=-1;r.fired=false;e.velocity={};
        e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;return;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized){r.initialized=true;continue;}
        ++r.ticks;
        if(r.attackFrame>=0) {
            if(r.attackFrame<p.shootFrame||r.fired)++r.attackFrame;
            if(r.attackFrame==p.shootFrame&&!r.fired) {
                if(!shootVis(e)){r.clock=0;return;}
                r.fired=true;
            }
            e.facing=r.heading;e.state=r.fired?EnemyState::Ready:EnemyState::Windup;
            e.stateTime=float(std::max(0,p.shootFrame-r.attackFrame))/30;
            if(r.attackFrame>=p.attackFrames){r.attackFrame=-1;r.fired=false;e.state=EnemyState::Ready;}
        } else {
            faceAxisWander(e,r);stepAxisWander(e,p,r);r.walkFrame=(r.walkFrame+1)%p.walkFrames;
            const auto frame=uint64_t(std::max(0.,std::floor((stats.duration-double(r.clock))*30+.00001)));
            const auto delta=horizontal(sub(player.position,e.position));
            // Native view/room bounds are adapted to the active room. The
            // acquisition helper is not line of sight: cover does not prevent a windup.
            if((frame+e.id)%uint64_t(p.checkFrames)==0&&
                length(delta)<p.range*p.scale&&std::min(std::abs(delta.x),std::abs(delta.z))<p.alignment*p.scale) {
                r.heading=std::abs(delta.x)>std::abs(delta.z)?Vector3{delta.x<0?-1.f:1.f,0,0}:
                    Vector3{0,0,delta.z<0?-1.f:1.f};
                r.attackFrame=0;r.fired=false;e.state=EnemyState::Windup;e.facing=r.heading;
                e.stateTime=float(p.shootFrame)/30;audioCues.push(AudioCueKind::Warning,e.position);
            }
        }
        r.momentum=mul(r.momentum,p.retention);
    }
    moveAxisWander(e,p,r,dt);
    if(planarDistance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position)) {
        Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
    }
}
} // namespace dw
