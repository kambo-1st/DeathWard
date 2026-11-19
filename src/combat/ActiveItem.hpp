#pragma once
#include "content/ContentId.hpp"
#include <stdexcept>
#include <cmath>

namespace dw {
inline constexpr int YumHeartCharges=4;
inline const ItemKey YumHeartKey{"isaac",ItemKind::Collectible,45};
inline constexpr int BookOfShadowsCharges=3;
inline const ItemKey BookOfShadowsKey{"isaac",ItemKind::Collectible,58};
inline const ItemKey IvBagKey{"isaac",ItemKind::Collectible,135};
inline bool supportedActive(const ItemKey &item){return item==YumHeartKey||item==BookOfShadowsKey||item==IvBagKey;}
inline int activeCapacity(const ItemKey &item) {
    return item==YumHeartKey?YumHeartCharges:item==BookOfShadowsKey?BookOfShadowsCharges:0;
}
inline const char *activeName(const ItemKey &item) {
    return item==IvBagKey?"IV BAG":item==BookOfShadowsKey?"BOOK OF SHADOWS":"YUM HEART";
}
struct ActiveItemState {
    ItemKey item=YumHeartKey;
    int charge=YumHeartCharges;
    bool operator==(const ActiveItemState &) const = default;
    void validate() const {
        if(!supportedActive(item)||charge<0||charge>activeCapacity(item))
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
struct BookOfShadowsTuning {
    float duration=10; // Seconds of active gameplay; source cooldown 300 / 30 Hz.
    int recharge=1;
    bool operator==(const BookOfShadowsTuning &) const = default;
    bool custom() const {return *this!=BookOfShadowsTuning{};}
    void validate() const {
        if(!std::isfinite(duration)||duration<1||duration>30||recharge<0||recharge>3)
            throw std::runtime_error("Invalid Book of Shadows duration or recharge");
    }
};
}
