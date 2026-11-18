#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourcePropRooms.hpp"
#include "world/PedestalGeometry.hpp"
#include <iostream>
#include <set>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
Simulation generated(uint64_t seed,float scale,int lo,int hi,int layouts=1,int props=1,int boss=67,int floor=0) {
    Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,
        defaultMechanics(),scale,lo,hi,.26f,true,layouts,true,true,true,true,true,true,1,1,
        MonstroTuning{boss==20},DukeTuning{boss==67},false,255,RoomPropsTuning{props});
    s.attackFlyMovementMultiplier=1;s.canonicalShooting=true;s.applyCombatBalance(3.5f,1);return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();
}
void arrangement(Simulation &s) {
    const auto &r=s.arena.rooms.back();const auto &source=*sourcePropRoom(RecordedDukeRoom);
    check(r.kind==RoomKind::Boss&&r.sourceCombatTemplate==RecordedDukeRoom&&r.sourceObstacleTemplate==RecordedDukeRoom,"complete recorded boss arrangement selected");
    check(source.type==5&&source.subtype==13&&source.entries.size()==8,"full source boss identity and slots");
    check(s.roomEnemyCount(s.finalRoom())==2&&s.roomEnemies(s.finalRoom()).size()==2,"exact initial two actors");
    int rocks=0,poop=0;std::set<uint64_t> ids;
    for(const auto &p:s.arena.breakables){check(ids.insert(p.id).second,"unique prop IDs");if(p.room==s.finalRoom()){rocks+=p.kind==BreakableKind::CrackedRock;poop+=p.kind==BreakableKind::Dung;}}
    check(rocks==4&&poop==2,"exact four rocks and two poop grids");
    for(const auto &slot:source.entries) {
        const auto at=sourcePropCell(r,source,slot.x,slot.y);
        if(slot.type<1000) {
            const auto &actors=s.roomEnemies(s.finalRoom());const auto e=std::find_if(actors.begin(),actors.end(),[&](const auto &e){return e.monster==monsterId(slot.type);});
            check(e!=actors.end()&&planarDistance(at,e->position)<.0001f&&!e->dukeChild&&!e->summoner&&e->champion<0,"original actor cells; initial fly is independent, not an offspring/champion");
            check(std::abs(e->hp-(slot.type==67?352:16))<.001f,"existing boss and regular source HP units");
            check(!s.arena.flightBlocked(e->position,e->radius,s.finalRoom()),"fly body is clear of terrain");
        } else {
            const auto p=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.room==s.finalRoom()&&p.sourceGridIndex==(slot.y+1)*15+slot.x+1;});
            check(p!=s.arena.breakables.end()&&planarDistance(at,p->rewardPosition)<.0001f&&p->lootSeed==propSlotSeed(r.sourceRoomSpawnSeed,slot.ordinal),"original prop cells and slot RNG sequence");
            check(s.arena.blocked(at,.48f),"visible props have real collision");
        }
    }
    check(!s.arena.blocked(r.entry,.48f)&&!s.arena.blocked(r.exit,.48f),"entrance and retained floor exit stay clear");
    check(!s.arena.path(r.entry,r.exit,.48f).empty()&&!s.arena.path(r.entry,r.center,.48f).empty(),"player can reach exit and central reward area");
    check(r.heartSpawns.empty()&&r.coinSpawns.empty()&&r.chestSpawns.empty(),"no extra initial pickups");
}
void loop(uint64_t seed,float scale,int lo,int hi) {
    auto s=generated(seed,scale,lo,hi);arrangement(s);
    check(s.enterSourceRoomReview(RecordedDukeRoom)&&s.player.hp==6&&!s.godMode,"normal-health direct entry into genuine generated boss room");
    check(planarDistance(s.player.position,s.arena.rooms.back().center)<6.01f&&!s.arena.blocked(s.player.position,.55f),"direct review starts near visible boss on clear floor");
    EntityId boss=0,fly=0;for(const auto &e:s.enemies){if(e.duke)boss=e.id;else if(e.monster==monsterId(18))fly=e.id;}
    check(boss&&fly&&!s.canUseFloorExit()&&!s.rewardAvailable(s.room),"fight locks reward and descent");
    s.godMode=true;damage(s,boss,10000);ticks(s,2);
    std::vector<EntityId> children;for(const auto &e:s.enemies)if(e.alive&&e.dukeChild)children.push_back(e.id);
    check(children.size()==6&&!s.roomClear,"existing six death offspring retained");
    for(auto id:children)damage(s,id,10000);ticks(s,2);
    check(s.livingEnemies()==1&&s.findEnemy(fly)->alive&&!s.roomClear&&!s.rewardAvailable(s.room)&&!s.canUseFloorExit(),"independent initial fly alone still seals the room");
    // Kill the final ordinary fly with real player shots and the retained aim path.
    for(int n=0;n<1200&&s.findEnemy(fly)&&s.findEnemy(fly)->alive;++n) {
        Input in;const auto at=s.findEnemy(fly)->position;
        for(auto dir:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}) {
            auto p=add(at,mul(dir,2.5f));p.y=.85f;
            if(s.arena.roomAt(p)==s.room&&!s.arena.blocked(p,.48f)&&s.arena.clear(p,at,.15f)){s.player.position=p;in.fire=true;in.aim=at;break;}
        }
        s.step(in);
    }
    s.player.position=s.arena.rooms.back().entry;ticks(s,4);
    check(s.roomClear&&s.stats.shots>=2&&s.rewardAvailable(s.room)&&s.canUseFloorExit(),"real shots finish initial fly and unlock normal reward/descent");
    auto prop=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.room==s.room&&p.kind==BreakableKind::Dung;});
    const auto propId=prop->id;bool destroyed=false;
    for(auto dir:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}) {
        auto p=add(prop->rewardPosition,mul(dir,(prop->bounds.max.x-prop->bounds.min.x)*.5f+1));p.y=.85f;
        if(s.arena.blocked(p,.48f)||s.arena.roomAt(p)!=s.room)continue;
        s.player.position=p;Input in;in.fire=true;in.aim=prop->rewardPosition;
        for(int n=0;n<480&&!prop->destroyed;++n)s.step(in);
        if(prop->destroyed){destroyed=true;break;}
    }
    check(destroyed&&prop->propReward.resolved,"actual shots destroy source poop and resolve reward once");
    s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);
    check(s.collectTreasureUpgrade()&&s.itemStacks({"isaac",ItemKind::Collectible,255})==1&&!s.collectTreasureUpgrade(),"selected Screw reward collected once");
    const int room=s.room;s.enterRoom(0);s.enterRoom(room);
    prop=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &p){return p.id==propId;});
    check(s.roomThreats()==0&&prop->destroyed&&!s.rewardAvailable(room),"revisit retains kills, destruction and reward");
    s.player.position=s.arena.exit;s.interact();check(s.floorExitRequested&&s.advanceFloor()&&s.itemStacks({"isaac",ItemKind::Collectible,255})==1,"ordinary descent retains reward");
    check(s.arena.rooms.back().sourceCombatTemplate!=RecordedDukeRoom,"recorded boss arrangement is opening-floor-only");
    std::cout<<"PASS Duke arrangement seed="<<seed<<" scale="<<scale<<" room="<<room+1<<" initial fly gate, real shots, props, reward/revisit/descent\n";
}
void boundaries() {
    for(int layout:{0,2}){auto s=generated(11,1.1f,7,9,layout);check(!s.enterSourceRoomReview(RecordedDukeRoom),"non-source layout excludes recorded boss contents");}
    for(int props:{0,2}){auto s=generated(11,1.1f,7,9,1,props);check(!s.enterSourceRoomReview(RecordedDukeRoom),"legacy/test props preserve bare boss");}
    auto monstro=generated(11,1.1f,7,9,1,1,20);check(!monstro.enterSourceRoomReview(RecordedDukeRoom),"Monstro remains unchanged");
    auto s=generated(11,1.1f,7,9);check(s.enterSourceRoomReview(RecordedDukeRoom),"review for Apply");
    s.attackFlyMovementMultiplier=.65f;s.player.hp=4;s.resizeRooms(.75f,5,5,.26f,std::nullopt,0);
    check(s.player.hp==4&&s.attackFlyMovementMultiplier==.65f&&s.arena.rooms.back().sourceCombatTemplate!=RecordedDukeRoom,"unrestricted Apply retains player/tuning and removes arrangement when OFF");
    s.resizeRooms(1.1f,7,9,.26f,std::nullopt,1);arrangement(s);
    check(!s.arena.blocked(s.player.position,.48f),"Apply cannot place player inside restored props");
    std::cout<<"PASS SOURCE/PROPS/boss boundaries and unrestricted Apply\n";
}
}
int main(){try{std::cout<<std::unitbuf;loop(11,.75f,5,5);loop(11,1.1f,7,9);loop(11,1.5f,10,10);boundaries();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
