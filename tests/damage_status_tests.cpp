#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
void near(float a,float b,const char *message){check(std::abs(a-b)<.003f,message);}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={0,.85f,10};return s;
}
void ticks(Simulation &s,int count=1,int hz=30){for(int n=0;n<count;++n)s.step({},1.f/hz);}
EntityId spawn(Simulation &s,MonsterId kind,bool durable=true){const auto id=s.spawnMonster(kind,{0,.85f,0});if(durable)s.findEnemy(id)->hp=s.findEnemy(id)->maxHp=1000;return id;}
DamageStatusRuntime &state(Simulation &s,EntityId id,EnemyStatus status){auto &r=*s.findEnemy(id)->statuses;return status==EnemyStatus::Poison?r.poison:r.burn;}
void hit(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
const std::array<MonsterId,5> Cohort{{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1),monsterId(12)}};
void timing() {
    for(auto kind:Cohort)for(auto status:{EnemyStatus::Poison,EnemyStatus::Burn})for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,kind);const int unit=hz/30;
        check(s.applyEnemyStatus(id,status,120,8),"damage status opt-in applies");
        ticks(s,unit,hz);near(s.stats.damageDealt,0,"no first-update damage");
        ticks(s,unit,hz);near(s.stats.damageDealt,8,"first damage on source update2");
        ticks(s,19*unit,hz);near(s.stats.damageDealt,8,"no early recurring tick");
        ticks(s,unit,hz);near(s.stats.damageDealt,16,"second damage on update22");
        ticks(s,98*unit,hz);near(s.stats.damageDealt,48,"120duration delivers exactly6ticks at all rates");
        check(!s.findEnemy(id)->affectedBy(status),"duration expires independently of step partition");
        ticks(s,20*unit,hz);near(s.stats.damageDealt,48,"no post-expiry damage");
    }
    for(int duration:{1,2,3,22,23,42,43}) {
        auto s=fixture();auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,EnemyStatus::Poison,duration,8);ticks(s,65);
        near(s.stats.damageDealt,float(duration<3?0:1+(duration-3)/20)*8,"expiry-before-tick duration boundary");
    }
    std::cout<<"DOT_TIMING all_five=1 poison_and_burn=1 rates_30_60_120=1 expiry_before_tick=1 six_ticks=1\n";
}
void reapplication() {
    for(auto status:{EnemyStatus::Poison,EnemyStatus::Burn}) {
        auto s=fixture();auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,status,90,8);ticks(s,5);
        const auto elapsed=state(s,id,status).elapsed;s.applyEnemyStatus(id,status,90,12);
        check(state(s,id,status).frames==120&&state(s,id,status).elapsed==elapsed,"reapply caps duration but preserves tick phase");
        s.applyEnemyStatus(id,status,1,7);near(state(s,id,status).damage,12,"weaker application cannot lower damage");
        ticks(s,17);near(s.stats.damageDealt,20,"stronger damage on original next due tick");
        s.applyEnemyStatus(id,status,-200,9);s.applyEnemyStatus(id,status,-100,9);
        check(state(s,id,status).frames==200,"negative duration keeps maximum extended duration");
        s.applyEnemyStatus(id,status,1,9);check(state(s,id,status).frames==120,"positive after extended reapplies120cap");
        s.removeEnemyStatus(id,status);const auto damage=s.stats.damageDealt;ticks(s,25);near(s.stats.damageDealt,damage,"explicit removal stops future ticks");
        s.applyEnemyStatus(id,status,3,1);ticks(s,2);near(s.stats.damageDealt,damage+6.4f,"new application resets phase and source2HP minimum");
        ticks(s);near(state(s,id,status).damage,6.4f,"expiry resets stored damage floor");
    }
    auto s=fixture();auto id=spawn(s,monsterId(12));s.applyEnemyStatus(id,EnemyStatus::Poison,3);ticks(s,2);
    near(s.stats.damageDealt,24,"zero damage resolves unchanged player build damage");
    Context environment;environment.damageSource=DamageSource::Environment;
    s.applyEnemyStatus(id,EnemyStatus::Burn,3,-1,environment);ticks(s,2);near(s.stats.damageDealt,30.4f,"non-player unspecified power uses source2HP floor");
    auto producer=spawn(s,monsterId(12));Context owner;owner.sourceEntity=producer;
    s.applyEnemyStatus(id,EnemyStatus::Poison,90,11,owner);
    check(state(s,id,EnemyStatus::Poison).source.damageSource==DamageSource::Enemy,"producer affiliation snapshots on application");
    hit(s,producer,2000);ticks(s,20);
    check(state(s,id,EnemyStatus::Poison).source.sourceEntity==producer&&state(s,id,EnemyStatus::Poison).source.damageSource==DamageSource::Enemy,"source snapshot survives producer death");
    std::cout<<"DOT_REAPPLY cap=1 extended=1 phase=1 strongest_damage=1 source_floor=1 source_snapshot=1\n";
}
void combinationsAndPause() {
    for(auto kind:Cohort) {
        auto s=fixture();auto id=spawn(s,kind);s.applyEnemyStatus(id,EnemyStatus::Poison,90,8);s.applyEnemyStatus(id,EnemyStatus::Burn,43,10);
        s.applyEnemyStatus(id,EnemyStatus::Slow,120);s.applyEnemyStatus(id,EnemyStatus::Freeze,120);
        const auto at=s.findEnemy(id)->position;const auto pose=s.findEnemy(id)->animationTime();ticks(s,43);
        near(s.stats.damageDealt,54,"poison and burn stack independently through Freeze and Slow");
        check(distance(at,s.findEnemy(id)->position)<.001f&&s.findEnemy(id)->animationTime()==pose,"damage effects do not thaw or animate held body");
        check(state(s,id,EnemyStatus::Poison).frames==47&&!s.findEnemy(id)->affectedBy(EnemyStatus::Burn),"independent damage durations");
        s.rewardOpen=true;const auto damage=s.stats.damageDealt;ticks(s,30);near(s.stats.damageDealt,damage,"modal pause holds damage and timers");
        check(state(s,id,EnemyStatus::Poison).frames==47,"modal preserves poison duration");
    }
    for(auto kind:Cohort) {
        auto s=fixture();auto id=spawn(s,kind,false);s.applyEnemyStatus(id,EnemyStatus::Poison,90,8);
        s.godMode=false;s.player.position={0,.85f,.3f};ticks(s);
        check(s.player.hp<StartingHealth,"poisoned bodies keep contact damage");
        hit(s,id,24);near(s.findEnemy(id)->hp,8,"damage statuses do not alter ordinary incoming24damage");
    }
    auto a=fixture(),b=fixture();auto x=spawn(a,monsterId(11,1)),y=spawn(b,monsterId(11,1));
    a.applyEnemyStatus(x,EnemyStatus::Poison,120,8);b.applyEnemyStatus(y,EnemyStatus::Poison,120,8);
    a.step({},.2f);ticks(b,6);near(a.stats.damageDealt,b.stats.damageDealt,"long step preserves due damage count");
    check(state(a,x,EnemyStatus::Poison).frames==state(b,y,EnemyStatus::Poison).frames,"long step preserves duration");
    for(auto status:{EnemyStatus::Poison,EnemyStatus::Burn}) {
        auto whole=fixture(),split=fixture();auto h=spawn(whole,monsterId(12)),i=spawn(split,monsterId(12));
        whole.applyEnemyStatus(h,status,90,8);split.applyEnemyStatus(i,status,90,8);
        whole.step({},.2f);ticks(split,6);
        check(whole.findEnemy(h)->headShooter->tick==split.findEnemy(i)->headShooter->tick&&
              whole.findEnemy(h)->headShooter->attackFrame==split.findEnemy(i)->headShooter->attackFrame,
              "damage-status subdivision cannot shift initial Horf global acquisition phase");
    }
    auto moving=fixture(),plain=fixture();x=spawn(moving,monsterId(10,1));y=spawn(plain,monsterId(10,1));
    moving.applyEnemyStatus(x,EnemyStatus::Poison,90,8);moving.applyEnemyStatus(x,EnemyStatus::Burn,90,8);ticks(moving,25);ticks(plain,25);
    check(distance(moving.findEnemy(x)->position,plain.findEnemy(y)->position)<.001f,"ordinary damage statuses do not modify movement");
    Simulation rooms(3,1,{},MissionTheme::Canyon);rooms.debugScenario=true;rooms.godMode=true;rooms.enterRoom(1);
    x=rooms.spawnMonster(monsterId(12),rooms.arena.rooms[1].center);rooms.applyEnemyStatus(x,EnemyStatus::Poison,90,6.4f);
    rooms.enterRoom(0);ticks(rooms,60);rooms.enterRoom(1);
    check(state(rooms,x,EnemyStatus::Poison).frames==90&&state(rooms,x,EnemyStatus::Poison).elapsed==0,"inactive room holds duration and tick phase");
    std::cout<<"DOT_COMBINATIONS independent=1 freeze=1 slow=1 modal=1 long_step=1 movement=1 inactive_room=1\n";
}
void mortalityAndCapacity() {
    for(auto kind:Cohort)for(auto status:{EnemyStatus::Poison,EnemyStatus::Burn}) {
        auto s=fixture();auto id=spawn(s,kind,false);s.applyEnemyStatus(id,status,90,1000);ticks(s,2);
        check(!s.findEnemy(id)&&s.stats.kills==1&&s.roomThreats()==0,"periodic lethal overkill removes exactly one threat and rewards once");
        ticks(s,30);check(s.stats.kills==1&&!s.applyEnemyStatus(id,status,30),"dead actor cannot tick or receive status");
    }
    for(auto status:{EnemyStatus::Poison,EnemyStatus::Burn}) {
        bool morphed=false;
        for(unsigned seed=0;seed<50&&!morphed;++seed) {
            auto s=fixture();auto id=spawn(s,monsterId(10,1),false);s.applyEnemyStatus(id,status,90,32);
            s.applyEnemyStatus(id,EnemyStatus::Freeze,120);s.combatRng=Random(seed);ticks(s,2);
            auto *e=s.findEnemy(id);if(!e||e->monster.type!=11)continue;
            morphed=true;check(s.stats.kills==0&&s.roomThreats()==1&&state(s,id,status).frames==88&&state(s,id,status).elapsed==2,"lethal status morph preserves duration,phase,identity and threat");
            ticks(s,19);check(s.findEnemy(id)&&s.stats.kills==0,"headless continuation has no immediate extra damage");
            ticks(s);check(!s.findEnemy(id)&&s.stats.kills==1,"next inherited status tick finishes headless body once");
        }
        check(morphed,"same-entity damage-status morph witness");
    }
    auto s=fixture();auto id=spawn(s,monsterId(12));s.limits.queuedEvents=0;s.applyEnemyStatus(id,EnemyStatus::Poison,3,8);ticks(s,2);
    check(state(s,id,EnemyStatus::Poison).pending.has_value(),"full queue retains due tick");
    const auto duration=state(s,id,EnemyStatus::Poison).frames;ticks(s,60);
    check(state(s,id,EnemyStatus::Poison).frames==duration&&s.stats.damageDealt==0,"backpressure holds only effect clock with bounded storage");
    s.applyEnemyStatus(id,EnemyStatus::Poison,3,16);s.limits.queuedEvents=512;ticks(s);
    near(s.stats.damageDealt,8,"retained tick keeps selected damage despite stronger reapplication");
    ticks(s,30);near(s.stats.damageDealt,8,"retained tick admitted exactly once without extra immediate tick");
    auto both=fixture();id=spawn(both,monsterId(12));both.limits.queuedEvents=0;
    both.applyEnemyStatus(id,EnemyStatus::Poison,3,8);both.applyEnemyStatus(id,EnemyStatus::Burn,3,9);ticks(both,2);
    both.limits.queuedEvents=1;ticks(both,3);near(both.stats.damageDealt,17,"independent pending ticks both survive single-slot event admission");
    std::cout<<"DOT_MORTALITY all_five=1 one_reward=1 morph=1 due_tick_backpressure=1 payload_snapshot=1 independent_retry=1\n";
}
void configuration() {
    const auto originalLib=defaultMechanics();
    const auto dir=std::filesystem::temp_directory_path()/("dw-dot-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(originalLib->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    const auto file=dir/"first_floor_statuses.mechanics";std::ifstream in(file);const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](const std::string &replacement){auto text=original;const std::string needle="damage_status 12.0.0 poison 120 20 2 6.4";const auto at=text.find(needle);check(at!=text.npos,"config fixture");text.replace(at,needle.size(),replacement);std::ofstream(file)<<text;return MechanicsLibrary::load(dir);};
    auto s=fixture();auto id=spawn(s,monsterId(12));s.content=edit("damage_status 12.0.0 poison 30 5 3 2");s.applyEnemyStatus(id,EnemyStatus::Poison,120,1);ticks(s,30);
    near(s.stats.damageDealt,12,"external cap,period,first tick and damage floor drive simulation");
    check(originalLib->enemyStatuses(monsterId(12))->poison->capFrames==120&&s.content->fingerprint()!=originalLib->fingerprint(),"immutable reload fingerprint");
    s.content=edit("# poison disabled");check(!s.applyEnemyStatus(id,EnemyStatus::Poison,30)&&s.applyEnemyStatus(id,EnemyStatus::Burn,30,8),"independent poison opt-in");
    for(const auto *value:{"damage_status 12.0.0 poison 0 20 2 6.4","damage_status 12.0.0 poison 120 0 2 6.4","damage_status 12.0.0 poison 120 20 21 6.4","damage_status 12.0.0 poison 120 20 2 0","damage_status 12.0.0 poison 120 20 2 nan","damage_status 12.0.0 poison 120 20 2 6.4\ndamage_status 12.0.0 poison 120 20 2 6.4","damage_status 12.0.0 invalid 120 20 2 6.4","damage_status 13.0.0 poison 120 20 2 6.4"}) {
        bool rejected=false;try{edit(value);}catch(const std::exception&){rejected=true;}check(rejected,"invalid damage profile rejected");
    }
    std::ofstream(file)<<original;
    std::ofstream(dir/"status_fire_test.mechanics")<<"DEATHWARD_MECHANICS 1\nfire_reaction 12.0.0 any 0 .5 none both fraction\n";
    auto channel=fixture();channel.content=MechanicsLibrary::load(dir);auto target=spawn(channel,monsterId(12));
    for(auto status:{EnemyStatus::Poison,EnemyStatus::Burn})channel.applyEnemyStatus(target,status,3,8);
    ticks(channel,2);near(channel.stats.damageDealt,8,"both statuses use Burning reaction channel, independently of zero flame scale");
    auto invalid=fixture();id=spawn(invalid,monsterId(12));auto fly=spawn(invalid,monsterId(13));
    check(!invalid.applyEnemyStatus(fly,EnemyStatus::Poison,30)&&!invalid.applyEnemyStatus(id,EnemyStatus::Burn,0)&&!invalid.applyEnemyStatus(id,EnemyStatus::Poison,18001)&&!invalid.applyEnemyStatus(id,EnemyStatus::Burn,30,std::numeric_limits<float>::quiet_NaN()),"invalid API requests rejected");
    std::cout<<"DOT_CONFIG external=1 immutable_reload=1 opt_in=1 rejected_profiles=8 invalid_api=1\n";
}
}
int main(){try{timing();reapplication();combinationsAndPause();mortalityAndCapacity();configuration();std::cout<<"First-floor Poison/Burn contracts passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
