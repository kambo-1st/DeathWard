#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool v,const char *why){if(!v)throw std::runtime_error(why);}
bool near(float a,float b){return std::abs(a-b)<.002f;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("deathward-health-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(root);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(root);}
    auto load(float multiplier){
        const auto file=root/"regular_enemy_health.mechanics";std::ifstream in(file);std::string data((std::istreambuf_iterator<char>(in)),{});in.close();
        const auto pos=data.find("regular_health_multiplier "),end=data.find('\n',pos);check(pos!=std::string::npos,"balance line present");
        data.replace(pos,end-pos,"regular_health_multiplier "+std::to_string(multiplier));std::ofstream(file)<<data;
        return MechanicsLibrary::load(root);
    }
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content){
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(content));
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={20,.85f,20};return s;
}
void hit(Simulation &s,EntityId id,float damage){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;s.queueRoot(e);s.drainEvents();}
void allProfiles(){
    const auto original=defaultMechanics();Pack p;const auto half=p.load(.5f);const auto reduced=p.load(.75f);int count=0;
    check(near(original->regularHealthMultiplier(),1)&&near(half->regularHealthMultiplier(),.5f),"separate immutable snapshots retain multipliers");
    for(const auto &body:original->monsters()){
        if(!original->regularHealthMember(body.id)){check(near(body.hp,half->monster(body.id)->hp),"unscoped boss/hazard/companion HP unchanged");continue;}
        ++count;const auto *source=original->stageHealth(body.id),*scaled=half->stageHealth(body.id);
        check(source&&scaled&&near(source->base,scaled->base)&&near(source->perStage,scaled->perStage),"source base and growth remain unchanged");
        for(int stage=1;stage<=13;++stage){check(near(half->monsterHealth(body.id,stage),original->monsterHealth(body.id,stage)*.5f),"all155stage curves scale once");check(near(reduced->monsterHealth(body.id,stage),original->monsterHealth(body.id,stage)*.75f),"all155stage curves support25percent reduction");}
        check(near(half->monster(body.id)->hp,body.hp*.5f),"runtime fallback scales once with stage curve");
    }
    check(count==155,"all reviewed regular identities have explicit health scope");
    auto a=fixture(original),b=fixture(half);
    check(near(a.player.maxHp,100)&&near(b.player.maxHp,100)&&near(a.player.shotDamage,24)&&near(b.player.shotDamage,24),"player100HP24damage unchanged");
    for(auto id:{monsterId(10),monsterId(23),monsterId(822),monsterId(24)}){
        auto first=a.spawnMonster(id,{0,.85f,0}),second=b.spawnMonster(id,{0,.85f,0});
        check(near(b.findEnemy(second)->hp,a.findEnemy(first)->hp*.5f),"real spawn scales once");
    }
    a.enemies.clear();b.enemies.clear();auto first=a.spawnMonster(monsterId(23),{0,.85f,0}),second=b.spawnMonster(monsterId(23),{0,.85f,0});
    check(a.makeChampion(first,0)&&b.makeChampion(second,0),"champion conversion available");
    check(near(b.findEnemy(second)->maxHp,a.findEnemy(first)->maxHp*.5f),"champion multiplies balanced HP once");
    auto hp=b.findEnemy(second)->hp;hit(b,second,24);check(near(b.findEnemy(second)->hp,hp-24),"player damage is not rescaled with enemy HP");
    check(near(original->stageHealth(monsterId(817,1))->base,14),"installed Mullighoul14HP wins wiki conflict");
    check(original->monsterHealth(monsterId(22,2),4)>original->monsterHealth(monsterId(22,2),1)&&original->monsterHealth(monsterId(872),4)>original->monsterHealth(monsterId(872),1),"Holy Mulligan and Cloggy now retain source stage growth");
    std::cout<<"REGULAR_HEALTH identities=155 stages=13 source_preserved=1 spawn=1 champion=1 player_unchanged=1 stage_growth=1\n";
}
void lifecycle(){
    Pack p;auto base=defaultMechanics(),half=p.load(.5f);auto a=fixture(base),b=fixture(half);
    auto first=a.spawnMonster(monsterId(24),{0,.85f,0}),second=b.spawnMonster(monsterId(24),{0,.85f,0});
    for(int n=0;n<12;++n){
        a.findEnemy(first)->state=b.findEnemy(second)->state=EnemyState::Ready;
        hit(a,first,10000);hit(b,second,10000);
        check(a.findEnemy(first)->alive&&b.findEnemy(second)->alive,"Globin collapse preserved");
        check(near(b.findEnemy(second)->maxHp,a.findEnemy(first)->maxHp*.5f)&&near(b.findEnemy(second)->hp,a.findEnemy(first)->hp*.5f),"regrowth and minimum floor scale consistently");
    }
    check(near(a.findEnemy(first)->maxHp,12)&&near(b.findEnemy(second)->maxHp,6),"minimum HP floor scales instead of undoing reduction");
    a=fixture(base);b=fixture(half);first=a.spawnMonster(monsterId(30),{0,.85f,0});second=b.spawnMonster(monsterId(30),{0,.85f,0});
    check(near(b.findEnemy(second)->hp,a.findEnemy(first)->hp*.5f),"Boil initial HP follows multiplier");
    for(int n=0;n<50;++n){a.step({});b.step({});}
    check(near(b.findEnemy(second)->hp,a.findEnemy(first)->hp*.5f),"Boil growth/healing follows multiplier");
    a=fixture(base);b=fixture(half);first=a.spawnMonster(monsterId(16),{0,.85f,0});second=b.spawnMonster(monsterId(16),{0,.85f,0});
    hit(a,first,a.findEnemy(first)->hp+8);hit(b,second,b.findEnemy(second)->hp+4);a.step({});b.step({});
    check(a.enemies.size()==4&&b.enemies.size()==4,"proportional overkill preserves Mulligan offspring");
    for(size_t n=0;n<a.enemies.size();++n)check(a.enemies[n].monster==b.enemies[n].monster&&near(b.enemies[n].hp,a.enemies[n].hp*.5f),"offspring HP is not double-scaled");
    std::cout<<"REGULAR_HEALTH_LIFECYCLE regrowth_floor=1 boil_growth=1 overkill=1 offspring_once=1\n";
}
void validation(){Pack p;for(float bad:{0.f,-1.f,4.1f}){bool rejected=false;try{p.load(bad);}catch(const std::exception&){rejected=true;}check(rejected,"invalid health multiplier rejected");}}
}
int main(){try{allProfiles();lifecycle();validation();std::cout<<"PASS regular health balance\n";return 0;}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
