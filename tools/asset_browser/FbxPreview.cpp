#include "FbxPreview.hpp"
#include "AssetInventory.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
namespace dw::assetBrowser {
void FbxPreview::clear() {
    for (auto &p : parts) {
        UnloadMesh(p.mesh);
        MemFree(p.material.maps);
    }
    parts.clear();
    for (auto t : textures)
        UnloadTexture(t);
    textures.clear();
    if (scene)
        ufbx_free_scene(scene);
    scene = nullptr;
    triangleCount = 0;
    animations.clear();
    notes.clear();
}
void FbxPreview::updatePart(Part &part, const ufbx_scene *s, bool upload) {
    auto *node = s->nodes.data[part.node];
    auto *mesh = node->mesh;
    const auto *positions = mesh->skinned_position.exists ? &mesh->skinned_position : &mesh->vertex_position;
    const auto *normals = mesh->skinned_normal.exists ? &mesh->skinned_normal : &mesh->vertex_normal;
    const auto normalMatrix = ufbx_matrix_for_normals(&node->geometry_to_world);
    for (size_t i = 0; i < part.corners.size(); ++i) {
        const auto index = part.corners[i];
        auto p = ufbx_get_vertex_vec3(positions, index);
        auto n = normals->exists ? ufbx_get_vertex_vec3(normals, index) : ufbx_vec3{0, 1, 0};
        if (!mesh->skinned_position.exists || mesh->skinned_is_local) {
            p = ufbx_transform_position(&node->geometry_to_world, p);
            n = ufbx_transform_direction(&normalMatrix, n);
        }
        const double length = std::sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
        if (length > 0) {
            n.x /= length;
            n.y /= length;
            n.z /= length;
        }
        part.mesh.vertices[3 * i] = float(p.x);
        part.mesh.vertices[3 * i + 1] = float(p.y);
        part.mesh.vertices[3 * i + 2] = float(p.z);
        part.mesh.normals[3 * i] = float(n.x);
        part.mesh.normals[3 * i + 1] = float(n.y);
        part.mesh.normals[3 * i + 2] = float(n.z);
        if (mesh->vertex_uv.exists) {
            auto uv = ufbx_get_vertex_vec2(&mesh->vertex_uv, index);
            part.mesh.texcoords[2 * i] = float(uv.x);
            part.mesh.texcoords[2 * i + 1] = 1 - float(uv.y);
        }
    }
    if (upload) {
        UpdateMeshBuffer(part.mesh, 0, part.mesh.vertices, part.mesh.vertexCount * 3 * sizeof(float), 0);
        UpdateMeshBuffer(part.mesh, 2, part.mesh.normals, part.mesh.vertexCount * 3 * sizeof(float), 0);
    }
}
bool FbxPreview::load(const std::filesystem::path &path,
                      const std::unordered_map<std::string, std::filesystem::path> &images) {
    clear();
    ufbx_load_opts opts{};
    opts.generate_missing_normals = true;
    opts.evaluate_skinning = true;
    opts.target_axes = ufbx_axes_right_handed_y_up;
    opts.target_unit_meters = 1;
    ufbx_error error{};
    scene = ufbx_load_file(path.string().c_str(), &opts, &error);
    if (!scene) {
        char text[1024];
        ufbx_format_error(text, sizeof(text), &error);
        notes = text;
        return false;
    }
    std::map<const ufbx_material *, Material> materials;
    for (auto *node : scene->nodes) {
        auto *mesh = node->mesh;
        if (!mesh || !mesh->num_triangles)
            continue;
        std::map<uint32_t, std::vector<uint32_t>> grouped;
        std::vector<uint32_t> triangle(mesh->max_face_triangles * 3);
        for (size_t f = 0; f < mesh->faces.count; ++f) {
            auto face = mesh->faces.data[f];
            const size_t count = ufbx_triangulate_face(triangle.data(), triangle.size(), mesh, face);
            const uint32_t mat = mesh->face_material.count ? mesh->face_material.data[f] : 0;
            auto &indices = grouped[mat];
            indices.insert(indices.end(), triangle.begin(), triangle.begin() + count * 3);
        }
        for (auto &[materialId, indices] : grouped) {
            const ufbx_material *source =
                materialId < node->materials.count ? node->materials.data[materialId] : nullptr;
            Material base = LoadMaterialDefault();
            if (source) {
                if (source->fbx.diffuse_color.has_value) {
                    auto color = source->fbx.diffuse_color.value_vec3;
                    base.maps[MATERIAL_MAP_ALBEDO].color = {
                        static_cast<unsigned char>(std::clamp(color.x, 0., 1.) * 255),
                        static_cast<unsigned char>(std::clamp(color.y, 0., 1.) * 255),
                        static_cast<unsigned char>(std::clamp(color.z, 0., 1.) * 255), 255};
                }
                auto *tex = source->fbx.diffuse_color.texture;
                if (tex && source->fbx.diffuse_color.texture_enabled) {
                    std::string textureName(tex->filename.data, tex->filename.length);
                    std::replace(textureName.begin(), textureName.end(), '\\', '/');
                    const std::filesystem::path filename(textureName);
                    auto resolved = path.parent_path() / filename;
                    if (!std::filesystem::is_regular_file(resolved)) {
                        auto found = images.find(lower(filename.filename().string()));
                        if (found != images.end())
                            resolved = found->second;
                    }
                    if (std::filesystem::is_regular_file(resolved)) {
                        auto texture = LoadTexture(resolved.string().c_str());
                        if (texture.id) {
                            textures.push_back(texture);
                            base.maps[MATERIAL_MAP_ALBEDO].texture = texture;
                        }
                    } else if (tex->content.size && tex->content.size < 64 * 1024 * 1024) {
                        auto image = LoadImageFromMemory(
                            filename.extension().string().c_str(),
                            static_cast<const unsigned char *>(tex->content.data), int(tex->content.size));
                        if (image.data) {
                            auto texture = LoadTextureFromImage(image);
                            UnloadImage(image);
                            if (texture.id) {
                                textures.push_back(texture);
                                base.maps[MATERIAL_MAP_ALBEDO].texture = texture;
                            }
                        }
                    }
                }
            }
            for (size_t start = 0; start < indices.size(); start += 60000) {
                const size_t count = std::min<size_t>(60000, indices.size() - start);
                Part part;
                part.node = node->typed_id;
                part.corners.assign(indices.begin() + start, indices.begin() + start + count);
                part.material = LoadMaterialDefault();
                std::copy(base.maps, base.maps + MATERIAL_MAP_BRDF + 1, part.material.maps);
                part.mesh.vertexCount = int(count);
                part.mesh.triangleCount = int(count / 3);
                part.mesh.vertices = static_cast<float *>(MemAlloc(count * 3 * sizeof(float)));
                part.mesh.normals = static_cast<float *>(MemAlloc(count * 3 * sizeof(float)));
                part.mesh.texcoords = static_cast<float *>(MemAlloc(count * 2 * sizeof(float)));
                std::fill(part.mesh.texcoords, part.mesh.texcoords + count * 2, 0.f);
                updatePart(part, scene, false);
                UploadMesh(&part.mesh, true);
                triangleCount += part.mesh.triangleCount;
                parts.push_back(std::move(part));
            }
            MemFree(base.maps);
        }
    }
    if (parts.empty()) {
        notes = "FBX contains no triangle geometry. Nodes: " + std::to_string(scene->nodes.count);
        return false;
    }
    bounds = {{std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
               std::numeric_limits<float>::max()},
              {-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(),
               -std::numeric_limits<float>::max()}};
    for (const auto &part : parts) {
        auto b = GetMeshBoundingBox(part.mesh);
        bounds.min = Vector3Min(bounds.min, b.min);
        bounds.max = Vector3Max(bounds.max, b.max);
    }
    for (auto *anim : scene->anim_stacks)
        animations.emplace_back(anim->name.data, anim->name.length);
    notes = std::to_string(parts.size()) + " mesh sections / " + std::to_string(triangleCount) +
            " triangles / " + std::to_string(scene->nodes.count) + " nodes";
    return true;
}
void FbxPreview::animate(size_t clip, double time) {
    if (!scene || clip >= scene->anim_stacks.count)
        return;
    auto *stack = scene->anim_stacks.data[clip];
    const double length = stack->time_end - stack->time_begin;
    ufbx_evaluate_opts opts{};
    opts.evaluate_skinning = true;
    ufbx_error error{};
    auto *evaluated = ufbx_evaluate_scene(
        scene, stack->anim, stack->time_begin + (length > 0 ? std::fmod(time, length) : 0), &opts, &error);
    if (evaluated) {
        for (auto &part : parts)
            updatePart(part, evaluated, true);
        if (!parts.empty()) {
            bounds = GetMeshBoundingBox(parts.front().mesh);
            for (size_t i = 1; i < parts.size(); ++i) {
                const auto b = GetMeshBoundingBox(parts[i].mesh);
                bounds.min = Vector3Min(bounds.min, b.min);
                bounds.max = Vector3Max(bounds.max, b.max);
            }
        }
        ufbx_free_scene(evaluated);
    }
}
void FbxPreview::draw(Shader shader, bool wire, int section) const {
    rlDisableBackfaceCulling();
    if (wire)
        rlEnableWireMode();
    for (size_t i = 0; i < parts.size(); ++i) {
        if (section >= 0 && int(i) != section)
            continue;
        const auto &p = parts[i];
        auto material = p.material;
        material.shader = shader;
        DrawMesh(p.mesh, material, MatrixIdentity());
    }
    if (wire)
        rlDisableWireMode();
    rlEnableBackfaceCulling();
}
} // namespace dw::assetBrowser
