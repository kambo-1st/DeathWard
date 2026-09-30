#pragma once
#include "core/Types.hpp"
namespace dw {
// A removable cloth accessory, attached to the existing torso animation.
class ArtWardrobe {
  public:
    ~ArtWardrobe() {
        unload();
    }
    ArtWardrobe() = default;
    ArtWardrobe(const ArtWardrobe &) = delete;
    ArtWardrobe &operator=(const ArtWardrobe &) = delete;
    void unload();
    void draw(const Model &rig, const std::vector<Transform> &pose, Matrix world, Shader shader,
              Texture2D shadow, int style);

  private:
    Model cloth_{};
    std::vector<Vector3> rest_;
    std::vector<float> weights_;
    int upper_ = -1, lower_ = -1, style_ = 0;
    void build(const Model &rig, int style);
};
} // namespace dw
