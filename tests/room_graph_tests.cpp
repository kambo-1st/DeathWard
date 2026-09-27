#include "world/Dungeon.hpp"
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>

namespace {
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
using Distances = std::array<int, dw::RoomCount>;
Distances distances(const dw::RoomGraph &graph, int source, int limit = dw::RoomCount) {
    Distances result;
    result.fill(-1);
    result[size_t(source)] = 0;
    std::queue<int> pending;
    pending.push(source);
    while (!pending.empty()) {
        const int at = pending.front();
        pending.pop();
        for (auto edge : graph.links) {
            const int next = edge[0] == at ? edge[1] : edge[1] == at ? edge[0] : -1;
            if (next >= 0 && next < limit && result[size_t(next)] < 0) {
                result[size_t(next)] = result[size_t(at)] + 1;
                pending.push(next);
            }
        }
    }
    return result;
}
// Ignore room numbering, translation, rotation and reflection. A changed shape
// must really arrange the rooms differently, rather than relabel the old grid.
std::vector<dw::FloorCell> footprint(const dw::RoomGraph &graph) {
    std::vector<dw::FloorCell> best;
    for (int mirror : {-1, 1})
        for (int rotation = 0; rotation < 4; ++rotation) {
            std::vector<dw::FloorCell> cells;
            int minX = 0, minZ = 0;
            for (auto [x, z] : graph.cells) {
                x *= mirror;
                for (int turn = 0; turn < rotation; ++turn) {
                    const int nextX = -z;
                    z = x;
                    x = nextX;
                }
                cells.push_back({x, z});
                minX = std::min(minX, x);
                minZ = std::min(minZ, z);
            }
            for (auto &[x, z] : cells) {
                x -= minX;
                z -= minZ;
            }
            std::sort(cells.begin(), cells.end());
            if (best.empty() || cells < best)
                best = cells;
        }
    return best;
}
} // namespace

int main() {
    uint64_t seed = 0;
    try {
        std::set<std::vector<dw::FloorCell>> shapes;
        std::set<std::vector<int>> structures;
        std::set<int> loopCounts, leafCounts, bossDepths, diameters, startDegrees;
        for (int sample = 0; sample < 10004; ++sample) {
            seed = sample < 10000 ? uint64_t(sample) : UINT64_MAX - uint64_t(sample - 10000);
            const auto graph = dw::generateRoomGraph(seed);
            const auto repeated = dw::generateRoomGraph(seed);
            check(graph.cells == repeated.cells && graph.links == repeated.links &&
                      graph.powerRooms == repeated.powerRooms,
                  "the same seed reproduces room positions, connections and special-room count");
            check(std::set<dw::FloorCell>(graph.cells.begin(), graph.cells.end()).size() == dw::RoomCount,
                  "rooms occupy distinct positions");
            check(graph.cells[0] == dw::FloorCell{0, 0}, "the starting room anchors world coordinates");
            check(graph.powerRooms >= 1 && graph.powerRooms <= 2, "power rooms retain their limit");
            const int ordinary = dw::RoomCount - graph.powerRooms - 1;
            std::array<int, dw::RoomCount> degree{};
            std::set<std::pair<int, int>> edges;
            for (auto edge : graph.links) {
                check(edge[0] >= 0 && edge[0] < dw::RoomCount && edge[1] >= 0 && edge[1] < dw::RoomCount,
                      "every passage connects valid rooms");
                const auto [ax, az] = graph.cells[size_t(edge[0])];
                const auto [bx, bz] = graph.cells[size_t(edge[1])];
                check(std::abs(ax - bx) + std::abs(az - bz) == 1,
                      "passages join adjacent cells without crossing or skipping rooms");
                check(edges.insert(std::minmax(edge[0], edge[1])).second, "each passage is unique");
                ++degree[size_t(edge[0])];
                ++degree[size_t(edge[1])];
            }
            const auto depth = distances(graph, 0), unlocked = distances(graph, 0, ordinary);
            check(std::all_of(depth.begin(), depth.end(), [](int d) { return d >= 0; }),
                  "every room belongs to one connected expedition");
            for (int i = 0; i < ordinary; ++i)
                check(unlocked[size_t(i)] >= 0, "ordinary rooms never require a key to reach");
            for (int i = ordinary; i < dw::RoomCount; ++i)
                check(degree[size_t(i)] == 1, "power rooms and the boss are branch ends");
            check(degree[0] >= 2 && degree[0] <= 3 && *std::max_element(degree.begin(), degree.end()) >= 3 &&
                      *std::max_element(degree.begin(), degree.end()) <= 4,
                  "starting choices and junctions have distinct cardinal doorways");
            check(depth.back() >= 3, "the boss lies beyond the starting rooms");
            const int loops = int(graph.links.size()) - dw::RoomCount + 1;
            check(loops >= 0 && loops <= 3, "each graph has a bounded number of optional loops");
            if (sample < 256) {
                shapes.insert(footprint(graph));
                std::vector<int> signature(5 + dw::RoomCount * 2, 0);
                int diameter = 0;
                for (int i = 0; i < dw::RoomCount; ++i) {
                    ++signature[size_t(degree[size_t(i)])];
                    ++signature[size_t(5 + depth[size_t(i)])];
                    const auto from = distances(graph, i);
                    for (int j = i + 1; j < dw::RoomCount; ++j) {
                        ++signature[size_t(5 + dw::RoomCount + from[size_t(j)])];
                        diameter = std::max(diameter, from[size_t(j)]);
                    }
                }
                structures.insert(signature);
                loopCounts.insert(loops);
                leafCounts.insert(signature[1]);
                bossDepths.insert(depth.back());
                diameters.insert(diameter);
                startDegrees.insert(degree[0]);
            }
        }
        check(shapes.size() >= 192, "seeds vary footprints beyond rotations/reflections of one template");
        check(structures.size() >= 64, "seeds vary graph structure beyond room identities and geometry");
        check(loopCounts.size() == 4 && leafCounts.size() >= 3 && bossDepths.size() >= 4 &&
                  diameters.size() >= 4 && startDegrees.size() == 2,
              "seeds vary loops, dead ends, route lengths and the starting branch count");
        std::cout << "PASS 10,004 seeds: deterministic connected graphs, safe passage topology, "
                     "junctions and locked leaves\n"
                  << "PASS 256-seed diversity: " << shapes.size() << " distinct footprints, "
                  << structures.size() << " distinct structural profiles, " << loopCounts.size()
                  << " loop counts, " << leafCounts.size() << " dead-end counts, " << bossDepths.size()
                  << " boss depths, " << diameters.size() << " path diameters\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "FAIL seed " << seed << ": " << error.what() << '\n';
        return 1;
    }
}
