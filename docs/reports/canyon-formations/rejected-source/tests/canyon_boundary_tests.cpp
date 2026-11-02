#include "combat/Simulation.hpp"
#include "world/CanyonBoundary.hpp"
#include "world/Dungeon.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
bool same(Vector3 a, Vector3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
void modeEnvironment(const char *value) {
#ifdef _WIN32
    _putenv_s("DEATHWARD_CANYON_BOUNDARY", value ? value : "");
#else
    if (value)
        setenv("DEATHWARD_CANYON_BOUNDARY", value, 1);
    else
        unsetenv("DEATHWARD_CANYON_BOUNDARY");
#endif
}
struct Mode {
    std::optional<std::string> previous;
    explicit Mode(const char *value) {
        if (auto p = std::getenv("DEATHWARD_CANYON_BOUNDARY"))
            previous = p;
        modeEnvironment(value);
    }
    ~Mode() {
        if (previous)
            modeEnvironment(previous->c_str());
        else
            modeEnvironment(nullptr);
    }
};
double classicMs = 0, organicMs = 0;
int pairedMaps = 0;
Arena make(uint64_t seed, bool river, bool tutorial, const char *mode, bool measure = true) {
    Mode setting(mode);
    auto start = std::chrono::steady_clock::now();
    Arena result(seed, MissionTheme::Canyon, river, tutorial);
    double elapsed =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
    if (measure && !tutorial) {
        if (std::string_view(mode) == "classic") {
            classicMs += elapsed;
            ++pairedMaps;
        } else
            organicMs += elapsed;
    }
    return result;
}
void dump(const Arena &classic, const Arena &organic, const char *directory) {
    std::ofstream cells(std::string(directory) + "/floor-grid.csv");
    cells << "x,z,classic,organic\n";
    const auto b = organic.rooms[2].bounds;
    for (float z = b.min.z - 5; z <= b.max.z + 5; z += .5f)
        for (float x = b.min.x - 5; x <= b.max.x + 5; x += .5f)
            cells << x << ',' << z << ',' << !classic.canyon->blocked({x, .85f, z}, 0) << ','
                  << !organic.canyon->blocked({x, .85f, z}, 0) << '\n';
    std::ofstream roads(std::string(directory) + "/road.csv");
    roads << "x,z\n";
    for (auto p : organic.canyon->road)
        roads << p.position.x << ',' << p.position.z << '\n';
    std::ofstream sockets(std::string(directory) + "/sockets.csv");
    sockets << "x,z\n";
    for (int link : organic.rooms[2].passages)
        for (auto p : {organic.passages[size_t(link)].from, organic.passages[size_t(link)].to})
            sockets << p.x << ',' << p.z << '\n';
}
} // namespace
int main(int argc, char **argv) {
    try {
        size_t changed = 0, roads = 0, sockets = 0;
        std::set<int> rivers;
        for (uint64_t seed : {0ULL, 1ULL, 2ULL, 7ULL, 42ULL, 1866ULL, 69175541ULL})
            for (bool river : {false, true}) {
                auto classic = make(seed, river, false, "classic"),
                     organic = make(seed, river, false, "organic"),
                     repeat = make(seed, river, false, "organic", false);
                check(classic.rooms.size() == organic.rooms.size() &&
                          classic.passages.size() == organic.passages.size(),
                      "room graph dimensions preserved");
                check(organic.canyon->heights == repeat.canyon->heights &&
                          organic.floorCells == repeat.floorCells,
                      "organic collision and navigation replay from seed");
                for (size_t i = 0; i < organic.rooms.size(); ++i) {
                    const auto &a = classic.rooms[i], &b = organic.rooms[i];
                    check(same(a.center, b.center) && same(a.entry, b.entry) && same(a.exit, b.exit) &&
                              same(a.objective, b.objective) && same(a.bounds.min, b.bounds.min) &&
                              same(a.bounds.max, b.bounds.max) && a.passages == b.passages &&
                              a.kind == b.kind,
                          "room identity, bounds, anchors and adjacency preserved");
                    check(!organic.canyon->blocked(b.center, .6f) && !organic.canyon->blocked(b.entry, .6f) &&
                              !organic.canyon->blocked(b.exit, .6f),
                          "room core and arrival/exit clearances preserved");
                }
                for (size_t i = 0; i < organic.passages.size(); ++i) {
                    const auto &a = classic.passages[i], &b = organic.passages[i];
                    check(a.rooms == b.rooms && a.locked == b.locked && same(a.from, b.from) &&
                              same(a.to, b.to),
                          "passage graph and socket transforms preserved");
                    check(!organic.canyon->blocked(b.from, .6f) && !organic.canyon->blocked(b.to, .6f),
                          "both passage sockets remain physically clear");
                    sockets += 2;
                }
                const auto &a = *classic.canyon, &b = *organic.canyon;
                check(b.road.size() == repeat.canyon->road.size(),
                      "independent seed replay preserves road count");
                for (size_t i = 0; i < b.road.size(); ++i)
                    check(same(b.road[i].position, repeat.canyon->road[i].position) &&
                              b.road[i].width == repeat.canyon->road[i].width,
                          "independent seed replay preserves road transforms");
                check(a.road.size() == b.road.size() && a.roadRooms == b.roadRooms &&
                          a.roadPassages == b.roadPassages,
                      "original road membership and samples preserved");
                for (size_t i = 0; i < a.road.size(); ++i) {
                    check(same(a.road[i].position, b.road[i].position) &&
                              a.road[i].width == b.road[i].width && a.road[i].along == b.road[i].along,
                          "road course, width and rut coordinates byte-identical");
                    ++roads;
                }
                check(a.riverKind == b.riverKind && a.river.size() == b.river.size(),
                      "river category and course retained");
                for (size_t i = 0; i < a.river.size(); ++i)
                    check(same(a.river[i].position, b.river[i].position) &&
                              a.river[i].width == b.river[i].width,
                          "river centerline and widths retained");
                size_t local = 0;
                for (size_t i = 0; i < a.heights.size(); ++i)
                    if ((a.heights[i] <= CanyonTerrain::WalkableHeight) !=
                        (b.heights[i] <= CanyonTerrain::WalkableHeight))
                        ++local;
                check(local > 20, "actual playable outline changes, not only the visual mesh");
                changed += local;
                rivers.insert(int(b.riverKind));
                if (argc > 1 && seed == 1866 && !river)
                    dump(classic, organic, argv[1]);
            }
        for (uint64_t seed : {0ULL, 42ULL, 1866ULL}) {
            auto a = make(seed, true, true, "organic");
            check(a.roomCount() == 5, "tutorial retains five rooms");
            for (auto &r : a.rooms)
                check(!a.canyon->blocked(r.center, .6f), "tutorial cores stay clear");
        }
        if (argc > 1) {
            Mode organicMode("organic");
            Simulation initial(1866, 1, {}, MissionTheme::Canyon, true);
            int floor = 0;
            while (initial.expedition.profileOnFloor(floor).band < 2)
                ++floor;
            Simulation organic(1866, 1, {}, MissionTheme::Canyon, true, false, WitnessAccount::None, floor);
            {
                Mode classicMode("classic");
                Simulation classic(1866, 1, {}, MissionTheme::Canyon, true, false, WitnessAccount::None,
                                   floor);
                dump(classic.arena, organic.arena, argv[1]);
            }
        }
        check(rivers.size() == 3, "dry, boundary and interior river layouts covered");
        std::cout << "GENERATION paired_maps=" << pairedMaps << " classic_mean_ms=" << classicMs / pairedMaps
                  << " organic_mean_ms=" << organicMs / pairedMaps << "\n";
        std::cout << "PASS organic boundaries maps=14 changed_vertices=" << changed
                  << " identical_road_samples=" << roads << " clear_sockets=" << sockets
                  << " tutorial_maps=3\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
