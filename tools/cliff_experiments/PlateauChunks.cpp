#include "PlateauChunks.hpp"
#include "FormationTiming.hpp"
#include "PlateauVertexBlend.hpp"
#include "PlateauAffineEnvelope.hpp"
#include "PlateauSourceReuse.hpp"
#include "PlateauSharedSourceEdges.hpp"
#include "PlateauCapDomain.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>

namespace dw::rockFormations {
namespace {
struct Height {double x=0,z=0,c=0;double at(Vector3 p)const{return x*p.x+z*p.z+c;}};
struct Bounds {float lx=0,hx=0,lz=0,hz=0;};
Bounds bounds(const Polygon &p) {
    Bounds b{p.front().x,p.front().x,p.front().z,p.front().z};
    for(auto q:p){b.lx=std::min(b.lx,q.x);b.hx=std::max(b.hx,q.x);b.lz=std::min(b.lz,q.z);b.hz=std::max(b.hz,q.z);}return b;
}
bool meets(Bounds a,Bounds b){return a.lx<=b.hx && b.lx<=a.hx && a.lz<=b.hz && b.lz<=a.hz;}
double area(const Polygon &p){double a=0;for(size_t k=1;k+1<p.size();++k)a+=(double(p[k].x)-p[0].x)*(double(p[k+1].z)-p[0].z)-(double(p[k].z)-p[0].z)*(double(p[k+1].x)-p[0].x);return std::abs(a)*.5;}
float snap(double x){return float(std::round(x*65536)/65536);}
Polygon clip(Polygon p,double nx,double nz,double d) {
    if(p.empty())return {};
    for(auto &q:p){q.x=snap(q.x);q.z=snap(q.z);q.y=0;}
    Polygon result;
    for(size_t i=0;i<p.size();++i) {
        const auto a=p[i],b=p[(i+1)%p.size()];const double u=nx*a.x+nz*a.z-d,v=nx*b.x+nz*b.z-d;
        if(u<=0)result.push_back({snap(a.x),0,snap(a.z)});
        if((u<0 && v>0) || (u>0 && v<0)){const double t=u/(u-v);result.push_back({snap(a.x+(double(b.x)-a.x)*t),0,snap(a.z+(double(b.z)-a.z)*t)});}
    }
    result.erase(std::unique(result.begin(),result.end(),[](auto a,auto b){return a.x==b.x && a.z==b.z;}),result.end());
    if(result.size()>1 && result.front().x==result.back().x && result.front().z==result.back().z)result.pop_back();
    if(result.size()<3 || area(result)<1e-10)return {};return result;
}
Polygon inside(Polygon p,const Polygon &domain) {
    for(size_t k=0;k<domain.size() && !p.empty();++k){auto a=domain[k],b=domain[(k+1)%domain.size()];p=clip(std::move(p),double(a.z)-b.z,double(b.x)-a.x,(double(a.z)-b.z)*a.x+(double(b.x)-a.x)*a.z);}return p;
}
bool contains(const Polygon &p,Vector3 q,double epsilon=1e-9) {
    for(size_t k=0;k<p.size();++k){auto a=p[k],b=p[(k+1)%p.size()];if((double(a.z)-b.z)*(double(q.x)-a.x)+(double(b.x)-a.x)*(double(q.z)-a.z)>epsilon)return false;}return true;
}
double distance(const Polygon &p,Vector3 q) {
    if(contains(p,q))return 0;
    double best=1e30;
    for(size_t k=0;k<p.size();++k){auto a=p[k],b=p[(k+1)%p.size()];double x=double(b.x)-a.x,z=double(b.z)-a.z,l=x*x+z*z;
        double t=l?std::clamp(((double(q.x)-a.x)*x+(double(q.z)-a.z)*z)/l,0.,1.):0;
        best=std::min(best,std::hypot(double(q.x)-a.x-t*x,double(q.z)-a.z-t*z));}return best;
}
Height height(const Plane &p){const auto n=planeNormal(p);return {-n[0]/n[1],-n[2]/n[1],p.distance/n[1]};}
Height height(const Polygon &p) {
    const auto a=p[0],b=p[1],c=p[2];const double ux=double(b.x)-a.x,uz=double(b.z)-a.z,uy=double(b.y)-a.y,vx=double(c.x)-a.x,vz=double(c.z)-a.z,vy=double(c.y)-a.y;
    const double determinant=ux*vz-uz*vx;
    if(determinant==0)throw std::runtime_error("Chunk source roof has no upward projection");
    Height h{(uy*vz-uz*vy)/determinant,(ux*vy-uy*vx)/determinant,0};h.c=a.y-h.x*a.x-h.z*a.z;return h;
}
Plane plane(Height h) {
    const double length=std::sqrt(h.x*h.x+1+h.z*h.z);Plane p;p.hasPreciseNormal=true;
    p.preciseNormal={-h.x/length,1/length,-h.z/length};p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};p.distance=h.c/length;return p;
}
std::vector<Polygon> subtract(const Polygon &subject,const std::vector<Polygon> &cuts,bool exact=false) {
    if(subject.empty())return {};
    std::vector<Polygon> local;const auto b=bounds(subject);
    for(const auto &cut:cuts)if(cut.size()>=3 && meets(b,bounds(cut))) {
        if(std::all_of(subject.begin(),subject.end(),[&](auto p){return contains(cut,p,exact?0:1e-9);}))return {};
        local.push_back(cut);
    }
    if(local.empty())return {subject};return plateauRegionFootprint({subject},local);
}
struct Source{Polygon domain;Height roof;Bounds box;};
struct Node{float delta=0,lower=.12f,baseline=.12f,weight=0,target=.12f;};
}

PlateauChunkBuild buildPlateauChunks(const PlateauRegion &region,const std::vector<Polygon> &caps,
    const std::vector<RoofGrade> &front,const std::vector<RoofGrade> &lower,
    const std::vector<Polygon> &holes,const PlateauChunkSettings &settings,std::span<const Volume> capVolumes) {
    ConstructionChecks requiredChecks;
    const bool sharedOwnership=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_PARTITION");
    const bool sharedCuts=sharedOwnership && std::getenv("DW_CLIFF_SOURCE_SHARED_CUTS");
    const bool sourceNodeBlend=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_NODE_BLEND")!=nullptr;
    const bool sourceVertexBlend=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_VERTEX_BLEND")!=nullptr;
    const bool affineEnvelope=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_AFFINE_ENVELOPE")!=nullptr;
    const bool retainedBand=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_RETAINED_BAND")!=nullptr;
    const bool reuseSources=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_REUSE")!=nullptr;
    const bool simplifySourceEdges=!settings.continuous && std::getenv("DW_CLIFF_SOURCE_SHARED_EDGES")!=nullptr;
    const bool capConnected=!settings.continuous && std::getenv("DW_CLIFF_CAP_CONNECTED_DOMAIN")!=nullptr;
    const bool earlyTarget=std::getenv("DW_CLIFF_EARLY_TARGET")!=nullptr;
    if(earlyTarget && (!capConnected || !affineEnvelope || retainedBand || reuseSources))throw std::runtime_error("Early target requires cap-connected affine construction and excludes retained-band/independent reuse");
    if(capConnected && (!simplifySourceEdges || reuseSources || !std::getenv("DW_CLIFF_ROOF_REGION") || !std::getenv("DW_CLIFF_ROOF_SHELL")))throw std::runtime_error("Cap domain requires shared source edges, regional shells and excludes independent cell reuse");
    if(simplifySourceEdges && (!affineEnvelope || reuseSources || !std::getenv("DW_CLIFF_BOOLEAN_SOURCE_CHECKED")))throw std::runtime_error("Shared source edge simplification requires the source-checked affine field and excludes independent reuse");
    if(reuseSources && (!affineEnvelope || !std::getenv("DW_CLIFF_BOOLEAN_SOURCE_CHECKED")))throw std::runtime_error("Source reuse requires the affine field and source-checked processing");
    if(retainedBand && !affineEnvelope)throw std::runtime_error("Retained band requires the affine source envelope");
    if(affineEnvelope && !sourceVertexBlend)throw std::runtime_error("Affine envelope requires shared source/grid vertex mode");
    if(sourceNodeBlend && !sharedOwnership)throw std::runtime_error("Source node blending requires source ownership");
    if(sourceVertexBlend && (!sharedCuts || sourceNodeBlend))throw std::runtime_error("Vertex blending requires shared source/grid cuts and excludes node blending");
    std::vector<std::vector<Polygon>> chunkCuts;
#ifndef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(sharedOwnership)throw std::runtime_error("Source ownership requires the boolean experiment");
#endif
    if(caps.empty() || settings.side<=0 || settings.support<=0)throw std::runtime_error("Invalid shared roof chunk settings");
    auto work=bounds(caps.front());
    for(const auto &cap:caps){auto b=bounds(cap);work.lx=std::min(work.lx,b.lx);work.hx=std::max(work.hx,b.hx);work.lz=std::min(work.lz,b.lz);work.hz=std::max(work.hz,b.hz);}
    const auto capBox=work;work.lx-=settings.support;work.hx+=settings.support;work.lz-=settings.support;work.hz+=settings.support;
    PlateauChunkBuild result;result.regionalFaces=region.domains.size();result.influence={{work.lx,0,work.lz},{work.hx,0,work.hz}};
    result.landHeight=.12f;for(const auto &g:lower)for(auto p:g.protectedRoof)result.landHeight=std::max(result.landHeight,float(height(g.roof).at(p))+.08f);
    Bounds anchors=capBox;anchors.lx-=2;anchors.hx+=2;anchors.lz-=2;anchors.hz+=2;
    std::vector<Source> sources;std::map<std::pair<int,int>,std::vector<size_t>> bins;
    // A one-cell halo supplies the same retained reference to both sides of a cut.
    Bounds halo=work;halo.lx-=1;halo.hx+=1;halo.lz-=1;halo.hz+=1;
    for(const auto &p:region.domains)if(meets(bounds(p),halo)) {
        auto canonical=p;for(auto &q:canonical){q.x=snap(q.x);q.z=snap(q.z);}
        const auto b=bounds(canonical);const auto id=sources.size();sources.push_back({std::move(canonical),height(p),b});
        if(meets(b,anchors))for(auto q:p)result.landHeight=std::max(result.landHeight,q.y+.04f);
        for(int x=int(std::floor(b.lx));x<=int(std::floor(b.hx));++x)for(int z=int(std::floor(b.lz));z<=int(std::floor(b.hz));++z)bins[{x,z}].push_back(id);
    }
    result.localFaces=sources.size();
    if(sharedCuts)if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
        // Compare point contacts against the uncut source footprint, outside
        // acceptance logic. A failed diagnostic must not replace the trial.
        try {
            std::vector<Polygon> domains=caps;for(const auto &source:sources)domains.push_back(source.domain);
            const auto original=meshPlateauFootprint(plateauRegionFootprint(domains,holes));
            const auto audit=auditStrictSurface(original);
            const auto output=std::string(path)+".uncut.json";
            writeSurfaceProbe(output.c_str(),original,{},audit);
            std::cout<<"PLATEAU_UNCUT_SOURCE triangles="<<original.faces.size()<<" nonmanifold="<<audit.exact.nonmanifoldEdges<<" links="<<audit.nonmanifoldVertices<<" crossings="<<audit.selfIntersections<<" overlaps="<<audit.coplanarOverlaps<<'\n';
        } catch(const std::exception &error) {
            std::cout<<"PLATEAU_UNCUT_SOURCE_PROBE_FAILED reason=\""<<error.what()<<"\"\n";
        }
    }
    if(const auto path=std::getenv("DW_CLIFF_CHUNK_SOURCE_PROBE")) {
        std::ofstream out(path);out.precision(17);
        out<<"{\"support\":"<<settings.support<<",\"canonical_quantum\":"<<1./65536
           <<",\"influence\":["<<work.lx<<','<<work.lz<<','<<work.hx<<','<<work.hz<<']';
        auto save=[&](const char *name,const std::vector<Polygon> &polygons,bool local) {
            out<<",\""<<name<<"\":[";size_t emitted=0;
            for(const auto &p:polygons) {
                if(local && !meets(bounds(p),halo))continue;
                if(emitted++)out<<',';out<<'[';
                for(size_t k=0;k<p.size();++k){if(k)out<<',';const auto q=p[k];out<<'['<<q.x<<','<<q.y<<','<<q.z<<']';}out<<']';
            }
            out<<']';
        };
        save("source",region.domains,true);save("caps",caps,false);save("holes",holes,false);out<<"}\n";
        if(!out)throw std::runtime_error("Cannot write local roof source fixture");
    }

    std::vector<Polygon> footprint;
    std::map<std::pair<int,int>,std::vector<size_t>> footprintBins;
    if(settings.continuous) {
        std::vector<Polygon> domains=caps;
        for(const auto &source:sources)domains.push_back(source.domain);
        footprint=bridgePlateauFootprintPinches(plateauRegionFootprint(domains));
        for(size_t i=0;i<footprint.size();++i) {
            const auto b=bounds(footprint[i]);
            for(int x=int(std::floor(b.lx));x<=int(std::floor(b.hx));++x)
                for(int z=int(std::floor(b.lz));z<=int(std::floor(b.hz));++z)footprintBins[{x,z}].push_back(i);
        }
    }
    std::map<std::pair<int,int>,Node> nodes;
    if(earlyTarget)std::cout<<"PLATEAU_EARLY_TARGET weight_scale=2 saturation_weight=.5 cold_source_endpoint=unchanged\n";
    auto node=[&](int x,int z) {
        const auto key=std::pair{x,z};auto found=nodes.find(key);if(found!=nodes.end())return found->second;
        const Vector3 p{float(x),0,float(z)};double d=1e30;for(const auto &cap:caps)d=std::min(d,distance(cap,p));
        Node n;
        double baseline=.12;std::set<size_t> visited;
        for(int bx=x-1;bx<=x;++bx)for(int bz=z-1;bz<=z;++bz){const auto at=bins.find({bx,bz});if(at!=bins.end())for(auto i:at->second)if(visited.insert(i).second && contains(sources[i].domain,p,settings.continuous?1e-9:0))baseline=std::max(baseline,sources[i].roof.at(p));}
        n.baseline=float(baseline);
        if(d<settings.support || sourceVertexBlend) {
            double target=result.landHeight;
            for(const auto &g:front) {
                double outside=0;
                for(size_t k=0;k<g.protectedRoof.size();++k){auto a=g.protectedRoof[k],b=g.protectedRoof[(k+1)%g.protectedRoof.size()];const double nx=double(a.z)-b.z,nz=double(b.x)-a.x,l=std::hypot(nx,nz);if(l)outside=std::max(outside,(nx*(double(p.x)-a.x)+nz*(double(p.z)-a.z))/l);}
                target=std::min(target,height(g.roof).at(p)+(g.outsideSlope>0?g.outsideSlope:1)*outside);
            }
            if(d<settings.support)for(const auto &g:lower)n.lower=std::max(n.lower,float(height(g.roof).at(p)-(g.outsideSlope>0?g.outsideSlope:2)*distance(g.protectedRoof,p)));
            target=std::max(target,double(n.lower));const double t=std::clamp(1-d/settings.support,0.,1.);
            n.delta=float((target-baseline)*t*t*(3-2*t));
            n.weight=float(t*t*(3-2*t));n.target=float(target);
            if(earlyTarget){n.weight=std::min(1.f,2*n.weight);n.delta=float((target-baseline)*n.weight);}
        }
        nodes.emplace(key,n);return n;
    };
    std::map<std::pair<int,int>,size_t> chunks;
    const int lx=int(std::floor(work.lx)),hx=int(std::ceil(work.hx)),lz=int(std::floor(work.lz)),hz=int(std::ceil(work.hz));
    for(int x=lx;x<hx;++x)for(int z=lz;z<hz;++z) {
        std::array<Vector3,4> points{{{float(x),0,float(z)},{float(x),0,float(z+1)},{float(x+1),0,float(z+1)},{float(x+1),0,float(z)}}};
        const std::array<Node,4> values{node(x,z),node(x,z+1),node(x+1,z+1),node(x+1,z)};
        for(const auto order:{std::array<int,3>{0,1,2},std::array<int,3>{0,2,3}}) {
            if(std::all_of(order.begin(),order.end(),[&](int k){return ((sourceNodeBlend||sourceVertexBlend)?values[k].weight==0:values[k].delta==0) && values[k].lower==.12f;}))continue;
            ++result.gridTriangles;Polygon grid,deltaPoints,lowerPoints,continuousPoints;
            for(auto k:order){grid.push_back(points[k]);auto p=points[k];p.y=values[k].delta;deltaPoints.push_back(p);p.y=values[k].lower;lowerPoints.push_back(p);p.y=std::max(values[k].baseline+values[k].delta,values[k].lower);continuousPoints.push_back(p);}
            const Height delta=height(deltaPoints),floor=height(lowerPoints);std::vector<std::pair<size_t,Polygon>> candidates;
            const auto found=bins.find({x,z});if(found!=bins.end())for(auto id:found->second){auto p=inside(sources[id].domain,grid);if(!p.empty())candidates.push_back({id,std::move(p)});}
            const auto key=std::pair{int(std::floor(double(x)/settings.side)),int(std::floor(double(z)/settings.side))};
            auto [at,added]=chunks.emplace(key,result.chunks.size());if(added)result.chunks.push_back({key.first,key.second,{}});
            auto emit=[&](const Polygon &p,Height baseline) {
                Height h{baseline.x+delta.x,baseline.z+delta.z,baseline.c+delta.c};
                const Height difference{h.x-floor.x,h.z-floor.z,h.c-floor.c};
                std::vector<std::pair<Polygon,Height>> pieces;
                if(std::abs(difference.x)+std::abs(difference.z)<1e-12)pieces.push_back({p,difference.c>=0?h:floor});
                else {
                    auto high=clip(p,-difference.x,-difference.z,difference.c);
                    if(settings.continuous) {
                        auto low=clip(p,difference.x,difference.z,-difference.c);
                        if(!low.empty())pieces.push_back({std::move(low),floor});
                    } else {
                        // One shared cut and its complement keep the source
                        // plane / lower-floor partition disjoint on the grid.
                        for(auto low:subtract(p,high.empty()?std::vector<Polygon>{}:std::vector<Polygon>{high},true))pieces.push_back({std::move(low),floor});
                    }
                    if(!high.empty())pieces.push_back({std::move(high),h});
                }
                for(const auto &[part,roof]:pieces)for(auto visible:subtract(part,holes,!settings.continuous)) {
                    for(auto &v:visible)v.y=float(roof.at(v));
                    result.chunks[at->second].cells.push_back({std::move(visible),plane(roof)});
                }
            };
            if(settings.continuous) {
                const auto roof=height(continuousPoints);
                const auto found=footprintBins.find({x,z});
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
                if(std::getenv("DW_CLIFF_POLYGON_CONTOURS")) {
                    std::vector<Polygon> parts;
                    if(found!=footprintBins.end())for(auto id:found->second) {
                        auto part=inside(footprint[id],grid);
                        if(!part.empty())parts.push_back(std::move(part));
                    }
                    // Discard artificial triangulation boundaries before
                    // building prisms or clipping cap faces against this field.
                    for(auto visible:plateauRegionFootprint(parts,holes)) {
                        for(auto &v:visible)v.y=float(roof.at(v));
                        result.chunks[at->second].cells.push_back({std::move(visible),plane(roof)});
                    }
                    continue;
                }
#endif
                if(found!=footprintBins.end())for(auto id:found->second) {
                    auto part=inside(footprint[id],grid);
                    if(!part.empty())for(auto visible:subtract(part,holes)) {
                        for(auto &v:visible)v.y=float(roof.at(v));
                        result.chunks[at->second].cells.push_back({std::move(visible),plane(roof)});
                    }
                }
                continue;
            }
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
            if(sharedOwnership) {
                auto deformed=[&](Height source) {
                    if(sourceVertexBlend)return source;
                    if(!sourceNodeBlend)return Height{source.x+delta.x,source.z+delta.z,source.c+delta.c};
                    if(std::all_of(order.begin(),order.end(),[&](int k){return values[k].weight==0;}))return source;
                    Polygon nodal;
                    for(auto k:order){auto p=points[k];const double original=source.at(p),w=values[k].weight;
                        p.y=float((1-w)*original+w*values[k].target);nodal.push_back(p);}
                    return height(nodal);
                };
                auto raw=[&](Polygon p,Height h) {
                    for(auto &v:p)v.y=float(h.at(v));
                    result.chunks[at->second].cells.push_back({std::move(p),plane(h)});
                    if(sharedCuts){chunkCuts.resize(result.chunks.size());chunkCuts[at->second].push_back(grid);}
                };
                // In the shared-cut mode no independently rounded clipped
                // outline reaches the arrangement: domain AND grid labels
                // define every cell in a single global scan.
                if(sharedCuts) {
                    const Height ownershipFloor=sourceVertexBlend?Height{0,0,.12}:floor;
                    if(found!=bins.end())for(auto owner:found->second) {
                        raw(sources[owner].domain,deformed(sources[owner].roof));raw(sources[owner].domain,ownershipFloor);
                    }
                    for(const auto &cap:caps)if(meets(bounds(cap),bounds(grid))){raw(cap,deformed({0,0,.12}));raw(cap,ownershipFloor);}
                    continue;
                }
                for(const auto &[owner,subject]:candidates) {
                    raw(subject,deformed(sources[owner].roof));raw(subject,floor);
                }
                for(const auto &cap:caps){auto p=inside(cap,grid);if(p.empty())continue;raw(p,deformed({0,0,.12}));raw(std::move(p),floor);}
                continue;
            }
#endif
            struct Owned {size_t owner;std::vector<Polygon> domains;};
            std::vector<Owned> ownership;
            for(const auto &[owner,subject]:candidates) {
                std::vector<Polygon> remaining{subject};
                for(auto &old:ownership) {
                    const auto a=sources[old.owner].roof,b=sources[owner].roof;
                    const Height d{b.x-a.x,b.z-a.z,b.c-a.c};
                    std::vector<Polygon> winning;
                    for(const auto &oldPart:old.domains)for(const auto &newPart:remaining) {
                        if(!meets(bounds(oldPart),bounds(newPart)))continue;
                        auto overlap=inside(oldPart,newPart);if(overlap.empty())continue;
                        if(std::abs(d.x)+std::abs(d.z)<1e-12) {
                            if(d.c>1e-9)winning.push_back(std::move(overlap));
                        } else {
                            auto high=clip(std::move(overlap),-d.x,-d.z,d.c);
                            if(!high.empty())winning.push_back(std::move(high));
                        }
                    }
                    if(!winning.empty())old.domains=plateauRegionFootprint(old.domains,winning);
                    // Subtract the final old region, not an independently
                    // rounded reverse height cut. All surviving ownership is
                    // carried forward into the next overlay operation.
                    if(!old.domains.empty())remaining=plateauRegionFootprint(remaining,old.domains);
                    if(remaining.empty())break;
                }
                if(!remaining.empty())ownership.push_back({owner,std::move(remaining)});
            }
            std::vector<Polygon> occupied;
            for(const auto &owned:ownership)for(const auto &part:owned.domains) {
                emit(part,sources[owned.owner].roof);occupied.push_back(part);
            }
            for(const auto &cap:caps){auto p=inside(cap,grid);if(p.empty())continue;for(const auto &part:subtract(p,occupied,true))emit(part,{0,0,.12});occupied.push_back(std::move(p));}
        }
    }
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(sharedOwnership) {
        std::vector<GradedRoofCell> inputs;
        for(const auto &chunk:result.chunks)for(const auto &cell:chunk.cells)inputs.push_back(cell);
        // Flatten paired cuts in the same chunk order as their roof cells.
        std::vector<Polygon> ownershipCuts;
        if(sharedCuts)for(const auto &cuts:chunkCuts)ownershipCuts.insert(ownershipCuts.end(),cuts.begin(),cuts.end());
        if(sharedCuts)if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
            const auto active=meshPlateauFootprint(plateauRegionFootprint(ownershipCuts));
            const auto output=std::string(path)+".grid.json";
            writeSurfaceProbe(output.c_str(),active,{},auditStrictSurface(active));
        }
        float vertexQuantum=0;auto vertexProtectedCuts=holes;
        if(sourceVertexBlend) {
            float extent=1;for(const auto &cell:inputs)for(auto p:cell.outline)extent=std::max({extent,std::abs(p.x),std::abs(p.z)});
            vertexQuantum=std::max(std::nextafter(extent,std::numeric_limits<float>::infinity())-extent,1.f/65536);
            auto turn=[](Vector3 a,Vector3 b,Vector3 c){return (double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);};
            for(auto &hole:vertexProtectedCuts) {
                if(hole.size()<3)throw std::runtime_error("Protected vertex cutout has no positive polygon");
                bool positive=false,negative=false;
                for(size_t k=0;k<hole.size();++k){const auto cross=turn(hole[k],hole[(k+1)%hole.size()],hole[(k+2)%hole.size()]);positive|=cross>0;negative|=cross<0;}
                if(positive && negative)throw std::runtime_error("Protected vertex cutout is not convex");
                Polygon points;
                for(auto p:hole)for(int x:{-1,1})for(int z:{-1,1})points.push_back({float(double(p.x)+x*vertexQuantum),0,float(double(p.z)+z*vertexQuantum)});
                std::sort(points.begin(),points.end(),[](auto a,auto b){return std::pair{a.x,a.z}<std::pair{b.x,b.z};});
                points.erase(std::unique(points.begin(),points.end(),[](auto a,auto b){return a.x==b.x && a.z==b.z;}),points.end());
                Polygon hull;
                for(auto p:points){while(hull.size()>1 && turn(hull[hull.size()-2],hull.back(),p)<=0)hull.pop_back();hull.push_back(p);}
                const auto lower=hull.size();
                for(auto p=points.rbegin()+1;p!=points.rend();++p){while(hull.size()>lower && turn(hull[hull.size()-2],hull.back(),*p)<=0)hull.pop_back();hull.push_back(*p);}
                if(!hull.empty())hull.pop_back();std::reverse(hull.begin(),hull.end());hole=std::move(hull);
            }
            std::cout<<"PLATEAU_VERTEX_CUT_CLEARANCE polygons="<<vertexProtectedCuts.size()<<" radius_m="<<vertexQuantum<<'\n';
        }
        auto partitioned=sourceVertexBlend?partitionPlateauGridOwnership(inputs,vertexProtectedCuts,ownershipCuts):partitionPlateauCellOwnership(inputs,holes,ownershipCuts);
        if(sourceVertexBlend) {
            // Give point-only contacts a finite construction. Near protected
            // cuts remove a tiny diamond; elsewhere add a source-owned link.
            // Both operations change geometry and retain every final guard.
            auto repairedInputs=inputs;auto repairedCuts=ownershipCuts;auto protectedCuts=vertexProtectedCuts;
            const float radius=2*vertexQuantum;
            std::vector<Polygon> activeGrids;std::set<std::vector<std::pair<float,float>>> seenGrids;
            for(const auto &grid:ownershipCuts) {
                std::vector<std::pair<float,float>> key;for(auto p:grid)key.emplace_back(p.x,p.z);std::sort(key.begin(),key.end());
                if(seenGrids.insert(key).second)activeGrids.push_back(grid);
            }
            for(int pass=0;pass<2;++pass) {
                std::vector<Polygon> domains;for(const auto &cell:partitioned)domains.push_back(cell.outline);
                const auto pinches=plateauFootprintPinches(domains);if(pinches.empty())break;
                size_t cuts=0,links=0;
                for(auto p:pinches) {
                    const Polygon diamond{{p.x-radius,0,p.z},{p.x,0,p.z+radius},{p.x+radius,0,p.z},{p.x,0,p.z-radius}};
                    bool protectedPoint=false;for(const auto &hole:holes)protectedPoint |= distance(hole,p)<=radius;
                    if(protectedPoint){protectedCuts.push_back(diamond);++cuts;continue;}
                    double highest=-1e30;Plane roof;
                    for(const auto &cell:partitioned)if(contains(cell.outline,p,0)) {
                        const double h=height(cell.roof).at(p);if(h>highest){highest=h;roof=cell.roof;}
                    }
                    if(highest<-1e20)throw std::runtime_error("Source point contact has no incident roof");
                    roof.distance+=.00002*planeNormal(roof)[1];
                    for(const auto &grid:activeGrids)if(meets(bounds(grid),bounds(diamond))) {
                        repairedInputs.push_back({diamond,roof});repairedCuts.push_back(grid);
                    }
                    ++links;
                }
                std::cout<<"PLATEAU_VERTEX_LINKS pass="<<pass<<" contacts="<<pinches.size()<<" protected_cuts="<<cuts<<" source_links="<<links<<" radius_m="<<radius<<" vertical_lift_m=.00002\n";
                partitioned=partitionPlateauGridOwnership(repairedInputs,protectedCuts,repairedCuts);
            }
            auto vertexField=[&](Vector3 p) {
                const int x=int(std::floor(p.x)),z=int(std::floor(p.z));
                const double u=double(p.x)-x,v=double(p.z)-z;
                Polygon weights,targets,floors;
                const std::array<Vector3,4> corners{{{float(x),0,float(z)},{float(x),0,float(z+1)},{float(x+1),0,float(z+1)},{float(x+1),0,float(z)}}};
                const auto indices=u<=v?std::array<int,3>{0,1,2}:std::array<int,3>{0,2,3};
                for(auto k:indices){auto q=corners[k];const auto n=node(int(q.x),int(q.z));q.y=n.weight;weights.push_back(q);q.y=n.target;targets.push_back(q);q.y=n.lower;floors.push_back(q);}
                return PlateauVertexField{plane(height(weights)),plane(height(targets)),plane(height(floors))};
            };
            if(retainedBand) {
                // The .12 cap-fill baseline is not retained original terrain.
                // Match genuine source slopes/offsets, including bounded source
                // ownership/link lifts; excluded cells must remain in support.
                std::map<std::pair<long long,long long>,std::vector<Height>> originalPlanes;
                auto key=[](Height h){return std::pair{std::llround(h.x*1e8),std::llround(h.z*1e8)};};
                for(const auto &source:sources)originalPlanes[key(source.roof)].push_back(source.roof);
                auto retained=[&](const Plane &roof) {
                    const auto h=height(roof);const auto [x,z]=key(h);
                    for(int dx=-1;dx<=1;++dx)for(int dz=-1;dz<=1;++dz) {
                        const auto at=originalPlanes.find({x+dx,z+dz});if(at==originalPlanes.end())continue;
                        for(const auto &p:at->second)if(std::abs(p.x-h.x)<=1e-9 && std::abs(p.z-h.z)<=1e-9 && std::abs(p.c-h.c)<=.0001)return true;
                    }
                    return false;
                };
                partitioned=envelopePlateauSelectedSourcePlanes(partitioned,vertexField,retained);
            } else partitioned=affineEnvelope?envelopePlateauSourcePlanes(partitioned,vertexField):blendPlateauSourceVertices(partitioned,vertexField);
        }
        result.chunks.clear();chunks.clear();
        for(const auto &cell:partitioned) {
            double x=0,z=0;for(auto p:cell.outline){x+=p.x;z+=p.z;}x/=cell.outline.size();z/=cell.outline.size();
            const auto key=std::pair{int(std::floor(x/settings.side)),int(std::floor(z/settings.side))};
            auto [at,added]=chunks.emplace(key,result.chunks.size());if(added)result.chunks.push_back({key.first,key.second,{}});
            result.chunks[at->second].cells.push_back(cell);
        }
    }
    if(settings.continuous && std::getenv("DW_CLIFF_POLYGON_CONTOURS")) {
        std::vector<Polygon> domains;
        for(const auto &chunk:result.chunks)for(const auto &cell:chunk.cells)domains.push_back(cell.outline);
        const auto conforming=improvePlateauFootprint(meshPlateauFootprint(domains));
        using Point=std::array<float,2>;using Edge=std::pair<Point,Point>;
        std::map<Edge,size_t> uses;
        for(const auto &f:conforming.faces)for(int k=0;k<3;++k) {
            Point a{f[k].x,f[k].z},b{f[(k+1)%3].x,f[(k+1)%3].z};if(b<a)std::swap(a,b);++uses[{a,b}];
        }
        std::vector<Edge> boundary;
        for(const auto &[edge,count]:uses)if(count==1)boundary.push_back(edge);
        struct Contact {Vector3 point;double height;};std::vector<Contact> contacts;
        const auto pinches=plateauFootprintPinches(domains);
        for(auto p:pinches) {
            double top=-1e30;
            for(const auto &cap:capVolumes) {
                double lo=-1e30,hi=1e30;bool inside=true;
                for(const auto &plane:cap.planes) {
                    const auto n=planeNormal(plane);const double d=plane.distance-n[0]*p.x-n[2]*p.z;
                    if(std::abs(n[1])<1e-14){if(d<0){inside=false;break;}}
                    else if(n[1]>0)hi=std::min(hi,d/n[1]);else lo=std::max(lo,d/n[1]);
                }
                if(inside && lo<hi)top=std::max(top,hi);
            }
            if(top>-1e20)contacts.push_back({p,top-.00002});
        }
        std::cout<<"PLATEAU_CAP_CONTACTS pinches="<<pinches.size()<<" covered="<<contacts.size()<<" vertical_overlap_m=.00002\n";
        std::map<std::pair<float,float>,float> heights;
        auto constrainedHeight=[&](Vector3 p) {
            const auto key=std::pair{p.x,p.z};if(auto found=heights.find(key);found!=heights.end())return found->second;
            const int x=int(std::floor(p.x)),z=int(std::floor(p.z));
            const double u=double(p.x)-x,v=double(p.z)-z;
            auto value=[&](int x,int z){const auto n=node(x,z);return double(std::max(n.baseline+n.delta,n.lower));};
            double h=u<=v?(1-v)*value(x,z)+(v-u)*value(x,z+1)+u*value(x+1,z+1):
                (1-u)*value(x,z)+v*value(x+1,z+1)+(u-v)*value(x+1,z);
            double boundaryDistance=1e30;
            for(const auto &[a,b]:boundary) {
                const double dx=double(b[0])-a[0],dz=double(b[1])-a[1],length=dx*dx+dz*dz;
                const double t=length?std::clamp(((double(p.x)-a[0])*dx+(double(p.z)-a[1])*dz)/length,0.,1.):0;
                boundaryDistance=std::min(boundaryDistance,std::hypot(double(p.x)-a[0]-t*dx,double(p.z)-a[1]-t*dz));
            }
            double capDistance=1e30,upper=1e30;
            for(const auto &g:lower) {
                const double d=distance(g.protectedRoof,p);capDistance=std::min(capDistance,d);
                upper=std::min(upper,height(g.roof).at(p)+std::max(d,boundaryDistance));
            }
            const double t=std::clamp(1-capDistance/settings.support,0.,1.),weight=t*t*(3-2*t);
            h-=weight*std::max(0.,h-upper);
            for(const auto &contact:contacts) {
                const double d=std::hypot(double(p.x)-contact.point.x,double(p.z)-contact.point.z);
                const double blend=std::clamp(1-d,0.,1.),w=blend*blend*(3-2*blend);
                h-=w*std::max(0.,h-contact.height-d);
            }
            const float rendered=float(h);heights.emplace(key,rendered);return rendered;
        };
        const auto refined=refinePlateauFootprint(conforming,constrainedHeight);
        result.chunks.clear();chunks.clear();
        for(auto face:refined.faces) {
            for(auto &p:face)p.y=constrainedHeight(p);
            Polygon outline{face[0],face[1],face[2]};const auto roof=height(outline);
            const double x=(double(face[0].x)+face[1].x+face[2].x)/3,z=(double(face[0].z)+face[1].z+face[2].z)/3;
            const auto key=std::pair{int(std::floor(x/settings.side)),int(std::floor(z/settings.side))};
            auto [at,added]=chunks.emplace(key,result.chunks.size());if(added)result.chunks.push_back({key.first,key.second,{}});
            result.chunks[at->second].cells.push_back({std::move(outline),plane(roof)});
        }
    }
#endif
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(simplifySourceEdges) {
        std::vector<GradedRoofCell> cells;for(const auto &chunk:result.chunks)cells.insert(cells.end(),chunk.cells.begin(),chunk.cells.end());
        std::vector<Polygon> original;for(const auto &p:region.domains)if(meets(bounds(p),halo))original.push_back(p);
        std::string certificate;
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")){const auto input=std::string(path)+".shared-input.chunks.json";writePlateauChunks(input.c_str(),result);certificate=std::string(path)+".shared-edges.json";}
        const auto simplified=sharedSourceEdges::simplify(cells,original,certificate.empty()?nullptr:certificate.c_str());
        result.chunks.clear();chunks.clear();
        for(const auto &cell:simplified) {
            double x=0,z=0;for(auto p:cell.outline){x+=p.x;z+=p.z;}x/=cell.outline.size();z/=cell.outline.size();
            const auto key=std::pair{int(std::floor(x/settings.side)),int(std::floor(z/settings.side))};
            auto [at,added]=chunks.emplace(key,result.chunks.size());if(added)result.chunks.push_back({key.first,key.second,{}});result.chunks[at->second].cells.push_back(cell);
        }
    }
    if(capConnected) {
        std::vector<GradedRoofCell> cells;for(const auto &chunk:result.chunks)cells.insert(cells.end(),chunk.cells.begin(),chunk.cells.end());
        std::string certificate;
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
            const auto input=std::string(path)+".cap-domain-input.chunks.json";writePlateauChunks(input.c_str(),result);
            certificate=std::string(path)+".cap-domain.json";
        }
        result.retainedSourceCells=capDomain::retainedSource(cells,caps,certificate.empty()?nullptr:certificate.c_str());
    }
    if(reuseSources) {
        std::vector<GradedRoofCell> cells;for(const auto &chunk:result.chunks)cells.insert(cells.end(),chunk.cells.begin(),chunk.cells.end());
        std::vector<Polygon> original;for(const auto &p:region.domains)if(meets(bounds(p),halo))original.push_back(p);
        const auto selection=sourceReuse::select(cells,original);
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
            const auto input=std::string(path)+".reuse-input.chunks.json";writePlateauChunks(input.c_str(),result);
            std::ofstream out(std::string(path)+".reuse.json");out.precision(17);out<<"{\"height_margin_m\":0.00002,\"height_margin_exact\":\"1/50000\",\"fan_minimum_interval_exact\":\"1/50000\",\"cells\":"<<cells.size()<<",\"plane_candidates\":"<<selection.planeCandidates<<",\"roof_planes\":[";
            for(size_t i=0;i<cells.size();++i){if(i)out<<',';const auto n=planeNormal(cells[i].roof);out<<'['<<n[0]<<','<<n[1]<<','<<n[2]<<','<<cells[i].roof.distance<<']';}out<<"],\"eligible\":[";
            bool first=true;for(size_t i=0;i<cells.size();++i)if(selection.eligible[i]){if(!first)out<<',';first=false;out<<i;}
            out<<"],\"guarded\":[";first=true;for(size_t i=0;i<cells.size();++i)if(selection.guarded[i]){if(!first)out<<',';first=false;out<<i;}out<<"]}\n";
            if(!out)throw std::runtime_error("Cannot write source reuse construction selection");
        }
        result.retainedSourceCells=selection.guarded;
        const size_t reused=std::count(selection.guarded.begin(),selection.guarded.end(),true);
        std::cout<<"PLATEAU_SOURCE_REUSE input_cells="<<cells.size()<<" plane_candidates="<<selection.planeCandidates<<" domain_rejected="<<selection.domainRejected<<" owner_rejected="<<selection.ownerRejected<<" transition_retained="<<selection.transitionRetained<<" pinch_retained="<<selection.pinchRetained<<" height_link_retained="<<selection.heightLinkRetained<<" original_backing_cells="<<reused<<" reconstructed_cells="<<cells.size()-reused<<" source_height_band_m=.00002\n";
    }
#endif
    result.chunks.erase(std::remove_if(result.chunks.begin(),result.chunks.end(),[](const auto &c){return c.cells.empty();}),result.chunks.end());
    result.gridNodes=nodes.size();return result;
}

void writePlateauChunks(const char *path,const PlateauChunkBuild &build) {
    std::ofstream out(path);out.precision(17);
    out<<"{\"regional_faces\":"<<build.regionalFaces<<",\"local_faces\":"<<build.localFaces<<",\"grid_triangles\":"<<build.gridTriangles<<",\"grid_nodes\":"<<build.gridNodes<<",\"land_height\":"<<build.landHeight<<",\"chunks\":[";
    for(size_t i=0;i<build.chunks.size();++i){if(i)out<<',';const auto &chunk=build.chunks[i];out<<"{\"x\":"<<chunk.x<<",\"z\":"<<chunk.z<<",\"cells\":[";
        for(size_t j=0;j<chunk.cells.size();++j){if(j)out<<',';out<<'[';for(size_t k=0;k<chunk.cells[j].outline.size();++k){if(k)out<<',';const auto p=chunk.cells[j].outline[k];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}out<<']';}out<<"]}";}
    out<<"]}\n";if(!out)throw std::runtime_error("Cannot write shared roof chunks");
}
}
