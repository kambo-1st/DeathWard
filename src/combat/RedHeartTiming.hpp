#pragma once
#include <algorithm>
#include <cmath>

namespace dw {
// Installed Repentance 1.7.9b full/half/double/soul-heart ANM2 metadata and
// executed pickup appearance gate. Seconds use DW's explicit 30 Hz adapter;
// the complete native spawn/scheduler/collision wrapper is not reproduced.
inline bool sourcePickupAppearanceGate(bool appearance,bool playing,bool dropEvent,bool previous) {
    return previous||(appearance&&(!playing||dropEvent));
}
struct RedHeartTiming {
    enum class Phase {Idle,Appear,Collect,Gone};
    static constexpr int AppearFrames=33,DropFrame=25,CollectFrames=12;
    Phase phase=Phase::Idle;
    float frame=0,appearanceSpeed=1;
    double remainder=0;
    bool collision=true;
    void appear(float speed) {
        phase=Phase::Appear;frame=0;remainder=0;collision=false;
        appearanceSpeed=std::isfinite(speed)?std::clamp(speed,.25f,4.f):1.f;
    }
    bool collectible() const {return collision&&phase!=Phase::Collect&&phase!=Phase::Gone;}
    void collect() {phase=Phase::Collect;frame=0;remainder=0;collision=false;}
    void tick() {
        if(phase==Phase::Appear) {
            const float next=frame+appearanceSpeed;
            const bool playing=next<AppearFrames;
            const bool drop=frame<DropFrame&&next>=DropFrame;
            collision=sourcePickupAppearanceGate(true,playing,drop,collision);
            frame=next;
            if(!playing){phase=Phase::Idle;frame=0;}
        } else if(phase==Phase::Collect) {
            if(++frame>=CollectFrames)phase=Phase::Gone;
        }
    }
    void advance(float dt) {
        if(!(dt>0)||!std::isfinite(dt))return;
        if(phase==Phase::Idle||phase==Phase::Gone){remainder=0;return;}
        remainder+=double(dt)*30;
        while(remainder+1e-7>=1) {
            remainder=std::max(0.,remainder-1);tick();
            if(phase==Phase::Idle||phase==Phase::Gone){remainder=0;break;}
        }
    }
};
} // namespace dw
