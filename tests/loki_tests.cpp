#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.002f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-loki-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(std::string from,std::string to) {
        auto file=path/"loki.mechanics";std::ifstream in(file);std::string text((std::istreambuf_iterator<char>(in)),{});
        check(text.find(from)!=std::string::npos,"configuration fixture exists");
        for(size_t at=0;(at=text.find(from,at))!=std::string::npos;at+=to.size())text.replace(at,from.size(),to);
        std::ofstream(file)<<text;
    }
    auto action(int attack){replace("3 2 1 2",attack==0?"1 0 0 0":attack==1?"0 1 0 0":attack==2?"0 0 1 0":"0 0 0 1");return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.stats={};s.room=0;
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    s.rooms.assign(s.arena.roomCount(),{});s.godMode=true;s.debugScenario=true;s.roomClear=false;s.bossKilled=false;
    s.player.position={15,.85f,15};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage,bool execute=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.execution=execute;s.queueRoot(e);s.drainEvents();}
void volleys() {
    for(int variant=0;variant<2;++variant)for(int action=0;action<2;++action) {
        Pack pack;auto s=fixture(pack.action(action));const auto id=s.spawnMonster(monsterId(69,variant),{0,.85f,0});
        check(id!=0,"Loki encounter spawns");for(auto &e:s.enemies)e.cooldown=1000;s.findEnemy(id)->cooldown=0;
        tick(s);check(s.findEnemy(id)->state==EnemyState::Windup&&s.findEnemy(id)->bossAttack==action,"configured action starts");
        int emitted=0;std::set<EntityId> observed;
        for(int frame=0;frame<160&&s.findEnemy(id)->bossCycles==0;++frame) {
            tick(s);const int total=int(s.stats.projectiles);
            if(total!=emitted) {
                const int count=action==0?4:8;check(total==emitted+count,"one authored volley per interval");
                int seen=0;
                for(const auto &shot:s.projectiles)if(shot.context.sourceEntity==id&&observed.insert(shot.id).second) {
                    const auto v=unit(horizontal(shot.velocity));
                    const bool cardinal=std::min(std::abs(v.x),std::abs(v.z))<.001f;
                    const bool diagonal=near(std::abs(v.x),std::abs(v.z));
                    check(action==1?(cardinal||diagonal):emitted==4?diagonal:cardinal,"cardinal then diagonal then cardinal, not an aimed spread");++seen;
                }
                check(seen==count,"volley remains physical projectiles");emitted=total;
                s.player.position={-15,.85f,13}; // Changing aim must not rotate the authored axes.
            }
        }
        check(emitted==(action==0?12:8)&&s.findEnemy(id)->bossCycles==1,"exact whole attack completes once");
        if(variant)check(s.enemies[1].bossCycles==0,"halves run independent clocks");
    }
    std::cout<<"LOKI_VOLLEYS ordered=4,4,4 axes=cardinal,diagonal,cardinal ring=8 independent_halves=1\n";
}
void teleport() {
    Pack pack;auto s=fixture(pack.action(3));auto id=s.spawnMonster(monsterId(69),{0,.85f,0});s.findEnemy(id)->cooldown=0;
    tick(s);auto target=s.findEnemy(id)->target;check(s.findEnemy(id)->state==EnemyState::Teleporting,"teleport has an absent state");
    hit(s,id,100);check(near(s.findEnemy(id)->hp,1120),"absent body cannot be hit");
    s.player.position=target;
    s.arena.obstacles.push_back({sub(target,{2,target.y,2}),add(target,{2,3,2})});s.arena.rebuildWalls();
    for(int n=0;n<100&&s.findEnemy(id)->state==EnemyState::Teleporting;++n)tick(s);
    auto *e=s.findEnemy(id);check(e->state==EnemyState::Exposed&&planarDistance(e->position,target)>=6,"arrival revalidates player and newly blocked landing");
    check(!s.arena.blocked(e->position,e->radius),"teleport stays on actual walkable ground");
    hit(s,id,100);check(near(e->hp,1020),"reappeared body vulnerable immediately");
    const auto pos=e->position;const auto timer=e->stateTime;s.enterRoom(1);tick(s,40);s.enterRoom(0);
    e=s.findEnemy(id);check(e&&distance(e->position,pos)<.001f&&near(e->stateTime,timer),"inactive room preserves teleport recovery");
    auto contact=fixture();contact.godMode=false;auto body=contact.spawnMonster(monsterId(69),{0,.85f,0});contact.findEnemy(body)->cooldown=1000;
    contact.player.position=contact.findEnemy(body)->position;tick(contact);check(near(contact.player.hp,75),"whole-heart contact maps to25 once");
    std::cout<<"LOKI_TELEPORT absent_immunity=1 grounded_vulnerability=1 landing_revalidation=1 inactive_pause=1 contact=25\n";
}
void summonsAndCompletion() {
    for(int variant=0;variant<2;++variant) {
        Pack pack;auto s=fixture(pack.action(2));auto first=s.spawnMonster(monsterId(69,variant),{0,.85f,0});
        for(auto &e:s.enemies)e.cooldown=0;
        tick(s,1500);const int limit=variant?1:4;
        std::vector<EntityId> children,bodies;
        for(const auto &e:s.enemies)if(e.alive) {
            if(e.bossGroup==first)bodies.push_back(e.id);
            if(e.summoner==first){children.push_back(e.id);check(e.monster==monsterId(25,variant),"correct fly identity");}
        }
        check(int(children.size())==limit,"shared live and pending child cap");
        check(bodies.size()==size_t(variant+1),"complete independent body group");
        const auto last=bodies.back();const auto dynamite=s.dynamite;
        s.debugScenario=false;
        hit(s,first,10000,true);tick(s);
        if(variant) {
            check(s.boss()&&s.boss()->id==last&&!s.bossKilled&&!s.rooms[0].bossPaid&&s.dynamite==dynamite,"first half does not finish or pay encounter");
            check(near(s.bossHealthFraction(*s.boss()),.5f),"aggregate HP keeps dead half after cleanup");
            s.enterRoom(1);tick(s,10);s.enterRoom(0);
            check(near(s.bossHealthFraction(*s.boss()),.5f)&&s.roomThreats()==2,"half-dead group survives room reentry");
            hit(s,last,10000,true);tick(s);
        }
        check(s.bossKilled&&s.rooms[0].bossPaid&&s.dynamite==dynamite+1&&!s.roomClear,"one group payout; living flies still gate clear");
        check(s.roomThreats()==size_t(limit),"children survive both boss deaths");
        for(auto child:children)hit(s,child,10000,true);
        tick(s);check(s.roomClear&&s.roomThreats()==0&&s.dynamite==dynamite+1,"ordinary child deaths release room without a second boss payout");
    }
    auto s=fixture();s.limits.enemies=1;check(!s.spawnMonster(monsterId(69,1),{0,.85f,0})&&s.enemies.empty(),"capacity cannot create one half");
    s.limits.enemies=10;s.arena.obstacles.push_back({{-25,0,-25},{25,3,25}});s.arena.rebuildWalls();
    check(!s.spawnMonster(monsterId(69,1),{0,.85f,0})&&s.enemies.empty(),"geometry failure cannot partially spawn group");
    Pack invalid;invalid.replace("1.2 3 2 1 2","1.2 0 0 0 0");bool rejected=false;
    try{MechanicsLibrary::load(invalid.path);}catch(const std::exception &){rejected=true;}check(rejected,"zero action weights rejected");
    std::cout<<"LOKI_GROUPS normal_children=4 red_children=1 atomic_spawn=1 per_half_hp=1120 aggregate_health=1 single_payout=1 child_clear=1\n";
}
void realRoutes() {
    std::set<int> found;int checked=0;
    for(uint64_t seed=0;seed<128&&found.size()<2;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&found.size()<2;++floor) {
            const auto p=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            if(p.bossMonster.type!=69||found.contains(p.bossMonster.variant))continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            ++checked;s.jumpDebug(s.finalRoom());s.godMode=true;
            check(s.boss()&&s.boss()->monster==p.bossMonster&&s.roomThreats()==size_t(p.bossMonster.variant+1),"actual floor instantiates complete configured encounter");
            check(p.band==(p.bossMonster.variant?3:2),"source chapters mapped to reviewed local bands");
            for(const auto &e:s.enemies)if(e.alive)check(near(e.hp,1120),"350 per body converted to1120, not split between halves");
            const auto group=s.boss()->bossGroup;std::vector<EntityId> bodies;
            for(const auto &e:s.enemies)if(e.bossGroup==group)bodies.push_back(e.id);
            tick(s,600);check(s.stats.projectiles>0,"real encounter attacks");
            std::vector<EntityId> threats;for(const auto &e:s.enemies)if(e.alive)threats.push_back(e.id);
            for(auto id:threats)hit(s,id,10000,true);tick(s);
            check(s.roomClear&&s.rooms[size_t(s.finalRoom())].bossPaid&&s.bossKilled,"actual generated boss and children resolve normally");
            if(!s.storySeen()) {
                check(!s.canUseFloorExit(),"boss death must not bypass required story evidence");
                const auto site=s.storyRoomIndex();check(site>=0,"required story room exists");
                s.jumpDebug(site);s.clearRoomDebug();s.player.position=s.arena.rooms[size_t(site)].objective;
                s.interact();check(s.storySeen(),"existing interaction records this account's evidence");s.storyOpen=StoryRoom::None;
                s.jumpDebug(s.finalRoom());
            }
            check(s.canUseFloorExit(),"actual boss floor exits after story requirements");
            found.insert(p.bossMonster.variant);
            std::cout<<"LOKI_ROUTE seed="<<seed<<" floor="<<floor<<" band="<<p.band<<" id="<<monsterIdText(p.bossMonster)<<" bodies="<<bodies.size()<<'\n';
        }
    }
    check(found.size()==2&&checked==2,"both ordinary boss routes reachable");
    const auto lib=defaultMechanics();check(!lib->configureFloor(ExpeditionPlan(0,true).profileOnFloor(0),0).active(),"tutorial remains separate");
}
}
int main(){try{volleys();teleport();summonsAndCompletion();realRoutes();std::cout<<"PASS Loki and Lokii partial controllers\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
