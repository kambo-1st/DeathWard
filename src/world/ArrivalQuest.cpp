#include "world/ArrivalQuest.hpp"
#include "raymath.h"
#include <stdexcept>

namespace dw {
namespace {
constexpr const char *Flags[]={"redstone.arrived", "redstone.evening_conductor", "redstone.slept",
    "redstone.morning_conductor", "redstone.survey_requested", "redstone.search_started",
    "redstone.survey_recovered", "redstone.survey_reported", "redstone.rourke_heard",
    "redstone.rourke_departed", "redstone.rourke_returned", "redstone.eleanor_response"};
}
ArrivalStage ArrivalQuest::stage(const WorldState &world) {
    // Require the complete prefix; unrelated/debug flags cannot skip a conversation.
    int completed=0;
    for(const auto *flag:Flags) {
        const bool legacy=completed==4&&world.flags.contains("redstone.daughter_missing");
        if(!world.flags.contains(flag)&&!legacy)break;
        ++completed;
    }
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
        {"YOU","The conductor said you needed help."},
        {"COMMANDER","Silas Bell, the railroad surveyor, was found dead in the badlands. His daughter Eleanor is back at Fort Mercy. So are his guide and Lieutenant Mercer. Their accounts disagree."},
        {"COMMANDER","Some of Bell's survey records are still missing. The railroad needs them to inspect the route ahead, and I cannot spare soldiers while the storm threatens the camp."},
        {"COMMANDER","Start at the near survey camp beyond the barricade. Look for a leather document case. This is a short recovery trip; bring the papers back before you go farther."},
        {"YOU","I'll recover the records."}};
    case ArrivalStage::Trail:
    case ArrivalStage::Searching:return {{"THE LOST SURVEY","Bell's near survey camp lies beyond the barricade. Follow the trail, recover his records and return to Fort Mercy?"}};
    case ArrivalStage::Report:return {
        {"YOU","I recovered the survey sheets. There was a letter with them, signed Eleanor."},
        {"COMMANDER","These will help the railroad crew. Eleanor Bell is the surveyor's daughter. Keep her letter; we should ask her about it when she is ready."},
        {"YOU","She says the route was different from the one her father showed Mercer."},
        {"COMMANDER","That tells us what she wrote. It does not tell us why Bell changed course, or how he died."},
        {"COMMANDER","Caleb Rourke, their guide, is being held here. He is very willing to tell his version. We will need to listen carefully."}};
    case ArrivalStage::Complete:return {
        {"CALEB ROURKE","Bell hired me because I knew the northern badlands. Mercer didn't like taking directions from an outlaw. Bell cared more about reaching his survey line."},
        {"CALEB ROURKE","Then I saw the old army map. A payroll wagon, lost years ago. Your respectable surveyor was hunting money. I asked for my share."},
        {"YOU","And Bell died?"},
        {"CALEB ROURKE","He drew first. Shot after shot, across the dry creek. I gave him every chance to surrender. He died better than most men live."},
        {"CALEB ROURKE","Mercer had already run. Eleanor vanished. Follow the camp past the split rock and the old cutting. You'll see where it happened."},
        {"YOU","I'll follow the route you described. Your account will have to stand beside whatever I find."}};
    case ArrivalStage::RourkeTrail:
    case ArrivalStage::RourkeSearching:return {{"ROURKE'S ACCOUNT","Follow Rourke's account into the badlands? This journey crosses several floors of connected rooms. His camp, split rock, railway cutting and dry creek lie along the way."}};
    case ArrivalStage::EleanorResponse:return {
        {"ELEANOR BELL","What did Rourke say happened?"},
        {"YOU","A magnificent duel. Your father fired repeatedly. But his revolver had only one discharged chamber, and there were shots from a position Rourke never mentioned."},
        {"ELEANOR BELL","Of course that is how he tells it. That is exactly the man he wants to be."},
        {"YOU","The revolver could have been reloaded or handled afterward. It leaves questions, not a verdict."},
        {"ELEANOR BELL","There was no treasure. My father learned how Rourke guided claim jumpers through railroad land. That is why they argued. And my father was still alive when I came back."}};
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
        result={at==ArrivalStage::Conductor?"STRANDED AT FORT MERCY":"STILL NO DEPARTURE",
                at==ArrivalStage::Conductor?"Ask the conductor when the train will leave.":"Ask the conductor about today's departure.",
                "Talk to conductor","!",conductor.position,conductor.position};
        for(const auto &resident:residents.residents())if(resident.definition.id=="quest-conductor")
            result.position=result.approach=resident.position;
    } else if(at==ArrivalStage::Tent) {
        if(!tent_||!bedApproach_)return {};
        result={"A BED FOR THE NIGHT","Sleep in the passenger tent before morning.","Rest in tent","Z",*tent_,*bedApproach_};
    } else if(at==ArrivalStage::Commander||at==ArrivalStage::Report) {
        const auto &people=residents.residents();
        const auto it=std::find_if(people.begin(),people.end(),[](const auto &c){return c.definition.id=="story-commander";});
        if(it==people.end())return {};
        result={at==ArrivalStage::Report?"THE RECOVERED PAPERS":"TROUBLE AT THE FORT",
                at==ArrivalStage::Report?"Bring Bell's records and Eleanor's letter to the commander.":"Find out what is troubling the commander.",
                "Talk to commander","!",it->position,it->position};
    } else if(at==ArrivalStage::Complete||at==ArrivalStage::EleanorResponse) {
        const char *id=at==ArrivalStage::Complete?"story-outlaw":"story-wife";
        const auto &people=residents.residents();
        const auto it=std::find_if(people.begin(),people.end(),[&](const auto &c){return c.definition.id==id;});
        if(it==people.end())return {};
        result={at==ArrivalStage::Complete?"HE DIED FIGHTING":"ANOTHER ACCOUNT",
            at==ArrivalStage::Complete?"Hear Caleb Rourke's account in the holding yard.":"Ask Eleanor about Rourke's account and the recovered evidence.",
            at==ArrivalStage::Complete?"Talk to Rourke":"Talk to Eleanor","!",it->position,it->position};
    } else if(at==ArrivalStage::RourkeTrail||at==ArrivalStage::RourkeSearching) {
        result={"ROURKE'S ACCOUNT","Follow his route through the badlands. Examine the story sites along the way.",
            at==ArrivalStage::RourkeTrail?"Follow his account":"Retry his account",">",ground.mission,ground.mission};
    } else if(at==ArrivalStage::Trail||at==ArrivalStage::Searching) {
        result={"THE LOST SURVEY","Recover Bell's survey records from the near camp.",
                at==ArrivalStage::Trail?"Recover the records":"Retry the recovery",">",ground.mission,ground.mission};
    } else return {};
    const float y=ground.height(result.position), approachY=ground.height(result.approach);
    if(std::isfinite(y))result.position.y=y;
    if(std::isfinite(approachY))result.approach.y=approachY;
    return result;
}
}
