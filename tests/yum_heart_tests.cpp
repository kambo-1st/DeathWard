#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
const auto Root=std::filesystem::path(__FILE__).parent_path().parent_path();
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation make(uint64_t seed=7,int pool=4){return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true,1,true,true,true,true,true,true,1,pool);}
int treasure(const Simulation &s){for(int i=0;i<s.arena.roomCount();++i)if(s.hasSourceTreasure(i))return i;throw std::runtime_error("No treasure room");}
void touch(Simulation &s){s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);}
void nativeHealth(){
    std::ifstream file(Root/"docs/reports/isaac-first-floor-parity/pw-a01-yum-heart/source/native-healing.csv");std::string line;std::getline(file,line);int n=0;
    auto s=make();s.grant(YumHeartKey);
    while(std::getline(file,line)){
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int capacity,bone,hp,soul,nextRed,nextSoul;
        check(bool(row>>capacity>>bone>>hp>>soul>>nextRed>>nextSoul),"Native healing row");
        if(hp==0&&soul==0&&bone==0)continue;
        SourcePlayerHealth health;health.maxRed=capacity;health.red=hp;health.bone=bone;health.soul=soul;
        s.player.setSourceHealth(health);s.activeItem->charge=4;
        check(s.useActiveItem(),"Use admitted with living owner");
        check(s.player.hp==nextRed&&s.player.soulHearts==nextSoul&&s.activeItem->charge==0,"Original AddHearts result / discharge");++n;
    }
    check(n>40,"Native health coverage");
    s.player.hp=3;s.activeItem->charge=3;check(!s.useActiveItem()&&s.player.hp==3&&s.activeItem->charge==3,"Incomplete charge rejected");
    s.activeItem->charge=4;s.dead=true;check(!s.useActiveItem(),"Dead use rejected");s.dead=false;s.rewardOpen=true;check(!s.useActiveItem(),"Modal use rejected");s.rewardOpen=false;
    s.jumpDebug(treasure(s));s.player.maxHp=6;s.player.hp=3;s.player.boneHearts=0;s.player.soulHearts=0;s.player.position=add(s.rewardPosition(s.room),{0,.85f,4});
    Input held;held.useActive=true;s.step(held);check(s.player.hp==5&&s.activeItem->charge==0,"Real step activation");
    s.activeItem->charge=4;for(int i=0;i<20;++i)s.step(held);check(s.activeItem->charge==4,"Held action never repeats");s.step({});s.step(held);check(s.player.hp==6&&s.activeItem->charge==0,"Released action rearmed and clamped");
    std::cout<<"PASS "<<n<<" native health comparisons, charge admission, actual held/released action\n";
}
void lifecycle(){
    auto s=make();const int owner=treasure(s);s.jumpDebug(owner);touch(s);
    check(s.collectTreasureUpgrade()&&s.activeItem==ActiveItemState{}&&s.itemStacks(YumHeartKey)==1,"Pedestal gives full active slot once");
    check(!s.collectTreasureUpgrade(),"No duplicate admission");s.useActiveItem();
    int count=0,first=-1;
    for(int i=1;i<s.finalRoom()&&count<4;++i){s.jumpDebug(i);if(s.roomClear||!s.roomThreats())continue;if(first<0)first=i;s.clearRoomDebug();check(s.activeItem->charge==++count,"One charge per hostile clear");s.clearRoom();check(s.activeItem->charge==count,"No duplicate clear charge");}
    check(count==4,"Four actual encounters recharge");s.useActiveItem();
    s.jumpDebug(first,true);s.clearRoomDebug();check(s.activeItem->charge==0,"Debug replay cannot re-award");
    s.jumpDebug(0);check(s.activeItem->charge==0,"Empty entrance does not recharge");s.jumpDebug(owner);touch(s);check(!s.collectTreasureUpgrade(),"Revisit preserves spent pedestal");
    // Explicit testing regeneration supplies a second genuine pedestal; held slot survives.
    s.resizeRooms(1.11f,7,9,.26f,true,1,true,true,true,true,true,1,4);
    check(s.activeItem->charge==0,"Apply does not refill");s.jumpDebug(first);s.clearRoomDebug();check(s.activeItem->charge==0,"Apply retains awarded-room ledger");
    s.jumpDebug(owner);touch(s);check(s.collectTreasureUpgrade(),"Second active pedestal swaps");
    check(s.activeItem->charge==4&&s.rooms[size_t(owner)].droppedActive->charge==0&&s.itemStacks(YumHeartKey)==1,"Swap preserves old charge and unique ownership");
    for(int i=0;i<30;++i)s.step({});check(s.activeItem->charge==4,"No immediate swap-back loop");
    s.player.position=add(s.rewardPosition(owner),{0,.85f,4});s.step({});touch(s);check(s.collectTreasureUpgrade(),"Leave and return swaps back");
    check(s.activeItem->charge==0&&s.rooms[size_t(owner)].droppedActive->charge==4,"Both charges retained across swap-back");
    s.jumpDebug(0);s.jumpDebug(owner);check(s.rooms[size_t(owner)].droppedActive->charge==4,"Dropped item persists on revisit");
    s.yumHeart={3,2,1};s.jumpDebug(s.finalRoom());s.clearRoomDebug();const int charge=s.activeItem->charge;s.floorExitRequested=true;check(s.advanceFloor(),"Floor advance");
    check(s.activeItem->charge==charge&&s.yumHeart==YumHeartTuning{3,2,1}&&s.itemStacks(YumHeartKey)==1,"Floor keeps slot/charge/tuning");
    std::cout<<"PASS first clears/revisit/replay/Apply, second-pedestal swaps and floor continuity\n";
}
void nativeCharge(){
    std::ifstream file(Root/"docs/reports/isaac-first-floor-parity/pw-a01-yum-heart/source/native-charge.csv");std::string line;std::getline(file,line);int n=0;
    while(std::getline(file,line)){
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);int before,award,after;check(bool(row>>before>>award>>after),"Native charge row");
        auto s=make();s.grant(YumHeartKey);s.activeItem->charge=before;s.yumHeart.recharge=award;
        int encounter=-1;for(int i=1;i<s.finalRoom();++i){s.jumpDebug(i);if(!s.roomClear&&s.roomThreats()){encounter=i;break;}}
        check(encounter>=0,"Charge encounter");s.killAll();for(int i=0;i<180&&!s.roomClear;++i)s.step({});
        check(s.roomClear&&s.activeItem->charge==after,"Actual clear matches native clamped charge write");++n;
    }
    check(n==15,"All native charge rows");std::cout<<"PASS 15 native charge comparisons through actual encounter completion\n";
}
void persistence(){
    const auto dir=std::filesystem::temp_directory_path()/("deathward-yum-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&!p.yumHeart.custom(),"Original preset migrated with defaults");
    p.yumHeart={3,2,1};p.brotherBobby.damage=.9f;p.treasureCollectiblePool=4;p.save(dir/"preset.json");check(BalancePreset::load(dir/"preset.json",p.mechanicsFingerprint).json()==p.json(),"Preset exact roundtrip including multiple objects");
    auto bad=p.json();const auto at=bad.find("\"healing\": 3");bad.replace(at,12,"\"healing\": 3.5");std::ofstream(dir/"bad.json")<<bad;
    bool rejected=false;try{BalancePreset::load(dir/"bad.json",p.mechanicsFingerprint);}catch(...){rejected=true;}check(rejected,"Fractional half-heart override rejected");
    auto s=make();s.grant(YumHeartKey);s.activeItem->charge=2;
    {CampaignStore c(dir/"campaign.save");auto id=c.begin(7);auto summary=s.summary();summary.id=id;c.checkpoint(summary);}
    CampaignStore loaded(dir/"campaign.save");check(loaded.data().pending&&loaded.data().pending->activeItem==s.activeItem,"Campaign checkpoint records exact charge");loaded.recover();check(loaded.data().history.back().activeItem==s.activeItem,"Interrupted history retains slot; no live resume claim");
    std::ifstream input(dir/"campaign.save");const std::string bytes((std::istreambuf_iterator<char>(input)),{});const auto payload=bytes.substr(bytes.find('\n')+1);
    const auto fixture=[&](const char *name,int version,std::string body){uint64_t hash=14695981039346656037ULL;for(unsigned char c:body){hash^=c;hash*=1099511628211ULL;}std::ofstream(dir/name)<<"DEATHWARD "<<version<<' '<<hash<<'\n'<<body;};
    auto legacy=payload;
    // Schema13/14 added bank and milestone fields to world/summary headers. A version7
    // fixture must remove those fields as well as the later active/trinket records.
    const auto stripDonation=[&](size_t start){const auto end=legacy.find('\n',start);auto last=legacy.rfind(' ',end);last=legacy.rfind(' ',last-1);legacy.erase(last,end-last);};
    stripDonation(0);const auto &history=loaded.data().history.back();const auto fingerprint="\""+history.mechanicsFingerprint+"\"";const auto tail=fingerprint+" "+std::to_string(history.donationBank)+" "+std::to_string(history.donationUnlocks)+"\n";const auto summaryTail=legacy.find(tail);check(summaryTail!=legacy.npos,"Summary tail fixture");legacy.replace(summaryTail,tail.size(),fingerprint+"\n");
    const std::string slot="1 \"isaac:collectible:45\" 2\n";const auto slotAt=payload.find(slot);check(slotAt!=payload.npos,"Slot serialization fixture");legacy.erase(legacy.find(slot),slot.size()+2);fixture("legacy.save",7,legacy);
    CampaignStore old(dir/"legacy.save");check(!old.data().history.back().activeItem&&old.data().history.back().items==s.items,"Version7 migration keeps inventory without inventing charge");
    auto corrupt=payload;corrupt.replace(slotAt,slot.size(),"1 \"isaac:collectible:45\" 9\n");std::istringstream header(bytes);std::string magic;int version=0;header>>magic>>version;fixture("bad.save",version,corrupt);rejected=false;try{CampaignStore invalid(dir/"bad.save");}catch(...){rejected=true;}check(rejected,"Out-of-range saved charge rejected");
    std::filesystem::remove_all(dir);std::cout<<"PASS preset validation/migration and campaign slot/charge checkpoint\n";
}
}
int main(int argc,char **){try{
    if(argc>1){std::set<int> found;for(int seed=1;seed<=30&&found.size()<4;++seed){auto s=make(seed,1);const int room=treasure(s),item=s.treasureUpgradeItem(room);if(found.insert(item).second)std::cout<<"WITNESS seed="<<seed<<" room="<<room+1<<" item="<<item<<'\n';}return found.size()==4?0:1;}
    nativeHealth();nativeCharge();lifecycle();persistence();return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
