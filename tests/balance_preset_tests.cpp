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
        for(float route:{.25f,.99f,1.f,1.01f,2.f})for(float scale:{.75f,1.f,1.25f,1.5f})for(auto range:{std::pair{0,0},std::pair{5,5},std::pair{7,9},std::pair{10,10}}) {
            BalancePreset p{.8f,"fixture-content",scale,range.first,range.second,route};p.save(file);
            check(BalancePreset::load(file,"fixture-content").revision()==p.revision(),"size and range round-trip");
        }
        for(float zoom:{67.f,125.f,159.25f,160.f,285.f}) {
            BalancePreset p{.8f,"fixture-content",1.25f,7,9,.65f,zoom};p.save(file);
            const auto loaded=BalancePreset::load(file,"fixture-content");
            check(loaded.defaultZoomPercent==zoom&&loaded.revision()==p.revision(),"default zoom round-trips with independent Speed/map settings");
        }
        const auto legacy=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d01-live-tuning/speed-080.json","2ccd5b1c274a302e");
        check(legacy.playerSpeed==.8f&&legacy.roomSizeScale==1&&legacy.roomMinHalfTiles==0&&legacy.defaultZoomPercent==160,"D01 migration preserves speed and selects automatic room sizes");
        const auto v2=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d02-room-scale/custom-size-range.json","2ccd5b1c274a302e");
        check(v2.roomSizeScale==1.25f&&v2.roomMinHalfTiles==7&&v2.roomMaxHalfTiles==9&&v2.routeLengthScale==1&&v2.defaultZoomPercent==160,
              "schema 2 migration preserves map sizing and defaults route length");
        const auto v3=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d02-room-scale/custom-map.json","2ccd5b1c274a302e");
        check(v3.routeLengthScale==.65f&&v3.defaultZoomPercent==160,"schema 3 migration retains route length and defaults zoom to 160 percent");
        BalancePreset zoomPreset{1,"fixture-content",1,0,0,1,125};
        BalancePreset routePreset{1,"fixture-content",1,0,0,.65f};
        BalancePreset custom{.8f,"fixture-content"};custom.save(file);
        const auto valid=custom.json();
        std::vector<std::string> invalid{
            valid+"garbage", valid.substr(0,valid.size()-3),
            replaceOne(valid,"\"schema_version\": 4","\"schema_version\": 5"),
            replaceOne(valid,"\"schema_version\": 4","\"schema_version\": 4, \"schema_version\": 4"),
            replaceOne(valid,"d02-view-v4","future-contract"),
            replaceOne(valid,"fixture-content","different-content"),
            replaceOne(valid,"Repentance 1.7.9b","Repentance 1.7.9a"),
            replaceOne(valid,"\"walking_pace_at_speed_one\": 4.8","\"walking_pace_at_speed_one\": 30"),
            replaceOne(valid,"\"universal_dodge\": true","\"universal_dodge\": false"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 0.9"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": -1"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 99"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": NaN"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 1e999"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 00.8"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": .8"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": \"0.8\""),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 0.8, \"damage\": 3.5"),
            replaceOne(valid,"\"room_size_scale\": 1","\"room_size_scale\": 0"),
            replaceOne(valid,"\"room_min_half_tiles\": 0","\"room_min_half_tiles\": 11"),
            replaceOne(valid,"\"route_length_scale\": 1","\"route_length_scale\": 0"),
            replaceOne(routePreset.json(),"\"route_length_scale\": 0.65","\"route_length_scale\": 2.01"),
            replaceOne(routePreset.json(),"\"route_length_scale\": 0.65","\"route_length_scale\": 0.64"),
            replaceOne(valid,"\"default_zoom_percent\": 160","\"default_zoom_percent\": 125"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": 66.99"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": 285.01"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": 126"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": NaN"),
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
        std::cout<<"PASS preset round-trip, schema migrations and rejection cases, invalid-export protection and atomic replacement failure\n";
        return 0;
    } catch(const std::exception &e){std::cerr<<e.what()<<'\n';std::filesystem::remove_all(dir);return 1;}
}
