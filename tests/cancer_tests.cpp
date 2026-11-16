#include "items/Items.hpp"
#include "items/SadOnion.hpp"
#include "core/BalancePreset.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
const ItemKey Onion{"isaac",ItemKind::Collectible,1};
void check(bool ok,const char *m){if(!ok)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>.00005f)throw std::runtime_error(m);}
Simulation make(uint64_t seed=1,float size=1.1f,int low=7,int high=9) {return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),size,low,high,.26f,true,1,true,true,true,true,true,true,1,1);}
void native() {
    auto s=make();s.canonicalShooting=true;
    std::ifstream in(Root/"docs/reports/isaac-first-floor-parity/pw-t01-cancer/source/native-tears.csv");std::string line;std::getline(in,line);int cases=0;
    while(std::getline(in,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float base,ordinary,bonus,rate,delay;int onions,held;
        check(bool(row>>base>>onions>>held>>ordinary>>bonus>>rate>>delay),"Native Cancer row");
        s.player.attributes.tearsPerSecond=sourceOrdinaryTears(base);s.items.assign(size_t(onions),Onion);s.heldTrinket=held?std::optional{CancerKey}:std::nullopt;
        near(s.effectivePlayerStats().tearsPerSecond,rate,"Native post-Onion Cancer rate");near(30/(delay+1),rate,"Native final-delay inversion");++cases;
    }
    check(cases==60,"All native arithmetic cases");
    check(cancerTears(5,true)==6&&cancerTears(0,true)==0&&cancerTears(3,false)==3,"Beyond ordinary cap, disabled/unowned exact");
    for(float dt:{1/30.f,1/60.f,1/120.f}) {
        TrinketTiming t;t.appear();for(int i=0;i<int(std::round(25/(30*dt)));++i)t.advance(dt);
        check(!t.collectible(),"No pickup before native Drop26");for(int i=0;i<int(std::round(1/(30*dt)));++i)t.advance(dt);check(t.collectible(),"Drop26 contact gate");
        t.collect();for(int i=0;i<int(std::round(16/(30*dt)));++i)t.advance(dt);check(t.phase==TrinketTiming::Phase::Gone,"Collect16 cleanup");
    }
    std::cout<<"PASS 60 native Cancer/Onion rates and 30/60/120Hz appearance gates\n";
}
Vector3 safeAway(const Simulation &s,Vector3 from,float minimum=2) {
    for(const auto &c:s.arena.floorCells){Vector3 p{(c.first+.5f)*FloorTile,.85f,(c.second+.5f)*FloorTile};if(s.arena.roomAt(p)==s.room&&planarDistance(p,from)>minimum&&!s.arena.blocked(p,.48f)&&!s.arena.path(s.player.position,p,.48f).empty())return p;}
    throw std::runtime_error("No safe away point");
}
void lifecycle() {
    auto s=make();s.canonicalShooting=true;s.player.attributes.tearsPerSecond=1.9272734f;s.grant(Onion);s.grant(YumHeartKey);s.activeItem->charge=2;
    const auto point=s.player.position;const float baseline=primaryCadence(s);const auto attack=primaryPlayerAttack(s,s.player.shotDamage,false);
    check(s.spawnTrinket(point,CancerKey,39,true),"Spawn valid Cancer");s.player.fireCooldown=.31f;s.step({});
    check(s.heldTrinket==CancerKey&&s.itemStacks(CancerKey)==0&&s.activeItem->charge==2&&s.itemStacks(Onion)==1,"Separate slot and unchanged active/passive ownership");
    check(primaryCadence(s)<baseline,"Actual primary cadence faster");const auto boosted=primaryPlayerAttack(s,s.player.shotDamage,false);
    check(boosted.damage==attack.damage&&boosted.speed==attack.speed&&boosted.life==attack.life&&boosted.maxDistance==attack.maxDistance&&boosted.radius==attack.radius,"Damage, speed, range, size unaffected");
    Event shot;shot.type=EventType::Shot;shot.position=s.player.position;shot.direction={1,0,0};shot.damage=boosted.damage;shot.attack=boosted;s.queueRoot(shot);s.drainEvents();check(!s.projectiles.empty(),"Emitted shot");const auto born=s.projectiles.back();
    s.player.fireCooldown=.31f;check(s.dropTrinket(),"Drop success");check(!s.heldTrinket&&s.player.fireCooldown==.31f&&s.projectiles.back().life==born.life,"Drop preserves committed wait and flying birth");near(primaryCadence(s),baseline,"Onion baseline restored");
    for(int i=0;i<90;++i)s.step({});check(!s.heldTrinket&&s.trinketPickups.size()==1,"Dropped actor survives and never instantly recollects");
    auto dropped=s.trinketPickups.front().position;s.player.position=safeAway(s,dropped);s.step({});s.player.position=dropped;s.step({});check(s.heldTrinket==CancerKey,"Recollect re-enables exactly one effect");
    const auto rate=s.effectivePlayerStats().tearsPerSecond;s.grant(CancerKey);check(s.effectivePlayerStats().tearsPerSecond==rate&&s.itemStacks(CancerKey)==0,"Duplicate direct grant cannot stack held effect");
    const auto second=safeAway(s,s.player.position);check(s.spawnTrinket(second,CancerKey,77,true),"Second actor for swap");s.player.position=second;s.step({});
    check(s.heldTrinket==CancerKey&&s.trinketPickups.back().contactBlocked&&s.trinketPickups.back().seed==77,"Same-kind swap leaves old item in world");
    for(int i=0;i<90;++i)s.step({});check(s.effectivePlayerStats().tearsPerSecond==rate&&s.trinketPickups.size()==1,"No repeated swap or duplicate permanent modifier");
    s.jumpDebug(1);s.jumpDebug(0);check(s.trinketPickups.size()==1&&s.heldTrinket==CancerKey,"World item and slot retained on revisit");
    s.trinkets={.5f,false,1};const float wait=s.player.fireCooldown;s.resizeRooms(1.11f,7,9,.26f);
    check(s.heldTrinket==CancerKey&&s.trinkets==TrinketTuning{.5f,false,1}&&s.trinketPickups.empty()&&s.player.fireCooldown==wait,"Apply keeps slot/config/wait and resets floor actors");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor()&&s.heldTrinket==CancerKey&&s.trinkets==TrinketTuning{.5f,false,1}&&s.trinketPickups.empty(),"Floor transition keeps owned slot only");
    auto gated=make();gated.grant(CancerKey);gated.trinketPickups.resize(1024);check(!gated.dropTrinket()&&gated.heldTrinket==CancerKey,"Capacity drop is atomic");gated.trinketPickups.clear();gated.dead=true;check(!gated.dropTrinket(),"Death blocks drop");gated.dead=false;gated.rewardOpen=true;check(!gated.dropTrinket(),"Modal blocks drop");gated.rewardOpen=false;
    Input input;input.dropTrinket=true;gated.step(input);check(!gated.heldTrinket,"Actual drop input");gated.grant(CancerKey);gated.step(input);check(gated.heldTrinket==CancerKey,"Held input does not repeat");gated.step({});gated.step(input);check(!gated.heldTrinket,"Released key rearms");
    std::cout<<"PASS slot/actual attack/drop/recollect/swap/revisit/Apply/floor/capacity/control lifecycle\n";
}
std::pair<int,int> witness(bool print=true) {
    for(int seed=1;seed<=100;++seed) {
        auto s=make(seed);
        for(int i=1;i<s.finalRoom();++i){s.jumpDebug(i);if(s.roomClear||!s.roomThreats())continue;s.clearRoomDebug();const auto &a=s.rooms[size_t(i)].redHeartAward;
            if(a&&a->variant==350&&a->delivered&&!s.trinketPickups.empty()){if(print)std::cout<<"WITNESS seed="<<seed<<" room="<<i+1<<" variant="<<a->variant<<" subtype="<<a->subtype<<" seed="<<a->pickupSeed<<" enemies-cleared\n";return {seed,i};}}
    }
    throw std::runtime_error("No natural trinket witness");
}
void producer() {
    auto [seed,owner]=witness();
    for(auto dimensions:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}}){auto [scale,lo,hi]=dimensions;auto s=make(seed,scale,lo,hi);s.jumpDebug(owner);check(!s.roomClear&&s.roomThreats()>0,"Natural hostile encounter");s.clearRoomDebug();
        const auto &a=s.rooms[size_t(owner)].redHeartAward;check(a&&a->variant==350&&a->subtype==39&&a->delivered,"Natural trinket clear result");check(s.trinketPickups.size()==1,"One actual actor");
        const auto p=s.trinketPickups.front().position;check(!s.arena.blocked(p,.35f)&&!s.arena.path(s.player.position,p,.48f).empty(),"Reward physically reachable");s.clearRoom();s.jumpDebug(0);s.jumpDebug(owner);check(s.trinketPickups.size()==1,"Clear and revisit never duplicate");
    }
    auto disabled=make(seed);disabled.trinkets.clearRewards=false;disabled.jumpDebug(owner);disabled.clearRoomDebug();check(disabled.rooms[size_t(owner)].redHeartAward->variant==350&&disabled.trinketPickups.empty(),"Disabled producer records unsupported roll");disabled.trinkets.clearRewards=true;disabled.clearRoom();check(disabled.trinketPickups.empty(),"Enable cannot reroll resolved award");
    auto pending=make(seed);pending.jumpDebug(owner);pending.trinketPickups.resize(1024);pending.clearRoomDebug();auto &a=pending.rooms[size_t(owner)].redHeartAward;check(a&&a->pending&&!a->delivered,"Capacity keeps pending identity");const auto identity=a->pickupSeed;pending.trinketPickups.clear();pending.trinkets.clearRewards=false;pending.step({});check(a->delivered&&pending.trinketPickups.size()==1&&pending.trinketPickups.front().seed==identity,"Birth retries retain selected identity despite live disable");
    std::cout<<"PASS natural producer/three sizes/revisit/off/pending identity\n";
}
void persistence() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-cancer-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&!p.trinkets.custom(),"Old original preset migrates exactly");
    p.trinkets={.75f,false,1};p.yumHeart={3,2,1};p.brotherBobby.interval=.8f;p.save(dir/"preset.json");check(BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).json()==p.json(),"All object overrides exact roundtrip");
    auto bad=p.json();const std::string before="\"binding\": 1";auto at=bad.find(before);bad.replace(at,before.size(),"\"binding\": 0.5");std::ofstream(dir/"bad.json")<<bad;bool rejected=false;try{BalancePreset::load(dir/"bad.json",p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"Invalid fractional binding refused");
    auto s=make();s.grant(CancerKey);s.grant(YumHeartKey);s.activeItem->charge=2;
    {CampaignStore store(dir/"campaign.save");const auto id=store.begin(1);auto summary=s.summary();summary.id=id;store.checkpoint(summary);}
    CampaignStore read(dir/"campaign.save");check(read.data().pending->heldTrinket==CancerKey&&read.data().pending->activeItem==s.activeItem&&read.data().pending->items==s.items,"Campaign slot checkpoint independent from collectible ownership");read.recover();check(read.data().history.back().heldTrinket==CancerKey,"Interrupted summary preserves trinket, no resume claim");
    std::ifstream file(dir/"campaign.save");std::string bytes((std::istreambuf_iterator<char>(file)),{});auto payload=bytes.substr(bytes.find('\n')+1);const std::string slot="1 \"isaac:trinket:39\"\n";const auto index=payload.find(slot);check(index!=payload.npos,"Serialized slot row");
    const auto fixture=[&](const char *name,int version,const std::string &body){uint64_t hash=14695981039346656037ULL;for(unsigned char c:body){hash^=c;hash*=1099511628211ULL;}std::ofstream(dir/name)<<"DEATHWARD "<<version<<' '<<hash<<'\n'<<body;};
    auto legacy=payload;legacy.erase(index,slot.size());fixture("old.save",8,legacy);CampaignStore old(dir/"old.save");check(!old.data().history.back().heldTrinket&&old.data().history.back().activeItem==s.activeItem,"Version8 migration preserves charge and empty trinket");
    auto corrupt=payload;corrupt.replace(index,slot.size(),"1 \"isaac:collectible:39\"\n");fixture("bad.save",9,corrupt);rejected=false;try{CampaignStore invalid(dir/"bad.save");}catch(...){rejected=true;}check(rejected,"Collectible/trinket numeric collision rejected");
    std::filesystem::remove_all(dir);std::cout<<"PASS presets and version9/8 campaign slot validation\n";
}
}
int main(int argc,char **){try{if(argc>1){witness();return 0;}native();lifecycle();producer();persistence();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
