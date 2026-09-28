#include "render/SkinnedModel.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cctype>
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
Matrix matrix(const Transform &t) {
    return MatrixMultiply(MatrixMultiply(MatrixScale(t.scale.x, t.scale.y, t.scale.z),
                                         QuaternionToMatrix(t.rotation)),
                          MatrixTranslate(t.translation.x, t.translation.y, t.translation.z));
}
} // namespace
void SkinnedModel::correctAnimationScale(ModelAnimation &animation) {
    // raylib 5.5 composes imported translations without parent scale. Recover
    // its local transforms, then rebuild the hierarchy with full TRS semantics.
    for (int frame = 0; frame < animation.frameCount; ++frame) {
        auto *pose = animation.framePoses[frame];
        for (int bone = animation.boneCount - 1; bone >= 0; --bone) {
            const int parent = animation.bones[bone].parent;
            if (parent < 0)
                continue;
            const auto translation = Vector3RotateByQuaternion(
                sub(pose[bone].translation, pose[parent].translation), QuaternionInvert(pose[parent].rotation));
            pose[bone] = local(pose[parent], pose[bone]);
            pose[bone].translation = translation;
        }
        for (int bone = 0; bone < animation.boneCount; ++bone) {
            const int parent = animation.bones[bone].parent;
            if (parent >= 0)
                pose[bone] = combine(pose[parent], pose[bone]);
        }
    }
}
void SkinnedModel::applyPose(Model model, const Transform *pose) {
    std::vector<Matrix> transforms(size_t(model.boneCount)), normals(size_t(model.boneCount));
    for (int bone = 0; bone < model.boneCount; ++bone) {
        auto &transform = transforms[size_t(bone)];
        transform = MatrixMultiply(MatrixInvert(matrix(model.bindPose[bone])), matrix(pose[bone]));
        auto &normal = normals[size_t(bone)];
        normal = MatrixTranspose(MatrixInvert(transform));
        normal.m12 = normal.m13 = normal.m14 = 0;
    }
    for (int m = 0; m < model.meshCount; ++m) {
        auto &mesh = model.meshes[m];
        for (int v = 0; v < mesh.vertexCount; ++v) {
            const Vector3 original{mesh.vertices[3*v], mesh.vertices[3*v+1], mesh.vertices[3*v+2]};
            const Vector3 normal = mesh.normals
                ? Vector3{mesh.normals[3*v], mesh.normals[3*v+1], mesh.normals[3*v+2]} : Vector3{};
            Vector3 position{}, direction{};
            for (int influence = 0; influence < 4; ++influence) {
                const float weight = mesh.boneWeights[4*v+influence];
                if (weight == 0)
                    continue;
                const auto bone = mesh.boneIds[4*v+influence];
                position = Vector3Add(position, Vector3Scale(Vector3Transform(original, transforms[bone]), weight));
                direction = Vector3Add(direction, Vector3Scale(Vector3Transform(normal, normals[bone]), weight));
            }
            direction = Vector3Normalize(direction);
            const std::array<float, 3> xyz{position.x, position.y, position.z};
            std::copy(xyz.begin(), xyz.end(), mesh.animVertices + 3*v);
            if (mesh.animNormals) {
                const std::array<float, 3> normalXYZ{direction.x, direction.y, direction.z};
                std::copy(normalXYZ.begin(), normalXYZ.end(), mesh.animNormals + 3*v);
            }
        }
        rlUpdateVertexBuffer(mesh.vboId[0], mesh.animVertices, mesh.vertexCount*3*sizeof(float), 0);
        if (mesh.animNormals)
            rlUpdateVertexBuffer(mesh.vboId[2], mesh.animNormals, mesh.vertexCount*3*sizeof(float), 0);
    }
}
SkinnedModel::~SkinnedModel() {
    unload();
}
void SkinnedModel::unload(Asset &a) {
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
void SkinnedModel::unload() { unload(asset_); }
bool SkinnedModel::load(const std::filesystem::path &path, bool alternateIdle) {
    auto &a = asset_;
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
    std::vector<std::string> names;
    for (int n = 0; n < count; ++n) {
        std::string name = clips[n].name;
        for (auto &c : name)
            c = char(std::tolower(static_cast<unsigned char>(c)));
        names.push_back(std::move(name));
    }
    const auto choose = [&](std::initializer_list<const char *> preferred) {
        for (const auto *name : preferred)
            for (int n = 0; n < count; ++n)
                if (names[size_t(n)] == name)
                    return n;
        return -1;
    };
    int idle = choose({"idle", "idlea", "idle2", "idleleft", "idle1", "idlebreathing", "idlebreath"});
    int move = choose({"walk", "walking", "slowwalk", "slither", "swim", "fly", "slow", "run", "fast"});
    if (idle < 0)
        idle = move >= 0 ? move : 0;
    if (move < 0)
        move = idle;
    int third = choose({"eat", "eating", "eatingloop"});
    if (third < 0 && alternateIdle) third = choose({"idle2"});
    const std::array<int, 3> selected{idle, move, third};
    for (int n = 0; valid && n < count; ++n) {
        const auto &clip = clips[n];
        valid = clip.frameCount >= 2 && IsModelAnimationValid(a.model, clip);
        if (!valid)
            continue;
        correctAnimationScale(clips[n]);
        for (size_t slot = 0; slot < selected.size(); ++slot) {
            if (selected[slot] != n)
                continue;
            auto &output = a.clips[slot];
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
    }
    if (clips)
        UnloadModelAnimations(clips, count);
    valid = valid && !a.clips[0].frames.empty() && !a.clips[1].frames.empty();
    for (int n = 0; valid && n < a.model.meshCount; ++n) {
        const auto &mesh = a.model.meshes[n];
        valid = mesh.boneIds && mesh.boneWeights && mesh.animVertices;
    }
    if (!valid) {
        TraceLog(LOG_WARNING, "SKIN: Invalid model or animation set: %s", path.string().c_str());
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
Transform SkinnedModel::sample(const Clip &c, double seconds, size_t bone) const {
    const float frame = float(std::fmod(std::max(0., seconds), double(c.duration))) / SampleSeconds;
    const size_t first = std::min(size_t(frame), c.frames.size() - 1),
                 next = std::min(first + 1, c.frames.size() - 1);
    return mix(c.frames[first][bone], c.frames[next][bone], frame - float(first));
}
bool SkinnedModel::pose(double phase, float walking, float alternate) {
    auto &a = asset_;
    if (!loaded()) return false;
    for (size_t bone = 0; bone < a.world.size(); ++bone) {
        auto rest = sample(a.clips[0], phase, bone);
        if (!a.clips[2].frames.empty())
            rest = mix(rest, sample(a.clips[2], phase, bone), alternate);
        const auto value = mix(rest, sample(a.clips[1], phase, bone), walking);
        const int parent = a.model.bones[bone].parent;
        a.world[bone] = parent < 0 ? value : combine(a.world[size_t(parent)], value);
    }
    applyPose(a.model, a.world.data());
    return true;
}
void SkinnedModel::draw(Vector3 position, Vector3 facing, float scale, Shader shader, Texture2D shadowMap) {
    if (!loaded()) return;
    const auto &a = asset_;
    const auto p = add(position, {0, a.floor * scale, 0});
    const auto transform = MatrixMultiply(
        a.model.transform,
        MatrixMultiply(MatrixMultiply(MatrixScale(scale, scale, scale),
                                      MatrixRotateY(std::atan2(facing.x, facing.z))),
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
