#pragma once
#include "content/ContentId.hpp"
#include <stdexcept>

namespace dw {
inline constexpr int YumHeartCharges=4;
inline const ItemKey YumHeartKey{"isaac",ItemKind::Collectible,45};
struct ActiveItemState {
    ItemKey item=YumHeartKey;
    int charge=YumHeartCharges;
    bool operator==(const ActiveItemState &) const = default;
    void validate() const {
        if(item!=YumHeartKey||charge<0||charge>YumHeartCharges)
            throw std::runtime_error("Invalid active item or charge");
    }
};
struct YumHeartTuning {
    int healing=2, recharge=1, binding=0; // Half-hearts, charges per clear, C/X/Z.
    bool operator==(const YumHeartTuning &) const = default;
    bool custom() const {return *this!=YumHeartTuning{};}
    void validate() const {
        if(healing<1||healing>6||recharge<0||recharge>4||binding<0||binding>2)
            throw std::runtime_error("Invalid Yum Heart healing, recharge or binding");
    }
    const char *keyName() const {return binding==1?"X":binding==2?"Z":"C";}
};
}
