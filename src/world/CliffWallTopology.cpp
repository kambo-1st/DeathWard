#include "world/CliffWallTopology.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <random>
#include <stdexcept>
namespace dw::cliffDetail {
void require(bool value, const char *what) {
    if (!value)
        throw std::runtime_error(what);
}
double orient(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
bool inCircle(Point p, Point a, Point b, Point c) {
    double ax = a.x - p.x, ay = a.y - p.y, bx = b.x - p.x, by = b.y - p.y, cx = c.x - p.x, cy = c.y - p.y;
    double d = (ax * ax + ay * ay) * (bx * cy - by * cx) - (bx * bx + by * by) * (ax * cy - ay * cx) +
               (cx * cx + cy * cy) * (ax * by - ay * bx);
    return d * orient(a, b, c) > 1e-10;
}
std::vector<Tri> triangulate(std::vector<Point> p) {
    const int count = int(p.size());
    double span = 1;
    for (auto v : p)
        span = std::max({span, v.x, v.y});
    p.push_back({-20 * span, -20 * span});
    p.push_back({40 * span, -20 * span});
    p.push_back({0, 40 * span});
    std::vector<Tri> tris{{count, count + 1, count + 2}};
    for (int i = 0; i < count; ++i) {
        std::map<std::pair<int, int>, int> edges;
        std::vector<Tri> keep;
        for (auto t : tris) {
            if (!inCircle(p[i], p[t.a], p[t.b], p[t.c])) {
                keep.push_back(t);
                continue;
            }
            for (auto e : {std::pair{t.a, t.b}, std::pair{t.b, t.c}, std::pair{t.c, t.a}}) {
                if (e.first > e.second)
                    std::swap(e.first, e.second);
                ++edges[e];
            }
        }
        for (auto [e, n] : edges)
            if (n == 1) {
                Tri t{e.first, e.second, i};
                if (orient(p[t.a], p[t.b], p[t.c]) < 0)
                    std::swap(t.a, t.b);
                if (std::abs(orient(p[t.a], p[t.b], p[t.c])) > 1e-9)
                    keep.push_back(t);
            }
        tris = std::move(keep);
    }
    std::erase_if(tris, [&](auto t) { return t.a >= count || t.b >= count || t.c >= count; });
    return tris;
}
Vector3 normal(Quad q) {
    return Vector3Normalize(Vector3CrossProduct(sub(q.bb, q.ab), sub(q.bt, q.ab)));
}
bool near(Vector3 a, Vector3 b) {
    return distance(a, b) < .00001f;
}
Study build(const std::vector<Quad> &patch, uint64_t seed, float reliefScale) {
    Study out;
    std::vector<float> s{0};
    for (auto q : patch)
        s.push_back(s.back() + distance(q.ab, q.bb));
    out.width = s.back();
    for (auto q : patch)
        out.height += ((q.at.y - q.ab.y) + (q.bt.y - q.bb.y)) * .5f / patch.size();
    auto pos = [&](Point p) {
        size_t k = std::min(patch.size() - 1,
                            size_t(std::upper_bound(s.begin(), s.end(), float(p.x)) - s.begin() - 1));
        auto q = patch[k];
        float u = (p.x - s[k]) / (s[k + 1] - s[k]), v = p.y / out.height;
        auto lo = Vector3Lerp(q.ab, q.bb, u), hi = Vector3Lerp(q.at, q.bt, u);
        return Vector3Lerp(lo, hi, v);
    };
    // Every existing top/bottom vertex is retained exactly. No interior column constraints.
    for (auto x : s) {
        out.points.push_back({x, 0});
        out.points.push_back({x, out.height});
    }
    for (int side = 0; side < 2; ++side)
        for (double v : {.29, .64})
            out.points.push_back({side * out.width, v * out.height});
    out.boundary = out.points.size();
    std::mt19937 rng(uint32_t(seed ^ (seed >> 32)));
    std::uniform_real_distribution<double> random(0, 1);
    const double spacing = std::max(.65, out.height * .32);
    require(out.width > spacing * 1.3, "Patch too narrow for broad facets");
    for (int attempt = 0; attempt < 1000 && out.points.size() < out.boundary + patch.size(); ++attempt) {
        Point p{spacing * .55 + random(rng) * (out.width - spacing * 1.1),
                spacing * .55 + random(rng) * (out.height - spacing * 1.1)};
        bool clear = true;
        for (auto q : out.points)
            if (std::hypot(p.x - q.x, p.y - q.y) < spacing) {
                clear = false;
                break;
            }
        if (clear)
            out.points.push_back(p);
    }
    out.triangles = triangulate(out.points);
    for (size_t i = 0; i < out.points.size(); ++i) {
        auto p = out.points[i];
        auto v = pos(p);
        if (i < (patch.size() + 1) * 2) {
            size_t edge = i / 2;
            auto q = patch[std::min(edge, patch.size() - 1)];
            v = edge == patch.size() ? (i % 2 ? q.bt : q.bb) : (i % 2 ? q.at : q.ab);
        }
        if (i >= out.boundary) {
            size_t k = std::min(patch.size() - 1,
                                size_t(std::upper_bound(s.begin(), s.end(), float(p.x)) - s.begin() - 1));
            auto n = normal(patch[k]);
            double u = p.x / out.width, t = p.y / out.height;
            double wave = .65 * std::sin(p.x * 1.35 + p.y * .73) + .35 * std::cos(p.x * .81 - p.y * 1.64);
            float relief = float(out.height * .075 * reliefScale * wave * std::sin(3.141592653589793 * u) *
                                 std::sin(3.141592653589793 * t));
            v = add(v, mul(n, relief));
        }
        out.vertices.push_back(v);
    }
    for (auto &t : out.triangles) {
        auto n = Vector3CrossProduct(sub(out.vertices[t.b], out.vertices[t.a]),
                                     sub(out.vertices[t.c], out.vertices[t.a]));
        if (Vector3DotProduct(n, normal(patch.front())) < 0)
            std::swap(t.a, t.b);
    }
    // Verify exact contour constraints, manifold edges, coverage and triangle shapes.
    for (size_t i = 0; i < out.boundary; ++i)
        require(near(out.vertices[i], pos(out.points[i])), "Moved perimeter vertex");
    std::map<std::pair<int, int>, int> edgeCounts;
    double area = 0, broadArea = 0;
    size_t broad = 0;
    float maxTilt = 0;
    for (auto t : out.triangles) {
        auto a = out.vertices[t.a], b = out.vertices[t.b], c = out.vertices[t.c];
        auto n = Vector3Normalize(Vector3CrossProduct(sub(b, a), sub(c, a)));
        maxTilt = std::max(maxTilt, std::abs(n.y));
        float longest = std::max({distance(a, b), distance(b, c), distance(c, a)});
        float twice = Vector3Length(Vector3CrossProduct(sub(b, a), sub(c, a)));
        if (longest * longest / twice <= 2.5f) {
            ++broad; broadArea += std::abs(orient(out.points[t.a],out.points[t.b],out.points[t.c]))*.5;
        }
        area += std::abs(orient(out.points[t.a], out.points[t.b], out.points[t.c])) * .5;
        for (auto e : {std::pair{t.a, t.b}, std::pair{t.b, t.c}, std::pair{t.c, t.a}}) {
            if (e.first > e.second)
                std::swap(e.first, e.second);
            require(++edgeCounts[e] <= 2, "Non-manifold edge");
        }
    }
    require(std::abs(area - out.width * out.height) < .0001, "Missing patch area");
    for (auto [e, n] : edgeCounts)
        if (n == 1) {
            auto a = out.points[e.first], b = out.points[e.second];
            require((std::abs(a.x - b.x) < 1e-5 && (a.x < 1e-5 || std::abs(a.x - out.width) < 1e-5)) ||
                        (std::abs(a.y - b.y) < 1e-5 && (a.y < 1e-5 || std::abs(a.y - out.height) < 1e-5)),
                    "Interior crack");
        }
    require(broadArea >= area*.7, "Dominant skinny facets");
    require(maxTilt < .5f, "Wall not steep");
    out.broad = broad;
    out.maxTilt = maxTilt;
    return out;
}
} // namespace dw::cliffDetail
