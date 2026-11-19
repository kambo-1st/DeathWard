#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "world/SourceRecordedShop.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
int main(){try{
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Recorded shop verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-recorded-shop-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a10-recorded-shop");
 auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a9/campaign.save.balance/export.json",defaultMechanics()->fingerprint());preset.save(report/"review-preset.json");
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText="6";game.reviewShopStock=true;game.nextBalancePreset=preset;game.launch(true);
 check(game.run&&game.error.empty(),"Game launched");const int shop=game.run->room;
 auto rocks=[&]{return std::count_if(game.run->arena.breakables.begin(),game.run->arena.breakables.end(),[&](const auto &p){return p.room==shop&&!p.destroyed;});};
 check(game.run->arena.rooms[size_t(shop)].sourceShopTemplate==0&&rocks()==4&&game.run->player.hp==4&&game.run->money()==20&&!game.run->godMode,"genuine recorded shop with labelled review funds/health");
 Renderer renderer;game.updateCamera(10);
 auto frame=[&]{game.update(Tick);BeginDrawing();auto action=renderer.draw(game);EndDrawing();game.perform(action);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto key=[&](int k){PlayAutomationEvent({0,2,{k,0,0,0}});frame();PlayAutomationEvent({0,1,{k,0,0,0}});frame();};
 auto capture=[&](const char *name){BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"screenshot");UnloadImage(im);EndDrawing();};
 frame();capture("shop.png");
 auto walk=[&](Vector3 at){auto screen=GetWorldToScreen(at,game.camera);click(int(screen.x),int(screen.y));for(int n=0;n<600&&planarDistance(game.run->player.position,at)>1;++n)frame();};
 walk(game.run->shopUpgradePosition());check(game.run->shopUpgradeSold&&game.run->money()==5&&game.run->itemStacks({"isaac",ItemKind::Collectible,195})==1,"mouse buys Purse through Game");for(int n=0;n<85;++n)frame();capture("pills.png");
 const auto pill=std::find_if(game.run->pillPickups.begin(),game.run->pillPickups.end(),[](const auto &p){return !p.shopStock&&p.color>0;});check(pill!=game.run->pillPickups.end(),"Purse pills present");game.run->player.position=pill->position;frame();const int color=game.run->pills.held;key(KEY_F);check(color>0&&!game.run->pills.held&&game.run->pills.known(color),"purse pill use in recorded shop");
 walk(game.run->shopCardPosition());check(game.run->shopCardSold&&game.run->money()==0&&game.run->pills.held==TemperanceCard,"mouse buys Temperance");key(KEY_F);check(!game.run->pills.held&&game.run->bloodMachines.size()==1,"card safely spawns machine among shop props");capture("machine.png");
 auto prop=std::find_if(game.run->arena.breakables.begin(),game.run->arena.breakables.end(),[&](const auto &p){return p.room==shop;});const float half=(prop->bounds.max.x-prop->bounds.min.x)*.5f;game.run->player.position=add(prop->rewardPosition,{0,0,half+.65f});check(!game.run->arena.blocked(game.run->player.position,.48f)&&game.run->placeDynamite(),"place ordinary dynamite by shop rock");game.run->player.position=game.run->arena.rooms[size_t(shop)].entry;for(int n=0;n<100;++n)frame();check(rocks()<4,"real rock demolition");
 game.run->enterRoom(0);game.run->enterRoom(shop);frame();check(game.run->shopUpgradeSold&&game.run->shopCardSold&&game.run->money()==0&&rocks()<4&&game.run->bloodMachines.size()==1,"leave/revisit retains all purchased/destroyed actors");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceRewardsTab);game.perform(Action::BalanceRoomHeartsTab);frame();game.perform(Action::RoomHeartsOff);check(game.hasPendingMapChanges()&&game.run->arena.rooms[size_t(shop)].sourceShopTemplate==0,"SOURCE edits staged");
 game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);const auto off=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(off.roomHeartLayouts==0&&off.defaultZoomPercent==165&&off.temperance==preset.temperance,"schema55 exports pending choice with accepted settings");
 game.perform(Action::ApplyMapChanges);check(game.error.empty()&&game.run->arena.rooms[size_t(shop)].sourceShopTemplate<0&&rocks()==0&&game.run->itemStacks({"isaac",ItemKind::Collectible,195})==1,"Apply OFF removes layout, retains build");
 game.perform(Action::RoomHeartsSource);game.perform(Action::ApplyMapChanges);check(game.run->arena.rooms[size_t(shop)].sourceShopTemplate==0&&rocks()==4&&!game.run->shopUpgradeSold&&!game.run->shopCardSold,"Apply SOURCE rebuilds full floor state");
 game.perform(Action::LoadBalance);check(game.run->arena.rooms[size_t(shop)].sourceShopTemplate==0&&game.hasPendingMapChanges(),"preset load stages map without premature reset");game.perform(Action::ApplyMapChanges);check(game.run->arena.rooms[size_t(shop)].sourceShopTemplate<0,"loaded OFF applies");
 game.perform(Action::RoomHeartsSource);game.perform(Action::ApplyMapChanges);game.perform(Action::RememberBalance);capture("tuning.png");game.perform(Action::CloseBalance);game.paused=false;
 game.run->dead=true;game.run->player.hp=0;game.perform(Action::RetryExpedition);check(game.error.empty()&&game.run->room==shop&&rocks()==4&&!game.run->shopUpgradeSold&&!game.run->shopCardSold&&game.run->items.empty()&&game.run->money()==20,"retry clean recorded room and explicit review funds");
 game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->roomHeartLayouts==1&&fresh.nextBalancePreset->defaultZoomPercent==165,"remembered configuration");fresh.seedText="6";fresh.themeChoice=ThemeChoice::Canyon;fresh.reviewShopStock=true;fresh.launch(true);check(fresh.run&&fresh.error.empty()&&fresh.run->arena.rooms[size_t(fresh.run->room)].sourceShopTemplate==0,"fresh launch admits recorded room");fresh.close();CloseWindow();
 std::cout<<"PASS Game/Renderer recorded shop, mouse purchases, pill/card consumption, dynamite/revisit, staged SOURCE/OFF, schema55 export/load/remember, Apply/retry/fresh launch\n";return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
