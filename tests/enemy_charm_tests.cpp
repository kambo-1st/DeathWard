#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b,float epsilon=.002f){return std::abs(a-b)<epsilon;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={0,.85f,30};return s;
}
void ticks(Simulation &s,int n=1,int hz=30){for(int i=0;i<n;++i)s.step({},1.f/hz);}
EntityId spawn(Simulation &s,MonsterId kind,Vector3 at={0,.85f,0}) {
    auto id=s.spawnMonster(kind,at);s.findEnemy(id)->cooldown=0;return id;
}
void hold(Simulation &s,EntityId id) {
    auto &e=*s.findEnemy(id);e.age=1;e.state=EnemyState::Stunned;e.stateTime=100;e.velocity={};
}
void hit(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
const std::array<MonsterId,5> Cohort{{monsterId(10),monsterId(10,1),monsterId(11),monsterId(11,1),monsterId(12)}};
void duration() {
    for(auto kind:Cohort)for(int hz:{30,60,120}) {
        auto s=fixture();auto id=spawn(s,kind);hold(s,id);
        check(s.applyEnemyStatus(id,EnemyStatus::Charm,300),"temporary Charm applies to each reviewed identity");
        check(!s.findEnemy(id)->friendly&&s.roomThreats()==1,"temporary Charm retains hostile affiliation and room threat");
        ticks(s,hz,hz);check(s.findEnemy(id)->statuses->charm==270,"real-time duration");
        s.applyEnemyStatus(id,EnemyStatus::Charm,20);check(s.findEnemy(id)->statuses->charm==270,"shorter refresh neither adds nor shortens");
        s.applyEnemyStatus(id,EnemyStatus::Charm,360);check(s.findEnemy(id)->statuses->charm==360,"longer refresh is max with no120/150 cap");
        check(!s.applyEnemyStatus(id,EnemyStatus::Charm,-1)&&s.findEnemy(id)->statuses->charm==360,
              "unimplemented permanent conversion is rejected, never interpreted as abs(duration)");
        s.removeEnemyStatus(id,EnemyStatus::Charm);check(!s.findEnemy(id)->affectedBy(EnemyStatus::Charm),"explicit removal");
        s.applyEnemyStatus(id,EnemyStatus::Charm,30);s.applyEnemyStatus(id,EnemyStatus::Freeze,30);s.applyEnemyStatus(id,EnemyStatus::Slow,30);
        ticks(s,hz-1,hz);check(s.findEnemy(id)->affectedBy(EnemyStatus::Charm),"active before exact expiry");ticks(s,1,hz);
        check(!s.findEnemy(id)->affectedBy(EnemyStatus::Charm)&&s.roomThreats()==1,"Freeze/Slow do not extend duration or clear room");
        s.applyEnemyStatus(id,EnemyStatus::Charm,90);s.rewardOpen=true;ticks(s,hz,hz);
        check(s.findEnemy(id)->statuses->charm==90,"modal pause holds duration");
    }
    std::cout<<"CHARM_TIME max_refresh=1 no_cap=1 expiry_partition=1 permanent_rejected=1 freeze_slow=1 room_threat=1 pause=1\n";
}
void targeting() {
    for(auto kind:{monsterId(10),monsterId(10,1),monsterId(12)}) {
        auto s=fixture();auto id=spawn(s,kind);auto close=spawn(s,monsterId(12),{5,.85f,0});auto far=spawn(s,monsterId(12),{-9,.85f,0});
        hold(s,close);hold(s,far);s.applyEnemyStatus(id,EnemyStatus::Charm,180);s.applyEnemyStatus(close,EnemyStatus::Charm,180);ticks(s);
        check(s.findEnemy(id)->statuses->charmTarget==far,"ordinary target beats closer penalized charmed target");
        s.findEnemy(far)->alive=false;ticks(s);
        check(s.findEnemy(id)->statuses->charmTarget==close,"dead target discarded; another charmed NPC remains eligible");
        s.findEnemy(close)->alive=false;ticks(s);
        check(s.findEnemy(id)->statuses->charmTarget==0,"no candidate falls back to player");
        // Horf only updates its displayed aim during acquisition/windup; the
        // fallback player here is deliberately outside its20-unit range.
        if(kind.type==10)check(s.findEnemy(id)->target.z>20,"Gaper uses player fallback");
    }
    auto s=fixture();auto id=spawn(s,monsterId(12));auto target=spawn(s,monsterId(12),{6,.85f,0});hold(s,target);
    s.arena.floorProps.push_back({StoryPropKind::Crate,{{2,-.1f,-5},{3,3,5}}});s.arena.rebuildWalls();
    s.applyEnemyStatus(id,EnemyStatus::Charm,180);ticks(s,14);
    check(s.findEnemy(id)->statuses->charmTarget==target&&s.stats.projectiles==0,"selection sees through cover; shooting does not");
    auto roots=fixture();id=spawn(roots,monsterId(10,1));auto parent=spawn(roots,monsterId(12),{5,.85f,0});auto sibling=spawn(roots,monsterId(12),{7,.85f,0});
    auto valid=spawn(roots,monsterId(12),{-10,.85f,0});hold(roots,parent);hold(roots,sibling);hold(roots,valid);
    roots.findEnemy(id)->summoner=parent;roots.findEnemy(sibling)->summoner=parent;
    roots.applyEnemyStatus(id,EnemyStatus::Charm,60);ticks(roots);
    check(roots.findEnemy(id)->statuses->charmTarget==valid,"self, parent and common-parent siblings excluded");
    auto recent=fixture();id=spawn(recent,monsterId(12));target=spawn(recent,monsterId(12),{6,.85f,0});
    recent.applyEnemyStatus(id,EnemyStatus::Charm,60);ticks(recent);
    check(recent.findEnemy(id)->statuses->charmTarget==0,"newborn target excluded initially");ticks(recent,3);
    check(recent.findEnemy(id)->statuses->charmTarget==target,"newborn becomes eligible after native age gate");
    for(int hz:{30,60,120}) {
        auto pursue=fixture();id=spawn(pursue,monsterId(10,1));target=spawn(pursue,monsterId(12),{20,.85f,0});hold(pursue,target);
        pursue.applyEnemyStatus(id,EnemyStatus::Charm,120);ticks(pursue,hz,hz);
        check(pursue.findEnemy(id)->position.x>1&&std::abs(pursue.findEnemy(id)->position.z)<.5f,"Gaper pursues NPC instead of player");
    }
    std::cout<<"CHARM_TARGET weighted=1 dead_fallback=1 cover=1 ancestry=1 birth_age=1 pursuit=1\n";
}
void shots() {
    auto s=fixture();auto id=spawn(s,monsterId(12));auto target=spawn(s,monsterId(12),{7,.85f,0});hold(s,target);
    s.grant(ItemId::Powder);s.grant(ItemId::Ghost);
    s.applyEnemyStatus(id,EnemyStatus::Charm,180);ticks(s,12);
    check(!s.projectiles.empty(),"charmed Horf shoots");auto shot=s.projectiles.front();
    check(shot.hostile&&shot.hitsEnemies&&!shot.ignoresPlayer&&near(shot.npcDamage,19.2f)&&near(shot.damage,10),"independent NPC shot policy and damage");
    check(shot.attack.capDamage==0&&shot.pierce==0,"player build does not rewrite charmed NPC shot");
    check(shot.velocity.x>0&&std::abs(shot.velocity.z)<.01f,"Horf aims at NPC");
    s.removeEnemyStatus(id,EnemyStatus::Charm);hit(s,id,1000);ticks(s,30);
    check(s.findEnemy(target)&&near(s.findEnemy(target)->hp,12.8f),"emitted shot preserves NPC damage and policy after source expiry/death");
    auto player=fixture();player.godMode=false;id=spawn(player,monsterId(12));player.player.position={7,.85f,0};
    player.applyEnemyStatus(id,EnemyStatus::Charm,180);ticks(player,35);
    check(near(player.player.hp,StartingHealth-10*EnemyDamageMultiplier),"temporary Charm projectile fallback still harms player");
    for(bool before:{true,false}) {
        auto pending=fixture();id=spawn(pending,monsterId(11));auto &e=*pending.findEnemy(id);
        e.headless->initialized=true;e.headless->cooldown=0;e.velocity={3,0,0};pending.limits.projectiles=0;
        if(before)pending.applyEnemyStatus(id,EnemyStatus::Charm,60);ticks(pending);
        check(e.headless->pendingShots.size()==1,"Gusher selected payload");
        if(before)pending.removeEnemyStatus(id,EnemyStatus::Charm);else pending.applyEnemyStatus(id,EnemyStatus::Charm,60);
        pending.limits.projectiles=512;ticks(pending);
        check(pending.projectiles.size()==1&&pending.projectiles.front().hitsEnemies==before,"selected payload snapshots affiliation before capacity retry");
    }
    auto plain=fixture(),charm=fixture();auto a=spawn(plain,monsterId(11,1)),b=spawn(charm,monsterId(11,1));
    charm.applyEnemyStatus(b,EnemyStatus::Charm,120);ticks(plain,60);ticks(charm,60);
    check(distance(plain.findEnemy(a)->position,charm.findEnemy(b)->position)<.001f&&charm.stats.projectiles==0,"Pacer still wanders and never shoots");
    std::cout<<"CHARM_SHOTS independent_masks=1 npc_hp=1 player_hp=1 owner_lifetime=1 selected_payload=1 pacer=1\n";
}
void contact() {
    const float damage=std::log(1.2f)*33*3.2f;
    for(auto kind:Cohort) {
        auto s=fixture();auto a=spawn(s,kind),b=spawn(s,monsterId(12),{.8f,.85f,0});hold(s,a);hold(s,b);
        s.applyEnemyStatus(a,EnemyStatus::Charm,120);ticks(s);
        check(s.findEnemy(a)&&s.findEnemy(b)&&near(s.findEnemy(a)->hp,32-damage)&&near(s.findEnemy(b)->hp,32-damage),"reciprocal native max-HP contact curve");
    }
    for(int hz:{30,60,120}) {
        auto s=fixture();auto a=spawn(s,monsterId(12)),b=spawn(s,monsterId(12),{.8f,.85f,0});hold(s,a);hold(s,b);
        s.findEnemy(a)->hp=s.findEnemy(b)->hp=10000;s.applyEnemyStatus(a,EnemyStatus::Charm,120);
        for(int i=0;i<hz;++i){s.findEnemy(a)->position={0,.85f,0};s.findEnemy(b)->position={.8f,.85f,0};ticks(s,1,hz);}
        // One immediate hit plus every staggered native3-update cache reset.
        const int count=1+(30+int(a))/3-(1+int(a))/3;
        check(near(s.findEnemy(b)->hp,10000-count*damage,.02f),"contact cache follows3-frame source poll at30/60/120Hz");
    }
    auto pending=fixture();auto a=spawn(pending,monsterId(12)),b=spawn(pending,monsterId(12),{.8f,.85f,0});hold(pending,a);hold(pending,b);
    pending.applyEnemyStatus(a,EnemyStatus::Charm,2);pending.limits.queuedEvents=0;
    ticks(pending);check(pending.findEnemy(a)->charmContact->pending.has_value(),"capacity retains one selected hit");
    pending.removeEnemyStatus(a,EnemyStatus::Charm);pending.findEnemy(a)->position={-20,.85f,0};pending.limits.queuedEvents=1024;ticks(pending);
    check(near(pending.findEnemy(b)->hp,32-damage),"pending contact survives expiry and separation without resampling");
    auto wall=fixture();a=spawn(wall,monsterId(12));b=spawn(wall,monsterId(12),{.8f,.85f,0});hold(wall,a);hold(wall,b);
    wall.arena.floorProps.push_back({StoryPropKind::Crate,{{.3f,-.1f,-3},{.4f,3,3}}});wall.arena.rebuildWalls();
    wall.applyEnemyStatus(a,EnemyStatus::Charm,30);ticks(wall);check(near(wall.findEnemy(b)->hp,32),"cover blocks NPC contact");
    auto player=fixture();player.godMode=false;a=spawn(player,monsterId(12));player.applyEnemyStatus(a,EnemyStatus::Charm,90);
    player.player.position=player.findEnemy(a)->position;ticks(player);
    check(near(player.player.hp,StartingHealth-10*EnemyDamageMultiplier),"temporary Charm is not friendly contact immunity");
    std::cout<<"CHARM_CONTACT reciprocal=1 native_curve=1 poll_cadence=1 queue_retry=1 cover=1 player_contact=1\n";
}
void combinations() {
    auto s=fixture();auto id=spawn(s,monsterId(10,1));auto target=spawn(s,monsterId(12),{6,.85f,0});hold(s,target);
    s.applyEnemyStatus(id,EnemyStatus::Charm,120);s.applyEnemyStatus(id,EnemyStatus::Fear,120);ticks(s,30);
    check(planarDistance(s.findEnemy(id)->position,s.findEnemy(target)->position)>6,"Fear evades resolved NPC target");
    auto confused=fixture();id=spawn(confused,monsterId(12));target=spawn(confused,monsterId(12),{6,.85f,0});hold(confused,target);
    confused.applyEnemyStatus(id,EnemyStatus::Charm,120);confused.applyEnemyStatus(id,EnemyStatus::Confusion,60);ticks(confused,30);
    check(confused.stats.projectiles==0,"Confusion still suppresses Horf acquisition under Charm");
    auto slow=fixture();id=spawn(slow,monsterId(12));target=spawn(slow,monsterId(12),{12,.85f,0});hold(slow,target);
    slow.applyEnemyStatus(id,EnemyStatus::Charm,120);slow.applyEnemyStatus(id,EnemyStatus::Slow,120);
    ticks(slow,18);check(!slow.projectiles.empty()&&near(slow.projectiles.front().sourceTimeScale,.5f)&&slow.projectiles.front().hitsEnemies,
                       "Slow and Charm coexist on emitted shots");
    auto frozen=fixture();auto a=spawn(frozen,monsterId(12)),b=spawn(frozen,monsterId(12),{.8f,.85f,0});hold(frozen,a);hold(frozen,b);
    frozen.findEnemy(a)->hp=frozen.findEnemy(b)->hp=10000;frozen.applyEnemyStatus(a,EnemyStatus::Charm,120);
    frozen.applyEnemyStatus(a,EnemyStatus::Freeze,60);frozen.applyEnemyStatus(b,EnemyStatus::Freeze,60);
    for(int n=0;n<59;++n){frozen.findEnemy(a)->position={0,.85f,0};frozen.findEnemy(b)->position={.8f,.85f,0};ticks(frozen);}
    check(near(frozen.findEnemy(b)->hp,10000-std::log(1.2f)*33*3.2f,.01f),"Freeze holds contact cache while allowing first physical contact");
    auto swept=fixture();a=spawn(swept,monsterId(12),{-8,.85f,0});b=spawn(swept,monsterId(12));hold(swept,b);
    swept.findEnemy(a)->velocity={500,0,0};swept.applyEnemyStatus(a,EnemyStatus::Charm,60);ticks(swept);
    check(swept.findEnemy(a)->position.x>2&&swept.findEnemy(b)->hp<32,"swept contact detects crossing with separated endpoints");
    auto cached=fixture();a=spawn(cached,monsterId(12));b=spawn(cached,monsterId(12),{9,.85f,0});auto closer=spawn(cached,monsterId(12),{12,.85f,0});hold(cached,b);hold(cached,closer);
    cached.applyEnemyStatus(a,EnemyStatus::Charm,120);ticks(cached);check(cached.findEnemy(a)->statuses->charmTarget==b,"initial nearest target");
    cached.findEnemy(closer)->position={5,.85f,0};
    for(int n=2;n<=16;++n) {
        ticks(cached);
        const bool due=(uint64_t(n)+a)%15==0;
        check(cached.findEnemy(a)->statuses->charmTarget==(due?closer:b),"cached target refreshes on native15-update poll");
        if(due)break;
    }
    std::cout<<"CHARM_COMBINATIONS fear_target=1 confusion=1 slow_shot=1 frozen_contact=1 swept_contact=1 poll15=1\n";
}
void lifecycle() {
    bool witnessed=false;
    for(unsigned seed=0;seed<50&&!witnessed;++seed) {
        auto s=fixture();auto id=spawn(s,monsterId(10,1));s.applyEnemyStatus(id,EnemyStatus::Charm,120);ticks(s,10);
        s.combatRng=Random(seed);hit(s,id,32);auto *e=s.findEnemy(id);
        if(!e||!e->alive||e->monster.type!=11)continue;witnessed=true;
        check(e->statuses->charm==110&&!e->friendly&&s.stats.kills==0&&s.roomThreats()==1,"headless morph preserves timed Charm without rewards");
    }
    check(witnessed,"morph fixture");
    Simulation s(3,1,{},MissionTheme::Canyon);s.debugScenario=true;s.godMode=true;s.enterRoom(1);
    auto id=s.spawnMonster(monsterId(12),s.arena.rooms[1].center);s.applyEnemyStatus(id,EnemyStatus::Charm,90);s.enterRoom(0);ticks(s,60);s.enterRoom(1);
    check(s.findEnemy(id)&&s.findEnemy(id)->statuses->charm==90,"temporary Charm stays with inactive resident room");
    std::cout<<"CHARM_LIFECYCLE morph=1 room_storage=1\n";
}
void configuration() {
    auto base=defaultMechanics();const auto dir=std::filesystem::temp_directory_path()/("dw-charm-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(base->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    const auto file=dir/"first_floor_statuses.mechanics";std::ifstream in(file);const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](const std::string &value){auto text=original;const std::string needle="charm_effect 12.0.0 15 500 1600 3 3.2 110 100 33 19.2";
        const auto at=text.find(needle);check(at!=text.npos,"profile fixture");text.replace(at,needle.size(),value);std::ofstream(file)<<text;return MechanicsLibrary::load(dir);};
    auto s=fixture();s.content=edit("charm_effect 12.0.0 1 4 0 6 3.2 110 100 33 9.6");auto id=spawn(s,monsterId(12));auto target=spawn(s,monsterId(12),{6,.85f,0});hold(s,target);
    s.applyEnemyStatus(id,EnemyStatus::Charm,60);ticks(s,12);check(s.findEnemy(id)->statuses->charmTarget==0,"external range changes target selection");
    check(base->fingerprint()!=s.content->fingerprint()&&base->enemyStatuses(monsterId(12))->charm->range==500,"immutable reload snapshot");
    s=fixture();s.content=edit("# omitted");id=spawn(s,monsterId(12));check(!s.applyEnemyStatus(id,EnemyStatus::Charm,60),"independent opt-in");
    for(const auto *bad:{"charm_effect 12.0.0 0 500 1600 3 3.2 110 100 33 19.2","charm_effect 12.0.0 15 nan 1600 3 3.2 110 100 33 19.2",
        "charm_effect 12.0.0 15 500 -1 3 3.2 110 100 33 19.2","charm_effect 12.0.0 15 500 1600 0 3.2 110 100 33 19.2",
        "charm_effect 12.0.0 15 500 1600 3 0 110 100 33 19.2","charm_effect 12.0.0 15 500 1600 3 3.2 110 0 33 19.2",
        "charm_effect 12.0.0 15 500 1600 3 3.2 110 100 33 inf","charm_effect 13.0.0 15 500 1600 3 3.2 110 100 33 19.2",
        "charm_effect 12.0.0 15 500 1600 3 3.2 110 100 33 19.2\ncharm_effect 12.0.0 15 500 1600 3 3.2 110 100 33 19.2"}) {
        bool rejected=false;try{edit(bad);}catch(const std::exception&){rejected=true;}check(rejected,"invalid Charm profile rejected");
    }
    std::cout<<"CHARM_CONTENT tuning=1 immutable_reload=1 opt_in=1 rejected_contracts=9\n";
}
}
int main(){try{duration();targeting();shots();contact();combinations();lifecycle();configuration();std::cout<<"First-floor temporary Charm contracts passed\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
