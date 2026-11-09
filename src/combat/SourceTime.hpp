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
// Review controllers apply AI at the beginning of each30Hz interval, then
// interpolate its realized velocity. Legacy controllers retain end scheduling.
inline int sourceControllerUpdates(float &clock,float dt,bool atStart) {
    int count=atStart&&clock<=1e-7f?1:0;
    clock+=dt;
    while(clock+1e-6f>=1.f/30) {
        clock=std::max(0.f,clock-1.f/30);
        if(!atStart||clock>1e-7f)++count;
    }
    return count;
}
inline int advanceSourceFrames(float &fraction,float timeScale) {
    fraction+=timeScale;
    const int frames=int(std::floor(fraction+1e-6f));
    fraction=std::max(0.f,fraction-float(frames));
    return frames;
}
}
