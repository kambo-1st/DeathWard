#pragma once
#include "world/Animals.hpp"
#include "render/SkinnedModel.hpp"

namespace dw {
// Shared textured meshes/clips. Every resident supplies its own pose clock and blending.
class AnimalModels {
  public:
    ~AnimalModels() = default;
    AnimalModels() = default;
    AnimalModels(const AnimalModels &) = delete;
    AnimalModels &operator=(const AnimalModels &) = delete;
    bool load(AnimalKind kind, const std::filesystem::path &path);
    void unload();
    bool loaded(AnimalKind kind) const;
    void prepare(const Animals &animals);
    void draw(const Animals &animals, Shader shader = {}, Texture2D shadowMap = {});
    void draw(const Animal &animal, Shader shader = {}, Texture2D shadowMap = {});
    bool pose(const Animal &animal);
    const Model &model(AnimalKind kind) const;
    const std::vector<Transform> &bonePose(AnimalKind kind) const;
    static std::filesystem::path assetDirectory();
    // Apply a world-space skeletal pose, including nonuniform bone scales.
    static void applyPose(Model model, const Transform *pose) { SkinnedModel::applyPose(model, pose); }
    static void correctAnimationScale(ModelAnimation &animation) { SkinnedModel::correctAnimationScale(animation); }

  private:
    std::array<SkinnedModel, size_t(AnimalKind::Count)> models_;
};
} // namespace dw
