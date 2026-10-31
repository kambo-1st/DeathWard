#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float epsilon=.003f){return std::abs(a-b)<epsilon;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0);
    s.arena=Arena{};s.arena.bounds={{-60,-1,-60},{60,8,60}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-60,-.4f,-60},{60,0,60}}};}
    s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;s.queueRoot(e);s.drainEvents();}
void acquire(Simulation &s,EntityId id){for(int i=0;i<16&&s.findEnemy(id)->state!=EnemyState::Windup;++i)tick(s);check(s.findEnemy(id)->state==EnemyState::Windup,"Maw acquires in seven source frames");}
void movementAndShot() {
    for(int v:{0,1,2}){auto s=fixture();auto id=s.spawnMonster(monsterId(26,v),{0,.85f,0});check(near(s.findEnemy(id)->hp,64),"all Maw variants sourceHP20");}
    auto red=fixture();auto id=red.spawnMonster(monsterId(26,1),{0,.85f,0});red.player.position.z=50;
    tick(red,2);check(near(red.findEnemy(id)->velocity.z,1.17f),"red first impulse native .39 converted x3");
    tick(red,2);check(near(red.findEnemy(id)->velocity.z,(.39f*.93f+.39f)*3),"native chase recurrence");
    tick(red,40);check(red.stats.projectiles==0,"Red never fires while alive");
    auto s=fixture();id=s.spawnMonster(monsterId(26),{0,.85f,0});acquire(s,id);
    const auto speed=length(horizontal(s.findEnemy(id)->velocity));tick(s,2);
    check(near(length(horizontal(s.findEnemy(id)->velocity)),speed*.93f),"attack coasts with friction and no pursuit impulse");
    tick(s,5);check(s.projectiles.empty(),"not before Shoot4");s.player.position={30,.85f,0};tick(s);
    check(s.projectiles.size()==1&&near(length(s.projectiles[0].velocity),21),"source speed21, single shot");
    check(s.projectiles[0].velocity.x>20.9f,"aim sampled at firing even outside acquisition range");
    tick(s,32);check(s.findEnemy(id)->state==EnemyState::Ready,"20-frame shoot recovery");
    auto cover=fixture();id=cover.spawnMonster(monsterId(26),{0,.85f,0});cover.arena.walls={{{-10,-1,3},{10,8,3.5f}}};tick(cover,240);
    check(cover.stats.projectiles==0&&cover.findEnemy(id)->position.z<3,"solid wall blocks flight and acquisition");
    auto stun=fixture();id=stun.spawnMonster(monsterId(26),{0,.85f,0});acquire(stun,id);
    stun.findEnemy(id)->state=EnemyState::Stunned;stun.findEnemy(id)->stateTime=1;tick(stun,30);
    check(stun.stats.projectiles==0&&stun.findEnemy(id)->maw->cast.attackFrame==-1,"stun cancels committed cast");
}
void psychicAndHoming() {
    auto s=fixture();const auto id=s.spawnMonster(monsterId(26,2),{0,.85f,0});acquire(s,id);tick(s,8);
    check(!s.projectiles.empty(),"Psychic shot emitted");const auto &b=s.projectiles[0];
    check(b.kind==ProjectileKind::Homing&&b.sourceHoming&&near(b.damage,20)&&near(b.radius,.33f),"whole-heart base damage, scale1.5 and source homing");
    auto h=fixture();h.player.position={5,.85f,5};
    Event shot;shot.hostile=true;shot.projectileKind=ProjectileKind::Homing;shot.projectileHoming=HostileHomingDefinition{};
    shot.position={0,.85f,0};shot.direction={1,0,0};shot.speed=21;h.queueRoot(shot);h.drainEvents();
    tick(h);const auto before=h.projectiles[0].position;const auto dir=unit(horizontal(sub(h.player.position,before)));tick(h);
    check(near(h.projectiles[0].velocity.x,(21+dir.x*4.2f)*.92f)&&near(h.projectiles[0].velocity.z,dir.z*4.2f*.92f),"independent30Hz homing recurrence without speed normalization");
    auto far=fixture();far.player.position={0,.85f,40};far.queueRoot(shot);far.drainEvents();tick(far,12);
    check(near(far.projectiles[0].velocity.x,21)&&near(far.projectiles[0].velocity.z,0),"outside native100-unit range no steering/friction");
}
void offspring() {
    auto s=fixture();const auto parent=s.spawnMonster(monsterId(26,2),{0,.85f,0});tick(s,180);
    EntityId child=0;for(const auto &e:s.enemies)if(e.monster==monsterId(96))child=e.id;
    check(child&&s.findEnemy(child)->partner==parent,"Psychic requires parent-linked Eternal Fly");
    auto *fly=s.findEnemy(child);check(fly->eternalFly&&fly->eternalFly->orbitTicks>70&&near(fly->hp,960),"300 sourceHP and growing ellipse");
    check(planarDistance(fly->position,s.findEnemy(parent)->position)<3.2f,"orbit stays near moving parent");
    hit(s,child,10000);check(near(s.findEnemy(child)->hp,960),"orbit invulnerable to ordinary damage");
    const auto ticks=s.findEnemy(child)->eternalFly->orbitTicks;hit(s,parent,1000);
    fly=s.findEnemy(child);check(fly&&fly->alive&&fly->monster==monsterId(18)&&!fly->partner,"release in parent death, same entity");
    check(s.roomThreats()==1&&fly->buzz->healingTicks==ticks,"release blocks room completion and retains orbit-age regen timer");
    const float maximum=fly->maxHp;hit(s,child,maximum/2);tick(s,2);
    fly=s.findEnemy(child);check(near(fly->hp,maximum/2+maximum/60),"released fly heals maxHP/60 per source frame");
    tick(s,ticks*2+4);fly=s.findEnemy(child);check(fly&&fly->buzz->healingTicks==0,"healing expires after recorded orbit frames");
    hit(s,child,maximum/2);const float hurt=s.findEnemy(child)->hp;tick(s,4);check(near(s.findEnemy(child)->hp,hurt),"no indefinite regeneration");
    auto pressure=fixture();pressure.limits.enemies=1;const auto p=pressure.spawnMonster(monsterId(26,2),{0,.85f,0});tick(pressure,20);
    check(pressure.livingEnemies()==1,"child remains queued under capacity");pressure.enterRoom(1);pressure.enterRoom(0);
    pressure.limits.enemies=2;tick(pressure,4);
    check(pressure.livingEnemies()==2&&pressure.findEnemy(p),"required child survives room round trip and eventually spawns once");
}
void deathAndPressure() {
    for(int limit:{0,3}) {
        auto s=fixture();const auto id=s.spawnMonster(monsterId(26,1),{0,.85f,0});s.limits.projectiles=size_t(limit);
        hit(s,id,1000);tick(s,8);check(s.findEnemy(id)&&s.findEnemy(id)->maw->deathPending&&s.stats.projectiles==0,"death cross waits atomically");
        s.limits.projectiles=4;tick(s,2);check(s.stats.projectiles==4&&!s.findEnemy(id),"one complete death burst after recovery");
        for(const auto &p:s.projectiles)check(near(length(p.velocity),24)&&(near(p.velocity.x,0)||near(p.velocity.z,0)),"cardinal cross speed24");
        tick(s,4);check(s.stats.projectiles==4,"no duplicate death payload");
    }
    auto s=fixture();const auto id=s.spawnMonster(monsterId(26),{0,.85f,0});acquire(s,id);s.limits.projectiles=0;tick(s,24);
    check(s.findEnemy(id)->maw->cast.attackFrame==4&&s.stats.projectiles==0,"living cast holds Shoot event when full");
    s.limits.projectiles=100;tick(s,2);check(s.stats.projectiles==1,"living cast resumes once");
}
void configAndPlacement() {
    const auto path=std::filesystem::temp_directory_path()/("dw-maw-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(path);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());
    const auto file=path/"maw_family.mechanics";std::ifstream in(file);const std::string original((std::istreambuf_iterator<char>(in)),{});
    for(const auto &entry:std::vector<std::pair<std::string,std::string>>{{".1 .13 .93",".1 .13 1"},{"96.0.0 10 4.2","9999.0.0 10 4.2"},{"7 28 20 4","0 28 20 4"}}) {
        auto text=original;const auto at=text.find(entry.first);check(at!=text.npos,"config fixture exists");text.replace(at,entry.first.size(),entry.second);std::ofstream(file)<<text;
        bool rejected=false;try{MechanicsLibrary::load(path);}catch(...){rejected=true;}check(rejected,"invalid profile rejected");
    }
    std::ofstream(file)<<original;auto before=MechanicsLibrary::load(path);auto text=original;auto at=text.find(".1 .13 .93");text.replace(at,10,".1 .20 .93");std::ofstream(file)<<text;
    auto after=MechanicsLibrary::load(path);check(near(before->maw(monsterId(26))->force,.13f)&&near(after->maw(monsterId(26))->force,.2f)&&before->fingerprint()!=after->fingerprint(),"immutable external reload");std::filesystem::remove_all(path);
    std::array<bool,3> found{};
    for(uint64_t seed=0;seed<128&&!std::all_of(found.begin(),found.end(),[](bool x){return x;});++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==26&&!found[size_t(e.monster.variant)]) {
            found[size_t(e.monster.variant)]=true;check(near(e.hp,64)&&s.arena.profile.band>=1,"correct stage and health");
            std::cout<<"NATURAL_MAW variant="<<e.monster.variant<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
        }
    }
    for(int floor=2;floor<6&&!found[2];++floor)for(uint64_t seed=0;seed<32&&!found[2];++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(26,2)&&!found[2]) {
            found[2]=true;check(near(e.hp,64)&&s.arena.profile.band>=1,"Psychic stage and health");
            const auto &residents=s.roomEnemies(room);
            check(std::count_if(residents.begin(),residents.end(),[&](const auto &child){return child.monster==monsterId(96)&&child.partner==e.id;})==1,
                "naturally prepared Psychic Maw retains its required child before entry");
            std::cout<<"NATURAL_MAW variant=2 seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
        }
    }
    check(std::all_of(found.begin(),found.end(),[](bool x){return x;}),"all three variants reachable in seeded rooms");
    for(int p=0;p<4;++p)for(const auto &entry:defaultMechanics()->encounterPool(0,EncounterPattern(p)).specialists)check(entry.monster.type!=26&&entry.monster.type!=96,"no opening-floor Maw or ordinary Eternal Fly");
}
}
int main(){try{movementAndShot();psychicAndHoming();offspring();deathAndPressure();configAndPlacement();std::cout<<"PASS Maw family: movement, timing, homing, linked orbit/release/regen, queue pressure, external config and seeded rooms\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
