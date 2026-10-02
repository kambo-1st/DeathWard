#include "world/ArrivalQuest.hpp"
#include "raymath.h"
#include <stdexcept>

namespace dw {
namespace {
constexpr const char *Flags[]={"redstone.arrived", "redstone.evening_conductor", "redstone.slept",
    "redstone.morning_conductor", "redstone.daughter_missing", "redstone.search_started"};
}
ArrivalStage ArrivalQuest::stage(const WorldState &world) {
    // Require the complete prefix; unrelated/debug flags cannot skip a conversation.
    int completed=0;
    for(const auto *flag:Flags) {if(!world.flags.contains(flag))break;++completed;}
    return ArrivalStage(completed);
}
void ArrivalQuest::begin(CampaignStore &campaign) {
    if(stage(campaign.data().world)==ArrivalStage::None)campaign.setFlag(Flags[0],true);
}
void ArrivalQuest::advance(CampaignStore &campaign, ArrivalStage expected) {
    if(stage(campaign.data().world)!=expected)throw std::runtime_error("That quest action is no longer available.");
    const int next=int(expected);
    if(next>0&&next<int(std::size(Flags)))campaign.setFlag(Flags[next],true);
}
std::vector<QuestLine> ArrivalQuest::dialogue(ArrivalStage at) {
    switch(at) {
    case ArrivalStage::Conductor:return {
        {"YOU","When will we be leaving? How long will it take to clear the tracks?"},
        {"CONDUCTOR","Probably tomorrow morning, if the wind lets up. The crew can't keep ahead of the sand tonight."},
        {"CONDUCTOR","Sun's already going down. The camp has a spare tent for passengers. Get some sleep; come find me in the morning."}};
    case ArrivalStage::Tent:return {{"PASSENGER TENT","An empty bedroll waits beneath the canvas. Outside, the light is fading and sand rattles against the tent. Rest until morning?"}};
    case ArrivalStage::MorningConductor:return {
        {"YOU","Morning. Are we leaving soon?"},
        {"CONDUCTOR","I wish I could tell you. The line is still buried, and nobody will give me a time."},
        {"CONDUCTOR","Something else is wrong. The fort commander has been questioning everyone at the gate since dawn. You should speak to him."}};
    case ArrivalStage::Commander:return {
        {"YOU","The conductor said you were looking for someone."},
        {"COMMANDER","My daughter. She left alone before first light. Nobody can tell me whether she slipped out in the night or just before dawn."},
        {"COMMANDER","The gate watch saw someone taking the badlands trail. My soldiers are scattered keeping this camp together."},
        {"YOU","I'll follow the trail and look for her."},
        {"COMMANDER","Start beyond the barricade. Keep your bearings in the storm, and come back if the way closes. Please find her."}};
    case ArrivalStage::Trail:
    case ArrivalStage::Searching:return {{"THE BADLANDS","The commander's daughter went this way alone. Leave the camp and follow her trail into the storm?"}};
    default:return {};
    }
}
void ArrivalQuest::locate(const TownDocument &scene, const HubWorld &ground) {
    conductor={};conductor.id="quest-conductor";conductor.model="conductor";
    conductor.position=add(ground.spawn,{-3,0,-2});conductor.yaw=75;conductor.speed=0;
    // An editor-authored conductor takes precedence over the prototype placement.
    for(const auto &c:scene.characters)if(c.id=="quest-conductor")conductor=c;
    tent_.reset();bedApproach_.reset();
    for(const auto &i:scene.instances)if(i.id.starts_with("story-settler-tent-0:")) {
        tent_=Vector3Transform({},i.transform);
        bedApproach_=Vector3Transform({0,0,3.4f},i.transform);break;
    }
}
std::optional<QuestMarker> ArrivalQuest::marker(const WorldState &world, const TownCharacters &residents,
                                               const HubWorld &ground) const {
    const auto at=stage(world);
    QuestMarker result;
    if(at==ArrivalStage::Conductor||at==ArrivalStage::MorningConductor) {
        result={at==ArrivalStage::Conductor?"STRANDED AT REDSTONE":"STILL NO DEPARTURE",
                at==ArrivalStage::Conductor?"Ask the conductor when the train will leave.":"Ask the conductor about today's departure.",
                "Talk to conductor","!",conductor.position,conductor.position};
        for(const auto &resident:residents.residents())if(resident.definition.id=="quest-conductor")
            result.position=result.approach=resident.position;
    } else if(at==ArrivalStage::Tent) {
        if(!tent_||!bedApproach_)return {};
        result={"A BED FOR THE NIGHT","Sleep in the passenger tent before morning.","Rest in tent","Z",*tent_,*bedApproach_};
    } else if(at==ArrivalStage::Commander) {
        const auto &people=residents.residents();
        const auto it=std::find_if(people.begin(),people.end(),[](const auto &c){return c.definition.id=="story-commander";});
        if(it==people.end())return {};
        result={"TROUBLE AT THE FORT","Find out what is troubling the commander.","Talk to commander","!",it->position,it->position};
    } else if(at>=ArrivalStage::Trail) {
        result={"BEFORE FIRST LIGHT","Follow the missing daughter's trail into the badlands.",
                at==ArrivalStage::Trail?"Follow the trail":"Continue the search",">",ground.mission,ground.mission};
    } else return {};
    const float y=ground.height(result.position), approachY=ground.height(result.approach);
    if(std::isfinite(y))result.position.y=y;
    if(std::isfinite(approachY))result.approach.y=approachY;
    return result;
}
}
