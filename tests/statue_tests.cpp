#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *message){if(!value)throw std::runtime_error(message);}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.rebuildWalls();for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;}
    for(auto &r:s.rooms){r.residents.clear();r.cleared=false;r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={0,.85f,8};s.debugScenario=true;s.godMode=true;s.roomClear=false;return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
EntityId statue(Simulation &s,MonsterId id=monsterId(42)) {
    const auto entity=s.spawnMonster(id,{0,.85f,0});auto *e=s.findEnemy(entity);
    check(e,"Statue definition spawns");e->cooldown=0;e->facing=e->statueFacing={0,0,1};return entity;
}
void hit(Simulation &s,EntityId id,bool execution=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.execution=execution;s.queueRoot(e);s.drainEvents();
}
void aimedAndLob() {
    for(auto id:{monsterId(42),monsterId(42,1),monsterId(42,2)}) {
        auto s=fixture();const auto entity=statue(s,id);ticks(s,30);
        const auto count=id.variant==2?3u:1u;check(s.stats.projectiles==count&&s.roomThreats()==0,"Aimed/triple/lob source attack counts without room threat");
        const auto *e=s.findEnemy(entity);check(e&&e->position.x==0&&e->position.z==0,"Statue remains anchored");
        hit(s,entity);check(e->alive&&e->hp==64,"Ordinary high damage cannot kill a statue");
        if(id.variant==1) {
            check(s.projectiles.size()==1&&s.projectiles[0].kind==ProjectileKind::Ipecac&&s.projectiles[0].gravity==12&&s.projectiles[0].blastDamage==20,"Vomit fires a real ballistic explosive");
            ticks(s,90);check(s.stats.explosions==1,"Vomit shot detonates on actual collision");
        } else for(const auto &p:s.projectiles)check(p.velocity.z>0,"Aimed blood travels toward player");
        s.clearRoom();const auto shots=s.stats.projectiles;ticks(s,240);
        check(s.findEnemy(entity)->alive&&s.findEnemy(entity)->statueDisabled&&s.stats.projectiles==shots,"Ordinary clear disables rather than deletes the statue");
    }
    std::cout<<"STATUE_AIMED single=1 triple=3 ballistic=1 ordinary_immune=1 cleared_body_retained=1\n";
}
void completionAndReentry() {
    auto s=fixture();const auto id=statue(s);s.debugScenario=false;
    const auto enemy=s.spawnMonster(monsterId(11),{8,.85f,0});hit(s,enemy);ticks(s,1);
    check(s.roomClear&&s.findEnemy(id)->alive&&s.findEnemy(id)->statueDisabled,"Killing last actual enemy clears room with statue retained");
    s.enterRoom(1);s.enterRoom(0);check(s.findEnemy(id)&&s.findEnemy(id)->alive&&s.findEnemy(id)->statueDisabled,"Disabled statue persists after room re-entry");
    const auto kills=s.stats.kills;hit(s,id,true);check(!s.findEnemy(id)->alive&&s.stats.kills==kills,"Exceptional statue death is not ordinary kill credit");
    s.enterRoom(1);s.enterRoom(0);check(s.findEnemy(id)&&s.findEnemy(id)->alive&&s.findEnemy(id)->statueDisabled,"Exceptionally destroyed statue respawns inactive in cleared room");
    s=fixture();const auto eye=statue(s,monsterId(201));ticks(s,1);check(!s.hazards.empty(),"Stone Eye starts firing without a Repentance+ full-turn wait");
    const auto heading=s.findEnemy(eye)->facing;ticks(s,30);check(distance(heading,s.findEnemy(eye)->facing)>.2f&&s.findEnemy(eye)->facing.x<0,"Eye rotates continuously clockwise viewed from above");
    s.clearRoom();ticks(s,1);check(s.hazards.empty()&&s.findEnemy(eye)->statueDisabled,"Clear stops rotating beam");
    s.enterRoom(1);s.enterRoom(0);check(!s.findEnemy(eye),"Cleared Stone Eye disappears on re-entry");
    std::cout<<"STATUE_LIFETIME last_enemy_clear=1 inactive_reentry=1 exceptional_respawn=1 eye_removal=1\n";
}
void persistentAndPlates() {
    for(auto type:{202,203}) {
        auto s=fixture();const auto id=statue(s,monsterId(type));ticks(s,90);
        const auto volleys=s.findEnemy(id)->statueVolley;s.clearRoom();ticks(s,150);
        check(s.findEnemy(id)->alive&&!s.findEnemy(id)->statueDisabled&&s.findEnemy(id)->statueVolley>volleys,"Persistent turret continues after combat clear");
        s.rooms[0].plates={{{-5,.85f,5},false},{{5,.85f,5},false}};
        s.player.position={-5,.85f,5};ticks(s,1);check(!s.findEnemy(id)->statueDisabled,"All required plates must be pressed");
        s.player.position={5,.85f,5};ticks(s,1);check(s.findEnemy(id)->statueDisabled&&s.hazards.empty(),"Final plate disables turret and active beam immediately");
        const auto stopped=s.findEnemy(id)->statueVolley;ticks(s,180);check(s.findEnemy(id)->statueVolley==stopped,"Pressed state prevents later attacks");
        s.enterRoom(1);s.enterRoom(0);check(s.findEnemy(id)->statueDisabled&&s.rooms[0].plates[0].pressed,"Plate progress persists on re-entry");
    }
    auto s=fixture();statue(s);s.debugScenario=false;s.rooms[0].plateObjective=true;s.rooms[0].plates={{{-5,.85f,5},false}};
    ticks(s,1);check(!s.roomClear,"Plate-only objective does not auto-clear for zero ordinary enemies");
    s.player.position={-5,.85f,5};ticks(s,1);check(s.roomClear,"Real player contact completes plate objective");
    std::cout<<"STATUE_PLATES persistent_combat_fire=1 all_plates=1 immediate_beam_stop=1 saved_plate_state=1 plate_objective=1\n";
}
void crossPatterns() {
    for(int variant:{10,11})for(int subtype:{0,1}) {
        auto s=fixture();const auto id=statue(s,monsterId(202,variant,subtype));ticks(s,1);
        check(s.projectiles.size()==4,"Cross fires four shots");
        for(const auto &p:s.projectiles)check(subtype?std::abs(std::abs(p.velocity.x)-std::abs(p.velocity.z))<.001f:
            std::abs(p.velocity.x)<.001f||std::abs(p.velocity.z)<.001f,"Configured initial cardinal/diagonal phase");
        s.projectiles.clear();ticks(s,37);check(s.projectiles.size()==4,"Cross emits next four-shot volley");
        for(const auto &p:s.projectiles)check(subtype?std::abs(p.velocity.x)<.001f||std::abs(p.velocity.z)<.001f:
            std::abs(std::abs(p.velocity.x)-std::abs(p.velocity.z))<.001f,"Second volley swaps axes");
        s.clearRoom();ticks(s,60);check(s.findEnemy(id)->statueDisabled==(variant==10),"Always-on configuration differs from ordinary Cross completion");
    }
    auto s=fixture();const auto id=statue(s,monsterId(202,10));s.rooms[0].trapOnly=true;s.clearRoom();ticks(s,1);
    check(!s.findEnemy(id)->statueDisabled&&s.stats.projectiles==4,"Objective-free trap keeps Cross active");
    std::cout<<"STATUE_CROSS alternating_axes=1 subtype_phase=1 always_on=1 objective_free_trap=1\n";
}
void physicalBodies() {
    auto s=fixture();const auto id=statue(s);
    check(s.arena.blocked({0,.85f,0},.48f)&&s.arena.flightBlocked({0,4,0},.48f,0),"Walking and flying cannot pass through statue");
    const auto moved=s.arena.move({0,.85f,-3},{0,0,6},.48f);check(moved.z<0,"Swept dodge cannot tunnel through statue");
    const auto route=s.arena.path({0,.85f,-3},{0,.85f,3},.48f);check(!route.empty()&&route.size()>1,"Mouse navigation routes around statue");
    auto from=Vector3{0,.85f,-3};for(const auto &to:route){check(s.arena.clear(from,to,.48f),"Every route segment clears physical body");from=to;}
    check(s.arena.sight({0,.85f,-3},{0,.85f,0}),"Aiming ray can still reach hazard entity");
    Event shot;shot.position=shot.origin={.55f,.85f,-3};shot.direction={0,0,1};shot.damage=24;shot.speed=20;
    s.queueRoot(shot);s.drainEvents();ticks(s,16);
    check(s.projectiles.empty()&&s.stats.damageDealt==0&&s.findEnemy(id)->hp==64,"Actual player shot is intercepted by immutable stone body without damaging it");
    hit(s,id,true);check(!s.arena.blocked({0,.85f,0},.48f),"Exceptional destruction removes movement collider immediately");
    std::cout<<"STATUE_PHYSICS walking=1 flight=1 swept_dodge=1 mouse_path=1 ray_aim=1 exceptional_collider_removal=1\n";
}
}
int main(){try{aimedAndLob();completionAndReentry();persistentAndPlates();crossPatterns();physicalBodies();
 std::cout<<"PASS configurable Grimace attacks, completion, plate state, re-entry and collision\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
