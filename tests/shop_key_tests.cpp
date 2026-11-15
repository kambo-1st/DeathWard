#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceShopHeart.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *message){if(!value)throw std::runtime_error(message);}
Simulation generated(uint64_t seed=69,float scale=1.1f,int minimum=7,int maximum=9,float routes=.26f) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,
        ExpeditionPacing::Compact,defaultMechanics(),scale,minimum,maximum,routes,true,1,true,true,true,true,true);
}
int stock(const Simulation &run) {
    return int(std::count_if(run.keyPickups.begin(),run.keyPickups.end(),[](const auto &key){return key.shopStock&&key.timing.collectible();}));
}
void enter(Simulation &run){run.jumpDebug(run.arena.shopRoom);check(stock(run)==1,"one ordinary key on display");}
void touch(Simulation &run){run.player.position=run.shopKeyPosition();run.player.position.y=.85f;run.step({});}
void nativePrices() {
    const auto root=std::filesystem::path(__FILE__).parent_path().parent_path();
    std::ifstream file(root/"docs/reports/isaac-first-floor-parity/d12b-shop-key/source/native-prices.csv");
    std::string line;std::getline(file,line);int cases=0;
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);
        uint64_t seed;int variant,subtype,slot,price;
        check(bool(row>>seed>>variant>>subtype>>slot>>price),"native price row");
        check(variant==30&&subtype==1&&price==SourceShopKeyPrice,"native ordinary key price");++cases;
    }
    check(cases==30,"all native shop key cases consumed");
}
void placement() {
    int cases=0;
    for(uint64_t seed:{1ULL,69ULL,129ULL})for(auto dimensions:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}})for(float route:{.25f,1.f,2.f}) {
        const auto [scale,minimum,maximum]=dimensions;auto run=generated(seed,scale,minimum,maximum,route);enter(run);
        const auto &room=run.arena.rooms[size_t(run.room)];const auto at=run.shopKeyPosition();
        check(planarDistance(at,sourceHeartCell(room,5,4))<.0001f,"recorded first stock slot");
        check(planarDistance(at,run.shopHeartPosition())>2,"separate heart/key contact regions");
        check(!run.arena.blocked(at,.48f)&&!run.arena.path(room.entry,at,.48f).empty(),"key reachable from entrance");
        for(const auto &key:run.arena.keys)check(planarDistance(at,key.position)>1.5f,"mandatory key cannot overlap shop key");
        check(run.roomClear&&run.enemies.empty()&&room.passages.size()==1,"peaceful optional shop retained");++cases;
    }
    std::cout<<"PASS "<<cases<<" key/heart placement and reachability cases\n";
}
void transactions() {
    for(int keys:{0,98,99})for(int coins:{0,4,5,8}) {
        auto run=generated();enter(run);run.keys=keys;run.moneyCollected=uint64_t(coins);run.player.hp=4;
        const auto combat=run.combatRng.state,reward=run.rewardRng.state;touch(run);
        const bool bought=keys<99&&coins>=5;
        check(run.shopKeySold==bought&&run.keys==keys+int(bought),"one key or capped/refused unchanged");
        check(run.moneySpent==uint64_t(bought?5:0)&&run.money()==uint64_t(coins-(bought?5:0)),"atomic exact coin payment");
        check(run.player.hp==4&&!run.shopHeartSold,"key cannot collect or charge for heart");
        check(run.combatRng.state==combat&&run.rewardRng.state==reward,"purchase preserves RNG streams");
        if(bought) {
            for(int n=0;n<90;++n)run.step({});check(stock(run)==0&&run.keys==keys+1&&run.moneySpent==5,"collection animation pays once");
            run.jumpDebug(0);run.jumpDebug(run.arena.shopRoom);check(stock(run)==0&&run.shopKeySold,"sold revisit stays sold");
        }
    }
    for(bool keyFirst:{false,true}) {
        auto run=generated();enter(run);run.player.hp=4;run.moneyCollected=8;
        const auto heart=[&]{run.player.position=run.shopHeartPosition();run.player.position.y=.85f;run.step({});};
        if(keyFirst){touch(run);heart();}else{heart();touch(run);}
        check(run.shopHeartSold&&run.shopKeySold&&run.keys==1&&run.player.hp==6&&run.moneySpent==8,"both purchase orders pay only their own prices");
    }
}
void configurationAndGates() {
    auto run=generated();enter(run);run.keys=0;run.moneyCollected=8;
    run.shopOpen=true;touch(run);check(!run.shopKeySold,"modal prevents purchase");run.shopOpen=false;
    run.roomClear=false;touch(run);check(!run.shopKeySold,"combat prevents purchase");run.roomClear=true;
    run.dead=true;touch(run);check(!run.shopKeySold,"death prevents purchase");run.dead=false;
    run.shopKeyPrice=15;touch(run);check(!run.shopKeySold&&run.moneySpent==0,"live unaffordable price refuses");
    run.shopKeyPrice=0;touch(run);check(run.shopKeySold&&run.keys==1&&run.moneySpent==0,"free testing override grants once");
    run.shopKeyPrice=6;touch(run);check(run.keys==1&&run.moneySpent==0,"editing price cannot restock");
    run.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,false);
    check(!run.sourceShopKey&&stock(run)==0&&run.shopKeyPrice==6&&run.keys==1,"Apply removes key stock, preserves inventory/price");
    run.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,true);
    check(stock(run)==1&&!run.shopKeySold&&run.shopKeyPrice==6,"explicit Apply restores fresh stock");
    touch(run);check(run.shopKeySold&&run.keys==2&&run.moneySpent==6,"regenerated stock uses live price");
    run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.floorExitRequested=true;check(run.advanceFloor(),"next floor");
    check(run.keys==2&&run.sourceShopKey&&run.shopKeyPrice==6&&!run.hasSourceShop(run.arena.shopRoom),"key inventory/config persists; later shop unchanged");
    auto legacy=generated();legacy.sourceShopHeart=false;legacy.jumpDebug(legacy.arena.shopRoom);
    check(stock(legacy)==0,"additional key follows existing source-shop master policy");
}
void presets() {
    const auto root=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity";
    const auto hash=defaultMechanics()->fingerprint();
    const auto dir=std::filesystem::temp_directory_path()/("deathward-shop-key-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    for(bool enabled:{false,true})for(int price:{0,5,6,15}) {
        BalancePreset p{1,hash};p.sourceShopKey=enabled;p.shopKeyPrice=price;p.shopHeartPrice=4;p.save(dir/"preset.json");
        const auto loaded=BalancePreset::load(dir/"preset.json",hash);check(loaded.revision()==p.revision(),"independent stock/prices schema31 roundtrip");
    }
    for(auto path:{root/"d03-shooting/user-preset-2026-11-11.json",root/"d12a-shop-heart/shop-heart-preset.json"}) {
        auto p=BalancePreset::load(path,hash);check(p.sourceShopKey&&p.shopKeyPrice==5&&p.defaultZoomPercent==165,"old schemas migrate with accepted zoom");
    }
    std::filesystem::remove_all(dir);
}
}
int main(){try{nativePrices();placement();transactions();configurationAndGates();presets();std::cout<<"PASS native prices, cap/payment/refusals, both purchase orders, sold revisit, live price/Apply/floor and schema31 migration\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
