#pragma once
#include "platform/Assets.hpp"
#include "render/DisplayFontCodepoints.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

namespace dw {
// Shared face and measurement for player-facing menus and HUD. Load only while
// a graphics context exists; owners unload before closing that context.
class MainFont {
  public:
    MainFont() = default;
    MainFont(const MainFont &) = delete;
    MainFont &operator=(const MainFont &) = delete;
    ~MainFont() { unload(); }

    float width(const char *text, float size) const {
        const auto &face = forText(text, size);
        return MeasureTextEx(face.font, text, pixels(face, size), spacing(size)).x;
    }
    void draw(const char *text, Vector2 position, float size, Color color) const {
        const auto &face = forText(text, size);
        const float fontSize = pixels(face, size);
        position.y -= face.capTop * fontSize / float(face.font.baseSize);
        DrawTextEx(face.font, text, position, fontSize, spacing(size), color);
    }
    bool ready() const { return load(body_, false).owned; }
    void unload() {
        for (auto *face : {&body_, &heading_}) {
            if (face->owned && IsWindowReady()) UnloadFont(face->font);
            *face = {};
        }
    }

  private:
    struct Face {
        Font font{};
        float capHeight = 1, capTop = 0;
        bool attempted = false, owned = false;
    };
    mutable Face body_, heading_;
    static float spacing(float size) { return std::max(.35f, size * .035f); }
    static float pixels(const Face &face, float size) {
        return size * float(face.font.baseSize) / face.capHeight;
    }
    const Face &load(Face &face, bool heading) const {
        if (face.attempted) return face;
        face.attempted = true;
        constexpr auto relative = "ui/deathward-display/DeathWardDisplay-Regular.otf";
#ifdef __EMSCRIPTEN__
        const auto file = sourceAssetDirectory() / relative;
#else
        auto file = std::filesystem::path(GetApplicationDirectory()) / "assets" / relative;
        if (!std::filesystem::exists(file)) file = sourceAssetDirectory() / relative;
#endif
        // A small full-coverage atlas keeps the HUD sharp. The larger atlas is
        // reserved for ordinary Latin headings instead of allocating every
        // inherited phonetic/symbol glyph at title resolution.
        std::vector<int> codepoints;
        for (const int cp : DisplayFontCodepoints)
            if (!heading || cp <= 0x17f) codepoints.push_back(cp);
        face.font = LoadFontEx(file.string().c_str(), heading ? 192 : 64,
                               codepoints.data(), int(codepoints.size()));
        face.owned = face.font.texture.id && face.font.texture.id != GetFontDefault().texture.id;
        if (!face.owned) {
            face.font = GetFontDefault();
            TraceLog(LOG_WARNING, "UI FONT: DeathWard Display unavailable: %s", file.string().c_str());
        } else {
            GenTextureMipmaps(&face.font.texture);
            SetTextureFilter(face.font.texture, TEXTURE_FILTER_TRILINEAR);
        }
        const int cap = GetGlyphIndex(face.font, 'H');
        face.capHeight = std::max(1.f, face.font.recs[cap].height);
        face.capTop = float(face.font.glyphs[cap].offsetY);
        return face;
    }
    const Face &forText(const char *text, float size) const {
        bool heading = size >= 36;
        for (const char *at = text; heading && *at;) {
            int bytes = 0;
            const int cp = GetCodepointNext(at, &bytes);
            if (cp > 0x17f) heading = false;
            at += std::max(1, bytes);
        }
        return heading ? load(heading_, true) : load(body_, false);
    }
};
} // namespace dw
