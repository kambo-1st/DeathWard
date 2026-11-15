#include "combat/Simulation.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <queue>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool special(RoomKind k){return k==RoomKind::Shop||k==RoomKind::Power;}
void shopLeaf(const Arena &a) {
    check(a.shopRoom>=4&&a.rooms[size_t(a.shopRoom)].kind==RoomKind::Shop,"shop avoids entrance/objectives");
    check(a.rooms[size_t(a.shopRoom)].passages.size()==1,"shop has exactly one entrance");
    const auto &p=a.passages[size_t(a.rooms[size_t(a.shopRoom)].passages.front())];
    const int parent=p.rooms[0]==a.shopRoom?p.rooms[1]:p.rooms[0];
    check(!special(a.rooms[size_t(parent)].kind)&&a.rooms[size_t(parent)].kind!=RoomKind::Boss,"shop branches from ordinary network");
    check(std::count_if(a.rooms.begin(),a.rooms.end(),[](const auto &r){return r.kind==RoomKind::Shop;})==1,"one shop per floor");
}
void shopGraphs() {
    for(int count=MinFloorRooms;count<=RoomCount;++count)for(uint64_t seed=0;seed<1024;++seed) {
        const auto g=generateRoomGraph(seed,false,count,true),again=generateRoomGraph(seed,false,count,true);
        check(g.cells==again.cells&&g.links==again.links&&g.shopRoom==again.shopRoom,"shop graph is deterministic");
        check(int(g.cells.size())==count&&int(std::set<FloorCell>(g.cells.begin(),g.cells.end()).size())==count,"room count and distinct cells retained");
        std::vector<std::vector<int>> adjacent(size_t(count),std::vector<int>{});std::set<std::pair<int,int>> edges;
        for(auto e:g.links) {
            const auto a=g.cells[size_t(e[0])],b=g.cells[size_t(e[1])];
            check(std::abs(a.first-b.first)+std::abs(a.second-b.second)==1,"corridors join neighboring cells without crossing");
            check(edges.insert(std::minmax(e[0],e[1])).second,"no duplicate connection");
            adjacent[size_t(e[0])].push_back(e[1]);adjacent[size_t(e[1])].push_back(e[0]);
        }
        check(g.shopRoom>=4&&adjacent[size_t(g.shopRoom)].size()==1,"reserved shop is a leaf outside protected identities");
        check(adjacent[size_t(g.shopRoom)].front()>0&&adjacent[size_t(g.shopRoom)].front()<g.shopRoom,"shop attached to ordinary non-entrance room");
        for(int i=count-g.powerRooms-1;i<count;++i)check(adjacent[size_t(i)].size()==1,"boss and treasure remain leaves");
        std::set<int> seen{0};std::queue<int> todo;todo.push(0);
        while(!todo.empty()){const int at=todo.front();todo.pop();for(int next:adjacent[size_t(at)])if(next!=g.shopRoom&&seen.insert(next).second)todo.push(next);}
        check(int(seen.size())==count-1,"all other rooms reachable without entering shop");
    }
    check(generateRoomGraph(99,true,5,true).shopRoom==-1,"tutorial does not gain a shop");
    check(generateRoomGraph(99).shopRoom==-1,"historical graph callers retain allocation");
    std::cout<<"shop_leaf_graphs=7168 (1024 seeds x room counts9-15)\n";
}
std::set<int> reachable(const Arena &a) {
    std::set<int> seen{0};std::queue<int> todo;todo.push(0);
    while(!todo.empty()) {
        const int at=todo.front();todo.pop();
        for(int i:a.rooms[size_t(at)].passages) {
            const auto &p=a.passages[size_t(i)];if(p.locked)continue;
            const int next=p.rooms[0]==at?p.rooms[1]:p.rooms[0];
            if(seen.insert(next).second)todo.push(next);
        }
    }
    return seen;
}
Simulation generated(uint64_t seed,int floor=0,bool source=true,float scale=1.1f,float route=.26f) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,
        ExpeditionPacing::Compact,defaultMechanics(),scale,7,9,route,true,1,true,source);
}
void native() {
    std::ifstream input(std::filesystem::path(__FILE__).parent_path().parent_path()/
        "docs/reports/isaac-first-floor-parity/d10d-room-locks/source/native-locks.csv");
    check(bool(input),"native fixture present");std::string line;std::getline(input,line);int verified=0,contrast=0;
    std::map<int,Arena> stages;
    for(int stage=1;stage<=8;++stage) {
        auto profile=defaultMechanics()->configureFloor(ExpeditionPlan(99).profileOnFloor(0),99);
        profile.sourceStage=stage;profile.floor=5; // Stage mapping, not expedition floor, drives the policy.
        stages.emplace(stage,Arena(99,MissionTheme::Canyon,true,false,StoryRoom::None,9,{},profile,false,0,true));
    }
    while(std::getline(input,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int stage,type,mode,origin,target,locked;row>>stage>>type>>mode>>origin>>target>>locked;
        if(type>=4){++contrast;continue;} // Repentance alternate stage families are not enabled in DW.
        const auto &a=stages.at(stage);
        if(target==1) {check(locked==0,"native ordinary exits are unkeyed");++verified;continue;}
        const auto kind=target==2?RoomKind::Shop:RoomKind::Power;bool found=false;
        for(const auto &p:a.passages)if(a.rooms[size_t(p.rooms[0])].kind==kind||a.rooms[size_t(p.rooms[1])].kind==kind) {
            check(p.locked==bool(locked),"actual generated lock agrees with native ordinary stage/type/mode matrix");found=true;
        }
        check(found,"generated source role exists");++verified;
    }
    check(verified==576&&contrast==288,"complete native fixture evaluated with explicit alternate-family exclusions");
}
void maps() {
    int relocations=0;
    for(uint64_t seed=0;seed<16;++seed)for(int floor:{0,1,3}) {
        auto old=generated(seed,floor,false),run=generated(seed,floor,true);
        shopLeaf(old.arena);shopLeaf(run.arena);
        check(run.arena.sourceRoomLocks&&run.sourceRoomLocks,"main canyon policy enabled");
        check(old.arena.rooms.size()==run.arena.rooms.size()&&old.arena.passages.size()==run.arena.passages.size()&&old.arena.keys.size()==run.arena.keys.size(),"room/connection/key counts retained");
        for(size_t i=0;i<run.arena.rooms.size();++i) {
            const auto &a=old.arena.rooms[i],&b=run.arena.rooms[i];
            check(a.kind==b.kind&&a.shape==b.shape&&distance(a.center,b.center)<.0001f&&distance(a.bounds.min,b.bounds.min)<.0001f&&distance(a.bounds.max,b.bounds.max)<.0001f,"room roles and geometry retained");
        }
        const auto open=reachable(run.arena);std::set<std::pair<float,float>> sites;
        for(int room=0;room<run.arena.roomCount();++room)
            if(!special(run.arena.rooms[size_t(room)].kind))check(open.contains(room),"shop lock cannot gate ordinary progression or boss");
        for(size_t i=0;i<run.arena.keys.size();++i) {
            const auto &key=run.arena.keys[i];relocations+=key.room!=old.arena.keys[i].room;
            check(open.contains(key.room)&&sites.insert({key.position.x,key.position.z}).second,"all guaranteed keys available before optional spending, with unique sites");
            const auto route=run.arena.path(run.arena.rooms[size_t(key.room)].entry,key.position,.48f);
            check(!run.arena.blocked(key.position,.48f)&&!route.empty()&&distance(route.back(),key.position)<.05f,"relocated key remains physically reachable");
        }
        for(size_t i=0;i<run.arena.passages.size();++i) {
            const auto &p=run.arena.passages[i],&q=old.arena.passages[i];
            check(p.rooms==q.rooms&&distance(p.from,q.from)<.0001f&&distance(p.to,q.to)<.0001f,"physical connections untouched");
            const bool selected=special(run.arena.rooms[size_t(p.rooms[0])].kind)||special(run.arena.rooms[size_t(p.rooms[1])].kind);
            check(p.locked==(selected?run.arena.profile.sourceStage>1:q.locked),"only selected room entrances change locks");
        }
        if(floor==0)check(open.size()==run.arena.rooms.size(),"opening floor needs no room keys");
    }
    for(float scale:{.75f,1.1f,1.5f})for(float route:{.25f,1.f,2.f}) {
        auto run=generated(7,1,true,scale,route);const auto open=reachable(run.arena);
        shopLeaf(run.arena);
        const int door=run.arena.rooms[size_t(run.arena.shopRoom)].passages.front();run.arena.passages[size_t(door)].locked=false;run.arena.rebuildWalls();
        const auto &p=run.arena.passages[size_t(door)];
        auto from=run.arena.rooms[size_t(p.rooms[0])].entry,to=run.arena.rooms[size_t(p.rooms[1])].entry;from.y=to.y=.85f;
        const auto shopPath=run.arena.path(from,to,.48f);
        if(shopPath.empty()||distance(shopPath.back(),to)>=.05f)
            std::cerr<<"shop path scale="<<scale<<" route="<<route<<" rooms="<<p.rooms[0]<<','<<p.rooms[1]
                     <<" from="<<from.x<<','<<from.z<<" to="<<to.x<<','<<to.z
                     <<" blocked="<<run.arena.blocked(from,.48f)<<','<<run.arena.blocked(to,.48f)<<'\n';
        check(!shopPath.empty()&&distance(shopPath.back(),to)<.05f,"shop branch physically traversable at dynamic sizes and route lengths");
        for(const auto &key:run.arena.keys) {
            const auto path=run.arena.path(run.arena.rooms[size_t(key.room)].entry,key.position,.48f);
            check(open.contains(key.room)&&!run.arena.blocked(key.position,.48f)&&!path.empty()&&distance(path.back(),key.position)<.05f,"dynamic room sizes/routes keep pre-lock key access");
        }
    }
    check(relocations==0,"optional shops no longer require guaranteed-key relocation");
    std::cout<<"generated_maps=48 relocated_keys="<<relocations<<'\n';
}
void narrowNetwork() {
    Arena a;a.rooms.resize(3);a.profile.sourceStage=2;
    for(int i=0;i<3;++i){auto &r=a.rooms[size_t(i)];r.center={float(i*20),.85f,0};r.objective=add(r.center,{5,0,0});r.entry=add(r.center,{0,0,5});}
    a.rooms[0].kind=RoomKind::Empty;a.rooms[2].kind=RoomKind::Shop;
    Passage first;first.rooms={0,1};Passage second;second.rooms={1,2};a.passages={first,second};
    a.rooms[0].passages={0};a.rooms[1].passages={0,1};a.rooms[2].passages={1};
    for(int i=0;i<3;++i)a.keys.push_back({i,a.rooms[size_t(i)].objective,false});
    a.applyRoomLockPolicy();const auto open=reachable(a);
    check(a.keys.size()==3&&open.size()==2,"small open network retains all keys");
    for(size_t i=0;i<a.keys.size();++i){check(open.contains(a.keys[i].room),"fallback key stays before locked shop");for(size_t j=0;j<i;++j)check(distance(a.keys[i].position,a.keys[j].position)>=3,"fallback keys occupy distinct anchors");}
}
void visitsAndRegeneration() {
    auto run=generated(99,1);const int shop=run.arena.shopRoom;
    const int link=run.arena.rooms[size_t(shop)].passages.front();const auto p=run.arena.passages[size_t(link)];
    const int side=p.rooms[0]==shop?1:0,outside=p.rooms[size_t(side)];
    run.jumpDebug(outside);run.clearRoomDebug();run.player.position=run.arena.doorApproach(link,side);run.player.position.y=.85f;run.keys=1;
    check(run.useDoor(link,side)&&run.keys==0,"later shop entrance spends one key");run.enterRoom(shop);
    for(int i:run.arena.rooms[size_t(shop)].passages) {
        const auto &door=run.arena.passages[size_t(i)];const int other=door.rooms[0]==shop?door.rooms[1]:door.rooms[0];
        if(!special(run.arena.rooms[size_t(other)].kind))check(!door.locked,"all ordinary shop exits are free after entry");
        else if(i!=link)check(door.locked,"adjacent unopened treasure room remains locked");
    }
    run.enterRoom(outside);run.enterRoom(shop);check(run.keys==0,"revisit no extra payment");
    run.resizeRooms(1.11f,7,9,.26f,true,1,false);
    check(!run.sourceRoomLocks&&!run.arena.sourceRoomLocks,"Apply supports legacy rollback during exploration");
    run.resizeRooms(1.11f,7,9,.26f,true,1,true);
    check(run.sourceRoomLocks&&run.arena.sourceRoomLocks&&run.keys==0,"Apply restores source rules while retaining inventory");
    auto first=generated(99);const int treasure=first.arena.roomCount()-2;
    first.jumpDebug(treasure);first.keys=0;first.resizeRooms(1.1f,7,9,.26f,true,1,false);
    for(int i:first.arena.rooms[size_t(treasure)].passages)check(!first.arena.passages[size_t(i)].locked,"testing legacy Apply inside free treasure cannot trap zero-key player");
    for(auto pacing:{ExpeditionPacing::Classic,ExpeditionPacing::Compact})for(auto theme:{MissionTheme::Mine,MissionTheme::Canyon}) {
        Simulation r(99,1,{},theme,true,false,WitnessAccount::None,0,pacing,defaultMechanics(),1,0,0,1,false,0,true,true);
        check(r.arena.sourceRoomLocks==(theme==MissionTheme::Canyon&&pacing!=ExpeditionPacing::Classic),"Mine/Classic remain outside source lock policy");
    }
    Simulation tutorial(99,1,{},MissionTheme::Canyon,true,true,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1,0,0,1,false,0,true,true);
    check(!tutorial.arena.sourceRoomLocks,"tutorial remains unchanged");
}
}
int main(){try{shopGraphs();native();maps();narrowNetwork();visitsAndRegeneration();std::cout<<"PASS optional single-entrance shops, source room lock policy, mapped stages, key reachability, shop exits, revisit and regeneration\n";}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
