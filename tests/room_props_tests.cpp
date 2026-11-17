#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourcePropRooms.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
void nativeDrops() {
    std::ifstream file(std::filesystem::path(DEATHWARD_TEST_ROOT)/"docs/reports/isaac-first-floor-parity/ordinary-room-props/source/native-drops.csv");
    check(bool(file),"native fixture exists");std::string line;std::getline(file,line);int count=0;
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);
        std::string kind;uint32_t seed,pickupSeed,actualSeed;int variant,subtype;
        check(bool(row>>kind>>seed>>variant>>pickupSeed>>subtype),"native fixture row");
        const auto got=ordinaryPropDrop(seed,kind=="fire",actualSeed);
        if(got.variant!=variant||got.subtype!=subtype||actualSeed!=pickupSeed){std::cerr<<kind<<' '<<seed<<' '<<got.variant<<' '<<actualSeed<<' '<<got.subtype<<" vs "<<variant<<' '<<pickupSeed<<' '<<subtype<<'\n';throw std::runtime_error("native drop mismatch");}++count;
    }
    check(count==1024,"1024 native drop cases");
}
Simulation make(int mode=2,uint64_t seed=69,float scale=1.1f,int minimum=7,int maximum=9) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,minimum,maximum,.26f,true,1,true,true,true,true,true,true,1,1,{}, {},true,25,{mode});
}
void hit(Simulation &s,EntityId id,bool bomb=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=11.2f;e.explosionDamage=bomb;
    check(s.queueRoot(e),"damage admitted");s.drainEvents();
}
void behavior() {
    auto s=make();check(s.enterSourceRoomReview(PropReviewRoom),"direct main-game test room exists");
    check(s.roomThreats()==0&&s.roomEnemyCount(s.room)==0&&s.enemies.size()==2,"fire props are not hostiles or room-clear threats");
    const int room=s.room;const auto fire=s.enemies.front().id;const auto at=s.enemies.front().position;
    s.player.position=at;s.step({});check(s.player.hp==5,"ordinary fire contact costs half a heart");
    s.step({});check(s.player.hp==5,"contact hurt immunity stops repeated payment");
    s.player.position=s.arena.rooms[size_t(room)].entry;
    int shots=0;while(!s.findEnemy(fire)->environment->spent&&shots<8){hit(s,fire);++shots;}
    check(shots>=2&&shots<=4&&s.findEnemy(fire)->environment->spent,"ordinary shots extinguish source hit-count durability");
    const auto reward=s.findEnemy(fire)->environment->propReward;hit(s,fire);check(s.findEnemy(fire)->environment->propReward.seed==reward.seed,"spent fire cannot reroll");
    hit(s,s.enemies.back().id,true);check(s.enemies.back().environment->spent,"one blast extinguishes fire");
    auto p=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &b){return b.room==room&&b.kind==BreakableKind::Dung;});
    check(p!=s.arena.breakables.end()&&p->health==4&&s.arena.blocked(p->rewardPosition,.48f),"source poop has four hit steps and solid collision");
    const auto poopId=p->id;const auto poopAt=p->rewardPosition;s.player.position=add(poopAt,{-3,0,0});const auto hp=s.player.hp;
    Input shoot;shoot.fire=true;shoot.aim=poopAt;for(int n=0;n<240&&!p->destroyed;++n)s.step(shoot);
    check(p->destroyed&&!s.arena.blocked(poopAt,.48f)&&s.player.hp==hp,"real shots destroy poop, opening collision without contact damage");
    const auto paid=p->propReward;check(paid.resolved,"destruction resolves reward once");
    s.enterRoom(0);s.enterRoom(room);
    p=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &b){return b.id==poopId;});
    check(p->destroyed&&p->propReward.seed==paid.seed&&s.findEnemy(fire)->environment->spent,"revisit keeps destroyed props and reward identity");
    auto protect=make();protect.enterSourceRoomReview(PropReviewRoom);protect.player.position=protect.enemies[0].position;protect.player.dodge=.3f;protect.step({});check(protect.player.hp==6,"universal dodge retains fire immunity");
    protect.player.dodge=0;protect.roomProps.fireDamageHalfHearts=2;protect.step({});check(protect.player.hp==4,"live contact edit affects next eligible hit");
}
void drops() {
    auto s=make();s.enterSourceRoomReview(PropReviewRoom);s.player.position=s.arena.rooms[size_t(s.room)].entry;
    uint32_t winning=1,unused;while(ordinaryPropDrop(winning,true,unused).variant!=20)++winning;
    auto &f=s.enemies.front();f.environment->dropSeed=winning;
    s.moneyPickups.resize(1024);hit(s,f.id,true);const auto resolved=f.environment->propReward;
    check(resolved.resolved&&!resolved.delivered&&resolved.variant==20,"capacity keeps resolved reward pending");
    s.roomProps.rewards=false;s.moneyPickups.clear();s.step({});
    check(f.environment->propReward.delivered&&s.moneyPickups.size()==1&&f.environment->propReward.seed==resolved.seed,"deferred reward survives disabling future drops");
    const auto count=s.moneyPickups.size();for(int n=0;n<10;++n)s.step({});check(s.moneyPickups.size()==count,"drop is paid exactly once");
    s.enemies.back().environment->dropSeed=winning;hit(s,s.enemies.back().id,true);s.step({});check(s.enemies.back().environment->propReward.variant==0&&s.moneyPickups.size()==count,"disabled future destruction emits no loot");
}
void coverage() {
    for(float scale:{.75f,1.1f,1.5f}) {
        auto s=make(2,69,scale);check(s.enterSourceRoomReview(PropReviewRoom),"test layout supported across sizes");
        int poops=0;for(const auto &p:s.arena.breakables)if(p.room==s.room&&p.kind==BreakableKind::Dung)++poops;
        check(poops==3&&s.enemies.size()==2,"exact test contents");
        s.roomProps.fireDamageHalfHearts=3;s.roomProps.rewards=false;s.resizeRooms(scale==1.5f?1.49f:scale+.01f,7,9,.26f);
        check(s.roomProps==RoomPropsTuning{2,3,false},"map regeneration retains live prop choices");
    }
    // Natural selection uses the existing descriptor stream. Capture witnesses,
    // rather than forcing records into protected room roles.
    // Witnesses found by a one-off scan of seeds0..1015. Keep the regression
    // bounded: each record is naturally selected, never injected by this test.
    for(const auto &[seed,id]:std::array<std::pair<uint64_t,int>,3>{{{150,26},{1015,52},{523,633}}}) {
        for(int size=0;size<3;++size) {
            const float scale=size==0?.75f:size==1?1.1f:1.5f;
            auto s=make(1,seed,scale,size==0?5:size==1?7:10,size==0?5:size==1?9:10);
            if(!s.enterSourceRoomReview(id)) {
                check(size!=1,"baseline natural witness remains selected");
                // Canyon geometry changes may alter compatible door weights;
                // never force a source record merely to preserve a test witness.
                std::cout<<"Natural selection changes for source "<<id<<" seed "<<seed<<" scale "<<scale<<'\n';continue;
            }
            check(s.roomEnemyCount(s.room)==(id==26?0:id==52?1:2),"only native monsters count as threats");
            int poops=0,rocks=0,fires=0;
            for(const auto &b:s.arena.breakables)if(b.room==s.room){poops+=b.kind==BreakableKind::Dung;rocks+=b.kind==BreakableKind::CrackedRock;}
            for(const auto &e:s.enemies)fires+=e.monster==monsterId(33);
            check(poops==(id==633?0:2)&&fires==(id==633?7:0)&&rocks==(id==633?8:0),"complete source prop/rock counts");
            std::cout<<"Natural source "<<id<<" seed "<<seed<<" displayed room "<<s.room+1<<" scale "<<scale<<'\n';
        }
    }
}
void presets() {
    const auto root=std::filesystem::path(DEATHWARD_TEST_ROOT),dir=std::filesystem::temp_directory_path()/("dw-props-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    auto p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());
    check(p.roomProps==RoomPropsTuning{}&&p.defaultZoomPercent==165&&p.playerSpeed==1,"old preset migrates props retaining accepted values");
    const auto old=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d14a1-screw-reward/screw-preset.json",defaultMechanics()->fingerprint());
    check(old.roomProps==RoomPropsTuning{}&&old.bossRewardItem==255&&old.defaultZoomPercent==165,"schema46 migration retains accepted Screw and view");
    p.roomProps={2,2,false};p.screw={.75f,1.25f};p.bossRewardItem=255;p.save(dir/"preset.json");check(BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).json()==p.json(),"schema47 complete round trip");
    auto bad=p;bad.roomProps.layouts=3;bool rejected=false;try{bad.save(dir/"preset.json");}catch(const std::exception&){rejected=true;}check(rejected&&BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).json()==p.json(),"invalid props reject atomically");
    p.roomProps={2};p.screw={};p.bossRewardItem=25;p.seededBosses=true;std::filesystem::create_directories(root/"artifacts");p.save(root/"artifacts/ordinary-props-preset.json");std::filesystem::remove_all(dir);
}
}
int main(){try{nativeDrops();behavior();drops();coverage();presets();std::cout<<"PASS ordinary props: native drops, real shots/contact, destruction/revisit, three source rooms, sizes, preset migration\n";return 0;}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
