#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>

namespace dw {
struct BloodExplosionTuning {
    bool destructible=true,rewards=true;
    int outcome=0; // Source / test nothing / test full red heart / test two pennies.
    bool operator==(const BloodExplosionTuning &)const=default;
    bool custom()const{return *this!=BloodExplosionTuning{};}
    void validate()const{if(outcome<0||outcome>3)throw std::runtime_error("Invalid blood-machine explosion outcome");}
};
struct BloodExplosionDrop {int variant=0;uint32_t seed=0;};
struct BloodExplosionDrops {std::array<BloodExplosionDrop,8> entries{};int count=0;};
inline uint32_t bloodExplosionRandom(uint32_t &state) {
    if(!state)throw std::invalid_argument("Blood-machine destruction requires nonzero RNG state");
    state^=state>>4;state^=state<<3;state^=state>>17;return state;
}
// Native 63f841..63f92d, ordinary blood machine; Daemon's Tail absent.
// A batch is either one unresolved heart or 1–4 unresolved coin actors.
inline BloodExplosionDrops sourceBloodExplosionDrops(uint32_t &state) {
    BloodExplosionDrops result;
    const int batches=1+int(bloodExplosionRandom(state)%2);
    for(int batch=0;batch<batches;++batch) {
        const bool heart=bloodExplosionRandom(state)%2!=0;
        const int count=heart?1:1+int(bloodExplosionRandom(state)%4);
        for(int i=0;i<count;++i)result.entries[std::size_t(result.count++)]={heart?10:20,bloodExplosionRandom(state)};
    }
    return result;
}
}
