#pragma once
#include "core/Types.hpp"
#include <array>
#include <cstdint>
namespace dw {
inline constexpr std::array<int,10> DonationMilestones{10,20,50,100,150,200,400,600,900,999};
inline constexpr uint16_t AllDonationMilestones=1023;
inline uint16_t donationMilestonesAt(unsigned bank) {
    uint16_t flags=0;for(size_t i=0;i<DonationMilestones.size();++i)if(bank>=unsigned(DonationMilestones[i]))flags|=uint16_t(1u<<i);return flags;
}
inline int donationShopLevel(uint16_t flags) {
    return flags&(1<<7)?4:flags&(1<<5)?3:flags&(1<<3)?2:flags&(1<<1)?1:0;
}
struct UpgradedShopOffer {
    Vector3 position{};int category=0,item=0,slot=0;uint32_t seed=1;bool sold=false,delivered=false;
    bool supported()const{return category!=7;} // Full trinket-stock dependencies remain pending.
};
// Default ordinary source2.level.level coordinates, separate from canyon adaptation.
inline constexpr std::array<std::array<std::pair<int,int>,6>,5> SourceShopCells{{
    {{{5,4},{7,4}}},{{{4,4},{6,4},{8,4}}},{{{3,4},{5,4},{7,4},{9,4}}},
    {{{2,4},{4,4},{6,4},{8,4},{10,4}}},{{{4,2},{8,2},{3,4},{5,4},{7,4},{9,4}}}
}};
}
