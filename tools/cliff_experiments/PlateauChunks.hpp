#pragma once
#include "PlateauRegion.hpp"
#include <span>

namespace dw::rockFormations {
struct PlateauChunkSettings {
    int side=16;
    float support=6;
    bool continuous=true;
};
struct PlateauRoofChunk {
    int x=0,z=0;
    std::vector<GradedRoofCell> cells;
};
struct PlateauChunkBuild {
    std::vector<PlateauRoofChunk> chunks;
    size_t regionalFaces=0,localFaces=0,gridTriangles=0,gridNodes=0;
    float landHeight=0;
    Box influence{};
    // Optional construction selection, in flattened chunk-cell order. The full
    // field remains available to callers and diagnostics before consumption.
    std::vector<bool> retainedSourceCells;
};
// One floor-space grid and one compact field, shared by all owned chunks.
PlateauChunkBuild buildPlateauChunks(const PlateauRegion &,const std::vector<Polygon> &caps,
    const std::vector<RoofGrade> &front,const std::vector<RoofGrade> &lower,
    const std::vector<Polygon> &holes,const PlateauChunkSettings &settings={},std::span<const Volume> capVolumes={});
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
std::vector<GradedRoofCell> partitionPlateauCellOwnership(const std::vector<GradedRoofCell> &,const std::vector<Polygon> &holes={},
    const std::vector<Polygon> &domainCuts={});
std::vector<GradedRoofCell> partitionPlateauGridOwnership(const std::vector<GradedRoofCell> &,const std::vector<Polygon> &holes,
    const std::vector<Polygon> &domainCuts);
std::vector<GradedRoofCell> partitionPlateauEnvelopePieces(const std::vector<GradedRoofCell> &,bool retainDomains);
#endif
void writePlateauChunks(const char *,const PlateauChunkBuild &);
}
