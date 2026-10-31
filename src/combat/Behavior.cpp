#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateBehavior(Enemy &e,const MonsterDefinition &d,const BehaviorDefinition &g,float dt) {
    auto &runtime=e.behavior;
    // External interruptions cancel the graph's committed attack, just as legacy stun did.
    if(e.state==EnemyState::Stunned) {
        e.stateTime-=dt;
        if(e.stateTime<=0){e.state=EnemyState::Ready;runtime.initialized=false;}
        return;
    }
    auto actions=[&](const std::vector<BehaviorAction> &list) {
        for(auto action:list)switch(action) {
        case BehaviorAction::None:break;
        case BehaviorAction::LockTarget:e.target=player.position;break;
        case BehaviorAction::ResetCooldown:e.cooldown=d.cooldown;break;
        case BehaviorAction::Warning:if(!e.friendly)audioCues.push(AudioCueKind::Warning,e.position);break;
        case BehaviorAction::Summon:if(g.summon)summonMonsters(e,*g.summon);break;
        case BehaviorAction::Fire: {
            auto aim=g.projectileAim==BehaviorAim::Facing?e.facing:
                sub(g.projectileAim==BehaviorAim::Player?player.position:e.target,e.position);
            if(!d.flying)aim.y=0;
            aim=unit(aim);
            const auto kind=g.projectileKind==BehaviorShot::Tar?ProjectileKind::Tar:
                g.projectileKind==BehaviorShot::Ember?ProjectileKind::Ember:
                g.projectileKind==BehaviorShot::Brown?ProjectileKind::Brown:
                g.projectileKind==BehaviorShot::Bone?ProjectileKind::Bone:
                g.projectileKind==BehaviorShot::DarkBone?ProjectileKind::DarkBone:ProjectileKind::Bullet;
            const float curve=g.projectileCurve*(g.alternateCurve&&(runtime.volleys%2)?-1.f:1.f);
            for(int n=0;n<g.projectileCount;++n) {
                const auto direction=g.projectilePattern==BehaviorPattern::Radial?
                    rotateY({1,0,0},g.projectileAngle+float(n)*2*Pi/float(g.projectileCount)):
                    rotateY(aim,g.projectileAngle+(float(n)-float(g.projectileCount-1)/2)*g.spread);
                shootEnemy(e,direction,g.projectileDamage,g.projectileSpeed,0,kind,g.projectileLife,curve);
            }
            ++runtime.volleys;
            break;
        }
        }
    };
    auto present=[&](const BehaviorState &state) {
        e.state=state.pose==BehaviorPose::Windup?EnemyState::Windup:state.pose==BehaviorPose::Exposed?EnemyState::Exposed:EnemyState::Ready;
        e.stateTime=std::max(0.f,(state.useWindup?d.windup:state.duration)-runtime.elapsed);
        if(state.pose==BehaviorPose::Windup&&g.projectileAim==BehaviorAim::Facing)
            e.target=add(e.position,mul(e.facing,g.projectileSpeed*g.projectileLife));
    };
    if(!runtime.initialized||runtime.graph!=g.key) {
        const auto volleys=runtime.graph==g.key?runtime.volleys:0;
        runtime={g.key,g.initialIndex,0,true};runtime.volleys=volleys;
        present(g.states[runtime.state]);actions(g.states[runtime.state].enter);
    }
    const auto &state=g.states.at(runtime.state);
    runtime.elapsed+=dt;present(state);
    auto direction=sub(player.position,e.position);direction.y=0;direction=unit(direction);
    if(state.motion!=BehaviorMotion::Still) {
        if(state.motion==BehaviorMotion::Wander||state.motion==BehaviorMotion::AxisWander) {
            if(e.auxiliary<=0) {
                e.facing=rotateY({1,0,0},state.motion==BehaviorMotion::AxisWander?float(combatRng.bounded(4))*Pi/2:combatRng.real(-Pi,Pi));
                e.auxiliary=combatRng.real(g.wanderMin,g.wanderMax);
            }
            direction=e.facing;
        } else if(state.motion==BehaviorMotion::Flee)direction=mul(direction,-1);
        else if(!(d.flying?arena.flightClear(e.position,player.position,e.radius,room):arena.clear(e.position,player.position,e.radius))) {
            if(e.pathTime<=0){e.path=d.flying?arena.flightPath(e.position,player.position,e.radius,room):arena.path(e.position,player.position,e.radius);e.pathTime=1.1f;}
            while(!e.path.empty()&&planarDistance(e.position,e.path.front())<.08f)e.path.erase(e.path.begin());
            if(!e.path.empty())direction=unit(horizontal(sub(e.path.front(),e.position)));
        }
        const auto before=e.position;const float speed=d.speed*state.motionSpeed*EnemyMovementMultiplier;
        if(state.motion==BehaviorMotion::Orbit) {
            if(runtime.orbitSign==0)runtime.orbitSign=combatRng.bounded(2)?1.f:-1.f;
            if(d.flying?arena.flightClear(e.position,player.position,e.radius,room):arena.clear(e.position,player.position,e.radius)) {
                const auto tangent=mul(rotateY(direction,Pi/2),runtime.orbitSign);
                const float radial=std::clamp((distance(e.position,player.position)-g.orbitRadius)/g.orbitRadius,-1.5f,2.f);
                direction=unit(add(tangent,mul(direction,radial)));
            }
            const auto change=sub(mul(direction,speed),runtime.momentum);
            const float amount=length(change);
            runtime.momentum=add(runtime.momentum,mul(change,amount>0?std::min(1.f,g.acceleration*dt/amount):0));
            moveMonster(e,runtime.momentum,dt);
            // Collision removes blocked velocity components instead of accumulating
            // hidden speed into a wall. Regaining a path still accelerates smoothly.
            runtime.momentum=e.velocity;
        } else {
            runtime.momentum={};
            const auto velocity=mul(direction,speed);
            moveMonster(e,state.motion==BehaviorMotion::Chase?steerMonsterBodies(e,velocity):velocity,dt);
        }
        if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
        if((state.motion==BehaviorMotion::Wander||state.motion==BehaviorMotion::AxisWander)&&distance(before,e.position)<speed*dt*.5f) {
            e.facing=rotateY(e.facing,Pi/2);e.auxiliary=std::min(g.wanderMin,.4f);
        }
    }
    // One transition per simulation tick: even an authored zero-time cycle is bounded.
    // File order is deliberate transition priority; no action can recursively tick a graph.
    for(const auto &transition:state.transitions) {
        bool match=false;
        switch(transition.guard) {
        case BehaviorGuard::Always:match=true;break;
        case BehaviorGuard::Timer:match=runtime.elapsed+Tick*.001f>=(state.useWindup?d.windup:state.duration);break;
        case BehaviorGuard::AttackReady:match=e.cooldown<=0&&distance(e.position,player.position)<g.range&&arena.sight(e.position,player.position);break;
        case BehaviorGuard::AlignedAttackReady: {
            // Bounded acquisition cadence, independent from the player's render
            // rate. Entity phase avoids all wanderers checking on the same step.
            const auto tick=int64_t(std::floor((e.age+float(e.id%3)/30)/g.alignmentInterval));
            if(tick==runtime.alignmentTick)break;
            runtime.alignmentTick=tick;
            if(e.cooldown>0)break;
            const auto predicted=add(player.position,mul(player.velocity,combatRng.real(0,g.alignmentPrediction)));
            const auto delta=horizontal(sub(predicted,e.position));
            match=std::min(std::abs(delta.x),std::abs(delta.z))<g.alignment&&length(delta)<g.range&&arena.sight(e.position,predicted);
            break;
        }
        case BehaviorGuard::CooldownReady:match=e.cooldown<=0;break;
        case BehaviorGuard::HealthBelow:match=e.hp<=e.maxHp*transition.value;break;
        }
        if(!match)continue;
        actions(state.exit);runtime.state=transition.target;runtime.elapsed=0;
        present(g.states[runtime.state]);actions(g.states[runtime.state].enter);break;
    }
    if(d.contact&&distance(e.position,player.position)<e.radius+.48f&&arena.sight(e.position,player.position))hurtPlayer(10);
}
} // namespace dw
