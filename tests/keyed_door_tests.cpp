#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation generated(uint64_t seed,float scale=1.1f,float routes=.26f) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,
        ExpeditionPacing::Compact,defaultMechanics(),scale,7,9,routes,true,1,true);
}
std::pair<int,int> lock(const Simulation &run) {
    for(size_t i=0;i<run.arena.passages.size();++i) {
        const auto &p=run.arena.passages[i];if(!p.locked)continue;
        return {int(i),run.arena.rooms[size_t(p.rooms[0])].kind==RoomKind::Power?1:0};
    }
    throw std::runtime_error("generated lock missing");
}
void approach(Simulation &run,int i,int side) {
    run.jumpDebug(run.arena.passages[size_t(i)].rooms[size_t(side)]);run.clearRoomDebug();
    run.player.position=run.arena.doorApproach(i,side);run.player.position.y=.85f;
    run.checkpointNeeded=false;
}
void spending() {
    for(int cost=0;cost<=5;++cost)for(int keys:{-1,0,1,2,3,5,98,99}) {
        auto run=generated(69);const auto [i,s]=lock(run);approach(run,i,s);run.keys=keys;run.keyedDoorCost=cost;
        const bool expected=keys>=cost;
        check(run.useDoor(i,s)==expected,"successful unlock requires exact available cost");
        check(run.keys==keys-(expected?cost:0)&&run.arena.passages[size_t(i)].locked==!expected,"atomic inventory/lock transition");
        if(expected) {
            check(run.checkpointNeeded,"successful unlock requests checkpoint");
            run.keyedDoorCost=5;check(run.useDoor(i,s)&&run.keys==keys-cost,"repeat cannot charge again after live cost increase");
            const int other=1-s;approach(run,i,other);
            check(run.useDoor(i,other)&&run.keys==keys-cost,"other side and revisit do not charge again");
        }
    }
}
void rejected() {
    for(int mode=0;mode<13;++mode) {
        auto run=generated(69);const auto [i,s]=lock(run);approach(run,i,s);run.keys=3;
        int index=i,side=s;
        switch(mode) {
        case 0:run.dead=true;break;case 1:run.finished=true;break;case 2:run.shopOpen=true;break;
        case 3:run.rewardOpen=true;break;case 4:run.roomClear=false;break;
        case 5:run.arena.passages[size_t(i)].sealed[1-s]=true;run.arena.rebuildWalls();break;
        case 6:side=1-s;break;case 7:index=-1;break;case 8:side=2;break;
        case 9:run.player.position=add(run.player.position,{20,0,0});break;
        case 10:run.keyedDoorCost=-1;break;case 11:run.keyedDoorCost=6;break;
        case 12:{auto at=run.arena.doorApproach(i,1-s);run.arena.obstacles.push_back({add(at,{-1,-2,-1}),add(at,{1,3,1})});run.arena.rebuildWalls();break;}
        }
        const auto walls=run.arena.walls.size();
        check(!run.useDoor(index,side)&&run.keys==3&&run.arena.passages[size_t(i)].locked&&!run.checkpointNeeded&&run.arena.walls.size()==walls,
            "failed request leaves inventory, lock, collision and checkpoint unchanged");
    }
}
void coverage() {
    for(uint64_t seed:{1ULL,69ULL,129ULL})for(float scale:{.75f,1.1f,1.5f})for(float routes:{.25f,1.f,2.f}) {
        auto run=generated(seed,scale,routes);
        for(size_t i=0;i<run.arena.passages.size();++i)if(run.arena.passages[i].locked) {
            const int side=run.arena.rooms[size_t(run.arena.passages[i].rooms[0])].kind==RoomKind::Power?1:0;
            approach(run,int(i),side);run.keys=1;
            check(run.useDoor(int(i),side)&&run.keys==0,"generated canyon lock remains traversable across size/route controls");
        }
    }
}
void queuedCost() {
    for(int cost:{0,2}) {
        auto run=generated(69);const auto [i,s]=lock(run);approach(run,i,s);run.keys=1;
        const auto at=run.player.position,center=run.arena.rooms[size_t(run.room)].center;
        run.player.position=add(at,mul(unit(sub(Vector3{center.x,at.y,center.z},at)),5));
        check(run.arena.clear(run.player.position,at,.48f),"queued approach fixture is physically clear");
        run.arena.keys.clear();run.requestDoor(i,s);
        check(run.arena.passages[size_t(i)].locked&&run.keys==1,"approaching does not prepay");
        run.keyedDoorCost=cost;
        for(int n=0;n<240;++n)run.step({});
        check(run.arena.passages[size_t(i)].locked==(cost==2)&&run.keys==1,"queued unlock uses the latest cost, including insufficient funds and free test override");
    }
}
void findReview() {
    for(uint64_t seed=0;seed<2000;++seed) {
        auto run=generated(seed);
        for(size_t i=0;i<run.arena.passages.size();++i) {
            const auto &p=run.arena.passages[i];if(!p.locked)continue;
            const int side=run.arena.rooms[size_t(p.rooms[0])].kind==RoomKind::Power?1:0,room=p.rooms[size_t(side)];
            if(run.rooms[size_t(room)].residents.size()>3)continue;
            for(const auto &key:run.arena.keys)if(key.room==room) {
                const auto route=run.arena.path(key.position,run.arena.doorApproach(int(i),side),.48f);
                if(route.empty())continue;
                std::cout<<"REVIEW seed="<<seed<<" room="<<room+1<<" passage="<<i<<" side="<<side<<" enemies="<<run.rooms[size_t(room)].residents.size()<<" key="<<key.position.x<<","<<key.position.z<<'\n';return;
            }
        }
    }
    throw std::runtime_error("no quiet natural witness found");
}
}
int main(int argc,char **argv) {
    try {
        if(argc>1&&std::string(argv[1])=="--find-review"){findReview();return 0;}
        spending();rejected();coverage();queuedCost();
        std::cout<<"PASS keyed doors: 48 cost/inventory cases, 13 rejection cases, repeat/revisit, 27 generated size/route cases and two queued live edits\n";
    } catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}
}
