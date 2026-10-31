#include "items/Items.hpp"

namespace dw {
namespace {
void emitItem(Simulation &run,Event child,const Event &parent,const ItemKey &item) {
    // New item effects are new attacks, not the original bomb's armor bypass.
    child.ignoreAdaptiveArmor=child.bypassAdaptiveHistory=false;
    auto context=parent.context;context.sourceItem=item;
    context.sourceEffect=item.legacy()?int(*item.legacy()):-1;
    run.emit(std::move(child),context);
}
void split(Simulation &run,const Event &e,const ItemKey &owner) {
    if(e.type!=EventType::ProjectileHit||e.hostile||e.areaDamage||e.remainingLife<=Tick)return;
    ++run.stats.splits;
    for(float angle:{-.42f,.42f}) {
        Event shot=e;shot.type=EventType::Shot;
        shot.direction=rotateY(unit(e.direction),angle);
        shot.position=add(e.position,mul(shot.direction,.2f));
        // Retain the firing origin for returning fragments and later ghosts.
        shot.attack=e.attack?*e.attack:playerAttack(run,e.damage,e.lastRound);
        auto &spec=*shot.attack;
        spec.damage=e.damage*(spec.scatter?.65f:.8f);
        spec.life=std::min(spec.life,e.remainingLife);
        if(e.attack) {spec.bounces=e.remainingBounces;spec.pierce=e.remainingPierce;}
        spec.radius=std::max(.06f,spec.radius*.85f);
        shot.damage=spec.damage;shot.target=e.target;shot.explosiveHit=false;
        emitItem(run,shot,e,owner);
    }
}
void powder(Simulation &run,const Event &e,const ItemKey &owner) {
    if(e.type!=EventType::EnemyKilled||e.hostile)return;
    Event explosion=e;explosion.type=EventType::Explosion;explosion.damage=35;explosion.radius=3.5f;
    explosion.demolition=Demolition::Soft;explosion.playerDamage=0;explosion.compactBlast=false;
    explosion.explosiveHit=false;
    emitItem(run,explosion,e,owner);
}
void ghost(Simulation &run,const Event &e,const ItemKey &owner) {
    if(e.type!=EventType::EnemyKilled||e.hostile)return;
    Event shot=e;shot.type=EventType::Shot;shot.position=e.origin;shot.target=0;
    shot.ghost=true;shot.returning=false;shot.explosiveHit=false;
    // Shotless kills (dynamite/barrels) repeat one current weapon projectile.
    // Bullet-derived explosions instead preserve the actual birth specification.
    shot.attack=e.attack?*e.attack:playerAttack(run,run.player.shotDamage,e.lastRound);
    shot.damage=shot.attack->damage;shot.direction=e.attack?e.attack->heading:unit(e.direction);
    shot.demolition=Demolition::Soft;shot.playerDamage=0;
    emitItem(run,shot,e,owner);
    ++run.stats.ghosts;run.effectVisual(e.origin,.7f,2,.6f);
}
void cap(Simulation &run,const Event &e,const ItemKey &owner) {
    if(e.type!=EventType::ProjectileHit||e.hostile||e.areaDamage||!e.explosiveHit||!e.attack)return;
    Event blast=e;blast.type=EventType::Explosion;blast.damage=e.attack->capDamage;
    blast.radius=e.attack->capRadius;blast.playerDamage=e.attack->capSelfDamage;
    blast.playerDamageHostile=false;blast.demolition=Demolition::Soft;blast.compactBlast=true;
    blast.explosiveHit=false;blast.areaDamage=true;
    emitItem(run,blast,e,owner);
}
}
AttackSpec playerAttack(const Simulation &run,float damage,bool sixth,float speed) {
    const auto b=run.content->resolve(run.items,damage,speed,sixth);
    AttackSpec spec;spec.damage=b[BuildStat::Damage];spec.speed=b[BuildStat::Speed];
    spec.life=b[BuildStat::Life];spec.radius=b[BuildStat::Radius];
    spec.homingTurn=b[BuildStat::Homing];spec.returnRange=b[BuildStat::ReturnRange];
    spec.capDamage=b[BuildStat::CapDamage];spec.capRadius=b[BuildStat::CapRadius];spec.capSelfDamage=b[BuildStat::CapSelfDamage];
    spec.pierce=int(b[BuildStat::Pierce]);spec.bounces=int(b[BuildStat::Bounces]);
    spec.scatter=b[BuildStat::Scatter]>0;spec.rail=b[BuildStat::Rail]>0;return spec;
}
int primaryPellets(const Simulation &run) {
    return int(run.content->resolve(run.items,run.player.shotDamage,26,false)[BuildStat::Pellets]);
}
float primaryCadence(const Simulation &run) {
    return run.content->resolve(run.items,run.player.shotDamage,26,false)[BuildStat::Cadence];
}
std::span<const ItemDefinition> itemDefinitions() { return defaultMechanics()->items(); }
const ItemDefinition &itemDefinition(const ItemKey &key,const MechanicsLibrary &content) {
    if(const auto *def=content.item(key))return *def;
    static const ItemDefinition missing{{"missing",ItemKind::Internal,0},"Unavailable power","UNKNOWN","This content is not installed.",{}};
    return missing;
}
void dispatchItemEffects(Simulation &run,const Event &event) {
    // Snapshot the dispatch list. A hook that grants an item must not invalidate
    // iteration or retroactively subscribe that new item to the current event.
    std::vector<std::pair<ItemKey,size_t>> owned;
    for(const auto &def:run.content->items())if(!def.effects.empty())
        if(const auto count=run.itemStacks(def.id);count)owned.emplace_back(def.id,count);
    std::sort(owned.begin(),owned.end(),[](const auto &a,const auto &b){return a.first<b.first;});
    for(const auto &[key,count]:owned) {
        const auto &def=*run.content->item(key);
        for(const auto &hook:def.effects)for(size_t n=0;n<(hook.perCopy?count:1);++n) {
            if(hook.action=="split")split(run,event,key);
            else if(hook.action=="powder")powder(run,event,key);
            else if(hook.action=="ghost")ghost(run,event,key);
            else if(hook.action=="cap")cap(run,event,key);
        }
    }
}
} // namespace dw
