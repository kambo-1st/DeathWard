#include "raylib.h"
#include "raymath.h"
#include "world/CanyonAppearance.hpp"
#include "world/Dungeon.hpp"
#include <bit>
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b, const char *m) {
    if (!b)
        throw std::runtime_error(m);
}
uint64_t fingerprint(const CanyonTerrain &f) {
    uint64_t h = 1469598103934665603ULL;
    for (float v : f.heights)
        h = (h ^ std::bit_cast<uint32_t>(v)) * 1099511628211ULL;
    return h;
}
void configuration() {
    const auto path = std::filesystem::path(DEATHWARD_ASSET_DIR) / "visual/canyon.cfg";
    const auto p = CanyonVisualParameters::load(path);
    check(p.enabled && p.irregularFacets && p.polygonFacets && p.terraces == 3, "production config enables three-tier presentation");
    auto bad = std::filesystem::temp_directory_path() / "deathward-canyon-invalid.cfg";
    for (const auto *line : {"terrace_count 0", "minimum_height -1", "maximum_height 0", "facet_variation 2",
                             "composition_strength 1.1", "plateau_vegetation -1", "maximum_decorations 6001",
                             "terrace_count 2.5", "unknown 3", "enabled 2", "enabled 1\nenabled 0", "irregular_facets 2", "polygon_facets 2"}) {
        std::ofstream(bad) << "DEATHWARD_CANYON 1\n" << line << '\n';
        bool rejected = false;
        try {
            CanyonVisualParameters::load(bad);
        } catch (const std::exception &) {
            rejected = true;
        }
        check(rejected, "bad or duplicate visual parameters rejected");
    }
    std::filesystem::remove(bad);
    std::cout << "CONFIG validated_parameters=13 default_loaded=1\n";
}
void narrowSupportRegression() {
    CanyonAppearance f;
    f.surface.width = f.surface.depth = 2;
    f.surface.step = 1;
    f.surface.heights.assign(4, 0);
    auto add = [&](Vector3 a, Vector3 b, Vector3 c) { f.triangles.push_back({{a, b, c}, true}); };
    add({0, 0, 0}, {1, 0, 1}, {1, 0, 0});
    add({0, 0, 0}, {0, 0, 1}, {1, 0, 1});
    add({.331f, 1, .331f}, {.336f, 1, .336f}, {.336f, 1, .331f});
    add({.35f, 0, .333f}, {.35f, 1, .333f}, {.35f, 1, .34f});
    f.cellOffsets = {0, f.triangles.size()};
    f.triangles.pop_back();
    f.cellOffsets.back() = f.triangles.size();
    check(!f.supports({.5f, 0, .5f}, .4f, .1f), "a tiny raised ledge cannot hide between footprint samples");
    f.triangles.pop_back();
    add({.35f, 0, .333f}, {.35f, 1, .333f}, {.35f, 1, .34f});
    f.cellOffsets.back() = f.triangles.size();
    check(!f.supports({.4f, 0, .4f}, .1f, .1f), "vertical risers inside a root pad reject placement");
    check(f.supports({.8f, 0, .8f}, .05f, .1f), "clear flat support is retained");
    std::cout
        << "FOOTPRINT exact_triangle_clip=PASS narrow_ledge=PASS vertical_riser=PASS flat_ground=PASS\n";
}
void displacedQueryRegression() {
    CanyonAppearance look;
    look.surface.width = 3;
    look.surface.depth = 2;
    look.surface.step = 1;
    look.surface.heights.assign(6, 0);
    look.triangles.push_back({{{Vector3{1.2f, 1, .1f}, Vector3{1.2f, 1, .8f}, Vector3{1.8f, 1, .1f}}}, true});
    // Render order still associates this triangle with source cell zero.
    // Its actual geometry has moved entirely into cell one.
    look.triangles.push_back({{{Vector3{1.4f, 0, .2f}, Vector3{1.4f, 1, .2f}, Vector3{1.4f, 0, .4f}}}, true});
    look.cellOffsets = {0, 2, 2};
    look.spatialOffsets = {0, 0, 2};
    look.spatialTriangles = {0, 1};
    check(std::abs(look.height(1.4f, .3f) - 1) < .00001f, "height follows displaced triangle bins");
    auto hit = look.trace({1.4f, 3, .3f}, {1.4f, -1, .3f});
    check(hit.hit && std::abs(hit.t - .5f) < .00001f, "ray follows displaced triangle bins");
    check(!look.supports({1.4f, 0, .3f}, .08f, .1f), "root support follows displaced geometry");
    std::cout << "SPATIAL displaced_height=PASS displaced_ray=PASS displaced_support=PASS\n";
}
void verify() {
    std::set<int> zones, kinds, rivers;
    size_t decor = 0, checks = 0;
    double elapsed = 0;
    std::vector<float> original, visual;
    for (uint64_t seed : {0ULL, 1ULL, 2ULL, 3ULL, 42ULL, 1866ULL})
        for (bool river : {false, true}) {
            Arena arena(seed, MissionTheme::Canyon, river);
            const auto fingerprintBefore = fingerprint(*arena.canyon);
            const auto floor = arena.floorCells;
            const auto trails = arena.canyon->trails;
            const auto boundary = arena.canyon->boundaryHeights;
            std::vector<SegmentHit> rays;
            std::vector<bool> blocked;
            for (const auto &room : arena.rooms) {
                rays.push_back(arena.trace(add(room.center, {-25, 1, 0}), add(room.center, {25, 1, 0}), .1f));
                blocked.push_back(arena.blocked(room.entry, .48f));
            }
            auto start = std::chrono::steady_clock::now();
            auto look = buildCanyonAppearance(arena);
            elapsed +=
                std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
            auto repeat = buildCanyonAppearance(arena);
            check(look.surface.heights == repeat.surface.heights &&
                      look.decorations.size() == repeat.decorations.size(),
                  "visual seed repeats geometry and candidate count");
            check(fingerprintBefore == fingerprint(*arena.canyon) && floor == arena.floorCells &&
                      boundary == arena.canyon->boundaryHeights,
                  "canonical terrain, boundary collision and navigation unchanged");
            check(look.surface.width == arena.canyon->width && look.surface.depth == arena.canyon->depth,
                  "canonical lattice and exterior extent unchanged");
            rivers.insert(int(arena.canyon->riverKind));
            for (size_t i = 0; i < look.surface.heights.size(); ++i) {
                const float a = arena.canyon->heights[i], b = look.surface.heights[i];
                check(std::isfinite(b), "finite mesh heights");
                check((a > CanyonTerrain::WalkableHeight) == (b > CanyonTerrain::WalkableHeight),
                      "all vertex walkability signs preserved");
                if (a <= CanyonTerrain::WalkableHeight)
                    check(a == b, "floor, water and ford vertices unchanged");
                if (a > 4) {
                    original.push_back(a);
                    visual.push_back(b);
                }
                check(b <= look.parameters.maxHeight + .0001f,
                      "visual rock heights bounded by configured cap");
            }
            check(look.triangles.size() == repeat.triangles.size(), "deterministic contour mesh size");
            double flatArea = 0, wallArea = 0, bevelArea = 0;
            for (size_t i = 0; i < look.triangles.size(); ++i) {
                const auto &t = look.triangles[i], &u = repeat.triangles[i];
                for (int j = 0; j < 3; ++j)
                    check(distance(t.vertices[j], u.vertices[j]) < .00001f,
                          "deterministic cap and wall vertices");
                if (!t.rock)
                    continue;
                auto a = t.vertices[0], b = t.vertices[1], c = t.vertices[2];
                auto normal = Vector3CrossProduct(sub(b, a), sub(c, a));
                float area = std::sqrt(dot(normal, normal)) * .5f;
                float up = normal.y / std::max(.000001f, 2 * area);
                if (up > .98f)
                    flatArea += area;
                else if (std::abs(up) < .35f)
                    wallArea += area;
                else
                    bevelArea += area;
            }
            std::cout << "TOPOLOGY patches=" << look.cliffTopologyPatches << " unchanged_corners=" << look.cliffTopologyFallbacks << " triangles=" << look.triangles.size() << " budget=" << (look.surface.width-1)*(look.surface.depth-1)*8 << std::endl;
            std::cout << "SURFACES seed=" << seed << " river=" << river << " caps=" << flatArea
                      << " walls=" << wallArea << " bevels=" << bevelArea << std::endl;
            check(flatArea > wallArea * .4 && wallArea > bevelArea * 2,
                  "broad flat caps and vertical walls dominate small bevels");
            check(look.triangles.size() < size_t((look.surface.width - 1) * (look.surface.depth - 1) * 8),
                  "bounded contour extrusion geometry");
            check(look.decorations.size() <= 2200, "cosmetic budget bounded");
            for (size_t i = 0; i < look.decorations.size(); ++i) {
                const auto &a = look.decorations[i], &b = repeat.decorations[i];
                check(distance(a.position, b.position) < .00001f && a.kind == b.kind && a.zone == b.zone &&
                          a.yaw == b.yaw,
                      "decoration seed repeats all positions and categories");
                check(look.supports(a.position, a.kind == CanyonDecorationKind::Tree ? .45f : a.span * .65f,
                                    a.kind == CanyonDecorationKind::Cactus ? .1f : .16f),
                      "complete candidate footprint supported; no plants on steep faces");
                check(!arena.canyon->waterBlocked(a.position), "no dry vegetation in river");
                const auto road = arena.canyon->roadSample(a.position);
                check(road.distance >= road.width + a.span * .6f + .8f,
                      "track and shoulders remain free of cosmetic props");
                zones.insert(int(a.zone));
                kinds.insert(int(a.kind));
                ++decor;
            }
            for (size_t i = 0; i < arena.rooms.size(); ++i) {
                const auto &room = arena.rooms[i];
                auto h = arena.trace(add(room.center, {-25, 1, 0}), add(room.center, {25, 1, 0}), .1f);
                check(h.hit == rays[i].hit && h.t == rays[i].t &&
                          arena.blocked(room.entry, .48f) == blocked[i],
                      "projectile traces and player collision remain bit-identical");
                ++checks;
            }
            CanyonVisualParameters legacy;
            legacy.enabled = false;
            auto old = buildCanyonAppearance(arena, legacy);
            check(old.surface.heights == arena.canyon->heights && old.decorations.empty() &&
                      old.triangles.empty(),
                  "enabled0 restores original surface and dressing path");
            if (seed == 1866 && !river) {
                check(look.cliffQuads>0 && look.cliffNgons>0 && look.cliffChips>0,"selected A mixed faces and chips are enabled");
                std::cout<<"POLYGONS quads="<<look.cliffQuads<<" ngons="<<look.cliffNgons<<" chips="<<look.cliffChips<<std::endl;
                auto plainParameters=CanyonVisualParameters{};plainParameters.irregularFacets=false;
                auto plain=buildCanyonAppearance(arena,plainParameters);
                check(plain.surface.heights==look.surface.heights,"face detail preserves every elevation");
                auto fixed=[](const CanyonAppearance &f){
                    std::vector<std::array<Vector3,3>> result;
                    for(const auto &t:f.triangles){auto n=Vector3Normalize(Vector3CrossProduct(sub(t.vertices[1],t.vertices[0]),sub(t.vertices[2],t.vertices[0])));
                        if(!t.rock||n.y>.98f)result.push_back(t.vertices);
                    }return result;
                };
                auto before=fixed(plain),after=fixed(look);
                check(before.size()==after.size(),"face detail preserves floor and cap triangles");
                for(size_t i=0;i<before.size();++i)for(int j=0;j<3;++j)check(distance(before[i][j],after[i][j])<.000001f,"face detail does not move shelf or floor vertices");
                bool same=plain.decorations.size()==look.decorations.size();
                for(size_t i=0;same&&i<plain.decorations.size();++i)same=distance(plain.decorations[i].position,look.decorations[i].position)<.000001f;
                std::cout<<"FACE_SCOPE floors_caps=unchanged elevations=unchanged decorations="<<(same?"unchanged":"different")<<std::endl;
                check(same,"face detail leaves decoration placements unchanged");
                auto zero = CanyonVisualParameters{};
                zero.debris = zero.floorVegetation = zero.baseVegetation = zero.terraceVegetation =
                    zero.plateauVegetation = 0;
                auto bare = buildCanyonAppearance(arena, zero);
                check(bare.decorations.empty() && bare.surface.heights == look.surface.heights,
                      "density changes never alter terrain or gameplay");
                auto flat = zero;
                flat.minHeight = flat.maxHeight = 1.f;
                flat.facets = 1.f;
                auto single = buildCanyonAppearance(arena, flat);
                for (size_t i = 0; i < single.surface.heights.size(); ++i) {
                    float y = single.surface.heights[i];
                    check(std::isfinite(y) && y <= 1.f, "equal height limits remain bounded");
                    check((y > CanyonTerrain::WalkableHeight) ==
                              (arena.canyon->heights[i] > CanyonTerrain::WalkableHeight),
                          "equal height limits retain the rock mask");
                }
                auto small = zero;
                small.maxDecorations = 3;
                small.debris = 3;
                check(buildCanyonAppearance(arena, small).decorations.size() <= 3, "hard instance cap");
            }
        }
    std::sort(original.begin(), original.end());
    std::sort(visual.begin(), visual.end());
    check(visual[visual.size() / 2] < original[original.size() / 2] * .8f,
          "cliffs meaningfully lower without a camera change");
    check(zones.size() == 4 && kinds.size() == 5,
          "all terrain categories and existing asset roles represented");
    check(rivers.size() == 3, "dry, boundary and interior river maps covered");
    std::cout << "GEOMETRY maps=12 categories=4 asset_roles=5 candidates=" << decor
              << " collision_room_checks=" << checks
              << " original_highland_median=" << original[original.size() / 2]
              << " visual_highland_median=" << visual[visual.size() / 2]
              << " original_max=" << original.back() << " visual_max=" << visual.back()
              << " appearance_mean_ms=" << elapsed / 12 << "\n";
}
} // namespace
int main() {
    try {
        configuration();
        narrowSupportRegression();
        displacedQueryRegression();
        verify();
        std::cout << "PASS canyon visual determinism, collision invariance, support, water/road clearance "
                     "and reversible config\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
