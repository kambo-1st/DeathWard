#pragma once
#include "core/Types.hpp"
#include <filesystem>
namespace dw {
// One shared mesh and three locomotion/idle slots, sampled independently by each resident.
class SkinnedModel {
  public:
    ~SkinnedModel();
    SkinnedModel() = default;
    SkinnedModel(const SkinnedModel &) = delete;
    SkinnedModel &operator=(const SkinnedModel &) = delete;
    bool load(const std::filesystem::path &path, bool alternateIdle = false);
    void unload();
    bool loaded() const { return asset_.model.meshCount > 0; }
    bool attempted() const { return asset_.attempted; }
    bool pose(double phase, float walking, float alternate = 0);
    void draw(Vector3 position, Vector3 facing, float scale, Shader shader = {}, Texture2D shadowMap = {});
    Box bounds(Vector3 position, Vector3 facing, float scale) const;
    const Model &model() const { return asset_.model; }
    const std::vector<Transform> &bonePose() const { return asset_.world; }
    static void applyPose(Model model, const Transform *pose);
    static void correctAnimationScale(ModelAnimation &animation);
  private:
    struct Clip { std::vector<std::vector<Transform>> frames; float duration = 0; };
    struct Asset {
        Model model{};
        std::array<Clip, 3> clips;
        std::vector<Transform> world;
        float floor = 0;
        bool attempted = false;
    } asset_;
    void unload(Asset &asset);
    Transform sample(const Clip &clip, double seconds, size_t bone) const;
};
}
