#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceCombatRockRooms.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *message){if(!b)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.00002f;}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Canyon);
    s.arena=Arena{};s.arena.bounds={{-20,-1,-20},{20,8,20}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-20,-.4f,-20},{20,0,20}}};}
    s.arena.boundaryWalls={{{-21,-1,-21},{-20,8,21}},{{20,-1,-21},{21,8,21}},{{-21,-1,-21},{21,8,-20}},{{-21,-1,20},{21,8,21}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void hit(Simulation &s,EntityId id,float damage=11.2f,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.debugExecution=debug;e.execution=debug;
    check(s.queueRoot(e),"hit admitted");s.drainEvents();
}

auto rows(const char *file) {
    std::ifstream in(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/d14a3-round-worm/source/"+file);
    check(bool(in),"native capture exists");std::vector<std::vector<float>> out;std::string line;std::getline(in,line);
    while(std::getline(in,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream r(line);std::vector<float> v;float f;while(r>>f)v.push_back(f);out.push_back(v);}return out;
}
void native() {
    int count=0;
    for(const auto &r:rows("native-shots.csv")){auto v=roundWormShot({r[0],0,r[1]});check(near(v.x,r[2])&&near(v.z,r[3]),"native single aimed speed10");++count;}
    for(const auto &r:rows("native-prediction.csv")){auto v=roundWormLead({r[0],0,r[1]});check(near(v.x,r[2])&&near(v.z,r[3]),"native ten-step lead");++count;}
    for(const auto &r:rows("native-relocation.csv")){check(roundWormRelocation(r[0]*r[0],unsigned(r[1]))==bool(r[2]),"native strict relocation/parity gate");++count;}
    check(count==61,"all bounded math comparisons");std::cout<<"PASS 61 original-code shot/lead/relocation comparisons\n";
}
void behavior() {
    using P=RoundWormPhase;
    auto s=fixture();const auto id=s.spawnMonster(monsterId(244),{0,.85f,0});
    check(id&&near(s.findEnemy(id)->hp,32)&&s.roomThreats()==1,"source10 HP x3.2 and threat participation");
    for(int i=0;i<33;++i)s.step({});check(s.findEnemy(id)->roundWorm->phase==P::DigIn,"DigIn remains visible before frame17");
    s.step({});check(s.findEnemy(id)->roundWorm->phase==P::Hidden&&s.findEnemy(id)->state==EnemyState::Buried,"DigIn17 hides and disables collision");
    hit(s,id,100);check(s.findEnemy(id)->hp==32,"hidden actor rejects ordinary damage");
    for(int i=0;i<200&&s.findEnemy(id)->roundWorm->phase==P::Hidden;++i)s.step({});
    auto *e=s.findEnemy(id);check(e->roundWorm->phase==P::DigOut&&e->roundWorm->relocations==1,"hidden ordinary relocation emerges");
    check(!s.arena.blocked(e->position,e->radius)&&planarDistance(e->position,s.player.position)>100*Simulation::GaperMovementScale,"emergence physically clear and outside native minimum distance");
    const auto at=e->position;for(int i=0;i<75;++i)s.step({});check(s.stats.projectiles==0,"no shot before DigOut38");s.step({});
    check(s.stats.projectiles==1&&e->roundWorm->shots==1,"exactly one shot at DigOut38");
    check(!s.projectiles.empty()&&s.projectiles.front().pooterFlight&&near(length(s.projectiles.front().velocity),10*Simulation::GaperMovementScale*30),"mode0 flight and fixed player-relative speed");
    const auto born=s.projectiles.front().velocity;s.roundWormTuning={.5f,.5f};check(distance(s.projectiles.front().velocity,born)==0,"live edit retains emitted projectile");
    for(int i=0;i<46;++i)s.step({});check(e->roundWorm->phase==P::DigIn&&e->roundWorm->cycleSpeed==.5f,"DigOut61 ends with next-phase tuning");
    check(distance(e->position,at)==0,"surfaced worm remains stationary");
    hit(s,id);hit(s,id);check(e->alive,"two base hits survive");hit(s,id);check(!e->alive&&s.stats.kills==1,"third base hit kills once");
    auto contact=fixture();auto c=contact.spawnMonster(monsterId(244),{0,.85f,0});contact.godMode=false;contact.player.position=contact.findEnemy(c)->position;contact.step({});check(contact.player.hp==5,"contact deals one half-heart");
    auto dodge=fixture();dodge.godMode=false;dodge.spawnMonster(monsterId(244),dodge.player.position);dodge.player.dodge=.3f;dodge.step({});check(dodge.player.hp==6,"universal dodge protects against Round Worm contact");
    auto cap=fixture();auto k=cap.spawnMonster(monsterId(244),{0,.85f,0});auto &r=*cap.findEnemy(k)->roundWorm;r.initialized=true;r.phase=P::DigOut;r.frame=37;cap.limits.projectiles=0;
    cap.step({},1.f/30);check(r.pending&&r.frame==38,"capacity delays Shoot event");auto velocity=r.shotVelocity;cap.roundWormTuning.shotSpeed=2;cap.player.position.x=9;
    cap.step({},1.f/30);check(r.pending&&distance(r.shotVelocity,velocity)==0,"deferred payload retains aim and speed");cap.limits.projectiles=100;cap.step({},1.f/30);
    check(!r.pending&&r.shots==1&&cap.stats.projectiles==1,"pending attack admitted once");
    for(int hz:{30,60,120}) {
        auto a=fixture();auto v=a.spawnMonster(monsterId(244),{0,.85f,0});
        for(int i=0;i<10*hz;++i)a.step({},1.f/float(hz));
        const auto &w=*a.findEnemy(v)->roundWorm;
        std::cout<<"PARTITION "<<hz<<" shots="<<w.shots<<" burrows="<<w.burrows<<" phase="<<int(w.phase)<<" frame="<<w.frame<<'\n';
        check(w.shots>=3&&w.shots<=4&&w.burrows==4&&w.relocations==4,"30/60/120Hz cycle count");
    }
    check(near(defaultMechanics()->withRegularHealthMultiplier(.75f)->monsterHealth(monsterId(244),1),24),"shared regular HP multiplier");
    std::cout<<"PASS phases, hidden immunity, stationary surface, contact, three hits, deferred attack and frame partitions\n";
}
Simulation generated(uint64_t seed,float scale,int minimum,int maximum,int mode=1) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,minimum,maximum,.26f,true,mode,true,true,true,true,true,true,1,1,{}, {},false,25,{1});
}
void generation() {
    for(auto dims:{std::array<float,3>{.75f,5,5},{1.1f,7,9},{1.5f,10,10}}) {
        bool found=false;
        for(uint64_t seed: {445ULL}) {
            auto s=generated(seed,dims[0],int(dims[1]),int(dims[2]));
            if(!s.enterSourceRoomReview(505))continue;
            found=true;const auto room=s.room;const auto &layout=s.arena.rooms[size_t(room)];
            std::cout<<"WITNESS seed="<<seed<<" room="<<room+1<<" size="<<dims[0]<<" range="<<dims[1]<<'-'<<dims[2]<<'\n';
            check(s.enemies.size()==2&&s.floorEncounter(room).monsters==std::vector<MonsterId>(2,monsterId(244)),"complete two-worm roster and budget");
            check(std::count_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &b){return b.room==room;})==36,"exact recorded36 rocks");
            for(size_t i=0;i<2;++i){const auto cell=Basement505Worms[i];check(distance(s.enemies[i].position,sourceHeartCell(layout,cell[0],cell[1]))<.0001f,"exact initial source cells");}
            s.godMode=true;
            for(int tick=0;tick<1200;++tick){s.step({});for(const auto &e:s.enemies)if(e.alive&&e.state!=EnemyState::Buried)check(!s.arena.blocked(e.position,e.radius),"all surfaced relocations clear actual cover/floor");}
            unsigned shots=0;for(const auto &e:s.enemies){check(e.roundWorm->relocations>=5,"worms cannot stay stuck hidden");shots+=e.roundWorm->shots;}
            check(shots>0,"generated worms can shoot through actual open lines");
            s.applyCombatBalance(3.5f,1);s.canonicalShooting=true;
            for(int tick=0;tick<7200&&!s.roomClear;++tick) {
                Input input;
                for(const auto &e:s.enemies)if(e.alive&&e.state!=EnemyState::Buried) {
                    for(Vector3 direction:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}) {
                        const auto at=add(e.position,mul(direction,1.8f));
                        if(s.arena.roomAt(at)==room&&!s.arena.blocked(at,.48f)&&s.arena.clear(at,e.position,.15f)) {
                            s.player.position=at;input.fire=true;input.aim=e.position;break;
                        }
                    }
                    if(input.fire)break;
                }
                s.step(input);
            }
            check(s.stats.kills==2&&s.stats.shots>=6,"real player projectiles finish both worms");
            for(int i=0;i<240;++i)s.step({});
            check(s.roomClear&&s.roomThreats()==0,"ordinary clear releases encounter");
            s.jumpDebug(0);s.jumpDebug(room);check(s.roomThreats()==0,"revisit does not respawn worms");
            s.roundWormTuning={.7f,1.3f};s.resizeRooms(dims[0],int(dims[1]),int(dims[2]),.26f,std::nullopt,0);
            check(s.roundWormTuning==RoundWormTuning{.7f,1.3f}&&s.arena.rooms[size_t(room)].sourceCombatTemplate!=505,"OFF Apply removes room and preserves tuning");
            s.resizeRooms(dims[0],int(dims[1]),int(dims[2]),.26f,std::nullopt,1);check(s.arena.rooms[size_t(room)].sourceCombatTemplate==505&&s.roomEnemies(room).size()==2,"SOURCE Apply restores recorded room");
        }
        check(found,"natural source505 seed witness");
    }
}
void presets() {
    const auto root=std::filesystem::path(DEATHWARD_TEST_ROOT);
    const auto dir=std::filesystem::temp_directory_path()/("dw-round-worm-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    auto p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());
    check(p.defaultZoomPercent==165&&p.roundWorm==RoundWormTuning{},"old preset retains view and baseline worm");
    p.roundWorm={.65f,1.3f};p.save(dir/"export.json");const auto q=BalancePreset::load(dir/"export.json",defaultMechanics()->fingerprint());
    check(q.json()==p.json(),"schema49 export/load retains all fields");
    p.roundWorm.cycleSpeed=0;bool rejected=false;try{p.validate();}catch(...){rejected=true;}check(rejected,"invalid cycle rejected");
    std::filesystem::remove_all(dir);std::cout<<"PASS preset migration/export/load/validation\n";
}
}
int main(){try{native();behavior();generation();presets();std::cout<<"PASS Round Worm delivery checks\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
