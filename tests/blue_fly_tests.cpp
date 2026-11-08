#include "combat/BlueFly.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace dw;
namespace {
void check(bool value,const std::string &why){if(!value)throw std::runtime_error(why);}
bool close(float a,float b){return std::abs(a-b)<.0002f;}
std::vector<std::vector<std::string>> read(const std::string &folder,const std::string &name) {
    std::ifstream file(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/"+folder+'/'+name);
    check(bool(file),"independent native trace exists: "+name);std::string line;std::getline(file,line);
    std::vector<std::vector<std::string>> rows;
    while(std::getline(file,line)) {
        std::istringstream stream(line);std::string field;std::vector<std::string> row;
        while(std::getline(stream,field,','))row.push_back(field);rows.push_back(std::move(row));
    }
    return rows;
}
}
int main() {
    try {
        auto motion=read("blue-fly","native-motion.csv");Vector3 position{},velocity{};std::string name;
        for(const auto &r:motion) {
            check(r.size()==12,"motion schema");if(name!=r[0]){name=r[0];position={};velocity={};}
            check(close(position.x,std::stof(r[2]))&&close(position.z,std::stof(r[3])),"native pre-motion position "+name);
            velocity=sourceBlueFlyMotion(velocity,sub(Vector3{std::stof(r[6]),0,std::stof(r[7])},position));
            position=add(position,velocity);
            check(close(position.x,std::stof(r[8]))&&close(position.z,std::stof(r[9]))&&close(velocity.x,std::stof(r[10]))&&close(velocity.z,std::stof(r[11])),"native steering/physics endpoint "+name+' '+r[1]);
        }
        check(motion.size()==318,"all native motion states checked");
        auto angles=read("blue-fly","native-orbit-angle.csv");
        for(const auto &r:angles)check(close(sourceBlueFlyOrbitAngleInput(std::stof(r[0]),uint32_t(std::stoul(r[1])),std::stoi(r[2])),std::stof(r[3])),"native pre-trigonometry orbit angle");
        auto scores=read("blue-fly","native-target-score.csv");
        for(const auto &r:scores)check(close(sourceBlueFlyTargetScore(std::stof(r[0]),std::stof(r[1]),std::stof(r[2])),std::stof(r[3])),"native ordinary target score");
        auto damage=read("blue-fly","native-damage.csv");
        for(const auto &r:damage)check(close(sourceBlueFlyDamage(std::stof(r[0])),std::stof(r[1])),"native initialized collision damage");
        auto kills=read("blue-fly","native-instakill.csv");
        for(const auto &r:kills)check(sourceBlueFlyInstakill(monsterId(std::stoi(r[0]),std::stoi(r[1])))==(r[2]=="1"),"native direct-kill target branch");
        auto refill=read("rotten-heart-flies","native-refill.csv");
        for(const auto &r:refill)check(sourceRottenFlyDeficit(std::stoi(r[0]),std::stoi(r[1]))==std::stoi(r[2]),"native refill deficit preserves owned excess");
        check(angles.size()==36&&scores.size()==64&&damage.size()==5&&refill.size()==104&&kills.size()==22,"complete independent native kernel matrices");
        std::cout<<"PASS blue fly: 318 native motion, 36 angle, 64 score, 5 damage and 104 refill cases; global RNG, imported trig, collision/ordering/items/live acceptance remain open\n";
        return 0;
    }catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
