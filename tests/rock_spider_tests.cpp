#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *s){if(!b)throw std::runtime_error(s);}
bool near(float a,float b,float eps=.01f){return std::abs(a-b)<eps;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,60};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int variant=0,int subtype=1){return s.spawnMonster(monsterId(818,variant,subtype),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical,bool blast=false,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;e.explosionDamage=blast;
    e.execution=e.debugExecution=debug;s.queueRoot(e);s.drainEvents();
}
void wake(Simulation &s,EntityId id) {
    for(int n=0;n<600&&s.findEnemy(id)->rockSpider->phase==RockSpiderPhase::Rock;++n)tick(s);
    check(s.findEnemy(id)->rockSpider->phase==RockSpiderPhase::Appearing,"rock wakes through appear phase");
}
void motion() {
    for(int v:{0,2}) {
        auto s=fixture();auto id=spawn(s,v);auto &e=*s.findEnemy(id);wake(s,id);
        check(e.rockSpider->frame==0&&length(e.velocity)<.001f,"stationary wake starts frame zero");
        tick(s,19);check(e.rockSpider->phase==RockSpiderPhase::Appearing,"20-frame reveal does not end early");
        tick(s);check(e.rockSpider->phase==RockSpiderPhase::Skitter&&e.rockSpider->counter==0,"20-frame reveal then new counter");
        auto &r=*e.rockSpider;r.counter=v==0?11:10;r.heading={};e.velocity={};s.combatRng=Random(4);
        tick(s);
        check(r.selections==1&&near(length(e.velocity),v==0?5.4f:9.72f),"first skitter source force3 or5.4 times.6 times3");
        const auto heading=r.heading;s.player.position={-60,.85f,-60};tick(s,2);
        check(distance(r.heading,heading)<.0001f,"heading remains committed between12-count selections");
        r.counter=46;r.heading={1,0,0};e.velocity={};tick(s,2);
        check(r.cycles==1&&length(r.heading)<.0001f&&length(e.velocity)>0,"last impulse precedes cycle reset");
    }
    auto a=fixture(),b=fixture();const auto ia=spawn(a),ib=spawn(b);
    tick(a,120);tick(b,480,1.f/120);
    check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.03f,"30/120Hz open-floor trajectory agreement");
    check(a.findEnemy(ia)->rockSpider->selections==b.findEnemy(ib)->rockSpider->selections,"source-frame selection cadence");
    bool chase=false,wander=false;
    for(int seed=0;seed<30&&!(chase&&wander);++seed) {
        auto s=fixture();s.combatRng=Random(seed);auto id=spawn(s);wake(s,id);tick(s,20);
        for(int n=0;n<120;++n){auto before=s.findEnemy(id)->rockSpider->selections;tick(s);const auto &r=*s.findEnemy(id)->rockSpider;
            if(r.selections>before){chase|=r.pursuing;wander|=!r.pursuing;}}
    }
    check(chase&&wander,"ordinary chase and wander branches reached");
    std::cout<<"MOTION reveal20=1 native_force=1 committed_heading=1 cycle48=1 partition=1 chase_wander=1\n";
}
void deaths() {
    for(int sub=0;sub<=3;++sub) {
        auto s=fixture();auto id=spawn(s,0,sub);const auto actual=s.findEnemy(id)->monster;
        check(actual.subtype>=1&&actual.subtype<=3&&(sub==0||actual.subtype==sub),"default subtype resolves and explicit subtype survives");
        s.limits.enemies=0;s.debugScenario=false;damage(s,id,10000);
        auto *e=s.findEnemy(id);check(e&&e->alive&&e->monster==monsterId(85)&&near(e->hp,20.8f),"even extreme overkill morphs same slot into full-health85");
        check(s.stats.kills==0&&s.moneyPickups.empty()&&s.roomThreats()==1,"outer shell is not independent kill/loot/room clear");
        tick(s);check(!s.roomClear,"inner spider keeps room sealed at capacity zero");
        damage(s,id,100);tick(s);check(s.roomClear&&s.stats.kills==1,"inner spider death alone pays kill and completes");
    }
    auto fire=fixture();auto id=spawn(fire);wake(fire,id);tick(fire,35);
    const auto before=*fire.findEnemy(id)->rockSpider;const auto velocity=fire.findEnemy(id)->velocity;
    damage(fire,id,1000,DamageKind::Flame);auto *e=fire.findEnemy(id);
    check(e->monster==monsterId(818,2,1)&&near(e->hp,48)&&e->rockSpider->counter==before.counter&&distance(e->velocity,velocity)<.001f,"flame transforms without damage or movement restart");
    damage(fire,id,1,DamageKind::Burning);check(near(fire.findEnemy(id)->hp,47),"burning is separate from flame immunity");
    auto debug=fixture();id=spawn(debug);damage(debug,id,1000,DamageKind::Physical,false,true);tick(debug);check(debug.livingEnemies()==0,"debug kill suppresses shell morph");
    std::cout<<"DEATH four_subtypes=1 same_entity=1 no_extra_reward=1 overkill=1 fire_morph=1 burning=1 debug=1\n";
}
void coal() {
    auto s=fixture();auto id=spawn(s,2,3);s.spawnMonster(monsterId(27),{60,.85f,-60});
    s.limits.enemies=1;damage(s,id,1000);tick(s,2);check(s.livingEnemies()==1,"coal birth retained under capacity");
    s.limits.enemies=2;tick(s);Enemy *ember=nullptr;for(auto &e:s.enemies)if(e.monster==monsterId(33,11,3))ember=&e;
    check(ember&&ember->environment&&ember->rockSpider&&near(ember->hp,15)&&ember->rockSpider->height<0,"real matching-subtype bouncing coal");
    const auto coalId=ember->id;check(s.roomThreats()==1&&s.stats.kills==1,"hot coal excluded from required threats and ordinary kill count");
    tick(s,30);ember=s.findEnemy(coalId);check(ember&&ember->alive&&ember->rockSpider->phase==RockSpiderPhase::Rock,"coal never becomes skittering spider");
    const auto hp=ember->hp;damage(s,coalId,24);ember=s.findEnemy(coalId);check(ember&&ember->hp>=hp-2&&ember->hp<=hp-1,"small shot causes one or two native HP wear");
    const auto next=ember->hp;damage(s,coalId,40);ember=s.findEnemy(coalId);check(ember->hp>=next-3&&ember->hp<=next-2,"large shot causes two or three native HP wear");
    const auto unburnt=ember->hp;damage(s,coalId,1000,DamageKind::Flame);
    check(s.findEnemy(coalId)->hp>=unburnt-3&&s.findEnemy(coalId)->hp<=unburnt-2,"hot coal applies bounded manual wear before native flame damage cancellation");
    damage(s,coalId,1,DamageKind::Physical,true);check(!s.findEnemy(coalId)->alive&&s.stats.kills==1,"explosion extinguishes without ordinary kill");
    auto timed=fixture();id=spawn(timed,2);timed.spawnMonster(monsterId(27),{60,.85f,-60});damage(timed,id,1000);tick(timed);
    EntityId heat=0;for(const auto &e:timed.enemies)if(e.environment)heat=e.id;check(heat!=0,"decay fixture coal exists");
    for(int n=0;n<3000&&timed.findEnemy(heat)&&timed.findEnemy(heat)->alive;++n)tick(timed);
    check(!timed.findEnemy(heat)||!timed.findEnemy(heat)->alive,"coal decays without shots");
    auto wet=fixture();wet.arena.rooms[0].flooded=true;id=spawn(wet,2);wet.spawnMonster(monsterId(27),{60,.85f,-60});damage(wet,id,1000);tick(wet);
    EntityId wetCoal=0;for(const auto &e:wet.enemies)if(e.environment)wetCoal=e.id;tick(wet,100);
    check(!wet.findEnemy(wetCoal)||!wet.findEnemy(wetCoal)->alive,"flooded room adds five-frame water wear");
    auto clear=fixture();id=spawn(clear,2);clear.debugScenario=false;damage(clear,id,1000);tick(clear,4);check(clear.roomClear&&clear.livingEnemies()==0,"last hostile coal death does not lock cleared room");
    std::cout<<"COAL retained_birth=1 matching_shape=1 bounce=1 per_hit_wear=1 explosive=1 flame=1 timed_decay=1 clear=1\n";
}
void collision() {
    auto s=fixture();s.arena.obstacles.push_back({{-25,0,2},{25,8,3}});s.arena.rebuildWalls();s.player.position={0,.85f,10};auto id=spawn(s);
    for(int n=0;n<200;++n){tick(s);const auto &e=*s.findEnemy(id);check(!s.arena.blocked(e.position,e.radius),"skitter collision never enters solid obstacle");}
    auto contact=fixture();contact.godMode=false;id=contact.spawnMonster(monsterId(818,0,1),contact.player.position);tick(contact);
    check(near(contact.player.hp,StartingHealth-10*EnemyDamageMultiplier),"disguised rock still has contact damage");
    for(float height:{-60.f,-20.f}) {
        auto air=fixture();id=spawn(air);auto &e=*air.findEnemy(id);
        e.rockSpider->initialized=true;e.rockSpider->height=height;e.lift=-height*.1f;
        Event shot;shot.position={-1,.85f+e.lift,0};shot.direction={1,0,0};shot.speed=120;shot.damage=1;
        air.queueRoot(shot);air.drainEvents();tick(air);
        check(height<-50?near(air.findEnemy(id)->hp,38.4f):air.findEnemy(id)->hp<38.4f,
            "real projectile respects high intangible and lower rendered-height hull");
    }
    std::cout<<"COLLISION walls=1 contact=1 height_classes=1\n";
}
void config() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-rock-spider-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream file(dir/"rock_spiders.mechanics");const std::string original(std::istreambuf_iterator<char>(file),{});
    auto edit=[&](std::string from,std::string to){auto s=original;const auto pos=s.find(from);check(pos!=s.npos,"config fixture exists");s.replace(pos,from.size(),to);std::ofstream(dir/"rock_spiders.mechanics")<<s;return MechanicsLibrary::load(dir);};
    auto changed=edit(".1 .6 3 1 12 48",".1 .6 4 1 12 48");check(changed->rockSpider(monsterId(818))->force==4&&defaultMechanics()->rockSpider(monsterId(818))->force==3,"immutable external profile snapshot");
    for(auto invalid:std::vector<std::pair<std::string,std::string>>{{".1 .6 3 1 12 48",".1 1 3 1 12 48"},{"1 12 48 6","1 12 47 6"},{".6 -4 -50",".6 -4 -1"},{"85.0.0 none","94.0.0 33.11.0"},{"none 33.11.0","none 85.0.0"}}) {
        bool failed=false;try{edit(invalid.first,invalid.second);}catch(const std::exception&){failed=true;}check(failed,"invalid profile rejected");
    }
    std::cout<<"CONFIG immutable=1 rejects_invalid=5\n";
}
void placement() {
    std::set<MonsterId> found;
    for(uint64_t seed=0;seed<64&&found.size()<6;++seed)for(int floor=0;floor<ExpeditionPlan(seed).floorCount;++floor) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==818) {
            check(e.monster.variant==0||e.monster.variant==2,"only reviewed variants enter pool");
            check(s.arena.profile.band<=1&&(e.monster.variant==2||s.arena.profile.band==1),"source stage placement");
            check(e.rockSpider&&e.monster.subtype>=1&&e.monster.subtype<=3&&!s.arena.blocked(e.position,e.radius),"natural legal concrete-subtype body");
            if(found.insert(e.monster).second)std::cout<<"NATURAL_ROCK "<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
        }
    }
    check(found.size()==6,"all six explicit ordinary subtypes found in actual seeded rooms");
}
}
int main(){std::cout<<std::unitbuf;try{motion();deaths();coal();collision();config();placement();std::cout<<"PASS Rock Spider and Coal Spider\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
