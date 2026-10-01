#include "world/Dungeon.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
void verify(uint64_t seed, bool river) {
    Arena arena(seed, MissionTheme::Canyon, river);
    const auto &field = *arena.canyon;
    check(field.road.size() > 20 && field.roadRooms.size() == 3 && field.roadPassages.size() == 2,
          "sampled layouts provide one continuous road through three connected rooms");
    check(arena.roomAt(add(field.road.front().position, {0, .85f, 0})) == field.roadRooms.front() &&
              arena.roomAt(add(field.road.back().position, {0, .85f, 0})) == field.roadRooms.back(),
          "the road reaches both declared endpoint rooms without truncating at a bend");
    const auto heights = field.heights;
    const auto floors = arena.floorCells;
    auto repeat = arena;
    repeat.canyon = std::make_shared<CanyonTerrain>(field);
    planCanyonRoad(repeat);
    check(heights == repeat.canyon->heights && floors == repeat.floorCells,
          "road planning never changes terrain or navigation");
    check(field.road.size() == repeat.canyon->road.size() && field.roadRooms == repeat.canyon->roadRooms,
          "the same seed repeats its road route");
    for (size_t i = 0; i < field.road.size(); ++i) {
        const auto &p = field.road[i], &other = repeat.canyon->road[i];
        check(distance(p.position, other.position) < .00001f && p.width == other.width &&
                  p.along == other.along,
              "road positions, widths and wheel-rut coordinates repeat");
        const auto water = field.riverSample(p.position);
        check(water.distance > water.width + p.width + .5f,
              "the complete road and its shoulders remain separate from rivers");
        for (size_t j = i + 1; j < field.road.size(); ++j)
            if (field.road[j].along - p.along > 10)
                check(distance(p.position, field.road[j].position) >= 3.8f,
                      "distant stretches of the road never overlap each other");
        if (i == 0)
            continue;
        const auto &a = field.road[i - 1];
        check(p.along > a.along && distance(p.position, a.position) < 3.2f,
              "the road has continuous ordered segments");
        const int steps = std::max(1, int(std::ceil(distance(a.position, p.position) / .2f)));
        for (int n = 0; n <= steps; ++n) {
            const auto q = add(a.position, mul(sub(p.position, a.position), float(n) / steps));
            for (int k = 0; k < 12; ++k) {
                const float angle = k * Pi / 6;
                const auto edge =
                    add(q, {(p.width + .4f) * std::cos(angle), 0, (p.width + .4f) * std::sin(angle)});
                const float h = field.height(edge.x, edge.z);
                check(h >= -.015f && h < .12f, "road shoulders never paint water, cliffs or solid cover");
            }
        }
    }
    for (int room : field.roadRooms) {
        if (field.riverKind == CanyonRiverKind::Interior)
            check(std::find(field.riverRooms.begin(), field.riverRooms.end(), room) == field.riverRooms.end(),
                  "interior river and road regions occupy separate rooms");
        const auto &layout = arena.rooms[size_t(room)];
        const auto size = sub(layout.bounds.max, layout.bounds.min);
        check(field.roadSample(layout.center).distance < std::min(size.x, size.z) * .25f,
              "the worn track passes through the interior of each selected room");
    }
    for (int link : field.roadPassages) {
        const auto &p = arena.passages[size_t(link)];
        for (auto gate : {p.from, p.to})
            check(field.roadSample(gate).distance < 1, "roads align with existing passage entrances");
    }
    for (auto &p : arena.passages) {
        p.locked = false;
        p.sealed = {false, false};
    }
    const int middle = field.roadRooms[1];
    arena.sealRoom(middle);
    for (int link : arena.rooms[size_t(middle)].passages) {
        const auto &p = arena.passages[size_t(link)];
        const int other = p.rooms[0] == middle ? p.rooms[1] : p.rooms[0];
        check(arena.path(arena.rooms[size_t(middle)].center, arena.rooms[size_t(other)].center, .48f).empty(),
              "a road never creates a bypass around sealed room exits");
    }
    std::cout << "PASS road seed " << seed << " river " << int(field.riverKind) << ": "
              << int(field.road.back().along) << "m, rooms";
    for (int room : field.roadRooms)
        std::cout << ' ' << room + 1;
    std::cout << '\n';
}
} // namespace
int main() {
    try {
        for (uint64_t seed : {0ULL, 1ULL, 2ULL, 3ULL, 4ULL, 5ULL, 6ULL, 7ULL, 42ULL, 1866ULL, 69175541ULL})
            verify(seed, true);
        for (uint64_t seed : {42ULL, 1866ULL})
            verify(seed, false);
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
