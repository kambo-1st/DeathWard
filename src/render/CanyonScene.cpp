#include "raylib.h"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "render/WesternScene.hpp"
#include "rlgl.h"
#include <cstdlib>
#include <map>
#include <stdexcept>

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
out float shore;
void main() {
    world = vertexPosition;
    normal = vertexNormal;
    uv = vertexTexCoord;
    tint = vertexColor.rgb;
    // Keep vertex alpha above the shared shadow caster's cutout threshold.
    shore = (vertexColor.a*255.-128.)/127.;
    gl_Position = mvp*vec4(world,1.);
}
)GLSL";
constexpr const char *TerrainFragment = R"GLSL(#version 330
in vec3 world;
in vec3 normal;
in vec2 uv;
in vec3 tint;
in float shore;
uniform sampler2D texture0;
uniform int terrainUnderlay;
uniform int terracedCliffs;
out vec4 finalColor;
void main() {
    vec3 n = normalize(normal);
    vec3 sun = missionSun;
    float shade = terrainUnderlay == 0 ? missionVisibility(world,n) : 1.;
    vec3 surface = texture(texture0,uv).rgb;
    // Local sandstone art direction only; lighting and legacy materials stay intact.
    if (terracedCliffs != 0 && world.y > .15) {
        float cap = smoothstep(.65,.96,n.y);
        surface = mix(surface,mix(vec3(.8,.46,.26),vec3(.82,.49,.26),cap),mix(.9,.75,cap));
    }
    if(terracedCliffs != 0 && world.y < .15) surface *= vec3(.96,.88,.85);
    surface *= tint;
    float floorBlend = (1.-smoothstep(.03,.45,world.y))*smoothstep(.6,.95,n.y);
    if (floorBlend > 0.) surface = mix(surface,groundSurface(surface,world),floorBlend);
    float gravel = groundNoise(world.xz*8.3);
    float bank = shore * (1.-smoothstep(.4,2.5,world.y));
    vec3 sediment = surface*vec3(.88,.91,.89);
    sediment *= .96 + .08*gravel;
    surface = mix(surface,sediment,bank);
    vec3 color = worldSurfaceColor(surface)*westernDaylight(n,sun,shade);
    if(terracedCliffs != 0 && world.y > .15 && n.y < .72)
        color += worldSurfaceColor(surface)*vec3(.14,.095,.045)*(1.-max(dot(n,sun),0.)*shade);
    finalColor=playerOcclusionSurface(world,vec4(color,1.));
}
)GLSL";
} // namespace
void WesternScene::clearTerrain() {
    water_.unload();
    for (auto &chunk : terrain_)
        UnloadMesh(chunk.mesh);
    terrain_.clear();
    terrainField_.reset();
    canyonAppearance_.reset();
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
    terrainField_ = arena.canyon;
    const auto overridePath = std::getenv("DEATHWARD_CANYON_CONFIG");
    const auto config = overridePath ? std::filesystem::path(overridePath)
                                     : assetDirectory().parent_path() / "visual/canyon.cfg";
    if (overridePath && !std::filesystem::is_regular_file(config))
        throw std::runtime_error("Missing canyon visual override: " + config.string());
    const auto parameters = CanyonVisualParameters::load(config);
    canyonAppearance_ = buildCanyonAppearance(arena, parameters);
    const auto &field = canyonAppearance_->surface;
    water_.prepare(field,arena.rails?&arena.rails->bounds:nullptr);
    const auto fragment = withPlayerOcclusion(
        MissionLighting::withShadows(GroundSurface::withDetail(TerrainFragment).c_str()).c_str());
    terrainShader_ = loadWorldShader(TerrainVertex, fragment.c_str());
    terrainMaterial_ = LoadMaterialDefault();
    terrainMaterial_.shader = terrainShader_;
    const int terraced = parameters.enabled ? 1 : 0;
    SetShaderValue(terrainShader_, GetShaderLocation(terrainShader_, "terracedCliffs"), &terraced,
                   SHADER_UNIFORM_INT);
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
    auto addTriangle = [&](const Triangle &triangle, bool rock, int x, int z) {
        const int key = rock ? sectionFor(mul(add(add(triangle[0], triangle[1]), triangle[2]), 1.f / 3))
                             : -1 - (z / 24) * ((field.width + 22) / 24) - x / 24;
        sections[key].push_back(triangle);
        terrainSections_.push_back(key);
    };
    if (parameters.enabled) {
        for (int z = 0; z + 1 < field.depth; ++z)
            for (int x = 0; x + 1 < field.width; ++x) {
                size_t cell = size_t(z * (field.width - 1) + x);
                for (size_t i = canyonAppearance_->cellOffsets[cell];
                     i < canyonAppearance_->cellOffsets[cell + 1]; ++i) {
                    const auto &face = canyonAppearance_->triangles[i];
                    addTriangle(face.vertices, face.rock, x, z);
                }
            }
    } else {
        for (int z = 0; z + 1 < field.depth; ++z)
            for (int x = 0; x + 1 < field.width; ++x) {
                auto a = field.vertex(x, z), b = field.vertex(x + 1, z), c = field.vertex(x, z + 1),
                     d = field.vertex(x + 1, z + 1);
                for (const auto &t : std::array<Triangle, 2>{Triangle{a, d, b}, Triangle{a, c, d}})
                    addTriangle(t, std::max({t[0].y, t[1].y, t[2].y}) > .001f, x, z);
            }
    }
    std::vector<unsigned char> shores(size_t(field.width * field.depth), 0);
    if (!field.river.empty())
        for (int z = 0; z < field.depth; ++z)
            for (int x = 0; x < field.width; ++x) {
                const auto sample = field.riverSample(field.vertex(x, z));
                const float weight = std::clamp(1.f - (sample.distance - sample.width) / 4.f, 0.f, 1.f);
                shores[size_t(z * field.width + x)] = static_cast<unsigned char>(weight * 255);
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
            const float variation = !parameters.enabled ?
                (rock&&!cap?.96f+.04f*std::sin(dot(add(add(a,b),c),{1.17f,.73f,2.31f})):1.f):
                rock&&cap?.94f+.06f*std::sin(dot(normal,{9.1f,0,12.7f})):
                rock?.96f+.04f*std::sin(dot(normal,{1.17f,.73f,2.31f})):1.f;
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
                const int ix = std::clamp(int(std::lround((p.x - field.x) / field.step)), 0, field.width - 1);
                const int iz = std::clamp(int(std::lround((p.z - field.z) / field.step)), 0, field.depth - 1);
                mesh.colors[4 * vertex + 3] = 128 + shores[size_t(iz * field.width + ix)] / 2;
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
    if (field.river.empty()) {
        terrainBase_ = makeMesh({Triangle{a, d, b}, Triangle{a, c, d}});
    } else {
        // The old flat underlay would cap the riverbed. Keep it flat beneath
        // mesas, but let it follow the channel below the visible terrain.
        std::vector<Triangle> base;
        for (int z = 0; z + 1 < field.depth; ++z) {
            int start = 0;
            auto flat = [&](int end) {
                if (end <= start)
                    return;
                const Vector3 v{field.x + start * field.step, -.2f, field.z + z * field.step},
                    w{field.x + end * field.step, -.2f, v.z}, u{v.x, -.2f, v.z + field.step},
                    t{w.x, -.2f, u.z};
                base.push_back({v, t, w});
                base.push_back({v, u, t});
            };
            for (int x = 0; x + 1 < field.width; ++x) {
                auto v = field.vertex(x, z), w = field.vertex(x + 1, z), u = field.vertex(x, z + 1),
                     t = field.vertex(x + 1, z + 1);
                if (std::min({v.y, w.y, u.y, t.y}) >= -.15f)
                    continue;
                flat(x);
                for (auto p : {&v, &w, &u, &t})
                    p->y = std::min(-.2f, p->y - .05f);
                base.push_back({v, t, w});
                base.push_back({v, u, t});
                start = x + 1;
            }
            flat(field.width - 1);
        }
        terrainBase_ = makeMesh(base);
    }
    if (!loaded())
        return;
    if (parameters.enabled) {
        for (const auto &d : canyonAppearance_->decorations) {
            if (int(placements_.size()) >= parameters.maxDecorations)
                break;
            WesternAsset asset = d.kind == CanyonDecorationKind::Tree     ? WesternAsset::DesertTree
                                 : d.kind == CanyonDecorationKind::Rock   ? WesternAsset::RockA
                                 : d.kind == CanyonDecorationKind::Cactus ? WesternAsset::CactusA
                                 : d.kind == CanyonDecorationKind::Shrub  ? WesternAsset::GreenBush
                                                                          : WesternAsset::GrassB;
            if (d.kind == CanyonDecorationKind::Shrub && int(d.yaw * 100) % 4 != 0)
                asset = WesternAsset::DesertGrass;
            if (d.kind == CanyonDecorationKind::Cactus) {
                int variant = int(d.yaw * 100) % 3;
                asset = d.zone == CanyonZone::CliffBase || variant == 2 ? WesternAsset::FlowerCactus
                        : variant == 1                                  ? WesternAsset::CactusB
                                                                        : WesternAsset::CactusA;
            }
            if (d.kind == CanyonDecorationKind::Rock)
                asset = int(d.yaw * 100) % 7 == 0 ? WesternAsset::StickA
                        : int(d.yaw * 100) % 2    ? WesternAsset::RockA
                                                  : WesternAsset::RockB;
            const auto native = sub(assetBounds(asset).max, assetBounds(asset).min);
            const float scale = std::min(d.span / std::max(native.x, native.z), d.height / native.y);
            const float c = std::abs(std::cos(d.yaw)), s = std::abs(std::sin(d.yaw));
            Vector3 size{scale * (native.x * c + native.z * s), scale * native.y,
                         scale * (native.z * c + native.x * s)};
            const bool cactus = d.kind == CanyonDecorationKind::Cactus;
            const float supportRadius = d.kind == CanyonDecorationKind::Tree
                                            ? .45f
                                            : std::max(size.x, size.z) * .5f + (cactus ? .35f : .15f);
            if (!canyonAppearance_->supports(d.position, supportRadius, cactus ? .1f : .18f))
                continue;
            float base = d.position.y;
            if (cactus)
                for (float dx = -supportRadius; dx <= supportRadius + .001f; dx += .12f)
                    for (float dz = -supportRadius; dz <= supportRadius + .001f; dz += .12f)
                        base = std::min(
                            base, canyonAppearance_->height(d.position.x + dx, d.position.z + dz) - .025f);
            placements_.push_back({asset,
                                   {{d.position.x - size.x / 2, base, d.position.z - size.z / 2},
                                    {d.position.x + size.x / 2, base + size.y, d.position.z + size.z / 2}},
                                   d.yaw,
                                   true,
                                   d.room,
                                   scale,
                                   d.extraVegetation ? 101 : 0});
            if (d.kind == CanyonDecorationKind::Rock && asset != WesternAsset::StickA) {
                for (int j = 0; j < 2 && int(placements_.size()) < parameters.maxDecorations; ++j) {
                    float angle = d.yaw + float(j) * 2.7f;
                    auto at = add(d.position,
                                  {std::cos(angle) * d.span * .28f, 0, std::sin(angle) * d.span * .28f});
                    auto tiny = mul(size, .35f);
                    float radius = std::max(tiny.x, tiny.z) * .5f + .04f;
                    if (!canyonAppearance_->supports(at, radius, .15f))
                        continue;
                    float base = canyonAppearance_->height(at.x, at.z) - .02f;
                    placements_.push_back({asset,
                                           {{at.x - tiny.x / 2, base, at.z - tiny.z / 2},
                                            {at.x + tiny.x / 2, base + tiny.y, at.z + tiny.z / 2}},
                                           d.yaw,
                                           true,
                                           d.room,
                                           scale * .35f,
                                           0});
                }
            }
        }
        std::array<int, 4> zones{};
        std::array<int, 5> kinds{};
        for (const auto &d : canyonAppearance_->decorations) {
            ++zones[size_t(d.zone)];
            ++kinds[size_t(d.kind)];
        }
        TraceLog(LOG_INFO,
                 "CANYON_VISUAL: grid=%dx%d triangles=%d chunks=%d candidates=%d props=%d floor=%d base=%d "
                 "terrace=%d plateau=%d rocks=%d grass=%d shrub=%d cactus=%d trees=%d enabled=1",
                 field.width, field.depth, int(canyonAppearance_->triangles.size()), int(terrain_.size()),
                 int(canyonAppearance_->decorations.size()), int(placements_.size()), zones[0], zones[1],
                 zones[2], zones[3], kinds[0], kinds[1], kinds[2], kinds[3], kinds[4]);
        return;
    }
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
        const auto &field = canyonAppearance_ ? canyonAppearance_->surface : *terrainField_;
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
                    const bool extruded = canyonAppearance_ && canyonAppearance_->parameters.enabled;
                    size_t cell = size_t(z * (field.width - 1) + x);
                    size_t begin = extruded ? canyonAppearance_->cellOffsets[cell] : cell * 2;
                    size_t end = extruded ? canyonAppearance_->cellOffsets[cell + 1] : begin + 2;
                    for (size_t i = begin; i < end; ++i) {
                        int index = terrainSections_[i];
                        if (index < 0 || terrain_[size_t(index)].faded)
                            continue;
                        std::array<Vector3, 3> t;
                        if (extruded)
                            t = canyonAppearance_->triangles[i].vertices;
                        else {
                            auto a = field.vertex(x, z), b = field.vertex(x + 1, z),
                                 c = field.vertex(x, z + 1), d = field.vertex(x + 1, z + 1);
                            t = i == begin ? std::array<Vector3, 3>{a, d, b}
                                           : std::array<Vector3, 3>{a, c, d};
                        }
                        const auto hit = GetRayCollisionTriangle(ray, t[0], t[1], t[2]);
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
