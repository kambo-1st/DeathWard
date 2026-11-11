#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::vector<std::string> columns(const std::string &row){std::istringstream in(row);std::vector<std::string> result;for(std::string s;std::getline(in,s,',');)result.push_back(s);return result;}
std::unique_ptr<Simulation> fixture(bool enabled=true) {
    auto run=std::make_unique<Simulation>(1866,1,WorldState{},MissionTheme::Mine,false);
    run->arena=Arena{};run->arena.bounds={{-100,-1,-100},{100,20,100}};run->arena.rooms.resize(1);
    auto &r=run->arena.rooms[0];r.bounds=run->arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;
    r.floors={{{-100,-.4f,-100},{100,0,100}}};run->arena.rebuildWalls();
    run->enemies.clear();run->projectiles.clear();run->hazards.clear();run->moneyPickups.clear();run->heartPickups.clear();
    run->rooms.assign(1,{});run->room=0;run->stats={};run->debugScenario=true;run->godMode=true;
    run->player.position={40,.85f,0};if(enabled)run->spiderMovementMultiplier=1;
    return run;
}
void step(Simulation &run,int count){for(int n=0;n<count;++n)run.step({},Tick);}

constexpr float scale=Simulation::GaperMovementScale;
const std::string root=std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/";
Vector3 world(float x,float z,Vector3 offset={}){return {offset.x+(x-320)*scale,.85f,offset.z+(z-280)*scale};}
void nativeMotion(int substeps,Vector3 offset) {
    std::ifstream in(root+"spider-pooter-movement/spider-native.csv");check(bool(in),"native Spider trace exists");
    std::string row,name;std::getline(in,row);std::unique_ptr<Simulation> run;EntityId id=0;int states=0;float maxError=0;
    while(std::getline(in,row)) {
        const auto c=columns(row);
        if(name!=c[0]) {
            name=c[0];run=fixture();run->player.position=world(1000,280,offset);
            id=run->spawnMonster(monsterId(85),world(320,280,offset));auto *e=run->findEnemy(id);check(e,"native Spider spawns");
            e->friendly=true;e->spider.emplace();e->spider->initialized=true;e->spider->counter=std::stoi(c[3]);
            e->velocity={std::stof(c[2])*scale*30,0,0};
            if(name!="idle"){e->spider->targetReady=e->spider->pursuing=true;e->spider->destination=world(name=="burst-arrival"?330:500,280,offset);}
        }
        for(int k=0;k<substeps;++k)run->step({},1.f/(30*substeps));
        const auto &e=*run->findEnemy(id);const float error=planarDistance(e.position,world(std::stof(c[6]),std::stof(c[7]),offset));
        maxError=std::max(maxError,error);
        check(error<.002f&&length(sub(e.velocity,{std::stof(c[8])*scale*30,0,std::stof(c[9])*scale*30}))<.005f&&
              e.spider->targetReady==(std::stoi(c[4])!=0)&&e.spider->counter==std::stoi(c[5]),"production Spider matches preserved native states");++states;
    }
    check(states==48,"all native Spider states compared");
    std::cout<<"PASS native Spider states="<<states<<" hz="<<30*substeps<<" offset="<<offset.x<<','<<offset.z<<" max_error="<<maxError<<'\n';
}
void acquisition() {
    std::ifstream in(root+"spider-pooter-movement/spider-gates.csv");check(bool(in),"native gates available");std::string row;std::getline(in,row);int gates=0;
    while(std::getline(in,row)) {
        auto run=fixture();run->player.position={1.3f,.85f,0};auto id=run->spawnMonster(monsterId(85),{0,.85f,0});
        auto *e=run->findEnemy(id);e->spider.emplace();e->spider->initialized=true;e->spider->counter=std::stoi(columns(row)[0]);
        run->step({},1.f/30);e=run->findEnemy(id);const auto c=columns(row);
        check(e->spider->counter==std::stoi(c[1])&&e->spider->targetReady==(std::stoi(c[2])!=0),"production acquisition matches native idle gate");++gates;
    }
    std::ifstream leads(root+"d05-spider-movement/native-target-lead.csv");check(bool(leads),"native target lead available");std::getline(leads,row);int predictions=0;
    while(std::getline(leads,row)) {
        const auto c=columns(row);auto run=fixture();run->player.position=world(std::stof(c[0]),std::stof(c[1]));
        const auto id=run->spawnMonster(monsterId(85),add(run->player.position,{-1.3f,0,0}));auto *e=run->findEnemy(id);e->spider.emplace();e->spider->initialized=true;e->spider->counter=14;
        const Vector3 velocity{std::stof(c[2])*scale*60,0,std::stof(c[3])*scale*60};
        Input input;input.movement=unit(velocity);if(length(velocity)<.001f)input.movement={};else run->player.attributes.speed=length(velocity)/4.8f;
        run->step(input,Tick);e=run->findEnemy(id);
        const auto expected=add(run->player.position,{(std::stof(c[4])-std::stof(c[0]))*scale,0,(std::stof(c[5])-std::stof(c[1]))*scale});
        check(e->spider->pursuing&&planarDistance(e->spider->destination,expected)<.0001f,"actual Spider acquisition uses native player-step lead");++predictions;
    }
    auto run=fixture();run->player.position={2,.85f,0};auto id=run->spawnMonster(monsterId(85),{0,.85f,0});
    bool burst=false,idleAfter=false,restarted=false;Vector3 destination{};
    for(int i=0;i<420;++i) {
        step(*run,1);const auto &r=*run->findEnemy(id)->spider;
        if(r.targetReady&&!burst){burst=true;destination=r.destination;run->player.position={0,.85f,2};}
        else if(burst&&!idleAfter&&r.targetReady)check(planarDistance(destination,r.destination)<.0001f,"burst commits target while player retreats");
        if(burst&&!r.targetReady)idleAfter=true;if(idleAfter&&r.targetReady)restarted=true;
    }
    check(burst&&idleAfter&&restarted&&run->projectiles.empty(),"natural acquisition repeats pause/burst cycle");
    auto far=fixture();id=far->spawnMonster(monsterId(85),{0,.85f,0});step(*far,31);const auto &r=*far->findEnemy(id)->spider;
    check(r.targetReady&&!r.pursuing&&length(r.destination)>=70*scale&&length(r.destination)<=110*scale+.001f,"distant player produces correctly scaled wandering");
    auto edge=fixture();edge->arena.rooms[0].bounds={{-2,-1,-2},{2,8,2}};edge->player.position={1.4f,.85f,0};
    id=edge->spawnMonster(monsterId(85),{.1f,.85f,0});auto *e=edge->findEnemy(id);e->spider.emplace();e->spider->initialized=true;e->spider->counter=14;
    Input outward;outward.movement={1,0,0};edge->step(outward,Tick);
    check(e->spider->pursuing&&std::abs(e->spider->destination.x-1.6f)<.0001f,"prediction clamps at existing body margin");
    auto narrow=fixture();narrow->arena.rooms[0].bounds={{-.6f,-1,-.6f},{.6f,8,.6f}};id=narrow->spawnMonster(monsterId(85),{0,.85f,0});step(*narrow,31);
    check(narrow->findEnemy(id)->spider->targetReady&&length(narrow->findEnemy(id)->spider->destination)<1,"inverted native margins collapse safely in small adapted rooms");
    std::cout<<"PASS idle gates="<<gates<<" native lead cases="<<predictions<<" committed bursts, pauses and far wandering\n";
}
void tuningAndSafety() {
    for(float multiplier:{.1f,.5f,1.f,2.f}) {
        auto run=fixture();run->spiderMovementMultiplier=multiplier;auto id=run->spawnMonster(monsterId(85),{0,.85f,0});auto *e=run->findEnemy(id);
        e->spider.emplace();e->spider->initialized=e->spider->targetReady=true;e->spider->counter=1000;e->spider->destination={90,.85f,0};step(*run,120);e=run->findEnemy(id);
        check(std::abs(length(e->velocity)-9*scale*30*multiplier)<.002f,"native burst steady speed scales with drive only");
        check(std::abs(e->hp-20.8f)<.0001f&&e->radius==.4f&&run->player.shotDamage==24,"Spider HP/damage/geometry unchanged");
        auto before=*e;run->spiderMovementMultiplier=.5f;
        check(e->spider->counter==before.spider->counter&&distance(e->velocity,before.velocity)==0&&distance(e->position,before.position)==0,"editing preserves phase/momentum/location");
        step(*run,2);e=run->findEnemy(id);const float expected=(9*multiplier+3)*.6f*scale*30;
        check(std::abs(length(e->velocity)-expected)<.003f&&e->spider->destination.x==90,"next steering update consumes drive without restarting target");
    }
    for(auto type:{monsterId(94),monsterId(14),monsterId(814),monsterId(884)}) {
        auto a=fixture(false),b=fixture();auto x=a->spawnMonster(type,{0,.85f,0}),y=b->spawnMonster(type,{0,.85f,0});
        for(int i=0;i<120;++i){step(*a,1);step(*b,1);check(distance(a->findEnemy(x)->position,b->findEnemy(y)->position)<.001f,"unselected actors unchanged");}
    }
    auto blocked=fixture();blocked->player.position={2,.85f,0};blocked->arena.obstacles={{{.7f,0,-99},{1.3f,3,99}}};blocked->arena.rebuildWalls();auto id=blocked->spawnMonster(monsterId(85),{0,.85f,0});
    for(int i=0;i<360;++i){step(*blocked,1);const auto &e=*blocked->findEnemy(id);check(!e.spider->pursuing&&!blocked->arena.blocked(e.position,e.radius),"blocked sight wanders without entering cover");}
    auto stuck=fixture();stuck->player.position={1.5f,.85f,0};id=stuck->spawnMonster(monsterId(85),{0,.85f,0});step(*stuck,31);
    check(stuck->findEnemy(id)->spider->pursuing,"near player acquired before obstruction");stuck->arena.obstacles={{{.5f,0,-99},{.8f,3,99}}};stuck->arena.rebuildWalls();bool cancelled=false;
    for(int i=0;i<100;++i){step(*stuck,1);const auto &e=*stuck->findEnemy(id);check(!stuck->arena.blocked(e.position,e.radius),"new obstruction never penetrated");cancelled|=!e.spider->targetReady;}check(cancelled,"blocked burst recovers to idle");
    auto stun=fixture();stun->player.position={2,.85f,0};id=stun->spawnMonster(monsterId(85),{0,.85f,0});step(*stun,40);
    auto *e=stun->findEnemy(id);e->state=EnemyState::Stunned;e->stateTime=.3f;step(*stun,2);check(!e->spider->targetReady&&length(e->velocity)==0,"stun cancels burst");
    auto river=fixture();river->arena.canyon=std::make_shared<CanyonTerrain>();auto &water=*river->arena.canyon;
    water.x=water.z=-31;water.step=1;water.width=water.depth=63;water.heights.resize(63*63);
    for(int z=0;z<63;++z)for(int x=0;x<63;++x)water.heights[size_t(z*63+x)]=std::abs(z-31)<=2?-1.f:0.f;
    water.boundaryHeights=water.heights;water.riverKind=CanyonRiverKind::Interior;water.river={{{-30,0,0},2,0},{{30,0,0},2,60}};
    id=river->spawnMonster(monsterId(85),{0,.85f,-4});river->player.position={0,.85f,4};
    for(int n=0;n<360;++n){step(*river,1);const auto &body=*river->findEnemy(id);check(!water.waterBlocked(body.position)&&!river->arena.blocked(body.position,body.radius),"ordinary Spider stays out of river");}
    auto contact=fixture();contact->godMode=false;contact->player.position={0,.85f,0};id=contact->spawnMonster(monsterId(85),{0,.85f,0});step(*contact,1);check(contact->player.hp==5,"ordinary Spider contact removes one half heart");
    std::cout<<"PASS live drive, unselected actors, sight/cover, blocked burst recovery, stun and contact\n";
}
void inventory() {
    const auto p=BalancePreset::load(root+"d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());
    for(uint64_t seed=0;seed<256;++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),p.roomSizeScale,p.roomMinHalfTiles,p.roomMaxHalfTiles,p.routeLengthScale);
        for(int room=1;room<s.finalRoom();++room) {
            bool adjacent=false;for(const auto &route:s.arena.passages)if((route.rooms[0]==0&&route.rooms[1]==room)||(route.rooms[1]==0&&route.rooms[0]==room))adjacent=true;
            if(!adjacent)continue;bool spider=false,suitable=true;
            for(const auto &e:s.roomEnemies(room)){spider|=e.monster==monsterId(85);suitable&=e.champion<0&&(e.monster==monsterId(85)||e.monster==monsterId(10,1)||e.monster==monsterId(12));}
            if(spider&&suitable){std::cout<<"NATURAL seed="<<seed<<" room="<<room<<'\n';for(const auto &e:s.roomEnemies(room))std::cout<<monsterIdText(e.monster)<<" id="<<e.id<<" at="<<e.position.x<<','<<e.position.z<<'\n';return;}
        }
    }
    check(false,"accessible ordinary Spider encounter found");
}
}
int main(int argc,char **argv){try {
    if(argc>1&&std::string(argv[1])=="--inventory"){inventory();return 0;}
    for(int n:{1,2,4})for(auto offset:{Vector3{},Vector3{30,0,-17}})nativeMotion(n,offset);
    acquisition();tuningAndSafety();std::cout<<"PASS D05 main-game Spider integration\n";
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
