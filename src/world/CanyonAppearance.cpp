#include "world/CanyonAppearance.hpp"
#include "world/Dungeon.hpp"
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
namespace dw {
namespace {
bool overlaps(Box a, Box b, float margin) {
    return a.min.x < b.max.x + margin && a.max.x > b.min.x - margin && a.min.z < b.max.z + margin &&
           a.max.z > b.min.z - margin;
}
Vector3 cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
float smooth(float t) {
    t = std::clamp(t, 0.f, 1.f);
    return t * t * (3 - 2 * t);
}
float hash(int x, int z, uint64_t seed) {
    uint64_t v =
        seed ^ uint64_t(int64_t(x)) * 0x9e3779b97f4a7c15ULL ^ uint64_t(int64_t(z)) * 0xbf58476d1ce4e5b9ULL;
    v = (v ^ (v >> 30)) * 0xbf58476d1ce4e5b9ULL;
    v = (v ^ (v >> 27)) * 0x94d049bb133111ebULL;
    return float((v ^ (v >> 31)) >> 40) / 16777215.f;
}
float noise(float x, float z, uint64_t seed) {
    int ix = int(std::floor(x)), iz = int(std::floor(z));
    float u = smooth(x - ix), v = smooth(z - iz);
    return std::lerp(std::lerp(hash(ix, iz, seed), hash(ix + 1, iz, seed), u),
                     std::lerp(hash(ix, iz + 1, seed), hash(ix + 1, iz + 1, seed), u), v);
}
std::vector<float> distances(const CanyonTerrain &f, bool rock) {
    std::vector<float> d(f.heights.size(), 100000);
    for (size_t i = 0; i < d.size(); ++i)
        if ((f.heights[i] > CanyonTerrain::WalkableHeight) == rock)
            d[i] = 0;
    auto relax = [&](int x, int z, int dx, int dz, float cost) {
        int nx = x + dx, nz = z + dz;
        if (nx >= 0 && nz >= 0 && nx < f.width && nz < f.depth) {
            auto &v = d[size_t(z * f.width + x)];
            v = std::min(v, d[size_t(nz * f.width + nx)] + cost * f.step);
        }
    };
    for (int z = 0; z < f.depth; ++z)
        for (int x = 0; x < f.width; ++x) {
            relax(x, z, -1, 0, 1);
            relax(x, z, 0, -1, 1);
            relax(x, z, -1, -1, 1.414214f);
            relax(x, z, 1, -1, 1.414214f);
        }
    for (int z = f.depth - 1; z >= 0; --z)
        for (int x = f.width - 1; x >= 0; --x) {
            relax(x, z, 1, 0, 1);
            relax(x, z, 0, 1, 1);
            relax(x, z, 1, 1, 1.414214f);
            relax(x, z, -1, 1, 1.414214f);
        }
    return d;
}
float routeDistance(Vector3 p, Vector3 a, Vector3 b) {
    p.y = a.y = b.y = 0;
    auto v = sub(b, a);
    return distance(p, add(a, mul(v, std::clamp(dot(sub(p, a), v) / std::max(.001f, dot(v, v)), 0.f, 1.f))));
}
} // namespace
void CanyonVisualParameters::validate() const {
    auto range = [](float v, float a, float b) { return std::isfinite(v) && v >= a && v <= b; };
    if (!range(minHeight, .8f, 10) || !range(maxHeight, minHeight, 16) || !range(heightVariation, 0, 1) ||
        terraces < 1 || terraces > 6 || !range(terraceWidth, 1, 8) || !range(silhouette, 0, 1) ||
        !range(facets, 0, 1) || !range(extent, 0, 35) || !range(debris, 0, 3) ||
        !range(floorVegetation, 0, 3) || !range(baseVegetation, 0, 3) || !range(terraceVegetation, 0, 3) ||
        !range(plateauVegetation, 0, 3) || candidatesPerRoom < 0 || candidatesPerRoom > 1000 ||
        maxDecorations < 0 || maxDecorations > 6000)
        throw std::runtime_error("Invalid canyon visual parameters");
}
CanyonVisualParameters CanyonVisualParameters::load(const std::filesystem::path &path) {
    CanyonVisualParameters p;
    std::ifstream file(path);
    if (!file)
        return p;
    std::map<std::string, float *> fields{{"minimum_height", &p.minHeight},
                                          {"maximum_height", &p.maxHeight},
                                          {"height_variation", &p.heightVariation},
                                          {"terrace_width", &p.terraceWidth},
                                          {"silhouette_irregularity", &p.silhouette},
                                          {"facet_variation", &p.facets},
                                          {"rock_debris_density", &p.debris},
                                          {"floor_vegetation", &p.floorVegetation},
                                          {"base_vegetation", &p.baseVegetation},
                                          {"terrace_vegetation", &p.terraceVegetation},
                                          {"plateau_vegetation", &p.plateauVegetation},
                                          {"decorative_extent", &p.extent}};
    std::set<std::string> seen;
    std::string line;
    int version = 0;
    while (std::getline(file, line)) {
        line = line.substr(0, line.find('#'));
        std::istringstream row(line);
        std::string key, extra;
        if (!(row >> key))
            continue;
        if (!seen.insert(key).second)
            throw std::runtime_error("Duplicate canyon visual key: " + key);
        if (key == "DEATHWARD_CANYON") {
            if (!(row >> version) || version != 1)
                throw std::runtime_error("Invalid canyon visual version");
        } else if (key == "enabled") {
            int v;
            if (!(row >> v) || (v != 0 && v != 1))
                throw std::runtime_error("Invalid canyon enabled flag");
            p.enabled = v;
        } else if (key == "terrace_count" || key == "candidates_per_room" || key == "maximum_decorations") {
            int v;
            if (!(row >> v))
                throw std::runtime_error("Invalid canyon integer");
            (key == "terrace_count"         ? p.terraces
             : key == "candidates_per_room" ? p.candidatesPerRoom
                                            : p.maxDecorations) = v;
        } else if (auto it = fields.find(key); it != fields.end()) {
            if (!(row >> *it->second))
                throw std::runtime_error("Invalid canyon number: " + key);
        } else
            throw std::runtime_error("Unknown canyon visual key: " + key);
        if (row >> extra)
            throw std::runtime_error("Unexpected canyon visual argument: " + extra);
    }
    if (version != 1)
        throw std::runtime_error("Missing DEATHWARD_CANYON header");
    p.validate();
    return p;
}
bool CanyonAppearance::flipped(int x, int z) const {
    return parameters.enabled && hash(x / 2, z / 2, seed ^ 0x464143455453ULL) < parameters.facets;
}
float CanyonAppearance::height(float x, float z) const {
    const auto &f = surface;
    float gx = (x - f.x) / f.step, gz = (z - f.z) / f.step;
    int ix = int(std::floor(gx)), iz = int(std::floor(gz));
    if (ix < 0 || iz < 0 || ix >= f.width - 1 || iz >= f.depth - 1)
        return 20;
    if (!flipped(ix, iz))
        return f.height(x, z);
    float u = gx - ix, v = gz - iz, a = f.vertex(ix, iz).y, b = f.vertex(ix + 1, iz).y,
          c = f.vertex(ix, iz + 1).y, d = f.vertex(ix + 1, iz + 1).y;
    return u + v <= 1 ? a + u * (b - a) + v * (c - a) : d + (1 - u) * (c - d) + (1 - v) * (b - d);
}
SegmentHit CanyonAppearance::trace(Vector3 from, Vector3 to) const {
    const float x = surface.x, z = surface.z, step = surface.step, radius = 0;
    const int width = surface.width, depth = surface.depth;
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
        const Vector3 normal = unit(cross(sub(surface.vertex(ix, iz + 1), surface.vertex(ix, iz)),
                                          sub(surface.vertex(ix + 1, iz), surface.vertex(ix, iz))));
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
        const auto a = surface.vertex(ix, iz), b = surface.vertex(ix + 1, iz), c = surface.vertex(ix, iz + 1),
                   d = surface.vertex(ix + 1, iz + 1);
        if (flipped(ix, iz)) {
            triangle(a, c, b);
            triangle(b, c, d);
        } else {
            triangle(a, d, b);
            triangle(a, c, d);
        }
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
bool CanyonAppearance::supports(Vector3 p, float radius, float tolerance) const {
    float low = 10000, high = -10000;
    const int steps = std::max(2, int(std::ceil(2 * radius / .25f)));
    for (int x = 0; x <= steps; ++x)
        for (int z = 0; z <= steps; ++z) {
            float h = height(p.x - radius + 2 * radius * x / steps, p.z - radius + 2 * radius * z / steps);
            low = std::min(low, h);
            high = std::max(high, h);
        }
    return high - low <= tolerance && low >= -.015f && high < parameters.maxHeight + .5f;
}
CanyonAppearance buildCanyonAppearance(const Arena &arena, const CanyonVisualParameters &p) {
    p.validate();
    CanyonAppearance out;
    out.parameters = p;
    out.seed = arena.visualSeed;
    if (!arena.canyon)
        return out;
    const auto &source = *arena.canyon;
    out.surface = source;
    if (!p.enabled)
        return out;
    out.distanceToFloor = distances(source, false);
    out.distanceToRock = distances(source, true);
    for (int pass = 0; pass < 2; ++pass) {
        auto previous = out.distanceToFloor;
        for (int z = 1; z + 1 < source.depth; ++z)
            for (int x = 1; x + 1 < source.width; ++x) {
                size_t i = size_t(z * source.width + x);
                if (source.heights[i] > CanyonTerrain::WalkableHeight)
                    out.distanceToFloor[i] =
                        previous[i] * .5f + (previous[i - 1] + previous[i + 1] + previous[i - source.width] +
                                             previous[i + source.width]) *
                                                .125f;
            }
    }

    for (int z = 0; z < source.depth; ++z)
        for (int x = 0; x < source.width; ++x) {
            size_t i = size_t(z * source.width + x);
            auto v = source.vertex(x, z);
            if (v.y <= .2f)
                continue;
            float n = noise(v.x / 19, v.z / 19, out.seed),
                  broad = noise(v.x / 43, v.z / 43, out.seed ^ 0x4d455341ULL);
            float peak = smooth((broad - .78f) / .18f) * .28f;
            float cap =
                std::lerp(p.minHeight, p.maxHeight,
                          std::clamp(.17f + p.heightVariation * (.64f * n + .19f * broad + peak), 0.f, 1.f));
            float d = out.distanceToFloor[i];
            float warp = (noise(v.x / 8, v.z / 8, out.seed ^ 0x45444745ULL) - .5f) * p.silhouette * 1.7f;
            float localWidth =
                p.terraceWidth * (.78f + .44f * noise(v.x / 23, v.z / 23, out.seed ^ 0x5348454c46ULL));
            float tier = std::max(.05f, (d + warp) / localWidth),
                  level = std::min(1.f, (std::floor(tier) + smooth((tier - std::floor(tier)) / .52f)) /
                                            p.terraces);
            // Broad shelves, short face bands and restrained correlated grain. A
            // shared vertex lattice guarantees watertight neighboring sections.
            float grain =
                (noise(v.x / 3.75f, v.z / 3.75f, out.seed ^ 0x53544f4e45ULL) - .5f) * p.facets * .32f;
            float h = std::max(.18f, cap * level + grain * level);
            float outside = std::max({arena.bounds.min.x - v.x, v.x - arena.bounds.max.x,
                                      arena.bounds.min.z - v.z, v.z - arena.bounds.max.z, 0.f});
            if (outside > p.extent)
                h = std::lerp(h, std::min(h, 2.2f), smooth((outside - p.extent) / 12));
            out.surface.heights[i] = source.boundaryHeights.size() == source.heights.size() &&
                                             source.boundaryHeights[i] <= CanyonTerrain::WalkableHeight
                                         ? v.y * .93f
                                         : std::min({v.y, h, p.maxHeight});
        }
    // Visual profile is never handed back to navigation, rivers or projectile tracing.
    out.surface.boundaryHeights = out.surface.heights;
    auto reserved = [&](Vector3 at, float radius, int index) {
        const auto &room = arena.rooms[size_t(index)];
        const auto road = source.roadSample(at);
        if (road.distance < road.width + radius + .8f)
            return true;
        if (distance(at, room.center) < radius + 3.5f || distance(at, room.objective) < radius + 3.5f)
            return true;
        for (auto end : {room.entry, room.exit, room.objective})
            if (routeDistance(at, room.center, end) < radius + 1.3f)
                return true;
        for (int link : room.passages) {
            const auto &door = arena.passages[size_t(link)];
            if (routeDistance(at, door.from, door.to) < radius + 4.f)
                return true;
        }
        for (const auto &key : arena.keys)
            if (key.room == index && planarDistance(at, key.position) < radius + 2)
                return true;
        Box foot{{at.x - radius, -1, at.z - radius}, {at.x + radius, 2, at.z + radius}};
        for (const auto &prop : arena.breakables)
            if (overlaps(foot, prop.bounds, .5f))
                return true;
        for (const auto &prop : arena.floorProps)
            if (overlaps(foot, prop.bounds, .5f))
                return true;
        return arena.supplyCache.room >= 0 && overlaps(foot, arena.supplyCache.bounds, .6f);
    };
    for (int phase = 0; phase < 2; ++phase)
        for (int room = 0; room < arena.roomCount() && int(out.decorations.size()) < p.maxDecorations;
             ++room) {
            const auto &bounds = arena.rooms[size_t(room)].bounds;
            Random rng(out.seed ^ 0x5445525241434553ULL ^ uint64_t(room + 1) * 0x9e3779b97f4a7c15ULL ^
                       uint64_t(phase) * 0x4558545241564547ULL);
            for (int n = 0; n < p.candidatesPerRoom && int(out.decorations.size()) < p.maxDecorations; ++n) {
                const float skirt = n % 5 == 0 ? p.extent * .6f : 3.f;
                Vector3 at{rng.real(bounds.min.x - skirt, bounds.max.x + skirt), 0,
                           rng.real(bounds.min.z - skirt, bounds.max.z + skirt)};
                int x = int((at.x - source.x) / source.step), z = int((at.z - source.z) / source.step);
                if (x < 1 || z < 1 || x >= source.width - 2 || z >= source.depth - 2)
                    continue;
                float h = out.height(at.x, at.z);
                if (h < -.015f || source.waterBlocked(at))
                    continue;
                const size_t i = size_t(z * source.width + x);
                const bool floor = source.height(at.x, at.z) <= CanyonTerrain::WalkableHeight;
                CanyonZone zone =
                    floor ? (out.distanceToRock[i] < 3 ? CanyonZone::CliffBase : CanyonZone::Floor)
                    : out.distanceToFloor[i] < p.terraceWidth * (p.terraces - .3f) ? CanyonZone::Terrace
                                                                                   : CanyonZone::Plateau;
                float vegetation = zone == CanyonZone::Floor       ? p.floorVegetation
                                   : zone == CanyonZone::CliffBase ? p.baseVegetation
                                   : zone == CanyonZone::Terrace   ? p.terraceVegetation
                                                                   : p.plateauVegetation;
                bool rock = rng.real(0, 1) < (zone == CanyonZone::CliffBase ? .65f : .3f);
                if (phase && rock)
                    continue;
                if (rng.real(0, 1) > std::min(1.f, (rock ? p.debris : vegetation) * .7f))
                    continue;
                auto kind = rock ? CanyonDecorationKind::Rock
                            : zone == CanyonZone::Plateau && rng.bounded(10) == 0
                                ? CanyonDecorationKind::Cactus
                            : rng.bounded(3) == 0 ? CanyonDecorationKind::Shrub
                                                  : CanyonDecorationKind::Grass;
                float span = kind == CanyonDecorationKind::Rock     ? rng.real(.2f, .8f)
                             : kind == CanyonDecorationKind::Cactus ? rng.real(.7f, 1.1f)
                             : kind == CanyonDecorationKind::Shrub  ? rng.real(1.25f, 2.1f)
                                                                    : rng.real(.65f, 1.1f);
                float height = kind == CanyonDecorationKind::Rock     ? span * rng.real(.35f, .7f)
                               : kind == CanyonDecorationKind::Cactus ? rng.real(1.5f, 2.5f)
                               : kind == CanyonDecorationKind::Shrub  ? rng.real(.5f, .9f)
                                                                      : rng.real(.45f, .8f);
                if (reserved(at, span * .6f, room) ||
                    !out.supports(at, span * .65f, kind == CanyonDecorationKind::Cactus ? .1f : .16f))
                    continue;
                // Overlapping room skirts share one sparse global cosmetic candidate set.
                if (std::any_of(out.decorations.begin(), out.decorations.end(), [&](const auto &d) {
                        return planarDistance(at, d.position) < (d.span + span) * .6f + .3f;
                    }))
                    continue;
                at.y = h - .025f;
                out.decorations.push_back(
                    {kind, zone, at, span, height, rng.real(0, 2 * Pi), room, phase != 0});
            }
        }
    return out;
}
} // namespace dw
