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
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,20,100}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={-90,.85f,-90};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(21),{0,.85f,0});}
void movement() {
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);
    check(e.cardinalWalker&&!e.spitty&&near(e.hp,48),"Maggot has dedicated contact walker and source health");
    e.cardinalWalker->hasDestination=true;e.cardinalWalker->destination={60,.85f,0};
    tick(s);check(near(e.velocity.x,0),"source steering waits a complete30Hz tick");
    tick(s);check(near(e.velocity.x,.75f*.85f*3)&&near(e.velocity.z,0),"first source force/friction endpoint and world conversion");
    tick(s,2);check(near(e.velocity.x,(.75f*.85f+.75f)*.85f*3),"second native momentum recurrence");
    check(e.facing.x==1&&e.facing.z==0,"facing follows previous cardinal momentum");
    auto left=fixture(),right=fixture();const auto a=spawn(left),b=spawn(right);right.player.position={90,.85f,90};
    for(int n=0;n<480;++n){tick(left);tick(right);check(distance(left.findEnemy(a)->position,right.findEnemy(b)->position)<.001f,"ordinary wandering does not pursue the player");}
    check(left.projectiles.empty()&&left.hazards.empty()&&left.stats.projectiles==0,"no ranged attack is inherited from Spitty");
    check(planarDistance(left.findEnemy(a)->position,{0,0,0})>1,"cardinal wandering progresses");
    auto small=fixture();const auto sid=small.spawnMonster(monsterId(853),{0,.85f,0});
    check(!small.findEnemy(sid)->cardinalWalker,"Small Maggot remains a separate behavior");
    std::cout<<"MOVEMENT source_force=.75 retention=.85 independent_target=1 seeded=1 no_projectiles=1\n";
}
void geometryAndLifecycle() {
    auto cover=fixture();cover.arena.obstacles.push_back({{2,0,-10},{3,5,10}});cover.arena.rebuildWalls();const auto id=spawn(cover);
    auto &e=*cover.findEnemy(id);e.velocity={12,0,0};e.cardinalWalker->hasDestination=true;e.cardinalWalker->destination={8,.85f,0};
    float travelled=0;auto previous=e.position;
    for(int n=0;n<480;++n){tick(cover);check(!sphereBox(e.position,e.radius,cover.arena.obstacles[0]),"source intent cannot tunnel through physical cover");travelled+=distance(previous,e.position);previous=e.position;}
    check(travelled>5,"blocked walker selects another path instead of remaining stuck");
    auto stun=fixture();const auto sid=spawn(stun);tick(stun,90);const auto at=stun.findEnemy(sid)->position;
    stun.findEnemy(sid)->state=EnemyState::Stunned;stun.findEnemy(sid)->stateTime=.5f;tick(stun,20);
    check(distance(at,stun.findEnemy(sid)->position)<.001f,"stunned walker remains still");tick(stun,40);check(distance(at,stun.findEnemy(sid)->position)>.1f,"walker resumes after stun");
    auto room=fixture();const auto rid=spawn(room);tick(room,90);const auto before=*room.findEnemy(rid)->cardinalWalker;
    room.enterRoom(1);tick(room,60);room.enterRoom(0);
    check(room.findEnemy(rid)->cardinalWalker->ticks==before.ticks&&distance(room.findEnemy(rid)->cardinalWalker->destination,before.destination)<.001f,"inactive room preserves destination and source clock");
    tick(room,2);check(room.findEnemy(rid)->cardinalWalker->ticks>before.ticks,"re-entered resident resumes");
    auto death=fixture();death.debugScenario=false;const auto dead=spawn(death);
    Event hit;hit.type=EventType::Damage;hit.target=dead;hit.damage=10000;death.queueRoot(hit);death.drainEvents();tick(death,30);
    check(death.roomClear&&death.stats.kills==1&&death.enemies.empty()&&death.projectiles.empty(),"normal death clears once with no offspring or death attack");
    std::cout<<"LIFECYCLE cover=1 recovery=1 stun=1 room_suspend=1 death_clear=1\n";
}
void contactAndStartingKit() {
    auto s=fixture();s.godMode=false;spawn(s);s.player.position={0,.85f,0};tick(s);
    check(near(s.player.hp,StartingHealth-10*EnemyDamageMultiplier),"source contact converts through shared hostile damage multiplier");
    const float hp=s.player.hp;tick(s,5);check(near(s.player.hp,hp),"player invulnerability prevents contact damage every frame");
    auto duel=fixture();duel.godMode=false;duel.player.position={0,.85f,8};const auto id=spawn(duel);int frames=0;
    while(duel.roomThreats()&&!duel.dead&&frames<1800) {
        Input input;input.fire=true;
        if(const auto *e=duel.findEnemy(id)) {
            const auto delta=horizontal(sub(e->position,duel.player.position));const float range=length(delta);
            input.aim=add(e->position,mul(e->velocity,std::min(.5f,range/26)));
            input.movement=range>12?unit(delta):range<6?mul(unit(delta),-1):rotateY(unit(delta),Pi/2);
        }
        duel.step(input);++frames;
    }
    check(!duel.dead&&duel.roomThreats()==0,"default player kit defeats moving Maggot");
    std::cout<<"STARTING_KIT seconds="<<frames*Tick<<" health="<<duel.player.hp<<" contact="<<10*EnemyDamageMultiplier<<'\n';
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-maggot-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"maggots.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"maggots.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit(".1 .75 .85",".1 .5 .85");check(near(changed->cardinalWalker(monsterId(21))->force,.5f)&&near(defaultMechanics()->cardinalWalker(monsterId(21))->force,.75f),"external tuning uses immutable libraries");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".1 .75 .85",".1 -1 .85"},{".1 .75 .85",".1 .75 1"},{"10 12 24","10 0 24"},{"40 5 .6","40 50 .6"},{"Wander None Worm","Chase None Worm"},{"Wander None Worm","Wander Shot Worm"}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or incompatible profile rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=6\n";
}
void placement() {
    std::array<bool,4> seen{};bool river=false;
    for(uint64_t seed=0;seed<64&&(!seen[1]||!seen[3]||!river);++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.godMode=true;
            const int band=s.arena.profile.band;
            for(int room=1;room<s.finalRoom();++room) {
                std::vector<EntityId> ids;
                for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(21)) {
                    check(band==1||band==3,"source habitats exclude opening and Depths-equivalent ordinary floors");
                    check(e.cardinalWalker&&!s.arena.blocked(e.position,e.radius),"real resident has dedicated controller and legal initial footprint");
                    if(!seen[size_t(band)])std::cout<<"NATURAL_MAGGOT seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<band<<'\n';
                    seen[size_t(band)]=true;ids.push_back(e.id);
                }
                if(ids.empty())continue;
                s.enterRoom(room);s.player.position=s.arena.rooms[size_t(room)].entry;
                const bool wet=s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&
                    std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &point){
                        return s.arena.roomAt({point.position.x,.85f,point.position.z})==room;
                    });
                for(int frame=0;frame<(wet?240:4);++frame) {
                    tick(s);
                    for(auto id:ids)if(const auto *e=s.findEnemy(id);e&&e->alive) {
                        check(e->cardinalWalker->ticks>0||frame==0,"resident really activates controller");
                        check(!s.arena.blocked(e->position,e->radius),"generated walker remains outside solid terrain and water");
                    }
                }
                if(wet){river=true;std::cout<<"RIVER_MAGGOT seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';}
            }
        }
    }
    check(seen[1]&&seen[3]&&river,"both source-equivalent bands and actual river room exercised");
}
}
int main(){try{movement();geometryAndLifecycle();contactAndStartingKit();configuration();placement();std::cout<<"PASS cardinal walkers\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
