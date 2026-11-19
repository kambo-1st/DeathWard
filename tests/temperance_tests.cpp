#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/Campaign.hpp"
#include "world/SourceShopStock.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
void near(float a,float b,const char *why){if(std::abs(a-b)>.0001f){std::cerr<<a<<" != "<<b<<'\n';throw std::runtime_error(why);}}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Mine,false);s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=false;s.player.position={0,.85f,0};s.roomClear=true;
    s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);return s;
}
Simulation generated(uint64_t seed,float scale=1,int lo=7,int hi=9) {
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1);
}
void tick(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void native(){
    auto csv=[&](const char *name,auto consume){std::ifstream f(Root/"docs/reports/isaac-first-floor-parity/d14a9-temperance/source"/name);check(bool(f),"native fixture exists");std::string line;std::getline(f,line);int n=0;while(std::getline(f,line)){std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);consume(in);++n;}return n;};
    check(csv("native-machine.csv",[](auto &in){uint32_t seed,after;int unlock,available,item,count;in>>seed>>unlock>>available>>item>>count>>after;auto result=sourceBloodOutcome(seed,unlock,available);check(result.item==item&&result.coins==count&&seed==after,"native supplied payout and RNG");})==1040,"1040 machine cases");
    check(csv("native-iv-coins.csv",[](auto &in){uint32_t seed,after;int count;in>>seed>>count>>after;check(sourceIvCoins(seed)==count&&seed==after,"native IV payout");})==256,"256 IV cases");
    auto s=fixture();check(csv("native-blood-bag-speed.csv",[&](auto &in){int copies;float value;in>>copies>>value;s.items.clear();for(int i=0;i<copies;++i)s.grant({"isaac",ItemKind::Collectible,119});near(s.effectivePlayerStats().speed,std::clamp(value,.1f,2.f),"source Blood Bag speed, retained cap");})==5,"5 speed cases");
    std::cout<<"PASS 1040 native payout/RNG cases, 256 IV draws, 5 Blood Bag speed cases\n";
}
void consumable(){
    auto s=fixture();s.pills.held=3;check(s.spawnPill(s.player.position,TemperanceCard,123,true),"card actor");s.step({});check(s.pills.held==TemperanceCard&&s.pillPickups[0].color==3,"shared pill/card swap");tick(s,90);check(s.pills.held==TemperanceCard,"no swap loop");s.pillPickups.clear();const auto effects=s.pills.effects;
    check(s.dropPill()&&s.pills.held==0,"card drop");tick(s,90);check(!s.pills.held,"drop rearming");s.player.position.x+=3;s.step({});s.player.position=s.pillPickups[0].position;s.step({});check(s.pills.held==TemperanceCard,"card recollect");
    check(s.usePill()&&!s.pills.held&&s.bloodMachines.size()==1&&s.pills.effects==effects,"use spawns once and does not touch pill mapping");const auto machine=s.bloodMachines[0].position;check(s.arena.blocked(machine,.48f),"machine solid");
    check(!s.spawnBloodMachine(s.player.position,1)&&!s.spawnBloodMachine(machine,2),"no overlapping player/machine births");
    PillTiming t;t.appear(true);for(int i=0;i<25;++i)t.advance(1.f/30);check(!t.collectible(),"card before drop gate");t.advance(1.f/30);check(t.collectible(),"card drop26");for(int i=0;i<9;++i)t.advance(1.f/30);check(t.phase==PillTiming::Phase::Idle,"card appear35");t.collect();for(int i=0;i<15;++i)t.advance(1.f/30);check(t.phase==PillTiming::Phase::Collect,"card collect15 still alive");t.advance(1.f/30);check(t.phase==PillTiming::Phase::Gone,"card collect16 gone");
    auto blocked=fixture();blocked.pills.held=TemperanceCard;blocked.arena.walls.push_back({{-100,-1,-100},{100,5,100}});check(!blocked.usePill()&&blocked.pills.held==TemperanceCard&&blocked.bloodMachines.empty(),"blocked card kept");
    for(int side=0;side<8;++side){auto approach=fixture();const float a=side*Pi/4;approach.player.position={std::cos(a)*4,.85f,std::sin(a)*4};check(approach.spawnBloodMachine({0,.85f,0},1),"approach machine");Input move;move.moveTarget=Vector3{0,.85f,0};approach.step(move);for(int n=0;n<300&&approach.bloodMachines[0].phase==BloodMachine::Phase::Idle;++n)approach.step({});check(approach.bloodMachines[0].phase!=BloodMachine::Phase::Idle,"eight approach directions");}
    std::cout<<"PASS eight approach directions; card/pill swap/drop/use/timing, collision and denied-placement retention\n";
}
void donation(){
    auto s=fixture();check(s.spawnBloodMachine({4,.85f,0},1),"machine spawn");s.bloodMachineTuning.outcome=1;const float hp=s.player.hp;s.player.soulHearts=2;s.player.position={2.94f,.85f,0};s.step({});check(s.player.hp==hp-1&&s.player.soulHearts==2&&s.bloodMachines[0].phase==BloodMachine::Phase::Initiate,"one red-first half-heart on contact");
    s.player.position={0,.85f,0};s.bloodMachineTuning.cycleSpeed=4;s.bloodMachineTuning.outcome=2;tick(s,65);check(s.moneyPickups.empty()&&s.pendingBloodRewards.empty(),"no early payout");s.step({});check(s.moneyPickups.size()==1&&s.bloodMachines[0].paid,"payout at33 ticks; cycle/outcome snapshot");tick(s,10);check(s.bloodMachines[0].phase==BloodMachine::Phase::Idle&&s.player.hp==hp-1,"idle after38 ticks and no remote payment");
    for(float hurt:{.5f,.3f}){s.player.hurt=hurt;s.player.position={2.94f,.85f,0};s.step({});check(s.bloodMachines[0].phase==BloodMachine::Phase::Idle,"hurt gate");}s.player.hurt=0;s.player.dodge=.2f;s.step({});check(s.bloodMachines[0].phase==BloodMachine::Phase::Idle&&s.player.hp==hp-1,"dodge preserved and activation denied");
    s.player.dodge=0;s.bookProtectionRemaining=5;s.step({});check(s.bloodMachines[0].phase==BloodMachine::Phase::Initiate&&s.player.hp==hp-1,"Book protection preserved/source payment return ignored");
    auto lethal=fixture();lethal.player.hp=1;check(lethal.spawnBloodMachine({4,.85f,0},1),"lethal machine");lethal.player.position={2.94f,.85f,0};lethal.step({});check(lethal.player.hp==0,"last half-heart can be donated");tick(lethal,2);check(lethal.dead,"donation can kill");
    std::cout<<"PASS real payment, red-first health, native event timing, snapshots, hurt/dodge/Book and death\n";
}
void rewards(){
    auto s=fixture();s.player.hp=2;s.bloodMachineTuning.outcome=2;check(s.spawnBloodMachine({4,.85f,0},20),"reward machine");s.player.position={2.94f,.85f,0};s.step({});s.player.position={0,.85f,0};tick(s,66);check(s.bloodMachines[0].phase==BloodMachine::Phase::Broken&&!s.arena.blocked({4,.85f,0},.48f)&&s.machineCollectibles.size()==1,"break once, collider removed, Blood Bag born");
    auto at=s.machineCollectibles[0].position;s.player.position=at;tick(s,52);check(s.itemStacks({"isaac",ItemKind::Collectible,119})==1&&s.player.maxHp==8&&s.player.hp==8&&s.machineCollectibles.empty(),"Blood Bag max+2 heal10 once");near(s.effectivePlayerStats().speed,1.3f,"Blood Bag speed");s.bloodMachineTuning.bloodBagStrength=.5f;near(s.effectivePlayerStats().speed,1.15f,"live Blood Bag strength");
    auto iv=fixture();iv.grant(BookOfShadowsKey);iv.activeItem->charge=2;iv.machineCollectibles.push_back({{0,.85f,0},0,135,0,1});iv.step({});check(iv.activeItem&&iv.activeItem->item==IvBagKey&&iv.activeItem->charge==0&&iv.machineCollectibles[0].item==58&&iv.machineCollectibles[0].charge==2,"IV swaps Book preserving outgoing charge");
    tick(iv,70);check(iv.activeItem->item==IvBagKey,"no active swap loop");const float hp=iv.player.hp;check(iv.useActiveItem()&&iv.player.hp==hp-1&&!iv.useActiveItem(),"IV zero-charge use and cooldown");tick(iv,31);check(iv.useActiveItem()&&iv.player.hp==hp-2,"IV reusable after .5s, no room charge");iv.player.position.x+=3;tick(iv,1);iv.player.position=iv.machineCollectibles[0].position;tick(iv,1);check(iv.activeItem->item==BookOfShadowsKey&&iv.activeItem->charge==2,"outgoing Book recollected with charge");
    auto queue=fixture();queue.bloodMachineTuning.outcome=1;check(queue.spawnBloodMachine({4,.85f,0},1),"capacity machine");queue.player.position={2.94f,.85f,0};queue.step({});queue.player.position={0,.85f,0};queue.moneyPickups.resize(1024);for(auto &p:queue.moneyPickups)p.position={50,.85f,50};tick(queue,66);check(queue.pendingBloodRewards.size()==1,"paid reward waits at actor capacity");const auto seed=queue.pendingBloodRewards[0].seed;queue.moneyPickups.clear();queue.step({});check(queue.pendingBloodRewards.empty()&&queue.moneyPickups.size()==1&&seed!=0,"paid identity delivered after capacity returns");
    std::cout<<"PASS Blood Bag health/live speed, break/collider, IV active swaps/cooldown and pending capacity recovery\n";
}
void shop(uint64_t seed,float scale,int lo,int hi){
    auto s=generated(seed,scale,lo,hi);check(s.shopCardSlot>=0&&s.shopUpgradeItem==195,"natural card/Purse pair");s.enterRoom(s.arena.shopRoom);s.player.position=s.arena.rooms[size_t(s.room)].center;s.step({});check(s.pillPickups.size()==1&&s.pillPickups[0].shopStock,"ordinary shop card admitted");s.moneyCollected=4;s.player.position=s.shopCardPosition();s.step({});check(!s.shopCardSold&&!s.pills.held,"unaffordable card retained");s.moneyCollected=20;s.step({});check(s.shopCardSold&&s.pills.held==TemperanceCard&&s.money()==15,"five coin purchase");tick(s,40);check(s.money()==15,"no second payment");
    check(s.usePill()&&s.bloodMachines.size()==1,"actual canyon placement");const auto at=s.bloodMachines[0].position;check(s.arena.blocked(at,.48f),"canyon collider");s.bloodMachineTuning.outcome=1;Input click;click.moveTarget=at;s.step(click);for(int n=0;n<1200&&s.bloodMachines[0].phase==BloodMachine::Phase::Idle;++n)s.step({});if(s.bloodMachines[0].phase==BloodMachine::Phase::Idle)std::cerr<<"CONTACT scale="<<scale<<" delta="<<s.player.position.x-at.x<<","<<s.player.position.y-at.y<<","<<s.player.position.z-at.z<<" hp="<<s.player.hp<<" room="<<s.room<<" target="<<s.bloodMachines[0].room<<" sight="<<s.arena.sight(s.player.position,at)<<"\n";check(s.bloodMachines[0].phase!=BloodMachine::Phase::Idle,"click reaches payment contact");s.step(Input{.movement={1,0,0}});
    s.pills.held=TemperanceCard;s.bloodMachineTuning.ivCooldown=.75f;s.resizeRooms(scale,lo,hi,.27f);check(s.pills.held==TemperanceCard&&s.bloodMachines.empty()&&s.bloodMachineTuning.ivCooldown==.75f,"Apply keeps held/config resets floor machine");s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.step({});s.floorExitRequested=true;check(s.advanceFloor()&&s.pills.held==TemperanceCard&&s.bloodMachines.empty()&&s.bloodMachineTuning.ivCooldown==.75f,"next floor keeps held/config");
    std::cout<<"PASS natural card shop seed="<<seed<<" scale="<<scale<<" range="<<lo<<'-'<<hi<<" purchase/click/Apply/floor\n";
}
void presets(){
    auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d14a8-coin-purse/review-preset.json",defaultMechanics()->fingerprint());check(p.temperance==BloodMachineTuning{}&&p.defaultZoomPercent==165,"old53 migration");const auto path=std::filesystem::temp_directory_path()/("deathward-temperance-test-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json");p.temperance={4,2,1.2f,.9f,.5f,.8f,.65f,3};p.save(path);check(BalancePreset::load(path,p.mechanicsFingerprint).temperance==p.temperance,"54 roundtrip all fields");auto bad=p;bad.temperance.outcome=4;bool rejected=false;try{bad.save(path);}catch(...){rejected=true;}check(rejected&&BalancePreset::load(path,p.mechanicsFingerprint).temperance==p.temperance,"invalid export atomic");std::filesystem::remove(path);
    auto sim=fixture();sim.grant(IvBagKey);const auto save=path.string()+".save";
    {CampaignStore campaign(save);const auto id=campaign.begin(69);auto record=sim.summary();record.id=id;campaign.checkpoint(record);}
    {CampaignStore campaign(save);check(campaign.data().pending&&campaign.data().pending->activeItem==sim.activeItem,"IV zero-charge checkpoint");campaign.recover();check(campaign.data().history.back().activeItem==sim.activeItem,"IV interrupted history");}std::filesystem::remove(save);
    std::cout<<"PASS campaign12 IV history, schema53/54 and invalid atomic export\n";
}
}
int main(int argc,char **argv){try {
    if(argc>1&&std::string(argv[1])=="--find"){for(uint64_t seed=0;seed<10000;++seed){const auto stock=sourceShopStock(canyonShopStockSeed(seed));if(!((stock.categories[0]==8&&stock.categories[1]==6)||(stock.categories[0]==6&&stock.categories[1]==8)))continue;auto s=generated(seed);if(s.shopCardSlot>=0&&s.shopUpgradeItem==195&&s.shopPrice(5,s.shopCardSlot)==5&&s.shopPrice(15,s.shopUpgradeSlot)==15){std::cout<<"WITNESS "<<seed<<" room="<<s.arena.shopRoom+1<<'\n';return 0;}}return 1;}
    native();consumable();donation();rewards();presets();if(argc>1){const auto seed=std::stoull(argv[1]);shop(seed,.75f,5,5);shop(seed,1,7,9);shop(seed,1.5f,10,10);}return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
