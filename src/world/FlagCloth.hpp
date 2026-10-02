#pragma once
#include "world/TownDocument.hpp"

namespace dw {
// Recognize the fabric section of the imported flag prefab, never its pole.
bool flagFabric(const TownAsset &asset);
uint32_t flagSeed(const std::string &id);

// A deterministic, length-preserving ribbon field. Travelling folds are integrated
// as unit tangents rather than stretching a flat plane with a sine offset.
// This makes paused previews and cinematic seeking reproduce the same cloth pose.
class FlagPose {
  public:
    static constexpr int Columns = 32, Rows = 12;
    FlagPose(Box rest, Matrix placement, double time, float storm, uint32_t seed);
    Vector3 position(Vector3 rest) const;
    Vector3 normal(Vector3 rest, Vector3 normal) const;
  private:
    Box bounds_;
    int axis_ = 2;
    float width_ = 1, height_ = 1;
    std::array<Vector3, (Columns + 1) * (Rows + 1)> offsets_{};
    void field(Vector3 rest, Vector3 &offset, Vector3 &along, Vector3 &vertical) const;
};

// Tessellates only the existing fabric triangles, retaining their UVs, colors,
// normals and silhouette. No graphics context or source-asset writes are needed.
struct FlagSurface {
    std::vector<Vector3> rest, normals, posed, posedNormals;
    std::vector<Vector2> uv;
    std::vector<Color> colors;
    Box restBounds{}, bounds{};
    void build(const Mesh &source);
    void pose(Matrix placement, double time, float storm, uint32_t seed);
};
}
