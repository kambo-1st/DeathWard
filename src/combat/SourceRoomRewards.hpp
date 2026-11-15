#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace dw {
// Repentance1.7.9b room reward/pickup RNG shift triplet at a08c44.
// Supplied nonzero seeds are required. Native room/floor seed mapping is separate.
struct SourceAwardRng {
    uint32_t state;
    uint32_t next(){if(!state)throw std::invalid_argument("Source award RNG requires a nonzero seed");state^=state>>5;state^=state<<9;state^=state>>7;return state;}
    uint32_t bounded(uint32_t maximum){return next()%maximum;}
    float unit(){return float(next())*0x1.fffffcp-33f;}
};
// Entire ordinary empty-inventory selector at7b82b0. All represented source
// items/trinkets are absent; this is not the complete modified award system.
inline int sourceOrdinaryRoomAward(SourceAwardRng &rng,float luck=0,bool preventNone=false) {
    float score=rng.unit();score+=rng.unit()*std::clamp(luck,0.f,10.f)*.1f;
    if(preventNone&&score<=.22f)score=std::clamp(score/.22f,0.f,1.f)*.7799f+.2201f;
    if(score<=.22f)return 0;
    int variant;
    if(score<.3f)variant=rng.bounded(3)==0?300:(rng.next()&1)?70:350;
    else if(score<.45f)variant=20;
    else if(score<.6f)variant=10;
    else if(score<.8f)variant=30;
    else if(score<.95f)variant=40;
    else variant=50;
    rng.bounded(15); // Source consumes this even without the battery trinket.
    if(rng.bounded(50)==0)variant=69;
    return variant;
}
// These are explicit achievement-gate inputs, not a complete save/unlock profile.
struct SourcePickupGates {
    bool rotten=false,scared=false,halfSoul=false,bone=false,goldenHeart=false;
    bool sticky=false,lucky=false,goldenCoin=false,chargedKey=false,goldenBomb=false;
    static SourcePickupGates representedEnabled(){return {true,true,true,true,true,true,true,true,true,true};}
};
// Ordinary native coin values; special coin behavior is outside this delivery.
inline int sourceOrdinaryCoinValue(int subtype) {
    switch(subtype){case 1:return 1;case 2:return 5;case 3:return 10;case 4:return 2;default:return 0;}
}
inline int sourceOrdinaryKeyValue(int subtype) { return subtype==1?1:subtype==3?2:0; }
inline int sourceOrdinaryBombValue(int subtype) { return subtype==1?1:subtype==2?2:0; }
struct SourcePickupChoice {int variant=0,subtype=0;bool resolved=false;};
// Native6b48b0 scoped ordinary room/type1, ordinary Isaac, empty inventory,
// Normal mode, input subtype0. No world actor/collection acceptance is implied.
inline SourcePickupChoice sourceOrdinaryPickup(uint32_t seed,int variant,SourcePickupGates gates={}) {
    SourceAwardRng rng{seed};int subtype=1;
    if(variant==10) {
        if(rng.bounded(2)==0)subtype=2;
        if(rng.bounded(20)==0)subtype=5;
        if(rng.bounded(50)==0&&gates.rotten)subtype=12;
        if(rng.bounded(100)==0&&gates.scared)subtype=9;
        if(rng.bounded(100)==0)subtype=10;
        if(rng.bounded(50)==0)subtype=4;
        if(rng.bounded(10)==0) {
            subtype=3;
            if(rng.bounded(4)==0&&gates.halfSoul)subtype=8;
            if(rng.bounded(20)==0&&gates.bone)subtype=11;
            if(rng.bounded(20)==0)subtype=6;
            rng.bounded(5); // Forgotten/Soul player-type override is absent here.
        }
        if(rng.bounded(160)==0&&gates.goldenHeart)subtype=7;
    } else if(variant==20) {
        if(rng.bounded(20)==0) {
            subtype=2;
            if(rng.bounded(20)==0&&gates.sticky)subtype=6;
        }
        if(rng.bounded(100)==0)subtype=3;
        else if(subtype==1&&rng.bounded(100)==0&&gates.lucky)subtype=5;
        if(rng.bounded(200)==0&&gates.goldenCoin)subtype=7;
    } else if(variant==30) {
        rng.next(); // Native passes Next() as the copied weighted-picker seed.
        const auto pick=rng.bounded(51);
        subtype=pick<49?1:pick==49?2:gates.chargedKey?4:1;
    } else if(variant==40) {
        // Native 6b5caf..6b5d52. Preserve all four draws and special outcomes;
        // ordinary inventory pickups admit only single1/double2 below.
        if(rng.bounded(7)==0)subtype=2;
        if(rng.bounded(100)==0&&gates.goldenBomb)subtype=4;
        if(rng.bounded(50)==0)subtype=subtype==4?6:5;
        if(rng.bounded(10)==0)subtype=subtype==4?6:3;
    } else return {variant,0}; // Unresolved families are not rerolled or substituted.
    return {variant,subtype,true};
}
} // namespace dw
