#include "items/Items.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b,float eps=.001f){return std::abs(a-b)<eps;}
Simulation fixture() {
    Simulation run(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
    run.arena=Arena{};run.arena.bounds={{-45,-1,-45},{45,8,45}};
    run.rooms.resize(run.arena.rooms.size());
    for(auto &r:run.arena.rooms){r.bounds=run.arena.bounds;r.center={0,.85f,0};}
    for(auto &r:run.rooms){r.residents.clear();r.cleared=false;}
    run.enemies.clear();run.moneyPickups.clear();run.player.position={0,.85f,0};
    run.debugScenario=true;run.godMode=true;run.roomClear=false;
    return run;
}
EntityId enemy(Simulation &run,Vector3 p,float hp=300,EnemyKind kind=EnemyKind::Gunman) {
    const auto id=run.spawn(kind,p);auto &e=*run.findEnemy(id);
    e.hp=e.maxHp=hp;e.state=EnemyState::Stunned;e.stateTime=10000;return id;
}
void tick(Simulation &run,int n){for(int i=0;i<n;++i)run.step({});}
void primary(Simulation &run,bool arrows=false) {
    Input in;in.fire=true;in.aim=add(run.player.position,{100,0,0});if(arrows)in.aimDirection=Vector3{1,0,0};
    run.player.fireCooldown=0;run.step(in);
}
void rootShot(Simulation &run,Vector3 at,Vector3 heading={1,0,0},bool sixth=false) {
    Event e;e.position=e.origin=at;e.direction=heading;e.lastRound=sixth;run.queueRoot(e);run.drainEvents();
}
std::string fingerprint(const Simulation &r) {
    std::ostringstream s;s<<std::hexfloat<<r.player.hp<<':'<<r.player.fireCooldown<<':'<<r.player.nextRound<<':'
      <<r.stats.shots<<':'<<r.stats.projectiles<<':'<<r.stats.explosions<<':'<<r.stats.kills<<':'<<r.stats.splits<<':'<<r.stats.ghosts<<':'<<r.stats.suppressed;
    for(const auto &e:r.enemies)s<<'E'<<e.id<<':'<<e.hp<<':'<<e.alive;
    for(const auto &p:r.projectiles)s<<'P'<<p.id<<':'<<p.damage<<':'<<p.life<<':'<<p.position.x<<':'<<p.position.z<<':'
      <<p.velocity.x<<':'<<p.velocity.z<<':'<<p.pierce<<':'<<p.bounces<<':'<<p.returning<<':'<<p.capSpent;
    for(const auto &h:r.hazards)s<<'H'<<h.position.x<<':'<<h.position.z<<':'<<h.age<<':'<<h.secondary;
    return s.str();
}
void pairwise() {
    int pairs=0;
    for(int a=0;a<ItemCount;++a)for(int b=a;b<ItemCount;++b) {
        auto left=fixture(),right=fixture();left.grant(ItemId(a));left.grant(ItemId(b));
        right.grant(ItemId(b));right.grant(ItemId(a));
        for(auto *r:{&left,&right}) {
            enemy(*r,{3,.85f,0},50);enemy(*r,{6,.85f,1},35);enemy(*r,{6,.85f,-1},35);
            enemy(*r,{11,.85f,0},100000,EnemyKind::Boss);
            r->arena.boundaryWalls.push_back({{15,0,-8},{15.5f,4,8}});r->arena.rebuildWalls();
            r->placeDynamite();
        }
        for(int frame=0;frame<360;++frame) {
            Input mouse;mouse.fire=frame<90;mouse.aim={100,.85f,0};
            Input arrows=mouse;arrows.aimDirection=Vector3{1,0,0};
            left.step(mouse);right.step(arrows);
            check(fingerprint(left)==fingerprint(right),"pair/order/input mismatch "+std::to_string(a)+"/"+std::to_string(b)+" frame "+std::to_string(frame));
        }
        left.enterRoom(1);check(left.projectiles.empty()&&left.hazards.empty()&&left.chains.empty()&&left.queuedEvents()==0,"room exit clears every weapon descendant");
        ++pairs;
    }
    std::cout<<"Pair matrix: "<<pairs<<" unordered pairs including duplicates; both orders and mouse/arrow inputs\n";
}
void forms() {
    auto scatter=fixture();scatter.grant(ItemId::Scatter);primary(scatter);
    check(scatter.projectiles.size()==5&&scatter.stats.shots==1&&scatter.player.nextRound==2,"fan is one trigger pull and one cylinder step");
    for(const auto &p:scatter.projectiles)check(near(p.damage,9.12f)&&near(p.life*p.attack.speed,14),"pellet damage/range trade-off");
    check(scatter.projectiles.front().velocity.z*scatter.projectiles.back().velocity.z<0,"fan spreads to both sides");
    auto rail=fixture();rail.grant(ItemId::Rail);primary(rail);
    check(rail.projectiles.size()==1&&near(rail.projectiles[0].damage,39.6f)&&near(length(rail.projectiles[0].velocity),18)&&
          rail.projectiles[0].pierce==3&&near(rail.player.fireCooldown,.5f),"rail is heavier, slower and piercing with slower cadence");
    rail.grant(ItemId::Scatter);primary(rail);
    check(rail.projectiles.size()==4&&near(rail.projectiles.back().damage,19.008f),"scatter/rail explicit three-spike hybrid");
    auto sixth=fixture();sixth.grant(ItemId::Scatter);sixth.grant(ItemId::Judas);
    for(int i=0;i<6;++i)primary(sixth);
    check(sixth.stats.shots==6&&sixth.player.nextRound==1,"fragments/pellets do not consume cylinder positions");
    int blessed=0;for(const auto &p:sixth.projectiles)if(p.lastRound){++blessed;check(p.pierce==6,"sixth primary blesses every pellet once");}
    check(blessed==5,"exactly the sixth fan gets Judas");
    auto duplicates=fixture();
    for(int i=0;i<12;++i)for(int item=5;item<ItemCount;++item)duplicates.grant(ItemId(item));
    primary(duplicates);
    check(duplicates.projectiles.size()==5&&duplicates.projectiles[0].pierce==11&&near(duplicates.projectiles[0].attack.homingTurn,2.55f),"duplicates respect explicit hybrid, pierce and turn caps");
    check(duplicates.projectiles[0].attack.capDamage==22&&near(duplicates.player.fireCooldown,.66f),"cap/cadence duplicate limits");
}
void guidanceAndReturn() {
    auto homing=fixture();homing.grant(ItemId::Lodestone);
    enemy(homing,{8,.85f,4});rootShot(homing,{0,.85f,0});const auto id=homing.projectiles.front().id;
    tick(homing,1);const auto &p=homing.projectiles.front();
    const float angle=std::atan2(p.velocity.z,p.velocity.x);
    check(p.id==id&&angle>0&&angle<=1.5f*Tick+.0001f&&near(length(p.velocity),21.32f),"homing turns gradually and pays speed tax");
    auto cover=fixture();cover.grant(ItemId::Lodestone);
    enemy(cover,{8,.85f,0});const auto visible=enemy(cover,{5,.85f,-5});
    cover.arena.boundaryWalls.push_back({{3,0,-1},{4,3,2}});cover.arena.rebuildWalls();
    rootShot(cover,{0,.85f,0});tick(cover,1);
    check(cover.projectiles.front().guidedTarget==visible,"homing ignores a hidden nearer target");
    auto returning=fixture();returning.grant(ItemId::Return);const auto body=enemy(returning,{3,.85f,0});
    rootShot(returning,{.7f,.85f,0});tick(returning,100);
    check(near(returning.findEnemy(body)->hp,252)&&returning.projectiles.empty(),"plain spring hits one body outward and once back, then is caught");
    auto bounced=fixture();bounced.grant(ItemId::Return);bounced.grant(ItemId::Ricochet);
    bounced.arena.boundaryWalls.push_back({{5,0,-4},{5.3f,3,4}});bounced.arena.rebuildWalls();
    rootShot(bounced,{.7f,.85f,0});bool turned=false;float previous=10;
    for(int i=0;i<150&&!bounced.projectiles.empty();++i) {
        bounced.step({});if(bounced.projectiles.empty())break;
        const auto &q=bounced.projectiles.front();check(q.life<previous,"turns and bounces cannot reset lifetime");previous=q.life;
        if(q.returning){turned=true;check(q.bounces==0,"wall bounces are outbound-only");}
    }
    check(turned&&bounced.stats.bounces>0&&bounced.projectiles.empty(),"ricochet/return completes without a repeating turn");
    auto walls=fixture();walls.grant(ItemId::Rail);walls.grant(ItemId::Judas);
    walls.arena.boundaryWalls.push_back({{2,0,-5},{2.3f,3,5}});walls.arena.rebuildWalls();
    const auto hidden=enemy(walls,{4,.85f,0});rootShot(walls,{0,.85f,0},{1,0,0},true);tick(walls,30);
    check(walls.findEnemy(hidden)->hp==300&&walls.projectiles.empty(),"body piercing never passes a solid wall");
}
void capAndProvenance() {
    auto cap=fixture();cap.grant(ItemId::Cap);cap.grant(ItemId::Judas);cap.grant(ItemId::Return);
    enemy(cap,{3,.85f,0},1000);enemy(cap,{5,.85f,0},1000);rootShot(cap,{.7f,.85f,0},{1,0,0},true);tick(cap,150);
    check(cap.stats.explosions==1,"piercing and return hits do not reset the per-projectile cap trigger");
    auto risk=fixture();risk.godMode=false;risk.grant(ItemId::Cap);const auto target=enemy(risk,{1.3f,.85f,0},1000);
    primary(risk);tick(risk,2);
    check(near(risk.player.hp,93)&&near(risk.findEnemy(target)->hp,973.2f),"small cap blast has direct damage tax and real self-damage");
    auto ghost=fixture();ghost.grant(ItemId::Ghost);ghost.grant(ItemId::Cap);
    enemy(ghost,{3,.85f,0},1);enemy(ghost,{3,.85f,1},1);rootShot(ghost,{.7f,.85f,0});tick(ghost,10);
    check(ghost.stats.ghosts>=2,"direct and explosive kills both produce ghosts");
    for(const auto &p:ghost.projectiles)if(p.ghost)check(near(p.damage,16.8f),"ghost preserves projectile damage after an area kill, without applying taxes twice");
    Event kill;kill.type=EventType::EnemyKilled;kill.damage=900;kill.origin={0,.85f,0};kill.direction={1,0,0};
    ghost.queueRoot(kill);ghost.drainEvents();check(near(ghost.projectiles.back().damage,16.8f),"shotless kills never create explosion-strength bullets");
    auto split=fixture();split.grant(ItemId::Split);split.grant(ItemId::Lodestone);split.grant(ItemId::Cap);
    enemy(split,{8,.85f,0},1000);rootShot(split,{0,.85f,0});tick(split,25);
    check(split.stats.splits>0,"direct hit produces fragments");
    for(const auto &p:split.projectiles) {
        check(p.life<3.2f-20*Tick,"split inherits remaining lifetime");
        check(p.attack.homingTurn>0&&!p.capSpent,"new fragments each inherit guidance and a fresh one-use cap");
    }
}
void braid() {
    auto run=fixture();run.godMode=false;run.grant(ItemId::Braid);run.placeDynamite();
    check(run.dynamite==2&&run.hazards.size()==1&&run.hazards[0].blastDamage==70&&near(run.hazards[0].radius,3.3f),"braid spends one stick and reduces primary blast");
    tick(run,121);check(run.stats.explosions==1&&run.hazards.size()==2,"main charge leaves exactly two timed children");
    for(const auto &h:run.hazards)check(h.secondary&&h.braidCopies==0&&h.blastDamage==35&&h.age<h.delay,"children inherit power but cannot reproduce");
    check(run.player.hp==82,"braid primary self damage follows its snapshot");
    const float age=run.hazards.front().age;run.rewardOpen=true;tick(run,30);run.rewardOpen=false;
    check(run.hazards.front().age==age,"secondary fuse pauses in modals");
    run.clearRoom();check(run.hazards.size()==2,"ordinary room clear preserves player ordnance");
    tick(run,80);check(run.stats.explosions==3&&run.hazards.empty()&&run.chains.empty(),"two children detonate once and release the root chain");
    auto cover=fixture();cover.grant(ItemId::Braid);
    Breakable gate;gate.kind=BreakableKind::CacheGate;gate.health=2;gate.bounds={{1.2f,0,-1},{1.8f,2,1}};gate.rewardPosition={2.5f,.85f,0};
    cover.arena.breakables.push_back(gate);cover.arena.rebuildWalls();cover.placeDynamite();tick(cover,210);
    check(cover.arena.breakables[0].destroyed&&cover.dynamite==2,"paid braid children deliberately improve hard demolition efficiency");
    auto limited=fixture();limited.grant(ItemId::Braid);limited.limits.hazards=1;limited.placeDynamite();tick(limited,210);
    check(limited.stats.explosions==2&&limited.stats.suppressed==1&&limited.chains.empty(),"hazard capacity bounds children without leaking active work");
}
void rewardsAndSave() {
    std::set<ItemId> offered;
    for(uint64_t seed=0;seed<32;++seed) {
        Simulation run(seed,1,{});
        for(const auto &r:run.rooms)for(auto i:r.offers)offered.insert(i);
        for(const auto &o:run.shopOffers)if(o.kind==ShopOfferKind::Power)offered.insert(o.item);
    }
    check(offered.size()==ItemCount,"all eleven items occur in seeded rewards/shop stock");
    const auto path=std::filesystem::temp_directory_path()/"deathward-m4-items.save";
    std::filesystem::remove(path);CampaignStore store(path);const auto id=store.begin(55);
    Simulation run(55,id,{});for(int i=0;i<ItemCount;++i)run.grant(ItemId(i));
    store.checkpoint(run.summary());CampaignStore read(path);
    check(read.data().pending->items==run.items,"all appended item IDs survive existing save format");
    read.recover();CampaignStore resumed(path);check(resumed.data().history.back().items==run.items,"interrupted summaries preserve the complete build");
    std::filesystem::remove(path);
}
void boundedBuild() {
    auto run=fixture();
    for(int i=0;i<ItemCount;++i)run.grant(ItemId(i));
    for(int i=0;i<3;++i)run.grant(ItemId::Split);
    run.limits.projectiles=64;run.limits.eventsPerChain=64;run.limits.eventsPerTick=32;run.limits.queuedEvents=128;
    for(int i=0;i<60;++i)enemy(run,{2+float(i%10)*.6f,.85f,(float(i/10)-2.5f)*.5f},5);
    primary(run);run.placeDynamite();
    tick(run,180);
    check(run.stats.suppressed>0&&run.stats.maxProjectiles<=64&&run.projectiles.size()<=64&&run.queuedEvents()<=128,
          "full build obeys projectile, event and queue limits under branching pressure");
    run.enemies.clear();tick(run,300);
    check(run.projectiles.empty()&&run.hazards.empty()&&run.chains.empty()&&run.queuedEvents()==0,
          "full build retires all suppressed and completed work");
}
void bossesAndSnapshots() {
    for(int item=5;item<ItemCount;++item) {
        auto run=fixture();run.grant(ItemId(item));
        const auto id=enemy(run,{3,.85f,0},1000,EnemyKind::Boss);
        primary(run);if(ItemId(item)==ItemId::Braid)run.placeDynamite();
        tick(run,210);check(run.findEnemy(id)->hp<1000,"each new build can damage a boss target");
    }
    auto run=fixture();rootShot(run,{0,.85f,0});
    run.grant(ItemId::Rail);run.grant(ItemId::Cap);run.tunePlayer(100,400);
    check(run.projectiles.front().damage==24&&run.projectiles.front().attack.capDamage==0&&
          !run.projectiles.front().attack.rail,"new pickups and tuning cannot rewrite an in-flight specification");
}
}
int main(){try{forms();guidanceAndReturn();capAndProvenance();braid();pairwise();boundedBuild();bossesAndSnapshots();rewardsAndSave();std::cout<<"PASS six weapon mechanics, explicit interactions, duplicates, provenance, resource rules, input parity and saves\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
