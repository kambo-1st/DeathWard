#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *message){if(!b)throw std::runtime_error(message);}
bool near(float a,float b,float tolerance=.002f){return std::abs(a-b)<tolerance;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,0};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int variant=1){return s.spawnMonster(monsterId(10,variant),{0,.85f,0});}
void hit(Simulation &s,EntityId id,float damage,DamageKind kind=DamageKind::Physical) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.damageKind=kind;s.queueRoot(e);s.drainEvents();
}
void healthAndAcceleration() {
    const auto library=defaultMechanics();
    for(int v:{0,1,2}) {
        const float hp=v==2?28.8f:32.f;
        for(int stage=1;stage<=12;++stage)check(near(library->monsterHealth(monsterId(10,v),stage),hp),"source base HP10/10/9, no stage HP, conversion3.2");
        auto s=fixture();auto id=spawn(s,v);check(near(s.findEnemy(id)->hp,hp),"real spawn consumes source HP");
        tick(s);auto *e=s.findEnemy(id);
        const float force=v==0?.6f:v==1?.498f:.5478f;
        check(near(e->velocity.x,force*6)&&near(e->velocity.z,0),"first tick already moves using source impulse and world conversion");
        check(e->gaper->walkFrame==0&&e->gaper->ticks==1,"walk selector sees initial zero momentum");
        tick(s);e=s.findEnemy(id);
        check(near(e->velocity.x,force*6*.7f+(v==0?.72f:force)*6),"old momentum retained at.7 before new source impulse");
        check(e->gaper->walkFrame==1,"walking animation advances at30FPS, not at .1 speed");
        if(v==1) {
            tick(s,28);e=s.findEnemy(id);
            // Geometric-series closed form, independent of the runtime loop.
            const float expectedSpeed=9.96f*(1-std::pow(.7f,30));
            const float expectedDistance=9.96f/30*(30-.7f*(1-std::pow(.7f,30))/.3f);
            check(near(e->velocity.x,expectedSpeed,.004f)&&near(e->position.x,expectedDistance,.004f),"thirty source ticks match analytic friction-driven motion");
            check(e->gaper->walkFrame==7,"22-frame walking loop wraps at full source frame rate");
        }
    }
    auto s=fixture();auto id=spawn(s);auto *e=s.findEnemy(id);e->velocity={3,0,0};e->gaper->destination=s.player.position;e->pathTime=2;
    e->path={add(e->position,{.05f,0,0})};tick(s);check(near(s.findEnemy(id)->velocity.x,1.5f),"arrival within1native unit halves momentum");
    e=s.findEnemy(id);e->velocity={3,0,0};e->path={e->position};tick(s);check(near(s.findEnemy(id)->velocity.x,2.55f),"zero route retains.85 momentum");
    e=s.findEnemy(id);e->velocity={};e->path={e->position};tick(s);check(e->gaper->walkFrame==0,"stopped walking holds frame0");
    std::cout<<"MOVEMENT hp32_32_28_8=1 first_tick=1 source_acceleration=1 analytic30ticks=1 arrival=1 no_route=1 walk22=1\n";
}
void awarenessAndCollision() {
    auto s=fixture();auto id=spawn(s,0);
    s.arena.floorProps.push_back({StoryPropKind::Crate,{{2,-.1f,-4},{4,3,4}}});s.arena.rebuildWalls();
    check(!s.arena.clear(s.findEnemy(id)->position,s.player.position,.6f),"solid cover obstructs direct ground path");
    tick(s);auto *e=s.findEnemy(id);
    check(!e->gaper->wakeStarted&&!e->awakened&&e->gaper->headFrame==0&&near(e->gaper->force,.6f),"covered Frowning keeps its eyes shut and closed force");
    check(length(e->velocity)>.1f,"closed Frowning still paths toward the player");
    s.arena.floorProps.clear();s.arena.rebuildWalls();tick(s);e=s.findEnemy(id);
    check(e->gaper->wakeStarted&&!e->awakened&&e->gaper->headFrame==0&&near(e->gaper->force,.6f),"first direct path starts overlay without same-tick speed increase");
    tick(s);e=s.findEnemy(id);check(e->awakened&&e->gaper->headFrame==1&&near(e->gaper->force,.72f)&&near(e->gaper->eyeOpenness,1.f/19),"next positive overlay frame boosts force and begins visible opening");
    s.arena.floorProps.push_back({StoryPropKind::Crate,{{10,-.1f,-20},{12,3,20}}});s.arena.rebuildWalls();tick(s,24);e=s.findEnemy(id);
    check(!e->gaper->directPath&&e->awakened&&e->gaper->headFrame==19&&near(e->gaper->eyeOpenness,1)&&near(e->gaper->force,.72f),"opening finishes and wake persists after renewed obstruction");
    e->state=EnemyState::Stunned;e->stateTime=.1f;const auto at=e->position;tick(s,3);
    check(distance(s.findEnemy(id)->position,at)<.001f&&s.findEnemy(id)->gaper->headFrame==19,"stun pauses motion without closing the head");
    s.enterRoom(1);tick(s,5);s.enterRoom(0);e=s.findEnemy(id);
    check(e&&e->gaper&&e->awakened&&e->gaper->headFrame==19,"room re-entry preserves activation and animation");
    for(int v:{0,1,2}) {
        auto q=fixture();auto body=spawn(q,v);
        q.arena.floorProps.push_back({StoryPropKind::Crate,{{2,-.1f,-4},{4,3,4}}});q.arena.rebuildWalls();
        for(int i=0;i<90;++i){tick(q);check(!q.arena.blocked(q.findEnemy(body)->position,q.findEnemy(body)->radius),"source-driven chase respects physical cover");}
    }
    std::cout<<"AWARENESS closed_chase=1 delayed_open=1 permanent_wake=1 animation20=1 reentry=1 cover=1\n";
}
void fireContactAndPartition() {
    for(int v:{0,1,2}) {
        auto s=fixture();auto id=spawn(s,v);const float hp=s.findEnemy(id)->hp;
        hit(s,id,3,DamageKind::Flame);hit(s,id,4,DamageKind::Burning);
        check(near(s.findEnemy(id)->hp,hp-7)&&s.findEnemy(id)->monster==monsterId(10,v),"Gaper variants take fire damage with no invented ignition conversion/immunity");
        tick(s,40);check(s.hazards.empty()&&s.stats.projectiles==0,"even Flaming has no invented damaging trail or ranged attack");
        auto a=fixture(),b=fixture();auto ia=spawn(a,v),ib=spawn(b,v);tick(a,60);tick(b,240,1.f/120);
        check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.02f&&
            a.findEnemy(ia)->gaper->headFrame==b.findEnemy(ib)->gaper->headFrame&&a.findEnemy(ia)->gaper->walkFrame==b.findEnemy(ib)->gaper->walkFrame,
            "30/120Hz partitions preserve ordinary movement and animation cadence");
    }
    auto s=fixture();s.godMode=false;auto id=spawn(s);s.player.position={.9f,.85f,0};tick(s);
    check(near(s.player.hp,StartingHealth-10*EnemyDamageMultiplier),"source-adapted contact base10 retains global damage multiplier");tick(s,3);
    check(near(s.player.hp,StartingHealth-10*EnemyDamageMultiplier),"player hurt invulnerability prevents repeated contact damage");
    std::cout<<"DAMAGE fire_vulnerable=3 no_ignition=1 no_trail=1 contact_base10_global_multiplier=1 partition30_120=1\n";
}
void externalProfiles() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-gaper-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"gapers.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;auto at=text.find(from);check(at!=text.npos,"reload fixture exists");text.replace(at,from.size(),to);std::ofstream(dir/"gapers.mechanics")<<text;return MechanicsLibrary::load(dir);};
    const auto changed=edit(".497999996 .497999996",".25 .25");
    auto s=fixture(changed);auto id=spawn(s);tick(s);
    check(near(s.findEnemy(id)->velocity.x,1.5f)&&near(defaultMechanics()->gaper(monsterId(10,1))->force,.498f),"reload changes new simulation force without mutating existing snapshot");
    const std::vector<std::pair<std::string,std::string>> invalid={
        {"gaper 10.1.0 0","gaper 10.0.0 0"},{".497999996 .497999996",".25 .3"},
        {".7 .85 .5","1 .85 .5"},{".7 .85 .5",".7 0 .5"},{"10 20 22","10 1 22"},
        {"10 20 22","10 20 1"},{".1 2 1 .1 10",".1 2 0 .1 10"},
        {"Chase None Walker 32","Wander None Walker 32"},{"Chase None Walker 32","Chase Shot Walker 32"},
        {".720000029","-.1"},{".1 2 1 .1 10",".1 2 1 .1 0"}};
    for(const auto &[from,to]:invalid){bool rejected=false;try{edit(from,to);}catch(const std::exception&){rejected=true;}check(rejected,"malformed Gaper contract rejected");}
    std::cout<<"EXTERNAL immutable_reload=1 runtime_force=1 rejected_contracts="<<invalid.size()<<'\n';
}
void placement() {
    const auto content=defaultMechanics();
    for(int band=0;band<4;++band)for(auto variant:{FloorVariant::Standard,FloorVariant::Scorched}) {
        FloorProfile p;p.band=band;p.variant=variant;
        for(int source:{0,1}) {
            const auto *replacement=content->replacement(monsterId(10,source),p);
            check(bool(replacement)==(band==0&&variant==FloorVariant::Scorched),"Flaming replacement only in Burning Basement analogue");
            if(replacement)check(replacement->target==monsterId(10,2)&&replacement->chance==6000,"both Gaper forms use pinned60percent replacement");
        }
    }
    auto s=fixture();s.arena.rooms.resize(400);s.arena.profile.maxThreat=12;s.arena.profile.areaPerThreat=95;
    for(auto &r:s.arena.rooms){r.kind=RoomKind::Combat;r.floorArea=800;}
    for(int band=0;band<4;++band) {
        s.arena.profile.band=band;s.arena.profile.variant=FloorVariant::Standard;
        for(int r=0;r<400;++r)for(const auto &id:s.floorEncounter(r).monsters)
            if(id.type==10&&id.variant<=2)check(band<=1&&id.variant!=2,"ordinary Gaper placement limited to source-supported early bands");
    }
    // Real scorched basic replacements cost2 rather than1. A4-threat room
    // containing a2-threat specialist must still receive two support actors.
    s.arena.profile.band=0;s.arena.profile.variant=FloorVariant::Scorched;
    s.arena.profile.maxThreat=4;s.arena.profile.maxSpecialists=2;
    for(int pattern=0;pattern<4;++pattern) {
        s.arena.profile.patterns={0,0,0,0};s.arena.profile.patterns[size_t(pattern)]=1;
        for(int room=0;room<400;++room) {
            const auto plan=s.floorEncounter(room);
            check(plan.spent<=plan.budget&&plan.monsters.size()>=size_t(plan.specialists+2),
                "stronger basic replacements cannot consume the second supporting enemy's reserved budget");
        }
    }
    std::cout<<"PLACEMENT bands0_1=1 scorched0_only=1 replacement60percent=1 support_reserve=1600\n";
}
void natural() {
    bool found[3]{};
    for(unsigned seed=0;seed<64&&(!found[0]||!found[1]||!found[2]);++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==10&&e.monster.variant<=2) {
            check(e.gaper&&!s.arena.blocked(e.position,e.radius),"natural Gaper resident has dedicated controller and legal footprint");
            if(!found[e.monster.variant]){found[e.monster.variant]=true;std::cout<<"NATURAL_GAPER variant="<<e.monster.variant<<" seed="<<seed<<" floor=0 room="<<room<<'\n';}
        }
    }
    check(found[0]&&found[1]&&found[2],"all three natural Gaper forms found");
}
}
int main(int argc,char**argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--natural"){natural();return 0;}healthAndAcceleration();awarenessAndCollision();fireContactAndPartition();externalProfiles();placement();std::cout<<"PASS Gaper family\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
