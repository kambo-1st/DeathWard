#include "world/TownNavigation.hpp"
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
    in.seekg(8);
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
    out.write("DWTNAV01", 8);
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
void TownNavigation::bake(const TownDocument &document, const Model &model) {
    document.validate();
    if (!width || !depth || width > 4096 || depth > 4096 || cell < .1f ||
        document.meshCount() != model.meshCount)
        throw std::runtime_error("Invalid navigation bounds or mesh library.");
    const float nan = std::numeric_limits<float>::quiet_NaN();
    std::vector<float> top(size_t(width) * depth, -std::numeric_limits<float>::infinity());
    std::vector<bool> flat(top.size(), false);
    for (size_t i = 0; i < document.instances.size(); ++i) {
        const auto &instance = document.instances[i];
        const auto &asset = document.assets[instance.asset];
        const auto bounds = document.bounds(i);
        if (asset.unlit || asset.label.find("Cloud") != std::string::npos || bounds.min.y > 12 ||
            bounds.max.x < minX || bounds.min.x > minX + width * cell || bounds.max.z < minZ ||
            bounds.min.z > minZ + depth * cell)
            continue;
        for (int m = asset.first; m < asset.first + asset.count; ++m) {
            const auto &mesh = model.meshes[m];
            for (int t = 0; t < mesh.triangleCount; ++t) {
                Vector3 p[3];
                for (int k = 0; k < 3; ++k) {
                    const int v = mesh.indices ? mesh.indices[3 * t + k] : 3 * t + k;
                    p[k] = Vector3Transform(
                        {mesh.vertices[3 * v], mesh.vertices[3 * v + 1], mesh.vertices[3 * v + 2]},
                        instance.transform);
                }
                const auto normal = Vector3CrossProduct(sub(p[1], p[0]), sub(p[2], p[0]));
                const float denom =
                    (p[1].z - p[2].z) * (p[0].x - p[2].x) + (p[2].x - p[1].x) * (p[0].z - p[2].z);
                if (std::abs(denom) < .000001f)
                    continue;
                const int x0 =
                    std::max(0, int(std::floor((std::min({p[0].x, p[1].x, p[2].x}) - minX) / cell)));
                const int x1 = std::min(int(width) - 1,
                                        int(std::floor((std::max({p[0].x, p[1].x, p[2].x}) - minX) / cell)));
                const int z0 =
                    std::max(0, int(std::floor((std::min({p[0].z, p[1].z, p[2].z}) - minZ) / cell)));
                const int z1 = std::min(int(depth) - 1,
                                        int(std::floor((std::max({p[0].z, p[1].z, p[2].z}) - minZ) / cell)));
                const bool surface = std::abs(normal.y) / length(normal) > .7f;
                for (int z = z0; z <= z1; ++z)
                    for (int x = x0; x <= x1; ++x) {
                        const float px = minX + (float(x) + .5f) * cell, pz = minZ + (float(z) + .5f) * cell;
                        const float a =
                            ((p[1].z - p[2].z) * (px - p[2].x) + (p[2].x - p[1].x) * (pz - p[2].z)) / denom;
                        const float b =
                            ((p[2].z - p[0].z) * (px - p[2].x) + (p[0].x - p[2].x) * (pz - p[2].z)) / denom;
                        if (a < -.00001f || b < -.00001f || a + b > 1.00001f)
                            continue;
                        const float h = a * p[0].y + b * p[1].y + (1 - a - b) * p[2].y;
                        const size_t at = size_t(z) * width + size_t(x);
                        if (h > top[at]) {
                            top[at] = h;
                            flat[at] = surface && h > -5 && h < 12;
                        }
                    }
            }
        }
    }
    std::vector<bool> clear(top.size(), false), connected(top.size(), false);
    for (uint32_t z = 1; z + 1 < depth; ++z)
        for (uint32_t x = 1; x + 1 < width; ++x) {
            const size_t at = size_t(z) * width + x;
            bool valid = flat[at];
            for (int dz = -1; dz <= 1; ++dz)
                for (int dx = -1; dx <= 1; ++dx) {
                    const size_t n = size_t(int(z) + dz) * width + size_t(int(x) + dx);
                    valid = valid && flat[n] && std::abs(top[at] - top[n]) < .6f;
                }
            clear[at] = valid;
        }
    auto nearest = [&](Vector3 target, const std::vector<bool> &allowed) {
        size_t result = top.size();
        float best = 64; // Do not silently move gameplay markers far away from their edited location.
        for (size_t i = 0; i < top.size(); ++i) {
            const float dx = minX + (float(i % width) + .5f) * cell - target.x;
            const float dz = minZ + (float(i / width) + .5f) * cell - target.z;
            if (allowed[i] && dx * dx + dz * dz < best) {
                best = dx * dx + dz * dz;
                result = i;
            }
        }
        if (result == top.size())
            throw std::runtime_error(
                "No connected ground near a marker. Move Arrival / Missions onto an open street.");
        return result;
    };
    const auto start = nearest(spawn, clear);
    std::queue<size_t> queue;
    queue.push(start);
    connected[start] = true;
    while (!queue.empty()) {
        const size_t at = queue.front();
        queue.pop();
        for (size_t next : {at - 1, at + 1, at - width, at + width})
            if (next < top.size() && clear[next] && !connected[next] &&
                std::abs(top[at] - top[next]) <= .6f) {
                connected[next] = true;
                queue.push(next);
            }
    }
    const auto board = nearest(mission, connected);
    for (size_t i = 0; i < top.size(); ++i)
        if (!connected[i])
            top[i] = nan;
    heights = std::move(top);
    spawn = point(start);
    mission = point(board);
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
