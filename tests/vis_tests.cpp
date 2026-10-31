#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float tolerance=.008f){return std::abs(a-b)<tolerance;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,20,100}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={70,.85f,70};return s;
}
void tick(Simulation &s,int frames=1){for(int i=0;i<frames;++i)s.step({},1.f/30);}
EntityId spawn(Simulation &s,int variant=0,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(39,variant),at);}
void damage(Simulation &s,EntityId id){Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=10000;s.queueRoot(hit);s.drainEvents();}
void prepareShot(Simulation &s,EntityId id,Vector3 heading={1,0,0}) {
    auto &e=*s.findEnemy(id);auto &r=*e.vis;r.initialized=true;r.heading=heading;
    r.attackFrame=s.content->vis(e.monster)->shootFrame-1;r.fired=false;e.velocity={};
}
void movementAndTiming() {
    for(int variant:{0,1,3}) {
        auto s=fixture();auto id=spawn(s,variant);auto &e=*s.findEnemy(id);const auto &p=*s.content->vis(e.monster);
        check(e.vis&&near(e.hp,variant==3?70.4f:80)&&near(e.hp,e.maxHp),"Vis source health and dedicated runtime");
        e.vis->hasDestination=true;e.vis->destination={60,.85f,0};tick(s);
        check(e.vis->initialized&&near(length(e.velocity),0),"first source frame initializes only");tick(s);
        check(near(e.velocity.x,.7f*.8f*3),"Vis force then common damping");
        s.player.position={20,.85f,e.position.z};
        for(int n=0;n<4&&e.vis->attackFrame<0;++n)tick(s);
        check(e.vis->attackFrame==0&&e.vis->heading.x==1,"cardinal aligned acquisition");
        const auto acquired=e.vis->ticks;
        s.player.position={e.position.x,.85f,-20};tick(s,p.shootFrame-1);
        check(s.hazards.empty()&&e.vis->attackFrame==p.shootFrame-1,"no beam before source Shoot event");tick(s);
        check(e.vis->ticks-acquired==uint64_t(p.shootFrame)&&e.vis->volleys==1&&s.hazards.size()==size_t(p.beams),
            "exact per-variant Shoot event and complete packet");
        check(s.hazards.front().ownedBeam->heading.x==1,"heading remains locked when player moves");
        for(const auto &h:s.hazards)check(h.delay==0&&near(h.duration,32.f/30)&&h.ownedBeam,
            "no second generic windup and correct active duration");
        if(p.beams>=2)check(s.hazards[1].ownedBeam->heading.x==-1,"opposing second beam");
        if(p.beams==4)check(s.hazards[2].ownedBeam->heading.z==1&&s.hazards[3].ownedBeam->heading.z==-1,"four distinct cardinal lanes");
        tick(s,p.attackFrames-p.shootFrame);
        check(e.vis->attackFrame==-1,"attack completes at source animation boundary");
    }
    auto diagonal=fixture();auto id=spawn(diagonal);diagonal.player.position={20,.85f,20};tick(diagonal,8);
    check(diagonal.findEnemy(id)->vis->attackFrame<0,"diagonal player does not trigger cardinal attack");
    auto vertical=fixture();auto vid=spawn(vertical);vertical.findEnemy(vid)->vis->hasDestination=true;
    vertical.findEnemy(vid)->vis->destination={0,.85f,60};tick(vertical,2);
    check(near(vertical.findEnemy(vid)->velocity.z,.7f*.8f*3),"same damping on both axes");
    auto cover=fixture();auto cid=spawn(cover);cover.player.position={15,.85f,0};
    cover.arena.obstacles.push_back({{5,0,-3},{6,4,3}});cover.arena.rebuildWalls();tick(cover,5);
    check(cover.findEnemy(cid)->vis->attackFrame>=0,"native acquisition is not a terrain line-of-sight check");
    std::cout<<"BODY variants3 hp80/80/70.4 force.7 retention.8 Shoot28/30/30 attack79/82/82 locked=1 cover_acquire=1\n";
}
void beamRules() {
    auto s=fixture();const auto owner=spawn(s);const auto immune=spawn(s,1,{8,.85f,0});
    const auto target=s.spawnMonster(monsterId(21),{12,.85f,0});
    for(auto id:{immune,target}){auto &e=*s.findEnemy(id);e.state=EnemyState::Stunned;e.stateTime=100;}
    s.findEnemy(target)->hp=s.findEnemy(target)->maxHp=1000;
    prepareShot(s,owner);tick(s);check(s.hazards.size()==1,"beam emitted");
    check(near(s.findEnemy(target)->hp,1000),"damage pulse waits for two source frames");tick(s);
    check(near(s.findEnemy(target)->hp,964.8f)&&near(s.findEnemy(immune)->hp,80),"source11 converts35.2 while same-type family is immune");
    check(near(s.hazards.front().origin.x,s.findEnemy(owner)->position.x+.6f),"horizontal beam origin offset");
    s.findEnemy(owner)->position.z=7;tick(s);
    check(near(s.hazards.front().origin.z,7)&&near(s.hazards.front().position.z,7),"beam follows moving owner without changing heading");
    check(near(s.findEnemy(target)->hp,964.8f),"moving beam leaves former target unharmed");
    auto cover=fixture();const auto cid=spawn(cover);prepareShot(cover,cid);
    cover.player.position={10,.85f,0};cover.godMode=false;
    cover.arena.obstacles.push_back({{5,0,-4},{6,5,4}});cover.arena.rebuildWalls();tick(cover,10);
    check(!cover.hazards.empty()&&cover.hazards.front().position.x<5&&near(cover.player.hp,100),"solid canyon cover clips beam and protects player");
    auto hit=fixture();const auto hid=spawn(hit);prepareShot(hit,hid);hit.player.position={10,.85f,0};hit.godMode=false;tick(hit,2);
    check(near(hit.player.hp,87.5f),"player uses source1 mapped to12.5 with existing combat multiplier");
    auto life=fixture();const auto lid=spawn(life);prepareShot(life,lid);tick(life,32);
    check(life.hazards.size()==1&&life.hazards.front().fadeAge<0&&life.hazards.front().ownedBeam->pulses==16,
        "32 active frames include sixteen two-frame damage pulses");
    tick(life);check(life.hazards.front().fadeAge>=0,"expiry begins visible fade");
    life.player.position={10,.85f,0};life.godMode=false;tick(life,18);
    check(life.hazards.empty()&&near(life.player.hp,100),"nineteen-frame expiry fade is harmless and removed");
    auto killed=fixture();const auto kid=spawn(killed);prepareShot(killed,kid);tick(killed);damage(killed,kid);tick(killed);
    check(killed.hazards.size()==1&&killed.hazards.front().fadeAge>=0,"owner death starts harmless fade");tick(killed,20);
    check(killed.hazards.empty(),"orphan beam cleaned up");
    std::cout<<"BEAM two_frame_damage=1 player12.5 monster35.2 same_type_immune=1 follows_owner=1 cover=1 frames32+19 owner_cleanup=1\n";
}
void capacityAndRooms() {
    auto s=fixture();const auto id=spawn(s,3);prepareShot(s,id);s.limits.hazards=3;tick(s,20);
    check(s.hazards.empty()&&s.findEnemy(id)->vis->attackFrame==30&&!s.findEnemy(id)->vis->fired,"quad packet retained atomically");
    s.limits.hazards=4;tick(s);check(s.hazards.size()==4&&s.findEnemy(id)->vis->volleys==1,"capacity release emits exactly once");
    s.enterRoom(1);check(s.hazards.empty(),"leaving room removes active beams");
    const auto previous=s.roomEnemies(0).front().vis->ticks;tick(s,10);s.enterRoom(0);
    check(s.findEnemy(id)&&s.findEnemy(id)->vis->ticks==previous,"inactive room suspends source state");
    auto stun=fixture();auto sid=spawn(stun);prepareShot(stun,sid);auto &e=*stun.findEnemy(sid);
    e.state=EnemyState::Stunned;e.stateTime=.5f;tick(stun,4);
    check(e.vis->attackFrame==-1&&stun.hazards.empty()&&near(length(e.velocity),0),"stun cancels pending windup");
    auto clear=fixture();clear.debugScenario=false;auto last=spawn(clear);prepareShot(clear,last);tick(clear);damage(clear,last);tick(clear);
    check(clear.roomClear&&!clear.hazards.empty()&&clear.hazards.front().fadeAge>=0,"last body death clears room without live damaging beam");
    std::cout<<"LIFECYCLE capacity_atomic=1 room_suspend=1 stun=1 clear=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-vis-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"vis.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture present");
        text.replace(at,from.size(),to);std::ofstream(root/"vis.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("100 .35 10 35.2 .6","100 .35 10 16 .6");
    check(near(changed->vis(monsterId(39))->monsterDamage,16)&&near(defaultMechanics()->vis(monsterId(39))->monsterDamage,35.2f),"external immutable beam tuning");
    for(const auto &pair:std::vector<std::pair<std::string,std::string>>{{"79 28 1","79 79 1"},{"79 28 1","79 28 3"},
        {".1 .7 .8",".1 .7 1"},{"20 400 79","400 20 79"},{"32 19 2 100","32 19 0 100"},{"10 35.2 .6","10 -1 .6"},
        {"vis_beam 39.0.0 32 19 2 100 .35 10 35.2 .6 .85 .895",""}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or incomplete Vis profile rejected");
    }
    std::cout<<"CONFIG immutable=1 invalid_profiles7\n";
}
void startingKit() {
    for(int variant:{0,1,3}) {
        auto s=fixture();s.godMode=false;s.player.position={0,.85f,10};const auto id=spawn(s,variant);
        check(s.player.hp==100&&s.player.shotDamage==24,"unchanged default player kit");
        int frames=0;
        while(!s.dead&&s.roomThreats()&&frames<600) {
            Input input;
            if(const auto *e=s.findEnemy(id);e&&e->alive) {
                input.fire=true;input.aim=e->position;
                const auto delta=horizontal(sub(e->position,s.player.position));
                // Strafe out of a visible cardinal lane while firing the real
                // starting revolver. No injected damage, health or invulnerability.
                input.movement=length(delta)>18?unit(delta):rotateY(unit(delta),Pi/2);
            }
            s.step(input);++frames;
        }
        check(!s.dead&&!s.roomThreats(),"default kit defeats each Vis beam body");
        std::cout<<"STARTING_KIT variant="<<variant<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<'\n';
    }
}
}
int main(){std::cout<<std::unitbuf;try{movementAndTiming();beamRules();capacityAndRooms();configuration();startingKit();std::cout<<"PASS Vis beam bodies (Chubber pending)\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
