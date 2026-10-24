#include "items/Items.hpp"

namespace dw {
namespace {
int stacks(const Simulation &run,ItemId item,int cap=4) {return std::min(cap,int(run.itemStacks(item)));}
void split(Simulation &run,const Event &e) {
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
        run.emit(shot,e.context,int(ItemId::Split));
    }
}
void powder(Simulation &run,const Event &e) {
    if(e.type!=EventType::EnemyKilled||e.hostile)return;
    Event explosion=e;explosion.type=EventType::Explosion;explosion.damage=35;explosion.radius=3.5f;
    explosion.demolition=Demolition::Soft;explosion.playerDamage=0;explosion.compactBlast=false;
    explosion.explosiveHit=false;
    run.emit(explosion,e.context,int(ItemId::Powder));
}
void ghost(Simulation &run,const Event &e) {
    if(e.type!=EventType::EnemyKilled||e.hostile)return;
    Event shot=e;shot.type=EventType::Shot;shot.position=e.origin;shot.target=0;
    shot.ghost=true;shot.returning=false;shot.explosiveHit=false;
    // Shotless kills (dynamite/barrels) repeat one current weapon projectile.
    // Bullet-derived explosions instead preserve the actual birth specification.
    shot.attack=e.attack?*e.attack:playerAttack(run,run.player.shotDamage,e.lastRound);
    shot.damage=shot.attack->damage;shot.direction=e.attack?e.attack->heading:unit(e.direction);
    shot.demolition=Demolition::Soft;shot.playerDamage=0;
    run.emit(shot,e.context,int(ItemId::Ghost));
    ++run.stats.ghosts;run.effectVisual(e.origin,.7f,2,.6f);
}
void cap(Simulation &run,const Event &e) {
    if(e.type!=EventType::ProjectileHit||e.hostile||e.areaDamage||!e.explosiveHit||!e.attack)return;
    Event blast=e;blast.type=EventType::Explosion;blast.damage=e.attack->capDamage;
    blast.radius=e.attack->capRadius;blast.playerDamage=e.attack->capSelfDamage;
    blast.playerDamageHostile=false;blast.demolition=Demolition::Soft;blast.compactBlast=true;
    blast.explosiveHit=false;blast.areaDamage=true;
    run.emit(blast,e.context,int(ItemId::Cap));
}
}
AttackSpec playerAttack(const Simulation &run,float damage,bool sixth,float speed) {
    AttackSpec spec;spec.damage=damage;spec.speed=speed;
    const int scatter=stacks(run,ItemId::Scatter,3),rail=stacks(run,ItemId::Rail,5);
    const int homing=stacks(run,ItemId::Lodestone),returning=stacks(run,ItemId::Return);
    const int explosive=stacks(run,ItemId::Cap);
    spec.scatter=scatter>0;spec.rail=rail>0;
    // Form and stats are resolved once, in fixed order, independent of acquisition.
    if(scatter) {spec.damage*=rail?.48f:.38f;spec.radius=.11f;}
    if(rail) {spec.damage*=1.65f+.15f*float(rail-1);spec.speed=18;spec.pierce=3+2*(rail-1);spec.radius=.17f;}
    if(homing) {spec.speed*=.82f;spec.homingTurn=1.5f+.35f*float(homing-1);}
    if(scatter)spec.life=14.f/spec.speed;
    if(returning) {spec.returnRange=8+1.5f*float(returning-1);spec.life=2.2f;}
    if(explosive) {
        spec.damage*=.7f;spec.capDamage=10+4*float(explosive-1);
        spec.capRadius=1.5f+.1f*float(explosive-1);spec.capSelfDamage=7+2*float(explosive-1);
    }
    spec.bounces=3*int(run.itemStacks(ItemId::Ricochet));
    if(sixth)spec.pierce+=6*int(run.itemStacks(ItemId::Judas));
    return spec;
}
int primaryPellets(const Simulation &run) {
    const int count=stacks(run,ItemId::Scatter,3);
    return count?(run.itemStacks(ItemId::Rail)?std::min(5,3+count-1):3+2*count):1;
}
float primaryCadence(const Simulation &run) {
    const int rail=stacks(run,ItemId::Rail,5);
    return rail?.50f+.04f*float(rail-1):run.itemStacks(ItemId::Scatter)?.34f:.29f;
}
const std::array<ItemDefinition,ItemCount> &itemDefinitions() {
    static const std::array<ItemDefinition,ItemCount> defs{{
        {ItemId::Ricochet,"Ricochet Coin","COMMON","Bullets bounce three times per copy. Body piercing survives a bank shot.",nullptr},
        {ItemId::Split,"Split Lead","STRANGE","Hits split into two smaller shots. Fragments share the remaining lifetime and chain budget.",split},
        {ItemId::Judas,"Judas Bullet","CURSED","Every sixth primary shot gains six pierces per copy. Lose 20% maximum health per copy.",nullptr},
        {ItemId::Powder,"Powder of Jericho","STRANGE","Kills explode; explosion kills can explode again. Free blasts cannot open hard cover.",powder},
        {ItemId::Ghost,"Hangman's Coin","STRANGE","Repeat the killing projectile's original specification. Blast damage never increases ghost damage.",ghost},
        {ItemId::Scatter,"Scatter Cylinder","STRANGE","A short fan of weak pellets. Rail makes three heavier spikes. Copies add pellets, up to nine.",nullptr},
        {ItemId::Rail,"Rail Spike","STRANGE","Heavy, slower piercing shots with a slower cadence. Copies add weight and pierces, up to five copies.",nullptr},
        {ItemId::Lodestone,"Lodestone Sight","STRANGE","Slower shots bend toward visible enemies. Each fragment seeks independently. Copies improve turning, up to four.",nullptr},
        {ItemId::Return,"Return Spring","STRANGE","Short shots return to you. One body per leg; piercing adds targets. Outbound bounces only. Copies extend reach, up to four.",nullptr},
        {ItemId::Cap,"Blasting Cap","DANGEROUS","Lower bullet damage; the first body hit explodes once and can hurt you. Copies strengthen the blast and risk, up to four.",cap},
        {ItemId::Braid,"Fuse Braid","DANGEROUS","Smaller dynamite blast leaves two weaker delayed charges. They can strike cover again. Copies add power and fuse time, up to four.",nullptr}
    }};
    return defs;
}
const ItemDefinition &itemDefinition(ItemId item){return itemDefinitions().at(size_t(item));}
void dispatchItemEffects(Simulation &run,const Event &event) {
    for(const auto &def:itemDefinitions()) {
        if(!def.onEvent)continue;
        // Cap stacks modify ONE explosion, never duplicate the lifetime trigger.
        const size_t count=def.id==ItemId::Cap?std::min(size_t(1),run.itemStacks(def.id)):run.itemStacks(def.id);
        for(size_t i=0;i<count;++i)def.onEvent(run,event);
    }
}
} // namespace dw
