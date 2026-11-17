#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceFullFlyRoom.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *message){if(!b)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.00002f;}
auto rows(const char *file) {
    std::ifstream in(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/d14a2-full-fly/source/"+file);
    check(bool(in),"native capture exists");std::vector<std::vector<float>> out;std::string line;std::getline(in,line);
    while(std::getline(in,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream r(line);std::vector<float> v;float f;while(r>>f)v.push_back(f);out.push_back(v);}return out;
}
void native() {
    int count=0;
    for(const auto &r:rows("native-pursuit.csv")) {
        const auto v=fullFlyPursuit({r[0],0,r[1]},r[2]!=0);
        check(near(v.x,r[3])&&near(v.z,r[4]),"native Full Fly pursuit, deadzone and Skatole");++count;
    }
    for(const auto &r:rows("native-recoil.csv")) {
        Vector3 recoil{r[0],0,r[1]};const auto v=fullFlyRecoil(recoil);
        check(near(v.x,r[2])&&near(v.z,r[3])&&near(recoil.x,r[4])&&near(recoil.z,r[5]),"native recoil cutoff and decay");++count;
    }
    for(const auto &r:rows("native-burst.csv")) {
        const auto v=fullFlyDeathVelocity(int(r[0]),1.f/30);
        check(near(v.x,r[1])&&near(v.z,r[2]),"native six-shot velocities");++count;
    }
    check(count==82,"all native cases compared");std::cout<<"PASS 82 native force/recoil/burst cases\n";
}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Canyon);
    s.arena=Arena{};s.arena.bounds={{-20,-1,-20},{20,8,20}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-20,-.4f,-20},{20,0,20}}};}
    s.arena.boundaryWalls={{{-21,-1,-21},{-20,8,21}},{{20,-1,-21},{21,8,21}},{{-21,-1,-21},{21,8,-20}},{{-21,-1,20},{21,8,21}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void hit(Simulation &s,EntityId id,float damage=11.2f,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.debugExecution=debug;e.execution=debug;
    check(s.queueRoot(e),"hit admitted");s.drainEvents();
}
void behavior() {
    auto s=fixture(),same=fixture();const auto id=s.spawnMonster(monsterId(249),{0,.85f,0}),other=same.spawnMonster(monsterId(249),{0,.85f,0});
    check(id&&near(s.findEnemy(id)->hp,32)&&s.roomThreats()==1,"source HP10 x3.2 and threat participation");
    float path=0;auto last=s.findEnemy(id)->position;
    for(int i=0;i<480;++i){s.step({});same.step({});const auto *e=s.findEnemy(id);check(e&&distance(e->position,same.findEnemy(other)->position)<1e-6f,"seeded motion deterministic");check(!s.arena.flightBlocked(e->position,e->radius,0),"flight stays inside walls");path+=distance(last,e->position);last=e->position;}
    check(path>5&&s.projectiles.empty(),"living Full Fly moves without firing");
    s.godMode=false;s.player.position=s.findEnemy(id)->position;s.step({});check(s.player.hp==5,"contact takes one half heart");
    s.godMode=true;s.player.position={-15,.85f,-15};hit(s,id);hit(s,id);check(s.findEnemy(id)->alive,"two base hits do not kill");hit(s,id);
    check(s.stats.kills==1&&s.projectiles.size()==6,"third hit kills once and emits six projectiles");
    for(const auto &p:s.projectiles)check(p.hostile&&p.fullFlyDeathShot&&p.pooterFlight&&near(length(p.velocity),8*Simulation::GaperMovementScale*30),"death shot uses native speed and height flight");
    const auto velocity=s.projectiles.front().velocity;s.fullFlyTuning.shotSpeed=.5f;
    check(distance(s.projectiles.front().velocity,velocity)==0,"emitted shots retain their birth speed");
    for(int i=0;i<240;++i)s.step({});check(s.projectiles.empty()&&s.stats.kills==1,"burst expires without duplicate emission");
    auto limited=fixture();limited.limits.projectiles=2;const auto capped=limited.spawnMonster(monsterId(249),{});hit(limited,capped,100);
    check(limited.projectiles.size()==2&&limited.findEnemy(capped)->buzz->fullFlyDeathPending,"capacity retains remaining burst");
    limited.fullFlyTuning.shotSpeed=2;limited.limits.projectiles=20;limited.step({});
    check(limited.stats.projectiles==6,"deferred shots complete exactly one burst");
    for(const auto &p:limited.projectiles)check(near(length(p.velocity),8*Simulation::GaperMovementScale*30),"pending burst retains speed selected at death");
    auto debug=fixture();const auto d=debug.spawnMonster(monsterId(249),{});hit(debug,d,100,true);check(debug.projectiles.empty(),"debug cleanup suppresses death attacks");
    auto tuned=fixture();tuned.fullFlyTuning.shotSpeed=.5f;const auto slow=tuned.spawnMonster(monsterId(249),{});hit(tuned,slow,100);
    check(tuned.projectiles.size()==6&&near(length(tuned.projectiles[0].velocity),4*Simulation::GaperMovementScale*30),"independent death-shot tuning");
    check(near(defaultMechanics()->withRegularHealthMultiplier(.75f)->monsterHealth(monsterId(249),1),24),"shared regular HP multiplier");
    std::cout<<"PASS runtime motion/contact/three hits/six shots/capacity/expiry/HP controls\n";
}
Simulation generated(uint64_t seed,float scale=1.1f,int minimum=7,int maximum=9,int mode=1) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,minimum,maximum,.3f,true,mode,true,true,true,true,true,true,1,1,{}, {},true,25,{1});
}
void generation() {
    int witnesses=0;
    for(uint64_t seed:{0,1,7,69})for(int size=0;size<3;++size) {
        auto s=generated(seed,size==0?.75f:size==1?1.1f:1.5f,size==0?5:size==1?7:10,size==0?5:size==1?9:10);
        if(!s.enterSourceRoomReview(704))continue;
        ++witnesses;const int room=s.room;
        check(s.enemies.size()==2&&s.roomEnemyCount(room)==2,"complete source704 contains exactly two Full Flies");
        for(size_t i=0;i<2;++i)check(s.enemies[i].monster==monsterId(249)&&distance(s.enemies[i].position,fullFlyRoomPosition(s.arena.rooms[size_t(room)],int(i)))<.0001f,"recorded cells mapped without substitution");
        for(const auto &p:s.arena.breakables)check(p.room!=room,"recorded empty floor has no unrelated destructibles");
        s.godMode=true;for(auto id:{s.enemies[0].id,s.enemies[1].id})hit(s,id,100);
        check(s.projectiles.size()==12,"both flies emit their full death bursts");
        for(int n=0;n<240;++n)s.step({});check(s.roomClear&&s.rooms[size_t(room)].cleared,"ordinary encounter clears after deaths");
        s.enterRoom(0);s.enterRoom(room);check(s.roomThreats()==0&&s.roomClear,"revisit does not respawn flies");
        std::cout<<"WITNESS seed="<<seed<<" room="<<room+1<<" scale="<<(size==0?.75f:size==1?1.1f:1.5f)<<'\n';
    }
    check(witnesses>=4,"multiple generated size/seed cases");
    auto off=generated(69,1.1f,7,9,0);check(!off.enterSourceRoomReview(704),"SOURCE OFF does not allocate Full Fly encounter");
}
void presets() {
    const auto root=std::filesystem::path(DEATHWARD_TEST_ROOT);
    const auto dir=std::filesystem::temp_directory_path()/("dw-full-fly-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    auto p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());
    check(p.defaultZoomPercent==165&&p.fullFly==FullFlyTuning{},"old accepted preset retains view and migrates baseline Full Fly");
    p.fullFly={.6f,1.25f};p.save(dir/"export.json");auto q=BalancePreset::load(dir/"export.json",defaultMechanics()->fingerprint());
    check(q.fullFly==p.fullFly&&q.json()==p.json(),"schema48 exports and reloads both values");
    p.fullFly.movement=0;bool rejected=false;try{p.validate();}catch(...){rejected=true;}check(rejected,"invalid multiplier rejected");
    std::filesystem::remove_all(dir);std::cout<<"PASS preset migration/export/load/validation\n";
}
}
int main(){try{native();behavior();generation();presets();std::cout<<"PASS Full Fly delivery checks\n";return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
