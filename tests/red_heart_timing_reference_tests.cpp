#include "combat/RedHeartTiming.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace dw;
void check(bool value,const char *why){if(!value)throw std::runtime_error(why);}
std::vector<std::vector<std::string>> rows(const char *name) {
    std::ifstream file(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/d09a-heart-timing/"+name);
    check(bool(file),"native fixture exists");std::string line;std::getline(file,line);
    std::vector<std::vector<std::string>> result;
    while(std::getline(file,line)) {
        std::istringstream stream(line);std::vector<std::string> row;std::string field;
        while(std::getline(stream,field,','))row.push_back(field);
        result.push_back(std::move(row));
    }
    return result;
}
int main(){try{
    int gates=0,states=0,collect=0;RedHeartTiming timer;
    for(const auto &r:rows("native-appearance-gates.csv")) {
        const bool appearance=r[0]=="Appear"||r[0]=="AppearFast"||r[0]=="Reappear";
        check(sourcePickupAppearanceGate(appearance,std::stoi(r[1]),std::stoi(r[2]),std::stoi(r[3]))==bool(std::stoi(r[4])),"native collision gate");++gates;
    }
    for(const auto &r:rows("native-appearance-timelines.csv")) {
        if(std::stoi(r[5])==0)timer.appear(std::stof(r[4]));else timer.tick();
        check(timer.collision==bool(std::stoi(r[9])),"native appearance collision timeline");
        const bool idle=std::stoi(r[11])>0;
        check((timer.phase==RedHeartTiming::Phase::Idle)==idle,"native appearance completion");
        if(!idle)check(std::abs(timer.frame-std::stof(r[6]))<.00001f,"native fractional appearance frame");
        ++states;
    }
    for(const auto &r:rows("native-collection-timelines.csv")) {
        if(std::stoi(r[2])==0)timer.collect();else timer.tick();
        check((timer.phase==RedHeartTiming::Phase::Gone)==bool(std::stoi(r[5])),"native consumed actor cleanup gate");
        if(timer.phase!=RedHeartTiming::Phase::Gone)check(timer.frame==std::stof(r[3]),"native collection frame");
        check(!timer.collectible(),"collection never reopens pickup");++collect;
    }
    check(gates==40&&states==2115&&collect==48,"all native cases consumed");
    std::cout<<"PASS "<<gates<<" native gates, "<<states<<" appearance states, "<<collect<<" collection states\n";
}catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
