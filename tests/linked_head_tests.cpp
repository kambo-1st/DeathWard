#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float epsilon=.006f){return std::abs(a-b)<epsilon;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,20,100}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={60,.85f,0};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage=10000,bool execute=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.execution=execute;s.queueRoot(e);s.drainEvents();
}
std::pair<EntityId,EntityId> pair(Simulation &s,int variant=0) {
    const auto id=s.spawnMonster(monsterId(35,variant),{0,.85f,0});tick(s);
    const auto *body=s.findEnemy(id);check(body&&body->partner,"required head has been allocated");
    return {id,body->partner};
}
void identityAndSurvivors() {
    for(int variant:{0,2}) {
        auto s=fixture();const auto [body,head]=pair(s,variant);
        check(s.findEnemy(body)->linkedHead&&s.findEnemy(head)->linkedHead&&near(s.findEnemy(body)->hp,80)&&
            near(s.findEnemy(head)->hp,variant==0?80:32),"source body25/head25or10 health");
        check(s.findEnemy(head)->partner==body&&distance(s.findEnemy(body)->position,s.findEnemy(head)->position)<.001f,
              "head is attached at birth, links are reciprocal");
        check(near(s.findEnemy(head)->lift,.65f),"head has its carried visual pose before first controller update");
        check(!s.spawnMonster(monsterId(35,10),{5,.85f,5}),"neck cannot spawn independently");
        hit(s,body,24);check(near(s.findEnemy(body)->hp,56)&&near(s.findEnemy(head)->hp,variant==0?80:32),"health is not shared");
        hit(s,body);check(s.findEnemy(head)->monster==monsterId(26,variant==2?1:0)&&near(s.findEnemy(head)->hp,64),
                         "body death releases the existing head at full Maw health");
        check(s.livingEnemies()==1&&!s.findEnemy(head)->linkedHead&&!s.findEnemy(head)->partner,
              "body death does not spawn an extra Gusher");
        auto h=fixture();const auto [b,k]=pair(h,variant);hit(h,b,72);hit(h,k);
        check(h.findEnemy(b)->monster==monsterId(11)&&near(h.findEnemy(b)->hp,h.content->monsterHealth(monsterId(11),0)),
              "head death morphs existing body into a full-health Gusher");
        check(h.projectiles.size()==size_t(variant==2?4:0),"only red head emits death cross");
        for(const auto &shot:h.projectiles) {
            check(near(length(shot.velocity),24)&&near(shot.damage,10),"red cross speed and damage");
            check(std::min(std::abs(shot.velocity.x),std::abs(shot.velocity.z))<.001f,"red cross stays cardinal");
        }
        auto execution=fixture();const auto [eb,eh]=pair(execution,variant);hit(execution,eb,10000,true);
        check(execution.findEnemy(eh)->monster==monsterId(26,variant==2?1:0),"non-debug execution still releases survivor");
    }
    auto orphan=fixture();auto id=orphan.spawnMonster(monsterId(35,3),{0,.85f,0});tick(orphan);
    check(orphan.findEnemy(id)->monster==monsterId(26,1)&&near(orphan.findEnemy(id)->hp,64),"orphan head becomes independent Red Maw");
    std::cout<<"IDENTITY independent_hp=1 body_death=maw head_death=gusher red_cross=4 neck_harmless=1\n";
}
void motionAndAttack() {
    auto s=fixture();const auto [body,head]=pair(s);
    // Freeze the source clocks for exact scalar recurrence assertions.
    auto &b=*s.findEnemy(body);b.linkedHead->initialized=true;b.linkedHead->clock=0;b.velocity={};
    auto &h=*s.findEnemy(head);h.linkedHead->initialized=true;h.linkedHead->clock=0;
    tick(s,2);check(near(b.velocity.x,3.6f),"path force .6*min(distance/10,2), local speed x3");
    tick(s,2);check(near(b.velocity.x,3.6f*.7f+3.6f),"path .7 retention is applied before source force");
    b.position={0,.85f,0};h.position=b.position;b.velocity={};h.velocity={};s.player.position={10,.85f,0};
    for(int i=0;i<12&&!b.linkedHead->extended;++i)tick(s);
    check(b.linkedHead->extended&&h.linkedHead->throws==1&&near(length(h.velocity),42),"head launches at native14 converted x3");
    check(h.linkedHead->neckCount==8&&s.livingEnemies()==2,"eight visual components are not eight room threats");
    check((uint64_t(std::floor(s.stats.duration*30+1e-4))+head)%4==0,"throw uses staggered global4 check");
    const float old=h.velocity.x;const int timer=b.linkedHead->timer;tick(s,2);
    const float force=1.4f-.7f*std::clamp(float(timer-1+30)/45,0.f,1.f);
    const float expected=(old/3-force)*(.9f+float(timer-1)*.0028f)*3;
    check(near(h.velocity.x,expected,.03f),"return spring is added before timer-dependent friction");
    s.player.position={60,.85f,50};for(int n=0;n<180&&b.monster==monsterId(35)&&!b.linkedHead->returns;++n)tick(s);
    check(b.monster==monsterId(35)&&b.linkedHead->returns==1&&!b.linkedHead->extended&&h.linkedHead->neckCount==0,
          "committed throw returns and hides cord without chasing the displaced player");
    auto cover=fixture();cover.arena.obstacles.push_back({{4,0,-12},{5,5,12}});cover.arena.rebuildWalls();
    const auto [cb,ch]=pair(cover);cover.player.position={10,.85f,0};tick(cover,20);
    check(!cover.findEnemy(ch)->linkedHead->throws&&!sphereBox(cover.findEnemy(cb)->position,.65f,cover.arena.obstacles[0]),
          "cover blocks acquisition and grounded body movement");
    auto contact=fixture();const auto [tb,th]=pair(contact);contact.godMode=false;contact.player.position=contact.findEnemy(tb)->position;
    tick(contact);check(near(contact.player.hp,87.5f),"body/head contact uses normal one-unit damage with shared multiplier once");
    std::cout<<"MOTION pursuit=1 global4=1 launch42=1 spring_order=1 return=1 cover=1 contact12.5=1\n";
}
void capacityAndCompletion() {
    auto s=fixture();s.limits.enemies=1;const auto body=s.spawnMonster(monsterId(35),{0,.85f,0});tick(s,8);
    check(s.livingEnemies()==1&&!s.findEnemy(body)->partner&&near(length(s.findEnemy(body)->velocity),0),"capacity retains required head without incomplete attack");
    s.limits.enemies=2;tick(s);check(s.findEnemy(body)->partner&&s.livingEnemies()==2,"required head retries after capacity opens");
    auto dead=fixture();dead.limits.enemies=1;const auto pending=dead.spawnMonster(monsterId(35),{0,.85f,0});tick(dead,4);hit(dead,pending);tick(dead,2);
    check(dead.livingEnemies()==1&&std::any_of(dead.enemies.begin(),dead.enemies.end(),[](const auto &e){return e.alive&&e.monster==monsterId(26);}),
          "body killed before head allocation leaves its required Maw survivor");
    auto finish=fixture();finish.debugScenario=false;const auto [b,h]=pair(finish);hit(finish,b);tick(finish);
    check(!finish.roomClear&&finish.livingEnemies()==1,"body death cannot clear room with surviving head");
    hit(finish,h);tick(finish);check(finish.roomClear,"last released head death clears room");
    auto cross=fixture();const auto [rb,rh]=pair(cross,2);cross.limits.projectiles=3;hit(cross,rh);tick(cross,2);
    check(cross.findEnemy(rh)&&cross.findEnemy(rh)->linkedHead->deathPending&&cross.projectiles.empty(),"full red cross waits atomically at capacity");
    cross.limits.projectiles=8;tick(cross);check(cross.projectiles.size()==4,"retained red death cross retries exactly once");
    std::cout<<"LIFECYCLE required_birth_retry=1 prebirth_death=1 completion=1 red_cross_retry=1\n";
}
void configurationAndSeparation() {
    const auto root=std::filesystem::temp_directory_path()/("dw-linked-head-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")
        std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"linked_heads.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](const std::string &from,const std::string &to){auto text=original;const auto at=text.find(from);
        check(at!=text.npos,"configuration fixture exists");text.replace(at,from.size(),to);
        std::ofstream(root/"linked_heads.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit(".1 .6 .7 .7 10 22 1000",".1 .6 .7 .7 10 22 1");
    check(changed->linkedHead(monsterId(35,1))->splitChance==1&&defaultMechanics()->linkedHead(monsterId(35,1))->splitChance==1000,
          "body and head share externally loaded profile without modifying current snapshot");
    auto s=fixture(changed);const auto [b,h]=pair(s);hit(s,b,24);hit(s,h,24);tick(s,8);
    check(s.findEnemy(b)->monster==monsterId(11)&&s.findEnemy(h)->monster==monsterId(26)&&s.stats.kills==0&&s.projectiles.empty(),
          "voluntary split releases both actors without deaths or death cross");
    check(near(s.findEnemy(h)->hp,64)&&near(s.findEnemy(b)->hp,40),"split refills each replacement to its configured health");
    for(const auto &change:std::vector<std::pair<std::string,std::string>>{
        {".1 .6 .7 .7 10 22 1000",".1 -.6 .7 .7 10 22 1000"},
        {"30 -30 15 1.4 .7 45 .9 .0028","30 -30 15 1.4 .7 45 1.2 .0028"},
        {"35.0.0 8 .09 .65 .35","35.0.0 17 .09 .65 .35"},
        {"35.1.0 35.10.0 11.0.0 26.0.0","35.1.0 35.10.0 35.0.0 26.0.0"},
        {"linked_head_throw 35.0.0 4 130 3 14 5 30 -30 15 1.4 .7 45 .9 .0028",""}}) {
        bool rejected=false;try{edit(change.first,change.second);}catch(const std::exception&){rejected=true;}
        check(rejected,"invalid/incomplete linked head configuration rejected");
    }
    std::cout<<"CONFIG shared_profile=1 immutable=1 voluntary_split=1 invalid_profiles=5\n";
}
void startingKit() {
    for(int variant:{0,2})for(bool cover:{false,true}) {
        auto s=fixture();s.godMode=false;s.player.position={0,.85f,10};
        s.arena.bounds={{-30,-1,-30},{30,20,30}};
        for(auto &room:s.arena.rooms){room.bounds=s.arena.bounds;room.floors={{{-30,-.4f,-30},{30,0,30}}};}
        if(cover)s.arena.obstacles.push_back({{2,0,2},{4,3,5}});
        s.arena.rebuildWalls();const auto id=s.spawnMonster(monsterId(35,variant),{0,.85f,0});int frames=0;
        check(near(s.player.hp,100),"starting-kit health unchanged");
        while(s.roomThreats()&&!s.dead&&frames<2400) {
            const auto *target=s.findEnemy(id);
            if(!target||!target->alive) {
                target=nullptr;float best=1e9f;
                for(const auto &e:s.enemies)if(e.alive&&!e.friendly&&planarDistance(e.position,s.player.position)<best) {
                    target=&e;best=planarDistance(e.position,s.player.position);
                }
            }
            Input input;input.fire=true;
            if(target) {
                const auto delta=horizontal(sub(target->position,s.player.position));const float range=length(delta);
                input.aim=add(target->position,mul(target->velocity,std::min(.35f,range/26)));
                input.movement=range>14?unit(delta):range<8?mul(unit(delta),-1):rotateY(unit(delta),Pi/2);
                // Steer away from the visible head's current flight lane. No
                // actor state writes, scripted damage, invulnerability or items.
                for(const auto &e:s.enemies)if(e.alive&&e.linkedHead&&e.linkedHead->extended&&s.content->monster(e.monster)->flying) {
                    const auto direction=unit(horizontal(e.velocity));const Vector3 side{-direction.z,0,direction.x};
                    const float lateral=dot(horizontal(sub(s.player.position,e.position)),side);
                    if(planarDistance(s.player.position,e.position)<10&&std::abs(lateral)<2)
                        input.movement=mul(side,lateral<0?-1.f:1.f);
                }
                if(std::max(std::abs(s.player.position.x),std::abs(s.player.position.z))>24)
                    input.movement=unit(mul(horizontal(s.player.position),-1));
            }
            s.step(input);++frames;
        }
        std::cout<<"STARTING_KIT variant="<<variant<<" cover="<<cover<<" seconds="<<frames*Tick
            <<" hp="<<s.player.hp<<" threats="<<s.roomThreats()<<" shots="<<s.stats.shots<<'\n';
        check(!s.dead&&s.roomThreats()==0,"default kit defeats body and every surviving part");
    }
}
}
int main(){try{identityAndSurvivors();motionAndAttack();capacityAndCompletion();configurationAndSeparation();startingKit();std::cout<<"PASS linked head family\n";return 0;}
catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
