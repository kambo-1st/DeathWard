#include "RockFormations.hpp"
#include "FormationPrecision.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <stdexcept>

namespace dw::rockFormations {
// A vertical arrangement of the input boundaries, rather than independently
// rounded polygon differences. Interior input edges remain constraints so that
// each output triangle can still be assigned to an original roof plane.
cliffOptions::Mesh arrangePlateauFootprint(const std::vector<Polygon> &polygons,float tolerance) {
    struct Point {float x,z;auto operator<=>(const Point &)const=default;};
    struct Segment {Point a,b;};
    std::vector<Segment> edges;std::set<std::pair<Point,Point>> unique;
    using Real=long double;
    std::set<Real> cuts;
    for(const auto &polygon:polygons)for(size_t k=0;k<polygon.size();++k) {
        auto p=polygon[k],q=polygon[(k+1)%polygon.size()];Point a{p.x,p.z},b{q.x,q.z};
        if(b<a)std::swap(a,b);if(a==b || !unique.emplace(a,b).second)continue;
        edges.push_back({a,b});cuts.insert(a.x);cuts.insert(b.x);
    }
    auto cross=[](Real ax,Real az,Real bx,Real bz){return ax*bz-az*bx;};
    struct Crossing {size_t a,b;float z;};
    std::map<Real,std::vector<Crossing>> crossings;
    for(size_t i=0;i<edges.size();++i)for(size_t j=i+1;j<edges.size();++j) {
        const auto [a,b]=edges[i];const auto [c,d]=edges[j];
        if(std::max(a.x,c.x)>std::min(b.x,d.x) || std::max(std::min(a.z,b.z),std::min(c.z,d.z))>std::min(std::max(a.z,b.z),std::max(c.z,d.z)))continue;
        const Real ux=Real(b.x)-a.x,uz=Real(b.z)-a.z,vx=Real(d.x)-c.x,vz=Real(d.z)-c.z;
        const Real det=cross(ux,uz,vx,vz);if(det==0)continue;
        const Real wx=Real(c.x)-a.x,wz=Real(c.z)-a.z;
        const Real t=cross(wx,wz,vx,vz)/det,s=cross(wx,wz,ux,uz)/det;
        if(t<0 || t>1 || s<0 || s>1)continue;
        const Real x=t==0?a.x:t==1?b.x:s==0?c.x:s==1?d.x:a.x+t*ux;
        const Real z=t==0?a.z:t==1?b.z:s==0?c.z:s==1?d.z:a.z+t*uz;
        const auto p=canonicalRenderPoint({float(x),0,float(z)});
        if(std::abs(Real(p.x)-x)>tolerance)throw std::runtime_error("Projected crossing exceeds the construction weld radius");
        cuts.insert(x);crossings[x].push_back({i,j,p.z});
    }
    auto at=[&](size_t id,Real x) {
        const auto [a,b]=edges[id];if(x==a.x)return Real(a.z);if(x==b.x)return Real(b.z);
        if(a.x==b.x)throw std::runtime_error("Cannot sample a vertical arrangement edge");
        return Real(a.z)+(x-a.x)*(Real(b.z)-a.z)/(Real(b.x)-a.x);
    };
    struct Cut {float x;Real first,last;std::vector<float> nodes;};
    std::vector<Cut> planes;
    // Several distinct crossings can share a rendered X coordinate while
    // remaining distinct Z nodes. Keep that vertical chain; never weld the
    // entire near-vertical segment into a single point.
    for(Real x:cuts) {
        const float rendered=canonicalRenderPoint({float(x),0,0}).x;
        if(planes.empty() || planes.back().x!=rendered)planes.push_back({rendered,x,x,{}});
        else planes.back().last=x;
    }
    std::map<std::pair<Real,size_t>,float> shared;
    for(const auto &[x,events]:crossings)for(auto event:events) {
        for(auto id:{event.a,event.b})if(edges[id].a.x!=edges[id].b.x) {
            auto [it,added]=shared.emplace(std::pair{x,id},event.z);
            if(!added && it->second!=event.z) {
                if(std::abs(double(it->second)-event.z)>tolerance)throw std::runtime_error("Inconsistent projected multi-way crossing");
                it->second=std::min(it->second,event.z);
            }
        }
    }
    auto sample=[&](size_t id,Real x) {
        auto found=shared.find({x,id});return found==shared.end()?float(at(id,x)):found->second;
    };
    for(auto &cut:planes) {
        for(size_t i=0;i<edges.size();++i) {
            const auto [a,b]=edges[i];
            if(a.x>=cut.first && a.x<=cut.last)cut.nodes.push_back(a.z);
            if(b.x>=cut.first && b.x<=cut.last)cut.nodes.push_back(b.z);
            if(a.x==b.x)continue;
            if(cut.first>=a.x && cut.first<=b.x)cut.nodes.push_back(sample(i,cut.first));
            if(cut.last>=a.x && cut.last<=b.x)cut.nodes.push_back(sample(i,cut.last));
        }
        for(auto at=crossings.lower_bound(cut.first);at!=crossings.end() && at->first<=cut.last;++at)
            for(auto event:at->second)cut.nodes.push_back(event.z);
        std::sort(cut.nodes.begin(),cut.nodes.end());cut.nodes.erase(std::unique(cut.nodes.begin(),cut.nodes.end()),cut.nodes.end());
    }
    cliffOptions::Mesh mesh;
    for(size_t k=0;k+1<planes.size();++k) {
        const auto &left=planes[k],&right=planes[k+1];const Real middle=(left.last+right.first)*.5;
        std::vector<std::pair<Real,size_t>> order;
        for(size_t i=0;i<edges.size();++i) {
            const auto [a,b]=edges[i];if(middle<=a.x || middle>=b.x)continue;
            const Real z=Real(a.z)+(middle-a.x)*(Real(b.z)-a.z)/(Real(b.x)-a.x);
            order.emplace_back(z,i);
        }
        std::sort(order.begin(),order.end());
        std::vector<std::pair<Real,Real>> intervals;
        for(const auto &polygon:polygons) {
            std::vector<Real> hits;
            for(size_t e=0;e<polygon.size();++e) {
                const auto a=polygon[e],b=polygon[(e+1)%polygon.size()];
                if((a.x>middle)==(b.x>middle))continue;
                hits.push_back(Real(a.z)+(middle-a.x)*(Real(b.z)-a.z)/(Real(b.x)-a.x));
            }
            std::sort(hits.begin(),hits.end());
            for(size_t h=0;h+1<hits.size();h+=2)intervals.emplace_back(hits[h],hits[h+1]);
        }
        std::sort(intervals.begin(),intervals.end());
        std::vector<std::pair<Real,Real>> covered;
        for(auto interval:intervals) {
            if(!covered.empty() && interval.first<=covered.back().second)covered.back().second=std::max(covered.back().second,interval.second);
            else covered.push_back(interval);
        }
        size_t coverage=0;
        for(size_t j=0;j+1<order.size();++j) {
            if(order[j].first==order[j+1].first)continue;
            const Real z=(order[j].first+order[j+1].first)*.5;
            while(coverage<covered.size() && covered[coverage].second<z)++coverage;
            if(coverage==covered.size() || covered[coverage].first>z)continue;
            const auto low=order[j].second,high=order[j+1].second;
            const float loL=sample(low,left.last),hiL=sample(high,left.last);
            const float loR=sample(low,right.first),hiR=sample(high,right.first);
            if(loL>hiL || loR>hiR)throw std::runtime_error("Projected arrangement changes edge order inside a slab");
            Polygon l,r;
            for(float q:left.nodes)if(q>=loL && q<=hiL)l.push_back({left.x,0,q});
            for(float q:right.nodes)if(q>=loR && q<=hiR)r.push_back({right.x,0,q});
            // The band is a convex trapezoid. A zipper keeps every collinear
            // vertical-side node without applying a small-area ear threshold.
            size_t a=0,b=0;
            while(a+1<l.size() || b+1<r.size()) {
                if(a+1<l.size() && (b+1==r.size() || l[a+1].z<=r[b+1].z)) {
                    mesh.faces.push_back({l[a],l[a+1],r[b]});++a;
                } else {mesh.faces.push_back({l[a],r[b+1],r[b]});++b;}
            }
        }
    }
    return mesh;
}
}
