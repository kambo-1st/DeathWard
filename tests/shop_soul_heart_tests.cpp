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
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
const ItemKey SteamSale{"isaac",ItemKind::Collectible,64};
Simulation make(uint64_t seed=18,float scale=1.1f,int low=7,int high=9,float route=.26f) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
        defaultMechanics(),scale,low,high,route,true,1,true,true,true,true,true,true);
}
void enter(Simulation &s){s.jumpDebug(s.arena.shopRoom);s.moneyCollected=20;}
void touch(Simulation &s,Vector3 at){s.player.position=at;s.player.position.y=.85f;s.step({});}
void native() {
    const auto source=Root/"docs/reports/isaac-first-floor-parity/d12e-shop-soul-heart/source";
    std::ifstream file(source/"native-prices.csv");std::string line;std::getline(file,line);int count=0;
    const auto defaults=make();
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);
        uint64_t seed;int variant,subtype,slot,price;check(bool(row>>seed>>variant>>subtype>>slot>>price),"native price row");
        check(variant==10&&subtype==3&&price==defaults.shopSoulHeartPrice&&price==BalancePreset{}.shopSoulHeartPrice,"native soul-heart price matches runtime/preset");++count;
    }
    check(count==30,"30 native price cases");count=0;
    std::ifstream health(source/"native-soul-health.csv");std::getline(health,line);
    while(std::getline(health,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);SourcePlayerHealth h;
        int admitted,amount,afterSoul,afterRed;
        check(bool(row>>h.maxRed>>h.red>>h.soul>>h.bone>>h.broken>>admitted>>amount>>afterSoul>>afterRed),"native health row");
        const int previous=h.soul;
        h.addSoul(2);
        check((h.soul!=previous)==bool(admitted)&&h.soul==afterSoul&&h.red==afterRed,"native admission and capped soul grant");
        check(amount==(admitted?2:0),"source full-soul quantity");++count;
    }
    check(count==66,"all native capacity/health cases consumed");
    std::cout<<"PASS 30 native prices and 66 source admission/health cases\n";
}
void placements() {
    int count=0;
    for(uint64_t seed:{18ULL,41ULL,43ULL})for(auto dims:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}})for(float route:{.25f,1.f,2.f}) {
        const auto [scale,low,high]=dims;auto s=make(seed,scale,low,high,route);enter(s);
        check(s.shopVariationActive()&&s.shopHeartOffered()&&s.shopHeartKind==HeartKind::Soul&&!s.shopKeyOffered()&&!s.shopBombOffered(),"natural category4 supplies soul heart");
        check(s.shopHeartSlot==(seed==41?1:0),"source stock slot order");
        const auto at=s.shopHeartPosition();const auto &r=s.arena.rooms[size_t(s.room)];
        check(!s.arena.blocked(at,.48f)&&!s.arena.path(r.entry,at,.48f).empty()&&planarDistance(at,s.shopUpgradePosition())>2,"cart clearance and entrance route");
        const auto stock=std::find_if(s.heartPickups.begin(),s.heartPickups.end(),[](const auto &p){return p.shopStock;});
        check(stock!=s.heartPickups.end()&&std::count_if(s.heartPickups.begin(),s.heartPickups.end(),[](const auto &p){return p.shopStock;})==1&&
            stock->room==s.room&&stock->kind==HeartKind::Soul&&stock->sourceSubtype==3&&stock->timing.collectible(),"one idle blue source heart in the shop; other-room hearts retained");++count;
    }
    std::cout<<"PASS "<<count<<" natural soul-heart size/range/route placements\n";
}
void transactions() {
    for(int halves:{0,17,18})for(int coins:{0,4,5,20})for(bool discount:{false,true}) {
        auto s=make();enter(s);s.moneyCollected=uint64_t(coins);
        auto health=s.player.sourceHealth();health.soul=halves;s.player.setSourceHealth(health);
        if(discount)s.grant(SteamSale);
        const int price=discount?3:5;const bool bought=halves<18&&coins>=price;
        const auto rewardRng=s.rewardRng.state;touch(s,s.shopHeartPosition());
        check(s.shopHeartSold==bought&&s.moneySpent==uint64_t(bought?price:0),"capacity/funds reject without payment; exact discount");
        check(s.player.hp==6&&s.player.soulHearts==(bought?std::min(18,halves+2):halves),"protective half/full gain even at full red health");
        check(s.rewardRng.state==rewardRng,"no purchase RNG draws");
        const auto paid=s.moneySpent;
        for(int n=0;n<40;++n)s.step({});s.jumpDebug(0);s.jumpDebug(s.arena.shopRoom);
        check(s.shopHeartSold==bought&&s.moneySpent==paid,"once-only charge and sold revisit");
        if(bought)check(std::none_of(s.heartPickups.begin(),s.heartPickups.end(),[](const auto &p){return p.shopStock;}),"sold actor absent");
    }
    for(bool itemFirst:{false,true}) {
        auto s=make();enter(s);
        if(itemFirst)touch(s,s.shopUpgradePosition());
        touch(s,s.shopHeartPosition());if(!itemFirst)touch(s,s.shopUpgradePosition());
        check(s.shopHeartSold&&s.shopUpgradeSold&&s.player.soulHearts==2&&s.moneySpent==uint64_t(itemFirst?18:20),"either purchase order with immediate owned discount");
        s.takeHeartDamage(1);check(s.player.hp==6&&s.player.soulHearts==1,"purchased protection absorbs damage before red health");
    }
    for(bool emptyRed:{false,true}) {
        auto s=make();enter(s);auto h=s.player.sourceHealth();h.maxRed=24;h.red=emptyRed?4:24;s.player.setSourceHealth(h);touch(s,s.shopHeartPosition());
        check(!s.shopHeartSold&&s.moneySpent==0&&s.player.hp==h.red,"full containers refuse soul purchase regardless of red injury");
    }
    auto s=make();enter(s);auto h=s.player.sourceHealth();h.soul=2;h.blackMask=1;h.bone=1;h.boneMask=4;h.broken=1;s.player.setSourceHealth(h);touch(s,s.shopHeartPosition());
    check(s.shopHeartSold&&s.player.soulHearts==4&&s.player.sourceHealth().blackMask==1&&s.player.boneHearts==1&&s.player.brokenHearts==1,"existing black/bone/broken health retained");
}
void gatesAndLifecycle() {
    auto s=make();enter(s);
    s.shopOpen=true;touch(s,s.shopHeartPosition());check(!s.shopHeartSold,"modal blocks");s.shopOpen=false;
    s.roomClear=false;touch(s,s.shopHeartPosition());check(!s.shopHeartSold,"combat blocks");s.roomClear=true;
    s.dead=true;touch(s,s.shopHeartPosition());check(!s.shopHeartSold,"death blocks");s.dead=false;
    s.heartPickups.front().timing.appear(1);touch(s,s.shopHeartPosition());check(!s.shopHeartSold,"appearance not admitted early");
    s.heartPickups.front().timing={};s.shopSoulHeartPrice=15;s.moneyCollected=14;touch(s,s.shopHeartPosition());check(!s.shopHeartSold,"live unaffordable price");
    s.shopHeartPrice=0;touch(s,s.shopHeartPosition());check(!s.shopHeartSold,"red-heart price independent");
    s.shopSoulHeartPrice=0;touch(s,s.shopHeartPosition());check(s.shopHeartSold&&s.moneySpent==0&&s.player.soulHearts==2,"zero-price override once");
    s.shopSoulHeartPrice=6;touch(s,s.shopHeartPosition());check(s.player.soulHearts==2,"price edit never restocks");
    s.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,true,false);
    check(s.shopHeartKind==HeartKind::Red&&s.shopSoulHeartPrice==6&&s.player.soulHearts==2,"Apply fixed pair preserves health and price");
    s.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,true,true);
    check(s.shopHeartKind==HeartKind::Soul&&!s.shopHeartSold&&s.shopSoulHeartPrice==6&&s.player.soulHearts==2,"Apply fresh source soul offering");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;const auto before=s.player.soulHearts;
    check(s.advanceFloor()&&s.player.soulHearts==before&&s.shopSoulHeartPrice==6&&!s.hasSourceShop(s.arena.shopRoom),"health/price carry; later legacy shop retained");
    auto delayed=make();delayed.heartPickups.resize(1024);for(auto &p:delayed.heartPickups)p.room=-1;enter(delayed);
    check(!delayed.shopHeartDelivered,"actor-capacity refusal is deferred");delayed.heartPickups.clear();delayed.step({});
    check(delayed.shopHeartDelivered&&delayed.heartPickups.size()==1&&!delayed.shopHeartSold,"capacity release births once without reroll/payment");
}
void presets() {
    const auto dir=std::filesystem::temp_directory_path()/("deathward-shop-soul-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto file=dir/"preset.json";const auto hash=defaultMechanics()->fingerprint();
    for(int price:{0,5,6,15}) {
        BalancePreset p{1,hash};p.shopSoulHeartPrice=price;p.shopHeartPrice=4;p.shopBombPrice=6;p.save(file);
        check(BalancePreset::load(file,hash).revision()==p.revision(),"independent heart/bomb/soul price roundtrip");
    }
    for(const char *relative:{"d03-shooting/user-preset-2026-11-11.json","d12d-shop-dynamite/shop-dynamite-preset.json"}) {
        auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity"/relative,hash);
        check(p.shopSoulHeartPrice==5&&p.defaultZoomPercent==165&&p.playerSpeed==1,"old schema migration keeps accepted settings");
    }
    BalancePreset valid{1,hash};const auto bytes=valid.json();
    for(auto [from,to]:{std::pair{"\"shop_soul_heart_price\": 5, \"shop_bomb_price\": 5, \"shop_upgrade_price\"","\"shop_soul_heart_price\": 5.5, \"shop_bomb_price\": 5, \"shop_upgrade_price\""},std::pair{"\"shop_soul_heart_price\": 5, \"shop_bomb_price\": 5, \"shop_stock_policy\"","\"shop_soul_heart_price\": 6, \"shop_bomb_price\": 5, \"shop_stock_policy\""}}) {
        // Numeric resolved and source reference values have distinct validation.
        auto invalid=bytes;const auto at=invalid.find(from);check(at!=std::string::npos,"negative fixture located");invalid.replace(at,std::string(from).size(),to);
        std::ofstream(file)<<invalid;bool rejected=false;try{(void)BalancePreset::load(file,hash);}catch(...){rejected=true;}check(rejected,"invalid price/reference rejected");
    }
    std::filesystem::remove_all(dir);
}
}
int main(){try{native();placements();transactions();gatesAndLifecycle();presets();std::cout<<"PASS soul-heart purchase/discount/cap/partial-health/damage/gates/revisit/Apply/floor/preset boundaries\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
