#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *s){if(!b)throw std::runtime_error(s);}
bool near(float a,float b,float epsilon=.015f){return std::abs(a-b)<epsilon;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={12,.85f,0};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int variant=0){return s.spawnMonster(monsterId(820,variant),{0,.85f,0});}
void arm(Enemy &e){auto &r=*e.danny;r.initialized=true;r.frame=0;r.fired=false;r.clock=0;r.frameReady=false;r.cooldown=150;e.velocity={};}
void hit(Simulation &s,EntityId id,float amount,bool debug=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=e.debugExecution=debug;s.queueRoot(e);s.drainEvents();}
void timing() {
    auto s=fixture();auto id=spawn(s);tick(s);
    check(near(s.findEnemy(id)->maxHp,128)&&s.findEnemy(id)->danny->cooldown>=10&&s.findEnemy(id)->danny->cooldown<=19,"source HP and short initial delay");
    for(int n=0;n<1200&&s.findEnemy(id)->danny->frame<0;++n)tick(s);
    check(s.findEnemy(id)->danny->frame==0,"natural attack decision enters animation");
    arm(*s.findEnemy(id));tick(s,11);check(s.findEnemy(id)->danny->attacks==0&&s.stats.projectiles==0,"no payload before Shoot frame12");
    s.player.position={0,.85f,12};const auto expectedAim=unit(horizontal(sub(s.player.position,s.findEnemy(id)->position)));tick(s);
    auto &r=*s.findEnemy(id)->danny;
    check(r.attacks==1&&r.children==2&&s.stats.projectiles==4,"first shot: four rocks plus two living spiders");
    int children=0;for(const auto &e:s.enemies)if(e.alive&&e.summoner==id){++children;std::cout<<"CHILD type="<<e.monster.type<<" variant="<<e.monster.variant<<" lift="<<e.lift<<" vx="<<e.velocity.x<<" vz="<<e.velocity.z<<" hp="<<e.hp<<"\n";check(e.monster.type==818&&e.monster.variant==0&&e.rockSpider&&e.lift>0&&dot(unit(horizontal(e.velocity)),expectedAim)>std::cos(15.1f*Pi/180),"actual falling child sampled current target within 30-degree spread");}
    check(children==2,"both thrown actors exist immediately");
    for(const auto &p:s.projectiles)check(p.kind==ProjectileKind::Rock&&p.velocity.z>0&&p.context.sourceEntity==id&&near(p.gravity,23.4f),"aimed attributed rock cluster uses source strength1 gravity");
    tick(s,26);check(s.findEnemy(id)->danny->frame==-1&&s.findEnemy(id)->danny->cooldown==150,"attack animation38 does not consume idle cooldown");
    tick(s,30);check(s.findEnemy(id)->danny->cooldown==120,"ordinary recovery decrements once per source frame");
    std::cout<<"TIMING natural=1 Shoot12=1 Attack38=1 delay150=1 live_children=2 rocks=4 late_aim=1\n";
}
void ownership() {
    auto s=fixture();auto id=spawn(s);arm(*s.findEnemy(id));tick(s,12);
    std::vector<EntityId> children;for(const auto &e:s.enemies)if(e.summoner==id)children.push_back(e.id);
    hit(s,children[0],10000);auto *morph=s.findEnemy(children[0]);
    check(morph&&morph->alive&&morph->monster==monsterId(85)&&morph->summoner==id,"shell break preserves living child ownership");
    s.projectiles.clear();auto shots=s.stats.projectiles;arm(*s.findEnemy(id));tick(s,12);
    check(s.findEnemy(id)->danny->children==2&&s.stats.projectiles-shots==6,"two owned survivors replace further spiders with six rocks");
    hit(s,children[0],10000,true);s.projectiles.clear();shots=s.stats.projectiles;arm(*s.findEnemy(id));tick(s,12);
    check(s.findEnemy(id)->danny->children==3&&s.stats.projectiles-shots==5,"one freed owner slot produces one child and five rocks");
    const auto other=spawn(s);arm(*s.findEnemy(other));tick(s,12);
    check(s.findEnemy(other)->danny->children==2,"ownership limit is per parent");
    std::cout<<"OWNERSHIP morph_keeps_slot=1 replacement=1 independent_parents=1\n";
}
void coal() {
    auto s=fixture();const auto id=spawn(s,1);arm(*s.findEnemy(id));tick(s,12);
    int children=0,coals=0;EntityId spider=0;
    for(const auto &e:s.enemies)if(e.alive&&e.id!=id){check(e.rockSpider&&e.lift>0,"coal payload is real falling actors");if(e.environment){++coals;check(!e.summoner&&e.monster.type==33&&e.monster.variant==11,"hot coals do not consume owner cap");}else{++children;spider=e.id;check(e.summoner==id&&e.monster.type==818&&e.monster.variant==2,"coal child identity and owner");}}
    check(children==1&&coals==3&&s.stats.projectiles==0,"first coal volley is one Coal Spider plus three Hot Coals");
    arm(*s.findEnemy(id));tick(s,12);
    coals=0;for(const auto &e:s.enemies)coals+=e.alive&&e.environment.has_value();
    check(coals==7&&s.findEnemy(id)->danny->children==1,"full owner cap changes next volley to four Hot Coals");
    hit(s,spider,10000,true);arm(*s.findEnemy(id));tick(s,12);
    check(s.findEnemy(id)->danny->children==2,"coal child replenishes after death");
    std::cout<<"COAL live1_hot3=1 capped_hot4=1 replenish=1\n";
}
void damageAndLimits() {
    auto s=fixture();auto id=spawn(s);tick(s);s.findEnemy(id)->danny->cooldown=100;
    hit(s,id,32);tick(s);check(s.findEnemy(id)->danny->cooldown==99&&near(s.findEnemy(id)->danny->recentDamage,9.89f),"damage accumulates in native HP at epilogue");
    tick(s);check(s.findEnemy(id)->danny->cooldown==97&&near(s.findEnemy(id)->danny->recentDamage,9.78f),"hurt cooldown doubles and accumulator decays");
    for(int variant:{0,1}) {
        auto capped=fixture();auto parent=spawn(capped,variant);
        for(int n=0;n<9;++n){auto child=capped.spawnMonster(monsterId(85),{30.f+float(n%3)*3,.85f,30.f+float(n/3)*3});auto *e=capped.findEnemy(child);check(e,"population fixture allocated");if(variant){/* Predicate-only marker: Red Fireplace runtime is not ported yet. */e->kind=EnemyKind::Rusher;e->monster=monsterId(33,2);e->spider.reset();}e->state=EnemyState::Stunned;e->stateTime=100;}
        tick(capped,700);check(capped.findEnemy(parent)->danny->attacks==0,"source room population threshold blocks attacks");
    }
    auto blocked=fixture();id=spawn(blocked);blocked.limits.projectiles=0;blocked.limits.enemies=1;arm(*blocked.findEnemy(id));tick(blocked,12);
    check(blocked.findEnemy(id)->danny->pendingShots.size()==4&&blocked.enemies.size()==1,"saturation retains exact volley and child requests");
    tick(blocked,15);check(blocked.findEnemy(id)->danny->attacks==1&&blocked.findEnemy(id)->danny->children==2,"saturated attack never rerolls or duplicates");
    hit(blocked,id,10000);blocked.debugScenario=false;tick(blocked);check(!blocked.roomClear&&blocked.findEnemy(id),"pending payload retains dead owner and room sealing");
    blocked.limits.projectiles=64;blocked.limits.enemies=10;tick(blocked);
    check(blocked.stats.projectiles==4&&blocked.roomThreats()==2&&blocked.stats.kills==1,"dead owner flushes exact retained payload once");
    auto coalBlocked=fixture();auto coalId=spawn(coalBlocked,1);coalBlocked.limits.enemies=1;arm(*coalBlocked.findEnemy(coalId));tick(coalBlocked,1000);
    check(coalBlocked.findEnemy(coalId)->danny->attacks==1&&coalBlocked.findEnemy(coalId)->danny->waitingBirths,"coal producer pauses while its volley lacks capacity");
    coalBlocked.limits.enemies=16;tick(coalBlocked,3);
    int coalBodies=0;for(const auto &e:coalBlocked.enemies)coalBodies+=e.alive&&e.id!=coalId;
    check(coalBodies==4&&coalBlocked.findEnemy(coalId)->danny->attacks==1,"capacity release admits exactly one retained coal volley");
    auto a=fixture(),b=fixture();auto ia=spawn(a),ib=spawn(b);a.player.position=b.player.position={60,.85f,0};
    tick(a,30);tick(b,120,1.f/120);check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.04f,"30/120Hz source motion agrees");
    std::cout<<"LIMITS source_room9=1 damage_response=1 retained=1 completion=1 partition=1\n";
}
void config() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-danny-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"dannies.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string a,std::string b){auto text=original;auto at=text.find(a);check(at!=text.npos,"config fixture exists");text.replace(at,a.size(),b);std::ofstream(dir/"dannies.mechanics")<<text;return MechanicsLibrary::load(dir);};
    auto changed=edit("10 19 150","10 19 120");check(changed->danny(monsterId(820))->cooldown==120&&defaultMechanics()->danny(monsterId(820))->cooldown==150,"profiles are immutable across hot reload");
    for(const auto &x:std::vector<std::pair<std::string,std::string>>{{"danny_payload 820.0.0","#danny_payload 820.0.0"},{"818.0.0 33.11.0","818.2.0 33.11.0"},{"818.2.0 33.11.0","818.2.0 85.0.0"},{"150 60 20 10 38 12","150 60 20 10 38 38"}}){bool failed=false;try{edit(x.first,x.second);}catch(const std::exception&){failed=true;}check(failed,"invalid controller payload rejected");}
    std::cout<<"CONFIG snapshots=1 invalid_contracts=4\n";
}
void witnesses() {
    bool hardy=false,corn=false;
    for(int seed=0;seed<128&&(!hardy||!corn);++seed) {
        Simulation s(uint64_t(seed),1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,2);
        for(int room=0;room<s.arena.roomCount();++room)for(const auto &e:s.roomEnemies(room)) {
            if((!hardy&&e.monster==monsterId(826))||(!corn&&e.monster==monsterId(217,3))) {
                if(e.monster.type==826)hardy=true;else corn=true;
                std::cout<<"UPDATED_WITNESS id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor=2 room="<<room<<'\n';
            }
        }
    }
    check(hardy&&corn,"existing Quarry populations remain reachable after roster expansion");
}
void natural() {
    bool found[2]{};
    for(int seed=0;seed<64&&(!found[0]||!found[1]);++seed) {
        Simulation s(uint64_t(seed),1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,2);
        for(int room=0;room<s.arena.roomCount();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==820&&!found[e.monster.variant]) {
            check(e.danny&&s.arena.profile.band==1&&!s.arena.blocked(e.position,e.radius),"generated Quarry resident uses real controller and valid placement");
            found[e.monster.variant]=true;std::cout<<"NATURAL_DANNY variant="<<e.monster.variant<<" seed="<<seed<<" floor=2 room="<<room<<'\n';
        }
    }
    check(found[0]&&found[1],"both actual seeded populations reachable");
}
}
int main(int argc,char**argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--witnesses"){witnesses();return 0;}if(argc>1&&std::string(argv[1])=="--natural"){natural();return 0;}timing();ownership();coal();damageAndLimits();config();std::cout<<"PASS Danny family\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
