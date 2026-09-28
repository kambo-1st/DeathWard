#include "world/Animals.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
float horizontal(Vector3 a, Vector3 b) {
    a.y = b.y = 0;
    return distance(a, b);
}
void same(const Animals &a, const Animals &b) {
    check(a.residents().size() == b.residents().size(), "matching population");
    for (size_t n = 0; n < a.residents().size(); ++n) {
        const auto &x = a.residents()[n], &y = b.residents()[n];
        check(distance(x.position, y.position) < .00001f && distance(x.facing, y.facing) < .00001f &&
                  std::abs(x.phase - y.phase) < .00001 && x.moving == y.moving && x.walking == y.walking,
              "independent fixed-step motion matches at different frame rates");
    }
}
struct Temporary {
    std::filesystem::path path =
        std::filesystem::temp_directory_path() /
        ("deathward-animals-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    ~Temporary() {
        std::filesystem::remove(path);
    }
    void write(const std::string &text) {
        std::ofstream(path) << text;
    }
};
} // namespace
int main() {
    try {
        const auto assets = std::filesystem::path(__FILE__).parent_path().parent_path() / "assets";
        HubWorld hub;
        check(hub.load(assets / "town/town.nav"), "real town navigation loads");
        hub.player.position = {1000, 0, 1000};
        Animals a, b, c;
        const auto placements = assets / "animals/town.animals";
        check(a.load(placements, hub) && b.load(placements, hub) && c.load(placements, hub),
              "animal placements load");
        check(a.residents().size() == 5, "all five residents find clear ground in original town");
        std::array<bool, 4> kinds{};
        for (const auto &animal : a.residents())
            kinds[size_t(animal.kind)] = true;
        check(std::all_of(kinds.begin(), kinds.end(), [](bool value) { return value; }),
              "all four species present");
        check(a.residents()[3].phase != a.residents()[4].phase, "two hens have independent clocks");
        for (int n = 0; n < 600; ++n)
            a.update(1.f / 30, hub);
        for (int n = 0; n < 1200; ++n)
            b.update(1.f / 60, hub);
        for (int n = 0; n < 2400; ++n)
            c.update(1.f / 120, hub);
        same(a, b);
        same(a, c);
        a.update(0, hub);
        a.update(-1, hub);
        a.update(std::numeric_limits<float>::quiet_NaN(), hub);
        same(a, b);
        std::array<float, 5> travel{};
        for (int tick = 0; tick < 7200; ++tick) {
            const auto previous = a.residents();
            a.update(Tick, hub);
            for (size_t n = 0; n < previous.size(); ++n) {
                const auto &animal = a.residents()[n];
                travel[n] += horizontal(previous[n].position, animal.position);
                check(hub.walkable(animal.position) &&
                          std::abs(animal.position.y - hub.height(animal.position)) < .001f,
                      "roaming stays on actual walkable town ground");
                check(horizontal(animal.position, animal.home) <= animal.roam + .01f,
                      "resident stays within its home radius");
                for (int sample = 0; sample < 8; ++sample) {
                    const float angle = sample * Pi / 4, radius = animalRadius(animal.kind) * animal.scale;
                    check(hub.walkable(
                              add(animal.position, {radius * std::cos(angle), 0, radius * std::sin(angle)})),
                          "whole animal footprint clears scenery");
                }
                for (size_t other = 0; other < n; ++other)
                    check(horizontal(animal.position, a.residents()[other].position) >=
                              animalRadius(animal.kind) * animal.scale +
                                  animalRadius(a.residents()[other].kind) * a.residents()[other].scale,
                          "residents avoid each other");
            }
        }
        check(std::all_of(travel.begin(), travel.end(), [](float d) { return d > 1; }),
              "every resident actually walks during two minutes");
        // Insert a current train hull at an active destination. The resident must stop before entry.
        bool blocked = false;
        for (int tick = 0; tick < 1200 && !blocked; ++tick) {
            a.update(Tick, hub);
            for (const auto &animal : a.residents()) {
                if (!animal.moving || horizontal(animal.position, animal.target) < 2.5f)
                    continue;
                const auto center = animal.target;
                MovingSolid train{center, {1, 0, 0}, {.5f, 2, .5f}};
                hub.setMovingSolids({train});
                const size_t index = size_t(&animal - a.residents().data());
                for (int n = 0; n < 600; ++n) {
                    a.update(Tick, hub);
                    check(!train.contains(a.residents()[index].position),
                          "animal avoids current moving hull");
                }
                blocked = true;
                break;
            }
        }
        check(blocked, "dynamic hull fixture exercised");
        hub.setMovingSolids({});
        Temporary file;
        file.write("DEATHWARD_ANIMALS 1\nanimal unknown dragon 0 0 0 1 3 1\n");
        check(!b.load(file.path, hub) && b.residents().empty() && !b.error().empty(),
              "bad species fails cleanly");
        file.write("DEATHWARD_ANIMALS 1\nanimal same cat 3 -2 0 1 3 1\nanimal same hen -1 -9 0 1 3 2\n");
        check(!b.load(file.path, hub), "duplicate stable IDs rejected");
        check(!b.load(file.path / "missing", hub), "missing config reported");
        check(a.load({}, hub) && a.residents().empty() && a.time() == 0,
              "hub without placements clears residents");
        TownDocument document;
        std::string error;
        check(document.load(assets / "town/town.scene", error), "town scene loads");
        check(document.ownsAnimals && document.animals.size() == 5, "format 5 owns the five original homes");
        const auto definitions = loadAnimalPlacements(placements);
        for (size_t n = 0; n < definitions.size(); ++n) {
            const auto &expected = definitions[n], &actual = document.animals[n];
            check(expected.id == actual.id && expected.kind == actual.kind && expected.seed == actual.seed &&
                  expected.yaw == actual.yaw && expected.scale == actual.scale && expected.roam == actual.roam &&
                  horizontal(expected.home, actual.home) == 0, "migration retains exact authored animal settings");
        }
        check(a.reset(document.animals, hub) && b.load(placements, hub), "both animal formats load");
        same(a, b);
        document.animals.back().kind = AnimalKind(size_t(AnimalKind::Count) - 1);
        document.animals.back().seed = UINT32_MAX;
        document.write(file.path);
        TownDocument roundtrip;
        check(roundtrip.load(file.path, error) && roundtrip.ownsAnimals &&
              roundtrip.animals.back().kind == document.animals.back().kind &&
              roundtrip.animals.back().seed == UINT32_MAX, "last catalog species and full seed round trip");
        document.animals.clear();
        document.write(file.path);
        check(roundtrip.load(file.path, error) && roundtrip.ownsAnimals && roundtrip.animals.empty(),
              "an intentionally empty population never restores legacy animals");
        check(a.reset(roundtrip.animals, hub) && a.residents().empty(), "runtime respects empty scene population");
        file.write("DEATHWARD_ANIMALS 1\nanimal huge horse 0 0 0 1 3 4294967296\n");
        check(!a.load(file.path, hub), "oversized seeds are rejected");
        file.write("DEATHWARD_ANIMALS 1\nanimal same horse 0 0 0 1 3 -1\n");
        check(!a.load(file.path, hub), "negative seeds are rejected");
        auto invalid = definitions;
        invalid[0].roam = 21;
        check(!a.reset(invalid, hub), "invalid roaming radius is rejected");
        invalid = definitions;
        invalid[0].kind = AnimalKind::Count;
        check(!a.reset(invalid, hub), "invalid catalog index is rejected before rendering");
        invalid = definitions;
        invalid[0].home = {9999, 0, 9999};
        check(a.reset(invalid, hub, false) && a.residents().size() == invalid.size(),
              "editor can display blocked authored homes so they can be repaired");
        check(horizontal(a.residents()[0].home, invalid[0].home) == 0,
              "editor initialization never silently relocates authored homes");
        std::cout << "PASS animals: seeded roaming, clearance, trains, "
                     "frame rates and reset\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
