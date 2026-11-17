#pragma once
#include "core/Types.hpp"
#include <cstdint>
#include <stdexcept>
namespace dw {
struct DukeTuning {
    bool enabled=false; // Staged opening-floor choice; existing presets keep Monstro.
    float health=1,movement=1,flySpeed=1;
    bool operator==(const DukeTuning &) const = default;
    bool custom() const {return enabled||health!=1||movement!=1||flySpeed!=1;}
    void validate() const {
        for(float v:{health,movement,flySpeed})if(!std::isfinite(v)||v<.1f||v>3)
            throw std::invalid_argument("Duke multipliers must be 10-300%");
    }
};
struct DukeBirth {
    int type=18;
    Vector3 position{};
    uint32_t seed=0;
    bool cohort=false,live=false;
    float healthScale=1,visualScale=1;
};
struct DukeRuntime {
    int state=0,frame=0;
    float clock=0,friction=1;
    Vector3 position{},momentum{};
    uint32_t initSeed=0;
    bool initialized=false,deathPending=false,deathPrepared=false,paused=false,pendingPhysics=false;
    std::vector<DukeBirth> pending;
};
struct DukeTick {bool release=false;int sound=0;};
inline float sourceDukeUnit(uint32_t word){return float(word)*0x1p-32f;}
inline Vector3 sourceDukeRelease(Vector3 delta,Vector3 velocity,float friction=1,float timeScale=1) {
    const float squared=delta.x*delta.x+delta.z*delta.z;
    if(squared<=.01f||friction==0)return velocity;
    const float factor=18/std::sqrt(squared);
    velocity.x+=(delta.x*factor)*timeScale/friction;
    velocity.z+=(delta.z*factor)*timeScale/friction;
    return velocity;
}
// Ordinary67.0.0 controller, supplied room/cohort counts and global MT stream.
// Graphics requests are omitted, but their original RNG draws are retained.
template<class Next>
DukeTick sourceDukeTick(DukeRuntime &r,int total,int owned,Next next,bool dead=false,
                       Vector3 minimum={},Vector3 maximum={640,0,560},float radius=35) {
    DukeTick out;
    r.position.x=std::clamp(r.position.x,minimum.x,maximum.x);
    r.position.z=std::clamp(r.position.z,minimum.z+40,maximum.z);
    if(r.position.x==maximum.x)r.momentum.x=-1;
    if(r.position.x==minimum.x)r.momentum.x=1;
    if(r.position.z==maximum.z)r.momentum.z=-1;
    if(r.position.z==minimum.z+40)r.momentum.z=1;
    r.friction*=.8f;
    if(r.friction!=0) {
        r.momentum.x+=(r.momentum.x>0?.4f:-.4f)/r.friction;
        r.momentum.z+=(r.momentum.z>=.1f?.4f:-.4f)/r.friction;
    }
    auto birth=[&](int type,Vector3 at,bool cohort,bool live,float hp=1,float visual=1) {
        r.pending.push_back({type,at,uint32_t(next()),cohort,live,hp,visual});
    };
    if(r.state==0)r.state=4;
    else if(r.state==4) {
        if(uint32_t(next())%40==0&&total+owned<9)r.state=13;
        else if(uint32_t(next())%70==0&&total-owned<10)r.state=14;
        else if(uint32_t(next())%45==0&&owned>4&&total-owned<5)r.state=8;
        else next(); // Fourth draw is consumed; its release branch excludes ordinary subtype0.
        r.frame=0;
    } else if(r.state==13&&r.frame==20) {
        out.sound=108;next();next(); // Two visual poof InitSeeds precede live offspring.
        birth(18,add(r.position,{0,0,20}),true,true);
        birth(18,add(r.position,{10,0,20}),true,true);
        birth(18,add(r.position,{-10,0,20}),true,true);
        const int cosmetics=1+int(uint32_t(next())%5);
        for(int i=0;i<cosmetics;++i){next();next();next();next();}
    } else if(r.state==14&&r.frame==18) {
        out.sound=106;birth(18,add(r.position,{0,0,20}),false,true,1.8f,1.25f);
    } else if(r.state==8&&r.frame==17) {out.sound=112;out.release=true;}
    ++r.frame;if(r.frame>=40)r.state=4;
    if(dead&&!r.deathPrepared) {
        r.deathPrepared=true;
        int cosmetics=0;uint32_t limit=uint32_t(next())%10+5;
        while(uint32_t(cosmetics)<limit) {next();next();next();++cosmetics;limit=uint32_t(next())%10+5;}
        if(!r.initSeed)throw std::invalid_argument("Duke death requires a resolved nonzero InitSeed");
        uint32_t local=r.initSeed;
        for(int i=0;i<6;++i) {
            const float spread=(sourceDukeUnit(uint32_t(next()))*.8f)*radius;
            float angle=sourceDukeUnit(uint32_t(next()))*Pi;angle+=angle;
            const Vector3 at{float(std::cos(double(angle)))*spread+r.position.x,0,float(std::sin(double(angle)))*spread+r.position.z};
            const uint32_t seed=uint32_t(next());local^=local>>5;local^=local<<9;local^=local>>7;
            r.pending.push_back({(local&1)?13:18,at,seed,false,false,1,1});
        }
    }
    return out;
}
inline void sourceDukePhysics(DukeRuntime &r) {
    r.momentum=mul(r.momentum,r.friction);r.position=add(r.position,r.momentum);r.friction=1;
}
struct DukeChildRuntime {uint32_t initSeed=0;EntityId parent=0;bool cohort=false;float visualScale=1;};
} // namespace dw
