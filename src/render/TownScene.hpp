#pragma once
#include "core/Types.hpp"
#include "render/ParticleEffects.hpp"
#include "render/PlayerOcclusion.hpp"
#include "render/RedstoneArt.hpp"
#include "world/HubDefinition.hpp"
#include "world/ObjectAnimation.hpp"
#include "world/TownDocument.hpp"
#include <filesystem>
#include <functional>

namespace dw {
class TownScene {
  public:
    ~TownScene();
    TownScene() = default;
    TownScene(const TownScene &) = delete;
    TownScene &operator=(const TownScene &) = delete;
    bool load(const std::filesystem::path &directory = assetDirectory(HubKind::BlackCreek));
    void unload();
    void draw(Vector3 focus, bool glass = false);
    void setArtPoc(bool enabled);
    bool artPoc() const {
        return artEnabled_;
    }
    void setPlayerOcclusion(const Camera3D &camera, Vector3 player, bool enabled = true);
    std::optional<size_t> interior() const { return interior_; }
    void drawOccluders();
    void drawEffects(const Camera3D &camera) { effects_.draw(camera); }
    void prepareSandstorm(const Camera3D &camera, float strength,
                          const std::function<float(Vector3)> &ground) {
        effects_.addSandstorm(camera, strength, 0x57a0d057u, ground);
    }
    const ParticleEffects &effects() const { return effects_; }
    // Call before BeginMode3D. Actors use the supplied depth shader in this pass.
    void prepareLighting(const Camera3D &camera, const std::function<void(Shader)> &actors = {});
    Shader actorShader() const {
        return actorShader_;
    }
    Texture2D shadowTexture() const {
        return shadowMap_.depth;
    }
    bool shadowsReady() const {
        return shadowMap_.id != 0 && sunIndex_ >= 0;
    }
    bool loaded() const {
        return model_.meshCount > 0;
    }
    size_t instanceCount() const {
        return instances_.size();
    }
    const Model &model() const {
        return model_;
    }
    static std::filesystem::path assetDirectory(HubKind hub = HubKind::BlackCreek);
    const TownDocument &document() const {
        return document_;
    }
    void applyDocument(const TownDocument &document);
    void applyAnimation(const ObjectAnimationSystem &animation);
    Box instanceBounds(size_t index) const {
        return instances_.at(index).bounds;
    }
    std::optional<size_t> pick(Ray ray) const;

  private:
    struct Asset {
        int first = 0, count = 0, unlit = 0;
        Box bounds;
        bool groundOverlay = false;
    };
    struct Instance {
        size_t asset;
        Matrix transform;
        Box bounds;
        bool animated = false;
        bool castsShadow = true;
    };
    Model model_{};
    TownDocument document_;
    Shader shader_{};
    Shader actorShader_{}, shadowShader_{}, actorShadowShader_{};
    RenderTexture2D shadowMap_{}, staticShadowMap_{};
    Vector3 shadowFocus_{};
    float shadowSpan_ = 0;
    bool shadowsDirty_ = true;
    Vector3 sunDirection_{0, 1, 0};
    int sunIndex_ = -1;
    std::vector<Asset> assets_;
    std::vector<Instance> instances_;
    std::vector<const Instance *> occluders_;
    std::vector<std::vector<Matrix>> batches_;
    std::vector<std::vector<Matrix>> shadowBatches_;
    bool attempted_ = false;
    PlayerOcclusion occlusion_;
    ParticleEffects effects_;
    RedstoneArt art_;
    bool artEnabled_ = false;
    std::optional<size_t> interior_;
    Matrix interiorInverse_{};
    Box interiorBounds_{}, interiorWorldBounds_{};
    float interiorFloor_ = 0;
    void bindInterior(bool architecture);
    bool belongsToInterior(const Instance &instance) const;
    void updateLights();
    void updateEffectLights(const Camera3D &camera);
};
} // namespace dw
