#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "PlateauExactContact.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <array>
#include <cmath>
#include <map>
#include <numeric>
#include <set>

namespace dw::rockFormations {
namespace {
constexpr double Eps=1e-8;
struct D {
    double x=0,y=0,z=0;
    D operator+(D b)const{return {x+b.x,y+b.y,z+b.z};}
    D operator-(D b)const{return {x-b.x,y-b.y,z-b.z};}
    D operator*(double s)const{return {x*s,y*s,z*s};}
};
D d(Vector3 p){return {p.x,p.y,p.z};}
double dot(D a,D b){return a.x*b.x+a.y*b.y+a.z*b.z;}
D cross(D a,D b){return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
double length(D a){return std::sqrt(dot(a,a));}
struct Triangle {
    std::array<D,3> p;
    std::array<size_t,3> ids;
    D normal,lo,hi;
};
bool inside(D p,const Triangle &t) {
    for(int k=0;k<3;++k) {
        const auto e=t.p[(k+1)%3]-t.p[k];
        if(dot(t.normal,cross(e,p-t.p[k])) < -Eps*length(e)) return false;
    }
    return true;
}
bool legitimate(D p,const std::vector<D> &common) {
    for(auto q:common) if(length(p-q)<Eps*4) return true;
    if(common.size()>=2) {
        const auto e=common[1]-common[0];
        const auto t=std::clamp(dot(p-common[0],e)/dot(e,e),0.,1.);
        if(length(p-(common[0]+e*t))<Eps*4) return true;
    }
    return false;
}
struct P {double x,y;};
double turn(P a,P b,P c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
bool coplanarOverlap(const Triangle &a,const Triangle &b) {
    const auto n=a.normal;
    const int axis=std::abs(n.x)>std::abs(n.y) ? (std::abs(n.x)>std::abs(n.z)?0:2) : (std::abs(n.y)>std::abs(n.z)?1:2);
    auto project=[&](D p){p=p-a.p[0];return axis==0 ? P{p.y,p.z} : axis==1 ? P{p.x,p.z} : P{p.x,p.y};};
    std::vector<P> polygon{project(a.p[0]),project(a.p[1]),project(a.p[2])};
    const std::array<P,3> clip{project(b.p[0]),project(b.p[1]),project(b.p[2])};
    const double sign=turn(clip[0],clip[1],clip[2])>=0?1:-1;
    for(int k=0;k<3 && !polygon.empty();++k) {
        std::vector<P> result;
        for(size_t i=0;i<polygon.size();++i) {
            const auto p=polygon[i],q=polygon[(i+1)%polygon.size()];
            const double u=sign*turn(clip[k],clip[(k+1)%3],p),v=sign*turn(clip[k],clip[(k+1)%3],q);
            if(u>=0) result.push_back(p);
            if((u<0 && v>0)||(u>0 && v<0)) {const double t=u/(u-v);result.push_back({p.x+(q.x-p.x)*t,p.y+(q.y-p.y)*t});}
        }
        polygon=std::move(result);
    }
    double area=0;
    for(size_t i=0;i<polygon.size();++i) area+=polygon[i].x*polygon[(i+1)%polygon.size()].y-polygon[i].y*polygon[(i+1)%polygon.size()].x;
    return std::abs(area)>.000000000002;
}
int intersection(const Triangle &a,const Triangle &b) {
    std::vector<D> common;
    for(int i=0;i<3;++i) for(int j=0;j<3;++j) if(a.ids[i]==b.ids[j]) common.push_back(a.p[i]);
    std::array<double,3> da,db;
    for(int i=0;i<3;++i) {da[i]=dot(b.normal,a.p[i]-b.p[0]);db[i]=dot(a.normal,b.p[i]-a.p[0]);}
    auto separated=[](const auto &v){return std::all_of(v.begin(),v.end(),[](double x){return x>Eps;}) || std::all_of(v.begin(),v.end(),[](double x){return x< -Eps;});};
    if(separated(da)||separated(db)) return 0;
    const bool coplanar=std::all_of(da.begin(),da.end(),[](double x){return std::abs(x)<Eps;}) &&
                         std::all_of(db.begin(),db.end(),[](double x){return std::abs(x)<Eps;});
    if(coplanar) return coplanarOverlap(a,b)?2:0;
    if(common.size()>=2) return 0; // Noncoplanar adjacent faces meet on their shared edge only.
    auto crosses=[&](const Triangle &from,const Triangle &to,const std::array<double,3> &distances) {
        for(int i=0;i<3;++i) {
            const int j=(i+1)%3;
            if(std::abs(distances[i])<Eps && inside(from.p[i],to) && !legitimate(from.p[i],common)) return true;
            if((distances[i]<-Eps && distances[j]>Eps)||(distances[i]>Eps && distances[j]<-Eps)) {
                const auto p=from.p[i]+(from.p[j]-from.p[i])*(distances[i]/(distances[i]-distances[j]));
                if(inside(p,to) && !legitimate(p,common)) return true;
            }
        }
        return false;
    };
    return crosses(a,b,da)||crosses(b,a,db)?1:0;
}
}
static StrictSurfaceAudit strictSurface(const cliffOptions::Mesh &mesh,size_t firstChangedTriangle) {
    ValidationTiming measured;
    StrictSurfaceAudit audit;
    std::map<std::array<float,3>,size_t> vertices;
    std::map<std::pair<size_t,size_t>,std::vector<std::pair<size_t,int>>> edges;
    std::set<std::array<size_t,3>> faces;
    std::vector<Triangle> triangles;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    const bool exactContacts=std::getenv("DW_CLIFF_EXACT_CONTACTS")!=nullptr;
    std::vector<exactContact::Triangle> exactTriangles;
    if(exactContacts){exactTriangles.reserve(mesh.faces.size());for(const auto &face:mesh.faces)exactTriangles.emplace_back(face);}
#else
    if(std::getenv("DW_CLIFF_EXACT_CONTACTS"))throw std::runtime_error("Exact contact audit requires the boolean experiment");
#endif
    std::vector<std::map<size_t,std::set<size_t>>> links;
    audit.minimumArea=mesh.faces.empty()?0:1e99;
    for(size_t f=0;f<mesh.faces.size();++f) {
        Triangle t;
        for(int k=0;k<3;++k) {
            auto p=mesh.faces[f][k];const std::array<float,3> key{p.x,p.y,p.z};
            auto [it,added]=vertices.try_emplace(key,vertices.size());if(added) links.emplace_back();
            t.ids[k]=it->second;t.p[k]=d(p);
        }
        t.normal=cross(t.p[1]-t.p[0],t.p[2]-t.p[0]);const double twiceArea=length(t.normal);
        audit.minimumArea=std::min(audit.minimumArea,twiceArea*.5);
        if(twiceArea<1e-14) ++audit.exact.degenerateFaces;
        if(twiceArea>0) t.normal=t.normal*(1/twiceArea);
        t.lo=t.hi=t.p[0];
        for(auto p:t.p) {t.lo={std::min(t.lo.x,p.x),std::min(t.lo.y,p.y),std::min(t.lo.z,p.z)};t.hi={std::max(t.hi.x,p.x),std::max(t.hi.y,p.y),std::max(t.hi.z,p.z)};}
        auto sorted=t.ids;std::sort(sorted.begin(),sorted.end());if(!faces.insert(sorted).second) ++audit.exact.duplicateFaces;
        for(int k=0;k<3;++k) {
            auto a=t.ids[k],b=t.ids[(k+1)%3];const int sign=a<b?1:-1;if(a>b)std::swap(a,b);edges[{a,b}].push_back({f,sign});
            auto &link=links[t.ids[k]];const auto u=t.ids[(k+1)%3],v=t.ids[(k+2)%3];link[u].insert(v);link[v].insert(u);
        }
        triangles.push_back(t);
    }
    std::vector<size_t> parents(mesh.faces.size());std::iota(parents.begin(),parents.end(),0);
    auto root=[&](size_t i){while(parents[i]!=i){parents[i]=parents[parents[i]];i=parents[i];}return i;};
    for(const auto &[key,incident]:edges) {
        audit.exact.boundaryEdges+=incident.size()==1;audit.exact.nonmanifoldEdges+=incident.size()>2;
        audit.exact.windingErrors+=incident.size()==2 && incident[0].second==incident[1].second;
        for(size_t i=1;i<incident.size();++i) parents[root(incident[i].first)]=root(incident[0].first);
    }
    for(const auto &link:links) {
        std::set<size_t> visited;std::vector<size_t> todo;
        if(!link.empty()) todo.push_back(link.begin()->first);
        while(!todo.empty()) {auto v=todo.back();todo.pop_back();if(!visited.insert(v).second)continue;for(auto u:link.at(v))todo.push_back(u);}
        size_t ends=0;bool bad=visited.size()!=link.size();
        for(const auto &[key,neighbors]:link) {ends+=neighbors.size()==1;bad|=neighbors.empty()||neighbors.size()>2;}
        bad|=ends!=0 && ends!=2;audit.nonmanifoldVertices+=bad;
    }
    std::set<size_t> roots;for(size_t i=0;i<mesh.faces.size();++i)roots.insert(root(i));
    audit.exact.vertices=vertices.size();audit.exact.components=roots.size();
    if(roots.size()>1 && std::getenv("DW_CLIFF_COMPONENTS")) {
        for(auto component:roots) {
            size_t count=0;Vector3 lo{1e9f,1e9f,1e9f},hi{-1e9f,-1e9f,-1e9f};
            for(size_t i=0;i<mesh.faces.size();++i)if(root(i)==component) {
                ++count;for(auto p:mesh.faces[i]) {
                    lo={std::min(lo.x,p.x),std::min(lo.y,p.y),std::min(lo.z,p.z)};
                    hi={std::max(hi.x,p.x),std::max(hi.y,p.y),std::max(hi.z,p.z)};
                }
            }
            std::cout<<"MESH_COMPONENT faces="<<count<<" min="<<lo.x<<','<<lo.y<<','<<lo.z<<" max="<<hi.x<<','<<hi.y<<','<<hi.z<<'\n';
        }
    }

    std::vector<size_t> order(triangles.size());std::iota(order.begin(),order.end(),0);
    std::sort(order.begin(),order.end(),[&](auto a,auto b){return triangles[a].lo.x<triangles[b].lo.x;});
    for(size_t i=0;i<order.size();++i) for(size_t j=i+1;j<order.size();++j) {
        const auto &a=triangles[order[i]],&b=triangles[order[j]];
        if(b.lo.x>a.hi.x+Eps) break;
        if(order[i]<firstChangedTriangle && order[j]<firstChangedTriangle)continue;
        if(b.lo.y>a.hi.y+Eps || b.hi.y<a.lo.y-Eps || b.lo.z>a.hi.z+Eps || b.hi.z<a.lo.z-Eps) continue;
        if(length(a.normal)==0 || length(b.normal)==0) continue;
        ++audit.testedPairs;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        const int type=exactContacts?exactContact::classify(exactTriangles[order[i]],exactTriangles[order[j]]):intersection(a,b);
#else
        const int type=intersection(a,b);
#endif
        if(type) {audit.selfIntersections+=type==1;audit.coplanarOverlaps+=type==2;if(audit.problemPairs.size()<64)audit.problemPairs.push_back({order[i],order[j]});}
    }
    return audit;
}
StrictSurfaceAudit auditStrictSurface(const cliffOptions::Mesh &mesh) {return strictSurface(mesh,0);}
void writeSurfaceProbe(const char *path,const cliffOptions::Mesh &mesh,const std::vector<Volume> &volumes,const StrictSurfaceAudit &audit) {
    std::ofstream out(path);out.precision(17);out<<"{\"faces\":[";
    for(size_t i=0;i<mesh.faces.size();++i) {
        if(i)out<<',';out<<'[';
        for(int k=0;k<3;++k){if(k)out<<',';const auto p=mesh.faces[i][k];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}
        out<<']';
    }
    out<<"],\"pairs\":[";
    for(size_t i=0;i<audit.problemPairs.size();++i){if(i)out<<',';const auto p=audit.problemPairs[i];out<<'['<<p[0]<<','<<p[1]<<']';}
    out<<"],\"volumes\":[";
    for(size_t i=0;i<volumes.size();++i) {
        if(i)out<<',';out<<'[';
        for(size_t k=0;k<volumes[i].planes.size();++k) {
            if(k)out<<',';const auto p=volumes[i].planes[k];const auto n=planeNormal(p);
            out<<'['<<n[0]<<','<<n[1]<<','<<n[2]<<','<<p.distance<<']';
        }
        out<<']';
    }
    out<<"]}\n";
    if(!out)throw std::runtime_error("Cannot write emitted surface probe");
}
StrictSurfaceAudit auditSurfaceReplacement(const cliffOptions::Mesh &mesh,size_t firstChangedTriangle) {return strictSurface(mesh,firstChangedTriangle);}
bool replacementIntersects(const cliffOptions::Mesh &mesh,size_t firstChangedTriangle) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    const bool exactContacts=std::getenv("DW_CLIFF_EXACT_CONTACTS")!=nullptr;
    std::map<size_t,exactContact::Triangle> exactTriangles;
    auto exactTriangle=[&](size_t i)->const exactContact::Triangle & {return exactTriangles.try_emplace(i,mesh.faces[i]).first->second;};
#else
    if(std::getenv("DW_CLIFF_EXACT_CONTACTS"))throw std::runtime_error("Exact contact audit requires the boolean experiment");
#endif
    std::vector<Triangle> triangles;triangles.reserve(mesh.faces.size());
    for(size_t i=0;i<mesh.faces.size();++i) {
        Triangle t;
        for(int k=0;k<3;++k){t.p[k]=d(mesh.faces[i][k]);t.ids[k]=i*3+k;}
        t.normal=cross(t.p[1]-t.p[0],t.p[2]-t.p[0]);const auto magnitude=length(t.normal);
        if(magnitude==0)return true;t.normal=t.normal*(1/magnitude);t.lo=t.hi=t.p[0];
        for(auto p:t.p){t.lo={std::min(t.lo.x,p.x),std::min(t.lo.y,p.y),std::min(t.lo.z,p.z)};t.hi={std::max(t.hi.x,p.x),std::max(t.hi.y,p.y),std::max(t.hi.z,p.z)};}
        triangles.push_back(t);
    }
    // Use the same pair ordering as the full verifier, including equal-x ties.
    std::vector<size_t> order(triangles.size()),rank(triangles.size());std::iota(order.begin(),order.end(),0);
    std::sort(order.begin(),order.end(),[&](auto a,auto b){return triangles[a].lo.x<triangles[b].lo.x;});
    for(size_t i=0;i<order.size();++i)rank[order[i]]=i;
    for(size_t i=firstChangedTriangle;i<triangles.size();++i)for(size_t j=0;j<i;++j) {
        const auto &u=triangles[i],&v=triangles[j];
        const auto &a=rank[i]<rank[j]?u:v;auto b=rank[i]<rank[j]?v:u;
        if(b.lo.x>a.hi.x+Eps || b.lo.y>a.hi.y+Eps || b.hi.y<a.lo.y-Eps || b.lo.z>a.hi.z+Eps || b.hi.z<a.lo.z-Eps)continue;
        for(int x=0;x<3;++x)for(int y=0;y<3;++y)
            if(a.p[x].x==b.p[y].x && a.p[x].y==b.p[y].y && a.p[x].z==b.p[y].z)b.ids[y]=a.ids[x];
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        if(exactContacts?exactContact::classify(exactTriangle(i),exactTriangle(j)):intersection(a,b))return true;
#else
        if(intersection(a,b))return true;
#endif
    }
    return false;
}
static BoundaryCoverageAudit boundaryCoverage(const cliffOptions::Mesh &mesh,const std::vector<Volume> &volumes,double margin,bool writeProbe) {
    ValidationTiming measured;
    BoundaryCoverageAudit audit;
    // Verification must not use construction's 20-micrometre classification
    // epsilon or round every intersection back to a render float. Keep the
    // emitted float inputs exact in double throughout half-space clipping.
    using Poly=std::vector<D>;
    auto area=[](const Poly &p) {
        D sum{};
        for(size_t i=1;i+1<p.size();++i)sum=sum+cross(p[i]-p[0],p[i+1]-p[0]);
        return length(sum)*.5;
    };
    auto cut=[](const Poly &p,const Plane &plane,bool outside) {
        if(p.empty())return Poly{};
        const auto n=planeNormal(plane);const D normal{n[0],n[1],n[2]};
        std::vector<double> values;values.reserve(p.size());
        for(auto q:p)values.push_back(dot(normal,q)-plane.distance);
        const auto [lo,hi]=std::minmax_element(values.begin(),values.end());
        if(outside && *hi<=0)return Poly{};
        if(!outside && *lo>0)return Poly{};
        if((outside && *lo>=0) || (!outside && *hi<=0))return p;
        Poly out;
        for(size_t i=0;i<p.size();++i) {
            const auto j=(i+1)%p.size();const double a=values[i],b=values[j];
            if(outside?a>=0:a<=0)out.push_back(p[i]);
            if((a<0 && b>0) || (a>0 && b<0))out.push_back(p[i]+(p[j]-p[i])*(a/(a-b)));
        }
        return out;
    };
    auto intersect=[&](Poly p,const Volume &volume) {
        for(const auto &plane:volume.planes){p=cut(p,plane,false);if(p.size()<3)break;}
        return p;
    };
    auto expanded=volumes,shrunk=volumes;
    for(auto &v:expanded)for(auto &p:v.planes)p.distance+=margin;
    for(auto &v:shrunk)for(auto &p:v.planes)p.distance-=margin;
    std::vector<size_t> failedFaces;
    for(const auto &t:mesh.faces) {
        const size_t index=audit.triangles;bool failed=false;
        const Poly face{d(t[0]),d(t[1]),d(t[2])};++audit.triangles;
        for(const auto &v:shrunk) {
            const auto a=area(intersect(face,v));
            if(a>1e-12){++audit.buriedFragments;audit.buriedArea+=a;failed=true;}
        }
        std::vector<Poly> parts{face};
        for(const auto &v:expanded) {
            std::vector<Poly> next;
            for(auto part:parts) {
                // Small intersections still contribute to union coverage.
                // An area cutoff here makes the result depend on how the
                // same source solid was partitioned into prisms.
                if(area(intersect(part,v))==0){next.push_back(std::move(part));continue;}
                for(const auto &plane:v.planes) {
                    auto outside=cut(part,plane,true);
                    if(area(outside)>0)next.push_back(std::move(outside));
                    part=cut(part,plane,false);if(part.size()<3)break;
                }
            }
            parts=std::move(next);if(parts.empty())break;
        }
        double uncoveredArea=0;size_t positiveParts=0;
        for(const auto &part:parts){const auto a=area(part);uncoveredArea+=a;positiveParts+=a>0;}
        // Test total uncovered area, so fragmentation cannot hide a gap.
        if(uncoveredArea>1e-12){audit.detachedFragments+=positiveParts;audit.detachedArea+=uncoveredArea;failed=true;}
        if(failed)failedFaces.push_back(index);
    }
    if(writeProbe && !failedFaces.empty())if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
        cliffOptions::Mesh selected;
        for(size_t k=0;k<std::min(size_t(8),failedFaces.size());++k)selected.faces.push_back(mesh.faces[failedFaces[k]]);
        const auto output=std::string(path)+".coverage.json";writeSurfaceProbe(output.c_str(),selected,volumes,{});
        std::ofstream out(std::string(path)+".coverage-map.json");out.precision(17);
        out<<"{\"total_faces\":"<<mesh.faces.size()<<",\"failed_faces\":"<<failedFaces.size()<<",\"margin_m\":"<<margin<<",\"selected_original_faces\":[";
        for(size_t k=0;k<selected.faces.size();++k){if(k)out<<',';out<<failedFaces[k];}out<<"]}\n";
        if(!out)throw std::runtime_error("Cannot save source-boundary failure map");
    }
    return audit;
}
BoundaryCoverageAudit auditBoundaryCoverage(const cliffOptions::Mesh &mesh,const std::vector<Volume> &volumes,double margin) {
    return boundaryCoverage(mesh,volumes,margin,true);
}
BoundaryCoverageAudit auditBoundaryCoverageQuiet(const cliffOptions::Mesh &mesh,const std::vector<Volume> &volumes,double margin) {
    return boundaryCoverage(mesh,volumes,margin,false);
}

} // namespace dw::rockFormations
