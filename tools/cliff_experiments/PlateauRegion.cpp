#include "PlateauRegion.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stdexcept>
#ifdef DEATHWARD_CLIFF_REGION_EXPERIMENT
#include <boost/polygon/polygon.hpp>
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include <manifold/polygon.h>
#endif
#endif

namespace dw::rockFormations {
namespace {
constexpr double Contact=.00004;
struct Edge {Vector3 a,b;size_t face;std::vector<std::pair<double,double>> covered;};
double squared(Vector3 p){return double(p.x)*p.x+double(p.y)*p.y+double(p.z)*p.z;}
double segmentDistance(Vector3 p,Vector3 a,Vector3 b) {
    const auto d=sub(b,a);const double length=squared(d);
    const double t=length?std::clamp(double(dot(sub(p,a),d))/length,0.,1.):0;
    const Vector3 q{float(a.x+t*d.x),float(a.y+t*d.y),float(a.z+t*d.z)};return squared(sub(p,q));
}
std::pair<double,double> overlap(const Edge &a,const Edge &b) {
    const auto d=sub(a.b,a.a);const double length=squared(d);if(length<1e-12)return {1,0};
    const double u=double(dot(sub(b.a,a.a),d))/length,v=double(dot(sub(b.b,a.a),d))/length;
    auto lineError=[&](Vector3 p,double t) {
        const double x=double(p.x)-a.a.x-t*d.x,y=double(p.y)-a.a.y-t*d.y,z=double(p.z)-a.a.z-t*d.z;
        return x*x+y*y+z*z;
    };
    if(lineError(b.a,u)>Contact*Contact || lineError(b.b,v)>Contact*Contact)return {1,0};
    return {std::max(0.,std::min(u,v)),std::min(1.,std::max(u,v))};
}
Plane roofPlane(const Polygon &p) {
    const auto a=sub(p[1],p[0]),b=sub(p[2],p[0]);
    std::array<double,3> n{double(a.y)*b.z-double(a.z)*b.y,double(a.z)*b.x-double(a.x)*b.z,double(a.x)*b.y-double(a.y)*b.x};
    const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    Plane result;result.hasPreciseNormal=true;for(auto &v:n)v/=length;
    result.preciseNormal=n;result.normal={float(n[0]),float(n[1]),float(n[2])};result.distance=planeProjection(result,p[0]);return result;
}
double faceDistance(Vector3 p,const Polygon &face,const Plane &roof) {
    bool inside=true;
    for(size_t k=0;k<face.size();++k) {
        const auto a=face[k],b=face[(k+1)%face.size()];
        if((double(a.z)-b.z)*(double(p.x)-a.x)+(double(b.x)-a.x)*(double(p.z)-a.z)>1e-9){inside=false;break;}
    }
    if(inside) {const auto n=planeNormal(roof);const double y=(roof.distance-n[0]*p.x-n[2]*p.z)/n[1];return (y-p.y)*(y-p.y);}
    double distance=1e30;for(size_t k=0;k<face.size();++k)distance=std::min(distance,segmentDistance(p,face[k],face[(k+1)%face.size()]));return distance;
}
}

PlateauRegion planPlateauRegion(const CanyonAppearance &base,const std::vector<cliffDetail::Quad> &wall,const std::vector<Polygon> &reachedRoofs) {
    if(wall.empty())throw std::runtime_error("Cannot seed a plateau region without a wall");
    std::vector<Polygon> faces;std::vector<Plane> roofs;std::vector<size_t> sourceIds;
    std::map<std::pair<int,int>,std::vector<size_t>> faceBins;
    auto bin=[](float p){return int(std::floor(double(p)/2));};
    for(size_t i=0;i<base.triangles.size();++i) {
        const auto &t=base.triangles[i];if(!t.rock)continue;
        const auto normal=Vector3CrossProduct(sub(t.vertices[1],t.vertices[0]),sub(t.vertices[2],t.vertices[0]));
        if(normal.y<=0 || normal.y/Vector3Length(normal)<=.65f || std::min({t.vertices[0].y,t.vertices[1].y,t.vertices[2].y})<=.35f)continue;
        Polygon p{t.vertices[0],t.vertices[1],t.vertices[2]};const size_t id=faces.size();faces.push_back(p);roofs.push_back(roofPlane(p));sourceIds.push_back(i);
        const int lx=bin(std::min({p[0].x,p[1].x,p[2].x})),hx=bin(std::max({p[0].x,p[1].x,p[2].x})),lz=bin(std::min({p[0].z,p[1].z,p[2].z})),hz=bin(std::max({p[0].z,p[1].z,p[2].z}));
        for(int x=lx;x<=hx;++x)for(int z=lz;z<=hz;++z)faceBins[{x,z}].push_back(id);
    }
    std::vector<size_t> parent(faces.size());std::iota(parent.begin(),parent.end(),0);
    auto root=[&](size_t i){while(parent[i]!=i){parent[i]=parent[parent[i]];i=parent[i];}return i;};
    std::vector<Edge> edges;std::map<std::pair<int,int>,std::vector<size_t>> bins;
    for(size_t face=0;face<faces.size();++face)for(size_t k=0;k<3;++k) {
        Edge e{faces[face][k],faces[face][(k+1)%3],face,{}};const size_t id=edges.size();
        const int lx=bin(std::min(e.a.x,e.b.x)-Contact),hx=bin(std::max(e.a.x,e.b.x)+Contact),lz=bin(std::min(e.a.z,e.b.z)-Contact),hz=bin(std::max(e.a.z,e.b.z)+Contact);
        std::set<size_t> visited;
        for(int x=lx;x<=hx;++x)for(int z=lz;z<=hz;++z) {
            auto &bucket=bins[{x,z}];
            for(auto other:bucket)if(visited.insert(other).second && edges[other].face!=face) {
                const auto interval=overlap(e,edges[other]);
                if((interval.second-interval.first)*std::sqrt(squared(sub(e.b,e.a)))<=Contact)continue;
                const auto reverse=overlap(edges[other],e);if(reverse.second<=reverse.first)continue;
                e.covered.push_back(interval);edges[other].covered.push_back(reverse);
                parent[root(face)]=root(edges[other].face);
            }
            bucket.push_back(id);
        }
        edges.push_back(std::move(e));
    }
    auto anchor=[&](const cliffDetail::Quad &q) {
        auto p=mul(add(q.at,q.bt),.5f);const auto facing=cliffDetail::normal(q);p=sub(p,mul(facing,.25f));
        size_t nearest=faces.size();double best=.75*.75;
        std::set<size_t> visited;
        for(int x=bin(p.x)-1;x<=bin(p.x)+1;++x)for(int z=bin(p.z)-1;z<=bin(p.z)+1;++z) {
            const auto found=faceBins.find({x,z});if(found==faceBins.end())continue;
            for(auto i:found->second)if(visited.insert(i).second) {
                const double distance=faceDistance(p,faces[i],roofs[i]);
                if(distance<best){best=distance;nearest=i;}
            }
        }
        return nearest;
    };
    PlateauRegion region;std::set<size_t> selected;
    for(auto q:wall) {const auto id=anchor(q);if(id==faces.size()){++region.unanchoredWalls;continue;}selected.insert(root(id));}
    // New cap backs can reach another retained terrace. Include that complete
    // roof component as well, rather than ending the body at the cap footprint.
    for(const auto &reach:reachedRoofs) {
        if(reach.size()<3)continue;
        float lx=reach.front().x,hx=lx,lz=reach.front().z,hz=lz;
        for(auto p:reach){lx=std::min(lx,p.x);hx=std::max(hx,p.x);lz=std::min(lz,p.z);hz=std::max(hz,p.z);}
        std::set<size_t> candidates;
        for(int x=bin(lx);x<=bin(hx);++x)for(int z=bin(lz);z<=bin(hz);++z) {
            const auto found=faceBins.find({x,z});if(found!=faceBins.end())candidates.insert(found->second.begin(),found->second.end());
        }
        for(auto id:candidates) {
            if(selected.contains(root(id)))continue;
            using P=std::pair<double,double>;std::vector<P> polygon;
            for(auto p:faces[id])polygon.emplace_back(p.x,p.z);
            for(size_t k=0;k<reach.size() && polygon.size()>=3;++k) {
                const auto a=reach[k],b=reach[(k+1)%reach.size()];const double nx=double(a.z)-b.z,nz=double(b.x)-a.x;
                auto value=[&](P p){return nx*(p.first-a.x)+nz*(p.second-a.z);};std::vector<P> clipped;
                for(size_t i=0;i<polygon.size();++i) {
                    const auto p=polygon[i],q=polygon[(i+1)%polygon.size()];const double u=value(p),v=value(q);
                    if(u<=0)clipped.push_back(p);
                    if((u<0 && v>0) || (u>0 && v<0)){const double t=u/(u-v);clipped.emplace_back(p.first+t*(q.first-p.first),p.second+t*(q.second-p.second));}
                }
                polygon=std::move(clipped);
            }
            double area=0;for(size_t k=0;k<polygon.size();++k)area+=polygon[k].first*polygon[(k+1)%polygon.size()].second-polygon[k].second*polygon[(k+1)%polygon.size()].first;
            if(std::abs(area)>2e-10)selected.insert(root(id));
        }
    }
    if(selected.empty() || region.unanchoredWalls)throw std::runtime_error("Plateau region has an unanchored source wall");
    region.components=selected.size();region.key=1469598103934665603ULL;region.minimumHeight=1e9f;region.maximumHeight=-1e9f;
    for(size_t i=0;i<faces.size();++i)if(selected.contains(root(i))) {
        region.domains.push_back(faces[i]);++region.sourceFaces;region.key=(region.key^sourceIds[i])*1099511628211ULL;
        region.projectedArea+=std::abs(Vector3CrossProduct(sub(faces[i][1],faces[i][0]),sub(faces[i][2],faces[i][0])).y)*.5;
        for(auto p:faces[i]){region.minimumHeight=std::min(region.minimumHeight,p.y);region.maximumHeight=std::max(region.maximumHeight,p.y);}
    }
    for(auto &e:edges)if(selected.contains(root(e.face))) {
        std::sort(e.covered.begin(),e.covered.end());double at=0;
        auto append=[&](double lo,double hi) {
            if((hi-lo)*distance(e.a,e.b)<=Contact)return;
            auto a=Vector3Lerp(e.a,e.b,float(lo)),b=Vector3Lerp(e.a,e.b,float(hi));const auto mid=mul(add(a,b),.5f);
            bool front=false;
            for(auto q:wall)if(segmentDistance(mid,q.at,q.bt)<1){front=true;break;}
            region.boundary.push_back({a,b,roofs[e.face],front});
        };
        for(auto [lo,hi]:e.covered){append(at,lo);at=std::max(at,hi);}append(at,1);
    }
    for(size_t i=0;i+1<base.triangles.size();++i) {
        const auto &a=base.triangles[i],&b=base.triangles[i+1];
        if(!a.rock || !b.rock || !cliffDetail::near(a.vertices[0],b.vertices[0]) || !cliffDetail::near(a.vertices[1],b.vertices[2]))continue;
        const cliffDetail::Quad q{a.vertices[0],b.vertices[1],a.vertices[1],a.vertices[2]};
        if(std::abs(cliffDetail::normal(q).y)>.65f || std::min(q.at.y-q.ab.y,q.bt.y-q.bb.y)<.8f || q.ab.y>.35f || q.bb.y>.35f)continue;
        ++i;const auto id=anchor(q);if(id==faces.size() || !selected.contains(root(id)))continue;
        if(std::any_of(wall.begin(),wall.end(),[&](auto p){return cliffDetail::near(p.ab,q.ab) && cliffDetail::near(p.bb,q.bb);}))++region.selectedWalls;
        else ++region.neighbourWalls;
    }
    return region;
}

std::vector<Polygon> plateauRegionFootprint(const std::vector<Polygon> &domains,const std::vector<Polygon> &holes) {
#ifdef DEATHWARD_CLIFF_REGION_EXPERIMENT
    namespace bp=boost::polygon;using Coordinate=long long;
    constexpr double scale=65536; // Binary grid, 15.26 micrometres; final emitted floats are independently checked.
    bp::polygon_set_data<Coordinate> set;
    auto insert=[&](const std::vector<Polygon> &polygons,auto &destination) {
    for(const auto &p:polygons) {
        std::vector<bp::point_data<Coordinate>> points;
        for(auto q:p)points.emplace_back(std::llround(double(q.x)*scale),std::llround(double(q.z)*scale));
        bp::polygon_data<Coordinate> polygon;bp::set_points(polygon,points.begin(),points.end());destination.insert(polygon);
    }
    };
    insert(domains,set);
    bp::polygon_set_data<Coordinate> cuts;insert(holes,cuts);
    using namespace bp::operators;set-=cuts;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(std::getenv("DW_CLIFF_POLYGON_CONTOURS")) {
        std::vector<bp::polygon_with_holes_data<Coordinate>> shapes;set.get(shapes);
        std::vector<Polygon> output;
        for(const auto &shape:shapes) {
            manifold::Polygons contours;std::vector<Vector3> vertices;
            auto contour=[&](const auto &loop,bool hole) {
                manifold::SimplePolygon polygon;
                for(auto it=bp::begin_points(loop);it!=bp::end_points(loop);++it)
                    polygon.push_back({double(bp::x(*it))/scale,double(bp::y(*it))/scale});
                if(polygon.size()>1 && polygon.front()==polygon.back())polygon.pop_back();
                bool changed=true;
                while(changed && polygon.size()>3) {
                    changed=false;
                    for(size_t i=0;i<polygon.size();++i) {
                        const auto a=polygon[(i+polygon.size()-1)%polygon.size()],b=polygon[i],c=polygon[(i+1)%polygon.size()];
                        if((b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x)==0) {
                            polygon.erase(polygon.begin()+i);changed=true;break;
                        }
                    }
                }
                double area=0;for(size_t i=0;i<polygon.size();++i)area+=polygon[i].x*polygon[(i+1)%polygon.size()].y-polygon[i].y*polygon[(i+1)%polygon.size()].x;
                if((area<0)!=hole)std::reverse(polygon.begin(),polygon.end());
                for(auto p:polygon)vertices.push_back({float(p.x),0,float(p.y)});
                contours.push_back(std::move(polygon));
            };
            contour(shape,false);
            for(auto hole=bp::begin_holes(shape);hole!=bp::end_holes(shape);++hole)contour(*hole,true);
            for(auto t:manifold::Triangulate(contours,0)) {
                Polygon triangle{vertices.at(t.x),vertices.at(t.y),vertices.at(t.z)};
                const auto a=triangle[0],b=triangle[1],c=triangle[2];
                const double turn=(double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);
                if(turn==0)throw std::runtime_error("Contour triangulator emitted a collapsed roof triangle");
                if(turn>0)std::swap(triangle[1],triangle[2]);output.push_back(std::move(triangle));
            }
        }
        return output;
    }
#else
    if(std::getenv("DW_CLIFF_POLYGON_CONTOURS"))
        throw std::runtime_error("Contour triangulation requires DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT");
#endif
    std::vector<bp::polygon_data<Coordinate>> traps;set.get_trapezoids(traps);
    std::vector<Polygon> result;
    for(const auto &trap:traps) {
        Polygon p;for(auto at=bp::begin_points(trap);at!=bp::end_points(trap);++at)p.push_back({float(bp::x(*at)/scale),0,float(bp::y(*at)/scale)});
        if(p.size()>1 && p.front().x==p.back().x && p.front().z==p.back().z)p.pop_back();
        bool changed=true;
        while(changed && p.size()>2) {
            changed=false;
            for(size_t i=0;i<p.size();++i) {
                const auto a=p[(i+p.size()-1)%p.size()],b=p[i],c=p[(i+1)%p.size()];
                const double turn=(double(b.x)-a.x)*(double(c.z)-b.z)-(double(b.z)-a.z)*(double(c.x)-b.x);
                if(turn==0){p.erase(p.begin()+i);changed=true;break;}
            }
        }
        double area=0;for(size_t k=0;k<p.size();++k)area+=double(p[k].x)*p[(k+1)%p.size()].z-double(p[k].z)*p[(k+1)%p.size()].x;
        if(std::abs(area)<1e-12)continue;if(area>0)std::reverse(p.begin(),p.end());result.push_back(std::move(p));
    }
    return result;
#else
    (void)domains;(void)holes;
    throw std::runtime_error("Plateau region experiment requires DEATHWARD_CLIFF_REGION_EXPERIMENT");
#endif
}

cliffOptions::Mesh meshPlateauFootprint(const std::vector<Polygon> &domains,bool interiorControls) {
    using Key=std::pair<float,float>;
    std::map<Key,size_t> ids;std::vector<Vector3> points;std::vector<std::vector<size_t>> outlines;
    for(const auto &domain:domains) {
        std::vector<size_t> outline;
        for(auto p:domain){p.y=0;auto [at,added]=ids.emplace(Key{p.x,p.z},points.size());if(added)points.push_back(p);if(outline.empty() || outline.back()!=at->second)outline.push_back(at->second);}
        if(outline.size()>1 && outline.front()==outline.back())outline.pop_back();if(outline.size()>=3)outlines.push_back(std::move(outline));
    }
    const size_t boundaryPoints=points.size();cliffOptions::Mesh mesh;
    auto turn=[&](size_t a,size_t b,size_t c){return (double(points[b].x)-points[a].x)*(double(points[c].z)-points[a].z)-(double(points[b].z)-points[a].z)*(double(points[c].x)-points[a].x);};
    for(const auto &outline:outlines) {
        std::vector<size_t> split;
        for(size_t k=0;k<outline.size();++k) {
            const auto ia=outline[k],ib=outline[(k+1)%outline.size()];const auto a=points[ia],b=points[ib];
            const double dx=double(b.x)-a.x,dz=double(b.z)-a.z,length=dx*dx+dz*dz;
            std::vector<std::pair<double,size_t>> on{{0,ia}};
            for(size_t i=0;i<boundaryPoints;++i)if(i!=ia && i!=ib && turn(ia,ib,i)==0) {
                const auto p=points[i];const double t=((double(p.x)-a.x)*dx+(double(p.z)-a.z)*dz)/length;
                if(t>0 && t<1)on.push_back({t,i});
            }
            std::sort(on.begin(),on.end());for(auto [t,i]:on)split.push_back(i);
        }
        for(size_t k=0;k<split.size();++k)mesh.polygonEdges.push_back({points[split[k]],points[split[(k+1)%split.size()]]});
        if(interiorControls) {
            double x=0,z=0;for(auto i:outline){x+=points[i].x;z+=points[i].z;}
            const Vector3 center{float(x/outline.size()),0,float(z/outline.size())};bool safe=true;
            for(size_t k=0;k<outline.size();++k) {
                const auto a=points[outline[k]],b=points[outline[(k+1)%outline.size()]];
                const double cross=(double(b.x)-a.x)*(double(center.z)-a.z)-(double(b.z)-a.z)*(double(center.x)-a.x);
                if(cross>=0 || segmentDistance(center,a,b)<.05*.05){safe=false;break;}
            }
            if(safe){for(size_t k=0;k<split.size();++k)mesh.faces.push_back({center,points[split[k]],points[split[(k+1)%split.size()]]});continue;}
        }
        while(split.size()>3) {
            bool removed=false;
            for(size_t k=0;k<split.size();++k) {
                const auto a=split[(k+split.size()-1)%split.size()],b=split[k],c=split[(k+1)%split.size()];if(turn(a,b,c)>=0)continue;
                bool occupied=false;
                for(auto p:split)if(p!=a && p!=b && p!=c && turn(a,b,p)<=0 && turn(b,c,p)<=0 && turn(c,a,p)<=0){occupied=true;break;}
                if(occupied)continue;
                mesh.faces.push_back({points[a],points[b],points[c]});split.erase(split.begin()+k);removed=true;break;
            }
            if(!removed)throw std::runtime_error("Cannot triangulate exact regional footprint boundary");
        }
        if(split.size()!=3 || turn(split[0],split[1],split[2])>=0)throw std::runtime_error("Regional footprint has a collapsed terminal triangle");
        mesh.faces.push_back({points[split[0]],points[split[1]],points[split[2]]});
    }
    return mesh;
}

std::vector<Vector3> plateauFootprintPinches(const std::vector<Polygon> &domains) {
    using Key=std::array<float,2>;
    const auto mesh=meshPlateauFootprint(domains);
    std::map<Key,std::vector<std::pair<Key,Key>>> links;
    for(const auto &f:mesh.faces)for(int k=0;k<3;++k) {
        const auto p=f[k],a=f[(k+1)%3],b=f[(k+2)%3];
        links[{p.x,p.z}].push_back({{a.x,a.z},{b.x,b.z}});
    }
    std::vector<Vector3> result;
    for(const auto &[p,edges]:links) {
        std::map<Key,std::set<Key>> graph;
        for(auto [a,b]:edges){graph[a].insert(b);graph[b].insert(a);}
        std::set<Key> visited;std::vector<Key> stack{graph.begin()->first};
        while(!stack.empty()) {
            const auto q=stack.back();stack.pop_back();if(!visited.insert(q).second)continue;
            for(auto neighbour:graph.at(q))stack.push_back(neighbour);
        }
        if(visited.size()!=graph.size())result.push_back({p[0],0,p[1]});
    }
    return result;
}
std::vector<Polygon> bridgePlateauFootprintPinches(const std::vector<Polygon> &domains,float radius) {
    if(radius<=0 || radius>.1f)throw std::runtime_error("Unsupported plateau point-bridge radius");
    const auto pinches=plateauFootprintPinches(domains);
    std::cout<<"PLATEAU_FOOTPRINT_BRIDGES contacts="<<pinches.size()<<" radius_m="<<radius<<std::endl;
    if(pinches.empty())return domains;
    auto combined=domains;
    for(auto p:pinches) {
        Polygon bridge{{p.x-radius,0,p.z},{p.x,0,p.z+radius},{p.x+radius,0,p.z},{p.x,0,p.z-radius}};
        for(auto q:bridge)if((q.x==p.x && q.z==p.z) || std::abs(std::hypot(double(q.x)-p.x,double(q.z)-p.z)-radius)>.00002)
            throw std::runtime_error("Plateau point bridge is not representable at its requested shape radius");
        combined.push_back(std::move(bridge));
    }
    return plateauRegionFootprint(combined);
}

std::vector<RoofGrade> plateauRegionConstraints(const PlateauRegion &region,const std::vector<std::array<Vector3,2>> &external,float strip) {
    std::vector<RoofGrade> grades;
    for(const auto &edge:region.boundary)if(!edge.selectedFront) {
        auto projectedA=edge.a,projectedB=edge.b;projectedA.y=projectedB.y=0;
        const Edge source{projectedA,projectedB,0,{}};
        std::vector<std::pair<double,double>> intervals;
        for(auto ends:external) {
            ends[0].y=ends[1].y=0;const auto interval=overlap(source,{ends[0],ends[1],0,{}});
            if(interval.second>interval.first)intervals.push_back(interval);
        }
        std::sort(intervals.begin(),intervals.end());std::vector<std::pair<double,double>> merged;
        for(auto interval:intervals) {
            if(!merged.empty() && interval.first<=merged.back().second+1e-9)merged.back().second=std::max(merged.back().second,interval.second);
            else merged.push_back(interval);
        }
        for(auto [lo,hi]:merged) {
            const auto a=Vector3Lerp(edge.a,edge.b,float(lo)),b=Vector3Lerp(edge.a,edge.b,float(hi));
            const auto delta=sub(b,a);const float length=std::hypot(delta.x,delta.z);if(length<Contact)continue;
            const Vector3 inward{delta.z/length*strip,0,-delta.x/length*strip};const auto n=planeNormal(edge.roof);
            grades.push_back({{a,b,add(b,inward),add(a,inward)},edge.roof,float(1+std::hypot(n[0],n[2])/n[1])});
        }
    }
    return grades;
}
void writePlateauRegion(const char *path,const PlateauRegion &region) {
    std::ofstream out(path);out.precision(17);
    out<<"{\"key\":"<<region.key<<",\"components\":"<<region.components<<",\"source_faces\":"<<region.sourceFaces
       <<",\"selected_walls\":"<<region.selectedWalls<<",\"neighbour_walls\":"<<region.neighbourWalls
       <<",\"area_m2\":"<<region.projectedArea<<",\"minimum_height\":"<<region.minimumHeight<<",\"maximum_height\":"<<region.maximumHeight<<",\"domains\":[";
    for(size_t i=0;i<region.domains.size();++i){if(i)out<<',';out<<'[';for(size_t k=0;k<region.domains[i].size();++k){if(k)out<<',';auto p=region.domains[i][k];out<<'['<<p.x<<','<<p.y<<','<<p.z<<']';}out<<']';}
    out<<"],\"boundary\":[";
    for(size_t i=0;i<region.boundary.size();++i){if(i)out<<',';const auto &e=region.boundary[i];out<<"{\"a\":["<<e.a.x<<','<<e.a.y<<','<<e.a.z<<"],\"b\":["<<e.b.x<<','<<e.b.y<<','<<e.b.z<<"],\"selected_front\":"<<(e.selectedFront?"true":"false")<<'}';}
    out<<"]}\n";if(!out)throw std::runtime_error("Cannot write plateau region probe");
}
}
