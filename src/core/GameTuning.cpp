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
            balanceNotice="Remembered preset loaded. Speed applies on expedition start.";
        }
    } catch(const std::exception &e) {
        balanceRestoreError_=std::string("Remembered preset could not load: ")+e.what();
        error=balanceRestoreError_;paused=true;
    }
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
    balancePreset=std::move(preset);balanceRestoreError_.clear();
    if(run) {
        run->player.attributes.speed=balancePreset.playerSpeed;
        run->checkpointNeeded=true;checkpoint();
    }
    error.clear();balanceNotice="Applied. Walking uses this Speed on the next movement step.";
}
void Game::setPlayerSpeed(float speed) {
    auto candidate=balancePreset;candidate.playerSpeed=speed;applyBalance(std::move(candidate));
}
void Game::resetBalance() {
    applyBalance(BalancePreset{1,defaultMechanics()->fingerprint()});
    balanceNotice="Speed reset to 1.00. Existing movement calibration is unchanged.";
}
void Game::exportBalancePreset() {
    balancePreset.save(std::filesystem::path(balanceFile));
    balanceNotice="Exported Speed preset. Use for next expedition to remember it.";
    error.clear();
}
void Game::loadBalancePreset(const std::filesystem::path &path) {
    auto candidate=BalancePreset::load(path,defaultMechanics()->fingerprint());
    const auto filename=path.string();applyBalance(std::move(candidate));balanceFile=filename;
    balanceNotice="Loaded and applied. Use for next expedition to remember it.";
}
void Game::rememberBalancePreset() {
    archiveBalance(balancePreset);
    balancePreset.save(balanceDirectory/"next.json");
    nextBalancePreset=balancePreset;
    balanceNotice="Remembered for future expeditions and application restarts.";
    error.clear();
}
RunSummary Game::configuredSummary() const {
    auto summary=run->summary();
    summary.mechanicsFingerprint+="/balance-v1:"+balancePreset.revision();
    return summary;
}
void Game::startExpedition(std::unique_ptr<Simulation> candidate,bool retry) {
    if(!balanceRestoreError_.empty())throw std::runtime_error(balanceRestoreError_);
    const auto preset=retry?balancePreset:nextBalancePreset.value_or(BalancePreset{1,candidate->content->fingerprint()});
    preset.validate();archiveBalance(preset);
    candidate->tunePlayer(playerHealth,playerDamage);
    candidate->player.attributes.speed=preset.playerSpeed;
    const RetrySetup setup{candidate->expedition.seed,candidate->arena.theme,visualSettings.canyonRiver,
                           candidate->surveyTutorial,candidate->expedition.account,candidate->expedition.pacing};
    campaign.begin(setup.seed,candidate->summary().expedition,setup.pacing);
    balancePreset=preset;retrySetup_=setup;seedText=std::to_string(setup.seed);
    run=std::move(candidate);buildOpen=balanceOpen=balancePathEditing=false;
    run->checkpointNeeded=true;checkpoint();
    walkingToQuest_=false;++audioContext;audioCues.clear();
    missionMenu=walkingToMission=false;town.stop();screen=Screen::Expedition;
    deathTime=0;paused=false;accumulator=0;error.clear();resetArmed=false;
    cameraZoom_=cameraZoomTarget_;snapCamera();resetPointerInput();
    std::cout<<"BALANCE speed="<<balancePreset.playerSpeed<<" revision="<<balancePreset.revision()
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
        setup.theme,setup.river,setup.tutorial,setup.account,0,setup.pacing);
    startExpedition(std::move(candidate),true);
    balanceNotice="Retried the same expedition seed with the current Speed preset.";
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
