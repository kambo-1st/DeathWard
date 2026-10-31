#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
struct Pack {
    std::filesystem::path dir=std::filesystem::temp_directory_path()/("dw-tainted-pooter-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
        std::ifstream in(dir/"buzz_flies.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(dir);}
    std::shared_ptr<const MechanicsLibrary> load(std::string text){std::ofstream(dir/"buzz_flies.mechanics")<<text;return MechanicsLibrary::load(dir);}
};
std::string replace(std::string s,const std::string &from,const std::string &to){auto at=s.find(from);check(at!=s.npos,"fixture profile exists");s.replace(at,from.size(),to);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int frames=1){for(int i=0;i<frames;++i)s.step({});}
EntityId spawn(Simulation &s){auto id=s.spawnMonster(monsterId(14,2),{0,.85f,0});s.findEnemy(id)->cooldown=0;return id;}
void acquire(Simulation &s,EntityId id){for(int n=0;n<16&&s.findEnemy(id)->state!=EnemyState::Windup;++n)tick(s);check(s.findEnemy(id)->state==EnemyState::Windup,"acquire within seven source frames");}
void shooter() {
    Pack pack;const auto text=replace(pack.original,"buzz_fly 14.2.0 .1 5 .7 .6 .4 .6 .06 3 24","buzz_fly 14.2.0 .1 5 0 0 .4 .6 0 3 24");
    const auto lib=pack.load(text);auto s=fixture(lib);const auto id=spawn(s);
    check(near(s.findEnemy(id)->hp,240)&&s.roomThreats()==1,"Tainted source75HPx3.2 and one ordinary threat");
    acquire(s,id);const auto began=s.stats.duration;tick(s,11);check(s.projectiles.empty(),"four-shot volley waits for Shoot6");
    s.player.position={25,.85f,0};tick(s);check(s.projectiles.size()==4,"four physical shots emitted together at current target");
    const std::array<Vector2,4> coefficients{{{.99f,.1668f},{.99f,-.1668f},{.8226f,.43956f},{.8226f,-.43956f}}};
    for(size_t i=0;i<4;++i) {
        const auto &p=s.projectiles[i];check(near(p.velocity.x,21*coefficients[i].x)&&near(p.velocity.z,21*coefficients[i].y),"native mode4 coefficients preserve outer slowdown and spread1.2");
        check(p.kind==ProjectileKind::SplitShot&&p.impactSplit&&near(p.radius,.308f)&&near(p.damage,10)&&p.context.sourceEntity==id,"large root carries split snapshot and attribution");
    }
    tick(s,16);check(s.findEnemy(id)->state==EnemyState::Ready,"full14-frame recovery");s.player.position={0,.85f,10};
    while(s.findEnemy(id)->state!=EnemyState::Windup&&s.stats.duration-began<3)tick(s);
    check(std::abs(s.stats.duration-began-63./30)<.0001,"63-source-frame delay starts at acquisition");
    for(int mode=0;mode<3;++mode) {
        auto q=fixture(lib);auto owner=spawn(q);
        if(mode==0)q.limits.projectiles=3;if(mode==1)q.limits.queuedEvents=3;if(mode==2)q.limits.eventsPerChain=0;
        tick(q,45);check(q.stats.projectiles==0&&q.findEnemy(owner)->buzz->attackFrame==6,"whole four-shot volley waits under bounded capacity");
        q.limits.projectiles=512;q.limits.queuedEvents=16384;q.limits.eventsPerChain=256;tick(q,2);
        check(q.projectiles.size()==4,"retained volley admitted once");
    }
    auto calm=fixture();const auto owner=spawn(calm);calm.grant(parseItemKey("isaac:collectible:9"));tick(calm,180);
    check(calm.stats.projectiles==0&&planarDistance(calm.findEnemy(owner)->position,{0,.85f,0})>.2f&&calm.roomThreats()==1,"native Skatole branch also suppresses Tainted shooting without stopping buzz");
    calm.godMode=false;calm.player.position=calm.findEnemy(owner)->position;tick(calm);check(near(calm.player.hp,StartingHealth),"Tainted touch remains harmless");
    auto dying=fixture(lib);auto victim=spawn(dying);acquire(dying,victim);
    Event hit;hit.type=EventType::Damage;hit.target=victim;hit.damage=10000;dying.queueRoot(hit);dying.drainEvents();tick(dying,30);
    check(dying.stats.projectiles==0&&dying.stats.kills==1&&dying.roomThreats()==0,"death during windup cancels all four shots");
    auto released=fixture(lib);auto deadOwner=spawn(released);tick(released,32);
    check(released.projectiles.size()==4,"actual owner emits full volley before death");
    hit.target=deadOwner;released.queueRoot(hit);released.drainEvents();released.player.position={-25,.85f,-25};tick(released,150);
    check(released.stats.projectiles==12&&released.stats.kills==1,"owner death does not cancel four released roots or their eight children");
    std::cout<<"PASS Tainted Pooter source health, four-shot coefficients, Shoot6/Attack14/delay63, atomic volley, harmless contact and Skatole\n";
}
EntityId rootShot(Simulation &s,float life=5) {
    Event shot;shot.hostile=true;shot.context.sourceEntity=4000;shot.position={0,.85f,0};shot.origin=shot.position;shot.direction={0,0,1};
    shot.speed=10;shot.damage=10;shot.projectileKind=ProjectileKind::SplitShot;shot.projectileRadius=.308f;shot.projectileLife=life;
    s.queueRoot(shot);s.drainEvents();return s.projectiles.back().id;
}
void wall(Simulation &s){s.arena.obstacles.push_back({{-20,0,3},{20,4,4}});s.arena.rebuildWalls();}
void splitImpacts() {
    auto s=fixture();wall(s);rootShot(s);
    for(int n=0;n<60&&s.stats.projectiles<3;++n)tick(s);
    check(s.projectiles.size()==2&&s.stats.projectiles==3,"physical obstacle impact creates exactly two children");
    for(const auto &p:s.projectiles) {
        check(p.kind==ProjectileKind::Bullet&&!p.impactSplit&&near(length(p.velocity),30)&&near(p.radius,.22f)&&near(p.damage,10),"children use source speed/default size and cannot recurse");
        check(near(dot(unit(p.velocity),{0,0,-1}),std::cos(24*Pi/180))&&p.position.z<2&&p.context.sourceEntity==4000,"children travel backward24degrees with native offset and retain removed-source attribution");
        check(!s.arena.blocked(p.position,p.radius),"children are born on clear side of obstacle");
    }
    for(auto &p:s.projectiles)p.life=0;tick(s);check(s.stats.projectiles==3&&s.projectiles.empty(),"children have no recursive split");
    for(bool cancel:{false,true}) {
        auto q=fixture();rootShot(q);if(cancel){q.projectiles[0].cancelled=true;q.projectiles[0].alive=false;}else q.projectiles[0].life=0;
        tick(q);check(q.projectiles.empty()&&q.stats.projectiles==1,"timeout or cancellation never triggers an impact split");
    }
    for(bool immune:{false,true}) {
        auto q=fixture();q.godMode=immune;q.player.position={0,.85f,1};rootShot(q);tick(q,4);
        check(q.stats.projectiles==3&&q.projectiles.size()==2&&near(q.player.hp,immune?StartingHealth:87.5f),"native death flag also splits on player collision, including invulnerability");
    }
    for(int mode=0;mode<3;++mode) {
        auto q=fixture();wall(q);const auto parent=rootShot(q);
        if(mode==0)q.limits.projectiles=1;if(mode==1)q.limits.queuedEvents=1;if(mode==2)q.limits.eventsPerChain=0;
        tick(q,25);check(q.projectiles.size()==1&&q.projectiles[0].id==parent&&q.projectiles[0].impactPending&&q.stats.projectiles==1,"split retains a single stopped carrier instead of half a pair");
        const auto at=q.projectiles[0].position;tick(q,6);check(distance(at,q.projectiles[0].position)<.001f,"retained impact does not move or hit again");
        q.limits.projectiles=2;q.limits.queuedEvents=16384;q.limits.eventsPerChain=256;tick(q);
        check(q.projectiles.size()==2&&q.stats.projectiles==3,"exact two-child capacity releases carrier and admits the whole pair");
    }
    // A bounce is not a death; a later safety timeout must not inherit impact.
    auto bounce=fixture();wall(bounce);rootShot(bounce);bounce.projectiles[0].bounces=1;tick(bounce,18);
    check(bounce.projectiles.size()==1&&!bounce.projectiles[0].physicalImpact&&bounce.stats.bounces==1,"live bounce is not a terminal split impact");
    bounce.projectiles[0].life=0;tick(bounce);check(bounce.stats.projectiles==1,"timeout after bounce does not split");
    auto changed=fixture();wall(changed);rootShot(changed);changed.limits.projectiles=1;tick(changed,25);
    check(changed.projectiles[0].impactPending,"impact retained before scenery changes");
    changed.arena.obstacles.push_back({{-20,0,2.1f},{20,4,2.15f}});changed.arena.rebuildWalls();
    changed.limits.projectiles=2;tick(changed);
    check(changed.projectiles.size()==2,"both children still admitted in narrowed space");
    for(const auto &p:changed.projectiles)check(p.position.z>2.15f&& !changed.arena.blocked(p.position,p.radius),"backward spawn offset clips against new thin wall instead of tunnelling");
    std::cout<<"PASS impact-only backward split: wall/player, lifetime/cancellation, no recursion, source identity, queue/chain/projectile pressure and bounce separation\n";
}
void configuration() {
    Pack pack;
    for(const auto &change:std::vector<std::pair<std::string,std::string>>{
        {"buzz_volley 14.2.0 4 .99 .1668 .99 -.1668 .8226 .43956 .8226 -.43956","buzz_volley 14.2.0 4 0 .1668 .99 -.1668 .8226 .43956 .8226 -.43956"},
        {"buzz_back_split 14.2.0 .308 24 30 10 .22 1 5","buzz_back_split 14.2.0 .308 90 30 10 .22 1 5"},
        {"buzz_back_split 14.2.0 .308 24 30 10 .22 1 5","buzz_back_split 14.2.0 .308 24 30 10 .4 1 5"},
        {"buzz_back_split 14.2.0 .308 24 30 10 .22 1 5","buzz_back_split 13.0.0 .308 24 30 10 .22 1 5"}}) {
        bool rejected=false;try{pack.load(replace(pack.original,change.first,change.second));}catch(...){rejected=true;}check(rejected,"invalid volley/split or nonshooter rejected");
    }
    auto before=pack.load(pack.original);auto live=fixture(before);spawn(live);tick(live,32);
    check(!live.projectiles.empty(),"live projectile exists before reload");
    const float angle=live.projectiles.front().impactSplit->angle;
    auto after=pack.load(replace(pack.original,"buzz_back_split 14.2.0 .308 24 30 10 .22 1 5","buzz_back_split 14.2.0 .308 30 25 10 .22 1 5"));
    check(before->fingerprint()!=after->fingerprint()&&near(angle,24*Pi/180)&&near(live.projectiles.front().impactSplit->angle,angle)&&
        near(after->buzzFly(monsterId(14,2))->impactSplit->angle,30*Pi/180),"external reload preserves both live content and projectile birth snapshot");
    for(int band=0;band<4;++band)for(int pattern=0;pattern<4;++pattern) {
        const auto &pool=before->encounterPool(band,EncounterPattern(pattern));
        for(const auto &entry:pool.basics)check(entry.monster!=monsterId(14,2)||entry.weight==0,"Ascent enemy excluded from ordinary basic pools");
        for(const auto &entry:pool.specialists)check(entry.monster!=monsterId(14,2)||entry.weight==0,"Ascent enemy excluded from ordinary specialist pools");
    }
    std::cout<<"PASS external validation/snapshots and no accidental ordinary-pool placement; dedicated Ascent route remains pending\n";
}
}
int main(){try{shooter();splitImpacts();configuration();std::cout<<"PASS Tainted Pooter and reusable impact splitting\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
