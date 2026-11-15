#include "combat/SourceRoomRewards.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace dw;
namespace {
void check(bool value,const std::string &why){if(!value)throw std::runtime_error(why);}
auto read(const char *name) {
    std::ifstream f(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/room-awards/"+name);
    check(bool(f),"independent native trace exists");std::string line;std::getline(f,line);std::vector<std::vector<std::string>> rows;
    while(std::getline(f,line)){std::istringstream in(line);std::string value;std::vector<std::string> row;while(std::getline(in,value,','))row.push_back(value);rows.push_back(std::move(row));}
    return rows;
}
}
int main(){try{
    auto awards=read("native-awards.csv"),pickups=read("native-pickups.csv");
    for(const auto &r:awards) {
        SourceAwardRng rng{uint32_t(std::stoul(r[0]))};
        check(sourceOrdinaryRoomAward(rng,std::stof(r[1]),std::stoi(r[2]))==std::stoi(r[3]),"native room reward variant for seed "+r[0]+" luck "+r[1]);
        check(rng.state==uint32_t(std::stoul(r[4])),"exact native selector RNG endpoint for seed "+r[0]);
    }
    size_t hearts=0,coins=0;
    for(const auto &r:pickups) {
        if(std::stoi(r[1])!=10&&std::stoi(r[1])!=20)continue;
        if(std::stoi(r[1])==10)++hearts;else ++coins;
        const auto choice=sourceOrdinaryPickup(uint32_t(std::stoul(r[0])),std::stoi(r[1]),std::stoi(r[2])?SourcePickupGates::representedEnabled():SourcePickupGates{});
        check(choice.resolved&&choice.variant==std::stoi(r[3])&&choice.subtype==std::stoi(r[4]),"native pickup resolution for seed "+r[0]+" variant "+r[1]+" gates "+r[2]+" expected "+r[4]+" got "+std::to_string(choice.subtype));
    }
    check(awards.size()==2196&&hearts==1036&&coins==1036,"complete independent native matrices compared");
    check(!sourceOrdinaryPickup(42,300).resolved,"unsupported subtype families remain explicit, not substituted");
    std::cout<<"PASS 2196 native award choices/RNG endpoints and 1036 heart and 1036 coin subtype choices; full native spawning/modifiers remain open\n";
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
