#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
struct Pack {
    std::filesystem::path dir=std::filesystem::temp_directory_path()/("dw-hive-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
        std::ifstream in(dir/"evaders.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(dir);}
    auto load(std::string text){std::ofstream(dir/"evaders.mechanics")<<text;return MechanicsLibrary::load(dir);}
};
std::string replace(std::string s,const std::string &from,const std::string &to){auto at=s.find(from);check(at!=s.npos,"fixture profile exists");s.replace(at,from.size(),to);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId target,float amount){Event e;e.type=EventType::Damage;e.target=target;e.damage=amount;s.queueRoot(e);s.drainEvents();}
int children(const Simulation &s,EntityId parent){return int(std::count_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.summoner==parent;}));}
void attack() {
    Pack pack;auto text=replace(pack.original,".8 .5 .9 1.079 30", ".8 0 .9 0 30");
    auto lib=pack.load(text);auto s=fixture(lib);const auto owner=s.spawnMonster(monsterId(22),{0,.85f,0});
    check(near(s.findEnemy(owner)->hp,64),"source20HPx3.2");
    while(!s.findEnemy(owner)->evader||s.findEnemy(owner)->evader->attackFrame<0)tick(s);
    const auto began=s.stats.duration;tick(s,7);check(children(s,owner)==0,"Shoot4 has not happened after seven60Hz steps");
    tick(s);check(children(s,owner)==1,"Shoot4 releases one fly");
    auto child=std::find_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.summoner==owner;});
    check(child->monster==monsterId(18)&&child->buzz&&child->buzz->diesOnContact&&near(child->buzz->contactRetention,.9f),"real Hive spit preserves live-child contact policy");
    check(near(child->maxHp,16)&&child->generation==1,"normal live child health/generation");
    tick(s,28);check(s.findEnemy(owner)->evader->attackFrame<0,"HeadAttack recovers after18sourceframes");
    // Remove its live child so the next request cannot be confused with contact expiry.
    for(auto &e:s.enemies)if(e.id!=owner)e.alive=false;
    while(s.findEnemy(owner)->evader->attackFrame<0&&s.stats.duration-began<3)tick(s);
    check(std::abs(s.stats.duration-began-76./30)<.0001,"source cooldown75 followed by next acquisition update");
    auto crowded=fixture(lib);auto hive=crowded.spawnMonster(monsterId(22),{0,.85f,0});
    for(int i=0;i<8;++i){auto id=crowded.spawnMonster(monsterId(12),{float(i*3-12),.85f,-15});crowded.findEnemy(id)->state=EnemyState::Stunned;crowded.findEnemy(id)->stateTime=100;}
    tick(crowded,360);check(children(crowded,hive)==0,"unrelated room enemies inhibit spitting; no owner-only limit");
    auto limited=fixture(lib);const auto parent=limited.spawnMonster(monsterId(22),{0,.85f,0});limited.limits.enemies=1;
    tick(limited,120);check(children(limited,parent)==0&&limited.findEnemy(parent)->evader->attackFrame==4,"live Shoot waits at capacity");
    limited.limits.enemies=2;tick(limited,2);check(children(limited,parent)==1,"one retained Shoot resumes without duplicate");
    auto obstructed=fixture(lib);auto gone=obstructed.spawnMonster(monsterId(22),{0,.85f,0});
    while(!obstructed.findEnemy(gone)->evader||obstructed.findEnemy(gone)->evader->attackFrame<3)tick(obstructed);
    obstructed.arena.boundaryWalls.push_back({{-8,0,-8},{8,12,8}});obstructed.arena.rebuildWalls();tick(obstructed,2);
    check(children(obstructed,gone)==0&&obstructed.findEnemy(gone)->evader->fired,"blocked birth remains reserved after Shoot");
    damage(obstructed,gone,1000);tick(obstructed);check(!obstructed.findEnemy(gone),"owner removed before reserved birth");
    obstructed.arena.boundaryWalls.pop_back();obstructed.arena.rebuildWalls();tick(obstructed);
    check(obstructed.enemies.size()==1&&obstructed.enemies[0].summoner==gone&&obstructed.enemies[0].buzz&&obstructed.enemies[0].buzz->diesOnContact,
        "reserved live-child policy survives missing owner and placement retry");
    auto drowned=fixture();auto wet=drowned.spawnMonster(monsterId(22,1),{0,.85f,0});
    check(near(drowned.findEnemy(wet)->hp,57.6f),"source18HPx3.2");
    for(int i=0;i<120&&children(drowned,wet)==0;++i)tick(drowned);
    auto charger=std::find_if(drowned.enemies.begin(),drowned.enemies.end(),[&](const auto &e){return e.summoner==wet;});
    check(charger!=drowned.enemies.end()&&charger->monster==monsterId(23,1)&&near(charger->maxHp,drowned.content->monsterHealth(monsterId(23,1),drowned.arena.profile.sourceStage)*.5f),"Drowned live child has half normal health");
    for(auto id:{monsterId(22),monsterId(22,1)}) {
        auto contact=fixture();contact.spawnMonster(id,contact.player.position);tick(contact);check(near(contact.player.hp,StartingHealth),"both source bodies have harmless contact");
    }
    std::cout<<"PASS Hive/Drowned health, harmless contact, native attack event/timer, global population delay, live-child policy and bounded Shoot\n";
}
void death() {
    int fly=0,attackFly=0,pooter=0;
    auto s=fixture();
    for(int n=0;n<350;++n) {
        s.enemies.clear();const auto owner=s.spawnMonster(monsterId(22),{0,.85f,0});damage(s,owner,64);tick(s);
        check(s.livingEnemies()==4,"lone Hive emits ceil4 death children");
        for(const auto &e:s.enemies) {
            check(e.generation==1&&e.summoner==0,"death children do not acquire live-summon policy");
            if(e.monster==monsterId(13))++fly;
            else if(e.monster==monsterId(18)){++attackFly;check(!e.buzz||!e.buzz->diesOnContact,"death Attack Fly persists on contact");}
            else if(e.monster==monsterId(14))++pooter;else check(false,"unexpected Hive child");
        }
    }
    check(fly>800&&fly<980&&attackFly>300&&attackFly<460&&pooter>90&&pooter<170,"seeded independent7:3:1 mixtures, not fixed groups");
    auto population=fixture();auto parent=population.spawnMonster(monsterId(22),{0,.85f,0});
    for(int i=0;i<5;++i)population.spawnMonster(monsterId(12),{float(i*4-8),.85f,-20});
    damage(population,parent,64);tick(population);check(population.livingEnemies()==7,"five survivors reduce death count to ceil4/(1+1)=2");
    for(auto type:{monsterId(22),monsterId(22,1)}) {
        for(float excess:{63.f,64.f}) {
            auto q=fixture();auto id=q.spawnMonster(type,{0,.85f,0});damage(q,id,q.findEnemy(id)->hp+excess);tick(q);
            check((q.livingEnemies()>0)==(excess<64),"source -20HP threshold scales consistently to -64DW and is inclusive");
        }
    }
    auto pending=fixture();pending.debugScenario=false;auto id=pending.spawnMonster(monsterId(22),{0,.85f,0});pending.limits.enemies=0;
    damage(pending,id,64);tick(pending,5);check(pending.livingEnemies()==0&&!pending.roomClear,"pending offspring keep chamber sealed at zero capacity");
    pending.limits.enemies=4;tick(pending);check(pending.livingEnemies()==4&&!pending.roomClear&&pending.stats.kills==1,"all four reserved children survive capacity exhaustion, with one owner death");
    pending.killAll();tick(pending);check(pending.roomClear&&pending.livingEnemies()==0,"kill cheat clears retained children without spawning more");
    std::cout<<"PASS independent death mixtures, population count, scaled overkill, live/death distinction, retained births and completion\n";
}
void movementAndData() {
    auto s=fixture();auto id=s.spawnMonster(monsterId(22),{0,.85f,0});const auto initial=planarDistance(s.player.position,s.findEnemy(id)->position);
    tick(s,120);check(planarDistance(s.player.position,s.findEnemy(id)->position)>initial+1,"physical flee gains distance");
    auto far=fixture();far.player.position={0,.85f,29};auto owner=far.spawnMonster(monsterId(22),{0,.85f,-20});tick(far,120);
    check(children(far,owner)==0&&planarDistance(far.findEnemy(owner)->position,{0,.85f,-20})>.1f,"distant body wanders instead of firing or fleeing forever");
    Pack pack;for(const auto &bad:std::vector<std::pair<std::string,std::string>>{{"30 18 4 75","30 18 18 75"},{"4 8 20 69","9 8 20 69"},{"18.0.0 1","22.0.0 1"}}) {
        bool rejected=false;try{pack.load(replace(pack.original,bad.first,bad.second));}catch(...){rejected=true;}check(rejected,"invalid evader profile rejected");
    }
    auto first=pack.load(pack.original);auto after=pack.load(replace(pack.original,"30 18 4 75","30 18 4 90"));
    check(first->fingerprint()!=after->fingerprint()&&first->evader(monsterId(22))->cooldownFrames==75&&after->evader(monsterId(22))->cooldownFrames==90,"immutable external snapshot");
    FloorProfile floor;floor.band=1;floor.variant=FloorVariant::Flooded;
    const auto *replacement=first->replacement(monsterId(22),floor);
    check(replacement&&replacement->target==monsterId(22,1)&&replacement->chance==5000,"50percent source flooded replacement configured");
    floor.variant=FloorVariant::Standard;check(!first->replacement(monsterId(22),floor),"no dry-floor replacement");
    std::cout<<"PASS flee/wander and validated immutable external profiles; Flooded-only replacement\n";
}
void placement() {
    bool drowned=false;
    for(int band=0;band<3;++band) {
        bool hive=false;
        // Specialist additions change weighted selections. Search a bounded
        // range instead of accumulating fragile hand-picked witness seeds.
        for(uint64_t seed=0;seed<2048&&(!hive||(band==1&&!drowned));++seed) {
            ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            // Once normal Hive is witnessed, only a Flooded floor can satisfy
            // the remaining replacement assertion. Its actual room spawning
            // still runs through the production generator unchanged.
            if(hive&&band==1&&defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor)).variant!=FloorVariant::Flooded)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room) {
                int count=0;
                for(const auto &e:s.roomEnemies(room)) {
                    if(e.monster==monsterId(22)||e.monster==monsterId(22,1))++count;
                    if(e.monster==monsterId(22)&&!hive) {
                        hive=true;std::cout<<"NATURAL_HIVE seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<band<<'\n';
                    }
                    if(e.monster==monsterId(22,1)) {
                        check(band==1&&s.arena.profile.variant==FloorVariant::Flooded,"Drowned Hive only through correct floor context");
                        if(!drowned){drowned=true;std::cout<<"NATURAL_DROWNED_HIVE seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';}
                    }
                }
                check(count<=1,"one initial Hive-family summoner per room");
            }
        }
        check(hive,"Hive reachable in each intended stage band");
    }
    check(drowned,"real seeded Flooded replacement reachable");
}
}
int main(){try{attack();death();movementAndData();placement();std::cout<<"PASS Hive/Drowned evaders\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
