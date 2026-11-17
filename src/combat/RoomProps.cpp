#include "combat/Simulation.hpp"

namespace dw {
void Simulation::resolvePropReward(PropRewardState &drop,uint32_t seed,bool fire) {
    if(drop.resolved)return;
    drop.resolved=true;drop.heartAppearanceSpeed=redHeartAppearanceSpeed;
    if(roomProps.rewards) {
        const auto choice=ordinaryPropDrop(seed?seed:1,fire,drop.seed);
        drop.variant=choice.variant;drop.subtype=choice.subtype;
    }
    drop.delivered=drop.variant==0;checkpointNeeded=true;
}
void Simulation::deliverPropRewards() {
    if(dead||finished)return;
    const auto deliver=[&](PropRewardState &drop,Vector3 origin) {
        if(!drop.resolved||drop.delivered)return;
        if((drop.variant==10&&heartPickups.size()>=1024)||(drop.variant==20&&moneyPickups.size()>=1024))return;
        std::optional<Vector3> position;
        for(int attempt=0;attempt<33&&!position;++attempt) {
            const float angle=float(attempt)*2.399963f,radius=attempt==0?0:.8f+float((attempt-1)/16)*.7f;
            const Vector3 at{origin.x+std::cos(angle)*radius,.85f,origin.z+std::sin(angle)*radius};
            if(arena.roomAt(at)!=room||arena.blocked(at,.4f)||!arena.clear(origin,at,.15f))continue;
            const auto near=[&](const auto &p){return planarDistance(p.position,at)<.7f;};
            if(std::any_of(moneyPickups.begin(),moneyPickups.end(),near)||std::any_of(heartPickups.begin(),heartPickups.end(),near)||
               std::any_of(keyPickups.begin(),keyPickups.end(),near)||std::any_of(bombPickups.begin(),bombPickups.end(),near))continue;
            position=at;
        }
        if(!position)return;
        if(drop.variant==20) {
            MoneyPickup coin{*position,sourceOrdinaryCoinValue(drop.subtype),0,true};
            coin.sourceSubtype=drop.subtype;coin.room=room;coin.timing.appear(1);moneyPickups.push_back(coin);
        } else if(drop.variant==10) {
            HeartKind kind=HeartKind::Red;int amount=2;
            switch(drop.subtype) {
            case 2:amount=1;break;case 5:amount=4;break;
            case 3:kind=HeartKind::Soul;break;case 4:kind=HeartKind::Eternal;amount=1;break;
            case 6:kind=HeartKind::Black;break;case 10:kind=HeartKind::Blended;break;
            default:break;
            }
            if(!spawnHeartPickup(kind,*position,amount))return;
            heartPickups.back().sourceSubtype=drop.subtype;heartPickups.back().timing.appear(drop.heartAppearanceSpeed);
        } else return;
        drop.delivered=true;checkpointNeeded=true;
    };
    for(auto &prop:arena.breakables)if(prop.room==room&&prop.kind==BreakableKind::Dung&&prop.destroyed)
        deliver(prop.propReward,prop.rewardPosition);
    for(auto &enemy:enemies)if(enemy.environment&&enemy.environment->spent)
        deliver(enemy.environment->propReward,enemy.position);
}
} // namespace dw
