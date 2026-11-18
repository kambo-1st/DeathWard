#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "world/PedestalGeometry.hpp"
#include "world/SourceTreasureStock.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
int main(int argc,char **argv){try {
    check(argc>1,"natural seed required");const std::string seed=argv[1];
    SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Mom's Eye verification");SetTargetFPS(0);
    const auto root=std::filesystem::path("/tmp")/("deathward-moms-eye-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a7-moms-eye");
    auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a6/campaign.save.balance/export.json",defaultMechanics()->fingerprint());
    check(preset.treasureCollectiblePool==1,"retain user's ordinary treasure pool");preset.save(report/"review-preset.json");
    Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText=seed;game.reviewSourceRoomTemplate=RecordedMomsEyeReview;game.nextBalancePreset=preset;game.launch(true);
    check(game.run&&game.error.empty(),"natural recorded treasure direct entry");const int room=game.run->room;
    check(game.run->treasureUpgradeItem(room)==55&&game.run->player.hp==6&&!game.run->godMode&&game.balancePreset.defaultZoomPercent==165,"Mom's Eye selected naturally, normal health and original view");
    check(game.run->arena.rooms[size_t(room)].coinSpawns.size()==2,"both pennies in actual Game");
    game.updateCamera(10);Renderer renderer;
    auto frame=[&]{game.update(Tick);BeginDrawing();auto action=renderer.draw(game);EndDrawing();game.perform(action);};
    auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
    auto capture=[&](const char *name){BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"rendered capture");UnloadImage(im);EndDrawing();};
    frame();capture("treasure.png");
    game.run->player.position=pedestalGeometry::approach(game.run->rewardPosition(room),{0,0,1},.85f);frame();
    check(game.run->itemStacks({"isaac",ItemKind::Collectible,55})==1&&!game.run->rewardAvailable(room),"normal Game update collects the passive");
    const auto originalWait=game.run->player.fireCooldown;
    game.perform(Action::OpenBalance);game.perform(Action::BalanceShootingTab);game.perform(Action::BalanceTreasureTab);frame();click(450,190);
    check(game.balanceMomsEyeOpen,"mouse opens Mom's Eye page");
    game.balanceDraft.roomSizeScale=1.11f;click(800,252);
    check(std::abs(game.run->momsEyeChanceMultiplier-.95f)<.0001f&&game.run->player.fireCooldown==originalWait&&game.balanceDraft.roomSizeScale==1.11f&&game.run->roomSizeScale==preset.roomSizeScale,"live chance keeps wait and pending map edits");
    bool keyboardReached=false;
    for(int n=0;n<40&&!keyboardReached;++n){PlayAutomationEvent({0,2,{KEY_DOWN,0,0,0}});frame();keyboardReached=game.keyboardFocus()==Action::MomsEyeChanceDown;PlayAutomationEvent({0,1,{KEY_DOWN,0,0,0}});frame();}
    check(keyboardReached,"keyboard reaches Mom's Eye chance control");
    capture("tuning.png");game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);
    const auto exported=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(exported.momsEyeChanceMultiplier==.95f&&exported.roomSizeScale==1.11f,"export retains live and staged settings");
    click(350,485);check(game.run->momsEyeChanceMultiplier==1,"mouse resets source chance");game.perform(Action::LoadBalance);
    check(game.run->momsEyeChanceMultiplier==.95f&&game.run->roomSizeScale==preset.roomSizeScale,"load live chance/map pending");
    game.perform(Action::ApplyMapChanges);check(game.error.empty()&&game.run->momsEyeChanceMultiplier==.95f&&game.run->itemStacks({"isaac",ItemKind::Collectible,55})==1,"Apply retains owned passive and chance");
    game.perform(Action::CloseBalance);game.paused=false;
    // The developer volley capture uses a labelled guaranteed chance. The
    // exported playable review above retains the user's baseline Luck/chance.
    game.run->player.attributes.luck=20;game.run->player.position=add(game.run->arena.rooms[size_t(room)].center,{0,0,3});game.run->player.fireCooldown=0;game.run->projectiles.clear();
    Input in;in.fire=true;in.aim=add(game.run->player.position,{20,0,0});game.run->step(in);check(game.run->projectiles.size()==2,"actual Game emits forward/backward volley");game.updateCamera(10);
    for(int n=0;n<10;++n)game.run->step({});
    capture("backward-shot-developer-luck20.png");
    game.run->player.hp=0;game.run->dead=true;
    game.perform(Action::RetryExpedition);check(game.error.empty()&&game.run->room==room&&game.run->player.hp==6&&!game.run->godMode&&game.run->itemStacks({"isaac",ItemKind::Collectible,55})==0&&game.run->player.attributes.luck==preset.playerLuck&&game.run->momsEyeChanceMultiplier==.95f,"death retry returns to uncollected room and restores normal baseline stats");
    game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->momsEyeChanceMultiplier==.95f,"fresh Game remembers chance");fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=seed;fresh.reviewSourceRoomTemplate=RecordedMomsEyeReview;fresh.launch(true);check(fresh.run&&fresh.error.empty()&&fresh.run->treasureUpgradeItem(fresh.run->room)==55,"fresh expedition applies remembered preset");fresh.close();CloseWindow();
    std::cout<<"PASS Game/Renderer seed="<<seed<<" room="<<room+1<<" natural Mom's Eye/pennies, real pickup/volley, mouse/keyboard tuning, staged Apply, export/load/remember/retry/fresh launch\n";return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
