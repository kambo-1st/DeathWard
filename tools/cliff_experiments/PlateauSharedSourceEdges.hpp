#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "PlateauSourceReuse.hpp"
#include <manifold/polygon.h>
#include <fstream>

namespace dw::rockFormations::sharedSourceEdges {
using Q=std::array<long long,2>;
using Wide=boost::multiprecision::int256_t;
using R=sourceReuse::R;
using H=sourceReuse::H;
using Key=std::pair<size_t,size_t>;
constexpr size_t Outside=size_t(-1);
inline Wide turn(Q a,Q b,Q c){return (Wide(b[0])-a[0])*(Wide(c[1])-a[1])-(Wide(b[1])-a[1])*(Wide(c[0])-a[0]);}
inline Wide area2(const std::vector<Q> &p){Wide a=0;for(size_t k=0;k<p.size();++k)a+=Wide(p[k][0])*p[(k+1)%p.size()][1]-Wide(p[k][1])*p[(k+1)%p.size()][0];return a;}
inline Key key(size_t a,size_t b){return std::minmax(a,b);}
inline bool conflict(Q a,Q b,Q c,Q d) {
    if(std::max(a[0],b[0])<std::min(c[0],d[0]) || std::max(c[0],d[0])<std::min(a[0],b[0]) || std::max(a[1],b[1])<std::min(c[1],d[1]) || std::max(c[1],d[1])<std::min(a[1],b[1]))return false;
    const auto u=turn(a,b,c),v=turn(a,b,d),s=turn(c,d,a),t=turn(c,d,b);
    if(a==c || a==d || b==c || b==d) {
        if(u!=0 || v!=0)return false;
        const int axis=a[0]!=b[0]?0:1;
        return std::max(std::min(a[axis],b[axis]),std::min(c[axis],d[axis]))<std::min(std::max(a[axis],b[axis]),std::max(c[axis],d[axis]));
    }
    return u*v<=0 && s*t<=0;
}
struct Loop{size_t group;bool hole;std::vector<Q> points;};
struct Group{Plane plane;H height;std::set<size_t> sourceEdges;};
struct Edge{size_t right,left;}; // Direction is the sorted vertex-ID key.
struct OriginalEdge{Vector3 a,b;};
inline bool near(Q p,const OriginalEdge &e,const R &limit) {
    const sourceReuse::P a{R(e.a.x),R(e.a.z)},b{R(e.b.x),R(e.b.z)},q{R(p[0])/65536,R(p[1])/65536};
    const R x=b[0]-a[0],z=b[1]-a[1],length=x*x+z*z;if(length==0)return false;
    R t=((q[0]-a[0])*x+(q[1]-a[1])*z)/length;t=std::max(R(0),std::min(R(1),t));
    const R dx=q[0]-a[0]-t*x,dz=q[1]-a[1]-t*z;return dx*dx+dz*dz<=limit*limit;
}

// Simplify shared *internal* original-source interfaces as one planar network.
// Every source cell remains represented. Outer/floor/hole boundaries are fixed.
inline std::vector<GradedRoofCell> simplify(const std::vector<GradedRoofCell> &input,const std::vector<Polygon> &original,const char *certificate=nullptr) {
    ConstructionTiming timing("shared_source_edges");ConstructionChecks checks;
    std::map<std::array<double,4>,size_t> groupIds;std::vector<Group> groups;std::vector<size_t> inputGroups;std::vector<Loop> raw;Wide originalSum=0;std::set<Q> allPoints;
    for(const auto &cell:input) {
        const auto n=planeNormal(cell.roof);const std::array<double,4> k{n[0],n[1],n[2],cell.roof.distance};
        auto [at,added]=groupIds.emplace(k,groups.size());if(added)groups.push_back({cell.roof,sourceReuse::height(cell.roof),{}});
        inputGroups.push_back(at->second);
        std::vector<Q> p;for(auto q:cell.outline){const double x=double(q.x)*65536,z=double(q.z)*65536;if(x!=std::round(x) || z!=std::round(z) || std::abs(x)>1e9 || std::abs(z)>1e9)throw std::runtime_error("Shared source edge exceeds the construction grid");p.push_back({std::llround(x),std::llround(z)});}const auto a=area2(p);if(a==0)throw std::runtime_error("Shared source input has a zero-area cell");if(a>0)std::reverse(p.begin(),p.end());originalSum+=abs(a);allPoints.insert(p.begin(),p.end());raw.push_back({at->second,false,std::move(p)});
    }
    using E3=std::array<float,3>;std::map<std::pair<E3,E3>,size_t> sourceEdgeIds;std::vector<OriginalEdge> sourceEdges;
    for(const auto &source:original) {
        const auto h=sourceReuse::height(source);std::vector<size_t> edges;
        for(size_t k=0;k<source.size();++k) {
            const auto a=source[k],b=source[(k+1)%source.size()];E3 x{a.x,a.y,a.z},y{b.x,b.y,b.z};if(y<x)std::swap(x,y);
            auto [at,added]=sourceEdgeIds.emplace(std::pair{x,y},sourceEdges.size());if(added)sourceEdges.push_back({a,b});edges.push_back(at->second);
        }
        for(auto &g:groups)if(std::abs((g.height[0]-h[0]).convert_to<double>())<=1e-10 && std::abs((g.height[1]-h[1]).convert_to<double>())<=1e-10 && std::abs((g.height[2]-h[2]).convert_to<double>())<=1e-10)g.sourceEdges.insert(edges.begin(),edges.end());
    }
    using Line=std::array<long long,3>;
    struct Event{int count=0,direction=0;};
    std::map<Line,std::map<long long,std::map<size_t,Event>>> events;
    for(const auto &loop:raw) {
            const auto group=loop.group;
            for(size_t k=0;k<loop.points.size();++k) {
                const auto a=loop.points[k],b=loop.points[(k+1)%loop.points.size()];const auto x=b[0]-a[0],z=b[1]-a[1],g=std::gcd(x,z);if(!g)continue;
                long long A=z/g,B=-x/g,C=-A*a[0]-B*a[1];if(A<0 || (A==0 && B<0)){A=-A;B=-B;C=-C;}
                const int axis=B?0:1,dir=a[axis]<b[axis]?1:-1;const auto lo=std::min(a[axis],b[axis]),hi=std::max(a[axis],b[axis]);
                auto &start=events[{A,B,C}][lo][group],&end=events[{A,B,C}][hi][group];++start.count;start.direction+=dir;--end.count;end.direction-=dir;
            }
    }
    for(auto &[line,positions]:events) {
        const auto [A,B,C]=line;const int axis=B?0:1;const auto lo=positions.begin()->first,hi=positions.rbegin()->first;
        for(auto p:allPoints)if(p[axis]>lo && p[axis]<hi && Wide(A)*p[0]+Wide(B)*p[1]+C==0)positions.try_emplace(p[axis]);
    }
    std::map<Q,size_t> ids;std::vector<Q> points;std::map<Key,Edge> edges;std::vector<std::set<size_t>> neighbours;
    auto id=[&](Q p){auto [at,added]=ids.emplace(p,points.size());if(added){points.push_back(p);neighbours.emplace_back();}return at->second;};
    for(const auto &[line,positions]:events) {
        std::map<size_t,Event> active;
        for(auto at=positions.begin();at!=positions.end();++at) {
            for(const auto &[g,event]:at->second){auto &e=active[g];e.count+=event.count;e.direction+=event.direction;if(!e.count){if(e.direction)throw std::runtime_error("Shared source winding mismatch");active.erase(g);}}
            const auto next=std::next(at);if(next==positions.end() || active.empty())continue;
            std::map<size_t,int> boundary;
            for(const auto &[g,e]:active){if(e.count<0 || std::abs(e.direction)>1)throw std::runtime_error("Shared source repeats a directed plane boundary");if(e.direction)boundary[g]=e.direction;}
            if(boundary.empty())continue;
            if(boundary.size()>2)throw std::runtime_error("Shared source has a nonmanifold plane boundary");
            const auto [A,B,C]=line;
            auto point=[&](long long t){const R x=B?R(t):-R(C)/R(A),z=B?(-R(A)*R(t)-R(C))/R(B):R(t);const Q q{x.convert_to<long long>(),z.convert_to<long long>()};if(R(q[0])!=x || R(q[1])!=z)throw std::runtime_error("Shared source T junction leaves the construction grid");return q;};
            size_t a=id(point(at->first)),b=id(point(next->first));Edge edge{Outside,Outside};
            for(const auto &[g,direction]:boundary){auto &side=direction>0?edge.right:edge.left;if(side!=Outside)throw std::runtime_error("Shared source boundary owners have equal winding");side=g;}
            if(b<a){std::swap(a,b);std::swap(edge.left,edge.right);}if(!edges.emplace(Key{a,b},edge).second)throw std::runtime_error("Shared source edge is duplicated");neighbours[a].insert(b);neighbours[b].insert(a);
        }
    }
    auto trace=[&]() {
        std::vector<std::set<Key>> directed(groups.size());
        for(const auto &[k,e]:edges){if(e.right!=Outside)directed[e.right].insert(k);if(e.left!=Outside)directed[e.left].insert({k.second,k.first});}
        std::vector<Loop> loops;
        for(size_t group=0;group<groups.size();++group) {
            std::map<size_t,std::vector<size_t>> outgoing;for(auto [a,b]:directed[group])outgoing[a].push_back(b);
            std::set<Key> visited;
            for(auto start:directed[group])if(!visited.contains(start)) {
                auto current=start;Loop loop{group,false,{}};
                while(!visited.contains(current)) {
                    visited.insert(current);const auto [a,v]=current;loop.points.push_back(points[a]);
                    const auto at=outgoing.find(v);if(at==outgoing.end() || at->second.empty())throw std::runtime_error("Shared source contour has an open end");
                    const Q r{points[a][0]-points[v][0],points[a][1]-points[v][1]};
                    auto earlier=[&](size_t x,size_t y) {
                        const Q p{points[x][0]-points[v][0],points[x][1]-points[v][1]},q{points[y][0]-points[v][0],points[y][1]-points[v][1]};
                        auto half=[&](Q p){const Wide cross=Wide(r[0])*p[1]-Wide(r[1])*p[0],dot=Wide(r[0])*p[0]+Wide(r[1])*p[1];return cross>0 || (cross==0 && dot>=0)?0:1;};
                        const auto hx=half(p),hy=half(q);if(hx!=hy)return hx<hy;const Wide cross=Wide(p[0])*q[1]-Wide(p[1])*q[0];return cross!=0?cross>0:x<y;
                    };
                    current={v,*std::min_element(at->second.begin(),at->second.end(),earlier)};
                }
                if(current!=start || loop.points.size()<3 || area2(loop.points)==0)throw std::runtime_error("Shared source contour is not one positive closed cycle");
                loop.hole=area2(loop.points)>0;loops.push_back(std::move(loop));
            }
        }
        return loops;
    };
    auto totalArea=[&](const std::vector<Loop> &loops){Wide sum=0;for(const auto &loop:loops)sum-=area2(loop.points);return sum;};
    if(totalArea(trace())!=originalSum)throw std::runtime_error("Shared source edge cancellation changes input coverage");
    std::map<Key,Edge> exterior;for(const auto &[k,e]:edges)if(e.left==Outside || e.right==Outside)exterior.emplace(k,e);
    auto validateFlat=[](const cliffOptions::Mesh &mesh) {
        const auto a=auditStrictSurface(mesh);
        if(a.exact.nonmanifoldEdges || a.selfIntersections || a.coplanarOverlaps || a.exact.degenerateFaces || a.exact.duplicateFaces || a.exact.windingErrors)throw std::runtime_error("Shared source field is not a valid planar partition");
    };
    std::vector<Polygon> flatInput;for(const auto &loop:raw){Polygon p;for(auto q:loop.points)p.push_back({float(double(q[0])/65536),0,float(double(q[1])/65536)});flatInput.push_back(std::move(p));}validateFlat(meshPlateauFootprint(flatInput));
    struct Edit{size_t a,v,b,right,left,source;};std::vector<Edit> edits;std::vector<bool> removed(points.size());std::vector<size_t> queue;
    for(size_t i=0;i<points.size();++i)if(neighbours[i].size()==2)queue.push_back(i);
    const R limit=R(1)/50000;
    while(!queue.empty()) {
        const auto v=queue.back();queue.pop_back();if(removed[v] || neighbours[v].size()!=2)continue;
        const auto a=*neighbours[v].begin(),b=*std::next(neighbours[v].begin());if(edges.contains(key(a,b)))continue;
        auto oriented=[&](size_t x,size_t y){auto e=edges.at(key(x,y));if(y<x)std::swap(e.left,e.right);return e;};
        const auto first=oriented(a,v),second=oriented(v,b);if(first.left!=second.left || first.right!=second.right || first.left==Outside || first.right==Outside)continue;
        const auto &g=groups[first.left],&h=groups[first.right];size_t support=sourceEdges.size();
        for(auto e:g.sourceEdges)if(h.sourceEdges.contains(e) && near(points[a],sourceEdges[e],limit) && near(points[v],sourceEdges[e],limit) && near(points[b],sourceEdges[e],limit)){support=e;break;}
        if(support==sourceEdges.size())continue;
        bool safe=true;for(auto p:{points[a],points[v],points[b]}) {const sourceReuse::P q{R(p[0])/65536,R(p[1])/65536};if(abs(sourceReuse::value(g.height,q)-sourceReuse::value(h.height,q))>limit)safe=false;}
        if(!safe)continue;
        const auto sign=turn(points[a],points[v],points[b]);
        if(sign!=0)for(size_t i=0;i<points.size() && safe;++i)if(!removed[i] && i!=a && i!=v && i!=b) {
            const auto p=points[i];if(p[0]<std::min({points[a][0],points[v][0],points[b][0]}) || p[0]>std::max({points[a][0],points[v][0],points[b][0]}) || p[1]<std::min({points[a][1],points[v][1],points[b][1]}) || p[1]>std::max({points[a][1],points[v][1],points[b][1]}))continue;
            const auto u=turn(points[a],points[v],p),w=turn(points[v],points[b],p),t=turn(points[b],points[a],p);
            if(sign>0?(u>=0 && w>=0 && t>=0):(u<=0 && w<=0 && t<=0))safe=false;
        }
        for(const auto &[k,e]:edges)if(safe && k!=key(a,v) && k!=key(v,b) && conflict(points[a],points[b],points[k.first],points[k.second]))safe=false;
        if(!safe)continue;
        edits.push_back({a,v,b,first.right,first.left,support});edges.erase(key(a,v));edges.erase(key(v,b));auto merged=first;if(b<a)std::swap(merged.left,merged.right);edges.emplace(key(a,b),merged);
        neighbours[a].erase(v);neighbours[b].erase(v);neighbours[a].insert(b);neighbours[b].insert(a);neighbours[v].clear();removed[v]=true;queue.push_back(a);queue.push_back(b);
    }
    const auto loops=trace();if(totalArea(loops)!=originalSum)throw std::runtime_error("Shared source contraction changes total signed coverage");
    size_t outsideEdges=0;for(const auto &[k,e]:edges)if(e.left==Outside || e.right==Outside){++outsideEdges;const auto at=exterior.find(k);if(at==exterior.end() || at->second.left!=e.left || at->second.right!=e.right)throw std::runtime_error("Shared source contraction changes an exterior boundary");}
    if(outsideEdges!=exterior.size())throw std::runtime_error("Shared source contraction removes an exterior boundary");
    std::vector<GradedRoofCell> result;cliffOptions::Mesh flatOutput;
    for(size_t group=0;group<groups.size();++group) {
        std::vector<Polygon> triangles;manifold::Polygons contours;std::vector<Vector3> vertices;Wide expected=0;
        for(const auto &loop:loops)if(loop.group==group) {
            expected-=area2(loop.points);manifold::SimplePolygon polygon;
            for(auto at=loop.points.rbegin();at!=loop.points.rend();++at){polygon.push_back({double((*at)[0])/65536,double((*at)[1])/65536});vertices.push_back({float(double((*at)[0])/65536),0,float(double((*at)[1])/65536)});}
            contours.push_back(std::move(polygon));
        }
        Wide area=0;
            for(auto t:manifold::Triangulate(contours,0)) {
                Polygon f{vertices.at(t.x),vertices.at(t.y),vertices.at(t.z)};std::vector<Q> q;for(auto p:f)q.push_back({std::llround(double(p.x)*65536),std::llround(double(p.z)*65536)});const auto a=area2(q);if(a==0)continue;if(a>0){std::swap(f[1],f[2]);std::swap(q[1],q[2]);}area+=abs(a);flatOutput.faces.push_back({f[0],f[1],f[2]});triangles.push_back(std::move(f));
            }
        if(expected<=0 || area!=expected)throw std::runtime_error("Shared source triangulation changes positive signed coverage");
        const auto &plane=groups[group].plane;const auto n=planeNormal(plane);
        for(auto p:consolidateExactPlanar(std::move(triangles),{0,1,0})){for(auto &q:p)q.y=float((plane.distance-n[0]*q.x-n[2]*q.z)/n[1]);result.push_back({std::move(p),plane});}
    }
    validateFlat(flatOutput);
    if(certificate) {
        std::ofstream out(certificate);out.precision(17);out<<"{\"footprint_equal\":true,\"no_positive_plane_overlap\":true,\"maximum_switched_vertical_difference_exact\":\"1/50000\",\"maximum_original_edge_distance_exact\":\"1/50000\",\"input_cells\":"<<input.size()<<",\"output_cell_count\":"<<result.size()<<",\"planes\":[";
        for(size_t i=0;i<groups.size();++i){if(i)out<<',';const auto n=planeNormal(groups[i].plane);out<<'['<<n[0]<<','<<n[1]<<','<<n[2]<<','<<groups[i].plane.distance<<']';}out<<"],\"input_cell_planes\":[";
        for(size_t i=0;i<inputGroups.size();++i){if(i)out<<',';out<<inputGroups[i];}out<<"],\"output_cells\":[";
        for(size_t i=0;i<result.size();++i){if(i)out<<',';const auto &cell=result[i];const auto n=planeNormal(cell.roof);out<<"{\"plane\":"<<groupIds.at({n[0],n[1],n[2],cell.roof.distance})<<",\"points\":[";for(size_t k=0;k<cell.outline.size();++k){if(k)out<<',';const auto p=cell.outline[k];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}out<<"]}";}out<<"],\"edits\":[";
        auto point=[&](size_t i){out<<'['<<points[i][0]<<','<<points[i][1]<<']';};
        for(size_t i=0;i<edits.size();++i){if(i)out<<',';const auto &e=edits[i];out<<"{\"a_grid\":";point(e.a);out<<",\"removed_grid\":";point(e.v);out<<",\"b_grid\":";point(e.b);out<<",\"planes\":["<<e.right<<','<<e.left<<"],\"source_edge\":[";const auto &s=sourceEdges[e.source];out<<'['<<s.a.x<<','<<s.a.y<<','<<s.a.z<<"],["<<s.b.x<<','<<s.b.y<<','<<s.b.z<<"]]}";}out<<"]}\n";if(!out)throw std::runtime_error("Cannot save shared source contraction certificate");
    }
    std::cout<<"PLATEAU_SHARED_SOURCE_EDGES input_cells="<<input.size()<<" output_cells="<<result.size()<<" plane_groups="<<groups.size()<<" removed_nodes="<<edits.size()<<" fixed_outer_footprint=1 positive_coverage=PASS switched_vertical_bound_m=.00002 original_edge_distance_m=.00002\n";
    return result;
}
} // namespace dw::rockFormations::sharedSourceEdges
#endif
