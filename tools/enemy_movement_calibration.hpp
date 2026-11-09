#pragma once
#include "combat/Simulation.hpp"
#include <fstream>
#include <iomanip>
#include <regex>
#include <set>
#include <sstream>

namespace dw::movement_review {
// Pinned 1.7.9b original player instructions: 360 held-input invocations,
// final 60 velocities identical. See enemy-movement-blocker/native-player-probe.json.
// Dispatch evidence: update-phases report. This anchors relative motion to the
// accepted responsive player; it does not establish native room/body geometry.
inline constexpr double NativePlayerSteadyStep = 4.414238452911377;
inline constexpr double NativePlayerHz = 60, NativeNpcHz = 30;
inline constexpr double WorldScale = Player::AcceptedWalkingPace / (NativePlayerSteadyStep * NativePlayerHz);
inline constexpr double PreviousScale = .1;
inline constexpr double ConversionRatio = WorldScale / PreviousScale;
inline bool selected(MonsterId id) {
    return id==monsterId(10)||id==monsterId(10,1)||id==monsterId(11)||
           id==monsterId(11,1)||id==monsterId(14)||id==monsterId(85);
}
inline void require(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
// Movement-only disposable candidate. Production, HP, attacks and source forces
// stay untouched. Change the coordinate conversion inside the recurrence, not
// its resulting velocity (which is fed back into native momentum next tick).
inline std::shared_ptr<const MechanicsLibrary> makePack(const MechanicsLibrary &original,
                                                       const std::filesystem::path &destination,double worldScale=WorldScale) {
    require(std::isfinite(worldScale)&&worldScale>0&&worldScale<=1,"valid explicit movement conversion");
    require(!std::filesystem::exists(destination),"movement destination must be new");
    std::filesystem::create_directories(destination);
    const std::regex profile(R"(^(\s*(gaper|headless)\s+(\S+)\s+\S+\s+)(\S+)(.*)$)");
    const std::regex simple(R"(^(\s*(buzz_fly|spider)\s+(\S+)\s+)(\S+)(.*)$)");
    std::set<MonsterId> patched;
    for(const auto &file:std::filesystem::directory_iterator(original.directory())) {
        if(file.path().extension()!=".mechanics")continue;
        std::ifstream in(file.path());std::ostringstream out;std::string line;bool changed=false;
        while(std::getline(in,line)) {
            std::smatch m;
            if((std::regex_match(line,m,profile)||std::regex_match(line,m,simple))&&selected(parseMonsterId(m[3].str()))) {
                const auto id=parseMonsterId(m[3].str());
                require(std::abs(std::stod(m[4].str())-PreviousScale)<1e-8,"unexpected previous movement conversion");
                std::ostringstream row;row<<m[1].str()<<std::setprecision(12)<<worldScale<<m[5].str();
                line=row.str();changed=true;patched.insert(id);
            }
            out<<line<<'\n';
        }
        if(changed){std::ofstream target(destination/file.path().filename());target<<out.str();require(bool(target),"write movement candidate");}
        else std::filesystem::copy_file(file.path(),destination/file.path().filename());
    }
    require(patched.size()==6,"movement scope: two Gapers, two headless dependencies, Pooter and Spider");
    return MechanicsLibrary::load(destination);
}
}
