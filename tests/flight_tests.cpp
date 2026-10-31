#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation fixture() {
    Simulation s(1866,1,{});s.enemies.clear();s.arena=Arena{};
    s.arena.bounds={{-20,-1,-20},{20,5,20}};
    for(auto &room:s.arena.rooms){room.bounds=s.arena.bounds;room.center={0,0,0};}
    s.arena.boundaryWalls={{{-21,-1,-21},{-20,8,21}},{{20,-1,-21},{21,8,21}},
        {{-21,-1,-21},{21,8,-20}},{{-21,-1,20},{21,8,21}}};
    s.arena.rebuildWalls();s.rooms.resize(s.arena.rooms.size());
    s.player.position={0,.85f,8};s.debugScenario=true;s.roomClear=false;s.godMode=true;
    return s;
}
void tick(Simulation &s,int count){for(int i=0;i<count;++i)s.step({});}
void kill(Simulation &s,EntityId id,float damage) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;s.queueRoot(e);s.drainEvents();s.step({});
}
void cover(Simulation &s) {
    s.arena.obstacles.push_back({{-1,0,-1},{1,2,1}});s.arena.rebuildWalls();
}
void water(Simulation &s) {
    auto field=std::make_shared<CanyonTerrain>();field->x=field->z=-20;field->step=1;field->width=field->depth=41;
    field->heights.assign(41*41,0);field->boundaryHeights=field->heights;
    field->river={{{-20,0,6},2,0},{{20,0,6},2,40}};field->riverKind=CanyonRiverKind::Interior;
    for(int z=24;z<=28;++z)for(int x=0;x<41;++x)field->heights[size_t(z*41+x)]=-1.5f;
    s.arena.canyon=field;
}
void movementAndGates() {
    auto s=fixture();cover(s);
    const auto id=s.spawnMonster(monsterId(18),{0,.85f,-6});float peak=0;
    for(int n=0;n<240;++n) {
        s.step({});const auto &e=*s.findEnemy(id);peak=std::max(peak,e.position.y);
        check(!sphereBox(e.position,e.radius,s.arena.obstacles.front()),"flying hitbox must stay above physical cover");
        check(!s.arena.flightBlocked(e.position,e.radius,s.room),"flying body stays inside its movement domain");
    }
    check(peak>=2.84f&&s.findEnemy(id)->position.z>6,"Attack Fly crosses interior cover on a direct pursuit route");
    check(!s.arena.clear({0,.85f,-6},{0,.85f,6},.38f),"cover still blocks ground movement");
    s.player.position={0,.85f,100};tick(s,600);
    check(s.findEnemy(id)->position.z<=19.62f,"fly cannot chase player out of its active room");

    Passage gate;gate.rooms={0,1};gate.sealed[0]=true;
    gate.gates[0]={{-20,0,2},{20,4,2.3f}};gate.gates[1]={{-20,0,18},{20,4,18.3f}};
    s.arena.passages.push_back(gate);s.arena.rebuildWalls();
    const Vector3 from{0,10,-4},to{0,10,5};
    check(!s.arena.flightClear(from,to,.38f,0),"sealed gate blocks flight even above its mesh");
    check(planarDistance(s.arena.fly(from,sub(to,from),.38f,0),from)<.001f,"large flight step cannot tunnel through gate");
    s.arena.passages[0].sealed[0]=false;s.arena.rebuildWalls();
    check(s.arena.flightClear(from,to,.38f,0),"opening gate refreshes flight collision");
    // A partial barrier requires a flight route around it, not a ground route over cover.
    s.arena.boundaryWalls.push_back({{-2,-1,2},{2,8,3}});s.arena.rebuildWalls();
    const auto path=s.arena.flightPath(from,to,.38f,0);check(!path.empty(),"flight routes around an interior solid barrier");
    auto p=from;for(auto next:path){check(s.arena.flightClear(p,next,.38f,0),"each smoothed flight path segment is collision safe");p=next;}
    std::cout<<"FLIGHT_COVER peak="<<peak<<" safe_path_points="<<path.size()<<'\n';
}
void riversAndOffspring() {
    auto s=fixture();water(s);s.player.position={0,.85f,12};
    check(s.arena.canyon->waterBlocked({0,.85f,6}),"test channel contains deep water");
    check(!s.arena.clear({0,.85f,0},{0,.85f,12},.38f)&&s.arena.flightClear({0,.85f,0},{0,.85f,12},.38f,0),
          "flight crosses deep water while grounded collision remains blocked");
    const auto id=s.spawnMonster(monsterId(18),{0,.85f,0});tick(s,240);
    check(s.findEnemy(id)->position.z>10&&s.findEnemy(id)->position.y<.86f,"Attack Fly crosses the river without sinking or taking a ford detour");
    int landBirths=0;
    for(int n=0;n<16;++n) {
        auto drowned=fixture();water(drowned);
        const auto root=drowned.spawnMonster(monsterId(25,2),{0,.85f,6});
        drowned.combatRng=Random(uint64_t(n));kill(drowned,root,1000);
        check(drowned.livingEnemies()==0,"Drowned Boom Fly cannot relocate a ground offspring from an illegal water death point");
        auto land=fixture();const auto control=land.spawnMonster(monsterId(25,2),{0,.85f,6});
        land.combatRng=Random(uint64_t(n));kill(land,control,1000);
        landBirths+=land.livingEnemies();
    }
    check(landBirths>0&&landBirths<16,"same death/RNG sample still produces probabilistic ground offspring on legal land");
    std::cout<<"FLIGHT_OFFSPRING water_births=0 land_births="<<landBirths<<" samples=16\n";
    auto moter=fixture();cover(moter);const auto root=moter.spawnMonster(monsterId(80),{0,.85f,0});kill(moter,root,72);
    check(moter.livingEnemies()==2,"Moter still creates both Attack Flies over cover");
    for(const auto &e:moter.enemies)check(e.monster==monsterId(18)&&e.position.y>2&&
        !moter.arena.flightBlocked(e.position,e.radius,0),"flying offspring retain elevated safe placement");
}
void combatElevation() {
    for(bool arrows:{false,true}) {
        auto s=fixture();cover(s);const auto root=s.spawnMonster(monsterId(13),{0,.85f,0});
        Input input;input.fire=true;input.aim=s.findEnemy(root)->position;
        if(arrows)input.aimDirection=Vector3{0,0,-1};
        s.step(input);
        check(!s.projectiles.empty()&&s.projectiles.front().velocity.y>0,"mouse and arrows shoot toward real airborne hitbox");
        check(std::abs(s.projectiles.front().velocity.x)<.00001f,"elevation assistance preserves arrow horizontal bearing");
        tick(s,35);check(!s.findEnemy(root),"elevated Fly can be killed through its visible body");
    }
    auto shooter=fixture();cover(shooter);shooter.godMode=false;
    const auto id=shooter.spawnMonster(monsterId(14),{0,.85f,0});shooter.findEnemy(id)->cooldown=0;
    tick(shooter,110);check(shooter.player.hp<StartingHealth,"elevated graph shooter can hit ground-level player");
    auto home=fixture();cover(home);home.spawnMonster(monsterId(13),{0,.85f,0});home.grant(ItemId::Lodestone);
    Input input;input.fire=true;input.aim={0,.85f,0};home.step(input);tick(home,2);
    check(!home.projectiles.empty()&&home.projectiles.front().velocity.y>0,"homing steers vertically toward elevated targets");
    std::cout<<"FLIGHT_COMBAT shooter_damage="<<StartingHealth-shooter.player.hp<<" mouse_arrow_hits=2\n";
}
void seededCanyons() {
    int rocks=0,waterCells=0,cliffs=0;bool interior=false,boundary=false;
    for(uint64_t seed:{0,1,42,1866}) {
        Arena arena(seed,MissionTheme::Canyon);
        interior|=arena.canyon->riverKind==CanyonRiverKind::Interior;
        boundary|=arena.canyon->riverKind==CanyonRiverKind::Boundary;
        for(int r=0;r<arena.roomCount();++r) {
            const auto &room=arena.rooms[size_t(r)];
            for(const auto &rock:room.obstacles) {
                auto p=mul(add(rock.min,rock.max),.5f);p.y=.85f;
                if(arena.canyon->height(p.x,p.z)<.3f)continue;
                check(!arena.flightBlocked(p,.38f,r),"seeded interior outcrop is flyable");
                check(arena.flightHeight(p,.38f)>arena.canyon->height(p.x,p.z)+.8f,"seeded fly altitude clears terrain rock");++rocks;
            }
            for(float z=room.bounds.min.z+1;z<room.bounds.max.z-1;z+=2)
                for(float x=room.bounds.min.x+1;x<room.bounds.max.x-1;x+=2) {
                    Vector3 p{x,.85f,z};
                    if(arena.canyon->height(x,z)>4) {check(arena.flightBlocked(p,.38f,r),"high enclosing canyon remains solid to flight");++cliffs;}
                    if(arena.canyon->waterBlocked(p)&&!arena.flightBlocked(p,.38f,r))++waterCells;
                }
        }
        for(int r:arena.canyon->riverRooms)if(arena.canyon->riverKind==CanyonRiverKind::Boundary) {
            auto p=arena.rooms[size_t(r)].center;const auto &area=arena.rooms[size_t(r)].bounds;
            const auto outward=arena.canyon->riverOutward;
            p=add(p,mul(outward,std::max(area.max.x-area.min.x,area.max.z-area.min.z)));
            check(arena.flightBlocked(p,.38f,r),"boundary river never permits flight into backdrop or adjacent rooms");
        }
    }
    check(rocks>30&&waterCells>10&&cliffs>10&&interior&&boundary,"real seeds cover outcrops, both river policies and cliffs");
    std::cout<<"FLIGHT_SEEDED rocks="<<rocks<<" water_cells="<<waterCells<<" cliffs="<<cliffs<<'\n';
}
}
int main(){try{movementAndGates();riversAndOffspring();combatElevation();seededCanyons();std::cout<<"PASS flight collision, elevation, combat and seeded terrain\n";}
catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
