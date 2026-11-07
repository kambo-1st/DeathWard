#pragma once
#include "PrototypeGeometry.hpp"
#include "world/CanyonAppearance.hpp"
namespace dw::rockFormations {
using Polygon = std::vector<Vector3>;
enum class FormationRole { Join, Supporting, Dominant, Shoulder, Base };
std::vector<cliffOptions::Triangle> triangulatePlateauRoof(const std::vector<Vector3> &);
std::vector<cliffOptions::Triangle> triangulatePlateauBoundary(std::vector<Vector3>,bool retainCollinear=false);
struct FormationProfile {
    float yaw = 0;
    Vector2 lean{}, roof{}, crown{};
    float crownAt = .2f, taper = .12f, bevel = .06f;
    unsigned corners = 8, bevelMask = 0;
};
struct FormationDescriptor {
    std::string name;
    float at, width, depth, height, setback;
    FormationProfile profile;
    FormationRole role = FormationRole::Supporting;
    bool enabled = true;
};
std::vector<FormationDescriptor> compose(float wallLength,uint64_t seed,bool authored);
struct Plane {
    Vector3 normal{};
    double distance = 0;
    std::array<double,3> preciseNormal{};
    bool hasPreciseNormal=false;
};
inline double projection(Vector3 n, Vector3 p) {
    return double(n.x)*p.x + double(n.y)*p.y + double(n.z)*p.z;
}
inline std::array<double,3> planeNormal(const Plane &p) {
    return p.hasPreciseNormal?p.preciseNormal:std::array<double,3>{p.normal.x,p.normal.y,p.normal.z};
}
inline double planeProjection(const Plane &plane,Vector3 p) {
    const auto n=planeNormal(plane);
    return n[0]*p.x+n[1]*p.y+n[2]*p.z;
}
struct Volume {
    std::vector<Plane> planes;
    std::vector<Polygon> faces;
    Box bounds{};
};
cliffOptions::Mesh solidBooleanUnion(const std::vector<Volume> &,double tolerance=.000008,float padding=0,const std::vector<Polygon> &floors={},const std::vector<cliffOptions::Mesh> &checkedBodies={},size_t bodyBegin=0,size_t bodyCount=0);
cliffOptions::Mesh solidBooleanTerrainJoin(const std::vector<Volume> &,const cliffOptions::Mesh &);
struct RoofGrade {
    Polygon protectedRoof;
    Plane roof;
    float outsideSlope=0; // Zero uses the caller's common grading slope.
};
struct GradedRoofCell {
    Polygon outline;
    Plane roof;
};
std::vector<GradedRoofCell> gradePlateauRoof(Polygon domain,float landHeight,const std::vector<RoofGrade> &,float slope=1,bool prune=true);
std::vector<GradedRoofCell> samplePlateauRegionRoof(std::vector<Polygon>,float,const std::vector<RoofGrade> &,float slope=1,const std::vector<RoofGrade> &lowerCaps={});
std::vector<GradedRoofCell> gradePlateauRegionRoof(std::vector<Polygon>,float,const std::vector<RoofGrade> &,float slope=1,bool prune=true);
std::vector<GradedRoofCell> blendPlateauBoundary(std::vector<GradedRoofCell>,const std::vector<RoofGrade> &,const std::vector<Plane> &,float slope=.8f);
std::vector<RoofGrade> plateauBoundaryGrades(const Polygon &,const std::vector<RoofGrade> &,const std::vector<Plane> &,float inwardSlope=.8f);
struct SurfaceAudit {
    size_t vertices=0, boundaryEdges=0, nonmanifoldEdges=0, duplicateFaces=0, degenerateFaces=0, components=0, windingErrors=0;
};
struct StrictSurfaceAudit {
    SurfaceAudit exact;
    size_t nonmanifoldVertices=0, testedPairs=0, selfIntersections=0, coplanarOverlaps=0;
    double minimumArea=0;
    std::vector<std::array<size_t,2>> problemPairs;
};
struct BoundaryCoverageAudit {
    size_t triangles=0, buriedFragments=0, detachedFragments=0;
    double buriedArea=0, detachedArea=0;
};
struct Experiment {
    cliffOptions::Mesh mesh;
    std::vector<Volume> volumes;
    size_t clearanceTests = 0, shiftedVolumes = 0, rayChecks = 0;
    size_t primaryVolumes = 0, plateauVolumes = 0, topChecks = 0, topEdgeGuards = 0;
    Vector3 plateauCenter{};
    size_t plateauRouteChecks=0;
    float maximumRouteStep=0;
    std::vector<cliffOptions::Triangle> plateauTops;
    std::vector<Polygon> protectedFloor;
    SurfaceAudit audit;
    StrictSurfaceAudit strictAudit,strictAssembledAudit;
    BoundaryCoverageAudit boundaryCoverage;
    cliffOptions::Mesh assembledMesh;
    SurfaceAudit assembledAudit;
    size_t intentionalBoundaryEdges=0, unexpectedBoundaryEdges=0, seamChecks=0;
    size_t seamSkipped=0;
    size_t contextBoundaryEdges=0, foundationBoundaryEdges=0;
    size_t buriedContextEdges=0;
    size_t floorBoundaryEdges=0;
    size_t repairedSlits=0, repairSamples=0;
    Box editBounds{};
    float width = 0;
    float editMargin = .75f;
    bool detailEnabled = false;
    bool seededComposition = false;
    bool blendedBacking = false;
    bool finishedRoof = false;
    std::vector<FormationDescriptor> descriptors;
    size_t rimCuts = 0, baseDetails = 0;
    size_t joinConnectors = 0, joinCoverageChecks = 0;
    size_t sceneryReanchored = 0, sceneryRemoved = 0, sceneryAdded = 0, scenerySupportTests = 0;
};
Experiment build(const std::vector<cliffDetail::Quad> &wall, const CanyonAppearance &base, uint64_t seed, bool detail = false,bool seeded = false,bool finishRoof = true,const CanyonAppearance *regionSource=nullptr);
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
std::vector<Polygon> consolidateExactPlanar(std::vector<Polygon>,Vector3 faceNormal);
Polygon clipToVolumeSingleRound(Polygon,const Volume &);
std::vector<Polygon> exposedSingleRound(Polygon,const std::vector<Volume> &,int owner=-1);
Polygon clipToVolumePrecise(Polygon,const Volume &);
std::vector<Polygon> exposedPrecise(Polygon,const std::vector<Volume> &,int owner=-1);
cliffOptions::Mesh improvePlateauFootprint(cliffOptions::Mesh);
cliffOptions::Mesh refinePlateauFootprint(cliffOptions::Mesh,const std::function<float(Vector3)> &);
#endif
std::vector<Polygon> exposed(Polygon face, const std::vector<Volume> &volumes, int owner = -1);
Polygon clipToVolume(Polygon, const Volume &);
// Independent triangle oracle for the prototype's metre-scale mesh; 1000 means no hit.
float traceMesh(const cliffOptions::Mesh &, Vector3 from, Vector3 direction);
float traceVolumes(const std::vector<Volume> &, Vector3 from, Vector3 direction);
// Split shared boundary edges before triangulation so CSG fragments cannot
// leave T-junctions. The audit checks the actual emitted triangle surface.
cliffOptions::Mesh weldSurface(const std::vector<Polygon> &,float tolerance=.00008f,bool preserveTriangles=false,bool triangulateConcave=false);
// Closed-solid union, independently verified after conversion to render floats.
SurfaceAudit auditSurface(const cliffOptions::Mesh &);
// Signed volume of the rendered roof triangle fan extruded to a flat base.
long double signedColumnVolume(const Polygon &,float bottom);
// Extract one closed height-field boundary; source prisms remain the oracle.
cliffOptions::Mesh simplifyPlateauSurface(const cliffOptions::Mesh &);
cliffOptions::Mesh arrangePlateauFootprint(const std::vector<Polygon> &,float tolerance=.00002f);
cliffOptions::Mesh meshPlateauBody(const std::vector<Volume> &,float bottom=-.12f,float tolerance=.00002f,bool splitCrossings=false);
std::vector<cliffOptions::Mesh> splitSurfaceComponents(const cliffOptions::Mesh &);
std::vector<cliffOptions::Mesh> meshPlateauRegionBodies(const std::vector<Volume> &);
// No positional welding in this verifier: tests the actual emitted floats.
StrictSurfaceAudit auditStrictSurface(const cliffOptions::Mesh &);
// Persist exact emitted floats and source planes for independent diagnostics.
void writeSurfaceProbe(const char *,const cliffOptions::Mesh &,const std::vector<Volume> &,const StrictSurfaceAudit &);
// Prefix must already be verified; topology is still checked for the full mesh.
StrictSurfaceAudit auditSurfaceReplacement(const cliffOptions::Mesh &,size_t firstChangedTriangle);
bool replacementIntersects(const cliffOptions::Mesh &,size_t firstChangedTriangle);
BoundaryCoverageAudit auditBoundaryCoverage(const cliffOptions::Mesh &,const std::vector<Volume> &,double margin=.0001);
BoundaryCoverageAudit auditBoundaryCoverageQuiet(const cliffOptions::Mesh &,const std::vector<Volume> &,double margin=.0001);
std::vector<std::array<Vector3,2>> surfaceBoundary(const cliffOptions::Mesh &, bool directed=false);
cliffOptions::Mesh assembleSurface(const std::vector<Polygon> &retained, Experiment &, const std::vector<Polygon> &outside={},bool completeContext=false);
bool buriedContextBoundary(const std::array<Vector3,2> &,const std::vector<Polygon> &,Box bounds);
void apply(CanyonAppearance &, const std::vector<cliffDetail::Quad> &wall, Experiment &);
Experiment buildAndApply(CanyonAppearance &,const CanyonAppearance &,const std::vector<cliffDetail::Quad> &,uint64_t seed,bool detail);
// Local cosmetic support and placement on the final emitted surface.
void addScenery(CanyonAppearance &, const std::vector<cliffDetail::Quad> &, Experiment &, uint64_t seed);
bool placeOnSurface(const CanyonAppearance &,const cliffOptions::Mesh &,Vector3 &,float radius,size_t &tests,float tolerance=.16f);
} // namespace dw::rockFormations
