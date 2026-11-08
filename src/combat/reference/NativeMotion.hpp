#pragma once
#include "core/Types.hpp"
#include <stdexcept>

namespace dw::native_motion {
// Native coordinates per invocation. No world-unit or accepted-feel calibration.
// Ordinary grounded empty-build player only: installed 1.7.9b, 74211c..7428ee.
inline Vector3 playerSteering(Vector3 velocity,Vector3 input,float speed=1) {
    if(!std::isfinite(speed)||speed<=0)throw std::invalid_argument("native reference requires positive Speed");
    input=horizontal(input);velocity=horizontal(velocity);
    if(length(input)>1)input=mul(input,1/length(input));
    const auto drive=mul(input,speed*.25f+.75f);
    if(drive.x!=0||drive.z!=0) {
        const float along=velocity.x*drive.x+velocity.z*drive.z;
        const auto parallel=mul(drive,along);
        velocity=add(mul(sub(velocity,parallel),std::sqrt(.8f)),parallel);
    }
    const float along=velocity.x*drive.x+velocity.z*drive.z;
    const float acceleration=(std::max(0.f,-.2f*along)/speed+3.f)*.4f;
    return mul(add(velocity,mul(mul(drive,.5f),acceleration)),std::sqrt(.775f));
}
// Native base physics 686406..686497: friction first, move incoming velocity,
// reset current friction to base. Steering prepares the following invocation.
struct Body {
    Vector3 position{},velocity{};
    float friction=1,baseFriction=1,timeScale=1;
    void integrate() {
        const float effective=timeScale==1?friction:friction/(friction+timeScale-friction*timeScale);
        velocity=mul(velocity,effective);
        friction=baseFriction;
        position=add(position,mul(velocity,timeScale));
    }
    void playerStep(Vector3 input,float speed=1) {integrate();velocity=playerSteering(velocity,input,speed);}
};
// Explicit opt-in adapter state. The caller owns its documented spatial
// conversion; the native recurrence itself has no calibrated speed constant.
struct PlayerAdapter {
    explicit PlayerAdapter(float scale):worldScale(scale) {
        if(!std::isfinite(scale)||scale<=0)throw std::invalid_argument("native reference requires positive spatial scale");
    }
    Body body;
    float clock=0;
    float worldScale;
    void reset(){body={};clock=0;}
};
// Selected ordinary path arithmetic only, 7a46db..7a47f5. Routing and its
// destination are supplied boundaries; this is not native pathfinding.
enum class Path { Moving, Arrived, Blocked };
inline void gaperSteering(Body &body,Vector3 delta,float force,Path route=Path::Moving) {
    if(route==Path::Blocked){body.friction*=.85f;return;}
    const float size=length(horizontal(delta));
    if(size<=1){body.friction*=.5f;return;}
    body.friction*=.7f;
    if(body.friction!=0)body.velocity=add(body.velocity,mul(unit(horizontal(delta)),std::min(size*.1f,2.f)*force*body.timeScale/body.friction));
}
// Selected Spider movement arithmetic only, 518508..518578, then5183a5..5183cd.
// Destination, idle/clear timing and RNG are supplied, not accepted by this core.
inline void spiderSteering(Body &body,Vector3 delta,bool hasTarget) {
    if(hasTarget&&length(horizontal(delta))>0&&body.friction!=0)
        body.velocity=add(body.velocity,mul(unit(horizontal(delta)),6*body.timeScale/body.friction));
    body.friction*=.6f;
}
}
