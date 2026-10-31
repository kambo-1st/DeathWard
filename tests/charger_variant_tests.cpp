#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.001f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.rebuildWalls();for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    s.rooms.resize(s.arena.roomCount());s.player.position={0,.85f,8};return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void kill(Simulation &s,EntityId id,bool execute=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.execution=execute;s.queueRoot(e);s.drainEvents();}
EntityId spawn(Simulation &s,MonsterId id){const auto actor=s.spawnMonster(id,{0,.85f,0});s.findEnemy(actor)->cooldown=0;return actor;}
void drowned() {
    auto s=fixture();auto id=spawn(s,monsterId(23,1));check(near(s.findEnemy(id)->hp,70.4f),"Drowned HP is 10 percent over normal Charger");
    ticks(s,1);check(s.findEnemy(id)->state==EnemyState::Charging&&s.findEnemy(id)->velocity.z>12,"Drowned inherits immediate cardinal dash");
    kill(s,id);check(s.projectiles.size()==4&&s.stats.kills==1,"ordinary death emits exactly four real shots and one reward");
    for(const auto &p:s.projectiles)check(p.hostile&&near(std::abs(p.velocity.x),std::abs(p.velocity.z)),"Drowned death shots have fixed diagonal axes");
    s.debugScenario=false;s.rooms[size_t(s.room)].cleared=false;ticks(s,1);
    check(s.roomClear&&s.projectiles.size()==4&&s.stats.rooms==1,"last-enemy volley survives room completion without keeping doors sealed");
    s=fixture();id=spawn(s,monsterId(23,1));kill(s,id,true);check(s.projectiles.empty(),"execution cleanup does not create death attacks");
    std::cout<<"DROWNED hp=70.4 immediate=1 diagonal_death_shots=4 execution_cleanup=1\n";
}
void dank() {
    auto s=fixture();s.player.position={0,.85f,2};
    s.arena.obstacles.push_back({{-10,-1,4},{10,5,5}});s.arena.rebuildWalls();auto id=spawn(s,monsterId(23,2));
    ticks(s,1);s.player.position={8,.85f,8}; // Let the committed dash pass the acquisition point.
    bool bounced=false;
    for(int n=0;n<100;++n){ticks(s,1);const auto *e=s.findEnemy(id);bounced|=e->state==EnemyState::Charging&&e->velocity.z<-15;
        check(!s.arena.blocked(e->position,e->radius),"swept fast reflection never crosses solid cover");}
    check(bounced,"Dank reflects from wall while preserving active dash");
    while(s.findEnemy(id)->state==EnemyState::Charging)ticks(s,1);
    auto *e=s.findEnemy(id);const auto stopped=e->position;check(e->chargeRecovery>0,"Dank has a stationary recovery");
    check(!s.hazards.empty()&&s.hazards.size()<=16,"bounded tar trail created during dash");
    ticks(s,20);check(distance(stopped,s.findEnemy(id)->position)<.0001f,"recovery does not wander or reacquire early");
    auto patch=s.hazards.front();s.player.position=patch.position;s.godMode=false;s.findEnemy(id)->position={15,.85f,15};s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;
    ticks(s,1);check(s.player.slowTime>0&&s.player.hp==100,"tar slows without dealing damage");
    s=fixture();id=spawn(s,monsterId(23,2));e=s.findEnemy(id);e->state=EnemyState::Charging;e->stateTime=1;e->facing=unit(Vector3{1,0,1});
    s.arena.obstacles.push_back({{2,-1,-10},{3,5,10}});s.arena.rebuildWalls();
    bool reflected=false;for(int n=0;n<20;++n){ticks(s,1);e=s.findEnemy(id);if(e->facing.x<0){check(e->facing.z>0,"wall normal reflects only the incident component");reflected=true;break;}}
    check(reflected,"oblique reflection observed");
    std::cout<<"DANK fast_dash=1 swept_wall_reflection=1 stationary_recovery=1 slowing_nondamaging_trail=1\n";
}
void shot(Simulation &s,EntityId id,Vector3 from,Vector3 direction,int pierce=0) {
    s.player.position=from;auto *e=s.findEnemy(id);e->state=EnemyState::Stunned;e->stateTime=100;
    Event shot;shot.position=shot.origin=from;shot.direction=direction;shot.damage=24;shot.speed=26;
    AttackSpec attack;attack.damage=24;attack.speed=26;attack.pierce=pierce;shot.attack=attack;
    s.queueRoot(shot);s.drainEvents();ticks(s,20);
}
void princess() {
    auto s=fixture();auto id=spawn(s,monsterId(23,3));s.findEnemy(id)->auxiliary=100;
    ticks(s,1);check(s.findEnemy(id)->state==EnemyState::Ready,"Princess does not acquire cardinal alignment");
    s.findEnemy(id)->position={0,.85f,0};s.player.position={8,.85f,8};ticks(s,1);
    check(s.findEnemy(id)->state==EnemyState::Charging&&near(s.findEnemy(id)->facing.x,s.findEnemy(id)->facing.z),"Princess commits to diagonal axis");
    s=fixture();id=spawn(s,monsterId(23,3));s.findEnemy(id)->facing={0,0,-1};
    shot(s,id,{0,.85f,-4},{0,0,1},2);check(near(s.findEnemy(id)->hp,83.2f),"real piercing shot at armored head remains blocked");
    shot(s,id,{0,.85f,4},{0,0,-1});check(near(s.findEnemy(id)->hp,59.2f),"real rear shot hits exposed tail");
    // An angled shot from behind can hit the armored midsection before the tail.
    shot(s,id,{-4,.85f,0},{1,0,0});
    check(near(s.findEnemy(id)->hp,59.2f),"real side shot hits armored midsection");
    const float before=s.findEnemy(id)->hp;
    Event blast;blast.type=EventType::Explosion;blast.position={0,.85f,-.65f};blast.radius=.2f;blast.damage=12;
    s.queueRoot(blast);s.drainEvents();check(near(s.findEnemy(id)->hp,before),"small front explosion does not reach tail");
    blast.position={0,.85f,.455f};s.queueRoot(blast);s.drainEvents();check(near(s.findEnemy(id)->hp,before-12),"explosion overlapping real tail damages once");
    kill(s,id,true);check(!s.findEnemy(id)->alive,"explicit execution still cleans up armored enemy");
    s=fixture();id=spawn(s,monsterId(23,3));auto *body=s.findEnemy(id);body->facing={0,0,-1};body->state=EnemyState::Stunned;body->stateTime=100;
    s.addFire({0,.85f,-.65f},.2f,2,10,true,false);ticks(s,15);
    check(near(s.findEnemy(id)->hp,83.2f),"flame at armored head cannot damage remote tail");
    s.addFire({0,.85f,.455f},.2f,2,10,true,false);ticks(s,72);
    check(near(s.findEnemy(id)->hp,53.2f),"tail stays vulnerable to repeated fire after contact cooldown expires");
    std::cout<<"PRINCESS diagonal=1 real_tail_projectile=1 head_piercing_blocked=1 spatial_explosions=1\n";
}
void levelTwo() {
    auto s=fixture();const auto id=spawn(s,monsterId(855));ticks(s,1);auto *e=s.findEnemy(id);
    check(e->state==EnemyState::Charging&&near(e->facing.x,0)&&e->velocity.z>10&&e->velocity.z<12,"Level2 begins on cardinal axis and is slower than Charger");
    s.player.position={8,.85f,8};float angle=0;
    for(int n=0;n<30;++n){ticks(s,1);e=s.findEnemy(id);const float next=std::atan2(e->facing.x,e->facing.z);check(next-angle<=1.1f*Tick+.001f,"steering is bounded per tick");angle=next;}
    check(e->position.x>1&&e->facing.x>.4f,"Level2 bends toward moving player during charge");
    s=fixture();const auto second=spawn(s,monsterId(855));s.player.position={0,.85f,.9f};s.godMode=false;ticks(s,1);
    check(s.player.hp==75&&s.findEnemy(second)->maxHp==128,"source double contact has one hostile multiplier; local HP conversion retained");
    std::cout<<"LEVEL2 hp=128 cardinal_start=1 steering=1 slower=1 contact_damage=25\n";
}
void startingKit() {
    for(const auto monster:{monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)}) {
        auto s=fixture();const auto id=spawn(s,monster);s.godMode=false;s.dynamite=0;int ticksTaken=0;
        for(;ticksTaken<3600&&s.findEnemy(id)&&s.player.hp>0;++ticksTaken) {
            const auto radial=unit(horizontal(s.player.position));const Vector3 tangent{-radial.z,0,radial.x};
            Input input;input.fire=true;input.aim=s.findEnemy(id)->position;
            input.movement=unit(add(tangent,mul(radial,std::clamp((8-length(horizontal(s.player.position)))*.7f,-2.f,2.f))));
            input.dodge=s.findEnemy(id)->state==EnemyState::Charging&&distance(s.player.position,s.findEnemy(id)->position)<4.5f;
            s.step(input);
        }
        // Keep moving after the body dies so the death volley is part of the trial.
        for(int n=0;n<90&&!s.findEnemy(id)&&s.player.hp>0;++n) {
            const auto radial=unit(horizontal(s.player.position));Input input;
            input.movement={-radial.z,0,radial.x};s.step(input);
        }
        std::cout<<"CHARGER_STARTING_KIT id="<<monsterIdText(monster)<<" seconds="<<float(ticksTaken)*Tick<<" post_death_seconds=1.5 hp="<<s.player.hp<<" kills="<<s.stats.kills<<'\n';
        check(!s.findEnemy(id)&&s.player.hp>0,"synthetic-room starting-kit bot defeats each variant without items, bombs or god mode");
    }
}
void pools() {
    const auto c=defaultMechanics();
    for(int band=0;band<4;++band) {
        const auto &pool=c->encounterPool(band,EncounterPattern::ChargeLane);
        auto has=[&](MonsterId id){return std::any_of(pool.specialists.begin(),pool.specialists.end(),[&](const auto &e){return e.weight>0&&e.monster==id;});};
        check(has(monsterId(23,1))==(band==1||band==2),"Drowned approved bands1/2");
        check(has(monsterId(23,2))==(band==2),"Dank approved band2");
        check(has(monsterId(23,3))==(band==1),"Princess approved Ashpit-equivalent band1");
        check(has(monsterId(855))==(band==3),"Level2 approved Corpse-equivalent band3");
    }
}
}
int main(){try{drowned();dank();princess();levelTwo();startingKit();pools();std::cout<<"PASS Charger variants and weak-point collision\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
