#include "combat/Simulation.hpp"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/
        ("deathward-replacements-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(root);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(root);}
    void rules(const std::string &rows){std::ofstream(root/"replacements.mechanics")<<"DEATHWARD_MECHANICS 1\n"<<rows;}
    void pool(MonsterId source){
        // This test samples one source's substitution probability. Encounter
        // rows also live in family files; remove all of them from the fixture.
        for(const auto &f:std::filesystem::directory_iterator(root))if(f.path().extension()==".mechanics") {
            std::ifstream in(f.path());std::ostringstream kept;std::string line;
            while(std::getline(in,line)){std::istringstream row(line);std::string command;row>>command;if(command!="encounter")kept<<line<<'\n';}
            in.close();std::ofstream(f.path())<<kept.str();
        }
        std::ofstream(root/"encounters.mechanics")<<"DEATHWARD_MECHANICS 1\nencounter 0 3 any basic 11.1.0 1 1 0\nencounter 0 3 any specialist "<<monsterIdText(source)<<" 1 3 1\n";
    }
    auto load(){return MechanicsLibrary::load(root);}
};
Simulation composition(std::shared_ptr<const MechanicsLibrary> content,int band=0,FloorVariant variant=FloorVariant::Standard) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(content));
    s.arena=Arena{};s.arena.profile.band=band;s.arena.profile.variant=variant;
    s.arena.profile.patterns={1,0,0,0};s.arena.profile.maxThreat=12;s.arena.profile.areaPerThreat=95;
    s.arena.rooms.resize(10000);
    for(auto &room:s.arena.rooms){room.kind=RoomKind::Combat;room.floorArea=800;room.bounds={{-20,0,-20},{20,3,20}};}
    return s;
}
void sourceOdds() {
    for(auto source:{monsterId(15),monsterId(15,1),monsterId(29),monsterId(23),monsterId(10),monsterId(10,1)}) {
        const bool burning=source.type==29||source.type==10;
        Pack p;p.pool(source);auto s=composition(p.load(),burning?0:1,
            burning?FloorVariant::Scorched:source.type==23?FloorVariant::Flooded:FloorVariant::Standard);
        const auto target=source.type==10?monsterId(10,2):source.type==29?monsterId(54):source.type==23?monsterId(23,1):monsterId(15,2);int replaced=0;
        for(int room=0;room<10000;++room) {
            const auto plan=s.floorEncounter(room);
            check(plan.originalMonsters.front()==source&&plan.monsters.size()==plan.originalMonsters.size(),"replacement preserves selected source and actor slots");
            check(plan.spent<=plan.budget&&plan.monsters.size()>=size_t(plan.specialists+2),"replacement reserves threat without losing basic support");
            check(plan.monsters.front()==source||plan.monsters.front()==target,"only the applicable target is substituted");
            replaced+=plan.monsters.front()==target;
        }
        check(burning?(replaced>5700&&replaced<6300):source.type==23?(replaced>4700&&replaced<5300):(replaced>65&&replaced<140),"seeded replacement rate is consistent with configured source chance");
        auto plan=s.floorEncounter(123);for(int i=0;i<30;++i){s.combatRng.next();s.rewardRng.next();}
        s.arena.rooms[123].depth=99;
        check(plan.monsters==s.floorEncounter(123).monsters,"combat/loot RNG and graph depth do not reroll replacement");
        std::cout<<"REPLACEMENT_ODDS source="<<monsterIdText(source)<<" replaced="<<replaced<<" samples=10000\n";
        if(source.type==23) {
            s.arena.profile.variant=FloorVariant::Standard;
            for(int i=0;i<1000;++i)check(s.floorEncounter(i).monsters.front()==source,"dry Quarry never replaces ordinary Charger");
            s.arena.profile.variant=FloorVariant::Flooded;s.arena.profile.band=2;
            for(int i=0;i<1000;++i)check(s.floorEncounter(i).monsters.front()==source,"Necropolis direct placement does not gain Flooded Caves replacement");
        }
        if(burning) {
            s.arena.profile.variant=FloorVariant::Standard;
            for(int i=0;i<1000;++i)check(s.floorEncounter(i).monsters.front()==source,"ordinary Washes never apply Burning Basement replacement");
            s.arena.profile.variant=FloorVariant::Scorched;s.arena.profile.band=1;
            for(int i=0;i<1000;++i)check(s.floorEncounter(i).monsters.front()==source,"later bands cannot inherit opening Burning Basement rule");
        }
    }
}
void snapshotsAndOneShot() {
    Pack p;p.pool(monsterId(15));p.rules("replace_monster 15.0.0 15.2.0 0 3 any 0 1\n");
    auto before=p.load();auto a=composition(before,1);
    p.rules("replace_monster 15.0.0 15.2.0 0 3 any 10000 1\nreplace_monster 15.2.0 15.3.0 0 3 any 10000 2\n");
    auto after=p.load();auto b=composition(after,1);
    for(int i=0;i<100;++i) {
        const auto left=a.floorEncounter(i),right=b.floorEncounter(i);
        check(left.originalMonsters==right.originalMonsters&&left.spent==right.spent,"chance-only edits preserve base composition and conservative reserved budget");
        check(left.monsters.front()==monsterId(15)&&right.monsters.front()==monsterId(15,2),"apply once to original identity; no recursive target replacement and no old-run mutation");
    }
    check(before->fingerprint()!=after->fingerprint(),"replacement rules participate in content snapshot hash");
    FloorProfile inactive;check(!after->replacement(monsterId(15),inactive),"tutorial/Classic inactive profile has no replacement policy");
    b.enemies.clear();const auto explicitId=b.spawnMonster(monsterId(15),{0,.85f,0});
    check(b.findEnemy(explicitId)->monster==monsterId(15),"explicit/debug/offspring spawning does not run natural room substitutions");
    std::cout<<"REPLACEMENT_SNAPSHOT one_shot=1 budget_reserved=1 immutable=1 explicit_spawn=1\n";
}
void floorContextAndDressing() {
    const auto content=defaultMechanics();FloorProfile p;p.band=0;
    int scorched=0,flooded=0;
    for(uint64_t seed=0;seed<600;++seed) {
        const auto profile=content->configureFloor(p,seed);scorched+=profile.variant==FloorVariant::Scorched;
        check(profile.variant==content->configureFloor(p,seed).variant,"floor variant is seed deterministic");
        p.band=1;const auto quarry=content->configureFloor(p,seed);flooded+=quarry.variant==FloorVariant::Flooded;
        check(quarry.variant==FloorVariant::Standard||quarry.variant==FloorVariant::Flooded,"Quarry has only dry/flooded contexts");
        for(int band=2;band<4;++band){p.band=band;const auto variant=content->configureFloor(p,seed).variant;check(variant==FloorVariant::Standard||variant==(band==2?FloorVariant::Dank:FloorVariant::Scarred),"Works/Storm only select their reviewed contexts");}p.band=0;
    }
    check(scorched>160&&scorched<240&&flooded>160&&flooded<240,"local 2:1 floor weights produce both contexts");
    Pack pack;
    // Isolate floor surface context from a boss with an authored rail footprint.
    // Hornfel is dry-only; changing to Flooded legitimately selects a different
    // boss arena. Dedicated footprint/entrance routing is tested by hornfel_boss.
    {const auto file=pack.root/"hornfel.mechanics";std::ifstream in(file);std::string text((std::istreambuf_iterator<char>(in)),{});
        const std::string row="boss_pool 1 906.0.0 normal 2 standard";const auto at=text.find(row);check(at!=std::string::npos,"rail boss isolation fixture");
        text.replace(at,row.size(),"boss_pool 1 906.0.0 normal 0 standard");std::ofstream(file)<<text;}
    pack.rules("floor_variant 0 standard 1\n");auto dry=pack.load();
    pack.rules("floor_variant 0 scorched 1\n");auto burned=pack.load();
    Simulation a(42,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,dry);
    Simulation b(42,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,burned);
    check(a.arena.scorchPatches.empty()&&!b.arena.scorchPatches.empty(),"Scorched context has visible local deposits, not only a hidden rule flag");
    check(a.arena.roomCount()==b.arena.roomCount()&&a.arena.passages.size()==b.arena.passages.size()&&
        a.arena.canyon->heights==b.arena.canyon->heights,"floor context does not reroll geometry or connections");
    for(int i=0;i<a.arena.roomCount();++i)check(distance(a.arena.rooms[size_t(i)].center,b.arena.rooms[size_t(i)].center)<.001f&&
        a.arena.rooms[size_t(i)].kind==b.arena.rooms[size_t(i)].kind,"story/room placement remains unchanged by variant selection");
    for(const auto &patch:b.arena.scorchPatches) {
        check(std::abs(b.arena.canyon->height(patch.position.x,patch.position.z))<.021f,"scorch center remains on flat terrain");
        check(!b.arena.canyon->waterBlocked(patch.position),"scorch does not stain deep water");
    }
    pack.rules("floor_variant 1 flooded 1\n");auto wet=pack.load();
    ExpeditionPlan plan(42);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
    Simulation c(42,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,dry);
    Simulation d(42,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,wet);
    check(c.arena.canyon->heights==d.arena.canyon->heights&&c.arena.roomCount()==d.arena.roomCount(),"flooded context preserves canyon geometry");
    check(c.arena.dampPatches.empty()&&!d.arena.dampPatches.empty()&&d.arena.profile.name=="Flooded Quarry","wet sediment and name expose flooded context");
    for(const auto &r:d.arena.rooms)check(r.flooded==(r.kind==RoomKind::Combat&&r.story==StoryRoom::None),"flooded combat context does not alter story/service rooms");
    for(const auto &patch:d.arena.dampPatches)check(std::abs(d.arena.canyon->height(patch.position.x,patch.position.z))<.021f&&!d.arena.canyon->waterBlocked(patch.position),"damp sediment stays on flat walkable floor");
    std::cout<<"FLOODED_QUARRY samples=600 flooded="<<flooded<<" patches="<<d.arena.dampPatches.size()<<" geometry_unchanged=1\n";
    Simulation tutorial(42,1,{},MissionTheme::Canyon,true,true,WitnessAccount::None,0,ExpeditionPacing::Compact,burned);
    Simulation mine(42,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,burned);
    check(!tutorial.arena.profile.active()&&tutorial.arena.scorchPatches.empty()&&!mine.arena.profile.active()&&mine.arena.scorchPatches.empty(),"tutorial and Mine do not inherit variant generation");
    std::cout<<"FLOOR_VARIANTS scorched="<<scorched<<" samples=600 patches="<<b.arena.scorchPatches.size()<<" geometry_unchanged=1\n";
}
void realResidents() {
    Pack p;p.pool(monsterId(15));p.rules("replace_monster 15.0.0 15.2.0 0 3 any 10000 1\n");
    ExpeditionPlan plan(1866);Simulation s(1866,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,
        plan.floorCount-1,ExpeditionPacing::Compact,p.load());
    int selected=-1,count=0;
    for(int room=0;room<s.arena.roomCount();++room) {
        const auto plan=s.floorEncounter(room);
        for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(15,2)) {
            ++count;selected=room;check(e.hp==96&&!s.arena.blocked(e.position,e.radius),"actual replacement resident has target stats and safe placement");
            check(std::find(plan.originalMonsters.begin(),plan.originalMonsters.end(),monsterId(15))!=plan.originalMonsters.end(),"actual replacement retains an authored source in the room plan");
        }
    }
    check(selected>=0&&count>0,"actual generation realizes conditional replacement plans");
    s.jumpDebug(selected);s.godMode=true;
    const auto selectedActor=std::find_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.monster==monsterId(15,2);})->id;
    const auto hp=s.findEnemy(selectedActor)->hp;s.enterRoom(0);s.enterRoom(selected);
    check(s.findEnemy(selectedActor)&&s.findEnemy(selectedActor)->monster==monsterId(15,2)&&s.findEnemy(selectedActor)->hp==hp,"room re-entry does not reroll or replace an existing resident again");
    std::cout<<"REPLACEMENT_RESIDENTS iblob="<<count<<" safe_placement=1 target_stats=1 reentry=1\n";
}
}
int main(){try{sourceOdds();snapshotsAndOneShot();floorContextAndDressing();realResidents();std::cout<<"PASS conditional replacements and floor variants\n";}
catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
