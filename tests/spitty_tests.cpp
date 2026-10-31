#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float epsilon=.005f){return std::abs(a-b)<epsilon;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("dw-spitties-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(root);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());std::ifstream in(root/"spitties.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(root);}
    std::shared_ptr<const MechanicsLibrary> load(std::string from,std::string to){auto s=original;auto at=s.find(from);check(at!=s.npos,"configuration fixture exists");s.replace(at,from.size(),to);std::ofstream(root/"spitties.mechanics")<<s;return MechanicsLibrary::load(root);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,20,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={-30,.85f,-30};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s,MonsterId id){return s.spawnMonster(id,{0,.85f,0});}
void attack(Simulation &s,EntityId id) {
    auto &e=*s.findEnemy(id);e.spitty->attackFrame=0;e.spitty->attackDirection={1,0,0};e.spitty->clock=0;
    e.spitty->fired=false;e.state=EnemyState::Windup;e.facing={1,0,0};
}
void kill(Simulation &s,EntityId id,bool debug=false) {
    Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=100000;hit.execution=true;hit.debugExecution=debug;
    check(s.queueRoot(hit),"death admitted");s.drainEvents();
}
void attacks() {
    for(auto key:{monsterId(31),monsterId(243),monsterId(31,1)}) {
        auto s=fixture();const auto id=spawn(s,key);const auto &profile=*s.content->spitty(key);
        check(near(s.findEnemy(id)->hp,key.type==243?57.6f:key.variant?192.f:32.f),"installed health scaled consistently");
        attack(s,id);tick(s,10);check(s.projectiles.empty(),"Shoot event waits six source frames");
        s.player.position={0,.85f,-30};tick(s,2);
        const int count=key.type==243?2:key.variant?10:1;
        check(s.projectiles.size()==size_t(count)&&s.findEnemy(id)->spitty->volleys==1,"complete primary packet only once");
        for(int n=0;n<count;++n) {
            const auto &p=s.projectiles[size_t(n)];const float sign=key.type==243&&n?-1.f:1.f;
            check(p.context.sourceEntity==id&&near(length(horizontal(p.velocity)),profile.shot.speed)&&p.velocity.x*sign>0,"source owner and facing-directed speed");
            check(near(p.position.y,profile.shot.height)&&near(p.velocity.y,profile.shot.upMin)&&near(p.flightRetention,.9f),"source-derived flight height and falling physics");
            if(key.variant) {
                check(p.sourcePlanarMotion&&near(p.sourcePlanarMotion->acceleration,1-.03f*float(n))&&near(p.radius,.22f*(1.7f-.1f*float(n)))&&
                    near(p.gravity,7.65f-.225f*float(n))&&!p.noWallCollision,"ten-shot stream size, slowing and landing progression");
                check(std::abs(std::atan2(p.velocity.z,p.velocity.x))<=float(n)*Pi/360+.0001f,"stream angular jitter stays within source cone");
            } else check(near(p.velocity.z,0)&&!p.sourcePlanarMotion,"ordinary and Conjoined shots stay cardinal");
        }
        tick(s,20);check(s.findEnemy(id)->spitty->attackFrame==-1&&s.findEnemy(id)->state==EnemyState::Ready,"Attack16 recovery ends without generic cooldown");
        std::cout<<"PRIMARY "<<monsterIdText(key)<<" count="<<count<<" source_frames=16 shoot=6\n";
    }
}
void walkingAndBurst() {
    Pack pack;auto lib=pack.load("20 35 16 6","20 1000000 16 6");
    auto s=fixture(lib);const auto id=spawn(s,monsterId(31,1));auto &e=*s.findEnemy(id);
    e.velocity={9,0,0};e.spitty->hasDestination=true;e.spitty->destination={35,.85f,0};
    tick(s,10);check(s.projectiles.empty()&&e.spitty->walkAxis==0,"moving burst waits animation Shoot6");tick(s,2);
    check(e.spitty->bursts==1&&(s.projectiles.size()==3||s.projectiles.size()==4),"walking event releases three or four random shots");
    for(const auto &p:s.projectiles)check(near(length(horizontal(p.velocity)),21)&&p.velocity.y>=7.5f&&p.velocity.y<=43.5f&&
        near(p.gravity,63.9f)&&p.radius>=.198f&&p.radius<=.2971f&&!p.sourcePlanarMotion,"moving burst source speed, height variance and size alternatives");
    auto left=fixture(),right=fixture();const auto a=spawn(left,monsterId(31)),b=spawn(right,monsterId(31));right.player.position={30,.85f,30};
    for(int n=0;n<240;++n){tick(left);tick(right);check(distance(left.findEnemy(a)->position,right.findEnemy(b)->position)<.001f,"wander path and facing do not seek the player");}
    check(planarDistance(left.findEnemy(a)->position,{0,0,0})>1,"random cardinal locomotion makes progress");
    auto stun=fixture(lib);const auto sid=spawn(stun,monsterId(31,1));attack(stun,sid);tick(stun,8);stun.findEnemy(sid)->state=EnemyState::Stunned;stun.findEnemy(sid)->stateTime=1;
    tick(stun,30);check(stun.projectiles.empty()&&stun.findEnemy(sid)->spitty->attackFrame==-1,"stun cancels unfinished attacks");
    auto rooms=fixture();const auto rid=spawn(rooms,monsterId(243));attack(rooms,rid);tick(rooms,4);const int frame=rooms.findEnemy(rid)->spitty->attackFrame;
    rooms.enterRoom(1);tick(rooms,60);rooms.enterRoom(0);check(rooms.findEnemy(rid)->spitty->attackFrame==frame,"inactive room suspends source attack clock");tick(rooms,8);check(rooms.stats.projectiles==2,"resumed attack emits exactly once");
    std::cout<<"WALK burst_event=1 no_pursuit=1 stun=1 room_suspend=1\n";
}
void capacityAndDeath() {
    auto shot=fixture();const auto id=spawn(shot,monsterId(243));attack(shot,id);shot.limits.projectiles=1;tick(shot,40);
    check(shot.stats.projectiles==0&&shot.findEnemy(id)->spitty->attackFrame==6,"Conjoined packet waits rather than firing one end");
    shot.limits.projectiles=2;tick(shot,2);check(shot.stats.projectiles==2,"Conjoined packet resumes together");
    auto s=fixture();s.debugScenario=false;const auto dead=spawn(s,monsterId(31,1));s.limits.projectiles=15;kill(s,dead);tick(s,6);
    check(s.stats.kills==1&&s.projectiles.empty()&&!s.roomClear&&s.findEnemy(dead)->spitty->deathPending,"death retains a bounded whole sixteen-shot packet");
    s.limits.projectiles=64;tick(s);check(s.projectiles.size()==16&&!s.roomClear,"death packet survives execution and releases when capacity returns");
    int cw=0,ccw=0;for(const auto &p:s.projectiles) {
        check(p.sourcePlanarMotion&&p.noWallCollision&&p.context.sourceEntity==dead&&near(p.radius,.275f)&&near(p.gravity,1.35f),"native orbit payload survives source death");
        if(p.sourcePlanarMotion->orbitDirection==1)++cw;else ++ccw;
    }
    check(cw==8&&ccw==8,"two eight-shot opposite rings");
    check(near(std::atan2(s.projectiles[8].velocity.z,s.projectiles[8].velocity.x),3*Pi/8),"second death ring has source half-step angular offset");
    tick(s,4);check(!s.findEnemy(dead)&&s.projectiles.size()==16,"orbits persist after actor removal");
    tick(s,480);check(s.roomClear&&s.projectiles.empty()&&s.stats.kills==1,"physical landing resolves room once");
    auto debug=fixture();auto did=spawn(debug,monsterId(31,1));kill(debug,did,true);tick(debug,30);check(debug.projectiles.empty(),"debug execution cancels death attack");
    std::cout<<"CAPACITY packet_atomicity=1 death_retention=1 owner_lifetime=1 completion=1\n";
}
void navigationAndConfiguration() {
    auto s=fixture();s.arena.obstacles.push_back({{2,0,-10},{3,5,10}});s.arena.rebuildWalls();const auto id=spawn(s,monsterId(31));
    auto &e=*s.findEnemy(id);e.velocity={15,0,0};e.spitty->hasDestination=true;e.spitty->destination={8,.85f,0};
    for(int n=0;n<240;++n){tick(s);check(!sphereBox(e.position,e.radius,s.arena.obstacles[0]),"physical wandering cannot pass through solid cover");}
    Pack pack;auto changed=pack.load("shot 24 .45","shot 18 .45");check(near(changed->spitty(monsterId(31))->shot.speed,18)&&near(defaultMechanics()->spitty(monsterId(31))->shot.speed,24),"new library loads external tuning without mutating existing runs");
    for(auto edit:std::vector<std::pair<std::string,std::string>>{{"1.7 .1 .03","1.7 .3 .03"},{"7.65 .9","0 .9"},{"death 24","death 101"},{"20 35 16 6","20 35 6 6"},{"spitty_burst 31.1.0","spitty_burst 31.0.0"}}) {
        bool rejected=false;try{pack.load(edit.first,edit.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid external profile rejected");
    }
    std::cout<<"GEOMETRY cover=1 CONFIG immutable_reload=1 invalid_profiles=5\n";
}
void startingKit() {
    for(auto key:{monsterId(31),monsterId(243),monsterId(31,1)}) {
        auto s=fixture();s.godMode=false;s.player.position={0,.85f,8};const auto id=spawn(s,key);int frames=0;
        while(s.roomThreats()&&!s.dead&&frames<2400) {
            Input input;input.fire=true;
            if(const auto *e=s.findEnemy(id)) {
                const auto delta=horizontal(sub(e->position,s.player.position));const float range=length(delta);
                input.aim=add(e->position,mul(e->velocity,std::min(.5f,range/26)));
                input.movement=range>12?unit(delta):range<6?mul(unit(delta),-1):rotateY(unit(delta),Pi/2);
            }
            s.step(input);++frames;
        }
        std::cout<<"STARTING_KIT "<<monsterIdText(key)<<" seconds="<<float(frames)*Tick<<" health="<<s.player.hp<<'\n';
        if(s.roomThreats())std::cout<<"REMAINING hp="<<s.findEnemy(id)->hp<<" dead="<<s.dead<<'\n';
        check(!s.dead&&s.roomThreats()==0,"default revolver defeats isolated source variant");
    }
}
void naturalPlacement() {
    std::array<bool,3> found{};
    for(uint64_t seed=0;seed<256&&(!found[0]||!found[1]||!found[2]);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            const auto band=plan.profileOnFloor(floor).band;if(band==0)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.godMode=true;
            for(int room=1;room<s.finalRoom();++room) {
                std::vector<EntityId> actors;
                for(const auto &e:s.roomEnemies(room))if(s.content->spitty(e.monster)) {
                    const int form=e.monster.type==243?1:e.monster.variant?2:0;
                    check(e.spitty&&!s.arena.blocked(e.position,e.radius)&&
                        (form==2?band==3:band>=1&&band<=2),"generated resident has legal geometry, controller and stage");
                    if(!found[size_t(form)])std::cout<<"NATURAL_SPITTY id="<<e.monster.type<<'.'<<e.monster.variant<<".0 seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<band<<'\n';
                    found[size_t(form)]=true;actors.push_back(e.id);
                }
                if(!actors.empty()) {
                    s.enterRoom(room);s.player.position=s.arena.rooms[size_t(room)].entry;tick(s,4);
                    for(auto id:actors)check(s.findEnemy(id)&&s.findEnemy(id)->spitty->ticks>0,"naturally spawned actor actually activates dedicated controller");
                }
            }
        }
    }
    check(found[0]&&found[1]&&found[2],"all three exact records reachable through real seeded floors");
}
}
int main(){try{attacks();walkingAndBurst();capacityAndDeath();navigationAndConfiguration();startingKit();naturalPlacement();std::cout<<"PASS Spitty family\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
