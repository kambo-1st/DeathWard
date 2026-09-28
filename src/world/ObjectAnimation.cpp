#include "world/ObjectAnimation.hpp"
#include "raymath.h"

namespace dw {
namespace {
constexpr double MotionTick = 1.0 / 60.0;
Matrix about(Matrix base, Vector3 center, Matrix rotation, Vector3 destination) {
    return MatrixMultiply(
        MatrixMultiply(MatrixMultiply(base, MatrixTranslate(-center.x, -center.y, -center.z)), rotation),
        MatrixTranslate(destination.x, destination.y, destination.z));
}
float groundHeight(const ObjectAnimationSystem::Ground &ground, Vector3 p, float radius) {
    if (!ground)
        return std::numeric_limits<float>::quiet_NaN();
    const float y = ground(p);
    if (!std::isfinite(y))
        return y;
    for (int n = 0; n < 8; ++n) {
        const float a = float(n) * Pi / 4;
        const float edge = ground(add(p, {radius * std::cos(a), 0, radius * std::sin(a)}));
        if (!std::isfinite(edge) || std::abs(edge - y) > .4f)
            return std::numeric_limits<float>::quiet_NaN();
    }
    return y;
}
} // namespace
void ObjectAnimationSystem::reset(const TownDocument &document) {
    document.validate();
    poses_.clear();
    moving_.clear();
    accumulator_ = time_ = 0;
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        const auto local = document.assets[i.asset].bounds;
        const auto bounds = document.bounds(n);
        poses_.push_back({i.transform, bounds, i.motion.kind != ObjectMotionKind::None});
        if (i.motion.kind == ObjectMotionKind::None)
            continue;
        Moving state{n, i.transform, local, i.motion};
        state.center = state.restCenter = mul(add(bounds.min, bounds.max), .5f);
        const auto size = sub(bounds.max, bounds.min);
        state.radius = std::max(.05f, std::max({size.x, size.y, size.z}) * .5f);
        uint64_t seed = i.motion.seed;
        for (unsigned char c : i.id)
            seed = (seed ^ c) * 1099511628211ULL;
        Random random(seed);
        state.phase = random.real(0, 2 * Pi);
        state.heading = {std::cos(state.phase), 0, std::sin(state.phase)};
        moving_.push_back(state);
    }
}
void ObjectAnimationSystem::update(float dt, const Ground &ground) {
    if (!std::isfinite(dt) || dt <= 0 || moving_.empty())
        return;
    accumulator_ += std::min(double(dt), .25);
    while (accumulator_ + 1e-9 >= MotionTick) {
        accumulator_ -= MotionTick;
        time_ += MotionTick;
        step(ground);
    }
}
void ObjectAnimationSystem::step(const Ground &ground) {
    for (auto &s : moving_) {
        const auto &m = s.motion;
        Matrix pose = s.rest;
        if (m.kind == ObjectMotionKind::Tumbleweed) {
            const float wave = float(std::fmod(time_ / m.period, 1000.0)) * 2 * Pi;
            const float wind = s.phase + .5f * std::sin(wave * .37f + s.phase);
            const Vector3 desired{std::cos(wind), 0, std::sin(wind)};
            s.heading = unit(add(mul(s.heading, .992f), mul(desired, .008f)));
            const float speed = m.speed * (.8f + .2f * std::sin(wave + s.phase));
            const auto delta = mul(s.heading, speed * float(MotionTick));
            const auto candidate = add(s.center, delta);
            const float y = groundHeight(ground, candidate, s.radius);
            if (std::isfinite(y) && std::abs(y + s.radius - s.center.y) < .6f) {
                const float travel = length(delta);
                s.distance += travel;
                if (travel > .000001f) {
                    const auto axis = unit(Vector3CrossProduct({0, 1, 0}, delta));
                    s.roll = QuaternionNormalize(
                        QuaternionMultiply(QuaternionFromAxisAngle(axis, travel / s.radius), s.roll));
                }
                s.center = candidate;
                s.center.y = y + s.radius;
            } else {
                // Bounce against the blocked axis without teleporting to another street.
                const bool xClear =
                    std::isfinite(groundHeight(ground, add(s.center, {delta.x, 0, 0}), s.radius));
                const bool zClear =
                    std::isfinite(groundHeight(ground, add(s.center, {0, 0, delta.z}), s.radius));
                if (!xClear || zClear)
                    s.heading.x = -s.heading.x;
                if (!zClear || xClear)
                    s.heading.z = -s.heading.z;
            }
            auto center = s.center;
            center.y += m.amplitude * std::abs(std::sin(s.distance / s.radius));
            pose = about(s.rest, s.restCenter, QuaternionToMatrix(s.roll), center);
        } else {
            const float angle =
                m.kind == ObjectMotionKind::Spin
                    ? float(std::fmod(time_ * m.speed, 360.0))
                    : m.amplitude * std::sin(float(std::fmod(time_ * m.speed / m.period, 1.0)) * 2 * Pi);
            const auto local =
                about(MatrixIdentity(), m.pivot, MatrixRotate(unit(m.axis), angle * DEG2RAD), m.pivot);
            pose = MatrixMultiply(local, s.rest);
        }
        poses_[s.index] = {pose, objectBounds(s.local, pose), true};
    }
}
} // namespace dw
