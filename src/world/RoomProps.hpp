#pragma once
#include "combat/SourceRoomRewards.hpp"
namespace dw {
struct RoomPropsTuning {
    int layouts=1; // 0 unchanged legacy layouts, 1 selected source records, 2 labelled test arrangement.
    int fireDamageHalfHearts=1;
    bool rewards=true;
    bool operator==(const RoomPropsTuning &) const = default;
    bool custom() const {return *this!=RoomPropsTuning{};}
    void validate() const {if(layouts<0||layouts>2||fireDamageHalfHearts<0||fireDamageHalfHearts>6)throw std::invalid_argument("Prop layouts must be0-2; fire damage0-6 half hearts");}
};
struct PropRewardState {
    bool resolved=false,delivered=false;
    int variant=0,subtype=0;
    uint32_t seed=0;
    float heartAppearanceSpeed=1;
};
inline uint32_t propRandom(uint32_t &s,int a,int b,int c){if(!s)throw std::invalid_argument("Prop seed must be nonzero");s^=s>>a;s^=s<<b;s^=s>>c;return s;}
inline SourcePickupChoice ordinaryPropDrop(uint32_t seed,bool fire,uint32_t &pickupSeed) {
    const int a=1,b=fire?11:5,c=fire?6:16;
    const auto next=[&]{return propRandom(seed,a,b,c);};
    const auto unit=[&]{return float(next())*0x1.fffffcp-33f;};
    pickupSeed=0;if(unit()>=(fire?.25f:.1f))return {};
    if(!fire)next(); // Native consumes the gated trinket roll even when that gate is off.
    const int variant=unit()<.25f?10:20;pickupSeed=next();
    return sourceOrdinaryPickup(pickupSeed,variant,{});
}
}
