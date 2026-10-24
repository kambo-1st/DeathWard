#pragma once
#include "combat/Simulation.hpp"

namespace dw {
struct ItemDefinition {
    ItemId id;
    const char *name;
    const char *rarity;
    const char *description;
    void (*onEvent)(Simulation &, const Event &);
};
const std::array<ItemDefinition, ItemCount> &itemDefinitions();
const ItemDefinition &itemDefinition(ItemId item);
AttackSpec playerAttack(const Simulation &run,float damage,bool sixth,float speed=26);
int primaryPellets(const Simulation &run);
float primaryCadence(const Simulation &run);
void dispatchItemEffects(Simulation &run, const Event &event);
} // namespace dw
