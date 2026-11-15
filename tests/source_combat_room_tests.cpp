#include "RoomReviewSeeds.hpp"
#include "combat/Simulation.hpp"
#include "world/SourceCombatRoom.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool value,const char *why){if(!value)throw std::runtime_error(why);}
int sourceRoom(const Simulation &r){int found=-1;for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceCombatTemplate>=0){check(found<0,"only one recorded template");found=i;}return found;}
Simulation create(uint64_t seed,float size=1.1f,int lo=7,int hi=9,float route=.26f,bool enabled=true,int floor=0){
    return Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),size,lo,hi,route,enabled);
}
void verify(const Simulation &r) {
    const int index=sourceRoom(r);check(index>0,"recorded template present in opening floor");
    const auto &layout=r.arena.rooms[size_t(index)];const auto &bodies=r.roomEnemies(index);
    check(layout.kind==RoomKind::Combat&&layout.story==StoryRoom::None&&layout.sourceCombatTemplate==47,"eligible ordinary room role");
    check(bodies.size()==2&&r.floorEncounter(index).monsters.size()==2,"exact roster, no specialists or statues");
    for(int slot=0;slot<2;++slot){const auto &e=bodies[size_t(slot)];
        check(e.monster==monsterId(10,1)&&e.champion<0,"exact ordinary Gaper identity");
        check(distance(e.position,sourceCombatSpawn(layout,slot))<.001f,"recorded cells mapped without random fallback");
        check(!r.arena.blocked(e.position,e.radius)&&!r.arena.canyon->waterBlocked(e.position),"legal dry spawn");
        check(std::abs(e.maxHp-32)<.001f,"preserved HP units");
    }
    check(layout.obstacles.empty()&&r.arena.supplyCache.room!=index,"no random template cover/cache");
    for(const auto &b:r.arena.breakables)check(b.room!=index,"no extra breakables/dung");
    for(const auto &k:r.arena.keys)check(k.room!=index,"no extra key site");
    for(const auto &m:r.moneyPickups)check(r.arena.roomAt(m.position)!=index,"no pregenerated extra coins");
    for(int river:r.arena.canyon->riverRooms)check(river!=index,"river stays outside recorded empty room");
    for(int p:layout.passages){const int side=r.arena.passages[size_t(p)].rooms[0]==index?0:1;
        check(!r.arena.path(r.arena.doorApproach(p,side),layout.center,.48f).empty(),"connected entrance to formation");}
    std::cout<<"TEMPLATE seed="<<r.expedition.seed<<" room="<<index+1<<" depth="<<layout.depth<<" size="<<r.roomSizeScale<<" roster=10.1.0,10.1.0 cover=0\n";
}
void walkTo(Simulation &r,Vector3 target,int room) {
    Input first;first.moveTarget=target;r.step(first);
    for(int n=0;n<6000&&r.room!=room;++n)r.step({});
    check(r.room==room,"ordinary movement crosses door and changes rooms");
}
void encounterLoop() {
    auto r=create(review::FullHeartClearSeed);r.redHeartClearRewards=true;r.applyCombatBalance(3.5f,1);r.canonicalShooting=true;r.gaperMovementMultiplier=1;r.godMode=true;
    const int index=sourceRoom(r);check(r.arena.rooms[size_t(index)].depth==1,"review template adjacent to entrance");
    // Freeze naturally generated actors solely for deterministic projectile counting.
    // Room transitions, sealed gates, attacks, death/morphs, rewards and persistence are real.
    for(auto &e:r.rooms[size_t(index)].residents){e.state=EnemyState::Stunned;e.stateTime=1000;}
    walkTo(r,r.arena.rooms[size_t(index)].center,index);
    check(!r.roomClear&&r.livingEnemies()==2,"entering ordinary encounter starts two-body fight");
    for(int p:r.arena.rooms[size_t(index)].passages)check(!r.arena.passages[size_t(p)].open(),"all connected doors seal");
    for(int n=0;n<6000&&!r.roomClear;++n) {
        Enemy *target=nullptr;
        for(auto &e:r.enemies)if(e.alive&&!e.friendly){e.state=EnemyState::Stunned;e.stateTime=1000;
            if(!target||distance(e.position,r.player.position)<distance(target->position,r.player.position))target=&e;}
        Input input;
        if(target){input.aim=target->position;const float gap=distance(target->position,r.player.position);
            if(gap>3.5f)input.movement=unit(sub(target->position,r.player.position));else input.fire=true;}
        r.step(input);
    }
    check(r.roomClear&&r.roomThreats()==0&&r.stats.shots>=6,"actual shots finish bodies and successor threats, automatic clear");
    for(int p:r.arena.rooms[size_t(index)].passages){const auto &door=r.arena.passages[size_t(p)];check(!door.sealed[0]&&!door.sealed[1],"combat seals reopen, independent key locks retained");}
    check(r.heartPickups.size()==1&&r.heartPickups.front().amount==2&&r.heartPickups.front().sourceSubtype==1,"D09 actual projectile clear naturally spawns source full heart");
    const auto kills=r.stats.kills,clears=r.stats.rooms;const auto rewards=r.moneyPickups.size();
    walkTo(r,r.arena.rooms[0].center,0);
    walkTo(r,r.arena.rooms[size_t(index)].center,index);
    check(r.roomClear&&r.livingEnemies()==0&&r.stats.kills==kills&&r.stats.rooms==clears,"revisit stays cleared without duplicate kill/clear");
    check(r.heartPickups.size()==1,"uncollected heart survives leave/revisit without duplication");
    check(r.moneyPickups.size()<=rewards,"revisit spawns no duplicate reward");
    std::cout<<"PASS real Simulation entry/seal/projectile deaths/offspring/clear/leave/revisit; shots="<<r.stats.shots<<" kills="<<kills<<'\n';
}
int main(){try {
    encounterLoop();
    for(uint64_t seed:{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,57,69,1866}){auto r=create(seed);verify(r);}
    for(auto range:{std::pair{5,5},std::pair{7,9},std::pair{10,10}})for(float size:{.75f,1.01f,1.5f}){
        auto r=create(69,size,range.first,range.second,size==.75f?.25f:2.f);verify(r);
    }
    auto r=create(69);const int index=sourceRoom(r);auto duplicate=create(69);check(sourceRoom(duplicate)==index,"seed-stable room selection");
    r.applyCombatBalance(7,.75f);r.player.hp=4;r.gaperMovementMultiplier=.65f;r.player.attributes.speed=.8f;
    const auto identity=r.summary().id;r.resizeRooms(1.2f,7,9,.3f,false);
    check(sourceRoom(r)<0&&!r.sourceCombatRoom&&r.summary().id==identity&&r.player.hp==4&&r.player.attributes.damage==7&&r.gaperMovementMultiplier==.65f,"toggle-only/regeneration retains expedition and player/build");
    r.resizeRooms(1.2f,7,9,.3f,true);check(sourceRoom(r)>=0,"same-size reenable actually regenerates");
    for(const auto &e:r.roomEnemies(sourceRoom(r)))check(std::abs(e.maxHp-24)<.001f,"regenerated template consumes live regular HP");
    auto off=create(69,1.1f,7,9,.26f,false);check(sourceRoom(off)<0,"disabled uses original generation");
    auto later=create(69,1.1f,7,9,.26f,true,1);check(sourceRoom(later)<0&&later.sourceCombatRoom,"delivery limited to opening floor, setting retained");
    std::cout<<"PASS D08: 28 generation/size cases, exact template/no extras, paths, repeatability, enable/disable/regeneration and floor scope\n";
}catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
