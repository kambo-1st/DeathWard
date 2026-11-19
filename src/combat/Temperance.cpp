#include "combat/Simulation.hpp"
#include "world/SourceShopHeart.hpp"
namespace dw {
Vector3 Simulation::shopCardPosition()const {
    return shopCardSlot==0?sourceShopKeyPosition(arena.rooms.at(size_t(arena.shopRoom))):sourceShopHeartPosition(arena.rooms.at(size_t(arena.shopRoom)));
}
void Simulation::deliverShopCard() {
    if(!hasSourceShop(room)||shopCardSlot<0||shopCardSold||shopCardDelivered)return;
    const auto &site=arena.rooms[size_t(room)];
    const auto seed=site.sourceShopTemplate==0?recordedShopSlotSeed(site,7):uint32_t(seed_^0x54454d504552414eULL)|1U;
    if(spawnPill(shopCardPosition(),TemperanceCard,seed,true)){
        pillPickups.back().shopStock=true;shopCardDelivered=true;
    }
}
bool Simulation::spawnBloodMachine(Vector3 at,uint32_t seed) {
    if(dead||finished||!seed||bloodMachines.size()>=64||!std::isfinite(at.x)||!std::isfinite(at.z)||arena.roomAt(at)!=room||arena.blocked(at,1.15f))return false;
    const auto body=bloodMachineBody(at);
    if(sphereBox(player.position,.6f,body)||arena.reservedSupplyCache(at,1.1f))return false;
    for(const auto &e:enemies)if(e.alive&&sphereBox(e.position,e.radius+.1f,body))return false;
    for(const auto &p:pillPickups)if(p.room==room&&sphereBox(p.position,.5f,body))return false;
    for(const auto &p:heartPickups)if(p.room==room&&sphereBox(p.position,.5f,body))return false;
    for(const auto &p:moneyPickups)if(arena.roomAt(p.position)==room&&sphereBox(p.position,.5f,body))return false;
    for(const auto &p:keyPickups)if(p.room==room&&sphereBox(p.position,.5f,body))return false;
    for(const auto &p:bombPickups)if(p.room==room&&sphereBox(p.position,.5f,body))return false;
    for(const auto &p:machineCollectibles)if(p.room==room&&sphereBox(p.position,.5f,body))return false;
    for(int id:arena.rooms[size_t(room)].passages)for(const auto &gate:arena.passages[size_t(id)].gates)if(sphereBox(at,2.2f,gate))return false;
    bloodMachines.push_back({at,room,seed});syncMovementBodies();cancelMove();checkpointNeeded=true;return true;
}
bool Simulation::useTemperance() {
    // Retain the card when no safe machine site exists. RNG advances only after admission.
    uint32_t next=temperanceRng_;const auto seed=bloodRandom(next);
    for(int ring=0;ring<5;++ring)for(int step=0;step<16;++step){
        const float a=step*Pi/8;auto at=add(player.position,{std::cos(a)*(2.3f+ring*.8f),0,std::sin(a)*(2.3f+ring*.8f)});
        if(arena.path(player.position,at,.48f).empty())continue;
        if(spawnBloodMachine(at,seed)){temperanceRng_=next;pills.held=0;announce("TEMPERANCE / TOUCH THE MACHINE TO DONATE HEALTH",4);return true;}
    }
    announce("NO ROOM FOR A MACHINE / CARD KEPT",3);return false;
}
bool Simulation::payBlood(bool portable) {
    if(dead||finished||player.totalHealth()<=0||player.dodge>0||rewardOpen||shopOpen||letterOpen||storyOpen!=StoryRoom::None||floorExitRequested||pendingBloodRewards.size()>1020)return false;
    if(!portable&&player.hurt>=.25f)return false;
    const float oldHurt=player.hurt;player.hurt=0;
    if(bloodMachineTuning.healthCost>0&&!godMode&&bookProtectionRemaining<=1e-7) {
        if(!takeHeartDamage(float(bloodMachineTuning.healthCost),true,{},false)){player.hurt=oldHurt;return false;}
    }else player.hurt=oldHurt; // Existing protection remains effective; source caller ignores damage denial.
    checkpointNeeded=true;return true;
}
bool Simulation::useIvBag() {
    if(ivBagCooldown>1e-7||!payBlood(true))return false;
    const int count=std::clamp(int(std::round(sourceIvCoins(temperanceRng_)*bloodMachineTuning.payoutScale)),0,6);
    for(int i=0;i<count;++i){const auto seed=bloodRandom(temperanceRng_);const auto coin=sourceOrdinaryPickup(seed,20);
        pendingBloodRewards.push_back({player.position,room,0,coin.subtype,i,seed});}
    ivBagCooldown=bloodMachineTuning.ivCooldown;announce("IV BAG / HEALTH FOR COINS",2);return true;
}
void Simulation::deliverBloodRewards() {
    std::erase_if(pendingBloodRewards,[&](const BloodReward &p){
        if(p.room!=room||(p.item?machineCollectibles.size()>=256:moneyPickups.size()>=1024))return false;
        for(int ring=0;ring<6;++ring)for(int step=0;step<16;++step){
            const float a=(step+p.ordinal*4)*Pi/8;auto at=add(p.origin,{std::cos(a)*(1.6f+ring*.5f),0,std::sin(a)*(1.6f+ring*.5f)});at.y=.85f;
            if(arena.roomAt(at)!=room||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.6f)||arena.path(player.position,at,.48f).empty())continue;
            bool crowded=false;for(const auto &v:machineCollectibles)if(v.room==room&&planarDistance(at,v.position)<1.2f)crowded=true;
            for(const auto &v:moneyPickups)if(arena.roomAt(v.position)==room&&planarDistance(at,v.position)<.75f)crowded=true;
            if(crowded)continue;
            if(p.item)machineCollectibles.push_back({at,room,p.item,0});
            else {MoneyPickup coin{at,sourceOrdinaryCoinValue(p.subtype),0,true};coin.sourceSubtype=p.subtype;coin.room=room;coin.timing.appear(1);moneyPickups.push_back(coin);}
            checkpointNeeded=true;return true;
        }return false;
    });
}
void Simulation::updateBloodMachines(float dt) {
    ivBagCooldown=std::max(0.,ivBagCooldown-double(dt));deliverShopCard();
    for(auto &m:bloodMachines)if(m.room==room){
        if(m.phase==BloodMachine::Phase::Idle){
            const auto d=sub(player.position,m.position);
            if(std::abs(d.x)<1.12f&&std::abs(d.z)<1.12f&&arena.sight(player.position,m.position)&&payBlood(false)){
                m.phase=BloodMachine::Phase::Initiate;m.elapsed=0;m.paid=false;m.cycleSpeed=bloodMachineTuning.cycleSpeed;
                m.payoutScale=bloodMachineTuning.payoutScale;m.breakScale=bloodMachineTuning.breakScale;m.outcome=bloodMachineTuning.outcome;
                audioCues.push(AudioCueKind::Pickup,m.position);
            }continue;
        }
        if(m.phase==BloodMachine::Phase::Broken)continue;
        m.elapsed+=double(dt)*30*m.cycleSpeed;
        if(m.elapsed+1e-6>=30)m.phase=BloodMachine::Phase::Prize;
        if(m.elapsed+1e-6>=33&&!m.paid){
            m.paid=true;auto result=sourceBloodOutcome(m.rng,true,ivBagAvailable_,m.breakScale);
            if(m.outcome==1)result={0,1};else if(m.outcome==2)result={119,0};else if(m.outcome==3)result={135,0};
            if(result.item){
                if(result.item==135)ivBagAvailable_=false;
                pendingBloodRewards.push_back({m.position,m.room,result.item,1,0,bloodRandom(m.rng)});
                m.phase=BloodMachine::Phase::Broken;announce("MACHINE BROKE / UPGRADE DROPPED",3);syncMovementBodies();
            }else {
                const int count=std::clamp(int(std::round(result.coins*m.payoutScale)),0,6);
                for(int i=0;i<count;++i){const auto seed=bloodRandom(m.rng);const auto coin=sourceOrdinaryPickup(seed,20);pendingBloodRewards.push_back({m.position,m.room,0,coin.subtype,i,seed});}
            }
            checkpointNeeded=true;
        }
        if(m.phase!=BloodMachine::Phase::Broken&&m.elapsed+1e-6>=38){m.phase=BloodMachine::Phase::Idle;m.elapsed=0;}
    }
    deliverKeeperDrops();deliverBloodRewards();
    bool admitted=false;
    std::erase_if(machineCollectibles,[&](MachineCollectible &p){
        if(p.room!=room)return false;
        p.age+=dt;
        const bool contact=planarDistance(player.position,p.position)<1;
        if(!contact){p.contactBlocked=false;return false;}
        if(admitted||p.age<.85f||p.contactBlocked||dead||player.totalHealth()<=0||!arena.clear(player.position,p.position,.1f))return false;
        const ItemKey item{"isaac",ItemKind::Collectible,uint32_t(p.item)};
        if(!content->item(item)||(items.size()>=256&&!(supportedActive(item)&&activeItem)))return false;
        admitted=true;const auto outgoing=activeItem;
        if(supportedActive(item)&&outgoing){
            const auto owned=std::find(items.begin(),items.end(),outgoing->item);if(owned==items.end())return false;
            items.erase(owned);activeItem.reset();grant(item);activeItem->charge=p.charge;
            p.item=int(outgoing->item.number);p.charge=outgoing->charge;p.age=0;p.contactBlocked=true;
            announce(std::string(activeName(item))+" / ACTIVE SWAPPED",3);return false;
        }
        grant(item);if(supportedActive(item))activeItem->charge=p.charge;
        announce(item.number==64?"STEAM SALE / SHOP DISCOUNT":item.number==119?"BLOOD BAG / HEALTH + SPEED":std::string(activeName(item))+" / ACTIVE ITEM",3);checkpointNeeded=true;return true;
    });
}
}
