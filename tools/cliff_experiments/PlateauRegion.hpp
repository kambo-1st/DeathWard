#pragma once
#include "RockFormations.hpp"

namespace dw::rockFormations {
struct PlateauRegionBoundary {
    Vector3 a{},b{};
    Plane roof;
    bool selectedFront=false;
};
struct PlateauRegion {
    std::vector<Polygon> domains;
    std::vector<PlateauRegionBoundary> boundary;
    size_t sourceFaces=0,components=0,selectedWalls=0,neighbourWalls=0,unanchoredWalls=0;
    float minimumHeight=0,maximumHeight=0;
    double projectedArea=0;
    uint64_t key=0;
};
// Complete connected source roof components, never clipped to a wall window or room box.
PlateauRegion planPlateauRegion(const CanyonAppearance &,const std::vector<cliffDetail::Quad> &,const std::vector<Polygon> &reachedRoofs={});
// Fixed-grid planar union/decomposition. Preserves holes and disconnected parts.
std::vector<Polygon> plateauRegionFootprint(const std::vector<Polygon> &,const std::vector<Polygon> &holes={});
cliffOptions::Mesh meshPlateauFootprint(const std::vector<Polygon> &,bool interiorControls=false);
std::vector<Vector3> plateauFootprintPinches(const std::vector<Polygon> &);
// Deliberate finite terrain links at point contacts; radius is a shape dimension, not a weld tolerance.
std::vector<Polygon> bridgePlateauFootprintPinches(const std::vector<Polygon> &,float radius=.04f);
std::vector<RoofGrade> plateauRegionConstraints(const PlateauRegion &,const std::vector<std::array<Vector3,2>> &external,float strip=.6f);
void writePlateauRegion(const char *,const PlateauRegion &);
}
