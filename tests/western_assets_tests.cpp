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
           distance(a.bounds.min, b.bounds.min) < 0.0001f && distance(a.bounds.max, b.bounds.max) < 0.0001f;
}
size_t verifyCanyon(WesternScene &scene) {
    size_t total = 0;
    for (uint64_t seed : {0ULL, 1ULL, 42ULL, 1866ULL, 69175541ULL}) {
        Arena arena(seed, MissionTheme::Canyon);
        scene.prepare(arena);
        check(scene.terrainReady(), "canyon builds one continuous triangulated terrain");
        const auto first = scene.placements();
        const auto &field = *arena.canyon;
        for (const auto &p : first)
            check(p.asset == WesternAsset::RockA || p.asset == WesternAsset::CactusA ||
                      p.asset == WesternAsset::CactusB,
                  "canyon decorations contain no cube cover, straight walls or repeated cliff cards");
        for (const auto &chunk : scene.terrainChunks()) {
            check(chunk.mesh.vertexCount > 0, "terrain chunks upload visible triangles");
            // Rock sections and floor chunks have irregular footprints; sample an actual triangle.
            const auto *v = chunk.mesh.vertices;
            const Vector3 p{(v[0] + v[3] + v[6]) / 3, 0, (v[2] + v[5] + v[8]) / 3};
            const Vector3 from{p.x, 30, p.z}, to{p.x, -1, p.z};
            const auto hit = field.trace(from, to);
            const auto meshHit = GetRayCollisionMesh({from, {0, -1, 0}}, chunk.mesh, MatrixIdentity());
            check(hit.hit && meshHit.hit && std::abs(hit.t * 31 - meshHit.distance) < .003f,
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
