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
struct Content {
    std::filesystem::path dir=std::filesystem::temp_directory_path()/("dw-buzz-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Content(){std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
        std::ifstream in(dir/"buzz_flies.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Content(){std::filesystem::remove_all(dir);}
    std::shared_ptr<const MechanicsLibrary> load(std::string text){std::ofstream(dir/"buzz_flies.mechanics")<<text;return MechanicsLibrary::load(dir);}
};
std::string replace(std::string text,const std::string &old,const std::string &value){const auto at=text.find(old);check(at!=std::string::npos,"test profile row exists");text.replace(at,old.size(),value);return text;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-20,-1,-20},{20,8,20}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-20,-.4f,-20},{20,0,20}}};}
    s.arena.boundaryWalls={{{-21,-1,-21},{-20,8,21}},{{20,-1,-21},{21,8,21}},{{-21,-1,-21},{21,8,-20}},{{-21,-1,20},{21,8,21}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId add(Simulation &s,int type){const auto id=s.spawnMonster(monsterId(type),{0,.85f,0});s.findEnemy(id)->cooldown=0;return id;}
void dung(Simulation &s,float half=.7f,bool spent=false){Breakable p;p.id=19;p.room=0;p.kind=BreakableKind::Dung;p.bounds={{-half,0,-half},{half,1.1f,half}};p.health=spent?0:4;p.initialHealth=4;p.destroyed=spent;p.paid=spent;s.arena.breakables={p};s.arena.rebuildWalls();}
void kill(Simulation &s,EntityId id){Event d;d.type=EventType::Damage;d.target=id;d.damage=100;s.queueRoot(d);s.drainEvents();tick(s);}
void motion() {
    auto a=fixture(),b=fixture();const auto x=add(a,13),y=add(b,13);
    check(near(a.findEnemy(x)->hp,9.6f)&&a.roomThreats()==1,"harmless source Fly health and room-clear participation");
    float path=0,side=0;Vector3 last=a.findEnemy(x)->position;
    for(int frame=0;frame<600;++frame) {
        tick(a);tick(b);const auto &e=*a.findEnemy(x),&other=*b.findEnemy(y);
        check(distance(e.position,other.position)<1e-6f,"same seeded inputs reproduce buzzing");
        path+=distance(last,e.position);side=std::max(side,std::abs(e.position.x));last=e.position;
        check(!a.arena.flightBlocked(e.position,e.radius,0)&&length(horizontal(e.velocity))<=24.001f,"physical flight stays bounded");
    }
    check(path>8&&side>.15f&&a.findEnemy(x)->position.z>2,"Fly actually buzzes and drifts toward the player");
    check(a.stats.projectiles==0&&a.roomThreats()==1&&!a.roomClear,"Fly neither attacks nor prematurely clears its room");
    a.godMode=false;a.player.position=a.findEnemy(x)->position;tick(a);check(near(a.player.hp,StartingHealth),"Fly touch harmless");
    kill(a,x);check(a.roomThreats()==0&&a.stats.kills==1,"Fly death resolves one room threat");
    std::cout<<"BUZZ path="<<path<<" side="<<side<<'\n';
}
void shooter() {
    Content content;auto text=replace(content.original,"buzz_fly 14.0.0 .1 5 .7 .6 .4 .6 .06 3 24","buzz_fly 14.0.0 .1 5 0 0 .4 .6 0 3 24");
    auto s=fixture(content.load(text));const auto id=add(s,14);check(near(s.findEnemy(id)->hp,25.6f),"Pooter source HP8x3.2");
    while(s.findEnemy(id)->state!=EnemyState::Windup&&s.stats.duration<.3)tick(s);
    check(s.findEnemy(id)->state==EnemyState::Windup,"Pooter acquires within7source frames");const auto began=s.stats.duration;
    tick(s,11);check(s.projectiles.empty(),"Pooter waits for Shoot6");s.player.position={25,.85f,0};tick(s);
    check(s.projectiles.size()==1&&near(s.projectiles[0].velocity.x,21)&&near(s.projectiles[0].velocity.z,0),"current aim survives leaving range");
    tick(s,15);check(s.findEnemy(id)->state==EnemyState::Windup,"full14-frame animation recovery");tick(s);check(s.findEnemy(id)->state==EnemyState::Ready,"recovery ends14frames");
    s.player.position={0,.85f,10};while(s.stats.projectiles<2&&s.stats.duration-began<2)tick(s);
    check(s.stats.projectiles==2&&std::abs(s.stats.duration-began-41./30)<.0001,"35-frame cooldown starts on acquisition");
    auto blocked=fixture(content.load(text));add(blocked,14);blocked.arena.walls.push_back({{-2,0,4},{2,5,5}});tick(blocked,120);
    check(blocked.stats.projectiles==0,"Pooter cannot acquire through solid cover");
    auto pressure=fixture(content.load(text));const auto p=add(pressure,14);pressure.limits.projectiles=0;tick(pressure,45);
    check(pressure.stats.projectiles==0&&pressure.findEnemy(p)->buzz->attackFrame==6,"full projectile capacity retains Shoot");
    pressure.limits.projectiles=512;tick(pressure,2);check(pressure.stats.projectiles==1,"retained shot admitted once");
    auto death=fixture(content.load(text));const auto d=add(death,14);
    while(death.findEnemy(d)->state!=EnemyState::Windup&&death.stats.duration<.3)tick(death);
    kill(death,d);tick(death,60);check(death.stats.projectiles==0,"death cancels pending shot");
    auto harm=fixture(content.load(text));harm.godMode=false;add(harm,14);tick(harm,65);check(near(harm.player.hp,87.5f),"physical Pooter shot applies hostile damage once");
}
void transformationAndDung() {
    Content config;auto text=replace(config.original,"dung_morph 13.0.0 14.0.0 1000","dung_morph 13.0.0 14.0.0 1");
    const auto lib=config.load(text);
    for(bool spent:{false,true}) {
        auto s=fixture(lib);dung(s,.7f,spent);const auto id=add(s,13);s.findEnemy(id)->hp=1;s.findEnemy(id)->summoner=123;
        tick(s,2);const auto *e=s.findEnemy(id);
        check(e&&e->monster==monsterId(14)&&near(e->hp,25.6f)&&e->summoner==123,"morph keeps actor/owner, restores Pooter health");
        check(s.stats.kills==0&&s.roomThreats()==1&&!s.roomClear,"live morph grants no kill and preserves room lock");
        check(spent?s.arena.breakables[0].health==0:(s.arena.breakables[0].health>=1&&s.arena.breakables[0].health<=3),"Hurt1 has two one-in-three bonus steps; spent grid still permits morph");
        kill(s,id);check(s.stats.kills==1&&s.roomThreats()==0,"one final death after morph");
    }
    auto s=fixture();int transformed=0;dung(s,8);
    for(int trial=0;trial<1000;++trial) {
        s.enemies.clear();s.projectiles.clear();s.stats={};s.roomClear=false;s.combatRng=Random(uint64_t(trial));
        s.arena.breakables[0].health=4;s.arena.breakables[0].destroyed=false;s.arena.breakables[0].paid=false;s.arena.rebuildWalls();
        const auto id=add(s,13);for(int frame=0;frame<60&&s.findEnemy(id)->monster==monsterId(13);++frame)tick(s);
        transformed+=s.findEnemy(id)->monster==monsterId(14);
    }
    check(transformed>=15&&transformed<=48,"production one-in1000 chance sampled over30source frames, not fixed dwell time");
    std::cout<<"DUNG_MORPHS trials=1000 updates=30 transformed="<<transformed<<'\n';
    auto blast=fixture();dung(blast);check(!blast.arena.sight({0,.85f,-3},{0,.85f,3}),"intact dung blocks shots");
    Event bomb;bomb.type=EventType::Explosion;bomb.position={0,.85f,-2};bomb.radius=4;bomb.damage=80;bomb.demolition=Demolition::SpentDynamite;
    blast.queueRoot(bomb);blast.drainEvents();check(blast.arena.breakables[0].destroyed&&blast.arena.sight({0,.85f,-3},{0,.85f,3}),"bomb destroys dung and opens collision");
    auto shot=fixture();dung(shot);shot.player.position={0,.85f,-3};Input fire;fire.fire=true;fire.aim={0,.85f,0};shot.step(fire);tick(shot,15);
    check(shot.arena.breakables[0].health<4&&!shot.arena.breakables[0].destroyed,"ordinary player shot damages dung without requiring bomb");
}
void superPooter() {
    Content config;
    const auto text=replace(config.original,"buzz_fly 14.1.0 .1 5 .7 .6 .4 .6 .06 3 24","buzz_fly 14.1.0 .1 5 0 0 .4 .6 0 3 24");
    const auto lib=config.load(text);
    auto spawn=[](Simulation &s){const auto id=s.spawnMonster(monsterId(14,1),{0,.85f,0});s.findEnemy(id)->cooldown=0;return id;};
    auto acquire=[](Simulation &s,EntityId id){for(int i=0;i<16&&s.findEnemy(id)->state!=EnemyState::Windup;++i)tick(s);
        check(s.findEnemy(id)->state==EnemyState::Windup,"Super Pooter acquires within seven source frames");};
    auto s=fixture(lib);const auto id=spawn(s);
    check(near(s.findEnemy(id)->hp,25.6f)&&s.roomThreats()==1,"Super Pooter has source8HP, harmless contact, one threat");
    acquire(s,id);const auto began=s.stats.duration;
    tick(s,11);check(s.stats.projectiles==0,"pair waits for Shoot6");
    s.player.position={25,.85f,0};tick(s);
    check(s.projectiles.size()==2,"pair emitted together at Shoot6 using current target outside acquisition range");
    check(near(s.projectiles[0].velocity.x,21*.961f)&&near(s.projectiles[1].velocity.x,21*.961f)&&
        near(s.projectiles[0].velocity.z,21*.276f)&&near(s.projectiles[1].velocity.z,-21*.276f),"source coefficients preserve unnormalized V velocities");
    for(const auto &p:s.projectiles)check(p.context.sourceEntity==id&&near(p.damage,10),"pair preserves attribution and unscaled base damage");
    tick(s,16);check(s.findEnemy(id)->state==EnemyState::Ready,"pair recovers at animation14");
    s.player.position={0,.85f,10};while(s.stats.projectiles<4&&s.stats.duration-began<2)tick(s);
    check(s.stats.projectiles==4&&std::abs(s.stats.duration-began-41./30)<.0001,"pair repeats from acquisition35 plus Shoot6");
    auto harm=fixture(lib);spawn(harm);for(int i=0;i<60&&harm.projectiles.empty();++i)tick(harm);
    check(harm.projectiles.size()==2,"physical damage fixture emits pair");
    harm.godMode=false;harm.player.position=dw::add(harm.projectiles.front().position,mul(harm.projectiles.front().velocity,1.f/60));
    tick(harm);check(near(harm.player.hp,87.5f),"Super Pooter impact applies hostile damage multiplier once");
    for(int mode=0;mode<3;++mode) {
        auto limited=fixture(lib);const auto owner=spawn(limited);
        if(mode==0)limited.limits.projectiles=1;
        if(mode==1)limited.limits.queuedEvents=1;
        if(mode==2)limited.limits.eventsPerChain=0;
        tick(limited,45);check(limited.stats.projectiles==0&&limited.findEnemy(owner)->buzz->attackFrame==6,"capacity never admits half of a pair");
        limited.limits.projectiles=512;limited.limits.queuedEvents=16384;limited.limits.eventsPerChain=256;
        tick(limited,2);check(limited.stats.projectiles==2,"retained pair admitted exactly once");
    }
    const auto skatole=parseItemKey("isaac:collectible:9");
    for(int variant=0;variant<=1;++variant) {
        auto calm=fixture();const auto owner=calm.spawnMonster(monsterId(14,variant),{0,.85f,0});calm.findEnemy(owner)->cooldown=0;
        calm.grant(skatole);const auto start=calm.findEnemy(owner)->position;tick(calm,180);
        check(calm.stats.projectiles==0&&calm.roomThreats()==1&&planarDistance(start,calm.findEnemy(owner)->position)>.1f,"Skatole suppresses shooting without stopping buzzing or clearing threat");
        calm.godMode=false;calm.player.position=calm.findEnemy(owner)->position;tick(calm);
        check(near(calm.player.hp,StartingHealth),"Pooter variants remain harmless on contact");
        calm.godMode=true;calm.player.position={0,.85f,10};
        calm.items.clear();tick(calm,60);check(calm.stats.projectiles>0,"removing Skatole restores normal shooting");
    }
    auto mid=fixture(lib);const auto owner=spawn(mid);acquire(mid,owner);tick(mid,4);
    const auto delay=mid.findEnemy(owner)->cooldown;mid.grant(skatole);tick(mid,8);
    check(mid.stats.projectiles==0&&near(mid.findEnemy(owner)->cooldown,delay),"Skatole consumes pending Shoot and freezes source delay");
    mid.items.clear();tick(mid,16);
    check(mid.stats.projectiles==0&&mid.findEnemy(owner)->state==EnemyState::Ready,"removed item does not replay suppressed Shoot");
    auto dying=fixture(lib);const auto victim=spawn(dying);acquire(dying,victim);kill(dying,victim);tick(dying,60);
    check(dying.stats.projectiles==0&&dying.stats.kills==1&&dying.roomThreats()==0,"Super Pooter dies once and cancels pair");
    for(const auto &bad:{"buzz_pair 14.1.0 0 .276","buzz_pair 14.1.0 .961 -1","buzz_pair 13.0.0 .961 .276"}) {
        bool rejected=false;try{config.load(replace(config.original,"buzz_pair 14.1.0 .961 .276",bad));}catch(...){rejected=true;}
        check(rejected,"invalid pair or pair without shooter rejected");
    }
    bool rejected=false;try{config.load(replace(config.original,"buzz_suppress 14.1.0 isaac:collectible:9","buzz_suppress 14.1.0 missing:collectible:9"));}catch(...){rejected=true;}
    check(rejected,"unknown suppressor item rejected");
    const auto before=config.load(config.original);
    const auto after=config.load(replace(config.original,"buzz_pair 14.1.0 .961 .276","buzz_pair 14.1.0 .9 .4"));
    check(near(before->buzzFly(monsterId(14,1))->pairSide,.276f)&&near(after->buzzFly(monsterId(14,1))->pairSide,.4f)&&before->fingerprint()!=after->fingerprint(),"external pair reload creates immutable snapshots");
    for(int band=0;band<=3;++band) {
        bool found=false;
        for(uint64_t seed=0;seed<80&&!found;++seed) {
            ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
            int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            Simulation natural(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            check(natural.arena.profile.band==band,"natural witness uses the requested stage band");
            for(int room=1;room<natural.finalRoom();++room) {
                int count=0;for(const auto &e:natural.roomEnemies(room))if(e.monster==monsterId(14,1))++count;
                check(count<=1,"one Super Pooter maximum per natural room");
                if(count&&!found){found=true;std::cout<<"NATURAL_SUPER_POOTER seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<band<<'\n';}
            }
        }
        check(found,"Super Pooter reachable in every intended stage band");
    }
    std::cout<<"PASS Super Pooter source pair, timing, health, atomic capacity, Skatole dependency, death, configuration and stage placement\n";
}
void attackFly() {
    Content config;
    const auto quiet=replace(config.original,"buzz_fly 18.0.0 .1 5 0 .6 .4 .6 .06 3 24","buzz_fly 18.0.0 .1 5 0 0 .4 .6 0 3 24");
    const auto lib=config.load(quiet);
    auto horizontal=fixture(lib),vertical=fixture(lib);
    horizontal.player.position={4,.85f,0};vertical.player.position={0,.85f,4};
    const auto x=add(horizontal,18),z=add(vertical,18);
    tick(horizontal,12);tick(vertical,12);
    check(near(horizontal.findEnemy(x)->hp,16),"Attack Fly source5HPx3.2");
    check(horizontal.findEnemy(x)->position.x>.1f&&near(vertical.findEnemy(z)->position.z,0),"native second-axis scale doubles the effective vertical deadzone");
    auto diagonal=fixture(lib);diagonal.player.position={10,.85f,10};const auto d=add(diagonal,18);tick(diagonal,8);
    const auto v=diagonal.findEnemy(d)->velocity;
    check(v.x>0&&near(v.x,v.z*2),"pursuit normalizes after halving the second axis");
    const auto cached=diagonal.findEnemy(d)->buzz->target;diagonal.player.position={-10,.85f,-10};tick(diagonal,2);
    check(distance(diagonal.findEnemy(d)->buzz->target,cached)<.001f,"target remains cached between source third frames");
    tick(diagonal,2);check(distance(diagonal.findEnemy(d)->buzz->target,diagonal.player.position)<.001f,"target refresh follows current player on third frame");
    auto persistent=fixture();persistent.godMode=false;const auto p=add(persistent,18);persistent.player.position=persistent.findEnemy(p)->position;
    tick(persistent);check(near(persistent.player.hp,87.5f)&&persistent.findEnemy(p)&&persistent.stats.kills==0,"ordinary contact damages once without consuming fly");

    const auto skatole=parseItemKey("isaac:collectible:9");
    for(float health:{1.f,16.f}) {
        auto s=fixture();const auto id=add(s,18);s.findEnemy(id)->hp=health;s.findEnemy(id)->summoner=123;s.findEnemy(id)->generation=2;
        s.godMode=false;s.player.position=s.findEnemy(id)->position;s.grant(skatole);tick(s,2);
        const auto *e=s.findEnemy(id);
        check(e&&e->monster==monsterId(13)&&near(e->hp,std::min(health,9.6f))&&near(e->maxHp,9.6f),"Skatole morph clamps HP without healing damage");
        check(e->summoner==123&&e->generation==2&&s.stats.kills==0&&s.roomThreats()==1&&near(s.player.hp,StartingHealth),"same actor keeps ownership, threat and reward identity; item prevents pre-morph contact damage");
        s.items.clear();tick(s,2);check(s.findEnemy(id)->monster==monsterId(13),"removing Skatole does not reverse a completed morph");
    }
    auto liveHive=[&]() {
        auto s=fixture(lib);const auto parent=add(s,22);
        for(int frame=0;frame<120&&std::none_of(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.summoner==parent;});++frame)tick(s);
        auto child=std::find_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.monster==monsterId(18)&&e.summoner==parent;});
        check(child!=s.enemies.end()&&child->buzz&&child->buzz->diesOnContact&&near(child->buzz->contactRetention,.9f),"real Hive live-spawn route latches source contact flag and friction");
        const auto id=child->id;
        std::erase_if(s.enemies,[&](const auto &e){return e.id!=id;}); // Isolate this child after verifying the real summon route.
        s.moneyPickups.clear();
        return s;
    };
    auto damped=liveHive(),undamped=damped;
    undamped.enemies[0].buzz->diesOnContact=false;
    const auto start=damped.enemies[0].position;tick(damped,24);tick(undamped,24);
    check(planarDistance(start,damped.enemies[0].position)<planarDistance(start,undamped.enemies[0].position),"live-summon friction actually reduces pursuit travel");
    for(bool immune:{false,true}) {
        auto s=liveHive();const auto id=s.enemies[0].id;s.godMode=immune;s.player.position=s.enemies[0].position;
        tick(s);check(!s.findEnemy(id)&&s.stats.kills==1&&s.roomThreats()==0,"live Hive child expires once even on invulnerable contact and after parent removal");
        check(near(s.player.hp,immune?StartingHealth:87.5f),"live child uses ordinary contact damage");
        check(s.moneyPickups.empty(),"summoned contact death does not farm money");
    }
    auto limited=liveHive();const auto id=limited.enemies[0].id;limited.player.position=limited.enemies[0].position;limited.limits.queuedEvents=0;
    tick(limited);check(limited.findEnemy(id)&&limited.findEnemy(id)->selfDetonated,"full queue retains spent contact death");
    const auto at=limited.findEnemy(id)->position;limited.player.position={10,.85f,10};tick(limited,8);
    check(distance(limited.findEnemy(id)->position,at)<.001f&&limited.stats.kills==0,"spent contact actor cannot resume moving during queue pressure");
    limited.limits.queuedEvents=16384;tick(limited);check(!limited.findEnemy(id)&&limited.stats.kills==1,"retained contact death resolves once after capacity returns");
    auto calm=liveHive();const auto c=calm.enemies[0].id;calm.grant(skatole);tick(calm,2);
    check(calm.findEnemy(c)->monster==monsterId(13)&&calm.findEnemy(c)->buzz->diesOnContact,"live-summon contact flag survives harmless morph");
    calm.godMode=false;calm.player.position=calm.findEnemy(c)->position;tick(calm);
    check(!calm.findEnemy(c)&&calm.stats.kills==1&&near(calm.player.hp,StartingHealth),"morphed live child expires harmlessly");
    bool deathChild=false;
    for(uint64_t seed=0;seed<20&&!deathChild;++seed) {
        auto s=fixture();s.combatRng=Random(seed);const auto parent=add(s,22);
        Event hit;hit.type=EventType::Damage;hit.target=parent;hit.damage=s.findEnemy(parent)->hp;s.queueRoot(hit);s.drainEvents();tick(s);
        auto child=std::find_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.monster==monsterId(18);});
        if(child==s.enemies.end())continue;deathChild=true;const auto childId=child->id;
        check(!child->summoner&&(!child->buzz||!child->buzz->diesOnContact)&&near(child->hp,16),"Hive death release keeps ordinary HP and persistent contact");
        s.player.position=child->position;tick(s);check(s.findEnemy(childId)&&s.stats.kills==1,"death-spawned fly survives touching player");
    }
    check(deathChild,"real Hive death route exercised");
    for(const auto &bad:{
        "buzz_chase 18.0.0 0 2 .5 25 .08 1.2 10",
        "buzz_chase 18.0.0 3 2 0 25 .08 1.2 10",
        "buzz_chase 18.0.0 3 2 .5 -1 .08 1.2 10"}) {
        bool rejected=false;try{config.load(replace(config.original,"buzz_chase 18.0.0 3 2 .5 25 .08 1.2 10",bad));}catch(...){rejected=true;}
        check(rejected,"invalid chase profile rejected");
    }
    for(const auto &change:std::vector<std::pair<std::string,std::string>>{
        {"buzz_item_morph 18.0.0 isaac:collectible:9 13.0.0","buzz_item_morph 18.0.0 missing:collectible:9 13.0.0"},
        {"buzz_item_morph 18.0.0 isaac:collectible:9 13.0.0","buzz_item_morph 18.0.0 isaac:collectible:9 18.0.0"},
        {"buzz_contact_summon 18.0.0 22.0.0 .9","buzz_contact_summon 18.0.0 9999.0.0 .9"}}) {
        bool rejected=false;try{config.load(replace(config.original,change.first,change.second));}catch(...){rejected=true;}check(rejected,"bad morph target/item or summon source rejected");
    }
    const auto old=config.load(config.original),next=config.load(replace(config.original,"buzz_chase 18.0.0 3 2 .5 25 .08 1.2 10","buzz_chase 18.0.0 3 2 .75 25 .08 1.2 10"));
    check(near(old->buzzFly(monsterId(18))->chase->axisScale,.5f)&&near(next->buzzFly(monsterId(18))->chase->axisScale,.75f)&&old->fingerprint()!=next->fingerprint(),"chase reload preserves old snapshots");
    for(int band=0;band<=3;++band) {
        bool found=false;
        for(uint64_t seed=0;seed<80&&!found;++seed) {
            ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room) {
                int count=0;for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(18))++count;
                check(count<=3,"natural room caps Attack Flies at three");
                if(count&&!found){found=true;std::cout<<"NATURAL_ATTACK_FLY seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<band<<'\n';}
            }
        }
        check(found,"Attack Fly reachable in every intended stage band");
    }
    std::cout<<"PASS Attack Fly native pursuit/asymmetry, health, contact, item morph, real live/death Hive routes, capacity, configuration and stage placement\n";
}
void contentAndPlacement() {
    Content config;for(const auto &bad:{"buzz_fly 13.0.0 0 5 .7 .6 .4 .6 .06 3 24","buzz_fly 13.0.0 .1 0 .7 .6 .4 .6 .06 3 24"}) {
        bool rejected=false;try{config.load(replace(config.original,"buzz_fly 13.0.0 .1 5 .7 .6 .4 .6 .06 3 24",bad));}catch(...){rejected=true;}
        check(rejected,"invalid buzzing configuration rejected");
    }
    const auto old=config.load(config.original);const auto next=config.load(replace(config.original,"dung_morph 13.0.0 14.0.0 1000","dung_morph 13.0.0 14.0.0 500"));
    check(old->buzzFly(monsterId(13))->morphChance==1000&&next->buzzFly(monsterId(13))->morphChance==500&&old->fingerprint()!=next->fingerprint(),"external snapshots stay immutable");
    bool fly=false,pooter=false,coexist=false;
    for(uint64_t seed=0;seed<40&&!(fly&&pooter&&coexist);++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room)) {
            if(e.monster==monsterId(14)&&!pooter){pooter=true;std::cout<<"NATURAL_POOTER seed="<<seed<<" floor=0 room="<<room<<'\n';}
            if(e.monster==monsterId(13)) {
                if(!fly){fly=true;std::cout<<"NATURAL_FLY seed="<<seed<<" floor=0 room="<<room<<'\n';}
                for(const auto &prop:s.arena.breakables)if(prop.room==room&&prop.kind==BreakableKind::Dung&&!coexist) {
                    coexist=true;std::cout<<"NATURAL_FLY_DUNG seed="<<seed<<" floor=0 room="<<room<<'\n';
                }
            }
        }
        for(const auto &p:s.arena.breakables)if(p.kind==BreakableKind::Dung) {
            check(s.arena.rooms[size_t(p.room)].kind==RoomKind::Combat&&s.arena.rooms[size_t(p.room)].story==StoryRoom::None,"dung stays in ordinary combat rooms");
            check(std::abs(s.arena.canyon->height(p.rewardPosition.x,p.rewardPosition.z))<.04f,"dung stays off slopes");
        }
    }
    check(fly&&pooter&&coexist,"seeded regular actors and real dung coexist");
    Simulation cache(24,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
    for(const auto &p:cache.arena.breakables)if(p.kind==BreakableKind::Dung)
        check(!sphereBox(cache.arena.supplyCache.approach,1.5f,p.bounds),"seed24 cache approach excludes dung cover");
    for(bool tutorial:{false,true}) {
        Simulation s(1,1,{},tutorial?MissionTheme::Canyon:MissionTheme::Mine,true,tutorial);
        check(std::none_of(s.arena.breakables.begin(),s.arena.breakables.end(),[](const auto &p){return p.kind==BreakableKind::Dung;}),"Mine and tutorial unchanged by dung dressing");
    }
}
}
int main(){try{motion();shooter();superPooter();attackFly();transformationAndDung();contentAndPlacement();std::cout<<"PASS Fly/Pooter buzz, source shot timing, dung damage/morph, collision, health and seeded placement\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
