#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "render/TownActorModels.hpp"
#include "render/TownScene.hpp"
#include "render/WesternScene.hpp"
#include "world/HubWorld.hpp"
#include "rlgl.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace dw;
namespace {
void check(bool value, const char *message) {
    if (!value) throw std::runtime_error(message);
}
bool same(Image a, Image b) {
    return a.width == b.width && a.height == b.height && a.format == b.format &&
           std::memcmp(a.data, b.data, GetPixelDataSize(a.width, a.height, a.format)) == 0;
}
Image finish(PostProcess &post) {
    post.end();
    rlDrawRenderBatchActive();
    auto image = LoadImageFromScreen();
    const Color marker{23, 211, 91, 255};
    DrawRectangle(2, 2, 5, 5, marker);
    rlDrawRenderBatchActive();
    auto uiProbe = LoadImageFromScreen();
    EndDrawing();
    auto pixel = GetImageColor(uiProbe, 4, 4);
    UnloadImage(uiProbe);
    check(pixel.r == marker.r && pixel.g == marker.g && pixel.b == marker.b,
          "Every style leaves UI colors unchanged");
    return image;
}
void output(Image image, const std::string &name) {
    check(ExportImage(image, ("artifacts/cel-" + name + ".png").c_str()), "Write preview image");
}
std::string read(const char *path) {
    std::ifstream file(path);
    return {std::istreambuf_iterator<char>(file), {}};
}
void townViews() {
    TownScene scene;
    check(scene.load(TownScene::assetDirectory(HubKind::Redstone)), "Load Redstone");
    scene.document().write("artifacts/cel-before.scene");
    const auto count = scene.instanceCount();
    HubWorld hub;
    check(hub.load(TownScene::assetDirectory(HubKind::Redstone) / "town.nav"), "Load navigation");
    ObjectAnimationSystem motion;
    motion.reset(scene.document());
    motion.update(Tick, [&](Vector3 p) { return hub.height(p); });
    scene.applyAnimation(motion);
    scene.prepareFlags(1.5);
    PlayerModel player;
    player.update(hub.player, 0, &hub);
    TownCharacters residents;
    residents.reset(scene.document(), hub);
    TownActorModels actors;
    actors.prepare(residents);
    PostProcess post;
    auto capture = [&](Vector3 focus, Vector3 eye, VisualStyle style, bool ink = true) {
        Camera3D camera{eye, focus, {0,1,0}, 45, CAMERA_PERSPECTIVE};
        scene.setVisualStyle(style);
        scene.setPlayerOcclusion(camera, hub.player.position, false);
        scene.prepareLighting(camera, [&](Shader depth) {
            player.draw(hub.player, false, depth);
            actors.draw(residents, depth);
        });
        check(GetShaderLocation(scene.actorShader(), "visualStyle") >= 0, "Actors share cel lighting");
        BeginDrawing();
        post.begin({154,186,199,255}, distance(eye,focus), false, ink ? style : VisualStyle::Original);
        check(post.ready(), "Post shaders and framebuffers compile");
        BeginMode3D(camera);
        scene.draw(focus);
        player.draw(hub.player, false, scene.actorShader(), scene.shadowTexture());
        actors.draw(residents, scene.actorShader(), scene.shadowTexture());
        scene.drawEffects(camera);
        scene.draw(focus, true);
        EndMode3D();
        return finish(post);
    };
    const Vector3 focus{2,0,-5}, eye{27,29,22};
    auto before = capture(focus, eye, VisualStyle::Original);
    auto bands = capture(focus, eye, VisualStyle::Cel, false);
    auto after = capture(focus, eye, VisualStyle::Cel);
    auto restored = capture(focus, eye, VisualStyle::Original);
    check(!same(before,bands), "Lighting changes before post-processing");
    check(!same(bands,after), "The finishing pass adds ink and a crisp grade");
    check(same(before,restored), "Disabling cel shading restores identical baseline pixels");
    output(before,"before-fort"); output(after,"after-fort");
    std::vector<Image> presets;
    for (int index=2; index<int(VisualStyle::Count); ++index) {
        const auto style = VisualStyle(index);
        auto styled = capture(focus,eye,style);
        check(!same(styled,before) && !same(styled,after), "Each preset has its own treatment");
        for (auto previous : presets) check(!same(styled,previous), "All presets are pairwise distinct");
        presets.push_back(styled);
        output(styled,std::string(visualStyleSlug(style))+"-fort");
        auto original = capture(focus,eye,VisualStyle::Original);
        auto cel = capture(focus,eye,VisualStyle::Cel);
        check(same(original,before) && same(cel,after), "Other presets cannot leak into original or cel");
        UnloadImage(original); UnloadImage(cel);
    }
    for (auto image : presets) UnloadImage(image);
    for (auto image : {before,bands,after,restored}) UnloadImage(image);
    for (int index=0; index<int(VisualStyle::Count); ++index) {
        const auto style = VisualStyle(index);
        auto image = capture(hub.player.position, add(hub.player.position, {-5,5,-7}), style);
        output(image,style == VisualStyle::Original ? "before-player" : style == VisualStyle::Cel ? "after-player" : std::string(visualStyleSlug(style))+"-player"); UnloadImage(image);
    }
    scene.document().write("artifacts/cel-after.scene");
    check(scene.instanceCount() == count && read("artifacts/cel-before.scene") == read("artifacts/cel-after.scene"),
          "Cel shading does not alter the editable scene, materials, lights or routes");
    player.unload(); actors.unload(); scene.unload(); post.unload();
}
void canyonViews() {
    // Water ripples use wall-clock time, so exclude them from an exact-pixel
    // restoration comparison. The ordinary river still uses the shared lighting.
    Arena arena(1866, MissionTheme::Canyon, false);
    WesternScene scene;
    scene.prepare(arena);
    const auto focus = arena.rooms.front().center;
    const Camera3D camera{add(focus,{22,32,25}),focus,{0,1,0},45,CAMERA_PERSPECTIVE};
    scene.setPlayerOcclusion(camera, focus, false);
    PostProcess post;
    auto capture = [&](VisualStyle style, float storm = 0.f) {
        scene.setVisualStyle(style);
        scene.prepareLighting(camera);
        check(scene.lighting().ready(), "Canyon lighting and shadow shaders compile");
        check(GetShaderLocation(scene.lighting().actorShader(), "visualStyle") >= 0,
              "Generated missions share the stepped lighting");
        BeginDrawing();
        post.begin({154,186,199,255},distance(camera.position,focus),false,style);
        BeginMode3D(camera);
        post.sandstorm(storm, 4.f);
        scene.draw(focus); scene.drawGlass();
        EndMode3D();
        return finish(post);
    };
    auto before = capture(VisualStyle::Original), after = capture(VisualStyle::Cel), restored = capture(VisualStyle::Original);
    check(!same(before,after), "Cel shading affects generated terrain and props");
    check(same(before,restored), "Mission rendering restores the original after comparison");
    output(before,"before-canyon"); output(after,"after-canyon");
    for (int index=2; index<int(VisualStyle::Count); ++index) {
        const auto style = VisualStyle(index);
        auto styled = capture(style);
        check(!same(styled,before) && !same(styled,after), "Presets reach generated canyon terrain");
        output(styled,std::string(visualStyleSlug(style))+"-canyon");
        auto storm = capture(style, 1.f);
        auto repeated = capture(style);
        check(!same(styled,storm), "Every preset retains the sandstorm");
        check(same(styled,repeated), "Static styles remain stable and weather cannot leak");
        UnloadImage(storm); UnloadImage(repeated);
        auto original = capture(VisualStyle::Original);
        check(same(original,before), "Every mission preset restores the original exactly");
        UnloadImage(styled); UnloadImage(original);
    }
    for (auto image : {before,after,restored}) UnloadImage(image);
    scene.unload(); post.unload();
}
}
int main() {
    try {
        for (int index=0; index<int(VisualStyle::Count); ++index) {
            const auto style = VisualStyle(index);
            check(parseVisualStyle(visualStyleSlug(style)) == style, "Every preset parses by slug");
            check(int(nextVisualStyle(style)) == (index+1)%int(VisualStyle::Count), "Preset cycle wraps");
        }
        check(parseVisualStyle("okami") == VisualStyle::Sumi, "Okami alias selects Sumi-e frontier");
        check(!parseVisualStyle("missing"), "Unknown presets are rejected");
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_MSAA_4X_HINT);
        InitWindow(1440,1000,"Cel shading comparison");
        check(IsWindowReady(), "A graphics display is required");
        std::filesystem::create_directories("artifacts");
        townViews(); canyonViews();
        CloseWindow();
        std::cout << "PASS 16 visual presets, unchanged UI/scene, sandstorms, exact restoration and 48 comparison captures\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        if (IsWindowReady()) CloseWindow();
        return 1;
    }
}
