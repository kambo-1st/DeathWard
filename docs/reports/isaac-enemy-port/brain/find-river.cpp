// Offline witness discovery; compile against the current deathward_core.
#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int main(int argc,char **argv) {
    std::cout<<std::unitbuf;
    const int first=argc>1?std::stoi(argv[1]):64,last=argc>2?std::stoi(argv[2]):320;
    for(int seed=first;seed<last;++seed) {
        if(seed%4==0)std::cout<<"SEARCH seed="<<seed<<'\n';
        ExpeditionPlan plan(uint64_t(seed),false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            if(plan.profileOnFloor(floor).band<2)continue;
            Simulation s(uint64_t(seed),1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            if(!s.arena.canyon||s.arena.canyon->riverKind!=CanyonRiverKind::Interior)continue;
            for(int room=1;room<s.finalRoom();++room) {
                if(!std::any_of(s.roomEnemies(room).begin(),s.roomEnemies(room).end(),[](const auto &e){return e.monster==monsterId(32);}))continue;
                if(!std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;}))continue;
                std::cout<<"RIVER_BRAIN seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<'\n';return 0;
            }
        }
    }
    std::cout<<"NO_WITNESS range="<<first<<":"<<last<<'\n';return 1;
}
