#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "PlateauSourceReuse.hpp"
#include <fstream>

namespace dw::rockFormations::capDomain {
// Limit the proposed edit, before solids are built, to whole footprint regions
// having positive-area cap contact. The adapter must preserve original terrain
// outside the selected columns. This is not deletion of Boolean components.
inline std::vector<bool> retainedSource(const std::vector<GradedRoofCell> &cells,
                                      const std::vector<Polygon> &caps,
                                      const char *certificate=nullptr) {
    ConstructionTiming timing("cap_connected_domain");ConstructionChecks checks;
    using namespace sourceReuse;
    std::vector<Polygon> domains;for(const auto &cell:cells)domains.push_back(cell.outline);
    const auto flat=meshPlateauFootprint(domains);
    const auto pieces=splitSurfaceComponents(flat);
    if(pieces.empty())throw std::runtime_error("Cap domain has no roof footprint");
    struct Triangle {Ring ring;std::vector<H> cuts;Bounds box;};
    std::vector<std::vector<Triangle>> triangles(pieces.size());
    for(size_t i=0;i<pieces.size();++i)for(const auto &face:pieces[i].faces) {
        auto ring=project({face[0],face[1],face[2]});
        triangles[i].push_back({ring,sides(ring),bounds(ring)});
    }
    std::vector<Ring> capRings;std::vector<std::vector<H>> capCuts;std::vector<Bounds> capBoxes;
    for(const auto &cap:caps){capRings.push_back(project(cap));capCuts.push_back(sides(capRings.back()));capBoxes.push_back(bounds(capRings.back()));}
    std::vector<size_t> owners;std::vector<bool> attached(pieces.size(),false);
    for(const auto &cell:cells) {
        const auto ring=project(cell.outline);P center{0,0};
        for(const auto &p:ring){center[0]+=p[0];center[1]+=p[1];}
        center[0]/=ring.size();center[1]/=ring.size();
        size_t owner=pieces.size();
        for(size_t i=0;i<triangles.size();++i)for(const auto &triangle:triangles[i]) {
            const auto box=triangle.box;const double x=center[0].convert_to<double>(),z=center[1].convert_to<double>();
            if(x<box.lx || x>box.hx || z<box.lz || z>box.hz)continue;
            if(std::all_of(triangle.cuts.begin(),triangle.cuts.end(),[&](const auto &h){return value(h,center)<=0;})) {
                if(owner!=pieces.size() && owner!=i)throw std::runtime_error("Roof cell has ambiguous cap-domain component");
                owner=i;break;
            }
        }
        if(owner==pieces.size())throw std::runtime_error("Cannot assign roof cell to cap domain");
        owners.push_back(owner);
        const auto box=bounds(ring);
        for(size_t cap=0;cap<capCuts.size() && !attached[owner];++cap)if(meets(box,capBoxes[cap])) {
            auto overlap=ring;for(const auto &cut:capCuts[cap])overlap=clip(overlap,cut);
            if(!overlap.empty())attached[owner]=true;
        }
    }
    std::vector<bool> retained;size_t count=0;
    for(auto owner:owners){retained.push_back(!attached[owner]);count+=retained.back();}
    if(count==cells.size())throw std::runtime_error("No roof component has positive cap contact");
    if(certificate) {
        std::ofstream out(certificate);out.precision(17);
        out<<"{\"scope\":\"Whole construction footprint components with positive cap contact; original backing preservation and full assembly still require validation\",\"cells\":"<<cells.size()<<",\"components\":"<<pieces.size()<<",\"component_attached\":[";
        for(size_t i=0;i<attached.size();++i){if(i)out<<',';out<<(attached[i]?"true":"false");}
        out<<"],\"cell_components\":[";for(size_t i=0;i<owners.size();++i){if(i)out<<',';out<<owners[i];}
        out<<"],\"retained_source_cells\":[";for(size_t i=0;i<retained.size();++i){if(i)out<<',';out<<(retained[i]?"true":"false");}
        out<<"],\"post_union_deletion\":false,\"full_assembly_proved\":false}\n";
        if(!out)throw std::runtime_error("Cannot write cap domain certificate");
    }
    std::cout<<"PLATEAU_CAP_DOMAIN components="<<pieces.size()<<" cap_components="<<std::count(attached.begin(),attached.end(),true)
             <<" input_cells="<<cells.size()<<" original_backing_cells="<<count<<" constructed_cells="<<cells.size()-count<<" whole_components=1\n";
    return retained;
}
}
#endif
