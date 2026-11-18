#include "world/SourcePropRooms.hpp"
#include "combat/Simulation.hpp"
#include "combat/ChestGeometry.hpp"
#include "world/PedestalGeometry.hpp"
#include "world/ShopCartGeometry.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/SourceCombatRockRooms.hpp"
#include "world/SourceChestRockRoomData.hpp"
#include "world/SourceCoinRockRoomData.hpp"
#include "world/SourceKeyRockRoomData.hpp"
#include "world/SourceBombRockRoomData.hpp"
#include <map>
#include <queue>

namespace dw {
namespace {
Vector3 center(FloorCell c, float y, float step=FloorTile) {
    return {(float(c.first) + 0.5f) * step, y, (float(c.second) + 0.5f) * step};
}
std::vector<Vector3> floorPath(const Arena &arena, Vector3 from, Vector3 target, float radius,
                             const std::set<FloorCell> &cells, int flightRoom=-1, float step=FloorTile,bool swimming=false,Vector3 origin={}) {
    auto blocked=[&](Vector3 p){return swimming?arena.swimBlocked(p,radius,flightRoom):flightRoom<0?arena.blocked(p,radius):arena.flightBlocked(p,radius,flightRoom);};
    auto clear=[&](Vector3 a,Vector3 b){return swimming?arena.swimClear(a,b,radius,flightRoom):flightRoom<0?arena.clear(a,b,radius):arena.flightClear(a,b,radius,flightRoom);};
    auto atCell=[&](FloorCell c){return add(center(c,from.y,step),origin);};
    const bool targetWasBlocked = blocked(target);
    // A demolished source-rock pocket can fit the player between coarse grid
    // nodes. Accept a physically clear segment before requiring grid anchors.
    // Both endpoints must be valid; blocked-click relocation still runs below.
    if(!targetWasBlocked&&!blocked(from)&&clear(from,target))return {target};
    auto nearest = [&](Vector3 p, bool requireSight) -> std::optional<FloorCell> {
        std::optional<FloorCell> result;
        float best = std::numeric_limits<float>::infinity();
        for (const auto &cell : cells) {
            Vector3 at = atCell(cell);
            float d = distance(at, p);
            if (d >= best || (requireSight && d > 6))
                continue;
            if (!blocked(at) && (!requireSight || clear(p, at))) {
                result = cell;
                best = d;
            }
        }
        return result;
    };
    const auto start = nearest(from, true), goal = nearest(target, !targetWasBlocked);
    if (!start || !goal)
        return {};
    if (targetWasBlocked)
        target = atCell(*goal);
    if (clear(from, target))
        return {target};
    struct Node {
        float cost = std::numeric_limits<float>::infinity();
        FloorCell previous{};
    };
    using Entry = std::pair<float, FloorCell>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> frontier;
    std::map<FloorCell, Node> nodes;
    auto heuristic = [&](FloorCell c) {
        return float(std::abs(c.first - goal->first) + std::abs(c.second - goal->second)) * step;
    };
    nodes[*start] = {0, *start};
    frontier.push({heuristic(*start), *start});
    while (!frontier.empty()) {
        auto [score, current] = frontier.top();
        frontier.pop();
        if (score > nodes[current].cost + heuristic(current) + 0.001f)
            continue;
        if (current == *goal)
            break;
        for (auto [dx, dz] : {FloorCell{0, -1}, FloorCell{1, 0}, FloorCell{0, 1}, FloorCell{-1, 0}}) {
            FloorCell next{current.first + dx, current.second + dz};
            if (!cells.contains(next))
                continue;
            float cost = nodes[current].cost + step;
            if (nodes.contains(next) && cost >= nodes[next].cost)
                continue;
            Vector3 p = atCell(next);
            if (blocked(p) || !clear(atCell(current), p))
                continue;
            nodes[next] = {cost, current};
            frontier.push({cost + heuristic(next), next});
        }
    }
    if (!nodes.contains(*goal))
        return {};
    std::vector<Vector3> reverse{target};
    for (auto at = *goal;; at = nodes[at].previous) {
        reverse.push_back(atCell(at));
        if (at == *start)
            break;
    }
    std::reverse(reverse.begin(), reverse.end());
    std::vector<Vector3> path;
    // Smooth the tile route into long segments while retaining real 3D clearance.
    Vector3 anchor = from;
    for (size_t i = 0; i < reverse.size();) {
        size_t end = i;
        while (end + 1 < reverse.size() && clear(anchor, reverse[end + 1]))
            ++end;
        path.push_back(reverse[end]);
        anchor = reverse[end];
        i = end + 1;
    }
    return path;
}
// Selected source rocks leave real aisles between the ordinary two-unit
// navigation samples. Align a bounded fallback to the placed source cells.
// This is canyon navigation, not native AI; every edge retains full collision.
std::vector<Vector3> sourceRockPath(const Arena &arena,int index,Vector3 from,Vector3 target,float radius) {
    const auto &layout=arena.rooms[size_t(index)];
    const auto *props=sourcePropRoom(layout.sourceObstacleTemplate);
    const float step=(props?sourcePropCellSize(layout,*props):sourceHeartCellSize(layout))*.5f;
    const Vector3 origin{layout.center.x-step*.5f,0,layout.center.z-step*.5f};
    std::set<FloorCell> cells;
    for(int x=int(std::floor((layout.bounds.min.x-origin.x-FloorTile)/step));x<int(std::ceil((layout.bounds.max.x-origin.x+FloorTile)/step));++x)
        for(int z=int(std::floor((layout.bounds.min.z-origin.z-FloorTile)/step));z<int(std::ceil((layout.bounds.max.z-origin.z+FloorTile)/step));++z)
            cells.insert({x,z});
    return floorPath(arena,from,target,radius,cells,-1,step,false,origin);
}
} // namespace
std::vector<Vector3> Arena::flightPath(Vector3 from,Vector3 target,float radius,int room) const {
    target.y=from.y;
    if(flightClear(from,target,radius,room))return {target};
    std::set<FloorCell> cells;
    const auto &area=rooms.at(size_t(room)).bounds;
    for(int z=int(std::floor(area.min.z));z<int(std::ceil(area.max.z));++z)
        for(int x=int(std::floor(area.min.x));x<int(std::ceil(area.max.x));++x)
            cells.insert({x,z});
    return floorPath(*this,from,target,radius,cells,room,1);
}
std::vector<Vector3> Arena::swimPath(Vector3 from,Vector3 target,float radius,int room) const {
    target.y=from.y;if(swimClear(from,target,radius,room))return {target};
    std::set<FloorCell> cells;const auto &area=rooms.at(size_t(room)).bounds;
    for(int z=int(std::floor(area.min.z));z<int(std::ceil(area.max.z));++z)
        for(int x=int(std::floor(area.min.x));x<int(std::ceil(area.max.x));++x)cells.insert({x,z});
    return floorPath(*this,from,target,radius,cells,room,1,true);
}
std::vector<Vector3> Arena::path(Vector3 from, Vector3 target, float radius) const {
    target.y = from.y;
    if (!floorCells.empty()) {
        auto route=floorPath(*this,from,target,radius,floorCells);
        if(route.empty()) {
            const int start=roomAt(from),goal=roomAt(target);
            const auto sourceRoom=[&](int i){return i>=0&&(sourcePropRoom(rooms[size_t(i)].sourceObstacleTemplate)||sourceCombatRockRoom(rooms[size_t(i)].sourceObstacleTemplate)||
                rooms[size_t(i)].sourceObstacleTemplate==SourceChestRockRoom||
                rooms[size_t(i)].sourceObstacleTemplate==SourceCoinRockRoom||
                rooms[size_t(i)].sourceObstacleTemplate==SourceKeyRockRoom||
                rooms[size_t(i)].sourceObstacleTemplate==SourceBombRockRoom);};
            const bool sourceStart=sourceRoom(start),sourceGoal=sourceRoom(goal);
            if(sourceStart&&start==goal)return sourceRockPath(*this,start,from,target,radius);
            if(sourceStart||sourceGoal) {
                struct Port {Vector3 point;std::vector<Vector3> path;};
                auto ports=[&](int index,Vector3 point,bool outgoing) {
                    std::vector<Port> result;
                    if(!sourceRoom(index)){result.push_back({point,{}});return result;}
                    for(int p:rooms[size_t(index)].passages) {
                        const auto at=doorApproach(p,passages[size_t(p)].rooms[0]==index?0:1);
                        auto local=outgoing?sourceRockPath(*this,index,point,at,radius):sourceRockPath(*this,index,at,point,radius);
                        if(!local.empty())result.push_back({at,std::move(local)});
                    }
                    return result;
                };
                float best=std::numeric_limits<float>::infinity();
                const auto starts=ports(start,from,true),goals=ports(goal,target,false);
                for(const auto &a:starts)for(const auto &b:goals) {
                    auto middle=floorPath(*this,a.point,b.point,radius,floorCells);
                    if(middle.empty())continue;
                    auto combined=a.path;combined.insert(combined.end(),middle.begin(),middle.end());
                    combined.insert(combined.end(),b.path.begin(),b.path.end());
                    float cost=0;auto previous=from;
                    for(auto at:combined){cost+=planarDistance(previous,at);previous=at;}
                    if(cost<best){best=cost;route=std::move(combined);}
                }
                return route;
            }
        }
        auto inRails=[&](Vector3 p) {return rails&&p.x>=rails->bounds.min.x&&p.x<=rails->bounds.max.x&&
            p.z>=rails->bounds.min.z&&p.z<=rails->bounds.max.z;};
        if(!route.empty()||!inRails(from)||!inRails(target))return route;
        // Authored rocks can leave a physically passable aisle between the
        // ordinary two-unit navigation nodes. Refine only a failed local rail
        // arena query; retain the same grounded collision and pit checks.
        constexpr float precision=.5f;std::set<FloorCell> fine;
        for(int x=int(std::floor(rails->bounds.min.x/precision));x<int(std::ceil(rails->bounds.max.x/precision));++x)
            for(int z=int(std::floor(rails->bounds.min.z/precision));z<int(std::ceil(rails->bounds.max.z/precision));++z)
                fine.insert({x,z});
        return floorPath(*this,from,target,radius,fine,-1,precision);
    }
    target.x = std::clamp(target.x, bounds.min.x + 0.7f, bounds.max.x - 0.7f);
    target.z = std::clamp(target.z, bounds.min.z + 0.7f, bounds.max.z - 0.7f);
    const float margin = radius + 0.08f;
    auto navigationWalls=walls;
    navigationWalls.insert(navigationWalls.end(),movementBodies.begin(),movementBodies.end());
    // Bounding corners supply route candidates; clearance uses the octagon.
    for(const auto &room:rooms)if(room.kind==RoomKind::Power)
        navigationWalls.push_back(pedestalGeometry::bounds(room.objective));
    if(bossRewardPedestal)navigationWalls.push_back(pedestalGeometry::bounds(*bossRewardPedestal));
    for(const auto &room:rooms)if(room.kind==RoomKind::Shop)navigationWalls.push_back(shopCartGeometry::bounds(room.center));
    auto valid = [&](Vector3 p) { return contains(p) && !blocked(p, radius); };
    // A click on solid cover lands at its nearest walkable edge.
    if (blocked(target, radius)) {
        std::optional<Vector3> nearest;
        float best = std::numeric_limits<float>::infinity();
        for (const auto &wall : navigationWalls) {
            const std::array<Vector3, 4> edges{
                {{wall.min.x - margin, from.y,
                  std::clamp(target.z, wall.min.z - margin, wall.max.z + margin)},
                 {wall.max.x + margin, from.y,
                  std::clamp(target.z, wall.min.z - margin, wall.max.z + margin)},
                 {std::clamp(target.x, wall.min.x - margin, wall.max.x + margin), from.y,
                  wall.min.z - margin},
                 {std::clamp(target.x, wall.min.x - margin, wall.max.x + margin), from.y,
                  wall.max.z + margin}}};
            for (auto p : edges) {
                float d = distance(p, target);
                if (valid(p) && d < best) {
                    nearest = p;
                    best = d;
                }
            }
        }
        if (!nearest)
            return {};
        target = *nearest;
    }
    auto clear = [&](Vector3 a, Vector3 b) {
        return this->clear(a,b,radius);
    };
    if (clear(from, target))
        return {target};

    // The arena has a handful of rectangular obstacles. A small visibility graph
    // around their expanded corners provides exact routes without a terrain grid.
    std::vector<Vector3> nodes{from, target};
    for (const auto &wall : navigationWalls) {
        for (float x : {wall.min.x - margin, wall.max.x + margin}) {
            for (float z : {wall.min.z - margin, wall.max.z + margin}) {
                Vector3 p{x, from.y, z};
                if (valid(p))
                    nodes.push_back(p);
            }
        }
    }
    const size_t count = nodes.size();
    std::vector<float> cost(count, std::numeric_limits<float>::infinity());
    std::vector<size_t> previous(count, count);
    std::vector<bool> visited(count, false);
    cost[0] = 0;
    for (size_t step = 0; step < count; ++step) {
        size_t current = count;
        for (size_t i = 0; i < count; ++i) {
            if (!visited[i] && std::isfinite(cost[i]) && (current == count || cost[i] < cost[current]))
                current = i;
        }
        if (current == count)
            return {};
        if (current == 1)
            break;
        visited[current] = true;
        for (size_t i = 0; i < count; ++i) {
            if (visited[i])
                continue;
            float candidate = cost[current] + distance(nodes[current], nodes[i]);
            if (candidate < cost[i] && clear(nodes[current], nodes[i])) {
                cost[i] = candidate;
                previous[i] = current;
            }
        }
    }
    if (previous[1] == count)
        return {};
    std::vector<Vector3> route;
    for (size_t at = 1; at != 0; at = previous[at])
        route.push_back(nodes[at]);
    std::reverse(route.begin(), route.end());
    return route;
}

void Simulation::cancelMove() {
    movePath_.clear();
    waypoint_ = 0;
    interactOnArrival_ = false;
    doorOnArrival_.reset();
}
void Simulation::requestMove(Vector3 target, bool interactAtDestination) {
    target.y = player.position.y;
    cancelMove();
    // An explicit passage command must reach its threshold even when an altar,
    // shop or cache happens to lie near the approach. Ground clicks may interact.
    if(!interactAtDestination) {
        movePath_=arena.path(player.position,target,.48f);
        return;
    }
    // A chest click means approach its reachable edge, not its blocked center.
    // Choose by actual path length so cover and other bodies still participate.
    for(const auto &chest:chests)if(chest.room==room&&
        std::abs(target.x-chest.position.x)<=chestGeometry::HalfWidth+.35f&&
        std::abs(target.z-chest.position.z)<=chestGeometry::HalfDepth+.35f) {
        const float x=chestGeometry::StopX+.04f,z=chestGeometry::StopZ+.04f;
        const auto at=chest.position;
        const float alignX=std::clamp(player.position.x,at.x-chestGeometry::HalfWidth,at.x+chestGeometry::HalfWidth);
        const float alignZ=std::clamp(player.position.z,at.z-chestGeometry::HalfDepth,at.z+chestGeometry::HalfDepth);
        const std::array<Vector3,4> approaches{{{at.x-x,target.y,alignZ},{at.x+x,target.y,alignZ},
                                              {alignX,target.y,at.z-z},{alignX,target.y,at.z+z}}};
        float best=std::numeric_limits<float>::infinity();
        for(auto point:approaches) {
            if(arena.blocked(point,chestGeometry::PlayerRadius))continue;
            auto route=arena.path(player.position,point,chestGeometry::PlayerRadius);
            if(route.empty())continue;
            float cost=0;auto previous=player.position;
            for(auto next:route){cost+=planarDistance(previous,next);previous=next;}
            if(cost<best){best=cost;movePath_=std::move(route);}
        }
        if(movePath_.empty())announce("That chest cannot be reached.",2);
        return;
    }
    for(const auto &bomb:suppliedBombs)if(bomb.room==room&&bomb.state==SuppliedBombState::Pickup&&
        planarDistance(target,bomb.charge.position)<.65f) {
        target=bomb.charge.position;target.y=player.position.y;
        movePath_=arena.path(player.position,target,.48f);return;
    }
    const auto &site=arena.rooms[size_t(room)];
    if(site.kind==RoomKind::Shop&&std::abs(target.x-site.center.x)<shopCartGeometry::HalfWidth+.2f&&
       std::abs(target.z-site.center.z)<shopCartGeometry::HalfDepth+.2f) {
        float best=std::numeric_limits<float>::infinity();
        for(float side:{-1.f,1.f}) {
            const Vector3 point{site.center.x,target.y,site.center.z+side*(shopCartGeometry::HalfDepth+.6f)};
            auto route=arena.path(player.position,point,.48f);if(route.empty())continue;
            float cost=0;auto previous=player.position;
            for(auto next:route){cost+=planarDistance(previous,next);previous=next;}
            if(cost<best){best=cost;movePath_=std::move(route);}
        }
        interactOnArrival_=!movePath_.empty()&&!hasSourceShop(room);
        if(movePath_.empty())announce("That shop cannot be reached.",2);
        return;
    }
    // The stone stays solid after collection. Clicking it approaches a legal
    // edge; source collectibles pay on contact, legacy relics retain their menu.
    const auto pedestal=rewardPosition(room);
    if((site.kind==RoomKind::Power||(hasSourceBoss(room)&&arena.bossRewardPedestal))&&planarDistance(target,pedestal)<2.4f) {
        float best=std::numeric_limits<float>::infinity();
        auto consider=[&](Vector3 direction) {
            const auto point=pedestalGeometry::approach(pedestal,direction,target.y);
            if(arena.blocked(point,pedestalGeometry::PlayerRadius))return;
            auto route=arena.path(player.position,point,pedestalGeometry::PlayerRadius);
            if(route.empty())return;
            float cost=0;auto previous=player.position;
            for(auto next:route){cost+=planarDistance(previous,next);previous=next;}
            if(cost<best){best=cost;movePath_=std::move(route);}
        };
        consider(sub(player.position,pedestal));
        for(auto normal:pedestalGeometry::Normals)consider(normal);
        interactOnArrival_=!movePath_.empty()&&rewardAvailable(room)&&!hasSourceTreasure(room);
        if(movePath_.empty())announce("That pedestal cannot be reached.",2);
        return;
    }
    if(site.story!=StoryRoom::None&&roomClear&&distance(target,site.objective)<2.4f) {
        target=site.objective;interactOnArrival_=true;
    } else if(surveyTutorial && room==finalRoom() && roomClear && distance(target,surveyPosition())<2.4f) {
        target=surveyPosition();interactOnArrival_=true;
    } else if (((room == arena.shopRoom&&!hasSourceShop(room)) || site.kind==RoomKind::Service) && distance(target, arena.rooms[size_t(room)].objective) < 2.4f) {
        target = arena.rooms[size_t(room)].objective;
        interactOnArrival_ = true;
    } else if (canUseFloorExit() && distance(target, arena.exit) < 2.4f) {
        target = arena.exit;
        interactOnArrival_ = true;
    }
    movePath_ = arena.path(player.position, target, 0.48f);
    if (movePath_.empty()) {
        interactOnArrival_ = false;
        announce("That point cannot be reached.", 2);
    }
}
std::string Simulation::nearbyInteraction() const {
    const auto &site=arena.rooms[size_t(room)];
    if(hasSourceShop(room)&&shopVariationActive()&&!shopUpgradeSold&&planarDistance(player.position,shopUpgradePosition())<2.6f)
        return "STEAM SALE / "+std::to_string(shopPrice(shopUpgradePrice,shopUpgradeSlot))+" COINS / WALK UP TO BUY";
    if(hasSourceShop(room)&&shopKeyOffered()&&!shopKeySold&&planarDistance(player.position,shopKeyPosition())<2.6f&&
       (!shopHeartOffered()||shopHeartSold||planarDistance(player.position,shopKeyPosition())<planarDistance(player.position,shopHeartPosition()))) {
        if(keys>=99)return "KEY / INVENTORY FULL";
        return "KEY / "+std::to_string(shopPrice(shopKeyPrice,shopKeySlot))+" COINS / WALK UP TO BUY";
    }
    if(hasSourceShop(room)&&shopHeartOffered()&&!shopHeartSold&&planarDistance(player.position,shopHeartPosition())<2.6f) {
        if(player.hp>=player.redHealthCapacity())return "RED HEART / HEALTH FULL";
        return "RED HEART / "+std::to_string(shopPrice(shopHeartPrice,shopHeartSlot))+" COINS / WALK UP TO BUY";
    }
    if(site.story!=StoryRoom::None&&roomClear&&distance(player.position,site.objective)<2.6f&&arena.sight(player.position,site.objective))
        return "EXAMINE SITE";
    if(surveyTutorial && room==finalRoom() && roomClear && distance(player.position,surveyPosition())<2.6f &&
       arena.sight(player.position,surveyPosition()))return surveyRecovered?"READ LETTER":"RECOVER RECORDS";
    if (((room == arena.shopRoom&&!hasSourceShop(room)) || site.kind==RoomKind::Service) && distance(player.position, arena.rooms[size_t(room)].objective) <= 2.6f &&
        arena.sight(player.position, arena.rooms[size_t(room)].objective))
        return "TRADE";
    if (rewardAvailable(room)&&distance(player.position,rewardPosition(room))<2.6f&&arena.sight(player.position,rewardPosition(room)))
        return hasSourceTreasure(room)?(content->item({"isaac",ItemKind::Collectible,uint32_t(treasureUpgradeItem(room))})->name+" / TOUCH TO COLLECT"):"CLAIM POWER";
    if (canUseFloorExit() && distance(player.position, arena.exit) < 2.8f)
        return !lastFloor()?"NEXT FLOOR":surveyTutorial||testimony()?"RETURN TO FORT":"RETURN HOME";
    if (roomClear)
        for (size_t i = 0; i < arena.passages.size(); ++i)
            for (int side = 0; side < 2; ++side)
                if (arena.passages[i].rooms[size_t(side)]==room&&distance(player.position, arena.doorApproach(int(i), side)) < 2.8f)
                    return arena.passages[i].locked ? keyedDoorCost==0?"UNLOCK (FREE)":
                        "UNLOCK ("+std::to_string(keyedDoorCost)+(keyedDoorCost==1?" KEY)":" KEYS)") : "ENTER";
    return {};
}
std::string Simulation::demolitionWarning() const {
    for(const auto &prop:arena.breakables)
        if(prop.solid()&&prop.room==room&&prop.kind==BreakableKind::PowderBarrel&&prop.fuse>=0&&
           distance(player.position,mul(add(prop.bounds.min,prop.bounds.max),.5f))<=3.8f)
            return "LIT POWDER / KEEP CLEAR";
    return {};
}
std::string Simulation::demolitionHint() const {
    if(const auto warning=demolitionWarning();!warning.empty())return warning;
    for (const auto &prop : arena.breakables) {
        if (!prop.solid() || prop.room != room || prop.kind == BreakableKind::CacheSide || prop.kind == BreakableKind::Dung) continue;
        if (distance(player.position,mul(add(prop.bounds.min,prop.bounds.max),.5f)) > 3.8f) continue;
        if (prop.kind == BreakableKind::CacheGate)
            return prop.health == 2 ? "SUPPLY CACHE / TWO DYNAMITE BLASTS" : "CRACKED CACHE SEAL / ONE MORE BLAST";
        if (prop.kind == BreakableKind::PowderBarrel)
            return prop.fuse >= 0 ? "LIT POWDER / KEEP CLEAR" : "POWDER BARREL / GUNFIRE IGNITES IT";
        if (prop.kind == BreakableKind::OreSeam) return "MARKED SEAM / DYNAMITE REVEALS SUPPLIES";
        return "CRACKED ROCK / DYNAMITE OPENS COVER";
    }
    return {};
}
} // namespace dw
