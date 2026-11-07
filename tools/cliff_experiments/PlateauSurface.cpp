#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "FormationPrecision.hpp"
#include "PlateauRegion.hpp"
#include "raymath.h"
#include <algorithm>
#include <map>
#include <limits>
#include <stdexcept>
#include <numeric>
#include <set>

namespace dw::rockFormations {
long double signedColumnVolume(const Polygon &top,float bottom) {
    long double volume=0;
    for(size_t k=1;k+1<top.size();++k) {
        const auto a=top[0],b=top[k],c=top[k+1];
        const long double area=(static_cast<long double>(b.x)-a.x)*(static_cast<long double>(c.z)-a.z)-
                               (static_cast<long double>(b.z)-a.z)*(static_cast<long double>(c.x)-a.x);
        volume-=area*((static_cast<long double>(a.y)-bottom)+(static_cast<long double>(b.y)-bottom)+(static_cast<long double>(c.y)-bottom))/6;
    }
    return volume;
}
namespace {
constexpr float WeldTolerance=.00008f;
struct Vertices {
    float distanceTolerance;
    explicit Vertices(float tolerance=WeldTolerance):distanceTolerance(tolerance) {}
    std::vector<Vector3> points;
    std::map<std::array<int,3>,std::vector<size_t>> bins;
    size_t insert(Vector3 p) {
        std::array<int,3> cell{int(std::floor(p.x/distanceTolerance)),int(std::floor(p.y/distanceTolerance)),int(std::floor(p.z/distanceTolerance))};
        for(int z=-1;z<=1;++z) for(int y=-1;y<=1;++y) for(int x=-1;x<=1;++x) {
            auto found=bins.find({cell[0]+x,cell[1]+y,cell[2]+z});
            if(found==bins.end()) continue;
            for(auto id:found->second)
                if(distance(p,points[id])<distanceTolerance) return id;
        }
        size_t id=points.size(); points.push_back(p); bins[cell].push_back(id); return id;
    }
};
}
cliffOptions::Mesh weldSurface(const std::vector<Polygon> &polygons,float tolerance,bool preserveTriangles,bool triangulateConcave) {
    ConstructionTiming stageTiming("weld");
    Vertices vertices(tolerance);
    std::vector<std::vector<size_t>> boundaries;
    for(const auto &p:polygons) {
        std::vector<size_t> ids;
        for(auto v:p) {
            v=canonicalRenderPoint(v);
            auto id=vertices.insert(v);
            if(ids.empty() || ids.back()!=id) ids.push_back(id);
        }
        if(ids.size()>1 && ids.front()==ids.back()) ids.pop_back();
        if(ids.size()>=3) boundaries.push_back(std::move(ids));
    }
    // A separate metre-scale index accelerates segment searches. The fine
    // insertion bins above still decide canonical vertices; this index only
    // narrows candidates for the unchanged point-on-segment predicate.
    std::map<std::array<int,3>,std::vector<size_t>> segmentBins;
    const bool indexed=vertices.points.size()>=64;
    const bool verifyIndex=std::getenv("DW_CLIFF_VERIFY_WELD")!=nullptr;
    auto cell=[](float value){return int(std::floor(double(value)));};
    if(indexed)for(size_t i=0;i<vertices.points.size();++i) {
        const auto p=vertices.points[i];segmentBins[{cell(p.x),cell(p.y),cell(p.z)}].push_back(i);
    }
    cliffOptions::Mesh mesh;
    for(const auto &ids:boundaries) {
        std::vector<size_t> split;
        for(size_t k=0;k<ids.size();++k) {
            auto a=vertices.points[ids[k]],b=vertices.points[ids[(k+1)%ids.size()]];
            auto e=sub(b,a); float length=dot(e,e);
            std::vector<std::pair<float,size_t>> on{{0,ids[k]}};
            auto visit=[&](size_t i,auto &hits) {
                if(i==ids[k] || i==ids[(k+1)%ids.size()])return;
                float t=dot(sub(vertices.points[i],a),e)/length;
                if(t<=0 || t>=1)return;
                if(distance(vertices.points[i],add(a,mul(e,t)))<tolerance)hits.push_back({t,i});
            };
            // Include arithmetic roundoff as well as the original weld radius.
            const float scale=std::max({1.f,std::abs(a.x),std::abs(a.y),std::abs(a.z),std::abs(b.x),std::abs(b.y),std::abs(b.z)});
            const float padding=tolerance+8*std::numeric_limits<float>::epsilon()*scale;
            const std::array<int,3> lo{cell(std::min(a.x,b.x)-padding),cell(std::min(a.y,b.y)-padding),cell(std::min(a.z,b.z)-padding)},
                                    hi{cell(std::max(a.x,b.x)+padding),cell(std::max(a.y,b.y)+padding),cell(std::max(a.z,b.z)+padding)};
            const double cells=(double(hi[0])-lo[0]+1)*(double(hi[1])-lo[1]+1)*(double(hi[2])-lo[2]+1);
            if(indexed && cells<=64) {
                for(int z=lo[2];z<=hi[2];++z)for(int y=lo[1];y<=hi[1];++y)for(int x=lo[0];x<=hi[0];++x) {
                    const auto found=segmentBins.find({x,y,z});
                    if(found!=segmentBins.end())for(auto i:found->second)visit(i,on);
                }
            } else for(size_t i=0;i<vertices.points.size();++i)visit(i,on);
            std::sort(on.begin(),on.end());
            if(verifyIndex) {
                std::vector<std::pair<float,size_t>> reference{{0,ids[k]}};
                for(size_t i=0;i<vertices.points.size();++i)visit(i,reference);
                std::sort(reference.begin(),reference.end());
                if(on!=reference)throw std::runtime_error("Weld segment index missed a point-on-edge candidate");
            }
            for(auto [t,id]:on)
                if(split.empty() || split.back()!=id) split.push_back(id);
        }
        if(preserveTriangles && split.size()==3) {
            const auto a=vertices.points[split[0]],b=vertices.points[split[1]],c=vertices.points[split[2]];
            if(Vector3Length(Vector3CrossProduct(sub(b,a),sub(c,a)))>1e-9f) {
                mesh.faces.push_back({a,b,c});mesh.polygonEdges.push_back({a,b});mesh.polygonEdges.push_back({b,c});mesh.polygonEdges.push_back({c,a});
            }
            continue;
        }
        if(preserveTriangles && (triangulateConcave || std::getenv("DW_CLIFF_EAR_WELD"))) {
            // A split node can lie slightly off its source edge after float
            // quantization. The boundary can then be concave even when the
            // source polygon was convex; a centroid fan can fold outside it.
            // Ear clipping retains the actual shared boundary with no new
            // center, and works for vertical faces through dominant projection.
            std::array<double,3> normal{};
            const auto origin=vertices.points[ids[0]];
            for(size_t k=1;k+1<ids.size();++k) {
                const auto a=sub(vertices.points[ids[k]],origin),b=sub(vertices.points[ids[k+1]],origin);
                normal[0]+=double(a.y)*b.z-double(a.z)*b.y;
                normal[1]+=double(a.z)*b.x-double(a.x)*b.z;
                normal[2]+=double(a.x)*b.y-double(a.y)*b.x;
            }
            const auto axis=size_t(std::max_element(normal.begin(),normal.end(),[](double a,double b){return std::abs(a)<std::abs(b);})-normal.begin());
            auto coordinate=[](Vector3 p,size_t k){return k==0?p.x:k==1?p.y:p.z;};
            const auto u=(axis+1)%3,v=(axis+2)%3;
            Polygon projected;std::map<std::pair<float,float>,Vector3> originals;
            for(auto id:split) {
                const auto p=vertices.points[id];const float x=coordinate(p,u),z=coordinate(p,v);
                projected.push_back({x,0,z});originals.emplace(std::pair{x,z},p);
            }
            double area=0;for(size_t k=0;k<projected.size();++k)area+=double(projected[k].x)*projected[(k+1)%projected.size()].z-double(projected[k].z)*projected[(k+1)%projected.size()].x;
            std::vector<cliffOptions::Triangle> ears;
            try{ears=triangulatePlateauBoundary(projected,true);}catch(const std::runtime_error &){}
            for(const auto &f:ears) {
                cliffOptions::Triangle triangle;
                for(int k=0;k<3;++k)triangle[k]=originals.at({f[k].x,f[k].z});
                if(area>0)std::swap(triangle[1],triangle[2]);
                mesh.faces.push_back(triangle);
            }
            if(!ears.empty()) {
                for(size_t k=0;k<split.size();++k)mesh.polygonEdges.push_back({vertices.points[split[k]],vertices.points[split[(k+1)%split.size()]]});
                continue;
            }
            // Approximate edge splits can also produce a self-crossing or
            // numerically collapsed loop. Keep the existing fan candidate in
            // that case; it still has to pass the full emitted-mesh audit.
        }
        Vector3 center{};
        for(auto id:ids) center=add(center,vertices.points[id]);
        center=canonicalRenderPoint(mul(center,1.f/ids.size()));
        // A center fan preserves every split boundary segment, including
        // collinear vertices that an ordinary corner fan can skip.
        for(size_t i=0;i<split.size();++i) {
            auto a=vertices.points[split[i]],b=vertices.points[split[(i+1)%split.size()]];
            if(Vector3Length(Vector3CrossProduct(sub(a,center),sub(b,center)))<1e-9f) continue;
            mesh.faces.push_back({center,a,b});
            mesh.polygonEdges.push_back({a,b});
        }
    }
    // CSG's classification epsilon can leave coincident copies which become
    // identical after welding. Keep one outward copy, cancel opposite internal
    // copies, and do not emit triangles collapsed by the weld itself.
    Vertices canonical(tolerance);
    struct Copies { int positive=0,negative=0; cliffOptions::Triangle plus{},minus{}; };
    std::map<std::array<size_t,3>,Copies> unique;
    for(const auto &f:mesh.faces) {
        std::array<size_t,3> ids;
        for(int k=0;k<3;++k) ids[k]=canonical.insert(f[k]);
        auto sorted=ids; std::sort(sorted.begin(),sorted.end());
        if(sorted[0]==sorted[1] || sorted[1]==sorted[2]) continue;
        int inversions=0;
        for(int i=0;i<3;++i) for(int j=i+1;j<3;++j) inversions+=ids[i]>ids[j];
        auto &copies=unique[sorted];
        auto snapped=f;
        for(int k=0;k<3;++k) snapped[k]=canonical.points[ids[k]];
        if(inversions%2) {++copies.negative;copies.minus=snapped;}
        else {++copies.positive;copies.plus=snapped;}
    }
    mesh.faces.clear();
    for(const auto &[key,copies]:unique) {
        if(copies.positive>copies.negative) mesh.faces.push_back(copies.plus);
        if(copies.negative>copies.positive) mesh.faces.push_back(copies.minus);
    }
    return mesh;
}
SurfaceAudit auditSurface(const cliffOptions::Mesh &mesh) {
    SurfaceAudit audit;
    Vertices vertices;
    std::map<std::pair<size_t,size_t>,std::vector<size_t>> edges;
    std::map<std::pair<size_t,size_t>,int> direction;
    std::set<std::array<size_t,3>> faces;
    std::vector<size_t> parents(mesh.faces.size());
    std::iota(parents.begin(),parents.end(),0);
    auto root=[&](size_t i) {
        while(parents[i]!=i) { parents[i]=parents[parents[i]]; i=parents[i]; }
        return i;
    };
    for(size_t f=0;f<mesh.faces.size();++f) {
        std::array<size_t,3> ids;
        for(int k=0;k<3;++k) ids[k]=vertices.insert(mesh.faces[f][k]);
        auto sorted=ids; std::sort(sorted.begin(),sorted.end());
        if(sorted[0]==sorted[1] || sorted[1]==sorted[2]) ++audit.degenerateFaces;
        if(!faces.insert(sorted).second) ++audit.duplicateFaces;
        for(int k=0;k<3;++k) {
            auto a=ids[k],b=ids[(k+1)%3];
            const int sign=a<b ? 1 : -1;
            if(a>b) std::swap(a,b);
            edges[{a,b}].push_back(f);
            direction[{a,b}]+=sign;
        }
    }
    for(const auto &[edge,adjacent]:edges) {
        if(adjacent.size()==1) ++audit.boundaryEdges;
        if(adjacent.size()>2) ++audit.nonmanifoldEdges;
        if(adjacent.size()==2 && direction[edge]!=0) ++audit.windingErrors;
        for(size_t k=1;k<adjacent.size();++k) parents[root(adjacent[k])]=root(adjacent[0]);
    }
    std::set<size_t> roots;
    for(size_t f=0;f<mesh.faces.size();++f) roots.insert(root(f));
    audit.vertices=vertices.points.size(); audit.components=roots.size(); return audit;
}
std::vector<std::array<Vector3,2>> surfaceBoundary(const cliffOptions::Mesh &mesh, bool directed) {
    std::map<std::array<float,3>,size_t> idsByPoint;
    std::vector<Vector3> points;
    auto insert=[&](Vector3 p) {
        auto [it,added]=idsByPoint.emplace(std::array{p.x,p.y,p.z},points.size());
        if(added)points.push_back(p);
        return it->second;
    };
    std::map<std::pair<size_t,size_t>,size_t> edges;
    std::map<std::pair<size_t,size_t>,std::pair<size_t,size_t>> oriented;
    for(const auto &f:mesh.faces) {
        std::array<size_t,3> ids;
        for(int k=0;k<3;++k) ids[k]=insert(f[k]);
        for(int k=0;k<3;++k) {
            auto a=ids[k],b=ids[(k+1)%3];
            const auto original=std::pair{a,b};
            if(a>b) std::swap(a,b);
            ++edges[{a,b}];
            oriented[{a,b}]=original;
        }
    }
    std::vector<std::array<Vector3,2>> boundary;
    for(auto [edge,count]:edges)
        if(count==1) {
            const auto ids=directed ? oriented[edge] : edge;
            boundary.push_back({points[ids.first],points[ids.second]});
        }
    return boundary;
}
} // namespace dw::rockFormations

namespace dw::rockFormations {
namespace {
cliffOptions::Mesh simplifyRoofInterior(const cliffOptions::Mesh &mesh) {
    ConstructionChecks constructiveChecks;
    const auto initial=auditStrictSurface(mesh);
    auto invalid=[](const StrictSurfaceAudit &a){return a.exact.boundaryEdges || a.exact.nonmanifoldEdges || a.nonmanifoldVertices || a.selfIntersections || a.coplanarOverlaps || a.exact.degenerateFaces || a.exact.duplicateFaces || a.exact.windingErrors;};
    if(invalid(initial)) {
        std::cout<<"PLATEAU_SIMPLIFY_INPUT_REJECT open="<<initial.exact.boundaryEdges<<" nonmanifold="<<initial.exact.nonmanifoldEdges
                 <<" links="<<initial.nonmanifoldVertices<<" crossings="<<initial.selfIntersections<<" overlaps="<<initial.coplanarOverlaps
                 <<" degenerate="<<initial.exact.degenerateFaces<<" winding="<<initial.exact.windingErrors<<'\n';
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE"))writeSurfaceProbe(path,mesh,{},initial);
        throw std::runtime_error("Cannot simplify an invalid plateau shell");
    }
    using Key=std::array<float,3>;using Face=std::array<size_t,3>;
    std::map<Key,size_t> ids;std::vector<Vector3> points;std::vector<Face> faces;
    for(const auto &f:mesh.faces) {
        Face face{};for(int k=0;k<3;++k) {
            const auto p=f[k];auto [it,added]=ids.emplace(Key{p.x,p.y,p.z},points.size());
            if(added)points.push_back(p);face[k]=it->second;
        }faces.push_back(face);
    }
    std::map<std::pair<size_t,size_t>,size_t> edges;
    for(auto f:faces)for(int k=0;k<3;++k){auto a=f[k],b=f[(k+1)%3];if(b<a)std::swap(a,b);++edges[{a,b}];}
    std::vector<bool> boundary(points.size());
    for(const auto &[edge,count]:edges)if(count!=2){boundary[edge.first]=true;boundary[edge.second]=true;}
    for(size_t vertex=0;vertex<points.size();++vertex) {
        if(boundary[vertex])continue;
        std::vector<size_t> incident;std::map<size_t,size_t> next;bool valid=true;
        for(size_t i=0;i<faces.size();++i)for(int k=0;k<3;++k)if(faces[i][k]==vertex) {
            incident.push_back(i);valid &= next.emplace(faces[i][(k+1)%3],faces[i][(k+2)%3]).second;
        }
        if(!valid || incident.size()<3 || next.size()!=incident.size())continue;
        Polygon loop;std::set<size_t> used;auto at=next.begin()->first;
        for(size_t k=0;k<next.size();++k) {
            if(!used.insert(at).second || !next.contains(at)){valid=false;break;}
            loop.push_back(points[at]);at=next[at];
        }
        if(!valid || at!=next.begin()->first || used.size()!=next.size())continue;
        size_t reference=incident[0];
        if(std::getenv("DW_CLIFF_ROOF_CHUNKS")) {
            auto areaSquared=[&](size_t id) {
                const auto f=faces[id];const auto a=sub(points[f[1]],points[f[0]]),b=sub(points[f[2]],points[f[0]]);
                const double x=double(a.y)*b.z-double(a.z)*b.y,y=double(a.z)*b.x-double(a.x)*b.z,z=double(a.x)*b.y-double(a.y)*b.x;
                return x*x+y*y+z*z;
            };
            for(auto i:incident)if(areaSquared(i)>areaSquared(reference))reference=i;
        }
        const auto first=faces[reference];const auto origin=points[first[0]];
        const auto a=sub(points[first[1]],origin),b=sub(points[first[2]],origin);
        std::array<double,3> n{double(a.y)*b.z-double(a.z)*b.y,double(a.z)*b.x-double(a.x)*b.z,double(a.x)*b.y-double(a.y)*b.x};
        const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);if(length<1e-14 || std::abs(n[1])/length<.1)continue;
        for(auto q:loop)if(std::abs(n[0]*(double(q.x)-origin.x)+n[1]*(double(q.y)-origin.y)+n[2]*(double(q.z)-origin.z))>length*.000001){valid=false;break;}
        if(!valid)continue;
        std::vector<cliffOptions::Triangle> replacement;
        try{replacement=triangulatePlateauBoundary(loop,true);}catch(const std::exception &){continue;}
        if(replacement.size()>=incident.size())continue;
        if(n[1]<0)for(auto &f:replacement)std::swap(f[1],f[2]);
        std::vector<Face> converted;std::set<size_t> retained;
        for(const auto &f:replacement) {
            Face face{};for(int k=0;k<3;++k){const auto p=f[k];face[k]=ids.at(Key{p.x,p.y,p.z});retained.insert(face[k]);}converted.push_back(face);
        }
        if(retained!=used)continue; // Never lose a split boundary vertex.
        std::vector<Face> remaining;remaining.reserve(faces.size());size_t cursor=0;
        for(size_t i=0;i<faces.size();++i) {
            if(cursor<incident.size() && incident[cursor]==i){++cursor;continue;}
            remaining.push_back(faces[i]);
        }
        const size_t firstChanged=remaining.size();
        remaining.insert(remaining.end(),converted.begin(),converted.end());
        cliffOptions::Mesh candidate;
        for(auto f:remaining)candidate.faces.push_back({points[f[0]],points[f[1]],points[f[2]]});
        cliffOptions::Mesh patch;for(auto f:converted)patch.faces.push_back({points[f[0]],points[f[1]],points[f[2]]});
        const auto local=auditStrictSurface(patch);
        std::set<std::pair<size_t,size_t>> actualBoundary,expectedBoundary(next.begin(),next.end());
        for(auto edge:surfaceBoundary(patch,true))actualBoundary.emplace(ids.at(Key{edge[0].x,edge[0].y,edge[0].z}),ids.at(Key{edge[1].x,edge[1].y,edge[1].z}));
        const bool disk=local.exact.boundaryEdges==next.size() && actualBoundary==expectedBoundary && local.exact.components==1 &&
            !local.exact.nonmanifoldEdges && !local.nonmanifoldVertices && !local.selfIntersections && !local.coplanarOverlaps &&
            !local.exact.degenerateFaces && !local.exact.duplicateFaces && !local.exact.windingErrors;
        const bool safe=disk && !replacementIntersects(candidate,firstChanged);
        if(std::getenv("DW_CLIFF_VERIFY_SIMPLIFIER")) {
            const auto full=auditSurfaceReplacement(candidate,firstChanged);
            const bool reference=!invalid(full) && full.exact.components==initial.exact.components;
            if(safe!=reference)throw std::runtime_error("Local simplifier proof differs from the full mesh verifier");
        }
        if(!safe)continue;
        faces=std::move(remaining);
    }
    if(std::getenv("DW_CLIFF_VERIFY_SIMPLIFIER"))std::cout<<"PLATEAU_SIMPLIFIER_ORACLE identical_decisions=PASS\n";
    auto result=mesh;result.faces.clear();
    for(auto f:faces)result.faces.push_back({points[f[0]],points[f[1]],points[f[2]]});return result;
}
}
cliffOptions::Mesh simplifyPlateauSurface(const cliffOptions::Mesh &mesh) {return simplifyRoofInterior(mesh);}
std::vector<cliffOptions::Mesh> splitSurfaceComponents(const cliffOptions::Mesh &mesh) {
    using Key=std::array<float,3>;std::map<Key,size_t> ids;
    std::map<std::pair<size_t,size_t>,size_t> owner;
    std::vector<size_t> parent(mesh.faces.size());std::iota(parent.begin(),parent.end(),0);
    auto root=[&](size_t i){while(parent[i]!=i){parent[i]=parent[parent[i]];i=parent[i];}return i;};
    for(size_t i=0;i<mesh.faces.size();++i) {
        std::array<size_t,3> vertices;
        for(int k=0;k<3;++k){auto p=mesh.faces[i][k];vertices[k]=ids.emplace(Key{p.x,p.y,p.z},ids.size()).first->second;}
        for(int k=0;k<3;++k) {
            auto a=vertices[k],b=vertices[(k+1)%3];if(b<a)std::swap(a,b);
            auto [at,added]=owner.emplace(std::pair{a,b},i);
            if(!added){auto u=root(i),v=root(at->second);parent[std::max(u,v)]=std::min(u,v);}
        }
    }
    std::map<size_t,cliffOptions::Mesh> groups;
    for(size_t i=0;i<mesh.faces.size();++i)groups[root(i)].faces.push_back(mesh.faces[i]);
    std::vector<cliffOptions::Mesh> result;for(auto &[id,group]:groups)result.push_back(std::move(group));return result;
}
std::vector<cliffOptions::Mesh> meshPlateauRegionBodies(const std::vector<Volume> &bodies) {
    std::vector<Polygon> domains;for(const auto &body:bodies)domains.push_back(body.faces.front());
    const auto flat=std::getenv("DW_CLIFF_ROOF_ARRANGEMENT")?arrangePlateauFootprint(domains):meshPlateauFootprint(domains);
    const auto components=splitSurfaceComponents(flat);
    std::vector<std::vector<Volume>> pieces(components.size());
    for(const auto &body:bodies) {
        double x=0,z=0;for(auto p:body.faces.front()){x+=p.x;z+=p.z;}x/=body.faces.front().size();z/=body.faces.front().size();
        size_t owner=components.size();
        for(size_t i=0;i<components.size() && owner==components.size();++i)for(const auto &f:components[i].faces) {
            bool inside=true;
            for(int k=0;k<3;++k){const auto a=f[k],b=f[(k+1)%3];if((double(b.x)-a.x)*(z-a.z)-(double(b.z)-a.z)*(x-a.x)>0){inside=false;break;}}
            if(inside){owner=i;break;}
        }
        if(owner==components.size())throw std::runtime_error("Cannot assign a regional roof prism to its edge component");
        pieces[owner].push_back(body);
    }
    std::vector<cliffOptions::Mesh> result;
    for(const auto &piece:pieces)if(!piece.empty())result.push_back(meshPlateauBody(piece));
    std::cout<<"PLATEAU_REGION_BODY_PARTS count="<<result.size()<<" prisms="<<bodies.size()<<" individually_closed=PASS\n";
    return result;
}
static size_t splitRoofJumps(cliffOptions::Mesh &mesh,float tolerance) {
    using Point=std::array<float,2>;using Edge=std::pair<Point,Point>;
    auto point=[](Vector3 p){return Point{p.x,p.z};};
    size_t changes=0;const size_t limit=mesh.faces.size()*6+1;
    while(changes<limit) {
        struct Owner{size_t face;int edge;};std::map<Edge,std::vector<Owner>> owners;
        for(size_t i=0;i<mesh.faces.size();++i)for(int k=0;k<3;++k){auto a=point(mesh.faces[i][k]),b=point(mesh.faces[i][(k+1)%3]);if(b<a)std::swap(a,b);owners[{a,b}].push_back({i,k});}
        bool found=false;
        for(const auto &[key,uses]:owners)if(uses.size()==2) {
            const auto f=mesh.faces[uses[0].face],g=mesh.faces[uses[1].face];const auto a=f[uses[0].edge],b=f[(uses[0].edge+1)%3];
            const auto u=point(g[uses[1].edge])==point(a)?g[uses[1].edge]:g[(uses[1].edge+1)%3];
            const auto v=point(g[uses[1].edge])==point(b)?g[uses[1].edge]:g[(uses[1].edge+1)%3];
            const double da=double(a.y)-u.y,db=double(b.y)-v.y;if(da*db>=0)continue;
            const double t=da/(da-db);
            auto p=canonicalRenderPoint({float(a.x+(double(b.x)-a.x)*t),0,float(a.z+(double(b.z)-a.z)*t)});
            if(point(p)==point(a) || point(p)==point(b)) {
                const auto old=point(p)==point(a)?a:b,other=point(p)==point(a)?u:v;
                const float y=float((double(old.y)+other.y)*.5);
                if(std::abs(double(y)-old.y)>tolerance || std::abs(double(y)-other.y)>tolerance)
                    throw std::runtime_error("Unrepresentable roof crossing exceeds the construction weld radius");
                for(auto &tri:mesh.faces)for(auto &q:tri)if(point(q)==point(p) && (q.y==old.y || q.y==other.y))q.y=y;
            } else {
                const double dx=double(b.x)-a.x,dz=double(b.z)-a.z;
                const double at=((double(p.x)-a.x)*dx+(double(p.z)-a.z)*dz)/(dx*dx+dz*dz);
                p.y=float((a.y+at*(double(b.y)-a.y)+u.y+at*(double(v.y)-u.y))*.5);
                for(auto owner:uses) {
                    const auto old=mesh.faces[owner.face];const auto x=old[owner.edge],y=old[(owner.edge+1)%3],z=old[(owner.edge+2)%3];
                    auto valid=[](Vector3 a,Vector3 b,Vector3 c){return (double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x)<0;};
                    if(!valid(x,p,z) || !valid(p,y,z))throw std::runtime_error("Roof crossing has no representable positive-area split");
                    mesh.faces[owner.face]={x,p,z};mesh.faces.push_back({p,y,z});
                }
            }
            ++changes;found=true;break;
        }
        if(!found)return changes;
    }
    throw std::runtime_error("Roof crossing split did not converge");
}
cliffOptions::Mesh meshPlateauBody(const std::vector<Volume> &bodies,float bottom,float tolerance,bool splitCrossings) {
    std::vector<Polygon> footprint;
    for(const auto &v:bodies) {
        if(v.faces.empty() || v.planes.empty())throw std::runtime_error("Missing plateau prism roof");
        auto p=v.faces.front();for(auto &q:p)q.y=0;footprint.push_back(std::move(p));
    }
    auto planar=std::getenv("DW_CLIFF_ROOF_ARRANGEMENT")?arrangePlateauFootprint(footprint,tolerance):
        std::getenv("DW_CLIFF_ROOF_REGION")?meshPlateauFootprint(footprint):weldSurface(footprint,tolerance,true);
    using Point=std::array<float,2>;
    using Edge=std::pair<Point,Point>;
    std::map<Point,std::vector<float>> levels;size_t fallback=0;
    auto point=[](Vector3 p){return Point{p.x,p.z};};
    auto level=[&](Vector3 p,float height) {
        auto &values=levels[point(p)];
        for(auto y:values)if(std::abs(y-height)<tolerance){p.y=y;return p;}
        values.push_back(height);p.y=height;return p;
    };
    auto roofAt=[&](std::array<double,3> p) -> const Plane & {
        size_t selected=bodies.size();float height=-1e9f;
        for(double margin:{0.,.00002,.00004}) {
            for(size_t i=0;i<bodies.size();++i) {
                bool inside=true;
                for(const auto &plane:bodies[i].planes)if(std::abs(planeNormal(plane)[1])<1e-12){const auto n=planeNormal(plane);if(n[0]*p[0]+n[1]*p[1]+n[2]*p[2]>plane.distance+margin){inside=false;break;}}
                if(!inside)continue;
                const auto n=planeNormal(bodies[i].planes.front());
                const float y=float((bodies[i].planes.front().distance-n[0]*p[0]-n[2]*p[2])/n[1]);
                if(y>height){height=y;selected=i;}
            }
            if(selected<bodies.size()){fallback+=margin>0;break;}
        }
        if(selected==bodies.size() || height<=bottom)throw std::runtime_error("Cannot locate a plateau roof triangle");
        return bodies[selected].planes.front();
    };
    cliffOptions::Mesh shell,roofMesh;
    std::map<Edge,std::vector<std::array<Vector3,2>>> sides;
    const bool sourcePlanes=std::getenv("DW_CLIFF_CHUNK_SOURCE_PLANES")!=nullptr;
    for(const auto &f:planar.faces) {
        const auto legacyCenter=mul(add(add(f[0],f[1]),f[2]),1.f/3);
        // A float centroid can round outside a thin but finite source cell.
        // Keep its query in double; emitted mesh coordinates remain floats.
        const std::array<double,3> center=sourcePlanes?
            std::array<double,3>{(double(f[0].x)+f[1].x+f[2].x)/3,0,(double(f[0].z)+f[1].z+f[2].z)/3}:
            std::array<double,3>{legacyCenter.x,legacyCenter.y,legacyCenter.z};
        const auto &roof=roofAt(center);const auto n=planeNormal(roof);auto top=f;
        for(auto &p:top)p=level(p,float((roof.distance-n[0]*p.x-n[2]*p.z)/n[1]));
        roofMesh.faces.push_back(top);
        for(int k=0;k<3;++k) {
            const auto a=top[k],b=top[(k+1)%3];auto u=point(a),v=point(b);if(v<u)std::swap(u,v);
            sides[{u,v}].push_back({a,b});
        }
    }
    if(splitCrossings || std::getenv("DW_CLIFF_ROOF_CHUNKS")) {
        const auto count=splitRoofJumps(roofMesh,tolerance);
        if(count)std::cout<<"PLATEAU_ROOF_CROSSINGS split_or_collapsed="<<count<<" maximum_vertex_weld_radius="<<tolerance<<'\n';
        sides.clear();levels.clear();
        for(const auto &f:roofMesh.faces) {
            for(auto p:f){auto &ys=levels[point(p)];if(std::find(ys.begin(),ys.end(),p.y)==ys.end())ys.push_back(p.y);}
            for(int k=0;k<3;++k){auto a=f[k],b=f[(k+1)%3];auto u=point(a),v=point(b);if(v<u)std::swap(u,v);sides[{u,v}].push_back({a,b});}
        }
    }
    auto foundation=roofMesh;
    shell.faces=roofMesh.faces;
    for(auto f:foundation.faces){for(auto &p:f)p.y=bottom;shell.faces.push_back({f[2],f[1],f[0]});}
    auto wall=[&](Vector3 a,Vector3 b,Vector3 loA,Vector3 loB) {
        if(a.y==loA.y && b.y==loB.y)return;
        std::vector<float> left{a.y},right{b.y};
        for(auto y:levels[point(a)])if(y<a.y && y>loA.y)left.push_back(y);
        for(auto y:levels[point(b)])if(y<b.y && y>loB.y)right.push_back(y);
        if(loA.y!=a.y)left.push_back(loA.y);if(loB.y!=b.y)right.push_back(loB.y);
        std::sort(left.begin(),left.end(),std::greater<float>());std::sort(right.begin(),right.end(),std::greater<float>());
        size_t i=0,j=0;
        while(i+1<left.size() || j+1<right.size()) {
            const Vector3 u{a.x,left[i],a.z},v{b.x,right[j],b.z};cliffOptions::Triangle triangle;
            if(i+1<left.size() && (j+1==right.size() || left[i+1]>=right[j+1]))triangle={u,Vector3{a.x,left[++i],a.z},v};
            else triangle={u,Vector3{b.x,right[++j],b.z},v};
            if(Vector3Length(Vector3CrossProduct(sub(triangle[1],triangle[0]),sub(triangle[2],triangle[0])))>1e-14f)shell.faces.push_back(triangle);
        }
    };
    for(const auto &[key,edges]:sides) {
        if(edges.size()==1) {
            auto loA=edges[0][0],loB=edges[0][1];loA.y=loB.y=bottom;wall(edges[0][0],edges[0][1],loA,loB);
        } else if(edges.size()==2) {
            const auto a=edges[0][0],b=edges[0][1];
            const auto otherA=point(edges[1][0])==point(a)?edges[1][0]:edges[1][1];
            const auto otherB=point(edges[1][0])==point(b)?edges[1][0]:edges[1][1];
            const double da=double(a.y)-otherA.y,db=double(b.y)-otherB.y;
            if((da<0 && db>0) || (da>0 && db<0))throw std::runtime_error("A roof jump crosses its shared edge");
            if(da>=0 && db>=0)wall(a,b,otherA,otherB);
            else wall(edges[1][0],edges[1][1],point(edges[1][0])==point(a)?a:b,point(edges[1][1])==point(a)?a:b);
        } else {
            if(std::getenv("DW_CLIFF_ROOF_CHUNKS")) {
                std::cout<<"PLATEAU_CHUNK_EDGE_REJECT a="<<key.first[0]<<','<<key.first[1]<<" b="<<key.second[0]<<','<<key.second[1]<<" owners="<<edges.size();
                for(auto e:edges)std::cout<<" heights="<<e[0].y<<','<<e[1].y;
                std::cout<<'\n';
                if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE"))writeSurfaceProbe(path,roofMesh,bodies,auditStrictSurface(roofMesh));
            }
            throw std::runtime_error("Planar roof partition has a nonmanifold edge");
        }
    }
    const auto sourceTriangles=shell.faces.size();
    if(std::getenv("DW_CLIFF_ROOF_CHUNKS")) {
        const auto a=auditStrictSurface(planar).exact,b=auditStrictSurface(roofMesh).exact;
        std::cout<<"PLATEAU_ARRANGEMENT_TOPOLOGY planar_faces="<<planar.faces.size()<<" planar_nonmanifold="<<a.nonmanifoldEdges
                 <<" planar_open="<<a.boundaryEdges<<" roof_nonmanifold="<<b.nonmanifoldEdges<<" roof_open="<<b.boundaryEdges<<std::endl;
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE"))writeSurfaceProbe(path,shell,bodies,auditStrictSurface(shell));
    }
    shell=simplifyRoofInterior(shell);
    std::cout<<"PLATEAU_SHELL_SIMPLIFY before="<<sourceTriangles<<" after="<<shell.faces.size()<<" checked_replacements=PASS\n";
    const auto strict=auditStrictSurface(shell);
    std::cout<<"PLATEAU_SHELL_EXACT open="<<strict.exact.boundaryEdges<<" nonmanifold="<<strict.exact.nonmanifoldEdges<<" links="<<strict.nonmanifoldVertices<<" crossings="<<strict.selfIntersections<<" overlaps="<<strict.coplanarOverlaps<<" degenerate="<<strict.exact.degenerateFaces<<" winding="<<strict.exact.windingErrors<<'\n';
    if(strict.exact.boundaryEdges || strict.exact.nonmanifoldEdges || strict.nonmanifoldVertices || strict.selfIntersections ||
       strict.coplanarOverlaps || strict.exact.degenerateFaces || strict.exact.duplicateFaces || strict.exact.windingErrors)
        throw std::runtime_error("Plateau height-field shell fails exact closure");
    const auto coverage=auditBoundaryCoverage(shell,bodies);
    std::cout<<"PLATEAU_SHELL_SOURCE buried="<<coverage.buriedFragments<<" detached="<<coverage.detachedFragments<<'\n';
    if(coverage.buriedFragments || coverage.detachedFragments)throw std::runtime_error("Plateau shell leaves the source prism boundary");
    size_t topCount=0,bottomCount=0;
    for(const auto &f:shell.faces){topCount+=Vector3CrossProduct(sub(f[1],f[0]),sub(f[2],f[0])).y>0;bottomCount+=f[0].y==bottom && f[1].y==bottom && f[2].y==bottom;}
    std::cout<<"PLATEAU_BODY_SHELL prisms="<<bodies.size()<<" source_top_triangles="<<planar.faces.size()<<" top_triangles="<<topCount<<" bottom_triangles="<<bottomCount<<" shell_triangles="<<shell.faces.size()<<" projected_fallbacks="<<fallback<<" exact_checks=PASS source_boundary=PASS\n";
    return shell;
}
}
