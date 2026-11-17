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
    const float after=std::max(0.f,player.maxHp-2);
    const auto &definition=itemDefinition(item,*content);
    return definition.pickupHealthMultiplier!=1&&after>0?
        std::min(float(player.sourceHealth().limit()),std::max(2.f*std::floor(std::clamp(definition.pickupHealthFloor,2.f,24.f)/2),2.f*std::floor(after*definition.pickupHealthMultiplier/2))):after;
}
ServiceOffer Simulation::serviceOffer(int index) const {
    if(index<0||index>=2)return {};
    switch(arena.rooms[size_t(room)].service) {
    case RoomService::Surgeon:
        return index==0?ServiceOffer{"Treat wounds","Restore up to three red hearts. Keep your containers. One treatment per floor.","20 COINS"}:
            ServiceOffer{"Strengthening tonic","Gain one filled red-heart container for this expedition. One tonic per floor.","35 COINS"};
    case RoomService::Smuggler: {
        const auto &item=itemDefinition(rooms[size_t(room)].offers[size_t(index)],*content);
        const float after=bargainMaxHealth(index);
        const auto preview="Red containers "+hpText(player.maxHp/2)+" -> "+hpText(after/2)+".";
        return {item.name,std::string(item.description)+" "+preview,
            player.maxHp>0?"1 RED CONTAINER":player.boneHearts>0?"1 BONE CONTAINER":"3 SOUL HEARTS"};
    }
    default:return {};
    }
}
std::string Simulation::serviceUnavailable(int index) const {
    if(index<0||index>=2||!shopOpen||arena.rooms[size_t(room)].kind!=RoomKind::Service||
       !roomClear||roomThreats()||dead||finished||player.totalHealth()<=0||
       distance(player.position,arena.rooms[size_t(room)].objective)>2.6f||
       !arena.sight(player.position,arena.rooms[size_t(room)].objective))return "TRADE CLOSED";
    if(rooms[size_t(room)].serviceSold[size_t(index)])return "ALREADY USED";
    switch(arena.rooms[size_t(room)].service) {
    case RoomService::Surgeon:
        if(money()<uint64_t(index?35:20))return "NOT ENOUGH COINS";
        if(index==0&&player.hp>=player.redHealthCapacity())return "HEALTH FULL";
        if(index==1&&player.redHealthCapacity()>=24-2*player.brokenHearts)return "MAX HEALTH LIMIT";
        break;
    case RoomService::Smuggler:
        if(items.size()>=256)return "INVENTORY FULL";
        if(!canPayHealthCost(1))return "NEED 1 RED CONTAINER OR 3 SOUL HEARTS";
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
    case RoomService::Surgeon:
        moneySpent+=index?35:20;
        if(index)addRedContainers(2,true);
        else collectHeart(HeartKind::Red,6);
        break;
    case RoomService::Smuggler:
        progress.serviceSold={true,true}; // Mutually exclusive bargain, never two rerolls.
        payHealthCost(1);
        grant(progress.offers[size_t(index)]); // Applies the item's additional health rule.
        break;
    default:return false;
    }
    if(player.totalHealth()<=0) {
        shopOpen=false;
        if(!tryRevivePlayer()) {
            dead=true;audioCues.push(AudioCueKind::PlayerDeath,player.position);
        }
    }
    audioCues.push(AudioCueKind::Pickup,player.position);checkpointNeeded=true;
    return true;
}
} // namespace dw
