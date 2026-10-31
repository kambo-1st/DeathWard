#include "combat/Simulation.hpp"
#include "combat/LobFlight.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-lob-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(std::string from,std::string to){const auto p=path/"gurgle.mechanics";std::ifstream in(p);std::string text((std::istreambuf_iterator<char>(in)),{});auto n=text.find(from);check(n!=std::string::npos,"fixture text exists");text.replace(n,from.size(),to);std::ofstream(p)<<text;}
    auto fixed(){replace("lob_walker 87.0.0 60 ","lob_walker 87.0.0 1 ");replace("Walker 128 3.6 ","Walker 128 0 ");replace("11.55 5.775 ","11.55 0 ");return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,12,30}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;
    r.floors={{{-30,-.4f,-30},{30,0,30}}};
    s.rooms.assign(1,{});s.room=0;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.moneyPickups.clear();s.stats={};
    s.godMode=true;s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s,MonsterId id=monsterId(87)){auto actor=s.spawnMonster(id,{0,.85f,0});check(actor!=0,"actor exists");s.findEnemy(actor)->cooldown=0;return actor;}
void flight() {
    // Independent native recurrence, including both extreme Gurgle arcs and Splasher.
    for(auto [initial,accel]:{std::pair{-6.5f,.72f},std::pair{-23.3f,.72f},std::pair{-8.f,.4f}}) {
        float sourceHeight=-23,sourceSpeed=initial,worldHeight=1.15f,worldSpeed=-initial*1.5f;
        const float gravity=(.1f+accel)*45;
        for(int frame=0;frame<80;++frame) {
            sourceSpeed=.9f*sourceSpeed+.1f+accel;sourceHeight+=sourceSpeed;
            worldHeight+=advanceLobHeight(worldSpeed,gravity,.9f,Tick);
            worldHeight+=advanceLobHeight(worldSpeed,gravity,.9f,Tick);
            check(near(worldHeight,-sourceHeight*.05f)&&near(worldSpeed,-sourceSpeed*1.5f),"60Hz flight matches30Hz source endpoints");
        }
    }
    std::cout<<"LOB_FLIGHT source_ticks=240 endpoint_match=1\n";
}
void attack() {
    Pack p;auto lib=p.fixed();auto s=fixture(lib);const auto id=spawn(s);
    tick(s,2);check(s.findEnemy(id)->state==EnemyState::Windup&&s.stats.projectiles==0,"acquires on30Hz clock");
    tick(s,9);check(s.stats.projectiles==0,"Shoot not early");s.player.position={8,.85f,0};tick(s);
    check(s.stats.projectiles==1&&s.projectiles.size()==1&&s.hazards.empty(),"Shoot atframe5 creates travelling projectile, not delayed ground hazard");
    const auto shot=s.projectiles.front();check(shot.kind==ProjectileKind::Ipecac&&near(shot.radius,.352f)&&near(length(horizontal(shot.velocity)),11.55f),"physical lob appearance and speed");
    check(shot.velocity.x>11.54f&&std::abs(shot.velocity.z)<.001f&&shot.velocity.y>0,"aim follows target at Shoot and travels upward");
    tick(s,49);check(s.findEnemy(id)->state==EnemyState::Windup,"full recovery throughframe29");tick(s);
    check(s.findEnemy(id)->state==EnemyState::Ready,"attack finishes atframe30");
    auto blocked=fixture(lib);const auto b=spawn(blocked);blocked.arena.walls.push_back({{-2,0,2},{2,12,3}});tick(blocked,12);
    check(blocked.stats.projectiles==1&&blocked.findEnemy(b)->state==EnemyState::Windup,"no invented line-of-sight acquisition restriction");
    tick(blocked,60);check(blocked.stats.explosions>0,"actual wall catches lob");
    auto stun=fixture(lib);const auto other=spawn(stun);tick(stun,4);stun.findEnemy(other)->state=EnemyState::Stunned;stun.findEnemy(other)->stateTime=1;tick(stun,40);
    check(stun.stats.projectiles==0&&stun.findEnemy(other)->lob->attackFrame<0,"stun cancels queued Shoot");
    auto full=fixture(lib);const auto f=spawn(full);full.limits.projectiles=0;tick(full,30);
    check(full.stats.projectiles==0&&full.findEnemy(f)->lob->attackFrame==5,"shot capacity holds Shoot without consuming attack");
    full.limits.projectiles=10;tick(full,2);check(full.stats.projectiles==1,"capacity recovery fires once");
}
void splasher() {
    auto s=fixture();const auto id=s.spawnMonster(monsterId(238),{0,.85f,0});auto *e=s.findEnemy(id);
    check(e->cooldown>=20.f/30&&e->cooldown<=39.f/30,"source initial delay");
    e->cooldown=1.f/30;e->facing={1,0,0};e->auxiliary=10;
    tick(s,2);check(s.projectiles.size()==1,"moving headless body fires after delay");
    check(s.projectiles.front().velocity.x>14.99f&&near(s.projectiles.front().velocity.z,0),"headless shot follows actual travel, not player");
    check(e->cooldown>=2&&e->cooldown<=89.f/30&&e->state==EnemyState::Ready,"no windup and integral repeat delay60..89");
    const auto first=s.stats.projectiles;tick(s,118);check(s.stats.projectiles==first,"repeat delay unscaled by floor cooldown multiplier");
    Pack p;p.replace("Headless 38.4 1.6 ","Headless 38.4 0 ");auto still=fixture(MechanicsLibrary::load(p.path));const auto stationary=spawn(still,monsterId(238));tick(still,120);
    check(still.stats.projectiles==0&&still.findEnemy(stationary)->cooldown==0,"zero actual movement neither fires nor resets delay");
}
void blast() {
    Pack p;auto lib=p.fixed();auto s=fixture(lib);const auto id=spawn(s);tick(s,12);
    s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;
    const auto other=s.spawnMonster(monsterId(10),{2,.85f,0});s.findEnemy(other)->hp=s.findEnemy(other)->maxHp=500;
    s.findEnemy(other)->state=EnemyState::Stunned;s.findEnemy(other)->stateTime=10;
    auto &lob=s.projectiles.front();lob.position={0,.23f,0};lob.velocity={0,-1,0};lob.radius=.22f;
    s.godMode=false;s.player.position={0,.85f,3};tick(s,2);
    check(s.stats.explosions==1&&near(s.findEnemy(id)->hp,128)&&near(s.findEnemy(other)->hp,340)&&near(s.player.hp,75),"blast source immunity, friendly fire, player scaling, once");
    auto pressure=fixture(lib);spawn(pressure);tick(pressure,12);pressure.enemies.clear();
    pressure.projectiles.front().position={0,.23f,0};pressure.projectiles.front().velocity={0,-1,0};pressure.projectiles.front().radius=.22f;
    pressure.limits.queuedEvents=0;pressure.debugScenario=false;tick(pressure,2);
    check(!pressure.roomClear&&pressure.projectiles.size()==1&&pressure.projectiles[0].impactPending&&pressure.stats.explosions==0,"pending physical blast gates room completion");
    pressure.limits.queuedEvents=256;tick(pressure,3);
    check(pressure.roomClear&&pressure.projectiles.empty()&&pressure.stats.explosions==1,"dead producer blast survives pressure and room clears afterward");
}
void config() {
    for(const auto &[from,to]:std::array<std::pair<std::string,std::string>,5>{{
        {"36.9 .9 ","36.9 1 "},{"36.9 .9 ","36.9 nan "},{"60 13 30 5 ","60 13 30 30 "},
        {"lob_projectile 87.0.0 ","lob_projectile 87.1.0 "},{"lob_walker 87.0.0 ","lob_walker 9999.0.0 "}}}) {
        Pack p;p.replace(from,to);bool rejected=false;try{MechanicsLibrary::load(p.path);}catch(...){rejected=true;}check(rejected,"invalid lob content rejected atomically");
    }
}
void routing() {
    const auto lib=defaultMechanics();bool gurgle=false,splasher=false;
    for(uint64_t seed=0;seed<30&&!(gurgle&&splasher);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!(gurgle&&splasher);++floor) {
            if(plan.profileOnFloor(floor).band==0)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room) {
                std::array<int,2> counts{};
                for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(87)||e.monster==monsterId(238)) {
                    ++counts[e.monster.type==87?0:1];check(e.lob.has_value()&&near(e.hp,lib->monsterHealth(e.monster,s.arena.profile.sourceStage)),"natural actor has controller and source-stage health");
                    if(e.monster.type==238)check(e.cooldown>=20.f/30&&e.cooldown<=39.f/30&&near(e.cooldown*30,std::round(e.cooldown*30)),"natural Splasher keeps integral initial20..39ticks without floor multiplier");
                    if(e.monster.type==87)gurgle=true;else splasher=true;
                    std::cout<<"NATURAL_LOBBER type="<<e.monster.type<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" hp="<<e.hp<<'\n';
                }
                check(counts[0]<=1&&counts[1]<=1,"at most one of each lobber identity per ordinary room");
            }
        }
    }
    check(gurgle&&splasher,"both regular lobbers reached through real seeded rooms");
    for(int pattern=0;pattern<4;++pattern)for(const auto &e:lib->encounterPool(0,EncounterPattern(pattern)).specialists)
        check(e.monster!=monsterId(87)&&e.monster!=monsterId(238),"opening band unchanged");
}
}
int main(){try{flight();attack();splasher();blast();config();routing();std::cout<<"PASS regular lobbers: timing, current aim, movement aim, physical flight, source blast, queue pressure, validation, seeded routing\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
