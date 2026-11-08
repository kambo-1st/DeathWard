#pragma once
#include "combat/Simulation.hpp"
#include <fstream>
#include <regex>
#include <set>
#include <sstream>

namespace dw::damage_review {
struct Body { MonsterId id; const char *name; float sourceHp; };
inline const std::array<Body,9> Bodies{{
    {{10,0,0},"Frowning Gaper",10},{{10,1,0},"Gaper",10},{{11,0,0},"Gusher",10},
    {{12,0,0},"Horf",10},{{13,0,0},"Fly",3},{{14,0,0},"Pooter",8},
    {{18,0,0},"Attack Fly",5},{{85,0,0},"Spider",6.5f},{{29,0,0},"Hopper",10}
}};
inline void require(bool condition,const char *why){if(!condition)throw std::runtime_error(why);}
inline bool selected(MonsterId id){return std::any_of(Bodies.begin(),Bodies.end(),[&](const auto &b){return b.id==id;});}
inline bool healthMember(MonsterId id){return selected(id)||id==monsterId(11,1);}
// Review only. No production files are edited and the destination must be new.
// Source base/growth and the audited regular-health multiplier are preserved.
inline std::shared_ptr<const MechanicsLibrary> makeSourcePack(const MechanicsLibrary &original,
                                                            const std::filesystem::path &destination) {
    require(!std::filesystem::exists(destination),"review mechanics destination must be new");
    std::filesystem::create_directories(destination);
    const std::regex body(R"re(^(\s*monster\s+(\S+)\s+"[^"]*"\s+\S+\s+\S+\s+\S+\s+)(\S+)(.*)$)re");
    const std::regex stage(R"re(^(\s*stage_health\s+(\S+)\s+)(\S+)\s+(\S+)\s+(\S+)(.*)$)re");
    const std::regex morph(R"re(^(\s*lethal_morph\s+(\S+)\s+\S+\s+\S+\s+)(\S+)(.*)$)re");
    std::set<MonsterId> bodies,stages,morphs;
    for(const auto &file:std::filesystem::directory_iterator(original.directory())) {
        if(file.path().extension()!=".mechanics")continue;
        std::ifstream in(file.path());std::ostringstream out;std::string line;bool changed=false;
        while(std::getline(in,line)) {
            std::smatch m;
            if(std::regex_match(line,m,body)&&healthMember(parseMonsterId(m[2].str()))) {
                const auto id=parseMonsterId(m[2].str());const auto *hp=original.stageHealth(id);
                require(hp&&original.regularHealthMember(id)&&!original.monsterBoss(id),"scoped regular body needs audited source health");
                std::ostringstream row;row<<m[1].str()<<(hp->base+hp->perStage)<<m[4].str();line=row.str();bodies.insert(id);changed=true;
            } else if(std::regex_match(line,m,stage)&&healthMember(parseMonsterId(m[2].str()))) {
                const auto id=parseMonsterId(m[2].str());
                line=m[1].str()+m[3].str()+" "+m[4].str()+" 1"+m[6].str();stages.insert(id);changed=true;
            } else if(std::regex_match(line,m,morph)) {
                const auto id=parseMonsterId(m[2].str());
                if(id==monsterId(10)||id==monsterId(10,1)) {
                    const auto *hp=original.stageHealth(id);require(hp&&hp->scale>0,"morph unit conversion requires source health scale");
                    std::ostringstream row;row<<m[1].str()<<(std::stof(m[3].str())/hp->scale)<<m[4].str();line=row.str();morphs.insert(id);changed=true;
                }
            }
            out<<line<<'\n';
        }
        if(changed){std::ofstream target(destination/file.path().filename());target<<"# REVIEW ONLY: source units for selected bodies and necessary morph HP dependencies.\n"<<out.str();require(bool(target),"write review mechanics");}
        else std::filesystem::copy_file(file.path(),destination/file.path().filename());
    }
    require(bodies.size()==10&&stages.size()==10&&morphs.size()==2,"review scope must match nine bodies, Pacer HP dependency and two overkill conversions");
    auto result=MechanicsLibrary::load(destination);
    require(result->regularHealthMultiplier()==original.regularHealthMultiplier(),"regular-health multiplier must remain unchanged");
    return result;
}
inline int bodyHits(float hp,float damage){return int(std::ceil(hp/damage));}
}
