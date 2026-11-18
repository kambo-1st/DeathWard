#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourcePropRooms.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
using namespace dw;
namespace {
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Mine,false);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;
    s.player.position={80,.85f,0};s.attackFlyMovementMultiplier=1;return s;
}
void native() {
    std::ifstream in(Root/"docs/reports/isaac-first-floor-parity/d14a5-mixed-flies/source/native-pursuit.csv");check(bool(in),"native capture available");std::string line;std::getline(in,line);int rows=0,states=0;
    while(std::getline(in,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float dx,dz,vx,vz;row>>dx>>dz>>vx>>vz;++rows;
        for(int hz:{30,60,120})for(float factor:{.1f,1.f,2.f}) {
            auto s=fixture();s.attackFlyMovementMultiplier=factor;auto at=Vector3{17,.85f,-29};
            const auto id=s.spawnMonster(monsterId(18),at);auto *e=s.findEnemy(id);check(e,"ordinary fly admitted");
            auto &r=e->buzz.emplace();r.initialized=r.targetReady=true;r.tick=1;r.target=add(at,{dx*Simulation::GaperMovementScale,0,dz*Simulation::GaperMovementScale});r.clock=0;r.wander={};e->velocity={};
            s.step({},1.f/hz);e=s.findEnemy(id);
            const auto expected=Vector3{vx*.6f*Simulation::GaperMovementScale*30*factor,0,vz*.6f*Simulation::GaperMovementScale*30*factor};
            if(length(sub(e->velocity,expected))>=.0003f)std::cerr<<"FORCE dx="<<dx<<" dz="<<dz<<" hz="<<hz<<" factor="<<factor<<" actual="<<e->velocity.x<<","<<e->velocity.z<<" expected="<<expected.x<<","<<expected.z<<" tick="<<e->buzz->tick<<" summon="<<e->summoner<<" tuned="<<s.tunedAttackFly(*e)<<" pos="<<e->position.x<<","<<e->position.z<<"\n";
            check(length(sub(e->velocity,expected))<.0003f,"actual Simulation matches native supplied force with due third-frame retention");
            check(distance(e->position,add(at,mul(expected,1.f/hz)))<.00003f&&e->buzz->tick==2,"start-of-interval phase at30/60/120Hz");++states;
        }
    }
    check(rows==63&&states==567,"complete supplied native cases");std::cout<<"PASS 63 native force cases / 567 actual Simulation states across tuning and frame partitions\n";
}
void movement() {
    for(float factor:{.1f,.5f,1.f,2.f}) {
        std::vector<Vector3> final;
        for(int hz:{30,60,120}) {
            auto s=fixture();s.attackFlyMovementMultiplier=factor;s.player.position={25,.85f,10};const auto id=s.spawnMonster(monsterId(18),{0,.85f,0});
            for(int n=0;n<hz*4;++n)s.step({},1.f/hz);
            auto *e=s.findEnemy(id);check(e&&e->alive&&e->hp==16&&e->buzz->tick==120,"ordinary source HP and120 source updates");final.push_back(e->position);
            const auto before=e->position,velocity=e->velocity;const auto tick=e->buzz->tick;s.attackFlyMovementMultiplier=.65f;
            check(distance(before,e->position)==0&&distance(velocity,e->velocity)==0&&tick==e->buzz->tick,"live edit does not reset motion or clock");
        }
        check(distance(final[0],final[1])<.005f&&distance(final[1],final[2])<.005f,"same bounded chase across frame partitions");
    }
    for(auto type:{14,249,18}) {
        auto a=fixture(),b=fixture();a.attackFlyMovementMultiplier=.1f;b.attackFlyMovementMultiplier=2;
        const auto x=a.spawnMonster(monsterId(type),{0,.85f,0}),y=b.spawnMonster(monsterId(type),{0,.85f,0});
        if(type==18){a.findEnemy(x)->summoner=99;b.findEnemy(y)->summoner=99;}
        for(int n=0;n<120;++n){a.step({});b.step({});}
        check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.00001f,"Pooter/Full Fly/summoned Attack Fly independent");
    }
    auto s=fixture();const auto id=s.spawnMonster(monsterId(18),{0,.85f,0});s.godMode=false;s.player.position={.5f,.85f,0};s.step({});check(s.player.hp==5&&s.findEnemy(id)->alive,"ordinary contact removes one half-heart and fly survives");s.step({});check(s.player.hp==5,"hurt immunity retained");
    auto d=fixture();d.spawnMonster(monsterId(18),{0,.85f,0});d.godMode=false;d.player.position={.5f,.85f,0};d.player.dodge=.3f;d.step({});check(d.player.hp==6,"universal dodge immunity retained");
    auto f=Simulation(69,1,{},MissionTheme::Canyon);f.attackFlyMovementMultiplier=.65f;f.jumpDebug(f.finalRoom());f.clearRoomDebug();f.step({});f.floorExitRequested=true;check(f.advanceFloor()&&f.attackFlyMovementMultiplier==.65f,"floor transition retains tuning");
    std::cout<<"PASS independent movement, cadence/partitions, contact/dodge and floor transition\n";
}
Simulation generated(uint64_t seed,float scale=1.1f,int lo=7,int hi=9,int mode=1,int props=1) {
    auto s=Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,mode,true,true,true,true,true,true,1,1,{}, {},true,25,{props});
    s.attackFlyMovementMultiplier=1;s.pooterTuning=PooterTuning{};s.applyCombatBalance(3.5f,1);return s;
}
void generation(uint64_t seed,float size,int lo,int hi) {
    auto s=generated(seed,size,lo,hi);check(s.enterSourceRoomReview(414),"complete414 exists at compatible size");const int room=s.room;const auto layout=s.arena.rooms[size_t(room)];const auto &source=*sourcePropRoom(414);
    check(s.enemies.size()==20&&s.floorEncounter(room).monsters.size()==20,"complete20 actor roster");int pooters=0,flies=0,poop=0;std::set<uint64_t> propIds;
    for(const auto &b:s.arena.breakables){check(propIds.insert(b.id).second,"all prop identities unique including expanded grid");if(b.room==room){++poop;check(b.kind==BreakableKind::Dung&&b.sourceGridIndex>0,"only recorded poop");}}
    check(poop==20&&layout.heartSpawns.empty()&&layout.chestSpawns.empty(),"exact20poop and no initial pickups");
    size_t actor=0;for(const auto &slot:source.entries)if(slot.type!=1500){const auto &e=s.enemies[actor++];pooters+=e.monster==monsterId(14);flies+=e.monster==monsterId(18);check(e.monster==monsterId(slot.type)&&planarDistance(e.position,sourcePropCell(layout,source,slot.x,slot.y))<.0001f&&e.champion<0&&!s.arena.blocked(e.position,e.radius),"original cells, identities and physical clearance");check(std::abs(e.hp-(slot.type==14?25.6f:16))<.0001f,"source HP unit retained");}
    check(pooters==8&&flies==12,"8Pooters/12AttackFlies");
    for(const auto &slot:source.entries)if(slot.type==1500){const int grid=(slot.y+1)*28+slot.x+1;auto b=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.room==room&&p.sourceGridIndex==grid;});check(b!=s.arena.breakables.end()&&b->lootSeed==propSlotSeed(layout.sourceRoomSpawnSeed,slot.ordinal)&&planarDistance(b->rewardPosition,sourcePropCell(layout,source,slot.x,slot.y))<.0001f,"native28-stride index, original slot seed and adapted placement");}
    s.godMode=true;
    // Actual projectiles must kill all20 actors, with test positioning only.
    for(int n=0;n<16000&&!s.roomClear;++n){Input in;for(const auto &e:s.enemies)if(e.alive&&!e.environment){for(auto dir:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}){auto p=add(e.position,mul(dir,2));p.y=.85f;if(s.arena.roomAt(p)==room&&!s.arena.blocked(p,.48f)&&s.arena.clear(p,e.position,.15f)){s.player.position=p;in.fire=true;in.aim=e.position;break;}}if(in.fire)break;}s.step(in);}
    check(s.roomClear&&s.stats.kills==20&&s.stats.shots>=48,"real player projectiles clear exact mixed roster");
    // Corner piles can be screened by neighbouring source piles. Shoot an
    // exposed intact pile, preserving the layout's real access restrictions.
    auto prop=s.arena.breakables.end();bool shot=false;
    for(auto candidate=s.arena.breakables.begin();candidate!=s.arena.breakables.end()&&!shot;++candidate) {
        if(candidate->room!=room||candidate->destroyed)continue;
        const auto at=candidate->rewardPosition;
        for(auto dir:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}) {
            const float offset=std::max(candidate->bounds.max.x-candidate->bounds.min.x,candidate->bounds.max.z-candidate->bounds.min.z)*.5f+.9f;
            auto p=add(at,mul(dir,offset));
            if(s.arena.roomAt(p)!=room||s.arena.blocked(p,.48f))continue;
            s.player.position=p;Input in;in.fire=true;in.aim=at;
            for(int n=0;n<360&&!candidate->destroyed;++n)s.step(in);
            if(candidate->destroyed){prop=candidate;shot=true;break;}
        }
    }
    check(shot&&prop->propReward.resolved,"exposed poop destroyed by shots and reward resolved");
    const auto propId=prop->id;const auto rewardSeed=prop->propReward.seed;
    s.enterRoom(0);s.enterRoom(room);check(s.roomThreats()==0,"cleared roster stays clear on revisit");
    prop=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &b){return b.id==propId;});
    check(prop->destroyed&&prop->propReward.seed==rewardSeed,"poop destruction/reward retained");
    s.attackFlyMovementMultiplier=.65f;s.resizeRooms(.75f,5,5,.26f);check(s.attackFlyMovementMultiplier==.65f&&!s.dead,"unrestricted small-room resize succeeds");check(std::none_of(s.arena.rooms.begin(),s.arena.rooms.end(),[](const auto &r){return r.sourceCombatTemplate==414;}),"incompatible small rooms omit whole arrangement");
    s.resizeRooms(size,lo,hi,.26f,std::nullopt,0);check(std::none_of(s.arena.rooms.begin(),s.arena.rooms.end(),[](const auto &r){return r.sourceCombatTemplate==414;}),"OFF removes414");s.resizeRooms(size,lo,hi,.26f,std::nullopt,1);check(s.arena.rooms[size_t(room)].sourceCombatTemplate==414&&s.roomEnemies(room).size()==20,"SOURCE Apply restores complete414");
    auto off=generated(seed,size,lo,hi,1,0);check(!off.enterSourceRoomReview(414),"propsOFF does not admit414");
    std::cout<<"PASS source414 seed="<<seed<<" room="<<room+1<<" size="<<size<<" range="<<lo<<'-'<<hi<<" fitted_cell="<<layout.sourcePropCellOverride<<" complete contents, real kills/poop/revisit and unrestricted Apply\n";
}
void presets() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-mixed-flies-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    for(auto file:{"d03-shooting/user-preset-2026-11-11.json","d14a4-frowning-room/tuned-preset.json"}) {
        auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity"/file,defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&p.attackFlyMovementMultiplier==1,"schema5/50 migrate baseline fly and preserve view");
        p.attackFlyMovementMultiplier=.65f;p.pooterMovementMultiplier=1.2f;p.save(dir/"export.json");check(BalancePreset::load(dir/"export.json",p.mechanicsFingerprint).json()==p.json(),"schema51 exact independent round trip");
        auto bad=p;bad.attackFlyMovementMultiplier=0;bool refused=false;try{bad.save(dir/"export.json");}catch(...){refused=true;}check(refused&&BalancePreset::load(dir/"export.json",p.mechanicsFingerprint).json()==p.json(),"invalid edit leaves exported preset intact");
    }
    std::filesystem::remove_all(dir);std::cout<<"PASS schema51 round trip, migration and invalid-value rejection\n";
}
}
int main(int argc,char **argv){try{std::cout<<std::unitbuf;
 if(argc>1&&std::string(argv[1])=="--find"){for(uint64_t seed=argc>2?std::stoull(argv[2]):0;seed<1000;++seed){if(seed%10==0)std::cout<<"SCAN "<<seed<<'\n';auto s=argc>5?generated(seed,std::stof(argv[3]),std::stoi(argv[4]),std::stoi(argv[5])):generated(seed);if(s.enterSourceRoomReview(414)){std::cout<<"FOUND "<<seed<<" room "<<s.room+1<<'\n';return 0;}}return 1;}
 if(argc>5&&std::string(argv[1])=="--room"){generation(std::stoull(argv[2]),std::stof(argv[3]),std::stoi(argv[4]),std::stoi(argv[5]));return 0;}
 native();movement();presets();return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
