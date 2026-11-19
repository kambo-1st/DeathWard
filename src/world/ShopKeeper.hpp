#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
namespace dw {
struct KeeperTuning {
    bool destructible=true,rewards=true;
    int outcome=0; // 0 source; 1 no drop, 2 coins, 3 spiders, 4 Steam Sale: testing overrides.
    bool operator==(const KeeperTuning &)const=default;
    bool custom()const{return *this!=KeeperTuning{};}
    void validate()const{if(outcome<0||outcome>4)throw std::runtime_error("Keeper outcome must be 0-4");}
};
struct KeeperDrop {int type=0,variant=0,subtype=0;uint32_t seed=0;};
struct KeeperDrops {std::array<KeeperDrop,2> entries{};int count=0;};
inline uint32_t keeperRandom(uint32_t &s){if(!s)s=1;s^=s>>4;s^=s<<3;s^=s>>17;return s;}
// Original ordinary 17.1 drop branch; explicit availability is separate from RNG.
// Production supports Steam Sale; Head of the Keeper/Coupon remain unavailable.
inline KeeperDrops sourceKeeperDrops(uint32_t &s,unsigned available=1) {
    for(int i=0;i<3;++i)if(keeperRandom(s)%100==0&&(available&(1u<<i))) {
        const int items[3]={64,429,521};return {{{KeeperDrop{5,100,items[i],keeperRandom(s)},KeeperDrop{}}},1};
    }
    KeeperDrops result;const auto draw=keeperRandom(s)%3;
    if(draw)for(int i=0;i<2;++i)result.entries[std::size_t(result.count++)]={draw==1?85:5,draw==1?0:20,0,keeperRandom(s)};
    return result;
}
struct ShopKeeperState {
    static constexpr float SourceHealth=5;
    float sourceHealth=SourceHealth;bool destroyed=false;
    KeeperDrops drops{};int delivered=0;uint32_t rng=0;
};
}
