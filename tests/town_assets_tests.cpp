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
