#include "combat/Simulation.hpp"
#include "world/SourceRecordedShop.hpp"
namespace dw {
void Simulation::prepareCoinDonation() {
    const int shop=arena.shopRoom;
    if(donation.excluded||!hasSourceShop(shop)||arena.rooms[size_t(shop)].sourceShopTemplate!=0)return;
    for(const auto &m:coinDonationMachines)if(m.room==shop)return;
    const auto &site=arena.rooms[size_t(shop)];auto at=recordedShopCell(site,3,0);
    // Source slot retained; canyon floor/collision is authoritative. Never move it over stock.
    if(arena.blocked(at,.58f))return;
    CoinDonationMachine m;m.position=at;m.room=shop;m.rng=recordedShopSlotSeed(site,0);
    if(donation.jammed)m.phase=CoinDonationMachine::Phase::Jammed;
    coinDonationMachines.push_back(m);syncMovementBodies();
}
void Simulation::updateCoinDonation(float dt) {
    prepareCoinDonation();
    for(auto &m:coinDonationMachines)if(m.room==room) {
        if(m.phase==CoinDonationMachine::Phase::Jammed||m.phase==CoinDonationMachine::Phase::Destroyed)continue;
        m.tick+=double(dt)*30;
        while(m.tick+1e-7>=1) {
            m.tick=std::max(0.,m.tick-1);
            const auto d=sub(player.position,m.position);
            const bool contact=std::abs(d.x)<1.12f&&std::abs(d.z)<1.12f&&arena.sight(player.position,m.position);
            m.held=contact?std::min(65535,m.held+1):0;
            if(m.cooldown>0)--m.cooldown;
            if(m.phase==CoinDonationMachine::Phase::Inserting) {
                m.frame+=m.cycle.cycleSpeed;
                if(m.frame+1e-7<m.payoutFrame)continue;
                const auto result=sourceDonation(m.rng,donation.bank,donation.deposits,m.held,m.cycle.jamScale,m.cycle.outcome);
                const int previousLevel=donationShopLevel(donation.unlocks);
                donation.unlocks|=donationMilestonesAt(donation.bank%1000+1);
                ++donation.bank;++donation.deposits;donation.luck+=result.luck;
                m.cooldown=result.cooldown;m.phase=CoinDonationMachine::Phase::Idle;
                if(donation.bank%1000==999)m.held=0;
                if(result.overflow) {
                    donation.excluded=true;m.phase=CoinDonationMachine::Phase::Destroyed;
                    for(int i=0;i<15;++i)pendingBloodRewards.push_back({m.position,room,0,3,i,result.overflowSeeds[size_t(i)]});
                    syncMovementBodies();announce("DONATION BANK FULL / DIMES RELEASED",4);
                } else if(result.jammed) {
                    donation.jammed=true;m.phase=CoinDonationMachine::Phase::Jammed;
                    announce("DONATION MACHINE JAMMED / BANK SAVED",4);
                } else announce("DONATED 1 COIN / BANK "+std::to_string(donation.bank%1000)+(result.luck?" / LUCK +1":""),2);
                if(donationShopLevel(donation.unlocks)>previousLevel)announce("SHOP UPGRADE "+std::to_string(donationShopLevel(donation.unlocks))+" EARNED / NEXT EXPEDITION",5);
                checkpointNeeded=true;
                if(m.phase==CoinDonationMachine::Phase::Jammed||m.phase==CoinDonationMachine::Phase::Destroyed)break;
                continue;
            }
            if(!contact||m.cooldown>0||!coinDonationTuning.enabled||money()<1||dead||finished||player.totalHealth()<=0||player.dodge>0||rewardOpen||shopOpen||letterOpen||storyOpen!=StoryRoom::None||floorExitRequested||pendingBloodRewards.size()>1000||donation.bank==UINT32_MAX)continue;
            ++moneySpent;m.phase=CoinDonationMachine::Phase::Inserting;m.frame=0;
            m.payoutFrame=m.held>120?2:m.held>60?4:6;m.cycle=coinDonationTuning;
            audioCues.push(AudioCueKind::Pickup,m.position);checkpointNeeded=true;
        }
    }
}
std::vector<size_t> Simulation::coinDonationBlastTargets(const Event &e)const {
    std::vector<size_t> hits;if(!coinDonationTuning.destructible)return hits;
    for(size_t i=0;i<coinDonationMachines.size();++i) {
        const auto &m=coinDonationMachines[i];
        if(m.room!=room||m.phase==CoinDonationMachine::Phase::Destroyed||m.phase==CoinDonationMachine::Phase::Jammed)continue;
        const auto box=coinDonationBody(m.position);
        const Vector3 surface{std::clamp(e.position.x,box.min.x,box.max.x),std::clamp(e.position.y,box.min.y,box.max.y),std::clamp(e.position.z,box.min.z,box.max.z)};
        const float d=distance(e.position,surface);const auto end=d>.025f?sub(surface,mul(unit(sub(surface,e.position)),.025f)):e.position;
        if(d<e.radius&&(!e.explosionLineCheck||d<.001f||arena.sight(e.position,end)))hits.push_back(i);
    }return hits;
}
void Simulation::destroyCoinDonation(size_t index) {
    auto &m=coinDonationMachines.at(index);
    if(m.phase==CoinDonationMachine::Phase::Destroyed||m.phase==CoinDonationMachine::Phase::Jammed)return;
    const int withdrawn=sourceDonationWithdrawal(m.rng,donation.bank);donation.bank-=uint32_t(withdrawn);
    m.phase=CoinDonationMachine::Phase::Destroyed;donation.excluded=true;
    // Withdrawals are ordinary random coin pickups (native subtype0 factory), not guaranteed pennies.
    for(int i=0;i<std::max(0,withdrawn-1);++i){auto seed=donationRandom(m.rng);auto coin=sourceOrdinaryPickup(seed,20);pendingBloodRewards.push_back({m.position,room,0,coin.subtype,i,seed});}
    syncMovementBodies();cancelMove();for(auto &e:enemies)e.pathTime=0;
    particleEffect(ParticleEffect::Dirt,m.position,{0,1,0},.8f);checkpointNeeded=true;
    announce("DONATION MACHINE DESTROYED / BANK "+std::to_string(donation.bank%1000),3);
}
}
