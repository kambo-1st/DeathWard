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
void check(bool condition,const char *message){if(!condition)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
struct Pack {
    std::filesystem::path dir=std::filesystem::temp_directory_path()/("dw-nest-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
        std::ifstream in(dir/"nest.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(dir);}
    auto load(const std::string &text){std::ofstream(dir/"nest.mechanics")<<text;return MechanicsLibrary::load(dir);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){auto n=s.find(a);check(n!=s.npos,"fixture directive");s.replace(n,a.size(),b);return s;}
Simulation fixture(uint32_t seed=1866,std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.roomClear=false;s.godMode=true;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({},1.f/30);}
void damage(Simulation &s,EntityId target,float amount){Event e;e.type=EventType::Damage;e.target=target;e.damage=amount;s.queueRoot(e);s.drainEvents();}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(205),{0,.85f,0});}
Enemy *child(Simulation &s,EntityId parent){for(auto &e:s.enemies)if(e.alive&&e.summoner==parent)return &e;return nullptr;}
int startAttack(Simulation &s,EntityId parent) {
    for(int n=0;n<500;++n){tick(s);auto *e=s.findEnemy(parent);if(e&&e->evader->attackFrame==0)return int(e->evader->cooldown);}
    throw std::runtime_error("Nest did not acquire an attack");
}
void attackAndMovement() {
    Pack pack;auto lib=pack.load(replace(pack.original,".8 .5 .9 1.079 30",".8 0 .9 0 30"));
    std::set<int> cooldowns;
    for(int seed=0;seed<32;++seed) {
        auto s=fixture(unsigned(seed),lib);auto owner=spawn(s);tick(s);
        auto *e=s.findEnemy(owner);check(e->evader->lifeTicks==1&&e->evader->attackFrame==-1&&length(e->velocity)==0,"initial native update does not move or attack");
        const int cooldown=startAttack(s,owner);cooldowns.insert(cooldown);
        check(cooldown>=130&&cooldown<=149,"Nest cooldown includes source55..74 bonus over75");
        tick(s,3);check(!child(s,owner),"no live spider before Shoot4");tick(s);
        e=child(s,owner);check(e&&e->monster==monsterId(85)&&near(e->hp,20.8f)&&e->spider&&e->spider->diesOnContact,"Shoot4 creates full-health contact-expiring Spider");
        const auto began=s.stats.duration-4./30;const auto offspring=e->id;
        damage(s,offspring,1000);tick(s,14);check(s.findEnemy(owner)->evader->attackFrame==-1,"HeadAttack ends after18source frames");
        startAttack(s,owner);check(std::abs(s.stats.duration-began-double(cooldown+1)/30)<.0001,"second attack respects the actual randomized countdown");
    }
    check(cooldowns.size()>=12,"independent seed stream exercises variable cooldown");
    auto flee=fixture();auto id=spawn(flee);tick(flee,120);
    check(planarDistance(flee.findEnemy(id)->position,flee.player.position)>11,"Nest flees a nearby player");
    auto far=fixture();far.player.position={0,.85f,29};id=far.spawnMonster(monsterId(205),{0,.85f,-20});tick(far,120);
    check(!child(far,id)&&planarDistance(far.findEnemy(id)->position,{0,.85f,-20})>.1f,"distant Nest wanders without spitting");
    auto blocked=fixture();blocked.arena.obstacles.push_back({{-29,0,4},{29,6,5}});blocked.arena.rebuildWalls();id=spawn(blocked);
    for(int n=0;n<120;++n){tick(blocked);check(!child(blocked,id)&&!blocked.arena.blocked(blocked.findEnemy(id)->position,.7f),"ground body stays outside solid cover and cannot spit through it");}
    auto crowd=fixture(1866,lib);id=spawn(crowd);
    for(int n=0;n<8;++n){auto other=crowd.spawnMonster(monsterId(12),{float(n*3-12),.85f,-20});crowd.findEnemy(other)->state=EnemyState::Stunned;crowd.findEnemy(other)->stateTime=100;}
    tick(crowd,240);check(!child(crowd,id),"unrelated hostile population delays Nest spawning");
    auto contact=fixture();contact.godMode=false;contact.spawnMonster(monsterId(205),contact.player.position);tick(contact);check(near(contact.player.hp,StartingHealth),"parent has harmless source contact");
    std::cout<<"PASS source initialization, Shoot4/18frames,130..149 cooldown, fleeing/wandering, sight and global population\n";
}
void liveContactAndRetention() {
    Pack pack;auto lib=pack.load(replace(pack.original,".8 .5 .9 1.079 30",".8 0 .9 0 30"));
    for(bool invulnerable:{false,true}) {
        auto s=fixture(1866,lib);auto owner=spawn(s);startAttack(s,owner);tick(s,4);const auto kid=child(s,owner)->id;
        s.player.position=child(s,owner)->position;s.godMode=invulnerable;
        if(invulnerable){child(s,owner)->state=EnemyState::Stunned;child(s,owner)->stateTime=1;}
        tick(s);
        check(!s.findEnemy(kid)&&s.stats.kills==1,"live spider expires on touch, even when player cannot take damage");
        check(near(s.player.hp,StartingHealth-(invulnerable?0:10*EnemyDamageMultiplier)),"only vulnerable player takes source contact damage");
    }
    auto pending=fixture(1866,lib);auto owner=spawn(pending);pending.limits.enemies=1;startAttack(pending,owner);tick(pending,10);
    check(!child(pending,owner)&&pending.findEnemy(owner)->evader->attackFrame==4,"capacity stalls the birth event instead of dropping it");
    pending.limits.enemies=2;tick(pending);check(child(pending,owner)&&child(pending,owner)->spider->diesOnContact,"capacity recovery delivers one flagged child");
    auto blocked=fixture(1866,lib);owner=spawn(blocked);startAttack(blocked,owner);tick(blocked,3);
    blocked.arena.boundaryWalls.push_back({{-8,0,-8},{8,12,8}});blocked.arena.rebuildWalls();tick(blocked);
    check(!child(blocked,owner)&&blocked.findEnemy(owner)->evader->fired,"blocked live birth remains reserved");
    damage(blocked,owner,1000);tick(blocked);check(!blocked.findEnemy(owner),"owner is removed before placement retries");
    blocked.arena.boundaryWalls.pop_back();blocked.arena.rebuildWalls();tick(blocked);
    check(child(blocked,owner)&&child(blocked,owner)->spider->diesOnContact,"birth policy survives loss of owner");
    auto *e=child(blocked,owner);const auto kid=e->id;blocked.player.position=e->position;blocked.limits.queuedEvents=0;tick(blocked);
    check(blocked.findEnemy(kid)&&blocked.findEnemy(kid)->selfDetonated,"full event queue preserves pending contact death");
    blocked.limits.queuedEvents=16384;tick(blocked);check(!blocked.findEnemy(kid),"spent spider retries its death without resuming pursuit");
    std::cout<<"PASS live/death policy distinction, invulnerable contact, capacity, orphaned birth and event-queue retry\n";
}
void deathAndCompletion() {
    auto s=fixture();int big=0,trite=0;
    for(int n=0;n<256;++n) {
        s.enemies.clear();const auto owner=spawn(s);damage(s,owner,64);tick(s);
        check(s.livingEnemies()==1,"Nest emits exactly one death child");const auto &e=s.enemies.front();
        check(!e.summoner&&e.generation==1&&near(e.position.x,0)&&near(e.position.z,0),"death child starts at parent with no live-summon ownership");
        if(e.monster==monsterId(94)) {++big;check(near(e.hp,64)&&(!e.spider||!e.spider->diesOnContact),"Big Spider has normal health/contact policy");}
        else {++trite;check(e.monster==monsterId(29,1)&&near(e.hp,32),"other equal-weight death outcome is Trite");}
    }
    check(big>85&&big<171&&trite>85&&trite<171,"seeded death choices exercise both source half-probability outcomes");
    for(float excess:{63.f,64.f,200.f}) {
        auto q=fixture();auto id=spawn(q);damage(q,id,64+excess);tick(q);
        check((q.livingEnemies()==1)==(excess<64),"inclusive source-20HP overkill threshold scales to-64DW");
    }
    auto cap=fixture();cap.debugScenario=false;auto owner=spawn(cap);cap.limits.enemies=0;damage(cap,owner,64);tick(cap,3);
    check(!cap.roomClear&&cap.livingEnemies()==0,"retained required death child keeps room sealed");
    cap.limits.enemies=2;tick(cap);check(!cap.roomClear&&cap.livingEnemies()==1&&cap.stats.kills==1,"one child appears after capacity returns");
    // Follow an actual Nest -> Big Spider -> ordinary Spider chain.
    for(int n=0;n<32;++n) {
        auto chain=fixture(unsigned(n));owner=spawn(chain);damage(chain,owner,64);tick(chain);
        if(chain.enemies.front().monster!=monsterId(94))continue;
        const auto bigId=chain.enemies.front().id;damage(chain,bigId,64);tick(chain);
        check(chain.livingEnemies()==2,"Nest's Big Spider releases its two required ordinary children");
        for(const auto &e:chain.enemies)check(e.monster==monsterId(85)&&(!e.spider||!e.spider->diesOnContact),"contact expiry does not leak into grandchildren");
        const auto kid=chain.enemies.front().id;chain.player.position=chain.enemies.front().position;tick(chain);
        check(chain.findEnemy(kid)&&chain.findEnemy(kid)->alive,"ordinary grandchild survives contact");
        cap.killAll();tick(cap);check(cap.roomClear,"kill cheat removes all remaining threats and reservations");
        std::cout<<"PASS equal death choice, overkill, offspring chain and sealed completion\n";return;
    }
    throw std::runtime_error("No Big Spider chain witness");
}
void configurationAndPlacement() {
    Pack pack;auto first=pack.load(pack.original);auto after=pack.load(replace(pack.original,"205.0.0 55 74","205.0.0 60 80"));
    check(first->fingerprint()!=after->fingerprint()&&first->evader(monsterId(205))->cooldownBonusMinimum==55&&after->evader(monsterId(205))->cooldownBonusMaximum==80,"immutable external cooldown snapshots");
    for(const auto &bad:std::vector<std::string>{replace(pack.original,"205.0.0 55 74","205.0.0 75 55"),replace(pack.original,"205.0.0 55 74","205.0.0 0 74"),
        replace(pack.original,"205.0.0 55 74","205.0.0 55 600"),replace(pack.original,"85.0.0 1","18.0.0 1"),
        pack.original+"evader_cooldown_bonus 205.0.0 55 74\n",pack.original+"evader_child_contact_death 205.0.0\n",
        pack.original+"evader_child_contact_death 16.0.0\n"}) {
        bool rejected=false;try{pack.load(bad);}catch(...){rejected=true;}check(rejected,"invalid or conflicting external profile rejected");
    }
    std::set<int> bands;
    for(uint64_t seed=0;seed<128&&bands.size()<3;++seed) {
      const ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
      for(int floor=0;floor<plan.floorCount;++floor) {
        if(plan.profileOnFloor(floor).band>=3||bands.contains(plan.profileOnFloor(floor).band))continue;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room) {
            int count=0;for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(205)) {
                ++count;check(s.arena.profile.band<3,"Nest stays in reviewed early/middle bands");
                if(bands.insert(s.arena.profile.band).second)std::cout<<"NATURAL_NEST seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<'\n';
            }
            check(count<=1,"one natural Nest specialist per room");
        }
      }
    }
    check(bands.size()==3,"actual seeded Nest residents in all three approved bands");
    std::cout<<"PASS external validation, snapshot reload and actual seeded floor placement\n";
}
void startingKit() {
    for(uint32_t seed=0;seed<8;++seed) {
        auto s=fixture(seed);s.debugScenario=false;s.godMode=false;const auto owner=spawn(s);
        bool firing=false;int frames=0;size_t peak=0;
        for(;frames<2400&&!s.dead&&!s.roomClear;++frames) {
            firing|=child(s,owner)!=nullptr;
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            check(target,"unfinished Nest encounter retains a target");
            Input in;in.fire=firing;const auto delta=horizontal(sub(target->position,s.player.position)),v=horizontal(target->velocity);
            const float speed=playerAttack(s,s.player.shotDamage,false).speed;
            const float a=dot(v,v)-speed*speed,b=2*dot(delta,v),c=dot(delta,delta),disc=b*b-4*a*c;
            float flight=length(delta)/speed;
            if(disc>=0&&std::abs(a)>.0001f) {
                const float t1=(-b-std::sqrt(disc))/(2*a),t2=(-b+std::sqrt(disc))/(2*a);
                if(t1>0)flight=t1;if(t2>0)flight=std::min(flight,t2);
            }
            in.aim=add(target->position,mul(v,flight));
            in.movement=length(delta)<4?mul(unit(delta),-1):length(delta)>9?unit(delta):Vector3{};
            in.dodge=length(delta)<2.2f;s.step(in);peak=std::max(peak,s.roomThreats());
        }
        std::cout<<"NEST_STARTING_KIT seed="<<seed<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<" peak="<<peak<<'\n';
        check(s.roomClear&&!s.dead&&s.player.hp>0&&frames<2400&&peak>=2,"starting revolver/dodge clears Nest, an actual live birth and death offspring without upgrades");
    }
}
}
int main(){try{attackAndMovement();liveContactAndRetention();deathAndCompletion();configurationAndPlacement();startingKit();std::cout<<"PASS Nest\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
