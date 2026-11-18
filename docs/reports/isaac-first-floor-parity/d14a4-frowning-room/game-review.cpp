#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
int main(int argc,char **argv){try{
 check(argc>1,"seed argument required");const char *seed=argv[1];
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Frowning room verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-frowning-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a4-frowning-room");
 const auto original="/home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json";
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText=seed;game.reviewSourceRoomTemplate=51;game.nextBalancePreset=BalancePreset::load(original,defaultMechanics()->fingerprint());game.launch(true);
 check(game.run&&game.error.empty(),"main-game source51 direct entry");check(game.run->enemies.size()==2&&game.run->player.hp==6&&!game.run->godMode,"two natural Frowning actors at normal health");
 check(game.balancePreset.defaultZoomPercent==165&&game.balancePreset.playerSpeed==1.1f&&game.balancePreset.shotSpeed==1.05f&&game.balancePreset.routeLengthScale==.26f,"user settings preserved");
 check(game.run->frowningMovementMultiplier==1&&!game.run->nativeGaperPursuit,"production consumer enabled without private global review");
 game.updateCamera(10);Renderer renderer;
 auto frame=[&]{game.update(Tick);BeginDrawing();auto a=renderer.draw(game);EndDrawing();game.perform(a);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto capture=[&](const char *file){BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/file).string().c_str()),"capture rendered game");UnloadImage(im);EndDrawing();};
 frame();capture("encounter.png");const int room=game.run->room;const auto sourceSeed=game.run->arena.rooms[size_t(room)].sourceRoomSpawnSeed;const auto actor=game.run->enemies.front().id;
 game.perform(Action::OpenBalance);game.perform(Action::BalanceEnemiesTab);frame();click(1000,356);check(game.balanceFrowningOpen,"mouse opens Frowning page");
 const auto position=game.run->findEnemy(actor)->position;const auto head=game.run->findEnemy(actor)->gaper->headFrame;
 game.balanceDraft.roomSizeScale=1.11f;click(705,251);
 check(game.balancePreset.frowningMovementMultiplier==.95f&&game.run->frowningMovementMultiplier==.95f&&game.balancePreset.gaperMovementMultiplier==1,"independent live Frowning edit");
 check(game.balanceDraft.roomSizeScale==1.11f&&game.run->roomSizeScale==1.1f&&game.run->arena.rooms[size_t(room)].sourceRoomSpawnSeed==sourceSeed,"live control preserves pending map edit and descriptor");
 check(distance(position,game.run->findEnemy(actor)->position)==0&&head==game.run->findEnemy(actor)->gaper->headFrame,"paused live edit preserves position and head");capture("tuning.png");
 game.balanceFile=(root/"export.json").string();click(335,605);check(std::filesystem::exists(game.balanceFile),"mouse export");const auto exported=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(exported.frowningMovementMultiplier==.95f&&exported.roomSizeScale==1.11f,"export includes live and staged map values");exported.save(report/"tuned-preset.json");
 click(900,605);check(game.nextBalancePreset&&game.nextBalancePreset->frowningMovementMultiplier==.95f,"remember next expedition");
 click(430,482);check(game.run->frowningMovementMultiplier==1,"mouse reset");click(610,605);check(game.run->frowningMovementMultiplier==.95f&&game.run->roomSizeScale==1.1f&&game.balanceDraft.roomSizeScale==1.11f,"load stages map and applies only live control");
 // The registry addition must not alter navigation among the other enemy pages.
 click(950,482);check(!game.balanceFrowningOpen,"back to Gaper/Spider");click(1000,242);check(game.balanceFullFlyOpen,"Full Fly page remains reachable");click(970,480);check(game.balanceRoundWormOpen,"Round Worm page remains reachable");
 game.applyMapChanges();check(game.error.empty()&&game.run->frowningMovementMultiplier==.95f&&game.run->roomSizeScale==1.11f,"Apply preserves new movement");
 // A size edit may legitimately select different source content. Restore the recorded witness dimensions before direct retry.
 game.balanceDraft.roomSizeScale=1.1f;game.applyMapChanges();
 game.perform(Action::CloseBalance);game.paused=false;game.perform(Action::RetryExpedition);check(game.error.empty()&&game.run->enemies.size()==2&&game.run->room==room&&game.run->player.hp==6&&game.run->frowningMovementMultiplier==.95f,"retry direct entry and tuning");
 game.run->godMode=true;for(int n=0;n<120;++n)game.run->step({});check(game.run->enemies.front().gaper->headFrame>0,"actual main-game actor wakes");game.updateCamera(10);capture("awake.png");
 // Retained Gaper headless lifecycle can survive the first execution; drain all threats.
 for(int i=0;i<240;++i){std::vector<EntityId> ids;for(const auto &e:game.run->enemies)if(e.alive&&!e.environment)ids.push_back(e.id);for(auto id:ids){Event e;e.type=EventType::Damage;e.target=id;e.damage=100;e.execution=e.debugExecution=true;check(game.run->queueRoot(e),"cleanup admitted");game.run->drainEvents();}game.run->step({});}check(game.run->roomClear,"ordinary room clears");game.run->enterRoom(0);game.run->enterRoom(room);check(game.run->roomThreats()==0,"revisit remains clear");
 game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->frowningMovementMultiplier==.95f,"remembered configuration on fresh Game");fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=seed;fresh.launch(true);check(fresh.run&&fresh.error.empty()&&fresh.run->frowningMovementMultiplier==.95f,"fresh expedition applies remembered value");fresh.close();CloseWindow();
 std::cout<<"PASS Game/Renderer: source51 seed="<<seed<<" room="<<room+1<<", mouse tuning/reset/export/load/remember, staged Apply, retry, awakening, clear/revisit, fresh launch\n";return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
