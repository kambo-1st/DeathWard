#include "render/TownScene.hpp"
#include "platform/Assets.hpp"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "render/WorldPalette.hpp"
#include "rlgl.h"
#include "world/TownBuildings.hpp"
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
uniform int artCloth;
uniform float artTime;
out vec2 uv;
out vec3 normal;
out vec3 world;
out vec4 color;
out float paletteVariation;
void main() {
    uv = vertexTexCoord;
    color = vertexColor;
    paletteVariation = 0.;
    vec3 position=vertexPosition;
    if (artCloth != 0) {
        float pinned=sin(vertexTexCoord.x*3.14159265)*sin(vertexTexCoord.y*3.14159265);
        position.y+=pinned*.075*sin(artTime*2.1+position.x*1.8+position.z);
    }
    world = (matModel * vec4(position,1.)).xyz;
    normal = normalize((matNormal * vec4(vertexNormal,0.)).xyz);
    gl_Position = mvp * vec4(position,1.);
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
uniform int interiorEnabled;
uniform int interiorArchitecture;
uniform mat4 interiorInverse;
uniform vec3 interiorMin;
uniform vec3 interiorMax;
uniform float interiorFloor;
uniform int lightCount;
uniform int sunIndex;
uniform int shadowEnabled;
uniform float shadowTexelDepth;
uniform vec3 lightPositions[8];
uniform vec3 lightDirections[8];
uniform vec3 lightColors[8];
uniform float lightRanges[8];
uniform int fireCount;
uniform vec3 firePositions[4];
uniform vec3 fireColors[4];
uniform float fireRanges[4];
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
    vec2 size = vec2(textureSize(shadowMap,0));
    vec2 at = p.xy*size-.5;
    vec2 fraction = fract(at);
    vec2 center = floor(at)+.5;
    float lit = 0.;
    // Interpolate comparisons across texels; interpolating depth itself would
    // invent occluders. Keep the 3x3 PCF footprint without its stepped edges.
    for (int x=-1; x<=2; ++x)
        for (int y=-1; y<=2; ++y) {
            float wx = x == -1 ? 1.-fraction.x : (x == 2 ? fraction.x : 1.);
            float wy = y == -1 ? 1.-fraction.y : (y == 2 ? fraction.y : 1.);
            lit += wx*wy*(p.z-bias <= texture(shadowMap,(center+vec2(x,y))/size).r ? 1. : 0.);
        }
    float edge = max(abs(p.x*2.-1.),abs(p.y*2.-1.));
    return mix(lit/9.,1.,smoothstep(.86,1.,edge));
}
void main() {
    if (interiorEnabled != 0) {
        vec3 local = (interiorInverse * vec4(world,1.)).xyz;
        float height = interiorFloor + (interiorArchitecture != 0 ? 1.25 : 2.65);
        if (local.x >= interiorMin.x && local.x <= interiorMax.x &&
            local.z >= interiorMin.z && local.z <= interiorMax.z && world.y > height) discard;
    }
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
    surface.rgb = artFinish(surface.rgb,world,n);
    // Warm ground bounce and a cool sky fill keep shaded porches readable.
    vec3 light = worldAmbient(n);
    if (artEnabled != 0) light=mix(vec3(.23,.225,.20),vec3(.45,.50,.54),n.y*.5+.5);
    for(int i=0;i<lightCount;i++) {
        vec3 d = lightDirections[i];
        float attenuation = worldSunAttenuation;
        if(lightRanges[i]>0.0) {
            vec3 delta = lightPositions[i]-world;
            d = delta/max(length(delta),.001);
            attenuation = pow(max(0.0,1.0-length(delta)/lightRanges[i]),2.0);
        }
        float direct = max(dot(n,d),0.0);
        float shade = i == sunIndex && direct > 0. ? visibility(n,d) : 1.;
        light += direct*lightColors[i]*attenuation*shade;
    }
    for(int i=0;i<fireCount;i++) {
        vec3 delta = firePositions[i]-world;
        float attenuation = pow(max(0.,1.-length(delta)/fireRanges[i]),2.);
        light += fireColors[i]*attenuation*max(.12,dot(n,normalize(delta+vec3(.0001))));
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
    const auto source = sourceAssetDirectory() / hubFolder(hub);
    if (std::filesystem::is_regular_file(source / "town.scene"))
        return source; // Editor saves in the checkout survive rebuilds; shipped builds use their own pack.
    auto packaged = std::filesystem::path(GetApplicationDirectory()) / "assets" / hubFolder(hub);
    return std::filesystem::is_regular_file(packaged / "town.scene") ? packaged : source;
}
TownScene::~TownScene() {
    unload();
}
void TownScene::unload() {
    flags_.clear();visibleFlags_.clear();
    effects_.unload();
    art_.unload();
    artEnabled_ = false;
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
    interior_.reset();
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
            assets_.push_back({a.first, a.count, a.unlit, a.bounds,
                a.name.starts_with("redstone_road_") || a.name == "redstone_gate_junction"});
        for (const auto &i : document_.instances) {
            const auto &asset = document_.assets[i.asset];
            instances_.push_back({i.asset, i.transform,
                transformBounds(assets_[i.asset].bounds, i.transform),
                i.animated() || buildingDoor(asset) || doorGlass(asset), i.castsShadow});
        }
#ifdef __EMSCRIPTEN__
        const auto modelFile = std::filesystem::path("/assets") / directory.filename() / "town.glb";
#else
        const auto modelFile = directory / "town.glb";
#endif
        model_ = LoadModel(modelFile.string().c_str());
        if (model_.meshCount != meshCount)
            throw std::runtime_error("Town model/catalog mismatch");
        bindFlags();
        auto source = withWorldPalette(Fragment);
        source.insert(source.find("float visibility"), RedstoneArt::shaderFunctions());
        const auto fragment = withPlayerOcclusion(source.c_str());
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
        shader_.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader_, "artContact");
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
        if (effects_.load()) effects_.bind(document_);
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
    art_.unload();
    if (artEnabled_)
        art_.build(document_, model_);
    effects_.bind(document_);
    updateLights();
    instances_.clear();
    occluders_.clear();
    interior_.reset();
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        const auto &asset = document.assets[i.asset];
        instances_.push_back({i.asset, i.transform, document.bounds(n),
            i.animated() || buildingDoor(asset) || doorGlass(asset), i.castsShadow});
    }
    bindFlags();
}
void TownScene::bindFlags() {
    flags_.clear();visibleFlags_.clear();
    for(size_t n=0;n<instances_.size();++n) {
        auto &instance=instances_[n];instance.flag=-1;
        const auto &asset=document_.assets[instance.asset];
        if(!flagFabric(asset))continue;
        instance.flag=int(flags_.size());instance.animated=true;
        const auto &id=document_.instances[n].id;
        flags_.push_back(std::make_unique<FlagCloth>(model_.meshes[asset.first],flagSeed(id.empty()?std::to_string(n):id)));
    }
    prepareFlags(0);
}
void TownScene::prepareFlags(double time,float storm) {
    for(auto &instance:instances_)if(instance.flag>=0) {
        auto &flag=*flags_[size_t(instance.flag)];flag.update(instance.transform,time,storm);
        instance.bounds=objectBounds(flag.bounds(),instance.transform);
    }
}
const Mesh &TownScene::instanceMesh(const Instance &instance,int mesh) const {
    return instance.flag>=0?flags_[size_t(instance.flag)]->mesh():model_.meshes[mesh];
}
void TownScene::applyAnimation(const ObjectAnimationSystem &animation) {
    const auto &poses = animation.poses();
    if (poses.size() != instances_.size())
        return;
    effects_.animate(animation);
    occluders_.clear();
    for (size_t n = 0; n < poses.size(); ++n) {
        instances_[n].animated = poses[n].animated || instances_[n].flag>=0;
        if (!instances_[n].animated)
            continue;
        instances_[n].transform = poses[n].transform;
        instances_[n].bounds = instances_[n].flag>=0
            ?objectBounds(flags_[size_t(instances_[n].flag)]->bounds(),instances_[n].transform)
            :poses[n].bounds;
    }
}
void TownScene::setArtPoc(bool enabled) {
    enabled = enabled && loaded() && RedstoneArt::supports(document_);
    if (enabled == artEnabled_)
        return;
    artEnabled_ = enabled;
    effects_.artDust = enabled;
    if (enabled && !art_.ready())
        art_.build(document_, model_);
    updateLights();
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
        if (artEnabled_) {
            lights.front().direction = Vector3Normalize({-.58f, .48f, .66f});
            lights.front().color = {1.f, .94f, .81f};
            lights.front().intensity = 1.22f;
        }
        if(daylight_==1) {
            lights.front().direction=Vector3Normalize({-.85f,.24f,.47f});
            lights.front().color={1.f,.66f,.40f};lights.front().intensity=1.05f;
        } else if(daylight_==2) {
            lights.front().direction=Vector3Normalize({.72f,.52f,-.35f});
            lights.front().color={1.f,.92f,.79f};lights.front().intensity=1.16f;
        }
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
    const int count = int(positions.size()), disabled = 0, art = artEnabled_;
    for (auto shader : {shader_, actorShader_}) {
        SetShaderValue(shader, GetShaderLocation(shader, "artEnabled"), &art, SHADER_UNIFORM_INT);
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
void TownScene::setDaylight(int phase) {
    phase=std::clamp(phase,0,2);
    if(phase==daylight_)return;
    daylight_=phase;
    if(loaded())updateLights();
}
void TownScene::updateEffectLights(const Camera3D &camera) {
    effects_.prepare(camera);
    const auto &lights = effects_.lights();
    const int count = int(lights.size());
    Vector3 positions[4]{}, colors[4]{};
    float ranges[4]{};
    for (int i = 0; i < count; ++i) {
        positions[i] = lights[size_t(i)].position;
        colors[i] = lights[size_t(i)].color;
        ranges[i] = lights[size_t(i)].range;
    }
    for (auto shader : {shader_, actorShader_}) {
        SetShaderValue(shader, GetShaderLocation(shader, "fireCount"), &count, SHADER_UNIFORM_INT);
        if (!count) continue;
        SetShaderValueV(shader, GetShaderLocation(shader, "firePositions"), positions, SHADER_UNIFORM_VEC3, count);
        SetShaderValueV(shader, GetShaderLocation(shader, "fireColors"), colors, SHADER_UNIFORM_VEC3, count);
        SetShaderValueV(shader, GetShaderLocation(shader, "fireRanges"), ranges, SHADER_UNIFORM_FLOAT, count);
    }
}
void TownScene::prepareLighting(const Camera3D &camera, const std::function<void(Shader)> &actors) {
    updateEffectLights(camera);
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
            if (!i.castsShadow || i.animated || asset.unlit || asset.label.find("BackgroundCard") != std::string::npos)
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
        if (!i.castsShadow || !i.animated || asset.unlit)
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
            DrawMeshInstanced(instanceMesh(i,mesh), material, &i.transform, 1);
        }
    }
    if (actors)
        actors(actorShadowShader_);
    if (artEnabled_)
        art_.draw(actorShadowShader_, {}, effects_.time(), true);
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
void TownScene::setPlayerOcclusion(const Camera3D &camera, Vector3 player, bool enabled) {
    occlusion_.set(camera,player);
    occlusion_.enabled=enabled;
    interior_.reset();
    if(!enabled)return;
    float best=std::numeric_limits<float>::infinity();
    for(size_t n=0;n<instances_.size();++n) {
        const auto &i=instances_[n];
        const auto &a=document_.assets[i.asset];
        if(!buildingShell(a))continue;
        const auto inverse=MatrixInvert(i.transform);
        const auto p=Vector3Transform(player,inverse);
        if(p.x<=a.bounds.min.x+.35f || p.x>=a.bounds.max.x-.35f ||
           p.z<=a.bounds.min.z+.35f || p.z>=a.bounds.max.z-.35f ||
           p.y<a.bounds.min.y || p.y>a.bounds.max.y-1.2f)continue;
        const float area=(a.bounds.max.x-a.bounds.min.x)*(a.bounds.max.z-a.bounds.min.z);
        if(area>=best)continue;
        best=area;interior_=n;interiorInverse_=inverse;
        interiorBounds_={sub(a.bounds.min,{.3f,0,.3f}),add(a.bounds.max,{.3f,0,.3f})};
        interiorWorldBounds_=objectBounds(interiorBounds_,i.transform);
        interiorFloor_=player.y-.85f;
    }
}
bool TownScene::belongsToInterior(const Instance &i) const {
    if(!interior_)return false;
    return i.bounds.min.x<=interiorWorldBounds_.max.x && i.bounds.max.x>=interiorWorldBounds_.min.x &&
           i.bounds.min.z<=interiorWorldBounds_.max.z && i.bounds.max.z>=interiorWorldBounds_.min.z &&
           buildingGeometry(document_.assets[i.asset]);
}
void TownScene::bindInterior(bool architecture) {
    const int enabled=interior_.has_value(), structure=architecture;
    SetShaderValue(shader_,GetShaderLocation(shader_,"interiorEnabled"),&enabled,SHADER_UNIFORM_INT);
    if(!enabled)return;
    SetShaderValue(shader_,GetShaderLocation(shader_,"interiorArchitecture"),&structure,SHADER_UNIFORM_INT);
    SetShaderValueMatrix(shader_,GetShaderLocation(shader_,"interiorInverse"),interiorInverse_);
    SetShaderValue(shader_,GetShaderLocation(shader_,"interiorMin"),&interiorBounds_.min,SHADER_UNIFORM_VEC3);
    SetShaderValue(shader_,GetShaderLocation(shader_,"interiorMax"),&interiorBounds_.max,SHADER_UNIFORM_VEC3);
    SetShaderValue(shader_,GetShaderLocation(shader_,"interiorFloor"),&interiorFloor_,SHADER_UNIFORM_FLOAT);
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
            const auto hit = GetRayCollisionMesh(ray, instanceMesh(i,mesh), i.transform);
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
        visibleFlags_.clear();
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
            if (!asset.unlit && !asset.groundOverlay && !belongsToInterior(i) && occlusion_.intersects(b))
                for (int mesh = asset.first; mesh < asset.first + asset.count && !blocked; ++mesh)
                    blocked = occlusion_.blocks(instanceMesh(i,mesh), i.transform);
            if (blocked)
                occluders_.push_back(&i);
            else if(i.flag>=0)
                visibleFlags_.push_back(&i);
            else
                batches_[i.asset].push_back(i.transform);
        }
    }
    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling(); // Original scene includes negative scales and two-sided materials.
    occlusion_.bind(shader_, false);
    // Feathered dirt blends over opaque soil before actors and fading rocks.
    // Drawing it with glass afterward would paint over transparent foreground rocks.
    for (int pass = 0; pass < (glass ? 1 : 2); ++pass) {
        const bool overlay = !glass && pass == 1;
        if (glass)
            rlDisableDepthMask();
        for (size_t i = 0; i < assets_.size(); ++i) {
            const auto &a = assets_[i];
            const auto &batch = batches_[i];
            if (batch.empty() || a.groundOverlay != overlay)
                continue;
            const int surface = RedstoneArt::surface(document_.assets[i]);
            SetShaderValue(shader_, GetShaderLocation(shader_, "artSurface"), &surface, SHADER_UNIFORM_INT);
            SetShaderValue(shader_, GetShaderLocation(shader_, "unlit"), &a.unlit, SHADER_UNIFORM_INT);
            bindInterior(buildingGeometry(document_.assets[i]));
            const auto &label = document_.assets[i].label;
            const int foliage =
                label.find("Tree_Clump") != std::string::npos || label.find("Birch") != std::string::npos;
            SetShaderValue(shader_, GetShaderLocation(shader_, "autumnFoliage"), &foliage, SHADER_UNIFORM_INT);
            for (int j = a.first; j < a.first + a.count; ++j) {
                auto &m = model_.materials[model_.meshMaterial[j]];
                if (!overlay && (m.maps[MATERIAL_MAP_ALBEDO].color.a < 255) != glass)
                    continue;
                const auto previous = m.maps[MATERIAL_MAP_METALNESS].texture;
                const auto contact = m.maps[MATERIAL_MAP_EMISSION].texture;
                m.maps[MATERIAL_MAP_EMISSION].texture = art_.contact();
                m.maps[MATERIAL_MAP_METALNESS].texture = shadowMap_.depth;
                DrawMeshInstanced(model_.meshes[j], m, batch.data(), int(batch.size()));
                m.maps[MATERIAL_MAP_METALNESS].texture = previous;
                m.maps[MATERIAL_MAP_EMISSION].texture = contact;
            }
        }
        if(!overlay)for(const auto *instance:visibleFlags_) {
            const auto &asset=assets_[instance->asset];
            auto &material=model_.materials[model_.meshMaterial[asset.first]];
            if((material.maps[MATERIAL_MAP_ALBEDO].color.a<255)!=glass)continue;
            const int zero=0,surface=RedstoneArt::surface(document_.assets[instance->asset]);
            SetShaderValue(shader_,GetShaderLocation(shader_,"unlit"),&zero,SHADER_UNIFORM_INT);
            SetShaderValue(shader_,GetShaderLocation(shader_,"autumnFoliage"),&zero,SHADER_UNIFORM_INT);
            SetShaderValue(shader_,GetShaderLocation(shader_,"artSurface"),&surface,SHADER_UNIFORM_INT);
            bindInterior(false);
            const auto previous=material.maps[MATERIAL_MAP_METALNESS].texture;
            const auto contact=material.maps[MATERIAL_MAP_EMISSION].texture;
            material.maps[MATERIAL_MAP_METALNESS].texture=shadowMap_.depth;
            material.maps[MATERIAL_MAP_EMISSION].texture=art_.contact();
            DrawMeshInstanced(instanceMesh(*instance,asset.first),material,&instance->transform,1);
            material.maps[MATERIAL_MAP_METALNESS].texture=previous;
            material.maps[MATERIAL_MAP_EMISSION].texture=contact;
        }
        if (glass)
            rlEnableDepthMask();
    }
    rlEnableBackfaceCulling();
    if (artEnabled_ && !glass)
        art_.draw(actorShader_, shadowMap_.depth, effects_.time());
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
        const int surface = RedstoneArt::surface(document_.assets[instance->asset]);
        SetShaderValue(shader_, GetShaderLocation(shader_, "artSurface"), &surface, SHADER_UNIFORM_INT);
        bindInterior(buildingGeometry(document_.assets[instance->asset]));
        const auto &label = document_.assets[instance->asset].label;
        const int foliage =
            label.find("Tree_Clump") != std::string::npos || label.find("Birch") != std::string::npos;
        SetShaderValue(shader_, GetShaderLocation(shader_, "autumnFoliage"), &foliage, SHADER_UNIFORM_INT);
        for (int j = asset.first; j < asset.first + asset.count; ++j) {
            auto &material = model_.materials[model_.meshMaterial[j]];
            const auto previous = material.maps[MATERIAL_MAP_METALNESS].texture;
            const auto contact = material.maps[MATERIAL_MAP_EMISSION].texture;
            material.maps[MATERIAL_MAP_EMISSION].texture = art_.contact();
            material.maps[MATERIAL_MAP_METALNESS].texture = shadowMap_.depth;
            DrawMeshInstanced(instanceMesh(*instance,j), material, &instance->transform, 1);
            material.maps[MATERIAL_MAP_EMISSION].texture = contact;
            material.maps[MATERIAL_MAP_METALNESS].texture = previous;
        }
    }
    rlEnableDepthMask();
    rlEnableBackfaceCulling();
}
} // namespace dw
