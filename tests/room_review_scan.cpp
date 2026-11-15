#include "combat/Simulation.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include "world/SourceRoomSelection.hpp"
#include <iostream>
#include <set>
using namespace dw;

// Candidate filtering is deliberately permissive. Every emitted witness comes
// from the real Simulation; no template, pickup outcome or room role is forced.
bool candidate(uint64_t seed,const std::set<int> &wanted) {
    ExpeditionPlan plan(seed,false,WitnessAccount::None,ExpeditionPacing::Compact);
    std::vector<float> initial;for(const auto &r:BasementHeartLayouts)initial.push_back(r.weight);
    for(int room=1;room<7;++room) {
        Random rng(plan.floorSeed(0)^0x524f4f4d48454152ULL^(uint64_t(room+1)*0x9e3779b97f4a7c15ULL));
        uint32_t state=uint32_t(rng.next());if(!state)state=1;
        for(int doors=1;doors<16;++doors) {
            auto weights=initial;
            const int selected=sourceRoomSelect(BasementHeartLayouts,weights,sourceBasementFirstFloorQuery(doors),state);
            if(selected>=0&&wanted.contains(BasementHeartLayouts[size_t(selected)].variant))return true;
        }
    }
    return false;
}
int main(int argc,char **argv) {
    if(argc>1&&std::string(argv[1])=="--clear") {
        for(uint64_t seed=0;seed<2000;++seed) {
            Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,
                ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true);
            for(int i=1;i<r.finalRoom();++i)if(r.arena.rooms[size_t(i)].sourceCombatTemplate==47&&r.arena.rooms[size_t(i)].depth==1) {
                r.redHeartClearRewards=true;r.jumpDebug(i);r.clearRoomDebug();
                if(r.heartPickups.size()==1&&r.heartPickups.front().sourceSubtype==1) {
                    std::cout<<"clear_reward_seed="<<seed<<" room="<<i+1<<'\n';return 0;
                }
            }
        }
        return 1;
    }
    if(argc>1&&std::string(argv[1])=="--grid") {
        std::cout<<"variant,scale,minimum,maximum,seed,room\n";
        for(int variant:{4,91,108})for(float size:{.75f,1.1f,1.5f})for(auto range:{std::pair{5,5},std::pair{7,9},std::pair{10,10}}) {
            bool found=false;
            for(uint64_t seed:{195,517,2521,22,443,586,1152,268,680,853,2046,1576,3817,243}) {
                Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),size,range.first,range.second,.26f,true,1,true,true);
                for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==variant) {
                    const auto &room=r.arena.rooms[size_t(i)];
                    if(variant==91&&(room.heartSpawns.size()!=2||room.heartSpawns[0].subtype+room.heartSpawns[1].subtype!=3))continue;
                    std::cout<<variant<<','<<size<<','<<range.first<<','<<range.second<<','<<seed<<','<<i+1<<std::endl;found=true;break;
                }
                if(found)break;
            }
            if(!found){std::cerr<<"MISSING GRID "<<variant<<' '<<size<<' '<<range.first<<'\n';return 1;}
        }
        return 0;
    }
    const int limit=argc>1?std::stoi(argv[1]):10000;
    std::cout<<"seed,scale,minimum,maximum,variant,room,subtypes\n";
    for(auto dims:{std::array<float,3>{.75f,5,5},{1.1f,7,9},{1.5f,10,10}}) {
        std::set<int> wanted{4,30,31,32,91,108,109,214,547,548,550};
        std::map<int,int> counts;
        for(uint64_t seed=0;seed<uint64_t(limit)&&!wanted.empty();++seed) {
            if(!candidate(seed,wanted))continue;
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,
                ExpeditionPacing::Compact,defaultMechanics(),dims[0],int(dims[1]),int(dims[2]),.26f,true,1,true,true);
            for(int index=0;index<run.arena.roomCount();++index) {
                const auto &r=run.arena.rooms[size_t(index)];const int v=r.sourceObstacleTemplate;
                if(!wanted.contains(v))continue;
                std::string subtypes;
                const auto append=[&](const auto &slots){for(const auto &s:slots){if(!subtypes.empty())subtypes+='|';subtypes+=std::to_string(s.subtype);}};
                append(r.heartSpawns);append(r.coinSpawns);append(r.keySpawns);append(r.bombSpawns);
                if(v==91&&subtypes!="1|2"&&subtypes!="2|1")continue;
                if(v==214&&subtypes!="1|1")continue;
                if(v==32&&subtypes!="1|1|1")continue;
                if(v==30&&std::any_of(r.coinSpawns.begin(),r.coinSpawns.end(),[](const auto &s){return sourceOrdinaryCoinValue(s.subtype)==0;}))continue;
                std::cout<<seed<<','<<dims[0]<<','<<dims[1]<<','<<dims[2]<<','<<v<<','<<index+1<<','<<subtypes<<std::endl;
                if(++counts[v]>=3)wanted.erase(v);
            }
        }
        for(int v:wanted)std::cerr<<"INCOMPLETE scale="<<dims[0]<<" variant="<<v<<" witnesses="<<counts[v]<<'\n';
    }
}
