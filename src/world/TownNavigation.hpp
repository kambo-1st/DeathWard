#pragma once
#include "world/TownDocument.hpp"

namespace dw {
struct TownNavigation {
    uint32_t width = 0, depth = 0;
    int bakeVersion = 2;
    float minX = 0, minZ = 0, cell = .4f;
    Vector3 spawn{}, mission{};
    std::vector<float> heights;
    void load(const std::filesystem::path &path);
    void write(const std::filesystem::path &path) const;
    void bake(const TownDocument &document, const Model &model);
    Vector3 point(size_t index) const;
    float height(Vector3 point) const;
};
// Rebuild derived navigation without modifying the authored scene.
void saveTownNavigation(const std::filesystem::path &directory, const TownNavigation &navigation);
// Validate both staged files before replacing either; keep backups and roll back on failure.
void saveTownProject(const std::filesystem::path &directory, const TownDocument &document,
                     const TownNavigation &navigation);
} // namespace dw
