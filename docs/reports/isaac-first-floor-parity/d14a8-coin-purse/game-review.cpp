#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
#include <numeric>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
int main(int argc,char **argv){try{
    check(argc>1,"natural shop seed required");SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Coin Purse verification");SetTargetFPS(0);
    const auto root=std::filesystem::path("/tmp")/("deathward-purse-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a8-coin-purse");
    auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a7/campaign.save.balance/export.json",defaultMechanics()->fingerprint());preset.save(report/"review-preset.json");
    Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText=argv[1];game.reviewShopStock=true;game.nextBalancePreset=preset;game.launch(true);
    check(game.run&&game.error.empty(),"main-game shop launched");const int room=game.run->room;const auto mapping=game.run->pills.effects;
    check(game.run->shopUpgradeItem==195&&game.run->shopPrice(15,game.run->shopUpgradeSlot)==15&&!game.run->godMode&&game.run->player.hp==4&&game.run->money()==20,"natural purse / explicit stock review inventory");
    Renderer renderer;game.updateCamera(10);
    auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);};
    auto key=[&](int key){PlayAutomationEvent({0,2,{key,0,0,0}});frame();PlayAutomationEvent({0,1,{key,0,0,0}});frame();};
    auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
    auto capture=[&](const char *name){BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"screen capture");UnloadImage(im);EndDrawing();};
    frame();capture("shop.png");game.run->player.position=game.run->shopUpgradePosition();frame();check(game.run->shopUpgradeSold&&game.run->money()==5&&game.run->pillPickups.size()==4,"Game update buys once and spawns four");
    for(int n=0;n<80;++n)frame();
    capture("four-pills.png");
    const auto first=game.run->pillPickups[0].position;const int color=game.run->pillPickups[0].color;game.run->player.position=first;frame();check(game.run->pills.held==color&&!game.run->pills.known(color),"unknown held slot in actual Game");capture("held-pill.png");
    key(KEY_H);check(game.run->pills.held==0,"default H drop key");for(int n=0;n<80;++n)frame();check(game.run->pills.held==0,"no immediate recollection");game.run->player.position.x+=3;frame();game.run->player.position=first;frame();check(game.run->pills.held==color,"walk away and recollect");
    key(KEY_F);check(!game.run->pills.held&&game.run->pills.known(color),"default F use identifies");const auto counts=game.run->pills.consumed;check(std::accumulate(counts.begin(),counts.end(),0)==1,"exact one consumption");
    game.perform(Action::OpenBalance);game.perform(Action::BalanceShootingTab);frame();click(1005,267);check(game.balancePillsOpen,"mouse opens pill tuning");game.balanceDraft.roomSizeScale=1.11f;click(960,252);click(805,309);click(400,370);
    check(game.run->pillTuning.purseCount==5&&std::abs(game.run->pillTuning.statStrength-.95f)<.0001f&&game.run->pillTuning.binding==1&&game.run->roomSizeScale==preset.roomSizeScale,"live count/strength/key, map stays pending");
    bool keyboard=false;for(int n=0;n<40&&!keyboard;++n){PlayAutomationEvent({0,2,{KEY_DOWN,0,0,0}});frame();keyboard=game.keyboardFocus()==Action::PillStrengthDown;PlayAutomationEvent({0,1,{KEY_DOWN,0,0,0}});frame();}check(keyboard,"keyboard reaches pill tuning");capture("tuning.png");
    game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);auto exported=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(exported.pills==game.run->pillTuning&&exported.roomSizeScale==1.11f&&exported.defaultZoomPercent==165,"export includes staged map and pills");
    click(365,485);check(game.run->pillTuning==PillTuning{},"reset mouse");game.perform(Action::LoadBalance);check(game.run->pillTuning==exported.pills&&game.run->roomSizeScale==preset.roomSizeScale,"load live pills, pending map");
    game.run->pills.held=color;game.perform(Action::ApplyMapChanges);check(game.error.empty()&&game.run->pills.consumed==counts&&game.run->pills.effects==mapping&&game.run->pills.held==color,"Apply keeps consumable and permanent pill effects");
    game.perform(Action::CloseBalance);game.paused=false;game.run->player.position=add(game.run->arena.rooms[size_t(room)].center,{0,0,4});key(KEY_COMMA);check(game.run->pills.held==0,"alternate comma drop key");game.run->pills.held=color;key(KEY_N);check(!game.run->pills.held,"alternate N use key");
    game.run->dead=true;game.run->player.hp=0;game.perform(Action::RetryExpedition);check(game.error.empty()&&game.run->room==room&&game.run->pills.held==0&&game.run->pills.effects==mapping&&!game.run->pills.known(color)&&game.run->pills.consumed==std::array<int,50>{}&&game.run->pillTuning==exported.pills,"retry returns unpurchased with clean pill history and retained tuning");
    game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->pills==exported.pills,"remembered next expedition");fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=argv[1];fresh.reviewShopStock=true;fresh.launch(true);check(fresh.run&&fresh.error.empty()&&fresh.run->pillTuning==exported.pills&&fresh.run->shopUpgradeItem==195,"fresh Game launch");fresh.close();CloseWindow();
    std::cout<<"PASS Game/Renderer natural shop seed="<<argv[1]<<" room="<<room+1<<", four pills, unknown/use/drop/default+alternate keys, mouse/keyboard tuning, export/load/remember, staged Apply and retry\n";return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
