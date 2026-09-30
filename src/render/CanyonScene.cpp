#include "raylib.h"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "render/WesternScene.hpp"
#include "rlgl.h"
#include <map>

namespace dw {
namespace {
constexpr const char *TerrainVertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec4 vertexColor;
uniform mat4 mvp;
out vec3 world;
out vec3 normal;
out vec2 uv;
out vec3 tint;
void main() {
    world = vertexPosition;
    normal = vertexNormal;
    uv = vertexTexCoord;
    tint = vertexColor.rgb;
    gl_Position = mvp*vec4(world,1.);
}
)GLSL";
constexpr const char *TerrainFragment = R"GLSL(#version 330
in vec3 world;
in vec3 normal;
in vec2 uv;
in vec3 tint;
uniform sampler2D texture0;
uniform int terrainUnderlay;
out vec4 finalColor;
void main() {
    vec3 n = normalize(normal);
    vec3 sun = missionSun;
    float shade = terrainUnderlay == 0 ? missionVisibility(world,n) : 1.;
    vec3 surface = texture(texture0,uv).rgb*tint;
    float floorBlend = (1.-smoothstep(.03,.45,world.y))*smoothstep(.6,.95,n.y);
    if (floorBlend > 0.) surface = mix(surface,groundSurface(surface,world),floorBlend);
    vec3 color = surface*westernDaylight(n,sun,shade);
    finalColor=playerOcclusionSurface(world,vec4(color,1.));
}
)GLSL";
} // namespace
void WesternScene::clearTerrain() {
    for (auto &chunk : terrain_)
        UnloadMesh(chunk.mesh);
    terrain_.clear();
    terrainField_.reset();
    terrainSections_.clear();
    if (terrainBase_.vaoId)
        UnloadMesh(terrainBase_);
    terrainBase_ = {};
    if (terrainShader_.id)
        UnloadShader(terrainShader_);
    // The atlas belongs to model_; this material only owns its map array.
    if (terrainMaterial_.maps)
        MemFree(terrainMaterial_.maps);
    terrainShader_ = {};
    terrainMaterial_ = {};
}
void WesternScene::generateCanyon(const Arena &arena) {
    if (!arena.canyon)
        return;
    const auto &field = *arena.canyon;
    terrainField_ = arena.canyon;
    const auto fragment = withPlayerOcclusion(
        MissionLighting::withShadows(GroundSurface::withDetail(TerrainFragment).c_str()).c_str());
    terrainShader_ = loadWorldShader(TerrainVertex, fragment.c_str());
    terrainMaterial_ = LoadMaterialDefault();
    terrainMaterial_.shader = terrainShader_;
    Vector2 sandUv{}, wallUv{}, capUv{};
    if (loaded()) {
        const int floorMesh = assets_[size_t(WesternAsset::Floor)].firstMesh;
        const auto &mesh = model_.meshes[floorMesh];
        sandUv = {mesh.texcoords[0], mesh.texcoords[1]};
        terrainMaterial_.maps[MATERIAL_MAP_ALBEDO].texture =
            model_.materials[model_.meshMaterial[floorMesh]].maps[MATERIAL_MAP_ALBEDO].texture;
        const auto &rock = model_.meshes[assets_[size_t(WesternAsset::CliffWall)].firstMesh];
        // Use the original cliff's two atlas swatches: brown faces and sandy caps.
        // Sampling the most vertical/upward normals avoids bevels between materials.
        float wallScore = 2, capScore = -2;
        for (int i = 0; i < rock.vertexCount; ++i) {
            const float up = rock.normals[i * 3 + 1];
            if (std::abs(up) < wallScore) {
                wallScore = std::abs(up);
                wallUv = {rock.texcoords[i * 2], rock.texcoords[i * 2 + 1]};
            }
            if (up > capScore) {
                capScore = up;
                capUv = {rock.texcoords[i * 2], rock.texcoords[i * 2 + 1]};
            }
        }
    }
    terrainShader_.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(terrainShader_, "shadowMap");
    terrainShader_.locs[SHADER_LOC_MAP_OCCLUSION] = GetShaderLocation(terrainShader_, "groundSoil");
    using Triangle = std::array<Vector3, 3>;
    std::vector<Box> outcrops;
    for (const auto &room : arena.rooms)
        outcrops.insert(outcrops.end(), room.obstacles.begin(), room.obstacles.end());
    std::map<int, std::vector<Triangle>> sections;
    terrainSections_.reserve(size_t((field.width - 1) * (field.depth - 1) * 2));
    auto sectionFor = [&](Vector3 center) {
        for (size_t i = 0; i < outcrops.size(); ++i) {
            const auto &box = outcrops[i];
            if (center.x >= box.min.x - field.step && center.x <= box.max.x + field.step &&
                center.z >= box.min.z - field.step && center.z <= box.max.z + field.step)
                return int(i);
        }
        size_t closest = 0;
        float best = 1e9f;
        for (size_t i = 0; i < arena.rooms.size(); ++i) {
            const auto delta = sub(center, arena.rooms[i].center);
            const float range = delta.x * delta.x + delta.z * delta.z;
            if (range < best) {
                closest = i;
                best = range;
            }
        }
        const auto delta = sub(center, arena.rooms[closest].center);
        const int side = std::clamp(int((std::atan2(delta.z, delta.x) + Pi) / (Pi / 4)), 0, 7);
        return int(outcrops.size()) + int(closest) * 8 + side;
    };
    for (int z = 0; z < field.depth - 1; ++z)
        for (int x = 0; x < field.width - 1; ++x) {
            const auto a = field.vertex(x, z), b = field.vertex(x + 1, z), c = field.vertex(x, z + 1),
                       d = field.vertex(x + 1, z + 1);
            for (const auto triangle : {Triangle{a, d, b}, Triangle{a, c, d}}) {
                // Include the low foot of the wall so fading does not leave opaque triangular stubs.
                const bool rock = std::max({triangle[0].y, triangle[1].y, triangle[2].y}) > .001f;
                // Outcrops remain complete objects; each basin rim has eight wall sections.
                // Floor chunks are independent so fading rock leaves playable surfaces opaque.
                const int key =
                    rock ? sectionFor(mul(add(add(triangle[0], triangle[1]), triangle[2]), 1.f / 3))
                         : -1 - (z / 24) * ((field.width + 22) / 24) - x / 24;
                sections[key].push_back(triangle);
                terrainSections_.push_back(key);
            }
        }
    auto makeMesh = [&](const std::vector<Triangle> &triangles) {
        Mesh mesh{};
        mesh.triangleCount = int(triangles.size());
        mesh.vertexCount = mesh.triangleCount * 3;
        mesh.vertices = static_cast<float *>(MemAlloc(unsigned(mesh.vertexCount * 3 * sizeof(float))));
        mesh.normals = static_cast<float *>(MemAlloc(unsigned(mesh.vertexCount * 3 * sizeof(float))));
        mesh.texcoords = static_cast<float *>(MemAlloc(unsigned(mesh.vertexCount * 2 * sizeof(float))));
        mesh.colors = static_cast<unsigned char *>(MemAlloc(unsigned(mesh.vertexCount * 4)));
        int vertex = 0;
        for (const auto &triangle : triangles) {
            const auto a = triangle[0], b = triangle[1], c = triangle[2];
            const auto normal = Vector3Normalize(Vector3CrossProduct(sub(b, a), sub(c, a)));
            const bool rock = std::max({a.y, b.y, c.y}) > .15f;
            const bool cap = normal.y > .72f;
            const auto uv = rock ? (cap ? capUv : wallUv) : sandUv;
            const Color tint = WHITE;
            const float variation =
                rock && !cap ? .96f + .04f * std::sin(dot(add(add(a, b), c), {1.17f, .73f, 2.31f})) : 1.f;
            for (auto p : triangle) {
                mesh.vertices[3 * vertex] = p.x;
                mesh.vertices[3 * vertex + 1] = p.y;
                mesh.vertices[3 * vertex + 2] = p.z;
                mesh.normals[3 * vertex] = normal.x;
                mesh.normals[3 * vertex + 1] = normal.y;
                mesh.normals[3 * vertex + 2] = normal.z;
                mesh.texcoords[2 * vertex] = uv.x;
                mesh.texcoords[2 * vertex + 1] = uv.y;
                mesh.colors[4 * vertex] = static_cast<unsigned char>(tint.r * variation);
                mesh.colors[4 * vertex + 1] = static_cast<unsigned char>(tint.g * variation);
                mesh.colors[4 * vertex + 2] = static_cast<unsigned char>(tint.b * variation);
                mesh.colors[4 * vertex + 3] = 255;
                ++vertex;
            }
        }
        UploadMesh(&mesh, false);
        return mesh;
    };
    std::map<int, int> sectionIndices;
    for (const auto &[key, triangles] : sections) {
        TerrainChunk chunk;
        chunk.mesh = makeMesh(triangles);
        const auto bounds = GetMeshBoundingBox(chunk.mesh);
        chunk.bounds = {bounds.min, bounds.max};
        chunk.rock = key >= 0;
        if (chunk.rock)
            for (const auto &triangle : triangles) {
                // Intersect the actual terrain with its walkable-height contour. This follows
                // irregular basin edges and outcrops without drawing mesh or section seams.
                std::array<Vector3, 2> edge{};
                int crossings = 0;
                for (int i = 0; i < 3; ++i) {
                    const auto a = triangle[size_t(i)], b = triangle[size_t((i + 1) % 3)];
                    constexpr float level = CanyonTerrain::WalkableHeight;
                    if ((a.y > level) != (b.y > level))
                        edge[size_t(crossings++)] =
                            add(add(a, mul(sub(b, a), (level - a.y) / (b.y - a.y))), {0, .025f, 0});
                }
                if (crossings == 2 && distance(edge[0], edge[1]) > .001f)
                    chunk.floorOutline.push_back(edge);
            }
        sectionIndices[key] = int(terrain_.size());
        terrain_.push_back(std::move(chunk));
    }
    for (auto &key : terrainSections_)
        key = key < 0 ? -1 : sectionIndices.at(key);
    // Sand remains visible through faded mesas; the original floor and physics stay intact.
    const Vector3 a{field.x, -.05f, field.z}, b{field.x + (field.width - 1) * field.step, -.05f, field.z},
        c{field.x, -.05f, field.z + (field.depth - 1) * field.step}, d{b.x, -.05f, c.z};
    terrainBase_ = makeMesh({Triangle{a, d, b}, Triangle{a, c, d}});
    if (!loaded())
        return;
    Random rng(arena.visualSeed ^ 0x43414e594f4e4152ULL);
    auto cactusBase = [&](Vector3 p, Vector3 size) -> std::optional<float> {
        const float halfX = std::max(.8f, size.x / 2 + .5f);
        const float halfZ = std::max(.8f, size.z / 2 + .5f);
        if (p.x - halfX < field.x || p.z - halfZ < field.z ||
            p.x + halfX > field.x + (field.width - 1) * field.step ||
            p.z + halfZ > field.z + (field.depth - 1) * field.step)
            return std::nullopt;
        float low = 100, high = -100;
        // Check the whole footprint plus a margin, not just the stem. This
        // rejects sloping shoulders and plants perched over a cliff edge.
        for (int x = 0; x <= 4; ++x)
            for (int z = 0; z <= 4; ++z) {
                const float h = field.height(p.x - halfX + halfX * x / 2, p.z - halfZ + halfZ * z / 2);
                low = std::min(low, h);
                high = std::max(high, h);
            }
        if (high - low > .1f)
            return std::nullopt;
        return low - .04f;
    };
    // Native proportions: small debris along the banks, sparse cacti on terraces.
    for (const auto &room : arena.rooms)
        for (int n = 0; n < 90; ++n) {
            const Vector3 p{rng.real(room.bounds.min.x - 5, room.bounds.max.x + 5), 0,
                            rng.real(room.bounds.min.z - 5, room.bounds.max.z + 5)};
            const float h = field.height(p.x, p.z);
            const bool cactus = n < 6 && h > 5;
            if (!cactus && (h < .15f || h > 1.0f))
                continue;
            const auto asset = cactus ? (rng.bounded(2) ? WesternAsset::CactusA : WesternAsset::CactusB)
                                      : WesternAsset::RockA;
            const float scale = cactus ? rng.real(.8f, 1.4f) : rng.real(.3f, .8f);
            auto size = mul(sub(assetBounds(asset).max, assetBounds(asset).min), scale);
            const float yaw = float(rng.bounded(4)) * Pi / 2;
            if (std::abs(std::sin(yaw)) > .5f)
                std::swap(size.x, size.z);
            float base = h - .07f;
            if (cactus) {
                const auto supported = cactusBase(p, size);
                if (!supported)
                    continue;
                base = *supported;
            }
            placements_.push_back({asset,
                                   {{p.x - size.x / 2, base, p.z - size.z / 2},
                                    {p.x + size.x / 2, base + size.y, p.z + size.z / 2}},
                                   yaw,
                                   true});
        }
    // More vegetation adds cacti around the same flat terraces. It never changes
    // bank rocks, the terrain or the baseline random stream.
    Random extra(arena.visualSeed ^ 0x6578747261636163ULL);
    const size_t baseline = placements_.size();
    for (size_t i = 0; i < baseline; ++i) {
        const auto original = placements_[i];
        if (!isVegetation(original.asset))
            continue;
        for (int attempt = 0; attempt < 20; ++attempt) {
            auto p = mul(add(original.bounds.min, original.bounds.max), .5f);
            p.x += extra.real(-4, 4);
            p.z += extra.real(-4, 4);
            const auto size = sub(original.bounds.max, original.bounds.min);
            const Box box{{p.x - size.x / 2, 0, p.z - size.z / 2}, {p.x + size.x / 2, 0, p.z + size.z / 2}};
            if (field.height(p.x, p.z) < 5)
                continue;
            const auto base = cactusBase(p, size);
            if (!base || std::any_of(placements_.begin(), placements_.end(), [&](const auto &other) {
                    return box.min.x < other.bounds.max.x + .5f && box.max.x > other.bounds.min.x - .5f &&
                           box.min.z < other.bounds.max.z + .5f && box.max.z > other.bounds.min.z - .5f;
                }))
                continue;
            auto placed = original;
            placed.bounds = {{box.min.x, *base, box.min.z}, {box.max.x, *base + size.y, box.max.z}};
            placed.vegetationLevel = 101;
            placements_.push_back(placed);
            break;
        }
    }
}
void WesternScene::updateTerrainOcclusion() {
    if (terrain_.empty())
        return;
    for (auto &section : terrain_)
        section.faded = false;
    if (occlusion_.enabled) {
        const auto &field = *terrainField_;
        // Test only height-field cells between the camera and the body. This avoids raycasting
        // every triangle in large mesa meshes, while using the exact rendered triangles.
        for (auto target : occlusion_.targets()) {
            const auto ray = occlusion_.rayTo(target);
            const float reach = distance(ray.position, target) - .15f;
            const int left =
                std::clamp(int(std::floor((std::min(ray.position.x, target.x) - field.x) / field.step)), 0,
                           field.width - 2);
            const int right =
                std::clamp(int(std::floor((std::max(ray.position.x, target.x) - field.x) / field.step)), 0,
                           field.width - 2);
            const int top =
                std::clamp(int(std::floor((std::min(ray.position.z, target.z) - field.z) / field.step)), 0,
                           field.depth - 2);
            const int bottom =
                std::clamp(int(std::floor((std::max(ray.position.z, target.z) - field.z) / field.step)), 0,
                           field.depth - 2);
            for (int z = top; z <= bottom; ++z)
                for (int x = left; x <= right; ++x) {
                    const auto a = field.vertex(x, z), b = field.vertex(x + 1, z), c = field.vertex(x, z + 1),
                               d = field.vertex(x + 1, z + 1);
                    for (int triangle = 0; triangle < 2; ++triangle) {
                        const int index =
                            terrainSections_[size_t((z * (field.width - 1) + x) * 2 + triangle)];
                        if (index < 0 || terrain_[size_t(index)].faded)
                            continue;
                        const auto hit = triangle == 0 ? GetRayCollisionTriangle(ray, a, d, b)
                                                       : GetRayCollisionTriangle(ray, a, c, d);
                        if (hit.hit && hit.distance > .05f && hit.distance < reach &&
                            hit.point.y > occlusion_.player.y - .85f)
                            terrain_[size_t(index)].faded = true;
                    }
                }
        }
    }
}
void WesternScene::drawTerrain(Vector3 focus) {
    if (terrain_.empty())
        return;
    lighting_.bind(terrainShader_);
    ground_.bind(terrainShader_);
    occlusion_.bind(terrainShader_, false);
    // The buried base must not self-shadow against the translucent rock above it.
    int underlay = 1;
    SetShaderValue(terrainShader_, GetShaderLocation(terrainShader_, "terrainUnderlay"), &underlay,
                   SHADER_UNIFORM_INT);
    lighting_.draw(terrainBase_, terrainMaterial_, MatrixIdentity());
    underlay = 0;
    SetShaderValue(terrainShader_, GetShaderLocation(terrainShader_, "terrainUnderlay"), &underlay,
                   SHADER_UNIFORM_INT);
    for (auto &chunk : terrain_) {
        const Vector3 closest{std::clamp(focus.x, chunk.bounds.min.x, chunk.bounds.max.x), focus.y,
                              std::clamp(focus.z, chunk.bounds.min.z, chunk.bounds.max.z)};
        if (!chunk.faded && distance(closest, focus) < 110)
            lighting_.draw(chunk.mesh, terrainMaterial_, MatrixIdentity());
    }
}
void WesternScene::drawTerrainOutlines() {
    if (terrain_.empty())
        return;
    // Draw after faded rock so the ground boundary remains legible through its surface.
    // Keep depth testing: opaque scenery and the character still cover the line normally.
    const float lineWidth = rlGetLineWidth();
    rlDrawRenderBatchActive();
    rlSetLineWidth(2);
    for (const auto &section : terrain_)
        if (section.faded)
            for (const auto &edge : section.floorOutline)
                DrawLine3D(edge[0], edge[1], {106, 112, 117, 220});
    rlDrawRenderBatchActive();
    rlSetLineWidth(lineWidth);
}
} // namespace dw
