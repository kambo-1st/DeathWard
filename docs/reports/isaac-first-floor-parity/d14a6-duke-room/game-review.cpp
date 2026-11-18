#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "world/SourcePropRooms.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
int main(){try {
    SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Recorded Duke room verification");SetTargetFPS(0);
    const auto root=std::filesystem::path("/tmp")/("deathward-recorded-duke-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a6-duke-room");
    auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json",defaultMechanics()->fingerprint());
    preset.seededBosses=false;preset.monstro.enabled=true;preset.duke.enabled=true;preset.bossRewardItem=255;
    preset.save(report/"review-preset.json");
    Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText="11";game.reviewSourceRoomTemplate=RecordedDukeRoom;game.nextBalancePreset=preset;game.launch(true);
    check(game.run&&game.error.empty(),"normal main-game direct entry");
    auto &s=*game.run;
    check(s.room==s.finalRoom()&&s.enemies.size()==2&&s.player.hp==6&&!s.godMode,"real generated boss room with initial fly and normal health");
    check(game.balancePreset.defaultZoomPercent==165&&game.balancePreset.playerSpeed==preset.playerSpeed&&game.balancePreset.shotSpeed==preset.shotSpeed&&game.balancePreset.routeLengthScale==preset.routeLengthScale,"accepted player/shooting/map/view settings preserved");
    int rocks=0,poop=0;for(const auto &p:s.arena.breakables)if(p.room==s.room){rocks+=p.kind==BreakableKind::CrackedRock;poop+=p.kind==BreakableKind::Dung;}
    check(rocks==4&&poop==2,"actual Game admits six recorded props");
    game.updateCamera(10);Renderer renderer;
    auto frame=[&]{game.update(Tick);BeginDrawing();auto action=renderer.draw(game);EndDrawing();game.perform(action);};
    auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
    auto capture=[&](const char *name){BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"Renderer capture");UnloadImage(im);EndDrawing();};
    frame();capture("encounter.png");
    game.perform(Action::OpenBalance);game.perform(Action::BalanceEnemiesTab);game.perform(Action::BalanceMonstroTab);frame();
    auto boss=std::find_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return bool(e.duke);})->id;
    s.findEnemy(boss)->hp*=.75f;const auto phase=s.findEnemy(boss)->duke->frame;
    game.balanceDraft.roomSizeScale=1.11f;click(800,295);
    check(std::abs(s.dukeTuning.health-(preset.duke.health-.05f))<.0001f&&std::abs(s.findEnemy(boss)->hp/s.findEnemy(boss)->maxHp-.75f)<.0001f&&s.findEnemy(boss)->duke->frame==phase,"mouse live Duke HP preserves injury/phase");
    check(s.roomSizeScale==preset.roomSizeScale&&game.balanceDraft.roomSizeScale==1.11f,"live edit preserves pending map change");capture("tuning.png");
    game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);
    auto exported=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());
    check(exported.duke==s.dukeTuning&&exported.bossRewardItem==255&&exported.roomProps.layouts==1&&exported.roomSizeScale==1.11f,"export/remember include selected content and live/staged settings");
    game.perform(Action::ResetMonstro);game.perform(Action::LoadBalance);
    check(game.run->dukeTuning==exported.duke&&game.run->roomSizeScale==preset.roomSizeScale,"load applies live values, keeps map edits staged");
    game.perform(Action::PropsOff);check(game.run->enemies.size()==2&&game.run->arena.rooms.back().sourceCombatTemplate==RecordedDukeRoom,"prop OFF remains pending");game.perform(Action::ApplyMapChanges);
    check(game.error.empty()&&game.run->arena.rooms.back().sourceCombatTemplate<0&&game.run->enemies.size()==1,"Apply restores existing bare Duke arena");
    game.perform(Action::PropsSource);check(game.run->enemies.size()==1,"source restore staged");game.perform(Action::ApplyMapChanges);
    check(game.error.empty()&&game.run->arena.rooms.back().sourceCombatTemplate==RecordedDukeRoom&&game.run->enemies.size()==2,"Apply restores full arrangement");
    game.perform(Action::CloseBalance);game.paused=false;game.perform(Action::RetryExpedition);
    check(game.error.empty()&&game.run->room==game.run->finalRoom()&&game.run->enemies.size()==2&&game.run->player.hp==6&&!game.run->godMode&&game.run->dukeTuning==exported.duke,"retry returns directly with normal health and selected settings");
    game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->duke==exported.duke,"fresh Game remembers configuration");fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="11";fresh.reviewSourceRoomTemplate=RecordedDukeRoom;fresh.launch(true);
    check(fresh.run&&fresh.error.empty()&&fresh.run->enemies.size()==2&&fresh.run->room==fresh.run->finalRoom(),"fresh expedition loads the recorded arrangement");fresh.close();CloseWindow();
    std::cout<<"PASS Game/Renderer source2012 room9, six props, normal health/165% zoom, mouse live HP, staged Apply, export/load/remember, retry and fresh launch\n";return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
