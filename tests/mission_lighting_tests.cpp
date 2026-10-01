#include "raylib.h"
#include "raymath.h"
#include "render/MissionLighting.hpp"
#include "render/WesternScene.hpp"
#include "rlgl.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
int brightness(Color c) {
    return int(c.r) + c.g + c.b;
}
int sample(Image image, Camera3D camera, Vector3 p) {
    const auto at = GetWorldToScreen(p, camera);
    check(at.x >= 1 && at.y >= 1 && at.x < image.width - 1 && at.y < image.height - 1,
          "sample inside viewport");
    return brightness(GetImageColor(image, int(at.x), int(at.y)));
}
template <class Draw> Image capture(Camera3D camera, Draw draw) {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    draw();
    EndMode3D();
    rlDrawRenderBatchActive();
    auto result = LoadImageFromScreen();
    EndDrawing();
    return result;
}
void verifyDepth() {
    MissionLighting light;
    auto cube = GenMeshCube(2, 4, 2), plane = GenMeshPlane(40, 40, 1, 1);
    auto material = LoadMaterialDefault();
    Camera3D camera{{0, 40, .01f}, {0, 0, 0}, {0, 0, -1}, 32, CAMERA_ORTHOGRAPHIC};
    int builds = 0;
    auto scenery = [&](Shader, Shader depth) {
        ++builds;
        auto m = material;
        m.shader = depth;
        DrawMesh(cube, m, MatrixTranslate(0, 2, 0));
    };
    light.prepare(camera, scenery);
    check(light.ready(), "mission depth buffers and shaders initialize");
    auto render = [&](bool mesh, bool flush = false) {
        return capture(camera, [&] {
            if (mesh) {
                auto m = material;
                m.shader = light.actorShader();
                light.draw(plane, m, MatrixIdentity());
            } else {
                light.beginPrimitives();
                if (flush)
                    for (int i = 0; i < 4000; ++i)
                        DrawCube({200, 0, 200}, 1, 1, 1, WHITE);
                DrawPlane({0, 0, 0}, {40, 40}, WHITE);
                light.endPrimitives();
            }
        });
    };
    const Vector3 shade{1.8f, 0, -1.3f}, sunlit{-4, 0, 3}, moving{8.8f, 0, -1.3f};
    auto baseline = render(false), mesh = render(true), flushed = render(false, true);
    const int lit = sample(baseline, camera, sunlit), dark = sample(baseline, camera, shade);
    check(dark < lit * .75f, "a mesh casts a directional shadow on a primitive ground receiver");
    check(std::abs(sample(mesh, camera, shade) - dark) < 6, "mesh and primitive receivers agree");
    check(std::abs(sample(flushed, camera, shade) - dark) < 6,
          "shadow sampling survives automatic rlgl batch flushes");
    light.prepare(camera, scenery, [&](Shader, Shader depth) {
        BeginShaderMode(depth);
        DrawCube({7, 2, 0}, 2, 4, 2, WHITE);
        EndShaderMode();
    });
    auto dynamic = render(false);
    check(builds == 1, "animated casters reuse static scenery depth");
    check(sample(dynamic, camera, moving) < lit * .75f, "primitive actor casts into the shared depth field");
    check(sample(dynamic, camera, shade) == dark, "dynamic depth retains static cliff shadows");
    light.prepare(camera, scenery);
    auto cleared = render(false);
    check(sample(cleared, camera, moving) > lit * .97f, "departed actors leave no stale shadow");
    light.invalidate();
    light.prepare(camera, scenery);
    check(builds == 2, "new scenery invalidates the static cache");
    camera.target.x = 40;
    camera.position.x = 40;
    light.prepare(camera, scenery);
    check(builds == 3, "moving to another room rebuilds shadow coverage");
    for (auto image : {baseline, mesh, flushed, dynamic, cleared})
        UnloadImage(image);
    UnloadMesh(cube);
    UnloadMesh(plane);
    UnloadMaterial(material);
    std::cout << "PASS shared mesh/primitive lighting, batch flush, animated depth, cache invalidation\n";
}
void verifyMine() {
    WesternScene scene;
    Arena arena(1866, MissionTheme::Mine);
    scene.prepare(arena);
    const auto focus = arena.rooms[2].center;
    Camera3D camera{add(focus, {0, 70, .01f}), focus, {0, 0, -1}, 65, CAMERA_ORTHOGRAPHIC};
    scene.setPlayerOcclusion(camera, focus, false);
    auto render = [&] {
        return capture(camera, [&] {
            scene.draw(focus);
            scene.drawGlass();
        });
    };
    auto before = render();
    scene.prepareLighting(camera);
    auto after = render();
    ExportImage(after, "artifacts/mission-shadow-mine-overhead.png");
    int samples = 0, matched = 0;
    for (float z = focus.z - 27; z < focus.z + 27; z += .55f)
        for (float x = focus.x - 27; x < focus.x + 27; x += .55f) {
            const Vector3 p{x, .10f, z};
            if (std::none_of(arena.floors.begin(), arena.floors.end(), [&](Box box) {
                    return x > box.min.x + .2f && x < box.max.x - .2f && z > box.min.z + .2f &&
                           z < box.max.z - .2f;
                }))
                continue;
            if (scene.pick({p, {0, 1, 0}}, focus).hit)
                continue;
            if (!scene.pick({p, MissionLighting::sun()}, focus).hit)
                continue;
            ++samples;
            matched += sample(before, camera, p) - sample(after, camera, p) > 30;
        }
    std::cout << "Mine: static prop shadow rays " << matched << "/" << samples << '\n';
    check(samples > 20 && matched > samples * .75f, "instanced mine props cast onto imported floor meshes");
    UnloadImage(before);
    UnloadImage(after);
}
void verifyCanyon() {
    WesternScene scene;
    for (uint64_t seed : {1866ULL, 69175541ULL}) {
        Arena arena(seed, MissionTheme::Canyon);
        scene.prepare(arena);
        const auto focus = arena.rooms[2].center;
        Camera3D camera{add(focus, {0, 70, .01f}), focus, {0, 0, -1}, 65, CAMERA_ORTHOGRAPHIC};
        scene.setPlayerOcclusion(camera, focus, false);
        auto render = [&] {
            return capture(camera, [&] {
                scene.draw(focus);
                scene.drawOccluders();
                scene.drawGlass();
            });
        };
        auto unlit = render();
        scene.prepareLighting(camera);
        check(scene.lighting().ready(), "generated canyon shadow map is ready");
        auto shaded = render();
        ExportImage(shaded, ("artifacts/mission-shadow-terrain-" + std::to_string(seed) + ".png").c_str());
        int shadowSamples = 0, matched = 0, open = 0, openMatched = 0;
        const auto &field = *arena.canyon;
        for (float z = focus.z - 27; z < focus.z + 27; z += .8f)
            for (float x = focus.x - 27; x < focus.x + 27; x += .8f) {
                const Vector3 p{x, .12f, z};
                if (field.height(x, z) > .001f)
                    continue;
                const int before = sample(unlit, camera, p), after = sample(shaded, camera, p);
                if (field.trace(p, add(p, mul(MissionLighting::sun(), 70))).hit) {
                    ++shadowSamples;
                    matched += before - after > 45;
                } else {
                    ++open;
                    openMatched += std::abs(before - after) < 15;
                }
            }
        std::cout << "Canyon " << seed << ": shadow rays " << matched << "/" << shadowSamples << ", open sky "
                  << openMatched << "/" << open << '\n';
        check(shadowSamples > 20 && matched > shadowSamples * .8f,
              "actual canyon walls shadow the floor where sun rays hit terrain");
        check(open > 20 && openMatched > open * .85f,
              "open canyon ground remains sunlit without self-shadow acne");
        // Camera fading must leave the physical depth field intact. Compare the
        // same ground receiver with a camera that fades the canyon wall.
        auto ground = [&] {
            return capture(camera, [&] {
                scene.lighting().beginPrimitives();
                DrawPlane(focus, {65, 65}, WHITE);
                scene.lighting().endPrimitives();
            });
        };
        auto beforeFade = ground();
        Camera3D oblique{add(focus, {24, 30, 24}), focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
        scene.setPlayerOcclusion(oblique, add(focus, {0, .85f, 0}));
        auto faded = render();
        UnloadImage(faded);
        scene.prepareLighting(camera);
        auto afterFade = ground();
        int changed = 0;
        for (int y = 0; y < beforeFade.height; ++y)
            for (int x = 0; x < beforeFade.width; ++x)
                changed +=
                    brightness(GetImageColor(beforeFade, x, y)) != brightness(GetImageColor(afterFade, x, y));
        check(changed == 0, "camera transparency never removes physical canyon shadows");
        for (auto image : {unlit, shaded, beforeFade, afterFade})
            UnloadImage(image);
        Arena mine(seed, MissionTheme::Mine);
        scene.prepare(mine);
        check(!scene.lighting().ready(), "changing themes invalidates the old shadow field");
        scene.prepareLighting(camera);
        check(scene.lighting().ready(), "mine scenery casts into its own refreshed shadow field");
    }
    scene.unload();
    check(!scene.lighting().ready(), "scene unload releases shadow resources");
    check(scene.load(), "scene reload succeeds after releasing borrowed depth textures");
    std::cout << "PASS generated terrain sun rays, camera fading, theme switching and resource reload\n";
}
void verifyGroundDetail() {
    for (auto theme : {MissionTheme::Mine, MissionTheme::Canyon}) {
        WesternScene scene;
        // Keep this exact restoration check independent of animated water.
        Arena arena(1866, theme, false);
        scene.prepare(arena);
        const auto focus = arena.rooms[2].center;
        Camera3D camera{add(focus, {0, 70, .01f}), focus, {0, 0, -1}, 45, CAMERA_ORTHOGRAPHIC};
        scene.setPlayerOcclusion(camera, focus, false);
        scene.prepareLighting(camera);
        auto render = [&] {
            return capture(camera, [&] {
                scene.draw(focus);
                scene.drawGlass();
            });
        };
        scene.setGroundDetail(false);
        auto flat = render();
        scene.setGroundDetail(true);
        auto detailed = render();
        scene.setGroundDetail(false);
        auto restored = render();
        int changed = 0;
        for (int y = 0; y < flat.height; ++y)
            for (int x = 0; x < flat.width; ++x) {
                const auto before = GetImageColor(flat, x, y), after = GetImageColor(detailed, x, y);
                const auto original = GetImageColor(restored, x, y);
                check(before.r == original.r && before.g == original.g && before.b == original.b &&
                          before.a == original.a,
                      "disabling floor detail exactly restores the original render");
                changed += std::abs(int(before.r) - after.r) + std::abs(int(before.g) - after.g) +
                               std::abs(int(before.b) - after.b) >
                           6;
            }
        check(changed > flat.width * flat.height / 15,
              "ground detail visibly breaks up the flat floor in both mission themes");
        const std::string name = theme == MissionTheme::Canyon ? "canyon" : "mine";
        ExportImage(flat, ("artifacts/ground-surface-flat-" + name + ".png").c_str());
        ExportImage(detailed, ("artifacts/ground-surface-detail-" + name + ".png").c_str());
        for (auto image : {flat, detailed, restored})
            UnloadImage(image);
        std::cout << "PASS " << name << " floor variation and exact toggle restoration (" << changed
                  << " pixels)\n";
    }
}
void verifyRoadSurface() {
    Arena arena(1866, MissionTheme::Canyon, false);
    check(!arena.canyon->road.empty(), "road surface fixture exists");
    Arena plain = arena;
    plain.canyon = std::make_shared<CanyonTerrain>(*arena.canyon);
    plain.canyon->road.clear();
    WesternScene scene;
    const auto focus = arena.rooms[size_t(arena.canyon->roadRooms[1])].center;
    Camera3D camera{add(focus, {0, 70, .01f}), focus, {0, 0, -1}, 45, CAMERA_ORTHOGRAPHIC};
    auto render = [&](const Arena &world) {
        scene.prepare(world);
        scene.setGroundDetail(false);
        scene.setPlayerOcclusion(camera, focus, false);
        scene.prepareLighting(camera);
        return capture(camera, [&] { scene.draw(focus); scene.drawGlass(); });
    };
    auto before = render(plain), after = render(arena);
    int count = 0, visible = 0;
    for (const auto &point : arena.canyon->road) {
        if (distance(point.position, focus) > 11 || point.along < 5 ||
            arena.canyon->road.back().along - point.along < 5)
            continue;
        ++count;
        visible += sample(before, camera, point.position) - sample(after, camera, point.position) > 15;
    }
    std::cout << "Road surface: " << visible << '/' << count << " visibly worn samples\n";
    check(count > 30 && visible > count * .75f,
          "roads are visibly shaded on terrain even when optional ground detail is disabled");
    ExportImage(before, "artifacts/road-surface-before.png");
    ExportImage(after, "artifacts/road-surface-after.png");
    UnloadImage(before); UnloadImage(after);
}
} // namespace
int main() {
    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(640, 640, "Mission lighting verification");
    std::filesystem::create_directories("artifacts");
    int result = 0;
    try {
        verifyDepth();
        verifyMine();
        verifyCanyon();
        verifyGroundDetail();
        verifyRoadSurface();
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        result = 1;
    }
    CloseWindow();
    return result;
}
