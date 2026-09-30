#include "render/TownScene.hpp"
#include "render/PostProcess.hpp"
#include "render/PlayerModel.hpp"
#include "world/HubWorld.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_MSAA_4X_HINT);
        InitWindow(1440, 1000, "Redstone Canyon verification");
        TownScene scene;
        if (!scene.load(TownScene::assetDirectory(HubKind::Redstone)))
            throw std::runtime_error("Redstone meshes and materials must load");
        std::set<unsigned> textures;
        for (int n = 0; n < scene.model().materialCount; ++n) {
            const auto texture = scene.model().materials[n].maps[MATERIAL_MAP_ALBEDO].texture;
            if (texture.width > 1) textures.insert(texture.id);
        }
        if (textures.size() < 8 || !scene.shadowsReady())
            throw std::runtime_error("All eight original textures and the canyon sunlight must load");
        HubWorld hub;
        if (!hub.load(TownScene::assetDirectory(HubKind::Redstone) / "town.nav"))
            throw std::runtime_error(hub.error);
        ObjectAnimationSystem motion;
        motion.reset(scene.document());
        for (int n = 0; n < 90; ++n) motion.update(Tick, [&](Vector3 p) { return hub.height(p); });
        scene.applyAnimation(motion);
        PostProcess post;
        PlayerModel player;
        player.update(hub.player, 0, &hub);
        const auto capture = [&](const char *name, Vector3 focus, Vector3 eye) {
            Camera3D camera{eye, focus, {0,1,0}, 45, CAMERA_PERSPECTIVE};
            scene.setPlayerOcclusion(camera, hub.player.position, false);
            scene.prepareLighting(camera, [&](Shader depth) { player.draw(hub.player, false, depth); });
            BeginDrawing();
            post.begin({154,186,199,255}, distance(eye,focus));
            BeginMode3D(camera);
            scene.draw(focus);
            player.draw(hub.player, false, scene.actorShader(), scene.shadowTexture());
            scene.drawEffects(camera);
            scene.drawOccluders();
            scene.draw(focus, true);
            EndMode3D();
            post.end();
            auto picture = LoadImageFromScreen();
            ExportImage(picture, name);
            UnloadImage(picture);
            EndDrawing();
        };
        capture("artifacts/redstone-overview.png", {0,0,8}, {110,155,-135});
        capture("artifacts/redstone-fort.png", {3,1,-26}, {44,48,-80});
        capture("artifacts/redstone-camp.png", {-23,1,-51}, {-3,28,-79});
        capture("artifacts/redstone-train.png", {-3,1,18}, {27,28,-12});
        if (!scene.effects().loaded() || scene.effects().particleCount() == 0)
            throw std::runtime_error("Imported campfires and locomotive steam must render");
        scene.unload();
        player.unload();
        post.unload();
        CloseWindow();
        std::cout << "PASS Redstone original textures, shadows, campfires, steam and rendered settlement views\n";
    } catch (const std::exception &e) { std::cerr << "FAIL " << e.what() << '\n'; return 1; }
}
