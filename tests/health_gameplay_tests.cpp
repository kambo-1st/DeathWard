#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *message){if(!value)throw std::runtime_error(message);}
Simulation fixture() {
    Simulation run(42,1,{},MissionTheme::Canyon);
    run.arena=Arena{};run.arena.walls.clear();
    for(auto &room:run.arena.rooms)room.bounds={{-30,0,-30},{30,4,30}};
    run.rooms.resize(run.arena.rooms.size());run.enemies.clear();run.hazards.clear();
    run.moneyPickups.clear();run.player.position={0,.85f,0};run.debugScenario=true;
    return run;
}
void survival() {
    auto run=fixture();
    Hazard creep;creep.kind=HazardKind::Creep;creep.position=run.player.position;
    creep.delay=0;creep.duration=20;creep.radius=10;creep.damage=10;run.hazards.push_back(creep);
    for(int hit=1;hit<=6;++hit) {
        run.player.hurt=0;run.step({});
        check(run.player.hp==6-hit,"ordinary authored contact amount removes one half heart");
        check(run.dead==(hit==6),"three red hearts survive five ordinary losses and die on sixth");
    }
    auto contact=fixture();const auto toucher=contact.spawnMonster(monsterId(10),contact.player.position);
    check(toucher!=0,"ordinary contact enemy spawned");contact.step({});
    check(contact.player.hp==5,"real grounded Gaper contact removes one half-heart unit");
    auto harmless=fixture();harmless.spawnMonster(monsterId(13),harmless.player.position);harmless.step({});
    check(harmless.player.hp==6,"source no-contact enemy remains harmless");
    auto guarded=fixture();guarded.hazards.push_back(creep);
    Input dodge;dodge.dodge=true;dodge.movement={1,0,0};guarded.step(dodge);
    check(guarded.player.hp==6&&guarded.player.position.x>6*Tick,"universal dodge retains immunity and boost");
    guarded.hazards.clear();guarded.player.dodge=0;
    check(guarded.takeHeartDamage(1)&&guarded.player.hurt==1,"ordinary half-heart hurt window is one second");
    check(!guarded.takeHeartDamage(1),"hurt window rejects repeated damage");
    for(int i=0;i<59;++i)guarded.step({});
    check(!guarded.takeHeartDamage(1),"hurt window persists before its 60Hz boundary");
    guarded.step({});check(guarded.takeHeartDamage(1),"hurt window expires at its 60Hz boundary");
    guarded.player.hurt=0;guarded.takeHeartDamage(2);check(guarded.player.hurt==2,"full-heart hit has two-second ordinary window");
}
void layers() {
    auto run=fixture();
    check(!run.collectHeart(HeartKind::Red,2),"full red health retains pickup");
    check(run.collectHeart(HeartKind::Soul,2)&&run.collectHeart(HeartKind::Black,2),"protective layers collected");
    const auto id=run.spawn(EnemyKind::Rusher,{6,.85f,0});auto *enemy=run.findEnemy(id);enemy->hp=enemy->maxHp=100;
    run.takeHeartDamage(1);check(run.player.hp==6&&run.player.soulHearts==3,"soul/black halves precede red health");
    run.player.hurt=0;run.takeHeartDamage(1);run.drainEvents();
    check(run.player.soulHearts==2&&run.findEnemy(id)->hp==60,"last black half triggers forty-damage burst");
    run.player.hurt=0;run.takeHeartDamage(1,true);
    check(run.player.hp==5&&run.player.soulHearts==2,"explicit red-first source damages red before soul");
    check(run.collectHeart(HeartKind::Red,2)&&run.player.hp==6&&run.player.soulHearts==2,"red pickup fills only red capacity");
    auto pressure=fixture();const auto a=pressure.spawn(EnemyKind::Gunman,{4,.85f,0});
    const auto b=pressure.spawn(EnemyKind::Gunman,{-4,.85f,0});
    pressure.findEnemy(a)->hp=pressure.findEnemy(b)->hp=100;
    pressure.collectHeart(HeartKind::Black,2);pressure.limits.queuedEvents=1;
    pressure.takeHeartDamage(2);pressure.limits.queuedEvents=256;pressure.step({});
    check(pressure.findEnemy(a)->hp==60&&pressure.findEnemy(b)->hp==60,"black burst retains every recipient under queue pressure");
    pressure.step({});check(pressure.findEnemy(a)->hp==60&&pressure.findEnemy(b)->hp==60,"deferred black burst never repeats a recipient");
    auto bone=fixture();auto health=bone.player.sourceHealth();health.maxRed=health.red=0;bone.player.setSourceHealth(health);
    // An empty bone is living health; add it through a modifier before pickup collection.
    health.addBone(1);bone.player.setSourceHealth(health);bone.step({});check(!bone.dead,"empty bone sustains life");
    bone.takeHeartDamage(1);bone.step({});check(bone.dead,"last empty bone break causes death");
    auto broken=fixture();broken.addBrokenHearts(10);
    check(broken.player.maxHp==4&&broken.player.hp==4,"broken hearts reduce maximum usable capacity");
    broken.addBrokenHearts(2);broken.step({});check(broken.dead,"twelve broken hearts leave no living capacity");
}
void pickupsAndEffects() {
    auto run=fixture();run.player.hp=5;
    check(run.spawnHeartPickup(HeartKind::Red,run.player.position,1),"place half red heart");
    run.step({});check(run.player.hp==6&&run.heartPickups.empty(),"walking over half red pickup collects it");
    run.spawnHeartPickup(HeartKind::Red,run.player.position);run.step({});
    check(run.heartPickups.size()==1,"unusable pickup stays in world");
    check(!run.spawnHeartPickup(HeartKind(99),run.player.position),"invalid heart kind rejected");
    const auto frozen=run.spawnMonster(monsterId(10),{4,.85f,0});
    check(frozen!=0,"ordinary Midas target placed");
    run.collectHeart(HeartKind::Golden,1);const auto before=run.player.hp;
    check(before==6,"golden overlay adds no HP");run.takeHeartDamage(2);
    check(run.player.goldenHearts==0&&run.moneyPickups.size()>=3&&run.moneyPickups.size()<=8,"golden depletion produces three to eight pennies");
    check(run.findEnemy(frozen)->statuses&&run.findEnemy(frozen)->statuses->midas==180,"golden burst applies six-second source Midas counter");
    auto rotten=fixture();rotten.player.hp=4;rotten.collectHeart(HeartKind::Rotten,2);rotten.rooms[size_t(rotten.room)].cleared=false;rotten.clearRoom();
    check(rotten.player.rottenHearts==1&&rotten.blueFlies.size()==2,"rotten heart supplies two blue flies");
    rotten.refillRottenHeartFlies();check(rotten.blueFlies.size()==2,"rotten refill caps at twice rotten count");
    rotten.takeHeartDamage(1);check(rotten.player.hp==4&&rotten.player.rottenHearts==0,"half-heart hit consumes full rotten heart");
    check(rotten.player.hurt==1,"rotten double depletion retains original damage cooldown");
    const auto target=rotten.spawn(EnemyKind::Gunman,{5,.85f,0});
    rotten.findEnemy(target)->hp=rotten.findEnemy(target)->maxHp=100;
    for(auto &fly:rotten.blueFlies)fly.position=fly.previous={5,.85f,0};
    rotten.step({},1.f/30);
    check(rotten.blueFlies.empty()&&rotten.findEnemy(target)->hp==4,"two rotten blue flies hit once for twice unchanged player damage each");
}
void upgradesAndRevival() {
    auto run=fixture();run.player.hp=3;run.addRedContainers(2,true);
    check(run.player.maxHp==8&&run.player.hp==5,"HP upgrade adds one filled container without full heal");
    check(run.payHealthCost(1)&&run.player.maxHp==6&&run.player.hp==5,"deal removes a red container without direct damage");
    auto soul=run.player.sourceHealth();soul.maxRed=soul.red=0;soul.soul=8;run.player.setSourceHealth(soul);
    check(run.payHealthCost(1)&&run.player.soulHearts==2,"red-free deal consumes three soul hearts");
    check(!run.payHealthCost(1),"insufficient soul health rejects deal");
    run.grant(ItemId::Judas);check(run.player.maxHp==0,"health-cost item does not invent red capacity in soul-only state");
    auto bones=fixture();auto boneCost=bones.player.sourceHealth();boneCost.maxRed=boneCost.red=0;
    boneCost.addBone(2);bones.player.setSourceHealth(boneCost);
    check(bones.payHealthCost(1)&&bones.player.boneHearts==1,"bone containers pay a container deal before soul health");
    auto life=fixture();life.grant(parseItemKey("isaac:collectible:11"));life.takeHeartDamage(6);life.step({});
    check(!life.dead&&life.player.hp==6&&life.itemStacks(parseItemKey("isaac:collectible:11"))==0,"1up revives once and is consumed");
    life.player.hurt=0;life.takeHeartDamage(6);life.step({});check(life.dead,"consumed extra life cannot revive twice");
    auto protectedOnly=fixture();auto health=protectedOnly.player.sourceHealth();health.red=health.maxRed=0;health.soul=2;protectedOnly.player.setSourceHealth(health);
    protectedOnly.grant(parseItemKey("isaac:collectible:11"));protectedOnly.takeHeartDamage(2);protectedOnly.step({});
    check(!protectedOnly.dead&&protectedOnly.player.soulHearts==1,"red-free 1up restores half a soul heart");
}
void floorTravel() {
    Simulation run(42,1,{},MissionTheme::Canyon);run.jumpDebug(run.finalRoom());run.clearRoomDebug();
    run.player.hp=3;run.collectHeart(HeartKind::Soul,3);run.collectHeart(HeartKind::Bone,1);
    run.collectHeart(HeartKind::Eternal,1);run.collectHeart(HeartKind::Golden,1);run.addBrokenHearts(1);
    run.grant(ItemId::Ricochet);const auto souls=run.player.soulHearts,bones=run.player.boneHearts;
    run.floorExitRequested=true;check(run.advanceFloor(),"next floor available");
    check(run.player.maxHp==8&&run.player.hp==5&&run.player.eternalHearts==0,"eternal floor conversion adds and fills one container only");
    check(run.player.soulHearts==souls&&run.player.boneHearts==bones&&run.player.brokenHearts==1&&run.player.goldenHearts==1,
        "typed layers and overlays persist between floors");
    check(run.itemStacks(ItemId::Ricochet)==1&&run.player.shotDamage==24,"inventory and unselected outgoing damage persist");
}
}
int main(){try{survival();layers();pickupsAndEffects();upgradesAndRevival();floorTravel();std::cout<<"PASS H02–H18 health gameplay integration\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
