#include "world/HubWorld.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace dw;
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
namespace {
struct TerrainFixture {
    uint32_t width = 64, depth = 64;
    float cell = .4f;
    Vector3 spawn{2.1f, 0, 2.13f}, mission{18.1f, 0, 18.13f};
    std::vector<float> heights = std::vector<float>(size_t(width) * depth, 0);
    std::filesystem::path path =
        std::filesystem::temp_directory_path() /
        ("deathward-hub-mouse-" +
         std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".nav");
    ~TerrainFixture() {
        std::filesystem::remove(path);
    }
    void block(int x, int z) {
        heights[size_t(z) * width + size_t(x)] = std::numeric_limits<float>::quiet_NaN();
    }
    void load(HubWorld &hub) {
        std::ofstream f(path, std::ios::binary);
        auto write = [&](const auto &v) { f.write(reinterpret_cast<const char *>(&v), sizeof(v)); };
        f.write("DWTNAV01", 8);
        write(width);
        write(depth);
        const float origin = 0;
        write(origin);
        write(origin);
        write(cell);
        write(spawn.x);
        write(spawn.y);
        write(spawn.z);
        write(mission.x);
        write(mission.y);
        write(mission.z);
        f.write(reinterpret_cast<const char *>(heights.data()),
                std::streamsize(heights.size() * sizeof(float)));
        f.close();
        check(hub.load(path), "regression terrain loads");
    }
};
float horizontalDistance(Vector3 a, Vector3 b) {
    a.y = b.y = 0;
    return distance(a, b);
}
float follow(HubWorld &hub, Vector3 target) {
    float traveled = 0;
    for (int i = 0; i < 5000 && hub.destination(); ++i) {
        auto before = hub.player.position;
        hub.step({}, Tick);
        check(hub.walkable(hub.player.position), "mouse route never enters a blocked terrain cell");
        traveled += horizontalDistance(before, hub.player.position);
    }
    check(!hub.destination() && horizontalDistance(hub.player.position, target) < .0001f,
          "mouse movement reaches the requested point exactly");
    return traveled;
}
void mouseRegressions() {
    TerrainFixture fixture;
    HubWorld hub;
    fixture.load(hub);
    Vector3 target{12.13f, 0, 13.27f};
    check(hub.moveTo(target) && hub.route().size() == 1, "open ground uses one direct diagonal segment");
    check(distance(*hub.destination(), target) < .0001f, "mouse destinations retain sub-cell precision");
    check(std::abs(follow(hub, target) - horizontalDistance(fixture.spawn, target)) < .001f,
          "an open diagonal does not walk a staircase or a right-angle detour");
    hub.reset();
    target = add(fixture.spawn, {.07f, 0, .08f});
    check(hub.moveTo(target), "small click inside the player's current cell is accepted");
    follow(hub, target);
    // Replanning while held must continue forward smoothly without resetting to
    // tile centers, including when the camera makes the cursor drift slightly.
    hub.reset();
    target = {13.13f, 0, 15.27f};
    float before = horizontalDistance(hub.player.position, target);
    for (int i = 0; i < 100; ++i) {
        if (i % 6 == 0)
            check(hub.moveTo(target), "held movement can refresh the route");
        hub.step({}, Tick);
        float after = horizontalDistance(hub.player.position, target);
        check(after < before, "held clicks make continuous forward progress");
        before = after;
    }
    follow(hub, target);
    for (int z = 0; z < 25; ++z)
        for (int x = 12; x < 15; ++x)
            fixture.block(x, z);
    fixture.load(hub);
    target = {11.13f, 0, 2.07f};
    check(hub.moveTo(target) && hub.route().size() > 1 && hub.route().size() < 10,
          "blocked routes retain obstacle turns while removing grid steps");
    auto anchor = fixture.spawn;
    for (auto end : hub.route()) {
        const int samples = int(std::ceil(horizontalDistance(anchor, end) / .01f));
        for (int i = 0; i <= samples; ++i)
            check(hub.walkable(add(anchor, mul(sub(end, anchor), float(i) / std::max(1, samples)))),
                  "every smoothed segment stays outside the obstacle");
        anchor = end;
    }
    follow(hub, target);
    hub.reset();
    target = {5.4f, 0, 4.13f};
    auto picked = hub.pickGround({add(target, {0, 20, 0}), {0, -1, 0}});
    check(picked && !hub.walkable(*picked) && hub.moveTo(*picked),
          "clicking blocked ground requests the nearest walkable edge instead of ignoring the click");
    follow(hub, *hub.destination());
    std::fill(fixture.heights.begin(), fixture.heights.end(), 0);
    fixture.block(6, 5);
    fixture.block(5, 6);
    fixture.spawn = {2.2f, 0, 2.2f};
    fixture.load(hub);
    target = {2.6f, 0, 2.6f};
    check(hub.moveTo(target) && hub.route().size() > 1,
          "mouse shortcuts cannot squeeze through a blocked corner");
    check(follow(hub, target) > 1, "corner barriers require a real detour");
    // A long gentle slope is valid even when its endpoints differ by > step height.
    for (uint32_t z = 0; z < fixture.depth; ++z)
        for (uint32_t x = 0; x < fixture.width; ++x)
            fixture.heights[size_t(z) * fixture.width + x] = float(x) * .1f;
    fixture.load(hub);
    hub.player.position.y = hub.height(hub.player.position) + .85f;
    target = {13.13f, 0, 13.27f};
    target.y = hub.height(target);
    check(hub.moveTo(target) && hub.route().size() == 1, "smooth mouse routes follow a long gradual slope");
    follow(hub, target);
    // Small visible patches next to holes were missed by the old 0.2-unit ray march.
    std::fill(fixture.heights.begin(), fixture.heights.end(), std::numeric_limits<float>::quiet_NaN());
    fixture.heights[5 * fixture.width + 5] = 0;
    fixture.mission = fixture.spawn;
    fixture.load(hub);
    for (float x : {2.0001f, 2.003f, 2.02f, 2.2f, 2.38f, 2.3999f})
        for (float z : {2.0001f, 2.003f, 2.02f, 2.2f, 2.38f, 2.3999f}) {
            Vector3 goal{x, 0, z};
            // Set the fallback plane to a different height so it cannot mask a missed surface.
            hub.player.position.y = 4.85f;
            for (Vector3 offset : std::array<Vector3, 3>{{{23, 30, 23}, {-23, 30, -23}, {0, 30, 0}}}) {
                auto origin = add(goal, offset);
                auto hit = hub.pickGround({origin, unit(sub(goal, origin))});
                check(hit && distance(*hit, goal) < .0001f,
                      "oblique and vertical mouse rays hit tiny ground edges precisely");
            }
        }
    check(!hub.pickGround({{0, 20, 0}, {0, 1, 0}}), "upward rays never create ground clicks");
}
} // namespace
int main() {
    try {
        mouseRegressions();
        for (const auto *pack : {"town", "frontier"}) {
            HubWorld hub;
            check(hub.load(std::filesystem::path(DEATHWARD_ASSET_DIR) / pack / "town.nav"),
                  "original town navigation loads");
            check(hub.walkableCells() > 10000, "town includes broad connected outdoor streets");
            check(hub.walkable(hub.spawn) && hub.walkable(hub.mission),
                  "spawn and mission entrance are valid terrain");
            check(hub.moveTo(hub.mission), "mission station is reachable from the arrival point");
            const auto route = hub.route();
            check(!route.empty() && horizontalDistance(hub.spawn, hub.mission) > 8,
                  "mission station remains a real walk through the town");
            for (auto p : route)
                check(hub.walkable(p), "every path waypoint avoids solid scene geometry");
            for (int i = 0; i < 3000 && hub.destination(); ++i) {
                auto previous = hub.player.position;
                hub.step({}, Tick);
                check(hub.walkable(hub.player.position), "automatic movement stays on connected terrain");
                check(std::abs(hub.player.position.y - hub.height(hub.player.position) - .85f) < .001f,
                      "feet follow original ground elevation");
                check(distance(previous, hub.player.position) < .7f,
                      "movement never teleports across colliders");
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
            check(ground && std::abs(ground->y - hub.spawn.y) < .01f,
                  "mouse ray picks actual terrain height");
            check(!hub.moveTo({10000, 0, 10000}), "unreachable clicks do not invent walkable terrain");
            check(!hub.load(std::filesystem::path(DEATHWARD_ASSET_DIR) / pack / "missing.nav"),
                  "missing navigation fails safely");
        }
        std::cout << "PASS both hub navigation packs, mission round trips, height following, barriers and "
                     "missing assets; precise mouse picking, direct/smoothed routes and held steering\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
