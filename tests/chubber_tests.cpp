#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float tolerance=.006f){return std::abs(a-b)<tolerance;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,20,100}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={70,.85f,70};return s;
}
void tick(Simulation &s,int frames=1,float dt=1.f/30){for(int i=0;i<frames;++i)s.step({},dt);}
void damage(Simulation &s,EntityId id,bool execution=false){Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=10000;hit.execution=execution;s.queueRoot(hit);s.drainEvents();}
EntityId parent(Simulation &s,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(39,2),at);}
void ready(Simulation &s,EntityId id,Vector3 heading={1,0,0}) {
    auto &e=*s.findEnemy(id);auto &r=*e.vis;r.initialized=true;r.heading=heading;
    r.attackFrame=17;r.fired=false;e.velocity={};
}
EntityId body(const Simulation &s) {
    for(const auto &e:s.enemies)if(e.alive&&e.returningBody)return e.id;
    return 0;
}
void freeze(Simulation &s,EntityId id){auto &e=*s.findEnemy(id);e.state=EnemyState::Stunned;e.stateTime=100;e.velocity={};}
void launchAndReturn() {
    for(bool horizontal:{false,true}) {
        auto s=fixture();const auto id=parent(s);auto &e=*s.findEnemy(id);
        check(e.hp==80&&e.maxHp==80&&e.vis,"Chubber source health and dedicated controller");
        s.player.position=horizontal?Vector3{15,.85f,0}:Vector3{0,.85f,15};
        for(int n=0;n<5&&e.vis->attackFrame<0;++n)tick(s);
        check(e.vis->attackFrame==0,"cardinal target acquires Chubber windup");
        s.player.position={70,.85f,70};tick(s,17);
        check(!body(s),"no component before frame18");
        const auto start=s.findEnemy(id)->position;tick(s);
        const auto child=body(s);check(child&&s.hazards.empty()&&s.projectiles.empty(),"Shoot18 creates owned body, not generic projectile");
        const auto *c=s.findEnemy(child);
        check(c->componentOwner==id&&c->hp==0&&c->maxHp==0&&s.roomThreats()==1,"zero HP, owned and not independent threat");
        check(near(c->position.x,start.x)&&near(c->position.z,start.z+(horizontal?.01f:0),.03f),"child launches inside parent without placement search");
        const auto born=c->position;freeze(s,id);
        check(near(length(c->returningBody->initialVelocity),horizontal?67.2f:48.f),"horizontal16*1.4 and vertical16 source velocities");
        s.arena.obstacles.push_back(horizontal?Box{{5,0,-3},{7,5,3}}:Box{{-3,0,5},{3,5,7}});s.arena.rebuildWalls();
        tick(s,21);c=s.findEnemy(child);
        check(c&&near(planarDistance(c->position,born),horizontal?24.64f:17.6f),"outbound arithmetic series passes through solid cover");
        const auto furthest=c->position;tick(s);
        check(near(planarDistance(s.findEnemy(child)->position,furthest),0),"frame21 is stationary turnaround");
        s.findEnemy(id)->position=add(born,horizontal?Vector3{0,0,8}:Vector3{8,0,0});tick(s);
        c=s.findEnemy(child);check(c&&(horizontal?c->velocity.z>0:c->velocity.x>0),"return curves toward moved parent");
        tick(s,19);check(body(s)==child,"component remains through source counter41");tick(s);
        check(body(s)==child&&s.findEnemy(child)->returningBody->frame==43,"counter42 update remains alive: native tests before increment");tick(s);
        check(!body(s)&&s.findEnemy(id)->monster==monsterId(39,2),"timeout cleans only component without parent morph");
    }
    auto s=fixture();const auto id=parent(s);ready(s,id);tick(s);tick(s,51);
    check(s.findEnemy(id)->vis->attackFrame==-1,"Chubber completes69-frame attack");
    std::cout<<"TRAJECTORY Shoot18 attack69 vertical48 horizontal67.2 reversal21 last_active_counter42 remove_on_counter43 moving_parent=1 cover_pass=1\n";
}
EntityId crossingBody(Simulation &s,Vector3 at={-3,.85f,0},Vector3 speed={180,0,0}) {
    const auto id=parent(s,{-50,.85f,-50});freeze(s,id);
    const auto c=s.spawnMonster(monsterId(39,22),at,id);check(c!=0,"owned direct fixture");
    auto &e=*s.findEnemy(c);e.returningBody->initialVelocity=speed;e.velocity=speed;return c;
}
void collisions() {
    for(int mode=0;mode<5;++mode) {
        auto s=fixture();const auto child=crossingBody(s);
        Projectile p;p.position=p.origin={0,.85f,-3};p.velocity={0,0,180};p.radius=.1f;p.damage=24;p.life=5;
        if(mode==1)p.pierce=2;
        if(mode==2){p.ghost=true;p.noWallCollision=true;}
        if(mode==3){p.attack.returnRange=50;p.phaseSpent=true;}
        if(mode==4)p.hostile=true;
        s.projectiles.push_back(p);tick(s);
        check(s.findEnemy(child)&&s.findEnemy(child)->alive&&s.findEnemy(child)->hp==0,"tear never damages returning body");
        check(s.projectiles.empty()==(mode==0||mode==2||mode==3),"relative swept collision blocks plain/spectral/returning, passes piercing/hostile");
        if(mode==1)check(s.projectiles.front().pierce==2,"invulnerable component does not consume finite piercing budget");
        check(s.stats.damageDealt==0,"blocked shot earns no enemy damage");
    }
    auto s=fixture();const auto child=crossingBody(s);s.godMode=false;s.player.position={0,.85f,0};tick(s);
    check(near(s.player.hp,75),"swept contact is double parent damage with existing multiplier");
    const auto owner=s.findEnemy(child)->componentOwner;damage(s,child);
    check(s.findEnemy(child)->alive&&s.findEnemy(child)->maxHp==0,"ordinary damage cannot kill attack");
    const auto money=s.moneyPickups.size();damage(s,child,true);
    check(!s.findEnemy(child)->alive&&s.findEnemy(owner)->alive&&s.findEnemy(owner)->monster==monsterId(39,2)&&s.moneyPickups.size()==money,
        "execution removes child without parent morph or money");
    auto partitioned=fixture();const auto part=crossingBody(partitioned,{-3,.85f,0},{48,0,0});
    tick(partitioned,24,1.f/120);const auto ppos=partitioned.findEnemy(part)->position;
    auto whole=fixture();const auto full=crossingBody(whole,{-3,.85f,0},{48,0,0});tick(whole,6);
    check(near(planarDistance(ppos,whole.findEnemy(full)->position),0),"trajectory independent of30Hz versus120Hz integration");
    std::cout<<"COLLISION swept_crossing=1 spectral_block=1 piercing_pass=1 spent_return_block=1 contact25=1 invulnerable=1 execution_no_loot=1 partition=1\n";
}
void lifecycle() {
    auto s=fixture();check(!s.spawnMonster(monsterId(39,22),{0,.85f,0}),"component cannot spawn without owner");
    const auto wrong=s.spawnMonster(monsterId(39),{20,.85f,0});
    check(!s.spawnMonster(monsterId(39,22),{0,.85f,0},wrong),"component rejects wrong parent type");damage(s,wrong);tick(s);
    const auto id=parent(s);ready(s,id);s.limits.enemies=1;tick(s,12);
    check(!body(s)&&s.findEnemy(id)->vis->attackFrame==18&&!s.findEnemy(id)->vis->fired,"capacity retains Shoot event");
    s.limits.enemies=2;tick(s);check(body(s)&&s.findEnemy(id)->vis->volleys==1,"capacity release creates exactly one body");
    const auto child=body(s);damage(s,id);
    check(!s.findEnemy(child)->alive,"parent death removes owned attack immediately");
    auto exit=fixture();const auto pid=parent(exit);ready(exit,pid);tick(exit);check(body(exit),"room exit starts with attack");
    exit.enterRoom(1);exit.enterRoom(0);
    check(!body(exit)&&exit.findEnemy(pid),"room reentry retains parent, never resurrects attack");
    auto clear=fixture();const auto cid=parent(clear);ready(clear,cid);tick(clear);clear.debugScenario=false;damage(clear,cid);tick(clear);
    check(clear.roomClear&&!body(clear),"last parent clears room without waiting for transient body");
    auto orphan=fixture();const auto oid=crossingBody(orphan);const auto parentId=orphan.findEnemy(oid)->componentOwner;
    std::erase_if(orphan.enemies,[&](const auto &e){return e.id==parentId;});tick(orphan);
    check(!body(orphan),"missing owner cannot leave orphan attack");
    std::cout<<"LIFECYCLE owner_validation=1 capacity_retry=1 parent_death=1 room_exit=1 room_clear=1 orphan=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-chubber-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"chubber.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture present");
        text.replace(at,from.size(),to);std::ofstream(root/"chubber.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit(".1 16 1.4 21 42",".1 12 1.4 21 42");
    check(changed->returningBody(monsterId(39,22))->launch==12&&defaultMechanics()->returningBody(monsterId(39,22))->launch==16,
        "external immutable returning-body tuning");
    for(const auto &pair:std::vector<std::pair<std::string,std::string>>{
        {".1 16 1.4 21 42",".1 16 1.4 21 20"},{".1 16 1.4 21 42",".1 0 1.4 21 42"},
        {"39.22.0 39.2.0 .1","39.22.0 39.0.0 .1"},{"Worm 0 0 1.3","Worm 1000 0 1.3"},
        {"Headless 80 1.3","Headless 0 1.3"},{"3 0 1 1 0 legacy","3 0 1 0 1 legacy"},
        {"69 18 0","69 18 1"},{"vis_returning_body 39.2.0 39.22.0","vis_returning_body 39.2.0 39.23.0"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(...){rejected=true;}
        check(rejected,"invalid owner/payload/lifetime/health rejected");
    }
    std::cout<<"CONFIG immutable=1 invalid_profiles8\n";
}
void startingKit() {
    auto s=fixture();s.godMode=false;s.player.position={0,.85f,10};const auto id=parent(s);
    check(s.player.hp==100&&s.player.shotDamage==24,"default player unchanged");
    int frames=0;
    while(!s.dead&&s.roomThreats()&&frames<600) {
        Input input;if(const auto *e=s.findEnemy(id);e&&e->alive) {
            input.fire=true;input.aim=e->position;const auto delta=horizontal(sub(e->position,s.player.position));
            input.movement=length(delta)>18?unit(delta):rotateY(unit(delta),Pi/2);
        }
        s.step(input);++frames;
    }
    check(!s.dead&&!s.roomThreats(),"starting revolver can defeat Chubber");
    std::cout<<"STARTING_KIT seconds="<<frames*Tick<<" hp="<<s.player.hp<<'\n';
}
void placement() {
    const auto content=defaultMechanics();
    for(int band=0;band<4;++band)for(auto pattern:{EncounterPattern::Pursuit,EncounterPattern::Crossfire,EncounterPattern::ChargeLane,EncounterPattern::SupplyGuard})
        for(const auto &entry:content->encounterPool(band,pattern).specialists)if(entry.monster.type==39) {
            check(entry.monster.variant<4&&entry.monster.subtype==0,"attack component never in ordinary pool");
            check(band>=(entry.monster.variant==2?1:entry.monster.variant==3?3:2),"Vis family source habitat floor bands");
            check(entry.maximum==1,"one of each specialist at most per room");
        }
    std::array<bool,4> found{};
    for(uint64_t seed=0;seed<128&&!std::all_of(found.begin(),found.end(),[](bool x){return x;});++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            if(plan.profileOnFloor(floor).band==0)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.godMode=true;
            for(int room=1;room<s.finalRoom();++room) {
                std::vector<EntityId> actors;
                for(const auto &e:s.roomEnemies(room))if(e.monster.type==39) {
                    check(e.monster.variant<4&&e.vis&&!e.returningBody&&!s.arena.blocked(e.position,e.radius),
                        "natural Vis resident has dedicated controller and legal footprint");
                    const size_t variant=size_t(e.monster.variant);
                    if(!found[variant])std::cout<<"NATURAL_VIS variant="<<variant<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<'\n';
                    found[variant]=true;actors.push_back(e.id);
                }
                if(!actors.empty()) {
                    s.enterRoom(room);s.player.position=s.arena.rooms[size_t(room)].entry;tick(s,4);
                    for(auto id:actors)check(s.findEnemy(id)&&s.findEnemy(id)->vis->ticks>0,"natural resident activates dedicated controller");
                }
            }
        }
    }
    check(std::all_of(found.begin(),found.end(),[](bool x){return x;}),"all four Vis bodies reachable on seeded floors");
}
}
int main(){std::cout<<std::unitbuf;try{launchAndReturn();collisions();lifecycle();configuration();startingKit();placement();std::cout<<"PASS Chubber contracts\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
