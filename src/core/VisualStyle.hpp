#pragma once
#include <optional>
#include <string_view>

namespace dw {
// Session-only rendering choices. Never serialized into maps or campaigns.
// Values are shared with the world and post-process shaders.
enum class VisualStyle {
    Original, Cel, Comic, Painted, Poster, Noir, Retro,
    Woodcut, Watercolor, Pencil, Ink, Diorama, Cinema, CRT, Spectral, Sumi, Count
};
inline constexpr VisualStyle nextVisualStyle(VisualStyle style) {
    return VisualStyle((int(style) + 1) % int(VisualStyle::Count));
}
inline constexpr const char *visualStyleName(VisualStyle style) {
    switch (style) {
    case VisualStyle::Cel: return "Cel-shaded";
    case VisualStyle::Comic: return "Western comic";
    case VisualStyle::Painted: return "Painted frontier";
    case VisualStyle::Poster: return "Wanted poster";
    case VisualStyle::Noir: return "Western noir";
    case VisualStyle::Retro: return "Retro 3D";
    case VisualStyle::Woodcut: return "Woodcut / linocut";
    case VisualStyle::Watercolor: return "Watercolor";
    case VisualStyle::Pencil: return "Colored pencil";
    case VisualStyle::Ink: return "Ink wash";
    case VisualStyle::Diorama: return "Miniature diorama";
    case VisualStyle::Cinema: return "Spaghetti Western";
    case VisualStyle::CRT: return "CRT arcade";
    case VisualStyle::Spectral: return "Spectral frontier";
    case VisualStyle::Sumi: return "Sumi-e frontier";
    default: return "Original";
    }
}
inline constexpr const char *visualStyleSlug(VisualStyle style) {
    switch (style) {
    case VisualStyle::Cel: return "cel";
    case VisualStyle::Comic: return "comic";
    case VisualStyle::Painted: return "painted";
    case VisualStyle::Poster: return "poster";
    case VisualStyle::Noir: return "noir";
    case VisualStyle::Retro: return "retro";
    case VisualStyle::Woodcut: return "woodcut";
    case VisualStyle::Watercolor: return "watercolor";
    case VisualStyle::Pencil: return "pencil";
    case VisualStyle::Ink: return "ink";
    case VisualStyle::Diorama: return "diorama";
    case VisualStyle::Cinema: return "cinema";
    case VisualStyle::CRT: return "crt";
    case VisualStyle::Spectral: return "spectral";
    case VisualStyle::Sumi: return "sumi";
    default: return "original";
    }
}
inline constexpr std::optional<VisualStyle> parseVisualStyle(std::string_view name) {
    if (name == "okami") return VisualStyle::Sumi;
    for (int index = 0; index < int(VisualStyle::Count); ++index) {
        const auto style = VisualStyle(index);
        if (name == visualStyleSlug(style)) return style;
    }
    return {};
}
} // namespace dw
