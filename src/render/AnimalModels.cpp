#include "render/AnimalModels.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cstring>
#include <set>

namespace dw {
namespace {
constexpr float SampleSeconds = .017f; // Pinned raylib glTF sampling interval.
Transform local(const Transform &parent, const Transform &world) {
    const auto inv = QuaternionInvert(parent.rotation);
    return {Vector3Divide(Vector3RotateByQuaternion(sub(world.translation, parent.translation), inv),
                          parent.scale),
            QuaternionMultiply(inv, world.rotation), Vector3Divide(world.scale, parent.scale)};
}
Transform combine(const Transform &parent, const Transform &child) {
    return {add(parent.translation,
                Vector3RotateByQuaternion(Vector3Multiply(child.translation, parent.scale), parent.rotation)),
            QuaternionMultiply(parent.rotation, child.rotation), Vector3Multiply(parent.scale, child.scale)};
}
Transform mix(const Transform &a, const Transform &b, float t) {
    return {Vector3Lerp(a.translation, b.translation, t), QuaternionSlerp(a.rotation, b.rotation, t),
            Vector3Lerp(a.scale, b.scale, t)};
}
} // namespace
std::filesystem::path AnimalModels::assetDirectory() {
#ifdef __EMSCRIPTEN__
    return "/assets/animals";
#else
    const auto source = std::filesystem::path(DEATHWARD_ASSET_DIR) / "animals";
    if (std::filesystem::is_directory(source))
        return source;
    return std::filesystem::path(GetApplicationDirectory()) / "assets/animals";
#endif
}
AnimalModels::~AnimalModels() {
    unload();
}
void AnimalModels::unload(Asset &a) {
    std::set<unsigned> textures;
    for (int n = 0; n < a.model.materialCount; ++n)
        for (int map = 0; map <= MATERIAL_MAP_BRDF; ++map) {
            const auto texture = a.model.materials[n].maps[map].texture;
            if (texture.id && texture.id != rlGetTextureIdDefault() && textures.insert(texture.id).second)
                UnloadTexture(texture);
        }
    if (a.model.meshCount)
        UnloadModel(a.model);
    a = {};
}
void AnimalModels::unload() {
    for (auto &a : assets_)
        unload(a);
}
bool AnimalModels::loaded(AnimalKind kind) const {
    return assets_.at(size_t(kind)).model.meshCount > 0;
}
void AnimalModels::prepare(const Animals &animals) {
    for (const auto &animal : animals.residents())
        if (!assets_[size_t(animal.kind)].attempted)
            load(animal.kind, assetDirectory() / (std::string(animalName(animal.kind)) + ".glb"));
}
const Model &AnimalModels::model(AnimalKind kind) const {
    return assets_.at(size_t(kind)).model;
}
const std::vector<Transform> &AnimalModels::bonePose(AnimalKind kind) const {
    return assets_.at(size_t(kind)).world;
}
bool AnimalModels::load(AnimalKind kind, const std::filesystem::path &path) {
    auto &a = assets_.at(size_t(kind));
    unload(a);
    a.attempted = true;
    if (!std::filesystem::is_regular_file(path))
        return false;
    a.model = LoadModel(path.string().c_str());
    int count = 0;
    auto *clips = LoadModelAnimations(path.string().c_str(), &count);
    bool valid = a.model.meshCount > 0 && a.model.boneCount > 0 && a.model.boneCount <= 255 && clips &&
                 a.model.bindPose;
    for (int n = 0; valid && n < a.model.boneCount; ++n)
        valid = a.model.bones[n].parent >= -1 && a.model.bones[n].parent < n;
    for (int n = 0; valid && n < count; ++n) {
        const auto &clip = clips[n];
        valid = clip.frameCount >= 2 && IsModelAnimationValid(a.model, clip);
        int slot = std::strcmp(clip.name, "Idle") == 0   ? 0
                   : std::strcmp(clip.name, "Walk") == 0 ? 1
                   : std::strcmp(clip.name, "Eat") == 0  ? 2
                                                         : -1;
        if (!valid || slot < 0)
            continue;
        auto &output = a.clips[size_t(slot)];
        output.duration = (clip.frameCount - 1) * SampleSeconds;
        for (int frame = 0; frame < clip.frameCount; ++frame) {
            auto &pose = output.frames.emplace_back();
            pose.resize(size_t(a.model.boneCount));
            for (int bone = 0; bone < a.model.boneCount; ++bone) {
                const int parent = a.model.bones[bone].parent;
                pose[size_t(bone)] =
                    parent < 0 ? clip.framePoses[frame][bone]
                               : local(clip.framePoses[frame][parent], clip.framePoses[frame][bone]);
            }
        }
    }
    if (clips)
        UnloadModelAnimations(clips, count);
    valid = valid && !a.clips[0].frames.empty() && !a.clips[1].frames.empty();
    for (int n = 0; valid && n < a.model.meshCount; ++n) {
        const auto &mesh = a.model.meshes[n];
        valid = mesh.boneIds && mesh.boneWeights && mesh.animVertices;
    }
    if (!valid) {
        TraceLog(LOG_WARNING, "ANIMAL: Invalid model or animation set: %s", path.string().c_str());
        unload(a);
        a.attempted = true;
        return false;
    }
    a.floor = .015f - GetModelBoundingBox(a.model).min.y;
    a.world.resize(size_t(a.model.boneCount));
    for (int n = 0; n < a.model.materialCount; ++n) {
        const auto texture = a.model.materials[n].maps[MATERIAL_MAP_ALBEDO].texture;
        if (texture.id != rlGetTextureIdDefault())
            SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    }
    return true;
}
Transform AnimalModels::sample(const Clip &c, double seconds, size_t bone) const {
    const float frame = float(std::fmod(std::max(0., seconds), double(c.duration))) / SampleSeconds;
    const size_t first = std::min(size_t(frame), c.frames.size() - 1),
                 next = std::min(first + 1, c.frames.size() - 1);
    return mix(c.frames[first][bone], c.frames[next][bone], frame - float(first));
}
bool AnimalModels::pose(const Animal &animal) {
    auto &a = assets_[size_t(animal.kind)];
    if (!a.attempted)
        load(animal.kind, assetDirectory() / (std::string(animalName(animal.kind)) + ".glb"));
    if (!loaded(animal.kind))
        return false;
    for (size_t bone = 0; bone < a.world.size(); ++bone) {
        auto rest = sample(a.clips[0], animal.phase, bone);
        if (!a.clips[2].frames.empty())
            rest = mix(rest, sample(a.clips[2], animal.phase, bone), animal.eating);
        const auto value = mix(rest, sample(a.clips[1], animal.phase, bone), animal.walking);
        const int parent = a.model.bones[bone].parent;
        a.world[bone] = parent < 0 ? value : combine(a.world[size_t(parent)], value);
    }
    Transform *frame = a.world.data();
    ModelAnimation animation{};
    animation.boneCount = a.model.boneCount;
    animation.frameCount = 1;
    animation.bones = a.model.bones;
    animation.framePoses = &frame;
    UpdateModelAnimation(a.model, animation, 0);
    return true;
}
void AnimalModels::draw(const Animals &animals, Shader shader, Texture2D shadowMap) {
    for (const auto &animal : animals.residents())
        draw(animal, shader, shadowMap);
}
void AnimalModels::draw(const Animal &animal, Shader shader, Texture2D shadowMap) {
    if (!pose(animal))
        return;
    const auto &a = assets_[size_t(animal.kind)];
    const auto p = add(animal.position, {0, a.floor * animal.scale, 0});
    const auto transform = MatrixMultiply(
        a.model.transform,
        MatrixMultiply(MatrixMultiply(MatrixScale(animal.scale, animal.scale, animal.scale),
                                      MatrixRotateY(std::atan2(animal.facing.x, animal.facing.z))),
                       MatrixTranslate(p.x, p.y, p.z)));
    for (int n = 0; n < a.model.meshCount; ++n) {
        auto material = a.model.materials[a.model.meshMaterial[n]];
        std::array<MaterialMap, 12> maps;
        std::copy_n(material.maps, maps.size(), maps.begin());
        material.maps = maps.data();
        if (shader.id) {
            material.shader = shader;
            maps[MATERIAL_MAP_METALNESS].texture = shadowMap;
        }
        DrawMesh(a.model.meshes[n], material, transform);
    }
}
} // namespace dw
