#include "combat/Simulation.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.01f){return std::abs(a-b)<eps;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.arena.flightCollisionPrepared=false;s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={65,.85f,0};return s;
}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(854),{0,.85f,0});}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
void damage(Simulation &s,EntityId id,float amount,bool area=false,bool execute=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=amount;h.areaDamage=area;h.execution=execute;s.queueRoot(h);s.drainEvents();
}
void acquire(Simulation &s,EntityId id) {
    for(int n=0;n<300&&!s.findEnemy(id)->adultLeech->charges;++n)tick(s);
    check(s.findEnemy(id)->adultLeech->phase==AdultLeechPhase::Charge,"horizontal distant target acquires charge");
}
void movementAndImpacts() {
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=*e.adultLeech;
    check(near(e.hp,288)&&near(s.content->monsterHealth(e.monster,15),288),"source90HP without stage growth");
    acquire(s,id);s.player.position={-10,.85f,30};tick(s,20);
    check(r.phase==AdultLeechPhase::Charge&&r.chargeSign==1&&e.velocity.x>0&&e.velocity.z>0,"committed horizontal charge with vertical steering");
    for(int n=0;n<200&&!r.wallRings;++n)tick(s);
    check(r.wallRings==1&&r.impacts==1&&r.stops==1&&r.recovery==12,"actual strong wall impact stops, emits, recovers");
    check(s.projectiles.size()==12,"wall packet has12 shots");
    for(const auto &shot:s.projectiles)check(near(length(horizontal(shot.velocity)),30)&&near(shot.gravity,8.1f)&&near(shot.damage,10)&&!shot.repeatWallBounce,"wall flight profile");
    check(!s.arena.flightBlocked(e.position,e.radius,0),"charge never escapes room bounds");
    auto weak=fixture();const auto wid=spawn(weak);auto &we=*weak.findEnemy(wid);auto &wr=*we.adultLeech;
    tick(weak);we.position.x=weak.arena.rooms[0].bounds.max.x-we.radius-.01f;
    wr.phase=AdultLeechPhase::Charge;wr.gain=.5f;wr.momentum={1,0,0};tick(weak,2);
    check(wr.stops==1&&wr.impacts==0&&weak.projectiles.empty(),"weak wall collision stops without ring");
    auto covered=fixture();covered.arena.walls.push_back({{20,0,-79},{21,10,79}});auto cid=spawn(covered);acquire(covered,cid);
    std::cout<<"CHARGE hp288=1 steering=1 committed_x=1 strong12=1 weak_no_ring=1 no_LOS_gate=1\n";
}
void burrowAndDamage() {
    auto s=fixture();s.player.position={0,.85f,65};const auto id=spawn(s);auto &e=*s.findEnemy(id);auto &r=*e.adultLeech;
    damage(s,id,110);
    for(int n=0;n<600&&r.phase!=AdultLeechPhase::Burrow;++n)tick(s);
    check(r.phase==AdultLeechPhase::Burrow&&r.frame==0&&r.burrows==1,"low health vertical separation acquires burrow");
    tick(s,21);check(!r.intangible&&r.frame==21,"body remains collidable until Hit22");
    auto hp=e.hp;damage(s,id,7,true);check(near(e.hp,hp-7),"pre-burrow blast damage");
    tick(s);check(r.intangible&&r.visibility==0,"Hit22 removes body");
    hp=e.hp;damage(s,id,7,true);check(near(e.hp,hp),"hidden body excluded from explosion collection");
    damage(s,id,3);check(near(e.hp,hp-3),"scripted direct damage not blanket blocked");
    auto bullets=s;Event shot;shot.position=add(e.position,{-3,-.85f,0});shot.origin=shot.position;
    shot.direction={1,0,0};shot.speed=180;shot.damage=20;shot.projectileLife=2;
    bullets.queueRoot(shot);bullets.drainEvents();tick(bullets);
    check(near(bullets.findEnemy(id)->hp,e.hp)&&!bullets.projectiles.empty()&&bullets.projectiles[0].position.x>e.position.x+1,"real bullet passes through hidden body");
    tick(s,3);check(r.phase==AdultLeechPhase::Hidden&&r.hidden==1,"Burrow25 then hidden wait");
    tick(s,29);check(r.phase==AdultLeechPhase::Hidden,"minimum hidden wait30");
    for(int n=0;n<300&&r.phase==AdultLeechPhase::Hidden;++n)tick(s);
    check(r.phase==AdultLeechPhase::Fall&&r.frame==0&&r.intangible&&e.lift==6&&planarDistance(e.position,s.player.position)<.01f,"one-time fall teleports to player after wait");
    s.player.position.x+=3;const auto from=e.position;tick(s,17);
    check(r.frame==17&&r.intangible&&r.landings==0&&e.position.x>from.x+.1f,"fall tracks player until Hit18");
    tick(s);check(!r.intangible&&r.landings==1&&r.landingRings==1&&s.projectiles.size()==10&&e.lift==0,"Hit18 lands, restores body and emits10");
    for(const auto &shot:s.projectiles)check(near(length(horizontal(shot.velocity)),24)&&near(shot.gravity,3.6f),"landing flight profile");
    tick(s,13);check(!r.anchored&&r.frame==31,"Sound31 releases landing anchor");tick(s,12);
    check(r.phase==AdultLeechPhase::Wander,"ChargeDown43 returns to wandering");
    s.player.position={0,.85f,-65};tick(s,600);check(r.burrows==1,"burrow never repeats at low health");
    std::cout<<"BURROW health_gate=1 Hit22=1 area_vs_direct=1 hidden30=1 tracking=1 Hit18_ring10=1 Sound31=1 once=1\n";
}
void determinismAndLimits() {
    auto a=fixture(),b=fixture();const auto x=spawn(a),y=spawn(b);tick(a,70);tick(b,280,1.f/120);
    std::cout<<"PARTITION distance="<<distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<<" ticks="<<a.findEnemy(x)->adultLeech->ticks<<','<<b.findEnemy(y)->adultLeech->ticks<<" impacts="<<a.findEnemy(x)->adultLeech->impacts<<','<<b.findEnemy(y)->adultLeech->impacts<<'\n';
    check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.02f&&a.findEnemy(x)->adultLeech->ticks==b.findEnemy(y)->adultLeech->ticks,"render partition keeps movement and source tick count");
    auto c=fixture(),d=fixture();const auto cx=spawn(c),dx=spawn(d);tick(c,3);tick(d,3);c.findEnemy(cx)->velocity={999,0,-999};tick(c);tick(d);
    check(distance(c.findEnemy(cx)->position,d.findEnemy(dx)->position)<.001f,"knockback immunity");
    auto s=fixture();const auto id=spawn(s);auto &r=*s.findEnemy(id)->adultLeech;s.limits.projectiles=11;
    for(int n=0;n<400&&r.pendingShots.empty();++n)tick(s);
    check(r.pendingShots.size()==12&&s.projectiles.empty(),"whole wall ring retained at capacity");
    const auto origin=r.pendingShots[0].position;tick(s,10);s.limits.projectiles=12;tick(s);
    check(r.wallRings==1&&s.projectiles.size()==12&&distance(s.projectiles[0].position,origin)<.001f,"exact packet released once with retained origin");
    auto contact=fixture();auto id2=spawn(contact);contact.godMode=false;contact.player.position=contact.findEnemy(id2)->position;tick(contact);
    check(near(contact.player.hp,75),"contact2 converts to25 after shared multiplier");
    s.debugScenario=false;damage(s,id,10000,false,true);tick(s,3);
    check(s.enemies.empty()&&!s.roomClear,"fired lob shots survive owner death and still gate clear");
    tick(s,90);check(s.roomClear&&s.enemies.empty(),"room clears after remaining shots land without offspring");
    auto ordinary=fixture();auto oid=spawn(ordinary);ordinary.debugScenario=false;damage(ordinary,oid,10000);tick(ordinary,3);
    check(ordinary.roomClear&&ordinary.enemies.empty(),"ordinary death has no offspring");
    std::cout<<"SYSTEM render_partition=1 knockback=1 ring_capacity=1 contact25=1 death_completion=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-adult-leech-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"adult_leeches.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"adult_leeches.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("25 8 22 30 15","25 8 22 45 15");check(changed->adultLeech(monsterId(854))->hiddenFrames==45&&defaultMechanics()->adultLeech(monsterId(854))->hiddenFrames==30,"immutable external reload");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".7 .8 30",".7 1 30"},{"43 18 31","43 43 31"},{"wall 12 30","wall 0 30"},{"Wander None Worm","Wander Ring Worm"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or incompatible config rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=4\n";
}
void placement() {
    for(uint64_t seed=1;seed<=100;++seed) {
      ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
      for(int floor=0;floor<plan.floorCount;++floor) {
        if(plan.profileOnFloor(floor).band!=3)continue;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.godMode=true;
        for(int room=1;room<int(s.arena.roomCount());++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(854)) {
            const auto id=e.id;check(s.arena.profile.band==3&&!s.arena.flightBlocked(e.position,e.radius,room),"band3 natural legal flight footprint");
            tick(s,8);const auto &resident=s.roomEnemies(room);auto it=std::find_if(resident.begin(),resident.end(),[&](const auto &a){return a.id==id;});
            check(it!=resident.end()&&it->idleTime>0&&it->adultLeech->ticks==0,"inactive room animates without attacks");
            s.enterRoom(room);tick(s,8);check(s.findEnemy(id)&&s.findEnemy(id)->adultLeech->ticks>0,"natural resident activates dedicated controller");
            std::cout<<"NATURAL_ADULT_LEECH seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';return;
        }
    }
    }
    check(false,"ordinary seeded Adult Leech must be reachable");
}
}
int main(){std::cout<<std::unitbuf;try{movementAndImpacts();burrowAndDamage();determinismAndLimits();configuration();placement();std::cout<<"PASS Adult Leech\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
