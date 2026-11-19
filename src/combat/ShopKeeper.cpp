#include "combat/Simulation.hpp"
#include "world/SourceRecordedShop.hpp"
namespace dw {
bool Simulation::keeperBlastHit(const Event &e) const {
    const auto &site=arena.rooms[size_t(room)];
    if(site.sourceShopTemplate!=0||site.keeper.destroyed||!keeperTuning.destructible||e.damage<=0)return false;
    const auto box=shopCartGeometry::bounds(site.center);
    const Vector3 surface{std::clamp(e.position.x,box.min.x,box.max.x),std::clamp(e.position.y,box.min.y,box.max.y),std::clamp(e.position.z,box.min.z,box.max.z)};
    const float d=distance(e.position,surface);
    const auto end=d>.025f?sub(surface,mul(unit(sub(surface,e.position)),.025f)):e.position;
    return d<e.radius&&(!e.explosionLineCheck||d<.001f||arena.sight(e.position,end));
}
void Simulation::damageKeeper(float internalDamage) {
    auto &site=arena.rooms[size_t(room)];auto &k=site.keeper;
    if(k.destroyed||site.sourceShopTemplate!=0||internalDamage<=0)return;
    k.sourceHealth=std::max(0.f,k.sourceHealth-internalDamage/CombatHealthUnitsPerSource);checkpointNeeded=true;
    if(k.sourceHealth>1e-5f)return;
    k.destroyed=true;k.rng=recordedShopSlotSeed(site,3);k.drops=sourceKeeperDrops(k.rng);
    if(!keeperTuning.rewards||keeperTuning.outcome==1)k.drops={};
    else if(keeperTuning.outcome>1) {
        k.drops={};const int mode=keeperTuning.outcome;
        k.drops.count=mode==4?1:2;
        for(int i=0;i<k.drops.count;++i)k.drops.entries[size_t(i)]={mode==3?85:5,mode==3?0:mode==4?100:20,mode==4?64:0,keeperRandom(k.rng)};
    }
    // All explosion recipients were selected before collision was removed.
    arena.rebuildWalls();cancelMove();for(auto &enemy:enemies)enemy.pathTime=0;
    particleEffect(ParticleEffect::Dirt,site.center,{0,1,0},1.3f);
    announce("KEEPER DESTROYED",2);
}
void Simulation::deliverKeeperDrops() {
    auto &site=arena.rooms[size_t(room)];auto &k=site.keeper;
    if(!k.destroyed||dead||finished)return;
    while(k.delivered<k.drops.count) {
        const auto &d=k.drops.entries[size_t(k.delivered)];
        if(d.type==85&&livingEnemies()>=limits.enemies)return;
        if(d.type==5&&pendingBloodRewards.size()>=1024)return;
        if(d.type==85) {
            std::optional<Vector3> at;
            for(int i=0;i<64&&!at;++i) {
                const float angle=float(i+k.delivered*7)*2.399963f;
                auto p=add(site.center,{std::cos(angle)*(1.2f+float(i/16)*.8f),0,std::sin(angle)*(1.2f+float(i/16)*.8f)});p.y=.85f;
                if(arena.roomAt(p)!=room||arena.blocked(p,.55f)||planarDistance(player.position,p)<1.5f||arena.path(site.entry,p,.48f).empty())continue;
                if(std::any_of(enemies.begin(),enemies.end(),[&](const auto &e){return e.alive&&planarDistance(e.position,p)<e.radius+.65f;}))continue;
                at=p;
            }
            if(!at)return;
            const auto id=spawnMonster(monsterId(85),*at);if(!id)return;
            auto *enemy=findEnemy(id);enemy->keeperSpawn=true;
            // Reuse accepted ordinary Spider movement/HP; native thrown arrival is separate.
        } else if(d.type==5&&d.variant==100)pendingBloodRewards.push_back({site.center,room,d.subtype,1,k.delivered,d.seed});
        else if(d.type==5&&d.variant==20) {
            const auto coin=sourceOrdinaryPickup(d.seed,20);
            pendingBloodRewards.push_back({site.center,room,0,coin.subtype,k.delivered,d.seed});
        } else return;
        ++k.delivered;checkpointNeeded=true;
    }
}
}
