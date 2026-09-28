#include "render/WesternScene.hpp"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "rlgl.h"
#include <fstream>
#include <set>

namespace dw {
namespace {
constexpr std::array<const char *, size_t(WesternAsset::Count)> Names{
    "crate",      "barrel",       "sacks",     "woodpile", "lantern",  "coffin",      "cart",
    "fence",      "saloon",       "jail",      "church",   "station",  "water_tower", "well",
    "rail",       "ground",       "rock_a",    "rock_b",   "cactus_a", "cactus_b",    "floor",
    "cliff_wall", "cliff_pillar", "cliff_cap", "sandstone"};
constexpr const char *VertexShader = R"GLSL(#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in mat4 instanceTransform;
uniform mat4 mvp;
out vec2 uv;
out vec3 normal;
out vec3 world;
void main() {
    uv = vertexTexCoord;
    normal = normalize(transpose(inverse(mat3(instanceTransform))) * vertexNormal);
    vec4 p = instanceTransform * vec4(vertexPosition, 1.0);
    world = p.xyz;
    gl_Position = mvp * p;
}
)GLSL";
constexpr const char *FragmentShader = R"GLSL(#version 330
in vec2 uv;
in vec3 normal;
in vec3 world;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 sceneryTint;
out vec4 finalColor;
void main() {
    vec4 surface = texture(texture0, uv) * colDiffuse;
    if (surface.a < 0.02) discard;
    surface = playerOcclusionSurface(world,surface);
    vec3 litNormal = gl_FrontFacing ? normalize(normal) : -normalize(normal);
    float sunlight = max(dot(litNormal, normalize(vec3(-0.45, 0.85, 0.3))), 0.0);
    finalColor = vec4(surface.rgb * sceneryTint * (0.62 + 0.43 * sunlight), surface.a);
}
)GLSL";
bool overlaps(Box a, Box b, float margin = 0) {
    return a.min.x < b.max.x + margin && a.max.x > b.min.x - margin && a.min.z < b.max.z + margin &&
           a.max.z > b.min.z - margin;
}
bool finite(Vector3 p) {
    return std::isfinite(p.x) && std::isfinite(p.y) && std::isfinite(p.z);
}
} // namespace

std::filesystem::path WesternScene::assetDirectory() {
    const auto packaged = std::filesystem::path(GetApplicationDirectory()) / "assets/western";
    return std::filesystem::is_regular_file(packaged / "western.glb")
               ? packaged
               : std::filesystem::path(DEATHWARD_ASSET_DIR) / "western";
}
WesternScene::~WesternScene() {
    unload();
}
void WesternScene::unload() {
    clearTerrain();
    std::set<unsigned int> textures;
    for (int i = 0; i < model_.materialCount; ++i)
        for (int map = MATERIAL_MAP_ALBEDO; map <= MATERIAL_MAP_BRDF; ++map) {
            const auto texture = model_.materials[i].maps[map].texture;
            if (texture.id && texture.id != rlGetTextureIdDefault() && textures.insert(texture.id).second)
                UnloadTexture(texture);
        }
    if (model_.meshCount)
        UnloadModel(model_);
    if (shader_.id)
        UnloadShader(shader_);
    model_ = {};
    shader_ = {};
    assets_ = {};
    placements_.clear();
    occluders_.clear();
    for (auto &batch : batches_)
        batch.clear();
    lastArena_ = nullptr;
    attempted_ = false;
    occlusion_ = {};
}
bool WesternScene::load(const std::filesystem::path &directory) {
    unload();
    attempted_ = true;
    std::ifstream catalog(directory / "western.catalog");
    std::string magic;
    int version = 0;
    if (!(catalog >> magic >> version) || magic != "DEATHWARD_WESTERN" || version != 1 ||
        !std::filesystem::is_regular_file(directory / "western.glb")) {
        TraceLog(LOG_WARNING, "WESTERN: Asset pack unavailable; using primitive scenery");
        return false;
    }
    std::array<bool, size_t(WesternAsset::Count)> found{};
    std::string name;
    bool valid = true;
    int expectedMeshes = 0;
    while (catalog >> name) {
        Asset asset;
        if (!(catalog >> asset.firstMesh >> asset.meshCount >> asset.bounds.min.x >> asset.bounds.min.y >>
              asset.bounds.min.z >> asset.bounds.max.x >> asset.bounds.max.y >> asset.bounds.max.z)) {
            valid = false;
            break;
        }
        const auto it = std::find(Names.begin(), Names.end(), name);
        if (it == Names.end() || asset.firstMesh != expectedMeshes || asset.meshCount <= 0 ||
            !finite(asset.bounds.min) || !finite(asset.bounds.max) ||
            asset.bounds.max.x <= asset.bounds.min.x || asset.bounds.max.z <= asset.bounds.min.z ||
            asset.bounds.max.y < asset.bounds.min.y) {
            valid = false;
            break;
        }
        const auto index = size_t(it - Names.begin());
        if (found[index]) {
            valid = false;
            break;
        }
        found[index] = true;
        assets_[index] = asset;
        expectedMeshes += asset.meshCount;
    }
    valid = valid && std::all_of(found.begin(), found.end(), [](bool v) { return v; });
    if (valid) {
        model_ = LoadModel((directory / "western.glb").string().c_str());
        valid = model_.meshCount == expectedMeshes;
    }
    for (const auto &asset : assets_) {
        if (!valid)
            break;
        BoundingBox actual = GetMeshBoundingBox(model_.meshes[asset.firstMesh]);
        for (int i = asset.firstMesh; i < asset.firstMesh + asset.meshCount; ++i) {
            const auto &mesh = model_.meshes[i];
            if (!mesh.vertices || !mesh.normals || !mesh.texcoords || model_.meshMaterial[i] <= 0 ||
                model_.meshMaterial[i] >= model_.materialCount) {
                valid = false;
                break;
            }
            const auto bounds = GetMeshBoundingBox(mesh);
            actual.min = Vector3Min(actual.min, bounds.min);
            actual.max = Vector3Max(actual.max, bounds.max);
        }
        valid = valid && finite(actual.min) && finite(actual.max) &&
                distance(actual.min, asset.bounds.min) < 0.01f &&
                distance(actual.max, asset.bounds.max) < 0.01f;
    }
    if (valid) {
        const auto fragment = withPlayerOcclusion(FragmentShader);
        shader_ = loadWorldShader(VertexShader, fragment.c_str());
        valid = shader_.id && shader_.id != rlGetShaderIdDefault();
    }
    if (!valid) {
        TraceLog(LOG_WARNING, "WESTERN: Invalid asset catalog, model or shader; using primitive scenery");
        unload();
        attempted_ = true;
        return false;
    }
    shader_.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader_, "instanceTransform");
    for (int i = 0; i < model_.materialCount; ++i) {
        model_.materials[i].shader = shader_;
        auto &texture = model_.materials[i].maps[MATERIAL_MAP_ALBEDO].texture;
        if (texture.id && texture.id != rlGetTextureIdDefault()) {
            GenTextureMipmaps(&texture);
            SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);
        }
    }
    TraceLog(LOG_INFO, "WESTERN: Ready, %d textured assets in %d mesh batches", int(assets_.size()),
             model_.meshCount);
    return true;
}
Matrix WesternScene::placementTransform(Box source, const WesternPlacement &placement) {
    const Vector3 sourceSize = sub(source.max, source.min),
                  size = sub(placement.bounds.max, placement.bounds.min);
    const bool quarterTurn = std::abs(std::sin(placement.yaw)) > 0.5f;
    const Vector3 scale{(quarterTurn ? size.z : size.x) / sourceSize.x,
                        sourceSize.y > 0.001f ? size.y / sourceSize.y : 1,
                        (quarterTurn ? size.x : size.z) / sourceSize.z};
    const Vector3 origin{(source.min.x + source.max.x) / 2, source.min.y, (source.min.z + source.max.z) / 2};
    const Vector3 position{(placement.bounds.min.x + placement.bounds.max.x) / 2, placement.bounds.min.y,
                           (placement.bounds.min.z + placement.bounds.max.z) / 2};
    auto transform = MatrixMultiply(MatrixTranslate(-origin.x, -origin.y, -origin.z),
                                    MatrixScale(scale.x, scale.y, scale.z));
    transform = MatrixMultiply(transform, MatrixRotateY(placement.yaw));
    return MatrixMultiply(transform, MatrixTranslate(position.x, position.y, position.z));
}
void WesternScene::prepare(const Arena &arena) {
    if (!attempted_)
        load();
    if (!loaded() && !arena.canyon)
        return;
    if (lastArena_ != &arena || lastSeed_ != arena.visualSeed || lastTheme_ != arena.theme) {
        generate(arena);
        lastArena_ = &arena;
        lastSeed_ = arena.visualSeed;
        lastTheme_ = arena.theme;
    }
}
void WesternScene::generate(const Arena &arena) {
    placements_.clear();
    clearTerrain();
    if (arena.theme == MissionTheme::Canyon && arena.canyon) {
        generateCanyon(arena);
        return;
    }
    Random random(arena.visualSeed ^ 0x7765737465726e31ULL);
    auto place = [&](WesternAsset asset, Box box, float yaw = 0, bool exterior = false) {
        placements_.push_back({asset, box, yaw, exterior});
    };
    for (auto floor : arena.floors) {
        floor.min.y = floor.max.y = -0.015f;
        place(WesternAsset::Floor, floor);
    }
    for (const auto &wall : arena.boundaryWalls) {
        const auto size = sub(wall.max, wall.min);
        const bool alongX = size.x > size.z;
        const float span = alongX ? size.x : size.z;
        const int panels = std::max(1, int(std::ceil(span / 3.2f)));
        for (int i = 0; i < panels; ++i) {
            Box panel = wall;
            panel.min.y = 0;
            if (alongX) {
                panel.min.x = wall.min.x + span * float(i) / panels;
                panel.max.x = wall.min.x + span * float(i + 1) / panels;
            } else {
                panel.min.z = wall.min.z + span * float(i) / panels;
                panel.max.z = wall.min.z + span * float(i + 1) / panels;
            }
            place(WesternAsset::Fence, panel, alongX ? 0 : Pi / 2);
        }
    }
    for (const auto &cover : arena.obstacles) {
        const auto size = sub(cover.max, cover.min);
        // Fill the existing solid cover volume with fitted crate stacks. Material,
        // rotation and stack divisions vary without changing collision or navigation.
        const int nx = std::max(1, int(std::round(size.x / 1.4f)));
        const int nz = std::max(1, int(std::round(size.z / 1.4f)));
        const int ny = std::max(1, int(std::round(size.y / 1.2f)));
        for (int x = 0; x < nx; ++x)
            for (int z = 0; z < nz; ++z)
                for (int y = 0; y < ny; ++y) {
                    Box cell{{cover.min.x + size.x * x / nx, cover.min.y + size.y * y / ny,
                              cover.min.z + size.z * z / nz},
                             {cover.min.x + size.x * (x + 1) / nx, cover.min.y + size.y * (y + 1) / ny,
                              cover.min.z + size.z * (z + 1) / nz}};
                    place(WesternAsset::Crate, cell, float(random.bounded(4)) * Pi / 2);
                }
    }
    for (const auto &passage : arena.passages) {
        const auto direction = unit(sub(passage.to, passage.from));
        const bool alongX = std::abs(direction.x) > 0.5f;
        const float span = distance(passage.from, passage.to);
        const int segments = std::max(1, int(std::ceil(span / 9.8f)));
        for (int i = 0; i < segments; ++i) {
            const auto center = add(passage.from, mul(direction, span * (float(i) + 0.5f) / segments));
            const float half = span / segments / 2;
            Box rail{{center.x - (alongX ? half : 1.65f), 0.005f, center.z - (alongX ? 1.65f : half)},
                     {center.x + (alongX ? half : 1.65f), 0.19f, center.z + (alongX ? 1.65f : half)}};
            place(WesternAsset::Rail, rail, alongX ? Pi / 2 : 0);
        }
        const Vector3 side{-direction.z, 0, direction.x};
        for (auto end : {passage.from, passage.to})
            for (float offset : {-3.5f, 3.5f}) {
                const auto p = add(end, mul(side, offset));
                place(WesternAsset::Lantern,
                      {{p.x - 0.22f, 1.96f, p.z - 0.14f}, {p.x + 0.22f, 2.61f, p.z + 0.14f}});
            }
    }
    for (auto p : {arena.entrance, arena.exit})
        place(WesternAsset::Lantern, {{p.x - 0.22f, 1.96f, p.z - 0.14f}, {p.x + 0.22f, 2.61f, p.z + 0.14f}});
    std::vector<Box> exterior;
    auto outside = [&](Box box) {
        for (const auto &floor : arena.floors)
            if (overlaps(box, floor, 0.65f))
                return false;
        for (const auto &other : exterior)
            if (overlaps(box, other, 0.6f))
                return false;
        return true;
    };
    auto exteriorPiece = [&](WesternAsset asset, Vector3 center, float scale, float yaw) {
        auto size = mul(sub(assetBounds(asset).max, assetBounds(asset).min), scale);
        if (std::abs(std::sin(yaw)) > 0.5f)
            std::swap(size.x, size.z);
        Box box{{center.x - size.x / 2, -0.02f, center.z - size.z / 2},
                {center.x + size.x / 2, size.y - 0.02f, center.z + size.z / 2}};
        if (!outside(box))
            return false;
        place(asset, box, yaw, true);
        exterior.push_back(box);
        return true;
    };
    constexpr std::array landmarks{WesternAsset::Saloon, WesternAsset::Jail, WesternAsset::Church,
                                   WesternAsset::Station, WesternAsset::WaterTower};
    constexpr std::array props{WesternAsset::Barrel, WesternAsset::Sacks, WesternAsset::Woodpile,
                               WesternAsset::Coffin, WesternAsset::Cart,  WesternAsset::Well,
                               WesternAsset::RockA,  WesternAsset::RockB, WesternAsset::CactusA,
                               WesternAsset::CactusB};
    for (const auto &room : arena.rooms) {
        for (int side = 0; side < 2; ++side) {
            const auto asset = landmarks[random.bounded(uint32_t(landmarks.size()))];
            const float scale = random.real(0.7f, 0.9f), yaw = side ? Pi / 2 : 0;
            const auto size = mul(sub(assetBounds(asset).max, assetBounds(asset).min), scale);
            for (int attempt = 0; attempt < 5; ++attempt) {
                auto center = room.center;
                if (side) {
                    center.x = room.bounds.min.x - size.z / 2 - 1.6f;
                    center.z += random.real(-8, 8);
                } else {
                    center.z = room.bounds.min.z - size.z / 2 - 1.6f;
                    center.x += random.real(-8, 8);
                }
                if (exteriorPiece(asset, center, scale, yaw))
                    break;
            }
        }
        for (int i = 0; i < 14; ++i) {
            const auto asset = props[random.bounded(uint32_t(props.size()))];
            auto center = room.center;
            const int side = int(random.bounded(4));
            if (side < 2) {
                center.x = (side ? room.bounds.max.x + 4 : room.bounds.min.x - 4);
                center.z = random.real(room.bounds.min.z - 3, room.bounds.max.z + 3);
            } else {
                center.z = (side == 2 ? room.bounds.max.z + 4 : room.bounds.min.z - 4);
                center.x = random.real(room.bounds.min.x - 3, room.bounds.max.x + 3);
            }
            exteriorPiece(asset, center, random.real(0.8f, 1.3f), float(random.bounded(4)) * Pi / 2);
        }
    }
}
void WesternScene::draw(Vector3 focus) {
    drawTerrain(focus);
    occluders_.clear();
    if (!loaded())
        return;
    for (auto &batch : batches_)
        batch.clear();
    for (const auto &placement : placements_) {
        const auto &box = placement.bounds;
        const Vector3 nearest{std::clamp(focus.x, box.min.x, box.max.x), focus.y,
                              std::clamp(focus.z, box.min.z, box.max.z)};
        if (distance(nearest, focus) > 75)
            continue;
        bool blocked = false;
        if (lastTheme_ == MissionTheme::Canyon) {
            const Vector3 base{(box.min.x + box.max.x) * .5f, 32, (box.min.z + box.max.z) * .5f};
            // Props on a faded cliff share its opacity instead of appearing to float above it.
            blocked = std::any_of(terrain_.begin(), terrain_.end(), [&](const auto &section) {
                return section.faded && base.x >= section.bounds.min.x && base.x <= section.bounds.max.x &&
                       base.z >= section.bounds.min.z && base.z <= section.bounds.max.z &&
                       GetRayCollisionMesh({base, {0, -1, 0}}, section.mesh, MatrixIdentity()).hit;
            });
        }
        const auto index = size_t(placement.asset);
        const auto &asset = assets_[index];
        const auto transform = placementTransform(asset.bounds, placement);
        if (occlusion_.intersects(box))
            for (int mesh = asset.firstMesh; mesh < asset.firstMesh + asset.meshCount && !blocked; ++mesh)
                blocked = occlusion_.blocks(model_.meshes[mesh], transform);
        if (blocked)
            occluders_.push_back(&placement);
        else
            batches_[index].push_back(transform);
    }
    drawBatches(false);
}
void WesternScene::drawGlass() {
    if (!loaded())
        return;
    // Draw after actors and lantern lights. Glass must not write depth and hide
    // the light inside the fixture or later particles behind its surface.
    rlDrawRenderBatchActive();
    rlDisableDepthMask();
    drawBatches(true);
    rlEnableDepthMask();
}
void WesternScene::drawBatches(bool transparent) {
    occlusion_.bind(shader_, false);
    for (size_t i = 0; i < assets_.size(); ++i) {
        const auto &batch = batches_[i];
        if (batch.empty())
            continue;
        const auto &asset = assets_[i];
        const Vector3 tint = lastTheme_ == MissionTheme::Canyon
                                 ? (i == size_t(WesternAsset::Floor) ? Vector3{1.22f, 1.04f, .85f}
                                                                     : Vector3{1.18f, .94f, .78f})
                                 : Vector3{1, 1, 1};
        SetShaderValue(shader_, GetShaderLocation(shader_, "sceneryTint"), &tint, SHADER_UNIFORM_VEC3);
        const bool cliff = i == size_t(WesternAsset::CliffWall) || i == size_t(WesternAsset::CliffCap) ||
                           i == size_t(WesternAsset::CliffPillar);
        // Unity cliff faces are open at the back. Orbiting can see them from
        // either side; draw both sides instead of exposing holes and slivers.
        if (cliff)
            rlDisableBackfaceCulling();
        for (int mesh = asset.firstMesh; mesh < asset.firstMesh + asset.meshCount; ++mesh) {
            const auto &material = model_.materials[model_.meshMaterial[mesh]];
            if ((material.maps[MATERIAL_MAP_ALBEDO].color.a < 255) != transparent)
                continue;
            DrawMeshInstanced(model_.meshes[mesh], material, batch.data(), int(batch.size()));
        }
        if (cliff)
            rlEnableBackfaceCulling();
    }
}
void WesternScene::drawOccluders() {
    if (!occlusion_.enabled)
        return;
    struct Surface {
        const TerrainChunk *terrain;
        const WesternPlacement *placement;
        float depth;
    };
    std::vector<Surface> surfaces;
    const auto forward = unit(sub(occlusion_.camera.target, occlusion_.camera.position));
    auto depth = [&](Box bounds) {
        return dot(sub(mul(add(bounds.min, bounds.max), .5f), occlusion_.camera.position), forward);
    };
    for (const auto &section : terrain_)
        if (section.faded)
            surfaces.push_back({&section, nullptr, depth(section.bounds)});
    for (const auto *placement : occluders_)
        surfaces.push_back({nullptr, placement, depth(placement->bounds)});
    // Terrain and its props share one back-to-front pass after actors, without depth writes.
    std::sort(surfaces.begin(), surfaces.end(),
              [](const auto &a, const auto &b) { return a.depth > b.depth; });
    rlDrawRenderBatchActive();
    rlDisableDepthMask();
    if (terrainShader_.id)
        occlusion_.bind(terrainShader_, true);
    if (loaded())
        occlusion_.bind(shader_, true);
    for (const auto &surface : surfaces) {
        if (surface.terrain) {
            DrawMesh(surface.terrain->mesh, terrainMaterial_, MatrixIdentity());
        } else {
            const auto *placement = surface.placement;
            const auto &asset = assets_[size_t(placement->asset)];
            const auto transform = placementTransform(asset.bounds, *placement);
            const Vector3 tint =
                lastTheme_ == MissionTheme::Canyon ? Vector3{1.18f, .94f, .78f} : Vector3{1, 1, 1};
            SetShaderValue(shader_, GetShaderLocation(shader_, "sceneryTint"), &tint, SHADER_UNIFORM_VEC3);
            const bool cliff = placement->asset == WesternAsset::CliffWall ||
                               placement->asset == WesternAsset::CliffCap ||
                               placement->asset == WesternAsset::CliffPillar;
            if (cliff)
                rlDisableBackfaceCulling();
            for (int j = asset.firstMesh; j < asset.firstMesh + asset.meshCount; ++j) {
                const auto &material = model_.materials[model_.meshMaterial[j]];
                DrawMeshInstanced(model_.meshes[j], material, &transform, 1);
            }
            if (cliff)
                rlEnableBackfaceCulling();
        }
    }
    drawTerrainOutlines();
    rlEnableDepthMask();
}
} // namespace dw
