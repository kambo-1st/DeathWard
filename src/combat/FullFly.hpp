#pragma once
#include "core/Types.hpp"
#include <stdexcept>

namespace dw {
struct FullFlyTuning {
    float movement=1,shotSpeed=1;
    bool custom() const{return movement!=1||shotSpeed!=1;}
    bool operator==(const FullFlyTuning&) const=default;
    void validate() const {
        if(!std::isfinite(movement)||movement<.1f||movement>2||!std::isfinite(shotSpeed)||shotSpeed<.1f||shotSpeed>2)
            throw std::runtime_error("Full Fly movement and death shots must be 10-200%");
    }
};
// Installed 249.0 ordinary pursuit. Source planar units; Skatole removes
// the diagonal transform and doubled force, without morphing Full Fly.
inline Vector3 fullFlyPursuit(Vector3 delta,bool skatole=false) {
    if(!skatole)delta={delta.x+delta.z,0,delta.z-delta.x};
    delta.z*=.5f;
    const float d=length(delta);
    return d>25?mul(delta,std::min((d-25)*.08f,1.2f)*(skatole?1:2)/d):Vector3{};
}
inline Vector3 fullFlyRecoil(Vector3 &recoil) {
    if(dot(recoil,recoil)<=1){recoil={};return {};}
    const auto impulse=recoil;recoil=mul(recoil,.9f);return impulse;
}
inline Vector3 fullFlyDeathVelocity(int index,float scale,float multiplier=1) {
    const float angle=float(index+1)*2*Pi/6;
    return {std::cos(angle)*8*scale*30*multiplier,0,std::sin(angle)*8*scale*30*multiplier};
}
} // namespace dw
