#include "RoomReviewSeeds.hpp"
#include "combat/Simulation.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceHeartRockRoomData.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(float scale=1.1f,int minimum=7,int maximum=9,int mode=1) {
    Simulation r(review::seed(91,scale,minimum,maximum),1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,minimum,maximum,.26f,true,mode);
    r.godMode=true;return r;
}
void checkRoom(Simulation &r,bool lifecycle) {
    int owner=-1;for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceObstacleTemplate==91)owner=i;
    check(owner>=0,"recorded witness selects complete source rock room");
    const auto &layout=r.arena.rooms[size_t(owner)];const float cell=sourceHeartCellSize(layout);
    const std::string tag=" size="+std::to_string(r.roomSizeScale)+" cell="+std::to_string(cell);
    check(layout.kind==RoomKind::Empty&&r.roomEnemies(owner).empty(),"source room has no generated enemies"+tag);
    check(layout.heartSpawns.size()==2,"two recorded source pickup slots"+tag);
    int rocks=0;
    for(const auto &rock:r.arena.breakables)if(rock.room==owner) {
        ++rocks;check(rock.sourceGridIndex>=0&&rock.kind==BreakableKind::CrackedRock,"source-only room props"+tag);
        check(rock.paid&&!rock.destroyed,"intact rocks do not introduce custom coin rewards"+tag);
    }
    check(rocks==19,"all nineteen source rocks admitted"+tag);
    check(r.arena.supplyCache.room!=owner&&layout.obstacles.empty(),"no unrelated cache or baked outcrop"+tag);
    for(const auto &money:r.moneyPickups)check(r.arena.roomAt(money.position)!=owner,"no extra coins in the source room"+tag);
    for(auto c:Basement91Rocks)check(r.arena.blocked(sourceHeartCell(layout,c[0],c[1]),.48f),"each source rock blocks movement"+tag);
    for(const auto &spawn:layout.heartSpawns) {
        check(!r.arena.blocked(spawn.preferred,.48f),"pickup pocket physically fits the player"+tag);
        check(r.arena.path(layout.entry,spawn.preferred,.48f).empty(),"sealed source pocket cannot be reached"+tag);
        const auto found=std::find_if(r.heartPickups.begin(),r.heartPickups.end(),[&](const auto &h){return h.room==owner&&planarDistance(h.position,spawn.preferred)<.001f;});
        check(found!=r.heartPickups.end(),"heart kept at its exact inaccessible source position"+tag);
    }
    for(int p:layout.passages) {
        const auto to=r.arena.doorApproach(p,r.arena.passages[size_t(p)].rooms[0]==owner?0:1);
        check(!r.arena.path(layout.entry,to,.48f).empty(),"ordinary door routes stay open"+tag);
    }
    r.jumpDebug(owner);r.player.position=sourceHeartCell(layout,3,3);
    check(!r.arena.blocked(r.player.position,.48f),"bomb approach remains accessible"+tag);
    const auto target=sourceHeartCell(layout,5,3);
    auto health=r.player.sourceHealth();health.addRed(-3);r.player.setSourceHealth(health);
    // Real movement cannot tunnel into the closed pocket, even on a long step.
    const auto stopped=r.arena.move(r.player.position,sub(target,r.player.position),.48f);
    check(planarDistance(stopped,target)>.9f,"closed wall stops movement"+tag);
    for(int n=0;n<20;++n)r.step({});
    check(r.player.hp==3&&r.heartPickups.size()>=2,"no through-wall collection"+tag);
    check(!r.rooms[size_t(owner)].redHeartAward&&r.roomClear,"obstacle room opens without a fake combat-clear reward"+tag);
    Input fire;fire.fire=true;fire.aim=target;
    for(int n=0;n<90;++n)r.step(fire);
    check(std::none_of(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==owner&&b.destroyed;}),"ordinary shooting does not remove enclosing rocks"+tag);
    check(r.placeDynamite(),"normal inventory dynamite placed"+tag);
    for(int n=0;n<240;++n)r.step({});
    check(r.dynamite==StartingDynamite-1,"opening spends real dynamite"+tag);
    check(!r.arena.path(r.player.position,target,.48f).empty(),"detonation opens a navigable route to the heart"+tag);
    check(r.arena.clear(r.player.position,target,.48f),"destroyed stones leave no invisible collision"+tag);
    const auto moved=r.arena.move(r.player.position,sub(target,r.player.position),.48f);
    check(planarDistance(moved,target)<.001f,"physical movement enters opened pocket"+tag);
    Input click;click.moveTarget=target;r.step(click);
    for(int n=0;n<180;++n)r.step({});
    check(planarDistance(r.player.position,target)<.15f,"ordinary click-to-move enters the demolished pocket"+tag);
    check(r.player.hp>3,"heart can be collected after opening"+tag);
    const auto right=sourceHeartCell(layout,7,3);r.player.position=sourceHeartCell(layout,9,3);
    check(!r.arena.blocked(r.player.position,.48f)&&r.placeDynamite(),"right pocket has its own valid demolition approach"+tag);
    for(int n=0;n<240;++n)r.step({});
    check(!r.arena.path(r.player.position,right,.48f).empty(),"right pocket opens after demolition"+tag);
    r.player.position=r.arena.move(r.player.position,sub(right,r.player.position),.48f);r.step({});
    check(r.player.hp==6&&r.dynamite==StartingDynamite-2,"both source hearts collected through real openings"+tag);
    if(lifecycle) {
        const auto destroyed=std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[](const auto &b){return b.sourceGridIndex>=0&&b.destroyed;});
        r.jumpDebug(0);r.jumpDebug(owner);
        check(std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[](const auto &b){return b.sourceGridIndex>=0&&b.destroyed;})==destroyed,"revisit preserves demolished rocks");
        r.resizeRooms(r.roomSizeScale,7,9,.26f,std::nullopt,0);
        check(std::none_of(r.arena.breakables.begin(),r.arena.breakables.end(),[](const auto &b){return b.sourceGridIndex>=0;}),"OFF regeneration removes source rocks");
        r.player.position=sourceHeartCell(r.arena.rooms[size_t(owner)],5,3);
        r.resizeRooms(r.roomSizeScale,7,9,.26f,std::nullopt,1);
        check(std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[](const auto &b){return b.sourceGridIndex>=0&&!b.destroyed;})==19,"Apply regeneration restores source arrangement");
        check(!r.arena.path(r.arena.rooms[size_t(owner)].entry,r.player.position,.48f).empty(),"Apply cannot trap the retained player inside a reclosed pickup pocket");
    }
    std::cout<<"PASS source91 closed/open pockets, physical movement, doors and real dynamite"<<tag<<'\n';
}
int main(){try{
    for(float scale:{.75f,1.1f,1.5f})for(auto range:{std::pair{5,5},std::pair{7,9},std::pair{10,10}}) {
        auto r=create(scale,range.first,range.second);checkRoom(r,scale==1.1f&&range.first==7);
    }
    auto test=create(1.1f,7,9,2);check(std::none_of(test.arena.breakables.begin(),test.arena.breakables.end(),[](const auto &b){return b.sourceGridIndex>=0;}),"forced full/half inspection mode retains its existing open placement");
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
