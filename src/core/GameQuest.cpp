#include "core/Game.hpp"
#include "raymath.h"

namespace dw {
std::vector<StoryEvidence> Game::journalEntries() const {
    std::vector<StoryEvidence> entries;
    auto include=[&](const auto &records) {
        for(const auto &record:records) {
            const auto it=std::find_if(entries.begin(),entries.end(),[&](const auto &e){return e.room==record.room&&e.account==record.account;});
            if(it==entries.end())entries.push_back(record);else *it=record;
        }
    };
    for(const auto &history:campaign.data().history)include(history.evidence);
    if(run)include(run->evidence);
    return entries;
}
void Game::configureArrival(const TownDocument &document) {
    questDialogue_.clear();walkingToQuest_=false;sleepTime_=-1;
    TownDocument cast;
    if(activeHub==HubKind::Redstone) {
        ArrivalQuest::begin(campaign);
        arrival_.locate(document,town);
        if(std::none_of(document.characters.begin(),document.characters.end(),[](const auto &c){return c.id=="quest-conductor";}))
            cast.characters.push_back(arrival_.conductor);
        sandstorm=true;
    }
    questCharacters.reset(cast,town);
}
std::optional<QuestMarker> Game::questMarker() const {
    return arrivalActive()?arrival_.marker(campaign.data().world,characters,town):std::nullopt;
}
Vector2 Game::questMarkerScreen() const {
    const auto marker=questMarker();if(!marker)return {};
    auto p=GetWorldToScreen(add(marker->position,{0,3.4f,0}),camera);
    p.x*=1280.f/GetScreenWidth();p.y*=800.f/GetScreenHeight();
    // Keep distant objectives usable at the edge of the view, clear of HUD panels.
    const float minimumY=campaign.data().world.flags.contains("redstone.survey_recovered")?300.f:260.f;
    return {std::clamp(p.x,125.f,1155.f),std::clamp(p.y,minimumY,590.f)};
}
const QuestLine *Game::questLine() const {
    return questLine_<questDialogue_.size()?&questDialogue_[questLine_]:nullptr;
}
bool Game::nearQuest(const QuestMarker &marker) const {
    const auto groundPosition=sub(town.player.position,{0,.85f,0});
    return distance(groundPosition,marker.approach)<=marker.radius&&town.canTraverse(groundPosition,marker.approach);
}
void Game::requestQuestAction() {
    if(screen!=Screen::Hub||paused||sleeping()||questDialogueOpen())return;
    const auto marker=questMarker();if(!marker)return;
    error.clear();walkingToMission=missionMenu=false;
    if(nearQuest(*marker)) {
        walkingToQuest_=false;town.stop();resetPointerInput();
        conversationStage_=arrivalStage();questDialogue_=ArrivalQuest::dialogue(conversationStage_);questLine_=0;
    } else {
        walkingToQuest_=town.moveTo(marker->approach);
        if(!walkingToQuest_)error="No clear route to this objective. Check its approach in the town editor.";
    }
}
void Game::nextQuestLine() {
    if(!questDialogueOpen()||sleeping())return;
    if(conversationStage_!=arrivalStage()) {questDialogue_.clear();return;}
    if(!questLastLine()) {++questLine_;return;}
    if(conversationStage_==ArrivalStage::Tent) {
        sleepTime_=0;town.stop();
    } else if(ArrivalQuest::ready(campaign.data().world)) {
        launch();
        if(!run)return;
    } else ArrivalQuest::advance(campaign,conversationStage_);
    questDialogue_.clear();resetPointerInput();
}
float Game::sleepFade() const {
    if(sleepTime_<0)return 0;
    return std::min(std::clamp(sleepTime_/.75f,0.f,1.f),std::clamp((3.2f-sleepTime_)/.85f,0.f,1.f));
}
bool Game::updateQuest(float dt) {
    if(sleeping()) {
        sleepTime_+=std::clamp(dt,0.f,.1f);
        if(sleepTime_>=1.15f&&arrivalStage()==ArrivalStage::Tent)
            ArrivalQuest::advance(campaign,ArrivalStage::Tent);
        if(sleepTime_>=3.2f)sleepTime_=-1;
        return true;
    }
    if(questDialogueOpen()) {
        if(IsKeyPressed(KEY_ESCAPE))perform(Action::QuestCancel);
        else if(IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_SPACE))perform(Action::QuestNext);
        return true;
    }
    return false;
}
}
