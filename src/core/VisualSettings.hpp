#pragma once
#include "platform/Browser.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

namespace dw {
struct VisualSettings {
    static constexpr int MaxVegetation = 200;
    int vegetation = 100;
    bool operator==(const VisualSettings &) const = default;
};
inline VisualSettings loadVisualSettings(const std::filesystem::path &path) {
    std::ifstream file(path);
    std::string magic;
    int version = 0;
    VisualSettings settings;
    if (!(file >> magic >> version >> settings.vegetation) || magic != "DEATHWARD_VISUAL" || version != 1 ||
        settings.vegetation < 0 || settings.vegetation > VisualSettings::MaxVegetation)
        return {};
    return settings;
}
inline bool saveVisualSettings(const std::filesystem::path &path, VisualSettings settings) {
    if (path.empty())
        return true;
    std::error_code error;
    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path(), error);
    if (error)
        return false;
    std::ofstream file(path);
    file << "DEATHWARD_VISUAL 1\n"
         << std::clamp(settings.vegetation, 0, VisualSettings::MaxVegetation) << '\n';
    file.close();
    if (!file)
        return false;
    persistBrowserFiles();
    return true;
}
} // namespace dw
