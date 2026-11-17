#include "items/Items.hpp"
#include "items/Screw.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const ItemKey Screw{"isaac",ItemKind::Collectible,255},Onion{"isaac",ItemKind::Collectible,1};
void check(bool ok,const char *m){if(!ok)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>.00004f){std::cerr<<a<<" != "<<b<<'\n';throw std::runtime_error(m);}}
void native() {
    const auto root=std::filesystem::path(DEATHWARD_TEST_ROOT)/"docs/reports/isaac-first-floor-parity/d14a1-screw-reward/source";
    std::ifstream file(root/"native-tears.csv");check(bool(file),"native Tears fixture exists");std::string line;std::getline(file,line);int cases=0;
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float raw,contribution,total,delay,rate;size_t onions,screws;
        check(bool(row>>raw>>onions>>screws>>contribution>>total>>delay>>rate),"native Tears row");
        near(sourceOrdinaryTears(total),rate,"native combined ordinary curve");
        near(ordinaryItemTears(sourceOrdinaryTears(raw),.7f*float(onions)+.5f*float(screws)),rate,"combined contribution and inverse accepted-base adapter");++cases;
    }
    check(cases==240,"240 original-code Tears cases");file.close();file.open(root/"native-shot-speed.csv");check(bool(file),"native Shot Speed fixture exists");std::getline(file,line);cases=0;
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);size_t copies;int held;float speed;
        check(bool(row>>copies>>held>>speed),"native Shot Speed row");near(whipShotSpeed(screwShotSpeed(1,copies),held==27,1),speed,"native copies plus Whip composition");++cases;
    }
    check(cases==18,"18 original-code Shot Speed cases");
}
Simulation make(int reward=255,uint64_t seed=1) {
    Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true,1,true,true,true,true,true,true,1,1,{}, {},true,reward);
    s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);s.player.attributes.tearsPerSecond=1.9272734f;s.player.attributes.shotSpeed=.9f;return s;
}
void effects() {
    auto s=make();const auto base=s.effectivePlayerStats();const auto attack=primaryPlayerAttack(s,s.player.shotDamage,false);const auto hp=s.player.maxHp;
    s.grant(Screw);check(s.itemStacks(Screw)==1,"catalog registers Screw");s.player.fireCooldown=.31f;
    auto upgraded=s.effectivePlayerStats();near(upgraded.tearsPerSecond,ordinaryItemTears(base.tearsPerSecond,.5f),"owned Screw Tears consumer");near(upgraded.shotSpeed,1.1f,"owned Screw Shot Speed consumer");
    auto next=primaryPlayerAttack(s,s.player.shotDamage,false);near(next.speed/attack.speed,1.1f/.9f,"actual shot speed adapts effective stat");
    check(next.maxDistance==attack.maxDistance&&next.damage==attack.damage&&s.player.maxHp==hp&&s.player.fireCooldown==.31f&&!s.activeItem,"Range/damage/health/wait/active slot retained");
    s.grant(Onion);s.grant(Screw);near(s.effectivePlayerStats().tearsPerSecond,ordinaryItemTears(base.tearsPerSecond,1.7f),"Onion/Screw contributions share one curve");
    s.heldTrinket=CancerKey;near(s.effectivePlayerStats().tearsPerSecond,ordinaryItemTears(base.tearsPerSecond,1.7f)+1,"Cancer applied after ordinary curve");
    s.heldTrinket=WhipWormKey;near(s.effectivePlayerStats().shotSpeed,1.8f,"Whip and two Screws stack");s.heldTrinket.reset();
    s.jumpDebug(0);s.godMode=true;s.player.fireCooldown=0;Input input;input.fire=true;input.aimDirection=Vector3{1,0,0};s.step(input);
    check(!s.projectiles.empty(),"real projectile emitted");const auto birth=s.projectiles.back().attack;const float wait=s.player.fireCooldown;
    s.screw={0,0};check(s.player.fireCooldown==wait&&s.projectiles.back().attack.speed==birth.speed,"live strength changes retain wait and birth");near(s.effectivePlayerStats().shotSpeed,.9f,"disabled Shot Speed strength");
    s.screw={1,0};const auto tears=s.effectivePlayerStats().tearsPerSecond;s.screw={1,2};near(s.effectivePlayerStats().tearsPerSecond,tears,"independent strengths");near(primaryPlayerAttack(s,s.player.shotDamage,false).maxDistance,attack.maxDistance,"speed strength preserves distance");
    for(float baseRate:{0.f,.1f,1.9272734f,5.f,10.f}){check(ordinaryItemTears(baseRate,0)==baseRate,"no owned contribution preserves base exactly");check(ordinaryItemTears(baseRate,.5f)>=baseRate,"no reduced custom base");}
}
void bossReward() {
    for(int reward:{25,255})for(uint64_t seed:{0ULL,1ULL}) {
        auto s=make(reward,seed);s.jumpDebug(s.finalRoom());check(s.hasSourceBoss(s.room)&&s.treasureUpgradeItem(s.room)==reward,"selected reward on both supported bosses");
        check(!s.collectTreasureUpgrade()&&!s.rewardAvailable(s.room),"combat gates collection");s.clearRoomDebug();s.step({});
        check(s.rewardAvailable(s.room),"clear unlocks reward");const auto at=s.rewardPosition(s.room);
        check(planarDistance(at,s.arena.rooms[size_t(s.room)].center)<.0001f&&s.arena.blocked({at.x,.85f,at.z},.48f),"centered solid pedestal");
        s.player.position=pedestalGeometry::approach(at,{1,0,0},.85f);const auto hp=s.player.maxHp;
        check(s.collectTreasureUpgrade()&&!s.collectTreasureUpgrade(),"once-only collection");
        check(s.itemStacks({"isaac",ItemKind::Collectible,uint32_t(reward)})==1&&s.player.maxHp==hp+(reward==25?2:0),"reward identity and distinct health behavior");
        const int room=s.room;s.jumpDebug(0);s.jumpDebug(room);check(!s.rewardAvailable(room),"revisit cannot repay");
        s.screw={.75f,1.25f};s.floorExitRequested=true;check(s.advanceFloor(),"descent allowed");
        check(s.bossRewardItem==reward&&s.screw==ScrewTuning{.75f,1.25f}&&s.itemStacks({"isaac",ItemKind::Collectible,uint32_t(reward)})==1,"floor carries permanent ownership and configuration");
        s.resizeRooms(1.11f,7,9,.26f);check(s.screw==ScrewTuning{.75f,1.25f}&&s.bossRewardItem==reward,"map regeneration keeps reward configuration");
    }
}
void presets() {
    const auto root=std::filesystem::path(DEATHWARD_TEST_ROOT);const auto hash=defaultMechanics()->fingerprint();
    const auto dir=std::filesystem::temp_directory_path()/("dw-screw-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    for(const char *name:{"d03-shooting/user-preset-2026-11-11.json","d13b-duke-loop/duke-preset.json","d13c-seeded-bosses/seeded-preset.json"}){
        const auto p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity"/name,hash);check(p.bossRewardItem==25&&!p.screw.custom()&&p.defaultZoomPercent==165,"older presets retain Breakfast, reference strengths and zoom165");
    }
    BalancePreset p;p.mechanicsFingerprint=hash;p.bossRewardItem=255;p.screw={.75f,1.25f};
    for(float zoom:{25.f,165.f,500.f}){p.defaultZoomPercent=zoom;p.save(dir/"preset.json");auto loaded=BalancePreset::load(dir/"preset.json",hash);check(loaded.json()==p.json(),"schema46 reward/effects/zoom round trip");}
    for(auto edit:{0,1,2,3,4}) {
        auto bad=p;if(edit==0)bad.bossRewardItem=1;if(edit==1)bad.screw.tearsStrength=-.01f;if(edit==2)bad.screw.shotSpeedStrength=2.01f;if(edit==3)bad.defaultZoomPercent=24;if(edit==4)bad.defaultZoomPercent=501;
        bool rejected=false;try{bad.save(dir/"preset.json");}catch(const std::exception&){rejected=true;}check(rejected,"invalid configuration rejected before write");check(BalancePreset::load(dir/"preset.json",hash).json()==p.json(),"invalid save leaves previous valid preset intact");
    }
    p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",hash);p.seededBosses=true;p.bossRewardItem=255;
    p.save(root/"artifacts/screw-preset.json");std::filesystem::remove_all(dir);
}
}
int main(){try{native();effects();bossReward();presets();std::cout<<"PASS Screw: 258 native cases, combined effects, real attacks, two boss rewards, lifecycle and schema46 migration/zoom\n";return 0;}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
