#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <iostream>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void seedSave(const std::filesystem::path &p){check(!std::filesystem::exists(p),"seed only new isolated save");CampaignStore store(p);store.begin(68);auto s=*store.data().pending;s.donationBank=19;s.donationUnlocks=donationMilestonesAt(19);store.resolve(s,EndReason::Retreat);}
int main(int argc,char **argv){try{
 if(argc==2){seedSave(argv[1]);return 0;}
 SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Shop milestone verification");SetTargetFPS(0);
 const auto root=std::filesystem::path("/tmp")/("deathward-milestone-game-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
 const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a15-donation-milestones");
 auto preset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a14/campaign.save.balance/export.json",defaultMechanics()->fingerprint());preset.save(report/"review-preset.json");seedSave(root/"campaign.save");
 Game game(root/"campaign.save");game.themeChoice=ThemeChoice::Canyon;game.seedText="68";game.reviewShopStock=true;game.nextBalancePreset=preset;game.launch(true);check(game.run&&game.error.empty(),"Game launch");
 Renderer renderer;game.updateCamera(10);
 auto frame=[&]{game.update(Tick);BeginDrawing();auto a=renderer.draw(game);EndDrawing();game.perform(a);};
 auto click=[&](int x,int y){PlayAutomationEvent({0,7,{x,y,0,0}});frame();PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});frame();PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});frame();};
 auto ticks=[&](int n){for(int i=0;i<n;++i)game.update(Tick);};
 auto capture=[&](const char *name){game.updateCamera(10);BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/name).string().c_str()),"screenshot");UnloadImage(im);EndDrawing();};
 frame();check(game.run->donation.bank==19&&game.run->shopLevel==0&&game.balancePreset.defaultZoomPercent==165,"19 bank baseline shop");capture("before.png");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceCoinDonationTab);game.perform(Action::CycleDonationOutcome);game.perform(Action::CloseBalance);game.paused=false;
 auto at=game.run->coinDonationMachines[0].position;game.run->player.position=add(at,{1.06f,0,0});ticks(2);game.run->player.position=game.run->arena.rooms[size_t(game.run->room)].entry;ticks(20);
 check(game.run->donation.bank==20&&game.campaign.data().world.donationUnlocks==3&&game.run->shopLevel==0,"Game checkpoint unlock without rebuilding shop");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceCoinDonationTab);game.perform(Action::DonationCycleUp);check(game.run->shopLevel==0&&game.run->donation.bank==20,"live edits do not refresh shop");frame();click(850,481);check(game.balanceShopProgressOpen,"mouse opens shop upgrades");capture("tuning-earned.png");
 click(400,470);check(game.run->shopLevel==1&&game.run->upgradedShop.size()==3&&game.error.empty(),"explicit Apply earned level");game.perform(Action::CloseBalance);game.paused=false;frame();game.run->player.position=shopCartGeometry::reviewStart(game.run->arena.rooms[size_t(game.run->room)].center);capture("level1.png");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceShopProgressTab);for(int i=0;i<5;++i)click(970,320);check(game.balanceDraft.shopLevelOverride==4&&game.run->shopLevel==1,"staged override");
 game.balanceFile=(root/"export.json").string();game.perform(Action::ExportBalance);game.perform(Action::RememberBalance);check(BalancePreset::load(game.balanceFile,preset.mechanicsFingerprint).shopLevelOverride==4,"export staged level");
 game.perform(Action::ShopLevelEarned);game.perform(Action::LoadBalance);check(game.balanceDraft.shopLevelOverride==4&&game.run->shopLevel==1,"load stages level without map changes");capture("tuning-level4.png");click(400,470);check(game.run->shopLevel==4&&game.run->upgradedShop.size()==6&&game.error.empty(),"explicit Apply six slots");game.perform(Action::CloseBalance);game.paused=false;frame();game.run->player.position=shopCartGeometry::reviewStart(game.run->arena.rooms[size_t(game.run->room)].center);capture("level4.png");
 game.perform(Action::OpenBalance);game.perform(Action::BalanceShopProgressTab);game.perform(Action::ShopLevelEarned);game.perform(Action::ApplyMapChanges);game.perform(Action::ResetCoinDonation);game.perform(Action::RememberBalance);game.perform(Action::CloseBalance);game.paused=false;frame();
 check(game.run->shopLevel==1&&game.run->donation.unlocks==3,"testing override never grants milestones");game.run->dead=true;game.run->player.hp=0;game.perform(Action::RetryExpedition);std::cerr<<"RETRY error="<<game.error<<" exists="<<bool(game.run)<<" level="<<(game.run?game.run->shopLevel:-1)<<" bank="<<(game.run?game.run->donation.bank:9999)<<" balance="<<game.balancePreset.shopLevelOverride<<" open="<<game.balanceOpen<<"\n";check(game.run&&game.error.empty()&&game.run->shopLevel==1&&game.run->donation.bank==20,"retry uses permanent shop upgrade");
 game.close();renderer.unload();Game fresh(root/"campaign.save");check(fresh.nextBalancePreset&&fresh.nextBalancePreset->shopLevelOverride==-1&&fresh.nextBalancePreset->defaultZoomPercent==165&&fresh.campaign.data().world.donationUnlocks==3,"fresh process earned level and preset retained");fresh.close();CloseWindow();
 std::cout<<"PASS actual Game/Renderer milestone checkpoint, mouse UI, staged export/load/Apply, six-slot render, retry and fresh process\n";return 0;
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
