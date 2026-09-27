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
PointerTarget pickTarget(const Simulation &run, Ray ray) {
    PointerTarget result;
    float nearest = std::numeric_limits<float>::infinity();
    // A wall in front of a body prevents clicking through it.
    for (const auto &wall : run.arena.walls) {
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
    if (run.roomClear)
        for (size_t i = 0; i < run.arena.passages.size(); ++i)
            for (int side = 0; side < 2; ++side)
                if (hits(run.arena.doorApproach(int(i), side), 2.5f, 3.2f)) {
                    result.objective.reset();
                    result.door = std::pair{int(i), side};
                }
    for (const auto &enemy : run.enemies) {
        if (enemy.alive && hits(enemy.position, enemy.radius, enemy.kind == EnemyKind::Boss ? 3.4f : 2.5f)) {
            result.enemy = enemy.id;
            result.objective.reset();
            result.door.reset();
        }
    }
    return result;
}
} // namespace

Game::Game(const std::filesystem::path &save) : campaign(save) {
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
    if (!town.load(TownScene::assetDirectory() / "town.nav"))
        error = town.error;
    snapCamera();
    newSeed();
}
void Game::launch() {
    uint64_t seed = 0;
    auto result = std::from_chars(seedText.data(), seedText.data() + seedText.size(), seed);
    if (result.ec != std::errc{} || result.ptr != seedText.data() + seedText.size()) {
        error = "Enter a whole-number seed (up to 20 digits).";
        return;
    }
    auto candidate = std::make_unique<Simulation>(seed, campaign.data().nextRunId, campaign.data().world);
    campaign.begin(seed);
    run = std::move(candidate);
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
    town.reset();
    newSeed();
    screen = Screen::Summary;
    paused = false;
    accumulator = 0;
    resetPointerInput();
}
void Game::resetPointerInput() {
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
            if (run && !paused && !run->rewardOpen)
                dodgeQueued_ = true;
            break;
        case Action::Interact:
            if (run && !paused && !run->rewardOpen)
                interactQueued_ = true;
            break;
        case Action::Retreat:
            finish(EndReason::Retreat);
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
    if (IsKeyPressed(KEY_F4))
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
    if (screen == Screen::Hub)
        return missionMenu || paused || (x >= 24 && x <= 410 && y >= 24 && y <= 122) ||
               (x >= 24 && x <= 700 && y >= 700) ||
               (debug && debugPanelOpen && x >= 24 && x <= 480 && y >= 140 && y <= 245);
    return (x >= 396 && x <= 936 && y >= 690 && y <= 734) ||
           (x >= 1040 && x <= 1256 && y >= 170 && y <= 362) ||
           (debug && debugPanelOpen && x >= 24 && x <= 539 && y >= 133 && y <= 592);
}
void Game::newSeed() {
    // Fresh offers each time the player returns, while retaining editable seeds
    // for replaying a particular mission layout.
    static Random seeds(uint64_t(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    seedText = std::to_string(seeds.next() % 1000000000);
}
void Game::updateHub(float dt) {
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
void Game::update(float dt) {
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
        Vector3 ground = input.aim;
        if (!overControls && std::abs(ray.direction.y) > 0.0001f) {
            float t = -ray.position.y / ray.direction.y;
            ground = t > 0 ? add(ray.position, mul(ray.direction, t)) : run->player.aim;
            input.aim = ground;
        }
        const auto pointed = overControls ? PointerTarget{} : pickTarget(*run, ray);
        hoveredEnemy = pointed.enemy;
        if (const auto *enemy = run->findEnemy(hoveredEnemy))
            input.aim = enemy->position;
        const bool leftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        const bool leftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        const bool rightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        input.standStill = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        mouseMoveCooldown_ = std::max(0.0f, mouseMoveCooldown_ - dt);
        if (!leftDown) {
            leftCommand_ = LeftCommand::None;
            attackTarget_ = 0;
        }
        if (!overControls && leftPressed) {
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
        if (!overControls) {
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
        accumulator += std::min(dt, 0.1f) * (slow ? 0.2f : 1.0f);
        while (accumulator >= Tick) {
            run->step(input);
            accumulator -= Tick;
            input.dodge = input.interact = false;
            input.moveTarget.reset();
            input.doorTarget.reset();
            moveQueued_.reset();
            doorQueued_.reset();
            fireQueued_.reset();
            standStillQueued_ = false;
            dodgeQueued_ = interactQueued_ = false;
            if (run->finished || run->dead || run->rewardOpen)
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
