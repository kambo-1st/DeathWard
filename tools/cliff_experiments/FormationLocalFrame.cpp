#include "RockFormations.hpp"
#include "FormationPrecision.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <iomanip>

namespace dw::rockFormations {
namespace {
using FaceKey=std::array<float,10>;
FaceKey key(const CanyonSurfaceTriangle &face) {
    FaceKey result{};result[9]=face.rock;
    for(int i=0;i<3;++i){result[i*3]=face.vertices[i].x;result[i*3+1]=face.vertices[i].y;result[i*3+2]=face.vertices[i].z;}
    return result;
}
void move(CanyonAppearance &surface,Vector3 offset) {
    surface.surface.x+=offset.x;surface.surface.z+=offset.z;
    for(auto &t:surface.triangles)for(auto &p:t.vertices)p=add(p,offset);
    for(auto &t:surface.supportTriangles)for(auto &p:t.vertices)p=add(p,offset);
    for(auto &d:surface.decorations)d.position=add(d.position,offset);
}
void index(CanyonAppearance &out,bool support) {
    const auto &field=out.surface;
    const int columns=field.width-1,rows=field.depth-1;
    std::vector<std::vector<size_t>> bins(size_t(columns*rows));
    const auto &faces=support?out.supportTriangles:out.triangles;
    for(size_t i=0;i<faces.size();++i) {
        int lx=columns-1,hx=0,lz=rows-1,hz=0;
        for(auto p:faces[i].vertices) {
            const int x=std::clamp(int(std::floor((p.x-field.x)/field.step)),0,columns-1);
            const int z=std::clamp(int(std::floor((p.z-field.z)/field.step)),0,rows-1);
            lx=std::min(lx,x);hx=std::max(hx,x);lz=std::min(lz,z);hz=std::max(hz,z);
        }
        for(int z=lz;z<=hz;++z)for(int x=lx;x<=hx;++x)bins[size_t(z*columns+x)].push_back(i);
    }
    auto &offsets=support?out.supportOffsets:out.spatialOffsets;
    auto &indices=support?out.supportIndices:out.spatialTriangles;
    offsets.clear();indices.clear();
    for(const auto &bin:bins){offsets.push_back(indices.size());indices.insert(indices.end(),bin.begin(),bin.end());}
    offsets.push_back(indices.size());
}
}

static Experiment buildAndApplyRecipe(CanyonAppearance &out,const CanyonAppearance &base,
                         const std::vector<cliffDetail::Quad> &wall,uint64_t seed,bool detail,bool finishRoof) {
    // CSG clipping operates near the origin. Far-away rooms otherwise amplify
    // float clipping differences into unverified cracks. Preserve exact original
    // faces so moving back to world space cannot perturb floors or scenery.
    auto origin=mul(add(wall.front().ab,wall.back().bb),.5f);
    if(std::getenv("DW_CLIFF_ROOF_WORLD") && std::getenv("DW_CLIFF_ROOF_SHELL"))origin={};
    if(std::getenv("DW_CLIFF_ROOF_REGION"))origin={}; // Regional fixed-grid domains use world coordinates directly.
    const bool worldGrid=std::getenv("DW_CLIFF_WORLD_GRID") && std::getenv("DW_CLIFF_ROOF_SHELL");
    if(worldGrid) {
        float lx=1e9f,hx=-1e9f,lz=1e9f,hz=-1e9f;
        for(auto q:wall)for(auto p:{q.ab,q.bb,q.at,q.bt}){lx=std::min(lx,p.x);hx=std::max(hx,p.x);lz=std::min(lz,p.z);hz=std::max(hz,p.z);}
        // Keep subtraction exact for the complete work region. Axes near zero
        // stay in world coordinates; distant axes retain the local frame.
        auto safe=[](float center,float lo,float hi){lo-=12;hi+=12;return center>0 && lo>=center*.5f && hi<=center*2 ? center : center<0 && lo>=center*2 && hi<=center*.5f ? center : 0.f;};
        origin.x=safe(origin.x,lx,hx);origin.z=safe(origin.z,lz,hz);
    }
    WorldGridScope precision(origin,worldGrid);
    std::cout<<"FORMATION_FRAME origin="<<origin.x<<','<<origin.y<<','<<origin.z<<" world_grid="<<worldGrid<<'\n';
    const Vector3 offset{-origin.x,0,-origin.z},restore{origin.x,0,origin.z};
    const auto original=out;
    auto local=out,localBase=base;
    move(local,offset);move(localBase,offset);
    std::map<FaceKey,CanyonSurfaceTriangle> originals,supportOriginals;
    for(size_t i=0;i<local.triangles.size();++i)originals.emplace(key(local.triangles[i]),original.triangles[i]);
    for(size_t i=0;i<local.supportTriangles.size();++i)supportOriginals.emplace(key(local.supportTriangles[i]),original.supportTriangles[i]);
    std::vector<cliffDetail::Quad> localWall=wall;
    for(auto &q:localWall){q.ab=add(q.ab,offset);q.bb=add(q.bb,offset);q.at=add(q.at,offset);q.bt=add(q.bt,offset);}
    const auto backing=std::getenv("DW_CLIFF_BACKING");
    const bool blended=!backing || std::string_view(backing)!="legacy";
    auto experiment=build(localWall,blended?local:localBase,seed,detail,true,finishRoof,std::getenv("DW_CLIFF_ROOF_REGION")?&localBase:nullptr);
    const auto core=experiment;
    std::string failure;
    bool applied=false;
    for(float margin:{1.f,1.5f,2.f}) {
        experiment=core;experiment.editMargin=margin;
        local=original;move(local,offset);
        try {
            apply(local,localWall,experiment);
            std::cout<<"FORMATION_EDIT_FIT margin="<<margin<<" exact_checks=PASS\n";
            applied=true;break;
        }catch(const std::exception &e){failure=e.what();std::cout<<"FORMATION_EDIT_REJECT margin="<<margin<<" reason="<<failure<<'\n';}
    }
    if(!applied)throw std::runtime_error(failure);
    for(auto &t:local.triangles) {
        const auto found=originals.find(key(t));
        if(found!=originals.end())t=found->second;
        else for(auto &p:t.vertices)p=add(p,restore);
    }
    for(auto &t:local.supportTriangles) {
        const auto found=supportOriginals.find(key(t));
        if(found!=supportOriginals.end())t=found->second;
        else for(auto &p:t.vertices)p=add(p,restore);
    }
    for(auto &d:local.decorations) {
        // Exact restoration for unchanged source placement records.
        auto found=std::find_if(original.decorations.begin(),original.decorations.end(),[&](const auto &old) {
            const auto p=add(old.position,offset);
            return p.x==d.position.x && p.y==d.position.y && p.z==d.position.z && old.kind==d.kind && old.yaw==d.yaw;
        });
        if(found!=original.decorations.end())d=*found;else d.position=add(d.position,restore);
    }
    local.surface=original.surface;
    auto mesh=[&](cliffOptions::Mesh &m) {
        for(auto &f:m.faces)for(auto &p:f)p=add(p,restore);
        for(auto &edge:m.polygonEdges)for(auto &p:edge)p=add(p,restore);
    };
    mesh(experiment.mesh);mesh(experiment.assembledMesh);
    for(auto &v:experiment.volumes) {
        for(auto &f:v.faces)for(auto &p:f)p=add(p,restore);
        for(auto &p:v.planes)p.distance+=planeProjection(p,restore);
        v.bounds.min=add(v.bounds.min,restore);v.bounds.max=add(v.bounds.max,restore);
    }
    for(auto &f:experiment.plateauTops)for(auto &p:f)p=add(p,restore);
    for(auto &f:experiment.protectedFloor)for(auto &p:f)p=add(p,restore);
    experiment.plateauCenter=add(experiment.plateauCenter,restore);
    experiment.editBounds.min=add(experiment.editBounds.min,restore);
    experiment.editBounds.max=add(experiment.editBounds.max,restore);
    experiment.strictAudit=auditStrictSurface(experiment.mesh);
    experiment.strictAssembledAudit=auditStrictSurface(experiment.assembledMesh);
    experiment.boundaryCoverage=auditBoundaryCoverage(experiment.mesh,experiment.volumes);
    if(experiment.boundaryCoverage.buriedFragments || experiment.boundaryCoverage.detachedFragments)
        throw std::runtime_error("World-space translation failed source-solid boundary coverage");
    const auto &a=experiment.strictAudit,&b=experiment.strictAssembledAudit;
    std::cout<<"FORMATION_WORLD_EXACT core_open="<<a.exact.boundaryEdges<<" core_nonmanifold="<<a.exact.nonmanifoldEdges<<" core_crossings="<<a.selfIntersections<<" core_degenerate="<<a.exact.degenerateFaces
             <<" assembled_open="<<b.exact.boundaryEdges<<" expected_open="<<experiment.intentionalBoundaryEdges<<" assembled_nonmanifold="<<b.exact.nonmanifoldEdges<<" assembled_crossings="<<b.selfIntersections<<" assembled_degenerate="<<b.exact.degenerateFaces<<'\n';
    if(a.exact.boundaryEdges || a.exact.nonmanifoldEdges || a.nonmanifoldVertices || a.selfIntersections ||
       a.coplanarOverlaps || a.exact.degenerateFaces || b.exact.nonmanifoldEdges || b.nonmanifoldVertices ||
       b.selfIntersections || b.coplanarOverlaps || b.exact.degenerateFaces || b.exact.boundaryEdges!=experiment.intentionalBoundaryEdges)
        throw std::runtime_error("World-space translation failed exact emitted-mesh checks");
    std::vector<std::array<Vector3,3>> beforeFloor,afterFloor;
    for(const auto &t:original.triangles)if(!t.rock)beforeFloor.push_back(t.vertices);
    for(const auto &t:local.triangles)if(!t.rock)afterFloor.push_back(t.vertices);
    if(beforeFloor.size()!=afterFloor.size())throw std::runtime_error("World-space floor count changed");
    for(size_t i=0;i<beforeFloor.size();++i)for(int j=0;j<3;++j)
        if(beforeFloor[i][j].x!=afterFloor[i][j].x || beforeFloor[i][j].y!=afterFloor[i][j].y || beforeFloor[i][j].z!=afterFloor[i][j].z)
            throw std::runtime_error("World-space floor vertex changed");
    index(local,false);if(!local.supportTriangles.empty())index(local,true);
    out=std::move(local);
    return experiment;
}
Experiment buildAndApply(CanyonAppearance &out,const CanyonAppearance &base,
                         const std::vector<cliffDetail::Quad> &wall,uint64_t seed,bool detail) {
    try {
        auto result=buildAndApplyRecipe(out,base,wall,seed,detail,true);
        std::cout<<"FORMATION_ROOF_RECIPE finished="<<result.finishedRoof<<" previous_retry=0\n";
        return result;
    } catch(const std::exception &error) {
        if(std::getenv("DW_CLIFF_REQUIRE_NEW_ROOF"))throw;
        // Both paths work on copies and pass the same emitted-mesh checks.
        // Retain the previously verified roof when a collar cannot fit safely.
        std::cout<<"FORMATION_ROOF_REJECT reason="<<std::quoted(error.what())<<'\n';
        auto result=buildAndApplyRecipe(out,base,wall,seed,detail,false);
        std::cout<<"FORMATION_ROOF_RECIPE finished=0 previous_retry=1\n";
        return result;
    }
}
} // namespace dw::rockFormations
