#pragma once
#include "combat/Simulation.hpp"
#include "world/HubWorld.hpp"
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
    EditTown
};
class Game {
  public:
    explicit Game(const std::filesystem::path &save);
    CampaignStore campaign;
    std::unique_ptr<Simulation> run;
    HubWorld town;
    bool missionMenu = false, walkingToMission = false;
    bool editorRequested = false;
    Screen screen = Screen::Hub;
    RunSummary lastSummary;
    Camera3D camera{};
    std::string seedText = "1866", error;
    bool quit = false, paused = false, slow = false, debug = true, collisionDebug = false, resetArmed = false;
    bool debugPanelOpen = false;
    int selectedItem = 0, historyIndex = 0, selectedFlag = 0;
    float accumulator = 0;
    float deathTime = 0;
    EntityId hoveredEnemy = 0;
    void update(float dt);
    void perform(Action action);
    void launch();
    void finish(EndReason reason);
    void close();
    const RunSummary *inspectedHistory() const;
    void updateCamera(float dt);
    bool pointerOverControls() const;

  private:
    enum class LeftCommand { None, Move, Attack, Interact };
    LeftCommand leftCommand_ = LeftCommand::None;
    EntityId attackTarget_ = 0;
    bool dodgeQueued_ = false, interactQueued_ = false;
    bool standStillQueued_ = false;
    std::optional<Vector3> moveQueued_, fireQueued_;
    std::optional<std::pair<int, int>> doorQueued_;
    float mouseMoveCooldown_ = 0;
    float cameraZoom_ = 1, cameraZoomTarget_ = 1;
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
};
} // namespace dw
