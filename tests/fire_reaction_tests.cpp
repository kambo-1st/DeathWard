#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.002f;}
Simulation fixture() {
    Simulation s(1866,1,{});s.enemies.clear();s.arena=Arena{};
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;}
    s.rooms.assign(s.arena.rooms.size(),{});s.room=0;s.player.position={15,.85f,15};
    s.godMode=true;s.debugScenario=true;s.roomClear=false;return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float amount,DamageKind kind=DamageKind::Physical,bool execute=false) {
    Event event;event.type=EventType::Damage;event.target=id;event.damage=amount;
    event.damageKind=kind;event.execution=execute;s.queueRoot(event);s.drainEvents();
}
void identityAndHealth() {
    for(auto kind:{DamageKind::Flame,DamageKind::Burning}) {
        auto s=fixture();auto id=s.spawnMonster(monsterId(15),{0,.85f,0});
        auto *e=s.findEnemy(id);e->summoner=1234;hit(s,id,20);e->cooldown=0;tick(s);
        check(e->state==EnemyState::Windup,"fixture starts a committed Clotty attack");
        const auto at=e->position;const auto damage=s.stats.damageDealt;const auto money=s.moneyPickups.size();
        hit(s,id,1000,kind);e=s.findEnemy(id);
        check(e->alive&&e->monster==monsterId(15,3)&&e->id==id&&e->summoner==1234,"ignition changes body identity in place, retaining ownership");
        check(near(e->hp,72)&&near(e->maxHp,96),"explicit fraction policy preserves damaged health proportion");
        check(distance(e->position,at)<.001f&&near(e->radius,.6f),"same source collision radius preserves physical placement");
        check(e->state==EnemyState::Ready&&!e->behavior.initialized&&s.stats.kills==0&&s.stats.damageDealt==damage&&s.moneyPickups.size()==money,"ignition cancels old attack without kill/reward/damage credit");
        hit(s,id,999,DamageKind::Flame);hit(s,id,999,DamageKind::Burning);
        check(near(e->hp,72),"dry flaming Clotty remains fire immune on later contacts");
        hit(s,id,12);check(near(e->hp,60),"fire immunity does not block physical shots");
        s.enterRoom(1);tick(s,5);s.enterRoom(0);
        check(s.findEnemy(id)->monster==monsterId(15,3)&&near(s.findEnemy(id)->hp,60),"transformed identity and health survive re-entry");
        hit(s,id,1000,DamageKind::Flame,true);check(!s.findEnemy(id)->alive,"execution bypasses immunity and does not transform");
    }
    auto s=fixture();const auto id=s.spawnMonster(monsterId(15),{0,.85f,0});
    auto *e=s.findEnemy(id);e->friendly=true;e->hp=e->maxHp=40;e->state=EnemyState::Stunned;e->stateTime=1;
    hit(s,id,0,DamageKind::Flame);
    check(e->friendly&&near(e->hp,48)&&near(e->maxHp,48)&&e->state==EnemyState::Stunned&&near(e->stateTime,1),"scaled health, team and stun survive in-place transformation");
    std::cout<<"FIRE_TRANSFORM fraction=1 identity=1 owner=1 team=1 stun=1 no_reward=1 reentry=1\n";
}
void floodedRoom() {
    auto s=fixture();s.arena.rooms[0].flooded=true;
    const auto id=s.spawnMonster(monsterId(15),{0,.85f,0});hit(s,id,10,DamageKind::Flame);
    check(s.findEnemy(id)->monster==monsterId(15)&&near(s.findEnemy(id)->hp,70),"flooded Clotty takes fire damage and does not transform");
    hit(s,id,20,DamageKind::Burning);check(near(s.findEnemy(id)->hp,50),"flooded condition also removes burning immunity");
    s.debugScenario=false;hit(s,id,1000,DamageKind::Flame);tick(s);
    check(s.roomClear&&s.stats.kills==1&&s.roomThreats()==0,"lethal flooded fire follows actual death/completion path");
    s=fixture();s.arena.rooms[0].flooded=true;const auto first=s.spawnMonster(monsterId(15),{0,.85f,0});
    s.enterRoom(1);const auto second=s.spawnMonster(monsterId(15),{0,.85f,0});hit(s,second,10,DamageKind::Flame);
    check(s.findEnemy(second)->monster==monsterId(15,3),"flooded condition is local to its room");
    s.enterRoom(0);hit(s,first,10,DamageKind::Flame);check(s.findEnemy(first)->monster==monsterId(15),"room re-entry retains flooded condition");
    std::cout<<"FLOODED disables_transform=1 enables_fire_damage=1 local_room=1 actual_clear=1\n";
}
void hopperDistinction() {
    auto s=fixture();const auto id=s.spawnMonster(monsterId(29),{0,.85f,0});
    hit(s,id,12,DamageKind::Burning);check(s.findEnemy(id)->monster==monsterId(29)&&near(s.findEnemy(id)->hp,20),"burning damage alone is not Hopper flame contact");
    s.arena.rooms[0].flooded=true;hit(s,id,1000,DamageKind::Flame);
    check(s.findEnemy(id)->monster==monsterId(54)&&near(s.findEnemy(id)->hp,40)&&near(s.findEnemy(id)->maxHp,64),"Hopper flame transform updates stats and has no invented flooding exception");
    hit(s,id,12,DamageKind::Burning);check(near(s.findEnemy(id)->hp,28),"Flaming Hopper still takes burning-status damage");
    hit(s,id,1000,DamageKind::Flame);check(near(s.findEnemy(id)->hp,28),"Flaming Hopper survives actual flame contact");
    auto friendRun=fixture();const auto ally=friendRun.spawnMonster(monsterId(29),{0,.85f,0});
    const auto foe=friendRun.spawnMonster(monsterId(12),{4,.85f,0});
    friendRun.findEnemy(ally)->friendly=true;tick(friendRun);
    check(friendRun.findEnemy(ally)->partner==foe,"legacy friendly Hopper stores its attack target separately from summoner");
    hit(friendRun,ally,0,DamageKind::Flame);
    check(friendRun.findEnemy(ally)->monster==monsterId(54)&&friendRun.findEnemy(ally)->friendly&&friendRun.findEnemy(ally)->partner==foe,
          "friendly attack target is retained and must not be mistaken for a multipart owner");
    std::cout<<"HOPPER flame_transforms=1 burning_damages=1 no_flood_exception=1\n";
}
void projectileChannel() {
    auto s=fixture();const auto id=s.spawnMonster(monsterId(15),{0,.85f,0});
    Event shot;shot.position=shot.origin={-4,.85f,0};shot.direction={1,0,0};shot.speed=50;
    shot.damage=1000;shot.damageKind=DamageKind::Flame;s.queueRoot(shot);s.drainEvents();tick(s,8);
    check(s.findEnemy(id)&&s.findEnemy(id)->monster==monsterId(15,3)&&near(s.findEnemy(id)->hp,96),
          "typed fire survives projectile creation, travel, hit and queued damage event");
    std::cout<<"FIRE_PROJECTILE channel_preserved=1\n";
}
void realHazards() {
    auto s=fixture();const auto clotty=s.spawnMonster(monsterId(15),{0,.85f,0});
    s.addFire({0,.85f,0},1.2f,6,10,true,false);tick(s);
    check(s.findEnemy(clotty)->monster==monsterId(15,3)&&near(s.findEnemy(clotty)->hp,96),"live flame hazard drives transformation");
    auto cover=fixture();const auto behind=cover.spawnMonster(monsterId(15),{1,.85f,0});
    cover.arena.obstacles.push_back({{-.15f,0,-3},{.15f,4,3}});cover.arena.rebuildWalls();
    cover.addFire({-1,.85f,0},3,6,10,true,false);tick(cover);
    check(cover.findEnemy(behind)->monster==monsterId(15),"fire exposure cannot pass through cover");
    auto air=fixture();const auto above=air.spawnMonster(monsterId(15),{0,5,0});
    // Freeze this controlled elevated body; normal ground navigation snaps a
    // walking ground actor back to its floor and would not test vertical reach.
    air.findEnemy(above)->position.y=5; // Ground spawning itself also normalizes y.
    air.findEnemy(above)->state=EnemyState::Stunned;air.findEnemy(above)->stateTime=1;
    air.addFire({0,.85f,0},3,6,10,true,false);tick(air);
    check(near(air.findEnemy(above)->position.y,5)&&air.findEnemy(above)->monster==monsterId(15),"ground fire does not ignite bodies above its vertical reach");
    auto delayed=fixture();const auto waiting=delayed.spawnMonster(monsterId(15),{0,.85f,0});
    delayed.addFire({0,.85f,0},3,1,10,true,false);delayed.hazards.back().delay=2;tick(delayed,30);
    check(delayed.findEnemy(waiting)->monster==monsterId(15),"unlit warning cannot ignite");
    delayed.hazards.back().age=3;tick(delayed);
    check(delayed.findEnemy(waiting)->monster==monsterId(15)&&delayed.hazards.empty(),"expired fire cannot ignite on its cleanup tick");
    auto overlaps=fixture();const auto horf=overlaps.spawnMonster(monsterId(12),{0,.85f,0});
    const auto initialHorfHp=overlaps.findEnemy(horf)->hp;
    for(int n=0;n<3;++n)overlaps.addFire({0,.85f,0},2,6,10,true,false);
    tick(overlaps);check(near(overlaps.findEnemy(horf)->hp,initialHorfHp-10),"overlapping fire applies one damage pulse");
    tick(overlaps,20);check(near(overlaps.findEnemy(horf)->hp,initialHorfHp-10),"contact pulse is bounded by target cooldown");
    tick(overlaps,15);check(near(overlaps.findEnemy(horf)->hp,initialHorfHp-20),"sustained contact emits a later bounded pulse");
    auto hostile=fixture();const auto actor=hostile.spawnMonster(monsterId(12),{0,.85f,0});
    const auto actorHp=hostile.findEnemy(actor)->hp;
    const auto native=hostile.spawn(EnemyKind::Gunman,{0,.85f,0});const auto nativeHp=hostile.findEnemy(native)->hp;
    hostile.addFire({0,.85f,0},3,6,10,false,true);tick(hostile);
    check(near(hostile.findEnemy(actor)->hp,actorHp)&&near(hostile.findEnemy(native)->hp,nativeHp),"ordinary hostile patches preserve native-enemy friendly-fire behavior");
    auto reactive=fixture();const auto hopper=reactive.spawnMonster(monsterId(29),{0,.85f,0});
    reactive.addFire({0,.85f,0},2,6,10,false,true);tick(reactive);
    check(reactive.findEnemy(hopper)->monster==monsterId(54),"hostile patches still expose known reactive bodies to contact");
    s.limits.hazards=s.hazards.size();s.addFire({0,.85f,0},1,2,10,true,false);check(s.stats.suppressed>0,"fire uses existing global hazard capacity");
    s.clearRoomDebug();check(s.hazards.empty()&&s.chains.empty(),"fire and transformation effects clean up with room debug clear");
    std::cout<<"FIRE_HAZARDS real_contacts=1 cover=1 height=1 lifetime=1 overlap_bound=1 mine_unchanged=1\n";
}
}
int main(){try{identityAndHealth();floodedRoom();hopperDistinction();projectileChannel();realHazards();std::cout<<"PASS monster fire reactions\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
