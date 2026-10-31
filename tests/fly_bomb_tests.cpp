#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> rules=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(rules));
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{200,12,25}};
    for(size_t i=0;i<s.arena.rooms.size();++i) {
        auto &r=s.arena.rooms[i];const float x=float(i)*60;
        r.bounds={{x-25,-1,-25},{x+25,12,25}};r.center={x,.85f,0};r.kind=RoomKind::Combat;
    }
    for(auto &r:s.rooms){r.residents.clear();r.cleared=false;r.segmented.clear();r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.suppliedBombs.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={20,.85f,20};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.bossKilled=false;return s;
}
void tick(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float amount,bool execution=false,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=execution;e.debugExecution=debug;
    e.position=s.findEnemy(id)->position;s.queueRoot(e);s.drainEvents();
}
void contactAndDeath() {
    auto contact=fixture();contact.godMode=false;contact.player.position={0,.85f,0};
    const auto fly=contact.spawnMonster(monsterId(819),{0,.85f,0});
    const auto target=contact.spawnMonster(monsterId(25),{2,.85f,0});contact.findEnemy(target)->hp=500;
    contact.step({});
    check(!contact.findEnemy(fly)&&contact.stats.explosions==1&&contact.enemyBombs.empty(),"Contact detonates once immediately without a delayed duplicate");
    check(contact.player.hp==87.5f&&contact.findEnemy(target)->hp==460,"Contact blast has base half-heart ratio and 40 enemy damage");
    tick(contact,10);check(contact.stats.explosions==1,"Later ticks cannot repeat contact explosion");

    auto death=fixture();death.godMode=false;death.player.position={2.5f,.85f,0};
    const auto killed=death.spawnMonster(monsterId(819),{0,.85f,0});
    hit(death,killed,24);
    check(death.enemyBombs.size()==1&&death.stats.explosions==0&&death.stats.kills==1,"Ordinary shot death creates one delayed bomb");
    const auto &bomb=death.enemyBombs[0];
    check(bomb.ordnance==monsterId(4,14)&&bomb.source==killed&&bomb.sourceMonster==monsterId(819),"Ordnance retains source and component identities");
    death.debugScenario=false;tick(death,1);
    check(death.roomClear&&death.enemyBombs.size()==1,"Last enemy death opens room without deleting the bomb");
    tick(death,58);check(death.stats.explosions==0&&death.player.hp==100,"Death fuse affords the configured delay");
    tick(death,3);check(death.stats.explosions==1&&death.player.hp==75&&death.enemyBombs.empty(),"Delayed blast survives clear and deals full-heart ratio once");
    auto collateral=fixture();const auto doomed=collateral.spawnMonster(monsterId(819),{0,.85f,0});
    const auto victim=collateral.spawnMonster(monsterId(14),{1,.85f,0});collateral.findEnemy(victim)->hp=500;
    hit(collateral,doomed,24);tick(collateral,62);
    check(collateral.findEnemy(victim)->hp==400,"Delayed ordnance uses 100 enemy damage instead of generic 80");
    auto debug=fixture();const auto clean=debug.spawnMonster(monsterId(819),{0,.85f,0});hit(debug,clean,1000,true,true);
    check(debug.enemyBombs.empty()&&debug.stats.explosions==0,"Explicit debugging execution suppresses death ordnance");
    auto limited=fixture();limited.player.position={0,.85f,0};const auto waiting=limited.spawnMonster(monsterId(819),{0,.85f,0});
    limited.limits.queuedEvents=0;limited.step({});
    check(limited.findEnemy(waiting)&&limited.findEnemy(waiting)->selfDetonated,"Suppressed contact event retains pending actor death");
    limited.limits.queuedEvents=16384;limited.step({});
    check(!limited.findEnemy(waiting)&&limited.stats.explosions==1,"Pending contact retries after event capacity recovers");
    std::cout<<"FLY_BOMB_DAMAGE contact_40=1 death_100=1 player_12_5_25=1 delayed_after_clear=1 exactly_once=1\n";
}
void movementAndCover() {
    auto s=fixture();s.player.position={0,.85f,10};const auto id=s.spawnMonster(monsterId(819),{0,.85f,-8});
    s.findEnemy(id)->facing={0,0,1};float curve=0;bool detonated=false;
    for(int n=0;n<600;++n) {
        s.step({});const auto *e=s.findEnemy(id);
        if(!e){detonated=true;break;}
        curve=std::max(curve,std::abs(e->position.x));
        check(!s.arena.flightBlocked(e->position,e->radius,s.room),"Pursuit remains inside actual flight bounds");
    }
    check(curve>.25f&&detonated&&s.stats.explosions==1,"Normal fly curves toward player and eventually makes contact");
    auto cover=fixture();cover.player.position={0,.85f,10};
    cover.arena.obstacles={{{-2,0,-1},{2,2,2}}};cover.arena.rebuildWalls();
    const auto high=cover.spawnMonster(monsterId(819),{0,.85f,-8});cover.findEnemy(high)->facing={0,0,1};float peak=0;
    for(int n=0;n<600&&cover.findEnemy(high);++n) {
        cover.step({});if(const auto *e=cover.findEnemy(high)) {
            peak=std::max(peak,e->position.y);
            check(!sphereBox(e->position,e->radius,cover.arena.obstacles[0]),"Flying bomb sphere remains above cover");
        }
    }
    check(peak>2.8f&&cover.stats.explosions==1,"Flying contact controller crosses interior cover and reaches player");
    auto sweep=fixture();sweep.player.position={-1.15f,.85f,0};
    sweep.spawnMonster(monsterId(819),{0,.85f,0});Input fast;fast.movement={1,0,0};fast.dodge=true;
    sweep.step(fast,.15f);
    check(sweep.stats.explosions==1,"Relative swept motion catches a dodge crossing the body");
    std::cout<<"FLY_BOMB_MOVEMENT curved_pursuit=1 reaches_player=1 flies_over_cover=1 swept_dodge=1\n";
}
void ownedGroup() {
    auto s=fixture();check(!s.spawnMonster(monsterId(819,1),{0,.85f,0}),"Eternal cannot spawn independently");
    const auto owner=s.spawnBombFlyHost(monsterId(819,1),{0,.85f,0});
    check(owner&&s.enemies.size()==4&&s.roomThreats()==1&&s.findEnemy(owner)->bossParts==7,"Real Boom Fly owns exactly three non-gating orbiters");
    const auto child=s.enemies[1].id;
    hit(s,child,10000);hit(s,child,10000,true);
    check(s.findEnemy(child)->hp==22.4f&&s.enemyBombs.empty(),"Live owned fly rejects bullets and generic execution");
    tick(s,90);
    for(const auto &e:s.enemies)if(e.componentOwner==owner)
        check(std::abs(planarDistance(e.position,s.findEnemy(owner)->position)-2)<.02f,"Owned trio maintains orbit around moving host");
    hit(s,owner,1000,true); // ordinary execution still triggers the attached bombs.
    check(s.enemyBombs.size()==3&&s.stats.kills==1&&std::none_of(s.enemies.begin(),s.enemies.end(),[](auto &e){return e.alive;}),
          "Owner death replaces each surviving orbiter with one bomb, without independent loot or kill counts");
    tick(s,62);check(s.stats.explosions==4,"The owner blast and all three actual delayed bombs detonate");
    auto chain=fixture();const auto chainOwner=chain.spawnBombFlyHost(monsterId(819,1),{0,.85f,0});
    const auto childPos=chain.enemies[1].position;chain.findEnemy(chainOwner)->hp=1;chain.player.position=childPos;
    chain.step({});
    check(chain.stats.explosions==2&&chain.enemyBombs.size()==2,"Orbiter contact immediately blasts owner and creates only the two surviving delayed bombs");
    tick(chain,62);check(chain.stats.explosions==4,"One contact, two surviving orbiters and the Boom Fly's own explosion occur exactly once");
    auto cap=fixture();cap.limits.enemies=3;
    check(!cap.spawnBombFlyHost(monsterId(819,1),{0,.85f,0})&&cap.enemies.empty(),"Capacity rejects the entire mandatory group atomically");
    auto wall=fixture();check(!wall.spawnBombFlyHost(monsterId(819,1),{24,.85f,0})&&wall.enemies.empty(),"Boundary rejection leaves no incomplete owner group");
    std::cout<<"FLY_BOMB_OWNERSHIP trio=1 invulnerable=1 real_orbit=1 owner_death=1 contact_chain=1 atomic_group=1\n";
}
void persistenceAndDemolition() {
    auto s=fixture();s.limits.enemyBombs=1;const auto a=s.spawnMonster(monsterId(819),{0,.85f,0}),b=s.spawnMonster(monsterId(819),{7,.85f,0});
    hit(s,a,24);hit(s,b,24);
    check(s.enemyBombs.size()==1&&s.pendingEnemyBombs.size()==1,"Bounded ordnance pool retains pending death work");
    tick(s,10);const auto age=s.enemyBombs[0].charge.age;
    s.enterRoom(1);s.player.position={60,.85f,0};tick(s,120);
    check(s.enemyBombs[0].charge.age==age&&s.pendingEnemyBombs.size()==1,"Real room departure pauses armed and pending bombs");
    s.enterRoom(0);s.player.position={20,.85f,20};tick(s,120);
    check(s.stats.explosions==2&&s.enemyBombs.empty()&&s.pendingEnemyBombs.empty(),"Returning resumes and drains pending ordnance after capacity frees");
    auto armor=fixture();const auto head=armor.spawnMonster(monsterId(19,2),{0,.85f,0});
    check(head!=0,"Tuff damage fixture exists");const auto at=armor.findEnemy(head)->position;
    const auto bomb=armor.spawnMonster(monsterId(819),add(at,{0,0,-.8f}));hit(armor,bomb,24);
    // Exercise the actual ordnance fuse beside the moving multipart boss.
    tick(armor,62);
    bool stripped=false;for(const auto &e:armor.enemies)if(e.segmentedEncounter&&e.segmentArmor==0)stripped=true;
    check(stripped,"Death ordnance is a real explosion that can remove Tuff armor");
    auto rock=fixture();Breakable prop;prop.id=1;prop.room=0;prop.kind=BreakableKind::CrackedRock;
    prop.bounds={{1,0,-.5f},{1.5f,1.5f,.5f}};prop.health=1;rock.arena.breakables.push_back(prop);rock.arena.rebuildWalls();
    const auto demolished=rock.spawnMonster(monsterId(819),{0,.85f,0});hit(rock,demolished,24);tick(rock,62);
    check(rock.arena.breakables[0].destroyed&&rock.arena.breakables[0].paid&&rock.dynamite==StartingDynamite,
        "Real enemy bomb demolishes authored rock without spending player inventory");
    auto reset=fixture();const auto last=reset.spawnMonster(monsterId(819),{0,.85f,0});hit(reset,last,24);reset.clearRoomDebug();
    check(reset.enemyBombs.empty()&&reset.pendingEnemyBombs.empty(),"Explicit debug clear removes remaining ordnance");
    std::cout<<"FLY_BOMB_LIFECYCLE inactive_pause=1 pending_retry=1 actual_tuff_armor=1 rock_demolition=1 debug_clear=1\n";
}
void externalAndStage() {
    const auto root=std::filesystem::temp_directory_path()/("deathward-fly-bombs-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup {std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}} cleanup{root};
    std::filesystem::create_directories(root);
    for(const auto &file:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(file.path().extension()==".mechanics")
        std::filesystem::copy_file(file.path(),root/file.path().filename());
    const auto path=root/"fly_bombs.mechanics";std::ifstream input(path);std::string data((std::istreambuf_iterator<char>(input)),{});
    const std::string from="6 .7 4 1 3 40 10 100 20",to="6 .7 4 2 3 40 10 200 20";
    const auto at=data.find(from);check(at!=std::string::npos,"Editable fuse and death damage exist");data.replace(at,from.size(),to);{std::ofstream out(path);out<<data;}
    auto changed=MechanicsLibrary::load(root);auto a=fixture(),b=fixture(changed);
    hit(a,a.spawnMonster(monsterId(819),{0,.85f,0}),24);hit(b,b.spawnMonster(monsterId(819),{0,.85f,0}),24);
    tick(a,62);tick(b,62);
    check(a.stats.explosions==1&&b.stats.explosions==0&&b.enemyBombs[0].charge.blastDamage==200,"External fuse/damage affect new snapshot without changing old run");
    data+="\nfly_bomb_orbit 819.1.0 25.0.0 3 2 1.8\n";{std::ofstream out(path);out<<data;}
    bool rejected=false;try{MechanicsLibrary::load(root);}catch(const std::exception&){rejected=true;}
    check(rejected,"Duplicate owner rules fail validation");
    int reached=0;
    for(uint64_t seed=0;seed<128&&reached<3;++seed) {
        ExpeditionPlan plan(seed);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
        Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);
        for(int room=0;room<run.arena.roomCount()&&reached<3;++room) {
            const auto &residents=run.roomEnemies(room);
            const auto it=std::find_if(residents.begin(),residents.end(),[](const auto &e){return e.monster==monsterId(819);});
            if(it==residents.end())continue;
            check(run.arena.profile.band==1&&run.arena.profile.variant==FloorVariant::Standard,"Natural Fly Bomb route is standard Broken Quarry only");
            const auto entity=it->id;run.jumpDebug(room);run.godMode=true;tick(run,120);
            check(run.findEnemy(entity)||run.stats.explosions>0,"Actual resident activates and moves or detonates");
            std::cout<<"FLY_BOMB_STAGE seed="<<seed<<" floor="<<floor<<" room="<<room<<" variant=standard\n";++reached;
        }
    }
    check(reached==3,"Three natural Fly Bomb encounters found");
    std::cout<<"FLY_BOMB_EXTERNAL immutable_snapshot=1 fuse_damage=1 duplicate_rejected=1 actual_seeded_route=1 eternal_producer_pending=1\n";
}
}
int main(){try{contactAndDeath();movementAndCover();ownedGroup();persistenceAndDemolition();externalAndStage();
 std::cout<<"PASS Fly Bomb pursuit, explosions, ordnance, ownership, external configuration and stage routing\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
