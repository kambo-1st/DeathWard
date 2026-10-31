#include "combat/Simulation.hpp"

namespace dw {
namespace {
Vector3 cardinal(Vector3 delta) {
    return std::abs(delta.x)>=std::abs(delta.z)?Vector3{delta.x<0?-1.f:1.f,0,0}:Vector3{0,0,delta.z<0?-1.f:1.f};
}
}

void Simulation::updateBoomFly(Enemy &enemy,float dt) {
    const auto &p=*content->boomFly(enemy.monster);const auto &d=*content->monster(enemy.monster);
    enemy.age+=dt;enemy.trailTime-=dt;
    enemy.cooldown-=dt/(EnemyCooldownMultiplier*arena.profile.cooldownScale);
    enemy.flash=std::max(0.f,enemy.flash-dt);
    enemy.fireContactCooldown=std::max(0.f,enemy.fireContactCooldown-dt);
    const auto previous=enemy.position;
    const auto wanted=mul(enemy.facing,d.speed*EnemyMovementMultiplier*dt);
    moveMonster(enemy,mul(wanted,1/dt),dt);
    const auto actual=sub(enemy.position,previous);
    // A wall can block one coordinate while the other slides. Reflect the
    // blocked axis independently; aggregate distance misses these collisions.
    if(std::abs(actual.x-wanted.x)>.0005f)enemy.facing.x=-enemy.facing.x;
    if(std::abs(actual.z-wanted.z)>.0005f)enemy.facing.z=-enemy.facing.z;
    if(p.kind==BoomFlyKind::Bone&&enemy.cooldown<=0) {
        const auto delta=horizontal(sub(player.position,enemy.position));
        if(length(delta)<=p.range&&std::min(std::abs(delta.x),std::abs(delta.z))<=p.alignment&&arena.sight(enemy.position,player.position)) {
            shootEnemy(enemy,cardinal(delta),p.shotDamage,p.shotSpeed,0,ProjectileKind::Bone);
            enemy.cooldown=p.interval;
        }
    }
    if(p.kind==BoomFlyKind::Sick&&enemy.trailTime<=0) {
        Hazard gas;gas.kind=HazardKind::Gas;gas.position=gas.origin=enemy.position;gas.delay=0;
        gas.radius=p.trailRadius;gas.duration=p.trailDuration;gas.damage=p.fieldDamage;gas.context.sourceEntity=enemy.id;
        gas.tint={111,137,59,120};addHazard(gas);enemy.trailTime=p.trailInterval;
    }
    if(segmentSphere(sub(previous,playerStepStart_),sub(enemy.position,player.position),{},enemy.radius+.48f)<=1&&
        arena.sight(enemy.position,player.position)) {
        Context source;source.sourceEntity=enemy.id;hurtPlayer(p.contact,source);
    }
}

void Simulation::boomFlyDeath(const Enemy &enemy) {
    const auto &p=*content->boomFly(enemy.monster);
    auto blast=[&](Vector3 position,float delay) {
        EnemyBomb bomb;bomb.id=nextEntity_++;bomb.source=enemy.id;bomb.sourceMonster=enemy.monster;bomb.room=room;bomb.blastMarker=true;
        bomb.charge.position=position;bomb.charge.origin=enemy.position;bomb.charge.delay=delay;
        bomb.charge.kind=HazardKind::MonsterBomb;bomb.charge.blastDamage=p.blastDamage;
        bomb.charge.damage=p.playerDamage;bomb.charge.radius=p.blastRadius;queueEnemyBomb(bomb);
    };
    if(p.kind==BoomFlyKind::Normal||p.kind==BoomFlyKind::Drowned||p.kind==BoomFlyKind::Tainted)
        blast(enemy.position,p.blastDelay);
    if(p.shots) {
        const bool bone=p.kind==BoomFlyKind::Bone;
        const auto axis=bone?cardinal(sub(player.position,enemy.position)):Vector3{1,0,0};
        const auto kind=bone?ProjectileKind::Bone:p.kind==BoomFlyKind::Sick?ProjectileKind::Green:ProjectileKind::Bullet;
        for(int n=0;n<p.shots;++n)shootEnemy(enemy,rotateY(axis,float(n)*2*Pi/float(p.shots)),p.shotDamage,p.shotSpeed,0,kind);
    }
    if(p.kind==BoomFlyKind::Drowned) {
        auto ground=enemy.position;ground.y=.85f;
        // Test the original death footprint, before a queued blast removes rocks.
        // A ground child must not materialize beside a death over a pit/obstacle.
        if(!arena.blocked(ground,content->monster(p.child)->radius)&&
            (!arena.canyon||!arena.canyon->waterBlocked(ground))&&combatRng.bounded(10000)<uint32_t(p.childChance))
            queueMonster(p.child,ground,0,enemy.generation+1);
    }
    if(p.kind==BoomFlyKind::Sick) {
        for(int n=0;n<8;++n) {
            Hazard gas;gas.kind=HazardKind::Gas;
            gas.position=add(enemy.position,rotateY({p.cloudSpread,0,0},float(n)*Pi/4));gas.origin=enemy.position;
            gas.radius=p.deathRadius;gas.delay=0;gas.duration=p.deathDuration;gas.damage=p.fieldDamage;
            gas.context.sourceEntity=enemy.id;gas.tint={111,137,59,135};addHazard(gas);
        }
    }
    if(p.kind==BoomFlyKind::Dragon||p.kind==BoomFlyKind::Tainted) {
        auto ground=enemy.position;ground.y=.85f;
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        for(int axis=0;axis<4;++axis) {
            const auto direction=rotateY({1,0,0},float(axis)*Pi/2+(p.diagonal?Pi/4:0));
            auto previous=ground;
            for(int n=1;n<=int(p.lineRange/p.lineStep);++n) {
                auto at=add(ground,mul(direction,float(n)*p.lineStep));
                if(at.x<=bounds.min.x||at.x>=bounds.max.x||at.z<=bounds.min.z||at.z>=bounds.max.z)break;
                if(p.kind==BoomFlyKind::Tainted) {
                    // Explosion propagation is not a projectile and is not stopped
                    // by breakable cover. Cliffs and actual room walls end the line;
                    // geometry shields targets at blast time.
                    if(!arena.flightClear(previous,at,.12f,room))break;
                    blast(at,p.blastDelay+float(n)*p.lineDelay);
                } else {
                    // Ground fire follows actual usable terrain. This clipping is
                    // a declared 3D adaptation, not a recovered native grid rule.
                    if(arena.blocked(at,.12f)||!arena.sight(previous,at)||
                        (arena.canyon&&arena.canyon->waterBlocked(at)))break;
                    Hazard fire;fire.kind=HazardKind::Fire;fire.position=at;fire.origin=enemy.position;
                    fire.radius=p.deathRadius;fire.delay=float(n)*p.lineDelay;fire.duration=p.deathDuration;
                    fire.damage=p.fieldDamage;fire.context.sourceEntity=enemy.id;addHazard(fire);
                }
                previous=at;
            }
        }
    }
}
} // namespace dw
