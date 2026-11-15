#pragma once
#include "combat/SourceRoomRewards.hpp"
#include <vector>

namespace dw {
struct ChestDrop {
    int variant=0, subtype=1;
    uint32_t seed=0;
    bool delivered=false;
};
// First playable chest: pickup batches only. This is an explicit adaptation,
// NOT the complete native chest selector (pills/trinkets/nested chests missing).
// Public ordinary-batch weights: coins35 / hearts20 / keys15 / bombs30.
// DW seed stream, equal 2/3 batch choice and ordinary key/bomb subtypes are
// adaptations until the installed native chest wrapper has been captured.
inline std::vector<ChestDrop> chestPickupBatches(uint32_t seed) {
    SourceAwardRng rng{seed};std::vector<ChestDrop> drops;
    const int packs=2+int(rng.bounded(2));
    for(int i=0;i<packs;++i) {
        const auto roll=rng.bounded(100);
        const int variant=roll<35?20:roll<55?10:roll<70?30:40;
        const int count=variant==20?1+int(rng.bounded(3)):1;
        for(int n=0;n<count;++n) {
            const auto init=rng.next();
            const int subtype=variant==10||variant==20?sourceOrdinaryPickup(init,variant).subtype:1;
            drops.push_back({variant,subtype,init,false});
        }
    }
    return drops;
}
} // namespace dw
