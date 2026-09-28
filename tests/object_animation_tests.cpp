#include "raylib.h"
#include "raymath.h"
#include "world/HubWorld.hpp"
#include "world/ObjectAnimation.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool pass, const char *message) {
    if (!pass)
        throw std::runtime_error(message);
}
bool same(Matrix a, Matrix b, float tolerance = .0001f) {
    const auto x = MatrixToFloatV(a), y = MatrixToFloatV(b);
    for (int n = 0; n < 16; ++n)
        if (std::abs(x.v[n] - y.v[n]) > tolerance)
            return false;
    return true;
}
TownDocument fixture() {
    TownDocument doc;
    doc.assets.push_back({"ball", "Ball", 0, 1, 0, {{-.3f, -.3f, -.3f}, {.3f, .3f, .3f}}});
    TownInstance i{0, MatrixTranslate(0, .3f, 0), "first"};
    i.motion.kind = ObjectMotionKind::Tumbleweed;
    doc.instances = {i, i};
    doc.instances[1].id = "second";
    return doc;
}
void determinismAndGround() {
    const auto doc = fixture();
    const auto ground = [](Vector3) { return 0.f; };
    ObjectAnimationSystem a, b, c;
    a.reset(doc);
    b.reset(doc);
    c.reset(doc);
    check(same(a.poses()[0].transform, doc.instances[0].transform),
          "reset preserves the exact authored pose");
    for (int n = 0; n < 120; ++n)
        a.update(1.f / 120, ground);
    for (int n = 0; n < 60; ++n)
        b.update(1.f / 60, ground);
    for (int n = 0; n < 30; ++n)
        c.update(1.f / 30, ground);
    check(same(a.poses()[0].transform, b.poses()[0].transform) &&
              same(a.poses()[0].transform, c.poses()[0].transform),
          "wind motion is independent of rendered frame rate");
    check(!same(a.poses()[0].transform, a.poses()[1].transform),
          "instances sharing one mesh have independent phases");
    check(!same(a.poses()[0].transform, doc.instances[0].transform) && a.activeCount() == 2,
          "wind advances both position and rolling orientation");
    const auto paused = a.poses()[0].transform;
    a.update(0, ground);
    check(same(paused, a.poses()[0].transform), "paused updates do not change poses");
    a.reset(doc);
    const auto walls = [](Vector3 p) { return std::abs(p.x) < 2 && std::abs(p.z) < 2 ? 0.f : NAN; };
    for (int n = 0; n < 7200; ++n) {
        const auto before = a.poses()[0].transform;
        a.update(Tick, walls);
        const auto after = a.poses()[0].transform;
        check(std::abs(after.m12) <= 1.701f && std::abs(after.m14) <= 1.701f,
              "the rolling sphere stays clear of scenery and navigation edges");
        check(distance({before.m12, before.m13, before.m14}, {after.m12, after.m13, after.m14}) < .15f,
              "collision turns do not teleport a tumbleweed");
        check(after.m13 >= .3f && after.m13 <= .341f, "rolling follows the floor with only a small bounce");
    }
}
void pivots() {
    auto doc = fixture();
    auto &i = doc.instances[0];
    i.transform = MatrixMultiply(MatrixScale(-2, 1, 3), MatrixTranslate(5, 2, 8));
    i.transform.m4 = .2f; // Preserve an imported shear as well as a reflection.
    i.motion.kind = ObjectMotionKind::Spin;
    i.motion.speed = 90;
    i.motion.pivot = {1, 0, 0};
    i.motion.axis = {0, 1, 0};
    doc.instances[1].motion.kind = ObjectMotionKind::None;
    ObjectAnimationSystem motion;
    motion.reset(doc);
    const auto fixed = Vector3Transform(i.motion.pivot, i.transform);
    for (int n = 0; n < 60; ++n)
        motion.update(Tick, {});
    check(distance(fixed, Vector3Transform(i.motion.pivot, motion.poses()[0].transform)) < .0001f,
          "rotation uses the authored local pivot under reflected and sheared transforms");
    check(std::abs(MatrixDeterminant(i.transform) - MatrixDeterminant(motion.poses()[0].transform)) < .001f,
          "animation preserves scale, reflection and shear");
    check(same(motion.poses()[1].transform, doc.instances[1].transform), "static objects stay exact");
    for (int n = 0; n < 180; ++n)
        motion.update(Tick, {});
    check(same(motion.poses()[0].transform, i.transform), "a full spin has no accumulated transform drift");
    i.motion.kind = ObjectMotionKind::Sway;
    i.motion.speed = 1;
    i.motion.period = 2;
    i.motion.amplitude = 15;
    motion.reset(doc);
    for (int n = 0; n < 30; ++n)
        motion.update(Tick, {});
    check(!same(motion.poses()[0].transform, i.transform), "sway reaches a distinct pose");
    for (int n = 0; n < 90; ++n)
        motion.update(Tick, {});
    check(same(motion.poses()[0].transform, i.transform), "sway returns to the rest pose");
}
void serialization(const std::filesystem::path &directory) {
    auto doc = fixture();
    doc.write(directory / "test.scene");
    TownDocument read;
    std::string error;
    check(read.load(directory / "test.scene", error), "version 2 loads");
    check(read.instances[0].id == "first" && read.instances[0].motion.kind == ObjectMotionKind::Tumbleweed &&
              same(read.instances[0].transform, doc.instances[0].transform),
          "scene roundtrip preserves bindings, configuration and rest transforms");
    std::swap(read.instances[0], read.instances[1]);
    read.write(directory / "test.scene");
    check(read.load(directory / "test.scene", error) && read.instances[0].id == "second",
          "reordering does not move animation to another object");
    {
        std::ofstream legacy(directory / "legacy.scene");
        legacy << "DEATHWARD_TOWN 1\nasset ball 0 1 0 -.3 -.3 -.3 .3 .3 .3\ninstance 0 1 0 0 0 0 1 0 .3 0 0 "
                  "1 0 0 0 0 1\n";
    }
    check(read.load(directory / "legacy.scene", error) &&
              read.instances[0].motion.kind == ObjectMotionKind::None && !read.instances[0].id.empty(),
          "legacy scenes stay static and acquire stable IDs");
    {
        std::ofstream bad(directory / "bad.scene");
        bad << "DEATHWARD_TOWN 2\nasset ball 0 1 0 -.3 -.3 -.3 .3 .3 .3\ninstance 0 one 1 0 0 0 0 1 0 .3 0 0 "
               "1 0 0 0 0 1\nmotion missing 3 1 .04 6 1 0 1 0 0 0 0\n";
    }
    check(!read.load(directory / "bad.scene", error) && read.instances[0].id == "legacy-1",
          "invalid bindings cannot replace a valid document");
    doc.instances[1].id = doc.instances[0].id;
    bool rejected = false;
    try {
        doc.validate();
    } catch (...) {
        rejected = true;
    }
    check(rejected, "duplicate IDs are rejected");
}
void townMotion() {
    const auto assets = std::filesystem::path(__FILE__).parent_path().parent_path() / "assets/town";
    TownDocument doc;
    HubWorld nav;
    std::string error;
    check(doc.load(assets / "town.scene", error) && nav.load(assets / "town.nav"), "town assets load");
    ObjectAnimationSystem motion;
    motion.reset(doc);
    check(motion.activeCount() == 2, "the imported town binds exactly two tumbleweeds");
    for (size_t n = 0; n < doc.instances.size(); ++n)
        if (motion.poses()[n].animated) {
            const auto &m = doc.instances[n].transform;
            check(nav.walkable({m.m12, 0, m.m14}), "the tumbleweed's original footprint is walkable ground");
        }
    for (int n = 0; n < 600; ++n)
        motion.update(Tick, [&](Vector3 p) { return nav.height(p); });
    for (size_t n = 0; n < doc.instances.size(); ++n)
        if (motion.poses()[n].animated)
            check(!same(motion.poses()[n].transform, doc.instances[n].transform),
                  "each real tumbleweed moves on imported ground");
}
} // namespace
int main() {
    const auto temp = std::filesystem::temp_directory_path() / "deathward-object-motion-tests";
    try {
        std::filesystem::create_directories(temp);
        determinismAndGround();
        pivots();
        serialization(temp);
        townMotion();
        std::filesystem::remove_all(temp);
        std::cout << "PASS object motion, ground collisions, pivots, stable IDs, scene versions and imported "
                     "tumbleweeds\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
