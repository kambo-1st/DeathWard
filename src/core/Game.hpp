#pragma once
#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "core/VisualSettings.hpp"
#include "core/VisualStyle.hpp"
#include "world/Animals.hpp"
#include "world/HubDefinition.hpp"
#include "world/HubWorld.hpp"
#include "world/ObjectAnimation.hpp"
#include "world/TownCharacters.hpp"
#include "world/ArrivalQuest.hpp"
#include <memory>

namespace dw {
enum class Screen { Hub, Expedition, Summary, History };
enum class Action {
    None,
    Launch,
    History,
    Hub,
    Pause,
    Resume,
    Dodge,
    Interact,
    Retreat,
    Quit,
    Reward0,
    Reward1,
    Previous,
    Next,
    Reset,
    Missions,
    CloseMissions,
    NewSeed,
    EditTown,
    ThemeSeeded,
    ThemeMine,
    ThemeCanyon,
    CycleExpeditionPacing,
    TravelHub,
    TravelFrontier,
    TravelRedstone,
    HealthDown,
    HealthUp,
    DamageDown,
    DamageUp,
    ResetPlayer,
    MasterDown,
    MasterUp,
    EffectsDown,
    EffectsUp,
    AmbienceDown,
    AmbienceUp,
    MusicDown,
    MusicUp,
    AudioMute,
    AudioTest,
    BuyShop0,
    BuyShop1,
    BuyShop2,
    BuyShop3,
    CloseShop,
    Dynamite,
    DynamiteMode, // Retired; keep the action ID stable for older automation.
    VegetationLess,
    VegetationMore,
    ToggleGroundDetail,
    ToggleCanyonRiver,
    ToggleSandstorm,
    CycleVisualStyle,
    QuestAction,
    QuestNext,
    QuestCancel,
    ReadLetter,
    CloseLetter,
    ReadJournal,
    CloseJournal,
    JournalPrevious,
    JournalNext,
    Controls,
    CloseControls,
    InspectBuild,
    CloseBuild,
    OpenBalance,
    CloseBalance,
    BalanceWorldTab,
    BalanceShootingTab,
    BalanceEnemiesTab,
    BalanceCombatTab, CombatDamageDown, CombatDamageUp, RegularHealthDown, RegularHealthUp, ResetCombat,
    BalanceChasersTab,
    BalancePooterTab,
    PooterMovementDown, PooterMovementUp, PooterShotDown, PooterShotUp, PooterDelayDown, PooterDelayUp, ResetPooter,
    GaperMovementDown,
    GaperMovementUp,
    GaperMovementReset,
    SpiderMovementDown,
    SpiderMovementUp,
    SpiderMovementReset,
    TearsDown,
    TearsUp,
    ShotSpeedDown,
    ShotSpeedUp,
    RangeDown,
    RangeUp,
    ResetShooting,
    RoomRangeAuto,
    RoomMinDown,
    RoomMinUp,
    RoomMaxDown,
    RoomMaxUp,
    RoomSizeDown,
    RoomSizeUp,
    RouteLengthDown,
    RouteLengthUp,
    ApplyMapChanges,
    ToggleSourceCombatRoom,
    BalanceRewardsTab, BalanceRoomHeartsTab, BalanceClearHeartsTab,
    RoomHeartsOff, RoomHeartsSource, RoomHeartsTest,
    ToggleRedHeartRewards, ToggleCoinRewards, ToggleChestRewards, ToggleKeyRewards, ToggleBombRewards,
    RewardLuckDown,
    RewardLuckUp,
    ResetRewardLuck, HeartAppearanceDown, HeartAppearanceUp, ResetHeartAppearance,
    DefaultZoomDown,
    DefaultZoomUp,
    DefaultZoomCurrent,
    DefaultZoomReset,
    SpeedDown,
    SpeedUp,
    ResetBalance,
    ExportBalance,
    LoadBalance,
    RememberBalance,
    EditBalancePath,
    RetryExpedition,
    BalanceDamageHealthTab, BalanceBombsTab, BombFuseDown, BombFuseUp,
    BombRadiusDown, BombRadiusUp, BombDamageDown, BombDamageUp,
    BombSelfDamageDown, BombSelfDamageUp, ResetInventoryBombs, ToggleRockBlastShielding,
    BalanceDoorsTab, DoorKeyCostDown, DoorKeyCostUp, ResetKeyedDoors, ToggleSourceRoomLocks, BalanceTreasureTab, ToggleTreasureUpgrade, SadOnionDown, SadOnionUp, ResetSadOnion, BalanceShopTab, ToggleShopHeart, ShopHeartPriceDown, ShopHeartPriceUp, ResetShopHeartPrice, BalanceShopHeartTab, BalanceShopKeyTab, ToggleShopKey, ShopKeyPriceDown, ShopKeyPriceUp, ResetShopKeyPrice, BalanceShopStockTab, ToggleShopVariation, ToggleSteamSaleDiscounts, ShopUpgradePriceDown, ShopUpgradePriceUp, ResetShopUpgradePrice, BalanceShopBombTab, ShopBombPriceDown, ShopBombPriceUp, ResetShopBombPrice, BalanceShopRedHeartTab, BalanceShopSoulHeartTab, ShopSoulHeartPriceDown, ShopSoulHeartPriceUp, ResetShopSoulHeartPrice, CycleShopCollectiblePool, CycleTreasureCollectiblePool, CricketHeadDown, CricketHeadUp, ResetCricketHead, BalanceFamiliarTab, BobbyMovementDown, BobbyMovementUp, BobbyIntervalDown, BobbyIntervalUp, BobbyDamageDown, BobbyDamageUp, BobbyShotDown, BobbyShotUp, ResetBrotherBobby, BalanceActiveTab, YumHealingDown, YumHealingUp, YumRechargeDown, YumRechargeUp, CycleActiveBinding, ResetYumHeart, UseActiveItem, BalanceTrinketTab, CancerDown, CancerUp, ToggleTrinketRewards, CycleTrinketBinding, ResetTrinkets, DropTrinket, ReviewPowerupFight, ReviewPowerupBoss, WhipDown, WhipUp, BalanceHaloTab, HaloSpeedDown, HaloSpeedUp, HaloRadiusDown, HaloRadiusUp, HaloContactDown, HaloContactUp, ResetHalo, BalanceBookTab, BookDurationDown, BookDurationUp, BookRechargeDown, BookRechargeUp, ResetBook, BalanceMonstroTab, ToggleMonstro, MonstroHealthDown, MonstroHealthUp, MonstroMovementDown, MonstroMovementUp, MonstroShotDown, MonstroShotUp, ResetMonstro, ToggleDuke, SelectLegacyBoss
};
class Game {
  public:
    using SceneryPicker =
        std::function<std::optional<RayCollision>(const Simulation &, const Camera3D &, Ray)>;
    explicit Game(const std::filesystem::path &save, HubKind initialHub = HubKind::BlackCreek);
    CampaignStore campaign;
    std::unique_ptr<Simulation> run;
    HubWorld town;
    ObjectAnimationSystem townObjects;
    Animals animals;
    TownCharacters characters;
    TownCharacters questCharacters;
    ArrivalStage arrivalStage() const { return ArrivalQuest::stage(campaign.data().world); }
    bool arrivalActive() const { return activeHub==HubKind::Redstone&&arrivalStage()!=ArrivalStage::None; }
    std::optional<QuestMarker> questMarker() const;
    Vector2 questMarkerScreen() const;
    const QuestLine *questLine() const;
    bool questDialogueOpen() const { return !questDialogue_.empty(); }
    bool questLastLine() const { return questLine_+1>=questDialogue_.size(); }
    bool walkingToQuest() const { return walkingToQuest_; }
    bool sleeping() const { return sleepTime_>=0; }
    bool readingLetter = false;
    bool letterVisible() const { return readingLetter||(run&&run->letterOpen); }
    bool journalOpen = false;
    bool controlsOpen = false;
    bool buildOpen = false;
    bool balanceOpen = false, balancePathEditing = false, balanceShootingOpen = false;
    bool balanceBookOpen = false, balanceHaloOpen = false, balanceFamiliarOpen = false, balanceActiveOpen = false, balanceTrinketOpen = false;
    bool balanceMonstroOpen=false;
    bool balanceEnemiesOpen = false, balancePooterOpen = false, balanceCombatOpen = false, balanceRewardsOpen = false, balanceRoomHeartsOpen = false, balanceTreasureOpen = false, balanceShopOpen=false, balanceShopKeyOpen=false, balanceShopStockOpen=false, balanceShopBombOpen=false, balanceShopSoulHeartOpen=false;
    bool balanceBombsOpen=false, balanceDoorsOpen=false;
    BalancePreset balancePreset, balanceDraft;
    std::optional<BalancePreset> nextBalancePreset;
    std::filesystem::path balanceDirectory;
    std::string balanceFile, balanceNotice;
    void setPlayerSpeed(float speed);
    void setShooting(float tears, float shotSpeed, float rangeTiles);
    void resetShooting();
    void setGaperMovement(float multiplier);
    void setSpiderMovement(float multiplier);
    void setCombatBalance(float damage,float regularHealth);
    void setPooterTuning(float movement,float shotSpeed,float interval);
    void setInventoryBombs(InventoryBombTuning tuning);
    void setDefaultZoom(float percent);
    void setRoomSize(float scale);
    void setRouteLength(float scale);
    bool hasPendingMapChanges() const;
    void applyMapChanges();
    void setSourceCombatRoom(bool enabled);
    void setRoomHeartLayouts(int mode);
    void setRedHeartAppearanceSpeed(float speed);
    void setRedHeartRewards(bool enabled,float luck);
    void setRoomSizeRange(int minimum, int maximum);
    std::pair<int,int> roomSizeRange() const;
    void resetBalance();
    void exportBalancePreset();
    void loadBalancePreset(const std::filesystem::path &path);
    void rememberBalancePreset();
    bool canRetryExpedition() const;
    void retryExpedition();
    int journalIndex = 0;
    bool journalVisible() const { return journalOpen||(run&&run->storyOpen!=StoryRoom::None); }
    std::vector<StoryEvidence> journalEntries() const;
    float sleepFade() const;
    bool reloadTownObjects();
    HubKind activeHub = HubKind::BlackCreek;
    std::filesystem::path hubDirectory() const;
    bool selectHub(HubKind hub);
    bool missionMenu = false, walkingToMission = false;
    bool editorRequested = false;
    Screen screen = Screen::Hub;
    RunSummary lastSummary;
    Camera3D camera{};
    AudioSettings audioSettings;
    VisualSettings visualSettings;
    VisualStyle visualStyle = VisualStyle::Original;
    bool sandstorm = false; // Optional weather trial; lasts only for this session.
    MusicScene musicScene() const;
    AudioStatus audioStatus = AudioStatus::Disabled;
    AudioCueQueue audioCues;
    uint64_t audioContext = 0;
    std::string seedText = "1866", error;
    bool reviewActives=false,reviewTrinkets=false;
    bool reviewPowerups=false; // Labelled category setup; ordinary consumers and encounters.
    std::optional<int> reviewRoomIndex; // Zero-based generated room; normal health/damage.
    bool reviewShopStock=false; // Direct bounded stock review with labelled test funds.
    bool reviewShopKeyPurchase=false; // Explicit key/heart review: eight coins and zero keys.
    bool reviewShopPurchase=false; // Explicit review start: shop, two red hearts, at least three coins.
    std::optional<int> reviewSourceRoomTemplate; // Launch/retry aid; not a balance override.
    ThemeChoice themeChoice = ThemeChoice::Canyon;
    ExpeditionPacing expeditionPacing = ExpeditionPacing::Compact;
    MissionTheme offeredTheme() const;
    bool quit = false, paused = false, slow = false, debug = true, collisionDebug = false, resetArmed = false;
    bool debugPanelOpen = false;
    int selectedItem = 0, historyIndex = 0, selectedFlag = 0;
    int selectedMonster = 0;
    float playerHealth = StartingHealth, playerDamage = BalancePreset::ReferenceDamage * CombatHealthUnitsPerSource;
    float accumulator = 0;
    float deathTime = 0;
    EntityId hoveredEnemy = 0;
    void update(float dt, const SceneryPicker &pickScenery = {});
    void perform(Action action);
    void launch(bool freeMission = false);
    void finish(EndReason reason);
    void close();
    const RunSummary *inspectedHistory() const;
    void updateCamera(float dt);
    float cameraZoomPercent() const {
        return 100.0f / cameraZoom_;
    }
    bool pointerOverControls() const;
    Action keyboardFocus() const;
    // Logical 1280 x 800 coordinates, shared by rendering and mouse picking.
    std::optional<Vector2> floorExitMarker() const;
    int ownedItemTypes() const;
    std::string expeditionNotice() const;

  private:
    enum class LeftCommand { None, Move, Attack, Interact };
    LeftCommand leftCommand_ = LeftCommand::None;
    EntityId attackTarget_ = 0;
    bool dodgeQueued_ = false, interactQueued_ = false;
    bool standStillQueued_ = false;
    Action keyboardFocus_ = Action::None;
    enum class Menu { None, Controls, Build, Journal, Letter, Dialogue, HubPause, ExpeditionPause, Missions, Shop, Reward, History, Summary, Balance, Death };
    Menu keyboardMenu_ = Menu::None;
    bool menuArrowsHeld_ = false;
    Menu menuContext() const;
    std::vector<Action> menuActions() const;
    bool updateMenuInput();
    struct FireCommand {
        Vector3 aim;
        std::optional<Vector3> direction;
    };
    std::optional<Vector3> dodgeAimQueued_;
    std::optional<Vector3> moveQueued_;
    std::optional<FireCommand> fireQueued_;
    bool placeDynamiteQueued_ = false, activeQueued_ = false, trinketQueued_ = false;
    std::optional<std::pair<int, int>> doorQueued_;
    float mouseMoveCooldown_ = 0;
    float cameraZoom_ = 100.0f / BalancePreset::ReferenceZoom, cameraZoomTarget_ = cameraZoom_;
    float cameraYaw_ = 0, cameraPitch_ = 0;
    bool cameraDragging_ = false;
    Vector2 cameraDragPosition_{};
    Vector3 cameraOffset() const;
    Vector3 cameraFocus() const;
    void updateCameraInput(float dt);
    void snapCamera();
    void resetPointerInput();
    void debugInput();
    void checkpoint();
    void updateHub(float dt);
    void newSeed();
    struct RetrySetup {
        uint64_t seed;
        MissionTheme theme;
        bool river, tutorial;
        WitnessAccount account;
        ExpeditionPacing pacing;
    };
    std::optional<RetrySetup> retrySetup_;
    std::string balanceRestoreError_, balancePathBeforeEdit_;
    void initializeBalance();
    void applyBalance(BalancePreset preset);
    void useDefaultZoom();
    void archiveBalance(const BalancePreset &preset) const;
    void startExpedition(std::unique_ptr<Simulation> candidate, bool retry = false);
    RunSummary configuredSummary() const;
    bool updateBalanceInput();
    ArrivalQuest arrival_;
    std::vector<QuestLine> questDialogue_;
    size_t questLine_ = 0;
    ArrivalStage conversationStage_ = ArrivalStage::None;
    bool walkingToQuest_ = false;
    float sleepTime_ = -1;
    void configureArrival(const TownDocument &document);
    void requestQuestAction();
    void nextQuestLine();
    bool updateQuest(float dt);
    bool nearQuest(const QuestMarker &marker) const;
};
} // namespace dw
