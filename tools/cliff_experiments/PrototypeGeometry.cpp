#include "PrototypeGeometry.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <stdexcept>
// Reuse the small deterministic triangulator, not the production wall-selection pass.
namespace dw::cliffDetail {
std::vector<Tri> triangulate(std::vector<Point>);
double orient(Point, Point, Point);
} // namespace dw::cliffDetail
namespace dw::cliffOptions {
namespace {
using Point = cliffDetail::Point;
using Poly = std::vector<Point>;
constexpr double Pi = 3.141592653589793;
void check(bool b, const char *text) {
    if (!b)
        throw std::runtime_error(text);
}
struct Chart {
    const std::vector<cliffDetail::Quad> &quads;
    std::vector<double> s{0};
    double height = 0;
    explicit Chart(const std::vector<cliffDetail::Quad> &q) : quads(q) {
        for (auto a : q) {
            s.push_back(s.back() + distance(a.ab, a.bb));
            height += ((a.at.y - a.ab.y) + (a.bt.y - a.bb.y)) * .5 / q.size();
        }
    }
    Vector3 raw(Point p) const {
        size_t i =
            std::min(quads.size() - 1, size_t(std::upper_bound(s.begin(), s.end(), p.x) - s.begin() - 1));
        auto q = quads[i];
        float u = float((p.x - s[i]) / (s[i + 1] - s[i])), v = float(p.y / height);
        return Vector3Lerp(Vector3Lerp(q.ab, q.bb, u), Vector3Lerp(q.at, q.bt, u), v);
    }
    Vector3 normal(Point p) const {
        auto l = raw({std::max(0., p.x - .4), p.y}), r = raw({std::min(s.back(), p.x + .4), p.y});
        auto n = Vector3Normalize(Vector3CrossProduct(sub(r, l), {0, 1, 0}));
        auto q = quads.front();
        if (Vector3DotProduct(n, cliffDetail::normal(q)) < 0)
            n = mul(n, -1);
        return n;
    }
    bool boundary(Point p) const {
        return p.x < 1e-6 || p.y < 1e-6 || s.back() - p.x < 1e-6 || height - p.y < 1e-6;
    }
    Vector3 point(Point p, double smoothing, double depth) const {
        auto a = raw(p);
        if (boundary(p))
            return a;
        Vector3 smoothed{};
        double weight = 0;
        for (int k = -3; k <= 3; ++k) {
            double w = 4 - std::abs(k);
            auto q = raw({std::clamp(p.x + k * height * .28, 0., s.back()), p.y});
            smoothed = add(smoothed, mul(q, float(w)));
            weight += w;
        }
        smoothed = mul(smoothed, float(1 / weight));
        double fade = std::pow(std::max(0., std::sin(Pi * p.y / height)), .65) *
                      std::min(1., std::min(p.x, s.back() - p.x) / height);
        auto v = Vector3Lerp(a, smoothed, float(smoothing * fade));
        v = add(v, mul(normal(p), float(depth * fade)));
        return v;
    }
};
struct Surface {
    const Chart &chart;
    Mesh result;
    std::vector<std::array<Point, 3>> uv;
    void emit(Point a, Point b, Point c, Vector3 av, Vector3 bv, Vector3 cv) {
        double area = std::abs(cliffDetail::orient(a, b, c)) * .5;
        if (area < 1e-10)
            return;
        auto n = Vector3CrossProduct(sub(bv, av), sub(cv, av));
        check(Vector3Length(n) > 1e-8, "Degenerate physical triangle");
        auto mid = Point{(a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3};
        if (Vector3DotProduct(n, chart.normal(mid)) < 0) {
            std::swap(bv, cv);
            std::swap(b, c);
        }
        result.faces.push_back({av, bv, cv});
        uv.push_back({a, b, c});
        result.area += area;
        for (auto [p, v] : {std::pair{a, av}, std::pair{b, bv}, std::pair{c, cv}}) {
            result.maxDepth = std::max(result.maxDepth, distance(v, chart.raw(p)));
            if (chart.boundary(p))
                check(distance(v, chart.raw(p)) < 1e-5, "Outer contour moved");
        }
    }
    void validate() {
        check(std::abs(result.area - chart.s.back() * chart.height) < .001, "Area coverage mismatch");
        using Key = std::array<int64_t, 2>;
        auto key = [](Point p) { return Key{std::llround(p.x * 1000000), std::llround(p.y * 1000000)}; };
        std::map<std::pair<Key, Key>, int> edges;
        std::map<Key, Point> pts;
        for (auto t : uv)
            for (int i = 0; i < 3; ++i) {
                auto a = key(t[i]), b = key(t[(i + 1) % 3]);
                pts[a] = t[i];
                pts[b] = t[(i + 1) % 3];
                if (b < a)
                    std::swap(a, b);
                check(++edges[{a, b}] <= 2, "Non-manifold edge");
            }
        for (auto [edge, n] : edges)
            if (n == 1) {
                auto a = pts[edge.first], b = pts[edge.second];
                check((std::abs(a.x - b.x) < 2e-5 && (a.x < 2e-5 || chart.s.back() - a.x < 2e-5)) ||
                          (std::abs(a.y - b.y) < 2e-5 && (a.y < 2e-5 || chart.height - a.y < 2e-5)),
                      "Interior gap");
            }
    }
};
Point snap(Point p) {
    return {std::round(p.x * 1000000) / 1000000, std::round(p.y * 1000000) / 1000000};
}
Poly clip(const Poly &poly, Point a, Point b) {
    Poly out;
    if (poly.empty())
        return out;
    auto value = [&](Point p) {
        return 2 * (b.x - a.x) * p.x + 2 * (b.y - a.y) * p.y -
               (b.x * b.x + b.y * b.y - a.x * a.x - a.y * a.y);
    };
    for (size_t i = 0; i < poly.size(); ++i) {
        auto p = poly[i], q = poly[(i + 1) % poly.size()];
        double v = value(p), w = value(q);
        if (v <= 1e-10)
            out.push_back(p);
        if ((v < 0 && w > 0) || (v > 0 && w < 0)) {
            double t = v / (v - w);
            out.push_back({std::lerp(p.x, q.x, t), std::lerp(p.y, q.y, t)});
        }
    }
    return out;
}
Poly boundaryVertices(Poly poly, const Chart &chart) {
    Poly out;
    for (size_t i = 0; i < poly.size(); ++i) {
        auto a = poly[i], b = poly[(i + 1) % poly.size()];
        out.push_back(a);
        std::vector<std::pair<double, Point>> added;
        for (auto s : chart.s)
            for (double y : {0., chart.height}) {
                Point p{s, y};
                double dx = b.x - a.x, dy = b.y - a.y, den = dx * dx + dy * dy,
                       t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / den;
                if (t > 1e-6 && t < 1 - 1e-6 && std::abs(cliffDetail::orient(a, b, p)) < 1e-6)
                    added.push_back({t, p});
            }
        std::sort(added.begin(), added.end(), [](auto a, auto b) { return a.first < b.first; });
        for (auto [t, p] : added)
            out.push_back(p);
    }
    return out;
}
} // namespace
Mesh build(const std::vector<cliffDetail::Quad> &quads, const std::string &mode, uint64_t seed) {
    Chart chart(quads);
    Surface mesh{chart};
    Random rng(seed);
    if (mode == "a" || mode == "a2") {
        std::vector<Point> points;
        for (auto s : chart.s) {
            points.push_back({s, 0});
            points.push_back({s, chart.height});
        }
        for (double x : {0., chart.s.back()})
            for (double t : {.26, .61, .83})
                points.push_back({x, t * chart.height});
        size_t boundary = points.size();
        double spacing = chart.height * .36;
        for (int attempt = 0;
             attempt < 3000 && points.size() < boundary + size_t(chart.s.back() / chart.height * 4);
             ++attempt) {
            Point p{rng.real(float(spacing * .6), float(chart.s.back() - spacing * .6)),
                    rng.real(float(spacing * .55), float(chart.height - spacing * .55))};
            bool ok = true;
            for (auto q : points)
                if (std::hypot(p.x - q.x, p.y - q.y) < spacing) {
                    ok = false;
                    break;
                }
            if (ok)
                points.push_back(p);
        }
        auto pos = [&](Point p) {
            double d = chart.height * .11 *
                       (.65 * std::sin(p.x * 1.21 + p.y * .62) + .35 * std::cos(p.x * .57 - p.y * 1.84));
            return chart.point(p, .7, d);
        };
        cliffDetail::Study study;
        study.points = points;
        study.width = float(chart.s.back());
        study.height = float(chart.height);
        study.boundary = boundary;
        for (auto p : points)
            study.vertices.push_back(pos(p));
        study.triangles = cliffDetail::triangulate(points);
        if (mode == "a2")
            study=cliffDetail::buildSelectedA(quads,seed);
        for (auto t : study.triangles)
            mesh.emit(study.points[t.a], study.points[t.b], study.points[t.c], study.vertices[t.a],
                      study.vertices[t.b], study.vertices[t.c]);
        mesh.result.quads = study.quads;
        mesh.result.ngons = study.ngons;
        mesh.result.chips = study.chips;
        for (auto f : study.polygons)
            for (size_t i = 0; i < f.size(); ++i)
                mesh.result.polygonEdges.push_back(
                    {study.vertices[f[i]], study.vertices[f[(i + 1) % f.size()]]});
    } else {
        check(mode == "b" || mode == "c", "Unknown variant");
        bool hybrid = mode == "c";
        std::vector<Point> centers;
        // Geological sections are seeded in staggered vertical positions, not a row of columns.
        double s = chart.height * .35;
        int i = 0;
        while (s < chart.s.back()) {
            centers.push_back({s, chart.height * (i % 3 == 0   ? .24
                                                  : i % 3 == 1 ? .74
                                                               : .48) +
                                      rng.real(-.14f, .14f) * chart.height});
            s += chart.height * rng.real(hybrid ? .95f : .65f, hybrid ? 1.75f : 1.3f);
            ++i;
        }
        mesh.result.masses = centers.size();
        for (size_t cell = 0; cell < centers.size(); ++cell) {
            Poly poly{{0, 0}, {chart.s.back(), 0}, {chart.s.back(), chart.height}, {0, chart.height}};
            for (size_t j = 0; j < centers.size(); ++j)
                if (j != cell)
                    poly = clip(poly, centers[cell], centers[j]);
            if (poly.size() < 3)
                continue;
            auto coarse = poly;
            poly = boundaryVertices(poly, chart);
            for (auto &p : poly) {
                p = snap(p);
                p.x = std::clamp(p.x, 0., chart.s.back());
                p.y = std::clamp(p.y, 0., chart.height);
            }
            Point center{};
            for (auto p : coarse) {
                center.x += p.x / coarse.size();
                center.y += p.y / coarse.size();
            }
            auto anchor = chart.point(center, .85, 0), n = chart.normal(center);
            auto tangent = Vector3Normalize(Vector3CrossProduct({0, 1, 0}, n));
            double inset = rng.real(hybrid ? .60f : .48f, hybrid ? .81f : .72f),
                   depth = chart.height * rng.real(hybrid ? .07f : .11f, hybrid ? .18f : .27f);
            if (cell % 5 == 3)
                depth = -chart.height * .075;
            double tiltX = rng.real(-.14f, .14f), tiltY = rng.real(-.1f, .1f);
            auto seam = [&](Point p) {
                return chart.point(p, .85, -chart.height * .025 * (.5 + .5 * std::sin(p.x * .9 + p.y)));
            };
            auto planeNormal = Vector3Normalize(Vector3CrossProduct(
                add(tangent, mul(n, float(tiltX))), add(Vector3{0, 1, 0}, mul(n, float(tiltY)))));
            auto planeAnchor = add(anchor, mul(n, float(depth)));
            auto plane = [&](Point p) {
                auto base = chart.raw(p), local = chart.normal(p);
                double denominator = Vector3DotProduct(planeNormal, local);
                double offset = Vector3DotProduct(planeNormal, sub(planeAnchor, base)) /
                                std::max(.25, std::abs(denominator));
                if (denominator < 0)
                    offset = -offset;
                double fade = std::pow(std::max(0., std::sin(Pi * p.y / chart.height)), .6) *
                              std::min(1., std::min(p.x, chart.s.back() - p.x) / chart.height);
                double limit = chart.height * (hybrid ? .22 : .27) * fade;
                return add(base, mul(local, float(std::clamp(offset, -limit, limit))));
            };
            std::vector<Point> ring;
            for (auto p : poly)
                ring.push_back({std::lerp(center.x, p.x, inset), std::lerp(center.y, p.y, inset)});
            for (size_t k = 0; k < poly.size(); ++k) {
                size_t j = (k + 1) % poly.size();
                auto a = poly[k], b = poly[j], c = ring[j], d = ring[k];
                auto av = seam(a), bv = seam(b), cv = plane(c), dv = plane(d);
                if (hybrid && (cell + k) % 4 == 0 && !chart.boundary(a) && !chart.boundary(b)) {
                    Point cut{(a.x + b.x + c.x + d.x) / 4, (a.y + b.y + c.y + d.y) / 4};
                    auto v = mul(add(add(av, bv), add(cv, dv)), .25f);
                    v = add(v, mul(n, float(-chart.height * .045)));
                    mesh.emit(a, b, cut, av, bv, v);
                    mesh.emit(b, c, cut, bv, cv, v);
                    mesh.emit(c, d, cut, cv, dv, v);
                    mesh.emit(d, a, cut, dv, av, v);
                } else {
                    mesh.emit(a, b, c, av, bv, cv);
                    mesh.emit(a, c, d, av, cv, dv);
                }
            }
            for (size_t k = 0; k < ring.size(); ++k)
                mesh.emit(ring[k], ring[(k + 1) % ring.size()], center, plane(ring[k]),
                          plane(ring[(k + 1) % ring.size()]), plane(center));
        }
    }
    mesh.validate();
    return mesh.result;
}
} // namespace dw::cliffOptions
