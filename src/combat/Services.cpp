#include "combat/Simulation.hpp"

namespace dw {
ServiceOffer Simulation::serviceOffer(int index) const {
    if(index<0||index>=2)return {};
    switch(arena.rooms[size_t(room)].service) {
    case RoomService::Surgeon:
        return index==0?ServiceOffer{"Treat wounds","Restore up to three red hearts. Keep your containers. One treatment per floor.","20 COINS"}:
            ServiceOffer{"Strengthening tonic","Gain one filled red-heart container for this expedition. One tonic per floor.","35 COINS"};
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
