#pragma once
#include "combat/RedHeartTiming.hpp"
#include "raylib.h"
#include <array>
#include <cstdint>
#include <stdexcept>
namespace dw {
struct PillTuning {
    int purseCount=4; // New purchases only; queued drops retain their identities/count.
    float statStrength=1; // Live multiplier on consumed stat-pill contributions.
    int binding=0; // F/H or N/comma: use/drop; retained combat/camera bindings stay intact.
    bool operator==(const PillTuning &) const = default;
    bool custom() const {return *this!=PillTuning{};}
    void validate() const {
        if(purseCount<1||purseCount>8||!std::isfinite(statStrength)||statStrength<0||statStrength>2||binding<0||binding>1)
            throw std::runtime_error("Invalid pill tuning");
    }
    const char *useKey() const {return binding?"N":"F";}
    const char *dropKey() const {return binding?",":"H";}
};
// Bounded supported health/stat pool. Native pool construction/unlocks remain
// separate: DW shuffles these effects once per expedition into 13 color slots.
inline constexpr std::array<int,14> SupportedPillEffects{2,5,6,7,11,12,13,14,15,16,17,18,47,48};
inline const char *pillEffectName(int effect) {
    switch(effect){case 2:return "BALLS OF STEEL";case 5:return "FULL HEALTH";case 6:return "HEALTH DOWN";case 7:return "HEALTH UP";
    case 11:return "RANGE DOWN";case 12:return "RANGE UP";case 13:return "SPEED DOWN";case 14:return "SPEED UP";
    case 15:return "TEARS DOWN";case 16:return "TEARS UP";case 17:return "LUCK DOWN";case 18:return "LUCK UP";
    case 47:return "SHOT SPEED DOWN";case 48:return "SHOT SPEED UP";default:return "UNKNOWN PILL";}
}
inline uint32_t sourcePillRandom(uint32_t value) {value=value?value:1;value^=value>>2;value^=value<<7;value^=value>>9;return value;}
inline int sourceOrdinaryPillColor(uint32_t seed) {return int(sourcePillRandom(seed)%13)+1;}
struct PillState {
    std::array<int,13> effects{};
    std::array<bool,13> identified{};
    std::array<int,50> consumed{};
    int held=0;
    explicit PillState(uint64_t seed=0) {
        auto pool=SupportedPillEffects;uint32_t rng=uint32_t(seed^(seed>>32)^0x50494c4cU);if(!rng)rng=1;
        for(size_t i=pool.size()-1;i>0;--i){rng=sourcePillRandom(rng);std::swap(pool[i],pool[rng%(i+1)]);}
        std::copy_n(pool.begin(),13,effects.begin());
    }
    int effect(int color) const {return color>=1&&color<=13?effects[size_t(color-1)]:-1;}
    bool known(int color) const {return color>=1&&color<=13&&identified[size_t(color-1)];}
};
// Installed ordinary pill metadata: 30 Hz Appear36/Drop26/Collect15. Physical
// admission/contact/swap use the retained canyon pickup adapter.
struct PillTiming {
    enum class Phase {Idle,Appear,Collect,Gone};
    static constexpr int AppearFrames=36,DropFrame=26,CollectFrames=15;
    Phase phase=Phase::Idle;int frame=0;double remainder=0;bool collision=true;
    void appear(){phase=Phase::Appear;frame=0;remainder=0;collision=false;}
    void collect(){phase=Phase::Collect;frame=0;remainder=0;collision=false;}
    bool collectible()const{return collision&&phase!=Phase::Collect&&phase!=Phase::Gone;}
    void advance(float dt){
        if(!(dt>0)||!std::isfinite(dt)||phase==Phase::Idle||phase==Phase::Gone)return;
        remainder+=double(dt)*30;
        while(remainder+1e-7>=1){remainder=std::max(0.,remainder-1);++frame;
            if(phase==Phase::Appear){collision=sourcePickupAppearanceGate(true,frame<AppearFrames,frame==DropFrame,collision);if(frame>=AppearFrames){phase=Phase::Idle;frame=0;remainder=0;break;}}
            else if(frame>=CollectFrames){phase=Phase::Gone;remainder=0;break;}
        }
    }
};
struct PillPickup {Vector3 position{};int room=-1,color=1;uint32_t seed=1;bool contactBlocked=false;PillTiming timing{};};
struct PendingPursePill {Vector3 origin{};int room=-1,color=1,ordinal=0;uint32_t seed=1;};
}
