#include "combat/Simulation.hpp"
#include "world/PedestalGeometry.hpp"

namespace dw {
namespace {
// Review travel only: choose real clear floor inside the destination, not its
// corridor entry coordinate. It never heals, clears an encounter or refills charge.
std::optional<Vector3> reviewPosition(const Simulation &s,int index,Vector3 preferred) {
    std::optional<Vector3> best;float score=std::numeric_limits<float>::infinity();
    for(const auto &cell:s.arena.floorCells) {
        const Vector3 at{(cell.first+.5f)*FloorTile,.85f,(cell.second+.5f)*FloorTile};
        if(s.arena.roomAt(at)!=index||s.arena.blocked(at,.48f))continue;
        const auto &site=s.arena.rooms[size_t(index)];
        if(at.x<site.bounds.min.x+1.1f||at.x>site.bounds.max.x-1.1f||at.z<site.bounds.min.z+1.1f||at.z>site.bounds.max.z-1.1f)continue;
        if(std::any_of(s.roomEnemies(index).begin(),s.roomEnemies(index).end(),[&](const auto &e){return e.alive&&planarDistance(e.position,at)<e.radius+2;}))continue;
        const float d=planarDistance(at,preferred);if(d<score){best=at;score=d;}
    }
    return best;
}
}
bool Simulation::beginTrinketReview() {
    if(floor!=0||surveyTutorial||stats.duration!=0||!items.empty()||activeItem||heldTrinket||powerupReview||!trinketPickups.empty())return false;
    const auto start=reviewPosition(*this,0,arena.rooms.front().center);if(!start)return false;
    std::vector<Vector3> points;
    for(int side:{-1,1}) {
        std::optional<Vector3> best;float score=std::numeric_limits<float>::infinity();
        for(const auto &cell:arena.floorCells) {
            const Vector3 at{(cell.first+.5f)*FloorTile,.85f,(cell.second+.5f)*FloorTile};
            const float distance=planarDistance(at,*start);
            if(distance<2.5f||distance>5||arena.roomAt(at)!=0||arena.blocked(at,.48f)||arena.path(*start,at,.48f).empty()||
               (!points.empty()&&planarDistance(at,points.front())<4))continue;
            const float d=planarDistance(at,add(*start,{side*3.f,0,side*3.f}));
            if(d<score){best=at;score=d;}
        }
        if(!best)return false;points.push_back(*best);
    }
    if(!content->item(CancerKey)||!content->item(WhipWormKey))return false;
    if(!spawnTrinket(points[0],CancerKey,1,true)||!spawnTrinket(points[1],WhipWormKey,2,true))return false;
    player.position=*start;cancelMove();enterRoom(0);
    announce("TRINKET REVIEW / Two test pickups: Cancer and Whip Worm",5);
    checkpointNeeded=true;return true;
}
bool Simulation::beginPowerupReview() {
    if(floor!=0||surveyTutorial||stats.duration!=0||!items.empty()||activeItem||heldTrinket||powerupReview)return false;
    int target=-1;for(int i=0;i<arena.roomCount();++i)if(hasSourceTreasure(i)){target=i;break;}
    if(target<0)return false;
    const auto at=rewardPosition(target);
    const auto start=reviewPosition(*this,target,add(at,{0,0,4}));if(!start)return false;
    std::optional<Vector3> charm;float best=std::numeric_limits<float>::infinity();
    for(const auto &cell:arena.floorCells) {
        const Vector3 p{(cell.first+.5f)*FloorTile,.85f,(cell.second+.5f)*FloorTile};
        const float d=planarDistance(p,at);
        if(d<2.5f||d>5||arena.roomAt(p)!=target||arena.blocked(p,.48f)||arena.path(*start,p,.48f).empty())continue;
        const float score=planarDistance(p,add(at,{3,0,0}));if(score<best){best=score;charm=p;}
    }
    if(!charm||!spawnTrinket(*charm,CancerKey,1,true))return false;
    powerupReview=PowerupReviewState{target,0};
    player.position=*start;cancelMove();enterRoom(target);
    announce("CATEGORY REVIEW / Four test pedestal offerings + Cancer. Step away between pickups.",8);
    checkpointNeeded=true;return true;
}
bool Simulation::visitPowerupReviewEncounter(bool bossRoom) {
    if(!powerupReview||powerupReview->collected<4||!roomClear||dead||finished||rewardOpen||shopOpen||
       letterOpen||storyOpen!=StoryRoom::None||floorExitRequested)return false;
    int target=-1;
    if(bossRoom)target=finalRoom();
    else for(int i=1;i<finalRoom();++i) {
        const auto &site=arena.rooms[size_t(i)];
        if(i==room||site.kind!=RoomKind::Combat||site.story!=StoryRoom::None||rooms[size_t(i)].cleared||
           rooms[size_t(i)].trapOnly||rooms[size_t(i)].plateObjective)continue;
        if(target<0)target=i;
        if(site.sourceCombatTemplate==47){target=i;break;}
    }
    if(target<0||target==room)return false;
    // Start on interior floor, away from the canyon lip at the corridor entry.
    // The normal enemy-clearance checks still apply; this changes only review travel.
    const auto point=reviewPosition(*this,target,arena.rooms[size_t(target)].center);if(!point)return false;
    player.position=*point;cancelMove();enterRoom(target);
    announce("CATEGORY REVIEW / Ordinary encounter / no health or charge refill",4);
    checkpointNeeded=true;return true;
}
} // namespace dw
