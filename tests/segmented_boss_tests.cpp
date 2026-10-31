#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *message){if(!value)throw std::runtime_error(message);}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> rules=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(rules));
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,12,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;}
    for(auto &r:s.rooms){r.residents.clear();r.cleared=false;r.segmented.clear();r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.suppliedBombs.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={20,.85f,20};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.bossKilled=false;return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s){auto id=s.spawnMonster(monsterId(19,2),{0,.85f,0});check(id!=0,"Complete Tuff encounter spawns");return id;}
void hit(Simulation &s,EntityId id,float amount,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=e.debugExecution=debug;
    e.position=s.findEnemy(id)->position;s.queueRoot(e);s.drainEvents();
}
void blast(Simulation &s,Vector3 at,float damage,float radius=1) {
    Event e;e.type=EventType::Explosion;e.position=e.origin=at;e.damage=damage;e.radius=radius;
    e.demolition=Demolition::SuppliedBomb;s.queueRoot(e);s.drainEvents();
}
void compositionAndMovement() {
    auto a=fixture(),b=fixture();const auto first=spawn(a);spawn(b);b.player.position={-20,.85f,-20};
    check(a.enemies.size()==14&&a.roomThreats()==12&&a.rooms[0].segmented.size()==1,"Two six-part worms and two non-gating suppliers");
    check(a.rooms[0].segmented[0].chains.size()==2&&std::count_if(a.enemies.begin(),a.enemies.end(),[](auto &e){return e.segmentHead;})==2,"Each independent chain starts with one head");
    for(auto &e:a.enemies)if(e.segmentedEncounter)check(e.hp==112&&e.segmentArmor==15,"Body HP and armor are separate source-based values");
    ticks(a,60);ticks(b,60);
    for(size_t i=0;i<12;++i)check(planarDistance(a.enemies[i].position,b.enemies[i].position)<.001f,"Worm roaming does not steer toward player");
    check(a.findEnemy(first)->position.x>5&&a.suppliedBombs.size()==2,"Head moves cardinally and suppliers really produce stock");
    for(auto &chain:a.rooms[0].segmented[0].chains)for(size_t i=1;i<chain.members.size();++i)
        check(std::abs(planarDistance(a.findEnemy(chain.members[i-1])->position,a.findEnemy(chain.members[i])->position)-1.55f)<.12f,"Segments follow actual head trail at authored spacing");
    ticks(a,1500);for(auto &e:a.enemies)if(e.segmentedEncounter)check(!a.arena.blocked(e.position,e.radius),"Long roaming remains outside real walls/supplier solids");
    check(a.bossHealthFraction(*a.boss())==1,"Aggregate bar starts full");
    auto cap=fixture();cap.limits.enemies=13;check(!cap.spawnMonster(monsterId(19,2),{0,.85f,0})&&cap.enemies.empty()&&cap.rooms[0].segmented.empty(),"Insufficient capacity leaves no partial mandatory encounter");
    auto blocked=fixture();blocked.arena.obstacles={{{-24,0,-24},{24,4,24}}};blocked.arena.rebuildWalls();
    check(!blocked.spawnMonster(monsterId(19,2),{0,.85f,0})&&blocked.enemies.empty(),"Blocked arena rejects complete encounter atomically");
    std::cout<<"TUFF_MOVEMENT paired_six=1 suppliers=2 cardinal_roaming=1 path_following=1 bounded_trail=1 atomic_spawn=1\n";
}
void armorAndDamage() {
    auto s=fixture();const auto id=spawn(s);auto *e=s.findEnemy(id);const auto position=e->position;
    hit(s,id,9999);check(e->hp==112&&e->segmentArmor==15,"Ordinary bullets cannot remove armor");
    Event fake;fake.type=EventType::Damage;fake.target=id;fake.damage=9999;fake.areaDamage=true;fake.armorPiercing=true;fake.execution=true;s.queueRoot(fake);s.drainEvents();
    check(e->hp==112&&e->segmentArmor==15,"Generic area/piercing/instant-death flags cannot impersonate explosives");
    blast(s,position,100);check(e->hp==112&&e->segmentArmor==0,"Real near explosion removes separate armor without invented spillover");
    hit(s,id,24);check(e->hp==88,"Exposed segment accepts player bullet damage");
    blast(s,position,100);check(std::abs(e->hp-63)<.001f,"Exposed segment retains 25 percent near explosive damage");
    auto far=fixture();const auto f=spawn(far);auto *other=far.findEnemy(f);const auto at=add(other->position,{0,0,-4});
    blast(far,at,100,4);check(std::abs(other->segmentArmor-1)<.001f&&other->hp==112,"Far explosion applies configured 14 percent endpoint");
    blast(far,at,100,4);check(other->segmentArmor==0&&other->hp==112,"Second distant blast breaks remaining armor");
    blast(far,at,100,4);check(std::abs(other->hp-98)<.001f,"Exposed far segment keeps resistance");
    std::cout<<"TUFF_ARMOR separate_hp=1 bullets_blocked=1 real_explosion=1 near_25=1 far_14=1 no_spillover_policy=1\n";
}
void topologyAndCompletion() {
    auto s=fixture();const auto first=spawn(s);const auto original=s.rooms[0].segmented[0].chains[0].members;
    hit(s,first,10000,true);check(!s.bossKilled&&!s.rooms[0].bossPaid&&s.roomThreats()==11,"Head death neither finishes fight nor pays reward");
    check(s.findEnemy(original[1])->segmentHead&&std::abs(s.bossHealthFraction(*s.boss())-11.f/12)<.001f,"Next live part becomes head and bar retains aggregate denominator");
    auto split=fixture();spawn(split);const auto members=split.rooms[0].segmented[0].chains[0].members;
    hit(split,members[2],10000,true);
    check(split.rooms[0].segmented[0].chains.size()==3&&split.findEnemy(members[3])->segmentHead,"Three-piece rear fragment becomes independent head/chain");
    auto shortTail=fixture();spawn(shortTail);const auto shortMembers=shortTail.rooms[0].segmented[0].chains[0].members;
    hit(shortTail,shortMembers[4],10000,true);
    check(shortTail.rooms[0].segmented[0].chains.size()==2&&shortTail.findEnemy(shortMembers[5])->alive&&shortTail.findEnemy(shortMembers[5])->segmentArmor==15,
          "Declared short-tail reattachment policy preserves HP and armor");
    for(auto id:s.rooms[0].segmented[0].allMembers)if(auto *part=s.findEnemy(id);part&&part->alive)hit(s,id,10000,true);
    check(s.bossKilled&&s.rooms[0].bossPaid&&s.moneyPickups.size()==1,"All segments dead pays one aggregate reward");
    const auto money=s.moneyPickups.size();ticks(s,5);s.enterRoom(1);s.enterRoom(0);ticks(s,5);
    check(s.moneyPickups.size()==money&&s.rooms[0].segmented[0].completed,"Repeated steps/re-entry never pay twice");
    auto pause=fixture();spawn(pause);ticks(pause,40);const auto part=pause.rooms[0].segmented[0].chains[0].members[1];const auto pos=pause.findEnemy(part)->position;
    pause.enterRoom(1);ticks(pause,180);pause.enterRoom(0);
    check(planarDistance(pause.findEnemy(part)->position,pos)<.001f&&pause.rooms[0].segmented[0].chains.size()==2,"Real chains pause and survive room departure");
    std::cout<<"TUFF_TOPOLOGY head_promotion=1 rear_split=1 short_fragment_policy=1 aggregate_reward_once=1 inactive_persistence=1\n";
}
void childrenAndDeathCrosses() {
    auto s=fixture();const auto head=spawn(s);s.findEnemy(head)->cooldown=0;s.step({});
    check(std::any_of(s.enemies.begin(),s.enemies.end(),[](auto &e){return e.monster==monsterId(61,3)&&e.summoner!=0&&e.hp==32;}),"Armored head produces actual Ink children");
    s.findEnemy(head)->segmentArmor=0;s.findEnemy(head)->cooldown=0;s.step({});
    check(std::any_of(s.enemies.begin(),s.enemies.end(),[](auto &e){return e.monster==monsterId(61)&&e.summoner!=0&&e.hp==32;}),"Exposed head switches to actual Suckers");
    const auto body=s.rooms[0].segmented[0].chains[0].members[1];s.findEnemy(body)->segmentArmor=0;s.findEnemy(body)->auxiliary=0;
    const auto shots=s.stats.projectiles;s.step({});check(s.stats.projectiles==shots+7,"Exposed body emits configured bloody spray");
    for(auto id:{monsterId(61),monsterId(61,3)}) {
        auto death=fixture();const auto child=death.spawnMonster(id,{0,.85f,0});hit(death,child,100);
        check(death.projectiles.size()==4,"Both flyer deaths emit exactly four actual shots");
        for(auto &shot:death.projectiles) {
            check(shot.kind==ProjectileKind::Bullet,"Ink shots do not invent tar impact puddles");
            if(id.variant==0)check(std::abs(shot.velocity.x)<.001f||std::abs(shot.velocity.z)<.001f,"Sucker death directions are cardinal");
            else check(std::abs(std::abs(shot.velocity.x)-std::abs(shot.velocity.z))<.001f,"Ink death directions are diagonal");
        }
        if(id.variant==0)check(death.hazards.empty(),"Sucker has no invented death creep");
        else {
            check(death.hazards.size()==1&&death.hazards[0].kind==HazardKind::Tar&&death.hazards[0].damage==0,"Ink leaves slowing black creep at death position");
            death.godMode=false;death.player.position={0,.85f,0};death.projectiles.clear();death.step({});
            check(death.player.hp==100&&death.player.slowTime>0,"Ink death creep slows without damage; death shots tested separately");
        }
    }
    std::cout<<"TUFF_ATTACKS armored_ink=1 exposed_sucker=1 body_spray=1 cardinal_ordinal_deaths=1 slowing_black_creep=1\n";
}
void suppliedBombAndCap() {
    auto s=fixture();spawn(s);s.dynamite=0;s.step({});
    check(s.suppliedBombs.size()==2,"Full encounter creates actual supplied pickups");
    s.player.position=s.suppliedBombs.front().charge.position;s.player.position.y=.85f;s.step({});
    check(s.carriedBomb()!=nullptr&&s.dynamite==0,"Approach picks up a bomb with empty inventory");
    const auto body=s.rooms[0].segmented[0].chains[0].members[3];
    // Hold a real armed bomb beside a moving part until its ordinary fuse ends.
    // Teleporting the player is limited to this damage-plumbing probe, not balance evidence.
    for(int tick=0;tick<190;++tick){s.player.position=s.findEnemy(body)->position;s.step({});}
    check(!s.carriedBomb()&&s.stats.explosions==1&&s.findEnemy(body)->segmentArmor==0&&s.findEnemy(body)->hp==112&&s.dynamite==0,
          "Actual supplied bomb fuse/explosion removes armor without spending inventory or harming flesh on the stripping hit");
    bool overshoot=false;
    for(uint64_t seed=0;seed<30&&!overshoot;++seed) {
        auto cap=fixture();cap.combatRng=Random(seed);spawn(cap);
        for(int n=0;n<3;++n)cap.spawnMonster(monsterId(61),{float(n)*2,.85f,15});
        for(auto &e:cap.enemies)if(e.segmentHead)e.cooldown=0;
        cap.step({});
        const auto count=[&]{return std::count_if(cap.enemies.begin(),cap.enemies.end(),[](const auto &e){return e.alive&&e.monster.type==61;});};
        check(count()>=4&&count()<=5,"All heads share room child cap, counting queued bursts");overshoot=count()==5;
        for(int tick=0;tick<15;++tick){for(auto &e:cap.enemies)if(e.segmentHead)e.cooldown=0;cap.step({});}
        check(count()<=5,"Further simultaneous heads cannot bypass cap");
    }
    check(overshoot,"A final two-child burst may pass the pre-attempt four-child cap");
    std::cout<<"TUFF_SUPPLY actual_pickup_fuse_explosion=1 inventory_unchanged=1 shared_child_cap=1 burst_overshoot=1\n";
}
void externalAndStage() {
    const auto root=std::filesystem::temp_directory_path()/("deathward-tuff-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup {std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}} cleanup{root};
    std::filesystem::create_directories(root);
    for(const auto &file:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(file.path().extension()==".mechanics")
        std::filesystem::copy_file(file.path(),root/file.path().filename());
    const auto file=root/"segmented.mechanics";std::ifstream input(file);std::string data((std::istreambuf_iterator<char>(input)),{});
    const std::string from="1.55 15 .25 .14 1.8 .8",to="1.55 30 .25 .14 3.6 .8";const auto at=data.find(from);check(at!=std::string::npos,"Editable chain values exist");
    data.replace(at,from.size(),to);{std::ofstream out(file);out<<data;}
    auto changed=MechanicsLibrary::load(root);auto before=fixture(),after=fixture(changed);const auto first=spawn(before),second=spawn(after);ticks(before,30);ticks(after,30);
    check(before.findEnemy(first)->segmentArmor==15&&after.findEnemy(second)->segmentArmor==30&&
          after.findEnemy(second)->position.x-before.findEnemy(first)->position.x>.8f,"External armor/speed affect new snapshot only");
    int reached=0;
    for(uint64_t seed=0;seed<100;++seed){ExpeditionPlan plan(seed);for(int floor=0;floor<plan.floorCount;++floor) {
        const auto p=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
        if(p.bossMonster!=monsterId(19,2))continue;
        check(p.band==1&&p.variant==FloorVariant::Standard,"Tuff never leaves reviewed stage and variant");
        if(reached>=3)continue;
        Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);
        run.jumpDebug(run.finalRoom());run.godMode=true;ticks(run,400);
        check(run.rooms.back().segmented.size()==1&&run.suppliedBombs.size()==2,"Real seeded arena activates whole encounter and stock");
        for(const auto &bomb:run.suppliedBombs)check(!run.arena.path(run.player.position,add(bomb.charge.position,{0,.67f,0}),.48f).empty(),"Real generated bombs remain reachable");
        for(const auto &e:run.enemies)if(e.segmentedEncounter)check(!run.arena.blocked(e.position,e.radius),"Actual arena roaming respects terrain");
        const auto inventory=run.dynamite;run.killAll();ticks(run,1);
        check(run.roomClear&&run.bossKilled&&run.rooms.back().bossPaid&&run.dynamite==inventory+1,"Real boss arena completes and pays once");
        std::cout<<"TUFF_STAGE seed="<<seed<<" floor="<<floor<<" room="<<run.room<<" stock_reachable=1 complete=1\n";++reached;
    }}
    check(reached==3,"Three independently generated Tuff encounters reached");
    std::cout<<"TUFF_EXTERNAL immutable_snapshot=1 armor_speed=1 variant_filter=1\n";
}
void startingKitProbe() {
    for(uint64_t seed:{1u,9u,23u}) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,2);
        s.jumpDebug(s.finalRoom());s.godMode=false;s.dynamite=0;s.debugScenario=false;
        for(int tick=0;tick<14400&&!s.dead&&!s.roomClear;++tick) {
            Input in;const Enemy *armored=nullptr,*target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&!s.content->statue(e.monster)) {
                if(e.segmentArmor>0) {if(!armored||planarDistance(s.player.position,e.position)<planarDistance(s.player.position,armored->position))armored=&e;}
                else if(!target||planarDistance(s.player.position,e.position)<planarDistance(s.player.position,target->position))target=&e;
            }
            auto move=Vector3{};
            if(const auto *bomb=s.carriedBomb()) {
                if(armored) {
                    const auto delta=horizontal(sub(armored->position,s.player.position));const float range=length(delta);
                    move=mul(unit(delta),std::clamp((range-7)*.5f,-1.f,1.f));
                    if(bomb->charge.age>2.1f){in.fire=true;in.aim=add(armored->position,mul(armored->velocity,.7f));}
                } else {in.fire=true;in.aim=target?target->position:add(s.player.position,{10,0,0});}
            } else {
                const SuppliedBomb *pickup=nullptr;
                if(armored)for(const auto &b:s.suppliedBombs)if(b.state==SuppliedBombState::Pickup&&
                    (!pickup||planarDistance(s.player.position,b.charge.position)<planarDistance(s.player.position,pickup->charge.position)))pickup=&b;
                if(pickup)move=unit(horizontal(sub(pickup->charge.position,s.player.position)));
                else if(target) {
                    const auto toward=unit(horizontal(sub(target->position,s.player.position)));
                    move=add(Vector3{-toward.z,0,toward.x},mul(toward,std::clamp((planarDistance(target->position,s.player.position)-9)*.5f,-1.f,1.f)));
                }
                if(target){in.fire=true;in.aim=add(target->position,mul(target->velocity,.2f));}
            }
            for(const auto &e:s.enemies)if(e.alive&&!s.content->statue(e.monster)) {
                const auto away=horizontal(sub(s.player.position,e.position));const float range=length(away);
                if(range<3)move=add(move,mul(unit(away),(3-range)*1.2f));
                if(range<1.8f)in.dodge=true;
            }
            for(const auto &b:s.suppliedBombs)if(b.state==SuppliedBombState::Thrown&&b.charge.age>2) {
                const auto away=horizontal(sub(s.player.position,b.charge.position));if(length(away)<5)move=add(move,mul(unit(away),3));
            }
            for(const auto &shot:s.projectiles)if(shot.hostile&&distance(shot.position,s.player.position)<2)in.dodge=true;
            in.movement=unit(move);s.step(in);
        }
        float hp=0,armor=0;int alive=0;
        for(const auto &e:s.enemies)if(e.alive&&e.segmentedEncounter){++alive;hp+=e.hp;armor+=e.segmentArmor;}
        std::cout<<"TUFF_STARTING_KIT_PROBE seed="<<seed<<" seconds="<<s.stats.duration<<" player_hp="<<s.player.hp<<" dead="<<s.dead
            <<" boss_killed="<<s.bossKilled<<" room_clear="<<s.roomClear<<" remaining_threats="<<s.roomThreats()<<" remaining_parts="<<alive<<" remaining_hp="<<hp<<" remaining_armor="<<armor
            <<" explosions="<<s.stats.explosions<<" inventory="<<s.dynamite<<" god=0 teleports=0\n";
    }
}
}
int main(int argc,char **argv){try{if(argc==2&&std::string(argv[1])=="--balance-probe"){startingKitProbe();return 0;}
 compositionAndMovement();armorAndDamage();topologyAndCompletion();childrenAndDeathCrosses();suppliedBombAndCap();externalAndStage();
 std::cout<<"PASS segmented Tuff encounter, armor, topology, movement, children and aggregate reward\n";return 0;
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
