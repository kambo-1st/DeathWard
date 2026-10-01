#pragma once
#include "raylib.h"
#include <functional>

namespace dw {
// Owns the world-only render targets. UI is drawn after end(), in ordinary screen space.
class PostProcess {
  public:
    ~PostProcess();
    PostProcess() = default;
    PostProcess(const PostProcess &) = delete;
    PostProcess &operator=(const PostProcess &) = delete;
    // A positive focus distance enables depth fog around the 3D camera's focal plane.
    void begin(Color background, float focusDistance = 0, bool artPoc = false);
    // Call inside BeginMode3D, before drawing models, to capture the world camera.
    // begin() resets the effect so menus and other views cannot inherit old weather.
    void sandstorm(float strength, float time);
    void end();
    // After end(): outline only silhouette edges hidden behind the rendered world depth.
    void outlineOccluded(const Camera3D &camera, const std::function<void()> &drawModels);
    void unload();
    bool ready() const {
        return scene_.id && bloom_[0].id && bloom_[1].id && composite_.id && filter_.id;
    }

  private:
    RenderTexture2D scene_{}, bloom_[2]{};
    Shader composite_{}, filter_{};
    RenderTexture2D silhouette_{};
    Shader silhouetteShader_{}, outlineShader_{};
    int width_ = 0, height_ = 0;
    float focusDistance_ = 0;
    float sandstorm_ = 0, weatherTime_ = 0;
    Matrix inverseViewProjection_{};
    bool active_ = false, artPoc_ = false;
    bool outlineAttempted_ = false;
    void resize(int width, int height);
    void filter(Texture2D source, RenderTexture2D target, int extract, Vector2 direction);
};
} // namespace dw
