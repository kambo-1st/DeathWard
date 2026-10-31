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
void durationAndSize() {
    for(auto kind:Cohort)for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,kind);auto &e=*s.findEnemy(id);const auto radius=e.radius;
        check(s.applyEnemyStatus(id,EnemyStatus::Shrink,100),"cohort opts into Shrink");s.applyEnemyStatus(id,EnemyStatus::Shrink,100);
        check(e.statuses->shrink==150&&e.statuses->visualScale==1&&e.radius==radius,"cap150 with no immediate visual or first-application collision shrink");
        ticks(s,hz,hz);
        check(e.statuses->shrink==120&&near(e.statuses->visualScale,.333f+.667f*std::pow(5.f/6,30),1e-5f)&&e.radius==radius,
              "real30Hz visual interpolation independent of collision size");
        const auto scale=e.statuses->visualScale;s.applyEnemyStatus(id,EnemyStatus::Shrink,1);
        check(e.radius==radius&&e.statuses->visualScale==scale,"active refresh does not resample collision size or restart transition");
        s.removeEnemyStatus(id,EnemyStatus::Shrink);check(e.radius==radius,"removal immediately restores physical radius");ticks(s,hz/30,hz);
        const auto recovered=scale+(1-scale)/6;
        check(near(e.statuses->visualScale,recovered,1e-5f),"recovery starts on next real source update");
        s.applyEnemyStatus(id,EnemyStatus::Shrink,1);
        check(near(e.radius,radius*recovered),"reapply during recovery samples current visual scale once");ticks(s,hz/30,hz);
        check(!e.affectedBy(EnemyStatus::Shrink)&&e.radius==radius,"expiry restores collision radius after last shrink interpolation");
        s.applyEnemyStatus(id,EnemyStatus::Shrink,-500);check(e.statuses->shrink==500,"negative refresh exceeds cap");
        s.applyEnemyStatus(id,EnemyStatus::Shrink,-1);check(e.statuses->shrink==500,"shorter negative refresh preserves duration");
        s.applyEnemyStatus(id,EnemyStatus::Shrink,1);check(e.statuses->shrink==150,"positive refresh caps extended duration");
        s.rewardOpen=true;const auto held=e.statuses->visualScale;ticks(s,hz,hz);
        check(e.statuses->shrink==150&&e.statuses->visualScale==held,"modal pause holds duration and transition");
        check(!s.applyEnemyStatus(id,EnemyStatus::Shrink,0)&&!s.applyEnemyStatus(id,EnemyStatus::Shrink,18001),"invalid application rejected");
    }
    std::cout<<"SHRINK_TIME cap150=1 negative_max=1 partition=1 visual_recurrence=1 collision_sample=1 expiry=1 pause=1\n";
}
void motionAndAttacks() {
    for(auto kind:{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1)}) {
        auto fear=fixture(),shrink=fixture();auto a=spawn(fear,kind),b=spawn(shrink,kind);
        fear.applyEnemyStatus(a,EnemyStatus::Fear,120);shrink.applyEnemyStatus(b,EnemyStatus::Shrink,120);
        for(int n=0;n<90;++n){ticks(fear);ticks(shrink);check(distance(fear.findEnemy(a)->position,shrink.findEnemy(b)->position)<.001f,"Shrink and Fear share moving-body steering");}
        check(shrink.stats.projectiles==0,"Shrink suppresses new Gusher shots");
        auto &r=*shrink.findEnemy(b)->statuses;r.flee.targetReady=true;r.flee.destination={12,.85f,12};
        shrink.applyEnemyStatus(b,EnemyStatus::Fear,60);check(r.flee.targetReady,"adding Fear to Shrink does not reset shared flee target");
    }
    auto s=fixture();auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,EnemyStatus::Shrink,30);ticks(s,30);
    check(s.stats.projectiles==0&&s.findEnemy(id)->headShooter->attackFrame<0,"Horf cannot acquire during Shrink");ticks(s,15);
    check(s.stats.projectiles==1,"Horf resumes acquisition after expiry");
    auto committed=fixture();id=spawn(committed,monsterId(12));
    while(committed.findEnemy(id)->state!=EnemyState::Windup)ticks(committed);
    committed.applyEnemyStatus(id,EnemyStatus::Shrink,120);ticks(committed,4);
    check(committed.stats.projectiles==1,"committed Horf Shoot4 survives Shrink");
    const auto shotId=committed.projectiles.front().id;hit(committed,id,1000);ticks(committed);
    check(std::any_of(committed.projectiles.begin(),committed.projectiles.end(),[&](const auto &p){return p.id==shotId;}),"emitted shot survives owner death");
    auto pending=fixture();id=spawn(pending,monsterId(11));auto &g=*pending.findEnemy(id);g.headless->initialized=true;g.headless->cooldown=0;g.velocity={3,0,0};
    pending.limits.projectiles=0;ticks(pending);check(g.headless->pendingShots.size()==1,"selected Gusher payload fixture");
    pending.applyEnemyStatus(id,EnemyStatus::Shrink,120);pending.limits.projectiles=512;ticks(pending);
    check(pending.stats.projectiles==1,"selected Gusher shot survives Shrink");
    std::cout<<"SHRINK_AI fear_motion=1 shared_target=1 acquisition=1 committed_shots=1 recovery=1\n";
}
void contactAndDamage() {
    for(auto kind:Cohort)for(int mode=0;mode<3;++mode) {
        auto s=fixture();s.godMode=false;auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Shrink,120);
        hit(s,id,24);check(s.findEnemy(id)->hp==8,"Shrink does not multiply direct damage");
        if(mode==1)s.applyEnemyStatus(id,EnemyStatus::Freeze,60);
        if(mode==2){s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=1;}
        s.player.position=s.findEnemy(id)->position;ticks(s);
        check((!s.findEnemy(id)||!s.findEnemy(id)->alive)&&s.player.hp==StartingHealth&&s.stats.kills==1&&s.roomThreats()==0,
              "contact squashes without player harm, headless morph, or remaining room threat, including frozen/stunned");
        ticks(s,3);check(s.stats.kills==1,"one kill only");
    }
    auto ordinary=fixture();ordinary.godMode=false;auto id=spawn(ordinary,monsterId(12));ordinary.applyEnemyStatus(id,EnemyStatus::Shrink,30);
    ordinary.removeEnemyStatus(id,EnemyStatus::Shrink);ordinary.player.position=ordinary.findEnemy(id)->position;ticks(ordinary);
    check(ordinary.player.hp==StartingHealth-10*EnemyDamageMultiplier&&ordinary.findEnemy(id)->alive,"removed Shrink restores ordinary contact immediately");
    auto pending=fixture();pending.godMode=false;id=spawn(pending,monsterId(11));pending.applyEnemyStatus(id,EnemyStatus::Shrink,1);
    pending.limits.queuedEvents=0;pending.player.position=pending.findEnemy(id)->position;ticks(pending,3);
    check(pending.findEnemy(id)->statuses->squashed&&pending.stats.kills==0&&pending.player.hp==StartingHealth,"bounded queue retains squash intent without harming player");
    pending.removeEnemyStatus(id,EnemyStatus::Shrink);pending.player.position={50,.85f,50};pending.limits.queuedEvents=1024;ticks(pending);
    check(pending.stats.kills==1&&pending.roomThreats()==0,"selected squash survives effect removal/player departure and retries once");
    auto wall=fixture();wall.godMode=false;id=spawn(wall,monsterId(12));wall.applyEnemyStatus(id,EnemyStatus::Shrink,120);
    wall.player.position={0,.85f,.7f};wall.arena.floorProps.push_back({StoryPropKind::Crate,{{-3,-.1f,.3f},{3,3,.4f}}});wall.arena.rebuildWalls();ticks(wall);
    check(wall.findEnemy(id)->alive&&wall.stats.kills==0&&wall.player.hp==StartingHealth,"physical cover prevents squash through walls");
    auto crossed=fixture();crossed.godMode=false;id=spawn(crossed,monsterId(12));crossed.applyEnemyStatus(id,EnemyStatus::Shrink,120);
    crossed.player.position={-3,.85f,0};Input input;input.movement={1,0,0};crossed.step(input,1);
    check(crossed.player.position.x>2&&crossed.stats.kills==1&&crossed.player.hp==StartingHealth,"swept movement squashes when both endpoints miss the body");
    std::cout<<"SHRINK_CONTACT squash=1 no_morph=1 single_reward=1 freeze_stun=1 normal_damage=1 capacity_retry=1 cover=1 swept=1\n";
}
void combinationsAndStorage() {
    for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,EnemyStatus::Shrink,60);s.applyEnemyStatus(id,EnemyStatus::Freeze,60);
        s.applyEnemyStatus(id,EnemyStatus::Slow,60);s.applyEnemyStatus(id,EnemyStatus::Poison,30,7);ticks(s,hz,hz);auto &e=*s.findEnemy(id);
        check(e.statuses->shrink==30&&near(e.statuses->visualScale,.333f+.667f*std::pow(5.f/6,30),1e-5f)&&e.hp==18&&e.animationTime()==0,
              "Shrink transition/expiry and Poison continue during Freeze plus Slow");
    }
    bool witnessed=false;
    for(unsigned seed=0;seed<50&&!witnessed;++seed) {
        auto s=fixture();auto id=spawn(s,monsterId(10,1));s.applyEnemyStatus(id,EnemyStatus::Shrink,120);ticks(s,10);
        const auto scale=s.findEnemy(id)->statuses->visualScale;s.combatRng=Random(seed);hit(s,id,32);auto *e=s.findEnemy(id);
        if(!e||!e->alive||e->monster.type!=11)continue;witnessed=true;
        check(e->statuses->shrink==110&&e->statuses->visualScale==scale&&s.stats.kills==0&&s.roomThreats()==1,"ordinary damage headless morph retains Shrink and identity");
        ticks(s);check(e->statuses->shrink==109,"morphed body continues effect");
    }
    check(witnessed,"headless morph fixture");
    Simulation s(3,1,{},MissionTheme::Canyon);s.debugScenario=true;s.godMode=true;s.enterRoom(1);auto id=s.spawnMonster(monsterId(12),s.arena.rooms[1].center);
    s.applyEnemyStatus(id,EnemyStatus::Shrink,90);s.enterRoom(0);ticks(s,60);s.enterRoom(1);
    check(s.findEnemy(id)->statuses->shrink==90&&s.findEnemy(id)->statuses->visualScale==1,"inactive room holds Shrink and visual scale without catchup");
    std::cout<<"SHRINK_LIFECYCLE freeze_slow_poison=1 ordinary_morph=1 inactive_room=1\n";
}
void configuration() {
    auto base=defaultMechanics();const auto dir=std::filesystem::temp_directory_path()/("dw-shrink-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(base->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    const auto file=dir/"first_floor_statuses.mechanics";std::ifstream input(file);const std::string original(std::istreambuf_iterator<char>(input),{});
    auto edit=[&](const std::string &value){auto text=original;const std::string needle="shrink_effect 12.0.0 150 .333 .166666667";const auto at=text.find(needle);check(at!=text.npos,"external profile fixture");text.replace(at,needle.size(),value);std::ofstream(file)<<text;return MechanicsLibrary::load(dir);};
    auto s=fixture();s.content=edit("shrink_effect 12.0.0 60 .5 .25");auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,EnemyStatus::Shrink,100);ticks(s);
    check(s.findEnemy(id)->statuses->shrink==59&&near(s.findEnemy(id)->statuses->visualScale,.875f),"external cap/scale/approach affect runtime");
    check(base->fingerprint()!=s.content->fingerprint()&&base->enemyStatuses(monsterId(12))->shrink->capFrames==150,"reload snapshot leaves original intact");
    auto unsupported=fixture();id=spawn(unsupported,monsterId(13));check(!unsupported.applyEnemyStatus(id,EnemyStatus::Shrink,30),"unreviewed controller rejects Shrink");
    unsupported.content=edit("# no shrink profile");id=spawn(unsupported,monsterId(12));check(!unsupported.applyEnemyStatus(id,EnemyStatus::Shrink,30),"Shrink independently opt-in");
    for(const auto *bad:{"shrink_effect 12.0.0 0 .333 .1","shrink_effect 12.0.0 150 1 .1","shrink_effect 12.0.0 150 .333 0",
        "shrink_effect 12.0.0 150 nan .1","shrink_effect 12.0.0 150 .333 inf","shrink_effect 13.0.0 150 .333 .1",
        "shrink_effect 12.0.0 150 .333 .1\nshrink_effect 12.0.0 150 .333 .1"}) {
        bool rejected=false;try{edit(bad);}catch(const std::exception&){rejected=true;}check(rejected,"malformed Shrink profile rejected");
    }
    std::cout<<"SHRINK_CONTENT tuning=1 immutable_reload=1 opt_in=1 rejected_contracts=7\n";
}
}
int main(){try{durationAndSize();motionAndAttacks();contactAndDamage();combinationsAndStorage();configuration();std::cout<<"First-floor Shrink contracts passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
