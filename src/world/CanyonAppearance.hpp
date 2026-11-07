#pragma once
#include "world/CanyonTerrain.hpp"
#include <filesystem>
namespace dw {
struct CanyonVisualParameters {
    bool enabled = true;
    bool irregularFacets = true;
    bool polygonFacets = true;
    float minHeight = 2.4f, maxHeight = 6.8f, heightVariation = .85f;
    int terraces = 3;
    float terraceWidth = 1.4f, silhouette = .9f, facets = .35f;
    float debris = .85f, floorVegetation = .35f, baseVegetation = .9f, terraceVegetation = 1.2f,
          plateauVegetation = .85f;
    float extent = 24;
    float composition = .85f;
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
    size_t cliffTopologyPatches=0, cliffTopologyFallbacks=0;
    size_t cliffQuads=0, cliffNgons=0, cliffChips=0;
    std::vector<float> distanceToFloor, distanceToRock;
    std::vector<CanyonDecoration> decorations;
    // Separate polygon caps and extruded walls, indexed by original source cell.
    std::vector<CanyonSurfaceTriangle> triangles;
    std::vector<size_t> cellOffsets;
    // Render order stays stable; these bins index the actual displaced triangles.
    std::vector<size_t> spatialOffsets, spatialTriangles;
    // Decorative support keeps the pre-detail surface; aiming uses visible facets.
    std::vector<CanyonSurfaceTriangle> supportTriangles;
    std::vector<size_t> supportOffsets, supportIndices;
    size_t queryBegin(size_t cell) const {
        return spatialOffsets.empty() ? cellOffsets[cell] : spatialOffsets[cell];
    }
    size_t queryEnd(size_t cell) const {
        return spatialOffsets.empty() ? cellOffsets[cell + 1] : spatialOffsets[cell + 1];
    }
    size_t queryTriangle(size_t entry) const {
        return spatialOffsets.empty() ? entry : spatialTriangles[entry];
    }
    float height(float x, float z) const;
    SegmentHit trace(Vector3 from, Vector3 to) const;
    bool supports(Vector3 p, float radius, float tolerance = .18f) const;
};
CanyonAppearance buildCanyonAppearance(const Arena &arena, const CanyonVisualParameters &parameters = {});
} // namespace dw
