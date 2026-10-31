#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b,float epsilon=.001f){return std::abs(a-b)<epsilon;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={0,.85f,10};return s;
}
void ticks(Simulation &s,int n=1,int hz=30){for(int i=0;i<n;++i)s.step({},1.f/hz);}
EntityId spawn(Simulation &s,MonsterId kind){const auto id=s.spawnMonster(kind,{0,.85f,0});s.findEnemy(id)->cooldown=0;return id;}
void hit(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
const std::array<MonsterId,5> Cohort{{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1),monsterId(12)}};
void durations() {
    for(auto kind:Cohort)for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Slow,90);s.applyEnemyStatus(id,EnemyStatus::Slow,90);
        check(s.findEnemy(id)->statuses->slow==180,"Slow adds past120 instead of using Freeze cap");
        ticks(s,hz,hz);auto &e=*s.findEnemy(id);
        check(e.statuses->slow==150&&near(e.age,1)&&near(e.animationTime(),.5f),"status counts real time while animation uses half time");
        s.applyEnemyStatus(id,EnemyStatus::Slow,-500);
        check(e.statuses->slow==2,"negative Slowing assigns2 even when it shortens existing duration");
        ticks(s,2*hz/30-1,hz);check(e.affectedBy(EnemyStatus::Slow),"negative refresh remains until expiry");
        ticks(s,1,hz);check(!e.affectedBy(EnemyStatus::Slow),"Slow expiry partition stable");
        const float pose=e.animationTime();ticks(s,hz,hz);check(near(e.animationTime()-pose,1),"animation resumes normal rate without catchup");
        s.applyEnemyStatus(id,EnemyStatus::Slow,18000);s.applyEnemyStatus(id,EnemyStatus::Slow,18000);
        check(e.statuses->slow==36000,"application bound is not an accumulated duration cap");
        s.rewardOpen=true;ticks(s,hz,hz);check(e.statuses->slow==36000,"modal pause holds duration");
        s.removeEnemyStatus(id,EnemyStatus::Slow);check(!e.affectedBy(EnemyStatus::Slow),"explicit removal");
    }
    auto s=fixture();auto id=spawn(s,monsterId(13));check(!s.applyEnemyStatus(id,EnemyStatus::Slow,30),"unreviewed controller rejects Slow");
    std::cout<<"SLOW_DURATION additive_uncapped=1 negative_assigns2=1 partition=1 animation_rate=1 pause=1\n";
}
void motion() {
    for(auto kind:{monsterId(10,1),monsterId(11,1),monsterId(12)})for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,kind);auto &e=*s.findEnemy(id);e.velocity={3,0,0};
        if(e.headless){e.headless->initialized=true;e.headless->targetReady=true;e.headless->destination={0,.85f,40};}
        s.applyEnemyStatus(id,EnemyStatus::Slow,120);ticks(s,hz/30,hz);
        const float q=kind.type==11?.75f:.7f,den=q+.5f-q*.5f;
        const float impulse=kind.type==10?.497999996f*2:kind.type==11?.5f:0;
        const float vx=3*q/den,vz=3*impulse*.5f/den;
        check(near(e.velocity.x,vx)&&near(e.velocity.z,vz)&&near(e.position.x,vx*.5f/30)&&near(e.position.z,vz*.5f/30),
              "source rational friction and scaled force/displacement match independent first-frame calculation");
    }
    for(auto kind:{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1)}) {
        Vector3 reference{};
        for(int hz:{30,60,120}) {
            auto s=fixture();auto id=spawn(s,kind);s.player.position={0,.85f,60};s.applyEnemyStatus(id,EnemyStatus::Slow,120);
            ticks(s,2*hz,hz);const auto &e=*s.findEnemy(id);
            check(!s.arena.blocked(e.position,e.radius),"slowed body stays on legal floor");
            if(hz==30)reference=e.position;else check(distance(reference,e.position)<.025f,"slowed pursuit/wander agree across timestep partitions");
        }
    }
    for(auto kind:{monsterId(10,1),monsterId(11,1)}) {
        auto s=fixture();auto id=spawn(s,kind);auto &e=*s.findEnemy(id);e.velocity={3,0,0};if(e.headless)e.headless->initialized=true;
        s.applyEnemyStatus(id,EnemyStatus::Slow,120);s.applyEnemyStatus(id,EnemyStatus::Fear,120);
        auto &f=e.statuses->flee;f.evadeChecks=3;f.targetReady=true;f.destination={0,.85f,-40};e.path={f.destination};
        ticks(s);const float q=kind.type==10?.56f:.42f,den=q+.5f-q*.5f;
        check(near(e.velocity.x,3*q/den)&&near(e.velocity.z,-5.1792f*.5f/den),"fear uses total friction with Slow force adjustment");
    }
    auto both=fixture();auto id=spawn(both,monsterId(12));both.findEnemy(id)->velocity={6,0,0};
    both.applyEnemyStatus(id,EnemyStatus::Slow,90);both.applyEnemyStatus(id,EnemyStatus::Freeze,1);ticks(both);
    check(near(both.findEnemy(id)->velocity.x,6*.01f/.505f)&&near(both.findEnemy(id)->position.x,6*.01f/.505f*.5f/30),
          "Freeze and Slow combine native friction and time scale");
    auto cover=fixture();id=spawn(cover,monsterId(10,1));cover.applyEnemyStatus(id,EnemyStatus::Slow,120);
    cover.arena.floorProps.push_back({StoryPropKind::Crate,{{-3,-.1f,4},{3,3,6}}});cover.arena.rebuildWalls();
    for(int n=0;n<100;++n){ticks(cover);check(!cover.arena.blocked(cover.findEnemy(id)->position,cover.findEnemy(id)->radius),"slowed path respects physical cover");}
    std::cout<<"SLOW_MOTION source_force_friction=1 displacement=1 partition=1 fear=1 freeze=1 cover=1\n";
}
void attacksAndAnimation() {
    auto normal=fixture(),slow=fixture();auto a=spawn(normal,monsterId(12)),b=spawn(slow,monsterId(12));slow.applyEnemyStatus(b,EnemyStatus::Slow,180);
    int acquired=0;while(acquired<8&&normal.findEnemy(a)->state!=EnemyState::Windup){ticks(normal);ticks(slow);++acquired;}
    check(normal.findEnemy(a)->state==EnemyState::Windup&&slow.findEnemy(b)->state==EnemyState::Windup,
          "Slow retains7-frame acquisition poll schedule");
    ticks(slow,7);check(slow.stats.projectiles==0&&slow.findEnemy(b)->headShooter->attackFrame==3,"slowed Shoot4 waits8real updates");
    ticks(slow);check(slow.stats.projectiles==1&&slow.findEnemy(b)->headShooter->attackFrame==4&&near(slow.findEnemy(b)->cooldown,24.f/30),
                      "Slow advances animation and reload by logical frames");
    slow.player.position={50,.85f,50};ticks(slow,31);check(slow.findEnemy(b)->state==EnemyState::Windup,"slowed recovery lasts full40real updates");
    ticks(slow);check(slow.findEnemy(b)->state==EnemyState::Ready,"slowed recovery completes without reset");
    auto g=fixture();a=spawn(g,monsterId(11));auto &e=*g.findEnemy(a);e.headless->initialized=true;e.headless->cooldown=2;e.velocity={3,0,0};
    g.applyEnemyStatus(a,EnemyStatus::Slow,120);ticks(g);
    check(e.headless->cooldown==2&&e.headless->animationTicks==0,"first half logical frame does not decrement or animate");
    ticks(g,3);check(e.headless->cooldown==0&&g.stats.projectiles==0&&e.headless->animationTicks==2,"Gusher reaches zero without same-tick shot");
    ticks(g);check(g.stats.projectiles==1,"Gusher checks due shot on next real AI update, not only next logical frame");
    auto f=fixture();a=spawn(f,monsterId(10));f.applyEnemyStatus(a,EnemyStatus::Slow,120);ticks(f,2);
    check(f.findEnemy(a)->gaper->headFrame==0,"Frowning wake animation starts its own half-speed phase");ticks(f);
    check(f.findEnemy(a)->gaper->headFrame==1,"Frowning eyes advance after two slowed wake updates");
    auto whole=fixture(),split=fixture();a=spawn(whole,monsterId(12));b=spawn(split,monsterId(12));
    whole.applyEnemyStatus(a,EnemyStatus::Slow,2);split.applyEnemyStatus(b,EnemyStatus::Slow,2);whole.step({},.2f);ticks(split,6);
    check(whole.findEnemy(a)->headShooter->tick==split.findEnemy(b)->headShooter->tick&&
          whole.findEnemy(a)->headShooter->attackFrame==split.findEnemy(b)->headShooter->attackFrame,
          "long step across Slow expiry retains correct poll and animation phases");
    std::cout<<"SLOW_ATTACKS real_poll=1 logical_cooldown=1 logical_animation=1 due_check=1 wake_phase=1 expiry=1\n";
}
void projectiles() {
    for(auto kind:{monsterId(11),monsterId(12)})for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Slow,180);
        if(auto &e=*s.findEnemy(id);e.headless){e.headless->initialized=true;e.headless->cooldown=0;e.velocity={3,0,0};}
        for(int n=0;n<2*hz&&s.projectiles.empty();++n)ticks(s,1,hz);
        check(!s.projectiles.empty()&&s.projectiles.front().sourceTimeScale==.5f,"new shot inherits persistent slowed flag");
        auto shot=s.projectiles.front();s.player.position={60,.85f,60};s.removeEnemyStatus(id,EnemyStatus::Slow);hit(s,id,1000);
        float y=shot.position.y,up=shot.velocity.y,x=shot.position.x,z=shot.position.z;
        const float gravity=kind.type==11?22.5f:5.4f;
        for(int n=0;n<12;++n) {
            up=(.9f/.95f)*up-gravity*.5f/30;y+=up*.5f/30;x+=shot.velocity.x*.5f/30;z+=shot.velocity.z*.5f/30;
            ticks(s,hz/30,hz);
            const auto it=std::find_if(s.projectiles.begin(),s.projectiles.end(),[&](const auto &p){return p.id==shot.id;});
            check(it!=s.projectiles.end()&&near(it->position.x,x)&&near(it->position.z,z)&&near(it->position.y,y)&&near(it->velocity.y,up)&&
                  near(it->life,shot.life-float(n+1)*.5f/30)&&it->sourceTimeScale==.5f,
                  "inherited Slow keeps native rational vertical recurrence and half displacement after shooter thaw/death");
        }
    }
    auto s=fixture();auto id=spawn(s,monsterId(11));auto &e=*s.findEnemy(id);e.headless->initialized=true;e.headless->cooldown=0;e.velocity={3,0,0};
    s.limits.projectiles=0;s.applyEnemyStatus(id,EnemyStatus::Slow,60);ticks(s);
    check(e.headless->pendingShots.size()==1&&e.headless->pendingShots.front().projectileTimeScale==.5f,"pending shot captures Slow at selection");
    s.removeEnemyStatus(id,EnemyStatus::Slow);s.limits.projectiles=512;ticks(s);
    check(s.stats.projectiles==1&&s.projectiles.front().sourceTimeScale==.5f,"admission retry keeps selected shot Slow after removal");
    auto old=fixture();id=spawn(old,monsterId(11));auto &body=*old.findEnemy(id);body.headless->initialized=true;body.headless->cooldown=0;body.velocity={3,0,0};ticks(old);
    old.applyEnemyStatus(id,EnemyStatus::Slow,120);ticks(old);check(old.projectiles.front().sourceTimeScale==1,"existing projectiles do not acquire shooter's later Slow");
    auto damage=fixture();damage.godMode=false;id=spawn(damage,monsterId(12));damage.applyEnemyStatus(id,EnemyStatus::Slow,180);
    for(int n=0;n<150&&damage.player.hp==StartingHealth;++n)ticks(damage);
    check(near(damage.player.hp,87.5f),"slowed projectile retains ordinary damage and hits standing player");
    std::cout<<"SLOW_PROJECTILES inherited_flag=1 rational_flight=1 partition=1 lifetime=1 owner_independent=1 selected_payload=1 damage=1\n";
}
void lifecycle() {
    for(auto kind:Cohort) {
        auto s=fixture();auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Slow,120);s.godMode=false;s.player.position={0,.85f,.3f};ticks(s);
        check(s.player.hp<StartingHealth,"Slow retains contact damage");hit(s,id,24);check(s.findEnemy(id)->hp==8,"Slow does not modify incoming damage");
    }
    bool morphed=false;
    for(unsigned seed=0;seed<50&&!morphed;++seed) {
        auto s=fixture();auto id=spawn(s,monsterId(10,1));s.applyEnemyStatus(id,EnemyStatus::Slow,180);s.applyEnemyStatus(id,EnemyStatus::Freeze,30);
        s.combatRng=Random(seed);hit(s,id,32);auto *e=s.findEnemy(id);if(!e||!e->alive||e->monster.type!=11)continue;
        morphed=true;check(e->statuses->slow==180&&e->statuses->freeze==30&&s.stats.kills==0&&s.roomThreats()==1,"same-id headless morph retains both effects");
        ticks(s,30);check(e->statuses->slow==150&&!e->affectedBy(EnemyStatus::Freeze)&&e->headless->animationTicks==0,"Slow duration continues while frozen animation holds");
        ticks(s,2);check(e->headless->animationTicks==1,"headless animation resumes at surviving Slow rate");
    }
    check(morphed,"slow morph witness");
    Simulation s(3,1,{},MissionTheme::Canyon);s.debugScenario=true;s.godMode=true;s.enterRoom(1);auto id=s.spawnMonster(monsterId(12),s.arena.rooms[1].center);
    s.applyEnemyStatus(id,EnemyStatus::Slow,90);s.enterRoom(0);ticks(s,60);s.enterRoom(1);
    check(s.findEnemy(id)->statuses->slow==90,"inactive residents preserve Slow without catchup");
    std::cout<<"SLOW_LIFECYCLE contacts=1 damage=1 morph=1 combined_freeze=1 room_storage=1\n";
}
void configuration() {
    const auto originalLib=defaultMechanics();
    const auto dir=std::filesystem::temp_directory_path()/("dw-slow-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(originalLib->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    const auto file=dir/"first_floor_statuses.mechanics";std::ifstream in(file);const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](const std::string &replacement) {
        auto text=original;const std::string needle="slow_effect 12.0.0 .5 .5 2";const auto at=text.find(needle);check(at!=text.npos,"slow profile fixture");
        text.replace(at,needle.size(),replacement);std::ofstream(file)<<text;return MechanicsLibrary::load(dir);
    };
    auto s=fixture();auto id=spawn(s,monsterId(12));s.content=edit("slow_effect 12.0.0 .25 .75 4");s.findEnemy(id)->velocity={6,0,0};s.applyEnemyStatus(id,EnemyStatus::Slow,120);ticks(s);
    check(near(s.findEnemy(id)->velocity.x,6*.7f/.775f)&&near(s.findEnemy(id)->position.x,6*.7f/.775f*.25f/30),"external actor scale affects actual physics");
    s.findEnemy(id)->velocity={};for(int n=0;n<60&&s.projectiles.empty();++n)ticks(s);
    check(!s.projectiles.empty()&&s.projectiles.front().sourceTimeScale==.75f,"independent external shot time scale applied");
    s.applyEnemyStatus(id,EnemyStatus::Slow,-1);check(s.findEnemy(id)->statuses->slow==4,"external refresh duration applied");
    check(originalLib->enemyStatuses(monsterId(12))->slow->timeScale==.5f&&originalLib->fingerprint()!=s.content->fingerprint(),"immutable snapshot reload changes fingerprint");
    s.removeEnemyStatus(id,EnemyStatus::Slow);s.content=edit("# no slow profile");check(!s.applyEnemyStatus(id,EnemyStatus::Slow,30),"Slow independently opt-in");
    for(const auto *value:{"slow_effect 12.0.0 0 .5 2","slow_effect 12.0.0 1 .5 2","slow_effect 12.0.0 .5 nan 2",
        "slow_effect 12.0.0 .5 .5 0","slow_effect 13.0.0 .5 .5 2","slow_effect 12.0.0 .5 .5 2\nslow_effect 12.0.0 .5 .5 2"}) {
        bool rejected=false;try{edit(value);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or unsupported Slow profile rejected");
    }
    std::cout<<"SLOW_CONTENT actor_and_shot_scales=1 refresh=1 immutable_reload=1 opt_in=1 rejected_contracts=6\n";
}
}
int main(){try{durations();motion();attacksAndAnimation();projectiles();lifecycle();configuration();std::cout<<"First-floor Slow contracts passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
