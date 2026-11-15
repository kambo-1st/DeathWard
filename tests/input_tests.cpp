#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "items/Items.hpp"
#include "combat/ChestGeometry.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "rlgl.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
// Event IDs from the pinned raylib 5.5 automation format (rcore.c).
constexpr unsigned MouseUp = 5, MouseDown = 6, MousePosition = 7, MouseWheel = 8;
constexpr unsigned KeyUp = 1, KeyDown = 2;
void mouseEvent(unsigned type, int first, int second = 0) {
    PlayAutomationEvent({0, type, {first, second, 0, 0}});
}
void balanceInputCheck(const std::filesystem::path &directory) {
    const auto save=directory/"balance.save";
    dw::Game game(save);game.debug=false;game.seedText="1866";
    game.themeChoice=dw::ThemeChoice::Canyon;game.launch(true);
    check(game.run&&game.error.empty(),"main game direct expedition launch");
    game.run->godMode=true;game.updateCamera(10);dw::Renderer renderer;
    auto frame=[&] {
        game.update(dw::Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);
    };
    auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    auto click=[&](int x,int y) {
        mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();
        mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
    };
    auto capture=[&](const char *name) {
        std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();
        auto image=LoadImageFromScreen();check(ExportImage(image,name),"capture tuning UI");UnloadImage(image);EndDrawing();
    };
    auto &run=*game.run;
    check(run.player.attributes.speed==1&&run.player.shotDamage==dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource&&run.player.hp==6,"D01 preserves baseline combat");
    const auto start=run.player.position;
    const auto walk=[&] {
        mouseEvent(KeyDown,KEY_W);
        for(int i=0;i<6;++i)frame();
        mouseEvent(KeyUp,KEY_W);frame();
        return dw::distance(start,run.player.position);
    };
    const float baseline=walk();check(baseline>.1f,"actual keyboard walking moves in starting room");
    run.player.position=start;run.player.velocity={};
    click(374,642);check(game.balanceOpen&&!game.paused,"live HUD opens tuning without a debug flag");
    const auto duration=run.stats.duration;const auto position=run.player.position;
    const auto shots=run.stats.shots;const auto rng=run.combatRng.state;
    mouseEvent(KeyDown,KEY_W);mouseEvent(KeyDown,KEY_UP);frame();
    check(run.stats.duration==duration&&run.stats.shots==shots&&dw::distance(position,run.player.position)==0,
          "tuning panel freezes gameplay and captures movement/fire keys");
    mouseEvent(KeyUp,KEY_W);mouseEvent(KeyUp,KEY_UP);frame();
    click(460,190);click(460,190);
    check(std::abs(run.player.attributes.speed-.8f)<1e-6f&&run.combatRng.state==rng,"Speed buttons apply without advancing combat RNG");
    check(game.campaign.data().pending->mechanicsFingerprint.find("/balance-v11:")!=std::string::npos,"checkpoint identifies active tuning revision");
    check(std::filesystem::exists(game.balanceDirectory/"revisions"/(game.balancePreset.revision()+".json")),"checkpoint revision retains its resolved preset");
    check(run.canResizeRooms(),"untouched starting room permits live resizing");
    const auto id=run.summary().id, nextId=game.campaign.data().nextRunId;
    const auto historyBefore=game.campaign.data().history.size();
    const float width=run.arena.rooms[0].bounds.max.x-run.arena.rooms[0].bounds.min.x;
    const auto oldTerrain=run.arena.canyon.get();const auto oldRevision=game.balancePreset.revision();
    click(665,270);
    check(game.hasPendingMapChanges()&&game.balanceDraft.roomSizeScale==1.01f&&run.roomSizeScale==1&&
          run.arena.canyon.get()==oldTerrain&&game.balancePreset.revision()==oldRevision,
          "size edit stays pending and leaves current geometry/checkpoint configuration intact");
    click(730,357);check(game.balanceDraft.routeLengthScale==1.01f&&run.routeLengthScale==1,"route edit uses one-percent pending steps");
    click(535,234);check(game.balancePreset.defaultZoomPercent==159&&std::abs(game.cameraZoomPercent()-159)<.001f,"default zoom decreases by one percent and previews immediately");
    click(635,234);check(game.balancePreset.defaultZoomPercent==160,"default zoom increases by one percent");
    game.setDefaultZoom(67);game.perform(dw::Action::DefaultZoomDown);check(game.balancePreset.defaultZoomPercent==67,"default zoom lower limit");
    game.setDefaultZoom(285);game.perform(dw::Action::DefaultZoomUp);check(game.balancePreset.defaultZoomPercent==285,"default zoom upper limit");
    click(970,234);check(std::abs(game.cameraZoomPercent()-160)<.001f,"reset zoom previews original 160 percent");
    game.setPlayerSpeed(.7f);game.resetBalance();game.setPlayerSpeed(.8f);
    check(run.arena.canyon.get()==oldTerrain&&game.hasPendingMapChanges(),"live Speed edits and reset never apply pending map settings");
    key(KEY_ESCAPE);mouseEvent(MousePosition,600,400);frame();mouseEvent(MouseWheel,0,-2);frame();frame();game.updateCamera(10);
    const float currentZoom=std::round(game.cameraZoomPercent());
    check(currentZoom<160&&game.balancePreset.defaultZoomPercent==160,"mouse wheel changes only the temporary view");
    click(374,642);click(780,234);
    check(game.balancePreset.defaultZoomPercent==currentZoom&&std::abs(game.cameraZoomPercent()-currentZoom)<.001f,"Use current captures the actual view as the default");
    check(run.arena.canyon.get()==oldTerrain&&game.hasPendingMapChanges(),"zoom controls never apply pending map changes");
    game.setDefaultZoom(145);
    check(game.balanceOpen&&game.hasPendingMapChanges(),"closing and reopening tuning retains pending map edits");
    const auto applyTime=run.stats.duration;
    click(375,409);
    check(!game.hasPendingMapChanges()&&run.roomSizeScale==1.01f&&run.routeLengthScale==1.01f,"Apply commits all pending map fields together");
    const auto appliedTerrain=run.arena.canyon.get();click(375,409);
    check(run.arena.canyon.get()==appliedTerrain,"Apply with no changes never regenerates the floor");
    check(run.arena.rooms[0].bounds.max.x-run.arena.rooms[0].bounds.min.x>width,"room grows visibly");
    check(run.summary().id==id&&run.stats.duration==applyTime&&game.campaign.data().nextRunId==nextId&&
          game.campaign.data().history.size()==historyBefore&&run.player.hp==6&&std::abs(run.player.walkingSpeed()-4.8f*.8f)<.001f,
          "live resize preserves expedition identity, time, history, health and accepted walking speed");
    click(535,270);click(590,357);click(375,409);check(run.roomSizeScale==1&&run.routeLengthScale==1,"size can be reduced without restarting");
    click(720,315);check(run.roomMinHalfTiles==0&&game.balanceDraft.roomMaxHalfTiles==9,"range control stays pending");
    click(375,409);check(run.roomMinHalfTiles==6&&run.roomMaxHalfTiles==9,"Apply regenerates selected range");
    click(925,315);click(375,409);check(run.roomMinHalfTiles==0&&run.roomMaxHalfTiles==0,"automatic range restored");
    run.player.position=start;run.player.velocity={};
    capture("artifacts/d02-live-size-panel.png");
    capture("artifacts/d01-tuning-custom.png");
    click(320,605);check(std::filesystem::exists(game.balanceFile),"export button writes JSON");
    std::filesystem::copy_file(game.balanceFile,"artifacts/d01-speed-080.json",std::filesystem::copy_options::overwrite_existing);
    click(900,605);check(game.nextBalancePreset&&game.nextBalancePreset->playerSpeed==.8f,"remember button persists next-expedition preset");
    key(KEY_ESCAPE);check(!game.balanceOpen&&!game.paused,"Escape returns directly to gameplay");
    const float tuned=walk();
    check(std::abs(tuned/baseline-.8f)<.01f,"main Game keyboard movement immediately follows live Speed ratio");
    key(KEY_ESCAPE);check(game.paused,"normal pause still works");
    click(1150,140);check(game.balanceOpen&&game.paused,"pause menu also opens tuning");
    run.player.hp=5;run.grant(dw::ItemId::Ricochet);run.keys=2;run.moneyCollected=11;
    const auto items=run.items;const auto rooms=run.stats.rooms;const auto health=run.player.hp;
    const auto money=run.money();const auto runSeed=run.expedition.seed;
    click(850,190);check(run.player.attributes.speed==1&&game.balancePreset.defaultZoomPercent==145,"reset reference changes Speed only");
    game.setDefaultZoom(160);
    click(590,605);
    check(std::abs(game.cameraZoomPercent()-145)<.001f&&run.player.attributes.speed==.8f&&run.player.hp==health&&run.items==items&&run.keys==2&&
          run.money()==money&&run.stats.rooms==rooms&&run.expedition.seed==runSeed,
          "preset load preserves injuries, inventory, wallet, keys, room progress and seed");
    const auto previous=game.balancePreset.revision(),previousDraft=game.balanceDraft.revision();
    const auto invalid=directory/"invalid.json";{std::ofstream out(invalid);out<<"{\"resolved\":{\"player_speed\":99}}";}
    const auto exportPath=game.balanceFile;game.balanceFile=invalid.string();game.perform(dw::Action::LoadBalance);
    check(!game.error.empty()&&game.balancePreset.revision()==previous&&game.balanceDraft.revision()==previousDraft&&run.player.attributes.speed==.8f,
          "invalid live load rejects atomically without changing active Speed");
    game.balanceFile=exportPath;game.perform(dw::Action::LoadBalance);check(game.error.empty(),"valid load recovers from invalid input");
    game.setPlayerSpeed(.7f);check(game.nextBalancePreset->playerSpeed==.8f,"live edit does not silently change remembered next-expedition settings");
    game.setPlayerSpeed(.8f);
    // Exercise the actual keyboard path editor, including paste and Escape restoration.
    click(600,540);check(game.balancePathEditing,"preset path is editable");
    SetClipboardText(invalid.string().c_str());mouseEvent(KeyDown,KEY_LEFT_CONTROL);key(KEY_V);mouseEvent(KeyUp,KEY_LEFT_CONTROL);frame();
    check(game.balanceFile==invalid.string(),"path editor supports pasting an arbitrary preset path");
    key(KEY_ESCAPE);check(!game.balancePathEditing&&game.balanceFile==exportPath,"Escape restores uncommitted path edit");
    key(KEY_ESCAPE);check(!game.balanceOpen&&game.paused,"tuning returns to the originating pause menu");key(KEY_ESCAPE);
    const auto history=game.campaign.data().history.size();
    mouseEvent(MousePosition,600,400);frame();mouseEvent(MouseWheel,0,-2);frame();frame();game.updateCamera(10);
    check(game.cameraZoomPercent()<140&&game.balancePreset.defaultZoomPercent==145,"temporary wheel zoom does not replace the saved default before retry");
    run.finishDebug(false);key(KEY_ENTER);
    check(game.run&&!game.run->dead&&game.screen==dw::Screen::Expedition&&game.run->expedition.seed==runSeed,
          "Enter after death retries the same expedition directly");
    check(game.campaign.data().history.size()==history+1&&game.run->player.attributes.speed==.8f&&game.run->player.hp==6&&std::abs(game.cameraZoomPercent()-145)<.001f,
          "retry resolves death once, retains active Speed and starts with normal health");
    game.run->finishDebug(false);game.finish(dw::EndReason::Death);
    capture("artifacts/d01-death-retry.png");
    check(game.keyboardFocus()==dw::Action::RetryExpedition,"death summary defaults to retry");key(KEY_ENTER);
    check(game.run&&!game.run->dead&&game.run->expedition.seed==runSeed,"summary Enter restarts without visiting the hub");
    game.setRoomSizeRange(7,9);game.setRoomSize(1.25f);game.setRouteLength(.65f);game.setDefaultZoom(125);game.rememberBalancePreset();game.exportBalancePreset();
    check(game.run->roomSizeScale==1&&game.run->routeLengthScale==1,"export and remember do not apply pending map to current floor");
    game.setRoomSize(1);game.setRoomSizeRange(0,0);game.setRouteLength(1);
    const auto beforeLoad=game.run->arena.canyon.get();game.loadBalancePreset(game.balanceFile);
    check(game.hasPendingMapChanges()&&game.run->arena.canyon.get()==beforeLoad&&game.balanceDraft.routeLengthScale==.65f,
          "loading exported map stages its settings without regeneration");
    game.applyMapChanges();
    std::filesystem::copy_file(game.balanceFile,"artifacts/d02-size-range.json",std::filesystem::copy_options::overwrite_existing);
    game.run->jumpDebug(game.run->finalRoom());game.run->clearRoomDebug();game.run->floorExitRequested=true;
    check(game.run->advanceFloor()&&game.run->player.attributes.speed==.8f,"preset Speed survives actual floor transfer");
    check(game.run->routeLengthScale==.65f&&game.run->roomSizeScale==1.25f&&game.run->roomMinHalfTiles==7&&game.run->roomMaxHalfTiles==9,"size range survives floor transition");
    game.run->grant(dw::ItemId::Ricochet);game.run->keys=2;game.run->moneyCollected=11;
    game.run->jumpDebug(game.run->finalRoom());game.run->player.hp=5;
    const auto resizeItems=game.run->items;const auto resizeId=game.run->summary().id;
    const auto resizeRoom=game.run->room,resizeFloor=game.run->floor;
    game.perform(dw::Action::RoomSizeDown);game.perform(dw::Action::ApplyMapChanges);
    check(game.error.empty()&&game.run->roomSizeScale==1.24f&&game.run->room==resizeRoom&&game.run->floor==resizeFloor&&
          game.run->summary().id==resizeId&&game.run->player.hp==5&&game.run->items==resizeItems&&game.run->keys==2&&game.run->moneyCollected==11,
          "testing resize after exploration/on later floor preserves player, inventory, currency and current expedition/room");
    check(game.run->livingEnemies()>0,"testing resize regenerates current room encounters");
    game.setRoomSize(1.25f);game.applyMapChanges();
    game.close();renderer.unload();
    dw::Game fresh(save);fresh.themeChoice=dw::ThemeChoice::Canyon;fresh.seedText="1866";fresh.launch(true);
    check(fresh.error.empty()&&fresh.run->player.attributes.speed==.8f,"fresh Game session auto-loads remembered preset for next expedition");
    check(fresh.run->routeLengthScale==.65f&&fresh.run->roomSizeScale==1.25f&&fresh.run->roomMinHalfTiles==7&&fresh.run->roomMaxHalfTiles==9&&std::abs(fresh.cameraZoomPercent()-125)<.001f,"fresh session loads size/range before generation");
    check(fresh.run->player.hp==6&&fresh.run->player.shotDamage==dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource&&fresh.run->items.empty(),"preset is configuration, not old inventory or damage changes");
    fresh.run->finishDebug(false);fresh.retryExpedition();
    check(fresh.run->routeLengthScale==.65f&&fresh.run->roomSizeScale==1.25f&&std::abs(fresh.cameraZoomPercent()-125)<.001f,"retry retains applied route and room settings");
    fresh.resetBalance();fresh.rememberBalancePreset();fresh.close();
    dw::Game restored(save);restored.themeChoice=dw::ThemeChoice::Canyon;restored.launch(true);
    check(restored.run->player.attributes.speed==1&&restored.balancePreset.defaultZoomPercent==125,"reference reset and remember round-trip to a new session");restored.close();
    {std::ofstream out(restored.balanceDirectory/"next.json");out<<"broken";}
    dw::Game broken(save);check(!broken.error.empty(),"corrupt remembered preset is reported, not silently accepted");
    bool rejected=false;try{broken.launch(true);}catch(const std::exception &){rejected=true;}
    check(rejected&&!broken.run&&!broken.campaign.data().pending,"incompatible remembered preset cannot silently launch defaults");
    broken.resetBalance();broken.rememberBalancePreset();broken.launch(true);check(broken.run!=nullptr,"reference reset recovers invalid saved configuration");broken.close();
    dw::Game setup(directory/"map-setup.save");setup.themeChoice=dw::ThemeChoice::Canyon;
    setup.setRoomSize(1.1f);setup.setRouteLength(1.5f);
    check(!setup.nextBalancePreset&&!std::filesystem::exists(setup.balanceDirectory/"next.json"),"pre-generation edits remain unsaved until explicit apply/remember");
    setup.setDefaultZoom(175);
    check(setup.nextBalancePreset&&setup.nextBalancePreset->roomSizeScale==1&&setup.nextBalancePreset->routeLengthScale==1,
          "pre-generation zoom edit saves zoom without leaking pending map settings");
    setup.applyMapChanges();setup.launch(true);
    check(setup.run->roomSizeScale==1.1f&&setup.run->routeLengthScale==1.5f&&std::abs(setup.cameraZoomPercent()-175)<.001f,"Apply before generation configures actual next expedition");setup.close();
    std::cout<<"PASS default zoom controls/export/load/retry, staged map Apply and route persistence; D01 actual Game/Renderer controls, live movement, export/load/remember, invalid-load isolation, state preservation, death/summary retry and floor/session persistence\n";
}
void shootingBalanceInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto save=directory/"shooting-balance.save";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="1866";
    BalancePreset chosen{1,defaultMechanics()->fingerprint(),1.1f,7,9,.3f,165};
    const auto file=directory/"shooting.json";chosen.save(file);game.loadBalancePreset(file);game.rememberBalancePreset();game.launch(true);
    auto &run=*game.run;run.godMode=true;game.updateCamera(10);Renderer renderer;
    const auto near=[&](float a,float b,const char *message){check(std::abs(a-b)<.001f,message);};
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"shooting UI has no error");};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    near(run.player.attributes.tearsPerSecond,BalancePreset::ReferenceTears,"migrated starting Tears baseline");
    near(run.player.walkingSpeed(),4.8f,"shooting controls preserve accepted walk");near(game.cameraZoomPercent(),165,"chosen zoom retained");
    click(374,642);click(710,143);check(game.balanceOpen&&game.balanceShootingOpen,"actual HUD opens shooting tab");
    game.setRoomSize(1.2f);const auto terrain=run.arena.canyon.get();const auto duration=run.stats.duration,shots=double(run.stats.shots);
    click(855,189);near(run.player.attributes.tearsPerSecond,BalancePreset::ReferenceTears+.1f,"Tears plus changes only rate");
    click(710,189);check(run.player.attributes.tearsPerSecond==BalancePreset::ReferenceTears,"opposite Tears steps preserve the exact baseline");
    click(855,189);
    near(run.player.attributes.shotSpeed,1,"Tears does not change shot speed");near(run.player.attributes.rangeTiles,6.5f,"Tears does not change range");
    click(855,268);near(run.player.attributes.shotSpeed,1.05f,"Shot Speed plus uses a small independent step");
    click(855,348);near(run.player.attributes.rangeTiles,6.75f,"Range plus uses quarter-tile steps");
    check(run.arena.canyon.get()==terrain&&run.stats.duration==duration&&run.stats.shots==shots&&game.hasPendingMapChanges(),
          "shooting edits preserve pending map, floor, timer and emission count");
    // Tabs expose only their visible actions to keyboard navigation.
    for(int i=0;i<20&&game.keyboardFocus()!=Action::ShotSpeedDown;++i)key(KEY_TAB);
    check(game.keyboardFocus()==Action::ShotSpeedDown,"shooting control reachable by keyboard");key(KEY_ENTER);
    near(run.player.attributes.shotSpeed,1,"keyboard activates focused shooting control");
    click(380,441);near(run.player.attributes.tearsPerSecond,BalancePreset::ReferenceTears,"reset restores exact 30/11 baseline");
    near(run.player.attributes.rangeTiles,6.5f,"reset restores base range");
    check(game.balanceDraft.roomSizeScale==1.2f&&run.roomSizeScale==1.1f,"shooting reset does not apply or discard map draft");
    // Fire through actual Game input in the generated main-game room.
    key(KEY_ESCAPE);run.player.position=run.arena.rooms[0].center;run.player.position.y=.85f;run.player.velocity={};run.player.fireCooldown=0;
    game.updateCamera(10);mouseEvent(KeyDown,KEY_RIGHT);frame();mouseEvent(KeyUp,KEY_RIGHT);frame();
    check(!run.projectiles.empty(),"actual Game shooting creates a projectile");click(374,642);
    const auto old=run.projectiles.front();const float wait=run.player.fireCooldown;
    check(wait>0,"shooting edit fixture has an active firing wait");
    game.setShooting(5,2,13);game.setShooting(4,1.5f,8);
    check(run.player.fireCooldown==wait&&run.projectiles.front().id==old.id&&run.projectiles.front().life==old.life&&
          run.projectiles.front().attack.speed==old.attack.speed&&run.projectiles.front().attack.maxDistance==old.attack.maxDistance&&
          distance(run.projectiles.front().velocity,old.velocity)==0,
          "repeated edits keep current cooldown and existing projectile birth/lifecycle state");
    const auto shotCount=run.stats.shots;key(KEY_ESCAPE);mouseEvent(KeyDown,KEY_RIGHT);frame();
    check(run.stats.shots==shotCount,"changing Tears does not grant an immediate extra shot");
    for(int i=0;i<80&&run.stats.shots==shotCount;++i)frame();mouseEvent(KeyUp,KEY_RIGHT);frame();
    check(run.stats.shots==shotCount+1,"next shot follows the retained firing wait");
    const auto &born=run.projectiles.back();near(born.attack.speed,12,"new projectile uses edited shot speed");
    near(born.attack.maxDistance,11.f*8/6.5f,"new projectile uses edited range");near(born.damage,11.2f,"shooting controls preserve D07 damage baseline");
    click(374,642);
    run.grant(ItemId::Rail);const auto before=primaryPlayerAttack(run,run.player.shotDamage,false);const float cadence=primaryCadence(run);
    game.setShooting(2,3,4);const auto after=primaryPlayerAttack(run,run.player.shotDamage,false);
    near(after.speed,before.speed*2,"owned speed modifier applied once to new base");near(after.maxDistance,before.maxDistance*.5f,"Range remains independent with owned weapon");
    near(primaryCadence(run),cadence*2,"owned cadence modifier applied once to edited Tears");
    check(run.itemStacks(ItemId::Rail)==1&&after.damage==before.damage,"editing retains owned build and damage");
    game.setShooting(4,1.5f,8);game.setPlayerSpeed(.9f);game.setDefaultZoom(165);
    click(320,605);click(900,605);
    const auto exported=BalancePreset::load(file,run.content->fingerprint());
    check(exported.tearsPerSecond==4&&exported.shotSpeed==1.5f&&exported.rangeTiles==8&&exported.roomSizeScale==1.2f,
          "actual export/remember includes shooting and still-pending map settings");
    game.resetShooting();game.setDefaultZoom(160);click(590,605);
    near(run.player.attributes.tearsPerSecond,4,"load restores Tears");near(run.player.attributes.shotSpeed,1.5f,"load restores Shot Speed");
    near(run.player.attributes.rangeTiles,8,"load restores Range");near(game.cameraZoomPercent(),165,"load retains chosen view");
    check(run.arena.canyon.get()==terrain&&game.hasPendingMapChanges(),"load applies shooting but stages map changes");
    const auto active=game.balancePreset.revision(),draft=game.balanceDraft.revision();const float invalidWait=run.player.fireCooldown;
    auto bytes=exported.json();auto at=bytes.find("\"shot_speed\": 1.5");check(at!=bytes.npos,"invalid shooting mutation exists");
    bytes.replace(at,std::string("\"shot_speed\": 1.5").size(),"\"shot_speed\": 99");
    const auto invalid=directory/"shooting-invalid.json";{std::ofstream out(invalid);out<<bytes;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);
    check(!game.error.empty()&&game.balancePreset.revision()==active&&game.balanceDraft.revision()==draft&&run.player.fireCooldown==invalidWait,
          "invalid shooting load changes neither active/draft settings nor firing state");
    game.balanceFile=file.string();game.perform(Action::LoadBalance);check(game.error.empty(),"valid shooting load recovers");
    std::filesystem::create_directories("artifacts");
    std::filesystem::copy_file(file,"artifacts/d03-shooting-preset.json",std::filesystem::copy_options::overwrite_existing);
    BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
    check(ExportImage(image,"artifacts/d03-shooting-panel.png"),"capture main-game shooting controls");UnloadImage(image);EndDrawing();
    game.applyMapChanges();check(run.player.attributes.tearsPerSecond==4&&run.player.attributes.shotSpeed==1.5f&&run.player.attributes.rangeTiles==8,
          "Apply map retains shooting settings");
    key(KEY_ESCAPE);run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;
    check(run.advanceFloor()&&run.player.attributes.tearsPerSecond==4&&run.player.attributes.shotSpeed==1.5f&&run.player.attributes.rangeTiles==8,
          "shooting settings survive actual floor travel");
    run.finishDebug(false);game.retryExpedition();
    check(game.run->player.attributes.tearsPerSecond==4&&game.run->player.attributes.shotSpeed==1.5f&&game.run->player.attributes.rangeTiles==8&&
          game.run->player.hp==6&&game.run->items.empty(),"retry uses current shooting config with fresh normal player");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.launch(true);
    check(fresh.run->player.attributes.tearsPerSecond==4&&fresh.run->player.attributes.shotSpeed==1.5f&&fresh.run->player.attributes.rangeTiles==8&&
          fresh.run->roomSizeScale==1.2f&&fresh.cameraZoomPercent()==165,"remembered shooting/map/view applied before fresh expedition");fresh.close();
    std::cout<<"PASS D03 actual Game/Renderer tabs, buttons and keyboard; independent shooting, old bullets/cooldown, owned modifiers, invalid-load isolation, export/load, Apply, floor/retry/fresh-session persistence\n";
}
void gaperBalanceInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/
        "docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"gaper.save",file=directory/"gaper-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="57";
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.run->gaperMovementMultiplier==1,"normal Game enables ordinary Gaper conversion from old preset");
    auto &run=*game.run;run.godMode=true;Renderer renderer;
    check(run.player.attributes.tearsPerSecond==1.9272734f&&run.player.attributes.shotSpeed==.9f&&
          run.player.walkingSpeed()==4.8f&&game.cameraZoomPercent()==165&&run.routeLengthScale==.26f,
          "D04 preserves accepted player/shooting/map/view preset");
    int room=-1;EntityId actor=0;
    for(int i=1;i<run.finalRoom()&&room<0;++i)for(const auto &e:run.roomEnemies(i))
        if(e.monster==monsterId(10,1)&&e.champion<0){room=i;actor=e.id;break;}
    check(room>0,"actual expedition naturally contains an ordinary Gaper");
    Vector3 position{};bool found=false;
    for(auto cell:run.arena.floorCells) {
        const Vector3 point{(cell.first+.5f)*FloorTile,.85f,(cell.second+.5f)*FloorTile};
        if(run.arena.roomAt(point)!=room||run.arena.blocked(point,.48f))continue;
        bool safe=true;for(const auto &e:run.roomEnemies(room))if(e.alive&&distance(e.position,point)<6)safe=false;
        if(safe){position=point;found=true;break;}
    }
    check(found,"natural encounter has a safe player observation point");
    run.player.position=position;run.enterRoom(room);game.updateCamera(10);
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"Gaper UI has no error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    click(374,642);click(995,143);check(game.balanceOpen&&game.balanceEnemiesOpen&&!game.balanceShootingOpen,"Enemies tab opens via actual HUD");
    game.setRoomSize(1.2f);const auto terrain=run.arena.canyon.get();const auto at=run.findEnemy(actor)->position;
    const auto velocity=run.findEnemy(actor)->velocity;const float hp=run.findEnemy(actor)->hp;const auto count=run.stats.shots;
    click(710,244);check(run.gaperMovementMultiplier==.95f,"Gaper movement uses 5 percent steps");
    for(int i=0;i<20&&game.keyboardFocus()!=Action::GaperMovementUp;++i)key(KEY_TAB);
    check(game.keyboardFocus()==Action::GaperMovementUp,"visible Gaper control reachable by keyboard");key(KEY_ENTER);
    check(run.gaperMovementMultiplier==1,"keyboard restores reference drive");
    game.setGaperMovement(.5f);
    check(distance(at,run.findEnemy(actor)->position)==0&&distance(velocity,run.findEnemy(actor)->velocity)==0&&
          run.findEnemy(actor)->hp==hp&&run.stats.shots==count&&run.arena.canyon.get()==terrain&&game.hasPendingMapChanges(),
          "live edit retains position, momentum, HP, emissions and pending map");
    key(KEY_ESCAPE);for(int n=0;n<10;++n)frame();
    check(run.findEnemy(actor)&&std::abs(run.findEnemy(actor)->gaper->force-.249f)<.0001f,
          "naturally generated ordinary actor consumes edited drive on real Game updates");
    check(!run.arena.blocked(run.findEnemy(actor)->position,run.findEnemy(actor)->radius),"natural actor remains on physical floor");
    const float beforePursuit=planarDistance(run.findEnemy(actor)->position,run.player.position);
    std::cout<<"D04_CHASE target="<<run.player.position.x<<','<<run.player.position.z<<" actor="<<actor<<" start_distance="<<beforePursuit<<'\n';
    std::cout<<"D04_ROUTE target_blocked_for_gaper="<<run.arena.blocked(run.player.position,.6f)
             <<" player_route="<<run.arena.path(run.findEnemy(actor)->position,run.player.position,.48f).size()
             <<" gaper_route="<<run.arena.path(run.findEnemy(actor)->position,run.player.position,.6f).size()
             <<" center_route="<<run.arena.path(run.findEnemy(actor)->position,run.arena.rooms[room].center,.6f).size()<<'\n';
    for(int n=0;n<600;++n) {
        game.update(Tick);
        if(n%120==119) {
            const auto *e=run.findEnemy(actor);
            std::cout<<"D04_CHASE step="<<n+1<<" actor="<<e->position.x<<','<<e->position.z<<" target="<<run.player.position.x<<','<<run.player.position.z
                     <<" velocity="<<e->velocity.x<<','<<e->velocity.z<<" path="<<e->path.size()<<" direct="<<e->gaper->directPath<<" duration="<<run.stats.duration<<'\n';
        }
        for(const auto &e:run.enemies)if(e.alive&&e.monster==monsterId(10,1))
            check(!run.arena.blocked(e.position,e.radius),"natural Gaper crowd respects canyon cover during pursuit");
    }
    check(planarDistance(run.findEnemy(actor)->position,run.player.position)<beforePursuit-1,
          "natural Gaper makes sustained progress through the generated encounter");
    click(374,642);click(400,441);check(run.gaperMovementMultiplier==1,"reset restores source-derived reference");
    game.setGaperMovement(.65f);click(320,605);click(900,605);
    auto exported=BalancePreset::load(file,run.content->fingerprint());
    check(exported.gaperMovementMultiplier==.65f&&exported.tearsPerSecond==1.9272734f&&exported.roomSizeScale==1.2f,
          "Export/Remember retains chosen shooting and pending map with Gaper override");
    game.setGaperMovement(1);click(590,605);check(run.gaperMovementMultiplier==.65f&&game.hasPendingMapChanges(),"load restores Gaper setting without applying map draft");
    const auto revision=game.balancePreset.revision();const auto draft=game.balanceDraft.revision();
    auto bad=exported.json();auto offset=bad.find("\"gaper_movement_multiplier\": 0.65");check(offset!=bad.npos,"invalid Gaper fixture field exists");
    bad.replace(offset,std::string("\"gaper_movement_multiplier\": 0.65").size(),"\"gaper_movement_multiplier\": 99");
    const auto invalid=directory/"invalid-gaper.json";{std::ofstream out(invalid);out<<bad;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);
    check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.gaperMovementMultiplier==.65f,
          "invalid movement load rejected without partial configuration/state change");
    game.balanceFile=file.string();game.perform(Action::LoadBalance);check(game.error.empty(),"valid reload recovers");
    std::filesystem::create_directories("artifacts");
    std::filesystem::copy_file(file,"artifacts/d04-gaper-preset.json",std::filesystem::copy_options::overwrite_existing);
    BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
    check(ExportImage(image,"artifacts/d04-gaper-panel.png"),"capture Enemies tuning tab");UnloadImage(image);EndDrawing();
    game.applyMapChanges();check(run.gaperMovementMultiplier==.65f,"map regeneration keeps Gaper override");
    key(KEY_ESCAPE);run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;
    check(run.advanceFloor()&&run.gaperMovementMultiplier==.65f,"ordinary floor descent keeps Gaper override");
    run.finishDebug(false);game.retryExpedition();
    check(game.run->gaperMovementMultiplier==.65f&&game.run->player.hp==6,"death retry preserves movement setting and restores ordinary start");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.launch(true);
    check(fresh.run->gaperMovementMultiplier==.65f&&fresh.run->player.attributes.tearsPerSecond==1.9272734f&&fresh.cameraZoomPercent()==165,
          "fresh expedition restores Gaper movement and accepted shooting/view");fresh.close();
    std::cout<<"PASS D04 main Game natural actor + UI mouse/keyboard, drive transition, preserved player settings, preset roundtrip/rejection, map/floor/retry/fresh-session persistence\n";
}
void spiderBalanceInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/
        "docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"spider.save",file=directory/"spider-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="0";
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.run->spiderMovementMultiplier==1&&game.run->gaperMovementMultiplier==1,"main Game enables both selected ordinary movement consumers");
    auto &run=*game.run;run.godMode=true;Renderer renderer;
    check(run.player.attributes.tearsPerSecond==1.9272734f&&run.player.attributes.shotSpeed==.9f&&
          run.player.walkingSpeed()==4.8f&&game.cameraZoomPercent()==165&&run.routeLengthScale==.26f,"D05 preserves accepted player/shooting/map/view preset");
    int room=-1;EntityId actor=0;
    for(int i:{5})for(const auto &e:run.roomEnemies(i))
        if(e.monster==monsterId(85)&&e.champion<0){room=i;actor=e.id;break;}
    check(room>0,"generated expedition contains ordinary Spider");run.jumpDebug(room);
    auto *e=run.findEnemy(actor);const auto initial=e->position;bool positioned=false;
    for(int n=0;n<16;++n) {
        const auto point=add(initial,rotateY({1.6f,0,0},float(n)*Pi/8));
        if(!run.arena.blocked(point,.48f)&&run.arena.sight(initial,point)&&run.arena.roomAt(point)==room){run.player.position=point;positioned=true;break;}
    }
    check(positioned,"natural Spider has legal nearby player approach");game.updateCamera(10);
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"D05 UI has no error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    click(374,642);click(995,143);check(game.balanceEnemiesOpen,"actual Enemies tab opens");
    game.setRoomSize(1.2f);const auto terrain=run.arena.canyon.get();const auto at=e->position,velocity=e->velocity;
    const float hp=e->hp;const auto shots=run.stats.shots;
    click(710,359);check(run.spiderMovementMultiplier==.95f&&run.gaperMovementMultiplier==1,"Spider adjustment independent from Gaper");
    for(int n=0;n<24&&game.keyboardFocus()!=Action::SpiderMovementUp;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::SpiderMovementUp,"Spider drive keyboard navigation");key(KEY_ENTER);
    check(run.spiderMovementMultiplier==1,"keyboard restores Spider reference");game.setSpiderMovement(.5f);
    check(distance(e->position,at)==0&&distance(e->velocity,velocity)==0&&e->hp==hp&&run.stats.shots==shots&&
          run.arena.canyon.get()==terrain&&game.hasPendingMapChanges(),"live edit retains actor/player/map state while paused");
    key(KEY_ESCAPE);bool burst=false,idle=false;float travelled=0;Vector3 previous=e->position;
    for(int n=0;n<600;++n) {
        game.update(Tick);e=run.findEnemy(actor);check(e&&e->alive,"natural actor remains available");
        burst|=e->spider&&e->spider->targetReady;idle|=burst&&e->spider&&!e->spider->targetReady;
        travelled+=planarDistance(previous,e->position);previous=e->position;
        for(const auto &body:run.enemies)if(body.alive&&body.monster==monsterId(85))
            check(!run.arena.blocked(body.position,body.radius),"natural Spider crowd respects generated canyon terrain");
    }
    check(burst&&idle&&travelled>.5f,"real Game updates execute burst and idle with visible motion");
    std::cout<<"D05 natural seed="<<game.seedText<<" room="<<room<<" travelled="<<travelled<<'\n';
    click(374,642);click(400,483);check(run.spiderMovementMultiplier==1,"Spider reset button");
    game.setSpiderMovement(.65f);click(320,605);click(900,605);
    const auto exported=BalancePreset::load(file,run.content->fingerprint());
    check(exported.spiderMovementMultiplier==.65f&&exported.gaperMovementMultiplier==1&&exported.roomSizeScale==1.2f&&exported.defaultZoomPercent==165,
          "Spider export and remember includes pending map and accepted settings");
    game.setSpiderMovement(1);click(590,605);check(run.spiderMovementMultiplier==.65f&&game.hasPendingMapChanges(),"load restores Spider drive and stages map");
    const auto revision=game.balancePreset.revision(),draft=game.balanceDraft.revision();
    auto bad=exported.json();const auto offset=bad.find("\"spider_movement_multiplier\": 0.65");check(offset!=bad.npos,"invalid Spider fixture exists");
    bad.replace(offset,std::string("\"spider_movement_multiplier\": 0.65").size(),"\"spider_movement_multiplier\": 99");
    const auto invalid=directory/"invalid-spider.json";{std::ofstream out(invalid);out<<bad;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);
    check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.spiderMovementMultiplier==.65f,
          "bad Spider preset has no partial effects");game.balanceFile=file.string();game.perform(Action::LoadBalance);
    std::filesystem::create_directories("artifacts");std::filesystem::copy_file(file,"artifacts/d05-spider-preset.json",std::filesystem::copy_options::overwrite_existing);
    BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
    check(ExportImage(image,"artifacts/d05-spider-panel.png"),"capture Spider tuning panel");UnloadImage(image);EndDrawing();
    game.applyMapChanges();check(run.spiderMovementMultiplier==.65f&&run.gaperMovementMultiplier==1,"regeneration retains independent enemy settings");
    key(KEY_ESCAPE);run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;
    check(run.advanceFloor()&&run.spiderMovementMultiplier==.65f,"descent keeps Spider tuning");run.finishDebug(false);game.retryExpedition();
    check(game.run->spiderMovementMultiplier==.65f&&game.run->player.hp==6,"retry restores normal hearts and selected Spider tuning");game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.launch(true);
    check(fresh.run->spiderMovementMultiplier==.65f&&fresh.run->gaperMovementMultiplier==1&&fresh.cameraZoomPercent()==165&&fresh.run->player.attributes.tearsPerSecond==1.9272734f,
          "fresh Game restores independent enemy and accepted user settings");fresh.close();
    std::cout<<"PASS D05 actual Game encounter, UI mouse/keyboard, live edit, export/reload/rejection, map/floor/retry/fresh-session persistence\n";
}
void bombInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"bombs.save",preset=directory/"bombs.json",sourcePreset=directory/"bombs-source.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="129";game.reviewSourceRoomTemplate=32;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=preset.string();game.launch(true);
    if(!game.run||!game.error.empty())throw std::runtime_error("direct bomb room launch: "+game.error);auto &run=*game.run;const int owner=run.room;
    check(run.bombPickups.size()==3&&run.bombClearRewards&&run.player.hp==6&&!run.godMode&&run.dynamite==3,"three natural bombs and normal starting player");
    const auto layout=run.arena.rooms[size_t(owner)];Renderer renderer;
    const auto frame=[&](bool draw=true){game.update(Tick);BeginDrawing();const auto action=draw?renderer.draw(game):Action::None;EndDrawing();game.perform(action);check(game.error.empty(),"bomb UI no errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto floorClick=[&](Vector3 p){p.y=0;auto screen=GetWorldToScreen(p,game.camera);click(int(screen.x),int(screen.y));};
    const auto key=[&](int k){mouseEvent(KeyDown,k);frame();mouseEvent(KeyUp,k);frame();};
    const auto capture=[&](const char *path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path),"bomb screenshot");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();check(renderer.missionShadowsReady(),"bomb scene shadows loaded");capture("artifacts/bombs-room.png");
    floorClick(layout.bombSpawns[1].preferred);for(int n=0;n<90;++n)frame(n%30==0);check(run.dynamite==3,"cannot collect through rocks");
    click(374,642);click(575,143);click(1010,383);
    check(!run.bombClearRewards&&run.bombPickups.size()==3,"AFTER CLEAR DYNAMITE independent of preplaced actors");
    for(int n=0;n<40&&game.keyboardFocus()!=Action::ToggleBombRewards;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::ToggleBombRewards,"bomb keyboard focus");key(KEY_ENTER);check(run.bombClearRewards,"keyboard bomb toggle");click(1010,383);
    capture("artifacts/bombs-rewards-panel.png");game.exportBalancePreset();std::filesystem::copy_file(preset,sourcePreset,std::filesystem::copy_options::overwrite_existing);
    click(970,190);click(275,270);check(game.hasPendingMapChanges()&&run.bombPickups.size()==3,"layout OFF staged");
    click(415,446);check(run.bombPickups.empty()&&run.roomHeartLayouts==0,"Apply removes bomb layout");
    game.exportBalancePreset();std::filesystem::copy_file(preset,"artifacts/bombs-layout-off-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.balanceFile=sourcePreset.string();click(605,606);check(game.hasPendingMapChanges()&&run.roomHeartLayouts==0&&!run.bombClearRewards,"Load stages map and restores live policy");
    click(415,446);check(run.bombPickups.size()==3&&run.roomHeartLayouts==1&&!run.bombClearRewards,"Apply restores layout independent of clear switch");
    game.balanceFile=preset.string();game.exportBalancePreset();game.rememberBalancePreset();
    std::filesystem::copy_file(preset,"artifacts/bombs-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.perform(Action::CloseBalance);game.paused=false;
    int spent=0;
    for(int row=0;row<=2;++row) {
        if(!run.arena.path(run.player.position,layout.bombSpawns[1].preferred,.48f).empty())break;
        game.updateCamera(10);frame();const auto approach=sourceHeartCell(layout,5,row);
        floorClick(approach);for(int n=0;n<480;++n)frame(n%30==0);
        check(planarDistance(run.player.position,approach)<.15f,"mouse reaches bomb-room demolition approach");
        game.updateCamera(10);frame();key(KEY_B);++spent;
        const auto retreat=sourceHeartCell(layout,1,1);floorClick(retreat);
        for(int n=0;n<300;++n)frame(n%30==0);
        if(run.player.hp!=6||run.room!=owner) {capture("artifacts/bombs-retreat-check.png");std::cerr<<"BOMB_RETREAT row="<<row<<" hp="<<run.player.hp<<" room="<<run.room<<" distance="<<planarDistance(run.player.position,approach)<<std::endl;}
        check(!run.dead&&run.player.hp==6&&run.room==owner,"normal-health retreat from real dynamite");
    }
    check(!run.arena.path(run.player.position,layout.bombSpawns[1].preferred,.48f).empty(),"real dynamite opens pocket");
    // Walk back toward the breach before targeting its interior: from the far
    // retreat point at165%, the bomb projections fall behind the bottom HUD.
    for(const auto cell:{std::array<int,2>{3,0},{5,0},{5,1}}) {
        game.updateCamera(10);frame();const auto at=sourceHeartCell(layout,cell[0],cell[1]);floorClick(at);
        for(int n=0;n<360;++n)frame(n%30==0);
        check(!game.paused&&planarDistance(run.player.position,at)<.15f,"visible mouse waypoints return to breach");
    }
    int expected=3-spent;for(const auto &p:layout.bombSpawns)expected+=sourceOrdinaryBombValue(p.subtype);
    for(const auto &p:layout.bombSpawns) {
        game.updateCamera(10);frame();floorClick(p.preferred);
        for(int n=0;n<600;++n){frame(n%30==0);check(!run.arena.blocked(run.player.position,.48f),"bomb mouse path physically clear");}
    }
    capture("artifacts/bombs-collected.png");
    if(run.dynamite!=expected||!run.bombPickups.empty()) {
        std::cerr<<"BOMB_COLLECTION expected="<<expected<<" actual="<<run.dynamite<<" left="<<run.bombPickups.size()<<" room="<<run.room<<" paused="<<game.paused<<" balance="<<game.balanceOpen<<" position="<<run.player.position.x<<","<<run.player.position.z<<std::endl;
        for(const auto &p:run.bombPickups) {const auto screen=GetWorldToScreen(p.position,game.camera);std::cerr<<"LEFT "<<p.position.x<<","<<p.position.z<<" screen="<<screen.x<<","<<screen.y<<" distance="<<planarDistance(p.position,run.player.position)<<" route="<<run.arena.path(run.player.position,p.position,.48f).size()<<std::endl;}
    }
    check(run.dynamite==expected&&run.bombPickups.empty(),"all bombs collected once");
    run.jumpDebug(0);run.jumpDebug(owner);frame();check(run.dynamite==expected&&run.bombPickups.empty(),"revisit no duplicate bombs");
    run.finishDebug(false);game.retryExpedition();check(game.run&&game.run->room==owner&&game.run->bombPickups.size()==3&&game.run->player.hp==6&&!game.run->godMode&&!game.run->bombClearRewards,"retry retains config with fresh actors and starting health");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="129";fresh.reviewSourceRoomTemplate=32;fresh.loadBalancePreset(preset);fresh.launch(true);
    check(fresh.run&&fresh.run->bombPickups.size()==3&&!fresh.run->bombClearRewards&&fresh.cameraZoomPercent()==165&&fresh.run->player.walkingSpeed()==4.8f,"fresh bomb preset retains accepted map/view/feel");fresh.close();
    std::cout<<"PASS main-game bombs, normal-health mouse rock access, keyboard demolition/live policy, Apply/export/load, revisit/retry and fresh preset; spent="<<spent<<" collected_inventory="<<expected<<'\n';
}
void keyInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"keys.save",preset=directory/"keys.json",sourcePreset=directory/"keys-source.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="285";game.reviewSourceRoomTemplate=214;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=preset.string();game.launch(true);
    check(game.run&&game.error.empty(),"direct key room launch");auto &run=*game.run;const int owner=run.room;
    check(owner==5&&run.keyPickups.size()==2&&run.keyClearRewards&&run.player.hp==6&&!run.godMode,"natural room6 ordinary keys at normal health");
    const auto layout=run.arena.rooms[size_t(owner)];Renderer renderer;
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"key UI no errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto floorClick=[&](Vector3 p){p.y=0;auto screen=GetWorldToScreen(p,game.camera);click(int(screen.x),int(screen.y));};
    const auto key=[&](int k){mouseEvent(KeyDown,k);frame();mouseEvent(KeyUp,k);frame();};
    const auto capture=[&](const char *path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path),"key screenshot");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();check(renderer.keyModelReady()&&renderer.missionShadowsReady(),"Synty key mesh and scene shadows loaded");capture("artifacts/keys-room.png");
    floorClick(layout.keySpawns[0].preferred);for(int n=0;n<90;++n)frame();check(run.keys==0,"mouse cannot collect through rocks");
    click(374,642);click(575,143);click(1005,303);
    check(!run.keyClearRewards&&run.keyPickups.size()==2,"AFTER CLEAR KEYS independent of preplaced actors");
    // Keyboard reaches the same live control, then restore OFF for export/reload.
    for(int n=0;n<32&&game.keyboardFocus()!=Action::ToggleKeyRewards;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::ToggleKeyRewards,"keys keyboard focus");key(KEY_ENTER);check(run.keyClearRewards,"keyboard key toggle");click(1005,303);
    capture("artifacts/keys-rewards-panel.png");game.exportBalancePreset();std::filesystem::copy_file(preset,sourcePreset,std::filesystem::copy_options::overwrite_existing);
    click(970,190);click(275,270);check(game.hasPendingMapChanges()&&run.keyPickups.size()==2,"layout OFF staged");
    click(415,446);check(run.keyPickups.empty()&&run.roomHeartLayouts==0,"Apply removes key layout");
    game.exportBalancePreset();std::filesystem::copy_file(preset,"artifacts/keys-layout-off-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.balanceFile=sourcePreset.string();click(605,606);check(game.hasPendingMapChanges()&&run.roomHeartLayouts==0&&!run.keyClearRewards,"Load stages map and restores live key policy");
    click(415,446);check(run.keyPickups.size()==2&&run.roomHeartLayouts==1&&!run.keyClearRewards,"Apply restores preplaced keys independent of reward switch");
    game.balanceFile=preset.string();game.exportBalancePreset();game.rememberBalancePreset();capture("artifacts/keys-panel.png");
    std::filesystem::copy_file(preset,"artifacts/keys-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.perform(Action::CloseBalance);game.paused=false;
    for(int i=0;i<2;++i) {
        game.updateCamera(10);frame();const auto approach=sourceHeartCell(layout,i==0?1:11,i==0?2:4);
        floorClick(approach);for(int n=0;n<480;++n)frame();
        check(planarDistance(run.player.position,approach)<.15f,"mouse reaches key demolition approach");
        game.updateCamera(10);frame();key(KEY_B);
        // Retreat to an interior aisle, away from the nearby clickable passage.
        const auto retreat=sourceHeartCell(layout,i==0?1:6,i==0?5:2);floorClick(retreat);
        for(int n=0;n<240;++n)frame();
        if(run.dead||run.player.hp!=6||run.dynamite!=StartingDynamite-i-1) {capture("artifacts/keys-retreat-check.png");std::cerr<<"KEY_RETREAT i="<<i<<" hp="<<run.player.hp<<" ammo="<<run.dynamite<<" distance="<<planarDistance(run.player.position,approach)<<" target_distance="<<planarDistance(run.player.position,retreat)<<" paused="<<game.paused<<" position="<<run.player.position.x<<","<<run.player.position.z<<" target="<<retreat.x<<","<<retreat.z<<std::endl;}
        check(!run.dead&&run.player.hp==6&&run.dynamite==StartingDynamite-i-1,"normal keyboard dynamite and safe retreat");
        game.updateCamera(10);frame();floorClick(layout.keySpawns[size_t(i)].preferred);
        for(int n=0;n<480;++n){frame();check(!run.arena.blocked(run.player.position,.48f),"mouse path stays physically clear");}
        check(run.keys==i+1,"mouse collects one key after real breach");
    }
    check(run.keyPickups.empty()&&run.keys==2,"both keys collected exactly once");capture("artifacts/keys-collected.png");
    run.jumpDebug(0);run.jumpDebug(owner);frame();check(run.keys==2&&run.keyPickups.empty(),"revisit has no duplicate keys");
    run.finishDebug(false);game.retryExpedition();check(game.run&&game.run->room==owner&&game.run->keyPickups.size()==2&&game.run->player.hp==6&&!game.run->godMode&&!game.run->keyClearRewards,"retry returns to fresh key room with saved policy and normal health");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="285";fresh.reviewSourceRoomTemplate=214;fresh.loadBalancePreset(preset);fresh.launch(true);
    check(fresh.run&&fresh.run->keyPickups.size()==2&&!fresh.run->keyClearRewards&&fresh.cameraZoomPercent()==165&&fresh.run->player.walkingSpeed()==4.8f,"fresh preset loads keys and accepted map/view/feel");fresh.close();
    Game reward(directory/"key-reward.save");reward.themeChoice=ThemeChoice::Canyon;reward.seedText="2";reward.reviewRoomIndex=1;reward.loadBalancePreset(source);reward.launch(true);
    check(reward.run&&reward.run->keyClearRewards,"legacy preset enables selected main-game key rewards");
    reward.run->clearRoomDebug();check(reward.run->keyPickups.size()==1&&reward.run->rooms[1].redHeartAward->variant==30,"main-game natural reward roll produces ordinary key");
    reward.run->player.position=reward.run->keyPickups[0].position;for(int n=0;n<100;++n)reward.update(Tick);
    check(reward.run->keys==1&&reward.run->keyPickups.empty(),"main-game clear key collects once");reward.close();
    std::cout<<"PASS main-game keys/model/shadows, mouse rock access, keyboard dynamite/live policy, staged Apply/export/load, revisit/retry and clear reward\n";
}

void coinLayoutInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    constexpr int seed=1063;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"coin-layout.save",preset=directory/"coin-layout.json",sourcePreset=directory/"coin-layout-source.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText=std::to_string(seed);game.reviewSourceRoomTemplate=30;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=preset.string();game.launch(true);
    check(game.run&&game.error.empty(),"direct coin layout launch");auto &run=*game.run;const int owner=run.room;
    auto count=[&]{return std::count_if(run.moneyPickups.begin(),run.moneyPickups.end(),[&](const auto &p){return p.placedInLayout&&p.room==owner;});};
    check(owner==1&&count()==4&&run.arena.rooms[size_t(owner)].sourceObstacleTemplate==30&&run.roomClear&&run.player.hp==6&&!run.godMode,"natural room2 has four ready coins with normal health");
    int expected=0;std::vector<Vector3> positions;
    for(const auto &coin:run.moneyPickups)if(coin.placedInLayout&&coin.room==owner){expected+=coin.value;positions.push_back(coin.position);check(coin.timing.phase==CoinTiming::Phase::Idle&&coin.timing.collectible(),"preplaced coins idle at launch");}
    Renderer renderer;
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"coin layout UI has no errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto clickFloor=[&](Vector3 p){p.y=0;auto screen=GetWorldToScreen(p,game.camera);click(int(screen.x),int(screen.y));};
    const auto capture=[&](const char *name){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,name),"coin layout capture");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();capture("artifacts/coin-layout-room.png");
    click(374,642);click(575,143);click(680,244);
    check(!run.coinClearRewards&&count()==4,"clear coin switch leaves existing layout coins intact");
    game.exportBalancePreset();std::filesystem::copy_file(preset,sourcePreset,std::filesystem::copy_options::overwrite_existing);
    click(970,190);click(275,270);check(game.hasPendingMapChanges()&&count()==4,"OFF staged without removing layout coins");
    click(415,446);check(count()==0&&run.roomHeartLayouts==0,"mouse Apply removes source coin layout");
    game.exportBalancePreset();std::filesystem::copy_file(preset,"artifacts/coin-layout-off-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.balanceFile=sourcePreset.string();click(605,606);
    check(game.hasPendingMapChanges()&&run.roomHeartLayouts==0&&game.balanceDraft.roomHeartLayouts==1&&count()==0,"mouse Load stages source map without recreating coins early");
    click(415,446);check(count()==4&&run.roomHeartLayouts==1&&!run.coinClearRewards,"loaded SOURCE Apply restores layout independently of clear coins");
    game.balanceFile=preset.string();game.exportBalancePreset();game.rememberBalancePreset();capture("artifacts/coin-layout-panel.png");
    std::filesystem::copy_file(preset,"artifacts/coin-layout-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.perform(Action::CloseBalance);game.paused=false;const auto before=run.money();
    for(auto point:positions) {
        game.updateCamera(10);frame();clickFloor(point);
        for(int n=0;n<360;++n){frame();check(!run.arena.blocked(run.player.position,.48f),"actual mouse navigation respects central rock");}
    }
    check(count()==0&&run.money()==before+expected&&run.dynamite==StartingDynamite,"actual mouse collects exact total without dynamite");capture("artifacts/coin-layout-collected.png");
    run.jumpDebug(0);run.jumpDebug(owner);frame();check(count()==0&&run.money()==before+expected,"revisit does not regenerate collected coins");
    run.finishDebug(false);game.retryExpedition();
    check(game.run&&game.run->room==owner&&game.run->player.hp==6&&!game.run->godMode&&!game.run->coinClearRewards&&std::count_if(game.run->moneyPickups.begin(),game.run->moneyPickups.end(),[&](const auto &p){return p.placedInLayout&&p.room==owner;})==4,"retry returns to original four coins at normal health");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=std::to_string(seed);fresh.reviewSourceRoomTemplate=30;fresh.loadBalancePreset(preset);fresh.launch(true);
    check(fresh.run&&fresh.run->room==owner&&fresh.cameraZoomPercent()==165&&fresh.run->player.walkingSpeed()==4.8f&&!fresh.run->coinClearRewards&&std::count_if(fresh.run->moneyPickups.begin(),fresh.run->moneyPickups.end(),[&](const auto &p){return p.placedInLayout&&p.room==owner;})==4,"fresh schema22 load retains layout, independent rewards and accepted feel");fresh.close();
    std::cout<<"PASS actual Game/Renderer preplaced coins, mouse toggle/Apply/staged Load/collection, revisit/retry and preset reload\n";
}
void chestLayoutInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    constexpr int seed=375; // Natural complete source31 room at the accepted preset.
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"chest-layout.save",preset=directory/"chest-layout.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText=std::to_string(seed);game.reviewSourceRoomTemplate=31;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=preset.string();game.launch(true);
    check(game.run&&game.error.empty(),"direct preplaced chest launch");auto &run=*game.run;
    const int owner=run.room;check(run.arena.rooms[size_t(owner)].sourceObstacleTemplate==31&&run.chests.size()==1&&!run.chests[0].opened&&run.player.hp==6&&!run.godMode,"normal-health source31 chest ready at entry");
    const auto at=run.chests[0].position;Renderer renderer;
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"chest layout UI has no errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto clickFloor=[&](Vector3 p){p.y=0;auto screen=GetWorldToScreen(p,game.camera);click(int(screen.x),int(screen.y));};
    const auto capture=[&](const char *name){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,name),"chest layout capture");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();capture("artifacts/chest-layout-closed.png");
    check(renderer.chestModelReady(),"accepted chest model loaded on first entry");
    clickFloor(at);for(int n=0;n<90;++n)frame();check(!run.chests[0].opened,"mouse cannot open enclosed chest");
    click(374,642);click(575,143);click(970,190);check(game.balanceRoomHeartsOpen,"room layouts tab opens with mouse");
    click(275,270);check(game.hasPendingMapChanges()&&run.chests.size()==1,"OFF staged until Apply");
    click(415,446);check(run.chests.empty()&&run.roomHeartLayouts==0,"mouse Apply removes arrangement");
    game.exportBalancePreset();std::filesystem::copy_file(preset,"artifacts/chest-layout-off-preset.json",std::filesystem::copy_options::overwrite_existing);
    click(510,270);check(game.hasPendingMapChanges()&&run.chests.empty(),"SOURCE staged until Apply");
    click(415,446);check(run.chests.size()==1&&run.roomHeartLayouts==1&&run.room==owner,"mouse Apply restores closed chest in current room");
    game.exportBalancePreset();game.rememberBalancePreset();capture("artifacts/chest-layout-panel.png");
    std::filesystem::copy_file(preset,"artifacts/chest-layout-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.perform(Action::CloseBalance);game.paused=false;game.updateCamera(10);frame();
    const auto approach=sourceHeartCell(run.arena.rooms[size_t(owner)],3,3);clickFloor(approach);
    for(int n=0;n<480;++n)frame();check(planarDistance(run.player.position,approach)<.15f,"mouse reaches demolition approach");
    // Normal keyboard bomb placement, then retreat beyond the retained blast.
    mouseEvent(KeyDown,KEY_B);frame();mouseEvent(KeyUp,KEY_B);frame();
    const auto retreat=add(approach,{-6,0,0});clickFloor(retreat);
    for(int n=0;n<240;++n)frame();
    check(!run.dead&&run.dynamite==StartingDynamite-1,"normal-health player uses and survives inventory dynamite");
    check(std::any_of(run.arena.breakables.begin(),run.arena.breakables.end(),[&](const auto &b){return b.room==owner&&b.destroyed;}),"actual bomb opens enclosing rocks");
    game.updateCamera(10);frame();clickFloor(at);for(int n=0;n<480;++n)frame();
    check(run.chests.size()==1&&run.chests[0].opened&&!run.arena.blocked(run.player.position,.48f),"actual mouse route enters breach and opens solid chest");
    check(std::all_of(run.chests[0].contents.begin(),run.chests[0].contents.end(),[](const auto &d){return d.delivered;}),"preplaced contents delivered once");capture("artifacts/chest-layout-open.png");
    run.jumpDebug(0);run.jumpDebug(owner);frame();check(run.chests.size()==1&&run.chests[0].opened,"revisit retains opened layout chest");
    run.finishDebug(false);game.retryExpedition();check(game.run&&game.run->room==owner&&game.run->chests.size()==1&&!game.run->chests[0].opened&&!game.run->godMode&&game.run->player.hp==6,"death retry returns to fresh natural chest with normal health");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=std::to_string(seed);fresh.reviewSourceRoomTemplate=31;fresh.loadBalancePreset(preset);fresh.launch(true);
    check(fresh.run&&fresh.run->room==owner&&fresh.run->chests.size()==1&&fresh.cameraZoomPercent()==165&&fresh.run->player.walkingSpeed()==4.8f,"fresh exported preset retains arrangement and accepted feel");fresh.close();
    std::cout<<"PASS actual Game/Renderer preplaced chest, mouse Apply/navigation/opening, keyboard demolition, revisit/retry and preset reload\n";
}
void chestInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"chests.save",preset=directory/"chests.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="50";game.reviewRoomIndex=1;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=preset.string();game.launch(true);
    check(game.run&&game.error.empty()&&game.run->room==1&&game.run->chestClearRewards&&!game.run->godMode&&game.run->player.hp==6,"normal-health chest encounter and legacy preset migration");
    auto &run=*game.run;Renderer renderer;
    const auto frame=[&]{game.update(Tick);BeginDrawing();auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"chest UI has no errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto capture=[&](const char *path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path),"chest screenshot");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();click(374,642);click(575,143);check(game.balanceRewardsOpen,"reward panel by mouse");
    click(965,244);check(!run.chestClearRewards&&run.coinClearRewards&&run.redHeartClearRewards,"chest toggle independent of existing rewards");
    game.setRoomHeartLayouts(0);click(965,244);
    check(run.chestClearRewards&&run.roomHeartLayouts==1&&game.hasPendingMapChanges(),"chest toggle retains staged map edits");
    game.exportBalancePreset();game.rememberBalancePreset();
    check(BalancePreset::load(preset,run.content->fingerprint()).chestClearRewards,"chest preset export");
    game.setRoomHeartLayouts(1);game.exportBalancePreset();game.rememberBalancePreset();
    std::filesystem::copy_file(preset,"artifacts/chest-preset.json",std::filesystem::copy_options::overwrite_existing);
    capture("artifacts/chest-panel.png");game.perform(Action::CloseBalance);game.paused=false;run.clearRoomDebug();
    check(run.chests.size()==1&&!run.chests[0].opened,"natural reward chest generated");
    const auto at=run.chests[0].position;run.player.position=add(at,{3,0,0});
    check(!run.arena.blocked(run.player.position,.48f),"approach fixture is clear");
    game.updateCamera(10);frame();check(renderer.chestModelReady(),"both textured chest model parts loaded");capture("artifacts/chest-closed.png");
    const auto clickFloor=[&](Vector3 point){point.y=0;auto screen=GetWorldToScreen(point,game.camera);click(int(screen.x),int(screen.y));};
    const auto keys=run.keys;const auto money=run.money();clickFloor(at);
    for(int n=0;n<180;++n)frame();
    check(run.chests[0].opened&&run.keys==keys,"actual mouse approach opens chest without key");
    check(std::all_of(run.chests[0].contents.begin(),run.chests[0].contents.end(),[](auto &d){return d.delivered;}),"all chest drops delivered in actual game");
    capture("artifacts/chest-open.png");
    run.player.position=add(at,{3,0,0});game.updateCamera(10);
    // Far enough beyond the scattered coins that their normal click targets
    // cannot intercept this ground-navigation check.
    const auto beyond=add(at,{-5,0,0});clickFloor(beyond);
    const auto clickedDestination=run.moveDestination();
    for(int n=0;n<240;++n) {
        frame();check(!sphereBox(run.player.position,.48f,chestGeometry::body(at)),"actual mouse route respects opened chest collision");
    }
    if(planarDistance(run.player.position,beyond)>=.15f) {
        std::cout<<"CHEST_ROUTE target="<<beyond.x<<','<<beyond.z<<" player="<<run.player.position.x<<','<<run.player.position.z;
        if(clickedDestination)std::cout<<" requested="<<clickedDestination->x<<','<<clickedDestination->z;
        std::cout<<" moving="<<bool(run.moveDestination())<<" paused="<<game.paused<<" distance="<<planarDistance(run.player.position,beyond)<<'\n';
        capture("artifacts/chest-collision-route.png");
    }
    check(planarDistance(run.player.position,beyond)<.15f,"actual mouse click beyond opened chest routes around it");
    std::vector<Vector3> coins;for(auto &coin:run.moneyPickups)if(coin.sourceSubtype&&coin.room==run.room)coins.push_back(coin.position);
    for(auto pos:coins){clickFloor(pos);for(int n=0;n<120;++n)frame();}
    check(run.money()==money+3,"three penny contents collected exactly once with mouse");
    run.jumpDebug(0);run.jumpDebug(1);frame();check(run.chests[0].opened&&run.money()==money+3,"actual revisit retains opened state and money");
    run.finishDebug(false);game.retryExpedition();check(game.run->room==1&&game.run->chestClearRewards&&game.run->chests.empty()&&!game.run->godMode,"retry returns to original encounter, no stale chest");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="50";fresh.reviewRoomIndex=1;fresh.loadBalancePreset(preset);fresh.launch(true);
    check(fresh.run&&fresh.run->chestClearRewards&&fresh.cameraZoomPercent()==165&&fresh.run->player.walkingSpeed()==4.8f,"fresh preset load preserves chest and accepted feel");fresh.close();
    std::cout<<"PASS actual Game/Renderer chest, mouse controls/collection, staged map boundary, export/remember/fresh load, revisit/retry\n";
}
void coinRewardInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"coins.save",preset=directory/"coins.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="20";game.reviewRoomIndex=1;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=preset.string();game.launch(true);
    check(game.run&&game.error.empty()&&game.run->room==1&&game.run->coinClearRewards&&!game.run->godMode&&game.run->player.hp==6,"direct coin encounter with normal health and schema5 migration");
    auto &run=*game.run;Renderer renderer;
    for(const auto &coin:run.moneyPickups)check(run.arena.roomAt(coin.position)!=1,"ordinary new room has no legacy random piles");
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"coin UI has no errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto capture=[&](const char *path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path),"coin UI capture");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();click(374,642);click(575,143);
    check(game.balanceRewardsOpen&&!game.balanceRoomHeartsOpen,"reward panel opens by mouse");
    click(680,244);check(!run.coinClearRewards&&run.redHeartClearRewards,"coins switch independent of hearts");
    click(680,244);check(run.coinClearRewards,"coin switch enables future clears");
    game.setRoomHeartLayouts(0);click(680,244);
    check(!run.coinClearRewards&&run.roomHeartLayouts==1&&game.hasPendingMapChanges(),"live coin edit preserves pending map edits");
    game.exportBalancePreset();game.rememberBalancePreset();capture("artifacts/coin-rewards-panel.png");
    check(!BalancePreset::load(preset,run.content->fingerprint()).coinClearRewards,"disabled coin setting exported");
    click(680,244);game.setRoomHeartLayouts(1);game.exportBalancePreset();game.rememberBalancePreset();
    std::filesystem::copy_file(preset,"artifacts/coin-rewards-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.perform(Action::CloseBalance);game.paused=false;run.clearRoomDebug();
    const auto &award=run.rooms[1].redHeartAward;check(award&&award->variant==20&&award->subtype==1&&award->delivered,"natural ordinary first clear pays source penny");
    auto coin=std::find_if(run.moneyPickups.begin(),run.moneyPickups.end(),[](const auto &c){return c.sourceSubtype==1;});check(coin!=run.moneyPickups.end(),"coin rendered actor exists");
    auto at=coin->position;run.player.position=add(at,{2,0,0});game.updateCamera(10);frame();capture("artifacts/coin-reward-appear.png");
    const auto before=run.money();run.player.position=at;for(int n=0;n<100;++n)frame();
    check(run.money()==before+1&&std::none_of(run.moneyPickups.begin(),run.moneyPickups.end(),[](const auto &c){return c.sourceSubtype!=0;}),"real Game updates collect once and remove presentation");
    run.jumpDebug(0);run.jumpDebug(1);frame();check(run.money()==before+1,"revisit preserves collection");
    run.finishDebug(false);game.retryExpedition();check(game.run->room==1&&game.run->coinClearRewards&&!game.run->godMode&&game.run->player.hp==6,"death retry returns to coin encounter");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="20";fresh.reviewRoomIndex=1;fresh.loadBalancePreset(preset);fresh.launch(true);
    check(fresh.run&&fresh.run->coinClearRewards&&fresh.run->room==1&&fresh.cameraZoomPercent()==165&&fresh.run->player.walkingSpeed()==4.8f,"fresh main-game preset reload preserves accepted settings and coins");fresh.close();
    std::cout<<"PASS actual Game/Renderer ordinary coins, mouse toggle, pending map boundary, export/remember/reload, collection/revisit/retry\n";
}
void combatRockRoomInputCheck(const std::filesystem::path &directory,int variant=4) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const int expectedRoom=variant==109?6:variant==108?5:4,count=variant==109?5:variant==108?4:2;
    const std::string seed=variant==109?"2942":variant==108?"117":"268",prefix=variant==109?"source-five-gaper":variant==108?"source-four-gaper":"source-combat-rock";
    const auto save=directory/(prefix+".save"),file=directory/(prefix+".json");
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText=seed;game.reviewSourceRoomTemplate=variant;
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.error.empty(),"source combat-room main-game launch");auto &run=*game.run;Renderer renderer;
    check(run.room==expectedRoom&&run.arena.rooms[size_t(expectedRoom)].sourceCombatTemplate==variant&&run.livingEnemies()==count&&!run.godMode&&run.player.hp==6,"review starts inside natural ordinary recorded Gaper fight");
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"source combat-room UI has no error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto capture=[&](const std::string &path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path.c_str()),"capture source combat-room review");UnloadImage(im);EndDrawing();};
    game.updateCamera(10);frame();capture("artifacts/"+prefix+"-room.png");
    click(374,642);click(575,143);click(975,189);check(game.balanceRoomHeartsOpen,"ROOM LAYOUTS opens by mouse");
    const auto terrain=run.arena.canyon.get();click(270,270);
    check(game.balanceDraft.roomHeartLayouts==0&&run.roomHeartLayouts==1&&game.hasPendingMapChanges()&&run.arena.canyon.get()==terrain,"OFF remains staged during active combat");
    click(400,447);check(run.roomHeartLayouts==0&&run.arena.rooms[size_t(expectedRoom)].sourceCombatTemplate!=variant,"Apply removes source combat-room during combat without restart");
    click(500,270);click(400,447);check(run.roomHeartLayouts==1&&run.arena.rooms[size_t(expectedRoom)].sourceCombatTemplate==variant,"SOURCE plus Apply restores complete arrangement");
    check(run.player.walkingSpeed()==4.8f&&game.cameraZoomPercent()==165&&run.player.attributes.tearsPerSecond==1.9272734f&&run.routeLengthScale==.26f,"accepted movement/shooting/map/view retained");
    game.exportBalancePreset();game.rememberBalancePreset();std::filesystem::copy_file(file,"artifacts/"+prefix+"-preset.json",std::filesystem::copy_options::overwrite_existing);
    capture("artifacts/"+prefix+"-layouts.png");
    run.finishDebug(false);game.retryExpedition();check(game.run->room==expectedRoom&&game.run->livingEnemies()==count&&!game.run->godMode&&game.run->player.hp==6,"retry returns to the ordinary source combat-room encounter");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText=seed;fresh.reviewSourceRoomTemplate=variant;fresh.loadBalancePreset(file);fresh.launch(true);
    check(fresh.run&&fresh.run->room==expectedRoom&&fresh.cameraZoomPercent()==165&&fresh.run->arena.rooms[size_t(expectedRoom)].sourceObstacleTemplate==variant,"exported preset reloads complete encounter in fresh game");fresh.close();
    std::cout<<"PASS actual Game/Renderer source"<<variant<<" natural entry, mouse OFF/SOURCE/Apply during combat, export/remember/reload and retry\n";
}
void heartRockRoomInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"heart-rock-room.save";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="934";game.reviewSourceRoomTemplate=91;game.loadBalancePreset(source);game.rememberBalancePreset();game.launch(true);
    check(game.run&&game.error.empty(),"source rock room launches with accepted preset");
    auto &run=*game.run;Renderer renderer;
    int owner=-1;for(int i=0;i<run.arena.roomCount();++i)if(run.arena.rooms[size_t(i)].sourceObstacleTemplate==91)owner=i;
    check(owner==3&&run.room==owner,"native descriptor seed934 launches directly in generated room4");
    check(!run.godMode&&run.player.hp==6&&run.dynamite==StartingDynamite,"review launch retains normal health, inventory and damage");
    run.godMode=true;
    auto point=[&](int x,int y) {
        const auto &layout=run.arena.rooms[size_t(owner)];const auto size=sub(layout.bounds.max,layout.bounds.min);
        const float cell=std::min(size.x*.86f/13,size.z*.86f/7);
        return add(layout.center,{(x-6)*cell,0,(y-3)*cell});
    };
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"source rock room frame has no error");};
    const auto capture=[&](const char *path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path),"capture source rock room");UnloadImage(im);EndDrawing();};
    check(!run.arena.blocked(run.player.position,.48f),"direct review entry starts outside rock formation");
    run.player.position=point(3,3);auto health=run.player.sourceHealth();health.addRed(-3);run.player.setSourceHealth(health);
    game.updateCamera(10);frame();capture("artifacts/source-heart-rock-room-closed.png");
    check(run.roomClear&&run.livingEnemies()==0&&run.heartPickups.size()==2,"ordinary obstacle room has two preplaced pickups and no enemies");
    game.perform(Action::Dynamite);frame();
    check(run.dynamite==StartingDynamite-1,"normal PLACE action spends dynamite");
    for(int n=0;n<240;++n)frame();capture("artifacts/source-heart-rock-room-open.png");
    const auto target=point(5,3);check(!run.arena.path(run.player.position,target,.48f).empty(),"rendered room opening has matching navigation");
    run.player.position=run.arena.move(run.player.position,sub(target,run.player.position),.48f);frame();check(run.player.hp==4,"half heart collects after the opening");
    run.player.position=point(9,3);game.perform(Action::Dynamite);frame();for(int n=0;n<240;++n)frame();
    const auto full=point(7,3);run.player.position=run.arena.move(run.player.position,sub(full,run.player.position),.48f);frame();check(run.player.hp==6,"full heart collects after the second opening");
    for(int n=0;n<30;++n)frame();run.jumpDebug(0);run.jumpDebug(owner);frame();check(run.heartPickups.empty(),"collected hearts remain consumed after revisit");
    game.setRoomHeartLayouts(0);check(game.hasPendingMapChanges()&&run.arena.rooms[size_t(owner)].sourceObstacleTemplate==91,"OFF stages without removing rocks");
    game.applyMapChanges();check(game.error.empty()&&run.arena.rooms[size_t(owner)].sourceObstacleTemplate<0,"Apply removes source arrangement");
    game.setRoomHeartLayouts(1);game.applyMapChanges();check(game.error.empty()&&run.arena.rooms[size_t(owner)].sourceObstacleTemplate==91&&run.heartPickups.size()==2,"Apply restores complete room and pickup state");
    check(game.cameraZoomPercent()==165&&game.balancePreset.shotSpeed==.9f,"accepted view/shooting retained");
    const auto exported=directory/"native-room-preset.json";game.balancePreset.save(exported);
    std::filesystem::copy_file(exported,"artifacts/native-room-eligibility-preset.json",std::filesystem::copy_options::overwrite_existing);
    run.finishDebug(false);game.retryExpedition();
    check(game.run->room==owner&&game.run->player.hp==6&&!game.run->godMode&&game.run->dynamite==StartingDynamite,"death retry returns to the generated source room with ordinary starting state");
    game.setRoomHeartLayouts(0);game.applyMapChanges();game.run->finishDebug(false);game.retryExpedition();
    check(game.run->room==0,"retry with disabled template explicitly returns to the entrance");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="934";fresh.reviewSourceRoomTemplate=91;fresh.loadBalancePreset(exported);fresh.rememberBalancePreset();fresh.launch(true);
    check(fresh.run&&fresh.run->room==owner&&!fresh.run->godMode&&fresh.cameraZoomPercent()==165,"fresh load keeps settings and direct natural room entry");fresh.close();
    Game missing(directory/"missing-review.save");missing.themeChoice=ThemeChoice::Canyon;missing.seedText="934";missing.reviewSourceRoomTemplate=999999;
    const auto previousId=missing.campaign.data().nextRunId;bool rejected=false;try{missing.launch(true);}catch(const std::exception &){rejected=true;}
    check(rejected&&!missing.run&&missing.campaign.data().nextRunId==previousId,"absent review template cannot fabricate a room or begin the campaign expedition");
    std::cout<<"PASS actual Game/Renderer source91, PLACE action, both pickups, revisit, staged OFF/Apply and accepted settings\n";
}
void roomHeartsInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"room-hearts.save",file=directory/"room-hearts-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="69";game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.run->roomHeartLayouts==1&&game.error.empty(),"main game enables selected source heart layers after preset migration");
    auto &run=*game.run;Renderer renderer;run.godMode=true;
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"room-heart UI has no error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    const auto capture=[&](const char *path){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,path),"capture room-heart check");UnloadImage(im);EndDrawing();};
    click(374,642);click(575,143);click(975,189);check(game.balanceRoomHeartsOpen,"room layouts page opens by mouse");
    const auto terrain=run.arena.canyon.get();const auto before=run.heartPickups.size();click(880,270);
    check(game.balanceDraft.roomHeartLayouts==2&&run.roomHeartLayouts==1&&game.hasPendingMapChanges()&&run.arena.canyon.get()==terrain&&run.heartPickups.size()==before,"layout edit stages without touching pickups or terrain");
    click(330,605);const auto exported=BalancePreset::load(file,run.content->fingerprint());check(exported.roomHeartLayouts==2&&exported.defaultZoomPercent==165&&exported.roomSizeScale==1.1f,"pending layout mode exports with accepted settings");
    game.setRoomHeartLayouts(0);click(590,605);check(game.balanceDraft.roomHeartLayouts==2&&run.roomHeartLayouts==1,"loading stages map layout mode");
    const auto revision=game.balancePreset.revision(),draft=game.balanceDraft.revision();auto bad=exported.json();auto at=bad.find("\"room_heart_layouts\": 2");check(at!=bad.npos,"invalid layout fixture exists");bad.replace(at,std::string("\"room_heart_layouts\": 2").size(),"\"room_heart_layouts\": 9");
    const auto invalid=directory/"invalid-room-hearts.json";{std::ofstream out(invalid);out<<bad;}game.balanceFile=invalid.string();game.perform(Action::LoadBalance);
    check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.arena.canyon.get()==terrain,"invalid layout preset has no partial effect");game.balanceFile=file.string();game.perform(Action::LoadBalance);
    click(400,447);check(run.roomHeartLayouts==2&&!game.hasPendingMapChanges()&&run.heartPickups.size()==2,"Apply regenerates current floor with full and half layout actors");
    check(game.cameraZoomPercent()==165&&run.player.walkingSpeed()==4.8f&&run.player.attributes.tearsPerSecond==1.9272734f&&run.routeLengthScale==.26f,"accepted movement/shooting/view/map remain");
    capture("artifacts/d09a-room-hearts-panel.png");game.rememberBalancePreset();game.exportBalancePreset();std::filesystem::copy_file(file,"artifacts/d09a-room-hearts-preset.json",std::filesystem::copy_options::overwrite_existing);key(KEY_ESCAPE);
    // Rejected configuration deliberately pauses Game; successful loading does
    // not implicitly resume combat. Resume through normal keyboard input.
    if(game.paused)key(KEY_ESCAPE);check(!game.paused&&!game.balanceOpen,"resume after rejected-preset recovery");
    const auto full=run.heartPickups[0],half=run.heartPickups[1];check(full.amount==2&&half.amount==1&&!run.rooms[size_t(full.room)].visited,"actors exist before first visit");
    run.jumpDebug(full.room);for(auto &e:run.enemies){e.state=EnemyState::Stunned;e.stateTime=1000;}check(run.livingEnemies()>0&&!run.roomClear,"room not cleared before placed heart collection");
    run.player.position=add(full.position,{0,0,3});game.updateCamera(10);frame();capture("artifacts/d09a-room-hearts-both.png");
    run.player.position=full.position;frame();check(run.player.hp==6&&run.heartPickups.size()==2,"full health refuses preplaced full heart");
    auto health=run.player.sourceHealth();health.addRed(-3);run.player.setSourceHealth(health);frame();check(run.player.hp==5,"full layout pickup heals two halves immediately");
    run.player.position=half.position;frame();check(run.player.hp==6,"half layout pickup heals one half immediately");for(int n=0;n<30;++n)frame();check(run.heartPickups.empty(),"collection effects expire");
    run.jumpDebug(0);run.jumpDebug(full.room);frame();check(run.heartPickups.empty(),"revisit never respawns consumed layout actors");
    click(374,642);click(575,143);click(975,189);
    for(int n=0;n<30&&game.keyboardFocus()!=Action::RoomHeartsOff;++n)key(KEY_TAB);check(game.keyboardFocus()==Action::RoomHeartsOff,"layout choice accessible by keyboard");key(KEY_ENTER);
    check(game.balanceDraft.roomHeartLayouts==0&&run.roomHeartLayouts==2&&run.heartPickups.empty(),"keyboard selection remains staged after exploration");
    game.setRedHeartAppearanceSpeed(4);check(run.heartPickups.empty()&&game.balanceDraft.roomHeartLayouts==0,"live appearance edit cannot respawn placed hearts or erase map draft");
    game.setRoomHeartLayouts(2);game.setRedHeartAppearanceSpeed(1);game.rememberBalancePreset();key(KEY_ESCAPE);
    run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;check(run.advanceFloor()&&run.roomHeartLayouts==2&&run.heartPickups.empty(),"next floor retains setting but no wrong-stage source hearts");
    run.finishDebug(false);game.retryExpedition();check(game.run->roomHeartLayouts==2&&game.run->heartPickups.size()==2,"retry regenerates selected opening-floor layout");game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="69";fresh.launch(true);check(fresh.run->roomHeartLayouts==2&&fresh.run->heartPickups.size()==2&&fresh.cameraZoomPercent()==165,"fresh application loads remembered layout setting");fresh.close();
    std::cout<<"PASS main Game preplaced full/half, mouse/keyboard controls, staged apply/export/load/reject, combat collection/revisit, floors/retry and fresh launch\n";
}
void redHeartRewardsInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"red-hearts.save",file=directory/"red-hearts-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="69";
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.run->redHeartClearRewards&&game.run->player.attributes.luck==0,"main Game enables D09a with migrated baseline Luck");
    auto &run=*game.run;run.godMode=true;Renderer renderer;
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"D09 UI without errors");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    const auto capture=[&](const char *file){std::filesystem::create_directories("artifacts");BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();check(ExportImage(image,file),"capture D09 handoff");UnloadImage(image);EndDrawing();};
    run.jumpDebug(2);check(run.livingEnemies()==2,"ordinary generated D08 witness has two Gapers");
    // Hold AI for deterministic input verification, retaining natural generation,
    // actual Game mouse primary fire, death/morph/clear and reward production.
    for(int body=0;body<10&&!run.roomClear;++body) {
        Enemy *target=nullptr;for(auto &e:run.enemies)if(e.alive){e.state=EnemyState::Stunned;e.stateTime=1000;if(!target)target=&e;}
        if(!target){frame();continue;}
        const auto id=target->id;const auto identity=target->monster;
        run.player.position=add(target->position,{0,0,3});check(!run.arena.blocked(run.player.position,.48f),"legal aligned firing point");game.updateCamera(10);
        const auto pixel=GetWorldToScreen(add(target->position,{0,.25f,0}),game.camera);mouseEvent(MousePosition,int(pixel.x),int(pixel.y));frame();mouseEvent(MouseDown,MOUSE_BUTTON_RIGHT);
        for(int n=0;n<700&&!run.roomClear;++n){frame();target=run.findEnemy(id);if(!target||!target->alive||target->monster!=identity)break;}
        mouseEvent(MouseUp,MOUSE_BUTTON_RIGHT);frame();
    }
    check(run.roomClear&&run.heartPickups.size()==1&&run.heartPickups[0].amount==2&&run.heartPickups[0].sourceSubtype==1,"actual Game mouse-fire clear produces the expected full red heart");
    capture("artifacts/d09a-timed-heart-birth.png");const auto pickup=run.heartPickups[0];run.player.position=pickup.position;
    const auto birthFrame=run.heartPickups[0].timing.frame;
    click(374,642);click(575,143);click(850,383);
    check(std::abs(run.redHeartAppearanceSpeed-1.05f)<.0001f&&run.heartPickups[0].timing.appearanceSpeed==1,"mouse appearance edit changes future births, retains current actor");
    const auto pausedFrame=run.heartPickups[0].timing.frame;for(int n=0;n<15;++n)frame();
    check(run.heartPickups[0].timing.frame==pausedFrame&&pausedFrame>=birthFrame,"tuning pause freezes birth clock");
    for(int n=0;n<30&&game.keyboardFocus()!=Action::ResetHeartAppearance;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::ResetHeartAppearance,"appearance reset reachable with keyboard");key(KEY_ENTER);
    check(run.redHeartAppearanceSpeed==1,"keyboard appearance reset");key(KEY_ESCAPE);
    for(int n=0;n<70;++n)frame();capture("artifacts/d09a-timed-heart-idle.png");
    check(run.heartPickups.size()==1&&run.player.hp==6,"full health refuses pickup in actual Game");
    auto health=run.player.sourceHealth();health.addRed(-2);run.player.setSourceHealth(health);frame();
    check(run.heartPickups.size()==1&&run.player.hp==6&&run.heartPickups[0].timing.phase==RedHeartTiming::Phase::Collect,"natural heart heals immediately at admission and starts collection effect");
    capture("artifacts/d09a-timed-heart-collection.png");for(int n=0;n<30;++n)frame();check(run.heartPickups.empty(),"collection presentation expires");
    const auto award=*run.rooms[2].redHeartAward;run.jumpDebug(0);run.jumpDebug(2);frame();check(run.heartPickups.empty(),"collected natural reward stays collected on revisit");
    click(374,642);click(575,143);check(game.balanceOpen&&game.balanceRewardsOpen,"Rewards tab via actual mouse");
    game.setRoomSize(1.2f);const auto terrain=run.arena.canyon.get();click(350,244);click(850,304);
    check(!run.redHeartClearRewards&&run.player.attributes.luck==1&&game.hasPendingMapChanges()&&run.arena.canyon.get()==terrain,"reward switch and Luck live, map still staged");
    for(int n=0;n<30&&game.keyboardFocus()!=Action::ResetRewardLuck;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::ResetRewardLuck,"reward reset reachable with keyboard");key(KEY_ENTER);check(run.player.attributes.luck==0&&!run.redHeartClearRewards,"Luck reset leaves reward switch alone");
    game.setRedHeartRewards(true,5);game.setRedHeartAppearanceSpeed(.5f);click(330,605);const auto exported=BalancePreset::load(file,run.content->fingerprint());
    check(exported.redHeartAppearanceSpeed==.5f&&exported.redHeartClearRewards&&exported.playerLuck==5&&exported.roomSizeScale==1.2f&&exported.defaultZoomPercent==165,"reward settings and staged map exported together");
    game.setRedHeartRewards(false,-3);game.setRedHeartAppearanceSpeed(4);click(590,605);check(run.redHeartAppearanceSpeed==.5f&&run.redHeartClearRewards&&run.player.attributes.luck==5&&game.hasPendingMapChanges(),"valid load applies rewards only to future clears");
    check(run.rooms[2].redHeartAward->pickupSeed==award.pickupSeed&&run.heartPickups.empty(),"editing/loading never rerolls paid room");
    const auto revision=game.balancePreset.revision(),draft=game.balanceDraft.revision();auto bad=exported.json();const auto offset=bad.find("\"player_luck\": 5");check(offset!=bad.npos,"invalid Luck fixture field");
    bad.replace(offset,std::string("\"player_luck\": 5").size(),"\"player_luck\": 21");const auto invalid=directory/"invalid-red-hearts.json";{std::ofstream out(invalid);out<<bad;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.arena.canyon.get()==terrain,"invalid reward config has no partial effect");
    game.balanceFile=file.string();game.perform(Action::LoadBalance);capture("artifacts/d09a-timing-panel.png");game.rememberBalancePreset();
    std::filesystem::copy_file(file,"artifacts/d09a-timing-preset.json",std::filesystem::copy_options::overwrite_existing);
    game.applyMapChanges();check(run.redHeartAppearanceSpeed==.5f&&run.redHeartClearRewards&&run.player.attributes.luck==5&&!run.rooms[2].redHeartAward,"map testing reset retains config and resets reward history");key(KEY_ESCAPE);
    run.jumpDebug(run.finalRoom());run.clearRoomDebug();check(!run.rooms[size_t(run.finalRoom())].redHeartAward,"boss uses separate existing reward policy");run.floorExitRequested=true;
    check(run.advanceFloor()&&run.redHeartAppearanceSpeed==.5f&&run.redHeartClearRewards&&run.player.attributes.luck==5,"floor descent retains config");
    run.finishDebug(false);game.retryExpedition();check(game.run->redHeartAppearanceSpeed==.5f&&game.run->redHeartClearRewards&&game.run->player.attributes.luck==5&&game.run->player.hp==6,"death retry retains reward settings");game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="69";fresh.launch(true);
    check(fresh.run->redHeartAppearanceSpeed==.5f&&fresh.run->redHeartClearRewards&&fresh.run->player.attributes.luck==5&&fresh.cameraZoomPercent()==165&&fresh.run->player.attributes.tearsPerSecond==1.9272734f,"fresh application retains rewards and accepted base");fresh.close();
    std::cout<<"PASS D09a actual Game natural heart through mouse-fire clear, full-health refusal/healing/revisit, reward UI, pending map, export/load/reject, floor/retry/new-session persistence\n";
}
void sourceCombatRoomInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"source-room.save",file=directory/"source-room-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="69";
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.error.empty(),"D08 ordinary main Game launch");auto &run=*game.run;Renderer renderer;
    auto sourceIndex=[&]{for(int i=0;i<run.arena.roomCount();++i)if(run.arena.rooms[size_t(i)].sourceCombatTemplate==47)return i;return -1;};
    check(sourceIndex()>0&&run.roomEnemies(sourceIndex()).size()==2,"main Game generates exact source roster");
    check(game.cameraZoomPercent()==165&&run.player.walkingSpeed()==4.8f&&run.player.attributes.tearsPerSecond==1.9272734f&&run.routeLengthScale==.26f,"accepted view/walking/shooting/map retained");
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"D08 UI without error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    click(374,642);check(game.balanceOpen,"open tuning through actual HUD");
    const auto terrain=run.arena.canyon.get(),identity=terrain;const auto expeditionId=run.summary().id;
    click(390,480);check(!game.balanceDraft.sourceCombatRoom&&run.sourceCombatRoom&&game.hasPendingMapChanges()&&run.arena.canyon.get()==identity,"click stages toggle without regeneration");
    for(int n=0;n<30&&game.keyboardFocus()!=Action::ToggleSourceCombatRoom;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::ToggleSourceCombatRoom,"source toggle accessible by keyboard");key(KEY_ENTER);
    check(game.balanceDraft.sourceCombatRoom&&!game.hasPendingMapChanges(),"keyboard restores active setting");click(390,480);
    click(330,605);const auto exported=BalancePreset::load(file,run.content->fingerprint());
    check(!exported.sourceCombatRoom&&exported.defaultZoomPercent==165&&exported.roomSizeScale==1.1f,"export retains pending switch plus accepted settings");
    game.setSourceCombatRoom(true);click(590,605);check(!game.balanceDraft.sourceCombatRoom&&run.sourceCombatRoom&&game.hasPendingMapChanges(),"load stages source-room setting");
    const auto revision=game.balancePreset.revision(),draft=game.balanceDraft.revision();auto bad=exported.json();const auto offset=bad.find("\"source_combat_room\": false");
    check(offset!=bad.npos,"invalid toggle fixture field");bad.replace(offset,std::string("\"source_combat_room\": false").size(),"\"source_combat_room\": 1");
    const auto invalid=directory/"invalid-source.json";{std::ofstream out(invalid);out<<bad;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);
    check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.arena.canyon.get()==terrain,"invalid toggle rejects without partial publication");
    game.balanceFile=file.string();game.perform(Action::LoadBalance);run.player.hp=4;
    click(370,408);check(!run.sourceCombatRoom&&sourceIndex()<0&&!game.hasPendingMapChanges()&&run.summary().id==expeditionId&&run.player.hp==4,"Apply switches generation without resetting player/identity");
    game.rememberBalancePreset();run.finishDebug(false);game.retryExpedition();
    check(!game.run->sourceCombatRoom&&game.cameraZoomPercent()==165,"retry keeps disabled switch and view");
    game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.seedText="69";fresh.launch(true);
    check(fresh.run&&!fresh.run->sourceCombatRoom,"fresh application loads remembered source-room setting");
    fresh.setSourceCombatRoom(true);fresh.applyMapChanges();check(fresh.run->sourceCombatRoom,"reenable in running expedition");
    fresh.balanceFile=file.string();fresh.exportBalancePreset();fresh.rememberBalancePreset();
    Renderer preview;fresh.perform(Action::OpenBalance);
    std::filesystem::create_directories("artifacts");BeginDrawing();preview.draw(fresh);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
    check(ExportImage(image,"artifacts/d08-source-room-panel.png"),"capture source-room tuning");UnloadImage(image);EndDrawing();
    std::filesystem::copy_file(file,"artifacts/d08-source-room-preset.json",std::filesystem::copy_options::overwrite_existing);
    fresh.close();preview.unload();
    std::cout<<"PASS D08 actual Game/Renderer mouse/keyboard, pending Apply, export/load, invalid rejection, retry, remembered fresh session\n";
}
void combatBalanceInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"combat.save",file=directory/"combat-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="69";
    game.loadBalancePreset(source);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    auto &run=*game.run;run.godMode=true;Renderer renderer;
    check(run.player.attributes.damage==3.5f&&std::abs(run.player.shotDamage-11.2f)<.0001f&&run.player.hp==6,"D07 ordinary Game baseline damage and hearts");
    check(run.player.walkingSpeed()==4.8f&&run.player.attributes.tearsPerSecond==1.9272734f&&game.cameraZoomPercent()==165&&run.routeLengthScale==.26f,"D07 retains accepted movement/shooting/map/view");
    run.jumpDebug(2);EntityId actor=0;for(auto &e:run.enemies){e.state=EnemyState::Stunned;e.stateTime=100;if(e.monster==monsterId(10,1)&&e.champion<0)actor=e.id;}
    check(actor,"natural room contains Gaper");auto *e=run.findEnemy(actor);const auto bodyPosition=e->position;
    bool found=false;
    for(int n=0;n<8;++n){const auto point=add(bodyPosition,rotateY({3,0,0},float(n)*Pi/4));if(run.arena.roomAt(point)==2&&!run.arena.blocked(point,.48f)&&run.arena.sight(point,bodyPosition)){
        bool clear=true;for(const auto &other:run.enemies)if(other.id!=actor&&distance(other.position,point)<2)clear=false;
        if(clear){run.player.position=point;found=true;break;}
    }}
    check(found,"legal firing point in generated Gaper encounter");game.updateCamera(10);
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"D07 UI no error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    // Mouse firing, actual Game and real canyon geometry. Only AI is held for
    // deterministic hit counting; no HP override and no injected target.
    const auto pixel=GetWorldToScreen(add(e->position,{0,.25f,0}),game.camera);mouseEvent(MousePosition,int(pixel.x),int(pixel.y));frame();
    mouseEvent(MouseDown,MOUSE_BUTTON_RIGHT);float previous=e->hp;int hits=0;
    for(int n=0;n<600&&e&&e->alive&&e->monster==monsterId(10,1);++n){frame();e=run.findEnemy(actor);if(!e||!e->alive||e->monster!=monsterId(10,1)||e->hp<previous-.001f)++hits;if(e)previous=e->hp;}
    mouseEvent(MouseUp,MOUSE_BUTTON_RIGHT);frame();check(hits==3,"actual Game mouse primary fire takes three hits for natural Gaper body");
    std::cout<<"D07 natural Gaper seed=69 room=2 body_hits="<<hits<<'\n';
    // Use another naturally generated body for proportional living HP changes.
    EntityId injured=0;for(auto &body:run.enemies)if(body.alive&&body.monster==monsterId(10,1)){injured=body.id;break;}
    check(injured,"another natural Gaper remains");Event hit;hit.type=EventType::Damage;hit.target=injured;hit.damage=8;run.queueRoot(hit);run.drainEvents();
    e=run.findEnemy(injured);const float oldHP=e->hp,oldMax=e->maxHp;
    click(374,642);click(840,143);check(game.balanceOpen&&game.balanceCombatOpen,"Combat tab accessible through actual HUD");
    game.setRoomSize(1.2f);const auto terrain=run.arena.canyon.get();const auto content=run.content.get();const auto ticks=run.stats.duration;const auto rng=run.combatRng.state;
    const auto cadence=primaryCadence(run);const auto spec=primaryPlayerAttack(run,run.player.shotDamage,false);
    const auto wait=run.player.fireCooldown;const auto oldShots=run.projectiles;
    click(850,244);check(std::abs(run.player.attributes.damage-3.6f)<.0001f,"Damage uses .1 steps");click(710,340);check(run.content->regularHealthMultiplier()==.95f,"HP uses five-percent steps");
    for(int n=0;n<24&&game.keyboardFocus()!=Action::CombatDamageDown;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::CombatDamageDown,"Damage keyboard focus");key(KEY_ENTER);check(run.player.attributes.damage==3.5f,"keyboard Damage control");
    game.setCombatBalance(7,.75f);e=run.findEnemy(injured);
    check(std::abs(e->hp-oldHP*.75f)<.001f&&std::abs(e->maxHp-oldMax*.75f)<.001f,"wounded natural Gaper retains HP fraction");
    check(run.stats.duration==ticks&&run.combatRng.state==rng&&run.arena.canyon.get()==terrain&&game.hasPendingMapChanges()&&run.content.get()!=content,"combat edits preserve RNG/geometry/time and map draft");
    check(run.player.fireCooldown==wait&&run.projectiles.size()==oldShots.size(),"combat edits preserve wait and flying shot count");
    for(size_t n=0;n<oldShots.size();++n)check(run.projectiles[n].damage==oldShots[n].damage&&run.projectiles[n].life==oldShots[n].life,"existing shot birth damage/lifetime retained");
    const auto updated=primaryPlayerAttack(run,run.player.shotDamage,false);check(std::abs(updated.damage-spec.damage*2)<.001f&&updated.speed==spec.speed&&updated.maxDistance==spec.maxDistance&&primaryCadence(run)==cadence,"Damage independent of shooting and current upgrades");
    click(320,605);click(900,605);const auto exported=BalancePreset::load(file,defaultMechanics()->fingerprint());check(exported.playerDamage==7&&exported.regularHealthMultiplier==.75f&&exported.defaultZoomPercent==165&&exported.roomSizeScale==1.2f,"all new values export with pending map");
    click(400,483);check(run.player.attributes.damage==3.5f&&run.content->regularHealthMultiplier()==1&&std::abs(run.findEnemy(injured)->hp-oldHP)<.001f,"reset baseline preserves wounds");click(590,605);check(run.player.attributes.damage==7&&run.content->regularHealthMultiplier()==.75f&&game.hasPendingMapChanges(),"load applies damage/HP without applying map");
    const auto revision=game.balancePreset.revision(),draft=game.balanceDraft.revision();const auto currentHP=run.findEnemy(injured)->hp;
    auto bad=exported.json();const std::string field="\"regular_health_multiplier\": 0.75";const auto offset=bad.find(field);check(offset!=bad.npos,"bad HP fixture field");bad.replace(offset,field.size(),"\"regular_health_multiplier\": 0");const auto invalid=directory/"invalid-combat.json";{std::ofstream out(invalid);out<<bad;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.findEnemy(injured)->hp==currentHP,"invalid preset rejects without partial Damage/HP/map effects");game.balanceFile=file.string();game.perform(Action::LoadBalance);
    std::filesystem::create_directories("artifacts");std::filesystem::copy_file(file,"artifacts/d07-combat-preset.json",std::filesystem::copy_options::overwrite_existing);
    BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();check(ExportImage(image,"artifacts/d07-combat-panel.png"),"capture Combat panel");UnloadImage(image);EndDrawing();
    game.applyMapChanges();check(run.player.attributes.damage==7&&run.content->regularHealthMultiplier()==.75f,"map regeneration retains damage/HP snapshot");key(KEY_ESCAPE);
    run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;check(run.advanceFloor()&&run.player.attributes.damage==7&&run.content->regularHealthMultiplier()==.75f,"floor descent retains damage/HP");
    run.finishDebug(false);game.retryExpedition();check(game.run->player.attributes.damage==7&&game.run->content->regularHealthMultiplier()==.75f&&game.run->player.hp==6,"retry retains tuning and starting hearts");
    game.close();renderer.unload();Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.launch(true);
    check(fresh.run->player.attributes.damage==7&&fresh.run->content->regularHealthMultiplier()==.75f&&fresh.cameraZoomPercent()==165&&fresh.run->player.attributes.tearsPerSecond==1.9272734f,"fresh session retains complete preset");fresh.close();
    std::cout<<"PASS D07 main Game natural hit count, mouse/keyboard controls, proportional living HP, birth/wait retention, reset/export/load/invalid isolation and map/floor/retry/fresh-session persistence\n";
}
void pooterBalanceInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/
        "docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json";
    const auto save=directory/"pooter.save",file=directory/"pooter-export.json";
    Game game(save);game.themeChoice=ThemeChoice::Canyon;game.seedText="69";
    // Retain the D06 generated Pooter witness; D08 deliberately replaces this room.
    game.loadBalancePreset(source);game.setSourceCombatRoom(false);game.rememberBalancePreset();game.balanceFile=file.string();game.launch(true);
    check(game.run&&game.run->pooterTuning&&game.run->pooterTuning->movement==1,"main Game enables selected Pooter from old preset");
    auto &run=*game.run;run.godMode=true;Renderer renderer;const int room=2;
    check(run.player.walkingSpeed()==4.8f&&run.player.attributes.tearsPerSecond==1.9272734f&&game.cameraZoomPercent()==165&&run.routeLengthScale==.26f,
          "D06 retains accepted player/shooting/map/view settings");
    EntityId actor=0;for(const auto &body:run.roomEnemies(room))if(body.monster==monsterId(14)&&body.champion<0)actor=body.id;
    check(actor!=0,"natural adjacent encounter contains ordinary Pooter");run.jumpDebug(room);auto *e=run.findEnemy(actor);const auto initial=e->position;bool found=false;
    for(int n=0;n<16;++n){const auto point=add(initial,rotateY({2,0,0},float(n)*Pi/8));if(!run.arena.blocked(point,.48f)&&run.arena.sight(initial,point)&&run.arena.roomAt(point)==room){run.player.position=point;found=true;break;}}
    check(found,"legal nearby player approach in actual canyon");
    for(int n=0;n<180&&(!e->buzz||e->buzz->attackFrame<0);++n){game.update(Tick);e=run.findEnemy(actor);}
    check(e->buzz&&e->buzz->attackFrame>=0,"natural Pooter acquires player through actual Game updates");game.updateCamera(10);
    const auto frame=[&]{game.update(Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);check(game.error.empty(),"D06 UI has no error");};
    const auto click=[&](int x,int y){mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();};
    const auto key=[&](int code){mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    click(374,642);click(995,143);click(995,189);check(game.balanceEnemiesOpen&&game.balancePooterOpen,"Pooter page accessible through actual HUD");
    game.setRoomSize(1.2f);const auto terrain=run.arena.canyon.get();const auto position=e->position,velocity=e->velocity;
    const auto attackSpeed=e->buzz->attackShotSpeed;const auto delay=e->cooldown;const auto attackFrame=e->buzz->attackFrame;const auto hp=e->hp;
    click(710,244);click(710,308);click(850,372);
    check(run.pooterTuning->movement==.95f&&run.pooterTuning->shotSpeed==.95f&&run.pooterTuning->attackInterval==1.05f,"independent 5 percent UI controls");
    for(int n=0;n<24&&game.keyboardFocus()!=Action::PooterMovementUp;++n)key(KEY_TAB);
    check(game.keyboardFocus()==Action::PooterMovementUp,"Pooter keyboard focus");key(KEY_ENTER);check(run.pooterTuning->movement==1,"Pooter keyboard action consumed");
    game.setPooterTuning(.5f,.65f,1.5f);
    check(e->cooldown==delay&&e->buzz->attackFrame==attackFrame&&e->buzz->attackShotSpeed==attackSpeed&&e->hp==hp&&distance(e->position,position)==0&&distance(e->velocity,velocity)==0&&run.arena.canyon.get()==terrain&&game.hasPendingMapChanges(),
          "live Pooter edits preserve committed attack, wait, momentum, HP and staged terrain");
    const auto prior=run.stats.projectiles;key(KEY_ESCAPE);bool sawOriginal=false,sawCustom=false;float travelled=0;Vector3 previous=e->position;
    for(int n=0;n<600;++n) {
        game.update(Tick);e=run.findEnemy(actor);check(e&&e->alive,"natural Pooter retained");travelled+=planarDistance(previous,e->position);previous=e->position;
        check(!run.arena.flightBlocked(e->position,e->radius,room),"natural Pooter uses retained full body against canyon boundaries");
        for(const auto &shot:run.projectiles)if(shot.context.sourceEntity==actor){check(shot.pooterFlight.has_value(),"natural shots use source mode0 lifetime");
            sawOriginal|=std::abs(length(shot.velocity)-attackSpeed)<.0001f;sawCustom|=std::abs(length(shot.velocity)-7*Simulation::GaperMovementScale*30*.65f)<.0001f;}
    }
    check(run.stats.projectiles>=prior+3&&sawOriginal&&sawCustom&&travelled>.1f,"generated main-game Pooter wanders, fires retained attack, then fires tuned attacks");
    std::cout<<"D06 natural seed=69 room=2 shots="<<run.stats.projectiles-prior<<" travelled="<<travelled<<'\n';
    click(374,642);click(400,483);check(run.pooterTuning->movement==1&&run.pooterTuning->shotSpeed==1&&run.pooterTuning->attackInterval==1,"reset all Pooter controls");
    game.setPooterTuning(.5f,.65f,1.5f);click(320,605);click(900,605);
    const auto exported=BalancePreset::load(file,run.content->fingerprint());check(exported.pooterMovementMultiplier==.5f&&exported.pooterShotSpeedMultiplier==.65f&&exported.pooterAttackIntervalMultiplier==1.5f&&exported.roomSizeScale==1.2f&&exported.defaultZoomPercent==165,"all Pooter fields export with pending map/view");
    game.setPooterTuning(1,1,1);click(590,605);check(run.pooterTuning->shotSpeed==.65f&&game.hasPendingMapChanges(),"reload updates Pooter without applying map draft");
    const auto revision=game.balancePreset.revision(),draft=game.balanceDraft.revision();auto bad=exported.json();const auto offset=bad.find("\"pooter_attack_interval_multiplier\": 1.5");check(offset!=bad.npos,"invalid Pooter fixture field");
    bad.replace(offset,std::string("\"pooter_attack_interval_multiplier\": 1.5").size(),"\"pooter_attack_interval_multiplier\": 99");const auto invalid=directory/"invalid-pooter.json";{std::ofstream out(invalid);out<<bad;}
    game.balanceFile=invalid.string();game.perform(Action::LoadBalance);check(!game.error.empty()&&game.balancePreset.revision()==revision&&game.balanceDraft.revision()==draft&&run.pooterTuning->attackInterval==1.5f,"invalid Pooter preset has no partial effects");
    game.balanceFile=file.string();game.perform(Action::LoadBalance);std::filesystem::create_directories("artifacts");std::filesystem::copy_file(file,"artifacts/d06-pooter-preset.json",std::filesystem::copy_options::overwrite_existing);
    BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();check(ExportImage(image,"artifacts/d06-pooter-panel.png"),"capture Pooter controls");UnloadImage(image);EndDrawing();
    game.applyMapChanges();check(run.pooterTuning->shotSpeed==.65f&&run.pooterTuning->attackInterval==1.5f,"map regeneration retains Pooter tuning");key(KEY_ESCAPE);
    run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;check(run.advanceFloor()&&run.pooterTuning->movement==.5f,"floor descent retains Pooter tuning");
    run.finishDebug(false);game.retryExpedition();check(game.run->pooterTuning->shotSpeed==.65f&&game.run->player.hp==6,"retry retains Pooter tuning and normal starting health");game.close();renderer.unload();
    Game fresh(save);fresh.themeChoice=ThemeChoice::Canyon;fresh.launch(true);check(fresh.run->pooterTuning->movement==.5f&&fresh.run->pooterTuning->shotSpeed==.65f&&fresh.run->pooterTuning->attackInterval==1.5f&&fresh.cameraZoomPercent()==165&&fresh.run->player.attributes.tearsPerSecond==1.9272734f,"fresh session loads all selected settings");fresh.close();
    std::cout<<"PASS D06 main Game natural encounter, UI controls, safe attack edits, export/load/rejection and map/floor/retry/fresh-session persistence\n";
}
void startingHeartsInputCheck(const std::filesystem::path &directory) {
    dw::Game game(directory/"starting-hearts.save");game.debug=true;game.seedText="42";
    game.themeChoice=dw::ThemeChoice::Canyon;game.launch(true);
    check(game.run&&game.error.empty(),"H01 actual game launch succeeds");auto &run=*game.run;
    check(run.player.hp==6&&run.player.maxHp==6&&run.player.baseHealth==6&&run.player.shotDamage==dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource,
          "H01 actual launch uses six half-heart units without changing shot damage");
    game.updateCamera(10);dw::Renderer renderer;
    std::filesystem::create_directories("artifacts");
    const auto capture=[&](const char *path) {
        BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
        check(ExportImage(image,path),"capture actual H01 heart HUD");UnloadImage(image);EndDrawing();
    };
    capture("artifacts/h01-starting-hearts.png");
    game.perform(dw::Action::HealthUp);check(run.player.baseHealth==8,"health debug step is one red heart");
    game.perform(dw::Action::ResetPlayer);
    check(run.player.hp==6&&run.player.maxHp==6&&game.playerHealth==6,"restore defaults returns to three full red hearts");
    auto originalArena=run.arena;const auto originalPosition=run.player.position;
    run.arena=dw::Arena{};run.arena.bounds={{-100,-1,-100},{100,8,100}};
    for(auto &room:run.arena.rooms) {room.bounds=run.arena.bounds;room.center={0,0,0};}
    run.enemies.clear();run.hazards.clear();run.debugScenario=true;run.godMode=false;run.player.position={0,.85f,0};
    dw::Hazard hazard;hazard.kind=dw::HazardKind::Creep;hazard.position=run.player.position;
    hazard.delay=0;hazard.radius=10;hazard.duration=2;hazard.damage=10;run.hazards.push_back(hazard);
    const auto before=run.player.position;
    mouseEvent(KeyDown,KEY_W);mouseEvent(KeyDown,KEY_SPACE);game.update(dw::Tick);
    check(run.player.dodge>0&&run.player.hp==6&&dw::distance(before,run.player.position)>6*dw::Tick,
          "H01 actual keyboard dodge retains boost and immunity to existing hostile damage");
    mouseEvent(KeyUp,KEY_W);mouseEvent(KeyUp,KEY_SPACE);
    for(int i=0;i<30&&run.player.hp==6;++i)game.update(dw::Tick);
    check(run.player.hp==5&&!run.dead,"H01 one damage unit leaves two full red hearts and one half heart");
    run.arena=std::move(originalArena);run.player.position=originalPosition;run.hazards.clear();game.updateCamera(10);
    capture("artifacts/h01-half-heart.png");
    std::cout<<"PASS H01 launch/reset:three full red hearts;six half-heart units;half-heart loss;D07 damage and universal keyboard dodge preserved\n";
}
void hudInputCheck(const std::filesystem::path &directory) {
    dw::Game game(directory/"hud.save");
    game.debug=false;game.seedText="1866";game.themeChoice=dw::ThemeChoice::Canyon;game.launch();
    auto &run=*game.run;run.godMode=true;run.stats.duration=10;run.messageTime=0;
    game.updateCamera(10);
    dw::Renderer renderer;
    auto frame=[&] {
        game.update(dw::Tick);BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);
        check(game.error.empty(),"compact HUD causes no game errors");
    };
    auto key=[&](int code) {mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    auto click=[&](int x,int y) {
        mouseEvent(MousePosition,x,y);frame();mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();
        mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
    };
    auto capture=[&](const char *path) {
        BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");check(ExportImage(image,path),"save compact HUD capture");
        UnloadImage(image);EndDrawing();
    };
    // Former buttons must leave no invisible mouse blockers after they shrink.
    for(const auto p:{Vector2{160,608},Vector2{850,711},Vector2{420,700},Vector2{480,736},Vector2{248,640}}) {
        mouseEvent(MousePosition,int(p.x),int(p.y));frame();
        check(!game.pointerOverControls(),"freed HUD space accepts world input");
        run.player.fireCooldown=0;const auto shots=run.stats.shots;
        mouseEvent(MouseDown,MOUSE_BUTTON_RIGHT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_RIGHT);frame();
        check(run.stats.shots>shots,"right-click fires through freed HUD space");
    }
    const auto shots=run.stats.shots;
    run.dynamiteCooldown=0;
    const auto placementAmmo=run.dynamite;
    click(160,640);frame();
    check(run.dynamite==placementAmmo-1&&run.hazards.back().settled,"compact dynamite button places immediately");
    check(game.expeditionNotice().find("landing point")==std::string::npos,"placement never enters throw aiming");
    click(754,736);check(game.paused,"compact Pause button works");
    capture("artifacts/expedition-mission-details.png");key(KEY_ESCAPE);
    check(!game.paused&&run.stats.shots==shots,"HUD clicks never fire into the world");
    for(int i=0;i<dw::ItemCount;++i)run.grant(dw::ItemId(i));
    run.messageTime=0;check(game.ownedItemTypes()==dw::ItemCount,"all unique items fit in the strip");
    mouseEvent(MousePosition,640,500);frame();capture("artifacts/expedition-hud-compact.png");
    const auto beforeBuildShots=run.stats.shots;
    click(834,754);check(game.buildOpen,"clicking an owned item opens build details");
    capture("artifacts/expedition-build-details.png");
    const auto duration=run.stats.duration;const auto position=run.player.position;const auto ammo=run.dynamite;
    mouseEvent(KeyDown,KEY_W);mouseEvent(KeyDown,KEY_B);mouseEvent(KeyDown,KEY_UP);frame();
    check(run.stats.duration==duration&&dw::distance(position,run.player.position)==0&&
          run.dynamite==ammo&&run.stats.shots==beforeBuildShots,"build details freeze movement, bombs and combat");
    mouseEvent(KeyUp,KEY_W);mouseEvent(KeyUp,KEY_B);key(KEY_TAB);
    check(!game.buildOpen&&run.stats.shots==beforeBuildShots,"closing build with a held arrow cannot fire");
    mouseEvent(KeyUp,KEY_UP);frame();key(KEY_TAB);check(game.buildOpen,"Tab opens build during play");
    key(KEY_ESCAPE);check(!game.buildOpen&&!game.paused,"Escape closes build directly to play");
    // A warning must win over an ordinary prop earlier in the list and a fresh pickup notice.
    run.arena.breakables.clear();
    dw::Breakable rock;rock.room=run.room;
    rock.bounds={dw::add(run.player.position,{2,-.85f,-.3f}),dw::add(run.player.position,{2.6f,0,.3f})};
    run.arena.breakables.push_back(rock);
    auto barrel=rock;barrel.kind=dw::BreakableKind::PowderBarrel;barrel.fuse=1;
    run.arena.breakables.push_back(barrel);run.announce("Power found");
    check(game.expeditionNotice()=="LIT POWDER / KEEP CLEAR","lit powder overrides ordinary hints and notices");
    run.arena.breakables.clear();run.debugNotice("TEST ENEMY / 10.0");
    check(game.expeditionNotice().empty(),"debug notices stay hidden with the cheat panel closed");
    game.debug=game.debugPanelOpen=true;
    check(game.expeditionNotice()==run.message,"open cheat panel shows debug feedback");
    game.close();renderer.unload();
    std::cout<<"PASS compact HUD hitboxes, mouse controls, build inspection, modal guards and warning priority\n";
}
void keyboardInputCheck(const std::filesystem::path &directory) {
    dw::Game game(directory/"keyboard.save");
    game.debug=false;game.seedText="1866";game.themeChoice=dw::ThemeChoice::Canyon;
    auto frame=[&](float dt=dw::Tick) {
        game.update(dt);BeginDrawing();EndDrawing();
        check(game.error.empty(),"keyboard controls cause no game errors");
    };
    auto key=[&](int code) {mouseEvent(KeyDown,code);frame();mouseEvent(KeyUp,code);frame();};
    auto focus=[&](dw::Action action) {
        for(int i=0;i<45&&game.keyboardFocus()!=action;++i)key(KEY_TAB);
        check(game.keyboardFocus()==action,"the requested menu action is reachable with Tab");
    };
    mouseEvent(MousePosition,1100,200);frame();
    key(KEY_ESCAPE);check(game.paused,"Escape pauses the hub without a mouse");
    key(KEY_H);check(game.controlsOpen,"pause H opens the complete control guide");
    key(KEY_ESCAPE);check(!game.controlsOpen&&game.paused,"help closes back to pause");
    focus(dw::Action::MusicDown);const float music=game.audioSettings.music;key(KEY_ENTER);
    check(game.audioSettings.music<music&&game.paused,"keyboard focus changes a pause setting");
    key(KEY_ESCAPE);check(!game.paused,"Escape returns to hub exploration");
    key(KEY_E);
    for(int i=0;i<2400&&!game.missionMenu;++i)frame(.1f);
    check(game.missionMenu,"E approaches the mission board and opens expedition setup");
    focus(dw::Action::ThemeMine);key(KEY_ENTER);
    check(game.themeChoice==dw::ThemeChoice::Mine&&game.missionMenu,"Enter activates the selected theme without launching");
    focus(dw::Action::ThemeCanyon);key(KEY_ENTER);
    focus(dw::Action::Launch);key(KEY_ENTER);
    check(game.run&&game.screen==dw::Screen::Expedition,"keyboard setup launches a canyon expedition");
    auto &run=*game.run;run.tunePlayer(24,dw::RevolverDamage); // Explicit legal bomb-test capacity.
    game.updateCamera(10);
    check(game.pointerOverControls(),"cursor stays parked over the minimap");
    const int ammo=run.dynamite;game.accumulator=0;
    mouseEvent(KeyDown,KEY_B);frame(.001f);mouseEvent(KeyUp,KEY_B);frame(.001f);
    check(run.dynamite==ammo,"short keyboard bomb tap is queued until the fixed tick");
    frame();
    check(run.dynamite==ammo-1&&run.hazards.back().settled,"B places dynamite even with cursor over HUD and cheats off");
    run.clearRoomDebug();run.dynamiteCooldown=0;
    key(KEY_C);
    const auto shots=run.stats.shots;
    mouseEvent(KeyDown,KEY_RIGHT);mouseEvent(KeyDown,KEY_B);frame();
    const auto &charge=run.hazards.back();
    check(run.dynamite==ammo-2&&charge.settled&&run.stats.shots==shots,
          "C cannot enable throwing; B plus arrow places without firing a bullet");
    check(charge.position.x==run.player.position.x&&charge.position.z==run.player.position.z&&
          dw::length(charge.velocity)==0,"arrow aiming cannot launch ordinary dynamite");
    mouseEvent(KeyUp,KEY_RIGHT);mouseEvent(KeyUp,KEY_B);frame();
    run.clearRoomDebug();run.dynamiteCooldown=0;
    const auto oldAngle=dw::unit(dw::sub(game.camera.position,game.camera.target));
    mouseEvent(KeyDown,KEY_Q);for(int i=0;i<15;++i)frame();mouseEvent(KeyUp,KEY_Q);frame();
    check(dw::distance(oldAngle,dw::unit(dw::sub(game.camera.position,game.camera.target)))>.1f,
          "Q rotates the camera independently of the cursor");
    const auto zoom=game.cameraZoomPercent();
    mouseEvent(KeyDown,KEY_PAGE_UP);for(int i=0;i<15;++i)frame();mouseEvent(KeyUp,KEY_PAGE_UP);frame();
    check(game.cameraZoomPercent()>zoom+5,"Page Up zooms while cursor is over HUD");
    const auto pitch=dw::unit(dw::sub(game.camera.position,game.camera.target)).y;
    mouseEvent(KeyDown,KEY_INSERT);for(int i=0;i<10;++i)frame();mouseEvent(KeyUp,KEY_INSERT);frame();
    check(dw::unit(dw::sub(game.camera.position,game.camera.target)).y>pitch,"Insert tilts the camera");
    run.player.facing={1,0,0};run.player.dodgeCooldown=0;key(KEY_SPACE);
    check(run.player.dodgeDirection.x>.99f,"stationary keyboard dodge follows facing, not the parked mouse");
    run.healDebug();run.clearRoomDebug();
    const auto gate=std::find_if(run.arena.passages.begin(),run.arena.passages.end(),[](const auto &p){return p.locked;});
    check(gate!=run.arena.passages.end(),"keyboard fixture has an optional locked door");
    const int passage=int(gate-run.arena.passages.begin());
    const int side=run.arena.rooms[size_t(gate->rooms[0])].kind==dw::RoomKind::Power?1:0;
    run.jumpDebug(gate->rooms[size_t(side)]);run.clearRoomDebug();
    run.player.position=run.arena.doorApproach(passage,side);run.player.position.y=.85f;run.keys=0;
    key(KEY_E);check(gate->locked,"E cannot unlock a door without its key");
    run.keys=1;key(KEY_E);check(!gate->locked&&run.keys==0,"E opens a locked door and spends exactly one key");
    run.jumpDebug(run.arena.shopRoom);run.clearRoomDebug();run.moneyCollected=100;
    run.player.hp=4;run.player.position=run.arena.rooms[size_t(run.room)].objective;run.player.position.y=.85f;
    key(KEY_E);check(run.shopOpen,"E opens a nearby shop");
    focus(dw::Action::BuyShop0);key(KEY_ENTER);
    check(run.shopOffers[0].sold&&run.player.hp==6,"Enter buys the focused medicine offer");
    const auto shopTime=run.stats.duration;
    mouseEvent(KeyDown,KEY_B);mouseEvent(KeyDown,KEY_E);frame();
    mouseEvent(KeyUp,KEY_B);mouseEvent(KeyUp,KEY_E);frame();
    check(run.stats.duration==shopTime&&run.hazards.empty(),"trade menus freeze combat and cannot deploy bombs");
    key(KEY_ESCAPE);check(!run.shopOpen&&!game.paused,"Escape closes a trade without pausing");
    run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.player.position=run.rewardPosition(run.room);
    run.player.position.y=.85f;key(KEY_E);
    check(run.rewardOpen,"E opens the optional boss reward");
    key(KEY_RIGHT);check(game.keyboardFocus()==dw::Action::Reward1,"arrow selects the second boss reward");
    const auto item=run.offers[1];key(KEY_ENTER);
    check(!run.rewardOpen&&run.itemStacks(item)==1,"Enter claims only the focused reward");
    const float hp=run.player.hp;const auto marker=game.floorExitMarker();
    check(marker&&marker->x>=150&&marker->x<=850&&marker->y>=180&&marker->y<=480,"exit marker stays inside unobstructed HUD bounds");
    run.player.position=run.arena.rooms.back().center;run.player.position.y=.85f;game.updateCamera(10);
    const auto clickable=game.floorExitMarker();
    mouseEvent(MousePosition,int(clickable->x),int(clickable->y));mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();
    mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
    check(run.moveDestination()&&dw::distance(*run.moveDestination(),run.arena.exit)<1,
          "clicking the large exit marker routes to the actual exit");
    run.jumpDebug(run.finalRoom());
    run.player.position=run.arena.exit;run.player.position.y=.85f;game.updateCamera(10);
    dw::Renderer renderer;
    auto capture=[&](const char *name) {
        BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(image,(std::string("artifacts/")+name+".png").c_str()),"save keyboard/exit visual capture");
        UnloadImage(image);EndDrawing();
    };
    capture("exit-beacon-keyboard");
    key(KEY_ENTER);
    check(game.run->floor==1&&game.run->itemStacks(item)==1&&game.run->player.hp==hp,
          "Enter at the exit advances one floor and carries the build without healing");
    // A story floor still requires evidence, even though the exit is clearly marked.
    game.run=std::make_unique<dw::Simulation>(1866,game.campaign.data().pending->id,game.campaign.data().world,
        dw::MissionTheme::Canyon,true,false,dw::WitnessAccount::Rourke);
    auto &story=*game.run;story.jumpDebug(story.finalRoom());story.clearRoomDebug();
    story.player.position=story.arena.exit;story.player.position.y=.85f;game.updateCamera(10);
    check(game.floorExitMarker()&&!story.canUseFloorExit(),"locked story exit remains visible");
    capture("exit-beacon-locked");key(KEY_E);check(story.floor==0,"keyboard exit preserves required evidence gate");
    const int site=story.storyRoomIndex();story.jumpDebug(site);story.clearRoomDebug();
    story.player.position=story.arena.rooms[size_t(site)].objective;story.player.position.y=.85f;
    key(KEY_E);check(game.journalVisible()&&story.storySeen(),"E examines required story evidence");
    key(KEY_ENTER);check(!game.journalVisible(),"Enter closes the field journal");
    story.jumpDebug(story.finalRoom());story.player.position=story.arena.exit;story.player.position.y=.85f;
    key(KEY_E);check(game.run->floor==1,"E advances once required evidence has been examined");
    key(KEY_ESCAPE);focus(dw::Action::Controls);key(KEY_ENTER);capture("keyboard-controls");key(KEY_ESCAPE);
    focus(dw::Action::Retreat);key(KEY_ENTER);check(game.screen==dw::Screen::Summary,"keyboard menus resolve a retreat");
    key(KEY_ENTER);check(game.screen==dw::Screen::Hub,"Enter returns from summary to hub");
    renderer.unload();
    std::cout<<"PASS keyboard hub/setup, menus/settings, bombs over HUD, directed throws, camera, doors, trades, rewards and evidence-gated floor exits\n";
}
void arrowInputCheck(const std::filesystem::path &directory, dw::MissionTheme theme) {
    const std::string name = theme == dw::MissionTheme::Canyon ? "canyon" : "mine";
    dw::Game game(directory / ("arrows-" + name + ".save"));
    game.seedText = "1866";
    game.themeChoice = theme == dw::MissionTheme::Canyon ? dw::ThemeChoice::Canyon : dw::ThemeChoice::Mine;
    game.launch();
    auto &run = *game.run;
    run.godMode = true;
    game.updateCamera(10);
    auto frame = [&](float dt = dw::Tick) {
        game.update(dt);
        BeginDrawing();
        EndDrawing(); // Poll raylib input, including pressed/released edges.
        check(game.error.empty(), "arrow input causes no game errors");
    };
    auto release = [&] {
        for (int key : {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_D, KEY_LEFT_SHIFT})
            mouseEvent(KeyUp, key);
        mouseEvent(MouseUp, MOUSE_BUTTON_RIGHT);
        frame();
    };
    auto forward = [&] {
        const auto offset = dw::sub(game.camera.target, game.camera.position);
        return dw::unit(Vector3{offset.x, 0, offset.z});
    };
    auto heading = [&] { return dw::unit(dw::sub(run.player.aim, run.player.position)); };
    auto shotHeading = [&] {
        check(!run.projectiles.empty(), "arrow firing creates a projectile");
        return dw::unit(run.projectiles.back().velocity);
    };
    mouseEvent(MousePosition, 1100, 200);
    release();
    check(game.pointerOverControls(), "arrow fixture keeps the cursor over the map HUD");
    auto directions = [&] {
        const auto f = forward();
        const Vector3 r{-f.z, 0, f.x};
        for (const auto &[key, direction] : std::array<std::pair<int, Vector3>, 4>{
                 {{KEY_UP, f}, {KEY_DOWN, dw::mul(f, -1)}, {KEY_RIGHT, r}, {KEY_LEFT, dw::mul(r, -1)}}}) {
            const auto shots = run.stats.shots;
            run.player.fireCooldown = 0;
            mouseEvent(KeyDown, key);
            frame();
            check(run.stats.shots == shots + 1 && dw::distance(shotHeading(), direction) < .001f,
                  "all four arrow keys fire relative to the camera even over the HUD");
            release();
        }
    };
    directions();
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_RIGHT);
    run.player.fireCooldown = 0;
    frame();
    const auto f = forward();
    check(dw::distance(shotHeading(), dw::unit(dw::add(f, {-f.z, 0, f.x}))) < .001f,
          "adjacent arrows produce a diagonal projectile");
    release();
    const auto beforeOpposite = run.stats.shots;
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_DOWN);
    mouseEvent(KeyDown, KEY_LEFT);
    mouseEvent(KeyDown, KEY_RIGHT);
    frame(.1f);
    check(run.stats.shots == beforeOpposite, "opposite arrows cancel instead of firing a zero direction");
    release();
    run.player.fireCooldown = 0;
    const auto beforeHeld = run.stats.shots;
    mouseEvent(KeyDown, KEY_UP);
    for (int i = 0; i < 60; ++i)
        frame();
    check(run.stats.shots >= beforeHeld + 3, "holding an arrow repeats at the revolver fire rate");
    release();
    const auto afterRelease = run.stats.shots;
    frame(.1f);
    check(run.stats.shots == afterRelease, "releasing arrows stops keyboard fire");
    game.accumulator = 0;
    run.player.fireCooldown = 0;
    mouseEvent(KeyDown, KEY_LEFT);
    frame(dw::Tick / 4);
    mouseEvent(KeyUp, KEY_LEFT);
    frame(dw::Tick / 4);
    check(run.stats.shots == afterRelease, "a short arrow tap waits for the simulation tick");
    frame();
    check(run.stats.shots == afterRelease + 1 &&
              dw::distance(shotHeading(), {f.z, 0, -f.x}) < .001f,
          "a short arrow tap preserves both the shot and its direction");
    const auto start = run.player.position;
    dw::Input navigation;
    navigation.moveTarget = dw::add(start, dw::mul(f, 2));
    run.step(navigation);
    check(run.moveDestination().has_value(), "arrow fixture begins with an active walking route");
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_D);
    run.player.fireCooldown = 0;
    frame(.1f); // Multiple simulation ticks must retain a directional aim while strafing.
    check(dw::distance(start, run.player.position) > .1f && !run.moveDestination() &&
              dw::distance(heading(), f) < .001f && dw::distance(shotHeading(), f) < .001f,
          "WASD strafes while arrow shots retain their heading and cancel click navigation");
    const auto standing = run.player.position;
    mouseEvent(KeyDown, KEY_LEFT_SHIFT);
    frame(.1f);
    check(dw::distance(standing, run.player.position) < .001f, "Shift holds position during arrow fire");
    release();
    mouseEvent(MousePosition, 600, 350);
    mouseEvent(MouseDown, MOUSE_BUTTON_MIDDLE);
    frame();
    mouseEvent(MousePosition, 790, 370);
    frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_MIDDLE);
    frame();
    check(dw::distance(f, forward()) > .1f, "arrow fixture rotates the camera with a middle drag");
    mouseEvent(MousePosition, 1100, 200);
    directions();
    mouseEvent(MousePosition, 680, 315);
    mouseEvent(MouseDown, MOUSE_BUTTON_RIGHT);
    mouseEvent(KeyDown, KEY_DOWN);
    frame();
    check(dw::distance(heading(), dw::mul(forward(), -1)) < .001f,
          "held arrows take aim priority over simultaneous mouse fire");
    mouseEvent(KeyUp, KEY_DOWN);
    run.player.fireCooldown = 0;
    const auto beforeMouse = run.stats.shots;
    frame();
    check(run.stats.shots == beforeMouse + 1 &&
              dw::distance(heading(), dw::mul(forward(), -1)) > .1f,
          "releasing arrows immediately restores existing mouse aiming and firing");
    release();
    // Neither held arrows nor sub-tick taps may leak through modal screens.
    auto modalGuard = [&](bool &open) {
        const auto shots = run.stats.shots;
        game.accumulator = 0;
        run.player.fireCooldown = 0;
        mouseEvent(KeyDown, KEY_UP);
        frame(dw::Tick / 4);
        open = true;
        frame();
        release();
        open = false;
        frame();
        check(run.stats.shots == shots, "modals block arrows and discard pending arrow taps");
    };
    modalGuard(game.paused);
    modalGuard(run.shopOpen);
    modalGuard(run.rewardOpen);
    modalGuard(run.letterOpen);
    modalGuard(game.journalOpen);
    modalGuard(game.buildOpen);
    const auto beforeDynamite = run.stats.shots;
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_B);
    frame();
    mouseEvent(KeyUp, KEY_B);
    release();
    check(run.stats.shots == beforeDynamite && run.dynamite == 2,
          "placing dynamite while holding an arrow does not also fire the revolver");
    std::cout << "PASS " << name
              << " arrow fire, diagonals, rotated camera, strafing, short taps, mouse fallback and modal guards\n";
}
void shopInputCheck(const std::filesystem::path &directory, dw::MissionTheme theme) {
    const std::string name = theme == dw::MissionTheme::Canyon ? "canyon" : "mine";
    dw::Game game(directory / ("shop-" + name + ".save"));
    game.campaign.begin(1);
    auto funding = *game.campaign.data().pending;
    funding.moneyCollected = 100;
    game.campaign.resolve(funding, dw::EndReason::Victory);
    game.seedText = "1866";
    game.themeChoice = theme == dw::MissionTheme::Canyon ? dw::ThemeChoice::Canyon : dw::ThemeChoice::Mine;
    game.launch();
    auto &run = *game.run;
    run.jumpDebug(run.arena.shopRoom);
    const auto merchant = run.arena.rooms[size_t(run.room)].objective;
    run.player.position =
        dw::add(merchant, dw::mul(dw::unit(dw::sub(run.arena.rooms[size_t(run.room)].center, merchant)), 4));
    run.player.hp = 3;
    game.updateCamera(10);
    dw::Renderer renderer;
    const dw::Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&](int x = 10, int y = 10, bool left = false, bool right = false) {
        mouseEvent(MousePosition, x, y);
        mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
        mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
        game.update(dw::Tick, picker);
        BeginDrawing();
        const auto action = renderer.draw(game);
        EndDrawing();
        game.perform(action);
        check(game.error.empty(), "shop input does not cause a game error");
    };
    auto click = [&](int x, int y) {
        frame(x, y);
        frame(x, y, true);
        frame(x, y);
    };
    auto capture = [&](const std::string &stage) {
        BeginDrawing();
        renderer.draw(game);
        rlDrawRenderBatchActive();
        const auto image = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(image, ("artifacts/shop-" + name + "-" + stage + ".png").c_str()),
              "save the shop capture");
        UnloadImage(image);
        EndDrawing();
    };
    frame();
    capture("merchant");
    const auto pixel = GetWorldToScreen(dw::add(merchant, {0, .8f, 0}), game.camera);
    click(int(pixel.x), int(pixel.y));
    for (int i = 0; i < 240 && !run.shopOpen; ++i)
        frame();
    check(run.shopOpen && run.enemies.empty() && run.stats.shots == 0,
          "clicking the actual shopkeeper approaches and opens trade without shooting");
    const auto position = run.player.position;
    const auto duration = run.stats.duration;
    mouseEvent(KeyDown, KEY_W);
    mouseEvent(KeyDown, KEY_B);
    for (int i = 0; i < 10; ++i)
        frame(600, 700, true, true);
    mouseEvent(KeyUp, KEY_W);
    mouseEvent(KeyUp, KEY_B);
    frame();
    check(game.pointerOverControls() && dw::distance(position, run.player.position) == 0 &&
              run.stats.duration == duration && run.stats.shots == 0 && run.dynamite == 3,
          "the trade window captures gameplay mouse/key input and freezes the world");
    click(330, 535);
    check(run.player.hp == 5 && run.money() == 90 && run.shopOffers[0].sold,
          "the medicine buy button heals and charges its displayed price");
    click(630, 535);
    check(run.money() == 65 && run.items.size() == 1 && game.campaign.data().pending->moneySpent == 35,
          "the power buy button applies its item and checkpoints spending immediately");
    click(630, 535);
    check(run.money() == 65 && run.items.size() == 1, "sold-out buttons do not charge again");
    click(450, 610);
    check(run.money() == 50 && run.dynamite == 6 && run.shopOffers[3].sold &&
              game.campaign.data().pending->moneySpent == 50,
          "the dynamite pack button adds three charges and saves the purchase");
    capture("stock");
    click(925, 610);
    check(!run.shopOpen && run.stats.shots == 0, "leaving the shop never fires through the panel");
    mouseEvent(KeyDown, KEY_E);
    frame();
    mouseEvent(KeyUp, KEY_E);
    frame();
    check(run.shopOpen && run.shopOffers[1].sold, "reopening preserves sold stock");
    mouseEvent(KeyDown, KEY_ESCAPE);
    frame();
    mouseEvent(KeyUp, KEY_ESCAPE);
    frame();
    check(!run.shopOpen && !game.paused, "Escape closes trade without opening Pause");
    game.finish(dw::EndReason::Retreat);
    check(game.campaign.data().world.money == 50, "returning from the shop preserves the wallet debit");
    std::cout << "PASS " << name
              << " shopkeeper approach, purchases, UI guards, closing and saved spending\n";
}
void dynamiteInputCheck(const std::filesystem::path &directory, dw::MissionTheme theme) {
    const std::string name = theme == dw::MissionTheme::Canyon ? "canyon" : "mine";
    dw::Game game(directory / ("dynamite-" + name + ".save"));
    game.seedText = "1866";
    game.themeChoice = theme == dw::MissionTheme::Canyon ? dw::ThemeChoice::Canyon : dw::ThemeChoice::Mine;
    game.launch();
    auto &run = *game.run;
    run.godMode = true;
    game.updateCamera(10);
    dw::Renderer renderer;
    const dw::Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&](int x, int y, bool left = false, bool right = false, float dt = dw::Tick) {
        mouseEvent(MousePosition, x, y);
        mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
        mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
        game.update(dt, picker);
        BeginDrawing();
        const auto action = renderer.draw(game);
        EndDrawing();
        game.perform(action);
        check(game.error.empty(), "dynamite input causes no game errors");
    };
    auto click = [&](int x, int y) {
        frame(x, y);
        frame(x, y, true);
        frame(x, y);
    };
    auto capture = [&](const std::string &stage) {
        BeginDrawing();
        renderer.draw(game);
        rlDrawRenderBatchActive();
        auto image = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(image, ("artifacts/dynamite-" + name + "-" + stage + ".png").c_str()),
              "save dynamite capture");
        UnloadImage(image);
        EndDrawing();
    };
    const auto aim = dw::add(run.player.position, {0, -.85f, -5});
    const auto pixel = GetWorldToScreen(aim, game.camera);
    const int x = int(pixel.x), y = int(pixel.y);
    frame(x, y);
    game.accumulator = 0;
    mouseEvent(KeyDown, KEY_B);
    frame(x, y, false, false, .001f);
    mouseEvent(KeyUp, KEY_B);
    frame(x, y, false, false, .001f);
    check(run.dynamite == 3, "short B press waits for the next fixed simulation step");
    frame(x, y);
    check(run.dynamite == 2 && run.hazards.size() == 1 && run.stats.shots == 0,
          "a short B press places exactly one dynamite without firing the revolver");
    const auto planted = run.hazards.front().position;
    check(run.hazards.front().settled && planted.x == run.player.position.x &&
              planted.z == run.player.position.z,
          "B places at the player's feet rather than at the cursor");
    for (int i = 0; i < 20; ++i)
        frame(x, y);
    capture("lit");
    game.perform(dw::Action::Pause);
    const float age = run.hazards.front().age;
    mouseEvent(KeyDown, KEY_B);
    mouseEvent(KeyDown, KEY_E);
    for (int i = 0; i < 10; ++i)
        frame(x, y);
    mouseEvent(KeyUp, KEY_B);
    mouseEvent(KeyUp, KEY_E);
    frame(x, y); // Let raylib observe the releases before the next E press.
    check(run.hazards.front().age == age && run.hazards.front().settled && run.dynamite == 2,
          "pause freezes fuses and rejects deployment and kicks");
    game.perform(dw::Action::Resume);
    check(run.nearbyInteraction() != "KICK DYNAMITE", "contact kicking needs no HUD control");
    mouseEvent(KeyDown, KEY_E);
    frame(x, y);
    mouseEvent(KeyUp, KEY_E);
    frame(x, y);
    check(run.hazards.front().settled, "E no longer kicks dynamite");
    mouseEvent(KeyDown, KEY_W);
    for (int i = 0; i < 10; ++i)
        frame(x, y);
    mouseEvent(KeyUp, KEY_W);
    frame(x, y);
    check(run.hazards.front().settled && dw::distance(planted, run.hazards.front().position) == 0,
          "WASD walking away leaves the planted charge in place");
    mouseEvent(KeyDown, KEY_S);
    for (int i = 0; i < 5; ++i)
        frame(x, y);
    mouseEvent(KeyUp, KEY_S);
    frame(x, y);
    check(!run.hazards.front().settled && run.hazards.front().age > age && run.dynamite == 2 &&
              run.stats.shots == 0,
          "walking back into a charge kicks it automatically without spending ammo or firing");
    capture("kicked");
    for (int i = 0; i < 130 && run.stats.explosions == 0; ++i)
        frame(x, y);
    check(run.stats.explosions == 1 && run.dynamite == 2, "the charge detonates once after resuming");
    for (int i = 0; i < 12; ++i)
        frame(x, y);
    capture("blast");
    for (int i = 0; i < 40; ++i)
        frame(x, y);
    frame(248,640);
    check(!game.pointerOverControls(),"removed mode button leaves no invisible input blocker");
    game.perform(dw::Action::DynamiteMode);
    mouseEvent(KeyDown,KEY_C);frame(x,y);mouseEvent(KeyUp,KEY_C);frame(x,y);
    const auto before=run.player.position;
    click(160,640);frame(160,640); // Buttons dispatch on release; consume the queued placement next tick.
    check(run.dynamite==1&&run.hazards.back().settled&&run.stats.shots==0&&
          dw::distance(before,run.player.position)<.001f,
          "retired mode action and C cannot turn the HUD placement into a throw");
    mouseEvent(KeyDown,KEY_ESCAPE);frame(x,y);mouseEvent(KeyUp,KEY_ESCAPE);frame(x,y);
    check(game.paused&&run.dynamite==1,"Escape pauses directly after placement");
    click(160,640);
    check(run.dynamite==1,"paused HUD cannot place another charge");
    game.perform(dw::Action::Resume);
    run.hazards.clear();run.dynamiteCooldown=0;
    mouseEvent(KeyDown, KEY_LEFT_SHIFT);
    mouseEvent(KeyDown, KEY_B);
    frame(x, y);
    mouseEvent(KeyUp, KEY_B);
    mouseEvent(KeyUp, KEY_LEFT_SHIFT);
    frame(x, y);
    check(run.dynamite == dw::MaxDynamite, "Shift+B refills dynamite for testing without throwing");
    click(160, 640);
    frame(160, 640);
    const auto &placed = run.hazards.back();
    check(run.dynamite == dw::MaxDynamite - 1 && placed.settled &&
              placed.position.x == run.player.position.x && placed.position.z == run.player.position.z &&
              run.stats.shots == 0,
          "the Place Dynamite button immediately places at the player's feet without a targeting click");
    capture("placed");
    const auto placedAt = placed.position;
    // Exercise ordinary ground clicks during combat, when the starting passage's
    // broad interaction area does not redirect them into a door approach.
    run.roomClear = false;
    run.debugScenario = true;
    Vector3 away{};
    bool found = false;
    for (const auto direction : {Vector3{1, 0, 0}, Vector3{0, 0, 1}, Vector3{-1, 0, 0}, Vector3{0, 0, -1}}) {
        away = dw::add(run.player.position, dw::mul(direction, 1.3f));
        if (!run.arena.blocked(away, .48f) && run.arena.clear(run.player.position, away, .48f)) {
            found = true;
            break;
        }
    }
    check(found, "there is room to step away from the planted charge");
    auto worldClick = [&](Vector3 at) {
        at.y = 0;
        const auto screen = GetWorldToScreen(at, game.camera);
        click(int(screen.x), int(screen.y));
    };
    worldClick(away);
    for (int i = 0; i < 25 && run.moveDestination(); ++i)
        frame(640, 400);
    check(dw::distance(run.player.position, placedAt) > 1,
          "mouse movement separates the feet from the bundle");
    check(dw::distance(placedAt, run.hazards.back().position) == 0 && run.hazards.back().settled,
          "click-to-move away leaves the bundle at the placement point");
    worldClick(placedAt);
    for (int i = 0; i < 25 && run.hazards.back().settled; ++i)
        frame(640, 400);
    check(!run.hazards.back().settled && run.dynamite == dw::MaxDynamite - 1 && run.stats.shots == 0,
          "click-to-move into dynamite nudges it without a special button");
    for (int i = 0; i < 25; ++i)
        frame(640, 400);
    const float nudged = dw::distance(placedAt, run.hazards.back().position);
    check(nudged > .4f && nudged < 1.5f, "the mouse contact kick travels only a short distance");
    game.close();
    std::cout
        << "PASS " << name
        << " dynamite placement only, WASD/mouse contact kicks, retired throw controls, pause and refill\n";
}
void boundaryRiverInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory / "river.save");
    game.seedText = "1866";
    game.launch();
    auto &run = *game.run;
    const auto &field = *run.arena.canyon;
    const int room = field.riverRooms.front();
    const auto &layout = run.arena.rooms[size_t(room)];
    const auto outward = field.riverOutward;
    const float reach = std::abs(dot(sub(layout.bounds.max, layout.bounds.min), outward)) * .5f;
    Vector3 from{};
    bool found = false;
    const auto bank = add(layout.center, mul(outward, reach - 2.5f));
    const auto water = add(bank, mul(outward, field.riverSample(bank).width + 3));
    const Vector3 tangent{-outward.z, 0, outward.x};
    for (float offset : {0.f, -2.f, 2.f, -4.f, 4.f}) {
        const auto candidate = add(add(layout.center, mul(outward, reach - 6)), mul(tangent, offset));
        if (!run.arena.blocked(candidate, .6f) && run.arena.sight(candidate, water)) {
            from = candidate;
            found = true;
            break;
        }
    }
    check(found && field.waterBlocked(water),
          "river mouse fixture has a clear approach to a deep-water boundary");
    run.jumpDebug(room);
    run.clearRoomDebug();
    run.player.position = from;
    run.godMode = true;
    game.updateCamera(1);
    Renderer renderer;
    const Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&]() {
        game.update(Tick, picker);
        BeginDrawing();
        renderer.draw(game);
        EndDrawing();
    };
    mouseEvent(MousePosition, 640, 400);
    mouseEvent(MouseWheel, 0, -5);
    frame();
    for (int n = 0; n < 40; ++n)
        frame();
    auto pixel = GetWorldToScreen({water.x, 0, water.z}, game.camera);
    check(pixel.x > 10 && pixel.x < 1270 && pixel.y > 130 && pixel.y < 670,
          "deep-water target is inside the play viewport");
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_LEFT);
    frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_LEFT);
    frame();
    check(run.moveDestination().has_value(), "clicking water queues an approach to the bank");
    for (int n = 0; n < 900 && run.moveDestination(); ++n) {
        frame();
        check(!field.waterBlocked(run.player.position), "mouse movement never steps into deep water");
    }
    check(distance(run.player.position, from) > 1 && !run.moveDestination() &&
              run.arena.roomAt(run.player.position) == room,
          "mouse movement approaches the boundary and stops on the playable near bank");
    check(run.stats.shots == 0, "a bank movement click never fires");
    const auto stopped = run.player.position;
    pixel = GetWorldToScreen({water.x, 0, water.z}, game.camera);
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_RIGHT);
    for (int n = 0; n < 20; ++n)
        frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_RIGHT);
    frame();
    check(run.stats.shots > 0 && distance(run.player.position, stopped) < .1f,
          "aiming and firing across water does not become a movement command");
    game.close();
    std::cout << "PASS river mouse approach, stopping at the natural boundary and "
                 "aiming/firing across water\n";
}

void interiorRiverInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory / "interior-river.save");
    game.seedText = "42";
    game.launch();
    auto &run = *game.run;
    const auto &field = *run.arena.canyon;
    check(field.riverKind == CanyonRiverKind::Interior, "interior mouse test uses an interior river seed");
    Vector3 from{}, to{}, water{};
    int room = -1;
    for (size_t i = 1; i + 1 < field.river.size(); ++i) {
        const auto &p = field.river[i];
        if (field.height(p.position.x, p.position.z) > -.4f)
            continue;
        const auto direction = unit(sub(field.river[i + 1].position, field.river[i - 1].position));
        const Vector3 side{-direction.z, 0, direction.x};
        auto a = add(p.position, mul(side, p.width + 2.5f)), b = sub(p.position, mul(side, p.width + 2.5f));
        a.y = b.y = .85f;
        const int index = run.arena.roomAt(a);
        if (index < 0 || index != run.arena.roomAt(b) || run.arena.blocked(a, .6f) ||
            run.arena.blocked(b, .6f) || !run.arena.sight(a, b) || run.arena.clear(a, b, .48f) ||
            run.arena.path(a, b, .48f).empty())
            continue;
        from = a;
        to = b;
        water = p.position;
        room = index;
        break;
    }
    check(room >= 0, "river mouse fixture has two connected banks separated by deep water");
    run.jumpDebug(room);
    run.clearRoomDebug();
    run.player.position = from;
    run.godMode = true;
    game.updateCamera(1);
    Renderer renderer;
    const Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&]() {
        game.update(Tick, picker);
        BeginDrawing();
        renderer.draw(game);
        EndDrawing();
    };
    mouseEvent(MousePosition, 640, 400);
    mouseEvent(MouseWheel, 0, -5);
    frame();
    for (int n = 0; n < 40; ++n)
        frame();
    auto pixel = GetWorldToScreen({to.x, 0, to.z}, game.camera);
    check(pixel.x > 10 && pixel.x < 1270 && pixel.y > 130 && pixel.y < 670,
          "opposite bank is inside the play viewport");
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_LEFT);
    frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_LEFT);
    frame();
    check(run.moveDestination().has_value(), "clicking the opposite bank queues a ford route");
    for (int n = 0; n < 900 && run.moveDestination(); ++n) {
        frame();
        check(!field.waterBlocked(run.player.position), "mouse movement never steps into deep water");
    }
    check(distance(run.player.position, to) < .9f, "mouse movement reaches the opposite bank through a ford");
    check(run.stats.shots == 0, "a bank movement click never fires");
    pixel = GetWorldToScreen({water.x, 0, water.z}, game.camera);
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_RIGHT);
    for (int n = 0; n < 20; ++n)
        frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_RIGHT);
    frame();
    check(run.stats.shots > 0 && distance(run.player.position, to) < .9f,
          "aiming and firing across water does not become a movement command");
    game.close();
    std::cout << "PASS river mouse routing through fords and aiming/firing across deep water\n";
}
void vegetationInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory / "vegetation.save");
    game.seedText = "1866";
    game.launch();
    game.paused = true;
    game.debug = false;
    Renderer renderer;
    auto frame = [&](int x = 10, int y = 10, bool down = false) {
        mouseEvent(MousePosition, x, y);
        mouseEvent(down ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
        game.update(Tick);
        BeginDrawing();
        const auto action = renderer.draw(game);
        EndDrawing();
        game.perform(action);
    };
    auto click = [&](int x) {
        frame(x, 719, true);
        frame(x, 719);
        frame();
    };
    frame();
    const auto duration = game.run->stats.duration;
    const auto plants = renderer.missionVegetationCount();
    check(game.visualSettings.groundDetail, "ground surface detail starts enabled");
    frame(1075, 650, true);
    frame(1075, 650);
    frame();
    check(!game.visualSettings.groundDetail, "pause ground detail toggles off without cheats");
    frame(1075, 650, true);
    frame(1075, 650);
    frame();
    check(game.visualSettings.groundDetail, "pause ground detail toggles on again");
    click(178);
    check(game.visualSettings.vegetation == 75 && renderer.missionVegetationCount() < plants,
          "pause LESS reduces vegetation immediately without cheats");
    click(265);
    check(game.visualSettings.vegetation == 100 && renderer.missionVegetationCount() == plants,
          "pause MORE restores the seeded vegetation");
    for (int i = 0; i < 10; ++i)
        click(178);
    check(game.visualSettings.vegetation == 0 && renderer.missionVegetationCount() == 0,
          "pause vegetation stops at zero");
    for (int i = 0; i < 10; ++i)
        click(265);
    check(game.visualSettings.vegetation == 200 && renderer.missionVegetationCount() > plants,
          "pause vegetation stops at 200 percent and adds plants");
    check(game.paused && game.run->stats.duration == duration && game.run->stats.shots == 0,
          "vegetation controls never advance combat or fire the weapon");
    const auto preferences = directory / "visual.cfg";
    game.perform(Action::ToggleCanyonRiver);
    check(game.visualSettings.canyonRiver, "river layout cannot be changed inside an active mission");
    game.visualSettings.groundDetail = false;
    check(saveVisualSettings(preferences, game.visualSettings) &&
              loadVisualSettings(preferences) == game.visualSettings,
          "vegetation preference survives a settings reload");
    {
        std::ofstream legacy(preferences);
        legacy << "DEATHWARD_VISUAL 1\n175\n";
    }
    check(loadVisualSettings(preferences).vegetation == 175 && loadVisualSettings(preferences).groundDetail,
          "old vegetation preferences migrate while enabling the new floor detail");
    {
        std::ofstream legacy(preferences);
        legacy << "DEATHWARD_VISUAL 2\n175\n0\n";
    }
    check(loadVisualSettings(preferences).vegetation == 175 &&
              !loadVisualSettings(preferences).groundDetail && loadVisualSettings(preferences).canyonRiver,
          "version two preserves floor settings and enables the river trial");
    {
        std::ofstream bad(preferences);
        bad << "DEATHWARD_VISUAL 1\n-25\n";
    }
    check(loadVisualSettings(preferences) == VisualSettings{}, "invalid density restores the default");
    game.finish(EndReason::Retreat);
    game.perform(Action::Hub);
    game.paused = true;
    click(178);
    check(game.screen == Screen::Hub && game.visualSettings.vegetation == 175,
          "the same vegetation control is available while paused in town");
    auto capture = LoadImageFromScreen();
    std::filesystem::create_directories("artifacts");
    ExportImage(capture, "artifacts/vegetation-pause-controls.png");
    UnloadImage(capture);
    game.paused = false;
    game.town.player.position = game.town.mission;
    game.perform(Action::Missions);
    frame(870, 497, true);
    frame(870, 497);
    frame();
    check(!game.visualSettings.canyonRiver, "the mission board offers a working river comparison toggle");
    check(saveVisualSettings(preferences, game.visualSettings) &&
              !loadVisualSettings(preferences).canyonRiver,
          "river-off preference survives reload");
    game.launch();
    check(game.run->arena.canyon && game.run->arena.canyon->river.empty(),
          "river-off launches the original canyon geometry");
    game.close();
    std::cout << "PASS vegetation pause controls, bounds, live changes, no gameplay input and persistence\n";
}
void economyInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory/"economy.save");game.seedText="1866";game.themeChoice=ThemeChoice::Canyon;game.launch();
    Renderer renderer;auto &run=*game.run;
    const auto frame=[&] {
        game.update(.1f,[&](const Simulation &simulation,const Camera3D &camera,Ray ray){return renderer.pickScenery(simulation,camera,ray);});
        BeginDrawing();const auto action=renderer.draw(game);EndDrawing();game.perform(action);
        check(game.error.empty(),"economy input causes no game errors");
    };
    const auto click=[&](float x,float y) {
        mouseEvent(MousePosition,int(x),int(y));mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
        mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
    };
    const auto key=[&](int value){mouseEvent(KeyDown,value);frame();mouseEvent(KeyUp,value);frame();};
    int site=-1;for(int i=0;i<run.arena.roomCount();++i)if(run.arena.rooms[size_t(i)].kind==RoomKind::Service){site=i;break;}
    check(site>=0,"native fixture contains a generated service room");
    for(auto service:{RoomService::Exchange,RoomService::Surgeon,RoomService::Smuggler}) {
        run.arena.rooms[size_t(site)].service=service;run.rooms[size_t(site)].serviceSold={false,false};
        run.rooms[size_t(site)].offers={ItemId::Judas,ItemId::Cap};
        run.jumpDebug(site);run.keys=2;run.dynamite=3;run.moneyCollected=100;run.moneySpent=0;run.player.hp=2;
        const auto target=run.arena.rooms[size_t(site)].objective;
        bool placed=false;for(int n=0;n<16;++n) {
            const auto p=add(target,rotateY({0,0,4},float(n)*Pi/8));
            if(run.arena.blocked(p,.48f)||!run.arena.clear(p,target,.48f))continue;
            run.player.position=p;placed=true;break;
        }
        check(placed,"a safe approach to the service person exists");game.updateCamera(10);frame();
        const auto point=GetWorldToScreen(add(target,{0,.6f,0}),game.camera);click(point.x,point.y);
        for(int i=0;i<200&&!run.shopOpen;++i)frame();
        check(run.shopOpen,"clicking service person walks over and opens the rendered offer");
        const auto frozen=run.stats.duration;key(KEY_UP);check(run.stats.duration==frozen,"trade modal pauses simulation and arrows");
        if(service==RoomService::Exchange)key(KEY_ONE);else click(425,572);
        check(run.rooms[size_t(site)].serviceSold[0],"keyboard or mouse accepts displayed trade");
        if(service==RoomService::Exchange)check(run.keys==0&&run.dynamite==6,"native exchange spends exact resources");
        if(service==RoomService::Surgeon)check(run.player.hp==6&&run.money()==80,"native surgeon charges exact healing price");
        if(service==RoomService::Smuggler)check(run.player.maxHp==2&&run.items.size()==1,"native bargain includes Judas health loss");
        key(KEY_ESCAPE);check(!run.shopOpen&&!game.paused,"Escape leaves service without opening pause");
    }
    run.startBoss();run.killAll();run.step({});run.player.position=run.rewardPosition(run.room);game.updateCamera(10);
    run.interact();check(run.rewardOpen,"native boss reward opens");
    key(KEY_ESCAPE);check(!run.rewardOpen&&!game.paused,"optional reward can be dismissed");
    run.interact();click(470,556);check(!run.rewardOpen&&run.items.size()==2,"mouse chooses one boss reward");
    check(run.stats.shots==0,"NPC, trade and reward clicks never fire");
    game.close();std::cout<<"PASS native service walking, mouse/keyboard trades, modal guards, health preview and boss reward dismissal\n";
}
void suppliedBombInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory/"supplied-bomb.save");game.seedText="1866";game.themeChoice=ThemeChoice::Mine;game.launch();
    auto &run=*game.run;run.arena=Arena{};run.arena.bounds={{-25,-1,-25},{25,12,25}};
    for(auto &r:run.arena.rooms){r.bounds=run.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;}
    for(auto &r:run.rooms){r.residents.clear();r.cleared=false;r.plates.clear();}
    run.enemies.clear();run.hazards.clear();run.projectiles.clear();run.suppliedBombs.clear();
    run.debugScenario=true;run.godMode=true;run.roomClear=false;run.dynamite=0;
    run.player.position={0,.85f,8};
    const auto producer=run.spawnMonster(monsterId(809),{0,.85f,0});run.findEnemy(producer)->statueFacing={0,0,1};
    auto frame=[&]{game.update(Tick);BeginDrawing();EndDrawing();check(game.error.empty(),"supplied bomb input has no game error");};
    auto click=[&](Vector3 target) {
        const auto pixel=GetWorldToScreen(target,game.camera);
        mouseEvent(MousePosition,int(pixel.x),int(pixel.y));frame();
        check(!game.pointerOverControls(),"bomb target is outside HUD");
        mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
    };
    game.updateCamera(10);frame();check(run.suppliedBombs.size()==1,"Input fixture uses actual supplier stock");
    click(run.suppliedBombs[0].charge.position);
    for(int i=0;i<240&&!run.carriedBomb();++i)frame();
    check(run.carriedBomb()&&run.dynamite==0,"Mouse pickup click walks to stock and takes it with zero inventory");
    const auto shots=run.stats.shots;
    game.updateCamera(10);click(add(run.player.position,{5,0,0}));
    check(!run.carriedBomb()&&run.suppliedBombs[0].state==SuppliedBombState::Thrown&&run.stats.shots==shots,
          "Left click on empty ground throws held bomb without firing a gun");
    auto takeStock=[&] {
        run.suppliedBombs.clear();run.findEnemy(producer)->supplyCooldown=0;run.player.position={0,.85f,8};frame();
        check(run.suppliedBombs.size()==1,"Supplier restocks control fixture");
        run.player.position=run.suppliedBombs[0].charge.position;run.player.position.y=.85f;frame();
        check(run.carriedBomb()!=nullptr,"Contact takes real stock for control check");
    };
    takeStock();mouseEvent(MousePosition,1100,200);frame();
    mouseEvent(KeyDown,KEY_RIGHT);frame();mouseEvent(KeyUp,KEY_RIGHT);frame();
    check(!run.carriedBomb()&&run.suppliedBombs[0].charge.velocity.x!=0&&run.stats.shots==shots,
          "Arrow throws held bomb while cursor is over HUD");
    takeStock();mouseEvent(KeyDown,KEY_B);frame();mouseEvent(KeyUp,KEY_B);frame();
    check(!run.carriedBomb()&&run.suppliedBombs[0].charge.settled&&run.dynamite==0,"B places held bomb with zero ordinary inventory");
    takeStock();game.perform(Action::Dynamite);frame();
    check(!run.carriedBomb()&&run.suppliedBombs[0].charge.settled&&run.dynamite==0,
          "HUD places carried supplier bomb with zero ordinary inventory");
    game.close();std::cout<<"PASS native supplied bomb mouse approach, empty-ground throw, arrows over HUD, B placement and zero-inventory HUD placement\n";
}
void flightInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory/"flight.save");game.seedText="1866";game.themeChoice=ThemeChoice::Canyon;game.launch();
    auto &run=*game.run;run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.debugScenario=true;run.godMode=true;
    auto at=run.arena.rooms.back().center;at.y=.85f;
    run.arena.floorProps.push_back({StoryPropKind::Crate,{{at.x-1,0,at.z-1},{at.x+1,6,at.z+1}}});run.arena.rebuildWalls();
    const auto fly=run.spawnMonster(monsterId(13),at);run.player.position=add(at,{0,0,8});
    game.updateCamera(10);
    auto frame=[&]{game.update(Tick);BeginDrawing();EndDrawing();check(game.error.empty(),"flight mouse input has no game error");};
    const auto pixel=GetWorldToScreen(add(run.findEnemy(fly)->position,{0,.25f,0}),game.camera);
    mouseEvent(MousePosition,int(pixel.x),int(pixel.y));frame();
    check(!game.pointerOverControls()&&game.hoveredEnemy==fly,"mouse selects the elevated visible body, not its old ground rectangle");
    mouseEvent(MouseDown,MOUSE_BUTTON_LEFT);frame();mouseEvent(MouseUp,MOUSE_BUTTON_LEFT);frame();
    check(run.stats.shots==1&&run.player.aim.y>6.8f,"click-locked firing preserves actual flying target elevation");
    check(std::abs(run.player.facing.y)<.00001f,"aiming upward does not tilt character navigation/facing");
    game.close();std::cout<<"PASS native mouse picking and click-locked firing at elevated flying body\n";
}
} // namespace
int main(int argc, char **argv) {
    const auto directory =
        std::filesystem::temp_directory_path() /
        ("deathward-input-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(1280, 800, "DeathWard input verification");
        check(IsWindowReady(), "a graphics display is required for input verification");
        SetTargetFPS(0);
        SetExitKey(KEY_NULL);
        const std::string mode = argc > 1 ? argv[1] : "";
        if(mode.empty()||mode=="--balance-only") {
            balanceInputCheck(directory);
            if(mode=="--balance-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--shooting-balance-only") {
            shootingBalanceInputCheck(directory);
            if(mode=="--shooting-balance-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode=="--bombs-only") {
            bombInputCheck(directory);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode=="--keys-only") {
            keyInputCheck(directory);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode=="--coin-layout-only") {
            coinLayoutInputCheck(directory);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode=="--chest-layout-only") {
            chestLayoutInputCheck(directory);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode=="--chests-only") {
            chestInputCheck(directory);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode=="--coin-rewards-only") {
            coinRewardInputCheck(directory);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode=="--five-gaper-room-only") {
            combatRockRoomInputCheck(directory,109);CloseWindow();std::filesystem::remove_all(directory);return 0;
        }
        if(mode.empty()||mode=="--four-gaper-room-only") {
            combatRockRoomInputCheck(directory,108);
            if(mode=="--four-gaper-room-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--combat-rock-room-only") {
            combatRockRoomInputCheck(directory);
            if(mode=="--combat-rock-room-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--heart-rock-room-only") {
            heartRockRoomInputCheck(directory);
            if(mode=="--heart-rock-room-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--room-hearts-only") {
            roomHeartsInputCheck(directory);
            if(mode=="--room-hearts-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--red-heart-rewards-only") {
            redHeartRewardsInputCheck(directory);
            if(mode=="--red-heart-rewards-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--source-combat-room-only") {
            sourceCombatRoomInputCheck(directory);
            if(mode=="--source-combat-room-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--combat-balance-only") {
            combatBalanceInputCheck(directory);
            if(mode=="--combat-balance-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--pooter-balance-only") {
            pooterBalanceInputCheck(directory);
            if(mode=="--pooter-balance-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--spider-balance-only") {
            spiderBalanceInputCheck(directory);
            if(mode=="--spider-balance-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--gaper-balance-only") {
            gaperBalanceInputCheck(directory);
            if(mode=="--gaper-balance-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--starting-hearts-only") {
            startingHeartsInputCheck(directory);
            if(mode=="--starting-hearts-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--supplied-bomb-only") {
            suppliedBombInputCheck(directory);
            if(mode=="--supplied-bomb-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--flight-only") {
            flightInputCheck(directory);
            if(mode=="--flight-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--hud-only") {
            hudInputCheck(directory);
            if(mode=="--hud-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--keyboard-only") {
            keyboardInputCheck(directory);
            if(mode=="--keyboard-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if(mode.empty()||mode=="--economy-only") {
            economyInputCheck(directory);
            if(mode=="--economy-only"){CloseWindow();std::filesystem::remove_all(directory);return 0;}
        }
        if (mode.empty() || mode == "--arrows-only") {
            arrowInputCheck(directory, dw::MissionTheme::Mine);
            arrowInputCheck(directory, dw::MissionTheme::Canyon);
            if (mode == "--arrows-only") {
                CloseWindow();
                std::filesystem::remove_all(directory);
                return 0;
            }
        }
        if (mode == "--river-only") {
            boundaryRiverInputCheck(directory);
            interiorRiverInputCheck(directory);
            CloseWindow();
            std::filesystem::remove_all(directory);
            return 0;
        }
        if (mode == "--vegetation-only") {
            vegetationInputCheck(directory);
            CloseWindow();
            std::filesystem::remove_all(directory);
            return 0;
        }
        for (auto theme : {dw::MissionTheme::Mine, dw::MissionTheme::Canyon}) {
            if (mode != "--dynamite-only")
                shopInputCheck(directory, theme);
            if (mode != "--shop-only")
                dynamiteInputCheck(directory, theme);
        }
        if (mode == "--shop-only" || mode == "--dynamite-only") {
            CloseWindow();
            std::filesystem::remove_all(directory);
            return 0;
        }
        dw::Game game(directory / "campaign.save");
        check(game.animals.residents().size() == 5, "Black Creek loads five ambient animals");
        game.update(dw::Tick);
        const auto animalTime = game.animals.time();
        check(animalTime > 0, "hub update advances animal simulation");
        game.paused = true;
        game.update(dw::Tick);
        check(game.animals.time() == animalTime, "pause freezes animal poses and motion");
        game.paused = false;
        game.missionMenu = true;
        game.update(dw::Tick);
        check(game.animals.time() == animalTime, "mission selection freezes ambient animals");
        game.missionMenu = false;
        check(game.musicScene() == dw::MusicScene::Town, "default hub selects its town score");
        dw::Renderer renderer;
        const dw::Game::SceneryPicker pickScenery = [&](const auto &run, const auto &camera, Ray ray) {
            return renderer.pickScenery(run, camera, ray);
        };
        auto frame = [&](int x = 10, int y = 10, bool left = false, bool right = false, bool middle = false,
                         bool shift = false, float dt = dw::Tick) {
            mouseEvent(MousePosition, x, y);
            mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
            mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
            mouseEvent(middle ? MouseDown : MouseUp, MOUSE_BUTTON_MIDDLE);
            mouseEvent(shift ? KeyDown : KeyUp, KEY_LEFT_SHIFT);
            game.update(dt, pickScenery);
            BeginDrawing();
            auto action = renderer.draw(game);
            EndDrawing();
            game.perform(action);
        };
        auto click = [&](int x, int y, int button = MOUSE_BUTTON_LEFT) {
            frame(x, y);
            frame(x, y, button == MOUSE_BUTTON_LEFT, button == MOUSE_BUTTON_RIGHT,
                  button == MOUSE_BUTTON_MIDDLE);
            frame(x, y);
        };
        auto pressKey = [&](int key, bool shift = false) {
            mouseEvent(KeyDown, key);
            frame(10, 10, false, false, false, shift);
            mouseEvent(KeyUp, key);
            frame();
        };
        auto cameraAngle = [&] { return dw::unit(dw::sub(game.camera.position, game.camera.target)); };
        auto orbit = [&](int dx, int dy) {
            frame(600, 350);
            frame(600, 350, false, false, true);
            frame(600 + dx, 350 + dy, false, false, true);
            frame();
        };
        auto verifyOrbit = [&](auto verifyRotatedView) {
            const auto beforeAngle = cameraAngle();
            const float beforeRadius = dw::distance(game.camera.position, game.camera.target);
            const auto beforePosition = game.run ? game.run->player.position : game.town.player.position;
            frame(600, 350, false, false, true);
            check(dw::distance(beforeAngle, cameraAngle()) < .0001f,
                  "pressing the middle button starts rotation without a camera jump");
            frame(750, 390, false, false, true);
            const auto rotated = cameraAngle();
            check(dw::distance(beforeAngle, rotated) > .1f && rotated.y > beforeAngle.y &&
                      std::abs(dw::distance(game.camera.position, game.camera.target) - beforeRadius) < .001f,
                  "middle drag orbits and tilts the camera without changing zoom");
            check(dw::distance(beforePosition,
                               game.run ? game.run->player.position : game.town.player.position) < .001f,
                  "rotating the camera never moves the player");
            frame();
            frame(850, 450);
            check(dw::distance(rotated, cameraAngle()) < .0001f,
                  "releasing the middle button stops rotation immediately");
            verifyRotatedView();
            orbit(-150, -40);
            check(dw::distance(beforeAngle, cameraAngle()) < .0001f,
                  "opposite mouse drags restore the previous camera orientation");
            for (int i = 0; i < 120; ++i)
                frame();
        };
        frame();
        check(game.screen == dw::Screen::Hub && !game.run && game.town.loaded(),
              "new games start in the walkable original town without beginning a campaign run");
        check(std::abs(game.cameraZoomPercent() - 160) < .001f, "new hub sessions start at 160% zoom");
        check(game.themeChoice == dw::ThemeChoice::Canyon,
              "new sessions offer Isaac-only canyon missions by default");
        check(!game.campaign.data().pending && game.campaign.data().history.empty(),
              "town exploration does not create a pending mission or a campaign outcome");
        const auto blackCreekArrival = game.town.spawn;
        const auto travelAngle = cameraAngle();
        const auto travelRadius = dw::distance(game.camera.position, game.camera.target);
        mouseEvent(MouseWheel, 0, 3);
        frame(1050, 734);
        frame(1050, 734, false, false, true);
        frame(1120, 734, false, false, true);
        frame(1050, 734);
        check(dw::distance(travelAngle, cameraAngle()) < .0001f &&
                  std::abs(dw::distance(game.camera.position, game.camera.target) - travelRadius) < .001f,
              "the hub travel control blocks camera zoom and rotation behind it");
        const auto beforeTravel = game.town.player.position;
        frame(1050, 734, true);
        check(game.activeHub == dw::HubKind::BlackCreek && !game.town.destination() &&
                  dw::distance(beforeTravel, game.town.player.position) < .001f,
              "pressing hub travel does not move the character or click through to the ground");
        frame(1050, 734);
        check(game.activeHub == dw::HubKind::Frontier && game.screen == dw::Screen::Hub && !game.paused &&
                  game.town.loaded() && dw::distance(blackCreekArrival, game.town.spawn) > 20,
              "the visible travel button switches directly to Frontier's scene and navigation");
        const auto frontierArrival = game.town.player.position;
        check(game.animals.residents().empty(), "Black Creek animals do not leak into Frontier");
        mouseEvent(KeyDown, KEY_W);
        for (int i = 0; i < 20; ++i)
            frame(700, 400);
        mouseEvent(KeyUp, KEY_W);
        frame();
        check(dw::distance(frontierArrival, game.town.player.position) > .3f &&
                  game.town.walkable(game.town.player.position),
              "WASD moves through the second hub's imported terrain");
        const auto frontierPixel = GetWorldToScreen(game.town.spawn, game.camera);
        click(int(frontierPixel.x), int(frontierPixel.y));
        for (int i = 0; i < 120; ++i)
            frame();
        check(dw::distance(frontierArrival, game.town.player.position) < .7f,
              "mouse ground targeting reaches the correct elevation in Frontier");
        pressKey(KEY_F4);
        check(game.editorRequested && game.hubDirectory().filename() == "frontier",
              "Frontier's editor targets its own pack instead of the first town");
        game.editorRequested = false;
        click(1050, 734);
        check(game.activeHub == dw::HubKind::BlackCreek &&
                  dw::distance(game.town.spawn, blackCreekArrival) < .001f && !game.campaign.data().pending &&
                  game.campaign.data().history.empty(),
              "the visible return button restores Black Creek without creating a campaign outcome");
        click(590, 734);
        click(620, 624);
        check(game.activeHub == dw::HubKind::Frontier && !game.paused,
              "pause-screen travel remains available alongside the visible hub button");
        click(590, 734);
        click(620, 624);
        check(game.activeHub == dw::HubKind::BlackCreek && !game.paused,
              "pause-screen return travel remains available");
        check(game.animals.residents().size() == 5, "return travel reloads town animals");
        click(1050, 680);
        check(game.activeHub == dw::HubKind::Redstone && game.hubDirectory().filename() == "redstone" &&
                  game.town.loaded() && game.townObjects.solids().size() == 4 &&
                  game.musicScene() == dw::MusicScene::Canyon,
              "the second travel button opens the canyon hub with its convoy and canyon score");
        pressKey(KEY_F4);
        check(game.editorRequested && game.hubDirectory().filename() == "redstone",
              "the canyon editor targets its independent authored pack");
        game.editorRequested = false;
        click(1050, 680);
        check(game.activeHub == dw::HubKind::Frontier, "Redstone offers direct travel to Frontier");
        click(590, 734);
        click(620, 676);
        check(game.activeHub == dw::HubKind::Redstone && !game.paused,
              "the pause menu offers direct travel to the canyon");
        click(1050, 734);
        check(game.activeHub == dw::HubKind::BlackCreek && game.campaign.data().history.empty(),
              "travel from the canyon returns to Black Creek without a mission outcome");
        pressKey(KEY_F4);
        check(game.editorRequested && game.screen == dw::Screen::Hub && !game.run &&
                  !game.campaign.data().pending,
              "F4 requests the town editor without starting an expedition");
        game.editorRequested = false;
        const auto arrival = game.town.player.position;
        mouseEvent(KeyDown, KEY_W);
        for (int i = 0; i < 20; ++i)
            frame(700, 400);
        mouseEvent(KeyUp, KEY_W);
        frame();
        check(dw::distance(arrival, game.town.player.position) > .3f &&
                  game.town.walkable(game.town.player.position),
              "WASD walks through the hub on imported terrain");
        auto arrivalScreen = GetWorldToScreen(game.town.spawn, game.camera);
        click(int(arrivalScreen.x), int(arrivalScreen.y));
        for (int i = 0; i < 180; ++i)
            frame();
        check(dw::distance(game.town.player.position, arrival) < .7f,
              "clicking town terrain routes the character to the correct elevation");
        auto townClick = [&](Vector3 goal) {
            goal.y = game.town.height(goal);
            const auto pixel = GetWorldToScreen(goal, game.camera);
            frame(int(pixel.x), int(pixel.y));
            const auto picked = game.town.pickGround(GetScreenToWorldRay(GetMousePosition(), game.camera));
            check(picked.has_value(), "town ground under the cursor can be picked");
            frame(int(pixel.x), int(pixel.y), true);
            check(game.town.destination() && dw::distance(*game.town.destination(), *picked) < .001f,
                  "town ground clicks preserve the exact point instead of snapping to cell centers");
            for (int i = 0; i < 180; ++i)
                frame();
            check(dw::distance(game.town.player.position, dw::add(*picked, {0, .85f, 0})) < .001f,
                  "the town character reaches the selected point and elevation");
        };
        townClick(dw::add(game.town.spawn, {.12f, 0, -4.13f}));
        mouseEvent(MouseWheel, 0, 3);
        for (int i = 0; i < 120; ++i)
            frame();
        townClick(dw::add(game.town.spawn, {.07f, 0, -.08f}));
        mouseEvent(MouseWheel, 0, -3);
        for (int i = 0; i < 120; ++i)
            frame();
        verifyOrbit([&] { townClick(dw::add(game.town.spawn, {.09f, 0, -2.17f})); });
        const auto beforeHudOrbit = cameraAngle();
        frame(100, 70, false, false, true);
        frame(800, 450, false, false, true);
        check(dw::distance(beforeHudOrbit, cameraAngle()) < .0001f,
              "middle drags that start on hub controls never rotate the view");
        frame();
        const auto beforeHudDrag = game.town.player.position;
        frame(100, 70, true);
        auto groundPixel = GetWorldToScreen(dw::add(game.town.spawn, {0, 0, -4}), game.camera);
        for (int i = 0; i < 20; ++i)
            frame(int(groundPixel.x), int(groundPixel.y), true);
        check(!game.town.destination() && dw::distance(beforeHudDrag, game.town.player.position) < .001f,
              "dragging a held HUD click into town never starts ground movement");
        frame();
        // Approach until the board is in view at the closer starting zoom.
        check(game.town.moveTo(game.town.mission), "the board approach fixture has a walkable route");
        for (int i = 0; i < 1800 && dw::distance(game.town.player.position, game.town.mission) > 6; ++i)
            game.town.step({}, dw::Tick);
        game.town.stop();
        game.updateCamera(10);
        const auto boardPixel = GetWorldToScreen(dw::add(game.town.mission, {0, 1.5f, 0}), game.camera);
        frame(int(boardPixel.x), int(boardPixel.y), true);
        check(game.walkingToMission, "clicking the board starts its approach");
        for (int i = 0; i < 30; ++i)
            frame(int(groundPixel.x), int(groundPixel.y), true);
        check(game.walkingToMission || game.missionMenu,
              "holding a board click keeps approaching it after the cursor moves onto ground");
        frame();
        game.town.stop();
        game.walkingToMission = false;
        click(140, 735);
        for (int i = 0; i < 1800 && !game.missionMenu; ++i)
            frame();
        check(game.missionMenu && game.town.nearMission() && !game.run,
              "missions button walks to the station and opens mission selection on arrival");
        check(dw::distance(arrival, game.town.player.position) > 2,
              "the town character moves through the scene before selecting a mission");
        const auto firstSeed = game.seedText;
        click(850, 433);
        check(game.seedText != firstSeed && !game.run, "new mission chooses a fresh seed without launching");
        game.seedText = "invalid";
        click(650, 550);
        check(!game.run && game.missionMenu && !game.error.empty(),
              "invalid seeds preserve the mission menu");
        game.seedText = "1866";
        click(630, 372);
        check(game.themeChoice == dw::ThemeChoice::Mine && game.offeredTheme() == dw::MissionTheme::Mine,
              "the mine theme can be selected with the mouse");
        click(380, 372);
        check(game.themeChoice == dw::ThemeChoice::Seeded &&
                  game.offeredTheme() == dw::resolveTheme(dw::ThemeChoice::Seeded, 1866),
              "the seeded theme preview matches the offered seed");
        click(860, 372);
        check(game.themeChoice == dw::ThemeChoice::Canyon &&
                  game.offeredTheme() == dw::MissionTheme::Canyon && game.seedText == "1866" && !game.run,
              "canyon selection preserves the editable seed and waits for launch");
        // The following occlusion/pickup regression uses the original seed's
        // specific scenery and coin placement. Other input fixtures use Growing.
        for(int i=0;i<5&&game.expeditionPacing!=dw::ExpeditionPacing::Classic;++i)click(500,497);
        check(game.expeditionPacing==dw::ExpeditionPacing::Classic,"mission board selects Classic through the mouse");
        click(650, 550);
        check(game.run && game.screen == dw::Screen::Expedition, "mouse launch opens expedition");
        check(game.musicScene() == dw::MusicScene::Canyon, "peaceful canyon arrival uses exploration music");
        check(game.run->arena.theme == dw::MissionTheme::Canyon &&
                  game.campaign.data().pending->expedition == "Redstone Canyon",
              "the selected canyon theme reaches gameplay and the initial campaign checkpoint");
        check(game.debug && !game.debugPanelOpen && game.run->roomClear && game.run->livingEnemies() == 0,
              "new games start with hidden cheats enabled and an open, enemy-free starting room");
        // A real seeded pile overlaps a passage's generous click area at wide zoom.
        // Clicking the pile must collect it rather than taking that passage.
        const auto moneyArrival = game.run->player.position;
        const auto moneyCamera = game.camera;
        const auto nearbyCoin = *std::min_element(
            game.run->moneyPickups.begin(), game.run->moneyPickups.end(), [&](const auto &a, const auto &b) {
                return dw::distance(a.position, moneyArrival) < dw::distance(b.position, moneyArrival);
            });
        check(game.run->arena.roomAt(nearbyCoin.position) == 0, "pickup fixture uses the quiet room");
        const auto startingMoney = game.run->money();
        game.camera.target = dw::add(moneyArrival, {0, .1f, 0});
        game.camera.position = dw::add(game.camera.target, dw::mul({23, 30, 23}, 1.284f));
        auto moneyPoint = nearbyCoin.position;
        moneyPoint.y = .4f;
        const auto moneyPixel = GetWorldToScreen(moneyPoint, game.camera);
        frame(int(moneyPixel.x), int(moneyPixel.y), true);
        for (int i = 0; i < 240 && game.run->money() < startingMoney + nearbyCoin.value; ++i)
            frame();
        check(game.run->money() >= startingMoney + nearbyCoin.value && game.run->room == 0 &&
                  game.run->stats.shots == 0,
              "a coin near a passage takes priority without leaving the room or firing");
        for (int i = 0; i < 60; ++i)
            frame();
        game.run->player.position = moneyArrival;
        game.camera = moneyCamera;
        frame(100, 200);
        check(!game.pointerOverControls(), "hidden cheat panel never blocks world mouse input");
        pressKey(KEY_GRAVE);
        frame(100, 200);
        check(game.debugPanelOpen && game.pointerOverControls(),
              "the optional shortcut panel opens only on request and captures its own clicks");
        pressKey(KEY_GRAVE);
        check(!game.debugPanelOpen && game.debug, "hiding shortcuts leaves cheat hotkeys active");
        pressKey(KEY_F2);
        check(game.run->godMode, "cheat hotkeys work immediately without pressing F1 first");
        pressKey(KEY_F1);
        check(!game.debug && !game.run->godMode, "F1 can disable the default cheat mode");
        pressKey(KEY_F1);
        check(game.debug && !game.debugPanelOpen, "enabling cheats never reopens the shortcut panel");
        game.run->godMode = true;
        game.run->debugScenario = true;
        for (int i = 0; i < 100; ++i)
            frame(); // Settle the tracking camera before projecting a click.
        Vector3 destination = game.run->arena.rooms[0].center;
        game.run->moneyPickups = {{{destination.x, .85f, destination.z}, 3, 1, false}};
        const auto moneyBeforePickup = game.run->money();
        destination.y = 0;
        auto point = GetWorldToScreen(destination, game.camera);
        BeginDrawing();
        renderer.draw(game);
        rlDrawRenderBatchActive();
        const auto coinImage = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(coinImage, "artifacts/money-ground.png"), "save the coin rendering capture");
        UnloadImage(coinImage);
        EndDrawing();
        click(int(point.x), int(point.y));
        check(game.run->moveDestination().has_value(), "left-clicking ground queues a route");
        for (int i = 0; i < 200; ++i)
            frame();
        destination.y = 0.85f;
        check(dw::distance(game.run->player.position, destination) < 0.15f,
              "mouse ray and navigation reach clicked ground point");
        check(game.run->stats.shots == 0, "left-clicking ground never fires");
        check(game.run->money() == moneyBeforePickup + 3 && game.run->moneyPickups.empty() &&
                  game.campaign.data().pending->moneyCollected == game.run->moneyCollected,
              "clicking a coin approaches it, collects it and saves the earnings without firing");
        // Hold an enemy, move the cursor away, then move the enemy: attacks must track its body.
        const auto target = game.run->spawn(dw::EnemyKind::Gunman, {0, 0.85f, -6});
        game.run->findEnemy(target)->hp = game.run->findEnemy(target)->maxHp = 10000;
        point = GetWorldToScreen({0, 1.5f, -6}, game.camera);
        frame(int(point.x), int(point.y));
        check(game.hoveredEnemy == target, "enemy body is selectable above the ground plane");
        frame(int(point.x), int(point.y), true);
        const auto attackPosition = game.run->player.position;
        game.run->findEnemy(target)->position.x = 2;
        for (int i = 0; i < 240; ++i)
            frame(680, 315, true);
        check(game.run->stats.shots >= 13, "holding an enemy fires continuously without reloading");
        check(game.run->findEnemy(target)->hp <= 10000 - dw::RevolverDamage * 10,
              "held attack tracks the moving enemy even when the cursor moves away");
        check(dw::distance(game.run->player.position, attackPosition) < 0.001f,
              "enemy attacks hold position instead of walking toward the cursor");
        game.run->findEnemy(target)->alive = false;
        const auto beforeDeathHold = game.run->stats.shots;
        for (int i = 0; i < 30; ++i)
            frame(680, 315, true);
        check(game.run->stats.shots == beforeDeathHold && !game.run->moveDestination(),
              "a dead target never turns a held attack into ground movement");
        frame(680, 315);
        // Shift attacks empty ground without movement, even during an existing route.
        point = GetWorldToScreen({6, 0, 0}, game.camera);
        click(int(point.x), int(point.y));
        const auto shiftPosition = game.run->player.position;
        for (int i = 0; i < 40; ++i)
            frame(680, 315, true, false, false, true);
        frame();
        check(game.run->stats.shots > beforeDeathHold && !game.run->moveDestination() &&
                  dw::distance(game.run->player.position, shiftPosition) < 0.001f,
              "Shift+LMB force-fires and cancels navigation without moving");
        const auto beforeRight = game.run->stats.shots;
        for (int i = 0; i < 40; ++i)
            frame(680, 315, false, true);
        frame();
        check(game.run->stats.shots > beforeRight && !game.run->moveDestination(),
              "RMB fires directly instead of issuing movement orders");
        game.run->player.fireCooldown = 0;
        const auto beforeShortClick = game.run->stats.shots;
        frame(680, 315, false, true, false, false, dw::Tick / 4);
        frame(680, 315, false, false, false, false, dw::Tick / 4);
        frame();
        check(game.run->stats.shots == beforeShortClick + 1,
              "a short attack click between simulation ticks is preserved");
        const auto shots = game.run->stats.shots;
        click(680, 315, MOUSE_BUTTON_MIDDLE);
        check(game.run->player.dodge == 0, "middle mouse button is reserved for camera rotation");
        verifyOrbit([&] {
            check(game.run->player.dodge == 0 && game.run->stats.shots == shots,
                  "middle dragging never dodges or fires");
            const auto start = game.run->player.position;
            const auto angle = cameraAngle();
            const auto forward = dw::unit(Vector3{-angle.x, 0, -angle.z});
            pressKey(KEY_W);
            auto movement = dw::sub(game.run->player.position, start);
            movement.y = 0;
            check(dw::length(movement) > .01f && dw::distance(dw::unit(movement), forward) < .001f,
                  "WASD remains relative to the rotated camera");
            for (int i = 0; i < 120; ++i)
                frame(); // Settle the following camera before projecting a world-space test target.
            const auto pixel = GetWorldToScreen({start.x, 0, start.z}, game.camera);
            click(int(pixel.x), int(pixel.y));
            for (int i = 0; i < 120; ++i)
                frame();
            check(dw::distance(start, game.run->player.position) < .15f,
                  "ground clicking remains accurate with a rotated mission camera");
        });
        pressKey(KEY_SPACE);
        check(game.run->player.dodge > 0, "Space still triggers dodge");
        for (int i = 0; i < 80; ++i)
            frame();
        click(642, 736);
        frame(670, 711);
        check(game.run->player.dodge > 0, "onscreen dodge works with a two-button mouse");
        click(754, 736);
        check(game.paused, "onscreen pause button pauses the expedition");
        const double duration = game.run->stats.duration;
        for (int i = 0; i < 60; ++i)
            frame(100, 200, true);
        frame(100, 200);
        check(game.run->stats.duration == duration, "simulation remains frozen while paused");
        const auto audioDefaults = game.audioSettings;
        click(230, 338);
        click(282, 390);
        click(230, 442);
        click(282, 494);
        check(std::abs(game.audioSettings.master - (audioDefaults.master - .1f)) < .001f &&
                  std::abs(game.audioSettings.effects - (audioDefaults.effects + .1f)) < .001f &&
                  std::abs(game.audioSettings.ambience - (audioDefaults.ambience - .1f)) < .001f &&
                  std::abs(game.audioSettings.music - (audioDefaults.music + .1f)) < .001f,
              "pause audio controls adjust each independent volume");
        click(90, 569);
        check(game.audioSettings.muted, "pause audio mute toggles independently of cheats");
        click(90, 569);
        click(237, 569);
        check(!game.audioSettings.muted &&
                  std::any_of(game.audioCues.cues().begin(), game.audioCues.cues().end(),
                              [](const auto &cue) { return cue.kind == dw::AudioCueKind::Test; }),
              "test button queues an audio preview without advancing gameplay");
        for (int i = 0; i < 12; ++i)
            game.perform(dw::Action::MasterUp);
        check(game.audioSettings.master == 1, "audio volume is capped at 100 percent");
        for (int i = 0; i < 12; ++i)
            game.perform(dw::Action::MasterDown);
        check(game.audioSettings.master == 0, "audio volume cannot become negative");
        for (int i = 0; i < 12; ++i)
            game.perform(dw::Action::MusicDown);
        check(game.audioSettings.music == 0 && game.audioSettings.effects == audioDefaults.effects + .1f,
              "music can be muted independently of effects");
        game.audioSettings = audioDefaults;
        frame();
        std::filesystem::create_directories("artifacts");
        auto audioPanel = LoadImageFromScreen();
        ExportImage(audioPanel, "artifacts/audio-pause-controls.png");
        UnloadImage(audioPanel);
        check(game.run->stats.duration == duration && game.run->stats.shots == shots,
              "audio controls never fire or resume the simulation");
        click(1214, 329);
        click(1214, 424);
        check(game.run->player.maxHp == dw::StartingHealth + 2 &&
                  game.run->player.hp == dw::StartingHealth + 2 &&
                  game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource) + 4 && game.paused,
              "pause controls adjust health and damage immediately without resuming");
        click(1156, 329);
        click(1156, 424);
        check(game.run->player.maxHp == dw::StartingHealth &&
                  game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource),
              "pause controls can lower health and damage");
        pressKey(KEY_EQUAL);
        pressKey(KEY_KP_ADD, true);
        check(game.run->player.maxHp == dw::StartingHealth + 2 &&
                  game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource) + 4,
              "keyboard and keypad stat controls work while paused");
        click(1050, 494);
        check(game.run->player.maxHp == dw::StartingHealth &&
                  game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource) && game.run->stats.duration == duration,
              "restore defaults changes stats while simulation remains frozen");
        click(620, 445);
        check(!game.paused, "mouse resumes the expedition");
        check(game.run->stats.shots == shots, "HUD and paused clicks never fire the revolver");
        pressKey(KEY_MINUS);
        pressKey(KEY_EQUAL, true);
        check(game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource) - 4 &&
                  game.run->player.maxHp == dw::StartingHealth + 2 && !game.debugPanelOpen,
              "live stat hotkeys work while the cheat overlay stays hidden");
        pressKey(KEY_F1);
        pressKey(KEY_EQUAL);
        game.perform(dw::Action::HealthUp);
        pressKey(KEY_HOME);
        check(game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource) - 4 &&
                  game.run->player.maxHp == dw::StartingHealth + 2,
              "stat shortcuts and actions are disabled with cheats off");
        pressKey(KEY_F1);
        pressKey(KEY_HOME);
        check(game.run->player.shotDamage == (dw::ReferencePlayerDamage*dw::CombatHealthUnitsPerSource) &&
                  game.run->player.maxHp == dw::StartingHealth,
              "Home restores defaults during play");
        game.run->godMode = true;
        game.run->clearRoomDebug();
        const int passageIndex = game.run->arena.rooms[0].passages.front();
        const auto &passage = game.run->arena.passages[size_t(passageIndex)];
        const int side = passage.rooms[0] == 0 ? 0 : 1;
        const int nextRoom = passage.rooms[size_t(1 - side)];
        const auto doorway = game.run->arena.doorApproach(passageIndex, side);
        const auto direction =
            dw::unit(dw::sub(game.run->arena.doorApproach(passageIndex, 1 - side), doorway));
        game.run->player.position = dw::sub(doorway, dw::mul(direction, 3));
        for (int i = 0; i < 100; ++i)
            frame();
        point = GetWorldToScreen({doorway.x, 1.5f, doorway.z}, game.camera);
        click(int(point.x), int(point.y));
        for (int i = 0; i < 600 && game.run->room == 0; ++i) {
            const auto before = game.run->player.position;
            frame();
            check(dw::distance(before, game.run->player.position) < 0.11f,
                  "mouse doorway traversal is continuous, without teleporting");
        }
        check(game.run->room == nextRoom, "left-clicking an open doorway walks into the connected room");
        check(game.run->arena.passages[size_t(passageIndex)].closed(1 - side),
              "the entrance seals behind the player");
        for (int i = 0; i < 100; ++i)
            frame();
        const float framingOffset = 200 / game.cameraZoomPercent();
        const auto cameraGoal = dw::sub(game.run->player.position, {framingOffset, 0.85f, framingOffset});
        check(dw::distance(game.camera.target, cameraGoal) < 0.1f,
              "camera follows the player to distant rooms");
        game.run->enterRoom(2);
        game.run->clearRoomDebug();
        game.run->player.position = game.run->arena.rooms[2].center;
        for (int i = 0; i < 100; ++i)
            frame();
        point = GetWorldToScreen({game.run->arena.miners.x, 1.7f, game.run->arena.miners.z}, game.camera);
        click(int(point.x), int(point.y));
        for (int i = 0; i < 220; ++i)
            frame();
        check(game.run->rescued, "left-clicking an objective's body approaches and interacts");
        const int powerRoom = game.run->arena.roomCount() - 2;
        const int lockIndex = game.run->arena.rooms[size_t(powerRoom)].passages.front();
        const auto &lock = game.run->arena.passages[size_t(lockIndex)];
        const int outside = lock.rooms[0] == powerRoom ? 1 : 0;
        const int approachRoom = lock.rooms[size_t(outside)];
        auto approachLock = [&] {
            game.run->enterRoom(approachRoom);
            game.run->clearRoomDebug();
            game.run->player.position = game.run->arena.doorApproach(lockIndex, outside);
            for (int i = 0; i < 100; ++i)
                frame();
            auto at = game.run->arena.doorApproach(lockIndex, outside);
            at.y = 1.5f;
            const auto screen = GetWorldToScreen(at, game.camera);
            click(int(screen.x), int(screen.y));
        };
        approachLock();
        check(game.run->keys == 0 && lock.locked, "mouse cannot unlock a golden door without a key");
        auto &key = game.run->arena.keys.front();
        game.run->enterRoom(key.room);
        game.run->clearRoomDebug();
        game.run->player.position = game.run->arena.rooms[size_t(key.room)].center;
        for (int i = 0; i < 100; ++i)
            frame();
        point = GetWorldToScreen({key.position.x, 1.2f, key.position.z}, game.camera);
        click(int(point.x), int(point.y));
        for (int i = 0; i < 280; ++i)
            frame();
        check(key.collected && game.run->keys == 1, "left-clicking a key approaches and picks it up once");
        approachLock();
        for (int i = 0; i < 600 && game.run->room != powerRoom; ++i)
            frame();
        check(game.run->room == powerRoom && !lock.locked && game.run->keys == 0,
              "mouse unlock spends one key and walks into the power room");
        check(!game.run->rewardOpen, "entering a power room does not automatically claim its item");
        for (int i = 0; i < 100; ++i)
            frame();
        const auto pedestal = game.run->arena.rooms[size_t(powerRoom)].objective;
        point = GetWorldToScreen({pedestal.x, 1.3f, pedestal.z}, game.camera);
        click(int(point.x), int(point.y));
        for (int i = 0; i < 350 && !game.run->rewardOpen; ++i)
            frame();
        check(game.run->rewardOpen, "left-clicking the pedestal opens its two choices");
        click(470, 556);
        check(!game.run->rewardOpen && game.run->powerUpsTaken == 1 && game.run->items.size() == 1,
              "mouse chooses exactly one power from the separate room");
        click(754, 736);
        click(620, 507);
        check(!game.run && game.screen == dw::Screen::Summary, "mouse retreat ends the run");
        check(game.lastSummary.stats.shots == shots, "retreat click does not produce an extra shot");
        check(game.campaign.data().world.prosperity == 42 && game.campaign.data().world.population == 48,
              "mouse-only outcome saves retreat and rescue consequences");
        game.perform(dw::Action::Hub);
        check(game.screen == dw::Screen::Hub && !game.run && !game.missionMenu &&
                  !game.campaign.data().pending && game.seedText != "1866" &&
                  dw::distance(game.town.player.position, dw::add(game.town.spawn, {0, .85f, 0})) < .01f,
              "mission results return to the town arrival point with a new mission offer and no pending run");
        game.launch();
        game.run->jumpDebug(2);
        game.paused = true;
        pressKey(KEY_F1);
        game.run->spawnEnemies(1);
        const auto initialEnemies = game.run->livingEnemies();
        pressKey(KEY_F3);
        pressKey(KEY_F10);
        check(game.run->livingEnemies() == initialEnemies && !game.collisionDebug,
              "cheat keys are inactive until F1 enables the mode");
        pressKey(KEY_F1);
        pressKey(KEY_F2);
        check(game.debug && game.run->godMode, "F1 enables cheats and F2 toggles invincibility");
        game.run->player.hp = 1;
        game.run->player.dodgeCooldown = 2;
        pressKey(KEY_F2, true);
        check(game.run->player.hp == game.run->player.maxHp && game.run->player.dodgeCooldown == 0,
              "Shift+F2 heals and resets cooldowns even while paused");
        pressKey(KEY_F3);
        check(game.run->livingEnemies() == 0 && !game.run->roomClear,
              "F3 kills current enemies without skipping the encounter");
        pressKey(KEY_F3, true);
        check(game.run->roomClear, "Shift+F3 clears the entire room immediately while paused");
        game.paused = false;
        for (int i = 0; i < 180; ++i)
            frame();
        check(game.run->livingEnemies() == 0, "cleared-room cheat never spawns another group");
        pressKey(KEY_F4);
        check(game.run->livingEnemies() >= 20 && game.run->livingEnemies() <= 40,
              "F4 spawns twenty testing enemies plus any attached companions");
        pressKey(KEY_F3, true);
        const auto selectedBefore = game.selectedMonster;
        pressKey(KEY_PERIOD);
        check(game.selectedMonster == selectedBefore + 1, "period selects the next catalog monster");
        pressKey(KEY_F4, true);
        check(game.run->livingEnemies() == 1 &&
                  game.run->enemies.front().monster == dw::monsterCatalog()[size_t(game.selectedMonster)].id,
              "Shift+F4 spawns the selected ID instead of a random crowd");
        pressKey(KEY_COMMA);
        check(game.selectedMonster == selectedBefore, "comma selects the previous catalog monster");
        pressKey(KEY_F3, true);
        pressKey(KEY_F6);
        pressKey(KEY_F6, true);
        check(game.run->items.size() == game.run->content->items().size() &&
                  std::all_of(game.run->content->items().begin(),game.run->content->items().end(),
                    [&](const auto &item){return std::find(game.run->items.begin(),game.run->items.end(),item.id)!=game.run->items.end();}) &&
                  game.run->keys == 3,
              "F6 grants every externally configured item and Shift+F6 supplies testing keys");
        pressKey(KEY_F12, true);
        check(game.run->room == 2 && !game.run->roomClear && game.run->livingEnemies() > 0,
              "Shift+F12 restarts the current room with its enemy group already present");
        check(game.musicScene() == dw::MusicScene::Combat,
              "an active ordinary encounter selects combat music");
        game.paused = true;
        pressKey(KEY_F12);
        check(game.run->room == 3 && !game.paused &&
                  dw::distance(game.camera.target, dw::sub(game.run->player.position,
                                                           {framingOffset, 0.85f, framingOffset})) < 0.01f,
              "F12 skips to the next room, resumes and immediately follows with the camera");
        pressKey(KEY_F7);
        check(game.run->room == game.run->finalRoom() && !game.run->boss() && game.run->roomThreats() > 0,
              "F7 jumps to the canyon's final monster encounter without a Western boss");
        check(game.musicScene() == dw::MusicScene::Boss, "canyon finale uses boss music without a Sheriff");
        pressKey(KEY_F3, true);
        pressKey(KEY_F7);
        check(!game.run->roomClear && !game.run->bossKilled && game.run->roomThreats() > 0,
              "F7 can replay a cleared canyon finale");
        const auto finalPopulation = game.run->livingEnemies();
        pressKey(KEY_F10);
        pressKey(KEY_O);
        pressKey(KEY_F1);
        check(!game.debug && !game.run->godMode && !game.slow && !game.collisionDebug,
              "turning cheat mode off disables invincibility, slow time and collision overlays");
        pressKey(KEY_F3);
        check(game.run->livingEnemies() == finalPopulation, "F3 is disabled again after leaving cheat mode");
        pressKey(KEY_F1);
        game.paused = true;
        pressKey(KEY_EQUAL);
        pressKey(KEY_EQUAL, true);
        pressKey(KEY_F8);
        check(!game.run && game.screen == dw::Screen::Summary &&
                  game.lastSummary.reason == dw::EndReason::Victory,
              "F8 completes the expedition immediately while paused");
        check(game.musicScene() == dw::MusicScene::Victory,
              "successful completion selects the victory score");
        game.perform(dw::Action::Hub);
        game.selectHub(dw::HubKind::Frontier);
        game.launch();
        check(game.run->player.hp == dw::StartingHealth + 2 &&
                  game.run->player.maxHp == dw::StartingHealth + 2 &&
                  game.run->player.shotDamage == game.balancePreset.playerDamage*dw::CombatHealthUnitsPerSource && game.run->items.empty(),
              "new expedition uses its selected Damage preset and retains debug heart capacity without old item penalties");
        pressKey(KEY_HOME);
        game.run->jumpDebug(game.run->arena.roomCount() - 2);
        game.run->player.position = game.run->arena.rooms[game.run->arena.roomCount() - 2].objective;
        game.run->interact();
        check(game.run->rewardOpen, "power-choice modal is open for terminal-cheat verification");
        pressKey(KEY_F9);
        check(!game.run && game.lastSummary.reason == dw::EndReason::Death,
              "F9 resolves defeat immediately from the power-choice modal");
        game.perform(dw::Action::Hub);
        game.launch();
        auto cameraDistance = [&] { return dw::distance(game.camera.position, game.camera.target); };
        auto settleCamera = [&] {
            for (int i = 0; i < 60; ++i)
                frame();
        };
        // Use open central floor, away from the entrance's clickable doorway.
        game.run->player.position = game.run->arena.rooms[0].center;
        const float defaultDistance = cameraDistance();
        check(std::abs(game.cameraZoomPercent() - 160) < .001f, "new missions retain the starting 160% zoom");
        const float referenceDistance = defaultDistance * 1.6f;
        const auto originalAngle = dw::unit(dw::sub(game.camera.position, game.camera.target));
        const auto beforeZoom = game.run->player.position;
        mouseEvent(MouseWheel, 0, 100);
        frame();
        check(cameraDistance() < defaultDistance && cameraDistance() > referenceDistance * 0.35f,
              "scrolling up smoothly moves the camera closer");
        check(std::abs(game.cameraZoomPercent() - 100 * referenceDistance / cameraDistance()) < .01f,
              "zoom display follows the actual smoothed camera distance");
        settleCamera();
        const float closestDistance = cameraDistance();
        check(std::abs(closestDistance - referenceDistance * 0.35f) < 0.01f,
              "large wheel input stops at the close zoom limit");
        check(dw::distance(beforeZoom, game.run->player.position) == 0 && game.run->stats.shots == 0 &&
                  game.run->player.dodge == 0,
              "scrolling never moves, shoots or dodges");
        mouseEvent(MouseWheel, 0, -100);
        frame(754, 736);
        settleCamera();
        check(std::abs(cameraDistance() - closestDistance) < 0.01f, "HUD controls ignore scrolling");
        mouseEvent(MouseWheel, 0, -100);
        frame(1100, 10);
        settleCamera();
        check(std::abs(cameraDistance() - closestDistance) < .01f,
              "the zoom readout blocks scrolling through the HUD");
        mouseEvent(MouseWheel, -100, 0);
        frame();
        game.paused = true;
        mouseEvent(MouseWheel, 0, -100);
        frame();
        game.paused = false;
        game.run->rewardOpen = true;
        mouseEvent(MouseWheel, 0, -100);
        frame();
        game.run->rewardOpen = false;
        settleCamera();
        check(std::abs(cameraDistance() - closestDistance) < 0.01f,
              "horizontal scroll, pause and power-choice screens leave zoom unchanged");
        auto verifyZoomedGroundClick = [&](Vector3 goal) {
            const auto pixel = GetWorldToScreen({goal.x, 0, goal.z}, game.camera);
            click(int(pixel.x), int(pixel.y));
            settleCamera();
            check(dw::distance(game.run->player.position, goal) < 0.15f,
                  "ground clicks stay accurate at both zoom limits");
        };
        verifyZoomedGroundClick(dw::sub(beforeZoom, {0, 0, 2}));
        mouseEvent(MouseWheel, 0, -100);
        frame();
        check(cameraDistance() > closestDistance, "scrolling down pulls the camera back");
        settleCamera();
        const float widestDistance = cameraDistance();
        check(std::abs(widestDistance - referenceDistance * 1.5f) < 0.01f &&
                  dw::distance(originalAngle, dw::unit(dw::sub(game.camera.position, game.camera.target))) <
                      0.0001f,
              "zoom out has a safe limit and preserves the viewing angle");
        verifyZoomedGroundClick(beforeZoom);
        orbit(0, 400);
        check(std::abs(std::asin(cameraAngle().y) * RAD2DEG - 75) < .001f,
              "upward camera tilt stops before the view can flip over");
        orbit(0, -400);
        check(std::abs(std::asin(cameraAngle().y) * RAD2DEG - 25) < .001f,
              "downward camera tilt stays above the ground");
        orbit(90, 60);
        auto retainedAngle = cameraAngle();
        frame(754, 736, false, false, true);
        frame(600, 350, false, false, true);
        frame();
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f,
              "middle drags from mission HUD controls do not rotate the camera");
        frame(600, 350, false, false, true);
        frame(650, 350, false, false, true);
        retainedAngle = cameraAngle();
        game.paused = true;
        frame(750, 450, false, false, true);
        game.paused = false;
        frame(850, 550, false, false, true);
        frame();
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f,
              "pausing cancels an active camera drag until a new middle press");
        game.run->rewardOpen = true;
        orbit(150, 100);
        game.run->rewardOpen = false;
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f, "power selection blocks camera rotation");
        pressKey(KEY_F12, true);
        check(std::abs(cameraDistance() - widestDistance) < 0.01f, "room jumps preserve the chosen zoom");
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f, "room jumps preserve camera rotation");
        game.run->player.hp = 0;
        frame();
        check(game.run && game.run->dead && game.screen == dw::Screen::Expedition,
              "natural death keeps the character visible for its animation");
        check(game.musicScene() == dw::MusicScene::Defeat, "death changes the score immediately");
        const auto deathDuration = game.run->stats.duration;
        const auto deathPosition = game.run->player.position;
        for (int i = 0; i < 60; ++i)
            frame();
        check(game.run && game.run->stats.duration == deathDuration &&
                  dw::distance(game.run->player.position, deathPosition) == 0,
              "death presentation does not keep simulating combat or movement");
        for (int i = 0; i < 70; ++i)
            frame();
        check(!game.run && game.lastSummary.reason == dw::EndReason::Death,
              "death animation finishes at the normal defeat summary");
        check(game.musicScene() == dw::MusicScene::Defeat,
              "defeat music continues across the summary transition");
        game.perform(dw::Action::Hub);
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f,
              "returning to town preserves camera rotation");
        game.missionMenu = true;
        orbit(150, 100);
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f, "the station menu blocks camera rotation");
        game.perform(dw::Action::CycleExpeditionPacing);
        check(game.expeditionPacing==dw::ExpeditionPacing::Growing,"mission board switches back to Growing pacing");
        game.missionMenu = false;
        game.perform(dw::Action::CycleExpeditionPacing);
        check(game.expeditionPacing==dw::ExpeditionPacing::Growing,"pacing changes only while choosing an expedition");
        game.launch();
        check(game.run->arena.roomCount()==9&&game.campaign.data().pending->pacing==dw::ExpeditionPacing::Growing,"selected pacing reaches gameplay and initial save");
        check(std::abs(game.cameraZoomPercent() - game.balancePreset.defaultZoomPercent) < 0.01f, "new expeditions restore the configured default zoom");
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f,
              "new expeditions retain session camera rotation");
        game.run->player.hp = 0;
        frame();
        game.close();
        check(game.lastSummary.reason == dw::EndReason::Death,
              "closing during a death animation records death, not retreat");
        renderer.unload();
        {
            dw::Game frontier(directory / "frontier.save", dw::HubKind::Frontier);
            check(frontier.town.loaded() && frontier.activeHub == dw::HubKind::Frontier,
                  "explicit startup hub loads Frontier directly");
            check(frontier.musicScene() == dw::MusicScene::Frontier, "Frontier selects its own hub score");
            const auto arrival = frontier.town.spawn;
            frontier.perform(dw::Action::Missions);
            for (int i = 0; i < 1200 && !frontier.missionMenu; ++i)
                frontier.update(dw::Tick);
            check(frontier.missionMenu, "Frontier mission board is reachable through normal hub controls");
            frontier.seedText = "1866";
            frontier.themeChoice = dw::ThemeChoice::Mine;
            frontier.launch();
            check(frontier.musicScene() == dw::MusicScene::Mine, "mine exploration has its own score");
            check(frontier.run && !frontier.selectHub(dw::HubKind::BlackCreek),
                  "an active mission prevents hub travel");
            frontier.finish(dw::EndReason::Retreat);
            check(frontier.musicScene() == dw::MusicScene::Frontier, "retreat does not play victory music");
            frontier.perform(dw::Action::Hub);
            check(frontier.activeHub == dw::HubKind::Frontier && !frontier.campaign.data().pending &&
                      dw::distance(frontier.town.player.position, dw::add(arrival, {0, .85f, 0})) < .001f,
                  "mission results return to the same Frontier hub and its arrival point");
            frontier.close();
        }
        CloseWindow();
        std::filesystem::remove_all(directory);
        std::cout << "PASS original town movement, station approach, mission seeds, launch and return loop\n";
        std::cout << "PASS Frontier travel, movement, picking, editor selection and mission return\n";
        std::cout
            << "PASS contextual LMB movement/attack/interaction, target tracking, Shift and RMB fire\n"
            << "PASS short clicks, no reload, mouse dodge, pause/resume, connected doorways, rescue "
               "and retreat\n"
            << "PASS mouse key pickup, locked doors and one-time power-room choice\n"
            << "PASS function-key cheats, disabled-mode guards, room/boss replay and modal outcomes\n"
            << "PASS smooth wheel zoom, limits, modal guards, zoomed ground clicks and retained zoom\n"
            << "PASS middle-drag orbit, tilt limits, rotated controls, modal guards and retained angle\n"
            << "PASS animated natural death, frozen combat and closing during death\n"
            << "PASS HUD clicks never fire; sixth-shot effects covered by core contracts\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << "\nTemporary campaign: " << directory << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
