#pragma once
#include "core/Types.hpp"
#include <functional>
#include <string>

namespace dw {
// One sun and one depth field shared by generated terrain, props and actors.
// Static casters are cached; animated casters are composited every frame.
class MissionLighting {
  public:
    ~MissionLighting();
    MissionLighting() = default;
    MissionLighting(const MissionLighting &) = delete;
    MissionLighting &operator=(const MissionLighting &) = delete;
    void unload();
    void invalidate() {
        dirty_ = true;
        prepared_ = false;
    }
    void prepare(const Camera3D &camera, const std::function<void(Shader, Shader)> &scenery,
                 const std::function<void(Shader, Shader)> &actors = {});
    bool ready() const {
        return prepared_;
    }
    bool contains(Box bounds) const;
    Texture2D texture() const {
        return prepared_ ? shadow_.depth : Texture2D{};
    }
    Shader actorShader() const {
        return prepared_ ? actor_ : Shader{};
    }
    void bind(Shader shader) const;
    void beginPrimitives() const;
    void endPrimitives() const;
    void draw(Mesh mesh, Material material, Matrix transform) const;
    void drawInstanced(Mesh mesh, Material material, const Matrix *transforms, int count) const;
    static std::string withShadows(const char *fragment);
    static Vector3 sun();

  private:
    static constexpr int Size = 2048;
    RenderTexture2D shadow_{}, staticShadow_{};
    Shader instanceDepth_{}, meshDepth_{}, primitiveDepth_{}, actor_{}, primitive_{};
    Matrix view_{}, lightVP_{};
    Vector3 focus_{};
    float span_ = 0;
    bool attempted_ = false, dirty_ = true, prepared_ = false;
    bool load();
};
} // namespace dw
