#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
Simulation create(uint64_t seed,int floor=0){
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f,true);
    r.redHeartClearRewards=true;r.godMode=true;return r;
}
void damageRed(Simulation &r,int amount){auto h=r.player.sourceHealth();h.addRed(-amount);r.player.setSourceHealth(h);}
void quantities(){
    for(const auto c:{std::array{69,2,1,2},std::array{1,1,2,1},std::array{355,2,5,4}}){
        auto r=create(uint64_t(c[0]));r.jumpDebug(c[1]);check(!r.roomClear,"ordinary uncleared witness");r.clearRoomDebug();
        const auto &a=r.rooms[size_t(c[1])].redHeartAward;check(a&&a->variant==10&&a->subtype==c[2]&&a->delivered&&!a->pending,"deterministic source heart outcome delivered once");
        check(r.heartPickups.size()==1&&r.heartPickups[0].amount==c[3]&&r.heartPickups[0].sourceSubtype==c[2],"full/half/double quantities from natural clear");
        const auto at=r.heartPickups[0].position;check(r.arena.roomAt(at)==c[1]&&!r.arena.blocked(at,.35f)&&!r.arena.path(r.player.position,at,.48f).empty(),"reward safely reachable in owning room");
        r.player.position=at;for(int n=0;n<70;++n)r.step({});check(r.heartPickups.size()==1&&r.player.hp==6,"full red health refuses and preserves pickup");
        damageRed(r,4);for(int n=0;n<30;++n)r.step({});check(r.heartPickups.empty()&&r.player.hp==2+c[3],"touch heals exact source halves, no container increase");
        const auto hp=r.player.hp;r.player.position=r.arena.rooms[0].center;r.enterRoom(0);r.player.position=at;r.enterRoom(c[1]);for(int n=0;n<3;++n)r.step({});
        check(r.heartPickups.empty()&&r.player.hp==hp,"collected pickup stays collected across revisit");
        std::cout<<"HEART seed="<<c[0]<<" room="<<c[1]+1<<" subtype="<<c[2]<<" healed="<<c[3]<<'\n';
    }
    auto r=create(69);r.jumpDebug(2);r.clearRoomDebug();damageRed(r,1);r.player.position=r.heartPickups[0].position;for(int n=0;n<90;++n)r.step({});
    check(r.player.hp==6&&r.heartPickups.empty(),"full heart clips to one missing half and consumes once");
}
void boundaries(){
    auto r=create(69);r.jumpDebug(2);r.heartPickups.assign(1024,HeartPickup{r.arena.rooms[0].center,HeartKind::Red,2,0});
    r.clearRoomDebug();
    auto &a=r.rooms[2].redHeartAward;check(a&&a->pending&&!a->delivered,"capacity preserves resolved award as pending");
    const auto seed=a->pickupSeed;r.redHeartClearRewards=false;r.player.attributes.luck=20;
    r.jumpDebug(0);r.heartPickups.pop_back();r.step({});check(a->pending&&r.heartPickups.size()==1023,"inactive room does not spawn its pending award");
    r.jumpDebug(2);r.step({});check(a->delivered&&a->pickupSeed==seed&&a->luck==0&&r.heartPickups.size()==1024,"pending award survives toggle/Luck edit without reroll");
    check(r.heartPickups.back().amount==2&&r.heartPickups.back().room==2,"committed birth identity and room retained");
    auto off=create(69);off.redHeartClearRewards=false;off.jumpDebug(2);off.clearRoomDebug();off.redHeartClearRewards=true;off.jumpDebug(0);off.jumpDebug(2);off.step({});
    check(!off.rooms[2].redHeartAward&&off.heartPickups.empty(),"enabling does not pay already-cleared rooms");
    auto special=create(13);special.jumpDebug(2);special.clearRoomDebug();
    check(special.rooms[2].redHeartAward&&special.rooms[2].redHeartAward->subtype==3&&special.heartPickups.empty(),"unselected soul outcome is recorded, not substituted or enabled");
    auto lucky=create(69);lucky.player.attributes.luck=10;lucky.jumpDebug(2);lucky.clearRoomDebug();
    check(lucky.rooms[2].redHeartAward->luck==10&&lucky.rooms[2].redHeartAward->variant!=10,"ordinary Luck consumer changes source table outcome");
    auto blocked=create(69);blocked.jumpDebug(2);const auto center=blocked.arena.rooms[2].center;
    blocked.arena.obstacles.push_back({add(center,{-2,-1,-2}),add(center,{2,2,2})});blocked.arena.rebuildWalls();blocked.clearRoomDebug();
    check(blocked.heartPickups.size()==1&&planarDistance(blocked.heartPickups[0].position,center)>2&&!blocked.arena.blocked(blocked.heartPickups[0].position,.35f),"blocked center chooses legal reachable nearby floor");
    auto later=create(69,1);later.jumpDebug(2);later.clearRoomDebug();check(!later.rooms[2].redHeartAward&&later.heartPickups.empty(),"delivery excludes later floors");
    auto resized=create(69);resized.player.attributes.luck=5;resized.resizeRooms(1.2f,7,9,.26f);
    check(resized.redHeartClearRewards&&resized.player.attributes.luck==5,"test regeneration retains reward configuration");
    std::cout<<"PASS capacity/backpressure, room ownership, committed edits, no retroactive rewards, unsupported families, Luck and floor/config boundaries\n";
}
void timing() {
    for(int fps:{30,60,120})for(float speed:{.25f,1.f,4.f}) {
        auto r=create(69);r.redHeartAppearanceSpeed=speed;r.jumpDebug(2);r.clearRoomDebug();
        check(r.heartPickups.size()==1&&!r.heartPickups[0].timing.collectible()&&r.heartPickups[0].timing.frame==0,"birth is visible but not immediately collectible");
        r.player.position=r.heartPickups[0].position;damageRed(r,2);
        const int frames=int(std::ceil(25/speed))*fps/30;
        r.redHeartAppearanceSpeed=2; // Existing actor must retain its snapshot.
        for(int n=1;n<frames;++n){r.step({},1.f/fps);check(r.player.hp==4,"no healing before native appearance gate");}
        r.step({},1.f/fps);
        check(r.player.hp==6&&r.heartPickups.size()==1&&r.heartPickups[0].timing.phase==RedHeartTiming::Phase::Collect,"gate admits exactly once and begins collection presentation");
        damageRed(r,2);
        for(int n=1;n<12*fps/30;++n){r.step({},1.f/fps);check(r.heartPickups.size()==1&&r.player.hp==4,"collection presentation never heals twice or expires early");}
        r.step({},1.f/fps);check(r.heartPickups.empty()&&r.player.hp==4,"collection actor removed after twelve source frames");
    }
    auto r=create(69);r.jumpDebug(2);r.clearRoomDebug();r.step({},.1f);
    const float born=r.heartPickups[0].timing.frame;check(born==3,"three source updates");
    r.rewardOpen=true;r.step({},2);check(r.heartPickups[0].timing.frame==born,"paused simulation does not age pickups");r.rewardOpen=false;
    r.jumpDebug(0);r.step({},2);check(r.heartPickups[0].timing.frame==born,"inactive-room clock is frozen");
    r.jumpDebug(2);r.step({},.1f);check(r.heartPickups[0].timing.frame==born+3,"revisit resumes rather than restarts appearance");
    r.redHeartAppearanceSpeed=.5f;r.resizeRooms(1.2f,7,9,.26f);check(r.redHeartAppearanceSpeed==.5f,"regeneration preserves configured appearance pace");
    auto pending=create(69);pending.jumpDebug(2);pending.heartPickups.assign(1024,HeartPickup{pending.arena.rooms[0].center,HeartKind::Red,2,0});pending.clearRoomDebug();
    pending.step({},1);pending.redHeartAppearanceSpeed=.5f;pending.heartPickups.clear();pending.step({},.1f);
    check(pending.heartPickups.size()==1&&pending.heartPickups[0].timing.frame==0&&pending.heartPickups[0].timing.appearanceSpeed==.5f,"deferred delivery starts birth clock on actual admission using then-current config");
    std::cout<<"PASS native birth/collection boundaries at 30/60/120 Hz, live birth snapshots, pause/inactive ownership and deferred admission\n";
}
int main(){try{quantities();boundaries();timing();}catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
