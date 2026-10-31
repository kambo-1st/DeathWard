#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *message){if(!b)throw std::runtime_error(message);}
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
EntityId spawn(Simulation &s,int variant=0){return s.spawnMonster(monsterId(11,variant),{0,.85f,0});}
void arm(Enemy &e,int cooldown=0,Vector3 velocity={3,0,0}) {
    auto &r=*e.headless;r.initialized=true;r.cooldown=cooldown;r.targetReady=true;r.destination={40,.85f,0};
    r.clock=0;r.frameReady=false;r.blocked=false;e.velocity=velocity;
}
void hit(Simulation &s,EntityId id,float damage) {Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;s.queueRoot(e);s.drainEvents();}
void movement() {
    auto a=fixture(),b=fixture();const auto ia=spawn(a,1),ib=spawn(b,1);
    b.player.position={-60,.85f,-40};tick(a,60);tick(b,60);
    check(near(a.findEnemy(ia)->hp,32)&&near(b.findEnemy(ib)->hp,32),"Pacer health is10native x3.2");
    check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.001f,"ordinary wandering does not acquire the player");
    check(planarDistance(a.findEnemy(ia)->position,{0,.85f,0})>.1f&&a.stats.projectiles==0,"Pacer moves without ranged attacks");
    auto exact=fixture();auto id=spawn(exact,1);arm(*exact.findEnemy(id));tick(exact);
    check(near(exact.findEnemy(id)->velocity.x,3.75f,.001f)&&near(exact.findEnemy(id)->velocity.z,0,.001f),"retention precedes impulse: native1*.75+.5, worldx3");
    auto cover=fixture();auto c=spawn(cover,1);arm(*cover.findEnemy(c),0,{6,0,0});
    cover.arena.floorProps.push_back({StoryPropKind::Crate,{{2,-.1f,-4},{4,3,4}}});cover.arena.rebuildWalls();
    for(int n=0;n<120;++n){tick(cover);check(!cover.arena.blocked(cover.findEnemy(c)->position,cover.findEnemy(c)->radius),"wander respects actual collision footprint");}
    std::cout<<"MOVEMENT no_target=1 retention_before_impulse=1 grounded_cover=1 pacer_no_shots=1\n";
}
void cadenceAndAim() {
    const auto base=fixture();int low=1000,high=0;
    for(unsigned seed=0;seed<80;++seed) {
        auto s=base;auto id=spawn(s);s.combatRng=Random(seed);tick(s);
        auto &r=*s.findEnemy(id)->headless;low=std::min(low,r.cooldown);high=std::max(high,r.cooldown);
        check(r.cooldown>=20&&r.cooldown<=39&&r.shots==0,"initial delay is integral20..39 with no initialization shot");
    }
    check(low==20&&high==39,"deterministic seed sample reaches both initial endpoints");
    auto s=base;auto id=spawn(s);arm(*s.findEnemy(id),3);s.limits.projectiles=0;tick(s,3);
    check(s.findEnemy(id)->headless->shots==0&&s.findEnemy(id)->headless->cooldown==0,"countdown reaching zero does not fire in the decrement branch");
    tick(s);const auto &r=*s.findEnemy(id)->headless;
    check(r.shots==1&&!r.pendingShots.empty()&&r.cooldown>=40&&r.cooldown<=59,"next tick emits and resets40..59");
    const auto &shot=r.pendingShots.front();const auto velocity=mul(shot.direction,shot.speed);
    check(near(velocity.x,15)&&near(velocity.y,12)&&near(velocity.z,0),"source mode0 moves along current velocity with correct launch speed");
    check(near(shot.position.y,1.15f)&&near(shot.projectileGravity,22.5f)&&near(shot.projectileFlightRetention,.9f)&&near(shot.projectileRadius,.22f)&&near(shot.damage,10)&&shot.context.sourceEntity==id,"lob physics includes common base acceleration, damage and source attribution");
    auto zero=base;auto z=spawn(zero);arm(*zero.findEnemy(z),0,{});zero.findEnemy(z)->facing={0,0,-1};tick(zero);
    check(zero.stats.projectiles==0&&zero.findEnemy(z)->headless->cooldown==0,"stationary due Gusher neither invents aim nor spends cooldown");
    zero.limits.projectiles=0;tick(zero);const auto &zs=zero.findEnemy(z)->headless->pendingShots.front();
    check(near(mul(zs.direction,zs.speed).x,15)&&near(mul(zs.direction,zs.speed).z,0),"movement resumes firing independently of old facing");
    auto tiny=base;auto t=spawn(tiny);arm(*tiny.findEnemy(t),0,{.00003f,0,0});tiny.limits.projectiles=0;tick(tiny);
    check(!tiny.findEnemy(t)->headless->pendingShots.empty(),"nonzero tiny movement still permits a due shot");
    const auto &ts=tiny.findEnemy(t)->headless->pendingShots.front();
    check(near(mul(ts.direction,ts.speed).x,15)&&near(mul(ts.direction,ts.speed).z,0),"tiny nonzero movement keeps its own shot direction instead of a generic normalization fallback");
    auto occluded=base;auto o=spawn(occluded);arm(*occluded.findEnemy(o),0,{0,0,3});occluded.limits.projectiles=0;
    occluded.arena.floorProps.push_back({StoryPropKind::Crate,{{2,-.1f,-4},{4,3,4}}});occluded.arena.rebuildWalls();
    check(!occluded.arena.sight(occluded.findEnemy(o)->position,occluded.player.position),"occlusion fixture blocks player sight");tick(occluded);
    check(!occluded.findEnemy(o)->headless->pendingShots.empty(),"no invented firing distance or LOS gate");
    std::cout<<"SHOTS initial20_39=1 reload40_59=1 decrement_branch=1 velocity_aim=1 zero_aim=1 lob_physics=1 no_los_gate=1\n";
}
void capacityAndMortality() {
    auto s=fixture();auto id=spawn(s);arm(*s.findEnemy(id));s.limits.projectiles=0;tick(s);
    const auto retained=s.findEnemy(id)->headless->pendingShots.front();const auto where=s.findEnemy(id)->position;
    tick(s,60);check(s.findEnemy(id)->headless->shots==1&&distance(where,s.findEnemy(id)->position)<.001f,"saturation retains one selected shot and freezes its producer");
    hit(s,id,32);check(!s.findEnemy(id)->alive&&s.stats.kills==1,"headless true death pays one kill");
    s.debugScenario=false;tick(s);check(!s.roomClear&&s.findEnemy(id)&&!s.findEnemy(id)->headless->pendingShots.empty(),"postmortem selected shot keeps room unresolved");
    s.limits.projectiles=64;tick(s);check(s.stats.projectiles==1,"pending postmortem shot admitted exactly once");
    auto bullet=std::find_if(s.projectiles.begin(),s.projectiles.end(),[&](const auto &p){return p.context.sourceEntity==id;});
    check(bullet!=s.projectiles.end()&&near(bullet->damage,retained.damage)&&near(bullet->gravity,retained.projectileGravity),"retained shot preserves payload and dead-owner attribution");
    tick(s,240);check(s.roomClear&&s.stats.projectiles==1,"room completes after real projectile expires, without a duplicate");
    bool seen[2]{};
    for(unsigned seed=0;seed<30&&(!seen[0]||!seen[1]);++seed) {
        auto q=fixture();const auto parent=q.spawnMonster(monsterId(10,1),{0,.85f,0});q.combatRng=Random(seed);
        hit(q,parent,q.findEnemy(parent)->hp);tick(q);
        for(const auto &e:q.enemies)if(e.alive&&e.monster.type==11){seen[e.monster.variant]=true;check(e.headless&&e.hp==32&&e.id==parent&&q.stats.kills==0,"Gaper morph keeps same entity, new controller and source-based child HP without a kill reward");}
    }
    check(seen[0]&&seen[1],"both real headless offspring observed");
    for(int variant:{0,1}) {
        auto q=fixture();const auto id=q.spawnMonster(monsterId(827),{0,.85f,0});
        for(unsigned seed=0;;++seed){Random rng(seed);if(rng.bounded(2)==0&&(rng.bounded(3)==0)==bool(variant)){q.combatRng=Random(seed);break;}}
        auto *e=q.findEnemy(id);e->summoner=777;e->spawnerType=827;e->velocity={3,0,0};hit(q,id,64);
        check(e->alive&&e->monster==monsterId(11,variant)&&e->headless&&e->hp==32&&e->id==id&&e->summoner==777&&e->spawnerType==827&&q.stats.kills==0,"Faceless same-entity morph initializes actual new controller without reward");
        tick(q,2);check(q.findEnemy(id)->headless->initialized,"morphed headless body advances independently");
    }
    std::cout<<"MORTALITY retained_payload=1 no_early_clear=1 gaper_offspring=2 faceless_morphs=2\n";
}
void partitionAndReload() {
    for(int variant:{0,1}) {
        auto a=fixture(),b=fixture();auto ia=spawn(a,variant),ib=spawn(b,variant);tick(a,90);tick(b,360,1.f/120);
        check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.05f&&a.findEnemy(ia)->headless->shots==b.findEnemy(ib)->headless->shots,"30/120Hz wandering and cadence agree");
    }
    const auto dir=std::filesystem::temp_directory_path()/("dw-headless-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"headless.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;auto at=text.find(from);check(at!=text.npos,"reload fixture exists");text.replace(at,from.size(),to);std::ofstream(dir/"headless.mechanics")<<text;return MechanicsLibrary::load(dir);};
    const auto changed=edit("10 20 39 40 59","10 12 12 40 59");check(changed->headless(monsterId(11))->initialMin==12&&defaultMechanics()->headless(monsterId(11))->initialMin==20,"immutable external reload");
    auto q=fixture(changed);auto id=spawn(q);tick(q);check(q.findEnemy(id)->headless->cooldown==12,"runtime consumes reloaded initial cadence");
    for(const auto &bad:std::vector<std::pair<std::string,std::string>>{{"headless_shot 11.0.0","#headless_shot 11.0.0"},{".5 .75 40",".5 1 40"},{"10 20 39 40 59","10 40 39 40 59"},{"15 1.15 12 22.5","15 1.15 12 -1"},{"Wander None Headless 32","Wander None Walker 32"},{"headless 11.1.0 0","headless 11.1.0 1"}}) {
        bool rejected=false;try{edit(bad.first,bad.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid headless contract rejected");
    }
    std::cout<<"PARTITION source30Hz=1 immutable_reload=1 runtime_reload=1 rejected_contracts=6\n";
}
void sourceFlight() {
    float height=-23,falling=-8;
    for(int n=0;n<20;++n){falling=.9f*falling+.1f+.1f+.3f;height+=falling;}
    for(int hz:{30,60,120}) {
        auto s=fixture();const auto id=spawn(s);arm(*s.findEnemy(id));s.limits.projectiles=0;tick(s);
        const auto shot=s.findEnemy(id)->headless->pendingShots.front();
        s.enemies.clear();s.limits.projectiles=512;s.queueRoot(shot);s.drainEvents();
        for(int n=0;n<hz*2/3;++n)tick(s,1,1.f/hz);
        check(s.projectiles.size()==1&&near(s.projectiles[0].position.y,-height*.05f,.002f)&&
              near(s.projectiles[0].velocity.y,-falling*1.5f,.002f),
              "Gusher actual projectile matches native mode0, modifier and common base at30/60/120Hz");
    }
    std::cout<<"FLIGHT independent_native_recurrence=20 partitions30_60_120=1 common_base_acceleration=1\n";
}
void natural() {
    bool found[2]{};
    for(unsigned seed=0;seed<64&&(!found[0]||!found[1]);++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==11) {
            check(e.headless&&!s.arena.blocked(e.position,e.radius),"natural headless resident has controller and legal footprint");
            if(!found[e.monster.variant]){found[e.monster.variant]=true;std::cout<<"NATURAL_HEADLESS variant="<<e.monster.variant<<" seed="<<seed<<" floor=0 room="<<room<<'\n';}
        }
    }
    check(found[0]&&found[1],"both natural headless bodies found");
}
}
int main(int argc,char**argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--natural"){natural();return 0;}movement();cadenceAndAim();capacityAndMortality();partitionAndReload();sourceFlight();std::cout<<"PASS Headless family\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
