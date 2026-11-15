#pragma once
#include "combat/PlayerAttributes.hpp"
#include <cmath>
#include <stdexcept>

namespace dw {
// Ordinary 1.7.9b inventory bomb, empty build. Source values are separate from
// the accepted DW shooting-distance and shared outgoing-damage conversions.
// Countdown 45 decrements to zero, then explodes on invocation 46.
struct InventoryBombTuning {
    static constexpr int SourceCountdown=45;
    static constexpr float SourceClock=30, SourceDamage=100;
    static constexpr float WorldPerSourceCoordinate=11.f/260.f;
    float fuseMultiplier=1, radiusMultiplier=1, damage=SourceDamage;
    int selfDamageHalfHearts=-1; // -1: source amount from blast damage; 0+: explicit testing override.
    bool custom() const {return fuseMultiplier!=1||radiusMultiplier!=1||damage!=SourceDamage||selfDamageHalfHearts!=-1;}
    void validate() const {
        if(!std::isfinite(fuseMultiplier)||fuseMultiplier<.25f||fuseMultiplier>4||
           !std::isfinite(radiusMultiplier)||radiusMultiplier<.25f||radiusMultiplier>3||
           !std::isfinite(damage)||damage<1||damage>500||selfDamageHalfHearts< -1||selfDamageHalfHearts>12)
            throw std::invalid_argument("Dynamite: fuse 25-400%, radius 25-300%, damage 1-500, self damage Auto or 0-6 hearts");
    }
    static float sourceRadius(float damage) {return damage<=140?75.f:damage<175?90.f:105.f;}
    static int sourceSelfDamage(float damage) {return damage<=0?0:damage<85?1:2;}
    float fuseSeconds() const {return float(SourceCountdown+1)/SourceClock*fuseMultiplier;}
    float radius() const {return sourceRadius(damage)*WorldPerSourceCoordinate*radiusMultiplier;}
    float internalDamage() const {return damage*CombatHealthUnitsPerSource;}
    int selfDamage() const {return selfDamageHalfHearts<0?sourceSelfDamage(damage):selfDamageHalfHearts;}
};
} // namespace dw
