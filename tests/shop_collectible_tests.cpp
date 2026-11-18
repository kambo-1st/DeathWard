#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceShopStock.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *why){if(!value)throw std::runtime_error(why);}
const ItemKey Bogo{"isaac",ItemKind::Collectible,250},Sale{"isaac",ItemKind::Collectible,64};
Simulation make(uint64_t seed=4,int pool=1,float size=1.1f,int low=7,int high=9,float route=.26f) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
        defaultMechanics(),size,low,high,route,true,1,true,true,true,true,true,true,pool);
}
void enter(Simulation &s){s.jumpDebug(s.arena.shopRoom);s.moneyCollected=20;s.player.hp=4;}
void touch(Simulation &s,Vector3 at){s.player.position=at;s.player.position.y=.85f;s.step({});}
void native() {
    const auto root=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d12f-shop-collectibles/source";
    std::ifstream in(root/"native-choice.csv");std::string line;std::getline(in,line);int cases=0;
    while(std::getline(in,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);uint32_t seed,after;int item;
        check(bool(row>>seed>>after>>item),"native choice row");check(sourceShopCollectibleChoice(seed)==item,"actual native float weighted choice");++cases;
    }
    check(cases==524,"native choice evidence complete, including float boundaries");
    in=std::ifstream(root/"native-bogo.csv");std::getline(in,line);int actors=0;
    while(std::getline(in,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int copies,variant,subtype,outVariant,outSubtype;
        check(bool(row>>copies>>variant>>subtype>>outVariant>>outSubtype),"native BOGO row");
        if(variant!=40||subtype>2)continue;
        auto s=make();for(int n=0;n<copies;++n)s.grant(Bogo);
        check(s.spawnOrdinaryBomb(s.player.position,subtype,42,true),"ordinary actor admission");
        check(s.bombPickups.back().sourceSubtype==outSubtype&&outVariant==40,"native subtype consumed by actual actor");
        const int before=s.dynamite;touch(s,s.player.position);
        check(s.dynamite==before+outSubtype,"actual quantity");++actors;
    }
    check(actors==8,"all supported native BOGO cases consumed");
    std::cout<<"PASS "<<cases<<" native choices / "<<actors<<" native ordinary BOGO actor cases\n";
}
void transactions() {
    for(int pool:{0,2})for(int funds:{0,14,15,20}) {
        auto s=make(4,pool);enter(s);s.moneyCollected=funds;
        const auto item=pool==0?Sale:Bogo;const auto before=s.player.attributes;
        touch(s,s.shopUpgradePosition());check(s.shopUpgradeSold==(funds>=15),"funds gate");
        check(s.itemStacks(item)==size_t(funds>=15)&&s.moneySpent==uint64_t(funds>=15?15:0),"one atomic correct item purchase");
        check(s.player.attributes.speed==before.speed&&s.player.attributes.damage==before.damage,"accepted balance unchanged");
        const auto paid=s.moneySpent;s.jumpDebug(0);s.jumpDebug(s.arena.shopRoom);touch(s,s.shopUpgradePosition());
        check(s.moneySpent==paid&&s.itemStacks(item)==size_t(funds>=15),"sold revisit never duplicates");
    }
    auto s=make(4,2);enter(s);check(s.bombPickups.back().sourceSubtype==1,"unowned shop bomb single");
    touch(s,s.shopUpgradePosition());check(s.itemStacks(Bogo)==1&&s.shopPrice(5,s.shopBombSlot)==5,"BOGO does not discount");
    check(s.bombPickups.back().sourceSubtype==1,"existing pickup immutable");
    touch(s,s.shopBombPosition());check(s.dynamite==4&&s.money()==0,"existing single still grants one");
    s.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true,true,true,0);
    check(s.shopUpgradeItem==64&&s.itemStacks(Bogo)==1&&s.moneySpent==20&&!s.shopUpgradeSold,"Apply retains build/spending and resets selected stock");
    check(s.bombPickups.back().sourceSubtype==2,"owned BOGO affects new shop actor after explicit regeneration");
    s.moneyCollected=40;touch(s,s.shopUpgradePosition());check(s.itemStacks(Sale)==1&&s.shopPrice(5,s.shopBombSlot)==3,"Sale works alongside BOGO");
    s.dynamite=98;touch(s,s.shopBombPosition());check(s.dynamite==99&&s.moneySpent==38,"double clamps at99 with one discounted payment");
    const auto spent=s.moneySpent;s.jumpDebug(0);s.jumpDebug(s.arena.shopRoom);touch(s,s.shopBombPosition());check(s.moneySpent==spent,"double never pays twice");
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor(),"advance floor");
    check(s.itemStacks(Bogo)==1&&s.shopCollectiblePool==0,"owned effect and selection carry floors");
    check(s.spawnOrdinaryBomb(s.player.position,1,43,true)&&s.bombPickups.back().sourceSubtype==2,"later floor ordinary producer uses BOGO");
    for(bool full:{false,true}) {
        auto gated=make(4,2);enter(gated);if(full)gated.items.assign(256,Sale);else gated.shopOpen=true;
        touch(gated,gated.shopUpgradePosition());check(!gated.shopUpgradeSold&&gated.moneySpent==0,"inventory/modal gate atomic");
    }
    auto cap=make();cap.grant(Bogo);cap.dynamite=99;check(cap.spawnOrdinaryBomb(cap.player.position,1,45,true),"full-cap actor admitted");
    touch(cap,cap.player.position);check(cap.bombPickups.back().timing.collectible(),"full cap leaves double");cap.dynamite=97;touch(cap,cap.player.position);check(cap.dynamite==99,"spending allows full double");
    std::cout<<"PASS purchases / immutable births / cap / repeat / Apply / next-floor effect\n";
}
void layouts() {
    int count=0;bool sale=false,bogo=false,purse=false;
    for(uint64_t seed:{2ULL,4ULL,7ULL,18ULL,26ULL})for(auto dims:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}}) {
        const auto [size,low,high]=dims;auto s=make(seed,1,size,low,high);enter(s);
        check(s.shopVariationActive()&&(s.shopUpgradeItem==64||s.shopUpgradeItem==195||s.shopUpgradeItem==250),"eligible natural choice");
        auto at=s.shopUpgradePosition();check(!s.arena.blocked(at,.48f)&&!s.arena.path(s.player.position,at,.48f).empty(),"reachable upgrade");
        sale|=s.shopUpgradeItem==64;bogo|=s.shopUpgradeItem==250;purse|=s.shopUpgradeItem==195;
        if(size==1.1f)std::cout<<"WITNESS seed="<<seed<<" item="<<s.shopUpgradeItem<<" bomb="<<s.shopBombOffered()<<" room="<<s.room+1<<'\n';++count;
    }
    check(sale&&bogo&&purse,"all three natural choices in recorded seeds");std::cout<<"PASS "<<count<<" size/selection cases\n";
}
void presets() {
    const auto root=std::filesystem::path(__FILE__).parent_path().parent_path();
    auto p=BalancePreset::load(root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());
    check(p.shopCollectiblePool==1&&p.defaultZoomPercent==165&&p.roomSizeScale==1.1f,"original accepted preset migrates additively");
    const auto path=std::filesystem::temp_directory_path()/("deathward-shop-collectibles-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json");
    for(int mode=0;mode<3;++mode){p.shopCollectiblePool=mode;p.save(path);auto loaded=BalancePreset::load(path,p.mechanicsFingerprint);check(loaded.shopCollectiblePool==mode&&loaded.json()==p.json(),"all selection modes roundtrip exactly");}
    auto bad=p.json();auto at=bad.find("\"shop_collectible_pool\": 2");check(at!=std::string::npos,"resolved mode present");bad.replace(at,std::string("\"shop_collectible_pool\": 2").size(),"\"shop_collectible_pool\": 2.5");std::ofstream(path)<<bad;
    bool failed=false;try{BalancePreset::load(path,p.mechanicsFingerprint);}catch(...){failed=true;}check(failed,"fractional mode rejected");std::filesystem::remove(path);
    std::cout<<"PASS original preset migration / all modes / invalid refusal\n";
}
}
int main(){try{native();transactions();layouts();presets();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
