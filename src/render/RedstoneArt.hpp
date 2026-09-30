#pragma once
#include "world/TownDocument.hpp"

namespace dw {
// Opt-in, derived rendering data only. Never added to the editable/saved document.
class RedstoneArt {
  public:
    ~RedstoneArt() {
        unload();
    }
    RedstoneArt() = default;
    RedstoneArt(const RedstoneArt &) = delete;
    RedstoneArt &operator=(const RedstoneArt &) = delete;
    void build(const TownDocument &document, const Model &library);
    void unload();
    void draw(Shader shader, Texture2D shadow, double time, bool depthOnly = false) const;
    Texture2D contact() const {
        return contact_;
    }
    bool ready() const {
        return contact_.id != 0;
    }
    static bool supports(const TownDocument &document);
    static int surface(const TownAsset &asset);
    static std::string shaderFunctions();

  private:
    Texture2D contact_{};
    Model dressing_{}, cloth_{}, dressingShadow_{}, clothShadow_{};
};
} // namespace dw
