#include "combat/Simulation.hpp"
#include "combat/LobFlight.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine);
    s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,10,50}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-50,-.4f,-50},{50,0,50}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
void tick(Simulation &s,int count=1){for(int n=0;n<count;++n)s.step({});}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(29,3),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
void sequence() {
    auto s=fixture();const auto id=spawn(s);
    check(near(s.findEnemy(id)->hp,256),"80sourceHP x3.2 without generic legacy health");
    tick(s,54);check(s.findEnemy(id)->targetHop->counter==26&&!s.findEnemy(id)->targetHop->targetReady,"26source-frame initial idle");
    tick(s,2);check(s.findEnemy(id)->targetHop->frame==0&&s.findEnemy(id)->targetHop->pursuing,"initial Hop starts at0 and targets nearby player");
    tick(s,8);check(s.findEnemy(id)->targetHop->airborne,"Jump4");
    tick(s,24);check(s.stats.projectiles==0,"no ring before Land17");
    const std::array<int,4> counts{4,6,8,12};const std::array<float,4> speeds{24,30,24,30};
    uint64_t total=0;
    for(int phase=0;phase<4;++phase) {
        for(int frame=0;frame<200&&s.findEnemy(id)->hopRings->volleys==phase;++frame)tick(s);
        const auto *e=s.findEnemy(id);check(e->hopRings->volleys==phase+1,"one ring per source Land event");
        check(e->hopRings->animationStage==phase,"Hop/Hop2 retains active phase through landing");
        check(e->hopRings->stage==(phase+1)%4,"phase advances exactly once");
        check(s.projectiles.size()==size_t(counts[size_t(phase)]),"measured4/6/8/12 ring counts");
        total+=counts[size_t(phase)];check(s.stats.projectiles==total,"no extra generic radial shot");
        for(const auto &shot:s.projectiles) {
            check(near(length(horizontal(shot.velocity)),speeds[size_t(phase)]),"source speed8/10/8/10 x3");
            check(shot.context.sourceEntity==id&&shot.hostile,"projectile retains hostile owner");
            check(near(shot.gravity,1.35f)&&near(shot.flightRetention,.9f)&&shot.velocity.y<.15f&&shot.velocity.y>-.2f,"source low-acceleration physical flight");
            const auto dir=unit(shot.velocity);const float angle=std::atan2(dir.z,dir.x)*float(counts[size_t(phase)])/(2*Pi);
            check(near(angle,std::round(angle)),"world-aligned ring instead of aimed/random rotation");
        }
        for(auto &shot:s.projectiles)shot.life=0;
        if(phase<3) {
            check(e->targetHop->restartAtJump&&!e->targetHop->targetReady,"first three landings chain immediately");
            tick(s,2);e=s.findEnemy(id);
            check(e->targetHop->frame==4&&e->targetHop->airborne&&e->hopRings->animationStage==phase+1,"chained hop skips preparation and alternates animation");
        }
    }
    const auto *e=s.findEnemy(id);check(e->hopRings->cycles==1&&e->targetHop->frame==17&&!e->targetHop->restartAtJump,"fourth landing recovers instead of chaining fifth");
    check(total==30&&s.hazards.empty()&&s.enemies.size()==1,"thirty shots, no invented creep/bomb/offspring");
    std::cout<<"PASS source26idle,Hop23,Jump4,Land17,four chained rings4/6/8/12,speeds8/10/8/10,alignment and recovery\n";
}
void retentionAndLifecycle() {
    auto s=fixture();auto id=spawn(s);s.limits.projectiles=0;tick(s,700);
    auto *e=s.findEnemy(id);check(e->hopRings->cycles==1&&e->hopRings->pending.size()==4&&s.stats.projectiles==0,"capacity retains exactly one full sequence without runaway queue");
    s.limits.projectiles=3;tick(s,4);check(s.stats.projectiles==0,"cannot emit partial first ring");
    s.limits.projectiles=64;tick(s);check(s.stats.projectiles==30&&e->hopRings->pending.empty(),"restored capacity emits all thirty retained shots once");
    auto stunned=fixture();id=spawn(stunned);tick(stunned,94);
    e=stunned.findEnemy(id);const auto volleys=e->hopRings->volleys;
    e->state=EnemyState::Stunned;e->stateTime=2;tick(stunned,60);
    check(stunned.findEnemy(id)->hopRings->volleys==volleys,"grounded stun does not invent landings or fire another ring");
    auto room=fixture();id=spawn(room);tick(room,94);
    const auto before=*room.findEnemy(id)->hopRings;
    room.enterRoom(1);auto guard=room.spawnMonster(monsterId(12),{20,.85f,20});room.findEnemy(guard)->state=EnemyState::Stunned;room.findEnemy(guard)->stateTime=100;
    tick(room,120);room.enterRoom(0);
    check(room.findEnemy(id)->hopRings->volleys==before.volleys&&room.findEnemy(id)->hopRings->stage==before.stage,"inactive-room sequence freezes");
    tick(room,200);check(room.findEnemy(id)->hopRings->volleys>before.volleys,"re-entry resumes sequence");
    auto dead=fixture();dead.debugScenario=false;id=spawn(dead);dead.limits.projectiles=0;tick(dead,180);damage(dead,id,10000);tick(dead,10);
    check(!dead.findEnemy(id)&&dead.stats.kills==1&&dead.roomClear,"death cancels un-emitted attacks and resolves ordinary threat once");
    dead.limits.projectiles=64;tick(dead,60);check(dead.stats.projectiles==0,"dead attacker cannot emit a delayed ring");
    auto contact=fixture();id=spawn(contact);contact.godMode=false;contact.player.position=contact.findEnemy(id)->position;tick(contact);
    check(near(contact.player.hp,StartingHealth-20*EnemyDamageMultiplier),"source full-heart contact conversion");
    std::cout<<"PASS whole-ring capacity retention, bounded cycle, stun, room suspension, death and full-heart contact\n";
}
void configAndPlacement() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-hop-ring-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream stream(dir/"tainted_hopper.mechanics");const std::string original((std::istreambuf_iterator<char>(stream)),{});
    for(const auto &[from,to]:std::array<std::pair<std::string,std::string>,6>{{{"4 24 6 30","1 24 6 30"},{"4 24 6 30","4 -1 6 30"},{"10 6 .18","10 6 0"},{"1.35 .9","1.35 1"},{"1.35 .9","-1 .9"},{"-.15 .15",".2 .15"}}}) {
        auto value=original;value.replace(value.find(from),from.size(),to);std::ofstream(dir/"tainted_hopper.mechanics")<<value;
        bool rejected=false;try{MechanicsLibrary::load(dir);}catch(...){rejected=true;}check(rejected,"invalid ring configuration rejected");
    }
    auto changed=original;changed.replace(changed.find("4 24 6 30"),9,"4 27 6 30");std::ofstream(dir/"tainted_hopper.mechanics")<<changed;
    const auto loaded=MechanicsLibrary::load(dir);check(near(loaded->hopRings(monsterId(29,3))->stages[0].speed,27)&&near(defaultMechanics()->hopRings(monsterId(29,3))->stages[0].speed,24),"immutable external ring snapshots");
    std::filesystem::remove_all(dir);
    bool found=false;
    for(uint64_t seed=0;seed<512&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!found;++floor) {
            if(plan.profileOnFloor(floor).band!=3)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room) {
                int count=0;for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(29,3)) {
                    ++count;check(e.targetHop&&e.hopRings&&near(e.maxHp,256),"natural dedicated source-health body");
                    if(!found)std::cout<<"NATURAL_TAINTED_HOPPER seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';found=true;
                }
                check(count<=1,"at most one initial late-floor Tainted Hopper");
            }
        }
    }
    check(found,"late ordinary pool is naturally reachable");std::cout<<"PASS external data and natural late-floor placement\n";
}
void flight() {
    float y=1.15f,v=.15f,nativeHeight=-23,nativeSpeed=-.1f;
    for(int i=0;i<40;++i) {
        nativeSpeed=.9f*nativeSpeed+.03f;nativeHeight+=nativeSpeed;
        y+=advanceLobHeight(v,1.35f,.9f,1.f/60);y+=advanceLobHeight(v,1.35f,.9f,1.f/60);
        check(near(y,-.05f*nativeHeight)&&near(v,-1.5f*nativeSpeed),"physical ring matches native30Hz damped descent endpoints");
    }
    auto s=fixture();const auto id=spawn(s);tick(s,90);check(s.stats.projectiles==4,"first ring exists before death");
    s.debugScenario=false;damage(s,id,10000);tick(s,2); // Resolve the next source30Hz damage batch.
    check(!s.findEnemy(id)&&!s.roomClear,"existing physical rings survive owner death and hold local clear");
    tick(s,400);check(s.projectiles.empty()&&s.roomClear&&s.stats.kills==1,"ground/wall expiry resolves remaining threat without another kill");
    std::cout<<"PASS physical30Hz descent and surviving projectile completion\n";
}
}
int main(){try{sequence();retentionAndLifecycle();flight();configAndPlacement();std::cout<<"PASS Tainted Hopper\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
