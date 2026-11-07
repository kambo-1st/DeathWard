#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <limits>

namespace dw::rockFormations::booleanSourceRestore {
// Uncertain face/solid pairs use rational clipping of actual emitted floats.
// The preliminary error bound rejects only proved outside pairs.
inline std::vector<size_t> buriedVolumes(const cliffOptions::Mesh &mesh,
                                       const std::vector<Volume> &volumes,
                                       double margin=.0001) {
    ConstructionTiming timing("boolean_source_restore_witnesses");ConstructionChecks checks;
    using R=boost::multiprecision::cpp_rational;using P=std::array<R,3>;
    struct Halfspace {std::array<double,3> normal;double distance;std::array<R,4> exact;};
    std::vector<std::vector<Halfspace>> solids;
    for(const auto &volume:volumes) {
        std::vector<Halfspace> planes;
        for(const auto &plane:volume.planes) {
            const auto n=planeNormal(plane);const double d=plane.distance-margin;
            planes.push_back({n,d,{R(n[0]),R(n[1]),R(n[2]),R(d)}});
        }
        solids.push_back(std::move(planes));
    }
    auto clip=[](const std::vector<P> &poly,const std::array<R,4> &plane) {
        std::vector<P> out;
        auto value=[&](const P &p)->R{return plane[0]*p[0]+plane[1]*p[1]+plane[2]*p[2]-plane[3];};
        for(size_t i=0;i<poly.size();++i) {
            const auto &a=poly[i],&b=poly[(i+1)%poly.size()];const R u=value(a),v=value(b);
            if(u<=0)out.push_back(a);
            if(u*v<0){const R t=u/(u-v);out.push_back({a[0]+t*(b[0]-a[0]),a[1]+t*(b[1]-a[1]),a[2]+t*(b[2]-a[2])});}
        }
        return out;
    };
    auto substantial=[](const std::vector<P> &poly) {
        if(poly.size()<3)return false;
        P area{0,0,0};
        for(size_t i=1;i+1<poly.size();++i) {
            P a,b;for(int k=0;k<3;++k){a[k]=poly[i][k]-poly[0][k];b[k]=poly[i+1][k]-poly[0][k];}
            area[0]+=a[1]*b[2]-a[2]*b[1];area[1]+=a[2]*b[0]-a[0]*b[2];area[2]+=a[0]*b[1]-a[1]*b[0];
        }
        const R limit=R(1e-12);
        return area[0]*area[0]+area[1]*area[1]+area[2]*area[2]>4*limit*limit;
    };
    std::vector<size_t> ids;
    for(size_t i=0;i<solids.size();++i)for(const auto &face:mesh.faces) {
        bool outside=false;
        for(const auto &plane:solids[i]) {
            bool allOutside=true;
            for(auto p:face) {
                const long double x=static_cast<long double>(plane.normal[0])*p.x,
                                  y=static_cast<long double>(plane.normal[1])*p.y,
                                  z=static_cast<long double>(plane.normal[2])*p.z;
                const long double sum=x+y+z-plane.distance;
                const long double error=16*std::numeric_limits<long double>::epsilon()*(std::abs(x)+std::abs(y)+std::abs(z)+std::abs(static_cast<long double>(plane.distance)));
                allOutside &= sum>error;
            }
            if(allOutside){outside=true;break;}
        }
        if(outside)continue;
        std::vector<P> poly;for(auto p:face)poly.push_back({R(p.x),R(p.y),R(p.z)});
        for(const auto &plane:solids[i]){poly=clip(poly,plane.exact);if(poly.size()<3)break;}
        if(substantial(poly)){ids.push_back(i);break;}
    }
    return ids;
}
}
#endif
