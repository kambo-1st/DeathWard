#pragma once
#include "combat/BrotherBobby.hpp"
namespace dw {
struct HaloOfFliesTuning {
    float orbitSpeed=1, orbitRadius=1, contactRadius=1;
    bool operator==(const HaloOfFliesTuning &) const = default;
    bool custom() const {return *this!=HaloOfFliesTuning{};}
    void validate() const {
        for(float v:{orbitSpeed,orbitRadius,contactRadius})
            if(!std::isfinite(v)||v<.25f||v>2)throw std::runtime_error("Halo multipliers must be 25-200%");
    }
};
inline constexpr float HaloSourceRadiusX=25,HaloSourceRadiusZ=20,HaloSourceContactRadius=6;
inline constexpr float HaloSourceSpeed=.045f,HaloSourceOffset=1.5f;
inline constexpr float HaloSpace=BobbySpace; // Accepted shooting-space adapter.
inline unsigned sourceHaloCount(unsigned copies) {return copies>=5?10:copies*2;}
inline float sourceHaloAngle(float phase,uint32_t frame,int parity=0) {
    return phase-(float(frame)+float(parity)*.5f)*HaloSourceSpeed*Pi*.5f;
}
inline Vector3 sourceHaloOffset(float phase) {
    const float angle=std::fmod(phase,2*Pi)+HaloSourceOffset;
    return {std::cos(angle)*HaloSourceRadiusX,0,std::sin(angle)*HaloSourceRadiusZ};
}
}
