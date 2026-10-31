#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
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
EntityId spawn(Simulation &s,int subtype,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(10,3,subtype),at);}
void damage(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;s.queueRoot(e);s.drainEvents();
}
int owned(const Simulation &s,EntityId parent){return int(std::count_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.summoner==parent;}));}
void identityAndPhysics() {
    std::array<int,6> selected{};
    for(unsigned seed=0;seed<128;++seed) {
        auto a=fixture(seed),b=fixture(seed);const auto ia=spawn(a,0),ib=spawn(b,0);
        const auto sub=a.findEnemy(ia)->monster.subtype;
        check(sub>=1&&sub<=5&&sub==b.findEnemy(ib)->monster.subtype,"default dispatch is seeded and reproducible");++selected[sub];
    }
    for(int sub=1;sub<=5;++sub)check(selected[sub]>8,"all five default outcomes occur across seeds");
    const std::array<float,6> forces={0,.72f,.9f,.48f,.54f,1.14f};
    for(int sub=1;sub<=5;++sub) {
        auto s=fixture();const auto id=spawn(s,sub);tick(s);const auto *e=s.findEnemy(id);
        check(e->monster.subtype==sub&&near(e->hp,76.8f)&&e->rottenGaper&&length(e->velocity)==0,"exact subtype and source24HP; initialization has no movement");
        for(int stage=1;stage<=12;++stage)check(near(defaultMechanics()->monsterHealth(e->monster,stage),76.8f),"source health has no stage gain");
        if(sub==5)continue;
        tick(s,30);e=s.findEnemy(id);
        const float terminal=forces[sub]*20;
        const float velocity=terminal*(1-std::pow(.7f,30));
        const float displacement=terminal/30*(30-.7f*(1-std::pow(.7f,30))/.3f);
        check(near(e->velocity.x,velocity,.01f)&&near(e->position.x,displacement,.01f),"30-tick acceleration matches independent source force/friction solution");
        check(s.stats.projectiles==0&&s.hazards.empty(),"Rotten does not inherit Dead Isaac shots or damaging trail");
    }
    std::cout<<"IDENTITY seeded128=1 all_five=1 exact=1 health76.8=1 PHYSICS analytic30=1 initialization=1\n";
}
void orbitAndCover() {
    auto s=fixture();s.player.position={0,.85f,0};auto id=spawn(s,5,{0,.85f,12});tick(s,2);
    auto *e=s.findEnemy(id);
    check(e->rottenGaper->orbitDirect&&near(e->rottenGaper->force,1.14f*.85f)&&near(e->velocity.z,-1.14f*.85f*.9f*3),
        "orbit starts from actual zero momentum with source distance gain and .9retention");
    check(near(planarDistance(e->rottenGaper->destination,s.player.position),6),"orbit destination lies on native60-unit radius");
    auto zero=fixture();zero.player.position={0,.85f,0};const auto z=spawn(zero,5,{0,.85f,6});tick(zero,60);
    check(length(zero.findEnemy(z)->velocity)==0&&near(zero.findEnemy(z)->position.z,6),"zero vector at exact orbit radius stays zero without an invented tangent");
    s.arena.floorProps.push_back({StoryPropKind::Crate,{{-2,-.1f,2},{2,3,4}}});s.arena.rebuildWalls();
    tick(s);check(!s.findEnemy(id)->rottenGaper->orbitDirect,"blocked orbit switches to ground route");
    bool regained=false;
    for(int i=0;i<300;++i){tick(s);e=s.findEnemy(id);check(!s.arena.blocked(e->position,e->radius),"orbit/path movement respects solid cover");regained|=e->rottenGaper->orbitDirect;}
    check(regained,"blocked orbit navigates around cover and resumes direct steering");
    auto a=fixture(),b=fixture();auto ia=spawn(a,5),ib=spawn(b,5);tick(a,120);tick(b,480,1.f/120);
    check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.03f&&a.findEnemy(ia)->rottenGaper->ticks==b.findEnemy(ib)->rottenGaper->ticks,
        "source orbit timing and motion survive30/120Hz partition");
    std::cout<<"ORBIT zero_vector=1 source_force=1 radius6=1 cover=1 partition30_120=1\n";
}
void broodTimingAndOwnership() {
    std::set<int> birthTicks;int earliest=10000,latest=0;
    for(unsigned seed=0;seed<48;++seed) {
        auto s=fixture(seed);auto id=spawn(s,3);tick(s,61);
        check(owned(s,id)==0&&s.findEnemy(id)->rottenGaper->spawnCounter==60&&s.findEnemy(id)->rottenGaper->spawnRolls==0,
            "strictly more than60 active source updates required before first roll");
        Vector3 birthPosition{};int frame=61;for(;frame<220&&owned(s,id)==0;++frame){birthPosition=s.findEnemy(id)->position;tick(s);}
        check(owned(s,id)==1,"eligible brood eventually births a child");
        earliest=std::min(earliest,frame);latest=std::max(latest,frame);birthTicks.insert(frame);
        for(const auto &child:s.enemies)if(child.summoner==id) {
            check(child.monster==monsterId(853)&&child.smallMaggot&&near(child.hp,32)&&child.partner==0,"source child identity, health and ownership");
            check(distance(child.position,birthPosition)<.001f&&length(child.velocity)==0,"queued birth uses parent location at source update and zero velocity");
        }
    }
    check(earliest==62&&latest>65&&birthTicks.size()>8,"summoning delay follows random eligible-frame rolls, not fixed two-second period");
    auto s=fixture();auto id=spawn(s,3);tick(s,1000);check(owned(s,id)==6,"owner cap stops at six live maggots");
    const auto counter=s.findEnemy(id)->rottenGaper->spawnCounter;bool reset=false;
    for(int i=0;i<160;++i){const auto before=s.findEnemy(id)->rottenGaper->spawnCounter;tick(s);reset|=s.findEnemy(id)->rottenGaper->spawnCounter<before;check(owned(s,id)==6,"cap persists across eligible rolls");}
    (void)counter;check(reset,"successful roll resets timer even at owner cap");
    auto child=std::find_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.summoner==id;})->id;
    damage(s,child,1000);tick(s,180);check(owned(s,id)==6,"dead owned child frees a slot");
    auto other=spawn(s,3,{-35,.85f,0});tick(s,240);check(owned(s,other)>0&&owned(s,id)==6,"owner caps are independent across parents");
    s.debugScenario=false;s.rooms[0].cleared=false;damage(s,id,1000);damage(s,other,1000);tick(s);
    check(!s.roomClear&&s.roomThreats()>=6,"live offspring remain room threats after all parents die");
    s.killAll();tick(s);check(s.roomClear,"last offspring death completes room");
    std::cout<<"BROOD births="<<earliest<<".."<<latest<<" owner_cap=1 cap_reset=1 refill=1 two_parents=1 completion=1\n";
}
void avoidanceAndIntegration() {
    auto s=fixture();auto parent=spawn(s,3),peer=spawn(s,1,{3,.85f,0});
    s.findEnemy(peer)->state=EnemyState::Stunned;s.findEnemy(peer)->stateTime=100;tick(s,2);
    auto *e=s.findEnemy(parent);check(e->rottenGaper->avoid==peer&&e->rottenGaper->remember>=30&&e->rottenGaper->remember<=44,"remote-player brood remembers different-subtype neighbor30..44frames");
    const int remember=e->rottenGaper->remember;tick(s,10);e=s.findEnemy(parent);
    check(e->rottenGaper->avoid==peer&&e->rottenGaper->remember==remember-10,"retained target timer decrements exactly once per source update");
    tick(s,16);e=s.findEnemy(parent);check(e->rottenGaper->evading&&e->position.x<-.1f,"brood flees nearby peer instead of continuing toward remote player");
    damage(s,peer,1000);tick(s);check(s.findEnemy(parent)->rottenGaper->avoid==0,"dead avoidance target is released");
    auto nearPlayer=fixture();nearPlayer.player.position={0,.85f,7};const auto a=spawn(nearPlayer,3);spawn(nearPlayer,1,{3,.85f,0});tick(nearPlayer,2);
    check(nearPlayer.findEnemy(a)->rottenGaper->avoid==0,"player within80native units prevents new peer acquisition");
    auto same=fixture();auto b=spawn(same,3);spawn(same,3,{3,.85f,0});auto f=spawn(same,2,{-3,.85f,0});same.findEnemy(f)->friendly=true;tick(same,2);
    check(same.findEnemy(b)->rottenGaper->avoid==0,"brood excludes same subtype and different friendliness");
    auto contact=fixture();contact.godMode=false;auto c=spawn(contact,1);contact.player.position={.9f,.85f,0};tick(contact);
    check(near(contact.player.hp,StartingHealth-10*EnemyDamageMultiplier),"contact preserves source10 and global damage multiplier");
    damage(contact,c,2,DamageKind::Flame);check(near(contact.findEnemy(c)->hp,74.8f),"Rotten remains fire vulnerable");
    e=s.findEnemy(parent);const auto at=e->position;const auto counter=e->rottenGaper->spawnCounter;e->state=EnemyState::Stunned;e->stateTime=.1f;tick(s,3);
    check(distance(at,s.findEnemy(parent)->position)<.001f&&s.findEnemy(parent)->rottenGaper->spawnCounter==counter,"stun pauses parent motion and summoning");
    s.enterRoom(1);tick(s,3);s.enterRoom(0);check(s.findEnemy(parent)&&s.findEnemy(parent)->rottenGaper->spawnCounter==counter,"room reentry retains independent parent runtime");
    std::cout<<"AVOIDANCE selection=1 retention=1 flee=1 death=1 filters=1 INTEGRATION contact=1 fire=1 stun=1 reentry=1\n";
}
void externalProfiles() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-rotten-gaper-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"rotten_gapers.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto t=original;auto at=t.find(from);check(at!=t.npos,"reload fixture exists");t.replace(at,from.size(),to);std::ofstream(dir/"rotten_gapers.mechanics")<<t;return MechanicsLibrary::load(dir);};
    auto changed=edit("rotten_gaper 10.3.1 .1 0.72","rotten_gaper 10.3.1 .1 .36");auto s=fixture(1866,changed);auto id=spawn(s,1);tick(s,2);
    check(near(s.findEnemy(id)->velocity.x,2.16f)&&near(defaultMechanics()->rottenGaper(monsterId(10,3,1))->force,.72f),"external force reload affects runtime and preserves previous immutable library");
    const std::vector<std::pair<std::string,std::string>> invalid={
        {".1 0.72 .7","0 .72 .7"},{".1 0.72 .7",".1 -.72 .7"},{".1 0.72 .7",".1 0.72 1"},
        {"60 8 6 80","60 0 6 80"},{"60 8 6 80","60 8 0 80"},{"30 44 .8","45 44 .8"},
        {"30 44 .8","30 44 1"},{"60 80 100 .75","60 80 0 .75"},{"60 80 100 .75","60 80 100 0"},
        {".25 .9 20",".25 1 20"},{"853.0.0 60","10.1.0 60"},{"Chase None Walker","Chase Shot Walker"}};
    for(const auto &[from,to]:invalid){bool rejected=false;try{edit(from,to);}catch(const std::exception&){rejected=true;}check(rejected,"malformed Rotten contract rejected");}
    std::cout<<"EXTERNAL reload=1 immutable=1 invalid_contracts="<<invalid.size()<<'\n';
}
void natural() {
    std::set<int> seen;bool defaultSeen=false;
    for(unsigned seed=0;seed<128&&(seen.size()<5||!defaultSeen);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        int floor=0;while(plan.profileOnFloor(floor).band<3)++floor;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=0;room<s.arena.roomCount();++room) {
            const auto encounter=s.floorEncounter(room);
            const bool selectsDefault=std::find(encounter.monsters.begin(),encounter.monsters.end(),monsterId(10,3))!=encounter.monsters.end();
            for(const auto &e:s.roomEnemies(room))if(e.monster.type==10&&e.monster.variant==3) {
                check(e.monster.subtype>=1&&e.monster.subtype<=5&&e.rottenGaper&&near(e.hp,76.8f)&&
                    s.arena.profile.band==3&&!s.arena.blocked(e.position,e.radius),"actual seeded Rotten has resolved subtype, source health, controller and safe late-band placement");
                if(seen.insert(e.monster.subtype).second)
                    std::cout<<"NATURAL_ROTTEN subtype="<<e.monster.subtype<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
                if(selectsDefault&&!defaultSeen){defaultSeen=true;std::cout<<"NATURAL_DEFAULT seed="<<seed<<" floor="<<floor<<" room="<<room<<" subtype="<<e.monster.subtype<<'\n';}
            }
        }
    }
    check(seen.size()==5&&defaultSeen,"all exact subtypes and default selector reachable in actual generated floors");
}
}
int main(int argc,char**argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--natural"){natural();return 0;}identityAndPhysics();orbitAndCover();broodTimingAndOwnership();avoidanceAndIntegration();externalProfiles();std::cout<<"Rotten Gaper checks passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
