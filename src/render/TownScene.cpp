#include "render/TownScene.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <fstream>
#include <set>
#include <stdexcept>

namespace dw {
namespace {
constexpr const char *Vertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;
in mat4 instanceTransform;
uniform mat4 mvp;
out vec2 uv;
out vec3 normal;
out vec3 world;
out vec4 color;
void main() {
    uv = vertexTexCoord;
    color = vertexColor;
    vec4 p = instanceTransform * vec4(vertexPosition,1.0);
    world = p.xyz;
    normal = normalize(transpose(inverse(mat3(instanceTransform))) * vertexNormal);
    gl_Position = mvp * p;
}
)GLSL";
constexpr const char *Fragment = R"GLSL(#version 330
in vec2 uv;
in vec3 normal;
in vec3 world;
in vec4 color;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform int unlit;
uniform int lightCount;
uniform vec3 lightPositions[8];
uniform vec3 lightDirections[8];
uniform vec3 lightColors[8];
uniform float lightRanges[8];
out vec4 finalColor;
void main() {
    vec4 surface = texture(texture0,uv) * colDiffuse * color;
    if(surface.a < .02) discard;
    vec3 light = vec3(.46);
    for(int i=0;i<lightCount;i++) {
        vec3 d = lightDirections[i];
        float attenuation = .62;
        if(lightRanges[i]>0.0) {
            vec3 delta = lightPositions[i]-world;
            d = normalize(delta);
            attenuation = pow(max(0.0,1.0-length(delta)/lightRanges[i]),2.0);
        }
        light += max(dot(normalize(normal),d),0.0)*lightColors[i]*attenuation;
    }
    finalColor=vec4(surface.rgb*(unlit!=0?vec3(1.0):light),surface.a);
}
)GLSL";
Matrix readMatrix(std::istream &in) {
    // The scene catalog stores mathematical rows; raylib's fields are named by
    // their column-major index even though the struct groups rows in memory.
    Matrix m{};
    in >> m.m0 >> m.m4 >> m.m8 >> m.m12 >> m.m1 >> m.m5 >> m.m9 >> m.m13 >> m.m2 >> m.m6 >> m.m10 >> m.m14 >>
        m.m3 >> m.m7 >> m.m11 >> m.m15;
    return m;
}
Box transformBounds(Box source, Matrix m) {
    Box box{{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    for (float x : {source.min.x, source.max.x})
        for (float y : {source.min.y, source.max.y})
            for (float z : {source.min.z, source.max.z}) {
                auto p = Vector3Transform({x, y, z}, m);
                if (!std::isfinite(p.x) || !std::isfinite(p.y) || !std::isfinite(p.z))
                    throw std::runtime_error("Non-finite town instance");
                box.min = Vector3Min(box.min, p);
                box.max = Vector3Max(box.max, p);
            }
    return box;
}
} // namespace
std::filesystem::path TownScene::assetDirectory(HubKind hub) {
    const auto source = std::filesystem::path(DEATHWARD_ASSET_DIR) / hubFolder(hub);
    if (std::filesystem::is_regular_file(source / "town.scene"))
        return source; // Editor saves in the checkout survive rebuilds; shipped builds use their own pack.
    auto packaged = std::filesystem::path(GetApplicationDirectory()) / "assets" / hubFolder(hub);
    return std::filesystem::is_regular_file(packaged / "town.scene") ? packaged : source;
}
TownScene::~TownScene() {
    unload();
}
void TownScene::unload() {
    std::set<unsigned> textures;
    for (int i = 0; i < model_.materialCount; ++i)
        for (int j = MATERIAL_MAP_ALBEDO; j <= MATERIAL_MAP_BRDF; ++j) {
            auto t = model_.materials[i].maps[j].texture;
            if (t.id && t.id != rlGetTextureIdDefault() && textures.insert(t.id).second)
                UnloadTexture(t);
        }
    if (model_.meshCount)
        UnloadModel(model_);
    if (shader_.id)
        UnloadShader(shader_);
    model_ = {};
    shader_ = {};
    assets_.clear();
    instances_.clear();
    document_ = {};
    batches_.clear();
    attempted_ = false;
}
bool TownScene::load(const std::filesystem::path &directory) {
    unload();
    attempted_ = true;
    try {
        std::string error;
        if (!document_.load(directory / "town.scene", error))
            throw std::runtime_error(error);
        std::ifstream in(directory / "town.scene");
        std::string token;
        int version = 0;
        if (!(in >> token >> version) || token != "DEATHWARD_TOWN" || version != 1)
            throw std::runtime_error("Missing town scene catalog");
        std::vector<Vector3> positions, directions, colors;
        std::vector<float> ranges;
        int meshCount = 0;
        while (in >> token) {
            if (token == "asset") {
                std::string name;
                Asset a{};
                in >> name >> a.first >> a.count >> a.unlit >> a.bounds.min.x >> a.bounds.min.y >>
                    a.bounds.min.z >> a.bounds.max.x >> a.bounds.max.y >> a.bounds.max.z;
                if (a.first != meshCount || a.count <= 0)
                    throw std::runtime_error("Invalid town mesh range");
                meshCount += a.count;
                assets_.push_back(a);
            } else if (token == "instance") {
                size_t asset;
                in >> asset;
                auto transform = readMatrix(in);
                if (asset >= assets_.size())
                    throw std::runtime_error("Invalid town asset index");
                instances_.push_back({asset, transform, transformBounds(assets_[asset].bounds, transform)});
            } else if (token == "light") {
                int type;
                Vector3 p, d, c;
                float intensity, range;
                in >> type >> p.x >> p.y >> p.z >> d.x >> d.y >> d.z >> c.x >> c.y >> c.z >> intensity >>
                    range;
                if (positions.size() < 8) {
                    positions.push_back(p);
                    directions.push_back(d);
                    colors.push_back(mul(c, intensity));
                    ranges.push_back(type == 1 ? 0 : range);
                }
            } else
                throw std::runtime_error("Unknown town scene entry");
            if (!in)
                throw std::runtime_error("Truncated town scene catalog");
        }
        if (assets_.empty() || instances_.empty())
            throw std::runtime_error("Empty town scene");
        model_ = LoadModel((directory / "town.glb").string().c_str());
        if (model_.meshCount != meshCount)
            throw std::runtime_error("Town model/catalog mismatch");
        shader_ = LoadShaderFromMemory(Vertex, Fragment);
        if (!shader_.id || shader_.id == rlGetShaderIdDefault())
            throw std::runtime_error("Town shader failed to compile");
        shader_.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader_, "instanceTransform");
        const int count = int(positions.size());
        SetShaderValue(shader_, GetShaderLocation(shader_, "lightCount"), &count, SHADER_UNIFORM_INT);
        if (count) {
            SetShaderValueV(shader_, GetShaderLocation(shader_, "lightPositions"), positions.data(),
                            SHADER_UNIFORM_VEC3, count);
            SetShaderValueV(shader_, GetShaderLocation(shader_, "lightDirections"), directions.data(),
                            SHADER_UNIFORM_VEC3, count);
            SetShaderValueV(shader_, GetShaderLocation(shader_, "lightColors"), colors.data(),
                            SHADER_UNIFORM_VEC3, count);
            SetShaderValueV(shader_, GetShaderLocation(shader_, "lightRanges"), ranges.data(),
                            SHADER_UNIFORM_FLOAT, count);
        }
        std::set<unsigned> filtered;
        for (int i = 0; i < model_.materialCount; ++i) {
            auto &m = model_.materials[i];
            m.shader = shader_;
            auto &t = m.maps[MATERIAL_MAP_ALBEDO].texture;
            if (t.id && t.id != rlGetTextureIdDefault() && filtered.insert(t.id).second) {
                GenTextureMipmaps(&t);
                SetTextureFilter(t, TEXTURE_FILTER_TRILINEAR);
            }
        }
        batches_.resize(assets_.size());
        TraceLog(LOG_INFO, "TOWN: Original Demo scene loaded: %d placements, %d mesh sections",
                 int(instances_.size()), meshCount);
        return true;
    } catch (const std::exception &e) {
        TraceLog(LOG_ERROR, "TOWN: %s", e.what());
        unload();
        attempted_ = true;
        return false;
    }
}
void TownScene::applyDocument(const TownDocument &document) {
    document.validate();
    if (document.meshCount() != model_.meshCount || document.assets.size() != assets_.size())
        throw std::runtime_error("The edited scene must use the loaded mesh library.");
    document_ = document;
    instances_.clear();
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        instances_.push_back({i.asset, i.transform, document.bounds(n)});
    }
}
std::optional<size_t> TownScene::pick(Ray ray) const {
    std::optional<size_t> selected;
    float nearest = std::numeric_limits<float>::infinity();
    for (size_t n = 0; n < instances_.size(); ++n) {
        const auto &i = instances_[n];
        const auto &a = assets_[i.asset];
        if (a.unlit || !GetRayCollisionBox(ray, {i.bounds.min, i.bounds.max}).hit)
            continue;
        for (int mesh = a.first; mesh < a.first + a.count; ++mesh) {
            const auto hit = GetRayCollisionMesh(ray, model_.meshes[mesh], i.transform);
            if (hit.hit && hit.distance < nearest) {
                selected = n;
                nearest = hit.distance;
            }
        }
    }
    return selected;
}
void TownScene::draw(Vector3 focus, bool glass) {
    if (!attempted_)
        load();
    if (!loaded())
        return;
    if (!glass) {
        for (auto &b : batches_)
            b.clear();
        for (const auto &i : instances_) {
            const auto &b = i.bounds;
            Vector3 nearest{std::clamp(focus.x, b.min.x, b.max.x), focus.y,
                            std::clamp(focus.z, b.min.z, b.max.z)};
            const bool backdrop = document_.assets[i.asset].label.find("BackgroundCard") != std::string::npos;
            if (distance(focus, nearest) > 120 && !assets_[i.asset].unlit && !backdrop)
                continue;
            batches_[i.asset].push_back(i.transform);
        }
    }
    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling(); // Original scene includes negative scales and two-sided materials.
    if (glass)
        rlDisableDepthMask();
    for (size_t i = 0; i < assets_.size(); ++i) {
        const auto &a = assets_[i];
        const auto &batch = batches_[i];
        if (batch.empty())
            continue;
        SetShaderValue(shader_, GetShaderLocation(shader_, "unlit"), &a.unlit, SHADER_UNIFORM_INT);
        for (int j = a.first; j < a.first + a.count; ++j) {
            const auto &m = model_.materials[model_.meshMaterial[j]];
            if ((m.maps[MATERIAL_MAP_ALBEDO].color.a < 255) != glass)
                continue;
            DrawMeshInstanced(model_.meshes[j], m, batch.data(), int(batch.size()));
        }
    }
    if (glass)
        rlEnableDepthMask();
    rlEnableBackfaceCulling();
}
} // namespace dw
