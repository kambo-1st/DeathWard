#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "PlateauRegion.hpp"
#include "PlateauHeightProjection.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>

namespace dw::rockFormations {
struct PlateauVertexField {Plane weight,target,lower;};
// Source/grid boundaries must already conform. Sample on actual shared
// vertices, rather than interpolating independently blended source-node data.
inline std::vector<GradedRoofCell> blendPlateauSourceVertices(const std::vector<GradedRoofCell> &cells,
    const std::function<PlateauVertexField(Vector3)> &sample) {
    using Coefficients=std::array<double,3>;
    auto coefficients=[](const Plane &p)->Coefficients {
        const auto n=planeNormal(p);if(n[1]<=0)throw std::runtime_error("Vertex field has no upper affine plane");
        return {-n[0]/n[1],-n[2]/n[1],p.distance/n[1]};
    };
    auto at=[](const Coefficients &h,Vector3 p){return h[0]*p.x+h[1]*p.z+h[2];};
    auto plane=[](const Coefficients &h) {
        const double length=std::sqrt(h[0]*h[0]+1+h[1]*h[1]);Plane p;p.hasPreciseNormal=true;
        p.preciseNormal={-h[0]/length,1/length,-h[1]/length};p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};p.distance=h[2]/length;return p;
    };
    std::map<std::pair<float,float>,PlateauVertexField> cache;
    auto field=[&](Vector3 p)->const PlateauVertexField & {
        const auto key=std::pair{p.x,p.z};auto found=cache.find(key);
        if(found==cache.end())found=cache.emplace(key,sample(p)).first;return found->second;
    };
    using Key=std::array<double,4>;
    struct Group {Plane roof;std::vector<Polygon> outlines;};std::map<Key,Group> groups;
    size_t cold=0,triangles=0;bool savedSteep=false;double maximumSlope=0;
    auto append=[&](Polygon outline,const Plane &roof) {
        const auto n=planeNormal(roof);auto [group,added]=groups.try_emplace({n[0],n[1],n[2],roof.distance},Group{roof,{}});
        for(auto &p:outline)p.y=0;group->second.outlines.push_back(std::move(outline));
    };
    struct Prepared {
        Coefficients source;cliffOptions::Triangle face;
        std::array<double,3> heights,weights,floors,targets;
        std::array<size_t,3> ids;
    };
    std::vector<Prepared> prepared;
    std::map<std::pair<float,float>,size_t> ids;
    std::vector<PlateauHeightOffset> offsets;
    std::vector<PlateauHeightConstraint> constraints;
    auto vertex=[&](Vector3 p,double original,double w,double target,double floor,double h) {
        double lo=std::max(floor,std::min(original,target))-h,hi=std::max(floor,std::max(original,target))-h;
        if(w==0 || w==1)lo=hi=0;
        // Zero is feasible for the sampled field by construction.
        lo=std::min(lo,0.);hi=std::max(hi,0.);
        auto [at,added]=ids.emplace(std::pair{p.x,p.z},offsets.size());
        if(added)offsets.push_back({lo,hi,0});
        else {auto &v=offsets[at->second];v.lower=std::max(v.lower,lo);v.upper=std::min(v.upper,hi);}
        return at->second;
    };
    for(const auto &cell:cells) {
        const auto source=coefficients(cell.roof);bool unchanged=true;
        for(auto p:cell.outline){const auto &f=field(p);unchanged &= at(coefficients(f.weight),p)<=0 && at(source,p)>=at(coefficients(f.lower),p);}
        if(unchanged){for(auto p:cell.outline)vertex(p,at(source,p),0,at(source,p),at(source,p),at(source,p));append(cell.outline,cell.roof);++cold;continue;}
        auto outline=cell.outline;for(auto &p:outline)p.y=0;
        // The regional mesher retains all split boundary vertices, including
        // collinear ones, and does not impose the legacy ear area heuristic.
        for(const auto &face:meshPlateauFootprint({outline},true).faces) {
            ++triangles;std::array<double,3> heights{},weights{},floors{},targets{};
            std::array<size_t,3> vertices{};
            for(int k=0;k<3;++k) {
                const auto p=face[k];const auto &f=field(p);
                weights[k]=std::clamp(at(coefficients(f.weight),p),0.,1.);
                targets[k]=at(coefficients(f.target),p);floors[k]=at(coefficients(f.lower),p);
                heights[k]=std::max(floors[k],std::lerp(at(source,p),targets[k],weights[k]));
                if(!std::isfinite(heights[k]))throw std::runtime_error("Nonfinite shared-vertex blend");
                vertices[k]=vertex(p,at(source,p),weights[k],targets[k],floors[k],heights[k]);
            }
            prepared.push_back({source,face,heights,weights,floors,targets,vertices});
            constraints.push_back({vertices,heights,face});
        }
    }
    projectPlateauVertexSlopes(offsets,constraints);
    for(const auto &preparedFace:prepared) {
            const auto &source=preparedFace.source;const auto &face=preparedFace.face;
            const auto &weights=preparedFace.weights,&floors=preparedFace.floors,&targets=preparedFace.targets;
            auto heights=preparedFace.heights;
            for(int k=0;k<3;++k)heights[k]+=offsets[preparedFace.ids[k]].value;
            Vector3 centre{float((double(face[0].x)+face[1].x+face[2].x)/3),0,float((double(face[0].z)+face[1].z+face[2].z)/3)};
            const auto &f=field(centre);const auto w=coefficients(f.weight),target=coefficients(f.target);
            Coefficients candidate{};bool analytic=false;
            if(std::all_of(weights.begin(),weights.end(),[](double x){return x==1;})){candidate=target;analytic=true;}
            else if(heights==floors){candidate=coefficients(f.lower);analytic=true;}
            else {
                const Coefficients delta{target[0]-source[0],target[1]-source[1],target[2]-source[2]};
                if(w[0]*delta[0]==0 && w[1]*delta[1]==0 && w[0]*delta[1]+w[1]*delta[0]==0) {
                    candidate={source[0]+w[0]*delta[2]+w[2]*delta[0],source[1]+w[1]*delta[2]+w[2]*delta[1],source[2]+w[2]*delta[2]};analytic=true;
                }
            }
            if(analytic)for(int k=0;k<3;++k)analytic &= float(at(candidate,face[k]))==float(heights[k]);
            if(!analytic) {
                const auto a=face[0],b=face[1],c=face[2];
                const double ux=double(b.x)-a.x,uz=double(b.z)-a.z,vx=double(c.x)-a.x,vz=double(c.z)-a.z;
                const double uy=heights[1]-heights[0],vy=heights[2]-heights[0],det=ux*vz-uz*vx;
                if(det==0)throw std::runtime_error("Shared-vertex blend has a zero-area source triangle");
                candidate={(uy*vz-uz*vy)/det,(ux*vy-uy*vx)/det,0};candidate[2]=heights[0]-candidate[0]*a.x-candidate[1]*a.z;
            }
            maximumSlope=std::max(maximumSlope,std::hypot(candidate[0],candidate[1]));
            if(!savedSteep && std::hypot(candidate[0],candidate[1])>std::sqrt(99.))if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
                std::ofstream out(std::string(path)+".vertex.json");out.precision(17);
                auto array=[&](const auto &values){out<<'[';for(size_t k=0;k<values.size();++k){if(k)out<<',';out<<values[k];}out<<']';};
                out<<"{\"source\":";array(source);out<<",\"roof\":";array(candidate);out<<",\"points\":[";
                for(int k=0;k<3;++k){if(k)out<<',';out<<'['<<face[k].x<<','<<heights[k]<<','<<face[k].z<<']';}
                out<<"],\"weight\":";array(w);out<<",\"target\":";array(target);out<<",\"floors\":";array(floors);out<<",\"weights\":";array(weights);out<<",\"targets\":";array(targets);out<<"}\n";
                if(!out)throw std::runtime_error("Cannot save shared-vertex slope witness");savedSteep=true;
            }
            append({face[0],face[1],face[2]},plane(candidate));
    }
    std::vector<GradedRoofCell> result;
    for(auto &[key,group]:groups) {
        const auto roof=coefficients(group.roof);
        for(auto outline:consolidateExactPlanar(std::move(group.outlines),{0,1,0})) {
            for(auto &p:outline)p.y=float(at(roof,p));result.push_back({std::move(outline),group.roof});
        }
    }
    std::cout<<"PLATEAU_VERTEX_BLEND input_cells="<<cells.size()<<" cold_cells="<<cold<<" triangles="<<triangles<<" plane_groups="<<groups.size()<<" output_cells="<<result.size()<<" maximum_slope="<<maximumSlope<<'\n';
    return result;
}
}
#endif
