#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-black-bony-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(std::string from,std::string to){const auto p=path/"black_bony.mechanics";std::ifstream in(p);std::string text((std::istreambuf_iterator<char>(in)),{});auto at=text.find(from);check(at!=std::string::npos,"fixture row exists");text.replace(at,from.size(),to);std::ofstream(p)<<text;}
    auto stationary(){replace("Skull 32 3.75","Skull 32 0");return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,5,30}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};r.kind=RoomKind::Combat;
    s.rooms.assign(1,{});s.room=0;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.moneyPickups.clear();s.stats={};s.godMode=true;s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s){auto id=s.spawnMonster(monsterId(277),{0,.85f,0});check(id!=0,"Black Bony spawns");s.findEnemy(id)->cooldown=0;return id;}
void waitThrow(Simulation &s,EntityId id){for(int n=0;n<60&&s.findEnemy(id)->state!=EnemyState::Windup;++n)tick(s);check(s.findEnemy(id)->state==EnemyState::Windup,"aligned target acquires");}
void kill(Simulation &s,EntityId id,bool execution=false,bool debug=false){Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1000;hit.execution=execution;hit.debugExecution=debug;s.queueRoot(hit);s.drainEvents();}
void burst() {
    Pack p;auto lib=p.stationary();auto s=fixture(lib);const auto id=spawn(s);waitThrow(s,id);
    tick(s,7);check(s.stats.projectiles==0,"first Shoot waits4native frames");tick(s);check(s.stats.projectiles==1,"first bone fires");
    s.player.position={8,.85f,10};
    for(int shot=2;shot<=3;++shot) {
        tick(s,25);check(s.stats.projectiles==unsigned(shot-1),"entire13-frame animation between shots");tick(s);
        check(s.stats.projectiles==unsigned(shot),"second/third fires without a fresh alignment test");
        const auto &b=s.projectiles.back();check(b.kind==ProjectileKind::DarkBone&&near(length(b.velocity),30),"dark fast bone retained");
        check(dot(unit(b.velocity),unit(horizontal(sub(s.player.position,s.findEnemy(id)->position))))>.999f,"each bone aims at current player");
        s.player.position={-8,.85f,10};
    }
    tick(s,17);check(s.findEnemy(id)->behavior.state!=0,"third recovery holds through frame38");tick(s);
    check(s.findEnemy(id)->behavior.state==0&&s.stats.projectiles==3,"burst completes at39native frames");
    auto interrupted=fixture(lib);auto other=spawn(interrupted);waitThrow(interrupted,other);tick(interrupted,10);kill(interrupted,other);tick(interrupted,100);
    check(interrupted.stats.projectiles==1&&interrupted.stats.explosions==1,"death interrupts remainder and explodes once");
    auto stun=fixture(lib);other=spawn(stun);waitThrow(stun,other);tick(stun,10);stun.findEnemy(other)->state=EnemyState::Stunned;stun.findEnemy(other)->stateTime=1;stun.player.position={8,.85f,8};tick(stun,40);
    check(stun.stats.projectiles==1,"stun cancels remaining burst");
}
void explosion() {
    for(bool execution:{false,true}) {
        auto s=fixture();const auto id=spawn(s);s.godMode=false;s.player.position={0,.85f,3};
        const auto witness=s.spawnMonster(monsterId(10),{3,.85f,0});s.findEnemy(witness)->hp=s.findEnemy(witness)->maxHp=200;
        kill(s,id,execution);check(s.stats.explosions==1&&near(s.player.hp,75)&&near(s.findEnemy(witness)->hp,72),"source damage conversion, player damage and friendly fire");
        kill(s,id,execution);check(s.stats.explosions==1&&s.stats.kills==1,"duplicate lethal input cannot repeat blast or kill");
    }
    {auto s=fixture();const auto id=spawn(s);s.godMode=false;s.player.position={0,.85f,3};s.arena.walls.push_back({{-2,0,1},{2,4,2}});kill(s,id);check(s.player.hp==StartingHealth,"line-check shields player behind real cover");}
    {auto s=fixture();const auto id=spawn(s);s.godMode=false;s.player.position={0,.85f,7};kill(s,id);check(s.player.hp==StartingHealth,"outside blast reach is safe");}
    {auto s=fixture();const auto id=spawn(s);kill(s,id,true,true);check(s.stats.explosions==0,"debug execution bypasses destructive death effects");}
    {auto s=fixture();const auto id=spawn(s);Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1000;s.queueRoot(hit);s.limits.queuedEvents=0;s.drainEvents();
     check(s.findEnemy(id)&&s.findEnemy(id)->deathBlastPending&&s.stats.explosions==0,"full queue retains mandatory death blast");
     s.debugScenario=false;tick(s);check(s.findEnemy(id)&&!s.roomClear,"pending dead actor survives cleanup and gates completion");
     s.limits.queuedEvents=256;tick(s,3);check(s.stats.explosions==1&&!s.findEnemy(id)&&s.roomClear,"retry explodes once before cleanup/room clear");}
}
void routingAndConfig() {
    const auto lib=defaultMechanics();check(near(lib->monsterHealth(monsterId(277),3),44.8f),"source stage HP");
    check(!lib->deathBlast(monsterId(227)),"ordinary Bony remains nonexplosive");
    bool found=false;
    for(uint64_t seed=0;seed<20&&!found;++seed) {
        ExpeditionPlan p(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<p.floorCount&&!found;++floor) {
            if(p.profileOnFloor(floor).band==0)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int r=1;r<s.finalRoom();++r){int count=0;for(const auto &e:s.roomEnemies(r))if(e.monster==monsterId(277)){++count;found=true;std::cout<<"NATURAL_BLACK_BONY seed="<<seed<<" floor="<<floor<<" room="<<r<<" hp="<<e.hp<<'\n';}check(count<=1,"one Black Bony per ordinary room");}
        }
    }
    check(found,"real ordinary seeded resident reachable");
    for(int pattern=0;pattern<4;++pattern)for(const auto &e:lib->encounterPool(0,EncounterPattern(pattern)).specialists)check(e.monster!=monsterId(277),"absent from opening band");
    for(const auto &change:std::array<std::pair<std::string,std::string>,5>{{{"128 20 6","128 20 0"},{"128 20 6","128 nan 6"},{"death_blast 277.0.0","death_blast 9999.0.0"},{"death_blast 277.0.0 128 20 6","death_blast 277.0.0 128 20 6\ndeath_blast 277.0.0 128 20 6"},{"death_blast 277.0.0","death_blast 25.0.0"}}}) {
        Pack p;p.replace(change.first,change.second);bool rejected=false;try{MechanicsLibrary::load(p.path);}catch(...){rejected=true;}check(rejected,"invalid death blast rejected transactionally");
    }
}
}
int main(){try{burst();explosion();routingAndConfig();std::cout<<"PASS Black Bony three-cycle aim, death blast, pressure retention and ordinary routing\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
