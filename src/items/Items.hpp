#pragma once
#include "combat/Simulation.hpp"

namespace dw {
std::span<const ItemDefinition> itemDefinitions();
const ItemDefinition &itemDefinition(const ItemKey &item, const MechanicsLibrary &content = *defaultMechanics());
AttackSpec playerAttack(const Simulation &run,float damage,bool sixth,float speed=26);
int primaryPellets(const Simulation &run);
float primaryCadence(const Simulation &run);
void dispatchItemEffects(Simulation &run, const Event &event);
} // namespace dw
