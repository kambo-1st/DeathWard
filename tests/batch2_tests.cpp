#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
const std::array<MonsterId,5> ids{monsterId(13),monsterId(14),monsterId(18),monsterId(85),monsterId(16)};
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation fixture(int seed=1866) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-24,-1,-24},{24,12,24}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-24,-.4f,-24},{24,0,24}}};}
    s.arena.boundaryWalls={{{-25,-1,-25},{-24,12,25}},{{24,-1,-25},{25,12,25}},{{-25,-1,-25},{25,12,-24}},{{-25,-1,24},{25,12,25}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.stats={};
    s.room=0;s.rooms.assign(s.arena.roomCount(),{});s.godMode=true;s.roomClear=false;s.player.position={0,.85f,18};return s;
}
void impacts() {
    for(auto kind:ids) {
        auto s=fixture();auto id=s.spawnMonster(kind,{0,.85f,0});for(int n=0;n<4;++n)s.step({},1.f/30);
        auto *e=s.findEnemy(id);const auto at=e->position;e->velocity={3,0,0};
        s.step({},1.f/120);
        check(s.findEnemy(id)->position.x>at.x,"external momentum survives cached controller state");
        e=s.findEnemy(id);e->velocity={};const auto hp=e->hp;
        Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1;hit.projectileImpact=true;hit.direction={1,0,0};
        s.queueRoot(hit);s.drainEvents();
        check(s.findEnemy(id)->hp==hp-1&&s.findEnemy(id)->velocity.x>0,"mass-based admitted-hit recoil");
        const bool eligible=kind==monsterId(14)||kind==monsterId(16);
        check(s.makeChampion(id,0)==eligible,"only Pooter and Mulligan are champion eligible");
        if(eligible)check(s.findEnemy(id)->champion==0,"supported champion applied");
    }
    for(auto kind:{monsterId(14),monsterId(16)})for(int variant:{0,1,2,5,7,13,18,19}) {
        auto s=fixture();auto id=s.spawnMonster(kind,{0,.85f,0});const float hp=s.findEnemy(id)->hp;
        check(s.makeChampion(id,variant),"eight existing champion types apply to both eligible batch2 enemies");
        check(std::abs(s.findEnemy(id)->hp-hp*s.content->champion(variant)->hp)<.001f,"batch2 champion HP scaling");
        s.findEnemy(id)->championTrail=100; // Isolate body contact from Green creep.
        s.godMode=false;s.player.position=s.findEnemy(id)->position;s.step({},1.f/120);
        check(s.player.hp==100,"Pooter and Mulligan champions retain harmless body contact");
    }
    std::cout<<"BATCH2_IMPACT identities=5 momentum=1 masses=1 champion_eligibility=1\n";
}
void fights() {
    for(int seed=0;seed<8;++seed) {
        auto s=fixture(seed);s.godMode=false;s.dynamite=0;
        std::vector<EntityId> roots;
        for(size_t n=0;n<ids.size();++n)roots.push_back(s.spawnMonster(ids[n],{float(n)*4-8,.85f,-4}));
        int frame=0;
        for(;frame<3600&&!s.dead&&!s.roomClear;++frame) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            Input input;
            if(target) {
                auto delta=horizontal(sub(target->position,s.player.position));input.fire=true;
                input.aim=add(target->position,mul(horizontal(target->velocity),length(delta)/26));
                input.movement=length(delta)<7?mul(unit(delta),-1):length(delta)>12?unit(delta):Vector3{};
                input.dodge=length(delta)<2.5f;
            }
            s.step(input);
        }
        std::cout<<"BATCH2_FIGHT seed="<<seed<<" seconds="<<frame*Tick<<" hp="<<s.player.hp<<" kills="<<s.stats.kills<<" clear="<<s.roomClear<<'\n';
        check(s.roomClear&&!s.dead&&s.stats.suppressed==0,"starting revolver/dodge clears mixed batch and offspring");
        for(auto root:roots)check(!s.findEnemy(root)||!s.findEnemy(root)->alive,"all five original threats defeated");
    }
}
void naturalAndPractice() {
    std::set<MonsterId> seen;int champions=0;
    for(int seed=0;seed<24;++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false);
        for(int r=1;r<s.finalRoom();++r)for(const auto &e:s.roomEnemies(r))if(std::find(ids.begin(),ids.end(),e.monster)!=ids.end()) {
            seen.insert(e.monster);const auto *d=s.content->monster(e.monster);
            check(!(d->flying?s.arena.flightBlocked(e.position,e.radius,r):s.arena.blocked(e.position,e.radius)),"natural resident legal footprint");
            if(e.champion>=0){++champions;check(e.monster==monsterId(14)||e.monster==monsterId(16),"champion spawning respects eligibility");}
        }
        if(seed<8) {
            s.startBatch2Practice();check(s.enemies.size()==5&&s.roomThreats()==5&&!s.godMode&&s.items.empty(),"practice has exact baseline mixed cohort");
            check(s.player.hp==100&&s.player.shotDamage==24&&!s.roomClear,"practice preserves starting-kit combat");
            std::set<MonsterId> actual;for(const auto &e:s.enemies)actual.insert(e.monster);check(actual==std::set<MonsterId>(ids.begin(),ids.end()),"practice contains correct five identities");
        }
    }
    check(seen.size()==5,"all five reachable on seeded first floors");
    std::cout<<"BATCH2_PLACEMENT seeds=24 identities="<<seen.size()<<" champions="<<champions<<" practice_seeds=8\n";
}
}
int main(){try{impacts();fights();naturalAndPractice();std::cout<<"PASS second first-floor batch\n";}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
