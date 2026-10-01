#include "render/WesternScene.hpp"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "rlgl.h"
#include <fstream>
#include <set>

namespace dw {
namespace {
constexpr std::array<const char *, size_t(WesternAsset::Count)> Names{
    "crate",     "barrel",  "sacks",    "woodpile", "lantern",     "coffin",     "cart",         "fence",
    "saloon",    "jail",    "church",   "station",  "water_tower", "well",       "rail",         "ground",
    "rock_a",    "rock_b",  "cactus_a", "cactus_b", "floor",       "cliff_wall", "cliff_pillar", "cliff_cap",
    "sandstone", "grass_a", "grass_b",  "stick_a",  "stick_b",     "skull",      "bones"};
constexpr const char *VertexShader = R"GLSL(#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
// Reserve the same four attributes in color/depth programs. raylib retains
// instance attributes on the mesh VAO between passes.
layout(location=8) in mat4 instanceTransform;
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
out vec4 finalColor;
void main() {
    vec4 surface = texture(texture0, uv) * colDiffuse;
    surface.rgb = groundSurface(surface.rgb,world);
    if (surface.a < 0.02) discard;
    surface = playerOcclusionSurface(world,surface);
    vec3 litNormal = gl_FrontFacing ? normalize(normal) : -normalize(normal);
    finalColor = vec4(surface.rgb * westernDaylight(litNormal,missionSun,missionVisibility(world,litNormal)), surface.a);
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
    ground_.unload();
    lighting_.unload();
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
    allPlacements_.clear();
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
        const auto fragment = withPlayerOcclusion(
            MissionLighting::withShadows(GroundSurface::withDetail(FragmentShader).c_str()).c_str());
        shader_ = loadWorldShader(VertexShader, fragment.c_str());
        shader_.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(shader_, "shadowMap");
        shader_.locs[SHADER_LOC_MAP_OCCLUSION] = GetShaderLocation(shader_, "groundSoil");
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
    Vector3 scale{(quarterTurn ? size.z : size.x) / sourceSize.x,
                  sourceSize.y > 0.001f ? size.y / sourceSize.y : 1,
                  (quarterTurn ? size.x : size.z) / sourceSize.z};
    if (placement.naturalScale > 0)
        scale = {placement.naturalScale, placement.naturalScale, placement.naturalScale};
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
    if (lastArena_ != &arena || lastSeed_ != arena.visualSeed || lastTheme_ != arena.theme ||
        terrainField_ != arena.canyon) {
        generate(arena);
        std::vector<Box> groundRocks;
        for (const auto &p : placements_)
            if ((p.asset == WesternAsset::RockA || p.asset == WesternAsset::RockB) && p.bounds.min.y < .2f)
                groundRocks.push_back(p.bounds);
        ground_.prepare(arena, groundRocks);
        if (terrainMaterial_.maps)
            terrainMaterial_.maps[MATERIAL_MAP_OCCLUSION].texture = ground_.texture();
        Random densityRandom(arena.visualSeed ^ 0x7665676574617465ULL);
        for (auto &p : placements_)
            if (isVegetation(p.asset))
                p.vegetationLevel = (p.vegetationLevel ? 101 : 1) + int(densityRandom.bounded(100));
        allPlacements_ = std::move(placements_);
        applyVegetationDensity();
        lastArena_ = &arena;
        lastSeed_ = arena.visualSeed;
        lastTheme_ = arena.theme;
    }
}
void WesternScene::setVegetationDensity(int percent) {
    percent = std::clamp(percent, 0, VisualSettings::MaxVegetation);
    if (vegetationDensity_ == percent)
        return;
    vegetationDensity_ = percent;
    applyVegetationDensity();
}
void WesternScene::applyVegetationDensity() {
    placements_.clear();
    for (const auto &p : allPlacements_)
        if (p.vegetationLevel <= vegetationDensity_)
            placements_.push_back(p);
    occluders_.clear();
    for (auto &batch : batches_)
        batch.clear();
    lighting_.invalidate();
}
int WesternScene::vegetationCount() const {
    return int(std::count_if(placements_.begin(), placements_.end(),
                             [](const auto &p) { return isVegetation(p.asset); }));
}
void WesternScene::generate(const Arena &arena) {
    placements_.clear();
    clearTerrain();
    lighting_.invalidate();
    if (arena.theme == MissionTheme::Canyon && arena.canyon) {
        generateCanyon(arena);
        generateRoomDecorations(arena);
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
    // Extra cacti use their own stream after all baseline scenery is fixed.
    Random extraCacti(arena.visualSeed ^ 0x6578747261636163ULL);
    const size_t baseline = placements_.size();
    for (size_t i = 0; i < baseline; ++i) {
        const auto original = placements_[i];
        if (original.asset != WesternAsset::CactusA && original.asset != WesternAsset::CactusB)
            continue;
        for (int attempt = 0; attempt < 12; ++attempt) {
            auto center = mul(add(original.bounds.min, original.bounds.max), .5f);
            center.x += extraCacti.real(-4, 4);
            center.z += extraCacti.real(-4, 4);
            if (exteriorPiece(original.asset, center, extraCacti.real(.8f, 1.3f),
                              float(extraCacti.bounded(4)) * Pi / 2)) {
                placements_.back().vegetationLevel = 101;
                break;
            }
        }
    }
    generateRoomDecorations(arena);
}
int WesternScene::decorationCount(int room) const {
    return int(std::count_if(placements_.begin(), placements_.end(), [&](const auto &p) {
        return p.decorationRoom >= 0 && (room < 0 || p.decorationRoom == room);
    }));
}
void WesternScene::generateRoomDecorations(const Arena &arena) {
    if (!loaded())
        return;
    const bool canyon = bool(arena.canyon);
    auto distanceXZ = [](Vector3 a, Vector3 b) { return std::hypot(a.x - b.x, a.z - b.z); };
    auto routeDistance = [&](Vector3 p, Vector3 a, Vector3 b) {
        a.y = b.y = p.y = 0;
        const auto delta = sub(b, a);
        const float t = std::clamp(dot(sub(p, a), delta) / std::max(.001f, dot(delta, delta)), 0.f, 1.f);
        return distanceXZ(p, add(a, mul(delta, t)));
    };
    for (int index = 0; index < RoomCount; ++index) {
        const auto &room = arena.rooms[size_t(index)];
        // A separate stream per room never consumes encounter, loot, terrain or
        // exterior-scenery randomness. Collected keys and open gates don't affect it.
        Random random(arena.visualSeed ^ 0x6465636f72617465ULL ^
                      (uint64_t(index + 1) * 0x9e3779b97f4a7c15ULL) ^ uint64_t(arena.theme));
        std::vector<Vector3> routes{room.entry, room.exit, room.objective};
        for (int link : room.passages) {
            const auto &passage = arena.passages[size_t(link)];
            routes.push_back(arena.doorPosition(link, passage.rooms[0] == index ? 0 : 1));
        }
        auto reserved = [&](Vector3 p, float radius) {
            if (canyon) {
                const auto road = arena.canyon->roadSample(p);
                if (road.distance < road.width + radius + .55f)
                    return true;
            }
            if (distanceXZ(p, room.center) < 3.5f + radius || distanceXZ(p, room.objective) < 3.5f + radius ||
                distanceXZ(p, arena.entrance) < 3 + radius || distanceXZ(p, arena.exit) < 3 + radius)
                return true;
            for (auto end : routes)
                if (distanceXZ(p, end) < 2.6f + radius || routeDistance(p, room.center, end) < 1.2f + radius)
                    return true;
            for (const auto &key : arena.keys)
                if (key.room == index && distanceXZ(p, key.position) < 2 + radius)
                    return true;
            const Box footprint{{p.x - radius, 0, p.z - radius}, {p.x + radius, 1, p.z + radius}};
            for (int link : room.passages)
                if (overlaps(footprint, arena.passages[size_t(link)].floor, 1.2f))
                    return true;
            return false;
        };
        auto ground = [&](Vector3 p, float halfX, float halfZ, float &height) {
            const Box footprint{{p.x - halfX - .15f, 0, p.z - halfZ - .15f},
                                {p.x + halfX + .15f, 1, p.z + halfZ + .15f}};
            if (footprint.min.x < room.bounds.min.x || footprint.max.x > room.bounds.max.x ||
                footprint.min.z < room.bounds.min.z || footprint.max.z > room.bounds.max.z)
                return false;
            for (const auto &cover : room.obstacles)
                if (overlaps(footprint, cover))
                    return false;
            for (const auto &wall : arena.boundaryWalls)
                if (overlaps(footprint, wall))
                    return false;
            float low = 100, high = -100;
            for (float x : {footprint.min.x, p.x, footprint.max.x})
                for (float z : {footprint.min.z, p.z, footprint.max.z}) {
                    if (!arena.contains({x, .85f, z}))
                        return false;
                    const float h = canyon ? arena.canyon->height(x, z) : -.015f;
                    if (canyon && h < -.015f)
                        return false; // Dry vegetation and litter stay out of water, including fords.
                    low = std::min(low, h);
                    high = std::max(high, h);
                }
            height = low - .012f;
            return high - low < .045f;
        };
        // Jittered candidates favour sheltered edges and cover. This avoids a
        // uniform carpet, and finite candidates bound generation time in any layout.
        std::vector<Vector3> edges, open;
        for (float x = room.bounds.min.x + 1; x < room.bounds.max.x - 1; x += 1.7f)
            for (float z = room.bounds.min.z + 1; z < room.bounds.max.z - 1; z += 1.7f) {
                const Vector3 p{x + random.real(-.6f, .6f), 0, z + random.real(-.6f, .6f)};
                float h = 0;
                if (reserved(p, .65f) || !ground(p, .6f, .6f, h))
                    continue;
                bool edge = false;
                for (auto offset : {Vector3{3, 0, 0}, {-3, 0, 0}, {0, 0, 3}, {0, 0, -3}}) {
                    const auto near = add(p, offset);
                    edge = edge || !arena.contains(near) || near.x < room.bounds.min.x ||
                           near.x > room.bounds.max.x || near.z < room.bounds.min.z ||
                           near.z > room.bounds.max.z;
                }
                for (const auto &cover : room.obstacles) {
                    const Vector3 nearest{std::clamp(p.x, cover.min.x, cover.max.x), 0,
                                          std::clamp(p.z, cover.min.z, cover.max.z)};
                    edge = edge || distanceXZ(p, nearest) < 3;
                }
                (edge ? edges : open).push_back(p);
            }
        auto shuffle = [&](auto &points) {
            for (size_t i = points.size(); i > 1; --i)
                std::swap(points[i - 1], points[random.bounded(uint32_t(i))]);
        };
        shuffle(edges);
        shuffle(open);
        edges.insert(edges.end(), open.begin(), open.end());
        const int patches = std::clamp(int(std::round(room.usableArea() / 80)), 5, 16);
        std::vector<Vector3> clusters;
        std::vector<Box> footprints;
        bool skull = false, bones = false;
        std::vector<WesternPlacement> grasses;
        auto placeMember = [&](WesternAsset asset, Vector3 anchor, bool extra) {
            const auto source = sub(assetBounds(asset).max, assetBounds(asset).min);
            float span = random.real(.45f, .85f), maxHeight = .3f;
            if (asset == WesternAsset::GrassA || asset == WesternAsset::GrassB) {
                span = random.real(.75f, 1.3f);
                maxHeight = .65f;
            } else if (asset == WesternAsset::StickA || asset == WesternAsset::StickB) {
                span = random.real(.65f, 1.05f);
                maxHeight = .26f;
            }
            const float scale = std::min(span / std::max(source.x, source.z), maxHeight / source.y);
            const float yaw = random.real(0, 2 * Pi);
            const float c = std::abs(std::cos(yaw)), s = std::abs(std::sin(yaw));
            const float halfX = scale * (source.x * c + source.z * s) / 2;
            const float halfZ = scale * (source.x * s + source.z * c) / 2;
            for (int attempt = 0; attempt < (extra ? 32 : 10); ++attempt) {
                const float angle = random.real(0, 2 * Pi);
                const float radius = extra ? random.real(1, 3) : random.real(0, 1.25f);
                const auto p = add(anchor, {std::cos(angle) * radius, 0, std::sin(angle) * radius});
                float h = 0;
                if (reserved(p, std::hypot(halfX, halfZ)) || !ground(p, halfX, halfZ, h))
                    continue;
                const Box box{{p.x - halfX, h, p.z - halfZ},
                              {p.x + halfX, h + source.y * scale, p.z + halfZ}};
                if (std::any_of(footprints.begin(), footprints.end(),
                                [&](auto other) { return overlaps(box, other, .1f); }))
                    continue;
                placements_.push_back({asset, box, yaw, false, index, scale, extra ? 101 : 0});
                if (!extra && isVegetation(asset))
                    grasses.push_back(placements_.back());
                footprints.push_back(box);
                skull = skull || asset == WesternAsset::Skull;
                bones = bones || asset == WesternAsset::Bones;
                return true;
            }
            return false;
        };
        for (auto anchor : edges) {
            if (int(clusters.size()) >= patches)
                break;
            if (std::any_of(clusters.begin(), clusters.end(),
                            [&](auto other) { return distanceXZ(anchor, other) < 2.6f; }))
                continue;
            const auto before = footprints.size();
            const auto river = canyon ? arena.canyon->riverSample(anchor) : RiverSample{};
            const bool bank = river.distance < river.width + 4.f;
            const int pieces = 3 + int(random.bounded(3));
            for (int member = 0; member < pieces; ++member) {
                const int choice = int(random.bounded(100));
                WesternAsset asset;
                if (choice < (bank ? 18 : canyon ? 46 : 25))
                    asset = random.bounded(2) ? WesternAsset::GrassA : WesternAsset::GrassB;
                else if (choice < (bank ? 80 : canyon ? 74 : 50))
                    asset = random.bounded(3) ? WesternAsset::RockA : WesternAsset::RockB;
                else if (choice < 93)
                    asset = random.bounded(2) ? WesternAsset::StickA : WesternAsset::StickB;
                else
                    asset = choice < 96 ? WesternAsset::Skull : WesternAsset::Bones;
                if ((asset == WesternAsset::Skull && skull) || (asset == WesternAsset::Bones && bones))
                    asset = WesternAsset::RockA;
                placeMember(asset, anchor, false);
            }
            if (footprints.size() > before)
                clusters.push_back(anchor);
        }
        // Add candidates for 100–200% only after baseline debris and vegetation
        // are fixed. Lower settings are stable subsets of this same candidate pool.
        for (const auto &grass : grasses) {
            const auto anchor = mul(add(grass.bounds.min, grass.bounds.max), .5f);
            placeMember(grass.asset, anchor, true);
        }
    }
}
void WesternScene::updateDrawState(Vector3 focus) {
    updateTerrainOcclusion();
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
}
void WesternScene::draw(Vector3 focus) {
    updateDrawState(focus);
    drawTerrain(focus);
    water_.draw(focus, lighting_);
    if (loaded())
        drawBatches(false);
}
RayCollision WesternScene::pick(Ray ray, Vector3 focus) {
    // Classify with the caller's current camera/player, including a rotation
    // before this frame has rendered. Drawing uses the exact same classification.
    updateDrawState(focus);
    RayCollision nearest{};
    nearest.distance = std::numeric_limits<float>::infinity();
    auto couldHit = [&](Box bounds) {
        const auto hit = GetRayCollisionBox(ray, {bounds.min, bounds.max});
        return hit.hit && hit.distance < nearest.distance;
    };
    auto meshHit = [&](const Mesh &mesh, Matrix transform) {
        const auto hit = GetRayCollisionMesh(ray, mesh, transform);
        if (hit.hit && hit.distance < nearest.distance)
            nearest = hit;
    };
    for (const auto &chunk : terrain_)
        if (!chunk.faded && couldHit(chunk.bounds))
            meshHit(chunk.mesh, MatrixIdentity());
    if (loaded())
        for (const auto &placement : placements_) {
            if (placement.decorationRoom >= 0)
                continue; // Cosmetic ground litter must never steal a movement/aim ray.
            const auto &box = placement.bounds;
            const Vector3 closest{std::clamp(focus.x, box.min.x, box.max.x), focus.y,
                                  std::clamp(focus.z, box.min.z, box.max.z)};
            if (distance(closest, focus) > 75 || !couldHit(box) ||
                std::find(occluders_.begin(), occluders_.end(), &placement) != occluders_.end())
                continue;
            const auto &asset = assets_[size_t(placement.asset)];
            const auto transform = placementTransform(asset.bounds, placement);
            for (int mesh = asset.firstMesh; mesh < asset.firstMesh + asset.meshCount; ++mesh)
                if (model_.materials[model_.meshMaterial[mesh]].maps[MATERIAL_MAP_ALBEDO].color.a == 255)
                    meshHit(model_.meshes[mesh], transform);
        }
    return nearest;
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
void WesternScene::prepareLighting(const Camera3D &camera,
                                   const std::function<void(Shader, Shader)> &actors) {
    lighting_.prepare(
        camera,
        [&](Shader instanceDepth, Shader meshDepth) {
            // Use physical geometry, independently of the camera's occlusion fade and
            // distance culling. Off-screen cliffs still block the sun.
            if (terrainMaterial_.maps) {
                auto material = terrainMaterial_;
                material.shader = meshDepth;
                for (const auto &chunk : terrain_)
                    if (lighting_.contains(chunk.bounds))
                        DrawMesh(chunk.mesh, material, MatrixIdentity());
            }
            std::array<std::vector<Matrix>, size_t(WesternAsset::Count)> batches;
            for (const auto &placement : placements_)
                if (lighting_.contains(placement.bounds))
                    batches[size_t(placement.asset)].push_back(
                        placementTransform(assets_[size_t(placement.asset)].bounds, placement));
            for (size_t i = 0; i < assets_.size(); ++i) {
                const auto &asset = assets_[i];
                const auto &batch = batches[i];
                if (batch.empty())
                    continue;
                for (int j = asset.firstMesh; j < asset.firstMesh + asset.meshCount; ++j) {
                    auto material = model_.materials[model_.meshMaterial[j]];
                    if (material.maps[MATERIAL_MAP_ALBEDO].color.a < 255)
                        continue;
                    material.shader = instanceDepth;
                    DrawMeshInstanced(model_.meshes[j], material, batch.data(), int(batch.size()));
                }
            }
        },
        actors);
    lighting_.bind(shader_);
    lighting_.bind(terrainShader_);
}
void WesternScene::drawBatches(bool transparent) {
    lighting_.bind(shader_);
    occlusion_.bind(shader_, false);
    for (size_t i = 0; i < assets_.size(); ++i) {
        const auto &batch = batches_[i];
        if (batch.empty())
            continue;
        const auto &asset = assets_[i];
        const bool floor = i == size_t(WesternAsset::Floor);
        ground_.bind(shader_, floor);
        const bool cliff = i == size_t(WesternAsset::CliffWall) || i == size_t(WesternAsset::CliffCap) ||
                           i == size_t(WesternAsset::CliffPillar) || i == size_t(WesternAsset::GrassA) ||
                           i == size_t(WesternAsset::GrassB);
        // Unity cliff faces are open at the back. Orbiting can see them from
        // either side; draw both sides instead of exposing holes and slivers.
        // Grass blades also need their reverse faces visible when orbiting.
        if (cliff)
            rlDisableBackfaceCulling();
        for (int mesh = asset.firstMesh; mesh < asset.firstMesh + asset.meshCount; ++mesh) {
            const auto &material = model_.materials[model_.meshMaterial[mesh]];
            if ((material.maps[MATERIAL_MAP_ALBEDO].color.a < 255) != transparent)
                continue;
            std::array<MaterialMap, 12> maps;
            std::copy_n(material.maps, maps.size(), maps.begin());
            auto surface = material;
            if (floor)
                maps[MATERIAL_MAP_OCCLUSION].texture = ground_.texture();
            surface.maps = maps.data();
            lighting_.drawInstanced(model_.meshes[mesh], surface, batch.data(), int(batch.size()));
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
    ground_.bind(terrainShader_);
    ground_.bind(shader_, false);
    if (loaded())
        occlusion_.bind(shader_, true);
    for (const auto &surface : surfaces) {
        if (surface.terrain) {
            lighting_.draw(surface.terrain->mesh, terrainMaterial_, MatrixIdentity());
        } else {
            const auto *placement = surface.placement;
            const auto &asset = assets_[size_t(placement->asset)];
            const auto transform = placementTransform(asset.bounds, *placement);
            const bool cliff =
                placement->asset == WesternAsset::CliffWall || placement->asset == WesternAsset::CliffCap ||
                placement->asset == WesternAsset::CliffPillar || placement->asset == WesternAsset::GrassA ||
                placement->asset == WesternAsset::GrassB;
            if (cliff)
                rlDisableBackfaceCulling();
            for (int j = asset.firstMesh; j < asset.firstMesh + asset.meshCount; ++j) {
                const auto &material = model_.materials[model_.meshMaterial[j]];
                lighting_.drawInstanced(model_.meshes[j], material, &transform, 1);
            }
            if (cliff)
                rlEnableBackfaceCulling();
        }
    }
    drawTerrainOutlines();
    rlEnableDepthMask();
}
} // namespace dw
