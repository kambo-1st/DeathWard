#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.01f){return std::abs(a-b)<eps;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,60};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int type=223){return s.spawnMonster(monsterId(type),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount=7,bool execution=false,bool debug=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=amount;h.execution=execution;h.debugExecution=debug;s.queueRoot(h);s.drainEvents();
}
void dips() {
    auto a=fixture(),b=fixture();auto x=spawn(a,217),y=spawn(b,217);b.player.position={-60,.85f,-60};
    check(near(a.findEnemy(x)->hp,12.8f)&&near(a.content->monsterHealth(monsterId(217),6),24.96f),"Dip source-stage HP");
    for(int n=0;n<200&&a.findEnemy(x)->slide->dashes==0;++n){tick(a);tick(b);}
    auto &e=*a.findEnemy(x);check(e.slide->dashes==1&&e.slide->phase==2,"Dip starts a random dash");
    check(distance(e.position,b.findEnemy(y)->position)<.001f,"Dip direction does not home toward player");
    check(length(e.velocity)>=12-.01f&&length(e.velocity)<24+.01f,"random source5..10 impulse with initial .8 retention");
    const auto v=e.velocity;tick(a);check(distance(e.velocity,mul(v,.95f))<.01f,"Dip coasts at .95 retention");
    for(int n=0;n<200&&e.slide->phase!=0;++n)tick(a);check(e.slide->phase==0,"Dip waits after speed drops below1");
    e.velocity={30,0,0};tick(a);check(e.position.x>0||e.velocity.x>0,"external push survives controller");
    auto c=fixture();auto z=spawn(c,217);c.godMode=false;c.player.position=c.findEnemy(z)->position;tick(c);
    check(near(c.player.hp,87.5f),"Dip contact damage12.5");
    std::cout<<"DIP random_dash=1 friction=1 rest=1 push=1 stage_HP=1 contact12.5=1\n";
}
void squirt() {
    auto s=fixture();const auto id=spawn(s,220);auto &e=*s.findEnemy(id);auto &r=*e.slide;
    check(near(e.hp,67.2f)&&near(s.content->monsterHealth(monsterId(220),6),140.16f),"Squirt source15+6stage HP");
    for(int n=0;n<500&&r.phase!=1;++n)tick(s);check(r.phase==1&&r.frame==0,"Squirt acquires attack");
    tick(s,35);check(r.frame==35&&length(e.velocity)<.001f,"Squirt waits for Slide36");
    s.player.position={-50,.85f,30};const auto aim=unit(horizontal(sub(s.player.position,e.position)));tick(s);
    check(r.frame==36&&distance(e.velocity,mul(aim,60))<.02f,"Slide36 samples current target with source20 impulse");
    s.player.position={50,.85f,-30};tick(s,4);check(r.phase==2&&dot(unit(e.velocity),aim)>.999f,"committed slide does not retarget");
    for(int n=0;n<300&&r.phase!=0;++n)tick(s);check(r.phase==0,"Squirt returns idle after coasting");
    auto blocked=fixture();blocked.arena.walls.push_back({{-79,0,40},{79,20,41}});auto bi=spawn(blocked,220);
    for(int n=0;n<500&&blocked.findEnemy(bi)->slide->phase!=1;++n)tick(blocked);
    check(blocked.findEnemy(bi)->slide->phase==1,"ordinary Squirt acquisition has no line-of-sight gate");
    auto wall=fixture();wall.arena.walls.push_back({{4,0,-79},{4.2f,20,79}});auto wi=spawn(wall,220);tick(wall);
    wall.player.position={40,.85f,0};wall.findEnemy(wi)->slide->phase=1;wall.findEnemy(wi)->slide->frame=35;
    auto split=wall;tick(wall,25);tick(split,100,1.f/120);
    check(!wall.arena.blocked(wall.findEnemy(wi)->position,.65f)&&near(wall.findEnemy(wi)->position.x,3.35f,.002f),"fast Squirt reaches solid wall without tunneling");
    check(distance(wall.findEnemy(wi)->position,split.findEnemy(wi)->position)<.002f,"wall contact agrees at30/120Hz");
    std::cout<<"SQUIRT stage_HP=1 telegraph36=1 launch60=1 aim_at_release=1 committed=1 recovery=1\n";
}
void acquire(Simulation &s,EntityId id) {
    for(int n=0;n<600&&s.findEnemy(id)->memBrain->attackFrame<0;++n)tick(s);
    check(s.findEnemy(id)->memBrain->attackFrame==0,"Dinga acquires hop");
}
void dinga() {
    bool birth=false,ring=false;
    for(uint64_t seed=0;seed<40&&(!birth||!ring);++seed) {
        auto s=fixture();s.combatRng=Random(seed);const auto id=spawn(s);acquire(s,id);tick(s,19);
        check(s.findEnemy(id)->memBrain->attackFrame==28.5f&&s.projectiles.empty()&&s.enemies.size()==1,"Dinga45FPS before Shoot29");
        tick(s);const auto r=*s.findEnemy(id)->memBrain;
        check(r.attackFrame==30&&r.fired,"Dinga crosses Shoot29 at20 simulation ticks");
        if(r.births) {
            birth=true;check(r.births==2&&r.volleys==0&&s.enemies.size()==3,"Dinga two live Dips instead of ring");
            for(const auto &e:s.enemies)if(e.monster.type==217)check(e.slide&&length(e.velocity)>30&&e.summoner==id,"new Dips pushed outward");
        } else {
            ring=true;check(r.volleys==1&&s.projectiles.size()==8,"Dinga eight-shot ring alternative");
            for(const auto &p:s.projectiles)check(p.kind==ProjectileKind::Brown&&near(length(horizontal(p.velocity)),30)&&near(p.damage,20),"brown source mode8 projectiles");
        }
        tick(s,27);check(s.findEnemy(id)->memBrain->attackFrame==-1,"Dinga Attack70 completes after47 source ticks");
    }
    check(birth&&ring,"both real seeded outcomes reachable");
    auto s=fixture();auto id=spawn(s);acquire(s,id);
    // Population6 forces ring even if a spawn draw would normally succeed.
    for(int n=0;n<5;++n)s.spawnMonster(monsterId(56),{float(n*3-30),.85f,-40});
    s.limits.projectiles=7;tick(s,20);check(s.findEnemy(id)->memBrain->pendingShots.size()==8&&s.projectiles.empty(),"population6 ring retained atomically at capacity");
    const auto origin=s.findEnemy(id)->memBrain->pendingShots.front().position;tick(s,5);s.limits.projectiles=8;tick(s);
    check(s.findEnemy(id)->memBrain->volleys==1&&s.findEnemy(id)->memBrain->births==0&&s.projectiles.size()==8&&distance(s.projectiles[0].position,origin)<.001f,"one retained ring released without reroll");
    auto capped=fixture();auto ci=spawn(capped);for(int n=0;n<7;++n)capped.spawnMonster(monsterId(56),{float(n*3-30),.85f,-40});tick(capped,400);
    check(capped.findEnemy(ci)->memBrain->attacks==0,"population8 suppresses hop acquisition");
    auto pushed=fixture();auto pi=spawn(pushed);acquire(pushed,pi);tick(pushed,19);
    const auto pos=pushed.findEnemy(pi)->position;auto di=pushed.spawnMonster(monsterId(217),add(pos,{8,0,0}));tick(pushed);
    check(pushed.findEnemy(pi)->memBrain->pushes==1&&pushed.findEnemy(di)->velocity.x>10,"hop pushes independently placed existing Dip");
    std::cout<<"DINGA FPS45=1 live_Dips=2 ring8=1 cap6=1 cap8=1 push_existing=1 retained_ring=1\n";
}
void lifecycle() {
    for(int mode=0;mode<3;++mode) {
        auto s=fixture();auto id=spawn(s);s.debugScenario=false;s.limits.enemies=1;
        damage(s,id,10000,mode!=0,mode==2);tick(s);
        if(mode==2){check(s.roomClear&&s.enemies.empty(),"debug clear suppresses whole chain");continue;}
        int squirts=0,dips=0;
        for(int n=0;n<12&&!s.roomClear;++n) {
            check(s.enemies.size()==1,"capacity retains exactly one active descendant");
            auto e=s.enemies.front();check(e.slide&&!s.arena.blocked(e.position,e.radius),"real offspring controller and legal spawn");
            if(e.monster.type==220)++squirts;else if(e.monster.type==217)++dips;else check(false,"unexpected descendant");
            damage(s,e.id,10000);tick(s);
        }
        check(s.roomClear&&squirts==2&&dips==4&&s.stats.kills==7,"both Squirts and all four Dips gate clear under capacity");
    }
    for(int type:{217,220,223}) {
        auto a=fixture(),b=fixture();auto x=spawn(a,type),y=spawn(b,type);tick(a,50);tick(b,200,1.f/120);
        check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.02f,"30/120Hz open-room integration agrees");
    }
    std::cout<<"LIFECYCLE two_Squirts_four_Dips=1 completion=1 capacity=1 execution=1 debug_clear=1 frame_partition=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-dinga-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"dinga.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"dinga.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("150 .1 45","150 .1 60");check(changed->memBrain(monsterId(223))->dinga->animationFps==60&&defaultMechanics()->memBrain(monsterId(223))->dinga->animationFps==45,"immutable config reload");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".8 .95 5 10","1 .95 5 10"},{"40 36 .5","40 40 .5"},{".85 217.0.0 1",".85 56.0.0 1"},{"dinga 223.0.0 217.0.0","dinga 223.0.0 220.0.0"},{"150 .1 45","150 .1 0"},{"20 20 1 5 5","20 21 1 5 5"},{"1 10 1 10 25","1 10 2 10 25"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid profile rejected");
    }
    std::cout<<"CONFIG reload=1 invalid_profiles=7\n";
}
void placement() {
    struct Witness{int type;uint64_t seed;int floor,room;};
    for(auto w:std::array<Witness,3>{{{217,0,0,6},{220,0,2,5},{223,4,5,10}}}) {
        Simulation s(w.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,w.floor);s.godMode=true;
        std::vector<EntityId> ids;
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==monsterId(w.type)) {
            check(!s.arena.blocked(e.position,e.radius)&&(w.type!=223||s.arena.profile.band>=2),"source habitat and legal footprint");ids.push_back(e.id);
        }
        check(!ids.empty(),"natural witness still contains exact identity");tick(s,8);
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==monsterId(w.type))check(e.idleTime>0&&(e.slide?e.slide->ticks:e.memBrain->ticks)==0,"dormant ambient animation without attacks");
        s.enterRoom(w.room);tick(s,8);
        for(auto id:ids){auto *e=s.findEnemy(id);check(e&&(e->slide?e->slide->ticks:e->memBrain->ticks)>0,"natural dedicated controller activates");}
        std::cout<<"NATURAL_DINGA id="<<w.type<<" seed="<<w.seed<<" floor="<<w.floor<<" room="<<w.room<<'\n';
    }
}
}
int main(){std::cout<<std::unitbuf;try{dips();squirt();dinga();lifecycle();configuration();placement();std::cout<<"PASS Dinga family\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
