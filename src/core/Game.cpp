#include "core/Game.hpp"
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
    const size_t firstWall = scenery ? run.arena.boundaryWalls.size() + run.arena.obstacles.size() : 0;
    for (size_t i = firstWall; i < run.arena.walls.size(); ++i) {
        const auto &wall = run.arena.walls[i];
        const auto hit = GetRayCollisionBox(ray, {wall.min, wall.max});
        if (hit.hit)
            nearest = std::min(nearest, hit.distance);
    }
    auto hits = [&](Vector3 p, float radius, float height) {
        const auto hit =
            GetRayCollisionBox(ray, {{p.x - radius, 0, p.z - radius}, {p.x + radius, height, p.z + radius}});
        if (!hit.hit || hit.distance >= nearest)
            return false;
        nearest = hit.distance;
        return true;
    };
    auto objective = [&](Vector3 p, float radius, float height) {
        if (hits(p, radius, height))
            result.objective = p;
    };
    if (!run.rescued)
        objective(run.arena.miners, 1.7f, 2.0f);
    if (!run.altarDestroyed)
        objective(run.arena.altar, 1.0f, 2.9f);
    if (run.room == Simulation::FinalRoom && run.roomClear)
        objective(run.arena.exit, 2.0f, 3.2f);
    if (run.arena.rooms[size_t(run.room)].kind == RoomKind::Power && !run.rooms[size_t(run.room)].rewardTaken)
        objective(run.arena.rooms[size_t(run.room)].objective, 1.2f, 2.4f);
    for (const auto &key : run.arena.keys)
        if (!key.collected && run.rooms[size_t(key.room)].cleared)
            objective(key.position, 1.0f, 2.0f);
    const float objectiveDistance = nearest;
    if (run.roomClear)
        for (size_t i = 0; i < run.arena.passages.size(); ++i)
            for (int side = 0; side < 2; ++side)
                if (hits(run.arena.doorApproach(int(i), side), 2.5f, 3.2f)) {
                    result.objective.reset();
                    result.door = std::pair{int(i), side};
                }
    // Visible pickups and the shopkeeper take priority over passage click areas.
    // Keep opaque scenery and actual interaction objects in front of them solid.
    nearest = objectiveDistance;
    if (run.arena.shopRoom >= 0 && hits(run.arena.rooms[size_t(run.arena.shopRoom)].objective, .9f, 2.8f)) {
        result.objective = run.arena.rooms[size_t(run.arena.shopRoom)].objective;
        result.door.reset();
    }
    for (const auto &coin : run.moneyPickups)
        if (hits(coin.position, .65f, 1.1f)) {
            result.objective = coin.position;
            result.door.reset();
        }
    // Aim at enemy bodies (including their occlusion outlines) through scenery.
    // Only the camera ray ignores cover; the fired projectile still collides.
    nearest = std::numeric_limits<float>::infinity();
    for (const auto &enemy : run.enemies) {
        if (enemy.alive && !enemy.friendly && enemy.state != EnemyState::Buried &&
            hits(enemy.position, enemy.radius, enemy.kind == EnemyKind::Boss ? 3.4f : 2.5f)) {
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
}
std::filesystem::path Game::hubDirectory() const {
    return TownScene::assetDirectory(activeHub);
}
MusicScene Game::musicScene() const {
    if (screen == Screen::Expedition && run) {
        if (run->dead)
            return MusicScene::Defeat;
        if (!run->roomClear && run->roomThreats() > 0)
            return run->room == Simulation::FinalRoom || run->boss() ? MusicScene::Boss : MusicScene::Combat;
        return run->arena.theme == MissionTheme::Canyon ? MusicScene::Canyon : MusicScene::Mine;
    }
    if (screen == Screen::Summary) {
        if (lastSummary.reason == EndReason::Victory)
            return MusicScene::Victory;
        if (lastSummary.reason == EndReason::Death)
            return MusicScene::Defeat;
    }
    return activeHub == HubKind::BlackCreek ? MusicScene::Town : MusicScene::Frontier;
}
bool Game::reloadTownObjects() {
    TownDocument document;
    if (!document.load(hubDirectory() / "town.scene", error))
        return false;
    townObjects.reset(document);
    return true;
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
    ++audioContext;
    audioCues.clear();
    activeHub = hub;
    paused = missionMenu = walkingToMission = false;
    error.clear();
    resetPointerInput();
    snapCamera();
    return true;
}
void Game::launch() {
    uint64_t seed = 0;
    auto result = std::from_chars(seedText.data(), seedText.data() + seedText.size(), seed);
    if (result.ec != std::errc{} || result.ptr != seedText.data() + seedText.size()) {
        error = "Enter a whole-number seed (up to 20 digits).";
        return;
    }
    const auto theme = resolveTheme(themeChoice, seed);
    auto candidate =
        std::make_unique<Simulation>(seed, campaign.data().nextRunId, campaign.data().world, theme);
    candidate->tunePlayer(playerHealth, playerDamage);
    campaign.begin(seed, missionTheme(theme).title);
    run = std::move(candidate);
    ++audioContext;
    audioCues.clear();
    missionMenu = walkingToMission = false;
    town.stop();
    screen = Screen::Expedition;
    deathTime = 0;
    paused = false;
    accumulator = 0;
    error.clear();
    resetArmed = false;
    cameraZoom_ = cameraZoomTarget_;
    snapCamera();
    resetPointerInput();
}
void Game::checkpoint() {
    if (run && run->checkpointNeeded) {
        campaign.checkpoint(run->summary());
        run->checkpointNeeded = false;
    }
}
void Game::finish(EndReason reason) {
    if (!run)
        return;
    lastSummary = campaign.resolve(run->summary(), reason);
    run.reset();
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
    dynamiteArmed = cancelFireHeld_ = false;
    dynamiteQueued_.reset();
    placeDynamiteQueued_ = false;
    cameraDragging_ = false;
    leftCommand_ = LeftCommand::None;
    attackTarget_ = hoveredEnemy = 0;
    dodgeQueued_ = interactQueued_ = standStillQueued_ = false;
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
        switch (action) {
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
                    health -= 25;
                if (action == Action::HealthUp)
                    health += 25;
                if (action == Action::DamageDown)
                    damage -= 4;
                if (action == Action::DamageUp)
                    damage += 4;
                if (action == Action::ResetPlayer) {
                    health = StartingHealth;
                    damage = RevolverDamage;
                }
                run->tunePlayer(health, damage);
                playerHealth = run->player.baseHealth;
                playerDamage = run->player.shotDamage;
                run->announce("PLAYER / base health " + std::to_string(int(playerHealth)) +
                              " / shot damage " + std::to_string(int(playerDamage)));
            }
            break;
        case Action::TravelHub:
            selectHub(activeHub == HubKind::BlackCreek ? HubKind::Frontier : HubKind::BlackCreek);
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
            paused = true;
            if (screen == Screen::Hub) {
                town.stop();
                walkingToMission = false;
            }
            break;
        case Action::Resume:
            paused = false;
            break;
        case Action::Dodge:
            if (run && !paused && !run->rewardOpen && !run->shopOpen)
                dodgeQueued_ = true;
            break;
        case Action::Dynamite:
            if (run && !paused && !run->dead && !run->rewardOpen && !run->shopOpen) {
                if (!dynamiteThrowMode) {
                    resetPointerInput();
                    placeDynamiteQueued_ = true;
                    break;
                }
                const bool arm = !dynamiteArmed && run->dynamite > 0;
                resetPointerInput();
                dynamiteArmed = arm;
                if (arm)
                    run->announce("Choose where to throw. Cancel with Escape or the right button.");
                else if (run->dynamite == 0)
                    run->announce("Out of dynamite. The shop sells a refill pack.");
            }
            break;
        case Action::DynamiteMode:
            if (run && !paused && !run->dead && !run->rewardOpen && !run->shopOpen) {
                resetPointerInput();
                dynamiteThrowMode = !dynamiteThrowMode;
            }
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
        selectedItem = (selectedItem + ItemCount - 1) % ItemCount;
    if (IsKeyPressed(KEY_RIGHT_BRACKET))
        selectedItem = (selectedItem + 1) % ItemCount;
    if (!run)
        return;
    const bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    if (shift && IsKeyPressed(KEY_B)) {
        run->dynamite = MaxDynamite;
        run->dynamiteCooldown = 0;
        run->announce("CHEAT / dynamite refilled");
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
        run->announce("TEST ENEMY / " + monsterIdText(d.id) + " / " + d.name);
    }
    if (IsKeyPressed(KEY_F4) && shift)
        run->spawnMonsterDebug(monsterCatalog()[size_t(selectedMonster)].id);
    if (IsKeyPressed(KEY_F2)) {
        if (shift)
            run->healDebug();
        else {
            run->godMode = !run->godMode;
            run->announce(run->godMode ? "CHEAT / invincible ON" : "CHEAT / invincible OFF");
        }
    }
    if (IsKeyPressed(KEY_F3)) {
        if (shift) {
            run->clearRoomDebug();
            resetPointerInput();
        } else {
            run->killAll();
            run->announce("CHEAT / enemies killed.");
        }
    }
    if (IsKeyPressed(KEY_F4) && !shift)
        run->spawnEnemies(20);
    if (IsKeyPressed(KEY_F5))
        run->spawnEnemies(100);
    if (IsKeyPressed(KEY_F6)) {
        if (shift) {
            run->keys += 3;
            run->announce("CHEAT / added 3 keys");
        } else
            for (int i = 0; i < ItemCount; ++i)
                run->grant(ItemId(i));
    }
    if (IsKeyPressed(KEY_F7) || IsKeyPressed(KEY_F12)) {
        if (IsKeyPressed(KEY_F7))
            run->startBoss();
        else
            run->jumpDebug(shift ? run->room : (run->room + 1) % RoomCount, shift);
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
        run->grant(ItemId(selectedItem));
    if (IsKeyPressed(KEY_V))
        for (int i = 0; i < 5; ++i)
            run->grant(ItemId(run->rewardRng.bounded(ItemCount)));
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
void Game::updateCameraInput() {
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
    const Vector2 mouse = GetMousePosition();
    const float x = mouse.x * 1280.0f / float(GetScreenWidth());
    const float y = mouse.y * 800.0f / float(GetScreenHeight());
    if (screen == Screen::Expedition && run && run->shopOpen)
        return true;
    if (x >= 1040 && x <= 1256 && y >= 2 && y <= 20)
        return true;
    if (screen == Screen::Hub)
        return missionMenu || paused || (x >= 24 && x <= 410 && y >= 24 && y <= 122) ||
               (x >= 24 && x <= 700 && y >= 700) || (x >= 856 && x <= 1256 && y >= 700) ||
               (debug && debugPanelOpen && x >= 24 && x <= 480 && y >= 140 && y <= 245);
    return (x >= 24 && x <= 300 && y >= 594 && y <= 660) || (x >= 396 && x <= 936 && y >= 690 && y <= 734) ||
           (x >= 1040 && x <= 1256 && y >= 170 && y <= 362) ||
           (debug && debugPanelOpen && x >= 24 && x <= 539 && y >= 133 && y <= 592);
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
    townObjects.update(std::min(dt, .1f), [&](Vector3 p) { return town.height(p); });
    const bool over = pointerOverControls();
    updateCameraInput();
    Vector3 forward = unit({camera.target.x - camera.position.x, 0, camera.target.z - camera.position.z});
    Vector3 right{-forward.z, 0, forward.x};
    Vector3 movement = add(mul(forward, float(IsKeyDown(KEY_W)) - float(IsKeyDown(KEY_S))),
                           mul(right, float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A))));
    if (length(movement) > .01f)
        walkingToMission = false;
    mouseMoveCooldown_ = std::max(0.0f, mouseMoveCooldown_ - dt);
    const bool leftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    const bool leftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    const Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
    if (!leftDown)
        leftCommand_ = LeftCommand::None;
    if (!over && leftPressed) {
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
        }
        mouseMoveCooldown_ = .1f;
    }
    if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_ENTER))
        perform(Action::Missions);
    town.step(movement, std::min(dt, .1f));
    if (walkingToMission && town.nearMission()) {
        walkingToMission = false;
        missionMenu = true;
        town.stop();
    }
    updateCamera(dt);
}
void Game::update(float dt, const SceneryPicker &pickScenery) {
    try {
        debugInput();
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
        if (dynamiteArmed && IsKeyPressed(KEY_ESCAPE)) {
            resetPointerInput();
            return;
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
        updateCameraInput();
        Input input;
        // Camera-relative movement projected onto XZ, so W moves up the screen.
        Vector3 forward =
            unit({-camera.position.x + camera.target.x, 0, -camera.position.z + camera.target.z});
        Vector3 right{-forward.z, 0, forward.x};
        input.movement = add(mul(forward, float(IsKeyDown(KEY_W)) - float(IsKeyDown(KEY_S))),
                             mul(right, float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A))));
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
        const auto pointed = overControls ? PointerTarget{} : pickTarget(*run, ray, scenery);
        hoveredEnemy = pointed.enemy;
        if (const auto *enemy = run->findEnemy(hoveredEnemy))
            input.aim = enemy->position;
        const bool leftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        const bool leftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        const bool rightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        if (!rightDown)
            cancelFireHeld_ = false;
        const bool dynamiteKey = IsKeyPressed(KEY_B) && !overControls &&
                                 !(debug && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)));
        const bool dynamiteGesture =
            dynamiteArmed || dynamiteQueued_.has_value() || placeDynamiteQueued_ || dynamiteKey;
        if (dynamiteArmed && rightDown) {
            dynamiteArmed = false;
            cancelFireHeld_ = true;
        } else if ((dynamiteArmed && leftPressed && !overControls) || dynamiteKey) {
            if (dynamiteThrowMode)
                dynamiteQueued_ = input.aim;
            else
                placeDynamiteQueued_ = true;
            dynamiteArmed = false;
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
            leftCommand_ = attackTarget_                         ? LeftCommand::Attack
                           : (pointed.objective || pointed.door) ? LeftCommand::Interact
                                                                 : LeftCommand::Move;
            if (leftCommand_ == LeftCommand::Interact && !input.standStill && !rightDown) {
                if (pointed.door)
                    doorQueued_ = pointed.door;
                else
                    moveQueued_ = pointed.objective;
            }
        }
        if (!overControls && !dynamiteGesture && !cancelFireHeld_) {
            if (rightDown || (leftDown && input.standStill)) {
                // The prototype has one weapon: RMB also force-fires the revolver.
                input.fire = true;
            } else if (leftDown && leftCommand_ == LeftCommand::Attack) {
                // Lock the clicked enemy until release, including when the cursor moves.
                // Once it dies, keep the attack gesture from turning into a movement order.
                if (const auto *enemy = run->findEnemy(attackTarget_); enemy && enemy->alive) {
                    input.aim = enemy->position;
                    input.fire = true;
                }
            } else if (leftDown && leftCommand_ == LeftCommand::Move && !input.standStill &&
                       (leftPressed || mouseMoveCooldown_ <= 0)) {
                moveQueued_ = ground;
                mouseMoveCooldown_ = 0.1f;
            }
        }
        if (input.fire && (leftPressed || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))) {
            fireQueued_ = input.aim; // Preserve short clicks between fixed simulation ticks.
            standStillQueued_ = input.standStill;
        }
        if (!input.fire && fireQueued_)
            input.aim = *fireQueued_;
        input.fire = input.fire || fireQueued_.has_value();
        input.standStill = input.standStill || standStillQueued_;
        if (input.fire || input.standStill) {
            moveQueued_.reset();
            doorQueued_.reset();
        }
        dodgeQueued_ = dodgeQueued_ || IsKeyPressed(KEY_SPACE);
        interactQueued_ = interactQueued_ || IsKeyPressed(KEY_E);
        input.moveTarget = moveQueued_;
        input.doorTarget = doorQueued_;
        input.dodge = dodgeQueued_;
        input.interact = interactQueued_;
        input.dynamiteTarget = dynamiteQueued_;
        input.placeDynamite = placeDynamiteQueued_;
        accumulator += std::min(dt, 0.1f) * (slow ? 0.2f : 1.0f);
        while (accumulator >= Tick) {
            run->step(input);
            accumulator -= Tick;
            input.dodge = input.interact = false;
            input.dynamiteTarget.reset();
            input.placeDynamite = placeDynamiteQueued_ = false;
            dynamiteQueued_.reset();
            input.moveTarget.reset();
            input.doorTarget.reset();
            moveQueued_.reset();
            doorQueued_.reset();
            fireQueued_.reset();
            standStillQueued_ = false;
            dodgeQueued_ = interactQueued_ = false;
            if (run->finished || run->dead || run->rewardOpen || run->shopOpen)
                break;
        }
        checkpoint();
        if (run->finished && !run->dead)
            finish(EndReason::Victory);
        updateCamera(dt);
    } catch (const std::exception &e) {
        error = e.what();
        paused = true;
    }
}
} // namespace dw
