#include "world/CanyonFacets.hpp"
#include "world/CanyonAppearance.hpp"
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <unordered_map>
namespace dw {
namespace {
struct Endpoint {
    std::array<int32_t, 6> v;
    bool operator==(const Endpoint &) const = default;
};
struct Hash {
    size_t operator()(const Endpoint &p) const {
        uint64_t h = 1469598103934665603ULL;
        for (auto v : p.v)
            h = (h ^ uint32_t(v)) * 1099511628211ULL;
        return size_t(h);
    }
};
Endpoint key(Vector3 a, Vector3 b) {
    return {{{int32_t(std::lround(a.x * 1000)), int32_t(std::lround(a.y * 1000)),
              int32_t(std::lround(a.z * 1000)), int32_t(std::lround(b.x * 1000)),
              int32_t(std::lround(b.y * 1000)), int32_t(std::lround(b.z * 1000))}}};
}
Vector3 cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
float length2(Vector3 a, Vector3 b) {
    return std::hypot(a.x - b.x, a.z - b.z);
}
float wave(Vector3 p, int row, uint64_t seed) {
    float phase = float(seed % 1009) * .017f + row * 1.93f;
    return .65f * std::sin(p.x * .43f + p.z * .29f + phase) +
           .35f * std::sin(p.x * .19f - p.z * .37f - phase);
}
struct WallPoint {
    double u = 0, v = 0;
    Vector3 base{}, p{};
    bool movable = false, boundary = false;
};
using Face = std::array<size_t, 3>;
double orientation(const WallPoint &a, const WallPoint &b, const WallPoint &c) {
    return (b.u - a.u) * (c.v - a.v) - (b.v - a.v) * (c.u - a.u);
}
std::vector<Face> triangulateWall(std::vector<WallPoint> points) {
    const size_t count = points.size();
    double scale = 1;
    for (const auto &p : points)
        scale = std::max({scale, p.u, p.v});
    points.push_back({-4 * scale, -scale});
    points.push_back({4 * scale, -scale});
    points.push_back({0, 4 * scale});
    std::vector<Face> faces{{count, count + 1, count + 2}};
    for (size_t i = 0; i < count; ++i) {
        std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> edges;
        std::vector<Face> keep;
        for (auto f : faces) {
            const auto &p = points[i], &a = points[f[0]], &b = points[f[1]], &c = points[f[2]];
            double ax = a.u - p.u, ay = a.v - p.v, bx = b.u - p.u, by = b.v - p.v, cx = c.u - p.u,
                   cy = c.v - p.v;
            double det = (ax * ax + ay * ay) * (bx * cy - by * cx) -
                         (bx * bx + by * by) * (ax * cy - ay * cx) +
                         (cx * cx + cy * cy) * (ax * by - ay * bx);
            if (det <= 1e-10) {
                keep.push_back(f);
                continue;
            }
            for (int k = 0; k < 3; ++k) {
                size_t a = f[k], b = f[(k + 1) % 3];
                auto key = std::minmax(a, b);
                auto it = edges.find(key);
                if (it == edges.end())
                    edges[key] = {a, b};
                else
                    edges.erase(it);
            }
        }
        for (const auto &[key, edge] : edges) {
            Face f{edge.first, edge.second, i};
            double turn = orientation(points[f[0]], points[f[1]], points[f[2]]);
            if (std::abs(turn) < 1e-10)
                continue;
            if (turn < 0)
                std::swap(f[0], f[1]);
            keep.push_back(f);
        }
        faces = std::move(keep);
    }
    std::erase_if(faces, [&](auto f) { return f[0] >= count || f[1] >= count || f[2] >= count; });
    // Keep every exact contact/cap vertex, including collinear hull points.
    for (size_t p = 0; p < count; ++p)
        if (points[p].boundary) {
            size_t existing = faces.size();
            for (size_t i = 0; i < existing; ++i)
                for (int k = 0; k < 3; ++k) {
                    auto f = faces[i];
                    size_t a = f[k], b = f[(k + 1) % 3], c = f[(k + 2) % 3];
                    if (p == a || p == b)
                        continue;
                    double du = points[b].u - points[a].u, dv = points[b].v - points[a].v;
                    double length = du * du + dv * dv;
                    if (length < 1e-12)
                        continue;
                    double t = ((points[p].u - points[a].u) * du + (points[p].v - points[a].v) * dv) / length;
                    if (t <= 1e-8 || t >= 1 - 1e-8 ||
                        std::abs(orientation(points[a], points[b], points[p])) > 1e-7)
                        continue;
                    faces[i] = {a, p, c};
                    faces.push_back({p, b, c});
                    break;
                }
        }
    return faces;
}
bool appendWallCloud(CanyonAppearance &look, const std::vector<Vector3> &lower,
                     const std::vector<Vector3> &upper, const std::vector<float> &arc, bool closed,
                     int tier) {
    float total = arc.back(), height = 0;
    for (size_t i = 0; i < lower.size(); ++i)
        height += std::max(.03f, upper[i].y - lower[i].y);
    height /= float(lower.size());
    auto sample = [&](const std::vector<Vector3> &curve, float u) {
        if (u <= 0)
            return curve.front();
        if (u >= total)
            return curve.back();
        auto it = std::upper_bound(arc.begin(), arc.end(), u);
        size_t i = std::min(size_t(it - arc.begin() - 1), arc.size() - 2);
        return add(curve[i],
                   mul(sub(curve[i + 1], curve[i]), (u - arc[i]) / std::max(.000001f, arc[i + 1] - arc[i])));
    };
    std::vector<WallPoint> points;
    std::map<std::pair<int64_t, int64_t>, size_t> unique;
    auto addPoint = [&](float u, float fraction, bool boundary, Vector3 exact, bool movable) {
        double v = double(fraction) * height;
        auto key = std::pair{int64_t(std::llround(u * 1e6)), int64_t(std::llround(v * 1e6))};
        if (auto it = unique.find(key); it != unique.end())
            return it->second;
        auto lo = sample(lower, u), hi = sample(upper, u);
        auto base = boundary ? exact : add(lo, mul(sub(hi, lo), fraction));
        auto p = base;
        if (movable) {
            auto before = sample(upper, std::max(0.f, u - .6f)),
                 after = sample(upper, std::min(total, u + .6f));
            if (closed && u < .6f)
                before = sample(upper, total - .6f);
            if (closed && u > total - .6f)
                after = sample(upper, .6f);
            auto tangent = unit(sub(after, before));
            Vector3 inward{tangent.z, 0, -tangent.x};
            float phase = float(look.seed % 1009) * .017f + tier * 1.7f;
            float variation = .6f * std::sin(base.x * .8f + base.z * .43f + fraction * 7 + phase) +
                              .4f * std::sin(base.x * .33f - base.z * .71f - fraction * 4 - phase);
            float edge = closed ? 1.f : std::clamp(std::min(u, total - u) / 1.5f, 0.f, 1.f);
            auto candidate = add(p, mul(inward, .4f * variation * std::sin(Pi * fraction) * edge *
                                                    look.parameters.facets / .35f));
            if (look.surface.height(candidate.x, candidate.z) > CanyonTerrain::WalkableHeight - .015f)
                p = candidate;
        }
        size_t id = points.size();
        unique[key] = id;
        points.push_back({u, v, base, p, movable, boundary});
        return id;
    };
    for (size_t i = 0; i < lower.size(); ++i) {
        addPoint(arc[i], 0, true, lower[i], false);
        addPoint(arc[i], 1, true, upper[i], false);
    }
    std::vector<std::pair<size_t, size_t>> seam;
    for (float f : {.33f, .67f}) {
        auto a = add(sample(lower, 0), mul(sub(sample(upper, 0), sample(lower, 0)), f));
        auto b = add(sample(lower, total), mul(sub(sample(upper, total), sample(lower, total)), f));
        seam.push_back({addPoint(0, f, true, a, closed), addPoint(total, f, true, b, closed)});
    }
    for (float u = .8f; u < total - .4f;) {
        auto center = mul(add(sample(lower, u), sample(upper, u)), .5f);
        bool pair = height > 3.2f || wave(center, tier * 7 + 5, look.seed) > .15f;
        if (pair) {
            addPoint(u, .24f + .10f * wave(center, tier * 7 + 1, look.seed), false, {}, true);
            float other = std::clamp(u + .4f * wave(center, tier * 7 + 2, look.seed), .2f, total - .2f);
            addPoint(other, .72f + .10f * wave(center, tier * 7 + 3, look.seed), false, {}, true);
        } else
            addPoint(u, .5f + .23f * wave(center, tier * 7 + 4, look.seed), false, {}, true);
        u += std::max(1.5f, 2.5f + .7f * wave(center, tier * 7 + 8, look.seed));
    }
    // Extra points are local to sharp contour bends, not full horizontal rows.
    for (size_t i = 1; i + 1 < arc.size(); ++i) {
        auto a = unit(sub(upper[i], upper[i - 1])), b = unit(sub(upper[i + 1], upper[i]));
        if (dot(a, b) < .75f)
            for (float f : {.25f, .6f})
                addPoint(arc[i], f, false, {}, true);
    }
    auto faces = triangulateWall(points);
    bool valid = !faces.empty();
    for (int attempt = 0; attempt < 14 && valid; ++attempt) {
        std::set<size_t> bad;
        bool fixedFailure = false;
        for (auto f : faces) {
            auto n = cross(sub(points[f[1]].p, points[f[0]].p), sub(points[f[2]].p, points[f[0]].p));
            float u = float((points[f[0]].u + points[f[1]].u + points[f[2]].u) / 3);
            auto tangent =
                sub(sample(upper, std::min(total, u + .1f)), sample(upper, std::max(0.f, u - .1f)));
            tangent.y = 0;
            tangent = unit(tangent);
            Vector3 outward{-tangent.z, 0, tangent.x};
            float magnitude = std::sqrt(dot(n, n));
            if (std::abs(n.y) <= .35f * magnitude && dot(n, outward) >= -.001f * magnitude)
                continue;
            bool adjustable = false;
            for (auto i : f)
                if (points[i].movable) {
                    bad.insert(i);
                    adjustable = true;
                }
            fixedFailure |= !adjustable;
        }
        if (bad.empty() && !fixedFailure)
            break;
        if (fixedFailure || attempt == 13) {
            valid = false;
            break;
        }
        if (closed)
            for (auto [a, b] : seam)
                if (bad.contains(a) || bad.contains(b)) {
                    bad.insert(a);
                    bad.insert(b);
                }
        for (auto i : bad)
            points[i].p = attempt >= 10 ? points[i].base : mul(add(points[i].p, points[i].base), .5f);
        if (closed)
            for (auto [a, b] : seam)
                points[b].p = points[a].p;
    }
    auto emit = [&](Vector3 a, Vector3 b, Vector3 c) {
        auto n = cross(sub(b, a), sub(c, a));
        if (dot(n, n) > 1e-10f)
            look.triangles.push_back({{a, b, c}, true});
    };
    if (valid)
        for (auto f : faces)
            emit(points[f[0]].p, points[f[1]].p, points[f[2]].p);
    else
        for (size_t i = 1; i < lower.size(); ++i) {
            emit(lower[i - 1], upper[i], upper[i - 1]);
            emit(lower[i - 1], lower[i], upper[i]);
        }
    return valid;
}
struct VertexCell {
    std::array<int32_t, 3> v;
    bool operator==(const VertexCell &) const = default;
};
struct VertexHash {
    size_t operator()(const VertexCell &p) const {
        return size_t(uint64_t(uint32_t(p.v[0])) * 73856093ULL ^ uint64_t(uint32_t(p.v[1])) * 19349663ULL ^
                      uint64_t(uint32_t(p.v[2])) * 83492791ULL);
    }
};
void weldContacts(CanyonAppearance &look) {
    std::unordered_map<VertexCell, std::vector<Vector3>, VertexHash> bins;
    auto cell = [](Vector3 v) {
        return VertexCell{{int32_t(std::lround(v.x * 1000)), int32_t(std::lround(v.y * 1000)),
                           int32_t(std::lround(v.z * 1000))}};
    };
    // Ground vertices have priority and never move. Rock edges then snap only
    // within 0.3mm, removing cracks from independent clipping arithmetic.
    for (const auto &t : look.triangles)
        if (!t.rock)
            for (auto v : t.vertices) {
                auto &list = bins[cell(v)];
                if (std::none_of(list.begin(), list.end(), [&](auto p) { return distance(p, v) < 1e-8f; }))
                    list.push_back(v);
            }
    for (auto &t : look.triangles)
        if (t.rock) {
            auto before = cross(sub(t.vertices[1], t.vertices[0]), sub(t.vertices[2], t.vertices[0]));
            for (auto &v : t.vertices) {
                auto key = cell(v);
                Vector3 nearest = v;
                float best = .0003f;
                for (int z = -1; z <= 1; ++z)
                    for (int y = -1; y <= 1; ++y)
                        for (int x = -1; x <= 1; ++x) {
                            VertexCell neighbor{{key.v[0] + x, key.v[1] + y, key.v[2] + z}};
                            auto it = bins.find(neighbor);
                            if (it == bins.end())
                                continue;
                            for (auto p : it->second) {
                                float d = distance(p, v);
                                if (d < best) {
                                    best = d;
                                    nearest = p;
                                }
                            }
                        }
                if (best < .0003f)
                    v = nearest;
                else
                    bins[key].push_back(v);
            }
            auto after = cross(sub(t.vertices[1], t.vertices[0]), sub(t.vertices[2], t.vertices[0]));
            if (dot(before, after) < 0)
                std::swap(t.vertices[1], t.vertices[2]);
        }
    std::erase_if(look.triangles, [](const auto &t) {
        auto n = cross(sub(t.vertices[1], t.vertices[0]), sub(t.vertices[2], t.vertices[0]));
        return t.rock && dot(n, n) < 1e-10f;
    });
}
} // namespace
void appendCanyonFacets(CanyonAppearance &look, const std::vector<CanyonWallSpan> &input) {
    auto spans = input;
    size_t chains = 0, fallback = 0, shortChains = 0, largest = 0;
    std::unordered_multimap<Endpoint, size_t, Hash> bottoms;
    for (size_t i = 0; i < spans.size(); ++i)
        bottoms.emplace(key(spans[i].bottomA, spans[i].bottomB), i);
    std::vector<bool> merged(spans.size());
    // Adjacent height fields can share the same outer contour. Join their
    // risers before retopology, so no artificial horizontal seam crosses a tall face.
    for (size_t i = 0; i < spans.size(); ++i) {
        if (merged[i])
            continue;
        int highestTier = spans[i].tier;
        while (true) {
            auto range = bottoms.equal_range(key(spans[i].topA, spans[i].topB));
            size_t found = spans.size();
            for (auto it = range.first; it != range.second; ++it) {
                size_t j = it->second;
                if (j != i && !merged[j] && spans[j].tier == highestTier + 1)
                    found = std::min(found, j);
            }
            if (found == spans.size())
                break;
            spans[i].topA = spans[found].topA;
            spans[i].topB = spans[found].topB;
            merged[found] = true;
            ++highestTier;
        }
    }
    std::vector<CanyonWallSpan> joined;
    for (size_t i = 0; i < spans.size(); ++i)
        if (!merged[i])
            joined.push_back(spans[i]);
    spans = std::move(joined);
    std::unordered_multimap<Endpoint, size_t, Hash> next, previous;
    for (size_t i = 0; i < spans.size(); ++i) {
        next.emplace(key(spans[i].bottomA, spans[i].topA), i);
        previous.emplace(key(spans[i].bottomB, spans[i].topB), i);
    }
    std::vector<bool> used(spans.size());
    for (size_t candidate = 0; candidate < spans.size(); ++candidate) {
        if (used[candidate])
            continue;
        // Begin at the head of an open contour, rather than wherever a source
        // triangle happened to be emitted. Otherwise reverse-ordered input turns
        // one long face into hundreds of one-edge chains.
        size_t start = candidate;
        std::set<size_t> backtrack{start};
        for (size_t count = 0; count < spans.size(); ++count) {
            auto range = previous.equal_range(key(spans[start].bottomA, spans[start].topA));
            size_t found = spans.size();
            for (auto it = range.first; it != range.second; ++it)
                if (!used[it->second] && spans[it->second].tier == spans[start].tier)
                    found = std::min(found, it->second);
            if (found == spans.size() || !backtrack.insert(found).second)
                break;
            start = found;
        }
        std::vector<Vector3> lower, upper;
        size_t at = start;
        bool closed = false;
        for (size_t count = 0; count <= spans.size(); ++count) {
            if (used[at])
                break;
            used[at] = true;
            const auto &s = spans[at];
            lower.push_back(s.bottomA);
            upper.push_back(s.topA);
            auto end = key(s.bottomB, s.topB);
            if (end == key(spans[start].bottomA, spans[start].topA)) {
                closed = true;
                lower.push_back(lower.front());
                upper.push_back(upper.front());
                break;
            }
            auto range = next.equal_range(end);
            size_t found = spans.size();
            for (auto i = range.first; i != range.second; ++i)
                if (!used[i->second] && spans[i->second].tier == s.tier) {
                    found = std::min(found, i->second);
                }
            if (found == spans.size()) {
                lower.push_back(s.bottomB);
                upper.push_back(s.topB);
                break;
            }
            at = found;
        }
        ++chains;
        largest = std::max(largest, lower.size());
        if (lower.size() < 2)
            continue;
        std::vector<float> arc(lower.size());
        for (size_t i = 1; i < arc.size(); ++i)
            arc[i] = arc[i - 1] +
                     length2(mul(add(lower[i - 1], upper[i - 1]), .5f), mul(add(lower[i], upper[i]), .5f));
        const float total = arc.back();
        if (total < 3.f)
            ++shortChains;
        if (total < .0001f)
            continue;
        if (!appendWallCloud(look, lower, upper, arc, closed, spans[start].tier))
            ++fallback;
    }
    if (std::getenv("DEATHWARD_CANYON_FACET_STATS"))
        std::fprintf(stderr, "FACETS input=%zu spans=%zu chains=%zu short=%zu largest=%zu fallback=%zu\n",
                     input.size(), spans.size(), chains, shortChains, largest, fallback);
    weldContacts(look);
    const auto &f = look.surface;
    int columns = f.width - 1, rows = f.depth - 1;
    auto owner = [&](const CanyonSurfaceTriangle &t) {
        auto p = mul(add(add(t.vertices[0], t.vertices[1]), t.vertices[2]), 1.f / 3);
        int x = std::clamp(int((p.x - f.x) / f.step), 0, columns - 1),
            z = std::clamp(int((p.z - f.z) / f.step), 0, rows - 1);
        return size_t(z * columns + x);
    };
    std::stable_sort(look.triangles.begin(), look.triangles.end(),
                     [&](const auto &a, const auto &b) { return owner(a) < owner(b); });
    look.cellOffsets.assign(size_t(columns * rows) + 1, 0);
    for (const auto &t : look.triangles)
        ++look.cellOffsets[owner(t) + 1];
    for (size_t i = 1; i < look.cellOffsets.size(); ++i)
        look.cellOffsets[i] += look.cellOffsets[i - 1];
}
} // namespace dw
