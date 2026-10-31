#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const std::string &message) {if(!value)throw std::runtime_error(message);}
bool overlap(Box a,Box b) {return a.min.x<b.max.x&&a.max.x>b.min.x&&a.min.z<b.max.z&&a.max.z>b.min.z;}
void paths(Arena &arena) {
    for(const auto &room:arena.rooms) {
        check(!arena.blocked(room.center,.48f),"room center remains walkable");
        check(!arena.path(room.center,room.objective,.48f).empty(),"objective reachable");
        for(int link:room.passages) {
            const auto &p=arena.passages[size_t(link)];const int side=p.rooms[0]==int(&room-arena.rooms.data())?0:1;
            check(!arena.path(room.objective,arena.doorApproach(link,side),.48f).empty(),"door approach reachable");
        }
    }
    for(size_t i=0;i<arena.rooms.size();++i)for(size_t j=i+1;j<arena.rooms.size();++j)
        check(!overlap(arena.rooms[i].bounds,arena.rooms[j].bounds),"room envelopes never overlap");
    for(auto &p:arena.passages)p.locked=false;
    arena.rebuildWalls();
    for(size_t i=0;i<arena.passages.size();++i) {
        const auto &p=arena.passages[i];
        const auto from=arena.doorApproach(int(i),0),to=arena.doorApproach(int(i),1);
        const auto path=arena.path(from,to,.48f);
        check(!path.empty(),"corridor has a traversable route");
        Vector3 previous=from;
        for(auto step:path) {check(arena.clear(previous,step,.48f),"corridor route respects terrain and walls");previous=step;}
        for(size_t j=0;j<arena.rooms.size();++j)
            if(int(j)!=p.rooms[0]&&int(j)!=p.rooms[1])check(!overlap(p.floor,arena.rooms[j].bounds),"corridors do not cross unrelated rooms");
    }
}
}
int main() {
    uint64_t seed=0;
    try {
        std::set<CanyonRiverKind> riverKinds;bool road=false;
        for(auto pacing:{ExpeditionPacing::Growing,ExpeditionPacing::Classic,ExpeditionPacing::ShortCorridors,
                         ExpeditionPacing::SmallRooms,ExpeditionPacing::Compact})
            for(seed=0;seed<4;++seed)
                for(auto theme:{MissionTheme::Mine,MissionTheme::Canyon}) {
                    Simulation run(seed,1,{},theme,true,false,WitnessAccount::None,0,pacing);
                    if(pacing==ExpeditionPacing::Compact&&theme==MissionTheme::Canyon) {
                        riverKinds.insert(run.arena.canyon->riverKind);
                        road=road||!run.arena.canyon->road.empty();
                    }
                    paths(run.arena);
                    const auto dims=run.expedition.dimensionsOnFloor(0);
                    for(int i=0;i<run.arena.roomCount();++i) {
                        const auto &room=run.arena.rooms[size_t(i)];
                        const auto width=sub(room.bounds.max,room.bounds.min);
                        if(dims.smallerRooms) {
                            if(room.kind==RoomKind::Boss)check(width.x>=32&&width.z>=32,"compact boss retains maneuvering room");
                            else check(width.x>=20&&width.x<=28&&width.z>=20&&width.z<=28,"ordinary opening rooms use 20-28 metre envelopes");
                        }
                        run.arena.sealRoom(i);
                        for(const auto &enemy:run.roomEnemies(i)) {
                            if(run.content->statue(enemy.monster)) {
                                auto bodies=std::move(run.arena.movementBodies);
                                const bool clear=!run.arena.blocked(enemy.position,enemy.radius);
                                run.arena.movementBodies=std::move(bodies);
                                check(clear,"stationary hazard spawns clear of scenery, excluding its own solid footprint");
                            } else {
                                const auto *definition=run.content->monster(enemy.monster);
                                const bool flying=definition&&definition->flying;
                                // Flying offspring may start over water or low cover. The
                                // walking mask is deliberately stricter than their own mask.
                                const bool blocked=flying?run.arena.flightBlocked(enemy.position,enemy.radius,i):
                                    run.arena.blocked(enemy.position,enemy.radius);
                                if(flying)check(enemy.position.y>=run.arena.flightHeight(enemy.position,enemy.radius)-.001f,
                                    "flying residents clear their supporting surface");
                                if(blocked)std::cerr<<"BLOCKED_RESIDENT pacing="<<int(pacing)<<" theme="<<int(theme)
                                    <<" room="<<i<<" monster="<<monsterIdText(enemy.monster)<<" position="
                                    <<enemy.position.x<<','<<enemy.position.y<<','<<enemy.position.z<<" radius="<<enemy.radius<<'\n';
                                check(!blocked,"smaller floor residents spawn clear of scenery");
                            }
                        }
                        run.arena.sealRoom(-1);
                    }
                    if(pacing==ExpeditionPacing::ShortCorridors) {
                        Arena original(seed,theme,true,false,StoryRoom::None,run.arena.roomCount(),{},run.arena.profile);
                        for(size_t i=0;i<original.rooms.size();++i) {
                            const auto &a=original.rooms[i],&b=run.arena.rooms[i];
                            check(distance(sub(a.bounds.max,a.bounds.min),sub(b.bounds.max,b.bounds.min))<.001f&&a.shape==b.shape,"corridor trial preserves room dimensions and shapes");
                            check(distance(sub(a.objective,a.center),sub(b.objective,b.center))<.001f,"corridor trial preserves relative objectives");
                        }
                    }
                }
        check(riverKinds.contains(CanyonRiverKind::Boundary)&&riverKinds.contains(CanyonRiverKind::Interior)&&road,
              "compact floors retain boundary rivers, interior rivers and dirt roads");
        for(auto pacing:{ExpeditionPacing::ShortCorridors,ExpeditionPacing::SmallRooms,ExpeditionPacing::Compact}) {
            ExpeditionPlan tutorial(42,true,WitnessAccount::None,pacing);
            Arena arena(42,MissionTheme::Canyon,true,true,StoryRoom::None,5,tutorial.dimensionsOnFloor(0));
            check(arena.roomCount()==5&&!tutorial.dimensionsOnFloor(0).smallerRooms,"tutorial retains five original room envelopes");paths(arena);
        }
        const auto compact=ExpeditionPlan(42,false,WitnessAccount::None,ExpeditionPacing::Compact).dimensionsOnFloor(0);
        Arena exhausted(42,MissionTheme::Mine,true,false,StoryRoom::None,15,compact);
        check(exhausted.roomCount()==15,"size-pair exhaustion terminates with valid repeated dimensions");paths(exhausted);
        for(auto story:{StoryRoom::SurveyCamp,StoryRoom::SplitRock,StoryRoom::RailwayCutting,StoryRoom::DryCreek}) {
            Arena arena(42,MissionTheme::Canyon,true,false,story,9,compact);
            check(!arena.storyProps.empty(),"compact story room retains landmark dressing");paths(arena);
        }
        for(bool click:{false,true}) {
            Simulation run(1,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Growing);
            run.godMode=true;run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.keys=3;
            const int link=run.arena.rooms.back().passages.front();
            const auto &p=run.arena.passages[size_t(link)];const int side=p.rooms[0]==run.room?0:1;
            const int next=p.rooms[size_t(1-side)];
            run.player.position=run.arena.doorApproach(link,side);
            run.arena.altar=run.arena.doorApproach(link,1-side);
            if(click) {Input input;input.doorTarget=std::pair{link,side};run.step(input);}
            else check(run.useDoor(link,side),"passage regression unlocks the door");
            for(int frame=0;frame<1200&&run.room!=next;++frame)run.step({});
            check(run.room==next&&!run.altarDestroyed,"explicit passage travel crosses the threshold without activating a nearby altar");
        }
        std::cout<<"PASS separate pacing trials, room/corridor collision, objectives, spawns, boss space, tutorial and size exhaustion\n";
    } catch(const std::exception &e) {std::cerr<<"FAIL seed "<<seed<<": "<<e.what()<<'\n';return 1;}
}
