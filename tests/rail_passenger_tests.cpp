#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-passengers-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(const std::string &from,const std::string &to) {
        const auto file=path/"rail_passengers.mechanics";std::ifstream in(file);std::string s((std::istreambuf_iterator<char>(in)),{});
        const auto at=s.find(from);check(at!=std::string::npos,"test row exists: "+from);s.replace(at,from.size(),to);std::ofstream(file)<<s;
    }
    void table(std::string rows) {
        const auto file=path/"rail_passengers.mechanics";std::ifstream in(file);std::string result,line;
        while(std::getline(in,line))if(!line.starts_with("rail_passenger "))result+=line+'\n';
        in.close();std::ofstream(file)<<result<<rows;
    }
    auto fast(MonsterId id=monsterId(33)) {
        replace("1 150 359 135 2 30 12 .3","1 2 2 135 1 30 12 .3");
        table("rail_passenger 906.0.0 "+monsterIdText(id)+" available\n");return MechanicsLibrary::load(path);
    }
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics(),bool rails=true,const std::string &layout="hornfel_special_5228") {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-60,-1,-60},{200,6,80}};s.arena.rooms.resize(2);
    for(int n=0;n<2;++n) {
        auto &r=s.arena.rooms[size_t(n)];r.bounds={{float(n)*120-40,0,-30},{float(n)*120+40,4,30}};
        r.center=r.entry=r.objective=r.reward=r.bossSpawn={float(n)*120,.85f,0};r.kind=RoomKind::Combat;
        r.floors={r.bounds};r.floors[0].min.y=-.4f;r.floors[0].max.y=0;
    }
    s.rooms.assign(2,{});s.room=0;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.pendingEnemyBombs.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={0,.85f,25};s.godMode=true;s.debugScenario=true;s.roomClear=false;
    if(rails) {
        s.arena.profile.bossRails=std::make_shared<RailLayout>(*lib->railLayout(layout));s.arena.prepareRailArena(0);
        check(s.spawnMonster(monsterId(906),{0,.85f,0})!=0,"fixture has a live boss");
        // Hold the real boss outside while testing the independent controller.
        s.rooms[0].hornfel->clock=100000;
    }
    return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float amount,bool explosion=false,DamageKind kind=DamageKind::Physical,bool drain=true) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;e.explosionDamage=explosion;
    check(s.queueRoot(e),"damage admitted");if(drain)s.drainEvents();
}
EntityId rider(Simulation &s) {
    for(int n=0;n<100;++n) {
        for(const auto &r:s.rooms[0].hornfel->traffic.passengers)if(r.cart.visible)return r.actor;
        tick(s);
    }
    throw std::runtime_error("passenger never became visible");
}
void validation() {
    const auto lib=defaultMechanics();const auto before=lib->fingerprint();const auto *p=lib->railTraffic(monsterId(906));
    check(p&&p->enabled&&p->passengers.size()==7,"complete ordered native table retained");
    const int types[]{823,820,827,227,87,33,292};
    for(int n=0;n<7;++n)check(p->passengers[size_t(n)].actor==monsterId(types[n])&&p->passengers[size_t(n)].available==(n>=5),"pending creature slots never impersonate implemented AI");
    auto reject=[](const std::string &from,const std::string &to,const std::string &why){Pack p;p.replace(from,to);bool caught=false;try{MechanicsLibrary::load(p.path);}catch(const std::exception &e){caught=std::string(e.what()).find(why)!=std::string::npos;}check(caught,"invalid data rejected: "+why);};
    reject("1 150 359 135 2 30 12 .3","1 150 359 135 2 nan 12 .3","finite");
    reject("1 150 359 135 2 30 12 .3","1 150 149 135 2 30 12 .3","Integer");
    reject("823.0.0 pending","823.0.0 available","not implemented");
    reject("823.0.0 pending","33.0.0 available","Duplicate");
    reject("fireplace 3.2 10","fireplace 0 10","Invalid environment");
    reject("monster 33.0.0 \"Fire Place\" Still None Blob 5","monster 33.0.0 \"Fire Place\" Still None Blob 6","identity");
    {Pack p;p.table("");bool caught=false;try{MechanicsLibrary::load(p.path);}catch(...){caught=true;}check(caught,"empty table rejected");}
    {Pack p;auto changed=p.fast();check(changed->fingerprint()!=before&&lib->fingerprint()==before&&lib->railTraffic(monsterId(906))->initialMin==150,"new snapshots leave the running library unchanged");}
}
void clocksAndAdmission() {
    auto s=fixture(defaultMechanics(),true,"hornfel_special_5227");tick(s,2);auto &t=s.rooms[0].hornfel->traffic;
    check(t.initialized&&t.lifespan>=150&&t.lifespan<=359&&t.timeout==t.lifespan-1,"large room initial interval stays unhalved");
    const int remaining=t.timeout;tick(s,remaining*2);check(t.expired&&t.attempts==0,"expiry latch precedes next controller attempt");
    tick(s,2);check(t.attempts==1&&t.lifespan>=75&&t.lifespan<=179&&t.timeout==t.lifespan-1,"subsequent large-room interval halves after attempt");
    {Pack p;p.replace("1 150 359 135 2 30 12 .3","1 2 2 135 1 30 12 .3");p.table("rail_passenger 906.0.0 823.0.0 pending\n");auto q=fixture(MechanicsLibrary::load(p.path));tick(q,12);const auto &u=q.rooms[0].hornfel->traffic;check(u.attempts==2&&u.unavailable==2&&u.spawned==0,"pending selection consumes interval without reroll");}
    {Pack p;auto q=fixture(p.fast());q.limits.enemies=q.livingEnemies();tick(q,6);const auto &u=q.rooms[0].hornfel->traffic;check(u.attempts==1&&u.capacityRejected==1&&u.passengers.empty(),"capacity admission has no orphan cart or rider");q.limits.enemies=256;tick(q,4);check(u.spawned==1,"next complete interval can admit a rider");}
    {Pack p;auto q=fixture(p.fast());q.findEnemy(q.rooms[0].hornfel->owner)->alive=false;tick(q,60);const auto &u=q.rooms[0].hornfel->traffic;check(u.expired&&u.attempts==0,"no live boss holds the expired controller without spawning");}
    {Pack p;auto q=fixture(p.fast());tick(q,120);auto &h=*q.rooms[0].hornfel;check(h.traffic.blocked>0,"occupied paired doors block subsequent attempts");std::set<int> ends;
        for(const auto &r:h.traffic.passengers){const auto &route=q.arena.rails->paths[size_t(r.cart.route)];check(!ends.contains(route.entry)&&!ends.contains(route.exit),"no two passengers share a reserved endpoint");ends.insert(route.entry);ends.insert(route.exit);}
        const auto t=h.traffic.timeout;const auto d=h.traffic.passengers.front().cart.distance;q.enterRoom(1);q.player.position={120,.85f,25};tick(q,120);q.enterRoom(0);q.player.position={0,.85f,25};check(h.traffic.timeout==t&&near(h.traffic.passengers.front().cart.distance,d),"inactive room pauses controller and transport");}
}
void durability() {
    auto s=fixture(defaultMechanics(),false);const auto fire=s.spawnMonster(monsterId(33),{0,.7f,0});const auto tnt=s.spawnMonster(monsterId(292),{8,1,0});
    check(s.roomThreats()==0&&s.findEnemy(fire)->hp==5&&s.findEnemy(tnt)->hp==4,"environment durability is not HP scaling or clear-room threat");
    auto high=s;hit(s,fire,32);hit(high,fire,32.01f);check(near(s.findEnemy(fire)->hp-high.findEnemy(fire)->hp,1),"normal fire strict ten-source-unit threshold changes loss by one");
    auto batch=s;for(int n=0;n<3;++n)hit(batch,tnt,24,false,DamageKind::Physical,false);batch.drainEvents();
    check(batch.findEnemy(tnt)->hp>=2&&batch.findEnemy(tnt)->hp<=3,"TNT loses one/two durability for a complete batch");
    auto one=s;hit(one,tnt,999);check(near(one.findEnemy(tnt)->hp,batch.findEnemy(tnt)->hp),"TNT batch durability is independent of strength and hit count");
    const auto hp=s.findEnemy(fire)->hp;hit(s,fire,0);hit(s,fire,100,false,DamageKind::Flame);check(near(s.findEnemy(fire)->hp,hp),"fire ignores zero damage and flame exposure");
    hit(s,fire,1,true);check(s.findEnemy(fire)->environment->spent&&s.findEnemy(fire)->hp==1&&s.stats.kills==0,"explosion extinguishes to persistent ash without enemy kill");
    s.godMode=false;s.player.position=s.findEnemy(fire)->position;tick(s);check(near(s.player.hp,StartingHealth),"ash has no contact damage");
    Event shot;shot.position=shot.origin=s.findEnemy(fire)->position;shot.direction={1,0,0};shot.speed=26;shot.damage=24;s.queueRoot(shot);s.drainEvents();tick(s);check(!s.projectiles.empty()&&s.projectiles.back().alive,"ash does not absorb projectiles");
    auto flood=fixture(defaultMechanics(),false);auto f=flood.spawnMonster(monsterId(33),{0,.7f,0});flood.arena.rooms[0].flooded=true;tick(flood);check(flood.findEnemy(f)->environment->spent,"flooded ground extinguishes unmounted normal fire");
    auto shoot=fixture(defaultMechanics(),false);f=shoot.spawnMonster(monsterId(33),{0,.7f,0});Event bullet;bullet.position=bullet.origin={-1,.7f,0};bullet.direction={1,0,0};bullet.speed=26;bullet.damage=24;shoot.queueRoot(bullet);shoot.drainEvents();tick(shoot,2);check(shoot.findEnemy(f)->hp<5,"actual player projectile reaches fire durability");
}
void blastAndContact() {
    auto s=fixture(defaultMechanics(),false);const auto tnt=s.spawnMonster(monsterId(292),{0,1,0});const auto victim=s.spawnMonster(monsterId(10),{3,.85f,0});s.findEnemy(victim)->hp=500;
    hit(s,tnt,1,true,DamageKind::Physical,false);s.limits.queuedEvents=0;s.drainEvents();
    check(s.findEnemy(tnt)->environment->destructionPending&&!s.findEnemy(tnt)->environment->spent,"full queue retains mandatory TNT detonation");
    auto pending=s;pending.findEnemy(victim)->alive=false;pending.debugScenario=false;tick(pending);check(!pending.roomClear,"pending destruction cannot clear room early");s.limits.queuedEvents=8192;s.drainEvents();s.drainEvents();
    check(s.findEnemy(tnt)->alive&&s.findEnemy(tnt)->environment->spent&&near(s.findEnemy(tnt)->hp,.5f),"ground TNT becomes inert scrap after accepted blast");
    check(near(s.findEnemy(victim)->hp,180),"TNT neutral blast damages hostile creature once");s.drainEvents();tick(s);check(near(s.findEnemy(victim)->hp,180),"TNT never repeats its explosion");
    auto flame=fixture(defaultMechanics(),false);const auto barrel=flame.spawnMonster(monsterId(292),{0,1,0});flame.addFire({0,1,0},1,3,0,false,false);tick(flame,2);check(flame.findEnemy(barrel)->environment->spent,"hostile zero-damage flame ignites TNT");
    auto touch=fixture(defaultMechanics(),false);const auto fire=touch.spawnMonster(monsterId(33),{0,.7f,0});touch.player.position={0,.85f,0};touch.godMode=false;tick(touch);check(touch.player.hp<StartingHealth&&touch.findEnemy(fire)->hp==5,"fire hurts player but not itself");
    auto push=fixture(defaultMechanics(),false);const auto box=push.spawnMonster(monsterId(292),{0,1,0});push.player.position={-.9f,.85f,0};Input walk;walk.movement={1,0,0};for(int i=0;i<30;++i)push.step(walk);check(push.findEnemy(box)->position.x>1&&near(push.findEnemy(box)->hp,4),"walking physically pushes TNT without damage");
}
void lifecycle() {
    for(auto type:{33,292}) {
        Pack p;auto s=fixture(p.fast(monsterId(type)));const auto id=rider(s);auto &h=*s.rooms[0].hornfel;
        const auto &r=h.traffic.passengers.front();check(s.findEnemy(id)->railCarrier==r.cart.id,"carrier identity differs from attributed summoner");
        check(s.findEnemy(id)->spawnerType==906,"original rail spawner type is captured independently of its carrier");
        if(type==33){s.arena.rooms[0].flooded=true;tick(s);check(!s.findEnemy(id)->environment->spent,"mounted fireplace stays dry above flooded ground");}
        s.findEnemy(h.owner)->alive=false;const auto attempts=h.traffic.attempts,spawned=h.traffic.spawned;tick(s,1800);
        check(h.traffic.attempts==attempts&&h.traffic.removed==spawned&&h.traffic.passengers.empty(),"surviving passengers quietly exit after boss death with no new arrivals");
        check(s.stats.kills==0&&s.moneyPickups.empty()&&s.enemyBombs.empty(),"normal exit has no kill loot or aftermath");
    }
    {Pack p;auto s=fixture(p.fast(monsterId(292)));const auto id=rider(s);auto &h=*s.rooms[0].hornfel;s.findEnemy(h.owner)->alive=false;hit(s,id,1,true);s.drainEvents();tick(s,10);check(h.traffic.destroyed>=1&&(!s.findEnemy(id)||!s.findEnemy(id)->alive),"destroyed mounted TNT removes rider and breaks its empty cart");}
    {Pack p;auto s=fixture(p.fast());const auto id=rider(s);auto &h=*s.rooms[0].hornfel;s.findEnemy(h.owner)->alive=false;
        const auto extra=s.spawnMonster(monsterId(10),{0,.85f,0});s.debugScenario=false;tick(s);check(!s.roomClear&&s.findEnemy(id)&&!h.doors.empty(),"boss death alone does not remove riders while ordinary threat survives");
        s.findEnemy(extra)->alive=false;tick(s);check(s.roomClear&&h.traffic.stopped&&h.traffic.passengers.empty()&&h.doors.empty(),"actual room clear quietly removes attached passengers and doors");tick(s,20);check(h.traffic.passengers.empty(),"cleared traffic stays stopped");}
    {auto s=fixture(defaultMechanics(),false);auto fire=s.spawnMonster(monsterId(33),{0,.7f,0});s.debugScenario=false;tick(s);check(s.roomClear&&s.findEnemy(fire)&&s.findEnemy(fire)->alive,"ordinary unmounted fire persists through room clear");
        hit(s,fire,1,true);s.enterRoom(1);s.enterRoom(0);check(s.findEnemy(fire)&&s.findEnemy(fire)->environment->spent,"ash remains spent on cleared-room re-entry");}
}
}
int main(){try{validation();clocksAndAdmission();durability();blastAndContact();lifecycle();std::cout<<"PASS rail passengers/environmental durability, transport, lifecycle and admission\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
