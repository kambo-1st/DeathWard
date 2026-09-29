#pragma once
#include "world/TownDocument.hpp"

namespace dw {
enum class ParticleEffect { PlayerMuzzle, Muzzle, Stone, Wood, Metal, Dirt, Flesh, Explosion };
struct ParticleBurst {
    ParticleEffect kind = ParticleEffect::Stone;
    Vector3 position{}, direction{0, 1, 0};
    float age = 0, scale = 1;
    uint32_t seed = 1;
};
enum class ParticleKind { Mesh, Billboard, Additive };
struct ParticleKey {
    float time = 0, value = 0, inSlope = 0, outSlope = 0;
};
struct ParticleColorKey {
    float time = 0;
    Vector3 value{};
};
struct ParticleEmitter {
    std::string name, resource;
    ParticleKind kind = ParticleKind::Mesh;
    float rate = 8, gravity = 0, radius = .01f, noise = 0, frequency = 1, emission = 1;
    Vector2 lifetime{1, 1}, size{1, 1}, speed{}, spin{};
    Vector3 drift{};
    int burstMin = 0, burstMax = 0;
    float spread = 0;
    std::vector<ParticleKey> sizes, alphas;
    std::vector<ParticleColorKey> colors;
};
struct ParticleAttachment {
    std::string label;
    size_t emitter = 0;
    Vector3 offset{};
    float scale = 1, lightRange = 0;
    bool trail = false;
};
struct ParticleSample {
    Vector3 position{}, color{};
    float size = 0, alpha = 0, rotation = 0, age = 0;
};
// Evaluate only particles alive at the requested time. No frame RNG, accumulated
// integration error, startup ramp or dependence on whether the emitter is visible.
class ParticleLibrary {
  public:
    std::vector<ParticleEmitter> emitters;
    std::vector<ParticleAttachment> attachments;
    void load(const std::filesystem::path &directory);
    static float curve(const std::vector<ParticleKey> &keys, float time, bool hermite = true);
    static std::vector<ParticleSample> sample(const ParticleEmitter &emitter, double time, uint32_t seed);
    static std::vector<ParticleSample> burst(const ParticleEmitter &emitter, float age, uint32_t seed,
                                             Vector3 direction);
};
} // namespace dw
