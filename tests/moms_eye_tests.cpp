#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "items/MomsEye.hpp"
#include "items/Items.hpp"
#include "world/PedestalGeometry.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
using namespace dw;
namespace {
const ItemKey Eye{"isaac",ItemKind::Collectible,55};
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void native() {
    std::ifstream f(Root/"docs/reports/isaac-first-floor-parity/d14a7-moms-eye/source/native-gate.csv");check(bool(f),"native cases exist");
    std::string line;std::getline(f,line);int count=0;
    while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int copies,expected,draws;float luck;uint32_t word;in>>copies>>luck>>word>>expected>>draws;
        check(bool(copies&&momsEyeBackward(luck,word))==bool(expected),"native strict single-precision Luck gate");++count;}
    check(count==632,"all native cases compared");std::cout<<"PASS 632 native Luck/ownership gate comparisons\n";
}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Mine,false);s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.player.position={0,.85f,0};
    s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);s.player.attributes.luck=20;return s;
}
void shots() {
    for(int copies:{0,1,2})for(int direction=0;direction<8;++direction) {
        auto s=fixture();for(int i=0;i<copies;++i)s.grant(Eye);
        const auto aim=rotateY({1,0,0},direction*Pi/4);Input in;in.fire=true;in.aim=add(s.player.position,mul(aim,30));s.step(in);
        check(s.projectiles.size()==size_t(copies?2:1)&&s.stats.shots==1&&s.player.nextRound==2,"one extra shot, one trigger/cylinder advancement; copies do not multiply");
        const auto &front=s.projectiles[0];check(dot(unit(horizontal(front.velocity)),aim)>.999f,"forward aim retained in all eight directions");
        if(copies) {const auto &rear=s.projectiles[1];check(dot(unit(horizontal(rear.velocity)),aim)<-.999f,"opposite planar heading");
            check(front.damage==rear.damage&&front.attack.speed==rear.attack.speed&&front.attack.maxDistance==rear.attack.maxDistance&&front.attack.radius==rear.attack.radius,"damage/speed/range/size copied from resolved ordinary shot");}
        const auto cooldown=s.player.fireCooldown;s.momsEyeChanceMultiplier=0;check(s.player.fireCooldown==cooldown,"live chance edit does not reset firing wait");
        if(copies)check(s.projectiles.size()==2,"live edit retains emitted shots");
    }
    auto s=fixture();s.grant(Eye);s.player.attributes.luck=0;s.momsEyeChanceMultiplier=0;Input in;in.fire=true;in.aim={30,.85f,0};s.step(in);check(s.projectiles.size()==1,"zero chance override affects new volley");
    // Real backward projectile damage at the retained canonical damage value.
    auto hit=fixture();hit.grant(Eye);const auto victim=hit.spawnMonster(monsterId(10,1),{-3,.85f,0});const auto hp=hit.findEnemy(victim)->hp;
    hit.step(in);for(int n=0;n<90&&hit.findEnemy(victim)->hp==hp;++n)hit.step({});
    check(hit.findEnemy(victim)->hp<hp&&std::abs(hp-hit.findEnemy(victim)->hp-11.2f)<.001f,"rear shot uses real collision/damage path once");
    std::cout<<"PASS eight-direction actual volleys, no-copy/copy gates, snapshot/cadence and rear hit\n";
}
Simulation generated(uint64_t seed,float scale,int lo,int hi,int mode=7,int floor=0,int layouts=1) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,layouts,true,true,true,true,true,true,1,mode);
}
void room(uint64_t seed,float scale,int lo,int hi) {
    auto s=generated(seed,scale,lo,hi);check(s.enterSourceRoomReview(4000006),"real recorded treasure room available");const int index=s.room;const auto &r=s.arena.rooms[size_t(index)];
    check(r.kind==RoomKind::Power&&r.sourceTreasureTemplate==6&&s.treasureUpgradeItem(index)==55&&s.roomThreats()==0&&s.player.hp==6,"treasure role, Mom's Eye offering, no enemies and normal health");
    check(r.coinSpawns.size()==2&&r.coinSpawns[0].ordinal==0&&r.coinSpawns[1].ordinal==2,"two pennies retain slots around collectible");
    int coins=0;std::vector<Vector3> positions;
    for(const auto &coin:s.moneyPickups)if(coin.room==index){check(coin.placedInLayout&&coin.value==1&&coin.sourceSubtype==1,"only ordinary preplaced pennies");positions.push_back(coin.position);++coins;}
    check(coins==2,"exact two live pennies");
    for(int n=0;n<2;++n){const auto at=sourceHeartCell(r,n?8:4,3);check(planarDistance(at,positions[size_t(n)])<.0001f&&!s.arena.blocked(at,.48f)&&!s.arena.path(s.player.position,at,.48f).empty(),"original adapted penny cells are accessible");}
    const auto money=s.money();for(auto at:positions){s.player.position=at;s.step({});}check(s.money()==money+2,"both pennies collect once");
    const auto before=s.effectivePlayerStats();s.player.fireCooldown=.3f;s.player.position=pedestalGeometry::approach(s.rewardPosition(index),{0,0,1},.85f);
    check(s.collectTreasureUpgrade()&&s.itemStacks(Eye)==1&&!s.collectTreasureUpgrade(),"touch grants permanent passive once");
    check(s.player.fireCooldown==.3f&&s.effectivePlayerStats().damage==before.damage&&s.effectivePlayerStats().tearsPerSecond==before.tearsPerSecond,"pickup preserves base stats and active firing wait");
    s.enterRoom(0);s.enterRoom(index);check(!s.rewardAvailable(index)&&s.money()==money+2,"revisit cannot repay item or pennies");
    s.momsEyeChanceMultiplier=.65f;s.resizeRooms(scale,lo,hi,.27f);check(s.itemStacks(Eye)==1&&s.momsEyeChanceMultiplier==.65f&&s.arena.rooms[size_t(index)].sourceTreasureTemplate==6,"Apply keeps owned item/tuning while regenerating selected layout");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.itemStacks(Eye)==1&&s.momsEyeChanceMultiplier==.65f,"descent retains passive/tuning");
    for(const auto &room:s.arena.rooms)check(room.sourceTreasureTemplate<0,"recorded arrangement is opening-floor-only");
    std::cout<<"PASS treasure seed="<<seed<<" room="<<index+1<<" scale="<<scale<<" two pennies/item/revisit/Apply/descent\n";
}
void presets() {
    const auto fp=defaultMechanics()->fingerprint();const auto pth=std::filesystem::temp_directory_path()/("deathward-moms-eye-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json");
    for(auto name:{"d03-shooting/user-preset-2026-11-11.json","d14a6-duke-room/review-preset.json"}) {
        auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity"/name,fp);check(p.defaultZoomPercent==165&&p.momsEyeChanceMultiplier==1,"old presets migrate with same view and source chance");
        p.momsEyeChanceMultiplier=.65f;p.treasureCollectiblePool=7;p.save(pth);check(BalancePreset::load(pth,fp).json()==p.json(),"new live chance and staged offering round-trip");
        p.momsEyeChanceMultiplier=2.01f;bool rejected=false;try{p.save(pth);}catch(...){rejected=true;}check(rejected&&BalancePreset::load(pth,fp).momsEyeChanceMultiplier==.65f,"invalid value rejected without replacing valid export");
    }
    std::filesystem::remove(pth);std::cout<<"PASS schema52 round-trip, older additive migrations and atomic invalid rejection\n";
}
void boundaries() {
    for(int layouts:{0,2}) {
        auto s=generated(11,1.1f,7,9,7,0,layouts);
        check(!s.enterSourceRoomReview(4000006),"OFF/test layouts do not claim complete recorded treasure");
        for(const auto &r:s.arena.rooms)check(r.sourceTreasureTemplate<0,"record excluded outside SOURCE layouts");
    }
    auto s=generated(11,1.1f,7,9,0);
    check(!s.enterSourceRoomReview(4000006),"fixed Onion cannot masquerade as the recorded Mom's Eye review");
    std::cout<<"PASS SOURCE/OFF/test and fixed offering review boundaries\n";
}
}
int main(int argc,char **argv){try{std::cout<<std::unitbuf;
    if(argc>1&&std::string(argv[1])=="--find"){for(uint64_t seed=0;seed<100;++seed){auto s=generated(seed,1.1f,7,9,1);if(s.enterSourceRoomReview(4000006)){std::cout<<"NATURAL "<<seed<<" room="<<s.room+1<<'\n';return 0;}}return 1;}
    native();shots();room(11,.75f,5,5);room(11,1.1f,7,9);room(11,1.5f,10,10);presets();boundaries();return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
