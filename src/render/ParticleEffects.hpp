#pragma once
#include "world/ObjectAnimation.hpp"
#include "world/Particles.hpp"
#include <deque>
#include <functional>
#include <optional>

namespace dw {
class Simulation;
struct ParticleLight {
    Vector3 position{}, color{};
    float range = 0;
};
class ParticleEffects {
  public:
    ~ParticleEffects() { unload(); }
    ParticleEffects() = default;
    ParticleEffects(const ParticleEffects &) = delete;
    ParticleEffects &operator=(const ParticleEffects &) = delete;
    static std::filesystem::path assetDirectory();
    bool load(const std::filesystem::path &directory = assetDirectory());
    void unload();
    void bind(const TownDocument &document);
    void animate(const ObjectAnimationSystem &animation);
    void prepare(const Camera3D &camera);
    bool artDust = false;
    void prepareMission(const Simulation &run, const Camera3D &camera, Vector3 muzzle, float sandstorm = 0);
    void addSandstorm(const Camera3D &camera, float strength, uint64_t seed,
                      const std::function<float(Vector3)> &ground);
    void draw(const Camera3D &camera);
    size_t attachmentCount() const { return bound_.size(); }
    size_t particleCount() const { return particles_.size(); }
    bool loaded() const { return !resources_.empty(); }
    double time() const { return time_; }
    size_t count(const std::string &emitter) const;
    std::optional<Box> bounds(const std::string &emitter) const;
    const std::vector<ParticleLight> &lights() const { return lights_; }

  private:
    struct Resource { Model model{}; Texture2D texture{}; };
    struct Bound {
        size_t instance = 0, attachment = 0;
        Matrix transform{};
        uint32_t seed = 1;
        std::deque<std::pair<double, Vector3>> trail;
    };
    struct DrawParticle {
        size_t emitter = 0;
        Matrix transform{};
        Vector3 position{};
        Color color{};
        float size = 1, rotation = 0, depth = 0;
    };
    ParticleLibrary library_;
    std::vector<Resource> resources_;
    std::vector<Bound> bound_;
    std::vector<DrawParticle> particles_;
    std::vector<ParticleLight> lights_;
    Shader shader_{};
    int emissionLocation_ = -1;
    double time_ = 0;
    uint64_t dustSeed_ = 0;
    int dustRoomCount_ = 0;
    bool dustReady_ = false;
    std::vector<Vector3> dustAnchors_, townDustAnchors_;
    void append(size_t emitter, const ParticleSample &sample, Vector3 position, float scale,
                Matrix view, Vector3 direction = {0,1,0});
    void sort();
};
} // namespace dw
