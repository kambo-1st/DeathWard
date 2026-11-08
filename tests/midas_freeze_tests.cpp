#include "combat/MidasFreeze.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace dw;
namespace {
void check(bool value,const std::string &message){if(!value)throw std::runtime_error(message);}
std::vector<std::string> split(const std::string &line) {
    std::istringstream stream(line);std::string value;std::vector<std::string> fields;
    while(std::getline(stream,value,','))fields.push_back(value);
    return fields;
}
}
int main() {
    try {
        std::ifstream input(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/midas-freeze/native-midas.csv");
        check(bool(input),"independent native Midas trace exists");std::string line;std::getline(input,line);
        ControlFreezeState state;int rows=0,cases=0;
        while(std::getline(input,line)) {
            const auto f=split(line);check(f.size()==12,"Midas trace schema");
            if(f[2]=="initial") {
                state={uint32_t(std::stoul(f[6])),std::stoi(f[7]),std::stoi(f[8]),std::stoi(f[9]),std::stoi(f[10])};
                ++cases;++rows;continue;
            }
            const int type=std::stoi(f[4]);const bool boss=std::stoi(f[5])!=0;const int amount=std::stoi(f[3]);
            bool accepted=false;
            if(f[2]=="tick")sourceStepControlFreeze(state);
            else if(f[2]=="midas")accepted=sourceApplyMidas(state,amount,type,boss);
            else if(f[2]=="golden")accepted=sourceGoldenHeartMidas(state,amount,type,boss);
            else if(f[2]=="ordinary")accepted=sourceApplyOrdinaryFreeze(state,amount,boss);
            else throw std::runtime_error("unknown Midas trace operation");
            const std::array<uint32_t,5> actual={state.flags,uint32_t(state.freeze),uint32_t(state.midas),uint32_t(state.cooldown),uint32_t(state.variant)};
            const auto context=f[0]+" step "+f[1]+" "+f[2];
            for(size_t i=0;i<actual.size();++i)check(actual[i]==std::stoul(f[6+i]),context+" mismatched field "+std::to_string(i));
            check((accepted&&type!=245)==(std::stoi(f[11])!=0),context+" SetColor intent differs");
            ++rows;
        }
        check(rows==1096&&cases==13,"all independent native Midas states checked");
        std::ifstream coins(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/midas-freeze/native-death-coins.csv");
        check(bool(coins),"independent native death-coin trace exists");std::getline(coins,line);int coinRows=0;
        while(std::getline(coins,line)) {
            const auto f=split(line);check(f.size()==2,"coin trace schema");
            check(sourceMidasDeathCoins(uint32_t(std::stoul(f[0])))==std::stoi(f[1]),"native ordinary-Isaac modulo and +1 selection");++coinRows;
        }
        check(coinRows==11,"all supplied-RNG death-coin cases checked");
        std::cout<<"PASS native Midas: "<<rows<<" control states, "<<cases<<" cases, "<<coinRows<<" RNG cases; actor eligibility/linked propagation/live clock remain open\n";
        return 0;
    }catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
