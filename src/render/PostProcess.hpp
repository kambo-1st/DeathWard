#pragma once
#include "raylib.h"

namespace dw {
// Owns the world-only render targets. UI is drawn after end(), in ordinary screen space.
class PostProcess {
  public:
    ~PostProcess();
    PostProcess() = default;
    PostProcess(const PostProcess &) = delete;
    PostProcess &operator=(const PostProcess &) = delete;
    // A positive focus distance enables depth fog around the 3D camera's focal plane.
    void begin(Color background, float focusDistance = 0);
    void end();
    void unload();
    bool ready() const {
        return scene_.id && bloom_[0].id && bloom_[1].id && composite_.id && filter_.id;
    }

  private:
    RenderTexture2D scene_{}, bloom_[2]{};
    Shader composite_{}, filter_{};
    int width_ = 0, height_ = 0;
    float focusDistance_ = 0;
    bool active_ = false;
    void resize(int width, int height);
    void filter(Texture2D source, RenderTexture2D target, int extract, Vector2 direction);
};
} // namespace dw
