#pragma once
#include "core/Types.hpp"
#include "combat/RedHeartTiming.hpp"
#include <stdexcept>
namespace dw {
struct BatteryTuning {
    bool enabled=true;
    int charges=6,price=5;
    bool operator==(const BatteryTuning &)const=default;
    bool custom()const{return *this!=BatteryTuning{};}
    void validate()const{if(charges<1||charges>12||price<0||price>30)throw std::runtime_error("Invalid battery charge or price");}
};
inline int batteryChargeGain(int current,int capacity,int amount=6){return std::min(std::max(0,capacity-current),std::max(0,amount));}
struct BatteryTiming {
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
struct BatteryPickup {Vector3 position{};int room=-1,shopSlot=-1;BatteryTiming timing{};};
}
