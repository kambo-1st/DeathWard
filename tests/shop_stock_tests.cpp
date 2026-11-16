#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceShopStock.hpp"
#include "world/SourceShopHeart.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
const ItemKey SteamSale{"isaac",ItemKind::Collectible,64};
Simulation make(uint64_t seed=7,float scale=1.1f,int low=7,int high=9,float route=.26f) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
        defaultMechanics(),scale,low,high,route,true,1,true,true,true,true,true,true);
}
void enter(Simulation &s){s.jumpDebug(s.arena.shopRoom);s.moneyCollected=20;s.player.hp=4;}
void touch(Simulation &s,Vector3 at){s.player.position=at;s.player.position.y=.85f;s.step({});}
void layouts() {
    int count=0;
    for(uint64_t seed:{2ULL,7ULL,19ULL})for(auto dims:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}})for(float route:{.25f,1.f,2.f}) {
        const auto [scale,low,high]=dims;auto s=make(seed,scale,low,high,route);enter(s);
        check(s.shopVariationActive(),"supported natural category pair");
        check(s.shopUpgradeSlot==(seed==7?0:1),"source slot order");
        check(s.shopHeartOffered()==(seed==2)&&s.shopKeyOffered()==(seed!=2),"source category selects heart or key");
        const auto a=s.shopUpgradePosition(),b=seed==2?s.shopHeartPosition():s.shopKeyPosition();
        check(planarDistance(a,b)>2,"stock contact regions disjoint");
        const auto &room=s.arena.rooms[size_t(s.room)];
        check(planarDistance(room.objective,room.center)<.0001f&&s.arena.blocked(add(room.center,{0,.85f,0}),.48f),"centered solid shop wagon");
        check(!s.arena.blocked(shopCartGeometry::reviewStart(room.center),.48f),"direct review starts beside cart");
        for(const auto &key:s.arena.keys)check(!sphereBox(key.position,.35f,shopCartGeometry::bounds(room.center)),"cart does not trap existing keys");
        for(auto at:{a,b}) {
            if(s.arena.blocked(at,.48f)||s.arena.path(room.entry,at,.48f).empty()) {
                std::cerr<<"placement seed="<<seed<<" scale="<<scale<<" range="<<low<<","<<high<<" route="<<route<<" at="<<at.x<<","<<at.z<<" blocked="<<s.arena.blocked(at,.48f)<<" entryBlocked="<<s.arena.blocked(room.entry,.48f)<<'\n';
                check(false,"all stock reachable in canyon size/route variants");
            }
            for(const auto &key:s.arena.keys)check(planarDistance(at,key.position)>1.5f,"mandatory keys distinct");
        }
        check(s.roomClear&&s.enemies.empty()&&room.passages.size()==1,"optional peaceful shop retained");++count;
    }
    auto fallback=make(69);enter(fallback);
    check(!fallback.shopVariationActive()&&fallback.shopKeyOffered()&&fallback.shopHeartOffered()&&fallback.shopDiscountSlot==-1,"unsupported native pair uses declared fixed fallback without sale reroll");
    auto sale=make(22);enter(sale);check(sale.shopUpgradeSlot==0&&sale.shopDiscountSlot==0&&sale.shopPrice(15,0)==7,"native random sale slot discounts before ownership");
    touch(sale,sale.shopUpgradePosition());check(sale.moneySpent==7&&sale.shopPrice(5,1)==3,"random sale and owned effect do not multiply");
    std::cout<<"PASS "<<count<<" generated slot/clearance/access cases plus unsupported and random-sale witnesses\n";
}
void purchase() {
    for(int funds:{0,14,15,20})for(bool itemFirst:{false,true}) {
        auto s=make();enter(s);s.moneyCollected=uint64_t(funds);
        if(!itemFirst)touch(s,s.shopKeyPosition());
        const int firstPrice=itemFirst?0:(funds>=5?5:0);
        touch(s,s.shopUpgradePosition());const bool bought=funds-firstPrice>=15;
        check(s.shopUpgradeSold==bought&&s.itemStacks(SteamSale)==size_t(bought),"collectible funds admission");
        if(itemFirst)touch(s,s.shopKeyPosition());
        const int keyPrice=itemFirst?(bought?3:5):5;
        const bool keyBought=itemFirst?(funds-(bought?15:0)>=keyPrice):funds>=5;
        check(s.moneySpent==uint64_t((bought?15:0)+(keyBought?keyPrice:0))&&s.keys==int(keyBought),"atomic price per purchase order");
        const auto paid=s.moneySpent;for(int i=0;i<40;++i)s.step({});
        s.jumpDebug(0);s.jumpDebug(s.arena.shopRoom);
        check(s.shopUpgradeSold==bought&&s.moneySpent==paid,"sold revisit no duplicate grant or charge");
    }
    auto s=make(2);enter(s);touch(s,s.shopUpgradePosition());
    check(s.shopPrice(3,s.shopHeartSlot)==2,"heart discount rounds up");touch(s,s.shopHeartPosition());
    check(s.player.hp==6&&s.moneySpent==17&&s.shopHeartSold,"discounted heart exact heal/payment");
    for(int copies=2;copies<=3;++copies){s.grant(SteamSale);check(s.shopPrice(15,0)==(copies==2?5:4),"owned copies use source count formula");}
    s.steamSaleDiscounts=false;check(s.shopPrice(15,0)==15,"live item effect comparison");
}
void lifecycle() {
    auto s=make();enter(s);
    s.shopOpen=true;touch(s,s.shopUpgradePosition());check(!s.shopUpgradeSold,"modal blocks");s.shopOpen=false;
    s.roomClear=false;touch(s,s.shopUpgradePosition());check(!s.shopUpgradeSold,"combat blocks");s.roomClear=true;
    s.dead=true;touch(s,s.shopUpgradePosition());check(!s.shopUpgradeSold,"dead blocks");s.dead=false;
    s.items.assign(256,SteamSale);touch(s,s.shopUpgradePosition());check(!s.shopUpgradeSold&&s.moneySpent==0,"full inventory refuses atomically");s.items.clear();
    s.shopUpgradePrice=30;touch(s,s.shopUpgradePosition());check(!s.shopUpgradeSold,"live price refuses");
    s.shopUpgradePrice=0;touch(s,s.shopUpgradePosition());check(s.shopUpgradeSold&&s.moneySpent==0&&s.itemStacks(SteamSale)==1,"free override grants once");
    s.shopUpgradePrice=16;s.steamSaleDiscounts=false;
    s.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,true,false);
    check(!s.shopVariationActive()&&s.itemStacks(SteamSale)==1&&s.shopUpgradePrice==16&&!s.steamSaleDiscounts,"Apply fixed stock keeps build/live options");
    s.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,false,true);
    check(s.shopVariationActive()&&!s.shopUpgradeSold&&!s.shopKeyOffered()&&s.itemStacks(SteamSale)==1,"Apply resets offering but disabled key is not rerolled");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor(),"floor advance");
    check(s.sourceShopVariation&&s.shopUpgradePrice==16&&!s.steamSaleDiscounts&&s.itemStacks(SteamSale)==1&&!s.hasSourceShop(s.arena.shopRoom),"carry config/item to later floor; legacy shop retained");
}
void cartMovement() {
    for(bool dodge:{false,true})for(int side=0;side<8;++side) {
        auto s=make();enter(s);const auto c=s.arena.rooms[size_t(s.room)].center;
        const Vector3 direction{std::cos(side*Pi/4),0,std::sin(side*Pi/4)};
        s.player.position=add(c,mul(direction,4));s.player.position.y=.85f;
        for(int tick=0;tick<100;++tick) {
            Input input;input.movement=mul(direction,-1);input.dodge=dodge&&tick==0;s.step(input);
            check(!s.arena.blocked(s.player.position,.48f),"walking/dodge cannot enter wagon");
        }
        if(side%2==0)check(dot(horizontal(sub(s.player.position,c)),direction)>0,"straight walking/dodge cannot cross wagon; diagonal sliding may route around it");
    }
    auto s=make();enter(s);const auto c=s.arena.rooms[size_t(s.room)].center;
    s.player.position=shopCartGeometry::reviewStart(c);
    for(int tick=0;tick<180;++tick){Input in;if(tick==0)in.moveTarget=c;s.step(in);}
    check(!s.arena.blocked(s.player.position,.48f)&&planarDistance(s.player.position,c)<2.1f,"click cart reaches an edge without collecting stock");
    check(!s.shopUpgradeSold&&!s.shopKeySold,"cart click never purchases unrelated stock");
    std::cout<<"PASS 16 walking/dodge directions and cart click approach\n";
}
void presets() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-stock-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto file=dir/"preset.json";const auto hash=defaultMechanics()->fingerprint();
    for(bool variation:{false,true})for(bool discounts:{false,true})for(int price:{0,15,30}) {
        BalancePreset p{1,hash};p.sourceShopVariation=variation;p.steamSaleDiscounts=discounts;p.shopUpgradePrice=price;p.save(file);
        check(BalancePreset::load(file,hash).revision()==p.revision(),"schema32 exact roundtrip");
    }
    const auto root=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity";
    for(auto path:{root/"d03-shooting/user-preset-2026-11-11.json",root/"d12b-shop-key/shop-key-preset.json"}) {
        const auto p=BalancePreset::load(path,hash);
        check(p.sourceShopVariation&&p.steamSaleDiscounts&&p.shopUpgradePrice==15&&p.defaultZoomPercent==165&&p.playerSpeed==1,"exact old catalog/schema migration retains accepted view/speed");
    }
    BalancePreset valid{1,hash};const auto bytes=valid.json();
    for(auto [from,to]:{std::pair{"\"shop_upgrade_price\": 15}","\"shop_upgrade_price\": 15.5}"},std::pair{"\"source_shop_variation\": true","\"source_shop_variation\": 1"},std::pair{"53ab4ae76cff6d8","bad-catalog"}}) {
        auto invalid=bytes;const auto at=invalid.find(from);check(at!=std::string::npos,"negative fixture located");invalid.replace(at,std::string(from).size(),to);
        std::ofstream(file)<<invalid;bool rejected=false;try{(void)BalancePreset::load(file,hash);}catch(...){rejected=true;}check(rejected,"invalid preset fails closed");
    }
    std::filesystem::remove_all(dir);
}
}
int main(){try{layouts();purchase();lifecycle();cartMovement();presets();std::cout<<"PASS stock transactions, discounts/copies, gates, sold revisit, Apply/floors and preset migration\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
