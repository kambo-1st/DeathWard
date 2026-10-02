#include "world/Dungeon.hpp"
#include <queue>

namespace dw {
RoomGraph generateRoomGraph(uint64_t seed, bool tutorial) {
    Random rng(seed ^ 0x544f504f4c4f4759ULL);
    RoomGraph graph;
    if (tutorial) {
        // One short floor: a seeded, non-crossing trail with no locks or branches.
        graph.cells.resize(5);graph.powerRooms=0;
        std::set<FloorCell> occupied{{0,0}};
        const std::array<FloorCell,3> steps{{{0,-1},{1,0},{-1,0}}};
        for (int i=1;i<5;++i) {
            std::vector<FloorCell> options;
            const auto [x,z]=graph.cells[size_t(i-1)];
            for (auto [dx,dz]:steps)if(!occupied.contains({x+dx,z+dz}))options.push_back({x+dx,z+dz});
            const auto cell=options[rng.bounded(uint32_t(options.size()))];
            graph.cells[size_t(i)]=cell;occupied.insert(cell);graph.links.push_back({i-1,i});
        }
        return graph;
    }
    graph.powerRooms = 1 + int(rng.bounded(2));
    const int ordinary = RoomCount - graph.powerRooms - 1;
    const std::array<FloorCell, 4> directions{{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
    auto shuffle = [&](auto &values) {
        for (size_t i = values.size(); i > 1; --i)
            std::swap(values[i - 1], values[rng.bounded(uint32_t(i))]);
    };
    std::set<FloorCell> occupied{{0, 0}};
    std::array<int, RoomCount> degree{};
    auto link = [&](int a, int b) {
        graph.links.push_back({a, b});
        ++degree[size_t(a)];
        ++degree[size_t(b)];
    };
    auto place = [&](int index, int parent, FloorCell cell) {
        graph.cells[size_t(index)] = cell;
        occupied.insert(cell);
        link(parent, index);
    };
    auto openings = [&](int count) {
        std::vector<std::pair<int, FloorCell>> result;
        // The initial routes stay open to ordinary rooms, never directly to a lock.
        for (int parent = 1; parent < count; ++parent)
            for (auto [dx, dz] : directions) {
                const auto [x, z] = graph.cells[size_t(parent)];
                FloorCell cell{x + dx, z + dz};
                if (!occupied.contains(cell))
                    result.push_back({parent, cell});
            }
        return result;
    };
    auto initial = directions;
    shuffle(initial);
    const int exits = 2 + int(rng.bounded(2));
    for (int i = 1; i <= exits; ++i)
        place(i, 0, initial[size_t(i - 1)]);

    // Vary the preference for extending a branch versus growing a new junction.
    // Coordinates are allocated as needed; there is no predefined rectangular footprint.
    const int continuation = 2 + int(rng.bounded(7));
    const int compactness = 1 + int(rng.bounded(4));
    for (int next = exits + 1; next < ordinary; ++next) {
        auto options = openings(next);
        std::vector<uint32_t> weights;
        uint32_t total = 0;
        for (const auto &[parent, cell] : options) {
            int neighbors = 0;
            for (auto [dx, dz] : directions)
                neighbors += occupied.contains({cell.first + dx, cell.second + dz});
            uint32_t weight = uint32_t(1 + compactness * (neighbors - 1));
            if (parent == next - 1)
                weight *= uint32_t(continuation);
            // A soft size preference avoids needlessly long corridors on the minimap,
            // without forcing every seed into the same bounding rectangle.
            if (std::abs(cell.first) + std::abs(cell.second) <= 5)
                weight *= 3;
            weights.push_back(weight);
            total += weight;
        }
        uint32_t choice = rng.bounded(total);
        size_t selected = 0;
        while (choice >= weights[selected])
            choice -= weights[selected++];
        place(next, options[selected].first, options[selected].second);
    }

    // Neighboring branches sometimes reconnect. Zero to three loops gives both
    // tree-like expeditions and maps with alternate routes; locked rooms stay leaves.
    std::vector<std::array<int, 2>> shortcuts;
    for (int a = 1; a < ordinary; ++a)
        for (int b = a + 1; b < ordinary; ++b) {
            const auto [ax, az] = graph.cells[size_t(a)];
            const auto [bx, bz] = graph.cells[size_t(b)];
            const bool linked = std::any_of(graph.links.begin(), graph.links.end(), [&](auto edge) {
                return (edge[0] == a && edge[1] == b) || (edge[0] == b && edge[1] == a);
            });
            if (!linked && std::abs(ax - bx) + std::abs(az - bz) == 1)
                shortcuts.push_back({a, b});
        }
    shuffle(shortcuts);
    const size_t loops = std::min(size_t(rng.bounded(4)), shortcuts.size());
    for (size_t i = 0; i < loops; ++i)
        link(shortcuts[i][0], shortcuts[i][1]);

    std::array<int, RoomCount> depth;
    depth.fill(-1);
    depth[0] = 0;
    std::queue<int> pending;
    pending.push(0);
    while (!pending.empty()) {
        const int at = pending.front();
        pending.pop();
        for (auto edge : graph.links) {
            const int next = edge[0] == at ? edge[1] : edge[1] == at ? edge[0] : -1;
            if (next >= 0 && depth[size_t(next)] < 0) {
                depth[size_t(next)] = depth[size_t(at)] + 1;
                pending.push(next);
            }
        }
    }
    auto bossOptions = openings(ordinary);
    int deepest = 0;
    for (const auto &[parent, cell] : bossOptions)
        deepest = std::max(deepest, depth[size_t(parent)]);
    std::erase_if(bossOptions,
                  [&](const auto &option) { return depth[size_t(option.first)] < std::max(2, deepest - 2); });
    const auto boss = bossOptions[rng.bounded(uint32_t(bossOptions.size()))];
    place(RoomCount - 1, boss.first, boss.second);
    for (int i = 0; i < graph.powerRooms; ++i) {
        auto options = openings(ordinary);
        // At least one cache branches off a route, keeping a genuine junction
        // even in seeds whose ordinary network grew as a long winding path.
        if (i == 0 && std::any_of(options.begin(), options.end(),
                                  [&](const auto &option) { return degree[size_t(option.first)] >= 2; }))
            std::erase_if(options, [&](const auto &option) { return degree[size_t(option.first)] < 2; });
        const auto cache = options[rng.bounded(uint32_t(options.size()))];
        place(RoomCount - 2 - i, cache.first, cache.second);
    }

    // Room identity and objective placement do not dictate the growth order.
    std::vector<int> ids;
    for (int i = 1; i < ordinary; ++i)
        ids.push_back(i);
    shuffle(ids);
    std::array<int, RoomCount> remap;
    for (int i = 0; i < RoomCount; ++i)
        remap[size_t(i)] = i > 0 && i < ordinary ? ids[size_t(i - 1)] : i;
    const auto cells = graph.cells;
    for (int i = 0; i < RoomCount; ++i)
        graph.cells[size_t(remap[size_t(i)])] = cells[size_t(i)];
    for (auto &edge : graph.links)
        for (int &room : edge)
            room = remap[size_t(room)];
    return graph;
}
} // namespace dw
