#include "raylib.h"
#include "raymath.h"
#include "render/AnimalModels.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(900, 700, "Animal asset verification");
        check(IsWindowReady(), "Graphics display required");
        AnimalModels models;
        std::filesystem::create_directories("artifacts");
        for (size_t kind = 0; kind < size_t(AnimalKind::Count); ++kind) {
            const auto species = AnimalKind(kind);
            const std::string name = animalName(species);
            const auto path =
                std::filesystem::path(GetApplicationDirectory()) / "assets/animals" / (name + ".glb");
            auto cwd = std::filesystem::current_path();
            std::filesystem::current_path(std::filesystem::temp_directory_path());
            check(models.load(species, path),
                  "Animal mesh, skeleton and Idle/Walk clips load away from repository");
            std::filesystem::current_path(cwd);
            const auto &model = models.model(species);
            bool textured = false;
            for (int m = 0; m < model.materialCount; ++m)
                textured |= model.materials[m].maps[MATERIAL_MAP_ALBEDO].texture.width >= 1024;
            check(textured, "Original albedo texture is embedded and uploaded");
            auto bounds = GetModelBoundingBox(model);
            const float height = bounds.max.y - bounds.min.y;
            check(height > .15f && height < 3, "Animal uses physical meter scale, not FBX centimeters");
            Animal animal;
            animal.kind = species;
            animal.facing = {0, 0, 1};
            animal.phase = .1;
            check(models.pose(animal), "Idle pose samples");
            const auto first = models.bonePose(species);
            const auto rest = std::vector<float>(
                model.meshes[0].animVertices, model.meshes[0].animVertices + 3 * model.meshes[0].vertexCount);
            const auto render = [&](const char *stage) {
                const Vector3 focus{0, height * .48f, 0};
                const float span = std::max(height, bounds.max.z - bounds.min.z);
                Camera3D camera{add(focus, {span * 1.4f, span * .7f, span * 1.5f}),
                                focus,
                                {0, 1, 0},
                                40,
                                CAMERA_PERSPECTIVE};
                BeginDrawing();
                ClearBackground({106, 124, 128, 255});
                BeginMode3D(camera);
                DrawPlane({0, -.015f, 0}, {20, 20}, {171, 150, 116, 255});
                models.draw(animal);
                EndMode3D();
                const auto image = LoadImageFromScreen();
                ExportImage(image, ("artifacts/animal-" + name + "-" + stage + ".png").c_str());
                UnloadImage(image);
                EndDrawing();
            };
            render("idle");
            animal.walking = 1;
            animal.phase = .43;
            check(models.pose(animal), "Walk pose samples");
            float difference = 0;
            for (size_t n = 0; n < rest.size(); ++n)
                difference += std::abs(rest[n] - model.meshes[0].animVertices[n]);
            check(difference > .1f, "Walk clip visibly deforms the skinned mesh");
            render("walk");
            const auto walking = models.bonePose(species);
            models.pose(animal);
            for (size_t n = 0; n < walking.size(); ++n)
                check(distance(walking[n].translation, models.bonePose(species)[n].translation) < .000001f,
                      "Repeated rendering never advances animation");
            for (int frame = 0; frame < 180; ++frame) {
                animal.phase = frame * .037;
                animal.walking = float(frame % 3) * .5f;
                animal.eating = 1 - animal.walking;
                models.pose(animal);
                for (int mesh = 0; mesh < model.meshCount; ++mesh)
                    for (int v = 0; v < model.meshes[mesh].vertexCount; ++v) {
                        const auto *p = model.meshes[mesh].animVertices + 3 * v;
                        check(std::isfinite(p[0]) && std::isfinite(p[1]) && std::isfinite(p[2]) &&
                                  std::abs(p[0]) < 5 && std::abs(p[1]) < 5 && std::abs(p[2]) < 5,
                              "Blended poses remain finite and correctly scaled");
                    }
            }
            animal.walking = 0;
            animal.eating = 0;
            animal.phase = .1;
            models.pose(animal);
            for (size_t n = 0; n < first.size(); ++n)
                check(distance(first[n].translation, models.bonePose(species)[n].translation) < .00001f,
                      "Independent resident clocks can reproduce their own pose on a shared model");
            std::cout << "PASS " << name << " texture, skeleton, blend, independent poses and rendered skinning\n";
        }
        check(!models.load(AnimalKind::Horse, "/missing/animal.glb"), "Missing animal asset fails safely");
        models.unload();
        models.unload();
        CloseWindow();
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
