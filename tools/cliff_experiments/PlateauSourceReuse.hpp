#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "PlateauChunks.hpp"
#include "FormationTiming.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <map>
#include <numeric>
#include <optional>
#include <set>

namespace dw::rockFormations::sourceReuse {
using R=boost::multiprecision::cpp_rational;
using P=std::array<R,2>;
using Ring=std::vector<P>;
using H=std::array<R,3>;
inline R value(const H &h,const P &p){return h[0]*p[0]+h[1]*p[1]+h[2];}
inline R signedArea(const Ring &p){R a=0;for(size_t k=0;k<p.size();++k)a+=p[k][0]*p[(k+1)%p.size()][1]-p[k][1]*p[(k+1)%p.size()][0];return a;}
inline Ring clip(const Ring &p,const H &h) {
    Ring out;
    for(size_t k=0;k<p.size();++k) {
        const auto &a=p[k],&b=p[(k+1)%p.size()];const R u=value(h,a),v=value(h,b);
        if(u<=0)out.push_back(a);
        if(u*v<0){const R t=u/(u-v);out.push_back({a[0]+t*(b[0]-a[0]),a[1]+t*(b[1]-a[1])});}
    }
    if(out.size()<3 || signedArea(out)==0)out.clear();return out;
}
inline std::vector<H> sides(const Ring &p) {
    const R a=signedArea(p);if(a==0)throw std::runtime_error("Reuse source has no projected area");
    const int sign=a>0?1:-1;std::vector<H> hs;
    for(size_t k=0;k<p.size();++k) {
        const auto &a=p[k],&b=p[(k+1)%p.size()];
        hs.push_back({sign*(b[1]-a[1]),sign*(a[0]-b[0]),sign*(b[0]*a[1]-a[0]*b[1])});
    }
    for(const auto &h:hs)for(const auto &q:p)if(value(h,q)>0)throw std::runtime_error("Reuse source is not convex");
    return hs;
}
inline std::vector<Ring> subtract(Ring p,const std::vector<H> &hs) {
    std::vector<Ring> out;
    for(const auto &h:hs) {
        auto outside=clip(p,{-h[0],-h[1],-h[2]});
        if(!outside.empty() && std::any_of(outside.begin(),outside.end(),[&](const auto &q){return value(h,q)>0;}))out.push_back(std::move(outside));
        p=clip(p,h);if(p.empty())break;
    }
    return out;
}
inline Ring project(const Polygon &p){Ring r;for(auto q:p)r.push_back({R(q.x),R(q.z)});return r;}
inline H height(const Plane &p){const auto n=planeNormal(p);if(n[1]<=0)throw std::runtime_error("Reuse candidate has no upper plane");return {-R(n[0])/R(n[1]),-R(n[2])/R(n[1]),R(p.distance)/R(n[1])};}
inline H height(const Polygon &p) {
    const auto a=p.front();
    for(size_t i=1;i<p.size();++i)for(size_t j=i+1;j<p.size();++j) {
        const auto b=p[i],c=p[j];
        const R ux=R(b.x)-R(a.x),uz=R(b.z)-R(a.z),uy=R(b.y)-R(a.y),vx=R(c.x)-R(a.x),vz=R(c.z)-R(a.z),vy=R(c.y)-R(a.y),det=ux*vz-uz*vx;
        if(det==0)continue;
        const R x=(uy*vz-uz*vy)/det,z=(ux*vy-uy*vx)/det;H h{x,z,R(a.y)-x*R(a.x)-z*R(a.z)};
        for(auto q:p)if(value(h,{R(q.x),R(q.z)})!=R(q.y))throw std::runtime_error("Reuse original source is not planar");
        return h;
    }
    throw std::runtime_error("Reuse original source has no projected area");
}
struct Bounds {double lx,lz,hx,hz;};
inline Bounds bounds(const Ring &p) {
    Bounds b{p[0][0].convert_to<double>(),p[0][1].convert_to<double>(),p[0][0].convert_to<double>(),p[0][1].convert_to<double>()};
    for(const auto &q:p){const double x=q[0].convert_to<double>(),z=q[1].convert_to<double>();b.lx=std::min(b.lx,x);b.hx=std::max(b.hx,x);b.lz=std::min(b.lz,z);b.hz=std::max(b.hz,z);}return b;
}
inline bool meets(Bounds a,Bounds b){return a.lx<b.hx && b.lx<a.hx && a.lz<b.hz && b.lz<a.hz;}
struct Selection {
    std::vector<bool> eligible,guarded;
    size_t planeCandidates=0,domainRejected=0,ownerRejected=0,transitionRetained=0,pinchRetained=0,heightLinkRetained=0;
};
// Select construction inputs only. Full cap/source/floor/core/assembly/world
// acceptance remains mandatory; this is never post-union component deletion.
inline Selection select(const std::vector<GradedRoofCell> &cells,const std::vector<Polygon> &original) {
    ConstructionTiming timing("source_reuse");ConstructionChecks checks;
    struct Source{Ring domain;H roof;std::vector<H> sides;Bounds box;};
    std::vector<Source> sources;std::map<std::pair<int,int>,std::vector<size_t>> bins;
    using PlaneKey=std::array<long long,3>;std::map<PlaneKey,std::vector<H>> planes;
    auto key=[](const H &h){return PlaneKey{std::llround(h[0].convert_to<double>()*1e8),std::llround(h[1].convert_to<double>()*1e8),std::llround(h[2].convert_to<double>()*1e8)};};
    for(const auto &p:original) {
        auto domain=project(p);const auto box=bounds(domain);const auto h=height(p);const size_t id=sources.size();
        sources.push_back({domain,h,sides(domain),box});planes[key(h)].push_back(h);
        for(int x=int(std::floor(box.lx));x<=int(std::floor(box.hx));++x)for(int z=int(std::floor(box.lz));z<=int(std::floor(box.hz));++z)bins[{x,z}].push_back(id);
    }
    Selection selection;selection.eligible.resize(cells.size());std::vector<H> roofs;
    const R margin=R(1)/50000; // Stricter construction precondition; weld/source guards unchanged.
    for(size_t i=0;i<cells.size();++i) {
        const auto h=height(cells[i].roof);roofs.push_back(h);const auto k=key(h);bool candidate=false;
        for(int x=-1;x<=1;++x)for(int z=-1;z<=1;++z)for(int c=-1;c<=1;++c) {
            auto at=planes.find({k[0]+x,k[1]+z,k[2]+c});if(at==planes.end())continue;
            for(const auto &s:at->second)if(std::abs((h[0]-s[0]).convert_to<double>())<=1e-10 && std::abs((h[1]-s[1]).convert_to<double>())<=1e-10 && std::abs((h[2]-s[2]).convert_to<double>())<=1e-10)candidate=true;
        }
        if(!candidate)continue;++selection.planeCandidates;
        const auto domain=project(cells[i].outline);sides(domain);const auto box=bounds(domain);
        std::set<size_t> nearby;
        for(int x=int(std::floor(box.lx));x<=int(std::floor(box.hx));++x)for(int z=int(std::floor(box.lz));z<=int(std::floor(box.hz));++z)if(auto at=bins.find({x,z});at!=bins.end())nearby.insert(at->second.begin(),at->second.end());
        std::vector<Ring> missing{domain};bool higher=false;
        for(auto id:nearby) {
            const auto &s=sources[id];if(!meets(box,s.box))continue;
            auto overlap=domain;for(const auto &cut:s.sides)overlap=clip(overlap,cut);if(overlap.empty())continue;
            const H delta{s.roof[0]-h[0],s.roof[1]-h[1],s.roof[2]-h[2]};const H high{delta[0],delta[1],delta[2]-margin};
            const auto above=clip(overlap,{-high[0],-high[1],-high[2]});
            higher |= !above.empty() && std::any_of(above.begin(),above.end(),[&](const auto &q){return value(high,q)>0;});
            auto cuts=s.sides;cuts.push_back(high);cuts.push_back({-delta[0],-delta[1],-delta[2]-margin});
            std::vector<Ring> next;for(auto &part:missing){auto pieces=subtract(std::move(part),cuts);next.insert(next.end(),std::make_move_iterator(pieces.begin()),std::make_move_iterator(pieces.end()));}missing=std::move(next);
        }
        selection.domainRejected+=!missing.empty();selection.ownerRejected+=higher;selection.eligible[i]=missing.empty() && !higher;
    }
    // Split every collinear saved-grid edge at all endpoints, so a T junction
    // has the same adjacency as an explicitly subdivided source mesh.
    using Grid=std::array<long long,2>;using Line=std::array<long long,3>;
    std::map<Line,std::map<long long,std::map<size_t,int>>> events;
    for(size_t i=0;i<cells.size();++i) {
        std::vector<Grid> ring;
        for(auto p:cells[i].outline) {
            const double x=double(p.x)*65536,z=double(p.z)*65536;
            if(x!=std::round(x) || z!=std::round(z) || std::abs(x)>1e9 || std::abs(z)>1e9)throw std::runtime_error("Reuse outline exceeds exact saved-grid bounds");
            ring.push_back({std::llround(x),std::llround(z)});
        }
        for(size_t k=0;k<ring.size();++k) {
            const auto a=ring[k],b=ring[(k+1)%ring.size()];const auto x=b[0]-a[0],z=b[1]-a[1],g=std::gcd(x,z);if(g==0)continue;
            long long A=z/g,B=-x/g,C=-A*a[0]-B*a[1];if(A<0 || (A==0 && B<0)){A=-A;B=-B;C=-C;}
            const int axis=B?0:1;const auto lo=std::min(a[axis],b[axis]),hi=std::max(a[axis],b[axis]);
            ++events[{A,B,C}][lo][i];--events[{A,B,C}][hi][i];
        }
    }
    struct Vertex {std::set<size_t> cells;std::vector<std::array<size_t,2>> edges;};
    std::map<Grid,Vertex> vertices;
    std::vector<std::set<size_t>> bad(cells.size());
    for(const auto &[line,positions]:events) {
        std::map<size_t,int> active;
        for(auto at=positions.begin();at!=positions.end();++at) {
            for(const auto &[i,delta]:at->second){active[i]+=delta;if(active[i]==0)active.erase(i);}
            const auto next=std::next(at);if(next==positions.end() || active.empty())continue;
            if(active.size()>2)throw std::runtime_error("Reuse outline has a nonmanifold collinear interval");
            const auto [A,B,C]=line;bool excessive=false;
            for(const auto t:{at->first,next->first}) {
                P p=B?P{R(t),(-R(A)*R(t)-R(C))/R(B)}:P{-R(C)/R(A),R(t)};p[0]/=65536;p[1]/=65536;
                const Grid key{(p[0]*65536).convert_to<long long>(),(p[1]*65536).convert_to<long long>()};
                if(R(key[0])!=p[0]*65536 || R(key[1])!=p[1]*65536)throw std::runtime_error("Reuse edge endpoint leaves the shared grid");
                auto &vertex=vertices[key];for(const auto &[i,count]:active)vertex.cells.insert(i);
                if(active.size()==2) {
                    const size_t a=active.begin()->first,b=std::next(active.begin())->first;vertex.edges.push_back({a,b});
                    if(abs(value(roofs[a],p)-value(roofs[b],p))>margin)excessive=true;
                }
            }
            if(excessive){const size_t a=active.begin()->first,b=std::next(active.begin())->first;bad[a].insert(b);bad[b].insert(a);}
        }
    }
    selection.guarded=selection.eligible;std::vector<size_t> pending;
    for(size_t i=0;i<cells.size();++i)if(selection.eligible[i] && std::any_of(bad[i].begin(),bad[i].end(),[&](size_t j){return !selection.eligible[j];})){selection.guarded[i]=false;pending.push_back(i);}
    auto propagate=[&](){while(!pending.empty()){const auto i=pending.back();pending.pop_back();for(auto j:bad[i])if(selection.guarded[j]){selection.guarded[j]=false;pending.push_back(j);}}};
    propagate();
    for(size_t pass=0;pass<=cells.size();++pass) {
        std::vector<Polygon> rebuilt;for(size_t i=0;i<cells.size();++i)if(!selection.guarded[i])rebuilt.push_back(cells[i].outline);
        if(rebuilt.empty())break;
        const auto pinches=plateauFootprintPinches(rebuilt);if(pinches.empty())break;
        size_t retained=0;
        for(auto point:pinches) {
            const P q{R(point.x),R(point.z)};
            for(size_t i=0;i<cells.size();++i)if(selection.guarded[i]) {
                const auto domain=project(cells[i].outline);const auto box=bounds(domain);
                if(point.x<box.lx || point.x>box.hx || point.z<box.lz || point.z>box.hz)continue;
                const auto cuts=sides(domain);
                if(std::all_of(cuts.begin(),cuts.end(),[&](const auto &h){return value(h,q)<=0;})){selection.guarded[i]=false;pending.push_back(i);++retained;}
            }
        }
        if(!retained)throw std::runtime_error("Source reuse cannot resolve a reconstructed footprint pinch");
        selection.pinchRetained+=retained;propagate();
        std::cout<<"PLATEAU_REUSE_LINK_GUARD pass="<<pass<<" pinches="<<pinches.size()<<" retained_source_cells="<<retained<<'\n';
    }
    // A connected projected footprint can still have two diagonal high sectors
    // meeting on a vertical edge. Audit every distinct emitted-height interval
    // in each source vertex fan, keeping original cells instead of bridging it.
    for(size_t pass=0;pass<=cells.size();++pass) {
        size_t restored=0,conflicts=0;
        for(const auto &[point,vertex]:vertices) {
            const double x=double(point[0])/65536,z=double(point[1])/65536;
            std::map<size_t,R> heights;std::set<R> levels{R(-.12f)};
            for(auto i:vertex.cells) {
                const auto n=planeNormal(cells[i].roof);const float h=float((cells[i].roof.distance-n[0]*x-n[2]*z)/n[1]);
                heights.emplace(i,R(h));levels.insert(R(h));
            }
            for(auto low=levels.begin();low!=levels.end();++low) {
                const auto high=std::next(low);if(high==levels.end())break;
                // Sub-weld tiers already occur in the unchanged valid baseline.
                // Leave them to the unchanged mesher and strict emitted audit.
                if(*high-*low<=margin)continue;
                const R level=(*low+*high)/2;
                std::set<size_t> active;
                for(const auto &[i,h]:heights)if(!selection.guarded[i] && h>level)active.insert(i);
                if(active.size()<2)continue;
                std::map<size_t,std::set<size_t>> graph;
                for(auto edge:vertex.edges)if(active.contains(edge[0]) && active.contains(edge[1])){graph[edge[0]].insert(edge[1]);graph[edge[1]].insert(edge[0]);}
                std::set<size_t> visited;std::vector<size_t> todo{*active.begin()};
                while(!todo.empty()){const auto i=todo.back();todo.pop_back();if(!visited.insert(i).second)continue;for(auto j:graph[i])todo.push_back(j);}
                if(visited.size()==active.size())continue;++conflicts;size_t added=0;
                for(const auto &[i,h]:heights)if(selection.guarded[i] && h>level){selection.guarded[i]=false;pending.push_back(i);++added;}
                if(!added)throw std::runtime_error("Source reuse cannot resolve a vertical source-link fan");
                restored+=added;
            }
        }
        if(!restored)break;selection.heightLinkRetained+=restored;propagate();
        std::cout<<"PLATEAU_REUSE_HEIGHT_GUARD pass="<<pass<<" conflicts="<<conflicts<<" retained_source_cells="<<restored<<'\n';
    }
    for(size_t i=0;i<cells.size();++i)selection.transitionRetained+=selection.eligible[i] && !selection.guarded[i];
    return selection;
}
using P3=std::array<R,3>;
using Face=std::vector<P3>;
inline bool positive(const Face &f) {
    P3 sum{};
    for(size_t k=1;k+1<f.size();++k) {
        P3 a,b;for(int j=0;j<3;++j){a[j]=f[k][j]-f[0][j];b[j]=f[k+1][j]-f[0][j];}
        sum[0]+=a[1]*b[2]-a[2]*b[1];sum[1]+=a[2]*b[0]-a[0]*b[2];sum[2]+=a[0]*b[1]-a[1]*b[0];
    }
    return sum[0]!=0 || sum[1]!=0 || sum[2]!=0;
}
inline R value(const H &h,const P3 &p){return h[0]*p[0]+h[1]*p[2]+h[2];}
inline Face clip(const Face &f,const H &h) {
    Face out;
    for(size_t k=0;k<f.size();++k) {
        const auto &a=f[k],&b=f[(k+1)%f.size()];const R u=value(h,a),v=value(h,b);
        if(u<=0)out.push_back(a);
        if(u*v<0){const R t=u/(u-v);P3 p;for(int j=0;j<3;++j)p[j]=a[j]+t*(b[j]-a[j]);out.push_back(std::move(p));}
    }
    if(!positive(out))out.clear();return out;
}
inline Ring hull(Ring p) {
    std::sort(p.begin(),p.end());p.erase(std::unique(p.begin(),p.end()),p.end());
    if(p.size()<3)throw std::runtime_error("Reconstructed source column has no footprint");
    auto turn=[](const P &a,const P &b,const P &c)->R{return (b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0]);};
    Ring result;
    for(const auto &q:p){while(result.size()>1 && turn(result[result.size()-2],result.back(),q)<=0)result.pop_back();result.push_back(q);}
    const auto lower=result.size();
    for(auto q=std::next(p.rbegin());q!=p.rend();++q){while(result.size()>lower && turn(result[result.size()-2],result.back(),*q)<=0)result.pop_back();result.push_back(*q);}
    if(!result.empty())result.pop_back();if(result.size()<3)throw std::runtime_error("Reconstructed source column has no footprint");return result;
}
struct Columns {
    struct Entry{Bounds box;std::vector<H> cuts;};std::vector<Entry> entries;
    explicit Columns(const std::vector<Volume> &volumes) {
        for(const auto &v:volumes) {
            Ring p;for(const auto &f:v.faces)for(auto q:f)p.push_back({R(q.x),R(q.z)});
            const auto domain=hull(std::move(p));entries.push_back({bounds(domain),sides(domain)});
        }
    }
    // The replacement is already one checked float mesh. Its projected faces
    // form its actual shadow, with shared vertices on both sides of every
    // internal edge. Reconstructing that shadow from the earlier individual
    // prism hulls reopens gaps that the connected mesher has already closed.
    explicit Columns(const cliffOptions::Mesh &mesh)
        :Columns(std::vector<Volume>{}) {
        for(const auto &face:mesh.faces) {
            const auto domain=project({face[0],face[1],face[2]});
            if(signedArea(domain)!=0)entries.push_back({bounds(domain),sides(domain)});
        }
        if(entries.empty())throw std::runtime_error("Replacement mesh has no source-crop footprint");
    }
    // Keep original source-domain identity through the grid conversion. A
    // source face whose COMPLETE canonical footprint belongs to the edit is
    // cropped as one original face, with its original border vertices. Testing
    // only against the fixed initial columns prevents recursive crop growth.
    void claimCanonicalSources(const std::vector<Polygon> &sources) {
        if(entries.empty())return;
        const size_t baseCount=entries.size();std::vector<Entry> claimed;
        Bounds region=entries.front().box;
        for(const auto &e:entries){region.lx=std::min(region.lx,e.box.lx);region.hx=std::max(region.hx,e.box.hx);region.lz=std::min(region.lz,e.box.lz);region.hz=std::max(region.hz,e.box.hz);}
        size_t candidates=0;R maximumShift=0;
        struct Claim {Polygon original;Ring canonical;R shift;};std::vector<Claim> proof;
        for(const auto &source:sources) {
            const auto original=project(source);if(signedArea(original)==0)continue;
            const auto box=bounds(original);if(!meets(box,region))continue;++candidates;
            Ring canonical;R displacement=0;
            for(auto p:source) {
                const P q{R(float(std::round(double(p.x)*65536)/65536)),R(float(std::round(double(p.z)*65536)/65536))};
                const R dx=R(p.x)-q[0],dz=R(p.z)-q[1];
                const R half=R(1)/131072;
                if(abs(dx)>half || abs(dz)>half)throw std::runtime_error("Source identity exceeds its canonical grid displacement");
                const R squared=dx*dx+dz*dz;displacement=std::max(displacement,squared);canonical.push_back(q);
            }
            if(signedArea(canonical)==0)continue;
            const auto canonicalBox=bounds(canonical);std::vector<Ring> remaining{canonical};
            for(size_t i=0;i<baseCount && !remaining.empty();++i)if(meets(canonicalBox,entries[i].box)) {
                std::vector<Ring> next;for(auto piece:remaining){auto parts=subtract(std::move(piece),entries[i].cuts);next.insert(next.end(),std::make_move_iterator(parts.begin()),std::make_move_iterator(parts.end()));}remaining=std::move(next);
            }
            if(!remaining.empty())continue;
            claimed.push_back({box,sides(original)});maximumShift=std::max(maximumShift,displacement);proof.push_back({source,canonical,displacement});
        }
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
            std::ofstream out(std::string(path)+".source-ownership.json");out.precision(17);
            out<<"{\"scope\":\"Complete canonical source footprints covered by fixed construction columns; original source boundary vertices are reused for cropping\",\"base_columns\":[";
            for(size_t i=0;i<baseCount;++i){if(i)out<<',';out<<"{\"box\":["<<entries[i].box.lx<<','<<entries[i].box.lz<<','<<entries[i].box.hx<<','<<entries[i].box.hz<<"],\"cuts\":[";for(size_t k=0;k<entries[i].cuts.size();++k){if(k)out<<',';const auto &h=entries[i].cuts[k];out<<"[\""<<h[0]<<"\",\""<<h[1]<<"\",\""<<h[2]<<"\"]";}out<<"]}";}
            out<<"],\"claims\":[";for(size_t i=0;i<proof.size();++i){if(i)out<<',';const auto &p=proof[i];out<<"{\"source\":[";for(size_t k=0;k<p.original.size();++k){if(k)out<<',';const auto q=p.original[k];out<<'['<<q.x<<','<<q.y<<','<<q.z<<']';}out<<"],\"canonical\":[";for(size_t k=0;k<p.canonical.size();++k){if(k)out<<',';out<<"[\""<<p.canonical[k][0]<<"\",\""<<p.canonical[k][1]<<"\"]";}out<<"],\"maximum_displacement_squared_exact\":\""<<p.shift<<"\"}";}
            out<<"],\"recursive_growth\":false,\"full_assembly_proved\":false}\n";
            if(!out)throw std::runtime_error("Cannot save shared source ownership");
        }
        entries.insert(entries.end(),std::make_move_iterator(claimed.begin()),std::make_move_iterator(claimed.end()));
        std::cout<<"PLATEAU_SHARED_SOURCE_OWNERSHIP candidates="<<candidates<<" claimed_faces="<<proof.size()<<" fixed_base_columns="<<baseCount
                 <<" maximum_xy_displacement_m="<<std::sqrt(maximumShift.convert_to<double>())<<" canonical_half_quantum_m="<<1./131072<<" positive_domain_coverage=PASS\n";
    }
    bool contains(Vector3 p)const {
        const P q{R(p.x),R(p.z)};
        return std::any_of(entries.begin(),entries.end(),[&](const auto &e){return std::all_of(e.cuts.begin(),e.cuts.end(),[&](const auto &h){return value(h,q)<=0;});});
    }
    // Exact intersections remain rational through every cut, with one final
    // conversion per retained source vertex. No positive source fragment is
    // dropped by an area/length threshold; collapsed render fragments reject.
    std::vector<Polygon> outside(const Polygon &source,bool &removed)const {
        Face input;for(auto q:source)input.push_back({R(q.x),R(q.y),R(q.z)});
        if(!positive(input))return {};
        std::vector<Face> parts{input};const auto box=bounds(project(source));
        for(const auto &e:entries) {
            if(e.box.hx<box.lx || box.hx<e.box.lx || e.box.hz<box.lz || box.hz<e.box.lz)continue;
            std::vector<Face> keep;
            for(auto part:parts) {
                auto intersection=part;for(const auto &h:e.cuts)intersection=clip(intersection,h);
                if(intersection.empty()){keep.push_back(std::move(part));continue;}
                removed=true;
                for(const auto &h:e.cuts) {
                    auto outside=clip(part,{-h[0],-h[1],-h[2]});
                    if(!outside.empty() && std::any_of(outside.begin(),outside.end(),[&](const auto &q){return value(h,q)>0;}))keep.push_back(std::move(outside));
                    part=clip(part,h);if(part.empty())break;
                }
            }
            parts=std::move(keep);if(parts.empty())break;
        }
        std::vector<Polygon> result;
        for(const auto &part:parts) {
            Polygon rendered;Face roundTrip;
            for(const auto &p:part){Vector3 q{p[0].convert_to<float>(),p[1].convert_to<float>(),p[2].convert_to<float>()};rendered.push_back(q);roundTrip.push_back({R(q.x),R(q.y),R(q.z)});}
            if(!positive(roundTrip)) {
                if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
                    std::ofstream out(std::string(path)+".source-fragment.json");out.precision(17);
                    out<<"{\"scope\":\"Rejected positive retained-source fragment and its collapsed render conversion; no fragment discarded\",\"input\":[";
                    for(size_t i=0;i<source.size();++i){if(i)out<<',';auto p=source[i];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}
                    out<<"],\"exact_fragment\":[";
                    for(size_t i=0;i<part.size();++i){if(i)out<<',';out<<"[\""<<part[i][0]<<"\",\""<<part[i][1]<<"\",\""<<part[i][2]<<"\"]";}
                    out<<"],\"rendered\":[";for(size_t i=0;i<rendered.size();++i){if(i)out<<',';auto p=rendered[i];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}
                    out<<"],\"original_positive\":true,\"render_positive\":false,\"rejected\":true}\n";
                    if(!out)throw std::runtime_error("Cannot save rejected retained-source fragment");
                }
                throw std::runtime_error("Retained source fragment collapses at render precision");
            }
            result.push_back(std::move(rendered));
        }
        return result;
    }
};
} // namespace dw::rockFormations::sourceReuse
#endif
