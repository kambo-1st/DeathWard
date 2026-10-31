#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.002f;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,8,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId ready(Simulation &s){const auto id=s.spawnMonster(monsterId(12),{0,.85f,0});s.findEnemy(id)->cooldown=0;return id;}
int acquire(Simulation &s,EntityId id){int n=0;while(n<14&&s.findEnemy(id)->state!=EnemyState::Windup){tick(s);++n;}check(s.findEnemy(id)->state==EnemyState::Windup,"staggered acquisition within7source frames");return n;}
void timingAndAim() {
    auto s=fixture();const auto id=ready(s);check(near(s.findEnemy(id)->hp,32),"source health10x3.2");
    acquire(s,id);const auto began=s.stats.duration;
    tick(s,7);check(s.projectiles.empty(),"not beforeShoot4");
    s.player.position={30,.85f,0};tick(s);
    check(s.projectiles.size()==1&&near(s.projectiles[0].velocity.x,21)&&near(s.projectiles[0].velocity.z,0),"current-target shot even after leaving acquisition range");
    tick(s,31);check(s.findEnemy(id)->state==EnemyState::Windup,"full20-frame recovery remains");tick(s);
    check(s.findEnemy(id)->state==EnemyState::Ready&&near(s.findEnemy(id)->position.x,0)&&near(s.findEnemy(id)->position.z,0),"stationary recovery ends at20source frames");
    s.player.position={0,.85f,10};while(s.stats.projectiles<2&&s.stats.duration-began<2)tick(s);
    check(s.stats.projectiles==2&&std::abs(s.stats.duration-began-32./30)<.0001,"cooldown28 starts at acquisition, not shot or recovery");
    auto tuned=fixture();tuned.arena.profile.cooldownScale=.2f;const auto other=ready(tuned);acquire(tuned,other);const auto start=tuned.stats.duration;
    while(tuned.stats.projectiles<2&&tuned.stats.duration-start<2)tick(tuned);
    check(tuned.stats.projectiles==2&&std::abs(tuned.stats.duration-start-32./30)<.0001,"floor multipliers do not alter source cadence");
}
void rangeCoverAndDamage() {
    auto s=fixture();const auto id=ready(s);s.player.position={0,.85f,20};tick(s,100);
    check(s.stats.projectiles==0,"strict200native-unit range excludes boundary");s.player.position.z=19.9f;
    s.arena.walls.push_back({{-2,-1,5},{2,5,5.1f}});tick(s,100);check(s.stats.projectiles==0,"cover prevents acquisition");
    s.arena.walls.clear();acquire(s,id);s.arena.walls.push_back({{-2,-1,1},{2,5,1.1f}});tick(s,14);
    check(s.stats.projectiles==1&&s.projectiles.empty(),"committed shot hits new intervening cover, no remote damage");
    auto damage=fixture();damage.godMode=false;const auto d=ready(damage);acquire(damage,d);tick(damage,40);
    check(near(damage.player.hp,87.5f),"existing hostile damage conversion occurs once");
    auto contact=fixture();contact.godMode=false;const auto c=ready(contact);contact.player.position=contact.findEnemy(c)->position;tick(contact);
    check(near(contact.player.hp,87.5f),"grounded head has contact damage");
}
void interruptionAndPressure() {
    auto dead=fixture();auto id=ready(dead);acquire(dead,id);Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=32;
    dead.queueRoot(hit);dead.drainEvents();tick(dead,80);check(dead.stats.projectiles==0&&dead.roomThreats()==0&&dead.stats.kills==1,"death cancels committed cast, counts once");
    auto stun=fixture();id=ready(stun);acquire(stun,id);stun.findEnemy(id)->state=EnemyState::Stunned;stun.findEnemy(id)->stateTime=.5f;tick(stun,30);
    check(stun.stats.projectiles==0&&stun.findEnemy(id)->headShooter->attackFrame==-1,"stun cancels queued windup");
    for(bool events:{false,true}) {
        auto pressure=fixture();id=ready(pressure);acquire(pressure,id);
        if(events)pressure.limits.queuedEvents=0;else pressure.limits.projectiles=0;
        tick(pressure,20);check(pressure.stats.projectiles==0&&pressure.findEnemy(id)->headShooter->attackFrame==4,"shot waits at event under capacity pressure");
        pressure.limits.queuedEvents=256;pressure.limits.projectiles=512;tick(pressure,2);
        check(pressure.stats.projectiles==1,"capacity recovery admits exactly one shot");
    }
}
void flightAndPassiveMotion() {
    auto s=fixture();const auto id=ready(s);acquire(s,id);
    while(s.projectiles.empty())tick(s);
    const auto shotId=s.projectiles.front().id;
    s.player.position={30,.85f,30};
    // Independent recurrence in native downward height units. The first
    // observed projectile has already advanced one simulation half-frame.
    float height=-s.projectiles.front().position.y/.03f;
    float falling=-s.projectiles.front().velocity.y/.9f;
    for(int n=0;n<12;++n) {
        falling=.9f*falling+.1f+.1f;height+=falling;
        s.step({},1.f/30);
        const auto it=std::find_if(s.projectiles.begin(),s.projectiles.end(),[&](const auto &p){return p.id==shotId;});
        check(it!=s.projectiles.end()&&near(it->position.y,-height*.03f)&&near(it->velocity.y,-falling*.9f),
              "Horf follows mode0 plus common-base vertical recurrence, not flat flight");
    }
    for(float range:{4.f,10.f,19.f}) {
        auto damage=fixture();damage.godMode=false;damage.player.position.z=range;
        const auto d=ready(damage);acquire(damage,d);
        for(int n=0;n<100&&damage.player.hp==StartingHealth;++n)tick(damage);
        check(near(damage.player.hp,StartingHealth-12.5f),"compressed aimed arc hits the standing player throughout acquisition range");
    }
    Vector3 final{};
    for(int hz:{30,60,120}) {
        auto body=fixture();body.player.position={30,.85f,30};const auto b=ready(body);
        body.findEnemy(b)->velocity={9,0,0};
        for(int n=0;n<hz/3;++n)body.step({},1.f/hz);
        const auto *e=body.findEnemy(b);
        const float speed=9*std::pow(.7f,10),travel=9.f/30*.7f*(1-std::pow(.7f,10))/.3f;
        check(near(e->velocity.x,speed)&&near(e->position.x,travel),"passive Horf impulse follows analytic .7 friction without pursuit");
        if(hz==30)final=e->position;else check(distance(final,e->position)<.002f,"Horf passive motion agrees at30/60/120Hz");
    }
    auto cover=fixture();const auto c=ready(cover);cover.findEnemy(c)->velocity={30,0,0};
    cover.arena.floorProps.push_back({StoryPropKind::Crate,{{1,-.1f,-4},{2,3,4}}});cover.arena.rebuildWalls();
    tick(cover,20);check(!cover.arena.blocked(cover.findEnemy(c)->position,cover.findEnemy(c)->radius)&&cover.findEnemy(c)->position.x<1,
                       "external impulse cannot push Horf through solid cover");
    std::cout<<"FLIGHT native_recurrence=12 standing_hits=3 passive_partitions=3 physical_cover=1\n";
}
void configAndPlacement() {
    const auto path=std::filesystem::temp_directory_path()/("dw-horf-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(path);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());
    const auto file=path/"horf.mechanics";std::ifstream in(file);const std::string original((std::istreambuf_iterator<char>(in)),{});
    for(const auto &replace:{"head_shooter 12.0.0 0 28 20 4 20 21 10 5","head_shooter 12.0.0 7 28 20 20 20 21 10 5","head_shooter 9999.0.0 7 28 20 4 20 21 10 5"}) {
        auto s=original;const auto begin=s.find("head_shooter 12.0.0");const auto end=s.find('\n',begin);s.replace(begin,end-begin,replace);std::ofstream(file)<<s;
        bool rejected=false;try{MechanicsLibrary::load(path);}catch(...){rejected=true;}check(rejected,"invalid stationary shooter rejected");
    }
    std::ofstream(file)<<original;const auto before=MechanicsLibrary::load(path);auto changed=original;const auto at=changed.find("20 21 10 5");changed.replace(at,10,"20 18 10 5");std::ofstream(file)<<changed;
    const auto after=MechanicsLibrary::load(path);check(near(before->headShooter(monsterId(12))->speed,21)&&near(after->headShooter(monsterId(12))->speed,18)&&before->fingerprint()!=after->fingerprint(),"new snapshot loads values while old one remains unchanged");
    for(const auto &[from,to]:std::vector<std::pair<std::string,std::string>>{
        {"head_shooter_body 12.0.0 .7","head_shooter_body 12.0.0 1"},
        {"head_shooter_body 12.0.0 .7","head_shooter_body 12.0.0 .7\nhead_shooter_body 12.0.0 .7"},
        {"head_shooter_body 12.0.0 .7","head_shooter_body 11.0.0 .7"},
        {".69 2.7 5.4 .9 .22",".69 2.7 -1 .9 .22"},
        {".69 2.7 5.4 .9 .22",".69 2.7 5.4 0 .22"},
        {"head_shooter_flight 12.0.0 .69 2.7 5.4 .9 .22","head_shooter_flight 12.0.0 .69 2.7 5.4 .9 .22\nhead_shooter_flight 12.0.0 .69 2.7 5.4 .9 .22"}}) {
        auto text=original;const auto at=text.find(from);check(at!=text.npos,"flight reload fixture exists");
        text.replace(at,from.size(),to);std::ofstream(file)<<text;
        bool rejected=false;try{MechanicsLibrary::load(path);}catch(const std::exception&){rejected=true;}
        check(rejected,"invalid or duplicate stationary shooter physics rejected");
    }
    std::filesystem::remove_all(path);
    bool found=false;for(uint64_t seed=0;seed<20&&!found;++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        for(int room=1;room<s.finalRoom()&&!found;++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(12)) {
            check(near(e.hp,32)&&s.arena.profile.band==0,"actual starting-stage Horf has source health");
            std::cout<<"NATURAL_HORF seed="<<seed<<" floor=0 room="<<room<<" hp="<<e.hp<<'\n';found=true;
        }
    }
    check(found,"actual regular seeded Horf exists");
    for(int band=1;band<4;++band)for(int pattern=0;pattern<4;++pattern)for(const auto &e:defaultMechanics()->encounterPool(band,EncounterPattern(pattern)).specialists)
        check(e.monster!=monsterId(12),"ordinary Horf restricted toBasement analogue");
}
}
int main(){try{timingAndAim();rangeCoverAndDamage();interruptionAndPressure();flightAndPassiveMotion();configAndPlacement();std::cout<<"PASS Horf: source cast/cadence/current aim, strict range/cover, pressure, health, flight/passive motion, config and natural stage\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
