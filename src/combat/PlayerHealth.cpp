#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::collectHeart(HeartKind kind,int amount) {
    if(amount<=0||dead||finished||player.totalHealth()<=0)return false;
    auto health=player.sourceHealth();
    amount=std::min(amount,24);
    const auto before=std::array{health.maxRed,health.red,health.eternal,health.soul,int(health.blackMask),
        health.golden,health.bone,int(health.boneMask),health.rotten};
    switch(kind) {
    case HeartKind::Red:health.addRed(amount);break;
    case HeartKind::Soul:health.addSoul(amount);break;
    case HeartKind::Black:health.addBlack(amount);break;
    case HeartKind::Eternal:health.addEternal(amount);break;
    case HeartKind::Golden:health.addGolden(amount);break;
    case HeartKind::Bone:health.addBone(amount);break;
    case HeartKind::Rotten:health.addRotten(amount);break;
    case HeartKind::Blended:if(amount!=2)return false;health.collectBlended();break;
    case HeartKind::Scared:if(amount!=2)return false;health.addRed(2);break;
    default:return false;
    }
    const auto after=std::array{health.maxRed,health.red,health.eternal,health.soul,int(health.blackMask),
        health.golden,health.bone,int(health.boneMask),health.rotten};
    if(before==after)return false;
    applyPlayerHealth(std::move(health));
    audioCues.push(AudioCueKind::Pickup,player.position);checkpointNeeded=true;
    return true;
}
bool Simulation::addBrokenHearts(int amount) {
    if(amount==0||dead||finished||player.totalHealth()<=0)return false;
    auto health=player.sourceHealth();health.addBroken(std::clamp(amount,-12,12));
    if(health.broken==player.brokenHearts)return false;
    applyPlayerHealth(std::move(health));checkpointNeeded=true;
    return true;
}
void Simulation::applyPlayerHealth(SourcePlayerHealth health) {
    player.setSourceHealth(health);
    for(const auto &effect:health.effects) {
        switch(effect.kind) {
        case HealthEffectKind::BlackBurst:
            for(const auto &enemy:enemies)if(enemy.alive&&!enemy.friendly) {
                Event hit;hit.type=EventType::Damage;hit.target=enemy.id;
                hit.damage=40;hit.position=enemy.position;hit.origin=player.position;
                hit.areaDamage=true;hit.ignoreAdaptiveArmor=true;
                hit.context.damageSource=DamageSource::Player;
                pendingHealthEvents_.push_back(hit);
            }
            effectVisual(player.position,8,0,.5f);break;
        case HealthEffectKind::GoldenBurst:
            for(int i=0;i<effect.count;++i) {
                const int coins=3+int(rewardRng.bounded(6));
                for(int n=0;n<coins&&moneyPickups.size()<1024;++n) {
                    auto point=arena.move(player.position,rotateY({1.5f,0,0},n*2*Pi/coins),.25f);
                    moneyPickups.push_back({point,1,0,true});
                }
            }
            for(const auto &enemy:enemies)if(enemy.alive&&distance(horizontal(enemy.position),horizontal(player.position))<=8)
                applyMidasFreeze(enemy.id,180,true);
            effectVisual(player.position,8,0,.5f);break;
        case HealthEffectKind::BoneBreakVisuals:particleEffect(ParticleEffect::Stone,player.position);break;
        case HealthEffectKind::ConversionAnimation:effectVisual(player.position,1,0,.5f);break;
        }
    }
    flushPlayerHealthEvents();
    checkpointNeeded=true;
}
void Simulation::flushPlayerHealthEvents() {
    while(!pendingHealthEvents_.empty()) {
        if(!queueRoot(pendingHealthEvents_.front()))break;
        pendingHealthEvents_.pop_front();
    }
}
// Ordinary Isaac's 1up: documented behavior; native death-branch acceptance
// is tracked separately from the executed health kernel.
bool Simulation::tryRevivePlayer() {
    const ItemKey oneUp{"isaac",ItemKind::Collectible,11};
    const auto life=std::find(items.begin(),items.end(),oneUp);
    if(life==items.end())return false;
    items.erase(life);
    auto health=player.sourceHealth();
    health.red=health.rotten=health.soul=0;health.blackMask=0;health.eternal=health.golden=0;
    if(health.redCapacity()>0)health.addRed(health.redCapacity());
    else health.addSoul(1);
    if(health.red+health.soul+health.bone<=0)return false; // Broken capacity can prevent revival.
    player.setSourceHealth(health);
    const int destination=std::clamp(reviveRoom_,0,finalRoom());
    enterRoom(destination);player.position=arena.rooms[size_t(destination)].entry;
    player.velocity={};player.hurt=2;player.dodge=0;cancelMove();
    announce("Extra life / returned to safety.");checkpointNeeded=true;
    return true;
}
bool Simulation::addRedContainers(int halves,bool fill) {
    if(dead||finished||halves==0||halves < -24||halves > 24)return false;
    auto health=player.sourceHealth();const int before=health.maxRed;
    health.addMaxRed(halves);
    if(fill&&health.maxRed>before)health.addRed(health.maxRed-before);
    if(health.maxRed==before)return false;
    applyPlayerHealth(std::move(health));return true;
}
bool Simulation::canPayHealthCost(int redContainers,int soulHalfHearts) const {
    if(dead||finished||player.totalHealth()<=0||redContainers<1||redContainers>12||soulHalfHearts<1||soulHalfHearts>24)return false;
    return player.redHealthCapacity()>0?player.redHealthCapacity()>=2*redContainers:player.soulHearts>=soulHalfHearts;
}
bool Simulation::payHealthCost(int redContainers,int soulHalfHearts) {
    if(!canPayHealthCost(redContainers,soulHalfHearts))return false;
    auto health=player.sourceHealth();
    if(health.redCapacity()>0)health.addMaxRed(-2*redContainers);
    else health.addSoul(-soulHalfHearts);
    applyPlayerHealth(std::move(health));return true;
}
bool Simulation::spawnHeartPickup(HeartKind kind,Vector3 position,int amount) {
    if(amount==0)amount=kind==HeartKind::Bone||kind==HeartKind::Eternal||kind==HeartKind::Golden?1:2;
    if(kind<HeartKind::Red||kind>HeartKind::Scared)return false;
    if(!std::isfinite(position.x)||!std::isfinite(position.y)||!std::isfinite(position.z))return false;
    if(amount<1||amount>24||heartPickups.size()>=1024||dead||finished||arena.blocked(position,.25f))return false;
    const int index=arena.roomAt(position);if(index<0)return false;
    heartPickups.push_back({position,kind,amount,index});checkpointNeeded=true;return true;
}
void Simulation::updateHeartPickups(float dt) {
    flushPlayerHealthEvents();
    std::erase_if(heartPickups,[&](auto &pickup) {
        if(pickup.room!=room)return false;
        pickup.timing.advance(dt);
        if(pickup.timing.phase==RedHeartTiming::Phase::Gone)return true;
        if(!pickup.timing.collectible()||distance(player.position,pickup.position)>=1||
           !arena.clear(player.position,pickup.position,.1f))return false;
        if(pickup.upgradedShopSlot>=0&&!canBuyUpgradedShop(pickup.upgradedShopSlot))return false;
        const int basePrice=shopHeartBasePrice();
        if(pickup.shopStock&&(!hasSourceShop(room)||!shopHeartOffered()||shopHeartSold||!roomClear||roomThreats()||
           pickup.kind!=shopHeartKind||basePrice<0||basePrice>15||money()<uint64_t(shopPrice(basePrice,shopHeartSlot))))return false;
        if(!collectHeart(pickup.kind,pickup.amount))return false;
        if(pickup.upgradedShopSlot>=0)payUpgradedShop(pickup.upgradedShopSlot);
        if(pickup.shopStock) {
            moneySpent+=uint64_t(shopPrice(basePrice,shopHeartSlot));shopHeartSold=true;checkpointNeeded=true;
            announce(std::string(pickup.kind==HeartKind::Soul?"SOUL HEART / ":"RED HEART / ")+std::to_string(shopPrice(basePrice,shopHeartSlot))+" COINS",2);
        }
        // Health changes once at admission; the source-duration collection
        // presentation cannot pay again, including after leaving/re-entering.
        if(pickup.sourceSubtype){pickup.timing.collect();return false;}
        return true; // Existing directly placed typed-health fixtures stay idle.
    });
    // A deferred actor is born after this update, with no retroactive age.
    deliverRoomHearts(room);
    deliverShopHeart();
    deliverRedHeartClearAward();
}
} // namespace dw
