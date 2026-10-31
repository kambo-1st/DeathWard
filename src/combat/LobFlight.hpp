#pragma once
#include <cmath>

namespace dw {
// Native30Hz recurrence in upward world coordinates: v'=q*v-g/30;
// y'=y+v'/30. Fractional interpolation composes to these exact endpoints.
// This interpolation is a3D adaptation, not the native time-scale helper.
inline float advanceLobHeight(float &velocity,float gravity,float retention,float dt) {
    const double q=retention,h=double(dt)*30;
    if(q==1) {
        // Limit of the geometric recurrence with no vertical damping. Avoid
        // dividing by zero for externally configured retention=1.
        const double old=velocity,acceleration=double(gravity)/30;
        velocity=float(old-acceleration*h);
        return float((old*h-acceleration*h*(h+1)/2)/30);
    }
    const double decay=std::pow(q,h),terminal=-double(gravity)/(30*(1-q));
    const double old=velocity;
    const double delta=(q*(1-decay)/(1-q)*(old-terminal)+terminal*h)/30;
    velocity=float(decay*old+terminal*(1-decay));
    return float(delta);
}
} // namespace dw
