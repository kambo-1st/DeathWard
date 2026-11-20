#pragma once
#include "core/Types.hpp"
#include <cstdint>
#include <stdexcept>
namespace dw {
struct CoinDonationTuning {
    bool enabled=true,destructible=true;
    float cycleSpeed=1,jamScale=1;
    int outcome=0; // 0 source; 1 never jam / 2 jam on next completed donation: testing.
    bool operator==(const CoinDonationTuning&)const=default;
    bool custom()const{return *this!=CoinDonationTuning{};}
    void validate()const {
        if(!std::isfinite(cycleSpeed)||cycleSpeed<.25f||cycleSpeed>4||!std::isfinite(jamScale)||jamScale<0||jamScale>3||outcome<0||outcome>2)
            throw std::runtime_error("Invalid coin donation settings");
    }
};
inline uint32_t donationRandom(uint32_t &seed){if(!seed)seed=1;seed^=seed>>4;seed^=seed<<3;seed^=seed>>17;return seed;}
struct DonationResult {bool luck=false,jammed=false,overflow=false;int cooldown=0;std::array<uint32_t,15> overflowSeeds{};};
inline DonationResult sourceDonation(uint32_t &seed,uint32_t bank,int deposits,int held,float jamScale=1,int outcome=0) {
    DonationResult r;r.luck=donationRandom(seed)%50==0;r.overflow=bank%1000==999;
    r.cooldown=bank%1000==998?20:std::max(0,15-held/10);
    if(r.overflow){for(auto &child:r.overflowSeeds)child=donationRandom(seed);return r;}
    r.jammed=double(donationRandom(seed)%2000)<3.*(double(deposits)+1)*jamScale;
    if(outcome)r.jammed=outcome==2;
    return r;
}
inline int sourceDonationWithdrawal(uint32_t &seed,uint32_t bank){return std::min(int(bank%1000),7+int(donationRandom(seed)%9));}
struct DonationProgress {
    // Native persistent counter is cumulative; display and available bank use modulo1000.
    uint32_t bank=0;uint16_t unlocks=0;int deposits=0,luck=0;bool jammed=false,excluded=false;
};
struct CoinDonationMachine {
    Vector3 position{};int room=-1;uint32_t rng=1;
    enum class Phase{Idle,Inserting,Jammed,Destroyed};Phase phase=Phase::Idle;
    double tick=0,frame=0;int cooldown=0,held=0,payoutFrame=6;
    CoinDonationTuning cycle{};
};
inline Box coinDonationBody(Vector3 at){return {{at.x-.55f,-.2f,at.z-.55f},{at.x+.55f,2.0f,at.z+.55f}};}
}
