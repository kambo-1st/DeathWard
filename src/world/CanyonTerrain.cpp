#include "world/CanyonTerrain.hpp"
#include "world/Dungeon.hpp"
#include <memory>

namespace dw {
namespace {
float smooth(float lo, float hi, float value) {
    const float t = std::clamp((value - lo) / (hi - lo), 0.f, 1.f);
    return t * t * (3 - 2 * t);
}
Vector3 cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
float lineDistance(Vector3 p, Vector3 a, Vector3 b) {
    p.y = a.y = b.y = 0;
    const auto v = sub(b, a);
    return distance(p, add(a, mul(v, std::clamp(dot(sub(p, a), v) / std::max(.001f, dot(v, v)), 0.f, 1.f))));
}
struct Basin {
    Vector3 center;
    float rx, rz, phase;
};
struct Outcrop {
    Vector3 center;
    float rx, rz, height, angle, phase;
};
struct TrailSegment {
    Vector3 a, b;
    float radius;
};
} // namespace

Vector3 CanyonTerrain::vertex(int ix, int iz) const {
    return {x + float(ix) * step, heights[size_t(iz * width + ix)], z + float(iz) * step};
}
float CanyonTerrain::height(float px, float pz) const {
    const float gx = (px - x) / step, gz = (pz - z) / step;
    const int ix = int(std::floor(gx)), iz = int(std::floor(gz));
    if (ix < 0 || iz < 0 || ix >= width - 1 || iz >= depth - 1)
        return 20;
    const float u = gx - ix, v = gz - iz;
    const float a = heights[size_t(iz * width + ix)], b = heights[size_t(iz * width + ix + 1)],
                c = heights[size_t((iz + 1) * width + ix)], d = heights[size_t((iz + 1) * width + ix + 1)];
    return u >= v ? a + u * (b - a) + v * (d - b) : a + v * (c - a) + u * (d - c);
}
bool CanyonTerrain::blocked(Vector3 p, float radius) const {
    if (height(p.x, p.z) > WalkableHeight || waterBlocked(p))
        return true;
    for (int n = 0; n < 8; ++n) {
        const float angle = float(n) * Pi / 4;
        const Vector3 edge{p.x + radius * std::cos(angle), p.y, p.z + radius * std::sin(angle)};
        if (height(edge.x, edge.z) > WalkableHeight || waterBlocked(edge))
            return true;
    }
    return false;
}
SegmentHit CanyonTerrain::trace(Vector3 from, Vector3 to, float radius) const {
    const auto direction = sub(to, from);
    const auto volume =
        segmentBox(from, to, {{x, -10000, z}, {x + (width - 1) * step, 10000, z + (depth - 1) * step}});
    if (!volume.hit)
        return {};
    const float begin = std::min(1.f, volume.t + .000001f);
    const auto start = add(from, mul(direction, begin));
    int ix = std::clamp(int(std::floor((start.x - x) / step)), 0, width - 2);
    int iz = std::clamp(int(std::floor((start.z - z) / step)), 0, depth - 2);
    if (height(start.x, start.z) > start.y - radius) {
        const Vector3 normal =
            unit(cross(sub(vertex(ix, iz + 1), vertex(ix, iz)), sub(vertex(ix + 1, iz), vertex(ix, iz))));
        return {true, volume.t, normal};
    }
    const int sx = direction.x >= 0 ? 1 : -1, sz = direction.z >= 0 ? 1 : -1;
    const float infinity = std::numeric_limits<float>::infinity();
    float tx =
        std::abs(direction.x) < .000001f ? infinity : (x + (ix + (sx > 0)) * step - from.x) / direction.x;
    float tz =
        std::abs(direction.z) < .000001f ? infinity : (z + (iz + (sz > 0)) * step - from.z) / direction.z;
    const float dx = std::abs(direction.x) < .000001f ? infinity : step / std::abs(direction.x);
    const float dz = std::abs(direction.z) < .000001f ? infinity : step / std::abs(direction.z);
    float entered = volume.t;
    for (int cells = 0; cells < width + depth + 4; ++cells) {
        const float leave = std::min({tx, tz, 1.f});
        SegmentHit best;
        auto triangle = [&](Vector3 a, Vector3 b, Vector3 c) {
            const auto normal = unit(cross(sub(b, a), sub(c, a)));
            const float denominator = dot(normal, direction);
            if (denominator >= -.000001f)
                return;
            const float t = (radius - dot(normal, sub(from, a))) / denominator;
            if (t < entered - .00001f || t > leave + .00001f || t < 0 || t > best.t)
                return;
            const auto p = sub(add(from, mul(direction, t)), mul(normal, radius));
            const auto edge = [&](Vector3 v, Vector3 w) { return dot(cross(sub(w, v), sub(p, v)), normal); };
            const float margin = radius * step * 2 + .0001f;
            if (edge(a, b) >= -margin && edge(b, c) >= -margin && edge(c, a) >= -margin)
                best = {true, t, normal};
        };
        const auto a = vertex(ix, iz), b = vertex(ix + 1, iz), c = vertex(ix, iz + 1),
                   d = vertex(ix + 1, iz + 1);
        triangle(a, d, b);
        triangle(a, c, d);
        if (best.hit)
            return best;
        if (leave >= 1)
            break;
        entered = leave;
        const bool nextX = tx <= tz, nextZ = tz <= tx;
        if (nextX) {
            ix += sx;
            tx += dx;
        }
        if (nextZ) {
            iz += sz;
            tz += dz;
        }
        if (ix < 0 || iz < 0 || ix >= width - 1 || iz >= depth - 1)
            break;
    }
    return {};
}

void buildCanyon(Arena &arena, bool river) {
    auto field = std::make_shared<CanyonTerrain>();
    Random rng(arena.visualSeed ^ 0x43414e594f4e5632ULL);
    std::vector<Basin> basins;
    std::vector<Outcrop> rocks;
    std::vector<TrailSegment> trails;
    for (auto &room : arena.rooms) {
        const auto size = sub(room.bounds.max, room.bounds.min);
        basins.push_back({room.center, size.x * .43f, size.z * .43f, rng.real(0, 2 * Pi)});
        room.obstacles.clear();
    }
    for (auto &passage : arena.passages) {
        const auto direction = unit(sub(passage.to, passage.from));
        const Vector3 side{-direction.z, 0, direction.x};
        const float span = distance(passage.from, passage.to);
        const float bend = rng.real(-1, 1) * std::min(7.f, span * .22f);
        std::vector<Vector3> points;
        for (int n = 0; n <= 16; ++n) {
            const float t = float(n) / 16;
            const float envelope = std::pow(std::sin(Pi * t), 2);
            points.push_back(add(add(passage.from, mul(direction, span * t)), mul(side, bend * envelope)));
            if (n)
                trails.push_back({points[size_t(n - 1)], points[size_t(n)], 4.f});
        }
        field->trails.push_back(points);
        for (int end = 0; end < 2; ++end) {
            const auto &room = arena.rooms[size_t(passage.rooms[size_t(end)])];
            trails.push_back({room.center, end ? passage.to : passage.from, 4.f});
        }
        // Culling uses the full bent route, while gates keep their exact neck width.
        for (auto p : points) {
            passage.floor.min.x = std::min(passage.floor.min.x, p.x - 4);
            passage.floor.min.z = std::min(passage.floor.min.z, p.z - 4);
            passage.floor.max.x = std::max(passage.floor.max.x, p.x + 4);
            passage.floor.max.z = std::max(passage.floor.max.z, p.z + 4);
        }
    }
    // Reserve generous paths to every objective, arrival and door before adding outcrops.
    std::vector<TrailSegment> reserved = trails;
    for (auto &path : reserved)
        path.radius = 1.5f;
    for (const auto &room : arena.rooms) {
        reserved.push_back({room.center, room.objective, 2.0f});
        reserved.push_back({room.center, room.entry, 2.0f});
        reserved.push_back({room.center, room.exit, 2.0f});
        trails.push_back({room.center, room.objective, 3.2f});
        trails.push_back({room.center, room.entry, 3.2f});
        trails.push_back({room.center, room.exit, 3.2f});
    }
    auto distanceToFloor = [&](Vector3 p) {
        float d = 10000;
        for (const auto &b : basins) {
            const float u = (p.x - b.center.x) / b.rx, v = (p.z - b.center.z) / b.rz;
            const float angle = std::atan2(v, u);
            const float rim =
                1 + .085f * std::sin(3 * angle + b.phase) + .055f * std::sin(5 * angle - b.phase);
            d = std::min(d, (std::sqrt(u * u + v * v) - rim) * std::min(b.rx, b.rz));
        }
        for (const auto &t : trails)
            d = std::min(d, lineDistance(p, t.a, t.b) - t.radius);
        return d;
    };
    for (auto &room : arena.rooms) {
        const int desired = 3 + int(rng.bounded(3));
        for (int attempt = 0; attempt < 180 && int(room.obstacles.size()) < desired; ++attempt) {
            Outcrop r{{rng.real(room.bounds.min.x + 4, room.bounds.max.x - 4), 0,
                       rng.real(room.bounds.min.z + 4, room.bounds.max.z - 4)},
                      rng.real(1.5f, 3.5f),
                      rng.real(1.4f, 2.8f),
                      rng.real(1.5f, 3.3f),
                      rng.real(0, 2 * Pi),
                      rng.real(0, 2 * Pi)};
            const float radius = std::max(r.rx, r.rz);
            if (distanceToFloor(r.center) > -radius - 2)
                continue;
            bool safe = distance(r.center, Vector3{room.center.x, 0, room.center.z}) > radius + 3;
            for (const auto &t : reserved)
                if (lineDistance(r.center, t.a, t.b) < radius + t.radius)
                    safe = false;
            for (const auto &other : rocks)
                if (distance(r.center, other.center) < radius + std::max(other.rx, other.rz) + 3)
                    safe = false;
            if (!safe)
                continue;
            rocks.push_back(r);
            room.obstacles.push_back({{r.center.x - radius, 0, r.center.z - radius},
                                      {r.center.x + radius, r.height, r.center.z + radius}});
        }
    }
    field->x = std::floor((arena.bounds.min.x - 40) / field->step) * field->step;
    field->z = std::floor((arena.bounds.min.z - 40) / field->step) * field->step;
    field->width = int(std::ceil((arena.bounds.max.x + 40 - field->x) / field->step)) + 1;
    field->depth = int(std::ceil((arena.bounds.max.z + 40 - field->z) / field->step)) + 1;
    // Keep the original cap RNG grid unchanged when extending the river backdrop.
    CanyonTerrain mesa;
    mesa.x = field->x;
    mesa.z = field->z;
    mesa.step = field->step * 3;
    mesa.width = (field->width + 2) / 3 + 1;
    mesa.depth = (field->depth + 2) / 3 + 1;
    if (river)
        planCanyonRiver(arena, *field);
    if (field->riverKind == CanyonRiverKind::Boundary) {
        // A low far bank reveals much more of the landscape than a tall cliff.
        // Extend that backdrop so the terrain mesh edge stays beyond the camera.
        const int extra = int(std::ceil(80.f / field->step));
        if (field->riverOutward.x != 0) {
            field->width += extra;
            if (field->riverOutward.x < 0)
                field->x -= extra * field->step;
        } else {
            field->depth += extra;
            if (field->riverOutward.z < 0)
                field->z -= extra * field->step;
        }
    }
    if (field->riverKind == CanyonRiverKind::Interior) {
        // Keep the original cover stream intact outside the river region.
        auto touchesRiver = [&](Vector3 p, float radius) {
            const auto sample = field->riverSample(p);
            return sample.distance < sample.width + radius + 1.5f;
        };
        std::erase_if(rocks, [&](const auto &r) { return touchesRiver(r.center, std::max(r.rx, r.rz)); });
        for (auto &room : arena.rooms)
            std::erase_if(room.obstacles, [&](Box box) {
                return touchesRiver(mul(add(box.min, box.max), .5f), (box.max.x - box.min.x) * .5f);
            });
    }
    field->heights.resize(size_t(field->width * field->depth));
    // Broad, planar cap facets subdivide exactly onto the collision lattice.
    // A separate stream keeps this surface detail independent of trails/cover.
    Random capRng(arena.visualSeed ^ 0x4d45534143415053ULL);
    for (int z = 0; z < mesa.depth; ++z)
        for (int x = 0; x < mesa.width; ++x) {
            const float px = mesa.x + x * mesa.step, pz = mesa.z + z * mesa.step;
            mesa.heights.push_back(7.6f + 1.7f * std::sin(px * .047f + pz * .039f) +
                                   .8f * std::sin(pz * .11f) + capRng.real(-.65f, .65f));
        }
    std::vector<float> dryHeights(field->riverKind == CanyonRiverKind::Interior ? field->heights.size() : 0);
    for (int z = 0; z < field->depth; ++z)
        for (int x = 0; x < field->width; ++x) {
            Vector3 p{field->x + x * field->step, 0, field->z + z * field->step};
            const float d = distanceToFloor(p);
            const float crag =
                .65f * std::sin(p.x * .63f + p.z * .41f) + .4f * std::sin(p.z * .87f - p.x * .33f);
            const float plateau = mesa.height(p.x, p.z);
            // A short, irregular shoulder produces tall angular faces, rather
            // than a broad ramp. The foot still starts outside the reserved floor.
            float height = plateau * smooth(.35f, 2.8f + crag, d);
            if (field->riverKind == CanyonRiverKind::Boundary) {
                const auto water = field->riverSample(p);
                const float outward = -water.side;
                if (outward >= 0) {
                    // The opposite landscape stays low all the way to the field
                    // edge. There is no remaining cliff hidden behind the river.
                    const float lowland = .85f + .3f * std::sin(p.x * .073f + p.z * .031f) +
                                          .2f * std::sin(p.z * .091f - p.x * .023f);
                    height = std::lerp(-1.65f, lowland, smooth(water.width * .4f, water.width + 5, outward));
                } else {
                    const Vector3 tangent{-field->riverOutward.z, 0, field->riverOutward.x};
                    float opening = 0;
                    for (int index : field->riverRooms) {
                        const auto &room = arena.rooms[size_t(index)];
                        const auto size = sub(room.bounds.max, room.bounds.min);
                        const auto local = sub(p, room.center);
                        const float span = std::abs(dot(size, tangent));
                        const float reach = std::abs(dot(size, field->riverOutward));
                        const float across =
                            1 - smooth(span * .20f, span * .43f, std::abs(dot(local, tangent)));
                        opening = std::max(opening, across * smooth(reach * .14f, reach * .32f,
                                                                  dot(local, field->riverOutward)));
                    }
                    // Cliff headlands between openings protect passage seals;
                    // only the exposed room front becomes a level, reachable bank.
                    height *= 1 - opening;
                    const float channel = 1 - smooth(water.width * .45f, water.width + 1.2f, -outward);
                    height = std::lerp(height, -1.65f, channel);
                }
            }
            for (const auto &r : rocks) {
                const auto local = rotateY(sub(p, r.center), r.angle);
                const float u = local.x / r.rx, v = local.z / r.rz;
                const float q =
                    std::sqrt(u * u + v * v) / (1 + .11f * std::sin(3 * std::atan2(v, u) + r.phase));
                if (q < 1)
                    height = std::max(height, r.height * (1 - smooth(.48f, 1.f, q)));
            }
            if (field->riverKind == CanyonRiverKind::Interior) {
                dryHeights[size_t(z * field->width + x)] = height;
                const auto water = field->riverSample(p);
                const float bank = water.distance - water.width;
                // A low, eroded shoulder softens the canyon beside the channel.
                // It remains raised wherever the original terrain was a wall.
                if (bank < 7) {
                    const float shoulder = std::max(.35f, .8f + std::max(0.f, bank) * .45f);
                    height = std::lerp(std::min(height, shoulder), height, smooth(1.5f, 7.f, bank));
                }
                if (bank < 1.15f) {
                    float crossing = 0;
                    // Fords only occupy existing floor: carving the river through
                    // a mesa must never create a route around gates or room locks.
                    if (height <= CanyonTerrain::WalkableHeight) {
                        for (const auto &route : reserved)
                            crossing = std::max(crossing, 1 - smooth(route.radius + 1.5f, route.radius + 3.5f,
                                                                     lineDistance(p, route.a, route.b)));
                    }
                    const float depth = std::lerp(1.7f, .065f, crossing);
                    const float channel = 1 - smooth(-water.width * .65f, 1.15f, bank);
                    // Eroded banks meet the riverbed continuously, including where
                    // the river disappears into the canyon beyond its end rooms.
                    height = std::lerp(height, -depth, channel);
                }
            }
            field->heights[size_t(z * field->width + x)] = height;
        }
    arena.canyon = field;
    if (field->riverKind == CanyonRiverKind::Interior)
        connectInteriorRiver(arena, dryHeights);
    arena.floorCells.clear();
    arena.floors.clear();
    arena.obstacles.clear();
    arena.boundaryWalls.clear();
    for (auto &room : arena.rooms) {
        room.floors.clear();
        room.floorArea = 0;
    }
    for (int z = int(std::floor(arena.bounds.min.z / FloorTile));
         z < int(std::ceil(arena.bounds.max.z / FloorTile)); ++z)
        for (int x = int(std::floor(arena.bounds.min.x / FloorTile));
             x < int(std::ceil(arena.bounds.max.x / FloorTile)); ++x) {
            Vector3 p{(x + .5f) * FloorTile, .85f, (z + .5f) * FloorTile};
            if (field->blocked(p, 0))
                continue;
            arena.floorCells.insert({x, z});
            Box tile{{x * FloorTile, -.4f, z * FloorTile}, {(x + 1) * FloorTile, 0, (z + 1) * FloorTile}};
            arena.floors.push_back(tile);
            for (auto &room : arena.rooms)
                if (p.x >= room.bounds.min.x && p.x <= room.bounds.max.x && p.z >= room.bounds.min.z &&
                    p.z <= room.bounds.max.z) {
                    room.floors.push_back(tile);
                    room.floorArea += FloorTile * FloorTile;
                    break;
                }
        }
    arena.rebuildWalls();
    planCanyonRoad(arena);
}
} // namespace dw
