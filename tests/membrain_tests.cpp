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
EntityId spawn(Simulation &s,int variant=0){return s.spawnMonster(monsterId(57,variant),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount=7,bool execution=false,bool debug=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=amount;h.execution=execution;h.debugExecution=debug;s.queueRoot(h);s.drainEvents();
}
void acquire(Simulation &s,EntityId id) {
    for(int n=0;n<600&&s.findEnemy(id)->memBrain->attackFrame<0;++n)tick(s);
    check(s.findEnemy(id)->memBrain->attackFrame==0,"chance acquisition even with distant player");
}
void attack() {
    for(int v=0;v<3;++v) {
        auto s=fixture();const auto id=spawn(s,v);auto &e=*s.findEnemy(id);auto &r=*e.memBrain;
        check(near(e.hp,198.4f)&&near(s.content->monsterHealth(e.monster,13),198.4f),"62 sourceHP, no stage growth");
        acquire(s,id);const auto velocity=e.velocity;tick(s,20);
        check(r.attackFrame==20&&s.projectiles.empty()&&e.lift>.5f,"hop precedes Shoot29");
        check(length(e.velocity)<length(velocity)+.001f,"attack coasts without propulsive jump");
        const auto hp=e.hp;damage(s,id);check(near(e.hp,hp-7),"hop remains damageable");
        tick(s,8);check(s.projectiles.empty(),"no projectile before Shoot29");tick(s);
        check(r.volleys==1&&s.projectiles.size()==8,"one actual eight-shot packet at Shoot29");
        for(int n=0;n<8;++n) {
            const auto &p=s.projectiles[size_t(n)];const float angle=float(n)*Pi/4+(v==2?Pi/8:0);
            check(distance(horizontal(p.velocity),{std::cos(angle)*(v==2?24.f:30.f),0,std::sin(angle)*(v==2?24.f:30.f)})<.01f,"ring angles and equal speeds");
            check(near(p.position.y,1.15f)&&std::abs(p.velocity.y)<=.151f&&near(p.radius,.308f),"source scale and near-zero falling speed");
            check(near(p.gravity,v==2?1.35f:4.5f)&&near(p.flightRetention,.9f)&&near(p.damage,20),"source flight and damage before shared hurt multiplier");
            check(p.repeatWallBounce==(v==2)&&p.bounces==0,"Dead Meat continuous reflection is not finite bounce budget");
        }
        tick(s,40);check(r.attackFrame==69,"Attack lasts through frame69");tick(s);check(r.attackFrame==-1,"Attack70 returns to wandering");
    }
    auto capped=fixture();const auto id=spawn(capped);
    for(int n=0;n<7;++n)capped.spawnMonster(monsterId(56),{float(n*3-30),.85f,-40});
    tick(capped,400);check(capped.findEnemy(id)->memBrain->attacks==0,"population8 suppresses new attacks");
    auto blocked=fixture();blocked.arena.walls.push_back({{-79,0,40},{79,20,41}});const auto bid=spawn(blocked);acquire(blocked,bid);
    std::cout<<"ATTACK variants3=1 HP198.4=1 Shoot29=1 Attack70=1 hop_vulnerable=1 ring8=1 cap8=1 no_LOS_gate=1\n";
}
void movementAndCapacity() {
    auto a=fixture(),b=fixture();const auto x=spawn(a),y=spawn(b);tick(a,70);tick(b,280,1.f/120);
    const auto &ae=*a.findEnemy(x),&be=*b.findEnemy(y);
    check(distance(ae.position,be.position)<.02f&&ae.memBrain->ticks==be.memBrain->ticks&&ae.memBrain->attackFrame==be.memBrain->attackFrame,"30 and120Hz movement and phase agree");
    auto s=fixture();const auto id=spawn(s);acquire(s,id);s.limits.projectiles=7;tick(s,29);
    auto &r=*s.findEnemy(id)->memBrain;check(r.pendingShots.size()==8&&r.attackFrame==29&&s.projectiles.empty(),"whole ring retained when only seven slots available");
    const auto position=r.pendingShots.front().position;tick(s,8);check(r.pendingShots.size()==8&&r.volleys==0,"capacity retry does not duplicate packet");
    s.limits.projectiles=8;tick(s);check(s.projectiles.size()==8&&r.volleys==1&&distance(s.projectiles[0].position,position)<.001f,"pending origin retained until release");
    auto contact=fixture();auto cid=spawn(contact);contact.godMode=false;contact.player.position=contact.findEnemy(cid)->position;tick(contact);
    check(near(contact.player.hp,75),"contact2 converts20 then shared multiplier25");
    std::cout<<"MOVEMENT render_partition=1 whole_packet_backpressure=1 contact25=1\n";
}
void cyst() {
    auto s=fixture();const auto id=s.spawnMonster(monsterId(862),{0,.85f,0});auto &e=*s.findEnemy(id);auto &r=*e.guts;
    check(near(e.hp,80)&&!e.memBrain,"Cyst source25HP and Guts controller");
    tick(s,31);check(r.shots==0&&r.shotTimer==30,"initialization then30 counter increments");
    const auto before=e.position;s.player.position={-60,.85f,60};const auto aim=unit(horizontal(sub(s.player.position,before)));tick(s);
    check(r.shots==1&&r.shotFrame==0&&s.projectiles.size()==1,"Cyst fires on next source update");
    check(distance(horizontal(s.projectiles[0].velocity),mul(aim,30))<.01f&&near(s.projectiles[0].velocity.y,4.5f)&&near(s.projectiles[0].gravity,9),"current-player mode0 shot");
    check(distance(before,e.position)>.01f&&s.hazards.empty(),"shooting keeps rolling and creates no damaging trail");
    tick(s,30);check(r.shots==1,"31-tick shot spacing");tick(s);check(r.shots==2,"second Cyst shot after31ticks");
    s.projectiles.clear();s.limits.projectiles=0;tick(s,31);check(r.pendingShots.size()==1,"Cyst retains capacity-blocked shot");
    const auto pending=r.pendingShots.front();s.player.position={60,.85f,-60};tick(s,4);s.limits.projectiles=1;tick(s);
    check(r.shots==3&&s.projectiles.size()==1&&distance(s.projectiles[0].velocity,mul(pending.direction,pending.speed))<.001f,"Cyst retains original aim through capacity wait");
    auto cover=fixture();cover.arena.walls.push_back({{-79,0,40},{79,20,41}});auto c=cover.spawnMonster(monsterId(862),{0,.85f,0});tick(cover,32);
    check(cover.findEnemy(c)->guts->shots==1,"ordinary Cyst does not require line of sight to start shot");
    std::cout<<"CYST init=1 interval31=1 current_aim=1 rolling=1 no_creep=1 capacity=1\n";
}
void bounceAndBirth() {
    for(int v:{0,2}) {
        auto s=fixture();const auto id=spawn(s,v);acquire(s,id);tick(s,29);
        // Exercise real emitted projectiles against repeated lateral surfaces.
        // Narrow test enclosure shortens travel without changing shot physics.
        s.arena.walls={{{-2.1f,0,-2.1f},{-2,8,2.1f}},{{2,0,-2.1f},{2.1f,8,2.1f}},{{-2,0,-2.1f},{2,8,-2}},{{-2,0,2},{2,8,2.1f}}};
        s.enemies.clear();for(auto &p:s.projectiles){p.position.x=0;p.position.z=0;}
        tick(s,20);check(v==2?s.stats.bounces>8&&s.projectiles.size()>0:s.stats.bounces==0&&s.projectiles.empty(),"Dead Meat reflects repeatedly; ordinary ring stops at wall");
        tick(s,200);check(s.projectiles.empty(),"bouncing shots still land and expire");
    }
    for(int v=0;v<3;++v)for(int mode=0;mode<3;++mode) {
        auto s=fixture();const auto id=spawn(s,v);s.debugScenario=false;
        const auto expected=monsterId(v==0?32:v==1?40:862);
        damage(s,id,10000,mode!=0,mode==2);tick(s);
        if(mode==2){check(s.roomClear&&s.enemies.empty(),"debug clear suppresses children");continue;}
        check(!s.roomClear&&s.enemies.size()==2&&s.stats.kills==1,"ordinary overkill and gameplay execution retain two offspring");
        for(const auto &e:s.enemies)check(e.monster==expected&&(e.brain||e.guts)&&!s.arena.blocked(e.position,e.radius)&&length(e.velocity)<.001f,"correct legal offspring with zero birth impulse");
        const auto children=s.enemies;for(const auto &e:children)damage(s,e.id,10000);tick(s,3);
        check(s.roomClear&&s.stats.kills==3,"offspring gate room completion until both die");
    }
    auto s=fixture();const auto id=spawn(s,2);s.debugScenario=false;s.limits.enemies=1;damage(s,id,10000);tick(s);
    check(s.enemies.size()==1&&!s.roomClear,"one child admitted at capacity without losing second");
    damage(s,s.enemies.front().id,10000);tick(s);check(s.enemies.size()==1&&!s.roomClear,"retained second child appears after slot opens");
    damage(s,s.enemies.front().id,10000);tick(s,3);check(s.roomClear&&s.stats.kills==3,"retained births finish exactly once");
    std::cout<<"LIFECYCLE repeated_wall_bounce=1 ground_terminal=1 exact_children=1 execution=1 debug_clear=1 capacity=1 completion=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-membrain-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"membrains.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"membrains.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("30 70 29 32.0.0","30 80 29 32.0.0");check(changed->memBrain(monsterId(57))->attackFrames==80&&defaultMechanics()->memBrain(monsterId(57))->attackFrames==70,"immutable external reload");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".1 .5 .8 40",".1 .5 1 40"},{"30 70 29 32.0.0","30 70 70 32.0.0"},{"29 32.0.0 1","29 56.0.0 1"},{"Wander None Blob","Wander Ring Blob"},{"guts_shot 862.0.0 30 10","guts_shot 862.0.0 0 10"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or incompatible config rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=5\n";
}
void placement() {
    struct Witness {MonsterId id;uint64_t seed;int floor,room;};
    for(const auto w:std::array<Witness,4>{{{monsterId(57),0,5,2},{monsterId(57,1),1,5,7},
        {monsterId(57,2),16,3,10},{monsterId(862),22,7,1}}}) {
        Simulation s(w.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,w.floor);s.godMode=true;
        std::vector<EntityId> ids;
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==w.id) {
            check(!s.arena.blocked(e.position,e.radius)&&(w.id.type==57&&w.id.variant<2?s.arena.profile.band>=2:s.arena.profile.band==3),
                "appropriate habitat and legal natural footprint");ids.push_back(e.id);
        }
        check(!ids.empty(),"discovered natural witness still contains exact identity");
        tick(s,8);
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==w.id)
            check(e.idleTime>0&&(e.memBrain?e.memBrain->ticks:e.guts->ticks)==0,"unentered room advances ambient clock without attacks");
        s.enterRoom(w.room);s.player.position=s.arena.rooms[size_t(w.room)].entry;tick(s,8);
        for(auto id:ids){const auto *e=s.findEnemy(id);check(e&&(e->memBrain?e->memBrain->ticks:e->guts->ticks)>0,"natural resident activates dedicated controller");}
        std::cout<<"NATURAL_MEMBRAIN id="<<w.id.type<<'.'<<w.id.variant<<".0 seed="<<w.seed<<" floor="<<w.floor<<" room="<<w.room<<'\n';
    }
    std::cout<<"PLACEMENT four_natural_records=1 active_controllers=1\n";
}
}
int main(){std::cout<<std::unitbuf;try{attack();movementAndCapacity();cyst();bounceAndBirth();configuration();placement();std::cout<<"PASS MemBrain family and Cyst\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
