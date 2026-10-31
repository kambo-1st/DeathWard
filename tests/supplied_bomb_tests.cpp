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
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(rules));
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,12,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;}
    for(auto &r:s.rooms){r.residents.clear();r.cleared=false;r.plates.clear();}
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.suppliedBombs.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={12,.85f,12};s.debugScenario=true;s.godMode=false;s.roomClear=false;return s;
}
void ticks(Simulation &s,int n,Input input={}){for(int i=0;i<n;++i)s.step(input);}
EntityId supplier(Simulation &s,Vector3 at={0,.85f,0}) {
    const auto id=s.spawnMonster(monsterId(809),at);check(id!=0,"Configured supplier exists");
    s.findEnemy(id)->facing=s.findEnemy(id)->statueFacing={0,0,1};return id;
}
void take(Simulation &s,size_t index=0) {
    s.player.position=s.suppliedBombs.at(index).charge.position;s.player.position.y=.85f;s.step({});
    check(s.carriedBomb()!=nullptr,"Actual player contact takes supplied pickup");
}
void hit(Simulation &s,EntityId id,bool execute=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.execution=execute;s.queueRoot(e);s.drainEvents();
}
void supplyAndTake() {
    auto s=fixture();const auto id=supplier(s);s.dynamite=0;ticks(s,1);
    check(s.suppliedBombs.size()==1&&s.suppliedBombs[0].sourceIdentity()==monsterId(5,41),"Supplier emits real unlit pickup identity");
    ticks(s,900);check(s.suppliedBombs.size()==1&&s.suppliedBombs[0].charge.age==0&&s.stats.explosions==0,"Waiting stock never starts a fuse or duplicates");
    hit(s,id);check(s.findEnemy(id)->alive&&s.findEnemy(id)->hp==64&&s.roomThreats()==0,"Supplier is ordinarily invulnerable, noncombat support");
    take(s);const auto carried=s.carriedBomb()->id;
    check(s.carriedBomb()->sourceIdentity()==monsterId(4,13)&&s.dynamite==0,"Taking changes identity without inventory charge");
    ticks(s,150);check(s.suppliedBombs.size()==2&&s.carriedBomb()->id==carried,"Replacement arrives after taking while prior bomb is still held");
    for(int n=0;n<35&&s.stats.explosions==0;++n)s.step({});check(!s.carriedBomb()&&s.stats.explosions==1&&s.player.hp==75,"Held bomb expires and hurts holder without hostile multiplier");
    check(s.dynamite==0&&s.stats.shots==0&&s.findEnemy(id)->alive,"No inventory, ordinary shot or supplier damage side effect");
    std::cout<<"SUPPLY_STOCK unlit_wait=1 pickup_5_41=1 armed_4_13=1 replenish_before_explosion=1 held_fuse=1 zero_inventory=1\n";
}
void controlsAndFlight() {
    auto s=fixture();supplier(s);s.dynamite=0;s.grant(ItemId::Braid);ticks(s,1);take(s);ticks(s,30);
    const auto age=s.carriedBomb()->charge.age;const auto id=s.carriedBomb()->id;
    Input fire;fire.fire=true;fire.aimDirection=Vector3{1,0,0};s.step(fire);
    const auto it=std::find_if(s.suppliedBombs.begin(),s.suppliedBombs.end(),[&](auto &b){return b.id==id;});
    check(!s.carriedBomb()&&it->state==SuppliedBombState::Thrown&&it->charge.velocity.x>10,"Arrow aim throws held bomb along its direction");
    check(it->charge.age>age&&it->charge.age<age+.02f&&it->charge.braidCopies==0,"Throw preserves fuse and does not invent Braid inheritance");
    check(s.dynamite==0&&s.stats.shots==0&&s.player.nextRound==1,"Throw consumes neither ordinary inventory nor magazine cycle");
    s.player.position={-12,.85f,-12};ticks(s,150);
    check(s.stats.explosions==1&&s.hazards.empty(),"Thrown supplied bomb detonates without Braid children");
    auto placed=fixture();supplier(placed);placed.dynamite=0;ticks(placed,1);take(placed);
    Input place;place.placeDynamite=true;placed.step(place);
    check(!placed.carriedBomb()&&placed.suppliedBombs[0].state==SuppliedBombState::Thrown&&placed.suppliedBombs[0].charge.settled,"Place control puts held bomb down without spending inventory");
    auto wall=fixture();supplier(wall);ticks(wall,1);take(wall);
    wall.arena.boundaryWalls={{{3,-1,-10},{3.3f,8,10}}};wall.arena.rebuildWalls();
    wall.step(fire);ticks(wall,25);check(wall.suppliedBombs[0].charge.position.x<3,"Thrown bomb uses real swept wall collision");
    std::cout<<"SUPPLY_CONTROLS arrows=1 place=1 no_inventory=1 no_shot_cycle=1 no_invented_braid=1 fuse_preserved=1 swept_throw=1\n";
}
void independentSuppliersAndDeath() {
    auto s=fixture();const auto a=supplier(s,{-4,.85f,0}),b=supplier(s,{4,.85f,0});ticks(s,1);
    check(s.suppliedBombs.size()==2,"Two producers keep separate stock (declared local ownership rule)");
    s.clearRoom();ticks(s,300);check(s.suppliedBombs.size()==2&&!s.findEnemy(a)->statueDisabled,"Ordinary clear does not stop supply or duplicate stock");
    const auto kills=s.stats.kills;hit(s,a,true);ticks(s,1);
    check(s.suppliedBombs.size()==12&&s.findEnemy(a)->supplyDeathPending==0,"Exceptional kill creates ten new unlit pickups, retaining existing stock");
    check(std::count_if(s.suppliedBombs.begin(),s.suppliedBombs.end(),[](auto &bomb){return bomb.deathDrop;})==10,"Exactly ten death drops have separate ownership role");
    check(s.stats.kills==kills&&s.stats.explosions==0&&s.findEnemy(b)->alive,"Death burst is not ten lit explosives or ordinary kill loot");
    s.enterRoom(1);ticks(s,30);s.enterRoom(0);ticks(s,1);
    check(s.findEnemy(a)->alive&&s.suppliedBombs.size()==12,"Re-entry preserves unlit stock without replaying death burst");
    auto limited=fixture();const auto capped=supplier(limited);limited.limits.suppliedBombs=4;ticks(limited,1);hit(limited,capped,true);ticks(limited,1);
    check(limited.suppliedBombs.size()==4&&limited.findEnemy(capped)->supplyDeathPending==7,"Capacity keeps remaining death drops as bounded pending work");
    limited.limits.suppliedBombs=16;ticks(limited,20);
    check(limited.suppliedBombs.size()==11&&limited.findEnemy(capped)->supplyDeathPending==0,"Deferred drops resume when capacity is available");
    std::cout<<"SUPPLY_DEATH independent_stock=1 ten_unlit_drops=1 retained_stock=1 no_kill_credit=1 no_reentry_duplicate=1 bounded_pending=1\n";
}
void persistenceAndDemolition() {
    auto s=fixture();supplier(s);ticks(s,1);take(s);ticks(s,30);const auto age=s.carriedBomb()->charge.age;
    s.enterRoom(1);ticks(s,30);check(s.carriedBomb()&&s.carriedBomb()->charge.age>age+.49f,"Carried fuse continues across room transitions");
    Input place;place.placeDynamite=true;s.step(place);const auto paused=s.suppliedBombs[0].charge.age;
    s.player.position={12,.85f,12};s.enterRoom(0);ticks(s,180);check(std::abs(s.suppliedBombs[0].charge.age-paused)<.0001f,"Thrown bomb pauses in inactive room under explicit persistence policy");
    s.enterRoom(1);ticks(s,140);check(s.stats.explosions==1,"Returning resumes same thrown fuse without reset");
    auto wall=fixture();supplier(wall);ticks(wall,1);take(wall);wall.dynamite=0;wall.step(place);
    Breakable gate;gate.id=1;gate.kind=BreakableKind::CacheGate;gate.room=0;gate.bounds={{1,0,1},{1.4f,2,3}};gate.health=1;gate.rewardPosition={2,.85f,2};
    wall.arena.breakables={gate};wall.arena.rebuildWalls();wall.player.position={12,.85f,12};ticks(wall,177);const auto enemy=wall.spawnMonster(monsterId(11),{-1,.85f,2});wall.findEnemy(enemy)->hp=wall.findEnemy(enemy)->maxHp=200;
    ticks(wall,4);
    check(wall.arena.breakables[0].destroyed&&wall.arena.keys.size()==1&&wall.dynamite==0,"Supplied explosion opens real hard terrain through its own provenance");
    check(wall.findEnemy(enemy)->hp<200&&wall.stats.explosions==1,"Actual explosion reaches nearby vulnerable enemy");
    for(int band=0;band<4;++band)for(const auto &entry:defaultMechanics()->statuePool(band))check(entry.monster!=monsterId(809),"No unsupported ordinary placement for dedicated encounter support");
    std::cout<<"SUPPLY_PERSISTENCE held_across_rooms=1 thrown_pause_resume=1 own_demolition_permission=1 actual_enemy_damage=1 dedicated_only=1\n";
}
void externalRules() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-supplied-bomb-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);
    for(const auto &p:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(p.path().extension()==".mechanics")std::filesystem::copy_file(p.path(),dir/p.path().filename());
    auto before=MechanicsLibrary::load(dir);std::ifstream file(dir/"statues.mechanics");std::string text((std::istreambuf_iterator<char>(file)),{});file.close();
    const std::string old="statue_supply 809.0.0 2.5 3 ";auto at=text.find(old);check(at!=std::string::npos,"External supply row exists");
    text.replace(at,old.size(),"statue_supply 809.0.0 .5 1 ");std::ofstream(dir/"statues.mechanics")<<text;
    auto after=MechanicsLibrary::load(dir);auto a=fixture(before),b=fixture(after);supplier(a);supplier(b);ticks(a,1);ticks(b,1);take(a);take(b);ticks(a,61);ticks(b,61);
    check(a.stats.explosions==0&&b.stats.explosions==1&&before->fingerprint()!=after->fingerprint(),"File-only fuse changes real behavior and old snapshot remains stable");
    std::filesystem::remove_all(dir);std::cout<<"SUPPLY_CONFIG actual_fuse=1 immutable_snapshot=1\n";
}
void blockedSupplyAndFloorTravel() {
    auto s=fixture();const auto producer=supplier(s);
    s.arena.obstacles={{{-24,-1,-24},{24,3,24}}};s.arena.rebuildWalls();ticks(s,60);
    check(s.suppliedBombs.empty()&&s.findEnemy(producer)->supplyProduced==0,"Blocked supplier never creates unreachable stock");
    s.arena.obstacles.clear();s.arena.rebuildWalls();ticks(s,20);
    check(s.suppliedBombs.size()==1,"Stock retries when a legal approach becomes available");
    take(s);ticks(s,25);const auto age=s.carriedBomb()->charge.age;
    const auto fuse=s.carriedBomb()->rules.fuse;
    s.room=s.finalRoom();s.roomClear=true;s.floorExitRequested=true;
    check(s.advanceFloor()&&s.floor==1,"Actual floor transition succeeds with a carried bomb");
    check(s.suppliedBombs.size()==1&&s.carriedBomb()&&s.carriedBomb()->supplier==0&&
          s.carriedBomb()->charge.age==age&&s.carriedBomb()->rules.fuse==fuse,
          "Only carried ordnance crosses floors, with original fuse and rules");
    s.step({});check(s.carriedBomb()&&s.carriedBomb()->charge.age>age,"Carried fuse resumes on new floor");
    std::cout<<"SUPPLY_ROUTING blocked_retry=1 real_floor_travel=1 preserved_fuse=1\n";
}
}
int main(){try{supplyAndTake();controlsAndFlight();independentSuppliersAndDeath();persistenceAndDemolition();externalRules();blockedSupplyAndFloorTravel();
 std::cout<<"PASS supplied bomb stock, taking, controls, flight, fuse, death drops, room persistence and external rules\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
