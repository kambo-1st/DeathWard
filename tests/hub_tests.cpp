#include "world/HubWorld.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace dw;
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
int main() {
    try {
        HubWorld hub;
        check(hub.load(std::filesystem::path(DEATHWARD_ASSET_DIR) / "town/town.nav"),
              "original town navigation loads");
        check(hub.walkableCells() > 10000, "town includes broad connected outdoor streets");
        check(hub.walkable(hub.spawn) && hub.walkable(hub.mission),
              "spawn and mission entrance are valid terrain");
        check(hub.moveTo(hub.mission), "mission station is reachable from the arrival point");
        const auto route = hub.route();
        check(route.size() > 8, "mission station is a real walk through the town");
        for (auto p : route)
            check(hub.walkable(p), "every path waypoint avoids solid scene geometry");
        for (int i = 0; i < 3000 && hub.destination(); ++i) {
            auto previous = hub.player.position;
            hub.step({}, Tick);
            check(hub.walkable(hub.player.position), "automatic movement stays on connected terrain");
            check(std::abs(hub.player.position.y - hub.height(hub.player.position) - .85f) < .001f,
                  "feet follow original ground elevation");
            check(distance(previous, hub.player.position) < .7f, "movement never teleports across colliders");
        }
        check(hub.nearMission() && !hub.destination(), "automatic route arrives and stops at station");
        check(hub.moveTo(hub.spawn), "return route to arrival point exists");
        for (int i = 0; i < 3000 && hub.destination(); ++i)
            hub.step({}, Tick);
        check(distance(hub.player.position, add(hub.spawn, {0, .85f, 0})) < .1f,
              "round trip returns to arrival point");
        for (Vector3 movement : std::array<Vector3, 4>{{{1, 0, 0}, {0, 0, 1}, {-1, 0, 0}, {0, 0, -1}}}) {
            hub.reset();
            for (int i = 0; i < 2000; ++i) {
                hub.step(movement, Tick);
                check(hub.walkable(hub.player.position),
                      "held movement cannot leave terrain or enter collision barriers");
            }
        }
        hub.reset();
        auto ground = hub.pickGround({add(hub.spawn, {0, 20, 0}), {0, -1, 0}});
        check(ground && std::abs(ground->y - hub.spawn.y) < .01f, "mouse ray picks actual terrain height");
        check(!hub.moveTo({10000, 0, 10000}), "unreachable clicks do not invent walkable terrain");
        check(!hub.load(std::filesystem::path(DEATHWARD_ASSET_DIR) / "town/missing.nav"),
              "missing navigation fails safely");
        std::cout << "PASS original town navigation, station round trip, height following, barriers and "
                     "missing assets\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
