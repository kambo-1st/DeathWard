#include "RoomReviewSeeds.hpp"
#include "combat/Simulation.hpp"
#include "world/SourceCombatRockRooms.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const std::string &why){if(!ok)throw std::runtime_error(why);}
Simulation create(uint64_t seed,float size,int lo,int hi,int mode=1) {
    Simulation r(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),size,lo,hi,.26f,true,mode);
    r.applyCombatBalance(3.5f,1);r.canonicalShooting=true;r.gaperMovementMultiplier=1;return r;
}
void route(const Arena &arena,Vector3 from,Vector3 to,float radius,const std::string &tag) {
    auto path=arena.path(from,to,radius);check(!path.empty(),"path exists "+tag);
    for(auto at:path){check(!arena.blocked(at,radius)&&arena.clear(from,at,radius),"physical route clearance "+tag);from=at;}
    check(planarDistance(from,to)<.001f,"route reaches destination "+tag);
}
void verify(uint64_t seed,int variant,float size,int lo,int hi,bool live) {
    auto r=create(seed,size,lo,hi);int index=-1;
    for(int i=0;i<r.arena.roomCount();++i)if(r.arena.rooms[size_t(i)].sourceCombatTemplate==variant)index=i;
    check(index>=0,"natural template "+std::to_string(variant)+" seed "+std::to_string(seed));
    const auto &source=*sourceCombatRockRoom(variant);const auto layout=r.arena.rooms[size_t(index)];
    const std::string tag="source="+std::to_string(variant)+" seed="+std::to_string(seed)+" size="+std::to_string(size);
    check(index!=2&&index!=3&&layout.story==StoryRoom::None&&layout.sourceObstacleTemplate==variant,"compatible complete room "+tag);
    const auto &enemies=r.roomEnemies(index);check(enemies.size()==source.enemies.size()&&r.floorEncounter(index).monsters.size()==enemies.size(),"exact roster and budget "+tag);
    for(size_t i=0;i<enemies.size();++i){const auto &e=enemies[i];auto cell=source.enemies[i];
        check(e.monster==monsterId(10,1)&&e.champion<0&&e.maxHp==32,"accepted ordinary identity and HP "+tag);
        check(planarDistance(e.position,sourceHeartCell(layout,cell[0],cell[1]))<.001f&&!r.arena.blocked(e.position,e.radius),"legal source placement "+tag);
        route(r.arena,layout.entry,e.position,e.radius,tag);route(r.arena,e.position,layout.entry,e.radius,tag);
    }
    check(std::count_if(r.arena.breakables.begin(),r.arena.breakables.end(),[&](const auto &b){return b.room==index;})==int(source.rocks.size()),"exact rocks "+tag);
    check(layout.obstacles.empty()&&layout.heartSpawns.empty()&&r.arena.supplyCache.room!=index,"no unrelated cover/pickups/cache "+tag);
    for(const auto &m:r.moneyPickups)check(r.arena.roomAt(m.position)!=index,"no initial random coins "+tag);
    for(auto p:layout.passages)route(r.arena,layout.entry,r.arena.doorApproach(p,r.arena.passages[size_t(p)].rooms[0]==index?0:1),.48f,tag);
    route(r.arena,r.arena.rooms[0].entry,layout.entry,.48f,"cross-room "+tag);
    check(r.enterSourceRoomReview(variant)&&r.room==index&&r.livingEnemies()==source.enemies.size(),"direct ordinary review "+tag);
    if(live){r.godMode=true;std::vector<bool> reached(source.enemies.size());std::vector<EntityId> ids;for(const auto &e:r.enemies)ids.push_back(e.id);
        for(int n=0;n<3600;++n){r.step({});for(size_t i=0;i<reached.size();++i)if(auto *e=r.findEnemy(ids[i]);e&&planarDistance(e->position,r.player.position)<1.5f){reached[i]=true;e->alive=false;}}
        // Retire each arriving actor to isolate route completion from crowd blocking.
        check(std::all_of(reached.begin(),reached.end(),[](bool b){return b;}),"all live Gapers reach entry "+tag);
        r.clearRoomDebug();auto kills=r.stats.kills;r.jumpDebug(0);r.jumpDebug(index);check(r.roomClear&&r.livingEnemies()==0&&r.stats.kills==kills,"no respawn on revisit "+tag);
        r.player.hp=4;r.player.attributes.speed=.8f;auto id=r.summary().id;
        r.resizeRooms(size,lo,hi,.26f,std::nullopt,0);check(r.arena.rooms[size_t(index)].sourceCombatTemplate!=variant,"OFF removes complete content "+tag);
        r.resizeRooms(size,lo,hi,.26f,std::nullopt,1);check(r.arena.rooms[size_t(index)].sourceCombatTemplate==variant&&r.player.hp==4&&r.player.attributes.speed==.8f&&r.summary().id==id,"Apply restores while keeping player/identity "+tag);
    }
    std::cout<<"PASS "<<tag<<" room="<<index+1<<" gapers="<<source.enemies.size()<<" rocks="<<source.rocks.size()<<" live="<<live<<'\n';
}
void fightAndRevisit() {
    auto r=create(review::seed(109),1.1f,7,9);r.redHeartClearRewards=r.coinClearRewards=true;const int index=review::room(109);
    check(r.enterSourceRoomReview(109)&&r.room==index&&!r.godMode&&r.player.hp==6,"direct ordinary launch has no cheats");
    r.godMode=true;
    check(!r.roomClear&&r.livingEnemies()==5,"fight begins on entry");
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
    check(r.roomClear&&r.roomThreats()==0&&r.stats.kills>=5&&r.stats.shots>=15,"real shots finish Gapers/successors and clear");
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
    r.resizeRooms(1.1f,7,9,.26f,std::nullopt,0);check(r.arena.rooms[size_t(index)].sourceCombatTemplate!=109,"OFF removes arrangement");
    r.resizeRooms(1.1f,7,9,.26f,std::nullopt,1);check(r.arena.rooms[size_t(index)].sourceCombatTemplate==109,"Apply restores natural source room");
    check(r.summary().id==id&&r.player.hp==4&&r.player.attributes.speed==.8f&&r.player.attributes.damage==7&&r.gaperMovementMultiplier==.65f,"Apply retains player/build/expedition");
    for(const auto &e:r.roomEnemies(index))check(std::abs(e.maxHp-24)<.001f,"regenerated source room uses selected HP multiplier");
    std::cout<<"PASS actual shots/cover/deaths/successors/seals/rewards/demolition/revisit/Apply; shots="<<shots<<" kills="<<kills<<'\n';
}
int main(){try{
    for(int variant:{109,547,548,550})for(auto dims:{std::array<float,3>{.75f,5,5},{1.1f,7,9},{1.5f,10,10}})
        verify(review::seed(variant,dims[0],int(dims[1]),int(dims[2])),variant,dims[0],int(dims[1]),int(dims[2]),dims[0]==.75f);
    fightAndRevisit();
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
