#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.003f){return std::abs(a-b)<eps;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("dw-trite-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(root);for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());std::ifstream in(root/"trites.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(root);}
    void replace(std::string from,std::string to){auto text=original;auto at=text.find(from);check(at!=text.npos,"configuration fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"trites.mechanics")<<text;}
};
Simulation fixture(uint64_t seed=1866,std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(seed,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,12,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(29,1),{0,.85f,0});}
auto &state(Simulation &s,EntityId id){return *s.findEnemy(id)->targetHop;}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void launch(Simulation &s,EntityId id){for(int i=0;i<360&&!state(s,id).airborne;++i)tick(s);check(state(s,id).airborne,"Trite takes off");}
void sourceTimingAndSelection() {
    auto s=fixture();auto id=spawn(s);check(near(s.findEnemy(id)->hp,32),"10 source HP converted once");
    tick(s,32);check(!state(s,id).targetReady&&state(s,id).counter==15,"15 idle frames before selection");
    tick(s,2);check(state(s,id).targetReady&&state(s,id).frame==0&&state(s,id).pursuing,"near target selected after threshold");
    auto destination=state(s,id).destination;
    check(destination.z>=8&&near(std::remainder(destination.x-2,4),0)&&near(std::remainder(destination.z-2,4),0),"overshoot candidate snapped to four-unit local grid");
    tick(s,6);check(state(s,id).frame==3&&!state(s,id).airborne,"preparation before Jump4");
    tick(s,2);check(state(s,id).frame==4&&state(s,id).airborne&&state(s,id).hops==1,"Jump4 changes collision mode");
    s.player.position={-60,.85f,-60};tick(s,28);
    check(state(s,id).frame==18&&state(s,id).landings==1&&state(s,id).airborne,"Land18 event does not clear native Jump collision interval");
    check(distance(state(s,id).destination,destination)<.001f&&state(s,id).targetReady,"destination remains committed through landing event");
    tick(s,16);check(!state(s,id).airborne&&state(s,id).frame==-1,"Hop26 restores grounded collision");
    check(s.stats.projectiles==0&&s.projectiles.empty()&&s.enemies.size()==1,"ordinary Trite has no shots or offspring");
    auto far=fixture();far.player.position={65,.85f,65};auto other=spawn(far);tick(far,34);
    check(state(far,other).targetReady&&!state(far,other).pursuing,"far target leads to wandering rather than unconditional pursuit");
    check(planarDistance({0,.85f,0},state(far,other).destination)<=24.4f,"wander95+bonus bounded by native120 bonus and grid snapping");
    auto same=fixture();auto repeat=spawn(same);tick(same,34);check(distance(state(same,repeat).destination,destination)<.001f,"seeded target law repeatable");
    Pack pack;pack.replace("50 70 130","0 0 130");auto exact=fixture(1866,MechanicsLibrary::load(pack.root));exact.player.position={0,.85f,13};auto boundary=spawn(exact);tick(exact,34);
    check(!state(exact,boundary).pursuing,"range boundary is strict, not inclusive");
}
void sourceMomentum() {
    for(bool air:{false,true}) {
        auto s=fixture();s.player.position={-60,.85f,-60};auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=state(s,id);
        r.initialized=true;r.targetReady=true;r.frame=air?3:0;r.clock=Tick;r.destination={20,.85f,0};r.lastGround=e.position;
        e.velocity={6,0,0};tick(s);
        check(near(state(s,id).momentum.x,air?8.4f:2.1f),"source delta force, ground factor and .7 post-retention; no global aggression scaling");
        check(near(s.findEnemy(id)->velocity.x,air?25.2f:6.3f),"native velocity converts by scale times30");
    }
    auto nearTarget=fixture();nearTarget.player.position={-60,.85f,-60};auto id=spawn(nearTarget);auto &e=*nearTarget.findEnemy(id);auto &r=state(nearTarget,id);
    r.initialized=true;r.targetReady=true;r.frame=0;r.clock=Tick;r.destination={2,.85f,0};e.velocity={6,0,0};tick(nearTarget);
    check(near(state(nearTarget,id).momentum.x,2.1f),"near-range branch normalizes even grounded direction");
}
void terrainAndLifecycle() {
    auto s=fixture();s.arena.obstacles.push_back({{-3,0,3},{3,2,5}});s.arena.rebuildWalls();auto id=spawn(s);launch(s,id);
    float peak=0;bool crossed=false;
    for(int i=0;i<80;++i){tick(s);const auto &e=*s.findEnemy(id);peak=std::max(peak,e.position.y);crossed|=e.position.z>5;
        check(!sphereBox(e.position,e.radius,s.arena.obstacles.front()),"physical airborne body clears cover");}
    check(crossed&&peak>3,"source steering crosses cover with real elevation");
    auto water=fixture();auto terrain=std::make_shared<CanyonTerrain>();
    terrain->x=terrain->z=-80;terrain->step=1;terrain->width=terrain->depth=161;
    terrain->heights.assign(161*161,0);terrain->boundaryHeights=terrain->heights;
    terrain->river={{{-80,0,4},1,0},{{80,0,4},1,160}};terrain->riverKind=CanyonRiverKind::Interior;
    for(int x=0;x<161;++x)terrain->heights[size_t(84*161+x)]=-1.5f;
    water.arena.canyon=terrain;auto swimmer=spawn(water);bool overWater=false;
    check(!water.arena.clear({0,.85f,0},{0,.85f,8},.5f),"river blocks grounded direct travel");
    for(int i=0;i<160;++i){tick(water);const auto &e=*water.findEnemy(swimmer);
        if(terrain->waterBlocked(e.position)){overWater=true;check(e.targetHop->airborne&&e.position.y>1,"water crossing uses physical airborne interval");}}
    check(overWater&&!water.arena.blocked(water.findEnemy(swimmer)->position,.5f),"Trite crosses deep water and reaches legal ground");
    auto walls=fixture();walls.arena.boundaryWalls={{{-80,-1,3},{80,12,3.1f}}};walls.arena.rebuildWalls();auto w=spawn(walls);
    for(int i=0;i<300;++i){tick(walls);check(walls.findEnemy(w)->position.z<3,"full room wall never crossed");}
    check(state(walls,w).hops>0,"target selection needs no line of sight, physical wall still blocks motion");
    auto prepare=fixture();auto preparing=spawn(prepare);tick(prepare,34);prepare.findEnemy(preparing)->state=EnemyState::Stunned;prepare.findEnemy(preparing)->stateTime=1;
    tick(prepare,30);check(!state(prepare,preparing).targetReady&&!state(prepare,preparing).airborne,"stun cancels preparation before takeoff");
    auto saved=fixture();auto resident=spawn(saved);launch(saved,resident);tick(saved,8);const auto before=state(saved,resident);const auto position=saved.findEnemy(resident)->position;
    saved.enterRoom(1);tick(saved,30);saved.enterRoom(0);
    check(saved.findEnemy(resident)&&state(saved,resident).frame==before.frame&&distance(saved.findEnemy(resident)->position,position)<.001f,"room suspension preserves actual airborne pose and destination");
    auto stun=fixture();auto st=spawn(stun);launch(stun,st);stun.findEnemy(st)->state=EnemyState::Stunned;stun.findEnemy(st)->stateTime=2;
    tick(stun,60);check(!state(stun,st).airborne&&!stun.arena.blocked(stun.findEnemy(st)->position,.5f)&&stun.findEnemy(st)->state==EnemyState::Stunned,"local stun reaches legal ground before waiting");
    auto contact=fixture();contact.godMode=false;contact.player.position={0,.85f,0};spawn(contact);tick(contact);
    check(contact.player.hp<100,"grounded Trite deals contact damage");
    auto death=fixture();auto victim=spawn(death);launch(death,victim);Event hit;hit.type=EventType::Damage;hit.target=victim;hit.damage=1000;death.queueRoot(hit);death.drainEvents();tick(death,60);
    check(death.stats.kills==1&&death.roomThreats()==0&&death.stats.projectiles==0,"death resolves exactly one threat without a pending jump or children");
}
void configAndStartingKit() {
    Pack pack;
    for(auto values:{std::pair{"15 26 4 18","15 26 18 18"},std::pair{".05 .1 .7 .75",".05 .1 1 .75"}}) {
        pack.replace(values.first,values.second);bool rejected=false;try{MechanicsLibrary::load(pack.root);}catch(...){rejected=true;}check(rejected,"invalid event/retention configuration rejected");
    }
    pack.replace("50 70 130","25 35 130");auto changed=MechanicsLibrary::load(pack.root);
    check(near(defaultMechanics()->targetHop(monsterId(29,1))->bonusA,50)&&near(changed->targetHop(monsterId(29,1))->bonusA,25)&&changed->fingerprint()!=defaultMechanics()->fingerprint(),"configuration reload preserves old snapshot");
    auto s=fixture();auto id=spawn(s);launch(s,id);s.godMode=false;s.player.position={0,.85f,16};int frames=0;
    for(;frames<1800&&s.findEnemy(id)&&s.findEnemy(id)->alive&&!s.dead;++frames){Input in;in.fire=true;in.aim=s.findEnemy(id)->position;s.step(in);}
    check(!s.dead&&s.stats.kills==1,"default 100HP/24damage kit kills airborne Trite");
    std::cout<<"TRITE_STARTING_KIT seconds="<<frames*Tick<<" hp="<<s.player.hp<<'\n';
}
void placement() {
    bool found=false;
    for(uint64_t seed=0;seed<256&&!found;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount&&!found;++floor) {
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(29,1)) {
                check(e.targetHop&&near(e.hp,32)&&plan.profileOnFloor(floor).band<=2,"dedicated Trite and source HP appear in approved ordinary habitat");found=true;
                std::cout<<"NATURAL_TRITE seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
            }
        }
    }
    check(found,"ordinary Trite is seed-reachable");
}
}
int main(){try{sourceTimingAndSelection();sourceMomentum();terrainAndLifecycle();configAndStartingKit();placement();std::cout<<"PASS Trite destination law, source timing/inertia, terrain, lifecycle, config, starting kit and placement\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
