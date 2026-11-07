#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "FormationPrecision.hpp"
#include "raymath.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dw::rockFormations {
namespace {
thread_local bool preciseJoinActive=false,singleRoundJoinActive=false;
struct JoinArithmeticScope {
    bool previousPrecise=preciseJoinActive,previousSingle=singleRoundJoinActive;
    JoinArithmeticScope() {
        const bool single=std::getenv("DW_CLIFF_JOIN_SINGLE_ROUND")!=nullptr;
        const bool precise=single || std::getenv("DW_CLIFF_PRECISE_JOIN")!=nullptr;
#ifndef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        if(precise)throw std::runtime_error("Precise join requires DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT");
#endif
        preciseJoinActive=precise;singleRoundJoinActive=single;
    }
    ~JoinArithmeticScope(){preciseJoinActive=previousPrecise;singleRoundJoinActive=previousSingle;}
};
bool preciseJoin(){return preciseJoinActive;}
Plane joinPlane(const Polygon &p) {
    std::array<double,3> best{};double magnitude=0;
    for(size_t i=1;i+1<p.size();++i) {
        const double ax=double(p[i].x)-p[0].x,ay=double(p[i].y)-p[0].y,az=double(p[i].z)-p[0].z,
                     bx=double(p[i+1].x)-p[0].x,by=double(p[i+1].y)-p[0].y,bz=double(p[i+1].z)-p[0].z;
        const std::array<double,3> n{ay*bz-az*by,az*bx-ax*bz,ax*by-ay*bx};
        const double length=std::hypot(n[0],n[1],n[2]);if(length>magnitude){magnitude=length;best=n;}
    }
    if(magnitude==0)throw std::runtime_error("Degenerate retained terrain plane");
    for(auto &n:best)n/=magnitude;
    Plane result;result.preciseNormal=best;result.hasPreciseNormal=true;
    result.normal={float(best[0]),float(best[1]),float(best[2])};result.distance=planeProjection(result,p[0]);return result;
}
Plane joinSide(Vector3 a,Vector3 b) {
    const double x=double(a.z)-b.z,z=double(b.x)-a.x,length=std::hypot(x,z);
    if(length==0)throw std::runtime_error("Degenerate retained terrain side");
    Plane p;p.hasPreciseNormal=true;p.preciseNormal={x/length,0,z/length};
    p.normal={float(p.preciseNormal[0]),0,float(p.preciseNormal[2])};p.distance=planeProjection(p,a);return p;
}
std::vector<Polygon> joinExposed(Polygon p,const std::vector<Volume> &v,int owner=-1) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(singleRoundJoinActive)return exposedSingleRound(std::move(p),v,owner);
    if(preciseJoin())return exposedPrecise(std::move(p),v,owner);
#endif
    return exposed(std::move(p),v,owner);
}
Polygon joinClip(Polygon p,const Volume &v) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(singleRoundJoinActive)return clipToVolumeSingleRound(std::move(p),v);
    if(preciseJoin())return clipToVolumePrecise(std::move(p),v);
#endif
    return clipToVolume(std::move(p),v);
}
float polygonArea(const Polygon &p) {
    float area=0;
    for(size_t i=1;i+1<p.size();++i) area+=Vector3Length(Vector3CrossProduct(sub(p[i],p[0]),sub(p[i+1],p[0])))*.5f;
    return area;
}
struct OutsideSections {
    struct Entry {Polygon surface;Volume below;bool enters=false;float lx,hx,lz,hz;};
    std::vector<Entry> entries;
    Box bounds;
    OutsideSections(const std::vector<Polygon> &outside,Box box):bounds(box) {
        for(auto p:outside) {
            Entry e;e.lx=e.lz=1e9f;e.hx=e.hz=-1e9f;
            for(auto a:p) {e.lx=std::min(e.lx,a.x);e.hx=std::max(e.hx,a.x);e.lz=std::min(e.lz,a.z);e.hz=std::max(e.hz,a.z);}
            if(e.hx<box.min.x-.0001f || e.lx>box.max.x+.0001f || e.hz<box.min.z-.0001f || e.lz>box.max.z+.0001f) continue;
            Vector3 n{};for(size_t i=1;i+1<p.size();++i) n=add(n,Vector3CrossProduct(sub(p[i],p[0]),sub(p[i+1],p[0])));
            n=Vector3Normalize(n);if(std::abs(n.y)<1e-7f) continue;
            e.enters=n.y>0;e.surface=p;
            if(n.y<0) {std::reverse(p.begin(),p.end());n=mul(n,-1);}
            e.below.planes.push_back(preciseJoin()?joinPlane(p):Plane{n,projection(n,p[0])});
            for(size_t i=0;i<p.size();++i) {
                auto a=p[i],b=p[(i+1)%p.size()];auto side=Vector3Normalize(Vector3{a.z-b.z,0,b.x-a.x});
                e.below.planes.push_back(preciseJoin()?joinSide(a,b):Plane{side,projection(side,a)});
            }
            entries.push_back(std::move(e));
        }
    }
    bool inside(Vector3 p,const std::vector<size_t> &candidates) const {
        double nearest=1e9;bool rock=false;
        for(auto id:candidates) {
            const auto &e=entries[id];
            for(size_t k=1;k+1<e.surface.size();++k) {
                const auto a=e.surface[0],b=e.surface[k],c=e.surface[k+1];
                const double determinant=(double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);
                if(std::abs(determinant)<1e-12) continue;
                const double u=((double(p.x)-a.x)*(double(c.z)-a.z)-(double(p.z)-a.z)*(double(c.x)-a.x))/determinant;
                const double v=((double(b.x)-a.x)*(double(p.z)-a.z)-(double(b.z)-a.z)*(double(p.x)-a.x))/determinant;
                if(u < -1e-6 || v < -1e-6 || u+v>1+1e-6) continue;
                const double height=a.y+u*(double(b.y)-a.y)+v*(double(c.y)-a.y);
                if(height>=p.y-.00001 && height<nearest) {nearest=height;rock=e.enters;}
            }
        }
        return rock;
    }
    bool covers(const std::array<Vector3,2> &edge) const {
        for(int axis:{0,2})for(int side:{0,1}) {
            const float value=axis==0?(side?bounds.max.x:bounds.min.x):(side?bounds.max.z:bounds.min.z);
            auto coordinate=[&](Vector3 p){return axis==0?p.x:p.z;};
            if(std::abs(coordinate(edge[0])-value)>.0001f || std::abs(coordinate(edge[1])-value)>.0001f)continue;
            auto a=edge[0],b=edge[1];
            if(axis==0)a.x=b.x=value+(side?1:-1)*.00001f;
            else a.z=b.z=value+(side?1:-1)*.00001f;
            std::vector<size_t> candidates;
            std::vector<double> cuts{0,1};
            for(size_t i=0;i<entries.size();++i) {
                const auto &e=entries[i];
                if(e.hx<std::min(a.x,b.x)-.00002f || e.lx>std::max(a.x,b.x)+.00002f ||
                   e.hz<std::min(a.z,b.z)-.00002f || e.lz>std::max(a.z,b.z)+.00002f)continue;
                candidates.push_back(i);
                for(const auto &plane:e.below.planes) {
                    const double first=planeProjection(plane,a)-plane.distance;
                    const double last=planeProjection(plane,b)-plane.distance;
                    if(std::abs(first-last)<1e-14)continue;
                    const double t=first/(first-last);
                    if(t>0 && t<1)cuts.push_back(t);
                }
            }
            if(candidates.empty())continue;
            std::sort(cuts.begin(),cuts.end());
            bool covered=true;
            for(size_t i=1;i<cuts.size();++i) {
                if(cuts[i]-cuts[i-1]<1e-10)continue;
                const auto p=Vector3Lerp(a,b,float((cuts[i]+cuts[i-1])*.5));
                if(!inside(p,candidates)){covered=false;break;}
            }
            if(covered)return true;
        }
        return false;
    }
    std::vector<Polygon> expose(const Polygon &p,bool keepInside=false) const {
        bool border=false;
        for(int axis:{0,2}) for(float value:axis==0 ? std::array<float,2>{bounds.min.x,bounds.max.x} : std::array<float,2>{bounds.min.z,bounds.max.z})
            border |= std::all_of(p.begin(),p.end(),[&](auto a){return std::abs((axis==0 ? a.x : a.z)-value)<.00003f;});
        if(!border) return {p};
        float lx=1e9f,hx=-1e9f,lz=1e9f,hz=-1e9f;
        for(auto a:p) {lx=std::min(lx,a.x);hx=std::max(hx,a.x);lz=std::min(lz,a.z);hz=std::max(hz,a.z);}
        std::vector<size_t> candidates;
        for(size_t i=0;i<entries.size();++i) if(entries[i].hx>=lx-.00002f && entries[i].lx<=hx+.00002f && entries[i].hz>=lz-.00002f && entries[i].lz<=hz+.00002f) candidates.push_back(i);
        std::vector<Polygon> parts{p};
        for(auto id:candidates) {
            std::vector<Polygon> split;
            for(auto part:parts) {
                auto cut=joinClip(part,entries[id].below);
                const float cutArea=polygonArea(cut),partArea=polygonArea(part);
                if(cut.size()<3 || cutArea<1e-10f || std::abs(cutArea-partArea)<std::max(1e-10f,partArea*1e-6f)) {split.push_back(std::move(part));continue;}
                for(auto other:joinExposed(part,{entries[id].below})) split.push_back(std::move(other));
                split.push_back(std::move(cut));
            }
            parts=std::move(split);
        }
        std::vector<Polygon> visible;
        for(auto part:parts) {
            Vector3 center{};for(auto a:part) center=add(center,a);center=mul(center,1.f/part.size());
            if(inside(center,candidates)==keepInside) visible.push_back(std::move(part));
        }
        return visible;
    }
};
struct Caps {
    std::vector<Volume> solids;
    std::vector<float> heights;
    std::vector<size_t> sources;
    std::map<std::pair<int,int>,std::vector<size_t>> cells;
    static constexpr float Step=2.5f;
    explicit Caps(const std::vector<Polygon> &surface,bool steep=false) {
        for(size_t source=0;source<surface.size();++source) {
            const auto &p=surface[source];
            Vector3 n{};
            for(size_t i=1;i+1<p.size();++i) n=add(n,Vector3CrossProduct(sub(p[i],p[0]),sub(p[i+1],p[0])));
            n=Vector3Normalize(n);
            // Rebuild the upward envelope, including steep bevel/riser pieces.
            // Each piece is a CLOSED prism, so its side faces also participate
            // in the union. Treating only broad caps leaves narrow vertical gaps.
            if(n.y<(steep?.00000001f:.0001f)) continue;
            Volume v;
            v.planes.push_back(preciseJoin()?joinPlane(p):Plane{n,projection(n,p[0])});
            float lx=1e9f,hx=-1e9f,lz=1e9f,hz=-1e9f,hy=-1e9f;
            // Upward winding is clockwise when projected onto x/z.
            for(size_t i=0;i<p.size();++i) {
                auto a=p[i],b=p[(i+1)%p.size()];
                auto side=Vector3Normalize(Vector3{a.z-b.z,0,b.x-a.x});
                v.planes.push_back(preciseJoin()?joinSide(a,b):Plane{side,projection(side,a)});
                lx=std::min(lx,a.x); hx=std::max(hx,a.x);
                lz=std::min(lz,a.z); hz=std::max(hz,a.z); hy=std::max(hy,a.y);
            }
            v.planes.push_back({{0,-1,0},.12f});
            v.faces.push_back(p);
            Polygon bottom=p;
            for(auto &a:bottom) a.y=-.12f;
            std::reverse(bottom.begin(),bottom.end());
            v.faces.push_back(bottom);
            for(size_t i=0;i<p.size();++i) {
                auto a=p[i],b=p[(i+1)%p.size()],loA=a,loB=b;
                loA.y=loB.y=-.12f;
                v.faces.push_back({a,loA,loB,b});
            }
            const size_t id=solids.size();
            solids.push_back(std::move(v)); heights.push_back(hy); sources.push_back(source);
            for(int z=int(std::floor(lz/Step));z<=int(std::floor(hz/Step));++z)
                for(int x=int(std::floor(lx/Step));x<=int(std::floor(hx/Step));++x)
                    cells[{x,z}].push_back(id);
        }
    }
    bool coversEdge(const std::array<Vector3,2> &edge) const {
        std::vector<std::pair<double,double>> intervals;
        for(const auto &solid:solids) {
            double begin=0,end=1;
            for(const auto &plane:solid.planes) {
                const double first=planeProjection(plane,edge[0])-plane.distance-.00002;
                const double change=planeProjection(plane,sub(edge[1],edge[0]));
                if(std::abs(change)<1e-14){if(first>0){begin=1;end=0;break;}continue;}
                if(change>0)end=std::min(end,-first/change);else begin=std::max(begin,-first/change);
            }
            if(end>=begin)intervals.push_back({begin,end});
        }
        std::sort(intervals.begin(),intervals.end());double covered=0;
        for(auto [begin,end]:intervals){if(begin>covered+1e-9)return false;covered=std::max(covered,end);if(covered>=1)return true;}
        return false;
    }
    std::vector<Polygon> expose(const Polygon &p, size_t source=size_t(-1),bool floor=false) const {
        float lx=1e9f,hx=-1e9f,lz=1e9f,hz=-1e9f,ly=1e9f;
        for(auto a:p) {
            lx=std::min(lx,a.x);hx=std::max(hx,a.x);lz=std::min(lz,a.z);hz=std::max(hz,a.z);ly=std::min(ly,a.y);
        }
        std::set<size_t> ids;
        for(int z=int(std::floor(lz/Step));z<=int(std::floor(hz/Step));++z)
            for(int x=int(std::floor(lx/Step));x<=int(std::floor(hx/Step));++x) {
                auto found=cells.find({x,z});
                if(found!=cells.end()) for(auto id:found->second) if(heights[id]>=ly-.00002f) ids.insert(id);
            }
        std::vector<Volume> candidates;
        int owner=source==size_t(-1) && !floor ? -2 : -1;
        for(auto id:ids) {
            if(sources[id]==source) owner=int(candidates.size());
            candidates.push_back(solids[id]);
        }
        // The new surface wins coincident outward caps; retained faces are
        // subsequently cut against the new solids, so exactly one copy remains.
        return joinExposed(p,candidates,owner);
    }
    bool onTop(Vector3 p) const {
        const int x=int(std::floor(p.x/Step)),z=int(std::floor(p.z/Step));
        for(int dz=-1;dz<=1;++dz) for(int dx=-1;dx<=1;++dx) {
            auto found=cells.find({x+dx,z+dz});
            if(found==cells.end()) continue;
            for(auto id:found->second) {
                const auto &planes=solids[id].planes;
                if(std::abs(planeProjection(planes[0],p)-planes[0].distance)>.0003) continue;
                bool inside=true;
                for(size_t i=1;i+1<planes.size();++i)
                    inside &= planeProjection(planes[i],p)<=planes[i].distance+.0003;
                if(inside) return true;
            }
        }
        return false;
    }
};
bool onOutsideSurface(Vector3 p,const std::vector<Polygon> &outside) {
    for(const auto &polygon:outside) {
        float lx=1e9f,hx=-1e9f,ly=1e9f,hy=-1e9f,lz=1e9f,hz=-1e9f;
        for(auto v:polygon) {lx=std::min(lx,v.x);hx=std::max(hx,v.x);ly=std::min(ly,v.y);hy=std::max(hy,v.y);lz=std::min(lz,v.z);hz=std::max(hz,v.z);}
        if(p.x<lx-.0003f || p.x>hx+.0003f || p.y<ly-.0003f || p.y>hy+.0003f || p.z<lz-.0003f || p.z>hz+.0003f) continue;
        for(size_t i=1;i+1<polygon.size();++i) {
            const std::array<Vector3,3> tri{polygon[0],polygon[i],polygon[i+1]};
            auto n=Vector3CrossProduct(sub(tri[1],tri[0]),sub(tri[2],tri[0]));
            if(Vector3Length(n)<1e-10f) continue;
            n=Vector3Normalize(n);
            if(std::abs(dot(n,sub(p,tri[0])))>.0003f) continue;
            bool inside=true;
            for(int k=0;k<3;++k) {
                auto e=sub(tri[(k+1)%3],tri[k]);
                inside &= dot(n,Vector3CrossProduct(e,sub(p,tri[k])))>=-.0003f*Vector3Length(e);
            }
            if(inside) return true;
        }
    }
    return false;
}
void repairNumericalSlits(cliffOptions::Mesh &mesh,const Caps &caps,Experiment &rocks) {
    const auto edges=surfaceBoundary(mesh,true);
    using Key=std::array<float,3>;
    auto key=[](Vector3 p){return Key{p.x,p.y,p.z};};
    std::map<Key,std::vector<size_t>> next;
    for(size_t i=0;i<edges.size();++i) next[key(edges[i][0])].push_back(i);
    std::set<size_t> visited;
    for(size_t first=0;first<edges.size();++first) {
        if(visited.contains(first)) continue;
        Polygon loop;
        size_t at=first;
        bool closed=false;
        for(size_t step=0;step<64;++step) {
            if(visited.contains(at)) {closed=at==first;break;}
            visited.insert(at);loop.push_back(edges[at][0]);
            auto found=next.find(key(edges[at][1]));
            if(found==next.end() || found->second.size()!=1) break;
            at=found->second.front();
        }
        if(!closed || loop.size()<3) continue;
        Vector3 a{},b{}; float longest=0;
        for(auto p:loop) for(auto q:loop) if(distance(p,q)>longest) {longest=distance(p,q);a=p;b=q;}
        if(longest<.0001f) continue;
        auto axis=Vector3Normalize(sub(b,a));
        float width=0;
        for(auto p:loop) width=std::max(width,Vector3Length(Vector3CrossProduct(sub(p,a),axis)));
        if(width>.003f)continue;
        std::reverse(loop.begin(),loop.end());
        Vector3 center{}; for(auto p:loop) center=add(center,p); center=mul(center,1.f/loop.size());
        std::vector<cliffOptions::Triangle> patch;
        bool valid=true;
        size_t samples=0;
        for(size_t i=0;i<loop.size();++i) {
            const cliffOptions::Triangle tri{center,loop[i],loop[(i+1)%loop.size()]};
            auto n=Vector3CrossProduct(sub(tri[1],tri[0]),sub(tri[2],tri[0]));
            if(Vector3Length(n)<1e-10f) {valid=false;break;}
            n=Vector3Normalize(n);
            for(auto p:{mul(add(add(tri[0],tri[1]),tri[2]),1.f/3),mul(add(tri[0],tri[1]),.5f),mul(add(tri[0],tri[2]),.5f)}) {
                const auto from=add(p,mul(n,.02f));
                const float expected=std::min(traceVolumes(rocks.volumes,from,mul(n,-1)),traceVolumes(caps.solids,from,mul(n,-1)));
                valid &= std::abs(expected-.02f)<.0003f;
                ++samples;
            }
            patch.push_back(tri);
        }
        // Fill only a narrow CLOSED loop independently confirmed to lie on the
        // desired solid boundary. True openings or recesses fail this oracle.
        if(!valid) continue;
        mesh.faces.insert(mesh.faces.end(),patch.begin(),patch.end());
        ++rocks.repairedSlits; rocks.repairSamples+=samples;
        std::cout<<"PLATEAU_SLIT_REPAIR width_m="<<width<<" triangles="<<patch.size()<<" oracle_samples="<<samples<<'\n';
    }
}

}
bool buriedContextBoundary(const std::array<Vector3,2> &edge,const std::vector<Polygon> &outside,Box bounds) {
    JoinArithmeticScope arithmetic;
    return OutsideSections(outside,bounds).covers(edge);
}
static cliffOptions::Mesh assembleSurfaceImpl(const std::vector<Polygon> &retained, Experiment &rocks, const std::vector<Polygon> &outside,bool closeContext=false) {
    ConstructionTiming stageTiming("join");
    JoinArithmeticScope arithmetic;
    if(const auto path=std::getenv("DW_CLIFF_ADAPTER_FIXTURE")) {
        std::ofstream out(std::string(path)+".margin-"+std::to_string(rocks.editMargin)+(closeContext?".closed-context":""));out.precision(17);
        const auto &b=rocks.editBounds;
        out<<"DWADAPTER2\n"<<closeContext<<' '<<preciseJoin()<<' '<<singleRoundJoinActive<<' '<<worldGridActive<<' '
           <<worldGridOrigin.x<<' '<<worldGridOrigin.y<<' '<<worldGridOrigin.z<<' '<<rocks.seededComposition<<'\n'
           <<b.min.x<<' '<<b.min.y<<' '<<b.min.z<<' '<<b.max.x<<' '<<b.max.y<<' '<<b.max.z<<'\n';
        for(const auto flag:{"DW_CLIFF_ROOF_SHELL","DW_CLIFF_EAR_WELD","DW_CLIFF_EXACT_CONTACTS","DW_CLIFF_JOINT_TERRAIN_JOIN","DW_CLIFF_JOINT_WHOLE_SOURCE"})out<<(std::getenv(flag)!=nullptr)<<' ';
        out<<'\n';
        auto save=[&](const std::vector<Polygon> &polys){out<<polys.size()<<'\n';for(const auto &p:polys){out<<p.size();for(auto v:p)out<<' '<<v.x<<' '<<v.y<<' '<<v.z;out<<'\n';}};
        save(retained);
        std::vector<Polygon> nearby;
        for(const auto &p:outside){float lx=1e30f,lz=1e30f,hx=-1e30f,hz=-1e30f;for(auto v:p){lx=std::min(lx,v.x);hx=std::max(hx,v.x);lz=std::min(lz,v.z);hz=std::max(hz,v.z);}if(hx>=b.min.x-.001f && lx<=b.max.x+.001f && hz>=b.min.z-.001f && lz<=b.max.z+.001f)nearby.push_back(p);}
        save(nearby);save(rocks.protectedFloor);
        out<<rocks.mesh.faces.size()<<'\n';for(const auto &f:rocks.mesh.faces){for(auto v:f)out<<v.x<<' '<<v.y<<' '<<v.z<<' ';out<<'\n';}
        out<<rocks.volumes.size()<<'\n';for(const auto &v:rocks.volumes){out<<v.planes.size()<<'\n';for(const auto &p:v.planes){const auto n=planeNormal(p);out<<n[0]<<' '<<n[1]<<' '<<n[2]<<' '<<p.distance<<'\n';}save(v.faces);}
        if(!out)throw std::runtime_error("Cannot save full terrain adapter fixture");
    }
    const auto original=weldSurface(retained);
    const auto expectedBoundary=surfaceBoundary(original);
    const bool wholeSource=std::getenv("DW_CLIFF_JOINT_WHOLE_SOURCE")!=nullptr;
    Caps caps(retained,closeContext || wholeSource);
    Caps context(outside);
    Caps floors(rocks.protectedFloor);
    OutsideSections sections(outside,rocks.editBounds);
    std::vector<Polygon> assembled;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(std::getenv("DW_CLIFF_JOINT_TERRAIN_JOIN")) {
        const auto joint=solidBooleanTerrainJoin(caps.solids,rocks.mesh);
        for(const auto &f:joint.faces)assembled.push_back({f[0],f[1],f[2]});
    } else
#endif
    {
    for(const auto &face:rocks.mesh.faces)
        for(auto p:caps.expose({face[0],face[1],face[2]})) assembled.push_back(std::move(p));
    // The old deformed skins are not reliable solids. Rebuild the selected
    // terrain from its upward caps, including their real vertical side faces.
    // Union those solids instead of leaving holes where skin intersections end.
    for(size_t i=0;i<caps.solids.size();++i)
        for(const auto &face:caps.solids[i].faces)
            for(auto p:joinExposed(face,rocks.volumes))
                for(auto surface:caps.expose(p,caps.sources[i])) assembled.push_back(std::move(surface));
    }
    std::vector<Polygon> contextClosure;
    if(closeContext && !wholeSource) {
        const auto box=rocks.editBounds;
        float high=box.max.y+1;
        for(const auto &p:outside)for(auto v:p)high=std::max(high,v.y+1);
        std::vector<Polygon> curtains{
            {{box.min.x,-.12f,box.min.z},{box.min.x,high,box.min.z},{box.min.x,high,box.max.z},{box.min.x,-.12f,box.max.z}},
            {{box.max.x,-.12f,box.max.z},{box.max.x,high,box.max.z},{box.max.x,high,box.min.z},{box.max.x,-.12f,box.min.z}},
            {{box.min.x,-.12f,box.min.z},{box.max.x,-.12f,box.min.z},{box.max.x,high,box.min.z},{box.min.x,high,box.min.z}},
            {{box.max.x,-.12f,box.max.z},{box.min.x,-.12f,box.max.z},{box.min.x,high,box.max.z},{box.max.x,high,box.max.z}}};
        size_t added=0;
        for(const auto &curtain:curtains)for(auto oldSolid:sections.expose(curtain,true))
            for(auto notRock:joinExposed(oldSolid,rocks.volumes))
                for(auto oldOnly:caps.expose(notRock,size_t(-1),true)) {contextClosure.push_back(std::move(oldOnly));++added;}
        std::cout<<"PLATEAU_CONTEXT_CLOSURE old_minus_new_panels="<<added<<'\n';
    }
    std::vector<Polygon> visible;
    for(const auto &p:assembled) {
        Vector3 n{};
        for(size_t i=1;i+1<p.size();++i) n=add(n,Vector3CrossProduct(sub(p[i],p[0]),sub(p[i+1],p[0])));
        // The finite diagnostic patch meets the existing ground/terrain along
        // its perimeter. Its buried foundation is deliberately not rendered.
        if(n.y<0 && std::all_of(p.begin(),p.end(),[](auto a){return a.y<-.1199f;})) continue;
        // Original floor faces are rendered unchanged elsewhere. Remove the
        // reconstructed rock sides buried beneath those floor solids too;
        // otherwise four invisible side strips can meet on a floor corner.
        for(auto aboveFloor:floors.expose(p,size_t(-1),true)) {
            const auto parts=wholeSource?context.expose(aboveFloor,size_t(-1),true):sections.expose(aboveFloor);
            for(auto part:parts)visible.push_back(std::move(part));
        }
    }
    for(const auto &panel:contextClosure)for(auto part:floors.expose(panel,size_t(-1),true))visible.push_back(std::move(part));
    const auto oldSlits=rocks.repairedSlits,oldSamples=rocks.repairSamples;
    auto finish=[&](float tolerance) {
        rocks.repairedSlits=oldSlits;rocks.repairSamples=oldSamples;
        auto result=weldSurface(visible,tolerance,std::getenv("DW_CLIFF_ROOF_SHELL")!=nullptr);
        repairNumericalSlits(result,caps,rocks);
        rocks.strictAssembledAudit=auditStrictSurface(result);
        rocks.assembledAudit=rocks.strictAssembledAudit.exact;
        if(const auto path=std::getenv("DW_CLIFF_ASSEMBLY_PROBE")) {
            static std::set<std::string> written;
            if(written.insert(path).second) {
                auto sources=rocks.volumes;sources.insert(sources.end(),caps.solids.begin(),caps.solids.end());
                writeSurfaceProbe(path,result,sources,rocks.strictAssembledAudit);
                std::ofstream out(std::string(path)+".context.json");out.precision(17);
                out<<"{\"tolerance\":"<<tolerance<<",\"close_context\":"<<closeContext<<",\"precise_join\":"<<preciseJoin()
                   <<",\"single_round\":"<<singleRoundJoinActive
                   <<",\"edit_bounds\":["<<rocks.editBounds.min.x<<','<<rocks.editBounds.min.z<<','<<rocks.editBounds.max.x<<','<<rocks.editBounds.max.z<<']'
                   <<",\"retained_source_count\":"<<retained.size()<<",\"outside_source_count\":"<<outside.size();
                auto save=[&](const char *name,const std::vector<Polygon> &faces) {
                    out<<",\""<<name<<"\":[";
                    size_t emitted=0;
                    for(size_t f=0;f<faces.size();++f){
                        if(std::string(name)=="outside") {
                            float lx=1e30f,lz=1e30f,hx=-1e30f,hz=-1e30f;
                            for(auto p:faces[f]){lx=std::min(lx,p.x);hx=std::max(hx,p.x);lz=std::min(lz,p.z);hz=std::max(hz,p.z);}
                            if(hx<rocks.editBounds.min.x-.001f || lx>rocks.editBounds.max.x+.001f || hz<rocks.editBounds.min.z-.001f || lz>rocks.editBounds.max.z+.001f)continue;
                        }
                        if(emitted++)out<<',';out<<'[';for(size_t k=0;k<faces[f].size();++k){if(k)out<<',';const auto p=faces[f][k];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}out<<']';}out<<']';
                };
                save("retained",retained);save("outside",outside);out<<"}\n";
                if(!out)throw std::runtime_error("Cannot write assembly source context");
            }
        }
        if(std::getenv("DW_CLIFF_EDGE_PROBE") && rocks.assembledAudit.nonmanifoldEdges && tolerance==.00008f) {
            using Point=std::array<float,3>;
            std::map<std::pair<Point,Point>,std::vector<size_t>> edges;
            for(size_t i=0;i<result.faces.size();++i)for(int k=0;k<3;++k) {
                auto a=result.faces[i][k],b=result.faces[i][(k+1)%3];
                Point p{a.x,a.y,a.z},q{b.x,b.y,b.z};if(q<p)std::swap(p,q);
                edges[{p,q}].push_back(i);
            }
            size_t reported=0;
            for(const auto &[edge,faces]:edges)if(faces.size()>2 && reported++<2) {
                std::cout<<"EDGE_PROBE bounds="<<rocks.editBounds.min.x<<','<<rocks.editBounds.max.x<<','<<rocks.editBounds.min.z<<','<<rocks.editBounds.max.z<<'\n';
                for(auto i:faces){std::cout<<"EDGE_TRI";for(auto p:result.faces[i])std::cout<<' '<<p.x<<','<<p.y<<','<<p.z;std::cout<<'\n';}
            }
        }
        if(std::getenv("DW_CLIFF_EDGE_PROBE") && tolerance==.0003f)for(auto edge:surfaceBoundary(result)) {
            const auto &b=rocks.editBounds;
            if(std::all_of(edge.begin(),edge.end(),[&](auto p){return std::hypot(p.x-b.max.x,p.z-b.min.z)<.2f;})) {
                std::cout<<"JOIN_CORNER_EDGE";for(auto p:edge)std::cout<<' '<<p.x<<','<<p.y<<','<<p.z;std::cout<<'\n';
            }
        }
        rocks.intentionalBoundaryEdges=rocks.unexpectedBoundaryEdges=0;
        rocks.contextBoundaryEdges=rocks.foundationBoundaryEdges=rocks.buriedContextEdges=rocks.floorBoundaryEdges=0;
        for(const auto &edge:surfaceBoundary(result)) {
            const bool foundation=edge[0].y<-.1197f && edge[1].y<-.1197f;
            bool meetsContext=true;
            for(auto p:{edge[0],mul(add(edge[0],edge[1]),.5f),edge[1]}) meetsContext &= context.onTop(p);
            if(!foundation && !meetsContext) {
                meetsContext=true;
                for(auto p:{edge[0],mul(add(edge[0],edge[1]),.5f),edge[1]}) meetsContext &= onOutsideSurface(p,outside);
            }
            const auto &bounds=rocks.editBounds;
            bool border=false;
            for(auto coordinate:{0,2}) {
                const auto first=coordinate==0 ? edge[0].x : edge[0].z;
                const auto second=coordinate==0 ? edge[1].x : edge[1].z;
                const auto lo=coordinate==0 ? bounds.min.x : bounds.min.z;
                const auto hi=coordinate==0 ? bounds.max.x : bounds.max.z;
                border |= (std::abs(first-lo)<.0003f && std::abs(second-lo)<.0003f) || (std::abs(first-hi)<.0003f && std::abs(second-hi)<.0003f);
            }
            const bool buriedBorder=border && std::max(edge[0].y,edge[1].y)<=CanyonTerrain::WalkableHeight+.0003f;
            const bool buriedContext=border && !foundation && !meetsContext && sections.covers(edge);
            const bool floorInterface=!foundation && !meetsContext && floors.coversEdge(edge);
            if(foundation || meetsContext || buriedBorder || buriedContext || floorInterface) {
                ++rocks.intentionalBoundaryEdges;
                rocks.contextBoundaryEdges+=meetsContext;
                rocks.foundationBoundaryEdges+=foundation || buriedBorder;
                rocks.buriedContextEdges+=buriedContext && !buriedBorder;
                rocks.floorBoundaryEdges+=floorInterface && !buriedContext && !buriedBorder;
            }
            else {
                if(rocks.unexpectedBoundaryEdges<12)
                    std::cerr<<"JOIN_BOUNDARY a="<<edge[0].x<<','<<edge[0].y<<','<<edge[0].z<<" b="<<edge[1].x<<','<<edge[1].y<<','<<edge[1].z<<" length="<<distance(edge[0],edge[1])<<'\n';
                ++rocks.unexpectedBoundaryEdges;
            }
        }
        std::cout<<"PLATEAU_ASSEMBLY triangles="<<result.faces.size()<<" original_boundary_edges="<<expectedBoundary.size()
                 <<" intentional_boundary="<<rocks.intentionalBoundaryEdges<<" unexpected_boundary="<<rocks.unexpectedBoundaryEdges
                 <<" context_boundary="<<rocks.contextBoundaryEdges<<" foundation_boundary="<<rocks.foundationBoundaryEdges
                 <<" buried_context="<<rocks.buriedContextEdges
                 <<" protected_floor_boundary="<<rocks.floorBoundaryEdges
                 <<" nonmanifold="<<rocks.assembledAudit.nonmanifoldEdges<<" duplicates="<<rocks.assembledAudit.duplicateFaces
                 <<" degenerate="<<rocks.assembledAudit.degenerateFaces<<" winding="<<rocks.assembledAudit.windingErrors<<'\n';
        if(rocks.unexpectedBoundaryEdges || rocks.assembledAudit.nonmanifoldEdges || rocks.assembledAudit.duplicateFaces ||
           rocks.assembledAudit.degenerateFaces || rocks.assembledAudit.windingErrors)
            throw std::runtime_error("Assembled plateau has an unverified boundary or invalid surface");
        const auto &strict=rocks.strictAssembledAudit;
        if(std::getenv("DW_CLIFF_EDGE_PROBE") && !strict.problemPairs.empty()) {
            std::cout<<"JOIN_BAD_PAIRS tolerance="<<tolerance<<'\n';
            for(auto pair:strict.problemPairs)for(auto i:pair) {
                std::cout<<"JOIN_BAD_TRI id="<<i;
                for(auto p:result.faces[i])std::cout<<' '<<p.x<<','<<p.y<<','<<p.z;
                std::cout<<'\n';
            }
        }

        std::cout<<"PLATEAU_ASSEMBLY_EXACT exact_open="<<strict.exact.boundaryEdges
                 <<" vertex_links="<<strict.nonmanifoldVertices<<" crossings="<<strict.selfIntersections
                 <<" coplanar_overlap="<<strict.coplanarOverlaps<<" degenerate="<<strict.exact.degenerateFaces
                 <<" tested_pairs="<<strict.testedPairs<<'\n';
        if(strict.exact.boundaryEdges!=rocks.intentionalBoundaryEdges || strict.exact.nonmanifoldEdges ||
           strict.nonmanifoldVertices || strict.selfIntersections || strict.coplanarOverlaps || strict.exact.degenerateFaces ||
           strict.exact.duplicateFaces || strict.exact.windingErrors)
            throw std::runtime_error("Exact assembled plateau connection audit failed");
        return result;
    };
    if(!rocks.seededComposition)return finish(.00008f);
    std::string failure;
    for(float tolerance:{.00008f,.00006f,.00004f,.00003f,.00012f,.0002f,.0003f,.00002f,.000008f,.000002f}) {
        try{return finish(tolerance);}catch(const std::exception &error) {
            failure=error.what();
            std::cout<<"FORMATION_WELD_REJECT tolerance="<<tolerance<<" reason="<<failure<<'\n';
        }
    }
    throw std::runtime_error(failure);

}
cliffOptions::Mesh assembleSurface(const std::vector<Polygon> &retained,Experiment &rocks,const std::vector<Polygon> &outside,bool completeContext) {
    if(std::getenv("DW_CLIFF_JOINT_WHOLE_SOURCE"))return assembleSurfaceImpl(retained,rocks,outside);
    if(completeContext)return assembleSurfaceImpl(retained,rocks,outside,true);
    const auto before=rocks;
    try{return assembleSurfaceImpl(retained,rocks,outside);}
    catch(const std::exception &e) {
        if(!rocks.seededComposition)throw;
        std::cout<<"FORMATION_CONTEXT_RETRY reason="<<e.what()<<'\n';
        rocks=before;
        return assembleSurfaceImpl(retained,rocks,outside,true);
    }
}
} // namespace dw::rockFormations
