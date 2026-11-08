#include "combat/PlayerHurt.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace dw;
namespace {
void check(bool value,const char *message){if(!value)throw std::runtime_error(message);}
std::vector<std::vector<std::string>> read(const char *name) {
    std::ifstream f(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/player-hurt/"+name);
    check(bool(f),"independent native trace exists");std::string line;std::getline(f,line);
    std::vector<std::vector<std::string>> rows;
    while(std::getline(f,line)) {
        std::istringstream in(line);std::string field;std::vector<std::string> row;
        while(std::getline(in,field,','))row.push_back(field);
        rows.push_back(std::move(row));
    }
    return rows;
}
}
int main() {
    try {
        const auto counters=read("native-counter.csv"),ticks=read("native-tick.csv");
        for(const auto &r:counters) {
            const int rounded=sourcePlayerRoundedDamage(std::stof(r[0]));
            check(rounded==std::stoi(r[1])&&rounded==std::stoi(r[2]),"native pre-modifier float rounding");
            check(sourcePlayerHurtCounter(rounded)==std::stoi(r[3]),"native damage-derived capped counter");
        }
        for(const auto &r:ticks)check(sourcePlayerHurtTick(std::stoi(r[2]))==std::stoi(r[3]),"native positive-counter decrement");
        check(counters.size()==24&&ticks.size()==193,"entire native matrices compared");
        std::cout<<"PASS player hurt: 24 original-damage/counter cases and 193 tick states; full entry/items/live scheduler unaccepted\n";
    }catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
