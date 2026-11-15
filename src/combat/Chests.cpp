#include "combat/Simulation.hpp"
#include "combat/ChestGeometry.hpp"

namespace dw {
void Simulation::deliverRoomChests(int index) {
    const auto &spawns=arena.rooms[size_t(index)].chestSpawns;
    auto &delivered=rooms[size_t(index)].roomChestsDelivered;
    delivered.resize(spawns.size(),false);
    for(size_t i=0;i<spawns.size();++i) {
        if(delivered[i]||!spawnChest(spawns[i].preferred,spawns[i].pickupSeed))continue;
        // Already present on entry: no clear-reward birth wait. Keep the source
        // cell even when enclosed by rocks; never move it onto reachable floor.
        auto &chest=chests.back();chest.age=.8f;chest.placedInLayout=true;
        delivered[i]=true;
    }
}
bool Simulation::spawnChest(Vector3 position,uint32_t seed) {
    if(!seed||dead||finished||chests.size()>=128||!std::isfinite(position.x)||
       !std::isfinite(position.y)||!std::isfinite(position.z)||arena.blocked(position,chestGeometry::PlacementRadius))return false;
    const int owner=arena.roomAt(position);if(owner<0)return false;
    const auto body=chestGeometry::body(position);
    // A new solid must never materialize around a character or another pickup.
    if(sphereBox(player.position,chestGeometry::PlayerRadius+.05f,body))return false;
    for(const auto &enemy:roomEnemies(owner))if(enemy.alive&&sphereBox(enemy.position,enemy.radius+.05f,body))return false;
    for(const auto &pickup:moneyPickups)if(sphereBox(pickup.position,.4f,body))return false;
    for(const auto &pickup:heartPickups)if(sphereBox(pickup.position,.4f,body))return false;
    for(const auto &pickup:chestSupplies)if(sphereBox(pickup.position,.4f,body))return false;
    for(const auto &pickup:bombPickups)if(sphereBox(pickup.position,.4f,body))return false;
    for(const auto &pickup:keyPickups)if(sphereBox(pickup.position,.4f,body))return false;
    for(const auto &key:arena.keys)if(!key.collected&&sphereBox(key.position,.6f,body))return false;
    ChestPickup chest;chest.position=position;chest.room=owner;chest.seed=seed;
    chest.heartAppearanceSpeed=redHeartAppearanceSpeed;
    chest.contents=chestPickupBatches(seed);chests.push_back(std::move(chest));
    syncMovementBodies();
    // Paths chosen before this birth must respect the newly occupied floor.
    if(!movePath_.empty()) {
        auto route=arena.path(player.position,movePath_.back(),chestGeometry::PlayerRadius);
        movePath_=std::move(route);waypoint_=0;
        if(movePath_.empty())cancelMove();
    }
    checkpointNeeded=true;return true;
}

void Simulation::updateChests(float dt) {
    for(auto &chest:chests) {
        if(chest.room!=room)continue;
        chest.age+=dt;
        // Arena movement/navigation owns the solid body in both states. This
        // local check only admits touch opening, never repairs penetration.
        const auto delta=sub(player.position,chest.position);
        const float stopX=chestGeometry::StopX,stopZ=chestGeometry::StopZ;
        const bool touching=std::abs(delta.x)<=stopX+chestGeometry::ContactMargin&&
                            std::abs(delta.z)<=stopZ+chestGeometry::ContactMargin;
        if(!chest.opened) {
            if(chest.age<.8f||dead||player.totalHealth()<=0||!touching||
               !arena.clear(player.position,chest.position,.15f))continue;
            chest.opened=true;chest.openAge=0;checkpointNeeded=true;
            continue; // Opening starts now, without retroactive time.
        }
        chest.openAge+=dt;
        if(chest.openAge<.4f)continue;
        for(size_t i=0;i<chest.contents.size();++i) {
            auto &drop=chest.contents[i];if(drop.delivered)continue;
            if((drop.variant==20&&moneyPickups.size()>=1024)||
               (drop.variant==10&&heartPickups.size()>=1024)||
               (drop.variant==30&&keyPickups.size()>=1024)||(drop.variant==40&&bombPickups.size()>=1024))continue;
            // Deterministic reachable scatter; do not lose or reroll a blocked
            // drop. Capacity/terrain failures retry this same drop later.
            std::optional<Vector3> position;
            for(int attempt=0;attempt<96&&!position;++attempt) {
                const float angle=float(i)*2.399963f+float(attempt%24)*2*Pi/24;
                const float radius=1.9f+float(attempt/24)*.8f;
                const Vector3 at{chest.position.x+std::cos(angle)*radius,.85f,chest.position.z+std::sin(angle)*radius};
                if(arena.roomAt(at)!=room||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.5f)||
                   !arena.clear(chest.position,at,.25f)||arena.path(player.position,at,.48f).empty())continue;
                const auto near=[&](const auto &p){return planarDistance(p.position,at)<.75f;};
                if(std::any_of(moneyPickups.begin(),moneyPickups.end(),near)||
                   std::any_of(heartPickups.begin(),heartPickups.end(),near)||
                   std::any_of(chestSupplies.begin(),chestSupplies.end(),near)||
                   std::any_of(bombPickups.begin(),bombPickups.end(),near)||
                   std::any_of(keyPickups.begin(),keyPickups.end(),near))continue;
                bool gate=false;
                for(int p:arena.rooms[size_t(room)].passages)for(auto box:arena.passages[size_t(p)].gates)
                    gate|=sphereBox(at,.5f,box);
                if(!gate)position=at;
            }
            if(!position)continue;
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
                if(!spawnHeartPickup(kind,*position,amount))continue;
                heartPickups.back().sourceSubtype=drop.subtype;
                heartPickups.back().timing.appear(chest.heartAppearanceSpeed);
            } else if(drop.variant==30) {
                if(!spawnOrdinaryKey(*position,drop.subtype,chest.seed))continue;
            } else if(drop.variant==40) {
                if(!spawnOrdinaryBomb(*position,drop.subtype,chest.seed))continue;
            } else continue;
            drop.delivered=true;checkpointNeeded=true;
        }
    }
    deliverRoomChests(room); // Deferred admission gets no retroactive update.
}

void Simulation::updateChestSupplies(float dt) {
    std::erase_if(chestSupplies,[&](auto &pickup) {
        if(pickup.room!=room)return false;
        pickup.timing.advance(dt);
        if(pickup.timing.phase==CoinTiming::Phase::Gone)return true;
        // Legacy explicit fixture actors; normal chest births use shared key/bomb actors.
        // Coin timing is an explicit presentation adapter, not key/bomb parity.
        int &amount=pickup.bomb?dynamite:keys;
        if(!pickup.timing.collectible()||amount>=(pickup.bomb?MaxDynamite:99)||player.totalHealth()<=0||
           planarDistance(player.position,pickup.position)>=1||!arena.clear(player.position,pickup.position,.1f))return false;
        ++amount;pickup.timing.collect();checkpointNeeded=true;return false;
    });
}
} // namespace dw
