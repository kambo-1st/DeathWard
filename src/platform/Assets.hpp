#pragma once
#include "raylib.h"
#include <filesystem>

namespace dw {
// Development builds retain editable source scenes. Portable releases must not
// reach back into that checkout, even while it is accessible through WSL.
inline std::filesystem::path sourceAssetDirectory() {
#ifdef __EMSCRIPTEN__
    return "/assets";
#elif defined(DEATHWARD_PACKAGED_ASSETS)
    return std::filesystem::path(GetApplicationDirectory()) / "assets";
#elif defined(DEATHWARD_ASSET_DIR)
    return DEATHWARD_ASSET_DIR;
#else
    return std::filesystem::path(GetApplicationDirectory()) / "assets";
#endif
}
} // namespace dw
