#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *s){if(!b)throw std::runtime_error(s);}
bool near(float a,float b,float tolerance=.015f){return std::abs(a-b)<tolerance;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,0};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int variant=0,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(827,variant),at);}
void arm(Enemy &e){auto &r=*e.faceless;r.initialized=true;r.frame=0;r.fired=false;r.clock=0;r.frameReady=false;e.velocity={};}
void hit(Simulation &s,EntityId id,float amount,bool execution=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=e.debugExecution=execution;
    s.queueRoot(e);s.drainEvents();
}
unsigned morphSeed(bool pacer=false) {
    for(unsigned seed=0;seed<1000;++seed){Random r(seed);if(r.bounded(2)==0&&(r.bounded(3)==0)==pacer)return seed;}
    throw std::runtime_error("no morph fixture seed");
}
void aggression() {
    auto s=fixture();auto id=spawn(s);tick(s,20);auto *e=s.findEnemy(id);
    check(near(e->maxHp,64)&&!e->faceless->aggressive&&planarDistance(e->position,{0,.85f,0})>.1f,"healthy distant Faceless wanders passively");
    s.player.position=add(e->position,{7.5f,0,0});tick(s);check(e->faceless->aggressive,"near player latches aggression");
    s.player.position={65,.85f,0};tick(s);check(e->faceless->aggressive,"distance never resets aggression");
    auto q=fixture();auto hurt=spawn(q),neighbor=spawn(q,1,{7,.85f,0}),far=spawn(q,0,{-20,.85f,0});
    tick(q);hit(q,hurt,3.2f);tick(q);
    check(q.findEnemy(hurt)->faceless->aggressive&&q.findEnemy(neighbor)->faceless->aggressive&&!q.findEnemy(far)->faceless->aggressive,"damage spreads aggression to a nearby variant, not distant peers");
    check(near(q.findEnemy(hurt)->faceless->recentDamage,.89f),"recent damage uses native HP and source epilogue decay");
    auto cover=fixture();auto actor=spawn(cover);cover.player.position={7,.85f,0};
    cover.arena.floorProps.push_back({StoryPropKind::Crate,{{2,-.1f,-4},{4,3,4}}});cover.arena.rebuildWalls();
    check(!cover.arena.sight(cover.findEnemy(actor)->position,cover.player.position),"cover fixture blocks sight");
    tick(cover,2);check(cover.findEnemy(actor)->faceless->aggressive,"aggression has no invented LOS gate");
    std::cout<<"AGGRESSION passive=1 proximity=1 damage=1 propagation=1 latch=1 through_cover=1\n";
}
void shots() {
    auto hurt=fixture();auto hurtId=spawn(hurt);auto *hurtBody=hurt.findEnemy(hurtId);
    hurtBody->faceless->initialized=true;hurtBody->faceless->recentDamage=400;
    tick(hurt);check(hurt.findEnemy(hurtId)->faceless->frame==0,"high recent damage raises ordinary attack chance even with a distant target");
    auto cost=fixture();auto costId=spawn(cost);arm(*cost.findEnemy(costId));
    cost.findEnemy(costId)->faceless->recentDamage=10;cost.limits.projectiles=0;tick(cost,9);
    check(near(cost.findEnemy(costId)->faceless->recentDamage,10-7-.11f*9),"Shoot subtracts seven native damage units in addition to per-frame decay");
    for(int variant:{0,1}) {
        auto s=fixture();auto id=spawn(s,variant);const auto &p=*s.content->faceless(monsterId(827,variant));
        arm(*s.findEnemy(id));s.limits.projectiles=0;
        tick(s,p.shootFrame-1);check(s.findEnemy(id)->faceless->attacks==0,"no shot before source Shoot event");
        const auto before=s.findEnemy(id)->position;s.player.position={-50,.85f,-25};tick(s);
        const auto &r=*s.findEnemy(id)->faceless;
        check(r.attacks==1&&r.pendingShots.size()==6,"Shoot event retains six exact projectiles");
        for(int n=0;n<6;++n) {
            const auto &shot=r.pendingShots[size_t(n)];const auto velocity=mul(shot.direction,shot.speed);
            const float angle=float(n+1)*Pi/3;
            check(near(velocity.x,std::cos(angle)*p.shotSpeed)&&near(velocity.z,std::sin(angle)*p.shotSpeed)&&near(velocity.y,4.5f),"ring uses fixed preincremented directions independent of target");
            check(near(shot.projectileGravity,variant?1.8f:4.5f)&&near(shot.projectileRadius,variant?.286f:.22f)&&shot.context.sourceEntity==id,"variant projectile gravity, size and attribution");
        }
        tick(s,30);check(s.findEnemy(id)->faceless->attacks==1&&planarDistance(s.findEnemy(id)->position,before)<.001f,"backpressure retains one volley and pauses only its producer");
        s.limits.projectiles=64;tick(s);check(s.stats.projectiles==6&&s.findEnemy(id)->faceless->pendingShots.empty(),"capacity admits exact volley once");
    }
    auto t=fixture();auto id=spawn(t,1);t.player.position={7,.85f,0};tick(t,2);const auto origin=t.findEnemy(id)->position;
    check(t.findEnemy(id)->faceless->frame==0,"aggressive Tainted starts its first attack immediately");
    tick(t,11);check(t.findEnemy(id)->faceless->attacks==0&&planarDistance(origin,t.findEnemy(id)->position)>.1f,"Tainted moves during windup without early shot");
    tick(t);check(t.findEnemy(id)->faceless->attacks==1,"Tainted Shoot12");
    tick(t,19);check(t.findEnemy(id)->faceless->attacks==2,"Tainted repeats at19-frame animation cadence");
    std::cout<<"SHOTS frames9_12=1 fixed_ring6=1 tainted_gravity=1 retained=1 movement_during_attack=1 cadence19=1 damage_chance_cost=1\n";
}
void mortality() {
    const auto base=fixture();int replaced=0,gushers=0,pacers=0;
    for(unsigned seed=0;seed<450;++seed) {
        auto s=base;const auto id=spawn(s);s.limits.enemies=1;s.combatRng=Random(seed);
        auto *e=s.findEnemy(id);e->summoner=12345;e->spawnerType=906;e->velocity={1,0,2};
        const auto position=e->position;hit(s,id,64);
        e=s.findEnemy(id);
        if(e->alive) {
            ++replaced;gushers+=e->monster==monsterId(11);pacers+=e->monster==monsterId(11,1);
            check(e->monster.type==11&&e->id==id&&s.enemies.size()==1&&e->summoner==12345&&e->spawnerType==906,"death morph keeps entity slot and original ownership");
            check(near(e->hp,e->maxHp)&&distance(position,e->position)==0&&near(e->velocity.x,1)&&near(e->velocity.z,2),"replacement starts at full child HP with position and momentum preserved");
            check(s.stats.kills==0&&s.moneyPickups.empty()&&!s.roomClear,"replacement never pays kill loot or clears the room");
        } else check(s.stats.kills==1,"failed death roll produces one normal kill");
    }
    check(replaced>185&&replaced<265&&gushers>110&&gushers<195&&pacers>45&&pacers<105,"death rolls match50percent with2to1 conditional offspring over450 deterministic seeds");
    for(bool pacer:{false,true}) {
        auto above=base;auto a=spawn(above);above.combatRng=Random(morphSeed(pacer));hit(above,a,64+80-.01f);
        check(above.findEnemy(a)->alive&&above.findEnemy(a)->monster==monsterId(11,pacer?1:0),"strict overkill boundary allows just-above threshold and both real replacements");
        auto exact=base;auto b=spawn(exact);exact.combatRng=Random(morphSeed(pacer));hit(exact,b,64+80);
        check(!exact.findEnemy(b)->alive,"exact-25nativeHP overkill prevents replacement");
        auto tainted=base;auto c=spawn(tainted,1);tainted.combatRng=Random(morphSeed(pacer));
        // Isolate the death rule from the armor batch, tested separately below.
        tainted.findEnemy(c)->adaptiveArmor.reset();hit(tainted,c,320);
        check(!tainted.findEnemy(c)->alive,"Tainted never transforms");
        auto cheat=base;auto d=spawn(cheat);cheat.combatRng=Random(morphSeed(pacer));hit(cheat,d,64,true);
        check(!cheat.findEnemy(d)->alive,"debug execution bypasses transformation");
    }
    for(bool morph:{false,true}) {
        auto s=base;auto id=spawn(s);s.limits.projectiles=0;arm(*s.findEnemy(id));tick(s,9);
        s.combatRng=Random(morphSeed());hit(s,id,morph?64:10000);s.debugScenario=false;tick(s);
        check(!s.roomClear&&s.findEnemy(id)&&s.findEnemy(id)->faceless->pendingShots.size()==6,"pending volley survives both real death and morph");
        s.limits.projectiles=64;tick(s);
        check(s.stats.projectiles==6&&s.stats.kills==unsigned(morph?0:1),"postmortem or morphed owner releases selected volley exactly once");
    }
    std::cout<<"MORTALITY trials450="<<replaced<<" gusher="<<gushers<<" pacer="<<pacers<<" strict_overkill=1 same_entity=1 retained_payload=1\n";
}
void partitionAndSpawner() {
    for(bool aggressive:{false,true}) {
        auto a=fixture(),b=fixture();auto ia=spawn(a),ib=spawn(b);
        a.findEnemy(ia)->faceless->aggressive=b.findEnemy(ib)->faceless->aggressive=aggressive;
        tick(a,60);tick(b,240,1.f/120);
        check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.05f,"30/120Hz movement agrees");
        check(a.findEnemy(ia)->faceless->attacks==b.findEnemy(ib)->faceless->attacks,"30/120Hz source attacks agree");
    }
    for(int type:{820,827}) {
        auto s=fixture();auto id=s.spawnMonster(monsterId(type),{0,.85f,0});auto *e=s.findEnemy(id);
        e->spawnerType=906;e->summoner=99999;s.player.position={6,.85f,0};tick(s,1200);
        check(type==820?e->danny->attacks==0:e->faceless->attacks==0,"original Hornfel attribution suppresses attacks after parent/carrier loss");
    }
    auto s=fixture();auto id=spawn(s,1);hit(s,id,24);check(s.findEnemy(id)->adaptiveArmor->pending.size()==1,"Tainted uses actual shared adaptive armor");
    tick(s,2);check(s.findEnemy(id)->hp>296&&s.findEnemy(id)->hp<320&&s.findEnemy(id)->faceless->aggressive,"resolved armor damage activates aggression after initialization");
    std::cout<<"PARTITION passive_active=1 source_cadence=1 spawner_lifetime=1 adaptive_armor=1\n";
}
void config() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-faceless-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"faceless.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(dir/"faceless.mechanics")<<text;return MechanicsLibrary::load(dir);};
    auto changed=edit("19 9 25","19 8 25");check(changed->faceless(monsterId(827))->shootFrame==8&&defaultMechanics()->faceless(monsterId(827))->shootFrame==9,"hot reload produces immutable separate snapshots");
    for(const auto &p:std::vector<std::pair<std::string,std::string>>{{"faceless_shot 827.0.0","#faceless_shot 827.0.0"},{"19 9 25","19 19 25"},{"11.0.0 11.1.0","827.0.0 11.1.0"},{"6 24 1.15 4.5 1.8","6 24 1.15 4.5 -1"},{"Wander None Walker 64 3 .6","Wander None Walker 64 3 .5"}}) {
        bool rejected=false;try{edit(p.first,p.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid Faceless contract rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 rejected_contracts=5\n";
}
void natural() {
    bool found[2]{};
    for(int band:{1,3})for(int seed=0;seed<128&&!found[band==3];++seed) {
        ExpeditionPlan plan(uint64_t(seed),false,WitnessAccount::Rourke);
        int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
        Simulation s(uint64_t(seed),1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=0;room<s.arena.roomCount();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==827) {
            check(e.faceless&&!s.arena.blocked(e.position,e.radius),"natural resident has dedicated controller and clear actual footprint");
            check(!e.monster.variant||s.arena.profile.band==3,"Tainted never appears in early bands");
            if(!found[e.monster.variant]){found[e.monster.variant]=true;std::cout<<"NATURAL_FACELESS variant="<<e.monster.variant<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';}
        }
    }
    check(found[0]&&found[1],"both actual seeded Faceless populations reachable");
}
}
int main(int argc,char**argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--natural"){natural();return 0;}aggression();shots();mortality();partitionAndSpawner();config();std::cout<<"PASS Faceless family\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
