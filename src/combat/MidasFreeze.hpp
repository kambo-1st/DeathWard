#pragma once
#include <algorithm>
#include <cstdint>

namespace dw {
// Ordinary unlinked NPC control fields from 1.7.9b. Source actor eligibility,
// linked-body propagation and item duration modifiers are separate contracts.
struct ControlFreezeState {
    uint32_t flags=0;
    int freeze=0,midas=0,cooldown=0,variant=0;
};
inline bool sourceApplyMidas(ControlFreezeState &state,int duration,int type,bool boss) {
    if((state.flags&0x20000000u)||duration<=0||state.midas!=0||state.cooldown>0)return false;
    if(type==245){state.variant=1;return true;}
    if(state.flags&1u)return false;
    state.flags|=0x420;
    state.midas=state.freeze=duration;
    if(boss)state.cooldown=240;
    return true;
}
inline bool sourceApplyOrdinaryFreeze(ControlFreezeState &state,int duration,bool boss) {
    if((state.flags&0x20000001u)||duration==0||state.cooldown>0)return false;
    state.freeze=duration>0?std::min(120,state.freeze+duration):std::max(state.freeze,-duration);
    state.flags|=0x20;
    if(boss)state.cooldown=240;
    return true;
}
inline bool sourceGoldenHeartMidas(ControlFreezeState &state,int duration,int type,bool boss) {
    state.cooldown=0;
    return sourceApplyMidas(state,duration,type,boss);
}
inline void sourceStepControlFreeze(ControlFreezeState &state) {
    if(state.freeze>0&&!--state.freeze)state.flags&=~0x20u;
    if(state.midas>0&&!--state.midas)state.flags&=~0x400u;
    if(state.cooldown>0)--state.cooldown;
}
inline int sourceMidasDeathCoins(uint32_t rng) { return int(rng%3)+1; }
} // namespace dw
