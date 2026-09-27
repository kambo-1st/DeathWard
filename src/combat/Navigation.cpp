#include "combat/Simulation.hpp"

namespace dw {
std::vector<Vector3> Arena::path(Vector3 from, Vector3 target, float radius) const {
    target.y = from.y;
    target.x = std::clamp(target.x, -14.3f, 14.3f);
    target.z = std::clamp(target.z, -14.3f, 14.3f);
    const float margin = radius + 0.08f;
    auto valid = [&](Vector3 p) {
        return std::abs(p.x) <= 14.3f && std::abs(p.z) <= 14.3f && !blocked(p, radius);
    };
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
}
void Simulation::requestMove(Vector3 target) {
    target.y = player.position.y;
    cancelMove();
    if (room == 2 && !rescued && distance(target, arena.miners) < 2.4f) {
        target = arena.miners;
        interactOnArrival_ = true;
    } else if (room == 3 && !altarDestroyed && distance(target, arena.altar) < 2.4f) {
        target = arena.altar;
        interactOnArrival_ = true;
    } else if (roomClear && distance(target, arena.exit) < 2.4f) {
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
    if (room == 2 && !rescued && distance(player.position, arena.miners) < 2.6f)
        return "FREE MINERS";
    if (room == 3 && !altarDestroyed && distance(player.position, arena.altar) < 2.6f)
        return "BREAK ALTAR";
    if (roomClear && distance(player.position, arena.exit) < 2.8f)
        return room == FinalRoom ? "RETURN HOME" : "DESCEND";
    return {};
}
} // namespace dw
