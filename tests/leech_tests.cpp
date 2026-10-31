#include "combat/Simulation.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float tolerance=.01f){return std::abs(a-b)<tolerance;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.arena.flightCollisionPrepared=false;s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.roomClear=false;s.godMode=true;
    s.player.position={0,.85f,65};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int v=0){return s.spawnMonster(monsterId(55,v),{0,.85f,0});}
void kill(Simulation &s,EntityId id,bool execution=false,bool debug=false) {
    Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1000;hit.execution=execution;hit.debugExecution=debug;s.queueRoot(hit);s.drainEvents();
}
void acquire(Simulation &s,EntityId id) {
    for(int n=0;n<20&&!s.findEnemy(id)->leech->charging;++n)tick(s);
    check(s.findEnemy(id)->leech->charging,"far aligned target triggers a charge without range cap");
}
void movement() {
    for(int variant=0;variant<3;++variant) {
        auto s=fixture();const auto id=spawn(s,variant);const auto &d=*s.content->monster(monsterId(55,variant));
        check(d.flying&&near(s.findEnemy(id)->maxHp,80)&&near(s.content->monsterHealth(d.id,12),80),"all variants fly with source25HP converted to80");
        acquire(s,id);auto &e=*s.findEnemy(id);auto &r=*e.leech;
        const auto direction=r.chargeDirection;const auto charges=r.charges;
        s.player.position={-60,.85f,-60};tick(s,35);
        check(r.charging&&r.charges==charges&&distance(r.chargeDirection,direction)<.001f,"charge keeps original aim after player leaves lane");
        check(length(e.velocity)>35&&s.stats.projectiles==0,"charge accelerates and is contact-only");
        for(int n=0;n<180&&r.stops==0;++n)tick(s);
        check(r.stops>0&&!s.arena.flightBlocked(e.position,e.radius,s.room),"actual room boundary stops charge even with open passages");
        e.state=EnemyState::Stunned;e.stateTime=1;const auto where=e.position;tick(s,10);
        check(!r.charging&&distance(e.position,where)<.001f,"stun interrupts charge");
    }
    auto a=fixture(),b=fixture();a.player.position=b.player.position={60,.85f,60};const auto x=spawn(a),y=spawn(b);tick(a,3);tick(b,3);
    a.findEnemy(x)->velocity={400,0,-400};tick(a);tick(b);
    check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.001f,"external knockback does not change Leech movement");
    std::cout<<"MOVEMENT equal_hp=1 flight=1 uncapped_range=1 committed_charge=1 acceleration=1 wall_stop=1 stun=1 knockback=1\n";
}
void geometry() {
    auto blocked=fixture();blocked.arena.walls.push_back({{-79,-1,5},{79,20,6}});const auto b=spawn(blocked);tick(blocked,12);
    check(blocked.findEnemy(b)->leech->charges==0,"solid wall blocks acquisition");
    auto cover=fixture();cover.arena.flightCollisionPrepared=true;cover.arena.flightWalls.clear();
    cover.arena.walls.push_back({{-79,0,5},{79,2,6}});cover.arena.flightCover.push_back({{-79,0,5},{79,2,6}});
    const auto c=spawn(cover);acquire(cover,c);bool crossed=false,raised=false;
    for(int n=0;n<60;++n){tick(cover);const auto &e=*cover.findEnemy(c);raised|=e.position.y>1.5f;crossed|=e.position.z>7;}
    check(crossed&&raised,"flight acquisition and movement cross low cover using flight height");
    auto wandering=fixture();wandering.player.position={60,.85f,60};wandering.arena.flightCollisionPrepared=true;
    wandering.arena.walls={{{-2,0,-79},{2,2,79}}};wandering.arena.flightCover=wandering.arena.walls;
    const auto w=spawn(wandering);tick(wandering,30);
    check(wandering.findEnemy(w)->leech->hasDestination||length(wandering.findEnemy(w)->velocity)>1,"shared cardinal wander uses flight paths, including inside low cover");
    std::cout<<"GEOMETRY walls_block=1 low_cover_crossed=1 airborne_wander=1\n";
}
void deathAndChild() {
    for(int variant=0;variant<3;++variant)for(bool execution:{false,true}) {
        auto s=fixture();const auto id=spawn(s,variant);tick(s);s.godMode=false;s.player.position={0,.85f,3};
        const auto witness=s.spawnMonster(monsterId(10),{3,.85f,0});s.findEnemy(witness)->hp=s.findEnemy(witness)->maxHp=200;
        kill(s,id,execution);
        check(s.stats.explosions==unsigned(variant>0)&&near(s.player.hp,variant?75:100),"variant death explosion is immediate with full-heart conversion");
        check(near(s.findEnemy(witness)->hp,variant?72:200),"death blast deals128 friendly-fire damage");
        check(std::none_of(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.alive&&e.monster==monsterId(96);}),"Holy Leech never leaves an orbiting fly behind");
        kill(s,id,execution);check(s.stats.explosions==unsigned(variant>0),"duplicate lethal input cannot duplicate explosion");
        check(s.enemyBombs.empty()&&s.hazards.empty(),"death produces no delayed legacy bomb");
    }
    {auto s=fixture();const auto id=spawn(s,2);s.limits.enemies=1;tick(s,10);check(s.livingEnemies()==1,"orbiter retained while capacity full");
     s.findEnemy(id)->position={20,.85f,20};s.player.position=s.findEnemy(id)->position;s.limits.enemies=10;tick(s);
     const auto it=std::find_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.monster==monsterId(96);});
     check(it!=s.enemies.end()&&it->partner==id&&planarDistance(it->position,s.findEnemy(id)->position)<1,"retained fly attaches at current parent even beside player");
     tick(s,20);check(it->eternalFly&&it->eternalFly->orbitTicks>0,"required child runs actual orbit controller");}
    {auto s=fixture();const auto id=spawn(s,2);s.limits.enemies=1;tick(s,3);kill(s,id);s.limits.enemies=10;tick(s,3);
     check(s.enemies.empty()&&s.roomThreats()==0,"dead parent cancels pending fly instead of spawning orphan Attack Fly");}
    {auto s=fixture();const auto id=spawn(s,1);Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1000;s.queueRoot(hit);s.limits.queuedEvents=0;s.drainEvents();
     check(s.findEnemy(id)->deathBlastPending&&s.stats.explosions==0,"full event capacity retains immediate blast");
     s.debugScenario=false;tick(s);check(!s.roomClear,"pending blast gates room completion");s.limits.queuedEvents=256;tick(s,3);
     check(s.stats.explosions==1&&!s.findEnemy(id)&&s.roomClear,"capacity release resolves once before room clear");}
    {auto s=fixture();const auto id=spawn(s,2);tick(s,3);kill(s,id,true,true);tick(s,3);check(s.stats.explosions==0&&s.enemies.empty(),"debug clear also removes Holy dependency safely");}
    {auto s=fixture();const auto id=spawn(s,1);s.godMode=false;s.player.position={0,.85f,3};s.arena.walls.push_back({{-2,0,1},{2,4,2}});kill(s,id);
     check(near(s.player.hp,100),"real wall shields player from blast");}
    std::cout<<"DEATH immediate=1 friendly_fire=1 one_blast=1 retained_payload=1 orbiter_birth=1 orbiter_cleanup=1 debug_cleanup=1 line_check=1\n";
}
void contact() {
    auto s=fixture();const auto id=spawn(s);s.godMode=false;s.player.position=s.findEnemy(id)->position;tick(s);
    check(near(s.player.hp,75),"full-heart contact is20 before shared1.25multiplier");tick(s);check(near(s.player.hp,75),"player invulnerability prevents per-frame contact damage");
    std::cout<<"CONTACT damage=25 invulnerability=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-leeches-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"leeches.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"leeches.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("20 1.55 .9 .3","20 1.2 .9 .3");check(near(changed->leech(monsterId(55))->chargeForce,1.2f)&&near(defaultMechanics()->leech(monsterId(55))->chargeForce,1.55f),"external edits load immutable snapshots");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".1 .85 .85",".1 -1 .85"},{"20 1.55 .9 .3","20 1.55 1 .3"},{"4 8 6 40","4 0 6 40"},{"5 96.0.0","5 10.0.0"},{"2 0 2 1 1 0 1 legacy","2 0 2 0 1 0 1 legacy"},{"leech 55.0.0","leech 9999.0.0"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or incompatible leech profile rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=6\n";
}
void placement() {
    std::array<bool,3> found{};int floors=0,rooms=0;
    for(uint64_t seed=0;seed<64&&(!found[0]||!found[1]||!found[2]);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            if(plan.profileOnFloor(floor).band<2)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++floors;
            for(int room=1;room<s.finalRoom();++room) {
                ++rooms;for(const auto &e:s.roomEnemies(room))if(e.leech) {
                    check(s.arena.profile.band>=2&&(e.monster.variant!=2||s.arena.profile.band==3),"source habitats select proper stage band");
                    check(!s.arena.flightBlocked(e.position,e.radius,room),"natural resident starts in valid flight footprint");
                    if(!found[size_t(e.monster.variant)])std::cout<<"NATURAL_LEECH id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
                    found[size_t(e.monster.variant)]=true;
                }
            }
        }
    }
    check(found[0]&&found[1]&&found[2],"all three variants have actual seeded placement witnesses");
    std::cout<<"PLACEMENT floors="<<floors<<" rooms="<<rooms<<" late_bands=1\n";
}
}
int main(){std::cout<<std::unitbuf;try{movement();geometry();deathAndChild();contact();configuration();placement();std::cout<<"PASS Leech family\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
