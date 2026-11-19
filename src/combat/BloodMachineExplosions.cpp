#include "combat/Simulation.hpp"

namespace dw {
std::vector<size_t> Simulation::bloodMachineBlastTargets(const Event &e)const {
    std::vector<size_t> targets;
    if(!bloodExplosionTuning.destructible)return targets;
    for(size_t i=0;i<bloodMachines.size();++i) {
        const auto &m=bloodMachines[i];
        if(m.room!=room||m.phase==BloodMachine::Phase::Broken)continue;
        const auto box=bloodMachineBody(m.position);
        const Vector3 surface{std::clamp(e.position.x,box.min.x,box.max.x),std::clamp(e.position.y,box.min.y,box.max.y),std::clamp(e.position.z,box.min.z,box.max.z)};
        const float d=distance(e.position,surface);
        const auto end=d>.025f?sub(surface,mul(unit(sub(surface,e.position)),.025f)):e.position;
        if(d<e.radius&&(!e.explosionLineCheck||d<.001f||arena.sight(e.position,end)))targets.push_back(i);
    }
    return targets;
}
void Simulation::destroyBloodMachine(size_t index) {
    auto &m=bloodMachines.at(index);
    if(m.phase==BloodMachine::Phase::Broken)return;
    // Native explosion flag destroys this prop regardless of damage amount.
    // The accepted donation RNG history is retained as an explicit DW adapter.
    m.phase=BloodMachine::Phase::Broken;m.blastDestroyed=true;m.paid=true;
    m.blastDrops=sourceBloodExplosionDrops(m.rng);m.blastOutcome=bloodExplosionTuning.outcome;
    if(!bloodExplosionTuning.rewards||m.blastOutcome==1)m.blastDrops={};
    else if(m.blastOutcome>1) {
        m.blastDrops={};m.blastDrops.count=m.blastOutcome==2?1:2;
        for(int i=0;i<m.blastDrops.count;++i)m.blastDrops.entries[size_t(i)]={m.blastOutcome==2?10:20,bloodExplosionRandom(m.rng)};
    }
    syncMovementBodies();cancelMove();for(auto &e:enemies)e.pathTime=0;
    particleEffect(ParticleEffect::Dirt,m.position,{0,1,0},.9f);
    checkpointNeeded=true;announce("BLOOD MACHINE DESTROYED",2);
}
void Simulation::deliverBloodExplosionDrops() {
    for(auto &m:bloodMachines)if(m.room==room&&m.blastDestroyed) {
        while(m.blastDelivered<m.blastDrops.count&&pendingBloodRewards.size()<1024) {
            const auto &d=m.blastDrops.entries[size_t(m.blastDelivered)];
            const auto resolved=sourceOrdinaryPickup(d.seed,d.variant);
            pendingBloodRewards.push_back({m.position,m.room,0,m.blastOutcome>1?1:resolved.subtype,m.blastDelivered,d.seed,d.variant});
            ++m.blastDelivered;checkpointNeeded=true;
        }
    }
}
}
