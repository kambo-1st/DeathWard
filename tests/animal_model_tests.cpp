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
void checkScaledSkinning() {
    BoneInfo bones[3]{};
    bones[0].parent = -1;
    bones[1].parent = 0;
    bones[2].parent = 1;
    // Imported global translations omit scale at both levels of this chain.
    Transform chain[3]{{{1, 2, 3}, QuaternionIdentity(), {2, 3, 4}},
                       {{2, 3, 4}, QuaternionIdentity(), {1, 3, 4}},
                       {{3, 4, 5}, QuaternionIdentity(), {1, 3, 4}}};
    Transform *frame = chain;
    ModelAnimation animation{};
    animation.boneCount = 3;
    animation.frameCount = 1;
    animation.bones = bones;
    animation.framePoses = &frame;
    AnimalModels::correctAnimationScale(animation);
    check(Vector3Distance(chain[1].translation, {3, 5, 7}) < .00001f &&
              Vector3Distance(chain[2].translation, {4, 8, 11}) < .00001f,
          "Imported animation translations inherit every ancestor's scale");
    Model model = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    auto &mesh = model.meshes[0];
    model.boneCount = 1;
    model.bindPose = static_cast<Transform *>(MemAlloc(sizeof(Transform)));
    model.bindPose[0] = {{1, 2, 3}, QuaternionIdentity(), {1, 1, 1}};
    mesh.animVertices = static_cast<float *>(MemAlloc(mesh.vertexCount * 3 * sizeof(float)));
    mesh.animNormals = static_cast<float *>(MemAlloc(mesh.vertexCount * 3 * sizeof(float)));
    mesh.boneIds = static_cast<unsigned char *>(MemAlloc(mesh.vertexCount * 4));
    mesh.boneWeights = static_cast<float *>(MemAlloc(mesh.vertexCount * 4 * sizeof(float)));
    std::fill_n(mesh.boneIds, mesh.vertexCount * 4, 0);
    std::fill_n(mesh.boneWeights, mesh.vertexCount * 4, 0.f);
    for (int v = 0; v < mesh.vertexCount; ++v)
        mesh.boneWeights[4*v] = 1;
    const Transform pose{{4, 5, 6}, QuaternionFromAxisAngle({0, 0, 1}, PI/2), {2, 3, .5f}};
    AnimalModels::applyPose(model, &pose);
    bool valid = true;
    for (int v = 0; v < mesh.vertexCount; ++v) {
        const auto *p = mesh.vertices + 3*v;
        const auto *n = mesh.normals + 3*v;
        const Vector3 expected{4 - 3*(p[1]-2), 5 + 2*(p[0]-1), 6 + .5f*(p[2]-3)};
        const Vector3 expectedNormal = Vector3Normalize({-n[1]/3, n[0]/2, n[2]*2});
        const auto *actual = mesh.animVertices + 3*v;
        const auto *actualNormal = mesh.animNormals + 3*v;
        valid &= Vector3Distance(expected, {actual[0], actual[1], actual[2]}) < .00001f;
        valid &= Vector3Distance(expectedNormal, {actualNormal[0], actualNormal[1], actualNormal[2]}) < .00001f;
    }
    UnloadModel(model);
    check(valid, "Bone scale and rotation preserve the pivot and use inverse-transpose normals");
}
int main(int argc, char **argv) {
    std::string current;
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(900, 700, "Animal asset verification");
        check(IsWindowReady(), "Graphics display required");
        checkScaledSkinning();
        AnimalModels models;
        std::filesystem::create_directories("artifacts");
        for (size_t kind = 0; kind < size_t(AnimalKind::Count); ++kind) {
            const auto species = AnimalKind(kind);
            const std::string name = animalName(species);
            if (argc > 1 && name != argv[1])
                continue;
            current = name;
            const auto path = argc > 2 ? std::filesystem::absolute(argv[2])
                                       : std::filesystem::path(GetApplicationDirectory()) / "assets/animals" /
                                             (name + ".glb");
            auto cwd = std::filesystem::current_path();
            std::filesystem::current_path(std::filesystem::temp_directory_path());
            check(models.load(species, path),
                  "Animal mesh, skeleton and Idle/Walk clips load away from repository");
            std::filesystem::current_path(cwd);
            const auto &model = models.model(species);
            bool textured = false;
            for (int m = 0; m < model.materialCount; ++m)
                textured |= model.materials[m].maps[MATERIAL_MAP_ALBEDO].texture.width > 1;
            check(textured, "Original albedo texture is embedded and uploaded");
            auto bounds = GetModelBoundingBox(model);
            const float height = bounds.max.y - bounds.min.y;
            check(height > .01f && height < 30, "Animal uses physical meter scale, not FBX centimeters");
            const float span = std::max({height, bounds.max.x - bounds.min.x, bounds.max.z - bounds.min.z});
            const float limit =
                3 * std::max({std::abs(bounds.min.x), std::abs(bounds.min.y), std::abs(bounds.min.z),
                              std::abs(bounds.max.x), std::abs(bounds.max.y), std::abs(bounds.max.z), 1.f});
            int clipCount = 0;
            auto *allClips = LoadModelAnimations(path.string().c_str(), &clipCount);
            check(allClips && clipCount > 0, "Source animation library loads");
            std::string invalidClip;
            for (int clip = 0; clip < clipCount; ++clip) {
                auto &take = allClips[clip];
                check(IsModelAnimationValid(model, take) && take.frameCount >= 2,
                      "Every preserved source clip matches the exported skeleton");
                AnimalModels::correctAnimationScale(take);
                for (int frame : {0, take.frameCount / 2, take.frameCount - 1}) {
                    AnimalModels::applyPose(model, take.framePoses[frame]);
                    for (int mesh = 0; mesh < model.meshCount; ++mesh)
                        for (int v = 0; v < model.meshes[mesh].vertexCount * 3; ++v) {
                            const float value = model.meshes[mesh].animVertices[v];
                            if (invalidClip.empty() && (!std::isfinite(value) || std::abs(value) >= limit))
                                invalidClip = std::string("Invalid skinned vertex in clip ") + take.name +
                                              " frame=" + std::to_string(frame) +
                                              " value=" + std::to_string(value) +
                                              " limit=" + std::to_string(limit);
                        }
                }
            }
            UnloadModelAnimations(allClips, clipCount);
            Animal animal;
            animal.kind = species;
            animal.facing = {0, 0, 1};
            animal.phase = .1;
            check(models.pose(animal), "Idle pose samples");
            const auto first = models.bonePose(species);
            const auto rest = std::vector<float>(
                model.meshes[0].animVertices, model.meshes[0].animVertices + 3 * model.meshes[0].vertexCount);
            const auto render = [&](const char *stage) {
                Vector3 low{1000, 1000, 1000}, high{-1000, -1000, -1000};
                for (int mesh = 0; mesh < model.meshCount; ++mesh)
                    for (int v = 0; v < model.meshes[mesh].vertexCount; ++v) {
                        const auto *p = model.meshes[mesh].animVertices + 3*v;
                        const Vector3 point{p[0], p[1] + .015f - bounds.min.y, p[2]};
                        low = Vector3Min(low, point);
                        high = Vector3Max(high, point);
                    }
                const Vector3 focus = Vector3Scale(Vector3Add(low, high), .5f);
                const float previewSpan = std::max({high.x-low.x, high.y-low.y, high.z-low.z});
                Camera3D camera{add(focus, {previewSpan * 1.4f, previewSpan * .7f, previewSpan * 1.5f}),
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
            check(difference > span * .001f, "Locomotion clip visibly deforms the skinned mesh");
            render("walk");
            check(models.clipNames(species).size() == size_t(clipCount), "the picker exposes every imported animation");
            if (species == AnimalKind::Horse) {
                animal.activity = {true, 1, {"Eat"}};
                animal.phase = .65;
                check(models.pose(animal), "a selected stationary eating clip plays");
                const auto eat = models.bonePose(species);
                render("stationary-eat");
                animal.phase = .65 + models.clipDuration(species, "Eat");
                models.pose(animal);
                for (size_t n = 0; n < eat.size(); ++n)
                    check(distance(eat[n].translation, models.bonePose(species)[n].translation) < .0001f,
                          "a selected clip loops at its original duration");
                animal.activity.clips = {"Idle", "Eat"};
                animal.phase = models.clipDuration(species, "Idle") + .65;
                models.pose(animal);
                for (size_t n = 0; n < eat.size(); ++n)
                    check(distance(eat[n].translation, models.bonePose(species)[n].translation) < .0001f,
                          "an ordered sequence reaches the chosen eating clip");
                animal.activity.speed = .5f;
                animal.phase *= 2;
                models.pose(animal);
                for (size_t n = 0; n < eat.size(); ++n)
                    check(distance(eat[n].translation, models.bonePose(species)[n].translation) < .0001f,
                          "playback speed scales the entire sequence");
                animal.activity = {};
                animal.phase = .43;
                models.pose(animal);
            }
            check(invalidClip.empty(), invalidClip.c_str());
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
                                  std::abs(p[0]) < limit && std::abs(p[1]) < limit && std::abs(p[2]) < limit,
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
            std::cout << "PASS " << name
                      << " texture, skeleton, blend, independent poses and rendered skinning\n";
            models.unload(); // Bound VRAM and pose memory while checking the whole library.
        }
        check(!models.load(AnimalKind::Horse, "/missing/animal.glb"), "Missing animal asset fails safely");
        models.unload();
        models.unload();
        CloseWindow();
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << current << ": " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
