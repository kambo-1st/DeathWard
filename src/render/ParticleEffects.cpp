#include "render/ParticleEffects.hpp"
#include "platform/Assets.hpp"
#include "combat/Simulation.hpp"
#include <set>
#include "render/ShaderPlatform.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <stdexcept>

namespace dw {
namespace {
constexpr const char *Vertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;
uniform mat4 mvp;
uniform mat4 matNormal;
out vec3 normal;
out vec2 uv;
void main() {
    uv = vertexTexCoord;
    normal = normalize((matNormal * vec4(vertexNormal,0.)).xyz);
    gl_Position = mvp * vec4(vertexPosition,1.);
}
)GLSL";
constexpr const char *Fragment = R"GLSL(#version 330
in vec3 normal;
in vec2 uv;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float emission;
out vec4 finalColor;
void main() {
    // Emissive, but retain the original low-poly flame's facets.
    float facet = .82 + .18 * abs(dot(normalize(normal),normalize(vec3(.4,.7,.3))));
    finalColor = texture(texture0, uv) * vec4(colDiffuse.rgb * emission * facet,colDiffuse.a);
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
    const auto source = sourceAssetDirectory() / "particles";
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
        if (r.model.meshCount) {
            std::set<unsigned int> textures;
            for (int m = 0; m < r.model.materialCount; ++m) {
                const auto texture = r.model.materials[m].maps[MATERIAL_MAP_ALBEDO].texture;
                if (texture.id && texture.id != rlGetTextureIdDefault() && textures.insert(texture.id).second)
                    UnloadTexture(texture);
            }
            UnloadModel(r.model);
        }
        if (r.texture.id) UnloadTexture(r.texture);
    }
    if (shader_.id) UnloadShader(shader_);
    shader_ = {};
    resources_.clear(); bound_.clear(); particles_.clear(); lights_.clear();
    library_ = {};
    dustAnchors_.clear();
    townDustAnchors_.clear();
    dustReady_ = false;
    artDust = false;
    time_ = 0;
}
void ParticleEffects::bind(const TownDocument &document) {
    townDustAnchors_.clear();
    bound_.clear(); particles_.clear(); lights_.clear();
    time_ = 0;
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        if (i.id.starts_with("story-frontage-scrub-") || i.id.starts_with("story-rail-barricade-"))
            townDustAnchors_.push_back(Vector3Transform({0, .22f, 0}, i.transform));
        for (size_t a = 0; a < library_.attachments.size(); ++a)
            if (document.assets[i.asset].label == library_.attachments[a].label)
                bound_.push_back({n, a, i.transform, seedFor(i.id.empty() ? std::to_string(n) : i.id, a),
                    {{0, Vector3Transform(library_.attachments[a].offset, i.transform)}}});
    }
}
void ParticleEffects::animate(const ObjectAnimationSystem &animation) {
    const double nextTime = animation.time();
    for (auto &b : bound_) {
        if (b.instance < animation.poses().size()) b.transform = animation.poses()[b.instance].transform;
        const auto &a = library_.attachments[b.attachment];
        if (!a.trail) continue;
        const auto center = Vector3Transform(a.offset,b.transform);
        if (nextTime < time_ || (!b.trail.empty() && distance(center,b.trail.back().second) > 20))
            b.trail.clear(); // Editor reset or teleport starts a fresh plume.
        if (b.trail.empty() || nextTime > b.trail.back().first) b.trail.emplace_back(nextTime,center);
        while (b.trail.size() > 2 && (b.trail.size() > 512 ||
               nextTime - b.trail[1].first > library_.emitters[a.emitter].lifetime.y + .1))
            b.trail.pop_front();
    }
    time_ = nextTime;
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
            if (a.trail && !b.trail.empty()) {
                // Place each puff where the stack was when it emitted it. World
                // gravity/wind then act independently of the train's current pose.
                const double birth = time_ - p.age;
                Vector3 origin = b.trail.front().second;
                for (size_t n = 1; n < b.trail.size(); ++n) {
                    const auto &[ta, pa] = b.trail[n-1];
                    const auto &[tb, pb] = b.trail[n];
                    origin = Vector3Lerp(pa,pb,float(std::clamp((birth-ta)/(tb-ta),0.,1.)));
                    if (birth <= tb) break;
                }
                append(a.emitter,p,add(origin,mul(p.position,a.scale*worldScale)),a.scale*worldScale,view);
                continue;
            }
            const auto position = Vector3Transform(local, b.transform);
            const auto transform = MatrixMultiply(MatrixMultiply(MatrixMultiply(MatrixScale(size,size,size),
                MatrixRotateY(p.rotation)), MatrixTranslate(local.x,local.y,local.z)), b.transform);
            particles_.push_back({a.emitter, transform, position,
                {byte(p.color.x),byte(p.color.y),byte(p.color.z),byte(p.alpha)},
                size * worldScale, p.rotation * RAD2DEG, -Vector3Transform(position, view).z});
        }
    }
    if (artDust) {
        const auto e = std::find_if(library_.emitters.begin(), library_.emitters.end(),
                                    [](const auto &emitter) { return emitter.name == "canyondust"; });
        if (e != library_.emitters.end())
            for (size_t n = 0; n < townDustAnchors_.size(); n += 3) {
                const auto anchor = townDustAnchors_[n];
                if (distance(anchor, camera.target) > 65)
                    continue;
                for (auto p : ParticleLibrary::sample(*e, time_, 0x1866u + uint32_t(n * 101))) {
                    const auto position = add(anchor, p.position);
                    p.color = {.69f, .65f, .55f};
                    p.alpha *= .65f * std::clamp((distance(position, camera.target) - 2) / 5, 0.f, 1.f);
                    if (p.alpha > .001f)
                        append(size_t(e - library_.emitters.begin()), p, position, 1, view);
                }
            }
    }
    sort();
}
void ParticleEffects::sort() {
    // Alpha particles share one back-to-front list, even across different sources.
    std::stable_sort(particles_.begin(), particles_.end(), [](const auto &a, const auto &b) {
        return a.depth > b.depth;
    });
}
void ParticleEffects::append(size_t emitter, const ParticleSample &p, Vector3 position, float scale,
                             Matrix view, Vector3 direction) {
    if (particles_.size() >= 4096) return;
    const float size = p.size * scale;
    // Debris tumbles around all axes; directional flashes follow the shot.
    Matrix rotation = MatrixMultiply(MatrixRotateXYZ({p.rotation*.7f,p.rotation,p.rotation*.4f}),
        QuaternionToMatrix(QuaternionFromVector3ToVector3({0,1,0},Vector3Normalize(direction))));
    const auto transform = MatrixMultiply(MatrixMultiply(MatrixScale(size,size,size),rotation),
                                           MatrixTranslate(position.x,position.y,position.z));
    particles_.push_back({emitter,transform,position,
        {byte(p.color.x),byte(p.color.y),byte(p.color.z),byte(p.alpha)}, size,p.rotation*RAD2DEG,
        -Vector3Transform(position,view).z});
}
size_t ParticleEffects::count(const std::string &emitter) const {
    return size_t(std::count_if(particles_.begin(),particles_.end(),[&](const auto &p) {
        return library_.emitters[p.emitter].name == emitter;
    }));
}
std::optional<Box> ParticleEffects::bounds(const std::string &emitter) const {
    std::optional<Box> result;
    for (const auto &p : particles_) {
        if (library_.emitters[p.emitter].name != emitter) continue;
        if (!result) result = Box{p.position,p.position};
        result->min = Vector3Min(result->min,p.position);
        result->max = Vector3Max(result->max,p.position);
    }
    return result;
}
void ParticleEffects::prepareMission(const Simulation &run, const Camera3D &camera, Vector3 muzzle,
                                     float sandstorm) {
    particles_.clear(); lights_.clear();
    time_ = run.stats.duration;
    const auto view = GetCameraMatrix(camera);
    const auto find = [&](const std::string &name) {
        return std::find_if(library_.emitters.begin(),library_.emitters.end(),
                            [&](const auto &e) { return e.name == name; });
    };
    for (const auto &burst : run.particleBursts) {
        if (distance(burst.position,camera.target) > 80) continue;
        std::vector<std::string> layers;
        switch (burst.kind) {
        case ParticleEffect::PlayerMuzzle: case ParticleEffect::Muzzle: layers={"muzzle","gunsmoke"}; break;
        case ParticleEffect::Stone: layers={"stonechip","stonedust"}; break;
        case ParticleEffect::Wood: layers={"woodchip","wooddust"}; break;
        case ParticleEffect::Metal: layers={"spark"}; break;
        case ParticleEffect::Dirt: layers={"grit","dirtdust"}; break;
        case ParticleEffect::Flesh: layers={"flesh"}; break;
        case ParticleEffect::Explosion: layers={"blastfire","blastrock","blastember","blastsmoke"}; break;
        }
        for (const auto &name : layers) {
            const auto e = find(name);
            if (e == library_.emitters.end()) continue;
            const auto index = size_t(e-library_.emitters.begin());
            // Keep the very short flash on the animated revolver's actual muzzle.
            const auto origin = name == "muzzle" && burst.kind == ParticleEffect::PlayerMuzzle ? muzzle : burst.position;
            for (const auto &p : ParticleLibrary::burst(*e,burst.age,burst.seed ^ uint32_t(index*97),burst.direction)) {
                const auto position = add(origin,mul(p.position,burst.scale));
                if (position.y < .035f) continue;
                append(index,p,position,burst.scale,view,burst.direction);
            }
        }
    }
    if (run.arena.theme == MissionTheme::Canyon && run.arena.canyon) {
        if (!dustReady_ || dustSeed_ != run.arena.visualSeed || dustRoomCount_ != run.arena.roomCount()) {
            dustRoomCount_ = run.arena.roomCount();
            dustSeed_ = run.arena.visualSeed; dustReady_ = true; dustAnchors_.clear();
            Random rng(dustSeed_ ^ 0xd057cafeULL);
            for (const auto &room : run.arena.rooms)
                for (int n = 0; n < 3; ++n)
                    for (int attempt = 0; attempt < 20; ++attempt) {
                        Vector3 p{rng.real(room.bounds.min.x,room.bounds.max.x),.22f,
                                  rng.real(room.bounds.min.z,room.bounds.max.z)};
                        if (run.arena.contains(p) && !run.arena.canyon->blocked(p,2.2f)) {
                            dustAnchors_.push_back(p); break;
                        }
                    }
        }
        const auto e = find("canyondust");
        if (e != library_.emitters.end())
            for (size_t n = 0; n < dustAnchors_.size(); ++n) {
                if (distance(dustAnchors_[n],camera.target) > 55) continue;
                for (auto p : ParticleLibrary::sample(*e,time_,uint32_t(dustSeed_) ^ uint32_t(n*101))) {
                    auto position = add(dustAnchors_[n],p.position);
                    // Do not render clouds inside rocks, through sealed passages,
                    // or across the player. Dust is atmosphere, never a vision penalty.
                    if (!run.arena.contains(position) || run.arena.blocked(position,p.size*.5f)) continue;
                    p.alpha *= std::clamp((distance(position,run.player.position)-1.5f)/4.f,0.f,1.f);
                    if (p.alpha > .001f) append(size_t(e-library_.emitters.begin()),p,position,1,view);
                }
            }
    } else { dustReady_ = false; dustAnchors_.clear(); }
    if (sandstorm > 0)
        addSandstorm(camera, sandstorm, run.arena.visualSeed, [&](Vector3 p) {
            if (!run.arena.contains(p))
                return std::numeric_limits<float>::quiet_NaN();
            return run.arena.canyon ? run.arena.canyon->height(p.x, p.z) : 0.f;
        });
    else
        sort();
}
void ParticleEffects::addSandstorm(const Camera3D &camera, float strength, uint64_t worldSeed,
                                  const std::function<float(Vector3)> &ground) {
    if (strength <= 0)
        return;
    const auto storm = std::find_if(library_.emitters.begin(), library_.emitters.end(),
                                    [](const auto &e) { return e.name == "sandstorm"; });
    if (storm == library_.emitters.end()) {
        sort();
        return;
    }
    // Fixed world cells and a common wind keep clouds on course when walking or
    // orbiting. The upwind margin covers travel during the longest particle life.
    constexpr float cell = 12.f;
    const int cx = int(std::floor(camera.target.x / cell));
    const int cz = int(std::floor(camera.target.z / cell));
    const auto view = GetCameraMatrix(camera);
    const float gust = .78f + .22f * std::sin(float(time_) * .65f);
    for (int z = cz - 6; z <= cz + 5; ++z)
        for (int x = cx - 8; x <= cx + 5; ++x) {
            const uint32_t seed = uint32_t(worldSeed) ^ (uint32_t(x) * 73856093u) ^
                                  (uint32_t(z) * 19349663u) ^ 0x57a0d057u;
            const Vector3 anchor{(float(x) + .5f) * cell, 0, (float(z) + .5f) * cell};
            for (auto p : ParticleLibrary::sample(*storm, time_, seed)) {
                auto position = add(anchor, p.position);
                const float radius = std::hypot(position.x - camera.target.x, position.z - camera.target.z);
                if (radius > 54)
                    continue;
                const float height = ground(position);
                if (!std::isfinite(height))
                    continue;
                position.y = height + .7f + float(seed % 11) * .16f;
                const float edge = std::clamp((54 - radius) / 12, 0.f, 1.f);
                const float focusClear = .35f + .65f * std::clamp((radius - 1) / 5, 0.f, 1.f);
                p.alpha *= strength * gust * edge * focusClear;
                if (p.alpha > .003f)
                    append(size_t(storm - library_.emitters.begin()), p, position, 1, view);
            }
        }
    sort();
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
