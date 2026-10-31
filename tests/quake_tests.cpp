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
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={12,.85f,12};s.debugScenario=true;s.godMode=false;s.roomClear=false;return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
EntityId quake(Simulation &s,int axis=3){const auto id=s.spawnMonster(monsterId(804,0,axis),{0,.85f,0});check(id!=0,"Configured Quake identity");return id;}
Breakable prop(int id,BreakableKind kind,Box bounds) {
    Breakable p;p.id=id;p.lootSeed=12345+id;p.kind=kind;p.bounds=bounds;p.health=2;
    p.rewardPosition=mul(add(bounds.min,bounds.max),.5f);p.rewardPosition.y=.85f;return p;
}
void cadenceAndAxes() {
    const std::array<Vector3,4> directions{{{-1,0,0},{0,0,-1},{1,0,0},{0,0,1}}};
    for(int axis=0;axis<4;++axis) {
        auto s=fixture();const auto id=quake(s,axis);ticks(s,150);
        check(s.hazards.empty()&&s.findEnemy(id)->lift==0,"No early attack before hop");
        ticks(s,15);check(s.findEnemy(id)->lift>.9f&&s.hazards.empty(),"Visible anchored hop precedes the landing");
        check(distance(s.findEnemy(id)->position,{0,.85f,0})==0,"No horizontal pursuit during hop");
        ticks(s,15);check(s.findEnemy(id)->statueVolley==1&&s.findEnemy(id)->lift<.001f,"First wave at exactly three seconds");
        check(s.hazards.size()==1&&s.hazards[0].kind==HazardKind::RockWave,"Landing emits an actual moving ground wave");
        check(distance(unit(s.hazards[0].velocity),directions[size_t(axis)])<.001f,"Animation subtype chooses fixed world direction");
        const auto start=s.hazards[0].position;ticks(s,30);
        check(s.hazards.size()==1&&std::abs(distance(start,s.hazards[0].position)-5)<.001f,"Wave propagates at configured ten units per second");
        ticks(s,149);check(s.findEnemy(id)->statueVolley==1,"No second landing before six seconds");
        ticks(s,1);check(s.findEnemy(id)->statueVolley==2,"Three seconds between landings, without extra windup");
        check(s.stats.projectiles==0&&s.stats.explosions==0&&s.roomThreats()==0,"Ground waves are neither bullets nor explosions nor combat threats");
    }
    std::cout<<"QUAKE_AXES left_up_right_down=1 anchored_hop=1 first_landing_3s=1 period_3s=1 real_wave_speed=10\n";
}
void contactsAndCover() {
    auto s=fixture();quake(s);s.player.position={0,.85f,4};ticks(s,210);
    check(s.player.hp==100-10*EnemyDamageMultiplier,"Actual wave front hurts a grounded player once");
    ticks(s,30);check(s.player.hp==100-10*EnemyDamageMultiplier,"Rendered trail does not multiply front damage");
    auto high=fixture();quake(high);high.player.position={0,4,4};ticks(high,210);
    check(high.player.hp==100,"Ground wave cannot hit a high airborne actor");
    auto wall=fixture();quake(wall);wall.arena.boundaryWalls={{{-5,-1,2},{5,8,2.2f}}};wall.arena.rebuildWalls();
    wall.player.position={0,.85f,2.4f};ticks(wall,210);
    check(wall.player.hp==100&&wall.hazards.empty(),"Swept collision stops at solid cover without damaging through it");
    auto corridor=fixture();quake(corridor);corridor.arena.rooms[0].bounds={{-3,-1,-3},{3,8,3}};
    corridor.player.position={0,.85f,3.1f};ticks(corridor,210);
    check(corridor.player.hp==100&&corridor.hazards.empty(),"Wave does not attack outside its active room");
    std::cout<<"QUAKE_CONTACT base_player_damage=10 multiplied_at_impact=1 one_front_hit=1 vertical_clearance=1 wall_cover=1 corridor_stop=1\n";
}
void demolitionAndPersistence() {
    for(bool reverse:{false,true}) {
        auto s=fixture();const auto id=quake(s);const auto bombs=s.dynamite;
        s.arena.breakables={prop(1,BreakableKind::CacheGate,{{-1,0,3},{1,2,3.3f}}),
                            prop(2,BreakableKind::CrackedRock,{{-1,0,5},{1,2,5.3f}})};
        if(reverse)std::reverse(s.arena.breakables.begin(),s.arena.breakables.end());s.arena.rebuildWalls();
        s.player.position={0,.85f,3.5f};ticks(s,210);
        auto gate=[&]()->const Breakable&{return *std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[](auto &p){return p.id==1;});};
        auto rock=[&]()->const Breakable&{return *std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[](auto &p){return p.id==2;});};
        check(gate().destroyed&&gate().paid&&!rock().destroyed,"First wave opens only the first wall independent of vector order");
        check(s.player.hp==100&&s.dynamite==bombs&&s.stats.kills==0&&s.stats.explosions==0,"Opening wall preserves cover snapshot, player inventory and kill/explosion accounting");
        check(s.arena.keys.size()==1&&s.moneyPickups.size()==1,"Optional cache analogue pays once on opening");
        s.player.position={12,.85f,12};ticks(s,180);
        check(rock().destroyed&&s.arena.keys.size()==1,"Later wave reaches the next obstruction without duplicate cache payout");
        const auto phase=s.findEnemy(id)->statuePhase;s.enterRoom(1);ticks(s,30);s.enterRoom(0);
        check(s.findEnemy(id)->statuePhase==phase&&gate().destroyed,"Inactive room pauses cycle and preserves opened wall");
    }
    auto protectedWall=fixture();quake(protectedWall);protectedWall.arena.breakables={prop(1,BreakableKind::OreSeam,{{-1,0,3},{1,2,3.3f}})};
    protectedWall.arena.rebuildWalls();ticks(protectedWall,400);
    check(!protectedWall.arena.breakables[0].destroyed&&protectedWall.arena.breakables[0].health==2,"Wave cannot mine protected ore resource gates");
    std::cout<<"QUAKE_DEMOLITION first_surface_only=1 cache_analogue=1 no_spent_bomb=1 no_kill_credit=1 persistent_loot_once=1 protected_ore=1\n";
}
void clearPlateAndBounds() {
    auto s=fixture();const auto id=quake(s);ticks(s,180);s.clearRoom();ticks(s,180);
    check(s.findEnemy(id)->statueVolley==2&&!s.findEnemy(id)->statueDisabled,"Ordinary combat clear does not stop Quake");
    s.rooms[0].plates={{{-5,.85f,5},false}};s.player.position={-5,.85f,5};ticks(s,1);
    check(s.findEnemy(id)->statueDisabled&&!s.hazards.empty(),"Plate stops future landings; emitted wave finishes independently");
    ticks(s,300);check(s.findEnemy(id)->statueVolley==2&&s.hazards.empty(),"No new wave after permanent plate shutdown");
    s.enterRoom(1);s.enterRoom(0);ticks(s,200);check(s.findEnemy(id)->statueVolley==2,"Shutdown survives re-entry");
    auto crowded=fixture();crowded.limits.hazards=2;for(int i=0;i<8;++i)quake(crowded);ticks(crowded,180);
    check(crowded.hazards.size()==2&&!crowded.logs.empty(),"Wave creation obeys existing hazard capacity and suppression reporting");
    std::cout<<"QUAKE_LIFETIME combat_persistence=1 plate=1 emitted_wave_finishes=1 reentry=1 bounded_hazards=1\n";
}
void externalRules() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-quake-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);
    for(const auto &p:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(p.path().extension()==".mechanics")std::filesystem::copy_file(p.path(),dir/p.path().filename());
    auto before=MechanicsLibrary::load(dir);std::ifstream file(dir/"statues.mechanics");std::string text((std::istreambuf_iterator<char>(file)),{});file.close();
    const std::string old="statue 804.0.3 quake plates 3 0 10 10";auto at=text.find(old);check(at!=std::string::npos,"External quake row exists");
    text.replace(at,old.size(),"statue 804.0.3 quake plates 3 0 10 5");std::ofstream(dir/"statues.mechanics")<<text;
    auto after=MechanicsLibrary::load(dir);auto a=fixture(before),b=fixture(after);quake(a);quake(b);ticks(a,200);ticks(b,200);
    check(a.hazards[0].position.z>b.hazards[0].position.z+1&&before->fingerprint()!=after->fingerprint(),"File edit changes real wave speed while prior snapshot remains intact");
    std::filesystem::remove_all(dir);std::cout<<"QUAKE_CONFIG actual_speed=1 immutable_snapshot=1\n";
}
}
int main(){try{cadenceAndAxes();contactsAndCover();demolitionAndPersistence();clearPlateAndBounds();externalRules();
 std::cout<<"PASS Quake directions, landing cadence, swept waves, cover, cache adaptation, plates and external rules\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
