#pragma once
#include "render/SkinnedModel.hpp"
#include "world/TownCharacters.hpp"
namespace dw {
class TownActorModels {
  public:
    static std::filesystem::path cowgirlPath() {
        return modelPath("cowgirl");
    }
    static std::filesystem::path modelPath(const std::string &name) {
#ifdef __EMSCRIPTEN__
        return "/assets/" + name + "/" + name + ".glb";
#else
        auto relative = std::filesystem::path(name) / (name + ".glb");
        auto source = std::filesystem::path(DEATHWARD_ASSET_DIR) / relative;
        return std::filesystem::is_regular_file(source) ? source :
            std::filesystem::path(GetApplicationDirectory()) / "assets" / relative;
#endif
    }
    void unload() { cowgirl_.unload(); bandit_.unload(); }
    void prepare(const TownCharacters &characters) {
        for (const auto &c : characters.residents()) {
            auto &model = c.definition.model == "bandit" ? bandit_ : cowgirl_;
            if (!model.attempted() && model.load(modelPath(c.definition.model), true) &&
                c.definition.model == "bandit") {
                const auto bounds = GetModelBoundingBox(model.model());
                banditScale_ = 2.05f / std::max(.1f, bounds.max.y - bounds.min.y);
            }
        }
    }
    void draw(const TownCharacters &characters, Shader shader = {}, Texture2D shadow = {}) {
        prepare(characters);
        for (const auto &c : characters.residents()) {
            auto &model = c.definition.model == "bandit" ? bandit_ : cowgirl_;
            const float scale = c.definition.scale * (c.definition.model == "bandit" ? banditScale_ : 1);
            if (model.pose(c.phase, c.walking, c.alternate))
                model.draw(c.position, c.facing, scale, shader, shadow);
        }
    }
  private:
    SkinnedModel cowgirl_, bandit_;
    float banditScale_ = 1;
};
}
