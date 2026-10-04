#include "world/TownNavigation.hpp"
#include "world/HubWorld.hpp"
#include "raymath.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
template <typename F> void rejects(F fn, const char *message) {
    bool failed = false;
    try { fn(); } catch (const std::exception &) { failed = true; }
    check(failed, message);
}
TownWalkArea rectangle(std::string id, bool blocked, float x0, float z0, float x1, float z1) {
    return {std::move(id), blocked, {{x0,0,z0},{x1,0,z0},{x1,0,z1},{x0,0,z1}}};
}
struct Floor {
    float vertices[18]{-10,0,-10, 10,0,10, 10,0,-10, -10,0,-10, -10,0,10, 10,0,10};
    Mesh mesh{};
    Model model{};
    TownDocument document;
    Floor() {
        mesh.vertexCount = 6; mesh.triangleCount = 2; mesh.vertices = vertices;
        model.meshCount = 1; model.meshes = &mesh;
        document.assets = {{"floor","Floor",0,1,0,{{-10,0,-10},{10,0,10}}}};
        document.instances = {{0, MatrixIdentity(), "ground"}};
    }
    TownNavigation bake() {
        TownNavigation nav;
        nav.width = nav.depth = 100; nav.minX = nav.minZ = -10; nav.cell = .2f;
        nav.spawn = {-6,0,-6}; nav.mission = {6,0,-6};
        nav.bake(document, model); return nav;
    }
};
} // namespace
int main() {
    const auto directory = std::filesystem::temp_directory_path() /
        ("deathward-walk-areas-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        Floor floor;
        auto original = floor.bake();
        check(std::isfinite(original.height({9,0,0})), "legacy scenes keep their original walkable ground");
        auto allowed = rectangle("town-limit", false, -8,-8,8,8);
        allowed.validate();
        check(allowed.contains({0,100,0}) && allowed.contains({8,0,0}) && !allowed.contains({9,0,0}),
              "outlines act on XZ and include the drawn boundary");
        auto reversed = allowed;
        std::reverse(reversed.points.begin(), reversed.points.end()); reversed.validate();
        check(reversed.contains({0,0,0}), "clockwise and counter-clockwise outlines work");
        TownWalkArea concave{"bend",false,{{-8,0,-8},{8,0,-8},{8,0,0},{0,0,0},{0,0,8},{-8,0,8}}};
        concave.validate();
        check(concave.contains({-4,0,4}) && !concave.contains({4,0,4}), "concave outlines preserve their notch");
        auto invalid = allowed;
        std::swap(invalid.points[1], invalid.points[2]);
        rejects([&] { invalid.validate(); }, "crossing edges are rejected");
        invalid = allowed; invalid.points[1] = invalid.points[0];
        rejects([&] { invalid.validate(); }, "duplicate consecutive points are rejected");
        invalid = {"line",false,{{0,0,0},{1,0,0},{2,0,0}}};
        rejects([&] { invalid.validate(); }, "zero-area polygons are rejected");
        invalid = allowed; invalid.points[0].x = std::numeric_limits<float>::quiet_NaN();
        rejects([&] { invalid.validate(); }, "nonfinite coordinates are rejected");
        floor.document.walkAreas = {allowed, rectangle("keep-out", true, -1,-4,1,4)};
        auto nav = floor.bake();
        HubWorld world; world.setNavigation(nav);
        check(world.walkable({3,0,0}) && !world.walkable({0,0,0}) && !world.walkable({9,0,0}),
              "allowed boundaries and blocked islands both constrain navigation");
        check(!world.walkable({1.1f,0,0}) && !world.walkable({7.9f,0,0}), "boundaries preserve player clearance");
        world.player.position = {-3,.85f,0};
        for (int i = 0; i < 120; ++i) world.step({1,0,0}, Tick);
        check(world.player.position.x < -1.3f && world.player.position.x > -2,
              "held keyboard movement stops at a blocked outline");
        check(world.moveTo({3,0,0}), "mouse navigation can find a route around a blocked area");
        for (int i = 0; i < 600 && world.destination(); ++i) {
            world.step({}, Tick);
            check(floor.document.walkAllowed(world.player.position), "mouse route never crosses a restricted cell");
        }
        check(distance(world.player.position,{3,.85f,0}) < .2f, "mouse route reaches the other side legally");
        check(world.moveTo({9,0,0}), "an outside click can approach the allowed boundary");
        for (int i = 0; i < 180 && world.destination(); ++i) world.step({}, Tick);
        check(world.player.position.x < 8 && world.player.position.x > 7, "outside click stops before leaving the allowed region");
        floor.document.walkAreas = {allowed, rectangle("thin-strip", true, -.06f,-8,.06f,8)};
        rejects([&] { floor.bake(); }, "a thin strip cannot disappear or silently relocate an unreachable mission marker");
        floor.document.walkAreas = {rectangle("arrival-blocked",true,-7,-7,-5,-5)};
        rejects([&] { floor.bake(); }, "excluding Arrival fails before writing navigation");
        floor.document.walkAreas = {rectangle("mission-blocked",true,5,-7,7,-5)};
        rejects([&] { floor.bake(); }, "excluding Missions fails before writing navigation");
        floor.document.walkAreas = {rectangle("only-block",true,-1,-1,1,1)};
        check(std::isfinite(floor.bake().height({9,0,0})), "blocked-only maps keep unrestricted outer ground");
        floor.document.walkAreas = {rectangle("left",false,-8,-8,0,8), rectangle("right",false,0,-8,8,8)};
        world.setNavigation(floor.bake());
        check(world.canTraverse({-4,0,0},{4,0,0}), "adjacent allowed polygons form a continuous union");
        floor.document.walkAreas = {allowed, rectangle("keep-out",true,-1,-4,1,4)};
        std::filesystem::create_directories(directory);
        floor.document.write(directory / "town.scene"); nav.write(directory / "town.nav");
        TownDocument loaded; std::string error;
        check(loaded.load(directory / "town.scene", error) && loaded.walkAreas.size() == 2 &&
              loaded.walkAreas[1].blocked && loaded.walkAreas[0].points[2].x == 8,
              "scene format 8 round-trips boundaries and their meaning");
        check(world.load(directory / "town.nav") && !world.walkable({0,0,0}) && !world.walkable({9,0,0}),
              "runtime navigation retains the restrictions after reload");
        auto duplicate = floor.document; duplicate.walkAreas.push_back(allowed);
        rejects([&] { duplicate.validate(); }, "duplicate area IDs are rejected");
        { std::ofstream out(directory / "town.scene", std::ios::app); out << "walk_area broken 0 999999\n"; }
        check(!loaded.load(directory / "town.scene", error) && loaded.walkAreas.size() == 2,
              "malformed area records preserve the previous loaded scene");
        floor.document.walkAreas.clear();
        check(std::isfinite(floor.bake().height({9,0,0})), "removing limits and rebaking restores geometry navigation");
        std::filesystem::remove_all(directory);
        std::cout << "PASS walk-area geometry, union, exclusions, clearance, WASD/mouse boundaries, guarded markers and scene/navigation persistence\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << "\nTemporary directory: " << directory << '\n'; return 1;
    }
}
