#include "world/CanyonAppearance.hpp"
#include "world/CliffWallTopology.hpp"
#include <tuple>
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
// Jittered geological cells make separate mesas with low saddles between
// them, instead of wrapping every room in the same concentric height bands.
float mesaCap(float x, float z, uint64_t seed, int tiers) {
    constexpr float span = 9.f;
    int ix = int(std::floor(x / span)), iz = int(std::floor(z / span));
    float first = 1e9f, second = 1e9f, value = 0;
    for (int dz = -1; dz <= 1; ++dz)
        for (int dx = -1; dx <= 1; ++dx) {
            int cx = ix + dx, cz = iz + dz;
            float px = (cx + .2f + .6f * hash(cx, cz, seed)) * span;
            float pz = (cz + .2f + .6f * hash(cx, cz, seed ^ 0x5aULL)) * span;
            float d = std::hypot(x - px, z - pz);
            if (d < first) {
                second = first;
                first = d;
                value = hash(cx, cz, seed ^ 0x484549474854ULL);
            } else
                second = std::min(second, d);
        }
    return std::lerp(.55f, .8f + float(tiers) * value, smooth((second - first) / 1.5f));
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
void indexSurface(CanyonAppearance &out) {
    const auto &source=out.surface;
    // A displaced triangle can cross the source lattice. Spatial queries and
    // occlusion must use its real bounds rather than its original cell ID.
    const int columns = source.width - 1, rows = source.depth - 1;
    auto bounds = [&](const CanyonSurfaceTriangle &triangle) {
        int left = columns - 1, right = 0, top = rows - 1, bottom = 0;
        for (auto v : triangle.vertices) {
            int x = std::clamp(int(std::floor((v.x - source.x) / source.step)), 0, columns - 1);
            int z = std::clamp(int(std::floor((v.z - source.z) / source.step)), 0, rows - 1);
            left = std::min(left, x);
            right = std::max(right, x);
            top = std::min(top, z);
            bottom = std::max(bottom, z);
        }
        return std::array<int, 4>{left, right, top, bottom};
    };
    out.spatialOffsets.assign(size_t(columns * rows) + 1, 0);
    for (const auto &triangle : out.triangles) {
        auto b = bounds(triangle);
        for (int z = b[2]; z <= b[3]; ++z)
            for (int x = b[0]; x <= b[1]; ++x)
                ++out.spatialOffsets[size_t(z * columns + x) + 1];
    }
    for (size_t i = 1; i < out.spatialOffsets.size(); ++i)
        out.spatialOffsets[i] += out.spatialOffsets[i - 1];
    out.spatialTriangles.resize(out.spatialOffsets.back());
    auto cursor = out.spatialOffsets;
    for (size_t i = 0; i < out.triangles.size(); ++i) {
        auto b = bounds(out.triangles[i]);
        for (int z = b[2]; z <= b[3]; ++z)
            for (int x = b[0]; x <= b[1]; ++x)
                out.spatialTriangles[cursor[size_t(z * columns + x)]++] = i;
    }
}
} // namespace
void CanyonVisualParameters::validate() const {
    auto range = [](float v, float a, float b) { return std::isfinite(v) && v >= a && v <= b; };
    if (!range(minHeight, .8f, 10) || !range(maxHeight, minHeight, 16) || !range(heightVariation, 0, 1) ||
        terraces < 1 || terraces > 6 || !range(terraceWidth, 1, 8) || !range(silhouette, 0, 1) ||
        !range(facets, 0, 1) || !range(extent, 0, 35) || !range(composition, 0, 1) || !range(debris, 0, 3) ||
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
                                          {"decorative_extent", &p.extent},
                                          {"composition_strength", &p.composition}};
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
        } else if (key == "enabled" || key == "irregular_facets" || key == "polygon_facets") {
            int v;
            if (!(row >> v) || (v != 0 && v != 1))
                throw std::runtime_error("Invalid canyon enabled flag");
            (key == "enabled"          ? p.enabled
             : key == "polygon_facets" ? p.polygonFacets
                                       : p.irregularFacets) = v;
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
float CanyonAppearance::height(float x, float z) const {
    if (triangles.empty())
        return surface.height(x, z);
    int ix = int(std::floor((x - surface.x) / surface.step)),
        iz = int(std::floor((z - surface.z) / surface.step));
    if (ix < 0 || iz < 0 || ix >= surface.width - 1 || iz >= surface.depth - 1)
        return 20;
    size_t cell = size_t(iz * (surface.width - 1) + ix);
    float result = -10000;
    for (size_t i = queryBegin(cell); i < queryEnd(cell); ++i) {
        const auto &t = triangles[queryTriangle(i)].vertices;
        auto a = t[0], b = t[1], c = t[2];
        float det = (b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x);
        if (std::abs(det) < .000001f)
            continue; // Vertical walls have no height footprint.
        float u = ((x - a.x) * (c.z - a.z) - (z - a.z) * (c.x - a.x)) / det;
        float v = ((b.x - a.x) * (z - a.z) - (b.z - a.z) * (x - a.x)) / det;
        if (u >= -.00001f && v >= -.00001f && u + v <= 1.00001f)
            result = std::max(result, a.y + u * (b.y - a.y) + v * (c.y - a.y));
    }
    return result == -10000 ? surface.height(x, z) : result;
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
            // Clipping can create very small triangles. An absolute edge
            // tolerance incorrectly accepts rays far outside thin polygons.
            const float margin = .00001f * dot(cross(sub(b, a), sub(c, a)), normal);
            if (edge(a, b) >= -margin && edge(b, c) >= -margin && edge(c, a) >= -margin)
                best = {true, t, normal};
        };
        if (!triangles.empty()) {
            size_t cell = size_t(iz * (width - 1) + ix);
            for (size_t i = queryBegin(cell); i < queryEnd(cell); ++i) {
                const auto &v = triangles[queryTriangle(i)].vertices;
                triangle(v[0], v[1], v[2]);
            }
        } else {
            auto a = surface.vertex(ix, iz), b = surface.vertex(ix + 1, iz), c = surface.vertex(ix, iz + 1),
                 d = surface.vertex(ix + 1, iz + 1);
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
    if (triangles.empty()) {
        const int steps = std::max(2, int(std::ceil(2 * radius / .12f)));
        for (int x = 0; x <= steps; ++x)
            for (int z = 0; z <= steps; ++z) {
                float h =
                    height(p.x - radius + 2 * radius * x / steps, p.z - radius + 2 * radius * z / steps);
                low = std::min(low, h);
                high = std::max(high, h);
            }
    } else {
        const float left = p.x - radius, right = p.x + radius, top = p.z - radius, bottom = p.z + radius;
        int x0 = int(std::floor((left - surface.x) / surface.step)),
            x1 = int(std::floor((right - surface.x) / surface.step));
        int z0 = int(std::floor((top - surface.z) / surface.step)),
            z1 = int(std::floor((bottom - surface.z) / surface.step));
        if (x0 < 0 || z0 < 0 || x1 >= surface.width - 1 || z1 >= surface.depth - 1)
            return false;
        for (int z = z0; z <= z1; ++z)
            for (int x = x0; x <= x1; ++x) {
                size_t cell = size_t(z * (surface.width - 1) + x);
                const bool original = !supportTriangles.empty();
                const auto &faces = original ? supportTriangles : triangles;
                size_t begin = original ? supportOffsets[cell] : queryBegin(cell);
                size_t end = original ? supportOffsets[cell + 1] : queryEnd(cell);
                for (size_t i = begin; i < end; ++i) {
                    // Clip the actual triangle to the support square. This catches
                    // thin risers and bevels that fixed sample grids can step over.
                    std::array<Vector3, 32> a{}, b{};
                    const auto &face = faces[original ? supportIndices[i] : queryTriangle(i)].vertices;
                    std::copy(face.begin(), face.end(), a.begin());
                    int count = 3;
                    for (int plane = 0; plane < 4 && count; ++plane) {
                        auto value = [&](Vector3 v) {
                            return plane == 0   ? v.x - left
                                   : plane == 1 ? right - v.x
                                   : plane == 2 ? v.z - top
                                                : bottom - v.z;
                        };
                        int n = 0;
                        auto previous = a[size_t(count - 1)];
                        float av = value(previous);
                        for (int j = 0; j < count; ++j) {
                            if (n >= int(b.size()) - 2)
                                return false;
                            auto next = a[size_t(j)];
                            float bv = value(next);
                            if ((av >= 0) != (bv >= 0))
                                b[size_t(n++)] = add(previous, mul(sub(next, previous), av / (av - bv)));
                            if (bv >= 0)
                                b[size_t(n++)] = next;
                            previous = next;
                            av = bv;
                        }
                        count = n;
                        a = b;
                    }
                    for (int j = 0; j < count; ++j) {
                        low = std::min(low, a[size_t(j)].y);
                        high = std::max(high, a[size_t(j)].y);
                    }
                    if (high - low > tolerance)
                        return false;
                }
            }
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

    // Clip source triangles into contour bands. Each band gets an broad, nearly horizontal
    // cap, and its contour edges are extruded vertically. We never interpolate
    // heights between tiers: a shelf meets a wall, not a triangular embankment.
    struct Point {
        Vector3 p;
        float mask;
        std::array<float, 6> layers{};
    };
    using Polygon = std::vector<Point>;
    auto clip = [](const Polygon &poly, float threshold, int layer, bool greater) {
        Polygon result;
        if (poly.empty())
            return result;
        auto value = [&](const Point &v) {
            return (layer >= 0 ? v.layers[size_t(layer)] : v.mask) - threshold;
        };
        auto inside = [&](float v) { return greater ? v >= 0 : v <= 0; };
        Point a = poly.back();
        float av = value(a);
        for (const auto &b : poly) {
            float bv = value(b);
            if (inside(av) != inside(bv)) {
                float t = av / (av - bv);
                Point point{add(a.p, mul(sub(b.p, a.p), t)), std::lerp(a.mask, b.mask, t)};
                for (size_t i = 0; i < point.layers.size(); ++i)
                    point.layers[i] = std::lerp(a.layers[i], b.layers[i], t);
                result.push_back(point);
            }
            if (inside(bv))
                result.push_back(b);
            a = b;
            av = bv;
        }
        return result;
    };
    std::vector<std::array<float, 6>> layers(source.heights.size());
    for (int z = 0; z < source.depth; ++z)
        for (int x = 0; x < source.width; ++x) {
            size_t i = size_t(z * source.width + x);
            auto v = source.vertex(x, z);
            float n = .65f * noise(v.x / 9, v.z / 9, out.seed ^ 0x4d455341ULL) +
                      .35f * noise(v.x / 23, v.z / 23, out.seed ^ 0x4d455341ULL);
            n = std::clamp((n - .5f) * 2.2f + .5f, 0.f, 1.f);
            float warp = (noise(v.x / 6, v.z / 6, out.seed ^ 0x45444745ULL) - .5f) * p.silhouette * 1.8f;
            float width =
                p.terraceWidth * (.65f + .75f * noise(v.x / 7, v.z / 7, out.seed ^ 0x5348454c46ULL));
            // A broad cap limiter makes neighboring formations stop at different
            // elevation levels. Changes in that limiter also produce vertical walls.
            float localCap =
                std::lerp(float(p.terraces),
                          .25f * n + .75f * mesaCap(v.x, v.z, out.seed ^ 0x424c4f434bULL, p.terraces),
                          p.heightVariation);
            // Static composition follows the game's normal scenic axis, not
            // the live camera. Foreground shoulders remain low while distant
            // walls carry the larger sandstone masses.
            const RoomLayout *nearest = &arena.rooms.front();
            float closest = 1e30f;
            for (const auto &room : arena.rooms) {
                float dx = v.x - room.center.x, dz = v.z - room.center.z;
                float d = dx * dx + dz * dz;
                if (d < closest) {
                    closest = d;
                    nearest = &room;
                }
            }
            float rx = std::max(1.f, (nearest->bounds.max.x - nearest->bounds.min.x) * .5f);
            float rz = std::max(1.f, (nearest->bounds.max.z - nearest->bounds.min.z) * .5f);
            float back = std::clamp(
                .5f - .25f * ((v.x - nearest->center.x) / rx + (v.z - nearest->center.z) / rz), 0.f, 1.f);
            float framing =
                std::lerp(float(p.terraces) + .5f, .4f + (p.terraces + .2f) * back, p.composition);
            localCap = std::min(localCap, framing);
            float outside = std::max({arena.bounds.min.x - v.x, v.x - arena.bounds.max.x,
                                      arena.bounds.min.z - v.z, v.z - arena.bounds.max.z, 0.f});
            localCap = std::lerp(localCap, std::min(localCap, .8f), smooth((outside - p.extent) / 12));
            // Each shelf has an independent, domain-warped erosion field.
            // Nesting is enforced at vertices (and therefore along clipped edges),
            // so local ledges can end/merge without crossing or opening seams.
            float previous = 1000;
            for (int band = 0; band < p.terraces; ++band) {
                uint64_t salt = out.seed ^ (0x45524f53494f4eULL + uint64_t(band) * 0x9e3779b97f4a7c15ULL);
                float wx = v.x + 4 * p.silhouette * (noise(v.x / 17, v.z / 17, salt) - .5f);
                float wz = v.z + 4 * p.silhouette * (noise(v.x / 17, v.z / 17, salt ^ 0x123ULL) - .5f);
                float erosion = (noise(wx / 8, wz / 8, salt ^ 0x214ULL) - .5f) * 3 * p.silhouette;
                float shelfWidth = width * (.75f + .75f * noise(wx / 12, wz / 12, salt ^ 0x317ULL));
                float available = out.distanceToFloor[i] / shelfWidth + warp + erosion - float(band + 1);
                float geology = localCap - float(band + 1) + erosion * .65f;
                float value = std::min({available, geology, previous - .28f});
                if (source.heights[i] <= CanyonTerrain::WalkableHeight ||
                    (source.boundaryHeights.size() == source.heights.size() &&
                     source.boundaryHeights[i] <= CanyonTerrain::WalkableHeight))
                    value = -2.f - float(band);
                layers[i][size_t(band)] = value;
                previous = value;
            }
        }
    const float bevelHeight = std::min(
        {.15f + .20f * p.facets, (p.maxHeight - p.minHeight) / p.terraces * .49f, p.minHeight * .35f});

    auto planeAt = [&](Vector3 at, int cells, uint64_t salt) {
        float gx = (at.x - source.x) / (source.step * cells), gz = (at.z - source.z) / (source.step * cells);
        int ix = int(std::floor(gx)), iz = int(std::floor(gz));
        float u = gx - ix, v = gz - iz;
        auto seed = out.seed ^ salt;
        float a = hash(ix, iz, seed), b = hash(ix + 1, iz, seed), c = hash(ix, iz + 1, seed),
              d = hash(ix + 1, iz + 1, seed);
        return u >= v ? a + u * (b - a) + v * (d - b) : a + v * (c - a) + u * (d - c);
    };
    auto elevation = [&](int band, Vector3 at) {
        float base = p.minHeight *
                     std::lerp(1.f, .75f + .7f * planeAt(at, 8, 0x4241534552495345ULL), p.heightVariation);
        float rise = (p.maxHeight - p.minHeight) / p.terraces;
        for (int k = 0; k < band; ++k)
            base +=
                rise *
                std::lerp(1.f,
                          .45f + .8f * planeAt(at, 13, 0x52495345ULL + uint64_t(k) * 0x9e3779b97f4a7c15ULL),
                          p.heightVariation);
        return base;
    };
    auto outcropWeight = [&](Vector3 at) {
        float boundary = source.height(at.x, at.z, true);
        float rock = std::max(0.f, source.height(at.x, at.z) - boundary);
        return (1 - smooth(std::max(0.f, boundary) / .45f)) * smooth(rock / .15f);
    };
    auto topOffset = [&](Vector3 at) {
        float fine =
            std::min(p.facets * .6f, p.minHeight * .12f) * (planeAt(at, 3, 0x434150504c414e45ULL) - 1);
        float formation = std::min(p.heightVariation * .6f, p.minHeight * .22f) *
                          (2 * planeAt(at, 9, 0x464f524d4154494fULL) - 1);
        float natural = .55f + 1.18f * std::sqrt(std::max(0.f, source.height(at.x, at.z))) -
                        elevation(0, at) + fine * .25f;
        return std::lerp(formation + fine, natural, outcropWeight(at));
    };
    auto localBevel = [&](Vector3 at) {
        return std::lerp(bevelHeight, std::min(.12f, bevelHeight), outcropWeight(at));
    };
    auto append = [&](Vector3 a, Vector3 b, Vector3 c, bool rock) {
        if (dot(cross(sub(b, a), sub(c, a)), cross(sub(b, a), sub(c, a))) > 1e-10f)
            out.triangles.push_back({{a, b, c}, rock});
    };
    auto cap = [&](const Polygon &poly, int band, bool rock, int bevel = -1) {
        for (size_t i = 1; i + 1 < poly.size(); ++i) {
            auto a = poly[0].p, b = poly[i].p, c = poly[i + 1].p;
            if (rock) {
                auto top = [&](const Point &point) {
                    float t = bevel < 0    ? 1.f
                              : bevel == 0 ? point.mask / .12f
                                           : point.layers[size_t(bevel - 1)] / .20f;
                    return std::min(p.maxHeight, elevation(band, point.p) - localBevel(point.p) +
                                                     localBevel(point.p) * std::clamp(t, 0.f, 1.f) +
                                                     topOffset(point.p));
                };
                a.y = top(poly[0]);
                b.y = top(poly[i]);
                c.y = top(poly[i + 1]);
            }
            append(a, b, c, rock);
        }
    };
    auto wall = [&](const Polygon &poly, float threshold, int layer, int low, int high,
                    const Polygon &foot = Polygon{}) {
        if (poly.size() < 2)
            return;
        // Only contour edges, never the source triangle's internal edges.
        for (size_t i = 0; i < poly.size(); ++i) {
            const auto &a = poly[i], &b = poly[(i + 1) % poly.size()];
            float av = layer >= 0 ? a.layers[size_t(layer)] : a.mask,
                  bv = layer >= 0 ? b.layers[size_t(layer)] : b.mask;
            if (std::abs(av - threshold) > .0001f || std::abs(bv - threshold) > .0001f)
                continue;
            auto at = a.p, bt = b.p, ab = a.p, bb = b.p;
            if (!foot.empty()) {
                std::vector<Vector3> edge;
                for (const auto &v : foot)
                    if (std::abs(v.mask) < .00001f)
                        edge.push_back(v.p);
                if (edge.size() == 2) {
                    if (distance(at, edge[0]) + distance(bt, edge[1]) >
                        distance(at, edge[1]) + distance(bt, edge[0]))
                        std::swap(edge[0], edge[1]);
                    ab = edge[0];
                    bb = edge[1];
                }
            }
            at.y = std::min(p.maxHeight, elevation(high, at) + topOffset(at) - localBevel(at));
            bt.y = std::min(p.maxHeight, elevation(high, bt) + topOffset(bt) - localBevel(bt));
            ab.y = std::min(p.maxHeight,
                            layer >= 0 ? elevation(low, ab) + topOffset(ab) : CanyonTerrain::WalkableHeight);
            bb.y = std::min(p.maxHeight,
                            layer >= 0 ? elevation(low, bb) + topOffset(bb) : CanyonTerrain::WalkableHeight);
            append(ab, bt, at, true);
            append(ab, bb, bt, true);
        }
    };
    out.triangles.reserve(size_t((source.width - 1) * (source.depth - 1) * 3));
    out.cellOffsets.reserve(size_t((source.width - 1) * (source.depth - 1) + 1));
    for (int z = 0; z + 1 < source.depth; ++z)
        for (int x = 0; x + 1 < source.width; ++x) {
            out.cellOffsets.push_back(out.triangles.size());
            auto point = [&](int dx, int dz) {
                size_t i = size_t((z + dz) * source.width + x + dx);
                return Point{source.vertex(x + dx, z + dz), source.heights[i] - CanyonTerrain::WalkableHeight,
                             layers[i]};
            };
            auto a = point(0, 0), b = point(1, 0), c = point(0, 1), d = point(1, 1);
            // Keep the canonical diagonal at the floor boundary; this preserves
            // the precise contour around roads, sockets and river banks.
            for (const auto &tri : std::array<Polygon, 2>{Polygon{a, d, b}, Polygon{a, c, d}}) {
                auto ground = clip(tri, 0, -1, false);
                cap(ground, 0, false);
                auto foot = clip(tri, 0, -1, true);
                auto rim = tri;
                for (auto &v : rim)
                    v.mask = std::min(v.mask, .5f);
                auto rock = clip(rim, 0, -1, true);
                // Recess the upper rim slightly while retaining the exact canonical
                // ground contact. These short, steep buttresses remove needle-like
                // top corners without widening into the playable floor.
                wall(rock, 0, -1, 0, 0, foot);
                for (int band = 0; band <= p.terraces; ++band) {
                    auto poly = band ? clip(rock, 0, band - 1, true) : rock;
                    if (band && std::any_of(rock.begin(), rock.end(), [&](const auto &v) {
                            return v.layers[size_t(band - 1)] < -.00001f;
                        }))
                        wall(poly, 0, band - 1, band - 1, band);
                    if (band < p.terraces)
                        poly = clip(poly, 0, band, false);
                    // Small top-edge chamfer, then a broad, nearly horizontal cap.
                    auto bevel = clip(poly, band ? .20f : .12f, band - 1, false);
                    auto flat = clip(poly, band ? .20f : .12f, band - 1, true);
                    cap(bevel, band, true, band);
                    cap(flat, band, true);
                }
            }
        }
    out.cellOffsets.push_back(out.triangles.size());
    // The floor contour is immutable. Only the upper mesh is eroded inward.
    // This deliberately separates scenic contours from the canonical heightmap:
    // visible upper faces need not inherit its long straight boundary segments.
    auto floorDistance = [&](float wx, float wz) {
        float gx = std::clamp((wx - source.x) / source.step, 0.f, float(source.width - 1) - .001f);
        float gz = std::clamp((wz - source.z) / source.step, 0.f, float(source.depth - 1) - .001f);
        int x = int(gx), z = int(gz);
        float u = gx - x, v = gz - z;
        size_t i = size_t(z * source.width + x);
        return std::lerp(
            std::lerp(out.distanceToFloor[i], out.distanceToFloor[i + 1], u),
            std::lerp(out.distanceToFloor[i + source.width], out.distanceToFloor[i + source.width + 1], u),
            v);
    };
    for (auto &triangle : out.triangles) {
        if (!triangle.rock)
            continue;
        for (auto &v : triangle.vertices) {
            if (v.x < source.x + source.step || v.z < source.z + source.step ||
                v.x > source.x + (source.width - 2) * source.step ||
                v.z > source.z + (source.depth - 2) * source.step ||
                v.y <= CanyonTerrain::WalkableHeight + .00001f || outcropWeight(v) > .5f)
                continue;
            Vector3 inward{floorDistance(v.x + source.step, v.z) - floorDistance(v.x - source.step, v.z), 0,
                           floorDistance(v.x, v.z + source.step) - floorDistance(v.x, v.z - source.step)};
            float length = std::sqrt(dot(inward, inward));
            if (length < .001f)
                continue;
            float amount = .65f * p.silhouette * smooth((v.y - CanyonTerrain::WalkableHeight) / 3.5f) *
                           (.2f + .8f * noise(v.x / 6.f, v.z / 6.f, out.seed ^ 0x52494d45524f4445ULL));
            auto displaced = add(v, mul(inward, amount / length));
            if (source.height(displaced.x, displaced.z) > CanyonTerrain::WalkableHeight)
                v = displaced;
        }
    }
    indexSurface(out);
    // The sampled surface is useful for water/detail metadata only. The mesh
    // and all visual height/ray tests use the explicit caps and wall triangles.
    for (int z = 0; z < source.depth; ++z)
        for (int x = 0; x < source.width; ++x) {
            size_t i = size_t(z * source.width + x);
            if (source.heights[i] > CanyonTerrain::WalkableHeight)
                out.surface.heights[i] =
                    std::min(p.maxHeight,
                             elevation(int(std::count_if(layers[i].begin(), layers[i].begin() + p.terraces,
                                                         [](float v) { return v >= 0; })),
                                       source.vertex(x, z)) +
                                 topOffset(source.vertex(x, z)));
        }
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
                float pocket =
                    smooth((noise(at.x / 5.f, at.z / 5.f, out.seed ^ 0x504f434b4554ULL) - .25f) * 2.f);
                if (rng.real(0, 1) > std::min(1.f, (rock ? p.debris : vegetation) * (.2f + 1.1f * pocket)))
                    continue;
                auto kind =
                    rock ? CanyonDecorationKind::Rock
                    : (zone == CanyonZone::Plateau || zone == CanyonZone::CliffBase) && rng.bounded(12) == 0
                        ? CanyonDecorationKind::Cactus
                    : rng.bounded(3) == 0 ? CanyonDecorationKind::Shrub
                                          : CanyonDecorationKind::Grass;
                if (!rock && zone == CanyonZone::Plateau && n % 19 == 0)
                    kind = CanyonDecorationKind::Tree;
                float span = kind == CanyonDecorationKind::Tree ? rng.real(2.3f, 3.1f)
                             : kind == CanyonDecorationKind::Rock
                                 ? (zone == CanyonZone::CliffBase ? rng.real(.35f, 1.f) : rng.real(.2f, .8f))
                             : kind == CanyonDecorationKind::Cactus ? rng.real(.7f, 1.1f)
                             : kind == CanyonDecorationKind::Shrub  ? rng.real(.55f, .95f)
                                                                    : rng.real(.45f, .85f);
                float height = kind == CanyonDecorationKind::Tree     ? rng.real(3.2f, 4.2f)
                               : kind == CanyonDecorationKind::Rock   ? span * rng.real(.35f, .7f)
                               : kind == CanyonDecorationKind::Cactus ? rng.real(1.5f, 2.5f)
                               : kind == CanyonDecorationKind::Shrub  ? rng.real(.65f, 1.f)
                                                                      : rng.real(.45f, .8f);
                if (reserved(at, span * .6f, room) ||
                    !out.supports(at, kind == CanyonDecorationKind::Tree ? .45f : span * .65f,
                                  kind == CanyonDecorationKind::Cactus ? .1f : .16f))
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
    // Give suitable upper room corners a sparse background canopy. Trees use
    // trunk/root support, not their overhanging crown as a ground footprint.
    if (p.plateauVegetation > 0 && p.candidatesPerRoom > 0)
        for (int room = 0; room < arena.roomCount(); ++room) {
            if (int(out.decorations.size()) >= p.maxDecorations)
                break;
            if (std::any_of(out.decorations.begin(), out.decorations.end(), [&](const auto &d) {
                    return d.room == room && d.kind == CanyonDecorationKind::Tree && !d.extraVegetation;
                }))
                continue;
            Random rng(out.seed ^ 0x43414e4f5059ULL ^ uint64_t(room + 1) * 0x9e3779b97f4a7c15ULL);
            const auto &b = arena.rooms[size_t(room)].bounds;
            for (int attempt = 0; attempt < std::min(32, p.candidatesPerRoom); ++attempt) {
                int corner = attempt / 8;
                Vector3 at{(corner & 1 ? b.max.x : b.min.x) + rng.real(-4, 4), 0,
                           (corner & 2 ? b.max.z : b.min.z) + rng.real(-4, 4)};
                if (source.height(at.x, at.z) <= CanyonTerrain::WalkableHeight || source.waterBlocked(at) ||
                    reserved(at, 2, room) || !out.supports(at, .45f, .16f))
                    continue;
                if (std::any_of(out.decorations.begin(), out.decorations.end(), [&](const auto &d) {
                        return planarDistance(at, d.position) < (d.span + 2.8f) * .6f + .3f;
                    }))
                    continue;
                at.y = out.height(at.x, at.z) - .025f;
                out.decorations.push_back({CanyonDecorationKind::Tree, CanyonZone::Plateau, at, 2.8f, 3.8f,
                                           rng.real(0, 2 * Pi), room, false});
                break;
            }
        }
    // A sparse flowering cactus on suitable canyon-floor edges provides the
    // reference's foreground green accent without occupying the combat center.
    if (p.baseVegetation > 0 && p.candidatesPerRoom > 0)
        for (int room = 0; room < arena.roomCount(); ++room) {
            if (int(out.decorations.size()) >= p.maxDecorations)
                break;
            if (std::any_of(out.decorations.begin(), out.decorations.end(), [&](const auto &d) {
                    return d.room == room && d.kind == CanyonDecorationKind::Cactus && !d.extraVegetation &&
                           source.height(d.position.x, d.position.z) <= CanyonTerrain::WalkableHeight;
                }))
                continue;
            Random rng(out.seed ^ 0x464c4f574552ULL ^ uint64_t(room + 1) * 0x9e3779b97f4a7c15ULL);
            const auto &b = arena.rooms[size_t(room)].bounds;
            for (int attempt = 0; attempt < std::min(80, p.candidatesPerRoom); ++attempt) {
                Vector3 at{rng.real(b.min.x + 1, b.max.x - 1), 0, rng.real(b.min.z + 1, b.max.z - 1)};
                int x = int((at.x - source.x) / source.step), z = int((at.z - source.z) / source.step);
                if (x < 0 || z < 0 || x >= source.width || z >= source.depth)
                    continue;
                if (out.distanceToRock[size_t(z * source.width + x)] > 3.5f ||
                    source.height(at.x, at.z) > CanyonTerrain::WalkableHeight || source.blocked(at, .8f) ||
                    reserved(at, 1.1f, room) || !out.supports(at, .8f, .1f))
                    continue;
                if (std::any_of(out.decorations.begin(), out.decorations.end(), [&](const auto &d) {
                        return planarDistance(at, d.position) < (d.span + 1.f) * .6f + .3f;
                    }))
                    continue;
                at.y = out.height(at.x, at.z) - .025f;
                out.decorations.push_back({CanyonDecorationKind::Cactus, CanyonZone::CliffBase, at, 1.f, 2.4f,
                                           rng.real(0, 2 * Pi), room, false});
                break;
            }
        }
    std::stable_partition(out.decorations.begin(), out.decorations.end(),
                          [](const auto &d) { return !d.extraVegetation; });
    if (p.irregularFacets && p.facets > 0) {
        // Only wall interiors change. Top/bottom contours and all non-wall triangles
        // stay fixed. Connected faces share a 2D network rather than a fan per column.
        using cliffDetail::Quad;
        struct Face {
            Quad q;
            size_t triangle;
        };
        std::vector<Face> faces;
        using Edge = std::array<int64_t, 6>;
        auto edge = [](Vector3 a, Vector3 b) {
            return Edge{std::llround(a.x * 1000), std::llround(a.y * 1000), std::llround(a.z * 1000),
                        std::llround(b.x * 1000), std::llround(b.y * 1000), std::llround(b.z * 1000)};
        };
        std::map<Edge, std::vector<size_t>> starts;
        std::map<Edge, int> ends;
        auto protectedCover = [&](Vector3 at) {
            for (const auto &room : arena.rooms)
                for (const auto &box : room.obstacles)
                    if (at.x >= box.min.x - source.step && at.x <= box.max.x + source.step &&
                        at.z >= box.min.z - source.step && at.z <= box.max.z + source.step)
                        return true;
            return false;
        };
        for (size_t i = 0; i + 1 < out.triangles.size(); ++i) {
            const auto &a = out.triangles[i], &b = out.triangles[i + 1];
            if (!a.rock || !b.rock || !cliffDetail::near(a.vertices[0], b.vertices[0]) ||
                !cliffDetail::near(a.vertices[1], b.vertices[2]))
                continue;
            Quad q{a.vertices[0], b.vertices[1], a.vertices[1], a.vertices[2]};
            auto n = cliffDetail::normal(q);
            auto mid = mul(add(q.at, q.bt), .5f);
            if (std::abs(n.y) > (p.polygonFacets ? .65f : .35f) ||
                std::min(q.at.y - q.ab.y, q.bt.y - q.bb.y) < .4f ||
                distance(q.ab, q.bb) < (p.polygonFacets ? .001f : .1f) ||
                (p.polygonFacets ? protectedCover(mid) : outcropWeight(mid) >= .5f))
                continue;
            starts[edge(q.ab, q.at)].push_back(faces.size());
            ++ends[edge(q.bb, q.bt)];
            faces.push_back({q, i});
            ++i;
        }
        std::vector<bool> used(faces.size()), skip(out.triangles.size());
        std::map<size_t, std::vector<CanyonSurfaceTriangle>> replacements;
        std::vector<size_t> order;
        for (size_t i = 0; i < faces.size(); ++i)
            if (!ends.contains(edge(faces[i].q.ab, faces[i].q.at)))
                order.push_back(i);
        for (size_t i = 0; i < faces.size(); ++i)
            order.push_back(i);
        for (auto first : order) {
            if (used[first])
                continue;
            std::vector<size_t> chain;
            std::vector<Quad> patch;
            size_t next = first;
            float width = 0;
            while (!used[next]) {
                auto q = faces[next].q;
                used[next] = true;
                chain.push_back(next);
                patch.push_back(q);
                width += distance(q.ab, q.bb);
                if (patch.size() >= (p.polygonFacets ? 64u : 12u))
                    break;
                auto it = starts.find(edge(q.bb, q.bt));
                if (it == starts.end() || it->second.size() != 1)
                    break;
                next = it->second.front();
                auto candidate = faces[next].q;
                // Source clipping makes staircase contours with alternating 90-degree
                // grid edges. They belong to one rock surface, not separate columns.
                if (used[next] ||
                    dot(cliffDetail::normal(patch.front()), cliffDetail::normal(candidate)) <
                        (p.polygonFacets ? -.35f : .35f) ||
                    width + distance(candidate.ab, candidate.bb) > (p.polygonFacets ? 32 : 11))
                    break;
            }
            if (patch.size() < 3 && (patch.front().at.y - patch.front().ab.y < 1.f || width < .6f)) {
                ++out.cliffTopologyFallbacks;
                continue;
            }
            try {
                const auto mid = patch.front().ab;
                uint64_t localSeed = out.seed ^
                                     uint64_t(int64_t(std::llround(mid.x * 1000))) * 0x9e3779b97f4a7c15ULL ^
                                     uint64_t(int64_t(std::llround(mid.z * 1000))) * 0xbf58476d1ce4e5b9ULL;
                auto mesh =
                    p.polygonFacets
                        ? cliffDetail::buildSelectedA(patch, localSeed, std::clamp(p.facets / .35f, 0.f, 1.f))
                        : cliffDetail::build(patch, localSeed, std::clamp(p.facets / .35f, 0.f, 1.f));
                out.cliffQuads += mesh.quads;
                out.cliffNgons += mesh.ngons;
                out.cliffChips += mesh.chips;
                auto &replacement = replacements[faces[first].triangle];
                for (auto t : mesh.triangles)
                    replacement.push_back(
                        {{mesh.vertices[t.a], mesh.vertices[t.b], mesh.vertices[t.c]}, true});
                for (auto index : chain) {
                    skip[faces[index].triangle] = true;
                    skip[faces[index].triangle + 1] = true;
                }
                ++out.cliffTopologyPatches;
            } catch (const std::runtime_error &) {
                // Tiny/degenerate corners keep their original faces; never risk a gap.
                ++out.cliffTopologyFallbacks;
            }
        }
        std::vector<CanyonSurfaceTriangle> detailed;
        std::vector<size_t> offsets;
        for (size_t cell = 0; cell + 1 < out.cellOffsets.size(); ++cell) {
            offsets.push_back(detailed.size());
            for (size_t i = out.cellOffsets[cell]; i < out.cellOffsets[cell + 1]; ++i) {
                if (auto it = replacements.find(i); it != replacements.end())
                    detailed.insert(detailed.end(), it->second.begin(), it->second.end());
                if (!skip[i])
                    detailed.push_back(out.triangles[i]);
            }
        }
        offsets.push_back(detailed.size());
        out.supportTriangles = std::move(out.triangles);
        out.supportOffsets = std::move(out.spatialOffsets);
        out.supportIndices = std::move(out.spatialTriangles);
        out.triangles = std::move(detailed);
        out.cellOffsets = std::move(offsets);
        indexSurface(out);
    }
    return out;
}
} // namespace dw
