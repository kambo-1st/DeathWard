#include "raylib.h"
#include "raymath.h"
#include "render/TownScene.hpp"
#include "world/HubWorld.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
void lightingCheck(TownScene &scene, Vector3 focus) {
    const Camera3D camera{add(focus, {23, 30, 23}), focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    const auto render = [&](bool shadows) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        if (shadows)
            scene.prepareLighting(camera);
        BeginMode3D(camera);
        scene.draw(focus);
        scene.draw(focus, true);
        EndMode3D();
        auto image = LoadImageFromScreen();
        EndDrawing();
        return image;
    };
    check(scene.shadowsReady(), "sun and shadow framebuffer are available");
    auto unshadowed = render(false), shadowed = render(true);
    auto before = LoadImageColors(unshadowed), after = LoadImageColors(shadowed);
    auto cached = render(true);
    auto reused = LoadImageColors(cached);
    int darkened = 0, unchanged = 0, brighter = 0;
    int cacheDifferences = 0;
    for (int i = 0; i < unshadowed.width * unshadowed.height; ++i) {
        const int delta =
            int(before[i].r) + before[i].g + before[i].b - int(after[i].r) - after[i].g - after[i].b;
        darkened += delta > 30;
        unchanged += std::abs(delta) <= 3;
        brighter += delta < -9;
        cacheDifferences +=
            after[i].r != reused[i].r || after[i].g != reused[i].g || after[i].b != reused[i].b;
    }
    UnloadImageColors(before);
    UnloadImageColors(after);
    UnloadImageColors(reused);
    UnloadImage(unshadowed);
    UnloadImage(shadowed);
    UnloadImage(cached);
    check(cacheDifferences < 20, "cached static depth reproduces the original shadow pass");
    check(darkened > 1000 && unchanged > 20000 && brighter < 100,
          "sun occlusion darkens visible regions while retaining sunlit surfaces and original textures");
    const auto original = scene.document();
    auto withoutSun = original;
    std::erase_if(withoutSun.lights, [](const auto &light) { return light.type == 1; });
    scene.applyDocument(withoutSun);
    check(!scene.shadowsReady(), "editing away the sun disables its shadows");
    scene.applyDocument(original);
    check(scene.shadowsReady(), "restoring the scene restores its original sun");
}
void motionCheck(TownScene &scene, HubWorld &ground) {
    ObjectAnimationSystem motion;
    const auto document = scene.document();
    motion.reset(document);
    if (!motion.activeCount())
        return;
    size_t selected = 0;
    while (document.instances[selected].motion.kind != ObjectMotionKind::Tumbleweed)
        ++selected;
    const auto start =
        mul(add(motion.poses()[selected].bounds.min, motion.poses()[selected].bounds.max), .5f);
    const Camera3D camera{add(start, {4, 5, 4}), start, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    const auto render = [&] {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        scene.prepareLighting(camera);
        BeginMode3D(camera);
        scene.draw(start);
        scene.draw(start, true);
        EndMode3D();
        auto image = LoadImageFromScreen();
        EndDrawing();
        return image;
    };
    const auto before = render();
    for (int n = 0; n < 150; ++n)
        motion.update(Tick, [&](Vector3 p) { return ground.height(p); });
    scene.applyAnimation(motion);
    const auto &pose = motion.poses()[selected];
    const auto bounds = scene.instanceBounds(selected);
    check(distance(bounds.min, pose.bounds.min) < .0001f && distance(bounds.max, pose.bounds.max) < .0001f,
          "rendering and picking bounds follow the current animated pose");
    const auto &asset = document.assets[document.instances[selected].asset];
    const auto &mesh = scene.model().meshes[asset.first];
    bool picked = false;
    for (int t = 0; t < std::min(32, mesh.triangleCount) && !picked; ++t) {
        Vector3 triangle[3];
        for (int k = 0; k < 3; ++k) {
            const int v = mesh.indices ? mesh.indices[t * 3 + k] : t * 3 + k;
            triangle[k] = Vector3Transform(
                {mesh.vertices[v * 3], mesh.vertices[v * 3 + 1], mesh.vertices[v * 3 + 2]}, pose.transform);
        }
        const auto point = mul(add(add(triangle[0], triangle[1]), triangle[2]), 1.f / 3);
        const auto normal =
            unit(Vector3CrossProduct(sub(triangle[1], triangle[0]), sub(triangle[2], triangle[0])));
        picked = scene.pick({add(point, mul(normal, .15f)), mul(normal, -1)}) == selected;
    }
    check(picked, "mesh picking hits the tumbleweed at its animated location");
    auto cached = render();
    scene.applyDocument(document); // Force a full static shadow rebuild at the same animated pose.
    scene.applyAnimation(motion);
    auto rebuilt = render();
    auto rest = LoadImageColors(before), a = LoadImageColors(cached), b = LoadImageColors(rebuilt);
    int differences = 0, changed = 0;
    for (int n = 0; n < cached.width * cached.height; ++n) {
        differences += a[n].r != b[n].r || a[n].g != b[n].g || a[n].b != b[n].b;
        changed += std::abs(int(rest[n].r) - int(a[n].r)) + std::abs(int(rest[n].g) - int(a[n].g)) +
                       std::abs(int(rest[n].b) - int(a[n].b)) >
                   20;
    }
    check(differences < 20, "moving objects cast current shadows without stale cached silhouettes");
    check(changed > 40, "the animated textured tumbleweed visibly changes position");
    std::filesystem::create_directories("artifacts");
    ExportImage(before, "artifacts/town-tumbleweed-before.png");
    ExportImage(cached, "artifacts/town-tumbleweed-after.png");
    UnloadImageColors(rest);
    UnloadImageColors(a);
    UnloadImageColors(b);
    UnloadImage(before);
    UnloadImage(cached);
    UnloadImage(rebuilt);
    scene.applyDocument(document);
}
void trainCheck(TownScene &scene) {
    const auto document = scene.document();
    if (document.groups.empty())
        return;
    ObjectAnimationSystem motion;
    motion.reset(document);
    const size_t body = 48;
    check(document.instances[body].id == "60904987:1235095919362174", "locomotive capture fixture");
    const auto capture = [&](const char *name, bool wide) {
        const auto pose = motion.poses()[body].transform;
        const Vector3 front = unit(Vector3{pose.m8, 0, pose.m10});
        auto focus = Vector3{pose.m12, pose.m13 + 2, pose.m14};
        if (wide)
            focus = sub(focus, mul(front, 15));
        Camera3D camera{add(focus, wide ? Vector3{32, 40, 32} : Vector3{5, 8, 18}),
                        focus,
                        {0, 1, 0},
                        45,
                        CAMERA_PERSPECTIVE};
        const auto render = [&] {
            scene.applyAnimation(motion);
            BeginDrawing();
            ClearBackground(SKYBLUE);
            scene.prepareLighting(camera);
            BeginMode3D(camera);
            scene.draw(focus);
            scene.draw(focus, true);
            EndMode3D();
            auto image = LoadImageFromScreen();
            EndDrawing();
            return image;
        };
        auto cached = render();
        scene.applyDocument(document);
        auto rebuilt = render();
        auto a = LoadImageColors(cached), b = LoadImageColors(rebuilt);
        int differences = 0;
        for (int n = 0; n < cached.width * cached.height; ++n)
            differences += a[n].r != b[n].r || a[n].g != b[n].g || a[n].b != b[n].b;
        check(differences < 20, "train shadows match a fresh shadow bake, with no stationary ghost");
        ExportImage(cached, name);
        UnloadImageColors(a);
        UnloadImageColors(b);
        UnloadImage(cached);
        UnloadImage(rebuilt);
        const auto bounds = scene.instanceBounds(body);
        check(distance(bounds.min, motion.poses()[body].bounds.min) < .001f,
              "train bounds follow the vehicle");
    };
    capture("artifacts/train-station.png", true);
    capture("artifacts/train-locomotive.png", false);
    for (int n = 0; n < 27 * 60; ++n)
        motion.update(Tick, {});
    capture("artifacts/train-curve.png", true);
    capture("artifacts/train-wheel-motion.png", false);
    for (int n = 0; n < 70 * 60; ++n)
        motion.update(Tick, {});
    capture("artifacts/train-far-curve.png", true);
    scene.applyDocument(document);
}
int main() {
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(800, 600, "Original town verification");
        check(IsWindowReady(), "graphics display required");
        for (auto hub : {HubKind::BlackCreek, HubKind::Frontier}) {
            const bool frontier = hub == HubKind::Frontier;
            const auto pack = std::filesystem::path(GetApplicationDirectory()) / "assets" / hubFolder(hub);
            TownScene scene;
            HubWorld town;
            auto original = std::filesystem::current_path();
            std::filesystem::current_path(std::filesystem::temp_directory_path());
            check(scene.load(pack), "packaged original scene loads outside repository");
            check(town.load(pack / "town.nav"), "packaged town navigation loads");
            std::filesystem::current_path(original);
            check(scene.instanceCount() == (frontier ? 2216 : 1516),
                  "all active mesh placements from the original scene are present");
            check(scene.model().meshCount == (frontier ? 346 : 398),
                  "original scene library contains every material variant and submesh");
            std::set<unsigned> textures;
            bool glass = false;
            for (int i = 1; i < scene.model().materialCount; ++i) {
                const auto &m = scene.model().materials[i].maps[MATERIAL_MAP_ALBEDO];
                if (m.texture.width > 1)
                    textures.insert(m.texture.id);
                glass |= m.color.a < 255;
            }
            check(textures.size() >= (frontier ? 5 : 12) && glass,
                  "original atlases, signs, sky and transparent materials are loaded");
            lightingCheck(scene, town.spawn);
            motionCheck(scene, town);
            trainCheck(scene);
            for (Vector3 p : std::array<Vector3, 3>{{town.spawn, town.mission, {-1, 2, -65}}}) {
                BeginDrawing();
                ClearBackground(SKYBLUE);
                const Camera3D camera{add(p, {23, 30, 23}), p, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
                scene.prepareLighting(camera);
                BeginMode3D(camera);
                scene.draw(p);
                scene.draw(p, true);
                EndMode3D();
                EndDrawing();
            }
            check(!scene.load(pack / "missing"), "missing source pack fails safely");
            check(scene.load(pack), "town resource reload succeeds");
            scene.unload();
            scene.unload();
        }
        CloseWindow();
        std::cout << "PASS both original hub scenes, exact placements and mesh sections, textures, glass, "
                     "sun shadows, lighting edits, rendering "
                     "and resource cleanup\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
