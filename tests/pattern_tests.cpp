#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.001f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine);s.enemies.clear();s.arena=Arena{};
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;}
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,8,26}},{{25,-1,-26},{26,8,26}},
        {{-26,-1,-26},{26,8,-25}},{{-26,-1,25},{26,8,26}}};s.arena.rebuildWalls();
    s.rooms.assign(s.arena.rooms.size(),{});s.room=0;s.player.position={9,.85f,17};
    s.godMode=true;s.debugScenario=true;s.roomClear=false;return s;
}
void tick(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
EntityId ready(Simulation &s,MonsterId id) {
    const auto entity=s.spawnMonster(id,{0,.85f,0});s.findEnemy(entity)->cooldown=0;return entity;
}
void volley(Simulation &s) {
    const auto before=s.stats.projectiles;
    for(int i=0;i<400&&s.stats.projectiles==before;++i)s.step({});
    check(s.stats.projectiles>before,"periodic attack never arrived");
}
void fixedAxes() {
    struct Case {MonsterId id;int count;float angle;ProjectileKind kind;};
    for(const auto test:{Case{monsterId(15),4,0,ProjectileKind::Bullet},
        Case{monsterId(15,1),4,Pi/4,ProjectileKind::Tar},
        Case{monsterId(15,2),8,0,ProjectileKind::Bullet},
        Case{monsterId(15,3),4,.12f,ProjectileKind::Ember}}) {
        auto s=fixture();const auto id=ready(s,test.id);s.findEnemy(id)->facing={.6f,0,.8f};
        s.step({});check(s.findEnemy(id)->state==EnemyState::Windup,"windup has a readable body pose");
        const auto windupAt=s.findEnemy(id)->position;tick(s,10);
        check(distance(windupAt,s.findEnemy(id)->position)>.2f,"wandering continues through attack windup");
        volley(s);check(s.projectiles.size()==size_t(test.count),"correct full volley count");
        for(int i=0;i<test.count;++i) {
            const auto &p=s.projectiles[size_t(i)];
            const auto expected=rotateY({9,0,0},test.angle+float(i)*2*Pi/test.count);
            check(distance(p.velocity,expected)<.001f,"shot uses room axes, not player or movement heading");
            check(p.kind==test.kind&&near(p.angularVelocity,0),"straight variant projectile type");
        }
        // A later volley must not rotate with age or retarget to the opposite player side.
        s.projectiles.clear();s.player.position={-17,.85f,-9};volley(s);
        for(int i=0;i<test.count;++i)
            check(distance(s.projectiles[size_t(i)].velocity,rotateY({9,0,0},test.angle+float(i)*2*Pi/test.count))<.001f,
                "repeat pattern stays aligned after target relocation");
        check(s.roomThreats()==1,"live blob remains a room threat");
        std::cout<<"PATTERN id="<<monsterIdText(test.id)<<" count="<<test.count<<" axes_repeat=1 windup_moving=1\n";
    }
    auto a=fixture(),b=fixture();auto aid=ready(a,monsterId(15)),bid=ready(b,monsterId(15,3));
    tick(a,10);tick(b,10);
    check(distance(b.findEnemy(bid)->position,{0,.85f,0})>distance(a.findEnemy(aid)->position,{0,.85f,0})*1.6f,
        "Grilled moves faster; faster firing is not invented from the word quicker");
}
void curvedVolleys() {
    auto s=fixture();const auto id=ready(s,monsterId(872));volley(s);
    check(s.projectiles.size()==4,"Cloggy four-way volley");
    const auto first=s.projectiles.front();
    for(const auto &p:s.projectiles)check(near(p.angularVelocity,.9f)&&p.kind==ProjectileKind::Brown,"first volley curves together");
    tick(s,20);
    const auto &curved=s.projectiles.front();
    check(distance(curved.velocity,rotateY(first.velocity,.9f*20*Tick))<.001f,"actual projectile heading follows configured curvature");
    check(near(length(curved.velocity),9),"curvature preserves projectile speed");
    check(distance(curved.position,add(first.position,mul(first.velocity,20*Tick)))>.3f,"actual path bends away from original ray");
    s.projectiles.clear();volley(s);
    for(const auto &p:s.projectiles)check(near(p.angularVelocity,-.9f),"second volley reverses handedness");
    s.projectiles.clear();s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=.25f;
    tick(s,16);volley(s);
    for(const auto &p:s.projectiles)check(near(p.angularVelocity,.9f),"stun cancels attack but retains volley parity");
    s.projectiles.clear();s.enterRoom(1);tick(s,30);s.enterRoom(0);volley(s);
    for(const auto &p:s.projectiles)check(near(p.angularVelocity,-.9f),"room re-entry preserves alternating parity");
    const auto shot=s.projectiles.front();Event death;death.type=EventType::Damage;death.target=id;death.damage=1000;
    s.queueRoot(death);s.drainEvents();tick(s,1);
    check(!s.projectiles.empty()&&distance(s.projectiles.front().velocity,rotateY(shot.velocity,-.9f*Tick))<.001f,
        "curved shots remain independent of shooter death");
    std::cout<<"CURVE alternating=1 stun_parity=1 reentry_parity=1 survives_owner=1\n";
}
void surfaceEffectsAndCollision() {
    auto s=fixture();const auto id=ready(s,monsterId(15,1));volley(s);
    s.findEnemy(id)->cooldown=1000;tick(s,80);
    check(s.hazards.size()==4,"four expired tar shots leave slowing patches");
    tick(s,14); // Existing patch primitive has a .2-second landing/activation delay.
    const auto patch=s.hazards.front();s.player.position=patch.position;s.player.slowTime=0;
    const auto hp=s.player.hp;s.godMode=false;tick(s,1);
    check(s.player.slowTime>0&&s.player.hp==hp,"tar patches slow without ground damage");
    s.player.position={20,.85f,20};tick(s,180);check(s.hazards.empty(),"tar patches expire");
    auto ember=fixture();const auto grilled=ready(ember,monsterId(15,3));volley(ember);
    ember.findEnemy(grilled)->cooldown=1000;tick(ember,340);
    check(ember.hazards.empty(),"ember shots do not silently create damaging fire patches");
    auto impact=fixture();impact.arena.obstacles.push_back({{3,0,-8},{4,4,8}});impact.arena.rebuildWalls();
    const auto cloggy=ready(impact,monsterId(872));volley(impact);impact.findEnemy(cloggy)->cooldown=1000;
    const auto forward=impact.projectiles.front().id;tick(impact,35);
    check(std::none_of(impact.projectiles.begin(),impact.projectiles.end(),[&](const auto &p){return p.id==forward;}),
        "curved projectile is swept against cover instead of passing through it");
    auto contact=fixture();ready(contact,monsterId(15));contact.player.position={.9f,.85f,0};contact.godMode=false;tick(contact,1);
    check(near(contact.player.hp,StartingHealth-12.5f),"body contact retains global hostile damage scaling");
    auto finish=fixture();ready(finish,monsterId(872));finish.debugScenario=false;finish.clearRoomDebug();
    check(finish.roomClear&&finish.roomThreats()==0,"ordinary Cloggy is cleared with the room");
    std::cout<<"SURFACES tar_slow_only=1 ember_no_fire_patch=1 curved_cover_collision=1\n";
}
void baselineFights() {
    for(auto monster:{monsterId(15),monsterId(15,1),monsterId(15,2),monsterId(15,3),monsterId(872)}) {
        auto s=fixture();s.godMode=false;s.player.position={7,.85f,8};const auto id=ready(s,monster);
        int frames=0;
        while(s.roomThreats()&&frames<1800&&!s.dead) {
            Input input;input.fire=true;
            if(const auto *e=s.findEnemy(id))input.aim=e->position;
            s.step(input);++frames;
        }
        check(s.roomThreats()==0&&!s.dead,"default revolver can defeat isolated patterned enemy");
        std::cout<<"PATTERN_STARTING_KIT id="<<monsterIdText(monster)<<" seconds="<<frames*Tick<<" health="<<s.player.hp<<'\n';
    }
}
}
int main(){try{fixedAxes();curvedVolleys();surfaceEffectsAndCollision();baselineFights();std::cout<<"PASS monster patterns\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
