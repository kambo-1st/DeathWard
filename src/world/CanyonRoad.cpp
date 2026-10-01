#include "world/CanyonTerrain.hpp"
#include "world/Dungeon.hpp"

namespace dw {
RoadSample CanyonTerrain::roadSample(Vector3 p) const {
    RoadSample result;
    p.y = 0;
    for (size_t i = 1; i < road.size(); ++i) {
        const auto &a = road[i - 1], &b = road[i];
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
void planCanyonRoad(Arena &arena) {
    auto &field = *arena.canyon;
    field.road.clear();
    field.roadRooms.clear();
    field.roadPassages.clear();
    Random random(arena.visualSeed ^ 0x43414e594f4e5244ULL);
    // Reserve the complete surface, including soft shoulders. Never put a dirt
    // road on a ford, on a slope or over a rock; river geometry has priority.
    constexpr float clearance = 2.15f;
    auto suitable = [&](Vector3 p) {
        const auto river = field.riverSample(p);
        if (river.distance < river.width + clearance + .65f)
            return false;
        for (int n = -1; n < 8; ++n) {
            const float angle = n * Pi / 4;
            const auto q = n < 0 ? p : add(p, {clearance * std::cos(angle), 0, clearance * std::sin(angle)});
            const float h = field.height(q.x, q.z);
            if (h < -.01f || h > .08f)
                return false;
        }
        return true;
    };
    auto clear = [&](Vector3 a, Vector3 b) {
        const int steps = std::max(1, int(std::ceil(distance(a, b) / .3f)));
        for (int n = 0; n <= steps; ++n)
            if (!suitable(add(a, mul(sub(b, a), float(n) / steps))))
                return false;
        return true;
    };
    struct Candidate {
        std::array<int, 3> rooms;
        std::array<int, 2> links;
        float priority;
    };
    std::vector<Candidate> candidates;
    auto inside = [](Vector3 p, Box box) {
        return p.x >= box.min.x && p.x <= box.max.x && p.z >= box.min.z && p.z <= box.max.z;
    };
    auto eligible = [&](int room) {
        return field.riverKind != CanyonRiverKind::Interior ||
               std::find(field.riverRooms.begin(), field.riverRooms.end(), room) == field.riverRooms.end();
    };
    for (int middle = 0; middle < RoomCount; ++middle) {
        const auto &room = arena.rooms[size_t(middle)];
        if (!eligible(middle))
            continue;
        for (size_t i = 0; i < room.passages.size(); ++i)
            for (size_t j = i + 1; j < room.passages.size(); ++j) {
                const int left = room.passages[i], right = room.passages[j];
                auto neighbor = [&](int link) {
                    const auto &p = arena.passages[size_t(link)];
                    return p.rooms[0] == middle ? p.rooms[1] : p.rooms[0];
                };
                const int a = neighbor(left), b = neighbor(right);
                if (!eligible(a) || !eligible(b))
                    continue;
                const float priority =
                    float(room.depth + arena.rooms[size_t(a)].depth + arena.rooms[size_t(b)].depth);
                candidates.push_back({{a, middle, b}, {left, right}, priority + random.real(0, 2)});
            }
    }
    std::stable_sort(candidates.begin(), candidates.end(),
                     [](const auto &a, const auto &b) { return a.priority < b.priority; });
    Arena nav = arena;
    nav.walls.clear(); // Gates remain authoritative in the real arena, not the material planner.
    const auto originalCells = arena.floorCells;
    const float phase = random.real(0, 2 * Pi);
    for (const auto &candidate : candidates) {
        auto gate = [&](int link, int room) {
            const auto &p = arena.passages[size_t(link)];
            return p.rooms[0] == room ? p.from : p.to;
        };
        nav.floorCells.clear();
        for (auto cell : originalCells) {
            const Vector3 p{(cell.first + .5f) * FloorTile, .85f, (cell.second + .5f) * FloorTile};
            bool insideRoute = false;
            for (int index : candidate.rooms)
                insideRoute |= inside(p, arena.rooms[size_t(index)].bounds);
            for (int link : candidate.links)
                insideRoute |= inside(p, arena.passages[size_t(link)].floor);
            if (insideRoute && suitable(p))
                nav.floorCells.insert(cell);
        }
        if (nav.floorCells.empty())
            continue;
        auto endpoint = [&](int room, int link) {
            const auto &layout = arena.rooms[size_t(room)];
            const auto size = sub(layout.bounds.max, layout.bounds.min);
            const auto away = unit(sub(layout.center, gate(link, room)));
            const auto p = add(layout.center, mul(away, std::min(size.x, size.z) * .24f));
            return suitable(p) ? p : layout.center;
        };
        std::vector<Vector3> anchors{endpoint(candidate.rooms[0], candidate.links[0])};
        for (int n = 0; n < 3; ++n) {
            const int room = candidate.rooms[size_t(n)];
            anchors.push_back(arena.rooms[size_t(room)].center);
            if (n < 2) {
                anchors.push_back(gate(candidate.links[size_t(n)], room));
                anchors.push_back(gate(candidate.links[size_t(n)], candidate.rooms[size_t(n + 1)]));
            }
        }
        anchors.push_back(endpoint(candidate.rooms[2], candidate.links[1]));
        std::vector<Vector3> route{anchors.front()};
        bool valid = suitable(route.front());
        for (size_t i = 1; i < anchors.size() && valid; ++i) {
            const auto from = route.back(), to = anchors[i];
            if (distance(from, to) < .01f)
                continue;
            if (!suitable(to)) {
                valid = false;
                break;
            }
            const auto path = nav.path(from, to, clearance);
            if (path.empty() || distance(path.back(), to) > .01f) {
                valid = false;
                break;
            }
            for (auto p : path) {
                if (!clear(route.back(), p)) {
                    valid = false;
                    break;
                }
                route.push_back(p);
            }
        }
        if (!valid)
            continue;
        // Give wagon turns a generous radius, reducing it only where the
        // terrain needs a tighter bend. Validate the whole shoulder at each try.
        std::vector<Vector3> rounded{route.front()};
        for (size_t i = 1; i + 1 < route.size(); ++i) {
            const auto a = route[i - 1], b = route[i], c = route[i + 1];
            const auto incoming = unit(sub(b, a)), outgoing = unit(sub(c, b));
            float radius = std::min({5.f, distance(a, b) * .4f, distance(b, c) * .4f});
            bool curved = false;
            if (dot(incoming, outgoing) < .98f)
                for (int attempt = 0; attempt < 4 && !curved; ++attempt, radius *= .5f) {
                    const auto start = sub(b, mul(incoming, radius)), end = add(b, mul(outgoing, radius));
                    std::vector<Vector3> bend;
                    auto previous = rounded.back();
                    bool safe = true;
                    for (int n = 0; n <= 12; ++n) {
                        const float t = float(n) / 12;
                        const auto p =
                            add(add(mul(start, (1 - t) * (1 - t)), mul(b, 2 * t * (1 - t))), mul(end, t * t));
                        if (!clear(previous, p)) {
                            safe = false;
                            break;
                        }
                        bend.push_back(p);
                        previous = p;
                    }
                    if (safe && clear(previous, c)) {
                        rounded.insert(rounded.end(), bend.begin(), bend.end());
                        curved = true;
                    }
                }
            if (!curved)
                rounded.push_back(b);
        }
        rounded.push_back(route.back());
        // Subtle seeded meanders avoid ruler-straight tracks across open basins.
        // The exact passage endpoints stay fixed for seamless gate approaches.
        std::vector<Vector3> dense{rounded.front()};
        for (size_t i = 1; i < rounded.size(); ++i) {
            const auto a = rounded[i - 1], b = rounded[i];
            const auto direction = unit(sub(b, a));
            const Vector3 side{-direction.z, 0, direction.x};
            const float length = distance(a, b);
            const int count = std::max(1, int(std::ceil(length / 2)));
            float amount = std::min(.75f, length * .035f) * std::sin(phase + float(i) * 1.7f);
            bool appended = false;
            for (int attempt = 0; attempt < 4; ++attempt, amount *= .4f) {
                std::vector<Vector3> bend;
                auto previous = dense.back();
                bool safe = true;
                for (int n = 1; n <= count; ++n) {
                    const float t = float(n) / count;
                    const auto p =
                        add(add(a, mul(sub(b, a), t)),
                            mul(side, (attempt == 3 ? 0 : amount) * std::pow(std::sin(Pi * t), 2)));
                    if (!clear(previous, p)) {
                        safe = false;
                        break;
                    }
                    bend.push_back(p);
                    previous = p;
                }
                if (safe) {
                    dense.insert(dense.end(), bend.begin(), bend.end());
                    appended = true;
                    break;
                }
            }
            if (!appended) {
                valid = false;
                break;
            }
        }
        if (!valid)
            continue;
        for (int pass = 0; pass < 3; ++pass) {
            std::vector<Vector3> smoothed{dense.front()};
            for (size_t i = 1; i < dense.size(); ++i) {
                smoothed.push_back(add(mul(dense[i - 1], .75f), mul(dense[i], .25f)));
                smoothed.push_back(add(mul(dense[i - 1], .25f), mul(dense[i], .75f)));
            }
            smoothed.push_back(dense.back());
            bool safe = true;
            for (size_t i = 1; i < smoothed.size(); ++i)
                if (!clear(smoothed[i - 1], smoothed[i])) {
                    safe = false;
                    break;
                }
            if (!safe)
                break;
            dense = std::move(smoothed);
        }
        // A single track must not double back and overlap a distant stretch
        // of itself. Nearby samples on the same rounded turn are intentional.
        std::vector<float> lengths(dense.size(), 0);
        for (size_t i = 1; i < dense.size(); ++i)
            lengths[i] = lengths[i - 1] + distance(dense[i - 1], dense[i]);
        bool overlaps = false;
        for (size_t i = 0; i < dense.size() && !overlaps; ++i)
            for (size_t j = i + 1; j < dense.size(); ++j)
                if (lengths[j] - lengths[i] > 10 && distance(dense[i], dense[j]) < 4) {
                    overlaps = true;
                    break;
                }
        if (overlaps)
            continue;
        float along = 0;
        for (auto p : dense) {
            p.y = 0;
            if (!field.road.empty()) {
                const float step = distance(field.road.back().position, p);
                if (step < .15f)
                    continue;
                along += step;
            }
            field.road.push_back({p, 1.4f + .13f * std::sin(along * .08f + phase), along});
        }
        field.roadRooms.assign(candidate.rooms.begin(), candidate.rooms.end());
        field.roadPassages.assign(candidate.links.begin(), candidate.links.end());
        return;
    }
    // An unsuitable layout simply has no road; never force a painted shortcut
    // through water or a blocked neck to satisfy a decoration quota.
}
} // namespace dw
