#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> rules=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(rules));s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,12,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;}
    for(auto &r:s.rooms){r.residents.clear();r.segmented.clear();r.cleared=false;r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.suppliedBombs.clear();s.enemyBombs.clear();s.moneyPickups.clear();s.stats={};
    s.debugScenario=true;s.godMode=true;s.roomClear=s.bossKilled=false;s.player.position={20,.85f,20};return s;
}
EntityId spawn(Simulation &s){const auto id=s.spawnMonster(monsterId(19,3),{0,.85f,0});check(id!=0,"Complete Shell encounter spawns");return id;}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.execution=e.debugExecution=debug;s.queueRoot(e);s.drainEvents();
}
void blast(Simulation &s,EntityId id,float damage,float radius=.1f) {
    Event e;e.type=EventType::Explosion;e.position=e.origin=s.findEnemy(id)->position;e.damage=damage;e.radius=radius;
    e.demolition=Demolition::SuppliedBomb;s.queueRoot(e);s.drainEvents();
}
std::vector<EntityId> chain(const Simulation &s){return s.rooms[0].segmented[0].chains[0].members;}
void compositionAndArmor() {
    auto s=fixture();const auto head=spawn(s);const auto ids=chain(s);const auto body=ids[1];
    check(s.enemies.size()==12&&s.roomThreats()==10&&ids.size()==5,"Two heads plus eight bodies and two non-gating suppliers");
    check(s.rooms[0].segmented[0].maximumHealth==896&&s.bossHealthFraction(*s.boss())==1,"Aggregate health excludes immortal heads");
    hit(s,head,10000);blast(s,head,10000);check(s.findEnemy(head)->hp==112&&s.findEnemy(head)->segmentArmor==15,"Head immune to shots and real explosions");
    Event fake;fake.type=EventType::Damage;fake.target=head;fake.damage=10000;fake.execution=true;s.queueRoot(fake);s.drainEvents();
    check(s.findEnemy(head)->alive,"Generic execution cannot kill head");
    hit(s,body,10000);check(s.findEnemy(body)->segmentArmor==15&&s.findEnemy(body)->hp==112,"Armored body blocks bullets");
    blast(s,body,14);check(s.findEnemy(body)->segmentArmor==1,"Shell does not inherit Tuff explosive resistance");
    blast(s,body,1);check(s.findEnemy(body)->segmentArmor==0&&s.findEnemy(body)->segmentSettling&&s.findEnemy(body)->hp==112,"15 actual explosive damage strips without spillover");
    blast(s,body,24);check(s.findEnemy(body)->hp==88,"Exposed flesh accepts full explosive damage");
    hit(s,body,24);check(s.findEnemy(body)->hp==64,"Exposed flesh accepts starting player damage");
    auto cap=fixture();cap.limits.enemies=11;check(!cap.spawnMonster(monsterId(19,3),{0,.85f,0})&&cap.enemies.empty(),"Capacity rejection is atomic including required suppliers");
    std::cout<<"SHELL_ARMOR pair_5=1 head_invulnerability=1 body_hp=112 armor=15 full_explosive_damage=1 atomic_spawn=1\n";
}
void movementAndAttacks() {
    auto s=fixture();const auto head=spawn(s);const auto ids=chain(s);const auto start=s.findEnemy(head)->position;
    ticks(s,60);const auto pos=s.findEnemy(head)->position;
    check(pos.x>start.x+2&&pos.z<start.z-2,"Head starts diagonal flight");
    auto close=fixture(),distant=fixture();const auto nearId=spawn(close),farId=spawn(distant);
    close.player.position=add(close.findEnemy(nearId)->position,{4,0,1});ticks(close,30);ticks(distant,30);
    check(close.findEnemy(nearId)->facing.z>distant.findEnemy(farId)->facing.z+.02f,"Nearby head veers slightly toward player");
    for(int n=0;n<1400;++n){s.step({});for(const auto &e:s.enemies)if(e.alive&&e.segmentedEncounter)check(!s.arena.flightBlocked(e.position,e.radius,0),"Reflection keeps all flying parts in arena");}
    auto slow=fixture(),fast=fixture();const auto a=spawn(slow),b=spawn(fast);const auto original=chain(slow);
    for(size_t i=1;i<original.size();++i)blast(slow,original[i],15);
    ticks(slow,30);ticks(fast,30);
    check(planarDistance(slow.findEnemy(a)->position,slow.findEnemy(a)->home)<planarDistance(fast.findEnemy(b)->position,fast.findEnemy(b)->home)*.5f,"Attached exposed bodies slow the head");
    auto attack=fixture();spawn(attack);const auto parts=chain(attack);blast(attack,parts[2],15);blast(attack,parts[4],15);
    attack.findEnemy(parts[2])->auxiliary=0;attack.findEnemy(parts[4])->cooldown=0;attack.step({});
    check(attack.stats.projectiles==3,"Middle flesh fires exactly one three-shot volley");
    check(std::count_if(attack.enemies.begin(),attack.enemies.end(),[&](auto &e){return e.monster==monsterId(819)&&e.summoner==parts[4];})==1,"Exposed tail produces actual independent Fly Bomb");
    for(const auto &shot:attack.projectiles)check(dot(unit(shot.velocity),unit(sub(attack.player.position,shot.origin)))>.95f,"Triple volley aims at player");
    std::cout<<"SHELL_MOTION diagonal=1 reflection=1 flesh_slowdown=1 aimed_triple=1 tail_fly_bomb=1\n";
}
void splitCases() {
    auto promote=fixture();spawn(promote);auto ids=chain(promote);hit(promote,ids[1],10000,true);
    check(!promote.findEnemy(ids[0])->alive&&promote.findEnemy(ids[2])->segmentHead&&promote.rooms[0].segmented[0].chains.size()==2,"Three-part armored rear becomes new headed copy; isolated old head retires");
    auto turn=fixture();spawn(turn);auto turned=chain(turn);turn.findEnemy(turned[2])->facing={1,0,0};hit(turn,turned[1],10000,true);
    const auto direction=turn.findEnemy(turned[2])->facing;
    check(std::abs(direction.x)>.7f&&std::abs(direction.z)>.7f,"Promoted head starts diagonal even if follower was moving cardinally");
    auto reverse=fixture();spawn(reverse);ids=chain(reverse);blast(reverse,ids[2],15);hit(reverse,ids[1],10000,true);
    check(reverse.findEnemy(ids[4])->segmentHead&&!reverse.findEnemy(ids[2])->segmentHead,"Rear armored endpoint promoted when front endpoint exposed");
    auto shortArmored=fixture();spawn(shortArmored);ids=chain(shortArmored);hit(shortArmored,ids[2],10000,true);
    check(!shortArmored.findEnemy(ids[3])->alive&&!shortArmored.findEnemy(ids[4])->alive&&shortArmored.findEnemy(ids[0])->alive,"Short armored rear retires without deleting retained head/body");
    auto flesh=fixture();spawn(flesh);ids=chain(flesh);blast(flesh,ids[3],15);blast(flesh,ids[4],15);hit(flesh,ids[2],10000,true);
    const auto before=flesh.findEnemy(ids[3])->position;const float range=planarDistance(before,flesh.player.position);ticks(flesh,60);
    check(flesh.findEnemy(ids[3])->alive&&!flesh.findEnemy(ids[3])->segmentHead&&planarDistance(flesh.findEnemy(ids[3])->position,flesh.player.position)<range-.5f,"Detached multi-flesh chain chases slowly without inventing a head");
    auto single=fixture();spawn(single);ids=chain(single);blast(single,ids[4],15);hit(single,ids[3],10000,true);const auto still=single.findEnemy(ids[4])->position;
    single.findEnemy(ids[4])->cooldown=0;ticks(single,30);
    check(planarDistance(still,single.findEnemy(ids[4])->position)<.001f&&single.findEnemy(ids[4])->alive,"Detached single flesh remains stationary");
    check(std::any_of(single.enemies.begin(),single.enemies.end(),[&](auto &e){return e.monster==monsterId(819)&&e.summoner==ids[4];}),"Detached single keeps real offspring attack");
    // All simultaneous body-death masks: each survivor appears once, no extra
    // headed copy is created, and heads never survive without a body.
    for(int mask=1;mask<16;++mask) {
        auto batch=fixture();spawn(batch);ids=chain(batch);
        for(int i=1;i<5;++i)if(mask&(1<<(i-1))) {Event e;e.type=EventType::Damage;e.target=ids[size_t(i)];e.damage=10000;e.execution=e.debugExecution=true;batch.queueRoot(e);}
        batch.drainEvents();std::set<EntityId> seen;int heads=0;
        for(const auto &c:batch.rooms[0].segmented[0].chains) {
            if(batch.findEnemy(c.members[0])->segmentHead){++heads;check(c.members.size()>1,"No immortal lone head after multi-hit blast");}
            for(auto id:c.members)check(seen.insert(id).second&&batch.findEnemy(id)->alive,"Topology contains each survivor exactly once");
        }
        check(heads<=2,"Default Shell never multiplies headed copies");
        for(const auto &e:batch.enemies)if(e.alive&&e.segmentedEncounter)check(seen.contains(e.id),"No orphan room-sealing segment after simultaneous deaths");
    }
    std::cout<<"SHELL_SPLIT promotion=1 reversed_endpoint=1 short_armor_retirement=1 detached_group=1 stationary_single=1 simultaneous_masks=15\n";
}
void landingAndCompletion() {
    for(bool water:{false,true}) {
        auto s=fixture();spawn(s);const auto ids=chain(s);const auto body=ids[4];
        if(water) {
            auto field=std::make_shared<CanyonTerrain>();field->x=field->z=-25;field->step=1;field->width=field->depth=51;
            field->heights.assign(51*51,0);field->boundaryHeights=field->heights;
            field->river={{{-25,0,0},2,0},{{25,0,0},2,50}};field->riverKind=CanyonRiverKind::Interior;
            for(int z=23;z<=27;++z)for(int x=0;x<51;++x)field->heights[size_t(z*51+x)]=-1.5f;s.arena.canyon=field;
        } else {s.arena.obstacles={{{-2,0,-2},{2,3,2}}};s.arena.rebuildWalls();}
        auto *e=s.findEnemy(body);e->position={0,s.arena.flightHeight({0,0,0},e->radius),0};blast(s,body,15);hit(s,ids[3],10000,true);
        check(e->alive&&e->segmentSettling,"Stripping armor over water/cover retains vulnerable body");
        for(int i=0;i<240&&e->segmentSettling;++i){s.step({});e=s.findEnemy(body);}
        check(e&&e->alive&&!e->segmentSettling&&e->position.y==.85f&&!s.arena.blocked(e->position,e->radius),"Flesh lands on connected legal ground without teleport/deletion");
    }
    auto s=fixture();spawn(s);s.debugScenario=false;const auto child=s.spawnMonster(monsterId(819),{19,.85f,-19});
    const auto all=s.rooms[0].segmented[0].allMembers;
    for(auto id:all)if(const auto *e=s.findEnemy(id);e&&e->alive&&!e->segmentHead)hit(s,id,10000,true);
    check(s.bossKilled&&s.rooms[0].bossPaid&&s.moneyPickups.size()==1&&s.findEnemy(child)->alive&&!s.roomClear,"One aggregate reward after all bodies, surviving offspring still blocks clearance");
    ticks(s,2);check(!s.roomClear,"Living Fly Bomb required for real room clearance");
    hit(s,child,10000,true);ticks(s,2);check(s.roomClear&&s.rooms[0].bossPaid,"Clear after last child with aggregate boss reward retained");
    const auto paid=s.moneyPickups.size();ticks(s,5);check(s.moneyPickups.size()==paid,"Later steps never repay boss reward");
    auto pause=fixture();spawn(pause);ticks(pause,40);const auto id=chain(pause)[1];const auto pos=pause.findEnemy(id)->position;
    pause.enterRoom(1);ticks(pause,120);pause.enterRoom(0);check(planarDistance(pos,pause.findEnemy(id)->position)<.001f,"Chains pause and persist offscreen");
    std::cout<<"SHELL_LIFECYCLE cover_landing=1 water_landing=1 aggregate_reward_once=1 children_gate_clear=1 inactive_persistence=1\n";
}
void stages() {
    int count=0;
    for(uint64_t seed=0;seed<100;++seed) {
        const ExpeditionPlan plan(seed);
        for(int floor=0;floor<plan.floorCount;++floor) {
            auto profile=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            if(profile.bossMonster!=monsterId(19,3))continue;
            check(profile.band==1&&profile.variant==FloorVariant::Standard&&profile.doubleBossRoom,"Shell source route is standard Quarry with double arena");
            if(count<3) {
                Simulation actual(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);
                actual.jumpDebug(actual.finalRoom());actual.godMode=true;ticks(actual,400);
                const auto &r=actual.arena.rooms.back();
                const float x=r.bounds.max.x-r.bounds.min.x,z=r.bounds.max.z-r.bounds.min.z;
                check(std::max(x,z)>=56&&std::min(x,z)>=28,"Actual Shell arena has doubled axis");
                check(actual.rooms.back().segmented.size()==1&&actual.suppliedBombs.size()==2,"Actual seeded Shell and both suppliers activate");
                for(const auto &e:actual.enemies)if(e.segmentedEncounter)check(!actual.arena.flightBlocked(e.position,e.radius,actual.room),"Actual Shell respects canyon boundaries");
                for(const auto &bomb:actual.suppliedBombs)check(!actual.arena.path(actual.player.position,add(bomb.charge.position,{0,.67f,0}),.48f).empty(),"Actual supplied bombs reachable from player");
                const int inventory=actual.dynamite;actual.killAll();ticks(actual,1);
                check(actual.roomClear&&actual.bossKilled&&actual.rooms.back().bossPaid&&actual.dynamite==inventory+1,"Actual Shell boss room completes and pays once");
                std::cout<<"SHELL_STAGE_FIXTURE seed="<<seed<<" floor="<<floor<<" room="<<actual.room<<" width="<<x<<" depth="<<z<<"\n";
            }
            ++count;
        }
    }
    check(count>0,"Shell has reachable actual seeded boss pool");
    std::cout<<"SHELL_STAGE seeded_profiles="<<count<<" band=1 standard_only=1 double_arena=1\n";
}
void externalConfiguration() {
    const auto root=std::filesystem::temp_directory_path()/("deathward-shell-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup {std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}} cleanup{root};
    std::filesystem::create_directories(root);
    for(const auto &file:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(file.path().extension()==".mechanics")
        std::filesystem::copy_file(file.path(),root/file.path().filename());
    const auto file=root/"shell.mechanics";std::ifstream input(file);std::string data((std::istreambuf_iterator<char>(input)),{});
    const std::string from="1.55 15 3.5 .6",to="1.55 30 7 .6";const auto at=data.find(from);check(at!=std::string::npos,"Editable Shell values exist");
    data.replace(at,from.size(),to);{std::ofstream out(file);out<<data;}
    const auto changed=MechanicsLibrary::load(root);auto a=fixture(),b=fixture(changed);const auto x=spawn(a),y=spawn(b);ticks(a,30);ticks(b,30);
    check(a.findEnemy(x)->segmentArmor==15&&b.findEnemy(y)->segmentArmor==30&&
        planarDistance(b.findEnemy(y)->position,b.findEnemy(y)->home)>planarDistance(a.findEnemy(x)->position,a.findEnemy(x)->home)*1.9f,"External armor and speed affect new snapshot without changing running one");
    {std::ofstream out(file);out<<data<<"boss_shell_attacks 19.3.0 819.0.0 5 4 2.8 8 .22 10\n";}
    bool rejected=false;try{MechanicsLibrary::load(root);}catch(const std::exception &){rejected=true;}
    check(rejected,"Duplicate Shell attack controller rejected atomically");
    std::cout<<"SHELL_EXTERNAL immutable_snapshot=1 armor_speed=1 invalid_duplicate_rejected=1\n";
}
}
int main(){try{compositionAndArmor();movementAndAttacks();splitCases();landingAndCompletion();stages();externalConfiguration();std::cout<<"PASS Shell armor, movement, topology, attacks, landing, lifecycle and route\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
