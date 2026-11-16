#include "combat/Simulation.hpp"
#include "combat/ChestGeometry.hpp"
#include "combat/SourceRoomRewards.hpp"

namespace dw {
void Simulation::resolveRedHeartClearAward() {
    auto &progress=rooms[size_t(room)];
    // First-clear only. This delivery is ordinary opening-floor combat, excluding
    // bosses, story sites, tutorial and other special-room/reward policies.
    const auto &layout=arena.rooms[size_t(room)];
    if((!trinkets.clearRewards&&!redHeartClearRewards&&!coinClearRewards&&!chestClearRewards&&!keyClearRewards&&!bombClearRewards)||progress.redHeartAward||!progress.cleared||floor!=0||surveyTutorial||
       !arena.profile.active()||arena.theme!=MissionTheme::Canyon||layout.kind!=RoomKind::Combat||
       layout.story!=StoryRoom::None||debugScenario||progress.trapOnly||progress.plateObjective)return;
    // Explicit DW room-seed adapter, isolated from combat/loot/order of discovery.
    // The native descriptor seed mapping is not claimed by this conversion.
    Random seed(seed_^0x4845415254415744ULL^(uint64_t(room+1)*0x9e3779b97f4a7c15ULL));
    RedHeartClearAward result;result.seed=uint32_t(seed.next());if(!result.seed)result.seed=1;
    result.luck=player.attributes.luck;
    SourceAwardRng rng{result.seed};result.variant=sourceOrdinaryRoomAward(rng,result.luck);
    if(result.variant==10||result.variant==20||result.variant==30||result.variant==40) {
        // Ordinary native spawning draws the pickup init seed after selection
        // (7b903a..7b9064). Full native wrapper/placement remains unaccepted.
        result.pickupSeed=rng.next();
        const auto choice=sourceOrdinaryPickup(result.pickupSeed,result.variant,{});
        result.subtype=choice.subtype;
        result.pending=choice.resolved&&(result.variant==10
            ? redHeartClearRewards&&(choice.subtype==1||choice.subtype==2||choice.subtype==5)
            : result.variant==20?coinClearRewards&&sourceOrdinaryCoinValue(choice.subtype)>0
            : result.variant==30?keyClearRewards&&sourceOrdinaryKeyValue(choice.subtype)>0
            : bombClearRewards&&sourceOrdinaryBombValue(choice.subtype)>0);
    }
    if(result.variant==50) {
        result.pickupSeed=rng.next();result.subtype=1;result.pending=chestClearRewards;
    }
    if(result.variant==350) {
        result.pickupSeed=rng.next();result.subtype=sourceSupportedTrinket(result.pickupSeed);result.pending=trinkets.clearRewards;
        // Explicit fresh two-entry pool adapter; no complete native pool claim.
    }
    // Keep unsupported outcomes explicit; no reroll or substitute red heart.
    progress.redHeartAward=result;checkpointNeeded=true;
    deliverRedHeartClearAward();
}
void Simulation::deliverRedHeartClearAward() {
    auto &award=rooms[size_t(room)].redHeartAward;
    if(!award||!award->pending||award->delivered||dead||finished)return;
    const bool trinket=award->variant==350,coin=award->variant==20,chest=award->variant==50,key=award->variant==30,bomb=award->variant==40;
    if(chest?chests.size()>=128:(trinket?trinketPickups.size():bomb?bombPickups.size():key?keyPickups.size():coin?moneyPickups.size():heartPickups.size())>=1024)return;
    const auto &layout=arena.rooms[size_t(room)];
    const int amount=award->subtype==2?1:award->subtype==5?4:2;
    auto safe=[&](Vector3 at) {
        if(arena.roomAt(at)!=room||arena.blocked(at,chest?chestGeometry::PlacementRadius:.35f)||arena.reservedSupplyCache(at,.5f))return false;
        if(chest) {
            const auto body=chestGeometry::body(at);
            if(sphereBox(player.position,chestGeometry::PlayerRadius+.05f,body))return false;
            for(const auto &enemy:roomEnemies(room))if(enemy.alive&&sphereBox(enemy.position,enemy.radius+.05f,body))return false;
            for(const auto &pickup:moneyPickups)if(sphereBox(pickup.position,.4f,body))return false;
            for(const auto &pickup:heartPickups)if(sphereBox(pickup.position,.4f,body))return false;
            for(const auto &pickup:chestSupplies)if(sphereBox(pickup.position,.4f,body))return false;
            for(const auto &pickup:bombPickups)if(sphereBox(pickup.position,.4f,body))return false;
            for(const auto &pickup:keyPickups)if(sphereBox(pickup.position,.4f,body))return false;
            for(const auto &key:arena.keys)if(!key.collected&&sphereBox(key.position,.6f,body))return false;
        }
        for(int p:layout.passages) {
            const auto &passage=arena.passages[size_t(p)];
            if(sphereBox(at,.5f,passage.gates[0])||sphereBox(at,.5f,passage.gates[1]))return false;
        }
        return !arena.path(player.position,at,.48f).empty();
    };
    auto position=layout.center;float best=std::numeric_limits<float>::infinity();
    if(safe(position))best=0;
    if(best!=0)for(const auto &cell:arena.floorCells) {
        const Vector3 at{(cell.first+.5f)*FloorTile,.85f,(cell.second+.5f)*FloorTile};
        const auto score=planarDistance(at,layout.center);
        if(score<best&&safe(at)){best=score;position=at;}
    }
    if(!std::isfinite(best))return;
    if(chest) {
        if(!spawnChest(position,award->pickupSeed))return;
    } else if(trinket) {
        if(!spawnTrinket(position,{"isaac",ItemKind::Trinket,uint32_t(award->subtype)},award->pickupSeed))return;
    } else if(bomb) {
        if(!spawnOrdinaryBomb(position,award->subtype,award->pickupSeed))return;
    } else if(key) {
        if(!spawnOrdinaryKey(position,award->subtype,award->pickupSeed))return;
    } else if(coin) {
        MoneyPickup pickup{position,sourceOrdinaryCoinValue(award->subtype),0,true};
        pickup.sourceSubtype=award->subtype;pickup.room=room;pickup.timing.appear(1);
        moneyPickups.push_back(pickup);
    } else {
        if(!spawnHeartPickup(HeartKind::Red,position,amount))return;
        heartPickups.back().sourceSubtype=award->subtype;
        heartPickups.back().timing.appear(redHeartAppearanceSpeed);
    }
    award->pending=false;award->delivered=true;checkpointNeeded=true;
}
} // namespace dw
