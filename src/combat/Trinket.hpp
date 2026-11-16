#pragma once
#include "content/ContentId.hpp"
#include "combat/RedHeartTiming.hpp"
#include <stdexcept>

namespace dw {
inline const ItemKey CancerKey{"isaac",ItemKind::Trinket,39};
struct TrinketTuning {
    float cancerStrength=1; // Source +1 tears/second, after ordinary Tears modifiers.
    bool clearRewards=true; // Future ordinary first clears; bounded Cancer-only pool.
    int binding=0; // U/Y; neither conflicts with active, aim, camera or dodge controls.
    bool operator==(const TrinketTuning &) const = default;
    bool custom() const {return *this!=TrinketTuning{};}
    void validate() const {
        if(!std::isfinite(cancerStrength)||cancerStrength<0||cancerStrength>2||binding<0||binding>1)
            throw std::runtime_error("Invalid trinket tuning");
    }
    const char *keyName() const {return binding==1?"Y":"U";}
};
inline float cancerTears(float ordinaryRate,bool held,float strength=1) {
    if(!held||strength==0||ordinaryRate<=0)return ordinaryRate;
    return ordinaryRate+strength;
}
// Installed 005.350_Trinket ANM2. Contact/drop placement uses the canyon adapter.
struct TrinketTiming {
    enum class Phase {Idle,Appear,Collect,Gone};
    static constexpr int AppearFrames=35,DropFrame=26,CollectFrames=16;
    Phase phase=Phase::Idle;
    int frame=0;
    double remainder=0;
    bool collision=true;
    void appear(){phase=Phase::Appear;frame=0;remainder=0;collision=false;}
    bool collectible() const {return collision&&phase!=Phase::Collect&&phase!=Phase::Gone;}
    void collect(){phase=Phase::Collect;frame=0;remainder=0;collision=false;}
    void advance(float dt) {
        if(!(dt>0)||!std::isfinite(dt))return;
        if(phase==Phase::Idle||phase==Phase::Gone){remainder=0;return;}
        remainder+=double(dt)*30;
        while(remainder+1e-7>=1) {
            remainder=std::max(0.,remainder-1);++frame;
            if(phase==Phase::Appear) {
                collision=sourcePickupAppearanceGate(true,frame<AppearFrames,frame==DropFrame,collision);
                if(frame>=AppearFrames){phase=Phase::Idle;frame=0;remainder=0;break;}
            } else if(frame>=CollectFrames){phase=Phase::Gone;remainder=0;break;}
        }
    }
};
}
