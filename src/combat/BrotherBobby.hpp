#pragma once
#include "core/Types.hpp"
#include <stdexcept>
namespace dw {
struct BrotherBobbyTuning {
    float movement=1, interval=1, damage=1, shotSpeed=1;
    bool operator==(const BrotherBobbyTuning &) const = default;
    bool custom() const {return *this!=BrotherBobbyTuning{};}
    void validate() const {
        for(float v:{movement,interval,damage,shotSpeed})
            if(!std::isfinite(v)||v<.25f||v>2)throw std::runtime_error("Brother Bobby multipliers must be 25-200%");
    }
};
// Ordinary FollowParent tail 5f4dc1..5f4e97; supplied parent, no trinkets.
// Free physics applies the .8 retention set by this routine.
inline Vector3 sourceBobbyFollow(Vector3 velocity,Vector3 awayFromParent) {
    const auto delta=horizontal(awayFromParent);const float d=length(delta);
    if(d>20)velocity=mul(delta,-.2f*(d-20)*(d-20)/(d*d));
    return mul(horizontal(velocity),.8f);
}
inline constexpr float BobbySourceDamage=3.5f,BobbySourceInterval=16.f/30;
// Accepted shooting-space adapter, not independently accepted native geometry.
inline constexpr float BobbySpace=11.f/260, BobbyLaunch=10*BobbySpace*30;
}
