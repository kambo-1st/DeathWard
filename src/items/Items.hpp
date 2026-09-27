#pragma once
#include "combat/Simulation.hpp"

namespace dw {
struct ItemDefinition {
    ItemId id;
    const char *name;
    const char *rarity;
    const char *description;
    void (*modifyProjectile)(Projectile &);
    void (*onEvent)(Simulation &, const Event &);
};
const std::array<ItemDefinition, ItemCount> &itemDefinitions();
const ItemDefinition &itemDefinition(ItemId item);
void applyProjectileItems(const Simulation &run, Projectile &projectile);
void dispatchItemEffects(Simulation &run, const Event &event);
} // namespace dw
