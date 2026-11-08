#pragma once
#include "combat/SourceTime.hpp"
#include "core/Types.hpp"
#include <cstdint>
namespace dw {
// Bounded ordinary 1.7.9b flight arithmetic. Source actor clock/scale below
// are explicit review adapters, not accepted live-game timing/geometry parity.
inline constexpr float ReviewTearScale=.04f, ReviewTearStep=1.f/30;
inline constexpr float ReviewTearSpeed=10*ReviewTearScale/ReviewTearStep;
struct PlayerTearFlight {
    float height=-23.75f,previousHeight=-23.75f;
    float fallingSpeed=0,acceleration=0,clock=0;
    bool ready=false,grounded=false;
    float reviewClockScale=1; // Presentation curve normalized to explicit review reach.
};
// Native unsigned RNG conversion at 75790d..757935. Stream selection/seeding
// is separate: matching this conversion does not establish native RNG parity.
inline float sourceTearBirthFallingSpeed(uint32_t random,float fallingSpeedStat=0) {
    return float(random)*2.3283064365386963e-10f*.2f-fallingSpeedStat;
}
inline bool sourceTearGrounded(const PlayerTearFlight &flight) {return flight.height>-5.f;}
inline void sourceTearFlightFrame(PlayerTearFlight &flight,float timeScale=1) {
    flight.previousHeight=flight.height;
    const float damped=sourceTimeRetention(.9f,timeScale)*flight.fallingSpeed;
    const float acceleration=timeScale*.1f;
    flight.fallingSpeed=timeScale*flight.acceleration+(acceleration+damped);
    flight.height+=timeScale*flight.fallingSpeed;
}
// Return the part of dt during which the tear remains alive. Ground contact is
// checked BEFORE the next flight invocation, as in the source update order.
inline float advancePlayerTear(PlayerTearFlight &flight,float dt,float timeScale=1) {
    float remaining=dt,alive=0;
    constexpr float interval=1.f/30;
    while(remaining>1e-7f&&!flight.grounded) {
        if(!flight.ready) {
            if(sourceTearGrounded(flight)){flight.grounded=true;break;}
            sourceTearFlightFrame(flight,timeScale);flight.ready=true;
        }
        const float step=std::min(remaining,interval-flight.clock);
        alive+=step;remaining-=step;flight.clock+=step;
        if(flight.clock>=interval-1e-6f){flight.clock=0;flight.ready=false;}
    }
    return alive;
}

// Native previous-player velocity is per 60Hz invocation, while tear velocity
// is per 30Hz invocation. Converting both to world units/s gives factor .6.
inline Vector3 reviewTearInheritance(Vector3 previousWorldVelocity,Vector3 direction) {
    auto inherited=mul(horizontal(previousWorldVelocity),.6f);
    direction=unit(horizontal(direction));
    const float along=dot(inherited,direction);
    if(along<0)inherited=sub(inherited,mul(direction,along));
    return inherited;
}
inline float reviewTearVisualY(const PlayerTearFlight &flight,float baseY) {
    const float h=flight.ready?flight.previousHeight+(flight.height-flight.previousHeight)*flight.clock*30:flight.height;
    return std::max(.14f,baseY*std::clamp((-h-5.f)/18.75f,0.f,1.f));
}
} // namespace dw
