#include "render/ParticleEffects.hpp"
#include "render/ShaderPlatform.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <stdexcept>

namespace dw {
namespace {
constexpr const char *Vertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec3 vertexNormal;
uniform mat4 mvp;
uniform mat4 matNormal;
out vec3 normal;
void main() {
    normal = normalize((matNormal * vec4(vertexNormal,0.)).xyz);
    gl_Position = mvp * vec4(vertexPosition,1.);
}
)GLSL";
constexpr const char *Fragment = R"GLSL(#version 330
in vec3 normal;
uniform vec4 colDiffuse;
uniform float emission;
out vec4 finalColor;
void main() {
    // Emissive, but retain the original low-poly flame's facets.
    float facet = .82 + .18 * abs(dot(normalize(normal),normalize(vec3(.4,.7,.3))));
    finalColor = vec4(colDiffuse.rgb * emission * facet,colDiffuse.a);
}
)GLSL";
float scaleOf(Matrix m) {
    return std::max({Vector3Length({m.m0,m.m1,m.m2}), Vector3Length({m.m4,m.m5,m.m6}),
                     Vector3Length({m.m8,m.m9,m.m10})});
}
uint32_t seedFor(const std::string &id, size_t n) {
    uint32_t seed = 2166136261u;
    for (unsigned char c : id) seed = (seed ^ c) * 16777619u;
    return seed ^ (uint32_t(n) * 0x9e3779b9u);
}
unsigned char byte(float f) { return static_cast<unsigned char>(std::clamp(f, 0.f, 1.f) * 255); }
} // namespace
std::filesystem::path ParticleEffects::assetDirectory() {
    const auto source = std::filesystem::path(DEATHWARD_ASSET_DIR) / "particles";
    if (std::filesystem::is_regular_file(source / "fire.particles")) return source;
    return std::filesystem::path(GetApplicationDirectory()) / "assets/particles";
}
bool ParticleEffects::load(const std::filesystem::path &directory) {
    unload();
    try {
        library_.load(directory);
        shader_ = loadWorldShader(Vertex, Fragment);
        if (!shader_.id || shader_.id == rlGetShaderIdDefault())
            throw std::runtime_error("Particle shader failed to compile");
        emissionLocation_ = GetShaderLocation(shader_, "emission");
        for (const auto &e : library_.emitters) {
            resources_.emplace_back();
            auto &r = resources_.back();
            const auto path = (directory / e.resource).string();
            if (e.kind == ParticleKind::Mesh) {
                r.model = LoadModel(path.c_str());
                if (!r.model.meshCount) throw std::runtime_error("Missing particle mesh: " + path);
            } else {
                r.texture = LoadTexture(path.c_str());
                if (!r.texture.id) throw std::runtime_error("Missing particle texture: " + path);
                GenTextureMipmaps(&r.texture);
                SetTextureFilter(r.texture, TEXTURE_FILTER_TRILINEAR);
                SetTextureWrap(r.texture, TEXTURE_WRAP_CLAMP);
            }
        }
        return true;
    } catch (const std::exception &e) {
        TraceLog(LOG_ERROR, "PARTICLES: %s", e.what());
        unload();
        return false;
    }
}
void ParticleEffects::unload() {
    for (auto &r : resources_) {
        if (r.model.meshCount) UnloadModel(r.model);
        if (r.texture.id) UnloadTexture(r.texture);
    }
    if (shader_.id) UnloadShader(shader_);
    shader_ = {};
    resources_.clear(); bound_.clear(); particles_.clear(); lights_.clear();
    library_ = {};
    time_ = 0;
}
void ParticleEffects::bind(const TownDocument &document) {
    bound_.clear(); particles_.clear(); lights_.clear();
    time_ = 0;
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        for (size_t a = 0; a < library_.attachments.size(); ++a)
            if (document.assets[i.asset].label == library_.attachments[a].label)
                bound_.push_back({n, a, i.transform, seedFor(i.id.empty() ? std::to_string(n) : i.id, a)});
    }
}
void ParticleEffects::animate(const ObjectAnimationSystem &animation) {
    time_ = animation.time();
    for (auto &b : bound_)
        if (b.instance < animation.poses().size()) b.transform = animation.poses()[b.instance].transform;
}
void ParticleEffects::prepare(const Camera3D &camera) {
    particles_.clear(); lights_.clear();
    std::vector<std::pair<float, size_t>> visible;
    const auto view = GetCameraMatrix(camera);
    for (size_t n = 0; n < bound_.size(); ++n) {
        const auto &b = bound_[n];
        const auto center = Vector3Transform(library_.attachments[b.attachment].offset, b.transform);
        const float d = distance(camera.target, center);
        if (d < 100) visible.emplace_back(d, n);
    }
    std::sort(visible.begin(), visible.end());
    for (const auto &[d, index] : visible) {
        (void)d;
        if (particles_.size() >= 4096) break;
        const auto &b = bound_[index];
        const auto &a = library_.attachments[b.attachment];
        const auto center = Vector3Transform(a.offset, b.transform);
        const float worldScale = scaleOf(b.transform);
        if (a.lightRange > 0 && lights_.size() < 4) {
            const float phase = float(b.seed % 1024);
            const float flicker = 1.65f + .18f * std::sin(float(time_ * 7.1) + phase) +
                                  .11f * std::sin(float(time_ * 13.7) + phase * .37f);
            lights_.push_back({add(center,{0,.32f*worldScale,0}), mul({1,.32f,.065f},flicker),
                               a.lightRange * worldScale});
        }
        const auto &e = library_.emitters[a.emitter];
        for (const auto &p : ParticleLibrary::sample(e, time_, b.seed)) {
            if (particles_.size() >= 4096) break;
            const float size = p.size * a.scale;
            const auto local = add(a.offset, mul(p.position, a.scale));
            const auto position = Vector3Transform(local, b.transform);
            const auto transform = MatrixMultiply(MatrixMultiply(MatrixMultiply(MatrixScale(size,size,size),
                MatrixRotateY(p.rotation)), MatrixTranslate(local.x,local.y,local.z)), b.transform);
            particles_.push_back({a.emitter, transform, position,
                {byte(p.color.x),byte(p.color.y),byte(p.color.z),byte(p.alpha)},
                size * worldScale, p.rotation * RAD2DEG, -Vector3Transform(position, view).z});
        }
    }
    // Alpha particles share one back-to-front list, even across different fires.
    std::stable_sort(particles_.begin(), particles_.end(), [](const auto &a, const auto &b) {
        return a.depth > b.depth;
    });
}
void ParticleEffects::draw(const Camera3D &camera) {
    if (particles_.empty()) return;
    rlDrawRenderBatchActive();
    rlDisableDepthMask(); // Keep depth testing: walls, logs and characters still cover the fire.
    rlDisableBackfaceCulling();
    for (bool additive : {false, true}) {
        BeginBlendMode(additive ? BLEND_ADDITIVE : BLEND_ALPHA);
        for (const auto &p : particles_) {
            const auto &e = library_.emitters[p.emitter];
            if ((e.kind == ParticleKind::Additive) != additive) continue;
            const auto &r = resources_[p.emitter];
            if (e.kind == ParticleKind::Mesh) {
                rlDrawRenderBatchActive();
                SetShaderValue(shader_, emissionLocation_, &e.emission, SHADER_UNIFORM_FLOAT);
                for (int m = 0; m < r.model.meshCount; ++m) {
                    auto material = r.model.materials[r.model.meshMaterial[m]];
                    material.shader = shader_;
                    material.maps[MATERIAL_MAP_ALBEDO].color = p.color;
                    DrawMesh(r.model.meshes[m], material, p.transform);
                }
            } else {
                DrawBillboardPro(camera, r.texture, {0,0,float(r.texture.width),float(r.texture.height)},
                    p.position, camera.up, {p.size,p.size}, {p.size*.5f,p.size*.5f}, p.rotation, p.color);
            }
        }
        EndBlendMode();
    }
    rlDrawRenderBatchActive();
    rlEnableBackfaceCulling();
    rlEnableDepthMask();
}
} // namespace dw
