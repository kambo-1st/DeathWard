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
void SkinnedModel::unload() {
    for (auto &accessory : wardrobe_)
        accessory.unload();
    unload(asset_);
}
bool SkinnedModel::load(const std::filesystem::path &path, bool alternateIdle) {
    unload();
    auto &a = asset_;
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
        a.names.emplace_back(clips[n].name);
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
    a.slots = {idle, move, third};
    a.clips.resize(size_t(count));
    for (int n = 0; valid && n < count; ++n) {
        const auto &clip = clips[n];
        valid = clip.frameCount >= 2 && IsModelAnimationValid(a.model, clip);
        if (!valid)
            continue;
        correctAnimationScale(clips[n]);
        {
            auto &output = a.clips[size_t(n)];
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
    valid = valid && idle >= 0 && move >= 0 && size_t(idle) < a.clips.size() && size_t(move) < a.clips.size() &&
            !a.clips[size_t(idle)].frames.empty() && !a.clips[size_t(move)].frames.empty();
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
        auto rest = sample(a.clips[size_t(a.slots[0])], phase, bone);
        if (a.slots[2] >= 0)
            rest = mix(rest, sample(a.clips[size_t(a.slots[2])], phase, bone), alternate);
        const auto value = mix(rest, sample(a.clips[size_t(a.slots[1])], phase, bone), walking);
        const int parent = a.model.bones[bone].parent;
        a.world[bone] = parent < 0 ? value : combine(a.world[size_t(parent)], value);
    }
    applyPose(a.model, a.world.data());
    return true;
}
float SkinnedModel::clipDuration(const std::string &name) const {
    const auto at = std::find(asset_.names.begin(), asset_.names.end(), name);
    return at == asset_.names.end() ? 0 : asset_.clips[size_t(at - asset_.names.begin())].duration;
}
bool SkinnedModel::poseSequence(double seconds, const std::vector<std::string> &names, float speed) {
    auto &a = asset_;
    if (!loaded()) return false;
    if (names.empty()) return pose(seconds * speed, 0);
    std::vector<size_t> sequence;
    double total = 0;
    for (const auto &name : names) {
        const auto at = std::find(a.names.begin(), a.names.end(), name);
        if (at == a.names.end()) return pose(seconds * speed, 0);
        const auto index = size_t(at - a.names.begin());
        sequence.push_back(index);
        total += a.clips[index].duration;
    }
    double time = std::fmod(std::max(0., seconds * speed), total);
    size_t current = 0;
    while (current + 1 < sequence.size() && time >= a.clips[sequence[current]].duration) {
        time -= a.clips[sequence[current]].duration;
        ++current;
    }
    const auto &clip = a.clips[sequence[current]];
    const auto &previous = a.clips[sequence[(current + sequence.size() - 1) % sequence.size()]];
    const float transition = std::min(.15f, clip.duration * .2f);
    const float blend = std::clamp(float(time) / transition, 0.f, 1.f);
    for (size_t bone = 0; bone < a.world.size(); ++bone) {
        auto value = sample(clip, time, bone);
        // Once the transition ends, sample this clip exactly. Slerping by 1
        // can still retain the preceding quaternion when their dot rounds to 1.
        if (blend < 1 && seconds * speed >= transition)
            value = mix(previous.frames.back()[bone], value, blend * blend * (3 - 2 * blend));
        const int parent = a.model.bones[bone].parent;
        a.world[bone] = parent < 0 ? value : combine(a.world[size_t(parent)], value);
    }
    applyPose(a.model, a.world.data());
    return true;
}
Box SkinnedModel::bounds(Vector3 position, Vector3 facing, float scale) const {
    const auto p = add(position, {0, asset_.floor * scale, 0});
    const auto transform = MatrixMultiply(asset_.model.transform,
        MatrixMultiply(MatrixMultiply(MatrixScale(scale, scale, scale),
                                      MatrixRotateY(std::atan2(facing.x, facing.z))), MatrixTranslate(p.x, p.y, p.z)));
    Box result{{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    for (int m = 0; m < asset_.model.meshCount; ++m) {
        const auto &mesh = asset_.model.meshes[m];
        const auto *vertices = mesh.animVertices ? mesh.animVertices : mesh.vertices;
        for (int n = 0; n < mesh.vertexCount; ++n) {
            const auto v = Vector3Transform({vertices[n * 3], vertices[n * 3 + 1], vertices[n * 3 + 2]}, transform);
            result.min = Vector3Min(result.min, v);
            result.max = Vector3Max(result.max, v);
        }
    }
    return result;
}
void SkinnedModel::draw(Vector3 position, Vector3 facing, float scale, Shader shader, Texture2D shadowMap,
                        int costume) {
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
    if (costume > 0 && costume <= int(wardrobe_.size()))
        wardrobe_[size_t(costume - 1)].draw(a.model, a.world, transform, shader, shadowMap, costume);
}
} // namespace dw
