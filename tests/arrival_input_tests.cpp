#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
int main() {
    const auto save=std::filesystem::temp_directory_path()/("deathward-arrival-input-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".save");
    try {
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Arrival quest verification");SetExitKey(KEY_NULL);
        Game game(save,HubKind::Redstone);Renderer renderer;game.seedText="1866";
        std::filesystem::create_directories("artifacts/quest");
        auto event=[](unsigned type,int a,int b=0){PlayAutomationEvent({0,type,{a,b,0,0}});};
        auto frame=[&](bool render=true) {
            game.update(.1f);BeginDrawing();
            const auto action=render?renderer.draw(game):Action::None;
            EndDrawing();game.perform(action);
            if(!game.error.empty())throw std::runtime_error(game.error);
        };
        auto click=[&](float x,float y) {
            event(7,int(x),int(y));event(5,MOUSE_BUTTON_LEFT);frame();
            event(6,MOUSE_BUTTON_LEFT);frame();event(5,MOUSE_BUTTON_LEFT);frame();
        };
        auto key=[&](int k) {event(2,k);frame();event(1,k);frame();};
        auto walk=[&] {
            const auto marker=game.questMarkerScreen();click(marker.x,marker.y+45);
            for(int n=0;n<2000&&!game.questDialogueOpen();++n)frame(n%10==0);
            check(game.questDialogueOpen(),"clicking the marker walks to its target and opens dialogue");
        };
        auto capture=[&](const char *name) {
            BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
            ExportImage(image,(std::string("artifacts/quest/")+name+".png").c_str());UnloadImage(image);EndDrawing();
        };
        frame();check(game.arrivalStage()==ArrivalStage::Conductor,"Redstone begins at sunset with the conductor objective");
        walk();capture("evening-dialogue");
        const auto position=game.town.player.position;
        event(2,KEY_W);event(2,KEY_F4);frame();event(1,KEY_W);event(1,KEY_F4);frame();
        check(distance(position,game.town.player.position)<.001f&&!game.editorRequested,"dialogue captures movement and editor shortcuts");
        key(KEY_ESCAPE);check(!game.questDialogueOpen()&&game.arrivalStage()==ArrivalStage::Conductor,"cancelling a conversation does not finish it");
        walk();while(game.questDialogueOpen())click(790,708);
        check(game.arrivalStage()==ArrivalStage::Tent,"finishing the conductor's evening conversation unlocks the tent");
        CampaignStore savedNight(save);check(ArrivalQuest::stage(savedNight.data().world)==ArrivalStage::Tent,"the new objective saves immediately");
        walk();capture("tent-dialogue");
        click(790,708);check(game.sleeping(),"the tent action begins the overnight transition");
        for(int n=0;n<80&&game.sleeping();++n)frame(n%5==0);
        check(game.arrivalStage()==ArrivalStage::MorningConductor,"sleep advances to the next morning");capture("morning");
        walk();while(game.questDialogueOpen())click(790,708);
        check(game.arrivalStage()==ArrivalStage::Commander,"the morning conductor points to the fort commander");
        walk();capture("commander-dialogue");while(game.questDialogueOpen())click(790,708);
        check(game.arrivalStage()==ArrivalStage::Trail&&!game.run,"the commander unlocks the trail without launching remotely");
        walk();capture("trail-confirmation");click(790,708);
        check(game.run&&game.run->surveyTutorial&&game.run->arena.theme==MissionTheme::Canyon,
              "the trail confirmation enters a seeded canyon search");
        check(game.campaign.data().pending->expedition==SurveyExpeditionTitle&&game.arrivalStage()==ArrivalStage::Searching,
              "the search purpose and quest progress are checkpointed");capture("first-expedition");
        game.finish(EndReason::Retreat);game.perform(Action::Hub);frame();
        check(game.activeHub==HubKind::Redstone&&game.questMarker()->action=="Retry the recovery",
              "returning leaves the records unrecovered and permits another attempt");
        Game restored(save,HubKind::Redstone);check(restored.arrivalStage()==ArrivalStage::Searching,"reload retains completed conversations and morning");
        walk();while(game.questDialogueOpen())click(790,708);
        game.run->jumpDebug(game.run->finalRoom());game.run->player.position=game.run->surveyPosition();
        game.run->interact();frame();check(game.letterVisible(),"cache opens the letter reader");capture("eleanor-letter");
        const auto still=game.run->player.position;
        event(2,KEY_W);event(2,KEY_F7);frame();event(1,KEY_W);event(1,KEY_F7);frame();
        check(distance(still,game.run->player.position)==0&&game.letterVisible(),"letter captures movement and debug shortcuts");
        click(850,584);check(!game.letterVisible(),"letter close button returns to the expedition");
        game.run->player.position=game.run->arena.exit;game.run->interact();frame();
        check(game.screen==Screen::Summary,"the one-floor tutorial ends at its return lantern");
        game.perform(Action::Hub);frame();check(game.arrivalStage()==ArrivalStage::Report,"return unlocks the commander report");
        walk();while(game.questDialogueOpen())click(790,708);
        check(game.arrivalStage()==ArrivalStage::Complete,"commander report completes the tutorial");capture("documents-delivered");
        click(1000,240);check(game.letterVisible(),"the recovered letter can be reread in the fort");key(KEY_ESCAPE);
        Game finished(save,HubKind::Redstone);check(finished.arrivalStage()==ArrivalStage::Complete,"completed tutorial reloads");
        renderer.unload();CloseWindow();std::filesystem::remove(save);
        std::cout<<"PASS arrival input: marker walking, dialogue/cancel, modal input, sleep, morning, commander, generated search and return\n";
    } catch(const std::exception &e) {
        if(IsWindowReady())CloseWindow();std::filesystem::remove(save);std::cerr<<"FAIL "<<e.what()<<'\n';return 1;
    }
}
