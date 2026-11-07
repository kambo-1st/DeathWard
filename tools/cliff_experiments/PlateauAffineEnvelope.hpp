#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "PlateauChunks.hpp"
#include "PlateauVertexBlend.hpp"
#include <limits>

namespace dw::rockFormations {
// Clamp S toward T through an affine band T +/- K(1-W). K is shared by
// the complete field and bounds |S-T| at every source/grid cell vertex.
// The optional selector bounds only retained source cells; every excluded
// cell must have strictly positive weight throughout its convex domain.
// This experiment does not exempt the result from source/floor/topology checks.
// Thus cold cells keep S, full-weight cells reach T, and each intermediate
// ideal height lies between S and T (or its required floor). The routed
// realization still needs the ownership-fit and final source/floor guards.
// Two shared arrangements
// construct all max/min crossover lines; no quadratic vertex interpolation.
inline std::vector<GradedRoofCell> envelopePlateauSelectedSourcePlanes(
    const std::vector<GradedRoofCell> &cells,
    const std::function<PlateauVertexField(Vector3)> &sample,
    const std::function<bool(const Plane &)> &retained) {
    using Height=std::array<double,3>;
    auto height=[](const Plane &p)->Height {const auto n=planeNormal(p);if(n[1]<=0)throw std::runtime_error("Envelope has no upper roof");return {-n[0]/n[1],-n[2]/n[1],p.distance/n[1]};};
    auto at=[](const Height &h,Vector3 p){return h[0]*p.x+h[1]*p.z+h[2];};
    auto plane=[](Height h) {Plane p;p.hasPreciseNormal=true;const double length=std::hypot(h[0],h[1],1.);p.preciseNormal={-h[0]/length,1/length,-h[1]/length};p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};p.distance=h[2]/length;return p;};
    auto field=[&](const Polygon &p) {
        Vector3 centre{};for(auto q:p){centre.x+=q.x/float(p.size());centre.z+=q.z/float(p.size());}
        return sample(centre);
    };
    double band=0,retainedBand=0;size_t retainedCells=0,excludedWarmCells=0;
    for(const auto &cell:cells) {
        const auto f=field(cell.outline);const auto s=height(cell.roof),t=height(f.target);
        const bool original=retained && retained(cell.roof);
        if(original)++retainedCells;else if(retained)++excludedWarmCells;
        for(auto p:cell.outline) {
            const double contrast=std::abs(at(s,p)-at(t,p));band=std::max(band,contrast);
            if(original)retainedBand=std::max(retainedBand,contrast);
            else if(retained && at(height(f.weight),p)<=0)throw std::runtime_error("Excluded source band contains cold terrain");
        }
    }
    if(retained && retainedCells) {
        std::cout<<"PLATEAU_RETAINED_BAND all_sources_m="<<band<<" retained_sources_m="<<retainedBand<<" retained_cells="<<retainedCells<<" excluded_warm_cells="<<excludedWarmCells<<'\n';
        band=retainedBand;
    }
    band=std::nextafter(band,std::numeric_limits<double>::infinity());
    std::vector<GradedRoofCell> lower;
    for(const auto &cell:cells) {
        const auto f=field(cell.outline);const auto t=height(f.target),w=height(f.weight);
        const Height low{t[0]+band*w[0],t[1]+band*w[1],t[2]-band+band*w[2]};
        for(const auto &roof:{cell.roof,plane(low),f.lower})lower.push_back({cell.outline,roof});
    }
    // Retain each source/grid cell here: the upper band must still be sampled
    // on one affine grid triangle after this first max operation.
    const auto raised=partitionPlateauEnvelopePieces(lower,true);
    std::vector<GradedRoofCell> upper;
    for(const auto &cell:raised) {
        const auto f=field(cell.outline);const auto t=height(f.target),w=height(f.weight),s=height(cell.roof);
        const Height high{t[0]-band*w[0],t[1]-band*w[1],t[2]+band-band*w[2]};
        upper.push_back({cell.outline,plane({-s[0],-s[1],-s[2]})});
        upper.push_back({cell.outline,plane({-high[0],-high[1],-high[2]})});
    }
    auto result=partitionPlateauEnvelopePieces(upper,false);
    for(auto &cell:result) {
        const auto h=height(cell.roof);cell.roof=plane({-h[0],-h[1],-h[2]});
        for(auto &p:cell.outline)p.y=float(-at(h,p));
    }
    std::cout<<"PLATEAU_AFFINE_ENVELOPE input_cells="<<cells.size()<<" band_m="<<band<<" raised_cells="<<raised.size()<<" output_cells="<<result.size()<<'\n';
    return result;
}
inline std::vector<GradedRoofCell> envelopePlateauSourcePlanes(const std::vector<GradedRoofCell> &cells,
    const std::function<PlateauVertexField(Vector3)> &sample) {
    return envelopePlateauSelectedSourcePlanes(cells,sample,{});
}

}
#endif
