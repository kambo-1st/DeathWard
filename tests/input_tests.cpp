#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
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
void arrowInputCheck(const std::filesystem::path &directory, dw::MissionTheme theme) {
    const std::string name = theme == dw::MissionTheme::Canyon ? "canyon" : "mine";
    dw::Game game(directory / ("arrows-" + name + ".save"));
    game.seedText = "1866";
    game.themeChoice = theme == dw::MissionTheme::Canyon ? dw::ThemeChoice::Canyon : dw::ThemeChoice::Mine;
    game.launch();
    auto &run = *game.run;
    run.godMode = true;
    game.updateCamera(10);
    auto frame = [&](float dt = dw::Tick) {
        game.update(dt);
        BeginDrawing();
        EndDrawing(); // Poll raylib input, including pressed/released edges.
        check(game.error.empty(), "arrow input causes no game errors");
    };
    auto release = [&] {
        for (int key : {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_D, KEY_LEFT_SHIFT})
            mouseEvent(KeyUp, key);
        mouseEvent(MouseUp, MOUSE_BUTTON_RIGHT);
        frame();
    };
    auto forward = [&] {
        const auto offset = dw::sub(game.camera.target, game.camera.position);
        return dw::unit(Vector3{offset.x, 0, offset.z});
    };
    auto heading = [&] { return dw::unit(dw::sub(run.player.aim, run.player.position)); };
    auto shotHeading = [&] {
        check(!run.projectiles.empty(), "arrow firing creates a projectile");
        return dw::unit(run.projectiles.back().velocity);
    };
    mouseEvent(MousePosition, 1100, 200);
    release();
    check(game.pointerOverControls(), "arrow fixture keeps the cursor over the map HUD");
    auto directions = [&] {
        const auto f = forward();
        const Vector3 r{-f.z, 0, f.x};
        for (const auto &[key, direction] : std::array<std::pair<int, Vector3>, 4>{
                 {{KEY_UP, f}, {KEY_DOWN, dw::mul(f, -1)}, {KEY_RIGHT, r}, {KEY_LEFT, dw::mul(r, -1)}}}) {
            const auto shots = run.stats.shots;
            run.player.fireCooldown = 0;
            mouseEvent(KeyDown, key);
            frame();
            check(run.stats.shots == shots + 1 && dw::distance(shotHeading(), direction) < .001f,
                  "all four arrow keys fire relative to the camera even over the HUD");
            release();
        }
    };
    directions();
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_RIGHT);
    run.player.fireCooldown = 0;
    frame();
    const auto f = forward();
    check(dw::distance(shotHeading(), dw::unit(dw::add(f, {-f.z, 0, f.x}))) < .001f,
          "adjacent arrows produce a diagonal projectile");
    release();
    const auto beforeOpposite = run.stats.shots;
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_DOWN);
    mouseEvent(KeyDown, KEY_LEFT);
    mouseEvent(KeyDown, KEY_RIGHT);
    frame(.1f);
    check(run.stats.shots == beforeOpposite, "opposite arrows cancel instead of firing a zero direction");
    release();
    run.player.fireCooldown = 0;
    const auto beforeHeld = run.stats.shots;
    mouseEvent(KeyDown, KEY_UP);
    for (int i = 0; i < 60; ++i)
        frame();
    check(run.stats.shots >= beforeHeld + 3, "holding an arrow repeats at the revolver fire rate");
    release();
    const auto afterRelease = run.stats.shots;
    frame(.1f);
    check(run.stats.shots == afterRelease, "releasing arrows stops keyboard fire");
    game.accumulator = 0;
    run.player.fireCooldown = 0;
    mouseEvent(KeyDown, KEY_LEFT);
    frame(dw::Tick / 4);
    mouseEvent(KeyUp, KEY_LEFT);
    frame(dw::Tick / 4);
    check(run.stats.shots == afterRelease, "a short arrow tap waits for the simulation tick");
    frame();
    check(run.stats.shots == afterRelease + 1 &&
              dw::distance(shotHeading(), {f.z, 0, -f.x}) < .001f,
          "a short arrow tap preserves both the shot and its direction");
    const auto start = run.player.position;
    dw::Input navigation;
    navigation.moveTarget = dw::add(start, dw::mul(f, 2));
    run.step(navigation);
    check(run.moveDestination().has_value(), "arrow fixture begins with an active walking route");
    mouseEvent(KeyDown, KEY_UP);
    mouseEvent(KeyDown, KEY_D);
    run.player.fireCooldown = 0;
    frame(.1f); // Multiple simulation ticks must retain a directional aim while strafing.
    check(dw::distance(start, run.player.position) > .1f && !run.moveDestination() &&
              dw::distance(heading(), f) < .001f && dw::distance(shotHeading(), f) < .001f,
          "WASD strafes while arrow shots retain their heading and cancel click navigation");
    const auto standing = run.player.position;
    mouseEvent(KeyDown, KEY_LEFT_SHIFT);
    frame(.1f);
    check(dw::distance(standing, run.player.position) < .001f, "Shift holds position during arrow fire");
    release();
    mouseEvent(MousePosition, 600, 350);
    mouseEvent(MouseDown, MOUSE_BUTTON_MIDDLE);
    frame();
    mouseEvent(MousePosition, 790, 370);
    frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_MIDDLE);
    frame();
    check(dw::distance(f, forward()) > .1f, "arrow fixture rotates the camera with a middle drag");
    mouseEvent(MousePosition, 1100, 200);
    directions();
    mouseEvent(MousePosition, 680, 315);
    mouseEvent(MouseDown, MOUSE_BUTTON_RIGHT);
    mouseEvent(KeyDown, KEY_DOWN);
    frame();
    check(dw::distance(heading(), dw::mul(forward(), -1)) < .001f,
          "held arrows take aim priority over simultaneous mouse fire");
    mouseEvent(KeyUp, KEY_DOWN);
    run.player.fireCooldown = 0;
    const auto beforeMouse = run.stats.shots;
    frame();
    check(run.stats.shots == beforeMouse + 1 &&
              dw::distance(heading(), dw::mul(forward(), -1)) > .1f,
          "releasing arrows immediately restores existing mouse aiming and firing");
    release();
    // Neither held arrows nor sub-tick taps may leak through modal screens.
    auto modalGuard = [&](bool &open) {
        const auto shots = run.stats.shots;
        game.accumulator = 0;
        run.player.fireCooldown = 0;
        mouseEvent(KeyDown, KEY_UP);
        frame(dw::Tick / 4);
        open = true;
        frame();
        release();
        open = false;
        frame();
        check(run.stats.shots == shots, "modals block arrows and discard pending arrow taps");
    };
    modalGuard(game.paused);
    modalGuard(run.shopOpen);
    modalGuard(run.rewardOpen);
    modalGuard(run.letterOpen);
    modalGuard(game.journalOpen);
    const auto beforeDynamite = run.stats.shots;
    game.dynamiteArmed = true;
    mouseEvent(KeyDown, KEY_UP);
    frame();
    check(run.stats.shots == beforeDynamite, "dynamite targeting blocks keyboard gunfire");
    game.dynamiteArmed = false;
    mouseEvent(KeyDown, KEY_B);
    frame();
    mouseEvent(KeyUp, KEY_B);
    release();
    check(run.stats.shots == beforeDynamite && run.dynamite == 2,
          "placing dynamite while holding an arrow does not also fire the revolver");
    std::cout << "PASS " << name
              << " arrow fire, diagonals, rotated camera, strafing, short taps, mouse fallback and modal guards\n";
}
void shopInputCheck(const std::filesystem::path &directory, dw::MissionTheme theme) {
    const std::string name = theme == dw::MissionTheme::Canyon ? "canyon" : "mine";
    dw::Game game(directory / ("shop-" + name + ".save"));
    game.campaign.begin(1);
    auto funding = *game.campaign.data().pending;
    funding.moneyCollected = 100;
    game.campaign.resolve(funding, dw::EndReason::Victory);
    game.seedText = "1866";
    game.themeChoice = theme == dw::MissionTheme::Canyon ? dw::ThemeChoice::Canyon : dw::ThemeChoice::Mine;
    game.launch();
    auto &run = *game.run;
    run.jumpDebug(run.arena.shopRoom);
    const auto merchant = run.arena.rooms[size_t(run.room)].objective;
    run.player.position =
        dw::add(merchant, dw::mul(dw::unit(dw::sub(run.arena.rooms[size_t(run.room)].center, merchant)), 4));
    run.player.hp = 55;
    game.updateCamera(10);
    dw::Renderer renderer;
    const dw::Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&](int x = 10, int y = 10, bool left = false, bool right = false) {
        mouseEvent(MousePosition, x, y);
        mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
        mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
        game.update(dw::Tick, picker);
        BeginDrawing();
        const auto action = renderer.draw(game);
        EndDrawing();
        game.perform(action);
        check(game.error.empty(), "shop input does not cause a game error");
    };
    auto click = [&](int x, int y) {
        frame(x, y);
        frame(x, y, true);
        frame(x, y);
    };
    auto capture = [&](const std::string &stage) {
        BeginDrawing();
        renderer.draw(game);
        rlDrawRenderBatchActive();
        const auto image = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(image, ("artifacts/shop-" + name + "-" + stage + ".png").c_str()),
              "save the shop capture");
        UnloadImage(image);
        EndDrawing();
    };
    frame();
    capture("merchant");
    const auto pixel = GetWorldToScreen(dw::add(merchant, {0, .8f, 0}), game.camera);
    click(int(pixel.x), int(pixel.y));
    for (int i = 0; i < 240 && !run.shopOpen; ++i)
        frame();
    check(run.shopOpen && run.enemies.empty() && run.stats.shots == 0,
          "clicking the actual shopkeeper approaches and opens trade without shooting");
    const auto position = run.player.position;
    const auto duration = run.stats.duration;
    mouseEvent(KeyDown, KEY_W);
    mouseEvent(KeyDown, KEY_B);
    for (int i = 0; i < 10; ++i)
        frame(600, 700, true, true);
    mouseEvent(KeyUp, KEY_W);
    mouseEvent(KeyUp, KEY_B);
    frame();
    check(game.pointerOverControls() && dw::distance(position, run.player.position) == 0 &&
              run.stats.duration == duration && run.stats.shots == 0 && run.dynamite == 3,
          "the trade window captures gameplay mouse/key input and freezes the world");
    click(330, 535);
    check(run.player.hp == 95 && run.money() == 90 && run.shopOffers[0].sold,
          "the medicine buy button heals and charges its displayed price");
    click(630, 535);
    check(run.money() == 65 && run.items.size() == 1 && game.campaign.data().pending->moneySpent == 35,
          "the power buy button applies its item and checkpoints spending immediately");
    click(630, 535);
    check(run.money() == 65 && run.items.size() == 1, "sold-out buttons do not charge again");
    click(450, 610);
    check(run.money() == 50 && run.dynamite == 6 && run.shopOffers[3].sold &&
              game.campaign.data().pending->moneySpent == 50,
          "the dynamite pack button adds three charges and saves the purchase");
    capture("stock");
    click(925, 610);
    check(!run.shopOpen && run.stats.shots == 0, "leaving the shop never fires through the panel");
    mouseEvent(KeyDown, KEY_E);
    frame();
    mouseEvent(KeyUp, KEY_E);
    frame();
    check(run.shopOpen && run.shopOffers[1].sold, "reopening preserves sold stock");
    mouseEvent(KeyDown, KEY_ESCAPE);
    frame();
    mouseEvent(KeyUp, KEY_ESCAPE);
    frame();
    check(!run.shopOpen && !game.paused, "Escape closes trade without opening Pause");
    game.finish(dw::EndReason::Retreat);
    check(game.campaign.data().world.money == 50, "returning from the shop preserves the wallet debit");
    std::cout << "PASS " << name
              << " shopkeeper approach, purchases, UI guards, closing and saved spending\n";
}
void dynamiteInputCheck(const std::filesystem::path &directory, dw::MissionTheme theme) {
    const std::string name = theme == dw::MissionTheme::Canyon ? "canyon" : "mine";
    dw::Game game(directory / ("dynamite-" + name + ".save"));
    game.seedText = "1866";
    game.themeChoice = theme == dw::MissionTheme::Canyon ? dw::ThemeChoice::Canyon : dw::ThemeChoice::Mine;
    game.launch();
    auto &run = *game.run;
    run.godMode = true;
    check(!game.dynamiteThrowMode, "dynamite defaults to ground placement");
    game.updateCamera(10);
    dw::Renderer renderer;
    const dw::Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&](int x, int y, bool left = false, bool right = false, float dt = dw::Tick) {
        mouseEvent(MousePosition, x, y);
        mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
        mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
        game.update(dt, picker);
        BeginDrawing();
        const auto action = renderer.draw(game);
        EndDrawing();
        game.perform(action);
        check(game.error.empty(), "dynamite input causes no game errors");
    };
    auto click = [&](int x, int y) {
        frame(x, y);
        frame(x, y, true);
        frame(x, y);
    };
    auto capture = [&](const std::string &stage) {
        BeginDrawing();
        renderer.draw(game);
        rlDrawRenderBatchActive();
        auto image = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(image, ("artifacts/dynamite-" + name + "-" + stage + ".png").c_str()),
              "save dynamite capture");
        UnloadImage(image);
        EndDrawing();
    };
    const auto aim = dw::add(run.player.position, {0, -.85f, -5});
    const auto pixel = GetWorldToScreen(aim, game.camera);
    const int x = int(pixel.x), y = int(pixel.y);
    frame(x, y);
    game.accumulator = 0;
    mouseEvent(KeyDown, KEY_B);
    frame(x, y, false, false, .001f);
    mouseEvent(KeyUp, KEY_B);
    frame(x, y, false, false, .001f);
    check(run.dynamite == 3, "short B press waits for the next fixed simulation step");
    frame(x, y);
    check(run.dynamite == 2 && run.hazards.size() == 1 && run.stats.shots == 0,
          "a short B press places exactly one dynamite without firing the revolver");
    const auto planted = run.hazards.front().position;
    check(run.hazards.front().settled && planted.x == run.player.position.x &&
              planted.z == run.player.position.z,
          "B places at the player's feet rather than at the cursor");
    for (int i = 0; i < 20; ++i)
        frame(x, y);
    capture("lit");
    game.perform(dw::Action::Pause);
    const float age = run.hazards.front().age;
    mouseEvent(KeyDown, KEY_B);
    mouseEvent(KeyDown, KEY_E);
    for (int i = 0; i < 10; ++i)
        frame(x, y);
    mouseEvent(KeyUp, KEY_B);
    mouseEvent(KeyUp, KEY_E);
    frame(x, y); // Let raylib observe the releases before the next E press.
    check(run.hazards.front().age == age && run.hazards.front().settled && run.dynamite == 2,
          "pause freezes fuses and rejects deployment and kicks");
    game.perform(dw::Action::Resume);
    check(run.nearbyInteraction() != "KICK DYNAMITE", "contact kicking needs no HUD control");
    mouseEvent(KeyDown, KEY_E);
    frame(x, y);
    mouseEvent(KeyUp, KEY_E);
    frame(x, y);
    check(run.hazards.front().settled, "E no longer kicks dynamite");
    mouseEvent(KeyDown, KEY_W);
    for (int i = 0; i < 10; ++i)
        frame(x, y);
    mouseEvent(KeyUp, KEY_W);
    frame(x, y);
    check(run.hazards.front().settled && dw::distance(planted, run.hazards.front().position) == 0,
          "WASD walking away leaves the planted charge in place");
    mouseEvent(KeyDown, KEY_S);
    for (int i = 0; i < 5; ++i)
        frame(x, y);
    mouseEvent(KeyUp, KEY_S);
    frame(x, y);
    check(!run.hazards.front().settled && run.hazards.front().age > age && run.dynamite == 2 &&
              run.stats.shots == 0,
          "walking back into a charge kicks it automatically without spending ammo or firing");
    capture("kicked");
    for (int i = 0; i < 130 && run.stats.explosions == 0; ++i)
        frame(x, y);
    check(run.stats.explosions == 1 && run.dynamite == 2, "the charge detonates once after resuming");
    for (int i = 0; i < 12; ++i)
        frame(x, y);
    capture("blast");
    for (int i = 0; i < 40; ++i)
        frame(x, y);
    click(160, 608);
    check(game.dynamiteThrowMode && run.dynamite == 2 && run.stats.shots == 0,
          "the mode switch enables throwing without spending ammo or firing");
    click(160, 640);
    check(game.dynamiteArmed && run.dynamite == 2, "the HUD button arms aiming without spending ammo");
    frame(x, y);
    capture("preview");
    const auto before = run.player.position;
    frame(x, y);
    frame(x, y, true);
    for (int i = 0; i < 12; ++i)
        frame(x, y, true);
    frame(x, y);
    check(!game.dynamiteArmed && run.dynamite == 1 && run.stats.shots == 0 &&
              dw::distance(before, run.player.position) < .001f,
          "mouse targeting throws once without a movement order or revolver shot");
    click(160, 640);
    for (int i = 0; i < 8; ++i)
        frame(x, y, false, true);
    frame(x, y);
    check(!game.dynamiteArmed && run.dynamite == 1 && run.stats.shots == 0,
          "holding the right button after cancel never fires through the cancellation");
    click(160, 640);
    mouseEvent(KeyDown, KEY_ESCAPE);
    frame(x, y);
    mouseEvent(KeyUp, KEY_ESCAPE);
    frame(x, y);
    check(!game.dynamiteArmed && !game.paused && run.dynamite == 1,
          "Escape cancels targeting without pausing or spending ammo");
    mouseEvent(KeyDown, KEY_LEFT_SHIFT);
    mouseEvent(KeyDown, KEY_B);
    frame(x, y);
    mouseEvent(KeyUp, KEY_B);
    mouseEvent(KeyUp, KEY_LEFT_SHIFT);
    frame(x, y);
    check(run.dynamite == dw::MaxDynamite, "Shift+B refills dynamite for testing without throwing");
    click(160, 640);
    check(game.dynamiteArmed, "refilled dynamite can target a throw");
    click(160, 608);
    check(!game.dynamiteThrowMode && !game.dynamiteArmed && run.dynamite == dw::MaxDynamite,
          "switching to placement cancels an armed throw without spending ammo");
    click(160, 640);
    frame(160, 640);
    const auto &placed = run.hazards.back();
    check(run.dynamite == dw::MaxDynamite - 1 && placed.settled &&
              placed.position.x == run.player.position.x && placed.position.z == run.player.position.z &&
              !game.dynamiteArmed && run.stats.shots == 0,
          "the Place Dynamite button immediately places at the player's feet without a targeting click");
    capture("placed");
    const auto placedAt = placed.position;
    // Exercise ordinary ground clicks during combat, when the starting passage's
    // broad interaction area does not redirect them into a door approach.
    run.roomClear = false;
    run.debugScenario = true;
    Vector3 away{};
    bool found = false;
    for (const auto direction : {Vector3{1, 0, 0}, Vector3{0, 0, 1}, Vector3{-1, 0, 0}, Vector3{0, 0, -1}}) {
        away = dw::add(run.player.position, dw::mul(direction, 1.3f));
        if (!run.arena.blocked(away, .48f) && run.arena.clear(run.player.position, away, .48f)) {
            found = true;
            break;
        }
    }
    check(found, "there is room to step away from the planted charge");
    auto worldClick = [&](Vector3 at) {
        at.y = 0;
        const auto screen = GetWorldToScreen(at, game.camera);
        click(int(screen.x), int(screen.y));
    };
    worldClick(away);
    for (int i = 0; i < 25 && run.moveDestination(); ++i)
        frame(640, 400);
    check(dw::distance(run.player.position, placedAt) > 1,
          "mouse movement separates the feet from the bundle");
    check(dw::distance(placedAt, run.hazards.back().position) == 0 && run.hazards.back().settled,
          "click-to-move away leaves the bundle at the placement point");
    worldClick(placedAt);
    for (int i = 0; i < 25 && run.hazards.back().settled; ++i)
        frame(640, 400);
    check(!run.hazards.back().settled && run.dynamite == dw::MaxDynamite - 1 && run.stats.shots == 0,
          "click-to-move into dynamite nudges it without a special button");
    for (int i = 0; i < 25; ++i)
        frame(640, 400);
    const float nudged = dw::distance(placedAt, run.hazards.back().position);
    check(nudged > .4f && nudged < 1.5f, "the mouse contact kick travels only a short distance");
    game.close();
    std::cout
        << "PASS " << name
        << " dynamite ground placement, WASD/mouse contact kicks, throws, pause, cancellation and refill\n";
}
void boundaryRiverInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory / "river.save");
    game.seedText = "1866";
    game.launch();
    auto &run = *game.run;
    const auto &field = *run.arena.canyon;
    const int room = field.riverRooms.front();
    const auto &layout = run.arena.rooms[size_t(room)];
    const auto outward = field.riverOutward;
    const float reach = std::abs(dot(sub(layout.bounds.max, layout.bounds.min), outward)) * .5f;
    Vector3 from{};
    bool found = false;
    const auto bank = add(layout.center, mul(outward, reach - 2.5f));
    const auto water = add(bank, mul(outward, field.riverSample(bank).width + 3));
    const Vector3 tangent{-outward.z, 0, outward.x};
    for (float offset : {0.f, -2.f, 2.f, -4.f, 4.f}) {
        const auto candidate = add(add(layout.center, mul(outward, reach - 6)), mul(tangent, offset));
        if (!run.arena.blocked(candidate, .6f) && run.arena.sight(candidate, water)) {
            from = candidate;
            found = true;
            break;
        }
    }
    check(found && field.waterBlocked(water),
          "river mouse fixture has a clear approach to a deep-water boundary");
    run.jumpDebug(room);
    run.clearRoomDebug();
    run.player.position = from;
    run.godMode = true;
    game.updateCamera(1);
    Renderer renderer;
    const Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&]() {
        game.update(Tick, picker);
        BeginDrawing();
        renderer.draw(game);
        EndDrawing();
    };
    mouseEvent(MousePosition, 640, 400);
    mouseEvent(MouseWheel, 0, -5);
    frame();
    for (int n = 0; n < 40; ++n)
        frame();
    auto pixel = GetWorldToScreen({water.x, 0, water.z}, game.camera);
    check(pixel.x > 10 && pixel.x < 1270 && pixel.y > 130 && pixel.y < 670,
          "deep-water target is inside the play viewport");
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_LEFT);
    frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_LEFT);
    frame();
    check(run.moveDestination().has_value(), "clicking water queues an approach to the bank");
    for (int n = 0; n < 900 && run.moveDestination(); ++n) {
        frame();
        check(!field.waterBlocked(run.player.position), "mouse movement never steps into deep water");
    }
    check(distance(run.player.position, from) > 1 && !run.moveDestination() &&
              run.arena.roomAt(run.player.position) == room,
          "mouse movement approaches the boundary and stops on the playable near bank");
    check(run.stats.shots == 0, "a bank movement click never fires");
    const auto stopped = run.player.position;
    pixel = GetWorldToScreen({water.x, 0, water.z}, game.camera);
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_RIGHT);
    for (int n = 0; n < 20; ++n)
        frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_RIGHT);
    frame();
    check(run.stats.shots > 0 && distance(run.player.position, stopped) < .1f,
          "aiming and firing across water does not become a movement command");
    game.close();
    std::cout << "PASS river mouse approach, stopping at the natural boundary and "
                 "aiming/firing across water\n";
}

void interiorRiverInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory / "interior-river.save");
    game.seedText = "42";
    game.launch();
    auto &run = *game.run;
    const auto &field = *run.arena.canyon;
    check(field.riverKind == CanyonRiverKind::Interior, "interior mouse test uses an interior river seed");
    Vector3 from{}, to{}, water{};
    int room = -1;
    for (size_t i = 1; i + 1 < field.river.size(); ++i) {
        const auto &p = field.river[i];
        if (field.height(p.position.x, p.position.z) > -.4f)
            continue;
        const auto direction = unit(sub(field.river[i + 1].position, field.river[i - 1].position));
        const Vector3 side{-direction.z, 0, direction.x};
        auto a = add(p.position, mul(side, p.width + 2.5f)), b = sub(p.position, mul(side, p.width + 2.5f));
        a.y = b.y = .85f;
        const int index = run.arena.roomAt(a);
        if (index < 0 || index != run.arena.roomAt(b) || run.arena.blocked(a, .6f) ||
            run.arena.blocked(b, .6f) || !run.arena.sight(a, b) || run.arena.clear(a, b, .48f) ||
            run.arena.path(a, b, .48f).empty())
            continue;
        from = a;
        to = b;
        water = p.position;
        room = index;
        break;
    }
    check(room >= 0, "river mouse fixture has two connected banks separated by deep water");
    run.jumpDebug(room);
    run.clearRoomDebug();
    run.player.position = from;
    run.godMode = true;
    game.updateCamera(1);
    Renderer renderer;
    const Game::SceneryPicker picker = [&](const auto &simulation, const auto &camera, Ray ray) {
        return renderer.pickScenery(simulation, camera, ray);
    };
    auto frame = [&]() {
        game.update(Tick, picker);
        BeginDrawing();
        renderer.draw(game);
        EndDrawing();
    };
    mouseEvent(MousePosition, 640, 400);
    mouseEvent(MouseWheel, 0, -5);
    frame();
    for (int n = 0; n < 40; ++n)
        frame();
    auto pixel = GetWorldToScreen({to.x, 0, to.z}, game.camera);
    check(pixel.x > 10 && pixel.x < 1270 && pixel.y > 130 && pixel.y < 670,
          "opposite bank is inside the play viewport");
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_LEFT);
    frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_LEFT);
    frame();
    check(run.moveDestination().has_value(), "clicking the opposite bank queues a ford route");
    for (int n = 0; n < 900 && run.moveDestination(); ++n) {
        frame();
        check(!field.waterBlocked(run.player.position), "mouse movement never steps into deep water");
    }
    check(distance(run.player.position, to) < .9f, "mouse movement reaches the opposite bank through a ford");
    check(run.stats.shots == 0, "a bank movement click never fires");
    pixel = GetWorldToScreen({water.x, 0, water.z}, game.camera);
    mouseEvent(MousePosition, int(pixel.x), int(pixel.y));
    mouseEvent(MouseDown, MOUSE_BUTTON_RIGHT);
    for (int n = 0; n < 20; ++n)
        frame();
    mouseEvent(MouseUp, MOUSE_BUTTON_RIGHT);
    frame();
    check(run.stats.shots > 0 && distance(run.player.position, to) < .9f,
          "aiming and firing across water does not become a movement command");
    game.close();
    std::cout << "PASS river mouse routing through fords and aiming/firing across deep water\n";
}
void vegetationInputCheck(const std::filesystem::path &directory) {
    using namespace dw;
    Game game(directory / "vegetation.save");
    game.seedText = "1866";
    game.launch();
    game.paused = true;
    game.debug = false;
    Renderer renderer;
    auto frame = [&](int x = 10, int y = 10, bool down = false) {
        mouseEvent(MousePosition, x, y);
        mouseEvent(down ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
        game.update(Tick);
        BeginDrawing();
        const auto action = renderer.draw(game);
        EndDrawing();
        game.perform(action);
    };
    auto click = [&](int x) {
        frame(x, 719, true);
        frame(x, 719);
        frame();
    };
    frame();
    const auto duration = game.run->stats.duration;
    const auto plants = renderer.missionVegetationCount();
    check(game.visualSettings.groundDetail, "ground surface detail starts enabled");
    frame(1075, 650, true);
    frame(1075, 650);
    frame();
    check(!game.visualSettings.groundDetail, "pause ground detail toggles off without cheats");
    frame(1075, 650, true);
    frame(1075, 650);
    frame();
    check(game.visualSettings.groundDetail, "pause ground detail toggles on again");
    click(178);
    check(game.visualSettings.vegetation == 75 && renderer.missionVegetationCount() < plants,
          "pause LESS reduces vegetation immediately without cheats");
    click(265);
    check(game.visualSettings.vegetation == 100 && renderer.missionVegetationCount() == plants,
          "pause MORE restores the seeded vegetation");
    for (int i = 0; i < 10; ++i)
        click(178);
    check(game.visualSettings.vegetation == 0 && renderer.missionVegetationCount() == 0,
          "pause vegetation stops at zero");
    for (int i = 0; i < 10; ++i)
        click(265);
    check(game.visualSettings.vegetation == 200 && renderer.missionVegetationCount() > plants,
          "pause vegetation stops at 200 percent and adds plants");
    check(game.paused && game.run->stats.duration == duration && game.run->stats.shots == 0,
          "vegetation controls never advance combat or fire the weapon");
    const auto preferences = directory / "visual.cfg";
    game.perform(Action::ToggleCanyonRiver);
    check(game.visualSettings.canyonRiver, "river layout cannot be changed inside an active mission");
    game.visualSettings.groundDetail = false;
    check(saveVisualSettings(preferences, game.visualSettings) &&
              loadVisualSettings(preferences) == game.visualSettings,
          "vegetation preference survives a settings reload");
    {
        std::ofstream legacy(preferences);
        legacy << "DEATHWARD_VISUAL 1\n175\n";
    }
    check(loadVisualSettings(preferences).vegetation == 175 && loadVisualSettings(preferences).groundDetail,
          "old vegetation preferences migrate while enabling the new floor detail");
    {
        std::ofstream legacy(preferences);
        legacy << "DEATHWARD_VISUAL 2\n175\n0\n";
    }
    check(loadVisualSettings(preferences).vegetation == 175 &&
              !loadVisualSettings(preferences).groundDetail && loadVisualSettings(preferences).canyonRiver,
          "version two preserves floor settings and enables the river trial");
    {
        std::ofstream bad(preferences);
        bad << "DEATHWARD_VISUAL 1\n-25\n";
    }
    check(loadVisualSettings(preferences) == VisualSettings{}, "invalid density restores the default");
    game.finish(EndReason::Retreat);
    game.perform(Action::Hub);
    game.paused = true;
    click(178);
    check(game.screen == Screen::Hub && game.visualSettings.vegetation == 175,
          "the same vegetation control is available while paused in town");
    auto capture = LoadImageFromScreen();
    std::filesystem::create_directories("artifacts");
    ExportImage(capture, "artifacts/vegetation-pause-controls.png");
    UnloadImage(capture);
    game.paused = false;
    game.town.player.position = game.town.mission;
    game.perform(Action::Missions);
    frame(870, 497, true);
    frame(870, 497);
    frame();
    check(!game.visualSettings.canyonRiver, "the mission board offers a working river comparison toggle");
    check(saveVisualSettings(preferences, game.visualSettings) &&
              !loadVisualSettings(preferences).canyonRiver,
          "river-off preference survives reload");
    game.launch();
    check(game.run->arena.canyon && game.run->arena.canyon->river.empty(),
          "river-off launches the original canyon geometry");
    game.close();
    std::cout << "PASS vegetation pause controls, bounds, live changes, no gameplay input and persistence\n";
}
} // namespace
int main(int argc, char **argv) {
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
        const std::string mode = argc > 1 ? argv[1] : "";
        if (mode.empty() || mode == "--arrows-only") {
            arrowInputCheck(directory, dw::MissionTheme::Mine);
            arrowInputCheck(directory, dw::MissionTheme::Canyon);
            if (mode == "--arrows-only") {
                CloseWindow();
                std::filesystem::remove_all(directory);
                return 0;
            }
        }
        if (mode == "--river-only") {
            boundaryRiverInputCheck(directory);
            interiorRiverInputCheck(directory);
            CloseWindow();
            std::filesystem::remove_all(directory);
            return 0;
        }
        if (mode == "--vegetation-only") {
            vegetationInputCheck(directory);
            CloseWindow();
            std::filesystem::remove_all(directory);
            return 0;
        }
        for (auto theme : {dw::MissionTheme::Mine, dw::MissionTheme::Canyon}) {
            if (mode != "--dynamite-only")
                shopInputCheck(directory, theme);
            if (mode != "--shop-only")
                dynamiteInputCheck(directory, theme);
        }
        if (mode == "--shop-only" || mode == "--dynamite-only") {
            CloseWindow();
            std::filesystem::remove_all(directory);
            return 0;
        }
        dw::Game game(directory / "campaign.save");
        check(game.animals.residents().size() == 5, "Black Creek loads five ambient animals");
        game.update(dw::Tick);
        const auto animalTime = game.animals.time();
        check(animalTime > 0, "hub update advances animal simulation");
        game.paused = true;
        game.update(dw::Tick);
        check(game.animals.time() == animalTime, "pause freezes animal poses and motion");
        game.paused = false;
        game.missionMenu = true;
        game.update(dw::Tick);
        check(game.animals.time() == animalTime, "mission selection freezes ambient animals");
        game.missionMenu = false;
        check(game.musicScene() == dw::MusicScene::Town, "default hub selects its town score");
        dw::Renderer renderer;
        const dw::Game::SceneryPicker pickScenery = [&](const auto &run, const auto &camera, Ray ray) {
            return renderer.pickScenery(run, camera, ray);
        };
        auto frame = [&](int x = 10, int y = 10, bool left = false, bool right = false, bool middle = false,
                         bool shift = false, float dt = dw::Tick) {
            mouseEvent(MousePosition, x, y);
            mouseEvent(left ? MouseDown : MouseUp, MOUSE_BUTTON_LEFT);
            mouseEvent(right ? MouseDown : MouseUp, MOUSE_BUTTON_RIGHT);
            mouseEvent(middle ? MouseDown : MouseUp, MOUSE_BUTTON_MIDDLE);
            mouseEvent(shift ? KeyDown : KeyUp, KEY_LEFT_SHIFT);
            game.update(dt, pickScenery);
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
        check(std::abs(game.cameraZoomPercent() - 160) < .001f, "new hub sessions start at 160% zoom");
        check(game.themeChoice == dw::ThemeChoice::Canyon,
              "new sessions offer Isaac-only canyon missions by default");
        check(!game.campaign.data().pending && game.campaign.data().history.empty(),
              "town exploration does not create a pending mission or a campaign outcome");
        const auto blackCreekArrival = game.town.spawn;
        const auto travelAngle = cameraAngle();
        const auto travelRadius = dw::distance(game.camera.position, game.camera.target);
        mouseEvent(MouseWheel, 0, 3);
        frame(1050, 734);
        frame(1050, 734, false, false, true);
        frame(1120, 734, false, false, true);
        frame(1050, 734);
        check(dw::distance(travelAngle, cameraAngle()) < .0001f &&
                  std::abs(dw::distance(game.camera.position, game.camera.target) - travelRadius) < .001f,
              "the hub travel control blocks camera zoom and rotation behind it");
        const auto beforeTravel = game.town.player.position;
        frame(1050, 734, true);
        check(game.activeHub == dw::HubKind::BlackCreek && !game.town.destination() &&
                  dw::distance(beforeTravel, game.town.player.position) < .001f,
              "pressing hub travel does not move the character or click through to the ground");
        frame(1050, 734);
        check(game.activeHub == dw::HubKind::Frontier && game.screen == dw::Screen::Hub && !game.paused &&
                  game.town.loaded() && dw::distance(blackCreekArrival, game.town.spawn) > 20,
              "the visible travel button switches directly to Frontier's scene and navigation");
        const auto frontierArrival = game.town.player.position;
        check(game.animals.residents().empty(), "Black Creek animals do not leak into Frontier");
        mouseEvent(KeyDown, KEY_W);
        for (int i = 0; i < 20; ++i)
            frame(700, 400);
        mouseEvent(KeyUp, KEY_W);
        frame();
        check(dw::distance(frontierArrival, game.town.player.position) > .3f &&
                  game.town.walkable(game.town.player.position),
              "WASD moves through the second hub's imported terrain");
        const auto frontierPixel = GetWorldToScreen(game.town.spawn, game.camera);
        click(int(frontierPixel.x), int(frontierPixel.y));
        for (int i = 0; i < 120; ++i)
            frame();
        check(dw::distance(frontierArrival, game.town.player.position) < .7f,
              "mouse ground targeting reaches the correct elevation in Frontier");
        pressKey(KEY_F4);
        check(game.editorRequested && game.hubDirectory().filename() == "frontier",
              "Frontier's editor targets its own pack instead of the first town");
        game.editorRequested = false;
        click(1050, 734);
        check(game.activeHub == dw::HubKind::BlackCreek &&
                  dw::distance(game.town.spawn, blackCreekArrival) < .001f && !game.campaign.data().pending &&
                  game.campaign.data().history.empty(),
              "the visible return button restores Black Creek without creating a campaign outcome");
        click(590, 734);
        click(620, 624);
        check(game.activeHub == dw::HubKind::Frontier && !game.paused,
              "pause-screen travel remains available alongside the visible hub button");
        click(590, 734);
        click(620, 624);
        check(game.activeHub == dw::HubKind::BlackCreek && !game.paused,
              "pause-screen return travel remains available");
        check(game.animals.residents().size() == 5, "return travel reloads town animals");
        click(1050, 680);
        check(game.activeHub == dw::HubKind::Redstone && game.hubDirectory().filename() == "redstone" &&
                  game.town.loaded() && game.townObjects.solids().size() == 4 &&
                  game.musicScene() == dw::MusicScene::Canyon,
              "the second travel button opens the canyon hub with its convoy and canyon score");
        pressKey(KEY_F4);
        check(game.editorRequested && game.hubDirectory().filename() == "redstone",
              "the canyon editor targets its independent authored pack");
        game.editorRequested = false;
        click(1050, 680);
        check(game.activeHub == dw::HubKind::Frontier, "Redstone offers direct travel to Frontier");
        click(590, 734);
        click(620, 676);
        check(game.activeHub == dw::HubKind::Redstone && !game.paused,
              "the pause menu offers direct travel to the canyon");
        click(1050, 734);
        check(game.activeHub == dw::HubKind::BlackCreek && game.campaign.data().history.empty(),
              "travel from the canyon returns to Black Creek without a mission outcome");
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
        // Approach until the board is in view at the closer starting zoom.
        check(game.town.moveTo(game.town.mission), "the board approach fixture has a walkable route");
        for (int i = 0; i < 1800 && dw::distance(game.town.player.position, game.town.mission) > 6; ++i)
            game.town.step({}, dw::Tick);
        game.town.stop();
        game.updateCamera(10);
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
        check(game.musicScene() == dw::MusicScene::Canyon, "peaceful canyon arrival uses exploration music");
        check(game.run->arena.theme == dw::MissionTheme::Canyon &&
                  game.campaign.data().pending->expedition == "Redstone Canyon",
              "the selected canyon theme reaches gameplay and the initial campaign checkpoint");
        check(game.debug && !game.debugPanelOpen && game.run->roomClear && game.run->livingEnemies() == 0,
              "new games start with hidden cheats enabled and an open, enemy-free starting room");
        // A real seeded pile overlaps a passage's generous click area at wide zoom.
        // Clicking the pile must collect it rather than taking that passage.
        const auto moneyArrival = game.run->player.position;
        const auto moneyCamera = game.camera;
        const auto nearbyCoin = *std::min_element(
            game.run->moneyPickups.begin(), game.run->moneyPickups.end(), [&](const auto &a, const auto &b) {
                return dw::distance(a.position, moneyArrival) < dw::distance(b.position, moneyArrival);
            });
        check(game.run->arena.roomAt(nearbyCoin.position) == 0, "pickup fixture uses the quiet room");
        const auto startingMoney = game.run->money();
        game.camera.target = dw::add(moneyArrival, {0, .1f, 0});
        game.camera.position = dw::add(game.camera.target, dw::mul({23, 30, 23}, 1.284f));
        auto moneyPoint = nearbyCoin.position;
        moneyPoint.y = .4f;
        const auto moneyPixel = GetWorldToScreen(moneyPoint, game.camera);
        frame(int(moneyPixel.x), int(moneyPixel.y), true);
        for (int i = 0; i < 240 && game.run->money() < startingMoney + nearbyCoin.value; ++i)
            frame();
        check(game.run->money() >= startingMoney + nearbyCoin.value && game.run->room == 0 &&
                  game.run->stats.shots == 0,
              "a coin near a passage takes priority without leaving the room or firing");
        for (int i = 0; i < 60; ++i)
            frame();
        game.run->player.position = moneyArrival;
        game.camera = moneyCamera;
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
        game.run->moneyPickups = {{{destination.x, .85f, destination.z}, 3, 1, false}};
        const auto moneyBeforePickup = game.run->money();
        destination.y = 0;
        auto point = GetWorldToScreen(destination, game.camera);
        BeginDrawing();
        renderer.draw(game);
        rlDrawRenderBatchActive();
        const auto coinImage = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        check(ExportImage(coinImage, "artifacts/money-ground.png"), "save the coin rendering capture");
        UnloadImage(coinImage);
        EndDrawing();
        click(int(point.x), int(point.y));
        check(game.run->moveDestination().has_value(), "left-clicking ground queues a route");
        for (int i = 0; i < 200; ++i)
            frame();
        destination.y = 0.85f;
        check(dw::distance(game.run->player.position, destination) < 0.15f,
              "mouse ray and navigation reach clicked ground point");
        check(game.run->stats.shots == 0, "left-clicking ground never fires");
        check(game.run->money() == moneyBeforePickup + 3 && game.run->moneyPickups.empty() &&
                  game.campaign.data().pending->moneyCollected == game.run->moneyCollected,
              "clicking a coin approaches it, collects it and saves the earnings without firing");
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
        check(game.run->findEnemy(target)->hp <= 10000 - dw::RevolverDamage * 10,
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
        const auto audioDefaults = game.audioSettings;
        click(230, 338);
        click(282, 390);
        click(230, 442);
        click(282, 494);
        check(std::abs(game.audioSettings.master - (audioDefaults.master - .1f)) < .001f &&
                  std::abs(game.audioSettings.effects - (audioDefaults.effects + .1f)) < .001f &&
                  std::abs(game.audioSettings.ambience - (audioDefaults.ambience - .1f)) < .001f &&
                  std::abs(game.audioSettings.music - (audioDefaults.music + .1f)) < .001f,
              "pause audio controls adjust each independent volume");
        click(90, 569);
        check(game.audioSettings.muted, "pause audio mute toggles independently of cheats");
        click(90, 569);
        click(237, 569);
        check(!game.audioSettings.muted &&
                  std::any_of(game.audioCues.cues().begin(), game.audioCues.cues().end(),
                              [](const auto &cue) { return cue.kind == dw::AudioCueKind::Test; }),
              "test button queues an audio preview without advancing gameplay");
        for (int i = 0; i < 12; ++i)
            game.perform(dw::Action::MasterUp);
        check(game.audioSettings.master == 1, "audio volume is capped at 100 percent");
        for (int i = 0; i < 12; ++i)
            game.perform(dw::Action::MasterDown);
        check(game.audioSettings.master == 0, "audio volume cannot become negative");
        for (int i = 0; i < 12; ++i)
            game.perform(dw::Action::MusicDown);
        check(game.audioSettings.music == 0 && game.audioSettings.effects == audioDefaults.effects + .1f,
              "music can be muted independently of effects");
        game.audioSettings = audioDefaults;
        frame();
        std::filesystem::create_directories("artifacts");
        auto audioPanel = LoadImageFromScreen();
        ExportImage(audioPanel, "artifacts/audio-pause-controls.png");
        UnloadImage(audioPanel);
        check(game.run->stats.duration == duration && game.run->stats.shots == shots,
              "audio controls never fire or resume the simulation");
        click(1214, 329);
        click(1214, 424);
        check(game.run->player.maxHp == dw::StartingHealth + 25 &&
                  game.run->player.hp == dw::StartingHealth + 25 &&
                  game.run->player.shotDamage == dw::RevolverDamage + 4 && game.paused,
              "pause controls adjust health and damage immediately without resuming");
        click(1156, 329);
        click(1156, 424);
        check(game.run->player.maxHp == dw::StartingHealth &&
                  game.run->player.shotDamage == dw::RevolverDamage,
              "pause controls can lower health and damage");
        pressKey(KEY_EQUAL);
        pressKey(KEY_KP_ADD, true);
        check(game.run->player.maxHp == dw::StartingHealth + 25 &&
                  game.run->player.shotDamage == dw::RevolverDamage + 4,
              "keyboard and keypad stat controls work while paused");
        click(1050, 494);
        check(game.run->player.maxHp == dw::StartingHealth &&
                  game.run->player.shotDamage == dw::RevolverDamage && game.run->stats.duration == duration,
              "restore defaults changes stats while simulation remains frozen");
        click(620, 445);
        check(!game.paused, "mouse resumes the expedition");
        check(game.run->stats.shots == shots, "HUD and paused clicks never fire the revolver");
        pressKey(KEY_MINUS);
        pressKey(KEY_EQUAL, true);
        check(game.run->player.shotDamage == dw::RevolverDamage - 4 &&
                  game.run->player.maxHp == dw::StartingHealth + 25 && !game.debugPanelOpen,
              "live stat hotkeys work while the cheat overlay stays hidden");
        pressKey(KEY_F1);
        pressKey(KEY_EQUAL);
        game.perform(dw::Action::HealthUp);
        pressKey(KEY_HOME);
        check(game.run->player.shotDamage == dw::RevolverDamage - 4 &&
                  game.run->player.maxHp == dw::StartingHealth + 25,
              "stat shortcuts and actions are disabled with cheats off");
        pressKey(KEY_F1);
        pressKey(KEY_HOME);
        check(game.run->player.shotDamage == dw::RevolverDamage &&
                  game.run->player.maxHp == dw::StartingHealth,
              "Home restores defaults during play");
        game.run->godMode = true;
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
        const float framingOffset = 200 / game.cameraZoomPercent();
        const auto cameraGoal = dw::sub(game.run->player.position, {framingOffset, 0.85f, framingOffset});
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
        check(game.run->livingEnemies() >= 20 && game.run->livingEnemies() <= 40,
              "F4 spawns twenty testing enemies plus any attached companions");
        pressKey(KEY_F3, true);
        const auto selectedBefore = game.selectedMonster;
        pressKey(KEY_PERIOD);
        check(game.selectedMonster == selectedBefore + 1, "period selects the next catalog monster");
        pressKey(KEY_F4, true);
        check(game.run->livingEnemies() == 1 &&
                  game.run->enemies.front().monster == dw::monsterCatalog()[size_t(game.selectedMonster)].id,
              "Shift+F4 spawns the selected ID instead of a random crowd");
        pressKey(KEY_COMMA);
        check(game.selectedMonster == selectedBefore, "comma selects the previous catalog monster");
        pressKey(KEY_F3, true);
        pressKey(KEY_F6);
        pressKey(KEY_F6, true);
        check(game.run->items.size() == dw::ItemCount && game.run->keys == 3,
              "F6 grants all effects and Shift+F6 supplies testing keys");
        pressKey(KEY_F12, true);
        check(game.run->room == 2 && !game.run->roomClear && game.run->livingEnemies() > 0,
              "Shift+F12 restarts the current room with its enemy group already present");
        check(game.musicScene() == dw::MusicScene::Combat,
              "an active ordinary encounter selects combat music");
        game.paused = true;
        pressKey(KEY_F12);
        check(game.run->room == 3 && !game.paused &&
                  dw::distance(game.camera.target, dw::sub(game.run->player.position,
                                                           {framingOffset, 0.85f, framingOffset})) < 0.01f,
              "F12 skips to the next room, resumes and immediately follows with the camera");
        pressKey(KEY_F7);
        check(game.run->room == dw::Simulation::FinalRoom && !game.run->boss() && game.run->roomThreats() > 0,
              "F7 jumps to the canyon's final monster encounter without a Western boss");
        check(game.musicScene() == dw::MusicScene::Boss, "canyon finale uses boss music without a Sheriff");
        pressKey(KEY_F3, true);
        pressKey(KEY_F7);
        check(!game.run->roomClear && !game.run->bossKilled && game.run->roomThreats() > 0,
              "F7 can replay a cleared canyon finale");
        const auto finalPopulation = game.run->livingEnemies();
        pressKey(KEY_F10);
        pressKey(KEY_O);
        pressKey(KEY_F1);
        check(!game.debug && !game.run->godMode && !game.slow && !game.collisionDebug,
              "turning cheat mode off disables invincibility, slow time and collision overlays");
        pressKey(KEY_F3);
        check(game.run->livingEnemies() == finalPopulation, "F3 is disabled again after leaving cheat mode");
        pressKey(KEY_F1);
        game.paused = true;
        pressKey(KEY_EQUAL);
        pressKey(KEY_EQUAL, true);
        pressKey(KEY_F8);
        check(!game.run && game.screen == dw::Screen::Summary &&
                  game.lastSummary.reason == dw::EndReason::Victory,
              "F8 completes the expedition immediately while paused");
        check(game.musicScene() == dw::MusicScene::Victory,
              "successful completion selects the victory score");
        game.perform(dw::Action::Hub);
        game.selectHub(dw::HubKind::Frontier);
        game.launch();
        check(game.run->player.hp == dw::StartingHealth + 25 &&
                  game.run->player.maxHp == dw::StartingHealth + 25 &&
                  game.run->player.shotDamage == dw::RevolverDamage + 4 && game.run->items.empty(),
              "player settings survive mission completion and hub travel without retaining item penalties");
        pressKey(KEY_HOME);
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
        check(std::abs(game.cameraZoomPercent() - 160) < .001f, "new missions retain the starting 160% zoom");
        const float referenceDistance = defaultDistance * 1.6f;
        const auto originalAngle = dw::unit(dw::sub(game.camera.position, game.camera.target));
        const auto beforeZoom = game.run->player.position;
        mouseEvent(MouseWheel, 0, 100);
        frame();
        check(cameraDistance() < defaultDistance && cameraDistance() > referenceDistance * 0.35f,
              "scrolling up smoothly moves the camera closer");
        check(std::abs(game.cameraZoomPercent() - 100 * referenceDistance / cameraDistance()) < .01f,
              "zoom display follows the actual smoothed camera distance");
        settleCamera();
        const float closestDistance = cameraDistance();
        check(std::abs(closestDistance - referenceDistance * 0.35f) < 0.01f,
              "large wheel input stops at the close zoom limit");
        check(dw::distance(beforeZoom, game.run->player.position) == 0 && game.run->stats.shots == 0 &&
                  game.run->player.dodge == 0,
              "scrolling never moves, shoots or dodges");
        mouseEvent(MouseWheel, 0, -100);
        frame(850, 711);
        settleCamera();
        check(std::abs(cameraDistance() - closestDistance) < 0.01f, "HUD controls ignore scrolling");
        mouseEvent(MouseWheel, 0, -100);
        frame(1100, 10);
        settleCamera();
        check(std::abs(cameraDistance() - closestDistance) < .01f,
              "the zoom readout blocks scrolling through the HUD");
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
        check(std::abs(widestDistance - referenceDistance * 1.5f) < 0.01f &&
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
        check(game.musicScene() == dw::MusicScene::Defeat, "death changes the score immediately");
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
        check(game.musicScene() == dw::MusicScene::Defeat,
              "defeat music continues across the summary transition");
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
        {
            dw::Game frontier(directory / "frontier.save", dw::HubKind::Frontier);
            check(frontier.town.loaded() && frontier.activeHub == dw::HubKind::Frontier,
                  "explicit startup hub loads Frontier directly");
            check(frontier.musicScene() == dw::MusicScene::Frontier, "Frontier selects its own hub score");
            const auto arrival = frontier.town.spawn;
            frontier.perform(dw::Action::Missions);
            for (int i = 0; i < 1200 && !frontier.missionMenu; ++i)
                frontier.update(dw::Tick);
            check(frontier.missionMenu, "Frontier mission board is reachable through normal hub controls");
            frontier.seedText = "1866";
            frontier.themeChoice = dw::ThemeChoice::Mine;
            frontier.launch();
            check(frontier.musicScene() == dw::MusicScene::Mine, "mine exploration has its own score");
            check(frontier.run && !frontier.selectHub(dw::HubKind::BlackCreek),
                  "an active mission prevents hub travel");
            frontier.finish(dw::EndReason::Retreat);
            check(frontier.musicScene() == dw::MusicScene::Frontier, "retreat does not play victory music");
            frontier.perform(dw::Action::Hub);
            check(frontier.activeHub == dw::HubKind::Frontier && !frontier.campaign.data().pending &&
                      dw::distance(frontier.town.player.position, dw::add(arrival, {0, .85f, 0})) < .001f,
                  "mission results return to the same Frontier hub and its arrival point");
            frontier.close();
        }
        CloseWindow();
        std::filesystem::remove_all(directory);
        std::cout << "PASS original town movement, station approach, mission seeds, launch and return loop\n";
        std::cout << "PASS Frontier travel, movement, picking, editor selection and mission return\n";
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
