#include "world/TownNavigation.hpp"
#include "world/TownBuildings.hpp"
#include "platform/Browser.hpp"
#include "raymath.h"
#include "world/HubWorld.hpp"
#include <cstring>
#include <fstream>
#include <queue>
#include <stdexcept>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace dw {
namespace {
// Clip a triangle to one navigation cell. This includes vertical and sub-cell
// walls that a ray through the cell center could miss entirely.
struct Polygon {
    std::array<Vector3, 12> points{};
    int count = 0;
};
Polygon clip(Polygon polygon, int axis, float edge, bool greater) {
    Polygon result;
    auto coordinate = [axis](Vector3 p) { return axis == 0 ? p.x : p.z; };
    for (int n = 0; n < polygon.count; ++n) {
        const auto a = polygon.points[size_t(n)], b = polygon.points[size_t((n + 1) % polygon.count)];
        const float da = coordinate(a) - edge, db = coordinate(b) - edge;
        const bool insideA = greater ? da >= 0 : da <= 0, insideB = greater ? db >= 0 : db <= 0;
        if (insideA) result.points[size_t(result.count++)] = a;
        if (insideA != insideB) result.points[size_t(result.count++)] = add(a, mul(sub(b, a), da / (da - db)));
    }
    return result;
}
constexpr float StepHeight = .6f, StandingClearance = 1.9f;
struct SolidSpan {
    float low = std::numeric_limits<float>::infinity();
    float high = -std::numeric_limits<float>::infinity();
    float surface = -std::numeric_limits<float>::infinity();
    bool flat = false;
};
struct WalkSurface { float height; bool clear = false; };
void replaceFile(const std::filesystem::path &from, const std::filesystem::path &to) {
#ifdef _WIN32
    if (!MoveFileExW(from.c_str(), to.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
        throw std::runtime_error("Could not replace " + to.string());
#else
    std::filesystem::rename(from, to);
#endif
}
} // namespace
void TownNavigation::load(const std::filesystem::path &path) {
    HubWorld check;
    if (!check.load(path))
        throw std::runtime_error(check.error);
    TownNavigation n;
    std::ifstream in(path, std::ios::binary);
    char magic[8]{};
    in.read(magic, 8);
    n.bakeVersion = magic[7] == '3' ? 3 : magic[7] == '2' ? 2 : 1;
    auto read = [&](auto &value) { in.read(reinterpret_cast<char *>(&value), sizeof(value)); };
    read(n.width);
    read(n.depth);
    read(n.minX);
    read(n.minZ);
    read(n.cell);
    read(n.spawn.x);
    read(n.spawn.y);
    read(n.spawn.z);
    read(n.mission.x);
    read(n.mission.y);
    read(n.mission.z);
    n.heights.resize(size_t(n.width) * n.depth);
    in.read(reinterpret_cast<char *>(n.heights.data()), std::streamsize(n.heights.size() * sizeof(float)));
    if (!in)
        throw std::runtime_error("Could not read town navigation.");
    *this = std::move(n);
}
void TownNavigation::write(const std::filesystem::path &path) const {
    if (heights.size() != size_t(width) * depth || !width || !depth)
        throw std::runtime_error("No navigation to save.");
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(bakeVersion >= 3 ? "DWTNAV03" : bakeVersion >= 2 ? "DWTNAV02" : "DWTNAV01", 8);
    auto write = [&](const auto &v) { out.write(reinterpret_cast<const char *>(&v), sizeof(v)); };
    write(width);
    write(depth);
    write(minX);
    write(minZ);
    write(cell);
    write(spawn.x);
    write(spawn.y);
    write(spawn.z);
    write(mission.x);
    write(mission.y);
    write(mission.z);
    out.write(reinterpret_cast<const char *>(heights.data()),
              std::streamsize(heights.size() * sizeof(float)));
    out.close();
    if (!out)
        throw std::runtime_error("Could not write town navigation.");
}
Vector3 TownNavigation::point(size_t i) const {
    return {minX + (float(i % width) + .5f) * cell, heights[i], minZ + (float(i / width) + .5f) * cell};
}
float TownNavigation::height(Vector3 p) const {
    if (!std::isfinite(p.x) || !std::isfinite(p.z) || cell <= 0)
        return std::numeric_limits<float>::quiet_NaN();
    const int x = int(std::floor((double(p.x) - minX) / cell)),
              z = int(std::floor((double(p.z) - minZ) / cell));
    if (x < 0 || z < 0 || x >= int(width) || z >= int(depth))
        return std::numeric_limits<float>::quiet_NaN();
    return heights.at(size_t(z) * width + size_t(x));
}
void TownNavigation::bake(const TownDocument &document, const Model &model) {
    document.validate();
    if (!document.walkAllowed(spawn))
        throw std::runtime_error("Arrival is outside the allowed walk area. Move Arrival or edit the outline.");
    if (!document.walkAllowed(mission))
        throw std::runtime_error("Missions is outside the allowed walk area. Move Missions or edit the outline.");
    if (!width || !depth || width > 4096 || depth > 4096 || cell < .1f ||
        document.meshCount() != model.meshCount)
        throw std::runtime_error("Invalid navigation bounds or mesh library.");
    // Door leaves are about 1.2 m wide. The outdoor .4 m grid plus erosion
    // sealed those openings; .2 m resolves a standing player's clearance.
    if (cell > .20001f) {
        width = uint32_t(std::ceil(float(width) * cell / .2f));
        depth = uint32_t(std::ceil(float(depth) * cell / .2f));
        cell = .2f;
        if (width > 4096 || depth > 4096) throw std::runtime_error("Refined navigation exceeds grid limits.");
    }
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const size_t count = size_t(width) * depth;
    std::vector<std::vector<SolidSpan>> columns(count);
    for (size_t i = 0; i < document.instances.size(); ++i) {
        const auto &instance = document.instances[i];
        if (instance.animated()) continue;
        const auto &asset = document.assets[instance.asset];
        if (buildingDoor(asset) || doorGlass(asset)) continue;
        const bool hollow = buildingGeometry(asset);
        const auto bounds = document.bounds(i);
        if (asset.unlit || asset.label.find("Cloud") != std::string::npos || bounds.min.y > 14 ||
            bounds.max.x < minX || bounds.min.x > minX + width * cell || bounds.max.z < minZ ||
            bounds.min.z > minZ + depth * cell) continue;
        const auto cellX = [&](float x) { return int(std::floor((x - minX) / cell)); };
        const auto cellZ = [&](float z) { return int(std::floor((z - minZ) / cell)); };
        const int left = std::max(0, cellX(bounds.min.x)), right = std::min(int(width) - 1, cellX(bounds.max.x));
        const int frontRow = std::max(0, cellZ(bounds.min.z)), backRow = std::min(int(depth) - 1, cellZ(bounds.max.z));
        const int row = right - left + 1;
        if (row <= 0 || backRow < frontRow) continue;
        std::vector<SolidSpan> spans(size_t(row) * size_t(backRow - frontRow + 1));
        for (int m = asset.first; m < asset.first + asset.count; ++m) {
            const auto &mesh = model.meshes[m];
            for (int t = 0; t < mesh.triangleCount; ++t) {
                Vector3 p[3];
                for (int k = 0; k < 3; ++k) {
                    const int v = mesh.indices ? mesh.indices[3 * t + k] : 3 * t + k;
                    p[k] = Vector3Transform({mesh.vertices[3 * v], mesh.vertices[3 * v + 1], mesh.vertices[3 * v + 2]}, instance.transform);
                }
                const auto normal = Vector3CrossProduct(sub(p[1], p[0]), sub(p[2], p[0]));
                const float denom = (p[1].z - p[2].z) * (p[0].x - p[2].x) + (p[2].x - p[1].x) * (p[0].z - p[2].z);
                const bool flat = length(normal) > .000001f && std::abs(normal.y) / length(normal) > .7f;
                const int x0 = std::max(left, cellX(std::min({p[0].x, p[1].x, p[2].x})));
                const int x1 = std::min(right, cellX(std::max({p[0].x, p[1].x, p[2].x})));
                const int z0 = std::max(frontRow, cellZ(std::min({p[0].z, p[1].z, p[2].z})));
                const int z1 = std::min(backRow, cellZ(std::max({p[0].z, p[1].z, p[2].z})));
                for (int z = z0; z <= z1; ++z)
                    for (int x = x0; x <= x1; ++x) {
                        const float xMin = minX + float(x) * cell, zMin = minZ + float(z) * cell;
                        Polygon polygon;
                        polygon.count = 3;
                        std::copy_n(p, 3, polygon.points.begin());
                        polygon = clip(polygon, 0, xMin, true);
                        polygon = clip(polygon, 0, xMin + cell, false);
                        polygon = clip(polygon, 2, zMin, true);
                        polygon = clip(polygon, 2, zMin + cell, false);
                        if (!polygon.count) continue;
                        SolidSpan triangle;
                        auto &span = hollow ? triangle : spans[size_t(z - frontRow) * size_t(row) + size_t(x - left)];
                        for (int n = 0; n < polygon.count; ++n) {
                            span.low = std::min(span.low, polygon.points[size_t(n)].y);
                            span.high = std::max(span.high, polygon.points[size_t(n)].y);
                        }
                        if (std::abs(denom) >= .000001f) {
                            const float px = xMin + .5f * cell, pz = zMin + .5f * cell;
                            const float a = ((p[1].z - p[2].z) * (px - p[2].x) + (p[2].x - p[1].x) * (pz - p[2].z)) / denom;
                            const float b = ((p[2].z - p[0].z) * (px - p[2].x) + (p[0].x - p[2].x) * (pz - p[2].z)) / denom;
                            if (a >= -.00001f && b >= -.00001f && a + b <= 1.00001f) {
                                const float height = a * p[0].y + b * p[1].y + (1 - a - b) * p[2].y;
                                if (height > span.surface) { span.surface = height; span.flat = flat; }
                            }
                        }
                        if (hollow) columns[size_t(z) * width + size_t(x)].push_back(triangle);
                    }
            }
        }
        if (!hollow) for (int z = frontRow; z <= backRow; ++z)
            for (int x = left; x <= right; ++x) {
                const auto &span = spans[size_t(z - frontRow) * size_t(row) + size_t(x - left)];
                if (std::isfinite(span.high)) columns[size_t(z) * width + size_t(x)].push_back(span);
            }
    }
    // Merge touching slabs, preserving empty space between a floor and roof
    // even when both belong to the same mesh. Ordinary rocks/crates remain solid.
    for (auto &column : columns) {
        std::sort(column.begin(),column.end(),[](const auto &a,const auto &b){return a.low < b.low;});
        size_t kept = 0;
        for (const auto span : column) {
            if (kept && span.low <= column[kept-1].high + .015f) {
                auto &previous = column[kept-1];
                previous.high = std::max(previous.high,span.high);
                if (span.surface > previous.surface) { previous.surface=span.surface; previous.flat=span.flat; }
            } else column[kept++] = span;
        }
        column.resize(kept);
    }
    // Keep street surfaces below bridges/signs as well as roof candidates. A
    // solid object crossing the standing body rejects a surface; overhead
    // geometry with sufficient headroom does not become a wall on the street.
    std::vector<std::vector<WalkSurface>> surfaces(count);
    for (size_t at = 0; at < count; ++at) {
        const Vector3 center{minX + (float(at % width) + .5f) * cell, 0,
                             minZ + (float(at / width) + .5f) * cell};
        // Apply before footprint clearance and connectivity. Thin blocked strips
        // cover intersecting cells too, so they cannot disappear between samples.
        if (!document.walkAllowed(center, cell * .7072f)) continue;
        for (const auto &candidate : columns[at]) {
            const float h = candidate.surface;
            if (!candidate.flat || h <= -5 || h >= 12) continue;
            bool clear = true;
            for (const auto &solid : columns[at])
                if ((solid.high > h + StepHeight && solid.low < h + StandingClearance) ||
                    (solid.flat && solid.surface > h + .03f && solid.surface <= h + StepHeight)) {
                    clear = false; break;
                }
            if (clear && std::none_of(surfaces[at].begin(), surfaces[at].end(),
                [&](const auto &s) { return std::abs(s.height - h) < .001f; })) surfaces[at].push_back({h});
        }
    }
    columns.clear();
    columns.shrink_to_fit();
    const int margin = int(std::ceil(.4f/cell));
    for (int z = margin; z + margin < int(depth); ++z)
        for (int x = margin; x + margin < int(width); ++x) {
            const size_t at = size_t(z) * width + size_t(x);
            for (auto &surface : surfaces[at]) {
                bool clear = true;
                for (int dz = -margin; dz <= margin && clear; ++dz)
                    for (int dx = -margin; dx <= margin && clear; ++dx) {
                        // Triangle clipping already covers each cell's full area.
                        // Erode around a circular footprint; a square expansion
                        // closes valid routes through narrow, angled doorways.
                        if (float(dx * dx + dz * dz) * cell * cell > .4f * .4f + .00001f) continue;
                        const auto &neighbors = surfaces[size_t(z + dz) * width + size_t(x + dx)];
                        clear &= std::any_of(neighbors.begin(), neighbors.end(), [&](const auto &n) {
                            return std::abs(surface.height - n.height) < StepHeight;
                        });
                    }
                surface.clear = clear;
            }
        }
    size_t start = count;
    float startHeight = 0, best = document.walkAreas.empty() ? 64.f : .64f;
    for (size_t at = 0; at < count; ++at)
        for (const auto &surface : surfaces[at]) {
            const Vector3 point{minX + (float(at % width) + .5f) * cell, surface.height,
                                minZ + (float(at / width) + .5f) * cell};
            const float d = distance(point, spawn);
            if (surface.clear && d * d < best) { best = d * d; start = at; startHeight = surface.height; }
        }
    if (start == count) throw std::runtime_error("No connected ground near Arrival. Move it onto an open street.");
    std::vector<float> result(count, nan);
    result[start] = startHeight;
    std::queue<size_t> queue;
    queue.push(start);
    while (!queue.empty()) {
        const auto at = queue.front(); queue.pop();
        for (size_t next : {at - 1, at + 1, at - width, at + width}) {
            if (next >= count || std::isfinite(result[next])) continue;
            const WalkSurface *chosen = nullptr;
            for (const auto &surface : surfaces[next])
                if (surface.clear && std::abs(surface.height - result[at]) <= StepHeight &&
                    (!chosen || std::abs(surface.height - result[at]) < std::abs(chosen->height - result[at]))) chosen = &surface;
            if (chosen) { result[next] = chosen->height; queue.push(next); }
        }
    }
    size_t board = count;
    best = document.walkAreas.empty() ? 64.f : .64f;
    for (size_t at = 0; at < count; ++at) {
        const float dx = minX + (float(at % width) + .5f) * cell - mission.x;
        const float dz = minZ + (float(at / width) + .5f) * cell - mission.z;
        if (std::isfinite(result[at]) && dx * dx + dz * dz < best) { best = dx * dx + dz * dz; board = at; }
    }
    if (board == count) throw std::runtime_error("No connected ground near Missions. Move it onto an open street.");
    bakeVersion = 3;
    heights = std::move(result);
    spawn = point(start);
    mission = point(board);
}
void saveTownNavigation(const std::filesystem::path &directory, const TownNavigation &navigation) {
    const auto path = directory / "town.nav", staged = directory / "town.nav.tmp";
    try {
        navigation.write(staged);
        HubWorld check;
        if (!check.load(staged) || !check.moveTo(check.mission))
            throw std::runtime_error("Rebuilt town navigation failed validation.");
        std::filesystem::copy_file(path, directory / "town.nav.bak", std::filesystem::copy_options::overwrite_existing);
        replaceFile(staged, path);
        persistBrowserFiles();
    } catch (...) {
        std::error_code ignored;
        std::filesystem::remove(staged, ignored);
        throw;
    }
}
void saveTownProject(const std::filesystem::path &directory, const TownDocument &document,
                     const TownNavigation &navigation) {
    const auto scene = directory / "town.scene", nav = directory / "town.nav";
    const auto sceneTemp = directory / "town.scene.tmp", navTemp = directory / "town.nav.tmp";
    bool replacing = false;
    try {
        document.write(sceneTemp);
        navigation.write(navTemp);
        TownDocument checkScene;
        HubWorld checkNav;
        std::string error;
        if (!checkScene.load(sceneTemp, error) || !checkNav.load(navTemp) ||
            !checkNav.moveTo(checkNav.mission))
            throw std::runtime_error("Edited town failed scene/navigation validation. " + error);
        std::filesystem::copy_file(scene, directory / "town.scene.bak",
                                   std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(nav, directory / "town.nav.bak",
                                   std::filesystem::copy_options::overwrite_existing);
        replacing = true;
        replaceFile(navTemp, nav);
        replaceFile(sceneTemp, scene);
        persistBrowserFiles();
    } catch (...) {
        std::error_code ignored;
        if (replacing) {
            std::filesystem::copy_file(directory / "town.scene.bak", scene,
                                       std::filesystem::copy_options::overwrite_existing, ignored);
            std::filesystem::copy_file(directory / "town.nav.bak", nav,
                                       std::filesystem::copy_options::overwrite_existing, ignored);
        }
        std::filesystem::remove(sceneTemp, ignored);
        std::filesystem::remove(navTemp, ignored);
        throw;
    }
}
} // namespace dw
