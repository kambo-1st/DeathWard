#include "combat/Simulation.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float tolerance=.01f){return std::abs(a-b)<tolerance;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,20,50}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-50,-.4f,-50},{50,0,50}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.roomClear=false;
    s.player.position={8,.85f,12};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId mirror(Simulation &s,int variant=0){return s.spawnMonster(monsterId(53,variant),{-15,.85f,-15});}
void movement() {
    for(int variant=0;variant<2;++variant) {
        auto s=fixture();s.arena.rooms[0].center={3,.85f,4};const auto id=mirror(s,variant);
        tick(s,2);auto &e=*s.findEnemy(id);
        check(near(e.position.x,-2)&&near(e.position.z,-4),"absolute reflection uses this room's center");
        check(near(e.maxHp,64)&&near(s.content->monsterHealth(e.monster,12),64),"both variants have source20HP with local3.2conversion");
        Input move;move.movement={1,0,0};s.step(move,1.f/30);
        check(near(e.position.x,6-s.player.position.x)&&e.velocity.x<0,"movement follows reflected position, not arbitrary spawn offset");
        s.player.position={3,.85f,4};s.player.hurt=0;tick(s,20);
        check(near(e.position.x,3)&&near(e.position.z,4)&&near(s.player.hp,100),"center overlap has no contact damage or body displacement");
        check(s.projectiles.empty(),"movement alone never creates attacks");
        s.player.position={80,.85f,12};tick(s);
        check(e.position.x>=-50+e.radius,"open exits do not permit mirroring outside active room");
    }
    auto duplicate=fixture();const auto a=mirror(duplicate),b=mirror(duplicate,1);tick(duplicate,3);
    check(duplicate.findEnemy(a)&&!duplicate.findEnemy(b)&&duplicate.livingEnemies()==1,"one mirror target across both variants");
    check(duplicate.stats.kills==0&&duplicate.moneyPickups.empty(),"duplicate removal gives no kill or loot");
    std::cout<<"MOVEMENT center_reflection=1 room_bounds=1 equal_hp=1 zero_contact=1 one_target=1\n";
}
void shots() {
    for(int variant=0;variant<2;++variant) {
        auto s=fixture();const auto id=mirror(s,variant);tick(s,2);auto &e=*s.findEnemy(id);
        Input fire;fire.fire=true;fire.aim=add(s.player.position,{0,0,20});s.step(fire,1.f/30);
        check(e.mirror->volleys==1&&s.stats.projectiles==unsigned(variant?4:2),"source delay rise emits one or three shots");
        int hostile=0;for(const auto &shot:s.projectiles)if(shot.hostile) {
            ++hostile;check(shot.velocity.z<0&&near(shot.radius,.308f)&&near(shot.damage,10),"opposite shots preserve1.4scale and base damage before player hurt multiplier");
            check(near(shot.gravity,4.455f)&&shot.velocity.y>0,"source falling modifiers use converted ballistic motion");
        }
        check(hostile==(variant?3:1),"no invented additional projectiles");
        const int count=variant?3:1;
        if(variant) {
            std::vector<Projectile> h;for(const auto &q:s.projectiles)if(q.hostile)h.push_back(q);
            check(near(h[0].velocity.z,-36)&&near(h[1].velocity.z,-36*.961f*.9f)&&
                near(std::abs(h[1].velocity.x),36*.276f*.9f),"mode2 uses unnormalized side vectors and speed1.2");
        }
        const auto before=s.stats.projectiles;tick(s,5);check(s.stats.projectiles==before,"countdown and idle do not repeat attack");
        s.player.fireCooldown=0;s.step(fire,1.f/30);
        check(e.mirror->volleys==unsigned(variant?1:2),"only Evil Twin throttles an early second trigger");
        tick(s,30);s.player.fireCooldown=0;s.step(fire,1.f/30);
        check(e.mirror->volleys==unsigned(variant?2:3),"cooldown expiry permits the next actual trigger");
        s.projectiles.clear();s.limits.projectiles=size_t(count);s.player.fireCooldown=0;tick(s,31);s.step(fire,1.f/30);
        check(e.mirror->pending,"full projectile pool retains entire mirror volley");
        s.projectiles.clear();s.limits.projectiles=128;const auto volleys=e.mirror->volleys;tick(s);
        check(!e.mirror->pending&&e.mirror->volleys==volleys+1,"capacity release emits retained volley once");
        e.state=EnemyState::Stunned;e.stateTime=1;s.player.fireCooldown=0;s.step(fire,1.f/30);
        check(e.mirror->volleys==volleys+1,"stun suppresses attacks");
    }
    auto fast=fixture();const auto id=mirror(fast);tick(fast,2);
    for(int i=0;i<5;++i){fast.player.fireCooldown=1;tick(fast);}
    check(fast.findEnemy(id)->mirror->volleys==1,"constant sampled integer delay does not invent rapid-fire triggers");
    std::cout<<"SHOTS trigger_delay=1 cardinal=1 twin_cooldown=1 spread=1 ballistics=1 capacity=1 stun=1 aliasing=1\n";
}
void terrain() {
    for(int variant=0;variant<2;++variant) {
        auto s=fixture();s.player.position={8,.85f,12};
        s.arena.obstacles.push_back({{-10,0,-14},{-6,2,-10}});s.arena.rebuildWalls();
        const auto id=mirror(s,variant);tick(s,3);const auto &e=*s.findEnemy(id);
        if(variant)check(near(e.position.x,-8)&&near(e.position.z,-12)&&e.position.y>2,"Evil Twin crosses and rises above low cover");
        else check(!s.arena.blocked(e.position,e.radius)&&e.mirror->terrainCorrections>0,"Dople projects blocked reflection to a legal ground footprint");
        s.arena.walls.push_back({{-50,-1,-50},{50,20,50}});tick(s);
        check(std::isfinite(s.findEnemy(id)->position.x),"fully obstructed search is bounded");
    }
    std::cout<<"TERRAIN ground_correction=1 flying_cover=1 bounded_search=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-mirrors-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path path;~Cleanup(){std::filesystem::remove_all(path);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"mirrors.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"mirrors.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("53.1.0 30 3 30","53.1.0 15 3 30");
    check(changed->mirror(monsterId(53,1))->cooldownFrames==15&&defaultMechanics()->mirror(monsterId(53,1))->cooldownFrames==30,"external tuning loads without mutating prior snapshot");
    for(auto replacement:std::array<std::pair<std::string,std::string>,4>{{{"53.1.0 30 3 30","53.1.0 30 2 30"},{"53.1.0 30 3 30","53.1.0 -1 3 30"},{"53.1.0 30 3 30","53.1.0 30 3 -30"},{"53.1.0 30 3 30","9999.0.0 30 3 30"}}}) {
        bool rejected=false;try{edit(replacement.first,replacement.second);}catch(const std::exception &){rejected=true;}check(rejected,"invalid mirror profile rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=4\n";
}
void placement() {
    bool found[2]{};int floors=0,rooms=0;
    for(uint64_t seed=0;seed<32&&(!found[0]||!found[1]);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++floors;
            for(int room=1;room<s.finalRoom();++room) {
                ++rooms;const auto encounter=s.floorEncounter(room);
                check(std::count_if(encounter.monsters.begin(),encounter.monsters.end(),[&](auto id){return s.content->mirror(id)!=nullptr;})<=1,"seeded composition reserves only one mirror across variants");
                for(const auto &e:s.roomEnemies(room))if(e.mirror) {
                    check(s.arena.profile.band==3,"mirrors appear only in their late habitat band");
                    check(!s.arena.blocked(e.position,e.radius),"natural initial footprint is valid");
                    if(!found[e.monster.variant])std::cout<<"NATURAL_MIRROR id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
                    found[e.monster.variant]=true;
                }
            }
        }
    }
    check(found[0]&&found[1],"both variants have actual seeded resident witnesses");
    std::cout<<"PLACEMENT floors="<<floors<<" rooms="<<rooms<<" late_band=1 shared_cap=1\n";
}
}
int main(){std::cout<<std::unitbuf;try{movement();shots();terrain();configuration();placement();std::cout<<"mirror behavior passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
