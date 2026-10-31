#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *message){if(!b)throw std::runtime_error(message);}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={0,.85f,10};return s;
}
void ticks(Simulation &s,int count=1,int hz=30){for(int n=0;n<count;++n)s.step({},1.f/hz);}
EntityId spawn(Simulation &s,MonsterId kind){const auto id=s.spawnMonster(kind,{0,.85f,0});s.findEnemy(id)->cooldown=0;return id;}
void hit(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
void lifetime() {
    for(auto status:{EnemyStatus::Fear,EnemyStatus::Confusion})for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,monsterId(12));
        check(s.applyEnemyStatus(id,status,90),"status applies to supported live enemy");
        ticks(s,hz,hz);check(s.applyEnemyStatus(id,status,90),"reapplication works");
        const auto remaining=[&](){const auto &r=*s.findEnemy(id)->statuses;return status==EnemyStatus::Fear?r.fear:r.confusion;};
        check(remaining()==120,"native positive durations add and cap at120");
        ticks(s,4*hz-1,hz);check(remaining()>0,"status remains before exact expiry");
        ticks(s,1,hz);check(remaining()==0,"expiry is independent of30/60/120Hz");
        check(s.applyEnemyStatus(id,status,-200),"native negative duration refresh is accepted");
        s.applyEnemyStatus(id,status,1);
        check(remaining()==(status==EnemyStatus::Fear?120:200),"fear and confusion have distinct positive-on-extended behavior");
        s.removeEnemyStatus(id,status);check(!s.findEnemy(id)->affectedBy(status),"explicit removal clears active state");
    }
    auto s=fixture();auto id=spawn(s,monsterId(12));
    check(!s.applyEnemyStatus(id,EnemyStatus::Fear,0)&&!s.applyEnemyStatus(id,EnemyStatus::Fear,-18001),"invalid duration is rejected");
    auto other=spawn(s,monsterId(13));check(!s.applyEnemyStatus(other,EnemyStatus::Fear,30),"unreviewed controller is not silently claimed supported");
    s.applyEnemyStatus(id,EnemyStatus::Fear,10);s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=2;
    ticks(s,10);check(!s.findEnemy(id)->affectedBy(EnemyStatus::Fear),"status timer advances while stunned");
    s.applyEnemyStatus(id,EnemyStatus::Confusion,10);s.rewardOpen=true;ticks(s,30);
    check(s.findEnemy(id)->statuses->confusion==10,"modal pause consumes no status duration");
    std::cout<<"LIFETIME cap120=1 additive=1 extended_refresh=1 partition=1 stun=1 pause=1\n";
}
void horf() {
    for(auto status:{EnemyStatus::Fear,EnemyStatus::Confusion}) {
        auto s=fixture();auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,status,90);
        ticks(s,90);check(s.stats.projectiles==0,"Horf does not acquire while afraid/confused");
        ticks(s,12);check(s.stats.projectiles==1,"Horf resumes after expiry");
        auto cast=fixture();id=spawn(cast,monsterId(12));
        for(int n=0;n<8&&cast.findEnemy(id)->state!=EnemyState::Windup;++n)ticks(cast);
        check(cast.findEnemy(id)->state==EnemyState::Windup,"Horf committed cast fixture");
        cast.applyEnemyStatus(id,status,120);cast.player.position={10,.85f,0};ticks(cast,4);
        check(cast.stats.projectiles==1&&!cast.projectiles.empty()&&cast.projectiles.front().velocity.x>20,
              "status preserves committed Horf shot and current target aim");
        ticks(cast,80);check(cast.stats.projectiles==1,"no second acquisition during active status");
    }
    std::cout<<"HORF acquisition_block=1 committed_shot_preserved=1 current_aim=1\n";
}
void headless() {
    for(auto status:{EnemyStatus::Fear,EnemyStatus::Confusion}) {
        auto s=fixture();auto id=spawn(s,monsterId(11));auto &e=*s.findEnemy(id);
        e.headless->initialized=true;e.headless->cooldown=2;e.velocity={3,0,0};
        s.applyEnemyStatus(id,status,30);ticks(s,30);
        check(s.stats.projectiles==0&&s.findEnemy(id)->headless->cooldown==-28,"Gusher timer keeps counting while shots are suppressed");
        ticks(s,2);check(s.stats.projectiles>0,"Gusher resumes without invented reload after status expiry");
    }
    auto a=fixture(),b=fixture();auto x=spawn(a,monsterId(11,1)),y=spawn(b,monsterId(11,1));
    b.applyEnemyStatus(y,EnemyStatus::Confusion,120);ticks(a,60);ticks(b,60);
    check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.001f&&b.stats.projectiles==0,
          "confused Pacer retains ordinary wandering without invented shooting or player target");
    auto queued=fixture();auto id=spawn(queued,monsterId(11));auto &e=*queued.findEnemy(id);
    e.headless->initialized=true;e.headless->cooldown=0;e.velocity={3,0,0};queued.limits.projectiles=0;ticks(queued);
    check(e.headless->pendingShots.size()==1,"selected Gusher payload fixture");
    queued.applyEnemyStatus(id,EnemyStatus::Confusion,90);queued.limits.projectiles=512;ticks(queued);
    check(queued.stats.projectiles==1&&queued.findEnemy(id)->headless->pendingShots.empty(),"status does not erase an already-selected capacity-delayed shot");
    std::cout<<"HEADLESS suppression=1 timer_continues=1 pacer_unchanged=1 selected_payload_retained=1\n";
}
void movement() {
    for(auto kind:{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1)}) {
        Vector3 reference{};
        for(int hz:{30,60,120}) {
            auto s=fixture();auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Fear,120);
            ticks(s,2*hz,hz);auto &e=*s.findEnemy(id);
            check(planarDistance(e.position,s.player.position)>11,"fear increases distance from nearby player");
            check(!s.arena.blocked(e.position,e.radius),"fear remains on legal floor");
            if(kind==monsterId(10))check(e.awakened,"direct escape path can open Frowning Gaper eyes");
            if(hz==30)reference=e.position;else check(distance(reference,e.position)<.02f,"fear path is frame-partition stable");
        }
    }
    for(int variant:{0,1}) {
        auto a=fixture(),b=fixture();auto x=spawn(a,monsterId(10,variant)),y=spawn(b,monsterId(10,variant));
        b.player.position={0,.85f,-60};a.applyEnemyStatus(x,EnemyStatus::Confusion,120);b.applyEnemyStatus(y,EnemyStatus::Confusion,120);
        ticks(a);ticks(b);const auto target=*a.findEnemy(x)->statuses->confusedTarget;
        check(distance(target,{0,.85f,0})<=24.001f,"confused destination is within native240unit radius");
        ticks(a,12);check(distance(target,*a.findEnemy(x)->statuses->confusedTarget)<.001f,"confusion caches a target between refresh frames");
        ticks(a,2);check(distance(target,*a.findEnemy(x)->statuses->confusedTarget)>.01f,"confusion refreshes at15source updates");
        ticks(a,45);ticks(b,59);
        check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.001f,"confused Gaper target is independent of player position");
        const auto cached=*a.findEnemy(x)->statuses->confusedTarget;
        a.removeEnemyStatus(x,EnemyStatus::Confusion);a.applyEnemyStatus(x,EnemyStatus::Confusion,30);ticks(a);
        check(distance(cached,*a.findEnemy(x)->statuses->confusedTarget)<.001f,"reapplication preserves the separate confused target until its refresh poll");
    }
    auto fear=fixture(),both=fixture();auto a=spawn(fear,monsterId(10,1)),b=spawn(both,monsterId(10,1));
    fear.applyEnemyStatus(a,EnemyStatus::Fear,120);both.applyEnemyStatus(b,EnemyStatus::Fear,120);both.applyEnemyStatus(b,EnemyStatus::Confusion,120);
    ticks(fear,50);ticks(both,50);check(distance(fear.findEnemy(a)->position,both.findEnemy(b)->position)<.001f,"fear takes precedence over confusion targeting");
    std::cout<<"MOVEMENT all_four_evade=1 partition=1 cached_random_target=1 player_independent=1 fear_precedence=1\n";
}
void frictionCoverAndContact() {
    for(auto kind:{monsterId(10,1),monsterId(11,1)}) {
        auto s=fixture();auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Fear,120);
        auto &e=*s.findEnemy(id);e.velocity={3,0,0};
        if(e.headless)e.headless->initialized=true;
        auto &r=e.statuses->flee;r.evadeChecks=3;r.targetReady=true;r.destination={0,.85f,-40};e.path={r.destination};
        ticks(s);const float expectedX=kind.type==10?1.68f:1.26f;
        check(std::abs(e.velocity.x-expectedX)<.001f&&std::abs(e.velocity.z+5.1792f)<.001f,
              "fear preserves source ordering of path impulse and family friction");
        auto cover=fixture();id=spawn(cover,kind);cover.applyEnemyStatus(id,EnemyStatus::Fear,120);
        cover.arena.floorProps.push_back({StoryPropKind::Crate,{{-3,-.1f,-5},{3,3,-3}}});cover.arena.rebuildWalls();
        for(int n=0;n<120;++n){ticks(cover);check(!cover.arena.blocked(cover.findEnemy(id)->position,cover.findEnemy(id)->radius),"fear path cannot pass through solid cover");}
        auto contact=fixture();id=spawn(contact,kind);contact.godMode=false;contact.player.position={0,.85f,.3f};
        contact.applyEnemyStatus(id,EnemyStatus::Fear,120);ticks(contact);
        check(contact.player.hp<StartingHealth,"fear does not make contact damage harmless");
    }
    std::cout<<"PHYSICS source_impulse_friction=1 cover=1 contact_retained=1\n";
}
void configuration() {
    const auto originalLib=defaultMechanics();
    const auto dir=std::filesystem::temp_directory_path()/("dw-status-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};
    std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(originalLib->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    const auto file=dir/"first_floor_statuses.mechanics";
    std::ifstream in(file);const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](const std::string &from,const std::string &to) {
        auto text=original;const auto at=text.find(from);check(at!=text.npos,"status config fixture exists");
        text.replace(at,from.size(),to);std::ofstream(file)<<text;return MechanicsLibrary::load(dir);
    };
    auto s=fixture();auto id=spawn(s,monsterId(10,1));s.content=edit("status_effects 10.1.0 120 15 24","status_effects 10.1.0 20 3 2");
    s.applyEnemyStatus(id,EnemyStatus::Confusion,120);ticks(s);
    check(s.findEnemy(id)->statuses->confusion==19&&planarDistance(*s.findEnemy(id)->statuses->confusedTarget,{0,.85f,0})<=2.001f,
          "reloaded content drives duration and targeting in actual simulation");
    check(originalLib->enemyStatuses(monsterId(10,1))->capFrames==120&&originalLib->fingerprint()!=s.content->fingerprint(),
          "content reload preserves old immutable snapshot and changes fingerprint");
    for(const auto &[from,to]:std::vector<std::pair<std::string,std::string>>{
        {"status_effects 12.0.0 120 15 24","status_effects 12.0.0 0 15 24"},
        {"status_effects 12.0.0 120 15 24","status_effects 12.0.0 120 0 24"},
        {"status_effects 12.0.0 120 15 24","status_effects 12.0.0 120 15 nan"},
        {"status_effects 12.0.0 120 15 24","status_effects 13.0.0 120 15 24"},
        {"fear_motion 10.0.0","#fear_motion 10.0.0"},
        {"fear_motion 10.0.0 .1","fear_motion 10.0.0 0"},
        {"status_effects 12.0.0 120 15 24","status_effects 12.0.0 120 15 24\nstatus_effects 12.0.0 120 15 24"}}) {
        bool rejected=false;try{edit(from,to);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or unsupported status contract rejected");
    }
    std::cout<<"CONTENT external_runtime_values=1 immutable_reload=1 rejected_contracts=7\n";
}
void morphAndRooms() {
    bool morphed=false;
    for(unsigned seed=0;seed<50&&!morphed;++seed) {
        auto s=fixture();auto id=spawn(s,monsterId(10,1));s.applyEnemyStatus(id,EnemyStatus::Fear,100);s.applyEnemyStatus(id,EnemyStatus::Confusion,90);
        s.combatRng=Random(seed);hit(s,id,32);auto *e=s.findEnemy(id);
        if(!e||!e->alive||e->monster.type!=11)continue;
        morphed=true;check(e->statuses->fear==100&&e->statuses->confusion==90&&s.stats.kills==0&&s.roomThreats()==1,
            "same-entity headless morph retains both statuses without duplicate rewards or clear");
        ticks(s,90);check(!s.findEnemy(id)->affectedBy(EnemyStatus::Confusion)&&s.findEnemy(id)->affectedBy(EnemyStatus::Fear),"morphed statuses expire independently");
        hit(s,id,1000);check(s.stats.kills==1&&!s.applyEnemyStatus(id,EnemyStatus::Fear,20),"final death counts once and rejects statuses");
    }
    check(morphed,"seeded lethal morph witness exists");
    Simulation s(3,1,{},MissionTheme::Canyon);s.debugScenario=true;s.godMode=true;s.enterRoom(1);
    const auto id=s.spawnMonster(monsterId(12),s.arena.rooms[1].center);s.applyEnemyStatus(id,EnemyStatus::Fear,90);
    s.enterRoom(0);ticks(s,60);s.enterRoom(1);
    check(s.findEnemy(id)&&s.findEnemy(id)->statuses->fear==90,"inactive stored room retains status without consuming time");
    std::cout<<"MORTALITY same_id_morph=1 independent_expiry=1 final_kill=1 inactive_room_pause=1\n";
}
}
int main(){try{lifetime();horf();headless();movement();frictionCoverAndContact();configuration();morphAndRooms();std::cout<<"First-floor status contracts passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
