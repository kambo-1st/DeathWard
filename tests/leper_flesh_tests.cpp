#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.004f){return std::abs(a-b)<eps;}
constexpr auto Flesh=monsterId(310,1);
Simulation fixture(uint32_t seed=1866,std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,20,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.arena.boundaryWalls={{{-31,-1,-31},{-30,20,31}},{{30,-1,-31},{31,20,31}},{{-31,-1,-31},{31,20,-30}},{{-31,-1,30},{31,20,31}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.roomClear=false;s.godMode=true;s.player.position={0,.85f,20};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({},1.f/30);}
EntityId spawn(Simulation &s,Vector3 p={0,.85f,0}){return s.spawnMonster(Flesh,p);}
void damage(Simulation &s,EntityId id,float amount,bool execution=false,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=execution;e.debugExecution=debug;s.queueRoot(e);s.drainEvents();
}
void movement() {
    auto s=fixture();const auto id=spawn(s);auto *e=s.findEnemy(id);
    check(e&&e->leperFlesh&&near(e->hp,20.8f)&&s.content->monster(Flesh)->flying,"full source stage-one HP and walls-only floating body");
    check(near(s.content->monsterHealth(Flesh,7),42.88f),"stage HP scales with the actual source stage");
    tick(s);check(near(s.findEnemy(id)->position.z,0),"first source frame initializes without motion");
    tick(s);e=s.findEnemy(id);
    const auto impulse=mul(horizontal(e->velocity),1/(.1f*30*.95f));
    check(near(length(sub(impulse,{0,0,.15f})),.3f),"native direct random impulse is damped after addition");
    auto a=fixture(),b=fixture();const auto ai=spawn(a),bi=spawn(b);
    tick(a,30);for(int n=0;n<60;++n)b.step({},1.f/60);
    check(a.findEnemy(ai)&&b.findEnemy(bi),"cadence comparison finishes before consuming flesh on contact");
    check(distance(a.findEnemy(ai)->position,b.findEnemy(bi)->position)<.002f,"30Hz and60Hz integrations share movement and RNG cadence");
    check(a.projectiles.empty()&&a.hazards.empty(),"living flesh emits no attack or damaging creep");
    auto cover=fixture();cover.arena.obstacles.push_back({{-2,0,-2},{2,3,2}});cover.arena.rebuildWalls();
    const auto ci=spawn(cover);tick(cover,2);
    check(cover.findEnemy(ci)->position.y>3&&length(cover.findEnemy(ci)->velocity)>0,"floating flesh can occupy and traverse interior cover");
    cover.player.position={0,.85f,0};cover.godMode=false;tick(cover);
    check(cover.findEnemy(ci)&&near(cover.player.hp,StartingHealth),"flesh above tall cover cannot contact player below");
    auto wall=fixture();const auto wi=spawn(wall,{29.3f,.85f,0});wall.findEnemy(wi)->velocity={30,0,0};
    tick(wall);check(wall.findEnemy(wi)->position.x<=29.4f,"initial impulse cannot cross room boundary");
    std::set<int> shapes;std::set<bool> flips;
    for(int seed=0;seed<40;++seed){auto v=fixture(seed);const auto vi=spawn(v);shapes.insert(v.findEnemy(vi)->leperFlesh->shape);flips.insert(v.findEnemy(vi)->leperFlesh->flip);}
    check(shapes.size()==6&&flips.size()==2,"seeded six silhouettes and both flips are reachable");
    auto resident=fixture();const auto ri=spawn(resident);tick(resident,20);
    const auto saved=*resident.findEnemy(ri)->leperFlesh;
    resident.enterRoom(1);tick(resident,30);resident.enterRoom(0);
    check(resident.findEnemy(ri)&&resident.findEnemy(ri)->leperFlesh->ticks==saved.ticks&&
        resident.findEnemy(ri)->leperFlesh->shape==saved.shape,"inactive room preserves flesh clock and silhouette without simulating pursuit");
    std::cout<<"PASS source force/friction, stage HP, floating cover/walls, source cadence and six shapes\n";
}
void deathAndContact() {
    for(bool execution:{false,true}) {
        auto s=fixture();const auto id=spawn(s);tick(s);s.player.position={0,.85f,12};s.player.velocity={6,0,0};
        damage(s,id,10000,execution);
        check(s.projectiles.size()==1&&s.stats.kills==1,"normal and execution deaths release exactly one shot and one kill");
        const auto &shot=s.projectiles.front();const auto direction=unit(Vector3{2.4f,0,12});
        check(distance(horizontal(shot.velocity),mul(direction,30))<.005f&&near(shot.velocity.y,4.5f),"lead uses distance-scaled native player velocity; planar speed10 and default falling speed-3");
        check(near(shot.gravity,4.5f)&&near(shot.flightRetention,.9f)&&shot.hostile,"death shot uses default falling acceleration and existing flight conversion");
        tick(s,3);check(s.stats.projectiles==1,"dead body cannot repeatedly emit");
    }
    auto debug=fixture();const auto di=spawn(debug);damage(debug,di,10000,true,true);tick(debug);
    check(debug.projectiles.empty()&&debug.stats.projectiles==0,"debug room clear suppresses death shot");
    for(bool god:{false,true}) {
        auto s=fixture();s.godMode=god;const auto id=spawn(s,s.player.position);tick(s);
        check(!s.findEnemy(id)||!s.findEnemy(id)->alive,"touch consumes flesh even when player invulnerable");
        check(s.stats.kills==1&&s.stats.projectiles==1,"contact death keeps the predictive death attack");
        check(god?near(s.player.hp,StartingHealth):s.player.hp<StartingHealth,"contact respects player damage policy");
    }
    auto stunned=fixture();const auto si=spawn(stunned,stunned.player.position);stunned.findEnemy(si)->state=EnemyState::Stunned;stunned.findEnemy(si)->stateTime=1;
    tick(stunned);check(stunned.stats.kills==1&&stunned.stats.projectiles==1,"stun does not remove collision-consumption property");
    auto pressure=fixture();pressure.debugScenario=false;const auto pi=spawn(pressure);tick(pressure);
    pressure.limits.projectiles=0;damage(pressure,pi,10000);tick(pressure,5);
    check(pressure.findEnemy(pi)&&!pressure.findEnemy(pi)->alive&&!pressure.roomClear,"pending death attack retains body and prevents early completion");
    pressure.limits.projectiles=1;tick(pressure);
    check(pressure.stats.projectiles==1&&!pressure.roomClear,"capacity recovery admits exactly one retained shot");
    tick(pressure,300);check(pressure.roomClear,"room clears after final attack lands or expires");
    auto resident=fixture();const auto ri=spawn(resident);resident.limits.projectiles=0;damage(resident,ri,10000);
    resident.enterRoom(1);tick(resident,10);resident.enterRoom(0);resident.limits.projectiles=10;tick(resident);
    check(resident.stats.projectiles==1,"unadmitted death shot survives an inactive-room round trip");
    auto queue=fixture();const auto qi=spawn(queue,queue.player.position);queue.limits.queuedEvents=0;tick(queue,3);
    check(queue.findEnemy(qi)->alive&&queue.findEnemy(qi)->selfDetonated,"contact death survives temporary event pressure");
    queue.limits.queuedEvents=100;tick(queue,2);check(queue.stats.kills==1&&queue.stats.projectiles==1,"contact consumption and attack recover without duplicates");
    std::cout<<"PASS predictive mortality, contact consumption, invulnerability/stun and retained death attack\n";
}
void configurationAndPlacement() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-leper-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}} cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"leper.mechanics");const std::string original{std::istreambuf_iterator<char>(in),{}};
    auto load=[&](const std::string &text){std::ofstream(dir/"leper.mechanics")<<text;return MechanicsLibrary::load(dir);};
    const auto before=load(original);auto edited=original;const auto at=edited.find(".95 .15 2");check(at!=edited.npos,"external force directive exists");edited.replace(at,9,".95 .25 2");
    const auto after=load(edited);
    check(before->fingerprint()!=after->fingerprint()&&near(before->leperFlesh(Flesh)->force,.15f)&&near(after->leperFlesh(Flesh)->force,.25f),"hot reload creates immutable new mechanics snapshot");
    auto changed=fixture(1866,after);const auto id=spawn(changed);tick(changed,2);
    check(near(length(sub(mul(horizontal(changed.findEnemy(id)->velocity),1/(.1f*30*.95f)),{0,0,.25f})),.5f),"runtime actually uses reloaded force");
    auto invalid=original;invalid.replace(invalid.find(".95 .15 2"),9,"1 .15 2");bool rejected=false;
    try{load(invalid);}catch(...){rejected=true;}check(rejected,"invalid friction rejected transactionally");
    rejected=false;try{load(original+"leper_flesh 310.1.0 .1 .95 .15 2 10 24 10 6 .1 .2 8 .1 30 4.5 4.5 1.15 .22 10 8 .9\n");}catch(...){rejected=true;}
    check(rejected,"duplicate controller rejected");
    int natural=0;
    for(uint64_t seed=0;seed<128&&natural<3;++seed) {
        const ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&natural<3;++floor) {
            if(plan.profileOnFloor(floor).band!=3)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom()&&natural<3;++room) {
                int n=0;for(const auto &e:s.roomEnemies(room))if(e.monster==Flesh)++n;
                check(n<=2,"at most two natural flesh specialists per room");
                if(n){++natural;std::cout<<"NATURAL_LEPER_FLESH seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<'\n';}
            }
        }
    }
    check(natural==3,"actual final-band seeded residents reach Leper Flesh");
    std::cout<<"PASS external reload, invalid/duplicate config and seeded placement\n";
}
void startingKit() {
    for(int seed=0;seed<4;++seed) {
        auto s=fixture(seed);s.debugScenario=false;s.godMode=false;s.arena.profile.sourceStage=7;
        for(int n=0;n<3;++n)spawn(s,{float(n*4-4),.85f,0});
        int frames=0;
        for(;frames<1800&&!s.dead&&!s.roomClear;++frames) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            Input input;
            if(target) {
                const auto delta=horizontal(sub(target->position,s.player.position));
                input.fire=true;input.aim=add(target->position,mul(horizontal(target->velocity),length(delta)/26));
                input.movement=length(delta)<6?mul(unit(delta),-1):length(delta)>12?unit(delta):Vector3{};
                input.dodge=length(delta)<2.5f;
            }
            s.step(input);
        }
        std::cout<<"LEPER_FLESH_STARTING_KIT seed="<<seed<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<" cleared="<<s.roomClear<<'\n';
        check(s.roomClear&&!s.dead&&s.stats.kills==3,"starting revolver and dodge clear three source-stage-seven flesh without upgrades");
    }
}
}
int main(){std::cout<<std::unitbuf;try{movement();deathAndContact();configurationAndPlacement();startingKit();std::cout<<"PASS Leper Flesh\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
