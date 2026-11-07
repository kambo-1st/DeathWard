#include "RockFormations.hpp"
#include <algorithm>
#include <cmath>

namespace dw::rockFormations {
namespace {
using Point=std::array<long double,3>;
using Face=std::vector<Point>;
constexpr long double epsilon=1e-9L;
Point difference(Point a,Point b){return {a[0]-b[0],a[1]-b[1],a[2]-b[2]};}
Point cross(Point a,Point b){return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};}
long double length(Point a){return std::hypot(a[0],a[1],a[2]);}
long double value(const Plane &p,Point a){const auto n=planeNormal(p);return n[0]*a[0]+n[1]*a[1]+n[2]*a[2]-p.distance;}
long double area(const Face &f) {
    Point sum{};
    for(size_t k=1;k+1<f.size();++k){const auto n=cross(difference(f[k],f[0]),difference(f[k+1],f[0]));for(int j=0;j<3;++j)sum[j]+=n[j];}
    return length(sum)/2;
}
Face convert(const Polygon &p){Face f;for(auto v:p)f.push_back({v.x,v.y,v.z});return f;}
Polygon render(const Face &p){Polygon f;for(auto v:p)f.push_back({float(v[0]),float(v[1]),float(v[2])});return f;}
Face clip(const Face &p,const Plane &plane,bool inside=true) {
    Face out;if(p.empty())return out;
    for(size_t i=0;i<p.size();++i) {
        const auto a=p[i],b=p[(i+1)%p.size()];auto u=value(plane,a),v=value(plane,b);
        if(std::abs(u)<epsilon)u=0;if(std::abs(v)<epsilon)v=0;
        if(!inside){u=-u;v=-v;}
        if(u<=0)out.push_back(a);
        if(u*v<0){const auto t=u/(u-v);Point q;for(int k=0;k<3;++k)q[k]=a[k]+t*(b[k]-a[k]);out.push_back(q);}
    }
    Face clean;
    for(auto v:out)if(clean.empty() || length(difference(v,clean.back()))>epsilon)clean.push_back(v);
    if(clean.size()>1 && length(difference(clean.front(),clean.back()))<epsilon)clean.pop_back();
    return clean;
}
}
Polygon clipToVolumeSingleRound(Polygon face,const Volume &volume) {
    auto f=convert(face);for(const auto &p:volume.planes)f=clip(f,p);return render(f);
}
std::vector<Polygon> exposedSingleRound(Polygon face,const std::vector<Volume> &volumes,int owner) {
    const auto original=convert(face);std::vector<Face> parts{original};
    Point n{};for(size_t k=1;k+1<original.size();++k){const auto c=cross(difference(original[k],original[0]),difference(original[k+1],original[0]));for(int j=0;j<3;++j)n[j]+=c[j];}
    const auto magnitude=length(n);if(magnitude==0)return {face};for(auto &c:n)c/=magnitude;
    for(size_t i=0;i<volumes.size() && !parts.empty();++i) {
        if(int(i)==owner)continue;
        const auto &planes=volumes[i].planes;
        const bool coplanar=std::any_of(planes.begin(),planes.end(),[&](const auto &plane){
            const auto m=planeNormal(plane);
            return n[0]*m[0]+n[1]*m[1]+n[2]*m[2]>.99999L &&
                std::all_of(original.begin(),original.end(),[&](auto p){return std::abs(value(plane,p))<epsilon;});
        });
        if(coplanar && (owner==-2 || (owner>=0 && int(i)>owner)))continue;
        std::vector<Face> keep;
        for(const auto &part:parts) {
            const bool separate=std::any_of(planes.begin(),planes.end(),[&](const auto &plane){return std::all_of(part.begin(),part.end(),[&](auto p){return value(plane,p)>epsilon;});});
            if(separate){keep.push_back(part);continue;}
            auto intersection=part;for(const auto &plane:planes){intersection=clip(intersection,plane);if(intersection.size()<3)break;}
            if(intersection.size()<3 || area(intersection)<1e-10L){keep.push_back(part);continue;}
            auto inside=part;
            for(const auto &plane:planes) {
                if(std::any_of(inside.begin(),inside.end(),[&](auto p){return value(plane,p)>epsilon;})) {
                    auto outside=clip(inside,plane,false);if(outside.size()>=3 && area(outside)>1e-10L)keep.push_back(std::move(outside));
                }
                inside=clip(inside,plane);if(inside.size()<3)break;
            }
        }
        parts=std::move(keep);
    }
    std::vector<Polygon> result;for(const auto &f:parts)result.push_back(render(f));
    return consolidateExactPlanar(std::move(result),{float(n[0]),float(n[1]),float(n[2])});
}
}
