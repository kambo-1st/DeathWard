#include "raylib.h"
#include "raymath.h"
#include "world/CliffWallTopology.hpp"
#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <stdexcept>
namespace dw::cliffDetail {
double orient(Point, Point, Point);
namespace {
using Face = std::vector<int>;
Vector3 faceNormal(const Face &f, const Study &m) {
    Vector3 n{};
    for (size_t i = 1; i + 1 < f.size(); ++i)
        n = add(n, Vector3CrossProduct(sub(m.vertices[f[i]], m.vertices[f[0]]),
                                       sub(m.vertices[f[i + 1]], m.vertices[f[0]])));
    return Vector3Normalize(n);
}
Vector3 centroid(const Face &f, const Study &m) {
    Vector3 p{};
    for (int i : f)
        p = add(p, m.vertices[i]);
    return mul(p, 1.f / f.size());
}
bool convex(const Face &f, const Study &m) {
    for (size_t i = 0; i < f.size(); ++i)
        if (orient(m.points[f[i]], m.points[f[(i + 1) % f.size()]], m.points[f[(i + 2) % f.size()]]) < 1e-9)
            return false;
    return true;
}
} // namespace
void refineFacets(Study &m, uint64_t seed) {
    if (m.triangles.size() < 4)
        return;
    std::vector<Face> faces;
    std::vector<Vector3> directions(m.vertices.size());
    for (auto t : m.triangles) {
        Face f{t.a, t.b, t.c};
        if (orient(m.points[t.a], m.points[t.b], m.points[t.c]) < 0)
            std::reverse(f.begin(), f.end());
        faces.push_back(f);
        auto n = faceNormal(f, m);
        for (int i : f)
            directions[i] = add(directions[i], n);
    }
    for (auto &d : directions) {
        d.y = 0;
        d = Vector3Normalize(d);
    }
    const auto initial = m.vertices;
    std::vector<bool> taken(faces.size());
    std::map<std::pair<int, int>, std::vector<int>> edges;
    for (size_t i = 0; i < faces.size(); ++i)
        for (size_t k = 0; k < 3; ++k) {
            auto e = std::minmax(faces[i][k], faces[i][(k + 1) % 3]);
            edges[e].push_back(int(i));
        }
    struct Candidate {
        int a, b;
        Face face;
        float score;
    };
    std::vector<Candidate> candidates;
    Random rng(seed ^ 0x51554144524f434bULL);
    for (auto [edge, owners] : edges) {
        if (owners.size() != 2)
            continue;
        int a = owners[0], b = owners[1];
        Face polygon;
        std::map<int, int> next;
        for (int index : {a, b})
            for (int k = 0; k < 3; ++k) {
                int u = faces[index][k], v = faces[index][(k + 1) % 3];
                if (std::pair{std::min(u, v), std::max(u, v)} == edge)
                    continue;
                next[u] = v;
            }
        if (next.size() != 4)
            continue;
        int at = next.begin()->first;
        for (int k = 0; k < 4; ++k) {
            polygon.push_back(at);
            at = next[at];
        }
        if (at != polygon.front() || !convex(polygon, m))
            continue;
        auto planeNormal=faceNormal(polygon,m);
        auto tangent=Vector3Normalize(Vector3CrossProduct({0,1,0},planeNormal));
        float left=1e9f,right=-1e9f,bottom=1e9f,top=-1e9f;
        for(int v:polygon){float x=Vector3DotProduct(m.vertices[v],tangent);left=std::min(left,x);right=std::max(right,x);bottom=std::min(bottom,m.vertices[v].y);top=std::max(top,m.vertices[v].y);}
        float span=right-left,rise=top-bottom;
        if(std::min(span,rise)<.001f||std::max(span,rise)/std::min(span,rise)>2.5f)continue;
        int movable = 0;
        for (int i : polygon)
            movable += size_t(i) >= m.boundary;
        if (!movable)
            continue;
        float alignment = Vector3DotProduct(faceNormal(faces[a], m), faceNormal(faces[b], m));
        if (alignment < .72f)
            continue;
        float minEdge = 1e9f, maxEdge = 0;
        double area = 0;
        for (size_t i = 0; i < 4; ++i) {
            float d = Vector3Distance(m.vertices[polygon[i]], m.vertices[polygon[(i + 1) % 4]]);
            minEdge = std::min(minEdge, d);
            maxEdge = std::max(maxEdge, d);
            area += orient({0, 0}, m.points[polygon[i]], m.points[polygon[(i + 1) % 4]]) * .5;
        }
        if (maxEdge / std::max(.001f, minEdge) > 4.5f || area < m.height * m.height * .025)
            continue;
        candidates.push_back({a, b, polygon, alignment + .4f * minEdge / maxEdge + rng.real(0, .1f)});
    }
    std::sort(candidates.begin(), candidates.end(),
              [](const auto &a, const auto &b) { return a.score > b.score; });
    std::vector<Face> polygons;
    for (auto c : candidates)
        if (!taken[c.a] && !taken[c.b]) {
            taken[c.a] = taken[c.b] = true;
            polygons.push_back(c.face);
        }
    for (size_t i = 0; i < faces.size(); ++i)
        if (!taken[i])
            polygons.push_back(faces[i]);
    // Shared vertices move only along the local horizontal rock normal. All
    // contour vertices remain fixed; no independent face colors/normals are used.
    for (int iteration = 0; iteration < 20; ++iteration) {
        std::vector<float> sum(m.vertices.size()), weight(m.vertices.size());
        for (const auto &f : polygons)
            if (f.size() > 3) {
                auto n = faceNormal(f, m), center = centroid(f, m);
                for (int i : f)
                    if (size_t(i) >= m.boundary) {
                        float den = Vector3DotProduct(n, directions[i]);
                        if (std::abs(den) < .2f)
                            continue;
                        float delta = Vector3DotProduct(n, sub(center, m.vertices[i])) / den;
                        sum[i] += delta;
                        weight[i] += 1;
                    }
            }
        for (size_t i = m.boundary; i < m.vertices.size(); ++i)
            if (weight[i]) {
                float delta = std::clamp(sum[i] / weight[i] * .8f, -m.height * .025f, m.height * .025f);
                auto proposed = add(m.vertices[i], mul(directions[i], delta));
                float depth = Vector3DotProduct(sub(proposed, initial[i]), directions[i]);
                m.vertices[i] =
                    add(initial[i], mul(directions[i], std::clamp(depth, -m.height * .13f, m.height * .13f)));
            }
    }
    // Only genuinely near-planar quads survive. Curved pairs retain their
    // original triangles instead of hiding a large diagonal with fake normals.
    faces.clear();
    for (auto f : polygons) {
        if (f.size() == 4) {
            auto n = faceNormal(f, m);
            float alignment = 1;
            for (int k = 1; k < 3; ++k) {
                auto t = Vector3Normalize(Vector3CrossProduct(sub(m.vertices[f[k]], m.vertices[f[0]]),
                                                              sub(m.vertices[f[k + 1]], m.vertices[f[0]])));
                alignment = std::min(alignment, Vector3DotProduct(n, t));
            }
            if (alignment < .99f) {
                faces.push_back({f[0], f[1], f[2]});
                faces.push_back({f[0], f[2], f[3]});
                continue;
            }
        }
        faces.push_back(f);
    }
    // Truncate a sparse set of interior junctions. These small, welded polygon
    // caps make chips and short shelves rather than beveling every edge alike.
    std::map<size_t, int> capCenters;
    std::set<int> blocked;
    size_t maxChips = std::max<size_t>(1, (m.vertices.size() - m.boundary) / 7);
    struct Junction {
        int vertex;
        float score;
    };
    std::vector<Junction> junctions;
    for (size_t i = m.boundary; i < m.vertices.size(); ++i) {
        float score = 0;
        int count = 0;
        Vector3 average{};
        for (auto f : faces)
            if (std::find(f.begin(), f.end(), int(i)) != f.end()) {
                average = add(average, faceNormal(f, m));
                ++count;
            }
        average = Vector3Normalize(average);
        for (auto f : faces)
            if (std::find(f.begin(), f.end(), int(i)) != f.end())
                score += 1 - Vector3DotProduct(average, faceNormal(f, m));
        if (count >= 4 && score > .015f)
            junctions.push_back({int(i), score + rng.real(0, .015f)});
    }
    std::sort(junctions.begin(), junctions.end(), [](auto a, auto b) { return a.score > b.score; });
    for (auto junction : junctions) {
        int v = junction.vertex;
        if (m.chips >= maxChips || blocked.contains(v))
            continue;
        std::set<int> neighbors;
        std::vector<size_t> incident;
        Vector3 normal{};
        for (size_t i = 0; i < faces.size(); ++i) {
            auto f = faces[i];
            auto at = std::find(f.begin(), f.end(), v);
            if (at == f.end())
                continue;
            size_t k = size_t(at - f.begin());
            neighbors.insert(f[(k + f.size() - 1) % f.size()]);
            neighbors.insert(f[(k + 1) % f.size()]);
            incident.push_back(i);
            normal = add(normal, faceNormal(f, m));
        }
        if (neighbors.size() < 4)
            continue;
        normal = Vector3Normalize(normal);
        std::map<int, int> cut;
        const auto center = m.vertices[v];
        float extent = m.height * rng.real(.07f, .13f);
        for (int u : neighbors) {
            float t =
                std::clamp(extent / std::max(.001f, Vector3Distance(center, m.vertices[u])), .08f, .28f);
            auto p =
                Point{std::lerp(m.points[v].x, m.points[u].x, t), std::lerp(m.points[v].y, m.points[u].y, t)};
            auto position = Vector3Lerp(center, m.vertices[u], t);
            auto direction = directions[v];
            auto plane = add(center, mul(direction, -m.height * .012f));
            float den = Vector3DotProduct(normal, direction);
            if (std::abs(den) > .2f)
                position =
                    add(position, mul(direction, Vector3DotProduct(normal, sub(plane, position)) / den));
            cut[u] = int(m.vertices.size());
            m.points.push_back(p);
            m.vertices.push_back(position);
            directions.push_back(direction);
        }
        for (auto i : incident) {
            auto f = faces[i];
            Face replaced;
            for (size_t k = 0; k < f.size(); ++k) {
                if (f[k] != v)
                    replaced.push_back(f[k]);
                else {
                    replaced.push_back(cut[f[(k + f.size() - 1) % f.size()]]);
                    replaced.push_back(cut[f[(k + 1) % f.size()]]);
                }
            }
            faces[i] = std::move(replaced);
        }
        Face cap;
        for (auto [u, i] : cut)
            cap.push_back(i);
        std::sort(cap.begin(), cap.end(), [&](int a, int b) {
            return std::atan2(m.points[a].y - m.points[v].y, m.points[a].x - m.points[v].x) <
                   std::atan2(m.points[b].y - m.points[v].y, m.points[b].x - m.points[v].x);
        });
        capCenters[faces.size()] = v;
        faces.push_back(cap);
        m.vertices[v] = add(center, mul(directions[v], -m.height * .012f));
        blocked.insert(v);
        for (int u : neighbors)
            blocked.insert(u);
        ++m.chips;
    }
    m.polygons = faces;
    m.triangles.clear();
    m.quads = m.ngons = 0;
    for (size_t fi = 0; fi < faces.size(); ++fi) {
        const auto &f = faces[fi];
        m.quads += f.size() == 4;
        m.ngons += f.size() > 4;
        auto emit = [&](int a, int b, int c) {
            Tri t{a, b, c};
            if (std::abs(orient(m.points[a], m.points[b], m.points[c])) < 1e-10)
                return;
            auto n =
                Vector3CrossProduct(sub(m.vertices[b], m.vertices[a]), sub(m.vertices[c], m.vertices[a]));
            if (Vector3DotProduct(n, add(add(directions[a], directions[b]), directions[c])) < 0)
                std::swap(t.b, t.c);
            m.triangles.push_back(t);
        };
        if (auto it = capCenters.find(fi); it != capCenters.end()) {
            for (size_t k = 0; k < f.size(); ++k)
                emit(it->second, f[k], f[(k + 1) % f.size()]);
        } else
            for (size_t k = 1; k + 1 < f.size(); ++k)
                emit(f[0], f[k], f[k + 1]);
    }
}
} // namespace dw::cliffDetail
namespace dw::cliffDetail {
constexpr double Pi = 3.141592653589793;
std::vector<Tri> triangulate(std::vector<Point>);
Study buildSelectedA(const std::vector<Quad> &patch, uint64_t seed, float reliefScale) {
    Study m;
    std::vector<double> distanceAlong{0};
    double height = 0;
    for (auto q : patch) {
        distanceAlong.push_back(distanceAlong.back() + distance(q.ab, q.bb));
        height += ((q.at.y - q.ab.y) + (q.bt.y - q.bb.y)) * .5 / patch.size();
    }
    if (height < 1.15 || distanceAlong.back() < height * .6)
        throw std::runtime_error("Cliff patch too narrow");
    m.width = float(distanceAlong.back());
    m.height = float(height);
    auto raw = [&](Point p) {
        size_t i = std::min(patch.size() - 1,
                            size_t(std::upper_bound(distanceAlong.begin(), distanceAlong.end(), p.x) -
                                   distanceAlong.begin() - 1));
        auto q = patch[i];
        float u = float((p.x - distanceAlong[i]) / (distanceAlong[i + 1] - distanceAlong[i])),
              v = float(p.y / height);
        return Vector3Lerp(Vector3Lerp(q.ab, q.bb, u), Vector3Lerp(q.at, q.bt, u), v);
    };
    auto direction = [&](Point p) {
        auto a = raw({std::max(0., p.x - .4), p.y}), b = raw({std::min(distanceAlong.back(), p.x + .4), p.y});
        auto n = Vector3Normalize(Vector3CrossProduct(sub(b, a), {0, 1, 0}));
        if (Vector3DotProduct(n, normal(patch.front())) < 0)
            n = mul(n, -1);
        return n;
    };
    auto position = [&](Point p) {
        auto original = raw(p);
        if (p.x < 1e-6 || p.y < 1e-6 || distanceAlong.back() - p.x < 1e-6 || height - p.y < 1e-6)
            return original;
        Vector3 smoothed{};
        double weights = 0;
        for (int k = -3; k <= 3; ++k) {
            double w = 4 - std::abs(k);
            smoothed =
                add(smoothed,
                    mul(raw({std::clamp(p.x + k * height * .28, 0., distanceAlong.back()), p.y}), float(w)));
            weights += w;
        }
        double fade = std::pow(std::max(0., std::sin(Pi * p.y / height)), .65) *
                      std::min(1., std::min(p.x, distanceAlong.back() - p.x) / height);
        double depth =
            height * .11 * (.65 * std::sin(p.x * 1.21 + p.y * .62) + .35 * std::cos(p.x * .57 - p.y * 1.84));
        return add(Vector3Lerp(original, mul(smoothed, float(1 / weights)), float(.7 * fade * reliefScale)),
                   mul(direction(p), float(depth * fade * reliefScale)));
    };
    for (auto s : distanceAlong) {
        m.points.push_back({s, 0});
        m.points.push_back({s, height});
    }
    for (double x : {0., distanceAlong.back()})
        for (double v : {.26, .61, .83})
            m.points.push_back({x, v * height});
    m.boundary = m.points.size();
    Random rng(seed);
    double spacing = std::max(.35, height * .36);
    size_t added = std::min(patch.size(), size_t(std::max(1., distanceAlong.back() / height * 4)));
    if (height > spacing * 1.1 && distanceAlong.back() > spacing * 1.2)
        for (int attempt = 0; attempt < 1600 && m.points.size() < m.boundary + added; ++attempt) {
            Point p{rng.real(float(spacing * .6), float(distanceAlong.back() - spacing * .6)),
                    rng.real(float(spacing * .55), float(height - spacing * .55))};
            bool good = true;
            for (auto q : m.points)
                if (std::hypot(p.x - q.x, p.y - q.y) < spacing) {
                    good = false;
                    break;
                }
            if (good)
                m.points.push_back(p);
        }
    if (m.points.size() == m.boundary)
        throw std::runtime_error("No interior cliff area to refine");
    for (auto p : m.points)
        m.vertices.push_back(position(p));
    m.triangles = triangulate(m.points);
    const auto fixed = m.vertices;
    size_t originalTriangles = m.triangles.size();
    refineFacets(m, seed);
    double area = 0, steep = 0, physicalArea = 0;
    std::map<std::pair<int, int>, int> edges;
    for (size_t i = 0; i < m.boundary; ++i)
        if (distance(fixed[i], m.vertices[i]) > 1e-7)
            throw std::runtime_error("Cliff contour changed");
    for (auto t : m.triangles) {
        area += std::abs(orient(m.points[t.a], m.points[t.b], m.points[t.c])) * .5;
        auto n =
            Vector3CrossProduct(sub(m.vertices[t.b], m.vertices[t.a]), sub(m.vertices[t.c], m.vertices[t.a]));
        float twice = Vector3Length(n);
        if (twice < 1e-8 || !std::isfinite(twice))
            throw std::runtime_error("Degenerate cliff facet");
        float up = std::abs(n.y) / twice;
        physicalArea += twice;
        if (up < .65f)
            steep += twice;
        m.maxTilt = std::max(m.maxTilt, up);
        for (auto e : {std::pair{t.a, t.b}, std::pair{t.b, t.c}, std::pair{t.c, t.a}}) {
            if (e.first > e.second)
                std::swap(e.first, e.second);
            if (++edges[e] > 2)
                throw std::runtime_error("Nonmanifold cliff mesh");
        }
    }
    for (auto [edge, count] : edges)
        if (count == 1) {
            auto a = m.points[edge.first], b = m.points[edge.second];
            if (!((std::abs(a.x - b.x) < 1e-6 && (a.x < 1e-6 || distanceAlong.back() - a.x < 1e-6)) ||
                  (std::abs(a.y - b.y) < 1e-6 && (a.y < 1e-6 || height - a.y < 1e-6))))
                throw std::runtime_error("Interior cliff gap");
        }
    if (std::abs(area - distanceAlong.back() * height) > .001 || steep < physicalArea * .65 ||
        m.triangles.size() > originalTriangles * 2 + 16)
        throw std::runtime_error("Invalid cliff facet budget/coverage/slope");
    return m;
}
} // namespace dw::cliffDetail
