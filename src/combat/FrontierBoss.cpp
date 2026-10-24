#include "combat/Simulation.hpp"

namespace dw {
void Simulation::throwBossCharge(const Enemy &enemy,Vector3 target) {
    Hazard charge;charge.kind=HazardKind::BossCharge;
    charge.position=enemy.position;charge.position.y=1.4f;
    charge.origin=target;
    constexpr float flight=.7f;
    charge.velocity=mul(sub(target,charge.position),1/flight);
    charge.velocity.y=(.18f-charge.position.y)/flight+9*flight;
    charge.delay=enemy.phase?2.2f:2.6f;charge.radius=2.6f;charge.damage=16;
    charge.context.sourceEntity=enemy.id;
    addHazard(charge);audioCues.push(AudioCueKind::Warning,target);
}

void Simulation::updateFrontierBoss(Enemy &e,float dt) {
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};
    e.phase=e.hp<=e.maxHp*.5f?1:0;e.stateTime-=dt;e.cooldown-=dt;
    const bool foreman=e.bossKind==BossKind::PowderForeman;
    const auto &layout=arena.rooms[size_t(room)];
    auto aim=[&](int attack) {
        e.bossAttack=attack;e.bossStep=0;e.bossTargetCount=0;
        e.target=player.position;e.facing=unit(sub(e.target,e.position));
        e.facing.y=0;e.facing=unit(e.facing);
        e.state=EnemyState::Windup;e.stateTime=foreman?1.05f:attack?1.2f:1.f;
        if(foreman&&attack==0) {
            const Vector3 side{-e.facing.z,0,e.facing.x};
            const auto predicted=add(player.position,mul(player.velocity,.25f));
            for(int n=0;n<(e.phase?3:2);++n) {
                auto wanted=add(predicted,mul(side,(float(n)-(e.phase?1.f:.5f))*3.5f));
                wanted.x=std::clamp(wanted.x,layout.bounds.min.x+3,layout.bounds.max.x-3);
                wanted.z=std::clamp(wanted.z,layout.bounds.min.z+3,layout.bounds.max.z-3);
                for(int attempt=0;attempt<20;++attempt) {
                    auto p=add(wanted,{std::cos(float(attempt)*2.4f)*float(attempt/4),0,
                                       std::sin(float(attempt)*2.4f)*float(attempt/4)});
                    if(arena.roomAt(p)!=room||arena.blocked(p,.6f)||
                       (arena.canyon&&arena.canyon->waterBlocked(p)))continue;
                    if(distance(p,e.position)<4)continue;
                    e.bossTargets[size_t(e.bossTargetCount++)]=p;break;
                }
            }
        }
        audioCues.push(AudioCueKind::Warning,e.position);
    };
    auto recover=[&] {
        e.state=EnemyState::Stunned;e.stateTime=e.phase?1.1f:1.5f;
    };
    if(e.state==EnemyState::Stunned) {
        if(e.stateTime<=0) {
            if(e.bossCombo>0) {--e.bossCombo;aim(0);}
            else {e.state=EnemyState::Ready;e.cooldown=.7f;}
        }
        return;
    }
    if(e.state==EnemyState::Ready) {
        // Short repositioning periods leave attacks committed and recovery readable.
        auto target=add(layout.center,rotateY({0,0,5},float(e.bossCycles)*2.1f));
        auto direction=unit(sub(target,e.position));
        if(distance(e.position,player.position)<4)direction=unit(sub(e.position,player.position));
        e.velocity=mul(direction,1.8f);e.position=arena.move(e.position,mul(e.velocity,dt),e.radius);
        e.facing=unit(sub(player.position,e.position));
        if(e.cooldown<=0) {
            const int attack=e.bossCycles++%2;
            e.bossCombo=!foreman&&e.phase&&attack==1?1:0;
            aim(attack);
        }
        return;
    }
    if(e.state==EnemyState::Windup) {
        if(e.stateTime>0)return;
        if(foreman&&e.bossAttack==0) {
            for(int n=0;n<e.bossTargetCount;++n)throwBossCharge(e,e.bossTargets[size_t(n)]);
            recover();return;
        }
        e.state=EnemyState::Charging;e.cooldown=0;
    }
    if(e.state!=EnemyState::Charging||e.cooldown>0)return;
    if(!foreman&&e.bossAttack==1) {
        // Sweep two sectors around a committed gap. The gap is 0.64 radians wide
        // and is drawn throughout the warning/attack; no shot enters it.
        const float angle=-1.08f+float(e.bossStep)*.18f;
        if(std::abs(angle)>.32f)shootEnemy(e,rotateY(e.facing,angle),12,9);
        ++e.bossStep;e.cooldown=.11f;
        if(e.bossStep>=13)recover();
    } else {
        // A burst repeats its locked aim, allowing a sideways escape. Neither a
        // faster phase nor the Marshal's follow-up removes the fresh windup.
        for(float angle:{-.2f,0.f,.2f})shootEnemy(e,rotateY(e.facing,angle),foreman?10:12,foreman?10:11);
        ++e.bossStep;e.cooldown=e.phase?.3f:.4f;
        if(e.bossStep>=3)recover();
    }
}
} // namespace dw
