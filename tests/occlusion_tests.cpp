#include "raylib.h"
#include "raymath.h"
#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "render/Renderer.hpp"
#include "render/TownScene.hpp"
#include "render/WesternScene.hpp"
#include "rlgl.h"
#include "world/HubWorld.hpp"
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
} // namespace
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(960, 640, "Player occlusion verification");
        check(IsWindowReady(), "graphics display required");
        townCheck(HubKind::BlackCreek);
        townCheck(HubKind::Frontier);
        canyonCheck();
        CloseWindow();
        std::cout << "PASS town/canyon transparency, enemy outlines, restoration, zoom and collision\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
