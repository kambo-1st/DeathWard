#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
int main(){try{
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Coin donation verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-donation-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a14-coin-donation");
 auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a12/campaign.save.balance/export.json",defaultMechanics()->fingerprint());preset.save(report/"review-preset.json");
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText="68";game.reviewShopStock=true;game.nextBalancePreset=preset;game.launch(true);check(game.run&&game.error.empty(),"Game launch");
 Renderer renderer;game.updateCamera(10);int shop=game.run->room;
 auto frame=[&]{game.update(Tick);BeginDrawing();auto a=renderer.draw(game);EndDrawing();game.perform(a);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto ticks=[&](int n){for(int i=0;i<n;++i)game.update(Tick);};
 auto key=[&](int k){PlayAutomationEvent({0,2,{k,0,0,0}});frame();PlayAutomationEvent({0,1,{k,0,0,0}});frame();};
 auto capture=[&](const char *name){game.updateCamera(10);BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"screenshot");UnloadImage(im);EndDrawing();};
 frame();check(game.run->coinDonationMachines.size()==1,"natural coin register");capture("shop.png");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceRewardsTab);game.perform(Action::BalanceShopTab);frame();click(1010,189);
 check(game.balanceCoinDonationOpen,"mouse opens donation page");click(400,273);check(!game.run->coinDonationTuning.enabled,"live toggle");click(400,273);
 click(620,318);click(495,362);check(game.run->coinDonationTuning.cycleSpeed==1.05f&&game.run->coinDonationTuning.jamScale==.95f,"independent cycle and jam controls");
 click(880,335);check(game.run->coinDonationTuning.outcome==1,"never jam test");bool keyboard=false;for(int n=0;n<35&&!keyboard;++n){key(KEY_DOWN);keyboard=game.keyboardFocus()==Action::CycleDonationOutcome;}check(keyboard,"keyboard reaches donation control");capture("tuning.png");
 game.perform(Action::BalanceWorldTab);game.perform(Action::RoomSizeUp);const auto draft=game.balanceDraft.roomSizeScale;game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);
 const auto saved=BalancePreset::load(game.balanceFile,defaultMechanics()->fingerprint());check(saved.coinDonation.outcome==1&&saved.defaultZoomPercent==165,"schema58 export");
 game.perform(Action::ResetCoinDonation);game.perform(Action::LoadBalance);check(game.run->coinDonationTuning.outcome==1&&game.balanceDraft.roomSizeScale==draft&&game.run->roomSizeScale==preset.roomSizeScale,"load keeps pending map edits");
 game.perform(Action::CloseBalance);game.paused=false;
 auto at=game.run->coinDonationMachines[0].position;Input move;move.moveTarget=at;game.run->step(move);check(game.run->moveDestination().has_value(),"actual shop has mouse route");
 for(int i=0;i<2000&&game.run->donation.bank<1;++i)game.run->step({});check(game.run->donation.bank>=1,"walked to register and donated");Input stop;stop.standStill=true;game.run->step(stop);game.run->player.position=game.run->arena.rooms[size_t(shop)].entry;ticks(20);
 const auto bank=game.run->donation.bank;check(bank>=1&&game.campaign.data().world.donationBank==bank,"actual Game checkpoints bank");
 game.run->player.position=add(at,{0,0,3});capture("donated.png");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceCoinDonationTab);game.perform(Action::CycleDonationOutcome);game.perform(Action::CloseBalance);game.paused=false;
 // Wait away for the existing cooldown, then use the ordinary contact consumer.
 game.run->player.position=game.run->arena.rooms[size_t(shop)].entry;ticks(40);game.run->player.position=add(at,{1.06f,0,0});ticks(35);
 check(game.run->donation.jammed&&game.run->donation.bank==bank+1,"next completed deposit jams");game.run->player.position=add(at,{0,0,3});capture("jammed.png");
 game.run->enterRoom(0);game.run->enterRoom(shop);frame();check(game.run->donation.jammed,"revisit jam");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceWorldTab);game.perform(Action::ApplyMapChanges);check(game.run->donation.jammed&&game.run->donation.bank==bank+1,"Apply keeps bank/jam");game.perform(Action::CloseBalance);game.paused=false;
 game.run->dead=true;game.run->player.hp=0;game.perform(Action::RetryExpedition);check(game.run&&game.error.empty()&&!game.run->donation.jammed&&game.run->donation.bank==bank+1,"death/retry retains bank, clears expedition jam");
 game.perform(Action::OpenBalance);game.perform(Action::ResetCoinDonation);game.perform(Action::CloseBalance);game.paused=false;at=game.run->coinDonationMachines[0].position;
 game.run->player.position=add(at,{0,0,1.6f});check(!game.run->arena.blocked(game.run->player.position,.48f),"real bomb placement clear");const auto bombs=game.run->dynamite;key(KEY_B);check(game.run->dynamite==bombs-1,"B places dynamite");game.run->player.position=game.run->arena.rooms[size_t(game.run->room)].entry;ticks(110);
 check(game.run->donation.excluded&&game.run->coinDonationMachines[0].phase==CoinDonationMachine::Phase::Destroyed,"ordinary dynamite destroys register");check(game.run->donation.bank==0,"small bank withdrawal capped");game.run->player.position=add(at,{0,0,3});capture("destroyed.png");
 game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->coinDonation.outcome==1&&fresh.nextBalancePreset->defaultZoomPercent==165&&fresh.campaign.data().world.donationBank==0,"new process remembers controls and independent bank");fresh.close();CloseWindow();
 std::cout<<"PASS actual Game/Renderer UI, mouse route, bank checkpoint, export/load/remember, staged Apply, jam/revisit/death/retry, real B dynamite and fresh campaign loading\n";return 0;
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
