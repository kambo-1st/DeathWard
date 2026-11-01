#pragma once
#include "world/CanyonTerrain.hpp"
#include <filesystem>
namespace dw {
struct CanyonVisualParameters {
    bool enabled = true;
    float minHeight = 1.65f, maxHeight = 6.8f, heightVariation = .85f;
    int terraces = 3;
    float terraceWidth = 1.f, silhouette = .65f, facets = .35f;
    float debris = .85f, floorVegetation = .35f, baseVegetation = .9f, terraceVegetation = 1.2f,
          plateauVegetation = .85f;
    float extent = 24;
    int candidatesPerRoom = 360, maxDecorations = 2200;
    static CanyonVisualParameters load(const std::filesystem::path &path);
    void validate() const;
};
enum class CanyonZone { Floor, CliffBase, Terrace, Plateau };
enum class CanyonDecorationKind { Rock, Grass, Shrub, Cactus, Tree };
struct CanyonDecoration {
    CanyonDecorationKind kind;
    CanyonZone zone;
    Vector3 position{};
    float span = 0, height = 0, yaw = 0;
    int room = -1;
    bool extraVegetation = false;
};
// Cosmetic copy only. Arena::canyon remains the authoritative gameplay field.
struct CanyonSurfaceTriangle {
    std::array<Vector3, 3> vertices;
    bool rock = false;
};
struct CanyonAppearance {
    CanyonTerrain surface;
    CanyonVisualParameters parameters;
    uint64_t seed = 0;
    std::vector<float> distanceToFloor, distanceToRock;
    std::vector<CanyonDecoration> decorations;
    // Separate polygon caps and extruded walls, indexed by original source cell.
    std::vector<CanyonSurfaceTriangle> triangles;
    std::vector<size_t> cellOffsets;
    float height(float x, float z) const;
    SegmentHit trace(Vector3 from, Vector3 to) const;
    bool supports(Vector3 p, float radius, float tolerance = .18f) const;
};
CanyonAppearance buildCanyonAppearance(const Arena &arena, const CanyonVisualParameters &parameters = {});
} // namespace dw
