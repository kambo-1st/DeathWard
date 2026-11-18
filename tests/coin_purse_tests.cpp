#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "items/SadOnion.hpp"
#include "world/ShopCartGeometry.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
using namespace dw;
namespace {
const ItemKey Purse{"isaac",ItemKind::Collectible,195};
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void near(float a,float b,const char *why){if(std::abs(a-b)>.0001f){std::cerr<<a<<" != "<<b<<'\n';throw std::runtime_error(why);}}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Mine,false);s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.player.position={0,.85f,0};
    s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);return s;
}
Simulation generated(uint64_t seed,float scale=.95f,int lo=7,int hi=9,int pool=1) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,pool,1);
}
void native() {
    auto csv=[&](const char *name,auto consume){std::ifstream f(Root/"docs/reports/isaac-first-floor-parity/d14a8-coin-purse/source"/name);check(bool(f),"native fixture exists");std::string line;std::getline(f,line);int n=0;while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);consume(in);++n;}return n;};
    check(csv("native-colors.csv",[](auto &in){uint32_t seed;int color;in>>seed>>color;check(sourceOrdinaryPillColor(seed)==color,"native ordinary color arithmetic");})==515,"515 colors");
    auto s=fixture();s.player.attributes={};
    check(csv("native-stats.csv",[&](auto &in){int effect,count;float speed,raw,range,shot,luck;in>>effect>>count>>speed>>raw>>range>>shot>>luck;
        s.pills.consumed={};s.pills.consumed[size_t(effect)]=count;auto a=s.effectivePlayerStats();
        near(a.speed,std::clamp(speed,.1f,2.f),"native speed contribution");near(a.rangeTiles,std::max(1.f,range),"native range contribution");near(a.shotSpeed,std::clamp(shot,.6f,2.f),"native shot contribution with adapter cap");near(a.luck,luck,"native luck contribution");near(a.tearsPerSecond,sourceOrdinaryTears(raw),"native raw tear contribution through ordinary curve");})==40,"40 stat cases");
    check(csv("native-health.csv",[&](auto &in){int effect,cap,red,afterCap,afterRed,soul,converted;in>>effect>>cap>>red>>afterCap>>afterRed>>soul>>converted;
        s.player.maxHp=cap;s.player.hp=red;s.player.soulHearts=s.player.boneHearts=0;s.player.blackHeartMask=0;s.pills.effects[0]=effect;
        const int resolved=s.resolvedPillEffect(1);check((resolved!=effect)==bool(converted),"health-down safety resolution");auto h=s.player.sourceHealth();
        switch(resolved){case 2:h.addSoul(4);break;case 5:h.addRed(h.redCapacity());break;case 6:h.addMaxRed(-2);break;case 7:h.addMaxRed(2);break;}
        s.player.setSourceHealth(h);check(s.player.maxHp==afterCap&&s.player.hp==afterRed&&s.player.soulHearts==soul,"native ordinary health mutations");})==60,"60 health cases");
    std::cout<<"PASS 515 native colors, 40 stat contributions (explicit adapter caps), 60 health states\n";
}
void lifecycle() {
    auto s=fixture();s.grant(Purse);check(s.itemStacks(Purse)==1&&s.pendingPursePills.size()==4,"fresh purse queues four");auto pending=s.pendingPursePills;
    s.pillTuning.purseCount=8;s.pillPickups.resize(1024);s.step({});check(s.pendingPursePills.size()==4,"capacity retains paid drops");
    for(size_t i=0;i<4;++i)check(s.pendingPursePills[i].seed==pending[i].seed&&s.pendingPursePills[i].color==pending[i].color,"retries retain identities");
    s.pillPickups.clear();s.step({});check(s.pendingPursePills.empty()&&s.pillPickups.size()==4,"space recovery delivers original count");
    auto &first=s.pillPickups[0];s.player.position=first.position;const int color=first.color;const auto hp=s.player.hp;
    s.step({});check(s.pills.held==0,"appear contact gated");for(int n=0;n<80;++n)s.step({});check(s.pills.held==color&&s.player.hp==hp&&!s.pills.known(color),"touch holds unidentified pill without using");
    s.pills.effects[size_t(color-1)]=14;Input use;use.usePill=true;s.step(use);check(s.pills.held==0&&s.pills.known(color)&&s.pills.consumed[14]==1,"use identifies and consumes once");
    s.pills.held=color;for(int n=0;n<5;++n)s.step(use);check(s.pills.held==color&&s.pills.consumed[14]==1,"held use edge cannot reuse newly held pill");s.step({});s.step(use);check(s.pills.consumed[14]==2,"release rearms use");
    s.pillPickups.clear();s.pills.held=2;check(s.spawnPill(s.player.position,3,123,true),"swap actor admitted");s.step({});check(s.pills.held==3&&s.pillPickups[0].color==2,"touch swaps outgoing color");for(int n=0;n<100;++n)s.step({});check(s.pills.held==3,"no contact swap loop");
    s.player.position.x+=3;s.step({});s.player.position=s.pillPickups[0].position;s.step({});check(s.pills.held==2,"leave contact rearms swap");
    s.pillPickups.clear();check(s.dropPill()&&s.pills.held==0,"manual drop empties slot");for(int n=0;n<100;++n)s.step({});check(s.pills.held==0,"drop not immediately recollected");s.player.position.x+=3;s.step({});s.player.position=s.pillPickups[0].position;s.step({});check(s.pills.held==2,"dropped pill recollected");
    s.pills.effects[1]=7;s.player.maxHp=6;s.player.hp=3;check(s.usePill()&&s.player.maxHp==8&&s.player.hp==3,"health up creates empty container");s.pills.effects[1]=6;s.pills.held=2;s.player.maxHp=2;s.player.hp=1;check(s.usePill()&&s.player.maxHp==4&&s.player.hp==1,"last red container safety");
    s.pills.held=2;s.dead=true;check(!s.usePill()&&!s.dropPill()&&s.pills.held==2,"dead consumption denied");
    PillTiming timing;timing.appear();for(int i=0;i<25;++i)timing.advance(1.f/30);check(!timing.collectible(),"before drop gate");timing.advance(1.f/30);check(timing.collectible(),"drop frame26 gate");timing.collect();timing.advance(.5f);check(timing.phase==PillTiming::Phase::Gone,"collect15 cleanup");
    std::cout<<"PASS purse capacity/retry, appear/collect timing, unknown/identified, swap/drop rearming, use edge and health safety\n";
}
void stats() {
    auto s=fixture();s.player.attributes.speed=1.1f;s.player.attributes.tearsPerSecond=1.9272734f;s.player.attributes.shotSpeed=1.05f;const auto base=s.player.attributes;
    auto up=s;up.pills.consumed[14]=1;Input move;move.movement={1,0,0};s.step(move);up.step(move);check(planarDistance(up.player.position,{0,.85f,0})>planarDistance(s.player.position,{0,.85f,0}),"actual walking consumes speed pill");near(up.player.attributes.speed,base.speed,"base stat immutable");
    up.pills.consumed[15]=1;check(up.effectivePlayerStats().tearsPerSecond<base.tearsPerSecond,"tears down lowers accepted custom cadence");up.pills.consumed[16]=2;check(up.effectivePlayerStats().tearsPerSecond>base.tearsPerSecond,"up/down aggregate once");
    up.grant({"isaac",ItemKind::Collectible,1});up.grant({"isaac",ItemKind::Collectible,255});up.heldTrinket=CancerKey;
    near(up.effectivePlayerStats().tearsPerSecond,ordinaryItemTears(base.tearsPerSecond,.7f+.5f+1.f-.4f)+1,"ordinary contributions then Cancer once");
    up.pills.consumed[48]=2;up.pills.consumed[12]=1;up.heldTrinket=WhipWormKey;near(up.effectivePlayerStats().shotSpeed,base.shotSpeed+.3f+.2f+.5f,"shot pill, Screw and Whip once");near(up.effectivePlayerStats().rangeTiles,base.rangeTiles+1.25f,"range independent");
    Input fire;fire.fire=true;fire.aim={20,.85f,0};up.step(fire);check(!up.projectiles.empty(),"actual attack exists");const auto spec=up.projectiles[0].attack;const auto wait=up.player.fireCooldown;up.pillTuning.statStrength=0;check(up.projectiles[0].attack.speed==spec.speed&&up.player.fireCooldown==wait,"live strength preserves birth/wait");near(up.effectivePlayerStats().speed,base.speed,"zero strength removes consumed effect only");
    check(ordinaryItemTears(7,-.4f)<7&&ordinaryItemTears(7,0)==7&&ordinaryItemTears(0,-.4f)==0,"custom high and disabled cadence preserved");
    std::cout<<"PASS actual speed/shots, signed Tears, owned modifier ordering, live strength and immutable base/waits/projectiles\n";
}
void shop(uint64_t seed,float scale,int lo,int hi) {
    auto s=generated(seed,scale,lo,hi);const auto mapping=s.pills.effects;check(s.shopUpgradeItem==195&&s.shopVariationActive(),"naturally selected purse shop");s.enterRoom(s.arena.shopRoom);s.player.position=s.shopUpgradePosition();s.moneyCollected=20;const int price=s.shopPrice(15,s.shopUpgradeSlot);check(s.collectShopUpgrade()&&s.money()==uint64_t(20-price)&&!s.collectShopUpgrade(),"purchase pays once");s.step({});check(s.pillPickups.size()==4&&s.pendingPursePills.empty(),"four safe delivered actors");
    for(const auto &p:s.pillPickups)check(!s.arena.blocked(p.position,.48f)&&!s.arena.path(s.player.position,p.position,.48f).empty(),"pill reachable around shop");
    s.pills.held=1;s.pills.identified[0]=true;s.pills.consumed[14]=1;s.pillTuning={6,.8f,1};s.grant(Purse);check(s.pendingPursePills.size()==6,"future purchase uses edited count");s.resizeRooms(scale,lo,hi,.27f);check(s.pendingPursePills.size()==6&&s.pills.effects==mapping&&s.pills.held==1&&s.pills.known(1)&&s.pills.consumed[14]==1&&s.itemStacks(Purse)==2,"Apply keeps build and pending birth identity");s.step({});check(s.pendingPursePills.empty()&&s.pillPickups.size()==6,"pending births placed after Apply");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.pills.effects==mapping&&s.pills.held==1&&s.pills.consumed[14]==1&&s.pillTuning.binding==1&&s.pillPickups.empty(),"descent keeps owned pills, drops stay behind");
    auto retry=generated(seed,scale,lo,hi);check(retry.pills.effects==mapping&&retry.pills.held==0&&retry.pills.consumed[14]==0&&!retry.pills.known(1),"fresh expedition resets identification/use history");
    std::cout<<"PASS natural shop seed="<<seed<<" room="<<retry.arena.shopRoom+1<<" size="<<scale<<" range="<<lo<<'-'<<hi<<" purchase, placement, Apply, descent and retry\n";
}
void presets() {
    auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a7-moms-eye/review-preset.json",defaultMechanics()->fingerprint());check(p.pills==PillTuning{}&&p.defaultZoomPercent==165,"schema52 migration retains accepted settings");
    const auto path=std::filesystem::temp_directory_path()/("deathward-pills-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json");p.pills={6,.75f,1};p.shopCollectiblePool=3;p.save(path);auto loaded=BalancePreset::load(path,p.mechanicsFingerprint);check(loaded.pills==p.pills&&loaded.shopCollectiblePool==3,"schema53 custom roundtrip");
    auto bad=p;bad.pills.purseCount=0;bool rejected=false;try{bad.save(path);}catch(...){rejected=true;}check(rejected&&BalancePreset::load(path,p.mechanicsFingerprint).pills==p.pills,"invalid export atomic");
    auto json=p.json();const auto at=json.find("\"purse_count\": 6");check(at!=std::string::npos,"pill field exists");json.replace(at,16,"\"purse_count\": 9");{std::ofstream f(path);f<<json;}rejected=false;try{(void)BalancePreset::load(path,p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"invalid import rejected");std::filesystem::remove(path);
    std::cout<<"PASS schema52/53 migration/roundtrip and invalid export/import\n";
}
}
int main(int argc,char **argv){try {
    if(argc>1&&std::string(argv[1])=="--find"){for(uint64_t seed=0;seed<300;++seed){auto s=generated(seed);if(s.shopUpgradeItem==195&&s.shopVariationActive()&&s.shopPrice(15,s.shopUpgradeSlot)==15){std::cout<<"WITNESS "<<seed<<" room="<<s.arena.shopRoom+1<<'\n';return 0;}}return 1;}
    native();lifecycle();stats();presets();const uint64_t seed=argc>1?std::stoull(argv[1]):0;shop(seed,.75f,5,5);shop(seed,.95f,7,9);shop(seed,1.5f,10,10);return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
