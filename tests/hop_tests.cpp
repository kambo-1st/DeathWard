#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.005f){return std::abs(a-b)<eps;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,12,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s,int type=29){return s.spawnMonster(monsterId(type),{0,.85f,0});}
void launch(Simulation &s,EntityId id){for(int i=0;i<360&&!s.findEnemy(id)->targetHop->airborne;++i)tick(s);check(s.findEnemy(id)->targetHop->airborne,"configured hopper launches");}
void hit(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical){Event event;event.type=EventType::Damage;event.target=id;event.damage=amount;event.damageKind=kind;s.queueRoot(event);s.drainEvents();}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("dw-hoppers-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(root);for(auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());std::ifstream in(root/"hops.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(root);}
    std::shared_ptr<const MechanicsLibrary> load(std::string from,std::string to){auto s=original;auto at=s.find(from);check(at!=s.npos,"external fixture exists");s.replace(at,from.size(),to);std::ofstream(root/"hops.mechanics")<<s;return MechanicsLibrary::load(root);}
};
void timingAndSelection() {
    for(int type:{29,54}) {
        auto s=fixture();const auto id=spawn(s,type);auto &e=*s.findEnemy(id);const auto &p=*s.content->targetHop(e.monster);
        check(near(e.hp,type==29?32:64)&&!s.content->hop(e.monster),"source HP and native destination controller");
        tick(s,4);check(e.targetHop->frame==0&&e.targetHop->pursuing,"no arbitrary initial idle or cooldown");
        const auto target=e.targetHop->destination;
        check(type==29?near(e.targetHop->bonus,0):(e.targetHop->bonus>=0&&e.targetHop->bonus<=50),"normal zero bonus vs Flaming one uniform0..50");
        tick(s,2*(p.jumpFrame-1));check(!e.targetHop->airborne&&e.targetHop->frame==p.jumpFrame-1,"native preparation interval");
        tick(s,2);check(e.targetHop->airborne&&e.targetHop->hops==1,"normalJump4 or FlamingJump5");
        s.player.position={-25,.85f,-25};tick(s,2*(p.landFrame-p.jumpFrame));
        check(e.targetHop->landings==1&&e.targetHop->frame==p.landFrame&&e.targetHop->airborne,"current Land17/18 retains accumulatedJump collision until animation ends");
        check(distance(e.targetHop->destination,target)<.001f,"mid-hop player movement cannot retarget destination");
        tick(s,2*(26-p.landFrame));check(!e.targetHop->airborne&&near(e.position.y,.85f),"Hop26 restores grounded collision");
        check(s.stats.projectiles==0&&s.hazards.empty()&&s.enemies.size()==1,"no invented fire trails, projectiles or offspring");
        auto far=fixture();far.player.position={0,.85f,30};const auto f=spawn(far,type);tick(far,4);check(!far.findEnemy(f)->targetHop->pursuing,"far player causes native wandering");
    }
    auto boundary=fixture();boundary.player.position={0,.85f,13};auto id=spawn(boundary);tick(boundary,4);check(!boundary.findEnemy(id)->targetHop->pursuing,"ordinary acquisition is strictly below130 units");
    auto flame=fixture();flame.player.position={0,.85f,13};id=spawn(flame,54);tick(flame,4);check(flame.findEnemy(id)->targetHop->pursuing,"Flaming random bonus expands acquisition beyond ordinary boundary");
    Pack pack;auto noLead=pack.load("1.8 10 5","1.8 10 0");
    auto lead=fixture(),plain=fixture(noLead);lead.player.position=plain.player.position={-.6f,.85f,8};
    auto l=spawn(lead,54),n=spawn(plain,54);
    for(int i=0;i<4;++i){Input in;in.movement={1,0,0};lead.step(in);plain.step(in);}
    const auto &a=*lead.findEnemy(l)->targetHop,&b=*plain.findEnemy(n)->targetHop;
    check(near(a.bonus,b.bonus)&&a.destination.x>b.destination.x,"native five-frame velocity lead changes snapped pursuit destination with same RNG");
    std::cout<<"PASS source health, Hop26 events, zero/random bonus, strict acquisition and five-frame prediction\n";
}
void morphAndInterruptions() {
    auto s=fixture();auto id=spawn(s);hit(s,id,8);launch(s,id);tick(s,10);auto before=*s.findEnemy(id);s.findEnemy(id)->summoner=77;
    s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=1;
    hit(s,id,1000,DamageKind::Flame);auto &e=*s.findEnemy(id);
    check(e.monster==monsterId(54)&&near(e.hp,48)&&near(e.maxHp,64)&&e.id==id&&e.summoner==77,"native flame morph preserves health fraction, identity and owner");
    check(e.targetHop->transformedFlight&&e.targetHop->frame==before.targetHop->frame&&distance(e.velocity,before.velocity)<.001f&&distance(e.targetHop->destination,before.targetHop->destination)<.001f,"air morph retains phase, committed target and momentum");
    check(e.state==EnemyState::Stunned&&s.stats.kills==0&&s.moneyPickups.empty(),"morph retains stun and grants no rewards");
    s.player.position={-25,.85f,-25};tick(s,70);
    check(!e.targetHop->airborne&&!e.targetHop->transformedFlight&&!s.arena.blocked(e.position,e.radius),"old source-flight snapshot retires after safe landing");
    hit(s,id,12,DamageKind::Burning);check(near(e.hp,36),"burning remains a damage channel");hit(s,id,1000,DamageKind::Flame);check(near(e.hp,36),"further flame contact is harmless");
    auto saved=fixture();id=spawn(saved,54);launch(saved,id);tick(saved,8);before=*saved.findEnemy(id);saved.enterRoom(1);tick(saved,30);saved.enterRoom(0);
    check(saved.findEnemy(id)->targetHop->frame==before.targetHop->frame&&distance(saved.findEnemy(id)->position,before.position)<.001f,"room re-entry preserves exact committed hop pose");
    auto fire=fixture();id=spawn(fire);launch(fire,id);tick(fire,10);auto at=fire.findEnemy(id)->position;at.y=.85f;
    fire.addFire(at,2,1,10,true,false);tick(fire,2);check(fire.findEnemy(id)->monster==monsterId(29),"physical airborne body clears low fire exposure");
    auto dead=fixture();dead.debugScenario=false;id=spawn(dead);launch(dead,id);hit(dead,id,1000);tick(dead,4);
    check(dead.roomClear&&dead.stats.kills==1&&dead.projectiles.empty()&&dead.enemies.empty(),"ordinary airborne death resolves one threat without offspring");
    std::cout<<"PASS in-flight flame morph, health fraction, stun, fire/burning distinction, suspension and death\n";
}
void terrainAndDamage() {
    for(int type:{29,54}) {
        auto s=fixture();s.arena.obstacles.push_back({{-3,0,3},{3,2,5}});s.arena.rebuildWalls();auto id=spawn(s,type);float peak=0;bool crossed=false;
        for(int i=0;i<180;++i){tick(s);const auto &e=*s.findEnemy(id);peak=std::max(peak,e.position.y);crossed|=e.position.z>5;check(!sphereBox(e.position,e.radius,s.arena.obstacles.front()),"physical destination hop clears cover");}
        check(crossed&&peak>3,"both source forms traverse cover");
        auto water=fixture();auto t=std::make_shared<CanyonTerrain>();t->x=t->z=-40;t->step=1;t->width=t->depth=81;t->heights.assign(81*81,0);t->boundaryHeights=t->heights;
        t->river={{{-40,0,4},1,0},{{40,0,4},1,80}};t->riverKind=CanyonRiverKind::Interior;for(int x=0;x<81;++x)t->heights[size_t(44*81+x)]=-1.5f;
        water.arena.canyon=t;id=spawn(water,type);bool over=false;
        for(int i=0;i<180;++i){tick(water);const auto &e=*water.findEnemy(id);if(t->waterBlocked(e.position)){over=true;check(e.targetHop->airborne&&e.position.y>1,"water crossed in actual airborne interval");}}
        check(over&&!water.arena.blocked(water.findEnemy(id)->position,.6f),"both source forms reach legal river bank");
        auto gate=fixture();id=spawn(gate,type);tick(gate,4);gate.arena.boundaryWalls={{{-40,-1,3},{40,12,3.1f}}};gate.arena.rebuildWalls();
        for(int i=0;i<180;++i){tick(gate);check(gate.findEnemy(id)->position.z<3,"newly closed full-height gate remains impassable");}
        auto shot=fixture();id=spawn(shot,type);launch(shot,id);tick(shot,8);auto body=shot.findEnemy(id)->position;auto hp=shot.findEnemy(id)->hp;
        Event e;e.position=e.origin=body;e.direction={1,0,0};e.speed=.1f;AttackSpec spec;spec.damage=10;spec.speed=.1f;spec.radius=.5f;e.attack=spec;shot.queueRoot(e);shot.drainEvents();tick(shot);
        check(shot.findEnemy(id)->hp<hp,"ordinary hop can be hit at actual elevated body");
    }
    std::cout<<"PASS real cover, deep river, closed gates and elevated projectile collision\n";
}
void configAndPlacement() {
    Pack pack;
    for(const auto &[from,to]:std::array<std::pair<std::string,std::string>,3>{{{"1.8 10 5","1.8 10 -1"},{"1.8 10 5","1.8 10 61"},{"26 5 18","26 18 18"}}}) {
        bool rejected=false;try{pack.load(from,to);}catch(...){rejected=true;}check(rejected,"invalid lead or phase ordering rejects snapshot");
    }
    auto changed=pack.load("50 0 130","25 0 130");check(near(changed->targetHop(monsterId(54))->bonusA,25)&&near(defaultMechanics()->targetHop(monsterId(54))->bonusA,50),"reload preserves existing library snapshot");
    std::array<bool,2> found{};
    for(uint64_t seed=0;seed<128&&(!found[0]||!found[1]);++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(29)||e.monster==monsterId(54)) {
            const auto v=size_t(e.monster.type==54);check(e.targetHop&&near(e.maxHp,v?64:32),"ordinary seeded source-health body");
            if(!found[v])std::cout<<"NATURAL_HOPPER type="<<e.monster.type<<" seed="<<seed<<" floor=0 room="<<room<<'\n';found[v]=true;
        }
    }
    check(found[0]&&found[1],"both normal and flaming reachable in early ordinary rooms");
    for(int type:{29,54}) {
        auto s=fixture();auto id=spawn(s,type);launch(s,id);s.godMode=false;s.player.position={0,.85f,14};int frames=0;
        for(;frames<1800&&s.findEnemy(id)&&s.findEnemy(id)->alive&&!s.dead;++frames){Input in;in.fire=true;in.aim=s.findEnemy(id)->position;s.step(in);}
        check(!s.dead&&s.stats.kills==1,"default100HP/24damage starting kit kills either form");
        std::cout<<"HOPPER_STARTING_KIT type="<<type<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<'\n';
    }
}
}
int main(){try{timingAndSelection();morphAndInterruptions();terrainAndDamage();configAndPlacement();std::cout<<"PASS source ordinary and Flaming Hopper\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
