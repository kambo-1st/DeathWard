#include "items/Items.hpp"
#include "items/SadOnion.hpp"
#include "core/BalancePreset.hpp"
#include "combat/SourceRoomRewards.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
void near(float a,float b,const char *message){if(std::abs(a-b)>.00005f)throw std::runtime_error(message);}
Simulation make(uint64_t seed=1,float size=1.1f,int lo=7,int hi=9){auto s=Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),size,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1);s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);s.player.attributes.shotSpeed=.9f;return s;}
void native() {
    auto s=make();std::ifstream in(Root/"docs/reports/isaac-first-floor-parity/pw-t02-whip-worm/source/native-shot-speed.csv");std::string line;std::getline(in,line);int cases=0;
    while(std::getline(in,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float base,before,after;int held;check(bool(row>>base>>held>>before>>after),"Native speed row");s.player.attributes.shotSpeed=base;s.heldTrinket=held?std::optional{ItemKey{"isaac",ItemKind::Trinket,uint32_t(held)}}:std::nullopt;near(s.effectivePlayerStats().shotSpeed,before,"Actual held query composition matches native before global floor");if(base>=.6f)near(s.effectivePlayerStats().shotSpeed,after,"Native ordinary final speed");++cases;}
    check(cases==24,"All native arithmetic cases");std::ifstream pair(Root/"docs/reports/isaac-first-floor-parity/pw-t02-whip-worm/source/native-pair.csv");std::getline(pair,line);int draws=0;
    while(std::getline(pair,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);uint32_t seed;int id;check(bool(row>>seed>>id)&&sourceSupportedTrinket(seed)==id,"Native supplied pair draw");++draws;}
    check(draws==8,"All pair factory cases");std::cout<<"PASS 24 native Whip cache cases and 8 native pair draws\n";
}
void lifecycle() {
    auto s=make();check(s.beginTrinketReview()&&s.items.empty()&&!s.heldTrinket&&s.trinketPickups.size()==2,"Labelled pair, no ownership grant");
    const auto start=s.player.position,cancer=s.trinketPickups[0].position,whip=s.trinketPickups[1].position;
    s.grant({"isaac",ItemKind::Collectible,1});s.grant({"isaac",ItemKind::Collectible,4});s.grant({"isaac",ItemKind::Collectible,8});s.grant(YumHeartKey);s.activeItem->charge=2;s.step({});
    const auto items=s.items;const auto cadence=primaryCadence(s);const auto base=primaryPlayerAttack(s,s.player.shotDamage,false);const auto stats=s.effectivePlayerStats();
    s.player.position=cancer;s.step({});check(s.heldTrinket==CancerKey&&primaryCadence(s)<cadence,"Cancer ordinary acquisition");
    s.player.position=start;for(int i=0;i<40;++i)s.step({});s.player.position=whip;s.step({});
    check(s.heldTrinket==WhipWormKey&&s.itemStacks(WhipWormKey)==0&&s.items==items&&s.activeItem->charge==2&&s.brotherBobbies.size()==1,"Different trinket actual swap preserves other categories");
    const auto shot=primaryPlayerAttack(s,s.player.shotDamage,false);near(shot.speed/base.speed,1.4f/.9f,"Primary launch speed consumes Whip");near(primaryCadence(s),cadence,"Cancer removed on swap");
    check(shot.maxDistance==base.maxDistance&&shot.damage==base.damage&&shot.radius==base.radius&&shot.life<base.life,"Faster travel, same damage/size/distance; shorter flight");
    check(s.effectivePlayerStats().rangeTiles==stats.rangeTiles&&s.effectivePlayerStats().tearsPerSecond==stats.tearsPerSecond,"Range and Tears independent");
    Event e;e.type=EventType::Shot;e.position=s.player.position;e.direction={1,0,0};e.damage=shot.damage;e.attack=shot;s.queueRoot(e);s.drainEvents();check(!s.projectiles.empty(),"Actual emitted Whip projectile");const auto born=s.projectiles.back().attack;
    s.player.fireCooldown=.31f;s.trinkets.whipStrength=.5f;near(s.effectivePlayerStats().shotSpeed,1.15f,"Live half strength");check(s.player.fireCooldown==.31f&&s.projectiles.back().attack.speed==born.speed&&s.projectiles.back().attack.maxDistance==born.maxDistance,"Edit keeps committed wait and emitted birth");
    s.trinkets.whipStrength=1;for(int i=0;i<90;++i)s.step({});check(s.heldTrinket==WhipWormKey&&s.trinketPickups.size()==1&&s.trinketPickups.front().item==CancerKey,"Outgoing Cancer remains without instant swap-back");
    s.player.position=start;s.step({});s.player.position=whip;s.step({});check(s.heldTrinket==CancerKey&&s.trinketPickups.front().item==WhipWormKey,"Swap back preserves outgoing Whip");near(primaryPlayerAttack(s,s.player.shotDamage,false).speed,base.speed,"Whip effect removed exactly");
    s.player.position=start;for(int i=0;i<90;++i)s.step({});s.player.position=whip;s.step({});check(s.heldTrinket==WhipWormKey,"Swap again");
    s.grant(WhipWormKey);check(s.items==items&&s.itemStacks(WhipWormKey)==0,"No duplicate permanent ownership");
    check(s.dropTrinket()&&!s.heldTrinket,"Drop Whip");near(s.effectivePlayerStats().shotSpeed,.9f,"Drop restores baseline");const auto dropped=s.trinketPickups.back().position;
    s.player.position=start;for(int i=0;i<90;++i)s.step({});s.player.position=dropped;s.step({});check(s.heldTrinket==WhipWormKey,"Recollect dropped Whip");
    s.jumpDebug(1);s.jumpDebug(0);check(s.heldTrinket==WhipWormKey,"Revisit keeps held slot");s.trinkets.whipStrength=.75f;s.resizeRooms(1.11f,7,9,.26f);check(s.heldTrinket==WhipWormKey&&s.trinkets.whipStrength==.75f&&s.trinketPickups.empty(),"Apply retains held item/config, resets actors");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor()&&s.heldTrinket==WhipWormKey&&s.trinkets.whipStrength==.75f,"Next floor retains effect");
    std::cout<<"PASS actual attacks, Cancer/Whip swaps/drop/recollect, other categories and floor/Apply lifecycle\n";
}
std::pair<int,int> witness() {
    for(int seed=1;seed<=40;++seed){auto s=make(seed);for(int room=1;room<s.finalRoom();++room){s.jumpDebug(room);if(s.roomClear||!s.roomThreats())continue;s.clearRoomDebug();const auto &a=s.rooms[size_t(room)].redHeartAward;if(a&&a->variant==350&&a->subtype==27&&a->delivered){std::cout<<"WHIP_WITNESS seed="<<seed<<" room="<<room+1<<" pickup_seed="<<a->pickupSeed<<'\n';return {seed,room};}}}
    throw std::runtime_error("No Whip witness");
}
void producer() {
    const auto [seed,room]=witness();
    for(auto shape:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}}){auto [scale,lo,hi]=shape;auto pair=make(seed,scale,lo,hi);check(pair.beginTrinketReview()&&pair.trinketPickups.size()==2,"Reachable review pair across sizes");for(const auto &p:pair.trinketPickups)check(!pair.arena.blocked(p.position,.48f)&&!pair.arena.path(pair.player.position,p.position,.48f).empty(),"Pair physically reachable");auto s=make(seed,scale,lo,hi);s.jumpDebug(room);s.clearRoomDebug();check(s.trinketPickups.size()==1&&s.trinketPickups.front().item==WhipWormKey,"Natural Whip actor across sizes");check(!s.arena.path(s.player.position,s.trinketPickups.front().position,.48f).empty(),"Natural placement reachable");s.clearRoom();check(s.trinketPickups.size()==1,"No duplicate clear payment");}
    auto s=make(seed);s.jumpDebug(room);s.trinketPickups.resize(1024);s.clearRoomDebug();const auto identity=s.rooms[size_t(room)].redHeartAward;check(identity&&identity->pending&&identity->subtype==27,"Pending Whip identity");s.trinkets.clearRewards=false;s.trinkets.whipStrength=0;s.trinketPickups.clear();s.step({});check(s.trinketPickups.size()==1&&s.trinketPickups.front().item==WhipWormKey&&s.trinketPickups.front().seed==identity->pickupSeed,"Pending birth not rerolled by live edits");
    std::cout<<"PASS natural Whip producer, three sizes, capacity and immutable pending identity\n";
}
void persistence() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-whip-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    const auto fp=defaultMechanics()->fingerprint();check(fp=="112a252173ba98d0","Audited additive content hash including Screw and Full Fly");
    for(const auto file:{"d03-shooting/user-preset-2026-11-11.json","pw-t01-cancer/cancer-preset.json","pw-c01-category-check/combined-preset.json"}){const auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity"/file,fp);check(p.defaultZoomPercent==165&&p.trinkets.whipStrength==1,"Old schema preserves accepted view, adds baseline Whip");}
    BalancePreset p{1,fp};p.trinkets={.75f,false,1,1.35f};p.save(dir/"preset.json");check(BalancePreset::load(dir/"preset.json",fp).json()==p.json(),"Exact independent trinket roundtrip");
    auto bad=p.json();auto pos=bad.find("\"whip_strength\": 1.35");check(pos!=bad.npos,"Custom strength field");bad.replace(pos,21,"\"whip_strength\": 3.35");std::ofstream(dir/"bad.json")<<bad;bool rejected=false;try{BalancePreset::load(dir/"bad.json",fp);}catch(...){rejected=true;}check(rejected,"Invalid strength rejected atomically");
    auto s=make();s.grant(WhipWormKey);s.grant(YumHeartKey);s.activeItem->charge=2;{CampaignStore c(dir/"campaign.save");const auto id=c.begin(1);auto record=s.summary();record.id=id;c.checkpoint(record);}
    CampaignStore c(dir/"campaign.save");check(c.data().pending->heldTrinket==WhipWormKey&&c.data().pending->activeItem==s.activeItem,"Version10 Whip checkpoint");c.recover();check(c.data().history.back().heldTrinket==WhipWormKey,"Interrupted history preserves Whip");
    std::filesystem::remove_all(dir);std::cout<<"PASS schema5/39 to41 migration, exact custom roundtrip and campaign10 Whip history\n";
}
}
int main(int argc,char **){try{if(argc>1){witness();return 0;}native();lifecycle();producer();persistence();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
