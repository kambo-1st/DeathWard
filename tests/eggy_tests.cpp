#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine);
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,10,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(29,2),{0,.85f,0});}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount) {Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
int children(const Simulation &s,EntityId id){return int(std::count_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.summoner==id;}));}
void hopping() {
    auto s=fixture();auto id=spawn(s);check(near(s.findEnemy(id)->hp,70.4f),"source20+2stage health x3.2");
    tick(s,18);check(s.findEnemy(id)->targetHop->counter==8&&!s.findEnemy(id)->targetHop->targetReady,"eight-frame idle threshold");
    tick(s,2);check(s.findEnemy(id)->targetHop->frame==0&&s.findEnemy(id)->targetHop->pursuing&&near(s.findEnemy(id)->targetHop->bonus,0),"near acquisition with no Trite random bonus");
    tick(s,8);check(s.findEnemy(id)->targetHop->airborne,"Jump4");
    tick(s,24);check(s.findEnemy(id)->eggy->creepPatches==0,"no creep before Land17");
    tick(s,2);check(s.findEnemy(id)->eggy->creepPatches==1&&s.hazards.size()==1,"Land17 creates exactly one patch");
    const auto h=s.hazards.front();check(h.kind==HazardKind::Tar&&near(h.duration,5)&&h.damage==0&&h.tint.r>200,"pale slow-only five-second creep");
    s.player.position=h.position;s.godMode=false;tick(s);
    check(s.player.slowTime>0,"white creep slows contact");
    auto far=fixture();far.player.position={0,.85f,9.1f};auto f=spawn(far);tick(far,20);
    check(!far.findEnemy(f)->targetHop->pursuing,"strict91source acquisition boundary");
    auto quick=fixture();auto q=spawn(quick);tick(quick,1200);
    check(quick.findEnemy(q)->eggy->restarts>0&&quick.findEnemy(q)->eggy->creepPatches>3,"seeded Land restart branch and repeated physical landings occur");
    check(quick.projectiles.empty(),"no invented ranged attacks");
    std::cout<<"PASS Eggy source health/range/idle/Jump/Land, white creep and immediate re-hops\n";
}
void deathSequence() {
    auto s=fixture();s.debugScenario=false;s.player.position={25,.85f,25};auto id=spawn(s);damage(s,id,10000);
    check(s.findEnemy(id)&&s.findEnemy(id)->dyingEggy()&&s.stats.kills==0&&s.roomThreats()==1,"lethal hit begins harmless husk without early kill/clear");
    const auto position=s.findEnemy(id)->position;damage(s,id,10000);
    check(near(s.findEnemy(id)->hp,.1f)&&s.findEnemy(id)->eggy->frame==0,"repeat damage cannot restart or kill husk");
    auto pass=fixture();pass.player.position={25,.85f,25};auto husk=spawn(pass);damage(pass,husk,1000);
    auto behind=pass.spawnMonster(monsterId(12),{6,.85f,0});pass.findEnemy(behind)->state=EnemyState::Stunned;pass.findEnemy(behind)->stateTime=100;
    const float hp=pass.findEnemy(behind)->hp;Event shot;shot.position={-3,.85f,0};shot.direction={1,0,0};shot.damage=1;pass.queueRoot(shot);pass.drainEvents();
    tick(pass,24);check(pass.findEnemy(behind)->hp<hp,"real bullet passes non-colliding husk and damages body behind it");
    auto harmless=fixture();auto shell=spawn(harmless);damage(harmless,shell,1000);
    auto ally=harmless.spawnMonster(monsterId(23,0,1),{0,.85f,0});harmless.findEnemy(ally)->state=EnemyState::Stunned;harmless.findEnemy(ally)->stateTime=100;
    const float allyHp=harmless.findEnemy(ally)->hp;tick(harmless);check(near(harmless.findEnemy(ally)->hp,allyHp),"husk cannot harm overlapping companion");
    const std::array<int,14> frames{8,11,13,14,17,19,20,21,25,31,36,37,51,66};int expected=0;
    for(int frame=1;frame<70;++frame) {
        tick(s,2);if(std::find(frames.begin(),frames.end(),frame)!=frames.end())++expected;
        const auto *e=s.findEnemy(id);check(e&&e->eggy->released==expected,"exact cumulative release cadence");
        check(children(s,id)==expected&&s.stats.kills==0&&!s.roomClear,"children persist and husk holds completion");
        check(distance(e->position,position)<.001f,"husk anchored despite crowd and impulse");
    }
    tick(s,2);check(!s.findEnemy(id)&&s.stats.kills==1&&children(s,id)==14&&!s.roomClear,"Die70 resolves parent once,14 real Swarm threats remain");
    s.killAll();tick(s);check(s.roomClear&&s.roomThreats()==0,"last children resolve room completion");
    std::cout<<"PASS70-frame deferred death,14 timed children, harmless body, no duplicate loot/kill and room completion\n";
}
void childLaunchAndCapacity() {
    auto s=fixture();s.debugScenario=false;s.player.position={25,.85f,25};auto id=spawn(s);s.limits.enemies=1;damage(s,id,1000);
    tick(s,138);check(s.findEnemy(id)->eggy->released==14&&children(s,id)==0&&!s.roomClear,"all mandatory births retained while only parent slot available");
    s.enterRoom(1);
    // Fixture rooms share bounds: keep this room occupied so clearing it does
    // not auto-enter room0 at the unchanged player position during the wait.
    auto guard=s.spawnMonster(monsterId(12),{-25,.85f,-25});s.findEnemy(guard)->state=EnemyState::Stunned;s.findEnemy(guard)->stateTime=100;
    tick(s,20);s.enterRoom(0);
    check(s.findEnemy(id)&&s.findEnemy(id)->eggy->frame==69&&!s.roomClear,"suspended release phase survives room re-entry");
    tick(s,2);check(!s.findEnemy(id)&&s.stats.kills==1&&children(s,id)==1&&!s.roomClear,"parent disappearance does not discard pending birth metadata");
    s.limits.enemies=32;tick(s);
    check(children(s,id)==14,"all fourteen retained births eventually placed");
    int fresh=0;
    for(const auto &e:s.enemies)if(e.summoner==id) {
        check(e.monster==monsterId(884)&&e.swarmSpider&&e.swarmSpider->initialized,"required child uses real Swarm controller");
        const auto &r=*e.swarmSpider;const auto &hop=s.content->swarmSpider(e.monster)->hops[size_t(r.kind)];
        check(r.airborne&&r.frame>=hop.jump+2&&r.frame<hop.land,"offspring begin mid-hop, not idle targeting");
        const float speed=length(r.launch);check(speed>=hop.minimum&&speed<hop.maximum,"source hop launch speed range");
        check(near(e.maxHp,15.04f),"child source stage health preserved");
        if(r.frame==hop.jump+2)++fresh;
    }
    check(fresh>=13,"retained child initial animation phase not advanced in pending queue");
    s.killAll();tick(s);check(s.roomClear,"debug kill also clears pending sequence");
    auto halted=fixture();auto h=spawn(halted);damage(halted,h,1000);tick(halted,20);halted.findEnemy(h)->state=EnemyState::Stunned;halted.findEnemy(h)->stateTime=100;
    tick(halted,130);check(!halted.findEnemy(h)&&children(halted,h)==14,"stun cannot resurrect or indefinitely postpone dying parent");
    std::cout<<"PASS retained child launch/health, capacity, room suspension and stun handling\n";
}
void configAndPlacement() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-eggy-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);
    for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"eggies.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    for(const auto &[from,to]:std::vector<std::pair<std::string,std::string>>{{"14 2 5 7","14 2 2 7"},{"70 7 884","60 7 884"},{"884.0.0 .1 2","884.0.0 .1 20"}}) {
        auto bad=original;bad.replace(bad.find(from),from.size(),to);std::ofstream(dir/"eggies.mechanics")<<bad;
        bool rejected=false;try{MechanicsLibrary::load(dir);}catch(...){rejected=true;}check(rejected,"invalid cadence/animation binding rejected");
    }
    auto changed=original;const std::string from="3 1.28 5 70";changed.replace(changed.find(from),from.size(),"3 1.5 5 70");std::ofstream(dir/"eggies.mechanics")<<changed;
    const auto loaded=MechanicsLibrary::load(dir);check(near(loaded->eggy(monsterId(29,2))->creepRadius,1.5f)&&near(defaultMechanics()->eggy(monsterId(29,2))->creepRadius,1.28f),"immutable external reload");
    std::filesystem::remove_all(dir);
    bool found=false;
    for(uint64_t seed=0;seed<256&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!found;++floor) {
            if(plan.profileOnFloor(floor).band<1)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room) {
                int count=0;
                for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(29,2)) {
                    ++count;check(e.eggy&&e.targetHop&&near(e.hp,s.content->monsterHealth(e.monster,s.arena.profile.sourceStage)),"natural dedicated controller/stage HP");
                    if(!found)std::cout<<"NATURAL_EGGY seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';found=true;
                }
                check(count<=1,"one initial Eggy per room");
            }
        }
    }
    check(found,"ordinary Eggy is naturally reachable");
    // Original failing production witness: legal target(111.197,.214081)
    // snapped into rock at(112,2), causing zero-bonus hopping to stall forever.
    Simulation actual(8,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,4);
    actual.jumpDebug(10);actual.godMode=true;actual.debugScenario=true;
    // Preserve the original terrain and actor/target coordinates independently
    // of later roster weights. Natural placement is checked above; this case
    // specifically guards the blocked-grid fallback, not a frozen encounter roll.
    // Source: docs/reports/isaac-enemy-port/eggy/navigation-diagnostic.txt.
    actual.enemies.clear();
    const Vector3 origin{106.247f,.85f,5.16383f};
    check(!actual.arena.blocked(origin,.65f),"original navigation witness starts on legal ground");
    const auto id=actual.spawnMonster(monsterId(29,2),origin);
    check(id&&actual.findEnemy(id)->eggy,"navigation regression uses the real Eggy controller");
    actual.player.position={111.197176f,.85f,.214081f};
    check(!actual.arena.blocked(actual.player.position,.65f)&&actual.arena.blocked({112,.85f,2},.65f),"legal target and blocked snapped cell reproduce source-grid mismatch");
    tick(actual,500);
    check(actual.findEnemy(id)->targetHop->hops>0&&actual.findEnemy(id)->eggy->creepPatches>0,"actual seeded Eggy hops and deposits creep instead of stalling on snapped rock");
    std::cout<<"PASS config and natural Eggy placement\n";
}
}
int main(){try{hopping();deathSequence();childLaunchAndCapacity();configAndPlacement();std::cout<<"PASS Eggy\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
