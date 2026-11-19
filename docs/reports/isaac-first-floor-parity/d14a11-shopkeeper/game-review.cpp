#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "world/SourceRecordedShop.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
int main(){try{
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Keeper verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-keeper-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a11-shopkeeper");
 auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a10/campaign.save.balance/export.json",defaultMechanics()->fingerprint());preset.save(report/"review-preset.json");
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText="6";game.reviewShopStock=true;game.nextBalancePreset=preset;game.launch(true);check(game.run&&game.error.empty(),"Game launch");
 Renderer renderer;game.updateCamera(10);const int shop=game.run->room;
 auto frame=[&]{game.update(Tick);BeginDrawing();auto a=renderer.draw(game);EndDrawing();game.perform(a);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto ticks=[&](int n){for(int i=0;i<n;++i)game.update(Tick);};
 auto key=[&](int k){PlayAutomationEvent({0,2,{k,0,0,0}});frame();PlayAutomationEvent({0,1,{k,0,0,0}});frame();};
 auto capture=[&](const char *name){if(!game.balanceOpen){game.run->player.position=shopCartGeometry::reviewStart(game.run->arena.rooms[size_t(shop)].center);game.updateCamera(10);}BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"screenshot");UnloadImage(im);EndDrawing();};
 frame();capture("before.png");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceRewardsTab);game.perform(Action::BalanceShopTab);frame();click(1010,189);frame();
 check(game.balanceKeeperOpen&&game.balanceShopOpen,"keeper page available");
 game.perform(Action::ToggleKeeperDestruction);check(!game.run->keeperTuning.destructible,"destruction live toggle");game.perform(Action::ToggleKeeperDestruction);
 game.perform(Action::CycleKeeperOutcome);game.perform(Action::CycleKeeperOutcome);check(game.run->keeperTuning.outcome==2,"live coin test selection");capture("tuning.png");
 game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);auto saved=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(saved.keeper.outcome==2&&saved.defaultZoomPercent==165&&saved.pills==preset.pills,"schema56 export");
 game.perform(Action::ResetKeeper);game.perform(Action::LoadBalance);check(game.run->keeperTuning.outcome==2&&!game.run->arena.rooms[size_t(shop)].keeper.destroyed,"preset load changes next destruction only");
 game.perform(Action::CloseBalance);game.paused=false;
 auto blast=[&]{auto &r=game.run->arena.rooms[size_t(shop)];game.run->player.position=add(r.center,{0,.85f,shopCartGeometry::HalfDepth+.65f});const int bombs=game.run->dynamite;key(KEY_B);check(game.run->dynamite==bombs-1,"actual B key places bomb");game.run->player.position=r.entry;ticks(110);check(r.keeper.destroyed&&!game.run->arena.blocked(add(r.center,{0,.85f,0}),.48f),"destroyed physical wagon");};
 blast();ticks(80);check(std::count_if(game.run->moneyPickups.begin(),game.run->moneyPickups.end(),[&](const auto &p){return p.room==shop;})==2,"two coin outcome");capture("coins.png");
 game.run->enterRoom(0);game.run->enterRoom(shop);frame();check(std::count_if(game.run->moneyPickups.begin(),game.run->moneyPickups.end(),[&](const auto &p){return p.room==shop;})==2&&game.run->arena.rooms[size_t(shop)].keeper.destroyed,"revisit coins/collision persist");
 game.run->player.position=game.run->shopUpgradePosition();frame();check(game.run->shopUpgradeSold&&game.run->money()==5,"purchase still works after keeper destruction");
 for(int mode:{3,4}){
  game.perform(Action::OpenBalance);game.perform(Action::CycleKeeperOutcome);check(game.run->keeperTuning.outcome==mode,"next outcome selected");const bool destroyed=game.run->arena.rooms[size_t(shop)].keeper.destroyed;check(destroyed,"tuning cannot resurrect keeper");
  game.perform(Action::BalanceWorldTab);game.perform(Action::RoomSizeUp);game.perform(Action::ApplyMapChanges);check(!game.run->arena.rooms[size_t(shop)].keeper.destroyed&&game.run->keeperTuning.outcome==mode,"Apply fresh keeper with retained live settings");game.perform(Action::CloseBalance);game.paused=false;game.run->dynamite=3;
  blast();ticks(60);
  if(mode==3){check(std::count_if(game.run->enemies.begin(),game.run->enemies.end(),[](auto &e){return e.keeperSpawn&&e.alive;})==2,"two spider outcome");game.run->enterRoom(0);game.run->enterRoom(shop);check(game.run->enemies.size()==2,"spiders survive room travel");capture("spiders.png");}
  else {check(game.run->machineCollectibles.size()==1&&game.run->machineCollectibles.front().item==64,"Steam Sale pickup");capture("steam-sale.png");game.run->player.position=game.run->machineCollectibles.front().position;frame();check(game.run->itemStacks({"isaac",ItemKind::Collectible,64})==1,"Steam Sale collected");}
 }
 game.run->dead=true;game.run->player.hp=0;game.perform(Action::RetryExpedition);check(game.run&&game.error.empty()&&!game.run->arena.rooms[size_t(shop)].keeper.destroyed&&game.run->items.empty(),"retry fresh keeper/build");
 game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->keeper.outcome==2&&fresh.nextBalancePreset->defaultZoomPercent==165,"remembered next expedition keeper settings");fresh.close();CloseWindow();
 std::cout<<"PASS actual Game/Renderer B-key blast, coin/spider/Steam Sale outcomes, post-destruction purchase, revisit, live UI, schema56 export/load/remember, Apply and retry\n";return 0;
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
