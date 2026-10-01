#include "world/CanyonTerrain.hpp"
#include "world/Dungeon.hpp"
#include <queue>

namespace dw {
RiverSample CanyonTerrain::riverSample(Vector3 p) const {
    RiverSample result;
    p.y = 0;
    for (size_t i = 1; i < river.size(); ++i) {
        const auto &a = river[i - 1], &b = river[i];
        const auto edge = sub(b.position, a.position);
        const float t =
            std::clamp(dot(sub(p, a.position), edge) / std::max(.001f, dot(edge, edge)), 0.f, 1.f);
        const auto delta = sub(p, add(a.position, mul(edge, t)));
        const float d = length(delta);
        if (d < result.distance) {
            result.distance = d;
            result.width = std::lerp(a.width, b.width, t);
            result.along = std::lerp(a.along, b.along, t);
            result.side = (edge.x * delta.z - edge.z * delta.x < 0 ? -1.f : 1.f) * d;
        }
    }
    return result;
}
bool CanyonTerrain::waterBlocked(Vector3 p) const {
    return !river.empty() && height(p.x, p.z) < WaterLevel - WadeDepth;
}
bool CanyonTerrain::waterClear(Vector3 from, Vector3 to, float radius) const {
    if (river.empty())
        return true;
    // Height is linear inside each of the two triangles per grid cell. Checking
    // every grid/diagonal crossing is an exact segment test, even for long dodges.
    auto clear = [&](Vector3 a, Vector3 b) {
        if (waterBlocked(a) || waterBlocked(b))
            return false;
        const auto delta = sub(b, a);
        auto family = [&](float first, float last, float origin) {
            const float span = last - first;
            if (std::abs(span) < .00001f)
                return true;
            const int begin = int(std::ceil((std::min(first, last) - origin) / step));
            const int end = int(std::floor((std::max(first, last) - origin) / step));
            for (int i = begin; i <= end; ++i) {
                const float t = (origin + i * step - first) / span;
                const auto p = add(a, mul(delta, t));
                if (waterBlocked(p))
                    return false;
            }
            return true;
        };
        return family(a.x, b.x, x) && family(a.z, b.z, z) && family(a.x - a.z, b.x - b.z, x - z);
    };
    if (!clear(from, to))
        return false;
    for (int n = 0; n < 8 && radius > 0; ++n) {
        const float angle = float(n) * Pi / 4;
        const Vector3 offset{radius * std::cos(angle), 0, radius * std::sin(angle)};
        if (!clear(add(from, offset), add(to, offset)))
            return false;
    }
    return true;
}

namespace {
void planBoundaryRiver(const Arena &arena, CanyonTerrain &field) {
    Random rng(arena.visualSeed ^ 0x7269766572626564ULL);
    auto smooth = [](float lo, float hi, float v) {
        const float t = std::clamp((v - lo) / (hi - lo), 0.f, 1.f);
        return t * t * (3 - 2 * t);
    };
    // Open an exterior side, never a wall separating two rooms. Prefer an early
    // reachable perimeter room; the seed resolves equally suitable directions.
    float best = 10000;
    for (Vector3 outward : {Vector3{1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}}) {
        float outer = -10000;
        for (const auto &room : arena.rooms)
            outer = std::max(outer, dot(room.center, outward));
        std::vector<int> rooms;
        for (int i = 0; i < int(arena.rooms.size()); ++i)
            if (dot(arena.rooms[size_t(i)].center, outward) >= outer - .1f)
                rooms.push_back(i);
        std::stable_sort(rooms.begin(), rooms.end(), [&](int a, int b) {
            return arena.rooms[size_t(a)].depth < arena.rooms[size_t(b)].depth;
        });
        const float score = float(arena.rooms[size_t(rooms.front())].depth) + rng.real(0, .9f);
        if (score < best) {
            best = score;
            field.riverOutward = outward;
            rooms.resize(std::min(size_t(3), rooms.size()));
            field.riverRooms = rooms;
        }
    }
    const auto outward = field.riverOutward;
    const Vector3 tangent{-outward.z, 0, outward.x};
    const Vector3 minimum{field.x, 0, field.z},
        maximum{field.x + (field.width - 1) * field.step, 0, field.z + (field.depth - 1) * field.step};
    const float start = std::min(dot(minimum, tangent), dot(maximum, tangent));
    const float end = std::max(dot(minimum, tangent), dot(maximum, tangent));
    const float outer = std::max(dot(arena.bounds.min, outward), dot(arena.bounds.max, outward));
    const float phase = rng.real(0, 2 * Pi);
    float along = 0;
    const int count = int(std::ceil((end - start) / field.step));
    for (int n = 0; n <= count; ++n) {
        const float s = std::lerp(start, end, float(n) / count);
        float bank = outer + 2 + .65f * std::sin(s * .045f + phase);
        for (int index : field.riverRooms) {
            const auto &room = arena.rooms[size_t(index)];
            const auto size = sub(room.bounds.max, room.bounds.min);
            const float span = std::abs(dot(size, tangent));
            const float offset = std::abs(s - dot(room.center, tangent));
            const float weight = 1 - smooth(span * .25f, span * .5f + 10, offset);
            const float edge = std::max(dot(room.bounds.min, outward), dot(room.bounds.max, outward));
            bank = std::lerp(bank, edge + .4f + .25f * std::sin(s * .11f + phase), weight);
        }
        const float width = 6.2f + .65f * std::sin(s * .035f - phase);
        const auto p = add(mul(tangent, s), mul(outward, bank + width));
        if (!field.river.empty())
            along += distance(field.river.back().position, p);
        field.river.push_back({p, width, along});
    }
}
void planInteriorRiver(const Arena &arena, CanyonTerrain &field) {
    Random rng(arena.visualSeed ^ 0x7269766572626564ULL);
    // The entrance has at least two ordinary exits. Following two existing links
    // gives the trial a continuous three-basin region, visible on arrival.
    auto links = arena.rooms[0].passages;
    if (links.size() < 2)
        return;
    for (size_t i = links.size(); i > 1; --i)
        std::swap(links[i - 1], links[rng.bounded(uint32_t(i))]);
    auto neighbor = [&](int index) {
        const auto &p = arena.passages[size_t(index)];
        return p.rooms[0] == 0 ? p.rooms[1] : p.rooms[0];
    };
    field.riverRooms = {neighbor(links[0]), 0, neighbor(links[1])};
    struct Knot {
        Vector3 p;
        float width;
    };
    std::vector<Knot> knots;
    auto knot = [&](Vector3 p, float width) {
        p.y = 0;
        if (knots.empty() || distance(knots.back().p, p) > .01f)
            knots.push_back({p, width});
    };
    auto gate = [&](int link, int room) {
        const auto &p = arena.passages[size_t(link)];
        return p.rooms[0] == room ? p.from : p.to;
    };
    for (int i = 0; i < 3; ++i) {
        const int index = field.riverRooms[size_t(i)];
        const auto &room = arena.rooms[size_t(index)];
        const float reach =
            std::min(room.bounds.max.x - room.bounds.min.x, room.bounds.max.z - room.bounds.min.z);
        Vector3 enter{}, leave{};
        if (i > 0)
            enter = gate(links[size_t(i - 1)], index);
        if (i < 2)
            leave = gate(links[size_t(i)], index);
        if (i == 0)
            enter = add(room.center, mul(unit(sub(room.center, leave)), reach * .9f));
        if (i == 2)
            leave = add(room.center, mul(unit(sub(room.center, enter)), reach * .9f));
        const auto direction = unit(sub(leave, enter));
        const Vector3 side{-direction.z, 0, direction.x};
        const float bend = reach * rng.real(.15f, .23f) * (rng.bounded(2) ? 1.f : -1.f);
        const float width = rng.real(2.5f, 3.4f);
        knot(enter, i == 0 ? width : 1.05f);
        knot(add(add(mul(enter, .4f), mul(room.center, .6f)), mul(side, bend * .7f)), width * .9f);
        knot(add(room.center, mul(side, bend)), width);
        knot(add(add(mul(leave, .4f), mul(room.center, .6f)), mul(side, bend * .5f)), width * .8f);
        knot(leave, i == 2 ? width : 1.05f);
        if (i < 2) {
            auto trail = field.trails[size_t(links[size_t(i)])];
            if (distance(trail.front(), leave) > distance(trail.back(), leave))
                std::reverse(trail.begin(), trail.end());
            for (auto p : trail)
                knot(p, 1.05f);
        }
    }
    auto catmull = [](Vector3 a, Vector3 b, Vector3 c, Vector3 d, float t) {
        return mul(add(add(mul(b, 2), mul(sub(c, a), t)),
                       add(mul(add(sub(mul(a, 2), mul(b, 5)), sub(mul(c, 4), d)), t * t),
                           mul(add(sub(mul(b, 3), a), sub(d, mul(c, 3))), t * t * t))),
                   .5f);
    };
    float along = 0;
    for (size_t i = 0; i + 1 < knots.size(); ++i) {
        const auto &a = knots[i ? i - 1 : i], &b = knots[i], &c = knots[i + 1],
                   &d = knots[std::min(i + 2, knots.size() - 1)];
        const int count = std::max(1, int(std::ceil(distance(b.p, c.p) / 1.25f)));
        for (int n = 0; n < count; ++n) {
            const float t = float(n) / count;
            const auto p = catmull(a.p, b.p, c.p, d.p, t);
            if (!field.river.empty())
                along += distance(field.river.back().position, p);
            field.river.push_back({p, std::lerp(b.width, c.width, t * t * (3 - 2 * t)), along});
        }
    }
    along += distance(field.river.back().position, knots.back().p);
    field.river.push_back({knots.back().p, knots.back().width, along});
}

} // namespace

void planCanyonRiver(const Arena &arena, CanyonTerrain &field) {
    // A separate stream chooses exactly one treatment without changing either
    // river's course RNG. Replaying a seed also replays its river type.
    Random choice(arena.visualSeed ^ 0x5249564552545950ULL);
    field.riverKind = choice.bounded(2) ? CanyonRiverKind::Boundary : CanyonRiverKind::Interior;
    if (field.riverKind == CanyonRiverKind::Interior)
        planInteriorRiver(arena, field);
    // The current graph guarantees two entrance links. Keep a safe exterior
    // fallback if a future room layout cannot accommodate an interior course.
    if (field.river.empty()) {
        field.riverKind = CanyonRiverKind::Boundary;
        planBoundaryRiver(arena, field);
    }
}

void connectInteriorRiver(Arena &arena, const std::vector<float> &dryHeights) {
    auto &field = *arena.canyon;
    // Validate before encounters are populated. A bend can isolate a small bank
    // even though every objective's reserved route remains open. Add a shallow
    // crossing to those banks, exclusively over originally accessible ground.
    Arena dry, wet;
    dry.bounds = wet.bounds = arena.bounds;
    dry.canyon = std::make_shared<CanyonTerrain>(field);
    dry.canyon->heights = dryHeights;
    dry.canyon->river.clear();
    wet.canyon = arena.canyon;
    auto point = [](FloorCell cell) {
        return Vector3{(cell.first + .5f) * FloorTile, .85f, (cell.second + .5f) * FloorTile};
    };
    for (int z = int(std::floor(arena.bounds.min.z / FloorTile));
         z < int(std::ceil(arena.bounds.max.z / FloorTile)); ++z)
        for (int x = int(std::floor(arena.bounds.min.x / FloorTile));
             x < int(std::ceil(arena.bounds.max.x / FloorTile)); ++x) {
            const FloorCell cell{x, z};
            if (!dry.canyon->blocked(point(cell), 0))
                dry.floorCells.insert(cell);
            if (!wet.canyon->blocked(point(cell), 0))
                wet.floorCells.insert(cell);
        }
    // Include cells that become shallow during repair, but keep terrain as the
    // authority for whether a candidate node is actually available.
    wet.floorCells.insert(dry.floorCells.begin(), dry.floorCells.end());
    const auto origin = *std::min_element(dry.floorCells.begin(), dry.floorCells.end(), [&](auto a, auto b) {
        const float da = dry.blocked(point(a), .6f) ? 1e9f : distance(point(a), arena.entrance);
        const float db = dry.blocked(point(b), .6f) ? 1e9f : distance(point(b), arena.entrance);
        return da < db;
    });
    auto flood = [&](const Arena &nav) {
        std::set<FloorCell> seen{origin};
        std::queue<FloorCell> pending;
        pending.push(origin);
        while (!pending.empty()) {
            const auto at = pending.front();
            pending.pop();
            for (auto [dx, dz] : {FloorCell{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
                const FloorCell next{at.first + dx, at.second + dz};
                if (!nav.floorCells.contains(next) || seen.contains(next) || nav.blocked(point(next), .6f) ||
                    !nav.clear(point(at), point(next), .6f))
                    continue;
                seen.insert(next);
                pending.push(next);
            }
        }
        return seen;
    };
    const auto originallyConnected = flood(dry);
    for (int attempt = 0; attempt < 24; ++attempt) {
        const auto reached = flood(wet);
        std::optional<FloorCell> stranded;
        for (auto cell : originallyConnected)
            if (!wet.blocked(point(cell), .6f) && !reached.contains(cell)) {
                stranded = cell;
                break;
            }
        if (!stranded)
            return;
        auto from = point(*stranded);
        std::vector<FloorCell> targets(reached.begin(), reached.end());
        std::sort(targets.begin(), targets.end(),
                  [&](auto a, auto b) { return distance(from, point(a)) < distance(from, point(b)); });
        std::vector<Vector3> route;
        for (auto to : targets) {
            if (!originallyConnected.contains(to))
                continue;
            route = dry.path(from, point(to), .6f);
            if (!route.empty())
                break;
        }
        if (route.empty())
            break;
        for (auto to : route) {
            const auto delta = sub(to, from);
            const int left =
                std::max(0, int(std::floor((std::min(from.x, to.x) - 4 - field.x) / field.step)));
            const int right = std::min(field.width - 1,
                                       int(std::ceil((std::max(from.x, to.x) + 4 - field.x) / field.step)));
            const int top = std::max(0, int(std::floor((std::min(from.z, to.z) - 4 - field.z) / field.step)));
            const int bottom = std::min(field.depth - 1,
                                        int(std::ceil((std::max(from.z, to.z) + 4 - field.z) / field.step)));
            for (int z = top; z <= bottom; ++z)
                for (int x = left; x <= right; ++x) {
                    const auto index = size_t(z * field.width + x);
                    if (dryHeights[index] > CanyonTerrain::WalkableHeight || field.heights[index] >= -.065f)
                        continue;
                    auto p = field.vertex(x, z);
                    p.y = from.y;
                    const float t =
                        std::clamp(dot(sub(p, from), delta) / std::max(.001f, dot(delta, delta)), 0.f, 1.f);
                    const float d = distance(p, add(from, mul(delta, t)));
                    float weight = std::clamp((4 - d) / 1.2f, 0.f, 1.f);
                    weight = weight * weight * (3 - 2 * weight);
                    field.heights[index] = std::lerp(field.heights[index], -.065f, weight);
                }
            from = to;
        }
    }
    // Bound generation time on unusual layouts. If local repairs cannot finish,
    // retain the river visually but make its original-floor portions fordable.
    // Mesa cuts remain deep, so this cannot open a bypass around a sealed neck.
    for (size_t i = 0; i < field.heights.size(); ++i)
        if (dryHeights[i] <= CanyonTerrain::WalkableHeight)
            field.heights[i] = std::max(field.heights[i], -.065f);
}
} // namespace dw
