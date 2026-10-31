#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
// Same natural boss and spectator placement as --scene resident-906.0.0.
int main() {
    for(const auto [seed,floor]:std::array<std::pair<uint64_t,int>,6>{{{10,2},{58,3},{953,2},{1254,3},{19,2},{57,2}}}) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        s.jumpDebug(s.finalRoom());s.godMode=true;s.debugScenario=true;
        const auto start=s.boss()->position;
        for(int n=0;n<24;++n) {
            auto point=add(start,rotateY({0,0,7},float(n)*Pi/12));point.y=.85f;
            if(s.arena.roomAt(point)!=s.room||s.arena.blocked(point,.48f)||!s.arena.sight(point,start))continue;
            if(std::any_of(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return distance(point,e.position)<3;}))continue;
            s.player.position=point;break;
        }
        int prior=-1;bool fire=false;
        for(int frame=1;frame<=6000;++frame) {
            s.step({});const auto &h=*s.rooms.back().hornfel;
            if(h.charges&&prior!=int(h.state)) {
                prior=int(h.state);
                std::cout<<"PHASE seed="<<seed<<" floor="<<floor<<" frame="<<frame<<" state="<<prior<<" charges="<<h.charges
                    <<" route="<<h.cart.route<<" passes="<<h.chargePasses<<" repeats="<<h.repeatsChosen<<" bombs="<<h.chargeBombs
                    <<" shots="<<h.recoveryShots<<" waves="<<s.fireWaves.size()<<'\n';
            }
            if(!fire&&!s.fireWaves.empty()) {
                fire=true;std::cout<<"FIRST_FIRE seed="<<seed<<" floor="<<floor<<" frame="<<frame<<'\n';
            }
            if(h.recoveryShots&&h.state==HornfelState::Outside)break;
        }
    }
}
