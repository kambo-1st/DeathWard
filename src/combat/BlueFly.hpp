#pragma once
#include "core/Types.hpp"

namespace dw {
// Ordinary 3.43 familiar, empty inventory. Native coordinates per invocation.
inline int sourceRottenFlyDeficit(int rotten,int owned) {return std::max(0,2*rotten-owned);}
inline float sourceBlueFlyDamage(float playerDamage) {return playerDamage+playerDamage;}
inline bool sourceBlueFlyInstakill(MonsterId id) {
    // Native contact6089cf/608ab2. Type14 variant2 is explicitly excluded.
    return id.type==13||(id.type==14&&id.variant!=2)||id.type==18||id.type==80||
        id.type==222||id.type==256||id.type==296||id.type==281||id.type==868;
}
inline Vector3 sourceBlueFlyMotion(Vector3 velocity,Vector3 delta) {
    delta=horizontal(delta);velocity=horizontal(velocity);
    const float size=std::sqrt(delta.x*delta.x+delta.z*delta.z);
    const float scale=size<.1f?0:std::min(size*.15f,2.f)/size;
    return mul(add(velocity,mul(delta,scale)),.8f);
}
inline float sourceBlueFlyOrbitAngleInput(float phase,uint32_t frame,int parity=0) {
    return phase-(float(frame)+float(parity)*.5f)*.045f*Pi*.5f;
}
inline Vector3 sourceBlueFlyOrbit(float phase,uint32_t frame,int parity=0) {
    const float angle=std::fmod(sourceBlueFlyOrbitAngleInput(phase,frame,parity),2*Pi)+.5f;
    return {std::cos(angle)*35,0,std::sin(angle)*30};
}
inline float sourceBlueFlyTargetScore(float flyDistance,float ownerDistance,float hp) {
    return std::max(800.f-flyDistance,0.f)+std::max(400.f-ownerDistance,0.f)*3+
        (400.f-std::min(hp,400.f));
}
inline bool sourceBlueFlyPoll(uint32_t frame,uint32_t seed,uint32_t rng) {
    return rng%3==0&&int32_t(frame+seed)%13==0;
}
} // namespace dw
