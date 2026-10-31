#pragma once
#include <algorithm>
#include <cmath>

namespace dw {
// Repentance 1.7.9b helper65c960/base Entity update. This is a rational
// time-scale adjustment, not pow(retention,timeScale).
inline float sourceTimeRetention(float retention,float timeScale) {
    if(timeScale==1)return retention;
    return retention/(retention+timeScale-retention*timeScale);
}
inline int advanceSourceFrames(float &fraction,float timeScale) {
    fraction+=timeScale;
    const int frames=int(std::floor(fraction+1e-6f));
    fraction=std::max(0.f,fraction-float(frames));
    return frames;
}
}
