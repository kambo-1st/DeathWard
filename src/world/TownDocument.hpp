#pragma once
#include "core/Types.hpp"
#include <filesystem>
#include <optional>

namespace dw {
struct TownAsset {
    std::string name, label;
    int first = 0, count = 0, unlit = 0;
    Box bounds;
};
struct TownInstance {
    size_t asset = 0;
    Matrix transform{};
};
struct TownLight {
    int type = 1;
    Vector3 position{}, direction{}, color{};
    float intensity = 1, range = 0;
};
struct TownDocument {
    std::vector<TownAsset> assets;
    std::vector<TownInstance> instances;
    std::vector<TownLight> lights;
    bool load(const std::filesystem::path &path, std::string &error);
    void write(const std::filesystem::path &path) const;
    void validate() const;
    Box bounds(size_t instance) const;
    int meshCount() const;
};
} // namespace dw
