#include "combat/Simulation.hpp"
#include "items/ItemPools.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
void pools() {
    std::set<ItemId> all;
    for(auto pool:{ItemPool::Armory,ItemPool::Shop,ItemPool::Boss,ItemPool::Bargain}) {
        std::set<ItemId> seen;
        for(uint64_t seed=0;seed<1024;++seed) {
            auto pair=drawItemOffers(pool,seed);check(pair==drawItemOffers(pool,seed),"offers are cached seeded choices");
            check(pair[0]!=pair[1],"two distinct choices within one offer");
            for(auto item:pair){check(itemPoolWeights(pool)[size_t(item)]>0,"item belongs to destination pool");seen.insert(item);all.insert(item);}
        }
        for(int i=0;i<ItemCount;++i)check(seen.contains(ItemId(i))==(itemPoolWeights(pool)[size_t(i)]>0),"all eligible items represented");
    }
    check(all.size()==ItemCount,"all eleven items obtainable across pools");
    check(itemPoolWeights(ItemPool::Armory)!=itemPoolWeights(ItemPool::Shop)&&
          itemPoolWeights(ItemPool::Boss)!=itemPoolWeights(ItemPool::Bargain),"destinations have distinct weights and membership");
}
void reachability() {
    std::set<int> lengths;std::set<RoomService> services;int floors=0;
    for(uint64_t seed=0;seed<16;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);lengths.insert(plan.floorCount);
        for(int floor=0;floor<plan.floorCount;++floor) {
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++floors;
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
            for(int i=0;i<run.arena.roomCount();++i) {
                const auto &r=run.arena.rooms[size_t(i)];combat+=r.kind==RoomKind::Combat;
                if(r.kind==RoomKind::Service) {
                    ++count;services.insert(r.service);
                    check(reached[size_t(i)]&&i!=0&&i!=2&&i!=3&&r.story==StoryRoom::None,"optional trade protects story/legacy sites");
                    check(run.roomEnemies(i).empty(),"peaceful service room");
                    check(!run.arena.path(r.center,r.objective,.48f).empty(),"trader physically approachable");
                }
                if(r.kind==RoomKind::Power)for(auto item:run.rooms[size_t(i)].offers)
                    check(itemPoolWeights(ItemPool::Armory)[size_t(item)]>0,"armory uses armory pool");
            }
            check(count>=1&&count<=2&&combat>=3,"small optional subset within existing room budget");
            for(int i=1;i<=2;++i)check(itemPoolWeights(ItemPool::Shop)[size_t(run.shopOffers[size_t(i)].item)]>0,"shop uses utility pool");
            for(auto item:run.rooms.back().offers)check(itemPoolWeights(ItemPool::Boss)[size_t(item)]>0,"boss has its own rewards");
            const auto pos=run.rewardPosition(run.finalRoom());
            check(!run.arena.blocked(pos,1.1f)&&distance(pos,run.arena.exit)>=4&&distance(pos,run.arena.rooms.back().objective)>=4,"boss reward separated from evidence/exit");
        }
    }
    check(lengths.size()==5&&services.size()==3,"all run lengths and optional functions occur");
    std::cout<<"Validated "<<floors<<" actual floors with zero-resource mandatory routes\n";
}
void enterService(Simulation &run,RoomService service) {
    int room=-1;for(int i=0;i<run.arena.roomCount();++i)if(run.arena.rooms[size_t(i)].kind==RoomKind::Service){room=i;break;}
    check(room>=0,"generated service room exists");
    run.arena.rooms[size_t(room)].service=service;run.jumpDebug(room);
    run.player.position=run.arena.rooms[size_t(room)].objective;run.openShop();check(run.shopOpen,"service opens through shop modal");
}
void transactions() {
    WorldState world;world.money=100;
    Simulation exchange(1866,1,world,MissionTheme::Canyon);enterService(exchange,RoomService::Exchange);
    exchange.keys=2;exchange.dynamite=3;
    check(exchange.buyShop(0)&&exchange.keys==0&&exchange.dynamite==6,"two keys buy three sticks");
    check(exchange.buyShop(1)&&exchange.dynamite==5&&exchange.money()==104,"one stick buys four coins");
    for(int i=0;i<100;++i)check(!exchange.buyShop(i%4),"no repeatable conversion loop or hidden third offer");
    const auto service=exchange.room;exchange.closeShop();exchange.jumpDebug(0);exchange.jumpDebug(service);
    exchange.player.position=exchange.arena.rooms[size_t(service)].objective;exchange.openShop();
    check(!exchange.buyShop(0)&&!exchange.buyShop(1),"revisits retain exhausted offers");
    check(!exchange.shopOffers[3].sold,"service stock separate from shop stock");
    Simulation surgeon(1866,1,world,MissionTheme::Canyon);enterService(surgeon,RoomService::Surgeon);
    check(!surgeon.buyShop(0),"cannot pay for wasted healing at full HP");
    surgeon.player.hp=25;check(surgeon.buyShop(0)&&surgeon.player.hp==85&&surgeon.money()==80,"explicit healing price and cap");
    check(surgeon.buyShop(1)&&surgeon.player.maxHp==115&&surgeon.player.hp==100&&surgeon.money()==45,"finite expedition vitality improvement");
    check(!surgeon.buyShop(1),"tonic not repeatable");
    Simulation deal(1866,1,world,MissionTheme::Canyon);enterService(deal,RoomService::Smuggler);
    deal.rooms[size_t(deal.room)].offers={ItemId::Judas,ItemId::Cap};deal.player.hp=50;
    check(deal.bargainMaxHealth(0)==64&&deal.serviceOffer(0).cost.find("36 MAX HP")!=std::string::npos,"exact preview includes Judas's extra tax");
    check(deal.buyShop(0)&&deal.player.maxHp==64&&deal.player.hp==50&&deal.itemStacks(ItemId::Judas)==1,"preview agrees with actual cost");
    check(!deal.buyShop(1),"bargain alternatives mutually exclusive");
    deal.closeShop();deal.startBoss();deal.killAll();deal.step({});
    deal.floorExitRequested=true;check(deal.advanceFloor(),"advance after service purchase");
    check(deal.player.maxHp==64&&deal.itemStacks(ItemId::Judas)==1,"health sacrifice and item persist between floors");
    enterService(deal,RoomService::Smuggler);deal.rooms[size_t(deal.room)].offers={ItemId::Judas,ItemId::Cap};
    deal.player.maxHp=39;deal.player.hp=1;
    check(!deal.buyShop(0)&&!deal.buyShop(1)&&deal.player.hp==1,"low maximum HP cannot create lethal menu transaction");
    deal.player.maxHp=40;check(deal.buyShop(1)&&deal.player.maxHp==20&&deal.player.hp==1,"nonfatal exact lower boundary");
    Simulation reward(1866,1,{},MissionTheme::Canyon);reward.startBoss();reward.killAll();reward.step({});
    check(reward.rewardAvailable(reward.room),"defeated boss opens optional item choice");
    reward.player.position=reward.rewardPosition(reward.room);reward.interact();check(reward.rewardOpen,"boss reward approachable");
    auto pair=reward.offers;reward.closeShop();reward.interact();check(reward.offers==pair,"leaving reward does not reroll");
    reward.chooseReward(0);check(reward.items.size()==1&&!reward.rewardAvailable(reward.room),"one of two boss items taken once");
    reward.interact();reward.chooseReward(1);check(reward.items.size()==1,"cannot take both boss rewards");
    check(reward.canUseFloorExit(),"optional boss reward does not gate floor exit");
}
}
int main(){try{pools();transactions();reachability();std::cout<<"PASS optional rooms, resource reachability, finite economy and distinct pools\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
