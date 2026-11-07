#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

namespace dw::rockFormations {
using SnapPoint=std::array<long long,2>;
struct LabelledSnapRing {std::vector<SnapPoint> points;size_t label;};

// Route every segment through the same hot-pixel centres. Intersections and
// pixel/segment membership use integer predicates, not a proximity tolerance.
inline void snapRoundPlateauRings(std::vector<LabelledSnapRing> &rings,long long binWidth,unsigned pass=0) {
    using Wide=__int128_t;using Edge=std::pair<SnapPoint,SnapPoint>;
    if(binWidth<=0)throw std::runtime_error("Invalid snap-round spatial bin");
    auto turn=[](SnapPoint a,SnapPoint b,SnapPoint c)->Wide{return Wide(b[0]-a[0])*(c[1]-a[1])-Wide(b[1]-a[1])*(c[0]-a[0]);};
    auto bin=[&](long long x){auto q=x/binWidth;if(x<0 && x%binWidth)--q;return q;};
    auto key=[](SnapPoint a,SnapPoint b){return a<b?Edge{a,b}:Edge{b,a};};
    auto rounded=[](Wide n,Wide d)->long long {
        if(d<0){n=-n;d=-d;}const bool negative=n<0;if(negative)n=-n;
        const Wide value=(n+d/2)/d;
        if(value>(Wide(1)<<29))throw std::runtime_error("Snap-round coordinate exceeds exact arithmetic scope");
        return static_cast<long long>(negative?-value:value);
    };
    std::set<Edge> unique;
    std::set<SnapPoint> pixels;
    for(const auto &ring:rings)for(size_t k=0;k<ring.points.size();++k) {
        const auto a=ring.points[k],b=ring.points[(k+1)%ring.points.size()];
        for(auto p:{a,b})for(auto v:p)if(v<-(1LL<<29) || v>(1LL<<29))throw std::runtime_error("Snap-round input exceeds exact arithmetic scope");
        pixels.insert(a);if(a!=b)unique.insert(key(a,b));
    }
    std::vector<Edge> edges(unique.begin(),unique.end());
    std::map<SnapPoint,std::vector<size_t>> edgeBins;
    std::set<std::pair<size_t,size_t>> pairs;
    for(size_t i=0;i<edges.size();++i) {
        const auto [a,b]=edges[i];
        for(auto x=bin(std::min(a[0],b[0]));x<=bin(std::max(a[0],b[0]));++x)
            for(auto z=bin(std::min(a[1],b[1]));z<=bin(std::max(a[1],b[1]));++z) {
                auto &near=edgeBins[{x,z}];for(auto j:near)pairs.insert({j,i});near.push_back(i);
            }
    }
    size_t crossings=0;
    std::map<Edge,std::set<SnapPoint>> forcedIntersections;
    for(auto [i,j]:pairs) {
        const auto [a,b]=edges[i];const auto [c,d]=edges[j];
        const Wide u=turn(a,b,c),v=turn(a,b,d),s=turn(c,d,a),t=turn(c,d,b);
        auto opposite=[](Wide a,Wide b){return (a<0 && b>0)||(a>0 && b<0);};
        if(!opposite(u,v) || !opposite(s,t))continue;
        // a + s/(s-t) * (b-a), with exact rational rounding.
        const SnapPoint pixel{rounded(Wide(a[0])*(s-t)+Wide(b[0]-a[0])*s,s-t),
                              rounded(Wide(a[1])*(s-t)+Wide(b[1]-a[1])*s,s-t)};
        pixels.insert(pixel);forcedIntersections[edges[i]].insert(pixel);forcedIntersections[edges[j]].insert(pixel);++crossings;
    }
    std::map<SnapPoint,std::vector<SnapPoint>> pixelBins;
    for(auto p:pixels)pixelBins[{bin(p[0]),bin(p[1])}].push_back(p);
    auto visits=[](SnapPoint a,SnapPoint b,SnapPoint p) {
        if(p==a || p==b)return true;
        struct Ratio{Wide n,d;};Ratio low{0,1},high{1,1};
        auto less=[](Ratio a,Ratio b){return a.n*b.d<b.n*a.d;};
        for(int k=0;k<2;++k) {
            const Wide origin=Wide(a[k])*2,delta=Wide(b[k]-a[k])*2;
            const Wide lo=Wide(p[k])*2-1,hi=Wide(p[k])*2+1;
            if(delta==0){if(origin<=lo || origin>=hi)return false;continue;}
            Ratio enter{lo-origin,delta},leave{hi-origin,delta};
            if(delta<0){enter={origin-hi,-delta};leave={origin-lo,-delta};}
            if(less(low,enter))low=enter;if(less(leave,high))high=leave;
            // Exclude mere corner tangency; adjacent hot pixels must not
            // both attract a segment that only touches their corners.
            if(!less(low,high))return false;
        }
        return true;
    };
    std::map<Edge,std::vector<SnapPoint>> routes;
    size_t routeVertices=0;
    for(const auto &edge:edges) {
        const auto [a,b]=edge;auto &route=routes[edge];
        // A genuine intersection exactly on a pixel corner still belongs
        // to its one rounded pixel. Mere unrelated tangencies stay excluded.
        if(const auto forced=forcedIntersections.find(edge);forced!=forcedIntersections.end())route.insert(route.end(),forced->second.begin(),forced->second.end());
        for(auto x=bin(std::min(a[0],b[0])-1);x<=bin(std::max(a[0],b[0])+1);++x)
            for(auto z=bin(std::min(a[1],b[1])-1);z<=bin(std::max(a[1],b[1])+1);++z) {
                const auto found=pixelBins.find({x,z});if(found==pixelBins.end())continue;
                for(auto p:found->second)if(visits(a,b,p))route.push_back(p);
            }
        auto projection=[&](SnapPoint p){return Wide(p[0]-a[0])*(b[0]-a[0])+Wide(p[1]-a[1])*(b[1]-a[1]);};
        std::sort(route.begin(),route.end(),[&](auto p,auto q){const auto u=projection(p),v=projection(q);return u!=v?u<v:p<q;});
        route.erase(std::unique(route.begin(),route.end()),route.end());
        if(route.empty() || route.front()!=a || route.back()!=b)throw std::runtime_error("Snap-round route loses its original endpoints");
        routeVertices+=route.size();
    }
    // A rounded intersection is useful only if the entire routed graph is
    // planar. Check it before passing any labels to the ownership scan.
    std::set<Edge> routed;
    for(const auto &[edge,route]:routes)for(size_t k=1;k<route.size();++k)if(route[k-1]!=route[k])routed.insert(key(route[k-1],route[k]));
    edgeBins.clear();pairs.clear();
    std::vector<Edge> routedEdges(routed.begin(),routed.end());
    size_t outputCrossings=0;
    for(size_t i=0;i<routedEdges.size();++i) {
        const auto [a,b]=routedEdges[i];std::set<size_t> seen;
        for(auto x=bin(std::min(a[0],b[0]));x<=bin(std::max(a[0],b[0]));++x)
            for(auto z=bin(std::min(a[1],b[1]));z<=bin(std::max(a[1],b[1]));++z) {
                auto &near=edgeBins[{x,z}];
                for(auto j:near)if(seen.insert(j).second) {
                    const auto [c,d]=routedEdges[j];const Wide u=turn(a,b,c),v=turn(a,b,d),s=turn(c,d,a),t=turn(c,d,b);
                    auto opposite=[](Wide a,Wide b){return (a<0 && b>0)||(a>0 && b<0);};
                    if(opposite(u,v) && opposite(s,t)) {
                        if(!outputCrossings)std::cout<<"PLATEAU_SNAP_CROSSING pass="<<pass<<" a="<<a[0]<<','<<a[1]<<" b="<<b[0]<<','<<b[1]<<" c="<<c[0]<<','<<c[1]<<" d="<<d[0]<<','<<d[1]<<'\n';
                        ++outputCrossings;
                    }
                }
                near.push_back(i);
            }
    }
    for(auto &ring:rings) {
        std::vector<SnapPoint> output;
        for(size_t k=0;k<ring.points.size();++k) {
            const auto a=ring.points[k],b=ring.points[(k+1)%ring.points.size()];if(a==b)continue;
            const auto &route=routes.at(key(a,b));
            if(a<b)output.insert(output.end(),route.begin(),route.end()-1);
            else output.insert(output.end(),route.rbegin(),route.rend()-1);
        }
        output.erase(std::unique(output.begin(),output.end()),output.end());ring.points=std::move(output);
    }
    std::cout<<"PLATEAU_SNAP_ROUND pass="<<pass<<" edges="<<edges.size()<<" proper_input_crossings="<<crossings<<" hot_pixels="<<pixels.size()<<" route_vertices="<<routeVertices<<" proper_output_crossings="<<outputCrossings<<'\n';
    if(outputCrossings) {
        if(pass>=3)throw std::runtime_error("Snap-rounded arrangement still crosses after four bounded routing passes");
        snapRoundPlateauRings(rings,binWidth,pass+1);
    }
}
}
