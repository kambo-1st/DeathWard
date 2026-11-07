#include "FormationSections.hpp"
#include "combat/Simulation.hpp"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>

int main(int argc,char **argv) {
    try {
        if(argc<2 || argc>3)throw std::runtime_error("Usage: deathward_formation_cases manifest.json [--inventory]");
        const bool inventory=argc==3 && std::string_view(argv[2])=="--inventory";
        if(argc==3 && !inventory)throw std::runtime_error("Unknown inventory option");
        const auto destination=std::filesystem::path(argv[1]);
        std::filesystem::create_directories(destination.parent_path());
        std::ofstream out(destination);if(!out)throw std::runtime_error("Cannot open manifest output");
        out<<"[\n";bool first=true;
        for(uint64_t seed:{0ULL,42ULL,404ULL,1866ULL}) {
            dw::Simulation firstFloor(seed,1,{},dw::MissionTheme::Canyon,true);
            const int count=firstFloor.expedition.floorCount;
            for(int slot=0;slot<3;++slot) {
                const int floor=slot==0?0:slot==1?count/2:count-1;
                dw::Simulation run(seed,1,{},dw::MissionTheme::Canyon,true,false,dw::WitnessAccount::None,floor);
                const int room=slot==0?0:slot==1?2:run.arena.roomCount()-2;
                dw::CanyonVisualParameters parameters;parameters.irregularFacets=false;
                const auto base=dw::buildCanyonAppearance(run.arena,parameters);
                const int firstRoom=inventory?0:room,lastRoom=inventory?run.arena.roomCount():room+1;
                for(int scanRoom=firstRoom;scanRoom<lastRoom;++scanRoom) {
                const auto sections=dw::rockFormations::selectSections(base,run.arena.rooms[size_t(scanRoom)].bounds);
                for(size_t candidate=0;candidate<(inventory?sections.size():1);++candidate) {
                const auto &section=sections[candidate];
                float gateDistance=1000;
                for(const auto &passage:run.arena.passages)if(passage.rooms[0]==scanRoom || passage.rooms[1]==scanRoom)
                    for(auto q:section.wall)for(auto gate:passage.gates) {
                        const auto centre=dw::mul(dw::add(gate.min,gate.max),.5f);
                        auto delta=dw::sub(q.bb,q.ab);delta.y=0;auto from=dw::sub(centre,q.ab);from.y=0;
                        const float t=dw::dot(delta,delta)>0?std::clamp(dw::dot(from,delta)/dw::dot(delta,delta),0.f,1.f):0;
                        gateDistance=std::min(gateDistance,dw::planarDistance(centre,dw::add(q.ab,dw::mul(delta,t))));
                    }
                if(!first)out<<",\n";first=false;
                out<<"  {\"id\":\"seed"<<seed<<"-floor"<<floor<<"-room"<<scanRoom<<"\",\"seed\":"<<seed
                   <<",\"floor\":"<<floor<<",\"room\":"<<scanRoom<<",\"profile_band\":"<<run.arena.profile.band
                   <<",\"room_count\":"<<run.arena.roomCount()<<",\"floor_count\":"<<count
                   <<",\"section_key\":"<<section.key<<",\"length\":"<<section.length
                   <<",\"turn\":"<<section.turn<<",\"shape\":"<<std::quoted(section.shape)
                   <<",\"curvature\":"<<std::quoted(section.curvature)<<",\"gate_distance\":"<<gateDistance
                   <<(inventory?",\"attempt\":"+std::to_string(candidate+1):"")
                   <<",\"selection_fallback\":"<<std::quoted(section.fallback)<<"}";
                if(!inventory)std::cout<<"CASE_MANIFEST seed="<<seed<<" floor="<<floor<<" room="<<room<<" shape="<<section.shape<<'\n';
                }
                }
            }
        }
        out<<"\n]\n";
    } catch(const std::exception &e) {std::cerr<<e.what()<<'\n';return 1;}
}
