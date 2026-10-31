#include "combat/Simulation.hpp"
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
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,20,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.arena.boundaryWalls={{{-41,-1,-41},{-40,20,41}},{{40,-1,-41},{41,20,41}},{{-41,-1,-41},{41,20,-40}},{{-41,-1,40},{41,20,41}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.roomClear=false;s.godMode=true;s.player.position={0,.85f,30};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({},1.f/30);}
EntityId spawn(Simulation &s,int stage=0){return s.spawnMonster(monsterId(310,0,stage),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float native,bool execution=false,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=native*3.2f;e.execution=execution;e.debugExecution=debug;s.queueRoot(e);s.drainEvents();
}
int flesh(const Simulation &s){return int(std::count_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.alive&&e.monster==monsterId(310,1);}));}
void shedding() {
    for(const auto &[amount,stage,hp,parts]:std::vector<std::tuple<float,int,float,int>>{{14,0,46,0},{15,1,30,1},{20,2,10,2}}) {
        auto s=fixture();const auto id=spawn(s);tick(s);damage(s,id,amount);
        check(near(s.findEnemy(id)->hp,192)&&s.findEnemy(id)->leper->pendingDamage.size()==1,"accepted damage waits for source-frame batch");
        tick(s);const auto *e=s.findEnemy(id);
        check(e&&e->monster==monsterId(310,0,stage)&&near(e->hp,hp*3.2f)&&flesh(s)==parts,"threshold loop and pre-subtraction Morph clamp match native ordering");
        check(s.stats.kills==0,"shedding is not a kill or parent replacement");
        if(parts) {
            check(e->leper->transition==9,"single nine-frame transition follows complete shed batch");
            for(const auto &child:s.enemies)if(child.monster==monsterId(310,1)) {
                check(near(child.hp,20.8f)&&!child.componentOwner&&!child.partner,"flesh has full source-stage health and independent lifetime");
                check(length(horizontal(child.velocity))>=14.99f&&length(horizontal(child.velocity))<=30.01f&&child.velocity.z<0,"shed flesh receives outward native5..10 speed impulse");
            }
            tick(s,9);check(s.findEnemy(id)->leper->transition==0,"transition finishes without reinitializing its chase timer");
        }
    }
    auto batch=fixture();const auto id=spawn(batch);tick(batch);damage(batch,id,10);damage(batch,id,10);tick(batch);
    check(batch.findEnemy(id)->monster.subtype==2&&near(batch.findEnemy(id)->hp,32)&&flesh(batch)==2&&batch.findEnemy(id)->leper->batches==1,"multiple hits coalesce before one form clamp");
    auto repeated=fixture();const auto ri=spawn(repeated);tick(repeated);damage(repeated,ri,10);tick(repeated);damage(repeated,ri,10);tick(repeated);
    check(repeated.findEnemy(ri)->monster.subtype==2&&near(repeated.findEnemy(ri)->hp,64),"separate source-frame hits retain different native HP history");
    auto stageOne=fixture();const auto oi=spawn(stageOne,1);tick(stageOne);damage(stageOne,oi,15);tick(stageOne);
    check(stageOne.findEnemy(oi)->monster.subtype==2&&near(stageOne.findEnemy(oi)->hp,48)&&flesh(stageOne)==1,"independently placed form1 uses its own45maxHP threshold");
    auto stun=fixture();const auto si=spawn(stun);tick(stun);stun.findEnemy(si)->state=EnemyState::Stunned;stun.findEnemy(si)->stateTime=2;
    damage(stun,si,15);tick(stun);check(stun.findEnemy(si)->monster.subtype==1&&stun.findEnemy(si)->state==EnemyState::Stunned,"stun neither blocks damage nor gets cancelled by shedding");
    std::cout<<"PASS batched thresholds, Morph-before-subtraction, full flesh impulses, transitions and stun\n";
}
void movement() {
    for(int stage=0;stage<4;++stage) {
        auto s=fixture();const auto id=spawn(s,stage);tick(s);auto *e=s.findEnemy(id);
        check(near(e->hp,float(60-stage*15)*3.2f)&&near(length(e->velocity),0),"all forms initialize with exact source HP and no first-frame movement");
        e->leper->chase=90;tick(s);
        check(near(s.findEnemy(id)->velocity.z,(stage==3?.9f:stage==2?.7f:.5f)*2*.9f*3),"form-specific chase force includes source additional .9 friction");
    }
    auto hurt=fixture();const auto hi=spawn(hurt);tick(hurt);hurt.findEnemy(hi)->leper->chase=90;damage(hurt,hi,1);tick(hurt);
    check(hurt.findEnemy(hi)->leper->chase==87,"one nativeHP shortens positive chase timer by ceil2damage after ordinary decrement");
    auto evade=fixture();const auto ei=spawn(evade);tick(evade);evade.player.position={0,.85f,10};evade.findEnemy(ei)->leper->evade.evadeChecks=3;tick(evade);
    check(evade.findEnemy(ei)->velocity.z<0,"nearby remembered threat produces evasive movement");
    auto final=fixture();const auto fi=spawn(final,3);tick(final);final.findEnemy(fi)->leper->chase=-70;tick(final,35);
    check(final.findEnemy(fi)->position.z>2&&final.findEnemy(fi)->leper->creepPatches>0,"last form pursues despite negative timer and leaves damaging creep");
    for(const auto &h:final.hazards)check(h.radius>=.4f&&h.radius<=1&&near(h.duration,1)&&near(h.damage,10),"last form creep has random small radius and native30tick active life");
    for(int stage:{0,1}) {
        auto s=fixture();s.godMode=false;const auto id=spawn(s,stage);s.player.position=s.findEnemy(id)->position;tick(s);
        check(stage==0?near(s.player.hp,100):s.player.hp<100,"only intact form has no contact damage");
    }
    auto a=fixture(),b=fixture();const auto ai=spawn(a,3),bi=spawn(b,3);tick(a,20);for(int n=0;n<40;++n)b.step({},1.f/60);
    check(distance(a.findEnemy(ai)->position,b.findEnemy(bi)->position)<.002f,"parent motion agrees at30/60Hz");
    std::cout<<"PASS evasion, pursuit force/timers, contact policy and last-form creep\n";
}
void mortality() {
    int morphs=0,deaths=0;std::set<int> delays;
    for(uint32_t seed=0;seed<32;++seed) {
        auto s=fixture(seed);const auto id=spawn(s);tick(s);damage(s,id,30);tick(s);
        check(flesh(s)==4,"large fatal hit releases three shed pieces plus one final flesh");
        const auto *e=s.findEnemy(id);
        if(e&&e->alive) {
            ++morphs;check(e->monster==monsterId(11)&&near(e->hp,32)&&e->headless&&e->headless->scarred&&s.stats.kills==0,"successful death branch preserves original ID as fullHP gray Gusher with no parent kill");
            check(e->headless->cooldown>=20&&e->headless->cooldown<=39,"Gusher receives native20..39delay");delays.insert(e->headless->cooldown);
        } else {++deaths;check(s.stats.kills==1,"ordinary parent death pays one kill");}
        for(const auto &child:s.enemies)if(child.monster==monsterId(310,1))check(!child.componentOwner&&!child.partner,"all flesh survives independent of parent mortality");
    }
    check(morphs>5&&deaths>5&&delays.size()>5,"seeded trials cover both50percent branches and Gusher timer range");
    auto cutoff=fixture();const auto ci=spawn(cutoff,3);tick(cutoff);damage(cutoff,ci,40);tick(cutoff);
    check(!cutoff.findEnemy(ci)&&flesh(cutoff)==1,"exact native-25HP cutoff suppresses Gusher but keeps final flesh");
    auto heavy=fixture();const auto hi=spawn(heavy);tick(heavy);damage(heavy,hi,1000);tick(heavy);
    check(!heavy.findEnemy(hi)&&flesh(heavy)==4,"extreme overkill cannot suppress required shedding or final flesh");
    auto debug=fixture();const auto di=spawn(debug);tick(debug);damage(debug,di,10);damage(debug,di,10000,true,true);tick(debug,3);
    check(debug.livingEnemies()==0&&debug.chains.empty(),"debug execution cancels queued parent damage and all death births");
    bool remainder=false;
    for(uint32_t seed=0;seed<32&&!remainder;++seed) {
        auto s=fixture(seed);const auto id=spawn(s);tick(s);damage(s,id,20);damage(s,id,20);tick(s);
        const auto *e=s.findEnemy(id);if(e&&e->monster==monsterId(11)) {remainder=true;check(near(e->hp,32),"unprocessed remainder of lethal parent batch does not damage its Gusher");}
    }
    check(remainder,"lethal-batch morph path reached");
    auto pressure=fixture();pressure.debugScenario=false;const auto pi=spawn(pressure);tick(pressure);pressure.limits.enemies=0;
    damage(pressure,pi,1000);tick(pressure,5);check(!pressure.roomClear&&pressure.livingEnemies()==0,"required flesh holds room completion under full capacity");
    pressure.limits.enemies=10;tick(pressure);check(flesh(pressure)==4&&!pressure.roomClear,"all retained flesh resumes after capacity recovery");
    auto deep=fixture();const auto gi=spawn(deep);deep.findEnemy(gi)->generation=4;tick(deep);damage(deep,gi,1000);tick(deep);
    check(flesh(deep)==4,"terminal flesh survives ancestry safety bound");
    std::cout<<"MORPH trials32 gusher="<<morphs<<" dead="<<deaths<<" delays="<<delays.size()<<'\n';
    std::cout<<"PASS mortality, overkill, same-entity Gusher, no duplicate rewards, remainder and retained flesh\n";
}
void lifecycleAndPlacement() {
    auto split=fixture();const auto si=spawn(split);tick(split);damage(split,si,15);
    split.step({},1.f/60);
    check(split.findEnemy(si)->monster.subtype==1&&near(split.findEnemy(si)->hp,144)&&
        split.findEnemy(si)->leper->applyingDamage.size()==1&&split.findEnemy(si)->position.z<0,
        "half source frame prepares Morph and knockback before subtracting HP");
    const auto halfPosition=split.findEnemy(si)->position;
    split.enterRoom(1);tick(split,3);split.enterRoom(0);
    check(split.findEnemy(si)->leper->applyingDamage.size()==1&&!split.chains.empty(),
        "prepared in-flight damage retains chain ownership across inactive room");
    damage(split,si,1);split.step({},1.f/60);
    check(near(split.findEnemy(si)->hp,96)&&split.findEnemy(si)->position.z<halfPosition.z&&
        split.findEnemy(si)->leper->pendingDamage.size()==1,
        "movement completes before subtraction and next half-frame hit waits for next source batch");
    tick(split);check(near(split.findEnemy(si)->hp,92.8f)&&split.chains.empty(),
        "later source batch applies exactly once and releases every chain");
    auto whole=fixture(),halves=fixture();const auto wi=spawn(whole),hi=spawn(halves);tick(whole);tick(halves);
    damage(whole,wi,1000);damage(halves,hi,1000);tick(whole);halves.step({},1.f/60);halves.step({},1.f/60);
    check(whole.enemies.size()==halves.enemies.size()&&whole.chains.empty()&&halves.chains.empty(),
        "fatal source frame has same births and no chain leaks at30/60Hz");
    for(size_t i=0;i<whole.enemies.size();++i) {
        std::cout<<"CADENCE_CHILD index="<<i<<" whole="<<whole.enemies[i].position.x<<','<<whole.enemies[i].position.z
            <<" split="<<halves.enemies[i].position.x<<','<<halves.enemies[i].position.z<<'\n';
        check(whole.enemies[i].monster==halves.enemies[i].monster&&
            distance(whole.enemies[i].position,halves.enemies[i].position)<.002f,
            "fatal frame preserves death-site translation and final flesh position at30/60Hz");
    }
    auto s=fixture();const auto id=spawn(s);tick(s);damage(s,id,1);s.enterRoom(1);tick(s,10);s.enterRoom(0);tick(s);
    check(near(s.findEnemy(id)->hp,188.8f)&&s.findEnemy(id)->leper->pendingDamage.empty()&&s.chains.empty(),"accepted damage and chain ownership survive inactive-room round trip");
    auto queue=fixture();const auto qi=spawn(queue);tick(queue);queue.limits.queuedEvents=1;damage(queue,qi,1);damage(queue,qi,1);tick(queue,4);
    check(near(queue.findEnemy(qi)->hp,185.6f)&&queue.findEnemy(qi)->leper->pendingDamage.empty()&&queue.chains.empty(),"full damage batch backpressures without losing accepted hits or leaking chains");
    auto creep=fixture();const auto ci=spawn(creep,3);creep.limits.hazards=0;tick(creep,20);check(creep.findEnemy(ci)->leper->pendingCreep.has_value(),"due creep retained under hazard pressure");
    damage(creep,ci,1000);tick(creep);check(creep.findEnemy(ci)&&creep.findEnemy(ci)->leper->pendingCreep.has_value(),"death cannot discard already reserved creep");
    creep.limits.hazards=10;tick(creep);check(!creep.hazards.empty(),"retained parent creep recovers after death");
    std::set<int> found;
    for(uint64_t seed=0;seed<128&&found.size()<4;++seed) {
        const ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&found.size()<4;++floor) {
            if(plan.profileOnFloor(floor).band!=3)continue;
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<run.finalRoom();++room) {
                std::array<int,4> count{};
                for(const auto &e:run.roomEnemies(room))if(e.monster.type==310&&e.monster.variant==0) {
                    ++count[size_t(e.monster.subtype)];
                    if(found.insert(e.monster.subtype).second)std::cout<<"NATURAL_LEPER stage="<<e.monster.subtype<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
                }
                for(int n:count)check(n<=1,"natural cap is one of each form per room");
            }
        }
    }
    check(found.size()==4,"all exact parent forms have actual seeded final-band residents");
    std::cout<<"PASS room lifecycle, damage/creep capacity and four natural parent forms\n";
}
void configuration() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-leper-parent-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}} cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream in(dir/"leper.mechanics");const std::string original{std::istreambuf_iterator<char>(in),{}};
    auto edit=[&](const std::string &from,const std::string &to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"external mutation fixture exists");text.replace(at,from.size(),to);std::ofstream(dir/"leper.mechanics")<<text;return MechanicsLibrary::load(dir);};
    const auto changed=edit("leper 310.0.3 .1 0.9","leper 310.0.3 .1 0.6");
    check(changed->fingerprint()!=defaultMechanics()->fingerprint()&&near(defaultMechanics()->leper(monsterId(310,0,3))->force,.9f),"reload leaves previous immutable mechanics snapshot intact");
    auto s=fixture(1866,changed);const auto id=spawn(s,3);tick(s,2);
    check(near(s.findEnemy(id)->velocity.z,.6f*2*.9f*3),"runtime consumes reloaded parent chase force");
    for(const auto &bad:std::vector<std::pair<std::string,std::string>>{
        {"leper 310.0.3 .1 0.9","leper 310.0.3 .1 0"},
        {"leper_creep 310.0.0 10 .4 1 10 30 40 .98\n",""},
        {"leper_evade 310.0.0 25 17 14 3 .8 .5 .9 1.079\n",""},
        {"310.1.0 11.0.0 2 15 30","310.1.0 10.0.0 2 15 30"},
        {"leper_creep 310.0.3 10 .4 1","leper_creep 310.0.3 10 2 1"},
        {"leper_creep 310.0.3 10 .4 1 10 30 40 .98","leper_creep 310.0.3 10 .4 1 10 30 40 .98\nleper_creep 310.0.3 10 .4 1 10 30 40 .98"}
    }) {bool rejected=false;try{edit(bad.first,bad.second);}catch(const std::exception &){rejected=true;}check(rejected,"invalid/incomplete/conflicting parent config rejected transactionally");}
    std::cout<<"PASS parent external reload, runtime force and six invalid contracts\n";
}
void startingKit() {
    for(int seed=0;seed<4;++seed) {
        auto s=fixture(seed);s.debugScenario=false;s.godMode=false;s.arena.profile.sourceStage=7;
        for(int stage=0;stage<4;++stage){const auto id=spawn(s,stage);s.findEnemy(id)->position.x=float(stage*4-6);}
        int frames=0;
        for(;frames<3600&&!s.dead&&!s.roomClear;++frames) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            Input input;
            if(target) {
                const auto delta=horizontal(sub(target->position,s.player.position));
                input.fire=true;input.aim=add(target->position,mul(horizontal(target->velocity),length(delta)/26));
                input.movement=length(delta)<7?mul(unit(delta),-1):length(delta)>12?unit(delta):Vector3{};
                input.dodge=length(delta)<2.5f;
            }
            s.step(input);
        }
        std::cout<<"LEPER_STARTING_KIT seed="<<seed<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<" kills="<<s.stats.kills<<" cleared="<<s.roomClear<<'\n';
        check(s.roomClear&&!s.dead&&s.stats.kills>=8,"starting revolver and dodge clear all four forms and required offspring without upgrades");
    }
}
}
int main(){std::cout<<std::unitbuf;try{shedding();movement();mortality();lifecycleAndPlacement();configuration();startingKit();std::cout<<"PASS Leper parent family\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
