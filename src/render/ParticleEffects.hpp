#pragma once
#include "world/ObjectAnimation.hpp"
#include "world/Particles.hpp"

namespace dw {
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
    void draw(const Camera3D &camera);
    size_t attachmentCount() const { return bound_.size(); }
    size_t particleCount() const { return particles_.size(); }
    bool loaded() const { return !resources_.empty(); }
    double time() const { return time_; }
    const std::vector<ParticleLight> &lights() const { return lights_; }

  private:
    struct Resource { Model model{}; Texture2D texture{}; };
    struct Bound {
        size_t instance = 0, attachment = 0;
        Matrix transform{};
        uint32_t seed = 1;
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
};
} // namespace dw
