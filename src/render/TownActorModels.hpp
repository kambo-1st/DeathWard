#pragma once
#include "render/SkinnedModel.hpp"
#include "world/TownCharacters.hpp"
namespace dw {
class TownActorModels {
  public:
    static std::filesystem::path cowgirlPath() {
#ifdef __EMSCRIPTEN__
        return "/assets/cowgirl/cowgirl.glb";
#else
        auto source = std::filesystem::path(DEATHWARD_ASSET_DIR) / "cowgirl/cowgirl.glb";
        return std::filesystem::is_regular_file(source) ? source :
            std::filesystem::path(GetApplicationDirectory()) / "assets/cowgirl/cowgirl.glb";
#endif
    }
    void unload() { cowgirl_.unload(); }
    void prepare(const TownCharacters &characters) {
        if (!characters.residents().empty() && !cowgirl_.attempted()) cowgirl_.load(cowgirlPath(), true);
    }
    void draw(const TownCharacters &characters, Shader shader = {}, Texture2D shadow = {}) {
        prepare(characters);
        for (const auto &c : characters.residents())
            if (cowgirl_.pose(c.phase, c.walking, c.alternate))
                cowgirl_.draw(c.position, c.facing, c.definition.scale, shader, shadow);
    }
  private:
    SkinnedModel cowgirl_;
};
}
