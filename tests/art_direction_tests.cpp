#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "render/TownActorModels.hpp"
#include "render/TownScene.hpp"
#include "world/HubWorld.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_MSAA_4X_HINT);
        InitWindow(1440, 1000, "Redstone art direction A/B");
        TownScene scene;
        if (!scene.load(TownScene::assetDirectory(HubKind::Redstone)))
            throw std::runtime_error("load Redstone");
        const auto original = scene.document();
        const auto instances = scene.instanceCount();
        HubWorld hub;
        if (!hub.load(TownScene::assetDirectory(HubKind::Redstone) / "town.nav"))
            throw std::runtime_error(hub.error);
        ObjectAnimationSystem motion;
        motion.reset(scene.document());
        for (int i = 0; i < 90; ++i)
            motion.update(Tick, [&](Vector3 p) { return hub.height(p); });
        scene.applyAnimation(motion);
        PostProcess post;
        PlayerModel player;
        TownCharacters residents;
        residents.reset(scene.document(), hub);
        TownActorModels actors;
        actors.prepare(residents);
        player.update(hub.player, 0, &hub);
        const auto capture = [&](const std::string &name, Vector3 focus, Vector3 eye, bool poc) {
            scene.setArtPoc(poc);
            player.artPoc = actors.artPoc = poc;
            if (scene.artPoc() != poc)
                throw std::runtime_error("profile toggle");
            Camera3D camera{eye, focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
            scene.setPlayerOcclusion(camera, hub.player.position, false);
            scene.prepareLighting(camera, [&](Shader depth) {
                player.draw(hub.player, false, depth);
                actors.draw(residents, depth);
            });
            BeginDrawing();
            post.begin({154, 186, 199, 255}, distance(eye, focus), scene.artPoc());
            BeginMode3D(camera);
            scene.draw(focus);
            player.draw(hub.player, false, scene.actorShader(), scene.shadowTexture());
            actors.draw(residents, scene.actorShader(), scene.shadowTexture());
            scene.drawEffects(camera);
            scene.draw(focus, true);
            EndMode3D();
            post.end();
            auto image = LoadImageFromScreen();
            ExportImage(image, ("artifacts/art-poc-" + name + ".png").c_str());
            EndDrawing();
            return image;
        };
        auto before = capture("before-frontage", {2, 0, -5}, {27, 29, 22}, false);
        auto after = capture("after-frontage", {2, 0, -5}, {27, 29, 22}, true);
        auto restored = capture("restored-frontage", {2, 0, -5}, {27, 29, 22}, false);
        if (std::memcmp(before.data, restored.data, size_t(before.width) * before.height * 4) != 0)
            throw std::runtime_error("Disabling POC must restore identical baseline pixels");
        if (std::memcmp(before.data, after.data, size_t(before.width) * before.height * 4) == 0)
            throw std::runtime_error("POC must visibly change the render");
        for (auto i : {before, after, restored})
            UnloadImage(i);
        for (bool poc : {false, true}) {
            const auto prefix = poc ? "after-" : "before-";
            UnloadImage(capture(std::string(prefix) + "fort", {3, 1, -26}, {44, 48, -80}, poc));
            UnloadImage(capture(std::string(prefix) + "camp", {-23, 1, -51}, {-3, 28, -79}, poc));
            UnloadImage(capture(std::string(prefix) + "close", {12, 0, -6}, {23, 15, 8}, poc));
            UnloadImage(capture(std::string(prefix) + "player", hub.player.position,
                                add(hub.player.position, {-5, 5, -7}), poc));
        }
        hub.player.position = {2, hub.height({2, 0, -3}) + .85f, -3};
        hub.player.facing = {0, 0, 1};
        hub.player.velocity = {0, 0, 2};
        for (int i = 0; i < 60; ++i)
            player.update(hub.player, (i + 1) * Tick, &hub);
        UnloadImage(
            capture("after-player-walking", hub.player.position, add(hub.player.position, {4, 4, 6}), true));
        UnloadImage(capture("after-wife", {-28, .9f, -21}, {-24, 5, -15}, true));
        UnloadImage(capture("after-scout", {33, .9f, -25}, {39, 6, -21}, true));
        if (scene.instanceCount() != instances)
            throw std::runtime_error("POC must not change editable instance count");
        original.write("artifacts/art-poc-document-before.scene");
        scene.document().write("artifacts/art-poc-document-after.scene");
        const auto read = [](const char *path) {
            std::ifstream f(path);
            return std::string(std::istreambuf_iterator<char>(f), {});
        };
        if (read("artifacts/art-poc-document-before.scene") != read("artifacts/art-poc-document-after.scene"))
            throw std::runtime_error("POC must not change document, lights, animations or shadow overrides");
        scene.load(TownScene::assetDirectory(HubKind::BlackCreek));
        scene.setArtPoc(true);
        if (scene.artPoc())
            throw std::runtime_error("POC must be limited to Redstone");
        scene.unload();
        player.unload();
        actors.unload();
        post.unload();
        CloseWindow();
        std::cout << "PASS reversible Redstone A/B, identical original pixels, unchanged document, other "
                     "hubs excluded\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
