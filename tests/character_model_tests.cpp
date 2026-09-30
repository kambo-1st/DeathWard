#include "render/TownActorModels.hpp"
#include "raymath.h"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(900, 700, "Cowgirl animation verification");
        SkinnedModel model;
        check(model.load(TownActorModels::cowgirlPath(), true), "Cowgirl model loads");
        const auto &mesh = model.model();
        check(mesh.boneCount == 48, "Original 48-bone skeleton preserved");
        bool texture = false;
        for (int m = 0; m < mesh.materialCount; ++m)
            texture |= mesh.materials[m].maps[MATERIAL_MAP_ALBEDO].texture.width == 2048;
        check(texture, "Original embedded 2048px texture uploaded");
        const auto bounds = GetModelBoundingBox(mesh);
        check(bounds.max.y - bounds.min.y > 1.6f && bounds.max.y - bounds.min.y < 2.1f, "Cowgirl uses meter scale");
        for (int frame = 0; frame < 500; ++frame) {
            model.pose(double(frame) / 30, float(frame % 3) * .5f, frame % 2 ? 1.f : 0.f);
            for (int m = 0; m < mesh.meshCount; ++m)
                for (int v = 0; v < mesh.meshes[m].vertexCount * 3; ++v)
                    check(std::isfinite(mesh.meshes[m].animVertices[v]) && std::abs(mesh.meshes[m].animVertices[v]) < 4,
                          "All animation blends remain finite and correctly scaled");
        }
        std::filesystem::create_directories("artifacts");
        for (int stage = 0; stage < 3; ++stage) {
            model.pose(.43, stage == 2 ? 1.f : 0.f, stage == 1 ? 1.f : 0.f);
            const auto pose = model.bonePose();
            BeginDrawing();
            ClearBackground({106, 124, 128, 255});
            BeginMode3D({{3.3f, 2.1f, 3.3f}, {0, .9f, 0}, {0, 1, 0}, 40, CAMERA_PERSPECTIVE});
            DrawPlane({0, -.01f, 0}, {20, 20}, {171, 150, 116, 255});
            model.draw({}, {0, 0, 1}, 1);
            EndMode3D();
            auto image = LoadImageFromScreen();
            ExportImage(image, ("artifacts/cowgirl-pose-" + std::to_string(stage) + ".png").c_str());
            UnloadImage(image);
            EndDrawing();
            model.pose(.43, stage == 2 ? 1.f : 0.f, stage == 1 ? 1.f : 0.f);
            for (size_t n = 0; n < pose.size(); ++n)
                check(distance(pose[n].translation, model.bonePose()[n].translation) < .00001f,
                      "Drawing does not advance character animation");
        }
        model.unload();
        check(model.load(TownActorModels::modelPath("bandit"), true), "Bandit resident model loads");
        const auto banditBounds = GetModelBoundingBox(model.model());
        const float banditScale = 2.05f / (banditBounds.max.y - banditBounds.min.y);
        for (int n = 0; n < 60; ++n) {
            check(model.pose(double(n) / 30, float(n % 2)), "Bandit idle/walk blends load");
            const auto b = model.bounds({}, {0,0,1}, banditScale);
            check(std::isfinite(b.min.y) && b.max.y > 1.5f && b.max.y < 2.5f && b.min.y > -.2f,
                  "Bandit residents remain grounded at human scale while animated");
        }
        model.unload();
        CloseWindow();
        std::cout << "PASS cowgirl texture, all three blended clips, scale and independent rendered poses\n";
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
