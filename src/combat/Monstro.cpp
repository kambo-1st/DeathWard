#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::flushMonstroShots(Enemy &e) {
    auto &r=*e.monstro;
    if(r.pendingShots.empty())return true;
    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const Event &x){return x.type==EventType::Shot;});
    if(!limits.eventsPerChain||limits.maxDepth<0||queue_.size()+r.pendingShots.size()>limits.queuedEvents||
        projectiles.size()+size_t(queued)+r.pendingShots.size()>limits.projectiles)return false;
    for(const auto &sample:r.pendingShots) {
        // Same fixed player-relative planar scale as D04-D06. Vertical arc
        // and bullet size remain explicit isometric presentation adapters.
        auto velocity=mul(sample.planar,GaperMovementScale*30*r.shotSpeed);velocity.y=-sample.fallingSpeed*.05f*30;
        Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
        shot.position=shot.origin=r.shotOrigin;shot.direction=unit(velocity);shot.speed=length(velocity);
        shot.damage=10;shot.projectileKind=ProjectileKind::Bullet;shot.projectileLife=8;
        shot.projectileFlightRetention=.9f;shot.projectileGravity=(.1f+sample.fallingAcceleration)*45;
        shot.projectileRadius=.22f*sample.size;
        queueRoot(shot);
    }
    r.pendingShots.clear();return true;
}

void Simulation::selectMonstroShots(Enemy &e,bool radial) {
    auto &r=*e.monstro;
    if(!r.pendingShots.empty())return;
    // ProjectileParams construction consumes one RNG word even when its angle
    // member is not used by this ordinary FireBossProjectiles path.
    combatRng.next();
    r.shotSpeed=monstroTuning.shotSpeed;
    r.shotOrigin={e.position.x,e.position.y+.3f,e.position.z};
    const auto aimed=unit(horizontal(sub(player.position,e.position)));
    for(int i=0;i<(radial?18:13);++i) {
        Vector3 planar;
        if(radial) {
            const float angle=sourceBossShotUnit(uint32_t(combatRng.next()))*Pi*2;
            planar={std::cos(angle)*7,0,std::sin(angle)*7};
        } else {
            const float magnitude=sourceBossShotUnit(uint32_t(combatRng.next()));
            const float angle=sourceBossShotUnit(uint32_t(combatRng.next()))*Pi*2;
            planar=add(mul(aimed,7),Vector3{std::cos(angle)*magnitude*3.5f,0,std::sin(angle)*magnitude*3.5f});
        }
        combatRng.next(); // Source Spawn seed; native global stream remains unaccepted.
        const auto fall=uint32_t(combatRng.next()),size=uint32_t(combatRng.next()),jitter=uint32_t(combatRng.next());
        r.pendingShots.push_back(sourceBossShot(planar,fall,size,jitter));
    }
    audioCues.push(AudioCueKind::MonsterAttack,e.position);
    flushMonstroShots(e);
}

void Simulation::updateMonstro(Enemy &e,float dt) {
    if(!e.monstro)e.monstro.emplace();
    auto &r=*e.monstro;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);
    if(!flushMonstroShots(e)){e.velocity={};return;}
    if(e.state==EnemyState::Stunned) {
        // Full native per-boss status eligibility is not accepted yet.
        e.stateTime-=dt;e.velocity={};
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    auto target=[&] {
        // Source targets the room grid with spacing40. Native room origin,
        // grid exclusions and layouts still require production-room integration.
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        const float cell=40*GaperMovementScale;
        const float x0=bounds.min.x+cell,z0=bounds.min.z+cell;
        r.goal={x0+cell*std::round((player.position.x-x0)/cell),.85f,z0+cell*std::round((player.position.z-z0)/cell)};
        r.goal.x=std::clamp(r.goal.x,bounds.min.x+e.radius,bounds.max.x-e.radius);
        r.goal.z=std::clamp(r.goal.z,bounds.min.z+e.radius,bounds.max.z-e.radius);
        r.hasGoal=true;
    };
    auto begin=[&](MonstroAction action) {
        r.action=action;r.frame=0;r.fired=false;r.hasGoal=false;
    };
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);
        if(!r.initialized){r.initialized=true;continue;}
        bool applyForce=false,large=false;
        float friction=.9f;
        if(r.action==MonstroAction::Select) {
            const int action=sourceMonstroAction(uint32_t(combatRng.next()));
            begin(action==0?MonstroAction::Walk:action==1?MonstroAction::Spit:MonstroAction::JumpUp);
            ++e.bossCycles;e.bossAttack=action;
            audioCues.push(AudioCueKind::Warning,e.position);
        } else {
            ++r.frame;
            if(r.action==MonstroAction::Spit) {
                if(r.frame==21&&!r.fired){r.fired=true;selectMonstroShots(e,false);}
                if(r.frame>=66)begin(MonstroAction::Select);
            } else if(r.action==MonstroAction::Walk) {
                r.intangible=r.frame>=6&&r.frame<22;
                if(!r.hasGoal)target();
                applyForce=r.frame<22;friction=sourceMonstroFriction(applyForce);
                if(r.frame>=45) {
                    if(uint32_t(combatRng.next())&1)begin(MonstroAction::Walk);
                    else begin(MonstroAction::Select);
                    r.intangible=false;
                }
            } else if(r.action==MonstroAction::JumpUp) {
                if(r.frame>=10){begin(MonstroAction::JumpDown);r.intangible=true;}
            } else if(r.action==MonstroAction::JumpDown) {
                if(!r.hasGoal)target();
                r.intangible=r.frame<32;
                applyForce=r.frame<32;large=true;friction=sourceMonstroFriction(applyForce,true);
                if(r.frame==34&&!r.fired){r.fired=true;selectMonstroShots(e,true);}
                if(r.frame>=64){begin(MonstroAction::Select);r.intangible=false;}
            }
        }
        if(applyForce)r.momentum=sourceMonstroForce(r.momentum,mul(horizontal(sub(r.goal,e.position)),1/GaperMovementScale),large);
        r.momentum=mul(r.momentum,friction); // Native base friction1, timeScale1.
        if(!r.pendingShots.empty())break;
    }
    const auto before=e.position;
    const auto movement=mul(r.momentum,GaperMovementScale*30*monstroTuning.movement*dt);
    if(r.intangible) {
        // Grid class3: preserve the enclosing room while crossing its interior.
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        auto wanted=add(e.position,movement);
        wanted.x=std::clamp(wanted.x,bounds.min.x+e.radius,bounds.max.x-e.radius);
        wanted.z=std::clamp(wanted.z,bounds.min.z+e.radius,bounds.max.z-e.radius);
        e.position=arena.move(e.position,sub(wanted,e.position),e.radius);
    } else e.position=arena.move(e.position,movement,e.radius);
    e.velocity=mul(sub(e.position,before),1/dt);
    if(length(horizontal(e.velocity))>0)e.facing=unit(horizontal(e.velocity));
    if(r.action==MonstroAction::Spit||r.action==MonstroAction::Select)e.facing=unit(horizontal(sub(player.position,e.position)));
    // Graphical height is separate from native planar collision policy.
    e.lift=0;
    if(r.action==MonstroAction::Walk&&r.intangible)e.lift=2*std::sin(Pi*float(r.frame-6)/16);
    if(r.action==MonstroAction::JumpUp)e.lift=float(r.frame)*.4f;
    if(r.action==MonstroAction::JumpDown&&r.intangible)e.lift=4*(1-float(r.frame)/32);
    e.state=r.intangible?EnemyState::Jumping:r.action==MonstroAction::Spit?EnemyState::Windup:EnemyState::Ready;
    if(!r.intangible&&segmentSphere(sub(before,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
       arena.sight(e.position,player.position))hurtPlayer(10,{0,0,e.id,-1});
}
} // namespace dw
