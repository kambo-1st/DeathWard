#pragma once
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace dw {
// Installed 1.7.9b ordinary damage cache and tear-size curve. The inverse
// below adapts the editable DW base; it does not replace other item caches.
inline float sourceOrdinaryDamage(float raw) {
    return 3.5f*std::sqrt(std::max(0.f,1.f+1.2f*raw));
}
inline float sourceOrdinaryTearScale(float damage) {
    return .23f*std::sqrt(std::max(0.f,damage))+(.55f+.01f*damage);
}
inline float cricketHeadDamage(float base,std::size_t copies,float strength=1) {
    if(!std::isfinite(base)||base<0||!std::isfinite(strength)||strength<0||strength>2)
        throw std::invalid_argument("Invalid Cricket's Head damage or strength");
    if(!copies||strength==0)return base;
    const float ratio=base/3.5f;
    const float raw=(ratio*ratio-1.f)/1.2f;
    // Copies stack the raw +0.5. The 1.5 multiplier is a presence gate once.
    return sourceOrdinaryDamage(raw+.5f*float(copies)*strength)*(1.f+.5f*strength);
}
}
