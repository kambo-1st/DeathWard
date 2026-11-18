#pragma once
#include "core/Types.hpp"
#include <stdexcept>

namespace dw {
struct RoundWormTuning {
    float cycleSpeed=1,shotSpeed=1;
    bool custom() const{return cycleSpeed!=1||shotSpeed!=1;}
    bool operator==(const RoundWormTuning&) const=default;
    void validate() const {
        if(!std::isfinite(cycleSpeed)||cycleSpeed<.1f||cycleSpeed>2||!std::isfinite(shotSpeed)||shotSpeed<.1f||shotSpeed>2)
            throw std::runtime_error("Round Worm cycle and shot speed must be 10-200%");
    }
};
enum class RoundWormPhase { DigIn, Hidden, DigOut };
struct RoundWormRuntime {
    RoundWormPhase phase=RoundWormPhase::DigIn;
    double clock=0,frame=0;
    float cycleSpeed=1,shotSpeed=1;
    bool initialized=false,fired=false,pending=false;
    Vector3 shotOrigin{},shotVelocity{};
    unsigned shots=0,burrows=0,relocations=0;
    float visibility() const {
        return phase==RoundWormPhase::Hidden?0:phase==RoundWormPhase::DigIn?
            std::max(.04f,1-float(frame)/17):std::clamp(float(frame)/12,.04f,1.f);
    }
};
// Bounded original-code comparisons; source coordinates, not world units.
inline Vector3 roundWormShot(Vector3 delta){return mul(unit(horizontal(delta)),10);}
inline Vector3 roundWormLead(Vector3 nativePlayerVelocity){return mul(nativePlayerVelocity,10);}
inline bool roundWormRelocation(float distanceSquared,unsigned randomWord) {
    return distanceSquared>10000&&distanceSquared<1000000&&(randomWord&1)==0;
}
} // namespace dw
