#include "items/Items.hpp"

namespace dw {
namespace {
void ricochet(Projectile &p) {
    p.bounces += 3;
}
void judas(Projectile &p) {
    if (p.lastRound)
        p.pierce += 6;
}
void split(Simulation &run, const Event &e) {
    if (e.type != EventType::ProjectileHit || e.hostile)
        return;
    ++run.stats.splits;
    for (float angle : {-0.42f, 0.42f}) {
        Event shot = e;
        shot.type = EventType::Shot;
        shot.target = 0;
        shot.direction = rotateY(unit(e.direction), angle);
        shot.position = add(e.position, mul(shot.direction, 0.2f));
        shot.origin = shot.position;
        shot.damage = e.damage * 0.8f;
        // The struck body counts as already hit by each fragment. Other bodies
        // remain eligible, and subsequent hits can produce further fragments.
        shot.target = e.target;
        run.emit(shot, e.context, int(ItemId::Split));
    }
}
void powder(Simulation &run, const Event &e) {
    if (e.type != EventType::EnemyKilled || e.hostile)
        return;
    Event explosion = e;
    explosion.type = EventType::Explosion;
    explosion.damage = 35;
    explosion.radius = 3.5f;
    run.emit(explosion, e.context, int(ItemId::Powder));
}
void ghost(Simulation &run, const Event &e) {
    if (e.type != EventType::EnemyKilled || e.hostile)
        return;
    Event shot = e;
    shot.type = EventType::Shot;
    shot.position = e.origin;
    shot.target = 0;
    shot.ghost = true;
    shot.damage = std::max(run.player.shotDamage, e.damage);
    shot.direction = unit(e.direction);
    run.emit(shot, e.context, int(ItemId::Ghost));
    ++run.stats.ghosts;
    run.effectVisual(e.origin, 0.7f, 2, 0.6f);
}
} // namespace
const std::array<ItemDefinition, ItemCount> &itemDefinitions() {
    static const std::array<ItemDefinition, ItemCount> defs{
        {{ItemId::Ricochet, "Ricochet Coin", "COMMON",
          "Bullets bounce off walls three times. Every bounce keeps its other effects.", ricochet, nullptr},
         {ItemId::Split, "Split Lead", "STRANGE",
          "Every hit births two angled bullets. Those bullets can split again.", nullptr, split},
         {ItemId::Judas, "Judas Bullet", "CURSED",
          "Every sixth shot pierces six bodies. Lose 20% maximum health per copy.", judas, nullptr},
         {ItemId::Powder, "Powder of Jericho", "STRANGE",
          "Every kill explodes. Explosion kills can explode again.", nullptr, powder},
         {ItemId::Ghost, "Hangman's Coin", "STRANGE",
          "A ghost repeats each killing shot, carrying your projectile effects.", nullptr, ghost}}};
    return defs;
}
const ItemDefinition &itemDefinition(ItemId item) {
    return itemDefinitions().at(size_t(item));
}
void applyProjectileItems(const Simulation &run, Projectile &p) {
    if (p.hostile)
        return;
    for (const auto &def : itemDefinitions())
        for (auto owned : run.items)
            if (owned == def.id && def.modifyProjectile)
                def.modifyProjectile(p);
}
void dispatchItemEffects(Simulation &run, const Event &event) {
    // Registry order is explicit priority; acquisition order breaks ties for copies.
    for (const auto &def : itemDefinitions())
        for (auto owned : run.items)
            if (owned == def.id && def.onEvent)
                def.onEvent(run, event);
}
} // namespace dw
