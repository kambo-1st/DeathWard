#include "core/Game.hpp"
#include "world/ShopCartGeometry.hpp"
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
            balanceNotice="Remembered player, enemy, view and map settings loaded for expedition start.";
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
    const bool resize=run&&(preset.roomProps.layouts!=run->roomProps.layouts||preset.bossRewardItem!=run->bossRewardItem||preset.seededBosses!=run->seededBosses||preset.duke.enabled!=run->dukeTuning.enabled||preset.monstro.enabled!=run->monstroTuning.enabled||preset.roomSizeScale!=run->roomSizeScale||preset.roomMinHalfTiles!=run->roomMinHalfTiles||preset.roomMaxHalfTiles!=run->roomMaxHalfTiles||preset.routeLengthScale!=run->routeLengthScale||preset.sourceCombatRoom!=run->sourceCombatRoom||preset.roomHeartLayouts!=run->roomHeartLayouts||preset.sourceRoomLocks!=run->sourceRoomLocks||preset.sourceTreasureUpgrade!=run->sourceTreasureUpgrade||preset.sourceShopHeart!=run->sourceShopHeart||preset.sourceShopKey!=run->sourceShopKey||preset.sourceShopVariation!=run->sourceShopVariation||preset.shopCollectiblePool!=run->shopCollectiblePool||preset.treasureCollectiblePool!=run->treasureCollectiblePool);
    if(resize)run->resizeRooms(preset.roomSizeScale,preset.roomMinHalfTiles,preset.roomMaxHalfTiles,preset.routeLengthScale,preset.sourceCombatRoom,preset.roomHeartLayouts,preset.sourceRoomLocks,preset.sourceTreasureUpgrade,preset.sourceShopHeart,preset.sourceShopKey,preset.sourceShopVariation,preset.shopCollectiblePool,preset.treasureCollectiblePool,preset.monstro,preset.duke,preset.seededBosses,preset.bossRewardItem,preset.roomProps); // Constructs first; an invalid/unsafe edit leaves the expedition intact.
    if(!run){preset.save(balanceDirectory/"next.json");nextBalancePreset=preset;}
    balancePreset=std::move(preset);balanceDraft.playerSpeed=balancePreset.playerSpeed;
    balanceDraft.tearsPerSecond=balancePreset.tearsPerSecond;balanceDraft.shotSpeed=balancePreset.shotSpeed;
    balanceDraft.rangeTiles=balancePreset.rangeTiles;
    balanceDraft.roomProps.fireDamageHalfHearts=balancePreset.roomProps.fireDamageHalfHearts;balanceDraft.roomProps.rewards=balancePreset.roomProps.rewards;
    balanceDraft.screw=balancePreset.screw;balanceDraft.fullFly=balancePreset.fullFly;balanceDraft.roundWorm=balancePreset.roundWorm;
    balanceDraft.inventoryBombs=balancePreset.inventoryBombs;
    balanceDraft.keyedDoorCost=balancePreset.keyedDoorCost;
    balanceDraft.duke.health=balancePreset.duke.health;balanceDraft.duke.movement=balancePreset.duke.movement;balanceDraft.duke.flySpeed=balancePreset.duke.flySpeed;
    balanceDraft.monstro.health=balancePreset.monstro.health;balanceDraft.monstro.movement=balancePreset.monstro.movement;balanceDraft.monstro.shotSpeed=balancePreset.monstro.shotSpeed;
    balanceDraft.trinkets=balancePreset.trinkets;balanceDraft.bookOfShadows=balancePreset.bookOfShadows;balanceDraft.yumHeart=balancePreset.yumHeart;balanceDraft.haloOfFlies=balancePreset.haloOfFlies;balanceDraft.brotherBobby=balancePreset.brotherBobby;balanceDraft.cricketHeadStrength=balancePreset.cricketHeadStrength;balanceDraft.sadOnionStrength=balancePreset.sadOnionStrength;balanceDraft.shopHeartPrice=balancePreset.shopHeartPrice;balanceDraft.shopKeyPrice=balancePreset.shopKeyPrice;balanceDraft.shopBombPrice=balancePreset.shopBombPrice;balanceDraft.shopSoulHeartPrice=balancePreset.shopSoulHeartPrice;balanceDraft.shopUpgradePrice=balancePreset.shopUpgradePrice;balanceDraft.steamSaleDiscounts=balancePreset.steamSaleDiscounts;
    balanceDraft.redHeartAppearanceSpeed=balancePreset.redHeartAppearanceSpeed;
    balanceDraft.bombClearRewards=balancePreset.bombClearRewards;balanceDraft.keyClearRewards=balancePreset.keyClearRewards;balanceDraft.chestClearRewards=balancePreset.chestClearRewards;balanceDraft.coinClearRewards=balancePreset.coinClearRewards;balanceDraft.redHeartClearRewards=balancePreset.redHeartClearRewards;balanceDraft.playerLuck=balancePreset.playerLuck;
    balanceDraft.playerDamage=balancePreset.playerDamage;balanceDraft.regularHealthMultiplier=balancePreset.regularHealthMultiplier;
    balanceDraft.gaperMovementMultiplier=balancePreset.gaperMovementMultiplier;
    balanceDraft.frowningMovementMultiplier=balancePreset.frowningMovementMultiplier;
    balanceDraft.momsEyeChanceMultiplier=balancePreset.momsEyeChanceMultiplier;
    balanceDraft.attackFlyMovementMultiplier=balancePreset.attackFlyMovementMultiplier;
    balanceDraft.spiderMovementMultiplier=balancePreset.spiderMovementMultiplier;
    balanceDraft.pooterMovementMultiplier=balancePreset.pooterMovementMultiplier;
    balanceDraft.pooterShotSpeedMultiplier=balancePreset.pooterShotSpeedMultiplier;
    balanceDraft.pooterAttackIntervalMultiplier=balancePreset.pooterAttackIntervalMultiplier;
    balanceDraft.defaultZoomPercent=balancePreset.defaultZoomPercent;balanceRestoreError_.clear();
    if(resize){resetPointerInput();snapCamera();++audioContext;audioCues.clear();}
    if(zoomChanged)useDefaultZoom();
    if(run) {
        run->applyCombatBalance(balancePreset.playerDamage,balancePreset.regularHealthMultiplier);
        run->roomProps=balancePreset.roomProps;run->screw=balancePreset.screw;run->fullFlyTuning=balancePreset.fullFly;run->roundWormTuning=balancePreset.roundWorm;
        run->inventoryBombTuning=balancePreset.inventoryBombs;
        run->keyedDoorCost=balancePreset.keyedDoorCost;
        run->applyDukeTuning(balancePreset.duke);
        run->applyMonstroTuning(balancePreset.monstro);
        run->trinkets=balancePreset.trinkets;run->bookOfShadows=balancePreset.bookOfShadows;run->yumHeart=balancePreset.yumHeart;run->haloOfFlies=balancePreset.haloOfFlies;run->brotherBobby=balancePreset.brotherBobby;run->cricketHeadStrength=balancePreset.cricketHeadStrength;run->sadOnionStrength=balancePreset.sadOnionStrength;run->shopHeartPrice=balancePreset.shopHeartPrice;run->shopKeyPrice=balancePreset.shopKeyPrice;run->shopBombPrice=balancePreset.shopBombPrice;run->shopSoulHeartPrice=balancePreset.shopSoulHeartPrice;run->shopUpgradePrice=balancePreset.shopUpgradePrice;run->steamSaleDiscounts=balancePreset.steamSaleDiscounts;
        playerDamage=run->player.shotDamage;
        run->redHeartAppearanceSpeed=balancePreset.redHeartAppearanceSpeed;
        run->bombClearRewards=balancePreset.bombClearRewards;run->keyClearRewards=balancePreset.keyClearRewards;run->chestClearRewards=balancePreset.chestClearRewards;run->coinClearRewards=balancePreset.coinClearRewards;run->redHeartClearRewards=balancePreset.redHeartClearRewards;run->player.attributes.luck=balancePreset.playerLuck;
        run->player.attributes.speed=balancePreset.playerSpeed;
        // New shots resolve these base attributes with owned-item modifiers.
        // Leave existing projectile birth specs and the current cooldown intact.
        run->player.attributes.tearsPerSecond=balancePreset.tearsPerSecond;
        run->player.attributes.shotSpeed=balancePreset.shotSpeed;
        run->player.attributes.rangeTiles=balancePreset.rangeTiles;
        run->gaperMovementMultiplier=balancePreset.gaperMovementMultiplier;
        run->frowningMovementMultiplier=balancePreset.frowningMovementMultiplier;
        run->momsEyeChanceMultiplier=balancePreset.momsEyeChanceMultiplier;
        run->attackFlyMovementMultiplier=balancePreset.attackFlyMovementMultiplier;
        run->spiderMovementMultiplier=balancePreset.spiderMovementMultiplier;
        run->pooterTuning=PooterTuning{balancePreset.pooterMovementMultiplier,balancePreset.pooterShotSpeedMultiplier,balancePreset.pooterAttackIntervalMultiplier};
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
void Game::setGaperMovement(float multiplier) {
    auto preset=balancePreset;preset.gaperMovementMultiplier=multiplier;applyBalance(std::move(preset));
    balanceNotice="Gaper movement applied at its next steering tick; existing momentum settles naturally.";
}
void Game::setSpiderMovement(float multiplier) {
    auto preset=balancePreset;preset.spiderMovementMultiplier=multiplier;applyBalance(std::move(preset));
    balanceNotice="Spider drive applies at its next steering tick; current burst target and pause timing are retained.";
}
void Game::setCombatBalance(float damage,float regularHealth) {
    auto preset=balancePreset;preset.playerDamage=damage;preset.regularHealthMultiplier=regularHealth;applyBalance(std::move(preset));
    balanceNotice="Damage: next attacks. Regular HP: applied proportionally to living enemies and future spawns. Boss HP retained.";
}
void Game::setInventoryBombs(InventoryBombTuning tuning) {
    auto preset=balancePreset;preset.inventoryBombs=tuning;applyBalance(std::move(preset));
    balanceNotice="Dynamite applied to new charges. Lit charges keep their fuse, radius and damage. Export or Use next expedition to keep edits.";
}
void Game::setPooterTuning(float movement,float shotSpeed,float interval) {
    auto preset=balancePreset;preset.pooterMovementMultiplier=movement;preset.pooterShotSpeedMultiplier=shotSpeed;
    preset.pooterAttackIntervalMultiplier=interval;applyBalance(std::move(preset));
    balanceNotice="Pooter movement: next steering tick. Shot speed/delay: next attack; current attacks and flying shots retained.";
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
        balanceDraft.roomProps.layouts!=balancePreset.roomProps.layouts||balanceDraft.bossRewardItem!=balancePreset.bossRewardItem||balanceDraft.seededBosses!=balancePreset.seededBosses||balanceDraft.duke.enabled!=balancePreset.duke.enabled||balanceDraft.monstro.enabled!=balancePreset.monstro.enabled||balanceDraft.routeLengthScale!=balancePreset.routeLengthScale||balanceDraft.sourceCombatRoom!=balancePreset.sourceCombatRoom||balanceDraft.roomHeartLayouts!=balancePreset.roomHeartLayouts||balanceDraft.sourceRoomLocks!=balancePreset.sourceRoomLocks||balanceDraft.sourceTreasureUpgrade!=balancePreset.sourceTreasureUpgrade||balanceDraft.sourceShopHeart!=balancePreset.sourceShopHeart||balanceDraft.sourceShopKey!=balancePreset.sourceShopKey||balanceDraft.sourceShopVariation!=balancePreset.sourceShopVariation||balanceDraft.shopCollectiblePool!=balancePreset.shopCollectiblePool||balanceDraft.treasureCollectiblePool!=balancePreset.treasureCollectiblePool;
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
void Game::setRedHeartAppearanceSpeed(float speed) {
    auto preset=balancePreset;preset.redHeartAppearanceSpeed=speed;applyBalance(std::move(preset));
    balanceNotice="Appearance speed applies to newly spawned red hearts. Existing hearts keep their birth timing.";
}
void Game::setRedHeartRewards(bool enabled,float luck) {
    auto preset=balancePreset;preset.redHeartClearRewards=enabled;preset.playerLuck=luck;applyBalance(std::move(preset));
    balanceNotice="Reward settings apply to future first clears. Existing rolls, pickups and cleared rooms stay as they were.";
}
void Game::setRoomHeartLayouts(int mode) {
    auto candidate=balanceDraft;candidate.roomHeartLayouts=mode;candidate.validate();balanceDraft=std::move(candidate);error.clear();
    balanceNotice="Room hearts pending. APPLY MAP CHANGES resets current-floor encounters and pickups; player/build retained.";
}
void Game::setSourceCombatRoom(bool enabled) {
    balanceDraft.sourceCombatRoom=enabled;error.clear();
    balanceNotice="Opening-floor formation pending. Press APPLY MAP CHANGES; current-floor encounters will reset.";
}
void Game::applyMapChanges() {
    if(!hasPendingMapChanges()){balanceNotice="Map settings are already applied.";return;}
    auto preset=balanceDraft;preset.playerSpeed=balancePreset.playerSpeed;applyBalance(std::move(preset));
    balanceDraft=balancePreset;
    balanceNotice=run?(reviewPowerups?"Map applied. Review offerings ended; owned build retained. Retry restarts the review.":"Map applied. Floor encounters/pickups reset; player, build and Speed retained."):
                      "Map settings saved for generation of the next expedition.";
}
void Game::resetBalance() {
    auto preset=balancePreset;preset.playerSpeed=1;applyBalance(std::move(preset));
    balanceNotice="Speed reset to 1.00. Existing movement calibration is unchanged.";
}
void Game::exportBalancePreset() {
    balanceDraft.save(std::filesystem::path(balanceFile));
    balanceNotice=hasPendingMapChanges()?"Exported selected settings. Current map still awaits APPLY MAP CHANGES.":"Exported player, enemy, view and map settings. Use next expedition to remember them.";
    error.clear();
}
void Game::loadBalancePreset(const std::filesystem::path &path) {
    auto candidate=BalancePreset::load(path,defaultMechanics()->fingerprint());
    const auto filename=path.string();
    auto live=balancePreset;live.playerSpeed=candidate.playerSpeed;live.defaultZoomPercent=candidate.defaultZoomPercent;
    live.roomProps=candidate.roomProps;live.roomProps.layouts=balancePreset.roomProps.layouts;
    live.screw=candidate.screw;live.fullFly=candidate.fullFly;live.roundWorm=candidate.roundWorm;
    live.duke=candidate.duke;live.duke.enabled=balancePreset.duke.enabled;
    live.monstro=candidate.monstro;live.monstro.enabled=balancePreset.monstro.enabled;
    live.tearsPerSecond=candidate.tearsPerSecond;live.shotSpeed=candidate.shotSpeed;live.rangeTiles=candidate.rangeTiles;live.inventoryBombs=candidate.inventoryBombs;live.keyedDoorCost=candidate.keyedDoorCost;live.trinkets=candidate.trinkets;live.bookOfShadows=candidate.bookOfShadows;live.yumHeart=candidate.yumHeart;live.haloOfFlies=candidate.haloOfFlies;live.brotherBobby=candidate.brotherBobby;live.cricketHeadStrength=candidate.cricketHeadStrength;live.sadOnionStrength=candidate.sadOnionStrength;live.shopHeartPrice=candidate.shopHeartPrice;live.shopKeyPrice=candidate.shopKeyPrice;live.shopBombPrice=candidate.shopBombPrice;live.shopSoulHeartPrice=candidate.shopSoulHeartPrice;live.shopUpgradePrice=candidate.shopUpgradePrice;live.steamSaleDiscounts=candidate.steamSaleDiscounts;
    live.redHeartAppearanceSpeed=candidate.redHeartAppearanceSpeed;live.bombClearRewards=candidate.bombClearRewards;live.keyClearRewards=candidate.keyClearRewards;live.chestClearRewards=candidate.chestClearRewards;live.coinClearRewards=candidate.coinClearRewards;live.redHeartClearRewards=candidate.redHeartClearRewards;live.playerLuck=candidate.playerLuck;
    live.playerDamage=candidate.playerDamage;live.regularHealthMultiplier=candidate.regularHealthMultiplier;
    live.gaperMovementMultiplier=candidate.gaperMovementMultiplier;
    live.frowningMovementMultiplier=candidate.frowningMovementMultiplier;
    live.momsEyeChanceMultiplier=candidate.momsEyeChanceMultiplier;
    live.attackFlyMovementMultiplier=candidate.attackFlyMovementMultiplier;
    live.spiderMovementMultiplier=candidate.spiderMovementMultiplier;
    live.pooterMovementMultiplier=candidate.pooterMovementMultiplier;
    live.pooterShotSpeedMultiplier=candidate.pooterShotSpeedMultiplier;
    live.pooterAttackIntervalMultiplier=candidate.pooterAttackIntervalMultiplier;
    applyBalance(std::move(live));useDefaultZoom();
    balanceDraft=std::move(candidate);balanceFile=filename;
    balanceNotice=hasPendingMapChanges()?"Loaded. Player/enemy/view applied; map settings await APPLY MAP CHANGES.":
        "Loaded player/enemy/view settings. Map already matches. Use next expedition to remember.";
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
    if(reviewPowerups&&summary.startingContext.find("PW-C01")==std::string::npos)summary.startingContext+=" / PW-C01 CATEGORY REVIEW: staged test offerings and direct travel";
    if(reviewActives)summary.startingContext+=" / PW-A02 ACTIVE REVIEW: two staged test offerings";
    if(reviewTrinkets)summary.startingContext+=" / PW-T02 TRINKET REVIEW: two staged test pickups";
    summary.mechanicsFingerprint+="/balance-v13:"+balancePreset.revision();
    return summary;
}
void Game::startExpedition(std::unique_ptr<Simulation> candidate,bool retry) {
    if(!balanceRestoreError_.empty())throw std::runtime_error(balanceRestoreError_);
    const auto preset=retry?balancePreset:nextBalancePreset.value_or(BalancePreset{1,candidate->content->fingerprint()});
    preset.validate();archiveBalance(preset);
    candidate->tunePlayer(playerHealth,playerDamage);
    candidate->applyCombatBalance(preset.playerDamage,preset.regularHealthMultiplier);
    candidate->roomProps=preset.roomProps;candidate->screw=preset.screw;candidate->fullFlyTuning=preset.fullFly;candidate->roundWormTuning=preset.roundWorm;
    candidate->inventoryBombTuning=preset.inventoryBombs;
    candidate->keyedDoorCost=preset.keyedDoorCost;
    candidate->applyDukeTuning(preset.duke);
    candidate->applyMonstroTuning(preset.monstro);
    candidate->trinkets=preset.trinkets;candidate->bookOfShadows=preset.bookOfShadows;candidate->yumHeart=preset.yumHeart;candidate->haloOfFlies=preset.haloOfFlies;candidate->brotherBobby=preset.brotherBobby;candidate->cricketHeadStrength=preset.cricketHeadStrength;candidate->sadOnionStrength=preset.sadOnionStrength;candidate->shopHeartPrice=preset.shopHeartPrice;candidate->shopKeyPrice=preset.shopKeyPrice;candidate->shopBombPrice=preset.shopBombPrice;candidate->shopSoulHeartPrice=preset.shopSoulHeartPrice;candidate->shopUpgradePrice=preset.shopUpgradePrice;candidate->steamSaleDiscounts=preset.steamSaleDiscounts;
    playerDamage=candidate->player.shotDamage;
    candidate->redHeartAppearanceSpeed=preset.redHeartAppearanceSpeed;
    candidate->bombClearRewards=preset.bombClearRewards;candidate->keyClearRewards=preset.keyClearRewards;candidate->chestClearRewards=preset.chestClearRewards;candidate->coinClearRewards=preset.coinClearRewards;candidate->redHeartClearRewards=preset.redHeartClearRewards;candidate->player.attributes.luck=preset.playerLuck;
    candidate->player.attributes.speed=preset.playerSpeed;
    candidate->player.attributes.tearsPerSecond=preset.tearsPerSecond;
    candidate->player.attributes.shotSpeed=preset.shotSpeed;
    candidate->player.attributes.rangeTiles=preset.rangeTiles;
    candidate->gaperMovementMultiplier=preset.gaperMovementMultiplier;
    candidate->frowningMovementMultiplier=preset.frowningMovementMultiplier;
    candidate->momsEyeChanceMultiplier=preset.momsEyeChanceMultiplier;
    candidate->attackFlyMovementMultiplier=preset.attackFlyMovementMultiplier;
    candidate->spiderMovementMultiplier=preset.spiderMovementMultiplier;
    candidate->pooterTuning=PooterTuning{preset.pooterMovementMultiplier,preset.pooterShotSpeedMultiplier,preset.pooterAttackIntervalMultiplier};
    if(reviewActives&&!candidate->beginActiveReview())throw std::runtime_error("Active review needs an empty build and reachable treasure room");
    if(reviewTrinkets&&!candidate->beginTrinketReview())throw std::runtime_error("Trinket review needs an empty build and reachable opening floor");
    if(reviewPowerups&&!candidate->beginPowerupReview())throw std::runtime_error("Category review needs opening-floor source treasure, an empty build and reachable floor");
    if(reviewSourceRoomTemplate&&!candidate->enterSourceRoomReview(*reviewSourceRoomTemplate)) {
        if(!retry)throw std::runtime_error("Source room "+std::to_string(*reviewSourceRoomTemplate)+" is absent from this generated floor. Use the recorded review seed and enable SOURCE LAYOUTS or SOURCE COMBAT ROOM.");
        candidate->announce("ROOM REVIEW / Requested template is absent with these map settings; starting at the entrance.",8);
    }
    if(reviewRoomIndex) {
        if(*reviewRoomIndex>=candidate->arena.roomCount()||*reviewRoomIndex<0) {
            if(!retry)throw std::runtime_error("Requested review room is absent from this generated floor");
            candidate->announce("ROOM REVIEW / Requested room is absent; starting at the entrance.",8);
        } else {
            const auto &site=candidate->arena.rooms[size_t(*reviewRoomIndex)];
            candidate->player.position=site.kind==RoomKind::Power
                ?add(site.center,mul(unit(sub(site.entry,site.center)),3.f)):site.entry;
            candidate->enterRoom(*reviewRoomIndex);
            if(candidate->hasSourceBoss(*reviewRoomIndex)) {
                const auto anchor=candidate->arena.rooms[size_t(*reviewRoomIndex)].bossSpawn;
                for(int n=0;n<16;++n) {
                    auto at=add(anchor,rotateY({6,0,0},n*Pi/8));at.y=.85f;
                    if(candidate->arena.roomAt(at)==*reviewRoomIndex&&!candidate->arena.blocked(at,.55f)&&candidate->arena.clear(at,anchor,.48f)) {
                        candidate->player.position=at;break;
                    }
                }
            }
            candidate->announce("ROOM REVIEW / Room "+std::to_string(*reviewRoomIndex+1),6);
        }
    }
    if(reviewShopPurchase||reviewShopKeyPurchase||reviewShopStock) {
        const int shop=candidate->arena.shopRoom;
        if(!candidate->hasSourceShop(shop)||(reviewShopKeyPurchase&&!candidate->shopKeyOffered())||(reviewShopPurchase&&!candidate->shopHeartOffered())||(reviewShopStock&&!candidate->shopVariationActive()))throw std::runtime_error("Shop review requires the requested opening-floor stock; use its recorded seed and stock settings");
        candidate->player.position=shopCartGeometry::reviewStart(candidate->arena.rooms[size_t(shop)].center);
        candidate->player.hp=4;
        const uint64_t funds=reviewShopStock?20:reviewShopKeyPurchase?8:3;
        if(reviewShopKeyPurchase||reviewShopStock)candidate->keys=0;
        if(candidate->money()<funds)candidate->moneyCollected+=funds-candidate->money();
        candidate->enterRoom(shop);
        candidate->announce(reviewShopStock?(candidate->shopUpgradeItem==250?"STOCK REVIEW / BOGO BOMBS / 20 TEST COINS":"STOCK REVIEW / STEAM SALE / 20 TEST COINS"):reviewShopKeyPurchase?"SHOP REVIEW / KEY + HEART / AT LEAST 8 COINS":"SHOP REVIEW / 2 RED HEARTS / AT LEAST 3 COINS",8);
    }
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
    std::cout<<"BALANCE duke="<<balancePreset.duke.enabled<<" duke_hp="<<balancePreset.duke.health<<" duke_movement="<<balancePreset.duke.movement<<" duke_flies="<<balancePreset.duke.flySpeed<<" monstro="<<balancePreset.monstro.enabled<<" boss_policy="<<(balancePreset.seededBosses?"seeded":"fixed")<<" opening_boss="<<openingBossType(run->expedition.floorSeed(0),balancePreset.seededBosses,balancePreset.monstro.enabled,balancePreset.duke.enabled)<<" boss_hp="<<balancePreset.monstro.health<<" boss_movement="<<balancePreset.monstro.movement<<" boss_shots="<<balancePreset.monstro.shotSpeed<<" speed="<<balancePreset.playerSpeed<<" room_size="<<balancePreset.roomSizeScale<<" routes="<<balancePreset.routeLengthScale<<" zoom="<<balancePreset.defaultZoomPercent<<" tears="<<balancePreset.tearsPerSecond<<" shot_speed="<<balancePreset.shotSpeed<<" range="<<balancePreset.rangeTiles<<" moms_eye_chance="<<balancePreset.momsEyeChanceMultiplier<<" attack_fly_movement="<<balancePreset.attackFlyMovementMultiplier<<" frowning_movement="<<balancePreset.frowningMovementMultiplier<<" gaper_movement="<<balancePreset.gaperMovementMultiplier<<" spider_movement="<<balancePreset.spiderMovementMultiplier<<" pooter_movement="<<balancePreset.pooterMovementMultiplier<<" pooter_shot="<<balancePreset.pooterShotSpeedMultiplier<<" pooter_delay="<<balancePreset.pooterAttackIntervalMultiplier<<" damage="<<balancePreset.playerDamage<<" regular_hp="<<balancePreset.regularHealthMultiplier<<" bomb_fuse="<<balancePreset.inventoryBombs.fuseMultiplier<<" bomb_radius="<<balancePreset.inventoryBombs.radiusMultiplier<<" bomb_damage="<<balancePreset.inventoryBombs.damage<<" bomb_self="<<balancePreset.inventoryBombs.selfDamageHalfHearts<<" treasure_upgrade="<<balancePreset.sourceTreasureUpgrade<<" treasure_pool="<<balancePreset.treasureCollectiblePool<<" whip_strength="<<balancePreset.trinkets.whipStrength<<" cancer_strength="<<balancePreset.trinkets.cancerStrength<<" trinket_rewards="<<balancePreset.trinkets.clearRewards<<" trinket_key="<<balancePreset.trinkets.keyName()<<" book_duration="<<balancePreset.bookOfShadows.duration<<" book_recharge="<<balancePreset.bookOfShadows.recharge<<" yum_healing="<<balancePreset.yumHeart.healing<<" yum_recharge="<<balancePreset.yumHeart.recharge<<" active_key="<<balancePreset.yumHeart.keyName()<<" halo_orbit_speed="<<balancePreset.haloOfFlies.orbitSpeed<<" halo_orbit_radius="<<balancePreset.haloOfFlies.orbitRadius<<" halo_contact_radius="<<balancePreset.haloOfFlies.contactRadius<<" bobby_movement="<<balancePreset.brotherBobby.movement<<" bobby_interval="<<balancePreset.brotherBobby.interval<<" bobby_damage="<<balancePreset.brotherBobby.damage<<" bobby_shot_speed="<<balancePreset.brotherBobby.shotSpeed<<" cricket_strength="<<balancePreset.cricketHeadStrength<<" onion_strength="<<balancePreset.sadOnionStrength<<" shop_collectible_pool="<<balancePreset.shopCollectiblePool<<" shop_stock="<<balancePreset.sourceShopVariation<<" shop_upgrade_price="<<balancePreset.shopUpgradePrice<<" steam_sale="<<balancePreset.steamSaleDiscounts<<" shop_heart="<<balancePreset.sourceShopHeart<<" shop_key="<<balancePreset.sourceShopKey<<" shop_soul_heart_price="<<balancePreset.shopSoulHeartPrice<<" shop_bomb_price="<<balancePreset.shopBombPrice<<" shop_key_price="<<balancePreset.shopKeyPrice<<" shop_heart_price="<<balancePreset.shopHeartPrice<<" room_locks="<<balancePreset.sourceRoomLocks<<" key_cost="<<balancePreset.keyedDoorCost<<" rock_shielding="<<balancePreset.inventoryBombs.rocksBlockBlast<<" bomb_rewards="<<balancePreset.bombClearRewards<<" key_rewards="<<balancePreset.keyClearRewards<<" chest_rewards="<<balancePreset.chestClearRewards<<" coin_rewards="<<balancePreset.coinClearRewards<<" red_heart_rewards="<<balancePreset.redHeartClearRewards<<" heart_appearance="<<balancePreset.redHeartAppearanceSpeed<<" luck="<<balancePreset.playerLuck<<" room_hearts="<<balancePreset.roomHeartLayouts<<" source_room="<<balancePreset.sourceCombatRoom<<" boss_reward="<<balancePreset.bossRewardItem<<" screw_tears="<<balancePreset.screw.tearsStrength<<" round_worm_cycle="<<balancePreset.roundWorm.cycleSpeed<<" round_worm_shots="<<balancePreset.roundWorm.shotSpeed<<" full_fly_movement="<<balancePreset.fullFly.movement<<" full_fly_shots="<<balancePreset.fullFly.shotSpeed<<" screw_shots="<<balancePreset.screw.shotSpeedStrength<<" revision="<<balancePreset.revision()
             <<" profile="<<(balancePreset.custom()?"custom":"reference-partial")<<'\n';
    if(reviewTrinkets)std::cout<<"TRINKET_REVIEW room="<<run->room+1<<" pickups="<<run->trinketPickups.size()<<" owned="<<run->items.size()<<" held="<<bool(run->heldTrinket)<<" hp="<<run->player.hp<<" god="<<run->godMode<<'\n';
    if(reviewPowerups)std::cout<<"CATEGORY_REVIEW room="<<run->room+1<<" staged_offerings=1,4,8,45 trinket=39 owned="<<run->items.size()<<" hp="<<run->player.hp<<" god="<<run->godMode<<'\n';
    if(reviewRoomIndex)std::cout<<"ROOM_REVIEW room="<<run->room+1<<" hp="<<run->player.hp<<" god="<<run->godMode<<'\n';
    if(reviewShopStock)std::cout<<"SHOP_STOCK_REVIEW room="<<run->room+1<<" upgrade_item="<<run->shopUpgradeItem<<" upgrade_slot="<<run->shopUpgradeSlot<<" key_slot="<<run->shopKeySlot<<" bomb_slot="<<run->shopBombSlot<<" heart_kind="<<(run->shopHeartKind==HeartKind::Soul?"soul":"red")<<" heart_slot="<<run->shopHeartSlot<<" sale_slot="<<run->shopDiscountSlot<<" coins="<<run->money()<<" price="<<run->shopPrice(run->shopUpgradePrice,run->shopUpgradeSlot)<<" god="<<run->godMode<<'\n';
    if(reviewShopKeyPurchase)std::cout<<"SHOP_KEY_REVIEW room="<<run->room+1<<" keys="<<run->keys<<" coins="<<run->money()<<" key_price="<<run->shopKeyPrice<<" heart_price="<<run->shopHeartPrice<<" god="<<run->godMode<<'\n';
    if(reviewShopPurchase)std::cout<<"SHOP_REVIEW room="<<run->room+1<<" hp="<<run->player.hp<<" coins="<<run->money()<<" price="<<run->shopHeartPrice<<" god="<<run->godMode<<'\n';
    if(reviewSourceRoomTemplate) {
        const auto &layout=run->arena.rooms[size_t(run->room)];
        std::cout<<"ROOM_REVIEW requested="<<*reviewSourceRoomTemplate<<" room="<<run->room+1
                 <<" template="<<(layout.sourceTreasureTemplate>=0?layout.sourceTreasureTemplate:layout.sourceHeartTemplate>=0?layout.sourceHeartTemplate:layout.sourceCombatTemplate)
                 <<" selection_seed="<<layout.sourceRoomSelectionSeed<<" spawn_seed="<<layout.sourceRoomSpawnSeed
                 <<" chest_slots="<<layout.chestSpawns.size()<<" chests="<<run->chests.size()
                 <<" bomb_slots="<<layout.bombSpawns.size()<<" layout_bombs="<<std::count_if(run->bombPickups.begin(),run->bombPickups.end(),[&](const auto &bomb){return bomb.placedInLayout&&bomb.room==run->room;})
                 <<" key_slots="<<layout.keySpawns.size()<<" layout_keys="<<std::count_if(run->keyPickups.begin(),run->keyPickups.end(),[&](const auto &key){return key.placedInLayout&&key.room==run->room;})
                 <<" coin_slots="<<layout.coinSpawns.size()<<" layout_coins="<<std::count_if(run->moneyPickups.begin(),run->moneyPickups.end(),[&](const auto &coin){return coin.placedInLayout&&coin.room==run->room;})
                 <<" hp="<<run->player.hp<<" god="<<run->godMode<<'\n';
    }
}
bool Game::canRetryExpedition() const {
    return retrySetup_&&((run&&run->dead)||(screen==Screen::Summary&&lastSummary.reason==EndReason::Death));
}
void Game::retryExpedition() {
    if(!canRetryExpedition())return;
    const auto setup=*retrySetup_;
    if(run)finish(EndReason::Death); // Resolve consequences once; never reset the campaign.
    auto candidate=std::make_unique<Simulation>(setup.seed,campaign.data().nextRunId,campaign.data().world,
        setup.theme,setup.river,setup.tutorial,setup.account,0,setup.pacing,defaultMechanics(),balancePreset.roomSizeScale,balancePreset.roomMinHalfTiles,balancePreset.roomMaxHalfTiles,balancePreset.routeLengthScale,balancePreset.sourceCombatRoom,balancePreset.roomHeartLayouts,balancePreset.coinClearRewards,balancePreset.sourceRoomLocks,balancePreset.sourceTreasureUpgrade,balancePreset.sourceShopHeart,balancePreset.sourceShopKey,balancePreset.sourceShopVariation,balancePreset.shopCollectiblePool,balancePreset.treasureCollectiblePool,balancePreset.monstro,balancePreset.duke,balancePreset.seededBosses,balancePreset.bossRewardItem,balancePreset.roomProps);
    startExpedition(std::move(candidate),true);
    balanceNotice="Retried the same expedition seed with the applied player, enemy, view and map settings.";
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
