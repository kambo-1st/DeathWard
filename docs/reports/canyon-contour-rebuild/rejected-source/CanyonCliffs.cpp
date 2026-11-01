#include "world/CanyonCliffs.hpp"
#include "clipper2/clipper.engine.h"
#include "earcut.hpp"
#include "world/CanyonAppearance.hpp"
#include <functional>
#include <unordered_map>

namespace dw {
namespace {
using namespace Clipper2Lib;
constexpr double Scale = 10000;
float random(int x, int z, uint64_t seed) {
    uint64_t v =
        seed ^ uint64_t(int64_t(x)) * 0x9e3779b97f4a7c15ULL ^ uint64_t(int64_t(z)) * 0xbf58476d1ce4e5b9ULL;
    v = (v ^ (v >> 30)) * 0xbf58476d1ce4e5b9ULL;
    v = (v ^ (v >> 27)) * 0x94d049bb133111ebULL;
    return float((v ^ (v >> 31)) >> 40) / 16777215.f;
}
float noise(float x, float z, uint64_t seed) {
    int a = int(std::floor(x)), b = int(std::floor(z));
    float u = x - a, v = z - b;
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    return std::lerp(std::lerp(random(a, b, seed), random(a + 1, b, seed), u),
                     std::lerp(random(a, b + 1, seed), random(a + 1, b + 1, seed), u), v);
}
Vector3 cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
Point64 point(Vector3 p) {
    return {int64_t(std::llround(p.x * Scale)), int64_t(std::llround(p.z * Scale))};
}
Vector3 vector(Point64 p) {
    return {float(p.x / Scale), 0, float(p.y / Scale)};
}
struct Edge {
    Point64 a, b;
    bool operator==(const Edge &) const = default;
};
struct EdgeHash {
    size_t operator()(const Edge &e) const {
        return size_t(e.a.x * 73856093ULL ^ e.a.y * 19349663ULL ^ e.b.x * 83492791ULL ^
                      e.b.y * 2654435761ULL);
    }
};
bool less(Point64 a, Point64 b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
struct PointHash {
    size_t operator()(const Point64 &p) const {
        return size_t(p.x * 73856093ULL ^ p.y * 19349663ULL);
    }
};
// Contours come from a scalar solid mask, then leave the source lattice entirely.
// Shared internal triangle edges cancel; the remaining directed edges form rings.
Paths64 contours(const CanyonTerrain &f, const std::vector<float> &mask) {
    std::unordered_map<Edge, Edge, EdgeHash> edges;
    auto edge = [&](Vector3 a, Vector3 b) {
        Edge directed{point(a), point(b)};
        if (directed.a == directed.b)
            return;
        Edge key = less(directed.a, directed.b) ? directed : Edge{directed.b, directed.a};
        auto it = edges.find(key);
        if (it != edges.end())
            edges.erase(it);
        else
            edges.emplace(key, directed);
    };
    struct Vertex {
        Vector3 p;
        float value;
    };
    for (int z = 0; z + 1 < f.depth; ++z)
        for (int x = 0; x + 1 < f.width; ++x) {
            auto v = [&](int dx, int dz) {
                return Vertex{f.vertex(x + dx, z + dz), mask[size_t((z + dz) * f.width + x + dx)]};
            };
            auto a = v(0, 0), b = v(1, 0), c = v(0, 1), d = v(1, 1);
            for (auto tri : {std::array<Vertex, 3>{a, d, b}, std::array<Vertex, 3>{a, c, d}}) {
                std::vector<Vector3> poly;
                auto previous = tri.back();
                for (auto current : tri) {
                    if ((previous.value > 0) != (current.value > 0))
                        poly.push_back(
                            add(previous.p, mul(sub(current.p, previous.p),
                                                previous.value / (previous.value - current.value))));
                    if (current.value > 0)
                        poly.push_back(current.p);
                    previous = current;
                }
                for (size_t i = 0; i < poly.size(); ++i)
                    edge(poly[i], poly[(i + 1) % poly.size()]);
            }
        }
    std::unordered_multimap<Point64, Point64, PointHash> next;
    for (auto &[key, e] : edges)
        next.emplace(e.a, e.b);
    Paths64 result;
    while (!next.empty()) {
        Path64 ring;
        auto first = next.begin()->first, p = first;
        for (size_t count = 0; count <= edges.size(); ++count) {
            ring.push_back(p);
            auto it = next.find(p);
            if (it == next.end())
                break;
            p = it->second;
            next.erase(it);
            if (p == first)
                break;
        }
        if (p == first && ring.size() >= 3)
            result.push_back(std::move(ring));
    }
    return result;
}
float pointLine(Point64 p, Point64 a, Point64 b) {
    auto av = vector(a), bv = vector(b), pv = vector(p);
    auto d = sub(bv, av);
    float t = std::clamp(dot(sub(pv, av), d) / std::max(.000001f, dot(d, d)), 0.f, 1.f);
    return distance(pv, add(av, mul(d, t)));
}
Path64 simplify(const Path64 &ring, float tolerance) {
    if (ring.size() < 5)
        return ring;
    size_t split = 1;
    float far = 0;
    for (size_t i = 1; i < ring.size(); ++i) {
        float d = distance(vector(ring[0]), vector(ring[i]));
        if (d > far) {
            far = d;
            split = i;
        }
    }
    std::vector<bool> keep(ring.size() + 1);
    keep[0] = keep[split] = keep[ring.size()] = true;
    std::function<void(size_t, size_t)> reduce = [&](size_t a, size_t b) {
        float most = tolerance;
        size_t at = a;
        for (size_t i = a + 1; i < b; ++i) {
            float d = pointLine(ring[i % ring.size()], ring[a % ring.size()], ring[b % ring.size()]);
            if (d > most) {
                most = d;
                at = i;
            }
        }
        if (at != a) {
            keep[at] = true;
            reduce(a, at);
            reduce(at, b);
        }
    };
    reduce(0, split);
    reduce(split, ring.size());
    Path64 result;
    for (size_t i = 0; i < ring.size(); ++i)
        if (keep[i])
            result.push_back(ring[i]);
    return result;
}
Paths64 boolean(const Paths64 &a, const Paths64 &b, ClipType operation) {
    Clipper64 clip;
    clip.PreserveCollinear(true);
    clip.AddSubject(a);
    clip.AddClip(b);
    Paths64 result;
    if (!clip.Execute(operation, FillRule::NonZero, result))
        throw std::runtime_error("Canyon contour boolean failed");
    return result;
}
std::vector<float> floorDistances(const CanyonTerrain &f, const std::vector<float> &mask) {
    std::vector<float> d(mask.size(), 10000);
    for (size_t i = 0; i < d.size(); ++i)
        if (mask[i] <= 0)
            d[i] = 0;
    auto relax = [&](int x, int z, int dx, int dz, float cost) {
        int nx = x + dx, nz = z + dz;
        if (nx >= 0 && nz >= 0 && nx < f.width && nz < f.depth) {
            size_t i = size_t(z * f.width + x);
            d[i] = std::min(d[i], d[size_t(nz * f.width + nx)] + cost * f.step);
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
} // namespace
void rebuildCanyonCliffs(CanyonAppearance &out, const CanyonTerrain &source) {
    const auto &p = out.parameters;
    const auto seed = out.seed;
    if (source.boundaryHeights.size() != source.heights.size())
        return;
    std::vector<float> canonical(source.heights.size()), primary(canonical.size()),
        patch(canonical.size(), -10000);
    for (size_t i = 0; i < canonical.size(); ++i)
        canonical[i] = std::min(source.heights[i], source.boundaryHeights[i]) - CanyonTerrain::WalkableHeight;
    auto floor = floorDistances(source, canonical);
    auto setback = [&](Vector3 v) {
        float broad = noise(v.x / 21, v.z / 21, seed ^ 0x434f4e544f5552ULL);
        float local = noise(v.x / 8, v.z / 8, seed ^ 0x53484f554c444552ULL);
        return 6.f + p.silhouette * (1.f + 4.f * broad * broad + 2.f * local);
    };
    for (int z = 0; z < source.depth; ++z)
        for (int x = 0; x < source.width; ++x) {
            size_t i = size_t(z * source.width + x);
            auto v = source.vertex(x, z);
            primary[i] = std::min(canonical[i], floor[i] - setback(v));
            // Pin the far edge so clipping remains closed on boundary-river maps.
            if (x < 2 || z < 2 || x >= source.width - 2 || z >= source.depth - 2)
                primary[i] = canonical[i];
        }
    // Seat independent chunky masses along the required floor, with coherent
    // recesses between them. The distant plateau is a separate backdrop, not
    // the one continuous face that defines every room's visible silhouette.
    auto canonicalPaths = boolean(contours(source, canonical), {}, ClipType::Union);
    for (const auto &ring : canonicalPaths) {
        float travel = 0, next = 2.f;
        for (size_t edge = 0; edge < ring.size(); ++edge) {
            auto a = vector(ring[edge]), b = vector(ring[(edge + 1) % ring.size()]);
            float length = distance(a, b);
            if (length < .001f)
                continue;
            auto tangent = mul(sub(b, a), 1 / length);
            Vector3 inward{-tangent.z, 0, tangent.x};
            while (next < travel + length) {
                auto foot = add(a, mul(tangent, next - travel));
                int hx = int(std::lround(foot.x * 7)), hz = int(std::lround(foot.z * 7));
                float choice = random(hx, hz, seed ^ 0x4d415353ULL);
                float along = 3.1f + 2.5f * random(hx, hz, seed ^ 0x41ULL);
                float deep = 2.7f + 1.1f * random(hx, hz, seed ^ 0x42ULL);
                auto center = add(foot, mul(inward, deep + .8f + 1.1f * choice));
                next += 4.8f + 4.4f * random(hx, hz, seed ^ 0x43ULL);
                if (choice < .12f)
                    continue;
                int x0 = std::max(0, int((center.x - 9 - source.x) / source.step));
                int x1 = std::min(source.width - 1, int((center.x + 9 - source.x) / source.step));
                int z0 = std::max(0, int((center.z - 9 - source.z) / source.step));
                int z1 = std::min(source.depth - 1, int((center.z + 9 - source.z) / source.step));
                for (int z = z0; z <= z1; ++z)
                    for (int x = x0; x <= x1; ++x) {
                        size_t i = size_t(z * source.width + x);
                        auto delta = sub(source.vertex(x, z), center);
                        float u = dot(delta, tangent) / along, v = dot(delta, inward) / deep;
                        float theta = std::atan2(v, u);
                        float shape = 1 + .11f * std::sin(3 * theta + choice * 6) +
                                      .06f * std::sin(5 * theta - choice * 4);
                        float mass = (shape - std::hypot(u, v)) * std::min(along, deep);
                        primary[i] =
                            std::min(canonical[i], std::max(primary[i], std::min(mass, floor[i] - .65f)));
                    }
            }
            travel += length;
        }
    }
    // Elliptical, asymmetric geological patches, not distance bands around rooms.
    // Independent sites make shelves start/end; some stretches have none at all.
    constexpr float spacing = 14;
    if (p.terraces > 1)
        for (int cz = int(std::floor(source.z / spacing));
             cz <= int((source.z + source.depth * source.step) / spacing); ++cz)
            for (int cx = int(std::floor(source.x / spacing));
                 cx <= int((source.x + source.width * source.step) / spacing); ++cx) {
                if (random(cx, cz, seed ^ 0x5041544348ULL) > .58f)
                    continue;
                float px = (cx + .15f + .7f * random(cx, cz, seed ^ 0x31ULL)) * spacing;
                float pz = (cz + .15f + .7f * random(cx, cz, seed ^ 0x32ULL)) * spacing;
                float rx = 3.2f + 4 * random(cx, cz, seed ^ 0x33ULL),
                      rz = 2.8f + 3.2f * random(cx, cz, seed ^ 0x34ULL);
                float angle = 2 * Pi * random(cx, cz, seed ^ 0x35ULL);
                int x0 = std::max(0, int((px - 10 - source.x) / source.step)),
                    x1 = std::min(source.width - 1, int((px + 10 - source.x) / source.step));
                int z0 = std::max(0, int((pz - 10 - source.z) / source.step)),
                    z1 = std::min(source.depth - 1, int((pz + 10 - source.z) / source.step));
                for (int z = z0; z <= z1; ++z)
                    for (int x = x0; x <= x1; ++x) {
                        size_t i = size_t(z * source.width + x);
                        auto v = rotateY(sub(source.vertex(x, z), {px, 0, pz}), angle);
                        float theta = std::atan2(v.z / rz, v.x / rx);
                        float radius =
                            1 + .12f * std::sin(3 * theta + angle) + .07f * std::sin(5 * theta - angle);
                        float value = (radius - std::hypot(v.x / rx, v.z / rz)) * std::min(rx, rz);
                        patch[i] = std::max(patch[i], std::min(value, primary[i] - 1.f));
                    }
            }

    auto primaryPaths = contours(source, primary), patchPaths = contours(source, patch);
    for (auto &ring : primaryPaths)
        ring = simplify(ring, .12f + .08f * p.silhouette);
    for (auto &ring : patchPaths)
        ring = simplify(ring, .18f + .12f * p.silhouette);
    primaryPaths = boolean(primaryPaths, canonicalPaths, ClipType::Intersection);
    patchPaths = boolean(patchPaths, primaryPaths, ClipType::Intersection);
    auto skirtPaths = boolean(canonicalPaths, primaryPaths, ClipType::Difference);
    auto mainPaths = boolean(primaryPaths, patchPaths, ClipType::Difference);
    // Retain the existing flat floor and every detached room obstacle verbatim.
    std::erase_if(out.triangles, [&](const CanyonSurfaceTriangle &t) {
        if (!t.rock)
            return false;
        auto v = mul(add(add(t.vertices[0], t.vertices[1]), t.vertices[2]), 1.f / 3);
        float boundary = source.height(v.x, v.z, true);
        return !(boundary <= CanyonTerrain::WalkableHeight && source.height(v.x, v.z) > boundary + .08f);
    });
    auto height = [&](Vector3 v, int level) {
        float grain = .65f * noise(v.x / 14, v.z / 14, seed ^ 0x454c4556415445ULL) +
                      .35f * noise(v.x / 31, v.z / 31, seed ^ 0x454c4556415445ULL);
        if (level == 0)
            return .62f + .16f * grain;
        float first = p.minHeight + 1.6f + p.heightVariation * (grain - .5f) * 3.f;
        return std::min(p.maxHeight,
                        first +
                            (level == 2 ? 1.2f + .8f * noise(v.x / 19, v.z / 19, seed ^ 0x52495345ULL) : 0));
    };
    auto append = [&](Vector3 a, Vector3 b, Vector3 c) {
        auto n = cross(sub(b, a), sub(c, a));
        if (dot(n, n) > 1e-10f)
            out.triangles.push_back({{a, b, c}, true});
    };
    auto caps = [&](const Paths64 &paths, int level) {
        Clipper64 clip;
        clip.AddSubject(paths);
        PolyTree64 tree;
        clip.Execute(ClipType::Union, FillRule::NonZero, tree);
        std::function<void(const PolyPath64 &)> visit = [&](const PolyPath64 &node) {
            if (!node.Polygon().empty() && !node.IsHole()) {
                using Vertex = std::array<double, 2>;
                std::vector<std::vector<Vertex>> rings;
                auto addRing = [&](const Path64 &ring) {
                    std::vector<Vertex> points;
                    for (auto q : ring)
                        points.push_back({q.x / Scale, q.y / Scale});
                    rings.push_back(std::move(points));
                };
                addRing(node.Polygon());
                for (const auto &child : node)
                    if (child->IsHole())
                        addRing(child->Polygon());
                auto indices = mapbox::earcut<uint32_t>(rings);
                std::vector<Vector3> vertices;
                for (const auto &ring : rings)
                    for (auto q : ring) {
                        Vector3 v{float(q[0]), 0, float(q[1])};
                        v.y = height(v, level);
                        vertices.push_back(v);
                    }
                // Split long cap triangles without changing their planar surfaces.
                std::function<void(Vector3, Vector3, Vector3, int)> emit = [&](Vector3 a, Vector3 b,
                                                                               Vector3 c, int depth) {
                    if (depth < 12) {
                        float ab = distance(a, b), bc = distance(b, c), ca = distance(c, a);
                        if (std::max({ab, bc, ca}) > 9) {
                            if (ab >= bc && ab >= ca) {
                                auto m = mul(add(a, b), .5f);
                                emit(a, m, c, depth + 1);
                                emit(m, b, c, depth + 1);
                            } else if (bc >= ca) {
                                auto m = mul(add(b, c), .5f);
                                emit(a, b, m, depth + 1);
                                emit(a, m, c, depth + 1);
                            } else {
                                auto m = mul(add(c, a), .5f);
                                emit(a, b, m, depth + 1);
                                emit(m, b, c, depth + 1);
                            }
                            return;
                        }
                    }
                    if (cross(sub(b, a), sub(c, a)).y < 0)
                        std::swap(b, c);
                    append(a, b, c);
                };
                for (size_t i = 0; i < indices.size(); i += 3)
                    emit(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]], 0);
            }
            for (const auto &child : node)
                visit(*child);
        };
        visit(tree);
    };
    caps(skirtPaths, 0);
    caps(mainPaths, 1);
    caps(patchPaths, 2);
    auto walls = [&](const Paths64 &paths, int low, int high) {
        for (const auto &ring : paths)
            for (size_t i = 0; i < ring.size(); ++i) {
                Vector3 a = vector(ring[i]), b = vector(ring[(i + 1) % ring.size()]);
                auto outwardAt = [&](size_t vertex) {
                    auto previous = vector(ring[(vertex + ring.size() - 1) % ring.size()]);
                    auto current = vector(ring[vertex]), next = vector(ring[(vertex + 1) % ring.size()]);
                    auto before = unit(sub(current, previous)), after = unit(sub(next, current));
                    return unit(Vector3{before.z + after.z, 0, -before.x - after.x});
                };
                auto at = a, bt = b, am = a, bm = b;
                float ah = height(a, high), bh = height(b, high);
                a.y = low < 0 ? CanyonTerrain::WalkableHeight : height(a, low);
                b.y = low < 0 ? CanyonTerrain::WalkableHeight : height(b, low);
                at.y = ah;
                bt.y = bh;
                auto middle = [&](Vector3 v, float bottom, float top, Vector3 outward) {
                    // Coherent buttresses with staggered facet junctions. Widths
                    // follow contour corners rather than uniform lattice columns.
                    float t = .28f + .44f * noise(v.x / 5, v.z / 5, seed ^ 0x4641434554ULL);
                    float relief =
                        high == 0 ? 0
                                  : .25f * (2 * noise(v.x / 5, v.z / 5, seed ^ 0x4255545452455353ULL) - 1);
                    v = add(v, mul(outward, relief));
                    v.y = std::lerp(bottom, top, t);
                    return v;
                };
                am = middle(am, a.y, ah, outwardAt(i));
                bm = middle(bm, b.y, bh, outwardAt((i + 1) % ring.size()));
                append(a, am, bm);
                append(a, bm, b);
                append(am, at, bt);
                append(am, bt, bm);
            }
    };
    walls(canonicalPaths, -1, 0);
    walls(primaryPaths, 0, 1);
    walls(patchPaths, 1, 2);
    // Keep the renderer's owner-cell order; spatial queries independently bin
    // the true triangle bounds, including broad contour faces crossing cells.
    const int columns = source.width - 1, rows = source.depth - 1;
    auto owner = [&](const CanyonSurfaceTriangle &t) {
        auto v = mul(add(add(t.vertices[0], t.vertices[1]), t.vertices[2]), 1.f / 3);
        int x = std::clamp(int((v.x - source.x) / source.step), 0, columns - 1),
            z = std::clamp(int((v.z - source.z) / source.step), 0, rows - 1);
        return size_t(z * columns + x);
    };
    std::stable_sort(out.triangles.begin(), out.triangles.end(),
                     [&](const auto &a, const auto &b) { return owner(a) < owner(b); });
    out.cellOffsets.assign(size_t(columns * rows) + 1, 0);
    for (const auto &t : out.triangles)
        ++out.cellOffsets[owner(t) + 1];
    for (size_t i = 1; i < out.cellOffsets.size(); ++i)
        out.cellOffsets[i] += out.cellOffsets[i - 1];
}
} // namespace dw
