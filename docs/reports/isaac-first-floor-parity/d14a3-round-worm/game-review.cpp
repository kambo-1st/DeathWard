#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <iostream>
#include <chrono>
using namespace dw;
void check(bool v,const char *why){if(!v)throw std::runtime_error(why);}
int main(int argc,char **argv){try{
 const auto seed=argc>1?argv[1]:"1";
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Round Worm review verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-round-worm-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto presetPath="/home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json";
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a3-round-worm");
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText=seed;game.reviewSourceRoomTemplate=505;
 game.nextBalancePreset=BalancePreset::load(presetPath,defaultMechanics()->fingerprint());game.launch(true);
 check(game.run&&game.error.empty(),"direct main-game Round Worm launch");
 check(game.run->enemies.size()==2&&game.run->player.hp==6&&game.balancePreset.defaultZoomPercent==165,"normal-health two-enemy review preserves view");
 check(game.balancePreset.playerSpeed==1.1f&&game.balancePreset.shotSpeed==1.05f&&game.balancePreset.routeLengthScale==.26f,"current user preset retains movement, shooting and corridors");
 game.updateCamera(10);Renderer renderer;
 auto frame=[&]{game.update(Tick);BeginDrawing();auto a=renderer.draw(game);EndDrawing();game.perform(a);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto capture=[&](const char *file){BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/file).string().c_str()),"render capture");UnloadImage(im);EndDrawing();};
 frame();capture("encounter.png");const int room=game.run->room;
 std::cout<<"WITNESS seed="<<seed<<" displayed_room="<<room+1<<" zoom="<<game.balancePreset.defaultZoomPercent<<" routes="<<game.balancePreset.routeLengthScale<<'\n';
 game.run->godMode=true;
 game.perform(Action::OpenBalance);game.perform(Action::BalanceEnemiesTab);frame();click(1000,242);check(game.balanceFullFlyOpen,"mouse opens Full Fly page");
 click(970,480);check(game.balanceRoundWormOpen,"mouse opens Round Worm tuning");click(700,250);click(850,320);
 check(std::abs(game.balancePreset.roundWorm.cycleSpeed-.95f)<.0001f&&std::abs(game.run->roundWormTuning.shotSpeed-1.05f)<.0001f,"mouse tuning reaches live consumer");
 capture("tuning.png");game.balanceFile=(root/"export.json").string();click(335,605);check(std::filesystem::exists(game.balanceFile),"mouse export writes preset");
 click(900,605);check(game.nextBalancePreset->roundWorm==game.balancePreset.roundWorm,"remembered settings");
 const auto exported=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());exported.save(report/"tuned-preset.json");
 click(400,480);check(game.run->roundWormTuning==RoundWormTuning{},"reset applies baseline");click(610,605);check(game.run->roundWormTuning==exported.roundWorm,"load restores settings");
 game.balanceDraft.roomSizeScale=1.11f;game.applyMapChanges();check(game.run->roundWormTuning==exported.roundWorm,"map regeneration preserves tuning");
 game.perform(Action::CloseBalance);game.paused=false;
 game.perform(Action::RetryExpedition);check(game.error.empty()&&game.run->room==room&&game.run->roundWormTuning==exported.roundWorm&&game.run->player.hp==6,"retry returns to source505 with normal health and tuning");
 game.run->godMode=true;
 // Capture the real surfaced model and aimed attack without altering its phase.
 bool shot=false;
 for(int i=0;i<1800;++i){game.run->step({});if(std::any_of(game.run->enemies.begin(),game.run->enemies.end(),[](const auto&e){return e.roundWorm&&e.roundWorm->phase==RoundWormPhase::DigOut&&e.roundWorm->frame>=30&&e.roundWorm->frame<38;})){game.updateCamera(10);capture("emergence.png");break;}}
 for(int i=0;i<1800;++i){game.run->step({});if(!game.run->projectiles.empty()){capture("aimed-shot.png");shot=true;break;}}
 check(shot,"ordinary room produces aimed shots");
 for(auto id:{game.run->enemies[0].id,game.run->enemies[1].id}){Event e;e.type=EventType::Damage;e.target=id;e.damage=100;e.execution=e.debugExecution=true;check(game.run->queueRoot(e),"developer cleanup admitted");game.run->drainEvents();}
 for(int i=0;i<240;++i)game.run->step({});check(game.run->roomClear&&game.run->roomThreats()==0,"ordinary clear and bullet expiry");
 game.run->enterRoom(0);game.run->enterRoom(room);check(game.run->roomThreats()==0,"revisit stays cleared");
 game.close();renderer.unload();
 Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->roundWorm==exported.roundWorm,"new Game loads remembered configuration");fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=seed;fresh.reviewSourceRoomTemplate=505;fresh.launch(true);check(fresh.run&&fresh.run->roundWormTuning==exported.roundWorm,"fresh launch consumes remembered values");fresh.close();CloseWindow();
 std::cout<<"PASS actual Game/Renderer, mouse live controls/export/load/reset/remember, Apply, retry, shooting, clear, revisit and fresh launch.\n";return 0;
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
