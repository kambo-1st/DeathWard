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
    s.player.position={0,.85f,8};s.debugScenario=true;s.godMode=true;s.roomClear=false;return s;
}
EntityId maw(Simulation &s,int type=235,Vector3 at={0,.85f,0}) {
    const auto id=s.spawnMonster(monsterId(type),at);check(id!=0,"Maw has a real configured definition");return id;
}
void ticks(Simulation &s,int n,Input input={}){for(int i=0;i<n;++i)s.step(input);}
void damage(Simulation &s,EntityId id,bool execution=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.execution=execution;s.queueRoot(e);s.drainEvents();
}
void pullAndInput() {
    auto normal=fixture(),broken=fixture();const auto id=maw(normal);maw(broken,236);
    ticks(normal,60);ticks(broken,60);
    check(normal.player.position.z<7&&normal.player.position.z>6,"Normal Maw actually pulls an idle player");
    check(broken.player.position.z<normal.player.position.z-1,"Broken Maw has stronger active attraction");
    check(normal.stats.projectiles==0&&broken.stats.projectiles==0&&normal.roomThreats()==0,"Attractors emit no shots and do not seal combat");
    check(normal.findEnemy(id)->hp==320&&normal.player.hp==100,"Source HP conversion and no body-contact damage");
    damage(normal,id);check(normal.findEnemy(id)->alive&&normal.findEnemy(id)->hp==320,"Ordinary damage cannot destroy Maw");
    for(bool dodge:{false,true}) {
        auto s=fixture();maw(s,236);Input input;input.movement={0,0,1};input.dodge=dodge;ticks(s,30,input);
        check(s.player.position.z>9,"Keyboard movement and dodge can counter the strongest configured force");
    }
    auto mouse=fixture();maw(mouse,236);Input click;click.moveTarget=Vector3{0,.85f,18};mouse.step(click);ticks(mouse,120);
    check(mouse.player.position.z>13,"Click-to-move continues toward its target against attraction");
    auto still=fixture();maw(still);Input stand;stand.standStill=true;ticks(still,30,stand);
    check(still.player.position.z<7.5f,"Stand-and-fire does not negate physical suction");
    std::cout<<"MAW_INPUT normal_z="<<normal.player.position.z<<" broken_z="<<broken.player.position.z<<" keyboard=1 dodge=1 mouse=1 stationary=1 no_shots=1\n";
}
void cycleAndLifecycle() {
    auto s=fixture();const auto id=maw(s,236);ticks(s,239);check(s.findEnemy(id)->statuePullActive,"Broken Maw active before four seconds");
    ticks(s,1);check(!s.findEnemy(id)->statuePullActive,"Broken Maw closes at four seconds");
    s.player.position={0,.85f,8};ticks(s,150);check(s.player.position.z==8,"Inactive half-cycle applies no player force");
    const auto phase=s.findEnemy(id)->statuePhase;s.enterRoom(1);ticks(s,30);s.enterRoom(0);
    check(s.findEnemy(id)->statuePhase==phase&&!s.findEnemy(id)->statuePullActive,"Room re-entry retains inactive phase; inactive rooms do not advance it");
    ticks(s,90);check(s.findEnemy(id)->statuePullActive&&s.player.position.z<8,"Attraction resumes after the next four seconds");
    s.clearRoom();s.player.position={0,.85f,8};ticks(s,10);check(s.player.position.z<8,"Ordinary room clear does not remove Maw suction");
    s.rooms[0].plates={{{-5,.85f,5},false}};s.player.position={-5,.85f,5};ticks(s,1);
    check(s.rooms[0].plates[0].pressed&&s.findEnemy(id)->statueDisabled&&!s.findEnemy(id)->statuePullActive,"Real plate contact disables attraction");
    const auto at=s.player.position;ticks(s,600);check(distance(at,s.player.position)==0,"Plate stops suction through later cycle changes");
    s.enterRoom(1);s.enterRoom(0);ticks(s,1);check(s.findEnemy(id)->statueDisabled,"Pressed plate remains effective on re-entry");
    auto killed=fixture();const auto dead=maw(killed);damage(killed,dead,true);ticks(killed,60);
    check(killed.player.position.z==8&&killed.stats.kills==0,"Exceptional kill removes force without ordinary rewards");
    killed.enterRoom(1);killed.enterRoom(0);ticks(killed,1);check(killed.findEnemy(dead)->alive&&killed.player.position.z<8,"Uncleared re-entry respawns the physical Maw");
    std::cout<<"MAW_LIFECYCLE four_seconds=1 inactive_phase=1 active_resume=1 clear_persistence=1 plate=1 exceptional_respawn=1\n";
}
void shoot(Simulation &s,bool hostile,float height=.85f,bool ballistic=false) {
    Event e;e.position=e.origin={6,height,-6};e.direction={0,0,1};e.speed=6;e.damage=24;e.hostile=hostile;
    if(ballistic){e.projectileKind=ProjectileKind::Ipecac;e.projectileGravity=12;e.projectileBlastDamage=20;e.projectileBlastRadius=2;}
    s.queueRoot(e);s.drainEvents();
}
void projectilesAndBounds() {
    auto s=fixture();maw(s);s.player.position={-15,.85f,15};shoot(s,false);shoot(s,true);ticks(s,30);
    check(s.projectiles.size()==2,"Both test shots remain in flight");
    const auto &a=s.projectiles[0];const auto &b=s.projectiles[1];
    check(a.velocity.x<-.5f&&b.velocity.x<-.5f&&a.position.x<6&&b.position.x<6,"Player and hostile shots both bend toward Maw");
    check(distance(a.position,b.position)<.0001f&&a.velocity.y==0&&b.velocity.y==0,"Faction does not alter force and planar pull preserves height");
    s.rooms[0].plates={{{-5,.85f,5},false}};s.player.position={-5,.85f,5};const auto velocity=a.velocity;ticks(s,1);
    check(distance(velocity,s.projectiles[0].velocity)<.0001f,"Plate shutdown stops further acceleration in the same tick");
    auto high=fixture();maw(high);shoot(high,false,6);ticks(high,30);
    check(high.projectiles.size()==1&&high.projectiles[0].velocity.x==0,"Configured vertical extent excludes distant overhead shots");
    auto gravity=fixture(),control=fixture();maw(gravity);shoot(gravity,false,3,true);shoot(control,false,3,true);ticks(gravity,5);ticks(control,5);
    check(gravity.projectiles.size()==1&&control.projectiles.size()==1&&std::abs(gravity.projectiles[0].position.y-control.projectiles[0].position.y)<.0001f,"Attraction preserves real ballistic gravity");
    auto wall=fixture();maw(wall,236);wall.arena.boundaryWalls.push_back({{-10,-1,3},{10,8,4}});wall.arena.rebuildWalls();ticks(wall,600);
    check(wall.player.position.z>=4.47f&&!wall.arena.blocked(wall.player.position,.48f),"Suction cannot pull player through solid terrain");
    auto corridor=fixture();maw(corridor);corridor.arena.rooms[0].bounds={{-5,-1,-5},{5,8,5}};ticks(corridor,60);
    check(corridor.player.position.z==8,"Active room Maw does not pull a player outside that room");
    auto opposed=fixture();maw(opposed,235,{-8,.85f,8});maw(opposed,235,{8,.85f,8});ticks(opposed,60);
    check(distance(opposed.player.position,{0,.85f,8})<.0001f,"Equal opposing fields cancel");
    auto stack=fixture();for(int n=0;n<6;++n)maw(stack,236,{float(n)*.1f,.85f,0});const auto start=stack.player.position;stack.step({});
    check(distance(start,stack.player.position)<=4*Tick+.0001f,"Combined player attraction stays bounded by strongest configured source");
    std::cout<<"MAW_PROJECTILES both_teams=1 current_velocity=1 height=1 gravity=1 terrain=1 corridor=1 opposing_fields=1 aggregate_limit=1\n";
}
void externalRules() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-maw-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);
    for(const auto &p:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(p.path().extension()==".mechanics")std::filesystem::copy_file(p.path(),dir/p.path().filename());
    const auto file=dir/"statues.mechanics";std::ifstream in(file);std::string text((std::istreambuf_iterator<char>(in)),{});in.close();
    const std::string original="statue_attraction 235.0.0 2 12 40 4 0 0";
    const auto at=text.find(original);check(at!=std::string::npos,"External fixture source row exists");
    text.replace(at,original.size(),"statue_attraction 235.0.0 4 24 40 4 0 0");std::ofstream(file)<<text;
    auto prior=fixture(),changed=fixture(MechanicsLibrary::load(dir));maw(prior);maw(changed);ticks(prior,60);ticks(changed,60);
    check(changed.player.position.z<prior.player.position.z-1&&prior.content->fingerprint()!=changed.content->fingerprint(),"File-only strength changes reach actual movement in new snapshots");
    check(defaultMechanics()->statue(monsterId(235))->playerPull==2,"Existing immutable snapshot retains its original force");
    std::filesystem::remove_all(dir);
    std::cout<<"MAW_CONFIG actual_force=1 snapshot_isolation=1\n";
}
}
int main(){try{pullAndInput();cycleAndLifecycle();projectilesAndBounds();externalRules();
 std::cout<<"PASS Maw suction, alternating cycle, both projectile teams, collision and configured snapshots\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
