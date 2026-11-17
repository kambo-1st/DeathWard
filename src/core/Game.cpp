#include "core/Game.hpp"
#include "core/ExpeditionHud.hpp"
#include "world/ShopCartGeometry.hpp"
#include "render/AnimalModels.hpp"
#include "render/PlayerModel.hpp"
#include "render/TownScene.hpp"
#include <charconv>
#include <chrono>

namespace dw {
namespace {
constexpr Vector3 CameraOffset{23, 30, 23};
constexpr float MinCameraZoom = 0.35f, MaxCameraZoom = 1.5f;
constexpr float MinCameraPitch = 25 * DEG2RAD, MaxCameraPitch = 75 * DEG2RAD;
struct PointerTarget {
    EntityId enemy = 0;
    std::optional<Vector3> objective;
    std::optional<std::pair<int, int>> door;
};
PointerTarget pickTarget(const Simulation &run, Ray ray, const std::optional<RayCollision> &scenery) {
    PointerTarget result;
    float nearest = std::numeric_limits<float>::infinity();
    if (scenery) {
        if (scenery->hit)
            nearest = scenery->distance;
    } else if (run.arena.canyon) {
        const auto hit = run.arena.canyon->trace(ray.position, add(ray.position, mul(ray.direction, 1000)));
        if (hit.hit)
            nearest = hit.t * 1000;
    }
    // Scenery and gates limit interaction targets. Without a renderer, use the
    // collision geometry for those targets instead.
    const auto storyWalls=std::count_if(run.arena.storyProps.begin(),run.arena.storyProps.end(),
        [](const auto &prop){return prop.bounds.max.y>.45f;});
    const size_t firstWall = scenery ? run.arena.boundaryWalls.size() + run.arena.obstacles.size() + storyWalls + std::count_if(run.arena.floorProps.begin(),run.arena.floorProps.end(),
        [](const auto &p){return p.bounds.max.y>.45f;}) : 0;
    for (size_t i = firstWall; i < run.arena.walls.size(); ++i) {
        const auto &wall = run.arena.walls[i];
        const auto hit = GetRayCollisionBox(ray, {wall.min, wall.max});
        if (hit.hit)
            nearest = std::min(nearest, hit.distance);
    }
    auto hits = [&](Vector3 p, float radius, float height, float base=0) {
        const auto hit =
            GetRayCollisionBox(ray, {{p.x - radius, base, p.z - radius}, {p.x + radius, base+height, p.z + radius}});
        if (!hit.hit || hit.distance >= nearest)
            return false;
        nearest = hit.distance;
        return true;
    };
    auto objective = [&](Vector3 p, float radius, float height) {
        if (hits(p, radius, height))
            result.objective = p;
    };
    if (run.surveyTutorial && run.room==run.finalRoom() && run.roomClear)
        objective(run.surveyPosition(),1.1f,1.4f);
    if(run.arena.rooms[size_t(run.room)].story!=StoryRoom::None&&run.roomClear)
        objective(run.arena.rooms[size_t(run.room)].objective,1.2f,1.6f);
    if (run.legacyObjectives() && !run.rescued)
        objective(run.arena.miners, 1.7f, 2.0f);
    if (run.legacyObjectives() && !run.altarDestroyed)
        objective(run.arena.altar, 1.0f, 2.9f);
    if (run.canUseFloorExit())
        objective(run.arena.exit, 2.0f, 3.2f);
    if (run.rewardAvailable(run.room))
        objective(run.rewardPosition(run.room), 1.2f, 2.4f);
    for (const auto &key : run.arena.keys)
        if (!key.collected && run.rooms[size_t(key.room)].cleared)
            objective(key.position, 1.0f, 2.0f);
    const float objectiveDistance = nearest;
    // Passage hit areas are intentionally generous. They must not steal a
    // visible evidence case, key, pedestal or exit lantern at their edge.
    if (run.roomClear && !result.objective)
        for (size_t i = 0; i < run.arena.passages.size(); ++i)
            for (int side = 0; side < 2; ++side)
                if (hits(run.arena.doorApproach(int(i), side), 2.5f, 3.2f)) {
                    result.objective.reset();
                    result.door = std::pair{int(i), side};
                }
    // Visible pickups and the shopkeeper take priority over passage click areas.
    // Keep opaque scenery and actual interaction objects in front of them solid.
    nearest = objectiveDistance;
    if(run.arena.shopRoom>=0) {
        const auto &shop=run.arena.rooms[size_t(run.arena.shopRoom)];
        const auto box=shopCartGeometry::bounds(shop.center);
        const auto hit=GetRayCollisionBox(ray,{box.min,box.max});
        // The shared cart surface also participates in scenery picking. Admit
        // that same surface, while retaining occlusion by anything in front.
        if(hit.hit&&hit.distance<=nearest+.001f) {
            nearest=hit.distance;result.objective=shop.center;result.door.reset();
        }
    }
    for(const auto &site:run.arena.rooms)if(site.kind==RoomKind::Service&&hits(site.objective,.9f,2.8f)) {
        result.objective=site.objective;result.door.reset();
    }
    for (const auto &coin : run.moneyPickups)
        if (hits(coin.position, .65f, 1.1f)) {
            result.objective = coin.position;
            result.door.reset();
        }
    for(const auto &bomb:run.suppliedBombs)
        if(bomb.state==SuppliedBombState::Pickup&&hits(bomb.charge.position,.45f,.7f)) {
            result.objective=add(bomb.charge.position,{0,.67f,0});result.door.reset();
        }
    // Aim at enemy bodies (including their occlusion outlines) through scenery.
    // Only the camera ray ignores cover; the fired projectile still collides.
    nearest = std::numeric_limits<float>::infinity();
    for (const auto &enemy : run.enemies) {
        if (enemy.alive && !enemy.friendly && !(enemy.adultLeech&&enemy.adultLeech->intangible) && !(enemy.environment&&enemy.environment->spent) && enemy.state != EnemyState::Buried &&
            hits(enemy.position, enemy.radius, enemy.kind == EnemyKind::Boss ? 3.4f : 2.5f,enemy.position.y-.85f)) {
            result.enemy = enemy.id;
            result.objective.reset();
            result.door.reset();
        }
    }
    return result;
}
} // namespace

Game::Game(const std::filesystem::path &save, HubKind initialHub) : campaign(save), activeHub(initialHub) {
    if (campaign.recover()) {
        lastSummary = campaign.data().history.back();
        screen = Screen::Summary;
    }
    camera.position = CameraOffset;
    camera.target = {0, 0, 0};
    camera.up = {0, 1, 0};
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;
    cameraYaw_ = std::atan2(CameraOffset.z, CameraOffset.x);
    cameraPitch_ = std::atan2(CameraOffset.y, std::hypot(CameraOffset.x, CameraOffset.z));
    if (!town.load(hubDirectory() / "town.nav"))
        error = town.error;
    else
        reloadTownObjects();
    snapCamera();
    newSeed();
    initializeBalance();
}
std::filesystem::path Game::hubDirectory() const {
    return TownScene::assetDirectory(activeHub);
}
MusicScene Game::musicScene() const {
    if (screen == Screen::Expedition && run) {
        if (run->dead)
            return MusicScene::Defeat;
        if (!run->roomClear && run->roomThreats() > 0)
            return run->arena.rooms[size_t(run->room)].kind == RoomKind::Boss || run->boss() ? MusicScene::Boss : MusicScene::Combat;
        return run->arena.theme == MissionTheme::Canyon ? MusicScene::Canyon : MusicScene::Mine;
    }
    if (screen == Screen::Summary) {
        if (lastSummary.reason == EndReason::Victory)
            return MusicScene::Victory;
        if (lastSummary.reason == EndReason::Death)
            return MusicScene::Defeat;
    }
    return activeHub == HubKind::Redstone ? MusicScene::Canyon :
           activeHub == HubKind::BlackCreek ? MusicScene::Town : MusicScene::Frontier;
}
bool Game::reloadTownObjects() {
    TownDocument document;
    if (!document.load(hubDirectory() / "town.scene", error))
        return false;
    townObjects.reset(document);
    town.setMovingSolids(townObjects.solids());
    characters.reset(document, town);
    const bool loaded = document.ownsAnimals ? animals.reset(document.animals, town) :
        animals.load(activeHub == HubKind::BlackCreek ? AnimalModels::assetDirectory() / "town.animals"
                                                      : std::filesystem::path{}, town);
    configureArrival(document);
    if (!loaded)
        error = animals.error();
    return loaded;
}
bool Game::selectHub(HubKind hub) {
    if (screen != Screen::Hub || run || editorRequested)
        return false;
    HubWorld candidate;
    if (!candidate.load(TownScene::assetDirectory(hub) / "town.nav")) {
        error = candidate.error;
        return false;
    }
    TownDocument document;
    if (!document.load(TownScene::assetDirectory(hub) / "town.scene", error))
        return false;
    townObjects.reset(document);
    town = std::move(candidate);
    town.setMovingSolids(townObjects.solids());
    characters.reset(document, town);
    ++audioContext;
    audioCues.clear();
    activeHub = hub;
    configureArrival(document);
    if (document.ownsAnimals) animals.reset(document.animals, town);
    else animals.load(activeHub == HubKind::BlackCreek ? AnimalModels::assetDirectory() / "town.animals"
                                                      : std::filesystem::path{}, town);
    paused = missionMenu = walkingToMission = false;
    error = animals.error();
    resetPointerInput();
    snapCamera();
    return true;
}
void Game::launch(bool freeMission) {
    if(!freeMission&&arrivalActive()&&!ArrivalQuest::ready(campaign.data().world)) {
        requestQuestAction();return;
    }
    uint64_t seed = 0;
    auto result = std::from_chars(seedText.data(), seedText.data() + seedText.size(), seed);
    if (result.ec != std::errc{} || result.ptr != seedText.data() + seedText.size()) {
        error = "Enter a whole-number seed (up to 20 digits).";
        return;
    }
    const bool search=!freeMission&&arrivalActive()&&ArrivalQuest::tutorialReady(campaign.data().world);
    const bool account=!freeMission&&arrivalActive()&&ArrivalQuest::testimonyReady(campaign.data().world);
    const auto theme = search||account?MissionTheme::Canyon:resolveTheme(themeChoice, seed);
    auto candidate = std::make_unique<Simulation>(seed, campaign.data().nextRunId, campaign.data().world,
                                                  theme, visualSettings.canyonRiver,search,
                                                  account?WitnessAccount::Rourke:WitnessAccount::None,0,expeditionPacing,defaultMechanics(),
                                                  nextBalancePreset?nextBalancePreset->roomSizeScale:1,
                                                  nextBalancePreset?nextBalancePreset->roomMinHalfTiles:0,
                                                  nextBalancePreset?nextBalancePreset->roomMaxHalfTiles:0,
                                                  nextBalancePreset?nextBalancePreset->routeLengthScale:1,
                                                  nextBalancePreset?nextBalancePreset->sourceCombatRoom:true,
                                                  nextBalancePreset?nextBalancePreset->roomHeartLayouts:1,
                                                  nextBalancePreset?nextBalancePreset->coinClearRewards:true,
                                                  nextBalancePreset?nextBalancePreset->sourceRoomLocks:true,
                                                  nextBalancePreset?nextBalancePreset->sourceTreasureUpgrade:true,
                                                  nextBalancePreset?nextBalancePreset->sourceShopHeart:true,
                                                  nextBalancePreset?nextBalancePreset->sourceShopKey:true,
                                                  nextBalancePreset?nextBalancePreset->sourceShopVariation:true,
                                                  nextBalancePreset?nextBalancePreset->shopCollectiblePool:1,
                                                  nextBalancePreset?nextBalancePreset->treasureCollectiblePool:1);
    startExpedition(std::move(candidate));
    if(search&&arrivalStage()==ArrivalStage::Trail)ArrivalQuest::advance(campaign,ArrivalStage::Trail);
    if(account&&arrivalStage()==ArrivalStage::RourkeTrail)ArrivalQuest::advance(campaign,ArrivalStage::RourkeTrail);
    if(search)run->announce("THE LOST SURVEY / Recover Bell's records from the near camp.",6);
}
void Game::checkpoint() {
    if (run && run->checkpointNeeded) {
        campaign.checkpoint(configuredSummary());
        run->checkpointNeeded = false;
    }
}
void Game::finish(EndReason reason) {
    if (!run)
        return;
    lastSummary = campaign.resolve(configuredSummary(), reason);
    run.reset();
    buildOpen=balanceOpen=balancePathEditing=false;
    ++audioContext;
    audioCues.clear();
    town.reset();
    newSeed();
    screen = Screen::Summary;
    paused = false;
    accumulator = 0;
    resetPointerInput();
}
void Game::resetPointerInput() {
    placeDynamiteQueued_ = activeQueued_ = trinketQueued_ = false;
    cameraDragging_ = false;
    leftCommand_ = LeftCommand::None;
    attackTarget_ = hoveredEnemy = 0;
    dodgeQueued_ = interactQueued_ = standStillQueued_ = false;
    dodgeAimQueued_.reset();
    moveQueued_.reset();
    doorQueued_.reset();
    fireQueued_.reset();
    mouseMoveCooldown_ = 0;
}
void Game::close() {
    if (run)
        finish(run->dead ? EndReason::Death : EndReason::Retreat);
    quit = true;
}
void Game::perform(Action action) {
    try {
        if(balanceOpen&&action!=Action::None&&action!=Action::Quit&&
           (action<Action::CloseBalance||action>Action::EditBalancePath)&&
           (action<Action::BalanceDamageHealthTab||action>Action::ResetYumHeart)&&
           (action<Action::BalanceTrinketTab||action>Action::ResetTrinkets)&&action!=Action::WhipDown&&action!=Action::WhipUp&&
           (action<Action::BalanceHaloTab||action>Action::ResetBook))return;
        if(balanceOpen&&action!=Action::None)balancePathEditing=false;
        if(buildOpen&&action!=Action::CloseBuild&&action!=Action::Quit)return;
        if(controlsOpen && action!=Action::CloseControls && action!=Action::Quit)return;
        if(letterVisible()&&action!=Action::CloseLetter&&action!=Action::Quit)return;
        if(journalVisible()&&action!=Action::CloseJournal&&action!=Action::JournalPrevious&&action!=Action::JournalNext&&action!=Action::Quit)return;
        switch (action) {
        case Action::OpenBalance:
            if(!run||(!run->dead&&!run->finished)) {
                balanceOpen=true;balancePathEditing=false;resetPointerInput();accumulator=0;
            }
            break;
        case Action::CloseBalance:
            balanceOpen=balancePathEditing=false;accumulator=0;resetPointerInput();break;
        case Action::BalanceWorldTab:balanceRewardsOpen=balanceShootingOpen=balanceEnemiesOpen=balanceCombatOpen=false;break;
        case Action::BalanceShootingTab:balanceTrinketOpen=false;balanceActiveOpen=balanceFamiliarOpen=balanceTreasureOpen=false;balanceShootingOpen=true;balanceEnemiesOpen=balanceRewardsOpen=balanceCombatOpen=false;break;
        case Action::BalanceEnemiesTab:balanceEnemiesOpen=true;balanceShootingOpen=balanceRewardsOpen=balanceCombatOpen=false;balancePooterOpen=false;break;
        case Action::BalanceRewardsTab:balanceShopOpen=false;balanceRewardsOpen=true;balanceShootingOpen=balanceEnemiesOpen=balanceCombatOpen=false;break;
        case Action::BalanceShopTab:balanceShopOpen=true;balanceShopKeyOpen=balanceShopStockOpen=balanceShopBombOpen=balanceShopSoulHeartOpen=false;break;
        case Action::BalanceShopHeartTab:balanceShopKeyOpen=balanceShopStockOpen=balanceShopBombOpen=balanceShopSoulHeartOpen=false;break;
        case Action::BalanceShopKeyTab:balanceShopKeyOpen=true;balanceShopStockOpen=balanceShopBombOpen=balanceShopSoulHeartOpen=false;break;
        case Action::BalanceShopStockTab:balanceShopStockOpen=true;balanceShopKeyOpen=balanceShopBombOpen=balanceShopSoulHeartOpen=false;break;
        case Action::BalanceShopBombTab:balanceShopBombOpen=true;balanceShopKeyOpen=balanceShopStockOpen=balanceShopSoulHeartOpen=false;break;
        case Action::ShopBombPriceDown:case Action::ShopBombPriceUp:case Action::ResetShopBombPrice: {
            auto preset=balancePreset;
            preset.shopBombPrice=action==Action::ResetShopBombPrice?5:std::clamp(preset.shopBombPrice+(action==Action::ShopBombPriceUp?1:-1),0,15);
            applyBalance(std::move(preset));balanceNotice="Unsold dynamite base price updated. Sold stock stays sold. Export to keep edits.";break;
        }
        case Action::BalanceShopRedHeartTab:balanceShopSoulHeartOpen=false;break;
        case Action::BalanceShopSoulHeartTab:balanceShopSoulHeartOpen=true;balanceShopKeyOpen=balanceShopStockOpen=balanceShopBombOpen=false;break;
        case Action::ShopSoulHeartPriceDown:case Action::ShopSoulHeartPriceUp:case Action::ResetShopSoulHeartPrice: {
            auto preset=balancePreset;
            preset.shopSoulHeartPrice=action==Action::ResetShopSoulHeartPrice?5:std::clamp(preset.shopSoulHeartPrice+(action==Action::ShopSoulHeartPriceUp?1:-1),0,15);
            applyBalance(std::move(preset));balanceNotice="Unsold soul-heart base price updated. Sold stock stays sold. Export to keep edits.";break;
        }
        case Action::BalanceFamiliarTab:balanceHaloOpen=false;balanceTrinketOpen=false;balanceActiveOpen=false;balanceFamiliarOpen=true;balanceTreasureOpen=false;break;
        case Action::BalanceHaloTab:balanceHaloOpen=true;balanceFamiliarOpen=true;balanceActiveOpen=balanceTrinketOpen=balanceTreasureOpen=false;break;
        case Action::HaloSpeedDown:case Action::HaloSpeedUp:
        case Action::HaloRadiusDown:case Action::HaloRadiusUp:
        case Action::HaloContactDown:case Action::HaloContactUp:case Action::ResetHalo: {
            auto preset=balancePreset;auto &t=preset.haloOfFlies;
            if(action==Action::ResetHalo)t={};
            else {
                const int offset=int(action)-int(Action::HaloSpeedDown);
                float *field=offset<2?&t.orbitSpeed:offset<4?&t.orbitRadius:&t.contactRadius;
                *field=std::clamp(*field+(offset%2?.05f:-.05f),.25f,2.f);
            }
            applyBalance(std::move(preset));balanceNotice="Orbit and contact edits apply next tick; rotation phase and ownership remain.";break;
        }
        case Action::BobbyMovementDown:case Action::BobbyMovementUp:
        case Action::BobbyIntervalDown:case Action::BobbyIntervalUp:
        case Action::BobbyDamageDown:case Action::BobbyDamageUp:
        case Action::BobbyShotDown:case Action::BobbyShotUp:case Action::ResetBrotherBobby: {
            auto preset=balancePreset;auto &t=preset.brotherBobby;
            if(action==Action::ResetBrotherBobby)t={};
            else {
                const int offset=int(action)-int(Action::BobbyMovementDown);
                float *field=offset<2?&t.movement:offset<4?&t.interval:offset<6?&t.damage:&t.shotSpeed;
                *field=std::clamp(*field+(offset%2?.05f:-.05f),.25f,2.f);
            }
            applyBalance(std::move(preset));balanceNotice="Following updates next tick. New shots use edits; current waits and flying shots stay fixed.";break;
        }
        case Action::BalanceActiveTab:balanceBookOpen=false;balanceTrinketOpen=false;balanceActiveOpen=true;balanceFamiliarOpen=balanceTreasureOpen=false;break;
        case Action::BalanceBookTab:balanceBookOpen=true;balanceActiveOpen=true;balanceTrinketOpen=balanceFamiliarOpen=balanceTreasureOpen=false;break;
        case Action::BookDurationDown:case Action::BookDurationUp:case Action::BookRechargeDown:case Action::BookRechargeUp:case Action::ResetBook: {
            auto preset=balancePreset;auto &t=preset.bookOfShadows;
            if(action==Action::ResetBook)t={};
            else if(action==Action::BookDurationDown||action==Action::BookDurationUp)t.duration=std::clamp(t.duration+(action==Action::BookDurationUp?.5f:-.5f),1.f,30.f);
            else t.recharge=std::clamp(t.recharge+(action==Action::BookRechargeUp?1:-1),0,3);
            applyBalance(std::move(preset));activeQueued_=false;
            balanceNotice="Duration applies on next use; recharge on future first combat clears. Current protection and charge stay fixed.";break;
        }
        case Action::YumHealingDown:case Action::YumHealingUp:
        case Action::YumRechargeDown:case Action::YumRechargeUp:
        case Action::CycleActiveBinding:case Action::ResetYumHeart: {
            auto preset=balancePreset;auto &t=preset.yumHeart;
            if(action==Action::ResetYumHeart)t={};
            else if(action==Action::CycleActiveBinding)t.binding=(t.binding+1)%3;
            else if(action==Action::YumHealingDown||action==Action::YumHealingUp)t.healing=std::clamp(t.healing+(action==Action::YumHealingUp?1:-1),1,6);
            else t.recharge=std::clamp(t.recharge+(action==Action::YumRechargeUp?1:-1),0,4);
            applyBalance(std::move(preset));activeQueued_=false;
            balanceNotice="Healing applies on next use; recharge on future first combat clears. Existing charge stays unchanged.";break;
        }
        case Action::BalanceTrinketTab:balanceTrinketOpen=true;balanceActiveOpen=balanceFamiliarOpen=balanceTreasureOpen=false;break;
        case Action::WhipDown:case Action::WhipUp:case Action::CancerDown:case Action::CancerUp:case Action::ToggleTrinketRewards:
        case Action::CycleTrinketBinding:case Action::ResetTrinkets: {
            auto preset=balancePreset;auto &t=preset.trinkets;
            if(action==Action::ResetTrinkets)t={};
            else if(action==Action::ToggleTrinketRewards)t.clearRewards=!t.clearRewards;
            else if(action==Action::CycleTrinketBinding)t.binding=(t.binding+1)%2;
            else if(action==Action::WhipDown||action==Action::WhipUp)t.whipStrength=std::clamp(t.whipStrength+(action==Action::WhipUp?.05f:-.05f),0.f,2.f);
            else t.cancerStrength=std::clamp(t.cancerStrength+(action==Action::CancerUp?.05f:-.05f),0.f,2.f);
            applyBalance(std::move(preset));trinketQueued_=false;
            balanceNotice="Owned effect changes next attack; current wait and flying shots stay fixed. Rewards apply to future first clears.";break;
        }
        case Action::CycleTreasureCollectiblePool:
            balanceDraft.treasureCollectiblePool=(balanceDraft.treasureCollectiblePool+1)%7;
            balanceNotice="Treasure selection pending / Apply resets this floor";break;
        case Action::CricketHeadDown:case Action::CricketHeadUp:case Action::ResetCricketHead: {
            auto preset=balancePreset;
            preset.cricketHeadStrength=action==Action::ResetCricketHead?1:std::clamp(preset.cricketHeadStrength+(action==Action::CricketHeadUp?.05f:-.05f),0.f,2.f);
            applyBalance(std::move(preset));balanceNotice="Cricket strength applies to new attacks. Flying shots retain their damage and size.";break;
        }
        case Action::CycleShopCollectiblePool:
            balanceDraft.shopCollectiblePool=(balanceDraft.shopCollectiblePool+1)%3;
            balanceNotice="Collectible selection pending / Apply resets this floor";
            break;
        case Action::ToggleShopVariation:
            balanceDraft.sourceShopVariation=!balanceDraft.sourceShopVariation;
            balanceNotice="Stock selection pending. APPLY MAP CHANGES resets floor purchases; player/build retained.";break;
        case Action::ToggleSteamSaleDiscounts: {
            auto preset=balancePreset;preset.steamSaleDiscounts=!preset.steamSaleDiscounts;applyBalance(std::move(preset));
            balanceNotice="Owned Steam Sale effect updated on unsold source-shop stock. Export to keep this setting.";break;
        }
        case Action::ShopUpgradePriceDown:case Action::ShopUpgradePriceUp:case Action::ResetShopUpgradePrice: {
            auto preset=balancePreset;
            preset.shopUpgradePrice=action==Action::ResetShopUpgradePrice?15:std::clamp(preset.shopUpgradePrice+(action==Action::ShopUpgradePriceUp?1:-1),0,30);
            applyBalance(std::move(preset));balanceNotice="Upgrade base price updated; discounts are applied at purchase. Sold stock stays sold.";break;
        }
        case Action::ToggleShopKey:
            balanceDraft.sourceShopKey=!balanceDraft.sourceShopKey;
            balanceNotice="Key stock pending. APPLY MAP CHANGES resets floor purchases; player/build retained.";break;
        case Action::ShopKeyPriceDown:case Action::ShopKeyPriceUp:case Action::ResetShopKeyPrice: {
            auto preset=balancePreset;
            preset.shopKeyPrice=action==Action::ResetShopKeyPrice?5:std::clamp(preset.shopKeyPrice+(action==Action::ShopKeyPriceUp?1:-1),0,15);
            applyBalance(std::move(preset));
            balanceNotice="Unsold key price updated. Sold stock stays sold. Export or Use next expedition to keep edits.";break;
        }
        case Action::ToggleShopHeart:
            balanceDraft.sourceShopHeart=!balanceDraft.sourceShopHeart;
            balanceNotice="Shop stock pending. APPLY MAP CHANGES resets floor purchases; player/build retained.";break;
        case Action::ShopHeartPriceDown:case Action::ShopHeartPriceUp:case Action::ResetShopHeartPrice: {
            auto preset=balancePreset;
            preset.shopHeartPrice=action==Action::ResetShopHeartPrice?3:std::clamp(preset.shopHeartPrice+(action==Action::ShopHeartPriceUp?1:-1),0,15);
            applyBalance(std::move(preset));
            balanceNotice="Unsold heart price updated. Sold stock stays sold. Export or Use next expedition to keep edits.";break;
        }
        case Action::BalanceTreasureTab:balanceTrinketOpen=false;balanceActiveOpen=balanceFamiliarOpen=false;balanceTreasureOpen=true;break;
        case Action::ToggleTreasureUpgrade:
            balanceDraft.sourceTreasureUpgrade=!balanceDraft.sourceTreasureUpgrade;
            balanceNotice="Treasure offering pending. APPLY MAP CHANGES resets this floor; player/build retained.";break;
        case Action::SadOnionDown:case Action::SadOnionUp:case Action::ResetSadOnion: {
            auto preset=balancePreset;
            preset.sadOnionStrength=action==Action::ResetSadOnion?1:std::clamp(preset.sadOnionStrength+(action==Action::SadOnionUp?.05f:-.05f),0.f,2.f);
            applyBalance(std::move(preset));
            balanceNotice="Owned Sad Onion: next firing interval. Current wait and emitted shots retained.";break;
        }
        case Action::BalanceRoomHeartsTab:balanceShopOpen=false;balanceRoomHeartsOpen=true;break;
        case Action::BalanceClearHeartsTab:balanceShopOpen=false;balanceRoomHeartsOpen=false;break;
        case Action::RoomHeartsOff:setRoomHeartLayouts(0);break;
        case Action::RoomHeartsSource:setRoomHeartLayouts(1);break;
        case Action::RoomHeartsTest:setRoomHeartLayouts(2);break;
        case Action::ToggleKeyRewards: {
            auto preset=balancePreset;preset.keyClearRewards=!preset.keyClearRewards;applyBalance(std::move(preset));
            balanceNotice="Keys: future first clears. Existing keys, chest contents and room layouts stay fixed.";break;
        }
        case Action::ToggleBombRewards: {
            auto preset=balancePreset;preset.bombClearRewards=!preset.bombClearRewards;applyBalance(std::move(preset));
            balanceNotice="Dynamite: future first clears. Existing dynamite pickups, chest contents and room layouts stay fixed.";break;
        }
        case Action::ToggleChestRewards: {
            auto preset=balancePreset;preset.chestClearRewards=!preset.chestClearRewards;applyBalance(std::move(preset));
            balanceNotice="Applies to future first clears. Existing chests and their contents stay fixed.";break;
        }
        case Action::ToggleCoinRewards: {
            auto preset=balancePreset;preset.coinClearRewards=!preset.coinClearRewards;applyBalance(std::move(preset));
            balanceNotice="Coins: future clears/drops; initial piles change on floor regeneration. Existing pickups stay.";break;
        }
        case Action::ToggleRedHeartRewards:setRedHeartRewards(!balancePreset.redHeartClearRewards,balancePreset.playerLuck);break;
        case Action::RewardLuckDown:case Action::RewardLuckUp:
            setRedHeartRewards(balancePreset.redHeartClearRewards,std::clamp(balancePreset.playerLuck+(action==Action::RewardLuckUp?1.f:-1.f),BalancePreset::MinLuck,BalancePreset::MaxLuck));break;
        case Action::HeartAppearanceDown:case Action::HeartAppearanceUp:
            setRedHeartAppearanceSpeed(std::clamp(balancePreset.redHeartAppearanceSpeed+(action==Action::HeartAppearanceUp?.05f:-.05f),BalancePreset::MinHeartAppearanceSpeed,BalancePreset::MaxHeartAppearanceSpeed));break;
        case Action::ResetHeartAppearance:setRedHeartAppearanceSpeed(1);break;
        case Action::ResetRewardLuck:setRedHeartRewards(balancePreset.redHeartClearRewards,BalancePreset::ReferenceLuck);break;
        case Action::BalanceCombatTab:balanceCombatOpen=true;balanceBombsOpen=balanceDoorsOpen=false;balanceShootingOpen=balanceEnemiesOpen=balanceRewardsOpen=false;break;
        case Action::BalanceDamageHealthTab:balanceBombsOpen=balanceDoorsOpen=false;break;
        case Action::BalanceBombsTab:balanceBombsOpen=true;balanceDoorsOpen=false;break;
        case Action::BalanceDoorsTab:balanceDoorsOpen=true;balanceBombsOpen=false;break;
        case Action::ToggleSourceRoomLocks:
            balanceDraft.sourceRoomLocks=!balanceDraft.sourceRoomLocks;
            balanceNotice="Room lock rules pending. APPLY MAP CHANGES resets this floor; player/build retained.";break;
        case Action::DoorKeyCostDown:case Action::DoorKeyCostUp:case Action::ResetKeyedDoors: {
            auto preset=balancePreset;
            preset.keyedDoorCost=action==Action::ResetKeyedDoors?1:std::clamp(preset.keyedDoorCost+(action==Action::DoorKeyCostUp?1:-1),0,5);
            applyBalance(std::move(preset));
            balanceNotice="Applies at the next successful unlock. Opened doors stay open.";break;
        }
        case Action::BombFuseDown:case Action::BombFuseUp:
        case Action::BombRadiusDown:case Action::BombRadiusUp:
        case Action::BombDamageDown:case Action::BombDamageUp:
        case Action::BombSelfDamageDown:case Action::BombSelfDamageUp: {
            auto t=balancePreset.inventoryBombs;
            const auto adjust=[](float value,float step,float lo,float hi){return std::clamp(std::round((value+step)*100)/100,lo,hi);};
            if(action==Action::BombFuseDown||action==Action::BombFuseUp)
                t.fuseMultiplier=adjust(t.fuseMultiplier,action==Action::BombFuseUp?.05f:-.05f,.25f,4);
            else if(action==Action::BombRadiusDown||action==Action::BombRadiusUp)
                t.radiusMultiplier=adjust(t.radiusMultiplier,action==Action::BombRadiusUp?.05f:-.05f,.25f,3);
            else if(action==Action::BombDamageDown||action==Action::BombDamageUp)
                t.damage=std::clamp(t.damage+(action==Action::BombDamageUp?5:-5),1.f,500.f);
            else t.selfDamageHalfHearts=std::clamp(t.selfDamageHalfHearts+(action==Action::BombSelfDamageUp?1:-1),-1,12);
            setInventoryBombs(t);break;
        }
        case Action::ResetInventoryBombs:setInventoryBombs({});break;
        case Action::ToggleRockBlastShielding: {
            auto t=balancePreset.inventoryBombs;t.rocksBlockBlast=!t.rocksBlockBlast;setInventoryBombs(t);break;
        }
        case Action::CombatDamageDown:case Action::CombatDamageUp:
            setCombatBalance(std::clamp(std::round((balancePreset.playerDamage+(action==Action::CombatDamageUp?.1f:-.1f))*10)/10,
                             BalancePreset::MinDamage,BalancePreset::MaxDamage),balancePreset.regularHealthMultiplier);break;
        case Action::RegularHealthDown:case Action::RegularHealthUp:
            setCombatBalance(balancePreset.playerDamage,std::clamp(std::round((balancePreset.regularHealthMultiplier+(action==Action::RegularHealthUp?.05f:-.05f))*100)/100,
                             BalancePreset::MinRegularHealth,BalancePreset::MaxRegularHealth));break;
        case Action::ResetCombat:setCombatBalance(BalancePreset::ReferenceDamage,BalancePreset::ReferenceRegularHealth);break;
        case Action::BalanceChasersTab:balancePooterOpen=false;break;
        case Action::BalancePooterTab:balancePooterOpen=true;break;
        case Action::PooterMovementDown:case Action::PooterMovementUp:
            setPooterTuning(std::clamp(std::round((balancePreset.pooterMovementMultiplier+(action==Action::PooterMovementUp?.05f:-.05f))*100)/100,
                           BalancePreset::MinPooterMovement,BalancePreset::MaxPooterMovement),balancePreset.pooterShotSpeedMultiplier,balancePreset.pooterAttackIntervalMultiplier);break;
        case Action::PooterShotDown:case Action::PooterShotUp:
            setPooterTuning(balancePreset.pooterMovementMultiplier,std::clamp(std::round((balancePreset.pooterShotSpeedMultiplier+(action==Action::PooterShotUp?.05f:-.05f))*100)/100,
                           BalancePreset::MinPooterShotSpeed,BalancePreset::MaxPooterShotSpeed),balancePreset.pooterAttackIntervalMultiplier);break;
        case Action::PooterDelayDown:case Action::PooterDelayUp:
            setPooterTuning(balancePreset.pooterMovementMultiplier,balancePreset.pooterShotSpeedMultiplier,std::clamp(std::round((balancePreset.pooterAttackIntervalMultiplier+(action==Action::PooterDelayUp?.05f:-.05f))*100)/100,
                           BalancePreset::MinPooterInterval,BalancePreset::MaxPooterInterval));break;
        case Action::ResetPooter:setPooterTuning(1,1,1);break;
        case Action::GaperMovementDown:case Action::GaperMovementUp:
            setGaperMovement(std::clamp(std::round((balancePreset.gaperMovementMultiplier+(action==Action::GaperMovementUp?.05f:-.05f))*100)/100,
                                       BalancePreset::MinGaperMovement,BalancePreset::MaxGaperMovement));break;
        case Action::GaperMovementReset:setGaperMovement(BalancePreset::ReferenceGaperMovement);break;
        case Action::SpiderMovementDown:case Action::SpiderMovementUp:
            setSpiderMovement(std::clamp(std::round((balancePreset.spiderMovementMultiplier+(action==Action::SpiderMovementUp?.05f:-.05f))*100)/100,
                                        BalancePreset::MinSpiderMovement,BalancePreset::MaxSpiderMovement));break;
        case Action::SpiderMovementReset:setSpiderMovement(BalancePreset::ReferenceSpiderMovement);break;
        case Action::TearsDown:case Action::TearsUp:
            setShooting(std::clamp(balancePreset.tearsPerSecond+(action==Action::TearsUp?.1f:-.1f),
                                  BalancePreset::MinTears,BalancePreset::MaxTears),balancePreset.shotSpeed,balancePreset.rangeTiles);break;
        case Action::ShotSpeedDown:case Action::ShotSpeedUp:
            setShooting(balancePreset.tearsPerSecond,std::clamp(std::round((balancePreset.shotSpeed+(action==Action::ShotSpeedUp?.05f:-.05f))*100)/100,
                        BalancePreset::MinShotSpeed,BalancePreset::MaxShotSpeed),balancePreset.rangeTiles);break;
        case Action::RangeDown:case Action::RangeUp:
            setShooting(balancePreset.tearsPerSecond,balancePreset.shotSpeed,
                        std::clamp(std::round((balancePreset.rangeTiles+(action==Action::RangeUp?.25f:-.25f))*100)/100,
                                   BalancePreset::MinRange,BalancePreset::MaxRange));break;
        case Action::ResetShooting:resetShooting();break;
        case Action::RoomRangeAuto:setRoomSizeRange(0,0);break;
        case Action::RoomMinDown:case Action::RoomMinUp:case Action::RoomMaxDown:case Action::RoomMaxUp: {
            auto [lo,hi]=roomSizeRange();
            if(action==Action::RoomMinDown)lo=std::max(5,lo-1);
            if(action==Action::RoomMinUp)lo=std::min(hi,lo+1);
            if(action==Action::RoomMaxDown)hi=std::max(lo,hi-1);
            if(action==Action::RoomMaxUp)hi=std::min(10,hi+1);
            setRoomSizeRange(lo,hi);break;
        }
        case Action::RoomSizeDown:
        case Action::RoomSizeUp:
            setRoomSize(std::clamp(std::round(balanceDraft.roomSizeScale*100+(action==Action::RoomSizeUp?1:-1))/100,.75f,1.5f));break;
        case Action::RouteLengthDown:case Action::RouteLengthUp:
            setRouteLength(std::clamp(std::round(balanceDraft.routeLengthScale*100+(action==Action::RouteLengthUp?1:-1))/100,.25f,2.f));break;
        case Action::ToggleSourceCombatRoom:setSourceCombatRoom(!balanceDraft.sourceCombatRoom);break;
        case Action::ApplyMapChanges:applyMapChanges();break;
        case Action::DefaultZoomDown:case Action::DefaultZoomUp:
            setDefaultZoom(std::clamp(std::round(balancePreset.defaultZoomPercent)+(action==Action::DefaultZoomUp?1:-1),
                                     BalancePreset::MinZoom,BalancePreset::MaxZoom));break;
        case Action::DefaultZoomCurrent:
            setDefaultZoom(std::clamp(std::round(cameraZoomPercent()),BalancePreset::MinZoom,BalancePreset::MaxZoom));break;
        case Action::DefaultZoomReset:setDefaultZoom(BalancePreset::ReferenceZoom);break;
        case Action::SpeedDown:
        case Action::SpeedUp:
            setPlayerSpeed(std::clamp(std::round(balancePreset.playerSpeed*100+(action==Action::SpeedUp?10:-10))/100,
                                      BalancePreset::MinSpeed,BalancePreset::MaxSpeed));break;
        case Action::ResetBalance:resetBalance();break;
        case Action::ExportBalance:exportBalancePreset();break;
        case Action::LoadBalance:loadBalancePreset(balanceFile);break;
        case Action::RememberBalance:rememberBalancePreset();break;
        case Action::EditBalancePath:
            balancePathBeforeEdit_=balanceFile;balancePathEditing=true;break;
        case Action::RetryExpedition:retryExpedition();break;
        case Action::InspectBuild:
            if(run&&!run->dead&&(paused||(!run->shopOpen&&!run->rewardOpen))) {buildOpen=true;resetPointerInput();}
            break;
        case Action::CloseBuild: buildOpen=false;accumulator=0;resetPointerInput();break;
        case Action::Controls: controlsOpen=true;resetPointerInput();break;
        case Action::CloseControls: controlsOpen=false;resetPointerInput();break;
        case Action::ReadJournal: journalOpen=true;journalIndex=0;resetPointerInput();town.stop();break;
        case Action::CloseJournal:
            journalOpen=false;if(run)run->storyOpen=StoryRoom::None;
            accumulator=0;resetPointerInput();break;
        case Action::JournalPrevious:
        case Action::JournalNext: {
            const auto entries=journalEntries();
            if(run&&run->storyOpen!=StoryRoom::None) {
                for(size_t i=0;i<entries.size();++i)if(entries[i].room==run->storyOpen)journalIndex=int(i);
                run->storyOpen=StoryRoom::None;journalOpen=true;
            }
            journalIndex=std::clamp(journalIndex+(action==Action::JournalNext?1:-1),0,std::max(0,int(entries.size())-1));
            break;
        }
        case Action::ReadLetter:
            if((run&&run->surveyRecovered)||campaign.data().world.flags.contains("redstone.survey_recovered")) {
                readingLetter=true;resetPointerInput();town.stop();
            }
            break;
        case Action::CloseLetter:
            readingLetter=false;if(run)run->letterOpen=false;
            accumulator=0;resetPointerInput();break;
        case Action::QuestAction: requestQuestAction(); break;
        case Action::QuestNext: nextQuestLine(); break;
        case Action::QuestCancel:
            questDialogue_.clear();walkingToQuest_=false;town.stop();resetPointerInput();break;
        case Action::ToggleSandstorm:
            sandstorm = !sandstorm;
            break;
        case Action::CycleVisualStyle:
            visualStyle = nextVisualStyle(visualStyle);
            break;
        case Action::CycleExpeditionPacing:
            if (screen == Screen::Hub && missionMenu)
                expeditionPacing = nextExpeditionPacing(expeditionPacing);
            break;
        case Action::ToggleCanyonRiver:
            if (screen == Screen::Hub && missionMenu)
                visualSettings.canyonRiver = !visualSettings.canyonRiver;
            break;
        case Action::ToggleGroundDetail:
            visualSettings.groundDetail = !visualSettings.groundDetail;
            break;
        case Action::VegetationLess:
        case Action::VegetationMore:
            visualSettings.vegetation =
                std::clamp(visualSettings.vegetation + (action == Action::VegetationMore ? 25 : -25), 0,
                           VisualSettings::MaxVegetation);
            break;
        case Action::MasterDown:
        case Action::MasterUp:
            audioSettings.master =
                std::clamp(audioSettings.master + (action == Action::MasterUp ? .1f : -.1f), 0.f, 1.f);
            break;
        case Action::EffectsDown:
        case Action::EffectsUp:
            audioSettings.effects =
                std::clamp(audioSettings.effects + (action == Action::EffectsUp ? .1f : -.1f), 0.f, 1.f);
            break;
        case Action::AmbienceDown:
        case Action::AmbienceUp:
            audioSettings.ambience =
                std::clamp(audioSettings.ambience + (action == Action::AmbienceUp ? .1f : -.1f), 0.f, 1.f);
            break;
        case Action::AudioMute:
            audioSettings.muted = !audioSettings.muted;
            break;
        case Action::MusicDown:
        case Action::MusicUp:
            audioSettings.music =
                std::clamp(audioSettings.music + (action == Action::MusicUp ? .1f : -.1f), 0.f, 1.f);
            break;
        case Action::AudioTest:
            audioCues.push(AudioCueKind::Test);
            break;
        case Action::HealthDown:
        case Action::HealthUp:
        case Action::DamageDown:
        case Action::DamageUp:
        case Action::ResetPlayer:
            if (debug && run && !run->dead && !run->finished) {
                float health = playerHealth, damage = playerDamage;
                if (action == Action::HealthDown)
                    health -= 2;
                if (action == Action::HealthUp)
                    health += 2;
                if (action == Action::DamageDown)
                    damage -= 4;
                if (action == Action::DamageUp)
                    damage += 4;
                if (action == Action::ResetPlayer) {
                    health = StartingHealth;
                    damage = BalancePreset::ReferenceDamage*CombatHealthUnitsPerSource;
                }
                run->tunePlayer(health, damage);
                setCombatBalance(std::clamp(damage/CombatHealthUnitsPerSource,BalancePreset::MinDamage,BalancePreset::MaxDamage),balancePreset.regularHealthMultiplier);
                playerHealth = run->player.baseHealth;
                playerDamage = run->player.shotDamage;
                run->debugNotice("PLAYER / base health " + std::to_string(int(playerHealth)) +
                              " / shot damage " + std::to_string(int(playerDamage)));
            }
            break;
        case Action::TravelHub:
            selectHub(primaryTravelHub(activeHub));
            break;
        case Action::TravelFrontier:
            selectHub(HubKind::Frontier);
            break;
        case Action::TravelRedstone:
            selectHub(HubKind::Redstone);
            break;
        case Action::ThemeSeeded:
        case Action::ThemeMine:
        case Action::ThemeCanyon:
            if (screen == Screen::Hub && !run)
                themeChoice = action == Action::ThemeSeeded ? ThemeChoice::Seeded
                              : action == Action::ThemeMine ? ThemeChoice::Mine
                                                            : ThemeChoice::Canyon;
            break;
        case Action::EditTown:
            if (screen == Screen::Hub && !run) {
                editorRequested = true;
                missionMenu = paused = walkingToMission = false;
                town.stop();
                resetPointerInput();
                questDialogue_.clear();walkingToQuest_=false;
            }
            break;
        case Action::Launch:
            launch();
            break;
        case Action::History:
            screen = Screen::History;
            historyIndex = std::max(0, int(campaign.data().history.size()) - 1);
            break;
        case Action::Missions:
            if(arrivalActive()) {requestQuestAction();break;}
            if (screen == Screen::Hub && town.loaded()) {
                if (town.nearMission()) {
                    missionMenu = true;
                    town.stop();
                } else
                    walkingToMission = town.moveTo(town.mission);
            }
            break;
        case Action::CloseMissions:
            missionMenu = false;
            walkingToMission = false;
            town.stop();
            break;
        case Action::NewSeed:
            newSeed();
            error.clear();
            break;
        case Action::Hub:
            questDialogue_.clear();walkingToQuest_=false;
            resetPointerInput();
            missionMenu = walkingToMission = false;
            paused = false;
            town.stop();
            screen = Screen::Hub;
            resetArmed = false;
            error.clear();
            snapCamera();
            break;
        case Action::Pause:
            walkingToQuest_=false;
            paused = true;
            if (screen == Screen::Hub) {
                town.stop();
                walkingToMission = false;
            }
            break;
        case Action::Resume:
            paused = false;
            break;
        case Action::ReviewPowerupFight:case Action::ReviewPowerupBoss:
            if(run&&!paused&&run->visitPowerupReviewEncounter(action==Action::ReviewPowerupBoss)){resetPointerInput();accumulator=0;updateCamera(10);checkpoint();}
            break;
        case Action::DropTrinket:
            if(run&&!paused&&!run->dead&&!run->finished&&!run->rewardOpen&&!run->shopOpen)trinketQueued_=true;
            break;
        case Action::UseActiveItem:
            if(run&&!paused&&!run->dead&&!run->finished&&!run->rewardOpen&&!run->shopOpen)activeQueued_=true;
            break;
        case Action::Dodge:
            if (run && !paused && !run->rewardOpen && !run->shopOpen)
                dodgeQueued_ = true;
            break;
        case Action::Dynamite:
            if (run && !paused && !run->dead && !run->rewardOpen && !run->shopOpen) {
                resetPointerInput();
                placeDynamiteQueued_ = true;
            }
            break;
        case Action::DynamiteMode:
            // Retired action ID: ordinary dynamite is always placed at the feet.
            break;
        case Action::Interact:
            if (run && !paused && !run->rewardOpen && !run->shopOpen)
                interactQueued_ = true;
            break;
        case Action::Retreat:
            finish(EndReason::Retreat);
            break;
        case Action::BuyShop0:
        case Action::BuyShop1:
        case Action::BuyShop2:
        case Action::BuyShop3:
            if (run && !paused && run->buyShop(int(action) - int(Action::BuyShop0)))
                checkpoint();
            break;
        case Action::CloseShop:
            if (run) {
                run->closeShop();
                resetPointerInput();
            }
            break;
        case Action::Quit:
            close();
            break;
        case Action::Reward0:
        case Action::Reward1:
            if (run) {
                run->chooseReward(int(action) - int(Action::Reward0));
                checkpoint();
            }
            break;
        case Action::Previous:
            historyIndex = std::max(0, historyIndex - 1);
            break;
        case Action::Next:
            historyIndex = std::min(int(campaign.data().history.size()) - 1, historyIndex + 1);
            break;
        case Action::Reset:
            if (resetArmed) {
                campaign.reset();
                if(activeHub==HubKind::Redstone)ArrivalQuest::begin(campaign);
                resetArmed = false;
            } else
                resetArmed = true;
            break;
        default:
            break;
        }
        if (action != Action::None && action != Action::AudioTest && action != Action::Dodge &&
            action != Action::Interact)
            audioCues.push(AudioCueKind::UI);
    } catch (const std::exception &e) {
        error = e.what();
        paused = true;
    }
}
const RunSummary *Game::inspectedHistory() const {
    const auto &h = campaign.data().history;
    return historyIndex >= 0 && size_t(historyIndex) < h.size() ? &h[size_t(historyIndex)] : nullptr;
}
void Game::debugInput() {
    if (IsKeyPressed(KEY_F1)) {
        debug = !debug;
        if (!debug) {
            collisionDebug = slow = debugPanelOpen = false;
            if (run)
                run->godMode = false;
        }
    }
    if (!debug)
        return;
    if (IsKeyPressed(KEY_GRAVE))
        debugPanelOpen = !debugPanelOpen;
    if (IsKeyPressed(KEY_F10))
        collisionDebug = !collisionDebug;
    if (IsKeyPressed(KEY_LEFT_BRACKET))
        selectedItem = (selectedItem + int(defaultMechanics()->items().size()) - 1) % int(defaultMechanics()->items().size());
    if (IsKeyPressed(KEY_RIGHT_BRACKET))
        selectedItem = (selectedItem + 1) % int(defaultMechanics()->items().size());
    if (!run)
        return;
    const bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    if (shift && IsKeyPressed(KEY_B)) {
        run->dynamite = MaxDynamite;
        run->dynamiteCooldown = 0;
        run->debugNotice("CHEAT / dynamite refilled");
    }
    if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT))
        perform(shift ? Action::HealthDown : Action::DamageDown);
    if (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD))
        perform(shift ? Action::HealthUp : Action::DamageUp);
    if (IsKeyPressed(KEY_HOME))
        perform(Action::ResetPlayer);
    if (IsKeyPressed(KEY_COMMA) || IsKeyPressed(KEY_PERIOD)) {
        const int count = int(monsterCatalog().size());
        selectedMonster = (selectedMonster + (IsKeyPressed(KEY_COMMA) ? count - 1 : 1)) % count;
        const auto &d = monsterCatalog()[size_t(selectedMonster)];
        run->debugNotice("TEST ENEMY / " + monsterIdText(d.id) + " / " + d.name);
    }
    if (IsKeyPressed(KEY_F4) && shift)
        run->spawnMonsterDebug(monsterCatalog()[size_t(selectedMonster)].id);
    if (IsKeyPressed(KEY_F2)) {
        if (shift)
            run->healDebug();
        else {
            run->godMode = !run->godMode;
            run->debugNotice(run->godMode ? "CHEAT / invincible ON" : "CHEAT / invincible OFF");
        }
    }
    if (IsKeyPressed(KEY_F3)) {
        if (shift) {
            run->clearRoomDebug();
            resetPointerInput();
        } else {
            run->killAll();
            run->debugNotice("CHEAT / enemies killed.");
        }
    }
    if (IsKeyPressed(KEY_F4) && !shift)
        run->spawnEnemies(20);
    if (IsKeyPressed(KEY_F5))
        run->spawnEnemies(100);
    if (IsKeyPressed(KEY_F6)) {
        if (shift) {
            run->keys += 3;
            run->debugNotice("CHEAT / added 3 keys");
        } else
            for (const auto &item:run->content->items())
                run->grant(item.id);
    }
    if (IsKeyPressed(KEY_F7) || IsKeyPressed(KEY_F12)) {
        if (IsKeyPressed(KEY_F7))
            run->startBoss();
        else
            run->jumpDebug(shift ? run->room : (run->room + 1) % run->arena.roomCount(), shift);
        resetPointerInput();
        accumulator = 0;
        paused = false;
        snapCamera();
    }
    if (IsKeyPressed(KEY_F8)) {
        run->finishDebug(true);
        finish(EndReason::Victory);
        return;
    }
    if (IsKeyPressed(KEY_F9)) {
        run->finishDebug(false);
        finish(EndReason::Death);
        return;
    }
    if (IsKeyPressed(KEY_F11))
        run->startStress();
    if (IsKeyPressed(KEY_I))
        run->grant(run->content->items()[size_t(selectedItem)%run->content->items().size()].id);
    if (IsKeyPressed(KEY_V))
        for (int i = 0; i < 5; ++i)
            run->grant(run->content->items()[run->rewardRng.bounded(uint32_t(run->content->items().size()))].id);
    if (IsKeyPressed(KEY_P))
        paused = !paused;
    if (IsKeyPressed(KEY_O))
        slow = !slow;
    if (IsKeyPressed(KEY_M)) {
        run->rescued = true;
        run->checkpointNeeded = true;
    }
}
Vector3 Game::cameraOffset() const {
    const float radius = length(CameraOffset) * cameraZoom_;
    const float horizontal = radius * std::cos(cameraPitch_);
    return {horizontal * std::cos(cameraYaw_), radius * std::sin(cameraPitch_),
            horizontal * std::sin(cameraYaw_)};
}
Vector3 Game::cameraFocus() const {
    const auto position = run ? run->player.position : town.player.position;
    const float framing = std::sqrt(8.0f) * cameraZoom_;
    return sub(position, {framing * std::cos(cameraYaw_), .85f, framing * std::sin(cameraYaw_)});
}
void Game::updateCameraInput(float dt) {
    const float step=std::clamp(dt,0.f,.1f);
    const float orbit=float(IsKeyDown(KEY_R))-float(IsKeyDown(KEY_Q));
    const float tilt=float(IsKeyDown(KEY_INSERT))-float(IsKeyDown(KEY_DELETE));
    const float zoom=float(IsKeyDown(KEY_PAGE_UP))-float(IsKeyDown(KEY_PAGE_DOWN));
    cameraYaw_=std::remainder(cameraYaw_+orbit*1.5f*step,2*PI);
    cameraPitch_=std::clamp(cameraPitch_+tilt*.8f*step,MinCameraPitch,MaxCameraPitch);
    cameraZoomTarget_=std::clamp(cameraZoomTarget_*std::exp(-zoom*step),MinCameraZoom,MaxCameraZoom);
    if(orbit!=0||tilt!=0)camera.position=add(camera.target,cameraOffset());
    const bool over = pointerOverControls();
    if (!over) {
        const float wheel = std::clamp(GetMouseWheelMoveV().y, -20.0f, 20.0f);
        cameraZoomTarget_ =
            std::clamp(cameraZoomTarget_ * std::exp(-wheel * .12f), MinCameraZoom, MaxCameraZoom);
    }
    const auto mouse = GetMousePosition();
    if (!IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        cameraDragging_ = false;
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        cameraDragging_ = !over;
        cameraDragPosition_ = mouse; // Pressing starts a gesture without jumping to the cursor.
    }
    if (cameraDragging_) {
        cameraYaw_ = std::remainder(cameraYaw_ - (mouse.x - cameraDragPosition_.x) * .006f, 2 * PI);
        cameraPitch_ = std::clamp(cameraPitch_ + (mouse.y - cameraDragPosition_.y) * .004f, MinCameraPitch,
                                  MaxCameraPitch);
        // Apply the angle before movement and picking so WASD and clicks use the current view.
        camera.position = add(camera.target, cameraOffset());
    }
    cameraDragPosition_ = mouse;
}
void Game::snapCamera() {
    camera.target = cameraFocus();
    camera.position = add(camera.target, cameraOffset());
}
void Game::updateCamera(float dt) {
    if (!run && !town.loaded())
        return;
    cameraZoom_ += (cameraZoomTarget_ - cameraZoom_) * (1 - std::exp(-12 * dt));
    const Vector3 target = cameraFocus();
    camera.target = add(camera.target, mul(sub(target, camera.target), 1 - std::exp(-5 * dt)));
    camera.position = add(camera.target, cameraOffset());
}
bool Game::pointerOverControls() const {
    if(balanceOpen)return true;
    if(controlsOpen||buildOpen||journalVisible()||letterVisible())return true;
    const Vector2 mouse = GetMousePosition();
    const float x = mouse.x * 1280.0f / float(GetScreenWidth());
    const float y = mouse.y * 800.0f / float(GetScreenHeight());
    if (screen == Screen::Expedition && run && run->shopOpen)
        return true;
    if (x >= 1040 && x <= 1256 && y >= 2 && y <= 20)
        return true;
    if(screen==Screen::Hub&&x>=24&&x<=202&&y>=636&&y<=668)return true;
    if (screen == Screen::Hub)
        return questDialogueOpen()||sleeping()||(arrivalActive()&&x>=880&&x<=1256&&y>=30&&y<=257)||
               missionMenu || paused || (x >= 24 && x <= 410 && y >= 24 && y <= 122) ||
               (x >= 24 && x <= 700 && y >= 700) || (x >= 856 && x <= 1256 && y >= 646) ||
               (debug && debugPanelOpen && x >= 24 && x <= 480 && y >= 140 && y <= 245);
    const auto over=[&](Rectangle r){return CheckCollisionPointRec({x,y},r);};
    const bool live=run&&!paused&&!run->dead&&!run->rewardOpen&&!run->shopOpen;
    return (run&&(run->surveyTutorial||run->testimony())&&x>=964&&x<=1256&&y>=22&&y<=153)||
           (live&&(((reviewActives||reviewTrinkets)&&over(expeditionHud::categoryReview(reviewActives&&run->activeReviewCollected>=2&&run->roomClear)))||(run->powerupReview&&over(expeditionHud::categoryReview(run->roomClear&&run->powerupReview->collected==4)))||over(expeditionHud::Dynamite)||
               (run->heldTrinket&&over(expeditionHud::Trinket))||(run->activeItem&&over(expeditionHud::Active))||over(expeditionHud::Dodge)||over(expeditionHud::Pause)||over(expeditionHud::Tuning)||
               (ownedItemTypes()>0&&over(expeditionHud::items(ownedItemTypes())))))||
           (x >= 1040 && x <= 1256 && y >= 170 && y <= 362) ||
           (debug && debugPanelOpen && x >= 24 && x <= 539 && y >= 133 && y <= 592);
}
int Game::ownedItemTypes() const {
    int count=0;
    if(run)for(const auto &item:run->content->items())count+=run->itemStacks(item.id)>0;
    return count;
}
std::string Game::expeditionNotice() const {
    if(!run)return {};
    if(run->carriedBomb())return "LIT BOMB / THROW OR PLACE";
    if(const auto warning=run->demolitionWarning();!warning.empty())return warning;
    const bool visible=run->messageTime>0&&
        (run->messageKind==MessageKind::Notice||
         (run->messageKind==MessageKind::Debug&&debug&&debugPanelOpen));
    return visible?run->message:run->demolitionHint();
}
Game::Menu Game::menuContext() const {
    if(balanceOpen)return Menu::Balance;
    if(run&&run->dead&&canRetryExpedition())return Menu::Death;
    if(controlsOpen)return Menu::Controls;
    if(buildOpen)return Menu::Build;
    if(journalVisible())return Menu::Journal;
    if(letterVisible())return Menu::Letter;
    if(screen==Screen::Hub&&questDialogueOpen())return Menu::Dialogue;
    if(paused)return screen==Screen::Hub?Menu::HubPause:Menu::ExpeditionPause;
    if(screen==Screen::Hub&&missionMenu)return Menu::Missions;
    if(screen==Screen::Expedition&&run&&!run->dead) {
        if(run->shopOpen)return Menu::Shop;
        if(run->rewardOpen)return Menu::Reward;
    }
    if(screen==Screen::History)return Menu::History;
    if(screen==Screen::Summary)return Menu::Summary;
    return Menu::None;
}
std::vector<Action> Game::menuActions() const {
    const auto context=menuContext();
    if(context==Menu::Balance) {
        std::vector<Action> actions{Action::CloseBalance,Action::BalanceWorldTab,Action::BalanceShootingTab,Action::BalanceCombatTab,Action::BalanceEnemiesTab,Action::BalanceRewardsTab};
        if(balanceEnemiesOpen){actions.push_back(Action::BalanceChasersTab);actions.push_back(Action::BalancePooterTab);}
        if(balanceRewardsOpen)actions.push_back(Action::BalanceShopTab);
        if(balanceRewardsOpen&&balanceShopOpen&&!balanceShopStockOpen&&!balanceShopKeyOpen&&!balanceShopBombOpen) {
            actions.push_back(Action::BalanceShopRedHeartTab);actions.push_back(Action::BalanceShopSoulHeartTab);
        }
        const std::vector<Action> page=balanceRewardsOpen&&balanceShopOpen&&balanceShopStockOpen?
            std::vector<Action>{Action::BalanceClearHeartsTab,Action::BalanceRoomHeartsTab,Action::BalanceShopStockTab,Action::BalanceShopHeartTab,Action::BalanceShopKeyTab,Action::BalanceShopBombTab,
                Action::ToggleShopVariation,Action::ShopUpgradePriceDown,Action::ShopUpgradePriceUp,Action::ToggleSteamSaleDiscounts,Action::ResetShopUpgradePrice,Action::CycleShopCollectiblePool,Action::ApplyMapChanges}:
            balanceRewardsOpen&&balanceShopOpen?
            std::vector<Action>{Action::BalanceClearHeartsTab,Action::BalanceRoomHeartsTab,Action::BalanceShopStockTab,Action::BalanceShopHeartTab,Action::BalanceShopKeyTab,Action::BalanceShopBombTab,
                (balanceShopSoulHeartOpen||balanceShopBombOpen)?Action::ToggleShopVariation:balanceShopKeyOpen?Action::ToggleShopKey:Action::ToggleShopHeart,
                balanceShopSoulHeartOpen?Action::ShopSoulHeartPriceDown:balanceShopBombOpen?Action::ShopBombPriceDown:balanceShopKeyOpen?Action::ShopKeyPriceDown:Action::ShopHeartPriceDown,
                balanceShopSoulHeartOpen?Action::ShopSoulHeartPriceUp:balanceShopBombOpen?Action::ShopBombPriceUp:balanceShopKeyOpen?Action::ShopKeyPriceUp:Action::ShopHeartPriceUp,
                balanceShopSoulHeartOpen?Action::ResetShopSoulHeartPrice:balanceShopBombOpen?Action::ResetShopBombPrice:balanceShopKeyOpen?Action::ResetShopKeyPrice:Action::ResetShopHeartPrice,Action::ApplyMapChanges}:
            balanceRewardsOpen&&balanceRoomHeartsOpen?
            std::vector<Action>{Action::BalanceClearHeartsTab,Action::BalanceRoomHeartsTab,Action::RoomHeartsOff,Action::RoomHeartsSource,Action::RoomHeartsTest,Action::ApplyMapChanges}:
            balanceRewardsOpen?
            std::vector<Action>{Action::BalanceClearHeartsTab,Action::BalanceRoomHeartsTab,Action::ToggleRedHeartRewards,Action::ToggleCoinRewards,Action::ToggleChestRewards,Action::ToggleKeyRewards,Action::ToggleBombRewards,Action::RewardLuckDown,Action::RewardLuckUp,Action::ResetRewardLuck,Action::HeartAppearanceDown,Action::HeartAppearanceUp,Action::ResetHeartAppearance}:
            balanceCombatOpen&&balanceDoorsOpen?
            std::vector<Action>{Action::BalanceDamageHealthTab,Action::BalanceBombsTab,Action::BalanceDoorsTab,Action::DoorKeyCostDown,Action::DoorKeyCostUp,Action::ToggleSourceRoomLocks,Action::ApplyMapChanges,Action::ResetKeyedDoors}:
            balanceCombatOpen&&balanceBombsOpen?
            std::vector<Action>{Action::BalanceDamageHealthTab,Action::BalanceBombsTab,Action::BalanceDoorsTab,Action::BombFuseDown,Action::BombFuseUp,Action::BombRadiusDown,Action::BombRadiusUp,Action::BombDamageDown,Action::BombDamageUp,Action::BombSelfDamageDown,Action::BombSelfDamageUp,Action::ToggleRockBlastShielding,Action::ResetInventoryBombs}:
            balanceCombatOpen?
            std::vector<Action>{Action::BalanceDamageHealthTab,Action::BalanceBombsTab,Action::BalanceDoorsTab,Action::CombatDamageDown,Action::CombatDamageUp,Action::RegularHealthDown,Action::RegularHealthUp,Action::ResetCombat}:
            balanceEnemiesOpen&&balancePooterOpen?
            std::vector<Action>{Action::PooterMovementDown,Action::PooterMovementUp,Action::PooterShotDown,Action::PooterShotUp,Action::PooterDelayDown,Action::PooterDelayUp,Action::ResetPooter}:
            balanceEnemiesOpen?
            std::vector<Action>{Action::GaperMovementDown,Action::GaperMovementUp,Action::GaperMovementReset,Action::SpiderMovementDown,Action::SpiderMovementUp,Action::SpiderMovementReset}:
            balanceShootingOpen&&balanceTrinketOpen?
            std::vector<Action>{Action::BalanceTreasureTab,Action::CancerDown,Action::CancerUp,Action::WhipDown,Action::WhipUp,Action::ToggleTrinketRewards,Action::CycleTrinketBinding,Action::ResetTrinkets}:
            balanceShootingOpen&&balanceActiveOpen&&balanceBookOpen?
            std::vector<Action>{Action::BalanceTreasureTab,Action::BalanceActiveTab,Action::BookDurationDown,Action::BookDurationUp,Action::BookRechargeDown,Action::BookRechargeUp,Action::CycleActiveBinding,Action::ResetBook}:
            balanceShootingOpen&&balanceActiveOpen?
            std::vector<Action>{Action::BalanceTreasureTab,Action::BalanceBookTab,Action::YumHealingDown,Action::YumHealingUp,Action::YumRechargeDown,Action::YumRechargeUp,Action::CycleActiveBinding,Action::ResetYumHeart}:
            balanceShootingOpen&&balanceFamiliarOpen&&balanceHaloOpen?
            std::vector<Action>{Action::BalanceTreasureTab,Action::BalanceFamiliarTab,Action::HaloSpeedDown,Action::HaloSpeedUp,Action::HaloRadiusDown,Action::HaloRadiusUp,Action::HaloContactDown,Action::HaloContactUp,Action::ResetHalo}:
            balanceShootingOpen&&balanceFamiliarOpen?
            std::vector<Action>{Action::BalanceTreasureTab,Action::BalanceHaloTab,Action::BobbyMovementDown,Action::BobbyMovementUp,Action::BobbyIntervalDown,Action::BobbyIntervalUp,Action::BobbyDamageDown,Action::BobbyDamageUp,Action::BobbyShotDown,Action::BobbyShotUp,Action::ResetBrotherBobby}:
            balanceShootingOpen&&balanceTreasureOpen?
            std::vector<Action>{Action::BalanceTrinketTab,Action::BalanceActiveTab,Action::BalanceFamiliarTab,Action::ToggleTreasureUpgrade,Action::SadOnionDown,Action::SadOnionUp,Action::ResetSadOnion,Action::CycleTreasureCollectiblePool,Action::CricketHeadDown,Action::CricketHeadUp,Action::ResetCricketHead,Action::ApplyMapChanges}:
            balanceShootingOpen?
            std::vector<Action>{Action::BalanceTreasureTab,Action::TearsDown,Action::TearsUp,Action::ShotSpeedDown,Action::ShotSpeedUp,Action::RangeDown,Action::RangeUp,Action::ResetShooting}:
            std::vector<Action>{Action::SpeedDown,Action::SpeedUp,Action::DefaultZoomDown,Action::DefaultZoomUp,Action::DefaultZoomCurrent,Action::DefaultZoomReset,
                Action::RoomSizeDown,Action::RoomSizeUp,Action::RoomMinDown,Action::RoomMinUp,Action::RoomMaxDown,Action::RoomMaxUp,Action::RoomRangeAuto,
                Action::RouteLengthDown,Action::RouteLengthUp,Action::ApplyMapChanges,Action::ToggleSourceCombatRoom,Action::ResetBalance};
        actions.insert(actions.end(),page.begin(),page.end());
        actions.insert(actions.end(),{Action::ExportBalance,Action::LoadBalance,Action::RememberBalance,Action::EditBalancePath});
        return actions;
    }
    if(context==Menu::Death)return {Action::RetryExpedition};
    if(context==Menu::Controls)return {Action::CloseControls};
    if(context==Menu::Build)return {Action::CloseBuild};
    if(context==Menu::Journal) {
        if(journalEntries().size()>1)return {Action::CloseJournal,Action::JournalPrevious,Action::JournalNext};
        return {Action::CloseJournal};
    }
    if(context==Menu::Letter)return {Action::CloseLetter};
    if(context==Menu::Dialogue)return {Action::QuestNext,Action::QuestCancel};
    if(context==Menu::HubPause||context==Menu::ExpeditionPause) {
        std::vector<Action> result;result.reserve(32);
        result.push_back(Action::Resume);result.push_back(Action::Controls);result.push_back(Action::OpenBalance);
        if(screen==Screen::Hub) {
            result.insert(result.end(),{Action::EditTown,Action::Quit,Action::TravelHub,
                secondaryTravelHub(activeHub)==HubKind::Redstone?Action::TravelRedstone:Action::TravelFrontier});
        } else result.insert(result.end(),{Action::InspectBuild,Action::Retreat,Action::Quit});
        result.insert(result.end(),{Action::MasterDown,Action::MasterUp,Action::EffectsDown,Action::EffectsUp,
            Action::AmbienceDown,Action::AmbienceUp,Action::MusicDown,Action::MusicUp,Action::AudioMute,
            Action::AudioTest,Action::VegetationLess,Action::VegetationMore,Action::CycleVisualStyle});
        if(screen==Screen::Expedition) {
            result.push_back(Action::ToggleGroundDetail);
            if(debug&&run&&!run->dead)result.insert(result.end(),{Action::HealthDown,Action::HealthUp,
                Action::DamageDown,Action::DamageUp,Action::ResetPlayer});
        }
        result.push_back(Action::ToggleSandstorm);
        return result;
    }
    if(context==Menu::Missions) {
        std::vector<Action> result{Action::Launch,Action::ThemeSeeded,Action::ThemeMine,Action::ThemeCanyon,
            Action::NewSeed,Action::OpenBalance,Action::CycleExpeditionPacing};
        if(offeredTheme()==MissionTheme::Canyon)result.push_back(Action::ToggleCanyonRiver);
        result.push_back(Action::CloseMissions);
        return result;
    }
    if(context==Menu::Shop) {
        std::vector<Action> result;
        const int count=run->arena.rooms[size_t(run->room)].kind==RoomKind::Service?2:4;
        for(int i=0;i<count;++i)if(run->shopUnavailable(i).empty())result.push_back(Action(int(Action::BuyShop0)+i));
        result.push_back(Action::CloseShop);
        return result;
    }
    if(context==Menu::Reward)return {Action::Reward0,Action::Reward1,Action::CloseShop};
    if(context==Menu::History) {
        if(inspectedHistory())return {Action::Hub,Action::Previous,Action::Next};
        return {Action::Hub};
    }
    if(context==Menu::Summary) {
        if(canRetryExpedition())return {Action::RetryExpedition,Action::Hub,Action::History};
        return {Action::Hub,Action::History};
    }
    return {};
}
Action Game::keyboardFocus() const {
    const auto actions=menuActions();
    if(actions.empty())return Action::None;
    return keyboardMenu_==menuContext()&&std::find(actions.begin(),actions.end(),keyboardFocus_)!=actions.end()
        ?keyboardFocus_:actions.front();
}
bool Game::updateMenuInput() {
    const auto actions=menuActions();
    keyboardFocus_=keyboardFocus();
    keyboardMenu_=menuContext();
    if(actions.empty())return false;
    menuArrowsHeld_=true;
    resetPointerInput();
    if(balanceOpen&&IsKeyPressed(KEY_ESCAPE)) {perform(Action::CloseBalance);return true;}
    if(buildOpen&&(IsKeyPressed(KEY_ESCAPE)||IsKeyPressed(KEY_TAB))) {perform(Action::CloseBuild);return true;}
    if(controlsOpen&&IsKeyPressed(KEY_ESCAPE)) {perform(Action::CloseControls);return true;}
    if(paused&&!controlsOpen&&IsKeyPressed(KEY_H)) {perform(Action::Controls);return true;}
    // Preserve journal/history page shortcuts; Tab still visits their buttons.
    if(journalVisible()||screen==Screen::History) {
        if(IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_RIGHT)) {
            perform(journalVisible()?(IsKeyPressed(KEY_LEFT)?Action::JournalPrevious:Action::JournalNext):
                (IsKeyPressed(KEY_LEFT)?Action::Previous:Action::Next));
            return true;
        }
    }
    const auto pressed=[](int key){return IsKeyPressed(key)||IsKeyPressedRepeat(key);};
    int direction=0;
    if(pressed(KEY_TAB))direction=(IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT))?-1:1;
    else if(pressed(KEY_DOWN)||pressed(KEY_RIGHT))direction=1;
    else if(pressed(KEY_UP)||pressed(KEY_LEFT))direction=-1;
    if(direction) {
        const int at=int(std::find(actions.begin(),actions.end(),keyboardFocus_)-actions.begin());
        keyboardFocus_=actions[size_t((at+direction+int(actions.size()))%int(actions.size()))];
        return true;
    }
    if(IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_KP_ENTER)||IsKeyPressed(KEY_SPACE)) {
        perform(keyboardFocus_);
        return true;
    }
    return controlsOpen||buildOpen||balanceOpen;
}
std::optional<Vector2> Game::floorExitMarker() const {
    if(screen!=Screen::Expedition||!run||run->dead||run->room!=run->finalRoom()||!run->roomClear||
        paused||controlsOpen||buildOpen||balanceOpen||journalVisible()||letterVisible()||run->shopOpen||run->rewardOpen)return std::nullopt;
    const auto projected=GetWorldToScreen(add(run->arena.exit,{0,4.2f,0}),camera);
    // Clear of the title, minimap and bottom controls, including at close zoom.
    return Vector2{std::clamp(projected.x*1280.f/GetScreenWidth(),150.f,850.f),
                   std::clamp(projected.y*800.f/GetScreenHeight(),180.f,480.f)};
}
MissionTheme Game::offeredTheme() const {
    uint64_t seed = 0;
    const auto parsed = std::from_chars(seedText.data(), seedText.data() + seedText.size(), seed);
    if (parsed.ec != std::errc{} || parsed.ptr != seedText.data() + seedText.size())
        seed = 0;
    return resolveTheme(themeChoice, seed);
}
void Game::newSeed() {
    // Fresh offers each time the player returns, while retaining editable seeds
    // for replaying a particular mission layout.
    static Random seeds(uint64_t(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    seedText = std::to_string(seeds.next() % 1000000000);
}
void Game::updateHub(float dt) {
    if(updateQuest(dt))return;
    if (IsKeyPressed(KEY_F4)) {
        perform(Action::EditTown);
        return;
    }
    if (debug && IsKeyPressed(KEY_G)) {
        const bool set = campaign.data().world.flags.contains("something_followed");
        campaign.setFlag("something_followed", !set);
    }
    if (IsKeyPressed(KEY_H)) {
        perform(Action::History);
        return;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (missionMenu)
            perform(Action::CloseMissions);
        else {
            paused = !paused;
            town.stop();
            walkingToMission = false;
            walkingToQuest_=false;
        }
    }
    if (missionMenu) {
        cameraDragging_ = false;
        for (int c = GetCharPressed(); c; c = GetCharPressed())
            if (c >= '0' && c <= '9' && seedText.size() < 20)
                seedText.push_back(char(c));
        if (IsKeyPressed(KEY_BACKSPACE) && !seedText.empty())
            seedText.pop_back();
        if (IsKeyPressed(KEY_N))
            newSeed();
        if (IsKeyPressed(KEY_ENTER))
            perform(Action::Launch);
        return;
    }
    if (paused || !town.loaded()) {
        cameraDragging_ = false;
        return;
    }
    townObjects.update(std::min(dt, .1f), [&](Vector3 p) { return town.height(p); }, town.player.position);
    town.setMovingSolids(townObjects.solids());
    const bool over = pointerOverControls();
    updateCameraInput(dt);
    Vector3 forward = unit({camera.target.x - camera.position.x, 0, camera.target.z - camera.position.z});
    Vector3 right{-forward.z, 0, forward.x};
    Vector3 movement = add(mul(forward, float(IsKeyDown(KEY_W)) - float(IsKeyDown(KEY_S))),
                           mul(right, float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A))));
    if (length(movement) > .01f)
        walkingToMission = walkingToQuest_ = false;
    mouseMoveCooldown_ = std::max(0.0f, mouseMoveCooldown_ - dt);
    const bool leftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    const bool leftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    const Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
    if (!leftDown)
        leftCommand_ = LeftCommand::None;
    if(!over&&leftPressed&&arrivalActive()) {
        const auto marker=questMarker();
        const auto icon=questMarkerScreen();
        const auto mouse=GetMousePosition();
        const Vector2 normalized{mouse.x*1280.f/GetScreenWidth(),mouse.y*800.f/GetScreenHeight()};
        if(marker&&(CheckCollisionPointRec(normalized,{icon.x-110,icon.y-27,220,83})||
            GetRayCollisionBox(ray,{add(marker->position,{-.65f,0,-.65f}),add(marker->position,{.65f,2.6f,.65f})}).hit)) {
            requestQuestAction();leftCommand_=LeftCommand::Interact;
        }
    }
    if (!over && leftPressed && leftCommand_!=LeftCommand::Interact) {
        const auto p = town.mission;
        const bool board =
            GetRayCollisionBox(ray, {{p.x - 1, p.y, p.z - 1}, {p.x + 1, p.y + 3, p.z + 1}}).hit;
        leftCommand_ = board ? LeftCommand::Interact : LeftCommand::Move;
        if (board)
            perform(Action::Missions);
    }
    if (!over && leftDown && leftCommand_ == LeftCommand::Move && (leftPressed || mouseMoveCooldown_ <= 0)) {
        if (auto point = town.pickGround(ray)) {
            town.moveTo(*point);
            walkingToMission = false;
            walkingToQuest_=false;
        }
        mouseMoveCooldown_ = .1f;
    }
    if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_ENTER))
        perform(arrivalActive()?Action::QuestAction:Action::Missions);
    town.step(movement, std::min(dt, .1f));
    animals.update(std::min(dt, .1f), town);
    characters.update(std::min(dt, .1f), town);
    questCharacters.update(std::min(dt,.1f),town);
    if(walkingToQuest_) {
        const auto marker=questMarker();
        if(marker&&nearQuest(*marker))requestQuestAction();
        else if(!town.destination()) {walkingToQuest_=false;error="The objective's approach is blocked. Try a clear route closer to it.";}
    }
    if (walkingToMission && town.nearMission()) {
        walkingToMission = false;
        missionMenu = true;
        town.stop();
    }
    updateCamera(dt);
}
void Game::update(float dt, const SceneryPicker &pickScenery) {
    try {
        if(updateBalanceInput())return;
        if(updateMenuInput())return;
        if(journalVisible()) {
            resetPointerInput();checkpoint();
            if(IsKeyPressed(KEY_ESCAPE)||IsKeyPressed(KEY_ENTER))perform(Action::CloseJournal);
            else if(IsKeyPressed(KEY_LEFT))perform(Action::JournalPrevious);
            else if(IsKeyPressed(KEY_RIGHT))perform(Action::JournalNext);
            return;
        }
        if(letterVisible()) {
            resetPointerInput();checkpoint();
            if(IsKeyPressed(KEY_ESCAPE)||IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_SPACE))perform(Action::CloseLetter);
            return;
        }
        if(screen==Screen::Hub&&(questDialogueOpen()||sleeping())) {updateHub(dt);return;}
        if(screen==Screen::Expedition&&run&&!run->dead&&!paused&&!run->shopOpen&&!run->rewardOpen&&IsKeyPressed(KEY_TAB)) {
            perform(Action::InspectBuild);return;
        }
        if((screen==Screen::Hub||screen==Screen::Expedition)&&IsKeyPressed(KEY_J)) {perform(Action::ReadJournal);return;}
        if((screen==Screen::Hub||screen==Screen::Expedition)&&IsKeyPressed(KEY_L)) {perform(Action::ReadLetter);return;}
        debugInput();
        if (IsKeyPressed(KEY_K) && (screen == Screen::Hub || screen == Screen::Expedition))
            perform(Action::ToggleSandstorm);
        if (screen == Screen::Hub) {
            updateHub(dt);
            return;
        }
        if (screen == Screen::Summary) {
            cameraDragging_ = false;
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
                perform(Action::Hub);
            return;
        }
        if (screen == Screen::History) {
            cameraDragging_ = false;
            if (IsKeyPressed(KEY_ESCAPE))
                perform(Action::Hub);
            if (IsKeyPressed(KEY_LEFT))
                perform(Action::Previous);
            if (IsKeyPressed(KEY_RIGHT))
                perform(Action::Next);
            return;
        }
        if (!run)
            return;
        if (run->dead) {
            resetPointerInput();
            deathTime += std::min(dt, 0.1f);
            if (deathTime >= PlayerDeathSeconds)
                finish(EndReason::Death);
            return;
        }
        deathTime = 0;
        if (run->shopOpen && !paused) {
            resetPointerInput();
            if (IsKeyPressed(KEY_ESCAPE))
                perform(Action::CloseShop);
            else if (IsKeyPressed(KEY_ONE))
                perform(Action::BuyShop0);
            else if (IsKeyPressed(KEY_TWO))
                perform(Action::BuyShop1);
            else if (IsKeyPressed(KEY_THREE))
                perform(Action::BuyShop2);
            else if (IsKeyPressed(KEY_FOUR))
                perform(Action::BuyShop3);
            return;
        }
        if(run->rewardOpen&&IsKeyPressed(KEY_ESCAPE)&&!paused) {
            perform(Action::CloseShop);resetPointerInput();return;
        }
        if (IsKeyPressed(KEY_ESCAPE))
            paused = !paused;
        if (paused) {
            resetPointerInput();
            if (IsKeyPressed(KEY_T))
                perform(Action::Retreat);
            return;
        }
        if (run->rewardOpen) {
            resetPointerInput();
            if (IsKeyPressed(KEY_ONE))
                perform(Action::Reward0);
            if (IsKeyPressed(KEY_TWO))
                perform(Action::Reward1);
            return;
        }
        updateCameraInput(dt);
        Input input;
        // Camera-relative movement projected onto XZ, so W moves up the screen.
        Vector3 forward =
            unit({-camera.position.x + camera.target.x, 0, -camera.position.z + camera.target.z});
        Vector3 right{-forward.z, 0, forward.x};
        input.movement = add(mul(forward, float(IsKeyDown(KEY_W)) - float(IsKeyDown(KEY_S))),
                             mul(right, float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A))));
        if(!IsKeyDown(KEY_UP)&&!IsKeyDown(KEY_DOWN)&&!IsKeyDown(KEY_LEFT)&&!IsKeyDown(KEY_RIGHT))
            menuArrowsHeld_=false;
        const Vector3 arrowDirection = menuArrowsHeld_?Vector3{}:
            add(mul(forward, float(IsKeyDown(KEY_UP)) - float(IsKeyDown(KEY_DOWN))),
                mul(right, float(IsKeyDown(KEY_RIGHT)) - float(IsKeyDown(KEY_LEFT))));
        const bool overControls = pointerOverControls();
        input.aim = run->player.aim;
        Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
        const auto scenery = !overControls && pickScenery ? pickScenery(*run, camera, ray) : std::nullopt;
        Vector3 ground = input.aim;
        if (!overControls && std::abs(ray.direction.y) > 0.0001f) {
            float t = -ray.position.y / ray.direction.y;
            ground = t > 0 ? add(ray.position, mul(ray.direction, t)) : run->player.aim;
            // Aim through all foreground geometry. Keep the scenery hit below
            // for movement/interaction so a wall click still approaches its edge.
            input.aim = ground;
            if (t > 0 && scenery) {
                if (scenery->hit && scenery->distance < t) {
                    ground = scenery->point;
                    ground.y = 0;
                }
            } else if (t > 0 && run->arena.canyon) {
                const auto hit = run->arena.canyon->trace(ray.position, ground);
                if (hit.hit) {
                    ground = add(ray.position, mul(ray.direction, t * hit.t));
                    ground.y = 0;
                }
            }
        }
        auto pointed = overControls ? PointerTarget{} : pickTarget(*run, ray, scenery);
        bool exitMarkerHovered=false;
        if(const auto marker=floorExitMarker()) {
            const Vector2 mouse{GetMouseX()*1280.f/GetScreenWidth(),GetMouseY()*800.f/GetScreenHeight()};
            exitMarkerHovered=CheckCollisionPointRec(mouse,expeditionHud::exit(*marker));
            if(exitMarkerHovered) {
                pointed={};
                if(run->canUseFloorExit())pointed.objective=run->arena.exit;
            }
        }
        hoveredEnemy = pointed.enemy;
        if (const auto *enemy = run->findEnemy(hoveredEnemy))
            input.aim = enemy->position;
        const bool leftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        const bool leftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        const bool rightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        const bool dynamiteKey = IsKeyPressed(KEY_B) &&
                                 !(debug && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)));
        const bool dynamiteGesture = placeDynamiteQueued_ || dynamiteKey;
        if (dynamiteKey) {
            placeDynamiteQueued_ = true;
            moveQueued_.reset();
            doorQueued_.reset();
            fireQueued_.reset();
            leftCommand_ = LeftCommand::None;
            attackTarget_ = 0;
        }
        input.standStill = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        mouseMoveCooldown_ = std::max(0.0f, mouseMoveCooldown_ - dt);
        if (!leftDown) {
            leftCommand_ = LeftCommand::None;
            attackTarget_ = 0;
        }
        if (!overControls && leftPressed && !dynamiteGesture) {
            moveQueued_.reset();
            doorQueued_.reset();
            attackTarget_ = pointed.enemy;
            leftCommand_ = exitMarkerHovered                     ? LeftCommand::Interact
                           : run->carriedBomb()                    ? LeftCommand::Attack
                           : attackTarget_                         ? LeftCommand::Attack
                           : (pointed.objective || pointed.door) ? LeftCommand::Interact
                                                                 : LeftCommand::Move;
            if (leftCommand_ == LeftCommand::Interact && !input.standStill && !rightDown) {
                if (pointed.door)
                    doorQueued_ = pointed.door;
                else
                    moveQueued_ = pointed.objective;
            }
        }
        if (!overControls && !dynamiteGesture) {
            if (rightDown || (leftDown && input.standStill)) {
                // The prototype has one weapon: RMB also force-fires the revolver.
                input.fire = true;
            } else if (leftDown && leftCommand_ == LeftCommand::Attack) {
                // Lock the clicked enemy until release, including when the cursor moves.
                // Once it dies, keep the attack gesture from turning into a movement order.
                if(run->carriedBomb())input.fire=true;
                else if (const auto *enemy = run->findEnemy(attackTarget_); enemy && enemy->alive) {
                    input.aim = enemy->position;
                    input.fire = true;
                }
            } else if (leftDown && leftCommand_ == LeftCommand::Move && !input.standStill &&
                       (leftPressed || mouseMoveCooldown_ <= 0)) {
                moveQueued_ = ground;
                mouseMoveCooldown_ = 0.1f;
            }
        }
        if (!dynamiteGesture && length(arrowDirection) > .01f) {
            // Arrows take aim priority while held, even with the cursor over the HUD.
            input.aimDirection = unit(arrowDirection);
            input.fire = true;
        }
        if(IsKeyPressed(KEY_SPACE)&&!input.aimDirection&&!leftDown&&!rightDown)
            dodgeAimQueued_=run->player.facing;
        if(dodgeAimQueued_&&!input.aimDirection)input.aimDirection=dodgeAimQueued_;
        const bool arrowPressed = input.aimDirection &&
            (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT));
        if (input.fire && (arrowPressed || leftPressed || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))) {
            fireQueued_ = FireCommand{input.aim, input.aimDirection}; // Preserve short taps between ticks.
            standStillQueued_ = input.standStill;
        }
        if (!input.fire && fireQueued_) {
            input.aim = fireQueued_->aim;
            input.aimDirection = fireQueued_->direction;
        }
        input.fire = input.fire || fireQueued_.has_value();
        input.standStill = input.standStill || standStillQueued_;
        if (input.fire || input.standStill) {
            moveQueued_.reset();
            doorQueued_.reset();
        }
        dodgeQueued_ = dodgeQueued_ || IsKeyPressed(KEY_SPACE);
        interactQueued_ = interactQueued_ || IsKeyPressed(KEY_E) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER);
        input.moveTarget = moveQueued_;
        input.doorTarget = doorQueued_;
        input.dodge = dodgeQueued_;
        input.interact = interactQueued_;
        activeQueued_=activeQueued_||IsKeyPressed(balancePreset.yumHeart.binding==1?KEY_X:balancePreset.yumHeart.binding==2?KEY_Z:KEY_C);
        input.useActive=activeQueued_;
        trinketQueued_=trinketQueued_||IsKeyPressed(balancePreset.trinkets.binding==1?KEY_Y:KEY_U);
        input.dropTrinket=trinketQueued_;
        input.placeDynamite = placeDynamiteQueued_;
        accumulator += std::min(dt, 0.1f) * (slow ? 0.2f : 1.0f);
        while (accumulator >= Tick) {
            run->step(input);
            accumulator -= Tick;
            input.useActive=activeQueued_=false;
            input.dropTrinket=trinketQueued_=false;
            input.dodge = input.interact = false;
            input.placeDynamite = placeDynamiteQueued_ = false;
            input.moveTarget.reset();
            input.doorTarget.reset();
            moveQueued_.reset();
            doorQueued_.reset();
            fireQueued_.reset();
            standStillQueued_ = false;
            dodgeQueued_ = interactQueued_ = false;
            dodgeAimQueued_.reset();
            if (run->finished || run->dead || run->rewardOpen || run->shopOpen || run->letterOpen ||
                run->storyOpen!=StoryRoom::None || run->floorExitRequested)
                break;
        }
        checkpoint();
        if(run->floorExitRequested&&run->advanceFloor()) {
            ++audioContext;audioCues.clear();resetPointerInput();accumulator=0;snapCamera();checkpoint();
        }
        if (run->finished && !run->dead)
            finish(EndReason::Victory);
        updateCamera(dt);
    } catch (const std::exception &e) {
        error = e.what();
        paused = true;
    }
}
} // namespace dw
