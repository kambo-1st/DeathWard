#include "RoomReviewSeeds.hpp"
#include "combat/Simulation.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceCombatRockRoomData.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(float size=1.1f,int lo=7,int hi=9,float route=.26f,int mode=1,bool d08=true,int floor=0,uint64_t seed=0) {
    Simulation r(seed?seed:review::seed(108,size,lo,hi),1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,defaultMechanics(),size,lo,hi,route,d08,mode);
    r.applyCombatBalance(3.5f,1);r.canonicalShooting=true;r.gaperMovementMultiplier=1;r.redHeartClearRewards=true;
    return r;
}
int owner(const Simulation &r){for(int i=1;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceCombatTemplate==108)return i;return -1;}
void validRoute(const Arena &arena,Vector3 from,Vector3 to,float radius,const std::string &tag) {
    const auto route=arena.path(from,to,radius);check(!route.empty(),"route exists "+tag);
    for(auto at:route){check(!arena.blocked(at,radius)&&arena.clear(from,at,radius),"every segment keeps full collision "+tag);from=at;}
    check(planarDistance(from,to)<.001f,"route reaches requested floor "+tag);
}
void verify(Simulation &r,int index) {
    const auto &l=r.arena.rooms[size_t(index)];const auto &bodies=r.roomEnemies(index);
    const std::string tag="size="+std::to_string(r.roomSizeScale)+" range="+std::to_string(r.roomMinHalfTiles)+" cell="+std::to_string(sourceHeartCellSize(l));
    check(index!=2&&index!=3&&l.story==StoryRoom::None&&l.kind==RoomKind::Combat,"compatible room role "+tag);
    check(l.sourceObstacleTemplate==108&&l.sourceHeartTemplate==108&&l.sourceRoomSpawnSeed&&l.sourceRoomSelectionSeed,"one coherent selected record "+tag);
    check(bodies.size()==4&&r.floorEncounter(index).monsters.size()==4,"exactly four ordinary enemies "+tag);
    for(size_t n=0;n<4;++n) {
        const auto &e=bodies[n];const auto cell=Basement108Gapers[n];
        check(e.monster==monsterId(10,1)&&e.champion<0&&std::abs(e.maxHp-32)<.001f,"accepted ordinary Gaper HP/identity "+tag);
        check(planarDistance(e.position,sourceHeartCell(l,cell[0],cell[1]))<.001f&&!r.arena.blocked(e.position,e.radius),"exact legal spawn "+tag);
        validRoute(r.arena,l.entry,e.position,e.radius,tag);
        validRoute(r.arena,e.position,l.entry,e.radius,tag);
        validRoute(r.arena,r.arena.rooms[0].entry,e.position,.48f,"cross-room entry "+tag);
        validRoute(r.arena,e.position,r.arena.rooms[0].entry,.48f,"cross-room exit "+tag);
    }
    int rocks=0;for(const auto &b:r.arena.breakables)if(b.room==index) {
        ++rocks;check(b.sourceGridIndex>=0&&b.kind==BreakableKind::CrackedRock&&b.paid&&!b.destroyed,"plain source rock only "+tag);
    }
    check(rocks==9&&l.obstacles.empty()&&r.arena.supplyCache.room!=index,"nine rocks without random cover/cache "+tag);
    for(auto cell:Basement108Rocks)check(r.arena.blocked(sourceHeartCell(l,cell[0],cell[1]),.48f),"source rock blocks "+tag);
    for(const auto &k:r.arena.keys)check(k.room!=index,"mandatory key kept outside arrangement "+tag);
    for(const auto &h:r.heartPickups)check(h.room!=index,"no unrelated initial hearts "+tag);
    for(const auto &m:r.moneyPickups)check(r.arena.roomAt(m.position)!=index,"no unrelated initial coins "+tag);
    check(l.heartSpawns.empty(),"source has no pickup slots "+tag);
    for(int p:l.passages)validRoute(r.arena,l.entry,r.arena.doorApproach(p,r.arena.passages[size_t(p)].rooms[0]==index?0:1),.48f,"door access "+tag);
    std::cout<<"PASS exact source108 content, physical routes and door access "<<tag<<'\n';
}
void fightAndRevisit() {
    auto r=create();const int index=owner(r);check(index==review::room(108),"recorded natural source108 review room");
    check(r.enterSourceRoomReview(108)&&r.room==index&&!r.godMode&&r.player.hp==6,"direct ordinary launch has no cheats");
    r.godMode=true;
    check(!r.roomClear&&r.livingEnemies()==4,"fight begins on entry");
    for(int p:r.arena.rooms[size_t(index)].passages)check(!r.arena.passages[size_t(p)].open(),"gates seal during combat");
    const auto l=r.arena.rooms[size_t(index)];
    // Hold actors only for a deterministic cover/attack check. Actual projectiles,
    // ordinary HP, death morphs, clear rewards and passage state remain active.
    auto stun=[&]{for(auto &e:r.enemies)if(e.alive&&!e.friendly){e.state=EnemyState::Stunned;e.stateTime=1000;e.velocity={};}};
    stun();r.player.position=sourceHeartCell(l,6,0);
    Input cover;cover.fire=true;cover.aim=r.enemies.front().position;
    for(int n=0;n<180;++n){stun();r.step(cover);}
    check(r.enemies.front().hp==32,"intervening rock stops ordinary player shots");
    check(std::none_of(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==index&&b.destroyed;}),"shots leave rocks intact");
    for(int n=0;n<3600&&!r.roomClear;++n) {
        stun();Enemy *target=nullptr;for(auto &e:r.enemies)if(e.alive&&!e.friendly){target=&e;break;}
        Input input;
        if(target) {
            // A physically clear nearby stance isolates damage/lifecycle from aim
            // automation. Independent movement checks below exercise real routes.
            bool found=false;
            for(Vector3 direction:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}) {
                const auto at=add(target->position,mul(direction,1.8f));
                if(r.arena.roomAt(at)==index&&!r.arena.blocked(at,.48f)&&r.arena.clear(at,target->position,.15f)) {r.player.position=at;found=true;break;}
            }
            check(found,"clear firing stance exists");input.fire=true;input.aim=target->position;
        }
        r.step(input);
    }
    check(r.roomClear&&r.roomThreats()==0&&r.stats.kills>=4&&r.stats.shots>=12,"real shots finish Gapers/successors and clear");
    for(int p:l.passages)check(!r.arena.passages[size_t(p)].sealed[0]&&!r.arena.passages[size_t(p)].sealed[1],"clear removes combat seals");
    const auto shots=r.stats.shots,kills=r.stats.kills,clears=r.stats.rooms;
    r.player.position=sourceHeartCell(l,5,2);check(r.placeDynamite(),"ordinary dynamite placed beside rock");
    for(int n=0;n<240;++n)r.step({});
    const auto destroyed=std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==index&&b.destroyed;});
    check(destroyed>0&&r.dynamite==StartingDynamite-1,"dynamite opens real cover");
    const auto hearts=r.heartPickups.size(),money=r.moneyPickups.size();
    r.jumpDebug(0);r.jumpDebug(index);
    check(r.roomClear&&r.livingEnemies()==0&&r.stats.kills==kills&&r.stats.rooms==clears,"revisit keeps cleared encounter");
    check(r.heartPickups.size()==hearts&&r.moneyPickups.size()==money,"revisit produces no duplicate rewards");
    check(std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==index&&b.destroyed;})==destroyed,"demolition persists on revisit");
    r.player.hp=4;r.player.attributes.speed=.8f;r.gaperMovementMultiplier=.65f;r.applyCombatBalance(7,.75f);const auto id=r.summary().id;
    r.resizeRooms(1.1f,7,9,.26f,std::nullopt,0);check(owner(r)<0,"OFF removes arrangement");
    r.resizeRooms(1.1f,7,9,.26f,std::nullopt,1);check(owner(r)==index,"Apply restores natural source room");
    check(r.summary().id==id&&r.player.hp==4&&r.player.attributes.speed==.8f&&r.player.attributes.damage==7&&r.gaperMovementMultiplier==.65f,"Apply retains player/build/expedition");
    for(const auto &e:r.roomEnemies(index))check(std::abs(e.maxHp-24)<.001f,"regenerated source room uses selected HP multiplier");
    std::cout<<"PASS actual shots/cover/deaths/successors/seals/rewards/demolition/revisit/Apply; shots="<<shots<<" kills="<<kills<<'\n';
}
void movement() {
    auto r=create(.75f,5,5,.26f,1,true,0,review::seed(108,.75f,5,5));const int index=owner(r);
    check(index>=0,"recorded minimum-size witness naturally selects source108");verify(r,index);
    check(r.enterSourceRoomReview(108),"small source room review available");r.godMode=true;
    const auto l=r.arena.rooms[size_t(index)];const auto target=sourceHeartCell(l,6,2);
    for(auto &e:r.enemies){e.state=EnemyState::Stunned;e.stateTime=1000;}
    Input click;click.moveTarget=target;r.step(click);for(int n=0;n<1800;++n)r.step({});
    check(planarDistance(r.player.position,target)<.15f,"real click movement reaches narrow Gaper slot");
    r.player.position=l.entry;
    for(auto &e:r.enemies){e.state=EnemyState::Ready;e.stateTime=0;}
    std::array<bool,4> reached{};std::array<EntityId,4> ids{};for(size_t i=0;i<4;++i)ids[i]=r.enemies[i].id;
    // Retire arrivals to measure all four independent navigation routes. A
    // different entrance can make the arrived actors block the waiting ones.
    for(int n=0;n<3600;++n){r.step({});for(size_t i=0;i<4;++i)if(auto *e=r.findEnemy(ids[i]);e&&e->alive&&planarDistance(e->position,r.player.position)<1.5f){reached[i]=true;e->alive=false;}}
    check(std::all_of(reached.begin(),reached.end(),[](bool value){return value;}),"all four live Gapers navigate the source cover toward the player");
    std::cout<<"PASS actual small-room player clicks and four live Gaper routes\n";
}
int main(){try{
    int arrangements=0;for(float size:{.75f,1.1f,1.5f})for(auto range:{std::pair{5,5},std::pair{7,9},std::pair{10,10}}) {
        auto r=create(size,range.first,range.second);const int i=owner(r);
        if(i>=0){verify(r,i);++arrangements;}
        else check(!r.enterSourceRoomReview(108),"geometry-dependent selection is not fabricated for review");
    }
    check(arrangements==9,"nine naturally selected size/range content cases");
    fightAndRevisit();movement();
    auto off=create(1.1f,7,9,.26f,0);check(owner(off)<0,"OFF restores ordinary generation");
    auto test=create(1.1f,7,9,.26f,2);check(owner(test)<0,"full/half testing override stays independent");
    auto later=create(1.1f,7,9,.26f,1,true,1);check(owner(later)<0,"later floors remain outside opening-floor content scope");
    auto independent=create(1.1f,7,9,.26f,1,false);for(const auto &l:independent.arena.rooms)check(l.sourceCombatTemplate!=47,"D08 switch disables only injected47");
    // Explicitly reject a heart-only source108 selection at a protected site.
    auto missing=create(1.1f,7,9,.26f,0);missing.arena.rooms[2].sourceHeartTemplate=108;
    check(!missing.enterSourceRoomReview(108),"review requires the complete combat record");
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
