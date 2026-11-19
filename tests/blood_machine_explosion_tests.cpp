#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceRecordedShop.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool value,const char *why){if(!value)throw std::runtime_error(why);}
void ticks(Simulation &s,int count){for(int i=0;i<count;++i)s.step({});}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Mine,false);s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=false;s.player.position={0,.85f,0};s.roomClear=true;
    s.inventoryBombTuning=InventoryBombTuning{};return s;
}
void blast(Simulation &s,Vector3 at,float damage=100,bool line=false) {
    Event e;e.type=EventType::Explosion;e.position=at;e.radius=2;e.damage=damage;e.demolition=Demolition::SpentDynamite;e.explosionLineCheck=line;
    check(s.queueRoot(e),"blast queued");s.drainEvents();
}
void native() {
    const auto folder=Root/"docs/reports/isaac-first-floor-parity/d14a12-blood-machine-explosions/source";
    std::ifstream f(folder/"native-blast-drops.csv");check(bool(f),"native drop fixture");std::string line;std::getline(f,line);int rows=0;
    while(std::getline(f,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);uint32_t seed,after;int count;in>>seed>>count;
        std::array<BloodExplosionDrop,8> expected;for(auto &drop:expected)in>>drop.variant>>drop.seed;in>>after;check(bool(in),"native row parsed");
        const auto got=sourceBloodExplosionDrops(seed);check(got.count==count&&seed==after,"native drop count/RNG");
        for(int i=0;i<8;++i)check(got.entries[size_t(i)].variant==expected[size_t(i)].variant&&got.entries[size_t(i)].seed==expected[size_t(i)].seed,"native drop identity/seed/order");++rows;
    }
    check(rows==1030,"1030 native rows");
    std::ifstream gates(folder/"native-blast-gates.csv");check(bool(gates),"native gate fixture");std::getline(gates,line);rows=0;
    while(std::getline(gates,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int state,flags,amount,accepted,after;in>>state>>flags>>amount>>accepted>>after;
        check(accepted==((flags&4)&&state!=3)&&after==(accepted?3:state),"native flag/state/damage-independent gate");++rows;
    }
    check(rows==90,"90 native gate rows");std::cout<<"PASS 1030 native ordered drops/RNG and 90 damage/state cases\n";
}
void phasesAndGates() {
    for(auto phase:{BloodMachine::Phase::Idle,BloodMachine::Phase::Initiate,BloodMachine::Phase::Prize,BloodMachine::Phase::Broken}) {
        auto s=fixture();check(s.spawnBloodMachine({4,.85f,0},42),"machine spawn");auto &m=s.bloodMachines.front();m.phase=phase;m.elapsed=32.9;m.outcome=2;
        s.bloodExplosionTuning.outcome=3;blast(s,m.position,0);ticks(s,150);
        check(m.phase==BloodMachine::Phase::Broken&&m.blastDestroyed==(phase!=BloodMachine::Phase::Broken),"all live phases break, old broken stays broken");
        check(s.machineCollectibles.empty(),"unpaid donation never awards upgrade after destruction");
        check(s.moneyPickups.size()==(phase==BloodMachine::Phase::Broken?0:2),"once-only explosion coins");
        const auto rng=m.rng;blast(s,m.position);ticks(s,3);check(m.rng==rng&&s.moneyPickups.size()==(phase==BloodMachine::Phase::Broken?0:2),"repeat blast never rerolls/pays");
    }
    auto s=fixture();s.spawnBloodMachine({4,.85f,0},1);s.bloodExplosionTuning.destructible=false;blast(s,{4,.85f,0});check(!s.bloodMachines[0].blastDestroyed,"live destruction disabled");
    s.bloodExplosionTuning.destructible=true;s.bloodExplosionTuning.rewards=false;blast(s,{4,.85f,0});ticks(s,3);check(s.bloodMachines[0].blastDestroyed&&s.moneyPickups.empty()&&s.heartPickups.empty(),"drops disabled and no collider");
    auto cover=fixture();cover.spawnBloodMachine({4,.85f,0},1);cover.arena.walls.push_back({{2.7f,-1,-1},{2.9f,3,1}});blast(cover,{2,.85f,0},100,true);check(!cover.bloodMachines[0].blastDestroyed,"pre-blast cover respected");blast(cover,{2,.85f,0},100,false);check(cover.bloodMachines[0].blastDestroyed,"line-check off respects explicit blast policy");
    std::cout<<"PASS zero-damage blasts, all machine phases, no duplicate or delayed donation, gates and cover\n";
}
void heartsAndCapacity() {
    auto s=fixture();s.player.hp=2;s.spawnBloodMachine({4,.85f,0},42);s.bloodExplosionTuning.outcome=2;blast(s,{4,.85f,0});s.step({});
    check(s.heartPickups.size()==1&&s.heartPickups[0].amount==2&&s.heartPickups[0].sourceSubtype==1,"full red heart test actor");
    const auto at=s.heartPickups[0].position;s.player.position=at;s.step({});check(s.player.hp==2,"heart waits for appearance gate");ticks(s,75);check(s.player.hp==4,"heart heals exactly two half-units");ticks(s,30);check(s.heartPickups.empty(),"collected heart gone");
    for(int subtype:{1,2,3,4,5,6,10}) {
        auto heart=fixture();heart.pendingBloodRewards.push_back({{4,.85f,0},0,0,subtype,0,42,10});heart.step({});check(heart.pendingBloodRewards.empty()&&heart.heartPickups.size()==1&&heart.heartPickups[0].sourceSubtype==subtype,"all rare-gates-off heart subtypes admitted without substitution");
    }
    auto queue=fixture();queue.spawnBloodMachine({4,.85f,0},42);queue.bloodExplosionTuning.outcome=2;queue.heartPickups.resize(1024);for(auto &h:queue.heartPickups)h.position={50,.85f,50};blast(queue,{4,.85f,0});queue.step({});check(queue.pendingBloodRewards.size()==1,"heart capacity defers admitted identity");const auto seed=queue.pendingBloodRewards[0].seed;
    queue.bloodExplosionTuning={false,false,3};queue.heartPickups.clear();queue.step({});check(queue.pendingBloodRewards.empty()&&queue.heartPickups.size()==1&&queue.heartPickups[0].sourceSubtype==1&&seed!=0,"late setting edits do not reroll queued heart");
    auto paid=fixture();paid.spawnBloodMachine({4,.85f,0},42);paid.pendingBloodRewards.push_back({{4,.85f,0},0,0,1,0,42});paid.bloodExplosionTuning.rewards=false;blast(paid,{4,.85f,0});paid.step({});check(paid.moneyPickups.size()==1,"already resolved donation survives explosion");
    std::cout<<"PASS heart kinds, timing/healing, capacity and resolved donation boundaries\n";
}
void canyon(float scale,int lo,int hi) {
    Simulation s(68,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{1});
    check(s.enterSourceRoomReview(RecordedShopReview)&&s.shopCardSlot>=0,"recorded canyon shop");s.step({});s.moneyCollected=20;s.player.position=s.shopCardPosition();s.step({});check(s.pills.held==TemperanceCard&&s.shopCardSold&&s.money()==15,"buy native Temperance");check(s.usePill()&&s.bloodMachines.size()==1,"card creates ordinary machine");
    const auto at=s.bloodMachines[0].position;const int room=s.room;auto expectedSeed=s.bloodMachines[0].rng;const auto expected=sourceBloodExplosionDrops(expectedSeed);
    s.player.position=s.arena.rooms[size_t(room)].entry;Input fire;fire.fire=true;fire.aim=at;for(int i=0;i<100;++i)s.step(fire);check(!s.bloodMachines[0].blastDestroyed,"ordinary shots leave machine intact");
    bool placed=false;s.inventoryBombTuning=InventoryBombTuning{};
    for(int i=0;i<16&&!placed;++i){const float a=i*Pi/8;auto p=add(at,{1.5f*std::cos(a),0,1.5f*std::sin(a)});if(s.arena.roomAt(p)!=room||s.arena.blocked(p,.48f))continue;s.player.position=p;placed=s.placeDynamite();}
    check(placed,"place real inventory dynamite");s.player.position=s.arena.rooms[size_t(room)].entry;ticks(s,100);
    check(s.bloodMachines[0].blastDestroyed&&!s.arena.blocked(at,.48f),"actual dynamite removes machine collider");
    check(s.bloodMachines[0].blastDrops.count==expected.count&&s.bloodMachines[0].rng==expectedSeed,"actual source outcome, no forced drop");
    const auto paid=s.bloodMachines[0].blastDelivered;s.enterRoom(0);s.enterRoom(room);ticks(s,3);check(s.bloodMachines[0].blastDestroyed&&s.bloodMachines[0].blastDelivered==paid,"revisit no resurrection/duplicates");
    s.moneyPickups.clear();s.heartPickups.clear();s.pendingBloodRewards.assign(1024,BloodReward{at,room,0,1,0,42});
    check(s.spawnBloodMachine(at,42),"second machine at cleared blast site");s.bloodExplosionTuning.outcome=2;blast(s,at);
    check(s.bloodMachines.back().blastDestroyed&&s.bloodMachines.back().blastDelivered==0,"full pending queue retains machine-owned drop");const auto deferredSeed=s.bloodMachines.back().blastDrops.entries[0].seed;
    s.bloodExplosionTuning={false,false,2};s.resizeRooms(scale,lo,hi,.27f);check(s.bloodMachines.empty()&&s.bloodExplosionTuning==BloodExplosionTuning{false,false,2},"Apply resets floor actors, retains tuning");
    check(s.pendingBloodRewards.size()==1025&&s.pendingBloodRewards.back().variant==10&&s.pendingBloodRewards.back().seed==deferredSeed,"Apply retains machine-owned deferred identity behind full queue");s.pendingBloodRewards.clear();
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.bloodExplosionTuning==BloodExplosionTuning{false,false,2},"next floor retains configuration");
    std::cout<<"PASS canyon size="<<scale<<" card purchase / use / real dynamite / revisit / Apply / floor\n";
}
void presets() {
    auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a11-shopkeeper/review-preset.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&!p.bloodExplosions.custom(),"schema56 migrates without changing view");
    const auto file=std::filesystem::temp_directory_path()/("deathward-blood-blast-preset-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json");
    for(int mode=0;mode<4;++mode)for(bool enabled:{false,true}){p.bloodExplosions={enabled,!enabled,mode};p.save(file);check(BalancePreset::load(file,p.mechanicsFingerprint).revision()==p.revision(),"schema57 export/load");}
    auto invalid=p;invalid.bloodExplosions.outcome=4;bool rejected=false;try{invalid.save(file);}catch(...){rejected=true;}check(rejected&&BalancePreset::load(file,p.mechanicsFingerprint).revision()==p.revision(),"invalid export is atomic");std::filesystem::remove(file);
}
}
int main(){try{std::cout<<std::unitbuf;native();phasesAndGates();heartsAndCapacity();for(auto size:{std::tuple{.75f,5,5},std::tuple{1.f,7,9},std::tuple{1.5f,10,10}}){auto [scale,lo,hi]=size;canyon(scale,lo,hi);}presets();std::cout<<"PASS blood-machine explosion delivery\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
