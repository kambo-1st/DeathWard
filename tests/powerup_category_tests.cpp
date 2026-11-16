#include "items/Items.hpp"
#include "items/SadOnion.hpp"
#include "items/CricketHead.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
void near(float a,float b,const char *m){if(std::abs(a-b)>.0001f)throw std::runtime_error(m);}
Simulation make(uint64_t seed=1,float scale=1.1f,int lo=7,int hi=9){auto s=Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1);s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);s.player.attributes.tearsPerSecond=1.9272734f;s.player.attributes.shotSpeed=.9f;return s;}
void acquire(Simulation &s) {
    check(s.beginPowerupReview()&&s.items.empty()&&!s.activeItem&&!s.heldTrinket,"Review stages actors, grants nothing");
    const auto source=s.arena.rooms[size_t(s.room)].sourceHeartTemplate;
    for(int item:PowerupReviewState::Offerings) {
        check(s.treasureUpgradeItem(s.room)==item,"Visible next offering");s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);
        check(s.collectTreasureUpgrade()&&!s.collectTreasureUpgrade(),"Actual once-per-contact pedestal transaction");
        const auto count=s.items.size();for(int n=0;n<12;++n)s.step({});check(s.items.size()==count,"No immediate collection of next offering");
        s.player.position=add(s.rewardPosition(s.room),{0,.85f,4});s.step({});
    }
    check(s.items.size()==4&&s.powerupReview->collected==4&&!s.rewardAvailable(s.room)&&s.activeItem->charge==4,"Four visible collectibles, spent pedestal, full active");
    check(s.arena.rooms[size_t(s.room)].sourceHeartTemplate==source,"No underlying room template rewrite");
    check(s.trinketPickups.size()==1,"One labelled Cancer actor");s.player.position=s.trinketPickups.front().position;s.step({});
    check(s.heldTrinket==CancerKey&&s.itemStacks(CancerKey)==0&&s.brotherBobbies.size()==1,"Separate held slot and one friendly actor");
}
void combined() {
    auto s=make();acquire(s);const auto base=s.player.attributes;
    near(s.effectivePlayerStats().damage,cricketHeadDamage(3.5f,1),"Combined Cricket damage");
    near(s.effectivePlayerStats().tearsPerSecond,sadOnionTears(base.tearsPerSecond,1)+1,"Combined Onion then Cancer");
    near(s.player.walkingSpeed(),4.8f,"Accepted walking preserved");
    const auto before=s.items;const auto familiar=s.brotherBobbies.front().id;s.player.hp=4;s.player.fireCooldown=.3f;
    check(s.visitPowerupReviewEncounter()&&s.roomThreats()>0&&!s.roomClear,"Real generated encounter");
    check(s.player.hp==4&&s.activeItem->charge==4&&s.player.fireCooldown==.3f,"Review travel never heals or refills waits/charge");
    check(!s.visitPowerupReviewEncounter(true),"Cannot skip active fight");
    check(s.useActiveItem()&&s.player.hp==6&&s.activeItem->charge==0,"Combined active heals/discharges");
    Input fire;fire.fire=true;
    bool playerHit=false,allyHit=false;uint64_t allyShots=0;
    for(int tick=0;tick<1800&&!s.roomClear&&!s.dead;++tick) {
        const Enemy *target=nullptr;float nearest=10000;
        for(const auto &e:s.enemies)if(e.alive&&!e.friendly&&!e.environment&&planarDistance(e.position,s.player.position)<nearest){target=&e;nearest=planarDistance(e.position,s.player.position);}
        if(target){const auto direction=unit(horizontal(sub(target->position,s.player.position)));fire.aimDirection=direction;fire.aim=target->position;}
        s.step(fire);
        for(const auto &p:s.projectiles) {
            if(p.hostile)continue;
            if(p.context.familiarAttack){allyHit=true;near(p.damage,11.2f,"Bobby retains its own damage with all player modifiers");}
            else {playerHit=true;near(p.damage,cricketHeadDamage(3.5f,1)*3.2f,"Actual player attack resolves combined build once");}
        }
        if(!s.brotherBobbies.empty())allyShots=s.brotherBobbies.front().shots;
    }
    check(s.roomClear&&!s.dead&&playerHit&&allyHit&&allyShots>0&&s.stats.damageDealt>0,"Both sources fire and clear actual ordinary encounter");
    check(s.activeItem->charge==1&&s.brotherBobbies.front().id==familiar,"Clear recharges once; same friendly identity transfers");s.clearRoom();check(s.activeItem->charge==1,"No duplicate recharge");
    const float ownedDamage=s.effectivePlayerStats().damage;s.player.fireCooldown=.27f;check(s.dropTrinket(),"Drop in combined build");
    near(s.effectivePlayerStats().tearsPerSecond,sadOnionTears(base.tearsPerSecond,1),"Only Cancer removed");check(s.items==before&&s.player.fireCooldown==.27f&&s.activeItem->charge==1,"Drop leaves passives/familiar/active/wait intact");near(s.effectivePlayerStats().damage,ownedDamage,"Drop leaves Cricket damage");
    const auto dropped=s.trinketPickups.back().position;
    for(int i=0;i<90;++i)s.step({});check(!s.heldTrinket,"No accidental recollect");
    Vector3 away{};bool found=false;for(const auto &c:s.arena.floorCells){Vector3 p{(c.first+.5f)*FloorTile,.85f,(c.second+.5f)*FloorTile};if(s.arena.roomAt(p)==s.room&&planarDistance(p,dropped)>2&&!s.arena.blocked(p,.48f)&&!s.arena.path(s.player.position,p,.48f).empty()){away=p;found=true;break;}}
    check(found,"Reachable rearm path");s.player.position=away;s.step({});s.player.position=dropped;s.step({});check(s.heldTrinket==CancerKey,"Combined recollection");
    s.trinkets.cancerStrength=.5f;s.brotherBobby.damage=1.1f;s.yumHeart.healing=3;
    const auto charge=s.activeItem->charge;check(s.visitPowerupReviewEncounter(true),"Direct real boss review");check(s.player.hp>0&&s.activeItem->charge==charge,"Boss travel preserves health/charge");
    s.clearRoomDebug();s.floorExitRequested=true;check(s.advanceFloor(),"Real floor transition path");s.step({});
    check(s.items==before&&s.heldTrinket==CancerKey&&s.activeItem->charge==charge+1&&s.brotherBobbies.size()==1&&s.powerupReview&&s.powerupReview->treasureRoom==-1,"All categories survive floor; no extra review pedestal");
    check(s.trinkets.cancerStrength==.5f&&s.brotherBobby.damage==1.1f&&s.yumHeart.healing==3,"All live settings survive floor");
    s.resizeRooms(1.11f,7,9,.26f);s.step({});check(!s.powerupReview&&s.items==before&&s.heldTrinket==CancerKey&&s.brotherBobbies.size()==1,"Explicit Apply ends fixture, retains actual build");
    std::cout<<"PASS actual combined combat/effects/one clear/recollect/floor/Apply\n";
}
void coverage() {
    for(auto d:{std::tuple{.75f,5,5},std::tuple{1.1f,7,9},std::tuple{1.5f,10,10}}){auto [size,lo,hi]=d;auto s=make(1,size,lo,hi);acquire(s);check(!s.arena.blocked(s.player.position,.48f),"Acquisition on clear floor");check(s.visitPowerupReviewEncounter()&&s.arena.roomAt(s.player.position)==s.room&&!s.arena.blocked(s.player.position,.48f),"Direct entry in actual destination room");}
    auto normal=make();check(!normal.powerupReview&&!normal.visitPowerupReviewEncounter(),"Normal expeditions cannot use review travel");check(normal.trinketPickups.empty(),"No review pickup in normal generation");
    std::cout<<"PASS three dynamic size setups and ordinary mode isolation\n";
}
}
int main(){try{combined();coverage();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
