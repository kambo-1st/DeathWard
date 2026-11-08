#include "../tools/damage_health_calibration.hpp"
#include <chrono>
#include <iostream>

namespace {
using namespace dw;
void check(bool ok,const char *why){damage_review::require(ok,why);}
void near(float a,float b,const char *why){check(std::abs(a-b)<.002f,why);}
struct Temporary {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-damage-calibration-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Temporary(){std::filesystem::create_directories(path);}
    ~Temporary(){std::error_code error;std::filesystem::remove_all(path,error);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> library){
    Simulation run(42,1,{},MissionTheme::Mine,false,false,WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(library));
    run.arena=Arena{};auto &a=run.arena;a.bounds={{-30,-1,-30},{30,5,30}};a.rooms.resize(1);a.profile.sourceStage=1;
    a.floors={{{-30,-.4f,-30},{30,0,30}}};a.boundaryWalls={};a.rooms[0].bounds=a.bounds;a.rooms[0].center={0,.85f,0};a.rooms[0].floors=a.floors;a.rebuildWalls();
    run.rooms.assign(1,{});run.room=0;run.debugScenario=true;run.enemies.clear();run.hazards.clear();run.projectiles.clear();run.stats={};run.player.position={-8,.85f,0};return run;
}
void hit(Simulation &run,EntityId id,float damage){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;run.queueRoot(e);run.drainEvents();}
std::string read(const std::filesystem::path &file){std::ifstream in(file);return {(std::istreambuf_iterator<char>(in)),{}};}
}
int main(){
    try {
        Temporary temporary;auto original=defaultMechanics();std::map<std::filesystem::path,std::string> before;
        for(const auto &f:std::filesystem::directory_iterator(original->directory()))if(f.path().extension()==".mechanics")before.emplace(f.path(),read(f.path()));
        auto source=damage_review::makeSourcePack(*original,temporary.path/"source");
        for(const auto &[path,text]:before)check(read(path)==text,"production mechanics are byte-for-byte unchanged");
        near(original->regularHealthMultiplier(),1,"production health control remains one");near(source->regularHealthMultiplier(),1,"review health control remains one");
        check(read(original->directory()/"regular_enemy_health.mechanics")==read(source->directory()/"regular_enemy_health.mechanics"),"health control file is not repurposed as a unit conversion");

        // Independent rows extracted from the pinned installed XML, not produced
        // by the C++ profile patcher. Includes the necessary Pacer dependency.
        const auto reference=original->directory().parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/damage-health-calibration/source-health.csv";
        std::ifstream input(reference);check(bool(input),"independent XML-derived HP fixture available");std::string row;std::getline(input,row);int rows=0;
        while(std::getline(input,row)){
            std::replace(row.begin(),row.end(),',',' ');std::istringstream in(row);std::string identity,role;float base,growth;check(bool(in>>identity>>base>>growth>>role),"parse independent source record");
            const auto id=parseMonsterId(identity);const auto *old=original->stageHealth(id),*now=source->stageHealth(id);check(old&&now,"source profiles exist");
            near(old->base,base,"existing base HP agrees with native XML");near(now->base,base,"source base HP preserved");near(now->perStage,growth,"source stage HP preserved");near(now->scale,1,"source unit conversion is exactly one");
            near(source->monster(id)->hp,base+growth,"fallback agrees with source-stage-one HP");
            for(int stage=1;stage<=13;++stage)near(source->monsterHealth(id,stage),original->monsterHealth(id,stage)/old->scale,"source stage calculation preserved while conversion changes");
            ++rows;
        }
        check(rows==10,"nine selected bodies plus Pacer morph dependency checked");
        for(const auto &body:original->monsters())if(!damage_review::healthMember(body.id)){
            near(source->monster(body.id)->hp,body.hp,"unselected actor/boss/hazard fallback HP unchanged");
            for(int stage:{1,4,13})near(source->monsterHealth(body.id,stage),original->monsterHealth(body.id,stage),"unselected stage health unchanged");
        }
        int bodyCases=0;
        for(bool candidate:{false,true})for(const auto &body:damage_review::Bodies){
            auto run=fixture(candidate?source:original);run.player.shotDamage=candidate?run.player.attributes.damage:RevolverDamage;
            auto id=run.spawnMonster(body.id,{0,.85f,0});check(id!=0,"spawn scoped body through shared HP calculation");
            const float starting=run.findEnemy(id)->hp;const int expected=damage_review::bodyHits(starting,run.player.shotDamage);int hits=0;
            for(;hits<10;++hits){auto *e=run.findEnemy(id);if(!e||!e->alive||e->monster!=body.id)break;hit(run,id,run.player.shotDamage);}
            check(hits==expected,"actual damage pipeline hits-to-body-end matches unit convention");
            if(candidate)near(starting,body.sourceHp,"selected real spawn uses native HP");
            near(run.player.hp,6,"calibration does not change player health");++bodyCases;
        }
        // Compare equivalent source-unit overkill, not the two different base
        // loadouts: RNG outcomes and child identities must survive conversion.
        int morphs=0,pacers=0;
        for(auto id:{monsterId(10),monsterId(10,1)})for(int seed=0;seed<32;++seed){
            auto a=fixture(original),b=fixture(source);auto x=a.spawnMonster(id,{0,.85f,0}),y=b.spawnMonster(id,{0,.85f,0});
            a.combatRng=Random(seed);b.combatRng=Random(seed);hit(a,x,10.5f*3.2f);hit(b,y,10.5f);
            const auto *old=a.findEnemy(x),*now=b.findEnemy(y);const bool ma=old&&old->alive&&old->monster!=id,mb=now&&now->alive&&now->monster!=id;
            check(ma==mb,"HP conversion preserves eligible lethal-morph roll");
            if(mb){check(old->monster==now->monster,"unit conversion preserves morph identity");near(now->maxHp,10,"Gusher/Pacer morph HP uses source conversion once");near(old->maxHp,now->maxHp*3.2f,"offspring unit scaling remains consistent");++morphs;pacers+=now->monster==monsterId(11,1);}
            a=fixture(original);b=fixture(source);x=a.spawnMonster(id,{0,.85f,0});y=b.spawnMonster(id,{0,.85f,0});
            hit(a,x,35*3.2f);hit(b,y,35);
            check((!a.findEnemy(x)||!a.findEnemy(x)->alive)&&(!b.findEnemy(y)||!b.findEnemy(y)->alive),"strict source overkill threshold remains identical in shared units");
        }
        check(morphs>0&&pacers>0,"both morph path and Pacer dependency have real witnesses");
        auto a=fixture(original),b=fixture(source);auto x=a.spawnMonster(monsterId(10),{0,.85f,0}),y=b.spawnMonster(monsterId(10),{0,.85f,0});
        check(a.makeChampion(x,0)&&b.makeChampion(y,0),"champion health path available");near(a.findEnemy(x)->hp,b.findEnemy(y)->hp*3.2f,"champion shares source-unit HP conversion");
        near(Simulation(42,1,{}).player.shotDamage,24,"normal expedition starting damage remains unchanged before human selection");
        std::cout<<"PASS "<<bodyCases<<" body-hit cases; pinned XML source rows; shared stage/offspring/champion/overkill units; unselected HP and production files unchanged; morph witnesses="<<morphs<<" Pacer="<<pacers<<'\n';
        return 0;
    }catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}
}
