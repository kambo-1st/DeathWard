#include "world/CanyonFormations.hpp"
#include "clipper2/clipper.engine.h"
#include "clipper2/clipper.offset.h"
#include "earcut.hpp"
#include "world/CanyonAppearance.hpp"
#include <map>
#include <set>
#include <unordered_map>
namespace dw {
namespace {
using namespace Clipper2Lib;
constexpr double Scale = 10000;
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
                    if ((previous.value > 0) != (current.value > 0)) {
                        auto a = previous, b = current;
                        if (a.p.x > b.p.x || (a.p.x == b.p.x && a.p.z > b.p.z))
                            std::swap(a, b);
                        poly.push_back(add(a.p, mul(sub(b.p, a.p), a.value / (a.value - b.value))));
                    }
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
struct Contact {
    Vector3 a, b;
    std::vector<Vector3> foot;
    std::vector<float> arc;
    Vector3 sample(float t) const {
        t = std::clamp(t, 0.f, 1.f);
        auto it = std::upper_bound(arc.begin(), arc.end(), t);
        size_t i = it == arc.begin() ? 0 : std::min(size_t(it - arc.begin() - 1), arc.size() - 2);
        float u = (t - arc[i]) / std::max(.000001f, arc[i + 1] - arc[i]);
        auto v = add(foot[i], mul(sub(foot[i + 1], foot[i]), u));
        v.y = CanyonTerrain::WalkableHeight;
        return v;
    }
};
float projection(Vector3 p, Vector3 a, Vector3 b) {
    auto d = sub(b, a);
    return dot(sub(p, a), d) / std::max(.000001f, dot(d, d));
}
float lineDistance(Vector3 p, Vector3 a, Vector3 b) {
    return distance(p, add(a, mul(sub(b, a), std::clamp(projection(p, a, b), 0.f, 1.f))));
}
// Split coincident nested contours at the same vertices. This is only an
// edge-conformity operation: risers belong to their elevation boundary, so
// millimetre Boolean fragments never determine a wall's height or ownership.
void nodeLevels(std::vector<Paths64> &levels, const std::vector<Point64> &contacts) {
    std::map<std::pair<int64_t, int64_t>, Point64> points;
    for (auto q : contacts)
        points[{q.x, q.y}] = q;
    for (const auto &paths : levels)
        for (const auto &ring : paths)
            for (auto q : ring)
                points[{q.x, q.y}] = q;
    constexpr int64_t Bin = 80000; // Eight metres in polygon coordinates.
    auto bin = [](int64_t v) { return v >= 0 ? v / Bin : (v - Bin + 1) / Bin; };
    std::map<std::pair<int64_t, int64_t>, std::vector<Point64>> bins;
    for (const auto &[key, q] : points)
        bins[{bin(q.x), bin(q.y)}].push_back(q);
    for (auto &paths : levels)
        for (auto &ring : paths) {
            Path64 result;
            for (size_t i = 0; i < ring.size(); ++i) {
                auto a = vector(ring[i]), b = vector(ring[(i + 1) % ring.size()]);
                result.push_back(ring[i]);
                std::vector<std::pair<float, Point64>> extra;
                auto lowX = std::min(ring[i].x, ring[(i + 1) % ring.size()].x) - 3,
                     highX = std::max(ring[i].x, ring[(i + 1) % ring.size()].x) + 3;
                auto lowZ = std::min(ring[i].y, ring[(i + 1) % ring.size()].y) - 3,
                     highZ = std::max(ring[i].y, ring[(i + 1) % ring.size()].y) + 3;
                for (auto z = bin(lowZ); z <= bin(highZ); ++z)
                    for (auto x = bin(lowX); x <= bin(highX); ++x) {
                        auto it = bins.find({x, z});
                        if (it == bins.end())
                            continue;
                        for (auto q : it->second) {
                            if (q.x < lowX || q.x > highX || q.y < lowZ || q.y > highZ)
                                continue;
                            auto v = vector(q);
                            float t = projection(v, a, b);
                            if (t > .000001f && t < .999999f && lineDistance(v, a, b) < .0002f)
                                extra.push_back({t, q});
                        }
                    }
                std::sort(extra.begin(), extra.end(), [](const auto &a, const auto &b) {
                    return a.first != b.first ? a.first < b.first : less(a.second, b.second);
                });
                for (const auto &[t, q] : extra)
                    if (result.back() != q)
                        result.push_back(q);
            }
            ring = std::move(result);
        }
}
} // namespace
void rebuildCanyonFormations(CanyonAppearance &out, const CanyonTerrain &source,
                             const std::vector<CanyonWallSpan> &oldSpans,
                             const std::function<float(Vector3, int)> &rawHeight,
                             const std::function<float(Vector3, int)> &formation) {
    const auto &p = out.parameters;
    // A shared coarse planar height field lets every cap and wall evaluate the
    // same surface, including collinear vertices omitted by triangulation.
    constexpr float Grid = 8;
    int gx0 = int(std::floor(source.x / Grid)) - 1, gz0 = int(std::floor(source.z / Grid)) - 1;
    int gx1 = int(std::ceil((source.x + (source.width - 1) * source.step) / Grid)) + 1;
    int gz1 = int(std::ceil((source.z + (source.depth - 1) * source.step) / Grid)) + 1;
    int width = gx1 - gx0 + 1, depth = gz1 - gz0 + 1;
    std::vector<float> heights(size_t(width * depth * (p.terraces + 1)));
    auto index = [&](int x, int z, int k) { return size_t((k * depth + z - gz0) * width + x - gx0); };
    for (int k = 0; k <= p.terraces; ++k)
        for (int z = gz0; z <= gz1; ++z)
            for (int x = gx0; x <= gx1; ++x)
                heights[index(x, z, k)] = rawHeight({x * Grid, 0, z * Grid}, k);
    auto height = [&](Vector3 v, int k) {
        int x = int(std::floor(v.x / Grid)), z = int(std::floor(v.z / Grid));
        float u = v.x / Grid - x, w = v.z / Grid - z;
        float a = heights[index(x, z, k)], b = heights[index(x + 1, z, k)], c = heights[index(x, z + 1, k)],
              d = heights[index(x + 1, z + 1, k)];
        return u >= w ? a + u * (b - a) + w * (d - b) : a + w * (c - a) + u * (d - c);
    };
    std::vector<float> mask(source.heights.size());
    for (size_t i = 0; i < mask.size(); ++i)
        mask[i] = source.boundaryHeights[i] - CanyonTerrain::WalkableHeight;
    auto original = boolean(contours(source, mask), {}, ClipType::Union);
    Paths64 base;
    std::vector<Contact> contacts;
    std::vector<Point64> contactNodes;
    for (const auto &ring : original) {
        auto top = simplify(ring, .08f + .18f * p.silhouette);
        if (top.size() < 3)
            top = ring;
        base.push_back(top);
        for (size_t i = 0; i < top.size(); ++i) {
            auto a = top[i], b = top[(i + 1) % top.size()];
            contactNodes.push_back(a);
            auto it = std::find(ring.begin(), ring.end(), a);
            if (it == ring.end())
                throw std::runtime_error("Canyon simplification lost its contact vertex");
            size_t index = size_t(it - ring.begin());
            Contact edge{vector(a), vector(b), {}, {0}};
            for (size_t count = 0; count <= ring.size(); ++count) {
                auto at = ring[(index + count) % ring.size()];
                edge.foot.push_back(vector(at));
                if (at == b)
                    break;
            }
            for (size_t k = 1; k < edge.foot.size(); ++k)
                edge.arc.push_back(edge.arc.back() + distance(edge.foot[k - 1], edge.foot[k]));
            if (edge.foot.size() < 2 || edge.arc.back() < .00001f)
                continue;
            float length = edge.arc.back();
            for (auto &t : edge.arc)
                t /= length;
            contacts.push_back(std::move(edge));
        }
    }
    base = boolean(base, {}, ClipType::Union);
    std::vector<Paths64> levels{base};
    for (int k = 0; k < p.terraces; ++k) {
        for (int z = 0; z < source.depth; ++z)
            for (int x = 0; x < source.width; ++x) {
                auto v = source.vertex(x, z);
                mask[size_t(z * source.width + x)] = formation(v, k);
            }
        auto patches = contours(source, mask);
        for (auto &ring : patches) {
            auto reduced = simplify(ring, .12f + .16f * p.silhouette);
            if (reduced.size() >= 3)
                ring = std::move(reduced);
        }
        auto region = boolean(patches, levels.back(), ClipType::Intersection);
        // Remove narrow raised tongues after clipping to the canyon. These
        // otherwise become tall blades at the ends of local terrace patches.
        const float radius = std::clamp(p.terraceWidth * .55f, .4f, 1.5f);
        auto offset = [&](const Paths64 &input, float delta) {
            ClipperOffset worker(2, .18 * Scale, true);
            worker.AddPaths(input, JoinType::Round, EndType::Polygon);
            Paths64 result;
            worker.Execute(delta * Scale, result);
            if (worker.ErrorCode())
                throw std::runtime_error("Canyon terrace opening failed");
            return result;
        };
        auto core = offset(region, -radius);
        auto opened = offset(core, radius);
        levels.push_back(boolean(opened, region, ClipType::Intersection));
    }
    std::vector<Paths64> regions;
    for (size_t k = 0; k < levels.size(); ++k)
        regions.push_back(k + 1 == levels.size() ? levels[k]
                                                 : boolean(levels[k], levels[k + 1], ClipType::Difference));
    nodeLevels(levels, contactNodes);
    auto detached = [&](Vector3 v) {
        return source.height(v.x, v.z) > source.height(v.x, v.z, true) + .025f;
    };
    std::erase_if(out.triangles, [&](const auto &t) {
        return t.rock && !detached(mul(add(add(t.vertices[0], t.vertices[1]), t.vertices[2]), 1.f / 3));
    });
    std::vector<CanyonWallSpan> walls;
    for (const auto &s : oldSpans)
        if (detached(mul(add(s.bottomA, s.bottomB), .5f))) {
            for (auto t : {std::array<Vector3, 3>{s.bottomA, s.topB, s.topA},
                           std::array<Vector3, 3>{s.bottomA, s.bottomB, s.topB}}) {
                auto n = cross(sub(t[1], t[0]), sub(t[2], t[0]));
                if (dot(n, n) > 1e-10f)
                    out.triangles.push_back({t, true});
            }
        }
    auto append = [&](Vector3 a, Vector3 b, Vector3 c) {
        auto n = cross(sub(b, a), sub(c, a));
        if (dot(n, n) < 1e-10f)
            return;
        if (n.y < 0)
            std::swap(b, c);
        out.triangles.push_back({{a, b, c}, true});
    };
    // First triangulate the polygon with holes. Then clip each triangle onto
    // the shared coarse planes. Tops are broad geological facets rather than
    // source-grid columns, and all boundary T-junctions are coplanar in 3D.
    auto clipFace = [](const std::vector<Vector3> &poly, auto value) {
        std::vector<Vector3> result;
        if (poly.empty())
            return result;
        auto a = poly.back();
        float av = value(a);
        for (auto b : poly) {
            float bv = value(b);
            if ((av >= 0) != (bv >= 0))
                result.push_back(add(a, mul(sub(b, a), av / (av - bv))));
            if (bv >= 0)
                result.push_back(b);
            a = b;
            av = bv;
        }
        return result;
    };
    auto cap = [&](const Paths64 &paths, int level) {
        Clipper64 clip;
        clip.PreserveCollinear(true);
        clip.AddSubject(paths);
        PolyTree64 tree;
        clip.Execute(ClipType::Union, FillRule::NonZero, tree);
        std::function<void(const PolyPath64 &)> visit = [&](const PolyPath64 &node) {
            if (!node.Polygon().empty() && !node.IsHole()) {
                using V = std::array<double, 2>;
                std::vector<std::vector<V>> rings;
                auto addRing = [&](const Path64 &ring) {
                    std::vector<V> r;
                    for (auto q : ring)
                        r.push_back({q.x / Scale, q.y / Scale});
                    rings.push_back(std::move(r));
                };
                addRing(node.Polygon());
                for (const auto &child : node)
                    if (child->IsHole())
                        addRing(child->Polygon());
                auto indices = mapbox::earcut<uint32_t>(rings);
                std::vector<Vector3> vertices;
                for (const auto &r : rings)
                    for (auto q : r)
                        vertices.push_back({float(q[0]), 0, float(q[1])});
                for (size_t i = 0; i < indices.size(); i += 3) {
                    std::vector<Vector3> tri{vertices[indices[i]], vertices[indices[i + 1]],
                                             vertices[indices[i + 2]]};
                    int x0 = int(std::floor(std::min({tri[0].x, tri[1].x, tri[2].x}) / Grid));
                    int x1 = int(std::floor(std::max({tri[0].x, tri[1].x, tri[2].x}) / Grid));
                    int z0 = int(std::floor(std::min({tri[0].z, tri[1].z, tri[2].z}) / Grid));
                    int z1 = int(std::floor(std::max({tri[0].z, tri[1].z, tri[2].z}) / Grid));
                    for (int z = z0; z <= z1; ++z)
                        for (int x = x0; x <= x1; ++x) {
                            auto poly = clipFace(tri, [&](Vector3 v) { return v.x - x * Grid; });
                            poly = clipFace(poly, [&](Vector3 v) { return (x + 1) * Grid - v.x; });
                            poly = clipFace(poly, [&](Vector3 v) { return v.z - z * Grid; });
                            poly = clipFace(poly, [&](Vector3 v) { return (z + 1) * Grid - v.z; });
                            if (poly.size() < 3)
                                continue;
                            for (int side : {-1, 1}) {
                                auto face = clipFace(
                                    poly, [&](Vector3 v) { return side * (v.x - v.z - (x - z) * Grid); });
                                for (auto &v : face)
                                    v.y = height(v, level);
                                for (size_t j = 1; j + 1 < face.size(); ++j)
                                    append(face[0], face[j], face[j + 1]);
                            }
                        }
                }
            }
            for (const auto &child : node)
                visit(*child);
        };
        visit(tree);
    };
    auto emitWall = [&](int k, int lower, Vector3 a, Vector3 b) {
        auto edge = sub(b, a);
        float length = std::sqrt(dot(edge, edge));
        if (length < .0001f)
            return;
        auto topA = a, topB = b;
        topA.y = height(a, k);
        topB.y = height(b, k);
        if (lower >= 0) {
            auto loA = a, loB = b;
            loA.y = height(a, lower);
            loB.y = height(b, lower);
            if (std::max(topA.y - loA.y, topB.y - loB.y) > .001f)
                walls.push_back({loB, loA, topB, topA, k});
            return;
        }
        const Contact *contact = nullptr;
        float error = .01f;
        for (const auto &c : contacts) {
            float d = std::max(lineDistance(a, c.a, c.b), lineDistance(b, c.a, c.b));
            if (d < error) {
                error = d;
                contact = &c;
            }
        }
        if (!contact)
            throw std::runtime_error("Canyon outer wall has no canonical floor contact: " +
                                     std::to_string(a.x) + "," + std::to_string(a.z));
        float first = std::clamp(projection(a, contact->a, contact->b), 0.f, 1.f),
              last = std::clamp(projection(b, contact->a, contact->b), 0.f, 1.f);
        if (std::abs(first - last) < .000001f)
            return;
        std::vector<float> points{first, last};
        for (float t : contact->arc)
            if (t > std::min(first, last) + .000001f && t < std::max(first, last) - .000001f)
                points.push_back(t);
        std::sort(points.begin(), points.end());
        if (first > last)
            std::reverse(points.begin(), points.end());
        auto top = [&](float t) { return add(topA, mul(sub(topB, topA), (t - first) / (last - first))); };
        for (size_t j = 1; j < points.size(); ++j) {
            auto loA = contact->sample(points[j - 1]), loB = contact->sample(points[j]);
            walls.push_back({loB, loA, top(points[j]), top(points[j - 1]), k});
        }
    };
    for (size_t k = 0; k < regions.size(); ++k)
        cap(regions[k], int(k));
    for (size_t k = 0; k < levels.size(); ++k)
        for (const auto &ring : levels[k])
            for (size_t i = 0; i < ring.size(); ++i) {
                auto a = vector(ring[i]), b = vector(ring[(i + 1) % ring.size()]);
                std::vector<float> cuts{0, 1};
                for (auto values :
                     {std::pair{a.x, b.x}, std::pair{a.z, b.z}, std::pair{a.x - a.z, b.x - b.z}}) {
                    if (std::abs(values.second - values.first) < .00001f)
                        continue;
                    int first = int(std::floor(std::min(values.first, values.second) / Grid)) + 1;
                    int last = int(std::ceil(std::max(values.first, values.second) / Grid));
                    for (int line = first; line < last; ++line) {
                        float t = (line * Grid - values.first) / (values.second - values.first);
                        if (t > 0 && t < 1)
                            cuts.push_back(t);
                    }
                }
                std::sort(cuts.begin(), cuts.end());
                cuts.erase(std::unique(cuts.begin(), cuts.end(),
                                       [](float a, float b) { return std::abs(a - b) < .000001f; }),
                           cuts.end());
                for (size_t j = 1; j < cuts.size(); ++j)
                    emitWall(int(k), int(k) - 1, add(a, mul(sub(b, a), cuts[j - 1])),
                             add(a, mul(sub(b, a), cuts[j])));
            }
    appendCanyonFacets(out, walls);
}
} // namespace dw
