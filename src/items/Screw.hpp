#pragma once
#include "items/SadOnion.hpp"
namespace dw {
struct ScrewTuning {
    float tearsStrength=1,shotSpeedStrength=1;
    bool operator==(const ScrewTuning &) const = default;
    bool custom() const {return *this!=ScrewTuning{};}
    void validate() const {
        if(!std::isfinite(tearsStrength)||tearsStrength<0||tearsStrength>2||
           !std::isfinite(shotSpeedStrength)||shotSpeedStrength<0||shotSpeedStrength>2)
            throw std::invalid_argument("Screw effect strengths must be between 0 and 200%");
    }
};
inline float screwShotSpeed(float base,std::size_t copies,float strength=1) {
    return base+.2f*float(copies)*strength;
}
inline void validateBossRewardItem(int item) {
    if(item!=25&&item!=255)throw std::invalid_argument("Boss reward must be Breakfast or Screw");
}
}
