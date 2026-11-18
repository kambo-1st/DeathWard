#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <filesystem>
#include <chrono>
#include <map>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
bool near(float a,float b){return std::abs(a-b)<.0002f;}
void check(bool b,const char *s){if(!b)throw std::runtime_error(s);}
auto rows(const char *name) {
    std::ifstream f(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/duke/"+name);
    check(bool(f),"native Duke fixture exists");std::string line;std::getline(f,line);std::vector<std::vector<std::string>> out;
    while(std::getline(f,line)){std::istringstream in(line);std::string cell;std::vector<std::string> row;while(std::getline(in,cell,','))row.push_back(cell);out.push_back(row);}return out;
}
void native() {
    using Key=std::pair<int,int>;std::map<Key,std::vector<std::vector<std::string>>> births;std::map<Key,int> sounds;std::map<Key,Vector3> origins;
    for(auto r:rows("native-births.csv"))births[{std::stoi(r[0]),std::stoi(r[1])}].push_back(r);
    for(auto r:rows("native-sounds.csv"))sounds[{std::stoi(r[0]),std::stoi(r[1])}]=std::stoi(r[2]);
    DukeRuntime duke;std::mt19937 rng;int current=-1,tick=0;size_t comparedBirths=0;float maximum=0;std::array<bool,15> selected{};
    auto difference=[&](float a,float b){maximum=std::max(maximum,std::abs(a-b));return std::abs(a-b)<.0001f;};
    const auto states=rows("native-states.csv");check(states.size()==3144,"all native Duke AI states present");
    for(const auto &r:states) {
        auto num=[&](int i){return std::stof(r[i]);};auto integer=[&](int i){return uint32_t(std::stoull(r[i]));};
        const int id=int(integer(0));
        if(id!=current) {
            current=id;tick=0;duke={};duke.initSeed=integer(1);rng.seed(duke.initSeed);
            duke.state=int(integer(2));duke.frame=int(integer(3));duke.position={num(6),0,num(7)};duke.momentum={num(8),0,num(9)};
        }
        ++tick;
        check(duke.state==int(integer(2))&&duke.frame==int(integer(3))&&difference(duke.position.x,num(6))&&difference(duke.position.z,num(7))&&difference(duke.momentum.x,num(8))&&difference(duke.momentum.z,num(9)),"native multi-update sequence enters the same controller state");
        const auto result=sourceDukeTick(duke,int(integer(4)),int(integer(5)),[&]{return uint32_t(rng());},integer(10));
        origins[{id,tick}]=duke.position;
        if(integer(11))sourceDukePhysics(duke);
        if(duke.state>=0&&duke.state<15)selected[size_t(duke.state)]=true;
        if(duke.state!=int(integer(12))||duke.frame!=int(integer(13)))std::cerr<<"STATE case="<<id<<" tick="<<tick<<" before="<<r[2]<<":"<<r[3]<<" wanted="<<r[12]<<":"<<r[13]<<" actual="<<duke.state<<":"<<duke.frame<<" total="<<r[4]<<" owned="<<r[5]<<'\n';
        check(duke.state==int(integer(12))&&duke.frame==int(integer(13)),"native Duke action selection and frame advancement");
        check(difference(duke.position.x,num(14))&&difference(duke.position.z,num(15))&&difference(duke.momentum.x,num(16))&&difference(duke.momentum.z,num(17))&&difference(duke.friction,num(18)),"native Duke force and optional ordered base physics");
        auto peek=rng;check(uint32_t(peek())==integer(19),"native global MT consumption includes omitted graphics requests");
        check(result.sound==sounds[{id,tick}]&&int(result.sound!=0)==int(integer(20)),"native Duke sound intent");
        const auto &expected=births[{id,tick}];check(duke.pending.size()==expected.size(),"native NPC birth payload count");
        for(size_t i=0;i<expected.size();++i) {
            const auto &e=expected[i];const auto &b=duke.pending[i];
            check(b.type==std::stoi(e[2])&&std::stoi(e[3])==0&&std::stoi(e[4])==0&&b.seed==std::stoul(e[5]),"native child identity and InitSeed");
            check(difference(b.position.x,std::stof(e[6]))&&difference(b.position.z,std::stof(e[7])),"native child position including death scatter");
            check(b.live==bool(std::stoi(e[8]))&&b.cohort==bool(std::stoi(e[9]))&&b.cohort==bool(std::stoi(e[10]))&&b.live==bool(std::stoi(e[11])),"native child spawner,parent,cohort and live-contact expiry");
            const float hp=float(b.type==13?3:5)*b.healthScale;
            check(difference(hp,std::stof(e[12]))&&difference(hp,std::stof(e[13]))&&difference(b.visualScale,std::stof(e[14])),"native child HP and visual scale mutation");++comparedBirths;
        }
        duke.pending.clear();
    }
    const auto releases=rows("native-releases.csv");check(releases.size()==304,"all native cohort releases present");
    for(const auto &r:releases) {
        const auto origin=origins.at({std::stoi(r[0]),std::stoi(r[1])});
        const auto after=sourceDukeRelease(sub(Vector3{std::stof(r[2]),0,std::stof(r[3])},origin),Vector3{std::stof(r[4]),0,std::stof(r[5])},std::stof(r[6]),std::stof(r[7]));
        check(difference(after.x,std::stof(r[8]))&&difference(after.z,std::stof(r[9]))&&r[10]=="1"&&r[11]=="1","native release impulse and detached cohort");
    }
    check(selected[4]&&selected[8]&&selected[13]&&selected[14],"all ordinary Duke actions exercised");check(comparedBirths==4345,"all native NPC birth intents compared");
    std::cout<<"NATIVE_DUKE states="<<states.size()<<" births="<<comparedBirths<<" maximum_numeric_difference="<<maximum<<" releases="<<releases.size()<<" retained_graphics_rng=1\n";
}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(42,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(content));
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,12,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={};r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.debugScenario=true;s.godMode=true;s.player.position={30,.85f,30};return s;
}
EntityId boss(Simulation &s,int state=4,int frame=0) {
    const auto id=s.spawnMonster(monsterId(67),{0,.85f,0});check(id,"source Duke boss can spawn");
    auto &e=*s.findEnemy(id);check(e.kind==EnemyKind::Boss&&e.duke&&e.hp==352&&e.maxHp==352,"dedicated Duke controller with separate XML110 HP");
    e.duke->initialized=true;e.duke->initSeed=42;e.duke->state=state;e.duke->frame=frame;e.duke->position={};s.combatRng=Random(42);return id;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,bool debug=false) {Event e;e.type=EventType::Damage;e.target=id;e.damage=1000;e.execution=debug;e.debugExecution=debug;s.queueRoot(e);s.drainEvents();}
void world() {
    auto s=fixture();auto id=boss(s,13,20);tick(s,2);
    size_t owned=0;std::vector<EntityId> flies;
    for(const auto &e:s.enemies)if(e.monster==monsterId(18)&&e.summoner==id) {
        ++owned;flies.push_back(e.id);check(e.dukeChild&&e.dukeChild->parent==id&&e.dukeChild->cohort&&e.dukeChild->initSeed&&e.buzz&&e.buzz->diesOnContact&&e.buzz->contactRetention==.9f&&e.spawnerType==67,"three live cohort children retain InitSeed,Parent,spawner and contact-expiry snapshot");
        check(e.hp==16&&e.maxHp==16,"live ordinary fly HP uses shared baseline spawning");
    }
    check(owned==3,"actual Duke cough creates exactly three owned Attack Flies");
    auto tuning=s.dukeTuning;const auto phase=s.findEnemy(id)->duke->frame;
    const auto velocity=s.findEnemy(flies.front())->velocity;tuning.flySpeed=.5f;tuning.movement=.75f;s.applyDukeTuning(tuning);
    check(planarDistance(s.findEnemy(flies.front())->velocity,mul(velocity,.5f))<.0001f&&s.findEnemy(id)->duke->frame==phase,"live fly speed preserves native momentum and boss phase");
    tuning.flySpeed=1;s.applyDukeTuning(tuning);

    auto &parent=*s.findEnemy(id);parent.duke->state=8;parent.duke->frame=17;parent.duke->clock=0;tick(s,2);
    for(auto fly:flies)check(s.findEnemy(fly)&&!s.findEnemy(fly)->dukeChild->cohort&&s.findEnemy(fly)->dukeChild->parent==0,"actual release detaches the whole cohort");
    auto big=fixture();id=boss(big,14,18);tick(big,2);size_t large=0;
    for(const auto &e:big.enemies)if(e.monster==monsterId(18)) {++large;check(e.dukeChild&&!e.dukeChild->cohort&&e.dukeChild->parent==0&&std::abs(e.hp-28.8f)<.001f&&std::abs(e.maxHp-28.8f)<.001f&&e.championVisual==1.25f&&e.buzz->diesOnContact,"big fly uses native1.8HP/1.25visual without acquiring cohort Parent");}
    check(large==1,"big-fly attack creates one actual actor");
    auto blocked=fixture();id=boss(blocked,13,20);blocked.limits.enemies=1;tick(blocked,2);
    auto *e=blocked.findEnemy(id);check(e&&e->duke->pending.size()==3&&e->duke->paused,"whole selected live birth waits when population is full");
    const auto seed=e->duke->pending[0].seed;auto rng=blocked.combatRng;tick(blocked,20);
    check(blocked.findEnemy(id)->duke->pending[0].seed==seed&&[&]{auto observed=blocked.combatRng;return rng.next()==observed.next();}(),"blocked live payload does not reroll or advance MT");
    blocked.limits.enemies=4;tick(blocked,2);check(blocked.livingEnemies()==4&&blocked.findEnemy(id)->duke->pending.empty(),"live birth recovery admits the complete retained cohort");
    auto held=fixture();id=boss(held,13,20);held.limits.enemies=1;tick(held,2);damage(held,id);tick(held,2);
    check(held.findEnemy(id)&&held.findEnemy(id)->duke->pending.size()==9,"death preserves selected live births plus all six death offspring");
    held.limits.enemies=9;tick(held,2);check(held.livingEnemies()==9,"combined retained payload recovers without loss");
    for(const auto &child:held.enemies)if(child.alive)check(child.dukeChild&&!child.dukeChild->cohort&&child.dukeChild->parent==0,"held live cohort detaches when its boss dies before admission");
    auto death=fixture();id=boss(death);death.limits.enemies=5;damage(death,id);tick(death,2);
    check(death.findEnemy(id)&&!death.findEnemy(id)->alive&&death.findEnemy(id)->duke->deathPending&&death.findEnemy(id)->duke->pending.size()==6,"dead Duke retains its complete six-fly payload under pressure");
    const auto first=death.findEnemy(id)->duke->pending[0].seed;tick(death,8);check(death.findEnemy(id)->duke->pending[0].seed==first,"death payload selected once");
    death.limits.enemies=6;tick(death,2);size_t offspring=0;
    for(const auto &child:death.enemies)if(child.alive) {++offspring;check(child.dukeChild&&!child.dukeChild->cohort&&child.dukeChild->parent==0&&child.summoner==0&&child.spawnerType==0&&(!child.buzz||!child.buzz->diesOnContact),"death offspring are unowned ordinary flies, with no live-contact expiry");}
    check(offspring==6,"exactly six real mixed Fly/Attack Fly death offspring admitted");
    auto clear=fixture();id=boss(clear,13,20);damage(clear,id,true);tick(clear,4);check(clear.livingEnemies()==0,"debug execution suppresses Duke offspring");
    auto touch=fixture();touch.godMode=false;boss(touch);touch.player.position={1.8f,.85f,0};tick(touch,2);
    check(touch.player.hp==5,"Duke planar source body contact deals one half-heart");
    auto dodge=fixture();dodge.godMode=false;boss(dodge);dodge.player.position={1.8f,.85f,0};const auto start=dodge.player.position;Input input;input.dodge=true;input.movement={1,0,0};dodge.step(input);
    check(dodge.player.dodge>0&&dodge.player.position.x-start.x>6*Tick&&dodge.player.hp==6,"universal dodge boost/immunity retained against the actual Duke body");
    check(!defaultMechanics()->regularHealthMember(monsterId(67))&&defaultMechanics()->monsterHealth(monsterId(67),1)==352&&defaultMechanics()->bossFormAllowed(monsterId(67),BossForm::Normal)&&!defaultMechanics()->bossFormAllowed(monsterId(67),BossForm::Cyan),"boss HP separation and ordinary-only form guard");
    struct Pack {
        std::filesystem::path path;
        Pack(){path=std::filesystem::temp_directory_path()/("deathward-duke-hp-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directory(path);for(const auto &entry:std::filesystem::directory_iterator(std::filesystem::path(DEATHWARD_TEST_ROOT)/"assets/mechanics"))if(entry.is_regular_file())std::filesystem::copy_file(entry.path(),path/entry.path().filename());}
        ~Pack(){std::error_code error;std::filesystem::remove_all(path,error);}
    } pack;
    const auto control=pack.path/"regular_enemy_health.mechanics";std::ifstream in(control);std::string text((std::istreambuf_iterator<char>(in)),{});in.close();
    const auto token=text.find("regular_health_multiplier 1");check(token!=text.npos,"regular HP control present");text.replace(token,std::string("regular_health_multiplier 1").size(),"regular_health_multiplier .75");std::ofstream(control)<<text;
    auto tuned=fixture(MechanicsLibrary::load(pack.path));id=boss(tuned,14,18);tick(tuned,2);
    check(tuned.findEnemy(id)->hp==352,"regular HP adjustment leaves Duke boss HP unchanged");
    for(const auto &child:tuned.enemies)if(child.monster==monsterId(18))check(std::abs(child.hp-21.6f)<.001f&&std::abs(child.maxHp-21.6f)<.001f,"big offspring HP uses shared .75 control before native1.8 multiplier");
    std::cout<<"PASS Duke world live/big/release/death payloads, capacity recovery, sourceHP and debug-clear isolation; full native acceptance and broad production pool remain open\n";
}
Simulation generated(float scale=1.1f,int lo=7,int hi=9) {
 return Simulation(69,17,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
    defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,25,RoomPropsTuning{0}); // Legacy bare arena; recorded contents have their own delivery test.
}
void hit(Simulation &s,EntityId id,float amount,bool area=false) {
 Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.areaDamage=area;s.queueRoot(e);s.drainEvents();
}
Enemy &liveBoss(Simulation &s) {for(auto &e:s.enemies)if(e.alive&&e.duke)return e;throw std::runtime_error("no live Duke");}
void ticks(Simulation &s,int n) {for(int i=0;i<n;++i)s.step({});}
void fightAndLoop() {
 for(auto dim:std::array<std::array<float,3>,3>{{{.75f,5,5},{1.1f,7,9},{1.5f,10,10}}}) {
  auto s=generated(dim[0],int(dim[1]),int(dim[2]));s.jumpDebug(s.finalRoom());
  check(s.livingEnemies()==1&&s.hasSourceBoss(s.room),"one selected ordinary Duke in actual generated boss room");
  auto id=liveBoss(s).id;check(liveBoss(s).hp==352,"source110 uses shared3.2 damage unit");
  check(!s.canUseFloorExit()&&!s.rewardAvailable(s.room)&&!s.arena.bossRewardPedestal,"fight seals reward and exit");
  check(near(s.player.attributes.speed,1)&&s.player.maxHp==6,"accepted movement and starting red health retained");
  hit(s,id,88);auto tuning=s.dukeTuning;tuning.health=.5f;s.applyDukeTuning(tuning);
  check(liveBoss(s).maxHp==176&&liveBoss(s).hp==132,"live boss HP preserves injury fraction");
  s.applyCombatBalance(3.5f,.75f);check(liveBoss(s).maxHp==176,"regular health override excludes boss");
  s.grant(BookOfShadowsKey);s.activeItem->charge=1;s.grant(CancerKey);s.grant({"isaac",ItemKind::Collectible,8});
  const auto beforeMoney=s.money();const auto beforeBombs=s.dynamite;
  s.player.hp=3;s.player.position=add(s.arena.rooms.back().center,{3,0,0});s.player.position.y=.85f;
  s.godMode=true;hit(s,id,400);ticks(s,2);
  check(!s.roomClear&&!s.canUseFloorExit()&&!s.rewardAvailable(s.room)&&!s.arena.bossRewardPedestal,"six death flies retain seals and reward gate");
  std::vector<EntityId> children;for(const auto &child:s.enemies)if(child.alive&&child.dukeChild)children.push_back(child.id);
  check(children.size()==6,"generated canyon admits all six death offspring");
  for(auto child:children)hit(s,child,1000);ticks(s,3);
  check(s.roomClear&&s.canUseFloorExit()&&s.rewardAvailable(s.room),"actual damage kill unlocks room, collectible and exit");
  check(s.money()==beforeMoney&&s.dynamite==beforeBombs,"no legacy boss currency or bomb payout");
  check(s.arena.bossRewardPedestal&&planarDistance(s.rewardPosition(s.room),s.arena.rooms.back().center)<.001f,"centered admitted pedestal");
  check(s.arena.blocked(s.rewardPosition(s.room),.48f),"pedestal collision exists");
  s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);
  check(s.collectTreasureUpgrade(),"touch collection grants Breakfast");
  check(s.player.maxHp==8&&s.player.hp==7,"installed XML maxhearts2 then hearts4");
  check(!s.collectTreasureUpgrade()&&s.itemStacks({"isaac",ItemKind::Collectible,25})==1,"single once-only reward");
  check(s.activeItem->item==BookOfShadowsKey&&s.activeItem->charge==2&&s.heldTrinket==CancerKey,"passive reward preserves active slot/clear charge/trinket");
  const int old=s.room;s.enterRoom(0);s.enterRoom(old);check(!s.rewardAvailable(old),"revisit cannot recreate reward");
  s.player.position=s.arena.exit;s.interact();check(s.floorExitRequested,"ordinary exit interaction requests descent");
  check(s.advanceFloor()&&s.floor==1&&s.player.maxHp==8&&s.player.hp==7,"descent retains Breakfast health");
  check(s.activeItem&&s.heldTrinket==CancerKey&&s.itemStacks({"isaac",ItemKind::Collectible,8})==1,"descent carries all owned categories");
  check(s.dukeTuning.health==.5f&&!s.hasSourceBoss(s.finalRoom()),"tuning carries but boss replacement is opening-floor-only");
 }
}
void persistence() {
 const auto fp=defaultMechanics()->fingerprint();BalancePreset p{1,fp};p.duke={true,.5f,.75f,1.25f};p.defaultZoomPercent=165;
 const auto path=std::filesystem::temp_directory_path()/"deathward-d13b-preset-test.json";p.save(path);
 auto loaded=BalancePreset::load(path,fp);check(loaded.duke==p.duke&&loaded.defaultZoomPercent==165,"schema44 exact round trip");std::filesystem::remove(path);
 for(const auto *name:{"d03-shooting/user-preset-2026-11-11.json","d13a-monstro-loop/migrated-preset-v43.json"}) {
  auto old=BalancePreset::load(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/"+name,fp);
  check(old.defaultZoomPercent==165&&!old.duke.enabled&&old.monstro.enabled&&old.playerSpeed==1,"old presets retain accepted boss and settings");
 }
}
} // namespace
int main(){try{native();world();fightAndLoop();persistence();std::cout<<"PASS D13b kernels, fly lifecycle, three generated reward/descent loops and presets\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<"\n";return 1;}}
