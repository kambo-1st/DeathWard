#pragma once
#include "core/Types.hpp"
#include <cstdint>
#include <stdexcept>
namespace dw {
// Tagged shared consumable slot: ordinary pills remain positive color IDs.
inline constexpr int TemperanceCard=-15;
struct BloodMachineTuning {
    int cardPrice=5,healthCost=1;
    float cycleSpeed=1,payoutScale=1,breakScale=1,bloodBagStrength=1,ivCooldown=.5f;
    int outcome=0; // 0 source rolls; 1 coins / 2 Blood Bag / 3 IV Bag testing overrides.
    bool operator==(const BloodMachineTuning &) const=default;
    bool custom()const{return *this!=BloodMachineTuning{};}
    void validate()const {
        if(cardPrice<0||cardPrice>30||healthCost<0||healthCost>4||outcome<0||outcome>3||
           !std::isfinite(cycleSpeed)||cycleSpeed<.25f||cycleSpeed>4||!std::isfinite(payoutScale)||payoutScale<0||payoutScale>3||
           !std::isfinite(breakScale)||breakScale<0||breakScale>3||!std::isfinite(bloodBagStrength)||bloodBagStrength<0||bloodBagStrength>2||
           !std::isfinite(ivCooldown)||ivCooldown<.1f||ivCooldown>3)throw std::runtime_error("Invalid Temperance settings");
    }
};
inline uint32_t bloodRandom(uint32_t &state){if(!state)state=1;state^=state>>1;state^=state<<11;state^=state>>6;return state;}
struct BloodOutcome{int item=0,coins=0;};
inline BloodOutcome sourceBloodOutcome(uint32_t &state,bool unlocked=true,bool ivAvailable=true,float breakScale=1) {
    bloodRandom(state); // Child's Heart roll; absent from this supported pool.
    const auto raw=bloodRandom(state);
    const double roll=double(raw%15)+double(raw/15)/286331154.;
    if(roll<breakScale){const bool iv=(bloodRandom(state)%2)!=0;return {iv&&ivAvailable?135:unlocked?119:135,0};}
    return {0,std::max(1,int(bloodRandom(state)%3))};
}
inline int sourceIvCoins(uint32_t &state){return std::max(1,int(bloodRandom(state)%3));}
struct BloodMachine {
    Vector3 position{};int room=-1;uint32_t rng=1;
    enum class Phase{Idle,Initiate,Prize,Broken};Phase phase=Phase::Idle;
    double elapsed=0;float cycleSpeed=1,payoutScale=1,breakScale=1;int outcome=0;bool paid=false;
};
inline Box bloodMachineBody(Vector3 at){return {{at.x-.55f,-.2f,at.z-.55f},{at.x+.55f,2.1f,at.z+.55f}};}
struct BloodReward {
    Vector3 origin{};int room=-1,item=0,subtype=1,ordinal=0;uint32_t seed=1;
};
struct MachineCollectible {
    Vector3 position{};int room=-1,item=119,charge=0;float age=0;bool contactBlocked=false;
};
}
