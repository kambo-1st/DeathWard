#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *m){if(!ok)throw std::runtime_error(m);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-crackle-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(std::string from,std::string to){const auto p=path/"gurgle.mechanics";std::ifstream in(p);std::string s((std::istreambuf_iterator<char>(in)),{});auto at=s.find(from);check(at!=std::string::npos,"fixture text exists");s.replace(at,from.size(),to);std::ofstream(p)<<s;}
    auto fixed(){replace("lob_walker 87.1.0 60 ","lob_walker 87.1.0 1 ");replace("\"Crackle\" Chase Lob Walker 128 3.6 ","\"Crackle\" Chase Lob Walker 128 0 ");replace("lob_projectile 87.1.0 11.55 5.775 ","lob_projectile 87.1.0 11.55 0 ");return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,12,50}};s.arena.rooms.resize(2);
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-50,-.4f,-50},{50,0,50}}};}
    s.rooms.assign(2,{});s.room=0;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.moneyPickups.clear();s.stats={};
    s.godMode=true;s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s,MonsterId id=monsterId(87,1),Vector3 at={0,.85f,0}){const auto actor=s.spawnMonster(id,at);check(actor!=0,"actor exists");s.findEnemy(actor)->cooldown=0;return actor;}
void stun(Simulation &s,EntityId id){s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;}
void impact(Simulation &s,EntityId source) {
    Event shot;shot.hostile=true;shot.context.sourceEntity=source;shot.position=shot.origin={0,.36f,0};shot.direction={0,-1,0};shot.speed=1;
    shot.projectileKind=ProjectileKind::Ember;shot.projectileGravity=36.9f;shot.projectileFlightRetention=.9f;shot.projectileRadius=.352f;
    shot.fireWave=s.content->lobWalker(monsterId(87,1))->fireWave;s.queueRoot(shot);s.drainEvents();
}
void attacks() {
    Pack p;auto lib=p.fixed();auto s=fixture(lib);auto id=spawn(s);tick(s,2);check(s.findEnemy(id)->state==EnemyState::Windup,"source acquisition");
    tick(s,9);check(s.stats.projectiles==0,"Shoot not early");s.player.position={8,.85f,0};tick(s);
    check(s.projectiles.size()==1&&s.fireWaves.empty()&&s.hazards.empty(),"travelling shot precedes landing effect");
    auto &shot=s.projectiles.front();check(shot.kind==ProjectileKind::Ember&&shot.blastRadius==0&&shot.fireWave.jetStepFrames==2,"fire-wave payload replaces explosion");
    check(near(shot.radius,.352f)&&shot.velocity.x>11.54f&&shot.velocity.y>0,"current target and shared damped launch");
    tick(s,53);check(s.findEnemy(id)->state==EnemyState::Windup,"Crackle recovery longer than Gurgle");tick(s);check(s.findEnemy(id)->state==EnemyState::Ready,"recovery ends at32source frames");
    auto dead=fixture(lib);id=spawn(dead);tick(dead,6);Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=129;dead.queueRoot(hit);dead.drainEvents();tick(dead,100);
    check(dead.stats.projectiles==0&&dead.stats.kills==1&&dead.roomThreats()==0,"death cancels windup and Crackle never morphs");
}
void propagation() {
    auto s=fixture();s.player.position={45,.85f,45};auto id=spawn(s);stun(s,id);impact(s,id);
    tick(s,3);check(s.fireWaves.size()==1&&s.fireWaves[0].jets.empty(),"generator waits until first even source frame");
    tick(s);const auto &first=s.fireWaves[0];check(first.jets.size()==4&&first.jetStep==1,"first four separate cardinal jets");
    for(const auto &j:first.jets)check(near(planarDistance(j.position,{}),3)&&near(j.scale,.94f)&&j.pulses==0,"source spacing, scale and pre-pulse warning");
    tick(s,52);check(s.fireWaves[0].jetStep==14,"finite generation through sourceframe28");
    for(const auto &r:s.fireWaves[0].rays)check(r.stopped&&near(r.length,42),"four bounded42-unit rays in open room");
    check(std::any_of(s.fireWaves[0].jets.begin(),s.fireWaves[0].jets.end(),[](const auto &j){return near(j.scale,.16f);}),"last jet visual scale");
    tick(s,70);check(s.fireWaves.empty()&&s.stats.explosions==0,"jets expire without explosions or permanent fire");
}
void pulses() {
    auto s=fixture();const auto source=spawn(s);stun(s,source);
    const auto immune=spawn(s,monsterId(87),{-3,.85f,0});stun(s,immune);
    const auto victim=spawn(s,monsterId(10),{3,.85f,0});stun(s,victim);s.findEnemy(victim)->hp=s.findEnemy(victim)->maxHp=200;
    const auto splasher=spawn(s,monsterId(238),{0,.85f,3});stun(s,splasher);s.findEnemy(splasher)->hp=s.findEnemy(splasher)->maxHp=200;
    s.godMode=false;s.player.position={3,.85f,0};impact(s,source);
    std::erase_if(s.enemies,[&](const auto &e){return e.id==source;});
    tick(s,7);check(near(s.player.hp,100)&&near(s.findEnemy(victim)->hp,200),"jets do not damage before age2");tick(s);
    check(near(s.player.hp,87.5f)&&near(s.findEnemy(victim)->hp,168)&&near(s.findEnemy(splasher)->hp,168)&&near(s.findEnemy(immune)->hp,128),"first pulse: player conversion, NPC damage, Splasher vulnerability, Gurgle immunity after source removal");
    tick(s,3);s.player.hurt=0;tick(s);check(near(s.player.hp,75)&&near(s.findEnemy(victim)->hp,168),"second pulse atage4 and localNPC contact cooldown");
    s.player.position={0,.85f,0};tick(s,5);s.player.position={3,.85f,0};s.player.hurt=0;tick(s);
    check(near(s.player.hp,75),"fading jet after age4 is visual only");
}
void geometryAndPressure() {
    auto wall=fixture();auto id=spawn(wall);stun(wall,id);wall.player.position={6,.85f,0};wall.godMode=false;
    wall.arena.walls.push_back({{2,-1,-2},{2.1f,6,2}});impact(wall,id);tick(wall,15);
    check(near(wall.player.hp,100)&&wall.fireWaves[0].rays[0].stopped&&near(wall.fireWaves[0].rays[0].length,0),"thin cover stops propagation without jumping to other side");
    auto pit=fixture();id=spawn(pit);stun(pit,id);pit.player.position={6,.85f,0};pit.godMode=false;pit.arena.rails.emplace();pit.arena.rails->pits.push_back({{2,-3,-2},{4,0,2}});
    impact(pit,id);tick(pit,12);check(pit.player.hp<100&&pit.fireWaves[0].rays[0].length>=9,"source jet generators cross pits, unlike continuous boss fire mode");
    auto pressure=fixture();id=spawn(pressure);stun(pressure,id);pressure.limits.fireWaves=0;impact(pressure,id);tick(pressure,5);
    check(pressure.fireWaves.empty()&&pressure.projectiles.size()==1&&pressure.projectiles[0].impactPending,"full burst capacity retains carrier");
    pressure.limits.fireWaves=32;tick(pressure);check(pressure.projectiles.empty()&&pressure.fireWaves.size()==1,"one burst after capacity recovery");
    auto pulse=fixture();id=spawn(pulse);stun(pulse,id);const auto target=spawn(pulse,monsterId(10),{3,.85f,0});stun(pulse,target);pulse.findEnemy(target)->hp=pulse.findEnemy(target)->maxHp=200;
    pulse.player.position={3,.85f,0};pulse.godMode=false;impact(pulse,id);tick(pulse,4);pulse.limits.queuedEvents=0;tick(pulse,4);
    check(near(pulse.player.hp,100)&&near(pulse.findEnemy(target)->hp,200)&&pulse.fireWaves[0].jets[0].pulses==0,"full event queue retains whole damaging pulse");
    pulse.limits.queuedEvents=256;tick(pulse);check(near(pulse.player.hp,87.5f)&&near(pulse.findEnemy(target)->hp,168),"pulse resumes once without partial/repeated player hit");
    const auto age=pulse.fireWaves[0].age;pulse.room=1;tick(pulse,15);pulse.room=0;check(near(pulse.fireWaves[0].age,age),"inactive room pauses jets");
}
void configAndPlacement() {
    for(auto [from,to]:std::array<std::pair<std::string,std::string>,4>{{{"2 3 14 20 2 4 2 32 10 .06","2 3 14 20 2 4 2 32 10 .1"},{"2 3 14 20 2 4 2 32 10 .06","0 3 14 20 2 4 2 32 10 .06"},{"2 3 14 20 2 4 2 32 10 .06","2 3 14 20 4 2 2 32 10 .06"},{"lob_fire_wave 87.1.0 ","lob_fire_wave 9999.0.0 "}}}) {
        Pack p;p.replace(from,to);bool rejected=false;try{MechanicsLibrary::load(p.path);}catch(...){rejected=true;}check(rejected,"invalid fire-wave data rejected");
    }
    bool found=false;
    // Ordinary specialist additions change weighted draws. Keep a bounded seed
    // search large enough to witness this rare Standard-band-1 encounter.
    for(uint64_t seed=0;seed<256&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!found;++floor) {
            if(plan.profileOnFloor(floor).band!=1)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(87,1)) {
                found=true;check(s.arena.profile.variant==FloorVariant::Standard&&near(e.hp,128)&&e.lob.has_value(),"natural Ashpit analogue actor");
                std::cout<<"NATURAL_CRACKLE seed="<<seed<<" floor="<<floor<<" room="<<room<<" hp="<<e.hp<<'\n';
            }
        }
    }
    check(found,"Crackle reachable through actual ordinary floor generation");
    for(int band:{0,2,3})for(int pattern=0;pattern<4;++pattern)for(const auto &e:defaultMechanics()->encounterPool(band,EncounterPattern(pattern)).specialists)
        check(e.monster!=monsterId(87,1),"Crackle limited to source-stage analogue");
}
}
int main(){try{attacks();propagation();pulses();geometryAndPressure();configAndPlacement();std::cout<<"PASS Crackle: physical lob,32-frame cycle, discrete cardinal jets, pulses, immunity, pit/cover, retained pressure, seeded stage\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
