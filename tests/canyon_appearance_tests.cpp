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
    check(p.enabled && p.terraces == 3, "production config enables three-tier presentation");
    auto bad = std::filesystem::temp_directory_path() / "deathward-canyon-invalid.cfg";
    for (const auto *line : {"terrace_count 0", "minimum_height -1", "maximum_height 0", "facet_variation 2",
                             "plateau_vegetation -1", "maximum_decorations 6001", "terrace_count 2.5",
                             "unknown 3", "enabled 2", "enabled 1\nenabled 0"}) {
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
    std::cout << "CONFIG validated_parameters=10 default_loaded=1\n";
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
                  "no additional terrain triangles or edge extent growth");
            rivers.insert(int(arena.canyon->riverKind));
            for (size_t i = 0; i < look.surface.heights.size(); ++i) {
                const float a = arena.canyon->heights[i], b = look.surface.heights[i];
                check(std::isfinite(b), "finite mesh heights");
                check((a > CanyonTerrain::WalkableHeight) == (b > CanyonTerrain::WalkableHeight),
                      "all vertex walkability signs preserved");
                if (a <= .2f)
                    check(a == b, "floor, water and ford vertices unchanged");
                if (a > 4) {
                    original.push_back(a);
                    visual.push_back(b);
                }
                check(b <= a + .0001f, "visual presentation never creates a taller blocker");
            }
            check(look.decorations.size() <= 2200, "cosmetic budget bounded");
            for (size_t i = 0; i < look.decorations.size(); ++i) {
                const auto &a = look.decorations[i], &b = repeat.decorations[i];
                check(distance(a.position, b.position) < .00001f && a.kind == b.kind && a.zone == b.zone &&
                          a.yaw == b.yaw,
                      "decoration seed repeats all positions and categories");
                check(look.supports(a.position, a.span * .65f,
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
                      !old.flipped(3, 5),
                  "enabled0 restores original surface and dressing path");
            if (seed == 1866 && !river) {
                auto zero = CanyonVisualParameters{};
                zero.debris = zero.floorVegetation = zero.baseVegetation = zero.terraceVegetation =
                    zero.plateauVegetation = 0;
                auto bare = buildCanyonAppearance(arena, zero);
                check(bare.decorations.empty() && bare.surface.heights == look.surface.heights,
                      "density changes never alter terrain or gameplay");
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
    check(zones.size() == 4 && kinds.size() == 4,
          "all terrain categories and existing asset roles represented");
    check(rivers.size() == 3, "dry, boundary and interior river maps covered");
    std::cout << "GEOMETRY maps=12 categories=4 asset_roles=4 candidates=" << decor
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
        verify();
        std::cout << "PASS canyon visual determinism, collision invariance, support, water/road clearance "
                     "and reversible config\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
