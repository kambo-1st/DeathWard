#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <iomanip>
#include <sstream>

namespace dw {
namespace {
std::string hpText(float value) {
    std::ostringstream out;out<<std::fixed<<std::setprecision(2)<<value;
    auto text=out.str();while(text.ends_with('0'))text.pop_back();if(text.ends_with('.'))text.pop_back();return text;
}
}
float Simulation::bargainMaxHealth(int index) const {
    if(index<0||index>=2)return player.maxHp;
    const auto item=rooms[size_t(room)].offers[size_t(index)];
    const float after=player.maxHp-20;
    const auto &definition=itemDefinition(item,*content);
    return definition.pickupHealthMultiplier!=1?
        std::max(definition.pickupHealthFloor,after*definition.pickupHealthMultiplier):after;
}
ServiceOffer Simulation::serviceOffer(int index) const {
    if(index<0||index>=2)return {};
    switch(arena.rooms[size_t(room)].service) {
    case RoomService::Exchange:
        return index==0?ServiceOffer{"Three sticks","Trade two keys for three dynamite sticks. Keep keys for armories, or invest in demolition.","2 KEYS"}:
            ServiceOffer{"Sell one stick","Trade one dynamite stick for four coins. Each offer can be used once on this floor.","1 DYNAMITE"};
    case RoomService::Surgeon:
        return index==0?ServiceOffer{"Treat wounds","Restore up to 60 health. Keep your maximum health. One treatment per floor.","20 COINS"}:
            ServiceOffer{"Strengthening tonic","Gain 15 maximum health and restore up to 15 health for this expedition. One tonic per floor.","35 COINS"};
    case RoomService::Smuggler: {
        const auto &item=itemDefinition(rooms[size_t(room)].offers[size_t(index)],*content);
        const float after=bargainMaxHealth(index);
        const auto preview="Maximum HP "+hpText(player.maxHp)+" -> "+hpText(after)+". Current HP -> "+hpText(std::min(player.hp,after))+".";
        return {item.name,std::string(item.description)+" "+preview,
            hpText(player.maxHp-after)+" MAX HP TOTAL"+(item.pickupHealthMultiplier!=1?" (INCLUDES ITEM COST)":"")};
    }
    default:return {};
    }
}
std::string Simulation::serviceUnavailable(int index) const {
    if(index<0||index>=2||!shopOpen||arena.rooms[size_t(room)].kind!=RoomKind::Service||
       !roomClear||roomThreats()||dead||finished||player.hp<=0||
       distance(player.position,arena.rooms[size_t(room)].objective)>2.6f||
       !arena.sight(player.position,arena.rooms[size_t(room)].objective))return "TRADE CLOSED";
    if(rooms[size_t(room)].serviceSold[size_t(index)])return "ALREADY USED";
    switch(arena.rooms[size_t(room)].service) {
    case RoomService::Exchange:
        if(index==0) {
            if(keys<2)return "NEED 2 KEYS";
            if(dynamite>MaxDynamite-3)return "DYNAMITE FULL";
        } else {
            if(dynamite<1)return "NEED 1 DYNAMITE";
            if(money()>MaxMoney-4||moneyCollected>MaxMoney-4)return "WALLET FULL";
        }
        break;
    case RoomService::Surgeon:
        if(money()<uint64_t(index?35:20))return "NOT ENOUGH COINS";
        if(index==0&&player.hp>=player.maxHp)return "HEALTH FULL";
        if(index==1&&player.maxHp>1985)return "MAX HEALTH LIMIT";
        break;
    case RoomService::Smuggler:
        if(items.size()>=256)return "INVENTORY FULL";
        if(bargainMaxHealth(index)<20)return "KEEP AT LEAST 20 MAX HP";
        break;
    default:return "TRADE CLOSED";
    }
    return {};
}
bool Simulation::buyService(int index) {
    if(!serviceUnavailable(index).empty())return false;
    auto &progress=rooms[size_t(room)];
    progress.serviceSold[size_t(index)]=true;
    switch(arena.rooms[size_t(room)].service) {
    case RoomService::Exchange:
        if(index==0){keys-=2;dynamite+=3;}else{--dynamite;moneyCollected+=4;}
        break;
    case RoomService::Surgeon:
        moneySpent+=index?35:20;
        if(index)player.maxHp+=15;
        player.hp=std::min(player.maxHp,player.hp+(index?15:60));
        break;
    case RoomService::Smuggler:
        progress.serviceSold={true,true}; // Mutually exclusive bargain, never two rerolls.
        player.maxHp-=20;player.hp=std::min(player.hp,player.maxHp);
        grant(progress.offers[size_t(index)]); // Applies the item's additional health rule.
        break;
    default:return false;
    }
    audioCues.push(AudioCueKind::Pickup,player.position);checkpointNeeded=true;
    return true;
}
} // namespace dw
