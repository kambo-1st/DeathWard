#include "combat/Simulation.hpp"
#include "world/SourceRoomHeartsData.hpp"
#include "world/SourceRoomSelection.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,int mode=2,float size=1.1f,int minimum=7,int maximum=9,int floor=0) {
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),size,minimum,maximum,.26f,true,mode);
    r.godMode=true;return r;
}
void damageRed(Simulation &r,int halves){auto h=r.player.sourceHealth();h.addRed(-halves);r.player.setSourceHealth(h);}
void placedLifecycle() {
    auto r=create(69);check(r.heartPickups.size()==2,"both test hearts generated before room entry");
    const auto full=r.heartPickups[0],half=r.heartPickups[1];const int owner=full.room;
    check(!r.rooms[size_t(owner)].visited&&!r.rooms[size_t(owner)].cleared&&full.amount==2&&half.amount==1,"full and half are initial layout actors, not clear rewards");
    check(full.placedInLayout&&half.placedInLayout&&full.timing.collectible()&&half.timing.collectible()&&full.timing.phase==RedHeartTiming::Phase::Idle,"preplaced actors start ready without a birth delay");
    for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceCombatTemplate==47)
        check(r.arena.rooms[size_t(i)].heartSpawns.empty(),"recorded D08 empty layout stays exact");
    r.jumpDebug(owner);for(auto &e:r.enemies){e.state=EnemyState::Stunned;e.stateTime=1000;}
    check(r.livingEnemies()>0,"hearts available before the encounter is cleared");
    r.player.position=full.position;r.step({});check(r.player.hp==6&&r.heartPickups.size()==2,"full health refuses preplaced heart");
    damageRed(r,3);r.step({});check(r.player.hp==5&&r.heartPickups[0].timing.phase==RedHeartTiming::Phase::Collect,"full pickup immediately restores two halves during combat");
    r.player.position=half.position;r.step({});check(r.player.hp==6&&r.heartPickups[1].timing.phase==RedHeartTiming::Phase::Collect,"half pickup restores one half");
    for(int n=0;n<30;++n)r.step({});check(r.heartPickups.empty(),"collected layout effects expire");
    r.jumpDebug(0);r.jumpDebug(owner);for(int n=0;n<3;++n)r.step({});check(r.heartPickups.empty(),"revisiting cannot repay a collected layout");
    r.clearRoomDebug();check(r.heartPickups.empty()&&r.rooms[size_t(owner)].roomHeartsDelivered==std::vector<bool>({true,true}),"clearing does not recreate layout hearts");
    auto untouched=create(69);const auto original=untouched.heartPickups[0];untouched.jumpDebug(original.room);untouched.jumpDebug(0);untouched.jumpDebug(original.room);
    check(untouched.heartPickups.size()==2&&distance(original.position,untouched.heartPickups[0].position)==0,"uncollected pickups survive revisits exactly once");
    damageRed(r,1);const auto id=r.summary().id;r.resizeRooms(1.1f,7,9,.26f,std::nullopt,0);
    check(r.roomHeartLayouts==0&&r.heartPickups.empty()&&r.player.hp==5&&r.summary().id==id,"same-size mode change regenerates floor and retains player/expedition");
    r.resizeRooms(1.1f,7,9,.26f,std::nullopt,2);check(r.heartPickups.size()==2&&r.player.hp==5,"explicit testing regeneration can reset layout pickup state");
    auto later=create(69,2,1.1f,7,9,1);check(later.heartPickups.empty()&&later.roomHeartLayouts==2,"opening-floor layer does not leak onto later source stages");
    std::cout<<"PASS preplaced full/half healing, refusal, combat admission, initial idle, revisit, separate clear rewards and regeneration boundaries; witness room="<<owner+1<<'\n';
}
void geometryAndCapacity() {
    for(uint64_t seed:{1,12,69,355})for(float size:{.75f,1.1f,1.5f}) {
        auto r=create(seed,2,size,5,10);check(r.heartPickups.size()==2,"both placements fit supported dynamic room sizes");
        for(const auto &h:r.heartPickups) {
            check(r.arena.roomAt(h.position)==h.room&&!r.arena.blocked(h.position,.48f)&&!r.arena.reservedSupplyCache(h.position,.6f),"layout hearts on legal accessible floor outside cover/cache");
            for(int p:r.arena.rooms[size_t(h.room)].passages)for(const auto &gate:r.arena.passages[size_t(p)].gates)check(!sphereBox(h.position,.7f,gate),"layout hearts stay clear of gates");
        }
        check(planarDistance(r.heartPickups[0].position,r.heartPickups[1].position)>=1.25f,"separate full and half pickup footprints");
    }
    auto r=create(69);const int owner=r.heartPickups[0].room;const auto wanted=r.heartPickups[0].position;
    r.rooms[size_t(owner)].roomHeartsDelivered.assign(2,false);
    r.heartPickups.assign(1024,HeartPickup{r.arena.rooms[0].center,HeartKind::Red,2,0});r.jumpDebug(owner);r.step({});
    check(!r.rooms[size_t(owner)].roomHeartsDelivered[0],"capacity waits without consuming layout request");
    r.heartPickups.clear();r.arena.obstacles.push_back({add(wanted,{-1,-1,-1}),add(wanted,{1,2,1})});r.arena.rebuildWalls();r.step({});
    check(r.heartPickups.size()==2&&planarDistance(r.heartPickups[0].position,wanted)>1&&r.heartPickups[0].amount==2,"blocked source point relocates safely without changing subtype");
    check(r.heartPickups[0].timing.phase==RedHeartTiming::Phase::Idle,"deferred layout actors retain placed lifecycle");
    std::cout<<"PASS 12 size/seed placement cases, gate/cache separation, capacity recovery and blocked-position fallback\n";
}
void sourcePool() {
    bool full=false,half=false,unsupported=false,empty=false;int generated=0;
    for(uint64_t seed=1;seed<=90&&!(full&&half&&unsupported&&empty);++seed) {
        auto r=create(seed,1);++generated;
        for(const auto &layout:r.arena.rooms)if(layout.sourceHeartTemplate>=0) {
            const auto source=std::find_if(BasementHeartLayouts.begin(),BasementHeartLayouts.end(),[&](const auto &s){return s.variant==layout.sourceHeartTemplate;});
            check(source!=BasementHeartLayouts.end(),"selected layout has preserved source metadata");
            check(sourceRoomEligible(*source,sourceBasementFirstFloorQuery(0)),"actual selection uses the ordinary native first-floor caller");
            check(layout.sourceRoomSelectionSeed&&layout.sourceRoomSpawnSeed==sourceRoomDescriptorSeeds(layout.sourceRoomSelectionSeed).spawn,"actual generation derives spawn seed from its selection seed");
            uint32_t slotSeed=layout.sourceRoomSpawnSeed;int ordinal=0;
            for(const auto &spawn:layout.heartSpawns) {
                const auto slot=std::find_if(BasementHeartSlots.begin()+source->firstSlot,BasementHeartSlots.begin()+source->firstSlot+source->slotCount,
                    [&](const auto &s){return s.x==spawn.x&&s.y==spawn.y;});
                check(slot!=BasementHeartSlots.begin()+source->firstSlot+source->slotCount,"source slot recorded");
                while(ordinal<=slot->ordinal){sourceRoomSpawnRandom(slotSeed);++ordinal;}
                check(spawn.pickupSeed==slotSeed,"actual pickup consumes descriptor seed after every preceding source slot");
            }
            for(int p:layout.passages) {
                const auto &passage=r.arena.passages[size_t(p)];
                const int index=int(&layout-r.arena.rooms.data());
                const auto direction=sub(r.arena.rooms[size_t(passage.rooms[0]==index?passage.rooms[1]:passage.rooms[0])].center,layout.center);
                const int door=std::abs(direction.x)>std::abs(direction.z)?(direction.x<0?0:2):(direction.z<0?1:3);
                check(source->doors&(1<<door),"actual main-game selection permits every connected door");
            }
            empty|=layout.heartSpawns.empty();
            for(const auto &spawn:layout.heartSpawns)unsupported|=spawn.subtype!=1&&spawn.subtype!=2;
        }
        for(const auto &h:r.heartPickups) {
            check(h.placedInLayout&&(h.sourceSubtype==1||h.sourceSubtype==2),"source pool only enables selected red variants");
            full|=h.amount==2;half|=h.amount==1;
            std::cout<<"SOURCE seed="<<seed<<" room="<<h.room+1<<" subtype="<<h.sourceSubtype<<" layout="<<r.arena.rooms[size_t(h.room)].sourceHeartTemplate<<'\n';
        }
        if(!r.heartPickups.empty()) {
            auto same=create(seed,1);check(same.heartPickups.size()==r.heartPickups.size(),"deterministic source-layer selection");
            for(size_t i=0;i<r.heartPickups.size();++i)check(same.heartPickups[i].sourceSubtype==r.heartPickups[i].sourceSubtype&&distance(same.heartPickups[i].position,r.heartPickups[i].position)==0,"seeded identity and placement repeat exactly");
        }
    }
    check(full&&half&&empty&&unsupported,"source layers exercise both selected variants, empty layouts and retained unsupported outcomes");
    std::cout<<"PASS source-layer generation witnesses across "<<generated<<" seeds (not a native selection-frequency benchmark)\n";
}
int main(){try{placedLifecycle();geometryAndCapacity();sourcePool();}catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
