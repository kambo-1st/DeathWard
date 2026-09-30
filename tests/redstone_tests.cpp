#include "world/HubWorld.hpp"
#include "world/ObjectAnimation.hpp"
#include "world/TownCharacters.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok) throw std::runtime_error(message);
}
Vector3 position(Matrix m) { return {m.m12, m.m13, m.m14}; }
void walk(HubWorld &hub, Vector3 target) {
    check(hub.walkable(target), "Authored destination is clear ground");
    target.y = hub.height(target);
    check(hub.moveTo(target), "A route connects the camp, fort and railway");
    for (int n = 0; n < 5000 && hub.destination(); ++n) {
        const auto before = hub.player.position;
        hub.step({}, Tick);
        check(hub.walkable(hub.player.position) && distance(before, hub.player.position) < .7f,
              "Navigation follows terrain without crossing walls or teleporting");
    }
    check(!hub.destination() && distance(hub.player.position, add(target, {0,.85f,0})) < .1f,
          "The player reaches the requested landmark");
}
}
int main() {
    try {
        const auto directory = std::filesystem::path(DEATHWARD_ASSET_DIR) / "redstone";
        TownDocument doc;
        std::string error;
        check(doc.load(directory / "town.scene", error), "Redstone scene loads");
        int tents = 0, wagons = 0, walls = 0, stacks = 0, wheels = 0;
        size_t engine = 0;
        for (size_t n = 0; n < doc.instances.size(); ++n) {
            const auto &i = doc.instances[n];
            const auto &label = doc.assets[i.asset].label;
            check(label.find("TrainStation") == std::string::npos, "The canyon contains no station or platform");
            tents += label.find("Tent_") != std::string::npos;
            wagons += label == "SM_Veh_Wagon_Travel_01";
            walls += label.find("Fort_Wall_") != std::string::npos;
            if (label == "SM_Veh_Train_01_Alt_Smokestack") { ++stacks; engine = n; }
            wheels += i.wheelRadius > 0;
        }
        check(tents >= 12 && wagons >= 8 && walls >= 20, "The original fort and expanded settler camp are present");
        check(doc.paths.size() == 1 && doc.groups.size() == 4 && stacks == 1 && wheels == 8,
              "One locomotive, tender and two carriages retain their linked animation");
        check(doc.paths.front().dwell == 0, "The stationless train has no scheduled stop");
        check(doc.paths.front().speed == 0, "The storm has stranded the train");
        check(doc.characters.size() == 15, "The hub has a provisional cast and ambient residents");
        HubWorld hub;
        check(hub.load(directory / "town.nav"), "Redstone navigation loads");
        check(hub.walkableCells() > 800000, "The full restored canyon retains its explorable scale");
        ObjectAnimationSystem parked;
        parked.reset(doc);
        hub.setMovingSolids(parked.solids());
        const auto arrival = hub.spawn;
        walk(hub, hub.mission);
        walk(hub, {4,0,-39});
        walk(hub, {7,0,-26});
        walk(hub, {-1,0,-13});
        walk(hub, {0,0,10});
        walk(hub, {0,0,23});
        walk(hub, arrival);
        walk(hub, {-38,0,-54});
        for (const auto &resident : doc.characters) {
            if (!hub.walkable(resident.position))
                throw std::runtime_error("Resident starts on blocked ground: " + resident.id);
            for (const auto &stop : resident.stops)
                check(hub.walkable(stop), "Residents' authored stops are clear ground");
            walk(hub, resident.position);
        }
        check(!hub.walkable({21.5f,0,-26}), "Fort walls remain solid");
        ObjectAnimationSystem motion;
        motion.reset(doc);
        for (int n = 0; n < 60 * 30; ++n) motion.update(Tick, {});
        check(motion.pathDistance() == 0 && motion.pathSpeed() == 0 && motion.solids().size() == 4,
              "The train stays parked with all four vehicle colliders active");
        TownCharacters residents;
        residents.reset(doc, hub);
        for (int n = 0; n < 60 * 90; ++n) residents.update(Tick, hub);
        for (const auto &resident : residents.residents())
            if (resident.blocked || (!resident.definition.stops.empty() && resident.visits < 2))
                throw std::runtime_error("Resident route does not circulate: " + resident.definition.id);
        // Its editor route remains usable for a later authored departure.
        doc.paths.front().speed = 3;
        motion.reset(doc);
        for (int n = 0; n < 220 * 60; ++n) {
            const auto before = position(motion.poses()[engine].transform);
            motion.update(Tick, {});
            check(distance(before, position(motion.poses()[engine].transform)) < .12f,
                  "The train crosses bends and the loop seam continuously");
            if (n > 5 * 60)
                check(motion.pathSpeed() > 2.9f, "A route with zero station wait never brakes at the loop seam");
        }
        check(motion.pathDistance() > 600 && motion.solids().size() == 4,
              "The complete convoy travels beyond one circuit with moving collision");
        const auto traveled = motion.pathDistance();
        motion.update(0, {});
        check(motion.pathDistance() == traveled, "Pause holds the canyon train");
        std::cout << "PASS story hub routes, residents, original fort, expanded camp, parked train and retained departure animation\n";
    } catch (const std::exception &e) { std::cerr << "FAIL " << e.what() << '\n'; return 1; }
}
