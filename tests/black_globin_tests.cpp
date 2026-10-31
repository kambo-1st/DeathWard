#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.006f){return std::abs(a-b)<eps;}
Simulation fixture(uint32_t seed=1866,std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,20,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.arena.boundaryWalls={{{-31,-1,-31},{-30,20,31}},{{30,-1,-31},{31,20,31}},{{-31,-1,-31},{31,20,-30}},{{-31,-1,30},{31,20,31}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.roomClear=false;s.godMode=true;s.player.position={0,.85f,20};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({},1.f/30);}
void damage(Simulation &s,EntityId id,float amount,bool execution=false,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=execution;e.debugExecution=debug;s.queueRoot(e);s.drainEvents();
}
int count(const Simulation &s,int type){return int(std::count_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.monster.type==type;}));}
Enemy *first(Simulation &s,int type){for(auto &e:s.enemies)if(e.alive&&e.monster.type==type)return &e;return nullptr;}
EntityId spawn(Simulation &s,int type=278){return s.spawnMonster(monsterId(type),{0,.85f,0});}

void damageAndMotion() {
    auto s=fixture();const auto id=spawn(s);
    check(near(s.findEnemy(id)->hp,105.6f)&&s.findEnemy(id)->blackGlobin&&!s.content->regrowth(monsterId(278)),"parent has converted33HP and no goo controller");
    tick(s);check(near(s.findEnemy(id)->position.z,0),"first source frame only initializes");
    tick(s);check(near(s.findEnemy(id)->velocity.z,3.6f),"source .6 ground force and doubled far impulse");
    damage(s,id,16);tick(s);check(count(s,85)==0,"exactly5sourceHP does not cross strict threshold");
    damage(s,id,.1f);tick(s);check(count(s,85)==1,"small hits accumulate past source threshold");
    auto *kid=first(s,85);const auto childId=kid->id;
    check(kid->thrownOffspring&&near(kid->hp,20.8f)&&!kid->spider->diesOnContact,"live spider has full HP and ordinary persistent contact policy");
    const auto flight=*kid->thrownOffspring;
    check(near(flight.height,-30)&&near(flight.verticalVelocity,-8),"spider begins at source height and upward velocity");
    check(near(flight.step.z,(s.player.position.z-flight.origin.z)*.75f*.04f),"launch targets three quarters of player delta");
    Event direct;direct.type=EventType::Damage;direct.target=childId;direct.damage=3;
    s.queueRoot(direct);s.drainEvents();check(near(s.findEnemy(childId)->hp,17.8f),"airborne collision-zero state does not grant blanket direct-damage immunity");
    Event bullet;bullet.type=EventType::Shot;bullet.position=bullet.origin=add(kid->position,{-2,-.85f,0});
    bullet.direction={1,0,0};bullet.speed=120;bullet.damage=100;bullet.projectileRadius=.2f;bullet.projectileLife=1;
    s.queueRoot(bullet);s.drainEvents();tick(s);check(s.findEnemy(childId)&&near(s.findEnemy(childId)->hp,17.8f),"physical projectile passes airborne child");
    damage(s,id,9);damage(s,id,9);tick(s);
    check(count(s,85)==2,"multiple damage events before one source update coalesce into one birth");
    const auto n=count(s,85);tick(s,2);check(count(s,85)==n,"unchanged HP does not repeatedly emit spiders");
    auto *moving=s.findEnemy(childId);s.godMode=false;s.player.position=moving->position;tick(s);
    check(near(s.player.hp,StartingHealth),"airborne entity-collision-zero spider cannot touch player");
    s.godMode=true;s.player.position={-25,.85f,-25};tick(s,45);
    check(s.findEnemy(childId)&&!s.findEnemy(childId)->thrownOffspring,"spider lands and remains an independent threat");
    s.player.position=s.findEnemy(childId)->position;s.findEnemy(childId)->state=EnemyState::Stunned;s.findEnemy(childId)->stateTime=2;
    s.godMode=false;tick(s);check(s.findEnemy(childId)&&s.player.hp<StartingHealth,"landed spider damages on contact without Nest expiration");
    auto a=fixture(),b=fixture();const auto ai=spawn(a),bi=spawn(b);
    tick(a,30);for(int i=0;i<60;++i)b.step({},1.f/60);
    check(distance(a.findEnemy(ai)->position,b.findEnemy(bi)->position)<.001f,"pursuit integration agrees at30/60Hz");
    auto cover=fixture();cover.arena.obstacles.push_back({{-2,0,3},{2,6,5}});cover.arena.rebuildWalls();const auto ci=spawn(cover);
    for(int i=0;i<150;++i){tick(cover);check(!cover.arena.blocked(cover.findEnemy(ci)->position,.6f),"ground pursuit never enters solid cover");}
    check(cover.findEnemy(ci)->position.z>5,"parent routes around cover toward player");
    std::cout<<"PASS initialization, ground pursuit, strict accumulated damage, coalescing, throws and contact policy\n";
}

void mortality() {
    for(float amount:{105.6f,10000.f})for(bool execution:{false,true}) {
        auto s=fixture();const auto id=spawn(s);tick(s);damage(s,id,amount,execution);tick(s);
        check(!first(s,278)&&count(s,279)==1&&count(s,280)==1&&count(s,85)==1,"normal and extreme lethal damage release independent head/body plus one HP-triggered spider");
        check(near(first(s,279)->hp,64)&&near(first(s,280)->hp,32),"head/body use native20/10HP conversion");
        for(const auto &e:s.enemies)check(!e.componentOwner&&!e.partner,"death parts survive without owned-component dependency");
        tick(s,2);check(count(s,279)==1&&count(s,280)==1,"death releases parts exactly once");
    }
    auto low=fixture();auto id=spawn(low);tick(low);damage(low,id,100);tick(low);
    check(count(low,85)==1,"large nonlethal hit emits one spider");damage(low,id,6);tick(low);
    check(count(low,85)==1&&count(low,279)==1&&count(low,280)==1,"small final hit does not invent extra death spider");
    auto debug=fixture();id=spawn(debug);tick(debug);damage(debug,id,10000,true,true);tick(debug);
    check(debug.livingEnemies()==0,"debug execution suppresses offspring");
    auto pending=fixture();pending.debugScenario=false;id=spawn(pending);tick(pending);pending.limits.enemies=0;
    damage(pending,id,10000);tick(pending,4);
    check(pending.livingEnemies()==0&&!pending.roomClear,"reserved death children keep exits sealed under capacity pressure");
    pending.limits.enemies=10;tick(pending);
    check(count(pending,279)==1&&count(pending,280)==1&&count(pending,85)==1&&!pending.roomClear,"all reserved offspring resume after capacity recovery");
    auto deep=fixture();id=spawn(deep);deep.findEnemy(id)->generation=4;tick(deep);damage(deep,id,10000);tick(deep);
    check(count(deep,279)==1&&count(deep,280)==1&&count(deep,85)==1,"terminal offspring survive ancestry safety bound");
    std::cout<<"PASS mortality, no goo/overkill cutoff, no duplicate final spider, retained births and room completion\n";
}

void headAndBody() {
    auto head=fixture();const auto id=spawn(head,279);tick(head);check(near(head.findEnemy(id)->velocity.z,0),"head initializes before pursuit");
    tick(head);check(near(head.findEnemy(id)->velocity.z,3),"head uses .5 pursuit force instead of Brain cardinal charge");
    tick(head,45);check(head.findEnemy(id)->position.z>5&&head.findEnemy(id)->brain->charges==0&&head.findEnemy(id)->brain->creepPatches>0,"head chases and leaves red creep without charge state");
    check(!head.hazards.empty()&&head.hazards.front().kind==HazardKind::Creep&&near(head.hazards.front().damage,10),"source trail is actual damaging creep");
    damage(head,id,10000);tick(head);check(head.livingEnemies()==0,"head has no further death offspring");
    std::set<int> initial,reload;
    for(uint32_t seed=0;seed<32;++seed) {
        auto s=fixture(seed);const auto body=spawn(s,280);tick(s);
        const int timer=s.findEnemy(body)->headless->cooldown;initial.insert(timer);
        check(timer>=20&&timer<=39,"body initial timer is20..39");
        tick(s,timer);check(count(s,85)==0&&s.findEnemy(body)->headless->cooldown==0,"timer reaches zero before release on following source update");
        tick(s);check(count(s,85)==1&&first(s,85)->thrownOffspring&&s.projectiles.empty(),"wandering body throws a spider, not Gusher bullets");
        const int next=s.findEnemy(body)->headless->cooldown;reload.insert(next);
        check(next==90||next==180,"body reload selects exactly90or180");
        check(s.findEnemy(body)->headless->births==1&&near(first(s,85)->hp,20.8f),"body releases one full-health persistent spider");
    }
    check(initial.size()>10&&reload.size()==2,"independent seeds cover both reload outcomes and initial range");
    auto crowd=fixture();auto body=spawn(crowd,280);
    for(int n=0;n<4;++n){auto dummy=crowd.spawnMonster(monsterId(12),{float(n*3-6),.85f,-20});crowd.findEnemy(dummy)->state=EnemyState::Stunned;crowd.findEnemy(dummy)->stateTime=100;}
    tick(crowd,90);check(count(crowd,85)==0&&crowd.findEnemy(body)->headless->cooldown==0,"five hostile room bodies block spawning without resetting due timer");
    damage(crowd,first(crowd,12)->id,10000,true,true);tick(crowd);check(count(crowd,85)==1,"population drop releases due spider immediately");
    auto blocked=fixture();body=spawn(blocked,280);blocked.limits.enemies=1;tick(blocked,700);
    check(blocked.findEnemy(body)->headless->births==4,"reserved births count toward global population cap");
    blocked.limits.enemies=10;tick(blocked);check(count(blocked,85)==4,"all retained brood can be placed after capacity recovers");
    std::cout<<"PASS head pursuit/creep and body cooldown/population/throw behavior\n";
}

void configurationAndPlacement() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-black-globin-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}} cleanup{dir};
    std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"black_globin.mechanics");const std::string original{std::istreambuf_iterator<char>(in),{}};
    auto load=[&](const std::string &s){std::ofstream(dir/"black_globin.mechanics")<<s;return MechanicsLibrary::load(dir);};
    const auto old=load(original);
    std::string changed=original;const auto at=changed.find("22 16 .75");check(at!=changed.npos,"threshold directive exists");changed.replace(at,9,"22 20 .75");
    const auto updated=load(changed);check(old->fingerprint()!=updated->fingerprint()&&near(old->blackGlobin(monsterId(278))->damageThreshold,16)&&near(updated->blackGlobin(monsterId(278))->damageThreshold,20),"external edit produces immutable new mechanics snapshot");
    for(const auto &line:{"brain_charge 279.0.0 7 20 200 16 .8 .1\n","headless_brood 280.0.0 85.0.0 5 90 180 10 -30\n"}) {
        bool rejected=false;try{load(original+line);}catch(...){rejected=true;}check(rejected,"conflicting/duplicate external controller rejected");
    }
    int natural=0;
    for(uint64_t seed=0;seed<128&&natural<3;++seed) {
        const ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&natural<3;++floor) {
            if(plan.profileOnFloor(floor).band!=3)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom()&&natural<3;++room) {
                int n=0;for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(278))++n;
                check(n<=1,"at most one natural Black Globin specialist per room");
                if(n){++natural;std::cout<<"NATURAL_BLACK_GLOBIN seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<'\n';}
            }
        }
    }
    check(natural==3,"actual seeded residents reach final expedition band");
    std::cout<<"PASS external snapshot reload, validation and seeded placement\n";
}
void startingKit() {
    for(uint32_t seed=0;seed<4;++seed) {
        auto s=fixture(seed);s.debugScenario=false;s.godMode=false;spawn(s);
        int frames=0;size_t peak=0;
        for(;frames<3600&&!s.dead&&!s.roomClear;++frames) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&!e.thrownOffspring&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            Input in;
            if(target) {
                const auto delta=horizontal(sub(target->position,s.player.position)),v=horizontal(target->velocity);
                const float speed=playerAttack(s,s.player.shotDamage,false).speed;
                const float a=dot(v,v)-speed*speed,b=2*dot(delta,v),c=dot(delta,delta),disc=b*b-4*a*c;
                float flight=length(delta)/speed;
                if(disc>=0&&std::abs(a)>.0001f) {
                    const float t1=(-b-std::sqrt(disc))/(2*a),t2=(-b+std::sqrt(disc))/(2*a);
                    if(t1>0)flight=t1;if(t2>0)flight=std::min(flight,t2);
                }
                in.fire=true;in.aim=add(target->position,mul(v,flight));
                in.movement=length(delta)<5?mul(unit(delta),-1):length(delta)>10?unit(delta):Vector3{};
                in.dodge=length(delta)<2.2f;
            }
            s.step(in);peak=std::max(peak,s.roomThreats());
        }
        std::cout<<"BLACK_GLOBIN_STARTING_KIT seed="<<seed<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<" peak="<<peak<<" cleared="<<s.roomClear<<'\n';
        check(s.roomClear&&!s.dead&&peak>=3,"starting revolver/dodge clears parent and actual offspring without upgrades");
    }
}
}
int main(){std::cout<<std::unitbuf;try{damageAndMotion();mortality();headAndBody();configurationAndPlacement();startingKit();std::cout<<"PASS Black Globin family\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
