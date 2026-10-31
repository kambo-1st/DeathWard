#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::delaysAdaptiveDamage(const Event &event) const {
    if(event.type!=EventType::Damage||event.adaptiveResolved||event.execution||event.damage<=0)return false;
    const auto *enemy=findEnemy(event.target);
    return enemy&&enemy->alive&&enemy->adaptiveArmor&&content->adaptiveArmor(enemy->monster)&&!sourceImmune(*enemy,event);
}
bool Simulation::adaptiveDamageFull(const Event &event) const {
    return delaysAdaptiveDamage(event)&&findEnemy(event.target)->adaptiveArmor->pending.size()>=std::max(size_t(1),limits.queuedEvents);
}
void Simulation::cancelAdaptiveDamage(Enemy &enemy) {
    if(!enemy.adaptiveArmor)return;
    for(const auto &hit:enemy.adaptiveArmor->pending) {
        const auto it=chains.find(hit.context.chainId);
        if(it!=chains.end()&&it->second.active)--it->second.active;
    }
    enemy.adaptiveArmor->pending.clear();
}
void Simulation::saveAdaptiveChains() {
    auto &saved=rooms.at(size_t(room)).adaptiveChains;saved.clear();
    // Both armor and Leper retain accepted source-frame damage across room exits.
    auto retain=[&](const auto &hits){for(const auto &hit:hits) {
        const auto id=hit.context.chainId;
        if(!saved.contains(id)) {
            const auto it=chains.find(id);
            saved[id]=it!=chains.end()?it->second:Chain{};
            saved[id].active=saved[id].queued=0;
        }
        ++saved[id].active;
    }};
    for(const auto &enemy:enemies) {
        if(enemy.adaptiveArmor)retain(enemy.adaptiveArmor->pending);
        if(enemy.leper){retain(enemy.leper->pendingDamage);retain(enemy.leper->applyingDamage);}
    }
}
void Simulation::updateAdaptiveArmor(float dt) {
    std::vector<EntityId> bodies;
    for(const auto &enemy:enemies)if(enemy.adaptiveArmor)bodies.push_back(enemy.id);
    for(const auto id:bodies) {
        auto *enemy=findEnemy(id);if(!enemy)continue;
        if(!enemy->alive){cancelAdaptiveDamage(*enemy);continue;}
        const auto *profile=content->adaptiveArmor(enemy->monster);
        if(!profile){cancelAdaptiveDamage(*enemy);enemy->adaptiveArmor.reset();continue;}
        enemy->adaptiveArmor->clock+=dt;
        while((enemy=findEnemy(id))&&enemy->alive&&enemy->adaptiveArmor->clock+1e-6f>=1.f/30) {
            auto &r=*enemy->adaptiveArmor;r.clock=std::max(0.f,r.clock-1.f/30);++r.ticks;
            auto hits=std::move(r.pending);r.pending.clear();
            float total=0;for(const auto &hit:hits)if(!hit.bypassAdaptiveHistory)total+=hit.damage;
            if(r.history.size()>=size_t(profile->historyFrames))r.history.pop_front();
            r.history.push_back(total);
            float sum=0;for(float amount:r.history)sum+=amount;
            r.recentDps=sum/float(r.history.size())*30;
            const float cap=enemy->maxHp/profile->strength;
            r.multiplier=1;
            if(r.recentDps>cap) {
                const float ratio=cap/r.recentDps;
                r.multiplier=ratio+std::max(profile->minimum-profile->correction*ratio,0.f);
            }
            if(!hits.empty())++r.batches;
            const float multiplier=r.multiplier;
            for(auto hit:hits) {
                // The whole accepted source-frame batch uses one multiplier.
                // Replaying does not consume another chain-generation budget.
                hit.adaptiveResolved=true;
                if(!hit.ignoreAdaptiveArmor&&!hit.bypassAdaptiveHistory)hit.damage*=multiplier;
                process(hit);
                const auto it=chains.find(hit.context.chainId);
                if(it!=chains.end()&&it->second.active)--it->second.active;
            }
        }
    }
}
} // namespace dw
