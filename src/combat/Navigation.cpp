#include "combat/Simulation.hpp"
#include <map>
#include <queue>

namespace dw {
namespace {
Vector3 center(FloorCell c, float y) {
    return {(float(c.first) + 0.5f) * FloorTile, y, (float(c.second) + 0.5f) * FloorTile};
}
std::vector<Vector3> floorPath(const Arena &arena, Vector3 from, Vector3 target, float radius) {
    const bool targetWasBlocked = arena.blocked(target, radius);
    auto nearest = [&](Vector3 p, bool requireSight) -> std::optional<FloorCell> {
        std::optional<FloorCell> result;
        float best = std::numeric_limits<float>::infinity();
        for (const auto &cell : arena.floorCells) {
            Vector3 at = center(cell, from.y);
            float d = distance(at, p);
            if (d >= best || (requireSight && d > 6))
                continue;
            if (!arena.blocked(at, radius) && (!requireSight || arena.clear(p, at, radius))) {
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
        target = center(*goal, from.y);
    if (arena.clear(from, target, radius))
        return {target};
    struct Node {
        float cost = std::numeric_limits<float>::infinity();
        FloorCell previous{};
    };
    using Entry = std::pair<float, FloorCell>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> frontier;
    std::map<FloorCell, Node> nodes;
    auto heuristic = [&](FloorCell c) {
        return float(std::abs(c.first - goal->first) + std::abs(c.second - goal->second)) * FloorTile;
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
            if (!arena.floorCells.contains(next))
                continue;
            float cost = nodes[current].cost + FloorTile;
            if (nodes.contains(next) && cost >= nodes[next].cost)
                continue;
            Vector3 p = center(next, from.y);
            if (arena.blocked(p, radius) || !arena.clear(center(current, from.y), p, radius))
                continue;
            nodes[next] = {cost, current};
            frontier.push({cost + heuristic(next), next});
        }
    }
    if (!nodes.contains(*goal))
        return {};
    std::vector<Vector3> reverse{target};
    for (auto at = *goal;; at = nodes[at].previous) {
        reverse.push_back(center(at, from.y));
        if (at == *start)
            break;
    }
    std::reverse(reverse.begin(), reverse.end());
    std::vector<Vector3> path;
    // Smooth the tile route into long segments while retaining real 3D clearance.
    Vector3 anchor = from;
    for (size_t i = 0; i < reverse.size();) {
        size_t end = i;
        while (end + 1 < reverse.size() && arena.clear(anchor, reverse[end + 1], radius))
            ++end;
        path.push_back(reverse[end]);
        anchor = reverse[end];
        i = end + 1;
    }
    return path;
}
} // namespace
std::vector<Vector3> Arena::path(Vector3 from, Vector3 target, float radius) const {
    target.y = from.y;
    if (!floorCells.empty())
        return floorPath(*this, from, target, radius);
    target.x = std::clamp(target.x, bounds.min.x + 0.7f, bounds.max.x - 0.7f);
    target.z = std::clamp(target.z, bounds.min.z + 0.7f, bounds.max.z - 0.7f);
    const float margin = radius + 0.08f;
    auto valid = [&](Vector3 p) { return contains(p) && !blocked(p, radius); };
    // A click on solid cover lands at its nearest walkable edge.
    if (blocked(target, radius)) {
        std::optional<Vector3> nearest;
        float best = std::numeric_limits<float>::infinity();
        for (const auto &wall : walls) {
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
        for (const auto &wall : walls)
            if (segmentBox(a, b, wall, radius).hit)
                return false;
        return true;
    };
    if (clear(from, target))
        return {target};

    // The arena has a handful of rectangular obstacles. A small visibility graph
    // around their expanded corners provides exact routes without a terrain grid.
    std::vector<Vector3> nodes{from, target};
    for (const auto &wall : walls) {
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
void Simulation::requestMove(Vector3 target) {
    target.y = player.position.y;
    cancelMove();
    const auto &site=arena.rooms[size_t(room)];
    if(site.story!=StoryRoom::None&&roomClear&&distance(target,site.objective)<2.4f) {
        target=site.objective;interactOnArrival_=true;
    } else if(surveyTutorial && room==finalRoom() && roomClear && distance(target,surveyPosition())<2.4f) {
        target=surveyPosition();interactOnArrival_=true;
    } else if (room == arena.shopRoom && distance(target, arena.rooms[size_t(room)].objective) < 2.4f) {
        target = arena.rooms[size_t(room)].objective;
        interactOnArrival_ = true;
    } else if (legacyObjectives() && !rescued && distance(target, arena.miners) < 2.4f) {
        target = arena.miners;
        interactOnArrival_ = true;
    } else if (legacyObjectives() && !altarDestroyed && distance(target, arena.altar) < 2.4f) {
        target = arena.altar;
        interactOnArrival_ = true;
    } else if (canUseFloorExit() && distance(target, arena.exit) < 2.4f) {
        target = arena.exit;
        interactOnArrival_ = true;
    } else if (arena.rooms[size_t(room)].kind == RoomKind::Power && !rooms[size_t(room)].rewardTaken &&
               distance(target, arena.rooms[size_t(room)].objective) < 2.4f) {
        target = arena.rooms[size_t(room)].objective;
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
    if(site.story!=StoryRoom::None&&roomClear&&distance(player.position,site.objective)<2.6f&&arena.sight(player.position,site.objective))
        return "EXAMINE SITE";
    if(surveyTutorial && room==finalRoom() && roomClear && distance(player.position,surveyPosition())<2.6f &&
       arena.sight(player.position,surveyPosition()))return surveyRecovered?"READ LETTER":"RECOVER RECORDS";
    if (room == arena.shopRoom && distance(player.position, arena.rooms[size_t(room)].objective) <= 2.6f &&
        arena.sight(player.position, arena.rooms[size_t(room)].objective))
        return "TRADE";
    if (arena.rooms[size_t(room)].kind == RoomKind::Power && !rooms[size_t(room)].rewardTaken &&
        distance(player.position, arena.rooms[size_t(room)].objective) < 2.6f)
        return "CLAIM POWER";
    if (legacyObjectives() && !rescued && distance(player.position, arena.miners) < 2.6f)
        return "FREE MINERS";
    if (legacyObjectives() && !altarDestroyed && distance(player.position, arena.altar) < 2.6f)
        return "BREAK ALTAR";
    if (canUseFloorExit() && distance(player.position, arena.exit) < 2.8f)
        return !lastFloor()?"NEXT FLOOR":surveyTutorial||testimony()?"RETURN TO FORT":"RETURN HOME";
    if (roomClear)
        for (size_t i = 0; i < arena.passages.size(); ++i)
            for (int side = 0; side < 2; ++side)
                if (distance(player.position, arena.doorApproach(int(i), side)) < 2.8f)
                    return arena.passages[i].locked ? "UNLOCK (1 KEY)" : "ENTER";
    return {};
}
} // namespace dw
