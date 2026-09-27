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
int main() {
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(800, 600, "Original town verification");
        check(IsWindowReady(), "graphics display required");
        {
            TownScene scene;
            HubWorld town;
            auto original = std::filesystem::current_path();
            std::filesystem::current_path(std::filesystem::temp_directory_path());
            check(scene.load(), "packaged original scene loads outside repository");
            check(town.load(TownScene::assetDirectory() / "town.nav"), "packaged town navigation loads");
            std::filesystem::current_path(original);
            check(scene.instanceCount() == 1516,
                  "all active mesh placements from the original scene are present");
            check(scene.model().meshCount == 398,
                  "original scene library contains every material variant and submesh");
            std::set<unsigned> textures;
            bool glass = false;
            for (int i = 1; i < scene.model().materialCount; ++i) {
                const auto &m = scene.model().materials[i].maps[MATERIAL_MAP_ALBEDO];
                if (m.texture.width > 1)
                    textures.insert(m.texture.id);
                glass |= m.color.a < 255;
            }
            check(textures.size() >= 12 && glass,
                  "original atlases, signs, sky and transparent materials are loaded");
            for (Vector3 p : std::array<Vector3, 3>{{town.spawn, town.mission, {-1, 2, -65}}}) {
                BeginDrawing();
                ClearBackground(SKYBLUE);
                BeginMode3D({add(p, {23, 30, 23}), p, {0, 1, 0}, 45, CAMERA_PERSPECTIVE});
                scene.draw(p);
                scene.draw(p, true);
                EndMode3D();
                EndDrawing();
            }
            check(!scene.load(TownScene::assetDirectory() / "missing"), "missing source pack fails safely");
            check(scene.load(), "town resource reload succeeds");
            scene.unload();
            scene.unload();
        }
        CloseWindow();
        std::cout << "PASS original town's 1516 placements, 398 mesh sections, textures, glass, rendering "
                     "and resource cleanup\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
