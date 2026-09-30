#include "raylib.h"
#include "raymath.h"
#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "render/Renderer.hpp"
#include "render/TownScene.hpp"
#include "render/WesternScene.hpp"
#include "rlgl.h"
#include "world/HubWorld.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
Camera3D view(Vector3 player, float yaw = 0, float zoom = .625f) {
    const auto center = add(player, {0, .1f, 0});
    return {add(center, mul(rotateY({23, 30, 23}, yaw), zoom)), center, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
}
int colorDifference(Color a, Color b) {
    return std::abs(int(a.r) - b.r) + std::abs(int(a.g) - b.g) + std::abs(int(a.b) - b.b);
}
template <class Draw, class Late, class Configure>
void verifyVisibility(Vector3 player, const Camera3D &camera, Draw draw, Late late, Configure configure,
                      const std::string &name) {
    auto render = [&](bool fade, bool marker, bool compositeOccluders = true) {
        configure(fade);
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);
        draw();
        if (marker)
            DrawSphere(add(player, {0, .1f, 0}), .38f, MAGENTA);
        if (compositeOccluders)
            late();
        EndMode3D();
        rlDrawRenderBatchActive();
        auto image = LoadImageFromScreen();
        EndDrawing();
        return image;
    };
    auto opaque = render(false, false), hidden = render(false, true);
    auto faded = render(true, false), visible = render(true, true);
    auto removed = render(true, false, false);
    int before = 0, after = 0, outside = 0, translucent = 0;
    const auto center = GetWorldToScreen(add(player, {0, .1f, 0}), camera);
    const auto right = Vector3Normalize(Vector3CrossProduct(sub(camera.target, camera.position), camera.up));
    const auto edge = GetWorldToScreen(add(add(player, {0, .1f, 0}), mul(right, 1.5f)), camera);
    const float radius = Vector2Distance(center, edge);
    for (int y = 0; y < opaque.height; ++y)
        for (int x = 0; x < opaque.width; ++x) {
            before += colorDifference(GetImageColor(opaque, x, y), GetImageColor(hidden, x, y)) > 20;
            after += colorDifference(GetImageColor(faded, x, y), GetImageColor(visible, x, y)) > 20;
            translucent += colorDifference(GetImageColor(faded, x, y), GetImageColor(removed, x, y)) > 3;
            if (Vector2Distance(center, {float(x), float(y)}) > radius + 2)
                outside += colorDifference(GetImageColor(opaque, x, y), GetImageColor(faded, x, y)) > 3;
        }
    std::cout << name << " / marker pixels " << before << " -> " << after << ", outside " << outside
              << ", translucent surface " << translucent << std::endl;
    check(after > 25, "the player is visible through the alpha-blended occluder");
    check(before < after / 4, "the fixture hides most of the player and fading restores visibility");
    check(outside > 100, "the whole blocking object changes beyond the former circular mask");
    check(translucent > 100, "blocking scenery remains visible instead of disappearing completely");
    auto restored = render(false, false);
    int restoredDifferences = 0;
    for (int y = 0; y < opaque.height; ++y)
        for (int x = 0; x < opaque.width; ++x)
            restoredDifferences +=
                colorDifference(GetImageColor(opaque, x, y), GetImageColor(restored, x, y)) > 3;
    check(restoredDifferences == 0, "disabling occlusion restores the original complete scenery");
    UnloadImage(restored);
    for (auto image : {opaque, hidden, faded, visible, removed})
        UnloadImage(image);

    // Capture the actual animated bandit, lighting and post processing for visual review.
    PlayerModel bandit;
    Player actor;
    actor.position = player;
    bandit.update(actor, 0, &actor);
    PostProcess post;
    for (bool fade : {false, true}) {
        configure(fade);
        BeginDrawing();
        post.begin(SKYBLUE, distance(camera.position, camera.target));
        BeginMode3D(camera);
        draw();
        bandit.draw(actor);
        late();
        EndMode3D();
        post.end();
        rlDrawRenderBatchActive();
        auto image = LoadImageFromScreen();
        std::filesystem::create_directories("artifacts");
        ExportImage(image, ("artifacts/occlusion-" + name + (fade ? "-after.png" : "-before.png")).c_str());
        UnloadImage(image);
        EndDrawing();
    }
}
void townCheck(HubKind hub) {
    TownScene scene;
    HubWorld town;
    check(scene.load(TownScene::assetDirectory(hub)), "town assets load with the occlusion shader");
    check(town.load(TownScene::assetDirectory(hub) / "town.nav"), "town navigation loads");
    Vector3 player{};
    Camera3D camera{};
    bool found = false;
    for (int z = -24; z <= 24 && !found; z += 2)
        for (int x = -24; x <= 24 && !found; x += 2) {
            Vector3 p = add(town.spawn, {float(x), 0, float(z)});
            if (!town.walkable(p))
                continue;
            p.y = town.height(p) + .85f;
            const auto candidate = view(p);
            const Ray ray{candidate.position, unit(sub(candidate.target, candidate.position))};
            const auto picked = scene.pick(ray);
            if (!picked)
                continue;
            const auto &instance = scene.document().instances[*picked];
            const auto &asset = scene.document().assets[instance.asset];
            if (asset.label.find("Bld") == std::string::npos && asset.label.find("Rock") == std::string::npos)
                continue;
            float nearest = 1e9f;
            for (int mesh = asset.first; mesh < asset.first + asset.count; ++mesh) {
                const auto hit = GetRayCollisionMesh(ray, scene.model().meshes[mesh], instance.transform);
                if (hit.hit)
                    nearest = std::min(nearest, hit.distance);
            }
            if (nearest > 2 && nearest < distance(candidate.position, candidate.target) - 2) {
                found = true;
                player = p;
                camera = candidate;
                std::cout << hubFolder(hub) << " blocker " << asset.label << " player " << p.x << "," << p.y
                          << "," << p.z << std::endl;
            }
        }
    check(found, "find a walkable player position behind an imported building or rock");
    scene.prepareLighting(camera);
    verifyVisibility(
        player, camera, [&] { scene.draw(player); },
        [&] {
            scene.drawOccluders();
            scene.draw(player, true);
        },
        [&](bool enabled) { scene.setPlayerOcclusion(camera, player, enabled); }, hubFolder(hub));
    check(town.walkable(player), "rendering leaves town collision unchanged");
}
void enemyOutlineCheck(Vector3 enemyPosition, const Camera3D &camera, const std::string &name) {
    Simulation run(69175541, 1, {}, MissionTheme::Canyon);
    // Isolate the actor under test from the mission's prepopulated neighboring rooms.
    for (auto &room : run.rooms)
        room.residents.clear();
    bool found = false;
    for (const auto &room : run.arena.rooms) {
        for (float z = room.bounds.min.z; z < room.bounds.max.z && !found; z += 2)
            for (float x = room.bounds.min.x; x < room.bounds.max.x && !found; x += 2) {
                const Vector3 p{x, .85f, z};
                if (run.arena.blocked(p, .6f) || distance(p, enemyPosition) > 40)
                    continue;
                PlayerOcclusion sight;
                sight.set(camera, p);
                bool clear = true;
                for (auto target : sight.targets())
                    clear = clear && !run.arena.canyon->trace(camera.position, target).hit;
                if (clear) {
                    found = true;
                    run.player.position = p;
                }
            }
        if (found)
            break;
    }
    check(found, "find a clear player view while the enemy stays behind an opaque canyon wall");
    Renderer renderer;
    auto capture = [&] {
        BeginDrawing();
        renderer.drawWorld(run, camera, false);
        rlDrawRenderBatchActive();
        auto result = LoadImageFromScreen();
        EndDrawing();
        return result;
    };
    run.enemies.clear();
    auto baseline = capture();
    auto outlinePixels = [&](Image frame) {
        int result = 0;
        for (int y = 0; y < frame.height; ++y)
            for (int x = 0; x < frame.width; ++x) {
                const auto c = GetImageColor(frame, x, y);
                result += c.r > 230 && c.g < 130 && c.b < 100 &&
                          colorDifference(c, GetImageColor(baseline, x, y)) > 30;
            }
        return result;
    };
    for (int type : {10, 13, 21}) {
        run.enemies.clear();
        check(run.spawnMonster(monsterId(type), enemyPosition) != 0, "spawn an occluded catalog enemy");
        auto frame = capture();
        const int pixels = outlinePixels(frame);
        std::cout << name << " enemy " << type << " outline pixels " << pixels << std::endl;
        check(pixels > 15, "actual hidden monster geometry gets a visible outline through the canyon");
        ExportImage(frame, ("artifacts/enemy-outline-" + name + "-" + std::to_string(type) + ".png").c_str());
        UnloadImage(frame);
    }
    auto &enemy = run.enemies.front();
    for (auto state : {EnemyState::Buried, EnemyState::Teleporting}) {
        enemy.state = state;
        auto frame = capture();
        check(outlinePixels(frame) == 0, "burrowing and teleporting do not reveal an absent body");
        UnloadImage(frame);
    }
    enemy.state = EnemyState::Ready;
    enemy.friendly = true;
    auto friendly = capture();
    check(outlinePixels(friendly) == 0, "friendly monsters do not get hostile outlines");
    UnloadImage(friendly);
    enemy.friendly = false;
    enemy.alive = false;
    auto dead = capture();
    check(outlinePixels(dead) == 0, "dead enemies leave no stale silhouette");
    UnloadImage(dead);
    UnloadImage(baseline);
}
void canyonCheck() {
    Arena arena(69175541, MissionTheme::Canyon);
    WesternScene scene;
    scene.prepare(arena);
    check(scene.terrainReady(), "canyon terrain builds with the occlusion shader");
    Vector3 player{};
    float yaw = 0;
    bool found = false;
    for (const auto &room : arena.rooms) {
        for (float z = room.bounds.min.z; z < room.bounds.max.z && !found; z += 2)
            for (float x = room.bounds.min.x; x < room.bounds.max.x && !found; x += 2) {
                Vector3 p{x, .85f, z};
                if (arena.blocked(p, .6f))
                    continue;
                for (float angle : {0.f, Pi / 2, Pi, -Pi / 2}) {
                    const auto camera = view(p, angle);
                    const auto hit = arena.canyon->trace(camera.position, camera.target);
                    if (hit.hit && hit.t > .1f && hit.t < .8f) {
                        found = true;
                        player = p;
                        yaw = angle;
                        break;
                    }
                }
            }
        if (found)
            break;
    }
    check(found, "find a walkable player position behind the full-height canyon mesh");
    for (float zoom : {.625f, 1.5f}) {
        const auto camera = view(player, yaw, zoom);
        verifyVisibility(
            player, camera, [&] { scene.draw(player); },
            [&] {
                scene.drawOccluders();
                scene.drawGlass();
            },
            [&](bool enabled) { scene.setPlayerOcclusion(camera, player, enabled); },
            zoom < 1 ? "canyon" : "canyon-wide");
        check(arena.canyon->trace(camera.position, camera.target).hit,
              "fading canyon wall sections leaves collision intact");
        int faded = 0, retained = 0;
        for (const auto &section : scene.terrainChunks()) {
            check(section.rock || !section.faded, "canyon floor sections stay opaque");
            faded += section.faded;
            retained += section.rock && !section.faded;
        }
        check(faded > 0 && retained > 0, "only obstructing canyon rock sections become translucent");
        enemyOutlineCheck(player, camera, zoom < 1 ? "canyon" : "canyon-wide");
    }
}
void residentRenderCheck(MissionTheme theme) {
    Simulation run(1866, 1, {}, theme);
    int room = 1;
    while (run.roomEnemies(room).empty())
        ++room;
    const int passage = run.arena.rooms[size_t(room)].passages.front();
    const auto &door = run.arena.passages[size_t(passage)];
    auto watcher = mul(add(door.from, door.to), .5f);
    if (run.arena.canyon)
        for (const auto &point : run.arena.canyon->trails[size_t(passage)])
            if (run.arena.roomAt(point) < 0) {
                watcher = point;
                break;
            }
    watcher.y = .85f;
    check(run.arena.roomAt(watcher) < 0, "render fixture watches from the corridor");
    run.player.position = watcher;
    for (int other = 0; other < RoomCount; ++other)
        if (other != room)
            run.rooms[size_t(other)].residents.clear();
    const auto &group = run.roomEnemies(room);
    const auto nearest = std::min_element(group.begin(), group.end(), [&](const Enemy &a, const Enemy &b) {
        return distance(a.position, watcher) < distance(b.position, watcher);
    });
    const auto camera = view(nearest->position, 0, .45f);
    Renderer renderer;
    auto capture = [&] {
        BeginDrawing();
        renderer.drawWorld(run, camera, false);
        rlDrawRenderBatchActive();
        const auto result = LoadImageFromScreen();
        EndDrawing();
        return result;
    };
    auto saved = std::move(run.rooms[size_t(room)].residents);
    run.rooms[size_t(room)].residents = {};
    auto empty = capture();
    run.rooms[size_t(room)].residents = std::move(saved);
    auto before = capture();
    for (int i = 0; i < 23; ++i)
        run.step({});
    auto after = capture();
    check(run.room == 0 && run.enemies.empty(), "rendered neighbors remain dormant in the corridor");
    int actorPixels = 0, animationPixels = 0;
    const auto center = GetWorldToScreen(nearest->position, camera);
    for (int y = std::max(0, int(center.y) - 70); y < std::min(before.height, int(center.y) + 70); ++y)
        for (int x = std::max(0, int(center.x) - 70); x < std::min(before.width, int(center.x) + 70); ++x) {
            actorPixels += colorDifference(GetImageColor(empty, x, y), GetImageColor(before, x, y)) > 18;
            animationPixels += colorDifference(GetImageColor(before, x, y), GetImageColor(after, x, y)) > 8;
        }
    const std::string name = theme == MissionTheme::Canyon ? "canyon" : "mine";
    std::cout << name << " resident pixels " << actorPixels << ", animation pixels " << animationPixels
              << std::endl;
    check(actorPixels > 30 && animationPixels > 3,
          "actual resident geometry is visible and animates before room entry");
    ExportImage(before, ("artifacts/resident-enemies-" + name + "-before.png").c_str());
    ExportImage(after, ("artifacts/resident-enemies-" + name + "-after.png").c_str());
    for (auto image : {empty, before, after})
        UnloadImage(image);
}
void sceneryInputCheck(MissionTheme theme, float yaw, bool transparent) {
    const auto directory = std::filesystem::temp_directory_path() /
                           ("deathward-transparent-input-" +
                            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Game game(directory / "campaign.save");
    game.seedText = "69175541";
    game.themeChoice = theme == MissionTheme::Canyon ? ThemeChoice::Canyon : ThemeChoice::Mine;
    game.launch();
    check(bool(game.run), "launch the transparency input fixture");
    auto &run = *game.run;
    run.debugScenario = run.godMode = true;
    run.roomClear = false;
    for (auto &room : run.rooms)
        room.residents.clear();
    WesternScene scene;
    scene.prepare(run.arena);
    Vector3 player{}, enemyPoint{}, groundPoint{};
    Vector2 enemyPixel{}, groundPixel{};
    Camera3D camera{};
    bool found = false;
    std::array<int, 4> candidates{};
    for (int room = 0; room < RoomCount && !found; ++room) {
        const auto bounds = run.arena.rooms[size_t(room)].bounds;
        for (float z = bounds.min.z + 2; z < bounds.max.z - 2 && !found; z += 2)
            for (float x = bounds.min.x + 2; x < bounds.max.x - 2 && !found; x += 2) {
                const Vector3 p{x, .85f, z};
                if (run.arena.blocked(p, .65f))
                    continue;
                const auto candidate = view(p, yaw);
                for (int direction = 0; direction < 8 && !found; ++direction) {
                    const auto enemy =
                        add(p, rotateY({transparent ? 1.8f : 6.f, 0, 0}, float(direction) * Pi / 4));
                    if (run.arena.roomAt(enemy) != room || run.arena.blocked(enemy, .8f) ||
                        !run.arena.clear(p, enemy, .3f))
                        continue;
                    auto pixel = GetWorldToScreen(add(enemy, {0, -.2f, 0}), candidate);
                    pixel = {float(int(pixel.x)), float(int(pixel.y))};
                    const auto ray = GetScreenToWorldRay(pixel, candidate);
                    const auto body = GetRayCollisionBox(
                        ray, {{enemy.x - .6f, 0, enemy.z - .6f}, {enemy.x + .6f, 2.5f, enemy.z + .6f}});
                    if (!body.hit ||
                        !run.arena.trace(ray.position, add(ray.position, mul(ray.direction, body.distance)))
                             .hit)
                        continue;
                    ++candidates[0];
                    scene.setPlayerOcclusion(candidate, p, false);
                    const auto opaque = scene.pick(ray, p);
                    if (!opaque.hit || opaque.distance >= body.distance - .1f)
                        continue;
                    ++candidates[1];
                    scene.setPlayerOcclusion(candidate, p);
                    const auto visibleHit = scene.pick(ray, p);
                    const bool stillBlocked = visibleHit.hit && visibleHit.distance < body.distance;
                    if (stillBlocked == transparent)
                        continue;
                    ++candidates[2];
                    auto floorPixel = GetWorldToScreen({enemy.x, 0, enemy.z}, candidate);
                    floorPixel = {float(int(floorPixel.x)), float(int(floorPixel.y))};
                    const auto floorRay = GetScreenToWorldRay(floorPixel, candidate);
                    const float t = -floorRay.position.y / floorRay.direction.y;
                    const auto floorHit = scene.pick(floorRay, p);
                    const bool floorBlocked = floorHit.hit && floorHit.distance < t - .15f;
                    if (floorBlocked == transparent)
                        continue;
                    ++candidates[3];
                    check(run.arena.trace(ray.position, add(ray.position, mul(ray.direction, body.distance)))
                              .hit,
                          "fading leaves the camera obstruction physically solid");
                    player = p;
                    enemyPoint = enemy;
                    enemyPixel = pixel;
                    groundPixel = floorPixel;
                    groundPoint = add(floorRay.position, mul(floorRay.direction, t));
                    groundPoint.y = .85f;
                    camera = candidate;
                    run.room = room;
                    found = true;
                }
            }
    }
    std::cout << "Pointer fixture " << int(theme) << " yaw " << yaw << " transparent " << transparent
              << " candidates " << candidates[0] << "/" << candidates[1] << "/" << candidates[2] << "/"
              << candidates[3] << std::endl;
    check(found, "find an enemy behind the requested transparent or opaque scenery");
    run.player.position = player;
    const auto target = run.spawnMonster(monsterId(12), enemyPoint); // Stationary Horf.
    run.findEnemy(target)->cooldown = 1000;
    run.findEnemy(target)->hp = run.findEnemy(target)->maxHp = 10000;
    Renderer renderer;
    const Game::SceneryPicker picker = [&](const auto &simulation, const auto &view, Ray ray) {
        return renderer.pickScenery(simulation, view, ray);
    };
    auto frame = [&](Vector2 pixel, bool left = false, bool right = false, bool shift = false,
                     bool renderedPicker = true) {
        game.camera = camera;
        PlayAutomationEvent({0, 7, {int(pixel.x), int(pixel.y), 0, 0}});
        PlayAutomationEvent({0, left ? 6u : 5u, {MOUSE_BUTTON_LEFT, 0, 0, 0}});
        PlayAutomationEvent({0, right ? 6u : 5u, {MOUSE_BUTTON_RIGHT, 0, 0, 0}});
        PlayAutomationEvent({0, shift ? 2u : 1u, {KEY_LEFT_SHIFT, 0, 0, 0}});
        game.update(Tick, renderedPicker ? picker : Game::SceneryPicker{});
        BeginDrawing();
        renderer.draw(game);
        EndDrawing();
        check(game.error.empty(), "transparency input never causes a game error");
    };
    frame(enemyPixel, false, false, false, false);
    check(game.hoveredEnemy == target, "enemy aiming ignores scenery even without a renderer");
    frame(enemyPixel);
    check(game.hoveredEnemy == target, "transparent and opaque scenery permit enemy body selection");
    const auto start = run.player.position;
    frame(enemyPixel, true);
    check(run.stats.shots == 1 && distance(start, run.player.position) < .001f,
          "left click attacks through foreground scenery without issuing movement");
    for (int i = 0; i < 24; ++i)
        frame(enemyPixel, true);
    check(run.findEnemy(target)->hp < 10000, "bullets reach the visible target along clear physical space");
    const std::string name = (theme == MissionTheme::Canyon ? "canyon" : "mine") +
                             std::string(yaw == 0 ? "" : "-rotated") +
                             (transparent ? "-transparent" : "-solid");
    BeginDrawing();
    renderer.draw(game);
    rlDrawRenderBatchActive();
    const auto capture = LoadImageFromScreen();
    check(ExportImage(capture, ("artifacts/scenery-aim-" + name + ".png").c_str()),
          "save the transparency input capture");
    UnloadImage(capture);
    EndDrawing();
    frame(enemyPixel);
    run.findEnemy(target)->alive = false;
    frame(groundPixel);
    run.player.fireCooldown = 0;
    auto shots = run.stats.shots;
    frame(groundPixel, false, true);
    check(run.stats.shots == shots + 1 && distance(run.player.aim, groundPoint) < .15f,
          "right click aims at the floor behind scenery, not the model surface");
    frame(groundPixel);
    run.player.fireCooldown = 0;
    shots = run.stats.shots;
    frame(groundPixel, true, false, true);
    check(run.stats.shots == shots + 1 && distance(run.player.aim, groundPoint) < .15f &&
              distance(start, run.player.position) < .001f,
          "Shift-left click also aims through scenery without moving");
    frame(groundPixel);
    // A real low obstacle between muzzle and target remains solid, even though
    // the high camera ray sees over it and can still select the enemy.
    run.projectiles.clear();
    const auto blockedTarget = run.spawnMonster(monsterId(12), enemyPoint);
    run.findEnemy(blockedTarget)->cooldown = 1000;
    const auto midpoint = mul(add(player, enemyPoint), .5f);
    run.arena.walls.push_back(
        {{midpoint.x - .5f, 0, midpoint.z - .5f}, {midpoint.x + .5f, 1.2f, midpoint.z + .5f}});
    const float health = run.findEnemy(blockedTarget)->hp;
    for (int i = 0; i < 30; ++i)
        frame(enemyPixel, false, true);
    check(run.findEnemy(blockedTarget)->hp == health,
          "transparency picking never lets bullets pass through physical cover");
    // Gates obey the same aiming rule; their physical collision stays in place.
    const auto ray = GetScreenToWorldRay(enemyPixel, camera);
    const auto gate = add(ray.position, mul(ray.direction, distance(ray.position, enemyPoint) - 3));
    run.arena.walls.push_back({sub(gate, {.8f, .8f, .8f}), add(gate, {.8f, .8f, .8f})});
    frame(enemyPixel);
    check(game.hoveredEnemy == blockedTarget, "solid gates do not intercept enemy aiming");
    std::filesystem::remove_all(directory);
    std::cout << "PASS " << name << " selection, left/force fire, aim and solid collision\n";
}
} // namespace
int main(int argc, char **argv) {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(960, 640, "Player occlusion verification");
        check(IsWindowReady(), "graphics display required");
        if (argc < 2 || std::string(argv[1]) != "--pointer-only") {
            townCheck(HubKind::BlackCreek);
            townCheck(HubKind::Frontier);
            townCheck(HubKind::Redstone);
            canyonCheck();
            residentRenderCheck(MissionTheme::Mine);
            residentRenderCheck(MissionTheme::Canyon);
        }
        for (auto theme : {MissionTheme::Mine, MissionTheme::Canyon})
            for (float yaw : {0.f, 1.2f})
                for (bool transparent : {true, false})
                    sceneryInputCheck(theme, yaw, transparent);
        CloseWindow();
        std::cout << "PASS town/canyon transparency, enemy outlines, restoration, zoom and collision\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
