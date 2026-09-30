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
    bool groundDetail = true;
    bool canyonRiver = true;
    bool operator==(const VisualSettings &) const = default;
};
inline VisualSettings loadVisualSettings(const std::filesystem::path &path) {
    std::ifstream file(path);
    std::string magic;
    int version = 0;
    VisualSettings settings;
    if (!(file >> magic >> version >> settings.vegetation) || magic != "DEATHWARD_VISUAL" ||
        (version < 1 || version > 3) || settings.vegetation < 0 ||
        settings.vegetation > VisualSettings::MaxVegetation)
        return {};
    if (version >= 2) {
        int detail = 0;
        if (!(file >> detail) || (detail != 0 && detail != 1))
            return {};
        settings.groundDetail = detail != 0;
    }
    if (version >= 3) {
        int river = 0;
        if (!(file >> river) || (river != 0 && river != 1))
            return {};
        settings.canyonRiver = river != 0;
    }
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
    file << "DEATHWARD_VISUAL 3\n"
         << std::clamp(settings.vegetation, 0, VisualSettings::MaxVegetation) << '\n'
         << int(settings.groundDetail) << '\n'
         << int(settings.canyonRiver) << '\n';
    file.close();
    if (!file)
        return false;
    persistBrowserFiles();
    return true;
}
} // namespace dw
