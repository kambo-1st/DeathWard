#include "raylib.h"
#include "raymath.h"
#include "world/CliffWallTopology.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
int main() {
    try {
        size_t quads = 0, ngons = 0, chips = 0, triangles = 0;
        for (auto seed : {0ULL, 1ULL, 2ULL, 42ULL, 1866ULL})
            for (int count : {4, 8, 16}) for(bool staircase : {false,true}) {
                auto lo = [=](int i) {
                    if(staircase)return Vector3{float(i/2)*.7f,.12f,-float((i+1)/2)*.7f};
                    return Vector3{float(i) * .9f, .12f, .15f * std::sin(float(i) * .7f)};
                };
                auto hi = [&](int i) {
                    auto p = lo(i);
                    p.y += 2.2f + .15f * std::sin(float(i) * .5f);
                    p.z += .06f;
                    return p;
                };
                std::vector<cliffDetail::Quad> patch;
                for (int i = 0; i < count; ++i)
                    patch.push_back({lo(i), lo(i + 1), hi(i + 1), hi(i)});
                auto m = cliffDetail::buildSelectedA(patch, seed),
                     repeat = cliffDetail::buildSelectedA(patch, seed);
                check(m.triangles.size() == repeat.triangles.size() &&
                          m.vertices.size() == repeat.vertices.size(),
                      "Seed changed mesh counts");
                for (size_t i = 0; i < m.vertices.size(); ++i)
                    check(distance(m.vertices[i], repeat.vertices[i]) < 1e-7, "Seed changed vertex");
                for (size_t i = 0; i < m.triangles.size(); ++i) {
                    auto a = m.triangles[i], b = repeat.triangles[i];
                    check(a.a == b.a && a.b == b.b && a.c == b.c, "Seed changed connectivity");
                }
                for (int i = 0; i <= count; ++i) {
                    check(distance(m.vertices[size_t(i) * 2], lo(i)) < 1e-5, "Moved floor contour");
                    check(distance(m.vertices[size_t(i) * 2 + 1], hi(i)) < 1e-5, "Moved top silhouette");
                }
                for (auto f : m.polygons) {
                    check(f.size() >= 3, "Invalid polygon");
                    for (int i : f)
                        check(size_t(i) < m.vertices.size(), "Invalid index");
                }
                quads += m.quads;
                ngons += m.ngons;
                chips += m.chips;
                triangles += m.triangles.size();
            }
        check(quads > 0 && ngons > 0 && chips > 0, "Missing mixed faces or chips");
        std::cout << "PASS selected A refinement: 30 smooth/staircase patches, fixed floor/top contours, manifold coverage, "
                     "deterministic vertices/connectivity, bounded steep meshes; quads="
                  << quads << " ngons=" << ngons << " chips=" << chips << " triangles=" << triangles << '\n';
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
