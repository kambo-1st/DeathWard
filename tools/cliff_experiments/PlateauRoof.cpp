#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "PlateauRegion.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace dw::rockFormations {
std::vector<cliffOptions::Triangle> triangulatePlateauRoof(const std::vector<Vector3> &controls) {
    std::vector<Vector3> points;
    for(auto p:controls)if(std::none_of(points.begin(),points.end(),[&](auto q){return planarDistance(p,q)<.002f;}))points.push_back(p);
    if(points.size()<3)throw std::runtime_error("Plateau roof needs three distinct controls");
    const auto count=points.size();
    float lx=points[0].x,hx=lx,lz=points[0].z,hz=lz;
    for(auto p:points){lx=std::min(lx,p.x);hx=std::max(hx,p.x);lz=std::min(lz,p.z);hz=std::max(hz,p.z);}
    const auto span=std::max(hx-lx,hz-lz),x=(lx+hx)*.5f,z=(lz+hz)*.5f;
    points.push_back({x-32*span,0,z-16*span});points.push_back({x+32*span,0,z-16*span});points.push_back({x,0,z+32*span});
    using Face=std::array<size_t,3>;
    auto turn=[&](size_t a,size_t b,size_t c) {
        return (double(points[b].x)-points[a].x)*(double(points[c].z)-points[a].z)-
               (double(points[b].z)-points[a].z)*(double(points[c].x)-points[a].x);
    };
    std::vector<Face> faces{{count,count+1,count+2}};
    for(size_t p=0;p<count;++p) {
        std::map<std::pair<size_t,size_t>,size_t> edges;
        std::vector<Face> retained;
        for(auto f:faces) {
            const double ax=double(points[f[0]].x)-points[p].x,az=double(points[f[0]].z)-points[p].z;
            const double bx=double(points[f[1]].x)-points[p].x,bz=double(points[f[1]].z)-points[p].z;
            const double cx=double(points[f[2]].x)-points[p].x,cz=double(points[f[2]].z)-points[p].z;
            const double circle=(ax*ax+az*az)*(bx*cz-bz*cx)-(bx*bx+bz*bz)*(ax*cz-az*cx)+(cx*cx+cz*cz)*(ax*bz-az*bx);
            if(circle<=1e-10){retained.push_back(f);continue;}
            for(int k=0;k<3;++k){auto a=f[k],b=f[(k+1)%3];if(a>b)std::swap(a,b);++edges[{a,b}];}
        }
        for(auto [edge,uses]:edges)if(uses==1) {
            Face f{edge.first,edge.second,p};const auto area=turn(f[0],f[1],f[2]);
            if(std::abs(area)<1e-10)continue;
            if(area<0)std::swap(f[0],f[1]);retained.push_back(f);
        }
        faces=std::move(retained);
    }
    std::vector<cliffOptions::Triangle> roof;
    for(auto f:faces)if(f[0]<count && f[1]<count && f[2]<count)roof.push_back({points[f[0]],points[f[2]],points[f[1]]});
    if(roof.empty())throw std::runtime_error("Plateau roof has no projected area");
    return roof;
}
} // namespace dw::rockFormations

namespace dw::rockFormations {
std::vector<cliffOptions::Triangle> triangulatePlateauBoundary(std::vector<Vector3> p,bool retainCollinear) {
    auto cross=[](Vector3 a,Vector3 b,Vector3 c) {
        return (double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);
    };
    auto fail=[](){throw std::runtime_error("Plateau boundary is not a simple nonzero-area polygon");};
    if(p.size()<3)fail();
    for(size_t i=0;i<p.size();++i)for(size_t j=i+1;j<p.size();++j) {
        if(j==i+1 || (i==0 && j+1==p.size()))continue;
        const auto a=p[i],b=p[(i+1)%p.size()],c=p[j],d=p[(j+1)%p.size()];
        auto onSegment=[&](Vector3 u,Vector3 v,Vector3 q) {
            return std::abs(cross(u,v,q))<1e-10 && q.x>=std::min(u.x,v.x)-1e-7 && q.x<=std::max(u.x,v.x)+1e-7 &&
                   q.z>=std::min(u.z,v.z)-1e-7 && q.z<=std::max(u.z,v.z)+1e-7;
        };
        if(onSegment(a,b,c) || onSegment(a,b,d) || onSegment(c,d,a) || onSegment(c,d,b) ||
           (cross(a,b,c)*cross(a,b,d)<-1e-14 && cross(c,d,a)*cross(c,d,b)<-1e-14))fail();
    }
    double area=0;for(size_t i=0;i<p.size();++i)area+=double(p[i].x)*p[(i+1)%p.size()].z-double(p[i].z)*p[(i+1)%p.size()].x;
    if(std::abs(area)<1e-8)fail();if(area>0)std::reverse(p.begin(),p.end());
    std::vector<cliffOptions::Triangle> result;
    while(p.size()>3) {
        bool removed=false;
        for(size_t i=0;i<p.size();++i) {
            const auto a=p[(i+p.size()-1)%p.size()],b=p[i],c=p[(i+1)%p.size()];
            if(std::abs(cross(a,b,c))<1e-9) {if(retainCollinear)continue;p.erase(p.begin()+i);removed=true;break;}
            if(cross(a,b,c)>=0)continue;
            bool occupied=false;
            for(size_t j=0;j<p.size();++j)if(j!=i && j!=(i+1)%p.size() && j!=(i+p.size()-1)%p.size())
                occupied|=cross(a,b,p[j])<=1e-10 && cross(b,c,p[j])<=1e-10 && cross(c,a,p[j])<=1e-10;
            if(occupied)continue;
            result.push_back({a,b,c});p.erase(p.begin()+i);removed=true;break;
        }
        if(!removed)fail();
    }
    if(p.size()!=3 || cross(p[0],p[1],p[2])>=-1e-10)fail();
    result.push_back({p[0],p[1],p[2]});return result;
}
}

namespace dw::rockFormations {
static std::vector<GradedRoofCell> gradeCells(std::vector<GradedRoofCell> cells,const std::vector<RoofGrade> &grades,float slope,bool prune) {
    if(slope<=0)throw std::runtime_error("Plateau grading needs a positive slope");
    auto projectedArea=[](const Polygon &p) {
        double a=0;for(size_t i=0;i<p.size();++i)a+=double(p[i].x)*p[(i+1)%p.size()].z-double(p[i].z)*p[(i+1)%p.size()].x;
        return std::abs(a)*.5;
    };
    auto normalized=[](std::array<double,3> n,double distance) {
        const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
        Plane p;p.hasPreciseNormal=true;
        for(size_t k=0;k<3;++k)p.preciseNormal[k]=n[k]/length;
        p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};
        p.distance=distance/length;return p;
    };
    auto reversed=[](Plane p) {p.normal=mul(p.normal,-1);for(auto &n:p.preciseNormal)n=-n;p.distance=-p.distance;return p;};
    for(const auto &grade:grades) {
        if(grade.protectedRoof.size()<3 || grade.roof.normal.y<=0)throw std::runtime_error("Invalid protected roof region");
        const float gradeSlope=grade.outsideSlope>0?grade.outsideSlope:slope;
        std::vector<Plane> sides;
        for(size_t k=0;k<grade.protectedRoof.size();++k) {
            auto a=grade.protectedRoof[k],b=grade.protectedRoof[(k+1)%grade.protectedRoof.size()];
            const std::array<double,3> n{double(a.z)-b.z,0,double(b.x)-a.x};
            if(std::hypot(n[0],n[2])<1e-10)continue;
            sides.push_back(normalized(n,n[0]*a.x+n[2]*a.z));
        }
        std::vector<Plane> bounds{grade.roof};
        const auto capNormal=planeNormal(grade.roof);
        for(const auto &side:sides) {
            const auto n=planeNormal(side);
            bounds.push_back(normalized({capNormal[0]-capNormal[1]*gradeSlope*n[0],capNormal[1],capNormal[2]-capNormal[1]*gradeSlope*n[2]},grade.roof.distance-capNormal[1]*gradeSlope*side.distance));
        }
        std::vector<GradedRoofCell> next,affected;
        for(auto &cell:cells) {
            const auto current=planeNormal(cell.roof);
            // One affine bound dominating at every vertex dominates the whole
            // convex cell. The maximum of bounds is not affine: testing only
            // its vertex values would miss an interior protected cap.
            const bool unchanged=prune && std::any_of(bounds.begin(),bounds.end(),[&](const auto &bound) {
                const auto n=planeNormal(bound);
                return std::all_of(cell.outline.begin(),cell.outline.end(),[&](auto p) {
                    const double a=(cell.roof.distance-current[0]*p.x-current[2]*p.z)/current[1];
                    const double b=(bound.distance-n[0]*p.x-n[2]*p.z)/n[1];
                    return b>=a+1e-8;
                });
            });
            if(unchanged)next.push_back(std::move(cell));else affected.push_back(std::move(cell));
        }
        // d(p) = max(0, every outward unit-side-plane displacement).
        // capHeight + slope*d is continuous. Clamping land to this bound
        // merges cap backs while retaining the protected front strip.
        for(int branch=-1;branch<int(sides.size());++branch) {
            Volume region;Plane limit=grade.roof;
            if(branch<0)region.planes=sides;
            else {
                const auto selected=sides[size_t(branch)];const auto n=planeNormal(selected);
                region.planes.push_back(reversed(selected));
                for(size_t k=0;k<sides.size();++k)if(k!=size_t(branch)) {
                    const auto other=planeNormal(sides[k]);const std::array<double,3> difference{other[0]-n[0],0,other[2]-n[2]};
                    if(std::hypot(difference[0],difference[2])<1e-10)continue;
                    region.planes.push_back(normalized(difference,sides[k].distance-selected.distance));
                }
                const auto cap=planeNormal(grade.roof);
                limit=normalized({cap[0]-cap[1]*gradeSlope*n[0],cap[1],cap[2]-cap[1]*gradeSlope*n[2]},grade.roof.distance-cap[1]*gradeSlope*selected.distance);
            }
            for(const auto &cell:affected) {
                auto part=clipToVolume(cell.outline,region);
                if(part.size()<3 || projectedArea(part)<1e-10)continue;
                Volume low;low.planes={limit};auto lower=clipToVolume(part,low);
                Volume high;high.planes={reversed(limit)};auto upper=clipToVolume(part,high);
                // Coplanar cells belong to the lower branch exactly once.
                bool above=false;for(auto q:part)above|=planeProjection(limit,q)>limit.distance+.000001;
                if(!above){next.push_back({std::move(part),cell.roof});continue;}
                if(lower.size()>=3 && projectedArea(lower)>1e-10)next.push_back({std::move(lower),cell.roof});
                if(upper.size()>=3 && projectedArea(upper)>1e-10) {
                    const auto n=planeNormal(limit);
                    for(auto &q:upper)q.y=float((limit.distance-n[0]*q.x-n[2]*q.z)/n[1]);
                    next.push_back({std::move(upper),limit});
                }
            }
        }
        cells=std::move(next);
    }
    return cells;
}
std::vector<GradedRoofCell> gradePlateauRoof(Polygon domain,float landHeight,const std::vector<RoofGrade> &grades,float slope,bool prune) {
    return gradeCells({{std::move(domain),{{0,1,0},landHeight}}},grades,slope,prune);
}
std::vector<GradedRoofCell> gradePlateauRegionRoof(std::vector<Polygon> domains,float landHeight,const std::vector<RoofGrade> &grades,float slope,bool prune) {
    std::vector<GradedRoofCell> cells;for(auto &domain:domains)cells.push_back({std::move(domain),{{0,1,0},landHeight}});
    return gradeCells(std::move(cells),grades,slope,prune);
}
std::vector<GradedRoofCell> samplePlateauRegionRoof(std::vector<Polygon> domains,float landHeight,const std::vector<RoofGrade> &grades,float slope,const std::vector<RoofGrade> &lowerCaps) {
    ConstructionChecks requiredChecks;
    if(slope<=0)throw std::runtime_error("Regional roof sampling needs a positive slope");
    for(auto &domain:domains)for(auto &p:domain)p.y=0;
    // Split every planar shared edge before evaluating elevations. Evaluating
    // unsplit trapezoids independently would produce height T-junctions.
    auto flat=meshPlateauFootprint(domains,true);
    const auto audit=auditStrictSurface(flat);
    bool componentLinksValid=true;
    if(audit.nonmanifoldVertices)for(const auto &component:splitSurfaceComponents(flat))componentLinksValid &= auditStrictSurface(component).nonmanifoldVertices==0;
    if(audit.exact.nonmanifoldEdges || !componentLinksValid || audit.selfIntersections || audit.coplanarOverlaps ||
       audit.exact.degenerateFaces || audit.exact.duplicateFaces || audit.exact.windingErrors) {
        std::cout<<"PLATEAU_REGION_FLAT_REJECT boundary="<<audit.exact.boundaryEdges<<" nonmanifold="<<audit.exact.nonmanifoldEdges
                 <<" links="<<audit.nonmanifoldVertices<<" crossings="<<audit.selfIntersections<<" overlaps="<<audit.coplanarOverlaps
                 <<" degenerate="<<audit.exact.degenerateFaces<<" winding="<<audit.exact.windingErrors<<'\n';
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE"))writeSurfaceProbe(path,flat,{},audit);
        throw std::runtime_error("Regional footprint triangulation is invalid");
    }
    // Trapezoid slicing can produce very long, thin cells. Improve interior
    // diagonals before sampling heights; interpolating a bounded-slope field
    // over a sliver can otherwise create an almost vertical roof plane.
    using Face=std::array<size_t,3>;using Key=std::pair<float,float>;
    std::map<Key,size_t> ids;std::vector<Vector3> points;std::vector<Face> faces;
    for(const auto &f:flat.faces) {
        Face face;for(int k=0;k<3;++k){auto [at,added]=ids.emplace(Key{f[k].x,f[k].z},points.size());if(added)points.push_back(f[k]);face[k]=at->second;}faces.push_back(face);
    }
    auto turn=[&](size_t a,size_t b,size_t c){return (double(points[b].x)-points[a].x)*(double(points[c].z)-points[a].z)-(double(points[b].z)-points[a].z)*(double(points[c].x)-points[a].x);};
    auto quality=[&](Face f) {
        double result=1;
        for(int k=0;k<3;++k) {
            const auto a=points[f[k]],b=points[f[(k+1)%3]],c=points[f[(k+2)%3]];
            const double ux=double(b.x)-a.x,uz=double(b.z)-a.z,vx=double(c.x)-a.x,vz=double(c.z)-a.z;
            const double cross=ux*vz-uz*vx,denominator=(ux*ux+uz*uz)*(vx*vx+vz*vz);
            result=std::min(result,denominator?cross*cross/denominator:0.);
        }
        return result;
    };
    size_t flips=0;
    for(int pass=0;pass<128;++pass) {
        std::map<std::pair<size_t,size_t>,std::vector<size_t>> adjacent;
        for(size_t i=0;i<faces.size();++i)for(int k=0;k<3;++k){auto a=faces[i][k],b=faces[i][(k+1)%3];if(b<a)std::swap(a,b);adjacent[{a,b}].push_back(i);}
        std::set<size_t> changed;
        for(const auto &[edge,owners]:adjacent) {
            if(owners.size()!=2 || changed.contains(owners[0]) || changed.contains(owners[1]))continue;
            const auto a=edge.first,b=edge.second;size_t c=0,d=0;
            for(auto id:faces[owners[0]])if(id!=a && id!=b)c=id;
            for(auto id:faces[owners[1]])if(id!=a && id!=b)d=id;
            auto newEdge=std::minmax(c,d);
            if(adjacent.contains(newEdge) || turn(c,d,a)*turn(c,d,b)>=0 || turn(a,b,c)*turn(a,b,d)>=0)continue;
            Face first{c,d,a},second{d,c,b};
            if(turn(first[0],first[1],first[2])>0)std::swap(first[1],first[2]);
            if(turn(second[0],second[1],second[2])>0)std::swap(second[1],second[2]);
            const double before=std::min(quality(faces[owners[0]]),quality(faces[owners[1]])),after=std::min(quality(first),quality(second));
            if(after<=before*(1+1e-6)+1e-14)continue;
            faces[owners[0]]=first;faces[owners[1]]=second;changed.insert(owners[0]);changed.insert(owners[1]);++flips;
        }
        if(changed.empty())break;
    }
    flat.faces.clear();for(auto f:faces)flat.faces.push_back({points[f[0]],points[f[1]],points[f[2]]});
    const auto improved=auditStrictSurface(flat);bool improvedLinksValid=true;
    if(improved.nonmanifoldVertices)for(const auto &component:splitSurfaceComponents(flat))improvedLinksValid &= auditStrictSurface(component).nonmanifoldVertices==0;
    if(improved.exact.boundaryEdges!=audit.exact.boundaryEdges || improved.exact.nonmanifoldEdges || !improvedLinksValid ||
       improved.selfIntersections || improved.coplanarOverlaps || improved.exact.windingErrors || improved.exact.degenerateFaces ||
       improved.exact.duplicateFaces || improved.exact.components!=audit.exact.components)
        throw std::runtime_error("Regional roof quality flips changed its valid domain");
    std::cout<<"PLATEAU_REGION_TRIANGULATION triangles="<<faces.size()<<" quality_flips="<<flips<<" exact_checks=PASS\n";
    struct Bound {Plane roof;std::vector<std::array<double,3>> sides;float slope;};
    std::vector<Bound> bounds;
    for(const auto &grade:grades) {
        Bound b{grade.roof,{},grade.outsideSlope>0?grade.outsideSlope:slope};
        for(size_t k=0;k<grade.protectedRoof.size();++k) {
            const auto a=grade.protectedRoof[k],c=grade.protectedRoof[(k+1)%grade.protectedRoof.size()];
            const double nx=double(a.z)-c.z,nz=double(c.x)-a.x,length=std::hypot(nx,nz);
            if(length>1e-10)b.sides.push_back({nx/length,nz/length,(nx*a.x+nz*a.z)/length});
        }
        bounds.push_back(std::move(b));
    }
    std::map<std::pair<float,float>,float> heights;
    std::vector<Bound> lowerBounds;
    for(const auto &grade:lowerCaps) {
        Bound b{grade.roof,{},grade.outsideSlope>0?grade.outsideSlope:2};
        for(size_t k=0;k<grade.protectedRoof.size();++k) {
            const auto a=grade.protectedRoof[k],c=grade.protectedRoof[(k+1)%grade.protectedRoof.size()];
            const double nx=double(a.z)-c.z,nz=double(c.x)-a.x,length=std::hypot(nx,nz);
            if(length>1e-10)b.sides.push_back({nx/length,nz/length,(nx*a.x+nz*a.z)/length});
        }
        lowerBounds.push_back(std::move(b));
    }
    for(auto &f:flat.faces)for(auto &p:f) {
        auto [at,added]=heights.emplace(std::pair{p.x,p.z},landHeight);
        if(added)for(const auto &b:bounds) {
            const auto n=planeNormal(b.roof);double distance=0;
            for(const auto &side:b.sides)distance=std::max(distance,side[0]*p.x+side[1]*p.z-side[2]);
            const double height=(b.roof.distance-n[0]*p.x-n[2]*p.z)/n[1]+b.slope*distance;
            at->second=std::min(at->second,float(height));
        }
        if(added)for(const auto &b:lowerBounds) {
            const auto n=planeNormal(b.roof);double distance=0;
            for(const auto &side:b.sides)distance=std::max(distance,side[0]*p.x+side[1]*p.z-side[2]);
            at->second=std::max(at->second,float((b.roof.distance-n[0]*p.x-n[2]*p.z)/n[1]-b.slope*distance));
        }
        p.y=at->second;
    }
    std::vector<GradedRoofCell> cells;
    for(const auto &f:flat.faces) {
        const std::array<double,3> a{double(f[1].x)-f[0].x,double(f[1].y)-f[0].y,double(f[1].z)-f[0].z},
                                   b{double(f[2].x)-f[0].x,double(f[2].y)-f[0].y,double(f[2].z)-f[0].z};
        std::array<double,3> n{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};
        const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
        if(n[1]<=0)throw std::runtime_error("Regional sampled roof folds in projection");
        for(auto &v:n)v/=length;Plane roof;roof.hasPreciseNormal=true;roof.preciseNormal=n;roof.normal={float(n[0]),float(n[1]),float(n[2])};roof.distance=planeProjection(roof,f[0]);
        cells.push_back({{f[0],f[1],f[2]},roof});
    }
    return cells;
}
}

namespace dw::rockFormations {
std::vector<GradedRoofCell> blendPlateauBoundary(std::vector<GradedRoofCell> cells,const std::vector<RoofGrade> &terrain,const std::vector<Plane> &interfaces,float slope) {
    auto area=[](const Polygon &p){double a=0;for(size_t k=0;k<p.size();++k)a+=double(p[k].x)*p[(k+1)%p.size()].z-double(p[k].z)*p[(k+1)%p.size()].x;return std::abs(a)*.5;};
    auto unit=[](std::array<double,3> n,double d) {
        const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);Plane p;p.hasPreciseNormal=true;
        for(size_t k=0;k<3;++k)p.preciseNormal[k]=n[k]/length;
        p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};p.distance=d/length;return p;
    };
    auto reverse=[](Plane p){p.normal=mul(p.normal,-1);for(auto &n:p.preciseNormal)n=-n;p.distance=-p.distance;return p;};
    for(const auto &source:terrain) {
        Volume domain;
        for(size_t k=0;k<source.protectedRoof.size();++k) {
            const auto a=source.protectedRoof[k],b=source.protectedRoof[(k+1)%source.protectedRoof.size()];
            const std::array<double,3> n{double(a.z)-b.z,0,double(b.x)-a.x};
            if(std::hypot(n[0],n[2])>1e-10)domain.planes.push_back(unit(n,n[0]*a.x+n[2]*a.z));
        }
        std::vector<Plane> limits;const auto old=planeNormal(source.roof);
        for(const auto &edge:interfaces) {
            const auto n=planeNormal(edge);
            // The cap equals the retained roof at this interface and rises
            // inward. The union with retained land therefore has no step here.
            limits.push_back(unit({old[0]+old[1]*slope*n[0],old[1],old[2]+old[1]*slope*n[2]},source.roof.distance+old[1]*slope*edge.distance));
        }
        std::vector<GradedRoofCell> next;
        for(const auto &cell:cells) {
            auto inside=clipToVolume(cell.outline,domain);
            if(inside.size()<3 || area(inside)<1e-10){next.push_back(cell);continue;}
            std::vector<GradedRoofCell> parts{{inside,cell.roof}};bool changed=false;
            for(const auto &limit:limits) {
                std::vector<GradedRoofCell> limited;
                for(const auto &part:parts) {
                    bool above=false;for(auto p:part.outline)above|=planeProjection(limit,p)>limit.distance+.000001;
                    if(!above){limited.push_back(part);continue;}
                    changed=true;Volume low;low.planes={limit};auto lower=clipToVolume(part.outline,low);
                    Volume high;high.planes={reverse(limit)};auto upper=clipToVolume(part.outline,high);
                    if(lower.size()>=3 && area(lower)>1e-10)limited.push_back({std::move(lower),part.roof});
                    if(upper.size()>=3 && area(upper)>1e-10) {
                        const auto n=planeNormal(limit);
                        for(auto &q:upper)q.y=float((limit.distance-n[0]*q.x-n[2]*q.z)/n[1]);
                        limited.push_back({std::move(upper),limit});
                    }
                }
                parts=std::move(limited);
            }
            if(!changed){next.push_back(cell);continue;}
            for(auto outside:exposed(cell.outline,{domain}))next.push_back({std::move(outside),cell.roof});
            next.insert(next.end(),parts.begin(),parts.end());
        }
        cells=std::move(next);
    }
    return cells;
}
}

namespace dw::rockFormations {
std::vector<RoofGrade> plateauBoundaryGrades(const Polygon &domain,const std::vector<RoofGrade> &terrain,const std::vector<Plane> &interfaces,float inwardSlope) {
    if(domain.size()<3 || inwardSlope<=0)throw std::runtime_error("Invalid plateau boundary grading domain");
    double span=1;for(auto a:domain)for(auto b:domain)span=std::max(span,double(planarDistance(a,b)));
    std::vector<RoofGrade> result;
    for(size_t edge=0;edge<domain.size();++edge) {
        const auto a=domain[edge],b=domain[(edge+1)%domain.size()];
        const double dx=double(b.x)-a.x,dz=double(b.z)-a.z,length=std::hypot(dx,dz);
        if(length<1e-8)continue;
        const double nx=-dz/length,nz=dx/length,distance=nx*a.x+nz*a.z;
        if(std::none_of(interfaces.begin(),interfaces.end(),[&](const auto &p){const auto n=planeNormal(p);return n[0]*nx+n[2]*nz>1-1e-8 && std::abs(p.distance-distance)<1e-5;}))continue;
        struct Range{double lo,hi,intercept,slope;};std::vector<Range> ranges;
        std::vector<double> events{0,1};
        for(const auto &source:terrain) {
            double lo=0,hi=1;
            for(size_t k=0;k<source.protectedRoof.size();++k) {
                const auto u=source.protectedRoof[k],v=source.protectedRoof[(k+1)%source.protectedRoof.size()];
                const double sx=double(u.z)-v.z,sz=double(v.x)-u.x;
                const double start=sx*(double(a.x)-u.x)+sz*(double(a.z)-u.z),delta=sx*dx+sz*dz;
                if(std::abs(delta)<1e-18){if(start>0){hi=-1;break;}}
                else if(delta>0)hi=std::min(hi,-start/delta);else lo=std::max(lo,-start/delta);
            }
            if(hi-lo<1e-9)continue;
            const auto n=planeNormal(source.roof);
            const double intercept=(source.roof.distance-n[0]*a.x-n[2]*a.z)/n[1];
            const double slope=-(n[0]*dx+n[2]*dz)/n[1];
            ranges.push_back({lo,hi,intercept,slope});events.push_back(lo);events.push_back(hi);
        }
        // Include changes of the upper source roof inside overlapping domains.
        for(size_t i=0;i<ranges.size();++i)for(size_t j=0;j<i;++j) {
            const auto &u=ranges[i],&v=ranges[j];const double delta=u.slope-v.slope;
            if(std::abs(delta)<1e-14)continue;
            const double t=(v.intercept-u.intercept)/delta;
            if(t>std::max(u.lo,v.lo) && t<std::min(u.hi,v.hi))events.push_back(t);
        }
        std::sort(events.begin(),events.end());events.erase(std::unique(events.begin(),events.end(),[](double x,double y){return std::abs(x-y)<1e-9;}),events.end());
        std::vector<Range> segments;
        for(size_t k=0;k+1<events.size();++k) {
            const double lo=events[k],hi=events[k+1],mid=(lo+hi)*.5;const Range *selected=nullptr;
            for(const auto &r:ranges)if(mid>=r.lo && mid<=r.hi && (!selected || r.intercept+r.slope*mid>selected->intercept+selected->slope*mid))selected=&r;
            if(!selected || hi-lo<1e-9)continue;
            auto segment=*selected;segment.lo=lo;segment.hi=hi;
            if(!segments.empty() && std::abs(segments.back().hi-lo)<1e-9 &&
               std::abs(segments.back().intercept-segment.intercept)<1e-6 && std::abs(segments.back().slope-segment.slope)<1e-6)segments.back().hi=hi;
            else segments.push_back(segment);
        }
        for(const auto &r:segments) {
            const Vector3 u{float(a.x+dx*r.lo),float(r.intercept+r.slope*r.lo),float(a.z+dz*r.lo)},
                          v{float(a.x+dx*r.hi),float(r.intercept+r.slope*r.hi),float(a.z+dz*r.hi)};
            if(planarDistance(u,v)<.00002f)continue;
            const Vector3 inward{float(-nx*span*2),0,float(-nz*span*2)};
            const double tangentSlope=r.slope/length;
            std::array<double,3> n{-tangentSlope*dx/length+inwardSlope*nx,1,-tangentSlope*dz/length+inwardSlope*nz};
            double d=r.intercept+n[0]*a.x+n[2]*a.z;
            const double magnitude=std::sqrt(n[0]*n[0]+1+n[2]*n[2]);for(auto &q:n)q/=magnitude;d/=magnitude;
            Plane roof;roof.hasPreciseNormal=true;roof.preciseNormal=n;roof.normal={float(n[0]),float(n[1]),float(n[2])};roof.distance=d;
            // The finite segment has a continuous extension beyond both ends.
            // Only boundary traces constrain the collar: interior source steps
            // must not turn into vertical walls inside otherwise shared land.
            result.push_back({{u,v,add(v,inward),add(u,inward)},roof,float(std::abs(tangentSlope)+inwardSlope)});
        }
    }
    return result;
}
}

#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
namespace dw::rockFormations {
cliffOptions::Mesh improvePlateauFootprint(cliffOptions::Mesh mesh) {
    ConstructionChecks requiredChecks;
    using Key=std::pair<float,float>;using Face=std::array<size_t,3>;
    const auto beforeAudit=auditStrictSurface(mesh);
    auto linksValid=[](const cliffOptions::Mesh &m,const StrictSurfaceAudit &a) {
        if(!a.nonmanifoldVertices)return true;
        for(const auto &piece:splitSurfaceComponents(m))if(auditStrictSurface(piece).nonmanifoldVertices)return false;
        return true;
    };
    if(beforeAudit.exact.nonmanifoldEdges || !linksValid(mesh,beforeAudit) || beforeAudit.selfIntersections || beforeAudit.coplanarOverlaps || beforeAudit.exact.degenerateFaces)
        throw std::runtime_error("Cannot improve an invalid plateau footprint");
    std::set<Key> keys;for(auto f:mesh.faces)for(auto p:f)keys.emplace(p.x,p.z);
    std::map<Key,size_t> ids;std::vector<Vector3> points;
    for(auto p:keys){ids.emplace(p,points.size());points.push_back({p.first,0,p.second});}
    std::vector<Face> faces;
    for(auto f:mesh.faces)faces.push_back({ids.at({f[0].x,f[0].z}),ids.at({f[1].x,f[1].z}),ids.at({f[2].x,f[2].z})});
    auto turn=[&](size_t a,size_t b,size_t c){return (double(points[b].x)-points[a].x)*(double(points[c].z)-points[a].z)-(double(points[b].z)-points[a].z)*(double(points[c].x)-points[a].x);};
    auto quality=[&](Face f) {
        double value=1;
        for(int k=0;k<3;++k) {
            const auto a=points[f[k]],b=points[f[(k+1)%3]],c=points[f[(k+2)%3]];
            const double x=double(b.x)-a.x,z=double(b.z)-a.z,u=double(c.x)-a.x,v=double(c.z)-a.z,d=(x*x+z*z)*(u*u+v*v),cross=x*v-z*u;
            value=std::min(value,d?cross*cross/d:0.);
        }
        return value;
    };
    size_t flips=0;
    for(int pass=0;pass<128;++pass) {
        std::map<std::pair<size_t,size_t>,std::vector<size_t>> edges;
        for(size_t i=0;i<faces.size();++i)for(int k=0;k<3;++k){auto a=faces[i][k],b=faces[i][(k+1)%3];if(b<a)std::swap(a,b);edges[{a,b}].push_back(i);}
        std::set<size_t> changed;
        for(const auto &[edge,owners]:edges) {
            if(owners.size()!=2 || changed.contains(owners[0]) || changed.contains(owners[1]))continue;
            const auto a=edge.first,b=edge.second;size_t c=0,d=0;
            for(auto id:faces[owners[0]])if(id!=a && id!=b)c=id;
            for(auto id:faces[owners[1]])if(id!=a && id!=b)d=id;
            if(edges.contains(std::minmax(c,d)) || turn(c,d,a)*turn(c,d,b)>=0 || turn(a,b,c)*turn(a,b,d)>=0)continue;
            const double x=std::floor((double(points[a].x)+points[b].x+points[c].x+points[d].x)*.25),
                         z=std::floor((double(points[a].z)+points[b].z+points[c].z+points[d].z)*.25);
            bool within=true,above=true,below=true;
            for(auto id:{a,b,c,d}) {
                const auto p=points[id];within &= p.x>=x && p.x<=x+1 && p.z>=z && p.z<=z+1;
                const double diagonal=(double(p.z)-z)-(double(p.x)-x);above &= diagonal>=0;below &= diagonal<=0;
            }
            if(!within || (!above && !below))continue;
            Face first{c,d,a},second{d,c,b};
            if(turn(first[0],first[1],first[2])>0)std::swap(first[1],first[2]);
            if(turn(second[0],second[1],second[2])>0)std::swap(second[1],second[2]);
            const double oldQuality=std::min(quality(faces[owners[0]]),quality(faces[owners[1]])),newQuality=std::min(quality(first),quality(second));
            if(newQuality<=oldQuality*(1+1e-6)+1e-14)continue;
            faces[owners[0]]=first;faces[owners[1]]=second;changed.insert(owners[0]);changed.insert(owners[1]);++flips;
        }
        if(changed.empty())break;
    }
    mesh.faces.clear();mesh.polygonEdges.clear();for(auto f:faces)mesh.faces.push_back({points[f[0]],points[f[1]],points[f[2]]});
    const auto after=auditStrictSurface(mesh);
    if(after.exact.boundaryEdges!=beforeAudit.exact.boundaryEdges || after.exact.components!=beforeAudit.exact.components || after.exact.nonmanifoldEdges ||
       !linksValid(mesh,after) || after.selfIntersections || after.coplanarOverlaps || after.exact.degenerateFaces || after.exact.duplicateFaces || after.exact.windingErrors)
        throw std::runtime_error("Plateau quality flips changed the domain");
    std::cout<<"PLATEAU_CHUNK_QUALITY triangles="<<mesh.faces.size()<<" flips="<<flips<<" grid_constraints=preserved exact_domain=PASS\n";
    return mesh;
}
}
#endif

#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
namespace dw::rockFormations {
cliffOptions::Mesh refinePlateauFootprint(cliffOptions::Mesh mesh,const std::function<float(Vector3)> &elevation) {
    ConstructionChecks requiredChecks;
    using P=std::array<float,2>;using Edge=std::pair<P,P>;
    auto key=[](Vector3 p){return P{p.x,p.z};};
    auto edge=[&](Vector3 a,Vector3 b){auto p=key(a),q=key(b);if(q<p)std::swap(p,q);return Edge{p,q};};
    auto turn=[](Vector3 a,Vector3 b,Vector3 c){return (double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);};
    const auto before=auditStrictSurface(mesh);size_t refinements=0;
    for(;refinements<256;++refinements) {
        size_t bad=mesh.faces.size();std::array<P,3> smallest;
        for(size_t i=0;i<mesh.faces.size();++i) {
            auto f=mesh.faces[i];for(auto &p:f)p.y=elevation(p);
            const double ax=double(f[1].x)-f[0].x,ay=double(f[1].y)-f[0].y,az=double(f[1].z)-f[0].z,
                         bx=double(f[2].x)-f[0].x,by=double(f[2].y)-f[0].y,bz=double(f[2].z)-f[0].z;
            const double nx=ay*bz-az*by,ny=az*bx-ax*bz,nz=ax*by-ay*bx,length=std::sqrt(nx*nx+ny*ny+nz*nz);
            if(length && ny/length>=.125)continue;
            std::array<P,3> order{key(f[0]),key(f[1]),key(f[2])};std::sort(order.begin(),order.end());
            if(bad==mesh.faces.size() || order<smallest){bad=i;smallest=order;}
        }
        if(bad==mesh.faces.size())break;
        struct Use{size_t face;int side;};std::map<Edge,std::vector<Use>> uses;std::set<P> vertices;
        for(size_t i=0;i<mesh.faces.size();++i)for(int k=0;k<3;++k){vertices.insert(key(mesh.faces[i][k]));uses[edge(mesh.faces[i][k],mesh.faces[i][(k+1)%3])].push_back({i,k});}
        const auto f=mesh.faces[bad];std::vector<std::pair<double,int>> candidates;
        for(int k=0;k<3;++k){const auto a=f[k],b=f[(k+1)%3];const double x=double(b.x)-a.x,z=double(b.z)-a.z;candidates.emplace_back(-(x*x+z*z),k);}
        std::sort(candidates.begin(),candidates.end());bool split=false;
        for(auto [negativeLength,k]:candidates) {
            const auto a=f[k],b=f[(k+1)%3],c=f[(k+2)%3];const double dx=double(b.x)-a.x,dz=double(b.z)-a.z,length=-negativeLength;
            if(length==0)continue;
            double t=((double(c.x)-a.x)*dx+(double(c.z)-a.z)*dz)/length;if(t<=.05 || t>=.95)t=.5;
            Vector3 p{float(a.x+t*dx),0,float(a.z+t*dz)};
            if(dx==0)p.x=a.x;if(dz==0)p.z=a.z;
            if(dx==dz) {
                const double constant=double(a.x)-a.z;
                const float xScale=std::max(std::abs(a.x),std::abs(b.x)),zScale=std::max(std::abs(a.z),std::abs(b.z));
                const double xu=std::nextafter(xScale,INFINITY)-xScale,zu=std::nextafter(zScale,INFINITY)-zScale;
                if(xu>=zu)p.z=float(double(p.x)-constant);else p.x=float(double(p.z)+constant);
            }
            if(vertices.contains(key(p)))continue;
            const auto &owners=uses.at(edge(a,b));
            if(owners.size()>2 || (owners.size()==1 && turn(a,b,p)!=0))continue;
            bool valid=true;
            for(auto owner:owners) {
                const auto old=mesh.faces[owner.face];const auto u=old[owner.side],v=old[(owner.side+1)%3],w=old[(owner.side+2)%3];
                valid &= turn(u,p,w)<0 && turn(p,v,w)<0;
            }
            if(!valid)continue;
            for(auto owner:owners) {
                const auto old=mesh.faces[owner.face];const auto u=old[owner.side],v=old[(owner.side+1)%3],w=old[(owner.side+2)%3];
                mesh.faces[owner.face]={u,p,w};mesh.faces.push_back({p,v,w});
            }
            split=true;break;
        }
        if(!split)throw std::runtime_error("Cap-boundary roof needs an unrepresentable refinement");
    }
    if(refinements==256)throw std::runtime_error("Cap-boundary roof refinement exceeds its construction limit");
    const auto after=auditStrictSurface(mesh);
    if(after.exact.nonmanifoldEdges || after.nonmanifoldVertices!=before.nonmanifoldVertices || after.selfIntersections || after.coplanarOverlaps ||
       after.exact.degenerateFaces || after.exact.duplicateFaces || after.exact.windingErrors || after.exact.components!=before.exact.components)
        throw std::runtime_error("Cap-boundary refinement changed the footprint topology");
    std::cout<<"PLATEAU_CAP_REFINEMENT splits="<<refinements<<" triangles="<<mesh.faces.size()<<" minimum_up=.125 topology=PASS\n";
    return mesh;
}
}
#endif
