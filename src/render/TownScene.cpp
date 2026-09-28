#include "render/TownScene.hpp"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "rlgl.h"
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
out float paletteVariation;
void main() {
    uv = vertexTexCoord;
    color = vertexColor;
    paletteVariation = fract(sin(dot(instanceTransform[3].xz,vec2(12.9898,78.233)))*43758.5453);
    vec4 p = instanceTransform * vec4(vertexPosition,1.0);
    world = p.xyz;
    normal = normalize(transpose(inverse(mat3(instanceTransform))) * vertexNormal);
    gl_Position = mvp * p;
}
)GLSL";
// Raylib CPU-skins the bandit; this shader consumes the same animated vertices.
constexpr const char *ActorVertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
out vec2 uv;
out vec3 normal;
out vec3 world;
out vec4 color;
out float paletteVariation;
void main() {
    uv = vertexTexCoord;
    color = vertexColor;
    paletteVariation = 0.;
    world = (matModel * vec4(vertexPosition,1.)).xyz;
    normal = normalize((matNormal * vec4(vertexNormal,0.)).xyz);
    gl_Position = mvp * vec4(vertexPosition,1.);
}
)GLSL";
constexpr const char *DepthFragment = R"GLSL(#version 330
in vec2 uv;
in vec4 color;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
out vec4 finalColor;
void main() {
    if ((texture(texture0,uv)*colDiffuse*color).a < .5) discard;
    finalColor = vec4(1.);
}
)GLSL";
constexpr const char *Fragment = R"GLSL(#version 330
in vec2 uv;
in vec3 normal;
in vec3 world;
in vec4 color;
in float paletteVariation;
uniform sampler2D texture0;
uniform sampler2D shadowMap;
uniform mat4 lightVP;
uniform vec4 colDiffuse;
uniform int unlit;
uniform int autumnFoliage;
uniform int lightCount;
uniform int sunIndex;
uniform int shadowEnabled;
uniform float shadowTexelDepth;
uniform vec3 lightPositions[8];
uniform vec3 lightDirections[8];
uniform vec3 lightColors[8];
uniform float lightRanges[8];
out vec4 finalColor;
float visibility(vec3 n, vec3 sun) {
    if (shadowEnabled == 0) return 1.;
    vec4 projected = lightVP * vec4(world,1.);
    vec3 p = projected.xyz / projected.w * .5 + .5;
    if (p.z <= 0. || p.z >= 1. || any(lessThan(p.xy,vec2(0.))) ||
        any(greaterThan(p.xy,vec2(1.)))) return 1.;
    // Account for the receiver's slope across the entire PCF footprint, including at wide zoom.
    float cosine = max(dot(n,sun),.15);
    float slope = sqrt(max(0.,1.-cosine*cosine))/cosine;
    float bias = shadowTexelDepth*(1.25+2.*slope);
    vec2 texel = 1. / vec2(textureSize(shadowMap,0));
    float lit = 0.;
    for (int x=-1; x<=1; ++x)
        for (int y=-1; y<=1; ++y)
            lit += p.z-bias <= texture(shadowMap,p.xy+vec2(x,y)*texel).r ? 1. : 0.;
    float edge = max(abs(p.x*2.-1.),abs(p.y*2.-1.));
    return mix(lit/9.,1.,smoothstep(.86,1.,edge));
}
void main() {
    vec4 surface = texture(texture0,uv) * colDiffuse * color;
    if(surface.a < .02) discard;
    if(unlit == 0) surface = playerOcclusionSurface(world,surface);
    if (autumnFoliage != 0) {
        // Recolor only green leaf swatches; the original bark and texture detail remain visible.
        float leaf = smoothstep(.012,.070,surface.g-surface.b) *
                     smoothstep(-.01,.045,surface.g-surface.r*.92);
        vec3 autumn = mix(vec3(1.12,.33,.12),vec3(1.25,.79,.22),paletteVariation);
        float value = dot(surface.rgb,vec3(.25,.65,.10))*1.5;
        surface.rgb = mix(surface.rgb,autumn*value,leaf*.94);
    }
    if(unlit != 0) { finalColor = surface; return; }
    vec3 n = normalize(normal);
    // Warm ground bounce and a cool sky fill keep shaded porches readable.
    vec3 light = mix(vec3(.27,.245,.215),vec3(.43,.48,.55),n.y*.5+.5);
    for(int i=0;i<lightCount;i++) {
        vec3 d = lightDirections[i];
        float attenuation = .90;
        if(lightRanges[i]>0.0) {
            vec3 delta = lightPositions[i]-world;
            d = delta/max(length(delta),.001);
            attenuation = pow(max(0.0,1.0-length(delta)/lightRanges[i]),2.0);
        }
        float direct = max(dot(n,d),0.0);
        float shade = i == sunIndex && direct > 0. ? visibility(n,d) : 1.;
        light += direct*lightColors[i]*attenuation*shade;
    }
    finalColor=vec4(surface.rgb*light,surface.a);
}
)GLSL";
constexpr int ShadowSize = 2048;
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
#ifdef __EMSCRIPTEN__
    return std::filesystem::path("/persist") / hubFolder(hub);
#endif
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
    for (auto shader : {shader_, actorShader_, shadowShader_, actorShadowShader_})
        if (shader.id)
            UnloadShader(shader);
    // The framebuffer owns its depth texture; it is only borrowed by draw materials.
    if (shadowMap_.id)
        UnloadRenderTexture(shadowMap_);
    if (staticShadowMap_.id)
        UnloadRenderTexture(staticShadowMap_);
    actorShader_ = shadowShader_ = actorShadowShader_ = {};
    shadowMap_ = staticShadowMap_ = {};
    shadowsDirty_ = true;
    shadowSpan_ = 0;
    sunIndex_ = -1;
    model_ = {};
    shader_ = {};
    assets_.clear();
    instances_.clear();
    occluders_.clear();
    document_ = {};
    batches_.clear();
    shadowBatches_.clear();
    attempted_ = false;
    occlusion_ = {};
}
bool TownScene::load(const std::filesystem::path &directory) {
    unload();
    attempted_ = true;
    try {
        std::string error;
        if (!document_.load(directory / "town.scene", error))
            throw std::runtime_error(error);
        const int meshCount = document_.meshCount();
        for (const auto &a : document_.assets)
            assets_.push_back({a.first, a.count, a.unlit, a.bounds});
        for (const auto &i : document_.instances)
            instances_.push_back({i.asset, i.transform, transformBounds(assets_[i.asset].bounds, i.transform),
                                  i.motion.kind != ObjectMotionKind::None});
#ifdef __EMSCRIPTEN__
        const auto modelFile = std::filesystem::path("/assets") / directory.filename() / "town.glb";
#else
        const auto modelFile = directory / "town.glb";
#endif
        model_ = LoadModel(modelFile.string().c_str());
        if (model_.meshCount != meshCount)
            throw std::runtime_error("Town model/catalog mismatch");
        const auto fragment = withPlayerOcclusion(Fragment);
        shader_ = loadWorldShader(Vertex, fragment.c_str());
        actorShader_ = loadWorldShader(ActorVertex, fragment.c_str());
        shadowShader_ = loadWorldShader(Vertex, DepthFragment);
        actorShadowShader_ = loadWorldShader(ActorVertex, DepthFragment);
        for (auto shader : {shader_, actorShader_, shadowShader_, actorShadowShader_})
            if (!shader.id || shader.id == rlGetShaderIdDefault())
                throw std::runtime_error("Town lighting shader failed to compile");
        for (auto shader : {shader_, shadowShader_})
            shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");
        for (auto shader : {shader_, actorShader_})
            shader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(shader, "shadowMap");
        const auto createShadowMap = [] {
            RenderTexture2D target{};
            target.id = rlLoadFramebuffer();
            if (target.id) {
                target.texture.width = target.texture.height = ShadowSize;
                target.depth = {loadDepthTexture(ShadowSize, ShadowSize), ShadowSize, ShadowSize, 1, 0};
                rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D,
                                    0);
                depthOnlyFramebuffer(target.id);
                if (!target.depth.id || !rlFramebufferComplete(target.id)) {
                    UnloadRenderTexture(target);
                    target = {};
                }
            }
            return target;
        };
        shadowMap_ = createShadowMap();
        staticShadowMap_ = createShadowMap();
        if (!shadowMap_.id || !staticShadowMap_.id) {
            if (shadowMap_.id)
                UnloadRenderTexture(shadowMap_);
            if (staticShadowMap_.id)
                UnloadRenderTexture(staticShadowMap_);
            shadowMap_ = staticShadowMap_ = {};
            TraceLog(LOG_WARNING, "TOWN: Shadow buffer unavailable; using unshadowed lighting");
        }
        updateLights();
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
        shadowBatches_.resize(assets_.size());
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
    updateLights();
    instances_.clear();
    occluders_.clear();
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        instances_.push_back(
            {i.asset, i.transform, document.bounds(n), i.motion.kind != ObjectMotionKind::None});
    }
}
void TownScene::applyAnimation(const ObjectAnimationSystem &animation) {
    const auto &poses = animation.poses();
    if (poses.size() != instances_.size())
        return;
    occluders_.clear();
    for (size_t n = 0; n < poses.size(); ++n) {
        if (!instances_[n].animated)
            continue;
        instances_[n].transform = poses[n].transform;
        instances_[n].bounds = poses[n].bounds;
    }
}
void TownScene::updateLights() {
    shadowsDirty_ = true;
    auto lights = document_.lights;
    auto sun = lights.end();
    float brightness = 0;
    for (auto i = lights.begin(); i != lights.end(); ++i) {
        const float value = i->intensity * std::max({i->color.x, i->color.y, i->color.z});
        if (i->type == 1 && length(i->direction) > .001f && value > brightness) {
            brightness = value;
            sun = i;
        }
    }
    sunIndex_ = sun == lights.end() ? -1 : 0;
    if (sunIndex_ == 0) {
        std::iter_swap(lights.begin(), sun); // Reserve a slot for the sun even in scenes with many lamps.
        sunDirection_ = Vector3Normalize(lights.front().direction);
    }
    std::vector<Vector3> positions, directions, colors;
    std::vector<float> ranges;
    for (size_t i = 0; i < std::min(size_t(8), lights.size()); ++i) {
        const auto &l = lights[i];
        positions.push_back(l.position);
        directions.push_back(Vector3Normalize(l.direction));
        colors.push_back(mul(l.color, l.intensity));
        ranges.push_back(l.type == 1 ? 0 : std::max(.001f, l.range));
    }
    const int count = int(positions.size()), disabled = 0;
    for (auto shader : {shader_, actorShader_}) {
        SetShaderValue(shader, GetShaderLocation(shader, "lightCount"), &count, SHADER_UNIFORM_INT);
        SetShaderValue(shader, GetShaderLocation(shader, "sunIndex"), &sunIndex_, SHADER_UNIFORM_INT);
        SetShaderValue(shader, GetShaderLocation(shader, "shadowEnabled"), &disabled, SHADER_UNIFORM_INT);
        if (count) {
            SetShaderValueV(shader, GetShaderLocation(shader, "lightPositions"), positions.data(),
                            SHADER_UNIFORM_VEC3, count);
            SetShaderValueV(shader, GetShaderLocation(shader, "lightDirections"), directions.data(),
                            SHADER_UNIFORM_VEC3, count);
            SetShaderValueV(shader, GetShaderLocation(shader, "lightColors"), colors.data(),
                            SHADER_UNIFORM_VEC3, count);
            SetShaderValueV(shader, GetShaderLocation(shader, "lightRanges"), ranges.data(),
                            SHADER_UNIFORM_FLOAT, count);
        }
    }
}
void TownScene::prepareLighting(const Camera3D &camera, const std::function<void(Shader)> &actors) {
    if (!shadowsReady())
        return;
    // A square orthographic sun map follows the camera's focus, including at wide zoom.
    // Quantized coverage and texel-snapped translation keep slow pans from shimmering.
    const float span =
        std::clamp(std::ceil(distance(camera.position, camera.target) * 2 / 16) * 16, 96.0f, 256.0f);
    const float texel = span / ShadowSize;
    const Vector3 up = std::abs(sunDirection_.y) > .98f ? Vector3{0, 0, 1} : Vector3{0, 1, 0};
    const auto right = Vector3Normalize(Vector3CrossProduct(up, sunDirection_));
    const auto sky = Vector3CrossProduct(sunDirection_, right);
    const bool rebuild =
        shadowsDirty_ || shadowSpan_ != span || distance(camera.target, shadowFocus_) > span * .075f;
    auto focus = rebuild ? camera.target : shadowFocus_;
    for (auto axis : {right, sky, sunDirection_}) {
        const float coordinate = Vector3DotProduct(focus, axis);
        focus = add(focus, mul(axis, std::round(coordinate / texel) * texel - coordinate));
    }
    Camera3D lightCamera{add(focus, mul(sunDirection_, 180)), focus, up, span, CAMERA_ORTHOGRAPHIC};
    const auto projection = MatrixOrtho(-span * .5, span * .5, -span * .5, span * .5, 1, 360);
    const auto lightVP = MatrixMultiply(GetCameraMatrix(lightCamera), projection);
    // Reuse the expensive town depth pass until the camera leaves its central area.
    // Moving objects and the character are redrawn separately; edits invalidate the cache.
    if (rebuild) {
        BeginTextureMode(staticShadowMap_);
        ClearBackground(WHITE);
        BeginMode3D(lightCamera);
        rlSetMatrixProjection(MatrixOrtho(-span * .5, span * .5, -span * .5, span * .5, 1, 360));
        const auto view = rlGetMatrixModelview();
        for (auto &batch : shadowBatches_)
            batch.clear();
        for (const auto &i : instances_) {
            const auto &asset = document_.assets[i.asset];
            if (i.animated || asset.unlit || asset.label.find("BackgroundCard") != std::string::npos)
                continue;
            const auto b = transformBounds(i.bounds, view);
            const float edge = span * .5f + 2;
            if (b.max.x < -edge || b.min.x > edge || b.max.y < -edge || b.min.y > edge || b.max.z < -360 ||
                b.min.z > -1)
                continue;
            shadowBatches_[i.asset].push_back(i.transform);
        }
        rlDisableBackfaceCulling(); // Mirrored prefab transforms and thin boards also cast shadows.
        for (size_t i = 0; i < assets_.size(); ++i) {
            const auto &a = assets_[i];
            const auto &batch = shadowBatches_[i];
            if (batch.empty())
                continue;
            for (int j = a.first; j < a.first + a.count; ++j) {
                auto material = model_.materials[model_.meshMaterial[j]];
                if (material.maps[MATERIAL_MAP_ALBEDO].color.a < 255)
                    continue; // Glass and water transmit the sun; their planes must not black out interiors.
                material.shader = shadowShader_;
                DrawMeshInstanced(model_.meshes[j], material, batch.data(), int(batch.size()));
            }
        }
        rlDrawRenderBatchActive();
        rlEnableBackfaceCulling();
        EndMode3D();
        EndTextureMode();
        shadowFocus_ = focus;
        shadowSpan_ = span;
        shadowsDirty_ = false;
    }
    BeginTextureMode(shadowMap_);
    rlBindFramebuffer(RL_READ_FRAMEBUFFER, staticShadowMap_.id);
    rlBindFramebuffer(RL_DRAW_FRAMEBUFFER, shadowMap_.id);
    rlBlitFramebuffer(0, 0, ShadowSize, ShadowSize, 0, 0, ShadowSize, ShadowSize,
                      0x00000100); // GL_DEPTH_BUFFER_BIT
    rlEnableFramebuffer(shadowMap_.id);
    BeginMode3D(lightCamera);
    rlSetMatrixProjection(projection);
    rlDisableBackfaceCulling();
    for (const auto &i : instances_) {
        const auto &asset = assets_[i.asset];
        if (!i.animated || asset.unlit)
            continue;
        const auto b = transformBounds(i.bounds, rlGetMatrixModelview());
        const float edge = span * .5f + 2;
        if (b.max.x < -edge || b.min.x > edge || b.max.y < -edge || b.min.y > edge || b.max.z < -360 ||
            b.min.z > -1)
            continue;
        for (int mesh = asset.first; mesh < asset.first + asset.count; ++mesh) {
            auto material = model_.materials[model_.meshMaterial[mesh]];
            if (material.maps[MATERIAL_MAP_ALBEDO].color.a < 255)
                continue;
            material.shader = shadowShader_;
            DrawMeshInstanced(model_.meshes[mesh], material, &i.transform, 1);
        }
    }
    if (actors)
        actors(actorShadowShader_);
    rlDrawRenderBatchActive();
    rlEnableBackfaceCulling();
    EndMode3D();
    EndTextureMode();
    const int enabled = 1;
    const float texelDepth = texel / 359;
    for (auto shader : {shader_, actorShader_}) {
        SetShaderValueMatrix(shader, GetShaderLocation(shader, "lightVP"), lightVP);
        SetShaderValue(shader, GetShaderLocation(shader, "shadowEnabled"), &enabled, SHADER_UNIFORM_INT);
        SetShaderValue(shader, GetShaderLocation(shader, "shadowTexelDepth"), &texelDepth,
                       SHADER_UNIFORM_FLOAT);
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
        occluders_.clear();
        for (auto &b : batches_)
            b.clear();
        for (const auto &i : instances_) {
            const auto &b = i.bounds;
            Vector3 nearest{std::clamp(focus.x, b.min.x, b.max.x), focus.y,
                            std::clamp(focus.z, b.min.z, b.max.z)};
            const bool backdrop = document_.assets[i.asset].label.find("BackgroundCard") != std::string::npos;
            if (distance(focus, nearest) > 120 && !assets_[i.asset].unlit && !backdrop)
                continue;
            const auto &asset = assets_[i.asset];
            bool blocked = false;
            if (!asset.unlit && occlusion_.intersects(b))
                for (int mesh = asset.first; mesh < asset.first + asset.count && !blocked; ++mesh)
                    blocked = occlusion_.blocks(model_.meshes[mesh], i.transform);
            if (blocked)
                occluders_.push_back(&i);
            else
                batches_[i.asset].push_back(i.transform);
        }
    }
    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling(); // Original scene includes negative scales and two-sided materials.
    occlusion_.bind(shader_, false);
    if (glass)
        rlDisableDepthMask();
    for (size_t i = 0; i < assets_.size(); ++i) {
        const auto &a = assets_[i];
        const auto &batch = batches_[i];
        if (batch.empty())
            continue;
        SetShaderValue(shader_, GetShaderLocation(shader_, "unlit"), &a.unlit, SHADER_UNIFORM_INT);
        const auto &label = document_.assets[i].label;
        const int foliage =
            label.find("Tree_Clump") != std::string::npos || label.find("Birch") != std::string::npos;
        SetShaderValue(shader_, GetShaderLocation(shader_, "autumnFoliage"), &foliage, SHADER_UNIFORM_INT);
        for (int j = a.first; j < a.first + a.count; ++j) {
            auto &m = model_.materials[model_.meshMaterial[j]];
            if ((m.maps[MATERIAL_MAP_ALBEDO].color.a < 255) != glass)
                continue;
            const auto previous = m.maps[MATERIAL_MAP_METALNESS].texture;
            m.maps[MATERIAL_MAP_METALNESS].texture = shadowMap_.depth;
            DrawMeshInstanced(model_.meshes[j], m, batch.data(), int(batch.size()));
            m.maps[MATERIAL_MAP_METALNESS].texture = previous;
        }
    }
    if (glass)
        rlEnableDepthMask();
    rlEnableBackfaceCulling();
}
void TownScene::drawOccluders() {
    if (!loaded() || !occlusion_.enabled)
        return;
    std::sort(occluders_.begin(), occluders_.end(), [&](const Instance *a, const Instance *b) {
        return distance(mul(add(a->bounds.min, a->bounds.max), .5f), occlusion_.camera.position) >
               distance(mul(add(b->bounds.min, b->bounds.max), .5f), occlusion_.camera.position);
    });
    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    occlusion_.bind(shader_, true);
    const int unlit = 0;
    SetShaderValue(shader_, GetShaderLocation(shader_, "unlit"), &unlit, SHADER_UNIFORM_INT);
    for (const auto *instance : occluders_) {
        const auto &asset = assets_[instance->asset];
        const auto &label = document_.assets[instance->asset].label;
        const int foliage =
            label.find("Tree_Clump") != std::string::npos || label.find("Birch") != std::string::npos;
        SetShaderValue(shader_, GetShaderLocation(shader_, "autumnFoliage"), &foliage, SHADER_UNIFORM_INT);
        for (int j = asset.first; j < asset.first + asset.count; ++j) {
            auto &material = model_.materials[model_.meshMaterial[j]];
            const auto previous = material.maps[MATERIAL_MAP_METALNESS].texture;
            material.maps[MATERIAL_MAP_METALNESS].texture = shadowMap_.depth;
            DrawMeshInstanced(model_.meshes[j], material, &instance->transform, 1);
            material.maps[MATERIAL_MAP_METALNESS].texture = previous;
        }
    }
    rlEnableDepthMask();
    rlEnableBackfaceCulling();
}
} // namespace dw
