#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
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
const std::array<MonsterId,5> Cohort{{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1),monsterId(12)}};
void durationAndPause() {
    for(auto kind:Cohort)for(int hz:{30,60,120}) {
        auto s=fixture();const auto id=spawn(s,kind);
        check(s.applyEnemyStatus(id,EnemyStatus::Freeze,90),"freeze supported for all first five");
        ticks(s,hz,hz);s.applyEnemyStatus(id,EnemyStatus::Freeze,90);
        check(s.findEnemy(id)->statuses->freeze==120,"freeze adds duration with120frame cap");
        ticks(s,4*hz-1,hz);check(s.findEnemy(id)->affectedBy(EnemyStatus::Freeze),"freeze lasts to exact expiry");
        ticks(s,1,hz);check(!s.findEnemy(id)->affectedBy(EnemyStatus::Freeze),"freeze duration independent of timestep");
        s.applyEnemyStatus(id,EnemyStatus::Freeze,-200);s.applyEnemyStatus(id,EnemyStatus::Freeze,-100);
        check(s.findEnemy(id)->statuses->freeze==200,"negative freeze refresh cannot shorten");
        s.applyEnemyStatus(id,EnemyStatus::Freeze,1);
        check(s.findEnemy(id)->statuses->freeze==120,"native positive-on-extended freeze reapplies cap");
        s.rewardOpen=true;ticks(s,hz,hz);check(s.findEnemy(id)->statuses->freeze==120,"modal pause holds freeze duration");
        s.removeEnemyStatus(id,EnemyStatus::Freeze);check(!s.findEnemy(id)->affectedBy(EnemyStatus::Freeze),"explicit thaw");
        check(!s.applyEnemyStatus(id,EnemyStatus::Freeze,0)&&!s.applyEnemyStatus(id,EnemyStatus::Freeze,18001)&&
              !s.applyEnemyStatus(id,static_cast<EnemyStatus>(999),30),"invalid statuses and durations rejected");
    }
    std::cout<<"FREEZE_DURATION all_five=1 source_cap=1 negative_refresh=1 partition=1 modal=1\n";
}
void posesAndPhysics() {
    for(auto kind:Cohort)for(int hz:{30,60,120}) {
        auto s=fixture();const auto id=spawn(s,kind);ticks(s,2);
        auto &e=*s.findEnemy(id);e.velocity={6,0,0};
        const auto at=e.position;const auto age=e.age,pose=e.animationTime();
        const int walk=e.gaper?e.gaper->walkFrame:0,head=e.gaper?e.gaper->headFrame:0;
        const int blood=e.headless?e.headless->animationTicks:0;
        const auto shots=s.stats.projectiles;
        s.applyEnemyStatus(id,EnemyStatus::Freeze,30);
        ticks(s,hz/30,hz);
        check(std::abs(e.velocity.x-.06f)<.0001f&&std::abs(e.position.x-at.x-.002f)<.0001f,
              "source freeze .01friction endpoint preserves passive movement across timesteps");
        ticks(s,hz-hz/30-1,hz);
        check(e.affectedBy(EnemyStatus::Freeze)&&std::abs(e.animationTime()-pose)<.0001f&&e.animationSpeed()==6,
              "freeze holds animation time and gait amplitude despite changing physical velocity");
        check(!e.gaper||(e.gaper->walkFrame==walk&&e.gaper->headFrame==head),"freeze holds Frowning eyes and Gaper gait");
        check(!e.headless||e.headless->animationTicks==blood,"freeze holds Gusher blood animation");
        check(s.stats.projectiles==shots&&s.roomThreats()==1&&!s.roomClear,"freeze cannot fire or clear room");
        ticks(s,1,hz);
        check(std::abs(e.animationTime()-pose)<.0002f&&std::abs(e.age-age-1)<.0002f,
              "actor lifetime advances but thaw has no animation catch-up jump");
        ticks(s,1,30);check(e.animationTime()>pose,"animation resumes after thaw");
    }
    auto s=fixture();auto id=spawn(s,monsterId(10,1));s.applyEnemyStatus(id,EnemyStatus::Freeze,120);
    ticks(s,5);s.findEnemy(id)->velocity={0,0,30};const auto at=s.findEnemy(id)->position;ticks(s);
    check(s.findEnemy(id)->position.z>at.z,"new impulse can move frozen enemy");
    s.arena.floorProps.push_back({StoryPropKind::Crate,{{-3,-.1f,1},{3,3,3}}});s.arena.rebuildWalls();
    s.findEnemy(id)->velocity={0,0,3000};ticks(s);
    check(!s.arena.blocked(s.findEnemy(id)->position,s.findEnemy(id)->radius),"frozen impulse cannot tunnel through cover");
    std::cout<<"FREEZE_PHYSICS partition=1 passive_friction=1 held_pose=1 no_animation_catchup=1 impulse=1 cover=1\n";
}
void attacks() {
    auto s=fixture();auto id=spawn(s,monsterId(12));
    for(int n=0;n<8&&s.findEnemy(id)->state!=EnemyState::Windup;++n)ticks(s);
    auto &e=*s.findEnemy(id);check(e.state==EnemyState::Windup,"committed Horf fixture");
    ticks(s);const int frame=e.headShooter->attackFrame;const float cooldown=e.cooldown;
    const auto phase=e.headShooter->tick;s.applyEnemyStatus(id,EnemyStatus::Freeze,60);s.player.position={10,.85f,0};
    ticks(s,60);
    check(s.stats.projectiles==0&&e.headShooter->attackFrame==frame&&e.cooldown==cooldown&&e.headShooter->tick==phase+60,
          "freeze holds committed shot/cooldown while source poll phase advances");
    ticks(s,4-frame);
    check(s.stats.projectiles==1&&!s.projectiles.empty()&&s.projectiles.front().velocity.x>20,
          "thawed Horf resumes exact remaining windup and aims at current target");
    const auto projectileAt=s.projectiles.front().position;
    s.applyEnemyStatus(id,EnemyStatus::Freeze,30);ticks(s);
    check(!s.projectiles.empty()&&distance(projectileAt,s.projectiles.front().position)>.1f,
          "freezing shooter does not freeze its already-emitted projectile");
    auto g=fixture();id=spawn(g,monsterId(11));auto &body=*g.findEnemy(id);
    body.headless->initialized=true;body.headless->cooldown=2;body.velocity={3,0,0};
    g.applyEnemyStatus(id,EnemyStatus::Freeze,30);ticks(g,30);
    check(body.headless->cooldown==2&&g.stats.projectiles==0,"freeze holds Gusher reload instead of silently consuming it");
    ticks(g,4);check(g.stats.projectiles==1,"Gusher reload resumes after thaw");
    auto pending=fixture();id=spawn(pending,monsterId(11));auto &p=*pending.findEnemy(id);
    p.headless->initialized=true;p.headless->cooldown=0;p.velocity={60,0,0};pending.limits.projectiles=0;ticks(pending);
    check(p.headless->pendingShots.size()==1,"backpressure fixture");
    pending.applyEnemyStatus(id,EnemyStatus::Freeze,30);pending.limits.projectiles=512;ticks(pending,30);
    check(pending.stats.projectiles==0&&p.headless->pendingShots.size()==1,"freeze preserves selected payload until thaw");
    ticks(pending);check(pending.stats.projectiles==1&&p.headless->pendingShots.empty()&&length(p.velocity)<10,
                        "thaw retries selected payload once without resurrecting old momentum");
    std::cout<<"FREEZE_ATTACKS paused_horf_cast=1 current_aim=1 reload=1 pending_payload=1\n";
}
void stepBoundaries() {
    auto whole=fixture(),split=fixture();
    auto a=spawn(whole,monsterId(12)),b=spawn(split,monsterId(12));
    whole.applyEnemyStatus(a,EnemyStatus::Freeze,1);split.applyEnemyStatus(b,EnemyStatus::Freeze,1);
    whole.step({},.2f);ticks(split,6);
    check(whole.findEnemy(a)->headShooter->tick==split.findEnemy(b)->headShooter->tick&&
          whole.findEnemy(a)->headShooter->attackFrame==split.findEnemy(b)->headShooter->attackFrame,
          "initially frozen Horf retains correct global polling phase through a long thawing step");
    auto s=fixture();a=spawn(s,monsterId(10));ticks(s,1,60);
    const auto pose=s.findEnemy(a)->animationTime();s.applyEnemyStatus(a,EnemyStatus::Freeze,2);ticks(s,1,60);
    check(s.findEnemy(a)->statuses->freeze==1,"mid-source-frame application uses existing actor phase");
    s.applyEnemyStatus(a,EnemyStatus::Freeze,2);check(s.findEnemy(a)->animationTime()==pose,"reapplication does not replace held pose");
    s.removeEnemyStatus(a,EnemyStatus::Freeze);check(std::abs(s.findEnemy(a)->animationTime()-pose)<.0001f,"explicit mid-frame thaw has no pose jump");
    ticks(s,1,60);check(s.findEnemy(a)->animationTime()>pose,"partial source frame resumes");
    std::cout<<"FREEZE_BOUNDARIES long_step_poll_phase=1 partial_frame=1 reapply_pose=1 explicit_thaw=1\n";
}
void interactions() {
    for(auto kind:Cohort) {
        auto s=fixture();const auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Freeze,120);
        s.godMode=false;s.player.position={0,.85f,.3f};ticks(s);
        check(s.player.hp<StartingHealth,"ordinary frozen enemies retain contact damage");
        hit(s,id,24);check(s.findEnemy(id)&&s.findEnemy(id)->hp==8,"freeze grants no armor or damage bonus");
    }
    auto both=fixture();auto id=spawn(both,monsterId(10,1));
    both.applyEnemyStatus(id,EnemyStatus::Fear,20);both.applyEnemyStatus(id,EnemyStatus::Confusion,50);both.applyEnemyStatus(id,EnemyStatus::Freeze,30);
    const auto at=both.findEnemy(id)->position;ticks(both,30);
    check(distance(at,both.findEnemy(id)->position)<.0001f&&!both.findEnemy(id)->affectedBy(EnemyStatus::Fear)&&
          both.findEnemy(id)->statuses->confusion==20,"freeze preempts movement while other status durations expire independently");
    ticks(both);check(both.findEnemy(id)->statuses->confusedTarget.has_value(),"surviving confusion takes over after thaw");
    bool morphed=false;
    for(unsigned seed=0;seed<50&&!morphed;++seed) {
        auto s=fixture();id=spawn(s,monsterId(10,1));s.applyEnemyStatus(id,EnemyStatus::Freeze,100);s.combatRng=Random(seed);hit(s,id,32);
        auto *e=s.findEnemy(id);if(!e||!e->alive||e->monster.type!=11)continue;
        morphed=true;check(e->statuses->freeze==100&&s.stats.kills==0&&s.roomThreats()==1,"same-id decapitation retains freeze and room threat");
        ticks(s,30);check(s.findEnemy(id)->statuses->freeze==70&&s.stats.projectiles==0,"headless child remains frozen with same duration");
        hit(s,id,1000);check(s.stats.kills==1&&!s.applyEnemyStatus(id,EnemyStatus::Freeze,30),"final death rewards once and rejects status");
    }
    check(morphed,"frozen morph witness");
    Simulation rooms(3,1,{},MissionTheme::Canyon);rooms.debugScenario=true;rooms.godMode=true;rooms.enterRoom(1);
    id=rooms.spawnMonster(monsterId(12),rooms.arena.rooms[1].center);rooms.applyEnemyStatus(id,EnemyStatus::Freeze,90);
    const auto pose=rooms.findEnemy(id)->animationTime();rooms.enterRoom(0);ticks(rooms,60);rooms.enterRoom(1);
    auto *e=rooms.findEnemy(id);check(e&&e->statuses->freeze==90&&e->animationTime()==pose,"inactive room holds duration and frozen pose");
    rooms.removeEnemyStatus(id,EnemyStatus::Freeze);check(std::abs(e->animationTime()-pose)<.0001f,"off-room time cannot cause thaw animation jump");
    std::cout<<"FREEZE_INTERACTIONS contact=1 ordinary_damage=1 other_statuses=1 same_id_morph=1 inactive_room=1\n";
}
void configuration() {
    const auto originalLib=defaultMechanics();
    const auto dir=std::filesystem::temp_directory_path()/("dw-freeze-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};
    std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(originalLib->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    const auto file=dir/"first_floor_statuses.mechanics";
    std::ifstream in(file);const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](const std::string &replacement) {
        auto text=original;const std::string needle="freeze_effect 12.0.0 120 .01";
        const auto at=text.find(needle);check(at!=text.npos,"freeze profile fixture");
        text.replace(at,needle.size(),replacement);std::ofstream(file)<<text;return MechanicsLibrary::load(dir);
    };
    auto s=fixture();auto id=spawn(s,monsterId(12));s.content=edit("freeze_effect 12.0.0 15 .2");
    s.findEnemy(id)->velocity={6,0,0};s.applyEnemyStatus(id,EnemyStatus::Freeze,120);ticks(s);
    check(s.findEnemy(id)->statuses->freeze==14&&std::abs(s.findEnemy(id)->velocity.x-1.2f)<.0001f,"external freeze cap and friction drive real simulation");
    check(originalLib->enemyStatuses(monsterId(12))->freeze->capFrames==120&&s.content->fingerprint()!=originalLib->fingerprint(),"reload remains immutable and fingerprinted");
    s.content=edit("# freeze disabled for Horf");s.removeEnemyStatus(id,EnemyStatus::Freeze);
    check(!s.applyEnemyStatus(id,EnemyStatus::Freeze,30)&&s.applyEnemyStatus(id,EnemyStatus::Fear,30),"freeze has independent opt-in support");
    for(const auto *value:{"freeze_effect 12.0.0 0 .01","freeze_effect 12.0.0 120 0","freeze_effect 12.0.0 120 1",
            "freeze_effect 12.0.0 120 nan","freeze_effect 13.0.0 120 .01",
            "freeze_effect 12.0.0 120 .01\nfreeze_effect 12.0.0 120 .01"}) {
        bool rejected=false;try{edit(value);}catch(const std::exception&){rejected=true;}check(rejected,"invalid freeze contract rejected");
    }
    std::cout<<"FREEZE_CONTENT cap_and_motion=1 immutable_reload=1 opt_in=1 rejected_contracts=6\n";
}
}
int main(){try{durationAndPause();posesAndPhysics();attacks();stepBoundaries();interactions();configuration();std::cout<<"First-floor freeze contracts passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
