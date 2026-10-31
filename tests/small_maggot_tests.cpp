#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *message){if(!b)throw std::runtime_error(message);}
bool near(float a,float b,float tolerance=.003f){return std::abs(a-b)<tolerance;}
Simulation fixture(uint32_t seed=1866,std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,0};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(853),at);}
void damage(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;s.queueRoot(e);s.drainEvents();
}
void sourceTimingAndPhysics() {
    auto library=defaultMechanics();
    for(int stage=1;stage<=12;++stage)check(near(library->monsterHealth(monsterId(853),stage),32),"source10HP, no stage increment, conversion3.2");
    int minimum=1000,maximum=0;
    for(unsigned seed=0;seed<96;++seed) {
        auto s=fixture(seed);auto id=spawn(s);tick(s);auto *e=s.findEnemy(id);
        check(near(e->hp,32)&&e->smallMaggot.has_value(),"spawn consumes source HP and dedicated controller");
        const int delay=e->smallMaggot->cooldown;minimum=std::min(minimum,delay);maximum=std::max(maximum,delay);
        check(delay>=10&&delay<=39&&e->smallMaggot->turns==0&&length(e->velocity)==0,"native state0 seeds variable timer without a chase impulse");
        tick(s,delay-1);e=s.findEnemy(id);check(e->smallMaggot->turns==0&&length(e->velocity)<.001f,"no impulse before first timer expires");
        tick(s);e=s.findEnemy(id);const auto &r=*e->smallMaggot;
        check(r.turns==1&&r.force>=.15f&&r.force<=.45f&&std::abs(r.curve)<=2*Pi/180+.00001f,"unaware crawl samples source force and curvature");
        check(near(length(e->velocity),r.force*.8f*3),"first force is applied before native.8friction and converted to world velocity");
        check(r.cooldown>=10&&r.cooldown<=39&&!r.alert,"turn timer remains10..39 without remote player awareness");
    }
    check(minimum<15&&maximum>34,"initial delay is actually variable across seeds");
    auto s=fixture();auto id=spawn(s);tick(s);auto *e=s.findEnemy(id);
    e->smallMaggot->heading={1,0,0};e->smallMaggot->force=.3f;e->smallMaggot->curve=0;e->smallMaggot->cooldown=60;e->velocity={};
    tick(s,30);e=s.findEnemy(id);
    const float speed=3.6f*(1-std::pow(.8f,30));
    const float distance=3.6f/30*(30-.8f*(1-std::pow(.8f,30))/.2f);
    check(near(e->velocity.x,speed,.005f)&&near(e->position.x,distance,.005f),"constant-force interval matches independent analytic acceleration and displacement");
    std::cout<<"PHYSICS source_hp=32 initial_delay="<<minimum<<".."<<maximum<<" first_force=1 analytic30=1\n";
}
void awarenessAndCover() {
    auto s=fixture();auto id=spawn(s);tick(s);s.player.position={4,.85f,0};
    s.arena.floorProps.push_back({StoryPropKind::Crate,{{1,-.1f,-8},{2,3,8}}});s.arena.rebuildWalls();
    bool alerted=false;
    for(int n=0;n<300&&!alerted;++n){tick(s);alerted=s.findEnemy(id)->smallMaggot->alert;}
    check(alerted,"nearby awareness is not gated by cover");
    auto *e=s.findEnemy(id);e->smallMaggot->cooldown=1;e->smallMaggot->alert=false;
    damage(s,id,1);tick(s);e=s.findEnemy(id);
    check(e->smallMaggot->alert&&e->smallMaggot->force<=.45f,"damage alerts but blocked sight does not double force");
    s.arena.floorProps.clear();s.arena.rebuildWalls();e->smallMaggot->alert=false;e->smallMaggot->cooldown=1;
    const auto expected=unit(horizontal(sub(s.player.position,e->position)));tick(s);e=s.findEnemy(id);
    check(e->smallMaggot->alert&&e->smallMaggot->force>=.3f&&e->smallMaggot->force<=.9f&&dot(e->smallMaggot->heading,expected)>.999f,
          "damaged body retargets along clear sight with double force");
    auto group=fixture();auto a=spawn(group),b=spawn(group,{0,.85f,3});tick(group);damage(group,a,1);
    bool shared=false;for(int i=0;i<300&&!shared;++i){tick(group);shared=group.findEnemy(b)->smallMaggot->alert;}
    check(shared,"alert spreads from nearby Small Maggot even with remote player");
    auto rock=fixture();auto m=spawn(rock);tick(rock);rock.player.position={4,.85f,0};damage(rock,m,1);
    rock.arena.floorProps.push_back({StoryPropKind::Crate,{{1,-.1f,-4},{2,3,4}}});rock.arena.rebuildWalls();
    for(int n=0;n<240;++n){tick(rock);check(!rock.arena.blocked(rock.findEnemy(m)->position,.3f),"crawling body never crosses solid cover");}
    e=rock.findEnemy(m);e->smallMaggot->blocked=true;e->smallMaggot->cooldown=30;const auto turns=e->smallMaggot->turns;tick(rock);
    check(rock.findEnemy(m)->smallMaggot->turns==turns+1,"actual collision forces a new direction on next source update");
    std::cout<<"AWARENESS cover_independent=1 damage=1 spread=1 clear_sight_force=1 ground_collision=1 collision_retarget=1\n";
}
void integration() {
    auto a=fixture(),b=fixture();auto ia=spawn(a),ib=spawn(b);
    tick(a,120);tick(b,480,1.f/120);
    check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.02f&&a.findEnemy(ia)->smallMaggot->ticks==b.findEnemy(ib)->smallMaggot->ticks&&
          a.findEnemy(ia)->smallMaggot->turns==b.findEnemy(ib)->smallMaggot->turns,"30/120Hz partitions preserve controller timing and movement");
    check(a.stats.projectiles==0&&a.hazards.empty(),"Small Maggot has no invented shots or damaging trail");
    auto *e=a.findEnemy(ia);const auto cooldown=e->smallMaggot->cooldown;e->state=EnemyState::Stunned;e->stateTime=.1f;const auto at=e->position;tick(a,3);
    check(distance(a.findEnemy(ia)->position,at)<.001f&&a.findEnemy(ia)->smallMaggot->cooldown==cooldown,"stun pauses crawl state");
    const auto turns=e->smallMaggot->turns;a.enterRoom(1);tick(a,3);a.enterRoom(0);e=a.findEnemy(ia);
    check(e&&e->smallMaggot->turns==turns,"room re-entry preserves the independent controller");
    damage(a,ia,2,DamageKind::Flame);damage(a,ia,3,DamageKind::Burning);check(near(a.findEnemy(ia)->hp,27),"Small Maggot remains fire vulnerable");
    auto contact=fixture();contact.godMode=false;spawn(contact);contact.player.position={.7f,.85f,0};tick(contact);
    check(near(contact.player.hp,StartingHealth-10*EnemyDamageMultiplier),"contact uses source base10 and unchanged global multiplier");
    auto clear=fixture();auto parent=clear.spawnMonster(monsterId(10,3,3),{-8,.85f,0});auto child=spawn(clear);
    clear.findEnemy(child)->summoner=parent;clear.debugScenario=false;clear.rooms[0].cleared=false;
    damage(clear,parent,1000);tick(clear);check(!clear.roomClear&&clear.roomThreats()==1,"owned maggot survives parent and retains room threat");
    damage(clear,child,1000);tick(clear);check(clear.roomClear&&clear.stats.kills==2,"final child death pays once and completes room");
    std::cout<<"INTEGRATION partition30_120=1 no_shots=1 stun=1 reentry=1 fire=1 contact=1 ownership_completion=1\n";
}
void externalProfiles() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-small-maggot-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"small_maggots.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto t=original;auto at=t.find(from);check(at!=t.npos,"reload fixture exists");t.replace(at,from.size(),to);std::ofstream(dir/"small_maggots.mechanics")<<t;return MechanicsLibrary::load(dir);};
    auto changed=edit(".1 .8 .15 .45",".1 .8 .1 .1");auto s=fixture(1866,changed);auto id=spawn(s);tick(s,45);
    check(near(s.findEnemy(id)->smallMaggot->force,.1f)&&near(defaultMechanics()->smallMaggot(monsterId(853))->forceMin,.15f),"reload affects new controller and preserves old immutable content");
    const std::vector<std::pair<std::string,std::string>> invalid={
        {".1 .8 .15 .45","0 .8 .15 .45"},{".1 .8 .15 .45",".1 1 .15 .45"},{".1 .8 .15 .45",".1 .8 .5 .45"},
        {"2 2 6 90 80",".5 2 6 90 80"},{"2 2 6 90 80","2 2 0 90 80"},{"10 39 10 39","40 39 10 39"},
        {"4 4 25 10 13","0 4 25 10 13"},{"4 4 25 10 13","4 0 25 10 13"},{"4 4 25 10 13","4 4 0 10 13"},
        {"4 4 25 10 13","4 4 25 0 13"},{"Chase None Worm","Wander None Worm"},{"Chase None Worm","Chase Shot Worm"}};
    for(const auto &[from,to]:invalid){bool rejected=false;try{edit(from,to);}catch(const std::exception&){rejected=true;}check(rejected,"malformed Small Maggot contract rejected");}
    std::cout<<"EXTERNAL runtime_reload=1 immutable=1 invalid_contracts="<<invalid.size()<<'\n';
}
void natural() {
    bool found=false;
    for(unsigned seed=0;seed<128&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        int floor=0;while(plan.profileOnFloor(floor).band<3)++floor;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=0;room<s.arena.roomCount()&&!found;++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(853)) {
            check(e.smallMaggot&&s.arena.profile.band==3&&!s.arena.blocked(e.position,e.radius),"naturally seeded Small Maggot has correct band, controller and clear footprint");
            std::cout<<"NATURAL_SMALL_MAGGOT seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';found=true;break;
        }
    }
    check(found,"Small Maggot reachable through actual late seeded composition");
}
}
int main(int argc,char**argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--natural"){natural();return 0;}sourceTimingAndPhysics();awarenessAndCover();integration();externalProfiles();std::cout<<"Small Maggot checks passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
