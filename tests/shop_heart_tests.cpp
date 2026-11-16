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
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
Simulation generated(uint64_t seed=69,float scale=1.1f,int min=7,int max=9,float routes=.26f) {
 return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,min,max,routes,true,1,true,true,true,true);
}
auto stock(const Simulation &r){return std::count_if(r.heartPickups.begin(),r.heartPickups.end(),[](const auto &h){return h.shopStock&&h.timing.collectible();});}
void enter(Simulation &r){r.jumpDebug(r.arena.shopRoom);check(r.hasSourceShop(r.room)&&stock(r)==1,"source shop has one ready full heart");}
void touch(Simulation &r){r.player.position=r.shopHeartPosition();r.player.position.y=.85f;r.step({});}
void nativeCases() {
 const auto root=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d12a-shop-heart/source";
 std::ifstream file(root/"native-prices.csv");std::string line;std::getline(file,line);int prices=0;
 while(std::getline(file,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);uint64_t seed;int variant,sub,slot,value;check(bool(row>>seed>>variant>>sub>>slot>>value),"native price row");check(value==SourceShopHeartPrice,"native full/half ordinary shop price");++prices;}
 check(prices==60,"all native price cases consumed");
 std::ifstream hearts(root/"native-red-admission.csv");std::getline(hearts,line);int cases=0;
 while(std::getline(hearts,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int cap,hp,can;check(bool(row>>cap>>hp>>can),"native admission row");SourcePlayerHealth health;health.maxRed=cap;health.red=hp;health.soul=2;const int before=health.red;health.addRed(2);check((health.red>before)==bool(can),"native ordinary red admission");++cases;}
 check(cases==49,"all native red cases consumed");
}
void layout(){
 int cases=0;
 for(uint64_t seed:{1ULL,69ULL,129ULL})for(auto dim:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}})for(float routes:{.25f,1.f,2.f}) {
  const auto [scale,min,max]=dim;auto r=generated(seed,scale,min,max,routes);r.jumpDebug(r.arena.shopRoom);
  const auto at=r.shopHeartPosition();
  if(stock(r)!=1)std::cerr<<"LAYOUT seed="<<seed<<" scale="<<scale<<" routes="<<routes<<" room="<<r.room<<" blocked="<<r.arena.blocked(at,.48f)<<'\n';
  check(stock(r)==1&&r.roomClear&&r.enemies.empty(),"priced stock is present in generated peaceful shop");
  const auto &site=r.arena.rooms[size_t(r.room)];
  check(planarDistance(at,shopCartGeometry::stockPosition(sourceHeartCell(site,7,4),site.center))<.0001f,"original second-slot coordinates adapted to canyon");
  check(!r.arena.blocked(at,.48f)&&!r.arena.path(site.entry,at,.48f).empty(),"shop stock reachable from entrance");
  check(site.passages.size()==1&&!r.arena.passages[size_t(site.passages.front())].locked,"free opening-floor optional shop retained");
  for(const auto &coin:r.moneyPickups)check(r.arena.roomAt(coin.position)!=r.room,"no unrelated custom free coin piles in source shop");
  for(const auto &key:r.arena.keys)check(planarDistance(key.position,at)>1.5f,"key does not overlap stock");
  r.openShop();check(!r.shopOpen&&!r.buyShop(0),"legacy menu cannot also sell in source shop");
  ++cases;
 }
 std::cout<<"PASS "<<cases<<" generated size/route/shop placement cases\n";
}
void transactions(){
 for(int hp:{4,5,6})for(int funds:{0,2,3,10}) {
  auto r=generated();enter(r);r.player.hp=float(hp);r.moneyCollected=uint64_t(funds);
  const auto combat=r.combatRng.state,reward=r.rewardRng.state;touch(r);
  const bool bought=hp<6&&funds>=3;
  check(r.shopHeartSold==bought&&r.money()==uint64_t(funds-(bought?3:0))&&r.moneySpent==uint64_t(bought?3:0),"atomic exact payment or unchanged refusal");
  check(r.player.hp==(bought?6:hp)&&stock(r)==(bought?0:1),"full-heart healing/clamp/refusal");
  check(r.combatRng.state==combat&&r.rewardRng.state==reward,"purchase consumes no combat/reward RNG");
  if(bought) {
   r.player.hp=4;for(int n=0;n<90;++n)r.step({});
   check(r.player.hp==4&&r.moneySpent==3&&stock(r)==0,"collection animation cannot pay twice");
   r.jumpDebug(0);r.jumpDebug(r.arena.shopRoom);check(stock(r)==0&&r.shopHeartSold,"sold slot deliberately does not respawn");
  }
 }
}
void persistenceAndGates(){
 auto r=generated();enter(r);r.player.hp=4;r.moneyCollected=10;
 r.shopOpen=true;touch(r);check(!r.shopHeartSold&&r.moneySpent==0,"modal blocks transaction");r.shopOpen=false;
 r.roomClear=false;touch(r);check(!r.shopHeartSold,"combat gate");r.roomClear=true;
 r.dead=true;touch(r);check(!r.shopHeartSold,"dead gate");r.dead=false;
 r.shopHeartPrice=0;touch(r);check(r.shopHeartSold&&r.moneySpent==0&&r.player.hp==6,"explicit free override still heals once");
 r.shopHeartPrice=15;r.player.hp=4;touch(r);check(r.moneySpent==0&&r.player.hp==4,"price edits cannot restock sold heart");
 r.jumpDebug(0);r.jumpDebug(r.arena.shopRoom);check(stock(r)==0&&r.shopHeartSold,"sold state survives revisit");
 r.resizeRooms(1.2f,7,9,.26f,true,1,true,true,false);
 check(!r.sourceShopHeart&&stock(r)==0&&r.shopHeartPrice==15,"Apply switches policy and keeps live price");
 r.resizeRooms(1.1f,7,9,.26f,true,1,true,true,true);
 check(r.sourceShopHeart&&stock(r)==1&&!r.shopHeartSold&&r.shopHeartPrice==15,"explicit testing Apply resets floor stock");
 r.player.hp=4;r.shopHeartPrice=3;r.moneyCollected=2;touch(r);check(!r.shopHeartSold,"cannot afford before live price edit");
 r.shopHeartPrice=2;touch(r);check(r.shopHeartSold&&r.moneySpent==2,"live price consumed by next contact");
 r.jumpDebug(r.finalRoom());r.clearRoomDebug();r.floorExitRequested=true;check(r.advanceFloor(),"next floor");
 check(r.sourceShopHeart&&r.shopHeartPrice==2&&!r.hasSourceShop(r.arena.shopRoom),"configuration carried with bounded opening-floor consumer");
}
void earnedCoins(){
 auto r=generated(84);int source=-1;
 for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==30)source=i;
 check(source>=0,"natural preplaced-coin witness");r.jumpDebug(source);
 std::vector<Vector3> coins;for(const auto &p:r.moneyPickups)if(p.placedInLayout&&p.room==source)coins.push_back(p.position);
 for(auto at:coins){r.player.position=at;r.step({});}
 check(r.money()>=3&&r.moneySpent==0,"normal coin actors fund purchase");const auto before=r.money();enter(r);r.player.hp=4;touch(r);
 check(r.shopHeartSold&&r.money()==before-3&&r.player.hp==6,"earned expedition coins buy actual shop heart");
}
void presets(){
 const auto dir=std::filesystem::temp_directory_path()/("deathward-shop-heart-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
 const auto hash=defaultMechanics()->fingerprint();
 for(bool enabled:{false,true})for(int price:{0,2,3,15}){BalancePreset p{1,hash};p.sourceShopHeart=enabled;p.shopHeartPrice=price;p.save(dir/"preset.json");auto q=BalancePreset::load(dir/"preset.json",hash);check(q.revision()==p.revision(),"schema30 stock/price exact roundtrip");}
 const auto root=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity";
 for(auto p:{root/"d03-shooting/user-preset-2026-11-11.json",root/"d11a-treasure-upgrade/treasure-preset.json"}){auto q=BalancePreset::load(p,hash);check(q.sourceShopHeart&&q.shopHeartPrice==3&&q.defaultZoomPercent==165,"schema5/29 migrate with accepted zoom");}
 std::filesystem::remove_all(dir);
}
}
int main(){try{nativeCases();layout();transactions();persistenceAndGates();earnedCoins();presets();std::cout<<"PASS source prices/admission, atomic purchases, live price, revisit/Apply/floor, earned coins and schema30 migration\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
