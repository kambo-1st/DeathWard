#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include <chrono>
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
} // namespace
int main() {
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
        dw::Game game(directory / "campaign.save");
        dw::Renderer renderer;
        auto frame = [&](int x = 10, int y = 10, bool left = false, bool right = false, bool middle = false,
                         bool shift = false, float dt = dw::Tick) {
            mouseEvent(MousePosition, x, y);
            mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
            mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
            mouseEvent(middle ? MouseDown : MouseUp, MOUSE_BUTTON_MIDDLE);
            mouseEvent(shift ? KeyDown : KeyUp, KEY_LEFT_SHIFT);
            game.update(dt);
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
        check(!game.campaign.data().pending && game.campaign.data().history.empty(),
              "town exploration does not create a pending mission or a campaign outcome");
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
        click(650, 550);
        check(game.run && game.screen == dw::Screen::Expedition, "mouse launch opens expedition");
        check(game.run->arena.theme == dw::MissionTheme::Canyon &&
                  game.campaign.data().pending->expedition == "Redstone Canyon",
              "the selected canyon theme reaches gameplay and the initial campaign checkpoint");
        check(game.debug && !game.debugPanelOpen && game.run->roomClear && game.run->livingEnemies() == 0,
              "new games start with hidden cheats enabled and an open, enemy-free starting room");
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
        destination.y = 0;
        auto point = GetWorldToScreen(destination, game.camera);
        click(int(point.x), int(point.y));
        check(game.run->moveDestination().has_value(), "left-clicking ground queues a route");
        for (int i = 0; i < 200; ++i)
            frame();
        destination.y = 0.85f;
        check(dw::distance(game.run->player.position, destination) < 0.15f,
              "mouse ray and navigation reach clicked ground point");
        check(game.run->stats.shots == 0, "left-clicking ground never fires");
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
        check(game.run->findEnemy(target)->hp <= 10000 - 48 * 10,
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
        click(670, 711);
        frame(670, 711);
        check(game.run->player.dodge > 0, "onscreen dodge works with a two-button mouse");
        click(850, 711);
        check(game.paused, "onscreen pause button pauses the expedition");
        const double duration = game.run->stats.duration;
        for (int i = 0; i < 60; ++i)
            frame(100, 200, true);
        frame(100, 200);
        check(game.run->stats.duration == duration, "simulation remains frozen while paused");
        click(620, 445);
        check(!game.paused, "mouse resumes the expedition");
        check(game.run->stats.shots == shots, "HUD and paused clicks never fire the revolver");
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
        const auto cameraGoal = dw::sub(game.run->player.position, {2, 0.85f, 2});
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
        const int powerRoom = dw::RoomCount - 2;
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
        click(850, 711);
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
        check(game.run->livingEnemies() == 20, "F4 spawns testing enemies");
        pressKey(KEY_F3, true);
        pressKey(KEY_F6);
        pressKey(KEY_F6, true);
        check(game.run->items.size() == dw::ItemCount && game.run->keys == 3,
              "F6 grants all effects and Shift+F6 supplies testing keys");
        pressKey(KEY_F12, true);
        check(game.run->room == 2 && !game.run->roomClear && game.run->livingEnemies() > 0,
              "Shift+F12 restarts the current room with its enemy group already present");
        game.paused = true;
        pressKey(KEY_F12);
        check(game.run->room == 3 && !game.paused &&
                  dw::distance(game.camera.target, dw::sub(game.run->player.position, {2, 0.85f, 2})) < 0.01f,
              "F12 skips to the next room, resumes and immediately follows with the camera");
        pressKey(KEY_F7);
        check(game.run->room == dw::Simulation::FinalRoom && game.run->boss(),
              "F7 jumps directly to the boss");
        pressKey(KEY_F3, true);
        pressKey(KEY_F7);
        check(!game.run->roomClear && !game.run->bossKilled && game.run->livingEnemies() == 1,
              "F7 can replay a defeated boss");
        pressKey(KEY_F10);
        pressKey(KEY_O);
        pressKey(KEY_F1);
        check(!game.debug && !game.run->godMode && !game.slow && !game.collisionDebug,
              "turning cheat mode off disables invincibility, slow time and collision overlays");
        pressKey(KEY_F3);
        check(game.run->livingEnemies() == 1, "F3 is disabled again after leaving cheat mode");
        pressKey(KEY_F1);
        game.paused = true;
        pressKey(KEY_F8);
        check(!game.run && game.screen == dw::Screen::Summary &&
                  game.lastSummary.reason == dw::EndReason::Victory,
              "F8 completes the expedition immediately while paused");
        game.perform(dw::Action::Hub);
        game.launch();
        game.run->jumpDebug(dw::RoomCount - 2);
        game.run->player.position = game.run->arena.rooms[dw::RoomCount - 2].objective;
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
        const auto originalAngle = dw::unit(dw::sub(game.camera.position, game.camera.target));
        const auto beforeZoom = game.run->player.position;
        mouseEvent(MouseWheel, 0, 100);
        frame();
        check(cameraDistance() < defaultDistance && cameraDistance() > defaultDistance * 0.35f,
              "scrolling up smoothly moves the camera closer");
        settleCamera();
        const float closestDistance = cameraDistance();
        check(std::abs(closestDistance - defaultDistance * 0.35f) < 0.01f,
              "large wheel input stops at the close zoom limit");
        check(dw::distance(beforeZoom, game.run->player.position) == 0 && game.run->stats.shots == 0 &&
                  game.run->player.dodge == 0,
              "scrolling never moves, shoots or dodges");
        mouseEvent(MouseWheel, 0, -100);
        frame(850, 711);
        settleCamera();
        check(std::abs(cameraDistance() - closestDistance) < 0.01f, "HUD controls ignore scrolling");
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
        check(std::abs(widestDistance - defaultDistance * 1.5f) < 0.01f &&
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
        frame(850, 711, false, false, true);
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
        game.perform(dw::Action::Hub);
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f,
              "returning to town preserves camera rotation");
        game.missionMenu = true;
        orbit(150, 100);
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f, "the station menu blocks camera rotation");
        game.missionMenu = false;
        game.launch();
        check(std::abs(cameraDistance() - widestDistance) < 0.01f, "new expeditions retain session zoom");
        check(dw::distance(retainedAngle, cameraAngle()) < .0001f,
              "new expeditions retain session camera rotation");
        game.run->player.hp = 0;
        frame();
        game.close();
        check(game.lastSummary.reason == dw::EndReason::Death,
              "closing during a death animation records death, not retreat");
        renderer.unload();
        CloseWindow();
        std::filesystem::remove_all(directory);
        std::cout << "PASS original town movement, station approach, mission seeds, launch and return loop\n";
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
