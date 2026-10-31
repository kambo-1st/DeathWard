#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &m){if(!ok)throw std::runtime_error(m);}
bool near(float a,float b){return std::abs(a-b)<.004f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-bony-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(std::string from,std::string to){const auto p=path/"bony.mechanics";std::ifstream in(p);std::string text((std::istreambuf_iterator<char>(in)),{});auto at=text.find(from);check(at!=std::string::npos,"fixture row exists");text.replace(at,from.size(),to);std::ofstream(p)<<text;}
    auto stationary(){replace("Skull 32 3.75","Skull 32 0");return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,5,30}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};r.kind=RoomKind::Combat;
    s.rooms.assign(1,{});s.room=0;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.moneyPickups.clear();s.stats={};s.godMode=true;s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,10};
    return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s){auto id=s.spawnMonster(monsterId(227),{0,.85f,0});check(id!=0,"Bony spawns");s.findEnemy(id)->cooldown=0;return id;}
void waitWindup(Simulation &s,EntityId id){for(int n=0;n<60&&s.findEnemy(id)->state!=EnemyState::Windup;++n)tick(s);check(s.findEnemy(id)->state==EnemyState::Windup,"aligned visible target starts throw");}
void sourceSequence() {
    Pack p;auto lib=p.stationary();auto s=fixture(lib);auto id=spawn(s);waitWindup(s,id);const auto at=s.findEnemy(id)->position;
    check(s.projectiles.empty(),"windup precedes actual bone");tick(s,7);check(s.projectiles.empty(),"Shoot event waits four native animation frames");
    s.player.position={6,.85f,10};tick(s);check(s.stats.projectiles==1&&s.projectiles.size()==1,"one bone at frame4/30");
    const auto &shot=s.projectiles.front();check(shot.kind==ProjectileKind::Bone&&shot.hostile&&shot.context.sourceEntity==id&&near(length(shot.velocity),30),"distinct fast hostile bone retains owner");
    check(dot(unit(shot.velocity),unit(sub(s.player.position,at)))>.999f,"shot tracks current target at Shoot, not initial alignment");
    check(distance(at,s.findEnemy(id)->position)<.001f,"throwing body stops");tick(s,17);check(s.findEnemy(id)->behavior.state==2&&s.stats.projectiles==1,"recovery holds until animation frame13");tick(s);check(s.findEnemy(id)->behavior.state==0,"animation completion returns to wandering");
    s.player.position={0,.85f,10};tick(s,40);check(s.stats.projectiles>=2,"reacquisition does not add invented multi-second cooldown");
    auto dying=fixture(lib);id=spawn(dying);waitWindup(dying,id);Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1000;dying.queueRoot(hit);dying.drainEvents();tick(dying,30);check(dying.stats.kills==1&&dying.stats.projectiles==0&&dying.roomThreats()==0,"death interrupts a committed throw and resolves its threat");
    auto stun=fixture(lib);id=spawn(stun);waitWindup(stun,id);stun.findEnemy(id)->state=EnemyState::Stunned;stun.findEnemy(id)->stateTime=.5f;tick(stun,20);check(stun.stats.projectiles==0,"stun cancels pending throw");
}
void acquisition() {
    Pack p;auto lib=p.stationary();
    for(auto pos:std::array<Vector3,3>{{{8,.85f,8},{0,.85f,22},{2,.85f,10}}}) {
        auto s=fixture(lib);spawn(s);s.player.position=pos;tick(s,120);check(s.stats.projectiles==0,"diagonal, beyond-range and exact margin do not acquire");
    }
    {auto s=fixture(lib);auto id=spawn(s);s.player.position={1.99f,.85f,10};waitWindup(s,id);}
    {auto s=fixture(lib);spawn(s);s.arena.walls.push_back({{-3,0,4},{3,4,5}});tick(s,120);check(s.stats.projectiles==0,"wall blocks acquisition even with perfect alignment");}
    {auto s=fixture(lib);auto id=spawn(s);waitWindup(s,id);s.godMode=false;tick(s,45);check(near(s.player.hp,StartingHealth-12.5f),"real bone collision applies current hostile damage conversion once");}
    {auto s=fixture(lib);auto id=spawn(s);waitWindup(s,id);s.arena.walls.push_back({{-3,0,4},{3,4,5}});s.godMode=false;tick(s,45);check(near(s.player.hp,StartingHealth)&&s.projectiles.empty(),"bone respects cover inserted after acquisition");}
}
void movementAndRouting() {
    auto s=fixture();const auto id=spawn(s);s.player.position={25,.85f,25};bool moved=false;
    for(int n=0;n<360;++n){const auto from=s.findEnemy(id)->position;tick(s);const auto delta=horizontal(sub(s.findEnemy(id)->position,from));moved|=length(delta)>.001f;check(std::abs(delta.x)<.001f||std::abs(delta.z)<.001f,"wandering uses cardinal axes");check(!s.arena.blocked(s.findEnemy(id)->position,s.findEnemy(id)->radius),"wander remains on legal floor");}
    check(moved,"ordinary Bony moves while not lined up");const auto lib=defaultMechanics();
    for(int band=0;band<4;++band)for(int pattern=0;pattern<4;++pattern){const auto &pool=lib->encounterPool(band,EncounterPattern(pattern));const bool found=std::any_of(pool.specialists.begin(),pool.specialists.end(),[](const auto &e){return e.monster==monsterId(227);});check(found==(band>=1&&(pattern==1||pattern==3)),"configured Caves/Mines onward roles only");}
    check(near(lib->monsterHealth(monsterId(227),1),32)&&near(lib->monsterHealth(monsterId(227),3),44.8f)&&near(lib->monsterHealth(monsterId(227),8),66.56f),"stage HP uses shared source formula and local conversion");
    bool reached=false;
    for(uint64_t seed=0;seed<12&&!reached;++seed){ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);for(int floor=0;floor<plan.floorCount&&!reached;++floor){if(plan.profileOnFloor(floor).band!=1)continue;Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);for(int room=1;room<run.finalRoom();++room)for(const auto &e:run.roomEnemies(room))if(e.monster==monsterId(227)){reached=true;check(near(e.hp,lib->monsterHealth(e.monster,run.arena.profile.sourceStage)),"natural resident stage health");std::cout<<"NATURAL_BONY seed="<<seed<<" floor="<<floor<<" room="<<room<<" hp="<<e.hp<<'\n';}}}
    check(reached,"Bony is an actual seeded expedition resident, not registry-only");
    Simulation tutorial(1866,1,{},MissionTheme::Canyon,true,true);Simulation mine(1866,1,{},MissionTheme::Mine);
    for(auto *run:{&tutorial,&mine})for(int room=0;room<run->arena.roomCount();++room)for(const auto &e:run->roomEnemies(room))check(e.monster!=monsterId(227),"tutorial and Mine roster preserved");
}
void validation() {
    auto reject=[](const std::string &from,const std::string &to){Pack p;p.replace(from,to);bool failed=false;try{MechanicsLibrary::load(p.path);}catch(...){failed=true;}check(failed,"invalid alignment package rejected");};
    reject("aimed_alignment 2 .1 .533333333","aimed_alignment 0 .1 .533333333");reject("aimed_alignment 2 .1 .533333333","aimed_alignment 2 0 .533333333");reject("aimed_alignment 2 .1 .533333333","aimed_alignment 2 .1 nan");reject("aimed_alignment 2 .1 .533333333","");
    const auto old=defaultMechanics();Pack p;auto fresh=p.stationary();check(old->monster(monsterId(227))->speed==3.75f&&fresh->monster(monsterId(227))->speed==0&&old->fingerprint()!=fresh->fingerprint(),"external values load into independent immutable snapshots");
}
}
int main(){try{validation();sourceSequence();acquisition();movementAndRouting();std::cout<<"PASS Bony alignment,13-frame throw, bone hits, interruption, navigation and stage routing\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
