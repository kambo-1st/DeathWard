#include "raylib.h"
#include "raymath.h"
#include "world/HubWorld.hpp"
#include "world/ObjectAnimation.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
bool same(Matrix a, Matrix b, float epsilon = .001f) {
    const auto x = MatrixToFloatV(a), y = MatrixToFloatV(b);
    for (int n = 0; n < 16; ++n)
        if (std::abs(x.v[n] - y.v[n]) > epsilon)
            return false;
    return true;
}
Vector3 position(Matrix m) {
    return {m.m12, m.m13, m.m14};
}
TownDocument town() {
    TownDocument d;
    std::string error;
    const auto pack = std::filesystem::path(__FILE__).parent_path().parent_path() / "assets/town";
    check(d.load(pack / "town.scene", error), error.c_str());
    return d;
}
size_t object(const TownDocument &d, const std::string &id) {
    for (size_t n = 0; n < d.instances.size(); ++n)
        if (d.instances[n].id == id)
            return n;
    throw std::runtime_error("Missing train fixture object");
}
float railDistance(Vector3 p) {
    p.y = 0;
    float best = 1e9f;
    auto line = [&](Vector3 a, Vector3 b) {
        const auto d = sub(b, a);
        best =
            std::min(best, distance(p, add(a, mul(d, std::clamp(dot(sub(p, a), d) / dot(d, d), 0.f, 1.f)))));
    };
    line({-40, 0, 18}, {50, 0, 18});
    line({-40, 0, 108}, {50, 0, 108});
    line({-65, 0, 43}, {-65, 0, 83});
    line({75, 0, 43}, {75, 0, 83});
    for (const auto c : std::array<Vector3, 4>{{{-40, 0, 43}, {-40, 0, 83}, {50, 0, 83}, {50, 0, 43}}}) {
        const bool quadrant = (c.x < 0 ? p.x <= c.x : p.x >= c.x) && (c.z < 60 ? p.z <= c.z : p.z >= c.z);
        if (quadrant)
            best = std::min(best, std::abs(distance(p, c) - 25));
    }
    return best;
}
void routeAndWheels(const TownDocument &d) {
    ObjectAnimationSystem a, b, c;
    a.reset(d);
    b.reset(d);
    c.reset(d);
    check(a.activeCount() == 64 && a.solids().size() == 8,
          "two trains bind all 62 parts as eight solid vehicles");
    int wheels = 0;
    for (size_t n = 0; n < d.instances.size(); ++n) {
        check(same(a.poses()[n].transform, d.instances[n].transform, 0),
              "reset retains exact original placements");
        wheels += d.instances[n].wheelRadius > 0;
    }
    check(wheels == 16, "all sixteen independent locomotive wheels have axle drivers");
    for (int n = 0; n < 600; ++n)
        a.update(1.f / 30, {});
    for (int n = 0; n < 1200; ++n)
        b.update(Tick, {});
    for (int n = 0; n < 2400; ++n)
        c.update(1.f / 120, {});
    for (size_t n = 0; n < d.instances.size(); ++n)
        if (!d.instances[n].group.empty())
            check(same(a.poses()[n].transform, b.poses()[n].transform) &&
                      same(a.poses()[n].transform, c.poses()[n].transform),
                  "train movement is frame-rate independent");
    a.reset(d);
    const auto body = object(d, "60904987:1235095919362174");
    const auto bell = object(d, "60904987:1538712731066112");
    const auto wheel = object(d, "60904987:1172621986598204");
    const auto bellBind =
        MatrixMultiply(d.instances[bell].transform, MatrixInvert(d.instances[body].transform));
    const auto axleBind =
        Vector3Transform(position(d.instances[wheel].transform), MatrixInvert(d.instances[body].transform));
    bool curved = false, stopped = false, resumed = false;
    double beforeStop = 0;
    for (int n = 0; n < 210 * 60; ++n) {
        const auto previous = a.poses()[body].transform;
        a.update(Tick, {});
        const auto current = a.poses()[body].transform;
        check(distance(position(previous), position(current)) < .12f,
              "train never teleports at curves or loop seam");
        const auto relative = MatrixMultiply(a.poses()[bell].transform, MatrixInvert(current));
        check(same(relative, bellBind, .003f),
              "cab, bell and attachments retain their rigid group transform");
        const auto axle = Vector3Transform(position(a.poses()[wheel].transform), MatrixInvert(current));
        check(distance(axle, axleBind) < .002f, "spinning wheel stays centered on its original axle");
        const auto forward = unit(Vector3{current.m8, 0, current.m10});
        for (const float sign : {-1.f, 1.f})
            check(railDistance(add(position(current), mul(forward, sign * 8.05f * .5f))) < .13f,
                  "front and rear axle positions remain on the original rail centerline");
        curved |= std::abs(forward.x) > .2f && std::abs(forward.z) > .2f;
        if (a.pathDistance() > 400 && a.pathSpeed() == 0) {
            stopped = true;
            beforeStop = a.pathDistance();
        }
        if (stopped && a.pathDistance() > beforeStop + 1)
            resumed = true;
    }
    check(curved && stopped && resumed, "train completes curves, stops for the station and departs again");
    check(!same(a.poses()[wheel].transform, MatrixMultiply(d.instances[wheel].transform, MatrixIdentity())),
          "wheels animate during travel");
    a.reset(d);
    for (int n = 0; n < 300; ++n)
        a.update(Tick, {});
    check(a.pathDistance() == 0 && same(a.poses()[body].transform, d.instances[body].transform, 0),
          "station dwell holds wheels and body at rest");
    for (int n = 0; n < 400; ++n)
        a.update(Tick, {});
    const auto solid =
        a.solids()[size_t(std::find_if(d.groups.begin(), d.groups.end(),
                                       [&](const auto &g) { return g.id == d.instances[body].group; }) -
                          d.groups.begin())];
    auto player = add(solid.center, mul(solid.forward, solid.halfSize.x + .85f));
    player.y = .9f;
    const auto before = a.pathDistance();
    const auto wheelBefore = a.poses()[wheel].transform;
    for (int n = 0; n < 120; ++n)
        a.update(Tick, {}, player);
    check(a.pathDistance() == before && same(wheelBefore, a.poses()[wheel].transform, 0),
          "blocked route and distance-driven wheels stop together without crushing the player");
    a.update(0, {});
    check(a.pathDistance() == before, "pause preserves route progress");
    for (int n = 0; n < 120; ++n)
        a.update(Tick, {}, Vector3{0, 1, -5});
    check(a.pathDistance() > before + 1, "clearing the track restarts the convoy smoothly");
}
void persistence(const TownDocument &d, const std::filesystem::path &temp) {
    d.write(temp / "train.scene");
    TownDocument copy;
    std::string error;
    check(copy.load(temp / "train.scene", error), "scene format 3 loads");
    check(copy.groups.size() == 8 && copy.paths.size() == 1 &&
              copy.instances[36].group == d.instances[36].group &&
              copy.instances[36].wheelRadius == d.instances[36].wheelRadius,
          "groups, paths and wheel bindings survive saves");
    std::reverse(copy.instances.begin(), copy.instances.end());
    copy.write(temp / "train.scene");
    check(copy.load(temp / "train.scene", error) && copy.instances.back().id == d.instances.front().id,
          "stable train bindings survive instance reordering");
    copy.groups[0].path = "missing";
    bool rejected = false;
    try {
        copy.validate();
    } catch (...) {
        rejected = true;
    }
    check(rejected, "missing route references are rejected");
    copy = d;
    copy.paths[0].points.back() = {900, 0, 900};
    rejected = false;
    try {
        copy.validate();
    } catch (...) {
        rejected = true;
    }
    check(rejected, "disconnected loop endpoints are rejected");
}
void dynamicNavigation(const std::filesystem::path &temp) {
    const auto file = temp / "flat.nav";
    std::ofstream out(file, std::ios::binary);
    auto write = [&](const auto &v) { out.write(reinterpret_cast<const char *>(&v), sizeof(v)); };
    out.write("DWTNAV01", 8);
    uint32_t size = 150;
    write(size);
    write(size);
    for (float v : {0.f, 0.f, .4f, 20.f, 0.f, 30.f, 40.f, 0.f, 30.f})
        write(v);
    std::vector<float> heights(size * size, 0);
    out.write(reinterpret_cast<const char *>(heights.data()), heights.size() * sizeof(float));
    out.close();
    HubWorld hub;
    check(hub.load(file), "dynamic navigation fixture loads");
    MovingSolid solid{{30, 2, 30}, {1, 0, 0}, {6, 2, 1.7f}};
    hub.setMovingSolids({solid});
    check(!hub.walkable({30, 0, 30}) && hub.walkable({30, 0, 35}),
          "moving occupancy blocks only the current vehicle footprint");
    for (int n = 0; n < 120; ++n)
        hub.step({1, 0, 0}, Tick);
    check(!solid.contains(hub.player.position) && hub.player.position.x < 24,
          "WASD cannot cross the train hull");
    hub.reset();
    check(hub.moveTo({40, 0, 30}), "mouse path can go around the current train");
    for (int n = 0; n < 1000 && hub.destination(); ++n) {
        hub.step({}, Tick);
        check(!solid.contains(hub.player.position), "mouse route stays outside moving solid clearance");
    }
    check(distance(hub.player.position, {40, .85f, 30}) < .001f,
          "mouse path arrives after routing around the train");
    solid.center.z = 40;
    hub.setMovingSolids({solid});
    check(hub.walkable({30, 0, 30}) && !hub.walkable({30, 0, 40}),
          "moving away clears every obsolete occupied cell");
    hub.setMovingSolids({});
    hub.reset();
    check(hub.moveTo({40, 0, 30}), "initial route is open");
    solid.center.z = 30;
    hub.setMovingSolids({solid});
    for (int n = 0; n < 1000 && hub.destination(); ++n)
        hub.step({}, Tick);
    check(distance(hub.player.position, {40, .85f, 30}) < .001f,
          "a train entering an existing mouse route triggers replanning");
    hub.setMovingSolids({});
    hub.reset();
    check(hub.moveTo({40, 0, 30}), "open target accepted");
    solid.center = {42, 2, 30};
    hub.setMovingSolids({solid});
    for (int n = 0; n < 240; ++n)
        hub.step({}, Tick);
    check(hub.destination() && distance(*hub.destination(), {40, 0, 30}) < .001f,
          "a temporarily covered goal keeps the original mouse destination");
    hub.setMovingSolids({});
    for (int n = 0; n < 500 && hub.destination(); ++n)
        hub.step({}, Tick);
    check(distance(hub.player.position, {40, .85f, 30}) < .001f,
          "waiting movement resumes when the train clears its destination");
    const auto pack = std::filesystem::path(__FILE__).parent_path().parent_path() / "assets/town";
    check(hub.load(pack / "town.nav") && hub.walkable({-21.81f, 0, 18}),
          "original locomotive footprint is ground after rebaking");
}
} // namespace
int main() {
    const auto temp = std::filesystem::temp_directory_path() / "deathward-train-tests";
    try {
        std::filesystem::create_directories(temp);
        const auto d = town();
        routeAndWheels(d);
        persistence(d, temp);
        dynamicNavigation(temp);
        std::filesystem::remove_all(temp);
        std::cout << "PASS train routes, wheel axles, groups, station stops, player clearance, dynamic "
                     "navigation and persistence\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
