#include "RockFormations.hpp"
#include "FormationSections.hpp"
#include "FormationPrecision.hpp"
#include "PlateauRegion.hpp"
#include "PlateauChunks.hpp"
#include "PlateauSnapRound.hpp"
#include "PlateauExactContact.hpp"
#include "PlateauVertexBlend.hpp"
#include "PlateauAffineEnvelope.hpp"
#include "PlateauSourceReuse.hpp"
#include "PlateauSharedSourceEdges.hpp"
#include "PlateauCapDomain.hpp"
#include "BooleanSourceRestore.hpp"
#include "PlateauFloatVertexRepair.hpp"
#include "raymath.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
using namespace dw;
using namespace dw::rockFormations;
namespace {
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
Volume box(float x0, float x1, float z0, float z1) {
    Volume v;
    v.planes = {{{-1,0,0}, -x0}, {{1,0,0}, x1}, {{0,-1,0}, 1},
                {{0,1,0}, 1}, {{0,0,-1}, -z0}, {{0,0,1}, z1}};
    return v;
}
float surfaceArea(const std::vector<Polygon> &parts) {
    float total = 0;
    for (const auto &p : parts)
        for (size_t i = 1; i + 1 < p.size(); ++i) {
            const auto cross = Vector3CrossProduct(sub(p[i],p[0]),sub(p[i+1],p[0]));
            check(cross.y > 0, "Clipped face changed winding");
            total += Vector3Length(cross) * .5f;
        }
    return total;
}
bool covers(const std::vector<Polygon> &parts, Vector3 p) {
    for (const auto &f : parts)
        for (size_t i = 1; i + 1 < f.size(); ++i)
            if (GetRayCollisionTriangle({add(p,{0,2,0}),{0,-1,0}}, f[0],f[i],f[i+1]).hit)
                return true;
    return false;
}
}
int main() {
    try {
        {
            const float q=1.f/65536;
            Polygon top{{50,2,-20},{51-q,2.125f-.125f*q,-20+q},{51,2.125f,-20+q}};
            const long double expected=static_cast<long double>(q)*q*(6.25L-.125L*q)/6;
            check(std::abs(signedColumnVolume(top,0)-expected)<1e-24L,"Thin source-prism volume disagrees with its analytic integral");
            for(auto &p:top){p.x+=64;p.z+=128;}
            check(std::abs(signedColumnVolume(top,0)-expected)<1e-24L,"Source-prism volume changes after an exactly representable translation");
            std::reverse(top.begin(),top.end());
            check(signedColumnVolume(top,0)<0,"Inverted source-prism winding loses its signed volume");
        }
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        {
            const Polygon a{{0,0,0},{0,0,1},{1,0,1},{1,0,0}};
            const Polygon b{{1,0,0},{1,0,.999999f},{2,0,.999999f},{2,0,0}};
            const auto recessed=consolidateExactPlanar({a,b},{0,1,0});
            check(recessed.size()==2 && !covers(recessed,{1.1f,0,.9999995f}),
                  "Fragment consolidation fills a real sub-millimetre recess");
            const Polygon flush{{1,0,0},{1,0,1},{2,0,1},{2,0,0}};
            const auto joined=consolidateExactPlanar({a,flush},{0,1,0});
            check(joined.size()==1 && std::abs(surfaceArea(joined)-2)<.000001,
                  "Exact coplanar fragment consolidation cannot merge a convex shared edge");
            const Polygon thin{{-.00001f,0,0},{-.00001f,0,1},{.00001f,0,1},{.00001f,0,0}};
            Volume halfSpace;halfSpace.planes={{{1,0,0},0}};
            const auto strip=exposedPrecise(thin,{halfSpace});
            check(std::abs(surfaceArea(strip)-.00001)<1e-10 && covers(strip,{.000005f,0,.5f}) &&
                  !covers(strip,{-.000005f,0,.5f}),
                  "Source half-space clipping deletes a positive narrow exposed strip");
            // Separate roof layers remain distinct even when the original
            // owner is preferred for genuinely coincident caps.
            const Polygon layer{{50,1,-30},{50,1,-28},{52,1,-28},{52,1,-30}};
            auto upper=box(49,53,-31,-27);upper.planes[3].distance=std::nextafter(1.f,2.f);
            check(exposedSingleRound(layer,{upper},-2).empty(),
                  "A distinct higher roof was mistaken for a coincident source cap");
            upper.planes[3].distance=1;
            check(std::abs(surfaceArea(exposedSingleRound(layer,{upper},-2))-4)<1e-6,
                  "Exact coincident-cap ownership changed in the extended clipping path");
            upper.planes[3].distance=std::nextafter(1.f,0.f);
            check(std::abs(surfaceArea(exposedSingleRound(layer,{upper},-2))-4)<1e-6,
                  "A lower retained roof hides the higher source cap");
            const Polygon work{{50,3,-40},{50,3,-20},{70,3,-20},{70,3,-40}};
            Volume cuts;cuts.planes={{{.3f,0,.7f},-2.750001234},{{-.81f,0,.19f},-50.0123456}};
            const auto clipped=clipToVolumeSingleRound(work,cuts);
            std::reverse(cuts.planes.begin(),cuts.planes.end());
            const auto reversed=clipToVolumeSingleRound(work,cuts);
            auto positions=[](const Polygon &p){std::set<std::array<float,3>> v;for(auto a:p)v.insert({a.x,a.y,a.z});return v;};
            check(clipped.size()>=3 && positions(clipped)==positions(reversed),
                  "Plane order changes the final render vertices of a clipped source face");
            const auto cutA=cuts.planes[0],cutB=cuts.planes[1];
            const double det=double(cutA.normal.x)*cutB.normal.z-double(cutA.normal.z)*cutB.normal.x;
            const Vector3 intersection{float((cutA.distance*cutB.normal.z-double(cutA.normal.z)*cutB.distance)/det),3,
                                       float((double(cutA.normal.x)*cutB.distance-cutA.distance*cutB.normal.x)/det)};
            check(positions(clipped).contains({intersection.x,intersection.y,intersection.z}),
                  "Clipped source intersection differs from its analytic plane intersection");
            cliffOptions::Mesh narrowMesh;
            narrowMesh.faces={{{{0,0,0},{.4f,0,.01f},{1,0,0}}},{{{1,0,0},{.4f,0,-.5f},{0,0,0}}}};
            auto elevation=[](Vector3 p){return 2+.5f*p.x*p.x;};
            const auto refined=refinePlateauFootprint(narrowMesh,elevation);
            const auto flatAudit=auditStrictSurface(refined);
            std::vector<Polygon> refinedDomains;
            for(auto f:refined.faces) {
                refinedDomains.push_back({f[0],f[1],f[2]});for(auto &p:f)p.y=elevation(p);
                const auto n=Vector3CrossProduct(sub(f[1],f[0]),sub(f[2],f[0]));
                check(n.y/Vector3Length(n)>=.12499f,"Adaptive roof refinement leaves a steep interpolation sliver");
            }
            check(refined.faces.size()>narrowMesh.faces.size() && flatAudit.exact.boundaryEdges==4 &&
                  flatAudit.exact.nonmanifoldEdges==0 && flatAudit.selfIntersections==0 && flatAudit.coplanarOverlaps==0 &&
                  std::abs(surfaceArea(refinedDomains)-.255f)<.000001f,
                  "Adaptive height sampling changes the roof footprint or fails to split its shared edge");
        }
#endif
        {
            CanyonAppearance base;
            auto roof=[&](float x0,float x1,float z0,float z1,float y) {
                const Vector3 a{x0,y,z0},b{x1,y,z0},c{x1,y,z1},d{x0,y,z1};
                base.triangles.push_back({{a,d,c},true});base.triangles.push_back({{a,c,b},true});
            };
            roof(0,4,0,4,2);roof(4,6,0,2,2);roof(4,6,2,4,2);
            roof(6,8,4,6,2); // Point contact must not join this island.
            roof(6,8,0,4,3); // A distinct upper terrace must remain separate.
            const cliffDetail::Quad selected{{0,0,0},{0,0,4},{0,2,4},{0,2,0}},neighbour{{6,0,4},{6,0,0},{6,2,0},{6,2,4}};
            for(auto q:{selected,neighbour}) {
                base.triangles.push_back({{q.ab,q.bt,q.at},true});base.triangles.push_back({{q.ab,q.bb,q.bt},true});
            }
            const auto region=planPlateauRegion(base,{selected});
            check(region.sourceFaces==6 && region.components==1 && region.selectedWalls==1 && region.neighbourWalls==1 &&
                  std::abs(region.projectedArea-24)<1e-6,"Plateau region missed a T-junction or crossed a point contact/height step");
            float boundary=0;for(auto e:region.boundary)boundary+=distance(e.a,e.b);
            check(std::abs(boundary-20)<.0001f,"Regional boundary contains an internal shared edge");
            const auto reached=planPlateauRegion(base,{selected},{{{5.5f,0,.5f},{5.5f,0,3.5f},{6.5f,0,3.5f},{6.5f,0,.5f}}});
            check(reached.components==2 && reached.sourceFaces==8 && std::abs(reached.projectedArea-32)<.0001f,
                  "A cap reaching the next terrace does not include that complete roof component");
            auto shifted=base;auto wall=selected;const Vector3 offset{100,0,-100};
            for(auto &t:shifted.triangles)for(auto &p:t.vertices)p=add(p,offset);
            for(auto p:{&wall.ab,&wall.bb,&wall.at,&wall.bt})*p=add(*p,offset);
            const auto translated=planPlateauRegion(shifted,{wall});
            check(translated.key==region.key && translated.sourceFaces==region.sourceFaces && translated.projectedArea==region.projectedArea,
                  "Plateau region ownership changes with coordinate frame");
#ifdef DEATHWARD_CLIFF_REGION_EXPERIMENT
            {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
                {
                    auto rectangle=[](float x0,float x1,float z0,float z1){return GradedRoofCell{{{x0,4,z0},{x0,4,z1},{x1,4,z1},{x1,4,z0}},{{0,1,0},4}};};
                    const std::vector<GradedRoofCell> cells{rectangle(0,1,0,1),rectangle(1,2,0,1),rectangle(2,3,1,2),rectangle(5,6,0,1)};
                    const auto mask=capDomain::retainedSource(cells,{rectangle(.25f,.75f,.25f,.75f).outline});
                    check(mask==std::vector<bool>({false,false,true,true}),"Cap domain discards an attached cell or crosses a point-only/empty connection");
                    const auto second=capDomain::retainedSource(cells,{rectangle(.25f,.75f,.25f,.75f).outline,rectangle(5,5+1.f/65536,.25f,.75f).outline});
                    check(second==std::vector<bool>({false,false,true,false}),"Cap domain loses a positive-area narrow cap contact");
                    const auto tangent=capDomain::retainedSource(cells,{rectangle(.25f,.75f,.25f,.75f).outline,rectangle(6,7,0,1).outline});
                    check(tangent==mask,"Cap domain treats a tangent cap edge as positive contact");
                    bool rejected=false;try{capDomain::retainedSource(cells,{rectangle(8,9,0,1).outline});}catch(const std::runtime_error &){rejected=true;}
                    check(rejected,"Cap domain accepts a construction with no positive cap contact");
                }
                {
                    const float q=1.f/65536;
                    const std::vector<Vector3> chain{{0,4,0},{.5f,4,.5f+q},{1,4,1-q},{1.5f,4,1.5f+q},{2,4,2}};
                    const Polygon sourceA{{0,4,0},{0,4,2},{2,4,2}},sourceB{{0,4,0},{2,4,2},{2,3,0}};
                    Polygon a{{0,4,0},{0,4,2},{2,4,2}},b=chain;b.push_back({2,3,0});
                    for(auto it=std::next(chain.rbegin());it!=chain.rend();++it)a.push_back(*it);
                    if(a.back().x==a.front().x && a.back().z==a.front().z)a.pop_back();
                    Plane slope;const double length=std::sqrt(1.5);slope.hasPreciseNormal=true;slope.preciseNormal={.5/length,1/length,-.5/length};slope.normal={float(slope.preciseNormal[0]),float(slope.preciseNormal[1]),float(slope.preciseNormal[2])};slope.distance=4/length;
                    for(auto &p:b)p.y=4+.5f*(p.z-p.x);
                    const auto simplified=sharedSourceEdges::simplify({{a,{{0,1,0},4}},{b,slope}},{sourceA,sourceB});
                    check(simplified.size()==2 && simplified[0].outline.size()==3 && simplified[1].outline.size()==3,
                          "Shared original-source interface retains grid-created zigzag vertices");
                    const auto boundary=sharedSourceEdges::simplify({{a,{{0,1,0},4}}},{sourceA});
                    for(size_t k=1;k+1<chain.size();++k) {
                        bool kept=false;for(const auto &cell:boundary)for(auto p:cell.outline)kept |= p.x==chain[k].x && p.z==chain[k].z;
                        check(kept,"Shared source simplification changes an outside or protected-cutout boundary");
                    }
                    auto rectangle=[](float x0,float x1,float z0,float z1){return GradedRoofCell{{{x0,4,z0},{x0,4,z1},{x1,4,z1},{x1,4,z0}},{{0,1,0},4}};};
                    const auto ring=sharedSourceEdges::simplify({rectangle(0,3,0,1),rectangle(0,3,2,3),rectangle(0,1,1,2),rectangle(2,3,1,2)},{{{0,4,0},{0,4,3},{3,4,3},{3,4,0}}});
                    sourceReuse::R ringArea=0;
                    for(const auto &cell:ring) {
                        const auto domain=sourceReuse::project(cell.outline);ringArea+=abs(sourceReuse::signedArea(domain))/2;
                        const auto cuts=sourceReuse::sides(domain);
                        check(!std::all_of(cuts.begin(),cuts.end(),[](const auto &h){return sourceReuse::value(h,sourceReuse::P{sourceReuse::R(1.5),sourceReuse::R(1.5)})<=0;}),"Shared source contour tracing fills a protected hole");
                    }
                    check(ringArea==8,"Shared source contour tracing changes a hole's exact area");
                }
                {
                    auto quad=[](float x0,float x1,float y){return Polygon{{x0,y,0},{x0,y,1},{x1,y,1},{x1,y,0}};};
                    const std::vector<GradedRoofCell> cells{{quad(0,1,5),{{0,1,0},5}},{quad(1,2,4),{{0,1,0},4}},{quad(2,3,4),{{0,1,0},4}}};
                    const auto selection=sourceReuse::select(cells,{quad(0,3,4)});
                    check(selection.eligible==std::vector<bool>({false,true,true}) && selection.guarded==std::vector<bool>({false,false,true}) && selection.transitionRetained==1,
                          "Source reuse skips a required transition across a roof-height jump");
                    auto shifted=[](Polygon p,float z){for(auto &q:p)q.z+=z;return p;};
                    auto entire=quad(0,2,4);for(auto &p:entire)p.z*=2;
                    const auto upper=shifted(quad(1,2,5),1);
                    const std::vector<GradedRoofCell> tiers{{shifted(quad(0,1,5),1),{{0,1,0},5}},{upper,{{0,1,0},5}},{quad(1,2,5),{{0,1,0},5}},{quad(0,1,3),{{0,1,0},3}}};
                    const auto vertical=sourceReuse::select(tiers,{entire,upper});
                    check(vertical.eligible==std::vector<bool>({false,true,false,false}) && std::none_of(vertical.guarded.begin(),vertical.guarded.end(),[](bool b){return b;}) && vertical.heightLinkRetained==1,
                          "Source reuse leaves two diagonal high sectors joined only by a vertical edge");
                    const auto tinyGap=sourceReuse::select({{quad(0,1,4),{{0,1,0},4}}},{quad(1e-12f,1,4)});
                    check(!tinyGap.guarded[0] && tinyGap.domainRejected==1,"Source reuse discards a positive tiny original-domain gap");
                    const auto higher=sourceReuse::select({{quad(0,1,4),{{0,1,0},4}}},{quad(0,1,4),quad(.5f,1,5)});
                    check(!higher.guarded[0] && higher.ownerRejected==1,"Source reuse hides a higher original terrain owner");
                    Volume replacement;replacement.faces={quad(0,2,3)};
                    const sourceReuse::Columns columns({replacement});bool removed=false;
                    const auto retained=columns.outside(quad(0,3,4),removed);
                    check(removed && retained.size()==1 && retained[0].size()==4,"Replacement columns do not preserve the original outside fragment");
                    for(auto p:retained[0])check(p.x>=2 && p.x<=3 && p.y==4,"Replacement column lowers or changes retained original terrain");
                    removed=false;const auto remote=columns.outside(quad(4,5,4),removed);
                    check(!removed && remote.size()==1 && !columns.contains({4.5f,4,.5f}) && columns.contains({1,4,.5f}),"Replacement columns change unrelated source terrain");
                    check(sourceReuse::R(.1)==sourceReuse::R(3602879701896397LL)/36028797018963968LL,"Source reuse does not interpret binary64 coefficients exactly");
                    Volume ownedCell;ownedCell.faces={{{64,4,0},{64,4,1},{65,4,1},{65,4,0}}};
                    const float quantum=1.f/65536;
                    const Polygon originalOwned{{64,4,-quantum/4},{64,4,1-quantum/4},{65,4,-quantum/4}};
                    sourceReuse::Columns sourceIdentity({ownedCell});bool beforeClaim=false,afterClaim=false;
                    check(!sourceIdentity.outside(originalOwned,beforeClaim).empty(),"Source ownership fixture has no original boundary remainder");
                    sourceIdentity.claimCanonicalSources({originalOwned});
                    check(sourceIdentity.outside(originalOwned,afterClaim).empty() && sourceIdentity.entries.size()==2,
                          "Original source boundary is cut again after its complete canonical domain was assigned to the edit");
                    Volume left,right;left.faces={{{0,4,0},{0,4,1},{1,4,1},{1,4,0}}};right.faces={{{2,4,0},{2,4,1},{3,4,1},{3,4,0}}};
                    sourceReuse::Columns separated({left,right});
                    separated.claimCanonicalSources({{{0,4,0},{3,4,0},{3,4,1}}});
                    check(separated.entries.size()==2,"Source ownership fills a positive gap between construction components");
                    Volume oldLeft,oldRight;oldLeft.faces={{{0,4,0},{0,4,1},{1,4,1},{1,4,0}}};oldRight.faces={{{1+quantum,4,0},{1+quantum,4,1},{2,4,1},{2,4,0}}};
                    cliffOptions::Mesh connectedRoof;connectedRoof.faces={{{{0,4,0},{0,4,1},{2,4,1}}},{{{0,4,0},{2,4,1},{2,4,0}}}};
                    const Polygon falseGap{{1+quantum/4,4,.25f},{1+quantum/4,4,.75f},{1+3*quantum/4,4,.25f}};
                    sourceReuse::Columns nominalCrop(std::vector<Volume>{oldLeft,oldRight}),renderedCrop(connectedRoof);bool nominalChanged=false,renderedChanged=false;
                    check(!nominalCrop.outside(falseGap,nominalChanged).empty() && renderedCrop.outside(falseGap,renderedChanged).empty(),
                          "Source crop reopens a gap absent from the connected replacement mesh");
                    cliffOptions::Mesh protectedRing;
                    auto addRoof=[&](float x0,float x1,float z0,float z1){protectedRing.faces.push_back({Vector3{x0,4,z0},Vector3{x0,4,z1},Vector3{x1,4,z1}});protectedRing.faces.push_back({Vector3{x0,4,z0},Vector3{x1,4,z1},Vector3{x1,4,z0}});};
                    addRoof(0,3,0,1);addRoof(0,3,2,3);addRoof(0,1,1,2);addRoof(2,3,1,2);
                    sourceReuse::Columns ringCrop(protectedRing);bool holeChanged=false;
                    check(!ringCrop.outside({{1.25f,4,1.25f},{1.25f,4,1.75f},{1.75f,4,1.25f}},holeChanged).empty() && !holeChanged,
                          "Rendered source shadow fills a protected hole");
                }
                {
                    const Polygon real{{0,0,0},{0,0,1},{1,0,1},{1,0,0}},fill{{1,0,0},{1,0,1},{2,0,1},{2,0,0}};
                    auto sample=[](Vector3){return PlateauVertexField{{{0,1,0},.5},{{0,1,0},3},{{0,1,0},.12}};};
                    auto retained=[](const Plane &p){return p.distance==4;};
                    const auto result=envelopePlateauSelectedSourcePlanes({{real,{{0,1,0},4}},{fill,{{0,1,0},.12}}},sample,retained);
                    cliffOptions::Mesh mesh;
                    for(const auto &cell:result)for(size_t k=1;k+1<cell.outline.size();++k)mesh.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});
                    check(std::abs(20-traceMesh(mesh,{.5f,20,.5f},{0,-1,0})-3.5f)<.00005f &&
                          std::abs(20-traceMesh(mesh,{1.5f,20,.5f},{0,-1,0})-2.5f)<.00005f,
                          "Artificial cap fill sets the retained-source transition width");
                    const auto cold=envelopePlateauSelectedSourcePlanes({{real,{{0,1,0},4}}},[](Vector3){return PlateauVertexField{{{0,1,0},0},{{0,1,0},3},{{0,1,0},.12}};},retained);
                    for(const auto &cell:cold)for(auto p:cell.outline)check(p.y==4,"Retained-source band changes its original cold roof");
                    bool rejected=false;
                    try{(void)envelopePlateauSelectedSourcePlanes({{fill,{{0,1,0},.12}}},[](Vector3){return PlateauVertexField{{{0,1,0},0},{{0,1,0},3},{{0,1,0},.12}};},retained);}
                    catch(const std::runtime_error &){rejected=true;}
                    check(rejected,"Retained-source width admits excluded cold terrain");
                }
                if(std::getenv("DW_CLIFF_EXACT_CONTACTS")) {
                    auto tetra=[](std::array<Vector3,4> p) {
                        cliffOptions::Mesh mesh;Volume volume;
                        for(const auto ids:{std::array<int,3>{0,2,1},std::array<int,3>{0,1,3},std::array<int,3>{0,3,2},std::array<int,3>{1,2,3}}) {
                            const cliffOptions::Triangle face{p[ids[0]],p[ids[1]],p[ids[2]]};mesh.faces.push_back(face);
                            const auto n=Vector3Normalize(Vector3CrossProduct(sub(face[1],face[0]),sub(face[2],face[0])));
                            volume.planes.push_back({n,projection(n,face[0])});
                        }
                        return std::pair{mesh,volume};
                    };
                    const auto a=tetra({{{50,50,50},{51,50,50},{50,51.5f,50},{50,50,52}}});
                    const Vector3 tip{std::nextafter(50.5f,51.f),std::nextafter(50.375f,0.f),50.5f};
                    const auto b=tetra({{tip,add(tip,{.25f,0,0}),add(tip,{0,.25f,0}),add(tip,{0,0,.25f})}});
                    const Vector3 spur{std::nextafter(tip.x,0.f),std::nextafter(tip.y,0.f),std::nextafter(tip.z,51.f)};
                    const auto bx=add(tip,{.25f,0,0}),by=add(tip,{0,.25f,0}),bz=add(tip,{0,0,.25f});
                    auto bad=a.first;
                    for(const auto &f:{cliffOptions::Triangle{tip,by,spur},cliffOptions::Triangle{spur,by,bx},
                        cliffOptions::Triangle{tip,spur,bz},cliffOptions::Triangle{spur,bx,bz},b.first.faces[2],b.first.faces[3]})bad.faces.push_back(f);
                    const auto before=auditStrictSurface(bad);check(before.selfIntersections>0 && before.selfIntersections<=16,
                        "Float repair fixture no longer has its tiny inter-solid crossing");
                    const auto repaired=repairBooleanFloatVertices(bad,{a.second,b.second});const auto after=auditStrictSurface(repaired);
                    check(after.selfIntersections==0 && after.coplanarOverlaps==0 && after.exact.components==before.exact.components && !after.exact.boundaryEdges && !after.exact.nonmanifoldEdges && !after.exact.degenerateFaces && repaired.faces.size()+2==bad.faces.size(),
                        "Source-checked short-edge cleanup does not resolve the tetrahedron spur crossing");
                    check(auditBoundaryCoverageQuiet(repaired,{a.second,b.second}).detachedFragments==0,
                        "Shared float repair leaves its nominal source boundary");
                    const auto denied=repairBooleanFloatVertices(bad,{});
                    check(denied.faces.size()==bad.faces.size(),"Float repair removes faces without source coverage");
                    for(size_t f=0;f<bad.faces.size();++f)for(int k=0;k<3;++k)check(distance(bad.faces[f][k],denied.faces[f][k])==0,
                        "Float repair changes geometry when source coverage rejects the proposed moves");
                }
                {
                    const Polygon a{{0,0,0},{0,0,1},{1,0,1}},b{{0,0,0},{1,0,1},{1,0,0}};
                    const auto result=envelopePlateauSourcePlanes({{a,{{-1,1,0},4}},{b,{{-1,1,0},4}}},
                        [](Vector3){return PlateauVertexField{{{-1,1,0},0},{{0,1,0},2},{{0,1,0},.12}};});
                    cliffOptions::Mesh mesh;std::vector<Polygon> footprint;
                    for(const auto &cell:result){auto projected=cell.outline;for(auto &p:projected)p.y=0;footprint.push_back(projected);for(size_t k=1;k+1<cell.outline.size();++k)mesh.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});}
                    check(std::abs(surfaceArea(footprint)-1)<1e-6,"Affine transition changes source footprint coverage");
                    for(float x:{.01f,.125f,.25f,.375f,.75f,.99f})for(float z:{.17f,.49f,.83f}) {
                        const float h=20-traceMesh(mesh,{x,20,z},{0,-1,0});
                        check(std::abs(h-std::min(4+x,5-3*x))<.00005f,
                              "Affine transition misses its source/band crossover or interior height bounds");
                    }
                    check(result.size()<=3,"Affine transition retains artificial source/grid plane fragments");
                    const Polygon square{{0,0,0},{0,0,1},{1,0,1},{1,0,0}};
                    const auto crossing=partitionPlateauEnvelopePieces({{square,{{-1,1,0},0}},{square,{{1,1,0},1}}},false);
                    cliffOptions::Mesh crossed;
                    for(const auto &cell:crossing)for(size_t k=1;k+1<cell.outline.size();++k)crossed.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});
                    for(float x:{.1f,.4f,.6f,.9f})check(std::abs(20-traceMesh(crossed,{x,20,.3f},{0,-1,0})-std::max(x,1-x))<.00005f,
                        "Disjoint-pair pruning removes a genuine overlapping-plane crossover");
                }
                {
                    const Polygon a{{0,0,0},{.25f,0,.5f},{.5f,0,1},{1,0,1}};
                    const Polygon b{{0,0,0},{0,0,1},{.5f,0,1},{.25f,0,.5f}};
                    auto field=[](Vector3){return PlateauVertexField{{{-1,1,0},0},{{0,1,0},2},{{0,1,0},.12}};};
                    const auto left=blendPlateauSourceVertices({{a,{{-1,1,0},0}}},field);
                    const auto right=blendPlateauSourceVertices({{b,{{0,1,-.5f},0}}},field);
                    auto seam=[](const auto &cells) {
                        std::map<std::pair<float,float>,float> values;
                        for(const auto &cell:cells)for(auto p:cell.outline)if(p.z==2*p.x)values[{p.x,p.z}]=p.y;
                        return values;
                    };
                    check(seam(left)==seam(right) && std::abs(seam(left).at({.25f,.5f})-.6875f)<1e-7f,
                          "Actual shared-vertex blending retains the nodal source-edge discontinuity");
                    const Plane original{{-1,1,0},4};
                    const auto cold=blendPlateauSourceVertices({{a,original}},[](Vector3){return PlateauVertexField{{{0,1,0},0},{{0,1,0},10},{{0,1,0},.12}};});
                    check(!cold.empty(),"Cold vertex blending deletes its original source");
                    for(const auto &cell:cold)check(planeNormal(cell.roof)==planeNormal(original) && cell.roof.distance==original.distance,
                                                   "Cold vertex blending refits the original source plane");
                    const float q=1.f/65536;
                    const Polygon thin{{0,0,0},{.5f,0,q},{1,0,0}};
                    const Polygon neighbour{{.5f,0,q},{.5f,0,1},{1,0,0}};
                    const auto regular=blendPlateauSourceVertices({{thin,{{-1,1,0},1}},{neighbour,{{-1,1,0},1}}},[](Vector3){return PlateauVertexField{{{-1,1,0},0},{{0,1,0},3},{{0,1,0},.12}};});
                    std::set<float> sharedHeights;size_t sharedUses=0;
                    for(const auto &cell:regular) {
                        check(planeNormal(cell.roof)[1]>.1,"Curved sampling leaves a pointed roof on a thin source triangle");
                        for(auto p:cell.outline){check(p.y>=1+p.x && p.y<=3,"Slope construction leaves the source/target envelope");if(p.x==0)check(p.y==1,"Slope construction changes a cold anchor");if(p.x==1)check(p.y==3,"Slope construction changes a full-target anchor");if(p.x==.5f && p.z==q){sharedHeights.insert(p.y);++sharedUses;}}
                    }
                    check(sharedUses>=2 && sharedHeights.size()==1,"Slope construction separates a shared source-edge vertex");
                }
                {
                    using Face=std::array<Vector3,3>;
                    const Face a{{{0,0,0},{0,0,1},{1,0,0}}};
                    auto classify=[&](const Face &b){return exactContact::classify(exactContact::Triangle(a),exactContact::Triangle(b));};
                    auto offset=a;for(auto &p:offset)p.y=std::numeric_limits<float>::denorm_min();
                    check(classify(offset)==0,"Exact contacts collapse distinct subnormal roof layers");
                    const float edge=1-std::ldexp(1.f,-20);
                    check(classify(Face{{{edge,0,0},{edge,0,1},{edge+1,0,0}}})==2,
                          "Exact contacts ignore a positive coplanar overlap below the old area threshold");
                    check(classify(Face{{{.25f,-1,.25f},{.25f,1,.25f},{.25f,0,.75f}}})==1,
                          "Exact contacts miss a genuine triangle crossing");
                    check(classify(Face{{{0,0,0},{0,0,1},{-1,1,0}}})==0 &&
                          classify(Face{{{0,0,0},{-1,1,0},{-1,0,-1}}})==0,
                          "Exact contacts reject a legitimate shared edge or vertex");
                    if(std::getenv("DW_CLIFF_EXACT_CONTACTS")) {
                        cliffOptions::Mesh separated;separated.faces={a,offset};
                        const auto full=auditSurfaceReplacement(separated,1);
                        check(!replacementIntersects(separated,1) && !full.selfIntersections && !full.coplanarOverlaps,
                              "Local and full exact replacement checks disagree for distinct roof layers");
                        cliffOptions::Mesh overlap;overlap.faces={a,Face{{{edge,0,0},{edge,0,1},{edge+1,0,0}}}};
                        check(replacementIntersects(overlap,1) && auditSurfaceReplacement(overlap,1).coplanarOverlaps==1,
                              "Local and full exact replacement checks disagree on a positive tiny overlap");
                    }
                }
                {
                    std::vector<LabelledSnapRing> rings{{{{0,0},{8,5},{8,0}},0},{{{0,5},{8,0},{0,0}},1}};
                    auto reversed=rings;std::reverse(reversed.begin(),reversed.end());
                    snapRoundPlateauRings(rings,8);snapRoundPlateauRings(reversed,8);
                    for(size_t i=0;i<rings.size();++i) {
                        check(std::find(rings[i].points.begin(),rings[i].points.end(),SnapPoint{4,3})!=rings[i].points.end(),
                              "Snap rounding gives crossing source edges different intersection vertices");
                        check(rings[i].points==reversed[reversed.size()-1-i].points,
                              "Snap rounding depends on labelled polygon order");
                    }
                    std::vector<LabelledSnapRing> contact{{{{0,0},{10,1},{10,-2}},0},{{{5,1},{6,3},{7,1}},1}};
                    snapRoundPlateauRings(contact,8);
                    check(std::find(contact[0].points.begin(),contact[0].points.end(),SnapPoint{5,1})!=contact[0].points.end(),
                          "Snap rounding leaves a nearby hot-pixel vertex detached from its edge");
                    for(long long sign:{-1LL,1LL}) {
                        std::vector<LabelledSnapRing> corner{{{{0,0},{sign,sign},{sign,0}},0},{{{0,sign},{sign,0},{0,0}},1}};
                        snapRoundPlateauRings(corner,8);
                        check(std::find(corner[1].points.begin(),corner[1].points.end(),SnapPoint{sign,sign})!=corner[1].points.end(),
                              "A crossing on a pixel corner remains detached from its rounded intersection");
                    }
                }
                {
                    const Polygon domain{{0,0,0},{0,0,2},{2,0,2},{2,0,0}};
                    const Polygon left{{0,0,0},{0,0,2},{1,0,2},{1,0,0}};
                    const Polygon hole{{.25f,0,.25f},{.25f,0,.75f},{.75f,0,.75f},{.75f,0,.25f}};
                    const auto cells=partitionPlateauCellOwnership({{domain,{{0,1,0},2}},{domain,{{0,1,0},10}}},{hole},{domain,left});
                    cliffOptions::Mesh mesh;
                    for(const auto &cell:cells)for(size_t k=1;k+1<cell.outline.size();++k)mesh.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});
                    check(std::abs(traceMesh(mesh,{.5f,20,1},{0,-1,0})-10)<.0001f &&
                          std::abs(traceMesh(mesh,{1.5f,20,1},{0,-1,0})-18)<.0001f,
                          "Shared source/grid labels leak a high owner outside its grid cut");
                    check(traceMesh(mesh,{.5f,20,.5f},{0,-1,0})>100,
                          "Shared source/grid labels fill a protected cutout");
                }
#endif
                PlateauRegion source;
                if(std::getenv("DW_CLIFF_SOURCE_NODE_BLEND") || std::getenv("DW_CLIFF_SOURCE_VERTEX_BLEND")) {
                    PlateauRegion thin;
                    thin.domains={{{-.4f,1,-.4f},{-.4f,1,.4f},{-.2f,1,.4f}},{{-.4f,1,-.4f},{-.2f,1,.4f},{-.2f,1,-.4f}}};
                    const Polygon cap{{-1,2,-1},{-1,2,1},{1,2,1},{1,2,-1}};
                    const std::vector<RoofGrade> front{{cap,{{0,1,0},2}}},lower{{cap,{{0,1,0},2},2}};
                    const auto blended=buildPlateauChunks(thin,{cap},front,lower,{}, {16,6,false});
                    check(!blended.chunks.empty(),"Source-aware nodal blending deletes its narrow source fixture");
                    for(const auto &chunk:blended.chunks)for(const auto &cell:chunk.cells)for(auto p:cell.outline)
                        check(p.y<=blended.landHeight+.0001f,"An off-roof fallback node adds a second height rise to a narrow source strip");
                }
                if(std::getenv("DW_CLIFF_SOURCE_VERTEX_BLEND")) {
                    PlateauRegion touching;
                    touching.domains={{{-1,2,-1},{-1,2,0},{0,2,0},{0,2,-1}},{{0,2,0},{0,2,1},{1,2,1},{1,2,0}}};
                    const Polygon cap{{2,3,-1},{2,3,1},{3,3,1},{3,3,-1}};
                    const std::vector<RoofGrade> front{{cap,{{0,1,0},3}}},lower{{cap,{{0,1,0},3},2}};
                    auto footprints=[](const auto &build){std::vector<Polygon> parts;for(const auto &chunk:build.chunks)for(const auto &cell:chunk.cells){auto p=cell.outline;for(auto &v:p)v.y=0;parts.push_back(p);}return parts;};
                    auto containsOrigin=[](const auto &parts) {
                        for(const auto &p:parts){bool inside=true;for(size_t k=0;k<p.size();++k){const auto a=p[k],b=p[(k+1)%p.size()];inside &= (double(b.x)-a.x)*(-a.z)-(double(b.z)-a.z)*(-a.x)<=0;}if(inside)return true;}return false;
                    };
                    const auto linked=footprints(buildPlateauChunks(touching,{cap},front,lower,{}, {16,6,false}));
                    check(plateauFootprintPinches(linked).empty() && containsOrigin(linked),"Source point contact does not receive a finite terrain link");
                    const Polygon protectedCorner{{0,0,-.5f},{0,0,0},{.5f,0,0},{.5f,0,-.5f}};
                    const auto cut=footprints(buildPlateauChunks(touching,{cap},front,lower,{protectedCorner}, {16,6,false}));
                    check(plateauFootprintPinches(cut).empty() && !containsOrigin(cut),"Source point repair fills its protected floor corner");
                }
                auto p=[](float x,float z){return Vector3{x,3+.125f*x-.0625f*z,z};};
                source.domains={{p(-8,-8),p(-8,8),p(8,8)},{p(-8,-8),p(8,8),p(8,-8)},{{50,100,50},{50,100,60},{60,100,60}}};
                const Polygon cap{{-1,4,-1},{-1,4,1},{1,4,1},{1,4,-1}};
                const std::vector<RoofGrade> constraints{{cap,{{0,1,0},4}}},lower{{cap,{{0,1,0},4},2}};
                {
                    const Polygon distantCap{{50,4,-25},{50,4,-23.5f},{52,4,-23.5f},{52,4,-25}};
                    const std::vector<RoofGrade> front{{distantCap,{{0,1,0},4}}},bottom{{distantCap,{{0,1,0},4},2}};
                    PlateauRegion strip;
                    strip.domains={{{50.70939254760742f,3.147385835647583f,-17.58802604675293f},
                                    {50.464942932128906f,2.941697120666504f,-17.55130958557129f},
                                    {51.44185256958008f,2.7670810222625732f,-16.6192626953125f}}};
                    auto asMesh=[](const PlateauChunkBuild &build){cliffOptions::Mesh m;for(const auto &chunk:build.chunks)for(const auto &cell:chunk.cells)for(size_t k=1;k+1<cell.outline.size();++k)m.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});return m;};
                    const auto preserved=asMesh(buildPlateauChunks(strip,{distantCap},front,bottom,{}, {16,6,false}));
                    auto triangles=[](const cliffOptions::Mesh &mesh) {
                        std::set<std::array<float,9>> keys;
                        for(auto face:mesh.faces){std::sort(face.begin(),face.end(),[](auto a,auto b){return std::array<float,3>{a.x,a.y,a.z}<std::array<float,3>{b.x,b.y,b.z};});std::array<float,9> key{};for(int i=0;i<3;++i){key[3*i]=face[i].x;key[3*i+1]=face[i].y;key[3*i+2]=face[i].z;}keys.insert(key);}return keys;
                    };
                    check(triangles(preserved)==triangles(asMesh(buildPlateauChunks(strip,{distantCap},front,bottom,{}, {8,6,false}))),
                          "Source-plane geometry depends on chunk grouping");
                    const auto f=strip.domains[0];const auto n=Vector3CrossProduct(sub(f[1],f[0]),sub(f[2],f[0]));
                    const Vector3 sample{51.098388671875f,10,-17};
                    const double expected=f[0].y-(double(n.x)*(sample.x-f[0].x)+double(n.z)*(sample.z-f[0].z))/n.y;
                    check(std::abs((10-traceMesh(preserved,sample,{0,-1,0}))-expected)<.0001,
                          "Source-plane cells drop a narrow retained roof strip between grid nodes");
                    PlateauRegion crossing;
                    auto patch=[](float sign){Polygon p;for(auto q:std::array<Vector2,4>{{{50,-18},{50,-16.5f},{52,-16.5f},{52,-18}}})p.push_back({q.x,2+sign*.5f*(q.x-51.2f),q.y});return p;};
                    crossing.domains={patch(1),patch(-1)};
                    const auto creased=asMesh(buildPlateauChunks(crossing,{distantCap},front,bottom,{}, {16,6,false}));
                    for(float x:{50.75f,51.1f,51.3f,51.8f}) {
                        const float actual=10-traceMesh(creased,{x,10,-17},{0,-1,0});
                        check(std::abs(actual-(2+.5f*std::abs(x-51.2f)))<.0001,
                              "Source-plane partition interpolates across an original roof-plane crossing");
                    }
                }
                const auto chunks=buildPlateauChunks(source,{cap},constraints,lower,{}, {4,2});
                check(chunks.localFaces==2 && chunks.regionalFaces==3 && chunks.landHeight<5,
                      "Distant highland changes the local chunk target or construction scope");
                std::map<float,float> left,right;bool retainedBorder=false;
                for(const auto &chunk:chunks.chunks)for(const auto &cell:chunk.cells)for(auto v:cell.outline) {
                    if(v.x==0 && chunk.x==-1)left[v.z]=v.y;
                    if(v.x==0 && chunk.x==0)right[v.z]=v.y;
                    if(std::abs(v.x)==3 || std::abs(v.z)==3) {
                        retainedBorder=true;check(std::abs(v.y-p(v.x,v.z).y)<.00001f,"Compact edit changes retained height at its outer grid boundary");
                    }
                    check(v.x>=-3 && v.x<=3 && v.z>=-3 && v.z<=3,"Chunk construction escapes its finite influence halo");
                }
                check(retainedBorder && !left.empty() && left==right,"Adjacent negative/positive chunks disagree on shared roof nodes");
                auto geometry=[](const PlateauChunkBuild &build) {
                    std::multiset<std::vector<std::array<float,3>>> cells;
                    for(const auto &chunk:build.chunks)for(const auto &cell:chunk.cells){std::vector<std::array<float,3>> points;for(auto p:cell.outline)points.push_back({p.x,p.y,p.z});cells.insert(std::move(points));}return cells;
                };
                check(geometry(chunks)==geometry(buildPlateauChunks(source,{cap},constraints,lower,{}, {8,2})),
                      "Changing chunk ownership changes the shared roof geometry");
                const Polygon protectedCap{{-.5f,0,-.5f},{-.5f,0,.5f},{.5f,0,.5f},{.5f,0,-.5f}};
                const auto cutChunks=buildPlateauChunks(source,{cap},constraints,lower,{protectedCap},{4,2});
                std::vector<Polygon> footprints;for(const auto &chunk:cutChunks.chunks)for(const auto &cell:chunk.cells){auto poly=cell.outline;for(auto &v:poly)v.y=0;footprints.push_back(std::move(poly));}
                check(!covers(footprints,{0,0,0}),"A chunk fills the protected cap-strip cutout");
                PlateauRegion tiers;
                tiers.domains={{{-8,2,-8},{-8,2,8},{0,2,8},{0,2,-8}},{{0,4,-8},{0,4,8},{8,4,8},{8,4,-8}}};
                const auto continuous=buildPlateauChunks(tiers,{cap},constraints,lower,{}, {4,2});
                std::map<float,std::set<float>> seam;
                for(const auto &chunk:continuous.chunks)for(const auto &cell:chunk.cells)for(auto v:cell.outline)
                    if(v.x==0)seam[v.z].insert(v.y);
                check(!seam.empty() && std::all_of(seam.begin(),seam.end(),[](const auto &entry){return entry.second.size()==1;}),
                      "A continuous chunk roof retains an internal discontinuity between source tiers");
                PlateauRegion ramp;
                ramp.domains={{{-8,-16,-8},{-8,-16,8},{8,16,8},{8,16,-8}}};
                const Polygon smallCap{{-.5f,4,-.5f},{-.5f,4,.5f},{.5f,4,.5f},{.5f,4,-.5f}};
                const auto clamped=buildPlateauChunks(ramp,{smallCap},{{smallCap,{{0,1,0},4}}},{{smallCap,{{0,1,0},4},.25f}},{},{16,1});
                auto roofHeight=[&](float x,float z) {
                    double result=-1e9;
                    for(const auto &chunk:clamped.chunks)for(const auto &cell:chunk.cells)if(covers({cell.outline},{x,20,z})) {
                        const auto n=planeNormal(cell.roof);result=std::max(result,(cell.roof.distance-n[0]*x-n[2]*z)/n[1]);
                    }
                    return result;
                };
                const double a=roofHeight(1,0),b=roofHeight(2,0),mid=roofHeight(1.5f,0);
                check(a>=3.875-.00001 && b>0 && std::abs(mid-(a+b)*.5)<.00001,
                      "A lower-cap constraint introduces a new crease inside a shared grid edge");
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
                if(std::getenv("DW_CLIFF_POLYGON_CONTOURS")) {
                    const auto capped=buildPlateauChunks(ramp,{smallCap},{{smallCap,{{0,1,0},4}}},{{smallCap,{{0,1,0},4},2}},{smallCap});
                    bool boundary=false;
                    for(const auto &chunk:capped.chunks)for(const auto &cell:chunk.cells)for(auto p:cell.outline)
                        if(p.x==.5f && p.z>=-.5f && p.z<=.5f){boundary=true;check(std::abs(p.y-4)<.00001,"The body rises above its protected cap boundary");}
                    check(boundary,"The protected cap boundary has no shared height controls");
                }
#endif
            }
            std::vector<Polygon> ring;
            for(int x=0;x<3;++x)for(int z=0;z<3;++z)if(x!=1 || z!=1)ring.push_back({{float(x),0,float(z)},{float(x),0,float(z+1)},{float(x+1),0,float(z+1)},{float(x+1),0,float(z)}});
            ring.push_back(ring.front()); // Union must discard overlap, not double-count it.
            const auto domains=plateauRegionFootprint(ring);
            const std::vector<Polygon> touchingDomains{{{0,0,0},{0,0,1},{1,0,1},{1,0,0}},{{1,0,1},{1,0,2},{2,0,2},{2,0,1}}};
            check(plateauFootprintPinches(touchingDomains).size()==1,"A point-only footprint contact was not identified");
            const auto bridged=bridgePlateauFootprintPinches(touchingDomains);
            check(plateauFootprintPinches(bridged).empty(),"The finite plateau bridge retains a pinched vertex");
            const auto bridgeAudit=auditStrictSurface(meshPlateauFootprint(bridged));
            check(bridgeAudit.exact.components==1 && bridgeAudit.exact.nonmanifoldEdges==0 && bridgeAudit.nonmanifoldVertices==0 &&
                  bridgeAudit.selfIntersections==0 && bridgeAudit.coplanarOverlaps==0,
                  "A finite footprint bridge fails the exact projected-surface audit");
            const auto bridgeMesh=meshPlateauFootprint(bridged);
            check(std::abs(traceMesh(bridgeMesh,{.99f,10,1.01f},{0,-1,0})-10)<.0001f &&
                  traceMesh(bridgeMesh,{.9f,10,1.1f},{0,-1,0})==1000,
                  "The terrain link has no finite width or extends beyond its local shape");
            const Polygon protectedLink{{.98f,0,.98f},{.98f,0,1.02f},{1.02f,0,1.02f},{1.02f,0,.98f}};
            const auto cutBridge=meshPlateauFootprint(plateauRegionFootprint(bridged,{protectedLink}));
            check(traceMesh(cutBridge,{1,10,1},{0,-1,0})==1000,
                  "A finite terrain link fills a later protected cutout");
            check(std::abs(surfaceArea(domains)-8)<1e-6 && !covers(domains,{1.5f,0,1.5f}) && covers(domains,{.5f,0,.5f}),
                  "Shared region decomposition fills a hole or double-counts overlap");
            const auto joined=plateauRegionFootprint(region.domains);
            check(std::abs(surfaceArea(joined)-24)<1e-6,"Regional footprint loses a connected roof domain");
            auto extended=region.domains;extended.push_back({{6,0,1},{6,0,3},{8,0,3},{8,0,1}});
            const auto extension=plateauRegionFootprint(extended);
            const auto external=surfaceBoundary(weldSurface(extension,.000008f,true),true);
            const auto constraints=plateauRegionConstraints(region,external);
            float retainedRight=0;
            for(const auto &g:constraints)if(g.protectedRoof[0].x==6 && g.protectedRoof[1].x==6)
                retainedRight+=std::abs(g.protectedRoof[0].z-g.protectedRoof[1].z);
            check(std::abs(retainedRight-2)<.0001f,"A covered internal source edge still constrains the shared roof");
            const Polygon outer{{0,0,0},{0,0,3},{3,0,3},{3,0,0}},hole{{1,0,1},{1,0,2},{2,0,2},{2,0,1}};
            const auto cut=plateauRegionFootprint({outer},{hole});
            const auto sampled=samplePlateauRegionRoof(cut,4,{{hole,{{0,1,0},2}}});
            cliffOptions::Mesh roofMesh;for(const auto &cell:sampled)roofMesh.faces.push_back({cell.outline[0],cell.outline[1],cell.outline[2]});
            const auto sampledAudit=auditStrictSurface(roofMesh);
            // Compare the projected perimeter: valid triangulators may retain
            // different collinear split nodes on the same outer/hole loops.
            double sampledProjectedBoundary=0;
            for(auto edge:surfaceBoundary(roofMesh))sampledProjectedBoundary+=std::hypot(double(edge[1].x)-edge[0].x,double(edge[1].z)-edge[0].z);
            check(std::abs(sampledProjectedBoundary-16)<.0001 && sampledAudit.exact.components==1 && sampledAudit.exact.nonmanifoldEdges==0 && sampledAudit.nonmanifoldVertices==0 &&
                  sampledAudit.selfIntersections==0 && sampledAudit.coplanarOverlaps==0 && sampledAudit.exact.windingErrors==0 &&
                  traceMesh(roofMesh,{1.5f,20,1.5f},{0,-1,0})==1000,
                  "Sampled shared roof opens a height T-junction or covers its protected hole");
            check(std::abs((20-traceMesh(roofMesh,{1.5f,20,1},{0,-1,0}))-2)<.0001f,
                  "Sampled regional roof does not meet its protected cap boundary");
            const auto touching=meshPlateauFootprint({{{0,0,0},{0,0,1},{1,0,1},{1,0,0}},{{1,0,1},{1,0,2},{2,0,2},{2,0,1}}});
            const auto pieces=splitSurfaceComponents(touching);
            check(pieces.size()==2 && auditStrictSurface(touching).nonmanifoldVertices==1,
                  "Point-touching roof domains were mistaken for one manifold component");
            for(const auto &piece:pieces)check(auditStrictSurface(piece).nonmanifoldVertices==0,
                  "A separated regional roof component still has a pinched vertex");
#endif
        }
        {
            const std::vector<Vector3> controls{{0,2,0},{4,3,0},{4,3.5f,4},{0,2.5f,4},{2,2.4f,2},{2,2.5f,0}};
            const auto roof=triangulatePlateauRoof(controls),replay=triangulatePlateauRoof(controls);
            check(roof.size()==replay.size(),"Plateau roof triangulation changed on replay");
            double projected=0;
            cliffOptions::Mesh surface;surface.faces=roof;
            for(size_t i=0;i<roof.size();++i) {
                const auto cross=Vector3CrossProduct(sub(roof[i][1],roof[i][0]),sub(roof[i][2],roof[i][0]));
                check(cross.y>0,"Regional plateau roof has a folded or zero-area cell");projected+=cross.y*.5;
                for(int k=0;k<3;++k)check(distance(roof[i][k],replay[i][k])==0,"Plateau roof replay changed a vertex");
            }
            check(std::abs(projected-16)<1e-5,"Regional roof has a projected hole or overlap");
            for(auto p:controls)check(std::abs(traceMesh(surface,add(p,{0,5,0}),{0,-1,0})-5)<.0001f,
                                      "Regional roof did not preserve a cap/terrain height control");
            const auto strict=auditStrictSurface(surface);
            check(strict.selfIntersections==0 && strict.coplanarOverlaps==0 && strict.nonmanifoldVertices==0,
                  "Regional roof triangulation crosses itself");
            bool rejected=false;
            try{(void)triangulatePlateauRoof({{0,1,0},{1,2,0},{2,3,0}});}catch(const std::runtime_error &){rejected=true;}
            check(rejected,"Collinear plateau roof was accepted as a surface");
        }
        {
            const auto domain=triangulatePlateauBoundary({{0,2,0},{0,2,2},{1,2,2},{1,2,1},{2,2,1},{2,2,0}});
            cliffOptions::Mesh roof;roof.faces=domain;double area=0;
            for(const auto &t:domain){const auto n=Vector3CrossProduct(sub(t[1],t[0]),sub(t[2],t[0]));check(n.y>0,"Constrained roof winding changed");area+=n.y*.5;}
            check(std::abs(area-3)<1e-6,"Concave roof footprint gained or lost projected area");
            check(traceMesh(roof,{1.5f,5,1.5f},{0,-1,0})==1000,"Concave front boundary was replaced by a convex chord");
            check(std::abs(traceMesh(roof,{.5f,5,1.5f},{0,-1,0})-3)<1e-6,"Constrained roof lost useful plateau coverage");
            bool rejected=false;try{(void)triangulatePlateauBoundary({{0,0,0},{2,0,2},{0,0,2},{2,0,0}});}catch(const std::runtime_error &){rejected=true;}
            check(rejected,"Self-crossing plateau boundary was accepted");
        }
        const Vector3 a{0,0,0},b{1,0,0},c{1,0,1},d{0,0,1};
        const Vector3 A{0,1,0},B{1,1,0},C{1,1,1},D{0,1,1};
        std::vector<Polygon> cube{{a,b,c,d},{A,D,C,B,{.5f,1,0}},
                                  {a,A,B,b},{b,B,C,c},{c,C,D,d},{d,D,A,a}};
        auto welded=weldSurface(cube);
        const auto strictCube=auditStrictSurface(welded);
        check(strictCube.exact.boundaryEdges==0 && strictCube.nonmanifoldVertices==0 && strictCube.selfIntersections==0 && strictCube.coplanarOverlaps==0,
              "Strict verifier rejected a valid cube");
        {
            // Tiled closed solids force metre-bin boundary contacts and
            // mid-edge T junctions at enough vertices to exercise the index.
            std::vector<Polygon> tiled;
            for(int x=0;x<5;++x)for(int z=0;z<5;++z)for(auto face:cube) {
                for(auto &p:face){p.x+=x;p.z+=z;}
                tiled.push_back(std::move(face));
            }
            const auto surface=weldSurface(tiled);
            const auto audit=auditStrictSurface(surface);
            check(audit.exact.boundaryEdges==0 && audit.exact.nonmanifoldEdges==0 && audit.nonmanifoldVertices==0 &&
                  audit.selfIntersections==0 && audit.coplanarOverlaps==0 && audit.exact.components==1,
                  "Indexed weld did not preserve a tiled solid with boundary T junctions");
        }
        auto cubeSolid=box(0,1,0,1);cubeSolid.planes[2].distance=0;
        {
            const Box bounds{{0,-.12f,-1},{2,3,2}};
            auto cap=[](float y,float z0,float z1,bool upward=true) {
                Polygon p{{-1,y,z0},{-1,y,z1},{0,y,z1},{0,y,z0}};
                if(!upward)std::reverse(p.begin(),p.end());return p;
            };
            check(buriedContextBoundary({Vector3{0,.2f,.5f},Vector3{0,1.8f,.5f}},{cap(2,-1,2)},bounds),
                  "A fully buried work-border edge was rejected");
            const std::vector<Polygon> overhang{cap(.3f,-1,2),cap(.7f,-1,2,false),cap(1.2f,-1,2)};
            check(!buriedContextBoundary({Vector3{0,.1f,.5f},Vector3{0,1.1f,.5f}},overhang,bounds),
                  "Buried-edge classification concealed an overhang air gap");
            check(!buriedContextBoundary({Vector3{0,1,-.5f},Vector3{0,1,.5f}},{cap(2,-1,.1f),cap(2,.2f,2)},bounds),
                  "Whole-edge proof missed a projected gap between endpoint/midpoint samples");
            check(!buriedContextBoundary({Vector3{0,.2f,.5f},Vector3{0,1.8f,.5f}},{},bounds),
                  "Missing context was treated as buried solid");
        }
        {
            Experiment floorJoin;
            floorJoin.protectedFloor={{{0,1,0},{0,1,1},{1,1,1},{1,1,0}}};
            const std::vector<Polygon> ground{{{-1,.5f,-1},{-1,.5f,2},{2,.5f,2},{2,.5f,-1}}};
            const auto joined=assembleSurface(ground,floorJoin,floorJoin.protectedFloor);
            check(traceMesh(joined,{.5f,2,.5f},{0,-1,0})==1000,
                  "A reconstructed terrain face remained buried beneath preserved floor");
            check(std::abs(traceMesh(joined,{1.5f,2,.5f},{0,-1,0})-1.5f)<1e-4f,
                  "Floor-interface cleanup removed visible neighbouring ground");
            check(floorJoin.floorBoundaryEdges>0 && floorJoin.unexpectedBoundaryEdges==0,
                  "Buried floor interfaces lacked whole-edge coverage proof");
        }
        {
            Experiment join;
            join.seededComposition=true;join.mesh=welded;join.volumes={cubeSolid};
            join.editBounds={{0,-.12f,-1},{2,3,2}};
            auto cap=[](float y,bool up) {
                Polygon p{{-1,y,-1},{-1,y,2},{0,y,2},{0,y,-1}};
                if(!up)std::reverse(p.begin(),p.end());return p;
            };
            const auto surface=assembleSurface({},join,{cap(.3f,true),cap(.7f,false),cap(1.5f,true)},true);
            check(std::abs(traceMesh(surface,{.5f,1.2f,1.5f},{-1,0,0})-.5f)<.0001f,
                  "Missing old-minus-new terrain closure above the replacement");
            check(traceMesh(surface,{.5f,.5f,1.5f},{-1,0,0})==1000,
                  "Context closure filled the old overhang's air gap");
            check(std::abs(traceMesh(surface,{-.5f,.5f,.5f},{1,0,0})-.5f)<.0001f,
                  "Context closure removed the new wall in old overhang air");
        }
        {
            const Polygon footprint{{-2,4,-2},{-2,4,4},{2,4,4},{2,4,-2}};
            const RoofGrade cap{{{-1,2,0},{-1,2,.6f},{1,2,.6f},{1,2,0}},{{0,1,0},2}};
            const auto cells=gradePlateauRoof(footprint,4,{cap});
            cliffOptions::Mesh roof;double projected=0;
            for(const auto &cell:cells)for(size_t k=1;k+1<cell.outline.size();++k) {
                const auto a=cell.outline[0],b=cell.outline[k],c=cell.outline[k+1];
                projected+=std::abs((double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x))*.5;
                roof.faces.push_back({a,b,c});
            }
            check(std::abs(projected-24)<.0001,"Graded land partition gained or lost area");
            auto height=[&](float x,float z){return 20-traceMesh(roof,{x,20,z},{0,-1,0});};
            check(std::abs(height(0,.3f)-2)<.0001f,"Grading changed the protected front roof");
            check(std::abs(height(0,1.6f)-3)<.0001f,"Rear grading has a vertical cap lip");
            check(std::abs(height(0,3)-4)<.0001f,"Rear grading did not merge into common land");
            check(std::abs(height(1.5f,.3f)-2.5f)<.0001f,"Lateral grading did not preserve the prescribed slope");
            check(std::abs(height(0,.6001f)-height(0,.5999f))<.0003f,"Protected-strip transition is discontinuous");
            const auto audit=auditStrictSurface(roof);
            check(audit.selfIntersections==0 && audit.coplanarOverlaps==0 && audit.nonmanifoldVertices==0,
                  "Graded roof partition crosses or overlaps itself");
            auto meshFor=[](const std::vector<GradedRoofCell> &cells) {
                cliffOptions::Mesh mesh;for(const auto &cell:cells)for(size_t k=1;k+1<cell.outline.size();++k)mesh.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});return mesh;
            };
            const auto unpruned=meshFor(gradePlateauRoof(footprint,4,{cap},1,false));
            for(int x=0;x<=20;++x)for(int z=0;z<=30;++z) {
                const Vector3 p{-2+x*.2f,20,-2+z*.2f};
                check(std::abs(traceMesh(roof,p,{0,-1,0})-traceMesh(unpruned,p,{0,-1,0}))<.0001f,
                      "Conservative grade pruning changed the roof field");
            }
            const Polygon far{{-10,4,3},{-10,4,5},{10,4,5},{10,4,3}};
            check(gradePlateauRoof(far,4,{cap}).size()==1,"Unaffected common land was needlessly partitioned");
            const std::vector<RoofGrade> old{
                {{{-2,2.8f,-2},{-2,2.8f,4},{0,3,4},{0,3,-2}},{{-.1f,1,0},3}},
                {{{0,3,-2},{0,3,4},{2,3.2f,4},{2,3.2f,-2}},{{-.1f,1,0},3}}};
            const auto collar=meshFor(blendPlateauBoundary({{footprint,{{0,1,0},4}}},old,{{{0,0,1},4}}));
            for(float x:{-1.f,0.f,1.f}) {
                check(std::abs((20-traceMesh(collar,{x,20,4},{0,-1,0}))-(3+.1f*x))<.0001f,
                      "Rear collar does not match the retained roof at its boundary");
                check(std::abs((20-traceMesh(collar,{x,20,3},{0,-1,0}))-(3.8f+.1f*x))<.0001f,
                      "Rear collar has a height step across source roof cells");
                check(std::abs((20-traceMesh(collar,{x,20,1},{0,-1,0}))-4)<.0001f,
                      "Rear collar changed interior common land");
            }
            const RoofGrade crown{cap.protectedRoof,{{.2f,1,0},2}};
            const std::vector<RoofGrade> interiorStep{
                {{{-2,2,-2},{-2,2,2},{2,2,2},{2,2,-2}},{{0,1,0},2}},
                {{{-2,3,2},{-2,3,4},{2,3,4},{2,3,2}},{{0,1,0},3}}};
            const auto boundaryGrades=plateauBoundaryGrades(footprint,interiorStep,{{{0,0,1},4}});
            const auto smoothCollar=meshFor(gradePlateauRoof(footprint,4,boundaryGrades));
            check(boundaryGrades.size()==1,"A flat source boundary retained unnecessary interior partitions");
            for(float x:{-1.f,0.f,1.f}) {
                check(std::abs((20-traceMesh(smoothCollar,{x,20,4},{0,-1,0}))-3)<.0001f,
                      "Boundary-derived collar lost its retained roof constraint");
                check(std::abs((20-traceMesh(smoothCollar,{x,20,3},{0,-1,0}))-3.8f)<.0001f,
                      "Boundary-derived collar changed its inward slope");
                check(std::abs(traceMesh(smoothCollar,{x,20,1.999f},{0,-1,0})-traceMesh(smoothCollar,{x,20,2.001f},{0,-1,0}))<.0001f,
                      "An interior source step propagated into the common roof");
            }
            const auto slopeGrades=plateauBoundaryGrades(footprint,old,{{{0,0,1},4}});
            const auto slopedCollar=meshFor(gradePlateauRoof(footprint,4,slopeGrades));
            for(float x:{-1.f,0.f,1.f})check(std::abs((20-traceMesh(slopedCollar,{x,20,4},{0,-1,0}))-(3+.1f*x))<.0001f,
                  "Boundary-derived collar flattened a sloped source edge");
            const auto overlappingGrades=plateauBoundaryGrades(footprint,
                {{footprint,{{-.2f,1,0},3}},{footprint,{{.2f,1,0},3}}},{{{0,0,1},4}});
            const auto upperBoundary=meshFor(gradePlateauRoof(footprint,4,overlappingGrades));
            check(overlappingGrades.size()==2,"Boundary trace missed an interior source-plane crossing");
            for(float x:{-1.f,0.f,1.f})check(std::abs((20-traceMesh(upperBoundary,{x,20,4},{0,-1,0}))-(3+.2f*std::abs(x)))<.0001f,
                  "Boundary trace selected a hidden roof inside overlapping source domains");
            cliffOptions::Mesh crowned;
            for(const auto &cell:gradePlateauRoof(footprint,4,{cap,crown}))
                for(size_t k=1;k+1<cell.outline.size();++k)crowned.faces.push_back({cell.outline[0],cell.outline[k],cell.outline[k+1]});
            check(std::abs((20-traceMesh(crowned,{.5f,20,.3f},{0,-1,0}))-1.9f)<.0001f,
                  "Grading preserved only one facet of a protected crown");
            check(std::abs((20-traceMesh(crowned,{-.5f,20,.3f},{0,-1,0}))-2)<.0001f,
                  "Grading chose a hidden crown plane instead of the convex roof envelope");
        }
        {
            // A shared node quantized just inside a long thin face makes its
            // split boundary concave. The old center fan folded across A-P.
            const Polygon face{{0,0,0},{0,0,.0001f},{4,0,.0001f},{4,0,0}};
            const Polygon neighbour{{0,0,0},{.1f,0,.000019f},{0,0,-.001f}};
            for(int axis=0;axis<3;++axis) {
                auto rotate=[&](Polygon p) {
                    for(auto &v:p)for(int k=0;k<axis;++k)v={v.y,v.z,v.x};return p;
                };
                const auto welded=weldSurface({rotate(face),rotate(neighbour)},.00002f,true,true);
                const auto audit=auditStrictSurface(welded);
                check(welded.faces.size()==4 && audit.selfIntersections==0 && audit.coplanarOverlaps==0 &&
                      audit.exact.nonmanifoldEdges==0 && audit.exact.windingErrors==0 && audit.exact.components==1,
                      "Off-edge split node folds a thin horizontal or vertical face");
            }
        }
        {
            const std::vector<Polygon> strips{
                {{59.53956604003906f,0,-34.00657653808594f},{59.50617980957031f,0,-34.02409362792969f},{59.50616455078125f,0,-34.024078369140625f}},
                {{59.50617980957031f,0,-34.02409362792969f},{59.53956604003906f,0,-34.00657653808594f},{59.53956604003906f,0,-34.05293273925781f}},
                {{59.50617980957031f,0,-34},{59.53956604003906f,0,-34.00657653808594f},{59.50617980957031f,0,-34.02409362792969f}}};
            const auto partition=arrangePlateauFootprint(strips);const auto audit=auditStrictSurface(partition);
            check(!partition.faces.empty() && audit.exact.nonmanifoldEdges==0 && audit.exact.windingErrors==0 &&
                  audit.exact.duplicateFaces==0 && audit.exact.degenerateFaces==0 && audit.selfIntersections==0 && audit.coplanarOverlaps==0,
                  "Native one-quantum roof-strip witness has no disjoint projected arrangement");
            const float next=std::nextafter(64.f,65.f);
            const std::vector<Polygon> verticalChain{
                {{64,0,0},{64,0,1},{next,0,1}},
                {{63.5f,0,.125f},{63.5f,0,.25f},{64.5f,0,.25f}},
                {{63.5f,0,.375f},{63.5f,0,.5f},{64.5f,0,.5f}}};
            const auto chained=arrangePlateauFootprint(verticalChain);const auto chainAudit=auditStrictSurface(chained);
            check(!chained.faces.empty() && chainAudit.exact.nonmanifoldEdges==0 && chainAudit.exact.degenerateFaces==0 &&
                  chainAudit.selfIntersections==0 && chainAudit.coplanarOverlaps==0,
                  "Distinct crossing heights sharing one rendered X coordinate collapse together");
            const std::vector<Polygon> ring{
                {{0,0,0},{0,0,3},{1,0,3},{1,0,0}},{{2,0,0},{2,0,3},{3,0,3},{3,0,0}},
                {{1,0,0},{1,0,1},{2,0,1},{2,0,0}},{{1,0,2},{1,0,3},{2,0,3},{2,0,2}}};
            const auto arrangedRing=arrangePlateauFootprint(ring);
            check(traceMesh(arrangedRing,{1.5f,10,1.5f},{0,-1,0})==1000 &&
                  std::abs(traceMesh(arrangedRing,{.5f,10,1.5f},{0,-1,0})-10)<.0001f,
                  "Projected arrangement fills a protected hole or removes retained land");
        }
        {
            auto prism=[](float x0,float x1,float z0,float z1,float gradient=0.f) {
                Volume v;const auto n=Vector3Normalize(Vector3{-gradient,1,0});
                v.planes={{n,2*double(n.y)},{{0,-1,0},.12},{{-1,0,0},-x0},{{1,0,0},x1},{{0,0,-1},-z0},{{0,0,1},z1}};
                v.faces={{{x0,2+gradient*x0,z0},{x0,2+gradient*x0,z1},{x1,2+gradient*x1,z1},{x1,2+gradient*x1,z0}}};return v;
            };
            const std::vector<Volume> slopes{prism(-1,0,0,1,.1f),prism(0,1,0,1,.3f)};
            const auto shell=meshPlateauBody(slopes);const auto closed=auditStrictSurface(shell);
            check(closed.exact.boundaryEdges==0 && closed.exact.nonmanifoldEdges==0 && closed.exact.components==1 && closed.selfIntersections==0,
                  "Direct plateau shell left an internal prism wall or open edge");
            check(std::abs((10-traceMesh(shell,{-.5f,10,.5f},{0,-1,0}))-1.95f)<.0001f &&
                  std::abs((10-traceMesh(shell,{.5f,10,.5f},{0,-1,0}))-2.15f)<.0001f,
                  "Direct plateau shell changed the graded roof heights");
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
            const auto checkedUnion=solidBooleanUnion(slopes,.000008,0,{}, {shell},0,slopes.size());
            const auto checkedAudit=auditStrictSurface(checkedUnion);
            const auto sourceAudit=auditBoundaryCoverage(checkedUnion,slopes);
            check(checkedAudit.exact.boundaryEdges==0 && checkedAudit.exact.nonmanifoldEdges==0 && checkedAudit.nonmanifoldVertices==0 &&
                  checkedAudit.selfIntersections==0 && checkedAudit.coplanarOverlaps==0 && checkedAudit.exact.degenerateFaces==0 &&
                  sourceAudit.buriedFragments==0 && sourceAudit.detachedFragments==0,
                  "Solid union changes the already-checked body or loses its source coverage");
#endif
            auto higher=prism(0,1,0,1);higher.planes[0].distance=3;
            for(auto &p:higher.faces[0])p.y=3;
            const auto stepped=meshPlateauBody({prism(-1,0,0,1),higher});
            check(std::abs(traceMesh(stepped,{-.5f,2.5f,.5f},{1,0,0})-.5f)<.0001f,
                  "Direct plateau shell bridged a retained roof step instead of closing its riser");
            check(std::abs((10-traceMesh(stepped,{-.5f,10,.5f},{0,-1,0}))-2)<.0001f &&
                  std::abs((10-traceMesh(stepped,{.5f,10,.5f},{0,-1,0}))-3)<.0001f,
                  "Roof-step extraction changed either source height");
            const auto hole=meshPlateauBody({prism(0,1,0,3),prism(2,3,0,3),prism(1,2,0,1),prism(1,2,2,3)});
            check(traceMesh(hole,{1.5f,10,1.5f},{0,-1,0})==1000,"Direct plateau shell filled a protected hole");
            check(auditStrictSurface(hole).exact.boundaryEdges==0,"Protected hole walls do not close the plateau shell");
            auto crossingPrism=[&](float x0,float x1,float slope) {
                auto v=prism(x0,x1,-1,1);
                const auto n=Vector3Normalize(Vector3{0,1,-slope});
                v.planes[0]={n,3*double(n.y)};
                for(auto &p:v.faces[0])p.y=3+slope*p.z;
                return v;
            };
            const auto crossing=meshPlateauBody({crossingPrism(-1,0,.5f),crossingPrism(0,1,-.5f)},-.12f,.00002f,true);
            const auto crossingAudit=auditStrictSurface(crossing);
            check(crossingAudit.exact.boundaryEdges==0 && crossingAudit.exact.nonmanifoldEdges==0 &&
                  crossingAudit.exact.windingErrors==0 && crossingAudit.selfIntersections==0,
                  "Crossing roof tiers do not form a closed shell");
            check(std::abs((10-traceMesh(crossing,{-.5f,10,.5f},{0,-1,0}))-3.25f)<.0001f &&
                  std::abs((10-traceMesh(crossing,{.5f,10,.5f},{0,-1,0}))-2.75f)<.0001f,
                  "Crossing roof tiers changed source heights");
        }
        {
            const std::vector<Polygon> partition{
                {{0,0,0},{0,0,2},{2,0,0}},
                {{0,0,0},{-1,0,1},{0,0,1}},
                {{0,0,1},{-1,0,1},{0,0,2}}};
            const auto optimized=weldSurface(partition,.00008f,true);
            for(const auto &edge:surfaceBoundary(optimized))check(edge[0].x!=0 || edge[1].x!=0,
                  "Triangle preservation discarded a required T-junction split");
            const auto retained=triangulatePlateauBoundary({{0,1,0},{0,1,1},{0,1,2},{2,1,2},{2,1,0}},true);
            bool midpoint=false;for(const auto &f:retained)for(auto p:f)midpoint |= p.x==0 && p.z==1;
            check(midpoint,"Planar simplification dropped an externally shared collinear vertex");
        }
        {
            const Vector3 origin{56.5714f,0,-33.0683f};const Vector3 input{1.234567f,3.5f,.9876543f};
            const Vector3 expected=add(input,origin);
            {WorldGridScope grid(origin,true);const auto canonical=canonicalRenderPoint(input),again=canonicalRenderPoint(canonical);
             const auto actual=add(canonical,origin);
             check(actual.x==expected.x && actual.z==expected.z && canonical.x==again.x && canonical.z==again.z,
                   "Construction coordinates do not round-trip on the final render grid");}
            check(!worldGridActive,"World-grid precision leaked into another construction");
        }
        const auto validBoundary=auditBoundaryCoverage(welded,{cubeSolid});
        check(validBoundary.buriedFragments==0 && validBoundary.detachedFragments==0,"Boundary verifier rejected a valid solid");
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        if(std::getenv("DW_CLIFF_BOOLEAN_SOURCE_CHECKED")) {
            const auto preserved=solidBooleanUnion({cubeSolid},.000001f,0,{}, {welded},0,1);
            check(auditStrictSurface(preserved).exact.components==1 && auditBoundaryCoverageQuiet(preserved,{cubeSolid}).buriedFragments==0,
                  "Source-checked processing rejects a valid checked-body boundary");
            bool rejected=false;
            try{(void)solidBooleanUnion({box(-1,2,-1,2)},.000001f,0,{}, {welded},0,1);}
            catch(const std::runtime_error &e){rejected=std::string(e.what()).find("cannot preserve")!=std::string::npos;}
            check(rejected,"Source-checked processing returns a body buried inside its nominal source after retries");
        }
        {
            cliffOptions::Mesh interior;interior.faces={{{{.2f,.5f,.2f},{.8f,.5f,.2f},{.2f,.5f,.8f}}}};
            check(booleanSourceRestore::buriedVolumes(interior,{cubeSolid,box(10,11,10,11)})==std::vector<size_t>{0},"Source restoration misses a buried original prism or selects a remote one");
            for(auto &p:interior.faces[0])p.y=.99995f;
            check(booleanSourceRestore::buriedVolumes(interior,{cubeSolid}).empty(),"Source restoration changes the existing source margin");
            interior.faces={{{{.2f,.5f,.2f},{.2000001f,.5f,.2f},{.2f,.5f,.2000001f}}}};
            check(booleanSourceRestore::buriedVolumes(interior,{cubeSolid}).empty(),"Source restoration changes the existing area policy");
            struct RestoreFlags {
                std::map<std::string,std::optional<std::string>> old;
                RestoreFlags(){for(const char *key:{"DW_CLIFF_BOOLEAN_SOURCE_CHECKED","DW_CLIFF_EXACT_CONTACTS","DW_CLIFF_BOOLEAN_SOURCE_RESTORE"}){if(const char *p=std::getenv(key))old[key]=p;else old[key]=std::nullopt;setenv(key,"1",1);}}
                ~RestoreFlags(){for(const auto &[key,value]:old){if(value)setenv(key.c_str(),value->c_str(),1);else unsetenv(key.c_str());}}
            } flags;
            auto raised=cubeSolid;raised.planes[3].distance=2;
            const auto restored=solidBooleanUnion({raised},.000016,0,{}, {welded},0,1);
            const auto coverage=auditBoundaryCoverageQuiet(restored,{raised});const auto strict=auditStrictSurface(restored);
            check(!coverage.buriedFragments && !coverage.detachedFragments && strict.exact.components==1 && !strict.selfIntersections && !strict.exact.boundaryEdges,
                  "Local source restoration fails complete strict/source checks");
            check(std::abs(traceMesh(restored,{.5f,10,.5f},{0,-1,0})-8)<.00001f,"Source restoration fails to restore the original nominal roof");
        }
#endif
        cliffOptions::Mesh hidden;hidden.faces={{{{.2f,.5f,.2f},{.8f,.5f,.2f},{.2f,.5f,.8f}}}};
        check(auditBoundaryCoverage(hidden,{cubeSolid}).buriedFragments>0,"Boundary verifier missed an internal face");
        for(auto &p:hidden.faces[0])p.y=2;
        check(auditBoundaryCoverage(hidden,{cubeSolid}).detachedFragments>0,"Boundary verifier missed a detached face");
        {
            cliffOptions::Mesh sliver;sliver.faces={{{{0,1,0},{10,1,0},{5,1,3e-13f}}}};
            check(auditBoundaryCoverage(sliver,{box(0,10,-1,1)}).detachedFragments==0 &&
                  auditBoundaryCoverage(sliver,{box(0,5,-1,1),box(5,10,-1,1)}).detachedFragments==0,
                  "Source partitioning changes coverage of a completely covered thin face");
            sliver.faces[0][2].z=6e-13f;
            check(auditBoundaryCoverage(sliver,{box(3,7,-1,1)}).detachedFragments>0,
                  "Small outside pieces hide a total uncovered area above the source threshold");
            // Whole-face proofs must detect a thin uncovered strip even when
            // every vertex and the centroid lie in the source union.
            cliffOptions::Mesh top;top.faces={{{{0,1,0},{2,1,0},{0,1,2}}}};
            check(auditBoundaryCoverage(top,{box(-1,.99988f,-1,3),box(1.00012f,3,-1,3)}).detachedFragments>0,
                  "Boundary verifier missed a strip beyond the 0.1 mm source margin");
            check(auditBoundaryCoverage(top,{box(-1,.99991f,-1,3),box(1.00009f,3,-1,3)}).detachedFragments==0,
                  "Boundary verifier rejected a gap covered by the explicit source margin");
            for(auto &p:top.faces[0])p.y=1.00011f;
            check(auditBoundaryCoverage(top,{box(-1,3,-1,3)}).detachedFragments>0,
                  "Construction epsilon leaked into the independent 0.1 mm boundary check");
            cliffOptions::Mesh partial;partial.faces={{{{-2,.5f,-2},{3,.5f,-2},{-2,.5f,3}}}};
            check(auditBoundaryCoverage(partial,{cubeSolid}).buriedFragments>0,
                  "Boundary verifier tested only a face centre instead of its complete area");
        }
        auto cracked=welded;cracked.faces[0][0].x+=.00001f;
        check(auditStrictSurface(cracked).exact.boundaryEdges>0,"Exact verifier hid a sub-weld gap");
        check(surfaceBoundary(cracked).size()==auditStrictSurface(cracked).exact.boundaryEdges,
              "Boundary classification merged an emitted sub-weld crack");
        cliffOptions::Mesh crossing;
        crossing.faces={{{{0,0,0},{2,0,0},{0,0,2}}},{{{.5f,-1,.5f},{.5f,1,.5f},{1.5f,0,.5f}}}};
        check(auditStrictSurface(crossing).selfIntersections>0,"Strict verifier missed crossing triangles");
        check(auditSurfaceReplacement(crossing,1).selfIntersections>0,"Replacement verifier skipped a new crossing");
        check(replacementIntersects(crossing,1),"Fast replacement verifier skipped a new crossing");
        cliffOptions::Mesh overlap;
        overlap.faces={{{{0,0,0},{2,0,0},{0,0,2}}},{{{.2f,0,.2f},{1.2f,0,.2f},{.2f,0,1.2f}}}};
        check(auditStrictSurface(overlap).coplanarOverlaps==1,"Strict verifier missed coplanar overlap");
        check(auditSurfaceReplacement(overlap,1).coplanarOverlaps==1,"Replacement verifier skipped a new overlap");
        check(replacementIntersects(overlap,1),"Fast replacement verifier skipped a new coplanar overlap");
        check(!replacementIntersects(welded,welded.faces.size()-1),"Fast replacement verifier rejected a legal shared edge");
        for(auto &p:overlap.faces[1])p.y=.00001f;
        check(auditStrictSurface(overlap).coplanarOverlaps==0 && auditStrictSurface(overlap).selfIntersections==0,
              "Strict verifier merged separated planes");
        auto pinched=cube;for(auto p:cube){for(auto &v:p)v=add(v,{1,1,1});pinched.push_back(std::move(p));}
        check(auditStrictSurface(weldSurface(pinched)).nonmanifoldVertices>0,"Strict verifier missed a pinched vertex");
        auto audit=auditSurface(welded);
        check(audit.boundaryEdges==0 && audit.nonmanifoldEdges==0 && audit.windingErrors==0 &&
              audit.duplicateFaces==0 && audit.degenerateFaces==0 && audit.components==1,
              "Welding left a T-junction in a closed cube");
        auto openCube=cube; openCube.erase(openCube.begin()+1);
        check(auditSurface(weldSurface(openCube)).boundaryEdges>0,"Surface audit failed to detect a real hole");
        auto copies=cube;copies.push_back(cube[1]);
        check(auditSurface(weldSurface(copies)).duplicateFaces==0 && auditSurface(weldSurface(copies)).boundaryEdges==0,
              "Welded duplicate exterior faces were not consolidated");
        auto adjacent=cube;
        for(auto p:cube) {for(auto &v:p) v.x+=1;adjacent.push_back(std::move(p));}
        const auto adjacentAudit=auditSurface(weldSurface(adjacent));
        check(adjacentAudit.boundaryEdges==0 && adjacentAudit.nonmanifoldEdges==0 && adjacentAudit.components==1,
              "Opposite shared internal faces did not cancel");
        for(float ground:{.5f,1.f}) {
            Experiment body;
            body.mesh=welded;
            auto solid=box(0,1,0,1); solid.planes[2].distance=0;
            body.volumes={solid};
            std::vector<Polygon> retained{{{-1,ground,-1},{-1,ground,2},{2,ground,2},{2,ground,-1}}};
            auto surface=assembleSurface(retained,body);
            check(body.unexpectedBoundaryEdges==0 && body.assembledAudit.nonmanifoldEdges==0 &&
                  body.assembledAudit.duplicateFaces==0 && body.assembledAudit.windingErrors==0,
                  "Terrain/body join has unexpected boundaries or duplicate surfaces");
            check(std::abs(traceMesh(surface,{.5f,-1,.5f},{0,1,0})-2.f)<.0001f,
                  "Buried body base or internal terrain cap survived union");
            check(std::abs(traceMesh(surface,{1.5f,2,.5f},{0,-1,0})-(2-ground))<.0001f,
                  "Terrain union lost the surrounding top surface");
        }
        {
            Experiment body;
            auto raised=cube;for(auto &p:raised) for(auto &v:p) v.y*=2;
            body.mesh=weldSurface(raised);
            auto solid=box(0,1,0,1);solid.planes[2].distance=0;solid.planes[3].distance=2;
            body.volumes={solid};body.editBounds={{0,-.12f,-1},{2,3,2}};
            // Actual old terrain has rock below .3 and from .7 to 1.2, with
            // an air gap under an overhang. Positive caps alone erase this gap.
            std::vector<Polygon> outside{
                {{-1,.3f,-1},{-1,.3f,2},{0,.3f,2},{0,.3f,-1}},
                {{-1,.7f,-1},{0,.7f,-1},{0,.7f,2},{-1,.7f,2}},
                {{-1,1.2f,-1},{-1,1.2f,2},{0,1.2f,2},{0,1.2f,-1}},
                {{0,-.12f,-1},{0,.3f,-1},{0,.3f,2},{0,-.12f,2}},
                {{0,.7f,-1},{0,1.2f,-1},{0,1.2f,2},{0,.7f,2}}};
            auto joined=assembleSurface({},body,outside);
            check(body.unexpectedBoundaryEdges==0 && body.assembledAudit.nonmanifoldEdges==0 && body.assembledAudit.windingErrors==0,
                  "Overhang-aware work boundary failed its surface audit");
            check(std::abs(traceMesh(joined,{-.5f,.5f,.5f},{1,0,0})-.5f)<.0001f,
                  "New wall vanished inside the old overhang's air gap");
            for(float y:{.1f,.9f})
                check(std::abs(traceMesh(joined,{-.5f,y,.5f},{1,0,0})-1.5f)<.0001f,
                      "Buried wall survived inside old terrain");
        }
        // A ray aimed at the common edge of a side and bevel must not fall
        // through both triangles because of float barycentric roundoff.
        const Vector3 edgeA{4.3212f,3.54195f,-4.93456f}, edgeB{4.29311f,3.68454f,-4.79162f};
        cliffOptions::Mesh seam;
        seam.faces = {{edgeA,edgeB,{3.93868f,3.38843f,-3.23075f}},
                      {edgeB,edgeA,{7.68473f,4.23109f,-5.8234f}}};
        const auto target=mul(add(edgeA,edgeB),.5f), origin=add(target,{0,2,2});
        check(std::abs(traceMesh(seam,origin,Vector3Normalize(sub(target,origin)))-std::sqrt(8.f))<.00001f,
              "Ray fell through a shared bevel edge");
        check(traceMesh(seam,origin,{0,1,0})==1000, "Mesh oracle reported a hit behind the ray");
        const Polygon face{{-2,0,-2},{-2,0,2},{2,0,2},{2,0,-2}};
        // Preserve a real interior hole and a concave edge recess. A convex-hull
        // cleanup would incorrectly fill both, despite reducing triangle counts.
        for (bool notch : {false, true}) {
            auto parts = exposed(face, {box(notch ? 0.f : -1.f, notch ? 3.f : 1.f, -1, 1)});
            check(std::abs(surfaceArea(parts) - 12.f) < .0001f, "Cutout area changed");
            check(!covers(parts,{.5f,0,0}) && covers(parts,{-1.5f,0,0}), "Filled hole or lost visible face");
            auto repeated = exposed(face, {box(notch ? 0.f : -1.f, notch ? 3.f : 1.f,-1,1)});
            check(parts.size() == repeated.size(), "Clipping changed on replay");
            for (size_t i = 0; i < parts.size(); ++i) {
                check(parts[i].size() == repeated[i].size(), "Replay polygon changed");
                for (size_t j = 0; j < parts[i].size(); ++j)
                    check(distance(parts[i][j],repeated[i][j]) < 1e-7f, "Replay vertex changed");
            }
        }
        auto strip = exposed(face, {box(-1,1,-3,3)});
        check(strip.size() == 2 && std::abs(surfaceArea(strip)-8.f)<.0001f,
              "Merged separated regions across a buried strip");
        auto untouched = exposed(face, {box(3,4,-1,1)});
        check(untouched.size()==1 && std::abs(surfaceArea(untouched)-16.f)<.0001f,
              "Nonintersecting volume fragmented a face");
        // Coincident outward surfaces belong to exactly one input volume.
        auto coplanar = box(-2,2,-2,2);
        coplanar.planes[3].distance=0;
        check(exposed(face,{coplanar,coplanar},0).size()==1, "First coplanar owner disappeared");
        check(exposed(face,{coplanar,coplanar},1).empty(), "Duplicate coplanar face survived");
        // Exercise the complete solid generator and ray oracle on three seeds.
        CanyonAppearance base;
        {
            const Box room{{-2,-1,-2},{10,4,10}};
            check(!selectSection(base,room).fallback.empty(),"Missing contour did not request fallback");
            CanyonAppearance shortSection;
            shortSection.triangles={{{{{0,.12f,0},{0,3,0},{8,3,0}}},true},
                                    {{{{0,.12f,0},{8,.12f,0},{0,3,0}}},true}};
            const auto selected=selectSection(shortSection,room);
            check(selected.length==8 && !selected.fallback.empty(),"Short contour did not retain an explicit A fallback");
            for(float bend:{0.f,.025f,-.025f}) {
                CanyonAppearance contour;
                for(int i=0;i<12;++i) {
                    const float x0=i*2.f,x1=(i+1)*2.f;
                    const Vector3 a{x0,.12f,bend*x0*x0},b{x1,.12f,bend*x1*x1};
                    const auto at=add(a,{0,3,0}),bt=add(b,{0,3,0});
                    contour.triangles.push_back({{a,at,bt},true});
                    contour.triangles.push_back({{a,b,at},true});
                }
                const auto sections=selectSections(contour,{{0,-1,-10},{24,4,20}});
                const auto expected=bend==0?"straight":bend>0?"concave":"convex";
                check(std::any_of(sections.begin(),sections.end(),[&](const auto &section){return section.curvature==expected && section.fallback.empty();}),
                      "Boundary inventory lost straight/concave/convex classification");
            }
            auto original=shortSection;
            const std::vector<cliffDetail::Quad> tiny{{{0,.12f,0},{4,.12f,0},{4,3,0},{0,3,0}}};
            bool rejected=false;
            try{(void)buildAndApply(shortSection,original,tiny,42,false);}catch(const std::runtime_error&){rejected=true;}
            check(rejected && shortSection.triangles.size()==original.triangles.size(),"Rejected local-frame build changed input count");
            for(size_t i=0;i<original.triangles.size();++i)for(int k=0;k<3;++k)
                check(distance(shortSection.triangles[i].vertices[k],original.triangles[i].vertices[k])==0,
                      "Rejected local-frame build mutated original terrain");
        }
        std::vector<cliffDetail::Quad> wall{{{0,.12f,0},{16,.12f,0},{16,3,0},{0,3,0}}};
        {
            float previousWidth=-1;
            for(auto seed:{0ULL,42ULL,404ULL,1866ULL}) {
                auto composition=compose(24.f,seed,false),replay=compose(24.f,seed,false);
                check(composition.size()==12,"Incomplete seeded formation roles");
                for(size_t i=0;i<composition.size();++i) {
                    const auto &a=composition[i],&b=replay[i];
                    check(a.at==b.at && a.width==b.width && a.height==b.height && a.profile.roof.x==b.profile.roof.x && a.enabled==b.enabled,
                          "Seeded composition is not deterministic");
                    check(a.width>0 && a.depth>0 && a.height>0 && a.at>0 && a.at<1,"Seeded dimensions escaped bounds");
                    if(i<5 && i!=2)check(a.height<composition[2].height,"Seeded composition lost its dominant mass");
                }
                check(composition[2].width!=previousWidth,"Distinct composition seeds repeated the dominant width");
                previousWidth=composition[2].width;
                const auto shoulders=std::count_if(composition.begin(),composition.end(),[](const auto &f){return f.enabled && f.role==FormationRole::Shoulder;});
                const auto bases=std::count_if(composition.begin(),composition.end(),[](const auto &f){return f.enabled && f.role==FormationRole::Base;});
                check(shoulders>=1 && shoulders<=3 && bases>=1 && bases<=4,"Optional formation counts escaped their role bounds");
            }
            bool rejected=false;
            try{(void)compose(4.f,42,false);}catch(const std::runtime_error&){rejected=true;}
            check(rejected,"Short seeded section did not request an explicit fallback");
        }
        for (auto seed : {0ULL,42ULL,1866ULL}) {
            auto geometry = build(wall,base,seed);
            const auto strict=auditStrictSurface(geometry.mesh);
            std::cout<<"STRICT_SYNTHETIC seed="<<seed<<" exact_open="<<strict.exact.boundaryEdges
                     <<" vertex_links="<<strict.nonmanifoldVertices<<" crossings="<<strict.selfIntersections
                     <<" coplanar_overlap="<<strict.coplanarOverlaps<<" degenerate="<<strict.exact.degenerateFaces<<'\n';
            check(strict.exact.boundaryEdges==0 && strict.nonmanifoldVertices==0 && strict.selfIntersections==0 &&
                  strict.coplanarOverlaps==0 && strict.exact.degenerateFaces==0,"Synthetic connection failed exact geometry audit");
            check(geometry.primaryVolumes==12 && geometry.plateauVolumes>=3 && geometry.rayChecks==640, "Incomplete solid/ray validation");
            check(geometry.topChecks==28*geometry.plateauVolumes && geometry.audit.boundaryEdges==0 && geometry.audit.components==1,
                  "Plateau top coverage or surface closure failed");
            check(geometry.joinConnectors==4 && geometry.joinCoverageChecks==612,
                  "Missing explicit dominant/shoulder footprint coverage checks");
            check(geometry.plateauRouteChecks==1935,"Some primary roofs lack elevated plateau route checks");
            auto detailed=build(wall,base,seed,true);
            check(detailed.rimCuts==2 && detailed.baseDetails<=2 && detailed.audit.components==1 &&
                  detailed.strictAudit.exact.boundaryEdges==0 && detailed.strictAudit.selfIntersections==0,
                  "Detail broke the connected plateau");
            std::cout<<"DETAIL_SYNTHETIC seed="<<seed<<" triangles="<<detailed.mesh.faces.size()<<" PASS\n";
        }
        {
            CanyonAppearance support;
            support.surface.width=support.surface.depth=2;
            support.surface.x=support.surface.z=-5;support.surface.step=10;
            support.surface.heights.assign(4,9.f); // deliberately stale physical field
            support.triangles={{{{{-4,2,-4},{-4,2,4},{4,2,4}}},true},
                               {{{{-4,2,-4},{4,2,4},{4,2,-4}}},true}};
            support.cellOffsets={0,2};
            cliffOptions::Mesh visible;
            for(auto t:support.triangles)visible.faces.push_back(t.vertices);
            Vector3 plant{0,9,0};size_t tests=0;
            check(placeOnSurface(support,visible,plant,.4f,tests) && std::abs(plant.y-1.975f)<1e-5f,
                  "Plant used stale physical heights instead of the final visible surface");
            auto absent=visible;absent.faces.clear();plant={0,9,0};
            check(!placeOnSurface(support,absent,plant,.4f,tests),"Missing visible mesh accepted plant support");
            auto stepped=visible;
            for(auto &v:stepped.faces[1])v.y+=.5f;
            plant={0,9,0};
            check(!placeOnSurface(support,stepped,plant,.4f,tests),"Plant straddles a visible height discontinuity");
            support.supportTriangles=support.triangles;
            for(auto &t:support.supportTriangles)for(auto &v:t.vertices)v.y=9;
            support.supportOffsets={0,2};support.supportIndices={0,1};
            support.parameters.maxDecorations=0; // isolate reanchoring from authored additions
            support.decorations={
                {CanyonDecorationKind::Grass,CanyonZone::Plateau,{0,9,-1},.4f,.5f,.2f,2,false},
                {CanyonDecorationKind::Grass,CanyonZone::Plateau,{4,9,-1},.4f,.5f,.3f,2,false},
                {CanyonDecorationKind::Grass,CanyonZone::Plateau,{2.9f,9,0},.4f,.5f,.4f,2,false}};
            const auto outside=support.decorations[1];
            Experiment scenery;scenery.editBounds={{-3,-.12f,-3},{3,3,3}};scenery.assembledMesh=visible;
            addScenery(support,wall,scenery,42);
            check(scenery.sceneryReanchored==1 && scenery.sceneryRemoved==1 && support.decorations.size()==2,
                  "Local scenery reanchoring or unsupported-edge suppression failed");
            check(std::abs(support.decorations[0].position.y-1.975f)<1e-5f &&
                  distance(support.decorations[1].position,outside.position)==0 && support.decorations[1].yaw==outside.yaw,
                  "Scenery support remained stale or moved an outside placement");
        }
        // Lower exposed old terraces continuously into the sand. Keep the
        // canonical contact height and immutable gameplay field/floor intact.
        base.surface.width = base.surface.depth = 3;
        base.surface.x = base.surface.z = -20;
        base.surface.step = 20;
        base.surface.heights.assign(9, 3.f);
        const auto physical = base.surface.heights;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        for(int joinMode:{0,1,2}) {
            // Exercise both adapters against identical original roof/floor data.
            // Exercise the new mode through the real adapter: a source roof
            // beside the selected column must keep its original elevation.
            CanyonAppearance retained;retained.surface=base.surface;
            const std::array<Vector3,3> protectedPatch{{{8,0,0},{8,0,1},{9,0,0}}};
            retained.triangles={
                {{{{0,3,0},{0,3,3},{6,3,3}}},true},
                {{{{0,3,0},{6,3,3},{6,3,0}}},true},
                {{{{6,3,0},{6,3,3},{8,3,3}}},true},
                {{{{6,3,0},{8,3,3},{8,3,0}}},true},
                {protectedPatch,false}};
            retained.cellOffsets={0,retained.triangles.size()};
            auto column=box(1,2,1,2);column.planes[2].distance=.12f;column.planes[3].distance=4;
            column.bounds={{1,-.12f,1},{2,4,2}};
            column.faces={{{1,4,1},{1,4,2},{2,4,2},{2,4,1}},
                          {{2,-.12f,1},{2,-.12f,2},{1,-.12f,2},{1,-.12f,1}},
                          {{1,-.12f,1},{1,4,1},{2,4,1},{2,-.12f,1}},
                          {{2,-.12f,2},{2,4,2},{1,4,2},{1,-.12f,2}},
                          {{1,-.12f,2},{1,4,2},{1,4,1},{1,-.12f,1}},
                          {{2,-.12f,1},{2,4,1},{2,4,2},{2,-.12f,2}}};
            Experiment selected;selected.seededComposition=true;selected.blendedBacking=true;
            selected.volumes={column};selected.mesh=weldSurface(column.faces);
            struct RestoreFlag {
                std::optional<std::string> old,oldJoint,oldWhole;
                RestoreFlag(int mode){if(const char *p=std::getenv("DW_CLIFF_CAP_CONNECTED_DOMAIN"))old=p;if(const char *p=std::getenv("DW_CLIFF_JOINT_TERRAIN_JOIN"))oldJoint=p;if(const char *p=std::getenv("DW_CLIFF_JOINT_WHOLE_SOURCE"))oldWhole=p;setenv("DW_CLIFF_CAP_CONNECTED_DOMAIN","1",1);if(mode)setenv("DW_CLIFF_JOINT_TERRAIN_JOIN","1",1);else unsetenv("DW_CLIFF_JOINT_TERRAIN_JOIN");if(mode==2)setenv("DW_CLIFF_JOINT_WHOLE_SOURCE","1",1);else unsetenv("DW_CLIFF_JOINT_WHOLE_SOURCE");}
                ~RestoreFlag(){if(old)setenv("DW_CLIFF_CAP_CONNECTED_DOMAIN",old->c_str(),1);else unsetenv("DW_CLIFF_CAP_CONNECTED_DOMAIN");if(oldJoint)setenv("DW_CLIFF_JOINT_TERRAIN_JOIN",oldJoint->c_str(),1);else unsetenv("DW_CLIFF_JOINT_TERRAIN_JOIN");if(oldWhole)setenv("DW_CLIFF_JOINT_WHOLE_SOURCE",oldWhole->c_str(),1);else unsetenv("DW_CLIFF_JOINT_WHOLE_SOURCE");}
            } flag(joinMode);
            apply(retained,wall,selected);
            cliffOptions::Mesh visible;for(const auto &t:retained.triangles)visible.faces.push_back(t.vertices);
            check(std::abs(traceMesh(visible,{.5f,10,1.5f},{0,-1,0})-7)<.00001f,
                  "Cap domain adapter lowers unselected original terrain beside a selected column");
            check(std::abs(traceMesh(visible,{1.5f,10,1.5f},{0,-1,0})-6)<.00001f,
                  "Cap domain adapter loses the selected replacement roof");
            for(float x:{5.f,7.f})check(std::abs(traceMesh(visible,{x,10,1.5f},{0,-1,0})-7)<.00001f,
                  "Whole-face ownership changes a cold roof or loses its neighbouring source");
            check(retained.surface.heights==physical,"Cap domain adapter changes physical heights");
            size_t floors=0;for(const auto &t:retained.triangles)if(!t.rock){++floors;for(int k=0;k<3;++k)check(distance(t.vertices[k],protectedPatch[k])==0,"Cap domain adapter changes protected floor");}
            check(floors==1,"Cap domain adapter loses protected floor");
            check(!selected.unexpectedBoundaryEdges && !selected.strictAssembledAudit.selfIntersections && !selected.strictAssembledAudit.coplanarOverlaps,
                  "Cap domain synthetic retained-source assembly is invalid");
        }
#endif
        const std::array<Vector3,3> floor{{{0,0,0},{0,0,4},{16,0,4}}};
        const std::array<Vector3,3> floor2{{{0,0,0},{16,0,4},{16,0,0}}};
        base.triangles = {
            {floor,false},
            {floor2,false},
            {{{{6,2,-2},{8,2,-1},{8,2,-2}}},true},
            {{{{6,2,0},{8,2,0},{8,2,-.4f}}},true},
            {{{{6,2,.2f},{8,2,.4f},{8,2,.2f}}},true}
        };
        base.cellOffsets = {0,base.triangles.size()};
        Experiment emptyBody;
        apply(base,wall,emptyBody);
        check(base.surface.heights == physical, "Backing cleanup changed physical heights");
        for (int i=0; i<3; ++i)
            check(distance(base.triangles[0].vertices[i],floor[i])<1e-7f, "Backing cleanup moved floor");
        for (int i=0; i<3; ++i)
            check(distance(base.triangles[1].vertices[i],floor2[i])<1e-7f, "Backing cleanup moved floor");
        cliffOptions::Mesh adapted;
        for(const auto &t:base.triangles) adapted.faces.push_back(t.vertices);
        check(std::abs(traceMesh(adapted,{7.5f,10,-1.8f},{0,-1,0})-10)<.0001f,
              "Exposed backing retained a raised plate");
        check(std::abs(traceMesh(adapted,{7.5f,10,-.2f},{0,-1,0})-9.91f)<.0001f,
              "Ground taper broke the canonical contour");
        check(std::abs(traceMesh(adapted,{7.5f,10,.3f},{0,-1,0})-10)<.0001f,
              "Old protruding facet overlaps the protected floor");
        {
            CanyonAppearance corner;
            corner.surface=base.surface;
            corner.triangles={
                {{{{1,2,-2},{3,2,-1},{3,2,-2}}},true},
                {{{{20,2,-2},{22,2,-1},{22,2,-2}}},true}};
            corner.cellOffsets={0,2};
            const std::vector<cliffDetail::Quad> turn{
                {{0,.12f,0},{4,.12f,0},{4,3,0},{0,3,0}},
                {{4,.12f,0},{4,.12f,4},{4,3,4},{4,3,0}}};
            Experiment noRocks;
            apply(corner,turn,noRocks);
            cliffOptions::Mesh surface;for(const auto &t:corner.triangles) surface.faces.push_back(t.vertices);
            check(std::abs(traceMesh(surface,{21.5f,10,-1.8f},{0,-1,0})-8.f)<.0001f,
                  "Corner projection incorrectly lowered distant terrain");
        }
        std::cout << "PASS rock formations: closed plateau, top coverage, T-junction welding, buried/coplanar terrain joins, shared bevel-edge rays, holes, recesses, replay, three synthetic-wall seeds, preserved floor/collision\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
