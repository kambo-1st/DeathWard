#include "combat/Simulation.hpp"
#include "combat/LobFlight.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.005f){return std::abs(a-b)<eps;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("dw-leapers-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(root);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());std::ifstream in(root/"leapers.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(root);}
    std::shared_ptr<const MechanicsLibrary> load(std::string from,std::string to){auto s=original;auto at=s.find(from);check(at!=s.npos,"configuration fixture exists");s.replace(at,from.size(),to);std::ofstream(root/"leapers.mechanics")<<s;return MechanicsLibrary::load(root);}
};
Simulation fixture(int variant=0) {
    Pack pack;const auto id="34."+std::to_string(variant)+".0";
    auto lib=pack.load("leaper "+id+" 7","leaper "+id+" 1");
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{40,14,40}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-40,-.4f,-40},{40,0,40}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s,int variant=0){return s.spawnMonster(monsterId(34,variant),{0,.85f,0});}
void begin(Simulation &s,EntityId id) {
    auto &e=*s.findEnemy(id);auto &hop=*e.targetHop;hop.initialized=true;hop.lastGround=e.position;
    hop.targetReady=true;hop.destination=e.position;hop.frame=25;hop.clock=0;e.velocity={};
    tick(s,2);check(e.leaper->phase==1&&e.leaper->frame==0,"source destination release selects high leap");
}
void damage(Simulation &s,EntityId id){Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=10000;s.queueRoot(hit);s.drainEvents();}
void timingAndAttacks() {
    for(int variant:{0,1}) {
        auto s=fixture(variant);const auto id=spawn(s,variant);auto &e=*s.findEnemy(id);
        check(near(e.hp,variant?89.6f:80)&&e.targetHop&&e.leaper,"source HP and dedicated controllers");
        tick(s,38);check(e.targetHop->landings==1&&e.leaper->leaps==0&&s.stats.projectiles==0,"ordinary Land17 emits no generic Cross/Burst");
        check(s.hazards.size()==size_t(variant),"only Sticky ordinary landing creates creep");
        if(variant){check(near(s.hazards.front().radius,1.5f)&&near(s.hazards.front().duration,10)&&s.hazards.front().damage==0,"small slow-only creep");}
        auto high=fixture(variant);const auto actor=spawn(high,variant);begin(high,actor);auto &body=*high.findEnemy(actor);
        const auto destination=body.leaper->target;
        tick(high,8);check(body.leaper->frame==4&&!body.targetHop->airborne,"BigJumpUp prepares for five source frames");
        high.player.position={-25,.85f,-25};tick(high,2);
        check(body.leaper->frame==5&&body.targetHop->airborne&&near(body.leaper->progress,.02f),"Jump5 begins progressive flight");
        check(near(body.position.z,.16f),"first native interpolation is target delta times.02");
        tick(high,14);check(body.leaper->phase==2&&body.leaper->frame==0&&near(body.leaper->progress,.16f),"Up12 transitions to Down0 with continued interpolation");
        tick(high,42);check(body.leaper->frame==21&&body.targetHop->airborne&&high.stats.projectiles==0,"no premature landing at Down21");
        check(distance(body.leaper->target,destination)<.001f,"high target snapshot never follows a moving player");
        tick(high,2);check(body.leaper->frame==22&&!body.targetHop->airborne&&body.leaper->bigLandings==1,"Land22 restores grounded body once");
        check(high.stats.projectiles==uint64_t(variant?6:4)&&body.leaper->volleys==1,"exact high-landing volley");
        check(high.projectiles.size()==size_t(variant?6:4),"complete packet exists");
        for(const auto &shot:high.projectiles) {
            check(shot.hostile&&shot.context.sourceEntity==actor&&shot.kind==ProjectileKind::Bullet,"physical shots retain owner without Tar impact behavior");
            check(near(length(horizontal(shot.velocity)),variant?21:27)&&near(shot.flightRetention,.9f),"native planar velocity and damping");
            if(variant) {
                check(near(shot.gravity,63.9f)&&shot.velocity.y>7&&shot.velocity.y<43.5f&&shot.tint.a==255,"trajectory10 and custom color");
                check((shot.radius>=.1386f&&shot.radius<=.14631f)||(shot.radius>=.2002f&&shot.radius<=.20791f),"source bimodal size times.7");
            } else {
                check(near(shot.gravity,4.5f)&&shot.velocity.y<.15f&&shot.velocity.y>-.3f&&!shot.tint.a,"normal source falling shot");
                check(std::abs(shot.velocity.x)<.01f||std::abs(shot.velocity.z)<.01f,"world-cardinal cross rather than aimed ring");
            }
        }
        const auto patches=body.leaper->creepPatches;
        check(patches==variant&&(!variant||near(high.hazards.front().radius,2)),"big landing creep scale2 only for Sticky");
        tick(high,34);check(body.leaper->phase==2&&body.leaper->frame==39,"full landing recovery");
        tick(high,2);check(body.leaper->phase==0&&body.leaper->volleys==1,"Down40 returns to ordinary hopping without extra volley");
        damage(high,actor);tick(high,180);check(high.hazards.size()==size_t(variant),"shots never invent impact tar and released creep survives death");
    }
    std::cout<<"PASS ordinary hops, native BigJump timing, target snapshot, cardinal/scattered shots, flight and creep\n";
}
void capacityLifecycle() {
    auto s=fixture(1);auto id=spawn(s,1);begin(s,id);s.limits.projectiles=5;tick(s,300);
    auto *e=s.findEnemy(id);check(e->leaper->pending&&e->leaper->leaps==1&&s.stats.projectiles==0&&s.hazards.empty(),"bounded whole landing waits for all six shot slots");
    s.limits.projectiles=64;s.limits.hazards=0;tick(s,4);check(s.stats.projectiles==0,"packet also waits for required creep capacity");
    s.limits.hazards=64;tick(s);check(s.stats.projectiles==6&&s.hazards.size()==1&&!e->leaper->pending,"capacity recovery releases one complete packet");
    auto room=fixture();id=spawn(room);begin(room,id);tick(room,20);const auto before=*room.findEnemy(id)->leaper;const auto pos=room.findEnemy(id)->position;
    room.enterRoom(1);tick(room,120);room.enterRoom(0);
    check(room.findEnemy(id)->leaper->frame==before.frame&&distance(room.findEnemy(id)->position,pos)<.001f,"inactive rooms freeze committed leap and pose");
    tick(room,60);check(room.findEnemy(id)->leaper->volleys==1,"re-entry resumes once");
    auto stun=fixture(1);id=spawn(stun,1);begin(stun,id);tick(stun,12);stun.findEnemy(id)->state=EnemyState::Stunned;stun.findEnemy(id)->stateTime=2;
    tick(stun,60);e=stun.findEnemy(id);check(!e->targetHop->airborne&&e->leaper->pending&&stun.stats.projectiles==0,"airborne stun lands safely and retains its attack until recovery");
    tick(stun,70);check(stun.stats.projectiles==6,"recovered actor emits deferred landing once");
    auto dead=fixture(1);dead.debugScenario=false;id=spawn(dead,1);begin(dead,id);dead.limits.projectiles=0;tick(dead,70);damage(dead,id);tick(dead,5);
    check(dead.stats.kills==1&&dead.roomClear,"death discards pending landing and resolves ordinary threat");
    dead.limits.projectiles=64;tick(dead,60);check(dead.stats.projectiles==0&&dead.hazards.empty(),"dead body never emits retained packet");
    auto released=fixture();released.debugScenario=false;id=spawn(released);begin(released,id);released.player.position={-25,.85f,-25};tick(released,68);damage(released,id);tick(released);
    check(!released.projectiles.empty()&&!released.roomClear,"released shots survive owner and hold completion");tick(released,300);check(released.roomClear,"completion resumes after physical shots expire");
    std::cout<<"PASS bounded capacity, room suspension, stun, death and surviving-shot completion\n";
}
void terrainAndConfig() {
    auto cover=fixture();cover.arena.obstacles.push_back({{-3,0,3},{3,2,5}});cover.arena.rebuildWalls();auto id=spawn(cover);begin(cover,id);cover.player.position={-25,.85f,-25};float peak=0;
    for(int i=0;i<70;++i){tick(cover);const auto &e=*cover.findEnemy(id);peak=std::max(peak,e.position.y);check(!sphereBox(e.position,e.radius,cover.arena.obstacles.front()),"real high body clears cover");}
    std::cout<<"COVER peak="<<peak<<" z="<<cover.findEnemy(id)->position.z<<" target="<<cover.findEnemy(id)->leaper->target.z<<"\n";check(peak>6&&cover.findEnemy(id)->position.z>7.9f&&!cover.arena.blocked(cover.findEnemy(id)->position,.6f),"high leap lands beyond cover");
    auto water=fixture();auto terrain=std::make_shared<CanyonTerrain>();terrain->x=terrain->z=-40;terrain->step=1;terrain->width=terrain->depth=81;
    terrain->heights.assign(81*81,0);terrain->boundaryHeights=terrain->heights;terrain->river={{{-40,0,4},1,0},{{40,0,4},1,80}};terrain->riverKind=CanyonRiverKind::Interior;
    for(int x=0;x<81;++x)terrain->heights[size_t(44*81+x)]=-1.5f;water.arena.canyon=terrain;id=spawn(water);begin(water,id);bool crossed=false;
    for(int i=0;i<70;++i){tick(water);const auto &e=*water.findEnemy(id);if(terrain->waterBlocked(e.position)){crossed=true;check(e.targetHop->airborne&&e.position.y>1,"river traversed only while physically airborne");}}
    check(crossed&&!water.arena.blocked(water.findEnemy(id)->position,.6f),"river ends on legal ground");
    auto target=fixture();target.arena.obstacles.push_back({{-1,0,7},{1,2,9}});target.arena.rebuildWalls();id=spawn(target);begin(target,id);
    check(!target.arena.blocked(target.findEnemy(id)->leaper->target,.6f)&&distance(target.findEnemy(id)->leaper->target,target.player.position)<=12,"blocked target searches nearby legal ground");
    Pack pack;
    for(const auto &[from,to]:std::array<std::pair<std::string,std::string>,4>{{{"7 12 5 40 22","7 12 12 40 22"},{".02 6 12","0 6 12"},{"4.5 .9 .22","4.5 1 .22"},{"1.5 2 10","1.5 -2 10"}}}) {
        bool rejected=false;try{pack.load(from,to);}catch(...){rejected=true;}check(rejected,"invalid external leap contract rejected");
    }
    const auto changed=pack.load("4 27 10 6","4 30 10 6");
    check(near(changed->leaper(monsterId(34))->speed,30)&&near(defaultMechanics()->leaper(monsterId(34))->speed,27)&&defaultMechanics()->leaper(monsterId(34))->chance==7,"immutable reload and original one-in-seven choice");
    std::cout<<"PASS real cover/river geometry, legal target adjustment, validated immutable reload\n";
}
void collisionAndSlow() {
    auto bullet=[](Simulation &s,Vector3 at) {
        Event shot;shot.position=shot.origin=at;shot.direction={1,0,0};shot.speed=.1f;
        AttackSpec spec;spec.damage=24;spec.speed=.1f;spec.radius=.4f;spec.life=1;shot.attack=spec;
        s.queueRoot(shot);s.drainEvents();
    };
    auto ground=fixture();auto id=spawn(ground);bullet(ground,ground.findEnemy(id)->position);tick(ground);
    check(near(ground.findEnemy(id)->hp,56),"grounded Leaper accepts physical player projectile");
    auto air=fixture();id=spawn(air);begin(air,id);tick(air,20);const auto before=air.findEnemy(id)->hp;
    bullet(air,air.findEnemy(id)->position);tick(air);
    check(near(air.findEnemy(id)->hp,before)&&!air.projectiles.empty(),"native high-air collision window lets ordinary projectile pass");
    auto slow=fixture(1);id=spawn(slow,1);begin(slow,id);slow.player.position={-20,.85f,-20};tick(slow,68);damage(slow,id);
    check(slow.hazards.size()==1,"landing produced source-owned slow patch");
    slow.player.position=slow.hazards.front().position;tick(slow);
    check(slow.player.slowTime>0&&near(slow.player.hp,StartingHealth),"black creep slows without damage after owner dies");
    slow.hazards.front().harmsPlayer=false;slow.player.slowTime=0;tick(slow);
    check(slow.player.slowTime==0,"friendly patch respects harmsPlayer flag");
    std::cout<<"PASS grounded/high-air projectile windows and non-damaging hostile/friendly slow patches\n";
}
void placementAndKit() {
    std::array<bool,2> found{};
    for(uint64_t seed=0;seed<256&&(!found[0]||!found[1]);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            const auto band=plan.profileOnFloor(floor).band;if(band<1||band>2)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==34) {
                const auto v=size_t(e.monster.variant);check(v<2&&e.leaper&&e.targetHop&&(!v||band==2),"source-compatible middle habitats and dedicated AI");
                if(!found[v])std::cout<<"NATURAL_LEAPER variant="<<v<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';found[v]=true;
            }
        }
    }
    check(found[0]&&found[1],"both regular variants seed-reachable");
    for(int v:{0,1}) {
        auto s=fixture(v);auto id=spawn(s,v);s.godMode=false;s.player.position={0,.85f,14};int frames=0;
        for(;frames<1800&&s.findEnemy(id)&&s.findEnemy(id)->alive&&!s.dead;++frames){Input in;in.fire=true;in.aim=s.findEnemy(id)->position;s.step(in);}
        check(!s.dead&&s.stats.kills==1,"default100HP/24damage kit kills regular variant");
        std::cout<<"LEAPER_STARTING_KIT variant="<<v<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<'\n';
    }
}
}
int main(){try{timingAndAttacks();capacityLifecycle();terrainAndConfig();collisionAndSlow();placementAndKit();std::cout<<"PASS Leaper and Sticky Leaper\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
