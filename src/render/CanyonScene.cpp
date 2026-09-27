#include "raylib.h"
#include "raymath.h"
#include "render/WesternScene.hpp"
#include "rlgl.h"

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
uniform sampler2D heightMap;
uniform vec4 terrainGrid;
uniform vec3 focus;
out vec4 finalColor;
float ground(vec2 p) {
    return texture(heightMap,(p-terrainGrid.xy)/terrainGrid.zw).r;
}
void main() {
    vec3 n = normalize(normal);
    vec3 sun = normalize(vec3(-.55,.85,.38));
    float shade = 1.;
    for (int i=1;i<=14;++i) {
        float travel = float(i)*1.7;
        vec3 ray = world+sun*travel;
        shade = min(shade, mix(1.,.22,smoothstep(-.5,.5,ground(ray.xz)-ray.y-.28)));
    }
    float direct = max(dot(n,sun),0.);
    float grain = .98+.025*sin(world.x*.59+world.z*.19)*sin(world.z*.43-world.x*.22);
    float strata = world.y > .15 ? .93+.07*sin(world.y*3.1+world.x*.055+world.z*.035) : 1.;
    vec3 color = texture(texture0,uv).rgb*tint*grain*strata*(.55+.62*direct*shade);
    float fog = smoothstep(60.,110.,length(world.xz-focus.xz))*.6;
    color = mix(color,vec3(.69,.54,.39),fog);
    finalColor=vec4(color,1.);
}
)GLSL";
} // namespace
void WesternScene::clearTerrain() {
    for (auto &chunk : terrain_)
        UnloadMesh(chunk.mesh);
    terrain_.clear();
    if (terrainShader_.id)
        UnloadShader(terrainShader_);
    if (heightTexture_.id)
        UnloadTexture(heightTexture_);
    // The atlas belongs to model_; this material only owns its map array.
    if (terrainMaterial_.maps)
        MemFree(terrainMaterial_.maps);
    terrainShader_ = {};
    heightTexture_ = {};
    terrainMaterial_ = {};
}
void WesternScene::generateCanyon(const Arena &arena) {
    if (!arena.canyon)
        return;
    const auto &field = *arena.canyon;
    terrainShader_ = LoadShaderFromMemory(TerrainVertex, TerrainFragment);
    terrainMaterial_ = LoadMaterialDefault();
    terrainMaterial_.shader = terrainShader_;
    Vector2 sandUv{};
    std::vector<Vector2> rockUvs;
    if (loaded()) {
        const int floorMesh = assets_[size_t(WesternAsset::Floor)].firstMesh;
        const auto &mesh = model_.meshes[floorMesh];
        sandUv = {mesh.texcoords[0], mesh.texcoords[1]};
        terrainMaterial_.maps[MATERIAL_MAP_ALBEDO].texture =
            model_.materials[model_.meshMaterial[floorMesh]].maps[MATERIAL_MAP_ALBEDO].texture;
        const auto &rock = model_.meshes[assets_[size_t(WesternAsset::CliffWall)].firstMesh];
        std::vector<std::pair<float, Vector2>> samples;
        for (int i = 0; i < rock.vertexCount; ++i)
            if (std::abs(rock.normals[i * 3 + 1]) < .7f)
                samples.push_back(
                    {rock.vertices[i * 3 + 1], {rock.texcoords[i * 2], rock.texcoords[i * 2 + 1]}});
        std::sort(samples.begin(), samples.end(), [](auto a, auto b) { return a.first < b.first; });
        for (int i = 0; i < 12 && !samples.empty(); ++i)
            rockUvs.push_back(samples[size_t((i + .5f) / 12 * samples.size())].second);
    }
    if (rockUvs.empty())
        rockUvs.push_back({});
    Image heightImage{const_cast<float *>(field.heights.data()), field.width, field.depth, 1,
                      PIXELFORMAT_UNCOMPRESSED_R32};
    heightTexture_ = LoadTextureFromImage(heightImage);
    terrainMaterial_.maps[MATERIAL_MAP_METALNESS].texture = heightTexture_;
    terrainShader_.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(terrainShader_, "heightMap");
    SetTextureFilter(heightTexture_, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(heightTexture_, TEXTURE_WRAP_CLAMP);
    const Vector4 grid{field.x - field.step * .5f, field.z - field.step * .5f, field.width * field.step,
                       field.depth * field.step};
    SetShaderValue(terrainShader_, GetShaderLocation(terrainShader_, "terrainGrid"), &grid,
                   SHADER_UNIFORM_VEC4);
    for (int iz = 0; iz < field.depth - 1; iz += 24)
        for (int ix = 0; ix < field.width - 1; ix += 24) {
            TerrainChunk chunk;
            const int right = std::min(ix + 24, field.width - 1), bottom = std::min(iz + 24, field.depth - 1);
            auto &m = chunk.mesh;
            m.triangleCount = (right - ix) * (bottom - iz) * 2;
            m.vertexCount = m.triangleCount * 3;
            m.vertices = static_cast<float *>(MemAlloc(unsigned(m.vertexCount * 3 * sizeof(float))));
            m.normals = static_cast<float *>(MemAlloc(unsigned(m.vertexCount * 3 * sizeof(float))));
            m.texcoords = static_cast<float *>(MemAlloc(unsigned(m.vertexCount * 2 * sizeof(float))));
            m.colors = static_cast<unsigned char *>(MemAlloc(unsigned(m.vertexCount * 4)));
            int vertex = 0;
            auto triangle = [&](int ax, int az, int bx, int bz, int cx, int cz) {
                const auto a = field.vertex(ax, az), b = field.vertex(bx, bz), c = field.vertex(cx, cz);
                const auto normal = Vector3Normalize(Vector3CrossProduct(sub(b, a), sub(c, a)));
                const bool rock = std::max({a.y, b.y, c.y}) > .15f;
                // Retain the source rock/sand palette; continuous strata are shaded
                // in world space so they don't expose the triangulation grid.
                const auto uv = rock ? rockUvs[rockUvs.size() / 2] : sandUv;
                const float mottling = rock ? .985f + .015f * std::sin(a.x * .83f + a.z * .37f) : 1.f;
                const Color tint = rock ? Color{255, 207, 169, 255} : Color{255, 249, 221, 255};
                for (auto cell : {std::pair{ax, az}, std::pair{bx, bz}, std::pair{cx, cz}}) {
                    const auto p = field.vertex(cell.first, cell.second);
                    m.vertices[3 * vertex] = p.x;
                    m.vertices[3 * vertex + 1] = p.y;
                    m.vertices[3 * vertex + 2] = p.z;
                    m.normals[3 * vertex] = normal.x;
                    m.normals[3 * vertex + 1] = normal.y;
                    m.normals[3 * vertex + 2] = normal.z;
                    m.texcoords[2 * vertex] = uv.x;
                    m.texcoords[2 * vertex + 1] = uv.y;
                    m.colors[4 * vertex] = static_cast<unsigned char>(tint.r * mottling);
                    m.colors[4 * vertex + 1] = static_cast<unsigned char>(tint.g * mottling);
                    m.colors[4 * vertex + 2] = static_cast<unsigned char>(tint.b * mottling);
                    m.colors[4 * vertex + 3] = 255;
                    ++vertex;
                }
            };
            for (int z = iz; z < bottom; ++z)
                for (int x = ix; x < right; ++x) {
                    triangle(x, z, x + 1, z + 1, x + 1, z);
                    triangle(x, z, x, z + 1, x + 1, z + 1);
                }
            chunk.bounds = {{field.x + ix * field.step, 0, field.z + iz * field.step},
                            {field.x + right * field.step, 12, field.z + bottom * field.step}};
            UploadMesh(&m, false);
            terrain_.push_back(chunk);
        }
    if (!loaded())
        return;
    Random rng(arena.visualSeed ^ 0x43414e594f4e4152ULL);
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
            placements_.push_back({asset,
                                   {{p.x - size.x / 2, h - .07f, p.z - size.z / 2},
                                    {p.x + size.x / 2, h + size.y - .07f, p.z + size.z / 2}},
                                   yaw,
                                   true});
        }
}
void WesternScene::drawTerrain(Vector3 focus) {
    if (terrain_.empty())
        return;
    SetShaderValue(terrainShader_, GetShaderLocation(terrainShader_, "focus"), &focus, SHADER_UNIFORM_VEC3);
    for (const auto &chunk : terrain_) {
        const Vector3 closest{std::clamp(focus.x, chunk.bounds.min.x, chunk.bounds.max.x), focus.y,
                              std::clamp(focus.z, chunk.bounds.min.z, chunk.bounds.max.z)};
        if (distance(closest, focus) < 110)
            DrawMesh(chunk.mesh, terrainMaterial_, MatrixIdentity());
    }
}
} // namespace dw
