#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
void near(float a,float b,const char *why){if(std::abs(a-b)>.002f){std::cerr<<a<<" != "<<b<<'\n';throw std::runtime_error(why);}}
Simulation fixture(){
    Simulation r(42,1,{},MissionTheme::Mine,false,false,WitnessAccount::None,0,ExpeditionPacing::Compact);
    r.arena=Arena{};auto &a=r.arena;a.bounds={{-30,-1,-30},{30,5,30}};a.rooms.resize(1);a.profile.sourceStage=1;
    a.floors={{{-30,-.4f,-30},{30,0,30}}};a.rooms[0].bounds=a.bounds;a.rooms[0].center={0,.85f,0};a.rooms[0].floors=a.floors;a.rebuildWalls();
    r.rooms.assign(1,{});r.room=0;r.debugScenario=true;r.enemies.clear();r.hazards.clear();r.projectiles.clear();r.stats={};r.player.position={0,.85f,0};r.applyCombatBalance(3.5f,1);return r;
}
void hit(Simulation &r,EntityId id,float damage){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;r.queueRoot(e);r.drainEvents();}
void primaryBodies(){
    const std::array<MonsterId,9> ids{monsterId(10),monsterId(10,1),monsterId(11),monsterId(12),monsterId(13),monsterId(14),monsterId(18),monsterId(85),monsterId(29)};
    const std::array<int,9> expected{3,3,3,3,1,3,2,2,3};
    for(size_t n=0;n<ids.size();++n){
        auto r=fixture();auto id=r.spawnMonster(ids[n],{0,.85f,-3});auto *e=r.findEnemy(id);check(e,"ordinary body spawned");const auto initial=e->hp;float previous=initial;int hits=0,steps=0;
        e->state=EnemyState::Stunned;e->stateTime=100;
        while(steps++<600&&e&&e->alive&&e->monster==ids[n]){
            Input in;in.fire=true;in.aim=e->position;r.step(in);e=r.findEnemy(id);
            if(!e||!e->alive||e->monster!=ids[n]||e->hp<previous-.001f)++hits;
            if(e)previous=e->hp;
        }
        check(hits==expected[n],"actual primary-projectile body-hit count agrees with source");
        check(steps<600,"body ends within firing/travel budget");
        std::cout<<"BODY "<<monsterIdText(ids[n])<<" hp="<<initial<<" damage="<<r.player.shotDamage<<" hits="<<hits<<" steps="<<steps<<'\n';
    }
}
void healthAndLifecycle(){
    const auto original=defaultMechanics(),half=original->withRegularHealthMultiplier(.5f),again=half->withRegularHealthMultiplier(.75f);int regulars=0;
    for(const auto &d:original->monsters()){
        const bool scoped=original->regularHealthMember(d.id);regulars+=scoped;
        for(int stage:{1,4,7,13})near(again->monsterHealth(d.id,stage),original->monsterHealth(d.id,stage)*(scoped?.75f:1),"regular roster scales once; boss/unscoped HP unchanged");
        if(const auto *p=original->stageHealth(d.id)){near(again->stageHealth(d.id)->base,p->base,"source base HP retained");near(again->stageHealth(d.id)->perStage,p->perStage,"source stage HP retained");}
    }
    check(regulars==155,"audited regular health scope retained");near(original->regularHealthMultiplier(),1,"authored snapshot unchanged");
    auto r=fixture();const auto g=r.spawnMonster(monsterId(10,1),{0,.85f,-4});check(r.makeChampion(g,0),"champion creation");
    auto *e=r.findEnemy(g);hit(r,g,8);const float hp=e->hp,max=e->maxHp;const auto state=e->state;const auto rng=r.combatRng.state;
    auto resident=*e;resident.id=100000;r.rooms[0].residents.push_back(resident);
    auto black=r.spawnMonster(monsterId(278),{6,.85f,0});r.findEnemy(black)->blackGlobin->lastEmissionHP=60;const auto stats=r.stats.kills;
    r.applyCombatBalance(3.5f,.5f);e=r.findEnemy(g);near(e->hp,hp*.5f,"live injury proportion retained");near(e->maxHp,max*.5f,"champion max scales once");near(r.rooms[0].residents[0].hp,hp*.5f,"stored-room residents scaled");near(r.findEnemy(black)->blackGlobin->lastEmissionHP,30,"HP-dependent brood checkpoint scaled");
    check(e->state==state&&r.combatRng.state==rng&&r.stats.kills==stats,"HP edit changes no phase/RNG/reward");
    const auto baby=r.spawnMonster(monsterId(85),{8,.85f,0});near(r.findEnemy(baby)->maxHp,10.4f,"new spawn uses edited HP");
    r.applyCombatBalance(3.5f,1);near(r.findEnemy(g)->hp,hp,"restoring HP is proportional, not heal-to-full");
    int gusher=0,pacer=0;
    for(int seed=1;seed<=128;++seed){
        auto a=fixture(),b=fixture();a.combatRng.state=b.combatRng.state=seed;b.applyCombatBalance(3.5f,.5f);
        const auto x=a.spawnMonster(monsterId(10,1),{0,.85f,-4}),y=b.spawnMonster(monsterId(10,1),{0,.85f,-4});
        hit(a,x,40);hit(b,y,20);auto *one=a.findEnemy(x),*two=b.findEnemy(y);
        check(one->alive==two->alive&&one->monster==two->monster,"proportional overkill preserves Gaper morph outcome");
        if(one->alive){near(two->maxHp,one->maxHp*.5f,"Gaper successor HP scales exactly once");gusher+=one->monster==monsterId(11);pacer+=one->monster==monsterId(11,1);}
    }
    check(gusher&&pacer,"both Gaper successor paths witnessed");
    auto a=fixture(),b=fixture();b.applyCombatBalance(3.5f,.5f);
    const auto x=a.spawnMonster(monsterId(16),{0,.85f,-4}),y=b.spawnMonster(monsterId(16),{0,.85f,-4});
    hit(a,x,a.findEnemy(x)->hp+8);hit(b,y,b.findEnemy(y)->hp+4);a.step({});b.step({});check(a.enemies.size()==b.enemies.size()&&a.enemies.size()>1,"offspring spawned");
    for(size_t i=0;i<a.enemies.size();++i){check(a.enemies[i].monster==b.enemies[i].monster,"offspring identity retained");near(b.enemies[i].maxHp,a.enemies[i].maxHp*.5f,"offspring HP scales once");}
    std::cout<<"PASS health profiles="<<regulars<<" stages=4 live fractions/champions/residents/brood/morphs/offspring; Gusher="<<gusher<<" Pacer="<<pacer<<'\n';
}
void shotsAndHurt(){
    auto r=fixture();Input input;input.fire=true;input.aim={0,.85f,-10};r.step(input);check(!r.projectiles.empty(),"ordinary shot emitted");
    const auto born=r.projectiles[0];const auto wait=r.player.fireCooldown;r.applyCombatBalance(7,.75f);
    near(r.projectiles[0].damage,born.damage,"existing shot damage retained");near(r.player.fireCooldown,wait,"current firing wait retained");
    near(primaryPlayerAttack(r,r.player.shotDamage,false).damage,22.4f,"new primary uses independent canonical damage");
    r.grant(ItemId::Rail);const auto before=primaryPlayerAttack(r,r.player.shotDamage,false);r.applyCombatBalance(3.5f,.75f);const auto after=primaryPlayerAttack(r,r.player.shotDamage,false);
    near(after.damage,r.content->resolve(r.items,11.2f,26,false)[BuildStat::Damage],"existing upgrades resolve once in internal units");near(after.speed,before.speed,"Damage does not alter shooting speed");near(after.maxDistance,before.maxDistance,"Damage does not alter range");
    const auto revision=r.content;const auto hp=r.player.hp;bool rejected=false;try{r.applyCombatBalance(9,0);}catch(const std::exception&){rejected=true;}
    check(rejected&&r.content==revision&&r.player.attributes.damage==3.5f&&r.player.hp==hp,"invalid HP/damage edit atomic");
    for(auto kind:{monsterId(10,1),monsterId(85)}) {
        auto contact=fixture();contact.gaperMovementMultiplier=1;contact.spiderMovementMultiplier=1;
        contact.spawnMonster(kind,{.3f,.85f,0});
        for(int n=0;n<10&&contact.player.hp==6;++n)contact.step({});
        near(contact.player.hp,5,"selected ordinary enemy contact removes one half heart");
        for(int n=0;n<20;++n)contact.step({});near(contact.player.hp,5,"overlapping body cannot bypass hurt immunity");
    }
    auto hurt=fixture();check(hurt.takeHeartDamage(1)&&hurt.player.hp==5&&hurt.player.hurt==1,"ordinary half-heart and one-second immunity");
    for(int n=0;n<59;++n)hurt.step({});check(!hurt.takeHeartDamage(1),"immunity lasts through prior tick");hurt.step({});check(hurt.takeHeartDamage(1)&&hurt.player.hp==4,"eligible hit after expiry");
    hurt.player.hurt=0;Input dodge;dodge.dodge=true;dodge.movement={1,0,0};const auto start=hurt.player.position;hurt.step(dodge);
    check(!hurt.takeHeartDamage(1)&&distance(start,hurt.player.position)>4.8f*Tick,"universal dodge immunity and boost retained");
    std::cout<<"PASS birth damage/current wait/items/independent shooting/atomic rejection/half hearts/hurt window/dodge\n";
}
}
int main(){try{primaryBodies();healthAndLifecycle();shotsAndHurt();std::cout<<"PASS D07 combat balance\n";return 0;}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
