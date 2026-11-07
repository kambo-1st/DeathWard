#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "raylib.h"
#include <array>
#include <bit>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

namespace dw::rockFormations::exactContact {
using Integer=boost::multiprecision::cpp_int;
using Point=std::array<Integer,3>;
inline Point sub(const Point &a,const Point &b){return {a[0]-b[0],a[1]-b[1],a[2]-b[2]};}
inline Point mul(const Point &a,const Integer &b){return {a[0]*b,a[1]*b,a[2]*b};}
inline Integer dot(const Point &a,const Point &b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
inline Point cross(const Point &a,const Point &b){return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};}
inline Integer coordinate(float value) {
    // Every finite float is an integer multiple of 2^-149. A common scale
    // eliminates division and preserves even subnormal coordinates exactly.
    const auto bits=std::bit_cast<uint32_t>(value);const auto exponent=(bits>>23)&255;
    if(exponent==255)throw std::runtime_error("Nonfinite coordinate in exact contact audit");
    Integer result=bits&0x7fffff;
    if(exponent){result+=1u<<23;result<<=exponent-1;}
    return bits>>31?-result:result;
}
struct Triangle {
    std::array<Point,3> p;Point normal;
    explicit Triangle(const std::array<Vector3,3> &face) {
        for(int k=0;k<3;++k)p[k]={coordinate(face[k].x),coordinate(face[k].y),coordinate(face[k].z)};
        normal=cross(sub(p[1],p[0]),sub(p[2],p[0]));
    }
};
inline bool inside(const Point &numerator,const Integer &denominator,const Triangle &t) {
    for(int k=0;k<3;++k)if(dot(t.normal,cross(sub(t.p[(k+1)%3],t.p[k]),sub(numerator,mul(t.p[k],denominator))))<0)return false;
    return true;
}
inline bool positiveCoplanarOverlap(const Triangle &a,const Triangle &b) {
    int omit=0;while(omit<3 && a.normal[omit]==0)++omit;
    if(omit==3)return false;
    const int u=(omit+1)%3,v=(omit+2)%3;
    // Strict separating-axis overlap excludes edge/point-only contact and
    // retains every positive area, with no minimum area threshold.
    for(const Triangle *t:{&a,&b})for(int k=0;k<3;++k) {
        const auto e=sub(t->p[(k+1)%3],t->p[k]);
        auto value=[&](const Point &p)->Integer{return e[u]*p[v]-e[v]*p[u];};
        Integer alo=value(a.p[0]),ahi=alo,blo=value(b.p[0]),bhi=blo;
        for(int j=1;j<3;++j){const Integer x=value(a.p[j]),y=value(b.p[j]);if(x<alo)alo=x;if(x>ahi)ahi=x;if(y<blo)blo=y;if(y>bhi)bhi=y;}
        if(ahi<=blo || bhi<=alo)return false;
    }
    return true;
}
// 0: disjoint or legitimate shared vertex/edge; 1: other contact/crossing;
// 2: positive coplanar overlap. Degenerate input also rejects as type 1.
inline int classify(const Triangle &a,const Triangle &b) {
    if(a.normal==Point{} || b.normal==Point{})return 1;
    std::array<Integer,3> da,db;
    for(int k=0;k<3;++k){da[k]=dot(b.normal,sub(a.p[k],b.p[0]));db[k]=dot(a.normal,sub(b.p[k],a.p[0]));}
    auto separated=[](const auto &d){return (d[0]>0 && d[1]>0 && d[2]>0)||(d[0]<0 && d[1]<0 && d[2]<0);};
    if(separated(da)||separated(db))return 0;
    if(da==std::array<Integer,3>{} && db==std::array<Integer,3>{})return positiveCoplanarOverlap(a,b)?2:0;
    std::vector<Point> common;for(const auto &p:a.p)for(const auto &q:b.p)if(p==q)common.push_back(p);
    if(common.size()>=2)return 0;
    auto legitimate=[&](const Point &n,const Integer &d){for(const auto &p:common)if(n==mul(p,d))return true;return false;};
    auto crossing=[&](const Triangle &from,const Triangle &to,const std::array<Integer,3> &distances) {
        for(int k=0;k<3;++k) {
            const int j=(k+1)%3;const auto &u=distances[k],&v=distances[j];
            if(u==0 && inside(from.p[k],Integer(1),to) && !legitimate(from.p[k],Integer(1)))return true;
            if((u<0 && v>0)||(u>0 && v<0)) {
                Integer denominator=u-v;
                Point numerator;
                for(int axis=0;axis<3;++axis)numerator[axis]=from.p[k][axis]*denominator+(from.p[j][axis]-from.p[k][axis])*u;
                if(denominator<0){denominator=-denominator;for(auto &x:numerator)x=-x;}
                if(inside(numerator,denominator,to) && !legitimate(numerator,denominator))return true;
            }
        }
        return false;
    };
    return crossing(a,b,da)||crossing(b,a,db)?1:0;
}
}
#endif
