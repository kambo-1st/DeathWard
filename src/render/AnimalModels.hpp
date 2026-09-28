#pragma once
#include "world/Animals.hpp"

namespace dw {
// Shared textured meshes/clips. Every resident supplies its own pose clock and blending.
class AnimalModels {
  public:
    ~AnimalModels();
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

  private:
    struct Clip {
        std::vector<std::vector<Transform>> frames;
        float duration = 0;
    };
    struct Asset {
        Model model{};
        std::array<Clip, 3> clips;
        std::vector<Transform> world;
        float floor = 0;
        bool attempted = false;
    };
    std::array<Asset, size_t(AnimalKind::Count)> assets_;
    void unload(Asset &asset);
    Transform sample(const Clip &clip, double seconds, size_t bone) const;
};
} // namespace dw
