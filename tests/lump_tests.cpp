#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.01f){return std::abs(a-b)<eps;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={12,.85f,12};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(56),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount=7,bool execution=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=amount;h.execution=execution;s.queueRoot(h);s.drainEvents();
}
void acquire(Simulation &s,EntityId id) {
    for(int n=0;n<20&&s.findEnemy(id)->lump->phase!=LumpPhase::Spitting;++n)tick(s);
    check(s.findEnemy(id)->lump->phase==LumpPhase::Spitting,"range and cadence acquire player");
}
void firing() {
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=*e.lump;
    check(near(e.hp,96)&&near(s.content->monsterHealth(e.monster,13),96),"source30HP converts96 without stage growth");
    acquire(s,id);check(r.frame==0&&r.cooldown==63,"attack starts cooldown63");
    check((uint64_t(std::round(s.stats.duration*30))+id)%7==0,"shared acquisition cadence7");
    tick(s,3);check(s.projectiles.empty(),"no shots before frame4");
    s.player.position={-12,.85f,12};const auto aim=unit(horizontal(sub(s.player.position,e.position)));tick(s);
    check(r.volleys==1&&s.projectiles.size()==3,"Shoot4 emits exactly3 projectiles");
    const auto &center=s.projectiles.front();const Vector3 side{-aim.z,0,aim.x};
    check(distance(horizontal(center.velocity),mul(aim,25.2f))<.01f,"shot samples current player with base7 and mode2 speed1.2");
    check(distance(horizontal(s.projectiles[1].velocity),mul(add(mul(aim,.961f),mul(side,.276f)),25.2f*.9f))<.01f,"side velocity preserves native unnormalized spread");
    check(near(center.velocity.y,6)&&near(center.gravity,9)&&near(center.flightRetention,.9f),"default native mode2 physical flight");
    tick(s,16);check(r.phase==LumpPhase::Hiding&&r.frame==0&&!r.intangible,"Spit20 then visible Hide");
    const auto hp=e.hp;damage(s,id);check(near(e.hp,hp-7),"Hide remains vulnerable");
    tick(s,15);check(!r.intangible&&r.phase==LumpPhase::Hiding,"Hide stays tangible until16");
    tick(s);check(r.intangible&&r.burrows==1,"Hide16 disables body collision");
    const auto hiddenHp=e.hp;damage(s,id);check(near(e.hp,hiddenHp),"buried body rejects damage");
    check(r.cooldown==27,"cooldown continues through attack and hiding");
    std::cout<<"FIRING hp=96 check=7 cooldown=63 Spit=20 Shoot=4 Hide=16 actual_shots=3 flight=1 vulnerability=1\n";
}
void sequence() {
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=*e.lump;
    r.initialized=true;r.phase=LumpPhase::Hidden;r.intangible=true;r.cooldown=0;e.state=EnemyState::Buried;
    acquire(s,id);check(!r.intangible,"expired cooldown can interrupt hidden phase");
    tick(s,4);check(r.volleys==1,"interrupted burrow fires after native Shoot4");
    auto far=fixture();far.player.position={65,.85f,65};const auto f=spawn(far);bool hidden=false,visibleAppear=false,ready=false;
    for(int n=0;n<600;++n) {
        tick(far);auto &a=*far.findEnemy(f);auto &b=*a.lump;
        hidden|=b.burrows>0;
        if(b.phase==LumpPhase::Appearing&&b.frame>0){visibleAppear=true;check(!b.intangible,"Appear restores collision on next source update");}
        if(visibleAppear&&b.phase==LumpPhase::Ready){ready=true;break;}
    }
    check(hidden&&visibleAppear&&ready,"out-of-range random hide and emerge cycle");
    check(far.stats.projectiles==0,"far target does not create shots");
    auto blocked=fixture();blocked.arena.walls.push_back({{-79,0,5},{79,20,6}});const auto b=spawn(blocked);tick(blocked,60);
    check(blocked.findEnemy(b)->lump->volleys==0,"wall blocks source acquisition");
    std::cout<<"SEQUENCE phase_independent_acquisition=1 random_hide=1 random_emerge=1 appear_collision=1 walls=1\n";
}
void relocation() {
    auto s=fixture();s.player.position={60,.85f,60};s.arena.walls.push_back({{-50,0,-50},{50,20,-20}});
    const auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=*e.lump;
    r.initialized=true;r.phase=LumpPhase::Hidden;r.intangible=true;r.cooldown=10000;e.state=EnemyState::Buried;
    bool moved=false;
    for(int n=0;n<90;++n) {
        // Keep observing underground search separately from emergence lottery.
        r.phase=LumpPhase::Hidden;r.intangible=true;e.state=EnemyState::Buried;const auto before=e.position;tick(s);
        check(!s.arena.blocked(r.anchor,e.radius),"chosen anchor rejects canyon solid terrain");
        check(r.anchor.x>=-79.4f&&r.anchor.x<=79.4f&&r.anchor.z>=-79.4f&&r.anchor.z<=79.4f,"destination footprint within room");
        if(r.phase==LumpPhase::Hidden)check(distance(e.position,add(before,mul(horizontal(sub(r.anchor,before)),.7f)))<.01f,"underground displacement is .7 times anchor delta");
        moved|=r.relocations>0;
    }
    check(moved,"large legal room has actual relocation witnesses");
    auto small=fixture();small.arena.bounds={{-4,-1,-4},{4,20,4}};
    for(auto &room:small.arena.rooms){room.bounds=small.arena.bounds;room.floors={{{-4,-.4f,-4},{4,0,4}}};}
    small.arena.rebuildWalls();small.player.position={3,.85f,3};const auto x=spawn(small);auto &a=*small.findEnemy(x);auto &b=*a.lump;
    b.initialized=true;b.cooldown=10000;b.phase=LumpPhase::Hidden;
    for(int n=0;n<80;++n){b.phase=LumpPhase::Hidden;b.intangible=true;a.state=EnemyState::Buried;tick(small);}
    check(b.relocations==0&&distance(a.position,{0,.85f,0})<.001f,"no invented short relocation in room failing source200-distance rule");
    std::cout<<"RELOCATION actual_move=1 native_anchor_retention=1 solids=1 bounds=1 source_distance_fallback=1\n";
}
void capacityAndCompletion() {
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=*e.lump;
    acquire(s,id);s.limits.projectiles=2;tick(s,4);
    check(r.pendingShots.size()==3&&s.projectiles.empty()&&r.frame==4,"whole volley retained at Shoot under capacity");
    const auto velocity=mul(r.pendingShots.front().direction,r.pendingShots.front().speed);s.player.position={-12,.85f,-12};tick(s,8);
    check(r.pendingShots.size()==3&&r.frame==4,"backpressure neither loses nor duplicates shots");
    s.limits.projectiles=3;tick(s);check(s.projectiles.size()==3&&r.volleys==1&&distance(s.projectiles.front().velocity,velocity)<.001f,"retained volley keeps emission-time aim");
    auto finish=fixture();const auto k=spawn(finish);finish.debugScenario=false;auto &a=*finish.findEnemy(k);
    a.lump->initialized=true;a.lump->phase=LumpPhase::Hidden;a.lump->intangible=true;a.lump->cooldown=500;a.state=EnemyState::Buried;tick(finish);
    check(!finish.roomClear&&finish.roomThreats()==1,"buried live enemy still gates completion");
    damage(finish,k,1000,true);tick(finish,3);check(finish.roomClear&&finish.enemies.empty()&&finish.stats.kills==1,"execution removes buried body and clears once without offspring");
    auto contact=fixture();const auto c=spawn(contact);contact.godMode=false;contact.player.position=contact.findEnemy(c)->position;tick(contact);
    check(near(contact.player.hp,87.5f),"contact1 becomes10 then shared1.25 damage");
    std::cout<<"CAPACITY whole_volley=1 frozen_aim=1 completion=1 contact=12.5\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-lump-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"lumps.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"lumps.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("7 63 20 4","7 70 20 4");check(changed->lump(monsterId(56))->shot.cooldownFrames==70&&defaultMechanics()->lump(monsterId(56))->shot.cooldownFrames==63,"immutable external configuration");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".1 .7 10",".1 1 10"},{"10 50 20","10 0 20"},{"7 63 20 4","7 63 20 20"},{"400 200 40","400 500 40"},{"Burrow None Blob","Burrow Spread Blob"},{"lump 56.0.0","lump 9999.0.0"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid/incompatible Lump config rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=6\n";
}
void placement() {
    bool found=false;int floors=0;
    for(uint64_t seed=0;seed<32&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!found;++floor) {
            if(plan.profileOnFloor(floor).band<3)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++floors;
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.lump) {
                check(s.arena.profile.band==3&&!s.arena.blocked(e.position,e.radius),"source Womb habitat and grounded spawn");
                std::cout<<"NATURAL_LUMP seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';found=true;
            }
        }
    }
    check(found,"actual seeded ordinary population contains Lump");std::cout<<"PLACEMENT floors="<<floors<<" band=3\n";
}
}
int main(){std::cout<<std::unitbuf;try{firing();sequence();relocation();capacityAndCompletion();configuration();placement();std::cout<<"PASS Lump\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
