#include "render/ArtWardrobe.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cstring>

namespace dw {
void ArtWardrobe::unload() {
    if (cloth_.meshCount)
        UnloadModel(cloth_);
    cloth_ = {};
    rest_.clear();
    weights_.clear();
    upper_ = lower_ = -1;
    style_ = 0;
}
void ArtWardrobe::build(const Model &rig, int style) {
    unload();
    int neck = -1;
    for (int i = 0; i < rig.boneCount; ++i) {
        const std::string name = rig.bones[i].name;
        if (name == "Neck")
            neck = i;
        if (name == "Spine_03")
            upper_ = i;
        if (name == "Spine_01")
            lower_ = i;
    }
    if (neck < 0 || upper_ < 0 || lower_ < 0)
        return;
    style_ = style;
    const auto bounds = GetModelBoundingBox(rig);
    const float unit = (bounds.max.y - bounds.min.y) / 2.05f;
    const auto center = rig.bindPose[neck].translation;
    std::vector<Color> colors;
    const Color fabric = style == 1   ? Color{136, 60, 43, 255}
                         : style == 2 ? Color{59, 96, 94, 255}
                         : style == 3 ? Color{169, 150, 109, 255}
                                      : Color{106, 67, 79, 255};
    const Color stripe = style == 3 ? Color{76, 88, 91, 255} : Color{184, 158, 113, 255};
    // An open neck and an asymmetric hem leave the revolver arm free. The
    // protagonist's rust poncho, scout's teal wrap and wife's shawl share one rig.
    const auto point = [&](int ring, int i) {
        const float angle = i * Pi / 4;
        const float sx = std::sin(angle), sz = std::cos(angle);
        const float width = ring == 0 ? .135f : ring == 1 ? .41f : .43f;
        const float depth = ring == 0 ? .13f : ring == 1 ? .245f : .27f;
        float drop = ring == 0 ? .025f : ring == 1 ? .17f : .46f + .40f * std::abs(sz);
        if (ring > 1)
            drop *= sx > .3f ? .73f : 1;
        if (style == 3)
            drop *= .5f;
        return add(center, mul({sx * width, -drop, sz * depth}, unit));
    };
    const auto addVertex = [&](Vector3 p, Color c, int ring) {
        rest_.push_back(p);
        colors.push_back(c);
        weights_.push_back(ring > 1 ? .58f : 0.f);
    };
    for (int ring = 0; ring < 3; ++ring)
        for (int i = 0; i < 8; ++i) {
            const auto a = ring < 2 ? point(ring, i) : Vector3Lerp(point(1, i), point(2, i), .87f);
            const auto b =
                ring < 2 ? point(ring, i + 1) : Vector3Lerp(point(1, i + 1), point(2, i + 1), .87f);
            const auto c = ring == 1 ? Vector3Lerp(point(1, i + 1), point(2, i + 1), .87f)
                                     : point(std::min(ring + 1, 2), i + 1);
            const auto d =
                ring == 1 ? Vector3Lerp(point(1, i), point(2, i), .87f) : point(std::min(ring + 1, 2), i);
            const Color color = ring == 2 ? stripe : fabric;
            addVertex(a, color, ring);
            addVertex(b, color, ring);
            addVertex(c, color, ring + 1);
            addVertex(a, color, ring);
            addVertex(c, color, ring + 1);
            addVertex(d, color, ring + 1);
        }
    Mesh m{};
    m.vertexCount = int(rest_.size());
    m.triangleCount = m.vertexCount / 3;
    m.vertices = static_cast<float *>(MemAlloc(rest_.size() * 3 * sizeof(float)));
    m.normals = static_cast<float *>(MemAlloc(rest_.size() * 3 * sizeof(float)));
    m.texcoords = static_cast<float *>(MemAlloc(rest_.size() * 2 * sizeof(float)));
    m.colors = static_cast<unsigned char *>(MemAlloc(rest_.size() * 4));
    std::memcpy(m.vertices, rest_.data(), rest_.size() * sizeof(Vector3));
    std::memset(m.normals, 0, rest_.size() * sizeof(Vector3));
    std::memset(m.texcoords, 0, rest_.size() * sizeof(Vector2));
    std::memcpy(m.colors, colors.data(), rest_.size() * 4);
    UploadMesh(&m, true);
    cloth_ = LoadModelFromMesh(m);
}
void ArtWardrobe::draw(const Model &rig, const std::vector<Transform> &pose, Matrix world, Shader shader,
                       Texture2D shadow, int style) {
    if (style <= 0)
        return;
    if (!cloth_.meshCount || style_ != style)
        build(rig, style);
    if (!cloth_.meshCount || pose.size() != size_t(rig.boneCount))
        return;
    const auto skin = [&](Vector3 p, int bone) {
        const auto &bind = rig.bindPose[bone];
        const auto &now = pose[size_t(bone)];
        auto local = Vector3RotateByQuaternion(sub(p, bind.translation), QuaternionInvert(bind.rotation));
        local = {local.x / bind.scale.x * now.scale.x, local.y / bind.scale.y * now.scale.y,
                 local.z / bind.scale.z * now.scale.z};
        return add(now.translation, Vector3RotateByQuaternion(local, now.rotation));
    };
    auto &mesh = cloth_.meshes[0];
    for (size_t i = 0; i < rest_.size(); ++i) {
        const auto p = Vector3Lerp(skin(rest_[i], upper_), skin(rest_[i], lower_), weights_[i]);
        std::memcpy(mesh.vertices + i * 3, &p, sizeof(Vector3));
    }
    for (int i = 0; i < mesh.vertexCount; i += 3) {
        Vector3 p[3];
        std::memcpy(p, mesh.vertices + i * 3, sizeof(p));
        const auto n = unit(Vector3CrossProduct(sub(p[2], p[0]), sub(p[1], p[0])));
        for (int k = 0; k < 3; ++k)
            std::memcpy(mesh.normals + (i + k) * 3, &n, sizeof(n));
    }
    UpdateMeshBuffer(mesh, 0, mesh.vertices, mesh.vertexCount * 3 * int(sizeof(float)), 0);
    UpdateMeshBuffer(mesh, 2, mesh.normals, mesh.vertexCount * 3 * int(sizeof(float)), 0);
    auto material = cloth_.materials[0];
    std::array<MaterialMap, 12> maps;
    std::copy_n(material.maps, maps.size(), maps.begin());
    material.maps = maps.data();
    material.shader = shader;
    maps[MATERIAL_MAP_METALNESS].texture = shadow;
    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling();
    DrawMesh(mesh, material, world);
    rlEnableBackfaceCulling();
}
} // namespace dw
