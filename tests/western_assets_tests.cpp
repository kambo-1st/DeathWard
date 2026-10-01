#include "raylib.h"
#include "raymath.h"
#include "render/WesternScene.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

namespace {
using namespace dw;
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
bool overlap(Box a, Box b) {
    return a.min.x < b.max.x && a.max.x > b.min.x && a.min.z < b.max.z && a.max.z > b.min.z;
}
bool same(const WesternPlacement &a, const WesternPlacement &b) {
    return a.asset == b.asset && a.yaw == b.yaw && a.exterior == b.exterior &&
           a.decorationRoom == b.decorationRoom && a.naturalScale == b.naturalScale &&
           a.vegetationLevel == b.vegetationLevel && distance(a.bounds.min, b.bounds.min) < 0.0001f &&
           distance(a.bounds.max, b.bounds.max) < 0.0001f;
}
void verifyDecorations(WesternScene &scene, const Arena &arena, int limit = 80) {
    std::array<int, RoomCount> counts{}, skulls{}, bones{};
    std::set<WesternAsset> kinds;
    for (const auto &p : scene.placements()) {
        if (p.decorationRoom < 0)
            continue;
        check(p.decorationRoom < RoomCount && !p.exterior && p.naturalScale > 0,
              "cosmetic props belong to a room and keep native proportions");
        const auto room = size_t(p.decorationRoom);
        ++counts[room];
        skulls[room] += p.asset == WesternAsset::Skull;
        bones[room] += p.asset == WesternAsset::Bones;
        kinds.insert(p.asset);
        const auto size = sub(p.bounds.max, p.bounds.min);
        check(size.y <= .651f && size.x < 1.9f && size.z < 1.9f,
              "room decorations remain small enough for combat readability");
        auto center = mul(add(p.bounds.min, p.bounds.max), .5f);
        center.y = .85f;
        if (arena.canyon) {
            const auto road = arena.canyon->roadSample(center);
            const float radius = std::hypot(p.bounds.max.x - p.bounds.min.x, p.bounds.max.z - p.bounds.min.z) * .5f;
            check(road.distance >= road.width + radius + .54f,
                  "decorative vegetation and debris keep the road and its shoulders clear");
        }
        check(arena.roomAt(center) == p.decorationRoom && !arena.blocked(center, .18f),
              "decoration anchors are on navigable ground in their assigned room");
        for (float x : {p.bounds.min.x, center.x, p.bounds.max.x})
            for (float z : {p.bounds.min.z, center.z, p.bounds.max.z}) {
                const Vector3 point{x, .85f, z};
                check(arena.contains(point), "the whole decoration footprint stays on playable ground");
                const float h = arena.canyon ? arena.canyon->height(x, z) : -.015f;
                check(h - p.bounds.min.y >= -.001f && h - p.bounds.min.y < .06f,
                      "decorations rest on terrain without floating or being buried in cliffs");
            }
        for (auto obstacle : arena.rooms[room].obstacles)
            check(!overlap(p.bounds, obstacle), "small props never intersect combat cover");
        for (const auto &passage : arena.passages)
            check(!overlap(p.bounds, passage.floor), "connecting passages stay clear of room decorations");
        for (const auto &key : arena.keys)
            if (key.room == p.decorationRoom)
                check(std::hypot(center.x - key.position.x, center.z - key.position.z) > 2,
                      "decorations leave keys clearly visible");
        const auto objective = arena.rooms[room].objective;
        check(std::hypot(center.x - objective.x, center.z - objective.z) > 3.5f,
              "shops and objective gathering spaces stay clear");
        const Camera3D camera{add(center, {0, 20, 10}), center, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
        scene.setPlayerOcclusion(camera, center, false);
        const auto hit = scene.pick({{center.x, 10, center.z}, {0, -1, 0}}, center);
        const float ground = arena.canyon ? arena.canyon->height(center.x, center.z) : -.015f;
        check(hit.hit && std::abs(hit.point.y - ground) < .005f,
              "movement/aim picking reaches the ground through cosmetic grass and debris");
    }
    for (int i = 0; i < RoomCount; ++i) {
        if (counts[size_t(i)] < 6)
            std::cerr << "Sparse room: seed " << arena.visualSeed << " theme " << int(arena.theme) << " room "
                      << i << " count " << counts[size_t(i)] << '\n';
        check(counts[size_t(i)] >= 6 && counts[size_t(i)] <= limit,
              "every room receives a bounded amount of small decoration, including empty/shop rooms");
        check(skulls[size_t(i)] <= 1 && bones[size_t(i)] <= 1,
              "bone and skull accents stay occasional rather than covering a room");
        check(scene.decorationCount(i) == counts[size_t(i)], "room decoration diagnostics match instances");
    }
    check(kinds.size() >= 6, "each generated mission uses a varied small-prop palette");
    std::cout << "Decorations seed " << arena.visualSeed << " theme " << int(arena.theme) << ": "
              << scene.decorationCount() << " props, room range "
              << *std::min_element(counts.begin(), counts.end()) << ".."
              << *std::max_element(counts.begin(), counts.end()) << '\n';
}
void verifyVegetation(WesternScene &scene, const Arena &arena) {
    const auto baseline = scene.placements();
    const int baselinePlants = scene.vegetationCount();
    std::vector<unsigned> terrainMeshes;
    for (const auto &chunk : scene.terrainChunks())
        terrainMeshes.push_back(chunk.mesh.vaoId);
    auto nonVegetation = [&] {
        std::vector<WesternPlacement> result;
        for (const auto &p : scene.placements())
            if (!isVegetation(p.asset))
                result.push_back(p);
        return result;
    };
    const auto fixed = nonVegetation();
    std::vector<WesternPlacement> previous;
    for (int density : {0, 25, 50, 75, 100, 125, 150, 175, 200}) {
        scene.setVegetationDensity(density);
        scene.prepare(arena);
        const auto currentFixed = nonVegetation();
        check(currentFixed.size() == fixed.size() &&
                  std::equal(fixed.begin(), fixed.end(), currentFixed.begin(), same),
              "vegetation density never moves or removes rocks, debris, buildings or cover");
        if (!density)
            check(scene.vegetationCount() == 0, "zero vegetation removes every grass patch and cactus");
        if (density == 200)
            check(scene.vegetationCount() > baselinePlants,
                  "more vegetation adds plants beyond the original amount");
        for (const auto &p : previous)
            check(std::any_of(scene.placements().begin(), scene.placements().end(),
                              [&](const auto &other) { return same(p, other); }),
                  "increasing density adds plants without moving existing ones");
        previous = scene.placements();
        for (size_t i = 0; i < terrainMeshes.size(); ++i)
            check(scene.terrainChunks()[i].mesh.vaoId == terrainMeshes[i],
                  "density changes keep uploaded terrain instead of rebuilding the canyon");
    }
    verifyDecorations(scene, arena, 160);
    int cacti = 0;
    if (arena.canyon)
        for (const auto &p : scene.placements()) {
            if (p.asset != WesternAsset::CactusA && p.asset != WesternAsset::CactusB)
                continue;
            ++cacti;
            const auto center = mul(add(p.bounds.min, p.bounds.max), .5f);
            float low = 100, high = -100;
            // Denser, independently spaced samples include the supporting pad.
            for (float x = p.bounds.min.x - .35f; x <= p.bounds.max.x + .35f; x += .12f)
                for (float z = p.bounds.min.z - .35f; z <= p.bounds.max.z + .35f; z += .12f) {
                    const float h = arena.canyon->height(x, z);
                    low = std::min(low, h);
                    high = std::max(high, h);
                }
            check(high - low < .11f && low - p.bounds.min.y >= -.005f && high - p.bounds.min.y < .15f,
                  "all canyon cacti have flat support across their footprint, away from slopes and edges");
        }
    std::cout << "Vegetation: " << baselinePlants << " at 100%, " << scene.vegetationCount() << " at 200%, "
              << cacti << " flat-terrace cacti\n";
    scene.setVegetationDensity(100);
    check(scene.placements().size() == baseline.size() &&
              std::equal(baseline.begin(), baseline.end(), scene.placements().begin(), same),
          "returning to 100 percent restores the exact original placement list");
}
size_t verifyCanyon(WesternScene &scene) {
    size_t total = 0;
    for (uint64_t seed : {0ULL, 1ULL, 42ULL, 1866ULL, 69175541ULL}) {
        Arena arena(seed, MissionTheme::Canyon);
        scene.prepare(arena);
        check(scene.terrainReady(), "canyon builds one continuous triangulated terrain");
        const auto first = scene.placements();
        verifyDecorations(scene, arena);
        verifyVegetation(scene, arena);
        const auto &field = *arena.canyon;
        for (const auto &p : first)
            check(p.asset == WesternAsset::RockA || p.asset == WesternAsset::CactusA ||
                      p.asset == WesternAsset::CactusB || p.decorationRoom >= 0,
                  "canyon decorations contain no cube cover, straight walls or repeated cliff cards");
        for (const auto &chunk : scene.terrainChunks()) {
            check(chunk.mesh.vertexCount > 0, "terrain chunks upload visible triangles");
            // Rock sections and floor chunks have irregular footprints; sample an actual triangle.
            const auto *v = chunk.mesh.vertices;
            const Vector3 p{(v[0] + v[3] + v[6]) / 3, 0, (v[2] + v[5] + v[8]) / 3};
            const Vector3 from{p.x, 30, p.z}, to{p.x, -4, p.z};
            const auto hit = field.trace(from, to);
            const auto meshHit = GetRayCollisionMesh({from, {0, -1, 0}}, chunk.mesh, MatrixIdentity());
            check(hit.hit && meshHit.hit && std::abs(hit.t * 34 - meshHit.distance) < .003f,
                  "rendered terrain triangles and collision rays agree across every chunk");
        }
        // Exercise oblique rays through cliff faces and cover, not only vertical ground probes.
        // Keep reference rays off exact lattice seams: raylib's float barycentric
        // mesh picker can reject both triangles at an edge. Core checks also probe seams.
        const auto center = add(arena.rooms[2].center, {.173f, 0, .217f});
        for (int n = 0; n < 12; ++n) {
            const float angle = n * Pi / 6;
            const Vector3 from = add(center, {std::cos(angle) * 35, 18, std::sin(angle) * 35});
            const auto direction = unit(sub(center, from));
            const auto hit = field.trace(from, add(from, mul(direction, 70)));
            float closest = 1000;
            for (const auto &chunk : scene.terrainChunks()) {
                if (!segmentBox(from, add(from, mul(direction, 70)), chunk.bounds).hit)
                    continue;
                const auto rendered = GetRayCollisionMesh({from, direction}, chunk.mesh, MatrixIdentity());
                if (rendered.hit)
                    closest = std::min(closest, rendered.distance);
            }
            if (!hit.hit || std::abs(hit.t * 70 - closest) >= .01f)
                std::cerr << "Ray seed " << seed << " angle " << n << " hit " << hit.hit << " terrain "
                          << hit.t * 70 << " mesh " << closest << " from " << from.x << "," << from.y << ","
                          << from.z << "\n";
            check(hit.hit && std::abs(hit.t * 70 - closest) < .01f,
                  "oblique terrain rays match the visible mesh");
        }
        Arena mine(seed);
        scene.prepare(mine);
        check(!scene.terrainReady(), "switching to the mine releases canyon terrain resources");
        scene.prepare(arena);
        check(first.size() == scene.placements().size(),
              "seeded canyon props reproduce after switching themes");
        for (size_t i = 0; i < first.size(); ++i)
            check(same(first[i], scene.placements()[i]), "canyon prop transforms reproduce");
        const auto focus = arena.rooms[0].center;
        Camera3D camera{add(focus, {30, 35, 30}), focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        scene.draw(focus);
        scene.drawGlass();
        EndMode3D();
        EndDrawing();
        total += first.size();
    }
    return total;
}
void verify() {
    WesternScene scene;
    const auto originalDirectory = std::filesystem::current_path();
    std::filesystem::current_path(std::filesystem::temp_directory_path());
    check(scene.load(), "packaged Western library loads away from the source working directory");
    std::filesystem::current_path(originalDirectory);
    check(scene.model().meshCount >= int(WesternAsset::Count), "all imported asset meshes are present");
    bool atlas = false, glass = false;
    for (int i = 1; i < scene.model().materialCount; ++i) {
        const auto &map = scene.model().materials[i].maps[MATERIAL_MAP_ALBEDO];
        atlas = atlas || (map.texture.width == 2048 && map.texture.height == 2048);
        glass = glass || map.color.a < 255;
    }
    check(atlas && glass, "original embedded texture atlas and transparent glass material survive import");
    const auto crate = scene.assetBounds(WesternAsset::Crate);
    check(std::abs(crate.max.y - 0.8441086f) < 0.001f,
          "FBX meters match the original Unity crate collider instead of centimeters");
    std::set<WesternAsset> kinds;
    size_t totalPlacements = 0;
    for (uint64_t seed : {0ULL, 1ULL, 42ULL, 1866ULL, 90210ULL}) {
        Arena arena(seed);
        scene.prepare(arena);
        const auto first = scene.placements();
        verifyDecorations(scene, arena);
        verifyVegetation(scene, arena);
        check(!first.empty(), "generated scenery is populated");
        std::vector<float> covered(arena.obstacles.size());
        size_t floors = 0;
        for (const auto &p : first) {
            kinds.insert(p.asset);
            const auto source = scene.assetBounds(p.asset);
            const auto transform = WesternScene::placementTransform(source, p);
            Vector3 lo{1e6f, 1e6f, 1e6f}, hi{-1e6f, -1e6f, -1e6f};
            for (float x : {source.min.x, source.max.x})
                for (float y : {source.min.y, source.max.y})
                    for (float z : {source.min.z, source.max.z}) {
                        const auto point = Vector3Transform({x, y, z}, transform);
                        check(std::isfinite(point.x) && std::isfinite(point.y) && std::isfinite(point.z),
                              "every instance transform is finite");
                        lo = Vector3Min(lo, point);
                        hi = Vector3Max(hi, point);
                    }
            check(distance(lo, p.bounds.min) < 0.002f && distance(hi, p.bounds.max) < 0.002f,
                  "imported mesh bounds fit their intended gameplay or scenery volume after rotation");
            if (p.exterior)
                for (auto floor : arena.floors)
                    check(!overlap(p.bounds, floor),
                          "exterior buildings and props never intrude on playable floor");
            if (p.asset == WesternAsset::Floor)
                ++floors;
            if (p.asset == WesternAsset::Crate) {
                int obstacle = -1;
                for (size_t i = 0; i < arena.obstacles.size(); ++i) {
                    const auto &box = arena.obstacles[i];
                    if (p.bounds.min.x >= box.min.x - 0.001f && p.bounds.max.x <= box.max.x + 0.001f &&
                        p.bounds.min.y >= box.min.y - 0.001f && p.bounds.max.y <= box.max.y + 0.001f &&
                        p.bounds.min.z >= box.min.z - 0.001f && p.bounds.max.z <= box.max.z + 0.001f)
                        obstacle = int(i);
                }
                check(obstacle >= 0, "cover models stay within a real collision obstacle");
                const auto size = sub(p.bounds.max, p.bounds.min);
                covered[size_t(obstacle)] += size.x * size.y * size.z;
            }
        }
        check(floors == arena.floors.size(),
              "textured ground exactly follows generated room and corridor strips");
        for (size_t i = 0; i < covered.size(); ++i) {
            const auto size = sub(arena.obstacles[i].max, arena.obstacles[i].min);
            check(std::abs(covered[i] - size.x * size.y * size.z) < 0.01f,
                  "every collision obstacle has a complete visible stack with matching dimensions");
        }
        Arena repeat(seed);
        for (auto &key : repeat.keys)
            key.collected = true;
        repeat.sealRoom(2);
        scene.prepare(repeat);
        check(first.size() == scene.placements().size(), "same seed repeats scenery count");
        for (size_t i = 0; i < first.size(); ++i)
            check(same(first[i], scene.placements()[i]), "same seed repeats scenery choices and placement");
        const auto focus = arena.rooms[0].center;
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D({add(focus, {30, 35, 30}), focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE});
        scene.draw(focus);
        scene.drawGlass();
        EndMode3D();
        EndDrawing();
        totalPlacements += first.size();
    }
    check(kinds.contains(WesternAsset::Saloon) && kinds.contains(WesternAsset::Church) &&
              kinds.contains(WesternAsset::Jail) && kinds.contains(WesternAsset::Station),
          "seeded scenes use the imported Western landmarks");
    totalPlacements += verifyCanyon(scene);
    check(!scene.load(WesternScene::assetDirectory() / "missing"),
          "missing pack selects the primitive fallback");
    check(scene.load(), "asset resources can be reloaded after cleanup");
    scene.unload();
    scene.unload();
    std::cout << "PASS Western textures, materials, meters, collision-fitting cover, clear routes and seeded "
                 "scenery ("
              << totalPlacements
              << " placements across five seeds in both themes, including terrain mesh rays)\n";
}
} // namespace
int main() {
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(640, 480, "Western asset verification");
        check(IsWindowReady(), "a graphics display is required");
        verify();
        CloseWindow();
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
