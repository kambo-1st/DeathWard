#include "render/PlayerModel.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace dw;
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
BoundingBox animatedBounds(const Model &model) {
    BoundingBox result{{1000, 1000, 1000}, {-1000, -1000, -1000}};
    for (int mesh = 0; mesh < model.meshCount; ++mesh)
        for (int vertex = 0; vertex < model.meshes[mesh].vertexCount; ++vertex) {
            const float *point = model.meshes[mesh].animVertices + vertex * 3;
            for (int axis = 0; axis < 3; ++axis)
                check(std::isfinite(point[axis]), "skinned vertices stay finite");
            result.min.x = std::min(result.min.x, point[0]);
            result.min.y = std::min(result.min.y, point[1]);
            result.min.z = std::min(result.min.z, point[2]);
            result.max.x = std::max(result.max.x, point[0]);
            result.max.y = std::max(result.max.y, point[1]);
            result.max.z = std::max(result.max.z, point[2]);
        }
    return result;
}
float poseDifference(const std::vector<Transform> &a, const std::vector<Transform> &b) {
    float difference = 0;
    for (size_t i = 0; i < a.size(); ++i)
        difference += distance(a[i].translation, b[i].translation);
    return difference;
}
void verifyModel() {
    PlayerModel model;
    const auto path = PlayerModel::assetPath();
    check(std::filesystem::equivalent(path.parent_path().parent_path().parent_path(),
                                      GetApplicationDirectory()),
          "runtime model is packaged beside the executable");
    const auto previousDirectory = std::filesystem::current_path();
    std::filesystem::current_path(std::filesystem::temp_directory_path());
    check(model.load(), "model loads independently of the current working directory");
    std::filesystem::current_path(previousDirectory);
    check(model.model().boneCount == 48 && model.model().meshCount == 1,
          "converted asset has one mesh and the original 48-bone skeleton");
    bool textured = false;
    for (int i = 0; i < model.model().materialCount; ++i) {
        const auto texture = model.model().materials[i].maps[MATERIAL_MAP_DIFFUSE].texture;
        textured = textured || (texture.width == 2048 && texture.height == 2048);
    }
    check(textured, "original embedded texture is present");
    for (int i = 0; i < int(PlayerAnimation::Count); ++i)
        check(model.duration(PlayerAnimation(i)) > 0.2f, "all nine source clips are available");
    for (int m = 0; m < model.model().meshCount; ++m) {
        const auto &mesh = model.model().meshes[m];
        for (int v = 0; v < mesh.vertexCount; ++v) {
            float weight = 0;
            for (int i = 0; i < 4; ++i) {
                weight += mesh.boneWeights[v * 4 + i];
                check(mesh.boneIds[v * 4 + i] < model.model().boneCount, "skin references valid bones");
            }
            check(std::abs(weight - 1) < 0.001f, "skin weights are normalized");
        }
    }

    Simulation run(1866, 1, {});
    run.player.position = {0, 0.85f, 0};
    model.update(run);
    check(model.animation() == PlayerAnimation::Idle, "standing uses breathing idle");
    const auto first = model.pose();
    run.stats.duration += 0.7;
    model.update(run);
    check(poseDifference(first, model.pose()) > 0.001f, "idle skeleton is animated, not a static mesh");
    auto bounds = animatedBounds(model.model());
    check(bounds.max.y - bounds.min.y > 1.6f && bounds.max.y - bounds.min.y < 2.2f,
          "animation and mesh use the same meter scale");
    const auto paused = model.pose();
    for (int i = 0; i < 20; ++i)
        model.update(run);
    check(poseDifference(paused, model.pose()) < 0.00001f, "paused simulation freezes the animation");

    run.player.velocity = {0, 0, 2};
    run.stats.duration += 0.2;
    model.update(run);
    check(model.animation() == PlayerAnimation::Walk, "slow movement selects walking");
    run.player.velocity.z = 6;
    run.stats.duration += 0.2;
    model.update(run);
    check(model.animation() == PlayerAnimation::Run, "normal movement selects running");
    const auto runStart = model.pose();
    for (int i = 0; i < 180; ++i) {
        run.stats.duration += Tick;
        model.update(run);
        check(std::abs(model.pose()[0].translation.x) < 0.001f &&
                  std::abs(model.pose()[0].translation.z) < 0.001f,
              "looping animation cannot drift away from the gameplay position");
    }
    check(poseDifference(runStart, model.pose()) > 0.01f, "running advances through different poses");
    const float beforeSlowTick = model.animationTime();
    run.stats.duration += Tick * 0.2f;
    model.update(run);
    check(std::abs(model.animationTime() - beforeSlowTick - Tick * 0.2f) < 0.0001f,
          "animation respects slowed simulation time");
    run.player.shootPose = 0.32f;
    run.stats.duration += 0.2;
    model.update(run);
    check(model.animation() == PlayerAnimation::Run && model.firingBlend() > 0.99f,
          "shooting while moving blends firing over locomotion");
    run.player.velocity = {};
    run.stats.duration += 0.2;
    model.update(run);
    check(model.animation() == PlayerAnimation::Fire, "stationary attacks use the firing clip");
    run.player.shootPose = 0;
    run.player.dodge = 0.11f;
    run.player.dodgeMoving = true;
    run.stats.duration += 0.1;
    model.update(run);
    check(model.animation() == PlayerAnimation::DodgeSlide, "moving dodge uses Running Slide");
    run.player.dodgeMoving = false;
    run.stats.duration += 0.05;
    model.update(run);
    check(model.animation() == PlayerAnimation::DodgeStanding, "dodge from rest uses Jumping");
    run.player.dodge = 0;
    run.dead = true;
    model.update(run, 1);
    check(model.animation() == PlayerAnimation::Death, "ordinary death uses its supplied clip");
    model.update(run, 2);
    const auto corpse = model.pose();
    model.update(run, 3);
    check(poseDifference(corpse, model.pose()) < 0.00001f, "death holds its final pose without looping");
    run.player.shootPose = 0.32f;
    model.update(run, 3.1f);
    check(model.animation() == PlayerAnimation::DeathRifle, "death while firing uses Rifle Death");
    bounds = animatedBounds(model.model());
    check(bounds.max.x - bounds.min.x < 3 && bounds.max.y - bounds.min.y < 3 &&
              bounds.max.z - bounds.min.z < 3,
          "mixed skin remains bounded through action transitions");
    Simulation next(1866, 2, {});
    model.update(next);
    check(model.animation() == PlayerAnimation::Idle && model.animationTime() == 0,
          "a new expedition resets the previous animation");
    check(!model.load(path.parent_path() / "missing.glb") && !model.loaded(),
          "missing asset fails safely for the procedural fallback");
    check(model.load(path), "asset can be reloaded after cleanup or failure");
    model.update(next);
    model.unload();
    model.unload();
}
} // namespace

int main() {
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(640, 480, "Bandit model verification");
        check(IsWindowReady(), "a graphics display is required");
        verifyModel();
        CloseWindow();
        std::cout
            << "PASS packaged bandit mesh, texture, nine clips, blending, timing, root motion and cleanup\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
