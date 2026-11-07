#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "PlateauRegion.hpp"
#include "PlateauChunks.hpp"
#include "PlateauSourceReuse.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <stdexcept>
namespace dw::rockFormations {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
std::vector<Polygon> consolidateExactPlanar(std::vector<Polygon> parts,Vector3 faceNormal) {
    const int omitted=std::abs(faceNormal.x)>=std::abs(faceNormal.y) && std::abs(faceNormal.x)>=std::abs(faceNormal.z)?0:
        std::abs(faceNormal.y)>=std::abs(faceNormal.z)?1:2;
    auto xy=[&](Vector3 p) {
        return omitted==0?std::array<long double,2>{p.y,p.z}:omitted==1?std::array<long double,2>{p.x,p.z}:std::array<long double,2>{p.x,p.y};
    };
    auto equal=[](Vector3 a,Vector3 b){return a.x==b.x && a.y==b.y && a.z==b.z;};
    auto turn=[&](Vector3 a,Vector3 b,Vector3 c){const auto u=xy(a),v=xy(b),w=xy(c);return (v[0]-u[0])*(w[1]-u[1])-(v[1]-u[1])*(w[0]-u[0]);};
    auto signedArea=[&](const Polygon &p){long double a=0;for(size_t k=1;k+1<p.size();++k)a+=turn(p[0],p[k],p[k+1]);return a;};
    bool changed=true;
    while(changed) {
        changed=false;
        for(size_t i=0;i<parts.size() && !changed;++i)for(size_t j=i+1;j<parts.size();++j) {
            bool shared=false;
            for(size_t a=0;a<parts[i].size();++a)for(size_t b=0;b<parts[j].size();++b)
                shared |= equal(parts[i][a],parts[j][(b+1)%parts[j].size()]) && equal(parts[i][(a+1)%parts[i].size()],parts[j][b]);
            if(!shared)continue;
            auto points=parts[i];points.insert(points.end(),parts[j].begin(),parts[j].end());
            std::sort(points.begin(),points.end(),[&](auto a,auto b){const auto u=xy(a),v=xy(b);return u!=v?u<v:std::array<float,3>{a.x,a.y,a.z}<std::array<float,3>{b.x,b.y,b.z};});
            points.erase(std::unique(points.begin(),points.end(),equal),points.end());
            if(points.size()<3)continue;
            Polygon hull;
            for(auto p:points){while(hull.size()>1 && turn(hull[hull.size()-2],hull.back(),p)<=0)hull.pop_back();hull.push_back(p);}
            const auto lower=hull.size();
            for(auto at=points.rbegin()+1;at!=points.rend();++at){while(hull.size()>lower && turn(hull[hull.size()-2],hull.back(),*at)<=0)hull.pop_back();hull.push_back(*at);}
            if(!hull.empty())hull.pop_back();if(hull.size()<3)continue;
            const auto expected=std::abs(signedArea(parts[i]))+std::abs(signedArea(parts[j]));
            if(std::abs(signedArea(hull))!=expected)continue;
            if(signedArea(hull)*signedArea(parts[i])<0)std::reverse(hull.begin(),hull.end());
            parts[i]=std::move(hull);parts.erase(parts.begin()+j);changed=true;break;
        }
    }
    return parts;
}
#endif
namespace {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
thread_local bool preciseCoreCsg=false;
struct CoreCsgScope {
    bool previous=preciseCoreCsg;
    explicit CoreCsgScope(bool enabled){preciseCoreCsg=enabled;}
    ~CoreCsgScope(){preciseCoreCsg=previous;}
};
#endif
constexpr float Epsilon = 0.00002f;
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
Vector3 normal(const Polygon &p) {
    Vector3 n{};
    for (size_t i = 1; i + 1 < p.size(); ++i)
        n = add(n, Vector3CrossProduct(sub(p[i], p[0]), sub(p[i + 1], p[0])));
    return Vector3Normalize(n);
}
Vector3 center(const Polygon &p) {
    Vector3 v{};
    for (auto a : p)
        v = add(v, a);
    return mul(v, 1.f / p.size());
}
float area(const Polygon &p) {
    float a = 0;
    for (size_t i = 1; i + 1 < p.size(); ++i)
        a += Vector3Length(Vector3CrossProduct(sub(p[i], p[0]), sub(p[i + 1], p[0]))) * .5f;
    return a;
}
// Clipping a face against several solids partitions even its exposed, planar
// regions. Join adjacent pieces only when their union is convex and has exactly
// the same area: a hull must never bridge a recess or cover a real hole.
std::vector<Polygon> consolidate(std::vector<Polygon> parts, Vector3 faceNormal) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(preciseCoreCsg)return consolidateExactPlanar(std::move(parts),faceNormal);
#endif
    const auto axis = Vector3Normalize(Vector3CrossProduct(
        std::abs(faceNormal.y) < .9f ? Vector3{0, 1, 0} : Vector3{1, 0, 0}, faceNormal));
    const auto other = Vector3CrossProduct(faceNormal, axis);
    auto hull = [&](const Polygon &a, const Polygon &b) {
        Polygon points = a;
        points.insert(points.end(), b.begin(), b.end());
        const auto origin = points.front();
        auto coordinates = [&](Vector3 p) {
            auto d = sub(p, origin);
            return std::pair<double, double>{dot(d, axis), dot(d, other)};
        };
        std::sort(points.begin(), points.end(), [&](auto p, auto q) {
            return coordinates(p) < coordinates(q);
        });
        points.erase(std::unique(points.begin(), points.end(), [](auto p, auto q) {
            return distance(p, q) < Epsilon;
        }), points.end());
        auto turn = [&](Vector3 a, Vector3 b, Vector3 c) {
            auto [ax, ay] = coordinates(a);
            auto [bx, by] = coordinates(b);
            auto [cx, cy] = coordinates(c);
            return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
        };
        Polygon boundary;
        for (auto p : points) {
            while (boundary.size() > 1 && turn(boundary[boundary.size()-2], boundary.back(), p) <= 0)
                boundary.pop_back();
            boundary.push_back(p);
        }
        const auto lower = boundary.size();
        for (auto it = points.rbegin() + 1; it != points.rend(); ++it) {
            while (boundary.size() > lower && turn(boundary[boundary.size()-2], boundary.back(), *it) <= 0)
                boundary.pop_back();
            boundary.push_back(*it);
        }
        boundary.pop_back();
        return boundary;
    };
    bool changed = true;
    while (changed) {
        changed = false;
        for (size_t i = 0; i < parts.size() && !changed; ++i)
            for (size_t j = i + 1; j < parts.size(); ++j) {
                int shared = 0;
                for (auto p : parts[i])
                    shared += std::any_of(parts[j].begin(), parts[j].end(),
                                          [&](auto q) { return distance(p, q) < Epsilon; });
                if (shared < 2)
                    continue;
                auto combined = hull(parts[i], parts[j]);
                const float sum = area(parts[i]) + area(parts[j]);
                if (std::abs(area(combined) - sum) > std::max(.000002f, sum * .000002f))
                    continue;
                parts[i] = std::move(combined);
                parts.erase(parts.begin() + j);
                changed = true;
                break;
            }
    }
    return parts;
}
Polygon clip(const Polygon &p, Plane plane, bool inside) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    const double clipEpsilon=preciseCoreCsg?1e-9:Epsilon;
#else
    constexpr auto clipEpsilon=Epsilon;
#endif
    Polygon out;
    if (p.empty())
        return out;
    for (size_t i = 0; i < p.size(); ++i) {
        auto a = p[i], b = p[(i + 1) % p.size()];
        double av = planeProjection(plane, a) - plane.distance, bv = planeProjection(plane, b) - plane.distance;
        if(std::abs(av)<clipEpsilon) av=0;
        if(std::abs(bv)<clipEpsilon) bv=0;
        if (!inside) {
            av = -av;
            bv = -bv;
        }
        if (av <= 0)
            out.push_back(a);
        if ((av < 0 && bv > 0) || (av > 0 && bv < 0)) {
            double t = av / (av - bv);
            out.push_back({float(a.x+(double(b.x)-a.x)*t),float(a.y+(double(b.y)-a.y)*t),float(a.z+(double(b.z)-a.z)*t)});
        }
    }
    Polygon clean;
    for (auto v : out)
        if (clean.empty() || distance(clean.back(), v) > clipEpsilon)
            clean.push_back(v);
    if (clean.size() > 1 && distance(clean.front(), clean.back()) < clipEpsilon)
        clean.pop_back();
    return clean;
}
bool contains(const Volume &volume, Vector3 p, float margin = 0) {
    for (auto plane : volume.planes)
        if (planeProjection(plane, p) > plane.distance + margin)
            return false;
    return true;
}
Volume polyhedron(std::vector<Plane> planes, Vector3 origin) {
    for (auto &p : planes) {
        if(p.hasPreciseNormal) {
            const auto n=p.preciseNormal;const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
            for(auto &v:p.preciseNormal)v/=length;
            p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};
            p.distance=p.distance/length-planeProjection(p,origin);continue;
        }
        float length = Vector3Length(p.normal);
        p.normal = mul(p.normal, 1 / length);
        p.distance = p.distance / length - planeProjection(p, origin);
    }
    // Classify plane intersections before converting to render floats. Loose
    // float tolerances attached near-corner vertices to unrelated bevel faces,
    // producing an open solid for otherwise valid formation seeds.
    using Precise = std::array<double, 3>;
    auto precise = [](Vector3 v) { return Precise{v.x, v.y, v.z}; };
    auto crossPrecise = [](Precise a, Precise b) {
        return Precise{a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]};
    };
    auto dotPrecise = [](Precise a, Precise b) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; };
    std::vector<Precise> exactVertices;
    for (size_t a = 0; a < planes.size(); ++a)
        for (size_t b = a + 1; b < planes.size(); ++b)
            for (size_t c = b + 1; c < planes.size(); ++c) {
                auto p = planes[a], q = planes[b], r = planes[c];
                auto cross = crossPrecise(planeNormal(q), planeNormal(r));
                double det = dotPrecise(planeNormal(p), cross);
                if (std::abs(det) < 1e-10)
                    continue;
                auto rp = crossPrecise(planeNormal(r), planeNormal(p));
                auto pq = crossPrecise(planeNormal(p), planeNormal(q));
                Precise v;
                for (int k = 0; k < 3; ++k)
                    v[k] = (cross[k]*p.distance + rp[k]*q.distance + pq[k]*r.distance) / det;
                bool good = true;
                for (auto plane : planes)
                    if (dotPrecise(planeNormal(plane), v) > plane.distance + 1e-8) {
                        good = false;
                        break;
                    }
                if (!good)
                    continue;
                if (std::none_of(exactVertices.begin(), exactVertices.end(), [&](auto u) {
                    return std::hypot(u[0]-v[0], u[1]-v[1], u[2]-v[2]) < 1e-8;
                }))
                    exactVertices.push_back(v);
            }
    std::vector<Vector3> vertices;
    for (auto v : exactVertices)
        vertices.push_back({float(v[0]), float(v[1]), float(v[2])});
    check(vertices.size() >= 4, "Empty convex rock volume");
    Volume out;
    out.planes = planes;
    out.bounds = {{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    for (auto v : vertices) {
        out.bounds.min = {std::min(out.bounds.min.x, v.x), std::min(out.bounds.min.y, v.y),
                          std::min(out.bounds.min.z, v.z)};
        out.bounds.max = {std::max(out.bounds.max.x, v.x), std::max(out.bounds.max.y, v.y),
                          std::max(out.bounds.max.z, v.z)};
    }
    for (auto plane : planes) {
        Polygon face;
        for (size_t i = 0; i < exactVertices.size(); ++i)
            if (std::abs(dotPrecise(planeNormal(plane), exactVertices[i]) - plane.distance) < 1e-8)
                face.push_back(vertices[i]);
        if (face.size() < 3)
            continue;
        auto mid = center(face);
        auto x = Vector3Normalize(Vector3CrossProduct(
            std::abs(plane.normal.y) < .9f ? Vector3{0, 1, 0} : Vector3{1, 0, 0}, plane.normal));
        auto y = Vector3CrossProduct(plane.normal, x);
        std::sort(face.begin(), face.end(), [&](auto a, auto b) {
            a = sub(a, mid);
            b = sub(b, mid);
            return std::atan2(dot(a, y), dot(a, x)) < std::atan2(dot(b, y), dot(b, x));
        });
        if (dot(normal(face), plane.normal) < 0)
            std::reverse(face.begin(), face.end());
        if (area(face) > .000000001f)
            out.faces.push_back(face);
    }
    // A convex boundary must have every undirected edge twice and positive volume.
    std::map<std::pair<int, int>, int> edges;
    double volume = 0;
    auto id = [&](Vector3 p) {
        auto it = std::min_element(vertices.begin(), vertices.end(),
                                   [&](auto a, auto b) { return distance(a, p) < distance(b, p); });
        return int(it - vertices.begin());
    };
    for (auto f : out.faces) {
        for (size_t k = 0; k < f.size(); ++k) {
            int a = id(f[k]), b = id(f[(k + 1) % f.size()]);
            if (a > b)
                std::swap(a, b);
            ++edges[{a, b}];
        }
        for (size_t k = 1; k + 1 < f.size(); ++k)
            volume += dot(f[0], Vector3CrossProduct(f[k], f[k + 1])) / 6.;
    }
    for (auto [edge, n] : edges)
        check(n == 2, "Rock solid is not closed");
    check(volume > 1e-10, "Non-positive rock volume");
    for (auto &p : out.planes)
        p.distance += planeProjection(p, origin);
    for (auto &f : out.faces)
        for (auto &v : f)
            v = add(v, origin);
    out.bounds.min = add(out.bounds.min, origin);
    out.bounds.max = add(out.bounds.max, origin);
    for(const auto& f:out.faces)for(auto v:f)check(contains(out,v,.0002f),"Rock vertex escaped its convex planes");
    return out;
}
struct Rock {
    Vector3 center{}, tangent{}, outward{};
    float width = 0, depth = 0, height = 0;
    uint64_t seed = 0;
    FormationProfile profile;
};
Volume rock(const Rock &r, bool chip = false) {
    Random rng(r.seed);
    std::vector<Vector2> footprint;
    const unsigned corners = r.profile.corners;
    const float phase = rng.real(0, 2 * Pi);
    // Coherent asymmetric outlines, rather than chamfered rectangular modules.
    for (unsigned i = 0; i < corners; ++i) {
        float angle = 2 * Pi * float(i) / corners + rng.real(-.075f, .075f);
        float radius = 1 + .07f * std::sin(2 * angle + phase) + .04f * std::cos(3 * angle - phase);
        footprint.push_back({std::cos(angle) * radius, std::sin(angle) * radius});
    }
    // A shallow structural break divides the broad front into two large planes.
    // It changes the volume footprint, rather than adding noise to a face.
    size_t front = 0;
    float longest = 0;
    for (size_t i = 0; i < footprint.size(); ++i) {
        auto a = footprint[i], b = footprint[(i + 1) % footprint.size()];
        float length = std::hypot((b.x - a.x) * r.width, (b.y - a.y) * r.depth);
        if (b.x < a.x && length > longest) {
            front = i;
            longest = length;
        }
    }
    auto a = footprint[front], b = footprint[(front + 1) % footprint.size()];
    float t = rng.real(.34f, .64f), ex = b.x - a.x, ez = b.y - a.y, len = std::hypot(ex, ez),
          push = rng.real(.06f, .13f);
    footprint.insert(footprint.begin() + front + 1,
                     {std::lerp(a.x, b.x, t) + ez / len * push, std::lerp(a.y, b.y, t) - ex / len * push});
    std::vector<Plane> sides;
    auto lean = add(mul(r.tangent, r.profile.lean.x), mul(r.outward, r.profile.lean.y));
    for (size_t i = 0; i < footprint.size(); ++i) {
        auto a = footprint[i], b = footprint[(i + 1) % footprint.size()];
        Vector2 e{b.x - a.x, b.y - a.y};
        Vector2 n{e.y, -e.x};
        auto horizontal = add(mul(r.tangent, n.x / (r.width * .5f)), mul(r.outward, n.y / (r.depth * .5f)));
        float support = n.x * a.x + n.y * a.y;
        float ny = Vector3Length(horizontal) * (r.profile.taper + rng.real(-.015f, .015f)) -
                   dot(horizontal, lean);
        sides.push_back({{horizontal.x, ny, horizontal.z}, projection(horizontal, r.center) + support + ny * .08f});
    }
    auto roof = Plane{add(Vector3{0, 1, 0}, add(mul(r.tangent, r.profile.roof.x),
                                                mul(r.outward, r.profile.roof.y))),
                      0};
    roof.distance = planeProjection(roof, {r.center.x, .08f + r.height, r.center.z});
    // Bury the closed base below the retained ground. A base coincident with
    // that ground produced tiny exposed plates and self-shadowing at the join.
    Plane bottom{{0, -1, 0}, .12f};
    auto planes = sides;
    planes.push_back(roof);
    planes.push_back(bottom);
    // A second roof plane breaks only one shoulder of the broad cap.
    auto roofBreak = add(roof.normal, add(mul(r.tangent, r.profile.crown.x),
                                         mul(r.outward, r.profile.crown.y)));
    planes.push_back(
        {roofBreak, projection(roofBreak, {r.center.x, .08f + r.height, r.center.z}) +
                    (r.width * std::abs(r.profile.crown.x) + r.depth * std::abs(r.profile.crown.y)) *
                    r.profile.crownAt});
    for (size_t i = 0; i < sides.size(); ++i) {
        auto side = sides[i];
        float scale = Vector3Length(side.normal);
        side.normal = mul(side.normal, 1 / scale);
        side.distance /= scale;
        if (r.profile.bevelMask & (1u << i)) {
            const float amount = r.profile.bevel;
            const float angle = .65f;
            planes.push_back(
                {add(side.normal, mul(roof.normal, angle)), side.distance + roof.distance * angle - amount});
        }
        // The sides continue into the ground. Beveling every base cut a raised
        // zigzag seam against the retained terrain instead of grounding the rock.
    }
    if (chip) {
        // Cut one local roof corner, rather than beveling a whole rim ring.
        const auto direction=Vector3Normalize(add(r.outward,r.tangent));
        size_t corner=0;
        for(size_t i=1;i<sides.size();++i)
            if(dot(Vector3Normalize(sides[i].normal),direction) >
               dot(Vector3Normalize(sides[corner].normal),direction)) corner=i;
        auto a=sides[corner], b=sides[(corner+1)%sides.size()];
        const auto al=Vector3Length(a.normal),bl=Vector3Length(b.normal);
        planes.push_back({add(add(mul(a.normal,1/al),mul(b.normal,1/bl)),mul(roof.normal,.7f)),
                          a.distance/al+b.distance/bl+roof.distance*.7f-.17f});
    }
    const auto cutPlane=planes.back();
    auto volume=polyhedron(std::move(planes), r.center);
    if(chip) {
        float cutArea=0;
        const double scale=Vector3Length(cutPlane.normal);
        for(const auto &face:volume.faces) {
            if(std::all_of(face.begin(),face.end(),[&](auto p) {
                return std::abs(planeProjection(cutPlane,p)-cutPlane.distance)/scale<.00002;
            }))cutArea+=area(face);
        }
        check(cutArea>.002f,"Requested rim cut is buried or has no visible extent");
    }
    return volume;
}
using Foot = std::vector<Vector2>;
float cross2(Vector2 a, Vector2 b, Vector2 c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
Foot footprint(const Volume &v) {
    Foot points;
    for (auto f : v.faces)
        for (auto p : f)
            points.push_back({p.x, p.z});
    std::sort(points.begin(), points.end(),
              [](auto a, auto b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    points.erase(
        std::unique(points.begin(), points.end(),
                    [](auto a, auto b) { return std::abs(a.x - b.x) < 1e-5 && std::abs(a.y - b.y) < 1e-5; }),
        points.end());
    Foot hull;
    for (auto p : points) {
        while (hull.size() > 1 && cross2(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    auto size = hull.size();
    for (auto it = points.rbegin() + 1; it != points.rend(); ++it) {
        while (hull.size() > size && cross2(hull[hull.size() - 2], hull.back(), *it) <= 0)
            hull.pop_back();
        hull.push_back(*it);
    }
    hull.pop_back();
    return hull;
}
bool overlaps(const Foot &a, const Foot &b) {
    for (const auto *p : {&a, &b})
        for (size_t i = 0; i < p->size(); ++i) {
            auto u = (*p)[i], v = (*p)[(i + 1) % p->size()];
            Vector2 n{v.y - u.y, u.x - v.x};
            float amin = 1e9f, amax = -1e9f, bmin = 1e9f, bmax = -1e9f;
            for (auto q : a) {
                float t = n.x * q.x + n.y * q.y;
                amin = std::min(amin, t);
                amax = std::max(amax, t);
            }
            for (auto q : b) {
                float t = n.x * q.x + n.y * q.y;
                bmin = std::min(bmin, t);
                bmax = std::max(bmax, t);
            }
            if (amax <= bmin + 1e-5 || bmax <= amin + 1e-5)
                return false;
        }
    return true;
}
struct FloorIndex {
    std::map<std::pair<int, int>, std::vector<Foot>> cells;
    static constexpr float step = 5;
    explicit FloorIndex(const CanyonAppearance &base) {
        for (auto t : base.triangles)
            if (!t.rock) {
                Foot p;
                float lx = 1e9f, hx = -1e9f, lz = 1e9f, hz = -1e9f;
                for (auto v : t.vertices) {
                    p.push_back({v.x, v.z});
                    lx = std::min(lx, v.x);
                    hx = std::max(hx, v.x);
                    lz = std::min(lz, v.z);
                    hz = std::max(hz, v.z);
                }
                for (int z = int(std::floor(lz / step)); z <= int(std::floor(hz / step)); ++z)
                    for (int x = int(std::floor(lx / step)); x <= int(std::floor(hx / step)); ++x)
                        cells[{x, z}].push_back(p);
            }
    }
    bool clear(const Volume &v, size_t &tests) const {
        auto p = footprint(v);
        for (int z = int(std::floor(v.bounds.min.z / step)); z <= int(std::floor(v.bounds.max.z / step)); ++z)
            for (int x = int(std::floor(v.bounds.min.x / step)); x <= int(std::floor(v.bounds.max.x / step));
                 ++x) {
                auto it = cells.find({x, z});
                if (it == cells.end())
                    continue;
                for (const auto &floor : it->second) {
                    ++tests;
                    if (overlaps(p, floor))
                        return false;
                }
            }
        return true;
    }
    std::vector<Polygon> trim(const Polygon &polygon) const {
        float lx=1e9f,hx=-1e9f,lz=1e9f,hz=-1e9f;
        for (auto p : polygon) {
            lx=std::min(lx,p.x); hx=std::max(hx,p.x);
            lz=std::min(lz,p.z); hz=std::max(hz,p.z);
        }
        std::set<std::array<float,6>> seen;
        std::vector<Volume> cutters;
        for (int z=int(std::floor(lz/step)); z<=int(std::floor(hz/step)); ++z)
            for (int x=int(std::floor(lx/step)); x<=int(std::floor(hx/step)); ++x) {
                auto found=cells.find({x,z});
                if (found==cells.end()) continue;
                for (const auto &f : found->second) {
                    std::array<float,6> key{f[0].x,f[0].y,f[1].x,f[1].y,f[2].x,f[2].y};
                    if (!seen.insert(key).second) continue;
                    Volume prism;
                    const float winding=cross2(f[0],f[1],f[2])>0 ? 1.f : -1.f;
                    for (size_t i=0;i<f.size();++i) {
                        auto a=f[i],b=f[(i+1)%f.size()];
                        auto n=Vector3Normalize(Vector3{(b.y-a.y)*winding,0,(a.x-b.x)*winding});
                        prism.planes.push_back({n,double(n.x)*a.x+double(n.z)*a.y});
                    }
                    cutters.push_back(std::move(prism));
                }
            }
        return exposed(polygon,cutters);
    }
};
Plane preciseVerticalSide(Vector3 a,Vector3 b) {
    const double x=double(a.z)-b.z,z=double(b.x)-a.x,length=std::hypot(x,z);
    check(length>0,"Zero projected prism edge");
    Plane p;p.preciseNormal={x/length,0,z/length};p.hasPreciseNormal=true;
    p.normal={float(p.preciseNormal[0]),0,float(p.preciseNormal[2])};p.distance=planeProjection(p,a);return p;
}
Polygon convexRoofFootprint(Polygon p) {
    std::sort(p.begin(),p.end(),[](auto a,auto b){return std::pair{a.x,a.z}<std::pair{b.x,b.z};});
    p.erase(std::unique(p.begin(),p.end(),[](auto a,auto b){return a.x==b.x && a.z==b.z;}),p.end());
    if(p.size()<3)return p;
    auto turn=[](Vector3 a,Vector3 b,Vector3 c){return (double(b.x)-a.x)*(double(c.z)-a.z)-(double(b.z)-a.z)*(double(c.x)-a.x);};
    Polygon hull;
    for(auto a:p){while(hull.size()>1 && turn(hull[hull.size()-2],hull.back(),a)<=0)hull.pop_back();hull.push_back(a);}
    const auto lower=hull.size();
    for(auto i=p.rbegin()+1;i!=p.rend();++i){while(hull.size()>lower && turn(hull[hull.size()-2],hull.back(),*i)<=0)hull.pop_back();hull.push_back(*i);}
    if(!hull.empty())hull.pop_back();std::reverse(hull.begin(),hull.end());return hull;
}
struct Wall {
    const std::vector<cliffDetail::Quad> &q;
    std::vector<float> s{0};
    explicit Wall(const std::vector<cliffDetail::Quad> &p) : q(p) {
        for (auto a : q)
            s.push_back(s.back() + distance(a.ab, a.bb));
    }
    Vector3 point(float d) const {
        d = std::clamp(d, 0.f, s.back());
        size_t i = std::min(q.size() - 1, size_t(std::upper_bound(s.begin(), s.end(), d) - s.begin() - 1));
        return Vector3Lerp(q[i].ab, q[i].bb, (d - s[i]) / (s[i + 1] - s[i]));
    }
    Vector3 facing(float d) const {
        d=std::clamp(d,0.f,s.back());
        const auto i=std::min(q.size()-1,size_t(std::upper_bound(s.begin(),s.end(),d)-s.begin()-1));
        return cliffDetail::normal(q[i]);
    }
    Vector3 tangent(float d, float span) const {
        return Vector3Normalize(sub(point(std::min(s.back(), d + span)), point(std::max(0.f, d - span))));
    }
    std::pair<float, float> locate(Vector3 p) const {
        float best = 1e9f, along = 0, depth = 0;
        for (size_t i = 0; i < q.size(); ++i) {
            auto a = q[i].ab, b = q[i].bb;
            a.y = b.y = p.y;
            auto e = sub(b, a);
            float t = std::clamp(dot(sub(p, a), e) / dot(e, e), 0.f, 1.f);
            auto on = add(a, mul(e, t));
            float d = distance(on, p);
            if (d < best) {
                best = d;
                along = std::lerp(s[i], s[i + 1], t);
                auto n = cliffDetail::normal(q[i]);
                n.y = 0;
                // Beyond a segment endpoint, the normal projection can be
                // small even for distant terrain. Use the actual nearest
                // contour distance, retaining only its inside/outside sign.
                depth = std::copysign(d,-dot(sub(p, on), Vector3Normalize(n)));
            }
        }
        return {along, depth};
    }
};
struct FrontRoofControl {std::vector<RoofGrade> grades;Plane front;};
FrontRoofControl capFrontRoof(const Volume &cap,const FormationDescriptor &descriptor,const Wall &wall) {
    Polygon perimeter;
    for(const auto &face:cap.faces)if(normal(face).y>.85f)perimeter.insert(perimeter.end(),face.begin(),face.end());
    check(perimeter.size()>=3,"Missing cap roof for rear grading");
    perimeter=convexRoofFootprint(std::move(perimeter));
    const float at=descriptor.at*wall.s.back();auto tangent=wall.tangent(at,descriptor.width*.45f);tangent.y=0;tangent=Vector3Normalize(tangent);
    auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));if(dot(outward,wall.facing(at))<0)outward=mul(outward,-1);
    double foremost=-1e9;for(auto q:perimeter)foremost=std::max(foremost,projection(outward,q));
    Plane front{mul(outward,-1),-(foremost-.6)};
    auto protectedRoof=clip(perimeter,front,true);
    check(protectedRoof.size()>=3,"Missing protected front roof strip");
    FrontRoofControl result;result.front=front;
    for(const auto &plane:cap.planes)if(plane.normal.y>.85f)result.grades.push_back({protectedRoof,plane});
    check(!result.grades.empty(),"Missing cap crown roof planes");return result;
}
void emit(cliffOptions::Mesh &m, const Polygon &p) {
    if (p.size() < 3 || area(p) < .00001f)
        return;
    for (size_t i = 1; i + 1 < p.size(); ++i) {
        if (Vector3Length(Vector3CrossProduct(sub(p[i], p[0]), sub(p[i + 1], p[0]))) > 1e-7)
            m.faces.push_back({p[0], p[i], p[i + 1]});
    }
    for (size_t i = 0; i < p.size(); ++i)
        m.polygonEdges.push_back({p[i], p[(i + 1) % p.size()]});
    m.quads += p.size() == 4;
    m.ngons += p.size() > 4;
}
float ray(const Volume &v, Vector3 from, Vector3 direction) {
    float enter = 0, leave = 1000;
    for (auto p : v.planes) {
        float a = float(p.distance - planeProjection(p, from)), b = float(planeProjection(p, direction));
        if (std::abs(b) < 1e-7) {
            if (a < -Epsilon)
                return 1000;
            continue;
        }
        float t = a / b;
        if (b < 0)
            enter = std::max(enter, t);
        else
            leave = std::min(leave, t);
        if (enter > leave)
            return 1000;
    }
    return leave >= 0 ? enter : 1000;
}
float triangleRay(const cliffOptions::Triangle &triangle, Vector3 from, Vector3 direction) {
    // Use the actual render vertices, but calculate in double precision. Float
    // barycentrics can miss both triangles when a ray hits their common edge.
    using D = std::array<double,3>;
    auto difference = [](Vector3 a, Vector3 b) { return D{double(a.x)-b.x,double(a.y)-b.y,double(a.z)-b.z}; };
    auto cross = [](D a,D b) { return D{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]}; };
    auto dot = [](D a,D b) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; };
    const D d{direction.x,direction.y,direction.z};
    const auto e1=difference(triangle[1],triangle[0]), e2=difference(triangle[2],triangle[0]);
    const auto p=cross(d,e2);
    const double determinant=dot(e1,p);
    if(std::abs(determinant)<1e-12) return 1000;
    const auto offset=difference(from,triangle[0]);
    const auto q=cross(offset,e1);
    const double u=dot(offset,p)/determinant, v=dot(d,q)/determinant;
    // Cover coordinate conversion at shared/outer edges (under 0.1 mm for
    // these faces), well below the separate 4 mm distance-agreement limit.
    if(u < -2e-6 || v < -2e-6 || u+v > 1+2e-6) return 1000;
    const double distance=dot(e2,q)/determinant;
    return distance>0 ? float(distance) : 1000;
}
Volume triangularBody(cliffOptions::Triangle top,float minimumUp=.1f) {
    auto n = Vector3Normalize(Vector3CrossProduct(sub(top[1],top[0]),sub(top[2],top[0])));
    if (n.y < 0) {
        std::swap(top[1],top[2]);
        n = mul(n,-1);
    }
    check(n.y > minimumUp, "Plateau top is not an upward surface");
    std::vector<Plane> planes{{n,projection(n,top[0])},{{0,-1,0},.12f}};
    const float winding = cross2({top[0].x,top[0].z},{top[1].x,top[1].z},{top[2].x,top[2].z}) > 0 ? 1.f : -1.f;
    for (int i=0;i<3;++i) {
        const auto a=top[i],b=top[(i+1)%3];
        const auto side=Vector3Normalize(Vector3{(b.z-a.z)*winding,0,(a.x-b.x)*winding});
        planes.push_back({side,projection(side,a)});
    }
    return polyhedron(planes,center({top[0],top[1],top[2]}));
}
void addPlateau(Experiment &result, const Wall &wall, const FloorIndex &floor, const CanyonAppearance &base,bool finishRoof,const CanyonAppearance *regionSource) {
    ConstructionTiming stageTiming("plateau");
    result.primaryVolumes = result.volumes.size();
    std::vector<Vector3> front, rear;
    std::array<float,7> stations{0,.12f,.235f,.49f,.745f,.90f,1};
    std::array<float,5> anchors{.035f,.235f,.49f,.745f,.97f};
    if(result.seededComposition) {
        for(size_t i=0;i<5;++i)anchors[i]=result.descriptors[i].at;
        stations={0,(anchors[0]+anchors[1])*.5f,anchors[1],anchors[2],anchors[3],(anchors[3]+anchors[4])*.5f,1};
    }
    float rearRoof=0;
    for(size_t i=0;i<5;++i)for(const auto &face:result.volumes[i].faces)
        for(auto p:face)rearRoof=std::max(rearRoof,p.y);
    for (float fraction : stations) {
        const float s=fraction*wall.s.back();
        auto tangent=wall.tangent(s,1.5f);
        tangent.y=0;
        const auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));
        auto direction=outward;
        if(dot(direction,result.seededComposition?wall.facing(s):cliffDetail::normal(wall.q.front()))<0) direction=mul(direction,-1);
        auto a=sub(wall.point(s),mul(direction,3.7f));
        auto b=sub(wall.point(s),mul(direction,9.f));
        auto from=a; from.y=20;
        float hit=1000;
        for(size_t i=0;i<5;++i)hit=std::min(hit,ray(result.volumes[i],from,{0,-1,0}));
        // Curved contours can bring another primary roof under this station.
        // Sampling only the nearest descriptor and clamping to its nominal
        // height created artificial low valleys behind taller neighbours.
        a.y=hit<1000?20-hit-.025f:rearRoof-.05f;
        // Rise into common elevated land behind the cap backs. Clamping each
        // rear station to its nearest cap left raised cap islands and exposed
        // rear skirts, despite a closed solid union.
        b.y=rearRoof+.10f+.06f*std::sin(fraction*Pi);
        front.push_back(a); rear.push_back(b);
        std::cout<<"PLATEAU_STATION at="<<fraction<<" front="<<a.x<<','<<a.y<<','<<a.z
                 <<" rear="<<b.x<<','<<b.y<<','<<b.z<<'\n';
    }
    // A single triangulated footprint avoids overlapping strip roofs when the
    // contour bends back on itself. Every top triangle shares canonical edges.
    Polygon control=front;control.insert(control.end(),rear.begin(),rear.end());
    // The plateau starts at the actual primary roof rims, not at an unrelated
    // inset ribbon. This also connects end masses whose rear corners would
    // otherwise sit outside that ribbon's footprint.
    for(size_t i=0;i<5;++i) {
        const auto &descriptor=result.descriptors[i];
        auto tangent=wall.tangent(descriptor.at*wall.s.back(),descriptor.width*.45f);tangent.y=0;tangent=Vector3Normalize(tangent);
        auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));
        if(dot(outward,result.seededComposition?wall.facing(descriptor.at*wall.s.back()):cliffDetail::normal(wall.q.front()))<0)outward=mul(outward,-1);
        const auto capCenter=mul(add(result.volumes[i].bounds.min,result.volumes[i].bounds.max),.5f);
        for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)
            for(auto p:face)if(dot(sub(p,capCenter),outward)<-.1f)control.push_back(p);
    }
    Volume controlVolume;controlVolume.faces={control};
    const auto hull=footprint(controlVolume);
    Polygon rim;
    for(auto p:hull) {
        const auto nearest=std::min_element(control.begin(),control.end(),[&](auto a,auto b) {
            return std::hypot(a.x-p.x,a.z-p.y)<std::hypot(b.x-p.x,b.z-p.y);
        });
        rim.push_back(*nearest);
    }
    auto middle=center(rim);middle.y=rearRoof+.05f;
    bool steep=false;
    for(size_t i=0;i<rim.size();++i)steep |= std::abs(normal({middle,rim[i],rim[(i+1)%rim.size()]}).y)<=.1f;
    if(result.seededComposition && steep) {
        std::cout<<"PLATEAU_ROOF_FIT slope_limit=1 reason=steep_hull_controls\n";
        // Closely spaced hull controls can come from different caps, with
        // unrelated elevations. Raise lower backing controls to a 1:1 upper
        // height envelope instead of creating an almost vertical roof sliver.
        const auto originalRim=rim;
        for(auto &p:rim)for(auto q:originalRim)p.y=std::max(p.y,q.y-planarDistance(p,q));
    }
    struct RoofPatch {Polygon outline;Plane plane;};
    std::vector<RoofPatch> constrainedRoof;
    std::vector<cliffOptions::Triangle> roof;
    if(result.blendedBacking) {
        std::vector<Vector3> controls,frontBoundary;
        std::vector<RoofGrade> grades;
        const bool finish=finishRoof && !std::getenv("DW_CLIFF_ROOF_PREVIOUS");
        const bool merged=result.seededComposition && finish && std::getenv("DW_CLIFF_ROOF_MERGED");
        const bool envelope=finish && !merged && std::getenv("DW_CLIFF_ROOF_ENVELOPE");
        const bool constrained=finish && !merged && !envelope && std::getenv("DW_CLIFF_ROOF_CONSTRAINED");
        result.finishedRoof=finish;
        std::cout<<"PLATEAU_ROOF_VARIANT mode="<<(merged?"merged_trial":envelope?"envelope_trial":constrained?"constrained_trial":finish?"extension":"previous")<<'\n';
        float commonHeight=0;
        for(size_t i=0;i<5;++i) {
            const auto &f=result.descriptors[i];
            const float at=f.at*wall.s.back();auto tangent=wall.tangent(at,f.width*.45f);tangent.y=0;tangent=Vector3Normalize(tangent);
            auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));
            if(dot(outward,wall.facing(at))<0)outward=mul(outward,-1);
            const auto capCenter=mul(add(result.volumes[i].bounds.min,result.volumes[i].bounds.max),.5f);
            std::array<Vector3,2> backEdge{};Vector3 rearNormal{};float rearmost=1e9f;
            for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)for(size_t k=0;k<face.size();++k) {
                const auto a=face[k],b=face[(k+1)%face.size()];
                if(planarDistance(a,b)<.25f)continue;
                const float score=dot(sub(mul(add(a,b),.5f),capCenter),outward);
                if(score<rearmost){rearmost=score;backEdge={a,b};rearNormal=normal(face);}
            }
            check(rearmost<1e8f,"Missing rear roof edge for plateau blend");
            float minimum=1000;
            for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)for(auto q:face)minimum=std::min(minimum,q.y);
            if(merged) {
                auto front=capFrontRoof(result.volumes[i],f,wall);
                for(auto q:front.grades.front().protectedRoof)if(std::abs(planeProjection(front.front,q)-front.front.distance)<.0001){controls.push_back(q);frontBoundary.push_back(q);}
                grades.insert(grades.end(),front.grades.begin(),front.grades.end());commonHeight=std::max(commonHeight,rearRoof+.08f);
                continue;
            }
            if(envelope) {
                // Match every upward cap perimeter rather than two rear
                // corners. Sample the union because neighbouring roofs can
                // overlap in projection at different elevations.
                for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)
                    for(auto p:face) {
                        p.y=20;float hit=1000;
                        for(size_t main=0;main<5;++main)hit=std::min(hit,ray(result.volumes[main],p,{0,-1,0}));
                        check(hit<1000,"Missing envelope cap roof anchor");
                        p.y=20-hit+.001f;
                        controls.push_back(p);commonHeight=std::max(commonHeight,p.y+.06f);
                    }
                continue;
            }
            for(auto corner:backEdge) {
                auto p=Vector3Lerp(corner,capCenter,.02f);p.y=20;
                float hit=1000;for(size_t main=0;main<5;++main)hit=std::min(hit,ray(result.volumes[main],p,{0,-1,0}));check(hit<1000,"Missing primary roof blend anchor");
                p.y=20-hit+.025f;
                // Keep controls inside both actual rear corners, so moving a
                // collar behind the cap cannot leave a roof-height gap.
                if(finish && !constrained) {
                    auto collar=sub(corner,mul(outward,.45f));
                    collar.y=corner.y+(rearNormal.x*outward.x+rearNormal.z*outward.z)*.45f/rearNormal.y;
                    controls.push_back(collar);
                } else controls.push_back(p);
                frontBoundary.push_back(p);
            }
            if(constrained) {
                const auto corner=mul(add(backEdge[0],backEdge[1]),.5f);
                auto collar=sub(corner,mul(outward,.45f));
                collar.y=std::max(minimum+.025f,corner.y+(rearNormal.x*outward.x+rearNormal.z*outward.z)*.45f/rearNormal.y);
                controls.push_back(collar);
            }
            commonHeight=std::max(commonHeight,minimum+.06f);
        }
        const auto capControls=controls.size();
        if(envelope)std::cout<<"PLATEAU_ENVELOPE controls="<<capControls<<" rear_height="<<commonHeight<<'\n';
        const std::vector<float> rearStations=finish?std::vector<float>{0,.25f,.5f,.75f,1}:std::vector<float>{0,.49f,1};
        for(float fraction:rearStations) {
            const auto at=fraction*wall.s.back();auto tangent=wall.tangent(at,1.5f);tangent.y=0;tangent=Vector3Normalize(tangent);
            auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));if(dot(outward,wall.facing(at))<0)outward=mul(outward,-1);
            float depth=8.f+.65f*std::sin(fraction*Pi*3+.7f);
            const auto nearest=size_t(std::min_element(anchors.begin(),anchors.end(),[&](auto a,auto b){return std::abs(a-fraction)<std::abs(b-fraction);})-anchors.begin());
            for(const auto &face:result.volumes[nearest].faces)for(auto p:face)depth=std::max(depth,-dot(sub(p,wall.point(at)),outward)+.5f);
            auto p=sub(wall.point(at),mul(outward,depth));
            p.y=commonHeight+.12f;
            if(!base.triangles.empty()) {
                const auto hit=base.trace({p.x,30,p.z},{p.x,-1,p.z});
                if(hit.hit) {const float height=30-31*hit.t;if(height>1.2f){if(merged)commonHeight=std::max(commonHeight,height);else p.y=height-.08f;}}
            }
            controls.push_back(p);
        }
        Vector3 rimCentre{},landCentre{};
        for(size_t i=0;i<capControls;++i)rimCentre=add(rimCentre,mul(controls[i],1.f/capControls));
        for(size_t i=capControls;i<controls.size();++i)landCentre=add(landCentre,mul(controls[i],1.f/rearStations.size()));
        middle=Vector3Lerp(rimCentre,landCentre,.65f);middle.y=commonHeight;
        controls.push_back(middle);
        if(merged) {
            for(auto &p:controls)p.y=commonHeight;
            auto outline=convexRoofFootprint(controls);
            auto cells=gradePlateauRoof(outline,commonHeight,grades,1,!std::getenv("DW_CLIFF_NO_GRADE_PRUNE"));
            const size_t gradedCells=cells.size();
            if(std::getenv("DW_CLIFF_ROOF_REGION")) {
                ConstructionChecks requiredRegionChecks;
                PlateauRegion capRims;std::vector<RoofGrade> lowerCaps;std::vector<Polygon> capDomains;
                for(size_t i=0;i<5;++i) {
                    Polygon perimeter;
                    for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f) {
                        Plane plane{normal(face),projection(normal(face),face.front())};
                        for(const auto &candidate:result.volumes[i].planes)if(candidate.normal.y>.85f &&
                            std::all_of(face.begin(),face.end(),[&](auto p){return std::abs(planeProjection(candidate,p)-candidate.distance)<.00005;})){plane=candidate;break;}
                        lowerCaps.push_back({face,plane,2});
                        perimeter.insert(perimeter.end(),face.begin(),face.end());
                        for(size_t k=0;k<face.size();++k)capRims.boundary.push_back({face[k],face[(k+1)%face.size()],plane,false});
                    }
                    capDomains.push_back(convexRoofFootprint(std::move(perimeter)));
                }
                const auto region=planPlateauRegion(regionSource?*regionSource:base,wall.q,capDomains);
                if(const auto path=std::getenv("DW_CLIFF_REGION_PROBE"))writePlateauRegion(path,region);
                std::cout<<"PLATEAU_REGION_PLAN key="<<region.key<<" components="<<region.components<<" source_faces="<<region.sourceFaces
                         <<" neighbour_walls="<<region.neighbourWalls<<" area_m2="<<region.projectedArea<<" boundary="<<region.boundary.size()<<'\n';
                auto domains=region.domains;
                domains.insert(domains.end(),capDomains.begin(),capDomains.end());
                std::vector<Polygon> holes;for(const auto &grade:grades)holes.push_back(grade.protectedRoof);
                if(std::getenv("DW_CLIFF_ROOF_CHUNKS")) {
                    auto contact=frontBoundary;
                    std::stable_sort(contact.begin(),contact.end(),[&](auto a,auto b){return wall.locate(a).first<wall.locate(b).first;});
                    for(size_t k=1;k<contact.size();++k) {
                        const auto a=contact[k-1],b=contact[k];if(planarDistance(a,b)<.0001f)continue;
                        const auto outward=wall.facing(wall.locate(mul(add(a,b),.5f)).first);
                        holes.push_back(convexRoofFootprint({a,b,add(b,mul(outward,16)),add(a,mul(outward,16))}));
                    }
                    PlateauChunkSettings chunkSettings;
                    chunkSettings.continuous=!std::getenv("DW_CLIFF_CHUNK_SOURCE_PLANES");
                    check(!std::getenv("DW_CLIFF_SOURCE_PARTITION") || !chunkSettings.continuous,"Source ownership requires source-plane chunks");
                    check(!std::getenv("DW_CLIFF_SOURCE_REGULARIZE") || std::getenv("DW_CLIFF_SOURCE_PARTITION"),"Source regularization requires shared ownership");
                    auto chunked=buildPlateauChunks(region,capDomains,grades,lowerCaps,holes,chunkSettings,std::span<const Volume>(result.volumes.data(),5));
                    if(!chunked.retainedSourceCells.empty()) {
                        size_t index=0;
                        for(auto &chunk:chunked.chunks) {
                            std::vector<GradedRoofCell> changed;
                            for(auto &cell:chunk.cells)if(!chunked.retainedSourceCells[index++])changed.push_back(std::move(cell));
                            chunk.cells=std::move(changed);
                        }
                        check(index==chunked.retainedSourceCells.size(),"Source reuse selection does not match its construction field");
                    }
                    if(const auto path=std::getenv("DW_CLIFF_CHUNK_PROBE"))writePlateauChunks(path,chunked);
                    cells.clear();float nearest=1e30f;bool target=false;
                    float minimum=0;for(size_t i=0;i<5;++i){float low=1e9f;for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)for(auto p:face)low=std::min(low,p.y);minimum=std::max(minimum,low);}
                    for(const auto &chunk:chunked.chunks)for(const auto &cell:chunk.cells) {
                        auto p=center(cell.outline);const auto n=planeNormal(cell.roof);p.y=float((cell.roof.distance-n[0]*p.x-n[2]*p.z)/n[1]);
                        const float d=planarDistance(p,middle);
                        if(p.y>=minimum && d<nearest){nearest=d;result.plateauCenter=p;target=true;}
                        cells.push_back(cell);
                    }
                    if(target)middle=result.plateauCenter;
                    commonHeight=chunked.landHeight;
                    std::cout<<"PLATEAU_CHUNKS count="<<chunked.chunks.size()<<" regional_faces="<<chunked.regionalFaces
                             <<" local_faces="<<chunked.localFaces<<" source_planes="<<!chunkSettings.continuous<<" grid_triangles="<<chunked.gridTriangles<<" grid_nodes="<<chunked.gridNodes<<" roof_cells="<<cells.size()<<" node_support_m=6 maximum_support_m=7.414214 side_m=16 grid_m=1\n";
                } else {
                domains=plateauRegionFootprint(domains);
                const auto footprintMesh=meshPlateauFootprint(domains);
                const auto footprintAudit=auditStrictSurface(footprintMesh);
                bool linksValid=true;
                if(footprintAudit.nonmanifoldVertices)for(const auto &component:splitSurfaceComponents(footprintMesh))linksValid &= auditStrictSurface(component).nonmanifoldVertices==0;
                check(!footprintAudit.exact.nonmanifoldEdges && linksValid && !footprintAudit.selfIntersections &&
                      !footprintAudit.coplanarOverlaps && !footprintAudit.exact.degenerateFaces && !footprintAudit.exact.windingErrors,
                      "Regional external footprint is invalid");
                const auto external=surfaceBoundary(footprintMesh,true);
                auto neighbours=plateauRegionConstraints(region,external);
                auto capEdges=plateauRegionConstraints(capRims,external);
                neighbours.insert(neighbours.end(),capEdges.begin(),capEdges.end());
                domains=plateauRegionFootprint(domains,holes);
                grades.insert(grades.end(),neighbours.begin(),neighbours.end());
                const float regionHeight=std::max(commonHeight,region.maximumHeight+.04f);
                cells.clear();double largest=0;
                for(auto &domain:domains) {
                    double area=0;for(size_t k=0;k<domain.size();++k)area+=double(domain[k].x)*domain[(k+1)%domain.size()].z-double(domain[k].z)*domain[(k+1)%domain.size()].x;
                    if(std::abs(area)>largest){largest=std::abs(area);middle=center(domain);middle.y=regionHeight;}
                }
                cells=samplePlateauRegionRoof(domains,regionHeight,grades,1,lowerCaps);
                commonHeight=regionHeight;
                }
                std::cout<<"PLATEAU_REGION key="<<region.key<<" components="<<region.components<<" source_faces="<<region.sourceFaces
                         <<" selected_walls="<<region.selectedWalls<<" neighbour_walls="<<region.neighbourWalls<<" area_m2="<<region.projectedArea
                         <<" boundary="<<region.boundary.size()<<" shared_domains="<<domains.size()<<" graded_cells="<<cells.size()<<'\n';
            }
            if(std::getenv("DW_CLIFF_ROOF_COLLAR") && !std::getenv("DW_CLIFF_ROOF_REGION")) {
                std::vector<Plane> interfaces;
                for(size_t k=0;k<outline.size();++k) {
                    const auto a=outline[k],b=outline[(k+1)%outline.size()];const auto side=preciseVerticalSide(a,b);
                    const auto midpoint=mul(add(a,b),.5f);const auto location=wall.locate(midpoint).first;
                    if(dot(side.normal,wall.facing(location))<.25f)interfaces.push_back(side);
                }
                float lx=1e9f,hx=-1e9f,lz=1e9f,hz=-1e9f;
                for(auto p:outline){lx=std::min(lx,p.x);hx=std::max(hx,p.x);lz=std::min(lz,p.z);hz=std::max(hz,p.z);}
                std::vector<RoofGrade> terrain;
                for(const auto &t:base.triangles)if(t.rock) {
                    const auto &v=t.vertices;
                    if(std::max({v[0].x,v[1].x,v[2].x})<lx || std::min({v[0].x,v[1].x,v[2].x})>hx ||
                       std::max({v[0].z,v[1].z,v[2].z})<lz || std::min({v[0].z,v[1].z,v[2].z})>hz)continue;
                    const std::array<double,3> a{double(v[1].x)-v[0].x,double(v[1].y)-v[0].y,double(v[1].z)-v[0].z};
                    const std::array<double,3> b{double(v[2].x)-v[0].x,double(v[2].y)-v[0].y,double(v[2].z)-v[0].z};
                    std::array<double,3> n{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};
                    const double length=std::sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);if(length==0 || n[1]/length<=.65)continue;
                    Plane roof;roof.hasPreciseNormal=true;for(auto &q:n)q/=length;
                    roof.preciseNormal=n;roof.normal={float(n[0]),float(n[1]),float(n[2])};roof.distance=planeProjection(roof,v[0]);
                    terrain.push_back({{v[0],v[1],v[2]},roof});
                }
                if(std::getenv("DW_CLIFF_ROOF_BOUNDARY_GRADES")) {
                    auto boundary=plateauBoundaryGrades(outline,terrain,interfaces);
                    std::cout<<"PLATEAU_BOUNDARY_GRADES segments="<<boundary.size()<<'\n';
                    grades.insert(grades.end(),boundary.begin(),boundary.end());
                    cells=gradePlateauRoof(outline,commonHeight,grades,1,!std::getenv("DW_CLIFF_NO_GRADE_PRUNE"));
                } else cells=blendPlateauBoundary(std::move(cells),terrain,interfaces);
                std::cout<<"PLATEAU_COLLAR source_roofs="<<terrain.size()<<" interfaces="<<interfaces.size()<<" input_cells="<<gradedCells<<" output_cells="<<cells.size()<<'\n';
                if(const auto path=std::getenv("DW_CLIFF_INTERFACE_PROBE")) {
                    std::ofstream probe(path);probe.precision(17);
                    probe<<"edge,t,x,z,retained_height,selected_roof_height,body_height,cap_height,union_height\n";
                    auto height=[](const Polygon &domain,const Plane &roof,Vector3 p) {
                        for(size_t k=0;k<domain.size();++k) {
                            const auto side=preciseVerticalSide(domain[k],domain[(k+1)%domain.size()]);
                            if(planeProjection(side,p)>side.distance+.00002)return -1000.f;
                        }
                        const auto n=planeNormal(roof);return float((roof.distance-n[0]*p.x-n[2]*p.z)/n[1]);
                    };
                    for(size_t k=0;k<outline.size();++k) {
                        const auto a=outline[k],b=outline[(k+1)%outline.size()],side=preciseVerticalSide(a,b).normal;
                        if(dot(side,wall.facing(wall.locate(mul(add(a,b),.5f)).first))>=.25f)continue;
                        for(int sample=0;sample<64;++sample) {
                            const float t=(sample+.5f)/64;const auto p=Vector3Lerp(a,b,t);
                            const auto hit=base.trace({p.x,30,p.z},{p.x,-1,p.z});
                            const float retained=hit.hit?30-31*hit.t:-1000;
                            float selected=-1000,body=-1000;
                            for(const auto &source:terrain)selected=std::max(selected,height(source.protectedRoof,source.roof,p));
                            for(const auto &cell:cells)body=std::max(body,height(cell.outline,cell.roof,p));
                            const float cap=30-traceVolumes(result.volumes,{p.x,30,p.z},{0,-1,0});
                            probe<<k<<','<<t<<','<<p.x<<','<<p.z<<','<<retained<<','<<selected<<','<<body<<','<<cap<<','<<std::max({retained,body,cap})<<'\n';
                        }
                    }
                    if(!probe)throw std::runtime_error("Cannot write plateau interface probe");
                }
            }
            for(auto &cell:cells)constrainedRoof.push_back({std::move(cell.outline),cell.roof});
            std::cout<<"PLATEAU_GRADED protected_front_m=.6 slope=1 cells="<<constrainedRoof.size()<<" land_height="<<commonHeight<<'\n';
        } else roof=triangulatePlateauRoof(controls);
        if(constrained) {
            auto along=[&](Vector3 p) {
                auto [s,d]=wall.locate(p);
                if(s==0)s+=dot(sub(p,wall.point(0)),wall.tangent(0,1));
                else if(s==wall.s.back())s+=dot(sub(p,wall.point(s)),wall.tangent(s,1));
                return s;
            };
            std::stable_sort(frontBoundary.begin(),frontBoundary.end(),[&](auto a,auto b){return along(a)<along(b);});
            Polygon outline=frontBoundary;
            for(size_t i=capControls+rearStations.size();i>capControls;)outline.push_back(controls[--i]);
            const auto domain=triangulatePlateauBoundary(outline);
            double requested=0,emitted=0;
            for(const auto &t:domain)requested+=std::abs(cross2({t[0].x,t[0].z},{t[1].x,t[1].z},{t[2].x,t[2].z}))*.5;
            for(const auto &t:roof) {
                const auto n=normal({t[0],t[1],t[2]});const double distance=projection(n,t[0]);
                std::vector<Polygon> pieces;
                for(const auto &cell:domain) {
                    Volume cutter;
                    for(int k=0;k<3;++k){const auto a=cell[k],b=cell[(k+1)%3];const auto side=Vector3Normalize(Vector3{a.z-b.z,0,b.x-a.x});cutter.planes.push_back({side,projection(side,a)});}
                    auto part=clipToVolume({t[0],t[1],t[2]},cutter);
                    if(part.size()>=3 && area(part)>1e-10f)pieces.push_back(std::move(part));
                }
                for(auto part:consolidate(std::move(pieces),n)) {
                    double projected=0;float longest=0;
                    for(size_t k=1;k+1<part.size();++k)projected+=std::abs(cross2({part[0].x,part[0].z},{part[k].x,part[k].z},{part[k+1].x,part[k+1].z}))*.5;
                    for(auto a:part)for(auto b:part)longest=std::max(longest,planarDistance(a,b));
                    if(projected<1e-10 || longest==0 || 2*projected/longest<.00004)continue;
                    // Keep the original plane through every clipping stage.
                    // Deriving it again from skinny float triangles can turn a
                    // planar cell into several slightly incompatible roofs.
                    for(auto &p:part)p.y=float((distance-double(n.x)*p.x-double(n.z)*p.z)/n.y);
                    constrainedRoof.push_back({std::move(part),{n,distance}});emitted+=projected;
                }
            }
            check(std::abs(requested-emitted)<.0001+requested*.00001,"Constrained plateau footprint lost area or overlaps");
            std::cout<<"PLATEAU_DOMAIN requested_area_m2="<<requested<<" emitted_area_m2="<<emitted<<" constrained=PASS\n";
        }
        std::cout<<"PLATEAU_BLEND controls="<<controls.size()<<" roof_cells="<<roof.size()<<" centre_height="<<commonHeight<<'\n';
    } else for(size_t i=0;i<rim.size();++i)roof.push_back({middle,rim[i],rim[(i+1)%rim.size()]});
    result.plateauCenter=middle;
    if(result.blendedBacking) {
        struct Patch {Polygon outline;Plane roof;bool covered=false;};
        std::vector<Patch> patches;
        for(const auto &cell:constrainedRoof)patches.push_back({cell.outline,cell.plane});
        if(constrainedRoof.empty())for(auto top:roof){auto n=normal({top[0],top[1],top[2]});
            if(n.y<=.1f) {std::cout<<"PLATEAU_STEEP up="<<n.y;for(auto p:top)std::cout<<" p="<<p.x<<','<<p.y<<','<<p.z;std::cout<<'\n';}
            check(n.y>1e-7f,"Blended roof cell has no upward projection");patches.push_back({{top[0],top[1],top[2]},{n,projection(n,top[0])}});}
        // Preserve the accepted cap surfaces. The backing may continue behind
        // them, but cannot form an extra wedge above a primary roof footprint.
        const bool merged=result.seededComposition && result.finishedRoof && std::getenv("DW_CLIFF_ROOF_MERGED");
        if(!merged)for(size_t i=0;i<5;++i)for(const auto &face:result.volumes[i].faces) {
            const auto n=normal(face);if(n.y<=.85f)continue;
            const Plane cap{n,projection(n,face[0])};Volume domain;
            const bool filledColumn=std::all_of(result.volumes[i].planes.begin(),result.volumes[i].planes.end(),[](const auto &plane) {
                return plane.normal.y>=0 || std::abs(plane.normal.x)+std::abs(plane.normal.z)<1e-7f;
            });
            for(size_t k=0;k<face.size();++k) {
                auto a=face[k],b=face[(k+1)%face.size()];
                auto side=Vector3Normalize(Vector3{a.z-b.z,0,b.x-a.x});domain.planes.push_back({side,projection(side,a)});
            }
            std::vector<Patch> next;
            for(const auto &patch:patches) {
                const auto inside=clipToVolume(patch.outline,domain);
                if(inside.size()<3 || area(inside)<1e-10f){next.push_back(patch);continue;}
                for(auto outside:exposed(patch.outline,{domain}))next.push_back({std::move(outside),patch.roof,patch.covered});
                const bool above=std::any_of(inside.begin(),inside.end(),[&](auto p){return projection(n,p)>cap.distance+Epsilon;});
                if(!above){next.push_back({inside,patch.roof,patch.covered || filledColumn});continue;}
                auto low=clip(inside,cap,true),high=clip(inside,cap,false);
                if(low.size()>=3 && area(low)>1e-10f)next.push_back({std::move(low),patch.roof,patch.covered || filledColumn});
                if(high.size()>=3 && area(high)>1e-10f) {
                    for(auto &p:high)p.y=float((cap.distance-double(n.x)*p.x-double(n.z)*p.z)/n.y);
                    next.push_back({std::move(high),cap,patch.covered || filledColumn});
                }
            }
            patches=std::move(next);
        }
        const bool sourcePlaneVolumes=std::getenv("DW_CLIFF_CHUNK_SOURCE_PLANES")!=nullptr;
        size_t volumePrecisionCorrections=0;
        for(const auto &patch:patches)for(auto part:floor.trim(patch.outline)) {
            const bool exactChunkCells=std::getenv("DW_CLIFF_ROOF_CHUNKS")!=nullptr;
            if(part.size()<3)continue;
            part=convexRoofFootprint(std::move(part));
            if(part.size()<3 || area(part)<(exactChunkCells?0.f:1e-9f))continue;
            float projected=0,longest=0;
            for(size_t k=1;k+1<part.size();++k)projected+=std::abs(cross2({part[0].x,part[0].z},{part[k].x,part[k].z},{part[k+1].x,part[k+1].z}));
            for(auto a:part)for(auto b:part)longest=std::max(longest,planarDistance(a,b));
            // A positive cell may be a finite bridge between roof regions.
            // Dropping it by width alone recreates point-only solid contacts.
            // Convexity, volume, protected floor and final exact checks remain.
            if(longest==0 || projected<=0 || (!exactChunkCells && projected/longest<.00004f))continue;
            if(std::getenv("DW_CLIFF_ROOF_REGION") && !patch.covered && patch.roof.normal.y<=.1f) {
                std::cout<<"PLATEAU_REGION_STEEP up="<<patch.roof.normal.y;
                for(auto p:part)std::cout<<" p="<<p.x<<','<<p.y<<','<<p.z;
                std::cout<<'\n';
            }
            check(patch.covered || patch.roof.normal.y>.1f,"Exposed blended roof cell is too steep");
            std::vector<Plane> planes{patch.roof,{{0,-1,0},.12f}};
            for(size_t k=0;k<part.size();++k) {
                const auto a=part[k],b=part[(k+1)%part.size()];
                auto side=preciseVerticalSide(a,b);
                for(auto p:part)side.distance=std::max(side.distance,planeProjection(side,p));
                planes.push_back(side);
            }
            Volume solid;solid.planes=std::move(planes);
            Polygon top=part;
            const auto roofNormal=planeNormal(patch.roof);
            for(auto &p:top)p.y=float((patch.roof.distance-roofNormal[0]*p.x-roofNormal[2]*p.z)/roofNormal[1]);
            solid.faces.push_back(top);auto bottom=top;for(auto &p:bottom)p.y=-.12f;std::reverse(bottom.begin(),bottom.end());solid.faces.push_back(bottom);
            for(size_t k=0;k<top.size();++k){auto a=top[k],b=top[(k+1)%top.size()],loA=a,loB=b;loA.y=loB.y=-.12f;solid.faces.push_back({a,loA,loB,b});}
            solid.bounds={{1e9f,1e9f,1e9f},{-1e9f,-1e9f,-1e9f}};
            for(const auto &face:solid.faces)for(auto p:face) {
                solid.bounds.min={std::min(solid.bounds.min.x,p.x),std::min(solid.bounds.min.y,p.y),std::min(solid.bounds.min.z,p.z)};
                solid.bounds.max={std::max(solid.bounds.max.x,p.x),std::max(solid.bounds.max.y,p.y),std::max(solid.bounds.max.z,p.z)};
                check(contains(solid,p,.00003f),"Blended prism is not convex or planar");
            }
            check(solid.bounds.max.y>solid.bounds.min.y,"Blended prism has no solid depth");
            using PointKey=std::array<float,3>;
            std::map<std::pair<PointKey,PointKey>,std::pair<int,int>> edges;
            double volume=0;const auto origin=center(top);
            for(const auto &face:solid.faces) {
                for(size_t k=0;k<face.size();++k) {
                    auto a=face[k],b=face[(k+1)%face.size()];PointKey ka{a.x,a.y,a.z},kb{b.x,b.y,b.z};
                    check(ka!=kb,"Blended prism has a collapsed edge");const int sign=ka<kb?1:-1;if(kb<ka)std::swap(ka,kb);
                    auto &edge=edges[{ka,kb}];++edge.first;edge.second+=sign;
                }
                for(size_t k=1;k+1<face.size();++k)volume+=projection(sub(face[0],origin),Vector3CrossProduct(sub(face[k],origin),sub(face[k+1],origin)))/6.;
            }
            for(const auto &[edge,uses]:edges)check(uses.first==2 && uses.second==0,"Blended prism is not closed and consistently wound");
            if(sourcePlaneVolumes) {
                const auto stable=double(signedColumnVolume(top,-.12f));
                volumePrecisionCorrections+=volume<=1e-10 && stable>1e-10;volume=stable;
                if(volume<=1e-10) {
                    std::cout<<"PLATEAU_COLUMN_VOLUME_REJECT volume="<<volume<<" minimum=1e-10";
                    for(auto p:top)std::cout<<" p="<<p.x<<','<<p.y<<','<<p.z;std::cout<<'\n';
                    if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")) {
                        cliffOptions::Mesh witness;for(const auto &face:solid.faces)for(size_t k=1;k+1<face.size();++k)witness.faces.push_back({face[0],face[k],face[k+1]});
                        writeSurfaceProbe(path,witness,{solid},auditStrictSurface(witness));
                    }
                }
            }
            check(volume>1e-10,"Blended prism has non-positive volume");
            check(floor.clear(solid,result.clearanceTests),"Blended plateau overlaps protected floor");
            result.volumes.push_back(std::move(solid));++result.plateauVolumes;
            for(size_t k=1;k+1<part.size();++k)if(area({part[0],part[k],part[k+1]})>1e-9f)
                result.plateauTops.push_back({part[0],part[k],part[k+1]});
        }
        if(sourcePlaneVolumes)std::cout<<"PLATEAU_VOLUME_PRECISION corrected_classifications="<<volumePrecisionCorrections<<" minimum_volume=1e-10\n";
        std::cout<<"PLATEAU_CAP_BLEND roof_patches="<<patches.size()<<" prisms="<<result.plateauVolumes<<'\n';
        return;
    }
    for(const auto &top:roof) {
        // Convex roof envelopes may span a playable recess. Clip those domains
        // out before constructing closed solids; never move the floor to fit.
        for(const auto &part:floor.trim({top[0],top[1],top[2]}))for(size_t k=1;k+1<part.size();++k) {
            if(area({part[0],part[k],part[k+1]})<1e-9f)continue;
            const auto clipped=cliffOptions::Triangle{part[0],part[k],part[k+1]};
            const float projected=std::abs(cross2({clipped[0].x,clipped[0].z},{clipped[1].x,clipped[1].z},{clipped[2].x,clipped[2].z}));
            const float longest=std::max({planarDistance(clipped[0],clipped[1]),planarDistance(clipped[1],clipped[2]),planarDistance(clipped[2],clipped[0])});
            if(projected/longest<.00004f)continue;
            Volume body;
            try{body=triangularBody(clipped);}catch(const std::exception &e) {
                std::cerr<<"PLATEAU_BODY_FAILURE altitude="<<projected/longest<<" area="<<projected*.5f<<" reason="<<e.what()<<'\n';
                throw;
            }
            check(floor.clear(body,result.clearanceTests),"Plateau body overlaps protected floor");
            result.volumes.push_back(std::move(body));result.plateauTops.push_back(clipped);++result.plateauVolumes;
        }
    }
}
std::vector<cliffOptions::Triangle> connectShoulder(Experiment &result,const Wall &wall,const FloorIndex &floor) {
    // The union may be watertight yet retain a V-shaped footprint notch between
    // unequal roof heights. Join the actual roof edges, including their heights,
    // with a sloped solid rather than accepting a closed recessed boundary.
    auto edge=[&](size_t volume,float f0,float d0,float f1,float d1) {
        std::array<Vector3,2> best{};float score=1e9f;
        auto error=[&](Vector3 p,float f,float d) {
            auto [s,depth]=wall.locate(p);
            return (s-f*wall.s.back())*(s-f*wall.s.back())+(depth-d)*(depth-d);
        };
        for(const auto &face:result.volumes[volume].faces)if(normal(face).y>.85f)
            for(size_t i=0;i<face.size();++i)for(int reverse:{0,1}) {
                auto a=face[i],b=face[(i+1)%face.size()];if(reverse)std::swap(a,b);
                const float value=error(a,f0,d0)+error(b,f1,d1);
                if(value<score){score=value;best={a,b};}
            }
        check(score<1e8f,"No roof edge available for plateau connector");
        return best;
    };
    const auto a=edge(2,.500f,.85f,.519f,1.17f);
    const auto b=edge(6,.533f,1.25f,.584f,.535f);
    const auto left=edge(1,.3466f,4.433f,.3466f,2.738f);
    const auto dominant=edge(2,.3466f,4.001f,.3501f,5.499f);
    std::vector<cliffOptions::Triangle> tops{{a[0],a[1],b[0]},{a[0],b[0],b[1]},
                                            {left[0],left[1],dominant[0]},
                                            {left[0],dominant[0],dominant[1]}};
    for(auto &top:tops) {
        if(normal({top[0],top[1],top[2]}).y<0)std::swap(top[1],top[2]);
        auto solid=triangularBody(top,.005f);
        check(floor.clear(solid,result.clearanceTests),"Plateau connector overlaps protected floor");
        result.volumes.push_back(std::move(solid));++result.joinConnectors;
    }
    return tops;
}
} // namespace
float traceMesh(const cliffOptions::Mesh &mesh, Vector3 from, Vector3 direction) {
    float closest = 1000;
    for (const auto &triangle : mesh.faces)
        closest = std::min(closest, triangleRay(triangle, from, direction));
    return closest;
}
float traceVolumes(const std::vector<Volume> &volumes, Vector3 from, Vector3 direction) {
    float closest=1000;
    for(const auto &v:volumes) closest=std::min(closest,ray(v,from,direction));
    return closest;
}
Polygon clipToVolume(Polygon face,const Volume &volume) {
    for(auto plane:volume.planes) face=clip(face,plane,true);
    return face;
}
std::vector<Polygon> exposed(Polygon face, const std::vector<Volume> &volumes, int owner) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    const double clipEpsilon=preciseCoreCsg?1e-9:Epsilon;
#else
    constexpr auto clipEpsilon=Epsilon;
#endif
    std::vector<Polygon> parts{face};
    auto faceNormal = normal(face);
    for (size_t i = 0; i < volumes.size() && !parts.empty(); ++i) {
        if (int(i) == owner)
            continue;
        std::vector<Polygon> keep;
        for (const auto &part : parts) {
            // A convex polygon wholly outside one solid half-space cannot
            // intersect that solid. Avoid constructing/clipping temporary
            // polygons for the many unrelated terrain/roof cells. Use the
            // same plane epsilon as clipping; touching faces still take the
            // full ownership/coplanar path below.
            const bool separated=std::any_of(volumes[i].planes.begin(),volumes[i].planes.end(),[&](const auto &plane) {
                return std::all_of(part.begin(),part.end(),[&](auto p) {
                    return planeProjection(plane,p)>plane.distance+clipEpsilon;
                });
            });
            if(separated) {keep.push_back(part);continue;}
            Polygon inside = part;
            bool coplanar = false;
            for (auto plane : volumes[i].planes)
                if (dot(faceNormal, plane.normal) > .99999f &&
                    // Coplanarity belongs to the original source face.
                    // A clipped fragment near a crossing edge can lie within
                    // epsilon of a different plane without sharing that plane.
                    std::all_of(face.begin(), face.end(), [&](auto p) {
                        return std::abs(planeProjection(plane, p) - plane.distance) < Epsilon;
                    })) {
                    coplanar = true;
                    break;
                }
            if (coplanar && (owner == -2 || (owner >= 0 && int(i) > owner))) {
                keep.push_back(part);
                continue;
            }
            auto intersection = part;
            for (auto plane : volumes[i].planes) {
                intersection = clip(intersection, plane, true);
                if (intersection.size() < 3)
                    break;
            }
            if (intersection.size() < 3 || area(intersection) < .0000000001f) {
                keep.push_back(part);
                continue;
            }
            for (auto plane : volumes[i].planes) {
                Polygon outside;
                if (std::any_of(inside.begin(), inside.end(),
                                [&](auto p) { return planeProjection(plane, p) > plane.distance + clipEpsilon; }))
                    outside = clip(inside, plane, false);
                if (outside.size() >= 3 && area(outside) > .0000000001f)
                    keep.push_back(std::move(outside));
                inside = clip(inside, plane, true);
                if (inside.size() < 3)
                    break;
            }
        }
        parts = std::move(keep);
    }
    return consolidate(std::move(parts), faceNormal);
}
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
Polygon clipToVolumePrecise(Polygon face,const Volume &volume) {
    CoreCsgScope precise(true);return clipToVolume(std::move(face),volume);
}
std::vector<Polygon> exposedPrecise(Polygon face,const std::vector<Volume> &volumes,int owner) {
    CoreCsgScope precise(true);return exposed(std::move(face),volumes,owner);
}
#endif

Experiment build(const std::vector<cliffDetail::Quad> &patch, const CanyonAppearance &base, uint64_t seed, bool detail,bool seeded,bool finishRoof,const CanyonAppearance *regionSource) {
    ConstructionTiming stageTiming("core");
    Wall wall(patch);
    FloorIndex floor(base);
    Experiment result;
    result.detailEnabled=detail;
    result.seededComposition=seeded;
    const auto backing=std::getenv("DW_CLIFF_BACKING");
    result.blendedBacking=seeded && (!backing || std::string_view(backing)!="legacy");
    result.editMargin=seeded?1.f:.75f;
    result.width = wall.s.back();
    const auto forms=compose(wall.s.back(),seed,!seeded);
    result.descriptors=forms;
    for (size_t i = 0; i < forms.size(); ++i) {
        if(!forms[i].enabled)continue;
        bool placed=false;
        for(int fit=0;fit<(seeded?4:1) && !placed;++fit) {
            auto f = forms[i];
            f.width*=fit==0?1.f:fit==1?.85f:fit==2?.70f:.55f;
            if(fit>=2)f.depth*=fit==2?.88f:.75f;
            float along = f.at * wall.s.back();
            auto tangent = wall.tangent(along, f.width * .45f);
            tangent.y = 0;
            tangent = Vector3Normalize(tangent);
            auto outward = Vector3Normalize(Vector3CrossProduct(tangent, {0, 1, 0}));
            if (dot(outward, seeded?wall.facing(along):cliffDetail::normal(patch.front())) < 0)
                outward = mul(outward, -1);
            const auto rotatedTangent = add(mul(tangent, std::cos(f.profile.yaw)),
                                             mul(outward, std::sin(f.profile.yaw)));
            const auto rotatedOutward = add(mul(outward, std::cos(f.profile.yaw)),
                                             mul(tangent, -std::sin(f.profile.yaw)));
            Rock desc{wall.point(along),
                      rotatedTangent,
                      rotatedOutward,
                      f.width,
                      f.depth,
                      f.height,
                      seed + i * 0x9e3779b97f4a7c15ULL,
                      f.profile};
            desc.center.y = 0;
            desc.center = sub(desc.center, mul(outward, f.depth * .56f + f.setback));
            for (int attempt = 0; attempt < 25; ++attempt) {
                const bool chip=detail && (i==3 || i==5);
                auto volume = rock(desc,chip);
                if (floor.clear(volume, result.clearanceTests)) {
                    result.shiftedVolumes += attempt > 0;
                    result.volumes.push_back(std::move(volume));
                    result.rimCuts+=chip;
                    std::cout << "FORMATION_PROFILE name=" << f.name << " at=" << f.at
                              << " width=" << f.width << " depth=" << f.depth << " height=" << f.height
                              << " setback=" << f.setback << " placement_shift=" << attempt * .2f
                              << " yaw=" << f.profile.yaw << " lean=" << f.profile.lean.x << ',' << f.profile.lean.y
                              << " roof=" << f.profile.roof.x << ',' << f.profile.roof.y
                              << " crown=" << f.profile.crown.x << ',' << f.profile.crown.y
                              << " crown_at=" << f.profile.crownAt << " taper=" << f.profile.taper
                              << " bevel=" << f.profile.bevel << " corners=" << f.profile.corners
                              << " bevel_mask=" << f.profile.bevelMask << '\n';
                    result.descriptors[i]=f;
                    if(fit)std::cout<<"FORMATION_FIT name="<<f.name<<" width_factor="<<(fit==1?.85f:fit==2?.70f:.55f)<<'\n';
                    placed = true;
                    break;
                }
                desc.center = sub(desc.center, mul(outward, .2f));
            }
        }
        if(!placed && seeded && (forms[i].role==FormationRole::Base || forms[i].role==FormationRole::Shoulder)) {
            result.descriptors[i].enabled=false;
            std::cout<<"FORMATION_OMITTED name="<<forms[i].name<<" reason=protected_floor\n";
            continue;
        }
        check(placed, "Cannot place rock clear of protected floor");
    }
    addPlateau(result,wall,floor,base,finishRoof,regionSource);
    // The authored edge hints belong only to the fixed regression wall. Seeded
    // primary roofs connect through the shared, floor-clipped plateau body.
    const auto connectorTops=seeded?std::vector<cliffOptions::Triangle>{}:connectShoulder(result,wall,floor);
    if(std::getenv("DW_CLIFF_JOIN_PROBE")) {
        for(auto q:patch)std::cout<<"JOIN_WALL a="<<q.ab.x<<','<<q.ab.z<<" b="<<q.bb.x<<','<<q.bb.z<<'\n';
        for(size_t i=0;i<8;++i)for(const auto &face:result.volumes[i].faces)if(normal(face).y>.45f)
            for(auto p:face)std::cout<<"JOIN_ROOF volume="<<i<<" p="<<p.x<<','<<p.y<<','<<p.z<<'\n';
    }
    if(detail) {
        // Two low, partly buried buttresses; the protected-floor test rejects
        // any attempt to use combat space for decoration.
        for(auto [fraction,width,height]:std::array<std::array<float,3>,2>{{{.13f,1.25f,.43f},{.70f,1.05f,.38f}}}) {
            auto tangent=wall.tangent(fraction*wall.s.back(),.8f);tangent.y=0;tangent=Vector3Normalize(tangent);
            auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));
            if(dot(outward,seeded?wall.facing(fraction*wall.s.back()):cliffDetail::normal(patch.front()))<0)outward=mul(outward,-1);
            Rock desc{wall.point(fraction*wall.s.back()),tangent,outward,width,1.1f,height,
                      seed^uint64_t(fraction*10000)^0x42415345ULL,{}};
            desc.center=sub(desc.center,mul(outward,.8f));desc.center.y=0;
            desc.profile.corners=6;desc.profile.roof={.19f,-.12f};desc.profile.crown={-.28f,.14f};
            desc.profile.taper=.22f;
            bool placed=false;
            for(int attempt=0;attempt<8;++attempt) {
                auto volume=rock(desc);
                bool embedded=!seeded;
                if(seeded)for(const auto &parent:result.volumes) {
                    if(parent.bounds.max.x<volume.bounds.min.x || parent.bounds.min.x>volume.bounds.max.x ||
                       parent.bounds.max.z<volume.bounds.min.z || parent.bounds.min.z>volume.bounds.max.z)continue;
                    auto interior=parent;for(auto &plane:interior.planes)plane.distance-=.005;
                    for(const auto &face:volume.faces) {
                        const auto shared=clipToVolume(face,interior);
                        if(shared.size()>=3 && area(shared)>1e-6f && center(shared).y>.08f){embedded=true;break;}
                    }
                    if(embedded)break;
                }
                if(embedded && floor.clear(volume,result.clearanceTests)) {
                    if(attempt)std::cout<<"FORMATION_BUTTRESS_FIT retreat_m="<<attempt*.12f<<" positive_attachment=PASS\n";
                    result.volumes.push_back(std::move(volume));++result.baseDetails;placed=true;break;
                }
                desc.center=sub(desc.center,mul(outward,.12f));
            }
            if(!placed && seeded)std::cout<<"FORMATION_DETAIL_OMITTED reason=no_attached_floor_clear_buttress\n";
            else check(placed,"Cannot place detail buttress clear of protected floor");
        }
        const auto firstDetail=result.volumes.size()-result.baseDetails;
        for(size_t cursor=result.volumes.size();cursor>firstDetail;) {
            const auto i=--cursor;
            float visibleArea=0;
            for(const auto &face:result.volumes[i].faces)
                for(const auto &part:exposed(face,result.volumes,int(i)))
                    if(center(part).y>.08f && normal(part).y>-.001f)visibleArea+=area(part);
            if(visibleArea<=.03f) {
                result.volumes.erase(result.volumes.begin()+i);--result.baseDetails;
                std::cout<<"FORMATION_DETAIL_OMITTED reason=buried_buttress\n";
                continue;
            }
            std::cout<<"FORMATION_BUTTRESS index="<<i<<" exposed_upper_area="<<visibleArea<<'\n';
        }
        std::cout<<"FORMATION_DETAIL rim_cuts="<<result.rimCuts<<" base_buttresses="<<result.baseDetails<<'\n';
    }
    if(std::getenv("DW_CLIFF_COMPONENTS"))for(size_t i=0;i<result.volumes.size();++i) {
        const auto b=result.volumes[i].bounds;
        std::cout<<"COMPONENT_SOURCE id="<<i<<" min="<<b.min.x<<','<<b.min.y<<','<<b.min.z<<" max="<<b.max.x<<','<<b.max.y<<','<<b.max.z<<'\n';
    }
    std::vector<Polygon> boundary;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    CoreCsgScope exactMerge(seeded && std::getenv("DW_CLIFF_ROOF_CHUNKS") && std::getenv("DW_CLIFF_POLYGON_CONTOURS"));
#endif
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    const bool solidBoolean=seeded && std::getenv("DW_CLIFF_SOLID_BOOLEAN");
    std::vector<cliffOptions::Mesh> booleanBodies;
#endif
    const bool usedRoofShell=seeded && result.blendedBacking && std::getenv("DW_CLIFF_ROOF_SHELL");
    const size_t bodyBegin=result.primaryVolumes,bodyEnd=bodyBegin+result.plateauVolumes;
    if(usedRoofShell) {
        check(result.finishedRoof && std::getenv("DW_CLIFF_ROOF_MERGED"),"Roof shell requires the graded roof trial");
        const std::vector<Volume> bodies(result.volumes.begin()+bodyBegin,result.volumes.begin()+bodyEnd);
        std::vector<cliffOptions::Mesh> shells;
        if(std::getenv("DW_CLIFF_ROOF_REGION"))shells=meshPlateauRegionBodies(bodies);else shells.push_back(meshPlateauBody(bodies));
        std::vector<Volume> cutters(result.volumes.begin(),result.volumes.begin()+bodyBegin);
        cutters.emplace_back(); // Virtual owner keeps original coplanar priority.
        cutters.insert(cutters.end(),result.volumes.begin()+bodyEnd,result.volumes.end());
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
        if(solidBoolean)booleanBodies=std::move(shells);else
#endif
        for(const auto &shell:shells)for(const auto &f:shell.faces)for(auto p:exposed({f[0],f[1],f[2]},cutters,int(bodyBegin)))boundary.push_back(std::move(p));
    }
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    if(!solidBoolean)
#endif
    for(size_t i=0;i<result.volumes.size();++i) {
        if(usedRoofShell && i>=bodyBegin && i<bodyEnd)continue;
        for(auto f:result.volumes[i].faces)for(auto p:exposed(f,result.volumes,int(i)))boundary.push_back(std::move(p));
    }
    bool usedSolidBoolean=false;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    usedSolidBoolean=solidBoolean;
    const auto booleanSetting=std::getenv("DW_CLIFF_BOOLEAN_TOLERANCE");
    const double booleanTolerance=booleanSetting?std::stod(booleanSetting):.000008;
    check(booleanTolerance>0 && booleanTolerance<=.0001,"Unsupported boolean construction tolerance");
    const auto paddingSetting=std::getenv("DW_CLIFF_BOOLEAN_PADDING");
    const float padding=paddingSetting?std::stof(paddingSetting):0;
    check(padding>=0 && padding<=.00004f,"Unsupported boolean regularization radius");
    std::vector<Polygon> booleanFloors;
    if(solidBoolean && padding>0) {
        Box region=result.volumes.front().bounds;
        for(const auto &v:result.volumes) {
            region.min.x=std::min(region.min.x,v.bounds.min.x);region.max.x=std::max(region.max.x,v.bounds.max.x);
            region.min.z=std::min(region.min.z,v.bounds.min.z);region.max.z=std::max(region.max.z,v.bounds.max.z);
        }
        for(const auto &t:base.triangles)if(!t.rock) {
            const auto &v=t.vertices;
            if(std::max({v[0].x,v[1].x,v[2].x})<region.min.x-padding || std::min({v[0].x,v[1].x,v[2].x})>region.max.x+padding ||
               std::max({v[0].z,v[1].z,v[2].z})<region.min.z-padding || std::min({v[0].z,v[1].z,v[2].z})>region.max.z+padding)continue;
            booleanFloors.push_back({v[0],v[1],v[2]});
        }
    }
    result.mesh=solidBoolean?solidBooleanUnion(result.volumes,booleanTolerance,padding,booleanFloors,booleanBodies,bodyBegin,result.plateauVolumes):weldSurface(boundary,.00008f,usedRoofShell);
#else
    check(!std::getenv("DW_CLIFF_SOLID_BOOLEAN"),"Solid boolean backend is disabled; configure DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT to investigate it");
    result.mesh=weldSurface(boundary,.00008f,usedRoofShell);
#endif
    if(seeded) {
        auto invalid=[](const StrictSurfaceAudit &a) {
            return a.exact.boundaryEdges || a.exact.nonmanifoldEdges || a.nonmanifoldVertices || a.selfIntersections ||
                a.coplanarOverlaps || a.exact.degenerateFaces || a.exact.duplicateFaces || a.exact.windingErrors || a.exact.components!=1;
        };
        result.strictAudit=auditStrictSurface(result.mesh);
        if(!usedSolidBoolean && invalid(result.strictAudit))for(float tolerance:{.00006f,.00004f,.00003f,.00002f,.000008f,.000002f,.00012f}) {
            auto alternative=weldSurface(boundary,tolerance,usedRoofShell);
            const auto audit=auditStrictSurface(alternative);
            if(invalid(audit))continue;
            result.mesh=std::move(alternative);result.strictAudit=audit;
            std::cout<<"FORMATION_WELD stage=core tolerance="<<tolerance<<" exact_checks=PASS\n";
            break;
        }

        if(usedRoofShell && !invalid(result.strictAudit)) {
            const auto before=result.mesh.faces.size();result.mesh=simplifyPlateauSurface(result.mesh);
            result.strictAudit=auditStrictSurface(result.mesh);
            std::cout<<"PLATEAU_CORE_SIMPLIFY before="<<before<<" after="<<result.mesh.faces.size()<<" checked_replacements=PASS\n";
        }
    }
    ValidationTiming measuredVerification;
    // Verify useful elevated routes from every main roof into the common land,
    // separately from manifold closure and rear-body triangle coverage.
    for(size_t i=0;i<5;++i) {
        float minimumRoof=1000;
        for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)
            for(auto p:face)minimumRoof=std::min(minimumRoof,p.y);
        const auto start=mul(add(result.volumes[i].bounds.min,result.volumes[i].bounds.max),.5f);
        const float position=result.descriptors[i].at*wall.s.back();
        auto tangent=wall.tangent(position,result.descriptors[i].width*.45f);tangent.y=0;tangent=Vector3Normalize(tangent);
        auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));
        if(dot(outward,seeded?wall.facing(position):cliffDetail::normal(patch.front()))<0)outward=mul(outward,-1);
        const auto waypoint=sub(wall.point(position),mul(outward,6.5f));
        auto along=sub(result.plateauCenter,start);along.y=0;along=Vector3Normalize(along);
        const Vector3 lateral{-along.z,0,along.x};
        std::vector<Vector3> routes{Vector3Lerp(start,result.plateauCenter,.5f),waypoint};
        for(const auto &top:result.plateauTops)routes.push_back(mul(add(add(top[0],top[1]),top[2]),1.f/3));
        bool connected=false;
        for(auto route:routes) {
            float maximumStep=0;bool valid=true;
            for(float side:{-.08f,0.f,.08f}) {
                const auto a=add(start,mul(lateral,side)),b=add(result.plateauCenter,mul(lateral,side));
                float previous=0;
                for(int sample=0;sample<=128;++sample) {
                    const float t=sample/128.f;const auto via=add(route,mul(lateral,side));
                    auto p=t<=.5f?Vector3Lerp(a,via,t*2):Vector3Lerp(via,b,(t-.5f)*2);p.y=20;
                    const float height=20-traceMesh(result.mesh,p,{0,-1,0});
                    if(height<minimumRoof-.12f){valid=false;break;}
                    if(sample)maximumStep=std::max(maximumStep,std::abs(height-previous));
                    previous=height;
                }
                if(!valid)break;
            }
            if(!valid)continue;
            result.maximumRouteStep=std::max(result.maximumRouteStep,maximumStep);
            result.plateauRouteChecks+=3*129;connected=true;break;
        }
        if(!connected)std::cout<<"PLATEAU_ROUTE_FAILED main="<<i<<" minimum_roof="<<minimumRoof<<" target="<<result.plateauCenter.y<<'\n';
        check(connected,"Main cliff roof has no elevated route into the plateau");
    }
    std::cout<<"PLATEAU_ROUTES main_roofs=5 samples="<<result.plateauRouteChecks<<" maximum_sample_step="<<result.maximumRouteStep<<'\n';
    for(const auto &top:connectorTops)for(int i=0;i<=16;++i)for(int j=0;j<=16-i;++j) {
        auto p=add(mul(top[0],1-(i+j)/16.f),add(mul(top[1],i/16.f),mul(top[2],j/16.f)));
        p=Vector3Lerp(p,mul(add(add(top[0],top[1]),top[2]),1.f/3),.001f);
        const auto from=Vector3{p.x,20,p.z};
        const auto actual=traceMesh(result.mesh,from,{0,-1,0});
        if(actual>20-p.y+.004f)std::cerr<<"JOIN_COVERAGE_FAILURE p="<<p.x<<','<<p.y<<','<<p.z<<" actual="<<actual<<" expected="<<20-p.y<<'\n';
        check(actual<=20-p.y+.004f,"Plateau roof connector has an uncovered footprint");
        ++result.joinCoverageChecks;
    }
    std::cout<<"PLATEAU_JOIN connectors="<<result.joinConnectors<<" footprint_checks="<<result.joinCoverageChecks<<'\n';
    result.audit=seeded?result.strictAudit.exact:auditSurface(result.mesh);
    if(!seeded)result.strictAudit=auditStrictSurface(result.mesh);
    const auto &strict=result.strictAudit;
    if(const auto probe=std::getenv("DW_CLIFF_EXACT_PROBE"))writeSurfaceProbe(probe,result.mesh,result.volumes,strict);
    std::cout<<"PLATEAU_EXACT exact_open="<<strict.exact.boundaryEdges<<" exact_nonmanifold="<<strict.exact.nonmanifoldEdges
             <<" vertex_links="<<strict.nonmanifoldVertices<<" crossings="<<strict.selfIntersections
             <<" coplanar_overlap="<<strict.coplanarOverlaps<<" degenerate="<<strict.exact.degenerateFaces
             <<" tested_pairs="<<strict.testedPairs<<" components="<<strict.exact.components
             <<" duplicates="<<strict.exact.duplicateFaces<<" winding="<<strict.exact.windingErrors
             <<" source="<<(usedSolidBoolean?"solid_boolean":usedRoofShell?"roof_shell":"clipped_union")<<'\n';
    check(strict.exact.boundaryEdges==0 && strict.exact.nonmanifoldEdges==0 && strict.nonmanifoldVertices==0 &&
          strict.selfIntersections==0 && strict.coplanarOverlaps==0 && strict.exact.degenerateFaces==0 &&
          strict.exact.duplicateFaces==0 && strict.exact.windingErrors==0 && strict.exact.components==1,
          "Exact cliff/plateau connection audit failed");
    result.boundaryCoverage=auditBoundaryCoverage(result.mesh,result.volumes);
    std::cout<<"PLATEAU_BOUNDARY whole_triangles="<<result.boundaryCoverage.triangles
             <<" buried_fragments="<<result.boundaryCoverage.buriedFragments
             <<" detached_fragments="<<result.boundaryCoverage.detachedFragments<<" position_margin_m=.0001\n";
    check(result.boundaryCoverage.buriedFragments==0 && result.boundaryCoverage.detachedFragments==0,
          "Plateau has a face buried in or detached from the source solid union");
    std::cout << "PLATEAU_SURFACE primary=" << result.primaryVolumes << " body=" << result.plateauVolumes
              << " vertices=" << result.audit.vertices << " open_edges=" << result.audit.boundaryEdges
              << " nonmanifold=" << result.audit.nonmanifoldEdges << " duplicates=" << result.audit.duplicateFaces
              << " degenerate=" << result.audit.degenerateFaces << " winding=" << result.audit.windingErrors
              << " components=" << result.audit.components << '\n';
    check(result.audit.boundaryEdges==0 && result.audit.nonmanifoldEdges==0 && result.audit.duplicateFaces==0 &&
          result.audit.degenerateFaces==0 && result.audit.windingErrors==0 && result.audit.components==1,
          "Plateau union is not one closed consistently oriented surface");
    result.mesh.masses = result.volumes.size();
    check(result.mesh.faces.size() < 2400, "Rock union mesh exceeds prototype budget");
    // Independent convex-plane rays must agree with the extracted exposed mesh.
    Box box = result.volumes.front().bounds;
    for (auto v : result.volumes) {
        box.min = {std::min(box.min.x, v.bounds.min.x), std::min(box.min.y, v.bounds.min.y),
                   std::min(box.min.z, v.bounds.min.z)};
        box.max = {std::max(box.max.x, v.bounds.max.x), std::max(box.max.y, v.bounds.max.y),
                   std::max(box.max.z, v.bounds.max.z)};
    }
    Random rng(seed);
    auto mid = mul(add(box.min, box.max), .5f);
    for (int i = 0; i < 640; ++i) {
        float angle = rng.real(0, 2 * Pi);
        auto from = add(mid, {std::cos(angle) * 35, rng.real(12, 25), std::sin(angle) * 35});
        auto target =
            Vector3{rng.real(box.min.x, box.max.x), rng.real(.4f, box.max.y), rng.real(box.min.z, box.max.z)};
        auto direction = Vector3Normalize(sub(target, from));
        float expected = 1000, actual = 1000;
        for (auto v : result.volumes)
            expected = std::min(expected, ray(v, from, direction));
        actual = traceMesh(result.mesh, from, direction);
        if (!((expected == 1000 && actual == 1000) || std::abs(expected - actual) < .004f))
            std::cerr << "FORMATION_RAY_FAILURE seed=" << seed << " ray=" << i
                      << " expected=" << expected << " actual=" << actual << '\n';
        check((expected == 1000 && actual == 1000) || std::abs(expected - actual) < .004f,
              "Exposed rock union ray mismatch");
        ++result.rayChecks;
    }
    std::map<std::array<float,4>,std::pair<int,std::array<Vector3,2>>> topEdges;
    for(const auto &top:result.plateauTops) for(int k=0;k<3;++k) {
        auto a=top[k],b=top[(k+1)%3];
        if(std::pair{a.x,a.z}>std::pair{b.x,b.z}) std::swap(a,b);
        auto &edge=topEdges[{a.x,a.z,b.x,b.z}]; ++edge.first; edge.second={a,b};
    }
    for(const auto &top:result.plateauTops)
        for(int i=0;i<=6;++i) for(int j=0;j<=6-i;++j) {
            auto point=add(mul(top[0],1-(i+j)/6.f),add(mul(top[1],i/6.f),mul(top[2],j/6.f)));
            for(const auto &[key,edge]:topEdges) if(edge.first==1) {
                auto a=edge.second[0],b=edge.second[1],p=point; a.y=b.y=p.y=0;
                const auto e=sub(b,a);
                const float t=std::clamp(dot(sub(p,a),e)/dot(e,e),0.f,1.f);
                if(distance(p,add(a,mul(e,t)))<.0001f) {
                    // The independent source corner can lie micrometres beyond
                    // the welded perimeter. Probe 0.3 mm inside outer edges;
                    // internal shared top edges remain sampled exactly.
                    auto inward=sub(center({top[0],top[1],top[2]}),point); inward.y=0;
                    // Tiny clipped triangles can have a centroid less than
                    // 0.3 mm away. A fixed step overshoots that centroid and
                    // can leave the very source triangle being checked.
                    const float inset=std::min(.0003f,Vector3Length(inward)*.5f);
                    point=add(point,mul(Vector3Normalize(inward),inset));
                    break;
                }
            }
            bool covered=false;
            size_t probe=0;
            // CSG welding can move a source seam by up to 80 micrometres.
            // Guard only these boundary samples within a 0.3 mm neighbourhood;
            // compare both independent oracles at the SAME probe position.
            for(auto offset:{Vector3{},Vector3{.0003f,0,0},Vector3{-.0003f,0,0},
                             Vector3{0,0,.0003f},Vector3{0,0,-.0003f}}) {
                auto from=add(add(point,offset),{0,10,0});
                float expected=1000;
                for(const auto &v:result.volumes) expected=std::min(expected,ray(v,from,{0,-1,0}));
                const float actual=traceMesh(result.mesh,from,{0,-1,0});
                if(std::getenv("DW_CLIFF_TOP_PROBE") && !(expected<1000 && expected<=10.004f && std::abs(expected-actual)<.004f))
                    std::cout<<"PLATEAU_TOP_PROBE p="<<point.x<<','<<point.y<<','<<point.z<<" offset="<<offset.x<<','<<offset.z<<" expected="<<expected<<" actual="<<actual<<" difference="<<expected-actual<<'\n';
                if(expected<1000 && expected<=10.004f && std::abs(expected-actual)<.004f) {
                    covered=true; result.topEdgeGuards+=probe>0; break;
                }
                ++probe;
            }
            if(!covered) std::cerr<<"PLATEAU_TOP_FAILURE p="<<point.x<<','<<point.y<<','<<point.z<<'\n';
            check(covered,
                  "Plateau top has a hole or insufficient elevated coverage");
            ++result.topChecks;
        }
    if(result.blendedBacking) {
        std::vector<Volume> originalCaps(result.volumes.begin(),result.volumes.begin()+result.primaryVolumes);
        size_t samples=0,rearSamples=0;float maximumError=0,maximumRearRaise=0;
        const bool merged=result.seededComposition && result.finishedRoof && std::getenv("DW_CLIFF_ROOF_MERGED");
        for(size_t i=0;i<5;++i) {
            const auto front=merged?capFrontRoof(result.volumes[i],result.descriptors[i],wall).front:Plane{};
            size_t frontSamples=0;
            for(const auto &face:result.volumes[i].faces)if(normal(face).y>.85f)
            for(size_t k=1;k+1<face.size();++k)for(int u=0;u<=4;++u)for(int v=0;v<=4-u;++v) {
                auto p=add(mul(face[0],1-(u+v)/4.f),add(mul(face[k],u/4.f),mul(face[k+1],v/4.f)));
                p=Vector3Lerp(p,center(face),.001f);p.y=20;
                const auto expected=traceVolumes(originalCaps,p,{0,-1,0}),actual=traceMesh(result.mesh,p,{0,-1,0});
                if(merged && planeProjection(front,p)>front.distance+.00002) {
                    check(expected<1000 && actual<=expected+.004f,"Rear grading lowered a primary roof");
                    maximumRearRaise=std::max(maximumRearRaise,expected-actual);++rearSamples;continue;
                }
                maximumError=std::max(maximumError,std::abs(actual-expected));
                if(expected>=1000 || std::abs(actual-expected)>=.004f)std::cout<<"CAP_FRONT_FAILURE main="<<i<<" x="<<p.x<<" z="<<p.z<<" expected_height="<<20-expected<<" actual_height="<<20-actual<<'\n';
                check(expected<1000 && std::abs(actual-expected)<.004f,"Backing changes a protected cap roof");++samples;++frontSamples;
            }
            check(frontSamples>0,"Primary cap has no protected roof samples");
        }
        std::cout<<"PLATEAU_CAP_SURFACE samples="<<samples<<" maximum_height_error_m="<<maximumError
                 <<" original_roofs="<<(merged?"front_preserved":"preserved")<<" rear_samples="<<rearSamples
                 <<" maximum_rear_raise_m="<<maximumRearRaise<<'\n';
    }
    std::cout<<"PLATEAU_TOP coverage_rays="<<result.topChecks<<" edge_guards="<<result.topEdgeGuards<<" shared_edges_included=PASS\n";
    for(const auto &face:result.mesh.faces) {
        const auto n=Vector3Normalize(Vector3CrossProduct(sub(face[1],face[0]),sub(face[2],face[0])));
        const auto middle=mul(add(add(face[0],face[1]),face[2]),1.f/3);
        float clearance=1e9f;
        for(int k=0;k<3;++k) {
            const auto e=Vector3Normalize(sub(face[(k+1)%3],face[k]));
            clearance=std::min(clearance,Vector3Length(Vector3CrossProduct(sub(middle,face[k]),e)));
        }
        // A ray exactly on a welded silhouette can graze the source solid and
        // amplify an 80 micrometre positional change into centimetres of ray
        // distance. Probe both incident faces just inside each seam instead.
        // Sub-weld-scale slivers are covered by the closed-surface edge audit.
        if(clearance<.00032f) {result.seamSkipped+=3;continue;}
        for(int k=0;k<3;++k) {
            const auto a=face[k],b=face[(k+1)%3],mid=mul(add(a,b),.5f);
            const auto tangent=Vector3Normalize(sub(b,a));
            const float inset=Vector3Length(Vector3CrossProduct(sub(middle,mid),tangent));
            const auto target=Vector3Lerp(mid,middle,std::min(1.f,.001f/inset));
            const auto from=add(target,mul(n,.02f));
            const float expected=traceVolumes(result.volumes,from,mul(n,-1));
            if(expected<.00001f) {++result.seamSkipped;continue;}
            const float actual=traceMesh(result.mesh,from,mul(n,-1));
            if(std::abs(expected-actual)>=.004f)
                std::cerr<<"PLATEAU_SEAM_FAILURE seed="<<seed<<" expected="<<expected<<" actual="<<actual<<'\n';
            check(std::abs(expected-actual)<.004f,"Targeted union seam ray disagrees with solid boundary");
            ++result.seamChecks;
        }
    }
    std::cout<<"PLATEAU_SEAMS targeted_rays="<<result.seamChecks<<" sub_weld_or_occluded_skips="<<result.seamSkipped<<" distance_tolerance_m=.004 PASS\n";
    std::cout << "FORMATION_SOLIDS count=" << result.volumes.size()
              << " triangles=" << result.mesh.faces.size() << " floor_tests=" << result.clearanceTests
              << " shifted=" << result.shiftedVolumes << " closed_convex=PASS union_rays=" << result.rayChecks
              << '\n';
    return result;
}
void apply(CanyonAppearance &out, const std::vector<cliffDetail::Quad> &patch, Experiment &rocks) {
    ConstructionTiming stageTiming("adapt");
    Wall wall(patch);
    FloorIndex floor(out);
    auto before = out.surface.heights;
    std::vector<std::array<Vector3, 3>> protectedFloor;
    for (const auto &t : out.triangles)
        if (!t.rock)
            protectedFloor.push_back(t.vertices);
    std::vector<CanyonSurfaceTriangle> triangles;
    std::vector<size_t> offsets;
    size_t changed = 0;
    Box bounds{{1e9f,1e9f,1e9f},{-1e9f,-1e9f,-1e9f}};
    for(const auto &v:rocks.volumes) {
        bounds.min.x=std::min(bounds.min.x,v.bounds.min.x); bounds.max.x=std::max(bounds.max.x,v.bounds.max.x);
        bounds.min.z=std::min(bounds.min.z,v.bounds.min.z); bounds.max.z=std::max(bounds.max.z,v.bounds.max.z);
    }
    if(rocks.volumes.empty()) for(const auto &t:out.triangles) for(auto p:t.vertices) {
        bounds.min.x=std::min(bounds.min.x,p.x); bounds.max.x=std::max(bounds.max.x,p.x);
        bounds.min.z=std::min(bounds.min.z,p.z); bounds.max.z=std::max(bounds.max.z,p.z);
    }
    bounds.min.x-=rocks.editMargin; bounds.min.z-=rocks.editMargin; bounds.max.x+=rocks.editMargin; bounds.max.z+=rocks.editMargin;
    rocks.editBounds=bounds;
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
    const bool reuseSources=rocks.seededComposition && (std::getenv("DW_CLIFF_SOURCE_REUSE") || std::getenv("DW_CLIFF_CAP_CONNECTED_DOMAIN"));
    std::optional<sourceReuse::Columns> reuseColumns;
    const bool jointJoin=std::getenv("DW_CLIFF_JOINT_TERRAIN_JOIN")!=nullptr;
    check(!jointJoin || reuseSources,"Joint terrain join requires seeded source reuse");
    if(reuseSources && !jointJoin)reuseColumns.emplace(rocks.mesh);
    if(reuseSources && !jointJoin && std::getenv("DW_CLIFF_CAP_CONNECTED_DOMAIN") && std::getenv("DW_CLIFF_SOURCE_SNAP_ROUND")) {
        std::vector<Polygon> sources;
        for(const auto &t:out.triangles)if(t.rock) {
            const auto n=Vector3CrossProduct(sub(t.vertices[1],t.vertices[0]),sub(t.vertices[2],t.vertices[0]));
            if(n.y>.65f*Vector3Length(n) && std::max({t.vertices[0].y,t.vertices[1].y,t.vertices[2].y})>.35f)sources.push_back({t.vertices[0],t.vertices[1],t.vertices[2]});
        }
        reuseColumns->claimCanonicalSources(sources);
    }
#else
    check(!std::getenv("DW_CLIFF_JOINT_TERRAIN_JOIN") && !std::getenv("DW_CLIFF_SOURCE_REUSE") && !std::getenv("DW_CLIFF_CAP_CONNECTED_DOMAIN"),"Source reuse requires the Boolean experiment");
#endif
    Volume region;
    region.planes={{{1,0,0},bounds.max.x},{{-1,0,0},-bounds.min.x},
                   {{0,0,1},bounds.max.z},{{0,0,-1},-bounds.min.z}};
    const bool wholeSource=std::getenv("DW_CLIFF_JOINT_WHOLE_SOURCE")!=nullptr;
    check(!wholeSource || std::getenv("DW_CLIFF_JOINT_TERRAIN_JOIN"),"Whole source joins require the joint terrain construction");
    Volume floorRegion=region;
    if(wholeSource) {
        // Own each intersecting source face in full. The perimeter then follows
        // original source edges rather than introducing a rectangular cut graph.
        for(const auto &t:out.triangles)if(t.rock) {
            Polygon p{t.vertices[0],t.vertices[1],t.vertices[2]};for(auto plane:region.planes)p=clip(p,plane,true);
            if(p.size()<3 || area(p)<1e-10f)continue;
            for(auto v:t.vertices){bounds.min.x=std::min(bounds.min.x,v.x);bounds.max.x=std::max(bounds.max.x,v.x);bounds.min.z=std::min(bounds.min.z,v.z);bounds.max.z=std::max(bounds.max.z,v.z);}
        }
        rocks.editBounds=bounds;
        floorRegion.planes={{{1,0,0},bounds.max.x},{{-1,0,0},-bounds.min.x},{{0,0,1},bounds.max.z},{{0,0,-1},-bounds.min.z}};
    }
    rocks.protectedFloor.clear();
    for(const auto &face:protectedFloor) {
        auto part=clipToVolume({face[0],face[1],face[2]},floorRegion);
        if(part.size()>=3 && area(part)>1e-10f)rocks.protectedFloor.push_back(std::move(part));
    }
    auto altered = [&](Vector3 p) {
        auto [s, d] = wall.locate(p);
        // The old facet pass protrudes in front of the source contour. Include
        // that skin as well, or lowering only the inset vertices leaves spikes.
        if (d < -.8f || d > 9 || s < .001f || s > wall.s.back() - .001f)
            return p;
        float weight =
            std::clamp(std::min(s, wall.s.back() - s) / .8f, 0.f, 1.f) * std::clamp((rocks.blendedBacking?6.f-d:9.f-d)/(rocks.blendedBacking?2.f:3.f),0.f,1.f);
        // The old 0.6 m backing read as a curb and intersected the base rocks.
        // Continue the existing floor contour into the lowered region, tapering
        // to the sand behind it. A constant-height backing left small raised
        // plates wherever the new volumes exposed the old terrace footprints.
        const float ground = rocks.blendedBacking ? CanyonTerrain::WalkableHeight : CanyonTerrain::WalkableHeight *
                             (1 - std::clamp(d / .8f, 0.f, 1.f));
        weight *= std::clamp(std::min({p.x-bounds.min.x,bounds.max.x-p.x,p.z-bounds.min.z,bounds.max.z-p.z})/.5f,0.f,1.f);
        p.y = std::lerp(p.y, rocks.blendedBacking?ground:std::min(p.y, ground), weight);

        return p;
    };
    std::vector<Polygon> retained, outside;
    size_t outsideSplitVertices=0;
    float outsidePlaneError=0;
    for (size_t cell = 0; cell + 1 < out.cellOffsets.size(); ++cell) {
        offsets.push_back(triangles.size());
        for (size_t i = out.cellOffsets[cell]; i < out.cellOffsets[cell + 1]; ++i) {
            auto t = out.triangles[i];
            if (!t.rock) { triangles.push_back(t); outside.push_back({t.vertices[0],t.vertices[1],t.vertices[2]}); continue; }
            const Polygon original{t.vertices[0],t.vertices[1],t.vertices[2]};
            auto inside=original;
            for(auto plane:region.planes) inside=clip(inside,plane,true);
            if(inside.size()<3 || area(inside)<1e-10f) {
                triangles.push_back(t); outside.push_back(original); continue;
            }
            if(wholeSource){retained.push_back(original);++changed;continue;}
            // Split crossing old triangles at the edit boundary. No remote
            // part of a large facet is pulled into the replacement surface.
            for(auto part:exposed(original,{region})) {
                const auto n=Vector3Normalize(Vector3CrossProduct(sub(original[1],original[0]),sub(original[2],original[0])));
                for(auto p:part) {
                    outsidePlaneError=std::max(outsidePlaneError,std::abs(dot(n,sub(p,original[0]))));
                    ++outsideSplitVertices;
                }
                for(size_t k=1;k+1<part.size();++k) triangles.push_back({{part[0],part[k],part[k+1]},true});
                outside.push_back(std::move(part));
            }
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
            if(reuseSources) {
                if(inside.size()<3)continue;
                if(jointJoin){retained.push_back(std::move(inside));++changed;continue;}
                bool removed=false;
                for(auto source:reuseColumns->outside(inside,removed))retained.push_back(std::move(source));
                changed+=removed;
                continue;
            }
#endif
            bool different=false;
            for(auto &v:inside) {
                auto p=altered(v); different |= distance(v,p)>.00001f; v=p;
            }
            changed+=different;
            if(area(inside)<1e-10f) continue;
            // The height adaptation is nonlinear. A clipped quad can warp,
            // so establish planar triangles before creating terrain solids.
            for(size_t k=1;k+1<inside.size();++k)
                for(auto ground:floor.trim({inside[0],inside[k],inside[k+1]}))retained.push_back(std::move(ground));

        }
    }
    check(changed>0, "No selected backing geometry changed");
    check(outsidePlaneError<.00003f,"Edit boundary changed an outside source plane");
    std::cout<<"PLATEAU_LOCALITY x="<<bounds.min.x<<','<<bounds.max.x<<" z="<<bounds.min.z<<','<<bounds.max.z
             <<" outside_split_vertices="<<outsideSplitVertices<<" max_plane_error_m="<<outsidePlaneError<<'\n';
    rocks.assembledMesh=assembleSurface(retained,rocks,outside);
    for(const auto &face:rocks.assembledMesh.faces) triangles.push_back({face,true});
    offsets.push_back(triangles.size());
    out.triangles = std::move(triangles);
    out.cellOffsets = std::move(offsets);
    // Suppress unsupported old plateau plants in this geometry-only diagnostic.
    const auto plantsBefore=out.decorations.size();
    if(!rocks.detailEnabled) std::erase_if(out.decorations,
                  [&](const auto &d) {
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
                      if(reuseSources)return reuseColumns->contains(d.position);
#endif
                      return distance(d.position, altered(d.position)) > .05f;
                  });
    // Refresh actual-mesh query bins. Physical terrain/collision remains untouched.
    int columns = out.surface.width - 1, rows = out.surface.depth - 1;
    std::vector<std::vector<size_t>> bins(size_t(columns * rows));
    for (size_t i = 0; i < out.triangles.size(); ++i) {
        int lx = columns - 1, hx = 0, lz = rows - 1, hz = 0;
        for (auto p : out.triangles[i].vertices) {
            int x = std::clamp(int(std::floor((p.x - out.surface.x) / out.surface.step)), 0, columns - 1),
                z = std::clamp(int(std::floor((p.z - out.surface.z) / out.surface.step)), 0, rows - 1);
            lx = std::min(lx, x);
            hx = std::max(hx, x);
            lz = std::min(lz, z);
            hz = std::max(hz, z);
        }
        for (int z = lz; z <= hz; ++z)
            for (int x = lx; x <= hx; ++x)
                bins[size_t(z * columns + x)].push_back(i);
    }
    out.spatialOffsets.clear();
    out.spatialTriangles.clear();
    for (auto &bin : bins) {
        out.spatialOffsets.push_back(out.spatialTriangles.size());
        out.spatialTriangles.insert(out.spatialTriangles.end(), bin.begin(), bin.end());
    }
    out.spatialOffsets.push_back(out.spatialTriangles.size());
    if(rocks.detailEnabled) addScenery(out,patch,rocks,out.seed^0x5343454e455259ULL);
    check(out.surface.heights == before, "Physical field changed");
    size_t floorIndex = 0;
    for (const auto &t : out.triangles)
        if (!t.rock) {
            check(floorIndex < protectedFloor.size(), "Extra floor triangle");
            for (int k = 0; k < 3; ++k)
                check(distance(t.vertices[k], protectedFloor[floorIndex][k]) < 1e-7f, "Floor vertex changed");
            ++floorIndex;
        }
    check(floorIndex == protectedFloor.size(), "Missing floor triangles");
    std::cout << "FORMATION_ADAPTER unsupported_plants_suppressed=" << (rocks.detailEnabled?rocks.sceneryRemoved:plantsBefore-out.decorations.size()) << " backing_triangles_changed=" << changed
              << " collision_heights=unchanged floor_triangles=unchanged\n";
}
} // namespace dw::rockFormations
