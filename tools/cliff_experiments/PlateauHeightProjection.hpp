#pragma once
#include "raylib.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace dw::rockFormations {
struct PlateauHeightOffset {double lower=0,upper=0,value=0;};
struct PlateauHeightConstraint {
    std::array<size_t,3> vertices;
    std::array<double,3> heights;
    std::array<Vector3,3> face;
};
// Change the constructed active field, never audit tolerances. Shared XY
// vertices use one additive correction, bounded by every incident source's
// source/target/floor interval. Cold and full-target vertices are fixed.
inline void projectPlateauVertexSlopes(std::vector<PlateauHeightOffset> &offsets,
    const std::vector<PlateauHeightConstraint> &triangles) {
    constexpr double maximumSlope=9.9; // Strictly below sqrt(99), the existing up>.1 gate.
    struct Constraint {std::array<size_t,3> id;std::array<double,3> height;double t,length,altitude;};
    std::vector<Constraint> constraints;
    for(const auto &tri:triangles) {
        auto distance=[](Vector3 a,Vector3 b){return std::hypot(double(b.x)-a.x,double(b.z)-a.z);};
        int first=0;double length=0;
        for(int k=0;k<3;++k){const auto d=distance(tri.face[k],tri.face[(k+1)%3]);if(d>length){length=d;first=k;}}
        const int a=first,c=(first+1)%3,b=(first+2)%3;
        if(length==0)throw std::runtime_error("Height projection has a collapsed edge");
        const auto p=tri.face[a],q=tri.face[b],r=tri.face[c];
        const double dx=double(r.x)-p.x,dz=double(r.z)-p.z;
        const double t=((double(q.x)-p.x)*dx+(double(q.z)-p.z)*dz)/(length*length);
        const double altitude=std::abs(dx*(double(q.z)-p.z)-dz*(double(q.x)-p.x))/length;
        if(altitude==0)throw std::runtime_error("Height projection has a zero-area triangle");
        constraints.push_back({{tri.vertices[a],tri.vertices[b],tri.vertices[c]},
            {tri.heights[a],tri.heights[b],tri.heights[c]},t,length,altitude});
    }
    auto values=[&](const Constraint &c){return std::array<double,3>{c.height[0]+offsets[c.id[0]].value,c.height[1]+offsets[c.id[1]].value,c.height[2]+offsets[c.id[2]].value};};
    auto slope=[&](const Constraint &c) {
        const auto h=values(c);const double parallel=(h[2]-h[0])/c.length;
        const double across=(h[1]-std::lerp(h[0],h[2],c.t))/c.altitude;
        return std::hypot(parallel,across);
    };
    auto adjust=[&](const Constraint &c,std::array<double,3> coefficients,double desired) {
        for(int pass=0;pass<4;++pass) {
            const auto h=values(c);double residual=-desired;
            for(int k=0;k<3;++k)residual+=coefficients[k]*h[k];
            if(std::abs(residual)<1e-14)return;
            std::array<bool,3> free{};double denominator=0;
            for(int k=0;k<3;++k) {
                const auto &v=offsets[c.id[k]];const double direction=-residual*coefficients[k];
                free[k]=(direction<0 && v.value>v.lower)||(direction>0 && v.value<v.upper);
                if(free[k])denominator+=coefficients[k]*coefficients[k];
            }
            if(denominator==0)return;
            for(int k=0;k<3;++k)if(free[k]) {
                auto &v=offsets[c.id[k]];v.value=std::clamp(v.value-residual*coefficients[k]/denominator,v.lower,v.upper);
            }
        }
    };
    size_t initial=0;for(const auto &c:constraints)initial+=slope(c)>maximumSlope;
    size_t passes=0,remaining=initial;
    for(;passes<256 && remaining;++passes) {
        for(const auto &c:constraints) {
            if(slope(c)<=maximumSlope)continue;
            auto h=values(c);double along=h[2]-h[0];
            if(std::abs(along)>maximumSlope*c.length)adjust(c,{-1,0,1},std::copysign(maximumSlope*c.length,along));
            h=values(c);const double parallel=(h[2]-h[0])/c.length;
            const double limit=std::sqrt(std::max(0.,maximumSlope*maximumSlope-parallel*parallel))*c.altitude;
            const double residual=h[1]-std::lerp(h[0],h[2],c.t);
            if(std::abs(residual)>limit)adjust(c,{-(1-c.t),1,-c.t},std::copysign(limit,residual));
        }
        remaining=0;for(const auto &c:constraints)remaining+=slope(c)>maximumSlope+1e-5;
    }
    double maximum=0;for(const auto &v:offsets)maximum=std::max(maximum,std::abs(v.value));
    std::cout<<"PLATEAU_VERTEX_PROJECT triangles="<<constraints.size()<<" initial_steep="<<initial<<" remaining_steep="<<remaining<<" passes="<<passes<<" maximum_height_change_m="<<maximum<<" slope_target="<<maximumSlope<<'\n';
    // Unresolved constraints are retained. The original native slope, source,
    // topology, coverage and floor guards still reject invalid construction.
}
}
