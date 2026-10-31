#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.003f){return std::abs(a-b)<eps;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("dw-mushroom-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(root);for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());std::ifstream in(root/"mushrooms.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(root);}
    void replace(std::string from,std::string to){auto text=original;auto at=text.find(from);check(at!=text.npos,"configuration fixture found");text.replace(at,from.size(),to);std::ofstream(root/"mushrooms.mechanics")<<text;}
    auto fixed(){replace("6 6 3 30 5 3","6 6 3 30 1 1");return MechanicsLibrary::load(root);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics(),uint64_t seed=1866) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,10,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={60,.85f,60};return s;
}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(300),{0,.85f,0});}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
auto &state(Simulation &s,EntityId id){return *s.findEnemy(id)->mushroom;}
void phase(Simulation &s,EntityId id,MushroomPhase target){for(int i=0;i<1500&&state(s,id).phase!=target;++i)tick(s);check(state(s,id).phase==target,"phase reached");}
void hit(Simulation &s,EntityId id,float value,DamageKind kind=DamageKind::Physical,bool explosion=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=value;e.damageKind=kind;e.explosionDamage=explosion;s.queueRoot(e);s.drainEvents();}
void cycleAndDamage() {
    Pack pack;auto lib=pack.fixed();auto s=fixture(lib);auto id=spawn(s);check(near(s.findEnemy(id)->hp,73.6f),"23sourceHP scaled once");
    for(auto kind:{DamageKind::Physical,DamageKind::Burning,DamageKind::Crush}){const float hp=s.findEnemy(id)->hp;hit(s,id,8,kind);check(near(s.findEnemy(id)->hp,hp-2),"closed quarter damage across channels");}
    float hp=s.findEnemy(id)->hp;hit(s,id,8,DamageKind::Physical,true);check(near(s.findEnemy(id)->hp,hp-2),"closed quarter explosive damage, not immunity");
    tick(s,10);check(state(s,id).phase==MushroomPhase::InitialHide,"initial hide still playing");tick(s,2);
    check(state(s,id).phase==MushroomPhase::Blocking&&state(s,id).timer==30,"initial hide6 frames precedes blocked countdown");
    tick(s,58);check(state(s,id).phase==MushroomPhase::Blocking&&state(s,id).timer==1,"closed30 ticks not early");tick(s,2);
    check(state(s,id).phase==MushroomPhase::Reveal&&state(s,id).frame==0,"opens regardless of distant target");
    hp=s.findEnemy(id)->hp;hit(s,id,8);check(near(s.findEnemy(id)->hp,hp-8),"full damage from start of Reveal, not only Shoot");
    tick(s,4);check(s.stats.projectiles==0,"no premature shot before sourceframe3");tick(s,2);
    check(state(s,id).fired&&s.stats.projectiles==4,"Shoot3 exactly four physical bullets");tick(s,6);
    check(state(s,id).phase==MushroomPhase::Revealed&&state(s,id).timer==30,"Reveal6 then exposed timer");
    tick(s,60);check(state(s,id).phase==MushroomPhase::Hide,"exposed30 frames then hide");
    hp=s.findEnemy(id)->hp;hit(s,id,8);check(near(s.findEnemy(id)->hp,hp-8),"hiding remains full damage until animation ends");
    tick(s,12);check(state(s,id).blocking()&&state(s,id).opening==0&&state(s,id).timer==30,"Hide6 returns to armor and resets timer");
    hp=s.findEnemy(id)->hp;hit(s,id,8);check(near(s.findEnemy(id)->hp,hp-2),"armor restored after hide");
    check(s.stats.projectiles==4&&s.enemies.size()==1,"no hidden repeat firing or offspring");
}
void patternsAndTiming() {
    Pack pack;auto lib=pack.fixed();bool cardinal=false,diagonal=false;
    for(uint64_t seed=1;seed<=20&&!(cardinal&&diagonal);++seed) {
        auto s=fixture(lib,seed);auto id=spawn(s);phase(s,id,MushroomPhase::Reveal);tick(s,6);const auto &r=state(s,id);
        check(s.projectiles.size()==4,"whole burst present");std::vector<Vector3> velocities;
        for(const auto &p:s.projectiles) {
            check(p.hostile&&p.context.sourceEntity==id&&near(p.damage,10)&&near(length(p.velocity),21),"native7speed converted3x without Host boost");
            check(near(p.velocity.y,0)&&near(p.origin.x,0)&&near(p.origin.z,0),"source origin and combat plane");
            if(r.diagonal)check(near(std::abs(p.velocity.x),21*.70710677f)&&near(std::abs(p.velocity.z),21*.70710677f),"diagonal cross coefficient");
            else check((near(p.velocity.x,0)&&near(std::abs(p.velocity.z),21))||(near(p.velocity.z,0)&&near(std::abs(p.velocity.x),21)),"cardinal axis cross");
            for(auto v:velocities)check(distance(v,p.velocity)>1,"four distinct directions");velocities.push_back(p.velocity);
        }
        cardinal|=!r.diagonal;diagonal|=r.diagonal;
        auto repeat=fixture(lib,seed);auto other=spawn(repeat);phase(repeat,other,MushroomPhase::Reveal);check(state(repeat,other).diagonal==r.diagonal,"seeded burst orientation");
    }
    check(cardinal&&diagonal,"both native cross selections reachable");
    for(uint64_t seed=1;seed<=12;++seed) {
        auto s=fixture(defaultMechanics(),seed);auto id=spawn(s);tick(s,2);
        check(state(s,id).timer>=30&&state(s,id).timer<=150&&state(s,id).timer%30==0,"discrete blocked1..5second choice");
        phase(s,id,MushroomPhase::Revealed);check(state(s,id).timer>=30&&state(s,id).timer<=90&&state(s,id).timer%30==0,"discrete exposed1..3second choice");
    }
}
void terrainAndLifecycle() {
    Pack pack;auto lib=pack.fixed();auto s=fixture(lib);auto id=spawn(s);
    s.arena.boundaryWalls={{{-5,-1,3},{5,10,3.1f}}};s.arena.rebuildWalls();s.player.position={0,.85f,6};
    phase(s,id,MushroomPhase::Revealed);check(s.stats.projectiles==4,"normal Mushroom does not require line of sight");tick(s,30);
    for(const auto &p:s.projectiles)if(p.velocity.z>20)check(p.position.z<3,"physical shots stopped by terrain");
    s.findEnemy(id)->position.x=1;s.findEnemy(id)->velocity={5,0,0};tick(s);check(near(s.findEnemy(id)->position.x,0)&&near(length(s.findEnemy(id)->velocity),0),"anchored position returns after shove");
    auto c=fixture(lib);c.godMode=false;c.player.position={0,.85f,0};spawn(c);tick(c);check(c.player.hp<100,"contact damages while closed");
    auto death=fixture(lib);id=spawn(death);phase(death,id,MushroomPhase::Reveal);hit(death,id,1000);tick(death,160);
    check(death.stats.projectiles==0&&death.stats.kills==1&&death.roomThreats()==0,"death cancels unissued burst and room threat");
    auto pause=fixture(lib);id=spawn(pause);phase(pause,id,MushroomPhase::Reveal);tick(pause,2);
    const int frame=state(pause,id).frame;pause.findEnemy(id)->state=EnemyState::Stunned;pause.findEnemy(id)->stateTime=1;tick(pause,30);
    check(state(pause,id).frame==frame&&pause.stats.projectiles==0,"local stun pauses cast");tick(pause,50);check(pause.stats.projectiles==4,"stun resumes once");
    auto rooms=fixture(lib);id=spawn(rooms);phase(rooms,id,MushroomPhase::Reveal);tick(rooms,2);
    const auto saved=state(rooms,id);rooms.enterRoom(1);tick(rooms,80);rooms.enterRoom(0);
    check(rooms.findEnemy(id)&&state(rooms,id).frame==saved.frame&&state(rooms,id).diagonal==saved.diagonal,"room suspension retains phase and chosen orientation");
}
void pressureAndConfig() {
    Pack pack;auto lib=pack.fixed();auto s=fixture(lib);auto id=spawn(s);s.limits.projectiles=3;tick(s,160);
    check(state(s,id).frame==3&&!state(s,id).fired&&s.stats.projectiles==0,"capacity never splits native cross");
    const bool direction=state(s,id).diagonal;s.limits.projectiles=32;s.limits.queuedEvents=3;tick(s,10);check(s.stats.projectiles==0,"event queue pressure retains whole cross");
    s.limits.queuedEvents=512;tick(s,2);check(s.stats.projectiles==4&&state(s,id).diagonal==direction,"retry preserves choice and emits once");
    for(auto pair:{std::pair{"6 6 3 30 5 3","6 6 6 30 5 3"},std::pair{".25 21 .70710677","0 21 .70710677"},std::pair{"Still Spread Skull","Chase Spread Skull"}}) {
        pack.replace(pair.first,pair.second);bool rejected=false;try{MechanicsLibrary::load(pack.root);}catch(...){rejected=true;}check(rejected,"invalid Mushroom configuration rejected");
    }
    auto original=defaultMechanics();pack.replace(".25 21 .70710677",".5 21 .70710677");auto changed=MechanicsLibrary::load(pack.root);
    check(near(original->mushroom(monsterId(300))->closedDamageScale,.25f)&&near(changed->mushroom(monsterId(300))->closedDamageScale,.5f)&&original->fingerprint()!=changed->fingerprint(),"immutable configuration reload");
}
void placement() {
    bool found=false;
    for(uint64_t seed=0;seed<256&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!found;++floor) {
            if(plan.profileOnFloor(floor).band!=1)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(300)) {
                found=true;check(near(e.hp,73.6f)&&e.mushroom.has_value(),"source HP and dedicated runtime in ordinary room");
                std::cout<<"NATURAL_MUSHROOM seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
            }
        }
    }
    check(found,"Mushroom reachable in Caves analogue band");
    for(int band:{0,2,3})for(int pattern=0;pattern<4;++pattern)for(const auto &e:defaultMechanics()->encounterPool(band,EncounterPattern(pattern)).specialists)
        check(e.monster!=monsterId(300),"Mushroom restricted to source habitat band");
}
}
int main(){try{cycleAndDamage();patternsAndTiming();terrainAndLifecycle();pressureAndConfig();placement();std::cout<<"PASS Mushroom source cycle, quarter damage, cross patterns, terrain, lifecycle, limits, config and placement\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
