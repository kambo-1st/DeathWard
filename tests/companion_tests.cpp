#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include "items/ItemPools.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
const auto shadow=parseItemKey("isaac:collectible:433");
void check(bool ok,const char *text){if(!ok)throw std::runtime_error(text);}
bool near(float a,float b){return std::abs(a-b)<.002f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.rebuildWalls();for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    for(auto &r:s.rooms){r.residents.clear();r.cleared=false;}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.moneyPickups.clear();s.stats={};
    s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,8};return s;
}
void ticks(Simulation &s,int count){for(int n=0;n<count;++n)s.step({});}
EntityId ally(Simulation &s,Vector3 p={0,.85f,0}) {
    const auto id=s.spawnMonster(monsterId(23,0,1),p);auto *e=s.findEnemy(id);
    e->cooldown=0;e->auxiliary=10;e->facing={1,0,0};return id;
}
EntityId enemy(Simulation &s,Vector3 p,float hp=1000,MonsterId type=monsterId(10,1)) {
    const auto id=s.spawnMonster(type,p);auto *e=s.findEnemy(id);
    e->hp=e->maxHp=hp;e->state=EnemyState::Stunned;e->stateTime=100;return id;
}
size_t allies(const Simulation &s){return std::count_if(s.enemies.begin(),s.enemies.end(),[](const auto &e){return e.alive&&e.friendly;});}
void producer() {
    auto s=fixture();s.player.position={0,.85f,0};s.godMode=true;
    const auto target=enemy(s,{1.18f,.85f,0},100000);
    ticks(s,1);check(s.familiars.empty()&&allies(s)==0,"No item means no familiar or ally");
    s.grant(shadow);s.grant(shadow);ticks(s,1);
    check(s.familiars.size()==1&&allies(s)==1,"Duplicate copies retain one contact producer");
    check(s.player.maxHp==100&&s.player.shotDamage==24,"Shadow pickup preserves character defaults");
    const auto familiar=s.familiars[0].id;
    for(int n=0;n<360;++n) {
        int i=0;for(auto &e:s.enemies)if(e.friendly){e.position={-16+float(i%4)*3,.85f,-16+float(i/4)*3};e.state=EnemyState::Stunned;e.stateTime=100;++i;}
        s.findEnemy(target)->position={1.18f,.85f,0};ticks(s,1);
        check(allies(s)<=16,"Live plus pending population never exceeds source cap");
    }
    check(allies(s)==16,"Repeated contact can reach the sixteen-ally cap");
    for(const auto &e:s.enemies)if(e.friendly)
        check(e.summoner==familiar&&e.companionItem==shadow&&e.monster==monsterId(23,0,1),"Spawn retains producer/item/exact subtype ownership");
    s.items.clear();ticks(s,1);check(s.familiars.empty()&&allies(s)==16,"Removing producer stops spawning without killing existing room allies");
    std::cout<<"SHADOW_PRODUCER duplicate_once=1 max_live=16 item_owner=1 removal_stops_only_producer=1\n";
}
void delayedPath() {
    auto s=fixture();s.grant(shadow);s.player.position={0,.85f,0};ticks(s,1);
    for(int n=0;n<30;++n){Input in;in.movement={1,0,0};s.step(in);}
    check(s.familiars.size()==1&&s.player.position.x-s.familiars[0].position.x>.5f,"Familiar follows delayed movement, not current position");
    const auto stop=s.player.position;ticks(s,20);
    check(distance(s.familiars[0].position,stop)<.01f,"Delayed shadow catches up when the player stops");
    check(s.familiars[0].trail.size()<=256,"Timed history stays bounded");
    std::cout<<"SHADOW_PATH lag=1 catch_up=1 bounded_history=1\n";
}
void chargeAndContact() {
    auto s=fixture();const auto id=ally(s);ticks(s,1);
    check(s.findEnemy(id)->state==EnemyState::Ready,"Ally never acquires an aligned player");
    s.findEnemy(id)->position={0,.85f,0};s.findEnemy(id)->cooldown=0;
    enemy(s,{2,.85f,2});const auto target=enemy(s,{8,.85f,0});ticks(s,1);
    check(s.findEnemy(id)->state==EnemyState::Charging&&s.findEnemy(id)->facing.x>.99f&&s.findEnemy(id)->partner==target,
        "Aligned hostile is acquired even with a nearer unaligned enemy");
    s=fixture();const auto friendly=ally(s);const auto hostile=enemy(s,{2,.85f,0});
    ticks(s,12);check(s.findEnemy(hostile)->hp<1000&&s.findEnemy(friendly)->hp<64,"Contact harms both sides");
    check(near(s.findEnemy(hostile)->hp,972.16f)&&near(s.findEnemy(friendly)->hp,60.8f),"Independent allied and hostile contact conversions");
    check(s.player.hp==100&&near(s.stats.damageDealt,27.84f),"Ally damage is not player damage or damage-dealt credit");
    std::cout<<"SHADOW_CONTACT enemy_damage=27.84 ally_damage=3.2 player_damage=0 cardinal_target=1\n";
}
void incoming() {
    auto s=fixture();const auto id=ally(s);s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=100;
    Event blast;blast.type=EventType::Explosion;blast.position={0,.85f,0};blast.damage=200;blast.radius=4;
    s.queueRoot(blast);s.drainEvents();check(s.findEnemy(id)->hp==64,"Ordinary player blast cannot hurt allied Charger");
    Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=10;hit.hostile=true;
    s.queueRoot(hit);s.drainEvents();check(near(s.findEnemy(id)->hp,60.8f),"Hostile damage reaches ally");
    s.queueRoot(hit);s.drainEvents();check(near(s.findEnemy(id)->hp,60.8f),"Shared hurt window prevents same-tick multi-hit");
    ticks(s,30);blast.hostile=true;s.queueRoot(blast);s.drainEvents();check(!s.findEnemy(id)->alive,"Hostile explosion can kill ally");
    check(s.stats.kills==0&&s.stats.damageDealt==0&&s.moneyPickups.empty(),"Ally death has no ordinary kill, damage credit or loot");
    s=fixture();const auto flameAlly=ally(s);s.findEnemy(flameAlly)->state=EnemyState::Stunned;s.findEnemy(flameAlly)->stateTime=100;
    s.addFire({0,.85f,0},1,.2f,10,false,false);ticks(s,15);
    check(s.findEnemy(flameAlly)->hp==64,"Explicitly harmless flame does not damage companions");
    s.addFire({0,.85f,0},1,3,10,false,true);ticks(s,75);
    check(near(s.findEnemy(flameAlly)->hp,54.4f),"Environmental flame repeatedly damages companion even with hostile-monster damage disabled");
    s=fixture();const auto beamAlly=ally(s);s.findEnemy(beamAlly)->state=EnemyState::Stunned;s.findEnemy(beamAlly)->stateTime=100;
    Hazard beam;beam.kind=HazardKind::Beam;beam.origin={-5,.85f,0};beam.position={5,.85f,0};beam.delay=0;beam.duration=1;beam.radius=.2f;beam.damage=10;
    s.hazards.push_back(beam);ticks(s,1);check(near(s.findEnemy(beamAlly)->hp,60.8f),"Enemy beam can damage a companion");
    std::cout<<"SHADOW_DAMAGE player_bomb_immune=1 hostile_blast=1 repeated_fire=1 beam=1 no_death_rewards=1\n";
}
void projectilesAndRewards() {
    auto s=fixture();s.player.position={0,.85f,5};const auto id=ally(s);
    s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=100;
    Event shot;shot.position=shot.origin={0,.85f,-5};shot.direction={0,0,1};shot.damage=10;shot.speed=10;shot.hostile=true;
    s.queueRoot(shot);s.drainEvents();ticks(s,35);
    check(near(s.findEnemy(id)->hp,60.8f)&&s.player.hp==100&&s.projectiles.empty(),"Ally intercepts nearest hostile shot before player");
    s=fixture();const auto explosiveAlly=ally(s);s.findEnemy(explosiveAlly)->state=EnemyState::Stunned;s.findEnemy(explosiveAlly)->stateTime=100;
    auto explosive=shot;explosive.position=explosive.origin={0,.85f,-2};explosive.damage=1000;
    explosive.projectileKind=ProjectileKind::Ipecac;explosive.projectileBlastRadius=2;explosive.projectileBlastDamage=20;
    s.queueRoot(explosive);s.drainEvents();ticks(s,15);
    check(s.findEnemy(explosiveAlly)&&near(s.findEnemy(explosiveAlly)->hp,57.6f)&&s.stats.explosions==1,
        "Explosive impact applies one blast, not a direct hit that consumes the hurt window");
    s=fixture();const auto friendId=ally(s);s.findEnemy(friendId)->state=EnemyState::Stunned;s.findEnemy(friendId)->stateTime=100;
    const auto foe=enemy(s,{0,.85f,4});shot.hostile=false;shot.attack=AttackSpec{};shot.attack->speed=20;shot.damage=24;
    s.queueRoot(shot);s.drainEvents();ticks(s,30);
    check(s.findEnemy(friendId)->hp==64&&s.findEnemy(foe)->hp==976,"Player shot passes through ally and hits hostile");
    s.grant(ItemId::Powder);s.grant(ItemId::Ghost);s.drainEvents();const auto explosions=s.stats.explosions,ghosts=s.stats.ghosts;
    Event kill;kill.type=EventType::Damage;kill.target=friendId;kill.damage=10000;kill.execution=true;s.queueRoot(kill);s.drainEvents();
    check(s.stats.kills==0&&s.stats.explosions==explosions&&s.stats.ghosts==ghosts,"Companion death does not dispatch hostile kill hooks");
    std::cout<<"SHADOW_PROJECTILES hostile_interception=1 player_pass_through=1 kill_hook_isolation=1\n";
}
void roomLifetime() {
    auto s=fixture();const auto id=ally(s);s.grant(shadow);ticks(s,1);const auto kills=s.stats.kills;
    s.enterRoom(1);check(s.familiars.empty()&&s.stats.kills==kills,"Room transition expires familiar without a kill");
    for(const auto &r:s.rooms)for(const auto &e:r.residents)check(e.id!=id,"Room-limited ally is not stored for re-entry");
    s.enterRoom(0);check(allies(s)==0,"Room re-entry cannot resurrect an expired ally");
    s=fixture();ally(s);s.debugScenario=false;s.rooms[0].cleared=false;ticks(s,1);
    check(s.roomClear&&s.roomThreats()==0&&allies(s)==1,"Living allies do not keep room doors sealed");
    std::cout<<"SHADOW_LIFETIME transition_expiry=1 no_resurrection=1 room_clear=1\n";
}
void seededBargain() {
    check(itemPoolWeight(ItemPool::Bargain,shadow)>0&&itemPoolWeight(ItemPool::Armory,shadow)==0&&
        itemPoolWeight(ItemPool::Shop,shadow)==0&&itemPoolWeight(ItemPool::Boss,shadow)==0,"Source Devil pool maps only to local bargain");
    bool found=false;
    for(uint64_t seed=0;seed<80&&!found;++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke);
        for(int room=0;room<s.arena.roomCount()&&!found;++room) {
            if(s.arena.rooms[size_t(room)].service!=RoomService::Smuggler)continue;
            for(int slot=0;slot<2;++slot)if(s.rooms[size_t(room)].offers[size_t(slot)]==shadow) {
                s.enterRoom(room);s.player.position=s.arena.rooms[size_t(room)].objective;s.openShop();
                check(s.buyShop(slot)&&s.itemStacks(shadow)==1,"Actual seeded bargain can acquire My Shadow");
                s.closeShop();s.step({});check(s.familiars.size()==1,"Acquired item actually creates its producer");
                std::cout<<"SHADOW_BARGAIN seed="<<seed<<" floor=0 room="<<room<<" slot="<<slot<<" hp="<<s.player.maxHp<<'\n';
                found=true;break;
            }
        }
    }
    check(found,"My Shadow must be reachable in seeded normal expedition trade");
}
void floorAndJournal() {
    Simulation s(3,1,{},MissionTheme::Canyon);
    s.grant(shadow);s.startBoss();s.killAll();s.step({});
    ally(s,s.player.position);s.step({});
    check(allies(s)==1&&s.familiars.size()==1,"Floor-exit fixture has a live ally and producer");
    const auto fingerprint=s.content->fingerprint();
    s.floorExitRequested=true;check(s.advanceFloor(),"A companion does not prevent floor advancement");
    check(s.floor==1&&s.itemStacks(shadow)==1&&s.player.maxHp==100&&s.player.shotDamage==24,
        "Namespaced item and character defaults survive floor transition");
    check(allies(s)==0&&s.familiars.empty()&&s.content->fingerprint()==fingerprint,
        "Floor transition expires room actors while preserving the mechanics snapshot");
    s.step({});check(s.familiars.size()==1&&distance(s.familiars[0].position,s.player.position)<.01f,
        "Next floor creates a fresh producer at the new entrance without old path history");
    struct Journal {
        std::filesystem::path path=std::filesystem::temp_directory_path()/
            ("deathward-shadow-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".save");
        ~Journal(){std::error_code error;std::filesystem::remove(path,error);}
    } journal;
    CampaignStore store(journal.path);auto summary=s.summary();summary.id=store.begin(3,summary.expedition);
    store.checkpoint(summary);CampaignStore reloaded(journal.path);
    check(reloaded.data().pending&&reloaded.data().pending->items==s.items&&
        reloaded.data().pending->mechanicsFingerprint==fingerprint&&reloaded.data().pending->floor==1,
        "Real My Shadow key, floor and content fingerprint survive the existing summary journal");
    std::cout<<"SHADOW_PERSISTENCE floor_carry=1 expired_allies=1 fresh_producer=1 journal_item=1\n";
}
}
int main(){try{producer();delayedPath();chargeAndContact();incoming();projectilesAndRewards();roomLifetime();seededBargain();floorAndJournal();
    std::cout<<"PASS My Shadow producer, allied combat and room lifetime\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
