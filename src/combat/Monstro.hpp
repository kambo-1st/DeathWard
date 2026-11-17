#pragma once
#include "core/Types.hpp"
#include <stdexcept>

namespace dw {
inline int sourceMonstroAction(uint32_t word,int subtype=0) {
    const int action=int(word%3);
    return subtype==2&&action==2?1:action;
}
// Forces before native base physics, supplied ordinary target, timeScale1.
// 45bf03 common friction; 45d015 small hop; 45d625 large jump.
inline Vector3 sourceMonstroForce(Vector3 velocity,Vector3 delta,bool large) {
    delta=horizontal(delta);const float size=length(delta);
    const auto normal=size>0?mul(delta,1/size):Vector3{};
    const auto force=large?add(mul(delta,.006f),mul(normal,.3f)):mul(normal,1.2f);
    return add(horizontal(velocity),mul(force,1/.9f));
}
inline float sourceMonstroFriction(bool moving,bool large=false) {
    return moving?(large?.9f:.9f*.9f):.9f*.8f;
}
// D13a overrides. Source numbers remain above; accepted spatial adapters are
// applied by the Simulation. Enabled is a staged floor-generation policy.
struct MonstroTuning {
    bool enabled=true;
    float health=1,movement=1,shotSpeed=1;
    bool operator==(const MonstroTuning &) const = default;
    bool custom() const { return !enabled||health!=1||movement!=1||shotSpeed!=1; }
    void validate() const {
        for(float v:{health,movement,shotSpeed})if(!std::isfinite(v)||v<.1f||v>3)
            throw std::invalid_argument("Monstro multipliers must be 10-300%");
    }
};
enum class MonstroAction { Select, Walk, Spit, JumpUp, JumpDown };
struct MonstroShot {
    Vector3 planar{};
    float fallingSpeed=0,fallingAcceleration=.32f,size=1;
};
inline float sourceBossShotUnit(uint32_t word) { return float(word)*0x1p-32f; }
inline MonstroShot sourceBossShot(Vector3 planar,uint32_t fall,uint32_t sizeBit,uint32_t jitter,float trajectory=0) {
    return {planar,5-sourceBossShotUnit(fall)*30*.8f-trajectory,.32f+trajectory*.1f,
        .9f+.4f*float(sizeBit&1)+sourceBossShotUnit(jitter)*.05f};
}
struct MonstroRuntime {
    MonstroAction action=MonstroAction::Select;
    int frame=0;
    float clock=0;
    Vector3 momentum{},goal{};
    bool hasGoal=false,intangible=false,initialized=false,fired=false;
    Vector3 shotOrigin{};
    float shotSpeed=1; // Snapshotted when a volley is selected, including queued recovery.
    std::vector<MonstroShot> pendingShots;
};
} // namespace dw
