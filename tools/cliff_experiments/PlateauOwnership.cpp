#include "PlateauChunks.hpp"
#include "FormationTiming.hpp"
#include "PlateauSnapRound.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#ifdef DEATHWARD_CLIFF_REGION_EXPERIMENT
#include <boost/polygon/polygon.hpp>
#include <manifold/polygon.h>
#endif

namespace dw::rockFormations {
static std::vector<GradedRoofCell> partitionOwnership(const std::vector<GradedRoofCell> &input,const std::vector<Polygon> &holes,const std::vector<Polygon> &domainCuts,bool retainGrid,bool pruneDisjoint=false) {
#ifndef DEATHWARD_CLIFF_REGION_EXPERIMENT
    throw std::runtime_error("Source ownership requires the region experiment");
#else
    ConstructionChecks requiredChecks;
    if(!domainCuts.empty() && domainCuts.size()!=input.size())throw std::runtime_error("Ownership domain/cut count differs");
    if(retainGrid && domainCuts.empty())throw std::runtime_error("Retained ownership grid needs paired cuts");
    namespace bp=boost::polygon;using Coordinate=long long;
    constexpr double fitLimit=.00004;
    float extent=1;for(const auto &cell:input)for(auto p:cell.outline)extent=std::max({extent,std::abs(p.x),std::abs(p.z)});
    // Keep the shared construction grid, enlarged only where render-float
    // spacing requires it. Every output coordinate remains representable.
    const double quantum=std::max(double(std::nextafter(extent,std::numeric_limits<float>::infinity())-extent),1./65536);
    const double scale=1/quantum;
    const bool regularize=std::getenv("DW_CLIFF_SOURCE_REGULARIZE")!=nullptr;
    constexpr double verticalPadding=.00004;
    auto grow=[&](const Polygon &p) {
        auto turn=[](Vector3 a,Vector3 b,Vector3 c){return (double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);};
        bool positive=false,negative=false;
        for(size_t k=0;k<p.size();++k){const auto t=turn(p[k],p[(k+1)%p.size()],p[(k+2)%p.size()]);positive|=t>0;negative|=t<0;}
        if(positive && negative)throw std::runtime_error("Source regularization requires convex input domains");
        Polygon points;
        for(auto q:p)for(int x:{-1,1})for(int z:{-1,1})points.push_back({float(double(q.x)+x*quantum),0,float(double(q.z)+z*quantum)});
        std::sort(points.begin(),points.end(),[](auto a,auto b){return std::pair{a.x,a.z}<std::pair{b.x,b.z};});
        points.erase(std::unique(points.begin(),points.end(),[](auto a,auto b){return a.x==b.x && a.z==b.z;}),points.end());
        Polygon hull;
        for(auto q:points){while(hull.size()>1 && turn(hull[hull.size()-2],hull.back(),q)<=0)hull.pop_back();hull.push_back(q);}
        const auto lower=hull.size();
        for(auto q=points.rbegin()+1;q!=points.rend();++q){while(hull.size()>lower && turn(hull[hull.size()-2],hull.back(),*q)<=0)hull.pop_back();hull.push_back(*q);}
        if(!hull.empty())hull.pop_back();std::reverse(hull.begin(),hull.end());return hull;
    };
    if(const auto path=std::getenv("DW_CLIFF_OWNER_SOURCE_PROBE")) {
        std::ofstream out(path);out.precision(17);out<<"{\"regularized\":"<<regularize<<",\"grid_m\":"<<quantum<<",\"vertical_padding_m\":"<<(regularize?verticalPadding:0)<<",\"cells\":[";
        auto polygon=[&](const Polygon &p){out<<'[';for(size_t k=0;k<p.size();++k){if(k)out<<',';out<<'['<<p[k].x<<','<<p[k].y<<','<<p[k].z<<']';}out<<']';};
        for(size_t i=0;i<input.size();++i){if(i)out<<',';const auto n=planeNormal(input[i].roof);out<<"{\"outline\":";polygon(input[i].outline);if(!domainCuts.empty()){out<<",\"domain_cut\":";polygon(domainCuts[i]);}out<<",\"plane\":["<<n[0]<<','<<n[1]<<','<<n[2]<<','<<input[i].roof.distance<<"]}";}
        out<<"],\"holes\":[";for(size_t i=0;i<holes.size();++i){if(i)out<<',';polygon(holes[i]);}out<<"]}\n";
        if(!out)throw std::runtime_error("Cannot write original ownership source cells");
    }
    // Stable geometry ordering makes ownership independent of chunk grouping.
    struct Input {GradedRoofCell cell;Polygon cut;std::array<double,4> plane;std::vector<std::pair<float,float>> points,cutPoints;};
    std::vector<Input> ordered;
    for(size_t i=0;i<input.size();++i) {auto cell=input[i];
        const auto n=planeNormal(cell.roof);
        if(regularize){cell.outline=grow(cell.outline);cell.roof.distance+=quantum*(std::abs(n[0])+std::abs(n[2]))+verticalPadding*n[1];}
        Input v{cell,domainCuts.empty()?Polygon{}:domainCuts[i],{n[0],n[1],n[2],cell.roof.distance},{},{}};
        for(auto p:v.cut)v.cutPoints.emplace_back(p.x,p.z);std::sort(v.cutPoints.begin(),v.cutPoints.end());
        for(auto p:cell.outline)v.points.emplace_back(p.x,p.z);std::sort(v.points.begin(),v.points.end());ordered.push_back(std::move(v));
    }
    std::sort(ordered.begin(),ordered.end(),[](const auto &a,const auto &b){return a.plane!=b.plane?a.plane<b.plane:(a.points!=b.points?a.points<b.points:a.cutPoints<b.cutPoints);});
    std::vector<GradedRoofCell> cells;std::vector<Polygon> cuts;
    for(auto &v:ordered){cells.push_back(std::move(v.cell));cuts.push_back(std::move(v.cut));}
    bp::property_merge<Coordinate,size_t> merge;
    const bool snapRound=std::getenv("DW_CLIFF_SOURCE_SNAP_ROUND")!=nullptr;
    std::vector<LabelledSnapRing> rings;
    auto insert=[&](const Polygon &outline,size_t label) {
        LabelledSnapRing ring{{},label};
        for(auto p:outline)ring.points.push_back({std::llround(double(p.x)*scale),std::llround(double(p.z)*scale)});
        rings.push_back(std::move(ring));
    };
    struct Roof {double x,z,c;double at(double a,double b)const{return x*a+z*b+c;}};
    struct Bounds {double lx,lz,hx,hz;};
    using Wide=boost::multiprecision::int256_t;
    using Point=std::array<Coordinate,2>;
    std::vector<std::vector<Point>> integerOutlines;std::vector<bool> convex;
    if(pruneDisjoint)for(const auto &cell:cells) {
        std::vector<Point> points;for(auto p:cell.outline)points.push_back({std::llround(double(p.x)*scale),std::llround(double(p.z)*scale)});
        bool positive=false,negative=false;
        for(size_t k=0;k<points.size();++k){const auto a=points[k],b=points[(k+1)%points.size()],c=points[(k+2)%points.size()];const Wide turn=(Wide(b[0])-a[0])*(Wide(c[1])-b[1])-(Wide(b[1])-a[1])*(Wide(c[0])-b[0]);positive|=turn>0;negative|=turn<0;}
        convex.push_back((positive||negative) && !(positive&&negative));integerOutlines.push_back(std::move(points));
    }
    auto overlap=[&](size_t i,size_t j) {
        if(!convex[i] || !convex[j])return true; // No pruning without a convexity proof.
        const auto &a=integerOutlines[i],&b=integerOutlines[j];
        for(const auto *ring:{&a,&b})for(size_t k=0;k<ring->size();++k) {
            const auto p=(*ring)[k],q=(*ring)[(k+1)%ring->size()];
            const Wide x=Wide(q[0])-p[0],z=Wide(q[1])-p[1];if(x==0 && z==0)continue;
            auto value=[&](const Point &r)->Wide{return x*r[1]-z*r[0];};
            Wide alo=value(a[0]),ahi=alo,blo=value(b[0]),bhi=blo;
            for(auto r:a){const auto v=value(r);alo=std::min(alo,v);ahi=std::max(ahi,v);}
            for(auto r:b){const auto v=value(r);blo=std::min(blo,v);bhi=std::max(bhi,v);}
            if(ahi<=blo || bhi<=alo)return false;
        }
        return true;
    };
    std::vector<Roof> roofs;std::vector<Bounds> boxes;
    std::map<std::pair<int,int>,std::vector<size_t>> inputBins;
    std::set<std::pair<size_t,size_t>> pairs;
    for(size_t i=0;i<cells.size();++i) {
        insert(cells[i].outline,i);const auto n=planeNormal(cells[i].roof);
        if(!domainCuts.empty())insert(cuts[i],cells.size()+i);
        if(n[1]<=0)throw std::runtime_error("Ownership input has no upper roof");
        roofs.push_back({-n[0]/n[1],-n[2]/n[1],cells[i].roof.distance/n[1]});
        Bounds b{1e30,1e30,-1e30,-1e30};for(auto p:cells[i].outline){b.lx=std::min(b.lx,double(p.x));b.hx=std::max(b.hx,double(p.x));b.lz=std::min(b.lz,double(p.z));b.hz=std::max(b.hz,double(p.z));}boxes.push_back(b);
        if(!domainCuts.empty()) {
            Bounds cut{1e30,1e30,-1e30,-1e30};for(auto p:cuts[i]){cut.lx=std::min(cut.lx,double(p.x));cut.hx=std::max(cut.hx,double(p.x));cut.lz=std::min(cut.lz,double(p.z));cut.hz=std::max(cut.hz,double(p.z));}
            b={std::max(b.lx,cut.lx),std::max(b.lz,cut.lz),std::min(b.hx,cut.hx),std::min(b.hz,cut.hz)};boxes.back()=b;
        }
        for(int x=int(std::floor(b.lx));x<=int(std::floor(b.hx));++x)for(int z=int(std::floor(b.lz));z<=int(std::floor(b.hz));++z) {
            auto &near=inputBins[{x,z}];for(auto j:near)pairs.insert({j,i});near.push_back(i);
        }
    }
    size_t nextLabel=cells.size()*(domainCuts.empty()?1:2),constraints=0,disjointPairs=0;
    for(auto [i,j]:pairs) {
        const auto a=boxes[i],b=boxes[j];const double lx=std::max(a.lx,b.lx),lz=std::max(a.lz,b.lz),hx=std::min(a.hx,b.hx),hz=std::min(a.hz,b.hz);
        if(lx>=hx || lz>=hz)continue;
        if(pruneDisjoint && !overlap(i,j)){++disjointPairs;continue;}
        const Roof d{roofs[j].x-roofs[i].x,roofs[j].z-roofs[i].z,roofs[j].c-roofs[i].c};
        double low=1e30,high=-1e30;for(auto x:{lx,hx})for(auto z:{lz,hz}){const auto v=d.at(x,z);low=std::min(low,v);high=std::max(high,v);}
        if(low>=0 || high<=0 || high-low<=fitLimit)continue;
        std::vector<std::array<long double,2>> rectangle{{lx,lz},{lx,hz},{hx,hz},{hx,lz}},clipped;
        for(size_t k=0;k<rectangle.size();++k) {
            const auto p=rectangle[k],q=rectangle[(k+1)%rectangle.size()];const long double u=d.x*p[0]+d.z*p[1]+d.c,v=d.x*q[0]+d.z*q[1]+d.c;
            if(u>=0)clipped.push_back(p);
            if(u*v<0){const auto t=u/(u-v);clipped.push_back({p[0]+t*(q[0]-p[0]),p[1]+t*(q[1]-p[1])});}
        }
        std::vector<bp::point_data<Coordinate>> points;
        for(auto p:clipped){bp::point_data<Coordinate> q(std::llround(p[0]*scale),std::llround(p[1]*scale));if(points.empty() || points.back()!=q)points.push_back(q);}
        if(points.size()>1 && points.front()==points.back())points.pop_back();
        long double area=0;for(size_t k=0;k<points.size();++k)area+=static_cast<long double>(bp::x(points[k]))*bp::y(points[(k+1)%points.size()])-static_cast<long double>(bp::y(points[k]))*bp::x(points[(k+1)%points.size()]);
        if(points.size()<3 || area==0)continue;
        LabelledSnapRing ring{{},nextLabel++};for(auto p:points)ring.points.push_back({bp::x(p),bp::y(p)});rings.push_back(std::move(ring));++constraints;
    }
    const size_t holeBegin=nextLabel;for(const auto &hole:holes)insert(regularize?grow(hole):hole,nextLabel++);
    if(pruneDisjoint)std::cout<<"PLATEAU_ENVELOPE_CONSTRAINTS candidate_pairs="<<pairs.size()<<" disjoint_pairs="<<disjointPairs<<" constraints="<<constraints<<" exact_integer_sat=1\n";
    if(snapRound)snapRoundPlateauRings(rings,std::llround(scale));
    for(const auto &ring:rings) {
        std::vector<bp::point_data<Coordinate>> points;for(auto p:ring.points)points.emplace_back(p[0],p[1]);
        bp::polygon_data<Coordinate> polygon;bp::set_points(polygon,points.begin(),points.end());merge.insert(polygon,ring.label);
    }
    std::map<std::set<size_t>,bp::polygon_set_data<Coordinate>> regions;merge.merge(regions);
    using GroupKey=std::pair<std::array<double,4>,std::vector<std::pair<float,float>>>;
    std::map<GroupKey,size_t> planeGroups;
    std::vector<bp::polygon_set_data<Coordinate>> grouped;
    std::vector<Plane> groupRoofs;size_t overlaps=0;double maximumFit=0,maximumLift=0;
    for(auto &[labels,set]:regions) {
        std::vector<size_t> owners;bool cut=false;
        for(auto label:labels){if(label<cells.size() && (domainCuts.empty() || labels.contains(cells.size()+label)))owners.push_back(label);else if(label>=holeBegin)cut=true;}
        if(cut || owners.empty())continue;
        overlaps+=owners.size()>1;
        std::vector<bp::polygon_with_holes_data<Coordinate>> shapes;set.get(shapes);
        for(const auto &shape:shapes) {
            std::vector<std::pair<double,double>> corners;
            auto append=[&](const auto &loop){for(auto at=bp::begin_points(loop);at!=bp::end_points(loop);++at)corners.emplace_back(double(bp::x(*at))/scale,double(bp::y(*at))/scale);};
            append(shape);for(auto h=bp::begin_holes(shape);h!=bp::end_holes(shape);++h)append(*h);
            size_t winner=owners.front();double best=1e30;
            for(auto candidate:owners) {
                double deficit=0;
                for(auto [x,z]:corners){double top=-1e30;for(auto i:owners)top=std::max(top,roofs[i].at(x,z));deficit=std::max(deficit,top-roofs[candidate].at(x,z));}
                if(deficit<best){best=deficit;winner=candidate;}
            }
            if(best>2*fitLimit){std::cout<<"PLATEAU_OWNERSHIP_FIT_REJECT fit_m="<<best<<" owners="<<owners.size()<<'\n';throw std::runtime_error("Ownership roof crosses unresolved source planes");}
            auto chosen=cells[winner].roof;const auto n=planeNormal(chosen);
            // The selected source plane lies between zero and `best` below
            // the upper envelope throughout this region. A small lift can
            // centre that bounded error without changing the source slope.
            const double lift=best>fitLimit?best/2:0;
            chosen.distance+=lift*n[1];maximumLift=std::max(maximumLift,lift);
            maximumFit=std::max(maximumFit,lift?best/2:best);
            GroupKey key{{n[0],n[1],n[2],chosen.distance},{}};
            if(retainGrid){for(auto p:cuts[winner])key.second.emplace_back(p.x,p.z);std::sort(key.second.begin(),key.second.end());}
            auto [at,added]=planeGroups.emplace(key,grouped.size());if(added){grouped.emplace_back();groupRoofs.push_back(chosen);}
            grouped[at->second].insert(shape);
        }
    }
    struct Part {cliffOptions::Triangle face;std::vector<size_t> owners;};
    std::vector<Part> parts;std::vector<Polygon> domains;size_t zeroAreaTriangles=0;
    for(size_t group=0;group<grouped.size();++group) {
        std::vector<bp::polygon_with_holes_data<Coordinate>> shapes;grouped[group].get(shapes);
        for(const auto &shape:shapes) {
            auto area2=[](const auto &ring) {
                std::vector<std::array<long double,2>> p;for(auto at=bp::begin_points(ring);at!=bp::end_points(ring);++at)p.push_back({static_cast<long double>(bp::x(*at)),static_cast<long double>(bp::y(*at))});
                long double area=0;for(size_t k=1;k+1<p.size();++k)area+=(p[k][0]-p[0][0])*(p[k+1][1]-p[0][1])-(p[k][1]-p[0][1])*(p[k+1][0]-p[0][0]);return std::abs(area);
            };
            long double expectedArea=area2(shape),emittedArea=0;
            for(auto h=bp::begin_holes(shape);h!=bp::end_holes(shape);++h)expectedArea-=area2(*h);
            bp::polygon_set_data<Coordinate> emittedSet;
            manifold::Polygons contours;std::vector<Vector3> vertices;
            auto contour=[&](const auto &ring,bool hole) {
                manifold::SimplePolygon polygon;
                for(auto at=bp::begin_points(ring);at!=bp::end_points(ring);++at)polygon.push_back({double(bp::x(*at))/scale,double(bp::y(*at))/scale});
                if(polygon.size()>1 && polygon.front()==polygon.back())polygon.pop_back();
                bool changed=true;
                while(changed && polygon.size()>3) {
                    changed=false;
                    for(size_t i=0;i<polygon.size();++i) {
                        const auto a=polygon[(i+polygon.size()-1)%polygon.size()],b=polygon[i],c=polygon[(i+1)%polygon.size()];
                        if((b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x)==0){polygon.erase(polygon.begin()+i);changed=true;break;}
                    }
                }
                double area=0;for(size_t i=0;i<polygon.size();++i)area+=polygon[i].x*polygon[(i+1)%polygon.size()].y-polygon[i].y*polygon[(i+1)%polygon.size()].x;
                if((area<0)!=hole)std::reverse(polygon.begin(),polygon.end());
                for(auto p:polygon)vertices.push_back({float(p.x),0,float(p.y)});contours.push_back(std::move(polygon));
            };
            contour(shape,false);for(auto h=bp::begin_holes(shape);h!=bp::end_holes(shape);++h)contour(*h,true);
            for(auto t:manifold::Triangulate(contours,0)) {
                cliffOptions::Triangle f{vertices.at(t.x),vertices.at(t.y),vertices.at(t.z)};
                const double turn=(double(f[1].x)-f[0].x)*(double(f[2].z)-f[0].z)-(double(f[1].z)-f[0].z)*(double(f[2].x)-f[0].x);
                if(turn==0){++zeroAreaTriangles;continue;}
                if(turn>0)std::swap(f[1],f[2]);
                const long double exactTurn=(static_cast<long double>(f[1].x)-f[0].x)*(static_cast<long double>(f[2].z)-f[0].z)-(static_cast<long double>(f[1].z)-f[0].z)*(static_cast<long double>(f[2].x)-f[0].x);
                emittedArea+=std::abs(exactTurn)*scale*scale;
                std::vector<bp::point_data<Coordinate>> triangle;for(auto p:f)triangle.emplace_back(std::llround(double(p.x)*scale),std::llround(double(p.z)*scale));
                bp::polygon_data<Coordinate> polygon;bp::set_points(polygon,triangle.begin(),triangle.end());emittedSet.insert(polygon);
                parts.push_back({f,{group}});domains.push_back({f[0],f[1],f[2]});
            }
            bp::polygon_set_data<Coordinate> expectedSet;expectedSet.insert(shape);
            using namespace bp::operators;auto difference=emittedSet;difference^=expectedSet;
            // Only mathematically zero emissions can be omitted. Exact area
            // and symmetric difference certify all positive projected area.
            if(emittedArea!=expectedArea || !difference.empty())throw std::runtime_error("Ownership triangulation changes projected region coverage");
        }
    }
    auto flat=meshPlateauFootprint(domains);
    const auto audit=auditStrictSurface(flat);
    if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
        const auto projected=std::string(path)+".ownership.json";
        writeSurfaceProbe(projected.c_str(),flat,{},audit);
    }
    std::cout<<"PLATEAU_OWNERSHIP_PLANAR inputs="<<cells.size()<<" shared_domain_cuts="<<!domainCuts.empty()<<" regions="<<regions.size()<<" constraints="<<constraints<<" grid_m="<<quantum<<" regularized="<<regularize<<" zero_area_triangles="<<zeroAreaTriangles<<" coverage=PASS plane_groups="<<grouped.size()<<" overlaps="<<overlaps<<" triangles="<<flat.faces.size()
             <<" nonmanifold="<<audit.exact.nonmanifoldEdges<<" links="<<audit.nonmanifoldVertices<<" crossings="<<audit.selfIntersections<<" overlaps_remaining="<<audit.coplanarOverlaps<<'\n';
    if(audit.exact.nonmanifoldEdges || audit.selfIntersections || audit.coplanarOverlaps || audit.exact.degenerateFaces || audit.exact.duplicateFaces || audit.exact.windingErrors) {
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE"))writeSurfaceProbe(path,flat,{},audit);
        throw std::runtime_error("Shared source ownership is not a valid projected partition");
    }
    std::map<std::pair<int,int>,std::vector<size_t>> bins;
    for(size_t i=0;i<parts.size();++i) {
        double lx=1e30,lz=1e30,hx=-1e30,hz=-1e30;
        for(auto p:parts[i].face){lx=std::min(lx,double(p.x));hx=std::max(hx,double(p.x));lz=std::min(lz,double(p.z));hz=std::max(hz,double(p.z));}
        for(int x=int(std::floor(lx));x<=int(std::floor(hx));++x)for(int z=int(std::floor(lz));z<=int(std::floor(hz));++z)bins[{x,z}].push_back(i);
    }
    auto height=[](const Plane &p,Vector3 q){const auto n=planeNormal(p);if(n[1]<=0)throw std::runtime_error("Ownership input has no upper roof");return (p.distance-n[0]*q.x-n[2]*q.z)/n[1];};
    std::map<size_t,std::vector<Polygon>> convexParts;
    for(auto f:flat.faces) {
        const double x=(double(f[0].x)+f[1].x+f[2].x)/3,z=(double(f[0].z)+f[1].z+f[2].z)/3;
        const auto found=bins.find({int(std::floor(x)),int(std::floor(z))});size_t selected=parts.size();
        if(found!=bins.end())for(auto i:found->second) {
            const auto &p=parts[i].face;bool inside=true;
            for(int k=0;k<3;++k){auto a=p[k],b=p[(k+1)%3];inside &= (double(b.x)-a.x)*(z-a.z)-(double(b.z)-a.z)*(x-a.x)<=0;}
            if(inside){selected=i;break;}
        }
        if(selected==parts.size())throw std::runtime_error("Conforming ownership triangle has no source region");
        const auto &owners=parts[selected].owners;
        convexParts[owners.front()].push_back({f[0],f[1],f[2]});
    }
    std::vector<GradedRoofCell> result;
    for(auto &[owner,polygons]:convexParts) {
        auto area=[](const Polygon &p){long double a=0;for(size_t k=1;k+1<p.size();++k)a+=(static_cast<long double>(p[k].x)-p[0].x)*(static_cast<long double>(p[k+1].z)-p[0].z)-(static_cast<long double>(p[k].z)-p[0].z)*(static_cast<long double>(p[k+1].x)-p[0].x);return std::abs(a);};
        std::stable_sort(polygons.begin(),polygons.end(),[&](const auto &a,const auto &b){return area(a)<area(b);});
        const auto &roof=groupRoofs[owner];
        for(auto p:consolidateExactPlanar(std::move(polygons),{0,1,0})) {
            for(auto &v:p)v.y=float(height(roof,v));result.push_back({std::move(p),roof});
        }
    }
    std::cout<<"PLATEAU_OWNERSHIP_ROOF cells="<<result.size()<<" retain_grid="<<retainGrid<<" maximum_vertical_fit_m="<<maximumFit<<" maximum_plane_lift_m="<<maximumLift<<" fit_limit_m="<<fitLimit<<'\n';
    return result;
#endif
}
std::vector<GradedRoofCell> partitionPlateauCellOwnership(const std::vector<GradedRoofCell> &input,const std::vector<Polygon> &holes,const std::vector<Polygon> &cuts) {
    return partitionOwnership(input,holes,cuts,false);
}
std::vector<GradedRoofCell> partitionPlateauGridOwnership(const std::vector<GradedRoofCell> &input,const std::vector<Polygon> &holes,const std::vector<Polygon> &cuts) {
    return partitionOwnership(input,holes,cuts,true);
}
std::vector<GradedRoofCell> partitionPlateauEnvelopePieces(const std::vector<GradedRoofCell> &input,bool retainDomains) {
    std::vector<Polygon> cuts;if(retainDomains)for(const auto &cell:input)cuts.push_back(cell.outline);
    return partitionOwnership(input,{},cuts,retainDomains,true);
}
}
