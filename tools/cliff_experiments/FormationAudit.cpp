#include "CliffExperiments.hpp"
#include "RockFormations.hpp"
#include "PlateauRegion.hpp"
#include "FormationSections.hpp"
#include <fstream>
#include "combat/Simulation.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc,char **argv) {
    try {
        if(argc==7 && std::string_view(argv[1])=="--region-probe") {
            const auto seed=std::stoull(argv[2]);const int floor=std::stoi(argv[3]),room=std::stoi(argv[4]);const size_t candidate=std::stoul(argv[5]);
            dw::Simulation run(seed,1,{},dw::MissionTheme::Canyon,true,false,dw::WitnessAccount::None,floor);
            if(room<0 || room>=run.arena.roomCount())throw std::runtime_error("Invalid region probe room");
            auto parameters=dw::CanyonVisualParameters::load("assets/visual/canyon.cfg");parameters.irregularFacets=false;
            const auto base=dw::buildCanyonAppearance(run.arena,parameters);
            const auto sections=dw::rockFormations::selectSections(base,run.arena.rooms[size_t(room)].bounds);
            if(candidate==0 || candidate>sections.size())throw std::runtime_error("Invalid region probe candidate");
            const auto &section=sections[candidate-1];
            if(!section.fallback.empty())throw std::runtime_error(section.fallback);
            const auto region=dw::rockFormations::planPlateauRegion(base,section.wall);
            dw::rockFormations::writePlateauRegion(argv[6],region);
            const auto domains=dw::rockFormations::plateauRegionFootprint(region.domains);
            std::cout<<"REGION_PLAN key="<<region.key<<" components="<<region.components<<" source_faces="<<region.sourceFaces
                     <<" selected_walls="<<region.selectedWalls<<" neighbour_walls="<<region.neighbourWalls<<" area_m2="<<region.projectedArea
                     <<" boundary="<<region.boundary.size()<<" shared_domains="<<domains.size()<<'\n';
            return 0;
        }
        if(argc==3 && std::string_view(argv[1])=="--boundary-probe") {
            std::ifstream in(argv[2]);size_t count=0;in>>count;
            dw::cliffOptions::Mesh mesh;mesh.faces.resize(count);
            for(auto &t:mesh.faces)for(auto &p:t)in>>p.x>>p.y>>p.z;
            in>>count;std::vector<dw::rockFormations::Volume> volumes(count);
            for(auto &v:volumes) {
                in>>count;v.planes.resize(count);
                for(auto &p:v.planes) {
                    p.hasPreciseNormal=true;in>>p.preciseNormal[0]>>p.preciseNormal[1]>>p.preciseNormal[2]>>p.distance;
                }
            }
            if(!in)throw std::runtime_error("Invalid boundary probe");
            const auto a=dw::rockFormations::auditBoundaryCoverage(mesh,volumes);
            std::cout<<"SOURCE_BOUNDARY triangles="<<a.triangles<<" buried="<<a.buriedFragments<<" detached="<<a.detachedFragments<<'\n';
            return a.buriedFragments || a.detachedFragments ? 2 : 0;
        }
        if(argc!=4)throw std::runtime_error("Usage: deathward_formation_audit seed floor room | --boundary-probe file");
        const auto seed=std::stoull(argv[1]);const int floor=std::stoi(argv[2]),room=std::stoi(argv[3]);
#ifdef _WIN32
        _putenv_s("DW_CLIFF_LAYOUT","seeded");_putenv_s("DW_CLIFF_OPTION","formations");
        _putenv_s("DW_CLIFF_DETAIL","1");_putenv_s("DW_CLIFF_ROOM",argv[3]);
#else
        setenv("DW_CLIFF_LAYOUT","seeded",1);setenv("DW_CLIFF_OPTION","formations",1);
        setenv("DW_CLIFF_DETAIL","1",1);setenv("DW_CLIFF_ROOM",argv[3],1);
#endif
        dw::Simulation run(seed,1,{},dw::MissionTheme::Canyon,true,false,dw::WitnessAccount::None,floor);
        if(room<0 || room>=run.arena.roomCount())throw std::runtime_error("Invalid audit room");
        const auto parameters=dw::CanyonVisualParameters::load("assets/visual/canyon.cfg");
        dw::cliffExperimentAppearance(run.arena,parameters);
    }catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}
}
