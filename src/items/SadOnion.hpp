#pragma once
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace dw {
// Original ordinary 1.7.9b fire-delay curve; source evidence is kept separately
// from the inverse adapter for DeathWard's accepted editable base shots/second.
inline float sourceOrdinaryTears(float tearStat) {
    const float delay=std::max(5.f,16.f-6.f*std::sqrt(std::max(0.f,1.f+1.3f*tearStat))-6.f*std::min(tearStat,0.f));
    return 30.f/(delay+1.f);
}
inline float ordinaryItemTears(float baseRate,float contribution) {
    if(!std::isfinite(baseRate)||baseRate<0||!std::isfinite(contribution)||contribution<0)
        throw std::invalid_argument("Invalid ordinary Tears base or contribution");
    // Preserve disabled fire and custom rates beyond the ordinary source cap.
    // No-owned-item evaluation must leave the accepted base bit-for-bit intact.
    if(contribution==0||baseRate==0||baseRate>=5)return baseRate;
    const float delay=30.f/baseRate-1.f;
    float raw;
    if(baseRate>=30.f/11.f) {
        const float root=(16.f-delay)/6.f;raw=(root*root-1.f)/1.3f;
    } else if(delay>=16.f+6.f/1.3f)raw=(16.f-delay)/6.f;
    else {
        const float q=1.3f*(delay-16.f)/6.f-1.f;
        const float root=(-1.3f+std::sqrt(1.69f-4.f*q))*.5f;
        raw=(root*root-1.f)/1.3f;
    }
    return sourceOrdinaryTears(raw+contribution);
}
inline float sadOnionTears(float baseRate,std::size_t copies,float strength=1) {
    if(!std::isfinite(strength)||strength<0||strength>2)throw std::invalid_argument("Invalid Sad Onion strength");
    return ordinaryItemTears(baseRate,.7f*float(copies)*strength);
}
}
