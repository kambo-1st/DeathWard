#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
bool same(Box a, Box b) {
    return distance(a.min, b.min) < .0001f && distance(a.max, b.max) < .0001f;
}
void sameBoxes(const std::vector<Box> &a, const std::vector<Box> &b) {
    check(a.size() == b.size(), "themes preserve geometry counts");
    for (size_t i = 0; i < a.size(); ++i)
        check(same(a[i], b[i]), "themes preserve exact collision and walkable bounds");
}
} // namespace
int main() {
    const auto path = std::filesystem::temp_directory_path() /
                      ("deathward-theme-" +
                       std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".save");
    try {
        bool mine = false, canyon = false;
        for (uint64_t seed = 0; seed < 128; ++seed) {
            const auto theme = resolveTheme(ThemeChoice::Seeded, seed);
            check(theme == resolveTheme(ThemeChoice::Seeded, seed), "seeded theme choice is reproducible");
            mine |= theme == MissionTheme::Mine;
            canyon |= theme == MissionTheme::Canyon;
            check(resolveTheme(ThemeChoice::Mine, seed) == MissionTheme::Mine &&
                      resolveTheme(ThemeChoice::Canyon, seed) == MissionTheme::Canyon,
                  "explicit theme choices override the seed");
        }
        check(mine && canyon, "random offers include both mission themes");
        for (const auto theme : {MissionTheme::Mine, MissionTheme::Canyon})
            check(Simulation::roomName(-1, theme) == Simulation::roomName(0, theme) &&
                      Simulation::roomName(999, theme) == Simulation::roomName(RoomCount - 1, theme),
                  "themed room names clamp out-of-range indices");
        for (uint64_t seed : {0ULL, 1ULL, 42ULL, 1866ULL, 69175541ULL}) {
            std::cerr << "Checking canyon seed " << seed << "\n";
            Simulation a(seed, 1, WorldState{}, MissionTheme::Canyon),
                b(seed, 1, WorldState{}, MissionTheme::Canyon);
            check(a.arena.canyon && a.arena.boundaryWalls.empty() && a.arena.obstacles.empty(),
                  "canyon collision comes from terrain, without rectangular walls or cover proxies");
            check(a.arena.canyon->heights == b.arena.canyon->heights &&
                      a.arena.floorCells == b.arena.floorCells,
                  "the same canyon seed reproduces its terrain and navigable cells");
            sameBoxes(a.arena.floors, b.arena.floors);
            check(a.summary().expedition == "Redstone Canyon", "summaries preserve the canyon theme");
            auto route = [&](Vector3 from, Vector3 to) {
                if (a.arena.blocked(from, .6f) || a.arena.blocked(to, .6f))
                    std::cerr << "Blocked endpoint " << from.x << "," << from.z << " -> " << to.x << ","
                              << to.z << "\n";
                check(!a.arena.blocked(from, .6f) && !a.arena.blocked(to, .6f),
                      "canyon route endpoints are clear");
                const auto points = a.arena.path(from, to, .6f);
                if (points.empty())
                    std::cerr << "No path " << from.x << "," << from.z << " -> " << to.x << "," << to.z
                              << "\n";
                check(!points.empty() && distance(points.back(), to) < .01f,
                      "canyon destination is reachable");
                for (auto next : points) {
                    check(a.arena.clear(from, next, .6f), "smoothed routes respect the terrain surface");
                    const int steps = std::max(1, int(distance(from, next) / .2f));
                    for (int i = 0; i <= steps; ++i)
                        check(!a.arena.blocked(add(from, mul(sub(next, from), float(i) / steps)), .6f),
                              "a route stays on navigable terrain");
                    from = next;
                }
            };
            for (auto &p : a.arena.passages) {
                p.locked = false;
                p.sealed = {false, false};
            }
            a.arena.rebuildWalls();
            for (const auto &room : a.arena.rooms) {
                check(room.usableArea() > 150 && room.usableArea() < 1600,
                      "canyon enemy area follows the basin's usable ground");
                route(room.entry, room.center);
                route(room.center, room.objective);
                route(room.center, room.exit);
            }
            bool bends = false;
            for (size_t i = 0; i < a.arena.passages.size(); ++i) {
                route(a.arena.doorApproach(int(i), 0), a.arena.doorApproach(int(i), 1));
                const auto &trail = a.arena.canyon->trails[i];
                const auto midpoint = mul(add(trail.front(), trail.back()), .5f);
                bends |= distance(midpoint, trail[trail.size() / 2]) > 1;
            }
            check(bends, "canyon passages wind between basins");
            for (int room = 0; room < RoomCount; ++room) {
                a.jumpDebug(room);
                b.jumpDebug(room);
                check(a.enemies.size() == b.enemies.size(), "seeded canyon populations repeat");
                check(int(a.livingEnemies()) == a.roomEnemyCount(room),
                      "canyon groups including the finale and companions respect the area budget");
                for (size_t i = 0; i < a.enemies.size(); ++i) {
                    check(a.enemies[i].kind == EnemyKind::Monster && a.enemies[i].monster != 0,
                          "every canyon enemy including the final encounter is from the Isaac catalog");
                    check(a.enemies[i].kind == b.enemies[i].kind &&
                              a.enemies[i].monster == b.enemies[i].monster &&
                              distance(a.enemies[i].position, b.enemies[i].position) < .001f,
                          "canyon encounters repeat their types and positions");
                    check(!a.arena.blocked(a.enemies[i].position, a.enemies[i].radius),
                          "enemies spawn clear of terrain");
                }
                if (a.arena.rooms[size_t(room)].kind == RoomKind::Combat) {
                    for (int p : a.arena.rooms[size_t(room)].passages) {
                        const int side = a.arena.passages[size_t(p)].rooms[0] == room ? 0 : 1;
                        check(
                            a.arena
                                .path(a.arena.doorApproach(p, side), a.arena.doorApproach(p, 1 - side), .48f)
                                .empty(),
                            "terrain necks cannot bypass combat seals");
                    }
                }
            }
            a.killAll();
            a.step({});
            check(a.roomClear && a.bossKilled && !a.boss(),
                  "clearing the canyon finale satisfies its objective without a Sheriff");
            a.startBoss();
            check(!a.roomClear && !a.bossKilled && !a.boss() && a.roomThreats() > 0,
                  "replaying the canyon finale restores its monster group");
            a.clearRoomDebug();
            a.spawnEnemies(30);
            a.godMode = true;
            a.step({});
            for (const auto &enemy : a.enemies)
                check(enemy.kind == EnemyKind::Monster,
                      "random canyon cheat spawns keep the Isaac-only roster");
            const auto &field = *a.arena.canyon;
            const float seamX = field.x + float(field.width / 2) * field.step;
            const float seamZ = field.z + float(field.depth / 2) * field.step;
            const auto seam = field.trace({seamX, 30, seamZ}, {seamX, -4, seamZ});
            check(seam.hit && std::abs(30 - 34 * seam.t - field.height(seamX, seamZ)) < .002f,
                  "terrain rays have no cracks at shared triangle vertices");
            for (int z = 2; z < field.depth - 2; z += 7)
                for (int x = 2; x < field.width - 2; x += 7) {
                    const float px = field.x + (x + .37f) * field.step,
                                pz = field.z + (z + .61f) * field.step;
                    const auto hit = field.trace({px, 30, pz}, {px, -4, pz});
                    check(hit.hit && std::abs(30 - 34 * hit.t - field.height(px, pz)) < .002f,
                          "vertical terrain ray hits agree with the triangulated surface");
                    check(hit.normal.y > 0, "terrain normals point out of the solid ground");
                }
        }
        {
            CampaignStore store(path);
            const auto id = store.begin(1866, "Redstone Canyon");
            check(store.data().pending->expedition == "Redstone Canyon",
                  "the initial pending checkpoint records the theme");
            Simulation run(1866, id, store.data().world, MissionTheme::Canyon);
            store.checkpoint(run.summary());
        }
        {
            CampaignStore store(path);
            check(store.recover(), "interrupted themed expedition recovers");
            check(store.data().history.back().expedition == "Redstone Canyon",
                  "interruption history preserves the canyon mission");
            auto id = store.begin(1866, "Redstone Canyon");
            Simulation run(1866, id, store.data().world, MissionTheme::Canyon);
            run.startBoss();
            run.killAll();
            run.step({});
            run.player.position = run.arena.exit;
            run.interact();
            check(run.finished, "the canyon exit works after defeating its monster group");
            store.resolve(run.summary(), EndReason::Victory);
            check(store.data().world.flags.contains("canyon_cleared") && !store.data().world.bossDefeated &&
                      !store.data().world.flags.contains("hollow_sheriff_dead"),
                  "canyon victory persists independently of the mine's Sheriff");
            Simulation mineRun(1866, 3, store.data().world, MissionTheme::Mine);
            mineRun.startBoss();
            check(mineRun.boss() && !mineRun.followup,
                  "the mine still contains its Sheriff after completing the canyon");
            mineRun.clearRoomDebug();
            mineRun.spawnEnemies(30);
            mineRun.godMode = true;
            mineRun.step({});
            for (const auto &enemy : mineRun.enemies)
                check(enemy.kind != EnemyKind::Monster, "random mine cheat spawns retain Western enemies");
            Simulation canyonReturn(1866, 4, store.data().world, MissionTheme::Canyon);
            check(canyonReturn.followup && canyonReturn.bossKilled,
                  "a return canyon visit recognizes its own previous completion");
        }
        std::filesystem::remove(path);
        std::cout << "PASS seeded/explicit themes, organic terrain, connected routes, seals, reproducible "
                     "encounters, named locations and "
                     "saved theme recovery\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
