#include "core/BalancePreset.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
std::string replaceOne(std::string s,const std::string &from,const std::string &to) {
    auto at=s.find(from);check(at!=s.npos,"mutation exists");s.replace(at,from.size(),to);return s;
}
int main() {
    const auto dir=std::filesystem::temp_directory_path()/
        ("deathward-preset-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        std::filesystem::create_directories(dir);const auto file=dir/"roundtrip.json";
        for(float speed:{.1f,.8f,1.f,1.234567f,2.f}) {
            BalancePreset p{speed,"fixture-content"};p.save(file);
            const auto loaded=BalancePreset::load(file,"fixture-content");
            check(loaded.playerSpeed==speed&&loaded.revision()==p.revision(),"export/import preserves effective value and revision");
        }
        BalancePreset custom{.8f,"fixture-content"};custom.save(file);
        const auto valid=custom.json();
        std::vector<std::string> invalid{
            valid+"garbage", valid.substr(0,valid.size()-3),
            replaceOne(valid,"\"schema_version\": 1","\"schema_version\": 2"),
            replaceOne(valid,"\"schema_version\": 1","\"schema_version\": 1, \"schema_version\": 1"),
            replaceOne(valid,"d01-speed-v1","future-contract"),
            replaceOne(valid,"fixture-content","different-content"),
            replaceOne(valid,"Repentance 1.7.9b","Repentance 1.7.9a"),
            replaceOne(valid,"\"walking_pace_at_speed_one\": 4.8","\"walking_pace_at_speed_one\": 30"),
            replaceOne(valid,"\"universal_dodge\": true","\"universal_dodge\": false"),
            replaceOne(valid,"\"resolved\": {\"player_speed\": 0.8}","\"resolved\": {\"player_speed\": 0.9}"),
            replaceOne(valid,"\"resolved\": {\"player_speed\": 0.8}","\"resolved\": {\"player_speed\": -1}"),
            replaceOne(valid,"\"resolved\": {\"player_speed\": 0.8}","\"resolved\": {\"player_speed\": 99}"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": NaN"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 1e999"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 00.8"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": .8"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": \"0.8\""),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 0.8, \"damage\": 3.5"),
            std::string(65537,' ')
        };
        for(const auto &bad:invalid) {
            const auto badFile=dir/"invalid.json";{std::ofstream out(badFile);out<<bad;}
            bool rejected=false;try{(void)BalancePreset::load(badFile,"fixture-content");}catch(const std::exception&){rejected=true;}
            check(rejected,"invalid/unsupported configuration rejected");
            check(BalancePreset::load(file,"fixture-content").playerSpeed==.8f,"failed load preserves prior exported file");
        }
        auto nan=custom;nan.playerSpeed=std::numeric_limits<float>::quiet_NaN();
        bool rejected=false;try{nan.save(file);}catch(const std::exception&){rejected=true;}
        check(rejected&&BalancePreset::load(file,"fixture-content").playerSpeed==.8f,"invalid export cannot replace existing preset");
        const auto blocked=dir/"directory.json";std::filesystem::create_directory(blocked);
        rejected=false;try{custom.save(blocked);}catch(const std::exception&){rejected=true;}
        check(rejected&&std::filesystem::is_directory(blocked),"failed atomic replacement preserves destination");
        for(const auto &entry:std::filesystem::directory_iterator(dir))
            check(entry.path().filename().string().find(".tmp-")==std::string::npos,"failed export removes its temporary file");
        std::filesystem::remove_all(dir);
        std::cout<<"PASS preset round-trip, 19 rejection cases, invalid-export protection and atomic replacement failure\n";
        return 0;
    } catch(const std::exception &e){std::cerr<<e.what()<<'\n';std::filesystem::remove_all(dir);return 1;}
}
