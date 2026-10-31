// Offline discovery, against the current real seeded generator and core library.
#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
using namespace dw;
int main(int argc,char **argv) {
    std::cout<<std::unitbuf;std::set<std::pair<int,int>> seen;
    const int first=argc>1?std::stoi(argv[1]):0,last=argc>2?std::stoi(argv[2]):64;
    for(int seed=first;seed<last;++seed) {
        std::cerr<<"SEARCH seed="<<seed<<'\n';ExpeditionPlan plan(uint64_t(seed),false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            const int band=plan.profileOnFloor(floor).band;if(band<2)continue;
            Simulation s(uint64_t(seed),1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room)) {
                if(e.monster.type!=38||e.monster.subtype!=0)continue;
                const bool river=s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&
                    std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;});
                if(seen.contains({e.monster.variant,band})&&!river)continue;
                std::cout<<"{\"seed\":"<<seed<<",\"floor\":"<<floor<<",\"room\":"<<room<<",\"band\":"<<band
                    <<",\"variant\":"<<e.monster.variant<<",\"flooded\":"<<(s.arena.profile.variant==FloorVariant::Flooded?"true":"false")
                    <<",\"river\":"<<(river?"true":"false")<<"}\n";
                seen.insert({e.monster.variant,band});if(seen.size()==4)return 0;
            }
        }
    }
    std::cerr<<"FOUND combinations="<<seen.size()<<" of4\n";return seen.size()==4?0:1;
}
