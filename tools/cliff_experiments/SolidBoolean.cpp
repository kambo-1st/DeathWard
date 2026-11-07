#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "PlateauFloatVertexRepair.hpp"
#include "BooleanSourceRestore.hpp"
#include <manifold/manifold.h>
#include <clipper2/clipper.h>
#include <algorithm>
#include <map>
#include <set>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdexcept>

namespace dw::rockFormations {
static cliffOptions::Mesh buildBooleanUnion(const std::vector<Volume> &volumes,double tolerance,float padding,const std::vector<Polygon> &floors,const std::vector<cliffOptions::Mesh> &checkedBodies,size_t bodyBegin,size_t bodyCount,const char *probeOverride=nullptr) {
    ConstructionTiming timed("solid_boolean");
    ConstructionChecks requiredInputChecks;
    std::vector<manifold::Manifold> inputs;
    if(bodyBegin>volumes.size() || bodyCount>volumes.size()-bodyBegin)throw std::runtime_error("Invalid checked-body source range");
    if(!checkedBodies.empty() && bodyCount==0)throw std::runtime_error("Checked bodies require their original source range");
    if(!checkedBodies.empty())if(const auto path=probeOverride?probeOverride:std::getenv("DW_CLIFF_INVALID_PROBE")) {
        cliffOptions::Mesh combined;for(const auto &body:checkedBodies)combined.faces.insert(combined.faces.end(),body.faces.begin(),body.faces.end());
        const auto output=std::string(path)+".boolean.json";writeSurfaceProbe(output.c_str(),combined,volumes,{});
        std::ofstream out(std::string(path)+".boolean-map.json");
        out<<"{\"body_begin\":"<<bodyBegin<<",\"body_count\":"<<bodyCount<<",\"body_faces\":[";
        for(size_t k=0;k<checkedBodies.size();++k){if(k)out<<',';out<<checkedBodies[k].faces.size();}out<<"]}\n";
        if(!out)throw std::runtime_error("Cannot save Boolean input map");
    }
    for(size_t source=0;source<volumes.size();++source) {
        if(!checkedBodies.empty() && source>=bodyBegin && source<bodyBegin+bodyCount)continue;
        // Use the nominal source half-spaces. Rounded face corners can
        // describe a different hull at nearly parallel prism sides.
        using L=std::array<long double,3>;
        auto normal=[](const Plane &p){const auto n=planeNormal(p);return L{n[0],n[1],n[2]};};
        auto cross=[](L a,L b){return L{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};};
        auto dot=[](L a,L b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];};
        const auto &planes=volumes[source].planes;
        std::vector<manifold::vec3> points;
        for(size_t i=0;i<planes.size();++i)for(size_t j=i+1;j<planes.size();++j)for(size_t k=j+1;k<planes.size();++k) {
            const auto a=normal(planes[i]),b=normal(planes[j]),c=normal(planes[k]);
            const auto bc=cross(b,c),ca=cross(c,a),ab=cross(a,b);const auto det=dot(a,bc);
            if(std::abs(det)<1e-14L)continue;
            L p{};for(size_t axis=0;axis<3;++axis)p[axis]=(planes[i].distance*bc[axis]+planes[j].distance*ca[axis]+planes[k].distance*ab[axis])/det;
            if(std::any_of(planes.begin(),planes.end(),[&](const auto &plane){return dot(normal(plane),p)>plane.distance+1e-12L;}))continue;
            if(padding==0)points.push_back({double(p[0]),double(p[1]),double(p[2])});
            else for(int x:{-1,1})for(int y:{-1,1})for(int z:{-1,1})points.push_back({double(p[0])+x*padding,double(p[1])+y*padding,double(p[2])+z*padding});
        }
        auto solid=manifold::Manifold::Hull(points);
        if(solid.Status()!=manifold::Manifold::Error::NoError)
            throw std::runtime_error("Boolean input "+std::to_string(source)+": "+std::to_string(int(solid.Status())));
        inputs.push_back(std::move(solid));
    }
    for(const auto &body:checkedBodies) {
        const auto audit=auditStrictSurface(body);
        if(audit.exact.boundaryEdges || audit.exact.nonmanifoldEdges || audit.nonmanifoldVertices || audit.selfIntersections ||
           audit.coplanarOverlaps || audit.exact.degenerateFaces || audit.exact.duplicateFaces || audit.exact.windingErrors)
            throw std::runtime_error("Boolean checked body fails its emitted-mesh audit: open="+std::to_string(audit.exact.boundaryEdges)+
                " nonmanifold="+std::to_string(audit.exact.nonmanifoldEdges)+" links="+std::to_string(audit.nonmanifoldVertices)+
                " crossings="+std::to_string(audit.selfIntersections)+" overlaps="+std::to_string(audit.coplanarOverlaps)+
                " degenerate="+std::to_string(audit.exact.degenerateFaces)+" duplicates="+std::to_string(audit.exact.duplicateFaces)+
                " winding="+std::to_string(audit.exact.windingErrors));
        manifold::MeshGL64 mesh;mesh.numProp=3;
        std::map<std::array<float,3>,uint64_t> ids;
        for(const auto &face:body.faces)for(auto p:face) {
            auto [at,added]=ids.emplace(std::array<float,3>{p.x,p.y,p.z},ids.size());
            if(added){mesh.vertProperties.push_back(p.x);mesh.vertProperties.push_back(p.y);mesh.vertProperties.push_back(p.z);}
            mesh.triVerts.push_back(at->second);
        }
        auto solid=manifold::Manifold(mesh);
        if(solid.Status()!=manifold::Manifold::Error::NoError)
            throw std::runtime_error("Boolean checked-body input: "+std::to_string(int(solid.Status())));
        inputs.push_back(std::move(solid));
    }
    auto result=manifold::Manifold::BatchBoolean(inputs,manifold::OpType::Add);
    if(padding>0 && !floors.empty()) {
        std::vector<manifold::Manifold> cutters;
        for(const auto &face:floors) {
            std::vector<manifold::vec3> points;
            const double clearance=std::min(.00004,double(padding)+tolerance);
            for(auto p:face)for(int x:{-1,1})for(int z:{-1,1}) {
                points.push_back({double(p.x)+x*clearance,-1,double(p.z)+z*clearance});
                points.push_back({double(p.x)+x*clearance,30,double(p.z)+z*clearance});
            }
            cutters.push_back(manifold::Manifold::Hull(points));
        }
        result=result-manifold::Manifold::BatchBoolean(cutters,manifold::OpType::Add);
    }
    double foundation=0;
    if(padding>0) {
        double lowest=1e9;
        for(const auto &v:volumes)for(const auto &f:v.faces)for(auto p:f)lowest=std::min(lowest,double(p.y));
        if(std::abs(lowest+.12)<.0001) {
            // Remove the regularization bevel below the buried common base.
            // This moves only the foundation, by 60 micrometres, within the
            // independent 0.1 mm source-boundary contract.
            foundation=lowest+.00006;
            result=result.TrimByPlane({0,1,0},foundation);
        }
    }
    const bool raw=std::getenv("DW_CLIFF_BOOLEAN_RAW");
    if(!raw) {
    result=result.AsOriginal().SetTolerance(tolerance).Simplify(tolerance);
    // The renderer stores float positions. Simplify that actual representation,
    // rather than validating a double mesh and rounding it only afterwards.
    auto quantized=result.GetMeshGL64();
    for(size_t i=0;i<quantized.NumVert();++i)for(size_t k=0;k<3;++k)
        quantized.vertProperties[i*quantized.numProp+k]=float(quantized.vertProperties[i*quantized.numProp+k]);
    quantized.faceID.clear();quantized.runIndex.clear();quantized.runOriginalID.clear();quantized.runTransform.clear();
    quantized.tolerance=tolerance;
    result=manifold::Manifold(quantized).AsOriginal().Simplify(tolerance);
    }
    if(result.Status()!=manifold::Manifold::Error::NoError)throw std::runtime_error("Solid boolean failed: "+std::to_string(int(result.Status())));
    const auto mesh=result.GetMeshGL64();
    cliffOptions::Mesh output;output.masses=volumes.size();
    auto point=[&](uint64_t i){return Vector3{float(mesh.vertProperties[i*mesh.numProp]),float(mesh.vertProperties[i*mesh.numProp+1]),float(mesh.vertProperties[i*mesh.numProp+2])};};
    std::map<std::pair<uint64_t,uint64_t>,std::pair<size_t,uint64_t>> edges;
    for(size_t i=0;i<mesh.NumTri();++i) {
        const auto a=mesh.triVerts[3*i],b=mesh.triVerts[3*i+1],c=mesh.triVerts[3*i+2];
        output.faces.push_back({point(a),point(b),point(c)});
        for(int k=0;k<3;++k) {
            auto u=mesh.triVerts[3*i+k],v=mesh.triVerts[3*i+(k+1)%3];if(v<u)std::swap(u,v);
            const auto face=mesh.faceID.empty()?uint64_t(i):mesh.faceID[i];
            auto [it,added]=edges.emplace(std::pair{u,v},std::pair{size_t(1),face});
            if(!added){++it->second.first;if(it->second.second!=face)it->second.second=uint64_t(-1);}
        }
    }
    for(const auto &[edge,info]:edges)if(info.first==1 || info.second==uint64_t(-1))output.polygonEdges.push_back({point(edge.first),point(edge.second)});
    if(std::getenv("DW_CLIFF_BOOLEAN_FLOAT_REPAIR")) {
        // Quantization can put a boundary vertex one float step through a
        // neighbouring roof. Change actual geometry, never the audit tolerance.
        // Restrict this diagnostic to otherwise closed, consistently oriented
        // surfaces with a small number of crossing pairs. Each vertex can move
        // once, vertically by one float step, and at most one micrometre.
        auto faceNormal=[](const cliffOptions::Triangle &face){
            const double x=double(face[1].x)-face[0].x,y=double(face[1].y)-face[0].y,z=double(face[1].z)-face[0].z,
                         u=double(face[2].x)-face[0].x,v=double(face[2].y)-face[0].y,w=double(face[2].z)-face[0].z;
            return std::array<double,3>{y*w-z*v,z*u-x*w,x*v-y*u};
        };
        auto audit=auditStrictSurface(output);
        auto topology=[](const StrictSurfaceAudit &a){return a.exact.boundaryEdges+a.exact.nonmanifoldEdges+a.nonmanifoldVertices+
            a.exact.duplicateFaces+a.exact.degenerateFaces+a.exact.windingErrors;};
        std::set<std::array<float,3>> moved;
        size_t accepted=0,trials=0;double maximumDisplacement=0;
        const auto initial=audit.selfIntersections;
        for(size_t pass=0;pass<8 && !topology(audit) && !audit.coplanarOverlaps && audit.selfIntersections>0 && audit.selfIntersections<=16;++pass) {
            std::set<std::array<float,3>> candidates;
            for(const auto &pair:audit.problemPairs)for(auto face:pair)for(auto p:output.faces[face])candidates.insert({p.x,p.y,p.z});
            bool improved=false;
            for(const auto &key:candidates) {
                if(moved.contains(key))continue;
                for(float direction:{std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity()}) {
                    const float height=std::nextafter(key[1],direction);
                    if(!std::isfinite(height) || std::abs(double(height)-key[1])>1e-6)continue;
                    auto trial=output;
                    auto move=[&](Vector3 &p){if(std::array<float,3>{p.x,p.y,p.z}==key)p.y=height;};
                    bool flipped=false;
                    for(size_t f=0;f<trial.faces.size();++f) {
                        auto &face=trial.faces[f];const auto before=faceNormal(face);
                        for(auto &p:face)move(p);
                        const auto after=faceNormal(face);
                        if(before[0]*after[0]+before[1]*after[1]+before[2]*after[2]<=0){flipped=true;break;}
                    }
                    if(flipped)continue;
                    for(auto &edge:trial.polygonEdges){move(edge[0]);move(edge[1]);}
                    ++trials;const auto checked=auditStrictSurface(trial);
                    if(topology(checked) || checked.coplanarOverlaps || checked.exact.components!=audit.exact.components || checked.selfIntersections>=audit.selfIntersections)continue;
                    output=std::move(trial);audit=checked;moved.insert(key);moved.insert({key[0],height,key[2]});++accepted;maximumDisplacement=std::max(maximumDisplacement,std::abs(double(height)-key[1]));improved=true;break;
                }
                if(improved)break;
            }
            if(!improved)break;
        }
        std::cout<<"FORMATION_FLOAT_REPAIR initial_crossings="<<initial<<" final_crossings="<<audit.selfIntersections
                 <<" moves="<<accepted<<" trials="<<trials<<" maximum_displacement_m="<<maximumDisplacement<<" displacement_limit_m=.000001 single_vertical_float_step=1\n";
    }
    if(std::getenv("DW_CLIFF_BOOLEAN_VERTEX_REPAIR"))output=repairBooleanFloatVertices(std::move(output),volumes);
    std::cout<<"FORMATION_BOOLEAN inputs="<<inputs.size()<<" triangles="<<output.faces.size()<<" source_volumes="<<volumes.size()<<" checked_bodies="<<checkedBodies.size()<<" tolerance_m="<<tolerance<<" raw="<<raw<<" padding_m="<<padding<<" protected_floor_cuts="<<floors.size()<<" foundation_y="<<foundation<<'\n';
    return output;
}
// Retry output processing only when the actual emitted float surface fails.
// Every attempt uses the same original solids, with a smaller simplification
// tolerance. No position/source/topology acceptance threshold is relaxed.
cliffOptions::Mesh solidBooleanUnion(const std::vector<Volume> &volumes,double tolerance,float padding,const std::vector<Polygon> &floors,const std::vector<cliffOptions::Mesh> &checkedBodies,size_t bodyBegin,size_t bodyCount) {
    const bool restoreSources=std::getenv("DW_CLIFF_BOOLEAN_SOURCE_RESTORE")!=nullptr;
    if(restoreSources && (!std::getenv("DW_CLIFF_BOOLEAN_SOURCE_CHECKED") || padding!=0 || !floors.empty()))throw std::runtime_error("Source restoration requires source-checked unpadded Boolean construction without explicit floor cutters");
    if(!std::getenv("DW_CLIFF_BOOLEAN_SOURCE_CHECKED"))return buildBooleanUnion(volumes,tolerance,padding,floors,checkedBodies,bodyBegin,bodyCount);
    if(!std::getenv("DW_CLIFF_EXACT_CONTACTS"))throw std::runtime_error("Source-checked Boolean processing requires exact contacts");
    if(std::getenv("DW_CLIFF_BOOLEAN_RAW"))throw std::runtime_error("Source-checked processing requires the processed Boolean path");
    ConstructionTiming timed("source_checked_boolean");
    ConstructionChecks requiredChecks;
    auto strictPass=[](const StrictSurfaceAudit &strict){return strict.exact.components>0 && !strict.exact.boundaryEdges && !strict.exact.nonmanifoldEdges &&
        !strict.nonmanifoldVertices && !strict.selfIntersections && !strict.coplanarOverlaps && !strict.exact.degenerateFaces &&
        !strict.exact.duplicateFaces && !strict.exact.windingErrors;};
    for(size_t attempt=0;attempt<4;++attempt) {
        auto mesh=buildBooleanUnion(volumes,tolerance,padding,floors,checkedBodies,bodyBegin,bodyCount);
        const auto strict=auditStrictSurface(mesh);
        const auto source=auditBoundaryCoverageQuiet(mesh,volumes);
        const bool valid=strict.exact.components>0 && !strict.exact.boundaryEdges && !strict.exact.nonmanifoldEdges &&
            !strict.nonmanifoldVertices && !strict.selfIntersections && !strict.coplanarOverlaps && !strict.exact.degenerateFaces &&
            !strict.exact.duplicateFaces && !strict.exact.windingErrors && !source.buriedFragments && !source.detachedFragments;
        std::cout<<"FORMATION_BOOLEAN_SOURCE attempt="<<attempt<<" tolerance_m="<<tolerance<<" triangles="<<mesh.faces.size()
                 <<" crossings="<<strict.selfIntersections<<" degenerate="<<strict.exact.degenerateFaces<<" components="<<strict.exact.components
                 <<" buried="<<source.buriedFragments<<" detached="<<source.detachedFragments<<" source_surface_pass="<<valid<<'\n';
        // Component count is preserved here; the caller still requires one
        // component and applies the unchanged budget and all world/floor gates.
        if(valid)return mesh;
        if(restoreSources && strictPass(strict) && source.buriedFragments && !source.detachedFragments) {
            const auto ids=booleanSourceRestore::buriedVolumes(mesh,volumes);
            if(!ids.empty() && ids.size()<=16) {
                // Re-add only unchanged original solids; duplicating their
                // nominal planes does not alter the source union. Validate the
                // complete result against the ORIGINAL union after rebuilding.
                auto sources=volumes;for(auto id:ids)sources.push_back(volumes[id]);
                std::string probe;
                if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
                    probe=std::string(path)+".source-restore"+std::to_string(attempt);
                    const auto coarse=probe+".coarse.json";writeSurfaceProbe(coarse.c_str(),mesh,volumes,strict);
                    std::ofstream out(probe+".map.json");out<<"{\"original_volumes\":"<<volumes.size()<<",\"restored_original_ids\":[";
                    for(size_t i=0;i<ids.size();++i){if(i)out<<',';out<<ids[i];}out<<"],\"original_nominal_union_unchanged\":true}\n";
                    if(!out)throw std::runtime_error("Cannot save source restoration provenance");
                }
                auto repaired=buildBooleanUnion(sources,std::min(tolerance,.000001),0,{},std::vector<cliffOptions::Mesh>{mesh},0,volumes.size(),probe.empty()?nullptr:probe.c_str());
                const auto repairedStrict=auditStrictSurface(repaired);
                const auto repairedSource=auditBoundaryCoverageQuiet(repaired,volumes);
                const bool accepted=strictPass(repairedStrict) && repairedStrict.exact.components==strict.exact.components && !repairedSource.buriedFragments && !repairedSource.detachedFragments;
                std::cout<<"FORMATION_BOOLEAN_RESTORE attempt="<<attempt<<" volumes="<<ids.size()<<" triangles="<<repaired.faces.size()
                         <<" components="<<repairedStrict.exact.components<<" buried="<<repairedSource.buriedFragments<<" detached="<<repairedSource.detachedFragments
                         <<" strict_and_original_source_pass="<<accepted<<'\n';
                if(accepted){repaired.masses=mesh.masses;return repaired;}
            } else std::cout<<"FORMATION_BOOLEAN_RESTORE_SKIPPED volumes="<<ids.size()<<" limit=16\n";
        }
        tolerance*=.25;
    }
    throw std::runtime_error("Boolean output cannot preserve its checked source boundary and strict surface");
}

// All operands stay double precision until BOTH the terrain subtraction and
// core union have completed. No retained cut fragment is rounded independently.
cliffOptions::Mesh solidBooleanTerrainJoin(const std::vector<Volume> &old,const cliffOptions::Mesh &core) {
    if(const auto path=std::getenv("DW_CLIFF_JOINT_FIXTURE")) {
        std::ofstream out(path);out.precision(17);
        out<<"DWJOIN1\n"<<old.size()<<'\n';
        for(const auto &v:old){out<<v.faces.size()<<'\n';for(const auto &f:v.faces){out<<f.size();for(auto p:f)out<<' '<<p.x<<' '<<p.y<<' '<<p.z;out<<'\n';}}
        out<<core.faces.size()<<'\n';for(const auto &f:core.faces){for(auto p:f)out<<p.x<<' '<<p.y<<' '<<p.z<<' ';out<<'\n';}
        if(!out)throw std::runtime_error("Cannot save joint terrain fixture");
    }
    auto check=[](const manifold::Manifold &m,const char *stage){if(m.Status()!=manifold::Manifold::Error::NoError)throw std::runtime_error(std::string("Joint terrain ")+stage+": "+std::to_string(int(m.Status())));};
    manifold::MeshGL64 input;input.numProp=3;
    std::map<std::array<float,3>,uint64_t> ids;
    double high=1;
    for(const auto &f:core.faces)for(auto p:f){auto [it,added]=ids.emplace(std::array<float,3>{p.x,p.y,p.z},ids.size());if(added){input.vertProperties.insert(input.vertProperties.end(),{p.x,p.y,p.z});high=std::max(high,double(p.y)+1);}input.triVerts.push_back(it->second);}
    auto stageProbe=[&](const char *name,const manifold::Manifold &body) {
        const auto prefix=std::getenv("DW_CLIFF_JOINT_STAGE_PROBE");if(!prefix)return;
        const auto data=body.GetMeshGL64();cliffOptions::Mesh rounded;
        auto point=[&](uint64_t i){return Vector3{float(data.vertProperties[i*data.numProp]),float(data.vertProperties[i*data.numProp+1]),float(data.vertProperties[i*data.numProp+2])};};
        for(size_t i=0;i<data.NumTri();++i)rounded.faces.push_back({point(data.triVerts[3*i]),point(data.triVerts[3*i+1]),point(data.triVerts[3*i+2])});
        const auto audit=auditStrictSurface(rounded);
        const auto path=std::string(prefix)+"."+name;
        writeSurfaceProbe((path+".json").c_str(),rounded,{},audit);
        std::ofstream out(path+".double.json");out.precision(17);
        out<<"{\"vertices\":[";for(size_t i=0;i<data.NumVert();++i){if(i)out<<',';out<<'[';for(size_t j=0;j<3;++j){if(j)out<<',';out<<data.vertProperties[i*data.numProp+j];}out<<']';}
        out<<"],\"triangles\":[";for(size_t i=0;i<data.NumTri();++i){if(i)out<<',';out<<'['<<data.triVerts[3*i]<<','<<data.triVerts[3*i+1]<<','<<data.triVerts[3*i+2]<<']';}out<<"]}\n";
        std::cout<<"PLATEAU_JOINT_OPERAND name="<<name<<" triangles="<<rounded.faces.size()<<" nonmanifold="<<audit.exact.nonmanifoldEdges<<" crossings="<<audit.selfIntersections<<" overlaps="<<audit.coplanarOverlaps<<" degenerate="<<audit.exact.degenerateFaces<<std::endl;
    };
    const manifold::Manifold replacement(input);check(replacement,"core input");
    stageProbe("core",replacement);
    std::vector<manifold::Manifold> terrain;
    for(const auto &v:old) {
        std::vector<manifold::vec3> points;
        for(const auto &f:v.faces)for(auto p:f){points.push_back({p.x,p.y,p.z});high=std::max(high,double(p.y)+1);}
        auto prism=manifold::Manifold::Hull(points);check(prism,"old cap");terrain.push_back(std::move(prism));
    }
    // Extrude the silhouette of the actual closed core. On this height-field
    // operand its projected boundary is a set of simple outer/hole rings.
    // Unioning thousands of touching triangle columns constructs the same
    // shadow but makes the Boolean graph prohibitively expensive.
    const auto projected=replacement.Rotate(-90,0,0).Project();
    // Decimal CrossSection scaling perturbs the binary-float core border.
    // Use a power-of-two scale that represents EVERY projected input exactly.
    int bits=40;
    for(;bits>=0;--bits){bool exact=true;for(const auto &p:projected)for(auto v:p)for(int k=0;k<2;++k){const double q=std::ldexp(v[k],bits);exact &= std::isfinite(q) && std::abs(q)<double(1ULL<<50) && q==std::trunc(q);}if(exact)break;}
    if(bits<0)throw std::runtime_error("Core projection exceeds exact binary clipping scope");
    Clipper2Lib::Paths64 paths;
    for(const auto &p:projected){Clipper2Lib::Path64 path;for(auto v:p)path.emplace_back(int64_t(std::ldexp(v.x,bits)),int64_t(std::ldexp(v.y,bits)));paths.push_back(std::move(path));}
    const auto normalized=Clipper2Lib::Union(paths,Clipper2Lib::FillRule::Positive);
    manifold::Polygons outline;
    for(const auto &p:normalized){manifold::SimplePolygon poly;for(auto v:p)poly.push_back({std::ldexp(double(v.x),-bits),std::ldexp(double(v.y),-bits)});outline.push_back(std::move(poly));}

    if(const auto prefix=std::getenv("DW_CLIFF_JOINT_STAGE_PROBE")) {
        std::ofstream out(std::string(prefix)+".projection.json");out<<"{\"binary_scale_bits\":"<<bits<<",\"input_exact\":true,\"raw\":[";
        auto save=[&](const Clipper2Lib::Paths64 &rings){for(size_t i=0;i<rings.size();++i){if(i)out<<',';out<<'[';for(size_t k=0;k<rings[i].size();++k){if(k)out<<',';out<<'['<<rings[i][k].x<<','<<rings[i][k].y<<']';}out<<']';}};
        save(paths);out<<"],\"normalized\":[";save(normalized);out<<"]}\n";if(!out)throw std::runtime_error("Cannot save exact binary projection certificate");
    }
    auto shadow=manifold::Manifold::Extrude(outline,high+1).Translate({0,0,-high}).Rotate(90,0,0);
    check(shadow,"projected shadow");
    std::cout<<"PLATEAU_JOINT_STAGE stage=inputs_ready caps="<<terrain.size()<<" shadow_rings="<<outline.size()<<" binary_scale_bits="<<bits<<std::endl;
    auto prior=manifold::Manifold::BatchBoolean(terrain,manifold::OpType::Add);check(prior,"old cap union");
    stageProbe("old",prior);
    stageProbe("shadow",shadow);
    std::cout<<"PLATEAU_JOINT_STAGE stage=old_union triangles="<<prior.NumTri()<<std::endl;
    std::cout<<"PLATEAU_JOINT_STAGE stage=shadow_union triangles="<<shadow.NumTri()<<std::endl;
    auto cut=prior-shadow;stageProbe("cut",cut);
    auto combined=cut+replacement;stageProbe("combined",combined);
    auto result=combined.AsOriginal().SetTolerance(.000008).Simplify(.000008);check(result,"shared cut union");
    std::cout<<"PLATEAU_JOINT_STAGE stage=shared_union triangles="<<result.NumTri()<<std::endl;
    auto rounded=result.GetMeshGL64();
    for(auto &value:rounded.vertProperties)value=float(value);
    rounded.faceID.clear();rounded.runIndex.clear();rounded.runOriginalID.clear();rounded.runTransform.clear();
    rounded.tolerance=.000008;
    result=manifold::Manifold(rounded).AsOriginal().Simplify(.000008);
    check(result,"joint float conversion");
    const auto mesh=result.GetMeshGL64();cliffOptions::Mesh output;
    auto point=[&](uint64_t i){return Vector3{float(mesh.vertProperties[i*mesh.numProp]),float(mesh.vertProperties[i*mesh.numProp+1]),float(mesh.vertProperties[i*mesh.numProp+2])};};
    for(size_t i=0;i<mesh.NumTri();++i)output.faces.push_back({point(mesh.triVerts[3*i]),point(mesh.triVerts[3*i+1]),point(mesh.triVerts[3*i+2])});
    const auto strict=auditStrictSurface(output);
    if(const auto path=std::getenv("DW_CLIFF_JOINT_PROBE"))writeSurfaceProbe(path,output,{},strict);
    std::cout<<"PLATEAU_JOINT_BOOLEAN old_caps="<<old.size()<<" shadow_rings="<<outline.size()<<" triangles="<<output.faces.size()<<" open="<<strict.exact.boundaryEdges<<" nonmanifold="<<strict.exact.nonmanifoldEdges<<" degenerate="<<strict.exact.degenerateFaces<<" crossings="<<strict.selfIntersections<<" overlaps="<<strict.coplanarOverlaps<<'\n';
    // This closed operand includes buried foundations and finite edit curtains.
    // Its diagnostics do not replace the unchanged final visible-assembly audit.
    // TerrainJoinReplay independently rejects defects when auditing this operand.

    return output;
}

}
