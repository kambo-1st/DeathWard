#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
int main(){try{
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Blood machine explosion verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-blood-blast-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a12-blood-machine-explosions");
 auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a11/campaign.save.balance/export.json",defaultMechanics()->fingerprint());preset.save(report/"review-preset.json");
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText="68";game.reviewShopStock=true;game.nextBalancePreset=preset;game.launch(true);check(game.run&&game.error.empty(),"Game launch");
 Renderer renderer;game.updateCamera(10);int shop=game.run->room;
 auto frame=[&]{game.update(Tick);BeginDrawing();auto a=renderer.draw(game);EndDrawing();game.perform(a);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto ticks=[&](int n){for(int i=0;i<n;++i)game.update(Tick);};
 auto key=[&](int k){PlayAutomationEvent({0,2,{k,0,0,0}});frame();PlayAutomationEvent({0,1,{k,0,0,0}});frame();};
 auto capture=[&](const char *name){game.updateCamera(10);BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"screenshot");UnloadImage(im);EndDrawing();};
 frame();game.perform(Action::OpenBalance);game.perform(Action::BalanceShootingTab);game.perform(Action::BalancePillsTab);game.perform(Action::BalanceTemperanceTab);frame();click(830,189);
 check(game.balanceBloodExplosionsOpen,"mouse opens explosions page");click(400,278);check(!game.run->bloodExplosionTuning.destructible,"live destruction toggle");click(400,278);click(800,278);check(!game.run->bloodExplosionTuning.rewards,"live drops toggle");click(800,278);
 click(500,345);click(500,345);check(game.run->bloodExplosionTuning.outcome==2,"live test heart outcome");bool keyboard=false;for(int n=0;n<30&&!keyboard;++n){key(KEY_DOWN);keyboard=game.keyboardFocus()==Action::CycleBloodExplosionOutcome;}check(keyboard,"keyboard reaches explosion test selection");capture("tuning.png");
 game.perform(Action::BalanceWorldTab);game.perform(Action::RoomSizeUp);const auto draft=game.balanceDraft.roomSizeScale;game.perform(Action::BalanceShootingTab);game.perform(Action::BalancePillsTab);game.perform(Action::BalanceTemperanceTab);game.perform(Action::BalanceBloodExplosionsTab);
 game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);auto saved=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(saved.bloodExplosions.outcome==2&&saved.defaultZoomPercent==165&&saved.pills==preset.pills,"schema57 export");
 game.perform(Action::ResetBloodExplosions);game.perform(Action::LoadBalance);check(game.run->bloodExplosionTuning.outcome==2&&game.balanceDraft.roomSizeScale==draft&&game.run->roomSizeScale==preset.roomSizeScale,"load preserves pending map edits");
 game.perform(Action::ResetBloodExplosions);game.perform(Action::CloseBalance);game.paused=false;
 game.run->player.position=game.run->shopCardPosition();frame();check(game.run->pills.held==TemperanceCard&&game.run->money()==15,"purchase Temperance");key(KEY_F);check(game.run->bloodMachines.size()==1,"F spawns machine");
 const auto at=game.run->bloodMachines.front().position;game.run->player.position=add(at,{0,0,1.6f});check(!game.run->arena.blocked(game.run->player.position,.48f),"bomb placement clear");capture("before.png");
 auto expectedSeed=game.run->bloodMachines.front().rng;const auto expected=sourceBloodExplosionDrops(expectedSeed);const auto bombs=game.run->dynamite;key(KEY_B);check(game.run->dynamite==bombs-1,"B places real bomb");game.run->player.position=game.run->arena.rooms[size_t(shop)].entry;ticks(110);
 check(game.run->bloodMachines.front().blastDestroyed&&!game.run->arena.blocked(at,.48f),"blast destroys physical machine");check(game.run->bloodMachines.front().blastDrops.count==expected.count&&game.run->bloodMachines.front().rng==expectedSeed,"source outcome unchanged by UI testing");game.run->player.position=add(at,{0,0,3});capture("destroyed.png");
 const auto delivered=game.run->bloodMachines.front().blastDelivered;game.run->enterRoom(0);game.run->enterRoom(shop);frame();check(game.run->bloodMachines.front().blastDestroyed&&game.run->bloodMachines.front().blastDelivered==delivered,"revisit retains destruction and resolved identity");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceShootingTab);game.perform(Action::BalancePillsTab);game.perform(Action::BalanceTemperanceTab);game.perform(Action::BalanceBloodExplosionsTab);game.perform(Action::CycleBloodExplosionOutcome);check(game.run->bloodMachines.front().blastDestroyed,"edit cannot resurrect");game.perform(Action::BalanceWorldTab);game.perform(Action::ApplyMapChanges);check(game.run->bloodMachines.empty()&&game.run->bloodExplosionTuning.outcome==1,"Apply clears actors and retains tuning");
 game.perform(Action::CloseBalance);game.paused=false;game.run->dead=true;game.run->player.hp=0;game.perform(Action::RetryExpedition);check(game.run&&game.error.empty()&&game.run->bloodMachines.empty()&&game.run->bloodExplosionTuning.outcome==1,"retry keeps settings, fresh actors");
 game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->bloodExplosions.outcome==2&&fresh.nextBalancePreset->defaultZoomPercent==165,"remembered next expedition settings");fresh.close();CloseWindow();
 std::cout<<"PASS actual Game/Renderer mouse controls, F/B keys, native drops, collision, revisit, export/load/remember, staged Apply and retry; natural drop actors="<<expected.count<<'\n';return 0;
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
