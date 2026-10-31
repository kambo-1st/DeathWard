#include "combat/Simulation.hpp"

namespace dw {
void Simulation::identifyDamageSource(Event &event) const {
    auto &source=event.context.damageSource;
    if(source!=DamageSource::Unspecified)return;
    if(!event.context.sourceEntity) {
        source=event.hostile?DamageSource::Enemy:event.harmsCompanions?DamageSource::Environment:DamageSource::Player;
        return;
    }
    if(const auto *body=findEnemy(event.context.sourceEntity)) {
        const auto *environment=content->environmentActor(body->monster);
        source=environment?(environment->kind==EnvironmentActorKind::Tnt?DamageSource::Tnt:DamageSource::Environment):
            body->friendly?DamageSource::Ally:DamageSource::Enemy;
    } else if(std::any_of(enemyBombs.begin(),enemyBombs.end(),[&](const auto &b){return b.id==event.context.sourceEntity;})||
              std::any_of(pendingEnemyBombs.begin(),pendingEnemyBombs.end(),[&](const auto &b){return b.id==event.context.sourceEntity;})) {
        source=DamageSource::Enemy;
    } else {
        source=event.hostile?DamageSource::Enemy:event.harmsCompanions?DamageSource::Environment:DamageSource::Player;
    }
}

bool Simulation::sourceImmune(const Enemy &enemy,const Event &event) const {
    if(event.execution)return false;
    const auto *p=content->sourceImmunity(enemy.monster);
    if(!p||!((p->flame&&event.damageKind==DamageKind::Flame)||(p->explosion&&event.explosionDamage)))return false;
    const auto source=event.context.damageSource;
    // Installed1.7.9b checks EntityRef friendly flag, direct player, player/familiar
    // spawner and TNT. Burning-status damage is a separate native flag from fire.
    return source!=DamageSource::Player&&source!=DamageSource::Ally&&source!=DamageSource::Tnt;
}

bool Simulation::tryLethalMorph(Enemy &enemy,const Event &event) {
    const auto *p=content->lethalMorph(enemy.monster);
    if(!p||event.execution||enemy.hp>0||enemy.kind!=EnemyKind::Monster||enemy.friendly||
       enemy.componentOwner||enemy.partner||enemy.formation)return false;
    const float scale=enemy.maxHp/content->monsterHealth(enemy.monster,arena.profile.sourceStage);
    // Strict source residual-health gate, already converted into DeathWard HP.
    if(enemy.hp<=-p->overkill||combatRng.bounded(unsigned(p->chanceOutOf))>=unsigned(p->chance))return false;
    auto target=p->target;
    if(!p->choices.empty()) {
        int total=0;for(const auto &[child,weight]:p->choices)total+=weight;
        int choice=int(combatRng.bounded(unsigned(total)));
        for(const auto &[child,weight]:p->choices) {
            if(choice<weight){target=child;break;}
            choice-=weight;
        }
    }
    enemy.monster=target;
    enemy.hp=enemy.maxHp=content->monsterHealth(target,arena.profile.sourceStage)*scale;
    enemy.state=EnemyState::Ready;enemy.stateTime=0;enemy.phase=0;
    enemy.behavior={};enemy.hop={};enemy.auxiliary=enemy.trailTime=enemy.lift=0;
    enemy.lob=content->lobWalker(target)?std::optional<LobWalkerRuntime>{LobWalkerRuntime{}}:std::nullopt;
    enemy.headShooter.reset();
    enemy.buzz.reset();
    enemy.path.clear();enemy.pathTime=0;
    // Source delay is an integral20..39 updates; no fractional cadence jitter.
    const int low=int(std::lround(p->delayMin*30)),high=int(std::lround(p->delayMax*30));
    const int delay=low+int(combatRng.bounded(unsigned(high-low+1)));
    enemy.cooldown=float(delay)/30;
    enemy.gaper.reset();enemy.awakened=false;
    enemy.headless.reset();
    if(const auto *child=content->headless(target)) {
        auto &r=enemy.headless.emplace();
        // Native Morph leaves State=4 intact. The Gaper death branch writes the
        // child timer itself: do not run the headless spawn initializer again.
        r.initialized=true;r.cooldown=delay;r.ticks=int(std::lround(enemy.age*30));
        r.momentum=mul(horizontal(enemy.velocity),1/(child->scale*30));
    }
    checkpointNeeded=true;
    // ID, position, momentum, owner, stage scaling and existing projectiles survive.
    // No EnemyKilled, loot, kill counter, new slot, or temporary room-clear window.
    return true;
}
} // namespace dw
