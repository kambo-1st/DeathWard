#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourceRecordedShop.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
Simulation canyon(float scale=1,int lo=7,int hi=9,WorldState w={},uint64_t seed=68) {return Simulation(seed,1,w,MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{},DukeTuning{true},false,255,RoomPropsTuning{1});}
void native(){
 const auto dir=Root/"docs/reports/isaac-first-floor-parity/d14a15-donation-milestones/source";std::string line;int rows=0;
 std::ifstream f(dir/"native-milestones.csv");check(bool(f),"milestones fixture");std::getline(f,line);
 while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);unsigned bank,flags;in>>bank>>flags;check(bool(in)&&donationMilestonesAt(bank)==flags,"native threshold mask");++rows;}check(rows==32,"32 native milestone gates");
 f.close();f.open(dir/"native-shop-level.csv");std::getline(f,line);rows=0;
 while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int bits,level;in>>bits>>level;uint16_t flags=0;for(int i=0;i<4;++i)if(bits&(1<<i))flags|=1<<(i*2+1);check(bool(in)&&donationShopLevel(flags)+1==level,"native level is one based");++rows;}check(rows==16,"16 native levels");
 f.close();f.open(dir/"source-stock-slots.csv");std::getline(f,line);rows=0;std::array<int,5> slots{};
 while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int level,ordinal,x,y;in>>level>>ordinal>>x>>y;check(bool(in)&&SourceShopCells[size_t(level)][size_t(slots[size_t(level)]++)]==std::pair{x,y},"source slot coordinates");++rows;}check(rows==20,"20 source positions");
 std::cout<<"PASS 32 native milestone gates,16 native levels,20 source stock positions\n";
}
void levels(float scale,int lo,int hi){
 for(int level=0;level<=4;++level){auto s=canyon(scale,lo,hi);s.configureShopLevel(level);check(s.enterSourceRoomReview(RecordedShopReview),"direct recorded shop");s.step({});
 check(s.shopLevel==level,"configured level");if(!level){check(s.upgradedShop.empty()&&s.shopUpgradeSlot==0,"legacy base stock preserved");continue;}
 std::cout<<"size="<<scale<<" level="<<level<<" count="<<s.upgradedShop.size()<<'\n';check(s.upgradedShop.size()==size_t(level+2),"all upgraded slots fit canyon");
 const auto expected=sourceShopStock(canyonShopStockSeed(68),level+1);s.moneyCollected=99;
 for(const auto &o:s.upgradedShop){check(o.category==expected.categories[size_t(o.slot)]&&o.seed!=0,"native category retained, nonzero actor seed");check(!s.arena.blocked(o.position,.48f)&&!s.arena.path(s.arena.rooms[size_t(s.room)].entry,o.position,.48f).empty(),"stock accessible");check(o.delivered==o.supported(),"unsupported outcomes omitted without reroll");}
 // Exercise real touch consumers, including payment/capacity and no duplicate collectible.
 for(size_t i=0;i<s.upgradedShop.size();++i){auto o=s.upgradedShop[i];if(!o.supported())continue;if(o.category==5){s.grant(YumHeartKey);s.useActiveItem();}s.player.hp=2;s.moneyCollected=500;s.player.position=o.position;const auto before=s.moneySpent;const auto price=s.upgradedShopPrice(int(i));ticks(s,3);check(s.upgradedShop[i].sold&&s.moneySpent==before+price,"real pickup paid once");ticks(s,20);check(s.moneySpent==before+price,"contact cannot buy twice");}
 s.enterRoom(0);s.enterRoom(s.arena.shopRoom);s.step({});for(auto &o:s.upgradedShop)if(o.supported())check(o.sold,"sold state retained on revisit");
 }
 std::cout<<"PASS stock geometry, categories, real purchases and revisit at size "<<scale<<'\n';
}
void purchaseGates(){
 auto s=canyon();s.configureShopLevel(4);check(s.enterSourceRoomReview(RecordedShopReview),"purchase-gate shop");s.step({});
 for(auto &o:s.upgradedShop)if(o.supported()){s.moneyCollected=s.moneySpent=0;s.player.position=o.position;ticks(s,2);check(!o.sold,"no purchase without money");}
 // A red heart selected through the ordinary expanded stock consumer must not charge at full health.
 s.heartPickups.clear();s.keyPickups.clear();s.bombPickups.clear();s.pillPickups.clear();auto &o=s.upgradedShop[0];o.category=0;o.item=0;o.sold=o.delivered=false;s.moneyCollected=30;s.player.hp=s.player.maxHp;s.player.position=o.position;s.deliverUpgradedShop();const auto spent=s.moneySpent;ticks(s,3);check(!o.sold&&s.moneySpent==spent,"full health cannot buy red heart");s.player.hp-=2;ticks(s,3);check(o.sold&&s.player.hp==s.player.maxHp,"injured player can buy red heart");
 std::cout<<"PASS insufficient funds and full-health admission gates\n";
}
void milestones(){
 WorldState w;w.donationBank=19;w.donationUnlocks=donationMilestonesAt(19);auto s=canyon(1,7,9,w);check(s.enterSourceRoomReview(RecordedShopReview),"milestone shop");s.coinDonationTuning.outcome=1;s.moneyCollected=20;s.step({});
 auto at=s.coinDonationMachines[0].position;s.player.position=add(at,{1.06f,0,0});ticks(s,2);s.player.position=s.arena.rooms[size_t(s.room)].entry;ticks(s,20);
 check(s.donation.bank==20&&donationShopLevel(s.donation.unlocks)==1&&s.shopLevel==0&&s.upgradedShop.empty(),"20th donation unlocks future stock without rebuilding present shop");
 s.resizeRooms(1,7,9,.26f);check(s.donation.bank==20&&s.shopLevel==1&&s.upgradedShop.size()==3,"explicit Apply refreshes earned stock");
 Event e;e.type=EventType::Explosion;e.position=s.coinDonationMachines[0].position;e.radius=2;e.damage=100;check(s.queueRoot(e),"blast queued");s.drainEvents();check(s.donation.bank<20&&donationShopLevel(s.donation.unlocks)==1,"withdrawal retains earned upgrade");
 s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&donationShopLevel(s.donation.unlocks)==1,"floor retains permanent flags");
 for(int bank:{99,199,599,998,999}){w.donationBank=bank;w.donationUnlocks=donationMilestonesAt(bank);auto t=canyon(1,7,9,w);check(t.enterSourceRoomReview(RecordedShopReview),"threshold shop");t.coinDonationTuning.outcome=1;t.moneyCollected=20;t.step({});t.player.position=add(t.coinDonationMachines[0].position,{1.06f,0,0});ticks(t,2);t.player.position=t.arena.rooms[size_t(t.room)].entry;ticks(t,20);check(t.donation.bank==unsigned(bank+1)&&t.donation.unlocks==donationMilestonesAt(bank+1),"threshold credit retains every unlock");}
 std::cout<<"PASS thresholds, explicit Apply, withdrawal, overflow and floor transition\n";
}
void persistence(){
 auto dir=std::filesystem::temp_directory_path()/("deathward-milestones-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
 {CampaignStore st(dir/"campaign.save");st.begin(68);auto s=*st.data().pending;s.donationBank=600;s.donationUnlocks=donationMilestonesAt(600);st.checkpoint(s);s.donationBank=0;s.donationUnlocks=0;st.checkpoint(s);check(donationShopLevel(st.data().world.donationUnlocks)==4,"stale summary cannot revoke upgrade");}
 {CampaignStore st(dir/"campaign.save");check(st.recover()&&st.data().world.donationBank==0&&donationShopLevel(st.data().world.donationUnlocks)==4,"recovery preserves irreversible unlock independently of bank");st.begin(69);auto s=*st.data().pending;check(donationShopLevel(s.donationUnlocks)==4,"new expedition inherits upgrades");st.resolve(s,EndReason::Death);}
 std::filesystem::copy_file(Root/"docs/reports/isaac-first-floor-parity/d14a15-donation-milestones/legacy-v13-bank600.save",dir/"legacy.save");
 {CampaignStore legacy(dir/"legacy.save");check(legacy.data().world.donationBank==600&&legacy.data().world.donationUnlocks==donationMilestonesAt(600),"campaign13 migrates observed bank to permanent milestones");legacy.recover();}
 {CampaignStore again(dir/"legacy.save");check(donationShopLevel(again.data().world.donationUnlocks)==4,"migrated flags survive schema14 save");}
 auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a14-coin-donation/review-preset.json",defaultMechanics()->fingerprint());check(p.shopLevelOverride==-1&&p.defaultZoomPercent==165,"schema58 migrates earned level and user zoom");
 for(int level=-1;level<=4;++level){p.shopLevelOverride=level;p.save(dir/"preset.json");auto q=BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint);check(q.shopLevelOverride==level&&q.revision()==p.revision(),"all level overrides roundtrip");}
 auto bad=p;bad.shopLevelOverride=5;bool reject=false;try{bad.save(dir/"preset.json");}catch(...){reject=true;}check(reject&&BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).shopLevelOverride==4,"bad level rejected atomically");std::filesystem::remove_all(dir);
 std::cout<<"PASS campaign recovery/permanence, schema58 migration,59 roundtrip, invalid export\n";
}
}
int main(){try{std::cout<<std::unitbuf;native();for(auto [scale,lo,hi]:{std::tuple{.75f,5,5},std::tuple{1.f,7,9},std::tuple{1.5f,10,10}})levels(scale,lo,hi);purchaseGates();milestones();persistence();std::cout<<"PASS donation milestone delivery\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
