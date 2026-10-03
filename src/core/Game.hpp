#pragma once
#include "combat/Simulation.hpp"
#include "core/VisualSettings.hpp"
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
    DynamiteMode,
    VegetationLess,
    VegetationMore,
    ToggleGroundDetail,
    ToggleCanyonRiver,
    ToggleSandstorm,
    QuestAction,
    QuestNext,
    QuestCancel,
    ReadLetter,
    CloseLetter,
    ReadJournal,
    CloseJournal,
    JournalPrevious,
    JournalNext
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
    bool dynamiteArmed = false;
    bool dynamiteThrowMode = false;
    AudioSettings audioSettings;
    VisualSettings visualSettings;
    bool sandstorm = false; // Optional weather trial; lasts only for this session.
    MusicScene musicScene() const;
    AudioStatus audioStatus = AudioStatus::Disabled;
    AudioCueQueue audioCues;
    uint64_t audioContext = 0;
    std::string seedText = "1866", error;
    ThemeChoice themeChoice = ThemeChoice::Canyon;
    MissionTheme offeredTheme() const;
    bool quit = false, paused = false, slow = false, debug = true, collisionDebug = false, resetArmed = false;
    bool debugPanelOpen = false;
    int selectedItem = 0, historyIndex = 0, selectedFlag = 0;
    int selectedMonster = 0;
    float playerHealth = StartingHealth, playerDamage = RevolverDamage;
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

  private:
    enum class LeftCommand { None, Move, Attack, Interact };
    LeftCommand leftCommand_ = LeftCommand::None;
    EntityId attackTarget_ = 0;
    bool dodgeQueued_ = false, interactQueued_ = false;
    bool standStillQueued_ = false;
    bool cancelFireHeld_ = false;
    std::optional<Vector3> moveQueued_, fireQueued_;
    std::optional<Vector3> dynamiteQueued_;
    bool placeDynamiteQueued_ = false;
    std::optional<std::pair<int, int>> doorQueued_;
    float mouseMoveCooldown_ = 0;
    float cameraZoom_ = 100.0f / 160.0f, cameraZoomTarget_ = cameraZoom_;
    float cameraYaw_ = 0, cameraPitch_ = 0;
    bool cameraDragging_ = false;
    Vector2 cameraDragPosition_{};
    Vector3 cameraOffset() const;
    Vector3 cameraFocus() const;
    void updateCameraInput();
    void snapCamera();
    void resetPointerInput();
    void debugInput();
    void checkpoint();
    void updateHub(float dt);
    void newSeed();
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
