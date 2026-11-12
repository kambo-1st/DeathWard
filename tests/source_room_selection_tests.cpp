#include "world/SourceRoomSelection.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
auto read(const char *name,const char *directory="native-room-selection-placement") {
    std::ifstream f(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/"+directory+"/"+name);
    check(bool(f),"native fixture exists");std::string line;std::getline(f,line);std::vector<std::vector<std::string>> rows;
    while(std::getline(f,line)){std::istringstream in(line);std::string v;std::vector<std::string> row;while(std::getline(in,v,','))row.push_back(v);rows.push_back(row);}return rows;
}
int main(){try{
    const auto queries=read("native-queries.csv","native-room-eligibility");
    for(const auto &r:queries) {
        const auto q=sourceBasementFirstFloorQuery(std::stoi(r[1]));
        check(q.type==std::stoi(r[5])&&q.shape==std::stoi(r[6])&&q.minVariant==std::stoul(r[7])&&q.maxVariant==std::stoul(r[8])&&
              q.minDifficulty==std::stoi(r[9])&&q.maxDifficulty==std::stoi(r[10])&&q.doors==std::stoi(r[11])&&q.subtype==std::stoi(r[12]),"native ordinary first-floor caller arguments");
    }
    const auto descriptors=read("native-descriptors.csv","native-room-eligibility");
    for(const auto &r:descriptors) {
        const auto s=sourceRoomDescriptorSeeds(uint32_t(std::stoul(r[0])));
        check(s.decoration==std::stoul(r[1])&&s.spawn==std::stoul(r[2])&&s.award==std::stoul(r[3])&&s.bossDeath==std::stoul(r[4]),"native placement and complete descriptor seed derivation");
    }
    check(queries.size()==1024&&descriptors.size()==64,"complete native caller/descriptor fixtures");
    std::cout<<"PASS "<<queries.size()<<" caller queries and "<<descriptors.size()<<" descriptor seed derivations\n";
    const auto filters=read("native-filters.csv"),selections=read("native-selections.csv");
    for(const auto &r:filters) {
        SourceRoomHeartLayout row{};row.type=std::stoi(r[0]);row.variant=int(std::stoul(r[1]));row.subtype=std::stoi(r[2]);row.difficulty=std::stoi(r[3]);row.shape=std::stoi(r[4]);row.doors=std::stoi(r[5]);
        SourceRoomQuery q{std::stoi(r[6]),std::stoi(r[7]),uint32_t(std::stoul(r[8])),uint32_t(std::stoul(r[9])),std::stoi(r[10]),std::stoi(r[11]),std::stoi(r[12]),std::stoi(r[13])};
        check(sourceRoomEligible(row,q)==bool(std::stoi(r[14])),"native numeric room filter");
    }
    std::vector<float> weights;int previous=-1;
    for(const auto &r:selections) {
        const int doors=std::stoi(r[0]);if(doors!=previous){weights.clear();for(const auto &row:BasementHeartLayouts)weights.push_back(row.weight);previous=doors;}
        SourceRoomQuery q;q.doors=doors;
        const int selected=sourceRoomSelect(BasementHeartLayouts,weights,q,uint32_t(std::stoul(r[2])),std::stoi(r[3]));
        check((selected<0?-1:BasementHeartLayouts[size_t(selected)].variant)==std::stoi(r[4]),"native weighted room selection");
        if(selected>=0)check(weights[size_t(selected)]==std::stof(r[5]),"native persistent reduced weight");
    }
    const auto spawns=read("native-spawns.csv");
    for(const auto &r:spawns) {
        const auto &slot=BasementHeartSlots.at(size_t(std::stoi(r[0])));uint32_t seed=uint32_t(std::stoul(r[1]));
        const float unit=sourceRoomSpawnRandom(seed);
        check(seed==uint32_t(std::stoul(r[3])),"native spawn slot RNG endpoint");
        check(sourceRoomSpawnChoice(BasementHeartChoices,slot.firstChoice,slot.choiceCount,unit)-slot.firstChoice==std::stoi(r[2]),"native mixed spawn-stack choice");
        check((slot.y+1)*15+slot.x+1==std::stoi(r[4]),"native source cell grid index");
    }
    check(filters.size()==560&&selections.size()==1024&&spawns.size()==1472,"complete native fixture coverage");
    std::cout<<"PASS "<<filters.size()<<" native filters, "<<selections.size()<<" selections/reduced weights, "<<spawns.size()<<" spawn choices/seeds/grid indices\n";
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
