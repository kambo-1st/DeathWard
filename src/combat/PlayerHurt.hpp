#pragma once
#include <algorithm>
#include <cmath>


namespace dw {
// Repentance 1.7.9b 73d701..73d719 and 740cfe..740d45.
// Use the original rounded amount, before damage-reduction health modifiers.
// This is a native invocation counter; wall-clock/scheduler acceptance is separate.
inline int sourcePlayerRoundedDamage(float halfHearts) {
    return int(halfHearts+.5f);
}
inline int sourcePlayerHurtCounter(int originalRoundedDamage) {
    return std::min(2,originalRoundedDamage)*60;
}
inline int sourcePlayerHurtTick(int counter) {
    return counter>0?counter-1:counter;
}
} // namespace dw
