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
bool near(float a,float b,float eps=.01f){return std::abs(a-b)<eps;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,60};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int type=223){return s.spawnMonster(monsterId(type),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount=7,bool execution=false,bool debug=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=amount;h.execution=execution;h.debugExecution=debug;s.queueRoot(h);s.drainEvents();
}
EntityId variant(Simulation &s,int type,int v=0){return s.spawnMonster(monsterId(type,v),{0,.85f,0});}
void acquire(Simulation &s,EntityId id){for(int n=0;n<1000&&s.findEnemy(id)->slide->phase!=1;++n)tick(s);check(s.findEnemy(id)->slide->phase==1,"acquires first windup");}
void corn() {
    float v1=3,v2=3;const float y1=advanceLobHeight(v1,4.5f,1,1.f/30);
    float y2=0;for(int n=0;n<4;++n)y2+=advanceLobHeight(v2,4.5f,1,1.f/120);
    check(near(v1,2.85f,.00001f)&&near(y1,.095f,.00001f)&&near(v1,v2,.00001f)&&near(y1,y2,.00001f),"undamped lob endpoint and fractional composition stay finite");
    auto a=fixture(),b=fixture(),c=fixture();auto x=variant(a,217),y=variant(b,217,1),z=variant(c,217,2);
    for(int n=0;n<200&&a.findEnemy(x)->slide->dashes==0;++n){tick(a);tick(b);tick(c);}
    check(distance(b.findEnemy(y)->velocity,mul(a.findEnemy(x)->velocity,2))<.01f,"Corn ordinary impulse doubles");
    check(distance(c.findEnemy(z)->velocity,a.findEnemy(x)->velocity)<.01f,"Brownie ordinary source branch does not double");
    check(near(b.findEnemy(y)->hp,9.6f)&&near(b.content->monsterHealth(monsterId(217,1),7),9.6f),"Corn HP stays3 source at all stages");
    auto s=fixture();auto id=variant(s,217,3);s.player.position={20,.85f,0};s.player.velocity={0,0,6};
    s.limits.projectiles=0;s.debugScenario=false;damage(s,id,10000);
    check(s.findEnemy(id)&&!s.findEnemy(id)->slide->deathShot.empty()&&s.projectiles.empty(),"Big Corn retains one lethal shot at cap");
    const auto expected=unit(Vector3{20,0,4});s.player.position={-20,.85f,-20};s.player.velocity={};tick(s);
    check(!s.roomClear,"pending death shot gates clear");s.limits.projectiles=10;tick(s);
    check(s.projectiles.size()==1&&dot(unit(horizontal(s.projectiles[0].velocity)),expected)>.9999f,"death prediction snapshots target position and velocity");
    check(s.projectiles[0].kind==ProjectileKind::Yellow&&near(s.projectiles[0].radius,.22f)&&near(length(horizontal(s.projectiles[0].velocity)),30),"one corn projectile at source speed10 converted30");
    for(int n=0;n<200&&!s.roomClear;++n)tick(s);check(s.roomClear,"room clears after death shot lands");
    auto d=fixture();id=variant(d,217,3);damage(d,id,10000,true,true);tick(d);check(d.projectiles.empty(),"debug clear suppresses death shot");
    std::cout<<"CORN impulse=2 Brownie_ordinary=1 HP=1 BigCorn_predictive_death=1 capacity=1 clear=1 debug=1\n";
}
void drips() {
    bool chain=false,aim=false,random=false;
    for(uint64_t seed=0;seed<12&&!(chain&&aim&&random);++seed) {
        auto s=fixture();s.combatRng=Random(seed);auto id=variant(s,870);s.player.position={70,.85f,0};
        auto &e=*s.findEnemy(id);auto &r=*e.slide;
        for(int n=0;n<1200;++n){auto old=r;tick(s);
            if(r.dashes>old.dashes&&old.dashes==0){const float speed=length(e.velocity);check(speed>=13.5f-.01f&&speed<=21.6f+.01f,"Drip source5..8 with.9 retention");if(std::abs(e.velocity.z)<.001f&&e.velocity.x>0)aim=true;else random=true;}
            if(r.chains>old.chains){check(r.frame==10&&r.phase==3,"Drip chains at animation10");const auto dashes=r.dashes;tick(s);check(r.dashes==dashes+1&&r.phase==2&&r.frame==0,"chain launches next update without idle chance");chain=true;break;}
        }
    }
    check(chain&&aim&&random,"Drip ordinary aimed, random and chain branches reachable");
    std::cout<<"DRIP distinct_impulse=1 aimed_and_random=1 chain_frame10=1\n";
}
void splurt() {
    auto s=fixture();auto id=variant(s,871);auto &e=*s.findEnemy(id);auto &r=*e.slide;acquire(s,id);tick(s,35);
    check(r.launches==0,"first windup waits36");s.player.position={60,.85f,0};tick(s);check(r.launches==1&&near(e.velocity.x,60),"first launch36");
    tick(s,4);check(r.phase==2&&!r.secondDash,"first sliding phase");
    for(int n=0;n<200&&!(r.phase==1&&r.secondDash);++n)tick(s);
    check(r.phase==1&&r.frame==0&&r.secondDash,"slowing starts second windup");
    tick(s,7);check(r.launches==1,"second windup waits8");s.player.position={e.position.x,.85f,-60};const auto old=e.velocity;tick(s);
    check(r.launches==2&&e.velocity.z<-59&&near(e.velocity.x,old.x*.95f),"second launch retargets and preserves residual momentum");
    tick(s,4);check(r.phase==2&&r.secondDash,"second Attack02 completes12");
    for(int n=0;n<250&&r.phase!=0;++n)tick(s);check(r.phase==0&&r.launches==2,"exactly two charges before idle");
    auto split=fixture();auto si=variant(split,871);tick(split,150);auto same=fixture();auto sj=variant(same,871);tick(same,600,1.f/120);
    check(distance(split.findEnemy(si)->position,same.findEnemy(sj)->position)<.03f,"Splurt30/120Hz agreement");
    for(int mode=0;mode<2;++mode){auto birth=fixture();auto bi=variant(birth,871);birth.debugScenario=false;birth.limits.enemies=1;damage(birth,bi,10000,mode==1);tick(birth);
        for(int n=0;n<2;++n){check(!birth.roomClear&&birth.enemies.size()==1,"retained Drip chain gates clear");auto child=birth.enemies.front();check(child.monster==monsterId(870)&&child.slide&&child.slide->initialized&&child.slide->phase==2&&length(child.velocity)>10,"launched real Drip child");damage(birth,child.id,10000);tick(birth);}
        check(birth.roomClear&&birth.stats.kills==3,"two Drips then room clear");}
    std::cout<<"SPLURT launch36=1 second8=1 retarget=1 two_charges=1 two_Drips=1 capacity=1 partition=1\n";
}
void dank() {
    auto s=fixture();auto id=variant(s,220,1);acquire(s,id);tick(s,35);check(s.hazards.empty(),"Dank no creep before launch");
    tick(s,20);auto &r=*s.findEnemy(id)->slide;check(r.creepPatches>=5&&s.hazards.size()>=5,"black trail emitted during slide");
    for(const auto &h:s.hazards)check(h.kind==HazardKind::Tar&&h.damage==0&&near(h.duration,2),"60frame slowing not damaging trail");
    s.player.position=s.hazards.front().position;s.player.slowTime=0;s.godMode=false;const auto hp=s.player.hp;tick(s);check(s.player.slowTime>0&&s.player.hp==hp,"black creep slows without damage");
    auto capped=fixture();auto ci=variant(capped,220,1);acquire(capped,ci);tick(capped,35);capped.limits.hazards=0;tick(capped,5);
    check(capped.findEnemy(ci)->slide->pendingCreep.has_value(),"trail retained at hazard cap");capped.limits.hazards=256;tick(capped);check(capped.findEnemy(ci)->slide->creepPatches>0,"retained trail released");
    auto birth=fixture();id=variant(birth,220,1);birth.debugScenario=false;birth.limits.enemies=1;damage(birth,id,10000);tick(birth);
    for(int n=0;n<2;++n){check(birth.enemies.size()==1&&!birth.roomClear,"Clot pending completion");auto child=birth.enemies.front();check(child.monster==monsterId(15,1)&&!child.slide,"real Clot offspring");damage(birth,child.id,10000);tick(birth);}check(birth.roomClear,"Clots gate clear");
    std::cout<<"DANK trail_after_launch=1 source_life60=1 slow_only=1 retained=1 two_Clots=1\n";
}
void water() {
    for(auto identity:std::array<MonsterId,4>{{monsterId(217),monsterId(217,3),monsterId(870),monsterId(871)}})for(bool flooded:{false,true}) {
        auto s=fixture();s.arena.rooms[0].flooded=flooded;s.arena.rails.emplace();s.arena.rails->pits.push_back({{1,-3,-10},{4,0,10}});
        auto id=s.spawnMonster(identity,{0,.85f,0});auto &e=*s.findEnemy(id);tick(s);e.slide->phase=2;e.velocity={30,0,0};
        tick(s,10);const bool crosses=flooded&&identity!=monsterId(217);check(crosses?e.position.x>4:e.position.x<1,"only swimming variants cross wet pits");
    }
    auto s=fixture();s.arena.rooms[0].flooded=true;s.arena.walls.push_back({{2,0,-50},{3,10,50}});auto id=variant(s,870);tick(s);s.findEnemy(id)->slide->phase=2;s.findEnemy(id)->velocity={30,0,0};tick(s,8);check(s.findEnemy(id)->position.x<2,"wet movement still respects solid walls");
    auto birth=fixture();birth.arena.rooms[0].flooded=true;birth.arena.rails.emplace();
    birth.arena.rails->pits.push_back({{-10,-3,-10},{10,0,10}});auto bi=variant(birth,871);damage(birth,bi,10000);tick(birth);
    check(birth.enemies.size()==2,"two water-born Drips emitted");
    for(const auto &e:birth.enemies)check(e.monster==monsterId(870)&&birth.arena.blocked(e.position,e.radius)&&!birth.arena.swimBlocked(e.position,e.radius,0),"child placement retains flooded-pit footprint");
    tick(birth,3);for(const auto &e:birth.enemies)check(!birth.arena.swimBlocked(e.position,e.radius,0),"water-born children remain legal during crowd resolution");
    std::cout<<"WATER wet_pits=1 dry_pits_block=1 walls_block=1 child_placement=1\n";
}
void placement() {
    struct Witness{MonsterId id;uint64_t seed;int floor,room;};
    for(auto w:std::array<Witness,6>{{{monsterId(217,1),0,2,1},{monsterId(217,2),0,0,5},
        {monsterId(217,3),31,3,5},{monsterId(220,1),1,6,7},{monsterId(870),0,2,1},{monsterId(871),4,3,3}}}) {
        Simulation s(w.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,w.floor);s.godMode=true;
        std::vector<EntityId> ids;
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==w.id) {
            check(e.slide&&!s.arena.blocked(e.position,e.radius),"natural exact controller and legal placement");ids.push_back(e.id);
        }
        check(!ids.empty(),"natural variant exists");tick(s,8);
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==w.id)check(e.idleTime>0&&e.slide->ticks==0,"dormant ambient motion, no attacks");
        s.enterRoom(w.room);tick(s,8);
        for(auto id:ids)check(s.findEnemy(id)&&s.findEnemy(id)->slide->ticks>0,"resident controller activates");
        std::cout<<"NATURAL_VARIANT "<<w.id.type<<'.'<<w.id.variant<<".0 seed="<<w.seed<<" floor="<<w.floor<<" room="<<w.room<<'\n';
    }
}

void config() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-dipvariants-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}clean{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream file(dir/"dip_variants.mechanics");const std::string original(std::istreambuf_iterator<char>(file),{});
    auto edit=[&](const std::string &from,const std::string &to){auto s=original;const auto at=s.find(from);check(at!=s.npos,"config fixture");s.replace(at,from.size(),to);std::ofstream(dir/"dip_variants.mechanics")<<s;return MechanicsLibrary::load(dir);};
    auto changed=edit("12 8 8 40 4 6","12 7 8 40 4 6");check(changed->slide(monsterId(871))->secondLaunchFrame==7&&defaultMechanics()->slide(monsterId(871))->secondLaunchFrame==8,"isolated external snapshot");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{"12 8 8 40 4 6","12 12 8 40 4 6"},{"10 3 3","22 3 3"},{"3 1 60 30 .97","3 0 60 30 .97"},{".1 30 1.15","-1 30 1.15"},{".85 870.0.0 1",".85 217.0.0 1"},{"slide_swim 870.0.0","slide_swim 870.0.0\nslide_swim 870.0.0"}}){bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid extension rejected");}
    std::cout<<"CONFIG immutable=1 invalid_profiles=6\n";
}
}
int main(){std::cout<<std::unitbuf;try{corn();drips();splurt();dank();water();config();placement();std::cout<<"PASS Dip variants\n";return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
