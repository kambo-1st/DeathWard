#include "editor/TownEditor.hpp"
#include "raymath.h"
#include "world/HubWorld.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool condition, const std::string &message) {
    if (!condition)
        throw std::runtime_error(message);
}
bool same(Matrix a, Matrix b) {
    auto x = MatrixToFloatV(a), y = MatrixToFloatV(b);
    for (int i = 0; i < 16; ++i)
        if (x.v[i] != y.v[i])
            return false;
    return true;
}
std::string bytes(const std::filesystem::path &path) {
    std::ifstream in(path, std::ios::binary);
    return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}
void navigationChecks() {
    // A floor and a movable block: deleting/moving geometry must free its former footprint.
    auto floor = GenMeshPlane(20, 20, 1, 1), cube = GenMeshCube(3, 4, 3);
    Mesh meshes[]{floor, cube};
    Model model{};
    model.meshCount = 2;
    model.meshes = meshes;
    TownDocument doc;
    doc.assets = {{"floor", "Floor", 0, 1, 0, {{-10, 0, -10}, {10, 0, 10}}},
                  {"block", "Block", 1, 1, 0, {{-1.5f, -2, -1.5f}, {1.5f, 2, 1.5f}}}};
    doc.instances = {{0, MatrixIdentity()}, {1, MatrixTranslate(0, 2, 0)}};
    TownNavigation nav;
    nav.width = nav.depth = 50;
    nav.minX = nav.minZ = -10;
    nav.cell = .4f;
    nav.spawn = {-6, 0, -6};
    nav.mission = {6, 0, 6};
    nav.bake(doc, model);
    const size_t middle = 25 * 50 + 25;
    check(!std::isfinite(nav.heights[middle]), "navigation blocks disconnected object roofs");
    doc.instances[1].motion.kind = ObjectMotionKind::Spin;
    nav.bake(doc, model);
    check(std::isfinite(nav.heights[middle]), "animated decoration is excluded from static navigation");
    doc.instances[1].motion.kind = ObjectMotionKind::None;
    doc.instances[1].transform.m12 = 5;
    nav.bake(doc, model);
    check(std::isfinite(nav.heights[middle]), "moving an object frees its previous footprint");
    const size_t moved = 25 * 50 + 37;
    check(!std::isfinite(nav.heights[moved]), "navigation blocks the moved object's new footprint");
    doc.instances.pop_back();
    nav.bake(doc, model);
    check(std::isfinite(nav.heights[moved]), "deleting an object reopens its terrain");
    UnloadMesh(floor);
    UnloadMesh(cube);
}
} // namespace
int main() {
    const auto directory =
        std::filesystem::temp_directory_path() /
        ("deathward-editor-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(1440, 900, "Town editor verification");
        check(IsWindowReady(), "graphics display required");
        SetTargetFPS(0);
        SetExitKey(KEY_NULL);
        navigationChecks();
        std::filesystem::create_directories(directory);
        const auto source = TownScene::assetDirectory();
        for (const auto *name : {"town.scene", "town.nav", "town.glb", "town.labels"})
            std::filesystem::copy_file(source / name, directory / name);
        TownDocument original;
        std::string error;
        check(original.load(directory / "town.scene", error), error);
        original.write(directory / "roundtrip.scene");
        TownDocument roundtrip;
        check(roundtrip.load(directory / "roundtrip.scene", error), error);
        check(original.instances.size() == roundtrip.instances.size() &&
                  original.lights.size() == roundtrip.lights.size(),
              "scene round trip preserves instances and lights");
        for (size_t i = 0; i < original.instances.size(); ++i)
            check(same(original.instances[i].transform, roundtrip.instances[i].transform),
                  "scene round trip preserves exact affine transforms including reflections and shear");
        {
            std::ofstream broken(directory / "bad.scene");
            broken << "DEATHWARD_TOWN 1\ninstance 999 nan\n";
        }
        check(!roundtrip.load(directory / "bad.scene", error) &&
                  roundtrip.instances.size() == original.instances.size(),
              "invalid reloads retain the existing document");
        TownNavigation nav;
        nav.load(directory / "town.nav");
        TownEditor editor;
        check(editor.open(directory,
                          {add(nav.spawn, {23, 30, 23}), nav.spawn, {0, 1, 0}, 45, CAMERA_PERSPECTIVE}),
              editor.status);
        auto event = [](unsigned type, int a, int b = 0) { PlayAutomationEvent({0, type, {a, b, 0, 0}}); };
        auto frame = [&](Vector2 pixel = Vector2{700, 450}, bool left = false, bool middle = false,
                         bool right = false) {
            event(7, int(pixel.x), int(pixel.y));
            event(left ? 6 : 5, MOUSE_BUTTON_LEFT);
            event(middle ? 6 : 5, MOUSE_BUTTON_MIDDLE);
            event(right ? 6 : 5, MOUSE_BUTTON_RIGHT);
            editor.update(Tick);
            BeginDrawing();
            editor.draw();
            EndDrawing();
        };
        auto click = [&](Vector2 pixel) {
            frame(pixel);
            frame(pixel, true);
            frame(pixel);
        };
        size_t chosen = 0;
        float best = 1e9f;
        for (size_t i = 0; i < original.instances.size(); ++i) {
            const auto &a = original.assets[original.instances[i].asset];
            if (a.label.find("Barrel") == std::string::npos)
                continue;
            auto b = original.bounds(i);
            auto p = mul(add(b.min, b.max), .5f);
            const float d = distance(p, nav.spawn);
            if (d < best) {
                best = d;
                chosen = i;
            }
        }
        editor.select(chosen);
        editor.focusSelection();
        frame();
        auto b = editor.document().bounds(chosen);
        click(GetWorldToScreen(mul(add(b.min, b.max), .5f), editor.camera));
        check(editor.selection().has_value(), "clicking real scene geometry selects an object");
        editor.select(chosen);
        editor.focusSelection();
        frame();
        const auto initial = editor.document().instances[chosen].transform;
        const auto pos = Vector3{initial.m12, initial.m13, initial.m14};
        const float handle = distance(editor.camera.position, editor.camera.target) * .12f;
        auto a = GetWorldToScreen(add(pos, {handle * .8f, 0, 0}), editor.camera);
        auto z = GetWorldToScreen(add(pos, {handle * 1.3f, 0, 0}), editor.camera);
        frame(a);
        frame(a, true);
        frame(z, true);
        frame(z);
        check(editor.dirty() && !same(initial, editor.document().instances[chosen].transform),
              "dragging a move handle changes the selected transform");
        editor.undo();
        check(same(initial, editor.document().instances[chosen].transform) && !editor.dirty(),
              "a complete drag undoes in one step and restores clean state");
        editor.redo();
        check(editor.dirty(), "redo restores the drag");
        editor.undo();
        editor.translate({.375f, 1, -.75f});
        auto moved = editor.document().instances[chosen].transform;
        editor.rotate({0, 1, 0}, 35);
        auto rotated = editor.document().instances[chosen].transform;
        editor.scale({1.2f, .8f, 1.1f});
        check(!same(rotated, editor.document().instances[chosen].transform), "scale changes geometry");
        editor.undo();
        check(same(rotated, editor.document().instances[chosen].transform),
              "scale undo preserves original rotation");
        editor.undo();
        check(same(moved, editor.document().instances[chosen].transform),
              "rotation undo preserves translation");
        editor.undo();
        check(!editor.dirty() && same(initial, editor.document().instances[chosen].transform),
              "undo reaches saved state");
        const auto count = editor.document().instances.size();
        editor.duplicate();
        check(editor.document().instances.size() == count + 1, "duplicate adds a mesh instance");
        editor.remove();
        check(editor.document().instances.size() == count, "delete removes the selected instance");
        editor.undo();
        check(editor.document().instances.size() == count + 1, "undo restores a deleted object");
        editor.undo();
        check(editor.document().instances.size() == count, "undo removes the duplicate");
        editor.addAsset(original.instances[chosen].asset);
        check(editor.document().instances.size() == count + 1,
              "asset palette placement adds a library instance");
        editor.undo();
        editor.select(chosen);
        editor.translate({2, 0, 0});
        const auto started = std::chrono::steady_clock::now();
        check(editor.save(), editor.status);
        const auto saveMs =
            std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count();
        check(!editor.dirty() && std::filesystem::exists(directory / "town.scene.bak") &&
                  std::filesystem::exists(directory / "town.nav.bak"),
              "save writes navigation and scene backups then marks the project clean");
        TownDocument saved;
        check(saved.load(directory / "town.scene", error), error);
        check(same(saved.instances[chosen].transform, editor.document().instances[chosen].transform),
              "saved layout reloads precisely");
        HubWorld town;
        check(town.load(directory / "town.nav") && town.moveTo(town.mission),
              "saved navigation still connects arrival and missions");
        const auto savedSceneBytes = bytes(directory / "town.scene");
        const auto savedNavBytes = bytes(directory / "town.nav");
        auto invalidNavigation = editor.navigation();
        invalidNavigation.spawn = {10000, 0, 10000};
        bool rejected = false;
        try {
            saveTownProject(directory, editor.document(), invalidNavigation);
        } catch (const std::exception &) {
            rejected = true;
        }
        check(rejected && bytes(directory / "town.scene") == savedSceneBytes &&
                  bytes(directory / "town.nav") == savedNavBytes &&
                  !std::filesystem::exists(directory / "town.scene.tmp"),
              "failed validation leaves both saved files intact and removes staged files");
        editor.translate({1, 0, 0});
        editor.undo();
        check(!editor.dirty(), "undo after saving returns to saved state");
        editor.redo();
        check(editor.dirty(), "redo after saving marks changes dirty");
        editor.requestClose(true);
        frame();
        check(editor.active, "unsaved window close requires an explicit save/discard choice");
        click({898, 470});
        check(editor.active && !editor.quitRequested, "cancel keeps the editor open");
        check(editor.reload() && !editor.dirty(), "reload restores the saved scene");
        editor.select(chosen);
        editor.focusSelection();
        frame();
        const auto angle = unit(sub(editor.camera.position, editor.camera.target));
        frame({700, 450}, false, true);
        frame({810, 490}, false, true);
        frame();
        check(distance(angle, unit(sub(editor.camera.position, editor.camera.target))) > .1f,
              "middle drag orbits editor camera");
        const auto target = editor.camera.target;
        frame({700, 450}, false, false, true);
        frame({740, 470}, false, false, true);
        frame();
        check(distance(target, editor.camera.target) > .1f, "right drag pans editor camera");
        check(editor.open(directory,
                          {add(nav.spawn, {23, 30, 23}), nav.spawn, {0, 1, 0}, 45, CAMERA_PERSPECTIVE}),
              editor.status);
        editor.select(chosen);
        frame();
        std::filesystem::create_directories("artifacts");
        auto capture = LoadImageFromScreen();
        check(ExportImage(capture, "artifacts/town-editor.png"), "editor preview exports");
        UnloadImage(capture);
        const auto moving =
            std::find_if(editor.document().instances.begin(), editor.document().instances.end(),
                         [](const auto &i) { return i.motion.kind == ObjectMotionKind::Tumbleweed; });
        check(moving != editor.document().instances.end(), "town exposes tumbleweed animation in the editor");
        const size_t weed = size_t(moving - editor.document().instances.begin());
        const auto rest = moving->transform;
        const auto stableId = moving->id;
        editor.select(weed);
        editor.focusSelection();
        click({1345, 178}); // Animation inspector.
        click({1190, 698}); // Play preview.
        check(editor.previewPlaying(), "the Animation inspector starts preview playback");
        for (int n = 0; n < 40; ++n)
            frame();
        check(!same(editor.animationPreview().poses()[weed].transform, rest) && !editor.dirty() &&
                  same(editor.document().instances[weed].transform, rest),
              "preview moves the mesh while preserving saved placement and clean state");
        click({1190, 698});
        const auto frozen = editor.animationPreview().poses()[weed].transform;
        for (int n = 0; n < 5; ++n)
            frame();
        check(!editor.previewPlaying() && same(frozen, editor.animationPreview().poses()[weed].transform),
              "the inspector pauses animation exactly");
        capture = LoadImageFromScreen();
        check(ExportImage(capture, "artifacts/town-animation-editor.png"),
              "animation inspector capture exports");
        UnloadImage(capture);
        click({1340, 698}); // Reset.
        check(same(editor.animationPreview().poses()[weed].transform, rest),
              "reset restores the authored pose");
        click({1340, 246}); // Spin preset.
        check(editor.document().instances[weed].motion.kind == ObjectMotionKind::Spin && editor.dirty(),
              "a reusable animation preset can be assigned through the inspector");
        editor.undo();
        check(editor.document().instances[weed].motion.kind == ObjectMotionKind::Tumbleweed &&
                  !editor.dirty(),
              "undo restores the previous animation settings and saved revision");
        editor.duplicate();
        check(editor.document().instances.back().id != stableId &&
                  editor.document().instances.back().motion.kind == ObjectMotionKind::Tumbleweed,
              "duplicated animated objects retain settings and get a distinct stable ID");
        editor.remove();
        editor.undo();
        check(editor.document().instances.back().motion.kind == ObjectMotionKind::Tumbleweed,
              "undoing deletion restores the animation with its object");
        editor.undo();
        editor.select(weed);
        auto changedMotion = editor.document().instances[weed].motion;
        changedMotion.speed = .9f;
        editor.setMotion(changedMotion);
        editor.setPreviewPlaying(true);
        for (int n = 0; n < 30; ++n)
            frame();
        check(editor.save(), editor.status);
        TownDocument animatedSaved;
        check(animatedSaved.load(directory / "town.scene", error) &&
                  animatedSaved.instances[weed].id == stableId &&
                  animatedSaved.instances[weed].motion.speed == .9f &&
                  same(animatedSaved.instances[weed].transform, rest),
              "saving during playback writes settings and rest transforms, never the temporary pose");
        check(editor.reload() && editor.document().instances[weed].motion.speed == .9f &&
                  editor.animationPreview().time() == 0,
              "reload restores motion settings with a fresh preview");
        editor.requestClose();
        check(!editor.active && !editor.quitRequested, "clean editor closes back to town");
        editor.unload();
        CloseWindow();
        std::filesystem::remove_all(directory);
        std::cout << "PASS editor picking, gizmo drag, transforms, add/duplicate/delete, undo/redo, dirty "
                     "state, save/reload, backups, navigation, camera and close guard; save_ms="
                  << saveMs << '\n';
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << "\nTemporary town: " << directory << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
