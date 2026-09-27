#pragma once
#include "core/Types.hpp"
#include <filesystem>

namespace dw {
class TownScene {
  public:
    ~TownScene();
    TownScene() = default;
    TownScene(const TownScene &) = delete;
    TownScene &operator=(const TownScene &) = delete;
    bool load(const std::filesystem::path &directory = assetDirectory());
    void unload();
    void draw(Vector3 focus, bool glass = false);
    bool loaded() const {
        return model_.meshCount > 0;
    }
    size_t instanceCount() const {
        return instances_.size();
    }
    const Model &model() const {
        return model_;
    }
    static std::filesystem::path assetDirectory();

  private:
    struct Asset {
        int first = 0, count = 0, unlit = 0;
        Box bounds;
    };
    struct Instance {
        size_t asset;
        Matrix transform;
        Box bounds;
    };
    Model model_{};
    Shader shader_{};
    std::vector<Asset> assets_;
    std::vector<Instance> instances_;
    std::vector<std::vector<Matrix>> batches_;
    bool attempted_ = false;
};
} // namespace dw
