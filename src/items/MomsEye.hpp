#pragma once
#include <cstdint>
namespace dw {
// Repentance1.7.9b ordinary weapon: Boolean ownership, one supplied global RNG
// word per volley, strict comparison after single-precision conversion.
inline bool momsEyeBackward(float luck,uint32_t word,float multiplier=1) {
    const float luckTerm=.1f*luck;
    const float threshold=(.5f+luckTerm)*multiplier;
    return float(word)*0x1p-32f<threshold;
}
}
