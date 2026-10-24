// Headless measurements for docs/isaac_expedition_study.md.
// Build instructions are recorded in that report. Does not change gameplay.
#include "world/Dungeon.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cout << "seed,rooms,combat_rooms,boss_rooms,quiet_rooms,power_rooms,shop_rooms,"
                 "map_width,map_depth,mean_room_width,mean_room_depth,mean_usable_room_area,"
                 "mean_corridor_length,min_corridor_length,max_corridor_length,"
                 "boss_graph_distance,configured_enemy_budget\n";
    std::cout << std::fixed << std::setprecision(3);
    for (uint64_t seed : {0ULL, 1ULL, 2ULL, 3ULL, 4ULL, 5ULL, 6ULL, 7ULL, 42ULL, 1866ULL}) {
        dw::Arena arena(seed, dw::MissionTheme::Canyon, true);
        int kinds[5]{};
        float widths = 0, depths = 0, area = 0, lengths = 0, shortest = 1e9f, longest = 0;
        int enemyBudget = 0;
        for (const auto &room : arena.rooms) {
            ++kinds[int(room.kind)];
            widths += room.bounds.max.x - room.bounds.min.x;
            depths += room.bounds.max.z - room.bounds.min.z;
            area += room.usableArea();
            if (room.kind == dw::RoomKind::Combat || room.kind == dw::RoomKind::Boss)
                enemyBudget += std::clamp(int(std::ceil(room.usableArea() / 70.f)), 4, 24);
        }
        for (const auto &passage : arena.passages) {
            const float length = dw::distance(passage.from, passage.to);
            lengths += length;
            shortest = std::min(shortest, length);
            longest = std::max(longest, length);
        }
        // Topological distance with locks ignored, not the required gameplay route.
        std::vector<int> distance(arena.rooms.size(), -1);
        distance[0] = 0;
        std::queue<int> queue;
        queue.push(0);
        while (!queue.empty()) {
            const int current = queue.front();
            queue.pop();
            for (int index : arena.rooms[size_t(current)].passages) {
                const auto &edge = arena.passages[size_t(index)];
                const int next = edge.rooms[0] == current ? edge.rooms[1] : edge.rooms[0];
                if (distance[size_t(next)] >= 0) continue;
                distance[size_t(next)] = distance[size_t(current)] + 1;
                queue.push(next);
            }
        }
        std::cout << seed << ',' << arena.rooms.size() << ','
                  << kinds[int(dw::RoomKind::Combat)] << ',' << kinds[int(dw::RoomKind::Boss)] << ','
                  << kinds[int(dw::RoomKind::Empty)] << ',' << kinds[int(dw::RoomKind::Power)] << ','
                  << kinds[int(dw::RoomKind::Shop)] << ','
                  << arena.bounds.max.x - arena.bounds.min.x << ','
                  << arena.bounds.max.z - arena.bounds.min.z << ','
                  << widths / arena.rooms.size() << ',' << depths / arena.rooms.size() << ','
                  << area / arena.rooms.size() << ',' << lengths / arena.passages.size() << ','
                  << shortest << ',' << longest << ',' << distance.back() << ',' << enemyBudget << '\n';
    }
}
