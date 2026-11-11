#include "core/Game.hpp"
#include <iostream>

namespace dw {
void Game::initializeBalance() {
    balanceDirectory=campaign.path();balanceDirectory+=".balance";
    balanceFile=(balanceDirectory/"export.json").string();
    balancePreset={1,defaultMechanics()->fingerprint()};
    try {
        const auto next=balanceDirectory/"next.json";
        if(std::filesystem::exists(next)) {
            auto preset=BalancePreset::load(next,balancePreset.mechanicsFingerprint);
            balancePreset=preset;nextBalancePreset=preset;
            balanceNotice="Remembered player, shooting, zoom and map settings loaded for expedition start.";
        }
    } catch(const std::exception &e) {
        balanceRestoreError_=std::string("Remembered preset could not load: ")+e.what();
        error=balanceRestoreError_;paused=true;
    }
    balanceDraft=balancePreset;useDefaultZoom();
}
void Game::archiveBalance(const BalancePreset &preset) const {
    const auto path=balanceDirectory/"revisions"/(preset.revision()+".json");
    if(std::filesystem::exists(path)) {
        if(BalancePreset::load(path,preset.mechanicsFingerprint).revision()!=preset.revision())
            throw std::runtime_error("Saved balance revision does not match its contents");
    } else preset.save(path);
}
void Game::applyBalance(BalancePreset preset) {
    preset.validate();archiveBalance(preset); // No partial runtime update on validation/write failure.
    const bool zoomChanged=preset.defaultZoomPercent!=balancePreset.defaultZoomPercent;
    const bool resize=run&&(preset.roomSizeScale!=run->roomSizeScale||preset.roomMinHalfTiles!=run->roomMinHalfTiles||preset.roomMaxHalfTiles!=run->roomMaxHalfTiles||preset.routeLengthScale!=run->routeLengthScale);
    if(resize)run->resizeRooms(preset.roomSizeScale,preset.roomMinHalfTiles,preset.roomMaxHalfTiles,preset.routeLengthScale); // Constructs first; an invalid/unsafe edit leaves the expedition intact.
    if(!run){preset.save(balanceDirectory/"next.json");nextBalancePreset=preset;}
    balancePreset=std::move(preset);balanceDraft.playerSpeed=balancePreset.playerSpeed;
    balanceDraft.tearsPerSecond=balancePreset.tearsPerSecond;balanceDraft.shotSpeed=balancePreset.shotSpeed;
    balanceDraft.rangeTiles=balancePreset.rangeTiles;
    balanceDraft.defaultZoomPercent=balancePreset.defaultZoomPercent;balanceRestoreError_.clear();
    if(resize){resetPointerInput();snapCamera();++audioContext;audioCues.clear();}
    if(zoomChanged)useDefaultZoom();
    if(run) {
        run->player.attributes.speed=balancePreset.playerSpeed;
        // New shots resolve these base attributes with owned-item modifiers.
        // Leave existing projectile birth specs and the current cooldown intact.
        run->player.attributes.tearsPerSecond=balancePreset.tearsPerSecond;
        run->player.attributes.shotSpeed=balancePreset.shotSpeed;
        run->player.attributes.rangeTiles=balancePreset.rangeTiles;
        run->checkpointNeeded=true;checkpoint();
    }
    error.clear();balanceNotice="Applied. Walking uses this Speed on the next movement step.";
}
void Game::setPlayerSpeed(float speed) {
    auto candidate=balancePreset;candidate.playerSpeed=speed;applyBalance(std::move(candidate));
}
void Game::setShooting(float tears,float shotSpeed,float rangeTiles) {
    auto preset=balancePreset;preset.tearsPerSecond=tears;preset.shotSpeed=shotSpeed;preset.rangeTiles=rangeTiles;
    applyBalance(std::move(preset));
    balanceNotice="Shooting applied to new shots. Current firing wait and flying shots stay as they were.";
}
void Game::resetShooting() {
    setShooting(BalancePreset::ReferenceTears,BalancePreset::ReferenceShotSpeed,BalancePreset::ReferenceRange);
    balanceNotice="Shooting reset to the accepted base. Movement, zoom and map settings retained.";
}
void Game::useDefaultZoom() {
    cameraZoom_=cameraZoomTarget_=100.f/balancePreset.defaultZoomPercent;snapCamera();
}
void Game::setDefaultZoom(float percent) {
    auto preset=balancePreset;preset.defaultZoomPercent=percent;applyBalance(std::move(preset));useDefaultZoom();
    balanceNotice="Default zoom previewed. Export or Use next expedition to keep it.";
}
std::pair<int,int> Game::roomSizeRange() const {
    if(balanceDraft.roomMinHalfTiles)return {balanceDraft.roomMinHalfTiles,balanceDraft.roomMaxHalfTiles};
    const auto dimensions=run?run->expedition.dimensionsOnFloor(run->floor):
        ExpeditionPlan(0,false,WitnessAccount::None,expeditionPacing).dimensionsOnFloor(0);
    return dimensions.smallerRooms?std::pair{dimensions.minHalfTiles,dimensions.maxHalfTiles}:std::pair{6,10};
}
bool Game::hasPendingMapChanges() const {
    return balanceDraft.roomSizeScale!=balancePreset.roomSizeScale||
        balanceDraft.roomMinHalfTiles!=balancePreset.roomMinHalfTiles||
        balanceDraft.roomMaxHalfTiles!=balancePreset.roomMaxHalfTiles||
        balanceDraft.routeLengthScale!=balancePreset.routeLengthScale;
}
void Game::setRoomSizeRange(int minimum,int maximum) {
    auto preset=balanceDraft;preset.roomMinHalfTiles=minimum;preset.roomMaxHalfTiles=maximum;preset.validate();
    balanceDraft=std::move(preset);error.clear();balanceNotice="Map settings pending. Press APPLY MAP CHANGES when ready.";
}
void Game::setRoomSize(float scale) {
    auto preset=balanceDraft;preset.roomSizeScale=scale;preset.validate();
    balanceDraft=std::move(preset);error.clear();balanceNotice="Map settings pending. Press APPLY MAP CHANGES when ready.";
}
void Game::setRouteLength(float scale) {
    auto preset=balanceDraft;preset.routeLengthScale=scale;preset.validate();
    balanceDraft=std::move(preset);error.clear();balanceNotice="Map settings pending. Press APPLY MAP CHANGES when ready.";
}
void Game::applyMapChanges() {
    if(!hasPendingMapChanges()){balanceNotice="Map settings are already applied.";return;}
    auto preset=balanceDraft;preset.playerSpeed=balancePreset.playerSpeed;applyBalance(std::move(preset));
    balanceDraft=balancePreset;
    balanceNotice=run?"Map applied. Floor encounters/pickups reset; player, build and Speed retained.":
                      "Map settings saved for generation of the next expedition.";
}
void Game::resetBalance() {
    auto preset=balancePreset;preset.playerSpeed=1;applyBalance(std::move(preset));
    balanceNotice="Speed reset to 1.00. Existing movement calibration is unchanged.";
}
void Game::exportBalancePreset() {
    balanceDraft.save(std::filesystem::path(balanceFile));
    balanceNotice=hasPendingMapChanges()?"Exported selected settings. Current map still awaits APPLY MAP CHANGES.":"Exported player, shooting, zoom and map settings. Use for next expedition to remember them.";
    error.clear();
}
void Game::loadBalancePreset(const std::filesystem::path &path) {
    auto candidate=BalancePreset::load(path,defaultMechanics()->fingerprint());
    const auto filename=path.string();
    auto live=balancePreset;live.playerSpeed=candidate.playerSpeed;live.defaultZoomPercent=candidate.defaultZoomPercent;
    live.tearsPerSecond=candidate.tearsPerSecond;live.shotSpeed=candidate.shotSpeed;live.rangeTiles=candidate.rangeTiles;
    applyBalance(std::move(live));useDefaultZoom();
    balanceDraft=std::move(candidate);balanceFile=filename;
    balanceNotice=hasPendingMapChanges()?"Loaded. Player/shooting settings applied; map settings await APPLY MAP CHANGES.":
        "Loaded player/shooting settings. Map settings already match. Use next expedition to remember this preset.";
}
void Game::rememberBalancePreset() {
    archiveBalance(balanceDraft);
    balanceDraft.save(balanceDirectory/"next.json");
    nextBalancePreset=balanceDraft;
    balanceNotice=hasPendingMapChanges()?"Selected settings remembered for next expedition. Current map still awaits APPLY.":"Remembered for future expeditions and application restarts.";
    error.clear();
}
RunSummary Game::configuredSummary() const {
    auto summary=run->summary();
    summary.mechanicsFingerprint+="/balance-v5:"+balancePreset.revision();
    return summary;
}
void Game::startExpedition(std::unique_ptr<Simulation> candidate,bool retry) {
    if(!balanceRestoreError_.empty())throw std::runtime_error(balanceRestoreError_);
    const auto preset=retry?balancePreset:nextBalancePreset.value_or(BalancePreset{1,candidate->content->fingerprint()});
    preset.validate();archiveBalance(preset);
    candidate->tunePlayer(playerHealth,playerDamage);
    candidate->player.attributes.speed=preset.playerSpeed;
    candidate->player.attributes.tearsPerSecond=preset.tearsPerSecond;
    candidate->player.attributes.shotSpeed=preset.shotSpeed;
    candidate->player.attributes.rangeTiles=preset.rangeTiles;
    const RetrySetup setup{candidate->expedition.seed,candidate->arena.theme,visualSettings.canyonRiver,
                           candidate->surveyTutorial,candidate->expedition.account,candidate->expedition.pacing};
    campaign.begin(setup.seed,candidate->summary().expedition,setup.pacing);
    balancePreset=balanceDraft=preset;retrySetup_=setup;seedText=std::to_string(setup.seed);
    run=std::move(candidate);buildOpen=balanceOpen=balancePathEditing=false;
    run->checkpointNeeded=true;checkpoint();
    walkingToQuest_=false;++audioContext;audioCues.clear();
    missionMenu=walkingToMission=false;town.stop();screen=Screen::Expedition;
    deathTime=0;paused=false;accumulator=0;error.clear();resetArmed=false;
    useDefaultZoom();resetPointerInput();
    std::cout<<"BALANCE speed="<<balancePreset.playerSpeed<<" room_size="<<balancePreset.roomSizeScale<<" routes="<<balancePreset.routeLengthScale<<" zoom="<<balancePreset.defaultZoomPercent<<" tears="<<balancePreset.tearsPerSecond<<" shot_speed="<<balancePreset.shotSpeed<<" range="<<balancePreset.rangeTiles<<" revision="<<balancePreset.revision()
             <<" profile="<<(balancePreset.custom()?"custom":"reference-partial")<<'\n';
}
bool Game::canRetryExpedition() const {
    return retrySetup_&&((run&&run->dead)||(screen==Screen::Summary&&lastSummary.reason==EndReason::Death));
}
void Game::retryExpedition() {
    if(!canRetryExpedition())return;
    const auto setup=*retrySetup_;
    if(run)finish(EndReason::Death); // Resolve consequences once; never reset the campaign.
    auto candidate=std::make_unique<Simulation>(setup.seed,campaign.data().nextRunId,campaign.data().world,
        setup.theme,setup.river,setup.tutorial,setup.account,0,setup.pacing,defaultMechanics(),balancePreset.roomSizeScale,balancePreset.roomMinHalfTiles,balancePreset.roomMaxHalfTiles,balancePreset.routeLengthScale);
    startExpedition(std::move(candidate),true);
    balanceNotice="Retried the same expedition seed with the applied player, shooting, zoom and map settings.";
}
bool Game::updateBalanceInput() {
    if(!balanceOpen)return false;
    resetPointerInput();accumulator=0;
    if(!balancePathEditing)return false;
    if(IsKeyPressed(KEY_ESCAPE)) {
        balanceFile=balancePathBeforeEdit_;balancePathEditing=false;return true;
    }
    if(IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_KP_ENTER)) {balancePathEditing=false;return true;}
    const bool control=IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL);
    if(control&&IsKeyPressed(KEY_A))balanceFile.clear();
    if(control&&IsKeyPressed(KEY_C))SetClipboardText(balanceFile.c_str());
    if(control&&IsKeyPressed(KEY_V)) {
        if(const auto *clipboard=GetClipboardText()) {
            const std::string value=clipboard;
            if(value.size()<=1024&&value.find_first_of("\r\n") == std::string::npos)balanceFile=value;
        }
    }
    if((IsKeyPressed(KEY_BACKSPACE)||IsKeyPressedRepeat(KEY_BACKSPACE))&&!balanceFile.empty())balanceFile.pop_back();
    for(int c=GetCharPressed();c;c=GetCharPressed())
        if(!control&&c>=32&&c<127&&balanceFile.size()<1024)balanceFile+=char(c);
    return true;
}
} // namespace dw
