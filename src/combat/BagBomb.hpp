#pragma once
#include "core/Types.hpp"
#include <stdexcept>

namespace dw {
// Ordinary 4.3/4.4, grounded, no item/status modifiers. Native source coordinates
// and 30 Hz steps; preserved whole-Update traces live in troll-bombs/.
struct BagBombMotion {
    int variant=3, countdown=0, ticks=0;
    Vector3 position{}, velocity{};
    float friction=1;
    static int fuse(uint32_t seed) {
        if(!seed)throw std::invalid_argument("Bag bomb requires a nonzero seed");
        seed^=seed>>4;seed^=seed<<3;seed^=seed>>17;
        return 45+int(seed%30);
    }
    void move() {
        velocity=mul(velocity,friction);
        position=add(position,velocity);
        velocity=mul(velocity,.95f);
        if(dot(velocity,velocity)<1)velocity=mul(velocity,.5f);
    }
    void steer(Vector3 target,Vector3 targetVelocity) {
        if(variant==4) {
            auto delta=sub(add(target,mul(targetVelocity,5)),position);
            const float square=dot(delta,delta);
            if(square<72900) {
                const float distance=std::sqrt(square);
                if(distance>0.00001f)delta=mul(delta,1/distance);
                velocity=add(velocity,mul(delta,1.5f));
            }
            velocity=mul(velocity,.8f);
        }
        ++ticks;friction=variant==4&&ticks<20?.8f:1.f;
    }
};
struct BagBombRuntime {
    // Fixed D04 player-relative motion; blasts use the accepted D10 scale.
    static constexpr float MotionScale=4.8f/(4.414238452911377f*60.f);
    BagBombMotion motion;
    uint32_t seed=1;
    double elapsed=0;
    float movement=1;
    int grace=4;
    bool blastPending=false;
};
}
