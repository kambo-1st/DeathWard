#include "combat/Simulation.hpp"
#include "items/ItemPools.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
void pools() {
    std::set<ItemKey> all;
    for(auto pool:{ItemPool::Armory,ItemPool::Shop,ItemPool::Boss,ItemPool::Bargain}) {
        std::set<ItemKey> seen;
        for(uint64_t seed=0;seed<1024;++seed) {
            auto pair=drawItemOffers(pool,seed);check(pair==drawItemOffers(pool,seed),"offers are cached seeded choices");
            check(pair[0]!=pair[1],"two distinct choices within one offer");
            for(auto item:pair){check(itemPoolWeight(pool,item)>0,"item belongs to destination pool");seen.insert(item);all.insert(item);}
        }
        for(const auto &item:defaultMechanics()->items())
            check(seen.contains(item.id)==(itemPoolWeight(pool,item.id)>0),"all eligible namespaced items represented");
    }
    // Skatole currently supplies only the Pooter reaction contract. Keep it
    // outside rewards until its other fly effects are ported, and reject any
    // accidental pool leak. H17's explicit-grant 1up dependency is also outside
    // natural pools until item/reward distributions are selected.
    const auto dependency=parseItemKey("isaac:collectible:9");
    check(!all.contains(dependency),"unfinished Skatole dependency stays outside natural pools");
    for(const auto &item:defaultMechanics()->items())
        check(all.contains(item.id)==(item.id!=dependency&&item.id!=parseItemKey("isaac:collectible:11")),"all supported items obtainable across pools");
    check(itemPoolWeights(ItemPool::Armory)!=itemPoolWeights(ItemPool::Shop)&&
          itemPoolWeights(ItemPool::Boss)!=itemPoolWeights(ItemPool::Bargain),"destinations have distinct weights and membership");
}
void reachability() {
    std::set<int> lengths;std::set<RoomService> services;int floors=0,surgeonsOnFourthFloor=0;
    for(uint64_t seed=0;seed<16;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);lengths.insert(plan.floorCount);
        for(int floor=0;floor<plan.floorCount;++floor) {
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++floors;
            check(run.arena.profile.floor==floor,"service unlocks retain the absolute floor number");
            // Zero keys and zero dynamite, after every optional purchase: traverse
            // only the free graph, treating combat clearance as the progression gate.
            std::vector<bool> reached(run.rooms.size());std::queue<int> pending;pending.push(0);reached[0]=true;
            while(!pending.empty()) {
                const int room=pending.front();pending.pop();
                for(int link:run.arena.rooms[size_t(room)].passages) {
                    const auto &p=run.arena.passages[size_t(link)];
                    if(p.locked)continue;
                    const int next=p.rooms[0]==room?p.rooms[1]:p.rooms[0];
                    if(!reached[size_t(next)]){reached[size_t(next)]=true;pending.push(next);}
                }
            }
            check(reached.back(),"boss reachable with all optional resources spent");
            if(run.storyRoomIndex()>=0)check(reached[size_t(run.storyRoomIndex())],"mandatory evidence never costs keys/bombs");
            int count=0,combat=0;
            std::set<int> traderRooms;
            for(int i=0;i<run.arena.roomCount();++i) {
                const auto &r=run.arena.rooms[size_t(i)];combat+=r.kind==RoomKind::Combat;
                if(r.kind==RoomKind::Shop||r.kind==RoomKind::Service) {
                    const int physicalRoom=run.arena.roomAt(r.objective);
                    check(physicalRoom==i&&traderRooms.insert(physicalRoom).second,"each trader occupies its own room");
                    check((i==run.arena.shopRoom)==(r.kind==RoomKind::Shop),"shop and specialist roles never share a room");
                }
                if(r.vacantServiceSite) {
                    check(r.kind==RoomKind::Empty&&r.service==RoomService::None&&run.roomEnemies(i).empty(),"removed service leaves a quiet room without a trader");
                }
                if(r.kind==RoomKind::Service) {
                    check(r.service==RoomService::Surgeon||r.service==RoomService::Smuggler,"only retained services generate");
                    ++count;services.insert(r.service);
                    check(floor>=3||r.service!=RoomService::Surgeon,"no doctor on floors one through three");
                    if(floor==3&&r.service==RoomService::Surgeon)++surgeonsOnFourthFloor;
                    check(reached[size_t(i)]&&i!=0&&i!=2&&i!=3&&r.story==StoryRoom::None,"optional trade protects story/legacy sites");
                    check(run.roomEnemies(i).empty(),"peaceful service room");
                    check(!run.arena.path(r.center,r.objective,.48f).empty(),"trader physically approachable");
                }
                if(r.kind==RoomKind::Power)for(auto item:run.rooms[size_t(i)].offers)
                    check(itemPoolWeight(ItemPool::Armory,item)>0,"armory uses armory pool");
            }
            check(count>=0&&count<=2&&combat>=3,"small optional subset within existing room budget");
            for(int i=1;i<=2;++i)check(itemPoolWeight(ItemPool::Shop,run.shopOffers[size_t(i)].item)>0,"shop uses utility pool");
            for(auto item:run.rooms.back().offers)check(itemPoolWeight(ItemPool::Boss,item)>0,"boss has its own rewards");
            const auto pos=run.rewardPosition(run.finalRoom());
            check(!run.arena.blocked(pos,1.1f)&&distance(pos,run.arena.exit)>=4&&distance(pos,run.arena.rooms.back().objective)>=4,"boss reward separated from evidence/exit");
        }
    }
    check(lengths.size()==5&&services.size()==2,"all run lengths and optional functions occur");
    check(surgeonsOnFourthFloor>0,"doctors can first appear on floor four");
    std::cout<<"Validated "<<floors<<" actual floors with zero-resource mandatory routes\n";
}
void enterService(Simulation &run,RoomService service) {
    int room=-1;for(int i=0;i<run.arena.roomCount();++i)if(run.arena.rooms[size_t(i)].kind==RoomKind::Service){room=i;break;}
    if(room<0)for(int i=1;i<run.arena.roomCount()-1;++i)if(run.arena.rooms[size_t(i)].vacantServiceSite) {
        room=i;run.arena.rooms[size_t(i)].kind=RoomKind::Service;run.arena.rooms[size_t(i)].vacantServiceSite=false;break;
    }
    check(room>=0,"transaction fixture has a reachable service site");
    run.arena.rooms[size_t(room)].service=service;run.jumpDebug(room);
    run.player.position=run.arena.rooms[size_t(room)].objective;run.openShop();check(run.shopOpen,"service opens through shop modal");
}
void removedSite() {
    Simulation run(4,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
        defaultMechanics(),1.1f,7,9,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{});
    int count=0;
    for(int i=0;i<run.arena.roomCount();++i)if(run.arena.rooms[size_t(i)].vacantServiceSite) {
        ++count;const auto &r=run.arena.rooms[size_t(i)];
        check(r.kind==RoomKind::Empty&&r.service==RoomService::None&&r.sourceHeartTemplate<0&&r.sourceCombatTemplate<0&&r.sourceObstacleTemplate<0,"former exchange stays quiet with production source layouts enabled");
        run.jumpDebug(i);run.player.position=r.objective;run.openShop();
        const auto keys=run.keys,bombs=run.dynamite;const auto money=run.money();
        check(!run.shopOpen&&!run.buyShop(0)&&!run.buyShop(1)&&run.keys==keys&&run.dynamite==bombs&&run.money()==money,"removed trader cannot open or convert resources");
    }
    check(count==1,"recorded former exchange is exercised");
}
void transactions() {
    WorldState world;world.money=100;
    Simulation surgeon(6,1,world,MissionTheme::Canyon);enterService(surgeon,RoomService::Surgeon);
    check(!surgeon.buyShop(0),"cannot pay for wasted healing at full HP");
    surgeon.player.hp=1;check(surgeon.buyShop(0)&&surgeon.player.hp==6&&surgeon.money()==80,"explicit healing price and cap");
    check(surgeon.buyShop(1)&&surgeon.player.maxHp==8&&surgeon.player.hp==8&&surgeon.money()==45,"finite expedition vitality improvement");
    check(!surgeon.buyShop(1),"tonic not repeatable");
    Simulation deal(6,1,world,MissionTheme::Canyon);enterService(deal,RoomService::Smuggler);
    deal.rooms[size_t(deal.room)].offers={ItemId::Judas,ItemId::Cap};deal.player.hp=3;
    check(deal.bargainMaxHealth(0)==2&&deal.serviceOffer(0).cost.find("1 RED CONTAINER")!=std::string::npos,"exact preview includes Judas's extra tax");
    check(deal.buyShop(0)&&deal.player.maxHp==2&&deal.player.hp==2&&deal.itemStacks(ItemId::Judas)==1,"preview agrees with actual cost");
    check(!deal.buyShop(1),"bargain alternatives mutually exclusive");
    deal.closeShop();deal.startBoss();deal.killAll();deal.step({});
    deal.floorExitRequested=true;check(deal.advanceFloor(),"advance after service purchase");
    check(deal.player.maxHp==2&&deal.itemStacks(ItemId::Judas)==1,"health sacrifice and item persist between floors");
    enterService(deal,RoomService::Smuggler);deal.rooms[size_t(deal.room)].offers={ItemId::Judas,ItemId::Cap};
    deal.player.maxHp=1;deal.player.hp=1;
    check(!deal.buyShop(0)&&!deal.buyShop(1)&&deal.player.hp==1,"low maximum HP cannot create lethal menu transaction");
    deal.player.maxHp=4;check(deal.buyShop(1)&&deal.player.maxHp==2&&deal.player.hp==1,"nonfatal exact lower boundary");
    Simulation reward(1866,1,{},MissionTheme::Canyon);reward.startBoss();reward.killAll();reward.step({});
    check(reward.rewardAvailable(reward.room),"defeated boss opens optional item choice");
    reward.player.position=reward.rewardPosition(reward.room);reward.interact();check(reward.rewardOpen,"boss reward approachable");
    auto pair=reward.offers;reward.closeShop();reward.interact();check(reward.offers==pair,"leaving reward does not reroll");
    reward.chooseReward(0);check(reward.items.size()==1&&!reward.rewardAvailable(reward.room),"one of two boss items taken once");
    reward.interact();reward.chooseReward(1);check(reward.items.size()==1,"cannot take both boss rewards");
    check(reward.canUseFloorExit(),"optional boss reward does not gate floor exit");
}
}
int main(int argc,char **argv){try{if(argc<2||std::string(argv[1])!="--services-only")pools();removedSite();transactions();reachability();std::cout<<"PASS optional rooms, resource reachability, finite economy and distinct pools\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
